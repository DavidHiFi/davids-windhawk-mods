# Universal settings window, ports (2026-11-11)

Spec: docs\settings-gui-standard.md. Engine: Seamless Launchpad 2.4.3.

## Seamless Dictate 1.1.0

- Old: 1.0.7 (legacy SettingsWindow, library local@seamless-dictate_1.0.7_435782.dll).
  New: 1.1.0 (local@seamless-dictate_1.1.0_542893.dll). Host: windhawk-mod.exe (tool mod).
- Changed: the tray icon, its "Settings..." item and the tray click open the new window
  (pages Dictation, Speech, Shortcuts, Providers, Look, About; own thread). Every setting keeps
  its key and storage (Config JSON in mod storage; showTrayIcon in Windhawk settings).
- Lists (custom styles, dictionary, app styles, history, keys, setup wizard) open the older window
  from link rows (WM_APP_LEGACY_PAGE). First-run wizard and the key-error window still use it.
- New Windhawk settings: settingsGlass, nativeSettingsTitleBar, settingsTitleButtons,
  settingsTrayIcon (tray shows only when it and showTrayIcon are both on; saving it writes both).
- Hotkey capture switches the overlay's global hotkeys off while recording a key, then back on.
- Source of record: work\2026-11-11-universal-settings\dictate (gen.py, assemble.py, build.py, live.py).
  Repo copy updated; old repo copy in backups\2026-11-11-dictate-settings.
- Proof: reports\2026-11-11-dictate-settings-<page>.png.
- Rollback: elevated run of scripts\2026-11-11-dictate-settings-install.ps1 -Rollback
  (installs the 1.0.7 source; backups, registry export and stored-source copy in
  backups\2026-11-11-dictate-settings).

## Seamless Clipboard Manager 1.3.0

- Ported by an earlier helper, live. The About header line was shortened at 7:10 am so the
  credits line no longer clips.
- Rollback: scripts\2026-11-11-clipboard-settings-install.ps1 -Rollback restores 1.2.6.

## Glass material fix (9 pm, 2026-11-11)

Problem: Dictate and Clipboard settings looked too bright, and went flat grey when unfocused.
Launchpad only looked right because Seamless Flyouts swaps its window to accent acrylic in Explorer.

- Old value (all three): system backdrop 3 (transient acrylic) with the frame extended.
- New value: backdrop 1 (none), full-window blur-behind, accent acrylic state 4 with tint D82E1E1E. The page tint is unchanged.
- Versions: Launchpad 2.4.4, Dictate 1.1.1, Clipboard 1.3.1.
- Patch: work\2026-11-11-settings-material\patch.py; staged sources in C:\Users\Public\settings-material.
- Install / rollback: scripts\2026-11-11-settings-material-install.ps1 -Mod <name> -Install | -Rollback (elevated).
  Backups of the installed sources and registry keys: backups\2026-11-11-settings-material, plus .bak-<stamp> beside each ModsSource file.
- Spec line updated in docs\settings-gui-standard.md.

## Glass material, second pass (10:30 pm)

The owner said the background was still too light. The first pass used accent flags 2, and that lifts
the page about 12 levels (Launchpad too: 40 went to 51 over white). Flyouts uses flags 0.

- Old value: accent flags 2 (Launchpad 2.4.4, Dictate 1.1.1, Clipboard 1.3.1).
- New value: accent flags 0 (Launchpad 2.4.5, Dictate 1.1.2, Clipboard 1.3.2).
- Over a white page, all three now read: page strip 40,40,50, sidebar 28,28,40, title bar 55,55,67, the same as the original Launchpad, focused or not.
- Rollback: scripts\2026-11-11-settings-material-install.ps1 -Mod <name> -Rollback goes back one step. The original sources are in backups\2026-11-11-settings-material.
- Dictate is a tool mod, and compiling it stops its process. Restart it with scripts\2026-11-10-tool-mod-restart.ps1 -Id local@seamless-dictate.

## Glass material, third pass (2026-11-12, 12:15 am)

Owner: still too light, make it match the Launchpad GUI. The launcher grid's material is a clear
blur (acrylic tint alpha 1) with a thin tint painted on top; the settings windows used a solid
D82E1E1E acrylic slab, which read as a light grey fill.

- Old: accent state 4, flags 0, colour 0xD82E1E1E; crust tint 0.42 with a fade from 0 under the title.
- New: accent state 4, flags 2, colour 0x012E1E1E (the grid's own call); crust 0.55, flat, no fade.
- Versions: Launchpad 2.4.6, Dictate 1.1.4, Clipboard 1.3.4.
- Live, side by side over the real desktop: page 21-23, sidebar 23-24 in all three (was 27-40).
- Proof: reports\2026-11-11-material-trio-v3.png.
- Rollback: scripts\2026-11-11-settings-material-install.ps1 -Mod <mod> -Rollback (elevated),
  or install backups\2026-11-11-settings-material\<mod>-installed-<stamp>.wh.cpp.

Collision, fixed: the first install of this pass (11:04 pm / 11:13 pm) was built from older
sources and briefly replaced newer work from other threads: Dictate's menu aim and menu pill
(their 1.1.3) and Clipboard's styled delete confirmation (their 1.3.3). Rebuilt from their
installed sources plus only the three material lines, then installed as Dictate 1.1.4 and
Clipboard 1.3.4. Threads working on Dictate or Clipboard: build on 1.1.4 / 1.3.4, not your
own 1.1.3 / 1.3.3 copies, or the dark material is lost.
