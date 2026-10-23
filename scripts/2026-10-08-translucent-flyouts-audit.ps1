<#
.SYNOPSIS
    Translucent-flyouts audit fixes, 2026-10-08 (thread t3-translucent-flyout-audit).

.DESCRIPTION
    -Audit    print the planned actions
    -Backup   reg export both mod keys + copy both mod sources into the backup dir
    -Install  apply: colorization settings DWORD->REG_SZ (same effective values),
              remove Ableton*.exe from local@translucent-flyouts Exclude,
              translucent-windows FlyoutsEffects 1 -> 0, bump both SettingsChangeTime
    -Rollback restore the registry from the backup .reg files (source file restore
              is manual: local@translucent-flyouts.wh.cpp.pre-audit.bak)

    The mod source edit and recompile happen outside this script; this script only
    touches the registry. Verify with -Audit style reads after each step.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Backup,
    [switch]$Install,
    [switch]$Rollback
)

$ErrorActionPreference = 'Stop'
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-08\translucent-flyouts-audit'
$tfKey  = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@translucent-flyouts'
$twKey  = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'

function Bump([string]$key) {
    $existing = (Get-ItemProperty -Path "Registry::$key" -Name SettingsChangeTime -ErrorAction SilentlyContinue).SettingsChangeTime
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $value = if ($existing -and $existing -ge $now) { $existing + 1 } else { $now }
    Set-ItemProperty -Path "Registry::$key" -Name SettingsChangeTime -Value $value -Type DWord
    "bumped $key SettingsChangeTime -> $value"
}

if ($Audit) {
    "would backup: reg export $tfKey and $twKey + copy both ModsSource .wh.cpp -> $backupDir"
    "would install: 14 colorization settings DWORD->REG_SZ; $tfKey Exclude minus Ableton*.exe;"
    "               $twKey FlyoutsEffects = 0; bump both SettingsChangeTime"
    "would rollback: reg import the two backup .reg files"
    exit 0
}

if ($Backup) {
    New-Item -ItemType Directory -Force -Path $backupDir | Out-Null
    reg export $tfKey "$backupDir\local-translucent-flyouts.reg" /y | Out-Null
    reg export $twKey "$backupDir\translucent-windows.reg" /y | Out-Null
    Copy-Item 'C:\ProgramData\Windhawk\ModsSource\local@translucent-flyouts.wh.cpp' "$backupDir\local@translucent-flyouts.wh.cpp.pre-audit.bak" -Force
    Copy-Item 'C:\ProgramData\Windhawk\ModsSource\translucent-windows.wh.cpp' "$backupDir\translucent-windows.wh.cpp.pre-audit.bak" -Force
    Get-ChildItem $backupDir | Select-Object Name, Length | Format-Table -AutoSize | Out-String
    exit 0
}

if ($Install) {
    # 1. Colorization settings: stored as DWORD option indices; the fixed schema
    #    uses strings. Preserve the effective value of each.
    $s = "Registry::$tfKey\Settings"
    $map = @{
        'dropDown.darkModeThemeColorizationType'            = 'start_hover'       # was 1
        'dropDown.lightModeThemeColorizationType'           = 'start_hover'       # was 1
        'menu.darkModeThemeColorizationType'                = 'start_background'  # was 0
        'menu.lightModeThemeColorizationType'               = 'start_background'  # was 0
        'tooltip.darkModeThemeColorizationType'             = 'start_background'  # was 0
        'tooltip.lightModeThemeColorizationType'            = 'start_background'  # was 0
        'menu.separator_darkThemeColorizationType'          = 'start_background'  # was 0
        'menu.separator_lightThemeColorizationType'         = 'start_background'  # was 0
        'menu.focusing_darkThemeColorizationType'           = 'start_background'  # was 0
        'menu.focusing_lightThemeColorizationType'          = 'start_background'  # was 0
        'menu.disabledHot_darkThemeColorizationType'        = 'start_background'  # was 0
        'menu.disabledHot_lightThemeColorizationType'       = 'start_background'  # was 0
        'menu.hot_darkThemeColorizationType'                = 'start_background'  # was 0
        'menu.hot_lightThemeColorizationType'               = 'start_background'  # was 0
    }
    foreach ($name in $map.Keys) {
        $before = (Get-ItemProperty -Path $s -Name $name).$name
        Set-ItemProperty -Path $s -Name $name -Value $map[$name] -Type String
        "set ${name}: $before -> '$($map[$name])' (REG_SZ)"
    }

    # 2. Ableton back in scope (standing 2026-09-28 exception; requested again today).
    $excl = (Get-ItemProperty -Path "Registry::$tfKey").Exclude
    if ($excl -match 'Ableton') {
        $new = ($excl -split '\|' | Where-Object { $_ -notlike 'Ableton*' }) -join '|'
        Set-ItemProperty -Path "Registry::$tfKey" -Name Exclude -Value $new -Type String
        "Exclude: '$excl' -> '$new'"
    } else {
        "Exclude already free of Ableton: '$excl'"
    }

    # 3. translucent-windows: stop styling flyouts; keep window backgrounds.
    Set-ItemProperty -Path "Registry::$twKey\Settings" -Name FlyoutsEffects -Value 0 -Type DWord
    "translucent-windows FlyoutsEffects -> 0"

    Bump $tfKey
    Bump $twKey
    exit 0
}

if ($Rollback) {
    reg import "$backupDir\local-translucent-flyouts.reg"
    reg import "$backupDir\translucent-windows.reg"
    Bump $tfKey
    Bump $twKey
    "rolled back registry from $backupDir (bumped SettingsChangeTime to re-apply old values live)"
    exit 0
}

'Nothing to do: pass -Audit, -Backup, -Install or -Rollback'
exit 1
