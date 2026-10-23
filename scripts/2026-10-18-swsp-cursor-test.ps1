Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class SwspTest {
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X; public int Y; }
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left; public int Top; public int Right; public int Bottom; }
    [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
    [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
    [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    [DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h, int attr, out RECT r, int size);
    public static POINT Cursor() { POINT p; GetCursorPos(out p); return p; }
    public static RECT Frame(IntPtr h) {
        RECT r;
        if (DwmGetWindowAttribute(h, 9, out r, Marshal.SizeOf(typeof(RECT))) != 0) { GetWindowRect(h, out r); }
        return r;
    }
}
"@

$dir = 'H:\Windhawk Configuration\reports\2026-10-18-swsp-restore'
New-Item -ItemType Directory -Force -Path $dir | Out-Null
$ex = [UIntPtr]::Zero
Start-Sleep -Seconds 3

function Switch-Once([string]$shot) {
    [SwspTest]::keybd_event(0x12, 0, 0, $ex)
    Start-Sleep -Milliseconds 250
    [SwspTest]::keybd_event(0x09, 0, 0, $ex)
    [SwspTest]::keybd_event(0x09, 0, 2, $ex)
    Start-Sleep -Milliseconds 900
    if ($shot) {
        $b = [System.Windows.Forms.SystemInformation]::VirtualScreen
        $bmp = New-Object System.Drawing.Bitmap $b.Width, $b.Height
        $g = [System.Drawing.Graphics]::FromImage($bmp)
        $g.CopyFromScreen($b.Location, [System.Drawing.Point]::Empty, $b.Size)
        $bmp.Save($shot, [System.Drawing.Imaging.ImageFormat]::Png)
        $g.Dispose(); $bmp.Dispose()
    }
    [SwspTest]::keybd_event(0x12, 0, 2, $ex)
    Start-Sleep -Milliseconds 1200
}

function Report([string]$label, $fgBefore) {
    $fg = [SwspTest]::GetForegroundWindow()
    $r = [SwspTest]::Frame($fg)
    $cx = [int](($r.Left + $r.Right) / 2)
    $cy = [int](($r.Top + $r.Bottom) / 2)
    $c = [SwspTest]::Cursor()
    $d = [math]::Sqrt([math]::Pow($c.X - $cx, 2) + [math]::Pow($c.Y - $cy, 2))
    Write-Output ("{0}: focus changed={1}  window center=({2},{3})  cursor=({4},{5})  distance={6:N1}px" -f $label, ($fg -ne $fgBefore), $cx, $cy, $c.X, $c.Y, $d)
}

$f0 = [SwspTest]::GetForegroundWindow()
Switch-Once (Join-Path $dir 'switcher-open.png')
Report 'switch 1' $f0
$f1 = [SwspTest]::GetForegroundWindow()
Switch-Once $null
Report 'switch 2 (back)' $f1
