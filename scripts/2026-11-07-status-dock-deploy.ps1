# Installs File Explorer Styler Plus (status bar dock, 1.9.x) from the work copy. Run elevated.
# Rollback: windhawk-cli mod install --file backups\2026-11-07\status-dock\styler-plus-1.7.3.wh.cpp
param([string]$Source = 'H:\Windhawk Configuration\work\2026-11-07-status-dock\styler-plus.wh.cpp')
$ErrorActionPreference = 'Continue'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windows-11-file-explorer-styler-plus'
& $cli mod install --file $Source 2>&1 | Select-Object -First 30
"install exit $LASTEXITCODE"
$s = Join-Path $key 'Settings'
if ((Get-ItemProperty $s -ErrorAction SilentlyContinue).statusBarDock -eq $null) {
    New-ItemProperty $s -Name statusBarDock -PropertyType DWord -Value 1 -Force | Out-Null
    Set-ItemProperty $key -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -ErrorAction SilentlyContinue
    'statusBarDock default written'
}
Get-ItemProperty $key | Select-Object LibraryFileName, Version, Disabled | Format-List | Out-String
