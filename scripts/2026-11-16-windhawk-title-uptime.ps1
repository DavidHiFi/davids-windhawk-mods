# Enhanced Styler 2.2.7: the window's uptime after the Windhawk window's own title, using
# Seamless Title Bars' own uptime settings (this window paints its own caption, so DWM never adds it).
#   -Action Audit      version, hashes, setting (read only)
#   -Action Install    copy 2.2.6 aside, install 2.2.7 (hash guarded)
#   -Action Disable    turn the mod off at once (use if the Windhawk window breaks)
#   -Action Rollback   reinstall 2.2.6
# Engine steps re-run this script elevated. Never restarts the Windhawk engine or Explorer.
param(
    [Parameter(Mandatory = $true)][ValidateSet('Audit', 'Install', 'Disable', 'Rollback')][string]$Action,
    [switch]$Elevated
)
$ErrorActionPreference = 'Stop'
$id = 'local@windhawk-enhanced-styler'
$root = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$newSrc = 'H:\Windhawk Configuration\work\2026-11-16-title-uptime-everywhere\enhanced-styler-2.2.7.wh.cpp'
$liveSrc = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$backup = 'H:\Windhawk Configuration\backups\2026-11-16\windhawk-title-uptime'
$copyOld = "$backup\enhanced-styler-2.2.6.wh.cpp"
$log = "$backup\script.log"
$oldHash = '175508009142048B98E2081C7F14CE48307E1A33D9C40F1D25BB002FFBDE52C1'   # 2.2.6, the base of this build
$installer = 'H:\Windhawk Configuration\scripts\Install-StagedMod.ps1'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'

function Show-State {
    $k = Get-ItemProperty "Registry::$root\$id"
    $state = if ($k.Disabled -eq 1) { 'off' } else { 'ON' }
    "$id  $state  version $($k.Version)  $($k.LibraryFileName)"
    "  live source sha256: $((Get-FileHash $liveSrc).Hash)"
}

function Invoke-Cli([string]$arguments) {
    $p = Start-Process $cli -ArgumentList $arguments -PassThru -WindowStyle Hidden
    if (-not $p.WaitForExit(600000)) { throw "cli timed out: $arguments" }
    if ($p.ExitCode -ne 0) { throw "cli exit $($p.ExitCode): $arguments" }
}

if ($Elevated) {
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    $stamp = Get-Date -Format 'yyyyMMdd-HHmm'
    try {
        reg export "$root\$id" "$backup\enhanced-styler-$stamp.reg" /y | Out-Null
        switch ($Action) {
            'Install' {
                if (-not (Test-Path $copyOld)) {
                    $live = (Get-FileHash $liveSrc).Hash
                    if ($live -ne $oldHash) { throw "live source is not 2.2.6 ($live): rebuild first" }
                    Copy-Item $liveSrc $copyOld
                }
                & $installer -Id $id -Staged $newSrc -BaseHash $oldHash
                if ($LASTEXITCODE -ne 0) { throw "Install-StagedMod exit $LASTEXITCODE" }
                $v = (Get-ItemProperty "Registry::$root\$id").Version
                if ($v -ne '2.2.7') { throw "registry version is $v after install" }
            }
            'Disable' { Invoke-Cli "mod disable $id" }
            'Rollback' {
                if (-not (Test-Path $copyOld)) { throw 'no 2.2.6 copy to roll back to' }
                Invoke-Cli "mod install --file `"$copyOld`""
                $v = (Get-ItemProperty "Registry::$root\$id").Version
                if ($v -ne '2.2.6') { throw "registry version is $v after rollback" }
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
