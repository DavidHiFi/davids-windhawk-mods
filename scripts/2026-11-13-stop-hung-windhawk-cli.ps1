# Stops one hung windhawk-cli.exe left by an install (pid passed in), only if it is that program.
param([Parameter(Mandatory)][int]$ProcessId)
$p = Get-Process -Id $ProcessId -ErrorAction SilentlyContinue
if (-not $p -or $p.ProcessName -ne "windhawk-cli") { "not windhawk-cli, nothing done"; exit 2 }
"stopping windhawk-cli $ProcessId, started $($p.StartTime)"
Stop-Process -Id $ProcessId -Force
Start-Sleep 1
if (Get-Process -Id $ProcessId -ErrorAction SilentlyContinue) { "still running"; exit 1 } else { "stopped"; exit 0 }
