param([switch]$Install,[switch]$Audit,[switch]$Rollback)
$ErrorActionPreference='Stop'
$base='SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$bk='H:\Windhawk Configuration\backups\2026-11-09-network-overflow-hover'
$receipt="$bk\values.json"
$key=[Microsoft.Win32.Registry]::LocalMachine.OpenSubKey("$base\Settings",($Install -or $Rollback))
$set=[ordered]@{
 'controlStyles[27].target'='SystemTray.NotifyIconView#NotifyItemIcon > Grid#ContainerGrid@ > Border#BackgroundBorder, SystemTray.IconView#SystemTrayIcon > Grid#ContainerGrid@ > Border#BackgroundBorder, SystemTray.ChevronIconView > Grid#ContainerGrid@ > Border#BackgroundBorder, SystemTray.NotifyIconView > Grid#ContainerGrid@ > Border#BackgroundBorder, SystemTray.OmniButton#ControlCenterButton > Grid@CommonStates > Border#BackgroundBorder'
 'controlStyles[55].target'='SystemTray.OmniButton#ControlCenterButton > Grid > Border#BackgroundBorder'
 'controlStyles[55].styles[0]'='Opacity=1'
 'controlStyles[53].styles[0]'='Width=22'
}
if($Install){
 if(Test-Path $receipt){throw 'Already applied'}
 if($null -ne $key.GetValue('controlStyles[55].target')){throw 'Rule 55 occupied'}
 New-Item $bk -ItemType Directory -Force | Out-Null
 & reg.exe export "HKLM\$base" "$bk\before.reg" /y | Out-Null
 if($LASTEXITCODE){throw 'Backup failed'}
 $old=[ordered]@{};foreach($name in $set.Keys){$old[$name]=$key.GetValue($name)}
 $old | ConvertTo-Json | Set-Content $receipt
}
if($Rollback){
 $set=[ordered]@{};$old=Get-Content $receipt -Raw | ConvertFrom-Json
 foreach($p in $old.PSObject.Properties){$set[$p.Name]=$p.Value}
}
foreach($name in $set.Keys){
 if($Install -or $Rollback){if($null -eq $set[$name]){$key.DeleteValue($name,$false)}else{$key.SetValue($name,[string]$set[$name],'String')}}
 $actual=$key.GetValue($name)
 if(($Install -or $Rollback) -and $actual -ne $set[$name]){throw "Readback failed: $name"}
 "$name = $actual"
}
$key.Close()
if($Install -or $Rollback){
 $mod=[Microsoft.Win32.Registry]::LocalMachine.OpenSubKey($base,$true)
 $mod.SetValue('SettingsChangeTime',[int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds(),'DWord');$mod.Close()
}
