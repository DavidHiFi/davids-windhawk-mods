# Seamless Title Bars 1.2.6: csrss.exe system box steps picked live from sysbox.mode in the mod's
# storage (1 dark title, 2 system backdrop, 4 full-glass margins; default 3).
#   -Action Audit      version, hashes, settings (read only)
#   -Action Install    copy 1.2.5 aside, install 1.2.6 (hash guarded)
#   -Action Rollback   reinstall 1.2.5
#   -Action Mode -Mode N   set sysbox.mode (takes effect on the next box, no reinstall)
# Engine steps re-run this script elevated. Never restarts the Windhawk engine.
param(
    [Parameter(Mandatory = $true)][ValidateSet('Audit', 'Install', 'Rollback', 'Mode')][string]$Action,
    [int]$Mode = 3,
    [switch]$Elevated
)
$ErrorActionPreference = 'Stop'
$id = 'local@seamless-title-bars'
$root = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$storage = "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\$id\LocalStorage"
$newSrc = 'H:\Windhawk Configuration\work\2026-11-13-hung-dialog\v126\seamless-title-bars.wh.cpp'
$liveSrc = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$backup = 'H:\Windhawk Configuration\backups\2026-11-14\seamless-title-bars-1.2.6'
$copy125 = "$backup\seamless-title-bars-1.2.5.wh.cpp"
$log = "$backup\script.log"
$oldHash = '1175DC6B050A7C9A7E8F37F244BD4148C4D18088AC2B78914E4E6173E417EB0B'   # 1.2.5, the base of this build
$installer = 'H:\Windhawk Configuration\scripts\Install-StagedMod.ps1'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'

function Show-State {
    $k = Get-ItemProperty "Registry::$root\$id"
    $state = if ($k.Disabled -eq 1) { 'off' } else { 'ON' }
    "$id  $state  version $($k.Version)  $($k.LibraryFileName)"
    "  live source sha256: $((Get-FileHash $liveSrc).Hash)"
    $s = Get-ItemProperty "Registry::$root\$id\Settings"
    "  hungDialog: enabled $($s.'hungDialog.enabled')"
    $st = Get-ItemProperty "Registry::$storage" -ErrorAction SilentlyContinue
    "  sysbox: " + (($st.PSObject.Properties | ? Name -like 'sysbox.*' | % { "$($_.Name -replace '^sysbox.','')=$($_.Value)" }) -join ' ')
}

if ($Elevated) {
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    $stamp = Get-Date -Format 'yyyyMMdd-HHmm'
    try {
        reg export "$root\$id" "$backup\seamless-title-bars-$stamp.reg" /y | Out-Null
        reg export $storage "$backup\local-storage-$stamp.reg" /y | Out-Null
        switch ($Action) {
            'Install' {
                if (-not (Test-Path $copy125)) {
                    $live = (Get-FileHash $liveSrc).Hash
                    if ($live -ne $oldHash) { throw "live source is not 1.2.5 ($live): rebuild first" }
                    Copy-Item $liveSrc $copy125
                }
                & $installer -Id $id -Staged $newSrc -BaseHash $oldHash
                if ($LASTEXITCODE -ne 0) { throw "Install-StagedMod exit $LASTEXITCODE" }
            }
            'Mode' {
                reg add $storage /v sysbox.mode /t REG_DWORD /d $Mode /f | Out-Null
            }
            'Rollback' {
                if (-not (Test-Path $copy125)) { throw 'no 1.2.5 copy to roll back to' }
                $p = Start-Process $cli -ArgumentList "mod install --file `"$copy125`"" -PassThru -WindowStyle Hidden
                if (-not $p.WaitForExit(600000)) { throw 'cli timed out' }
                $v = (Get-ItemProperty "Registry::$root\$id").Version
                if ($v -ne '1.2.5') { throw "registry version is $v after rollback" }
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
        $text = & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList "-Action $Action -Mode $Mode -Elevated" 2>&1 | Out-String
        Add-Content $log ("==== {0} {1}`n{2}" -f (Get-Date -Format s), $Action, $text)
        $text
        if ($text -notmatch 'ELEVATED STEP OK') { throw 'Elevated step failed; see the log above' }
    }
}
