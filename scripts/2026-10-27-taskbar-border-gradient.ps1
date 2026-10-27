# Taskbar border: same Catppuccin Mocha blue-to-mauve gradient as window-ring.exe.
# Rollback: reg import backups\2026-10-27-taskbar-styler-before-edge-fix.reg, then bump SettingsChangeTime.
$k = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
Set-ItemProperty "$k\Settings" -Name 'controlStyles[1].styles[4]' -Value 'Stroke:=<LinearGradientBrush StartPoint="0,0.5" EndPoint="1,0.5"><GradientStop Color="#89B4FA" Offset="0"/><GradientStop Color="#CBA6F7" Offset="1"/></LinearGradientBrush>'
Set-ItemProperty $k -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
