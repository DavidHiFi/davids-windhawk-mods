# Opens a file Properties dialog in Explorer, reports its styles and DWM state,
# saves a screenshot of just that window, then closes it.
param([string]$Target = "C:\Windows\notepad.exe", [string]$Shot = "", [switch]$InExplorer, [int]$Tab = -1)
$src = @'
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public static class TP{delegate bool EP(IntPtr h,IntPtr l);
[DllImport("user32")]static extern bool EnumWindows(EP e,IntPtr l);
[DllImport("user32",CharSet=CharSet.Unicode)]static extern int GetWindowText(IntPtr h,StringBuilder s,int n);
[DllImport("user32",CharSet=CharSet.Unicode)]static extern int GetClassName(IntPtr h,StringBuilder s,int n);
[DllImport("user32")]static extern long GetWindowLongPtr(IntPtr h,int i);
[DllImport("user32")]static extern bool IsWindowVisible(IntPtr h);
[DllImport("user32")]public static extern bool SetForegroundWindow(IntPtr h);[DllImport("user32")]public static extern bool PostMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
[DllImport("user32")]public static extern bool GetWindowRect(IntPtr h,out RECT r);
[DllImport("user32")]static extern uint GetWindowThreadProcessId(IntPtr h,out uint p);
[DllImport("dwmapi")]static extern int DwmGetWindowAttribute(IntPtr h,int a,out int v,int s);
public struct RECT{public int L,T,R,B;}[StructLayout(LayoutKind.Sequential)]public struct AP{public int S,F,C,A;}[StructLayout(LayoutKind.Sequential)]public struct WCA{public int At;public IntPtr P;public int Sz;}[DllImport("user32")]static extern bool GetWindowCompositionAttribute(IntPtr h,ref WCA d);public static int Accent(IntPtr h){var a=new AP();var p=Marshal.AllocHGlobal(16);Marshal.StructureToPtr(a,p,false);var d=new WCA{At=19,P=p,Sz=16};GetWindowCompositionAttribute(h,ref d);a=(AP)Marshal.PtrToStructure(p,typeof(AP));Marshal.FreeHGlobal(p);return a.S;}
public static List<IntPtr> Hw=new List<IntPtr>();
public static List<string> Run(string title){var r=new List<string>();Hw.Clear();EnumWindows((h,l)=>{var t=new StringBuilder(256);GetWindowText(h,t,256);if(t.ToString().Contains(title)&&IsWindowVisible(h)){var c=new StringBuilder(256);GetClassName(h,c,256);uint p;GetWindowThreadProcessId(h,out p);int v,cl;DwmGetWindowAttribute(h,38,out v,4);DwmGetWindowAttribute(h,14,out cl,4);Hw.Add(h);r.Add(String.Format("{0:X} '{1}' class={2} pid={3} style={4:X8} ex={5:X8} backdrop={6} cloak={7} accent={8}",(long)h,t,c,p,GetWindowLongPtr(h,-16),GetWindowLongPtr(h,-20),v,cl,Accent(h)));}return true;},IntPtr.Zero);return r;}}
'@
Add-Type $src
$name = Split-Path $Target -Leaf
$sh = New-Object -ComObject Shell.Application
if ($InExplorer) {
  $dir = Split-Path $Target; $before = @($sh.Windows()).Count
  Start-Process explorer.exe "`"$dir`""
  for ($i = 0; $i -lt 40 -and -not $w; $i++) { Start-Sleep -Milliseconds 250
    $w = @($sh.Windows() | Where-Object { $_.Document.Folder.Self.Path -eq $dir })[-1] }
  if (-not $w) { "explorer window did not open"; exit 1 }
  Start-Sleep -Milliseconds 800
  $w.Document.Folder.ParseName($name).InvokeVerb("properties")
} else { $sh.Namespace((Split-Path $Target)).ParseName($name).InvokeVerb("properties") }
$title = "$name Properties"
for ($i = 0; $i -lt 30 -and [TP]::Run($title).Count -eq 0; $i++) { Start-Sleep -Milliseconds 200 }
if ([TP]::Hw.Count) { [TP]::SetForegroundWindow([TP]::Hw[0]) | Out-Null }
Start-Sleep -Milliseconds 1500
if ($Tab -ge 0) { [TP]::PostMessage([TP]::Hw[0], 0x466, [IntPtr]$Tab, [IntPtr]::Zero) | Out-Null; Start-Sleep -Milliseconds 800 }
[TP]::SetForegroundWindow([TP]::Hw[0]) | Out-Null; Start-Sleep -Milliseconds 500
[TP]::Run($title)
if ($Shot -and [TP]::Hw.Count) {
  Add-Type -AssemblyName System.Drawing
  $r = New-Object TP+RECT; [TP]::GetWindowRect([TP]::Hw[0], [ref]$r) | Out-Null
  $b = New-Object Drawing.Bitmap ($r.R - $r.L), ($r.B - $r.T)
  $g = [Drawing.Graphics]::FromImage($b); $g.CopyFromScreen($r.L, $r.T, 0, 0, $b.Size)
  $c = $b.GetPixel([int]($b.Width/2), [int]($b.Height*0.6)); "center pixel: $c"
  $b.Save($Shot); $g.Dispose(); $b.Dispose()
}
foreach ($h in [TP]::Hw) { [TP]::PostMessage($h, 0x10, [IntPtr]::Zero, [IntPtr]::Zero) | Out-Null }



if ($w) { Start-Sleep -Milliseconds 300; $w.Quit() }


