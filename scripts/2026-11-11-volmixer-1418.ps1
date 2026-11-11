param([ValidateSet('Apply','Rollback')][string]$Action='Apply')
# 2026-11-11: master volume number missing next to the mixer tray icon. Run ELEVATED.
# - Mixer 1.4.17 -> 1.4.18: TIMER_TRAY_SYNC shared id 4 with TIMER_NAME_TOOLTIP, so the number
#   never moved after its first (empty-rect) placement at -32,-9. Own id 7 now, and an empty
#   rect counts as "no slot". The icon gets a tip name (no NIF_SHOWTIP, so no shell bubble).
# - Styler rule 64: the icon named "Seamless Volume Mixer" gets a left margin, so the number
#   has its own gap instead of covering the icon to its left.
# Tool mod: disable + enable restarts its windhawk-mod.exe. No Explorer restart.
$ErrorActionPreference='Stop'
trap { "ERROR: $_ (line $($_.InvocationInfo.ScriptLineNumber))"; exit 1 }
$bk='H:\Windhawk Configuration\backups\2026-11-11-volmixer-1418'
$work='H:\Windhawk Configuration\work\2026-11-11-tray-hover'
$sty='HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'; $S="$sty\Settings"
$id='local@better-volume-mixer-plus'
$srcLive="C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$cli='C:\Program Files\Windhawk\windhawk-cli.exe'
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
if($Action -eq 'Rollback'){
    & reg.exe import "$bk\styler.reg" | Out-Null
    Remove-ItemProperty $S -Name 'controlStyles[64].target','controlStyles[64].styles[0]' -ErrorAction SilentlyContinue
    Update-StylerTime
    Install-MixerSource "$bk\better-volume-mixer-plus-1.4.17.wh.cpp"
    'rolled back'; return
}
$r64='SystemTray.NotifyIconView#NotifyItemIcon[AutomationProperties.Name=Seamless Volume Mixer]'
$cur=(Get-ItemProperty $S).'controlStyles[64].target'
if($cur -and $cur -ne $r64){ throw "rule 64 is taken: $cur" }
if(-not $cur){
    New-ItemProperty $S -Name 'controlStyles[64].target' -Value $r64 -PropertyType String | Out-Null
    New-ItemProperty $S -Name 'controlStyles[64].styles[0]' -Value 'Margin=30,0,0,0' -PropertyType String | Out-Null
    Update-StylerTime
    'rule 64 added'
} else { 'rule 64 already in place' }
# The 1.4.18 overlay also presents from the DC that holds its bitmap (it was invisible before).
Install-MixerSource "$work\better-volume-mixer-plus-1.4.18.wh.cpp"
'applied'
