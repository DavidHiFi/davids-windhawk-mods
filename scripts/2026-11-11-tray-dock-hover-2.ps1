param([ValidateSet('Apply','Rollback')][string]$Action='Apply')
# 2026-11-11 pass 2. Run ELEVATED. Settings only, no recompile, no Explorer restart.
# - Rule 12 (network button frame = right cap of the tray dock): BorderBrush solid grey -> two-stop
#   grey LinearGradientBrush, so System Info 1.4.30 can recolour it in place on hover
#   (the hover gradient stopped short of the right end).
# - Rule 53 (network hover box): 22x20 -> 26x26, same as the other tray icon boxes.
$ErrorActionPreference='Stop'
trap { "ERROR: $_ (line $($_.InvocationInfo.ScriptLineNumber))"; exit 1 }
$sty='HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'; $S="$sty\Settings"
$bk='H:\Windhawk Configuration\backups\2026-11-11-tray-hover'
function Bump { Set-ItemProperty $sty SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord }
if($Action -eq 'Rollback'){ & reg.exe import "$bk\styler-pass2.reg" | Out-Null; Bump; 'rolled back'; return }
if(-not (Test-Path "$bk\styler-pass2.reg")){ & reg.exe export ($S -replace 'HKLM:','HKLM') "$bk\styler-pass2.reg" /y | Out-Null }
function Set1($name,$expectPrefix,$value){
    $cur=(Get-ItemProperty $S).$name
    if($null -eq $cur -or -not $cur.StartsWith($expectPrefix)){ throw "$name is '$cur', expected $expectPrefix" }
    Set-ItemProperty $S $name $value; "$name : $cur -> $value" }
Set1 'controlStyles[12].styles[5]' 'BorderBrush' 'BorderBrush:=<LinearGradientBrush StartPoint="0,0.5" EndPoint="1,0.5"><GradientStop Color="#E645475A" Offset="0"/><GradientStop Color="#E645475A" Offset="1"/></LinearGradientBrush>'
Set1 'controlStyles[53].styles[0]' 'Width' 'Width=26'
Set1 'controlStyles[53].styles[1]' 'Height' 'Height=26'
Bump
'applied'
