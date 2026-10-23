#requires -Version 5.1
<#
Fixes the NanaZip drag-marquee trails by excluding NanaZip from the
win32-ui-modernizer Windhawk mod.

Cause: win32-ui-modernizer hooks user32!DrawFocusRect (ModernFocusRect=modern)
and draws an opaque rounded outline instead. A classic SysListView32 without
double-buffering draws its drag marquee with DrawFocusRect and erases the old
frame by drawing the same rectangle again, relying on XOR. The opaque outline
never erases, so every frame of the drag stays on screen.

Change: adds NanaZip.Modern.FileManager.exe to the mod's ExcludeCustom list (the
value the Windhawk UI writes for "Custom process exclusion list"). Every other
process keeps the mod and all its settings.

Also normalises translucent-windows SettingsChangeTime back to REG_DWORD; the
2026-09-24 revert script wrote it as REG_QWORD, which is not the type Windhawk
itself uses.

Rollback: -Rollback re-imports the backup taken by this script.
#>
[CmdletBinding()]
param(
    [switch]$Rollback,
    [string]$Backup = 'H:\System Configuration\backups\2026-09-25-win32-ui-modernizer-windhawk.reg',
    [string]$LogPath = 'H:\System Configuration\reports\2026-09-25-nanazip-marquee-fix.log'
)

$ErrorActionPreference = 'Continue'
$mod = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\win32-ui-modernizer'
$translucent = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'
$target = 'NanaZip.Modern.FileManager.exe'

New-Item -ItemType Directory -Force -Path (Split-Path $LogPath) | Out-Null
Add-Content -LiteralPath $LogPath -Value "start $(Get-Date -Format o) rollback=$Rollback" -Encoding UTF8

function Write-Log {
    param([string]$Message)
    Add-Content -LiteralPath $LogPath -Value $Message -Encoding UTF8
    Write-Output $Message
}

function Get-RegValue {
    param([string]$Key, [string]$Name)
    $out = & reg.exe query $Key /v $Name 2>$null
    if ($LASTEXITCODE -ne 0) { return $null }
    $line = $out | Where-Object { $_ -match "^\s+$([regex]::Escape($Name))\s+REG_" } | Select-Object -First 1
    if ($line -match 'REG_\w+\s*(.*)$') { return $Matches[1].Trim() }
    return ''
}

function Update-ChangeTime {
    param([string]$Key)
    # Windhawk reloads a mod's config when this timestamp moves.
    $stamp = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    & reg.exe add $Key /v 'SettingsChangeTime' /t REG_DWORD /d $stamp /f 2>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: SettingsChangeTime on $Key exit $LASTEXITCODE"; exit 1 }
}

if ($Rollback) {
    if (-not (Test-Path -LiteralPath $Backup)) { Write-Log "FAIL: backup not found: $Backup"; exit 1 }
    # reg import merges; drop the value first so a backup without it really removes it.
    & reg.exe delete $mod /v 'ExcludeCustom' /f 2>&1 | Out-Null
    & reg.exe import $Backup 2>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: reg import exit $LASTEXITCODE"; exit 1 }
    Update-ChangeTime $mod
    Write-Log "rolled back from $Backup; ExcludeCustom now '$(Get-RegValue $mod 'ExcludeCustom')'"
    exit 0
}

if (-not (Test-Path -LiteralPath $Backup)) {
    & reg.exe export $mod $Backup /y 2>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: reg export exit $LASTEXITCODE"; exit 1 }
    Write-Log "backed up $mod -> $Backup"
}
else {
    Write-Log "backup already present, kept: $Backup"
}

$before = Get-RegValue $mod 'ExcludeCustom'
Write-Log "BEFORE ExcludeCustom='$before' Exclude='$(Get-RegValue $mod 'Exclude')'"

$items = @()
if ($before) { $items = $before -split '\|' | Where-Object { $_ } }
if ($items -notcontains $target) { $items += $target }
$new = $items -join '|'

& reg.exe add $mod /v 'ExcludeCustom' /t REG_SZ /d $new /f 2>&1 | Out-Null
if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: ExcludeCustom write exit $LASTEXITCODE"; exit 1 }
Update-ChangeTime $mod
Write-Log "AFTER  ExcludeCustom='$(Get-RegValue $mod 'ExcludeCustom')'"

$tq = & reg.exe query $translucent /v 'SettingsChangeTime' 2>$null
if ($tq -match 'REG_QWORD') {
    & reg.exe delete $translucent /v 'SettingsChangeTime' /f 2>&1 | Out-Null
    Update-ChangeTime $translucent
    Write-Log "translucent-windows SettingsChangeTime normalised to REG_DWORD"
}

Write-Log "done $(Get-Date -Format o)"
exit 0
