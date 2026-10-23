[CmdletBinding()]
param([switch]$Install,[switch]$Rollback,[int]$Revision=1)
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$backup="$root\backups\2026-09-30\taskbar-weather-1.2"
$report="$root\reports\2026-09-30\taskbar-weather"
if(!$Install -and !$Rollback){Get-ItemProperty $key | Select-Object Disabled,Version,LibraryFileName;exit}
$admin=([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if(!$admin){throw 'Use the saved silent-elevation wrapper.'}
if($Install){
 if(!(Test-Path "$backup\weather-before.reg")){
  New-Item -ItemType Directory -Force $backup | Out-Null
  & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather' "$backup\weather-before.reg" /y
  if($LASTEXITCODE){throw 'Weather backup failed'}
  Copy-Item 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp' "$backup\source-before.wh.cpp"
  (Get-ItemProperty $key | Select-Object Disabled,LibraryFileName,Version) | ConvertTo-Json | Set-Content "$backup\metadata-before.json"
 }
 $location=Get-Content "$root\work\taskbar-weather\private-location-next.json" -Raw | ConvertFrom-Json
 $source="$root\work\taskbar-weather\taskbar-weather.wh.cpp"
 $version=(Select-String -Path $source -Pattern '^// @version\s+(\S+)').Matches[0].Groups[1].Value
 $dll="$root\work\taskbar-weather\local@taskbar-weather_${version}_1.dll"
 if(!(Test-Path $dll)){throw 'Build is missing'}
 Set-ItemProperty $key Disabled 1
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 Start-Sleep -Seconds 4
 $installedFile="local@taskbar-weather_${version}_${Revision}.dll"
 Copy-Item $dll ("C:\ProgramData\Windhawk\Engine\Mods\64\"+$installedFile)
 Copy-Item $source 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp' -Force
 foreach($pair in @(@('latitude',$location.latitude),@('longitude',$location.longitude),@('placeName',$location.placeName))){
  New-ItemProperty "$key\Settings" -Name $pair[0] -Value $pair[1] -PropertyType String -Force | Out-Null
  if((Get-ItemPropertyValue "$key\Settings" $pair[0]) -ne $pair[1]){throw 'Town settings read-back failed'}
 }
 Set-ItemProperty "$key\Settings" updateMinutes 10
 # The taskbar row has to use the performance panel's font, not a bigger copy of it.
 $panelFamily=(Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-system-info-weather\Settings' -ErrorAction SilentlyContinue).fontFamily
 if($panelFamily){Set-ItemProperty "$key\Settings" fontFamily $panelFamily}
 Set-ItemProperty "$key\Settings" fontSize 11
 if((Get-ItemPropertyValue "$key\Settings" fontSize) -ne 11){throw 'Font size read-back failed'}
 if($panelFamily -and (Get-ItemPropertyValue "$key\Settings" fontFamily) -ne $panelFamily){throw 'Font family read-back failed'}
 Set-ItemProperty $key LibraryFileName $installedFile
 Set-ItemProperty $key Version $version
 Set-ItemProperty $key Disabled 0
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 if((Get-FileHash $dll).Hash -ne (Get-FileHash ("C:\ProgramData\Windhawk\Engine\Mods\64\"+$installedFile)).Hash){throw 'Installed DLL hash mismatch'}
 [pscustomobject]@{Timestamp=(Get-Date).ToString('o');Version=$version;Revision=$Revision;DllHash=(Get-FileHash $dll).Hash;SourceHash=(Get-FileHash $source).Hash;Location='User-selected town center; exact location omitted';TownSettingsVerified=$true;ExplorerRestarted=$false;GlobalEngineRestarted=$false} | ConvertTo-Json | Set-Content "$report\upgrade-installed.json"
 'Weather1.2 installed. Town settings and binary independently verified; no process restart.'
}
if($Rollback){
 if(!(Test-Path "$backup\weather-before.reg")){throw 'Rollback snapshot missing'}
 Set-ItemProperty $key Disabled 1
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 if(Test-Path "$backup\stock-monitor-before.reg"){& "$root\scripts\taskbar-weather\Install-WeatherMonitor.ps1" -Rollback}
 Start-Sleep -Seconds 4
 Copy-Item "$backup\source-before.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp' -Force
 Remove-ItemProperty "$key\Settings" placeName -ErrorAction SilentlyContinue
 & reg.exe import "$backup\weather-before.reg"
 if($LASTEXITCODE){throw 'Weather registry restore failed'}
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 'Previous weather package and settings restored. No process restart.'
}
