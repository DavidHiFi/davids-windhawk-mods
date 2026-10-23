# UIA dump of the taskbar tray region: element classes, names, rects.
# Read-only inspection of the live Shell_TrayWnd tree.
Add-Type -AssemblyName UIAutomationClient, UIAutomationTypes
$root = [System.Windows.Automation.AutomationElement]::RootElement
$cond = New-Object System.Windows.Automation.PropertyCondition([System.Windows.Automation.AutomationElement]::ClassNameProperty, 'Shell_TrayWnd')
$tray = $root.FindFirst([System.Windows.Automation.TreeScope]::Children, $cond)
if (-not $tray) { "no Shell_TrayWnd"; exit 1 }
$all = $tray.FindAll([System.Windows.Automation.TreeScope]::Descendants, [System.Windows.Automation.Condition]::TrueCondition)
"total elements: $($all.Count)"
foreach ($e in $all) {
  try {
    $r = $e.Current.BoundingRectangle
    if ($r.IsEmpty) { continue }
    # only right side of taskbar (tray region) on primary
    if ($r.X -lt 1800) { continue }
    "{0:d5} {1} | {2} | {3}" -f [int]$r.X, $e.Current.ClassName, $e.Current.Name, "{0},{1} {2}x{3}" -f [int]$r.X, [int]$r.Y, [int]$r.Width, [int]$r.Height
  } catch {}
}
