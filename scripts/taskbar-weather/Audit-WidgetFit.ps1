$ErrorActionPreference='Stop'
Add-Type @'
using System; using System.Text; using System.Runtime.InteropServices;
public class WidgetFitAudit {
 [StructLayout(LayoutKind.Sequential)] public struct RECT {public int Left,Top,Right,Bottom;}
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c,string t);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr GetProp(IntPtr h,string p);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
 [DllImport("user32.dll")] public static extern uint GetDpiForWindow(IntPtr h);
}
'@
$tray=[WidgetFitAudit]::FindWindow('Shell_TrayWnd',$null)
$rect=New-Object WidgetFitAudit+RECT
[void][WidgetFitAudit]::GetWindowRect($tray,[ref]$rect)
$dpi=[WidgetFitAudit]::GetDpiForWindow($tray)
$weather=[WidgetFitAudit]::GetProp($tray,'WindhawkTaskbarWeatherRightDip').ToInt64()
$panel=[WidgetFitAudit]::GetProp($tray,'WindhawkTaskbarSystemInfoRightDip').ToInt64()
$mods=foreach($id in @('local@taskbar-weather','local@taskbar-system-info-weather','local@davids-audio-visualizer')){
 $p=Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
 [pscustomobject]@{Id=$id;Version=$p.Version;Disabled=$p.Disabled;Library=$p.LibraryFileName;Hash=(Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$($p.LibraryFileName)").Hash}
}
[pscustomobject]@{Timestamp=(Get-Date).ToString('o');Dpi=$dpi;WeatherRightDip=$weather;PanelRightDip=$panel;VisualizerStartDip=($panel+8);ExplorerPid=(Get-Process explorer).Id;Mods=$mods} | ConvertTo-Json -Depth 4
Add-Type -AssemblyName System.Drawing
$b=New-Object System.Drawing.Bitmap(900,($rect.Bottom-$rect.Top))
$g=[System.Drawing.Graphics]::FromImage($b)
$g.CopyFromScreen($rect.Left,$rect.Top,0,0,$b.Size)
$b.Save('H:\System Configuration\reports\2026-10-03\taskbar-weather\widget-fit-live.png')
$g.Dispose();$b.Dispose()
