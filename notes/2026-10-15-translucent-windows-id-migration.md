# 2026-10-15 — translucent-windows: phantom 1.8.2 "update" offer killed by `local@` id migration

## Symptom

Updating the mod 1.8.2 → 1.8.3 worked, then Windhawk's "Review Updates" offered
**1.8.2** as a *new* version, over and over. In parallel the app silently
reinstalled stock builds (the drift guard healed three more times that morning:
08:30:06, 09:50:06, 11:50:06 — stock build 813921 among them).

## Root cause

`C:\ProgramData\Windhawk\userprofile.json` tracked the catalog id
`translucent-windows` with `version: 1.8.3` (our custom build) and
`latestVersion: 1.8.2` (the real upstream latest by Undisputed00x). Any
difference is treated as an update, so the app offered — and periodically
applied — a **downgrade dressed as an update**. That machinery is also what
kept reverting the mod on 10-11/12/14 (see `2026-10-14-translucent-windows-revert3.md`).

## Fix (the plan recorded in revert3: migrate to a `local@` id)

1. Backed up first: `backups\2026-10-15\translucent-windows-id-migration\`
   (pre-migration reg export, old source, old DLLs, `userprofile.json.before`,
   staged new source) at 11:52:18.
2. Removed the old catalog id with `windhawk-cli mod remove` — config, source,
   DLLs and the **profile entry** (the phantom's fuel) gone.
3. Rebuilt the reviewed 1.8.3 fork as `local@translucent-windows` with the
   bundled clang (id via force-included header, `Engine\2.0.0_1` libs) and
   direct-installed: source + both-arch DLLs + registry key clone (**156
   settings**, `excludeCustom=notepad++.exe`), `SettingsChangeTime` bumped
   12:04:41 +08. The CLI cannot do this for `@` ids (see traps), so this is the
   manual recipe from `notes\2026-10-04-mod-id-migration.md`.
4. Re-pointed the drift guard to the new id (`scripts\2026-10-15-translucent-windows-guard.ps1`),
   `InstallGuard` at 12:22:31 — task Ready, suspend marker cleared, audit reads
   all three hashes pristine, Disabled=0, version 1.8.3.
5. Deleted the stale 6-hour T3 drift canary (it watched the dead id; the
   5-minute guard replaces it).

## Verification (12:41–12:52 +08, this thread)

- Registry: old key **absent**; `HKLM\...\Mods\local@translucent-windows`
  present with Version 1.8.3, Disabled 0, LibraryFileName
  `local@translucent-windows_1.8.3_1.dll`, 156 flat settings values.
- Hashes: both DLLs and ModsSource match `receipt-verify.json` and the guard's
  constants exactly.
- `userprofile.json`: **zero** `translucent-windows` mentions.
- Engine IPC (`windhawk-cli --json mod list`): `enabled=true`,
  **`updateAvailable=false`** — the engine itself no longer computes any update
  for the mod.
- Guard: heartbeat stamp (`ModsWritable\translucent-guard.stamp`) refreshing
  every 5 minutes, no drift entries since the re-point.
- Engine liveness evidence: symbols (user32, comctl32, comdlg32, winbrand,
  wuser32) fetched 12:01:02–12, immediately after the key write and DLL staging
  — consistent with the engine loading the new hook mod into running processes;
  `taskbar-app-memory` wrote mod-storage at 12:50 (engine injecting normally).

## Not directly verifiable from the agent sandbox

- Per-process DLL mapping. The sandbox has a filtered process view, and
  `Engine\ModsWritable\mod-status` records stopped being written after
  2026-10-08 13:01 while mods demonstrably run — so module-census scripts
  report false zeros. Until engine behaviour changes, verify load state via
  engine IPC (`windhawk-cli --json mod list`) and `mod-storage` activity.
  Worst case meanwhile: the old identical-code DLL stays mapped in already
  running processes until each restarts; a reboot normalizes everything.
- **User spot-check:** the Windhawk UI should show no update for the mod, and
  taskbar/Terminal blur should be unchanged.

## Traps learned (added to `docs\traps-and-tips.md`)

- A local fork's metadata `@id` keeps the CATALOG id (no prefix) - the
  `local@` prefix lives only in the filename and registry key. `@id local@…`
  gets the mod rejected by the app's parser (UI toast: MODS_LOAD_FAILED) while
  the engine keeps running it. The CLI also cannot install/compile `@` ids at
  all → manual build + key clone for `local@` installs.
- `mod-status` is stale by design now; don't census from it.

## Follow-up (13:27 +08, same day): UI MODS_LOAD_FAILED fixed

The first verification missed that the app's metadata parser (shared by the UI
and the CLI) rejects `@` inside the `@id` line. The migration had written
`@id local@translucent-windows` into the source, so the Windhawk UI raised
"Something went wrong - 1 mod(s) could not be loaded ... MODS_LOAD_FAILED"
repeatedly (each failed-load retry re-opens the source, which also briefly
locks it against writes).

The rule (matches every other local fork here, e.g. `local@translucent-flyouts`
whose source says `@id translucent-flyouts`): the `local@` prefix lives only in
the source filename and the registry key; the metadata `@id` keeps the catalog
id. The engine was never affected - it reads the compiled DLL, whose embedded
id is correct.

Fixed by `scripts\2026-10-15-translucent-windows-metadata-fix.ps1` (elevated;
suspends the drift guard for the edit and resumes it after): `@id` restored to
`translucent-windows` in ModsSource and the dev copy (byte-exact; source hash
`B6F8DF…` → `F694DA98C260CCF01FF8C7E765463CC6F98F54A99010651C9B7FE8D9EFCD7878`),
guard `$forkHash` updated to match. Verified: `windhawk-cli source meta` parses
(id=translucent-windows, version 1.8.3), `--json mod list` shows the version
populated with `updateAvailable=false`, guard heartbeat clean with no drift.
DLLs untouched (hashes unchanged). Receipt:
`reports\2026-10-15-translucent-windows-id-migration\metadata-fix.json`.

Separately, two mods (`explorer-tags`, `vlc-discord-rpc`) were uninstalled at
13:28 (userprofile.json shrank two entries, registry and engine list both went
130 → 128 keys, in agreement) — user action from the UI, unrelated to this fix;
recorded so a future count audit doesn't chase it.

## Records

- Scripts: `scripts\2026-10-15-translucent-windows-{id-migration,local-install,verify-restage,load,guard,remove-drift-canary}.ps1`
- Receipt + logs: `reports\2026-10-15-translucent-windows-id-migration\`
  (`receipt.json` is the final summary; guard reports land in
  `reports\2026-10-15-translucent-windows-guard\` on any heal)
- Backups: `backups\2026-10-15\translucent-windows-id-migration\`; the old
  guard's drift captures from the final phantom war:
  `backups\2026-10-15\guard-20261015-*`

## Rollback

Disable the guard (`Disable-ScheduledTask -TaskName TranslucentWindowsGuard`),
import `backups\2026-10-15\translucent-windows-id-migration\translucent-windows-before-migration.reg`
(restore `LibraryFileName=translucent-windows_1.8.3_256343.dll`; the 256343
DLLs are in the same folder), copy the old `translucent-windows.wh.cpp` back to
`ModsSource\`, delete the `local@` key/source/DLLs, bump `SettingsChangeTime`.
Do **not** restore `userprofile.json.before` — it re-arms the phantom.

## Context

- Saga: `notes\2026-10-13-terminal-titlebar-revert2.md`,
  `notes\2026-10-14-translucent-windows-revert3.md` (where the migration plan
  was first written down).
- Recipe: `notes\2026-10-04-mod-id-migration.md`.
- The interrupted thread (`7011d9fc…`) performed remove + install + guard
  re-point; this thread verified the machine state, killed the stale canary,
  and wrote the records.
