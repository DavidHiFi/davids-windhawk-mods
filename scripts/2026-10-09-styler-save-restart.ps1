# Windhawk Styler 2.0.7 "save-restart" deploy: -Audit / -Install / -Rollback.
# The 2.0.7 change: settings saves close+reopen the interface reliably via the
# engine's SettingsChangeTime marker (polled by the mod) plus a user toggle.
# Install expects to run elevated (ModsSource + HKLM + windhawk-cli need it).
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Install,
    [switch]$Rollback
)
$ErrorActionPreference = 'Stop'
$ws = 'H:\Windhawk Configuration'
$src = Join-Path $ws 'work\windhawk-styler\tauri20\windhawk-styler.wh.cpp'
$modsSource = 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp'
$keyPath = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$dllDir = 'C:\ProgramData\Windhawk\Engine\Mods\64'
$bak = Join-Path $ws 'backups\2026-10-09\styler-save-restart'
$report = Join-Path $ws 'reports\2026-10-09-styler-save-restart'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$helperLog = Join-Path $env:TEMP 'wh-styler-helper.log'

function Get-KeyState {
    $p = Get-ItemProperty $keyPath
    [PSCustomObject]@{
        Version = $p.Version
        LibraryFileName = $p.LibraryFileName
        Include = $p.Include
        Architecture = $p.Architecture
        Disabled = $p.Disabled
        SettingsChangeTime = ('0x{0:x8}' -f [int64]$p.SettingsChangeTime)
    }
}

function Get-UiSnapshot {
    $uis = Get-CimInstance Win32_Process -Filter "Name='windhawk-ui.exe'" -ErrorAction SilentlyContinue
    $port = $null
    $listener = netstat -ano | Select-String '127\.0\.0\.1:9333\s' | Select-String 'LISTENING'
    if ($listener) { $port = $listener[0].ToString().Trim() }
    [PSCustomObject]@{
        UiPids = (($uis | ForEach-Object ProcessId) -join ',')
        UiStarted = (($uis | ForEach-Object { $_.CreationDate.ToString('HH:mm:ss') }) -join ',')
        Port9333 = $port
    }
}

if ($Audit) {
    "=== mod key ==="
    Get-KeyState | Format-List | Out-String -Width 200
    "=== source ==="
    "src hash : $((Get-FileHash $src -Algorithm MD5).Hash)"
    "live hash: $((Get-FileHash $modsSource -Algorithm MD5).Hash)"
    "src mtime: $((Get-Item $src).LastWriteTime)  live mtime: $((Get-Item $modsSource).LastWriteTime)"
    "=== UI ==="
    Get-UiSnapshot | Format-List | Out-String -Width 200
    "=== helper log tail ==="
    if (Test-Path $helperLog) { Get-Content $helperLog -Tail 14 }
    "=== debug log tail ==="
    Get-Content "$env:TEMP\wh-styler-debug.log" -Tail 8
    exit 0
}

if ($Install) {
    New-Item -ItemType Directory -Force -Path $bak, $report | Out-Null
    $before = Get-KeyState
    $beforeUi = Get-UiSnapshot
    "before: version=$($before.Version) dll=$($before.LibraryFileName) ui=$($beforeUi.UiPids)"

    # 1. backup: mod key, current source, current DLL (skip on rerun - the
    # source may already be synced to 2.0.7 after an earlier failed attempt)
    $reg = "$bak\mod-key-pre-2.0.7.reg"
    if (-not (Test-Path "$bak\ModsSource.pre-2.0.7.wh.cpp")) {
        reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler' $reg /y | Out-Null
        Copy-Item $modsSource "$bak\ModsSource.pre-2.0.7.wh.cpp" -Force
        Get-ChildItem "$dllDir\local@windhawk-styler_2.0.6_*.dll" -ErrorAction SilentlyContinue |
            Copy-Item -Destination $bak -Force
    }

    # 2. sync source and compile (hot-swaps the running interface). The CLI
    # writes progress on stderr; capture both to files so a 5.1 NativeCommandError
    # cannot kill the script mid-statement.
    Copy-Item $src $modsSource -Force
    "synced source MD5 $((Get-FileHash $modsSource -Algorithm MD5).Hash.Substring(0,8))"
    $cout = "$bak\compile-out.txt"; $cerr = "$bak\compile-err.txt"
    $proc = Start-Process -FilePath $cli -ArgumentList 'mod', 'compile', 'local@windhawk-styler' `
        -NoNewWindow -Wait -PassThru -RedirectStandardOutput $cout -RedirectStandardError $cerr
    $outRaw = (Get-Content $cout -Raw -ErrorAction SilentlyContinue)
    $errRaw = (Get-Content $cerr -Raw -ErrorAction SilentlyContinue)
    $compile = "exit=$($proc.ExitCode) out=[$($outRaw.Trim())] err=[$($errRaw.Trim())]"
    if ($proc.ExitCode -ne 0) { throw "compile failed: $compile" }
    "compile: $compile"

    # 3. read back the key the compile rewrote (Include must stay windhawk-ui.exe)
    Start-Sleep -Seconds 1
    $after = Get-KeyState
    "after compile: version=$($after.Version) dll=$($after.LibraryFileName) include=$($after.Include) arch=$($after.Architecture)"

    # 4. watch the helper restart the interface and the CDP port come up
    $deadline = (Get-Date).AddSeconds(50)
    $newUi = ''
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Seconds 3
        $nowUi = Get-UiSnapshot
        if ($nowUi.UiPids -and $nowUi.UiPids -ne $beforeUi.UiPids) { $newUi = $nowUi.UiPids; break }
    }
    $afterUi = Get-UiSnapshot
    "after: ui=$($afterUi.UiPids) started=$($afterUi.UiStarted) port9333=$($afterUi.Port9333 -ne $null)"
    "helper log tail:"
    if (Test-Path $helperLog) { Get-Content $helperLog -Tail 10 | ForEach-Object { "  $_" } }

    [PSCustomObject]@{
        When = (Get-Date).ToString('s')
        What = 'styler 2.0.7 save-restart (SettingsChangeTime poll + restartOnSave toggle)'
        Before = $before; BeforeUi = $beforeUi
        Compile = $compile.Trim()
        After = $after; AfterUi = $afterUi
        SourceMd5 = (Get-FileHash $src -Algorithm MD5).Hash
        LiveSourceMd5 = (Get-FileHash $modsSource -Algorithm MD5).Hash
        Backup = $bak
    } | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $report 'receipt.json') -Encoding UTF8
    "receipt: $(Join-Path $report 'receipt.json')"
    exit 0
}

if ($Rollback) {
    if (-not (Test-Path "$bak\ModsSource.pre-2.0.7.wh.cpp")) { throw "backup missing: $bak" }
    Copy-Item "$bak\ModsSource.pre-2.0.7.wh.cpp" $modsSource -Force
    Remove-ItemProperty -Path "$keyPath\Settings" -Name 'restartOnSave' -ErrorAction SilentlyContinue
    $cout = "$env:TEMP\wh-cli-rb-out.txt"; $cerr = "$env:TEMP\wh-cli-rb-err.txt"
    $proc = Start-Process -FilePath $cli -ArgumentList 'mod', 'compile', 'local@windhawk-styler' `
        -NoNewWindow -Wait -PassThru -RedirectStandardOutput $cout -RedirectStandardError $cerr
    $errRaw = (Get-Content $cerr -Raw -ErrorAction SilentlyContinue)
    $compile = "exit=$($proc.ExitCode) err=[$($errRaw.Trim())]"
    "rollback compile: $compile"
    Start-Sleep -Seconds 1
    Get-KeyState | Format-List | Out-String -Width 200
    "rollback done - the engine hot-swapped the 2.0.6 source back."
    exit 0
}

Get-Help $MyInvocation.MyCommand.Definition -Parameter * | Out-String
