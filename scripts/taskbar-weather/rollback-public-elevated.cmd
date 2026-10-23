@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\taskbar-weather\Rollback-PublicRevision.ps1" -Apply > "H:\System Configuration\reports\2026-09-30\taskbar-weather\rollback-public.log" 2>&1
