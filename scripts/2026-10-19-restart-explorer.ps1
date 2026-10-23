# Restart Explorer to un-hang the tray (pre-approved 2026-10-08), brief and verified.
$explorer = Get-Process explorer -ErrorAction SilentlyContinue
Start-Process -FilePath 'explorer.exe' -WindowStyle Hidden   # spawn a successor holder before killing? not needed; kill then start
if ($explorer) { $explorer | Stop-Process -Force }
Start-Sleep -Seconds 3
Start-Process -FilePath "$env:WINDIR\explorer.exe"
Start-Sleep -Seconds 6
$p = Get-Process explorer -ErrorAction SilentlyContinue
if ($p) { Write-Output "explorer running pid=$($p.Id)" } else { Write-Output 'explorer NOT running' }
Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class Rst {
    [DllImport("user32.dll")] public static extern IntPtr FindWindow(string cls, string title);
    [DllImport("user32.dll")] public static extern bool IsHungAppWindow(IntPtr h);
}
'@
$h = [Rst]::FindWindow('Shell_TrayWnd', $null)
Write-Output "Shell_TrayWnd=$h hung=$([Rst]::IsHungAppWindow($h))"
