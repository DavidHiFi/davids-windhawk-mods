# Probe OpenCode Go and Grok usage endpoints. Never prints token material.
$out = 'H:\Windhawk Configuration\t3-handoff\scratch\probe-20261018-out.txt'
function Log($m) { $m | Tee-Object -FilePath $out -Append }

"" | Set-Content $out
Log "=== $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') ==="

# --- OpenCode Go ---
$authPath = "$env:USERPROFILE\.local\share\opencode\auth.json"
$auth = Get-Content $authPath -Raw | ConvertFrom-Json
$oc = $auth.'opencode-go'
Log "opencode-go: type=$($oc.type) keylen=$($oc.key.Length)"
$h = @{ Authorization = "Bearer $($oc.key)"; Accept = 'application/json'; 'User-Agent' = 'taskbar-ai-quota/0.1' }
foreach ($u in @('https://opencode.ai/zen/go/v1/usage')) {
    try {
        $r = Invoke-WebRequest -Uri $u -Headers $h -UseBasicParsing -TimeoutSec 25
        Log "GET $u -> $($r.StatusCode)"
        Log $r.Content
    } catch {
        Log "GET $u -> ERROR $($_.Exception.Response.StatusCode.value__) $($_.Exception.Message)"
        try {
            $sr = New-Object IO.StreamReader($_.Exception.Response.GetResponseStream())
            Log $sr.ReadToEnd()
        } catch {}
    }
}

# --- Grok ---
$graw = Get-Content "$env:USERPROFILE\.grok\auth.json" -Raw | ConvertFrom-Json
$entry = $graw.PSObject.Properties | Where-Object { $_.Name -like 'https://auth.x.ai*' } | Select-Object -First 1
$tok = $entry.Value.key
Log "grok token present=$([bool]$tok) len=$($tok.Length)"
$gh = @{ Authorization = "Bearer $tok"; 'x-xai-token-auth' = 'xai-grok-cli'; Accept = 'application/json' }
foreach ($u in @('https://cli-chat-proxy.grok.com/v1/billing?format=credits','https://cli-chat-proxy.grok.com/v1/billing')) {
    try {
        $r = Invoke-WebRequest -Uri $u -Headers $gh -UserAgent 'grok-cli-oauth' -UseBasicParsing -TimeoutSec 25
        Log "GET $u -> $($r.StatusCode)"
        Log $r.Content
    } catch {
        Log "GET $u -> ERROR $($_.Exception.Response.StatusCode.value__) $($_.Exception.Message)"
        try {
            $sr = New-Object IO.StreamReader($_.Exception.Response.GetResponseStream())
            Log $sr.ReadToEnd()
        } catch {}
    }
}
