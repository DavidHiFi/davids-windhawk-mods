# Tray: gap between hidden-icons button and recycle bin (2026-11-10)

Owner, about 12:45 am: the gap between the hidden-icons button and the recycle bin was bigger than the
gaps between the other tray icons. The right side of the hover box must not be cut off.

## Cause

UIA bounds before: hidden-icons button x=2212 w=26 (ends 2238), recycle bin starts at 2242. Every other
tray icon is 26 px wide and touches the next one, so that slot had 4 px extra.

## Change

| Setting | Old | New |
| --- | --- | --- |
| Taskbar Styler `controlStyles[54].styles[0]` (target `SystemTray.ChevronIconView`) | `Margin=0` | `Margin=0,0,-4,0` |

The button keeps its full 26 px width; only its outside margin changed, so its hover box is not clipped.

- Script: `scripts\2026-11-10-tray-chevron-gap.ps1 -Action Install|Rollback|Audit` (elevated).
- Backup: `backups\2026-11-10-tray-chevron-gap\styler.reg`, `old-value.txt`, receipts.
- Rollback: elevated `scripts\2026-11-10-tray-chevron-gap.ps1 -Action Rollback` (writes `Margin=0` back).
- No Explorer restart; hot-reload through `SettingsChangeTime`.

## Verified live, 12:56 am

- UIA after: hidden-icons x=2216 w=26 (ends 2242), recycle bin 2242. All slots now 26 px and touching.
- Hover captures (under `coop lock desktop`, owner idle, cursor put back): the hidden-icons hover box
  shows all four rounded corners and its right edge; the recycle bin hover box is also whole.
- Captures: `work\2026-11-10-tray-chevron-gap\before-3x.png`, `after-rest-4x.png`,
  `after-hover-chevron-4x.png`, `after-hover-bin-4x.png`.
