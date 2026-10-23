# Weather widget doubled on the taskbar

Applied 2026-10-05. Independent Taskbar Weather went from 1.4.0 to 1.4.1.

Cause: the mod targets every `explorer.exe`. Folder windows were running in eight separate explorer processes. Each process found the shell's `Shell_TrayWnd` and attached its own weather window to it, so eight copies drew on top of each other.

Fix: a new `OwnTaskbar()` helper returns the taskbar only when the current process owns it. Window creation, layout and card placement all go through it. The stats mod already had the same check.

Verified: 9 explorer processes load the 1.4.1 DLL, and only one `WindhawkIndependentWeather` child exists, owned by shell PID 36328. Screenshot: reports/2026-10-05-weather-single-process.png. Settings unchanged.

Backup and rollback: backups in `H:\System Configuration\backups\2026-10-05\weather-single-process`. Run `scripts/taskbar-weather/Install-SingleProcess.ps1 -Rollback` elevated. Not yet published to the public repo.
