<#
.SYNOPSIS
    Forces Explorer to load a fresh copy of the current translucent-flyouts build under a
    new DLL filename, so colour settings that stopped updating are read again.

.DESCRIPTION
    Copies the 0.6.13 x64 and x86 DLLs to *_0.6.13_2.dll, points LibraryFileName at the
    copy, and bumps SettingsChangeTime. -Rollback points LibraryFileName back at the
    original _0.6.13_1.dll. Needs elevation. Does not restart Windhawk or Explorer.
#>
[CmdletBinding()]
param([switch]$Rollback)

$ErrorActionPreference = 'Stop'
$id    = 'local@translucent-flyouts'
$key   = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$mods  = 'C:\ProgramData\Windhawk\Engine\Mods'
$orig  = 'local@translucent-flyouts_0.6.13_1.dll'
$copy  = 'local@translucent-flyouts_0.6.13_2.dll'

if (-not $Rollback) {
    Copy-Item -LiteralPath "$mods\64\$orig" -Destination "$mods\64\$copy" -Force
    Copy-Item -LiteralPath "$mods\32\$orig" -Destination "$mods\32\$copy" -Force
    Set-ItemProperty $key LibraryFileName $copy
} else {
    Set-ItemProperty $key LibraryFileName $orig
}
$now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
$prev = (Get-ItemProperty $key).SettingsChangeTime
$marker = if ($prev -ge $now) { $prev + 1 } else { $now }
Set-ItemProperty $key SettingsChangeTime -Value $marker -Type DWord
"LibraryFileName=$((Get-ItemProperty $key).LibraryFileName) SettingsChangeTime=$marker"
exit 0
