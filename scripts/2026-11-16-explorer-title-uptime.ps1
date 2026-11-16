# Explorer Styler Plus 1.10.7: the window's uptime after the folder name in Explorer's title, using
# Seamless Title Bars' own uptime settings (that mod skips Explorer, which draws its own title).
#   -Action Audit      version, hashes, setting (read only)
#   -Action Install    copy 1.10.6 aside, set titleUptime=1, install 1.10.7 (hash guarded)
#   -Action Disable    turn the mod off at once (use if Explorer crashes)
#   -Action Rollback   reinstall 1.10.6
# Engine steps re-run this script elevated. Never restarts the Windhawk engine or Explorer.
param(
    [Parameter(Mandatory = $true)][ValidateSet('Audit', 'Install', 'Disable', 'Rollback')][string]$Action,
    [switch]$Elevated
)
$ErrorActionPreference = 'Stop'
$id = 'local@windows-11-file-explorer-styler-plus'
$root = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$newSrc = 'H:\Windhawk Configuration\work\2026-11-16-title-uptime-everywhere\styler-plus-1.10.7.wh.cpp'
$liveSrc = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$backup = 'H:\Windhawk Configuration\backups\2026-11-16\explorer-title-uptime'
$copyOld = "$backup\styler-plus-1.10.6.wh.cpp"
$log = "$backup\script.log"
$oldHash = '1D544B722AD24D59C514BF5C1972394A042B50F6C44C712C392DD1959FD496A3'   # 1.10.6, the base of this build
$installer = 'H:\Windhawk Configuration\scripts\Install-StagedMod.ps1'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'

function Show-State {
    $k = Get-ItemProperty "Registry::$root\$id"
    $state = if ($k.Disabled -eq 1) { 'off' } else { 'ON' }
    "$id  $state  version $($k.Version)  $($k.LibraryFileName)"
    "  live source sha256: $((Get-FileHash $liveSrc).Hash)"
    $s = Get-ItemProperty "Registry::$root\$id\Settings"
    "  titleUptime: $($s.titleUptime)"
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
        reg export "$root\$id" "$backup\styler-plus-$stamp.reg" /y | Out-Null
        switch ($Action) {
            'Install' {
                if (-not (Test-Path $copyOld)) {
                    $live = (Get-FileHash $liveSrc).Hash
                    if ($live -ne $oldHash) { throw "live source is not 1.10.6 ($live): rebuild first" }
                    Copy-Item $liveSrc $copyOld
                }
                # The CLI stores no settings for a new option, so its default goes in first.
                reg add "$root\$id\Settings" /v titleUptime /t REG_DWORD /d 1 /f | Out-Null
                & $installer -Id $id -Staged $newSrc -BaseHash $oldHash
                if ($LASTEXITCODE -ne 0) { throw "Install-StagedMod exit $LASTEXITCODE" }
                $v = (Get-ItemProperty "Registry::$root\$id").Version
                if ($v -ne '1.10.7') { throw "registry version is $v after install" }
            }
            'Disable' { Invoke-Cli "mod disable $id" }
            'Rollback' {
                if (-not (Test-Path $copyOld)) { throw 'no 1.10.6 copy to roll back to' }
                Invoke-Cli "mod install --file `"$copyOld`""
                $v = (Get-ItemProperty "Registry::$root\$id").Version
                if ($v -ne '1.10.6') { throw "registry version is $v after rollback" }
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
