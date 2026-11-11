# Seamless Crash Watch (local@seamless-crash-watch): install, audit or roll back. Run elevated.
#   -Audit     show the mod's engine key and host process
#   -Install   install from the build, enabled, then confirm the host runs
#   -Rollback  disable and remove the mod
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Continue'
$id = 'local@seamless-crash-watch'
$src = 'H:\Windhawk Configuration\work\2026-11-11-crash-toast\build\seamless-crash-watch.wh.cpp'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$stamp = Get-Date -Format 'yyyyMMdd-HHmm'
$log = "H:\Windhawk Configuration\reports\$((Get-Date).ToString('yyyy-MM-dd'))-seamless-crash-watch-$stamp.log"
Start-Transcript -Path $log -Force | Out-Null

function Show-State {
    if (Test-Path $key) { Get-ItemProperty $key | Select-Object Version, Disabled, LibraryFileName | Format-List | Out-String | Write-Output }
    else { Write-Output 'mod key: not present' }
    @(Get-CimInstance Win32_Process -Filter "Name='windhawk-mod.exe'" | Where-Object { $_.CommandLine -like '*seamless-crash-watch*' }) |
        Select-Object ProcessId, CreationDate | Format-List | Out-String | Write-Output
}

if ($Install) {
    if (Test-Path $key) {
        $bak = "H:\Windhawk Configuration\backups\$id-$stamp.reg"
        reg export ($key -replace 'HKLM:', 'HKLM') $bak /y | Out-Null
        Write-Output "backup: $bak"
    }
    & $cli mod install --file $src --yes 2>&1 | Out-String | Write-Output
    Write-Output "cli exit: $LASTEXITCODE"
    & 'H:\Windhawk Configuration\scripts\2026-11-10-tool-mod-restart.ps1' -Id $id 2>&1 | Out-String | Write-Output
}
if ($Rollback) {
    & $cli mod disable $id 2>&1 | Out-String | Write-Output
    & $cli mod uninstall $id --yes 2>&1 | Out-String | Write-Output
}
Show-State
Stop-Transcript | Out-Null
