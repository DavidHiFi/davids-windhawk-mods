# Mod audit and cleanup (2026-10-13)

Continues `notes\2026-10-13-mod-author-credits.md` and `notes\2026-10-13-style-fixes.md`.
Nothing is committed or pushed. The publish line is `origin/main`, which is the same commit as branch `style-pass-2026-10-13`.

## Done

- **Everything Start Menu Plus.** Renamed in the live mod, the repo folder, the mod readme title, `mods/README.md`, the root `README.md` (table row and license line), and the themes readme. The `@id` is unchanged, so settings carry over. `@author` is DavidHiFi, bardelyne.
- **Author credits.** Checked live for all local mods. Each fork lists DavidHiFi first, then its original creators. The legacy Windhawk Styler (`mods/local/windhawk-styler/legacy/`) now also credits Ingan121, because its code is the same Titlebar For Everyone lineage as the main Styler. Taskbar Weather stays DavidHiFi only: its Credits name only Open-Meteo, a data source.
- **Old AI Quota mod.** Removed from the publish checkout (staged). Not installed: no `Mods\local@taskbar-ai-quota-opencode` registry key and no ModsSource file. The live `local@taskbar-ai-quota-plus` is enabled (`Disabled` = 0).
- **Explorer TreeItem Tweaker Plus.** Live 1.1.3, enabled. The original `explorer-treeitem-tweaker` is disabled. Added `mods/local/explorer-treeitem-tweaker-plus/` (source copied from the live file, readme built from the mod's own embedded readme) and `media/previews/explorer-treeitem-tweaker-plus.png`. The preview is the user's capture `reports\2026-10-13-treeitem-rebrand\pill-confirmed-2026-10-13.png`. It shows the selected-item pill with the tweak applied. It also shows drive labels and pinned folder names.
- **Previews.** Every mod folder in the publish checkout has a preview except Center Titlebar Plus, which is excluded by request.
- **David's Window Pack.** Superseded by Window Manager. Copied to `archive\2026-10-13-david-window-pack\` (4 files, checked), then removed from `work\window-pack-publish` (staged). Its old AI Quota copy and two manifest entries were removed from that repo too.
- **Window Manager.** Live 1.1.4 matches the repo copy line for line.
- **Top-level AI Quota folders.** Moved, not deleted, to `archive\`:
  - `2026-10-13-ai-quota-plus-retired\` (27 files: old DLL, registry backups, probes, install logs).
  - `2026-10-11-ai-quota-build\` (5 files).
  Neither folder is tracked by git, so deleting them would lose the only copies of the old DLL and registry backups.
- **Manifest.** Added the TreeItem Plus entry. Set `explorer-treeitem-tweaker` and `explorer-title-bar-label` to disabled to match the registry. Counts: 123 mods, 113 enabled, 14 local.

## Needs a decision or action

1. **Rotate the OpenCode API key.** `settings/quota-mod-localstorage.json` held a non-empty `opencodeKey` value. It was committed on 2026-10-07 (`5cfe8c6`) and is on `origin/main`, so it is public. The working copies are now blanked. Blanking does not remove it from history. Rotate the key in the OpenCode console. Scrubbing history needs a force-push, which needs your go.
2. **Publish from `style-pass-2026-10-13`.** It is at `origin/main`, so a push is a plain fast-forward. Say go and I will commit and push. Local `main` in `davids-windhawk-mods` is 5 ahead and 21 behind `origin/main`, so do not publish from it.
3. **Local `main` has uncommitted copies** of the credit edits and the name fixes. They duplicate the style-pass work. Do not commit them.
4. **Manifest entries with no registry key.** `clipboard-history-upgrade`, `taskbar-dock-animation` and `taskbar-icon-separators` are enabled in the manifest but have no `Mods\` key. Left as is until checked.
5. **Old id in snapshot files.** `settings/mods-state.json` and `settings/quota-mod-localstorage.json` still key the opencode id. Left as is.
6. **TreeItem Plus license.** The upstream source has no `@license` line. The readme table says "Not stated". No license was invented.

## Rollback

- Credit and style edits to live mods: `backups\2026-10-13-author-credits\` and `backups\2026-10-13-style-fixes\`.
- Window Pack: `archive\2026-10-13-david-window-pack\david-window-pack\`.
- Publish checkout: all changes are uncommitted. `git restore --staged --worktree <path>` reverts any file.

## Pushed to GitHub (2026-10-13)

- Commit a8731d9 on origin/main (fast-forward from a458d66). Verified: remote ref matches, TreeItem Plus folder and preview are public, old AI Quota folder and preview are gone (raw preview returns 404), and the full history scan finds nothing new.
- Also in this push: Audio Visualizer repo copy synced to the installed 1.3.2 with its readme regenerated; AI Quota Plus repo readme gained the Credits block; Window Manager credit names Stefan Sundin (repo readme and source, plus the live in-mod readme via an elevated script with backup and receipt in backups\2026-10-13-window-manager-credit\); Shell Font Changer readme states the 85%/80% floor; AI Quota live readme now uses the repo wording (backups\2026-10-13-ai-quota-readme\ has the receipt).
- Scanner: gitleaks 8.30.1 finds nothing in history or the tree. It does not catch short values like the OpenCode key, so those were checked with targeted patterns.

## Still open (needs the user)

1. The OpenCode key is still in the public main. settings/quota-mod-localstorage.json on origin/main has a non-empty opencodeKey. The working copy is blanked, but it is held out of the push, because committing the blank would show the old key in a diff. Rotate the key in the OpenCode console first.
2. Choose how to remove it from the public repo: (a) force-push a rewritten main that drops the key from history, which is destructive and needs an explicit go, or (b) leave history and rely on the rotation. Option (a) is recommended. After it, the blanked snapshot can be committed.
3. Readme feature wording differs between GitHub and the in-mod readme for five mods (start-everything-plus, simple-window-switcher-plus, translucent-flyouts, window-manager, taskbar-ai-quota-plus). Both are reasonable and differ in content. Not reconciled.

## Key removed from public history (2026-10-13)

- Rewrote every head and tag that contained the OpenCode key (fix/font-changer-symbols, main, translucent-flyouts-0.6.33 and 11 tags), with git-filter-repo in a temp mirror. The rule replaced only the JSON value of "opencodeKey". Commit counts and every other file are unchanged; the only file that differs in any rewritten commit is settings/quota-mod-localstorage.json.
- Force-pushed each ref with --force-with-lease against its old SHA. Remote matches the rewritten refs for all 14. origin/main is now b36a855. The public snapshot file has zero non-empty opencodeKey values.
- Restore point, local only: backups\2026-10-13-pre-scrub\davids-windhawk-mods-all-refs.bundle. It still holds the old history with the key. Delete it once you are satisfied.

## Still needs you

1. **Rotate the OpenCode key** in the OpenCode console. A rewrite does not revoke it. I cannot confirm rotation from here.
2. **GitHub copies that the rewrite cannot reach.** The 11 pull request refs (refs/pull/1-11) still hold the old commits, and GitHub does not accept pushes to those refs. Old commits stay reachable by SHA, and forks or caches may still have them. Ask GitHub Support to purge the cached and dangling objects for this repository.
