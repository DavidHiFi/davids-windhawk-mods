<#
.SYNOPSIS
    Installs / rolls back Better Volume Mixer Plus in place of the stock
    Better Volume Mixer Windhawk mod.

.DESCRIPTION
    Modes (default -Audit, changes nothing; the others self-elevate):

    -Audit      Show the stock and fork mod state.
    -Install    Back up both registry keys and the stock files, copy the fork
                source + DLLs into Windhawk, register local@better-volume-mixer-plus
                with the stock mod's settings (Include=windhawk.exe, same as
                upstream), disable the stock better-volume-mixer, and bump
                SettingsChangeTime on both so the engine swaps them live.
    -Rollback   Disable the fork and re-enable the stock mod. Files stay.
    -Uninstall  Remove the fork's key and files and re-enable the stock mod.

    The fork and the stock mod share a tray-icon GUID, so exactly one of them is
    enabled at any time. The mod runs only in its own windhawk.exe -tool-mod
    process; no other process is injected.

.EXAMPLE
    .\2026-09-30-better-volume-mixer-plus-install.ps1
    .\2026-09-30-better-volume-mixer-plus-install.ps1 -Install
    .\2026-09-30-better-volume-mixer-plus-install.ps1 -Rollback
#>
[CmdletBinding()]
param(
    [switch]$Install,
    [switch]$Rollback,
    [switch]$Uninstall,
    [switch]$Audit,
    [string]$Source    = 'H:\Windhawk Configuration\Windhawk\better-volume-mixer-fork\better-volume-mixer-plus.wh.cpp',
    [string]$DllDir    = 'H:\Windhawk Configuration\Windhawk\better-volume-mixer-fork',
    [string]$LogPath   = 'H:\Windhawk Configuration\reports\2026-09-30\better-volume-mixer-plus\install.log',
    [string]$BackupDir = 'H:\Windhawk Configuration\backups\2026-09-30\better-volume-mixer-plus'
)

$ErrorActionPreference = 'Stop'

$ModId       = 'local@better-volume-mixer-plus'
$StockId     = 'better-volume-mixer'
$Windhawk    = 'C:\ProgramData\Windhawk'
$Mods64      = Join-Path $Windhawk 'Engine\Mods\64'
$Mods32      = Join-Path $Windhawk 'Engine\Mods\32'
$ModsSource  = Join-Path $Windhawk 'ModsSource'
$ModsRoot    = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$ModKey      = "$ModsRoot\$ModId"
$StockKey    = "$ModsRoot\$StockId"
$ModKeyReg   = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$ModId"
$StockKeyReg = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$StockId"

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
function Format-Key {
    param([string]$Key)
    $props = Get-ItemProperty -LiteralPath $Key -ErrorAction SilentlyContinue
    if (-not $props) { return '(missing)' }
    ($props.PSObject.Properties | Where-Object { $_.Name -notlike 'PS*' } |
        ForEach-Object { "$($_.Name)=$($_.Value)" }) -join ', '
}
function Set-ModState {
    param([string]$Key, [int]$Disabled)
    $null = New-ItemProperty -LiteralPath $Key -Name Disabled -Value $Disabled -PropertyType DWord -Force
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $null = New-ItemProperty -LiteralPath $Key -Name SettingsChangeTime -Value $now -PropertyType DWord -Force
    $readBack = (Get-ItemProperty -LiteralPath $Key).Disabled
    if ($readBack -ne $Disabled) { throw "read-back mismatch on $Key (Disabled=$readBack)" }
    Write-Log "registry: $Key Disabled=$Disabled SettingsChangeTime=$now (verified)"
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
    $switchName = $mode.Substring(0, 1).ToUpper() + $mode.Substring(1)
    $argString = '-NoProfile -ExecutionPolicy Bypass -File "{0}" -{1}' -f $PSCommandPath, $switchName
    Write-Host "elevating: $argString"
    $p = Start-Process pwsh -Verb RunAs -ArgumentList $argString -PassThru -Wait -WindowStyle Hidden
    exit $p.ExitCode
}

Write-Log "=== better-volume-mixer-plus: mode=$mode ==="
Write-Log ("identity={0} elevated={1}" -f [Security.Principal.WindowsIdentity]::GetCurrent().Name, (Test-Admin))

if ($mode -eq 'audit') {
    Write-Log "$StockKey : $(Format-Key $StockKey)"
    Write-Log "$ModKey : $(Format-Key $ModKey)"
    foreach ($dir in @($Mods64, $Mods32)) {
        $files = Get-ChildItem -LiteralPath $dir -ErrorAction SilentlyContinue |
            Where-Object { $_.Name -like "$ModId*" -or $_.Name -like "$StockId*" }
        Write-Log ("$dir : " + $(if ($files) { ($files.Name -join ', ') } else { '(none)' }))
    }
    $tools = Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" |
        Where-Object { $_.CommandLine -match 'better-volume-mixer' }
    foreach ($t in $tools) { Write-Log "running: pid=$($t.ProcessId) $($t.CommandLine)" }
    exit 0
}

if (-not (Test-Admin)) {
    Write-Log 'not elevated; aborting'
    exit 10
}

if ($mode -eq 'install') {
    if (-not (Test-Path -LiteralPath $Source)) { Write-Log "missing source: $Source"; exit 11 }
    if (-not (Test-Path -LiteralPath $StockKey)) { Write-Log "missing stock key: $StockKey"; exit 11 }
    # local@ belongs to the installed filename and registry key, not @id.
    $idMatch = Select-String -LiteralPath $Source -Pattern '^\s*//\s*@id\s+([0-9a-z-]+)\s*$' | Select-Object -First 1
    if (-not $idMatch -or $idMatch.Matches[0].Groups[1].Value -ne 'better-volume-mixer-plus') {
        Write-Log 'invalid source @id; expected better-volume-mixer-plus without local@'
        exit 12
    }
    $versionMatch = Select-String -LiteralPath $Source -Pattern '^\s*//\s*@version\s+(\S+)' | Select-Object -First 1
    if (-not $versionMatch) { Write-Log 'cannot parse @version'; exit 12 }
    $version = $versionMatch.Matches[0].Groups[1].Value

    $dll64 = Join-Path $DllDir ('{0}_{1}_1_64.dll' -f $ModId, $version)
    $dll32 = Join-Path $DllDir ('{0}_{1}_1_32.dll' -f $ModId, $version)
    foreach ($dll in @($dll64, $dll32)) {
        if (-not (Test-Path -LiteralPath $dll)) { Write-Log "missing DLL: $dll"; exit 13 }
    }

    # Backups: both registry keys (settings included) and the stock source.
    if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null }
    $stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    $stockReg = Join-Path $BackupDir "stock-mod-key-before-$stamp.reg"
    $null = & reg.exe export $StockKeyReg $stockReg /y 2>&1
    Write-Log "backup: $StockKeyReg -> $stockReg (exit=$LASTEXITCODE)"
    $writableReg = Join-Path $BackupDir "stock-mod-writable-before-$stamp.reg"
    $null = & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\$StockId" $writableReg /y 2>&1
    Write-Log "backup: ModsWritable\$StockId -> $writableReg (exit=$LASTEXITCODE)"
    $forkReg = $null
    if (Test-Path -LiteralPath $ModKey) {
        $forkReg = Join-Path $BackupDir "fork-mod-key-before-$stamp.reg"
        $null = & reg.exe export $ModKeyReg $forkReg /y 2>&1
        Write-Log "backup: $ModKeyReg -> $forkReg (exit=$LASTEXITCODE)"
    }
    $stockSource = Join-Path $ModsSource "$StockId.wh.cpp"
    if (Test-Path -LiteralPath $stockSource) {
        Copy-Item -LiteralPath $stockSource -Destination (Join-Path $BackupDir "$StockId.wh.cpp") -Force
    }
    $stockBefore = Format-Key $StockKey
    Write-Log "stock before: $stockBefore"

    Copy-Item -LiteralPath $Source -Destination (Join-Path $ModsSource "$ModId.wh.cpp") -Force
    Write-Log "copied source -> $ModsSource\$ModId.wh.cpp"

    # The engine keeps loaded DLLs mapped, so each build gets a fresh revision
    # number and LibraryFileName points at it.
    $rev = 1
    if (Test-Path -LiteralPath $ModKey) {
        $cur = (Get-ItemProperty -LiteralPath $ModKey).LibraryFileName
        if ($cur -match '_(\d+)\.dll$') { $rev = [int]$Matches[1] + 1 }
    }
    $libName = '{0}_{1}_{2}.dll' -f $ModId, $version, $rev
    Copy-Item -LiteralPath $dll64 -Destination (Join-Path $Mods64 $libName) -Force
    Copy-Item -LiteralPath $dll32 -Destination (Join-Path $Mods32 $libName) -Force
    $hash64 = (Get-FileHash -LiteralPath (Join-Path $Mods64 $libName) -Algorithm SHA256).Hash
    $hash32 = (Get-FileHash -LiteralPath (Join-Path $Mods32 $libName) -Algorithm SHA256).Hash
    Write-Log "installed: $Mods64\$libName sha256=$hash64 (rev=$rev)"
    Write-Log "installed: $Mods32\$libName sha256=$hash32"

    # Stock off first: the two share a tray GUID.
    Set-ModState -Key $StockKey -Disabled 1

    $freshKey = -not (Test-Path -LiteralPath $ModKey)
    if ($freshKey) { $null = New-Item -Path $ModKey -Force }
    $null = New-ItemProperty -LiteralPath $ModKey -Name LibraryFileName -Value $libName -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Include -Value 'windhawk.exe' -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Exclude -Value '' -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Architecture -Value '' -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Version -Value $version -PropertyType String -Force
    if ($freshKey) {
        $null = & reg.exe copy "$StockKeyReg\Settings" "$ModKeyReg\Settings" /s /f 2>&1
        Write-Log "settings: copied stock Settings -> fork (exit=$LASTEXITCODE)"
    } else {
        Write-Log 'settings: fork key existed; kept its settings'
    }
    Set-ModState -Key $ModKey -Disabled 0
    Write-Log "fork after: $(Format-Key $ModKey)"

    $receipt = [ordered]@{
        mode          = 'install'
        timestamp     = (Get-Date -Format o)
        identity      = [Security.Principal.WindowsIdentity]::GetCurrent().Name
        mod_id        = $ModId
        version       = $version
        revision      = $rev
        include       = 'windhawk.exe'
        library       = $libName
        dll64_sha256  = $hash64
        dll32_sha256  = $hash32
        source        = "$ModsSource\$ModId.wh.cpp"
        source_sha256 = (Get-FileHash -LiteralPath (Join-Path $ModsSource "$ModId.wh.cpp") -Algorithm SHA256).Hash
        stock_mod     = $StockId
        stock_before  = $stockBefore
        stock_after   = 'Disabled=1'
        backups       = @($stockReg, $writableReg, $forkReg) | Where-Object { $_ }
        rollback      = "$PSCommandPath -Rollback"
        log           = $LogPath
    }
    $receipt | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $BackupDir "install-receipt-$stamp.json") -Encoding UTF8
    Write-Log 'INSTALL OK'
    exit 0
}

if ($mode -eq 'rollback') {
    if (Test-Path -LiteralPath $ModKey) { Set-ModState -Key $ModKey -Disabled 1 }
    else { Write-Log "$ModKey missing" }
    if (Test-Path -LiteralPath $StockKey) { Set-ModState -Key $StockKey -Disabled 0 }
    Write-Log 'ROLLBACK OK'
    exit 0
}

if ($mode -eq 'uninstall') {
    if (Test-Path -LiteralPath $ModKey) {
        Set-ModState -Key $ModKey -Disabled 1
        Remove-Item -LiteralPath $ModKey -Recurse -Force
        Write-Log "registry: removed $ModKey"
    }
    if (Test-Path -LiteralPath $StockKey) { Set-ModState -Key $StockKey -Disabled 0 }
    # Loaded DLLs may still be mapped until the tool process exits; ignore failures.
    Get-ChildItem -LiteralPath $Mods64, $Mods32 -Filter "$ModId*" -ErrorAction SilentlyContinue |
        Remove-Item -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath (Join-Path $ModsSource "$ModId.wh.cpp") -Force -ErrorAction SilentlyContinue
    Write-Log 'UNINSTALL OK'
    exit 0
}
