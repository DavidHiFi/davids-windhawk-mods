# Set local@window-borders colors (elevated) from a preset name and bump
# SettingsChangeTime so the engine hot-reloads. Presets avoid passing '#' through
# the elevation wrapper. Presets: test (loud green/red), default (accent/none).
param([ValidateSet('test','default')][string]$Preset = 'default', [switch]$Elevated)
$ErrorActionPreference = 'Stop'
if (-not $Elevated) {
    & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList "-Preset $Preset -Elevated"
    exit 0
}
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@window-borders'
$p = @{ test = @('#00FF40', '#FF0040'); default = @('accent', 'transparent') }[$Preset]
New-ItemProperty "$key\Settings" -Name focusedColor   -Value $p[0] -PropertyType String -Force | Out-Null
New-ItemProperty "$key\Settings" -Name unfocusedColor -Value $p[1] -PropertyType String -Force | Out-Null
New-ItemProperty $key -Name SettingsChangeTime -Value ([DateTimeOffset]::Now.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null
$s = Get-ItemProperty "$key\Settings"
"settings now: focused=$($s.focusedColor) unfocused=$($s.unfocusedColor)" | Out-File 'H:\Windhawk Configuration\backups\2026-10-25\window-borders\set.log'
