# Switches off the third-party mod win7-display-control-panel-restorer 1.1.0.
# Why: Explorer error boxes ("explorer.exe - System Error", 0xc0000005) started 10 Nov 9:52 pm,
# two and a half hours after it was installed (10 Nov 7:21 pm), about 160 boxes since, and two
# Explorer crash records name its DLL (12 Nov 2:23 am, 14 Nov 11:00 am).
#   -Action Disable | Enable (Enable is the rollback). Re-runs itself elevated.
param(
    [Parameter(Mandatory = $true)][ValidateSet('Disable', 'Enable')][string]$Action,
    [switch]$Elevated
)
$ErrorActionPreference = 'Stop'
$id = 'win7-display-control-panel-restorer'
$key = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id"
$backup = 'H:\Windhawk Configuration\backups\2026-11-14\win7-display-restorer'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
if ($Elevated) {
    try {
        New-Item -ItemType Directory -Force -Path $backup | Out-Null
        reg export $key "$backup\$id-$(Get-Date -Format 'yyyyMMdd-HHmm').reg" /y | Out-Null
        $verb = $Action.ToLower()
        $p = Start-Process $cli -ArgumentList "mod $verb $id --yes" -PassThru -WindowStyle Hidden -Wait
        $d = (Get-ItemProperty "Registry::$key").Disabled
        "cli exit $($p.ExitCode), Disabled=$d"
        if (($Action -eq 'Disable') -ne ($d -eq 1)) { throw "state did not change" }
        'ELEVATED STEP OK'
    } catch { "ERROR: $_" }
    exit 0
}
$text = & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList "-Action $Action -Elevated" 2>&1 | Out-String
$text
if ($text -notmatch 'ELEVATED STEP OK') { throw 'Elevated step failed' }
