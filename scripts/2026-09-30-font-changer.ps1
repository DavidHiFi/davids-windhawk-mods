[CmdletBinding()]
param([switch]$Audit, [switch]$Install, [switch]$Rollback, [switch]$VerificationProbe)
$ErrorActionPreference = 'Stop'
$root = 'H:\System Configuration'
$work = "$root\work\font-changer"
$backup = "$root\backups\2026-09-30\font-changer"
$report = "$root\reports\2026-09-30\font-changer"
$id = 'local@explorer-font-changer-davidhifi'
$originalKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\explorer-font-changer'
$forkKey = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$lib = "$($id)_1.0.1_1.dll"
if (@($Audit,$Install,$Rollback | Where-Object {$_}).Count -gt 1) {throw 'Choose one mode'}
if (!$Install -and !$Rollback) {
    foreach ($key in @($originalKey,$forkKey)) {
        if (Test-Path $key) {Get-ItemProperty $key | Select-Object PSChildName,Disabled,Include,Version,LibraryFileName}
    }
    if (Test-Path "$forkKey\Settings") {Get-ItemProperty "$forkKey\Settings" | Select-Object 'font.name'}
    exit 0
}
$principal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
if (!$principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {throw 'Elevated process required'}
New-Item -ItemType Directory -Force $report | Out-Null
if ($Rollback) {
    if (!(Test-Path "$backup\before.json")) {throw 'Backup receipt missing'}
    $before = Get-Content "$backup\before.json" -Raw | ConvertFrom-Json
    if (Test-Path $forkKey) {Set-ItemProperty $forkKey Disabled 1}
    & reg.exe import "$backup\original.reg"
    if ($LASTEXITCODE) {throw 'Registry restore failed'}
    if ((Get-ItemProperty $originalKey).Disabled -ne $before.originalDisabled) {throw 'Rollback verification failed'}
    Write-Output 'Original mod state restored; fork disabled. No engine or application restart.'
    exit 0
}
if (Test-Path $forkKey) {throw 'Fork already exists. Audit or rollback before another install'}
$source = "$work\repo\mods\local\explorer-font-changer-davidhifi\explorer-font-changer-davidhifi.wh.cpp"
foreach ($path in @($source,"$work\build\$($id)_1.0.0_1_64.dll","$work\build\$($id)_1.0.0_1_32.dll")) {
    if (!(Test-Path $path)) {throw "Missing build input $path"}
}
New-Item -ItemType Directory -Force $backup | Out-Null
if (Test-Path "$backup\before.json") {throw 'Preserving existing rollback backup'}
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\explorer-font-changer' "$backup\original.reg" /y
if ($LASTEXITCODE) {throw 'Backup failed'}
Copy-Item 'C:\ProgramData\Windhawk\ModsSource\explorer-font-changer.wh.cpp' "$backup\original.wh.cpp"
$original = Get-ItemProperty $originalKey
@{originalDisabled=$original.Disabled; originalLibrary=$original.LibraryFileName; originalInclude=$original.Include; timestamp=(Get-Date -Format o)} | ConvertTo-Json | Set-Content "$backup\before.json"
Copy-Item $source "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$hashes = @()
foreach ($arch in @('64','32')) {
    $src = "$work\build\$($id)_1.0.0_1_$arch.dll"
    $dest = "C:\ProgramData\Windhawk\Engine\Mods\$arch\$lib"
    Copy-Item $src $dest
    $expected = (Get-FileHash $src -Algorithm SHA256).Hash
    $actual = (Get-FileHash $dest -Algorithm SHA256).Hash
    if ($expected -ne $actual) {throw 'Installed DLL hash mismatch'}
    $hashes += @{architecture=$arch;path=$dest;sha256=$actual}
}
New-Item -Path $forkKey -Force | Out-Null
New-ItemProperty $forkKey Disabled -PropertyType DWord -Value 1 -Force | Out-Null
$values = @{
    LibraryFileName=$lib; Include='explorer.exe|StartMenuExperienceHost.exe|ShellExperienceHost.exe|SearchHost.exe|ShellHost.exe|SystemSettings.exe';
    Exclude=''; Architecture=''; Version='1.0.0'
}
foreach ($name in $values.Keys) {New-ItemProperty $forkKey $name -PropertyType String -Value $values[$name] -Force | Out-Null}
if ($VerificationProbe) {Set-ItemProperty $forkKey Include ($values.Include + '|font-changer-probe.exe')}
New-ItemProperty $forkKey SettingsChangeTime -PropertyType DWord -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Force | Out-Null
New-Item "$forkKey\Settings" -Force | Out-Null
$font = (Get-ItemProperty "$originalKey\Settings").'font.name'
New-ItemProperty "$forkKey\Settings" 'font.name' -PropertyType String -Value $font -Force | Out-Null
# The engine watches mod registry changes. Leave all applications running.
Set-ItemProperty $originalKey Disabled 1
Set-ItemProperty $forkKey Disabled 0
if ((Get-ItemProperty $forkKey).Disabled -ne 0 -or (Get-ItemProperty $originalKey).Disabled -ne 1) {throw 'Activation state verification failed'}
@{timestamp=(Get-Date -Format o);mod=$id;version='1.0.0';font=$font;include=$values.Include;originalDisabledBefore=$original.Disabled;originalDisabledAfter=1;dlls=$hashes;restartPerformed=$false;rollbackScript=$PSCommandPath} | ConvertTo-Json -Depth 5 | Set-Content "$report\install.json"
Write-Output "Installed $id using $font. Original disabled. No restart performed."
