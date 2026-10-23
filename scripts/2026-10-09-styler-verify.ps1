[CmdletBinding()]
param([string]$Label='current',[switch]$Activate,[switch]$ProbeCaption)
$ErrorActionPreference = 'Stop'
$report = 'H:\Windhawk Configuration\reports\2026-10-09-styler-audit'
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System;using System.Collections.Generic;using System.Runtime.InteropServices;using System.Text;
public static class StylerProbe {
 public delegate bool Callback(IntPtr h,IntPtr l);
 [StructLayout(LayoutKind.Sequential)] public struct Rect { public int Left,Top,Right,Bottom; }
 [StructLayout(LayoutKind.Sequential)] public struct Point { public int X,Y; }
 public sealed class Window { public long Handle; public uint Pid; public string Class,Title; public bool Visible,Iconic; public uint Cloaked; public Rect Bounds,Client; public Point Origin; }
 [DllImport("user32.dll")] static extern bool EnumWindows(Callback cb,IntPtr l);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] static extern int GetClassName(IntPtr h,StringBuilder s,int n);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] static extern int GetWindowText(IntPtr h,StringBuilder s,int n);
 [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr h,out uint p);
 [DllImport("user32.dll")] static extern bool GetWindowRect(IntPtr h,out Rect r);
 [DllImport("user32.dll")] static extern bool GetClientRect(IntPtr h,out Rect r);
 [DllImport("user32.dll")] static extern bool ClientToScreen(IntPtr h,ref Point p);
 [DllImport("user32.dll")] static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] static extern bool IsIconic(IntPtr h);
 [DllImport("dwmapi.dll")] static extern int DwmGetWindowAttribute(IntPtr h,uint a,out uint v,uint n);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] static extern bool BringWindowToTop(IntPtr h);
 [DllImport("user32.dll")] static extern bool AttachThreadInput(uint a,uint b,bool attach);
 [DllImport("kernel32.dll")] static extern uint GetCurrentThreadId();
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern uint GetGuiResources(IntPtr p,uint flags);
 [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern bool ShowWindowAsync(IntPtr h,int n);
 [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h,IntPtr after,int x,int y,int w,int n,uint flags);
 public static void Focus(IntPtr h) {
  uint pid;uint target=GetWindowThreadProcessId(GetForegroundWindow(),out pid);uint current=GetCurrentThreadId();
  bool attached=target!=0 && target!=current && AttachThreadInput(current,target,true);
  try { BringWindowToTop(h);SetForegroundWindow(h); }
  finally { if(attached)AttachThreadInput(current,target,false); }
 }
 public static Window[] Windows() {
  var items=new List<Window>();
  EnumWindows((h,l)=>{
   var s=new StringBuilder(128);GetClassName(h,s,s.Capacity);string c=s.ToString();
   if(c!="WindhawkTauriMainUI" && c!="WindhawkStylerVeil")return true;
   var v=new Window{Handle=h.ToInt64(),Class=c,Visible=IsWindowVisible(h),Iconic=IsIconic(h)};
   GetWindowThreadProcessId(h,out v.Pid);GetWindowRect(h,out v.Bounds);GetClientRect(h,out v.Client);
   ClientToScreen(h,ref v.Origin);DwmGetWindowAttribute(h,14,out v.Cloaked,4);
   s.Clear();GetWindowText(h,s,s.Capacity);v.Title=s.ToString();items.Add(v);return true;
  },IntPtr.Zero);return items.ToArray();
 }
}
'@
$windows = [StylerProbe]::Windows()
$main = @($windows | Where-Object { $_.Class -eq 'WindhawkTauriMainUI' -and $_.Visible -and !$_.Iconic -and !$_.Cloaked })
if ($main.Count -ne 1) { throw "Expected one visible interface, found $($main.Count)." }
$win = $main[0]
$handle = [IntPtr]$win.Handle
if ($Activate) { [StylerProbe]::Focus($handle); Start-Sleep -Milliseconds 700 }
$caption = $null
if ($ProbeCaption) {
    $p = Get-Process -Id $win.Pid
    # Count repeated work after the one-time caption allocation.
    [void][StylerProbe]::SendMessage($handle,0x86,[IntPtr]::Zero,[IntPtr]::Zero)
    [void][StylerProbe]::SendMessage($handle,0x86,[IntPtr]1,[IntPtr]::Zero)
    Start-Sleep -Milliseconds 100
    $before = [StylerProbe]::GetGuiResources($p.Handle,0)
    for ($i=0;$i -lt 30;$i++) {
        [void][StylerProbe]::SendMessage($handle,0x86,[IntPtr]::Zero,[IntPtr]::Zero)
        [void][StylerProbe]::SendMessage($handle,0x86,[IntPtr]1,[IntPtr]::Zero)
    }
    $after = [StylerProbe]::GetGuiResources($p.Handle,0)
    $caption = [ordered]@{before=$before;after=$after;growth=([int]$after-[int]$before)}
}
$windows = [StylerProbe]::Windows()
$win = $windows | Where-Object Handle -eq $win.Handle
$b = $win.Bounds
$width = $b.Right-$b.Left; $height=$b.Bottom-$b.Top
$bmp = [System.Drawing.Bitmap]::new($width,$height)
$graphics = [System.Drawing.Graphics]::FromImage($bmp)
$graphics.CopyFromScreen($b.Left,$b.Top,0,0,[System.Drawing.Size]::new($width,$height))
$graphics.Dispose()
$bmp.Save("$report\$Label.png",[System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
$result=[ordered]@{time=(Get-Date -Format o);windows=$windows;captionProbe=$caption;
    sideInset=($win.Origin.X-$b.Left);bottomInset=($height-($win.Origin.Y-$b.Top)-$win.Client.Bottom);
    captionHeight=($win.Origin.Y-$b.Top);foreground=([StylerProbe]::GetForegroundWindow().ToInt64() -eq $win.Handle)}
$result | ConvertTo-Json -Depth 6 | Set-Content "$report\$Label.json" -Encoding UTF8
$result | ConvertTo-Json -Depth 6
