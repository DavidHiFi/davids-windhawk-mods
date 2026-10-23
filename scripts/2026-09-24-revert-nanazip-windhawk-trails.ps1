#requires -Version 5.1
<#
Reverts the 2026-09-24 translucent-windows change made while chasing the NanaZip
drag-marquee trails. Restores the full mod key from the pre-change export, bumps
SettingsChangeTime so Windhawk reloads, and restarts the service.

reg.exe writes its success banner to stderr, so native calls run with
ErrorActionPreference = Continue and are checked via $LASTEXITCODE instead.
#>
[CmdletBinding()]
param(
    [string]$Backup = 'H:\System Configuration\backups\2026-09-24-translucent-windows-windhawk.reg',
    [string]$LogPath = 'H:\System Configuration\reports\2026-09-24-nanazip-windhawk-revert.log'
)

$ErrorActionPreference = 'Continue'
$key = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\translucent-windows\Settings'
$mod = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'

New-Item -ItemType Directory -Force -Path (Split-Path $LogPath) | Out-Null
Set-Content -LiteralPath $LogPath -Value "start $(Get-Date -Format o)" -Encoding UTF8

function Write-Log {
    param([string]$Message)
    Add-Content -LiteralPath $LogPath -Value $Message -Encoding UTF8
    Write-Output $Message
}

function Show-Value {
    param([string]$Name)
    $out = (& reg.exe query $key /v $Name 2>&1 | Out-String).Trim()
    Write-Log ("  {0} -> {1}" -f $Name, (($out -split "`r?`n" | Select-Object -Last 1).Trim()))
}

$names = @(
    'RuledPrograms[21].target',
    'RuledPrograms[21].BackgroundEffects.type',
    'RuledPrograms[21].RenderingMod.ThemeBackground',
    'RuledPrograms[21].RenderingMod.AccentColorControls'
)

if (-not (Test-Path -LiteralPath $Backup)) { Write-Log "FAIL: backup not found: $Backup"; exit 1 }

Write-Log 'BEFORE:'
$names | ForEach-Object { Show-Value $_ }

& reg.exe import $Backup 2>&1 | Out-Null
if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: reg import exit $LASTEXITCODE"; exit 1 }
Write-Log "imported $Backup"

# Windhawk only re-reads a mod's settings when this timestamp moves.
$stamp = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
& reg.exe add $mod /v 'SettingsChangeTime' /t REG_QWORD /d $stamp /f 2>&1 | Out-Null
if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: SettingsChangeTime bump exit $LASTEXITCODE"; exit 1 }

Write-Log 'AFTER:'
$names | ForEach-Object { Show-Value $_ }

try {
    Restart-Service -Name Windhawk -Force -ErrorAction Stop
    Write-Log 'Windhawk service restarted OK'
}
catch {
    Write-Log "FAIL: service restart: $($_.Exception.Message)"
    exit 1
}

Write-Log "done $(Get-Date -Format o)"
exit 0
