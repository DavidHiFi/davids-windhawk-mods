#requires -Version 5.1
<#
Turns off the win32-ui-modernizer "Modern focus rectangle" feature system-wide.

Why: the mod hooks user32!DrawFocusRect and draws an opaque rounded outline.
A classic, non-double-buffered SysListView32 draws its drag marquee with
DrawFocusRect and erases the previous frame by calling the same API again,
which works only because DrawFocusRect is XOR. The opaque outline never
erases, so every frame of the drag stays on screen as trails (white nested
outlines). NanaZip was excluded per-process on 2026-09-24; Registry Editor
showed the same trails on 2026-09-28. Excluding more processes loses those
apps' other modernizer features (regedit's transparent background), so this
turns the feature off the way the mod itself defines it:

  GeneralSection.Enabled = 0  ->  ModernFocusRect = -1 (native passthrough)

The hook then calls the original DrawFocusRect in every process, which is the
correct XOR behavior. In this configuration every other General feature is
already off (tooltips, menubar, buttons, checkboxes, etc. are all 0), so the
only behavioral change is: modern rounded focus rectangle -> native dotted.

Changes:
- ...\win32-ui-modernizer\Settings\GeneralSection.Enabled: 1 -> 0 (DWORD)
- ...\win32-ui-modernizer\SettingsChangeTime bumped so Windhawk reloads the
  config without a service restart; already-open windows pick it up on their
  next repaint, new processes from their first paint.

Audit mode (-Audit) reads and prints the mod state without changing anything.

Rollback: -Rollback re-imports the backup taken by this script from
backups\2026-09-28\win32-ui-modernizer-before-focusrect-off.reg and bumps
SettingsChangeTime.
#>
[CmdletBinding()]
param(
    [switch]$Rollback,
    [switch]$Audit,
    [string]$Backup = 'H:\System Configuration\backups\2026-09-28\win32-ui-modernizer-before-focusrect-off.reg',
    [string]$LogPath = 'H:\System Configuration\reports\2026-09-28\windhawk-modernizer-focusrect-fix.log'
)

$ErrorActionPreference = 'Continue'
$mod = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\win32-ui-modernizer'
$settings = "$mod\Settings"

New-Item -ItemType Directory -Force -Path (Split-Path $LogPath) | Out-Null
Add-Content -LiteralPath $LogPath -Value "start $(Get-Date -Format o) rollback=$Rollback audit=$Audit" -Encoding UTF8

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
    $stamp = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    & reg.exe add $mod /v 'SettingsChangeTime' /t REG_DWORD /d $stamp /f 2>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: SettingsChangeTime exit $LASTEXITCODE"; exit 1 }
}

function Show-State {
    $line = "state: GeneralSection.Enabled='$(Get-RegValue $settings 'GeneralSection.Enabled')' ModernFocusRect='$(Get-RegValue $settings 'GeneralSection.ModernFocusRect')' Exclude='$(Get-RegValue $mod 'Exclude')' ExcludeCustom='$(Get-RegValue $mod 'ExcludeCustom')' Disabled='$(Get-RegValue $mod 'Disabled')'"
    Write-Log $line
}

Show-State
if ($Audit) { Write-Log 'audit only, no change'; exit 0 }

if ($Rollback) {
    if (-not (Test-Path -LiteralPath $Backup)) { Write-Log "FAIL: backup not found: $Backup"; exit 1 }
    & reg.exe import $Backup 2>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: reg import exit $LASTEXITCODE"; exit 1 }
    Update-ChangeTime
    Write-Log "rolled back from $Backup"
    Show-State
    exit 0
}

$enabled = Get-RegValue $settings 'GeneralSection.Enabled'
if ($enabled -eq '0x0') {
    Write-Log 'GeneralSection.Enabled already 0; still bumping SettingsChangeTime to reload'
}
else {
    if (-not (Test-Path -LiteralPath $Backup)) {
        New-Item -ItemType Directory -Force -Path (Split-Path $Backup) | Out-Null
        & reg.exe export $mod $Backup /y 2>&1 | Out-Null
        if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: reg export exit $LASTEXITCODE"; exit 1 }
        Write-Log "backed up $mod (with subkeys) -> $Backup"
    }
    else {
        Write-Log "backup already present, kept: $Backup"
    }
}

& reg.exe add $settings /v 'GeneralSection.Enabled' /t REG_DWORD /d 0 /f 2>&1 | Out-Null
if ($LASTEXITCODE -ne 0) { Write-Log "FAIL: GeneralSection.Enabled write exit $LASTEXITCODE"; exit 1 }
Update-ChangeTime
Write-Log 'GeneralSection.Enabled -> 0 (ModernFocusRect now native passthrough everywhere)'
Show-State
exit 0
