# 2026-11-09 taskbar polish (thread 970909cf)

Every change below has a backup and a one-line rollback. No Explorer restart; the shell stayed at PID 24016 the whole time.

| Change | Old | New | Rollback |
|---|---|---|---|
| Taskbar icon sharpness (styler IconSize) | 20 | 32 | `work\2026-11-09-native-power\icon-sharp.ps1 -Rollback` |
| System info widget | 1.4.19 (RAM/VRAM bar gap, VRAM watts `--`) | 1.4.20 (tight gap, VRAM watts from an NVML estimate, about 10 W) | `work\2026-11-09-sysinfo-1420\install.ps1 -Action Rollback` |
| Hover preview look (styler rules 46/47 + stats colours) | stock border | Mocha blue to mauve gradient border | `work\2026-11-09-native-power\thumb-style.ps1 -Rollback` |
| App hover on the middle dock (styler rules 7 and 9) | grey blob #8845475A, 24 px, corner 6 | tray look: #BF45475A fill, 1 px blue #89B4FA edge, mauve #CBA6F7 edge while pressed, 26 px, corner 7, all six hover/pressed states | `work\2026-11-09-native-power\app-hover.ps1 -Rollback` (receipt `backups\2026-11-09-native-power\app-hover.json`, export `taskbar-styler-before-app-hover.reg`) |
| Seamless Dock Animation | 2.1.1 (middle dock only) | 2.2.0 (also tray, AI usage and media docks; settings `OtherDocks.Tray/AiUsage/Media`, all on) | `work\2026-11-09-dock-220\install.ps1 -Action Rollback` (originals in `backups\2026-11-09-dock-220`) |

| Seamless Dock Animation (tray, AI usage, media docks) | 2.2.0: the whole tray icon with its hover box grew and spread, so boxes got cut off; compositor stretch looked blurry; the network button was skipped | 2.2.2: only the icon grows, from its centre, no spread; XAML redraws it at the new size (sharp); network/volume button icons grow too | `work\2026-11-09-hover-borders\v222\install.ps1 -Action Rollback` (back to 2.2.1), then `work\2026-11-09-hover-borders\install.ps1 -Action Rollback` (back to 2.2.0) |
| Widget hover (system info 1.4.21, media player 1.9.10, clock 1.2.1) | inner dark box with a 1 px blue edge | the widget's own 2 px grey border turns into the blue-to-mauve gradient on hover; no inner box | `work\2026-11-09-hover-borders\install.ps1 -Action Rollback` (originals in `backups\2026-11-09-hover-borders`) |
| Styler rules 7, 9, 23 | rule 7 forced a plain fill/border on app hover squares (beat the hover look on pinned apps); rule 23 forced the grey island border | rule 7 styles[6]/[7] now `Margin=0` / `VerticalAlignment=Center`; rule 9 gets the resting look as base values plus InactivePointerOver, InactivePressed, MultiWindowPressed; rule 23 styles[1] `BorderThickness=2` | `work\2026-11-09-hover-borders\styler.ps1 -Rollback` (receipt `backups\2026-11-09-hover-borders\styler.json`, export `taskbar-styler-before-hover-borders.reg`) |

| Seamless Dock Animation (tray, AI usage, media docks) | 2.2.2: icon-only zoom, no spread, boxes clipped by the island outline, not eased like the apps dock | 2.2.3: the whole button grows with its hover box, capped so it stays inside the island outline (the glyph does the rest), neighbours make room, eased each frame like the apps dock (same curve, 250 ms fade, lerp 60); exit events from children no longer cut it short; fast flicks off the taskbar caught | `work\2026-11-09-hover-borders\v223\install.ps1 -Action Rollback` (back to 2.2.2, clock 1.2.1, drawer 1.0.1; originals in `backups\2026-11-09-hover-borders\v223`) |
| Seamless Dock Animation 2.2.4 (installed 1:17 pm) | 2.2.3: hover box stopped growing at the island outline (about 1.2x) while the icon kept going, so it looked pressed against the edge; neighbours only made room inside their own segment and the end icons were held at the outline; the network button only grew its icon | 2.2.4: whole button (box and icon) grows to the full 130% like an app icon, the whole tray row and the AI usage row make room as one, no outline limit (a 1.6x test box at 1:12 pm went past the outline untrimmed); the network button grows with its own hover box when it is the only icon showing. Same easing as the apps dock | `work\2026-11-09-hover-borders\v224\install.ps1 -Action Rollback` (back to 2.2.3; original and export in `backups\2026-11-09-hover-borders\v224`) |
| Taskbar clock | 1.2.1: hover gradient edge switched off when the pointer crossed the text inside | 1.2.2: edge only turns off on a real exit | same as above |
| Seamless Tray Drawer | 1.0.1: no hover zoom in the hidden-icons panel; footer arrow button hover a flat #313244 fill | 1.0.2: icons in both drawers grow on hover (whole button, same easing as the dock); footer arrow button gets the Mocha box | same as above |
| Drawer settings (registry `...\local@seamless-tray-drawer\Settings`) | `chevron.hoverColor` #313244, `chevron.pressedColor` #45475A, no edge or zoom values | hoverColor #BF45475A, pressedColor #E6585B70, new `chevron.hoverEdge` #89B4FA, `chevron.pressedEdge` #CBA6F7, `hoverZoom.enabled` 1, `hoverZoom.size` 130, `hoverZoom.reach` 64 | the rollback above puts the old two back and deletes the new ones; full export `backups\2026-11-09-hover-borders\v223\local@seamless-tray-drawer.reg` |

| Hover preview look (styler rules 48, 49, 50, and rule 46 styles[8] to [10]) | stock grey blurred background, Segoe UI title and stats text, light blue-grey card fill on hover | background: blur 20 tinted Mocha base `#C01E1E2E`; title: FiraCode Nerd Font, `#CDD6F4`; stats line: FiraCode Nerd Font; card fill clear at rest, `#4D313244` on hover, `#6645475A` pressed. All editable in Windhawk > Taskbar Styler > Control styles (rules 46 to 50); stats colours and size stay in Taskbar Thumbnail Stats settings | `work\2026-11-09-hover-borders\thumb-rice.ps1 -Rollback` (receipt `backups\2026-11-09-hover-borders\thumb-rice.json`, export `taskbar-styler-before-thumb-rice.reg`) |
| Thumbnail Stats `singleLine` | 1 (one line; FiraCode is wider, so it cut off at "8...") | 0 (wraps to a second line, same size 10) | `work\2026-11-09-hover-borders\thumb-rice-wrap.ps1 -Rollback` (export `taskbar-thumbnail-stats-before-wrap.reg`) |

Seen on screen 12:37 pm (owner away, asked for the hover): `reports\2026-11-09-hover-borders\thumb-rice-final-3x.png`, `thumb-rice-hover-3x.png`. Hover driven by `thumb-rice-shot.ps1` (absolute mouse moves under `coop lock desktop`, cursor put back). Note: in pwsh `Mv` is an alias of Move-Item, so a helper named Mv silently never ran.

Source patches: `work\2026-11-09-hover-borders\patch.py` (four mods), `patch2.py` (dock 2.2.2), `patch3.py` (dock 2.2.3), `patch4.py` (drawer 1.0.2), `patch5.py` (clock 1.2.2). The first 2.2.3 run stopped at a clock compile error (missing include) after dock 2.2.3 was in; the family came back on, the second run finished. Receipt `backups\2026-11-09-hover-borders\v223\installed.json`. Shell stayed at PID 24016.

2.2.4: `patch6.py` makes `src\dock.v224.wh.cpp` from 2.2.3; receipt `backups\2026-11-09-hover-borders\v224\installed.json`, shell still PID 24016, styler on. Clip test (`v224\clip-test.ps1`, styler rules 52/53 for about 2 minutes, export `v224\taskbar-styler-before-clip-test.reg`): its first cleanup missed because PowerShell `-like "controlStyles[52].*"` reads `[52]` as a wildcard set, so nothing matched; fixed with `.StartsWith(...)` and rules confirmed gone at 1:14 pm. Same fix applied to `toast-title.ps1 -Rollback`.
Seen on screen 1:33 pm during the owner's own hovers (passive watcher, `reports\2026-11-09-hover-borders\v224\hover-01..04`): the "..." box grows to about 1.3x over the island's left edge, untrimmed, like an app icon; the network icon grows and the volume and fan icons next to it grow less. Open item: the network button shows no hover box at all (the styler's PointerOver rule on `OmniButton#ControlCenterButton > Grid@CommonStates > Border#BackgroundBorder` does not light up on this build), so only its icon grows.

Icon fit (2:41 pm): app icons on the middle dock poked past their rounded hover box. Styler rules 6 (icon), 7 (hover box) and 8 (running box, every state): old icon 22 / box 26, new icon 20 / box 28, so 4 px clear on every side. Icons still load at 32 px, so they stay sharp. Script `work\2026-11-09-hover-borders\v225\icon-fit.ps1`; old values in `backups\2026-11-09-hover-borders\v225\icon-fit.json` plus export `taskbar-styler-before-icon-fit.reg`. Rollback: `v225\icon-fit.ps1 -Rollback` (elevated). Seen: `reports\2026-11-09-hover-borders\v225\apps-before-fit.png` vs `apps-after-fit.png`.

2.2.5 (2:50 pm): `patch7.py` makes `src\dock.v225.wh.cpp` from 2.2.4. Old: the network button had no hover box, and a growing tray icon was drawn under the next tray segment (cut off, blur seams). New: the network button lights its own inner box with the tray hover colours (new settings Network hover fill #BF45475A, edge #FF89B4FA; the original look is saved and put back when the hover ends); every growing icon's parent chain is raised above its neighbours (Canvas.ZIndex, restored afterwards). Receipt `backups\2026-11-09-hover-borders\v225\installed.json`, shell PID 14140 unchanged, styler on. Rollback: `work\2026-11-09-hover-borders\v225\install.ps1 -Action Rollback` (elevated, under the windhawk-engine lock) puts 2.2.4 back. Resting capture: `reports\2026-11-09-hover-borders\v225\tray-rest.png`.
2.2.6 (3:38 pm): `patch8.py`. Capped each tray hover box at its tray part, so nothing was trimmed. The owner reported two problems: the "..." box still looked cut off on the left and right, and the network button stopped growing (its part was found as its own tight inner corner, cap 1). Rollback was `v226\install.ps1 -Action Rollback`.
2.2.7 (3:55 pm): `patch9.py`. Only a part with a drawn edge, or a rounded one with room, counts as a tray part. Writes a size readout to `%TEMP%\seamless-dock-sides.txt` (only while the pointer is over a side dock). The readout showed the real limit: every part is 30 px tall inside, the tray boxes were 22x24, so they could only reach 1.17x; the "..." part was 28 px wide, so it could reach only 1.09x; the network button has no box inside its icon (the tray now holds only the network icon in that button).
2.2.8 and tray room (4:04 pm): `patch10.py`. The network button uses the button's own hover box (grows with the icon, lit with the tray colours; the box was hidden by rule 43, the light puts opacity 1 back and restores it after). Styler, script `work\2026-11-09-hover-borders\v228\tray-room.ps1`:

| Setting | Old | New |
|---|---|---|
| Rule 28 target | tray icons, plain IconViews and the "..." | plain IconViews only (Height 28 unchanged for them) |
| Rule 52 (new) | none | tray icons and "..." ContainerGrid Height 24, so boxes are 22x20 at rest and 28.6x26 at 1.3x |
| Rule 53 (new) | none | network button hover box Width 24, Height 20, centred |
| Rule 16 styles[1] | `Padding=0` | `Padding=4,0,4,0` (room for the "..." box to grow) |

Old values: `backups\2026-11-09-hover-borders\v228\tray-room.json`, export `taskbar-styler-before-tray-room.reg`. Rollback (elevated, under the windhawk-engine lock): `v228\tray-room.ps1 -Rollback`, then `v228\install.ps1 -Action Rollback` (back to 2.2.7). Receipt `backups\2026-11-09-hover-borders\v228\installed.json`, shell PID 32732 unchanged, styler on. Resting capture `reports\2026-11-09-hover-borders\v228\tray-rest.png`.
## Checked on screen
- Icon sharpness, RAM/VRAM gap, VRAM watts: `reports\2026-11-09-steam-line\icons-after-zoom.png`, `stats-after-gap.png`, `taskbar-after-1420.png`.
- Taskbar renders normally after the hover style and after 2.2.0: `apps-after-hover-style.png`, `taskbar-after-dock220.png`.

## Not yet seen during a hover
- The new app hover, the magnify on the other docks and the preview gradient need a real hover. The owner was at the PC the whole time, so nothing was injected.
- `work\2026-11-09-dock-220\pen-hover.ps1` (synthetic pen hover, no clicks, puts the cursor back) is ready for a later idle check. It has never been run.
- A passive watcher (`thumb-watch.ps1`) photographs the hover preview the next time the owner opens one.

## 2026-11-09 8:15 pm — tray hovers verified (thread 970909cf)
- Side zoom stays off (owner change of mind). patch17 and styler3 abandoned, never installed.
- Live styler rules from Codex scripts: network-overflow-hover (rules 27, 53, 55) and
  tray-hover-cleanup (rules 16, 43, 54). Rollback: each script with `-Rollback`, elevated.
- Real-pointer check (injected mouse input; SetCursorPos does not fire XAML hover):
  network shows one Mocha blob with blue edge, same as lock icon; "..." blob not clipped;
  overflow icons (clipboard, LuaTools, Stream Deck) show the same themed blob; no stale blob.
- Proof: reports/2026-11-09-hover-borders/v229/take11/sheet-bar.png, sheet-panel.png.
- Desktop "libunwind.dll was not found" box came from the launchpad-settings harness test; closed.
