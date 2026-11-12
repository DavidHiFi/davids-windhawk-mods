# Tray measurement: UIA icon rects, mixer number window rect, a 1x gfxcapture of the tray and
# per-icon ink columns (bright pixels) so spacing can be compared in real pixels.
param([string]$Name='now',[switch]$NoUia)
$d=$PSScriptRoot
Add-Type @'
using System;using System.Runtime.InteropServices;
public static class W{
 [DllImport("user32.dll",CharSet=CharSet.Unicode)]public static extern IntPtr FindWindow(string c,string n);
 [DllImport("user32.dll")]public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")]public static extern bool GetWindowRect(IntPtr h,out R r);
 public struct R{public int l,t,r,b;}
}
'@
$h=[W]::FindWindow('WindhawkMixerTrayNumber',$null)
if($h -ne [IntPtr]::Zero){ $r=New-Object W+R; [void][W]::GetWindowRect($h,[ref]$r); "number window: visible=$([W]::IsWindowVisible($h)) x $($r.l)-$($r.r) y $($r.t)-$($r.b)" }
Add-Type -AssemblyName UIAutomationClient,UIAutomationTypes
$root=[Windows.Automation.AutomationElement]::RootElement
$c=New-Object Windows.Automation.PropertyCondition ([Windows.Automation.AutomationElement]::AutomationIdProperty),'NotifyItemIcon'
$(if(-not $NoUia){ $root.FindAll('Descendants',$c) }) | % { $b=$_.Current.BoundingRectangle; "icon x $($b.X)-$($b.X+$b.Width) y $($b.Y)-$($b.Y+$b.Height)  $((($_.Current.Name -split "`n")[0]))" }
$ff="$env:LOCALAPPDATA\Microsoft\WinGet\Links\ffmpeg.exe"; $png="$d\$Name.png"
$psi=New-Object Diagnostics.ProcessStartInfo $ff
$psi.Arguments="-y -loglevel error -filter_complex `"gfxcapture=monitor_idx=1:max_framerate=10,hwdownload,format=bgra,crop=560:50:2000:0`" -frames:v 1 `"$png`""
$psi.UseShellExecute=$false; $psi.CreateNoWindow=$true; $p=[Diagnostics.Process]::Start($psi); $p.WaitForExit(20000) | Out-Null
Add-Type -AssemblyName System.Drawing
$bmp=[Drawing.Bitmap]::FromFile($png); $cols=@()
for($x=0;$x -lt $bmp.Width;$x++){ $ink=$false; for($y=14;$y -lt 36;$y++){ $px=$bmp.GetPixel($x,$y); if(($px.R+$px.G+$px.B) -gt 330 -or ($px.G -gt 150 -and $px.R -lt 120)){ $ink=$true; break } }; $cols+=$ink }
$runs=@(); $start=-1
for($x=0;$x -lt $cols.Count;$x++){ if($cols[$x] -and $start -lt 0){$start=$x}; if(-not $cols[$x] -and $start -ge 0){ $runs+="$($start+2000)-$($x-1+2000)"; $start=-1 } }
"ink runs (screen x): " + ($runs -join ', ')
# rows of ink for the number and the speaker, for vertical alignment
foreach($span in @(@(2240,2262),@(2262,2284),@(2206,2234))){ $top=99;$bot=-1; for($x=$span[0]-2000;$x -lt $span[1]-2000;$x++){ for($y=5;$y -lt 45;$y++){ $px=$bmp.GetPixel($x,$y); if(($px.R+$px.G+$px.B) -gt 400){ if($y -lt $top){$top=$y}; if($y -gt $bot){$bot=$y} } } }; "rows x $($span[0])-$($span[1]): $top-$bot" }
$bmp.Dispose()
