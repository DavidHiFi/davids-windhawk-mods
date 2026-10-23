# Windhawk per-mod logging toggle for the input-death hunt, 2026-10-22.
# -Audit    read-only: list per-mod LoggingEnabled/DebugLoggingEnabled bits, write receipt.
# -Apply    write LoggingEnabled=1 on every installed mod key. Refuses while the
#           engine is running (the write hot-reloads mods mid-experiment) unless -Force.
#           Exports the Mods registry tree first; writes a receipt for -Rollback.
# -Rollback delete the LoggingEnabled values listed in the receipt (only ones this
#           script created; values that already existed are left alone).
# Run elevated (HKLM writes). Pure ASCII for PS 5.1.
param(
    [switch]$Audit,
    [switch]$Apply,
    [switch]$Rollback,
    [switch]$Force,
    [string]$ReceiptPath = 'H:\Windhawk Configuration\backups\2026-10-22\log-enable\receipt.json',
    [string]$BackupDir   = 'H:\Windhawk Configuration\backups\2026-10-22\log-enable'
)
$ErrorActionPreference = 'Stop'
$ModsKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'

function Get-EngineState {
    $procs = @(Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue)
    $svc = Get-Service -Name 'Windhawk' -ErrorAction SilentlyContinue
    [pscustomobject]@{
        Procs = $procs.Count
        ServiceStatus = if ($svc) { $svc.Status.ToString() } else { 'NotFound' }
        StartType = if ($svc) { $svc.StartType.ToString() } else { 'NotFound' }
    }
}

function Read-ModBits {
    Get-ChildItem $ModsKey | ForEach-Object {
        $p = Get-ItemProperty $_.PSPath
        [pscustomobject]@{
            Id = $_.PSChildName
            LoggingEnabled = if ($null -ne $p.LoggingEnabled) { ($p.LoggingEnabled -ne 0) } else { $null }
            DebugLoggingEnabled = if ($null -ne $p.DebugLoggingEnabled) { ($p.DebugLoggingEnabled -ne 0) } else { $null }
            Disabled = [int]($p.Disabled -ne $null -and $p.Disabled -ne 0)
        }
    }
}

$mode = if ($Audit) { 'audit' } elseif ($Apply) { 'apply' } elseif ($Rollback) { 'rollback' } else { 'none' }

if ($mode -eq 'audit') {
    $bits = Read-ModBits
    $set = @($bits | Where-Object { $_.LoggingEnabled -eq $true })
    $dbg = @($bits | Where-Object { $_.DebugLoggingEnabled -eq $true })
    $dis = @($bits | Where-Object { $_.Disabled -eq 1 })
    $st = Get-EngineState
    $summary = [ordered]@{
        time = (Get-Date).ToString('yyyy-MM-ddTHH:mm:ss')
        mods = $bits.Count
        loggingEnabledOn = @($set | ForEach-Object { $_.Id })
        debugLoggingEnabledOn = @($dbg | ForEach-Object { $_.Id })
        disabledMods = @($dis | ForEach-Object { $_.Id })
        engine = @{ procs = $st.Procs; service = $st.ServiceStatus; startType = $st.StartType }
    }
    $summary | ConvertTo-Json -Depth 4
    Write-Output ("VERDICT AUDIT OK mods={0} loggingOn={1} debugOn={2} disabled={3} engineProcs={4} service={5}" -f $bits.Count, $set.Count, $dbg.Count, $dis.Count, $st.Procs, $st.ServiceStatus)
    exit 0
}

if ($mode -eq 'apply') {
    $st = Get-EngineState
    if (($st.Procs -gt 0 -or $st.ServiceStatus -eq 'Running') -and -not $Force) {
        Write-Output ("VERIFY REFUSED engine alive: procs={0} service={1}. Run -Apply -Force only with key owner approval." -f $st.Procs, $st.ServiceStatus)
        exit 4
    }
    New-Item -ItemType Directory -Force -Path $BackupDir | Out-Null
    $regFile = Join-Path $BackupDir 'Mods-tree-before-enable.reg'
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods' $regFile /y | Out-Null
    if (-not (Test-Path $regFile)) { Write-Output 'VERIFY REFUSED backup export failed'; exit 5 }

    $mods = Read-ModBits
    $existing = @{}
    foreach ($m in $mods) { $existing[$m.Id] = $m.LoggingEnabled }
    $writes = 0
    $already = @()
    foreach ($id in $existing.Keys) {
        if ($null -eq $existing[$id]) {
            New-ItemProperty -Path (Join-Path $ModsKey $id) -Name 'LoggingEnabled' -PropertyType DWord -Value 1 -Force | Out-Null
            $writes++
        } else {
            $already += $id
        }
    }
    $verified = @((Read-ModBits | Where-Object { $_.LoggingEnabled -eq $true }))
    $receipt = [ordered]@{
        time = (Get-Date).ToString('yyyy-MM-ddTHH:mm:ss')
        action = 'set LoggingEnabled=1'
        wroteOn = @($writes)
        alreadyOn = $already
        setBy = 'e4c9ed97 thread, user-approved go 2026-10-22'
        backupFile = $regFile
    }
    New-Item -ItemType Directory -Force -Path (Split-Path $ReceiptPath -Parent) | Out-Null
    $receipt | ConvertTo-Json -Depth 3 | Set-Content -Path $ReceiptPath -Encoding ascii
    Write-Output ("VERDICT APPLY OK wrote={0} alreadyOn={1} verifiedOn={2}" -f $writes, $already.Count, $verified.Count)
    exit 0
}

if ($mode -eq 'rollback') {
    $st = Get-EngineState
    if (($st.Procs -gt 0 -or $st.ServiceStatus -eq 'Running') -and -not $Force) {
        Write-Output ("VERIFY REFUSED engine alive: procs={0} service={1}. Rollback at a boundary." -f $st.Procs, $st.ServiceStatus)
        exit 4
    }
    if (-not (Test-Path $ReceiptPath)) { Write-Output 'VERIFY REFUSED no receipt found for rollback'; exit 5 }
    $receipt = Get-Content $ReceiptPath -Raw | ConvertFrom-Json
    $mods = Read-ModBits
    $bitIndex = @{}
    foreach ($m in $mods) { $bitIndex[$m.Id] = $m.LoggingEnabled }
    $deleted = 0
    foreach ($pair in $receipt.values.PSObject.Properties) {
        $id = $pair.Name
        $priorState = $pair.Value.state
        if ($priorState -eq 'absent' -and $bitIndex[$id] -eq $true) {
            Remove-ItemProperty -Path (Join-Path $ModsKey $id) -Name 'LoggingEnabled'
            $deleted++
        }
    }
    $left = @((Read-ModBits | Where-Object { $_.LoggingEnabled -eq $true }))
    Write-Output ("VERDICT ROLLBACK OK deleted={0} stillOn={1}" -f $deleted, $left.Count)
    exit 0
}

Write-Output 'VERIFY REFUSED no -Audit / -Apply / -Rollback switch given'
exit 1
