# Translucent Flyouts 0.6.10: menu corners (main menus fixed, submenu fill open)

2026-10-13, thread 912ca616. Continues `2026-10-13-translucent-flyouts-corner-status.md`.

## Change (src\30-engine.inc, src\00-foundation.inc)

- `kMenuRegionRadius` 16 -> 20. A 16 px region trims only the outermost corner pixels, so the
  fill's square corner (about 5 px in from the outline) stayed inside the arc. At 20 px the arc
  cuts that corner, so the fill follows the outline.
- `@version` 0.6.9 -> 0.6.10.
- Not changed: the paint hooks (BORDERS and BACKGROUND BLACKNESS fills). The 5 px dark band is
  still unexplained.

## Installed (live, no Windhawk restart)

- `LibraryFileName=local@translucent-flyouts_0.6.10_1.dll`, `Version=0.6.10`, `Include=*`.
  Exclude unchanged: `discord*.exe|Voicemeeter*.exe|Matrix*.exe|Stream Deck*.exe|dwm.exe`.
- Build: `Windhawk\translucency-flyouts\build-0.6.10\` (x64 and x86, sha256 in
  `reports\2026-10-13\translucent-flyouts-build-0.6.10.log`). Built against engine 2.0.0_1.
- Install script: `scripts\2026-10-13-translucent-flyouts-0.6.10.ps1` (`-Audit`, `-Install`,
  `-Rollback`). Verified: hashes match. Explorer pid 26112 has `local@translucent-flyouts_0.6.10_1.dll`
  loaded.
- Receipts and backups: `backups\2026-10-13\translucent-flyouts-corners\` (registry export of
  the 0.6.9 key, `local@translucent-flyouts.wh.cpp.0.6.9`, install receipt).

## Verified (live desktop menu, `2026-10-13-flyout-fix\probe-v3.ps1`)

- Main menu 321x597: region complex. All four corners (`m1-TL/TR/BL/BR.png`) show the fill
  following the arc. The 0.6.9 crops (`before-0.6.9-m1-*.png`) show a square fill corner.

## Not fixed: submenu fill

- The submenu (hover View) gets a rounded outline from DWM (ROUNDSMALL, 16 px through
  `custom-corner-radius`), and its black fill is clipped to that outline. Its fill is solid
  black, not the translucent fill of the main menu, and it has no window region.
- Likely cause (from source, not yet confirmed): `ResolveFlyoutWindow` falls back to
  `FindFlyoutWindowOnCurrentThread`, which returns the first menu window on the thread. That can
  be the main menu, so submenu paints never reach the submenu's own state.
- Not yet checked: whether 0.6.9 also shows the black submenu. Rollback is one command, below.

## Rollback

    H:\System Configuration\scripts\Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-13-translucent-flyouts-0.6.10.ps1" -ArgumentList "-Rollback"

Points `LibraryFileName` back to `_0.6.9_1.dll`, restores the 0.6.9 source, bumps `SettingsChangeTime`.
