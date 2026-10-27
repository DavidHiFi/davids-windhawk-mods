# Installs the Fullscreen Start Plus keys helper: copies fsp-keys.exe to
# Program Files (only administrators can change it there), adds a scheduled task
# that starts it as administrator when you sign in, and starts it now.
# Run as administrator. -Uninstall removes the task, the program and the folder.
param(
    [string]$Exe = (Join-Path $PSScriptRoot 'fsp-keys.exe'),
    [switch]$Uninstall
)
$ErrorActionPreference = 'Stop'
$dir = Join-Path $env:ProgramFiles 'FullscreenStartPlus'
$task = 'FullscreenStartPlusKeys'

Get-Process fsp-keys -ErrorAction SilentlyContinue | Stop-Process -Force
if ($Uninstall) {
    Unregister-ScheduledTask -TaskName $task -Confirm:$false -ErrorAction SilentlyContinue
    Remove-Item $dir -Recurse -Force -ErrorAction SilentlyContinue
    "removed"
    exit 0
}
New-Item $dir -ItemType Directory -Force | Out-Null
Start-Sleep -Milliseconds 300  # The stopped copy lets go of the file.
Copy-Item $Exe "$dir\fsp-keys.exe" -Force
$user = "$env:USERDOMAIN\$env:USERNAME"
$action = New-ScheduledTaskAction -Execute "$dir\fsp-keys.exe"
$trigger = New-ScheduledTaskTrigger -AtLogOn -User $user
$principal = New-ScheduledTaskPrincipal -UserId $user -LogonType Interactive -RunLevel Highest
# No time limit, normal priority (a task's default is below normal), and a
# restart if it ever stops.
$settings = New-ScheduledTaskSettingsSet -ExecutionTimeLimit ([TimeSpan]::Zero) -Priority 4 `
    -RestartCount 3 -RestartInterval (New-TimeSpan -Minutes 1) -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries
Register-ScheduledTask -TaskName $task -Action $action -Trigger $trigger -Principal $principal `
    -Settings $settings -Force | Out-Null
Start-ScheduledTask -TaskName $task
Start-Sleep -Seconds 1
$p = Get-Process fsp-keys -ErrorAction SilentlyContinue
if (-not $p) { throw 'fsp-keys.exe did not start' }
"running, process $($p.Id)"
