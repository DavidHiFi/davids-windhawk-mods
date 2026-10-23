# One styler settings save, the way the interface's Save button does it:
# write the value, bump the engine's SettingsChangeTime marker, then watch
# the relaunch helper close+reopen the interface and the CDP port come up.
param(
    [Parameter(Mandatory = $true)][string]$Accent,
    [Parameter(Mandatory = $true)][string]$Label
)
$ErrorActionPreference = 'Continue'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$helperLog = Join-Path $env:TEMP 'wh-styler-helper.log'
$debugLog = Join-Path $env:TEMP 'wh-styler-debug.log'
$helperLen = (Get-Item $helperLog -ErrorAction SilentlyContinue).Length
$debugLen = (Get-Item $debugLog -ErrorAction SilentlyContinue).Length
$start = Get-Date

Set-ItemProperty "$key\Settings" -Name 'accentColor' -Value $Accent
Set-ItemProperty $key -Name 'SettingsChangeTime' -Value ([int][DateTimeOffset]::Now.ToUnixTimeSeconds())
"[$Label] 0s: saved accentColor=$Accent + marker bump"

$beforePids = @((Get-CimInstance Win32_Process -Filter "Name='windhawk-ui.exe'" -ErrorAction SilentlyContinue).ProcessId)
$newPids = ''
$dl = (Get-Date).AddSeconds(45)
while ((Get-Date) -lt $dl) {
    Start-Sleep -Milliseconds 750
    $now = @((Get-CimInstance Win32_Process -Filter "Name='windhawk-ui.exe'" -ErrorAction SilentlyContinue).ProcessId)
    if ($now.Count -gt 0 -and (($now -join ',') -ne ($beforePids -join ','))) { $newPids = ($now -join ','); break }
}
$swapAt = ((Get-Date) - $start).TotalSeconds
"[$Label] {0:n1}s: ui pair replaced -> [$newPids]" -f $swapAt

$dl2 = (Get-Date).AddSeconds(45)
$port = $false
while ((Get-Date) -lt $dl2) {
    $l = netstat -ano | Select-String '127\.0\.0\.1:9333\s' | Select-String 'LISTENING'
    if ($l) { $port = $true; break }
    Start-Sleep -Milliseconds 800
}
$portAt = ((Get-Date) - $start).TotalSeconds
"[$Label] {0:n1}s: cdp listener={1}" -f $portAt, $port

"[$Label] helper log additions:"
if (Test-Path $helperLog) { Get-Content $helperLog | Select-Object -Skip 0 | Out-Null }
$tail = Get-Content $helperLog -ErrorAction SilentlyContinue
$tail | Select-Object -Last 9 | ForEach-Object { "  $_" }
"[$Label] debug log additions:"
$dtail = Get-Content $debugLog -ErrorAction SilentlyContinue
$dtail | Select-Object -Last 8 | ForEach-Object { "  $_" }
