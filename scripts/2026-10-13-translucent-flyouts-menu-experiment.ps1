<#
.SYNOPSIS
    Translucent Flyouts menu experiments: back up the mod's Settings key, change one
    value, bump SettingsChangeTime so the mod reloads, or restore the backup.

.DESCRIPTION
    -Backup                 export the Settings key to settings-pre-experiment.reg
    -Name <v> -Value <v>    set one value (-Type SZ or DWORD, default SZ), bump the marker
    -Restore                reg import the backup, bump the marker

    Needs elevation (HKLM writes). Run through H:\System Configuration\scripts\Invoke-Elevated.ps1.
    Does not restart Windhawk or Explorer.
#>
[CmdletBinding()]
param(
    [switch]$Backup,
    [switch]$Restore,
    [string]$Name,
    [string]$Value,
    [ValidateSet('SZ', 'DWORD')]
    [string]$Type = 'SZ',
    [string]$Mod = 'local@translucent-flyouts'
)

$ErrorActionPreference = 'Stop'
$id         = $Mod
$key        = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$regSetting = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id\Settings"
$backupDir  = 'H:\Windhawk Configuration\backups\2026-10-13\translucent-flyouts-corners'
$backupFile = Join-Path $backupDir "settings-pre-experiment-$id.reg"

function Bump-Marker {
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $prev = (Get-ItemProperty $key).SettingsChangeTime
    $value = if ($prev -ge $now) { $prev + 1 } else { $now }
    Set-ItemProperty $key SettingsChangeTime -Value $value -Type DWord
    $value
}

New-Item -ItemType Directory -Path $backupDir -Force | Out-Null

if ($Backup) {
    reg export $regSetting $backupFile /y | Out-Null
    "backup: $backupFile"
    exit 0
}

if ($Restore) {
    reg import $backupFile | Out-Null
    $marker = Bump-Marker
    "restored from $backupFile; SettingsChangeTime=$marker"
    exit 0
}

if ($Name) {
    $old = (Get-ItemProperty -Path "$key\Settings").$Name
    reg add $regSetting /v $Name /t "REG_$Type" /d $Value /f | Out-Null
    $now = (Get-ItemProperty -Path "$key\Settings").$Name
    $marker = Bump-Marker
    "set $Name=$Value (was $old, now $now); SettingsChangeTime=$marker"
    exit 0
}

'Nothing to do: pass -Backup, -Restore, or -Name and -Value'
exit 1
