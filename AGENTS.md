# Copying this Windhawk setup with an agent

This file is the runbook for an AI agent (OpenCode, Claude Code, Codex or
similar) tasked with copying this Windhawk setup onto a Windows 11 machine.
Work through it in order and verify at the end. Ask the user only for the
things marked ASK.

## What the target state is

[manifest.json](manifest.json) is the source of truth: one entry per mod with
its version, license, origin (`local` or `catalog`), the source file in this
repo, and whether it is enabled. The end state is "the same mod set with the
same versions and the same settings".

## 1. Install Windhawk

Install Windhawk 2.0 or newer from [windhawk.net](https://windhawk.net). The
`.reg` imports and the apply script need an elevated shell, so open one and
keep it.

## 2. Install the catalog mods

For every entry in `manifest.json` with `"origin": "catalog"`, install the mod
from `https://windhawk.net/mods/<id>`. Opening that URL (or
`start windhawk://install/<id>`) offers the install in Windhawk's own window.
If that route fails, the exact source that runs on the source machine is in
`mods/catalog/<id>.wh.cpp`: in Windhawk, choose **Create a new mod**, paste
the file, **Compile**. Then set its version to match the manifest entry.

## 3. Install the local mods

For every entry with `"origin": "local"`, open `mods/local/<name>/`, copy the
`.wh.cpp` into a new mod in Windhawk and compile it the same way. Some folders
carry extra files (helper programs, modid headers, `Build.ps1`); read the
folder's README before building those.

## 4. Apply the settings

From an elevated PowerShell in the repo root:

```powershell
powershell -ExecutionPolicy Bypass -File tools\Apply-WindhawkSettings.ps1 -Audit
powershell -ExecutionPolicy Bypass -File tools\Apply-WindhawkSettings.ps1
powershell -ExecutionPolicy Bypass -File tools\Apply-WindhawkSettings.ps1 -IncludeAppSettings -RestartEngine
```

`-Audit` lists every difference and writes nothing. The second run writes
per-mod state and settings. The third imports the app and engine `.reg` files
and restarts the engine. Reopen the Windhawk window afterwards.

## 5. Copy the loose files

- `mod-storage/` to `C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage\`
- `editor/settings.json` to `C:\ProgramData\Windhawk\UIData\user-data\User\settings.json`

## 6. Verify

1. The installed mod list in Windhawk matches `manifest.json`: same ids, and
   versions at or above the manifest's.
2. `tools\Apply-WindhawkSettings.ps1 -Audit` now reports zero differences.
3. Spot-check two or three mods visually (taskbar, menus) after a reboot or an
   Explorer restart.

## Rules

- Disable a catalog original before enabling its Plus replacement; the manifest
  marks which entries are enabled on the source machine, and disabled ones can
  be installed but left off.
- Sign-ins and API keys are deliberately blank in this repo. ASK the user to
  sign in through each mod's own UI (dictate AI keys, quota mod accounts,
  weather location) rather than trying to restore them.
- Do not import anything from `settings/` that is not listed above.

## Refreshing this repo

To refresh the snapshot after mods or settings change, on the machine with
Windhawk:

```powershell
powershell -ExecutionPolicy Bypass -File tools\Build-Repo.ps1
```

From any other machine, dump the state first, move the export folder over, and
rebuild from it:

```powershell
powershell -ExecutionPolicy Bypass -File tools\Dump-WindhawkState.ps1 -OutPath H:\tmp\wh-export
powershell -ExecutionPolicy Bypass -File tools\Build-Repo.ps1 -FromExport H:\tmp\wh-export
```

Both keep the repo an exact mirror: mods that are no longer installed are
removed, and secret-looking values are blanked before anything is written.
