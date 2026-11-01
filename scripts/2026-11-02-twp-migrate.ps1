# Swap translucent-windows (repo id, local 1.8.3 fork) for local@translucent-windows-plus 1.9.0.
# Runs ELEVATED. Same code, same settings; only the id, name and metadata change.
#   -Action install   back up, disable old, create the Plus key from the old one, then remove the old key and source.
#   -Action rollback  delete the Plus key and source, re-import the old key and source.
# No windhawk.exe -restart; the engine picks up the key changes.
param([ValidateSet('install', 'rollback')][string]$Action = 'install')
$ErrorActionPreference = 'Stop'
$mods   = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$old    = "$mods\translucent-windows"
$new    = "$mods\local@translucent-windows-plus"
$srcDir = 'C:\ProgramData\Windhawk\ModsSource'
$bk     = 'H:\Windhawk Configuration\backups\2026-11-02\translucent-windows-plus'
$dir    = 'H:\Windhawk Configuration\Windhawk\translucent-windows-plus'
$name   = 'local@translucent-windows-plus_1.9.0_1.dll'
function Fail($m) { Write-Output "FAIL: $m"; exit 1 }
function Bump($k) { reg add $k /v SettingsChangeTime /t REG_DWORD /d ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) /f | Out-Null }

if ($Action -eq 'rollback') {
    reg add $new /v Disabled /t REG_DWORD /d 1 /f | Out-Null
    reg delete $new /f | Out-Null
    Remove-Item "$srcDir\local@translucent-windows-plus.wh.cpp" -Force -ErrorAction SilentlyContinue
    reg import "$bk\old-key.reg" 2>&1 | Out-Null
    Copy-Item "$bk\translucent-windows.wh.cpp" "$srcDir\translucent-windows.wh.cpp" -Force
    Bump $old
    Write-Output ("ROLLBACK OK old Lib={0}" -f (Get-ItemProperty "Registry::$old").LibraryFileName); exit 0
}

New-Item -ItemType Directory -Force $bk | Out-Null
if (-not (Test-Path "$bk\old-key.reg")) { reg export $old "$bk\old-key.reg" /y | Out-Null }
if (-not (Test-Path "$bk\old-key.reg")) { Fail 'registry backup missing' }
Copy-Item "$srcDir\translucent-windows.wh.cpp" "$bk\translucent-windows.wh.cpp" -Force
$before = Get-ItemProperty "Registry::$old"
$oldCount = (Get-Item "Registry::$old\Settings").ValueCount

foreach ($bits in '64', '32') {
    $d = "C:\ProgramData\Windhawk\Engine\Mods\$bits\$name"
    Copy-Item "$dir\translucent-windows-plus-$bits.dll" $d -Force
    if ((Get-FileHash $d).Hash -ne (Get-FileHash "$dir\translucent-windows-plus-$bits.dll").Hash) { Fail "$bits copy hash" }
}
Copy-Item "$dir\translucent-windows-plus.wh.cpp" "$srcDir\local@translucent-windows-plus.wh.cpp" -Force

# Old off first so the two never run together.
reg add $old /v Disabled /t REG_DWORD /d 1 /f | Out-Null; Bump $old
Start-Sleep -Seconds 2
reg copy $old $new /s /f | Out-Null
reg add $new /v LibraryFileName /t REG_SZ /d $name /f | Out-Null
reg add $new /v Version /t REG_SZ /d '1.9.0' /f | Out-Null
reg delete $new /v DisableUpdateCheck /f 2>&1 | Out-Null
reg add $new /v Disabled /t REG_DWORD /d ([int]$before.Disabled) /f | Out-Null
Bump $new

$after = Get-ItemProperty "Registry::$new"
if ((Get-Item "Registry::$new\Settings").ValueCount -ne $oldCount) { Fail 'settings count' }
if ($after.IncludeCustom -ne $before.IncludeCustom -or $after.ExcludeCustom -ne $before.ExcludeCustom -or $after.IncludeExcludeCustomOnly -ne $before.IncludeExcludeCustomOnly) { Fail 'include/exclude changed' }

Start-Sleep -Seconds 3
reg delete $old /f | Out-Null
Remove-Item "$srcDir\translucent-windows.wh.cpp" -Force
Write-Output ("INSTALL OK Lib={0} Version={1} Disabled={2} settings={3}" -f $after.LibraryFileName, $after.Version, $after.Disabled, $oldCount)
