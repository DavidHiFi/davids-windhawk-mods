@echo off
echo %DATE% %TIME% RUN-ELEV >> "H:\System Configuration\scripts\2026-10-02-tourne-av\trayfix-elev.log"
powershell.exe -NoProfile -NonInteractive -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\2026-10-02-tourne-av\Set-TrayFix.ps1"
set RC=%ERRORLEVEL%
echo %DATE% %TIME% RUN-ELEV exit=%RC% >> "H:\System Configuration\scripts\2026-10-02-tourne-av\trayfix-elev.log"
exit /b %RC%
