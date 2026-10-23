param([string]$Png = "$env:TEMP\tbfix\measure-64.png")
Add-Type -AssemblyName System.Drawing
Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
public class TB2 {
    [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindowW(string cls, string title);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
}
'@
$h = [TB2]::FindWindowW("Shell_TrayWnd", $null)
$r = New-Object TB2+RECT
[TB2]::GetWindowRect($h, [ref]$r) | Out-Null
"taskbar window: L=$($r.L) T=$($r.T) R=$($r.R) B=$($r.B) height=$($r.B - $r.T)"
$bmp = [System.Drawing.Bitmap]::FromFile($Png)
"image: $($bmp.Width)x$($bmp.Height)"
$zones = @(
    @("tray-cluster", 1850, 2530),
    @("left-icons", 10, 400),
    @("clock", 2350, 2535)
)
foreach ($z in $zones) {
    $name = $z[0]; $x0 = $z[1]; $x1 = $z[2]
    $rows = @()
    for ($y = 0; $y -lt $bmp.Height; $y++) {
        $ink = 0
        for ($x = $x0; $x -lt $x1; $x += 2) {
            $c = $bmp.GetPixel($x, $y)
            $mx = [Math]::Max($c.R, [Math]::Max($c.G, $c.B))
            if ($mx -gt 90) { $ink++ }
        }
        if ($ink -gt 0) { $rows += "$y($ink)" }
    }
    "$name ink rows: $($rows -join ' ')"
}
$bmp.Dispose()
