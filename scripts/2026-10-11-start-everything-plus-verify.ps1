<#
.SYNOPSIS
    Live verification of the start-everything-plus 1.1.0 fork: idle compact view,
    expanded results, collapse back, mod-status and the adaptive layout log.
#>
param([string]$OutDir = "H:\Windhawk Configuration\reports\2026-10-11-start-everything-sync")
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System;using System.Runtime.InteropServices;
public class S {
[DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
[DllImport("user32.dll")] public static extern int GetSystemMetrics(int n);
}
'@
[void][S]::SetProcessDPIAware()
$w = [S]::GetSystemMetrics(0); $h = [S]::GetSystemMetrics(1)
function Shot([string]$name) {
    $bmp = New-Object System.Drawing.Bitmap $w, $h
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen(0, 0, 0, 0, [System.Drawing.Size]::new($w, $h))
    $g.Dispose()
    $bmp.Save("$OutDir\$name", [System.Drawing.Imaging.ImageFormat]::Png)
    $bmp.Dispose()
    "captured $name ($w x $h)"
}
$shell = New-Object -ComObject WScript.Shell
$shell.SendKeys('{ESC}'); Start-Sleep -Milliseconds 700      # close Start if open
$shell.SendKeys('^{ESC}'); Start-Sleep -Milliseconds 2000    # open Start -> compact idle
Shot 'verify-idle.png'
$shell.SendKeys('network'); Start-Sleep -Milliseconds 2500   # query -> expanded results
Shot 'verify-expanded.png'
$shell.SendKeys('{ESC}'); Start-Sleep -Milliseconds 1000     # back to compact
Shot 'verify-collapsed.png'
'--- mod-status entries ---'
Get-ChildItem 'C:\ProgramData\Windhawk\Engine\ModsWritable\mod-status' -Filter '*start-everything-plus*' -ErrorAction SilentlyContinue |
    Select-Object Name, LastWriteTime | Format-Table -AutoSize
'--- adaptive layout log tail ---'
$log = 'C:\ProgramData\Windhawk\Engine\ModsWritable\local@start-everything-plus-layout.log'
if (Test-Path $log) { Get-Content $log -Tail 15 } else { 'no layout log yet' }
