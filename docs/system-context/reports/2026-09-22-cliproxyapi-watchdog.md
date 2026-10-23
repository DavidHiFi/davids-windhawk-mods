# CLIProxyAPI keep-alive watchdog — 2026-09-22

## Problem (observed)

`cli-proxy-api.exe` (CLIProxyAPI v7.2.156, `ANTHROPIC_BASE_URL=http://127.0.0.1:8317`) can die while apps are restarted (user was tinkering with Windhawk). The only scheduled task, `CLIProxyAPI`, had a **Logon trigger only, no repetition**, so once dead it stayed dead until next logon — a T3 Code V2 nightly orchestration thread failed as a result.

- Exe: `C:\Users\localuser\AppData\Local\CLIProxyAPI\cli-proxy-api.exe`
- Config: `C:\Users\localuser\AppData\Local\CLIProxyAPI\config.yaml` (port **8317**)
- Health signal = TCP 127.0.0.1:8317 listening (port 8080 belongs to steamwebhelper — ignore).

## Change applied

| Item | Before | After |
|---|---|---|
| Watchdog script | none | `scripts\Watch-CLIProxyAPI.ps1` (audit + heal; checks port 8317, restarts hidden, 30 s poll, logs) |
| Hidden launcher | none | `C:\ProgramData\CLIProxyAPI\Watch-CLIProxyAPI-Hidden.vbs` (wscript, window style 0 — no console flash) |
| Scheduled task | `CLIProxyAPI` logon-only, action `Start-CLIProxyAPI.cmd` | **New** task `CLIProxyAPI-Watchdog`: localuser, triggers = **Logon + every 1 min**, action `wscript.exe` → hidden VBS, Hidden, ExecutionTimeLimit 0, MultipleInstances IgnoreNew |
| Old task | `CLIProxyAPI` | **left unchanged** (belt-and-suspenders at logon; both paths no-op when process already healthy) |

Log: `C:\ProgramData\CLIProxyAPI\watchdog.log` (healthy runs do not log; only starts/restarts/heals/errors).

## Test evidence (kill-test via production path)

1. `Stop-Process -Name cli-proxy-api -Force` → port 8317 closed.
2. `Start-ScheduledTask CLIProxyAPI-Watchdog` → log:
   - `14:26:41 port 8317 closed (process missing) - starting cli-proxy-api`
   - `14:26:44 heal succeeded - port 8317 listening` (~6 s)
3. New process pid 50812, same exe path; `-Audit` → **HEALTHY**.
4. Task LastRunTime 14:27:01, LastTaskResult **0**, NextRunTime 14:28:00 (1-min repetition firing).

## Backups (rollback)

- `backups\2026-09-22-cliproxyapi\CLIProxyAPI.before-watchdog.xml` — original logon-only task
- `backups\2026-09-22-cliproxyapi\CLIProxyAPI.logon-only.before-watchdog.xml` — second export of same
- `backups\2026-09-22-cliproxyapi\CLIProxyAPI-Watchdog.after-create.xml` — new task as registered

Undo: `Unregister-ScheduledTask -TaskName "CLIProxyAPI-Watchdog" -Confirm:$false` (old task and Start script untouched).

## Notes / limits

- Repetition duration set to 365 days (`TimeSpan.MaxValue` rejected as out-of-range ISO duration); re-register or extend after 2027-09-22, or rely on the logon trigger.
- Watchdog starts the proxy with `-WindowStyle Hidden` only — never touches the protected audio/comms chain.
- No git commit made (workspace rule: only on explicit request).
