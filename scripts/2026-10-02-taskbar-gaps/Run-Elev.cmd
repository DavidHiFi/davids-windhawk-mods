@echo off
echo %DATE% %TIME% RUN-ELEV >> "H:\System Configuration\scripts\2026-10-02-taskbar-gaps\elev.log"
powershell.exe -NoProfile -NonInteractive -ExecutionPolicy Bypass -File "H:\System Configuration\scripts\2026-10-02-taskbar-gaps\Set-StylerControlStyle.ps1"
set RC=%ERRORLEVEL%
echo %DATE% %TIME% RUN-ELEV exit=%RC% >> "H:\System Configuration\scripts\2026-10-02-taskbar-gaps\elev.log"
exit /b %RC%
