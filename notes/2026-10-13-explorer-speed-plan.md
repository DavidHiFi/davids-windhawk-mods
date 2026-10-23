# Explorer folder navigation: plan (APPLIED 2026-10-13)

Updated 2026-10-13. Status: Sets A and B were applied the same day and the
size-on-disk mod was disabled for the dedupe the user requested. Record and
verification: `2026-10-13-explorer-speed-final.md`. The rest of this note is
the original plan, kept for the evidence and the contingency list.

## Your choices, as I read them

- **Elastic:** off. You said it's fine to remove it.
- **Blur:** no changes. translucent-windows and the styler backdrop stay as they are.
- **Folder sizes:** keep Better File Sizes through Everything, and turn off folder sizes in Size on disk. One source.
- **Timing:** shorten the auto-fit and content-animation waits. I took "number 2 and number 3" to mean plan steps 2 (timing) and 3 (one size source). Tell me if you meant something else.

## Is Everything the slowdown?

Mostly no. Your read is right. Everything is set up correctly.

- Folder-size indexing is on, and C: and H: are both indexed. Measured in `%APPDATA%\Everything\Everything.ini`: `index_folder_size=1`, and both drives in `ntfs_volume_paths`.
- The mod still has two design costs. It asks Everything one subfolder at a time and waits for each answer, on the thread that asks for the size. That is Explorer's main thread when a column draws (inferred from the call path, `Everything4Wh_GetFileSize` L1301-1439). It also drops its cache when Explorer goes more than one second without asking (L1776, set at L1852).
- Estimate, not timed: a few milliseconds per folder. Only folders with hundreds of subfolders would feel it.
- The bigger folder-size cost was Size on disk. Its folder walks run in the background. It also reads each file on Explorer's main thread (`ReadAllocation` L405-408, `ReadAllocationByHandle` opens and closes each file). That hurts on H:, which the machine notes list as a 5400 RPM hard drive. Turning off its folder sizes stops the walks (verified in code: `ShouldCalculateFolder` L790-801). File sizes still show.

## The plan

**Set A: timing (the two largest fixed waits)**

- File Explorer WinUI-Like Content Animation (`file-explorer-content-animation`)
  - `navigationDelay` 300 to 0. If "Working on it..." flashes, try 60, then 140.
  - `duration` 500 to 150.
  - `firstOpenDelay` 500 to 100.
  - Fade, slide, page transitions, and nav pane animation stay on.
- File Explorer Details Auto-Fit Columns (`file-explorer-details-autofit-columns`)
  - `elastic` 1 to 0.
  - `delay` 400 to 150. If columns truncate in the 10,000-item test folder, try 250, then 400.
  - `passiveTriggers` stays 1, so columns still fit on every navigation.
- Expected from the timers (inferred, not timed): columns settle about 150 ms after navigation instead of about 530 ms. The transition starts at once instead of after 300 ms.

**Set B: one size source**

- Size on disk (`explorer-size-on-disk-column`): `folderSizes` from `exceptSystemFolders` to `disabled`. File sizes still show.
- Better File Sizes (`explorer-details-better-file-sizes`): no change. `calculateFolderSizes` stays `everything`.

**Set C: blur.** None.

**Contingency.** Only if the test still shows a gap after Sets A and B. Each one is tested before the next.

1. Auto-fit local fork: ignore folder-change refits, or debounce them, so downloads and syncs stop re-laying out columns.
2. Better File Sizes local fork: keep the folder-size cache until the folder changes, drop the one-second idle clear, and move Everything lookups off the thread that asks.
3. H: only: if Size on disk's file reads are still slow on H:, the next step is turning off its column. That loses file sizes, so I'd ask you first.
4. Windows-side settings for big folders (folder templates, thumbnails). Only if still slow.

Blur stays untouched unless you approve a change.

## Benchmark (after go, before and after each set)

- Folders on both drives. C: small, about 1,000 files, and about 10,000 files. H: small, about 1,000 files, and a wide folder with 300 or more subfolders. H: matters most, because it's the hard drive.
- Runs: current settings, after Set A, after Set B. Optional reference run with the four navigation mods off. Ten runs per folder.
- Screenshots per folder for flashes, truncated columns, and blur.
- Target (my number, not measured): settled in about 200 ms on small and medium folders, on both drives.

## Safety

- Back up each touched key first with `reg export` into `backups\2026-10-13\explorer-speed\`. Save the old values in this note.
- One set at a time. Write through the elevated route, read each value back, and bump `SettingsChangeTime`. Restart Explorer only if a mod doesn't reload live (pre-approved).
- Never run `windhawk.exe -restart`.
- Code changes go to local forks only. Keep the authors' headers and license lines. Push nothing.
- Another thread (t3-d75ddc5d) is editing fork metadata in this workspace. Claim the mod paths before any code change.

## Need from you before go

1. Confirm my reading: "number 2 and number 3" means timing and one size source, and no blur changes.
2. OK the contingency code changes in local forks, if the gap stays after Sets A and B.

## Evidence

- Live settings: `HKLM\SOFTWARE\Windhawk\Engine\Mods\<id>\Settings` for the four mods above, plus translucent-windows and windows-11-file-explorer-styler.
- Everything: `%APPDATA%\Everything\Everything.ini` (lines 237, 443, 448).
- Explorer snapshot, measured at 6:55 PM on 2026-10-13: PID 15856, started 5:40 PM, 324.5 CPU-seconds, 403 MB, 292 threads, 5,582 handles. 88 Windhawk DLLs loaded.
- Source: `C:\ProgramData\Windhawk\ModsSource\<id>.wh.cpp`. Line numbers refer to these files.
- Blur stacking is measured in settings. Its GPU cost is not measured.
- Not read in depth: explorer-glyphs-colorizer, explorer-tags, explorer-command-bar, icon-resource-redirect, file-operation-styler.
