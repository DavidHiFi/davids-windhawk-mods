# Windhawk Configuration workspace

Shared ricing defaults: for appearance work, read `H:\System Configuration\agent-tools\AgentRules\ricing-style.md` before editing. Current instructions and this workspace's established theme take precedence. Global rules apply.

Home for all Windhawk work on this machine: installed mods and settings, taskbar and shell themes, local or forked mod development, and the engine. General Windows configuration stays in `H:\System Configuration`.

## Scope

- Windhawk engine, installed mods, mod settings, local or forked mod development.
- `windows-11-taskbar-styler` configs and other appearance or shell mods.
- `Windhawk\` (mod sources, builds, historical backups) and `davids-windhawk-mods\` (the local clone of the one public repo, DavidHiFi/seamless-workshop; the folder kept its old name). `seamless-workshop\` beside it is a link to the same clone.
- One public repo holds everything Windhawk since 2026-11-22: every mod, the Workshop feed, the one-line installer and the Windhawk update script. Never make a second Windhawk repo, and never a repo for a single mod. The old davids-windhawk-mods links redirect; seamless-workshop-old and windhawk-alpha-updater are private leftovers, never push to them.
- Records: `notes\`, `reports\`, `scripts\`, `backups\`, `docs\`.
- Not here: WinLaunch Enhanced (retired, do not resume). Its launcher is now the mod Seamless Launchpad (`local@seamless-launchpad`, renamed from Fullscreen Start Plus 2026-11-02; keys helper `launchpad-keys.exe`, task SeamlessLaunchpadKeys).

## Engine facts

| Thing | Where |
| --- | --- |
| Install | `C:\Program Files\Windhawk\windhawk.exe` |
| Data | `C:\ProgramData\Windhawk\` (`ModsSource\`, `Engine\Mods\{64,32}\`) |
| Mod settings | `HKLM\SOFTWARE\Windhawk\Engine\Mods\<mod-id>\Settings` (structured registry values, not YAML) |
| Apply a settings change | write the registry elevated and bump `SettingsChangeTime` (REG_DWORD, unix seconds) on the mod key; the mod hot-reloads on the marker |
| Engine restart | `windhawk.exe -restart` is banned: it restarts Explorer too. Reload per mod instead. A full engine restart happens only when the user asks for that exact action, and only with no T3 Code window live |
| Mod tasks box | Keep `HKLM\SOFTWARE\Windhawk\Settings\ModTasksDialogDelay` at 600000 (10 min), never back to 2000: on a busy PC the 2 s default kept "Mod tasks in progress" on the owner's screen for hours. Apply with `windhawk.exe -app-settings-changed` (elevated), never a restart |
| Service start | Starting the stopped service restarts Explorer once a few seconds later (Explorer TreeItem Tweaker Plus). Expected, not a crash |

## Safety

- On resume, recover unfinished settings work from handoffs and continue every safe offline task before reporting a live-load blocker.
- A broken mod or a visual bug with one right result needs no question: pick the best fix, do it, verify it on screen and report. When a proven fix pattern exists for the same issue, apply it first; probe only a genuinely new symptom. New features, looks and scope choices follow the global ask-first rule; a plan alone counts only when the owner says "plan only".
- Back up first: `reg export` the mod key and copy any files into `backups\<date>\...`, and record the original values. Write elevated, then read the value back.
- tray-utility-customizer is uninstalled and translucent-flyouts is removed for good: never install, suggest or re-enable either.
- A mod the owner turned off stays off. Never re-enable it, even briefly, without the owner asking for that exact mod.
- A mod version that crashed dwm (Seamless Title Bars 1.3.19, 2026-11-26) gets its installed copy rolled back to the last good version in the same turn, so the owner switching it on in Windhawk can never crash dwm again. New dwm-side code runs in the test PC before it touches the tower.
- dwm gone and not coming back: a lock or a session disconnect does not restart it. Ask the owner, then sign out (`logoff`).
- caption-buttons-customizer is cleared: do not blame or disable it for freezes. The `\Windhawk-CaptionDwmGuard` task stays disabled and its log is no longer written (`notes\2026-11-07-caption-buttons-reenable.md`).
- Fork recipe (owner rule): never patch someone else's mod under its original id. Fork it to `local@<name>-plus`, "<Name> Plus", `@author DavidHiFi, <original author>`, `@donateUrl`, a "Based on X by Y" line in the readme, then replace the original, keeping its settings. Never reinstall a mod that a fork or merge replaced.
- Borders come only from the `local@window-borders` tool mod. `window-ring.exe` is retired; never run both. A "Windhawk mod" is always a real mod, never a background exe.
- Start Windhawk with `scripts\2026-10-25-windhawk-watched-start.ps1`. `scripts\Test-WindhawkFreezeGate.ps1` is a quick check, not a gate.
- No watchdog tasks that keep a mod off or police a ban. Remove the mod once and write the rule here.
- Prefer scoped targets (`Include=explorer.exe`). No debloat scripts, registry cleaners or blanket tweaks. One change at a time, with a visible before and after, checked by screenshot.
- Change only the look the owner names. Taskbar asks count until they are on screen: earlier same-day items ship in the next round too.
- Per-mod state (Translucent Windows Plus, Terminal and FreeDictate title bars, Helium, Explorer title and drive highlight, media player look, docks): `CURRENT-STATUS.md`, section "Mod state and traps moved from AGENTS.md". Read it before touching one of those mods.

## Traps (full list in `docs\traps-and-tips.md`)

- `-DWH_EDITING` builds no-op Wh_* stubs; production mods build with `WH_MOD` only. PowerShell 5.1 strips quotes from `-DWH_MOD_ID=L"..."`; pass the id via a force-included header.
- The engine keeps loaded DLLs mapped; install a new revision and point `LibraryFileName` at it. Mods do not initialize in console-subsystem processes.
- Tool mods (`windhawk_tool_mod.h`) are built only with `windhawk-cli.exe mod compile <id>` (elevated); a hand-built DLL crashed the host. The compile deletes the previous DLL, so rollback means recompiling the old source. From a script, read its stderr asynchronously or a big compile deadlocks.
- Restart a tool mod only with `scripts\2026-11-10-tool-mod-restart.ps1 -Id <id>` (elevated): it waits for the old process to exit before turning the mod back on. A fixed off/sleep/on leaves the mod dead and pops "Running the mod failed" on the owner's screen.
- Patch `.wh.cpp` sources with Python bytes/UTF-8 and write non-ASCII as `\u` escapes; build PUA glyphs in `.ps1` with `[char]0xE971`. A PS 5.1 round trip shipped broken text.
- Dock-mod recompile: disable the ENTIRE dock family first, recompile, re-enable island providers, then dependents, with no per-mod shell restarts (enabling hot-loads) and at most one guarded restart for the whole job. A serial one-mod-per-restart bisect is banned unattended.
- Any shell loop is a 30-second emergency: disable the last-enabled mod elevated, one guarded shell restart, verify 0 respawns in 20 s, never diagnose mid-loop.
- The taskbar styler carries half of the owner's taskbar theme (its quarantine was lifted by the owner, 2026-11-07). Every dock-family off/on cycle must end with the styler back on and a guard after it. Never leave it off without telling the owner in the first line.
- Before saying docks fit or match: run `scripts\2026-11-06-dock-measure.ps1` on every dock, tray included. Every dock is 34 px; stats text clears the island border by at least 2 px in the 3x crop; icon plates are at most the dock's inner height minus 4 px. Layout work is finished only when a 4x zoom shows every text row inside its border.
- Every button that sits on the taskbar by itself (Focus, notes, window title, any new widget) is a full dock, the same as the AI usage, media and clock docks: 34 px, radius 10, 2 px `#E645475A` edge, gradient edge on hover, HostBackdrop acrylic `#1E1E2E` at 0.85 (fallback `#FA1E1E2E`), 4 px to its neighbours with every margin on both sides counted. Never 1 px, `#585B70` or a flat `#181825` fill there (owner, angry, 2026-11-26). Before shipping a taskbar change, sample each dock's edge, fill and gaps in a capture and fix the odd one out.
- Run `scripts\check-dock-align.ps1` after ANY change to the taskbar height, a styler Margin, Height, Padding or VerticalAlignment on the taskbar or tray, or a Seamless Taskbar tray change. Exit 1 means the change failed: fix it before you reply. The styler's `SystemTray.SystemTrayFrame` top margin must be half of the `Grid#RootGrid` top margin (now 3 and 6), never the same value. `Install-StagedMod.ps1` runs the check after every taskbar mod install.
- Taskbar media widget band layout (icon, two text lines and the pill shared with the time): spec and proof in `notes6-11-26-agents-reference-diet.md`.
- Side-dock and tray-panel hover (tray, AI usage, media, hidden-icons panel) must match the apps dock: the whole button grows with its hover box, stays inside the outline, is eased every frame with the same curve and timing; never a glyph-only or clipped zoom.
- Self-drawn popups with WS_THICKFRAME return 0 from every WM_NCCALCSIZE (wParam TRUE and FALSE), and an "edge band gone" fix is proven only by live pixels sampled just inside all four edges, never by a render.
- Blurred self-drawn popups with WS_THICKFRAME use accent acrylic (`SetWindowCompositionAttribute`), not `DWMWA_SYSTEMBACKDROP_TYPE`: the system backdrop leaves a caption-height band at the top unblurred.
- Screens stay SDR (ACM off). Never turn ACM back on to fix blur rings; judge on-screen text from a `ddagrab` frame, not a GDI screenshot.
- Classic menus (etched grey text, short rows) in one app mean that app turned off themed controls (Steam does); fix it only in Seamless Flyouts, which lifts `STAP_ALLOW_CONTROLS` during the menu loop. Never restyle that app's menus elsewhere.
- A window body meant to be glass is made see-through (alpha 0, colour 0), never painted darker or opaque (`local@ableton-glass-fill` shipped that defect).
- Every glass surface a mod makes matches the owner's Explorer frost: capture it beside an Explorer window over the same busy background and run the rice skill's `glass-check.py` on both; a thick tint or a flat fill is a defect, never a style choice (owner: "permanent").
- The Windows Settings page glass (`local@seamless-settings-styler`) uses Seamless Title Bars' own caption material, raw host backdrop plus #1E1E2E at its `uwp.tint` alpha (percent*255/100), never a second blur recipe; prove the title bar and page meet with no visible seam, focused and unfocused (owner asked twice, 2026-11-26).
- Menu row spacing is read once per process: after a Seamless Flyouts spacing change, apps already open keep the old rows until they restart or call uxtheme ordinal 136 on their UI thread; never reload Flyouts (Include=*) with apps open to apply it.
- Test exes built with Windhawk's toolchain must link libc++ statically, or every launch pops a "libc++.whl not found" error.
- Every button a mod styles gets a visible resting state and a hover state; zoom both on a capture (4x) before reporting done.
- Explorer docks (nav buttons, address, command bar, title pill) rest on a grey #585B70 edge; the blue to mauve gradient shows only on hover, muted to the command bar's strength (100/255), and every Explorer scrollbar thumb is the same gradient.
- Every Explorer dock, pill and the whole side list use the one dark dock fill (#4B11111B, title pills #991E1E2E), side list rows get the dock edge with gradient hover, and no Explorer part is ever filled lighter than another app's dock; check with the owner's glass setting (`explorerFrame`), not the whole-window one (owner, 2026-11-26).
- No line between Explorer's side list and the files: the gap carries a copy of the files area's own pixels, never a dark layer blended on top (it stacks to black). The side list fold is paced one step per screen frame with an ease-out, and the Tags panel folds away with it (owner, 2026-11-26).
- The apps dock must never snap on hover or unhover. Read `notes\2026-11-07-apps-island-fade.md` before touching the collapse mod or System Info's apps island.
- Windhawk's "System instability was detected" dialog ignores WM_CLOSE and blocks input from non-elevated shells: read its button rects with UIA and click from an elevated shell.
- On VB-Audio VAIO/Matrix inputs one session's mute is the whole device's mute. Snapshot every session before changing any, restore newest first.
- Explorer page slides must take the slide effect off their visual on every exit path, or the list parks at the slide start with hover one row low (details: `notes6-11-26-agents-reference-diet.md`).
- Mouse mods: read what each button really sends with `scripts\2026-11-12-hidpp-profile.py read` before guessing from hook logs; the PRO X2's G-Shift sends nothing and remaps left to forward, right to back.
- After every mod setting change, compare a fresh live capture with the one before before you tune again or answer "still too X"; identical captures mean the reload is stuck, so fix that first (guarded shell restart), never keep nudging the value.
- `Start-Process -Verb RunAs` quoting traps: `H:\System Configuration\agent-tools\AgentRules\machine-gotchas.md`.

## Conventions

- Current ids: Start menu `local@seamless-launchpad`, media player `local@seamless-media-player`, Windhawk UI theme `local@windhawk-enhanced-styler`, menus and Translucent Windows `local@seamless-flyouts` (was `local@translucent-windows-plus`), borders `local@window-borders`. A rename request means the id too; scripts naming old ids are dead.
- Tooltips and popups use HostBackdrop acrylic with tint at least 0.85; text behind a tooltip must never be readable.
- Rounded popups, menus, toasts and settings windows that draw their own edge: draw it on DWM's live corner radius, never a hard-coded 8, and check all four corners at 4x on a live capture (formula: `notes6-11-26-agents-reference-diet.md`). Popup edges copy Seamless Borders: 2 px, accent to mauve at 45 degrees.
- Copy and Replace dialogs (`local@file-operation-styler-plus`) use Explorer's main blur: acrylic accent, #1E1E2E at 0xD8 (strength 85), no extra overlay.
- Enhanced Styler passes style every copy and state at once: native `title` tooltips (they go through the styler's own tooltip), the expanded (F11) settings view, hover, selected, and scrollbars beside sticky docks. Probe all of them live before reporting. Every chip, badge and small icon button gets the dark fill, 2px grey edge and gradient hover edge, and must sit inside its card's padding (cards clip). Every group of tabs or switch halves is one pill dock with 2px dividers, never an underline. Every dialog, pop-up, drop-down, reset pill and number-arrow box gets the same grey 2px edge at rest and the blue to mauve edge on hover, including one that opens under a still cursor; changed-setting bars are blue to mauve.
- Preview (alpha) engine updates: load the `windhawk-alpha-update` skill and run `scripts\windhawk-alpha-update.ps1` (`-Check`, `-Prepare`, `-Launch`, `-Rollback`). Never update by hand. The engine restart waits for T3 Code to close, so ask the owner to close it.
- Every mod we write or fork follows `docs\mod-style-guide.md`. Before any install or publish: `@author` starts with `DavidHiFi`; `@donateUrl https://ko-fi.com/DavidHiFi` is set; text passes `humanizer`; the readme shows a real preview; settings blocks follow the StartPad style in that guide.
- Every mod with settings ships its own settings window on the Seamless Launchpad settings engine (own icon, centred title, collapsible sidebar, About tab, built-in or native title bar, fitted boxes and dropdowns, gradient scrollbars, middle-click autoscroll); its gear and menu item open that window, never Windhawk. A new one starts with `python scripts\settings-engine.py add --staged <file>`; any template edit reaches every mod with `settings-engine.py sync <id> --out <dir>`, and `Install-StagedMod.ps1` refuses (exit 4) a mod behind the template. Check with `settings-engine.py check` and `settings-material.py check`. Spec: `docs\settings-gui-standard.md`.
- Same features in every settings window, no exceptions (owner, 2026-11-17). The tray right-click menu comes from the engine and looks like Seamless Clipboard Manager's (glyph column, aligned text, Mocha); never a hand-made `TrackPopupMenu`. The native title bar and glass toggles apply the moment Save is pressed (`Set_ApplyFrame`), never after a reopen. Middle-click autoscroll works on every page. The "Settings window" group has exactly `settingsGlass`, `nativeSettingsTitleBar`, `settingsTrayIcon` with the standard names, tray on by default. A feature added to one window goes into the template and is synced to all.
- Consistency is the owner's top rule: every mod with a tray icon, tray menu or settings window uses the shared clean tray icon (gradient glyph, clear background, no plate), the engine's `Set_TrayMenu` (Clipboard's look) and FiraCode Nerd Font defaults, and `Install-StagedMod.ps1` refuses one that fails `scripts\mod-consistency.py` (exit 5).
- A mod with two settings windows carries two engine copies; list each extra namespace in `EXTRA_COPIES` in `scripts\settings-engine.py` so check covers it. Seamless Taskbar's AI usage window (`namespace aiset`) syncs with `work\2026-11-20-ai-usage-settings\apply.py`; never reinstall the retired standalone AI usage mod.
- Seamless Taskbar tray drawer footer: the folder buttons and the overflow button sit in one row with equal gaps, the outer two lined up with the panel edges (`LayoutFooterRow`); every Windows tray icon (Bluetooth, Safely Remove) must be visible. Prove both with a capture of the open drawer before calling any drawer change done.
- Cross-mod habit: whenever you work on any mod, run `python scripts\mod-consistency.py check --full` and `python scripts\settings-engine.py status` first. If another mod has fallen behind or differs, fix it when it is free on coop, or tell the owner in your reply. Never leave a known inconsistency unmentioned.
- A mod is not done until its preview PNG is pushed to `media/previews/<id>.png` on the public repo's main and the raw readme image URL returns 200; check credits against each original's `@author` first.
- Official library (ramensoftware/windhawk-mods, the Explore tab): a mod going there must pass the library's rule checker and compile on Windhawk 1.6.1, 1.7.3 and the 2.0 alpha. The public repo's `Library check` workflow runs both on every push to main that touches a mod; read its table before calling a mod library-ready. The library's own metadata rules override our fork-recipe author line (`@author` is exactly `DavidHiFi`; credit originals in the readme's "Based on X by Y" line). Full metadata list and submission steps: `notes6-11-26-agents-reference-diet.md` (Official library).
- Workshop releases: the installer downloads the repo's latest release, so that must always be a "Seamless Workshop" release — cut any release for a single mod with `--latest=false`. `publish-mods.py` marks the Workshop release latest again on its next run if one slips through.
- Settings windows: pages that list mods, modules or presets fill the full width as a Grid / List card layout with Windhawk-style cards (switch, Details, Settings, Source, Remove, Update or Install); view controls apply at once without Save; settings pages stay lean. Rule: `docs\settings-gui-standard.md`, Layout.
- Tray icons: every tool mod shares windhawk-mod.exe, so each mod's tray id is hashed from its mod id (`TrayIconId()` as in Seamless Dictate), never a fixed 1. Shared ids make every mod's icon move together when one is pinned.
- Snipper drawings stay editable like ShareX: a new shape stays picked with handles, and every option (font and size too) is on the strip and applies to the picked shape.
- One feature, one mod (owner, angry). When a mod has to reach more apps or another process, widen that same mod (a tool-mod helper inside it, plus a setting to switch the wider reach off), never a companion mod like "X Global" or "X Everywhere".
- Category suites (owner, 2026-11-26): every mod lives in one category mod (Seamless Taskbar, Explorer, Icons, Windows, Apps, Input, Look, Wallpaper, Tools, Gaming; the big apps listed in the plan stay their own mod). Each old mod is a module with its own switch, its settings nested under it with `enabled` first, read as `<module>.<name>`. Plan and members: `reports\2026-11-24-mod-suites-audit.md`; generators and tools: `work\2026-11-24-mod-suites\`. A new mod for an area a suite covers becomes a module of that suite, never a new standalone mod; standalone only when no suite fits.
- No stale copies: once a module replaces a mod (merge, fork or enhanced copy), turn the old one off with `scripts\Set-ModState.ps1 -Off`, uninstall it, drop it from the presets and feed, and delete its dead work folders, all in the same turn. Back up its source and settings first.
- An app window that opens blank after a live mod update has two copies of a mod loaded (owner, 2026-11-26, Stream Deck): list processes holding two versions of one mod file, restart those apps, never ship a guess fix to another mod.
- Every owner mod has settings, a plain readme and a preview (PNG, GIF or video) on the public repo; `mod-consistency.py` and the release checklist both check it.
- New store mods (owner, 2026-11-26): the owner browses the Explore tab by newest and wants agents to do it for them. The daily `windhawk-new-mods` job on Foxtrot runs `tools\store-watch` and writes `reports\store-watch\queue.md` (and `queue.json`; `merged.json` lists store mods already folded in, so their upstream fixes get flagged). Before forking any store mod, read that queue. A good pick becomes a forked, riced, configurable `local@` module in its suite (test PC first load, install, publish), then `store-watch mark <id> handled` (or `skipped`).
- Build a feature to the owner's whole ask and prove it live on every machine it covers before reporting (clipboard sync means old history and offline catch-up too); never stop at a partial with a "still needs" list (owner).
- When the owner says "get it done", start building that same turn; slow side research (a decompile, a long scan) never blocks the build (owner, 2026-11-26). When the owner says "continue" or "get it done", finish the whole job in that turn: while one step waits (memory, a build slot, another thread's file), do the next step instead of stopping, and end only when it is verified or truly blocked.
- A mod that replaces an app the owner already uses copies their real setup first: read their live layout and settings, make that the default with every detail and animation it had, only cleaner, then expose each detail as a setting with a plain, human name and description (no jargon). Never ship a bare version first (owner, repeated 2026-11-26, Seamless FPS Overlay).
- An overlay of several sections is one panel: no gaps between sections, columns level at top and bottom, sections split by 1px lines inside one outer edge; separate boxes only as an option (owner, repeated 2026-11-26, Seamless FPS Overlay).
- Docks and bars reserve screen space only up to their own top or bottom edge; Seamless Window Manager adds its gap past that, so tiled windows sit the same distance from every screen edge and never overlap a dock.
- Every applied change gets a script with `-Audit` / `-Install` / `-Rollback` when practical, a receipt JSON and a note. ISO dates in filenames.
- Singleton resources for coop are in `.agent-coop.json` (`windhawk-engine`, `backups`, `packages`). Old absolute paths resolve through junctions in `H:\System Configuration`.

## Reference

Moved detail (reliability playbook, retired launcher, mod state history and evidence, traps, release checklist, record placement): `notes\2026-10-31-agents-reference.md`. Mod state and long traps moved 2026-11-07: `CURRENT-STATUS.md`. What this diet moved out of this file: `notes\2026-11-26-agents-reference-diet.md`.

- Seamless Window Manager (`local@seamless-window-manager`) must cover every window, elevated ones included: its global helper runs elevated as `windhawk-mod.exe -windhawk-tool-mod local@seamless-window-manager`. Check it with an elevated Win32_Process query. Key map and version history: `notes6-11-26-agents-reference-diet.md`.
- If the owner cannot click: read every mouse button's state, inject the release for any button shown held, then turn off the newest mouse-hook mod.
- Never swallow a modifier key-up in a low-level keyboard hook: replace it with an injected dummy key plus the key-up.

## Never freeze the PC

- Never capture debug output yourself with `DBWIN_BUFFER` / `DBWIN_BUFFER_READY` / `DBWIN_DATA_READY` (no Add-Type debug catchers, inline or in a script): while that channel is open and not being read, every program on the PC waits about 10 s on each debug message and the whole desktop freezes. To see mod logs, use the Windhawk log window or ask the owner to open DebugView. Do not script it.
- Every `windhawk-cli` or child process you start gets a hard timeout (`WaitForExit(15000)`, then kill). Never use a bare `WaitForExit()`.
- If the PC gets slow while you work, stop what you started first, then tell the owner.
- Explorer proofs reuse one folder window: open it once, send every key to it, close it at the end, and never start `explorer.exe <folder>` per run (each run leaves a 240 MB windowless `/factory` host). After a proof loop, close the windowless `/factory` hosts you started, never the shell.

## Test PC first

Risky work goes in the Warden test PC or test Linux (global rules). Every new mod and every big change to one gets its first load in the test PC (`ready-windhawk` rewind point, recipe `mod.md`); small look tweaks to a proven mod may go straight on. If a mod the owner asked for has waited over 30 minutes on the test PC or the big-job queue, ask the owner once whether to put it straight on with the safety watch; never sit silent in a queue. When the owner says "hurry" or "no more waiting", skip that ask: put a tool mod straight on with the guarded installer (it watches the desktop), publish, and say the test PC run was skipped.
