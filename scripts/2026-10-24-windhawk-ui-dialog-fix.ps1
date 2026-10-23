<#
Windhawk settings dialog fix, 2026-10-24.
Scope: the Windhawk app's own UI, not a mod. The "More advanced settings" dialog gets:
  1. The process inclusion list and its info box join as one block with square corners.
  2. Scrollbars inside the dialog are slim and stay inside their boxes.
Method: appends one marked CSS block to the installed webview stylesheet. Nothing else changes.
  -Audit     read-only: hashes and whether the block is present (default)
  -Install   backs up the original once, appends the block, reads the bytes back
  -Rollback  restores the original bytes from the backup and reads them back
Program Files is protected, so run elevated:
  Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-24-windhawk-ui-dialog-fix.ps1" -ArgumentList "-Install"
Note: notes\2026-10-24-windhawk-ui-dialog-fix.md
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Install,
    [switch]$Rollback
)

$ErrorActionPreference = 'Stop'
$target = 'C:\Program Files\Windhawk\UI\resources\app\extensions\windhawk\webview\main.d4a0304aa029f0f1.css'
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-24\windhawk-ui-dialog'
$backup = Join-Path $backupDir 'main.d4a0304aa029f0f1.css.orig'
$cssSource = Join-Path $PSScriptRoot '2026-10-24-windhawk-ui-dialog-fix.css'
$originalHash = '9DE12EA8C789C1E98EAA48A97C402FC18419679DC906DC5A2CD6484FA7EAEDFA'
$beginMarker = '/* >>> local dialog fix 2026-10-24 >>> */'
$endMarker = '/* <<< local dialog fix 2026-10-24 <<< */'
$utf8 = New-Object System.Text.UTF8Encoding($false)

function Get-FileSha([string]$path) { (Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash }
function Test-Block([string]$path) { [IO.File]::ReadAllText($path, $utf8).Contains($beginMarker) }
function Save-Receipt([string]$name, [hashtable]$data) {
    $data | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $backupDir $name) -Encoding UTF8
}

if (-not ($Install -or $Rollback)) { $Audit = $true }

if ($Audit) {
    "target:   $target"
    "sha256:   $(Get-FileSha $target)"
    "original: $originalHash"
    "block:    $(Test-Block $target)"
    "backup:   $(Test-Path -LiteralPath $backup)"
    exit 0
}

if ($Install) {
    if (-not (Test-Path -LiteralPath $cssSource)) { throw "Missing CSS source: $cssSource" }
    if (Test-Block $target) { 'Block already present. Nothing to do.'; exit 0 }
    $before = Get-FileSha $target
    if ($before -ne $originalHash) {
        throw "Target hash $before is not the expected original $originalHash. Refusing to edit an unknown file."
    }
    New-Item -ItemType Directory -Force -Path $backupDir | Out-Null
    if (-not (Test-Path -LiteralPath $backup)) { Copy-Item -LiteralPath $target -Destination $backup }
    if ((Get-FileSha $backup) -ne $originalHash) { throw 'Backup hash does not match the original. Stopping.' }

    $css = [IO.File]::ReadAllText($cssSource, $utf8).TrimEnd()
    $block = "`n$beginMarker`n$css`n$endMarker`n"
    $blockBytes = $utf8.GetBytes($block)
    $origBytes = [IO.File]::ReadAllBytes($backup)
    [IO.File]::AppendAllText($target, $block, $utf8)

    $newBytes = [IO.File]::ReadAllBytes($target)
    $prefixOk = $newBytes.Length -eq ($origBytes.Length + $blockBytes.Length)
    for ($i = 0; $prefixOk -and $i -lt $origBytes.Length; $i++) {
        if ($newBytes[$i] -ne $origBytes[$i]) { $prefixOk = $false }
    }
    $after = Get-FileSha $target
    $verified = $prefixOk -and (Test-Block $target)
    Save-Receipt 'receipt.json' @{
        action = 'install'; time = (Get-Date).ToString('yyyy-MM-dd h:mm:ss tt')
        target = $target; sha256_before = $before; sha256_after = $after
        verified = $verified; rollback = '-Rollback (same script, elevated)'
    }
    if (-not $verified) {
        Copy-Item -LiteralPath $backup -Destination $target -Force
        throw 'Verification failed. Original bytes restored from backup.'
    }
    "Installed. sha256 $before -> $after. Block verified: $verified"
    exit 0
}

if ($Rollback) {
    if (-not (Test-Path -LiteralPath $backup)) { throw "No backup at $backup" }
    if ((Get-FileSha $backup) -ne $originalHash) { throw 'Backup hash does not match the original. Not restoring.' }
    if (-not (Test-Block $target)) {
        'Block not present. Nothing restored.'
        exit 0
    }
    Copy-Item -LiteralPath $backup -Destination $target -Force
    $after = Get-FileSha $target
    if ($after -ne $originalHash) { throw "Restore check failed: $after" }
    Save-Receipt 'receipt-rollback.json' @{
        action = 'rollback'; time = (Get-Date).ToString('yyyy-MM-dd h:mm:ss tt')
        target = $target; sha256_after = $after; matches_original = $true
    }
    "Rolled back. sha256 $after matches the original."
    exit 0
}
