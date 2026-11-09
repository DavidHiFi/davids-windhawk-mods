# 2026-11-09: the taskbar icon bubbles lost their left and right borders.
# Cause: Windows 11 Taskbar Styler draws each bubble 28 px wide inside a 26 px icon slot, so
# XAML clips 1 px off each side and only the rounded corners show. A -1 px side margin makes
# the bubble fit the slot while it still draws 28 px wide, so nothing is clipped.
#   rule 8 (RunningIndicator bubble):      add   Margin=-1,0,-1,0
#   rule 7 (BackgroundElement hover face): Margin=0 -> Margin=-1,0,-1,0 (styles[2] and [6])
# Run elevated (Invoke-Elevated.ps1) under `coop lock windhawk-engine`. No Explorer restart.
param([ValidateSet('Install', 'Rollback', 'Audit')][string]$Action = 'Audit')
$ErrorActionPreference = 'Stop'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$settings = "$key\Settings"
$bk = 'H:\Windhawk Configuration\backups\2026-11-09-dock-bubble'
$margin = 'Margin=-1,0,-1,0'
$changes = [ordered]@{
    'controlStyles[8].styles[74]' = @{ Old = $null; New = $margin }
    'controlStyles[7].styles[2]'  = @{ Old = 'Margin=0'; New = $margin }
    'controlStyles[7].styles[6]'  = @{ Old = 'Margin=0'; New = $margin }
}

# Brackets in -Name are wildcards, so values are read and removed through the .NET key.
function Get([string]$n) { (Get-Item $settings).GetValue($n) }
function Show { foreach ($n in $changes.Keys) { "$n = $(Get $n)" } }
function Bump { Set-ItemProperty $key -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) }

if ($Action -eq 'Audit') { Show; return }

if ($Action -eq 'Install') {
    New-Item $bk -ItemType Directory -Force | Out-Null
    if (-not (Test-Path "$bk\taskbar-styler.reg")) {
        & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' "$bk\taskbar-styler.reg" /y | Out-Null
    }
    foreach ($n in $changes.Keys) {
        $cur = Get $n
        if ($cur -ne $changes[$n].Old -and $cur -ne $changes[$n].New) { throw "$n is '$cur', expected '$($changes[$n].Old)'; inspect first" }
    }
    foreach ($n in $changes.Keys) { New-ItemProperty $settings -Name $n -Value $changes[$n].New -PropertyType String -Force | Out-Null }
} else {
    foreach ($n in $changes.Keys) {
        if ($null -eq $changes[$n].Old) {
            $k = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey('SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings', $true)
            $k.DeleteValue($n, $false); $k.Close()
        }
        else { New-ItemProperty $settings -Name $n -Value $changes[$n].Old -PropertyType String -Force | Out-Null }
    }
}
Bump
Show
