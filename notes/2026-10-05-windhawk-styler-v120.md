# Windhawk Styler 1.2.0

Installed revision 6 (`local@windhawk-styler_1.2.0_6.dll`, source 1.2.0) and published the update to DavidHiFi/davids-windhawk-mods.

## What changed from 1.1.0

- **The title bar mode keeps the blur.** It no longer switches the window to an opaque native frame. The window stays see-through and the window controls are drawn into the blurred title bar.
- **Theme window buttons, matched to the machine's Windows theme.** The controls are drawn as the theme's 16 px round buttons (Catppuccin Mocha): minimize `#f9e2af`, maximize `#a6e3a1`, close `#f38ba8`. On hover the dot darkens (min `#c8b17e`, max `#74b16f`, close `#c45c79`) and a dark tinted glyph appears: a 10x2 rounded bar (`#6f5825`), an 8x8 diagonal expand arrow (`#286523`), an 8x8 X (`#851d3a`). The glyphs are SVG drawings, not codicon font characters, so they are smooth at any size. The maximize control is `window-max-restore`; when maximized it swaps to a restore glyph.
- **No bottom strip.** The old opaque native-frame mode that showed a black box at the bottom is gone.
- **Readable disabled buttons.** `.ant-btn-primary` takes the accent colour only when enabled; disabled buttons use a neutral fill with light text. Text on accent fills picks black or white by luminance.

The geometry and colours were measured from a native window on this machine (regedit): dot diameter 16 px, hover dots and glyph colours sampled per pixel; reference crops are in the reports folder.

## Why the buttons are drawn, not a DWM caption

The bundled VSCodium/Electron (1.74.2 / 19.1.8) cannot combine the DWM title bar with a per-pixel-transparent window. Tests: `transparent:true` + `frame:true` produces an opaque client area (white-behind test), and adding `WS_CAPTION` to the frameless window is ignored because Chromium's custom-frame `WM_NCCALCSIZE` keeps the client full-window. The controls draw the theme's buttons and call the real window actions.

## Verification

- Rest and both hover states match the theme reference (`v120r5-hover-min/max/close.png` vs `regedit-hover*.png`).
- Stripe test with the window verified on top: background blurred and see-through (`v120r3-stripes.png`).
- All four patched files carry the style markers; the tool-mod process is running.
- Disabling the mod restores every file from its `.windhawk-styler.bak`.

## Files

- Source: `work/windhawk-styler/v3/windhawk-styler.wh.cpp`
- Build: `work/windhawk-styler/v3/Build.ps1` (1.2.0 rev 6)
- Install: `work/windhawk-styler/v3/Update.ps1`
- Evidence: `reports/2026-10-05-windhawk-styler-v120`
- Backups: `backups/2026-10-05/windhawk-styler/v120` (plus `.windhawk-styler.bak` originals next to each UI file)
- Audit/rollback: `scripts/2026-10-05-windhawk-styler.ps1 -Audit` / `-Rollback`

## Traps for the next thread

- The mod's tool process only launches when a plain `windhawk.exe` instance loads the mod. After a disable/enable cycle, start `windhawk.exe` once or no tool runs and the files stay unstyled.
- Windhawk resets the mod's `Settings` key when the source file is updated. `Update.ps1` captures the settings before disabling and writes them back before enabling.
- Workbench controls: `div.window-icon.window-minimize`, `div.window-icon.window-max-restore` (codicon class swaps dynamically), `div.window-icon.window-close`, inside `.part.titlebar>.window-controls-container`. The codicon glyphs live on `::before`; the mod hides them and draws dots on `::after` and SVG glyphs on `::before`.

