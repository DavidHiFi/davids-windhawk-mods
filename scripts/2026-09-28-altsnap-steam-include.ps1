<#
.SYNOPSIS
    Adds the Steam client to Windhawk's process inclusion list so the engine
    injects into it despite the built-in "well-known games" exclusion.

.DESCRIPTION
    The Windhawk engine excludes ?:\Program Files\Steam\* (and the x86 twin)
    by default, as part of the well-known games list, so no mod - including
    local@alt-snap-drag - can ever load in steam.exe / steamwebhelper.exe.
    The engine's process inclusion list overrides that exclusion.

    Modes (default -Audit, which changes nothing):

    -Audit      Print engine Settings (Include/Exclude/InjectInto*), the engine
                service process, and whether steam.exe / steamwebhelper.exe
                currently carry windhawk.dll and the mod.
    -Install    Back up HKLM\SOFTWARE\Windhawk\Engine, add the Steam client
                paths to Engine\Settings\Include, restart the engine, wait for
                injection, write a receipt. Requires elevation.
    -Rollback   Remove the Steam entries from Include, restart the engine,
                write a receipt. Requires elevation.

    Only the Steam client paths are added. Game installs (steamapps\common)
    stay excluded: anti-cheat inside games does not tolerate injection.
#>
[CmdletBinding()]
param(
    [switch]$Install,
    [switch]$Rollback,
    [switch]$Audit,
    [string]$LogPath   = 'H:\Windhawk Configuration\reports\2026-09-28\altsnap-steam-include.log',
    [string]$BackupDir = 'H:\Windhawk Configuration\backups\2026-09-28\altsnap-steam-include'
)

$ErrorActionPreference = 'Stop'

$EngineKey    = 'HKLM:\SOFTWARE\Windhawk\Engine'
$SettingsKey  = 'HKLM:\SOFTWARE\Windhawk\Engine\Settings'
$WindhawkExe  = 'C:\Program Files\Windhawk\windhawk.exe'
$SteamPatterns = @(
    'C:\Program Files (x86)\Steam\*',
    'C:\Program Files\Steam\*'
)

$logDir = Split-Path -Parent $LogPath
if (-not (Test-Path -LiteralPath $logDir)) {
    New-Item -ItemType Directory -Path $logDir -Force | Out-Null
}
function Write-Log {
    param([string]$Message)
    $line = '{0} {1}' -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'), $Message
    Write-Host $line
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
}
function Test-Admin {
    (New-Object Security.Principal.WindowsPrincipal(
        [Security.Principal.WindowsIdentity]::GetCurrent())
    ).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}
function Get-SettingValue {
    param([string]$Name)
    if (-not (Test-Path -LiteralPath $SettingsKey)) { return $null }
    (Get-ItemProperty -LiteralPath $SettingsKey -Name $Name -ErrorAction SilentlyContinue).$Name
}
function Get-IncludeList {
    $v = Get-SettingValue -Name 'Include'
    if (-not $v) { return @() }
    return @($v -split '\|' | Where-Object { $_ -ne '' })
}
function Set-IncludeList {
    param([string[]]$List)
    if (-not (Test-Path -LiteralPath $SettingsKey)) {
        $null = New-Item -Path $SettingsKey -Force
    }
    $joined = ($List -join '|')
    if ($joined) {
        $null = New-ItemProperty -LiteralPath $SettingsKey -Name Include -Value $joined -PropertyType String -Force
    } else {
        Remove-ItemProperty -LiteralPath $SettingsKey -Name Include -ErrorAction SilentlyContinue
    }
}
function Get-EngineServicePid {
    (Get-CimInstance Win32_Service -Filter "Name='Windhawk'").ProcessId
}
function Restart-Engine {
    $before = Get-EngineServicePid
    Write-Log "engine service pid before restart: $before"
    Start-Process -FilePath $WindhawkExe -ArgumentList '-restart' -WindowStyle Hidden
    $deadline = (Get-Date).AddSeconds(60)
    $svc = $null
    do {
        Start-Sleep -Milliseconds 500
        $svc = Get-CimInstance Win32_Service -Filter "Name='Windhawk'"
    } while (($svc.State -ne 'Running' -or $svc.ProcessId -eq $before) -and (Get-Date) -lt $deadline)
    Write-Log "engine service after restart: state=$($svc.State) pid=$($svc.ProcessId)"
    return @{ PidBefore = $before; PidAfter = $svc.ProcessId; State = $svc.State }
}
function Get-SteamInjection {
    $rows = foreach ($p in (Get-Process -Name 'steam','steamwebhelper' -ErrorAction SilentlyContinue)) {
        $mods = @()
        try {
            $mods = @($p.Modules | Where-Object { $_.ModuleName -match 'windhawk|alt-snap|alt-drag' } |
                     ForEach-Object { $_.ModuleName })
        } catch {
            $mods = @('ERR')
        }
        [pscustomobject]@{
            Id   = $p.Id
            Name = $p.ProcessName
            Mods = ($mods -join ', ')
        }
    }
    return @($rows)
}
function Wait-SteamInjection {
    param([int]$TimeoutSeconds = 30)
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    do {
        Start-Sleep -Seconds 1
        $rows = Get-SteamInjection
        $injected = @($rows | Where-Object { $_.Mods -match 'alt-snap' })
    } while ($injected.Count -eq 0 -and (Get-Date) -lt $deadline)
    return @($rows)
}
function Show-State {
    Write-Log '--- engine settings ---'
    foreach ($n in 'Include','Exclude','InjectIntoCriticalProcesses','InjectIntoIncompatiblePrograms','InjectIntoGames') {
        Write-Log ("{0} = {1}" -f $n, (Get-SettingValue -Name $n))
    }
    $svc = Get-CimInstance Win32_Service -Filter "Name='Windhawk'"
    Write-Log "engine service: state=$($svc.State) pid=$($svc.ProcessId) start=$($svc.StartName)"
    Write-Log '--- steam injection ---'
    $rows = Get-SteamInjection
    if ($rows.Count -eq 0) {
        Write-Log 'no steam.exe / steamwebhelper.exe processes'
    } else {
        foreach ($r in $rows) { Write-Log ("pid {0} {1}: {2}" -f $r.Id, $r.Name, $r.Mods) }
    }
}

if (($Install -and $Rollback) -or ($Install -and $Audit) -or ($Rollback -and $Audit)) {
    Write-Log 'use exactly one of -Audit, -Install, -Rollback'
    exit 2
}
if (-not ($Install -or $Rollback)) { $Audit = $true }

Write-Log "=== altsnap-steam-include: mode=$($(if ($Install) {'install'} elseif ($Rollback) {'rollback'} else {'audit'})) ==="
Write-Log ("identity={0} elevated={1}" -f [Security.Principal.WindowsIdentity]::GetCurrent().Name, (Test-Admin))

if ($Audit) {
    Show-State
    exit 0
}

if (-not (Test-Admin)) {
    Write-Log 'not elevated; aborting'
    exit 10
}

if ($Install) {
    if (-not (Test-Path -LiteralPath $BackupDir)) {
        New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null
    }
    $stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    $engineRegFile = Join-Path $BackupDir "windhawk-engine-before-$stamp.reg"
    $null = & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine' $engineRegFile /y 2>&1
    Write-Log "backup: reg export HKLM\SOFTWARE\Windhawk\Engine -> $engineRegFile (exit=$LASTEXITCODE)"
    $settingsRegFile = Join-Path $BackupDir "windhawk-engine-settings-before-$stamp.reg"
    $null = & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Settings' $settingsRegFile /y 2>&1
    Write-Log "backup: reg export HKLM\SOFTWARE\Windhawk\Engine\Settings -> $settingsRegFile (exit=$LASTEXITCODE)"

    $includeBefore = Get-IncludeList
    Write-Log ("Include before: [{0}]" -f ($includeBefore -join ', '))

    $includeAfter = @($includeBefore)
    foreach ($pattern in $SteamPatterns) {
        if ($includeAfter -notcontains $pattern) { $includeAfter += $pattern }
    }
    Set-IncludeList -List $includeAfter
    $includeReadBack = Get-IncludeList
    Write-Log ("Include after:  [{0}]" -f ($includeReadBack -join ', '))
    if (($includeReadBack -join '|') -ne ($includeAfter -join '|')) {
        Write-Log 'read-back mismatch; aborting'
        exit 12
    }

    $engine = Restart-Engine
    $steamRows = Wait-SteamInjection -TimeoutSeconds 30
    foreach ($r in $steamRows) { Write-Log ("pid {0} {1}: {2}" -f $r.Id, $r.Name, $r.Mods) }
    $injectedCount = @($steamRows | Where-Object { $_.Mods -match 'alt-snap' }).Count

    $receipt = [ordered]@{
        mode                  = 'install'
        timestamp             = (Get-Date -Format o)
        identity              = [Security.Principal.WindowsIdentity]::GetCurrent().Name
        settings_key          = 'HKLM\SOFTWARE\Windhawk\Engine\Settings'
        include_before        = $includeBefore
        include_after         = $includeReadBack
        steam_patterns_added  = $SteamPatterns
        engine_pid_before     = $engine.PidBefore
        engine_pid_after      = $engine.PidAfter
        engine_state          = $engine.State
        steam_injection_after = $steamRows
        steam_injected_count  = $injectedCount
        engine_reg_backup     = $engineRegFile
        settings_reg_backup   = $settingsRegFile
        log                   = $LogPath
    }
    $receiptFile = Join-Path $BackupDir 'steam-include-receipt.json'
    $receipt | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $receiptFile -Encoding UTF8
    Write-Log "receipt: $receiptFile"
    if ($injectedCount -gt 0) {
        Write-Log 'INSTALL OK - mod present in Steam processes'
        exit 0
    }
    Write-Log 'INSTALL DONE but no alt-snap in Steam processes yet (may need a Steam restart)'
    exit 13
}

if ($Rollback) {
    $includeBefore = Get-IncludeList
    Write-Log ("Include before rollback: [{0}]" -f ($includeBefore -join ', '))
    $includeAfter = @($includeBefore | Where-Object { $SteamPatterns -notcontains $_ })
    Set-IncludeList -List $includeAfter
    $includeReadBack = Get-IncludeList
    Write-Log ("Include after rollback:  [{0}]" -f ($includeReadBack -join ', '))
    $engine = Restart-Engine
    $steamRows = Wait-SteamInjection -TimeoutSeconds 15
    foreach ($r in $steamRows) { Write-Log ("pid {0} {1}: {2}" -f $r.Id, $r.Name, $r.Mods) }
    $receipt = [ordered]@{
        mode                  = 'rollback'
        timestamp             = (Get-Date -Format o)
        identity              = [Security.Principal.WindowsIdentity]::GetCurrent().Name
        include_before        = $includeBefore
        include_after         = $includeReadBack
        engine_pid_before     = $engine.PidBefore
        engine_pid_after      = $engine.PidAfter
        engine_state          = $engine.State
        steam_injection_after = $steamRows
        log                   = $LogPath
    }
    $receiptFile = Join-Path $BackupDir 'steam-include-rollback-receipt.json'
    $receipt | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $receiptFile -Encoding UTF8
    Write-Log "receipt: $receiptFile"
    Write-Log 'ROLLBACK OK'
    exit 0
}
