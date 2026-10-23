# Backup before Grok usage-display fix, 2026-10-16.
# Copies the mod source, the live 1.8.1.0 DLL, and both registry keys.
$ErrorActionPreference = 'Stop'
$dst = 'H:\Windhawk Configuration\backups\2026-10-16-ai-quota-grok'
New-Item -ItemType Directory -Force -Path $dst | Out-Null

Copy-Item 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-ai-quota-plus.wh.cpp' `
    (Join-Path $dst 'local@taskbar-ai-quota-plus.wh.cpp') -Force
Copy-Item 'C:\ProgramData\Windhawk\Engine\Mods\64\local@taskbar-ai-quota-plus_1.8.1.0_787281.dll' `
    (Join-Path $dst 'local@taskbar-ai-quota-plus_1.8.1.0_787281.dll') -Force
reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-ai-quota-plus' `
    (Join-Path $dst 'mod-key.reg') /y | Out-Null
reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\local@taskbar-ai-quota-plus' `
    (Join-Path $dst 'mods-writable-key.reg') /y | Out-Null

Get-ChildItem $dst | ForEach-Object { "$($_.Name)  $($_.Length)" }
