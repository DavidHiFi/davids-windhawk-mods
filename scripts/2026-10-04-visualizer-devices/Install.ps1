[CmdletBinding()]
param([switch]$Audit,[switch]$Install,[switch]$Rollback)
$ErrorActionPreference='Stop'
$root='H:\Windhawk Configuration'
$backup="$root\backups\2026-10-04-visualizer-devices"
$report="$root\reports\2026-10-04-visualizer-devices"
$id='local@davids-audio-visualizer'
$key="HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$source="C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
if(!$Install -and !$Rollback){Get-ItemProperty $key;Get-FileHash $source;exit}
if($Install -and !(Test-Path "$backup\mod.reg")){
 & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\mod.reg" /y
 if($LASTEXITCODE){throw 'Backup failed'}
 Copy-Item $source "$backup\source.wh.cpp" -Force
 $old=(Get-ItemProperty $key).LibraryFileName
 foreach($arch in @('64','32')){Copy-Item "C:\ProgramData\Windhawk\Engine\Mods\$arch\$old" "$backup\original-$arch.dll" -Force}
}
Set-ItemProperty $key Disabled 1
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Start-Sleep -Seconds 4
if($Rollback){
 Copy-Item "$backup\source.wh.cpp" $source -Force
 & reg.exe import "$backup\mod.reg"
 if($LASTEXITCODE){throw 'Rollback failed'}
}else{
 $build="$root\work\visualizer-devices-20261004\build"
 foreach($arch in @('64','32')){
  $src="$build\${id}_1.1.0_1_${arch}.dll"
  $dst="C:\ProgramData\Windhawk\Engine\Mods\$arch\${id}_1.1.0_6.dll"
  Copy-Item $src $dst -Force
  if((Get-FileHash $src).Hash -ne (Get-FileHash $dst).Hash){throw 'DLL mismatch'}
 }
 Copy-Item "$root\work\visualizer-devices-20261004\mods\local\davids-audio-visualizer\davids-audio-visualizer.wh.cpp" $source -Force
 Set-ItemProperty $key LibraryFileName "${id}_1.1.0_6.dll"
 Set-ItemProperty $key Version '1.1.0'
 Set-ItemProperty $key Disabled 0
}
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Get-ItemProperty $key | Select-Object Version,Disabled,LibraryFileName | ConvertTo-Json | Set-Content "$report\install-receipt.json"
Get-FileHash $source





