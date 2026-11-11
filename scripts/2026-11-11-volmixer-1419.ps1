param([ValidateSet('Apply','Rollback')][string]$Action='Apply')
# 2026-11-12: mixer tray number as part of a real tray icon. Run ELEVATED.
# - Mixer 1.4.18 -> 1.4.19: number 14 -> 12 px; sits inside the speaker's own slot, 3 px left
#   of the glyph; hides whenever anything but the taskbar is on screen at the slot (borderless
#   or fullscreen games), checked on every foreground change and every 500 ms.
# - Styler rule 64: the speaker slot is 52 px wide instead of a 30 px left margin, so the
#   slot's own hover box and click area cover number + speaker. Rule 65 right-aligns the glyph.
# Rollback returns to 1.4.18 + Margin=30 and removes rule 65.
$ErrorActionPreference='Stop'
trap { "ERROR: $_ (line $($_.InvocationInfo.ScriptLineNumber))"; exit 1 }
$bk='H:\Windhawk Configuration\backups\2026-11-11-volmixer-1418'
$work='H:\Windhawk Configuration\work\2026-11-11-tray-hover'
$sty='HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'; $S="$sty\Settings"
$id='local@better-volume-mixer-plus'
$srcLive="C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$cli='C:\Program Files\Windhawk\windhawk-cli.exe'
$r64='SystemTray.NotifyIconView#NotifyItemIcon[AutomationProperties.Name=Seamless Volume Mixer]'
$r65="$r64 > Grid#ContainerGrid > ContentPresenter#ContentPresenter"
function Update-StylerTime { Set-ItemProperty $sty SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord }
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
function Install-MixerSource([string]$source){
    Invoke-WhCli @('mod','disable',$id)
    Copy-Item $source $srcLive -Force
    try { Invoke-WhCli @('mod','compile',$id) }
    finally { Invoke-WhCli @('mod','enable',$id) }
}
function Set-Rule([int]$n,[string]$target,[string[]]$styles){
    $names=(Get-ItemProperty $S).PSObject.Properties.Name | Where-Object { $_.StartsWith("controlStyles[$n].") }
    # Remove-ItemProperty treats [ ] as wildcards and silently deletes nothing; use the raw key.
    $key=[Microsoft.Win32.Registry]::LocalMachine.OpenSubKey('SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings',$true)
    try { foreach($v in $names){ $key.DeleteValue($v) } } finally { $key.Close() }
    if(-not $target){ return }
    New-ItemProperty $S -Name "controlStyles[$n].target" -Value $target -PropertyType String | Out-Null
    for($i=0;$i -lt $styles.Count;$i++){
        New-ItemProperty $S -Name "controlStyles[$n].styles[$i]" -Value $styles[$i] -PropertyType String | Out-Null
    }
}
if((Get-ItemProperty $S).'controlStyles[64].target' -ne $r64){ throw 'rule 64 is not the mixer rule' }
$t65=(Get-ItemProperty $S).'controlStyles[65].target'
if($t65 -and $t65 -ne $r65){ throw "rule 65 is taken: $t65" }
if($Action -eq 'Rollback'){
    Set-Rule 64 $r64 @('Margin=30,0,0,0'); Set-Rule 65 $null @(); Update-StylerTime
    Install-MixerSource "$bk\better-volume-mixer-plus-1.4.18.wh.cpp"
    'rolled back'; return
}
$stamp=Get-Date -Format 'yyyyMMdd-HHmm'
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' "$bk\styler.reg.bak-$stamp" /y | Out-Null
if(-not (Test-Path "$bk\better-volume-mixer-plus-1.4.18.wh.cpp")){ Copy-Item $srcLive "$bk\better-volume-mixer-plus-1.4.18.wh.cpp" }
Set-Rule 64 $r64 @('Width=52')
Set-Rule 65 $r65 @('HorizontalAlignment=Right','Margin=0,0,6,0')
Update-StylerTime; 'styler rules 64 and 65 set'
Install-MixerSource "$work\better-volume-mixer-plus-1.4.19.wh.cpp"
# The mixer re-adds its tray icon on enable; the styler kept the old rule on that fresh icon
# until a second bump (2026-11-12), so bump again once the icon is back.
Start-Sleep -Seconds 3; Update-StylerTime
'applied'
