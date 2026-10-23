# Antigravity removed from the taskbar quota mod (2026-10-13)

## Result

The Antigravity ("AG") account is removed from `local@taskbar-ai-quota-plus` 1.8.0.0. The
mod reloaded and the taskbar shows Grok 7d, OAI 30d, CC 1, CC 2 (unpaid, gray) and Go. No AG
row and no `!`. Evidence: `2026-10-13-ai-quota-plus\verify-ag-removed.png` and
`verify-ag-removed-zoom.png`.

## Correction to the morning record

`notes/2026-10-13-taskbar-ai-quota-bars-plus.md` said AGi "renders 5h + 7d bars with data". That
was wrong. The `mod-zoom.png` from 3:57 PM shows empty AG bars with no fill and no percentage.
AG never returned data in this build.

## Why AG could not show usage

- AG quota exists only on a local language server. `agy` starts one on random localhost ports
  and shuts it down when the command ends. Measured in
  `~/.gemini/antigravity-cli/log/cli-20261013_161049.log`: started 4:10:49 PM, shut down 4:10:55 PM.
  So the mod can read AG quota only while an `agy` or Antigravity session is running.
- The last-known cache (`antigravity_last_known_v1`) was never written. It is saved only after a
  successful live fetch, and none happened. Antigravity was closed during install.
- With no session and no cache, the row shows "Antigravity not running" plus the stale `!`.

## Cloud route tried and stopped

- `agy` signs in through the Windows keyring entry `gemini:antigravity`.
- `v1internal:retrieveUserQuotaSummary` returns 403 `SUBSCRIPTION_REQUIRED`.
- `v1internal:loadCodeAssist` returns `UNSUPPORTED_CLIENT` for the free tier ("migrate to the
  Antigravity suite") and no `currentTier`.
- Getting past these gates would mean presenting as a different client. That is a licence bypass,
  so it was not pursued.

## What changed

- Backup: `2026-10-13-ai-quota-plus\backup\pre-ag-removal\ModsWritable-quota-plus.reg`.
- `settings_v1` in mod storage: 6 accounts became 5. `settings_v1_len` 1553 became 1397.
  Script: `2026-10-13-ai-quota-plus\scripts-remove-ag.py`.
- Reload: `2026-10-13-ai-quota-plus\reload-quota-plus.ps1`, elevated via
  `H:\System Configuration\scripts\Invoke-Elevated.ps1`. Logs: `2026-10-13-ai-quota-plus\reload-log.txt`
  and `H:\System Configuration\backups\2026-10-13-elevated\log-172611.txt`. Held under the
  `windhawk-engine` lock.

## Left behind

- The AG code is still compiled into 1.8.0.0 but has no account, so it does nothing. Stripping it
  needs a source edit and a rebuild.
- The `probe\` folder holds read-only probes. They read the `agy` keyring token and print no token
  values. Delete the folder if you do not want them kept.

## Rollback

`reg import` the `.reg` backup, then run `reload-quota-plus.ps1`.

## Published to GitHub (2026-10-13)

- Commit `aab3682` on `DavidHiFi/davids-windhawk-mods` `main`: `mods/local/taskbar-ai-quota-plus/`
  (source and README), `media/previews/taskbar-ai-quota-plus.png`, and a new `manifest.json` entry.
  The old `taskbar-ai-quota-opencode` entry is marked disabled. Published from an isolated worktree
  on `origin/main`, so the local `main` (5 unpushed Styler commits from another thread) was not pushed.
- Published source still includes Antigravity support, documented as session-only.
- The installed build still has the old readme sentence "local to this machine" in its Windhawk
  metadata. The source now says "developed in the DavidHiFi repository". Text only; it changes on the
  next rebuild.

## Open decisions

1. `settings/quota-mod-localstorage.json` is tracked on public `main` and holds a non-empty
   `opencodeKey` field on account 0 (9 characters; value not printed). If it is a real OpenCode key,
   rotate it. Then remove the file from `main`. Removing it from history needs a separate decision.
2. The old `mods/local/taskbar-ai-quota-opencode/` folder is still on `main`, disabled in the
   manifest. Remove it?
3. Antigravity support is still in the published source. Strip it from the source and republish?
