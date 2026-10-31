# Windhawk Configuration workspace

Home for all Windhawk work on this machine: installed mods and settings, taskbar and shell themes, local or forked mod development, and the engine. General Windows configuration stays in `H:\System Configuration`. Machine-wide rules (freeze rules, coop, replies, proof) are global; do not copy them here.

## Scope

- Windhawk engine, installed mods, mod settings, local or forked mod development.
- `windows-11-taskbar-styler` configs and other appearance or shell mods.
- `Windhawk\` (mod sources, builds, historical backups) and `davids-windhawk-mods\` (public fork repo DavidHiFi/davids-windhawk-mods).
- Records: `notes\`, `reports\`, `scripts\`, `backups\`, `docs\`.
- Not here: WinLaunch Enhanced (retired 2026-10-24, do not resume). Its launcher is now the mod Fullscreen Start Plus.

## Engine facts

| Thing | Where |
| --- | --- |
| Install | `C:\Program Files\Windhawk\windhawk.exe` |
| Data | `C:\ProgramData\Windhawk\` (`ModsSource\`, `Engine\Mods\{64,32}\`) |
| Mod settings | `HKLM\SOFTWARE\Windhawk\Engine\Mods\<mod-id>\Settings` (structured registry values, not YAML) |
| Apply a settings change | write the registry elevated and bump `SettingsChangeTime` (REG_DWORD, unix seconds) on the mod key; the mod hot-reloads on the marker |
| Engine restart | `windhawk.exe -restart` is banned: it restarts Explorer too. Reload per mod instead. A full engine restart happens only when the user asks for that exact action, and only with no T3 Code window live |
| Service start | Starting the stopped service restarts Explorer once a few seconds later (Explorer TreeItem Tweaker Plus). Expected, not a crash |

## Safety

- Back up first: `reg export` the mod key and copy any files into `backups\<date>\...`, and record the original values.
- Write elevated, then verify by reading the value back.
- A mod the owner turned off stays off. Never re-enable it, even briefly, without the owner asking for that exact mod.
- tray-utility-customizer is uninstalled. Never install, suggest or re-enable it.
- caption-buttons-customizer is cleared. Do not blame or disable it for freezes.
- translucent-windows is on the owner's full look: acrylicblur on the 30 pre-freeze apps, `IncludeExcludeCustomOnly=1`, global style none. Never give it `*`, add apps, or switch to the light acrylicsystem setup without the owner. Never fork it again.
- Every blur app must stay in window-borders' Exclude list.
- Borders come only from the `local@window-borders` 2.0 tool mod, run by Windhawk in its own `windhawk-mod.exe` host. `window-ring.exe` is retired. Never run both. A "Windhawk mod" is always a real mod, never a background exe.
- translucent-flyouts was removed for good. Never reinstall or reference it.
- theme-tool-plus does not re-apply the theme on load (`applyOnSettingsChange=0`). settings-styler-plus runs in SystemSettings.exe and ApplicationFrameHost.exe.
- Start Windhawk with `scripts\2026-10-25-windhawk-watched-start.ps1` (freeze check, start, 20-minute kill switch). `scripts\Test-WindhawkFreezeGate.ps1` is a quick check, not a gate.
- No watchdog tasks that keep a mod off or police a ban. Remove the mod once and write the rule here.
- Prefer scoped targets (`Include=explorer.exe`) over all-process injection.
- No debloat scripts, registry cleaners or blanket tweaks. One change at a time, with a visible before and after.
- Verify visual changes by screenshot (tray, taskbar), not by assuming the write landed.

## Traps (full list in `docs\traps-and-tips.md`)

- `-DWH_EDITING` builds no-op Wh_* stubs; production mods build with `WH_MOD` only.
- PowerShell 5.1 strips quotes from `-DWH_MOD_ID=L"..."`; pass the id via a force-included header.
- The engine keeps loaded DLLs mapped; install a new revision and point `LibraryFileName` at it.
- Mods do not initialize in console-subsystem processes (e.g. `powershell.exe`).
- PUA glyphs in a BOM-less `.ps1` are misread by PS 5.1; build them with `[char]0xE971`.
- `Start-Process -Verb RunAs` quoting traps: `H:\System Configuration\agent-tools\AgentRules\machine-gotchas.md`.

## Conventions

- Preview (alpha) engine updates: load the `windhawk-alpha-update` skill and run `scripts\windhawk-alpha-update.ps1` (`-Check`, `-Prepare`, `-Launch`, `-Rollback`). Never update by hand. The engine restart waits for T3 Code to close, so ask the user to close it.
- Every mod we write or fork follows `docs\mod-style-guide.md`. Before any install or publish: `@author` starts with `DavidHiFi`; `@donateUrl https://ko-fi.com/DavidHiFi` is set; text passes `humanizer`; the readme shows a real preview.
- Every applied change gets a script with `-Audit` / `-Install` / `-Rollback` when practical, a backup, a receipt JSON and a note. ISO dates in filenames.
- Singleton resources for coop are in `.agent-coop.json` (`windhawk-engine`, `backups`, `packages`).
- Old absolute paths resolve through junctions in `H:\System Configuration`.

## Reference

Moved detail (reliability playbook, retired launcher, mod state history and evidence, traps, release checklist, record placement): `notes\2026-10-31-agents-reference.md`.
