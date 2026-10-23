# Fullscreen Start Plus install: swaps the catalog fullscreen-start for our fork.
# Copies the built DLL and source into Windhawk, creates local@fullscreen-start-plus
# with the original's settings plus coverScreen=1 and monitor=mouse, disables the
# original, bumps SettingsChangeTime on both, verifies by readback. Run elevated.
# -Rollback re-enables the original and disables the fork.
param([switch]$Rollback)

$ErrorActionPreference = 'Stop'
$id       = 'local@fullscreen-start-plus'
$stock    = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\fullscreen-start'
$key      = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$work     = 'H:\Windhawk Configuration\work\2026-10-24-fullscreen-start-plus'
$src      = "$work\repo\mods\local\fullscreen-start-plus\fullscreen-start-plus.wh.cpp"
$backup   = 'H:\Windhawk Configuration\backups\2026-10-24\fullscreen-start-plus'
$mods64   = 'C:\ProgramData\Windhawk\Engine\Mods\64'
function Now { [DateTimeOffset]::UtcNow.ToUnixTimeSeconds() }
function Bump($k) { Set-ItemProperty $k -Name SettingsChangeTime -Value (Now) -Type DWord }

if ($Rollback) {
    Set-ItemProperty $key -Name Disabled -Value 1 -Type DWord; Bump $key
    Remove-ItemProperty $stock -Name Disabled -ErrorAction SilentlyContinue; Bump $stock
    "rollback: fork Disabled=$((Get-ItemProperty $key).Disabled), original Disabled=$((Get-ItemProperty $stock).Disabled)"
    exit 0
}

$version = ([regex]::Match((Get-Content $src -Raw), '(?m)^//\s*@version\s+(\S+)')).Groups[1].Value
$dll = "$work\build\fullscreen-start-plus_${version}_64.dll"
if (-not (Test-Path $dll)) { throw "no build for $version" }

New-Item $backup -ItemType Directory -Force | Out-Null
$stamp = Get-Date -Format 'HHmmss'
reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\fullscreen-start' "$backup\fullscreen-start-$stamp.reg" /y | Out-Null
if (Test-Path $key) { reg export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\$id-$stamp.reg" /y | Out-Null }

# A fresh revision number each install: the engine keeps loaded DLLs mapped.
$rev = 1
while (Test-Path "$mods64\${id}_${version}_$rev.dll") { $rev++ }
$lib = "${id}_${version}_$rev.dll"
Copy-Item $dll "$mods64\$lib" -Force
Copy-Item $src "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp" -Force

$isNew = -not (Test-Path $key)
if ($isNew) {
    New-Item $key -Force | Out-Null
    reg copy 'HKLM\SOFTWARE\Windhawk\Engine\Mods\fullscreen-start\Settings' "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id\Settings" /s /f | Out-Null
    Set-ItemProperty "$key\Settings" -Name coverScreen -Value 1 -Type DWord
    Set-ItemProperty "$key\Settings" -Name monitor -Value 'mouse' -Type String
}
foreach ($v in @{ Include = 'explorer.exe'; Exclude = ''; Architecture = 'x86-64'; Version = $version; LibraryFileName = $lib }.GetEnumerator()) {
    Set-ItemProperty $key -Name $v.Key -Value $v.Value -Type String
}
Set-ItemProperty $key -Name Disabled -Value 0 -Type DWord
Set-ItemProperty $key -Name LoggingEnabled -Value 1 -Type DWord
Set-ItemProperty $stock -Name Disabled -Value 1 -Type DWord
Bump $stock; Bump $key

$k = Get-ItemProperty $key; $s = Get-ItemProperty "$key\Settings"
if ($k.LibraryFileName -ne $lib -or $k.Disabled -ne 0 -or (Get-ItemProperty $stock).Disabled -ne 1) { throw 'readback mismatch' }
if ((Get-FileHash "$mods64\$lib").Hash -ne (Get-FileHash $dll).Hash) { throw 'DLL hash mismatch' }
"installed $lib; coverScreen=$($s.coverScreen) monitor=$($s.monitor) blurMode=$($s.blurMode); original disabled"
