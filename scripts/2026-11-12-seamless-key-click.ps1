# Seamless Key Click: install the fork, remove the original Key Click, or roll back.
# Run ELEVATED (Invoke-Elevated.ps1). -Audit only reads.
#   -Audit      show both mods' state and the running helper
#   -Install    back up the original, install the fork, restart its helper, remove the original
#   -Rollback   remove the fork and reinstall the original from the backup
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$src = 'H:\Windhawk Configuration\work\2026-11-11-seamless-key-click\local@seamless-key-click.wh.cpp'
$backup = 'H:\Windhawk Configuration\backups\2026-11-12\key-click'
$orig = 'C:\ProgramData\Windhawk\ModsSource\key-click.wh.cpp'
$base = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$receipt = 'H:\Windhawk Configuration\reports\2026-11-12-seamless-key-click-receipt.json'

# Every windhawk-cli call is hidden and stopped after its time limit.
function Invoke-Cli([string]$ArgLine, [int]$Seconds = 15) {
    $out = [IO.Path]::GetTempFileName(); $err = [IO.Path]::GetTempFileName()
    $p = Start-Process $cli -ArgumentList $ArgLine -WindowStyle Hidden -PassThru -RedirectStandardOutput $out -RedirectStandardError $err
    $null = $p.Handle  # Without this, ExitCode stays empty after the process ends.
    if (-not $p.WaitForExit($Seconds * 1000)) { $p.Kill(); Write-Host "TIMEOUT after $Seconds s: $ArgLine"; return 124 }
    # Output goes to the host so the function returns only the exit code.
    Get-Content $out, $err -ErrorAction SilentlyContinue | Where-Object { $_ } | ForEach-Object { Write-Host "  $_" }
    Remove-Item $out, $err -ErrorAction SilentlyContinue
    return $p.ExitCode
}
# Same filter as the restart script. Retries for 20 s, because the helper can take a moment to show.
function Helper {
    for ($i = 0; $i -lt 10; $i++) {
        $h = @(Get-CimInstance Win32_Process -Filter "Name='windhawk-mod.exe' OR Name='windhawk.exe'" |
               Where-Object { $_.CommandLine -like '*-tool-mod "local@seamless-key-click"*' })
        if ($h.Count) { return ,$h }
        Start-Sleep -Seconds 2
    }
    return ,@()
}
function State([string]$Id) {
    $k = "$base\$Id"
    if (-not (Test-Path $k)) { return "$Id : not installed" }
    $v = Get-ItemProperty $k
    "$Id : version=$($v.Version) disabled=$([int]$v.Disabled) library=$($v.LibraryFileName)"
}

if ($Audit -or -not ($Install -or $Rollback)) {
    State 'key-click'; State 'local@seamless-key-click'
    "helper running: $((Helper).Count) pid: $((Helper).ProcessId -join ',')"
    exit 0
}

if ($Install) {
    New-Item -ItemType Directory -Force $backup | Out-Null
    if ((Test-Path $orig) -and -not (Test-Path "$backup\key-click.wh.cpp")) { Copy-Item $orig "$backup\key-click.wh.cpp" }
    if ((Test-Path "$base\key-click") -and -not (Test-Path "$backup\key-click.reg")) {
        & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\key-click' "$backup\key-click.reg" /y | Out-Null
    }
    "backup: $((Get-ChildItem $backup).Name -join ', ')"

    $installed = 'C:\ProgramData\Windhawk\ModsSource\local@seamless-key-click.wh.cpp'
    # Windhawk stores the source with CRLF line ends; compare the text without them.
    $same = (Test-Path $installed) -and ([IO.File]::ReadAllText($installed).Replace("`r`n", "`n") -eq [IO.File]::ReadAllText($src).Replace("`r`n", "`n"))
    if ($same) {
        "install: this source is already installed, skipping the compile"
    } else {
        "install (compiles, up to 4 min):"
        $rc = Invoke-Cli "mod install --file `"$src`" --strict --yes --json" 240
        "install exit=$rc"
        if ($rc -ne 0) { exit 1 }
    }
    State 'local@seamless-key-click'

    & 'H:\Windhawk Configuration\scripts\2026-11-10-tool-mod-restart.ps1' -Id 'local@seamless-key-click'
    $h = @(Helper)
    if (-not $h.Count) { 'FATAL: helper not running, original left in place'; exit 2 }

    if (Test-Path "$base\key-click") {
        "remove original:"
        $rc = Invoke-Cli 'mod remove key-click --yes --json'
        "remove exit=$rc"
    }
    State 'key-click'
    [ordered]@{
        when = (Get-Date).ToString('s'); fork = 'local@seamless-key-click'; source = $src
        sourceSha256 = (Get-FileHash $src -Algorithm SHA256).Hash
        library = (Get-ItemProperty "$base\local@seamless-key-click").LibraryFileName
        helperPid = ($h.ProcessId -join ','); originalRemoved = -not (Test-Path "$base\key-click"); backup = $backup
    } | ConvertTo-Json | Set-Content $receipt -Encoding UTF8
    "receipt: $receipt"
    exit 0
}

if ($Rollback) {
    if (Test-Path "$base\local@seamless-key-click") { "remove fork: exit=$(Invoke-Cli 'mod remove local@seamless-key-click --yes --json')" }
    if (Test-Path "$backup\key-click.wh.cpp") {
        # The original reinstalls disabled, as it was before the fork.
        "reinstall original: exit=$(Invoke-Cli "mod install key-click --disabled --yes --json" 240)"
    }
    State 'key-click'; State 'local@seamless-key-click'
}
