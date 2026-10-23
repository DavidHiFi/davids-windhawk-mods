# Weather condition no longer cut off

Applied 2026-10-05. Independent Taskbar Weather went from 1.4.1 to 1.4.2.

Cause: `ContentWidth()` truncated the fractional icon offset (`(int)TextX`) before adding it, so the widget came out a fraction of a pixel narrower than its text. DirectWrite then trimmed "Partly cloudy" to "Partly clou…".

Fix: the whole sum is rounded up, with 1 px of slack. The maximum width is now at least 240 DIP, so long conditions fit. The stats panel already positions itself from the weather's published right edge (`WindhawkTaskbarWeatherRightDip`), so it shifts automatically.

Verified by screenshot: reports/2026-10-05-weather-fit.png. Rollback: run `scripts/taskbar-weather/Install-Fit.ps1 -Rollback` elevated. Backup is in `H:\System Configuration\backups\2026-10-05\weather-fit`.
Published to GitHub main as ce92e2a (https://github.com/DavidHiFi/davids-windhawk-mods/commit/ce92e2a).
