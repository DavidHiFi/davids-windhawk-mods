# Explorer TreeItem Tweaker: hover and selected backgrounds not applying (2026-10-12)

Status: fixed on this machine. Installed fork `local@explorer-treeitem-tweaker-plus` 1.1.2 enabled;
original `explorer-treeitem-tweaker` 1.1.1 disabled. Verified by screenshot after an Explorer restart.

## Symptom

Font and text colour applied, but the rounded hover and selected backgrounds did not draw. The
mod looked enabled, and the only workaround was disabling and re-enabling it and restarting Explorer.

## Root cause (measured)

`translucent-windows` 1.8.2 (build 948147) hooks `DrawThemeBackground` and paints TreeView items
itself (`PaintTreeViewButton`), then returns without calling the original. Two hooks on the same
function chain, so whichever is outer decides the draw. When translucent-windows is outer, the
tweaker never sees `TVP_TREEITEM` draws.

Evidence:

- Mod load order in each explorer process (from `ModsWritable\mod-status`, 2026-10-05): the tweaker
  loads before translucent-windows in every sample.
- A/B test (2026-10-12, 02:14 AM): with `Exclude=explorer.exe` on translucent-windows, the selected
  "This PC" row drew as the tweaker's rounded pill. Without the exclude it drew as a square row.
  Measured by screenshot crop. `reports\2026-10-12-treeitem\test-exclude-navpane-selected.png`.
- `translucent-windows` was reinstalled as 948147 on 2026-10-11 at 23:22. Before that the user saw
  the tweaker working (their account), but I did not confirm the older build lacked tree painting.

Inferred: the order of hooks follows mod load order, which differs between boots. Toggling the mod
moved it later in that order, so it worked until the next boot. This is why disable/enable plus an
Explorer restart appeared to fix it. I did not reboot to test this.

## Fix

Local fork `local@explorer-treeitem-tweaker-plus` (source
`Windhawk\explorer-treeitem-tweaker-plus\local@explorer-treeitem-tweaker-plus.wh.cpp`).
`DrawThemeBackground`, `DrawThemeBackgroundEx`, `GetThemeColor` and `DrawThemeTextEx` are hooked
3 seconds after the worker thread starts, through a timer, instead of in `Wh_ModInit`. The
other mods have finished hooking by then, so this mod is the outer hook whatever the order. The
initial track and font still run at start. A `RefreshTrackedTrees()` call repaints once the
hooks are in. Diff: `reports\2026-10-12-treeitem\fork-vs-original.diff`.

Verification (measured, one Explorer restart, translucent-windows loaded in that process):

- Module list: the fork loaded, `translucent-windows_1.8.2_948147.dll` loaded too.
- Selected row: rounded pill. `reports\2026-10-12-treeitem\fork-navpane-1.png`.
- Hover on Downloads: rounded outline. `reports\2026-10-12-treeitem\fork-hover-downloads.png`.

Not verified: a real reboot. The fix does not depend on load order, but the first boot after this
change is the test. If the tree looks plain at boot, check the Explorer modules for the fork and
restart Explorer once.

## Records

- Install script: `scripts\2026-10-12-treeitem-plus-install.ps1` (`-Install`, `-Rollback`, no
  parameter prints the state). Elevated through `H:\System Configuration\scripts\Invoke-Elevated.ps1`.
- Backup of the original key: `backups\2026-10-12-treeitem\explorer-treeitem-tweaker-before.reg`.
- Receipt: `backups\2026-10-12-treeitem\treeitem-plus-receipt.json`.
- translucent-windows exclude test: `scripts\2026-10-12-translucent-windows-explorer-test.ps1`.
  Applied and rolled back the same morning. The restored key matches
  `backups\2026-10-12-treeitem\translucent-windows-before-test.reg` line for line.
- Other restarts: Explorer restarted at 02:08 AM, 02:14 AM and 02:23 AM (all for these tests). Explorer
  also restarted at 02:08:48 AM by a process I did not identify. A coop note was posted before the tests.

## Rollback

Elevated, `scripts\2026-10-12-treeitem-plus-install.ps1 -Rollback`: disables the fork and enables
the original. That restores the broken look. The fork stays installed.

## Ruled out

- `IsTreeViewTheme`: uxtheme ordinal 74 (`GetThemeClass`) returns `TreeView` on this build, so the
  check is not the cause.
- Font path: applies, so tree tracking works. The fault is in drawing only.
- The tweaker itself: its DLL is unchanged since 2026-10-04. The part that changed is
  translucent-windows (948147, 2026-10-11).

## Other notes

- The DBWIN capture (`scripts\2026-10-12-treeitem-dbwin-capture.ps1`) saw no Windhawk or mod
  `OutputDebugString` lines during an Explorer start, so Wh_Log is not a usable log here.
- Windhawk 2.0.0-alpha.7 was installed on 2026-10-11 (see `notes\2026-10-11-windhawk-2a7-update.md`).
  It is not the cause here: the mod DLL and the failing draw path predate it.
