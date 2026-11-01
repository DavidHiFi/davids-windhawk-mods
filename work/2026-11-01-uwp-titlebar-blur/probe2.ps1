# Cross-process probes: DWMWA_USE_HOSTBACKDROPBRUSH (21) and WCA accent
# states 4/5 over a black/white stripe board on the live Store frame.
param([switch]$KeepOpen)
$out = 'H:\Windhawk Configuration\work\2026-11-01-uwp-titlebar-blur'
Add-Type -AssemblyName System.Windows.Forms, System.Drawing
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text;
public static class P {
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc p, IntPtr l);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr a, int x, int y, int cx, int cy, uint f);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [StructLayout(LayoutKind.Sequential)] public struct MARGINS { public int L, R, T, B; }
  [DllImport("dwmapi.dll")] public static extern int DwmSetWindowAttribute(IntPtr h, int a, ref int v, int s);
  [DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h, int a, out int v, int s);
  [DllImport("dwmapi.dll")] public static extern int DwmExtendFrameIntoClientArea(IntPtr h, ref MARGINS m);
  [StructLayout(LayoutKind.Sequential)] public struct DWM_BLURBEHIND { public uint flags; public bool enable; public IntPtr rgn; public bool transition; }
  [DllImport("dwmapi.dll")] public static extern int DwmEnableBlurBehindWindow(IntPtr h, ref DWM_BLURBEHIND b);
  [StructLayout(LayoutKind.Sequential)] public struct ACCENT { public int State; public int Flags; public uint Color; public int AnId; public int AnFlags; }
  [StructLayout(LayoutKind.Sequential)] public struct WADM { public int attr; public int size; public IntPtr data; }
  [DllImport("user32.dll")] public static extern bool SetWindowCompositionAttribute(IntPtr h, ref WADM d);
  public static IntPtr Find() {
    IntPtr found = IntPtr.Zero;
    EnumWindows((h, l) => {
      var c = new StringBuilder(64); GetClassName(h, c, 64);
      var t = new StringBuilder(64); GetWindowText(h, t, 64);
      if (c.ToString() == "ApplicationFrameWindow" && t.ToString() == "Microsoft Store" && IsWindowVisible(h)) { found = h; return false; }
      return true; }, IntPtr.Zero);
    return found;
  }
}
'@
function Accent([IntPtr]$h, [int]$state, [uint32]$color, [int]$flags) {
  $a = New-Object P+ACCENT; $a.State = $state; $a.Color = $color; $a.Flags = $flags
  $sz = [System.Runtime.InteropServices.Marshal]::SizeOf($a)
  $ptr = [System.Runtime.InteropServices.Marshal]::AllocHGlobal($sz)
  [System.Runtime.InteropServices.Marshal]::StructureToPtr($a, $ptr, $false)
  $d = New-Object P+WADM; $d.attr = 19; $d.size = $sz; $d.data = $ptr
  $ok = [P]::SetWindowCompositionAttribute($h, [ref]$d)
  [System.Runtime.InteropServices.Marshal]::FreeHGlobal($ptr)
  "accent state=$state flags=$flags ok=$ok"
  $ok
}
function Margins([IntPtr]$h, [int]$t) { $m = New-Object P+MARGINS; $m.T = $t; $hr = [P]::DwmExtendFrameIntoClientArea($h, [ref]$m); "margins top=$t hr=0x{0:X8}" -f $hr; $hr }
function Attr([IntPtr]$h, [int]$a, [int]$v) { $hr = 0; $hr = [P]::DwmSetWindowAttribute($h, $a, [ref]$v, 4); "seta $a=$v hr=0x{0:X8}" -f $hr; $hr }
function ReadA([IntPtr]$h, [int]$a) { $v = 0; [void][P]::DwmGetWindowAttribute($h, $a, [ref]$v, 4); "geta $a=$v"; $v }
function BlurBehind([IntPtr]$h, [bool]$on) {
  $b = New-Object P+DWM_BLURBEHIND; $b.flags = 3; $b.enable = $on; $b.rgn = [IntPtr]::Zero
  $hr = [P]::DwmEnableBlurBehindWindow($h, [ref]$b); "blurbehind=$on hr=0x{0:X8}" -f $hr; $hr
}
function Shot([string]$tag) {
  $bmp = New-Object System.Drawing.Bitmap 1500, 60
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen(200, 150, 0, 0, $bmp.Size); $g.Dispose()
  $bmp.Save("$out\probe2-$tag.png"); $bmp.Dispose()
  "saved probe2-$tag.png"
}
$prevFg = [P]::GetForegroundWindow()
$board = New-Object System.Windows.Forms.Form
$board.FormBorderStyle = 'None'; $board.StartPosition = 'Manual'; $board.ShowInTaskbar = $false
$board.Location = New-Object System.Drawing.Point(150, 120); $board.Size = New-Object System.Drawing.Size(1650, 140)
$bmp = New-Object System.Drawing.Bitmap 1650, 140
$g = [System.Drawing.Graphics]::FromImage($bmp)
for ($x = 0; $x -lt 1650; $x += 80) { $g.FillRectangle([System.Drawing.Brushes]::White, $x, 0, 40, 140); $g.FillRectangle([System.Drawing.Brushes]::Black, $x + 40, 0, 40, 140) }
$g.Dispose(); $board.BackgroundImage = $bmp
$board.Show(); [System.Windows.Forms.Application]::DoEvents()
$h = [P]::Find()
$opened = $false
if ($h -eq [IntPtr]::Zero) {
  Start-Process 'ms-windows-store:'; $opened = $true
  for ($i = 0; $i -lt 80 -and $h -eq [IntPtr]::Zero; $i++) { Start-Sleep -Milliseconds 250; [System.Windows.Forms.Application]::DoEvents(); $h = [P]::Find() }
}
if ($h -eq [IntPtr]::Zero) { 'no store frame'; $board.Close(); exit 1 }
"frame $h"
for ($i = 0; $i -lt 20; $i++) { Start-Sleep -Milliseconds 250; [System.Windows.Forms.Application]::DoEvents() }
[void][P]::SetWindowPos($h, [IntPtr]::Zero, 200, 160, 1500, 900, 0x10)
for ($i = 0; $i -lt 12; $i++) { Start-Sleep -Milliseconds 250; [System.Windows.Forms.Application]::DoEvents() }
[void][P]::SetForegroundWindow($h); Start-Sleep -Milliseconds 700

$baseCC = ReadA $h 33
$baseBD = ReadA $h 38
$base21 = ReadA $h 21
Shot 'A-base'

Attr $h 21 1
ReadA $h 21
Start-Sleep -Milliseconds 900
Shot 'B-hbattr'

Accent $h 5 0xC02E1E1E 2
Start-Sleep -Milliseconds 1300
Shot 'C-accent5'

Margins $h -1
Start-Sleep -Milliseconds 1300
Shot 'D-accent5-margins'

Accent $h 4 0xC02E1E1E 2
Start-Sleep -Milliseconds 1300
Shot 'E-accent4-margins'

Accent $h 0 0 0
[void](Margins $h 0)
[void](BlurBehind $h $false)
[void](Attr $h 21 $base21)
[void](Attr $h 33 $baseCC)
[void](Attr $h 38 $baseBD)
Start-Sleep -Milliseconds 900
ReadA $h 33
ReadA $h 21
Shot 'Z-restored'

if ($prevFg -ne $h) { [void][P]::SetForegroundWindow($prevFg) }
$board.Close()
if ($KeepOpen) { 'keeping store open' } else { [System.Windows.Forms.Application]::DoEvents() }
"done (opened=$opened)"