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
$text=New-Object Text.StringBuilder 400
[WeatherAudit]::GetWindowText($weather,$text,400) | Out-Null
$mod='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$p=Get-ItemProperty $mod
$explorer=Get-Process explorer | Select-Object Id,StartTime
[pscustomobject]@{
 Timestamp=(Get-Date).ToString('o');WindowPresent=($weather -ne [IntPtr]::Zero);Status=$text.ToString();
 Explorer=$explorer;ModDisabled=$p.Disabled;LibraryFileName=$p.LibraryFileName;
 UpdateMinutes=(Get-ItemProperty "$mod\Settings").updateMinutes;
 WeatherRightDip=([WeatherAudit]::GetProp($taskbar,'WindhawkTaskbarWeatherRightDip').ToInt64());
 MonitorLibrary=if(Test-Path 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-system-info-weather'){(Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-system-info-weather').LibraryFileName}else{(Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\taskbar-system-info').LibraryFileName};
 MachineWidgetsPolicy=(Get-ItemProperty 'HKLM:\SOFTWARE\Policies\Microsoft\Dsh').AllowNewsAndInterests;
 UserWidgetsPolicy=(Get-ItemProperty 'HKCU:\SOFTWARE\Policies\Microsoft\Dsh').AllowNewsAndInterests;
 WidgetProcesses=@(Get-Process Widgets,WidgetService -ErrorAction SilentlyContinue).Count;
 DllHash=(Get-FileHash ('C:\ProgramData\Windhawk\Engine\Mods\64\'+$p.LibraryFileName)).Hash;
 SourceHash=(Get-FileHash 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp').Hash
} | ConvertTo-Json -Depth 4
