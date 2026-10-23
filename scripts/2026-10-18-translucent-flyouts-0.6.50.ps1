<#
.SYNOPSIS
    Translucent Flyouts 0.6.50 (2026-10-18): restores item text on uxtheme menus (0.6.49 regression:
    the exact ring fill left every item text invisible) and adds the accent ring to menus drawn
    outside the uxtheme hooks (desktop context menu), painted from inside the host process.

.DESCRIPTION
    -Version <v>      selects the DLL version to install (default 0.6.50; pass 0.6.50-diag).
    -Audit            print the registry state and the engine DLLs
    -Build            assemble src/ and compile the release x64 + x86 DLLs (no TF_DEBUG_LOG)
    -Install          back up the mod key and the installed source, copy the DLLs into
                      Engine\Mods\{64,32}, copy the source into ModsSource, point
                      LibraryFileName/Version at <version> and bump SettingsChangeTime.
    -Rollback         point LibraryFileName/Version back at 0.6.49 and bump the marker

    Needs elevation (ProgramData and HKLM writes). Run through
    H:\System Configuration\scripts\Invoke-Elevated.ps1.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Build,
    [switch]$Install,
    [switch]$Rollback,
    [string]$Version = '0.6.50'
)

$ErrorActionPreference = 'Stop'
$id        = 'local@translucent-flyouts'
$key       = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$modRoot   = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts'
$assembled = "$modRoot\translucent-flyouts.wh.cpp"
$buildPs1  = 'H:\Windhawk Configuration\scripts\2026-09-28-translucent-flyouts-build.ps1'
$engineLib = 'C:\Program Files\Windhawk\Engine\2.0.0_1'
$modsDir   = 'C:\ProgramData\Windhawk\Engine\Mods'
$modsSrc   = 'C:\ProgramData\Windhawk\ModsSource'
$libName   = "$id`_${Version}_1.dll"
$prevVer   = '0.6.49'
$prevLib   = "$id`_${prevVer}_1.dll"
$backup    = 'H:\Windhawk Configuration\backups\2026-10-18\translucent-flyouts-0.6.50'
$logPath   = 'H:\Windhawk Configuration\reports\2026-10-18-flyout-border\build-0.6.50.log'

function Show-State {
    $p = Get-ItemProperty $key
    "LibraryFileName=$($p.LibraryFileName) Version=$($p.Version) Disabled=$($p.Disabled) SettingsChangeTime=$($p.SettingsChangeTime)"
}
function Bump-Marker {
    $now  = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $prev = (Get-ItemProperty $key).SettingsChangeTime
    $value = if ($prev -ge $now) { $prev + 1 } else { $now }
    Set-ItemProperty $key SettingsChangeTime -Value $value -Type DWord
    "bumped SettingsChangeTime=$value"
}

if ($Audit) {
    '--- current ---'
    Show-State
    foreach ($arch in '64', '32') {
        "engine $arch has $libName : $(Test-Path (Join-Path $modsDir "$arch\$libName"))"
        "engine $arch has $prevLib : $(Test-Path (Join-Path $modsDir "$arch\$prevLib"))"
    }
    exit 0
}

if ($Build) {
    & $buildPs1 -Source $assembled -OutDir $modRoot `
        -ModIdHeader "$modRoot\translucent-flyouts-modid.h" `
        -LogPath $logPath -EngineLibRoot $engineLib -Arch both
    if ($LASTEXITCODE -ne 0) { throw "build failed (exit $LASTEXITCODE); see $logPath" }
    foreach ($arch in '64', '32') {
        $dll = Join-Path $modRoot "$id`_${Version}_1_$arch.dll"
        if (-not (Test-Path $dll)) { throw "missing build output: $dll" }
        "built $(Split-Path $dll -Leaf) sha256=$((Get-FileHash $dll -Algorithm SHA256).Hash)"
    }
    exit 0
}

if ($Install) {
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\mod-key-before-$Version-install.reg" /y | Out-Null
    if (Test-Path "$modsSrc\$id.wh.cpp") {
        Copy-Item "$modsSrc\$id.wh.cpp" "$backup\local@translucent-flyouts.wh.cpp.installed-0.6.49" -Force
    }
    foreach ($arch in '64', '32') {
        $src = Join-Path $modRoot "$id`_${Version}_1_$arch.dll"
        $dst = Join-Path $modsDir "$arch\$libName"
        Copy-Item -LiteralPath $src -Destination $dst -Force
        $same = (Get-FileHash -LiteralPath $src).Hash -eq (Get-FileHash -LiteralPath $dst).Hash
        "copied $arch to $dst hashMatches=$same"
        if (-not $same) { throw "hash mismatch after copy: $dst" }
    }
    Copy-Item $assembled "$modsSrc\$id.wh.cpp" -Force
    Set-ItemProperty $key LibraryFileName $libName
    Set-ItemProperty $key Version $Version
    Bump-Marker
    '--- after install ---'
    Show-State
    exit 0
}

if ($Rollback) {
    Set-ItemProperty $key LibraryFileName $prevLib
    Set-ItemProperty $key Version $prevVer
    Bump-Marker
    '--- after rollback ---'
    Show-State
    exit 0
}

Write-Error 'Pass -Audit, -Build, -Install or -Rollback.'
exit 2
