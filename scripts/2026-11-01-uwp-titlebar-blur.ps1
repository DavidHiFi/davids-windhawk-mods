# Remove UWP Title Bars Plus 2.2.0: title bar blur option.
# -Audit   show the installed version and settings
# -Install install 2.2.0 and turn the blur on (run elevated)
# -Rollback reinstall 2.1.0 and drop the blur settings (run elevated)
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$root = 'H:\Windhawk Configuration'
$log = "$root\backups\2026-11-01\remove-uwp-title-bars-plus\log.txt"
function L($m) { "$(Get-Date -Format 'yyyy-MM-dd h:mm:ss tt') $m" | Out-File $log -Append -Encoding utf8 }
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@remove-uwp-title-bars-plus'
$new = "$root\work\2026-11-01-uwp-titlebar-blur\remove-uwp-title-bars-plus.wh.cpp"
$old = "$root\backups\2026-11-01\remove-uwp-title-bars-plus\local@remove-uwp-title-bars-plus.v2.1.0.wh.cpp"

function Show {
    $p = Get-ItemProperty $key
    $s = Get-ItemProperty "$key\Settings" -ErrorAction SilentlyContinue
    "version=$($p.Version) lib=$($p.LibraryFileName) disabled=$($p.Disabled) blur=$($s.blur) blurTint=$($s.blurTint)"
}

if ($Audit) { Show; exit 0 }
if (-not ($Install -or $Rollback)) { 'Use -Audit, -Install or -Rollback'; exit 2 }

$src = if ($Install) { $new } else { $old }
# The CLI takes the mod id from the file, so stage it under a plain name.
$t = Join-Path $env:TEMP 'uwp-titlebar-blur'
New-Item -ItemType Directory -Force $t | Out-Null
Copy-Item $src "$t\remove-uwp-title-bars-plus.wh.cpp" -Force
$ErrorActionPreference = 'Continue'  # PS 5.1 turns native stderr into a stop
$out = & $cli mod install --file "$t\remove-uwp-title-bars-plus.wh.cpp" 2>&1 | Out-String
L "install $src exit $LASTEXITCODE`n$out"
if ($LASTEXITCODE -ne 0) { $out; exit 1 }

New-Item -Path "$key\Settings" -Force | Out-Null
if ($Install) {
    Set-ItemProperty "$key\Settings" blur 1 -Type DWord
    Set-ItemProperty "$key\Settings" blurTint '661E1E2E' -Type String
} else {
    Remove-ItemProperty "$key\Settings" blur, blurTint -ErrorAction SilentlyContinue
}
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
$r = Show
L $r
$r
