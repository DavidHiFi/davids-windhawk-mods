param([switch]$Install,[switch]$Rollback,[switch]$Audit)
$ErrorActionPreference='Stop'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@start-everything'
$backup='H:\Windhawk Configuration\backups\2026-10-09\start-search-footer'
$work='H:\Windhawk Configuration\work\start-search-adaptive'
$report='H:\Windhawk Configuration\reports\2026-10-09-start-search-footer'
$source='C:\ProgramData\Windhawk\ModsSource\local@start-everything.wh.cpp'
$library='local@start-everything_1.0.4_710103.dll'
if ($Install -and $Rollback) { throw 'Choose Install or Rollback.' }
if ($Install) {
    if (!(Test-Path "$work\$library")) { throw 'Build missing.' }
    New-Item -ItemType Directory -Force $backup,$report | Out-Null
    if (!(Test-Path "$backup\mod.reg")) {
        & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@start-everything' "$backup\mod.reg" /y | Out-Null
        if ($LASTEXITCODE) { throw 'Registry backup failed.' }
        Copy-Item $source "$backup\local-source.wh.cpp"
    }
    Copy-Item "$work\$library" "C:\ProgramData\Windhawk\Engine\Mods\64\$library" -Force
    Copy-Item "$work\start-everything.wh.cpp" $source -Force
    Set-ItemProperty $key LibraryFileName $library
    Set-ItemProperty $key Version '1.0.4'
    Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    [ordered]@{ Time=(Get-Date).ToString('o'); Library=$library; Hash=(Get-FileHash "$work\$library").Hash; Change='Limit idle overlay to search box height so native power/navigation controls remain uncovered'; Verification='Pending visual check' } | ConvertTo-Json | Set-Content "$report\receipt.json"
}
if ($Rollback) {
    Copy-Item "$backup\local-source.wh.cpp" $source -Force
    & reg.exe import "$backup\mod.reg" | Out-Null
    if ($LASTEXITCODE) { throw 'Registry restore failed.' }
    Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
}
Get-ItemProperty $key | Select-Object Disabled,Version,LibraryFileName
Get-Content 'C:\ProgramData\Windhawk\Engine\ModsWritable\local@start-everything-layout.log' -Tail 10 -ErrorAction SilentlyContinue
