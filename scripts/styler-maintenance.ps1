[CmdletBinding()]
param([switch]$Audit,[switch]$Install,[switch]$Rollback,[string]$BackupPath)
$ErrorActionPreference='Stop'
$root='H:\Windhawk Configuration'
$source="$root\work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp"
$live='C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$report="$root\reports\2026-10-09-styler-audit"
$cli='C:\Program Files\Windhawk\windhawk-cli.exe'
if ($Audit) {
    $state=Get-ItemProperty $key
    $version=[regex]::Match((Get-Content $source -Raw),'(?m)^// @version\s+(\S+)').Groups[1].Value
    $hash=(Get-FileHash $source).Hash
    $result=[ordered]@{time=(Get-Date -Format o);version=$state.Version;sourceVersion=$version;library=$state.LibraryFileName;
        include=$state.Include;disabled=$state.Disabled;sourceHash=$hash;installedSourceHash=(Get-FileHash $live).Hash;
        libraryHash=(Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$($state.LibraryFileName)").Hash;
        legacyMachine=[Environment]::GetEnvironmentVariable('WINDHAWK_USE_VSCODIUM_UI','Machine');
        legacyUser=[Environment]::GetEnvironmentVariable('WINDHAWK_USE_VSCODIUM_UI','User')}
    $result | ConvertTo-Json | Set-Content "$report\styler-audit.json" -Encoding UTF8
    $result | ConvertTo-Json
    if ($state.Disabled -or $state.Include -ne 'windhawk-ui.exe' -or $version -ne $state.Version -or
        $hash -ne $result.installedSourceHash -or $result.legacyMachine -eq '1' -or $result.legacyUser -eq '1') {
        throw 'Styler installation differs from its canonical source or selects the legacy interface.'
    }
    return
}
if (!$Install -and !$Rollback) { throw 'Choose -Audit, -Install or -Rollback.' }
New-Item -ItemType Directory -Force -Path $report | Out-Null
if ($Rollback) {
    if (!$BackupPath) { throw 'Specify the exact BackupPath from the install receipt.' }
    Copy-Item "$BackupPath\installed.wh.cpp" $live -Force
    Copy-Item "$BackupPath\installed.wh.cpp" $source -Force
    & reg.exe import "$BackupPath\mod.reg" | Out-Null
    if ($LASTEXITCODE) { throw 'Registry rollback failed.' }
} else {
    $BackupPath="$root\backups\2026-10-09\styler-audit\build-$(Get-Date -Format 'HHmmss')"
    New-Item -ItemType Directory -Path $BackupPath | Out-Null
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler' "$BackupPath\mod.reg" /y | Out-Null
    if ($LASTEXITCODE) { throw 'Mod backup failed.' }
    Copy-Item $live "$BackupPath\installed.wh.cpp"
    Copy-Item $source "$BackupPath\canonical.wh.cpp"
    $version=[regex]::Match((Get-Content $source -Raw),'(?m)^// @version\s+(\S+)').Groups[1].Value
    if (!$version) { throw 'Source version missing.' }
    Copy-Item $source $live -Force
}
$compiler=Start-Process $cli -ArgumentList '--json mod compile local@windhawk-styler' -WindowStyle Hidden -Wait -PassThru -RedirectStandardOutput "$report\compile-out.json" -RedirectStandardError "$report\compile-err.txt"
if ($compiler.ExitCode) { throw "Compile failed. See $report\compile-err.txt." }
$state=Get-ItemProperty $key
if ($state.Include -ne 'windhawk-ui.exe' -or $state.Disabled) { throw 'Compiler changed the intended scope or disabled the mod.' }
if ((Get-FileHash $source).Hash -ne (Get-FileHash $live).Hash) { throw 'Installed source mismatch.' }
[ordered]@{time=(Get-Date -Format o);version=$state.Version;library=$state.LibraryFileName;backup=$BackupPath;
    sourceHash=(Get-FileHash $live).Hash;rollback=[bool]$Rollback} |
    ConvertTo-Json | Set-Content "$report\build-receipt.json" -Encoding UTF8
Get-Content "$report\build-receipt.json"
