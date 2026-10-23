<#
.SYNOPSIS
Finish the rollback of the Translucent Windows Plus migration back to local@translucent-windows.

WHY THIS SCRIPT EXISTS
scripts\2026-10-24-translucent-windows-plus-migrate.ps1 -Action Rollback stopped partway at 6:10 AM
(elevated exit 1). By then it had restored the old registry key and removed the Plus key, but it had
not put the old source back in ModsSource, had not bumped SettingsChangeTime, and had not re-registered
the old guard, so the guard stayed suspended and disabled.

Every step checks a hash first and throws before changing anything if a check fails.

Run elevated through H:\System Configuration\scripts\Invoke-Elevated.ps1 -File, under the windhawk-engine lock.
#>
$ErrorActionPreference = 'Stop'

$ws        = 'H:\Windhawk Configuration'
$bkd       = Join-Path $ws 'backups\2026-10-24-translucent-windows-plus'
$modsSource = 'C:\ProgramData\Windhawk\ModsSource'
$oldSrc    = Join-Path $modsSource 'local@translucent-windows.wh.cpp'
$beforeSrc = Join-Path $bkd 'local@translucent-windows.wh.cpp.before'
$oldKey    = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@translucent-windows'
$dll       = 'local@translucent-windows_1.8.3_2.dll'
$live64    = "C:\ProgramData\Windhawk\Engine\Mods\64\$dll"
$live32    = "C:\ProgramData\Windhawk\Engine\Mods\32\$dll"
$oldGuard  = Join-Path $ws 'scripts\2026-10-15-translucent-windows-guard.ps1'
$wantSrc   = '8280803C303E8B8A931AA5D4BD3B19C38ADC4C7B80A53E8E31518F66AAC5F809'
$want64    = '7665FBCB07A157AAE201059D49C39929F4251401A41BCED272F7A44BC8987E57'
$want32    = '52C48DF65A282BEB415C859E18741420BCF25F28A5A70318B43F7903D01B37D3'

function Get-Sha([string]$p) { (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

if ((Get-Sha $beforeSrc) -ne $wantSrc) { throw 'backup source hash does not match the guard constant; stopped before any change' }
if ((Get-Sha $live64) -ne $want64)     { throw 'live x64 DLL hash does not match the guard constant' }
if ((Get-Sha $live32) -ne $want32)     { throw 'live x86 DLL hash does not match the guard constant' }

Copy-Item -LiteralPath $beforeSrc -Destination $oldSrc -Force
if ((Get-Sha $oldSrc) -ne $wantSrc) { throw 'ModsSource readback mismatch after restore' }
Write-Output 'ModsSource restored and verified'

$now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
Set-ItemProperty -Path $oldKey -Name 'SettingsChangeTime' -Value $now -Type DWord
$p = Get-ItemProperty $oldKey
if ($p.LibraryFileName -ne $dll) { throw "key points at $($p.LibraryFileName), expected $dll" }
if ([int]$p.Disabled -ne 0)      { throw 'old key is disabled' }
Write-Output "key: lib=$($p.LibraryFileName) version=$($p.Version) disabled=$($p.Disabled)"

Remove-Item -LiteralPath @(
    'C:\ProgramData\Windhawk\Engine\Mods\64\local@translucent-windows-plus_1.8.3_1.dll',
    'C:\ProgramData\Windhawk\Engine\Mods\32\local@translucent-windows-plus_1.8.3_1.dll'
) -Force -ErrorAction SilentlyContinue
Write-Output 'Plus DLL copies removed where unmapped'

& $oldGuard -Action InstallGuard
