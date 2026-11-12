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

## Hardened for every mod (2026-11-12, 1:05 am)

The owner asked for every mod, present and future, to use this settings GUI and glass.

- `scripts\settings-material.py`: `check` lists every mod on the settings engine as ok or OFF
  against the live Launchpad source; `stage <id> <out>` copies in the reference glass block, tint
  and fade, and bumps the patch version.
- `scripts\Install-StagedMod.ps1`: installs a staged source only if the live one is unchanged
  since staging (hash). Backs up the source and registry key to `backups\settings-material\`.
  Run it through heavy.py with `pwsh` (Windows PowerShell under the gate could not load Get-FileHash).
- Installed: Color Picker 1.1.2 (was 1.1.1). Media Player 1.10.9 (was 1.10.8). The first try was
  refused: its settings had an unquoted `(Suggested: 2)` that the newer CLI rejects. Now quoted.
- Not touched, because other threads own them and were told: Crash Watch and Key Click (both OFF).
  Taskbar AI Usage Plus has its own non-engine window (follow-up).
- Hardened in: memory `universal-settings-gui.md`, `docs\settings-gui-standard.md`, global
  agent rules (`AgentRules\global.md`, backup `.bak-20261112-*`, rendered to every agent).
- Threads told to build on the new versions: crash popup, key click, color picker, menu pill,
  Halo Launcher, mixer, black-areas blur, clipboard.
- Rollback: install `backups\settings-material\<id>-<stamp>.wh.cpp` with windhawk-cli; rules
  file from its `.bak`.

## Engine sync and footer real blur (2026-11-12, 8 am)

The owner asked for no small inconsistencies across the settings windows and real blur in the
footer dock.

- Found with `work\2026-11-11-settings-material\engine-drift.py` (set `DRIFT_SRC` to a folder of
  staged copies to compare those): Color Picker, Media Player, Crash Watch, Key Click and
  AutoClicker ran a frozen older Launchpad engine. Missing: Support and About card hover (no hit
  ids 3700/3800), resting box edge and `kSetBoxFill`, the blurred footer pill and its new
  buttons, the rail resize edge, the native-buttons and mouse-leave fixes.
- Footer: Launchpad blurred the rows under the pill but painted mantle at 0.85 over it, so the
  blur hardly showed. Now 0.58 in glass mode, the same as the rail dock (Launchpad 2.4.7).
- `scripts\settings-engine-sync.py`: `build` copies a generator to a sandbox, gives it the
  Launchpad settings section as its template, runs its own gen.py and splices the new block into
  the installed source (the rest of the mod stays as live). `adopt` refreshes a generator's
  template (backup beside it).
- Rebuilt and compiled offline: Key Click 1.0.2, Color Picker 1.1.4, Media Player 1.10.10.
  Key Click ships from its own thread (same settings block, plus the Mixer tray menu look).
  Dictate 1.1.5 and Clipboard 1.3.7 only needed the footer line (their engines were current;
  Dictate keeps its scrolling dropdown). After: only mod-specific functions differ.
- gen.py fix in Color Picker and Media Player: the new engine reads `settingsTitleButtons` twice.
- Templates refreshed: Color Picker, Media Player, Key Click (`.bak-20261112-0812`).
- Left to owners (told): Crash Watch (crash popup thread; its gen.py must skip the old glass
  patch when the template has it), AutoClicker (autoclicker-160), Halo Launcher.
- Install: `work\2026-11-12-engine-sync\install.ps1`, hash-guarded, log beside it.

## Native title bar only when asked (2026-11-12, 10 am)

Owner: with "Native Windows title bar" off, the settings windows still showed the Windows title
bar (title bar mod pill and dots).

- Cause: `nativeTitle = nativeSettingsTitleBar || settingsTitleButtons != "builtin"`, and
  "Windows buttons" was the default, so every mod forced the native title bar. AutoClicker and
  Listary had the older hybrid instead (Windows buttons on the built-in title bar, which draws
  dull buttons with no hover, notes 2026-10-18).
- Old: two settings (Native Windows title bar, Title bar buttons). New: one switch. Off = the
  window's own title bar and buttons. On = Windows draws both. `settingsTitleButtons` removed
  (YAML, row, reads). Spec updated.
- Installed on live sources: Launchpad 2.4.8, Clipboard 1.3.8, Dictate 1.1.6, Color Picker 1.1.5,
  Media Player 1.10.11, Key Click 1.0.3, Crash Watch 1.2.1, AutoClicker 1.6.1, Listary 1.1.1,
  Taskbar AI Usage Plus 1.2.1. Crash Watch and AutoClicker stopped on compile; restarted.
- Taskbar AI Usage Plus: its own thread reinstalled its 1.2.1 one minute later, so it still has
  the old logic. Handed over: `python work\2026-11-12-native-title\stage.py local@taskbar-ai-usage-plus`.
- Color Picker shipped `nativeSettingsTitleBar: true` as its default (every other mod: false),
  which is why its window had the native title bar. Default now false (1.1.7, generator head too).
- Stored switch turned off in Launchpad (was 1 since at least 2026-11-11) and Color Picker (was 1
  from the wrong default). Old 1, new 0. Undo: import
  `backups\settings-material\<id>-key-<stamp>-native.reg`.
- Generators: `settingsTitleButtons` dropped from Color Picker and Media Player gen.py; templates
  re-adopted; a dry rebuild matches live apart from the version line. Key Click's spec.py
  (line 120) is its thread's to drop.
- Proof: reports\2026-11-12-native-title-both.png (Launchpad with the switch on: Windows title
  bar; Clipboard with it off: built-in title bar).
- Rollback per mod: install `backups\settings-material\<id>-20261112-1xxx.wh.cpp` with
  Install-StagedMod or windhawk-cli.
