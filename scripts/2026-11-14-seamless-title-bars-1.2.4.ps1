# Seamless Title Bars 1.2.4: the hard-error boxes drawn by csrss.exe ("explorer.exe - System
# Error") get the dark title and blur too, set from inside DWM's own window record.
#   -Action Audit      version, hashes, settings (read only)
#   -Action Install    copy 1.2.3 aside, install 1.2.4 (hash guarded)
#   -Action Rollback   reinstall 1.2.3 (dwm boxes only)
# Engine steps re-run this script elevated. Never restarts the Windhawk engine.
param(
    [Parameter(Mandatory = $true)][ValidateSet('Audit', 'Install', 'Rollback')][string]$Action,
    [switch]$Elevated
)
$ErrorActionPreference = 'Stop'
$id = 'local@seamless-title-bars'
$root = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$storage = "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\$id\LocalStorage"
$newSrc = 'H:\Windhawk Configuration\work\2026-11-13-hung-dialog\v124\seamless-title-bars.wh.cpp'
$liveSrc = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$backup = 'H:\Windhawk Configuration\backups\2026-11-14\seamless-title-bars-1.2.4'
$copy123 = "$backup\seamless-title-bars-1.2.3.wh.cpp"
$log = "$backup\script.log"
$oldHash = 'CF1D1A997C227CE0EC45B5F35F313040E8509981B30309EC0F2396DEBBFCF84D'   # 1.2.3, the base of this build
$installer = 'H:\Windhawk Configuration\scripts\Install-StagedMod.ps1'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'

function Show-State {
    $k = Get-ItemProperty "Registry::$root\$id"
    $state = if ($k.Disabled -eq 1) { 'off' } else { 'ON' }
    "$id  $state  version $($k.Version)  $($k.LibraryFileName)"
    "  live source sha256: $((Get-FileHash $liveSrc).Hash)"
    $s = Get-ItemProperty "Registry::$root\$id\Settings"
    "  hungDialog: enabled $($s.'hungDialog.enabled')"
}

if ($Elevated) {
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    $stamp = Get-Date -Format 'yyyyMMdd-HHmm'
    try {
        reg export "$root\$id" "$backup\seamless-title-bars-$stamp.reg" /y | Out-Null
        reg export $storage "$backup\local-storage-$stamp.reg" /y | Out-Null
        switch ($Action) {
            'Install' {
                if (-not (Test-Path $copy123)) {
                    $live = (Get-FileHash $liveSrc).Hash
                    if ($live -ne $oldHash) { throw "live source is not 1.2.3 ($live): rebuild first" }
                    Copy-Item $liveSrc $copy123
                }
                & $installer -Id $id -Staged $newSrc -BaseHash $oldHash
                if ($LASTEXITCODE -ne 0) { throw "Install-StagedMod exit $LASTEXITCODE" }
            }
            'Rollback' {
                if (-not (Test-Path $copy123)) { throw 'no 1.2.3 copy to roll back to' }
                $p = Start-Process $cli -ArgumentList "mod install --file `"$copy123`"" -PassThru -WindowStyle Hidden
                if (-not $p.WaitForExit(600000)) { throw 'cli timed out' }
                $v = (Get-ItemProperty "Registry::$root\$id").Version
                if ($v -ne '1.2.3') { throw "registry version is $v after rollback" }
            }
        }
        Show-State
        'ELEVATED STEP OK'
    } catch {
        "ERROR: $_"
    }
    exit 0
}

switch ($Action) {
    'Audit' { Show-State }
    default {
        New-Item -ItemType Directory -Force -Path $backup | Out-Null
        $text = & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList "-Action $Action -Elevated" 2>&1 | Out-String
        Add-Content $log ("==== {0} {1}`n{2}" -f (Get-Date -Format s), $Action, $text)
        $text
        if ($text -notmatch 'ELEVATED STEP OK') { throw 'Elevated step failed; see the log above' }
    }
}
