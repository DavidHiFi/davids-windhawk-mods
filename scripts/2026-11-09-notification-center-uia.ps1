# Opens the notification center via URI, dumps its UIA tree (names, ids, classes), closes it with Esc.
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName UIAutomationClient, UIAutomationTypes
Add-Type @'
using System; using System.Runtime.InteropServices;
public class NCK2 { [DllImport("user32.dll")] public static extern void keybd_event(byte k, byte s, uint f, UIntPtr e); }
'@
Start-Process 'ms-actioncenter:'
Start-Sleep -Milliseconds 3000
$root = [System.Windows.Automation.AutomationElement]::RootElement
$ids = @((Get-Process ShellExperienceHost,ShellHost -ErrorAction SilentlyContinue).Id)
$all = $root.FindAll([System.Windows.Automation.TreeScope]::Children, [System.Windows.Automation.Condition]::TrueCondition)
$wins = @($all | Where-Object { $ids -contains $_.Current.ProcessId })
"windows: " + ($wins | ForEach-Object { $_.Current.Name + "/" + $_.Current.ClassName }) -join "; "
$walker = [System.Windows.Automation.TreeWalker]::RawViewWalker
function Dump($e, $d) {
    if ($d -gt 25) { return }
    $c = $e.Current
    ('  ' * $d) + "[$($c.ClassName)] id=$($c.AutomationId) name=$($c.Name)"
    $ch = $walker.GetFirstChild($e)
    while ($ch) { Dump $ch ($d + 1); $ch = $walker.GetNextSibling($ch) }
}
foreach ($w in $wins) { Dump $w 0 }
[NCK2]::keybd_event(0x1B, 0, 0, [UIntPtr]::Zero); [NCK2]::keybd_event(0x1B, 0, 2, [UIntPtr]::Zero)

