param([string]$Tag = 'x')
Add-Type -AssemblyName System.Drawing
Add-Type -TypeDefinition @"
using System; using System.Runtime.InteropServices;
public static class TW {
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern IntPtr FindWindowEx(IntPtr p, IntPtr a, string c, string t);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr SendMessageTimeout(IntPtr h, uint m, IntPtr w, IntPtr l, uint f, uint t, out IntPtr r);
}
"@
$dir = 'H:\Windhawk Configuration\reports\2026-10-18-flyout-border'
$stamp = Get-Date -Format 'HHmmss'
$p = Start-Process -FilePath 'H:\Windhawk Configuration\scripts\tools\FlyoutTestWindow.exe' -PassThru
Start-Sleep -Seconds 4
$p.Refresh()
$h = $p.MainWindowHandle
"test window pid=$($p.Id) hwnd=0x$($h.ToInt64().ToString('X'))"
$r = New-Object TW+RECT; [void][TW]::GetWindowRect($h, [ref]$r)
"test window rect=$($r.Left),$($r.Top),$($r.Right),$($r.Bottom)"
$x = $r.Left + 80; $y = $r.Top + 14
[void][TW]::PostMessage($h, 0x00A5, [IntPtr]2, [IntPtr](((($y) -band 0xFFFF) -shl 16) -bor ($x -band 0xFFFF)))
Start-Sleep -Milliseconds 1200
$best = $null; $hh = [IntPtr]::Zero
do { $hh = [TW]::FindWindowEx([IntPtr]::Zero, $hh, '#32768', $null)
  if ($hh -ne [IntPtr]::Zero -and [TW]::IsWindowVisible($hh)) { $q = New-Object TW+RECT; [void][TW]::GetWindowRect($hh, [ref]$q); $w = $q.Right-$q.Left; $ht = $q.Bottom-$q.Top; if ($w -gt 60 -and $ht -gt 60 -and (-not $best -or ($w*$ht) -gt $best.A)) { $best = [pscustomobject]@{H=$hh;R=$q;W=$w;Ht=$ht;A=$w*$ht} } }
} while ($hh -ne [IntPtr]::Zero)
if (-not $best) { "NO SYSTEM MENU FOUND"; Stop-Process -Id $p.Id -Force; exit 3 }
"system menu size $($best.W)x$($best.Ht)"
Start-Sleep -Milliseconds 400
$bmp = New-Object System.Drawing.Bitmap $best.W, $best.Ht
$g = [System.Drawing.Graphics]::FromImage($bmp); $g.CopyFromScreen($best.R.Left, $best.R.Top, 0, 0, (New-Object System.Drawing.Size $best.W, $best.Ht)); $g.Dispose()
$png = "$dir\test-window-sysmenu-$Tag-$stamp.png"; $bmp.Save($png, [System.Drawing.Imaging.ImageFormat]::Png); $bmp.Dispose()
"saved $png"
[IntPtr]$o = [IntPtr]::Zero
[void][TW]::SendMessageTimeout($best.H, 0x001F, [IntPtr]::Zero, [IntPtr]::Zero, 0x0002, 2000, [ref]$o)
Start-Sleep -Milliseconds 400
Stop-Process -Id $p.Id -Force -ErrorAction SilentlyContinue
"done"
