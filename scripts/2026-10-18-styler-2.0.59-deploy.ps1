# Deploy a Windhawk Styler build (2.0.59+: caption buttons drawn at full brightness, DWM hover when maximized).
# -Install -Version x deploys .tmp\styler-x; -Rollback restores the mod key backed up before the first install (2.0.58).
param([switch]$Install, [switch]$Rollback, [string]$Version = '2.0.59')
$ErrorActionPreference = 'Stop'
$key = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$ps = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$bk = 'H:\Windhawk Configuration\backups\2026-10-18\styler-2.0.59'
$stage = "H:\Windhawk Configuration\.tmp\styler-$Version"
$src = 'H:\Windhawk Configuration\work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp'
$modsSource = 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp'
$lib = "local@windhawk-styler_${Version}_1.dll"
$now = [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
if ($Install) {
    if (-not (Test-Path "$bk\mod-key-before.reg")) {
        reg export $key "$bk\mod-key-before.reg" /y | Out-Null
        Copy-Item $modsSource "$bk\ModsSource-before.wh.cpp" -Force
    }
    Copy-Item "$stage\windhawk-styler-64.dll" "C:\ProgramData\Windhawk\Engine\Mods\64\$lib" -Force
    Copy-Item "$stage\windhawk-styler-32.dll" "C:\ProgramData\Windhawk\Engine\Mods\32\$lib" -Force
    Copy-Item $src $modsSource -Force
    Set-ItemProperty $ps LibraryFileName $lib
    Set-ItemProperty $ps Version $Version
    Set-ItemProperty $ps SettingsChangeTime $now -Type DWord
}
if ($Rollback) {
    reg import "$bk\mod-key-before.reg"
    Copy-Item "$bk\ModsSource-before.wh.cpp" $modsSource -Force
    Set-ItemProperty $ps SettingsChangeTime $now -Type DWord
}
Get-ItemProperty $ps | Select-Object LibraryFileName, Version, SettingsChangeTime | Format-List
Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$((Get-ItemProperty $ps).LibraryFileName)" -ErrorAction SilentlyContinue | Select-Object Hash
