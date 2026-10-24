# Swap: disable the old win11-accent-border mod (it swallows every
# DWMWA_BORDER_COLOR call, so local@window-borders cannot work beside it).
# Rollback: -Action Restore sets Disabled back to 0.
param([ValidateSet('Disable','Restore')][string]$Action = 'Disable', [switch]$Elevated)
$ErrorActionPreference = 'Stop'
$dir = 'H:\Windhawk Configuration\backups\2026-10-25\window-borders'
if (-not $Elevated) {
    & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList "-Action $Action -Elevated"
    exit 0
}
Start-Transcript -Path "$dir\swap-old-$Action.log" -Force | Out-Null
try {
    $key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\win11-accent-border'
    reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\win11-accent-border' "$dir\old-accent-border-before-$Action.reg" /y | Out-Null
    $v = if ($Action -eq 'Disable') { 1 } else { 0 }
    New-ItemProperty -Path $key -Name Disabled -Value $v -PropertyType DWord -Force | Out-Null
    New-ItemProperty -Path $key -Name SettingsChangeTime -Value ([DateTimeOffset]::Now.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null
    "Disabled readback = $((Get-ItemProperty $key).Disabled)"
} catch { "ERROR: $($_.Exception.Message)" }
finally { Stop-Transcript | Out-Null }
