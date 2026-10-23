param(
    [string]$OutJson = "",
    [switch]$Quiet
)

Add-Type -AssemblyName UIAutomationClient

function Get-TrayElements {
    $root = [System.Windows.Automation.AutomationElement]::RootElement
    $trayCond = New-Object System.Windows.Automation.PropertyCondition(
        [System.Windows.Automation.AutomationElement]::ClassNameProperty, 'Shell_TrayWnd')
    $tray = $root.FindFirst([System.Windows.Automation.TreeScope]::Children, $trayCond)
    if (-not $tray) { throw 'Shell_TrayWnd not found' }

    $all = $tray.FindAll([System.Windows.Automation.TreeScope]::Descendants,
        [System.Windows.Automation.Condition]::TrueCondition)

    $rows = @()
    foreach ($e in $all) {
        $c = $e.Current
        if ($c.ControlType.ProgrammaticName -ne 'ControlType.Button' -and
            $c.ControlType.ProgrammaticName -ne 'ControlType.ListItem') { continue }
        $r = $e.Current.BoundingRectangle
        if ([double]::IsInfinity($r.X) -or [double]::IsInfinity($r.Width)) { continue }
        $rows += [pscustomobject]@{
            Class = $c.ClassName
            Name  = $c.Name
            X     = [math]::Round($r.X, 1)
            W     = [math]::Round($r.Width, 1)
            Right = [math]::Round($r.Right, 1)
            Y     = [math]::Round($r.Y, 1)
            H     = [math]::Round($r.Height, 1)
        }
    }
    return $rows
}

$rows = Get-TrayElements
$watch = $rows | Where-Object {
    $_.Name -match '^(Clock|Network|Volume|Notifications|Show Hidden Icons|Show desktop|Clock )' -or
    $_.Class -match 'SystemTray\.(OmniButton|AccentButton)'
}
$watch = $watch | Sort-Object X, W

if (-not $Quiet) {
    $watch | Format-Table Class, X, W, Right, H, Name -AutoSize | Out-String -Width 200 | Write-Output
    $clock = $watch | Where-Object { $_.Name -like 'Clock*' } | Sort-Object X -Descending | Select-Object -First 1
    $net   = $watch | Where-Object { $_.Name -like 'Network*' } | Sort-Object X -Descending | Select-Object -First 1
    if ($clock -and $net) {
        Write-Output ("MEASURE clockX={0} clockRight={1} networkX={2} networkRight={3} gap={4}" -f `
            $clock.X, $clock.Right, $net.X, $net.Right, [math]::Round($clock.X - $net.Right, 1))
    }
}

if ($OutJson) {
    $rows | ConvertTo-Json -Depth 3 | Set-Content -LiteralPath $OutJson -Encoding UTF8
}
