<#
.SYNOPSIS
    Installs / rolls back the local translucent-flyouts Windhawk mod.

.DESCRIPTION
    Modes (default -Audit, changes nothing; -Install/-Rollback self-elevate):

    -Audit      Show current mod state (no elevation needed).
    -Install    Back up the Windhawk mods key, copy source + DLLs into Windhawk,
                register local@translucent-flyouts and bump SettingsChangeTime
                so the engine reloads mods live (NO engine restart - that
                restarts explorer and breaks the live T3 Code GUI).
    -Rollback   Set the mod Disabled=1 and bump the change time; files stay.
    -Uninstall  Remove the registry key and installed files.

    DLL architecture: x64 is required; x86 is copied when present. The version
    is parsed from the mod source header.

.EXAMPLE
    .\2026-09-28-translucent-flyouts-install.ps1 -Install
    .\2026-09-28-translucent-flyouts-install.ps1 -Install -Include explorer.exe
#>
[CmdletBinding()]
param(
    [switch]$Install,
    [switch]$Rollback,
    [switch]$Uninstall,
    [switch]$Audit,
    [string]$Include  = '*',
    [string]$Exclude  = 'discord*.exe|Voicemeeter*.exe|Matrix*.exe|Stream Deck*.exe|dwm.exe',
    [string]$Source   = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts\translucent-flyouts.wh.cpp',
    [string]$DllDir   = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts',
    [string]$LogPath  = 'H:\Windhawk Configuration\reports\2026-09-28\translucent-flyouts-install.log',
    [string]$BackupDir = 'H:\Windhawk Configuration\backups\2026-09-28\translucent-flyouts'
)

$ErrorActionPreference = 'Stop'

$ModId      = 'local@translucent-flyouts'
$Windhawk   = 'C:\ProgramData\Windhawk'
$Mods64     = Join-Path $Windhawk 'Engine\Mods\64'
$Mods32     = Join-Path $Windhawk 'Engine\Mods\32'
$ModsSource = Join-Path $Windhawk 'ModsSource'
$ModKey     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$ModId"

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

$mode = if ($Install) { 'install' } elseif ($Rollback) { 'rollback' } elseif ($Uninstall) { 'uninstall' } else { 'audit' }
if (@($Install, $Rollback, $Uninstall, $Audit).Where({ $_ }).Count -gt 1) {
    Write-Log 'use at most one mode switch'
    exit 2
}
trap {
    $msg = $_ | Out-String
    Write-Log "ERROR: $msg"
    exit 99
}

# Self-elevate for mutating modes: one pre-quoted argument string (arrays with
# paths containing spaces are mangled by Start-Process -Verb RunAs).
if ($mode -ne 'audit' -and -not (Test-Admin)) {
    $scriptPath = $PSCommandPath
    $switchName = $mode.Substring(0, 1).ToUpper() + $mode.Substring(1)
    $argString = '-NoProfile -ExecutionPolicy Bypass -File "{0}" -{1}' -f $scriptPath, $switchName
    if ($mode -eq 'install') { $argString += (' -Include "{0}" -Exclude "{1}"' -f $Include, $Exclude) }
    Write-Host "elevating: $argString"
    $p = Start-Process pwsh -Verb RunAs -ArgumentList $argString -PassThru -Wait -WindowStyle Hidden
    exit $p.ExitCode
}

Write-Log "=== translucent-flyouts: mode=$mode ==="
Write-Log ("identity={0} elevated={1}" -f [Security.Principal.WindowsIdentity]::GetCurrent().Name, (Test-Admin))

if ($mode -eq 'audit') {
    $props = Get-ItemProperty -LiteralPath $ModKey -ErrorAction SilentlyContinue
    if ($props) {
        Write-Log ("$ModKey : " + (($props.PSObject.Properties | Where-Object { $_.Name -notlike 'PS*' } | ForEach-Object { "$($_.Name)=$($_.Value)" }) -join ', '))
    } else {
        Write-Log "$ModKey : (missing)"
    }
    foreach ($dir in @($Mods64, $Mods32)) {
        $files = Get-ChildItem -LiteralPath $dir -Filter 'local@translucent-flyouts*' -ErrorAction SilentlyContinue
        Write-Log ("$dir : " + $(if ($files) { ($files.Name -join ', ') } else { '(none)' }))
    }
    exit 0
}

if (-not (Test-Admin)) {
    Write-Log 'not elevated; aborting'
    exit 10
}

if ($mode -eq 'install') {
    if (-not (Test-Path -LiteralPath $Source)) { Write-Log "missing source: $Source"; exit 11 }
    $versionMatch = Select-String -LiteralPath $Source -Pattern '^\s*//\s*@version\s+(\S+)' | Select-Object -First 1
    if (-not $versionMatch) { Write-Log 'cannot parse @version'; exit 12 }
    $version = $versionMatch.Matches[0].Groups[1].Value

    $dll64 = Join-Path $DllDir ('{0}_{1}_1_64.dll' -f $ModId, $version)
    $dll32 = Join-Path $DllDir ('{0}_{1}_1_32.dll' -f $ModId, $version)
    if (-not (Test-Path -LiteralPath $dll64)) { Write-Log "missing DLL: $dll64"; exit 13 }

    if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null }
    $regFile = Join-Path $BackupDir ('windhawk-mods-before-{0}.reg' -f (Get-Date -Format 'yyyyMMdd-HHmmss'))
    if (-not (Test-Path -LiteralPath $ModKey)) {
        $null = & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods' $regFile /y 2>&1
        Write-Log "backup: reg export -> $regFile (exit=$LASTEXITCODE)"
    } else {
        $null = & reg.exe export ("HKLM\SOFTWARE\Windhawk\Engine\Mods\{0}" -f 'local@translucent-flyouts') (Join-Path $BackupDir 'mod-key-before.reg') /y 2>&1
        Write-Log "backup: existing mod key exported"
    }

    Copy-Item -LiteralPath $Source -Destination (Join-Path $ModsSource "$ModId.wh.cpp") -Force
    Write-Log "copied source -> $ModsSource\$ModId.wh.cpp"

    # The engine keeps loaded DLLs mapped, so an existing revision with the same
    # name cannot be overwritten; install each build under a fresh revision
    # number and let the registry point at it. LibraryFileName is the exact file
    # name inside Engine\Mods\{64,32} per architecture (no arch suffix), like
    # every installed mod on this machine.
    $rev = 1
    if (Test-Path -LiteralPath $ModKey) {
        $cur = (Get-ItemProperty -LiteralPath $ModKey).LibraryFileName
        if ($cur -match '_(?:(\d+)(?:_(?:64|32))?)\.dll$') { $rev = [int]$Matches[1] + 1 }
    }
    $libName = '{0}_{1}_{2}.dll' -f $ModId, $version, $rev
    Copy-Item -LiteralPath $dll64 -Destination (Join-Path $Mods64 $libName) -Force
    $hash64 = (Get-FileHash -LiteralPath (Join-Path $Mods64 $libName) -Algorithm SHA256).Hash
    Write-Log "installed: $Mods64\$libName sha256=$hash64 (rev=$rev)"
    if (Test-Path -LiteralPath $dll32) {
        Copy-Item -LiteralPath $dll32 -Destination (Join-Path $Mods32 $libName) -Force
        $hash32 = (Get-FileHash -LiteralPath (Join-Path $Mods32 $libName) -Algorithm SHA256).Hash
        Write-Log "installed: $Mods32\$libName sha256=$hash32"
    } else {
        Write-Log 'x86 DLL absent; 32-bit processes will not be injected this revision'
    }

    if (-not (Test-Path -LiteralPath $ModKey)) { $null = New-Item -Path $ModKey -Force }
    $null = New-ItemProperty -LiteralPath $ModKey -Name LibraryFileName -Value $libName -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Disabled -Value 0 -PropertyType DWord -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Include -Value $Include -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Exclude -Value $Exclude -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Architecture -Value '' -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Version -Value $version -PropertyType String -Force
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $null = New-ItemProperty -LiteralPath $ModKey -Name SettingsChangeTime -Value $now -PropertyType DWord -Force
    Write-Log "registry: $ModKey enabled (Include=$Include, LibraryFileName=$libName, SettingsChangeTime=$now)"

    $receipt = [ordered]@{
        mode        = 'install'
        timestamp   = (Get-Date -Format o)
        identity    = [Security.Principal.WindowsIdentity]::GetCurrent().Name
        mod_id      = $ModId
        version     = $version
        revision    = $rev
        include     = $Include
        exclude     = $Exclude
        dll_source  = $dll64
        dll_sha256  = $hash64
        installed   = "$Mods64\$libName"
        source      = "$ModsSource\$ModId.wh.cpp"
        reg_backup  = $regFile
        log         = $LogPath
    }
    $receipt | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $BackupDir 'install-receipt.json') -Encoding UTF8
    Write-Log 'INSTALL OK'
    exit 0
}

if ($mode -eq 'rollback') {
    if (Test-Path -LiteralPath $ModKey) {
        $null = New-ItemProperty -LiteralPath $ModKey -Name Disabled -Value 1 -PropertyType DWord -Force
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        $null = New-ItemProperty -LiteralPath $ModKey -Name SettingsChangeTime -Value $now -PropertyType DWord -Force
        Write-Log "registry: $ModId Disabled=1 (files kept)"
    } else {
        Write-Log "$ModKey missing; nothing to roll back"
    }
    Write-Log 'ROLLBACK OK'
    exit 0
}

if ($mode -eq 'uninstall') {
    if (Test-Path -LiteralPath $ModKey) {
        Remove-Item -LiteralPath $ModKey -Recurse -Force
        Write-Log "registry: removed $ModKey"
    }
    Get-ChildItem -LiteralPath $Mods64 -Filter 'local@translucent-flyouts*' -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
    Get-ChildItem -LiteralPath $Mods32 -Filter 'local@translucent-flyouts*' -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath (Join-Path $ModsSource "$ModId.wh.cpp") -Force -ErrorAction SilentlyContinue
    Write-Log 'UNINSTALL OK'
    exit 0
}
