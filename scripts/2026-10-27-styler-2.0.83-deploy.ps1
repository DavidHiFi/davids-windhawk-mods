# 2026-10-27: Windhawk Styler 2.0.83, centered title (centerTitle=1) to match Caption Buttons Customizer. Run elevated.
# Build first: 2026-10-27-styler-2.0.80-build.ps1. Rollback: -Rollback restores the 2.0.82 key and source (its DLL stays in place).
param([switch]$Rollback)
$ErrorActionPreference = 'Continue'
$Version = '2.0.83'
$key = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$ps = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$bk = 'H:\Windhawk Configuration\backups\2026-10-27\styler-2.0.83'
$stage = "H:\Windhawk Configuration\.tmp\styler-$Version"
$src = 'H:\Windhawk Configuration\work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp'
$modsSource = 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp'
$lib = "local@windhawk-styler_${Version}_1.dll"
New-Item -ItemType Directory -Force $bk | Out-Null
$log = Join-Path $bk 'deploy-log.txt'
$now = [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
& {
    if ($Rollback) {
        reg import "$bk\styler-key-before.reg" 2>&1
        Copy-Item "$bk\ModsSource-before.wh.cpp" $modsSource -Force
    } else {
        New-Item -ItemType Directory -Force $bk | Out-Null; reg export $key "$bk\styler-key-before.reg" /y; Copy-Item $modsSource "$bk\ModsSource-before.wh.cpp" -Force
        if (-not (Test-Path "$bk\styler-key-before.reg")) { 'NO BACKUP, abort'; return }
        Set-ItemProperty "$ps\Settings" centerTitle 1 -Type DWord
        Copy-Item "$stage\windhawk-styler-64.dll" "C:\ProgramData\Windhawk\Engine\Mods\64\$lib" -Force
        Copy-Item "$stage\windhawk-styler-32.dll" "C:\ProgramData\Windhawk\Engine\Mods\32\$lib" -Force
        Copy-Item $src $modsSource -Force
        Set-ItemProperty $ps LibraryFileName $lib
        Set-ItemProperty $ps Version $Version
    }
    Set-ItemProperty $ps SettingsChangeTime $now -Type DWord
    Get-ItemProperty $ps | Select-Object Version, LibraryFileName, SettingsChangeTime | Format-List | Out-String
    $l = (Get-ItemProperty $ps).LibraryFileName
    "dll64 " + (Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$l").Hash
    "dll32 " + (Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\32\$l").Hash
    "modsSource " + (Get-FileHash $modsSource).Hash
    "settings " + ((Get-ItemProperty "$ps\Settings" | Out-String) -replace '\s+', ' ')
} *>&1 | Out-File -Encoding utf8 $log


