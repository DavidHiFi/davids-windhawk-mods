<#
.SYNOPSIS
    Translucent Flyouts 0.6.41-diag: the menu accent outline stroke follows the rounded window region
    (2026-10-18). Earlier builds framed a square rect; the 24 px region clipped it into
    straight stubs that stopped where the corners start, and a stale square frame stayed.

.DESCRIPTION
    -Audit     print the current registry values, the engine DLLs and the source version
    -Build     assemble src/ and compile x64 + x86 (release: no TF_DEBUG_LOG)
    -Install   back up the mod key and the installed source, copy the DLLs into Engine\Mods\{64,32},
               copy the source into ModsSource, point LibraryFileName/Version at 0.6.41-diag
               and bump SettingsChangeTime. Explorer loads the new DLL only after its next
               restart; other processes pick it up as they start.
    -Rollback  point LibraryFileName/Version back at the 0.6.40-diag DLL and bump the marker

    Needs elevation (ProgramData and HKLM writes). Run through
    H:\System Configuration\scripts\Invoke-Elevated.ps1.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Build,
    [switch]$Install,
    [switch]$Rollback
)

$ErrorActionPreference = 'Stop'
$id       = 'local@translucent-flyouts'
$key      = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$modRoot  = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts'
$assembled = "$modRoot\translucent-flyouts.wh.cpp"
$buildPs1 = 'H:\Windhawk Configuration\scripts\2026-09-28-translucent-flyouts-build.ps1'
$engineLib = 'C:\Program Files\Windhawk\Engine\2.0.0_1'
$modsDir  = 'C:\ProgramData\Windhawk\Engine\Mods'
$modsSrc  = 'C:\ProgramData\Windhawk\ModsSource'
$version  = '0.6.41-diag'
$libName  = "$id`_${version}_1.dll"
$prevLib  = "$id`_0.6.40-diag_1.dll"
$backup   = 'H:\Windhawk Configuration\backups\2026-10-18\translucent-flyouts-0.6.41-diag'
$logPath  = 'H:\Windhawk Configuration\reports\2026-10-18-flyout-border\build-0.6.41-diag.log'

function Show-State {
    $p = Get-ItemProperty $key
    "LibraryFileName=$($p.LibraryFileName) Version=$($p.Version) Disabled=$($p.Disabled) Include=$($p.Include) SettingsChangeTime=$($p.SettingsChangeTime)"
}
function Bump-Marker {
    $now  = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $prev = (Get-ItemProperty $key).SettingsChangeTime
    $value = if ($prev -ge $now) { $prev + 1 } else { $now }
    Set-ItemProperty $key SettingsChangeTime -Value $value -Type DWord
    "bumped SettingsChangeTime=$value"
}

if ($Audit -or $Install) {
    '--- current ---'
    Show-State
    foreach ($arch in '64', '32') {
        "engine $arch already has $libName : $(Test-Path (Join-Path $modsDir "$arch\$libName"))"
    }
    $srcVersion = (Select-String -LiteralPath $assembled -Pattern '^\s*//\s*@version\s+(\S+)' |
                   Select-Object -First 1).Matches[0].Groups[1].Value
    "assembled source version: $srcVersion"
    if ($Audit -and -not $Install) { exit 0 }
}

if ($Build) {
    & $buildPs1 -Source $assembled -OutDir $modRoot `
        -ModIdHeader "$modRoot\translucent-flyouts-modid.h" `
        -LogPath $logPath -EngineLibRoot $engineLib -Arch both
    if ($LASTEXITCODE -ne 0) { throw "build failed (exit $LASTEXITCODE); see $logPath" }
    foreach ($arch in '64', '32') {
        $dll = Join-Path $modRoot "$id`_${version}_1_$arch.dll"
        if (-not (Test-Path $dll)) { throw "missing build output: $dll" }
        "built $(Split-Path $dll -Leaf) sha256=$((Get-FileHash $dll -Algorithm SHA256).Hash)"
    }
    if (-not $Install) { exit 0 }
}

if ($Install) {
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" `
        "$backup\mod-key-before-0.6.41-diag-install.reg" /y | Out-Null
    if (Test-Path "$modsSrc\$id.wh.cpp") {
        Copy-Item "$modsSrc\$id.wh.cpp" "$backup\local@translucent-flyouts.wh.cpp.installed-0.6.40-diag" -Force
    }
    foreach ($arch in '64', '32') {
        $src = Join-Path $modRoot "$id`_${version}_1_$arch.dll"
        $dst = Join-Path $modsDir "$arch\$libName"
        Copy-Item -LiteralPath $src -Destination $dst -Force
        $same = (Get-FileHash -LiteralPath $src).Hash -eq (Get-FileHash -LiteralPath $dst).Hash
        "copied $arch to $dst hashMatches=$same"
        if (-not $same) { throw "hash mismatch after copy: $dst" }
    }
    Copy-Item $assembled "$modsSrc\$id.wh.cpp" -Force
    $srcInEngine = Select-String -LiteralPath "$modsSrc\$id.wh.cpp" -Pattern "@version\s+$version" -Quiet
    "ModsSource carries $version : $srcInEngine"
    Set-ItemProperty $key LibraryFileName $libName
    Set-ItemProperty $key Version $version
    Bump-Marker
    '--- after ---'
    Show-State
    exit 0
}

if ($Rollback) {
    Set-ItemProperty $key LibraryFileName $prevLib
    Set-ItemProperty $key Version '0.6.40-diag'
    Bump-Marker
    '--- after rollback ---'
    Show-State
    exit 0
}

Write-Error 'Pass -Audit, -Build, -Install or -Rollback.'
exit 2
