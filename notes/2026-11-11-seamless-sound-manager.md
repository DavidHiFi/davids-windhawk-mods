# Seamless Sound Manager 1.0.0: Sound Manager ported to a Windhawk mod (2026-11-12)

Owner asked for a full port and replacement of ORelio's Sound Manager app as a Windhawk tool
mod, with the universal settings window (Launchpad engine and glass) and every preset.

## What was built

- Mod `local@seamless-sound-manager` 1.0.0 (source @id `seamless-sound-manager`), runs in
  windhawk-mod.exe. Work folder `work\2026-11-11-sound-manager\` (src: engine `core.cpp`,
  pages `pages.cpp`, generator `gen.py`, joiner `assemble.py`, test copy `harness\`).
- Engine: all 31 events, scheme setup/apply into `HKCU\AppEvents` (scheme `SoundManager`),
  same data folder as the app (`%APPDATA%\SoundManager`), .ths/.zip/.soundpack import,
  .ths/.themepack export, Media Foundation conversion (30 s cap), scheme picture, system
  schemes, reinstall/uninstall, startup/logon/logoff/shutdown/lock/unlock sounds, optional
  imageres startup-sound patch (off, admin only), 161 presets downloaded on demand to
  `%LOCALAPPDATA%\SeamlessSoundManager\presets`.
- Settings window pages: Scheme, Sounds, Presets, System, Look, About. Glass matches the
  Launchpad reference (settings-material parts all equal). Shared tool tray menu look
  copied in by `assemble.py` from the live Mixer block.
- Settings mirror into `SoundManager.ini [Main]`; first run migrated the app's INI values.

## Changes on the PC (old -> new)

| Item | Old | New |
|---|---|---|
| Task `\SoundManager-S-1-5-21-...-1001` | Ready/Running, app `--bg-sounds` | Disabled, app stopped (still installed) |
| `HKCU\Software\Classes\ths_auto_file` / `soundpack_auto_file` | icon from app folder, verb `import` -> SoundManager.exe "%1" | icon mmsys.cpl,0, verb `open` -> wscript import.js "%1" (inbox picked up by the mod) |
| `HKCU\AppEvents\Schemes` | SoundManager | SoundManager (unchanged; same Media files) |
| Windhawk mod | none | local@seamless-sound-manager 1.0.0 enabled |

Backups: `backups\2026-11-12\sound-manager\` (task.xml, the four class keys, AppEvents.reg).
The mod also keeps its own one-time association backup in
`%LOCALAPPDATA%\SeamlessSoundManager\backup\`. The app's `SoundManager.ini` was not copied by
the install script (path not found in the elevated run); the mod rewrote it with the same
values: PatchStartupSound=False, UseDefaultOnMissingSound=True, ConvertProprietaryFiles=False,
PreferStartupSoundOnLogon=False, no disabled events.

## Rollback

`Invoke-Elevated.ps1 -File scripts\2026-11-11-seamless-sound-manager.ps1 -ArgumentList -Rollback`:
removes the mod, re-imports the class keys, enables the task and starts the app.
Full sound state: `reg import backups\2026-11-12\sound-manager\AppEvents.reg`.

## 1.0.1 (2026-11-12, 2:47 pm)

- Settings engine refreshed from Launchpad's live source (`scripts\settings-engine-sync.py adopt`):
  footer real blur, and the native title bar now follows only "Native Windows title bar" (the
  "Title bar buttons" setting is gone, as in every other settings-engine mod). Default is the
  window's own title bar. `settings-material.py check`: ok.
- The settings window is tall and narrow here because Seamless Window Manager tiles it like any
  app window (same for Launchpad's settings). Not a mod fault.
- Published: DavidHiFi/davids-windhawk-mods 09a208d (source, preview, manifest); the preview's
  raw URL returns 200.

## Checks

- Syntax check and the test copy build: no errors. Test copy rendered all pages from the
  real scheme (harness\shots).
- Live: helper running, scheme still `SoundManager`, event paths point at the same Media
  files, file types switched, LastBootTime.ini untouched (no replayed boot sound).
