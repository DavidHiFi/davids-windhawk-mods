# Captures Shell_TrayWnd / secondary taskbar windows via PrintWindow (works when covered by fullscreen apps).
# Usage: powershell -NoProfile -ExecutionPolicy Bypass -File capture-tray.ps1 [outdir]
param([string]$OutDir = "H:\Windhawk Configuration\reports\2026-10-07-tray-gap")

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -TypeDefinition @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class TrayCap {
  public delegate bool EnumProc(IntPtr h, IntPtr lp);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr lp);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint flags);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L; public int T; public int R; public int B; }
}
"@

New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$found = New-Object System.Collections.ArrayList
$cb = [TrayCap+EnumProc]{
  param($h, $lp)
  $sb = New-Object System.Text.StringBuilder 256
  [void][TrayCap]::GetClassName($h, $sb, 256)
  $cn = $sb.ToString()
  if ($cn -eq 'Shell_TrayWnd' -or $cn -eq 'Shell_SecondaryTrayWnd') {
    $r = New-Object TrayCap+RECT
    [void][TrayCap]::GetWindowRect($h, [ref]$r)
    [void]$found.Add([pscustomobject]@{ Handle = $h; Cls = $cn; L = $r.L; T = $r.T; R = $r.R; B = $r.B; Vis = [TrayCap]::IsWindowVisible($h) })
  }
  return $true
}
[void][TrayCap]::EnumWindows($cb, [IntPtr]::Zero)

$i = 0
foreach ($f in $found) {
  $w = $f.R - $f.L; $h = $f.B - $f.T
  Write-Output "$($f.Cls) handle=$($f.Handle) visible=$($f.Vis) rect=($($f.L),$($f.T))-($($f.R),$($f.B)) size=${w}x${h}"
  if ($w -le 0 -or $h -le 0) { continue }
  $bmp = New-Object System.Drawing.Bitmap $w, $h
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $hdc = $g.GetHdc()
  [void][TrayCap]::PrintWindow($f.Handle, $hdc, 2)  # PW_RENDERFULLCONTENT
  $g.ReleaseHdc($hdc); $g.Dispose()
  $path = Join-Path $OutDir "traybar-$i.png"
  $bmp.Save($path)
  $bmp.Dispose()
  Write-Output "saved $path"
  $i++
}
if ($i -eq 0) { Write-Output "no tray windows found" }
