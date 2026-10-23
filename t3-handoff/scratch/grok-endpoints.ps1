# Bounded research: (1) extract every /v1/... path string from the grok CLI
# binary, (2) live-probe plausible usage/limit endpoints with the CLI token.
# Prints no token material. Output -> t3-handoff\scratch\grok-endpoints-out.txt
$ErrorActionPreference = 'Continue'
$out = 'H:\Windhawk Configuration\t3-handoff\scratch\grok-endpoints-out.txt'
function Log($s) { Add-Content -Path $out -Value $s }
Remove-Item $out -ErrorAction SilentlyContinue
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12 -bor [Net.SecurityProtocolType]::Tls13

# --- 1. endpoint strings from the binary ---
$bin = "$env:USERPROFILE\.grok\bin\grok.exe"
if (Test-Path $bin) {
    Log ("binary: {0} ({1:N0} B)" -f $bin, (Get-Item $bin).Length)
    $bytes = [IO.File]::ReadAllBytes($bin)
    $text = [Text.Encoding]::ASCII.GetString($bytes)
    $bytes = $null
    $matches = [regex]::Matches($text, '/v1/[A-Za-z0-9_./-]{2,60}')
    $uniq = $matches | ForEach-Object { $_.Value } | Sort-Object -Unique
    Log ("unique /v1/ paths: {0}" -f $uniq.Count)
    $uniq | ForEach-Object { Log "  $_" }
    # also grab non-v1 API-ish paths mentioning limit/usage
    $m2 = [regex]::Matches($text, '"(/[A-Za-z0-9_./-]*(limit|usage|quota)[A-Za-z0-9_./-]*)"')
    $u2 = $m2 | ForEach-Object { $_.Groups[1].Value } | Sort-Object -Unique
    Log "limit/usage paths:"
    $u2 | ForEach-Object { Log "  $_" }
    $text = $null
} else {
    Log "binary not found: $bin"
}

# --- 2. live probes ---
try {
    $raw = Get-Content "$env:USERPROFILE\.grok\auth.json" -Raw | ConvertFrom-Json
    $entry = $raw.PSObject.Properties | Where-Object { $_.Name -like 'https://auth.x.ai::*' } | Select-Object -First 1
    $token = $entry.Value.key
    $tokenOk = ($null -ne $token) -and ($token.Length -gt 0)
    Log "token found: $tokenOk"
    if ($tokenOk) {
        $headers = @{ Authorization = "Bearer $token"; "x-xai-token-auth" = "xai-grok-cli"; Accept = "application/json" }
        foreach ($p in @('/v1/usage', '/v1/rate-limits', '/v1/limits', '/v1/user', '/v1/api-key', '/v1/team')) {
            $u = "https://cli-chat-proxy.grok.com$p"
            try {
                $r = Invoke-WebRequest -Uri $u -Headers $headers -UserAgent "grok-cli-oauth" -UseBasicParsing -TimeoutSec 15
                $body = $r.Content; if ($body.Length -gt 400) { $body = $body.Substring(0, 400) + ' ...' }
                Log "GET $p -> $($r.StatusCode): $body"
            } catch {
                $code = 'n/a'
                if ($_.Exception.Response) { $code = [int]$_.Exception.Response.StatusCode }
                Log "GET $p -> FAIL ($code)"
            }
        }
    }
} catch { Log "probe fatal: $($_.Exception.Message)" }
exit 0
