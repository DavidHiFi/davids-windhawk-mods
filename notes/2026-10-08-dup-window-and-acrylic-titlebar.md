# 2026-10-08: duplicate window killed + true acrylic title bar (styler 2.0.4)

User ask (verbatim intent): "the duplicate old window is still open, so can you fix
that? also the title bar is still not being blurred like the rest of the window …
just make the title bar acrylic and blurry as well, like the main window."
Two asks only; do not restyle anything else.

## Ask 1: the duplicate old window

- It was the Windhawk 2.0 **mod editor** (VSCodium pid 14012, started 19:48:24
  elevated) left over from the styler-port-2 session, plus 3 windowless orphan
  processes (3884 renderer, 24512 ptyHost, 4884 fileWatcher). All killed
  (`work\dup-window-titlebar\kill-orphans.ps1`, logged cmdlines first); zero
  VSCodium processes remain.
- Why it looked like it "kept coming back": the styler's own relaunch helper
  restarts windhawk-ui in a pair every time the DLL hot-swaps — that is the mod
  working, not a second spawner. Helper log proves it:
  `C:\Users\localuser\AppData\Local\Temp\wh-styler-helper.log` (one RUN per
  restart, `afterstart <pids>`).
- It cannot return unless someone opens the mod editor again.

## Ask 2: acrylic title bar — what was measured on Win11 26200

All claims below are measured on this machine (dxcam desktop-duplication grabs;
PIL/ImageGrab and PrintWindow cannot see acrylic windows; sleep ~0.5 s after a
DWM set before grabbing; measure with the window ACTIVE, DWM washes colors
inactive).

1. `DWMWA_CAPTION_COLOR`: opaque colors render exactly (green/red race test);
   the alpha byte is ignored; the getter fails with E_INVALIDARG while the WCO
   accent is active.
2. **Inactive captions ignore the caption color entirely**: with opaque red
   set and the window deactivated, the strip renders the same constant flat
   (84,84,84) as with COLOR_NONE. Nothing via DWM changes the inactive strip.
3. WCO accent (`ACCENT_ENABLE_ACRYLICBLURBEHIND`) does **not** render behind
   the caption: with caption COLOR_NONE + accent, the strip is a flat dark
   fill (the old 2.0.1 complaint).
4. `DWMWA_SYSTEMBACKDROP_TYPE=3` (DWMSBT_TRANSIENTWINDOW, acrylic) is
   suppressed while a WCO accent policy is active. With the accent removed it
   renders behind the **caption** immediately (strip shows blurred wallpaper),
   and behind the **client** only once `DwmExtendFrameIntoClientArea(-1)` is
   applied.
5. SBT + ExtendFrame survive maximize and restore (measured maximized:
   strip (91,95,113), body-top (77,77,93) — backdrop present).
6. Material difference: the SBT acrylic is brighter/more faithful than the
   legacy accent blur (same wallpaper region: accent ≈ (30,30,30) raw,
   SBT ≈ (142,132,140) raw). The body is therefore somewhat more transparent
   than the 2.0.2 accent look — inherent to the only mechanism that gives the
   caption a real blur.

## Final architecture (styler 2.0.4)

Source of truth: `work\windhawk-styler\tauri20\windhawk-styler.wh.cpp` (2.0.4),
synced to `C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp`
(hash 4F8ED97F…C262A). Deployed DLL
`C:\ProgramData\Windhawk\Engine\Mods\64\local@windhawk-styler_2.0.4_684023.dll`;
mod key verified: Version 2.0.4, Include windhawk-ui.exe, Architecture x86-64.
UI pair after deploy: 19824 + 31484, put sites patched (3), CSS re-pushed.

- `titleBarAcrylic` (new bool setting, default **true**): no WCO accent;
  SBT=3 + ExtendFrame(-1) + caption COLOR_NONE → the strip and the client are
  the same acrylic surface, wallpaper sweeps continuously through both.
- `titleBarAcrylic=false` (fallback): the legacy accent + solid
  `titleBarColor` strip (2.0.2 behavior). `titleBarColor` (#403a45 default) is
  unused while acrylic mode is on.
- `DwmSetWindowAttribute_hook` keeps caption puts at NONE in acrylic mode;
  `ApplyEnumProc` re-applies every cycle in acrylic mode (the failing
  E_INVALIDARG read returns 0 = NONE, which would otherwise look "already
  correct").
- `ClearWindowStack` resets SBT, ExtendFrame margins, caption/text/border and
  the accent on unload.

Known imperfections (accepted): active strip is ~25 rawer/brighter than the
veiled body (same material, soft step); inactive strip is Windows' constant
(84,84,84) vs body (72,72,80).

## Backups / rollback

- `backups\2026-10-08\styler-2.0.2-titlebar-deploy\`: mod-key.reg (2.0.1-era),
  all pre-2.0.2 DLLs, `ModsSource.pre-2.0.2.wh.cpp` (the 2.0.1 source).
- `backups\2026-10-08\styler-2.0.3-acrylic-titlebar\`:
  `local@windhawk-styler_2.0.2_162547.dll` (the 2.0.2 build),
  `ModsSource.pre-2.0.3.wh.cpp` (the 2.0.2 source),
  `mod-key-2.0.2.reg` (key state as of the 2.0.3 deploy).
- Receipt: `scripts\2026-10-08-styler-acrylic-titlebar.ps1`
  (-Audit / -Install / -Rollback). -Rollback restores the 2.0.2 source and
  recompiles; the engine hot-swaps and the helper restarts the UI.

## Work files

`work\dup-window-titlebar\`: accent_probe.py, strip_probe.py, layout_probe.py,
inactive_probe.py, verify_sbt.py, max_test.py, deploy-203.ps1, compile-202.ps1,
kill-orphans.ps1, cdp-check.ps1; screenshots before-titlebar.png (2.0.2 look),
sbt-active.png / sbt-inactive.png (2.0.4 final), max-act.png, inactive-red.png.
