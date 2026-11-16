# Seamless Title Bars 1.2.8 (the 1.2.7 sysbox change, rebased on the live 1.2.7 settings sync): csrss.exe system boxes get a see-through body over the blur (DWM's own
# blur-behind handler), and every captioned window gets DWM's dark title.
# sysbox.mode bits: 1 dark title on csrss boxes, 2 system backdrop, 4 see-through body,
# 8 dark title on every window. Install sets 15.
#   -Action Audit      version, hashes, settings (read only)
#   -Action Install    copy 1.2.7 aside, install 1.2.8, mode 15 (hash guarded)
#   -Action Rollback   reinstall 1.2.7, mode 3
#   -Action Mode -Mode N   set sysbox.mode (takes effect on the next box, no reinstall)
# Engine steps re-run this script elevated. Never restarts the Windhawk engine.
param(
    [Parameter(Mandatory = $true)][ValidateSet('Audit', 'Install', 'Rollback', 'Mode')][string]$Action,
    [int]$Mode = 15,
    [switch]$Elevated
)
$ErrorActionPreference = 'Stop'
$id = 'local@seamless-title-bars'
$root = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$storage = "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\$id\LocalStorage"
$newSrc = 'H:\Windhawk Configuration\work\2026-11-13-hung-dialog\v128\seamless-title-bars.wh.cpp'
$liveSrc = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$backup = 'H:\Windhawk Configuration\backups\2026-11-17\seamless-title-bars-1.2.8'
$copy126 = "$backup\seamless-title-bars-1.2.7.wh.cpp"
$log = "$backup\script.log"
$oldHash = 'C6FF8EB59A8404AF7BC94990AE208977F4D591283B6D5CE154F4CDBD019D184B'   # 1.2.7, the base of this build
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
                if (-not (Test-Path $copy126)) {
                    $live = (Get-FileHash $liveSrc).Hash
                    if ($live -ne $oldHash) { throw "live source is not 1.2.7 ($live): rebuild first" }
                    Copy-Item $liveSrc $copy126
                }
                & $installer -Id $id -Staged $newSrc -BaseHash $oldHash
                if ($LASTEXITCODE -ne 0) { throw "Install-StagedMod exit $LASTEXITCODE" }
                reg add $storage /v sysbox.mode /t REG_DWORD /d $Mode /f | Out-Null
            }
            'Mode' {
                reg add $storage /v sysbox.mode /t REG_DWORD /d $Mode /f | Out-Null
            }
            'Rollback' {
                if (-not (Test-Path $copy126)) { throw 'no 1.2.7 copy to roll back to' }
                $p = Start-Process $cli -ArgumentList "mod install --file `"$copy126`"" -PassThru -WindowStyle Hidden
                if (-not $p.WaitForExit(600000)) { throw 'cli timed out' }
                $v = (Get-ItemProperty "Registry::$root\$id").Version
                if ($v -ne '1.2.7') { throw "registry version is $v after rollback" }
                reg add $storage /v sysbox.mode /t REG_DWORD /d 3 /f | Out-Null
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
