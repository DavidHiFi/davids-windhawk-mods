# Bigger thermometer icons for CPU/GPU temps (2026-11-09, 3:28 pm)

Mod: `local@taskbar-system-info-weather` 1.4.23 -> 1.4.24.
Change: new `kTempIconScale = 1.35`. In `ApplyStackedGeometry` the two icon runs get
`FontSize(stackedFontSize * 1.35)`, and the temperature label column widens by the extra icon width,
so the CPU/GPU text does not shift into the value column. Old: icon at the label size.
Work: `work\2026-11-09-temp-icon-size\` (patch.py, src old/new, install.ps1 family batch, no Explorer restart).
Backups: `backups\2026-11-09-temp-icon-size\` (original source, registry export, cli.log, installed.json).
Verified: `reports\2026-11-09-temp-icon-size\stats-zoom.png`. Both icons are larger, not clipped,
same colours, shell PID unchanged (32732).
Rollback: run `work\2026-11-09-temp-icon-size\install.ps1 -Action Rollback` elevated.
