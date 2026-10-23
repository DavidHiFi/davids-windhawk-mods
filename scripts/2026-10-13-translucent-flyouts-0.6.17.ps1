<#
.SYNOPSIS
    Translucent Flyouts 0.6.17 (menu body painted with the Gradient Color under a blur or acrylic effect), 2026-10-13.

.DESCRIPTION
    -Audit     print the current values and the planned actions
    -Install   copy both 0.6.17 DLLs and the canonical source into place, point
               LibraryFileName and Version at 0.6.17, bump SettingsChangeTime
    -Rollback  point LibraryFileName and Version back at 0.6.16, restore the
               0.6.16 canonical source, bump SettingsChangeTime

    Needs elevation (ProgramData and HKLM writes). Run it through
    H:\System Configuration\scripts\Invoke-Elevated.ps1. Does not restart
    Windhawk or Explorer; the engine reloads the mod on the settings marker.
    A new DLL is loaded by Explorer only after an Explorer restart.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Install,
    [switch]$Rollback
)

$ErrorActionPreference = 'Stop'
$id      = 'local@translucent-flyouts'
$key     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$mods    = 'C:\ProgramData\Windhawk\Engine\Mods'
$source  = 'C:\ProgramData\Windhawk\ModsSource\local@translucent-flyouts.wh.cpp'
$build   = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts\build-0.6.17'
$backup  = 'H:\Windhawk Configuration\backups\2026-10-13\translucent-flyouts-0.6.17'
$newLib  = 'local@translucent-flyouts_0.6.17_1.dll'
$oldLib  = 'local@translucent-flyouts_0.6.16_1.dll'

function Show-State {
    $p = Get-ItemProperty $key
    "LibraryFileName=$($p.LibraryFileName) Version=$($p.Version) Include=$($p.Include) Exclude=$($p.Exclude) SettingsChangeTime=$($p.SettingsChangeTime)"
}
function Bump-Marker {
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $prev = (Get-ItemProperty $key).SettingsChangeTime
    $value = if ($prev -ge $now) { $prev + 1 } else { $now }
    Set-ItemProperty $key SettingsChangeTime -Value $value -Type DWord
    $value
}

function Copy-IfDifferent([string]$from, [string]$to) {
    if ((Test-Path -LiteralPath $to) -and ((Get-FileHash -LiteralPath $from).Hash -eq (Get-FileHash -LiteralPath $to).Hash)) {
        "unchanged: $to"
    } else {
        Copy-Item -LiteralPath $from -Destination $to -Force
    }
}

if ($Audit) {
    'current:'; Show-State
    "would copy: $build\local@translucent-flyouts_0.6.17_1_64.dll -> $mods\64\$newLib"
    "would copy: $build\local@translucent-flyouts_0.6.17_1_32.dll -> $mods\32\$newLib"
    "would copy: $build\local@translucent-flyouts.wh.cpp -> $source"
    "would set LibraryFileName=$newLib Version=0.6.17 and bump SettingsChangeTime"
    exit 0
}

if ($Install) {
    Copy-IfDifferent "$build\local@translucent-flyouts_0.6.17_1_64.dll" "$mods\64\$newLib"
    Copy-IfDifferent "$build\local@translucent-flyouts_0.6.17_1_32.dll" "$mods\32\$newLib"
    Copy-IfDifferent "$build\local@translucent-flyouts.wh.cpp" $source
    Set-ItemProperty $key LibraryFileName $newLib
    Set-ItemProperty $key Version '0.6.17'
    $marker = Bump-Marker
    'installed:'; Show-State
    $checks = @(
        ((Get-FileHash "$mods\64\$newLib").Hash -eq (Get-FileHash "$build\local@translucent-flyouts_0.6.17_1_64.dll").Hash),
        ((Get-FileHash "$mods\32\$newLib").Hash -eq (Get-FileHash "$build\local@translucent-flyouts_0.6.17_1_32.dll").Hash),
        ((Get-FileHash $source).Hash -eq (Get-FileHash "$build\local@translucent-flyouts.wh.cpp").Hash),
        ((Get-ItemProperty $key).LibraryFileName -eq $newLib)
    )
    $receipt = [ordered]@{
        date = (Get-Date -Format 'yyyy-MM-dd HH:mm:ss')
        action = 'install'
        mod = $id
        from = $oldLib
        to = $newLib
        settings_change_time = $marker
        verified = ($checks -notcontains $false)
        restart = 'none'
    }
    $receipt | ConvertTo-Json | Set-Content -LiteralPath "$backup\receipt-install-0.6.17.json" -Encoding UTF8
    if ($checks -contains $false) { 'VERIFY FAILED'; exit 2 }
    'verified: hashes and LibraryFileName match'
    exit 0
}

if ($Rollback) {
    Set-ItemProperty $key LibraryFileName $oldLib
    Set-ItemProperty $key Version '0.6.16'
    Copy-Item "$backup\local@translucent-flyouts.wh.cpp.0.6.16" $source -Force
    $marker = Bump-Marker
    'rolled back:'; Show-State
    $receipt = [ordered]@{
        date = (Get-Date -Format 'yyyy-MM-dd HH:mm:ss')
        action = 'rollback'
        mod = $id
        to = $oldLib
        settings_change_time = $marker
        restart = 'none'
    }
    $receipt | ConvertTo-Json | Set-Content -LiteralPath "$backup\receipt-rollback-0.6.16.json" -Encoding UTF8
    exit 0
}

'Nothing to do: pass -Audit, -Install or -Rollback'
exit 1
