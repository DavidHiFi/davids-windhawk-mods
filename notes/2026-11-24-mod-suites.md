# 2026-11-24: mod suites (debloat), state

Owner ask: fold small mods into suite mods, each old mod a module with its own switch, then
remove the old ones with a backup. Plan and lists: `reports\2026-11-24-mod-suites-audit.md`.
Owner answers: ours and other authors' mods both; big apps stay separate; drop the dead weight;
remove old mods with a backup. "Skip the queue" holds for this thread (seats and load gate).

## Wave 1 (this turn)
- Mocha App Icons 1.2.0 takes in Mocha Steam Icons. `work\2026-11-24-mod-suites\mocha-icons\gen.py`
  builds it from the live sources: each original in its own namespace, a dispatcher picks the
  Steam engine in steam.exe / steamwebhelper.exe and the app engine elsewhere. New `steam` switch
  (default on) gates Steam's tray, window and shortcut switches. Steam's admin-declined memory
  renamed `steamSharedDeclined`. Offline compile: no errors, 0 warnings.
- Install: `mocha-icons\install-120.ps1` (engine lock, Steam mod off, Install-StagedMod elevated).
- Removal with backup: `remove-wave1.ps1` takes out local@mocha-steam-icons plus the five unused
  mods (store logitech-battery-tray, search-menu-inspect-helper, smart-process-priority-ram-optimizer,
  live-video-wallpaper, lock-screen-live-wallpaper). Backups in `backups\2026-11-24-mod-suites\<id>`.
- Then: `python scripts\2026-11-22-manifest-sync.py --write`, `publish-mods.py`,
  `mod-consistency.py check --full`, `settings-engine.py check`.

## 2026-11-26: category suites and the new-mods watch
- Owner: every area is one suite (Taskbar, Explorer, Icons, Windows, Apps, Input, Look,
  Wallpaper, Tools, Gaming); plan v2 in the audit report. Rules added to `AGENTS.md`, the global
  rules and memory (`new-store-mods-watch`).
- Wave 2 sources: Seamless Input and Seamless Wallpaper built by helpers in `input\` and
  `wallpaper\` (the first wallpaper run hit a rate limit and was restarted). Not installed yet:
  the owner is gaming, so no test PC first load.
- New laptop job `windhawk-new-mods`, daily 2:00 pm with backups to 2:50. Job file
  `C:\H\Server Configuration\scripts\scheduled-jobs\windhawk-new-mods.md` (source here:
  `work\2026-11-24-mod-suites\windhawk-new-mods.md`). It runs
  `%LOCALAPPDATA%\store-watch\daily.ps1` on the tower over ssh (source
  `scripts\store-watch-daily.ps1`), which needs `store-watch.exe` next to it.
- jobs.json on the laptop: old value none; new key `windhawk-new-mods` (every 24 h, grace 3 h,
  hold 18 min, first due 2026-11-26 14:00). Backup `jobs.json.bak-20261126-0257`. Rollback:
  delete the key or restore that backup, and delete the six "Windhawk new mods check" tasks.
- Laptop tasks (project b8683208..., daily, laptop time): 1 Halo 14:00, 2 Claude 14:10,
  4 DeepSeek 14:30, 5 MiMo 14:40, 6 Router 14:50 exist (ids end
  `windhawk-new-mods-<tier>-20261126`). 3 Codex is missing: its step thread hit Codex's usage
  limit. Step 5 of the job file makes the Halo or Claude run resend the create message to that
  step thread each day until the task exists, so no hand fix is needed.
- The store watcher itself (`store-watch.exe`, Rust; crate `tools\store-watch\` in this
  workspace, build output in `D:\Agent Work\store-watch\target`) is still being built by a
  helper. Until it is copied to `%LOCALAPPDATA%\store-watch\` on the tower, daily.ps1 prints
  `exit 2` and the run is recorded as failed down the chain.
- Wave 3 helpers (2026-11-26, 3 am, owner gaming so source only): Seamless Windows (grows Seamless
  Window Manager, keeps its id), Seamless Icons, Seamless Tools, in `windows\`, `icons\`, `tools\`.
  Their briefs: `C:\Users\Public\suite-briefs\` (delete when the helpers are done).
- 3:40 am: T3 restarted and cut every helper's turn; the Halo ones (store watcher, Wallpaper,
  Windows, Tools) resumed by themselves. Input and Icons had already died on Halo's limit of 8
  jobs at once, so they and Seamless Look run on Claude Sonnet instead (`*-sonnet.txt` briefs,
  same text with the Claude Code board line).

## Left (waves 2 to 4)
Each suite: generate with the same pattern, compile offline, first load in the test PC (all of
these load into explorer.exe), install, carry settings over, remove the old mods with a backup,
publish. Order: Seamless Explorer, Seamless Taskbar extras (other threads work in Seamless
Taskbar; check coop first), then Windows, Apps, Input, Look, Tools.
