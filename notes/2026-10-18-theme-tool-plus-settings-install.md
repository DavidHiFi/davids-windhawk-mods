# Theme Tool Plus: settings overhaul installed as 1.0.2, revision 8 (2026-10-18)

Canonical copy after install: H:\Windhawk Configuration\notes\2026-10-18-theme-tool-plus-settings-install.md

## What was wrong

The settings-tab rewrite (hotkey scrapped, 21 settings, humanized names) was saved
to the workspace source at 7:39 PM but never compiled. Windhawk was still running
1.0.1 revision 7 from 4:56 PM, so none of the new settings existed in the
installed mod. The rewrite had also been written on a pre-1.0.1 copy, so the
"Unsaved Theme" skip (applying that theme re-saves Custom.theme) was missing.

## What was done (8:19 PM)

- Restored the Unsaved Theme skip in both paths (picker list + apply-by-name),
  version bumped to 1.0.2. Pre-patch source backed up first.
- Rebuilt x64 + x86: BUILD OK (build log in the temp build folder).
- Installed revision 8 under the desktop lock: INSTALL OK. Registry read back:
  LibraryFileName `local@theme-tool-plus_1.0.2_8.dll`, Version 1.0.2,
  Disabled 0. DLL SHA-256 on disk matches the build (x64 B125183B…, x86 8767772B…).
- Mod hot-reloaded in the included processes; log at 8:19:24 PM shows
  `RegisterHotKey ok mods=0x0 vk=0x0` — no hotkey is registered; the picker and
  apply flow are settings-driven only (21 settings, lines 63–130 of the
  installed source).

## Records

- Backups: `H:\Windhawk Configuration\backups\2026-10-18\theme-tool-plus\`
  (pre-patch source, registry exports before install). Old revisions 1–7 of the
  DLLs remain on disk as rollback copies.
- Rollback: `theme-tool-plus-install.ps1 -Rollback` (disables this mod,
  re-enables uxtheme-hook), or point LibraryFileName back at
  `local@theme-tool-plus_1.0.1_7.dll`.
- Patch script: `patch-unsaved-fix.ps1` in this folder (wrapper `ttp-run.ps1`
  ran patch + build + locked install elevated).

## Not verified

- The settings tab itself was not screenshotted: that needs clicks inside the
  Windhawk window and no UI automation was used this session. Verified instead
  in the installed source (settings block), the registry and the DLL hashes.
