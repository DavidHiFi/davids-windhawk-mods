<#
.SYNOPSIS
  Copies the polished window-manager source from the snapshot repo into the
  live Windhawk ModsSource so the readme Windhawk shows matches what was
  published. Documentation text only: no code, no DLL, no registry change.

  -Audit     Read-only. Prints both hashes and whether they match.
  -Install   Needs admin. Backs up the live file, copies the repo file over it
             and verifies the hash.
  -Rollback  Needs admin. Restores the backed-up live file.
#>
[CmdletBinding()]
param([switch]$Audit, [switch]$Install, [switch]$Rollback,
      [string]$LogPath)
$ErrorActionPreference = 'Stop'
if ($LogPath) { Start-Transcript -Path $LogPath -Force | Out-Null }

$root    = Split-Path $PSScriptRoot -Parent
$repo    = Join-Path $root 'davids-windhawk-mods\mods\local\window-manager\window-manager.wh.cpp'
$live    = 'C:\ProgramData\Windhawk\ModsSource\local@window-manager.wh.cpp'
$backup  = Join-Path $root 'backups\2026-10-04\mod-polish-final\local@window-manager.wh.cpp'
$report  = Join-Path $root 'reports\2026-10-04-mod-metadata-polish\receipt-wm-readme-sync.json'
$hash    = { param($p) (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

if (-not (Test-Path -LiteralPath $repo)) { throw "Missing repo source: $repo" }
if (-not (Test-Path -LiteralPath $live)) { throw "Missing live source: $live" }
$repoHash = & $hash $repo
$liveHash = & $hash $live

if ($Audit) {
    [pscustomobject]@{
        repo    = $repo; repoSha256 = $repoHash
        live    = $live; liveSha256 = $liveHash
        match   = ($repoHash -eq $liveHash)
    } | ConvertTo-Json -Depth 4
    return
}

if ($Rollback) {
    if (-not (Test-Path -LiteralPath $backup)) { throw "No backup at $backup" }
    Copy-Item -LiteralPath $backup -Destination $live -Force
    [pscustomobject]@{ restored = $live; sha256 = (& $hash $live); backup = $backup } |
        ConvertTo-Json | Set-Content -LiteralPath $report
    Get-Content -LiteralPath $report
    return
}

if ($Install) {
    if ($repoHash -eq $liveHash) {
        [pscustomobject]@{ applied = $false; reason = 'already matching'; sha256 = $liveHash } |
            ConvertTo-Json | Set-Content -LiteralPath $report
        Get-Content -LiteralPath $report
        return
    }
    New-Item -ItemType Directory -Path (Split-Path $backup -Parent) -Force | Out-Null
    if (-not (Test-Path -LiteralPath $backup)) {
        Copy-Item -LiteralPath $live -Destination $backup
    }
    Copy-Item -LiteralPath $repo -Destination $live -Force
    $after = & $hash $live
    if ($after -ne $repoHash) { throw "Hash after copy ($after) does not match repo ($repoHash)" }
    [pscustomobject]@{
        applied = $true; live = $live; sha256 = $after
        backup = $backup; backupSha256 = (& $hash $backup)
    } | ConvertTo-Json | Set-Content -LiteralPath $report
    Get-Content -LiteralPath $report
    return
}

throw 'Pass -Audit, -Install or -Rollback.'
