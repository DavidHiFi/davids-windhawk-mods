<#
.SYNOPSIS
    Translucent Flyouts 0.6.34 DEBUG builds for the missing-accent-border investigation, 2026-10-17.

.DESCRIPTION
    -Audit     print the current registry values and the planned copy
    -Install   back up the mod key, copy a debug DLL beside the live DLLs, point
               LibraryFileName at it and bump SettingsChangeTime
    -Rollback  point LibraryFileName and Version back at the live 0.6.33 DLL and bump
               SettingsChangeTime

    -BuildDir and -LibName select the build and the DLL name; use a new LibName for every
    build so a DLL that a process has mapped is never overwritten. Needs elevation
    (ProgramData and HKLM writes). Run through H:\System Configuration\scripts\Invoke-Elevated.ps1.
    Does not restart Explorer. New processes load the debug DLL; Explorer loads it only
    after its next restart.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Install,
    [switch]$Rollback,
    [string]$BuildDir = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts\build-0.6.34-diag3',
    [string]$LibName  = 'local@translucent-flyouts_0.6.34-diag3_1.dll'
)

$ErrorActionPreference = 'Stop'
$id      = 'local@translucent-flyouts'
$key     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$mods    = 'C:\ProgramData\Windhawk\Engine\Mods'
$backup  = "H:\Windhawk Configuration\backups\2026-10-17\translucent-flyouts-$($LibName -replace '^local@translucent-flyouts_','' -replace '_1\.dll$','')"
$srcDll  = Join-Path $BuildDir 'local@translucent-flyouts_0.6.34_1_64.dll'
$liveLib = 'local@translucent-flyouts_0.6.33_1.dll'

function Show-State {
    $p = Get-ItemProperty $key
    "LibraryFileName=$($p.LibraryFileName) Version=$($p.Version) Include=$($p.Include) SettingsChangeTime=$($p.SettingsChangeTime) Disabled=$($p.Disabled)"
}
function Bump-Marker {
    $now  = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $prev = (Get-ItemProperty $key).SettingsChangeTime
    $value = if ($prev -ge $now) { $prev + 1 } else { $now }
    Set-ItemProperty $key SettingsChangeTime -Value $value -Type DWord
}

if ($Audit) {
    'current:'; Show-State
    "would copy: $srcDll -> $mods\64\$LibName"
    "would set LibraryFileName=$LibName Version=0.6.34 and bump SettingsChangeTime"
    exit 0
}

if ($Install) {
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@translucent-flyouts' (Join-Path $backup 'mod-key-before-install.reg') /y | Out-Null
    Copy-Item -LiteralPath $srcDll -Destination "$mods\64\$LibName" -Force
    Set-ItemProperty $key LibraryFileName $LibName
    Set-ItemProperty $key Version '0.6.34'
    Bump-Marker
    'installed:'; Show-State
    $same = (Get-FileHash "$mods\64\$LibName").Hash -eq (Get-FileHash $srcDll).Hash
    "dll hash matches build: $same"
    exit 0
}

if ($Rollback) {
    Set-ItemProperty $key LibraryFileName $liveLib
    Set-ItemProperty $key Version '0.6.33'
    Bump-Marker
    'rolled back:'; Show-State
    exit 0
}

Write-Error 'Pass -Audit, -Install or -Rollback.'
exit 2
