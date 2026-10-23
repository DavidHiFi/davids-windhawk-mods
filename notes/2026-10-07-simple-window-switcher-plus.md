# Simple Window Switcher Plus

User requested Vista Flip 3D animations and blur with Simple Window Switcher customization, under the name Simple Window Switcher Plus, including elevated foreground apps.

Worktree and branch: `work/simple-window-switcher-plus/repo`, `simple-window-switcher-plus`. Sources were pulled from ramensoftware/windhawk-mods main, Vista 1.5.3 and Simple 2.1. GPL-2.0 from valinet/sws applies to the combined mod. Vista retains its MIT notice and author credit.

Measured: both originals were enabled. Both are now disabled. Registry exports and original sources are in `backups/2026-10-07/simple-window-switcher-plus`. The new mod is `local@simple-window-switcher-plus`, included only in explorer.exe and windhawk.exe. No engine or Explorer restart occurred.

Measured on revision 3: Vista shows and dismisses from a normal test window and an elevated test window. Its host token is elevated. Ctrl+Alt+Tab stays open after modifiers release and Enter dismisses it. Simple mode passed the same tests on revision 2. Settings can switch renderers live and return to Vista. Evidence JSON and screenshots currently in `work/simple-window-switcher-plus`.

The Vista renderer shares SWS title font and weight, icon/title visibility, theme border and tint colors, title/exe wildcard exclusions, per-monitor filtering, and minimized ordering. Simple mode retains all original customization. Grouping, badge layout, tile dimensions and thumbnail corners currently apply to Simple mode only. Vista keeps all original animation styles and animation controls.

Elevated support runs the isolated tool host at administrator integrity, so its keyboard hook receives input while administrator windows have focus. Explorer forwarding now hooks GetMessageW and PeekMessageW rather than depending on the thread name Immersive Shell. The normal native fallback is preserved if no ready renderer exists. Secure UAC desktop is outside scope.

The first sticky attempt failed because Ctrl+Alt Tab did not have LLKHF_ALTDOWN set. The working hook also checks the Alt key state. The start message carries sticky state across completion of a previous closing animation.

Rollback: run `work/simple-window-switcher-plus/install.ps1 -Rollback` elevated. This disables Plus and restores the exact original registry exports, including their original enabled state. The installer and tests are reversible and restore temporary exclusions and renderer selection.

Measured final check: Vista also opens and cancels with the actual Windhawk UI in front. Windhawk PID 35624 and the Plus host PID 25156 both have elevated tokens. The final test restored all temporary exclusions and left Vista selected. The fixture windows were closed afterward. The engine lock was released and the styler thread was notified.

The 840 by 560 preview GIF contains neutral fixture windows, 16 optimized frames at nominal 12 fps and is 2.3 MB. It is in the fork's `media/previews` folder. The supplied portable Build.ps1 successfully built x64 and x86. Installed source bytes and both installed DLLs match the build artifacts. Evidence is archived in `reports/2026-10-07-simple-window-switcher-plus`.

Fork committed as `3158227` on `simple-window-switcher-plus`. The user approved publication and confirmed that it works great. Published to `DavidHiFi/davids-windhawk-mods` main with a normal fast-forward push from `28ef40a` to `3158227`. The remote main ref and published source and preview hashes were independently verified. The worktree is clean.

Final source cleanup removed only inherited trailing spaces without changing statements or line numbers. The installed source was backed up and updated to match the committed source. No DLL or settings reload was needed. The final independent verifier checked installed source equality, both installed DLL hashes, production API imports, callback exports, architecture and enabled states.
