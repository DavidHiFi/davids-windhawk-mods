# Puts a black/white stripe board behind the Store title bar and measures how
# sharp the stripe edges look through it. Blur turns hard edges into ramps.
param([string]$Tag = 'test', [switch]$KeepOpen, [switch]$Focus, [string]$Solid, [switch]$Reopen)
$out = 'H:\Windhawk Configuration\work\2026-11-01-uwp-titlebar-blur'
Add-Type -AssemblyName System.Windows.Forms, System.Drawing
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text;
public static class B {
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc p, IntPtr l);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr a, int x, int y, int cx, int cy, uint f);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  public static IntPtr Find(string title) {
    IntPtr found = IntPtr.Zero;
    EnumWindows((h, l) => {
      var c = new StringBuilder(64); GetClassName(h, c, 64);
      var t = new StringBuilder(64); GetWindowText(h, t, 64);
      if (c.ToString() == "ApplicationFrameWindow" && t.ToString() == title && IsWindowVisible(h)) { found = h; return false; }
      return true; }, IntPtr.Zero);
    return found;
  }
}
'@
$board = New-Object System.Windows.Forms.Form
$board.FormBorderStyle = 'None'; $board.StartPosition = 'Manual'; $board.ShowInTaskbar = $false
$board.Location = New-Object System.Drawing.Point(150, 120); $board.Size = New-Object System.Drawing.Size(1650, 140)
$bmp = New-Object System.Drawing.Bitmap 1650, 140
$g = [System.Drawing.Graphics]::FromImage($bmp)
if ($Solid) { $g.Clear([System.Drawing.Color]::FromName($Solid)) } else { for ($x = 0; $x -lt 1650; $x += 80) { $g.FillRectangle([System.Drawing.Brushes]::White, $x, 0, 40, 140); $g.FillRectangle([System.Drawing.Brushes]::Black, $x + 40, 0, 40, 140) } }
$g.Dispose(); $board.BackgroundImage = $bmp
$board.Show(); [System.Windows.Forms.Application]::DoEvents()

$h = [B]::Find('Microsoft Store')
$opened = $false
if ($h -ne [IntPtr]::Zero -and $Reopen) {
  [void][B]::PostMessage($h, 0x10, [IntPtr]::Zero, [IntPtr]::Zero)
  for ($i = 0; $i -lt 20 -and [B]::Find('Microsoft Store') -ne [IntPtr]::Zero; $i++) { Start-Sleep -Milliseconds 250; [System.Windows.Forms.Application]::DoEvents() }
  $h = [IntPtr]::Zero
}
if ($h -eq [IntPtr]::Zero) {
  Start-Process 'ms-windows-store:'; $opened = $true
  for ($i = 0; $i -lt 80 -and $h -eq [IntPtr]::Zero; $i++) { Start-Sleep -Milliseconds 250; [System.Windows.Forms.Application]::DoEvents(); $h = [B]::Find('Microsoft Store') }
}
if ($h -eq [IntPtr]::Zero) { 'no store frame'; $board.Close(); exit 1 }
for ($i = 0; $i -lt 20; $i++) { Start-Sleep -Milliseconds 250; [System.Windows.Forms.Application]::DoEvents() }
# Top of the z-order without activating, title bar over the board.
[void][B]::SetWindowPos($h, [IntPtr]::Zero, 200, 160, 1500, 900, 0x10)
if ($Focus) { [void][B]::SetForegroundWindow($h) }
for ($i = 0; $i -lt 12; $i++) { Start-Sleep -Milliseconds 250; [System.Windows.Forms.Application]::DoEvents() }
$fg = [B]::GetForegroundWindow()
$shot = New-Object System.Drawing.Bitmap 1500, 60
$sg = [System.Drawing.Graphics]::FromImage($shot)
$sg.CopyFromScreen(200, 150, 0, 0, $shot.Size); $sg.Dispose()
$shot.Save("$out\board-$Tag.png"); $shot.Dispose()
"frame=$h focused=$($fg -eq $h) saved board-$Tag.png"
if (-not $KeepOpen -and $opened) { [void][B]::PostMessage($h, 0x10, [IntPtr]::Zero, [IntPtr]::Zero) }
$board.Close()
