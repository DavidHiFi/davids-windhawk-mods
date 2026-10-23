# Read-only stall test for LocalSend (its Receive-tab logo animates continuously, so unchanged pixels = a stall).
# Launches LocalSend, samples its window every 250 ms, lists what is injected into it, then closes it.
# Only hashes are computed; nothing on screen is saved.
param([int]$Runs = 3, [int]$Seconds = 30, [string]$Tag = 'test', [int]$X = [int]::MinValue, [int]$Y = 0)
Add-Type -AssemblyName System.Drawing, System.Windows.Forms
Add-Type @'
using System; using System.Runtime.InteropServices;
public static class TFS { [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L,T,R,B; }
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr after, int x, int y, int cx, int cy, uint f);
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint flags);
 [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
 public static bool Covers(IntPtr top, int x, int y) { POINT p; p.X = x; p.Y = y; return GetAncestor(WindowFromPoint(p), 2) == top; } }
'@ -ErrorAction SilentlyContinue
$exe = 'C:\Program Files\LocalSend\localsend_app.exe'
$log = "H:\System Configuration\reports\2026-09-27-flutter-stall-$Tag.txt"
$sha = [System.Security.Cryptography.SHA256]::Create()
$out = New-Object System.Collections.Generic.List[string]
for ($run = 1; $run -le $Runs; $run++) {
    Get-Process localsend_app -ErrorAction SilentlyContinue | Stop-Process -Force; Start-Sleep 2
    $t0 = Get-Date; Start-Process $exe
    do { Start-Sleep -Milliseconds 200; $p = Get-Process localsend_app -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowHandle -ne [IntPtr]::Zero } | Select-Object -First 1 } until ($p -or ((Get-Date) - $t0).TotalSeconds -gt 15)
    if ($X -ne [int]::MinValue) { Start-Sleep 1; [void][TFS]::SetWindowPos($p.MainWindowHandle, [IntPtr]::Zero, $X, $Y, 0, 0, 0x0001 -bor 0x0004) }
    $r0 = New-Object TFS+RECT; [void][TFS]::GetWindowRect($p.MainWindowHandle, [ref]$r0)
    $mon = [System.Windows.Forms.Screen]::FromHandle($p.MainWindowHandle).DeviceName
    $cx = [int](($r0.L + $r0.R) / 2); $cy = [int](($r0.T + $r0.B) / 2)
    $mon += ' visible=' + ([TFS]::Covers($p.MainWindowHandle, $cx, $cy) -and [TFS]::Covers($p.MainWindowHandle, $r0.L + 40, $r0.T + 60) -and [TFS]::Covers($p.MainWindowHandle, $r0.R - 40, $r0.B - 40))
    $prev = ''; $same = 0; $stalls = New-Object System.Collections.Generic.List[string]; $n = 0; $changes = 0
    $end = (Get-Date).AddSeconds($Seconds)
    while ((Get-Date) -lt $end) {
        $r = New-Object TFS+RECT; [void][TFS]::GetWindowRect($p.MainWindowHandle, [ref]$r)
        $w = $r.R - $r.L; $h = $r.B - $r.T
        $bmp = New-Object System.Drawing.Bitmap($w, $h)
        $g = [System.Drawing.Graphics]::FromImage($bmp); $g.CopyFromScreen($r.L, $r.T, 0, 0, (New-Object System.Drawing.Size($w, $h))); $g.Dispose()
        $ms = New-Object System.IO.MemoryStream; $bmp.Save($ms, [System.Drawing.Imaging.ImageFormat]::Bmp); $bmp.Dispose()
        $s = [BitConverter]::ToString($sha.ComputeHash($ms.ToArray()), 0, 4); $ms.Dispose(); $n++
        $at = ((Get-Date) - $t0).TotalSeconds
        if ($s -eq $prev) { $same++ } else {
            if ($same -ge 4) { $stalls.Add(('{0:N1}s@{1:N1}' -f ($same * 0.25), ($at - $same * 0.25))) }
            $same = 0; $changes++ }
        $prev = $s; Start-Sleep -Milliseconds 250
    }
    if ($same -ge 4) { $stalls.Add(('{0:N1}s@end' -f ($same * 0.25))) }
    $p.Refresh()
    $inj = ($p.Modules | Where-Object { $_.FileName -match 'RivaTuner|Windhawk|RTSS' } | ForEach-Object { $_.ModuleName }) -join ','
    $line = 'run {0} [{5} at {6},{7}]: samples={1} changes={2} stalls>=1s: {3} | injected: {4}' -f $run, $n, $changes, $(if ($stalls.Count) { $stalls -join ' ' } else { 'none' }), $inj, $mon, $r0.L, $r0.T
    $out.Add($line); $line
    Get-Process localsend_app -ErrorAction SilentlyContinue | Stop-Process -Force
}
$out | Set-Content -LiteralPath $log
