# Taskbar AI Quota Bars Plus (2026-10-13)

Continuation of the interrupted morning thread; finished, installed, and verified.

## What shipped

- **Rename**: `local@taskbar-ai-quota-opencode` 1.7.0.0 → `local@taskbar-ai-quota-plus`
  1.8.0.0, "Taskbar AI Quota Bars Plus". Old mod disabled, not removed.
- **True window labels**: bars/tooltips show the window the provider actually reported
  (`5h`, `7d`, `3h`, `30d`, `m`). The free ChatGPT plan's primary window is **30 days** —
  the old static "5h" label was wrong; confirmed live: `OAI 30d`.
- **Grok**: weekly period renders as `7d` (was `wk`).
- **Antigravity**: last-known snapshot cached in mod storage
  (`antigravity_last_known_v1`), replayed clearly-stale while no session is live, with a
  15s re-poll while stale (60s fresh). AGi now renders `5h` + `7d` bars.
- **Compact stack**: in Stacked layout, accounts showing exactly one window share one
  vertical column (drift → 2s-debounced rebuild). Live: Grok + OAI in one column.

## Install path

`windhawk-cli mod install --file <src> --disabled` (compiles locally) → `reg copy` the
old `ModsWritable` key to the new id (carries accounts + DPAPI tokens) → disable old →
enable new → bump `SettingsChangeTime` on both. Script: `2026-10-13-ai-quota-plus\install.ps1`.

The first elevated run failed on a PS 5.1 trap: windhawk-cli prints progress on stderr,
which becomes a terminating error under `ErrorActionPreference=Stop`. Native calls go
through a temp-Continue helper now (also: don't Start-Transcript and Tee-Object the same
file).

One compile fix: the morning thread's label code in `UpdateQuotaUi` used
`showBarLabels`/`percentFontSize` without reading them from settings.

## Verification

Taskbar screenshot after enable: Grok 7d 0% stacked over OAI 30d 100%; AGi 5h/7d with
data; CC 1, CC 2 (gray, unpaid — expected), Go all migrated. No double render. Evidence:
`2026-10-13-ai-quota-plus\mod-zoom.png`.

## Open items

- `agent-coop` is broken on this machine (ACL denies its state dir) — board unavailable.
- Sync the new source into `davids-windhawk-mods` when that repo is free (another thread
  was working in it).
- Old mod left disabled for rollback; remove it once the user is happy.
