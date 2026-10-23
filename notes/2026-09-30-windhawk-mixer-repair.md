# Better Volume Mixer Plus metadata repair

On 2026-09-30, Windhawk showed an empty Details page and reported that the local mod failed to load. The mixer tool process itself was running.

The source header declared `@id local@better-volume-mixer-plus`. Windhawk 1.7.3 accepts only lowercase letters, digits, and hyphens in `@id`. The `local@` prefix belongs to the installed filename and registry key. Its metadata parser rejected the entire header, so the UI lost the name, description, author, and documentation.

Changed the header to `@id better-volume-mixer-plus` in the installed source, canonical development source, and repository snapshot source. Added an ID check to the existing installer so it rejects this mistake before installation. The repository change remains local and uncommitted.

Verification used the metadata parser extracted directly from the installed Windhawk extension. It reproduced the error before the change and passed afterward for all three source copies. The installer passed the PowerShell syntax check. A live UI check confirmed the Installed Mods entry and Details page show Better Volume Mixer Plus, version 1.0.0, author DavidHiFi, its description, and its README. The page remains open. Evidence is in `reports/2026-09-30/windhawk-mixer-repair/`, including `windhawk-ui.png` and `ui-tree.txt`.

The mixer tool remained PID 12744 with its existing DLL loaded. No DLL, registry setting, audio route, volume, or device changed. Windhawk's engine and the protected audio applications were not restarted. No restart is pending. Audio routing was not retested because this repair changes source metadata only. The earlier fork record contains the user's routing confirmation.

Backups and the timestamped source receipt are in `backups/2026-09-30/windhawk-mixer-repair/`. The installer backup is `backups/2026-09-30/windhawk-mixer-repair-installer-before.ps1`.

To restore the installed and canonical source headers, run `scripts/windhawk-mixer-repair/Repair-Metadata.ps1 -Rollback` elevated. Restore `snapshot-before.wh.cpp` to `H:\Windhawk Configuration\davids-windhawk-mods\mods\local\better-volume-mixer-plus\better-volume-mixer-plus.wh.cpp` and restore the installer backup to `H:\Windhawk Configuration\scripts\2026-09-30-better-volume-mixer-plus-install.ps1` to undo the remaining source changes. Rollback restores the invalid metadata and its UI error.

After the user's reported unexpected shutdown, a read-only check at 2026-09-30T05:44:28.3648522+08:00 confirmed the corrected installed source still passes Windhawk's own metadata parser. The mixer automatically started again as PID 2020. The mod remains enabled, version 1.0.0, with its existing DLL. No further repair or restart was required.
