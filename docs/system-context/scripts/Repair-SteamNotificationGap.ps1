[CmdletBinding()]
param([switch]$Apply,[switch]$Rollback)
$ErrorActionPreference = 'Stop'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\titlebar-for-everyone'
$backup = 'H:\System Configuration\backups\2026-10-01-steam-notification-gap'
$current = Get-ItemProperty "$key\Settings"
if (!$Apply -and !$Rollback) {
    $current | Select-Object nosteamhtmlinject,notoolwinsteam
    exit
}
if ($Apply -and $Rollback) {throw 'Choose Apply or Rollback'}
$principal = [Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()
if (!$principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {throw 'Elevation required'}
if ($Apply) {
    New-Item -ItemType Directory -Force $backup | Out-Null
    if (!(Test-Path "$backup\before.json")) {
        & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\titlebar-for-everyone' "$backup\before.reg" /y
        if ($LASTEXITCODE) {throw 'Backup export failed'}
        @{original=[int]$current.nosteamhtmlinject;timestamp=(Get-Date -Format o)} | ConvertTo-Json | Set-Content "$backup\before.json"
    }
    $expected = 1
} else {
    $expected = [int](Get-Content "$backup\before.json" -Raw | ConvertFrom-Json).original
}
Set-ItemProperty "$key\Settings" nosteamhtmlinject -Type DWord -Value $expected
Set-ItemProperty $key SettingsChangeTime -Type DWord -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
$after = Get-ItemProperty "$key\Settings"
if ($after.nosteamhtmlinject -ne $expected) {throw 'Setting verification failed'}
Write-Output "Steam HTML injection disabled: $($current.nosteamhtmlinject) -> $($after.nosteamhtmlinject). Millennium remains responsible for window parameters."
