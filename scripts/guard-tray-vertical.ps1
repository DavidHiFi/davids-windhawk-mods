# Defensive guard: restore the right-side tray cluster position, and the tray seam,
# if any agent/regression changes them back. Checked-by-read, write only on drift.
# Values verified good on 2026-10-19: notes\2026-10-19-tray-vertical-shift.md.
$ErrorActionPreference = 'Continue'
$modRoot = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$settings = "$modRoot\Settings"
$want = @{
    'controlStyles[63].target'    = 'SystemTray.SystemTrayFrame > StackPanel#SystemTrayFrameGrid, SystemTray.SystemTrayFrame > Grid#SystemTrayFrameGrid'
    'controlStyles[63].styles[0]' = 'VerticalAlignment=1'
    'controlStyles[63].styles[1]' = 'Margin=0,9,0,0'
    'controlStyles[61].styles[0]' = 'Margin=0,0,-4,0'
}
$drift = $false
foreach ($name in $want.Keys) {
    $have = (Get-Item -Path $settings).GetValue($name)
    if ($have -ne $want[$name]) {
        Write-Output "DRIFT: $name is '$have', want '$want[$name]'"
        $drift = $true
    }
}
if ($drift) {
    foreach ($name in $want.Keys) {
        New-ItemProperty -Path $settings -Name $name -Value $want[$name] -PropertyType String -Force | Out-Null
    }
    $ct = [int][math]::Round((Get-Date).ToUniversalTime().Subtract((Get-Date '1970-01-01T00:00:00Z')).TotalSeconds)
    New-ItemProperty -Path $modRoot -Name 'SettingsChangeTime' -Value $ct -PropertyType DWord -Force | Out-Null
    Write-Output "RESTORED all guard values, bumped SettingsChangeTime to $ct"
} else {
    Write-Output "OK: tray guard values match."
}