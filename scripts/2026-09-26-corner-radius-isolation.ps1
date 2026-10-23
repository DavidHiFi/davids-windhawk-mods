# 2026-09-26 custom-corner-radius isolation: disable mod + rebuild DWM
Start-Transcript -Path 'H:\System Configuration\reports\2026-09-26-corner-radius-isolation.log' -Force
$k = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\custom-corner-radius'
'before:'
reg query "HKLM\SOFTWARE\Windhawk\Engine\Mods\custom-corner-radius" /v Disabled 2>&1
New-ItemProperty -Path $k -Name 'Disabled' -PropertyType DWord -Value 1 -Force | Out-Null
'after :'
reg query "HKLM\SOFTWARE\Windhawk\Engine\Mods\custom-corner-radius" /v Disabled
Start-Sleep 6
'-- restarting dwm to clear any DWM-resident state'
Stop-Process -Name dwm -Force -ErrorAction SilentlyContinue
Start-Sleep 8
Get-Process dwm -ErrorAction SilentlyContinue | Select-Object Id, StartTime
'-- done'
Stop-Transcript
