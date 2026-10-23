Add-Type -AssemblyName System.Windows.Forms, System.Drawing
Add-Type -TypeDefinition 'using System; using System.Runtime.InteropServices; public static class Cl { [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindowEx(IntPtr p, IntPtr a, string c, string t); }'
Get-Process explorer -ErrorAction SilentlyContinue | Stop-Process -Force
"killed explorer"
Start-Sleep -Seconds 20
$n = @(Get-Process explorer -ErrorAction SilentlyContinue).Count
"explorer count after wait (winlogon relaunch): $n"
if ($n -eq 0) { Start-Process explorer.exe; "started explorer once"; Start-Sleep -Seconds 15 }
Start-Sleep -Seconds 10
$pg = [Cl]::FindWindowEx([IntPtr]::Zero, [IntPtr]::Zero, 'Progman', $null)
$dv = [Cl]::FindWindowEx($pg, [IntPtr]::Zero, 'SHELLDLL_DefView', $null)
$lv = [Cl]::FindWindowEx($dv, [IntPtr]::Zero, 'SysListView32', 'FolderView')
"progman=$pg defview=$dv listview=$lv"
Get-Process explorer | Select-Object Id, StartTime | Format-Table | Out-String
$b = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
$bmp = New-Object System.Drawing.Bitmap $b.Width, $b.Height
$g = [System.Drawing.Graphics]::FromImage($bmp); $g.CopyFromScreen($b.Location, [System.Drawing.Point]::Empty, $b.Size); $g.Dispose()
$out = 'H:\Windhawk Configuration\reports\2026-10-18-flyout-border\screen-after-clean-shell-restart.png'
$bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Png); $bmp.Dispose()
"screen saved $out"
