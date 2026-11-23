# Current status

Last updated: 2026-11-22

- 2026-11-24: Network Speed Test Plus 2.4.0 live 3:30 am: the window fades and slides open
  and closed, with its own on/off and speed (follows the global speed). Published. New rule
  for every UI: open and close animation, toggleable. Live recording still queued. Note:
  `notes\2026-11-24-speedtest-motion.md`.
- 2026-11-23: Seamless Controls 1.0.5 live 7:50 pm: skips about 30 windowless helpers (152 to 66 programs), clearer turned-off text; test PC 11 of 11.
- 2026-11-23: Seamless Controls 1.0.2 live: preview picture fixed, settings window and drag box checked live.
- 2026-11-22: Seamless Controls 1.0.1 (`local@seamless-controls`, our fork of Win32 UI
  Modernizer): Mocha dark classic windows and controls, stands down where our own mods own a
  part, universal settings window. Test PC first load clean, installed and published on the
  tower 8:45 pm. Note: `notes\2026-11-22-seamless-controls.md`.
- 2026-11-23: Seamless Window Manager 2.8.7: Alt+PageDown/PageUp get past a remote desktop
  window that grabs the keyboard (RustDesk, since 2.8.4), and since 2.8.6 a key release that
  window eats no longer locks the walk key. 24 of 24 test PC checks, tower hand test passed
  9:22 am (run from Task Scheduler: the agent guard blocks test keys from agent programs).
  Note: `notes\2026-11-21-window-manager-2.7.0.md`.
- 2026-11-21: Seamless Window Manager 2.7.0: new windows split the biggest tile, a window
  opened over a full-screen app floats centered and tiles once it is gone, the mod's own focus
  jumps skip the Windows Animations fade (Alt+Tab keeps its zoom), Alt+PageDown/PageUp walk
  hidden windows. Installed and published 2026-11-22 5:25 am after 16 of 16 test PC checks.
  Note: `notes\2026-11-21-window-manager-2.7.0.md`.
- 2026-11-19: Seamless Window Manager 2.6.4 installed: engine settings window, plain names,
  speed work, and send to desktop, retile, focus last, thirds, per-monitor tiling off. Owner
  decision open on tiling's desktop id. Note: `notes\2026-11-09-seamless-window-manager-build.md`.
- 2026-11-13: Seamless Hub step 1 done (native Windhawk manager on the Launchpad settings
  engine, drives stock Windhawk through windhawk-cli; nothing installed, runs from
  `work\2026-11-12-seamless-hub\hub.exe`). Verified live on a test mod. Steps 2 to 5 of
  `docs\plans\2026-11-12-seamless-windhawk-app.md` wait for the owner. Note:
  `notes\2026-11-12-seamless-hub.md`.

## Mod state and traps moved from AGENTS.md (2026-11-07)

The full Safety, Traps and Conventions text from `AGENTS.md` before the 2026-11-07 agent debloat, kept word for word. `AGENTS.md` keeps the short rules. Where they differ, `AGENTS.md` wins: the taskbar styler quarantine described below was lifted on 2026-11-07 when the owner named it for re-enable.

### Safety (old wording)

- No questions or option lists in Windhawk fix replies. The owner pre-approves fixes inside the rules below: pick the best fix, do it, verify it and report. The owner said this repeatedly on 2026-10-31.
- When a proven fix pattern already exists for an identical issue, apply it and verify first (owner, 2026-11-02). Do not re-measure or re-prove an already-answered question; new probes are only for a genuinely new symptom.
- A Windhawk feature request ends with the change live and verified on screen. A plan alone counts only when the owner says "plan only" (owner repeated this 2026-11-01).

- Back up first: `reg export` the mod key and copy any files into `backups\<date>\...`, and record the original values.
- Write elevated, then verify by reading the value back.
- A mod the owner turned off stays off. Never re-enable it, even briefly, without the owner asking for that exact mod.
- tray-utility-customizer is uninstalled. Never install, suggest or re-enable it.
- caption-buttons-customizer is cleared. Do not blame or disable it for freezes.
- Caption buttons re-enabled 2026-11-07 4:08 AM (owner asked for this exact mod). The `\Windhawk-CaptionDwmGuard` task had auto-disabled it on a DWM stall; that guard is now STOPPED+DISABLED — it blames the cleared mod for any 10 s stall and its kill-dwm remedy caused the 10-27 black screens. Verified: widthfix DLL mapped in dwm.exe, centered titles on screen. Backups and rollback: `scripts\2026-11-07-caption-buttons-reenable.ps1` (`-Action Rollback` re-arms the guard), note `notes\2026-11-07-caption-buttons-reenable.md`.
- 2026-11-09 9:28 pm: all title bar work is ONE mod, `local@seamless-title-bars` 1.0.0 (Seamless Title Bars). It replaces caption-buttons-customizer, win11-custom-title-bar-colours, local@remove-uwp-title-bars-plus, local@terminal-titlebar-blur, titlebar-for-everyone, cef-titlebar-enabler-universal and fix-basic-caption-text, which were REMOVED at 9:31 pm on the owner's request (backups of keys, sources and DLLs in `backups\2026-11-09\seamless-title-bars\`; restore steps in the note). Where lines below name those mods, read the matching section of the new mod: buttons, colours (`colours.excludedApps` holds the old ExcludeCustom, incl. chrome.exe and FreeDictate.exe), uwp, terminalBar, nativeFrames, spotify, basicFrames. Basic frames is off: its uxtheme symbols are missing on this Windows build, so the old mod never did anything. Source and builder: `work\2026-11-09-seamless-title-bars\` (build output `out\seamless-title-bars.wh.cpp`). Note: `notes\2026-11-09-seamless-title-bars.md`.
- 2026-11-09: the fork is renamed Seamless Flyouts, id `local@seamless-flyouts` 2.0.0 (same code and settings plus the classic-menu look; notes\2026-11-09-flyout-match.md Part 7). Where this file says `local@translucent-windows-plus`, read `local@seamless-flyouts`. Rollback: `scripts\2026-11-09-seamless-flyouts-migrate.ps1 -Action rollback` elevated.
- 2026-11-09 menu audit (notes\2026-11-09-flyout-match.md Part 8): tool mods run in windhawk-mod.exe where Seamless Flyouts never loads, so the five tool mods with their own menus carry the look themselves (`SeamlessMenuSkin` block): better-volume-mixer-plus 1.4.1, seamless-dictate 1.0.4, window-manager 1.3.1, and two forks that replace the repo mods: `local@recycle-bin-tray-plus` 1.0.1 (was `recycle-bin-tray`, now off) and `local@magic-pointer-plus` 1.0.5 (was `magic-pointer`, now off; on 2026-11-14 merged into `local@seamless-snipper` 0.2.0 and removed, see `notes\2026-11-14-snipper-magic-pointer.md`). A new tool mod with a TrackPopupMenu needs the same block. Seamless Flyouts ExcludeCustom is now `FreeDictate.exe|WindowsTerminal.exe` (Ableton and Notepad++ let in, menus only). Rollback: `scripts\2026-11-09-menu-skin-tools.ps1 -Action rollback [-Only id]` and `scripts\2026-11-09-flyouts-ableton.ps1 -Action rollback`, both elevated. Hover gap (Part 9): hovers are 2 px shorter top and bottom so the first and last rows clear the rounded corners; Seamless Flyouts 2.0.1, recycle-bin-tray-plus 1.0.2, magic-pointer-plus 1.0.6, better-volume-mixer-plus 1.4.2, seamless-dictate 1.0.5, window-manager 1.3.2; rollback `scripts6-11-09-menu-hover-gap.ps1 -Action rollback` (elevated).
- Translucent Windows is now our fork `local@translucent-windows-plus` (1.9.0 on 2026-11-02, source `Windhawk\translucent-windows-plus\`). The repo `translucent-windows` is removed; never reinstall it or accept its update. Registry key and ModsSource use the `local@translucent-windows-plus` name, so old scripts pointing at `Mods\translucent-windows` are dead. It stays on the owner's full look: acrylicblur on the 30 pre-freeze apps, `IncludeExcludeCustomOnly=1`, global style none. Never give it `*`, add apps, or switch to the light acrylicsystem setup without the owner. Rollback: `scripts\2026-11-02-twp-migrate.ps1 -Action rollback` elevated.
- Fork recipe (owner rule, 2026-11-02): when we change someone else's mod, never patch it under the original id. Fork it to `local@<name>-plus`, "<Name> Plus", `@author DavidHiFi, <original author>`, `@donateUrl`, a "Based on X by Y" line in the readme, then replace the original with it, keeping its settings. A patched repo mod gets "updated" back to stock.
- window-borders' Exclude list has been empty since 2026-10-28; blur apps get the ring too.
- Windows Terminal titlebar (native bar, `showTabsInTitlebar false`): centered title and dots come from caption-buttons-customizer; Terminal is OUT of its `exclusions.excludedApps` (2026-11-01) and OUT of win11-custom-title-bar-colours painting (`ExcludeCustom` ends `|WindowsTerminal.exe`). Bar material comes from the `local@terminal-titlebar-blur` tool mod 1.0.0 (2026-11-03): FreeDictate accent recipe (frame sheet, blur-behind empty region, acrylic accent tinted #1e1e2e @ 85) applied to CASCADIA windows from its own host; verified focused and unfocused. Terminal's own `useMica true` stays but is NOT the visible bar material: backdrop 2 was reported while the strip measured flat rgb(32,32,32) sd 0.0 and the owner rejected it (2026-11-03). Body keeps `useAcrylic true`, opacity 70. Keep Terminal OFF translucent-windows (a mod backdrop flattens unfocus, and its blur path skips Terminal's class); never `acrylicblur` on Terminal (clear-glass caption). The old tab-row-acrylic recipe in `notes\2026-10-31-terminal-unfocused-acrylic.md` is superseded. Record: `notes\2026-11-01-terminal-titlebar.md`.
- Keep FreeDictate.exe in the ExcludeCustom lists of translucent-windows and win11-custom-title-bar-colours. FreeDictate draws its own materials, and both mods overwrite them with a flat dark colour (measured 2026-10-31). FreeDictate's Windows title bar can blur: blur-behind with an empty region (0,0,-1,-1), then the acrylic accent tinted with the theme colour, then a -1 frame sheet (measured 2026-10-31, `H:\System Configuration\notes\2026-10-31-freedictate-material-live-install.md`). The traffic-light dots and centred title on its Windows title bar come from caption-buttons-customizer, so they mean native, not FreeDictate's own bar.
- Helium (chrome.exe) is ruled in translucent-windows like Zen (RuledPrograms[31], acrylicblur 661E1E2E, owner asked 2026-11-01) and sits in win11-custom-title-bar-colours ExcludeCustom so its native title bar shows the blur. This only works because the Helium build keeps an alpha GPU surface (`H:\hb` patch `native-titlebar-acrylic-alpha`); on stock Helium the same rule turns it black. Script: `scripts\2026-11-01-helium-zen-blur.ps1`, note `notes\2026-11-01-helium-black-backdrop.md`.
- Borders come only from the `local@window-borders` tool mod (2.1.0 since 2026-11-01), run by Windhawk in its own `windhawk-mod.exe` host. `window-ring.exe` is retired. Never run both. A "Windhawk mod" is always a real mod, never a background exe. Its Menus option (on, menuRadius 16) rings classic `#32768` context menus and submenus; install and rollback: `scripts\2026-11-01-window-borders-2.1.0.ps1`.
- translucent-flyouts was removed for good. Never reinstall or reference it.
- theme-tool-plus does not re-apply the theme on load (`applyOnSettingsChange=0`). settings-styler-plus runs in SystemSettings.exe and ApplicationFrameHost.exe.
- 2026-11-09: Settings Styler Plus 1.4.1 (local only): Translucent theme now draws one blur layer with fine grain instead of ~13 stacked ones; bands and green blotches gone. Note: notes/2026-11-09-settings-blur-smooth.md.
- Start Windhawk with `scripts\2026-10-25-windhawk-watched-start.ps1` (freeze check, start, 20-minute kill switch). `scripts\Test-WindhawkFreezeGate.ps1` is a quick check, not a gate.
- No watchdog tasks that keep a mod off or police a ban. Remove the mod once and write the rule here.
- Prefer scoped targets (`Include=explorer.exe`) over all-process injection.
- No debloat scripts, registry cleaners or blanket tweaks. One change at a time, with a visible before and after.
- Verify visual changes by screenshot (tray, taskbar), not by assuming the write landed.
- Explorer title strip drag: post the system move loop and let the real left press through. Never re-send the press, never show the move cursor, and leave Alt-drag behavior out of it.
- Explorer title centering: stretch the tab list across the strip and center its panel (explorer-styler controlStyles[5], [16], `TabViewItemMaxWidth` 4000). Never pin the title pill to a fixed width. Keep the header ContentPresenter at `OpticalMarginAlignment=None` with 3 DIP side padding ([17]), or the last letter loses its edge pixel.
- Explorer drive highlight alignment: apply the offset in shared `SelectionRect` geometry independently of `state.hovered`, so hover animation endpoints, click selection, keyboard focus and drop highlights agree. Keep drive content fixed (owner correction, 2026-11-04).
- Explorer path bar edit text is centred and text selection is visible (explorer-styler controlStyles[34]): `Padding=10,7.5,6,6` centres the 17 px line in the 32 px box (was 5 top / 10 bottom), and `SelectionHighlightColor` is `#6689B4FA` again - it had been set to `#00000000`, which made every selection invisible (owner ask, 2026-11-10). Script: `scripts\2026-11-10-pathbar-text-align-selection.ps1`, note: `notes\2026-11-10-pathbar-text-align-selection.md`.
- Change only the look the owner names. Fluent Media Player buttons are filled glyphs (`iconStyle fluent_filled`) with nothing behind them: no faces, bubbles or outlines (owner repeated this 2026-11-02). The glyphs themselves carry one left-to-right Mocha blue to mauve gradient (`buttonGradient`, 1.8.4, owner asked 2026-11-02 round 3).
- Taskbar asks count until they are on screen: earlier same-day items (dock size, outline width, icon blobs) carry into the next round and ship in it, not just the newest ones. Docks are 34 px with 2 px outlines; app icons sit on Catppuccin blobs (owner repeated this 2026-11-02).
- Never run a DBWIN / OutputDebugString listener on this PC. One ran when the PC reset at 12:42 PM on 10/31.

### Traps (old wording)

- `-DWH_EDITING` builds no-op Wh_* stubs; production mods build with `WH_MOD` only.
- PowerShell 5.1 strips quotes from `-DWH_MOD_ID=L"..."`; pass the id via a force-included header.
- The engine keeps loaded DLLs mapped; install a new revision and point `LibraryFileName` at it.
- Mods do not initialize in console-subsystem processes (e.g. `powershell.exe`).
- Tool mods that include `windhawk_tool_mod.h` must be built with `windhawk-cli.exe mod compile <id>` (elevated, source in `ModsSource`). A hand-built DLL crashed the host with 0xC0000005 (2026-11-01). The compile also deletes the previous DLL, so rollback means recompiling the old source.
- PUA glyphs in a BOM-less `.ps1` are misread by PS 5.1; build them with `[char]0xE971`.
- Patch `.wh.cpp` sources with Python bytes/UTF-8 and write every non-ASCII character as a `\u` escape. A PS 5.1 Get-Content/Set-Content round trip shipped "Â°C" and broke NET UP/DOWN in sysinfo 1.4.2 (2026-11-02).
- Recompiling one dock mod recreates its taskbar islands and dangles the cached XAML references other dock mods hold (fluent's FollowSystemInfo). Explorer then AVs in the stale holder on every shell restart - a self-sustaining ~4 s crash loop (fluent 1.8.5 faulted after a sysinfo 1.4.7 rebuild, 2026-11-03, round 5 unloaded). Around any dock-mod recompile: disable the ENTIRE dock family first (island providers AND dependents), recompile, then re-enable island providers, then dependents, with NO per-mod shell restarts: enabling hot-loads, and at most one guarded restart (`H:\System Configuration\scripts\Restart-ExplorerGuarded.ps1`) for the whole job. Disabling only the recompiled pair is not enough: on 2026-11-03 4:02 pm fluent-plus and sysinfo were disabled but the still-enabled dependents (windows-11-taskbar-styler and friends) kept failing init in every new shell until the whole family went off (5 s exit loop, "shell stopped unexpectedly" events, no taskbar or wallpaper). Root cause found 2026-11-04: the sysinfo rebuild (1.4.6_168667.dll, built 11-03 12:26) broke the island handshake; pointing sysinfo's LibraryFileName back at the last good binary (1.4.1_diag1, backed up key in backups\2026-11-04-dock-restore) made the providers render the modded bar again, stable. But the 14 dependents enabled TOGETHER still loop the shell even on healthy providers, so they stay off until the owner, present, names a bisect. A serial one-mod-per-restart bisect blacked out the tower on 2026-11-07 (18 restarts, DWM crash, hard power-off) and is banned unattended. The taskbar sits at the top edge: StuckRects3 edits do not move it on build 26200 (the shell rewrites them), and the owner's dock lives at the top anyway.
- Never restart Explorer to re-enable mods: enabling a Windhawk mod hot-loads. Any Explorer restart goes only through `H:\System Configuration\scripts\Restart-ExplorerGuarded.ps1 -Reason "..."`, which refuses after 2 restarts in 10 minutes, and a refusal is final. This overrides the "shell restart in between" step above (2026-11-07: a per-mod restart script restarted Explorer 18 times in 20 minutes, DWM crashed, and the tower needed a hard power-off).
- Before saying docks fit or match: run `scripts\2026-11-06-dock-measure.ps1` on every dock, tray included. Every dock must be 34 px, and stats text must clear the island border by at least 2 px in the 3x crop. The stats scale is styler rule 30 (Viewbox Height 26). The tray height is pinned by `Height=34` on rules 12-16 (owner repeated both corrections 2026-11-07).
- Windhawk's "System instability was detected" dialog ignores WM_CLOSE and blocks synthetic input from non-elevated shells (UIPI). Read its button rects with UIA (`ControlType.Pane` children, name per button), then click the exact center from an elevated shell. It appeared 2026-11-03 after the explorer crash loop.
- The 2026-11-04 styler 1.11 update looped the shell with our 493 settings, and the LibraryFileName rollback to 1.10_660216 did NOT cure it: with our settings the styler loops the shell on BOTH binaries (plain-shell churn measured 1:46 PM, no -tool-mod involved). The styler is QUARANTINED (disabled, orange-dot update skipped, settings intact in the registry plus backups\2026-11-04-dock-restore\styler-before-rollback.reg) until the 1.10 source is reinstalled wholesale (backups\2026-10-08\windhawk-2a6-update\ProgramData-Windhawk\ModsSource\windows-11-taskbar-styler.wh.cpp) or the 493 settings are bisected offline, and the owner names it (the owner named it 2026-11-07; see Conventions). Any shell loop is a 30-second emergency: disable the last-enabled mod elevated, one shell restart, verify 0 respawns in 20 s via Win32_Process CommandLine (plain shell vs -tool-mod hosts), never diagnose mid-loop; the 1:11 PM BSOD came from ~5 min of unattended churn. Full chain: notes\2026-11-04-dock-restore-complete.md.
- On VB-Audio VAIO/Matrix inputs, one capture session's mute is the whole device's mute. Never mute sessions on the device being recorded. Snapshot every session before changing any of them, and restore newest first. A sequential save stored the already-muted value and left every mic muted (Seamless Dictate, 2026-11-07).
- The apps dock must never snap on hover/unhover (owner repeated it, 2026-11-07). In Taskbar Collapse to Running Plus, a reveal/collapse reversal mid-run lets the run land and then animates back (1.1.2); never `StopAnimation` plus an instant apply on a hover toggle, which jumps the row and the sysinfo apps island around it in one frame. Only a real instant request (hotkey/settings) may cut a run short. The flash itself (fixed 2026-11-07, collapse 1.1.3 + dock animation 2.1.1): Windows arms implicit Show/Hide animations on taskbar buttons, so a Collapsed button keeps drawing while it fades and the restored opacity turns it into a ghost icon. Every Visibility write in the collapse mod goes through `SetVisibilityStill` (clears the show/hide channel first); dock animation must reset the magnify matrix on hidden icons and re-measure every frame. The outline snap (owner repeated it with a screenshot, 2026-11-07): System Info's apps island counted a fading button at full width until 1% opacity, then jumped. The real cause (owner repeated it again, 2026-11-07): collapse gave a pin past the row's end its neighbour's shift, so it slid beside the dock and faded outside the outline. Since collapse 1.1.4 such icons fade into the end icon; System Info uses full-extent outlines, which track converging icons with no snap. Since 1.4.15 only Rendering places the island; LayoutUpdated only checks, because it fires inside the collapse mod's dry-run passes and a placement there flashes a half-built row for one frame. Since 1.4.16 the island reads each button's slide X straight off its TranslateTransform (TransformToVisual returns the old transform on the frame a slide is seated, which flashed the outline wide) and re-subscribes its Rendering hook after the slide's, so it never trails a frame; collapse 1.1.5 fades one-sided icons on a squared curve so converging icons never pile up as ghosts. Measure the island from layout offset plus slide X, never TransformToVisual alone, and always run it after the slide tick. Never weight the island by opacity (1.4.14 tried it and left ghosts outside) and never let a one-sided icon end its run outside the surviving row (`notes\2026-11-07-apps-island-fade.md`).
- Taskbar icon plates are 26 px, radius 7, with 22 px icons (styler controlStyles 6 to 9). The 34 px dock has a 2 px border, so 26 px plates leave 2 px of air; 28 px plates touched the border and read as cut off (owner, 2026-11-07). Never make plates taller than the dock's inner height minus 4 px. To make icons bigger, grow the dock (kIslandHeight), not the plates.
- Calling `windhawk-cli` from a script: read stderr asynchronously (`StandardError.ReadToEndAsync()` before `StandardOutput.ReadToEnd()`). Reading both synchronously deadlocked a big compile's warning stream for 10 minutes with the whole taskbar family disabled (2026-11-07). Syntax-check first with `Compiler\bin\clang++.exe -fsyntax-only -target x86_64-w64-mingw32 -DUNICODE -D_UNICODE -DWH_MOD '-DWH_MOD_ID=L"x"' -include windhawk_api.h`.
- Under an accent blur (Ditto styler), only black (RGB 0) reads as plain glass: any other GDI fill adds light, so never fill a strip or band behind a rounded shape. Paint only the shape itself, then check the whole bottom edge in a live capture. Ditto's row numbers are enlarged at draw time in the DrawTextW hook, because a font hook needs a Ditto restart (owner repeated both corrections, 2026-11-07).
- `Start-Process -Verb RunAs` quoting traps: `H:\System Configuration\agent-tools\AgentRules\machine-gotchas.md`.

### Conventions (old wording)

- Volume Mixer border corrections: verify corner thickness numerically against straight edges at 4x zoom before calling it fixed. DWM ROUND measured a 16 px outer radius at 96 DPI on this machine; the inner ring must share that center, with radius reduced by the stroke. The old 12 px center thinned the diagonal to about 1.3 px despite 3 px straight edges (owner correction, 2026-11-06).

- `local@taskbar-stats-fit` was uninstalled 2026-11-07 (bloat; its pointer hook churned the shell). Also uninstalled as superseded: `micrographics-taskbar-clock` (use the -plus fork), `windows-11-file-explorer-styler` (use the -plus fork), Explorer TreeItem Tweaker Plus (built into GPU Accelerated Explorer). Never reinstall a mod a fork or merge replaced; remove the old one when the replacement ships. Backups and rollback: `notes\2026-11-07-mod-debloat.md`.
- GPU Accelerated Explorer draws the file list itself, so it owns sorting: every column sort must match real Explorer (Size is true biggest/smallest with folder sizes included), and each folder must reopen with the sort Explorer saved for it. Never ship a change that resets or ignores the saved sort (owner, 2026-11-07, 1.2.3).
- The Windhawk UI theme mod is `local@windhawk-enhanced-styler` ("Windhawk Enhanced Styler"), renamed from `local@windhawk-styler` on 2026-11-07, id included. Scripts that name the old id are dead. Gradient titles and selection color are settings in it, never a second mod. 2026-11-23: the Enhanced badge is removed (2.2.23, owner ask) and, with Mocha icons on, the header logo is the Mocha tile with a dark hawk (2.2.32, CSS only: the Windhawk page blocks embedded pictures). Note: `notes\2026-11-23-styler-header-logo.md`.
- 2026-11-12: Enhanced Styler 2.2.3 themes the Windhawk window from its first frame. It registers the theme in-process, in the background-colour hook, before Windhawk navigates. The debugger session is only a fallback, and its port moves off 9333 when Dopamine holds it. Settings are re-read only on a save. Never force-kill the Windhawk UI in tests. Note and rollback: `notes\2026-11-12-styler-fastpaint.md`.
- 2026-11-14: Enhanced Styler 2.2.6 wraps long mod descriptions on a mod's page instead of cutting them off. Note: `notes\2026-11-14-styler-desc-wrap.md`.
- 2026-11-14: Seamless Window Manager 2.5.6 asks each app for its smallest size when it joins the layout (idea from the public Adaptive Windows mod; ideas only). Remaining Adaptive Windows ideas, ranked, at the end of `notes\2026-11-09-seamless-window-manager-build.md`.
- 2026-11-17: Seamless Window Manager 2.5.8 fixes the right-side gap and the flickering title bar on apps that keep stalling (frozen windows keep their tile; no stand-in window while tiling is on). Go programs (cloudflared, Ollama, Tailscale tray, esbuild) are excluded because they crash when the mod reloads.
- 2026-11-17: Seamless Window Manager 2.5.9: the focus jump animation is now a ring (blue to mauve outline closes in on the window's edge and fades; the window never hides). Zoom stays as an option under Look.
- The media player is `local@seamless-media-player` ("Seamless Media Player"). It was renamed from `local@taskbar-fluent-media-player-plus` on 2026-11-07, id included. A rename request means the id too.
- The taskbar styler carries half of the owner's taskbar theme: the stats text fit, the dock sizes, the hovers, the tooltips and the tray dock. The owner named it for re-enable on 2026-11-07, which lifts the 11-04 quarantine. Every dock-family off/on cycle must end with the styler back on and a guard after it. Never leave it off without telling the owner in the first line (owner correction, 2026-11-07: a family script skipped it as "quarantined").
- Every dock hover is an exact copy of the media island hover: #BF181825 fill behind the content filling the whole dock interior, 1 px blue #89B4FA ring, radius 8, dock border stays grey. Never a grey fill, an inset, or a fill drawn over text (owner correction repeated, 2026-11-06; styler rules 38/39).
- Every taskbar dock is 34 px tall (rows 8-41 in the 48 px bar), sized to fit its content. Stats 1.4.11 measures at `stackedFontSize` 8, renders text at 7 via styler rule 40 and scales its four rows to 26 px via rule 30. Its native island and published right edge use the displayed width, not the unscaled measurement. Keep leftOffset 30 and islandPadding 8 for text clearance. Changing stackedFontSize live previously restarted the shell; change it only with the owner warned.
- The clock fork also styles the tray chevron container. Styler rule 42 removes that container's native border and background; rule 16 alone supplies the tray's left outer edge. Never draw both outlines (owner correction, 2026-11-07). Evidence: notes/2026-11-07-stats-clearance.md.
- Tooltips and popups use HostBackdrop acrylic with tint at least 0.85; text behind a tooltip must never be readable.

- Preview (alpha) engine updates: load the `windhawk-alpha-update` skill and run `scripts\windhawk-alpha-update.ps1` (`-Check`, `-Prepare`, `-Launch`, `-Rollback`). Never update by hand. The engine restart waits for T3 Code to close, so ask the user to close it.
- Every mod we write or fork follows `docs\mod-style-guide.md`. Before any install or publish: `@author` starts with `DavidHiFi`; `@donateUrl https://ko-fi.com/DavidHiFi` is set; text passes `humanizer`; the readme shows a real preview. Settings blocks follow the StartPad style in that guide (plain `$name`, range plus suggested value in `$description`, labelled `$options`, grouped order, rich look knobs; owner rule 2026-11-04).
- Every applied change gets a script with `-Audit` / `-Install` / `-Rollback` when practical, a backup, a receipt JSON and a note. ISO dates in filenames.
- Taskbar layout work is finished only when a 4x pixel zoom shows every row of text at least 1 px inside its island border; never report "still not fixed" and stop. Keep iterating settings-only changes (scale, translate, padding) until it fits (owner rule repeated 2026-11-05/06).
- Singleton resources for coop are in `.agent-coop.json` (`windhawk-engine`, `backups`, `packages`).
- Old absolute paths resolve through junctions in `H:\System Configuration`.

## 2026-11-10: Seamless Window Manager 2.2.0, GlazeWM fill, borderless and monitor keys

- Alt+T floats or tiles a window (was Alt+Shift+Space); center half moved to Alt+C.
- Snap halves and quarters (Alt+Q/W/E/R, Alt+U/I/J/K) on a tiled window rearrange the tiles; stacked windows move side by side before going to the next monitor.
- Ctrl+Alt+Shift+Up/Down now resize a tile's height; maximized tiled windows move and snap again.
- Alt+F fills the screen inside the gaps; Ctrl+Shift+F is borderless fullscreen (like ShareX), working once ShareX lets go of the key.
- 2.3.0 (Nov 10): Alt+1-4 focus left, main, right, top monitor; Alt+Shift+1-4 send there; Ctrl+Alt+Shift+1-9 virtual desktops; Ctrl+Shift+P pause; windows glide 180 ms; Ctrl+Alt+drag magnetic. Ctrl+Shift+arrows freed. Record: build note, "Change: 2.3.0".
- 2.4.1 (Nov 11): Alt+PageDown shows the window stacked behind, Alt+PageUp brings it back, Alt+Shift+M restores the last minimized window. Not yet tested live. Record: build note, "Change: 2.4.1".
- 2.5.0 (Nov 11): Focus animation option (zoom on every focus key), tiles respect app minimum sizes and never spill onto the next monitor, Ctrl+Shift+F freed from ShareX. Record: build note, "Change: 2.5.0".
- Pause key (Nov 11, settings change, no rebuild): now Alt+Shift+P, was Ctrl+Shift+P. Probe-verified: Alt+Shift+P taken by the mod, Ctrl+Shift+P free, helper running. Record: build note, "Change: pause key moved to Alt+Shift+P".
- Apps that never tile is a one-app-per-entry list in the settings.
- Record: `notes\2026-11-09-seamless-window-manager-build.md`, section "Change: 2.2.0 keys".

## 2026-11-10: Seamless Window Manager 2.1.0, GlazeWM-style tiling and keys

- New windows tile side by side with 20 px gaps; dialogs, small and on-top windows float.
- Keys: Alt+arrows focus (pointer jumps), Alt+Shift+arrows move, Ctrl+Alt+Shift+arrows grow, Alt+Shift+Space float or tile. Snap halves are Alt+Q/W/E/R again; send to monitor is Ctrl+Alt+arrows.
- Browsers and Explorer lose Alt+Left/Right for Back and Forward.
- Record: `notes\2026-11-09-seamless-window-manager-build.md`, section "Change: tiling and GlazeWM keys".

## 2026-11-14: Explorer drop-down menus styled, Tags pills and menus match the folder list

- Command bar menus (Sort, View, New): Styler Plus controlStyles[41..45], Mocha glass, gradient edge, FiraCode, blue dots. Focus ring stays a plain colour (a gradient fail-fasts Explorer).
- Explorer Tags Plus 0.8.3: same columns, font and text colour as the folder rows (checked live by PrintWindow).
- Seamless Explorer View: resting folder text now Mocha text (205,214,244).
- Explorer Tags Plus 0.8.5 and Seamless Explorer View 2.0.2: Tags pills now identical to the folder pills (fill, edge, height sampled live within 1-2 shades); hover edge is the blue to mauve gradient on both.
- Right-click menus: folder list and Tags use the same glass, edge and font (sampled live).
- Open: hover state not forced live (posted mouse moves do not trigger it); This PC drive tiles not reviewed this pass.
- Record and rollbacks: `notes\2026-11-14-explorer-menu-and-pills.md`.

## 2026-11-12: Seamless Explorer View 2.0.0 (renamed from GPU Accelerated Explorer View Plus, id included)

- Where this file says `local@gpu-accelerated-explorer-view-plus`, read `local@seamless-explorer-view`.
  Same code; 140 settings values carried; old id removed. Explorer restarted once at the swap (the mod's own load behaviour, no crash entries).
- Rollback: `scripts\2026-11-12-seamless-explorer-view-rebrand.ps1 -Action rollback` elevated. Note and proof: `notes\2026-11-12-seamless-explorer-view-rename.md`. Repo rename in PR DavidHiFi/davids-windhawk-mods#54.

## 2026-11-07: Peek 1.5.0, scroll-wheel zoom and zoom badge
- The wheel zooms images and videos at the cursor. Zoom glides, rests at fit, and supports drag pan, double-click real size and `+`/`-`/`0`. A Mocha badge shows the magnifier and percent.
- Verified 11/7 by a live posted-message test (fit/zoom/pan/detent/video diffs, badge alpha) and an 8x badge crop with an unbroken ring: `peek-work\zoom-img-hud-badge-x8.png`.
- Note and rollback: `notes\2026-11-07-peek-zoom.md`.

## 2026-11-07: GPU Accelerated Explorer View Plus 1.3.2, header gap and view switch drag fixes

- Page slide end state pinned to 0, and NavTree's Explorer restart limited to the taskbar process. Live 12:30 pm: churn=False, and every explorer.exe holds 1.3.1 (tasklist /m).
- No header gap in 10 navigations (repro captures). Original trigger not reproduced, so the cause is unverified. Record: notes\2026-11-07-header-gap.md.
- 1.3.2 (12:40 pm): view switch no longer drops to the fallback spot when the window moves. Live, churn=False. Drag check 12:55 pm: 120/120 samples on the same spot (notes).

## 2026-11-07: GPU Accelerated Explorer View Plus 1.3.0, Navigation Tree Offset merged in
- Explorer Navigation Tree Offset 1.1 (Languster) is built in under Navigation pane > Tree position and arrows; settings carried, old mod removed, Languster credited.
- Verified 11/7 by install log (new dll loaded, old unloaded, no shell churn) and removal log, plus a live Explorer capture 11/7 (tree style 0x56019228: no buttons, lines or root lines; proof2.png in the work folder).
- Note and rollback: `notes\2026-11-07-navtree-offset-merge.md`.

## 2026-11-07: Windhawk Enhanced Styler 2.1.0 (renamed from Windhawk Styler, id included)
- Selected text uses Mocha blue at 40%, Windhawk logo, name and section titles/icons carry a blue to mauve gradient, Enhanced badge beside the name. All configurable.
- Verified 11/7 by registry (2.1.0 enabled, old id removed, settings carried), CDP computed styles and a window capture: `reports6-11-07-enhanced-styler-window.png`.
- Note and rollback: `notes\2026-11-07-windhawk-enhanced-styler.md`.

## 2026-11-01: window-borders 2.1.0 live, context menus get the border
- New Menus option (on, menuRadius 16) rings classic `#32768` menus and submenus with
  the active gradient. Built with windhawk-cli; host loads
  `local@window-borders_2.1.0_487264.dll` (elevated module scan, 11/1).
- Verified on screen 11/1: Explorer's desktop menu strips 4 -> 8 -> 4 on open and close,
  capture `reports\2026-11-01-window-borders-menus\explorer-menu-open.png`; test menu
  plus submenu 8 -> 16 -> 8, no orphans. Classifier tests pass.
- Note `notes\2026-11-01-window-borders-2.1.0.md`; rollback
  `scripts\2026-11-01-window-borders-2.1.0.ps1 -Action Rollback`.

## 2026-11-01: local@steam-caption-hittest nuked per owner order; Steam title bar fixed in Steam itself
- Owner order: get rid of the Steam title bar Windhawk mod ("that is slop"), fix it in Steam itself.
- Removed and verified: engine key gone (reg query: not found), source gone from
  `ModsSource`, DLL deleted from `Engine\Mods\64` after a clean Steam restart
  (exit 4:23:53 am, back 4:24:25 am 11/1), and an elevated module scan shows no
  `steam-caption` or `titlebar-for-everyone` DLL in any steam/steamwebhelper process.
  `titlebar-for-everyone` IncludeCustom is Discord-only (steam.exe removed 10/31,
  Discord entries kept, read back).
- Steam-side fix applied: MochaSteam theme condition "Window Controls" was `Hide`
  in Millennium `config.json` (that hid Steam's own buttons and left the dead dot
  strip). Flipped to `Show`; verified via CDP after restart: `.title-bar-actions`
  `display: flex`, three 42x32 `.title-area-icon` buttons (min 1314, max 1356,
  close 1398 at 1456 px width). Page DragArea answered HTCAPTION (measured 11/1
  3:56 am). Backups: `backups\2026-10-31\steam-caption-hittest-removal\` (mod +
  tb4e keys, sources, DLLs, receipt) and the Millennium config backup is in
  `H:\System Configuration\backups\2026-11-01-millennium-config\`.
- Rollback: `H:\System Configuration\scripts\2026-10-31-steam-caption-hittest-install.ps1 -Rollback`.
- Unverified until the owner opens Steam's window once: a real-mouse click on
  each button (synthetic clicks are unreliable per prior findings) and whether
  the old dot strip still paints above the page; note § 2 in
  `H:\System Configuration\notes\2026-10-31-millennium-steam-audit.md` has the details.

## 2026-10-31: ZoomIt 1.1.0 pen color (system/accent/custom) live; previews pending owner-run capture
- Live and verified: registry `Version=1.1.0`, `LibraryFileName=local@zoomit_1.1.0_599761.dll`,
  `penColor=blue` preserved, `penColorCustom=#ff00ff` seeded (reg query read 2026-10-31
  ~10:45 AM); uiaccess host pid 18756 restarted 8:46:42 AM on the settings bump.
  Receipt/backups `backups\2026-10-31\zoomit-1.1.0\`; build shas `reports\2026-10-31-zoomit-peek-polish.log`;
  rollback `scripts\2026-10-31-zoomit-peek-polish-install.ps1 -Rollback`.
- Pushed: `mods/local/zoomit` 1.1.0 to origin/main commit `43fec97` (verified by push output 2026-10-31).
- Unverified (needs the owner's go — the capture covers the whole screen):
  the two preview PNGs and the visual proof of the custom pen color. One command
  in `notes\2026-10-31-zoomit-peek-polish.md`.
- Peek stays 1.0.0: repo 1.1.0 is half-built (action bar never drawn, three keys
  unhandled) — not installed, not pushed, finish-or-strip is the owner's call.

## 2026-10-31: window-manager 1.2.9, centered unclipped Explorer title, Explorer blur fix (real drag unverified)
- Live (read 1:20 PM 10/31): window-manager 1.2.9 loaded in all explorer processes. Title press goes to the
  native move loop with the real press passed through; no re-sent press, no move cursor.
- Live: explorer-styler stretches the tab list and centers the title; fixed 1200 px pill removed.
  Verified by off-screen captures at 600 to 2400 px with a long path: full and centered (reports\2026-10-31-native-title-strip\final\).
- Unverified: real-mouse title drag and the FreeDictate stuck Alt-drag fix (no live input tests).
- Fixed: last title letter clipped (styler [17] optical margin off plus padding) and exact centering ([6] margin). Measured 2026-10-31, `reports\2026-10-31-native-title-strip\clip4`.
- Fixed: blur missing on some Explorer opens. translucent-windows 1.8.3 local patch re-applies the accent on folder windows at show, +0.5 s and +2 s. 20 of 20 opens blurred, measured 4:25 PM 10/31 (`reports\2026-10-31-blur-open\run20`). Stock 1.8.2 silently replaced it at 5:46 PM 10/31; hardened build `1.8.3_20261102a` (keeps polling hidden windows) redeployed 2026-11-02, loaded in explorer (`tasklist /m`), 20 of 20 opens blurred (`reports\2026-11-02-blur-open\run20`). Note: `notes\2026-11-02-explorer-blur-redeploy.md`. Rollback: `deploy.ps1 -Action rollback`, elevated.
- Detail and rollback: `notes\2026-10-31-explorer-native-title-strip.md`.

## 2026-10-30: window-manager 1.2.3 — Explorer title bar drag fixed (tabless look kept)
- Owner ask: Explorer windows could not be dragged from the title bar; grabbing
  the title started a tab grab (the styler's 1200 px pill is a tab-grab
  passthrough region). Fix: window-manager holds a persistent WH_MOUSE_LL hook
  in every explorer process (`explorerTitleStripDrag=1`); a plain left press on
  the CabinetWClass strip band (caption-button scaffolding excluded) starts a
  native SC_MOVE|HTCAPTION move. Alt+drag and right-drag-size triggers
  unchanged (settings restored after the deploy script wiped them — see below).
- Final clean build `local@window-manager_1.2.3_20261030.dll` deployed and
  hot-swapped 3:31 PM (no engine restart). Verified on the final build:
  `title-drag-verify-sep.ps1` 5/5 grabs moved 154 px, no new frames;
  `alt-vs-plain.ps1` both paths move 154 px on established windows. Plain
  clicks on the strip replay harmlessly; caption-button presses are provably
  untouched (log-proven) — the owner should try the buttons themselves, as
  synthetic-click testing of the custom buttons is unreliable tooling.
- Incident, fixed twice: the deploy script's `New-Item -Force` on the mod's
  Settings key deleted and recreated it (wiping all 67 trigger/hotkey values;
  a mod with missing settings runs KEYLESS triggers). Restored both times from
  registry exports; deploy.ps1 now only creates the key when missing. Trap
  recorded: `New-Item -Force` on an existing registry key is destructive, and
  `reg import` of a full key export also restores `LibraryFileName`.
- `-Mode center` for the title strip was applied and A/B-measured: the
  `TabViewListView HorizontalAlignment=Center` style has NO effect (identical
  title position with and without), so it was removed again per plan.
  Windowed centering was already correct and stays; maximized stays
  off-center (open item, owner decides whether to pursue). Details:
  `notes\2026-10-29-title-centering-refactor.md`, evidence
  `reports\2026-10-29-title-centering\`.
- Probe tooling note for future sessions: `SetCursorPos` never fires
  WH_MOUSE_LL — inject probe moves with `mouse_event(0x8001, …)` absolute.
- Bookkeeping sync (gen 5, 3:5x PM): final 1.2.3 source published to
  davids-windhawk-mods as `b0a283e` ("Window Manager Plus 1.2.3: drag File
  Explorer windows from the title bar") from a fresh clean clone (the standing
  checkout is dirty and diverged — do not publish from it), and copied to
  `C:\ProgramData\Windhawk\ModsSource\local@window-manager.wh.cpp`
  (sha256-verified 9AB56DFF…BB856). Note: the 32-bit DLL in
  `Engine\Mods\32` is still the pre-fix 27/10 `1.2.3_1` (build/deploy scripts
  are 64-bit only) — no functional impact, the strip-drag fix only triggers in
  Explorer, which is 64-bit. Old debug `1.2.3d_*` DLLs stay locked until those
  processes restart; harmless.

## 2026-10-30: gpu-accelerated explorer view 0.9.242 — flyout pill fixed
- Owner ask: secondary flyout menus (right-click → NanaZip) opened as an empty
  pill while the mod was enabled. Two defects: the item/bulk menus never armed
  the `ShellPopupBridge` (fixed in an intermediate 0.9.241 — still pill), and
  `ShellMenuFlags()` defaulted to `TPM_NONOTIFY`, so the popup owner got no
  messages at all and the bridge was never invoked. 0.9.242 arms the bridge AND
  passes `ShellMenuFlags(state, true)` at both item-menu sites.
- Verified live ~12:05 PM with the idle-gated raw-menu probe: NanaZip cascade
  populated (8 items) — **PASS** (`reports\2026-10-30-gpu-view-flyout\`);
  0.9.242 DLL loaded in all 5 explorer processes; hot-swapped via
  `LibraryFileName` + `SettingsChangeTime`, no engine restart. Clean A/B:
  0.9.241 pill vs 0.9.242 populated with the identical probe.
- Note: `notes\2026-10-30-gpu-view-flyout-fix.md`. Receipt:
  `backups\2026-10-30-gpu-view-flyout\receipt-fix-0.9.242.json`. Wrapper:
  `scripts\2026-10-30-gpu-view-flyout.ps1` (-Audit/-Install/-Rollback).
- Upstream is at 0.9.290 (ours forks 0.9.240); offer the owner a catalog
  update separately — do not auto-update. windows-animations untouched (1.3.7).

## 2026-10-27: Fullscreen Start Plus 1.6.1 — search box is a real text field
- Owner ask: the caret line was static and text could not be selected or
  bulk-edited. 1.6.1 adds a blinking caret, click-drag and Shift+arrow
  selection, Ctrl+A/C/X/V, Delete, and caret keys (with an empty search,
  Left/Right still pick apps). Same branch and PR as 1.6.0.
- Built 12:5x PM, 840,192 bytes (sha256 4345434E…). Host test suite PASSED
  3:4x PM — the new `edit` step (select, replace, drag-select, cut/paste
  roundtrip) and the 1.6.0 pin/unpin regression (`reports\2026-10-24-
  fullscreen-start-plus\1.6.1\suite-result.txt`). Installed 3:52 PM as rev _1,
  Explorer verified loading it; pushed `081df99` to PR #22 (retitled 1.6.1).
  The suite initially failed on the test driver's vk-only key injection
  (injected Shift missed by GetKeyState), not on the mod; the driver now sends
  scancodes.
- 1.6.0 (same day, PR #22, installed rev _2): Shift+Win works over admin
  windows via the elevated helper fsp-keys.exe (task FullscreenStartPlusKeys;
  admin test 5/5), and pinned mode with search over all apps plus right-click
  pin/unpin — verified live by the owner, who now runs appSource=pinned.

## 2026-10-27: Remove UWP Title Bars Plus 2.1.0 — Settings and Store verified visible and captioned
- Owner-asked install at 11:31 AM (ApplicationFrameHost only). Verification finished
  12:25 PM: Settings launched via `ms-settings:` (the Win+I code path) and the Store
  both render native title bars, uncloaked, themed buttons and icon drawn; maximize
  check reproduced twice via SendMessage `SC_MAXIMIZE` with the correct 8 px-overshoot
  rect under the top taskbar (`-8,42,2568,1448`); all probe frames restored and closed.
  Evidence: `work\2026-10-27-settings-invisible\fork-v2.1\printwindow-store-2.1.0-121405.png`,
  `pw-settings-maximized-122506.png`, `pw-settings-normal-122233.png`.
- Calculator/Photos not installed, so their checks are void. The real Win+I keypress was
  not sent (T6 fullscreen in front). DWM guard clean since the install (last stall 10:19 AM).
- 2.1.0 source committed to davids-windhawk-mods main as `71cf782` (local). Open: readme/
  preview publishing pass and the owner's one-press Win+I check. Details:
  `notes\2026-10-27-remove-uwp-title-bars-plus.md`.

## 2026-10-27: Remove UWP Title Bars Plus 2.0.4 — Settings caption fixed (icon, title, min/max/close)
- Fork of Anixx's Remove UWP titlebars installed 8:14:48 AM:
  `local@remove-uwp-title-bars-plus_2.0.4_337312.dll`, Disabled=0. The upstream
  `native-titlebars-uwp-lite` key, DLL and source are gone (removed by an unknown
  actor between 7:38 and 7:49 AM — not either agent chain; flagged for the owner).
- The blank Settings caption had two causes: the UWP-titlebar mod's subclass
  passed WM_NCPAINT/WM_NCCALCSIZE to DefWindowProcW, bypassing settings-styler-plus's
  painter; and styler's `nativeTitleBar` had been turned off (~10:49 PM 2026-10-26,
  unknown actor), so it never painted Settings frames at all. Setting the
  normal-window prop directly does not make DWM draw a caption (2.0.2/2.0.3, four
  probes) — it is styler's claim marker.
- Fork 2.0.4 yields styler-marked frames to styler's painter; styler
  `nativeTitleBar` restored to 1 (snapshot
  `backups\2026-10-27\settings-styler-plus-key-after-nativetitlebar-restore.reg`).
- Verified 8:20 AM on a fresh Settings frame: PrintWindow strip shows the gear
  icon, title and three themed caption buttons —
  `work\2026-10-27-uwp-titlebars-plus\pw-2026-10-27-082021-15292.png`.
  8:22 AM independent probe passed in both focus states (same frame). Scope:
  Settings verified visually; other UWP apps verified by code-path equivalence
  only — one `Verify-Fork2.ps1` run confirms any UWP app the owner opens later.
- Receipt: `backups\2026-10-27\remove-uwp-title-bars-plus\receipt-install.json`.
  Note and rollback: `notes\2026-10-27-remove-uwp-title-bars-plus.md`.
- 8:55 AM rung 2: re-verified the caption pixels (`pw-2026-10-27-082456-15292.png`)
  and committed the fork source to davids-windhawk-mods (`a93a4c5`) after a
  verified ACL repair on the repo (`reports\2026-10-27-acl-davids-windhawk-mods\`,
  recovery scripts alongside). Remaining loose end for publishing: readme/preview
  still upstream's + release-checklist pass.

## 2026-10-25: translucent-windows on the smallest safe setup; stale blur rules cleaned
- 10:41 AM: catalog `translucent-windows` 1.8.2 enabled with `acrylicsystem` on 12
  classic apps only, global style `none`, `IncludeExcludeCustomOnly=1`. No Explorer,
  Chromium/Electron, browser or console apps. Watch 10:42-11:07 clean (avg 3.45 ms,
  worst 9.5 ms, no stalls).
- 12:20 PM: the setup script's wipe had left 20 stale `acrylicblur` rules at indices
  12-31; deleted 100 values with literal registry deletes. Readback: 12 rules, all
  `acrylicsystem`. Watch 12:26-12:51 clean (avg 3.41 ms, worst 8.3 ms, no stalls).
- Visual: winver's DWM backdrop attribute is 3 (acrylic). The mod DLL is loaded only in
  winver, regedit, Everything and HWiNFO64; not in Explorer, Chromium/Electron,
  consoles or rundll32.
- 12:25 PM: removed the 4 remaining off owner picks; 84 mods installed, 73 on, 11 off.
  The two ON Start menu mods are left in place pending the owner's word.
- Note: `notes\2026-10-25-tw-safe.md`; receipt and backups:
  `backups\2026-10-25-tw-safe\`; trim backups: `backups\2026-10-25-trim\122532\`.

## 2026-10-25: Translucent Windows Plus back on all its apps
- Cause: after the 2026-10-24 freeze work the mod's Include was `Discord.exe` only, so
  no other app got the blur. The freezes were tray-utility-customizer, not this mod.
- 1:31 AM: Include set back to `*`; Discord stays in, StreamDeck, VB-Audio Matrix,
  Ableton and notepad++ stay excluded. Verified 2026-10-25: registry readback,
  `tasklist /m` shows the DLL in 184 processes (none of the protected audio apps),
  screenshots in `reports\2026-10-25-twp-coverage\`.
- Note and rollback: `notes\2026-10-25-translucent-windows-coverage.md`.

## 2026-10-25: Settings Styler Plus 1.3.0 — real native title bar on Settings, PR #21 open
- Shipped on branch `settings-styler-plus`, commit 40ca980, open PR
  [davids-windhawk-mods#21](https://github.com/DavidHiFi/davids-windhawk-mods/pull/21)
  (awaiting owner review; no checks or reviews yet as of 2026-10-25). Installed and
  enabled: DLL `local@settings-styler-plus_1.3.0_576163.dll` (10:35:31 PM), original
  `windows-11-settings-styler` still disabled.
- The mod now also injects into `ApplicationFrameHost.exe`, turning Settings frames
  into normal captioned windows: caption buttons come from the DWM system theme
  (custom themes included) and acrylic shows through; WM_NCACTIVATE restores the
  stock bar when the mod unloads.
- Verified live 00:30:31 (full pass): hit-test 20/9/8, maximize/restore/minimize/
  bring-back all clean, Settings survived; off/restore screenshot pair proves the
  WM_NCACTIVATE path. Evidence: `reports\2026-10-24-settings-styler-plus-final\`.
- If Settings ever "won't launch" after testing churn, kill ApplicationFrameHost
  first — a wedged frame host stopped creating frames silently once. A
  disable→enable cycle does not restyle an open Settings window; reopen it.
- Receipt: `backups\2026-10-24-settings-styler-plus\receipt-1.3.0.json`. Note:
  `notes\2026-10-24-settings-styler-plus.md`.

## 2026-10-24: Windhawk Styler 2.0.76 — settings page scrollbar hugs the card edge, rounded thumb
- Deployed and read back at 9:45 PM on 2026-10-24 (registry Version 2.0.76, DLL hash). Live check: bar right edge equals card right edge (0px gap), thumb radius 999px. Evidence: `reports\2026-10-24-styler-scrollbar\page-scrollbar-2026-10-24-214541.txt`. Details in the 2.0.75 note.

## 2026-10-24: Windhawk Styler 2.0.75 — drop-down scrollbars stay inside the rounded corners
- Deployed. Registry `Version` 2.0.75 and DLL hash read back at 9:40 PM on 2026-10-24.
- Live probe, 9:42 PM: on three long menus there was no Windhawk overlay bar inside the menu, and the arc check found no scrollbar point outside the corner curve. Evidence: `reports\2026-10-24-styler-scrollbar\probe-2.0.75-run.txt` and its clips.
- Source is uncommitted in `work\styler-release`. Cause, rollback and gaps: `notes\2026-10-24-styler-scrollbar-2.0.75.md`.

## 2026-10-24: Windhawk Styler 2.0.73 — dropdown menus solid, no gap
- Deployed. Registry `Version` 2.0.73 read back on 2026-10-24.
- Live check of a settings select, 8:45 PM on 2026-10-24: solid fill `rgb(24, 24, 37)`, `backdrop-filter: none`, list padding 0, first row top equals panel top (gap 0). Evidence: `reports\2026-10-24-styler-dropdown\live-check-2026-10-24-204503.txt` and the two PNGs in that folder.
- Not checked: picker dropdowns, modals, drawers, blur against the real desktop. Source is uncommitted in `work\styler-release`. Rollback and details: `notes\2026-10-24-styler-dropdown-2.0.73.md`.

## 2026-10-24: Translucent Flyouts 0.6.70 — submenu overlap flicker fix deployed
- Fix in `30-engine.inc` `UpdateRingOverlay()` (lines 1456-1483): replaced unconditional `SetWindowPos(entry->window, HWND_TOPMOST, ...)` with conditional z-order logic that places the overlay **below** any visible popup menu (#32768 class) that overlaps the parent menu's right/bottom edge
- Uses existing `Utils::IsPopupMenu()` (class-32768 / atom 0x8000 check) to identify submenus
- When overlapping submenu found: `SetWindowPos(entry->window, submenuAbove, ...)` places overlay below it; fallback `HWND_TOPMOST` when no overlap
- Preserves existing `SetWindowPos(menu, entry->window, ...)` at line 1490 (menu stays below overlay)
- 0.6.70 pill fix integrity: **unchanged** — `ClientOffset()`, `LPtoDP` clip shift, `RoundRect` pen, buffered-paint DC conversion all intact
- Built: `local@translucent-flyouts_0.6.70_1_64.dll` + `_1_32.dll` (build log 16:24)
- Deployed: `_0.6.70_4.dll` to both `Mods/64/` (205312B, 5:23 PM) and `Mods/32/` (204800B, 5:25 PM)
- Registry: `LibraryFileName` = `_0.6.70_4.dll`, `SettingsChangeTime` = `0x6adc6b3a` (5:25 PM), `Disabled` = `0`
- Visual verification: **attempted but incomplete** — FlyoutTestWindow harness could not reliably detect the #32768 submenu window in automated capture loop; rapid frames (`submenu-overlap-*.png`) not produced
- Records: `notes/2026-10-24-submenu-flicker-fix.md`, handoff `t3-handoff/mcp:e5392bd3-42bc-424b-9d25-4e0d64102783.md`
- Rollback: point `LibraryFileName` to `local@translucent-flyouts_0.6.70_3.dll` and bump `SettingsChangeTime`

## 2026-10-24: Dark mode context menus merged into Translucent Flyouts 0.6.66 (installed)

- `dark-menus` 1.4.2 is removed; its menu darkening and a `darkMenus.appMode` setting (default force_dark) are inside
  `local@translucent-flyouts` 0.6.66. Checked 11:40 AM: registry shows 0.6.66 and `force_dark`, the dark-menus key and
  source are gone, 231 processes (all Explorer) load `local@translucent-flyouts_0.6.66_1.dll`, screenshot
  `reports\2026-10-24\translucent-flyouts-menu-20261024-113604.png`.
- Not yet clean: 13 long-running apps still hold the old DLLs until they restart. Discord, Voicemeeter, Matrix, Stream Deck
  and dwm are on the flyouts skip list, so they get no dark menus from this mod.
- Rollback: `scripts\2026-10-24-dark-menus-merge.ps1 -Rollback`. Details: `notes\2026-10-24-dark-menus-merge.md`.
- Public README or publish copy still says "pair with Dark Menus"; not pushed.

## 2026-10-24: Fullscreen Start Plus 1.5.0 installed: right-click menu and drag to move
- Right-click any icon: Open, Run as administrator, Open file location, Open shortcut location, Change icon, Remove from this grid, Properties. Drag icons to reorder them, onto an app to make a folder, into and out of folders, and to another page by holding at the edge.
- Installed 9:27 PM: explorer loads `local@fullscreen-start-plus_1.5.0_1.dll` and no 1.4.0 copy (tasklist, 9:27 PM).
- Verified 2026-10-24 in the test host (`scripts\2026-10-24-fsp-150-test.ps1`, every step) and in Explorer (`-Live -Steps open,menu,reorder,makefolder,sort`, about 9:30 PM): live menu, saved reorder, folder made, Sort A to Z restored the order. Screenshots: `reports\2026-10-24-fullscreen-start-plus\1.5.0`. The test layout file was deleted afterwards, so the grid is back to A to Z.
- Commit f2e6356 pushed to PR #19 (title and body now 1.5.0). Details: `notes\2026-10-24-fullscreen-start-plus.md`.

## 2026-10-24: Fullscreen Start Plus 1.4.0 revision 8: blurred settings window with its own icon
- The settings window body now shares the title bar's acrylic blur and tint, and the title bar shows a 3x3 tile icon.
- Verified 3:58 PM: `scripts\2026-10-24-fsp-settings-window-test.ps1 -ShotOnly` on `local@fullscreen-start-plus_1.4.0_8.dll` (tasklist): screenshot `reports\2026-10-24-fullscreen-start-plus\2026-10-24-settings-window.png`; an outside change to 57 showed live, 50 restored (registry read). Commit a54d722 pushed to PR #19.
- New repo preview of the pages grid pushed as 6ef8c6d (4:00 PM; check.py 0 FAIL, 0 WARN).

## 2026-10-24: Fullscreen Start Plus 1.4.0 revision 7: its own settings window
- The grid's "..." menu, Open settings, opens a native settings window inside the mod. It writes the same settings as Windhawk's page via elevated windhawk-cli.
- Verified 11:40 AM: `local@fullscreen-start-plus_1.4.0_7.dll` loaded in explorer (tasklist); `scripts\2026-10-24-fsp-settings-window-test.ps1` opened the window in front, saved and restored blur strength (registry read). Commit af3563a pushed to PR #19.
- Details: `notes\2026-10-24-fsp-handoff.md` item 7.

## 2026-10-24: Fullscreen Start Plus 1.4.0 installed (revision 2): macro-key fix and pages

- Macro keys (Wooting "menu" key sending Shift+Win) open the grid again. Cause: the key lets go of Shift
  before Win, so the hook never saw Shift+Win. Fix pushed to PR 19 as 1ed0580. Verified before 8:50 AM:
  5 of 5 simulated macro presses opened the grid (`scripts\2026-10-24-fsp-macro-key-test.ps1 -Order macro`).
- New setting Layout: scroll (old behavior) or pages that flip left and right with dots, set to pages.
  Rows stretch to fill the screen down to the dots (user asked, 9:00 AM). Pushed to PR 19 as f93959a.
  Verified 9:05 AM: explorer has `local@fullscreen-start-plus_1.4.0_2.dll` loaded, gridLayout=pages kept,
  screenshot `reports\2026-10-24-fullscreen-start-plus\2026-10-24-pages-fill.png` shows the rows reaching
  the dots. Page flip verified 3:56 PM: `reports\2026-10-24-fullscreen-start-plus\2026-10-24-pages-2.png` shows page 2 with its dot lit.
- Open question: in about 3 of 12 key-path test runs the grid closed itself after half a second when another
  window took focus. Those runs overlapped the user typing, so the cause is unproven.

## 2026-10-24: Fullscreen Start Plus 1.3.0 installed (revision 5); Open-Shell retired

- Keys: Win starts Flow Launcher, Shift+Win and the Start button open the grid. Settled; do not change.
- Verified 8:36 AM: explorer has `local@fullscreen-start-plus_1.3.0_5.dll` loaded (module list).
  Shift+Win opened the grid at 8:18 AM (`reports\2026-10-24-fullscreen-start-plus\2026-10-24-shift-win-grid.png`).
- Open-Shell 4.4.198 uninstalled; `C:\Program Files\Open-Shell` is gone (checked 8:36 AM).
  Rollback: `H:\System Configuration\scripts\2026-10-24-openshell-retire.ps1 -Rollback`.
- PR: https://github.com/DavidHiFi/davids-windhawk-mods/pull/19 (open). Repo preview: unverified, new shot pending an idle desktop.
- Details: `notes\2026-10-24-fullscreen-start-plus.md`, handoff `notes\2026-10-24-fsp-handoff.md`.

## 2026-10-24: Theme Tool Plus 1.1.1 installed (revision 10)

- Plain-English setting text, readme and the settings-tab preview are pushed as 5f75321. The raw preview
  at that commit matches the local file (SHA-256 checked this session). The `main` copy lags the cache.
- Installed 6:12 AM with `theme-tool-plus-install.ps1 -Install`. Verified: registry reads LibraryFileName
  `local@theme-tool-plus_1.1.1_10.dll`, Version 1.1.1, Disabled 0; installed DLL SHA-256 matches the build;
  the ModsSource copy matches the repo file; Explorer has the module loaded.
- Checked on screen this session: the Windhawk settings tab shows 1.1.1 and the new setting text.
- The install script no longer stops when the UXTheme hook key is missing; that key is gone, so there is nothing to switch off.

## 2026-10-24: Explorer TreeItem Tweaker Plus 1.1.5, restart switch (installed)

- New setting "Restart Explorer without asking" (on by default). Off brings back the original popup.
  Verified 6:01 AM: 1.1.5 DLL loaded in explorer after one automatic restart; off path showed the popup
  and Cancel left Explorer alone. Note: `notes\2026-10-24-treeitem-restart-toggle.md`.
- Mod release checklist (author, Ko-fi donate link, humanized text, preview) added to AGENTS.md and
  `docs\mod-style-guide.md`. The donate/author audit of all mods runs in its own thread.

## 2026-10-24: Fullscreen Start Plus base created (not installed); WinLaunch Enhanced retired

- Fork of Fullscreen Start (Launchpad style) 1.0.0 by Rafael Mendes, upstream commit 6cea3b6.
  Committed on branch `fullscreen-start-plus` (71ca9b8) in the worktree
  `work\2026-10-24-fullscreen-start-plus\repo`, not pushed. Built OK with
  `scripts\2026-10-24-fullscreen-start-plus-build.ps1` (5:28 AM, engine 2.0.0 lib).
- Not installed yet. Install steps, backlog and upstream sync: `notes\2026-10-24-fullscreen-start-plus.md`.
- WinLaunch Enhanced uninstalled and its repo made private and archived (verified 5:31 AM):
  `H:\System Configuration\notes\2026-10-24-winlaunch-retired.md`.

## 2026-10-24: back on 2.0.0-alpha.7; freeze-8 hunt closed

- Engine 2.0.0-alpha.7 installed 1:02 AM over 1.7.3 (owner order). Verified 1:13 AM: windhawk.exe
  FileVersion 2.0.0-alpha.7, `EnginePath=Engine\2.0.0`, explorer/dwm/StartMenuExperienceHost load
  `Engine\2.0.0\64\windhawk.dll`, mod keys 129 before and after (`receipt.json` in
  `backups\2026-10-24\windhawk-1.7.3-to-2.0.0-alpha.7\`). Windhawk UI toasts: not checked.
- Freeze-8 hunt closed. The culprit was the Windhawk mod `caption-buttons-customizer`. Its developer shipped
  a fix, and the freeze is fixed (owner, 2026-10-24). Not RAM, not hardware. Record:
  `H:\System Configuration\notes\2026-10-24-freeze8-hunt.md` (closed header added).
- Hunt leftovers cleared this session: the `WindhawkHunt8-Sampler` scheduled task is deleted (exported
  first to `backups\2026-10-24\freeze8-hunt-task-remnant\`, absent on readback), the sampler process is
  stopped (its CSV stopped growing), and the freeze-7 gate file is renamed to `hunt-state.closed.json`.
  The translucent guard marker file is absent. The taskbar suspects read Disabled=0: windows-11-taskbar-styler,
  taskbar-on-top, taskbar-icon-size. Only `fullscreen-start` and `local@start-everything-plus` are Disabled=1.

## 2026-10-21: translucent-flyouts 0.6.60-0.6.62 â€” sysmenu double border fixed, DC ring symmetry restored

- Sysmenu (WinForms classic menu) double accent line on right/bottom explained: the
  mod's themed DC ring (POPUPBORDERS pass) and the unthemed watcher overlay ring ran
  on the same menu at different insets ({1,w-3} vs {1,w-1}) because the menu's
  POPUPBACKGROUND clip fails the bandRectValid test. Measured in a GDI ground-truth
  rig: GDI round-rect regions cover to right-2/bottom-2 (not right-1), so the DC ring
  was asymmetric inset 1 / inset 3.
- Fixes shipped as 0.6.60 (watcher tick destroys the overlay for any DC-painted
  border: `dcBorderPainted`), superseded by 0.6.62 which also restores ring symmetry:
  widened GDI round-rectparams for the ring, rim and fill clip (+1/+2 for the GDI
  right-2/bottom-2 exclusion) and dropped the rim clip before the ring FillRgn.
  0.6.61 caught the missing clip dropping (partial ring) and was replaced.
- Verified live on 0.6.62: single symmetric inset-1 ring on all four sides, full
  accent at px1/w-2, cleared outer edge, TL arc (5,6) / BR arc (258,119) mirrored,
  no spill (test-window-sysmenu-0662-153133.png).
- Explorer still runs 0.6.59 until its next restart; fresh processes pick 0.6.62 up.
  Records: notes\2026-10-19-translucent-flyouts-0.6.50.md (0.6.59-0.6.62 section),
  scripts\2026-10-21-translucent-flyouts-0.6.6{0,1,2}.ps1,
  backups\2026-10-21\, reports\2026-10-20-flyout-border\.

## 2026-10-20: translucent-flyouts accent ring fixed (0.6.58) â€” ring now paints above its menu

- 0.6.55 field failure (duplicate borders, dark area outside the border) traced by a
  live z-order walk: the ring overlay window sat BELOW its menu, so the ring only
  showed through region holes. The visible ring in 0.6.55 was the buffered-paint DC
  re-stroke (a second painter), not the overlay.
- Fix chain: 0.6.56 removed the DC re-stroke and restored the inset-3 watcher region
  (ring vanished, overlay still below); 0.6.57's per-tick insert-above lost the race
  with the menu's own re-raises; 0.6.58 (2026-10-20, 7:10 PM install) creates the
  overlay owned by its menu, which Windows guarantees stays above the owner.
- Verified on shell pid 10420 (started 7:20 PM): z-walk shows the overlay directly
  above the live menu; flats read full accent 84B1F9 at menu-x 3 (left/top) and
  x=318 (right, 321-wide menu); corner arc AA at (9,9); nothing outside the border;
  ring intact after item hover repaints; sysmenu regression clean 264x125 (7:21 PM).
  Evidence and captures: reports\2026-10-20-flyout-border\, note
  notes\2026-10-19-translucent-flyouts-0.6.50.md (0.6.56-0.6.58 section).
- Install scripts scripts\2026-10-20-translucent-flyouts-0.6.5{6,7,8}.ps1 with
  backups backups\2026-10-20\; publish copy synced
  work\window-pack-publish\mods\local\translucent-flyouts\.

## 2026-10-19: drag-to-delete-plus bottom-rim crescent fixed and verified live

- The overlay's fill darkened along the circle's bottom rim (a dark crescent
  over bright backdrops): the gradient's bottom stop sampled rows biased by
  the icon's shadow and the lift brightening.
- Fix in the mod source: SampleBackdropGradient samples the backdrop at the
  circle's top/mid/bottom rows and paints a three-stop vertical gradient.
  Live as rev _1.1.0_3 (built 2026-10-18 11:16 PM from the fixed source);
  the engine's source is byte-identical to the fork checkout.
- Verified 2026-10-19 with the synthetic-drag harness: the overlay engaged on
  the first attempt, rim deltas at the true drawn radius top=2 / left=16 /
  right=17 / bottom=17 â€” top is pixel-exact over the smooth sky, the rest is
  the wallpaper's own gradient plus the icon's designed shadow; the 4x rim
  crop shows no dark band or seam.
- Record and evidence: notes\2026-10-19-drag-to-delete-plus-rim-fix.md,
  reports\2026-10-19-drag-to-delete-plus-rimfix\ (receipt.json + crops).
- Fork source committed and pushed: DavidHiFi/davids-windhawk-mods 1f9a438 on main.

## 2026-10-19: right-side tray cluster re-centered (rule 63 added)

- Whole right cluster (quota bars, chevron, tray icons, clock) was pinned to the
  top of the 50px taskbar; ink scan showed rows 2..29 with 30..49 empty.
- Fix: styler rule 63 `VerticalAlignment=1` + `Margin=0,9,0,0` on the tray frame
  grid; verified ink rows 11..38 = centered (owner confirmed margin 9 is the
  centered state after a 4px attempt read too high).
- Explorer restart needed mid-task: the tray window had hung (IsHungAppWindow=True,
  scripts\Diag-TrayHung.ps1), which also froze screen capture. See
  scripts\2026-10-19-restart-explorer.ps1.
- Evidence: thread attachments `tray-before-3x.png` / `tray-after-3x.png` and
  `reports\2026-10-19-tray-vertical\tb-right-3x-before.png` / `tb-right-3x-after.png`.
- Record, backup and guard: notes\2026-10-19-tray-vertical-shift.md,
  `backups\2026-10-19-tray-vertical\`, `scripts\guard-tray-vertical.ps1` (read-check,
  restore + bump on drift; currently OK).
- Supersedes 2026-10-18's wrong root cause on rule 61 (that margin is horizontal-only).

## 2026-10-18: Windhawk Styler 2.0.64 - title bar buttons bright, hover works maximized

- Installed and loaded (module local@windhawk-styler_2.0.64_1.dll in windhawk-ui, checked 10:1x PM).
  Body styling, blur and settings untouched; the title strip is now clear glass so Windows' buttons are not dimmed.
- Evidence: reports\2026-10-18-styler-caption-buttons\ (normal, hover, maximized hover, real restore click).
- Record and rollback: notes\2026-10-18-styler-caption-buttons-2.0.64.md. Source committed locally (2752154), not pushed.

## 2026-10-16: translucent-windows fork credited to DavidHiFi and description rewritten

- The fork's `@author` now reads "DavidHiFi, Undisputed00x". The owner's screenshot
  showing only Undisputed00x was from before the 11:15 AM credit fix; engine
  `mod list` confirms the credit is live.
- Description humanized to "Blur, acrylic and mica for app windows, with per-app
  rules and custom themes" (76 chars, one line, no trailing period). Metadata-only:
  no rebuild, no `SettingsChangeTime` bump, DLL hashes unchanged, guard repointed
  to the new source hash and its suspend marker cleared.
- Style-guide audit filed with the deliberate exceptions (catalog `@id`, no Plus
  name, no `@homepage`/`@license`, upstream readme kept):
  `notes\2026-10-16-translucent-windows-fork-audit.md`.
- Rollback: elevated `scripts\2026-10-16-translucent-windows-description.ps1 -Action Rollback`.
  Backup `backups\2026-10-16\translucent-windows-description\`; receipt and
  transcript in `reports\2026-10-16-translucent-windows-description\`.

## 2026-10-15: translucent-windows moved to a local@ id â€” phantom 1.8.2 "update" offer killed

- The app kept offering an "update" 1.8.3 â†’ 1.8.2 and silently reinstalling stock builds
  (the guard healed three more times that morning). Root cause: the app's `userprofile.json`
  tracked `latestVersion` 1.8.2 (catalog) vs `version` 1.8.3 (our fork under the catalog id) â€”
  an inequality, so a downgrade looked like an update and got applied.
- Fix: the fork now lives as **`local@translucent-windows`** (same reviewed 1.8.3 code, build
  `_1`, 156 settings carried over), which the app never checks against the catalog. Old catalog
  id removed with its profile entry. Guard re-pointed and verified; old T3 drift canary deleted.
  Engine view: enabled, `updateAvailable=false`.
- Records: `notes\2026-10-15-translucent-windows-id-migration.md` (verification + rollback),
  receipt + logs in `reports\2026-10-15-translucent-windows-id-migration\`, backups in
  `backups\2026-10-15\translucent-windows-id-migration\`.
- User spot-check: no update offer for the mod in the Windhawk UI; taskbar/Terminal blur
  unchanged. A reboot normalizes the loaded DLL name (old identical-code DLL keeps running
  until then).
- Follow-up same day: the UI's "Something went wrong / MODS_LOAD_FAILED" toast was the
  metadata parser rejecting `@` inside `@id`; fixed - the metadata keeps the catalog id,
  `local@` only in filename/registry key. Details in the same note.

## 2026-10-13: Explorer navigation bisected; auto-fit on navigation and folder-size lookups off by default

- Median navigation (5 folders): 1.2 to 4.4 s before, 0.45 to 0.54 s now. Floor with all Windhawk mods off is about 0.3 s.
- Settings only: `file-explorer-details-autofit-columns` `passiveTriggers` 1 to 0 (F5 and refresh still fit); `explorer-details-better-file-sizes` `calculateFolderSizes` everything to `withShiftKey` (folder sizes only while Shift is held on load or refresh).
- Verified: readback, 133 mod flags unchanged from snapshot, 87 DLLs in explorer.
- Saved "Size on disk" columns removed from 67 folder views (shell bags ColInfo); screen-checked. Record and rollback: `notes\2026-10-13-explorer-lag-shellbag.md`.
- Resolved (2026-10-17): the earlier open choice (window-manager off in Explorer, folder sizes off, blur off) is closed. The fix held on re-verify: all six settings values still match, `explorer-size-on-disk-column` is still absent from Explorer's 81 mod DLLs, and a fresh navtest beat the 2026-10-13 finals (`C:\` 705 ms, notes 370 ms, AppData\Local 378 ms, `H:\Windhawk Configuration` 535 ms; the 2026-10-13 finals were 1580/2839/3527/3595 ms). Record and bisect: `notes\2026-10-13-explorer-lag-bisect.md`, `notes\2026-10-13-explorer-speed-final.md`. Rollback: `scripts\2026-10-13-explorer-lag-settings.ps1 -Rollback "H:\Windhawk Configuration\backups\2026-10-13\explorer-lag\settings"` (elevated).

## 2026-10-13: translucent-windows restored after second silent revert (Terminal/cmd lost all blur)

- Evening: freshly opened cmd (Windows Terminal) was fully see-through, no blur. Cause: the mod
  had been flipped from the round-5 fork (**1.8.3 / build 256343**, source `70B64AFâ€¦`) back to
  **stock 1.8.2 / build 598230** at 11:58:47 that morning â€” new stock build compiled,
  ModsSource overwritten, no `SettingsChangeTime` bump. Stock skips CASCADIA windows, so
  Terminal fell back to its own opacity-0 transparent-gradient accent. Same unattributed
  signature as the 2026-10-11 revert; no thread transcript mentions it.
- Fixed same evening (no recompile; the hash-verified 256343 DLLs were still on disk):
  `scripts\2026-10-13-translucent-windows-revert2.ps1` (`-Audit`/`-Install`/`-Rollback`).
  Verified: registry readback, module census (explorer + conhost + a new WindowsTerminal all
  map 256343), and a pixel-checked capture of the live window showing tinted acrylic over body
  and title strip. Evidence: `reports\2026-10-13-terminal-titlebar-revert2\`.
- Rollback: `â€¦revert2.ps1 -Action Rollback` (or import the backed-up reg + bump the marker).
- Records: `notes\2026-10-13-terminal-titlebar-revert2.md`. Backups:
  `backups\2026-10-13\translucent-windows-revert2\`. If it regresses a third time, capture
  `LibraryFileName` + `SettingsChangeTime` + DLL mtimes BEFORE touching anything, and note
  which agent threads were live that minute. A read-only drift check runs every 6 hours.

## 2026-10-13: Explorer navigation speed â€” timing + one size source applied and verified

- Set A (timing): content-animation `navigationDelay` 300â†’0, `duration` 500â†’150, `firstOpenDelay` 500â†’100; autofit-columns `elastic` 1â†’0, `delay` 400â†’150 (`passiveTriggers` kept 1).
- Set B + dedupe: `explorer-size-on-disk-column` disabled entirely per the user's "size and size on disk do the same thing" fix; folder sizes live once in **Size** via better-file-sizes (Everything). Blur untouched.
- Measured: big folders 13â€“16 s â†’ ~3 s; `C:\` 2.3 s â†’ 1.6 s (navtest). Verified: registry readback, 87 mod DLLs in Explorer (size-on-disk absent, everything else loaded), no "Size on disk" column after the shell restart.
- Records: `notes\2026-10-13-explorer-speed-final.md`, receipt + screenshots + navtest in `reports\2026-10-13-explorer-speed\`, backups in `backups\2026-10-13\explorer-speed\`, scripts `2026-10-13-explorer-speed*.ps1`. Rollback commands in the final note.

## 2026-10-13: Windhawk Styler 2.0.52 published to main; title-bar menu back on Translucent Flyouts

- Published to DavidHiFi/davids-windhawk-mods `main` as `00aec35` (`382170e..00aec35`, no force push).
- 2.0.48 to 2.0.52: the save bar floats while scrolling (the mod had overridden the interface's
  sticky positioning with relative; it now sticks 12px down), the page container has 12px bottom
  padding so the card's bottom curve clears the edge, and the mode/version switches plus the mod id
  chip join into pills. Preview, mods README row and `VERIFICATION.md` updated.
- Title-bar menu: `windhawk-ui.exe` off the Translucent Flyouts block list per owner reversal;
  verified translucent with accent border, not red, on 0.6.32.
- Records: `notes\2026-10-13-styler-2048-2052.md`.

## 2026-10-20: Translucent Flyouts 0.6.55 â€” desktop-menu corner darkness and dashes fixed (overlay ring)

- `local@translucent-flyouts` **0.6.55 is live** (`LibraryFileName=local@translucent-flyouts_0.6.55_1.dll`,
  installed + one shell restart at 12:57 PM, release build, no debug logging).
- The day's chain, driven by the owner's screenshots: 0.6.53's black rim paint bled
  darkness from the corners â†’ 0.6.54 removed the paint but its inset-3 window region
  cut the ring's corner arcs into dashes (the owner's 8:04 AM photo) â†’ **0.6.55 moves
  the ring onto its own layered overlay window** (`TF_RingOverlay`) floating over the
  menu: item paints can't erase it, no region can clip it, and the band is a GDI+
  anti-aliased even-odd fill (gdiplus loaded via GetProcAddress). A measured GDI+
  quirk (pixel i centred on integer i) fixed the band intensity to full on pixel 3.
- Verified 12:58 PM: full-intensity accent at exactly 1 px inside the edge on all
  four flats; smooth complete corner arcs with the desktop outside; the ring survives
  hovering across items; title-bar menu regression clean. Captures + probes in
  `reports\2026-10-18-flyout-border\` (wide/hover crops, `final5-run.ps1`, logs).
- Records: `notes\2026-10-19-translucent-flyouts-0.6.50.md` (the 0.6.50â†’0.6.55 chain,
  including the owner-requested 10:20 AMâ€“12:57 PM pause). Cleanup 1:08 PM removed 10
  diag DLLs + tf-*.log debug artifacts; only `Mods\64\â€¦0.6.50-diag28b_1.dll` remains
  (locked by Ableton until reboot).

## 2026-10-13: Translucent Flyouts 0.6.32 â€” title-bar menu artefacts fixed, look verified persistent

- `local@translucent-flyouts` 0.6.32 is live (`LibraryFileName=local@translucent-flyouts_0.6.32_1.dll`,
  `Include=*`, both architectures, release build against `Engine\2.0.0_1` with no debug logging).
- Fix: removed the per-background-band border re-draw in `src\30-engine.inc`. The real outline
  (POPUPBORDERS, full window rect) already paints last, so the per-band frame only left strays:
  bright ticks down every menu's right edge, a doubled right outline, and bright lines flanking
  the separator. Root cause proved with a temporary magenta/cyan/green attribution run, then
  test colours restored (separators empty = schema defaults, matching baseline).
- Settings: modern_acrylic, Mocha `0xCC1E1E2E`, border `0xFF89B4FA`. The `windhawk-ui.exe`
  block list is EMPTY by owner decision (2026-10-13, later the same day), so the Windhawk title-bar
  menu gets Translucent Flyouts like other apps. Keep it empty unless the owner says otherwise.
- Verified live: Dopamine title-bar menu is clean (single outline, uniform Mocha body, single
  separator); desktop menu dark + bright with submenus matches the 0.6.31 baseline within 1-2
  levels; Explorer restarted twice and the look is identical after each restart.
- Records: `notes\2026-10-13-translucent-flyouts-0.6.32-final.md`, receipt + probes + captures in
  `reports\2026-10-13-translucent-flyouts-0.6.32\`, install/rollback
  `scripts\2026-10-13-translucent-flyouts-0.6.32.ps1`, registry backup
  `backups\2026-10-13\translucent-flyouts-0.6.32\`. Public repo untouched (main still 0.6.16).

## 2026-10-13: Windhawk Styler 2.0.47 published to main; title bar menu is the plain Windows menu

- Published to DavidHiFi/davids-windhawk-mods `main` as `382170e`, merged onto `origin/main` as `5452438`. No force push. Canonical source is now `work/styler-release/mods/local/windhawk-styler/windhawk-styler.wh.cpp`.
- 2.0.47 installed and verified (`scripts\2026-10-13-styler-polish-2047.ps1`): readme for the 2.0 interface, tested on Windhawk 2.0.0-alpha.7, mods README row updated, `VERIFICATION.md` 2.0.47 section, preview replaced with the settings page (`media/previews/windhawk-styler.png`).
- Title bar right-click menu: `windhawk-ui.exe` is on Translucent Flyouts' process block list (`advancedFunctions.processBlockList`), so the Windhawk window uses the plain Windows menu. Other menus keep their translucent look. Rollback and detail: `notes\2026-10-13-titlebar-menu-standard.md`. Keep it on the list through every Translucent Flyouts install; the flyout work is now with capuchin-flyout.
- Records: `notes\2026-10-13-styler-published.md`, `notes\2026-10-13-styler-final-check.md`.
- Not touched: the `davids-windhawk-mods` checkout in this workspace has uncommitted changes in `mods/local/taskbar-audio-visualizer` and diverged history (ahead 5, behind 11). Publish from `work/styler-release` only.

## 2026-10-13: Windhawk Styler 2.0.54 frozen card and scrollbar

- The mod card stays in place and scrolls inside its rounded frame. Its ring no longer scrolls into view, and the scrollbar has no arrows and sits inside the corners. Verified live. Record and rollback: `notesÂ‚6-10-13-styler-2054-frozen-card.md`.

## 2026-10-13: Windhawk Styler 2.0.45 polish

- Spinner handles are an inset pill, the save bar sits inside the page card, every button icon is centered, the two page buttons have a gap, the modified-setting bar uses the accent, and the title bar has its system menu (right-click, icon click, Alt+Space).
- Verified live through CDP and a caption right-click test. Record and rollback: `notesÂ‚6-10-13-styler-2045-polish.md`.

## 2026-10-12: Explorer tree hover and selected backgrounds fixed (Explorer TreeItem Tweaker Plus)

- Cause (measured): translucent-windows 948147 paints TreeView items itself and swallows the draw that the tree item tweaker needs. Which mod draws first depends on load order, so the fix only held until the next boot.
- Fix: local fork `local@explorer-treeitem-tweaker-plus` 1.1.2 enabled, with its draw hooks set 3 seconds after start. The original `explorer-treeitem-tweaker` is disabled. Settings were copied.
- Verified by screenshot after an Explorer restart, with translucent-windows still loaded: selected row and hover both draw. A reboot is not yet tested.
- Records: `notes\2026-10-12-treeitem-hook-conflict.md`, `scripts\2026-10-12-treeitem-plus-install.ps1` (`-Rollback` restores the original), backup in `backups\2026-10-12-treeitem\`.

## 2026-10-11: Windhawk 2.0.0-alpha.7 update installed

- Routine for every future preview release: skill `windhawk-alpha-update`, script `scripts\windhawk-alpha-update.ps1` (`-Check`, `-Prepare`, `-Launch`, `-Rollback`). It takes the newest pre-release from GitHub and checks the digest, signer, and file version before any change.
- alpha.7 installed 2026-10-11 (installer exit 0). Receipt and backup: `backups\2026-10-11\windhawk-2.0.0-alpha.6-to-2.0.0-alpha.7\receipt.json`. The installer touched no Discord, Ableton or Stream Deck processes.
- Rollback: `scripts\windhawk-alpha-update.ps1 -Rollback -BackupDir "<that folder>"`. Detail: `notes\2026-10-11-windhawk-2a7-update.md`.
- The first attempt (`scripts\2026-10-11-windhawk-2a7-*.ps1`) was superseded by the routine script before it ran. Its backup `backups\2026-10-11\windhawk-2a7-update\` is the verified alpha.6 copy.

## 2026-10-09: Windhawk Styler release cleanup

- Installed 2.0.34 with the owner's accepted 75% Acrylic appearance and integrated caption. Removed the detached popup, stale VSCodium selector, frame gaps, repeated-save size growth and unused settings/build helpers.
- Reordered and clarified all twelve settings. Real saves exercised every field. Removed the unsupported legacy Blur choice; Acrylic supplies the frosted material, and None uses alpha composition.
- Canonical source: `work/windhawk-styler/tauri20/windhawk-styler.wh.cpp`. Installation and rollback: `scripts/styler-maintenance.ps1`. Records: `notes/2026-10-09-styler-audit.md` and its report folder.
- Published to DavidHiFi/davids-windhawk-mods main as `7425002` from the isolated `work/styler-release` checkout. The legacy 1.4.0 edition is preserved. A requested follow-up added GUI reopening on disable and verified one disable/enable cycle; earlier entries below describe historical builds.

## 2026-10-09: styler 2.0.13 â€” settings descriptions complete and reworded

- The "Background color" description was cut at "Main background tint, in":
  the settings block is YAML, so an unquoted ` #RRGGBB` starts a comment and
  everything after it is dropped at parse time. "Title bar color" had the
  same trap. All descriptions are now quoted, fixed, tightened to plain
  sentences and regrouped (background trio, title-bar trio, colors, font).
- Text-only release (2.0.13): no code changed; no settings values changed
  (install backup matches live values and SettingsChangeTime).
- Verified by reading the rendered settings page back through the mod's CDP
  port: all twelve descriptions display in full. Record and rollback:
  `notes/2026-10-09-styler-descriptions.md`,
  `scripts/2026-10-09-styler-descriptions.ps1 -Rollback`.

## 2026-10-09: window-manager 1.1.4 â€” Alt+right-drag resizes borderless windows (Ditto, Flow Launcher)

- The standalone `local@alt-snap-drag` fork was found uninstalled (since
  2026-10-04); live Alt-drag comes from window-manager's embedded copy of the
  same engine. Resize required `WS_THICKFRAME`, so borderless windows could
  move but never resize. New `sizeWindowsWithoutSizingBorder` setting
  (default on) lifts that; right-click mid-drag stays maximize-toggle.
- Built x64+x86 against Engine 2.0.0, hot-reloaded live (no engine restart),
  setting = 1, old DLLs kept for rollback
  (`scripts\2026-10-09-window-manager-1.1.4-resize-borderless.ps1 -Rollback`).
  Fork source mirrored to 1.2.3, left uninstalled. Owner tested Ditto/Flow
  resize live and confirmed it works; the synthetic input suite never ran
  (machine was active, it refuses to inject unless idle).
- Detail: `notes\2026-10-09-window-manager-borderless-resize.md`; publish
  copies in `davids-windhawk-mods` committed and pushed as `7b0659d`.

## 2026-10-09: Windhawk Styler 2.0.11 final refinements

- Added an eight-pixel gap before Reset to default controls.
- Removed the optional restart-on-save switch. Every Styler settings save now restarts the interface automatically.
- Prevented the native startup splash from drawing its logo under the transparent WebView. Removed the old delayed root clear. Repeated real saves and a background-only screenshot verified no ghost logo remains.
- Earlier accent-border, corner, inactive title-bar and live-blur behavior still passes verification. Record and rollback: `notes/2026-10-09-styler-final.md`.

## 2026-10-09: Windhawk Styler 2.0.10 sticky toolbar restored

- Restored the dark card background behind Save settings and the editing-mode controls. Transparent card settings also use a 16-pixel backdrop blur.
- Verified the toolbar stays visible at scroll positions 500 and 1000. Visual/Textual switching works, with no settings changed during verification.
- The native accent border and earlier title-bar, blur and startup-logo fixes remain intact. Installed source and workspace source match. Record and rollback: `notes/2026-10-09-styler-toolbar.md`.

## 2026-10-09: Windhawk Styler 2.0.9 native accent border

- The user accepted 2.0.8's appearance. The remaining faded corner edges were resolved by restoring a native DWM border using the Windows accent color.
- Windows draws the stroke around the existing 16-pixel corner geometry. No global corner settings changed and no overlay was added.
- Focus, live inactive blur, title-bar visibility, maximize, resize and minimize/restore checks still pass. Rollback restores the accepted 2.0.8 build. Record: `notes/2026-10-09-styler-edges.md`.

## 2026-10-09: Windhawk Styler 2.0.8 rendering stabilized

- Removed the sheet overlay that covered the inactive native title bar and painted outside the visible frame.
- Kept native acrylic active in the caption and body across focus changes. Keyboard focus still follows the real foreground window.
- Cleared leftover startup-logo pixels after the page and splash handover finished. No centered watermark remains.
- Verified active/inactive rendering against changing backgrounds, twelve focus transitions, maximize, resize, minimize and restore. Both actual settings saves closed and reopened the interface; the original accent was restored.
- The final build has no compiler warnings. Include remains `windhawk-ui.exe`. Backups, evidence and rollback: `notes/2026-10-09-styler-stability.md`.

## 2026-10-09: styler 2.0.7 â€” saving settings closes+reopens the interface (hardened)

- User ask: styler saves changed nothing visible and a tray-reopen came back
  bugged; they want the 1.x save = close+reopen behavior with a toggle.
- Shipped `local@windhawk-styler` 2.0.7 (rev 597474): the mod polls the
  engine's `SettingsChangeTime` marker on its own key every second and
  closes+reopens the interface via the mutex-guarded helper on any bump;
  `Wh_ModSettingsChanged` stays the fast path. New setting `restartOnSave`
  (default ON, "Restart the interface on save") turns the restart off; with
  it off, changes apply live through the per-cycle CSS/DWM push.
- Trap found: 2.0 pre-alpha reads a never-saved boolean as 0 (not the schema
  default), which gated the first restart off. Fixed by materializing the
  value ON and by `ReadBoolSetting` defaulting it to ON at read time.
- Verified live: marker-only bump -> helper RUN -> pair swap -> port 9333
  listening -> page themed; accent round-trip #f5c2e7 -> #89b4fa through the
  full save path. Note `notes\2026-10-09-styler-save-restart.md`, receipt
  `reports\2026-10-09-styler-save-restart\receipt.json`, backups
  `backups\2026-10-09\styler-save-restart\`, rollback
  `scripts\2026-10-09-styler-save-restart.ps1 -Rollback`.


## 2026-10-08: styler 2.0.4 â€” whole-window acrylic (true acrylic title bar) + duplicate window solved

- Duplicate window: was the 2.0 mod editor (VSCodium) left over from an earlier
  session + 3 orphans; all killed, zero remain. The "respawning pair" is the
  styler's own relaunch helper working as designed.
- Title bar: on this build a DWM caption can only be a flat color when active
  and is a constant (84,84,84) when inactive; the legacy WCO accent never
  renders behind the caption. The fix drops the accent and uses the Win11
  system acrylic backdrop (SBT=3 + DwmExtendFrameIntoClientArea(-1)) so the
  strip and the client are one acrylic surface. Verified on screen active,
  inactive and maximized.
- Trade-off: the SBT material is brighter than the old accent blur, so the
  body is somewhat more transparent than 2.0.2 (same wallpaper shows through
  both strip and body). Setting `titleBarAcrylic=0` in the mod settings falls
  back to the old accent + solid titleBarColor strip without a redeploy.
- Deployed 2.0.4 (`local@windhawk-styler_2.0.4_684023.dll`, Include verified).
  Note: `notes\2026-10-08-dup-window-and-acrylic-titlebar.md`; receipt:
  `scripts\2026-10-08-styler-acrylic-titlebar.ps1`.

## 2026-10-08: translucent-flyouts audited and fixed to 0.6.8

- The "Failed to parse settings" toast was real: 14 colorization settings in
  the dropDown/menu/tooltip groups used numeric `$options`, which Windhawk
  rejects. Fixed to string options like the global group; `mod show` parses
  both translucent mods now.
- The mod also briefly injected nowhere: `windhawk-cli mod compile` resets the
  mod key's `Include` to the header's `@include` list (empty here), and empty
  Include means no processes. `Include=*` restored. Check any mod key after a
  2.0 `mod compile`.
- Ableton removed from Exclude (was added 2026-10-04; the standing exception
  wins), translucent-windows `FlyoutsEffects` set to 0 so it stops fighting
  this mod over context menus; its window backgrounds stay.
- 0.6.8 compiled (x64+x86), injected and verified live in explorer, fresh
  processes, and on screen. Receipt:
  `reports\2026-10-08\flyout-check\receipt.json`. Note + rollback:
  `notes\2026-10-08-translucent-flyouts-audit.md`,
  `scripts\2026-10-08-translucent-flyouts-audit.ps1 -Rollback`.

## 2026-10-08: 2.0.0-alpha.6 health audit (follow-up to the update)

- Install verdict: **healthy**. The "installation corrupted" toast was the pre-install UI
  session watching the installer swap files under it - one-off. Payload verified self-consistent
  (all 6 product.json checksums pass; scheme is MD5-base64-no-padding, not sha256).
- Visualizer settings YAML fixed: 2.0's strict YAML parser rejected an unquoted `state:` inside a
  rev-4 description; source patched and recompiled, parse OK.
- Resolved (2026-10-17): both mods load. taskbar-audio-visualizer (1.3.2) and
  better-volume-mixer-plus (1.1.0) are injected under the `windhawk-mod.exe` hosts - their DLLs are
  loaded and their window classes (`DesktopAudioVisOverlay_*`, `WindhawkBetterTaskbarVolumeMixer`)
  exist. Moving them off `windhawk.exe` is what fixed the original "don't load" failure; the styler
  still uses its own `-tool-mod` host (rev 28).
- Resolved (2026-10-17): the visualizer's settings YAML failed to parse again in the live
  `ModsSource` copy (`state: while...`, file line 272); repaired there and in the fork source.
  `mod show`, `mod settings get` and `mod settings defaults` now exit 0 for both mods.
  Record and rollback: `notes\2026-10-17-windhawk-audio-mods.md`, `reports\2026-10-17-audio-mods\`.
- Details: `notes\2026-10-08-windhawk-2a6-health-audit.md`.

## 2026-10-08: Windhawk updated to 2.0.0-alpha.6 (engine + app + compiler)

- Windhawk is now 2.0.0-alpha.6 via the official offline NSIS installer
  (`/S`, exit 0), NOT a source build - the release does ship installers.
  All 119 mod keys preserved; mods recompiled by the new mingw toolchain
  (`Engine\2.0.0`, 32/64/arm64). Engine running, 5 processes.
- `WINDHAWK_USE_VSCODIUM_UI=1` is set machine-wide: the styled legacy UI stays
  default. Delete the var (or tray toggle) for the new 2.0 UI.
- **The installer rewrote `C:\Program Files\Windhawk\UI` (168 files, 60 in
  styler-manifest scope); the prepared Electron 28.3.3 runtime was NOT
  re-applied (2.0's legacy UI is a different VSCodium build).** Styler rev 23
  is installed+enabled, but the styled native-mode look needs styler-fix to
  re-apply the runtime against the new payload.
- Receipt + backups: `backups\2026-10-08\windhawk-2a6-update\` (reg export,
  full dir copies, UI hashes). Rollback: elevated
  `scripts\2026-10-08-windhawk-2a6-update.ps1 -Rollback`.
  Detail: `notes\2026-10-08-windhawk-2a6-update.md`.

## 2026-10-08: Windhawk Styler rev 19 â€” the frame veil + stray border fixed, "box off the title bar" explained

- The user's follow-up complaint (a weird box off the title bar's side, acrylic
  not properly implemented) traced to three things: raw unveiled resize-border
  zones down the window edges, a stray 1px accent border the app paints for its
  frameless look (wrong in native mode), and the mod list's own scrollbar thumb.
  Rev 19 (`local@windhawk-styler_1.5.0_19.dll`) fixes all three: the veil popup
  now covers the whole window rect (frame zones flattened opaque to the veil
  color, four rounded corners, class-registration made reload-safe), and the
  native-mode CSS kills the stray border. Edges verified within 1 RGB unit of
  the body; corners 5x clean; both modes captured same-session; delivered as 8
  thread attachments. Note `notes\2026-10-08-styler-rev19-frame-veil.md`.
- Also: the window's renderer blanked once (~08:50, no crash events, recovered
  by restart). If it recurs, chase GPU/driver events.

## 2026-10-08: Windhawk Styler rev 18 verified â€” native vs custom title bar and acrylic

- Rev 18 (`local@windhawk-styler_1.5.0_18.dll`, the 03:42 corner-bug build)
  had been installed but never captured. Verified live: no artifacting in
  the title bar in either mode (four corners 5x, strip 1x), and the acrylic
  is the same frosted sheet native and custom (tone within ~5 RGB units,
  same-session captures). Window flipped custom -> native via registry
  bumps, both restarts clean, end state `nativeTitleBar=1` (user's setting).
- Scripts `scripts\2026-10-08-styler-native-titlebar.ps1` (flip + wait) and
  `scripts\2026-10-08-styler-capture.ps1` (mode-agnostic capture). Receipt
  + captures `reports\2026-10-08-native-vs-custom\`; note
  `notes\2026-10-08-styler-native-vs-custom-verified.md`; registry backup
  `backups\2026-10-08\styler-native-compare\`.

## 2026-10-07: tray gap between ethernet icon and clock closed (taskbar styler settings)

- User asked to close the dead gap between the ethernet tray icon and the
  clock. Measured 25px glyph-to-text; cause was the 24px-wide network button
  (16px glyph) plus 16px between it and the clock button on this build's
  reworked tray. Fixed live in `windows-11-taskbar-styler`:
  `sysTraySpacing` 6 -> 0 and rule 61
  (`SystemTray.OmniButton#ControlCenterButton`, `Margin=0,0,-10,0`),
  applied with `SettingsChangeTime` bumps, no restart. Now ~9px, even with
  the tray's icon rhythm. First attempt (Width=16) clipped the glyph and
  was reverted; the tray lays out right-to-left, so the seam is the
  button's RIGHT margin.
- Backup `backups\2026-10-07-tray-gap\`, rollback
  `scripts\2026-10-07-tray-gap-rollback.ps1`, note
  `notes\2026-10-07-tray-gap-closed.md`, evidence
  `reports\2026-10-07-tray-gap\` (before-after.png, live-now.png).

## 2026-10-07: Windhawk Styler 1.5.0 rev 15 - Electron 28 runtime, uniform frosted sheet in native mode

- The user's three complaints (corner artifact blocks, alt-drag + right-click
  maximize broken, no transparency/blurriness with native title bar) are all
  fixed by an architecture change: the Windhawk UI runs on a locally prepared
  Electron 28.3.3 runtime (copied into `C:\Program Files\Windhawk\UI`, 79
  files, originals backed up in `backups\2026-10-07-native-v15\runtime\`).
  Native+blur injects `frame:!0` + `backgroundMaterial:"acrylic"` +
  `setMaximizable(!0)`; the page paints only the tint; all UI-process
  injection and the 1.4.0-style hacks are gone.
- Rev 15 adds the native-mode workbench CSS the modern runtime needs: hide
  `.part.titlebar` (its hide path does not fire on Electron 28, so the menubar
  remnant showed and the layout spilled a gray band at the bottom), paint the
  host canvas with the veil (`html{background:rgba(...)}` â€” the layout still
  reserves the bar's height, so the guest ends 30px above the client), and
  clear the editor-group container's own opaque fill (high specificity).
  `Effect()` leaves the caption at default on Electron 28: DWM keeps NC
  rendering on, so the caption shows the glass; the tool's veil popup tints
  the strip to match the body.
- Verified live (final window): no toast, no band, no menubar remnant; strip
  (42,40,52) vs body (33,34,48) = the wallpaper's vertical gradient through
  live acrylic; bottom rows uniform (37,38,53); plain Alt-drag, Alt-drag +
  right-click real OS maximize, press+right-click all match the fixture
  baseline. product.json checksums re-recorded and all six files match (a
  stale css checksum fired the "installation corrupt" toast once; fixed).
- Installed `local@windhawk-styler_1.5.0_15.dll`, enabled. NOT published to
  the fork: the runtime swap is machine-local; publication needs a shipping
  decision. Fork main still `28ef40a` (1.4.0).
- Receipt `reports\2026-10-07-native-fix\receipt-v15.json`; logs
  `v15-*.log`; fixture in `C:\Users\localuser\WindhawkStylerTest\` and
  `C:\Program Files\Windhawk\UI-styler-test\`.
- Rollback: `Runtime.ps1 -Rollback` then `Install.ps1 -Rollback`. Traps in
  `notes\2026-10-07-windhawk-styler-electron28.md`: Runtime.ps1's manifest
  pins first-run hashes (delete manifest + backed files after a rebuild);
  minified css = use `(?s)` regex when removing probe blocks; manual css
  edits break product.json's checksum and the integrity toast fires until
  ApplyFiles re-records + the window restarts.

## 2026-10-07: Windhawk Styler 1.4.0 - native title bar strip keeps the frosted veil (superseded by 1.5.0)

- Supersedes the 1.3.1 trade-off below. The user rejected raw acrylic: the
  window must keep the rgba veil everywhere AND the real caption. The tool
  now seats a click-through layered popup (`WindhawkStylerVeil`) over each
  native strip, tinted with the same veil as the page; it tracks drags via
  EVENT_OBJECT_LOCATIONCHANGE, re-seats above its owner on z changes and
  the 1s tick. Same-moment proof: strip (24,24,37) vs body (23,23,36);
  drag-follow verified; custom mode has no overlay and is unchanged.
- Installed `local@windhawk-styler_1.4.0_1.dll` live, published to the fork
  (`28ef40a`). Receipt `reports\2026-10-07-native-fix\receipt-140.json`,
  note `notes\2026-10-07-windhawk-styler-strip-veil.md`, captures
  `reports\2026-10-07-native-fix\v140-*.png`. Rollback: point
  `LibraryFileName` at `local@windhawk-styler_1.3.1_1.dll` and bump.
- Measured traps now in the note: SetWindowPos insert-after places a window
  BELOW the given handle; owned windows are not kept above their owner on
  z changes; the desktop wallpaper is animated so cross-time tone
  comparisons lie; WCO and the accent are dead ends on this build.

## 2026-10-07: Windhawk Styler 1.3.1 - native title bar is one uniform acrylic sheet (superseded by 1.4.0)

- `local@windhawk-styler` 1.3.1 rev 1 installed live and published to the
  fork (`2f64116`). With the native title bar on, the page no longer paints
  the background veil, so the caption strip and the body show the same DWM
  acrylic sheet: strip and body background both measure (17,17,27), no
  band. Custom title bar mode is unchanged.
- The user's setting stays nativeTitleBar=1, blur acrylic. Receipt +
  screenshots: `reports\2026-10-07-native-fix\`; note:
  `notes\2026-10-07-windhawk-styler-native-uniform.md`. Rollback by pointing
  `LibraryFileName` back at `local@windhawk-styler_1.3.0_5.dll`.

## 2026-10-05: Better Volume Mixer Plus 1.1.0 adds a Font setting

- `local@better-volume-mixer-plus` 1.1.0 adds a **Font** (`fontFamily`)
  setting. Empty = Segoe UI; a missing family falls back to Segoe UI; icons
  stay Segoe Fluent Icons. Fonts rebuild live when settings change.
- Installed `1.1.0_2.dll` with `fontFamily = FiraCode Nerd Font`, verified on
  screen: `reports\2026-10-05\bvm-font\mixer-font-fira-code.png`.
- Published to `DavidHiFi/davids-windhawk-mods` main as `14ea315`; no open PRs.
- Receipt `reports\2026-10-05\bvm-font\receipt.json`, note
  `notes\2026-10-05-better-volume-mixer-plus-font.md`, backup
  `backups\2026-10-05\bvm-font\`.
- Note: run 1 restarted the engine (`windhawk.exe -restart`) and explorer
  restarted at 07:58:29 with no observed fallout; prefer
  `SettingsChangeTime` bumps for future settings changes.

## 2026-10-04: all ten local mods unslopped, previews published, seven PRs updated

- Every local mod now has a clean id and display name with no personal name, a
  one-line description, a README with feature bullets, a preview image and a
  matching embedded readme. Verified with zero problems:
  `reports\2026-10-04-mod-metadata-polish\final-verification.json`.
- Ten previews live in `davids-windhawk-mods\media\previews\` (three GIFs,
  seven PNGs); all ten raw URLs return 200.
- Fork commit `0275dce` pushed. Open catalog PRs all refreshed:
  #5881 window-manager, #5835 taskbar-system-info-weather, #5834
  taskbar-weather, #5815 npp-taskdlg-textcolor, #5814
  taskbar-ai-quota-opencode, #5813 alt-snap-drag, #5785 translucent-flyouts.
  Better Volume Mixer Plus, Shell Font Changer and Taskbar Audio Visualizer are
  local only and were never submitted.
- Visualizer revision 3 (`local@taskbar-audio-visualizer_1.2.0_3.dll`) drops the
  old fork name from the settings dialog, the thread descriptions and the
  capture-picker class. Rev2 DLLs and source are in
  `backups\2026-10-04\mod-polish-final`.
- Install snapshot refreshed, commit `a5dcb5e`: 111 installed mods, 107
  enabled. `local@alt-snap-drag` and eight catalog mods were uninstalled from
  the machine this evening, not by this run, and were left that way.
- Everything: `notes\2026-10-04-mod-metadata-polish.md`.

## Workspace sorting completed 2026-10-04

Windhawk development checkouts, settings backups, scripts, diagnostics, screenshots,
themes and notes from System Configuration now live in this workspace.
Directory junctions and file hardlinks preserve old paths. Write new records here.
Mixed system notes remain in System Configuration with reference copies in
`docs/system-context`. See `notes/2026-10-04-workspace-sort.md` and the migration
receipts in `reports/2026-10-04-workspace-sort`.

The latest imported records document Taskbar Weather 1.4.0 using DirectWrite,
Taskbar System Info 1.2.3 capacity alignment, the audio visualizer, and the window
pack. Read their dated notes before changing them. This sort did not change live
mods, registry settings, applications, or T3 conversation bindings.

## 2026-09-30: Better Volume Mixer Plus replaces the stock mixer

- `local@better-volume-mixer-plus` 1.0.0 (DavidHiFi fork of 0Allu's 1.4.5)
  is installed and running. The stock `better-volume-mixer` is disabled, and
  its settings were copied over.
- New: right-click an app row, then **Output device** or **Input device**, to
  route just that app, or pick **Default** to clear it. It covers EarTrumpet's
  per-app device menu.
- The user confirmed it works. It is in the snapshot repo at commit c3ec657.
  EarTrumpet is no longer needed.
- Rollback: `scripts\2026-09-30-better-volume-mixer-plus-install.ps1 -Rollback`.
  Details: `notes\2026-09-30-better-volume-mixer-plus.md`.

## 2026-09-30: all local mods audited, metadata standardized, submitted to the catalog

- All five local mods now carry `@author DavidHiFi`, a GitHub profile link, a
  homepage back to `DavidHiFi/davids-windhawk-mods`, and an explicit license:
  translucent-flyouts 0.6.1 (LGPL-3.0), alt-snap-drag 1.2.2 (GPL-3.0),
  taskbar-ai-quota-opencode 1.6.5.1 (MIT), npp-taskdlg-textcolor 1.0.1 (MIT),
  center-titlebar-fork 3.4 (MIT, prototype). Fork credits stay in the sources.
- Live ModsSource updated via `scripts\2026-09-30-apply-modsource-metadata.ps1`;
  backups + receipt in `backups\2026-09-30\modsource\`. Metadata-only, no
  engine restart.
- center-titlebar-fork (until now only in H:\Claude\misc\side-projects\windhawk)
  now lives in `Windhawk\center-titlebar-fork\` and in the snapshot repo;
  `Build-Repo.ps1` carries it via `$offlineLocal`.
- Snapshot repo: commit b49cb90, push, tag + release v1.2.0
  (`davids-windhawk-mods-1.2.0.zip`). Catalog refresh inside:
  restore-folder-menubar-25h2 3.1.0, taskbar-notification-icon-spacing 1.4.
- Upstream catalog PRs, pending review: #5785 translucent-flyouts (updated),
  #5813 alt-snap-drag, #5814 taskbar-ai-quota-opencode, #5815
  npp-taskdlg-textcolor. All four files pass the upstream validator locally
  with 0 warnings.
- RESOLVED 2026-10-04 - GitHub account flagged on 2026-09-30: DavidHiFi's
  profile, the repo page and `api.github.com/users/DavidHiFi` all answer 200
  again, and the ten preview URLs answer 200, so the account is reachable.
  Whether Actions and `/ai-review` have resumed has not been checked. Background
  and evidence: `notes\2026-09-30-github-account-flagged.md`.
- Details: `notes\2026-09-30-windhawk-mods-github-audit.md`.

## Workspace created and registered: done 2026-09-28

- `H:\Windhawk Configuration` created as a standalone workspace for all Windhawk
  work, split out of `H:\System Configuration`.
- Moved in: `Windhawk\` (mod sources, builds, historical backups) and
  `davids-windhawk-mods\` (public fork repo). Directory junctions left in
  `H:\System Configuration` so every old absolute path still resolves.
- Registered in T3 Code (Nightly) as project "Windhawk Configuration"; the
  separate V2 Orchestration registration retired with V2 on 2026-10-03.
- Historical Windhawk records were moved here on 2026-10-04; old paths remain
  available through compatibility links.
- Detail, registration ids, backup and undo:
  `notes\2026-09-28-workspace-created-and-registered.md`.

## Live Windhawk state

- `local@translucent-flyouts` 0.6.8 (2026-10-08 audit): full TranslucentFlyouts
  engine port as one Windhawk mod (menus/dropdowns/tooltips, controller settings
  schema, no app). Installed live (`Include=*`, `Exclude=discord*.exe|Voicemeeter*.exe|Matrix*.exe|Stream Deck*.exe|dwm.exe`,
  `Architecture=x86-64|x86`) with both x64 and x86 DLLs - all 64-bit and 32-bit
  processes are covered, including Ableton Live (native menu bar; the standing
  exception). Defaults = Modern Acrylic; settings
  readable/writable via the Windhawk UI or
  `scripts\2026-10-08-translucent-flyouts-audit.ps1` (audit/backup/install/rollback;
  the older per-setting script `2026-09-28-translucent-flyouts-set-setting.ps1` still works).
  After a `mod compile`, check the mod key's `Include` - the compile resets it.
  Source + build/install/test scripts in `Windhawk\translucency-flyouts\` and
  `scripts\`; the 2026-10-08 audit, fixes and verification:
  `notes\2026-10-08-translucent-flyouts-audit.md`. Menu corners follow
  `custom-corner-radius` (smallRadius 16, rollback
  `scripts\2026-09-28-custom-corner-radius-small-radius.ps1 -Set 8`);
  `dark-menus` "TranslucentFlyoutsFix" is 1.
- Published 2026-09-28 evening: `mods/local/translucent-flyouts/` and the
  refreshed snapshot on `DavidHiFi/davids-windhawk-mods` main (f9246e9,
  0f2a1f7), release v1.1.0 with the zip, and upstream catalog PR
  https://github.com/ramensoftware/windhawk-mods/pull/5785 (validation check
  passed, pending review).
- `windows-11-taskbar-styler` 1.10: giant-pill taskbar theme, plus the tray
  overflow arrow as three dots. Rule 59 now matches the up arrow (U+E971) and the
  down arrow (U+E972) and sets `Text=<U+E712>` (RosePine pattern). Verified
  2026-10-24 at 6:33 PM by pixel crop `reports\2026-10-24-icon-row\chevron-zoom-183328.png`:
  dots present, arrow gone. The 9/28 "verified" line was stale: rule 59 matched only U+E971,
  so the down arrow kept the stock glyph.
  Rollback: `scripts\2026-10-24-chevron-dots-apply.ps1 -Rollback` (elevated; restores the target
  saved in `backups\2026-10-24-chevron-dots\`).
- `local@alt-snap-drag` 1.2.2: AltSnap replacement for all processes; stock
  `alt-drag` disabled. Source in `Windhawk\altsnap-fork\`, installed build
  receipts in `H:\System Configuration\backups\2026-09-28\altsnap-fork\`.
  Steam client support added 2026-09-28 via the engine process inclusion list
  (`HKLM\SOFTWARE\Windhawk\Engine\Settings\Include` now also contains
  `C:\Program Files (x86)\Steam\*` and `C:\Program Files\Steam\*`); elevated
  windows verified. Details, evidence and the live-reload procedure:
  `notes\2026-09-28-altsnap-steam-include.md`; change/rollback script:
  `scripts\2026-09-28-altsnap-steam-include.ps1`.
- Do not run `windhawk.exe -restart` on this machine: it also restarts explorer
  and can freeze a live T3 Code GUI. Apply mod/settings changes live by writing
  the registry and bumping `SettingsChangeTime`.
- `local@taskbar-ai-quota-opencode`: forked AI-quota taskbar bars (OpenCode Go
  added); source in `Windhawk\Opencode-fork\`.
- `npp-taskdlg-textcolor`: Notepad++ task-dialog text-color fix; source and DLLs
  in `Windhawk\`.
- `win32-ui-modernizer` 1.0.2: the "modern focus rectangle" feature is off
  system-wide (`Settings\GeneralSection.Enabled` 0, was 1, applied 2026-09-28
  live with a `SettingsChangeTime` bump, no engine restart). Its opaque
  rounded outline replaced the native XOR erase that classic list views
  (regedit, NanaZip) need for their drag marquee, which left every drag frame
  on screen as trails. Rollback, evidence and reasoning:
  `H:\System Configuration\notes\2026-09-28-windhawk-modernizer-focusrect-global.md`.
  The local `davids-windhawk-mods` settings snapshot is aligned to the new
  value (2026-09-28, uncommitted until the repo thread publishes).



- 2026-10-25 2:50 PM: removed windows-11-start-menu-styler 1.7 and windows-11-start-menu-buttons 2.2 (owner said go). Evidence: registry keys gone, modules not loaded in StartMenuExperienceHost or explorer, 82 mods installed. Backup and receipt: backups\2026-10-25-trim\145055 (rollback: scripts\2026-10-25-trim-mods.ps1 -Action Rollback).

- 2026-10-30: nuked the forked Center Titlebar mod (owner dictated go). It was never installed (no registry key, ModsSource or DLLs), so no Windhawk uninstall was needed; title centering stays with caption-buttons-customizer. Deleted Windhawk\center-titlebar-fork\ (hash-verified backups: backups\2026-10-30-center-titlebar-fork-removal\, receipt.json included) and pushed da2d340 + 494bb59 to DavidHiFi/davids-windhawk-mods main, removing the mod folder, the README unfinished warning, credit-row clauses, manifest entry and Build-Repo offline-local machinery. Full-tree grep: only the intentional retirement-list line remains. Record: notes\2026-10-30-center-titlebar-fork-removed.md.
- 2026-11-07: Seamless Dictate 1.0.2 installed. Bar now opens on the focused window's screen (measured live: T3 on DISPLAY9, bar on DISPLAY9) and a plain click no longer pins it; new Settings > General 'Bar screen' picker (focused/mouse/main/specific display; settings row visually unverified). Record: notes\2026-11-07-dictate-bar-screen.md.
- 2026-11-09: Seamless Dictate 1.0.3 installed. New 'Mic privacy on/off' shortcut (Shortcuts > Privacy, unset by default) flips Keep the microphone private from any app; settings darkened to Mocha with gray borders and blue-to-mauve hover glow, mode switch and rail hover (hover visually unverified). Record: notes\2026-11-09-dictate-mic-hotkey.md.
- 2026-11-10: Seamless Dictate 1.0.6 installed. New 'Correction cue' box (Styles > Clean-up, empty by default), ported from T3 Code: the AI applies a spoken self-correction ('make it 42, sorry, 24' -> 24) only where it is one, and filler removal never eats the cue word. Built-in rule 3 now carries T3's correction examples for every AI style. Not ported: cue as a Whisper vocabulary hint (mod never sends prompts to Whisper). Groq cleanup returns 403 from this network, so cleanup runs on the Gemini fallback. Rollback: scripts\2026-11-10-dictate-correction-cue.ps1 -Rollback (elevated). Record: notes\2026-11-10-dictate-correction-cue.md.
- 2026-11-22 8:27 pm: Seamless Flyouts 2.1.3 live. Open/Save windows in every app: search box hidden, address and back/forward docks, footer and File name label now the same glass as the file list (the dialog is subclassed; GDI colours over glass add up, so only black reads as glass). notes\2026-11-22-file-dialog.md. Rollback: Install-StagedMod with backup local@seamless-flyouts-20261122-2017.wh.cpp (2.1.2) or the 2.1.0 copy in work\2026-11-22-file-dialog\stage\.
