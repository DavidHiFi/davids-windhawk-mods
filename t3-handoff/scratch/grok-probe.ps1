[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12 -bor [Net.SecurityProtocolType]::Tls13
$out = 'H:\Windhawk Configuration\t3-handoff\scratch\grok-probe-out.txt'
function Log($s) { Add-Content -Path $out -Value $s }
Remove-Item $out -ErrorAction SilentlyContinue
try {
  $raw = Get-Content "$env:USERPROFILE\.grok\auth.json" -Raw | ConvertFrom-Json
  $entry = $raw.PSObject.Properties | Where-Object { $_.Name -like 'https://auth.x.ai::*' } | Select-Object -First 1
  $token = $entry.Value.key
  $tokenOk = ($null -ne $token) -and ($token.Length -gt 0)
  Log "token found: $tokenOk"
  $headers = @{ Authorization = "Bearer $token"; "x-xai-token-auth" = "xai-grok-cli"; Accept = "application/json" }
  foreach ($u in @("https://cli-chat-proxy.grok.com/v1/billing?format=credits", "https://cli-chat-proxy.grok.com/v1/billing")) {
    Log "==== GET $u ===="
    try {
      $r = Invoke-WebRequest -Uri $u -Headers $headers -UserAgent "grok-cli-oauth" -UseBasicParsing -TimeoutSec 25
      Log "STATUS: $($r.StatusCode)"
      Log $r.Content
    } catch {
      Log "HTTP FAIL: $($_.Exception.Message)"
      if ($_.Exception.Response) {
        Log "STATUS: $([int]$_.Exception.Response.StatusCode)"
        try { $sr = New-Object IO.StreamReader($_.Exception.Response.GetResponseStream()); Log $sr.ReadToEnd() } catch { Log "no body" }
      }
    }
  }
} catch { Log "FATAL: $($_.Exception.Message)" }