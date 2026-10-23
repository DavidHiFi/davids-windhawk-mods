<#
.SYNOPSIS
    Sets or clears one translucent-flyouts mod setting (for tests / scripting).

.DESCRIPTION
    Writes a value under
      HKLM\SOFTWARE\Windhawk\Engine\Mods\local@translucent-flyouts\Settings
    and bumps SettingsChangeTime so the engine reloads mods live (NO engine
    restart - that restarts explorer and breaks the live T3 Code GUI).

    The canonical settings editor is the Windhawk mod UI (Textual mode); this
    script exists for scripted tests. -Audit lists current values.

.EXAMPLE
    .\2026-09-28-translucent-flyouts-set-setting.ps1 -Audit
    .\2026-09-28-translucent-flyouts-set-setting.ps1 -Name global.effectType -Value acrylic
    .\2026-09-28-translucent-flyouts-set-setting.ps1 -Name menu.enableCustomRendering -Value 1 -Type DWord
    .\2026-09-28-translucent-flyouts-set-setting.ps1 -Remove global.effectType
#>
[CmdletBinding()]
param(
    [string]$Name,
    [string]$Value,
    [ValidateSet('String', 'DWord')]
    [string]$Type = 'String',
    [switch]$Remove,
    [switch]$Audit,
    [string]$ModKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@translucent-flyouts'
)

$ErrorActionPreference = 'Stop'

function Test-Admin {
    (New-Object Security.Principal.WindowsPrincipal(
        [Security.Principal.WindowsIdentity]::GetCurrent())
    ).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

$write = ($Name -and ($Remove -or $null -ne $Value)) -or ($Name -and $Value)
if ($Audit) { $write = $false }
if ($write -and -not (Test-Admin)) {
    $argString = '-NoProfile -ExecutionPolicy Bypass -File "{0}"' -f $PSCommandPath
    $argString += ' -Name "{0}"' -f $Name
    if ($Remove) { $argString += ' -Remove' } else { $argString += ' -Value "{0}" -Type {1}' -f $Value, $Type }
    Write-Host "elevating: $argString"
    $p = Start-Process pwsh -Verb RunAs -ArgumentList $argString -PassThru -Wait -WindowStyle Hidden
    exit $p.ExitCode
}

$settingsKey = Join-Path $ModKey 'Settings'
if ($Audit) {
    if (Test-Path -LiteralPath $settingsKey) {
        $k = Get-Item -LiteralPath $settingsKey
        foreach ($n in $k.GetValueNames()) {
            "{0}`t{1}`t{2}" -f $n, $k.GetValueKind($n), $k.GetValue($n)
        }
    } else {
        Write-Host '(no Settings key - all values use code defaults)'
    }
    exit 0
}

if (-not $Name) { Write-Host 'nothing to do (use -Name/-Value, -Remove, or -Audit)'; exit 2 }
if (-not (Test-Path -LiteralPath $ModKey)) { Write-Host "missing mod key: $ModKey"; exit 10 }

if ($Remove) {
    if (Test-Path -LiteralPath $settingsKey) {
        Remove-ItemProperty -LiteralPath $settingsKey -Name $Name -ErrorAction SilentlyContinue
    }
    Write-Host "removed $Name (default applies)"
} else {
    if (-not (Test-Path -LiteralPath $settingsKey)) { New-Item -Path $settingsKey -Force | Out-Null }
    if ($Type -eq 'DWord') {
        Set-ItemProperty -LiteralPath $settingsKey -Name $Name -Value ([int]$Value) -Type DWord
    } else {
        Set-ItemProperty -LiteralPath $settingsKey -Name $Name -Value $Value -Type String
    }
    Write-Host "set $Name=$Value ($Type)"
}

$now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
Set-ItemProperty -LiteralPath $ModKey -Name SettingsChangeTime -Value $now -Type DWord
Write-Host "SettingsChangeTime=$now (live reload)"
exit 0
