# Open This PC, capture its on-screen pixels (shows real blur), then close it.
param([string]$OutFile)
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System; using System.Runtime.InteropServices;
public static class R { [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L,T,R,B; }
[DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
[DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
[DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h, uint m, IntPtr w, IntPtr l); }
"@
[R]::SetProcessDPIAware() | Out-Null
Start-Process explorer.exe 'shell:MyComputerFolder'
$h = [IntPtr]::Zero
for ($i = 0; $i -lt 30 -and $h -eq [IntPtr]::Zero; $i++) {
    Start-Sleep -Milliseconds 300
    $p = Get-Process explorer | Where-Object { $_.MainWindowTitle -like '* - File Explorer' } | Select-Object -First 1
    if ($p) { $h = $p.MainWindowHandle }
}
Start-Sleep 14
$r = New-Object R+RECT; [R]::GetWindowRect($h, [ref]$r) | Out-Null
$b = New-Object Drawing.Bitmap ($r.R - $r.L), ($r.B - $r.T)
$g = [Drawing.Graphics]::FromImage($b); $g.CopyFromScreen($r.L, $r.T, 0, 0, $b.Size); $g.Dispose()
$b.Save($OutFile); $b.Dispose()
[R]::PostMessageW($h, 0x10, [IntPtr]::Zero, [IntPtr]::Zero) | Out-Null
"saved $OutFile"
