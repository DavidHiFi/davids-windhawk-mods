# Evaluate JavaScript in the Windhawk 2.0 UI page through the styler mod's
# CDP port (9333). Usage:
#   .\2026-10-11-styler-listview-cdp.ps1 -Expression "document.title"
#   .\2026-10-11-styler-listview-cdp.ps1 -FromFile script.js
param(
    [string]$Expression,
    [string]$FromFile,
    [int]$Port = 9333
)
$ErrorActionPreference = 'Stop'

if ($FromFile) { $Expression = Get-Content $FromFile -Raw }

$targets = Invoke-RestMethod -Uri "http://127.0.0.1:$Port/json" -TimeoutSec 5
$page = $targets | Where-Object { $_.type -eq 'page' } | Select-Object -First 1
if (-not $page) { throw 'no page target on CDP' }

$ws = [System.Net.WebSockets.ClientWebSocket]::new()
$ct = [System.Threading.CancellationToken]::None
$ws.ConnectAsync([Uri]$page.webSocketDebuggerUrl, $ct).Wait()

function Send-Json([string]$s) {
    $bytes = [System.Text.Encoding]::UTF8.GetBytes($s)
    $seg = [ArraySegment[byte]]::new($bytes)
    $ws.SendAsync($seg, [System.Net.WebSockets.WebSocketMessageType]::Text, $true, $ct).Wait()
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

# JSON-encode the expression so quotes/newlines survive the CDP envelope.
$enc = ConvertTo-Json $Expression -Compress
Send-Json ('{"id":1,"method":"Runtime.evaluate","params":{"expression":' + $enc + ',"returnByValue":true}}')

# Drain frames until our response (skip any events).
$deadline = (Get-Date).AddSeconds(20)
while ((Get-Date) -lt $deadline) {
    $msg = Recv-Json
    $obj = $msg | ConvertFrom-Json
    if ($obj.id -eq 1) {
        $obj.result | ConvertTo-Json -Depth 10
        break
    }
}
$ws.Dispose()
