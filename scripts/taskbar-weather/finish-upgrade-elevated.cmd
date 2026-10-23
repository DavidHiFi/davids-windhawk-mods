@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\taskbar-weather\Upgrade.ps1" -Install -Revision 2 > "H:\System Configuration\reports\2026-09-30\taskbar-weather\upgrade-install-final.log" 2>&1
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\taskbar-weather\Install-WeatherMonitor.ps1" >> "H:\System Configuration\reports\2026-09-30\taskbar-weather\upgrade-install-final.log" 2>&1
