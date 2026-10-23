# Read-only: dump the real window and UI Automation rectangles of the taskbar tray.
# Moves no input, focuses nothing. Output: one line per element right of x=1700.
# Use it to see where the tray frame sits inside the bar, not to guess a margin.
param([string]$Out = "H:\Windhawk Configuration\reports\2026-10-24-tray-go\geometry.txt")
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName UIAutomationClient, UIAutomationTypes
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class W32 {
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindowW(string c, string n);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindowExW(IntPtr p, IntPtr a, string c, string n);
}
"@
$lines = New-Object System.Collections.Generic.List[string]
$tb = [W32]::FindWindowW('Shell_TrayWnd', $null)
function Rect($h) { $r = New-Object W32+RECT; [void][W32]::GetWindowRect($h, [ref]$r); $r }
function Show($label, $h) { if ($h -eq [IntPtr]::Zero) { $lines.Add("$label : none"); return }; $r = Rect $h; $lines.Add(("{0,-22} x {1}..{2}  y {3}..{4}  h {5}" -f $label, $r.L, $r.R, $r.T, $r.B, ($r.B - $r.T))) }
$lines.Add("== Win32 (screen px)")
Show 'Shell_TrayWnd' $tb
$child = [IntPtr]::Zero
do {
  $child = [W32]::FindWindowExW($tb, $child, $null, $null)
  if ($child -ne [IntPtr]::Zero) {
    Show ("  child " + $child.ToString('X')) $child
  }
} while ($child -ne [IntPtr]::Zero)
$lines.Add("== UI Automation (x >= 1700)")
$bar = [System.Windows.Automation.AutomationElement]::FromHandle($tb)
if ($bar) {
  $all = $bar.FindAll([System.Windows.Automation.TreeScope]::Descendants, [System.Windows.Automation.Condition]::TrueCondition)
  $n = 0
  foreach ($e in $all) {
    $b = $e.Current.BoundingRectangle
    if ($b.IsEmpty -or $b.X -lt 1700 -or $b.Width -le 0) { continue }
    $lines.Add(("{0,-28} {1,-34} x {2,5:N0}..{3,5:N0}  y {4,3:N0}..{5,3:N0}  h {6,3:N0}" -f $e.Current.ClassName, $e.Current.AutomationId, $b.X, ($b.X + $b.Width), $b.Y, ($b.Y + $b.Height), $b.Height))
    $n++; if ($n -ge 120) { break }
  }
} else { $lines.Add("UIA: Shell_TrayWnd not found") }
New-Item -ItemType Directory -Force (Split-Path $Out) | Out-Null
$lines | Set-Content -Path $Out -Encoding utf8
$lines | Select-Object -First 140
