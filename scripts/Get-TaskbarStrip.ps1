# Capture the real taskbar rect (Shell_TrayWnd) to a PNG. Read-only on screen; writes only to %TEMP%.
param([string]$Out = (Join-Path $env:TEMP 'ai-quota-taskbar.png'))

Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class Win {
    [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
    [DllImport("user32.dll")] public static extern IntPtr FindWindow(string cls, string title);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
}
"@

[void][Win]::SetProcessDPIAware()
$h = [Win]::FindWindow('Shell_TrayWnd', $null)
if ($h -eq [IntPtr]::Zero) { Write-Error 'no Shell_TrayWnd'; exit 1 }
$r = New-Object Win+RECT
[void][Win]::GetWindowRect($h, [ref]$r)
$w = $r.R - $r.L; $ht = $r.B - $r.T
"taskbar rect: $($r.L),$($r.T) ${w}x${ht}"

$bmp = New-Object System.Drawing.Bitmap($w, $ht)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($r.L, $r.T, 0, 0, (New-Object System.Drawing.Size($w, $ht)))
$g.Dispose()
$ms = New-Object System.IO.MemoryStream
$bmp.Save($ms, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
[System.IO.File]::WriteAllBytes($Out, $ms.ToArray())
$ms.Dispose()
"saved $Out $((Get-Item $Out).Length) bytes"
