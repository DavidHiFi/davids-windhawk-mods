[CmdletBinding()]
param([switch]$Audit,[switch]$Install,[switch]$Rollback)
$ErrorActionPreference='Stop'
$backup='H:\Windhawk Configuration\backups\2026-10-09\styler-audit'
$report='H:\Windhawk Configuration\reports\2026-10-09-styler-audit'
$cli='C:\Program Files\Windhawk\windhawk-cli.exe'
$mod='local@start-everything'
$key="HKLM:\SOFTWARE\Windhawk\Engine\Mods\$mod"
if ($Audit) {
    Get-ItemProperty $key | Select-Object Disabled,Version,LibraryFileName
    Get-CimInstance Win32_Process -Filter "Name='VSCodium.exe' OR Name='windhawk.exe'" |
        Select-Object Name,ProcessId,ExecutablePath,CommandLine
    return
}
if ($Rollback) {
    & reg.exe import "$backup\experimental-start-everything.reg" | Out-Null
    if ($LASTEXITCODE) { throw 'Experimental mod rollback failed.' }
    return
}
if (!$Install) { throw 'Choose -Audit, -Install or -Rollback.' }
if ((Test-Path $key) -and !(Test-Path "$backup\experimental-start-everything.reg")) {
    & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$mod" "$backup\experimental-start-everything.reg" /y | Out-Null
    if ($LASTEXITCODE) { throw 'Experimental mod backup failed.' }
}
if (Test-Path $key) {
    $p=Start-Process $cli -ArgumentList "--json mod disable $mod" -Wait -PassThru -WindowStyle Hidden -RedirectStandardOutput "$report\disable-experimental.json" -RedirectStandardError "$report\disable-experimental-err.txt"
    if ($p.ExitCode -or !(Get-ItemProperty $key).Disabled) { throw 'Experimental mod remains enabled.' }
}
$oldUi=@(Get-CimInstance Win32_Process -Filter "Name='VSCodium.exe'" | Where-Object ExecutablePath -eq 'C:\Program Files\Windhawk\UI\VSCodium.exe')
foreach ($item in $oldUi) { Stop-Process -Id $item.ProcessId -Force -ErrorAction SilentlyContinue }
$tray=@(Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" | Where-Object {
    $_.ExecutablePath -eq 'C:\Program Files\Windhawk\windhawk.exe' -and $_.CommandLine -match '(?:^|\s)-tray-only(?:\s|$)'
})
foreach ($item in $tray) { Stop-Process -Id $item.ProcessId -Force }
Remove-Item Env:ELECTRON_RUN_AS_NODE -ErrorAction SilentlyContinue
Remove-Item Env:WINDHAWK_USE_VSCODIUM_UI -ErrorAction SilentlyContinue
$env:APPDATA='C:\Users\localuser\AppData\Roaming'
Start-Process 'C:\Program Files\Windhawk\windhawk.exe' -ArgumentList '-tray-only' -WindowStyle Hidden
[ordered]@{time=(Get-Date -Format o);experimentalExists=(Test-Path $key);
    closedLegacyUi=@($oldUi.ProcessId);refreshedTray=@($tray.ProcessId);
    engineService=(Get-Service Windhawk).Status.ToString()} |
    ConvertTo-Json | Set-Content "$report\runtime-cleanup.json" -Encoding UTF8
Get-Content "$report\runtime-cleanup.json"
