# Last completeness check: dump every key path in the full /v1/user response
# and flag anything limit/rate/percent/credit related. Prints no token.
$ErrorActionPreference = 'Stop'
$out = 'H:\Windhawk Configuration\t3-handoff\scratch\grok-user-out.txt'
function Log($s) { Add-Content -Path $out -Value $s }
Remove-Item $out -ErrorAction SilentlyContinue
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12 -bor [Net.SecurityProtocolType]::Tls13
$raw = Get-Content "$env:USERPROFILE\.grok\auth.json" -Raw | ConvertFrom-Json
$entry = $raw.PSObject.Properties | Where-Object { $_.Name -like 'https://auth.x.ai::*' } | Select-Object -First 1
$headers = @{ Authorization = "Bearer $($entry.Value.key)"; "x-xai-token-auth" = "xai-grok-cli"; Accept = "application/json" }
$r = Invoke-WebRequest -Uri 'https://cli-chat-proxy.grok.com/v1/user' -Headers $headers -UserAgent "grok-cli-oauth" -UseBasicParsing -TimeoutSec 20
$j = $r.Content | ConvertFrom-Json
function Walk($obj, $path) {
    if ($obj -is [System.Management.Automation.PSCustomObject]) {
        foreach ($p in $obj.PSObject.Properties) { Walk $p.Value "$path.$($p.Name)" }
    } elseif ($obj -is [System.Array]) {
        for ($i = 0; $i -lt $obj.Count; $i++) { Walk $obj[$i] "$path[$i]" }
    } else {
        Log "$path = $obj"
    }
}
Walk $j 'user'
Log '--- limit/rate/credit/percent hits:'
($r.Content | Select-String -Pattern 'limit|rate|credit|percent|quota' -AllMatches).Matches.Value | Sort-Object -Unique | ForEach-Object { Log "  $_" }
exit 0
