@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\taskbar-weather\Test-RefreshInterval.ps1" -Restore > "H:\System Configuration\reports\2026-09-30\taskbar-weather\timer-restore-setting.log" 2>&1
