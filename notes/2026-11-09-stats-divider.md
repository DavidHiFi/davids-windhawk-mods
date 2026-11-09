# 2026-11-09: second divider in the taskbar stats widget

Mod: `local@taskbar-system-info-weather` (Taskbar System Info Plus) 1.4.21 -> 1.4.22.
Work: `work\2026-11-09-stats-divider\` (patch.py, src\old/new.wh.cpp, install.ps1, cap.ps1).
Backups: `backups\2026-11-09-stats-divider\` (original source, registry export, cli.log, installed.json).

- New 1 px line between the CPU/GPU block (GHz column) and the RAM/VRAM block, made the same
  way as the existing line before the temperatures: grid column 4 copy plus an island copy that
  runs border to border.
- Old: group gap (column 4) min 7 px, no line. New: min 10 px (same as the section gap), with a line.
- Installed 1:41 pm with the family batch script. Same Explorer, no restart. Compiled 1.4.22.
- Verified 2:38 pm from a screen capture: two full-height lines at x=218 and x=438, both #585B70
  (`reports\2026-11-09-stats-divider\stats-zoom.png`).
- Rollback: run `work\2026-11-09-stats-divider\install.ps1 -Action Rollback` elevated
  (via `Invoke-Elevated.ps1`). It restores the original 1.4.21 source and recompiles it.
