[CmdletBinding()]
param([switch]$Install,[switch]$Rollback,[switch]$OnlyVisualizer)
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$backup="$root\backups\2026-10-03\taskbar-widget-fit"
$packages=@(
 @{Id='local@taskbar-weather';Version='1.2.3';Source="$root\work\taskbar-weather\taskbar-weather.wh.cpp";Dll="$root\work\taskbar-weather\local@taskbar-weather_1.2.3_1.dll"},
 @{Id='local@taskbar-system-info-weather';Version='1.0.1';Source="$root\work\taskbar-widget-fit\monitor.wh.cpp";Dll="$root\work\taskbar-widget-fit\monitor.dll"},
 @{Id='local@davids-audio-visualizer';Version='1.0.1';Source="$root\work\taskbar-widget-fit\visualizer.wh.cpp";Dll="$root\work\taskbar-widget-fit\visualizer.dll"}
)
if($OnlyVisualizer){$packages=@($packages | Where-Object {$_.Id -eq 'local@davids-audio-visualizer'})}
if(!$Install -and !$Rollback){foreach($p in $packages){Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$($p.Id)" | Select-Object PSChildName,Version,Disabled,LibraryFileName};exit}
foreach($p in $packages){
 $key="HKLM:\SOFTWARE\Windhawk\Engine\Mods\$($p.Id)"
 if($Install -and !(Test-Path $p.Dll)){throw "Missing build for $($p.Id)"}
}
foreach($p in $packages){
 $key="HKLM:\SOFTWARE\Windhawk\Engine\Mods\$($p.Id)"
 Set-ItemProperty $key Disabled 1
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
}
Start-Sleep -Seconds 4
foreach($p in $packages){
 $key="HKLM:\SOFTWARE\Windhawk\Engine\Mods\$($p.Id)"
 if($Rollback){
  Copy-Item "$backup\$($p.Id).wh.cpp" "C:\ProgramData\Windhawk\ModsSource\$($p.Id).wh.cpp" -Force
  & reg.exe import "$backup\$($p.Id).reg"
  if($LASTEXITCODE){throw 'Registry rollback failed'}
 }else{
  $name="$($p.Id)_$($p.Version)_fit1.dll"
  $dest="C:\ProgramData\Windhawk\Engine\Mods\64\$name"
  Copy-Item $p.Dll $dest -Force
  if($p.Id -eq 'local@davids-audio-visualizer'){
   $dll32="$root\work\taskbar-widget-fit\visualizer-32.dll"
   $dest32="C:\ProgramData\Windhawk\Engine\Mods\32\$name"
   Copy-Item $dll32 $dest32 -Force
   if((Get-FileHash $dll32).Hash -ne (Get-FileHash $dest32).Hash){throw '32-bit DLL hash mismatch'}
  }
  Copy-Item $p.Source "C:\ProgramData\Windhawk\ModsSource\$($p.Id).wh.cpp" -Force
  if((Get-FileHash $p.Dll).Hash -ne (Get-FileHash $dest).Hash){throw 'DLL hash mismatch'}
  Set-ItemProperty $key LibraryFileName $name
  Set-ItemProperty $key Version $p.Version
  Set-ItemProperty $key Disabled 0
 }
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 Write-Output "$($p.Id) version=$((Get-ItemProperty $key).Version) disabled=$((Get-ItemProperty $key).Disabled)"
}
