@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\taskbar-weather\Activate-Revision.ps1" -UpdateMinutes 1 > "H:\System Configuration\reports\2026-09-30\taskbar-weather\activate-test.log" 2>&1
