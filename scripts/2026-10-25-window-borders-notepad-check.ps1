# Opens Notepad, confirms the window-borders DLL loaded, and captures the
# window plus a margin (the overlay ring sits around the frame) focused and unfocused.
param([string]$Out = 'H:\Windhawk Configuration\reports\2026-10-25-window-borders-live')
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System; using System.Runtime.InteropServices;
public static class W {
  [StructLayout(LayoutKind.Sequential)] public struct R { public int L, T, Rt, B; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out R r);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr a, int x, int y, int cx, int cy, uint f);
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern IntPtr FindWindow(string c, string n);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, IntPtr p);
  [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool f);
  [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out P p);
  [StructLayout(LayoutKind.Sequential)] public struct P { public int X, Y; }
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, int x, int y, uint d, UIntPtr e);
}
'@
[W]::SetProcessDPIAware() | Out-Null
$before = @(Get-Process notepad++ -ErrorAction SilentlyContinue).Id
Start-Process 'C:\Program Files\Notepad++\notepad++.exe' -ArgumentList '-multiInst','-nosession'
$p = $null
for ($i = 0; $i -lt 40 -and -not $p; $i++) {
  Start-Sleep -Milliseconds 250
  $p = Get-Process notepad++ -ErrorAction SilentlyContinue | Where-Object { $before -notcontains $_.Id -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
}
if (-not $p) { 'NO NOTEPAD WINDOW'; exit 1 }
$h = $p.MainWindowHandle
[W]::SetWindowPos($h, [IntPtr]::Zero, 300, 200, 900, 560, 0x40) | Out-Null
# Raise it above any topmost window, then borrow the foreground thread's input queue so focus is allowed.
[W]::SetWindowPos($h, [IntPtr](-1), 0, 0, 0, 0, 0x43) | Out-Null
$fg = [W]::GetWindowThreadProcessId([W]::GetForegroundWindow(), [IntPtr]::Zero); $me = [W]::GetCurrentThreadId()
[W]::AttachThreadInput($me, $fg, $true) | Out-Null; [W]::SetForegroundWindow($h) | Out-Null; [W]::AttachThreadInput($me, $fg, $false) | Out-Null
Start-Sleep 1
# Foreground lock can still refuse (seen with an elevated regedit in front). Minimizing the
# foreground window hands activation to the next window, our topmost Notepad++; it is restored at the end.
$parked = [IntPtr]::Zero
if ([W]::GetForegroundWindow() -ne $h) { $parked = [W]::GetForegroundWindow(); [W]::ShowWindow($parked, 6) | Out-Null; Start-Sleep 1 }
# Last resort: one real click on the title bar always activates; the cursor goes back where it was.
if ([W]::GetForegroundWindow() -ne $h) { $cp = New-Object W+P; [W]::GetCursorPos([ref]$cp) | Out-Null; [W]::SetCursorPos(500, 214) | Out-Null; [W]::mouse_event(2, 0, 0, 0, [UIntPtr]::Zero); [W]::mouse_event(4, 0, 0, 0, [UIntPtr]::Zero); [W]::SetCursorPos($cp.X, $cp.Y) | Out-Null; Start-Sleep 1 }
$fw = [W]::GetForegroundWindow()
"foreground is notepad: $($fw -eq $h)  (foreground app: $((Get-Process | ? MainWindowHandle -eq $fw).Name))"
$mods = (Get-Process -Id $p.Id).Modules | Where-Object ModuleName -like '*window-borders*' | ForEach-Object ModuleName
"pid=$($p.Id) loaded=$($mods -join ',')"
function Shot($name) {
  $r = New-Object W+R; [W]::GetWindowRect($h, [ref]$r) | Out-Null
  $m = 24; $x = $r.L - $m; $y = $r.T - $m; $w = $r.Rt - $r.L + 2*$m; $hh = $r.B - $r.T + 2*$m
  $bmp = New-Object Drawing.Bitmap $w, $hh
  $g = [Drawing.Graphics]::FromImage($bmp); $g.CopyFromScreen($x, $y, 0, 0, $bmp.Size); $g.Dispose()
  $f = Join-Path $Out $name; $bmp.Save($f, [Drawing.Imaging.ImageFormat]::Png); $bmp.Dispose(); "saved $f"
}
Shot 'notepad-focused.png'
# Move focus away (to the taskbar), then capture the unfocused look after the fade.
[W]::SetForegroundWindow([W]::FindWindow("Shell_TrayWnd", $null)) | Out-Null
Start-Sleep 1
Shot 'notepad-unfocused.png'
Stop-Process -Id $p.Id -Force
if ($parked -ne [IntPtr]::Zero) { [W]::ShowWindow($parked, 9) | Out-Null }
"closed notepad"



