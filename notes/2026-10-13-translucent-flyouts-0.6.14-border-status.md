# Translucent Flyouts 0.6.14: Mocha tint done, Mocha blue border not showing

2026-10-13, thread 912ca616.

## Working (verified by pixel samples in `2026-10-13-flyout-fix\screen.png`)

- Fill: Catppuccin Mocha navy tint. The menu fill samples `#1F1F2E` to `#272839`, and the blur is still on.
- Window region: 24 px rounded corners on the main menu and the submenu.
- Live: `local@translucent-flyouts_0.6.14_1.dll`, loaded in Explorer pid 31200 after a restart.

## Not working

- The outline samples as neutral `#202020` on the left, top, and right edges. The Mocha blue
  border value (`0xFF89B4FA`) is stored in `menu.darkModeBorderColor`, `menu.lightModeBorderColor`,
  and the global keys, but it never reaches the screen.
- A red test (`0xFFFF0000`) showed a red border once, on the 0.6.13_1 DLL. It has not shown since.
- 0.6.14 redraws the outline after the background fill. The edge is still `#202020`.
- An Explorer restart (pre-approved) did not change the edge colour.

## Likely causes (not confirmed)

- The border may not be drawn through the `MENU_POPUPBORDERS` path at all. Then the
  `HandlePopupMenuNonClientBorderColors` `FrameRect` never runs, and the `#202020` edge is the
  default frame.
- `ApplyBorderEffect` sets `DWMWA_BORDER_COLOR`. The probe reads `0xFFFFFFFF` (default) on these
  menus, so that DWM call may not take effect for them either.

## Next step (needs a decision)

Switch the outline to the DWM border colour and read it back with `DwmGetWindowAttribute` to confirm it
applied. This is one build and one install. Rollback: point `LibraryFileName` back at `_0.6.13_1.dll`
with `scripts\2026-10-13-translucent-flyouts-0.6.13.ps1 -Rollback`.

## Settings currently live

- `menu.darkModeBorderColor` and `menu.lightModeBorderColor`: `0xFF89B4FA`. Global keys: same.
- `menu.darkModeGradientColor` and `menu.lightModeGradientColor`: `0x991E1E2E`. Global keys: same.
- `global.enableDropShadow=0`, `global.enableThemeColorization=0`, `menu.noSystemDropShadow=0`.
