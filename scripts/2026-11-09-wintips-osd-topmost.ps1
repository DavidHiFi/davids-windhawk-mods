# WinTips OSD Plus 1.4.1: card lifts itself to the front of the always-on-top band on every show.
# Run elevated. Source is already staged in ModsSource (old one backed up by the first run in
# backups\2026-11-07-gpu-plan\local@wintips-osd-plus\2026-11-09-2153). Tool mods must be compiled
# by windhawk-cli, then disabled+enabled so a fresh -tool-mod process starts.
$ErrorActionPreference = 'Stop'
$w = 'H:\Windhawk Configuration\work\2026-11-09-wintips-topmost'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
Copy-Item "$w\local@wintips-osd-plus.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\local@wintips-osd-plus.wh.cpp' -Force
Copy-Item "$w\local@wintips-osd-plus.wh.cpp" 'H:\Windhawk Configuration\Windhawk\wintips-osd-plus\wintips-osd-plus.wh.cpp' -Force
$p = Start-Process $cli -ArgumentList 'mod compile local@wintips-osd-plus' -WindowStyle Hidden -Wait -PassThru `
    -RedirectStandardOutput "$w\compile-out.txt" -RedirectStandardError "$w\compile-err.txt"
"compile exit=$($p.ExitCode)" | Out-File "$w\install.log"
Start-Process $cli -ArgumentList 'mod disable local@wintips-osd-plus' -WindowStyle Hidden -Wait
Start-Sleep 2
Start-Process $cli -ArgumentList 'mod enable local@wintips-osd-plus' -WindowStyle Hidden -Wait
Start-Sleep 4
Set-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@wintips-osd-plus' -Name Version -Value '1.4.1'
(Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@wintips-osd-plus').LibraryFileName | Out-File "$w\install.log" -Append
Get-CimInstance Win32_Process -Filter "name='windhawk.exe'" | ? CommandLine -match 'wintips' |
    % { "proc $($_.ProcessId) $($_.CommandLine)" } | Out-File "$w\install.log" -Append
