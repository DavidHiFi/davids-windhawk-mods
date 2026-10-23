[CmdletBinding()]
param([switch]$Apply, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\titlebar-for-everyone'
$backup = 'H:\System Configuration\backups\2026-09-30\steam-final-fixes'
$current = Get-ItemProperty $key
if (!$Apply -and !$Rollback) {
    $current | Select-Object Disabled,ExcludeCustom,SettingsChangeTime
    exit
}
if ($Apply -and $Rollback) {throw 'Choose Apply or Rollback'}
$principal = [Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()
if (!$principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {throw 'Elevation required'}
New-Item -ItemType Directory -Force $backup | Out-Null
if ($Rollback) {
    $before = Get-Content "$backup\titlebar-before.json" -Raw | ConvertFrom-Json
    if ($before.hadExcludeCustom) {
        Set-ItemProperty $key ExcludeCustom $before.excludeCustom
    } else {
        Remove-ItemProperty $key ExcludeCustom -ErrorAction SilentlyContinue
    }
    $expected = $before.excludeCustom
} else {
    if (!(Test-Path "$backup\titlebar-before.json")) {
        & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\titlebar-for-everyone' "$backup\titlebar-before.reg" /y
        if ($LASTEXITCODE) {throw 'Registry export failed'}
        @{hadExcludeCustom=($null -ne $current.PSObject.Properties['ExcludeCustom']);excludeCustom=[string]$current.ExcludeCustom;timestamp=(Get-Date -Format o)} | ConvertTo-Json | Set-Content "$backup\titlebar-before.json"
    }
    $parts = @(([string]$current.ExcludeCustom -split '\|') | Where-Object {$_})
    if ($parts -notcontains 'steamwebhelper.exe') {$parts += 'steamwebhelper.exe'}
    $expected = $parts -join '|'
    New-ItemProperty $key ExcludeCustom -PropertyType String -Value $expected -Force | Out-Null
}
New-ItemProperty $key SettingsChangeTime -PropertyType DWord -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Force | Out-Null
$after = Get-ItemProperty $key
if ([string]$after.ExcludeCustom -ne [string]$expected) {throw 'Verification failed'}
Write-Output "Titlebar For Everyone ExcludeCustom: '$($current.ExcludeCustom)' -> '$($after.ExcludeCustom)'. No application restart."
