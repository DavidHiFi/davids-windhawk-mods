# 2026-10-08: Taskbar Audio Visualizer 1.3.1 - the strip follows the taskbar's real state

## The complaint

The user could not see the audio visualizer at all any more: the taskbar sat
plainly on screen while the strip was gone, and the strip only came back when
they clicked the taskbar. Yesterday's 1.3.0 "taskbar auto-hide follow" was the
breaking change.

## What was actually wrong (three things)

1. **The follow model read a signal the shell ignores.** `1.3.0` keyed the
   reveal decision to the StuckRects3 auto-hide switch plus cursor/foreground
   heuristics. On this machine the shell *claims* auto-hide (StuckRects3 byte
   12 bit 0 = 1, SHAppBarMessage says so too) but actually behaves as a
   resident bar: the monitor's work area is pushed in by the full 50 px bar
   height and the bar sat parked and visible for minutes at a time with the
   cursor on another monitor (4 monitors: one above, one left, one right) and
   an ordinary window in the foreground. The model decided "hidden" while the
   bar was plainly on screen. Yesterday's own verification screenshots show it:
   `snap-hidden-2.png` (cursor moved away) still has the whole bar on screen,
   and `snap-revealed.png` has no strip painted at all.

2. **Hide-when-covered was compiled out.** The user asked for "hidden when a
   window is covering the taskbar, just the normal taskbar behavior".
   `pauseWhenObscured` existed (`IsVisualizerOccluded` + coverage check on the
   fullscreen watcher) but `LoadSettings` hardcoded it to `false` and the
   setting was never declared. Two latent bugs inside it:
   - The coverage enumeration failed to discount the strip's own z-order: the
     strip is topmost, parked over the taskbar, so a maximized ordinary
     window's *rect* intersects it while nothing covers it on screen. Enabling
     the check unmodified would have hidden the strip whenever any maximized
     app was open - the same bug by another route. Fixed with a `topmostOnly`
     mode: only WS_EX_TOPMOST genuine app windows count as coverers (fullscreen
     is still handled by the separate foreground watcher).
   - The occlusion target rect was published with the virtual screen origin
     (`SM_XVIRTUALSCREEN`/`SM_YVIRTUALSCREEN`) added to taskbar-local layout
     coordinates. On a single-monitor desktop the virtual screen origin is
     (0,0) and the error is invisible; here the "strip" the occlusion check
     examined was at the bottom edge of the monitor *above* the primary. The
     feature shipped hardcoded off, so nothing ever exercised it. Correct
     origin: the overlay window's own rect (the overlay is parked on the
     taskbar, the layout is taskbar-local).

3. **The tool process wedged mid-reload last night.** The user played a
   fullscreen game (rev 1.3.0_1 paused the strip at 5:44 PM); the
   `set-diagnostics.ps1 0` settings bump landed at 5:47:25 PM and the log ends
   mid-write two lines later (`WhTool_ModSettingsChanged` starts with
   `Wh_Log(L">")`). The instance died with the overlay and media windows
   destroyed, the message window left behind, `Disabled=0` and no living
   instance - the strip was dead until the next foreground change recreated
   it, and nothing healed it afterwards. The zombie windhawk.exe (pid 39008)
   exited cleanly on this morning's first disable.

## The fix (revision 1.3.1)

- `IsTaskbarReservingScreenSpace()` replaces the StuckRects3/ABM read: the
  follow mode is keyed to the shell's live work-area reservation. Bar parked
  and holding its space = resident = the strip stays visible with it. Work
  area full = auto-hide in effect = the reveal heuristics decide, as before.
- `performance.pauseWhenObscured` is a real declared setting now, default on,
  with topmost-only coverage; the coverage call sites for the visualizer and
  the media strip both use it.
- The occlusion draw rect is published from the overlay window's screen
  origin.
- Hiding now requires two agreeing ticks (100 ms), reveals stay immediate -
  a single misread must not park the strip away from a visible bar.
- Self-heal: the 100 ms tick recreates the overlay whenever its window is
  lost (gated by unload/pause/fullscreen state), and `EnsureLazyInitialized`
  retries (throttled to one attempt per 5 s) instead of a one-shot latch that
  made one InitDirectX failure permanent.
- Version, README feature bullet, settings declarations and SETTINGS.md rows
  updated.

## Verification (all measured on this machine)

- Stray facts measured first: work area vs rect, StuckRects3 byte, cursor,
  foreground, a 12 s passive pixel watch of the top edge (no change - the bar
  never auto-hid in desktop use), screenshot of the bar visible with the strip
  absent while clicking showed it.
- Built clean for 64/32 (Windhawk's bundled clang++, Build.ps1):
  `local@taskbar-audio-visualizer_1.3.1_4_{64,32}.dll`,
  64 SHA256 703FD9AD30719E748612695BD7C7582D8E45D30A4B4DBC9945CD871C74EDBE9E,
  32 SHA256 8996C635F749B78E0D1ADC3E7D20A0E554F84FE6009D364BBD2B4FAD3CB026E5.
  (1.3.1_1.._3 were iteration builds inside this session; each install cycle
  verified by audit script, hash match and fresh-instance logs.)
- Screenshot after install: 32 gradient bars seated on the taskbar at the
  chosen offset, cursor on the left monitor and T3 Code foreground, matching
  barIdleSize when audio is silent. `strip-after-reinstall.png`,
  `crop-strip-fixed.png`, `final-strip.png` in the report dir.
- Occlusion: a titled topmost WS_POPUP over the strip rect produced
  `[Viz] occluded: 100% covered (threshold 100%)` + `Pausing visualizer` +
  `watch: covered=100% paused=1`; removing it produced `[Viz] visible again:
  0% covered` + `Resuming visualizer`, within one 250 ms watcher tick each
  way. Diagnostic excerpt archived: `diagnostic-end-of-session.log`.
- Self-heal: posting WM_CLOSE to the overlay destroyed it and a fresh overlay
  window existed within one tick (hwnd changed). NOTE: EnumWindows from the
  Store pwsh session misses some top-level windows - FindWindow by exact class
  is the reliable probe (see the gotcha file).
- Follow: no `[Follow] ... not in effect` flip logged because the initial
  state already matched (resident mode since startup); the gating line and the
  debounce only exercise on real transitions.
- Diagnostics were enabled for the test session and are turned back off
  (`diagnostics.enabled=0`), SettingsChangeTime bumped.
- Final state: single tool process (pid 29080), overlay hwnd 0x1BC1328,
  rect (0,0,2560,50), visible, no leftover tool processes (1528, 23312, 40184,
  39008 all gone), explorer untouched (tray hwnd unchanged all session:
  0x26A1030).

## Records

- Report + install/audit/rollback script + build + log copy:
  `reports\2026-10-08-visualizer-follow-fix\` (rollback:
  `install-visualizer-131.ps1 -Rollback` points LibraryFileName back at
  `..._1.3.0_1.dll`).
- Backup: `backups\2026-10-08\visualizer-follow-fix\` (1.3.0_1 DLLs, registry
  export, pre-change source).
- Known limitations: if Windows ever wedges the *opposite* way (auto-hide
  functioning, work area full, bar stuck revealed) the reveal heuristics can
  still misjudge; pixel forensics of the bar's own edge would settle it, left
  as future work. Flash-reveal (taskbar button attention) and reveal-by-touch
  sliver differences are unchanged from 1.3.0's known-limitations list. Only
  the main taskbar is followed, as before.
