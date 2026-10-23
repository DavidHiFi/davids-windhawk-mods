<#
.SYNOPSIS
Starts the Windhawk alpha.7 update (or its rollback) elevated and detached, then polls the
phase log until a marker appears. Run from a non-elevated shell, under coop lock windhawk-engine.

The update waits for T3 Code to close before it stops the engine, so the poll can sit for hours.

Exit codes: 0 complete, 2 failed, 3 not run (cancelled or T3 Code stayed open), 4 still running at the poll limit.
#>
param(
    [ValidateSet('Install', 'Rollback')][string]$Phase = 'Install',
    [int]$PollSeconds = 21600
)

$ErrorActionPreference = 'Stop'
$script   = 'H:\Windhawk Configuration\scripts\2026-10-11-windhawk-2a7-update.ps1'
$phaseLog = 'H:\Windhawk Configuration\backups\2026-10-11\windhawk-2a7-update\phase-log.txt'

Remove-Item Env:ELECTRON_RUN_AS_NODE -ErrorAction SilentlyContinue
$startLine = if (Test-Path $phaseLog) { @(Get-Content $phaseLog).Count } else { 0 }
$argLine = '-NoProfile -ExecutionPolicy Bypass -File "{0}" -{1}' -f $script, $Phase
Start-Process powershell.exe -ArgumentList $argLine -Verb RunAs -WindowStyle Hidden | Out-Null
"launched $Phase elevated and detached; polling $phaseLog"

$deadline = (Get-Date).AddSeconds($PollSeconds)
while ((Get-Date) -lt $deadline) {
    Start-Sleep -Seconds 5
    $new = if (Test-Path $phaseLog) { @(Get-Content $phaseLog | Select-Object -Skip $startLine) -join "`n" } else { '' }
    if ($new -match 'install-complete|rollback-complete') { 'COMPLETE'; $new; exit 0 }
    if ($new -match 'install-failed|rollback-failed') { 'FAILED - read the *-error.txt in the backup folder'; $new; exit 2 }
    if ($new -match 'install-cancelled|install-timeout') { 'NOT RUN'; $new; exit 3 }
}
'STILL RUNNING - waiting on T3 Code or a slow install; keep reading phase-log.txt'
exit 4
