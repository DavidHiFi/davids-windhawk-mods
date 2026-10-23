[CmdletBinding()]
param([switch]$Install,[switch]$Rollback)
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$backup="$root\backups\2026-10-05\weather-single-process"
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$installed='C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp'
$source="$root\work\taskbar-weather\taskbar-weather.wh.cpp"
$name='local@taskbar-weather_1.4.1_1.dll'
$dll="$root\work\taskbar-weather\$name"
if(!$Install -and !$Rollback){Get-ItemProperty $key | Select-Object Version,Disabled,LibraryFileName;exit}
if($Install){
 if(Test-Path "$backup\before.reg"){throw 'Backup already exists; use audit or rollback'}
 New-Item -ItemType Directory -Force $backup | Out-Null
 & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather' "$backup\before.reg" /y
 if($LASTEXITCODE){throw 'Backup failed'}
 Copy-Item $installed "$backup\before.wh.cpp"
 $prior=Get-ItemProperty $key
 Copy-Item "C:\ProgramData\Windhawk\Engine\Mods\64\$($prior.LibraryFileName)" $backup
 Get-ItemProperty "$key\Settings" | Export-Clixml "$backup\settings.xml"
}
Set-ItemProperty $key Disabled 1
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Start-Sleep -Seconds 4
if($Rollback){
 Copy-Item "$backup\before.wh.cpp" $installed -Force
 & reg.exe import "$backup\before.reg"
 if($LASTEXITCODE){throw 'Rollback failed'}
}else{
 $dest="C:\ProgramData\Windhawk\Engine\Mods\64\$name"
 Copy-Item $dll $dest -Force
 Copy-Item $source $installed -Force
 if((Get-FileHash $dll).Hash -ne (Get-FileHash $dest).Hash){throw 'DLL mismatch'}
 if((Get-FileHash $source).Hash -ne (Get-FileHash $installed).Hash){throw 'Source mismatch'}
 Set-ItemProperty $key LibraryFileName $name
 Set-ItemProperty $key Version '1.4.1'
 Set-ItemProperty $key Disabled 0
}
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Get-ItemProperty $key | Select-Object Version,Disabled,LibraryFileName
'Only weather metadata and source changed. Existing settings preserved.'


