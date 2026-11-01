# 2026-11-01 Right-click the Fluent Media Player Plus player once, capture the menu, press Escape,
# put the cursor back. Run under: coop lock desktop.
param([int]$X = 440, [int]$Y = 25, [string]$Out = 'H:\Windhawk Configuration\reports\2026-11-01-fluent-media-player-plus\menu-probe.png')
Add-Type -AssemblyName System.Drawing, System.Windows.Forms
Add-Type @'
using System; using System.Runtime.InteropServices;
public static class In {
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint d, IntPtr e);
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint f, IntPtr e);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c, string w);
}
'@
$saved = [System.Windows.Forms.Cursor]::Position
[In]::SetCursorPos($X, $Y); Start-Sleep -Milliseconds 150
[In]::mouse_event(0x0008, 0, 0, 0, [IntPtr]::Zero); Start-Sleep -Milliseconds 40
[In]::mouse_event(0x0010, 0, 0, 0, [IntPtr]::Zero)
Start-Sleep -Milliseconds 700
$menuUp = [In]::FindWindow('#32768', $null) -ne [IntPtr]::Zero
$b = New-Object Drawing.Bitmap 700, 260; $g = [Drawing.Graphics]::FromImage($b)
$g.CopyFromScreen($X - 120, 0, 0, 0, $b.Size); $b.Save($Out)
[In]::keybd_event(0x1B, 0, 0, [IntPtr]::Zero); [In]::keybd_event(0x1B, 0, 2, [IntPtr]::Zero)
Start-Sleep -Milliseconds 200
[In]::SetCursorPos($saved.X, $saved.Y)
"menuUp=$menuUp saved=$Out"
