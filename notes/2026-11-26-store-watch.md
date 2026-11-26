# 2026-11-26: daily Windhawk store watch

Owner ask: agents find new store mods that fit a suite, so the owner never scans the Explore tab by hand.

- Tool: `store-watch` (Rust, 1.6 MB, about 14 MB memory). Source `tools\store-watch\` (local, not
  tracked by this repo's ignore rules), build output `D:\Agent Work\store-watch\target`.
- Installed: `%LOCALAPPDATA%\store-watch\store-watch.exe` next to `daily.ps1` (copy of
  `scripts\store-watch-daily.ps1`). Re-copy both after a rebuild.
- Queue: `reports\store-watch\queue.md` (read it before forking any store mod), state in
  `seen.json`, `merged.json`, `queue.json` beside it.
- Daily job: Foxtrot T3 job `windhawk-new-mods`, 2 pm with backups to 2:50 pm, job file
  `C:\H\Server Configuration\scripts\scheduled-jobs\windhawk-new-mods.md`. A fit of 80 or more
  launches one Halo build thread on the tower to fold the mod into its suite.
- Proved 9:2x am: first run 74 new, top pick language-cursor -> Seamless Input (98); second run
  0 new; mark and open work; a test upstream bump flags the merged mod first. The laptop ran
  `daily.ps1` on the tower over ssh and got `exit 0`.
- Open: the step 3 (Codex) scheduled task is missing; the job's repair step asks its step thread
  to create it. Fit scores come from keyword rules and are not yet checked against the owner's picks.
- Built by a Sonnet helper after four Halo runs were cut off.

Rollback: delete `%LOCALAPPDATA%\store-watch\` and the six "Windhawk new mods check" tasks on Foxtrot.
