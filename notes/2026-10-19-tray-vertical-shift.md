# Right-side tray cluster drawn 10px too high: root cause and fix (2026-10-19)

Supersedes `2026-10-18-tray-icons-vertical-fix.md` (that note's root cause was wrong:
rule 61's margin is horizontal-only and was never the problem).

## Symptom (owner's screenshot, 2026-10-18 ~10:02 PM)

Everything on the right of the taskbar - AI quota bars, overflow chevron, tray icons,
clock - drawn in the top ~30px of the 50px taskbar, with a dead band at the bottom.
Left-side app pills were fine and centered.

## Root cause (measured)

Row-ink scan of the Shell_TrayWnd strip (2560x50), right half x>=1600:

- Broken: ink rows 2..29, rows 30..49 completely empty. Whole right cluster
  (quota bars, chevron, tray icons, clock) pinned to the top of the bar.
- Left-side pills: rows 2..45, centered on the pill design (2..46 span). Fine.

The whole right cluster lives inside `SystemTray.SystemTrayFrame`'s frame grid
(injected mods included - the AI quota bars also moved when it moved). No styler
rule anchored it vertically, so after some earlier change the frame resumed its
native top-anchored position inside the taskbar. Rule 61 (`OmniButton#ControlCenterButton`
margin) is horizontal-only and was never responsible.

## Fix (windows-11-taskbar-styler rule 63, hot reload)

- `controlStyles[63].target`:
  `SystemTray.SystemTrayFrame > StackPanel#SystemTrayFrameGrid, SystemTray.SystemTrayFrame > Grid#SystemTrayFrameGrid`
- `controlStyles[63].styles[0]`: `VerticalAlignment=1`
- `controlStyles[63].styles[1]`: tuning history 14 (too low) -> 9 -> 4 (too high,
  owner) -> 9. Owner's final word 2026-10-19: "centred, how they're meant to be".
  Final: `Margin=0,9,0,0` - cluster ink band rows 11..38, symmetric 11px clearance
  in the 50px bar, aligned with the pill interior. Margin 9 IS the centered state;
  do not "improve" it again.
- `controlStyles[63].styles[2]`: `VerticalAlignment@1=1` (inert safeguard probe slot kept in
  the same style)
- Applied elevated via `H:\System Configuration\scripts\Invoke-Elevated.ps1` running
  `scripts\2026-10-19-tray-vertical-shift.ps1`; `SettingsChangeTime` bumped each round.

## Verified (measured + visuals)

- After margin 14: ink rows 16..43 (moved exactly 14). After margin 9: rows 11..38.
- Visual proof sent as real T3 thread attachments this session: `tray-before-3x.png`
  (pinned high) and `tray-after-3x.png` (centered). Sources:
  `reports\2026-10-19-tray-vertical\tb-right-3x-before.png` / `t-b-right-3x-after.png`.

## Records

- Backup: `backups\2026-10-19-tray-vertical\styler-before-reg63.reg`
- Apply script: `scripts\2026-10-19-tray-vertical-shift.ps1`
- Guard: `scripts\guard-tray-vertical.ps1` (also restores rule 61 `-4,0` and now rule 63)
- Utilities: `scripts\Crop-TaskbarRight.ps1`, `scripts\Measure-TrayRows.ps1`

## Errors worth remembering

- `Set-ItemProperty` through `-ArgumentList` mangled the margins once (`Margin=0 0 -4 0\`);
  script files run through `Invoke-Elevated.ps1 -File` are the reliable route.
- A first capture right after a settings bump can catch the tray mid-reload and show it
  empty; sleep ~3s and capture again before concluding anything broke.