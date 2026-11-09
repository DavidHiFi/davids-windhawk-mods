# Rename local@translucent-windows-plus to local@seamless-flyouts (2.0.0). Runs ELEVATED.
# Same code and settings; new id and name, plus the one-hover fix.
#   -Action install   back up old key and source, install the new mod disabled, copy every
#                     setting and the app lists across, turn the old one off, the new one on,
#                     then remove the old mod.
#   -Action rollback  remove the new mod, re-import the old key, restore the 1.9.5 source, compile.
# No windhawk.exe -restart.
param([ValidateSet('install', 'rollback')][string]$Action = 'install')
$ErrorActionPreference = 'Stop'
$mods    = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$oldId   = 'local@translucent-windows-plus'
$newId   = 'local@seamless-flyouts'
$old     = "$mods\$oldId"
$new     = "$mods\$newId"
$srcDir  = 'C:\ProgramData\Windhawk\ModsSource'
$work    = 'H:\Windhawk Configuration\work\2026-11-09-flyout-match'
$bk      = 'H:\Windhawk Configuration\backups\2026-11-09\seamless-flyouts'
$cli     = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$log     = Join-Path $bk 'migrate-receipt.txt'
New-Item -ItemType Directory -Force $bk | Out-Null
Start-Transcript -Path (Join-Path $bk "transcript-$(Get-Date -Format HHmmss).txt") | Out-Null
function Say($t) { $l = "$(Get-Date -Format 'h:mm:ss tt') $t"; Add-Content -Path $log -Value $l -Encoding UTF8; Write-Host $l }
function Fail($m) { Say "FAIL: $m"; exit 1 }
function Bump($k) { reg add $k /v SettingsChangeTime /t REG_DWORD /d ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) /f | Out-Null }
function Invoke-WhCli([string[]]$a) {
    $o = Join-Path $bk 'cli.out'; $e = "$o.err"
    $p = Start-Process $cli -ArgumentList $a -WindowStyle Hidden -PassThru -Wait -RedirectStandardOutput $o -RedirectStandardError $e
    Say "cli $($a -join ' ') exit=$($p.ExitCode)"
    if ($p.ExitCode -ne 0) { Get-Content $o, $e | Select-Object -Last 12 | ForEach-Object { Say "  $_" } }
    return $p.ExitCode
}

if ($Action -eq 'rollback') {
    if (Test-Path "Registry::$new") {
        reg add $new /v Disabled /t REG_DWORD /d 1 /f | Out-Null; Bump $new
        Invoke-WhCli @('mod', 'remove', $newId, '--yes') | Out-Null
    }
    reg import "$bk\old-key.reg" 2>&1 | Out-Null
    Copy-Item "$work\translucent-windows-plus-1.9.5.wh.cpp" "$srcDir\$oldId.wh.cpp" -Force
    if ((Invoke-WhCli @('mod', 'compile', $oldId, '--json')) -ne 0) { Fail 'old compile' }
    reg add $old /v Disabled /t REG_DWORD /d 0 /f | Out-Null; Bump $old
    Say "ROLLBACK OK"; exit 0
}

if (-not (Test-Path "$bk\old-key.reg")) { reg export $old "$bk\old-key.reg" /y | Out-Null }
if (-not (Test-Path "$bk\old-key.reg")) { Fail 'registry backup missing' }
Copy-Item "$srcDir\$oldId.wh.cpp" "$bk\$oldId-live.wh.cpp" -Force
Say "backup key and source in $bk"
$before   = Get-ItemProperty "Registry::$old"
$settings = Get-Item "Registry::$old\Settings"

if (-not (Test-Path "Registry::$new")) {
    if ((Invoke-WhCli @('mod', 'install', '--file', "`"$work\seamless-flyouts-2.0.0.wh.cpp`"", '--disabled', '--json')) -ne 0) { Fail 'install' }
}
if (-not (Test-Path "Registry::$new")) { Fail "new key $new missing" }

# Settings: copy every value (types kept) into the new key. (reg copy hangs on a hidden prompt.)
$src = Get-Item "Registry::$old\Settings"
$dst = "Registry::$new\Settings"
if (-not (Test-Path $dst)) { New-Item -Path $dst -Force | Out-Null }
foreach ($n in $src.GetValueNames()) {
    New-ItemProperty -Path $dst -Name $n -Value $src.GetValue($n, $null, 'DoNotExpandEnvironmentNames') -PropertyType $src.GetValueKind($n) -Force | Out-Null
}
$d = Get-Item $dst
$diff = @($src.GetValueNames() | Where-Object { "$($src.GetValue($_))" -ne "$($d.GetValue($_))" })
if ($diff.Count) { Fail "values differ: $($diff -join ', ')" }
foreach ($v in 'Include', 'Exclude', 'IncludeCustom', 'ExcludeCustom', 'IncludeExcludeCustomOnly', 'Architecture') {
    if ($null -ne $before.$v) {
        # Not reg add: PowerShell drops an empty /d argument and reg then waits on a hidden prompt.
        $type = if ($v -eq 'IncludeExcludeCustomOnly') { 'DWord' } else { 'String' }
        New-ItemProperty -Path "Registry::$new" -Name $v -Value $before.$v -PropertyType $type -Force | Out-Null
    }
}
$after = Get-ItemProperty "Registry::$new"
$newCount = (Get-Item "Registry::$new\Settings").ValueCount
if ($newCount -ne $settings.ValueCount) { Fail "settings count $newCount vs $($settings.ValueCount)" }
if ($after.IncludeCustom -ne $before.IncludeCustom -or $after.ExcludeCustom -ne $before.ExcludeCustom -or
    $after.IncludeExcludeCustomOnly -ne $before.IncludeExcludeCustomOnly) { Fail 'app lists differ' }
Say "settings copied: $newCount values, lists match"

# Old off first so the two never run together.
reg add $old /v Disabled /t REG_DWORD /d 1 /f | Out-Null; Bump $old
Start-Sleep -Seconds 3
reg add $new /v Disabled /t REG_DWORD /d 0 /f | Out-Null; Bump $new
Start-Sleep -Seconds 3
if ((Invoke-WhCli @('mod', 'remove', $oldId, '--yes')) -ne 0) { Fail 'remove old' }
$after = Get-ItemProperty "Registry::$new"
Say ("INSTALL OK Lib={0} Version={1} Disabled={2} settings={3}" -f $after.LibraryFileName, $after.Version, $after.Disabled, $newCount)
