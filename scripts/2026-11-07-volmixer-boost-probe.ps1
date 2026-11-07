# Probe: does an IncludeCustom write on the mixer key restart its tool host?
# Uses a process name that never runs, then removes it again.
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@better-volume-mixer-plus'
$out = Join-Path $env:PUBLIC 'wh-probe.txt'
function Host-Pid { (Get-CimInstance Win32_Process -Filter "Name='windhawk-mod.exe'" | Where-Object CommandLine -like '*better-volume-mixer-plus*').ProcessId }
"before pid=$(Host-Pid) custom='$((Get-ItemProperty $key).IncludeCustom)' only='$((Get-ItemProperty $key).IncludeExcludeCustomOnly)'" | Out-File $out
Set-ItemProperty $key -Name IncludeCustom -Value 'bvmp-probe.exe' -Type String
Start-Sleep -Seconds 4
"after-add pid=$(Host-Pid)" | Out-File -Append $out
Remove-ItemProperty $key -Name IncludeCustom
Start-Sleep -Seconds 4
"after-remove pid=$(Host-Pid)" | Out-File -Append $out
