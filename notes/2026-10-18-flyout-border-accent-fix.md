# Flyout accent border fix (2026-10-18)

Result: rounded menus now draw one continuous accent ring that follows the corners, and the ring
takes its colour from the live Windows accent. Measured with the native menu probe (`MenuTest.exe`)
on translucent-flyouts 0.6.47, Explorer restarted at 4:49 PM and loaded
`local@translucent-flyouts_0.6.47_1.dll` (module list read back).

## Root cause (measured)

- 0.6.42 removed the GDI ring on rounded menus and assumed DWM would draw the ring along the window
  region. It does not: the title-bar menu had no accent at all.
- Restoring the arc stroke alone was not enough. The background band fill (177 by 141 inside a 183
  by 147 menu) paints after the outline on these menus, and it blacks out the corner arcs.
- Diagnostic log (MenuTest process, 0.6.46 diagnostic build): viewport origin, window origin and
  the logical-to-device point at (0, 0) were all (0, 0) on every paint. The outline paints at
  0,0,183,147 and the band at 0,0,177,141. So there is no offset to correct.
- Two approaches were wrong and are recorded so they are not repeated:
  - Re-stroking the ring after each band (0.6.44 to 0.6.46). Items paint from x = 3, and each
    band's ring landed at its own paint rect, which left a second ring inside the window.
  - Flipping the sign of the viewport origin. The origin is zero, so it changed nothing.

## Fix (0.6.47)

- Rounded menus: the DWM border colour is set to none, so DWM adds no second ring.
- Rounded menus: the outline is a 1 px GDI stroke on the region's own arc (the 0.6.39 design).
- Rounded menus: each band fill is clipped to the rounded rect inset 1 px, so a band that paints
  after the outline cannot cover the arc. The outline is drawn once, at the window edge.
- Menu border colour source: live accent. `menu.enableThemeColorization` = `yes`; the dark and
  light accent slots are `system_accent` (Windows `ImmersiveSystemAccent`).
- Source: `Windhawk\translucency-flyouts\src\30-engine.inc` (EnsureWindowState,
  HandlePopupMenuNonClientBorderColors, HandleMenuDrawThemeBackground) and
  `src\00-foundation.inc` (version 0.6.47).

## Evidence

Probe, native menu, 0.6.47 build with the fixed colour:

| Check | Result |
| --- | --- |
| Arcs TL / TR / BR / BL | 23/23, 23/23, 19/23, 23/23 |
| Straight edges | left 50/50, right 50/50, top 68/68, bottom 68/68 |
| Inner ring (left offset 3 at mid-height) | 0 |

This matches the 0.6.39 baseline (`reports\2026-10-18-flyout-border\test-0639-result.txt`).

Probe, live-accent setting (`test-0647-accent-result.txt`): same counts. The ring pixels read
`84B1F9`. The Windows accent swatch (DWM `AccentColor`) is `89B4FA`. The 5-step difference is the
gap between the immersive accent slot and the swatch. It is not visible by eye.

Images (absolute paths):

- Fixed to live accent: `H:\Windhawk Configuration\reports\2026-10-18-flyout-border\test-0647-accent-view-2x.png`
- Corner, fixed build: `H:\Windhawk Configuration\reports\2026-10-18-flyout-border\test-0647-TL-8x.png`
- Before, arc missing (0.6.43): `H:\Windhawk Configuration\reports\2026-10-18-flyout-border\test-0643-TL-8x.png`
- Before, inner ring (0.6.46): `H:\Windhawk Configuration\reports\2026-10-18-flyout-border\test-0646-TL-8x.png`

## Changes made

- Mod source: `src\30-engine.inc`, `src\00-foundation.inc`. Assembled and built as 0.6.43 through
  0.6.47 (`scripts\2026-10-18-translucent-flyouts-0.6.43.ps1` to `-0.6.47.ps1`; each has -Build,
  -Install and -Rollback).
- Installed 0.6.47 elevated under `coop lock windhawk-engine`. Hashes match in `Engine\Mods\64` and `\32`.
- Settings, backed up first to `backups\2026-10-18\translucent-flyouts-0.6.47-menu-accent\mod-key-before-menu-accent.reg`:
  - `menu.enableThemeColorization`: `use_global` to `yes`
  - `menu.darkModeThemeColorizationType`: `start_background` to `system_accent`
  - `menu.lightModeThemeColorizationType`: `start_background` to `system_accent`
- Diagnostic-only: `reports\2026-10-18-flyout-border\instrument-0646.py` and its build output. The
  real source has no logging lines (checked by grep).

## Not verified

- The real desktop and Explorer menus were not opened. The desktop is covered by your windows, and
  the probe must not click into them. The test menu uses the same menu window class and the same
  mod render path, and the mod loads in its process.
- Non-rounded menus (corner setting "do not round") were not measured in this pass.
- A leftover `local@translucent-flyouts_0.6.46-diag_1.dll` (64-bit) is still held open by a process
  that loaded it during the diagnostic run. The engine points at 0.6.47, so it has no effect. It can
  be deleted once that process exits (`reports\2026-10-18-flyout-border\cleanup-diag-0646.ps1`).
- The mod's default for menu colour (`use_global`, fixed colour) is unchanged in the source. A fresh
  install from defaults would show the fixed colour until the setting above is applied.

## Rollback

- Settings: elevated `reg import` of `mod-key-before-menu-accent.reg`, then bump `SettingsChangeTime`.
- Code: point `LibraryFileName` at `local@translucent-flyouts_0.6.42_1.dll` and `Version` at `0.6.42`
  (the state before this session), elevated, bump the marker, restart Explorer. The 0.6.47 script's
  `-Rollback` goes to 0.6.46, which has the inner ring, so use the 0.6.42 route instead.

Previous checkpoint: `notes\2026-10-18-flyout-border-artifacts-status.md` (superseded by this note).
