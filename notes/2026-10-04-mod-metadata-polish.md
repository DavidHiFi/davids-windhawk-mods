# 2026-10-04 Mod metadata polish

Ten local mods got the same treatment: a clean id and name with no personal
names, a one-line description, a README with feature bullets and a preview
image, and a matching embedded readme. The Window Manager monitor-move fix and
an install-snapshot refresh rode along.

## What each mod ended up with

| Folder | @id | Display name |
| --- | --- | --- |
| alt-snap-drag | alt-snap-drag | AltSnap |
| better-volume-mixer-plus | better-volume-mixer-plus | Better Volume Mixer Plus |
| npp-taskdlg-textcolor | npp-taskdlg-textcolor | Notepad++ Dark Dialog Fix |
| shell-font-changer | shell-font-changer | Shell Font Changer |
| taskbar-ai-quota-opencode | taskbar-ai-quota-opencode | Taskbar AI Quota Bars Plus |
| taskbar-audio-visualizer | taskbar-audio-visualizer | Taskbar Audio Visualizer |
| taskbar-system-info-weather | taskbar-system-info-weather | Taskbar System Info Plus |
| taskbar-weather | taskbar-weather | Taskbar Weather |
| translucent-flyouts | translucent-flyouts | Translucent Flyouts |
| window-manager | window-manager | Window Manager |

Descriptions run 63 to 98 characters, all single line. `@author DavidHiFi`,
`@github` and `@homepage` are set on every one. Verification output:
`reports\2026-10-04-mod-metadata-polish\final-verification.json` (zero problems
across id, name, description, README, embedded readme, preview file).

## Previews

Ten files in `davids-windhawk-mods\media\previews\`: three GIFs
(`alt-snap-drag.gif`, `taskbar-audio-visualizer.gif`, `window-manager.gif`) and
seven PNGs. Capture table:
`work\mod-polish-20261004\previews-scratch\previews.md`.

All ten raw URLs returned HTTP 200 after the push.

## Publishing

Fork commit `0275dce` ("Rename the personal-named mods and give every mod a
preview") carries the renames and the preview assets.

Seven open PRs to `ramensoftware/windhawk-mods`, all updated
2026-10-04T14:02-14:03Z and all still open:

- #5881 window-manager 1.1.0
- #5835 taskbar-system-info-weather 1.2.3
- #5834 taskbar-weather 1.4.0
- #5815 npp-taskdlg-textcolor 1.0.1
- #5814 taskbar-ai-quota-opencode 1.6.5.1
- #5813 alt-snap-drag 1.2.2
- #5785 translucent-flyouts 0.6.6

Three mods are local only and were never submitted: better-volume-mixer-plus,
shell-font-changer, taskbar-audio-visualizer.

## Old ids removed from the machine

`local@david-window-pack`, `local@davids-audio-visualizer` and
`local@explorer-font-changer-davidhifi` are gone from the registry and from
`C:\ProgramData\Windhawk\ModsSource`. Receipt:
`reports\2026-10-04-old-mod-cleanup\receipt-remove.json`.

## Window Manager fix

The maximized and borderless monitor-move bug is fixed and installed as
`local@window-manager_1.1.0_2.dll`. Root cause, workspace-offset maths and the
install record live in `notes\2026-10-04-window-manager.md`.

The live mod source carried two readme lines the repo already had, so
`scripts\2026-10-04-wm-readme-sync.ps1` copied the repo file over
`ModsSource\local@window-manager.wh.cpp`. Receipt:
`reports\2026-10-04-mod-metadata-polish\receipt-wm-readme-sync.json`.

## Visualizer strings, revision 3

Three leftover strings still named the mod this one was forked from:

- The settings dialog body opened with "Tourne'Table found something worth
  flagging in your settings." (that box is on by default, so users hit it when
  a setting fails to parse).
- Thread descriptions read `DavidsAudioVisualizer-Capture`,
  `DavidsAudioVisualizer-Render` and `TourneTable-InputHooks`.
- The capture-picker window class was `DavidsAudioVisualizerCapturePicker`.

All five lines now use Taskbar Audio Visualizer wording. Rebuilt both
architectures with `mods\local\taskbar-audio-visualizer\Build.ps1` (WH_MOD only,
id through a force-included `modid.h`, engine lib 1.7.3_2) and installed
`local@taskbar-audio-visualizer_1.2.0_3.dll`.

Install order, which is what keeps the helper process from holding two copies
of the mod: export the registry key, copy the rev2 DLLs and source to
`backups\2026-10-04\mod-polish-final`, stage rev3, set `Disabled=1`, wait for
the old `-tool-mod` process to exit, copy the source and both DLLs, point
`LibraryFileName` at rev3, bump `SettingsChangeTime`, restore `Disabled`.

Independent checks after the run: registry reads
`local@taskbar-audio-visualizer_1.2.0_3.dll` with `Disabled=0`; the installed
64-bit hash `F9A33F7284B0D686DDDECEF023819705B02CFCD17E2CF0F009E4FE865E1CA255`
matches the build; one tool process, PID 26160, started 22:44:37; mod-status
files for the new revision were written 22:44:37-38; string probes in the
installed DLL find the new dialog body, the new thread names and the new class
name, and no longer find the old ones.

Left alone: the internal `VizColorMode::Tourne` enum (it has no settings option,
so no user sees it) and the readme notes that name Tourne'Table as a mod to
disable first, which is accurate.

Receipt: `reports\2026-10-04-mod-metadata-polish\receipt-visualizer-rev3.json`.

Audit and rollback:
`powershell -File scripts\2026-10-04-visualizer-rev3.ps1 -Audit` prints the live
library, the string probes, the tool-process count and whether the live source
still matches the repo; it changed nothing when run at 22:55. `-Rollback`
points the mod back at the revision 2 DLLs kept in the backup folder, through
`scripts\2026-10-04-visualizer-rev3-rollback.cmd`, which logs to
`reports\2026-10-04-mod-metadata-polish\rollback-visualizer-rev3.log`.

A screen capture at 22:52 shows the spectrum drawing on the taskbar again:
`reports\2026-10-04-mod-metadata-polish\screen-after-rev3.png`.

## Install snapshot refreshed

`davids-windhawk-mods\tools\Build-Repo.ps1` ran at 22:47, commit `a5dcb5e`.
The manifest now records 111 installed mods, 107 enabled, and ten local entries
(nine installed plus the offline center-titlebar-fork). Twelve catalog sources
arrived with tonight's installs, from `close-explorer-on-esc` to
`vlc-discord-rpc`.

Nine catalog sources no longer have an installed mod and stay in
`mods\catalog` as extras the script only warns about: alt-drag,
better-volume-mixer, explorer-folder-bookmarks-bar, explorer-font-changer,
explorer-visual-tweaks-dark, snap-commander, taskbar-ai-quota,
taskbar-system-info, tourne-table-desktop-audio-visualizer.

## Finding: local@alt-snap-drag was uninstalled

At the 21:57 snapshot `local@alt-snap-drag` was installed and disabled. By 22:21
its registry key, its `ModsSource` file and its DLL were gone, along with eight
catalog mods the same evening. No script in this run removes it:
`scripts\2026-10-04-old-mod-cleanup.ps1` only targets the three old ids above,
and the pattern fits a cleanup in the Windhawk UI.

It was not reinstalled. Window Manager covers the same Alt+drag behaviour for
every process, its drag module is loaded into 190 processes, and the source and
PR #5813 both remain. The catalog PR is unaffected either way.

## Also worth knowing

- `center-titlebar-fork` is still a prototype: no README, no preview, and the
  root README lists it as unfinished.
- The GitHub account flagged on 2026-09-30 answers again.
  `github.com/DavidHiFi`, the repo page and `api.github.com/users/DavidHiFi`
  all return 200 from this machine, and the ten preview URLs return 200. No
  Actions run or `/ai-review` reply has been checked since the flag.
- `windhawk.exe -restart` was not used; the workspace rule forbids it because
  it also restarts explorer.

## Files

- Receipts: `reports\2026-10-04-mod-metadata-polish\` (install, final install,
  window-manager readme sync, visualizer rev3, final verification).
- Pre-change copies: `backups\2026-10-04\mod-polish-final\` (rev2 DLLs, rev2
  source, registry exports).
- Build output: `work\mod-polish-20261004\build-visualizer-rev3\`.
- Install script and log: `work\mod-polish-20261004\install-visualizer-rev3.ps1`
  and `.log`.
- Audit and rollback: `scripts\2026-10-04-visualizer-rev3.ps1`, wrapper
  `scripts\2026-10-04-visualizer-rev3-rollback.cmd`.
- Style rules for future mods: `docs\mod-style-guide.md`.
