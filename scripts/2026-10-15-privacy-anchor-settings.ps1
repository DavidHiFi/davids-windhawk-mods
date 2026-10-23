# 2026-10-15-privacy-anchor-settings.ps1
# Privacy Indicator Anchor (privacy-indicator-anchor v2.1): make the indicator
# group match the rest of the tray - one row, 16 px icons, 28 px pitch, 10 px
# outer padding - and retheme it in Catppuccin Mocha.
#
#   -Audit     read-only: print current mod settings
#   -Install   export a one-time backup, apply the desired values, bump
#              SettingsChangeTime (mod hot-reloads on the marker)
#   -Rollback  reg import the backup, bump SettingsChangeTime
#
# Run elevated (Invoke-Elevated.ps1). The 48 px taskbar carries 16 px tray
# glyphs in 28 px notification-icon cells (taskbar-notification-icon-spacing),
# so 16 px slots with a 12 px gap reproduce that pitch exactly.
param(
    [switch]$Audit,
    [switch]$Install,
    [switch]$Rollback
)
$ErrorActionPreference = 'Stop'

$Key        = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\privacy-indicator-anchor'
$Settings   = "$Key\Settings"
$BackupDir  = 'H:\Windhawk Configuration\backups\2026-10-15-privacy-anchor'
$BackupFile = Join-Path $BackupDir 'privacy-indicator-anchor-before-2026-10-15.reg'

# Changed on 2026-10-15. Everything else (position, content toggles, item size,
# vertical padding, offsets, opacities, slash direction/opacity, glow on/speed,
# camera hardware detection, native-indicator suppression) is left at its
# existing value.
$Desired = [ordered]@{
    'Layout.Arrangement'    = 'location | mic | camera | copilot'  # single row, was 'auto' (2x2 block)
    'Size.ItemSpacing'      = 12                                    # 16+12 = 28 px pitch, matches tray cells
    'Adjust.PadX'           = 10                                    # outer seams were ~2 px; +10 both sides -> ~12 px rhythm
    'Surface.IdleColor'     = '#A6ADC8'                             # Catppuccin Mocha Subtext0
    'Surface.IdleOpacity'   = 60
    'Surface.ActiveColor'   = '#F38BA8'                             # Catppuccin Mocha Red
    'Surface.DisabledColor' = '#6C7086'                             # Catppuccin Mocha Overlay0
    'Surface.SlashColor'    = '#F38BA8'                             # Catppuccin Mocha Red
    'Surface.GlowStyle'     = 'steady'                              # was 'radiate' at 220% reach - the bloat
    'Surface.GlowColor'     = '#F38BA8'                             # Catppuccin Mocha Red
    'Surface.GlowOpacity'   = 25
    'Surface.GlowSize'      = 130
}

function Get-SettingsNow {
    reg query $Settings
}

function Bump-Marker {
    $b = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    reg add $Key /v SettingsChangeTime /t REG_DWORD /d $b /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw 'SettingsChangeTime bump failed' }
    Write-Output "SettingsChangeTime=$b"
}

if ($Audit) {
    Get-SettingsNow
    exit 0
}

if ($Install) {
    New-Item -ItemType Directory -Force -Path $BackupDir | Out-Null
    if (-not (Test-Path $BackupFile)) {
        reg export $Key $BackupFile /y | Out-Null
        if (-not (Test-Path $BackupFile) -or (Get-Item $BackupFile).Length -lt 500) {
            throw "backup export failed: $BackupFile"
        }
        Write-Output "Backup exported: $BackupFile"
    } else {
        Write-Output "Backup already present, kept as-is: $BackupFile"
    }
    foreach ($e in $Desired.GetEnumerator()) {
        $v = $e.Value
        if ($v -is [int]) {
            reg add $Settings /v $e.Key /t REG_DWORD /d $v /f | Out-Null
        } else {
            reg add $Settings /v $e.Key /t REG_SZ /d $v /f | Out-Null
        }
        if ($LASTEXITCODE -ne 0) { throw "reg add failed: $($e.Key)" }
    }
    Bump-Marker
    Write-Output 'PIA-INSTALL-OK'
    Get-SettingsNow
    exit 0
}

if ($Rollback) {
    if (-not (Test-Path $BackupFile)) { throw "backup missing: $BackupFile" }
    reg import $BackupFile
    if ($LASTEXITCODE -ne 0) { throw 'reg import failed' }
    Bump-Marker
    Write-Output 'PIA-ROLLBACK-OK'
    exit 0
}

Write-Output 'No mode given. Use -Audit, -Install or -Rollback.'
