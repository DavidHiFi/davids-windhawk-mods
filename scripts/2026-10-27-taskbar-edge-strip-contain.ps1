# Keeps the taskbar blur inside the Catppuccin border: the BackgroundStroke edge strip
# (Margin 2,-4,2,-4) painted the fill 4px above and below the border. Collapse it.
# Rollback: reg import backups\2026-10-27-taskbar-styler-before-edge-fix.reg, then bump SettingsChangeTime.
$k = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' 'H:\Windhawk Configuration\backups\2026-10-27-taskbar-styler-before-edge-fix.reg' /y | Out-Null
Set-ItemProperty "$k\Settings" -Name 'controlStyles[2].styles[2]' -Value 'Visibility=Collapsed'
Set-ItemProperty $k -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
