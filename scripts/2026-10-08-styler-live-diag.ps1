# Measure the live Windhawk Styler window: DWM backdrop/corner attributes,
# a margin capture around the window (to catch popups overhanging the visible
# glass), pixel scans outside the rect at strip height, and a two-frame
# shimmer check. Run elevated.
param([string]$OutDir = "H:\Windhawk Configuration\reports\2026-10-08-native-vs-custom")
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$log = Join-Path $OutDir "live-diag.log"
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
[DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
public struct RECT{public int L,T,R,B;}
[DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h,int a,out int v,int s);
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

$backdrop = 0; [void][V]::DwmGetWindowAttribute($vh, 38, [ref]$backdrop, 4)
$corner = 0; [void][V]::DwmGetWindowAttribute($vh, 33, [ref]$corner, 4)
$border = 0; [void][V]::DwmGetWindowAttribute($vh, 34, [ref]$border, 4)
$r = New-Object V+RECT; [void][V]::GetWindowRect($vh, [ref]$r)
$w = $r.R - $r.L; $h = $r.B - $r.T
L ("window rect ($($r.L),$($r.T))-($($r.R),$($r.B)) ${w}x${h} style=0x{0:X8} BACKDROP=$backdrop CORNER=$corner BORDERCOLOR=0x{1:X8}" -f [V]::GetWindowLong($vh, -16), $border)

function Shot([int]$x, [int]$y, [int]$cw, [int]$ch, [string]$path) {
    $b = New-Object System.Drawing.Bitmap $cw, $ch
    $g = [System.Drawing.Graphics]::FromImage($b)
    $g.CopyFromScreen($x, $y, 0, 0, [System.Drawing.Size]::new($cw, $ch))
    $g.Dispose(); $b.Save($path, [System.Drawing.Imaging.ImageFormat]::Png); $b.Dispose()
}
$m = 80
Shot ($r.L - $m) ($r.T - $m) ($w + 2 * $m) ($h + 2 * $m) "$OutDir\live-margin.png"

function Px([System.Drawing.Bitmap]$b, [int]$x, [int]$y) { $c = $b.GetPixel($x, $y); "{0},{1},{2}" -f $c.R, $c.G, $c.B }
$bm = [System.Drawing.Bitmap]::FromFile("$OutDir\live-margin.png")
# Outside-left scan at strip height (y=15): from 60px left of window to 12px inside
L ("== left of window, y=(strip)15: " + ((-60..12 | ForEach-Object { "$_=$(Px $bm ($_ + $m) ($m + 15))" }) -join ' '))
# Outside-right scan at strip height: from 12px inside to 60px past the right edge
L ("== right of window, y=15: " + ((($w - 12)..($w + 60) | ForEach-Object { "$_=$(Px $bm ($_ + $m) ($m + 15))" }) -join ' '))
# Same scans lower in the body for reference
L ("== left of window, y=400: " + ((-20..12 | ForEach-Object { "$_=$(Px $bm ($_ + $m) ($m + 400))" }) -join ' '))
L ("== right of window, y=400: " + ((($w - 12)..($w + 20) | ForEach-Object { "$_=$(Px $bm ($_ + $m) ($m + 400))" }) -join ' '))
# Box region scan inside the window (right edge, below strip)
L ("== box row y=145, x1070-1099: " + ((1070..1099 | ForEach-Object { "$_=$(Px $bm ($_ + $m) ($m + 145))" }) -join ' '))
L ("== box col x=1086, y120-170: " + ((120..170 | ForEach-Object { "$_=$(Px $bm ($m + 1086) ($_ + $m))" }) -join ' '))
$bm.Dispose()

# Two-frame shimmer check on the strip (glass re-composites; solid does not)
Shot $r.L $r.T $w 44 "$OutDir\shimmer-a.png"
Start-Sleep -Seconds 3
Shot $r.L $r.T $w 44 "$OutDir\shimmer-b.png"
$ba = [System.Drawing.Bitmap]::FromFile("$OutDir\shimmer-a.png")
$bb = [System.Drawing.Bitmap]::FromFile("$OutDir\shimmer-b.png")
$diff = 0; $maxd = 0
for ($yy = 2; $yy -lt 42; $yy += 1) { for ($xx = 12; $xx -lt ($w - 12); $xx += 2) {
    $ca = $ba.GetPixel($xx, $yy); $cb2 = $bb.GetPixel($xx, $yy)
    $d = [math]::Abs($ca.R - $cb2.R) + [math]::Abs($ca.G - $cb2.G) + [math]::Abs($ca.B - $cb2.B)
    if ($d -gt 10) { $diff++ }; if ($d -gt $maxd) { $maxd = $d }
} }
$ba.Dispose(); $bb.Dispose()
L "shimmer: $diff pixels changed >10 (max delta $maxd) out of strip sample"
L 'live-diag done'
