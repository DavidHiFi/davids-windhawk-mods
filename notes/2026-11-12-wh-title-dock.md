# Windhawk window title dock (Enhanced Styler 2.2.5)

Date: 2026-11-12. Thread: 1a27061b. Owner: "windhawk is missing the dock" (screenshot of the
Windhawk window title with no dock).

## Why it was missing
The Windhawk window (windhawk-ui.exe, class WindhawkTauriMainUI) has no DWM-drawn title.
Enhanced Styler folds the caption into the client (WM_NCCALCSIZE top = frame top) and paints
the icon and title itself in `PaintCaption`. Seamless Title Bars draws its dock inside DWM's own
title drawing, so it never reaches this window.

## Change
- `work\2026-11-12-wh-title-dock\patch.py` turns live 2.2.4 (sha256 d5d89e11…00ff) plus
  `dock-block.cpp` into the staged 2.2.5; `patch.py --compile` compiles it offline (exit 0).
- `PaintCaption` rasterises the dock into the buffered-paint pixels before the text and icon:
  rounded rect, fill, top glass shine, edge grey at rest and a blue to mauve gradient on hover
  (150 ms ease-out). Every value is read from Seamless Title Bars' own settings (registry,
  refreshed at most once a second), so both docks always match. No dock when that mod is off,
  removed, or its dock switch is off.
- Title font: the same family and weight as Seamless Title Bars (FiraCode Nerd Font Medium; GDI
  lists it as "FiraCode Nerd Font Med", which is tried first). Windows caption font otherwise.
- Right-click on the dock: the styler reports its dock in `Local\SeamlessTitleBarsHotDock`
  the way DWM does, so Seamless Title Bars 1.2's tool opens the same dock menu. Without 1.2 the
  window menu opens as before.

## Rollback
Reinstall the backup copy Install-StagedMod made (`backups\settings-material\
local@windhawk-enhanced-styler-<stamp>.wh.cpp`, also `ModsSource\...wh.cpp.bak-<stamp>`) with
`windhawk-cli mod install --file <copy>`. No settings were changed.

## Verification (2026-11-14, 4:15 pm)
- 2.2.5 installed and enabled; since replaced by 2.2.6 from another thread (description wrap), which keeps this dock code.
- Offline compile exit 0 (above).
- Not proved: no capture of the Windhawk window's dock was taken in this thread. Check it next time the window is open.
