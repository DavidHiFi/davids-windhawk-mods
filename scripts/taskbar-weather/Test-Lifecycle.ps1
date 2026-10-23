$ErrorActionPreference='Stop'
Add-Type @'
using System;using System.Text;using System.Runtime.InteropServices;
public static class WeatherLifecycleTest {
 public delegate bool Callback(IntPtr h,IntPtr l);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)]public static extern IntPtr FindWindow(string c,string n);
 [DllImport("user32.dll")]static extern bool EnumChildWindows(IntPtr h,Callback c,IntPtr l);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)]static extern int GetClassName(IntPtr h,StringBuilder s,int n);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)]static extern int GetWindowText(IntPtr h,StringBuilder s,int n);
 [DllImport("user32.dll")]public static extern IntPtr SendMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")]public static extern IntPtr GetForegroundWindow();
 public static IntPtr Child(){IntPtr result=IntPtr.Zero;EnumChildWindows(FindWindow("Shell_TrayWnd",null),(h,l)=>{var s=new StringBuilder(256);GetClassName(h,s,256);if(s.ToString()=="WindhawkIndependentWeather")result=h;return true;},IntPtr.Zero);return result;}
 public static string Text(IntPtr h){var s=new StringBuilder(1024);GetWindowText(h,s,1024);return s.ToString();}
}
'@
$root='H:\System Configuration'
$original=[WeatherLifecycleTest]::Child()
if($original -eq [IntPtr]::Zero){throw 'Weather HWND absent before test'}
$explorer=(Get-Process explorer).Id
$before=[WeatherLifecycleTest]::Text($original)
# Close only this mod's child, never Explorer or a taskbar owned by Windows.
[WeatherLifecycleTest]::SendMessage($original,0x10,[IntPtr]::Zero,[IntPtr]::Zero)|Out-Null
Start-Sleep -Milliseconds 50
$absent=([WeatherLifecycleTest]::Child() -eq [IntPtr]::Zero)
Start-Sleep -Seconds 2
$replacement=[WeatherLifecycleTest]::Child()
if($replacement -eq [IntPtr]::Zero){throw 'Weather child did not recreate'}
$controller=[WeatherLifecycleTest]::FindWindow('WindhawkWeatherLifecycle','Weather lifecycle')
if($controller -eq [IntPtr]::Zero){throw 'Lifecycle controller not found'}
$initialStatus=[WeatherLifecycleTest]::Text($replacement)
$initialCount=[int]([regex]::Match($initialStatus,'updates (\d+)').Groups[1].Value)
# Deliver resume notification only to the mod's hidden controller.
[WeatherLifecycleTest]::SendMessage($controller,0x218,[IntPtr]0x12,[IntPtr]::Zero)|Out-Null
$refreshed=$false
for($i=0;$i -lt 25;$i++){
 Start-Sleep -Seconds 1
 $after=[WeatherLifecycleTest]::Text([WeatherLifecycleTest]::Child())
 $count=[regex]::Match($after,'updates (\d+)')
 if($count.Success -and [int]$count.Groups[1].Value -gt $initialCount){$refreshed=$true;break}
}
$focusBefore=[WeatherLifecycleTest]::GetForegroundWindow()
[WeatherLifecycleTest]::SendMessage([WeatherLifecycleTest]::Child(),0x8002,[IntPtr]::Zero,[IntPtr]::Zero)|Out-Null
Start-Sleep -Milliseconds 400
$focusAfter=[WeatherLifecycleTest]::GetForegroundWindow()
Add-Type -AssemblyName System.Drawing
$b=New-Object Drawing.Bitmap 380,350
$g=[Drawing.Graphics]::FromImage($b)
$g.CopyFromScreen(0,1090,0,0,$b.Size)
$b.Save("$root\work\taskbar-weather\private-card-verification.png")
$g.Dispose();$b.Dispose()
$result=[pscustomobject]@{Timestamp=(Get-Date).ToString('o');ChildRemoved=$absent;ChildRecreated=($replacement -ne [IntPtr]::Zero);ResumeRefreshVerified=$refreshed;Before=$before;After=$after;CardPreviewPreservedFocus=($focusBefore -eq $focusAfter);ExplorerPidUnchanged=((Get-Process explorer).Id -eq $explorer)}
$result | ConvertTo-Json | Set-Content "$root\reports\2026-09-30\taskbar-weather\lifecycle-test.json"
$result | ConvertTo-Json
if(!$refreshed -or !$result.ExplorerPidUnchanged){throw 'Lifecycle regression failed'}
