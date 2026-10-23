@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& 'H:\Windhawk Configuration\scripts\2026-10-04-window-manager.ps1' -Audit; Get-CimInstance Win32_Process -Filter \"Name='windhawk.exe'\" | ForEach-Object { '{0} {1} {2}' -f $_.ProcessId, $_.CreationDate, $_.CommandLine }" > "H:\Windhawk Configuration\reports\2026-10-04-window-manager\audit.log" 2>&1
