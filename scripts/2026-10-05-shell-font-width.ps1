[CmdletBinding()]
param([switch]$Audit,[switch]$Install,[switch]$Rollback,[switch]$Probe)
$ErrorActionPreference='Stop'
$root='H:\Windhawk Configuration'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@shell-font-changer'
$backup="$root\backups\2026-10-05-shell-font-width"
$report="$root\reports\2026-10-05-shell-font-width"
$repo="$root\davids-windhawk-mods\mods\local\shell-font-changer"
$data='C:\ProgramData\Windhawk'
$p=Get-ItemProperty $key
if (!$Install -and !$Rollback -and !$Probe) {
    $p | Select-Object Disabled,LibraryFileName,Version,Include
    Get-ItemProperty "$key\Settings" | Select-Object 'font.name'
    foreach ($arch in '64','32') {Get-FileHash "$data\Engine\Mods\$arch\$($p.LibraryFileName)"}
    return
}
$principal=New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
if (!$principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {throw 'Elevated process required'}
if ($Rollback) {
    & reg.exe import "$backup\before.reg"
    if ($LASTEXITCODE) {throw 'Registry rollback failed'}
    Copy-Item "$backup\source.wh.cpp" "$data\ModsSource\local@shell-font-changer.wh.cpp" -Force
    $before=Get-Content "$backup\before.json" -Raw | ConvertFrom-Json
    if ((Get-ItemProperty $key).LibraryFileName -ne $before.LibraryFileName) {throw 'Rollback verification failed'}
    Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    Write-Output 'Restored previous source, library and settings.'
    return
}
if ($Probe) {
    $before=Get-Content "$backup\before.json" -Raw | ConvertFrom-Json
    Set-ItemProperty $key Include ($before.Include+'|shell-font-width-probe.exe')
    Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    try {
        $env:PATH="$data\Engine\Mods\64;"+$env:PATH
        $process=Start-Process "$report\shell-font-width-probe.exe" -WindowStyle Hidden -PassThru -Wait
        if ($process.ExitCode -ne 0) {throw "Live probe failed: $($process.ExitCode)"}
    } finally {
        Set-ItemProperty $key Include $before.Include
        Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    }
    return
}
New-Item -ItemType Directory -Force $backup,$report | Out-Null
if (!(Test-Path "$backup\before.reg")) {
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@shell-font-changer' "$backup\before.reg" /y
if ($LASTEXITCODE) {throw 'Registry export failed'}
$p | Select-Object Disabled,LibraryFileName,Version,Include | ConvertTo-Json | Set-Content "$backup\before.json"
Copy-Item "$data\ModsSource\local@shell-font-changer.wh.cpp" "$backup\source.wh.cpp"
}
foreach ($arch in '64','32') {
    if (!(Test-Path "$backup\old-$arch.dll")) {Copy-Item "$data\Engine\Mods\$arch\$($p.LibraryFileName)" "$backup\old-$arch.dll"}
    $source="$repo\build\local@shell-font-changer_1.2.2_4_$arch.dll"
    $dest="$data\Engine\Mods\$arch\local@shell-font-changer_1.2.2_4.dll"
    Copy-Item $source $dest
    if ((Get-FileHash $source).Hash -ne (Get-FileHash $dest).Hash) {throw 'Installed hash mismatch'}
}
Copy-Item "$repo\shell-font-changer.wh.cpp" "$data\ModsSource\local@shell-font-changer.wh.cpp" -Force
Set-ItemProperty $key LibraryFileName 'local@shell-font-changer_1.2.2_4.dll'
Set-ItemProperty $key Version '1.2.2'
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
$after=Get-ItemProperty $key
if ($after.LibraryFileName -ne 'local@shell-font-changer_1.2.2_4.dll' -or $after.Disabled -ne $p.Disabled -or $after.Include -ne $p.Include) {throw 'Install readback mismatch'}
@{timestamp=(Get-Date -Format o);before=$p.LibraryFileName;after=$after.LibraryFileName;font=(Get-ItemProperty "$key\Settings").'font.name';include=$after.Include;dlls=@(foreach($arch in '64','32'){Get-FileHash "$data\Engine\Mods\$arch\$($after.LibraryFileName)"});sourceHash=(Get-FileHash "$data\ModsSource\local@shell-font-changer.wh.cpp").Hash} | ConvertTo-Json -Depth 5 | Set-Content "$report\install.json"
Write-Output 'Installed 1.2.2. Settings and targets preserved. Engine watches registry changes.'
