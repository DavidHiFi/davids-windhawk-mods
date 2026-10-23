# Retry of the styler live re-pull with in-loop diagnostics.
# Distinguishes: UI never started / UI died during wait / UI alive but no CDP.

$ErrorActionPreference = 'Continue'
$env:WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS = '--remote-debugging-port=9333'
$p = Start-Process 'C:\Program Files\Windhawk\windhawk-ui.exe' -PassThru
Write-Output "launched pid=$($p.Id)"

$deadline = (Get-Date).AddSeconds(90)
$page = $null
$lastAlive = "unknown"
while ((Get-Date) -lt $deadline) {
    Start-Sleep -Milliseconds 2000
    $alive = Get-Process -Id $p.Id -ErrorAction SilentlyContinue
    if (-not $alive) { $lastAlive = "DIED at $((Get-Date).ToString('HH:mm:ss'))"; Write-Output $lastAlive; break }
    $lastAlive = "alive"
    try {
        $targets = Invoke-RestMethod -Uri "http://127.0.0.1:9333/json" -TimeoutSec 3
        $page = $targets | Where-Object { $_.type -eq 'page' -and $_.url -like '*tauri.localhost*' } | Select-Object -First 1
    } catch {}
    if ($page) { break }
}
Write-Output "wait-end state: process=$lastAlive, page=$(if ($page) { $page.url } else { 'none' })"
if (-not $page) { Write-Output "RESULT: no CDP page"; exit 1 }

$ws = [System.Net.WebSockets.ClientWebSocket]::new()
$ct = [System.Threading.CancellationToken]::None
$ws.ConnectAsync([Uri]$page.webSocketDebuggerUrl, $ct).Wait()

function Send-Json([string]$s) {
    $bytes = [System.Text.Encoding]::UTF8.GetBytes($s)
    $ws.SendAsync([ArraySegment[byte]]::new($bytes), [System.Net.WebSockets.WebSocketMessageType]::Text, $true, $ct).Wait()
}
function Recv-Json {
    $buf = New-Object byte[] (4MB)
    $ms = [System.IO.MemoryStream]::new()
    do {
        $seg = [ArraySegment[byte]]::new($buf)
        $r = $ws.ReceiveAsync($seg, $ct).Result
        if ($r.MessageType -eq [System.Net.WebSockets.WebSocketMessageType]::Close) { throw 'closed' }
        $ms.Write($buf, 0, $r.Count)
    } while (-not $r.EndOfMessage)
    [System.Text.Encoding]::UTF8.GetString($ms.ToArray())
}
function Invoke-Eval([string]$expr) {
    $script:nextId++
    $enc = ConvertTo-Json $expr -Compress
    Send-Json ('{"id":' + $script:nextId + ',"method":"Runtime.evaluate","params":{"expression":' + $enc + ',"returnByValue":true}}')
    $dl = (Get-Date).AddSeconds(15)
    while ((Get-Date) -lt $dl) {
        $obj = (Recv-Json) | ConvertFrom-Json
        if ($obj.id -eq $script:nextId) { return $obj.result.result.value }
    }
}
$script:nextId = 0

$js = @'
(() => { const st = document.getElementById('wh-styler-style'); if (!st) return JSON.stringify({missing:true});
  const t = st.textContent;
  return JSON.stringify({len: t.length, text: t});
})()
'@
$raw = Invoke-Eval $js
if ($raw -eq $null -or $raw -eq '') { Write-Output "RESULT: empty eval response"; exit 1 }
$info = $raw | ConvertFrom-Json
if ($info.missing) { Write-Output "RESULT: style tag missing from page"; exit 1 }
$t = $info.text
$sha = [System.BitConverter]::ToString([System.Security.Cryptography.SHA256]::HashData([System.Text.Encoding]::UTF8.GetBytes($t))).Replace('-','')
Write-Output ("RESULT: len=" + $info.len + " sha256=" + $sha)
Write-Output ("hasRingRule=" + ($t -like '*::after*') + " hasRibbon=" + $t.Contains('ant-ribbon') + " hasTable=" + $t.Contains('.ant-table'))
$ws.Dispose()
