# Seamless Title Bars 1.0.0 (local@seamless-title-bars): one mod that replaces
# the seven title bar mods.
#   -Action Audit     show the new mod and the seven old mods
#   -Action Compile   install the new mod disabled (compiles it, loads nothing)
#   -Action Swap      back up the old keys, disable the seven, enable the new one
#   -Action Rollback  disable the new mod and put the seven old keys back
# Engine steps re-run this script elevated. Never restarts the Windhawk engine.
# The old mods are only disabled, never removed.
param(
    [Parameter(Mandatory = $true)][ValidateSet('Audit', 'Compile', 'Swap', 'Rollback')][string]$Action,
    [switch]$Elevated
)
$ErrorActionPreference = 'Stop'
$id = 'local@seamless-title-bars'
$root = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$src = 'H:\Windhawk Configuration\work\2026-11-09-seamless-title-bars\out\seamless-title-bars.wh.cpp'
$backup = 'H:\Windhawk Configuration\backups\2026-11-09\seamless-title-bars'
$log = "$backup\script.log"
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$old = @(
    'caption-buttons-customizer', 'win11-custom-title-bar-colours',
    'local@remove-uwp-title-bars-plus', 'local@terminal-titlebar-blur',
    'titlebar-for-everyone', 'cef-titlebar-enabler-universal', 'fix-basic-caption-text'
)

function Invoke-Cli([string[]]$CliArgs) {
    $out = [IO.Path]::GetTempFileName(); $err = [IO.Path]::GetTempFileName()
    $argText = ($CliArgs | ForEach-Object { if ($_ -match '\s') { '"' + $_ + '"' } else { $_ } }) -join ' '
    $p = Start-Process $cli -ArgumentList $argText -NoNewWindow -PassThru `
        -RedirectStandardOutput $out -RedirectStandardError $err
    $null = $p.Handle  # keeps the handle so ExitCode is readable
    $timeout = if ($CliArgs[1] -eq 'install') { 300000 } else { 15000 }
    if (-not $p.WaitForExit($timeout)) { $p.Kill(); throw "cli timed out: $($CliArgs -join ' ')" }
    $text = (Get-Content $out, $err -Raw -ErrorAction SilentlyContinue) -join "`n"
    Remove-Item $out, $err -ErrorAction SilentlyContinue
    "> cli $($CliArgs -join ' ') -> $($p.ExitCode)`n$text"
    if ($p.ExitCode -ne 0) { throw "cli failed ($($p.ExitCode)): $($CliArgs -join ' ')" }
}

function Show-Key([string]$modId) {
    $k = Get-ItemProperty "Registry::$root\$modId" -ErrorAction SilentlyContinue
    if (-not $k) { "{0,-34} absent" -f $modId; return }
    $state = if ($k.Disabled -eq 1) { 'off' } else { 'ON' }
    "{0,-34} {1,-3} {2}" -f $modId, $state, $k.LibraryFileName
}

function Show-All {
    Show-Key $id
    foreach ($m in $old) { Show-Key $m }
}

if ($Elevated) {
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    try {
        switch ($Action) {
            'Compile' {
                Invoke-Cli @('mod', 'install', '--file', $src, '--disabled')
                # Engine includes: the metadata covers *, dwm.exe and windhawk.exe.
                # These apps keep their own title bar code out of the mod entirely.
                $k = "Registry::$root\$id"
                Set-ItemProperty $k -Name ExcludeCustom -Value 'FreeDictate.exe|WindowsTerminal.exe|ESDDiscord.exe|windhawk-ui.exe'
            }
            'Swap' {
                $stamp = Get-Date -Format 'yyyyMMdd-HHmm'
                foreach ($m in $old) {
                    $file = "$backup\$($m -replace '@', '_')-$stamp.reg"
                    reg export "$root\$m" $file /y | Out-Null
                    $srcFile = "C:\ProgramData\Windhawk\ModsSource\$m.wh.cpp"
                    if (Test-Path $srcFile) { Copy-Item $srcFile $backup -Force }
                }
                $wasOn = @($old | Where-Object {
                    $k = Get-ItemProperty "Registry::$root\$_" -ErrorAction SilentlyContinue
                    $k -and $k.Disabled -ne 1 })
                if ($wasOn.Count) { Set-Content "$backup\was-on.txt" $wasOn }
                foreach ($m in $wasOn) { Invoke-Cli @('mod', 'disable', $m) }
                Invoke-Cli @('mod', 'enable', $id)
            }
            'Rollback' {
                Invoke-Cli @('mod', 'disable', $id)
                if (Test-Path "$backup\was-on.txt") {
                    foreach ($m in (Get-Content "$backup\was-on.txt")) { Invoke-Cli @('mod', 'enable', $m) }
                }
            }
        }
        Show-All
        'ELEVATED STEP OK'
    } catch {
        "ERROR: $_"
    }
    exit 0
}

switch ($Action) {
    'Audit' { Show-All }
    default {
        New-Item -ItemType Directory -Force -Path $backup | Out-Null
        $text = & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList "-Action $Action -Elevated" 2>&1 | Out-String
        Add-Content $log ("==== {0} {1}`n{2}" -f (Get-Date -Format s), $Action, $text)
        $text
        if ($text -notmatch 'ELEVATED STEP OK') { throw 'Elevated step failed; see the log above' }
    }
}
