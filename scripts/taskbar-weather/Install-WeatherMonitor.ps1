[CmdletBinding()]
param([switch]$Rollback)
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$backup="$root\backups\2026-09-30\taskbar-weather-1.2"
$stock='HKLM:\SOFTWARE\Windhawk\Engine\Mods\taskbar-system-info'
$local='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-system-info-weather'
if($Rollback){
 if(Test-Path $local){Set-ItemProperty $local Disabled 1;Set-ItemProperty $local SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())}
 Start-Sleep -Seconds 4
 & reg.exe import "$backup\stock-monitor-before.reg"
 if($LASTEXITCODE){throw 'Stock monitor restore failed'}
 Set-ItemProperty $stock SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 'Stock performance monitor restored; local fork disabled.'
 exit
}
if(!(Test-Path "$backup\stock-monitor-before.reg")){
 & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\taskbar-system-info' "$backup\stock-monitor-before.reg" /y
 if($LASTEXITCODE){throw 'Stock monitor backup failed'}
}
$file='local@taskbar-system-info-weather_1.0.0_1.dll'
Copy-Item "$root\work\taskbar-weather\$file" ("C:\ProgramData\Windhawk\Engine\Mods\64\"+$file)
Copy-Item "$root\work\taskbar-weather\taskbar-system-info.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-system-info-weather.wh.cpp'
$registry=[Microsoft.Win32.Registry]::LocalMachine
$target=$registry.CreateSubKey('SOFTWARE\Windhawk\Engine\Mods\local@taskbar-system-info-weather')
$target.SetValue('Disabled',1,[Microsoft.Win32.RegistryValueKind]::DWord)
foreach($pair in @(@('Include','explorer.exe'),@('LibraryFileName',$file),@('Version','1.0.0'),@('Name','Taskbar System Info with Weather'))){$target.SetValue($pair[0],$pair[1],[Microsoft.Win32.RegistryValueKind]::String)}
$sourceSettings=$registry.OpenSubKey('SOFTWARE\Windhawk\Engine\Mods\taskbar-system-info\Settings')
$destSettings=$target.CreateSubKey('Settings')
foreach($name in $sourceSettings.GetValueNames()){$destSettings.SetValue($name,$sourceSettings.GetValue($name),$sourceSettings.GetValueKind($name))}
$destSettings.Close();$sourceSettings.Close();$target.Close()
Set-ItemProperty $stock Disabled 1
Set-ItemProperty $stock SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Start-Sleep -Seconds 4
Set-ItemProperty $local Disabled 0
Set-ItemProperty $local SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
if((Get-FileHash "$root\work\taskbar-weather\$file").Hash -ne (Get-FileHash ("C:\ProgramData\Windhawk\Engine\Mods\64\"+$file)).Hash){throw 'Local monitor hash mismatch'}
'Weather-aware local monitor installed; stock settings preserved. No Explorer restart.'
