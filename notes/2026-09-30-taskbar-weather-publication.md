# Taskbar weather publication — 2026-09-30

Published commit dbe9707730f0e8fd4b5c4ee34b8f2c8130f29256 to main at https://github.com/DavidHiFi/davids-windhawk-mods. Release v1.3.0 includes a source archive. Anonymous source and archive downloads succeeded; downloaded asset SHA256 matches GitHub's digest. Receipt: reports/2026-09-30/taskbar-weather/publication.json.

Weather 1.2.1 and performance companion 1.0.0 are documented under mods/local. Source defaults and public settings have empty coordinates and town. A scan confirmed the saved local town and both coordinate strings are absent from public files. Build-Repo.ps1 strips weather location fields; Apply-WindhawkSettings.ps1 preserves existing location when public fields are empty. GitHub topics include windhawk, taskbar, weather and open-meteo. Upstream monitoring credits and GPL-3.0 are preserved.

Catalog submissions are https://github.com/ramensoftware/windhawk-mods/pull/5834 and https://github.com/ramensoftware/windhawk-mods/pull/5835. Each changes exactly one new source file; both are linked to this T3 thread. AI review was requested on both. Catalog visibility depends on upstream review and merge; submission is not catalog approval. Weather CI passed metadata validation and builds for Windhawk1.6.1,1.7.3,2.0.0-alpha.6. Companion local validation and compilation passed; upstream approval was granted and metadata plus all three compatibility builds also passed. Both submissions remain in the AI review queue.

Locally upgraded weather from1.2.0 to1.2.1 to match publication. The revision adds a setup prompt for missing coordinates and corrects the settings callback signature. Fresh weather and taskbar window verified after installation. No Explorer or global Windhawk restart was issued. Current evidence: reports/2026-09-30/taskbar-weather/publication-live.json. Full reboot and physical sleep remain untested.

Rollback for this revision: scripts/taskbar-weather/Rollback-PublicRevision.ps1 audits by default; -Apply restores the saved1.2.0 registry metadata and source. The old DLL remains installed. Use the silent elevated cmd wrapper. Backup: backups/2026-09-30/taskbar-weather-1.2.1. Earlier whole-feature rollback remains scripts/taskbar-weather/Upgrade.ps1 -Rollback.

Canonical GitHub checkout on main was fast-forwarded to the published commit. The unrelated dirty better-volume-mixer-plus source was preserved and not included. Isolated publication and catalog checkouts remain for review follow-up. Source thread history was retained.
