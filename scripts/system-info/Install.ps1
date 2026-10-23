[CmdletBinding()]
param([switch]$Install,[switch]$Rollback)
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$id='local@taskbar-system-info-weather'
$key="HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$backup="$root\backups\2026-10-03\system-info-v1.2.2"
$job="$root\work\windhawk-system-info"
$source="$job\repo\mods\local\taskbar-system-info-weather\taskbar-system-info-weather.wh.cpp"
$destSource="C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
if(!$Install -and !$Rollback){Get-ItemProperty $key;Get-ItemProperty "$key\Settings";exit}
if($Install -and $Rollback){throw 'Choose Install or Rollback'}
if($Install){
 if(!(Test-Path "$job\system-info.dll")){throw 'Build missing'}
 New-Item -ItemType Directory -Force $backup | Out-Null
 if(!(Test-Path "$backup\before.reg")){
  & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\before.reg" /y
  if($LASTEXITCODE){throw 'Registry backup failed'}
  Copy-Item $destSource "$backup\before.wh.cpp"
  $old=(Get-ItemProperty $key).LibraryFileName
  Copy-Item "C:\ProgramData\Windhawk\Engine\Mods\64\$old" "$backup\before.dll"
 }
}
Set-ItemProperty $key Disabled 1
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Start-Sleep -Seconds 4
if($Rollback){
 Copy-Item "$backup\before.wh.cpp" $destSource -Force
 foreach($name in @('itemGap','showComputeGraphs','showMemoryGraphs','showMemoryBars')){
  Remove-ItemProperty "$key\Settings" $name -ErrorAction SilentlyContinue
 }
 & reg.exe import "$backup\before.reg"
 if($LASTEXITCODE){throw 'Registry rollback failed'}
 $old=(Get-ItemProperty $key).LibraryFileName
 if((Get-FileHash "$backup\before.dll").Hash -ne (Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$old").Hash){throw 'Rollback DLL hash mismatch'}
 if((Get-FileHash "$backup\before.wh.cpp").Hash -ne (Get-FileHash $destSource).Hash){throw 'Rollback source hash mismatch'}
}else{
 $name='local@taskbar-system-info-weather_1.2.2_1.dll'
 $dest="C:\ProgramData\Windhawk\Engine\Mods\64\$name"
 Copy-Item "$job\system-info.dll" $dest -Force
 Copy-Item $source $destSource -Force
 if((Get-FileHash "$job\system-info.dll").Hash -ne (Get-FileHash $dest).Hash){throw 'DLL hash mismatch'}
 if((Get-FileHash $source).Hash -ne (Get-FileHash $destSource).Hash){throw 'Source hash mismatch'}
 Set-ItemProperty $key LibraryFileName $name
 Set-ItemProperty $key Version '1.2.2'
 Set-ItemProperty $key Disabled 0
}
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Get-ItemProperty $key | Select-Object Version,LibraryFileName,Disabled


