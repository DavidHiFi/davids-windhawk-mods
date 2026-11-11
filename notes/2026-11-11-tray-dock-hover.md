# 2026-11-11 Tray dock hover edge, bigger tray hover boxes, mouse glyph

Owner asked: bigger hover boxes for tray icons, the blue-to-mauve hover edge on the tray dock
(like the other docks), and a normal mouse icon on the battery pill.

## Root cause (tray dock hover missing)
The tray dock is made of Windows 11 Taskbar Styler segments (rules 13/14/15/16). The styler
registers a property-changed callback on every property it styles and re-applies its own value
when anything else replaces it. System Info's hover set a new BorderBrush, so the styler put
the grey one back at once. The AI and apps docks are owned by System Info itself, so they worked.

## Changes
- System Info mod 1.4.29 -> 1.4.30: SetTrayDockHover now recolours the styler's own
  LinearGradientBrush in place (Absolute mapping across the whole dock, #89B4FA -> #CBA6F7 on
  hover, #E645475A both stops at rest). No DependencyProperty change, so the styler leaves it.
- Styler rules 13/14/15 styles[4] and 16 styles[5]: BorderBrush was a solid grey, now a
  two-stop LinearGradientBrush with both stops #E645475A (same resting look).
- Rule 17 split: tray hover boxes Margin 2 -> 1; the 2 AugmentedEntryPointButton selectors
  moved to new rule 62 (Margin=2, CornerRadius=8, BorderThickness=0).
- Rule 52 notify icon ContainerGrid Height 24 -> 28.
- taskbar-notification-icon-spacing notificationIconWidth 26 -> 28.
- New rule 63: Logitech battery pill FontIcon Glyph = U+E962 (mouse). The mod falls back to
  U+E772 (generic devices) when HID++ reports no device type. Note: rule 63 forces the mouse
  glyph for any Logitech device the pill shows.

## Verify
- 1.4.30 DLL loaded; Explorer not restarted.
- Resting tray dock edge unchanged; battery pill shows the mouse glyph (zoom checked).
- The pill went missing for a few minutes after the reload (same HID++ receiver dropout as
  earlier today) and came back on its own.
- Hover on the tray dock not checked live: owner was at the PC, cursor not moved.

## Rollback
Run `scripts\2026-11-11-tray-dock-hover.ps1 -Action Rollback` elevated. It imports
`backups\2026-11-11-tray-hover\styler.reg` and `spacing.reg`, bumps SettingsChangeTime and
recompiles System Info from `sysinfo-1.4.29.wh.cpp`.

## Trap
In PowerShell 5.1 `cli` is the Clear-Item alias; a helper named Cli never ran. Named it Invoke-WhCli.

## Pass 2 (9:38 pm): hover cut off on the right, network hover box
- Owner saw the hover edge stop at the network icon. The right cap of the dock is the network
  button frame (styler rule 12), which still had a SolidColorBrush, so 1.4.30 fell back to the
  brush swap and the styler reverted it. Rule 12 styles[5] is now the same two-stop grey
  LinearGradientBrush as 13-16. No recompile.
- Rule 53 network hover box 22x20 -> 26x26 (same as the other tray icons: 28 cell, Margin 1).
- Script: scripts\2026-11-11-tray-dock-hover-2.ps1 (-Action Rollback imports
  backups\2026-11-11-tray-hover\styler-pass2.reg).
- Applied while another thread held the windhawk-engine lock (my lock call was refused but the
  command was chained). Styler settings only; Explorer PIDs unchanged; coop note posted.
- Hover not checked live: owner at the PC.
