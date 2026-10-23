# Post-restart health check for the Windhawk Styler window.
param([string]$OutDir = "H:\Windhawk Configuration\reports\2026-10-08-native-vs-custom")
$ErrorActionPreference = 'Stop'
$log = Join-Path $OutDir "health-check.log"
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
}
'@

$script:vs = @(Get-CimInstance Win32_Process -Filter "Name='VSCodium.exe'" | ForEach-Object { [int]$_.ProcessId })
$script:found = [IntPtr]::Zero
$script:veil = ''
$cb = [V+CB] { param($w, $l)
    if (-not [V]::IsWindowVisible($w)) { return $true }
    $wp = [uint32]0; [void][V]::GetWindowThreadProcessId($w, [ref]$wp)
    $sb = New-Object System.Text.StringBuilder 256
    [void][V]::GetWindowText($w, $sb, 256)
    $t = $sb.ToString()
    if ($script:found -eq [IntPtr]::Zero -and $script:vs -contains [int]$wp -and $t -eq 'Windhawk' -and -not [V]::IsIconic($w) -and [V]::GetWindow($w, 4) -eq [IntPtr]::Zero) { $script:found = $w }
    if ($t -match 'WindhawkStylerVeil') { $r = New-Object V+RECT; [void][V]::GetWindowRect($w, [ref]$r); $script:veil = "($($r.L),$($r.T))-($($r.R),$($r.B)) $($r.R-$r.L)x$($r.B-$r.T) pid=$wp" }
    return $true
}
[void][V]::EnumWindows($cb, [IntPtr]::Zero)
$vh = $script:found
if ($vh -eq [IntPtr]::Zero) { L 'no window'; exit 1 }
$r = New-Object V+RECT; [void][V]::GetWindowRect($vh, [ref]$r)
$w = $r.R - $r.L; $h = $r.B - $r.T
$wp = 0; [void][V]::GetWindowThreadProcessId($vh, [ref]$wp)
$L1 = "window pid=$wp rect ($($r.L),$($r.T))-($($r.R),$($r.B)) ${w}x${h} style=0x{0:X8}" -f [V]::GetWindowLong($vh, -16); L $L1
L "veil popup: $(if ($script:veil) { $script:veil } else { 'NOT FOUND' })"

$bmp = New-Object System.Drawing.Bitmap $w, $h
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($r.L, $r.T, 0, 0, [System.Drawing.Size]::new($w, $h))
$g.Dispose()
$bmp.Save("$OutDir\live-after-restart.png", [System.Drawing.Imaging.ImageFormat]::Png)

function Px([int]$x, [int]$y) { $c = $bmp.GetPixel($x, $y); "{0},{1},{2}" -f $c.R, $c.G, $c.B }
L ("strip y=15 left: " + ((0..12 | ForEach-Object { "$_=$(Px $_ 15)" }) -join ' '))
L ("strip y=15 right: " + ((1088..1099 | ForEach-Object { "$_=$(Px $_ 15)" }) -join ' '))
L ("body row y=304 right: " + ((1070..1099 | ForEach-Object { "$_=$(Px $_ 304)" }) -join ' '))
# content check: variance in the big header area (y60-110, x40-300) - blank page = near zero
$vals = New-Object System.Collections.Generic.List[double]
for ($yy = 60; $yy -lt 110; $yy += 2) { for ($xx = 40; $xx -lt 300; $xx += 4) { $c = $bmp.GetPixel($xx, $yy); $vals.Add([double](($c.R + $c.G + $c.B) / 3)) } }
$m = ($vals | Measure-Object -Average -StandardDeviation)
L ("header region: n=$($vals.Count) mean=$([math]::Round($m.Average,1)) std=$([math]::Round($m.StandardDeviation,2)) (std>10 = content rendered)")
$bmp.Dispose()
L 'health-check done'
