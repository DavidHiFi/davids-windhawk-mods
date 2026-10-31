# 2026-10-27 Taskbar Elastic WinUI Pill Plus: install our fork with the owner's settings, pill on unfocused open apps,
# and take the catalog original out. Run elevated (Invoke-Elevated.ps1 -File).
#   -Mode Install  copy source + DLL, create the mod key (settings copied from the original, ShowOn=unfocused), disable the original
#   -Mode Remove   delete the original's key, source and DLL (backups stay in backups\2026-10-27-elastic-pill-plus)
#   -Mode Rollback re-import the original's key, restore its source and DLL, disable the fork
param([ValidateSet('Install', 'Remove', 'Rollback')][string]$Mode = 'Install', [string]$Lib = 'local@taskbar-elastic-pill-plus_2.1.0_1.dll')
$ErrorActionPreference = 'Stop'

$ws      = 'H:\Windhawk Configuration'
$work    = "$ws\work\2026-10-27-elastic-pill-plus"
$backup  = "$ws\backups\2026-10-27-elastic-pill-plus"
$id      = 'local@taskbar-elastic-pill-plus'
$lib     = $Lib
$origLib = 'taskbar-elastic-pill_2.0.1_586863.dll'
$key     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$orig    = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\taskbar-elastic-pill'
$src     = 'C:\ProgramData\Windhawk\ModsSource'
$mods64  = 'C:\ProgramData\Windhawk\Engine\Mods\64'
function Now { [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds() }
function Bump($k) { Set-ItemProperty $k -Name SettingsChangeTime -Value (Now) -Type DWord }
$out = @("$((Get-Date).ToString('yyyy-MM-dd h:mm:ss tt')) mode=$Mode")

if ($Mode -eq 'Install') {
    New-Item $backup -ItemType Directory -Force | Out-Null
    if (-not (Test-Path "$backup\taskbar-elastic-pill.reg")) {
        reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\taskbar-elastic-pill' "$backup\taskbar-elastic-pill.reg" /y | Out-Null
        Copy-Item "$mods64\$origLib" "$backup\$origLib"
    }
    Copy-Item "$work\$id.wh.cpp" "$src\$id.wh.cpp" -Force
    Copy-Item "$work\build\x64\$lib" "$mods64\$lib" -Force
    if ((Get-FileHash "$mods64\$lib").Hash -ne (Get-FileHash "$work\build\x64\$lib").Hash) { throw 'DLL copy mismatch' }

    if (-not (Test-Path $key)) {
        New-Item $key -Force | Out-Null
        reg copy 'HKLM\SOFTWARE\Windhawk\Engine\Mods\taskbar-elastic-pill\Settings' "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id\Settings" /s /f | Out-Null
    }
    Set-ItemProperty "$key\Settings" -Name 'Pill.ShowOn' -Value 'unfocused' -Type String
    Set-ItemProperty $key -Name LibraryFileName -Value $lib -Type String
    Set-ItemProperty $key -Name Version -Value ($lib -replace '^.*_(\d+\.\d+\.\d+)_\d+\.dll$','$1') -Type String
    Set-ItemProperty $key -Name Include -Value 'explorer.exe' -Type String
    Set-ItemProperty $key -Name Exclude -Value '' -Type String
    Set-ItemProperty $key -Name Architecture -Value 'x86-64' -Type String
    Set-ItemProperty $key -Name LoggingEnabled -Value 1 -Type DWord
    Set-ItemProperty $key -Name Disabled -Value 0 -Type DWord
    Bump $key
    Set-ItemProperty $orig -Name Disabled -Value 1 -Type DWord; Bump $orig

    $k = Get-ItemProperty $key; $s = Get-ItemProperty "$key\Settings"
    if ($k.LibraryFileName -ne $lib -or $k.Disabled -ne 0 -or $s.'Pill.ShowOn' -ne 'unfocused' -or (Get-ItemProperty $orig).Disabled -ne 1) { throw 'readback mismatch' }
    $out += "installed $lib; ShowOn=$($s.'Pill.ShowOn') Dimensions=$($s.'Pill.Dimensions') HideInactiveDots=$($s.'Pill.HideInactiveDots'); original Disabled=1"
} elseif ($Mode -eq 'Remove') {
    if (-not (Test-Path "$backup\taskbar-elastic-pill.reg")) { throw 'no backup, refusing to remove' }
    Copy-Item "$src\taskbar-elastic-pill.wh.cpp" "$backup\taskbar-elastic-pill.wh.cpp.installed" -Force
    Remove-Item $orig -Recurse -Force
    Remove-Item "$src\taskbar-elastic-pill.wh.cpp" -Force
    Remove-Item "$mods64\$origLib" -Force -ErrorAction SilentlyContinue
    $out += "original removed: key=$(Test-Path $orig) source=$(Test-Path "$src\taskbar-elastic-pill.wh.cpp") dll=$(Test-Path "$mods64\$origLib")"
} else {
    reg import "$backup\taskbar-elastic-pill.reg" 2>$null
    Copy-Item "$backup\taskbar-elastic-pill.wh.cpp.original" "$src\taskbar-elastic-pill.wh.cpp" -Force
    if (-not (Test-Path "$mods64\$origLib")) { Copy-Item "$backup\$origLib" "$mods64\$origLib" }
    Set-ItemProperty $orig -Name Disabled -Value 0 -Type DWord; Bump $orig
    Set-ItemProperty $key -Name Disabled -Value 1 -Type DWord; Bump $key
    $out += "rolled back: original Disabled=$((Get-ItemProperty $orig).Disabled) fork Disabled=$((Get-ItemProperty $key).Disabled)"
}
$out | Set-Content "$work\$Mode-result.txt" -Encoding UTF8
$out
