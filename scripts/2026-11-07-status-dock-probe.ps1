# Installs or removes the temporary status-dock probe mod (explorer.exe logger). Run elevated.
param([switch]$Install, [switch]$Remove)
$ErrorActionPreference = 'Continue'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$src = 'H:\Windhawk Configuration\work\2026-11-07-status-dock\status-dock-probe.wh.cpp'
if ($Install) { & $cli mod install --file $src 2>&1 | Select-Object -First 30; "exit $LASTEXITCODE" }
if ($Remove)  { & $cli --yes mod remove local@status-dock-probe 2>&1 | Select-Object -First 30; "exit $LASTEXITCODE" }
& $cli mod list 2>&1 | Select-String 'probe'
