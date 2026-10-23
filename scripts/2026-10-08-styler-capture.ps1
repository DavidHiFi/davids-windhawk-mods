# Capture the Windhawk Styler UI window (works in native and custom title bar
# modes): full window, title bar strip at 1x, four corners at 5x, plus pixel
# statistics for the blur/artifact check. Run elevated:
#   Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-08-styler-capture.ps1" -ArgumentList "-Mode native"
param(
    [Parameter(Mandatory = $true)][ValidateSet('native', 'custom')][string]$Mode,
    [string]$OutDir = "H:\Windhawk Configuration\reports\2026-10-08-native-vs-custom"
)
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$log = Join-Path $OutDir "capture-$Mode.log"
if (Test-Path $log) { Remove-Item $log }
function L($m) { $m | Tee-Object -FilePath $log -Append }

Add-Type -AssemblyName System.Drawing
Add-Type @'
using System;using System.Runtime.InteropServices;using System.Text;
public class V{
public delegate bool CB(IntPtr h,IntPtr l);
[DllImport("user32.dll")] public static extern bool EnumWindows(CB cb,IntPtr l);
[DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h,out uint p);
[DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
[DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
[DllImport("user32.dll")] public static extern IntPtr GetWindow(IntPtr h,uint f);
[DllImport("user32.dll")] public static extern int GetWindowLong(IntPtr h,int i);
[DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h,StringBuilder s,int n);
[DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
[DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
[DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
public struct RECT{public int L,T,R,B;}
}
'@

$script:vs = @(Get-CimInstance Win32_Process -Filter "Name='VSCodium.exe'" | ForEach-Object { [int]$_.ProcessId })
$script:found = [IntPtr]::Zero
$cb = [V+CB] { param($w, $l)
    if ($script:found -ne [IntPtr]::Zero) { return $true }
    if (-not [V]::IsWindowVisible($w)) { return $true }
    $wp = [uint32]0; [void][V]::GetWindowThreadProcessId($w, [ref]$wp)
    if ($script:vs -contains [int]$wp) {
        $sb = New-Object System.Text.StringBuilder 256
        [void][V]::GetWindowText($w, $sb, 256)
        if ($sb.ToString() -eq 'Windhawk' -and -not [V]::IsIconic($w) -and [V]::GetWindow($w, 4) -eq [IntPtr]::Zero) { $script:found = $w }
    }
    return $true
}
[void][V]::EnumWindows($cb, [IntPtr]::Zero)
$vh = $script:found
if ($vh -eq [IntPtr]::Zero) { L 'no window'; exit 1 }

if ([V]::IsIconic($vh)) { [void][V]::ShowWindow($vh, 9); Start-Sleep -Milliseconds 500 }
[void][V]::SetForegroundWindow($vh)
Start-Sleep -Milliseconds 900

$r = New-Object V+RECT; [void][V]::GetWindowRect($vh, [ref]$r)
$w = $r.R - $r.L; $h = $r.B - $r.T
$st = [V]::GetWindowLong($vh, -16)
L ("window: ($($r.L),$($r.T))-($($r.R),$($r.B)) ${w}x${h} style=0x{0:X8}" -f $st)

$bmp = New-Object System.Drawing.Bitmap $w, $h
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($r.L, $r.T, 0, 0, [System.Drawing.Size]::new($w, $h))
$g.Dispose()
$bmp.Save("$OutDir\$Mode-full.png", [System.Drawing.Imaging.ImageFormat]::Png)

function CropZoom([System.Drawing.Bitmap]$b, [int]$x, [int]$y, [int]$cw, [int]$ch, [int]$scale, [string]$path) {
    $crop = $b.Clone([System.Drawing.Rectangle]::new($x, $y, $cw, $ch), $b.PixelFormat)
    $big = [System.Drawing.Bitmap]::new($cw * $scale, $ch * $scale)
    $g2 = [System.Drawing.Graphics]::FromImage($big)
    $g2.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
    $g2.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
    $g2.DrawImage($crop, 0, 0, $cw * $scale, $ch * $scale)
    $big.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
    $g2.Dispose(); $big.Dispose(); $crop.Dispose()
}
# Title bar strip at 1x (the artifacting view) and the four corners at 5x.
$strip = $bmp.Clone([System.Drawing.Rectangle]::new(0, 0, $w, 44), $bmp.PixelFormat)
$strip.Save("$OutDir\$Mode-strip-1x.png", [System.Drawing.Imaging.ImageFormat]::Png); $strip.Dispose()
CropZoom $bmp 0 0 120 44 5 "$OutDir\$Mode-tl-5x.png"
CropZoom $bmp ($w - 120) 0 120 44 5 "$OutDir\$Mode-tr-5x.png"
CropZoom $bmp 0 ($h - 44) 120 44 5 "$OutDir\$Mode-bl-5x.png"
CropZoom $bmp ($w - 120) ($h - 44) 120 44 5 "$OutDir\$Mode-br-5x.png"

function Px([int]$x, [int]$y) { $c = $bmp.GetPixel($x, $y); "{0},{1},{2}" -f $c.R, $c.G, $c.B }
L ("== strip row y=15, x0..24: " + ((0..24 | ForEach-Object { "$_=$(Px $_ 15)" }) -join ' '))
L ("== strip row y=15, x last 24: " + (($w - 24)..($w - 1) | ForEach-Object { "$_=$(Px $_ 15)" }) -join ' ')
L ("== TL corner diagonal (x=y): " + ((0..12 | ForEach-Object { "$_=$(Px $_ $_)" }) -join ' '))
L ("== strip col x=3: " + ((0..35 | ForEach-Object { "$_=$(Px 3 $_)" }) -join ' '))

# Region stats: mean RGB + luminance stddev. Live acrylic shows wallpaper
# texture, so a flat solid fill reads stddev ~0 while glass reads higher.
function RegionStats([System.Drawing.Bitmap]$b, [int]$x, [int]$y, [int]$cw, [int]$ch, [string]$name) {
    $rs = 0.0; $gs = 0.0; $bs = 0.0; $n = 0; $lum = New-Object System.Collections.Generic.List[double]
    for ($yy = $y; $yy -lt $y + $ch; $yy += 2) {
        for ($xx = $x; $xx -lt $x + $cw; $xx += 3) {
            $c = $b.GetPixel($xx, $yy); $rs += $c.R; $gs += $c.G; $bs += $c.B; $n++
            $lum.Add(0.2126 * $c.R + 0.7152 * $c.G + 0.0722 * $c.B)
        }
    }
    $mean = @([math]::Round($rs / $n, 1), [math]::Round($gs / $n, 1), [math]::Round($bs / $n, 1))
    $avg = ($lum | Measure-Object -Average).Average
    $var = 0.0; foreach ($v in $lum) { $var += [math]::Pow($v - $avg, 2) }
    $std = [math]::Sqrt($var / $lum.Count)
    L ("== $name mean RGB=($($mean -join ',')) lumStd=" + [math]::Round($std, 2))
}
RegionStats $bmp 10 4 ($w - 20) 36 'strip(y4-40)'
RegionStats $bmp 10 80 ($w - 20) 200 'body(y80-280)'
RegionStats $bmp 10 8 200 28 'strip-left(y8-36,x0-200)'
RegionStats $bmp ($w - 210) 8 200 28 'strip-right(y8-36,x-200)'

$bmp.Dispose()
L "capture-$Mode done"
exit 0
