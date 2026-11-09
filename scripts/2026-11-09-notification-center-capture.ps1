# Opens the notification center through its URI (no mouse, no Win key), captures the
# right 420 px of the primary screen at several moments into one strip, then closes it with Esc.
param([string]$Suffix = 'after')
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing, System.Windows.Forms
Add-Type @'
using System; using System.Runtime.InteropServices;
public class NCK3 {
 [DllImport("user32.dll")] public static extern void keybd_event(byte k, byte s, uint f, UIntPtr e);
 [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
}
'@
[void][NCK3]::SetProcessDPIAware()
$scr = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
$w = 420; $h = $scr.Height
$times = @(800, 1600, 2600, 4000)
$strip = New-Object System.Drawing.Bitmap ($w * $times.Count), $h
$sg = [System.Drawing.Graphics]::FromImage($strip)
Start-Process 'ms-actioncenter:'
$sw = [Diagnostics.Stopwatch]::StartNew()
for ($i = 0; $i -lt $times.Count; $i++) {
    while ($sw.ElapsedMilliseconds -lt $times[$i]) { Start-Sleep -Milliseconds 50 }
    $b = New-Object System.Drawing.Bitmap $w, $h
    $g = [System.Drawing.Graphics]::FromImage($b)
    $g.CopyFromScreen($scr.Right - $w, $scr.Top, 0, 0, $b.Size); $g.Dispose()
    $sg.DrawImage($b, $i * $w, 0); $b.Dispose()
}
$sg.Dispose()
$out = "H:\Windhawk Configuration\reports\2026-11-09-notification-center-$Suffix.png"
$strip.Save($out); $strip.Dispose()
[NCK3]::keybd_event(0x1B, 0, 0, [UIntPtr]::Zero); [NCK3]::keybd_event(0x1B, 0, 2, [UIntPtr]::Zero)
$out
