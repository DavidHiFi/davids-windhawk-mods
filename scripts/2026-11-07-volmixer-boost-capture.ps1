# Opens the mixer through its tray message, optionally posts one click at
# client (X,Y) to the mixer window (posted message, the cursor never moves),
# captures it, posts the same click again to undo it, and hides the popup.
param([int]$ClickX = -1, [int]$ClickY = -1, [string]$Suffix = '')
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System; using System.Text; using System.Runtime.InteropServices;
public class MV2 {
 public struct R {public int L,T,Right,Bottom;}
 public delegate bool E(IntPtr h,IntPtr p);
 [DllImport("user32.dll")] static extern bool EnumWindows(E e,IntPtr p);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] static extern int GetClassName(IntPtr h,StringBuilder s,int n);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out R r);
 [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int n);
 public static IntPtr Find() {
  IntPtr found=IntPtr.Zero;
  EnumWindows((h,p)=>{var s=new StringBuilder(256); GetClassName(h,s,256);
   if(s.ToString()=="WindhawkBetterTaskbarVolumeMixer") {found=h; return false;} return true;},IntPtr.Zero);
  return found;
 }
}
'@
function Click([IntPtr]$h, [int]$x, [int]$y) {
    $lp = [IntPtr]($x -bor ($y -shl 16))
    [void][MV2]::PostMessage($h, 0x201, [IntPtr]1, $lp)
    [void][MV2]::PostMessage($h, 0x202, [IntPtr]::Zero, $lp)
    Start-Sleep -Milliseconds 500
}
$h = [MV2]::Find()
if ($h -eq [IntPtr]::Zero) { throw 'Mixer window not found' }
$wasVisible = [MV2]::IsWindowVisible($h)
try {
    if (-not $wasVisible) {
        [void][MV2]::PostMessage($h, 32769, [IntPtr]::Zero, [IntPtr]1025)
        Start-Sleep -Milliseconds 800
        [void][MV2]::ShowWindow($h, 4)
        Start-Sleep -Milliseconds 100
    }
    if ($ClickX -ge 0) { Click $h $ClickX $ClickY; [void][MV2]::ShowWindow($h, 4); Start-Sleep -Milliseconds 300 }
    $r = New-Object MV2+R
    [void][MV2]::GetWindowRect($h, [ref]$r)
    "visible=$([MV2]::IsWindowVisible($h)) rect=$($r.L),$($r.T),$($r.Right),$($r.Bottom)"
    if (-not [MV2]::IsWindowVisible($h)) { throw 'Mixer is hidden; no capture' }
    $b = New-Object System.Drawing.Bitmap ($r.Right - $r.L), ($r.Bottom - $r.T)
    $g = [System.Drawing.Graphics]::FromImage($b)
    try { $g.CopyFromScreen($r.L, $r.T, 0, 0, $b.Size); $b.Save("H:\Windhawk Configuration\reports\2026-11-07-mixer-1.3.0$Suffix.png") }
    finally { $g.Dispose(); $b.Dispose() }
} finally {
    if ($ClickX -ge 0) { Click $h $ClickX $ClickY }
    if (-not $wasVisible) { [void][MV2]::ShowWindow($h, 0) }
}
