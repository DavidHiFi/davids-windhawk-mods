# Diagnose: 1) is Shell_TrayWnd's thread hung? 2) does raw GDI BitBlt from screen DC block?
Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class Dg {
    [DllImport("user32.dll")] public static extern IntPtr FindWindow(string cls, string title);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
    [DllImport("user32.dll")] public static extern bool IsHungAppWindow(IntPtr h);
    [DllImport("user32.dll", SetLastError = true)] public static extern IntPtr GetWindowDC(IntPtr h);
    [DllImport("gdi32.dll")] public static extern bool BitBlt(IntPtr hdc, int x, int y, int w, int h, IntPtr hdcs, int xs, int ys, int rop);
    [DllImport("user32.dll")] public static extern int ReleaseDC(IntPtr h, IntPtr hdc);
}
'@
$h = [Dg]::FindWindow('Shell_TrayWnd', $null)
if ($h -eq [IntPtr]::Zero) { Write-Output 'no tray window' }
else {
    [uint32]$pid = 0
    $t = [Dg]::GetWindowThreadProcessId($h, [ref]$pid)
    $hung = [Dg]::IsHungAppWindow($h)
    Write-Output "tray hwnd=$h pid=$pid thread=$t hung=$hung"
    $hdcs = [Dg]::GetWindowDC([IntPtr]::Zero)
    $sw = [System.Diagnostics.Stopwatch]::StartNew()
    $ok = [Dg]::BitBlt($hdcs, 0, 0, 8, 8, [IntPtr]::Zero, 0, 0, 0x00CC0020)
    $sw.Stop()
    [Dg]::ReleaseDC([IntPtr]::Zero, $hdcs) | Out-Null
    Write-Output "bitblt screen ok=$ok in $($sw.ElapsedMilliseconds) ms"
}
