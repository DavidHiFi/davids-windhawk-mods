# Installs or removes the temporary status glyph probe. Run elevated. -Remove uninstalls it.
param([switch]$Remove)
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
if ($Remove) { & $cli --yes mod remove local@status-glyph-probe 2>&1 | Select-Object -First 10; "remove exit $LASTEXITCODE"; return }
& $cli mod install --file 'H:\Windhawk Configuration\work\2026-11-07-status-dock\glyph-probe.wh.cpp' 2>&1 | Select-Object -First 30
"install exit $LASTEXITCODE"
