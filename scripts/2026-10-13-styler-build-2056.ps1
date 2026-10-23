$ErrorActionPreference = 'Continue'
$modDir = 'H:\Windhawk Configuration\work\styler-release\mods\local\windhawk-styler'
$backup = 'H:\Windhawk Configuration\backups\2026-10-13\styler-polish-2056'
New-Item -ItemType Directory -Path $backup -Force | Out-Null
$log = Join-Path $backup 'build-log.txt'

# Build.ps1 sets $ErrorActionPreference='Stop', and under Windows PowerShell 5.1
# any native stderr line then becomes a terminating NativeCommandError that
# kills the build mid-way (64-bit ok, 32-bit never ran). Patch a temp copy:
# continue on native stderr, and resolve $PSScriptRoot to the real mod dir
# because the copy does not live there.
$src = Get-Content -LiteralPath (Join-Path $modDir 'Build.ps1') -Raw
$src = $src.Replace('$' + 'ErrorActionPreference' + " = 'Stop'", '$' + 'ErrorActionPreference' + " = 'Continue'")
$src = $src.Replace('$' + 'PSScriptRoot', "'" + $modDir + "'")
$tmpPs1 = Join-Path $env:TEMP 'styler-build-2056.ps1'
Set-Content -LiteralPath $tmpPs1 -Value $src -Encoding ASCII

$out = @()
$code = 0
try {
    $out = & $tmpPs1 2>&1
    $code = $LASTEXITCODE
}
catch {
    $out = @('TERMINATING: ' + $_.ToString())
    $code = 1
}
Write-Output ("build exit=" + $code)
$out | ForEach-Object { $_.ToString() } | Set-Content -LiteralPath $log -Encoding utf8
exit $code
