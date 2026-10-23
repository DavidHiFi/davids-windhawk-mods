# Materialize restartOnSave=1 (the toggle the 2.0.7 schema adds; a value the
# interface never saved yet), then run one marker-only bump and watch whether
# the interface closes+reopens. Disambiguates the missing-default value from
# any other drop in the relaunch path.
param([int]$PreWaitSec = 3)
$ErrorActionPreference = 'Continue'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$helperLog = Join-Path $env:TEMP 'wh-styler-helper.log'
$debugLog = Join-Path $env:TEMP 'wh-styler-debug.log'
$helperLen = (Get-Item $helperLog -ErrorAction SilentlyContinue).Length
$debugLen = (Get-Item $debugLog -ErrorAction SilentlyContinue).Length

Set-ItemProperty "$key\Settings" -Name 'restartOnSave' -Value 1
"0s: restartOnSave materialized as 1 (REG_DWORD)"
if ($PreWaitSec -gt 0) { Start-Sleep -Seconds $PreWaitSec }

$beforePids = @((Get-CimInstance Win32_Process -Filter "Name='windhawk-ui.exe'" -ErrorAction SilentlyContinue).ProcessId)
"before: ui=[$($beforePids -join ',')]"
Set-ItemProperty $key -Name 'SettingsChangeTime' -Value ([int][DateTimeOffset]::Now.ToUnixTimeSeconds())
"marker bumped (restart-on-save test, no value change)"

$newPids = ''
$dl = (Get-Date).AddSeconds(45)
while ((Get-Date) -lt $dl) {
    Start-Sleep -Milliseconds 750
    $now = @((Get-CimInstance Win32_Process -Filter "Name='windhawk-ui.exe'" -ErrorAction SilentlyContinue).ProcessId)
    if ($now.Count -gt 0 -and (($now -join ',') -ne ($beforePids -join ','))) { $newPids = ($now -join ','); break }
}
"ui pair replaced -> [$newPids]"

$dl2 = (Get-Date).AddSeconds(40)
$port = $false
while ((Get-Date) -lt $dl2) {
    $l = netstat -ano | Select-String '127\.0\.0\.1:9333\s' | Select-String 'LISTENING'
    if ($l) { $port = $true; break }
    Start-Sleep -Milliseconds 800
}
"cdp listener=$port"

"helper log (new lines):"
if ($helperLen) { Get-Content $helperLog | Select-Object -Skip 0 | Out-Null }
$all = Get-Content $helperLog -ErrorAction SilentlyContinue
$allPos = if ($helperLen) { $all.Count } else { 0 }
$all | Select-Object -Last ([Math]::Max(0, $all.Count - $allPos + 0)) | Out-Null
$all | Select-Object -Last 14 | ForEach-Object { "  $_" }
"debug log (new lines):"
$dtail = Get-Content $debugLog -ErrorAction SilentlyContinue
$dtail | Select-Object -Last 14 | ForEach-Object { "  $_" }
