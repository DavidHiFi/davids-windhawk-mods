# Moves, minimizes, restores and closes the Store frame and reports where the
# backdrop window is after each step.
$out = 'H:\Windhawk Configuration\work\2026-11-01-uwp-titlebar-blur'
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text;
public static class F {
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc p, IntPtr l);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr a, int x, int y, int cx, int cy, uint f);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern IntPtr GetWindow(IntPtr h, uint c);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  public static IntPtr Find(string cls, string title) {
    IntPtr found = IntPtr.Zero;
    EnumWindows((h, l) => {
      var c = new StringBuilder(64); GetClassName(h, c, 64);
      var t = new StringBuilder(64); GetWindowText(h, t, 64);
      if (c.ToString() == cls && (title == null || (t.ToString() == title && IsWindowVisible(h)))) { found = h; return false; }
      return true; }, IntPtr.Zero);
    return found;
  }
  public static int Count(string cls) {
    int n = 0;
    EnumWindows((h, l) => { var c = new StringBuilder(64); GetClassName(h, c, 64); if (c.ToString() == cls) n++; return true; }, IntPtr.Zero);
    return n;
  }
}
'@
$cls = 'RemoveUwpTitleBarsPlus_Backdrop'
function State($label, $frame) {
  $r = New-Object F+RECT; $b = New-Object F+RECT
  [void][F]::GetWindowRect($frame, [ref]$r)
  # The backdrop should be the window right below the frame.
  $below = [F]::GetWindow($frame, 2)
  $c = New-Object Text.StringBuilder 64; [void][F]::GetClassName($below, $c, 64)
  [void][F]::GetWindowRect($below, [ref]$b)
  "$label frame=($($r.L),$($r.T),$($r.R),$($r.B)) below=$c visible=$([F]::IsWindowVisible($below)) at ($($b.L),$($b.T),$($b.R),$($b.B)) backdrops=$([F]::Count($cls))"
}
$h = [F]::Find('ApplicationFrameWindow', 'Microsoft Store')
if ($h -eq [IntPtr]::Zero) {
  Start-Process 'ms-windows-store:'
  for ($i = 0; $i -lt 80 -and $h -eq [IntPtr]::Zero; $i++) { Start-Sleep -Milliseconds 250; $h = [F]::Find('ApplicationFrameWindow', 'Microsoft Store') }
  Start-Sleep -Seconds 4
}
if ($h -eq [IntPtr]::Zero) { 'no store frame'; exit 1 }
State 'start' $h
[void][F]::SetWindowPos($h, [IntPtr]::Zero, 320, 240, 1200, 760, 0x14); Start-Sleep -Milliseconds 800
State 'moved' $h
$shot = New-Object Drawing.Bitmap 1240, 120; $g = [Drawing.Graphics]::FromImage($shot); $g.CopyFromScreen(300, 220, 0, 0, $shot.Size); $g.Dispose(); $shot.Save("$out\follow-moved.png"); $shot.Dispose()
[void][F]::ShowWindow($h, 6); Start-Sleep -Milliseconds 1200
$vis = 0; [F]::EnumWindows({ param($w, $l) $c = New-Object Text.StringBuilder 64; [void][F]::GetClassName($w, $c, 64); if ($c.ToString() -eq $cls -and [F]::IsWindowVisible($w)) { $script:vis++ }; $true }, [IntPtr]::Zero) | Out-Null
"minimized visibleBackdrops=$vis"
[void][F]::ShowWindow($h, 9); Start-Sleep -Milliseconds 1200
State 'restored' $h
[void][F]::PostMessage($h, 0x10, [IntPtr]::Zero, [IntPtr]::Zero); Start-Sleep -Seconds 3
"closed backdrops=$([F]::Count($cls))"
