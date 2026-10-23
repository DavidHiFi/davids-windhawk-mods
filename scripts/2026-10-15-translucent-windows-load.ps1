<#
.SYNOPSIS
Get the freshly installed local@translucent-windows mod loaded by the engine.
Tries the house trigger (windhawk-cli mod compile), then a registry
disable/enable cycle, verifying with a module census after each step. A
baseline census of other mods confirms injection itself is healthy.

Run elevated.
#>
[CmdletBinding()]
param()

$ErrorActionPreference = 'Stop'

$cli      = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$newId    = 'local@translucent-windows'
$newKey   = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@translucent-windows'
$rep      = 'H:\Windhawk Configuration\reports\2026-10-15-translucent-windows-id-migration'
$log      = Join-Path $rep 'load.log'

function Write-Log([string]$m) {
    Add-Content -LiteralPath $log -Value ("{0} {1}" -f (Get-Date -Format o), $m) -Encoding UTF8
    Write-Output $m
}

function Get-Census {
    $new = 0; $old = 0; $base = 0; $unopenable = 0
    Get-Process | ForEach-Object {
        try {
            foreach ($m in ($_.Modules)) {
                if ($m.ModuleName -like '*translucent-windows*') {
                    if ($m.ModuleName -like 'local@*') { $script:new++ } else { $script:old++ }
                }
                elseif ($m.ModuleName -like 'windows-11-taskbar-styler*') { $script:base++ }
            }
        } catch { $script:unopenable++ }
    }
    return @{ new = $new; old = $old; baseline = $base; unopenable = $unopenable }
}

Write-Log '=== load start ==='
$c = Get-Census
Write-Log "baseline census: new=$($c.new) old=$($c.old) taskbar-styler=$($c.baseline) unopenable=$($c.unopenable)"

# mod-status files for the new id (engine error state?)
$statusDir = 'C:\ProgramData\Windhawk\Engine\ModsWritable\mod-status'
if (Test-Path $statusDir) {
    $hits = Get-ChildItem $statusDir -Filter '*translucent*' -ErrorAction SilentlyContinue
    foreach ($h in $hits) {
        Write-Log "mod-status file: $($h.Name) ($($h.Length) bytes)"
        Get-Content $h.FullName -TotalCount 10 | ForEach-Object { Write-Log "  status: $_" }
    }
    if (-not $hits) { Write-Log 'mod-status: no translucent entries' }
}

# 1. house trigger: CLI compile (loads the mod after compiling)
$prevEap = $ErrorActionPreference
$ErrorActionPreference = 'Continue'
$out = & $cli mod compile $newId 2>&1 | Out-String
$code = $LASTEXITCODE
$ErrorActionPreference = $prevEap
$out -split "`n" | Select-Object -First 12 | ForEach-Object { Write-Log "cli compile: $_" }
Write-Log "cli compile exit: $code"

if ($code -eq 0) {
    Start-Sleep -Seconds 6
    $c = Get-Census
    Write-Log "census after compile: new=$($c.new) old=$($c.old) taskbar-styler=$($c.baseline) unopenable=$($c.unopenable)"
}

if ($c.new -eq 0) {
    # 2. registry disable/enable cycle on the new key
    Write-Log 'trying registry disable/enable cycle'
    Set-ItemProperty -Path $newKey -Name 'Disabled' -Value 1 -Type DWord
    Start-Sleep -Seconds 2
    Set-ItemProperty -Path $newKey -Name 'Disabled' -Value 0 -Type DWord
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    Set-ItemProperty -Path $newKey -Name 'SettingsChangeTime' -Value $now -Type DWord
    Start-Sleep -Seconds 8
    $c = Get-Census
    Write-Log "census after cycle: new=$($c.new) old=$($c.old) taskbar-styler=$($c.baseline) unopenable=$($c.unopenable)"
}

if ($c.new -eq 0) {
    Write-Log 'WARN: mod is still not mapped in any process - needs manual investigation'
} else {
    Write-Log 'mod is loaded'
}
Write-Log '=== load done ==='
