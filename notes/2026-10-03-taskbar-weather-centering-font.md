# Taskbar Weather 1.2.2: vertical centering, font size, icon-text gap

Date: 2026-10-03
Mod: `local@taskbar-weather` (Independent Taskbar Weather, DavidHiFi)
Source: `work\taskbar-weather\taskbar-weather.wh.cpp`
Installed: `C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp`

## What the user asked

Make the widget vertically centered, make its font match the rest of the taskbar,
and tighten the gap between the sun icon and the text a little.

## Observed facts (measured, 96 DPI)

Tray `Shell_TrayWnd` spans y 1390..1440, center y 1415.

| | before (1.2.1) | after (1.2.2) |
|---|---|---|
| widget window rect | (16,1394)..(152,1436) w 136 | (16,1394)..(135,1436) w 119 |
| icon ink rows | 1406..1419, mid 1412.5 (**-2.5 px**) | 1409..1422, mid 1415.5 (**+0.5 px**) |
| text ink rows | 1408..1417, mid 1412.5 (**-2.5 px**) | 1411..1419, mid 1415 (**0 px**) |
| sun-to-text rect gap (code 0) | 18 px | 8 px |
| sun-to-text rect gap (cloud, code 3+) | 8 px | 8 px (unchanged) |
| font size setting | 12 | 11 |
| font family | FiraCode Nerd Font | FiraCode Nerd Font (unchanged) |

Reference: `local@taskbar-system-info-weather` ink mid 1414.5, fontSize 11,
fontFamily FiraCode Nerd Font. Its panel still follows the weather window's
right edge (`WindhawkTaskbarWeatherRightDip` = 135, panel ink starts x 141,
6 px logical gap, unchanged behaviour).

Facts behind the symptoms:

- The window itself was already centered (1394..1436 has center 1415). What
  was off-center was the *content* inside it: GDI+ centers the line box, not
  the ink, so a label with no descenders sits 2.5 px high at 12 px; and
  `DrawIcon` placed a 24x22 box at `height/2-10`, which puts the sun's
  0..14 ink span 3 px above the row center.
- The font family was never the difference. Both mods already had
  `FiraCode Nerd Font`, and GDI+ resolves that family (constructing
  `FontFamily('FiraCode Nerd Font')` succeeds where an invented name throws).
  The visible mismatch was size 12 against the panel's size 11.
- The gap was conditional, not constant: `TextX` was hardcoded to 42, which
  gives 8 px when the cloud fills the 24 px box but 18 px when only the
  14 px sun draws.

## Changes applied

Source (`work\taskbar-weather\taskbar-weather.wh.cpp`):

1. `// @version` 1.2.1 -> 1.2.2.
2. Settings default `fontSize: 12` -> `11`.
3. New layout constants `kIconLeft=10`, `kIconGap=8`, `kTextRightPad=6`,
   `kInkCenterBias=2.5/12` (measured GDI+ line-box bias, scaled with font size).
4. New helpers `IconInkWidth(code)`, `IconInkMid(code)`, `TextX(code)` —
   ink bounds of each condition's glyph, so the row centers the ink and keeps
   one gap for every condition.
5. `Paint`: icon y is now `height/2-IconInkMid(r.code)`; the `DrawString`
   rect starts at `TextX(r.code)` with y offset `fontSize*kInkCenterBias`.
6. `ContentWidth`: `+48` replaced by `+TextX(r.code)+6`, so the widget width
   still matches the drawn content.

Registry (`HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather`):

- `Settings\fontSize` (REG_DWORD) 12 -> 11.
- `Settings\fontFamily` (REG_SZ) re-synced from
  `local@taskbar-system-info-weather`; was already the same value.
- `Version` 1.2.1 -> 1.2.2, `LibraryFileName`
  `local@taskbar-weather_1.2.1_1.dll` -> `local@taskbar-weather_1.2.2_1.dll`,
  `Disabled` 0, `SettingsChangeTime` bumped by `Upgrade.ps1 -Install`.

Script (`scripts\taskbar-weather\Upgrade.ps1`, `-Install` block): now copies the
panel's `fontFamily`, writes `fontSize 11`, and throws if either read-back
mismatches, so the two mods cannot drift again on install.

## Tested

- Build: `scripts\taskbar-weather\Build.ps1` (clang, `-std=c++23`) succeeded.
  DLL hash `DBEDDACB08BD0EAC6E5E1760A91D701DC137E9F37478B5B9A54FAFBF6AC914BC`.
- Install: `upgrade-1.2.2-elevated.cmd` -> `Upgrade.ps1 -Install` (silent
  elevation). Log `reports\2026-10-03\taskbar-weather\upgrade-install.log`:
  "Weather1.2 installed. Town settings and binary independently verified; no
  process restart."
- Read-back: installed DLL hash equals the built hash; ModsSource hash equals
  the work copy hash; `fontSize=11`, `fontFamily=FiraCode Nerd Font`.
- Live: `Audit-Live.ps1` reports the widget present, `Disabled=0`, status
  "17 C | Clear", updates 1, no explorer restart (PID 9576 unchanged).
- Geometry: re-captured tray to
  `reports\2026-10-03\taskbar-weather\tray-after-3x.png` and re-ran
  `work\taskbar-weather\private-measure-ink.ps1`; numbers are in the table
  above. Eyeball check: sun and text now sit on the row center and read at
  the same size as the CPU/GPU labels beside them.

No restart is pending. The hover card keeps its own fixed sizes and was not
touched.

## Rollback

Backup: `backups\2026-10-03\taskbar-weather-1.2.1\`
(`weather-key-before.reg`, `source-before.wh.cpp`,
`local@taskbar-weather_1.2.1_1.dll`, `before.json`).

To undo: copy the backed-up DLL to `C:\ProgramData\Windhawk\Engine\Mods\64\`
(it was also left in place under its own name), restore the backed-up source
over `ModsSource\local@taskbar-weather.wh.cpp`, import
`weather-key-before.reg`, then set
`HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather\SettingsChangeTime`
to the current Unix seconds to force a reload. No explorer restart required.

## Not changed

- `leftOffset=16`, `width=220`, `updateMinutes=10`, location
  (Collie, WA) all untouched.
- `local@taskbar-system-info-weather` untouched.
