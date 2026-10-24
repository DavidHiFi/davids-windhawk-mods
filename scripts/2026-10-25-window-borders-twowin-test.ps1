# Two stock windows: A loses focus (expect the unfocused color), B has focus
# (expect the accent). Reads pixels at each frame edge from a real screenshot.
Add-Type -AssemblyName System.Windows.Forms,System.Drawing
Add-Type @'
using System;using System.Runtime.InteropServices;
public class N{
 [DllImport("user32.dll")]public static extern bool MoveWindow(IntPtr h,int x,int y,int w,int ht,bool r);
 [DllImport("user32.dll")]public static extern bool GetWindowRect(IntPtr h,out RECT r);
 [DllImport("dwmapi.dll")]public static extern int DwmGetWindowAttribute(IntPtr h,int a,out RECT r,int sz);
 [DllImport("user32.dll")]public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")]public static extern IntPtr GetForegroundWindow();
 [StructLayout(LayoutKind.Sequential)]public struct RECT{public int L,T,R,B;}
}
'@
$out = 'H:\Windhawk Configuration\reports\2026-10-25-window-borders-twowin.png'
$a = Start-Process winver -PassThru; Start-Sleep 2
$ha = (Get-Process -Id $a.Id).MainWindowHandle
if ($ha -eq 0) { $ha = (Get-Process winver | select -first 1).MainWindowHandle }
[N]::MoveWindow($ha, 300, 300, 520, 380, $true) | Out-Null
$b = Start-Process charmap -PassThru; Start-Sleep 2
$hb = (Get-Process -Id $b.Id).MainWindowHandle
[N]::MoveWindow($hb, 1000, 300, 600, 420, $true) | Out-Null
[N]::SetForegroundWindow($hb) | Out-Null
Start-Sleep 1
"charmap is foreground: $([N]::GetForegroundWindow() -eq $hb)"
$vs = [System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp = New-Object System.Drawing.Bitmap $vs.Width, $vs.Height
[System.Drawing.Graphics]::FromImage($bmp).CopyFromScreen($vs.Left, $vs.Top, 0, 0, $bmp.Size)
$bmp.Save($out)
foreach ($w in @(@('A winver (unfocused)', $ha), @('B charmap (focused)', $hb))) {
    $r = New-Object N+RECT
    [N]::DwmGetWindowAttribute($w[1], 9, [ref]$r, 16) | Out-Null
    $midY = [int](($r.T + $r.B) / 2) - $vs.Top
    $row = for ($x = $r.L - 2; $x -le $r.L + 2; $x++) { $c = $bmp.GetPixel($x - $vs.Left, $midY); "{0}:{1:X2}{2:X2}{3:X2}" -f ($x - $r.L), $c.R, $c.G, $c.B }
    $ring=@{}; foreach($x in ($r.L-3)..($r.R+3)){ foreach($yy in @(($r.T-3)..($r.T+3)+($r.B-3)..($r.B+3))){ $c=$bmp.GetPixel($x-$vs.Left,$yy-$vs.Top); $k='{0:X2}{1:X2}{2:X2}' -f $c.R,$c.G,$c.B; $ring[$k]++ } }
    "ring top colors: " + (($ring.GetEnumerator()|sort Value -desc|select -first 4|%{"$($_.Key)x$($_.Value)"}) -join ' ')
    "{0} frame L={1} T={2} R={3} B={4} leftEdge-row {5}" -f $w[0], $r.L, $r.T, $r.R, $r.B, ($row -join ' ')
}
Stop-Process -Id $a.Id, $b.Id -ErrorAction SilentlyContinue
Get-Process winver, charmap -ErrorAction SilentlyContinue | Stop-Process -ErrorAction SilentlyContinue
