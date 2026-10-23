# Apply/Audit/Rollback for smart-process-priority-ram-optimizer settings.
# Run Apply/Rollback elevated (Invoke-Elevated.ps1). Audit works un-elevated.
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet('Audit', 'Apply', 'Rollback')]
    [string]$Action
)

$ErrorActionPreference = 'Stop'
$cli    = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$modId  = 'smart-process-priority-ram-optimizer'
$backup = Join-Path (Split-Path $PSScriptRoot -Parent) 'backups\2026-10-21-smart-priority-ram\mod-settings-backup.reg'

# Immunity list: author defaults + protected audio/VPN chain (verified installed exe names).
$excl = 'explorer.exe, windhk.exe, dwm.exe, csrss.exe, lsass.exe, smss.exe, services.exe, system, wininit.exe, winlogon.exe, logonui.exe, lockapp.exe, consent.exe, credentialuibroker.exe, smartscreen.exe, svchost.exe, memcompression, registry, fontdrvhost.exe, audiodg.exe, sihost.exe, taskhostw.exe, ctfmon.exe, wlanext.exe, dashost.exe, syntpenh.exe, syntphelper.exe, etdcontrol.exe, etdctrl.exe, alpspad.exe, hcontrol.exe, wireguard.exe, openvpn.exe, tailscale.exe, splwow64.exe, printfilterpipelinesvc.exe, spoolsv.exe, wudfhost.exe, devicecensus.exe, mullvad vpn.exe, ableton live 12 suite.exe, push2displayprocess.exe, push3.exe, vbaudiomatrix.exe, vbaudiomatrix_x64.exe, vbaudiomatrixcoconut.exe, vbaudiomatrixcoconut_x64.exe, vbmatrixvaio_controlpanel.exe, streamdeck.exe'

if ($Action -eq 'Audit') {
    Write-Output "=== current settings ==="
    & $cli mod settings get $modId --json
    Write-Output "=== reg marker ==="
    reg query "HKLM\SOFTWARE\Windhawk\Engine\Mods\$modId" /v SettingsChangeTime
    exit 0
}

if ($Action -eq 'Apply') {
    & $cli mod settings set $modId enableEcoQosManagement=false enableDynamicPowerPlan=false "excludedProcesses=$excl"
    $code = $LASTEXITCODE
    Write-Output "cli-exit=$code"
    if ($code -ne 0) { exit 1 }
    Write-Output "=== post-apply settings ==="
    & $cli mod settings get $modId --json
    reg query "HKLM\SOFTWARE\Windhawk\Engine\Mods\$modId" /v SettingsChangeTime
    exit 0
}

if ($Action -eq 'Rollback') {
    if (-not (Test-Path $backup)) { Write-Error "backup missing: $backup"; exit 1 }
    reg import $backup
    if ($LASTEXITCODE -ne 0) { exit 1 }
    Write-Output "rolled back from $backup"
    exit 0
}
