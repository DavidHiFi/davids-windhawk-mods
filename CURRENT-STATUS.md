# Current status

Last updated: 2026-11-09

## 2026-11-09: Seamless Title Bars

- 2026-11-09 9:28 pm: all title bar work is ONE mod, `local@seamless-title-bars` 1.0.0 (Seamless Title Bars). It replaces caption-buttons-customizer, win11-custom-title-bar-colours, local@remove-uwp-title-bars-plus, local@terminal-titlebar-blur, titlebar-for-everyone, cef-titlebar-enabler-universal and fix-basic-caption-text, which were REMOVED at 9:31 pm on the owner's request (backups of keys, sources and DLLs in `backups\2026-11-09\seamless-title-bars\`; restore steps in the note). Where lines below name those mods, read the matching section of the new mod: buttons, colours (`colours.excludedApps` holds the old ExcludeCustom, incl. chrome.exe and FreeDictate.exe), uwp, terminalBar, nativeFrames, spotify, basicFrames. Basic frames is off: its uxtheme symbols are missing on this Windows build, so the old mod never did anything. Source and builder: `work\2026-11-09-seamless-title-bars\` (build output `out\seamless-title-bars.wh.cpp`). Note: `notes\2026-11-09-seamless-title-bars.md`.

## 2026-10-24: Dark mode context menus merged into Translucent Flyouts 0.6.66 (installed)

- `dark-menus` 1.4.2 is removed; its menu darkening and a `darkMenus.appMode` setting (default force_dark) are inside
  `local@translucent-flyouts` 0.6.66. Checked 11:40 AM: registry shows 0.6.66 and `force_dark`, the dark-menus key and
  source are gone, 231 processes (all Explorer) load `local@translucent-flyouts_0.6.66_1.dll`, screenshot
  `reports\2026-10-24\translucent-flyouts-menu-20261024-113604.png`.
- Not yet clean: 13 long-running apps still hold the old DLLs until they restart. Discord, Voicemeeter, Matrix, Stream Deck
  and dwm are on the flyouts skip list, so they get no dark menus from this mod.
- Rollback: `scripts\2026-10-24-dark-menus-merge.ps1 -Rollback`. Details: `notes\2026-10-24-dark-menus-merge.md`.
- Public README or publish copy still says "pair with Dark Menus"; not pushed.

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
  the dots. Page flip on screen: unverified, check queued for an idle desktop.
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
  overflow chevron rendered as three dots (RosePine rule
  `TextBlock#InnerTextBlock[Text=<U+E971>] -> Text=<U+E712>`, rule index 59).
  Rollback for the dots:
  `H:\System Configuration\scripts\2026-09-28-windhawk-taskbar-styler-tray-dots.ps1 -Rollback`.
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


