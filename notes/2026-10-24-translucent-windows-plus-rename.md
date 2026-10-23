# Translucent Windows Plus: rename record (2026-10-24)

Thread: e50dff90-4ecb-4c93-82e9-5480de69dae1. PR (draft): https://github.com/DavidHiFi/davids-windhawk-mods/pull/17 (branch translucent-windows-plus, commit 63c18d2).

## Current state (measured at about 6:20 AM)

- Engine id: local@translucent-windows-plus, version 1.8.3, enabled. The mod list shows the name "Translucent Windows Plus" and author "DavidHiFi, Undisputed00x, WinExperiments".
- Registry key local@translucent-windows-plus: LibraryFileName local@translucent-windows-plus_1.8.3_1.dll, 161 settings.
- Old key local@translucent-windows: removed.
- ModsSource: local@translucent-windows-plus.wh.cpp, SHA256 3A9212A1... (matches repo copy and the guard).
- Guard: task TranslucentWindowsGuard Ready, re-pointed to scripts\2026-10-24-translucent-windows-plus-guard.ps1. Suspend marker clear.
- Plus DLL is loaded in explorer.exe pid 29340, not in the taskbar process (Shell_TrayWnd owner). The old DLL showed the same pattern at 6:13 AM.

## What happened (in order)

- 5:56 AM: migration to the Plus id (scripts\2026-10-24-translucent-windows-plus-migrate.ps1 -Action Install).
- 5:59 AM: new guard installed.
- 6:08 AM: Explorer restarted. Plus DLL loaded in one of two Explorer processes; the taskbar process had none.
- 6:10 to 6:13 AM: rolled back to the old id (migrate -Action Rollback stopped partway; finished by scripts\2026-10-24-translucent-windows-plus-rollback-finish.ps1). Explorer restarted at 6:13 AM.
- 6:15 to 6:18 AM: migration re-run with the in-place DLL kept (the 5:56 DLL was mapped and could not be overwritten). Guard re-installed.

## Gaps and things to know

- Desktop lock: coop reports desktop is not declared in .agent-coop.json, so the desktop lock did not take. Both Explorer restarts ran without it. Declare desktop on the board or stop running Explorer restarts without a lock.
- Taskbar process gap: Windows loads the mod into some Explorer processes and not the taskbar process. This is the likely source of "some windows not translucent". Measured at 6:13 AM. Not fixed.
- Preview image is not captured (media\previews\translucent-windows-plus.png). The desktop lock is held by another thread, and the one capture taken shows another mod's window and drive names, so it is not used.
- Live FlyoutsEffects is 0, the repo snapshot says 1. The drift predates this change (pre-migration export also had 0). Snapshot left unchanged.
- The engine-restore run from 10-22 is not active (tasks disabled, no status file). Its tier plan still names the old id; it needs a refresh before anyone resumes it.
- Catalog copy of upstream 1.8.2 removed from the repo (git history keeps it).

## Rollback

- Old id: scripts\2026-10-24-translucent-windows-plus-migrate.ps1 -Action Rollback, then scripts\2026-10-24-translucent-windows-plus-rollback-finish.ps1 if it stops partway. Backups: backups\2026-10-24-translucent-windows-plus\.
- Repo: close PR 17 and delete branch translucent-windows-plus.
