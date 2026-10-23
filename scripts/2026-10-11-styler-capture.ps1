# Capture the Windhawk UI window as a PNG without changing focus or state.
# Used to check the Styler's current appearance (border corners, accent
# coverage) while a popup is open. Finds the window by title 'Windhawk', and
# restores it only if it is minimized.
#
#   .\2026-10-11-styler-capture.ps1 -OutFile C:\temp\shot.png
param(
    [string]$OutFile = "C:\Users\localuser\AppData\Local\Temp\styler-capture.png"
)
$ErrorActionPreference = 'Stop'

Add-Type -ReferencedAssemblies System.Drawing @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public static class WinCapture {
    private delegate bool EnumProc(IntPtr hWnd, IntPtr lParam);
    [StructLayout(LayoutKind.Sequential)]
    public struct RECT { public int Left, Top, Right, Bottom; }
    [DllImport("user32.dll")] private static extern bool EnumWindows(EnumProc cb, IntPtr lParam);
    [DllImport("user32.dll")] private static extern int GetWindowTextW(IntPtr hWnd, StringBuilder sb, int max);
    [DllImport("user32.dll")] private static extern bool IsWindowVisible(IntPtr hWnd);
    [DllImport("user32.dll")] private static extern bool IsIconic(IntPtr hWnd);
    [DllImport("user32.dll")] private static extern bool ShowWindow(IntPtr hWnd, int cmd);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT rect);
    [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
    [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr hWnd, IntPtr hdc, uint flags);
    public static IntPtr Find(string title) {
        IntPtr found = IntPtr.Zero;
        EnumWindows((h, l) => {
            if (!IsWindowVisible(h)) return true;
            var sb = new StringBuilder(256);
            GetWindowTextW(h, sb, 256);
            if (sb.ToString() == title) { found = h; return false; }
            return true;
        }, IntPtr.Zero);
        return found;
    }
    public static void RestoreIfMinimized(IntPtr h) { if (IsIconic(h)) ShowWindow(h, 9); }
}
"@

[WinCapture]::SetProcessDPIAware() | Out-Null
$proc = Get-Process -Name windhawk-ui -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowTitle -eq 'Windhawk' } | Select-Object -First 1
if (-not $proc) { throw 'Windhawk window not found' }
$hwnd = [IntPtr]$proc.MainWindowHandle
[WinCapture]::RestoreIfMinimized($hwnd)
Start-Sleep -Milliseconds 300

$rect = New-Object WinCapture+RECT
[WinCapture]::GetWindowRect($hwnd, [ref]$rect) | Out-Null
$w = $rect.Right - $rect.Left
$h = $rect.Bottom - $rect.Top
$bmp = New-Object System.Drawing.Bitmap $w, $h
$g = [System.Drawing.Graphics]::FromImage($bmp)
# PrintWindow renders this window alone, so windows stacked on top of it
# (other apps) stay out of the capture and nothing gets foregrounded.
$hdc = $g.GetHdc()
$ok = [WinCapture]::PrintWindow($hwnd, $hdc, 2)
$g.ReleaseHdc($hdc)
if (-not $ok) { throw 'PrintWindow failed' }
$bmp.Save($OutFile, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"saved $OutFile ${w}x${h}"

