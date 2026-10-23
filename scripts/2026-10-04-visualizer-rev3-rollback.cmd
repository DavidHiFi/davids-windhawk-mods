@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\Windhawk Configuration\scripts\2026-10-04-visualizer-rev3.ps1" -Rollback > "H:\Windhawk Configuration\reports\2026-10-04-mod-metadata-polish\rollback-visualizer-rev3.log" 2>&1
