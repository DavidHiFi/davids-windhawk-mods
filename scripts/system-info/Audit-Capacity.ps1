[CmdletBinding()]
param([string]$Label='live')
$ErrorActionPreference='Stop'
$report='H:\System Configuration\reports\2026-10-03\memory-align'
New-Item -ItemType Directory -Force $report | Out-Null
Add-Type @'
using System; using System.Runtime.InteropServices;
public class SystemInfoAudit {
 [StructLayout(LayoutKind.Sequential)] public struct RECT {public int Left,Top,Right,Bottom;}
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c,string t);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr GetProp(IntPtr h,string p);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
 [DllImport("user32.dll")] public static extern uint GetDpiForWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h,out uint p);
}
'@
$tray=[SystemInfoAudit]::FindWindow('Shell_TrayWnd',$null)
if($tray -eq [IntPtr]::Zero){throw 'Taskbar missing'}
$rect=New-Object SystemInfoAudit+RECT
[void][SystemInfoAudit]::GetWindowRect($tray,[ref]$rect)
$shellPid=0
[void][SystemInfoAudit]::GetWindowThreadProcessId($tray,[ref]$shellPid)
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-system-info-weather'
$mod=Get-ItemProperty $key
$settings=Get-ItemProperty "$key\Settings"
$modules=@((Get-Process -Id $shellPid).Modules | Where-Object ModuleName -like '*system-info-weather*' | ForEach-Object ModuleName)
$record=[ordered]@{Timestamp=(Get-Date).ToString('o');ExplorerPid=$shellPid;Dpi=[SystemInfoAudit]::GetDpiForWindow($tray);WeatherRightDip=[SystemInfoAudit]::GetProp($tray,'WindhawkTaskbarWeatherRightDip').ToInt64();PanelRightDip=[SystemInfoAudit]::GetProp($tray,'WindhawkTaskbarSystemInfoRightDip').ToInt64();Version=$mod.Version;Library=$mod.LibraryFileName;Disabled=$mod.Disabled;LoadedModules=$modules;ItemGap=$settings.itemGap;ShowComputeGraphs=$settings.showComputeGraphs;ShowMemoryGraphs=$settings.showMemoryGraphs;ShowMemoryBars=$settings.showMemoryBars;ShowNetwork=$settings.showNetwork;Font=$settings.fontFamily;DllHash=(Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$($mod.LibraryFileName)").Hash;SourceHash=(Get-FileHash 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-system-info-weather.wh.cpp').Hash}
$record | ConvertTo-Json -Depth 4 | Set-Content "$report\$Label.json" -Encoding UTF8
$record | ConvertTo-Json -Depth 4
Add-Type -AssemblyName System.Drawing
$bitmap=New-Object System.Drawing.Bitmap(1100,($rect.Bottom-$rect.Top))
$graphics=[System.Drawing.Graphics]::FromImage($bitmap)
$graphics.CopyFromScreen($rect.Left,$rect.Top,0,0,$bitmap.Size)
$bitmap.Save("$report\$Label.png")
$graphics.Dispose();$bitmap.Dispose()




