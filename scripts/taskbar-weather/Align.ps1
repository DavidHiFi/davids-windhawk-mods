$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$backup="$root\backups\2026-09-30\taskbar-weather"
$weather='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$monitor='HKLM:\SOFTWARE\Windhawk\Engine\Mods\taskbar-system-info'
if(!(Test-Path "$backup\monitor-before.reg")){
 & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\taskbar-system-info' "$backup\monitor-before.reg" /y
 if($LASTEXITCODE){throw 'Monitor registry backup failed'}
 Copy-Item 'C:\ProgramData\Windhawk\ModsSource\taskbar-system-info.wh.cpp' "$backup\monitor-source-before.wh.cpp"
}
Set-ItemProperty $weather Disabled 1
Set-ItemProperty $weather SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Set-ItemProperty $monitor Disabled 1
Set-ItemProperty $monitor SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Start-Sleep -Seconds 4
Copy-Item "$root\work\taskbar-weather\local@taskbar-weather_1.0.0_1.dll" 'C:\ProgramData\Windhawk\Engine\Mods\64\local@taskbar-weather_1.0.0_3.dll'
Copy-Item "$root\work\taskbar-weather\taskbar-weather.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp' -Force
Copy-Item "$root\work\taskbar-weather\taskbar-system-info_1.5.0.weather1_1.dll" 'C:\ProgramData\Windhawk\Engine\Mods\64\taskbar-system-info_1.5.0.weather1_1.dll'
Copy-Item "$root\work\taskbar-weather\taskbar-system-info.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\taskbar-system-info.wh.cpp' -Force
Set-ItemProperty $weather LibraryFileName 'local@taskbar-weather_1.0.0_3.dll'
Set-ItemProperty $monitor LibraryFileName 'taskbar-system-info_1.5.0.weather1_1.dll'
Set-ItemProperty $monitor Version '1.5.0.weather1'
# The coordinated fork falls back to the original monitor offset.
Set-ItemProperty "$monitor\Settings" leftOffset 175
Set-ItemProperty $weather Disabled 0
Set-ItemProperty $weather SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Set-ItemProperty $monitor Disabled 0
Set-ItemProperty $monitor SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
foreach($pair in @(@('local@taskbar-weather_1.0.0_3.dll','local@taskbar-weather_1.0.0_1.dll'),@('taskbar-system-info_1.5.0.weather1_1.dll','taskbar-system-info_1.5.0.weather1_1.dll'))){
 if((Get-FileHash ('C:\ProgramData\Windhawk\Engine\Mods\64\'+$pair[0])).Hash -ne (Get-FileHash ("$root\work\taskbar-weather\"+$pair[1])).Hash){throw 'Aligned DLL hash mismatch'}
}
'Weather and performance panel now share measured layout. DLL hashes verified. No process restarted.'
