# Captures the real Explorer title-bar system menu (2026-10-22). Opens a fresh
# Explorer folder window, posts WM_CONTEXTMENU on the title bar (same message a
# title-bar right-click produces), pulls the largest visible #32768 popup,
# screen-grabs it, then cancels the menu and closes the window. Desktop-touching:
# run under the coop desktop lock.
param([string]$Tag = 'x')
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -TypeDefinition @"
using System; using System.Runtime.InteropServices;
public static class EC {
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern IntPtr SendMessageTimeout(IntPtr h, uint m, IntPtr w, IntPtr l, uint f, uint t, out IntPtr r);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern int GetWindowTextW(IntPtr h, [MarshalAs(UnmanagedType.LPWStr)] System.Text.StringBuilder t, int n);
  [DllImport("user32.dll")] public static extern int GetClassNameW(IntPtr h, [MarshalAs(UnmanagedType.LPWStr)] System.Text.StringBuilder t, int n);
  [DllImport("user32.dll")] public static extern IntPtr FindWindowEx(IntPtr p, IntPtr a, string c, string t);
}
"@
$dir = 'H:\Windhawk Configuration\reports\2026-10-22-sysmenu-border'
$stamp = Get-Date -Format 'HHmmss'
Add-Type -TypeDefinition @"
using System; using System.Runtime.InteropServices;
public static class DPI { [DllImport("user32.dll")] public static extern bool SetProcessDPIAware(); }
"@
[void][DPI]::SetProcessDPIAware()

# Fresh folder window (Start-Process is fine here; the ban is only on
# Start-Process after killing the shell).
Start-Process -FilePath "$env:WINDIR\explorer.exe" -ArgumentList 'C:\Windows'
$folder = $null
foreach ($i in 1..40) {
    Start-Sleep -Milliseconds 400
    $cand = Get-Process explorer -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowHandle -ne 0 } |
        ForEach-Object { $hh = $_.MainWindowHandle; $cls = New-Object System.Text.StringBuilder 256; $ti = New-Object System.Text.StringBuilder 256;
            [void][EC]::GetClassNameW($hh, $cls, 256); [void][EC]::GetWindowTextW($hh, $ti, 256);
            [pscustomobject]@{ H = $hh; Pid = $_.Id; Cls = $cls.ToString(); Title = $ti.ToString() } } |
        Where-Object { $_.Cls -in @('CabinetWClass', 'ExplorerWClass') -and [EC]::IsWindowVisible($_.H) }
    if ($cand) { $folder = $cand | Select-Object -First 1; break }
}
if (-not $folder) { 'NO FOLDER WINDOW'; exit 3 }
"folder pid=$($folder.Pid) hwnd=0x$($folder.H.ToInt64().ToString('X')) title=$($folder.Title)"

# WM_SYSCOMMAND(SC_KEYMENU, space) = the Alt+Space path: opens the system menu
# without any coordinates, so no DPI scaling can break the point.
"folder rect=$($r.Left),$($r.Top),$($r.Right),$($r.Bottom) opening sysmenu via SC_KEYMENU"
[void][EC]::PostMessage($folder.H, 0x0112, [IntPtr][UInt32]0x0000F100, [IntPtr][UInt32]0x00000020)
Start-Sleep -Milliseconds 1500

# Largest visible #32768 popup.
$best = $null; $hh = [IntPtr]::Zero
do {
    $hh = [EC]::FindWindowEx([IntPtr]::Zero, $hh, '#32768', $null)
    if ($hh -ne [IntPtr]::Zero -and [EC]::IsWindowVisible($hh)) {
        $q = New-Object EC+RECT; [void][EC]::GetWindowRect($hh, [ref]$q)
        $w = $q.Right - $q.Left; $ht = $q.Bottom - $q.Top
        if ($w -gt 60 -and $ht -gt 60 -and (-not $best -or ($w * $ht) -gt $best.A)) {
            $best = [pscustomobject]@{ H = $hh; R = $q; W = $w; Ht = $ht; A = $w * $ht }
        }
    }
} while ($hh -ne [IntPtr]::Zero)
if (-not $best) { 'NO SYSTEM MENU FOUND'; exit 3 }
"system menu size $($best.W)x$($best.Ht) rect=$($best.R.Left),$($best.R.Top),$($best.R.Right),$($best.R.Bottom)"

Start-Sleep -Milliseconds 500
$bmp = New-Object System.Drawing.Bitmap $best.W, $best.Ht
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($best.R.Left, $best.R.Top, 0, 0, (New-Object System.Drawing.Size $best.W, $best.Ht))
$g.Dispose()
$png = "$dir\explorer-sysmenu-0663-$Tag-$stamp.png"
$bmp.Save($png, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"saved $png"

[intptr]$o = [IntPtr]::Zero
[void][EC]::SendMessageTimeout($best.H, 0x001F, [IntPtr]::Zero, [IntPtr]::Zero, 0x0002, 2000, [ref]$o)
Start-Sleep -Milliseconds 400
# Close the folder window (never the shell process).
[void][EC]::PostMessage($folder.H, 0x0010, [IntPtr]::Zero, [IntPtr]::Zero)
'done'
