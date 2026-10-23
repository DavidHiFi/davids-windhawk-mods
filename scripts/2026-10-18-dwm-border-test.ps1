Add-Type -AssemblyName System.Drawing
Add-Type -TypeDefinition @"
using System; using System.Runtime.InteropServices;
public static class Dwm2 {
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c, string t);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindowEx(IntPtr p, IntPtr a, string c, string t);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern IntPtr SendMessageTimeout(IntPtr h, uint m, IntPtr w, IntPtr l, uint f, uint t, out IntPtr r);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("dwmapi.dll")] public static extern int DwmSetWindowAttribute(IntPtr h, int attr, ref int v, int size);
}
"@
function Popup {
  $best = $null; $h = [IntPtr]::Zero
  do {
    $h = [Dwm2]::FindWindowEx([IntPtr]::Zero, $h, '#32768', $null)
    if ($h -ne [IntPtr]::Zero -and [Dwm2]::IsWindowVisible($h)) {
      $r = New-Object Dwm2+RECT; [void][Dwm2]::GetWindowRect($h, [ref]$r)
      $w = $r.Right - $r.Left; $hh = $r.Bottom - $r.Top
      if ($w -gt 60 -and $hh -gt 60) { if (-not $best -or ($w*$hh) -gt $best.A) { $best = [pscustomobject]@{ H=$h; R=$r; W=$w; Hh=$hh; A=$w*$hh } } }
    }
  } while ($h -ne [IntPtr]::Zero)
  $best
}
function Grab($p) {
  $bmp = New-Object System.Drawing.Bitmap $p.W, $p.Hh
  $g = [System.Drawing.Graphics]::FromImage($bmp); $g.CopyFromScreen($p.R.Left, $p.R.Top, 0, 0, (New-Object System.Drawing.Size $p.W, $p.Hh)); $g.Dispose(); $bmp
}
function Sample($bmp) {
  $w = $bmp.Width; $h = $bmp.Height
  $pts = @{ 'left x=2'=@(2,[int]($h/2)); 'top y=2'=@([int]($w/2),2); 'right x=w-3'=@(($w-3),[int]($h/2)); 'bottom y=h-3'=@([int]($w/2),($h-3)); 'corner 3,3'=@(3,3) }
  foreach ($k in $pts.Keys) { $c = $bmp.GetPixel($pts[$k][0], $pts[$k][1]); "{0}: {1:X2}{2:X2}{3:X2}" -f $k, $c.R, $c.G, $c.B }
}

$dir = 'H:\Windhawk Configuration\reports\2026-10-18-flyout-border'
$pg = [Dwm2]::FindWindow('Progman', 'Program Manager')
$dv = [Dwm2]::FindWindowEx($pg, [IntPtr]::Zero, 'SHELLDLL_DefView', $null)
$lv = [Dwm2]::FindWindowEx($dv, [IntPtr]::Zero, 'SysListView32', 'FolderView')
"listview=$lv"
$lp = [IntPtr](((900) -band 0xFFFF) -bor ((500 -band 0xFFFF) -shl 16))
[void][Dwm2]::PostMessage($lv, 0x0204, [IntPtr]2, $lp)
Start-Sleep -Milliseconds 60
[void][Dwm2]::PostMessage($lv, 0x0205, [IntPtr]::Zero, $lp)
$p = $null
for ($i = 0; $i -lt 12 -and -not $p; $i++) { Start-Sleep -Milliseconds 300; $p = Popup }
if (-not $p) { "NO MENU"; exit 3 }
"menu size $($p.W)x$($p.Hh) hwnd=0x$($p.H.ToInt64().ToString('X'))"
Start-Sleep -Milliseconds 400
$before = Grab $p
"BEFORE:"; Sample $before
$before.Save("$dir\dwm-test-before.png", [System.Drawing.Imaging.ImageFormat]::Png)

$cornerRound = 2; $accentBgr = 0x00FAB489
$hr1 = [Dwm2]::DwmSetWindowAttribute($p.H, 33, [ref]$cornerRound, 4)
$hr2 = [Dwm2]::DwmSetWindowAttribute($p.H, 34, [ref]$accentBgr, 4)
"DwmSetWindowAttribute corner hr=0x{0:X8} border hr=0x{1:X8}" -f $hr1, $hr2
Start-Sleep -Milliseconds 600
$after = Grab $p
"AFTER:"; Sample $after
$after.Save("$dir\dwm-test-after.png", [System.Drawing.Imaging.ImageFormat]::Png)

[IntPtr]$o = [IntPtr]::Zero
[void][Dwm2]::SendMessageTimeout($p.H, 0x001F, [IntPtr]::Zero, [IntPtr]::Zero, 0x0002, 2000, [ref]$o)
Start-Sleep -Milliseconds 500
if ([Dwm2]::IsWindowVisible($p.H)) { [void][Dwm2]::PostMessage($p.H, 0x0100, [IntPtr]0x1B, [IntPtr]::Zero); Start-Sleep -Milliseconds 300 }
"menu still visible after cancel: " + [Dwm2]::IsWindowVisible($p.H)
