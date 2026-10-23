# Explorer folder navigation speed: applied and verified

2026-10-13. Continuation of `2026-10-13-explorer-speed-plan.md` (the plan and its
evidence live there). That note's "awaiting go" header is historical; everything
below is applied. Receipt: `reports\2026-10-13-explorer-speed\receipt.json`.

## What changed

**Set A — timing** (applied 19:33, hot-reloaded via `SettingsChangeTime`):

| Mod | Setting | From → To |
| --- | --- | --- |
| file-explorer-content-animation | navigationDelay | 300 → 0 |
| file-explorer-content-animation | duration | 500 → 150 |
| file-explorer-content-animation | firstOpenDelay | 500 → 100 |
| file-explorer-details-autofit-columns | elastic | 1 → 0 |
| file-explorer-details-autofit-columns | delay | 400 → 150 |

`passiveTriggers` stays 1 (columns still fit on every navigation). No "Working
on it..." flash observed in the tests at navigationDelay 0.

**Set B — one size source**: `explorer-size-on-disk-column` `folderSizes`
`exceptSystemFolders` → `disabled`, then, per the user's dedupe request ("size
and then size on disk which do the same thing ... autonomously choose"), the
whole mod was disabled (`Disabled=1`, 20:00). Folder sizes now come from one
place: `explorer-details-better-file-sizes` via the Everything index, shown in
the native **Size** column. This also removed the mod's per-file allocation
reads on Explorer's UI thread — the H: (5400 RPM) killer. Blur untouched.

## Result

- Baseline (19:31): big folders 13–16 s to settle, `C:\` 2.3 s.
- After sets (20:16): big folders ~3 s.
- Final, after the 20:33 shell restart (navtest, ms until location reported and
  not busy): `C:\` 1,580 · `notes` 2,839 · `AppData\Local` 3,527 ·
  `H:\Windhawk Configuration` 3,595. Raw:
  `reports\2026-10-13-explorer-speed\navtest-final-post-restart.txt`.
- Visual check (`final-check-after-restart.png`): details view of
  `C:\Users\localuser` — **no "Size on disk" column**, folder sizes in **Size**.

## Verification

- Registry read back directly: all six values + `Disabled=1`.
- Module census: 87 Windhawk DLLs in every explorer.exe process (was 88); the
  missing one is exactly `explorer-size-on-disk-column`. better-file-sizes,
  content-animation, autofit-columns, taskbar styler, translucent-flyouts all
  loaded. All explorer processes responding.
- The "Size on disk" header that briefly survived the disable was Explorer's
  in-memory view cache (no persisted entry in any of the 84 saved-view blobs or
  templates); the pre-approved shell restart flushed it.

## Rollback

- Settings: `scripts\2026-10-13-explorer-speed.ps1 -Rollback -BackupDir "H:\Windhawk Configuration\backups\2026-10-13\explorer-speed"` (elevated).
- Dedupe: `scripts\2026-10-13-explorer-speed-dedupe.ps1 -Rollback` (elevated).

## Notes for next time

- The 20:33 shell restart crashed Explorer once (recovered the same minute);
  cause not pinned, possibly raced another thread's shell work. No recurrence.
- A confined DSH shell cannot enumerate processes, drive shell COM, or write
  `reports\`; do verification in one escalated run. The harness write/edit
  tools handle workspace files fine.
- Contingency items from the plan (auto-fit fork debounce, better-file-sizes
  fork cache tweaks, H: file reads) were not needed — only revisit if navtest
  regresses.
