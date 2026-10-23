$ErrorActionPreference = 'Stop'
$log = 'H:\Windhawk Configuration\reports\2026-10-16-translucent-windows-description\install-log.txt'
Start-Transcript -Path $log -Force
try {
    & 'H:\Windhawk Configuration\scripts\2026-10-16-translucent-windows-description.ps1' -Action Install
    $global:TRANSCRIPT_EXIT = $LASTEXITCODE
}
finally { Stop-Transcript }
exit $global:TRANSCRIPT_EXIT
