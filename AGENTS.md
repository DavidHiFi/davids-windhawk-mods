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
- Owner keeps using the PC (rule 2026-11-10, after Explorer crashed at 1:16 and 4:14 am from test mods): compile and test at Idle priority, one heavy job at a time, wait if CPU is over 70% or free RAM under 4 GB; check Explorer and shell mods offline, enable once, and if Explorer crashes or restarts turn the mod off at once, never retry.
- Never run a DBWIN / OutputDebugString listener on this PC (the PC reset at 12:42 pm on 10/31 while one ran).
- Per-mod state (Translucent Windows Plus, Terminal and FreeDictate title bars, Helium, Explorer title and drive highlight, media player look, docks): `CURRENT-STATUS.md`, section "Mod state and traps moved from AGENTS.md". Read it before touching one of those mods.

## Traps (full list in `docs\traps-and-tips.md`)

- `-DWH_EDITING` builds no-op Wh_* stubs; production mods build with `WH_MOD` only. PowerShell 5.1 strips quotes from `-DWH_MOD_ID=L"..."`; pass the id via a force-included header.
- The engine keeps loaded DLLs mapped; install a new revision and point `LibraryFileName` at it. Mods do not initialize in console-subsystem processes.
- Tool mods (`windhawk_tool_mod.h`) are built only with `windhawk-cli.exe mod compile <id>` (elevated); a hand-built DLL crashed the host. The compile deletes the previous DLL, so rollback means recompiling the old source. From a script, read its stderr asynchronously or a big compile deadlocks.
- Restart a tool mod only with `scripts\2026-11-10-tool-mod-restart.ps1 -Id <id>` (elevated): it waits for the old process to exit before turning the mod back on. A fixed off/sleep/on leaves the mod dead and pops "Running the mod failed" on the owner's screen (2026-11-10).
- Patch `.wh.cpp` sources with Python bytes/UTF-8 and write non-ASCII as `\u` escapes; build PUA glyphs in `.ps1` with `[char]0xE971`. A PS 5.1 round trip shipped broken text.
- Dock-mod recompile: disable the ENTIRE dock family first, recompile, re-enable island providers, then dependents, with no per-mod shell restarts (enabling hot-loads) and at most one guarded restart for the whole job. A serial one-mod-per-restart bisect blacked out the tower on 2026-11-07 and is banned unattended.
- Any shell loop is a 30-second emergency: disable the last-enabled mod elevated, one guarded shell restart, verify 0 respawns in 20 s, never diagnose mid-loop.
- The taskbar styler carries half of the owner's taskbar theme. The owner named it for re-enable on 2026-11-07, which lifts the 11-04 quarantine. Every dock-family off/on cycle must end with the styler back on and a guard after it. Never leave it off without telling the owner in the first line.
- Before saying docks fit or match: run `scripts\2026-11-06-dock-measure.ps1` on every dock, tray included. Every dock is 34 px; stats text clears the island border by at least 2 px in the 3x crop; icon plates are at most the dock's inner height minus 4 px. Layout work is finished only when a 4x zoom shows every text row inside its border.
- Side-dock and tray-panel hover (tray, AI usage, media, hidden-icons panel) must match the apps dock: the whole button grows with its hover box, stays inside the outline, is eased every frame with the same curve and timing; never a glyph-only or clipped zoom.
- Self-drawn popups with WS_THICKFRAME return 0 from every WM_NCCALCSIZE (wParam TRUE and FALSE), and an "edge band gone" fix is proven only by live pixels sampled just inside all four edges, never by a render.
- Blurred self-drawn popups with WS_THICKFRAME use accent acrylic (`SetWindowCompositionAttribute`), not `DWMWA_SYSTEMBACKDROP_TYPE`: the system backdrop leaves a caption-height band at the top unblurred.
- Blur blotches, rings or green/purple tint flips: first run `scripts\2026-11-10-display-acm.py`; every screen must show ACM on (16-bit desktop). Never turn it off, and judge blur from a 16-bit `ddagrab` frame, not an 8-bit screenshot.
- Classic menus (etched grey text, short rows) in one app mean that app turned off themed controls (Steam does); fix it only in Seamless Flyouts, which lifts `STAP_ALLOW_CONTROLS` during the menu loop (2.0.2). Never restyle that app's menus elsewhere.
- Test exes built with Windhawk's toolchain must link libc++ statically, or every launch pops a "libc++.whl not found" error (proto.exe, 2026-11-09).
- Every button a mod styles gets a visible resting state and a hover state; zoom both on a capture (4x) before reporting done.
- The apps dock must never snap on hover or unhover. Read `notes\2026-11-07-apps-island-fade.md` before touching the collapse mod or System Info's apps island.
- Windhawk's "System instability was detected" dialog ignores WM_CLOSE and blocks input from non-elevated shells: read its button rects with UIA and click from an elevated shell.
- On VB-Audio VAIO/Matrix inputs one session's mute is the whole device's mute. Snapshot every session before changing any, restore newest first.
- Classic menus in one app (etched grey text, short rows; Steam) mean it turned off themed controls; Seamless Flyouts 2.0.2 lifts that only during the menu loop, so fix it there, never per app.
- Test exes built with Windhawk's toolchain must link the runtime statically, or they pop "libc++.whl not found" errors.
- `Start-Process -Verb RunAs` quoting traps: `H:\System Configuration\agent-tools\AgentRules\machine-gotchas.md`.

## Conventions

- Current ids: Start menu `local@seamless-launchpad`, media player `local@seamless-media-player`, Windhawk UI theme `local@windhawk-enhanced-styler`, menus and Translucent Windows `local@seamless-flyouts` (Seamless Flyouts, was `local@translucent-windows-plus` until 2026-11-09), borders `local@window-borders`. A rename request means the id too; scripts naming old ids are dead.
- Tooltips and popups use HostBackdrop acrylic with tint at least 0.85; text behind a tooltip must never be readable.
- Enhanced Styler passes style every copy and state at once: native `title` tooltips (they go through the styler's own tooltip), the expanded (F11) settings view, hover, selected, and scrollbars beside sticky docks. Probe all of them live before reporting.
- Preview (alpha) engine updates: load the `windhawk-alpha-update` skill and run `scripts\windhawk-alpha-update.ps1` (`-Check`, `-Prepare`, `-Launch`, `-Rollback`). Never update by hand. The engine restart waits for T3 Code to close, so ask the owner to close it.
- Every mod we write or fork follows `docs\mod-style-guide.md`. Before any install or publish: `@author` starts with `DavidHiFi`; `@donateUrl https://ko-fi.com/DavidHiFi` is set; text passes `humanizer`; the readme shows a real preview; settings blocks follow the StartPad style in that guide.
- Every mod with settings ships its own settings window, generated from the Seamless Launchpad GUI by `work\2026-11-10-media-settings\gen.py` (own icon, centred title, collapsible sidebar, About tab, built-in or native title bar); its gear and menu item open that window, never Windhawk.
- A mod is not done until its preview PNG is pushed to `media/previews/<id>.png` on the public repo's main and the raw readme image URL returns 200; check credits against each original's `@author` first.
- Every applied change gets a script with `-Audit` / `-Install` / `-Rollback` when practical, a backup, a receipt JSON and a note. ISO dates in filenames.
- Singleton resources for coop are in `.agent-coop.json` (`windhawk-engine`, `backups`, `packages`). Old absolute paths resolve through junctions in `H:\System Configuration`.

## Reference

Moved detail (reliability playbook, retired launcher, mod state history and evidence, traps, release checklist, record placement): `notes\2026-10-31-agents-reference.md`. Mod state and long traps moved 2026-11-07: `CURRENT-STATUS.md`.

- Seamless Dictate: continue the requested fork through implementation, installation and live verification; an offline build or partial features are not completion.
- Seamless Window Manager (`local@seamless-window-manager`, was `local@window-manager`) must cover every window, elevated ones included: its global helper runs elevated as `windhawk-mod.exe -windhawk-tool-mod local@seamless-window-manager`. Check it with an elevated Win32_Process query. Since 2.1 (2026-11-10) it tiles new windows; its keys: Alt+arrows focus, Alt+Shift+arrows move, Ctrl+Alt+Shift+arrows grow, Alt+Shift+Space float or tile.
- Never swallow a modifier key-up in a low-level keyboard hook: replace it with an injected dummy key plus the key-up.

## Never freeze the PC (added 2026-11-09 after two tower freezes)

- Never capture debug output yourself with `DBWIN_BUFFER` / `DBWIN_BUFFER_READY` / `DBWIN_DATA_READY`
  (no Add-Type debug catchers, inline or in a script). While that channel is open and not being read,
  every program on the PC waits about 10 s on each debug message and the whole desktop freezes. This
  froze the tower twice on 2026-11-09 (9:57 am and 10:05 am) while debugging `local@seamless-media-player`.
- To see mod logs, use the Windhawk log window or ask the owner to open DebugView. Do not script it.
- Every `windhawk-cli` or child process you start gets a hard timeout (`WaitForExit(15000)`, then kill).
  Never use a bare `WaitForExit()`.
- If the PC gets slow while you work, stop what you started first, then tell the owner.
