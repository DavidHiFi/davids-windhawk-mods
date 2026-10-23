param(
    [switch]$Backup,
    [switch]$Apply,
    [switch]$Rollback
)

# Explorer speed dedupe: disable explorer-size-on-disk-column entirely.
# Folder sizes stay in the Size column via explorer-details-better-file-sizes
# (Everything index). This removes the duplicate column and the mod's
# per-file allocation reads on Explorer's UI thread.
#   (no switch)  print current state
#   -Backup      reg export of the mod key only
#   -Apply       backup (if missing) + Disabled=1 + SettingsChangeTime bump + readback
#   -Rollback    remove Disabled + bump + readback

$ErrorActionPreference = 'Stop'
$modId = 'explorer-size-on-disk-column'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$modId"
$regKey = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$modId"
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-13\explorer-speed'
$stamp = Get-Date -Format 'HHmmss'

function Read-Back {
    $p = Get-ItemProperty -Path $key
    $dis = if ($null -ne $p.Disabled) { '{0} (DWord)' -f $p.Disabled } else { '(absent)' }
    '{0}\Disabled = {1}' -f $modId, $dis
    '{0}\SettingsChangeTime = {1} (DWord)' -f $modId, $p.SettingsChangeTime
}

function Export-Backup {
    if (-not (Test-Path -LiteralPath $backupDir)) {
        New-Item -ItemType Directory -Path $backupDir -Force | Out-Null
    }
    $file = Join-Path $backupDir ("$modId-pre-disable-$stamp.reg")
    & reg.exe export $regKey $file /y | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg export failed: $file" }
    "backup: $file"
}

if ($Backup) { Export-Backup; Read-Back; return }

if ($Apply) {
    $existing = Get-ChildItem -LiteralPath $backupDir -Filter "$modId-pre-disable-*.reg" -ErrorAction SilentlyContinue
    if (-not $existing) { Export-Backup }
    Set-ItemProperty -Path $key -Name Disabled -Value 1 -Type DWord
    Set-ItemProperty -Path $key -Name SettingsChangeTime -Value ([int][DateTimeOffset]::Now.ToUnixTimeSeconds()) -Type DWord
    Read-Back
    return
}

if ($Rollback) {
    Remove-ItemProperty -Path $key -Name Disabled -ErrorAction SilentlyContinue
    Set-ItemProperty -Path $key -Name SettingsChangeTime -Value ([int][DateTimeOffset]::Now.ToUnixTimeSeconds()) -Type DWord
    Read-Back
    return
}

Read-Back
