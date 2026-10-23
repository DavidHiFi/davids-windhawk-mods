[CmdletBinding()]
param([int]$UpdateMinutes=10)
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$mod='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$now=[int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
Set-ItemProperty $mod Disabled 1
Set-ItemProperty $mod SettingsChangeTime $now
Start-Sleep -Seconds 3
Copy-Item "$root\work\taskbar-weather\local@taskbar-weather_1.0.0_1.dll" 'C:\ProgramData\Windhawk\Engine\Mods\64\local@taskbar-weather_1.0.0_2.dll' -Force
Copy-Item "$root\work\taskbar-weather\taskbar-weather.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp' -Force
Set-ItemProperty $mod LibraryFileName 'local@taskbar-weather_1.0.0_2.dll'
Set-ItemProperty "$mod\Settings" updateMinutes $UpdateMinutes
Set-ItemProperty $mod Disabled 0
Set-ItemProperty $mod SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
if((Get-FileHash 'C:\ProgramData\Windhawk\Engine\Mods\64\local@taskbar-weather_1.0.0_2.dll').Hash -ne (Get-FileHash "$root\work\taskbar-weather\local@taskbar-weather_1.0.0_1.dll").Hash){throw 'DLL hash mismatch'}
'Scoped weather revision activated and binary verified. No engine or Explorer restart.'
