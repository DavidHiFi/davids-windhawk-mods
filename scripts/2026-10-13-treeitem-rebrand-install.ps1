# Explorer TreeItem Tweaker Plus 1.1.3: GetThemeClass rebrand (persistent fix).
#
# 1.1.2 hooked DrawThemeBackground 3 s after start to end up outermost, but
# translucent-windows hooks DrawThemeBackground in Wh_ModInit and re-hooks on
# every settings change or update, so a cold boot or any translucent reload put
# translucent outermost: it painted the tree items and the fork never saw the
# TVP_TREEITEM draws. 1.1.3 also hooks GetThemeClass (uxtheme ordinal 74) at
# init and answers "Explorer::TreeView" instead of "TreeView", the exact string
# translucent-windows 1.8.x checks before swallowing tree draws. That is
# order-independent, so the pill survives boots and translucent reloads.
# See notes\2026-10-13-treeitem-rebrand.md.
#
#   -Install    back up key + current source, install 1.1.3 from the staged
#               source, verify LibraryFileName, write a receipt
#   -Rollback   reinstall the backed-up 1.1.2 source
#   (no switch) print current state
#
# Run elevated through H:\System Configuration\scripts\Invoke-Elevated.ps1:
#   Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-13-treeitem-rebrand-install.ps1" -ArgumentList "-Install"

param(
    [switch]$Install,
    [switch]$Rollback
)

$ErrorActionPreference = 'Continue'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$modsRoot = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$forkId = 'local@explorer-treeitem-tweaker-plus'
$origId = 'explorer-treeitem-tweaker'
$ws = 'H:\Windhawk Configuration'
$forkDir = "$ws\Windhawk\explorer-treeitem-tweaker-plus"
$forkSource = "$forkDir\local@explorer-treeitem-tweaker-plus.wh.cpp"
$stageSource = "$ws\local@explorer-treeitem-tweaker-plus_v1.1.3.wh.cpp"
$backupDir = "$ws\backups\2026-10-13-treeitem-rebrand"
$backupSource = "$backupDir\local@explorer-treeitem-tweaker-plus_v1.1.2.wh.cpp"
$backupKey = "$backupDir\fork-key-before.reg"
$receipt = "$backupDir\receipt.json"
$thisScript = "$ws\scripts\2026-10-13-treeitem-rebrand-install.ps1"

function Set-ChangeTime([string]$keyPath) {
    $now = [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    reg add $keyPath /v SettingsChangeTime /t REG_DWORD /d $now /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "could not bump SettingsChangeTime on $keyPath" }
}

function Get-LibraryFileName([string]$id) {
    $k = "$modsRoot\$id"
    if (-not (Test-Path ($k -replace '^HKLM\\', 'HKLM:'))) { return '(no key)' }
    (Get-ItemProperty -Path ($k -replace '^HKLM\\', 'HKLM:') -Name LibraryFileName -ErrorAction SilentlyContinue).LibraryFileName
}

function Get-Disabled([string]$id) {
    $k = "$modsRoot\$id"
    if (-not (Test-Path ($k -replace '^HKLM\\', 'HKLM:'))) { return 'no-key' }
    $v = (Get-ItemProperty -Path ($k -replace '^HKLM\\', 'HKLM:') -Name Disabled -ErrorAction SilentlyContinue).Disabled
    if ($v) { 'disabled' } else { 'enabled' }
}

function Show-State {
    "state $forkId : $(Get-Disabled $forkId) | $(Get-LibraryFileName $forkId)"
    "state $origId : $(Get-Disabled $origId) | $(Get-LibraryFileName $origId)"
    "state translucent-windows : $(Get-Disabled 'translucent-windows') | $(Get-LibraryFileName 'translucent-windows')"
}

if ($Install) {
    if (-not (Test-Path $stageSource)) { throw "staged 1.1.3 source missing: $stageSource" }
    if (-not (Test-Path $forkSource)) { throw "current fork source missing: $forkSource" }
    New-Item -ItemType Directory -Force -Path $backupDir | Out-Null

    reg export "$modsRoot\$forkId" $backupKey /y | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg export of fork key failed ($LASTEXITCODE)" }
    Copy-Item $forkSource $backupSource -Force

    & $cli mod install --file $stageSource --yes
    if ($LASTEXITCODE -ne 0) { throw "mod install --file failed ($LASTEXITCODE)" }

    $lib = Get-LibraryFileName $forkId
    if ($lib -notmatch '1\.1\.3') { throw "LibraryFileName did not move to a 1.1.3 revision (got: $lib)" }
    Set-ChangeTime "$modsRoot\$forkId"

    Copy-Item $stageSource $forkSource -Force
    Copy-Item $PSCommandPath $thisScript -Force

    $r = [ordered]@{
        date          = (Get-Date).ToString('yyyy-MM-dd HH:mm:ss')
        mod           = $forkId
        fromVersion   = '1.1.2'
        toVersion     = '1.1.3'
        change        = 'GetThemeClass (ordinal 74) hooked at init; TreeView rebranded to Explorer::TreeView so translucent-windows passes tree draws through'
        sourceStaged  = $stageSource
        sourceUpdated = $forkSource
        previousSource = $backupSource
        keyBackup     = $backupKey
        rollback      = 'Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-13-treeitem-rebrand-install.ps1" -ArgumentList "-Rollback"'
    }
    $r | ConvertTo-Json | Set-Content -Path $receipt -Encoding UTF8
    "installed: $forkId 1.1.3; key backup $backupKey; receipt $receipt"
    Show-State
}

if ($Rollback) {
    if (-not (Test-Path $backupSource)) { throw "backed-up 1.1.2 source missing: $backupSource" }
    & $cli mod install --file $backupSource --yes
    if ($LASTEXITCODE -ne 0) { throw "mod install --file (rollback) failed ($LASTEXITCODE)" }
    Set-ChangeTime "$modsRoot\$forkId"
    Copy-Item $backupSource $forkSource -Force
    "rolled back: $forkId restored to 1.1.2 from $backupSource"
    Show-State
}

if (-not $Install -and -not $Rollback) { Show-State }
