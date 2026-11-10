# Stops the superseded 2.1.6 WaitInstall watcher (2.1.7 replaces it).
Get-CimInstance Win32_Process | Where-Object { $_.CommandLine -like '*styler-216-install*' -and $_.ProcessId -ne $PID } | ForEach-Object { "stop $($_.ProcessId) $($_.Name)"; Stop-Process -Id $_.ProcessId -Force }
"done"
