# Windhawk engine restore - Audit / Rollback companion (2026-10-22).
# Pairs with work\2026-10-22-engine-restore\orchestrator.ps1 (the -Install).
#   -Audit    : read-only report of the restore state (no changes).
#   -Rollback : engine off + re-import the pre-restore registry snapshot + stays off.
# ASCII only. Elevated. Self-logging to reports\2026-10-22-engine-restore\.
#Requires -RunAsAdministrator
param(
    [ValidateSet('Audit', 'Rollback')]
    [string]$Mode = 'Audit'
)
$ErrorActionPreference = 'Continue'
$RepDir = 'H:\Windhawk Configuration\work\reports\2026-10-22-engine-restore'
$BakDir = 'H:\Windhawk Configuration\backups\2026-10-22\engine-restore'
$Log = Join-Path $RepDir ('companion-' + $Mode.ToLower() + '.log')
"companion $Mode $(Get-Date -Format 'yyyy-MM-dd hh:mm:ss tt')" | Set-Content $Log -Encoding ascii
function L($m) { ("{0}  {1}" -f (Get-Date -Format 'HH:mm:ss'), $m) | Out-File $Log -Append -Encoding ascii }

$svc = Get-Service Windhawk -ErrorAction SilentlyContinue
L ("service: {0} / {1}" -f $svc.Status, $svc.StartType)
$wh = @(Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue)
L ("windhawk processes: {0}" -f $wh.Count)

$modsRoot = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$enabled = @(Get-ChildItem $modsRoot -ErrorAction SilentlyContinue | Where-Object { (Get-ItemProperty $_.PSPath -ErrorAction SilentlyContinue).Disabled -ne 1 } | ForEach-Object { $_.PSChildName })
$disabled = @(Get-ChildItem $modsRoot -ErrorAction SilentlyContinue | Where-Object { (Get-ItemProperty $_.PSPath -ErrorAction SilentlyContinue).Disabled -eq 1 } | ForEach-Object { $_.PSChildName })
L ("mods enabled: {0}  disabled: {1}" -f $enabled.Count, $disabled.Count)
L ("enabled list: {0}" -f ($enabled -join ', '))

$broken = 'custom-corner-radius','local@simple-window-switcher-plus','local@taskbar-audio-visualizer','local@theme-tool-plus','local@translucent-flyouts','smart-process-priority-ram-optimizer','taskbar-fluent-media-player','windows-11-settings-styler','windows-11-taskbar-styler','uwp-assets-redirect'
foreach ($b in $broken) {
    if (Test-Path (Join-Path $modsRoot $b)) {
        $d = (Get-ItemProperty (Join-Path $modsRoot $b) -ErrorAction SilentlyContinue).Disabled
        if ($d -ne 1) { L ("WARNING: stay-off mod is ENABLED: " + $b) } else { L ("stay-off OK (disabled): " + $b) }
    } else { L ("stay-off absent (removed): " + $b) }
}

if ($Mode -eq 'Rollback') {
    L 'ROLLBACK: stopping engine'
    Stop-Service Windhawk -Force -ErrorAction SilentlyContinue
    Start-Sleep -Seconds 2
    Get-Process | Where-Object { $_.Name -like 'windhawk*' } | Stop-Process -Force -ErrorAction SilentlyContinue
    Start-Sleep -Seconds 3
    $latest = Get-ChildItem $BakDir -Filter 'windhawk-engine-pre-restore-*.reg' | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if ($latest) {
        L ("importing snapshot: " + $latest.FullName)
        $null = reg import $latest.FullName 2>&1
        L ("import exit: {0}" -f $LASTEXITCODE)
        # keep the engine off after rollback regardless of what the snapshot says about StartType
        Set-Service Windhawk -StartupType Manual -ErrorAction SilentlyContinue
    } else { L 'no pre-restore snapshot found - registry untouched' }
    $svc2 = Get-Service Windhawk
    $wh2 = @(Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue)
    L ("post-rollback: service {0}/{1}, processes {2}" -f $svc2.Status, $svc2.StartType, $wh2.Count)
    L ("post-rollback enabled mods: {0}" -f @(Get-ChildItem $modsRoot | Where-Object { (Get-ItemProperty $_.PSPath).Disabled -ne 1 }).Count)
}
L ("companion $Mode done")
