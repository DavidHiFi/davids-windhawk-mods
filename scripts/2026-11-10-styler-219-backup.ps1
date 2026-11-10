# Styler 2.1.8: back up the mod registry key and live source before install. Run elevated.
$ErrorActionPreference = 'Stop'
$bak = 'H:\Windhawk Configuration\backups\2026-11-10-styler-219'
New-Item -ItemType Directory -Force $bak | Out-Null
reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-enhanced-styler' "$bak\mod-key.reg" /y | Out-Null
Copy-Item 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-enhanced-styler.wh.cpp' "$bak\live.wh.cpp" -Force
Get-ChildItem $bak | ForEach-Object { "$($_.Name) $($_.Length)" }
