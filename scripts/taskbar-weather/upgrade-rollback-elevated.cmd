@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\taskbar-weather\Upgrade.ps1" -Rollback > "H:\System Configuration\reports\2026-09-30\taskbar-weather\upgrade-rollback.log" 2>&1
