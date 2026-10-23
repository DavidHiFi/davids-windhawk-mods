[CmdletBinding()]
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$ws = 'H:\Windhawk Configuration'
$source = "$ws\work\windhawk-styler\tauri20\windhawk-styler.wh.cpp"
$liveSource = 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp'
$backup = "$ws\backups\2026-10-09\styler-descriptions"
$report = "$ws\reports\2026-10-09-styler-descriptions"
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
if ($Install -or $Rollback) {
    New-Item -ItemType Directory -Force -Path $backup, $report | Out-Null
    if ($Rollback) {
        Copy-Item "$backup\ModsSource.wh.cpp" $liveSource -Force
        Copy-Item "$backup\work-source.wh.cpp" $source -Force
    } else {
        reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler' "$backup\mod-key.reg" /y | Out-Null
        Copy-Item $liveSource "$backup\ModsSource.wh.cpp" -Force
        Copy-Item $source "$backup\work-source.wh.cpp" -Force
        Copy-Item $source $liveSource -Force
    }
    $proc = Start-Process 'C:\Program Files\Windhawk\windhawk-cli.exe' -ArgumentList 'mod compile local@windhawk-styler' -WindowStyle Hidden -Wait -PassThru -RedirectStandardOutput "$report\compile-out.txt" -RedirectStandardError "$report\compile-err.txt"
    Get-Content "$report\compile-out.txt", "$report\compile-err.txt"
    if ($proc.ExitCode) { throw "Compile failed: $($proc.ExitCode)" }
    $state = Get-ItemProperty $key
    $wanted = if ($Rollback) { '2.0.12' } else { '2.0.13' }
    if ($state.Version -ne $wanted -or $state.Include -ne 'windhawk-ui.exe') { throw 'Unexpected installed mod state' }
    [PSCustomObject]@{when=(Get-Date).ToString('o');version=$state.Version;library=$state.LibraryFileName;include=$state.Include;backup=$backup;sourceHash=(Get-FileHash $source).Hash;liveSourceHash=(Get-FileHash $liveSource).Hash;rollback=[bool]$Rollback} | ConvertTo-Json | Set-Content "$report\receipt.json" -Encoding UTF8
}
Get-ItemProperty $key | Select-Object Version, LibraryFileName, Include, Disabled
Get-FileHash $source, $liveSource | ForEach-Object { "SHA256 $($_.Hash) $($_.Path)" }
if ($Audit) {
    $state = Get-ItemProperty $key
    if ($state.Version -ne '2.0.13') { throw 'Expected 2.0.13 installed' }
    $dll = "C:\ProgramData\Windhawk\Engine\Mods\64\$($state.LibraryFileName)"
    Get-FileHash $dll | ForEach-Object { "SHA256 $($_.Hash) $($_.Path)" }
    Get-Process -Name windhawk-ui | ForEach-Object {
        $ui = $_
        $ui.Modules | Where-Object ModuleName -eq $state.LibraryFileName | ForEach-Object {
            "Loaded in UI $($ui.Id): $($_.FileName)"
        }
    }
}
