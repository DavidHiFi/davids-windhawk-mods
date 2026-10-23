# 2026-10-10: Taskbar Audio Visualizer 1.3.2 - borderless games hide the strip even after an alt-tab away

## The complaint

A windowed borderless game was up on the taskbar's monitor. The user alt-tabbed
to a window on another monitor. Windows kept the taskbar hidden (it stays
hidden for as long as a fullscreen-style window is *visible* on the monitor,
foreground or not), but the visualizer strip stayed up - drawn over the game
it had just been told to hide from.

## Why all three hide paths went blind at once (measured live, run 1)

- `IsFullscreenOrGameActive()` is **foreground-only** and bails at the monitor
  check when the foreground window is on another monitor - the game is
  invisible to it.
- `pauseWhenObscured` counts **only WS_EX_TOPMOST** coverers (the 1.3.1 fix
  that stops maximized windows from hiding the strip); a borderless game is
  not topmost, so it reads 0% covered.
- The follow model keys on the work-area reservation; a borderless game does
  not lift the reservation (`reservation: top=50` measured during the broken
  state), so the bar looks like a permanent resident and the strip never
  follows it away.

## The fix (revision 1.3.2)

- `IsTaskbarMonitorCoveredByAnyApp()` - any real application window whose rect
  covers >=99% of the taskbar's monitor. Same proven filter set as the
  occlusion check (visible, root-owned, non-tool, non-transparent,
  non-shell-class, **uncloaked**, non-child, own PID excluded). Maximized
  windows in resident mode top out at ~96.5% and cannot trigger it. The cloak
  filter is what keeps "Windows Input Experience" (2560x1440, cloaked,
  permanent) from hiding the strip at all times - dropping any filter here
  would be the random-hide bug by another route.
- `IsFullscreenPauseConditionActive()` - one shared predicate: the foreground
  path stays immediate; the monitor-cover path needs **two agreeing
  evaluations** before it may hide anything on its own, the same visible-bias
  the follow model uses. All five call sites now use it: the fullscreen
  watcher, the overlay self-heal gate, the media repaint gate, the startup
  pause and the settings-change pause - so the three consumers can never
  disagree.

## Deployment on Windhawk 2.0

The engine now compiles ModsSource into timestamp-suffixed DLLs
(`..._1.3.1_359131.dll` was its own build). A SettingsChangeTime bump alone
did NOT recompile or swap the DLL. The path that works under 2.0 (proven on
Oct 8 with 1.3.1_4, and again today): place the manually built DLLs in
`Engine\Mods\{64,32}`, point `LibraryFileName` at them, bump. The tool
process restarts onto the new DLL on the next disable/enable cycle.

- Build: report\build\ (clang++ against `Engine\2.0.0\windhawk.lib`; the
  1.3.1-era `1.7.3_2` path no longer has a .lib).
- Live: pid 3068 with `1.3.2_1.dll` in its loaded modules
  (deploy-132-result.json).

## Verification (all measured, evidence in report\evidence\)

- Borderless cover window 2560x1440, non-topmost, titled:
  `Pausing visualizer: fullscreen, hiding strip` within ~250 ms of the second
  confirming tick; `paused=1` steady the whole time it was up; the occlusion
  check read `covered=0%` throughout (correct - the new path did the hiding,
  the topmost-only check correctly ignored a non-topmost window).
- Cover removed: `Resuming visualizer: visible again` on the next tick.
- No stray pause lines anywhere else in the diagnostic log.
- strip-before.png / strip-after.png: strip seated before and after.

## Traps worth remembering (machine-gotchas material)

- **This session's file sandbox**: the harness `write` tool can create
  directories that the session's own Low-integrity PowerShell cannot write
  to (no user ACE, no integrity label). Any directory PowerShell must write
  into (build outputs, elevated-run logs) has to be created by PowerShell
  itself. Diagnosed with the sandbox-ACL skill; report in
  `acl-recovery\acl-report-489752cb16ea4f8492676244ac24882f.jsonl`.
- `reports\2026-10-08-visualizer-borderless-hide\` is an abandoned artifact of
  that trap (its `build` dir is unwritable to the confined session and cannot
  be deleted by it). Everything real lives in
  `reports\2026-10-08-visualizer-borderless-cover\`.
- `Get-CimInstance`, `tasklist` and `Get-Process windhawk*` are all denied or
  blind from the confined session; WMI works elevated. FindWindow by exact
  class from the confined session returned 0 for a window that provably
  existed - the reliable mod-liveness probe here is the mod's own
  diagnostic.log (`diagnostics.enabled=1` + bump, then read the file).

## Records

- Report + receipt + install/rollback + build:
  `reports\2026-10-08-visualizer-borderless-cover\`.
- Backup: `backups\2026-10-08\visualizer-borderless-cover\` (reg export,
  1.3.1_359131 DLLs, pre-change source).
- Diagnostics enabled for the test session and turned back off
  (`diagnostics.enabled=0`), SettingsChangeTime bumped.
