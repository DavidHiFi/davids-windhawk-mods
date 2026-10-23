# Rollback for 2026-10-13 Steam bubble fix (disables taskbar-blob-shape).
param([switch]$Rollback)
$ErrorActionPreference = 'Stop'
$key = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\taskbar-blob-shape'
if ($Rollback) {
  $cmd = "reg add '$key' /v Disabled /t REG_DWORD /d 0 /f"
  powershell -NoProfile -ExecutionPolicy Bypass -File 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -Command $cmd
  Write-Output 'Rolled back: taskbar-blob-shape re-enabled (Disabled=0).'
} else {
  Write-Output 'No action. Use -Rollback to re-enable taskbar-blob-shape.'
}
