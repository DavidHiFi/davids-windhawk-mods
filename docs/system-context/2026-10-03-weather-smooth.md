# Smooth weather text

Applied 2026-10-03. Weather changed from 1.3.1 to 1.3.2. The pixel-only rendering in 1.3.1 made small letters jagged. The taskbar now uses grayscale antialiasing with grid fitting and GDI+ text contrast 8. The semibold font and whole-pixel line positions remain. The stacked layout and inset hover highlight remain.

The x64 Windhawk 1.7.3 build passed. Installed source and DLL hashes matched; all weather settings were preserved. Explorer loaded the new DLL without restarting. A live 96-DPI capture confirms smoother letter edges. Other scales, reboot and physical sleep were not tested. No restart is pending.

Published and merged through https://github.com/DavidHiFi/davids-windhawk-mods/pull/8. GitHub main matches installed source after whitespace normalization. Evidence is in reports/2026-10-03/weather-smooth.

Rollback: run scripts/taskbar-weather/Install-Smooth.ps1 -Rollback with silent elevation. Previous source, registry and DLL are in backups/2026-10-03/weather-smooth. Calling the script without switches audits its installed version.
