# Windhawk Styler 1.3.1 — native title bar shows one uniform acrylic sheet

Installed revision 1 (`local@windhawk-styler_1.3.1_1.dll`) and published
commit `2f64116` to DavidHiFi/davids-windhawk-mods main.

## The defect the user saw

With the native title bar on, the DWM caption strip showed the raw system
acrylic while the page body showed acrylic plus the background veil
(`rgba(30,30,46,0.5)`). Measured this morning: strip (17,17,27) vs body
(29,29,42) — a visibly darker band across the top of the window. The page
can never paint into the non-client caption area, so no veil change on the
body side could ever match the strip; the only uniform state is no veil.

## The fix

With the native title bar enabled, the page no longer paints the veil at
all: `html` and `--app-background-color` go transparent (or solid
background color when blur is off, matching the solid caption color), and
the workbench titlebar/editor rules follow. The window is then one DWM
acrylic sheet from edge to edge, caption included — the same mechanism as
every native acrylic app. `DWMWA_COLOR_NONE` on the caption (already in
1.3.0 rev 5) keeps the strip on the shared backdrop.

Custom title bar mode is untouched: veil intact, same look as before.

## Verification (live, elevated captures in reports/2026-10-07-native-fix)

- Native mode: strip (17,17,27) = body background (17,17,27) — pixel
  identical, no band (`fix-native-full.png`, `before-after-top-compare.png`).
- Native caption: themed pastel window buttons from the user's Windows
  theme, drawn by Windows, on the same acrylic (`fix-native-full-titlebar-crop.png`).
- Custom mode: unchanged (veil (28,30) range, frameless, same glyphs)
  (`fix-custom-full.png`, `cmp-custom-overnight-tr.png` vs
  `cmp-custom-today-tr.png`).
- Final state left on the user's own setting: nativeTitleBar=1, blur
  acrylic, backgroundOpacity 50. Window reads BACKDROP=3, CORNER=2.

## Install notes

- The install script's file checks raced the fresh tool's ApplyFiles and
  read clean files; the tool finished a second later. Files verified
  patched afterwards (main.js inject, workbench css marker, index.html
  transparent rule all present).
- `DwmGetWindowAttribute(35)` reports 0x00000000 on the live window even
  though the strip visually shows the backdrop; do not use that read as a
  pass/fail signal, use the pixel scan.

## Files

- Source: `work/windhawk-styler/v3/windhawk-styler.wh.cpp` (synced to fork)
- Builds: `work/windhawk-styler/v3/local@windhawk-styler_1.3.1_1_{64,32}.dll`
- Install/verify: `work/windhawk-styler/v3/elev/install-131-native-fix.ps1`
- Receipt: `reports/2026-10-07-native-fix/receipt.json`
- Backup: `backups/2026-10-07/styler-131/`
- Rollback: point `LibraryFileName` back to `local@windhawk-styler_1.3.0_5.dll`
  and bump `SettingsChangeTime` (old DLLs still in `Engine\Mods\{64,32}`).
