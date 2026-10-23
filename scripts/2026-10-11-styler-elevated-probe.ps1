Write-Output 'probe-ok'
Write-Output "temp=$env:TEMP"
Write-Output "user=$env:USERNAME"
$out = Join-Path $env:TEMP 'styler-probe-child.txt'
Set-Content -Path $out -Value "child wrote this, pid $PID, $(Get-Date -Format 'HH:mm:ss')" -Encoding ascii
Write-Output "childfile=$out"
