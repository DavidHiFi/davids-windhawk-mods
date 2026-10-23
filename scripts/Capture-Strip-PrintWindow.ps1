# PrintWindow capture of Shell_TrayWnd (works even when CopyFromScreen hangs).
param([string]$Out = (Join-Path $env:TEMP 'tray-pw.png'))
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class Pw {
    [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
    [DllImport("user32.dll")] public static extern IntPtr FindWindow(string cls, string title);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint flags);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
}
'@
[void][Pw]::SetProcessDPIAware()
$h = [Pw]::FindWindow('Shell_TrayWnd', $null)
if ($h -eq [IntPtr]::Zero) { Write-Error 'no Shell_TrayWnd'; exit 1 }
$r = New-Object Pw+RECT
[void][Pw]::GetWindowRect($h, [ref]$r)
$w = $r.R - $r.L; $ht = $r.B - $r.T
Write-Output "taskbar rect: $($r.L),$($r.T) ${w}x${ht}"
$bmp = New-Object System.Drawing.Bitmap -ArgumentList $w, $ht
$g = [System.Drawing.Graphics]::FromImage($bmp)
$hdc = $g.GetHdc()
# PW_RENDERFULLCONTENT = 2
$ok = [Pw]::PrintWindow($h, $hdc, 2)
$g.ReleaseHdc($hdc)
$g.Dispose()
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
Write-Output "printwindow ok=$ok saved $Out"
