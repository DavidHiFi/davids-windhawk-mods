# UIA: tray buttons and nested child rects around the network/clock region.
Add-Type -AssemblyName UIAutomationClient, UIAutomationTypes
$root = [System.Windows.Automation.AutomationElement]::RootElement
$cond = New-Object System.Windows.Automation.PropertyCondition([System.Windows.Automation.AutomationElement]::ClassNameProperty, 'Shell_TrayWnd')
$tray = $root.FindFirst([System.Windows.Automation.TreeScope]::Children, $cond)
if (-not $tray) { "no tray"; exit 1 }

function Dump($el, $depth) {
  $c = $el.FindAll([System.Windows.Automation.TreeScope]::Children, [System.Windows.Automation.Condition]::TrueCondition)
  foreach ($k in $c) {
    try {
      $r = $k.Current.BoundingRectangle
      if (-not $r.IsEmpty -and [int]$r.X -gt 2390) {
        $pad = ' ' * ($depth * 2)
        "{0}{1} | {2} | {3}" -f $pad, $k.Current.ClassName, $k.Current.AutomationId, ("{0},{1} {2}x{3}" -f [int]$r.X,[int]$r.Y,[int]$r.Width,[int]$r.Height)
      }
      Dump $k ($depth + 1)
    } catch {}
  }
}
Dump $tray 0
