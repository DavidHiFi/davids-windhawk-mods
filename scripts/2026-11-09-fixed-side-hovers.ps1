param([switch]$Audit,[switch]$Install,[switch]$Rollback)
$ErrorActionPreference='Stop'
$base='SOFTWARE\Windhawk\Engine\Mods'
$bk='H:\Windhawk Configuration\backups\2026-11-09-fixed-side-hovers'
$receipt="$bk\values.json"
$styler='windows-11-taskbar-styler'
$changes=@{
 'local@seamless-dock-animation'=@{'OtherDocks.Tray'=0;'OtherDocks.AiUsage'=0;'OtherDocks.Media'=0;'SideTest'=0}
 'local@seamless-tray-drawer'=@{'hoverZoom.enabled'=0}
}
$oldStyles=Get-Content 'H:\Windhawk Configuration\backups\2026-11-09-hover-borders\v229\styler.json' -Raw | ConvertFrom-Json
$styles=@{}
foreach($name in @('controlStyles[27].styles[1]','controlStyles[27].styles[5]','controlStyles[34].styles[2]')){$styles[$name]=$oldStyles.$name}
$styles['controlStyles[43].target']='SystemTray.OmniButton#NotificationCenterButton > Grid > Border'
$changes[$styler]=$styles
if($Install){
 if(Test-Path $receipt){throw 'Already installed'}
 New-Item $bk -ItemType Directory -Force | Out-Null
 $saved=@{}
 foreach($id in $changes.Keys){
  & reg.exe export "HKLM\$base\$id" "$bk\$id.reg" /y | Out-Null
  if($LASTEXITCODE){throw 'Backup failed'}
  $key=[Microsoft.Win32.Registry]::LocalMachine.OpenSubKey("$base\$id\Settings")
  $saved[$id]=@{}
  foreach($name in $changes[$id].Keys){$saved[$id][$name]=$key.GetValue($name)}
  $key.Close()
 }
 $saved | ConvertTo-Json -Depth 5 | Set-Content $receipt
}
if($Rollback){
 $changes=@{}
 $saved=Get-Content $receipt -Raw | ConvertFrom-Json
 foreach($mod in $saved.PSObject.Properties){$changes[$mod.Name]=@{};foreach($v in $mod.Value.PSObject.Properties){$changes[$mod.Name][$v.Name]=$v.Value}}
}
foreach($id in @('local@seamless-dock-animation','local@seamless-tray-drawer',$styler)){
 $key=[Microsoft.Win32.Registry]::LocalMachine.OpenSubKey("$base\$id\Settings",($Install -or $Rollback))
 foreach($name in $changes[$id].Keys){
  $value=$changes[$id][$name]
  if($Install -or $Rollback){
   if($null -eq $value){$key.DeleteValue($name,$false)}else{$kind=if($value -is [string]){'String'}else{'DWord'};$key.SetValue($name,$value,$kind)}
  }
  $actual=$key.GetValue($name)
  if(($Install -or $Rollback) -and $actual -ne $value){throw "Readback failed: $id $name"}
  "$id : $name = $actual"
 }
 $key.Close()
 if($Install -or $Rollback){
  $mod=[Microsoft.Win32.Registry]::LocalMachine.OpenSubKey("$base\$id",$true)
  $mod.SetValue('SettingsChangeTime',[int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds(),'DWord');$mod.Close()
  Start-Sleep -Seconds 2
 }
}
