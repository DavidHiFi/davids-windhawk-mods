param([ValidateSet('Apply','Rollback')][string]$Action='Apply')
# 2026-11-11: tray dock hover edge, bigger tray icon hover boxes, mouse glyph on the battery pill.
# Run ELEVATED. No Explorer restart: mods hot-load on enable and on SettingsChangeTime.
# - System Info 1.4.29 -> 1.4.30: the styler re-applies the tray pieces' BorderBrush whenever
#   another mod replaces it, so the hover gradient was reverted instantly. 1.4.30 recolours the
#   styler's own LinearGradientBrush in place.
# - Styler rules 13/14/15/16: tray piece edge becomes a two-stop grey LinearGradientBrush (same look).
# - Rule 17 split: tray hover boxes Margin 2 -> 1; AugmentedEntryPoint keeps Margin 2 in new rule 62.
# - Rule 52: notify icon ContainerGrid 24 -> 28 tall. Icon spacing mod: width 26 -> 28.
# - New rule 63: battery pill device icon shows the mouse glyph (U+E962) instead of the generic
#   devices glyph the mod falls back to when HID++ reports no type.
$ErrorActionPreference='Stop'
trap { "ERROR: $_ (line $($_.InvocationInfo.ScriptLineNumber))"; exit 1 }
$bk='H:\Windhawk Configuration\backups\2026-11-11-tray-hover'
$work='H:\Windhawk Configuration\work\2026-11-11-tray-hover'
$k='HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$sty="$k\windows-11-taskbar-styler"; $spc="$k\taskbar-notification-icon-spacing"
$sysId='local@taskbar-system-info-weather'; $mediaId='local@seamless-media-player'
$srcLive="C:\ProgramData\Windhawk\ModsSource\$sysId.wh.cpp"
$cli='C:\Program Files\Windhawk\windhawk-cli.exe'
function Bump($key){ Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord }
function Invoke-WhCli([string[]]$a){
    $psi=New-Object Diagnostics.ProcessStartInfo $cli
    $psi.Arguments=($a | ForEach-Object { '"' + $_ + '"' }) -join ' '
    $psi.UseShellExecute=$false; $psi.CreateNoWindow=$true
    $psi.RedirectStandardOutput=$true; $psi.RedirectStandardError=$true
    $p=[Diagnostics.Process]::Start($psi)
    try{ $p.PriorityClass='Idle' }catch{}
    $errTask=$p.StandardError.ReadToEndAsync()
    $out=$p.StandardOutput.ReadToEnd(); $p.WaitForExit()
    $err=$errTask.Result
    "cli $($a -join ' ') -> exit $($p.ExitCode)"
    if($p.ExitCode -ne 0){ ($out+$err).Trim() | Select-Object -Last 30; throw "cli failed: $($a -join ' ')" }
}
function SwapMod([string]$source){
    Invoke-WhCli @('mod','disable',$mediaId); Invoke-WhCli @('mod','disable',$sysId)
    Copy-Item $source $srcLive -Force
    try { Invoke-WhCli @('mod','compile',$sysId) }
    finally { Invoke-WhCli @('mod','enable',$sysId); Invoke-WhCli @('mod','enable',$mediaId) }
}

if($Action -eq 'Rollback'){
    & reg.exe import "$bk\styler.reg" | Out-Null
    & reg.exe import "$bk\spacing.reg" | Out-Null
    Bump $sty; Bump $spc
    SwapMod "$bk\sysinfo-1.4.29.wh.cpp"
    'rolled back'; return
}

$explorerBefore=(Get-Process explorer -EA SilentlyContinue | Select-Object -Expand Id) -join ','
"explorer pids before: $explorerBefore"

# 1. Mod 1.4.30
SwapMod "$work\sysinfo-1.4.30.wh.cpp"
"sysinfo now: " + (Get-ItemProperty "$k\$sysId").LibraryFileName

# 2. Styler settings
$S="$sty\Settings"
function Set1($name,$expectPrefix,$value){
    $cur=(Get-ItemProperty $S).$name
    if($null -eq $cur -or -not $cur.StartsWith($expectPrefix)){ throw "$name is '$cur', expected $expectPrefix" }
    Set-ItemProperty $S $name $value; "$name : $cur -> $value" }
$grey='BorderBrush:=<LinearGradientBrush StartPoint="0,0.5" EndPoint="1,0.5"><GradientStop Color="#E645475A" Offset="0"/><GradientStop Color="#E645475A" Offset="1"/></LinearGradientBrush>'
Set1 'controlStyles[13].styles[4]' 'BorderBrush' $grey
Set1 'controlStyles[14].styles[4]' 'BorderBrush' $grey
Set1 'controlStyles[15].styles[4]' 'BorderBrush' $grey
Set1 'controlStyles[16].styles[5]' 'BorderBrush' $grey

$t17=(Get-ItemProperty $S).'controlStyles[17].target'
$parts=$t17 -split ',\s*'
$tray=$parts | Where-Object { $_ -notmatch 'AugmentedEntryPointButton' }
$aug=$parts | Where-Object { $_ -match 'AugmentedEntryPointButton' }
if($tray.Count -ne 4 -or $aug.Count -ne 2){ throw "rule 17 target unexpected: $t17" }
Set-ItemProperty $S 'controlStyles[17].target' ($tray -join ', ')
Set1 'controlStyles[17].styles[0]' 'Margin' 'Margin=1'
if((Get-ItemProperty $S).'controlStyles[62].target'){ throw 'rule 62 already exists' }
Set-ItemProperty $S 'controlStyles[62].target' ($aug -join ', ')
Set-ItemProperty $S 'controlStyles[62].styles[0]' 'Margin=2'
Set-ItemProperty $S 'controlStyles[62].styles[1]' 'CornerRadius=8'
Set-ItemProperty $S 'controlStyles[62].styles[2]' 'BorderThickness=0'
'rule 17 split -> 62 (AugmentedEntryPoint keeps Margin 2)'

Set1 'controlStyles[52].styles[0]' 'Height' 'Height=28'

if((Get-ItemProperty $S).'controlStyles[63].target'){ throw 'rule 63 already exists' }
$bt='StackPanel#LogitechBatteryTray > Button > ContentPresenter#ContentPresenter > Viewbox > StackPanel > Windows.UI.Xaml.Controls.FontIcon, StackPanel#LogitechBatteryTray > Button > ContentPresenter#ContentPresenter > Viewbox > Border > StackPanel > Windows.UI.Xaml.Controls.FontIcon'
Set-ItemProperty $S 'controlStyles[63].target' $bt
Set-ItemProperty $S 'controlStyles[63].styles[0]' ('Glyph=' + [char]0xE962)
'rule 63 battery mouse glyph added'

$curW=(Get-ItemProperty "$spc\Settings").notificationIconWidth
Set-ItemProperty "$spc\Settings" notificationIconWidth 28 -Type DWord
"icon spacing width: $curW -> 28"

Bump $sty; Bump $spc
Start-Sleep -Seconds 4
$explorerAfter=(Get-Process explorer -EA SilentlyContinue | Select-Object -Expand Id) -join ','
"explorer pids after: $explorerAfter"
'applied'
