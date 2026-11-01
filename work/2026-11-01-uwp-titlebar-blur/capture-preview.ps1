# Opens Settings, captures its title bar region from the screen focused and
# unfocused, logs frame facts, closes Settings.
$out = 'H:\Windhawk Configuration\work\2026-11-01-uwp-titlebar-blur'
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text;
public static class W {
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc p, IntPtr l);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr a, int x, int y, int cx, int cy, uint f);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern int GetWindowLong(IntPtr h, int i);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
  [DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h, int a, out RECT r, int s);
  [DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h, int a, out int v, int s);
  public static IntPtr Find() {
    IntPtr found = IntPtr.Zero;
    EnumWindows((h, l) => {
      var c = new StringBuilder(64); GetClassName(h, c, 64);
      var t = new StringBuilder(64); GetWindowText(h, t, 64);
      if (c.ToString() == "ApplicationFrameWindow" && t.ToString() == "Settings" && IsWindowVisible(h)) { found = h; return false; }
      return true; }, IntPtr.Zero);
    return found;
  }
}
'@
function Shot($h, $name) {
    $r = New-Object W+RECT
    [void][W]::DwmGetWindowAttribute($h, 9, [ref]$r, 16)  # extended frame bounds
    $w = $r.R - $r.L; $hh = 360
    $bmp = New-Object System.Drawing.Bitmap $w, $hh
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen($r.L, $r.T, 0, 0, $bmp.Size)
    $bmp.Save("$out\$name.png"); $g.Dispose(); $bmp.Dispose()
    "$name rect=$($r.L),$($r.T),$($r.R),$($r.B)"
}
$prevFg = [W]::GetForegroundWindow()
$existing = [W]::Find()
"existing settings frame: $existing"
Start-Process 'ms-settings:'
$h = [IntPtr]::Zero
for ($i = 0; $i -lt 60 -and $h -eq [IntPtr]::Zero; $i++) { Start-Sleep -Milliseconds 250; $h = [W]::Find() }
if ($h -eq [IntPtr]::Zero) { 'no settings frame'; exit 1 }
"frame $h"
Start-Sleep -Seconds 3
[void][W]::SetWindowPos($h, [IntPtr]::Zero, 200, 160, 1500, 1000, 0x14)  # NOZORDER|NOACTIVATE
Start-Sleep -Milliseconds 800
$cloak = 0; [void][W]::DwmGetWindowAttribute($h, 14, [ref]$cloak, 4)
"style=0x{0:X8} cloak=$cloak" -f [W]::GetWindowLong($h, -16)
[void][W]::SetForegroundWindow($h); Start-Sleep -Milliseconds 800
Shot $h 'settings-focused'
[void][W]::SetForegroundWindow($prevFg); Start-Sleep -Milliseconds 800
"fg after restore: $([W]::GetForegroundWindow()) (was $prevFg)"
Shot $h 'settings-unfocused'
$mods = (Get-Process ApplicationFrameHost).Modules | Where-Object ModuleName -like '*remove-uwp*' | ForEach-Object ModuleName
"loaded: $mods"
if ($existing -eq [IntPtr]::Zero) { [void][W]::PostMessage($h, 0x10, [IntPtr]::Zero, [IntPtr]::Zero); Start-Sleep 1; "closed; still there: $([W]::Find())" }
