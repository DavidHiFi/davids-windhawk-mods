# Explorer folder navigation: bisect and settings fix

2026-10-13. Follows `notes\2026-10-13-explorer-speed-final.md`. After Sets A and B
the five test folders still took 1.2 to 4.4 s to settle. This note records which
mods cost that time and the two settings-only changes that removed most of it.

## Result

Median time from Navigate() until the folder is shown and idle (5 rounds, same five folders):

| Folder | Before (2 runs, this session) | Now |
| --- | --- | --- |
| `C:\` | 1,153 to 1,241 ms | 449 ms |
| `D:\Configuration Files` | 3,078 to 3,594 ms | 461 ms |
| `H:\Windhawk Configuration\notes` | 1,577 to 2,110 ms | 455 ms |
| `C:\Users\localuser\AppData\Local` | 3,546 to 4,411 ms | 457 ms |
| `H:\Windhawk Configuration` | 3,402 to 3,815 ms | 540 ms |

Floor with every Windhawk mod off, same folders (one run): 267 to 430 ms.

## Changes applied (settings only, no code)

| Mod | Setting | Was | Now | Effect |
| --- | --- | --- | --- | --- |
| `file-explorer-details-autofit-columns` | `passiveTriggers` | 1 | 0 | No auto-fit on folder open, navigate, or minimize/restore. F5, Ctrl+R, the refresh button and the context-menu refresh still fit. |
| `explorer-details-better-file-sizes` | `calculateFolderSizes` | `everything` | `withShiftKey` | Folder sizes show in Size only while Shift is held on load or refresh. No Everything lookups on normal navigation. |

- Backups: `backups\2026-10-13\explorer-lag\settings\*.settings.reg`.
- Script: `scripts\2026-10-13-explorer-lag-settings.ps1` (`-Backup`, `-Apply`, `-Rollback`).
- Rollback (elevated): `scripts\2026-10-13-explorer-lag-settings.ps1 -Rollback "H:\Windhawk Configuration\backups\2026-10-13\explorer-lag\settings"`.
- Verified: registry readback of both values; SettingsChangeTime bumped.

Not changed: blur (`translucent-windows`), every other mod's enabled state, the Size-on-disk
removal from the earlier session (`explorer-size-on-disk-column` still Disabled=1), and the
content-animation and auto-fit timing from Set A.

## Where the time went

Each test restarted Explorer, waited for the mods to load, then ran the benchmark. Median
ms on the same five folders; floor is about 300.

| Test (state under test, all else off) | Result | Cost over floor |
| --- | --- | --- |
| Auto-fit on navigation (`passiveTriggers` 1) | 325 (notes) to 800 (other folders) | about +0.4 to 0.5 s |
| Better File Sizes, `everything` | 330 (notes) to 1,130 (AppData) | about +0.4 to 0.8 s |
| Better File Sizes, `withShiftKey` | 407 to 444 | about +0.1 s |
| `local@window-manager` | 459 to 542 | about +0.15 s |
| `icon-resource-redirect` | 288 to 362 | none |
| `local@translucent-flyouts` + `dark-menus` | 312 to 338 | none |
| 8 global mods (incl. `translucent-windows`, `windows-animations`, `never-auto-expand-explorer-tree-items`, `timer-resolution-control`) | 380 to 510 | about +0.1 to 0.15 s |
| 34 explorer-scoped mods (group B, not split further) | 391 to 420 | about +0.1 s |
| 17 explorer-scoped mods (group A2) | 278 to 412 | 0 to 0.1 s |
| 9 explorer-scoped mods (A1b) and 5 more (A1a-even) | 243 to 336 | none |

Full state, all mods on, before the settings fix: 1.2 to 4.4 s. Auto-fit on navigation and
Everything folder-size lookups account for most of it.

Measurement caveat: Discord, Ableton Live and Steam ran during the tests with CPU bursts of
50 to 80%. A single navigation varied by about 2x, so each figure above is a median of 3 to 5
rounds. Read differences under about 100 ms as noise.

## Verification

- Registry readback: both settings values as written; 133 Windhawk mod `Disabled` flags match
  the pre-test snapshot (`backups\2026-10-13\explorer-lag\original-disabled.json`, 0 mismatches).
  Eight mods were already disabled before this session and stay disabled.
- Modules: 87 Windhawk DLLs in `explorer.exe`, the same count as at the end of the earlier
  session. The Size-on-disk mod is off, but saved folder views still showed the column. That is
  fixed in `notes\2026-10-13-explorer-lag-shellbag.md`; screen checked after the fix.
- Raw benchmark output: `reports\2026-10-13-explorer-lag\bench-*.json`.
- Full-mod-set snapshot for a reg-level restore: `backups\2026-10-13\explorer-lag\mods-all-before.reg`.

## Options not applied (user decision)

1. Keep this state (applied). About 0.45 to 0.55 s. Keeps all looks and features.
2. Also exclude `explorer.exe` from `local@window-manager`. About 0.15 s less, estimated from the
   single-mod test. Costs Alt+drag move and resize and right-click maximize in File Explorer
   windows. Keeps them in other apps.
3. Also disable folder sizes entirely (`explorer-details-better-file-sizes` Disabled) and the
   Explorer blur (`translucent-windows`). Reaches the floor of about 0.3 s. Costs all folder sizes
   and the Explorer blur.

Auto-fit on every navigation (`passiveTriggers` back to 1) adds about 0.4 s. Folder sizes on every
navigation (`calculateFolderSizes` back to `everything`) adds about 0.5 s on folders with subfolders.

## Notes

- Explorer restarted about 25 times during the tests. Any open Explorer windows closed each time.
  Restarts are pre-approved.
- The bisect driver is `scripts\2026-10-13-explorer-lag-bisect.ps1` (`-Action Snapshot`, `Set`,
  `Restore`, `Show`). Its snapshot restore is what returned every flag to its original value.
- The benchmark is `scripts\2026-10-13-explorer-lag-bench.ps1` (median over rounds). The earlier
  single-run timer is `scripts\2026-10-13-explorer-speed-navtest.ps1`.
