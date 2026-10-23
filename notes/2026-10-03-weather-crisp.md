# Weather text and hover highlight

Applied 2026-10-03. Weather changed from 1.3.0 to 1.3.1. Taskbar text uses grid-fitted pixel rendering and whole-pixel line positions to remove soft edges on the small status label. The existing semibold face and two-line layout remain. The hover highlight is inset by 2 DIP horizontally and 3 DIP vertically. The weather window no longer enforces a minimum height larger than a short taskbar.

The x64 build passed. Installed source and DLL hashes matched. Explorer loaded the new DLL without restarting. Weather settings remained unchanged. The live hover capture at 96 DPI shows the sharper text and highlight inside the styled taskbar. Window bounds were y=4..46 within taskbar y=0..50, with the highlight inset to y=7..43. The forecast card keeps its existing placement outside the taskbar. Other scales, reboot and physical sleep were not tested. No restart is pending.

Published and merged through https://github.com/DavidHiFi/davids-windhawk-mods/pull/6. GitHub main matches the installed source after whitespace normalization. Evidence is in reports/2026-10-03/weather-crisp.

Rollback: run scripts/taskbar-weather/Install-Crisp.ps1 -Rollback with silent elevation. The previous registry, source and DLL are backed up in backups/2026-10-03/weather-crisp. Calling the script without switches audits its version.
