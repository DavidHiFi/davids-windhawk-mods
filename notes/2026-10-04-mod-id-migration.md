# 2026-10-04 mod id migration

Two local mods moved to ids without the owner's name. The code is unchanged from
the installed versions. Only the header and readme differ, and a line compare
after the readme block found no differences.

| Old id | New id | New version |
| --- | --- | --- |
| `local@davids-audio-visualizer` (1.1.0) | `local@taskbar-audio-visualizer` | 1.2.0 |
| `local@explorer-font-changer-davidhifi` (1.0.1) | `local@shell-font-changer` | 1.1.0 |

## What moved

- Visualizer: `Mods\<id>` with all 49 Settings values,
  `ModsWritable\<id>\LocalStorage` (`captureEndpointId`), and
  `mod-storage\<id>\diagnostic.log`.
- Font changer: `Mods\<id>\Settings` (`font.name` = `FiraCode Nerd Font`). It
  has no LocalStorage and no mod-storage folder.
- Neither mod contains an old-id literal outside `WH_MOD_ID`. Some cosmetic
  strings are left as they were: the visualizer's thread names
  (`DavidsAudioVisualizer-Capture` and `-Render`), its picker window class
  (`DavidsAudioVisualizerCapturePicker`), and the font changer's log line
  ("DavidHiFi font changer initialized"). None of them affects the new ids.

## How

Both mods were built x64 and x86 with the bundled clang against engine
`1.7.3_2`, using `-DWH_MOD` only and the id in a force-included header. Build
output is in `work\id-migrate\build`. `scripts\2026-10-04-mod-id-migration.ps1
-Install` ran elevated through a `.cmd` wrapper. It backs up the old keys and
files, copies the source and DLLs, clones the keys with `reg copy /s`, disables
the old id, then enables the new one. The engine picked up both changes live,
with no `windhawk.exe -restart`.

## Evidence

- Installed DLL and source hashes match the build and `work\mod-polish-20261004\src`.
- The new keys have `Disabled=0`, and the old keys have `Disabled=1`. The
  Settings values are identical.
- There is exactly one visualizer tool process: `windhawk.exe -tool-mod
  "local@taskbar-audio-visualizer"`. No process remains under the old id.
- The strip is visible in `reports\2026-10-04-mod-id-migration\taskbar-after.png`
  at the same position as in `taskbar-before.png`. The taskbar is at the top of
  the screen.
- All four explorer.exe processes, ShellHost and StartMenuExperienceHost load
  `local@shell-font-changer_1.1.0_1.dll`, and none of the explorer processes
  still loads the old DLL. SearchHost and ShellExperienceHost still map the old
  DLL because every one of their threads is suspended. The engine swaps the DLL
  when they resume.
- Receipt: `reports\2026-10-04-mod-id-migration\receipt.json`. Install
  transcript: `install.log` in the same folder.

## Rollback

Run `scripts\2026-10-04-mod-id-migration.ps1 -Rollback` elevated, through a
`.cmd` wrapper. It disables the new ids and re-enables the old ones. The old
keys, sources, DLLs and storage were left in place. Full copies are in
`backups\2026-10-04\mod-id-migration\<old-id>\`: `.reg` exports, source, every
old DLL, and mod-storage.
