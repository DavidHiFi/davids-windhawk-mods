# Deploy Windhawk Styler 2.0.69 (true save-bar blur: opaque rounded patch under the bar, bar at normal card opacity). Run elevated.
# -Install deploys .tmp\styler-2.0.69; -Rollback restores the mod key and source saved before the install (2.0.68).
param([switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$Version = '2.0.69'
$key = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$ps = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$bk = 'H:\Windhawk Configuration\backups\2026-10-24\styler-blur'
$stage = "H:\Windhawk Configuration\.tmp\styler-$Version"
$src = 'H:\Windhawk Configuration\work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp'
$modsSource = 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp'
$lib = "local@windhawk-styler_${Version}_1.dll"
$now = [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
if ($Install) {
    if (-not (Test-Path "$bk\mod-key-before-2.0.69.reg")) {
        reg export $key "$bk\mod-key-before-2.0.69.reg" /y | Out-Null
        Copy-Item $modsSource "$bk\ModsSource-before-2.0.69.wh.cpp" -Force
    }
    Copy-Item "$stage\windhawk-styler-64.dll" "C:\ProgramData\Windhawk\Engine\Mods\64\$lib" -Force
    Copy-Item "$stage\windhawk-styler-32.dll" "C:\ProgramData\Windhawk\Engine\Mods\32\$lib" -Force
    Copy-Item $src $modsSource -Force
    Set-ItemProperty $ps LibraryFileName $lib
    Set-ItemProperty $ps Version $Version
    Set-ItemProperty $ps SettingsChangeTime $now -Type DWord
}
if ($Rollback) {
    reg import "$bk\mod-key-before-2.0.69.reg"
    Copy-Item "$bk\ModsSource-before-2.0.69.wh.cpp" $modsSource -Force
    Set-ItemProperty $ps SettingsChangeTime $now -Type DWord
}
Get-ItemProperty $ps | Select-Object LibraryFileName, Version, SettingsChangeTime | Format-List
Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$((Get-ItemProperty $ps).LibraryFileName)" -ErrorAction SilentlyContinue | Select-Object Hash
