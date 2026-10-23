<#
.SYNOPSIS
    Installs Explorer TreeItem Tweaker Plus 1.1.5 (restart-without-asking switch) or rolls back to 1.1.4.
.EXAMPLE
    .\2026-10-24-treeitem-restart-toggle-install.ps1 -Audit
    .\2026-10-24-treeitem-restart-toggle-install.ps1 -Install
    .\2026-10-24-treeitem-restart-toggle-install.ps1 -Rollback
#>
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$id = 'local@explorer-treeitem-tweaker-plus'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$ws = 'H:\Windhawk Configuration'
$work = "$ws\work\2026-10-24-treeitem-restart-toggle"
$stage = "$work\explorer-treeitem-tweaker-plus.wh.cpp"
$before = "$work\explorer-treeitem-tweaker-plus.before-1.1.4.wh.cpp"
$forkSource = "$ws\Windhawk\explorer-treeitem-tweaker-plus\$id.wh.cpp"
$backupDir = "$ws\backups\2026-10-24-treeitem-restart-toggle"

function Show-State {
    $p = Get-ItemProperty $key
    $s = Get-ItemProperty "$key\Settings" -ErrorAction SilentlyContinue
    "version $($p.Version) | $($p.LibraryFileName) | Disabled=$($p.Disabled) | RestartExplorerWithoutAsking=$($s.'Global.RestartExplorerWithoutAsking')"
}

if ($Audit) { Show-State }

if ($Install) {
    New-Item -ItemType Directory -Force -Path $backupDir | Out-Null
    reg export ($key -replace '^HKLM:', 'HKLM') "$backupDir\mod-key-before.reg" /y | Out-Null
    if (Test-Path $forkSource) { Copy-Item $forkSource "$backupDir\fork-source-before.wh.cpp" -Force }
    & $cli mod install --file $stage --yes
    if ($LASTEXITCODE -ne 0) { throw "mod install failed ($LASTEXITCODE)" }
    # Keep today's behaviour (no popup) if the engine did not write the new setting's default.
    $s = Get-ItemProperty "$key\Settings" -ErrorAction SilentlyContinue
    if ($null -eq $s.'Global.RestartExplorerWithoutAsking') {
        New-ItemProperty "$key\Settings" -Name 'Global.RestartExplorerWithoutAsking' -PropertyType DWord -Value 1 -Force | Out-Null
    }
    Copy-Item $stage $forkSource -Force
    [ordered]@{ date = (Get-Date).ToString('yyyy-MM-dd h:mm:ss tt'); mod = $id; from = '1.1.4'; to = '1.1.5'
        change = 'Restart Explorer without asking switch; off brings back the original prompt'; rollback = "$PSCommandPath -Rollback" } |
        ConvertTo-Json | Set-Content "$backupDir\receipt.json"
    Show-State
}

if ($Rollback) {
    & $cli mod install --file $before --yes
    if ($LASTEXITCODE -ne 0) { throw "rollback install failed ($LASTEXITCODE)" }
    Copy-Item $before $forkSource -Force
    Show-State
}
