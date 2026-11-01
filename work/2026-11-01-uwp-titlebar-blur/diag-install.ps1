# Installs a diagnostic or work build of the mod from the given folder (run elevated).
param([string]$Dir = 'H:\Windhawk Configuration\work\2026-11-01-uwp-titlebar-blur\diag', [int]$Logging = -1, [switch]$Work)
$ErrorActionPreference = 'Continue'
if ($Work) { $Dir = Split-Path $Dir }
if ($Logging -ge 0) {
    Set-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@remove-uwp-title-bars-plus' LoggingEnabled $Logging -Type DWord
}
$out = & 'C:\Program Files\Windhawk\windhawk-cli.exe' mod install --file "$Dir\remove-uwp-title-bars-plus.wh.cpp" 2>&1 | Out-String
"exit $LASTEXITCODE"
$out | Select-String -Pattern 'error|Installed' | ForEach-Object { $_.Line }
