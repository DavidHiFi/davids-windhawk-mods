@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\windhawk-mixer-repair\Repair-Metadata.ps1" -Install > "H:\System Configuration\reports\2026-09-30\windhawk-mixer-repair\repair.log" 2>&1
