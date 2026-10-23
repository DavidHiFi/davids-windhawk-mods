<#
.SYNOPSIS
Verify the local@ translucent-windows install, restage the guard's pristine
copies for the new id, and write the receipt. Companion to
2026-10-15-translucent-windows-local-install.ps1, whose verification section
died on a PS 5.1 NativeCommandError (the CLI prints a harmless stderr warning
for local@ metadata; the engine itself runs local@ mods fine).

Actions: Verify | RollbackHint. Run elevated.
#>
[CmdletBinding()]
param(
    [ValidateSet('Verify')]
    [string]$Action = 'Verify'
)

$ErrorActionPreference = 'Stop'

$ws         = 'H:\Windhawk Configuration'
$newId      = 'local@translucent-windows'
$oldId      = 'translucent-windows'
$newDll     = 'local@translucent-windows_1.8.3_1.dll'
$newKeyReg  = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$newId"
$newKey     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$newId"
$mods64     = 'C:\ProgramData\Windhawk\Engine\Mods\64'
$mods32     = 'C:\ProgramData\Windhawk\Engine\Mods\32'
$modsSource = 'C:\ProgramData\Windhawk\ModsSource'
$devDir     = Join-Path $ws 'Windhawk\translucent-windows'
$guardDir   = Join-Path $devDir 'guard'
$cli        = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$profileJ   = 'C:\ProgramData\Windhawk\userprofile.json'
$rep        = Join-Path $ws 'reports\2026-10-15-translucent-windows-id-migration'
$log        = Join-Path $rep 'verify-restage.log'

function Write-Log([string]$m) {
    Add-Content -LiteralPath $log -Value ("{0} {1}" -f (Get-Date -Format o), $m) -Encoding UTF8
    Write-Output $m
}

function Get-Sha([string]$p) { (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

function Get-ProfileModNames {
    if (Test-Path $profileJ) {
        try {
            $mods = (Get-Content $profileJ -Raw | ConvertFrom-Json).mods
            if ($mods) { return @($mods.PSObject.Properties.Name) }
        } catch { }
    }
    return @()
}

function Get-Census {
    $newLoaded = 0; $oldLoaded = 0; $unopenable = 0
    Get-Process | ForEach-Object {
        try {
            foreach ($m in ($_.Modules | Where-Object { $_.ModuleName -like '*translucent-windows*' })) {
                if ($m.ModuleName -like 'local@*') { $script:newLoaded++ } else { $script:oldLoaded++ }
            }
        } catch { $script:unopenable++ }
    }
    return @{ new = $newLoaded; old = $oldLoaded; unopenable = $unopenable }
}

Write-Log '=== verify + restage start ==='

# 1. registry readback
$p = Get-ItemProperty $newKey
Write-Log "key: lib=$($p.LibraryFileName) version=$($p.Version) disabled=$($p.Disabled) include=$($p.Include) excludeCustom=$($p.ExcludeCustom)"
$settingsCount = (Get-Item "$newKey\Settings").ValueCount
Write-Log "settings count: $settingsCount"

# 2. files
if (-not (Test-Path "$mods64\$newDll")) { throw "missing $mods64\$newDll" }
if (-not (Test-Path "$mods32\$newDll")) { throw "missing $mods32\$newDll" }
if (-not (Test-Path "$modsSource\local@translucent-windows.wh.cpp")) { throw 'missing source in ModsSource' }
Write-Log "dll64 sha256: $(Get-Sha "$mods64\$newDll")"
Write-Log "dll32 sha256: $(Get-Sha "$mods32\$newDll")"

# 3. census, with one SCT nudge if the engine has not picked the mod up yet
$c = Get-Census
Write-Log "census: new=$($c.new) old=$($c.old) unopenable=$($c.unopenable)"
if ($c.new -eq 0) {
    Write-Log 'mod not loaded yet - bumping SettingsChangeTime and waiting'
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    Set-ItemProperty -Path $newKey -Name 'SettingsChangeTime' -Value $now -Type DWord
    Start-Sleep -Seconds 6
    $c = Get-Census
    Write-Log "census after nudge: new=$($c.new) old=$($c.old) unopenable=$($c.unopenable)"
    if ($c.new -eq 0) { Write-Log 'WARN: mod still not mapped in any process' }
}

# 4. CLI mod list (stderr-safe: the local@ metadata warning is expected)
$prevEap = $ErrorActionPreference
$ErrorActionPreference = 'Continue'
$listJson = (& $cli mod list --json 2>&1 | Out-String)
$ErrorActionPreference = $prevEap
if ($listJson -match [regex]::Escape($newId)) { Write-Log 'mod list: contains local@translucent-windows' } else { Write-Log 'mod list: local@translucent-windows NOT listed (CLI may skip ids it cannot parse)' }
if ($listJson -match '(?<!local@)"translucent-windows"') { Write-Log 'WARN: old id still listed by mod list' } else { Write-Log 'mod list: old id absent' }

# 5. profile entries
$names = Get-ProfileModNames
if ($names -contains $oldId) { Write-Log 'WARN: profile entry for old id present' } else { Write-Log 'profile entry for old id: absent' }
if ($names -contains $newId) { Write-Log 'note: new id tracked in profile' } else { Write-Log 'new id not tracked in profile (expected for local@ ids)' }

# 6. restage guard pristine copies for the new id
$archive = Join-Path $guardDir 'archive-256343'
New-Item $archive -ItemType Directory -Force | Out-Null
foreach ($d in @('64', '32')) {
    if (Test-Path (Join-Path $guardDir $d)) { Move-Item (Join-Path $guardDir $d) (Join-Path $archive $d) -Force }
    New-Item (Join-Path $guardDir $d) -ItemType Directory -Force | Out-Null
}
Copy-Item "$mods64\$newDll" "$guardDir\64\$newDll" -Force
Copy-Item "$mods32\$newDll" "$guardDir\32\$newDll" -Force
Move-Item "$guardDir\translucent-windows-1.8.3-256343.reg" "$archive\translucent-windows-1.8.3-256343.reg" -Force -ErrorAction SilentlyContinue
reg.exe export $newKeyReg "$guardDir\local@translucent-windows-1.8.3-1.reg" /y | Out-Null
Write-Log 'guard pristine copies restaged (old set archived under archive-256343)'

# 7. receipt
$receipt = [ordered]@{
    action                = 'verify-restage'
    date                  = '2026-10-15'
    newId                 = $newId
    libraryFileName       = $newDll
    dll64Sha256           = Get-Sha "$mods64\$newDll"
    dll32Sha256           = Get-Sha "$mods32\$newDll"
    settingsCount         = $settingsCount
    excludeCustom         = $p.ExcludeCustom
    censusNewLoaded       = $c.new
    censusOldLoaded       = $c.old
    profileOldEntryAbsent = -not ($names -contains $oldId)
}
$receipt | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $rep 'receipt-verify.json') -Encoding UTF8
Write-Log '=== verify + restage done ==='
