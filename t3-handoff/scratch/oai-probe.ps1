# Live-probes the OpenAI (free plan) account the way the mod does:
# decrypts auth_* DPAPI blobs from ModsWritable LocalStorage, finds the one
# with a ChatGPT-Account-Id, GETs chatgpt.com/backend-api/wham/usage.
# NEVER prints access/refresh tokens - only metadata and the usage response.
$ErrorActionPreference = 'Stop'
$out = 'H:\Windhawk Configuration\t3-handoff\scratch\oai-probe-out.txt'
function Log($s) { Add-Content -Path $out -Value $s }
Remove-Item $out -ErrorAction SilentlyContinue
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12 -bor [Net.SecurityProtocolType]::Tls13
Add-Type -AssemblyName System.Security

$key = 'HKLM:\SOFTWARE\Windhawk\Engine\ModsWritable\local@taskbar-ai-quota-plus\LocalStorage'
$props = Get-ItemProperty -LiteralPath $key
$authNames = $props.PSObject.Properties.Name | Where-Object { $_ -like 'auth_*' }
Log "auth values: $($authNames.Count)"

foreach ($name in $authNames) {
    $b64 = $props.$name
    try {
        $blob = [Convert]::FromBase64String($b64)
        $plain = [Text.Encoding]::UTF8.GetString(
            [System.Security.Cryptography.ProtectedData]::Unprotect($blob, $null, 'CurrentUser'))
        $j = $plain | ConvertFrom-Json
        $hasAccess = [bool]$j.access; $hasRefresh = [bool]$j.refresh
        Log ("{0}: accountId='{1}' expiresMs={2} hasAccess={3} hasRefresh={4}" -f `
            $name, $j.accountId, $j.expiresMs, $hasAccess, $hasRefresh)
        if ($j.accountId -and $j.access) {
            $h = @{
                Authorization        = "Bearer $($j.access)"
                Origin               = 'https://chatgpt.com'
                Referer              = 'https://chatgpt.com/'
                Accept               = 'application/json'
                'ChatGPT-Account-Id' = $j.accountId
                'User-Agent'         = 'taskbar-ai-quota/0.1'
            }
            try {
                $r = Invoke-WebRequest -Uri 'https://chatgpt.com/backend-api/wham/usage' `
                    -Headers $h -UseBasicParsing -TimeoutSec 25
                Log "WHAM STATUS: $($r.StatusCode)"
                Log $r.Content
            } catch {
                Log "WHAM FAIL: $($_.Exception.Message)"
                if ($_.Exception.Response) {
                    Log "WHAM STATUS: $([int]$_.Exception.Response.StatusCode)"
                }
            }
        }
    } catch {
        Log "${name}: decrypt/parse failed: $($_.Exception.Message)"
    }
}
exit 0
