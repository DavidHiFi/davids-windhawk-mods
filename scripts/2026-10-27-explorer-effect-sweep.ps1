# For each styler backdrop effect: apply it, open This PC, capture the screen, close. Run elevated-capable shell.
$dir = 'H:\Windhawk Configuration\reports\2026-10-27-explorer-tabless'
foreach ($e in 'acrylicblur', 'acrylic', 'mica', '') {
    & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File 'H:\Windhawk Configuration\scripts\2026-10-27-explorer-styler-effect.ps1' -ArgumentList "-Effect '$e'" | Out-Null
    Start-Sleep 3
    $name = if ($e) { $e } else { 'default' }
    & 'H:\Windhawk Configuration\scripts\2026-10-27-explorer-screen-check.ps1' -OutFile "$dir\sweep-$name.png"
    Start-Sleep 2
}
