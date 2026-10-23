Add-Type -AssemblyName System.Windows.Forms, System.Drawing
Add-Type -TypeDefinition @"
using System; using System.Runtime.InteropServices;
public static class Rec {
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindowEx(IntPtr p, IntPtr a, string c, string t);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr SendMessageTimeout(IntPtr h, uint m, IntPtr w, IntPtr l, uint f, uint t, out IntPtr r);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
}
"@
$cancelled = 0
$h = [IntPtr]::Zero
do {
  $h = [Rec]::FindWindowEx([IntPtr]::Zero, $h, '#32768', $null)
  if ($h -ne [IntPtr]::Zero -and [Rec]::IsWindowVisible($h)) {
    [IntPtr]$o = [IntPtr]::Zero
    [void][Rec]::SendMessageTimeout($h, 0x001F, [IntPtr]::Zero, [IntPtr]::Zero, 0x0002, 2000, [ref]$o)
    $cancelled++
  }
} while ($h -ne [IntPtr]::Zero)
"menus cancelled: $cancelled"
Start-Sleep -Milliseconds 800
Stop-Process -Name explorer -Force -ErrorAction SilentlyContinue
Start-Sleep -Seconds 2
Start-Process explorer.exe
Start-Sleep -Seconds 14
$exp = Get-Process explorer | Sort-Object StartTime -Descending | Select-Object -First 1
"explorer pid=$($exp.Id)"
"mod modules: " + (($exp.Modules | Where-Object { $_.ModuleName -like 'local@translucent*' } | ForEach-Object { $_.ModuleName }) -join ', ')
$pg = [Rec]::FindWindowEx([IntPtr]::Zero, [IntPtr]::Zero, 'Progman', $null)
$dv = [Rec]::FindWindowEx($pg, [IntPtr]::Zero, 'SHELLDLL_DefView', $null)
$lv = [Rec]::FindWindowEx($dv, [IntPtr]::Zero, 'SysListView32', 'FolderView')
"progman=$pg defview=$dv listview=$lv"
$b = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
$bmp = New-Object System.Drawing.Bitmap $b.Width, $b.Height
$g = [System.Drawing.Graphics]::FromImage($bmp); $g.CopyFromScreen($b.Location, [System.Drawing.Point]::Empty, $b.Size); $g.Dispose()
$out = 'H:\Windhawk Configuration\reports\2026-10-18-flyout-border\screen-after-rollback-recovery.png'
$bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Png); $bmp.Dispose()
"screen saved $out"
