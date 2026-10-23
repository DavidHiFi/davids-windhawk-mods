Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;using System.Runtime.InteropServices;public class Hover { [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h); [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y); }
"@
$r=[System.Windows.Automation.AutomationElement]::RootElement
$c=New-Object System.Windows.Automation.PropertyCondition([System.Windows.Automation.AutomationElement]::ClassNameProperty,'CabinetWClass')
$ws=$r.FindAll([System.Windows.Automation.TreeScope]::Children,$c)
foreach($w in $ws){
 [Hover]::SetForegroundWindow([IntPtr]$w.Current.NativeWindowHandle) | Out-Null
 $items=$w.FindAll([System.Windows.Automation.TreeScope]::Descendants,[System.Windows.Automation.Condition]::TrueCondition)
 foreach($i in $items){
 if($i.Current.Name -match '\(C:\)'){
  $b=$i.Current.BoundingRectangle
  if($b.Width -gt 50 -and $b.Height -gt 20){
   [Hover]::SetCursorPos(50,50) | Out-Null
   Start-Sleep -Seconds 1
   [Hover]::SetCursorPos([int]($b.X+$b.Width/2),[int]($b.Y+$b.Height-12)) | Out-Null
   Start-Sleep -Seconds 7
   $wb=$w.Current.BoundingRectangle
   $bmp=New-Object Drawing.Bitmap([int]$wb.Width,[int]$wb.Height)
   $g=[Drawing.Graphics]::FromImage($bmp)
   $g.CopyFromScreen([int]$wb.X,[int]$wb.Y,0,0,$bmp.Size)
   $bmp.Save('H:\Windhawk Configuration\reports\2026-10-04\explorer-tooltip.png')
   $g.Dispose();$bmp.Dispose()
   Write-Output "Captured tooltip for $($i.Current.Name)"
   exit
  }
 }
 }
}
Write-Output 'Drive element not found'



