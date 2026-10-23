$ct = [int][math]::Round((Get-Date).ToUniversalTime().Subtract((Get-Date '1970-01-01T00:00:00Z')).TotalSeconds)
New-ItemProperty -Path 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' -Name 'SettingsChangeTime' -Value $ct -PropertyType DWord -Force | Out-Null
Write-Output "Bumped SettingsChangeTime to $ct"
