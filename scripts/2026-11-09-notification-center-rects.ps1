# Opens the notification center via URI, reports the top-level window at the panel's area, closes with Esc.
Add-Type @'
using System; using System.Text; using System.Runtime.InteropServices;
public class NCP {
 public struct R {public int L,T,Right,Bottom;}
 public struct P {public int X,Y;}
 [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(P p);
 [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h,uint f);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h,StringBuilder s,int n);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h,StringBuilder s,int n);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out R r);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h,out uint p);
 [DllImport("user32.dll")] public static extern void keybd_event(byte k, byte s, uint f, UIntPtr e);
 public static string Info(int x,int y){ P p; p.X=x; p.Y=y; IntPtr h=GetAncestor(WindowFromPoint(p),2);
  var c=new StringBuilder(256); GetClassName(h,c,256); var t=new StringBuilder(256); GetWindowText(h,t,256);
  R r; GetWindowRect(h,out r); uint pid; GetWindowThreadProcessId(h,out pid);
  return String.Format("({0},{1}) {2:X} pid={3} [{4}] '{5}' {6},{7},{8},{9}",x,y,h.ToInt64(),pid,c,t,r.L,r.T,r.Right,r.Bottom); }
}
'@
[void][NCP]::SetProcessDPIAware()
Start-Process 'ms-actioncenter:'
Start-Sleep -Milliseconds 3500
foreach ($pt in @(@(2400,1150), @(2400,1380), @(2400,700), @(2400,120))) {
    $s = [NCP]::Info($pt[0], $pt[1])
    if ($s -match 'pid=(\d+)') { $s += '  ' + (Get-Process -Id $Matches[1] -EA SilentlyContinue).ProcessName }
    $s
}
[NCP]::keybd_event(0x1B,0,0,[UIntPtr]::Zero); [NCP]::keybd_event(0x1B,0,2,[UIntPtr]::Zero)
