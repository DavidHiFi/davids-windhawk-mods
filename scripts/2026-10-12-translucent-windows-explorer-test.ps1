# A/B test for the Explorer TreeItem Tweaker conflict with translucent-windows.
#
# translucent-windows 1.8.2 paints TreeView items itself (PaintTreeViewButton) and
# returns without calling the original DrawThemeBackground. When its hook sits
# outside explorer-treeitem-tweaker's hook, the tweaker never draws its rounded
# hover and selected backgrounds. -Apply adds explorer.exe to translucent-windows'
# Exclude list for the test only. -Rollback restores the exported key exactly.
#
# Run elevated through H:\System Configuration\scripts\Invoke-Elevated.ps1:
#   Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-12-translucent-windows-explorer-test.ps1" -ArgumentList "-Apply"
#   Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-12-translucent-windows-explorer-test.ps1" -ArgumentList "-Rollback"

param(
    [switch]$Apply,
    [switch]$Rollback
)

$ErrorActionPreference = 'Stop'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'
$regKey = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-12-treeitem'
$backupFile = Join-Path $backupDir 'translucent-windows-before-test.reg'

if (-not (Test-Path $backupDir)) { New-Item -ItemType Directory -Path $backupDir | Out-Null }

function Get-ExcludeValue { (Get-ItemProperty -Path $key -Name Exclude).Exclude }

if ($Apply) {
    if (-not (Test-Path $backupFile)) {
        reg export $regKey $backupFile /y | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "reg export failed with $LASTEXITCODE" }
    }
    Set-ItemProperty -Path $key -Name Exclude -Value 'explorer.exe' -Type String
    Set-ItemProperty -Path $key -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
    "applied: Exclude='$(Get-ExcludeValue)'"
}

if ($Rollback) {
    if (-not (Test-Path $backupFile)) { throw "no backup at $backupFile, nothing to restore" }
    reg import $backupFile | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg import failed with $LASTEXITCODE" }
    Set-ItemProperty -Path $key -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
    "rolled back: Exclude='$(Get-ExcludeValue)'"
}

if (-not $Apply -and -not $Rollback) {
    "state: Exclude='$(Get-ExcludeValue)' Disabled=$((Get-ItemProperty -Path $key -Name Disabled).Disabled) LibraryFileName=$((Get-ItemProperty -Path $key -Name LibraryFileName).LibraryFileName)"
}
