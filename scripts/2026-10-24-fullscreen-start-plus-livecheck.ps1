# Opens Fullscreen Start Plus with Ctrl+Esc (the same path as the Windows key),
# screenshots the monitor it opened on, reads its window rectangle, closes it.
param([string]$Out = 'H:\Windhawk Configuration\reports\2026-10-24-fullscreen-start-plus\live.png')
Add-Type -AssemblyName System.Windows.Forms, System.Drawing
Add-Type @'
using System; using System.Runtime.InteropServices;
public static class W {
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c, string n);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool SetProcessDpiAwarenessContext(IntPtr c);
  [DllImport("user32.dll")] public static extern void keybd_event(byte k, byte s, uint f, UIntPtr e);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  public static void Press(params byte[] keys) { foreach (var k in keys) keybd_event(k, 0, 0, UIntPtr.Zero); Array.Reverse(keys); foreach (var k in keys) keybd_event(k, 0, 2, UIntPtr.Zero); }
  public struct RECT { public int L, T, R, B; }
}
'@
[W]::SetProcessDpiAwarenessContext([IntPtr]-4) | Out-Null
$h = [W]::FindWindow('WindhawkFullscreenStartPlus', [NullString]::Value)
if ($h -eq [IntPtr]::Zero) { throw 'Plus window not found' }
if ($env:FSP_POST) { [W]::PostMessage($h, 0x8001, [IntPtr]::Zero, [IntPtr]::Zero) | Out-Null } else { [W]::Press([byte[]](0x11, 0x1B)) }  # toggle message or Ctrl+Esc
$timeline = @()
for ($i = 0; $i -lt 20; $i++) { Start-Sleep -Milliseconds 100; $timeline += [int][W]::IsWindowVisible($h); if ($i -eq 9 -and [W]::IsWindowVisible($h)) { break } }
"visible timeline (100 ms steps): $($timeline -join '')"
if ($env:FSP_EXTRA) { Start-Sleep -Milliseconds ([int]$env:FSP_EXTRA) }
"foreground: $([W]::GetForegroundWindow()) plus=$h"
$r = New-Object W+RECT; [W]::GetWindowRect($h, [ref]$r) | Out-Null
$visible = [W]::IsWindowVisible($h)
$screen = [System.Windows.Forms.Screen]::FromPoint([System.Drawing.Point]::new(($r.L + $r.R) / 2, ($r.T + $r.B) / 2))
$b = $screen.Bounds
$bmp = New-Object System.Drawing.Bitmap $b.Width, $b.Height
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($b.Location, [System.Drawing.Point]::Empty, $b.Size, [System.Drawing.CopyPixelOperation]::SourceCopy)
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png); $g.Dispose(); $bmp.Dispose()
if ([W]::IsWindowVisible($h)) { [W]::Press([byte[]](0x1B)) }  # Esc closes
Start-Sleep -Milliseconds 600
"visible=$visible window=($($r.L),$($r.T))-($($r.R),$($r.B)) monitor=$($screen.DeviceName) bounds=($($b.Left),$($b.Top))-($($b.Right),$($b.Bottom)) workarea=$($screen.WorkingArea) closedAfter=$(-not [W]::IsWindowVisible($h))"
'all monitors: ' + (([System.Windows.Forms.Screen]::AllScreens | ForEach-Object { "$($_.DeviceName) primary=$($_.Primary) $($_.Bounds)" }) -join ' | ')
