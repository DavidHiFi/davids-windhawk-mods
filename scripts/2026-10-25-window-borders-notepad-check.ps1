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
[W]::SetForegroundWindow($h) | Out-Null
Start-Sleep 2
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
"closed notepad"

