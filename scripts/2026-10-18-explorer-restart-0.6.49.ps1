Add-Type -AssemblyName System.Windows.Forms, System.Drawing
Add-Type -TypeDefinition 'using System; using System.Runtime.InteropServices; public static class Ex2 { [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindowEx(IntPtr p, IntPtr a, string c, string t); }'
Get-Process explorer -ErrorAction SilentlyContinue | Stop-Process -Force
"explorer stopped"
Start-Sleep -Seconds 25
$n = @(Get-Process explorer -ErrorAction SilentlyContinue).Count
"explorer count after winlogon relaunch wait: $n"
if ($n -eq 0) { Start-Process explorer.exe; "started explorer once"; Start-Sleep -Seconds 15 }
$ready = $false
for ($i = 0; $i -lt 12 -and -not $ready; $i++) {
  Start-Sleep -Seconds 5
  $pg = [Ex2]::FindWindowEx([IntPtr]::Zero, [IntPtr]::Zero, 'Progman', 'Program Manager')
  $dv = [Ex2]::FindWindowEx($pg, [IntPtr]::Zero, 'SHELLDLL_DefView', $null)
  $ready = ($dv -ne [IntPtr]::Zero)
}
"desktop ready=$ready"
Get-Process explorer | ForEach-Object { $m = $_.Modules | Where-Object { $_.ModuleName -like 'local@translucent-flyouts*' } | ForEach-Object { $_.ModuleName }; "explorer pid=$($_.Id) mod=" + ($m -join ',') }
$b = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
$bmp = New-Object System.Drawing.Bitmap $b.Width, $b.Height
$g = [System.Drawing.Graphics]::FromImage($bmp); $g.CopyFromScreen($b.Location, [System.Drawing.Point]::Empty, $b.Size); $g.Dispose()
$bmp.Save('H:\Windhawk Configuration\reports\2026-10-18-flyout-border\screen-after-0.6.49-explorer-restart.png', [System.Drawing.Imaging.ImageFormat]::Png); $bmp.Dispose()
"screen saved"
