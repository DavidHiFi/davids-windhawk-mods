# Read-only: reports the state of one process (threads, wait reasons, exit status, modules).
param([Parameter(Mandatory)][int]$ProcessId)
$p = Get-Process -Id $ProcessId -ErrorAction SilentlyContinue
if (-not $p) { "no process $ProcessId"; exit 2 }
"name $($p.ProcessName) start $($p.StartTime) exited $($p.HasExited) handles $($p.HandleCount) ws $($p.WorkingSet64)"
try { "exitcode $($p.ExitCode)" } catch { "exitcode n/a" }
$p.Threads | ForEach-Object { "thread $($_.Id) $($_.ThreadState) $($_.WaitReason)" }
try { $p.Modules | ForEach-Object { "module $($_.ModuleName)" } } catch { "modules: $($_.Exception.Message)" }
