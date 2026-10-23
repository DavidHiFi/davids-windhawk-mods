@echo off
reg.exe import "H:\System Configuration\backups\2026-10-02-taskbar-gaps\fix-controlstyle59.reg"
echo REG-IMPORT exit=%ERRORLEVEL%>> "H:\System Configuration\backups\2026-10-02-taskbar-gaps\import.log"
