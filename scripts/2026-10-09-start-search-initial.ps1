param([switch]$Install,[switch]$Rollback,[switch]$Audit)
$ErrorActionPreference='Stop'
$base='HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$backup='H:\Windhawk Configuration\backups\2026-10-09\start-search-initial'
$report='H:\Windhawk Configuration\reports\2026-10-09-start-search-initial'
$work='H:\Windhawk Configuration\work\start-search-adaptive'
$library='local@start-everything_1.0.3_710102.dll'
$source='C:\ProgramData\Windhawk\ModsSource\local@start-everything.wh.cpp'
$ids=@('local@start-everything','start-menu-size','windows-11-start-menu-styler')
if ($Install -and $Rollback) { throw 'Choose Install or Rollback.' }
if ($Install) {
    if (!(Test-Path "$work\$library")) { throw 'Build missing.' }
    New-Item -ItemType Directory -Force $backup,$report | Out-Null
    if (!(Test-Path "$backup\before.json")) {
        foreach ($id in $ids) {
            & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\$id.reg" /y | Out-Null
            if ($LASTEXITCODE) { throw 'Registry backup failed.' }
        }
        Copy-Item $source "$backup\local-source.wh.cpp"
        [ordered]@{ Height=(Get-ItemProperty "$base\start-menu-size\Settings").height; Library=(Get-ItemProperty "$base\local@start-everything").LibraryFileName } | ConvertTo-Json | Set-Content "$backup\before.json"
    }
    Set-ItemProperty "$base\start-menu-size\Settings" height 0
    Set-ItemProperty "$base\start-menu-size" SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    Copy-Item "$work\$library" "C:\ProgramData\Windhawk\Engine\Mods\64\$library" -Force
    Copy-Item "$work\start-everything.wh.cpp" $source -Force
    Set-ItemProperty "$base\local@start-everything" LibraryFileName $library
    Set-ItemProperty "$base\local@start-everything" Version '1.0.3'
    Set-ItemProperty "$base\local@start-everything" SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    [ordered]@{ Time=(Get-Date).ToString('o'); Library=$library; Hash=(Get-FileHash "$work\$library").Hash; SizeModHeight=(Get-ItemProperty "$base\start-menu-size\Settings").height; Change='Show idle search box; collapse results and hints while idle; set frame Height=160 idle/500 searching; remove fixed size-mod height override'; Verification='Pending rendered check' } | ConvertTo-Json | Set-Content "$report\receipt.json"
}
if ($Rollback) {
    Copy-Item "$backup\local-source.wh.cpp" $source -Force
    foreach ($id in $ids) {
        & reg.exe import "$backup\$id.reg" | Out-Null
        if ($LASTEXITCODE) { throw 'Registry restore failed.' }
        Set-ItemProperty "$base\$id" SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    }
}
Get-ItemProperty "$base\local@start-everything" | Select-Object Disabled,Version,LibraryFileName
Get-ItemProperty "$base\start-menu-size\Settings" | Select-Object width,height,searchWidth,searchHeight
Get-Content 'C:\ProgramData\Windhawk\Engine\ModsWritable\local@start-everything-layout.log' -Tail 16 -ErrorAction SilentlyContinue
