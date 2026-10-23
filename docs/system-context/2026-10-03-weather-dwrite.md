# Weather text through DirectWrite

Applied 2026-10-03. Weather moved from 1.3.2 to 1.4.0. GDI+ `DrawString` drew the small text thin and jagged on the transparent layered window, and neither the grid-fit nor the antialias hints fixed it. The temperature and conditions now render through a Direct2D DC render target with DirectWrite, using grayscale smoothing and NATURAL_SYMMETRIC rendering. The text uses the real FiraCode Nerd Font SemiBold face (weight 600) and whole-pixel baselines. The icon and hover highlight still render through GDI+. `Build.ps1` now links `-ld2d1 -ldwrite`.

The x64 Windhawk 1.7.3 build passed with no warnings. Explorer 32028 loaded the new DLL without a restart, and settings were preserved. A 96-DPI capture shows the text matching the system info weight. See zoom-weather-smooth.png (before) and zoom-weather-dwrite.png (after) in reports/2026-10-03/weather-dwrite. Other scales, reboot, and sleep were not tested.

Published: PR https://github.com/DavidHiFi/davids-windhawk-mods/pull/9, merged at 37ba4fe. GitHub main matches the installed source. Release: https://github.com/DavidHiFi/davids-windhawk-mods/releases/tag/taskbar-weather-v1.4.0 (source ZIP, not marked Latest, matching the other per-mod releases).

Rollback: run scripts/taskbar-weather/Install-DWrite.ps1 -Rollback elevated. The 1.3.2 source, registry, and DLL are saved in backups/2026-10-03/weather-dwrite.
