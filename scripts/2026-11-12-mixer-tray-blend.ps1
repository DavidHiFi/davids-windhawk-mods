param([ValidateSet('Apply','Rollback')][string]$Action='Apply')
# 2026-11-12: mixer tray number blends with the tray. Run ELEVATED.
# - Mixer 1.4.20 -> 1.4.22 (1.4.21 was the first try): the tray tooltip shows its name (NIF_SHOWTIP, kept on every icon
#   update) instead of an empty bubble; the number's ink sits 4 px left of the speaker's, and
#   a wide "100" is kept inside the slot's hover box.
# - Styler rule 64: speaker slot 52 -> 47 px wide, so the gap from Fan Control's ink to the
#   number is ~15 px like the other icons, and a 3-digit "100" still fits the hover box.
# Rollback: rule 64 back to Width=52, mixer 1.4.20 reinstalled from the work folder.
$ErrorActionPreference='Stop'
trap { "ERROR: $_ (line $($_.InvocationInfo.ScriptLineNumber))"; exit 1 }
$work='H:\Windhawk Configuration\work\2026-11-12-mixer-tray-blend'
$sty='HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'; $S="$sty\Settings"
$id='local@better-volume-mixer-plus'
$srcLive="C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$installer='H:\Windhawk Configuration\scripts\Install-StagedMod.ps1'
$r64='SystemTray.NotifyIconView#NotifyItemIcon[AutomationProperties.Name=Seamless Volume Mixer]'
function Update-StylerTime { Set-ItemProperty $sty SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord }
function Set-Width([int]$w){
    if((Get-ItemProperty $S).'controlStyles[64].target' -ne $r64){ throw 'rule 64 is not the mixer rule' }
    Set-ItemProperty $S -Name 'controlStyles[64].styles[0]' -Value "Width=$w"
}
function Install-Source([string]$staged){
    $hash=(Get-FileHash $srcLive -Algorithm SHA256).Hash
    if($Action -eq 'Apply'){ $hash=(Get-Content "$work\base.sha256" -Raw).Trim() }
    & $installer -Id $id -Staged $staged -BaseHash $hash
    if($LASTEXITCODE -ne 0){ throw "install refused, exit $LASTEXITCODE" }
    # A tool mod compile can leave its process stopped (the 1.4.22 install did): restart it.
    Start-Sleep -Seconds 3
    $up=Get-CimInstance Win32_Process -Filter "Name='windhawk-mod.exe'" | Where-Object { $_.CommandLine -match 'volume-mixer' }
    if(-not $up){
        $cli='C:\Program Files\Windhawk\windhawk-cli.exe'
        & $cli mod disable $id | Out-Null; Start-Sleep -Seconds 3; & $cli mod enable $id | Out-Null
        'mixer process restarted'
    }
}
if($Action -eq 'Apply'){
    $now=(Get-FileHash $srcLive -Algorithm SHA256).Hash
    if($now -ne (Get-Content "$work\base.sha256" -Raw).Trim()){ 'live source CHANGED since staging, nothing done'; exit 2 }
    $stamp=Get-Date -Format 'yyyyMMdd-HHmm'
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' "$work\styler.reg.bak-$stamp" /y | Out-Null
    Set-Width 47; Update-StylerTime; 'rule 64 Width=47'
    Install-Source "$work\better-volume-mixer-plus-1.4.22.wh.cpp"
} else {
    Set-Width 52; Update-StylerTime; 'rule 64 Width=52'
    Install-Source "$work\base-1.4.20.wh.cpp"
}
# The mixer re-adds its tray icon on reload; the styler only restyles that fresh icon after a
# second bump (2026-11-12).
Start-Sleep -Seconds 4; Update-StylerTime
"$Action done"
