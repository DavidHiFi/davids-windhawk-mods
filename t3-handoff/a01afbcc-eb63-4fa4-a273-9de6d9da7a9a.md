# Handoff brief: Translucent Flyouts Plus, accent border missing on some menus

Thread: a01afbcc-eb63-4fa4-a273-9de6d9da7a9a
Project: Windhawk Configuration (workspaceRoot `H:\Windhawk Configuration`)
Chain generation: 1
No brief file existed for this thread; this brief was composed by the handoff watch from the thread record plus the workspace status file.

## Objective

Audit the forked Translucent Flyouts Plus Windhawk mod and fix that some menus (right-click/context menus and pop-out menus) do not get the chosen accent border colour. Example from the user: right-clicking the desktop does not use the border colour set in Windows settings. The user's accent colour is Catppuccin Mocha blue ("mocha blue mauve"; the third screenshot in the original prompt shows the intended look). User's exact instruction: get that fixed fully autonomously, do not ask questions, ASAP.

## Done

- Mod source located: `Windhawk\translucency-flyouts\src\30-engine.inc`. The build script assembles `src/` into `translucent-flyouts.wh.cpp` (~127 KB) and accepts `-DebugLog`.
- Two source copies exist: the fork in `davids-windhawk-mods` and the engine's copy in `ModsSource`. The loaded build is **0.6.33**. The build script's default engine path is stale; the current engine path is the `2.0.0_1` path.
- Install route to mirror (from the 0.6.32 install script): copy the DLL into `Engine\Mods`, copy the source into `ModsSource`, set registry `LibraryFileName` and `Version`.
- Coop: the thread joined the board and claimed the mod source. A peer thread `4fd80e25` was editing shell popups, probably the same mod. Check its notes before touching shared files.
- Last edit that landed (11:02:37 AM local, immediately before the failure): a change in `Windhawk\translucency-flyouts\src\30-engine.inc` to the paint code around the comment "No full-rect fill here. It painted the dark band around the menu. Only the 1 px outline ...", near offset 632.

## In flight (exact step)

Adding temporary debug logging to the menu paint hook, guarded by `TF_DEBUG_LOG` so release builds stay clean, and bumping the mod version to 0.6.34. The thread had read the exact hook text; its last status was: "Next I'll add a matching log line in the `MENU_POPUPBORDERS` branch, which records the colour the paint uses. First I'll read the shifted lines." That read is where it stopped. The run then died on the Claude pool: 503 auth_unavailable, `rate_limit_error: This request would exceed your account's rate limit.`

## Next steps

1. Inspect the uncommitted edit in `Windhawk\translucency-flyouts\src\30-engine.inc` and finish (or revert) the `TF_DEBUG_LOG` instrumentation, including the `MENU_POPUPBORDERS` branch log line.
2. With the debug log, establish which paint branch the desktop right-click menu takes and whether that branch actually receives the accent colour.
3. Fix the border path for the affected menus. Rebuild with the mod build script, passing the current `2.0.0_1` engine path. Install by mirroring the 0.6.32 script: DLL to `Engine\Mods`, source to `ModsSource`, registry `LibraryFileName` and `Version`.
4. Verify visually on the desktop right-click menu and pop-out menus against the Catppuccin Mocha blue accent. Record before and after.
5. Update `H:\Windhawk Configuration\CURRENT-STATUS.md` and add a dated note under `notes\`. Then release coop claims with `coop done`.

## Gotchas and paths

- `H:\Windhawk Configuration` is a git repository with **no commits yet** on `master`. Every file is untracked, so `git status` gives no usable baseline. Copy any file before overwriting it.
- The `glob` and `grep` tools timed out repeatedly on this workspace. Use PowerShell `Select-String` and direct reads instead.
- `translucent-windows` (a different mod) was moved to a `local@` id after the app silently reinstalled stock builds. The same engine install and registry patterns apply, and a read-only drift check runs every 6 hours. See `CURRENT-STATUS.md`.
- The sandbox denies file-tool writes to some dot-folders. Use PowerShell for those writes.
- Other live threads may hold the same mod files. Check coop notes (peer `4fd80e25`) before editing.

## Verification status

- Measured: source file locations, loaded build 0.6.33, engine build and install route, and a peer-thread conflict on the same mod. Nothing has been rebuilt, installed or visually verified yet. The missing-border bug is still open.

## State of context

The audit is finished and instrumentation was just starting when the Claude pool rate-limited the run. The border fix, rebuild, install, and visual verification are all still ahead, so do not treat any of this as complete. Successor started at chain generation 1.

## Live state (updated by successor)

- [ ] Brief written (this file)
- [ ] Workspace verified (AGENTS.md read, git status, 30-engine.inc edit inspected)
- [ ] Coop joined, peer 4fd80e25 notes read
- [ ] TF_DEBUG_LOG instrumentation finished or reverted
- [ ] Root cause of missing border identified
- [ ] Fix applied, rebuilt, installed
- [ ] Visual verification on desktop right-click and pop-out menus
- [ ] CURRENT-STATUS.md and notes updated, coop done
