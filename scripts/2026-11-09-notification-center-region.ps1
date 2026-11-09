# Opens the notification center via URI and reports its window rect, window region box and DWM border colour; closes with Esc.
Add-Type @'
using System; using System.Runtime.InteropServices;
public class NCR {
 public struct R {public int L,T,Right,Bottom;}
 [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c,string t);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out R r);
 [DllImport("user32.dll")] public static extern int GetWindowRgnBox(IntPtr h,out R r);
 [DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h,int a,out int v,int s);
 [DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h,int a,out R v,int s);
 [DllImport("user32.dll")] public static extern void keybd_event(byte k, byte s, uint f, UIntPtr e);
}
'@
[void][NCR]::SetProcessDPIAware()
Start-Process 'ms-actioncenter:'
Start-Sleep -Milliseconds 1500
$h = [NCR]::FindWindow('Windows.UI.Core.CoreWindow', 'Notification Centre')
if ($h -eq [IntPtr]::Zero) { $h = [NCR]::FindWindow('Windows.UI.Core.CoreWindow', 'Notification Center') }
"hwnd " + $h.ToInt64().ToString('X')
$r = New-Object NCR+R; [void][NCR]::GetWindowRect($h, [ref]$r); "rect $($r.L),$($r.T),$($r.Right),$($r.Bottom)"
$g = New-Object NCR+R; $t = [NCR]::GetWindowRgnBox($h, [ref]$g); "rgn type $t box $($g.L),$($g.T),$($g.Right),$($g.Bottom)"
$e = New-Object NCR+R; $hr = [NCR]::DwmGetWindowAttribute($h, 9, [ref]$e, 16); "dwm frame hr=$hr $($e.L),$($e.T),$($e.Right),$($e.Bottom)"
$c = 0; $hr = [NCR]::DwmGetWindowAttribute($h, 34, [ref]$c, 4); "border colour hr=$hr 0x$($c.ToString('X8'))"
$c = 0; $hr = [NCR]::DwmGetWindowAttribute($h, 33, [ref]$c, 4); "corner pref hr=$hr $c"
[NCR]::keybd_event(0x1B,0,0,[UIntPtr]::Zero); [NCR]::keybd_event(0x1B,0,2,[UIntPtr]::Zero)
