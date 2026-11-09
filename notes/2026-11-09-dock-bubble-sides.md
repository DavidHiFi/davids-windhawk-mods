# 2026-11-09: taskbar icon bubbles lost their side borders

Mod: `windows-11-taskbar-styler` (settings only, no code change).
Script: `scripts\2026-11-09-dock-bubble-sides.ps1` (`-Action Audit|Install|Rollback`, run elevated
under `coop lock windhawk-engine`). Backup: `backups\2026-11-09-dock-bubble\taskbar-styler.reg`.

- Symptom: each pinned or open app bubble showed its rounded corners and top and bottom edges,
  but the left and right edges were missing.
- Cause: the bubble (rule 8, `Rectangle#RunningIndicator`) is 28 px wide, but its icon slot is
  26 px, so XAML clipped 1 px off each side. The straight sides sit in exactly that pixel.
- Change, applied 3:04 pm:
  - `controlStyles[8].styles[74]`: (none) -> `Margin=-1,0,-1,0`
  - `controlStyles[7].styles[2]` and `[6]` (hover face): `Margin=0` -> `Margin=-1,0,-1,0`
- Verified 3:05 pm from a screen capture: full-height blue left edge and mauve right edge on
  every bubble (`reports\2026-11-09-dock-pill\after-bubble.png`, before: `bubble-zoom.png`).
- Rollback: `scripts\2026-11-09-dock-bubble-sides.ps1 -Action Rollback` (puts `Margin=0` back
  and deletes the added value), or import the .reg backup.
- Trap hit again: `Get-ItemProperty -Name 'controlStyles[8]...'` treats brackets as wildcards and
  reads nothing. The script reads through `(Get-Item $key).GetValue($name)` instead.
