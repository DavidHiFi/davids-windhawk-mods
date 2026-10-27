# PrintWindow capture of the first visible File Explorer window (CabinetWClass), no focus change.
param([string]$OutFile)
Add-Type -ReferencedAssemblies System.Drawing @"
using System; using System.Runtime.InteropServices;
public static class ExCap {
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
    [DllImport("user32.dll")] public static extern IntPtr FindWindowW(string c, string t);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint f);
    [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
    [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
}
"@
[ExCap]::SetProcessDPIAware() | Out-Null
$h = (Get-Process explorer | Where-Object { $_.MainWindowTitle -like "* - File Explorer" } | Select-Object -First 1).MainWindowHandle; if (-not $h) { $h = [IntPtr]::Zero }
if ($h -eq [IntPtr]::Zero) { 'no explorer window'; exit 2 }
if ([ExCap]::IsIconic($h)) { 'minimized'; exit 3 }
$r = New-Object ExCap+RECT; [ExCap]::GetWindowRect($h, [ref]$r) | Out-Null
$bmp = New-Object System.Drawing.Bitmap ($r.R - $r.L), ($r.B - $r.T)
$g = [System.Drawing.Graphics]::FromImage($bmp); $hdc = $g.GetHdc()
[ExCap]::PrintWindow($h, $hdc, 2) | Out-Null
$g.ReleaseHdc($hdc); $g.Dispose(); $bmp.Save($OutFile); $bmp.Dispose()
"saved $OutFile $($r.R - $r.L)x$($r.B - $r.T)"
