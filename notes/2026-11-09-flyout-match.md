# 2026-11-09 Menu match: classic menus take the taskbar menu look

## Part 1: taskbar menu experiment, reverted (2:39 pm)

I first read the request backwards and restyled the taskbar menus to copy the desktop
menus (taskbar styler rules 51-56 plus a `MenuMaterial` constant). The owner said the
taskbar menus were already right and lost their material and clipped icons.

| What | Old | New (reverted) | Now |
|---|---|---|---|
| styler `controlStyles[51]` | `Background:=$TaskbarMaterial` | blur 40%, gradient border, radius 16 | `Background:=$TaskbarMaterial` |
| styler rules 52-56 | none | item, separator, presenter rules | none |
| `styleConstants[1]` | none | `MenuMaterial=` acrylic 40% | none |

- Script: `scripts\2026-11-09-flyout-match.ps1` (obsolete, kept for the record).
- Backup: `backups\2026-11-09\flyout-match\taskbar-styler-before.reg`, receipt `receipt.json`.
- Checked: registry back to 51 rules with rule 51 = taskbar material; empty-area and HaloCord
  app menus captured in their original look.
- Open point: the AI usage tile menus (Codex, Claude Pro) showed no border afterwards.
  They are built once per Explorer session, so a guarded Explorer restart rebuilds them.

## Part 2: classic Win32 menus match the taskbar menus (staged)

Target look, measured from the taskbar menus: dark blurred #181825 material, 2 px
blue-to-mauve border left to right, radius about 8, FiraCode Nerd Font Medium 14 px
#CDD6F4, about 30 px rows, mantle hover with a blue ring, surface1 separators.

| Mod | Setting or code | Old | New |
|---|---|---|---|
| Translucent Windows Plus 1.9.0 -> 1.9.1 | `MenuBlur` (new) | menus used `661E1E2E` (global) | `B4181825` for menus only |
| | menu item text | RGB 255,255,255 | RGB 205,214,244 |
| | menu font (when Segoe UI) | Segoe UI Variable Small, 13, 400 | FiraCode Nerd Font Med, 14, 500 |
| | POPUPITEM margins top/bottom | 4 / 4 | 6 / 6 |
| | hover | accent fill, radius 4 | mantle fill, blue 1 px ring, radius 6 |
| | separator | white at 96 alpha | #45475A solid |
| Seamless Borders 1.0.3 -> 1.0.4 | `menuGradientAngle` (new) | shared 45 | 0 (left to right) |
| | `menuRadius` | 16 | 8 |

- Staged sources and the patcher: `work\2026-11-09-flyout-match\` (`patch-menus.py`).
  Both pass a clang syntax check.
- Install, audit, rollback: `scripts\2026-11-09-system-menus-match.ps1` (run elevated).
  It backs up both live sources (`*.wh.cpp.bak-<stamp>`) and both settings keys
  (`*-settings-before.reg`) into `backups\2026-11-09\flyout-match\`, then recompiles.
- Rollback: `-Rollback` restores both sources and settings and recompiles.
- Applied 2:57 pm on the owner's go-ahead ("get it done fully autonomously").

## Part 3: what it took on the real thing (3:05 pm)

- The compile of the Seamless Borders tool mod stopped its process and did not start it
  again (no menu or window borders). Fixed with `windhawk-cli mod disable` then `enable`
  (elevated) at 2:59 pm: `work\2026-11-09-flyout-match\restart-borders.ps1`.
- The font hook in Translucent Windows Plus never runs for classic menus: they take the
  system menu font. Set it with `scripts\2026-11-09-system-menus-font.ps1` (per user):

| Setting | Old | New |
|---|---|---|
| system menu font (WindowMetrics MenuFont) | Segoe UI, -12, 400 | FiraCode Nerd Font Med, -14, 500 |

  Backup `backups\2026-11-09\flyout-match\windowmetrics-before.reg` and `menufont-before.json`;
  undo with `-Rollback`.
- Guarded Explorer restart at 3:02 pm (OK). It also rebuilt the taskbar AI usage menus,
  which have their blue-to-mauve border again.
- Measured: test menu in a new process, rows about 29 px; desktop menu rows 25 px
  (Explorer's own menu spacing ignores the theme margins). Text #CDD6F4, border left to
  right blue to mauve, radius 8, background dark #1E1E2E-ish.
- Proof: `reports\2026-11-09-menus-match-proof.png` (taskbar, desktop, app menu).
- Full undo: `scripts\2026-11-09-system-menus-match.ps1 -Rollback` (elevated) and
  `scripts\2026-11-09-system-menus-font.ps1 -Rollback`; then disable and enable Seamless
  Borders if its process is missing.

## Part 4: same material as the taskbar menus (3:24 pm)

The owner saw the desktop menu as lighter and see-through next to the taskbar menu.
Measured: taskbar menu background a flat (41,43,65); desktop menu (26-42,27-43,40-58),
changing with the wallpaper behind it.

| Setting | Old | New |
|---|---|---|
| Translucent Windows Plus `MenuBlur` | `B4181825` | `CC24263D` |

- Script: `scripts\2026-11-09-menu-tint.ps1 -Value CC24263D` (elevated); `-Rollback` puts back B4181825.
  Log: `backups\2026-11-09\flyout-match\menu-tint-log.txt`.
- Measured after: desktop menu (38-42,40-44,61-65), separators (69,71,90) on both.
- Proof: `reports\2026-11-09-menu-material-proof.png`.

## Part 5: rows, darker Mocha, clean corners, edge-to-edge separators (4:03 pm)

The owner wanted taskbar-height rows, a darker Mocha background, no dark specks inside the
rounded corners, and separators that touch the border on both sides.

| What | Old | New |
|---|---|---|
| Translucent Windows Plus | 1.9.1 | 1.9.2 rows, 1.9.3 separators, 1.9.4 separator edges |
| desktop menu rows (owner-drawn, WM_MEASUREITEM) | 25 px | 33 px, same as the taskbar menus |
| separators | stopped 2 px short of the frame | painted through the 3 px frame up to the border |
| Translucent Windows Plus `MenuBlur` | `CC24263D` | `F5181825` (Mocha mantle, body reads 26,26,39) |
| Seamless Borders `menuRadius` | 8 | 16 (ring now covers the window's own corner edge) |

- 1.9.4 removes the unused part-size hook from 1.9.3 and adds a menu subclass that paints the
  separator line into the window frame after each paint (`work\...\patch-edges.py`).
- Source install and undo: `scripts\2026-11-09-menu-rows.ps1 -Install | -Rollback` (elevated).
  Backups in `backups\2026-11-09\flyout-match\`: `...bak-20261109-1531-rows` (1.9.1),
  `-1547-rows` (1.9.2), `-1554-rows` (1.9.3). Rollback restores the newest one; repeat to go further.
- Tint and radius: `scripts\2026-11-09-menu-look2.ps1 -MenuBlur <ARGB> | -MenuRadius <n> | -Rollback`
  (elevated). `-Rollback` puts back `CC24263D` and 8. Log: `menu-look2-log.txt`.
- Measured on the real desktop menu (three opens): separators (69,71,90) from the blue border
  pixel to the mauve one, zero dark pixels inside the ring at all four corners
  (`work\...\corner-fringe.py`), body (25-27,25-27,38-40).
- The first menu opened right after a settings change missed the frame part of the separators
  once; every later open had it.
- Proof: `reports\2026-11-09-menu-edges-proof.png`.

## Part 6: clearer blur, see-through hover, submenu gap (4:10 pm)

The owner found the menu too much like a flat colour, the hover too dark, and the
submenus overlapping the main menu.

| What | Old | New |
|---|---|---|
| Translucent Windows Plus `MenuBlur` | `F5181825` (96%) | `A011111B` (crust at 63%, the wallpaper shows through) |
| Translucent Windows Plus | 1.9.4 | 1.9.5 |
| hover fill | mantle, solid | overlay0 at about 31%, blur shows through; blue ring kept |
| submenu position | overlaps the parent edge by about 6 px | opens 8 px past the parent's edge, flips side at the monitor edge |
| separator line ends | missed on some opens | menu subclass attached at window creation (thread CBT hook while a popup menu runs), plus one repaint 150 ms after show |

- Staged by `work\...\patch-gap.py`; installed with `scripts\2026-11-09-menu-rows.ps1 -Install`.
  Backup of 1.9.4: `backups\2026-11-09\flyout-match\...bak-20261109-1608-rows`.
  `-Rollback` restores it (run again for older ones).
- Tint undo: `scripts\2026-11-09-menu-look2.ps1 -MenuBlur F5181825` (or `-Rollback` for the
  original `CC24263D` and radius 8).
- Measured: View submenu at x 359 against the main menu's 351 edge (6 px clear between the
  two borders); separator ends present on every open tested; body follows the wallpaper
  (20 to 34 grey levels across the menu instead of a flat 26).
- Limit: menus that never go through TrackPopupMenu (title-bar system menu) still get the
  separator fix through the paint path, but not the submenu gap. They have no submenus.
- Proof: `reports\2026-11-09-menu-blur-submenu-proof.png`.

## Part 7: renamed Seamless Flyouts, one hover everywhere (4:46 pm)

The owner asked for the mod to be renamed Seamless Flyouts, and said the main menu's
"View" hover was too dark while the submenu's "Large icons" hover was too light.

Cause: the 31% see-through hover took on the colour behind each menu. The main menu sits
over a darker part of the wallpaper than the submenu, so the same hover came out darker
there. (Diagnosed with a logging build: both rows are drawn through the same theme part
when the mouse selects them; arrow keys draw the main row as a focus ring instead.)

| What | Old | New |
|---|---|---|
| mod id | `local@translucent-windows-plus` | `local@seamless-flyouts` |
| name / version | Translucent Windows Plus 1.9.5 | Seamless Flyouts 2.0.0 |
| hover fill | overlay0 (108,112,134) at 31% | surface1 (69,71,90) at 75%; backdrop now moves it by about 6 levels instead of 25 |
| keyboard focus row (part 26) | grey focus ring on the plain row | same hover as the mouse |
| settings, app lists | 167 values, `*.exe` custom-only list | copied unchanged |

- Staged by `work\...\patch-flyouts.py`; repo copy `Windhawk\seamless-flyouts\seamless-flyouts.wh.cpp`.
- Installed by `scripts\2026-11-09-seamless-flyouts-migrate.ps1 -Action install` (elevated):
  installs the new mod disabled, copies settings and lists, turns the old one off, the new
  one on, removes the old one. Backups: `backups\2026-11-09\seamless-flyouts\` (old key
  `.reg`, receipt). `-Action rollback` removes the new mod, re-imports the old key and
  compiles 1.9.5 under the old id.
- Traps hit: `Cli` is a PowerShell alias for Clear-Item; `reg copy` and `reg add /d ""` wait on
  a hidden prompt from an elevated shell (PowerShell 5 drops the empty argument). The script
  now writes values with New-ItemProperty.
- Measured on the real desktop menu with View open: main row (58,60,77), submenu row
  (59,61,78), the same with mouse-style and arrow-key selection. Separators still reach the
  border, 8 px submenu gap kept, corners clean.
- Scripts that set menu values (`menu-rows`, `menu-look2`, `menu-tint`) now use the new id;
  `system-menus-match` is marked dead.
- Proof: `reports\2026-11-09-seamless-flyouts-proof.png`.

## Part 8: every classic menu audited (5:20 pm)

Owner: some menus were missed (Recycle Bin tray, Ableton Options). Audit and fix all of them.

Why they were missed:
- Tool mods run in `windhawk-mod.exe`, and Windhawk never loads other mods there, so
  Seamless Flyouts cannot reach their menus. Five tool mods show their own menus.
- Ableton and Notepad++ were in Seamless Flyouts' ExcludeCustom.

What changed:
- `menu-skin\menu-skin.inc.cpp`: the Seamless Flyouts menu look as one self-contained
  block (`namespace SeamlessMenuSkin`), started first thing in `WhTool_ModInit`.
  `menu-skin\patch-tools.py` stages it into each mod.
- Own mods, version bumped in place: better-volume-mixer-plus 1.4.0 -> 1.4.1,
  seamless-dictate 1.0.3 -> 1.0.4, window-manager 1.3.0 -> 1.3.1.
- Repo mods forked per the fork recipe, settings and app lists copied, original turned off:
  `recycle-bin-tray` 1.0.0 -> `local@recycle-bin-tray-plus` 1.0.1 (Recycle Bin Tray Plus),
  `magic-pointer` 1.0.4 -> `local@magic-pointer-plus` 1.0.5 (Magic Pointer Plus).
- Seamless Flyouts ExcludeCustom:
  old `FreeDictate.exe|Ableton*.exe|notepad++.exe|WindowsTerminal.exe`,
  new `FreeDictate.exe|WindowsTerminal.exe`. Neither app has a window rule, so only their
  menus change. Ableton: the 2026-09-28 standing exception, asked again today.
  Notepad++ was only ever out to skip window blur (its old rule was "none").
  FreeDictate and Terminal stay out (they draw their own materials, CURRENT-STATUS).

Verified:
- Receipts: `backups\2026-11-09\menu-skin\receipt.txt` and `ableton-receipt.txt`. All five
  tools compiled and their processes restarted (window-manager as its elevated helper).
- Captures (cursor never moved, under the desktop lock): Recycle Bin, volume mixer and
  dictate tray menus, Notepad++ editor menu: blur, Mocha tint, ring, 33 px rows, soft hover.
  `reports\2026-11-09-menu-audit-proof.png`.
- Ableton: the DLL is loaded in the running Live (tasklist /m). Its menu bar opens only
  when Live has focus and the owner was at the PC, so it was not opened by automation.
- Coverage (elevated): every process with a window has the DLL except dwm, svchost, adb,
  EncoderServer, RemoteServerWin, RTSS, MSI Afterburner and Sound Manager (no Windhawk
  engine in them at all). Magic Pointer's menu sits inside its AI answer card; same block.

Rollback (elevated):
- `scripts\2026-11-09-menu-skin-tools.ps1 -Action rollback [-Only <id>]` (forks removed,
  originals back on; own mods get the backed-up source and a compile).
- `scripts\2026-11-09-flyouts-ableton.ps1 -Action rollback` (old ExcludeCustom back).
- Key and source backups: `backups\2026-11-09\menu-skin\`.

## Part 9 - Hover clear of the menu corners (5:36 pm)

Owner: the hover on the last row ran into the menu's rounded bottom corners (Recycle Bin
tray menu, "Properties").

Cause: the hover filled the whole row. Sides had a 4 px gap, but the first and last rows
had only 2-3 px above or below, so the rounded hover met the menu's rounded corner.

Change: popup-menu hovers are drawn 2 px (DPI scaled) shorter at the top and the bottom,
the same gap as at the sides. Row height and layout are unchanged.
- Seamless Flyouts 2.0.0 -> 2.0.1 (`PaintMenu`, popup rows only, not menu bar items).
- `SeamlessMenuSkin` block in the tool mods: recycle-bin-tray-plus 1.0.1 -> 1.0.2,
  magic-pointer-plus 1.0.5 -> 1.0.6, better-volume-mixer-plus 1.4.1 -> 1.4.2,
  seamless-dictate 1.0.4 -> 1.0.5, window-manager 1.3.1 -> 1.3.2.
- Staging: `work\2026-11-09-flyout-match\menu-skin\patch-hover-gap.py`.

Verified: receipt `backups\2026-11-09\menu-hover-gap\receipt.txt` (six compiles exit 0,
all on); Window Manager's elevated helper restarted at 5:38 pm. Captures with the first
and last rows hovered, and the Notepad++ menu: `reports\2026-11-09-menu-gap-*.png`.

Rollback (elevated): `scripts\2026-11-09-menu-hover-gap.ps1 -Action rollback` (restores
the first backed-up sources in `backups\2026-11-09\menu-hover-gap\` and compiles).
