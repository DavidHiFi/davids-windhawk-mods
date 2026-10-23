param([string]$Id)
$ErrorActionPreference = 'Stop'
$out = & "C:\Program Files\Windhawk\windhawk-cli.exe" mod compile $Id --json 2>&1
$out
Write-Output "cli-exit=$LASTEXITCODE"
if ($LASTEXITCODE -ne 0) { exit 1 }
