# Translucent Flyouts 0.6.13: clean menu borders, rounded corners, submenus match

2026-10-13, thread 912ca616. Supersedes the 0.6.10 notes for the menu look.

## Code changes (src\)

- `30-engine.inc`, `DrawThemeBackgroundHook`, MENU_POPUPBORDERS: removed the full-rect BLACKNESS
  fill. The border part was filled black over its whole rect, which drew the thick dark band.
  Only the 1 px outline (`HandlePopupMenuNonClientBorderColors`) is drawn now.
- `kMenuRegionRadius` 20 -> 24. One rounded region clips the outline and the fill together.
- `BeginPaint`: for menus, `EnsureOtherMenuWindows` brings every other menu window on the thread
  up to date. A buffered paint has no window DC, so the wrong menu could get the state. The
  submenu then never got its effects, which made it black.
- `EnsureOtherMenuProc` no longer requires the menu to be visible. A submenu that was not yet
  visible at its first paint was being skipped, and it never got its region.
- Version 0.6.13.

## Installed (live, no Windhawk restart)

- `LibraryFileName=local@translucent-flyouts_0.6.13_1.dll`, `Version=0.6.13`. Hashes verified.
  Explorer pid 26112 has the 0.6.13 DLL loaded.
- Build: `Windhawk\translucency-flyouts\build-0.6.13\`. Log: `reports\2026-10-13\translucent-flyouts-build-0.6.13.log`.
- Install script: `scripts\2026-10-13-translucent-flyouts-0.6.13.ps1` (`-Audit`, `-Install`, `-Rollback`).

## Verified (live desktop menu, `2026-10-13-flyout-fix\probe-v3.ps1`)

- Main menu and submenu both have a window region, and both have the same translucent grey fill.
- `screen.png`: thin outline on both menus. No thick dark band, no black submenu.
- `m2-TL.png` (8x): smooth arc, thin outline, fill follows the curve.

## Settings (registry, live)

- `global.enableDropShadow=0` and `global.enableThemeColorization=0`. Both are global, so
  tooltips and dropdowns are affected too. Not checked yet.
- `menu.disabled=use_global`, `menu.noSystemDropShadow=0`.
- `custom-corner-radius\Settings\smallRadius=16` (test value 8 was restored).

## Rollback

To 0.6.12 (the build just before this one):

    H:\System Configuration\scripts\Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-13-translucent-flyouts-0.6.13.ps1" -ArgumentList "-Rollback"

To the settings: set `global.enableDropShadow` and `global.enableThemeColorization` back to 1.
Pre-experiment values are in `backups\2026-10-13\translucent-flyouts-corners\`.

## Still open

- Tooltips and dropdowns: not checked after the global settings change.
- The 0.6.13 install script's header comment still says "20 px". The code uses 24.
