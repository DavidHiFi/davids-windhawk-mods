Add-Type -AssemblyName System.Drawing
Add-Type @"
using System; using System.Text; using System.Runtime.InteropServices;
public class TipCapture {
 public delegate bool EnumProc(IntPtr h,IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb,IntPtr l);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h,out uint p);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h,StringBuilder s,int n);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
 public struct RECT {public int L,T,R,B;}
 public static RECT Find(uint target) { RECT result=new RECT(); EnumWindows((h,l)=>{uint p;GetWindowThreadProcessId(h,out p); var s=new StringBuilder(256);GetClassName(h,s,256);if(p==target && s.ToString()=="tooltips_class32")GetWindowRect(h,out result);return true;},IntPtr.Zero); return result; }
}
"@
$p=Start-Process 'H:\Windhawk Configuration\scripts\tools\FlyoutTestWindow.exe' -ArgumentList '2600 9000 nativetip' -PassThru
Start-Sleep -Seconds 4
$r=[TipCapture]::Find($p.Id)
$b=New-Object Drawing.Bitmap(($r.R-$r.L+40),($r.B-$r.T+40))
$g=[Drawing.Graphics]::FromImage($b)
$g.CopyFromScreen(($r.L-20),($r.T-20),0,0,$b.Size)
$b.Save('H:\Windhawk Configuration\reports\2026-10-04\tooltip-closeup.png')
$g.Dispose();$b.Dispose()
$p.WaitForExit()
Get-Process explorer | ForEach-Object { $_.Modules | Where-Object ModuleName -like '*translucent-flyouts*' | Select-Object ModuleName,FileName | Format-List }
