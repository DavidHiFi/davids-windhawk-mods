Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class SwspKeys {
    [DllImport("user32.dll")]
    public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
}
"@

$out = 'H:\Windhawk Configuration\reports\2026-10-18-swsp-restore\alt-tab-after-restore.png'
New-Item -ItemType Directory -Force -Path (Split-Path -Parent $out) | Out-Null
$ex = [UIntPtr]::Zero

# Hold Alt, tap Tab once so the switcher opens.
[SwspKeys]::keybd_event(0x12, 0, 0, $ex)
Start-Sleep -Milliseconds 200
[SwspKeys]::keybd_event(0x09, 0, 0, $ex)
[SwspKeys]::keybd_event(0x09, 0, 2, $ex)
Start-Sleep -Milliseconds 900

# Capture every monitor while the switcher is open.
$b = [System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp = New-Object System.Drawing.Bitmap $b.Width, $b.Height
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($b.Location, [System.Drawing.Point]::Empty, $b.Size)
$bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose()
$bmp.Dispose()

# Escape cancels the switch, so focus and the cursor stay where they were.
[SwspKeys]::keybd_event(0x1B, 0, 0, $ex)
[SwspKeys]::keybd_event(0x1B, 0, 2, $ex)
Start-Sleep -Milliseconds 200
[SwspKeys]::keybd_event(0x12, 0, 2, $ex)
Write-Output "saved $out"
