<#
.SYNOPSIS
    Deploys the local @alt-snap-drag Windhawk mod and swaps it in for the stock
    alt-drag mod and the AltSnap auto-start.

.DESCRIPTION
    Modes (default -Audit, which changes nothing):

    -Audit      Print the current Windhawk mod and AltSnap task state.
    -Install    Back up first, then:
                  1. copy the source and the 64/32-bit DLLs into Windhawk,
                  2. register local@alt-snap-drag enabled for all processes,
                     with settings matching the user's AltSnap.ini,
                  3. disable the stock alt-drag mod,
                  4. disable the AltSnap auto-start scheduled task,
                  5. restart the Windhawk engine and write a receipt.
                Requires an elevated session (writes HKLM and ProgramData).
    -Rollback   Re-enable alt-drag and the AltSnap task, disable the fork,
                restart the engine. Requires elevation.

    Changes, originals and hashes go into
    backups\2026-09-28\altsnap-fork\install-receipt.json and the log.
    Rollback procedure is written into notes\2026-09-28-altsnap-windhawk-fork.md.
#>
[CmdletBinding()]
param(
    [switch]$Install,
    [switch]$Rollback,
    [switch]$Audit,
    [string]$Workspace = 'H:\System Configuration',
    [string]$LogPath   = 'H:\System Configuration\reports\2026-09-28\altsnap-windhawk-install.log',
    [string]$BackupDir = 'H:\System Configuration\backups\2026-09-28\altsnap-fork'
)

$ErrorActionPreference = 'Stop'

$ModId       = 'local@alt-snap-drag'
$ModVer      = '1.2.2'
$LibName     = 'local@alt-snap-drag_1.2.2_1.dll'
$StockId     = 'alt-drag'
$TaskName    = 'AltSnap'
$Windhawk    = 'C:\ProgramData\Windhawk'
$Mods64      = Join-Path $Windhawk 'Engine\Mods\64'
$Mods32      = Join-Path $Windhawk 'Engine\Mods\32'
$ModsSource  = Join-Path $Windhawk 'ModsSource'
$ModKey      = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$ModId"
$StockKey    = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$StockId"
$WindhawkExe = 'C:\Program Files\Windhawk\windhawk.exe'
$Src64       = Join-Path $Workspace 'Windhawk\altsnap-fork\local@alt-snap-drag_1.2.2_1_64.dll'
$Src32       = Join-Path $Workspace 'Windhawk\altsnap-fork\local@alt-snap-drag_1.2.2_1_32.dll'
$SrcCpp      = Join-Path $Workspace 'Windhawk\altsnap-fork\alt-snap.wh.cpp'

# The fork's source defaults, except dragWindowsWithoutTitleBar which mirrors
# the previous alt-drag configuration on this machine. The hotkey* values
# mirror the user's AltSnap.ini [KBShortcuts]: Maximize=326 (Alt+F),
# Minimize=333 (Alt+M), Close=1361 (Alt+Shift+Q); Menu/Lower/Kill are unbound
# there, so they stay unbound here.
$ModSettings = @(
    @{ Name = 'moveTrigger.button';        Value = 'left';      Type = 'String' }
    @{ Name = 'moveTrigger.ctrl';          Value = 0;           Type = 'DWord' }
    @{ Name = 'moveTrigger.alt';           Value = 1;           Type = 'DWord' }
    @{ Name = 'moveTrigger.shift';         Value = 0;           Type = 'DWord' }
    @{ Name = 'moveTrigger.win';           Value = 0;           Type = 'DWord' }
    @{ Name = 'moveTrigger.delay';         Value = 0;           Type = 'DWord' }
    @{ Name = 'sizeTrigger.button';        Value = 'right';     Type = 'String' }
    @{ Name = 'sizeTrigger.ctrl';          Value = 0;           Type = 'DWord' }
    @{ Name = 'sizeTrigger.alt';           Value = 1;           Type = 'DWord' }
    @{ Name = 'sizeTrigger.shift';         Value = 0;           Type = 'DWord' }
    @{ Name = 'sizeTrigger.win';           Value = 0;           Type = 'DWord' }
    @{ Name = 'sizeTrigger.delay';         Value = 0;           Type = 'DWord' }
    @{ Name = 'dragWindowsWithoutTitleBar'; Value = 1;          Type = 'DWord' }
    @{ Name = 'middleAction';              Value = 'menu';      Type = 'String' }
    @{ Name = 'rightClickAction';          Value = 'maximize';  Type = 'String' }
    @{ Name = 'x1Action';                  Value = 'none';      Type = 'String' }
    @{ Name = 'x2Action';                  Value = 'none';      Type = 'String' }
    @{ Name = 'leftDoubleAction';          Value = 'none';      Type = 'String' }
    @{ Name = 'middleDoubleAction';        Value = 'none';      Type = 'String' }
    @{ Name = 'rightDoubleAction';         Value = 'none';      Type = 'String' }
    @{ Name = 'hotkeyMaximize';            Value = 'Alt+F';       Type = 'String' }
    @{ Name = 'hotkeyMinimize';            Value = 'Alt+M';       Type = 'String' }
    @{ Name = 'hotkeyClose';               Value = 'Alt+Shift+Q'; Type = 'String' }
    @{ Name = 'hotkeyMenu';                Value = '';          Type = 'String' }
    @{ Name = 'hotkeyTopmost';             Value = '';          Type = 'String' }
    @{ Name = 'hotkeyLower';               Value = '';          Type = 'String' }
    @{ Name = 'hotkeyCenter';              Value = '';          Type = 'String' }
    @{ Name = 'hotkeySideSnap';            Value = '';          Type = 'String' }
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
function Get-RegProps {
    param([string]$Path)
    $key = Get-Item -LiteralPath $Path -ErrorAction SilentlyContinue
    if (-not $key) { return $null }
    foreach ($n in $key.Property) {
        [pscustomobject]@{ Name = $n; Kind = $key.GetValueKind($n); Value = $key.GetValue($n) }
    }
}
function Show-State {
    Write-Log '--- current state ---'
    Write-Log ("alt-drag key: " + (($ModId, 'alt-drag' | ForEach-Object {
        $p = Get-RegProps "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$_"
        if ($p) { "$_ : " + (($p | ForEach-Object { "$($_.Name)=$($_.Value)" }) -join ', ') } else { "$_ : (missing)" }
    }) -join ' | '))
    $ms = Get-RegProps "$ModKey\Settings"
    Write-Log ("local@alt-snap-drag settings: " + $(if ($ms) { (($ms | ForEach-Object { "$($_.Name)=$($_.Value)" }) -join ', ') } else { '(none)' }))
    foreach ($dir in @($Mods64, $Mods32)) {
        $files = Get-ChildItem -LiteralPath $dir -Filter 'local@alt-snap-drag*' -ErrorAction SilentlyContinue
        Write-Log ("$dir : " + $(if ($files) { ($files.Name -join ', ') } else { '(no fork dlls)' }))
    }
    $task = Get-ScheduledTask -TaskName $TaskName -ErrorAction SilentlyContinue
    Write-Log ("task $TaskName : " + $(if ($task) { $task.State } else { '(missing)' }))
    $alt = Get-Process -Name AltSnap -ErrorAction SilentlyContinue
    Write-Log ("AltSnap.exe running: " + [bool]$alt)
}
function Restart-Engine {
    Write-Log 'restarting Windhawk engine'
    Start-Process -FilePath $WindhawkExe -ArgumentList '-restart' -WindowStyle Hidden
    Start-Sleep -Seconds 5
    $alive = Get-Process -Name windhawk -ErrorAction SilentlyContinue
    Write-Log ("windhawk processes after restart: " + @($alive).Count)
}

if (($Install -and $Rollback) -or ($Install -and $Audit) -or ($Rollback -and $Audit)) {
    Write-Log 'use exactly one of -Audit, -Install, -Rollback'
    exit 2
}
if (-not ($Install -or $Rollback)) { $Audit = $true }

Write-Log "=== altsnap-windhawk install script: mode=$($(if ($Install) {'install'} elseif ($Rollback) {'rollback'} else {'audit'})) ==="
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
    foreach ($p in @($Src64, $Src32, $SrcCpp)) {
        if (-not (Test-Path -LiteralPath $p)) { Write-Log "missing source: $p"; exit 11 }
    }
    $src64Hash = (Get-FileHash -LiteralPath $Src64 -Algorithm SHA256).Hash
    $src32Hash = (Get-FileHash -LiteralPath $Src32 -Algorithm SHA256).Hash

    # 1. backups
    if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null }
    $regFile = Join-Path $BackupDir ('windhawk-mods-before-{0}.reg' -f (Get-Date -Format 'yyyyMMdd-HHmmss'))
    $null = & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods' $regFile /y 2>&1
    Write-Log "backup: reg export -> $regFile (exit=$LASTEXITCODE)"
    $stockBefore = Get-RegProps $StockKey
    $stockBeforeJson = $stockBefore | ConvertTo-Json -Compress
    Write-Log "alt-drag before: $stockBeforeJson"
    $taskBefore = $null
    $task = Get-ScheduledTask -TaskName $TaskName -ErrorAction SilentlyContinue
    if ($task) {
        $taskBefore = $task.State.ToString()
        $xmlFile = Join-Path $BackupDir 'alt-snap-scheduled-task.xml'
        Export-ScheduledTask -TaskName $TaskName | Set-Content -LiteralPath $xmlFile -Encoding Unicode
        Write-Log "backup: task xml -> $xmlFile (state=$taskBefore)"
    } else {
        Write-Log 'AltSnap task not present'
    }
    if (Get-Process -Name AltSnap -ErrorAction SilentlyContinue) {
        Write-Log 'WARNING: AltSnap.exe is running; it will conflict with the fork until closed'
    }

    # 2. source and DLLs
    Copy-Item -LiteralPath $SrcCpp -Destination (Join-Path $ModsSource "$ModId.wh.cpp") -Force
    Write-Log "copied source -> $ModsSource\$ModId.wh.cpp"
    # The engine keeps previously loaded DLLs mapped, so old files may be
    # locked; the cleanup is best-effort and the new revision is what the
    # registry points at.
    Get-ChildItem -LiteralPath $Mods64 -Filter 'local@alt-snap-drag*' -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
    Get-ChildItem -LiteralPath $Mods32 -Filter 'local@alt-snap-drag*' -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
    Copy-Item -LiteralPath $Src64 -Destination (Join-Path $Mods64 $LibName) -Force
    Copy-Item -LiteralPath $Src32 -Destination (Join-Path $Mods32 $LibName) -Force
    $dst64Hash = (Get-FileHash -LiteralPath (Join-Path $Mods64 $LibName) -Algorithm SHA256).Hash
    $dst32Hash = (Get-FileHash -LiteralPath (Join-Path $Mods32 $LibName) -Algorithm SHA256).Hash
    Write-Log "installed: $Mods64\$LibName sha256=$dst64Hash"
    Write-Log "installed: $Mods32\$LibName sha256=$dst32Hash"

    # 3. registry: enable the fork for all processes, with settings
    if (-not (Test-Path -LiteralPath $ModKey)) { $null = New-Item -Path $ModKey -Force }
    $null = New-ItemProperty -LiteralPath $ModKey -Name LibraryFileName -Value $LibName -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Disabled -Value 0 -PropertyType DWord -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Include -Value '*' -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Exclude -Value '' -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Architecture -Value '' -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name Version -Value $ModVer -PropertyType String -Force
    $null = New-ItemProperty -LiteralPath $ModKey -Name SettingsChangeTime -Value ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -PropertyType DWord -Force
    Write-Log "registry: $ModKey enabled (Include=*, LibraryFileName=$LibName)"
    $settingsKey = Join-Path $ModKey 'Settings'
    if (-not (Test-Path -LiteralPath $settingsKey)) { $null = New-Item -Path $settingsKey -Force }
    foreach ($s in $ModSettings) {
        $null = New-ItemProperty -LiteralPath $settingsKey -Name $s.Name -Value $s.Value -PropertyType $s.Type -Force
    }
    Write-Log "registry: $settingsKey written ($($ModSettings.Count) values)"

    # 4. disable the stock alt-drag mod
    $null = New-ItemProperty -LiteralPath $StockKey -Name Disabled -Value 1 -PropertyType DWord -Force
    Write-Log 'registry: alt-drag Disabled=1 (was 0)'

    # 5. disable AltSnap auto-start (app stays installed)
    if ($task -and $task.State -ne 'Disabled') {
        Disable-ScheduledTask -TaskName $TaskName | Out-Null
        Write-Log "task: $TaskName disabled (was $taskBefore)"
    }

    # 6. restart engine and receipt
    Restart-Engine
    $taskAfter = (Get-ScheduledTask -TaskName $TaskName -ErrorAction SilentlyContinue).State.ToString()
    $receipt = [ordered]@{
        mode                 = 'install'
        timestamp            = (Get-Date -Format o)
        identity             = [Security.Principal.WindowsIdentity]::GetCurrent().Name
        mod_id               = $ModId
        version              = $ModVer
        source_dll_64_sha256 = $src64Hash
        source_dll_32_sha256 = $src32Hash
        installed_64         = "$Mods64\$LibName"
        installed_64_sha256  = $dst64Hash
        installed_32         = "$Mods32\$LibName"
        installed_32_sha256  = $dst32Hash
        source_copied_to     = "$ModsSource\$ModId.wh.cpp"
        mod_key_enabled      = $true
        mod_settings         = $ModSettings
        alt_drag_before      = $stockBefore
        alt_drag_after_disabled = 1
        alt_snap_task_before = $taskBefore
        alt_snap_task_after  = $taskAfter
        registry_backup      = $regFile
        log                  = $LogPath
    }
    $receiptFile = Join-Path $BackupDir 'install-receipt.json'
    $receipt | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $receiptFile -Encoding UTF8
    Write-Log "receipt: $receiptFile"
    Write-Log 'INSTALL OK'
    exit 0
}

if ($Rollback) {
    # re-enable the stock alt-drag mod
    if (Test-Path -LiteralPath $StockKey) {
        $null = New-ItemProperty -LiteralPath $StockKey -Name Disabled -Value 0 -PropertyType DWord -Force
        Write-Log 'registry: alt-drag Disabled=0'
    } else {
        Write-Log 'alt-drag key missing; cannot re-enable'
    }
    # disable the fork
    if (Test-Path -LiteralPath $ModKey) {
        $null = New-ItemProperty -LiteralPath $ModKey -Name Disabled -Value 1 -PropertyType DWord -Force
        Write-Log "registry: $ModId Disabled=1"
    } else {
        Write-Log "$ModId key missing; nothing to disable"
    }
    # re-enable AltSnap auto-start
    $task = Get-ScheduledTask -TaskName $TaskName -ErrorAction SilentlyContinue
    if ($task -and $task.State -ne 'Ready') {
        Enable-ScheduledTask -TaskName $TaskName | Out-Null
        Write-Log "task: $TaskName enabled (was $($task.State))"
    }
    Restart-Engine
    $receipt = [ordered]@{
        mode      = 'rollback'
        timestamp = (Get-Date -Format o)
        identity  = [Security.Principal.WindowsIdentity]::GetCurrent().Name
        note      = 'alt-drag re-enabled, fork disabled, AltSnap task enabled; fork files left in place'
        log       = $LogPath
    }
    $receiptFile = Join-Path $BackupDir 'rollback-receipt.json'
    $receipt | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $receiptFile -Encoding UTF8
    Write-Log "receipt: $receiptFile"
    Write-Log 'ROLLBACK OK'
    exit 0
}
