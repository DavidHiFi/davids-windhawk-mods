# Tray cluster centered at margin 9 (2026-10-24)

## Result
The right tray cluster and the left side both sit on the bar's center line.

## Measured (fresh capture, read-only)
- Bar ring (pill) rows 5 to 44, center 24.5.
- Left side offset 0 px. Right side offset -0.5 px.
- Band check, right side: clock center 24.5, icons 25, quota dashboard 24.
- Proof: `reports\2026-10-24-tray-go\2026-10-24-tray-centered-margin9.png` (4x crop, red line at 24.5). Shown in the thread as an html_render page and as an attachment.

## Live value
- `windows-11-taskbar-styler`, `controlStyles[63].styles[1]` = `Margin=0,9,0,0`, read back.
- Written elevated at 6:12 AM (`backups\2026-10-24-elevated\log-061208.txt`). Hot reload, no Explorer or engine restart.
- Suspect flags checked and not changed: styler, taskbar-on-top, taskbar-icon-size all Disabled=0.

## Correction to older notes
- The "margin 0 is exact centering" law (2026-10-21) does not hold on the bar as it is now. Measured today: margin 0 sits high, margin 14 sits about 4.5 px low, margin 9 is centered.
- The guard script already expected 9 (since 2026-10-19), so it did not need a change.

## Hardening
- Scheduled task `WindhawkTrayGuard` (registered 6:20 AM, runs as SYSTEM at startup and every 5 minutes). Its last run returned 0 and logged `OK: tray guard values match.` Log: `reports\2026-10-24-tray-go\guard-task.log`.
- The guard writes only when a value drifts. Its drift branch is read-verified only. A scratch-key test was blocked by a path guard and did not run.
- Remove the task: `scripts\tray-guard-task.ps1 -Remove` (elevated).

## Rollback
- Original margin-0 state: `backups\2026-10-24-tray-center\windows-11-taskbar-styler-before-margin14.reg` (elevated `reg import`, then bump `SettingsChangeTime`).
- `reports\2026-10-24-tray-go\styler-before.reg` now holds the margin-14 state, not the original. Do not roll back to it.
