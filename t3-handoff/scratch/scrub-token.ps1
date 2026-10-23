# Scrub echoed Grok JWT tokens from elevated-run logs (hygiene fix, 2026-10-16).
$targets = @(
    'H:\System Configuration\backups\2026-10-16-elevated\log-011145.txt'
) + (Get-ChildItem 'H:\System Configuration\backups\2026-10-16-elevated' -Filter '*.txt' -ErrorAction SilentlyContinue |
    Select-Object -ExpandProperty FullName)
$pattern = 'eyJ[A-Za-z0-9_\-]{20,}\.[A-Za-z0-9_\-]{20,}\.[A-Za-z0-9_\-]{20,}'
$scrubbed = @()
foreach ($f in ($targets | Select-Object -Unique)) {
    if (-not (Test-Path $f)) { continue }
    $text = Get-Content $f -Raw
    $new = [regex]::Replace($text, $pattern, '[scrubbed-jwt]')
    if ($new -ne $text) {
        Set-Content -Path $f -Value $new -NoNewline -Encoding utf8
        $scrubbed += $f
    }
}
if ($scrubbed) { "SCRUBBED:"; $scrubbed } else { "no tokens found" }
