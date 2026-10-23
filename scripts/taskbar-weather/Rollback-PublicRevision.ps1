[CmdletBinding()]
param([switch]$Apply)
$ErrorActionPreference='Stop'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$backup='H:\System Configuration\backups\2026-09-30\taskbar-weather-1.2.1'
if(!$Apply){Get-ItemProperty $key | Select-Object Disabled,Version,LibraryFileName; 'Apply restores the previous weather registry and source without restarting Explorer.';exit}
if(!(Test-Path "$backup\weather-before.reg") -or !(Test-Path "$backup\source-before.wh.cpp")){throw 'Rollback snapshot missing'}
Set-ItemProperty $key Disabled 1
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Start-Sleep -Seconds 4
Copy-Item "$backup\source-before.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp' -Force
& reg.exe import "$backup\weather-before.reg"
if($LASTEXITCODE){throw 'Registry restore failed'}
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Get-ItemProperty $key | Select-Object Disabled,Version,LibraryFileName
if((Get-FileHash "$backup\source-before.wh.cpp").Hash -ne (Get-FileHash 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp').Hash){throw 'Source verification failed'}
