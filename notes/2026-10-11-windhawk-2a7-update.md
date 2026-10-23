# Windhawk 2.0.0-alpha.6 -> 2.0.0-alpha.7 update (2026-10-11)

Status: **armed, waiting for T3 Code to close.** Nothing is installed yet. The install
runs the moment the T3 Code (Nightly) processes exit.

## Why it waits

The engine restart and the Explorer restart both break a live T3 Code window. The
2026-09-28 incident (`scripts\FreeDictate\transcripts.log`, 10:10 and 10:17) and
`CURRENT-STATUS.md` both record a frozen T3 GUI that only a close and reopen recovered.
Many `*`-scoped mods also load into the T3 process, so the restart leaves stale hooks
there (trap 16 in `docs\traps-and-tips.md`). AGENTS.md allows a full engine restart
only with no T3 Code window live.

## Release facts (measured)

- Tag `2.0.0-alpha.7`, published 2026-10-10 10:35:55Z, pre-release.
- `windhawk_setup_offline.exe`, 178,524,472 bytes, SHA256
  `B8208BC9189568BDA811A1CF883C4F6399077D619899D2205CB2DA25C74E1FA3`
  (matches the GitHub asset digest). Authenticode valid, "Open Source Developer,
  Michael Maltsev".
- Release notes: per-user mod configuration (opt-in, not used here); `colorRgb` and
  `colorArgb` values now saved with a leading `#` (check the styler and taskbar mods parse);
  leftover `windhawk-ui.exe` fix; blank-main-window fix at startup.
- Installer script (extracted read-only from the payload with 7-Zip, `payload-list\nsi\`):
  stops the service, runs `windhawk.exe -exit`, then `RMDir /r` on the whole `Engine`
  and `UI` folders, and writes the new engine into the first free `Engine\2.0.0[_n]` folder.
  It keeps `Include`/`Exclude` (both non-empty, so untouched).

## Current state at prep (measured 2026-10-11)

- `windhawk.exe` FileVersion `2.0.0-alpha.6`; `EnginePath=Engine\2.0.0`.
- Service `Windhawk` Running (`windhawk.exe -service`, LocalSystem).
- 124 mod keys. Styler `local@windhawk-styler` 2.0.34, Include `windhawk-ui.exe`, enabled.
- `WINDHAWK_USE_VSCODIUM_UI` is unset (machine and user). The legacy UI is no longer in play.
- Discord, Ableton Live, Stream Deck, and T3 Code have `Engine\2.0.0\64\windhawk.dll` loaded.
  The installer cannot delete those locked files, so the new engine most likely lands in
  `Engine\2.0.0_1` (prediction; the receipt records the real path).

## Protected chain

Discord, Ableton, VB-Audio Matrix, and Stream Deck keep the alpha.6 engine code loaded
until they restart. The script does not stop or restart them (AGENTS.md protected list).
A reboot clears that cleanly.

## Files

- `scripts\2026-10-11-windhawk-2a7-update.ps1`: `-Audit`, `-Backup`, `-Install`, `-Rollback`.
- `scripts\2026-10-11-windhawk-2a7-launch.ps1`: elevated, detached launcher. It polls
  `backups\2026-10-11\windhawk-2a7-update\phase-log.txt` for a marker.
- Backup: `backups\2026-10-11\windhawk-2a7-update\` (registry export, Program Files and
  ProgramData copies, `backup-manifest.json`, `installer\`).
- Cancel a waiting install by creating `backups\2026-10-11\windhawk-2a7-update\CANCEL`.
- Receipt on success: `backups\2026-10-11\windhawk-2a7-update\receipt.json`.

## What Install does

1. Refuses unless the installed version is exactly alpha.6.
2. Waits until no `T3 Code*` process runs (6-hour limit). Cancel and timeout log a marker and change nothing.
3. Fresh backup (incremental robocopy, registry export, manifest).
4. Stops the service, runs `-exit`, kills every `windhawk*` process, confirms zero remain.
5. Runs the installer with `/S`, checks exit 0, version `2.0.0-alpha.7`, and the engine DLLs
   for 32, 64, and arm64 in the EnginePath from `windhawk.ini`.
6. Starts the service and the tray (`-tray-only`) if they are not up.
7. Restarts Explorer through a one-shot scheduled task (medium integrity, verified 2026-10-11)
   and reads back the `windhawk.dll` path Explorer loaded. Skipped if T3 Code is open.
8. Compares mod-key count and engine settings before and after, then writes the receipt.

## Rollback

Elevated:
`scripts\2026-10-11-windhawk-2a7-update.ps1 -Rollback`. It stops the engine, mirror-restores
Program Files and ProgramData from `backups\2026-10-11\windhawk-2a7-update\`, re-imports
`windhawk-registry-HKLM.reg`, and starts the tray. Close T3 Code first.

The earlier alpha.6 backup (`backups\2026-10-08\windhawk-2a6-update\`) predates this one
and is kept as-is.

## Verify after it runs

- Read the receipt and `phase-log.txt`.
- `Get-Service Windhawk` Running; `windhawk.exe` version `2.0.0-alpha.7`.
- Styler 2.0.34 still enabled; open the Windhawk UI and confirm the styled look.
- Taskbar and Explorer mods still apply after the Explorer restart.
- Discord, Ableton, Stream Deck, and T3 Code run the alpha.6 engine code until they restart. Reboot when convenient.

## Result (2026-10-11, 11:20 AM)

- Installed with T3 Code open, through `-AllowT3Open` (you chose this after the freeze risk was explained).
- Measured: `windhawk.exe` and `windhawk-ui.exe` 2.0.0-alpha.7; service Running; EnginePath `Engine\2.0.0_1` (32, 64, arm64 DLLs present); 124 mod keys before and after; styler 2.0.34 enabled.
- Measured: T3 window responds; Explorer and T3 both report `Engine\2.0.0_1\64\windhawk.dll` loaded.
- Not done: Explorer restart. A reboot or Explorer restart is still the clean finish. Discord, Ableton, Stream Deck keep the alpha 6 code until they restart.
- Not checked yet: the styled UI look, and the colour settings after the colorRgb `#` change.
- Log quirk: the phase log says "T3 Code is closed" before the install step, which is wrong for this run. The install ran with T3 open.

## Routine fixes (2026-10-11, after the install)

- Lock release: the elevated install started in System32, so coop looked in the wrong project and
  reported the lock as not held. Fixed by passing `-C "H:\Windhawk Configuration"` on every coop call.
  Measured with a throwaway lock: the unlock now works from an elevated shell.
- Launcher crash: it read `phase-log.txt` while the install was appending, and died on a sharing error.
  Fixed: the install writes its final result to `result.txt` once, with a rename. The launcher reads only that file.
- Log writes now retry. A contention test showed appended lines can be lost under a busy reader, so the log is
  for humans, not for control.
- Tested: the result-file path on the safe "already up to date" branch. The full install path with these
  fixes has not run yet. The next real update is the first full test.
