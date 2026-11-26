# Daily Windhawk store check. The laptop job `windhawk-new-mods` runs this on the tower over ssh.
# Installed copy: %LOCALAPPDATA%\store-watch\daily.ps1, next to store-watch.exe (no spaces in the path,
# so the ssh command needs no nested quotes). Source: H:\Windhawk Configuration\scripts\store-watch-daily.ps1.
#
#   daily.ps1                      check the store, refresh the queue, print the summary and top pick
#   daily.ps1 -Mark <id>           record that an agent took this mod (handled)
#   daily.ps1 -Mark <id> -As skipped
#
# Last line is always `exit N`: 0 ok, 2 tool missing, anything else = the tool's own error.
param(
    [string]$Mark = '',
    [ValidateSet('handled', 'skipped')][string]$As = 'handled'
)
$ErrorActionPreference = 'Continue'
$exe = Join-Path $PSScriptRoot 'store-watch.exe'
$dir = 'H:\Windhawk Configuration\reports\store-watch'
$coop = 'H:\System Configuration\agent-tools\AgentCoop\coop.py'

if (-not (Test-Path $exe)) { 'error: store-watch.exe is missing next to daily.ps1'; 'exit 2'; exit 2 }

if ($Mark) {
    (& $exe mark $Mark $As --out $dir 2>&1 | Out-String).Trim()
    $code = $LASTEXITCODE
    "exit $code"; exit $code
}

$summary = (& $exe run --state $dir --out $dir 2>&1 | Out-String).Trim()
$code = $LASTEXITCODE
$summary
if ($code -ne 0) { "exit $code"; exit $code }

$top = (& $exe top --state $dir --out $dir 2>&1 | Out-String).Trim()
"top: $top"

if ($summary -notmatch ':\s*0 new, 0 upstream') {
    $env:COOP_AGENT = 'store-watch'
    try {
        & python -I $coop note -C 'H:\Windhawk Configuration' --tag finding `
            "Windhawk store check: $summary. Queue: reports\store-watch\queue.md" 2>&1 | Out-Null
    } catch { }
}
'exit 0'
