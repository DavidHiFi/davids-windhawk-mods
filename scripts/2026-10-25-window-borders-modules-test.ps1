# Is the mod DLL mapped in fresh stock processes, and can a direct
# DwmSetWindowAttribute call color the border on this machine?
Add-Type -AssemblyName System.Windows.Forms,System.Drawing
Add-Type @'
using System;using System.Runtime.InteropServices;
public class N2{
 [DllImport("user32.dll")]public static extern bool MoveWindow(IntPtr h,int x,int y,int w,int ht,bool r);
 [DllImport("dwmapi.dll")]public static extern int DwmSetWindowAttribute(IntPtr h,int a,ref uint v,int sz);
 [DllImport("dwmapi.dll")]public static extern int DwmGetWindowAttribute(IntPtr h,int a,out R r,int sz);
 [StructLayout(LayoutKind.Sequential)]public struct R{public int L,T,Rt,B;}
}
'@
$a = Start-Process winver -PassThru; Start-Sleep 2
$pa = Get-Process -Id $a.Id
"winver modules: " + (($pa.Modules | ? ModuleName -like '*window-borders*').ModuleName -join ',')
$ha = $pa.MainWindowHandle
[N2]::MoveWindow($ha, 300, 300, 520, 380, $true) | Out-Null
$c = Start-Process charmap -PassThru; Start-Sleep 2
$pc = Get-Process -Id $c.Id
"charmap modules: " + (($pc.Modules | ? ModuleName -like '*window-borders*').ModuleName -join ',')
[N2]::MoveWindow($pc.MainWindowHandle, 1000, 300, 600, 420, $true) | Out-Null
# direct call: color the unfocused winver border pure green
[uint32]$green = 0x0000FF00  # COLORREF 0x00BBGGRR -> green
$hr = [N2]::DwmSetWindowAttribute($ha, 34, [ref]$green, 4)
"direct DwmSetWindowAttribute hr=$hr"
Start-Sleep 1
$vs = [System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp = New-Object System.Drawing.Bitmap $vs.Width, $vs.Height
[System.Drawing.Graphics]::FromImage($bmp).CopyFromScreen($vs.Left, $vs.Top, 0, 0, $bmp.Size)
$r = New-Object N2+R; [N2]::DwmGetWindowAttribute($ha, 9, [ref]$r, 16) | Out-Null
$my = [int](($r.T + $r.B) / 2)
$row = for ($x = $r.L - 2; $x -le $r.L + 2; $x++) { $p = $bmp.GetPixel($x - $vs.Left, $my - $vs.Top); "{0}:{1:X2}{2:X2}{3:X2}" -f ($x - $r.L), $p.R, $p.G, $p.B }
"winver left edge after direct green: " + ($row -join ' ')
Get-Process winver, charmap -ErrorAction SilentlyContinue | Stop-Process -ErrorAction SilentlyContinue
