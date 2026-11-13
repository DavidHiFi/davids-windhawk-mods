# Replace local@seamless-find (Seamless Find 1.2.0) with local@seamless-explorer-search (Seamless Explorer Search 2.0.0).
# Owner order 2026-11-12: Explorer type-to-search on Everything, no launcher. Runs ELEVATED. No windhawk.exe -restart.
#   -Action install   back up the old key, its LocalStorage and source; old off; install the new mod through
#                     Install-StagedMod.ps1 (template check, refuses if it already exists); copy the settings both
#                     mods share and the settings-window LocalStorage; restart the new tool process; remove the old.
#   -Action rollback  remove the new mod, re-import the old keys, restore the 1.2.0 source, compile, enable.
# Model: scripts\2026-11-12-seamless-find-rename.ps1.
param([ValidateSet('install', 'rollback')][string]$Action = 'install')
$ErrorActionPreference = 'Stop'
$mods   = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$wr     = 'HKLM\SOFTWARE\Windhawk\Engine\ModsWritable'
$oldId  = 'local@seamless-find'
$newId  = 'local@seamless-explorer-search'
$old    = "$mods\$oldId"; $new = "$mods\$newId"
$oldW   = "$wr\$oldId";   $newW = "$wr\$newId"
$srcDir = 'C:\ProgramData\Windhawk\ModsSource'
$staged = 'C:\Users\Public\seamless-explorer-search-2.0.0.wh.cpp'   # space-free path for the elevation chain
$bk     = 'H:\Windhawk Configuration\backups\2026-11-12\seamless-explorer-search'
$cli    = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$log    = Join-Path $bk 'migrate-receipt.txt'
# Settings that mean the same thing in both mods. Launcher-only ones (hotkeys, web keywords, commands,
# quick menu, dialogs) and the template's dropped settingsTitleButtons stay behind.
$shared = 'hideOnFocusLost', 'searchAsYouType', 'resultLimit', 'queryTimeoutMs', 'matchPath', 'fuzzyRanking',
          'accentColor', 'popupOpacity', 'animations', 'settingsGlass', 'nativeSettingsTitleBar', 'settingsTrayIcon'
$stored = 'Settings_X', 'Settings_Y', 'Settings_CX', 'Settings_CY', 'Settings_RailW', 'Settings_RailCollapsed', 'paused'
New-Item -ItemType Directory -Force $bk | Out-Null
function Say($t) { $l = "$(Get-Date -Format 'h:mm:ss tt') $t"; Add-Content -Path $log -Value $l -Encoding UTF8; Write-Host $l }
function Fail($m) { Say "FAIL: $m"; exit 1 }
function Bump($k) { reg add $k /v SettingsChangeTime /t REG_DWORD /d ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) /f | Out-Null }
function Invoke-WhCli([string[]]$a, [int]$limit = 300000) {
    $o = Join-Path $bk 'cli.out'; $e = "$o.err"
    $si = [Diagnostics.ProcessStartInfo]::new(); $si.FileName = $cli; $si.Arguments = ($a -join ' ')
    $si.UseShellExecute = $false; $si.CreateNoWindow = $true
    $si.RedirectStandardOutput = $true; $si.RedirectStandardError = $true
    $p = [Diagnostics.Process]::Start($si)
    try { $p.PriorityClass = 'BelowNormal' } catch {}
    $ot = $p.StandardOutput.ReadToEndAsync(); $et = $p.StandardError.ReadToEndAsync()
    if (-not $p.WaitForExit($limit)) { try { $p.Kill() } catch {}; Say "cli KILLED after $limit ms: $($a -join ' ')"; return 124 }
    [IO.File]::WriteAllText($o, $ot.Result); [IO.File]::WriteAllText($e, $et.Result)
    Say "cli $($a -join ' ') exit=$($p.ExitCode)"
    if ($p.ExitCode -ne 0) { Get-Content $o, $e | Select-Object -Last 12 | ForEach-Object { Say "  $_" } }
    return $p.ExitCode
}
function Copy-Named($from, $to, [string[]]$names) {
    if (-not (Test-Path "Registry::$from")) { return 0 }
    $src = Get-Item "Registry::$from"
    if (-not (Test-Path "Registry::$to")) { New-Item -Path "Registry::$to" -Force | Out-Null }
    $n = 0
    foreach ($v in $names) {
        if ($src.GetValueNames() -notcontains $v) { continue }
        New-ItemProperty -Path "Registry::$to" -Name $v -Value $src.GetValue($v, $null, 'DoNotExpandEnvironmentNames') `
            -PropertyType $src.GetValueKind($v) -Force | Out-Null
        if ("$((Get-Item "Registry::$to").GetValue($v))" -ne "$($src.GetValue($v))") { Fail "value $v differs under $to" }
        $n++
    }
    return $n
}

if ($Action -eq 'rollback') {
    if (Test-Path "Registry::$new") {
        reg add $new /v Disabled /t REG_DWORD /d 1 /f | Out-Null; Bump $new
        Start-Sleep -Seconds 3
        Invoke-WhCli @('mod', 'remove', $newId, '--yes') | Out-Null
    }
    reg import "$bk\old-key.reg" 2>&1 | Out-Null
    if (Test-Path "$bk\old-writable.reg") { reg import "$bk\old-writable.reg" 2>&1 | Out-Null }
    Copy-Item "$bk\$oldId-live.wh.cpp" "$srcDir\$oldId.wh.cpp" -Force
    if ((Invoke-WhCli @('mod', 'compile', $oldId)) -ne 0) { Fail 'old compile' }
    reg add $old /v Disabled /t REG_DWORD /d 0 /f | Out-Null; Bump $old
    Say 'ROLLBACK OK'; exit 0
}

if (-not (Test-Path "Registry::$old")) { Fail "$old missing (already migrated?)" }
if (-not (Test-Path "$bk\old-key.reg")) { reg export $old "$bk\old-key.reg" /y | Out-Null }
if (-not (Test-Path "$bk\old-key.reg")) { Fail 'registry backup missing' }
if (Test-Path "Registry::$oldW") { if (-not (Test-Path "$bk\old-writable.reg")) { reg export $oldW "$bk\old-writable.reg" /y | Out-Null } }
if (-not (Test-Path "$bk\$oldId-live.wh.cpp")) { Copy-Item "$srcDir\$oldId.wh.cpp" "$bk\$oldId-live.wh.cpp" -Force }
Say "backups in $bk"
$before = Get-ItemProperty "Registry::$old"

# Old off first so the two never run together.
reg add $old /v Disabled /t REG_DWORD /d 1 /f | Out-Null; Bump $old
Start-Sleep -Seconds 4

$inst = Join-Path $PSScriptRoot 'Install-StagedMod.ps1'
$out = & powershell.exe -NoProfile -ExecutionPolicy Bypass -File $inst -Id $newId -Staged $staged -BaseHash new 2>&1
$code = $LASTEXITCODE
$out | ForEach-Object { Say "  install: $_" }
if ($code -ne 0) {
    reg add $old /v Disabled /t REG_DWORD /d 0 /f | Out-Null; Bump $old
    Fail "Install-StagedMod exit $code (old mod turned back on)"
}
if (-not (Test-Path "Registry::$new")) { Fail "new key $new missing" }

$nSet = Copy-Named "$old\Settings" "$new\Settings" $shared
$nLoc = Copy-Named "$oldW\LocalStorage" "$newW\LocalStorage" $stored
Say "copied $nSet settings, $nLoc stored values"

# Off and on again restarts the tool process, so it starts with the copied settings and stored values.
reg add $new /v Disabled /t REG_DWORD /d 1 /f | Out-Null; Bump $new
Start-Sleep -Seconds 4
reg add $new /v Disabled /t REG_DWORD /d 0 /f | Out-Null; Bump $new
Start-Sleep -Seconds 4

if ((Invoke-WhCli @('mod', 'remove', $oldId, '--yes')) -ne 0) { Fail 'remove old' }
if (Test-Path "Registry::$old") { Fail 'old key still present' }
$after = Get-ItemProperty "Registry::$new"
if ($after.Disabled -ne 0) { Fail 'new mod not enabled' }
if ($after.Version -ne '2.0.0') { Fail "unexpected version $($after.Version)" }
[pscustomobject]@{
    date = (Get-Date -Format 'yyyy-MM-dd HH:mm'); oldId = $oldId; newId = $newId
    oldVersion = $before.Version; newVersion = $after.Version; library = $after.LibraryFileName
    settingsValues = $nSet; storedValues = $nLoc
} | ConvertTo-Json | Set-Content -Path (Join-Path $bk 'receipt.json') -Encoding UTF8
Say "INSTALL OK Lib=$($after.LibraryFileName) settings=$nSet stored=$nLoc"
