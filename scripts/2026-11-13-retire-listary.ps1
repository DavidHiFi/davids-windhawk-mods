# Retire Listary now that Seamless Explorer Search does its Explorer search (owner order 2026-11-12).
# Listary stays installed. Its logon task is turned off and the running copy is ended. Runs ELEVATED.
#   -Action retire    export the task XML, disable the task, end Listary, verify
#   -Action rollback  enable the task and start it again
param([ValidateSet('retire', 'rollback')][string]$Action = 'retire')
$ErrorActionPreference = 'Stop'
$bk = 'H:\Windhawk Configuration\backups\2026-11-13\retire-listary'
New-Item -ItemType Directory -Force $bk | Out-Null
$log = Join-Path $bk 'receipt.txt'
function Say($t) { $l = "$(Get-Date -Format 'h:mm:ss tt') $t"; Add-Content -Path $log -Value $l -Encoding UTF8; Write-Host $l }

if ($Action -eq 'rollback') {
    Enable-ScheduledTask -TaskName 'Listary' | Out-Null
    Start-ScheduledTask -TaskName 'Listary'
    Start-Sleep -Seconds 5
    Say "ROLLBACK task $((Get-ScheduledTask -TaskName Listary).State), running: $([bool](Get-Process Listary -EA SilentlyContinue))"
    exit 0
}

$xml = Join-Path $bk 'Listary-task.xml'
if (-not (Test-Path $xml)) { Export-ScheduledTask -TaskName 'Listary' | Set-Content -Path $xml -Encoding Unicode }
Say "task exported to $xml (state $((Get-ScheduledTask -TaskName Listary).State))"
Disable-ScheduledTask -TaskName 'Listary' | Out-Null
schtasks /end /tn Listary 2>&1 | Out-Null
for ($i = 0; $i -lt 20 -and (Get-Process Listary -EA SilentlyContinue); $i++) { Start-Sleep -Milliseconds 500 }
if (Get-Process Listary -EA SilentlyContinue) { Get-Process Listary | Stop-Process -Force; Start-Sleep -Seconds 2 }
$state = (Get-ScheduledTask -TaskName Listary).State
$running = [bool](Get-Process Listary -EA SilentlyContinue)
Say "RETIRED task $state, Listary running: $running"
if ($state -ne 'Disabled' -or $running) { exit 1 }
