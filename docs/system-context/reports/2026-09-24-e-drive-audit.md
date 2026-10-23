# E: drive audit and reorganization — 2026-09-24

## Summary

| | |
|---|---|
| Folder moves | **19/19** |
| Path/config rewrites | **63** (54 .lnk, 4 HKCU Classes, 3 TypedPaths, 1 ExtInject xml, 1 Notepad++ config) |
| Manifest rows | 82 (`Move` 19, `Updated` 61, initial `FAIL` 2 → fixed elevated) |
| External E:-drive shortcuts | **30/30 resolve** (target + working dir) |
| non-MessageLogger files / bytes delta | **0 / +2,850 B** (config path string rewrites only) |
| MessageLogger delta | +45 files / +~25.5 MB — **live Discord sink** (expected) |
| Data deleted | **none** (same-volume moves only) |

Rollback manifest: `H:\System Configuration\backups\2026-09-24/e-drive-move-manifest.csv`  
Script (dry-run default): `H:\System Configuration\scripts\2026-09-24-organize-e-drive.ps1`  
Move log: `H:\System Configuration\reports\2026-09-24-e-organize.log`  
Baselines: `reports\2026-09-24-e-pre-state.json`, `-e-pre-move-live.json`, `-e-post-state.json`  
Shortcuts: `reports\2026-09-24-e-shortcuts.csv` (pre), `-e-shortcuts-post.csv` (post)

## E:\ root after

```
E:\
  _Archive\
    01-Backups\   SteaMidra, UniGet UI, Everything Database, Everything Database (2)
    02-Software\  Windhawk, PowerToys
    03-Games\     AC Black Flag CE Table, CoD FF Tools
    04-Misc\      BoxAverageTracker.exe
    05-Audio\     FabFilter Presets
    06-Config\    hide-linux-from-explorer.reg, mpo_disable.reg, mpo_restore.reg
  MessageLogger\              PROTECTED (live)
  Miscallaneous\Scripts\      PROTECTED (canonical path)
  Software\
    Cherax, Cold War Stuffs, Notepad++,
    nvidiaProfileInspector, NVPI-R, Sordum Software Suite
  $RECYCLE.BIN, Recovery, System Volume Information   (system, untouched)
```

All twelve former E: root tool/cache folders are gone from root (`Test-Path` = False).

## Protected — never moved

| Path | Why |
|---|---|
| `E:\MessageLogger` | Live Discord media sink; still writing as of session end (28,318 files / ~26.76 GB). No writer config found that could be redirected safely. |
| `E:\Miscallaneous\Scripts` | Canonical path: 3 `H:\Claude` launcher .lnk, H: docs/audits, internal self-references. 919 files intact; all `H:\Claude` launchers still resolve. |
| `$RECYCLE.BIN`, `Recovery`, `System Volume Information` | System. |

## Path / config rewrites (verified)

- **External .lnk (30):** Desktop 5 + ProgramData Start Menu 24 + Public Desktop 1 — all targets and working directories exist.
- **Internal E: .lnk:** 24 under `E:\Software\…` rewritten in place.
- **HKCU Classes:** `nvidiaProfileInspector.exe` and `NVPI-R.exe` DefaultIcon + shell\open\command → `E:\Software\…`.
- **TypedPaths:** url8/18/23 → `E:\Software\Cold War Stuffs\UAsoft\UAsoft.slnx`, `E:\_Archive\02-Software\PowerToys`, `E:\Software\Sordum Software Suite\24122024`.
- **Extreme Injector `settings.xml`:** DLL paths → `E:\Software\Cold War Stuffs\…`.
- **Notepad++ `config.xml`:** Backup + last-used dirs → `E:\Software\Notepad++\Backup`. (Two MRU entries still list `E:\Remove Contex Menu Items.txt` / `E:\Move Window to Monitor.txt` — historical recent-files, not app config; harmless.)

### Elevated fix (post-move)

Two .lnk files denied non-admin `Save`/`Copy-Item` (file-specific ACLs on ProgramData / Public Desktop):

| File | Fix |
|---|---|
| `C:\ProgramData\…\Start Menu\Programs\Black Ops GSC Compiler.lnk` | Elevated copy of correct Desktop twin; target now `E:\Software\Cold War Stuffs\…\Black Ops GSC Compiler.exe` (was broken: old `E:\Cold War Stuffs\…`). |
| `C:\Users\Public\Desktop\DefenderControl.lnk` | Elevated `WorkingDirectory` → `E:\Software\Sordum Software Suite\24122024\` (target `C:\Program Files (x86)\DefenderControl\dControl.exe` always resolved). |

Both verified post-fix. No other leftovers.

## Integrity

- Pre EXCL (system dirs excluded, MessageLogger included): 29,906 files / 27,589,086,348 B.
- Post same definition: 29,951 files / 27,614,627,582 B.
- Split: non-MessageLogger **0 file / +2,850 B delta** (path rewrites inside moved configs); MessageLogger **+45 / +~25.5 MB** (active Discord writes).
- 19 Moved rows: every destination exists; no source left at old root.
- No deletions; recycle bin not emptied.

## Manifest action counts

| Action | Count |
|---|---:|
| Move | 19 |
| Lnk (Updated) | 54 |
| Reg (Updated) | 4 |
| TypedPath (Updated) | 3 |
| ExtInject (Updated) | 1 |
| Notepad++ (Updated) | 1 |
| **Total** | **82** |

## How to undo

1. Open `backups\2026-09-24/e-drive-move-manifest.csv`.
2. For each `Action=Move` row with `Status=Moved`: `Move-Item -LiteralPath $row.Dest -Destination (Split-Path $row.Source)` (create parents; reverse any ` (2)` collision suffix — see `Everything Database (2)`).
3. Lnk/Reg/TypedPath/config rewrites: reverse by hand from pre-state exports (`-e-shortcuts.csv`, `-e-registry-hkcu.txt`, pre config copies if needed). The CSV is the source of truth for moves.

## Change log entry

| When | Was | Now | Test | Undo |
|---|---|---|---|---|
| 2026-09-24 17:56 | 12 mixed tool/cache folders + Miscallaneous clutter at `E:\` root | 19 moves into `E:\Software\*` and `E:\_Archive\*`; 63 path rewrites | non-ML delta 0 files; 30/30 external .lnk OK; stale roots gone | reverse via e-drive-move-manifest.csv |
| 2026-09-24 18:12 | 2 ACL-denied .lnk (ProgramData BOC broken; Public DC stale workdir) | elevated copy + WorkDir fix | both targets/workdirs exist | restore from Desktop twin / previous .lnk |
| Not changed | `E:\MessageLogger`, `E:\Miscallaneous\Scripts`, system dirs | left in place | live writer + H: launchers OK | n/a |
