param([switch]$Install,[switch]$Rollback,[switch]$Audit)
$ErrorActionPreference='Stop'
$base='HKLM:\SOFTWARE\Windhawk\Engine'
$oldId='local@start-everything'
$newId='local@start-everything-plus'
$backup='H:\Windhawk Configuration\backups\2026-10-09\start-everything-plus'
$report='H:\Windhawk Configuration\reports\2026-10-09-start-everything-plus'
$source='H:\Windhawk Configuration\work\start-everything-plus-publish\mods\local\start-everything-plus\start-everything-plus.wh.cpp'
$library='local@start-everything-plus_1.0.4_710104.dll'
$oldSource="C:\ProgramData\Windhawk\ModsSource\$oldId.wh.cpp"
$newSource="C:\ProgramData\Windhawk\ModsSource\$newId.wh.cpp"
function Stamp($id) { New-ItemProperty "$base\Mods\$id" SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null }
if ($Install -and $Rollback) { throw 'Choose Install or Rollback.' }
if ($Install) {
    if (!(Test-Path "$report\$library")) { throw 'Build missing.' }
    New-Item -ItemType Directory -Force $backup | Out-Null
    if (!(Test-Path "$backup\old-mod.reg")) {
        if (Test-Path "$base\Mods\$newId") { throw 'New mod already exists; audit before migration.' }
        & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$oldId" "$backup\old-mod.reg" /y | Out-Null
        if ($LASTEXITCODE) { throw 'Registry backup failed.' }
        Copy-Item $oldSource "$backup\old-source.wh.cpp"
        if (Test-Path "$base\ModsWritable\$oldId") {
            & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\$oldId" "$backup\old-storage.reg" /y | Out-Null
            if ($LASTEXITCODE) { throw 'Storage backup failed.' }
        }
        $storage="C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage\$oldId"
        if (Test-Path $storage) { Copy-Item -LiteralPath $storage -Destination "$backup\mod-storage" -Recurse }
    }
    Copy-Item "$report\$library" "C:\ProgramData\Windhawk\Engine\Mods\64\$library" -Force
    Copy-Item $source $newSource -Force
    Set-ItemProperty "$base\Mods\$oldId" Disabled 1
    Stamp $oldId
    Start-Sleep -Seconds 3
    & reg.exe copy "HKLM\SOFTWARE\Windhawk\Engine\Mods\$oldId" "HKLM\SOFTWARE\Windhawk\Engine\Mods\$newId" /s /f | Out-Null
    if ($LASTEXITCODE) { throw 'Settings migration failed.' }
    Set-ItemProperty "$base\Mods\$newId" LibraryFileName $library
    Set-ItemProperty "$base\Mods\$newId" Version '1.0.4'
    if (Test-Path "$base\ModsWritable\$oldId") {
        & reg.exe copy "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\$oldId" "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\$newId" /s /f | Out-Null
        if ($LASTEXITCODE) { throw 'Storage migration failed.' }
    }
    if (Test-Path "$backup\mod-storage") {
        $destination="C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage\$newId"
        if (!(Test-Path $destination)) { Copy-Item "$backup\mod-storage" $destination -Recurse }
    }
    Set-ItemProperty "$base\Mods\$newId" Disabled 0
    Stamp $newId
    [ordered]@{ Time=(Get-Date).ToString('o'); OldId=$oldId; NewId=$newId; Library=$library; Author='DavidHiFi'; Version='1.0.4'; LibraryHash=(Get-FileHash "$report\$library").Hash; Runtime='Same executable and settings section as accepted working 1.0.4'; Migration='Full mod key, settings and any per-mod storage copied; old mod disabled for rollback' } | ConvertTo-Json | Set-Content "$report\receipt.json"
}
if ($Rollback) {
    if (Test-Path "$base\Mods\$newId") { Set-ItemProperty "$base\Mods\$newId" Disabled 1; Stamp $newId }
    Copy-Item "$backup\old-source.wh.cpp" $oldSource -Force
    & reg.exe import "$backup\old-mod.reg" | Out-Null
    if ($LASTEXITCODE) { throw 'Registry restore failed.' }
    Stamp $oldId
}
foreach ($id in @($oldId,$newId,'start-everything')) { if (Test-Path "$base\Mods\$id") { Get-ItemProperty "$base\Mods\$id" | Select-Object PSChildName,Disabled,Version,LibraryFileName } }
