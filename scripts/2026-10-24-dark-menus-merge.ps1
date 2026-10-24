<#
.SYNOPSIS
    Retire the "Dark mode context menus" mod (dark-menus 1.4.2) and ship its code inside
    Translucent Flyouts 0.6.66.

.DESCRIPTION
    -Audit     print both mods' registry state; change nothing
    -Install   back up, remove dark-menus through windhawk-cli (clears key, source, DLLs,
               profile entry), then install the 0.6.66 DLLs, source and registry values
               and bump SettingsChangeTime. Order matters: dark-menus resets the process
               menu theme when it unloads, so it goes first and 0.6.66 applies after.
    -Rollback  point flyouts back at 0.6.65_5 and reinstall dark-menus from the backed-up
               source with its saved settings

    Needs elevation. Run through H:\System Configuration\scripts\Invoke-Elevated.ps1.
    Build first: scripts\2026-09-28-translucent-flyouts-build.ps1 (Engine\2.0.0).
#>
param([switch]$Audit, [switch]$Install, [switch]$Rollback)

$ErrorActionPreference = 'Stop'
$cli       = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$id        = 'local@translucent-flyouts'
$key       = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$darkKey   = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\dark-menus'
$modRoot   = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts'
$assembled = "$modRoot\translucent-flyouts.wh.cpp"
$modsDir   = 'C:\ProgramData\Windhawk\Engine\Mods'
$modsSrc   = 'C:\ProgramData\Windhawk\ModsSource'
$version   = '0.6.66'
$libName   = "$id`_${version}_1.dll"
$prevLib   = "$id`_0.6.65_5.dll"
$prevVer   = '0.6.65'
$backup    = 'H:\Windhawk Configuration\backups\2026-10-24\dark-menus-merge'
$logPath   = 'H:\Windhawk Configuration\work\2026-10-24-dark-menus-merge\install.log'

function Log([string]$t) {
    $line = "$(Get-Date -Format 'h:mm:ss tt') $t"
    Write-Host $line
    Add-Content -LiteralPath $logPath -Value $line
}
function Show-State {
    foreach ($k in $key, $darkKey) {
        if (Test-Path $k) {
            $p = Get-ItemProperty $k
            Log "$(Split-Path $k -Leaf): LibraryFileName=$($p.LibraryFileName) Version=$($p.Version) Disabled=$($p.Disabled)"
        } else {
            Log "$(Split-Path $k -Leaf): key absent"
        }
    }
}
function Bump-Marker {
    $now  = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $prev = (Get-ItemProperty $key).SettingsChangeTime
    $value = if ($prev -ge $now) { $prev + 1 } else { $now }
    Set-ItemProperty $key SettingsChangeTime -Value $value -Type DWord
    Log "bumped SettingsChangeTime=$value"
}

New-Item -ItemType Directory -Force -Path (Split-Path $logPath) | Out-Null

if ($Audit) { Show-State; exit 0 }

if ($Install) {
    Show-State
    foreach ($arch in '64', '32') {
        $dll = Join-Path $modRoot "$id`_${version}_1_$arch.dll"
        if (-not (Test-Path $dll)) { throw "missing build output: $dll" }
    }
    if (-not (Select-String -LiteralPath $assembled -Pattern "@version\s+$version\b" -Quiet)) {
        throw "assembled source is not $version"
    }

    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\dark-menus' "$backup\dark-menus.reg" /y | Out-Null
    & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\flyouts-before-0.6.66.reg" /y | Out-Null
    Copy-Item "$modsSrc\dark-menus.wh.cpp" "$backup\dark-menus.wh.cpp" -Force
    Copy-Item "$modsSrc\$id.wh.cpp" "$backup\flyouts-0.6.65.wh.cpp" -Force
    Copy-Item 'C:\ProgramData\Windhawk\userprofile.json' "$backup\userprofile.json.before" -Force
    Log "backup: $backup"

    # 1. copy the 0.6.66 DLLs first (nothing points at them yet)
    foreach ($arch in '64', '32') {
        $src = Join-Path $modRoot "$id`_${version}_1_$arch.dll"
        $dst = Join-Path $modsDir "$arch\$libName"
        Copy-Item -LiteralPath $src -Destination $dst -Force
        $same = (Get-FileHash -LiteralPath $src).Hash -eq (Get-FileHash -LiteralPath $dst).Hash
        Log "copied $arch hashMatches=$same"
        if (-not $same) { throw "hash mismatch after copy: $dst" }
    }

    # 2. retire dark-menus
    $out = & $cli mod remove dark-menus --yes 2>&1
    $out | ForEach-Object { Log "cli remove: $_" }
    if ($LASTEXITCODE -ne 0) { throw "mod remove failed (exit $LASTEXITCODE)" }
    if (Test-Path $darkKey) { throw 'dark-menus key still present after remove' }
    if (Test-Path "$modsSrc\dark-menus.wh.cpp") { throw 'dark-menus source still present after remove' }
    Log 'dark-menus removed'

    # 3. flyouts 0.6.66 live; carry the old setting across explicitly
    Copy-Item -LiteralPath $assembled -Destination "$modsSrc\$id.wh.cpp" -Force
    New-ItemProperty -LiteralPath "$key\Settings" -Name 'darkMenus.appMode' -Value 'force_dark' -PropertyType String -Force | Out-Null
    Set-ItemProperty $key LibraryFileName $libName
    Set-ItemProperty $key Version $version
    Bump-Marker
    Show-State
    exit 0
}

if ($Rollback) {
    Set-ItemProperty $key LibraryFileName $prevLib
    Set-ItemProperty $key Version $prevVer
    Copy-Item "$backup\flyouts-0.6.65.wh.cpp" "$modsSrc\$id.wh.cpp" -Force
    Remove-ItemProperty -LiteralPath "$key\Settings" -Name 'darkMenus.appMode' -ErrorAction SilentlyContinue
    Bump-Marker
    $out = & $cli mod install --file "$backup\dark-menus.wh.cpp" 2>&1
    $out | ForEach-Object { Log "cli install: $_" }
    if ($LASTEXITCODE -ne 0) { throw "dark-menus reinstall failed (exit $LASTEXITCODE)" }
    $darkSettings = "$darkKey\Settings"
    New-ItemProperty -LiteralPath $darkSettings -Name AppMode -Value 'ForceDark' -PropertyType String -Force | Out-Null
    New-ItemProperty -LiteralPath $darkSettings -Name TranslucentFlyoutsFix -Value 1 -PropertyType DWord -Force | Out-Null
    Show-State
    exit 0
}

Write-Error 'Pass -Audit, -Install or -Rollback.'
exit 2
