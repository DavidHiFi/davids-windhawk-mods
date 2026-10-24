# Enable/disable local@window-borders (elevated, reversible).
param([ValidateSet('On','Off')][string]$State = 'On', [switch]$Elevated)
$ErrorActionPreference = 'Stop'
if (-not $Elevated) {
    & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList "-State $State -Elevated"
    exit 0
}
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@window-borders'
New-ItemProperty $key -Name Disabled -Value $(if ($State -eq 'On') { 0 } else { 1 }) -PropertyType DWord -Force | Out-Null
New-ItemProperty $key -Name SettingsChangeTime -Value ([DateTimeOffset]::Now.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null
"Disabled=$((Get-ItemProperty $key).Disabled)" | Out-File 'H:\Windhawk Configuration\backups\2026-10-25\window-borders\toggle.log'
