<#
.SYNOPSIS
Applies this repo's Windhawk state and settings to the local machine.

.DESCRIPTION
Reads settings\mods-state.json and settings\mods-settings.json and writes them
to HKLM\SOFTWARE\Windhawk\Engine\Mods. Optionally imports the Windhawk app and
engine .reg files and restarts the engine. Run elevated, or use -Audit to see
what would change without writing anything.

.PARAMETER Audit
Print the planned changes and write nothing. Works without elevation.

.PARAMETER IncludeAppSettings
Also import settings\windhawk-app-settings.reg and
settings\windhawk-engine-settings.reg.

.PARAMETER RestartEngine
Restart the Windhawk engine when done (windhawk.exe -restart).

.EXAMPLE
.\Apply-WindhawkSettings.ps1 -Audit
Show every difference between this machine and the snapshot.

.EXAMPLE
.\Apply-WindhawkSettings.ps1 -IncludeAppSettings -RestartEngine
Apply everything and restart the engine.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$IncludeAppSettings,
    [switch]$RestartEngine
)

$ErrorActionPreference = 'Stop'
$repoRoot = Split-Path $PSScriptRoot -Parent
$stateFile = Join-Path $repoRoot 'settings\mods-state.json'
$settingsFile = Join-Path $repoRoot 'settings\mods-settings.json'

$isAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not [Environment]::Is64BitProcess) { throw 'Run from 64-bit PowerShell. 32-bit PowerShell sees a different registry view.' }
if (-not $Audit -and -not $isAdmin) { throw 'Run elevated, or use -Audit to preview.' }
foreach ($f in $stateFile, $settingsFile) { if (-not (Test-Path $f)) { throw "missing $f" } }

$script:changes = 0

function Write-Change {
    param([string]$Key, [string]$Name, $From, $To)
    $shown = if ($null -eq $From) { '(absent)' } else { [string]$From }
    $short = $Key -replace '^.*\\Mods', 'Mods'
    Write-Output ("  {0}\{1}: {2} -> {3}" -f $short, $Name, $shown, $To)
    $script:changes++
}

function Set-RegValue {
    # Value names can contain [ and ], and DWORDs are unsigned while .NET reads
    # them signed, so everything here goes through the .NET registry API with
    # explicit normalization. The PowerShell cmdlets treat [ and ] as wildcards.
    param([string]$Key, [string]$Name, $Value, [string]$Type)
    $kind = [Microsoft.Win32.RegistryValueKind]$Type
    if ($Key -like 'HKLM:*') { $hive = [Microsoft.Win32.Registry]::LocalMachine } else { throw "unsupported hive: $Key" }
    $sub = $Key.Substring($Key.IndexOf(':') + 1).TrimStart('\')

    $read = $hive.OpenSubKey($sub, $false)
    if ($read) {
        $current = $null
        if ($read.GetValueNames() -contains $Name) {
            $current = $read.GetValue($Name, $null)
            $same = if ($kind -eq [Microsoft.Win32.RegistryValueKind]::DWord) {
                ([int64]$current -band 4294967295) -eq ([int64]$Value -band 4294967295)
            } else {
                [string]$current -eq [string]$Value
            }
            if ($same) { $read.Close(); return }
        }
        $read.Close()
    } else { $current = $null }

    Write-Change $Key $Name $current $Value
    if ($Audit) { return }

    $write = $hive.CreateSubKey($sub, $true)
    if ($kind -eq [Microsoft.Win32.RegistryValueKind]::DWord) {
        $n = [int64]$Value -band 4294967295
        if ($n -gt [int]::MaxValue) { $n -= 4294967296 }
        $write.SetValue($Name, [int]$n, $kind)
    } else {
        $write.SetValue($Name, [string]$Value, $kind)
    }
    $write.Close()
}

$modsKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'

Write-Output 'state:'
$state = Get-Content $stateFile -Raw | ConvertFrom-Json
foreach ($mod in $state.PSObject.Properties) {
    $key = Join-Path $modsKey $mod.Name
    $st = $mod.Value
    Set-RegValue $key 'Disabled' ([int][bool]$st.disabled) 'DWord'
    foreach ($pair in @(@('Include', $st.include), @('Exclude', $st.exclude), @('Architecture', $st.architecture))) {
        if ($pair[1]) { Set-RegValue $key $pair[0] ([string]$pair[1]) 'String' }
    }
}

Write-Output 'values:'
$settings = Get-Content $settingsFile -Raw | ConvertFrom-Json
foreach ($mod in $settings.PSObject.Properties) {
    $key = Join-Path $modsKey ($mod.Name + '\Settings')
    foreach ($value in $mod.Value.PSObject.Properties) {
        $type = if ($value.Value -is [int] -or $value.Value -is [long]) { 'DWord' } else { 'String' }
        Set-RegValue $key $value.Name $value.Value $type
    }
}

if ($IncludeAppSettings) {
    foreach ($file in 'windhawk-app-settings.reg', 'windhawk-engine-settings.reg') {
        $path = Join-Path $repoRoot "settings\$file"
        if (-not (Test-Path $path)) { Write-Warning "skipping missing $file"; continue }
        Write-Output "importing $file"
        if (-not $Audit) { & reg.exe import $path | Out-Null }
    }
}

if ($RestartEngine) {
    $exe = 'C:\Program Files\Windhawk\windhawk.exe'
    if (Test-Path $exe) {
        Write-Output 'restarting the Windhawk engine'
        if (-not $Audit) { Start-Process -FilePath $exe -ArgumentList '-restart' -WindowStyle Hidden }
    } else { Write-Warning "windhawk.exe not found at $exe" }
}

if ($Audit) { Write-Output "audit: $($script:changes) difference(s) found, nothing written" }
else { Write-Output "applied: $($script:changes) change(s)" }
