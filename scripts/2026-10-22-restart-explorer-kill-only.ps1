# Kill-only Explorer restart: Winlogon relaunches the shell, so never call
# Start-Process after the kill (it produced two shells on 2026-10-19).
$ErrorActionPreference = 'Continue'
Get-Process explorer -ErrorAction SilentlyContinue | Stop-Process -Force
$deadline = (Get-Date).AddSeconds(25)
do {
    Start-Sleep -Milliseconds 500
    $p = Get-Process explorer -ErrorAction SilentlyContinue
} until ($p -or (Get-Date) -gt $deadline)
Start-Sleep -Seconds 6
$ex = Get-Process explorer -ErrorAction SilentlyContinue
if ($ex) { Write-Output ('explorer back: ' + (($ex.Id) -join ', ')) } else { Write-Output 'explorer NOT running' }
Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
public static class Rst22 {
    [DllImport("user32.dll")] public static extern IntPtr FindWindow(string cls, string title);
    [DllImport("user32.dll")] public static extern bool IsHungAppWindow(IntPtr h);
}
'@
$h = [Rst22]::FindWindow('Shell_TrayWnd', $null)
Write-Output ("Shell_TrayWnd=" + $h + " hung=" + [Rst22]::IsHungAppWindow($h))
