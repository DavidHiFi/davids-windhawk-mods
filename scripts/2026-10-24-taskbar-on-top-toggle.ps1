# Enable or disable the taskbar-on-top mod through the Windhawk CLI. Run elevated.
param([ValidateSet('enable', 'disable')][string]$Action = 'enable')
$id = 'taskbar-on-top'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
"before Disabled=$((Get-ItemProperty $key).Disabled)"
& 'C:\Program Files\Windhawk\windhawk-cli.exe' mod $Action $id 2>&1 | ForEach-Object { "$_" }
"cli-exit=$LASTEXITCODE"
"after Disabled=$((Get-ItemProperty $key).Disabled)"
