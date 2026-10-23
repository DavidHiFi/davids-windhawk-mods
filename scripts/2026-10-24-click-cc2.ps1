# One left-click on the CC 2 quota bar (starts the mod's own sign-in), then put the cursor back.
Add-Type @'
using System; using System.Runtime.InteropServices;
public class M {
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out P p);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint x, uint y, uint d, IntPtr e);
  public struct P { public int X, Y; }
}
'@
$p = New-Object M+P; [M]::GetCursorPos([ref]$p) | Out-Null
[M]::SetCursorPos(2150, 25) | Out-Null; Start-Sleep -Milliseconds 300
[M]::mouse_event(0x2, 0, 0, 0, [IntPtr]::Zero); Start-Sleep -Milliseconds 60
[M]::mouse_event(0x4, 0, 0, 0, [IntPtr]::Zero); Start-Sleep -Milliseconds 300
[M]::SetCursorPos($p.X, $p.Y) | Out-Null
"clicked at 2150,25; cursor restored to $($p.X),$($p.Y)"
