param([Parameter(Mandatory)][ValidateSet('Audit','Backup','Install','Rollback')][string]$Phase)
& 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File 'H:\Windhawk Configuration\scripts\2026-10-08-windhawk-2a6-update.ps1' -ArgumentList "-$Phase"
exit $LASTEXITCODE
