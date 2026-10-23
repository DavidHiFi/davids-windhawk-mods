param([switch]$Install,[switch]$Rollback,[switch]$Audit)
$ErrorActionPreference='Stop'
$base='HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$backup='H:\Windhawk Configuration\backups\2026-10-09\start-search-adaptive'
$report='H:\Windhawk Configuration\reports\2026-10-09-start-search-adaptive'
$work='H:\Windhawk Configuration\work\start-search-adaptive'
$local="$base\local@start-everything"
$gallery="$base\start-everything"
$theme="$base\windows-11-start-menu-styler"
$library='local@start-everything_1.0.2_710101.dll'
if ($Install -and $Rollback) { throw 'Choose Install or Rollback.' }
if ($Install) {
    if (!(Test-Path "$work\$library")) { throw 'Build is missing.' }
    New-Item -ItemType Directory -Force $backup,$report | Out-Null
    if (!(Test-Path "$backup\before.json")) {
        foreach ($id in @('start-everything','windows-11-start-menu-styler')) {
            & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\$id.reg" /y | Out-Null
            if ($LASTEXITCODE) { throw 'Registry export failed.' }
        }
        $existed=Test-Path $local
        if ($existed) { & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@start-everything' "$backup\local-start-everything.reg" /y | Out-Null; if ($LASTEXITCODE) { throw 'Local registry export failed.' } }
        [ordered]@{ LocalExisted=$existed; GalleryDisabled=(Get-ItemProperty $gallery).Disabled; Height=(Get-ItemProperty "$theme\Settings").'controlStyles[0].styles[0]'; PowerGlyph=(Get-ItemProperty "$theme\Settings").'controlStyles[21].styles[0]' } | ConvertTo-Json | Set-Content "$backup\before.json" -Encoding UTF8
        if (Test-Path 'C:\ProgramData\Windhawk\ModsSource\local@start-everything.wh.cpp') { Copy-Item 'C:\ProgramData\Windhawk\ModsSource\local@start-everything.wh.cpp' "$backup\local-source.wh.cpp" }
    }
    Copy-Item "$work\$library" "C:\ProgramData\Windhawk\Engine\Mods\64\$library" -Force
    Copy-Item "$work\start-everything.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\local@start-everything.wh.cpp' -Force
    New-Item $local -Force | Out-Null
    foreach ($name in @('Include','Exclude','Architecture')) { New-ItemProperty $local $name -Value (Get-ItemProperty $gallery).$name -PropertyType String -Force | Out-Null }
    New-ItemProperty $local LibraryFileName -Value $library -PropertyType String -Force | Out-Null
    New-ItemProperty $local Version -Value '1.0.2' -PropertyType String -Force | Out-Null
    & reg.exe copy 'HKLM\SOFTWARE\Windhawk\Engine\Mods\start-everything\Settings' 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@start-everything\Settings' /s /f | Out-Null
    if ($LASTEXITCODE) { throw 'Settings copy failed.' }
    Set-ItemProperty $gallery Disabled 1
    New-ItemProperty $local Disabled -Value 0 -PropertyType DWord -Force | Out-Null
    Set-ItemProperty "$theme\Settings" 'controlStyles[21].styles[0]' ('Text='+[char]0xE7E8)
    foreach ($key in @($gallery,$local,$theme)) { New-ItemProperty $key SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null }
    [ordered]@{ Time=(Get-Date).ToString('o'); Library=$library; SourceHash=(Get-FileHash "$work\start-everything.wh.cpp").Hash; LibraryHash=(Get-FileHash "$work\$library").Hash; Behavior='160 DIP idle, 640 DIP ceiling while searching, one glyph per power icon'; Verified='Pending live visual test' } | ConvertTo-Json | Set-Content "$report\receipt.json" -Encoding UTF8
}
if ($Rollback) {
    if (Test-Path $local) { Set-ItemProperty $local Disabled 1 }
    foreach ($id in @('start-everything','windows-11-start-menu-styler')) { & reg.exe import "$backup\$id.reg" | Out-Null; if ($LASTEXITCODE) { throw 'Registry restore failed.' } }
    if (Test-Path "$backup\local-start-everything.reg") { & reg.exe import "$backup\local-start-everything.reg" | Out-Null }
    if (Test-Path "$backup\local-source.wh.cpp") { Copy-Item "$backup\local-source.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\local@start-everything.wh.cpp' -Force }
    foreach ($key in @($gallery,$local,$theme)) { if (Test-Path $key) { New-ItemProperty $key SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null } }
}
foreach ($key in @($gallery,$local,$theme)) { if (Test-Path $key) { Get-ItemProperty $key | Select-Object PSChildName,Disabled,LibraryFileName,SettingsChangeTime } }
$glyph=(Get-ItemProperty "$theme\Settings").'controlStyles[21].styles[0]'
'Power glyph codepoints: '+(($glyph.Substring(5).ToCharArray() | ForEach-Object { 'U+{0:X4}' -f [int]$_ }) -join ', ')
