# Opens one Explorer window, changes the selection through the shell view (no input),
# and captures the status bar several times right after, to catch transient artifacts.
# -Hover also posts WM_MOUSEMOVE to the folder view over each view button (the real
# cursor never moves) and captures the hover state, then switches views.
param([string]$OutDir = 'H:\Windhawk Configuration\reports\2026-11-07-status-dock\repro',
      [string]$Folder = 'C:\Windows', [string]$Tag = 'r', [switch]$Hover)
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text;
public static class SR {
  [StructLayout(LayoutKind.Sequential)] public struct R { public int L, T, Rt, B; }
  public delegate bool P(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out R r);
  [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out R r);
  [DllImport("user32.dll")] public static extern bool MoveWindow(IntPtr h, int x, int y, int w, int hh, bool p);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr h, P p, IntPtr l);
  [DllImport("user32.dll")] public static extern IntPtr GetParent(IntPtr h);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  public static IntPtr FolderView(IntPtr root) {
    IntPtr found = IntPtr.Zero;
    EnumChildWindows(root, (h, l) => {
      var s = new StringBuilder(64); GetClassName(h, s, 64);
      if (s.ToString() == "DirectUIHWND") {
        var p = new StringBuilder(64); GetClassName(GetParent(h), p, 64);
        if (p.ToString() == "DUIViewWndClassName") { found = h; return false; }
      }
      return true; }, IntPtr.Zero);
    return found; }
}
'@
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
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
Start-Sleep -Seconds 2
[SR]::MoveWindow($h, 120, 120, 1300, 700, $true) | Out-Null
[SR]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Seconds 3
$r = New-Object SR+R; [SR]::GetWindowRect($h, [ref]$r) | Out-Null
function Shot([string]$name) {
    $hgt = 60
    $bmp = New-Object System.Drawing.Bitmap ($r.Rt - $r.L), $hgt
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen($r.L, $r.B - $hgt, 0, 0, $bmp.Size)
    $bmp.Save((Join-Path $OutDir "$Tag-$name.png"), [System.Drawing.Imaging.ImageFormat]::Png)
    $g.Dispose(); $bmp.Dispose()
}
Shot 'idle'
$items = @($win.Document.Folder.Items())
foreach ($n in 0..2) {
    $win.Document.SelectItem($items[$n * 3], 1 + 4 + 8) | Out-Null
    Start-Sleep -Milliseconds 60;  Shot "sel$n-a"
    Start-Sleep -Milliseconds 250; Shot "sel$n-b"
    Start-Sleep -Milliseconds 1500; Shot "sel$n-c"
}
if ($Hover) {
    $fv = [SR]::FolderView($h)
    $c = New-Object SR+R; [SR]::GetClientRect($fv, [ref]$c) | Out-Null
    "folder view $fv client $($c.Rt)x$($c.B)"
    $y = $c.B - 12
    foreach ($b in @(@('details', 40), @('tiles', 16))) {
        $x = $c.Rt - $b[1]
        [SR]::PostMessage($fv, 0x200, [IntPtr]0, [IntPtr](($y -shl 16) -bor $x)) | Out-Null
        Start-Sleep -Milliseconds 400; Shot "hover-$($b[0])"
    }
    $x = $c.Rt / 2
    [SR]::PostMessage($fv, 0x200, [IntPtr]0, [IntPtr](($y -shl 16) -bor [int]$x)) | Out-Null
    [SR]::PostMessage($fv, 0x2A3, [IntPtr]0, [IntPtr]0) | Out-Null
    Start-Sleep -Milliseconds 400; Shot 'hover-none'
    $win.Document.CurrentViewMode = 1; Start-Sleep -Milliseconds 800; Shot 'view-icons'
    $win.Document.CurrentViewMode = 4; Start-Sleep -Milliseconds 800; Shot 'view-details'
}
$win.Quit()
"saved to $OutDir"
