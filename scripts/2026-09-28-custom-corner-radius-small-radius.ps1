<#
.SYNOPSIS
    Sets the custom-corner-radius mod's "Small corner radius" (menus, small
    flyouts), live, with a registry backup and a receipt.

.DESCRIPTION
    The translucent-flyouts fix on 2026-09-28 unified menu corners with the
    window corner radius (16). Menus are DWM "small radius" elements: while
    custom-corner-radius is active, the effective menu radius follows its
    smallRadius setting, not the menu's corner preference. The original value
    was 8; it was changed to 16 so menus match windows (radius=16).

    Modes (default -Audit; -Set self-elevates):
      -Audit            Show radius / smallRadius / tooltipRadius.
      -Set <n>          Write smallRadius=n, bump SettingsChangeTime (live
                        reload in dwm.exe; no engine restart).

.EXAMPLE
    .\2026-09-28-custom-corner-radius-small-radius.ps1 -Set 8   # rollback
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [int]$Set = -1,
    [string]$BackupDir = 'H:\Windhawk Configuration\backups\2026-09-28\custom-corner-radius'
)

$ErrorActionPreference = 'Stop'

$ModKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\custom-corner-radius'
$SetKey = Join-Path $ModKey 'Settings'

function Test-Admin {
    (New-Object Security.Principal.WindowsPrincipal(
        [Security.Principal.WindowsIdentity]::GetCurrent())
    ).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

if (-not $Audit -and $Set -ge 0 -and -not (Test-Admin)) {
    $argString = '-NoProfile -ExecutionPolicy Bypass -File "{0}" -Set {1}' -f $PSCommandPath, $Set
    Write-Host "elevating: $argString"
    $p = Start-Process pwsh -Verb RunAs -ArgumentList $argString -PassThru -Wait -WindowStyle Hidden
    exit $p.ExitCode
}

$props = Get-ItemProperty -LiteralPath $SetKey
$before = $props.smallRadius
Write-Host ("smallRadius={0} radius={1} tooltipRadius={2}" -f $props.smallRadius, $props.radius, $props.tooltipRadius)

if ($Audit -or $Set -lt 0) {
    exit 0
}

if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null }
$stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$regFile = Join-Path $BackupDir ("custom-corner-radius-before-{0}.reg" -f $stamp)
$null = & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\custom-corner-radius' $regFile /y 2>&1

Set-ItemProperty -LiteralPath $SetKey -Name 'smallRadius' -Value $Set -Type DWord
$now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
Set-ItemProperty -LiteralPath $ModKey -Name 'SettingsChangeTime' -Value $now -Type DWord

$after = (Get-ItemProperty -LiteralPath $SetKey).smallRadius
Write-Host ("smallRadius: {0} -> {1} (SettingsChangeTime={2})" -f $before, $after, $now)

$receipt = [ordered]@{
    mode              = 'set'
    timestamp         = (Get-Date -Format o)
    mod_id            = 'custom-corner-radius'
    setting           = 'smallRadius'
    value_before      = $before
    value_after       = $after
    reg_backup        = $regFile
    reason            = 'unify context-menu corner radius with windows (16px) for the translucent-flyouts fix'
    rollback_command  = ".\2026-09-28-custom-corner-radius-small-radius.ps1 -Set $before"
}
$receipt | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $BackupDir 'small-radius-receipt.json') -Encoding UTF8
Write-Host "receipt: $(Join-Path $BackupDir 'small-radius-receipt.json')"
