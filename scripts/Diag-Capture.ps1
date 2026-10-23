# Diagnose screen capture: input desktop + a tiny CopyFromScreen with timing.
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class W2 {
    [DllImport("user32.dll")] public static extern IntPtr OpenInputDesktop(uint f, bool inherit, uint access);
    [DllImport("user32.dll")] public static extern IntPtr GetThreadDesktop(int t);
    [DllImport("user32.dll")] public static extern bool CloseDesktop(IntPtr h);
    [DllImport("kernel32.dll")] public static extern int GetCurrentThreadId();
}
'@
$td = [W2]::GetThreadDesktop([W2]::GetCurrentThreadId())
$id = [W2]::OpenInputDesktop(0, $true, 0x02000000 -bor 0x10000000)
Write-Output "threadDesk=$td inputDesk=$id"
if ($id -ne [IntPtr]::Zero) { [W2]::CloseDesktop($id) | Out-Null }
$bmp = New-Object System.Drawing.Bitmap -ArgumentList 200, 20
$g = [System.Drawing.Graphics]::FromImage($bmp)
$sw = [System.Diagnostics.Stopwatch]::StartNew()
$g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(200, 20)))
$sw.Stop()
$g.Dispose()
$bmp.Dispose()
Write-Output "copy ok in $($sw.ElapsedMilliseconds) ms"
$c = $bmp2 = $null
