$ErrorActionPreference='Stop'
Add-Type @'
using System;
using System.Text;
using System.Runtime.InteropServices;
public static class WeatherAudit {
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c,string n);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr FindWindowEx(IntPtr p,IntPtr a,string c,string n);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h,StringBuilder b,int n);
 public delegate bool Callback(IntPtr h,IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr h,Callback c,IntPtr l);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h,StringBuilder b,int n);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr GetProp(IntPtr h,string name);
 public static IntPtr Weather(IntPtr parent) {
   IntPtr found=IntPtr.Zero;
   EnumChildWindows(parent,(h,l)=>{var b=new StringBuilder(256);GetClassName(h,b,256);if(b.ToString()=="WindhawkIndependentWeather")found=h;return true;},IntPtr.Zero);
   return found;
 }
}
'@
$taskbar=[WeatherAudit]::FindWindow('Shell_TrayWnd',$null)
$weather=[WeatherAudit]::Weather($taskbar)

Add-Type @"
using System;using System.Runtime.InteropServices;
public class CrispHover {
 [StructLayout(LayoutKind.Sequential)] public struct RECT {public int Left,Top,Right,Bottom;}
 [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
}
"@
[void][CrispHover]::PostMessage($weather,0x8002,[IntPtr]::Zero,[IntPtr]::Zero)
Start-Sleep -Milliseconds 450
$r=New-Object CrispHover+RECT
$bar=New-Object CrispHover+RECT
[void][CrispHover]::GetWindowRect($weather,[ref]$r)
[void][CrispHover]::GetWindowRect($taskbar,[ref]$bar)
if($r.Top -lt $bar.Top -or $r.Bottom -gt $bar.Bottom){throw 'Weather extends outside taskbar'}
[pscustomobject]@{Taskbar=$bar;Weather=$r;HighlightInsetDip=3;Contained=$true} | ConvertTo-Json -Depth 3 | Set-Content 'H:\System Configuration\reports\2026-10-03\weather-crisp\hover-bounds.json'
Add-Type -AssemblyName System.Drawing
$b=New-Object Drawing.Bitmap(900,320)
$g=[Drawing.Graphics]::FromImage($b)
$g.CopyFromScreen($bar.Left,$bar.Top,0,0,$b.Size)
$b.Save('H:\System Configuration\reports\2026-10-03\weather-crisp\hover.png')
$g.Dispose();$b.Dispose()
