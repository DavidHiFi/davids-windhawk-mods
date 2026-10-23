# Tray gap evened: network icon to clock

Date: 2026-10-11
Thread: tray-gap-fix

## Ask

The 2026-10-07 fix (rule 61 `Margin=0,0,-10,0`) had overshot: the network-to-clock
gap was visibly tighter than the speaker-to-network gap. Make all tray gaps even.

## Measured (PrintWindow capture `traybar-0.png`, 2560x50, bg 18,18,20)

Before: speaker glyph `..2428`, network glyph `2440..2455` (16px, unclipped),
speaker-to-network ink gap 11px, network-to-clock ink gap 5px.

## Fix (windows-11-taskbar-styler, hot-reload, no restart)

- `controlStyles[61].styles[0]` on `SystemTray.OmniButton#ControlCenterButton`:
  `Margin=0,0,-10,0` -> `Margin=0,0,-4,0`.
- Bumped `SettingsChangeTime`. Verified by read-back.
- Tray lays out right-to-left (`x = nextX - rightMargin - width - 10`), so +6 on
  the right margin shifts the network button and everything left of it 6px left;
  left-neighbour gaps are unchanged, only the clock seam opens.

After: network glyph `2434..2449` (still 16px), speaker-to-network 11px,
network-to-clock 11px. Both sit in the tray's 10-14px rhythm.

## Records

- Backup: `backups\2026-10-11-tray-gap-even\windows-11-taskbar-styler-before.reg`
- Apply/rollback: `scripts\2026-10-11-tray-gap-even.ps1` (`-Rollback` re-imports backup, bumps)
- Evidence: `reports\2026-10-11-tray-gap-even\` (traybar-0.png, tray-right-4x-after.png, receipt.json)
