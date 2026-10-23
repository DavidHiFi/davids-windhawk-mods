# Registers or removes the scheduled recheck for guard-tray-vertical.ps1.
# Run elevated through scripts\Invoke-Elevated.ps1:
#   -Install   register the task, run it once now, print its state
#   -Remove    unregister the task
#   -Status    print the task state and last result
# The task runs as SYSTEM at startup and every 5 minutes. The guard writes only on drift,
# so a steady state changes nothing and the log stays short.
param([switch]$Install, [switch]$Remove, [switch]$Status)
$ErrorActionPreference = 'Stop'
$task = 'WindhawkTrayGuard'
$guard = 'H:\Windhawk Configuration\scripts\guard-tray-vertical.ps1'
$log = 'H:\Windhawk Configuration\reports\2026-10-24-tray-go\guard-task.log'

if ($Install) {
    $cmd = "& '$guard' *>> '$log'"
    $action = New-ScheduledTaskAction -Execute 'powershell.exe' -Argument "-NoProfile -ExecutionPolicy Bypass -Command `"$cmd`""
    $every = New-ScheduledTaskTrigger -Once -At (Get-Date).AddMinutes(1) -RepetitionInterval (New-TimeSpan -Minutes 5) -RepetitionDuration (New-TimeSpan -Days 3650)
    $boot = New-ScheduledTaskTrigger -AtStartup
    $principal = New-ScheduledTaskPrincipal -UserId 'SYSTEM' -LogonType ServiceAccount -RunLevel Highest
    $settings = New-ScheduledTaskSettingsSet -StartWhenAvailable -MultipleInstances IgnoreNew -ExecutionTimeLimit (New-TimeSpan -Minutes 2)
    Register-ScheduledTask -TaskName $task -Action $action -Trigger @($every, $boot) -Principal $principal -Settings $settings -Force | Out-Null
    Start-ScheduledTask -TaskName $task
    Start-Sleep -Seconds 8
}
if ($Remove) {
    if (Get-ScheduledTask -TaskName $task -ErrorAction SilentlyContinue) { Unregister-ScheduledTask -TaskName $task -Confirm:$false }
}
if ($Install -or $Status) {
    $t = Get-ScheduledTask -TaskName $task
    $i = Get-ScheduledTaskInfo -TaskName $task
    "task $task state=$($t.State) last=$($i.LastRunTime) result=$($i.LastTaskResult) next=$($i.NextRunTime)"
}
