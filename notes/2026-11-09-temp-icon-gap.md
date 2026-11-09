# 2026-11-09: space between the CPU and GPU thermometer icons

Mod: `local@taskbar-system-info-weather` 1.4.24 -> 1.4.25 (installed 3:37 pm, same shell PID 32732, no restart).
Work: `work\2026-11-09-temp-icon-gap\` (`patch.py <src> <dst>`, `src\old.wh.cpp`, `src\new.wh.cpp`,
`install.ps1` family batch, `run.ps1`). Backups: `backups\2026-11-09-temp-icon-gap\` (1.4.24 source,
.reg export, active.json, cli.log, installed.json).

- Before: after the 35% size bump (1.4.24) the two glyphs filled y 13-24 and 25-36, touching.
- Change: the icon Run inside each label is now a transparent spacer (widths and text stay put);
  the visible glyph is its own TextBlock in the same cell (`CpuTemperatureIcon`,
  `GpuTemperatureIcon`) with a TranslateTransform of -2 / +2 DIP (`kTempIconNudge`).
  Temperature colours still go to the glyph Run, as before.
- Verified 3:38 pm (`reports\2026-11-09-temp-icon-gap\taskbar.png`, `before-after.png`): glyphs now
  y 11-22 and 27-38, a 4 px gap; text rows unchanged (15-22, 27-34); 1 px clear of the island
  border on each side; CPU glyph still yellow, GPU glyph still lavender.
- Rollback: `work\2026-11-09-temp-icon-gap\install.ps1 -Action Rollback`, elevated, under
  `coop lock windhawk-engine` (restores the 1.4.24 source and recompiles).
- For a smaller gap, set `kTempIconNudge` to 1.0 (2 px gap).

## Follow-up, 3:46 pm to 3:55 pm (owner: gap too big, text closer to the icon)

- 1.4.26 (`patch2.py`): `kTempIconNudge` 2 -> 1 (4 px gap -> 2 px); the hidden glyph Run gets
  `CharacterSpacing(-185)`, pulling CPU/GPU about 3 px toward the icon. Its column width
  subtracted a guessed saving of 4 px, too much: the labels showed as "C...".
- 1.4.27 (`patch3.py`): the column now measures the real label (spaced hidden glyph plus "GPU")
  plus 1 px. Installed 3:53 pm, same shell PID 32732.
- Verified from `reports\2026-11-09-temp-icon-gap\taskbar3.png` / `final-zoom.png`: glyphs y 12-23 and
  26-37 (2 px gap), "CPU" and "GPU" whole, text starts 7 px after the glyph (was 10).
- Rollback: `work\2026-11-09-temp-icon-gap\install3.ps1 -Action Rollback` (back to 1.4.26), then
  `install2.ps1 -Action Rollback` (1.4.25) and `install.ps1 -Action Rollback` (1.4.24), each elevated
  under `coop lock windhawk-engine`.
