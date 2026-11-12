# Rename local@seamless-listary (Seamless Listary 1.1.3) to local@seamless-find (Seamless Find 1.2.0).
# Owner order 2026-11-12: the mod must not be called Listary. Runs ELEVATED. Same code, new id and name.
#   -Action install   back up the old key, its LocalStorage and source; install the new mod disabled; copy
#                     the 27 settings and the LocalStorage values (launch history, pause); old off, new on,
#                     remove the old mod.
#   -Action rollback  remove the new mod, re-import the old keys, restore the 1.1.3 source, compile, enable.
# No windhawk.exe -restart. Model: scripts\2026-11-12-seamless-explorer-view-rebrand.ps1.
param([ValidateSet('install', 'rollback')][string]$Action = 'install', [string]$BaseHash = '')
$ErrorActionPreference = 'Stop'
$mods    = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$wr      = 'HKLM\SOFTWARE\Windhawk\Engine\ModsWritable'
$oldId   = 'local@seamless-listary'
$newId   = 'local@seamless-find'
$old     = "$mods\$oldId"; $new = "$mods\$newId"
$oldW    = "$wr\$oldId";   $newW = "$wr\$newId"
$srcDir  = 'C:\ProgramData\Windhawk\ModsSource'
$staged  = 'C:\Users\Public\seamless-find-1.2.0.wh.cpp'   # space-free path for the elevation chain
$bk      = 'H:\Windhawk Configuration\backups\2026-11-12\seamless-find-rename'
$cli     = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$log     = Join-Path $bk 'migrate-receipt.txt'
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
function Copy-Values($from, $to) {
    if (-not (Test-Path "Registry::$from")) { return 0 }
    $src = Get-Item "Registry::$from"
    if (-not (Test-Path "Registry::$to")) { New-Item -Path "Registry::$to" -Force | Out-Null }
    foreach ($n in $src.GetValueNames()) {
        New-ItemProperty -Path "Registry::$to" -Name $n -Value $src.GetValue($n, $null, 'DoNotExpandEnvironmentNames') `
            -PropertyType $src.GetValueKind($n) -Force | Out-Null
    }
    $d = Get-Item "Registry::$to"
    $diff = @($src.GetValueNames() | Where-Object { "$($src.GetValue($_))" -ne "$($d.GetValue($_))" })
    if ($diff.Count) { Fail "values differ under $to : $($diff -join ', ')" }
    return $src.ValueCount
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

if ($BaseHash) {
    $now = (Get-FileHash "$srcDir\$oldId.wh.cpp" -Algorithm SHA256).Hash
    if ($now -ne $BaseHash) { Fail "live $oldId changed since the rename build; rebuild first" }
}
if (-not (Test-Path "$bk\old-key.reg")) { reg export $old "$bk\old-key.reg" /y | Out-Null }
if (-not (Test-Path "$bk\old-key.reg")) { Fail 'registry backup missing' }
if (Test-Path "Registry::$oldW") { if (-not (Test-Path "$bk\old-writable.reg")) { reg export $oldW "$bk\old-writable.reg" /y | Out-Null } }
if (-not (Test-Path "$bk\$oldId-live.wh.cpp")) { Copy-Item "$srcDir\$oldId.wh.cpp" "$bk\$oldId-live.wh.cpp" -Force }
Say "backups in $bk"
$before = Get-ItemProperty "Registry::$old"

if (-not (Test-Path "Registry::$new")) {
    if ((Invoke-WhCli @('mod', 'install', '--file', "`"$staged`"", '--disabled', '--json')) -ne 0) { Fail 'install' }
}
if (-not (Test-Path "Registry::$new")) { Fail "new key $new missing" }

$nSet = Copy-Values "$old\Settings" "$new\Settings"
$nLoc = Copy-Values "$oldW\LocalStorage" "$newW\LocalStorage"
foreach ($v in 'Include', 'Exclude', 'IncludeCustom', 'ExcludeCustom', 'IncludeExcludeCustomOnly', 'Architecture') {
    if ($null -ne $before.$v) {
        $type = if ($v -eq 'IncludeExcludeCustomOnly') { 'DWord' } else { 'String' }
        New-ItemProperty -Path "Registry::$new" -Name $v -Value $before.$v -PropertyType $type -Force | Out-Null
    }
}
Say "copied $nSet settings, $nLoc stored values"

# Old off first so the two never run together (both would grab Ctrl Ctrl).
reg add $old /v Disabled /t REG_DWORD /d 1 /f | Out-Null; Bump $old
Start-Sleep -Seconds 4
reg add $new /v Disabled /t REG_DWORD /d 0 /f | Out-Null; Bump $new
Start-Sleep -Seconds 4
if ((Invoke-WhCli @('mod', 'remove', $oldId, '--yes')) -ne 0) { Fail 'remove old' }
if (Test-Path "Registry::$old") { Fail 'old key still present' }
$after = Get-ItemProperty "Registry::$new"
if ($after.Disabled -ne 0) { Fail 'new mod not enabled' }
if ($after.Version -ne '1.2.0') { Fail "unexpected version $($after.Version)" }
[pscustomobject]@{
    date = (Get-Date -Format 'yyyy-MM-dd HH:mm'); oldId = $oldId; newId = $newId
    oldVersion = $before.Version; newVersion = $after.Version; library = $after.LibraryFileName
    settingsValues = $nSet; storedValues = $nLoc
} | ConvertTo-Json | Set-Content -Path (Join-Path $bk 'receipt.json') -Encoding UTF8
Say "INSTALL OK Lib=$($after.LibraryFileName) settings=$nSet stored=$nLoc"
