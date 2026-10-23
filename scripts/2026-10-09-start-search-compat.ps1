param([switch]$Install, [switch]$Rollback, [switch]$Audit)
$ErrorActionPreference = 'Stop'
$mod = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-start-menu-styler'
$settings = "$mod\Settings"
$backup = 'H:\Windhawk Configuration\backups\2026-10-09\start-search-compat'
$report = 'H:\Windhawk Configuration\reports\2026-10-09-start-search-compat'
$property = 'controlStyles[0].styles[0]'
if ($Install -and $Rollback) { throw 'Choose Install or Rollback.' }
if ($Install) {
    $current = Get-ItemProperty $settings
    if ($current.'controlStyles[0].target' -ne 'Grid#FrameRoot') { throw 'FrameRoot rule moved. Audit before applying.' }
    New-Item -ItemType Directory -Force $backup,$report | Out-Null
    if (!(Test-Path "$backup\before.json")) {
        & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-start-menu-styler' "$backup\start-menu-styler.reg" /y | Out-Null
        if ($LASTEXITCODE) { throw 'Registry backup failed.' }
        [ordered]@{ HeightLimit=$current.$property; Disabled=(Get-ItemProperty $mod).Disabled } | ConvertTo-Json | Set-Content "$backup\before.json"
    }
    Set-ItemProperty $settings $property 'MaxHeight=640'
    Set-ItemProperty $mod Disabled 0
    Set-ItemProperty $mod SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    [ordered]@{ Time=(Get-Date).ToString('o'); Change='FrameRoot MaxHeight=160 to MaxHeight=640; enable Start Menu Styler'; Original=(Get-Content "$backup\before.json" -Raw | ConvertFrom-Json); CurrentHeight=(Get-ItemProperty $settings).$property; Disabled=(Get-ItemProperty $mod).Disabled } | ConvertTo-Json -Depth 5 | Set-Content "$report\receipt.json"
}
if ($Rollback) {
    $original = Get-Content "$backup\before.json" -Raw | ConvertFrom-Json
    Set-ItemProperty $settings $property $original.HeightLimit
    Set-ItemProperty $mod Disabled ([int]$original.Disabled)
    Set-ItemProperty $mod SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
}
[pscustomobject]@{ HeightLimit=(Get-ItemProperty $settings).$property; Disabled=(Get-ItemProperty $mod).Disabled; Marker=(Get-ItemProperty $mod).SettingsChangeTime } | Format-List
