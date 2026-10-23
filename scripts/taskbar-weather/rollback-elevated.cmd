@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\taskbar-weather\Install.ps1" -Rollback > "H:\System Configuration\reports\2026-09-30\taskbar-weather\rollback.log" 2>&1
