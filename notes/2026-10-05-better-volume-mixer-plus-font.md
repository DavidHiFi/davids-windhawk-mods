# Better Volume Mixer Plus 1.1.0: Font setting (2026-10-05)

## What changed

- `local@better-volume-mixer-plus` 1.1.0 adds a **Font** setting (registry value
  `fontFamily`).
- Empty = Segoe UI. A family that isn't installed also falls back to Segoe UI.
  Icons stay on Segoe Fluent Icons.
- The title uses the font's bold style; body and small text use regular. Fonts
  are rebuilt when settings change (`WM_APP_RELOAD_SETTINGS` now calls
  `CreateFonts`), so no restart is needed after editing the setting.

## Installed state

- `LibraryFileName = local@better-volume-mixer-plus_1.1.0_2.dll`,
  `Version = 1.1.0`, `fontFamily = FiraCode Nerd Font`.
- Deployed x64/x86 DLLs hash-match the built 1.1.0_1 artifacts; the ModsSource
  copy hash-matches the repo source and the origin/main blob.
- Verified on screen: replayed the tray-icon open event into the mixer window
  from an elevated helper and captured it; all text renders monospace.
  Screenshot `reports\2026-10-05\bvm-font\mixer-font-fira-code.png`, log
  `verify-ui.log`.

## Published

- Pushed to `DavidHiFi/davids-windhawk-mods` main as `14ea315` (mod source,
  README feature line, manifest version). No PRs existed before or after.
- Run 1 committed from a throwaway worktree because the main checkout carries
  other threads' uncommitted files.

## Leftovers and cautions for the next session

- Run 1 used `windhawk.exe -restart` (07:57:39); explorer.exe restarted at
  07:58:29, exactly the behavior CURRENT-STATUS warns about. Nothing broke this
  time - the mixer and every tool mod came back. Use registry writes plus
  `SettingsChangeTime` bumps for settings changes, not `-restart`.
- The main checkout is still `ahead 1, behind 4` with uncommitted Windhawk
  Styler files and the unpushed commit `d619c06` (Shell Font Changer). Left
  untouched; not this task's work. The bvm source in the main checkout is now
  identical to origin/main, so a future pull is safe for that file.
- The fork folder's default build source
  (`Windhawk\better-volume-mixer-fork\better-volume-mixer-plus.wh.cpp`) was
  still 1.0.0; it now matches the repo 1.1.0 source. The stale copy is kept at
  `backups\2026-10-05\bvm-font\fork-source-before-font-sync-1.0.0.wh.cpp` so a
  default rebuild can't silently produce a fontless 1.0.0.
- The empty orphan directory `work-weather-pub` (left from the weather publish
  worktree) was removed.

## Receipt

`reports\2026-10-05\bvm-font\receipt.json`
