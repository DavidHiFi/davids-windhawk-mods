# Reload one mod (disable, then enable) through the Windhawk CLI. Run elevated.
param([Parameter(Mandatory)][string]$Id)
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
& $cli mod disable $Id 2>&1 | ForEach-Object { "$_" }
Start-Sleep 3
& $cli mod enable $Id 2>&1 | ForEach-Object { "$_" }
"Disabled=$((Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$Id").Disabled)"
