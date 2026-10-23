# Windhawk [WH] debug-stream capture for the input-death hunt, 2026-10-22.
# Starts the bundled DbgViewMini.exe elevated, filtering the system-wide
# OutputDebugString stream to the [WH] tag (Windhawk engine + mods), writing to a
# timestamped log file. One listener may own the debug capture slot; -Stop frees it.
#
#  -Start  [-LogFile <path>]  start capture (refuses if DbgViewMini already runs)
#  -Stop                      kill the capture
#  -Status                    show whether it runs, log size and tail
# Pure ASCII for PS 5.1.
param(
    [switch]$Start,
    [switch]$Stop,
    [switch]$Status,
    [string]$LogFile = ''
)
$ErrorActionPreference = 'Stop'
$Exe = 'C:\Program Files\Windhawk\UI\resources\app\extensions\windhawk\files\DbgViewMini.exe'

$existing = @(Get-Process -Name 'DbgViewMini' -ErrorAction SilentlyContinue)

if ($Stop) {
    if ($existing.Count -eq 0) { Write-Output 'VERDICT STOP none running'; exit 0 }
    foreach ($p in $existing) { Stop-Process -Id $p.Id -Force }
    Start-Sleep -Milliseconds 500
    Write-Output ("VERDICT STOP OK killed={0}" -f $existing.Count)
    exit 0
}

if ($Status) {
    foreach ($p in $existing) { Write-Output ("running pid={0} start={1:HH:mm:ss}" -f $p.Id, $p.StartTime) }
    if ($LogFile -and (Test-Path $LogFile)) {
        $f = Get-Item $LogFile
        Write-Output ("log {0} bytes={1} lastWrite={2:HH:mm:ss}" -f $f.FullName, $f.Length, $f.LastWriteTime)
        Get-Content $LogFile -Tail 3 | ForEach-Object { Write-Output ("  tail: {0}" -f $_) }
    } elseif ($LogFile) {
        Write-Output ("log missing: {0}" -f $LogFile)
    }
    exit 0
}

if ($Start) {
    if ($existing.Count -gt 0) {
        foreach ($p in $existing) { Write-Output ("already running pid={0}" -f $p.Id) }
        Write-Output 'VERDICT START SKIP (already running)'
        exit 3
    }
    if (-not $LogFile) {
        $LogFile = Join-Path 'H:\System Configuration\work\reports' ("windhog-dbgview-{0:HHmmss}.txt" -f (Get-Date))
    }
    $dir = Split-Path $LogFile -Parent
    if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }

    # Detached .cmd wrapper redirect: cmd runs DbgViewMini in the foreground, so the
    # redirect handle lives with the capture process even after the launcher exits.
    $cmdFile = Join-Path $env:TEMP ("dbgview-capture-{0:HHmmss}.cmd" -f (Get-Date))
    $line = '"{0}" --pattern "[WH] *" --no-buffering > "{1}" 2>&1' -f $Exe, $LogFile
    Set-Content -Path $cmdFile -Value $line -Encoding ascii
    $p = Start-Process -FilePath $cmdFile -WindowStyle Hidden -PassThru
    Start-Sleep -Seconds 3
    $now = @(Get-Process -Name 'DbgViewMini' -ErrorAction SilentlyContinue)
    if ($now.Count -eq 0) { Write-Output "VERIFY FAILED DbgViewMini not running after start"; exit 6 }
    $size = 0
    if (Test-Path $LogFile) { $size = (Get-Item $LogFile).Length }
    foreach ($d in $now) { Write-Output ("capture pid={0} log={1} bytes={2}" -f $d.Id, $LogFile, $size) }
    Write-Output 'VERDICT START OK'
    exit 0
}

Write-Output 'VERIFY REFUSED no -Start / -Stop / -Status switch given'
exit 1
