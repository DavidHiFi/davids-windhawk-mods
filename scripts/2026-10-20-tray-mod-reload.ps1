# 2026-10-20 Tray mod reload — restore right-side tray render after 12:57 PM shell restart
#
# Symptom (measured 6:29 PM, primary taskbar 2560x48 at top):
#   - local@taskbar-ai-quota-plus dashboard absent (config + DLL intact; render missing)
#   - micrographics-taskbar-clock date pills absent (plain date text instead)
#   - taskbar-tray-system-icon-tweaks hiding lost (ENG US / network / bell reappeared)
# Styler rule 63 (margin 9) verified intact and centered - do NOT touch positioning.
# Remedy: hot reload the three mods via the SettingsChangeTime marker. No explorer/engine restart.
# A fullscreen game is running on the primary monitor - nothing may restart explorer.

param([switch]$Audit)

$ErrorActionPreference = 'Stop'
$mods = @(
    'local@taskbar-ai-quota-plus',
    'micrographics-taskbar-clock',
    'taskbar-tray-system-icon-tweaks'
)
$root = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-20-tray-mod-reload'

if ($Audit) {
    foreach ($m in $mods) {
        $p = Get-ItemProperty "$root\$m" -ErrorAction SilentlyContinue
        if ($p) {
            $sct = if ($p.SettingsChangeTime) {
                [DateTimeOffset]::FromUnixTimeSeconds([int]$p.SettingsChangeTime).LocalDateTime.ToString('h:mm:ss tt')
            } else { 'never' }
            "AUDIT {0}: version={1} disabled={2} sct={3}" -f $m, $p.Version, $p.Disabled, $sct
        } else {
            "AUDIT ${m}: KEY MISSING"
        }
    }
    "AUDIT plan: backup 3 mod keys + ModsWritable quota key to '$backupDir', then bump SettingsChangeTime on all three (unix-seconds marker). Hot reload only - no explorer restart, no engine restart."
    exit 0
}

# --- Install: backup first, then bump, then read back ---
New-Item -ItemType Directory -Force -Path $backupDir | Out-Null

foreach ($m in $mods) {
    $dest = Join-Path $backupDir ($m + '.reg')
    reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$m" $dest /y | Out-Null
    if (-not (Test-Path $dest)) { throw "backup export failed: $m" }
    "BACKUP-OK $m -> $dest"
}
$mwDest = Join-Path $backupDir 'modswritable-local@taskbar-ai-quota-plus.reg'
reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\local@taskbar-ai-quota-plus' $mwDest /y | Out-Null
if (-not (Test-Path $mwDest)) { throw 'backup export failed: ModsWritable quota key' }
"BACKUP-OK ModsWritable quota -> $mwDest"

$stamp = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
foreach ($m in $mods) {
    Set-ItemProperty -Path "$root\$m" -Name 'SettingsChangeTime' -Value $stamp -Type DWord
}

foreach ($m in $mods) {
    $v = (Get-ItemProperty "$root\$m").SettingsChangeTime
    "READBACK {0}: SettingsChangeTime={1} (expected {2}) match={3}" -f $m, $v, $stamp, ($v -eq $stamp)
}
"STAMP $stamp"
