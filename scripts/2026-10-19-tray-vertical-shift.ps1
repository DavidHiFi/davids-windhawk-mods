# Shift the SystemTrayFrame cluster down: rule 63 VerticalAlignment center + margin nudge.
$ErrorActionPreference = 'Stop'
$settings = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$root = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'

# Rule 63: center + nudge down the whole tray cluster (both native template variants).
Set-ItemProperty -Path $settings -Name 'controlStyles[63].target' -Value 'SystemTray.SystemTrayFrame > StackPanel#SystemTrayFrameGrid, SystemTray.SystemTrayFrame > Grid#SystemTrayFrameGrid'
Set-ItemProperty -Path $settings -Name 'controlStyles[63].styles[0]' -Value 'VerticalAlignment=1'
Set-ItemProperty -Path $settings -Name 'controlStyles[63].styles[1]' -Value 'Margin=0,9,0,0'
Set-ItemProperty -Path $settings -Name 'controlStyles[63].styles[2]' -Value 'VerticalAlignment@1=1'

# Bump so the mod hot-reloads the new settings.
$ct = [int][math]::Round((Get-Date).ToUniversalTime().Subtract((Get-Date '1970-01-01T00:00:00Z')).TotalSeconds)
New-ItemProperty -Path $root -Name 'SettingsChangeTime' -Value $ct -PropertyType DWord -Force | Out-Null
Write-Output "rule 63 set, bumped to $ct"