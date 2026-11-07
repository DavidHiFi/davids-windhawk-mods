# Windhawk Configuration workspace

Shared ricing defaults: for appearance work, read `H:\System Configuration\agent-tools\AgentRules\ricing-style.md` before editing. Current instructions and this workspace's established theme take precedence.

Home for all Windhawk work on this machine: installed mods and settings, taskbar and shell themes, local or forked mod development, and the engine. General Windows configuration stays in `H:\System Configuration`. Machine-wide rules (freeze rules, coop, replies, proof) are global; do not copy them here.

## Scope

- Windhawk engine, installed mods, mod settings, local or forked mod development.
- `windows-11-taskbar-styler` configs and other appearance or shell mods.
- `Windhawk\` (mod sources, builds, historical backups) and `davids-windhawk-mods\` (public fork repo DavidHiFi/davids-windhawk-mods).
- Records: `notes\`, `reports\`, `scripts\`, `backups\`, `docs\`.
- Not here: WinLaunch Enhanced (retired 2026-10-24, do not resume). Its launcher is now the mod Seamless Launchpad (`local@seamless-launchpad`, renamed from Fullscreen Start Plus 2026-11-02; keys helper `launchpad-keys.exe`, task SeamlessLaunchpadKeys).

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

- No questions or option lists in Windhawk fix replies. The owner pre-approves fixes inside these rules: pick the best fix, do it, verify it on screen and report. When a proven fix pattern exists for the same issue, apply it first; probe only a genuinely new symptom. A plan alone counts only when the owner says "plan only".
- Back up first: `reg export` the mod key and copy any files into `backups\<date>\...`, and record the original values. Write elevated, then read the value back.
- A mod the owner turned off stays off. Never re-enable it, even briefly, without the owner asking for that exact mod.
- tray-utility-customizer is uninstalled and translucent-flyouts is removed for good: never install, suggest or re-enable either.
- caption-buttons-customizer is cleared: do not blame or disable it for freezes. It was re-enabled 2026-11-07 4:08 am at the owner's request. The `\Windhawk-CaptionDwmGuard` task is disabled since then and its log is no longer written (`notes\2026-11-07-caption-buttons-reenable.md`).
- Fork recipe (owner rule, 2026-11-02): never patch someone else's mod under its original id. Fork it to `local@<name>-plus`, "<Name> Plus", `@author DavidHiFi, <original author>`, `@donateUrl`, a "Based on X by Y" line in the readme, then replace the original, keeping its settings. Never reinstall a mod that a fork or merge replaced.
- Borders come only from the `local@window-borders` tool mod. `window-ring.exe` is retired; never run both. A "Windhawk mod" is always a real mod, never a background exe.
- Start Windhawk with `scripts\2026-10-25-windhawk-watched-start.ps1`. `scripts\Test-WindhawkFreezeGate.ps1` is a quick check, not a gate.
- No watchdog tasks that keep a mod off or police a ban. Remove the mod once and write the rule here.
- Prefer scoped targets (`Include=explorer.exe`). No debloat scripts, registry cleaners or blanket tweaks. One change at a time, with a visible before and after, checked by screenshot.
- Change only the look the owner names. Taskbar asks count until they are on screen: earlier same-day items ship in the next round too.
- Never run a DBWIN / OutputDebugString listener on this PC (the PC reset at 12:42 pm on 10/31 while one ran).
- Per-mod state (Translucent Windows Plus, Terminal and FreeDictate title bars, Helium, Explorer title and drive highlight, media player look, docks): `CURRENT-STATUS.md`, section "Mod state and traps moved from AGENTS.md". Read it before touching one of those mods.

## Traps (full list in `docs\traps-and-tips.md`)

- `-DWH_EDITING` builds no-op Wh_* stubs; production mods build with `WH_MOD` only. PowerShell 5.1 strips quotes from `-DWH_MOD_ID=L"..."`; pass the id via a force-included header.
- The engine keeps loaded DLLs mapped; install a new revision and point `LibraryFileName` at it. Mods do not initialize in console-subsystem processes.
- Tool mods (`windhawk_tool_mod.h`) are built only with `windhawk-cli.exe mod compile <id>` (elevated); a hand-built DLL crashed the host. The compile deletes the previous DLL, so rollback means recompiling the old source. From a script, read its stderr asynchronously or a big compile deadlocks.
- Patch `.wh.cpp` sources with Python bytes/UTF-8 and write non-ASCII as `\u` escapes; build PUA glyphs in `.ps1` with `[char]0xE971`. A PS 5.1 round trip shipped broken text.
- Dock-mod recompile: disable the ENTIRE dock family first, recompile, re-enable island providers, then dependents, with no per-mod shell restarts (enabling hot-loads) and at most one guarded restart for the whole job. A serial one-mod-per-restart bisect blacked out the tower on 2026-11-07 and is banned unattended.
- Any shell loop is a 30-second emergency: disable the last-enabled mod elevated, one guarded shell restart, verify 0 respawns in 20 s, never diagnose mid-loop.
- The taskbar styler carries half of the owner's taskbar theme. The owner named it for re-enable on 2026-11-07, which lifts the 11-04 quarantine. Every dock-family off/on cycle must end with the styler back on and a guard after it. Never leave it off without telling the owner in the first line.
- Before saying docks fit or match: run `scripts\2026-11-06-dock-measure.ps1` on every dock, tray included. Every dock is 34 px; stats text clears the island border by at least 2 px in the 3x crop; icon plates are at most the dock's inner height minus 4 px. Layout work is finished only when a 4x zoom shows every text row inside its border.
- The apps dock must never snap on hover or unhover. Read `notes\2026-11-07-apps-island-fade.md` before touching the collapse mod or System Info's apps island.
- Windhawk's "System instability was detected" dialog ignores WM_CLOSE and blocks input from non-elevated shells: read its button rects with UIA and click from an elevated shell.
- On VB-Audio VAIO/Matrix inputs one session's mute is the whole device's mute. Snapshot every session before changing any, restore newest first.
- `Start-Process -Verb RunAs` quoting traps: `H:\System Configuration\agent-tools\AgentRules\machine-gotchas.md`.

## Conventions

- Current ids: Start menu `local@seamless-launchpad`, media player `local@seamless-media-player`, Windhawk UI theme `local@windhawk-enhanced-styler`, Translucent Windows `local@translucent-windows-plus`, borders `local@window-borders`. A rename request means the id too; scripts naming old ids are dead.
- Tooltips and popups use HostBackdrop acrylic with tint at least 0.85; text behind a tooltip must never be readable.
- Preview (alpha) engine updates: load the `windhawk-alpha-update` skill and run `scripts\windhawk-alpha-update.ps1` (`-Check`, `-Prepare`, `-Launch`, `-Rollback`). Never update by hand. The engine restart waits for T3 Code to close, so ask the owner to close it.
- Every mod we write or fork follows `docs\mod-style-guide.md`. Before any install or publish: `@author` starts with `DavidHiFi`; `@donateUrl https://ko-fi.com/DavidHiFi` is set; text passes `humanizer`; the readme shows a real preview; settings blocks follow the StartPad style in that guide.
- Every applied change gets a script with `-Audit` / `-Install` / `-Rollback` when practical, a backup, a receipt JSON and a note. ISO dates in filenames.
- Singleton resources for coop are in `.agent-coop.json` (`windhawk-engine`, `backups`, `packages`). Old absolute paths resolve through junctions in `H:\System Configuration`.

## Reference

Moved detail (reliability playbook, retired launcher, mod state history and evidence, traps, release checklist, record placement): `notes\2026-10-31-agents-reference.md`. Mod state and long traps moved 2026-11-07: `CURRENT-STATUS.md`.

- Seamless Dictate: continue the requested fork through implementation, installation and live verification; an offline build or partial features are not completion.
- Window Manager must cover every window, elevated ones included: its global helper runs elevated as `windhawk-mod.exe -windhawk-tool-mod local@window-manager`. Check it with an elevated Win32_Process query.
- Never swallow a modifier key-up in a low-level keyboard hook: replace it with an injected dummy key plus the key-up.
