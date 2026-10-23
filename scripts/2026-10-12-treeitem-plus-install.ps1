# Installs "Explorer TreeItem Tweaker Plus" (local fork of explorer-treeitem-tweaker 1.1.1)
# and disables the original so only one copy draws the tree items.
#
# The fork moves its DrawThemeBackground / GetThemeColor / DrawThemeTextEx hooks
# from Wh_ModInit to 3 seconds after start. translucent-windows paints TreeView
# items itself, and whichever DrawThemeBackground hook is outermost wins. Hooks set
# at init follow load order, so the original loses to translucent-windows whenever
# it loads first. See notes\2026-10-12-treeitem-hook-conflict.md.
#
#   -Install   back up the original key, disable it, install the fork from source,
#              copy the original's Settings into the fork, and write a receipt.
#   -Rollback  disable the fork and re-enable the original. The fork stays installed.
#
# Run elevated through H:\System Configuration\scripts\Invoke-Elevated.ps1:
#   Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-12-treeitem-plus-install.ps1" -ArgumentList "-Install"

param(
    [switch]$Install,
    [switch]$Rollback
)

# The CLI writes progress to stderr ("Compiling for x64..."). Under Stop that line
# becomes a terminating error, so native calls are checked through $LASTEXITCODE.
$ErrorActionPreference = 'Continue'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$modsRoot = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$origId = 'explorer-treeitem-tweaker'
$forkId = 'local@explorer-treeitem-tweaker-plus'
$forkSource = 'H:\Windhawk Configuration\Windhawk\explorer-treeitem-tweaker-plus\local@explorer-treeitem-tweaker-plus.wh.cpp'
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-12-treeitem'
$origBackup = Join-Path $backupDir 'explorer-treeitem-tweaker-before.reg'
$receipt = Join-Path $backupDir 'treeitem-plus-receipt.json'

if (-not (Test-Path $backupDir)) { New-Item -ItemType Directory -Path $backupDir | Out-Null }

function Set-ChangeTime([string]$keyPath) {
    $now = [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    reg add $keyPath /v SettingsChangeTime /t REG_DWORD /d $now /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "could not bump SettingsChangeTime on $keyPath" }
}

if ($Install) {
    if (-not (Test-Path $forkSource)) { throw "fork source missing: $forkSource" }

    if (-not (Test-Path $origBackup)) {
        reg export "$modsRoot\$origId" $origBackup /y | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "reg export of original failed ($LASTEXITCODE)" }
    }

    & $cli mod disable $origId --quiet
    if ($LASTEXITCODE -ne 0) { throw "mod disable $origId failed ($LASTEXITCODE)" }

    & $cli mod install --file $forkSource --yes
    if ($LASTEXITCODE -ne 0) { throw "mod install --file failed ($LASTEXITCODE)" }

    $forkKey = "$modsRoot\$forkId"
    if (-not (reg query $forkKey 2>$null)) { throw "fork key $forkKey not created by the CLI" }

    reg delete "$forkKey\Settings" /f 2>$null | Out-Null
    reg copy "$modsRoot\$origId\Settings" "$forkKey\Settings" /s /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "could not copy Settings to $forkKey" }
    Set-ChangeTime $forkKey

    $r = [ordered]@{
        date = (Get-Date).ToString('yyyy-MM-dd HH:mm:ss')
        original = $origId
        fork = $forkId
        forkSource = $forkSource
        originalBackup = $origBackup
        rollback = 'Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-12-treeitem-plus-install.ps1" -ArgumentList "-Rollback"'
    }
    $r | ConvertTo-Json | Set-Content -Path $receipt -Encoding UTF8
    "installed: $forkId; original $origId disabled; receipt $receipt"
}

if ($Rollback) {
    & $cli mod disable $forkId --quiet
    if ($LASTEXITCODE -ne 0) { throw "mod disable $forkId failed ($LASTEXITCODE)" }
    & $cli mod enable $origId --quiet
    if ($LASTEXITCODE -ne 0) { throw "mod enable $origId failed ($LASTEXITCODE)" }
    "rolled back: $forkId disabled, $origId enabled"
}

foreach ($id in $origId, $forkId) {
    $k = "$modsRoot\$id"
    if (-not (reg query $k 2>$null)) {
        "state ${id}: no registry key"
        continue
    }
    # A missing Disabled value means enabled.
    $disabled = (Get-ItemProperty -Path ($k -replace '^HKLM\\', 'HKLM:\') -Name Disabled -ErrorAction SilentlyContinue).Disabled
    $lib = (Get-ItemProperty -Path ($k -replace '^HKLM\\', 'HKLM:\') -Name LibraryFileName).LibraryFileName
    "state ${id}: $(if ($disabled) { 'disabled' } else { 'enabled' }) | $lib"
}
