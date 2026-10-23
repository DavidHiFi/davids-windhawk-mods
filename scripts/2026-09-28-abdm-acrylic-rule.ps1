# AB Download Manager — acrylic/Mica window effect via the Windhawk
# "Translucent Windows" mod (translucent-windows), same recipe used for
# Discord/Zen/etc. on this machine: acrylicblur with AccentBlurBehind AA1E1E2E
# (Catppuccin base at 66% alpha).
#
# Adds one process rule (RuledPrograms[25]) for ABDownloadManager.exe and bumps
# the mod's SettingsChangeTime so the running Windhawk engine reloads it live.
# NO engine restart (it breaks explorer/T3 on this machine).
#
# Requires elevation (HKLM). Usage:
#   -Audit              show current rule/state (no changes)
#   -Apply              add the rule + bump SettingsChangeTime
#   -Rollback           remove the rule values (index 25) + bump SettingsChangeTime

param(
    [switch]$Audit,
    [switch]$Apply,
    [switch]$Rollback
)

$ErrorActionPreference = 'Stop'
$modKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'
$setKey = Join-Path $modKey 'Settings'
$ruleIdx = 25
$props = @{
    "RuledPrograms[$ruleIdx].target" = 'ABDownloadManager.exe'
    "RuledPrograms[$ruleIdx].RenderingMod.ThemeBackground" = 1
    "RuledPrograms[$ruleIdx].RenderingMod.AccentColorControls" = 1
    "RuledPrograms[$ruleIdx].BackgroundEffects.type" = 'acrylicblur'
    "RuledPrograms[$ruleIdx].BackgroundEffects.AccentBlurBehind" = 'AA1E1E2E'
}

function Show-State {
    Write-Host "key: $setKey"
    foreach ($name in $props.Keys) {
        $v = (Get-ItemProperty -Path $setKey -Name $name -ErrorAction SilentlyContinue).$name
        Write-Host ("  {0} = {1}" -f $name, $(if ($null -ne $v) { $v } else { '(absent)' }))
    }
    $t = (Get-ItemProperty -Path $modKey -Name SettingsChangeTime -ErrorAction SilentlyContinue).SettingsChangeTime
    Write-Host "  SettingsChangeTime = $t"
}

function Bump-Time {
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    New-ItemProperty -Path $modKey -Name 'SettingsChangeTime' -Value $now -PropertyType DWord -Force | Out-Null
    Write-Host "SettingsChangeTime bumped to $now"
}

if (-not ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    throw 'This script writes HKLM; run it elevated.'
}

if ($Apply) {
    foreach ($name in $props.Keys) {
        $type = if ($props[$name] -is [int]) { 'DWord' } else { 'String' }
        New-ItemProperty -Path $setKey -Name $name -Value $props[$name] -PropertyType $type -Force | Out-Null
        Write-Host "set $name = $($props[$name])"
    }
    Bump-Time
    Write-Host 'applied. The engine reloads live; existing ABDM windows may need a repaint (restart the app for a clean start).'
} elseif ($Rollback) {
    foreach ($name in $props.Keys) {
        Remove-ItemProperty -Path $setKey -Name $name -ErrorAction SilentlyContinue
        Write-Host "removed $name"
    }
    Bump-Time
} else {
    Show-State
}
