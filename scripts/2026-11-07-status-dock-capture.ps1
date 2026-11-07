# Opens one Explorer window, captures it, dumps its child HWND tree, closes it.
param([string]$Out = 'H:\Windhawk Configuration\reports\2026-11-07-status-dock\before.png',
      [string]$Folder = 'C:\Windows', [switch]$Keep)
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text; using System.Collections.Generic;
public static class SD {
  [StructLayout(LayoutKind.Sequential)] public struct R { public int L, T, Rt, B; }
  public delegate bool P(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out R r);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool MoveWindow(IntPtr h, int x, int y, int w, int hh, bool p);
  [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr h, P p, IntPtr l);
  [DllImport("user32.dll")] public static extern IntPtr GetParent(IntPtr h);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  public static List<string> Tree(IntPtr root) {
    var o = new List<string>();
    EnumChildWindows(root, (h, l) => {
      var s = new StringBuilder(256); GetClassName(h, s, 256); R r; GetWindowRect(h, out r);
      int d = 0; for (IntPtr p = GetParent(h); p != root && p != IntPtr.Zero; p = GetParent(p)) d++;
      o.Add(new string(' ', d * 2) + s + " vis=" + IsWindowVisible(h) + " [" + r.L + "," + r.T + "," + r.Rt + "," + r.B + "]");
      return true; }, IntPtr.Zero);
    return o; }
}
'@
New-Item -ItemType Directory -Force -Path (Split-Path $Out) | Out-Null
$shell = New-Object -ComObject Shell.Application
$before = @($shell.Windows() | ForEach-Object { $_.HWND })
$shell.Open($Folder)
$win = $null
for ($i = 0; $i -lt 40 -and -not $win; $i++) {
    Start-Sleep -Milliseconds 250
    $win = $shell.Windows() | Where-Object { $before -notcontains $_.HWND } | Select-Object -First 1
}
if (-not $win) { throw 'no new Explorer window' }
$h = [IntPtr]$win.HWND
[SD]::MoveWindow($h, 120, 120, 1300, 700, $true) | Out-Null
[SD]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Seconds 4
$r = New-Object SD+R; [SD]::GetWindowRect($h, [ref]$r) | Out-Null
"frame [$($r.L),$($r.T),$($r.Rt),$($r.B)]"
[SD]::Tree($h) | Select-Object -First 80
$bmp = New-Object System.Drawing.Bitmap ($r.Rt - $r.L), ($r.B - $r.T)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($r.L, $r.T, 0, 0, $bmp.Size)
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
if (-not $Keep) { $win.Quit() }
"saved $Out"
