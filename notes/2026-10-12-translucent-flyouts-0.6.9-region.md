# Translucent Flyouts 0.6.9: rounded window region for menus

2026-10-12, thread ebb8ff41-b11c-4417-9d9d-0a4a69f0a0ec. Follows
`2026-10-12-translucent-flyouts-corners.md` (findings and options).

## Change (src\30-engine.inc, version 0.6.9)

- `ApplyMenuWindowRegion`: for menus whose corner preference is ROUND or
  ROUNDSMALL, set a window region with a 16 px rounded rect the size of the
  window. The region clips the acrylic fill, which DWM does not clip to its
  outline. Cached by size; rebuilt only on resize; cleared when corners are
  sharp. Called from `EnsureWindowState` for menus only.
- Restored the shipped 0.6.8 `HandlePopupMenuNonClientBorderColors`. The prior
  run's rounded-corner branches are gone (draft kept in `backups\...\src-before-0.6.9`).

## Installed (live, no Windhawk restart)

- Mod key: `LibraryFileName=local@translucent-flyouts_0.6.9_1.dll`,
  `Version=0.6.9`, `Include=*`, Exclude unchanged. Both DLLs in
  `Engine\Mods\64` and `\32`. Canonical source in `ModsSource` updated.
- Install script: `scripts\2026-10-12-translucent-flyouts-0.6.9.ps1`
  (`-Audit`, `-Install`, `-Rollback`), run elevated through Invoke-Elevated.
- Receipt: `backups\2026-10-12\translucent-flyouts-corners\receipt-install-0.6.9.json`
  (verified: true). Registry backup of 0.6.8: `local-translucent-flyouts-0.6.8.reg`.

## Verified

- Test window (`FlyoutTestWindow`, menu mode): `local@translucent-flyouts_0.6.9_1.dll`
  is loaded; `GetWindowRgn` on the menu gives a complex region, box 0,0,263,124.
- Corner crops (`reports\2026-10-12-flyout-corners\v096-menu-*.png`): the fill
  follows the arc at top-left and bottom-right; the accent ring still follows
  the rounded outline.
- Not verified: the Explorer context menu from the user's screenshot. Opening
  one needs a right-click on the desktop, which this session does not do.

## Rollback

    H:\System Configuration\scripts\Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-12-translucent-flyouts-0.6.9.ps1" -ArgumentList "-Rollback"

This points `LibraryFileName` back to `_0.6.8_350274.dll`, restores the 0.6.8
source and bumps `SettingsChangeTime`.

## Caveat

The region radius is fixed at 16 px. That matches `custom-corner-radius`
(radius 16, DWM menus at 16). Without that mod, DWM draws ROUND at 8 px, so
the region would cut more than the outline. Making it a setting is the next step
if the mod is ever disabled.
