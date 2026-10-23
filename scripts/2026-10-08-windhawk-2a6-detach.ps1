<#
Spawn the update script DETACHED (elevated, hidden) so no caller timeout can kill it.
Then optionally wait for the completion marker in phase-log.txt (the install keeps
running detached even if this wrapper is killed).
#>
param([ValidateSet('Install','Rollback')][string]$Phase = 'Install')
$script = 'H:\Windhawk Configuration\scripts\2026-10-08-windhawk-2a6-update.ps1'
$argLine = '-NoProfile -ExecutionPolicy Bypass -File "{0}" -{1}' -f $script, $Phase
Start-Process powershell.exe -ArgumentList $argLine -Verb RunAs -WindowStyle Hidden
'detached {0} launched' -f $Phase

$phase = $Phase.ToLower()
$deadline = (Get-Date).AddSeconds(420)
while ((Get-Date) -lt $deadline) {
    Start-Sleep -Seconds 3
    $log = Get-Content 'H:\Windhawk Configuration\backups\2026-10-08\windhawk-2a6-update\phase-log.txt' -Tail 5 -ErrorAction SilentlyContinue
    if ("$log" -match "$phase-complete") { 'COMPLETE'; exit 0 }
    if ("$log" -match "$phase-failed") { 'FAILED - see phase-error file'; exit 2 }
}
'TIMEOUT-WAITING (install continues detached - poll phase-log.txt)'
exit 3
