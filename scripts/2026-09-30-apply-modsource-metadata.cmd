@echo off
mkdir "H:\Windhawk Configuration\backups\2026-09-30" 2>nul
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\Windhawk Configuration\scripts\2026-09-30-apply-modsource-metadata.ps1" > "H:\Windhawk Configuration\backups\2026-09-30\modsource-apply.log" 2>&1
