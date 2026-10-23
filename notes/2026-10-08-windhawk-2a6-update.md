# Windhawk 1.7.3 -> 2.0.0-alpha.6 update (2026-10-08)

Result: **Windhawk 2.0.0-alpha.6 installed and verified**, engine running, all
119 mod keys preserved, mods recompiled by the new compiler. Thread:
`windhawk-2a6-update`.

## How it went

- The user believed 2.0.0-alpha.6 was source-only. The GitHub release actually
  ships `windhawk_setup.exe` and `windhawk_setup_offline.exe`
  (tag `2.0.0-alpha.6`). The offline installer was used: 178 MB, Authenticode
  signed "Open Source Developer, Michael Maltsev", SHA256
  `EAC905E2E0D87C53241F3A06721124B83A56E7736695EEDF1E1A40B536523D23`.
- Route: official NSIS installer with `/S`, after a full backup. No source
  build was needed (src is Rust core + nx frontend + VSCode extension - a
  source build would have needed Rust, Node and VS for the same binaries).
- Script: `scripts\2026-10-08-windhawk-2a6-update.ps1`
  (`-Audit` / `-Backup` / `-Install` / `-Rollback`), wrapper
  `scripts\2026-10-08-windhawk-2a6-lockrun.ps1`, detached launcher
  `scripts\2026-10-08-windhawk-2a6-detach.ps1`.

## Verified state (13:01-13:10, 2026-10-08)

- `windhawk.exe` FileVersion `2.0.0-alpha.6`; installer exit 0.
- `windhawk.ini` now `EnginePath=Engine\2.0.0` (32/64/arm64 + engine.ini);
  old `Engine\1.7.3_2` left in place for rollback.
- New mod compiler toolchain in `Compiler\` (mingw: x86_64/i686/aarch64).
- Mods recompiled 13:01:06 (`windhawk-mod-shim.dll`, `libunwind.whl`,
  `libc++.whl` + 463 mod DLLs across 64/32-bit).
- Registry: 119 mod keys before = 119 after. Key mods enabled:
  styler rev 23, translucent-flyouts 0.6.7_28, visualizer 1.3.1_4,
  taskbar-styler 1.10.
- `WINDHAWK_USE_VSCODIUM_UI=1` set machine-wide so the styled legacy UI stays
  the default. To see the new 2.0 UI instead, delete that env var (or use the
  tray menu) - the 2.0 release notes describe the tray toggle.
- Engine running: 5 windhawk processes.

## The styler UI situation (for windhawk-styler-fix)

The installer rewrote `C:\Program Files\Windhawk\UI`: **168 files changed**
(see `backups\2026-10-08\windhawk-2a6-update\ui-changed.txt`), 60 of them in
the styler runtime manifest's scope. Post-install `VSCodium.exe` hash does NOT
match the old stock 1.74.2 original hash - 2.0's legacy UI is a different
VSCodium payload - so the automatic re-apply of the prepared Electron 28.3.3
runtime was correctly SKIPPED (would have corrupted the new base). The styler
mod rev 23 is still installed and enabled; if the styled native-mode look is
wanted on 2.0, the runtime needs a fresh re-apply against the new payload.

## Racing attempts (context for the log)

Two install attempts interleaved in `phase-log.txt`: the first (12:52) hung in
the old `windhawk.exe -exit -wait` while styler-fix's reload was finishing,
survived a caller kill, and completed everything (12:59:41-13:01:17). The
second (13:01, detached launcher) lost the race at its stop stage, logged
`install-failed`, and never ran the installer - harmless; its
`install-error.txt` is that race, not a real failure. The `-exit -wait` hang
is why the script now uses a bounded stop.

## Backup / rollback

- `backups\2026-10-08\windhawk-2a6-update\`: registry export
  (`windhawk-registry-HKLM.reg`), full copies of `Program Files\Windhawk`
  and `ProgramData\Windhawk` (`ProgramFiles-Windhawk\`,
  `ProgramData-Windhawk\`), UI hash snapshot (`ui-hashes-before.json`),
  `receipt.json`, `backup-manifest.json`.
- Rollback: elevated
  `scripts\2026-10-08-windhawk-2a6-update.ps1 -Rollback`
  (stops engine, mirror-restores both dirs, reg delete+import, starts 1.7.3,
  removes the env var). Volatile files skipped during backup (locked
  ModsWritable/UIData caches, robocopy logs per subtree) are re-creatable and
  not needed for rollback.
- `install-error.txt` in the backup dir documents the second attempt's race,
  not a fault of the installed build.

## Release-note highlights for 2.0.0-alpha.6

Mod reviews, settings annotations (`$format: colorRgb`, hotkey, slider,
`$dynamicSelect`, `$showIf`...), `windhawk://` links, dark native dialogs,
fixed a process-skipping regression from alpha 4. Upgrading from 1.x
preserves settings and mods (confirmed here).
