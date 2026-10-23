# Freeze-7 ground truth, 2026-10-22, thread e4c9ed97. Read-only except coop join.
# Run elevated so process and event-log visibility are complete. Pure ASCII.
$ErrorActionPreference = 'Continue'
$out = 'H:\Windhawk Configuration\reports\2026-10-22-freeze7-ground-truth.txt'
"FREEZE7 GROUND TRUTH " + (Get-Date -Format 'HH:mm:ss tt') + " " + (Get-Date -Format 'yyyy-MM-dd') | Set-Content -Path $out
function W($s) { $s | Tee-Object -FilePath $out -Append }

# coop board join (must run unsandboxed; the sandboxed shell cannot touch the coop state dir)
$coop = 'H:\System Configuration\agent-tools\AgentCoop\coop.py'
W ("COOP JOIN: " + (& python $coop join --as e4c9ed97 --task 'freeze7 ground truth + rearm decision, user gave explicit go' 2>&1 | Out-String))

# input probe: zero-delta SendInput nudge, DEAD if GetLastInputInfo does not advance
Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class Probe {
  [StructLayout(LayoutKind.Sequential)] public struct LASTINPUTINFO { public uint cbSize; public uint dwTime; }
  [DllImport("user32.dll")] public static extern bool GetLastInputInfo(ref LASTINPUTINFO p);
  [DllImport("user32.dll")] public static extern uint SendInput(uint n, INPUT[] inputs, int size);
  [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx; public int dy; public uint mouseData; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
  [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public MOUSEINPUT mi; }
  public static uint Nudge() {
    INPUT[] i = new INPUT[1];
    i[0].type = 0;
    i[0].mi.dx = 0; i[0].mi.dy = 0; i[0].mi.mouseData = 0; i[0].mi.dwFlags = 1; i[0].mi.time = 0; i[0].mi.dwExtraInfo = IntPtr.Zero;
    return SendInput(1, i, Marshal.SizeOf(typeof(INPUT)));
  }
}
"@
$b = New-Object Probe+LASTINPUTINFO
$b.cbSize = [uint32][System.Runtime.InteropServices.Marshal]::SizeOf($b)
[Probe]::GetLastInputInfo([ref]$b) | Out-Null
$before = $b.dwTime
[Probe]::Nudge() | Out-Null
Start-Sleep -Milliseconds 300
$a = New-Object Probe+LASTINPUTINFO
$a.cbSize = [uint32][System.Runtime.InteropServices.Marshal]::SizeOf($a)
[Probe]::GetLastInputInfo([ref]$a) | Out-Null
$after = $a.dwTime
$verdict = if ($after -ne $before) { 'ALIVE' } else { 'DEAD' }
$idleMs = [Environment]::TickCount - $after
if ($idleMs -lt 0) { $idleMs = $idleMs + 4294967296 }
W ("INPUT PROBE: $before -> $after | $verdict | last-input idle ms: $idleMs")

W ("BOOT TIME: " + (Get-CimInstance Win32_OperatingSystem).LastBootUpTime)
$svc = Get-Service Windhawk
W ("ENGINE: {0} startType={1}" -f $svc.Status, $svc.StartType)
$wh = @(Get-Process | Where-Object { $_.ProcessName -match 'windhawk|windhog|DbgViewMini' })
W ("WINDHAWK-RELATED PROCESSES: $($wh.Count)")
foreach ($p in $wh) { W ("  pid {0} {1}" -f $p.Id, $p.ProcessName) }
$apps = 'PowerToys','Ditto','ShareX','Flow.Launcher','WinLaunchEnhanced','DSX','FreeDictate','steam','Discord'
foreach ($app in $apps) {
  $n = @(Get-Process | Where-Object { $_.ProcessName -like "*$app*" }).Count
  if ($n -gt 0) { W ("  RUNNING: $app x$n") }
}
$fi = Get-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Services\FakerInput' -ErrorAction SilentlyContinue
W ("FakerInput ConfigFlags: {0}" -f $fi.ConfigFlags)
$hid = (Get-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Control\Class\{745a17a0-74d3-11d0-b6fe-00a0c90f57da}' -ErrorAction SilentlyContinue).UpperFilters
W ("HID UpperFilters: {0}" -f ($hid -join ','))
W ("ViGEmBus Start: {0}" -f (Get-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Services\ViGEmBus' -ErrorAction SilentlyContinue).Start)

W "--- SCM Windhawk events today ---"
Get-WinEvent -FilterHashtable @{ LogName='System'; ProviderName='Service Control Manager'; StartTime=(Get-Date).Date } -ErrorAction SilentlyContinue |
  Where-Object { $_.Message -match 'Windhawk' } |
  ForEach-Object { W ("  {0:HH:mm:ss tt} id={1} {2}" -f $_.TimeCreated, $_.Id, (($_.Message -split "`r?`n")[0])) }

W "--- unexpected shutdown (6008) events today ---"
Get-WinEvent -FilterHashtable @{ LogName='System'; Id=6008; StartTime=(Get-Date).Date } -ErrorAction SilentlyContinue |
  ForEach-Object { W ("  {0:HH:mm:ss tt}: {1}" -f $_.TimeCreated, (($_.Message -split "`r?`n") -join ' ')) }

W "--- task states of interest ---"
foreach ($t in 'WindhawkRunBrokerTask','WindhawkUpdateTask','TranslucentWindowsGuard','DSX','FreeDictate','AB Download Manager','Steam','Ableton Live 12 Suite','Open-Shell') {
  $row = schtasks /query /tn "\$t" /fo csv 2>$null | Select-Object -Skip 1 | ConvertFrom-Csv
  if ($row) { W ("  task $t : " + $row.Status) } else { W ("  task $t : NOT FOUND") }
}
W 'GROUND TRUTH DONE'
