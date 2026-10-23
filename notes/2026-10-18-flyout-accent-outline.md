# Translucent Flyouts: menu accent outline (2026-10-18)

## Symptom
The accent outline on menus (the window system menu, the desktop menu) showed straight
blue stubs that stopped before the rounded corners, with no outline on the corners, and on
some menus a second line about 3 px inside the top and left edges.

## Root cause (measured)
- The menu window has a 24 px rounded window region (`ApplyMenuWindowRegion`). Anything drawn
  outside the arc is clipped.
- The accent frame was a square `FrameRect` (`HandlePopupMenuNonClientBorderColors`). The
  region clipped it into straight stubs. The stubs end where the arc crosses them, which is
  the pattern measured on the 0.6.34 capture (top stub starts at x 13, y 3; left stub at
  x 3, y 13; both sit on a 24 px arc).
- The band paints (`HandleMenuDrawThemeBackground`) also re-framed the outline in a DC that
  is offset about 3 px. That copy showed as the inner line on the top and left only, because
  its right and bottom sides fall outside the window.
- The DWM border (`DWMWA_BORDER_COLOR`) was set on every pass too, so a rounded menu had a
  third drawer.

## What changed (0.6.35 to 0.6.39)
- 0.6.35: no change in behaviour yet (install and probe only).
- 0.6.36: a rounded menu never gets the square frame. It waits for its region.
- 0.6.37: no DWM border on a rounded menu (`DWMWA_COLOR_NONE`).
- 0.6.38: the rounded stroke maps the window origin through `GetViewportOrgEx`.
- 0.6.39: the band re-frame is removed, so only the POPUPBORDERS paint strokes the outline.
  This removed the inner copy.
- Source: `Windhawk\translucency-flyouts\src\30-engine.inc` and `00-foundation.inc`.
  Backup before the change: `backups\2026-10-18\translucent-flyouts-0.6.35-pre\`.

## Verification
- Native test menu (`reports\2026-10-18-flyout-border\MenuTest.exe`, probe
  `probe-menu-0639` run as `test-0639`): accent on all four straight edges (50/50 and 68/68
  samples), arcs 23/23, 23/23, 19/23, 23/23. No inner copy at mid-height.
- Crops: `test-0639-view-2x.png`, `test-0639-TL-8x.png`, `test-0639-BR-8x.png`.
- Shell: `explorer.exe` restarted and loaded `local@translucent-flyouts_0.6.39_1.dll`
  (module list, read back after the restart).
- Not verified: the real desktop context menu. The desktop is covered by user windows, and
  the probe must not click into them (see the 2026-10-18 mistake below). Submenus and
  non-rounded menus were not measured.

## Mistake during this work
The 0.6.35 probe clicked at two desktop points that were inside System Informer, not the
desktop. No menus opened, so the probe measured nothing. Those clicks may have changed a
selection in System Informer. The later probe does not click.

## Rollback
- One step: `scripts\2026-10-18-translucent-flyouts-0.6.39.ps1 -Rollback` points
  `LibraryFileName` at the 0.6.38 DLL and bumps the marker. Run it elevated through
  `H:\System Configuration\scripts\Invoke-Elevated.ps1`, under
  `coop lock windhawk-engine`.
- Original state: 0.6.33 (`backups\2026-10-18\translucent-flyouts-0.6.34\`).
- Explorer keeps the DLL it loaded until its next restart.

## Open items
- Corner radius is a code constant, `kMenuRegionRadius = 24`. Windows menus are closer to
  8 px. If the rounding still looks off, change that one constant.
- Non-rounded menus (cornerType "do not round") still use the square frame. Their outline
  was not re-measured after the band re-frame removal, so check them before relying on it.
