<#
.SYNOPSIS
Windhawk 2.0.0-alpha.6 -> 2.0.0-alpha.7 update. Started elevated and detached by
scripts\2026-10-11-windhawk-2a7-launch.ps1. Do not run it from a T3 Code shell.

  -Audit     print the current state, change nothing
  -Backup    registry export and tree copies (robocopy skips identical files, so re-running is cheap)
  -Install   wait for T3 Code to close, back up, stop the Windhawk service and processes, run the
             offline installer silently, verify, start the service and tray, restart Explorer, write receipt
  -Rollback  stop, mirror-restore Program Files and ProgramData from the backup, import the registry, start

Each phase appends to backups\2026-10-11\windhawk-2a7-update\phase-log.txt. Failures also write
<phase>-error.txt there. Markers: install-complete, install-cancelled, install-timeout, install-failed,
rollback-complete, rollback-failed. Create the file CANCEL in the backup folder to stop a waiting install.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Backup,
    [switch]$Install,
    [switch]$Rollback
)

$ErrorActionPreference = 'Stop'
$root       = 'H:\Windhawk Configuration'
$bdir       = "$root\backups\2026-10-11\windhawk-2a7-update"
$installer  = "$bdir\installer\windhawk_setup_offline.exe"
$instSha    = 'B8208BC9189568BDA811A1CF883C4F6399077D619899D2205CB2DA25C74E1FA3'
$pf         = 'C:\Program Files\Windhawk'
$pfBak      = "$bdir\ProgramFiles-Windhawk"
$pd         = 'C:\ProgramData\Windhawk'
$pdBak      = "$bdir\ProgramData-Windhawk"
$regBak     = "$bdir\windhawk-registry-HKLM.reg"
$manifestF  = "$bdir\backup-manifest.json"
$receipt    = "$bdir\receipt.json"
$phaseLog   = "$bdir\phase-log.txt"
$cancelFile = "$bdir\CANCEL"
$t3Pattern  = 'T3 Code*'
$t3WaitSec  = 21600
$fromVer    = '2.0.0-alpha.6'
$toVer      = '2.0.0-alpha.7'
$stylerKey  = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$settingsKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Settings'

function Log([string]$Message) {
    $line = '[{0}] {1}' -f (Get-Date -Format 'HH:mm:ss'), $Message
    Write-Host $line
    Add-Content -Path $phaseLog -Value $line -Encoding UTF8
}

function Save-PhaseError([string]$Phase, $Err) {
    $file = "$bdir\$Phase-error.txt"
    "$((Get-Date -Format 'HH:mm:ss')) $Phase" | Set-Content $file -Encoding UTF8
    $Err | Out-String | Add-Content $file -Encoding UTF8
}

function Copy-Tree([string]$Src, [string]$Dst, [bool]$Strict) {
    if (-not (Test-Path $Src)) { Log "skipped missing $Src"; return }
    $rclog = "$bdir\robocopy-" + ($Dst.Substring($bdir.Length + 1) -replace '[\\/]', '_') + '.log'
    & robocopy $Src $Dst /E /XJ /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File $rclog -Encoding UTF8
    $code = $LASTEXITCODE
    if ($code -ge 8) {
        if ($Strict) { throw "robocopy $Src failed: exit $code (log: $rclog)" }
        Log ("WARNING: {0} exit {1}; locked or volatile files skipped ({2})" -f $Src, $code, $rclog)
    } else {
        Log ("copied {0} (robocopy exit {1})" -f $Src, $code)
    }
}

function Get-VersionOf([string]$Exe) {
    return (Get-Item $Exe -ErrorAction SilentlyContinue).VersionInfo.FileVersion
}

function Get-ModKeyCount {
    $k = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
    if (Test-Path $k) { return @(Get-ChildItem $k).Count }
    return 0
}

function Get-EnginePath {
    $line = Get-Content "$pf\windhawk.ini" | Where-Object { $_ -match '^EnginePath=' } | Select-Object -First 1
    return ($line -replace '^EnginePath=', '').Trim()
}

function Get-StylerState {
    if (-not (Test-Path $stylerKey)) { return $null }
    $p = Get-ItemProperty $stylerKey
    return [ordered]@{ Version = $p.Version; Include = $p.Include; Disabled = $p.Disabled; LibraryFileName = $p.LibraryFileName }
}

function Get-EngineSettings {
    $p = Get-ItemProperty $settingsKey
    return [ordered]@{ Include = $p.Include; Exclude = $p.Exclude; InjectIntoGames = $p.InjectIntoGames }
}

function Invoke-Backup {
    try {
        if (-not (Test-Path $installer)) { throw "installer missing: $installer" }
        if ((Get-FileHash $installer -Algorithm SHA256).Hash -ne $instSha) { throw 'installer hash mismatch' }
        New-Item -ItemType Directory -Force -Path $bdir, $pdBak, "$pdBak\Engine" | Out-Null

        Log 'exporting HKLM\SOFTWARE\Windhawk'
        & reg.exe export 'HKLM\SOFTWARE\Windhawk' $regBak /y | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "reg export failed: $LASTEXITCODE" }

        Log 'copying Program Files\Windhawk (strict)'
        Copy-Tree $pf $pfBak $true
        if ((Get-FileHash "$pf\windhawk.exe").Hash -ne (Get-FileHash "$pfBak\windhawk.exe").Hash) {
            throw 'Program Files backup failed the hash check on windhawk.exe'
        }

        Log 'copying ProgramData\Windhawk'
        Copy-Tree "$pd\ModsSource"          "$pdBak\ModsSource"          $true
        Copy-Tree "$pd\Engine\Mods"         "$pdBak\Engine\Mods"         $false
        Copy-Tree "$pd\Engine\ModsWritable" "$pdBak\Engine\ModsWritable" $false
        Copy-Tree "$pd\Engine\Symbols"      "$pdBak\Engine\Symbols"      $false
        Copy-Tree "$pd\UIData"              "$pdBak\UIData"              $false
        Copy-Tree "$pd\EditorWorkspace"     "$pdBak\EditorWorkspace"     $false
        Get-ChildItem $pd -File | Copy-Item -Destination $pdBak -Force
        Get-ChildItem "$pd\Engine" -File | Copy-Item -Destination "$pdBak\Engine" -Force

        $manifest = [ordered]@{
            when          = (Get-Date -Format 'o')
            version       = (Get-VersionOf "$pf\windhawk.exe")
            enginePath    = (Get-EnginePath)
            modKeys       = (Get-ModKeyCount)
            registryBytes = (Get-Item $regBak).Length
            styler        = (Get-StylerState)
            engine        = (Get-EngineSettings)
        }
        $manifest | ConvertTo-Json -Depth 4 | Set-Content $manifestF -Encoding UTF8
        Log 'backup complete'
    } catch {
        Save-PhaseError 'backup' $_
        throw
    }
}

function Wait-ForT3Close {
    $deadline = (Get-Date).AddSeconds($t3WaitSec)
    $announced = $false
    while (Get-Process -Name $t3Pattern -ErrorAction SilentlyContinue) {
        if (Test-Path $cancelFile) { return 'cancelled' }
        if ((Get-Date) -gt $deadline) { return 'timeout' }
        if (-not $announced) { Log 'waiting: T3 Code is open; the engine stays up until it closes'; $announced = $true }
        Start-Sleep -Seconds 5
    }
    if (Test-Path $cancelFile) { return 'cancelled' }
    return 'clear'
}

function Stop-WindhawkEngine {
    Log 'stopping the Windhawk service and every Windhawk process'
    Stop-Service -Name Windhawk -Force -ErrorAction SilentlyContinue
    $p = Start-Process -FilePath "$pf\windhawk.exe" -ArgumentList '-exit' -WindowStyle Hidden -PassThru
    if (-not $p.WaitForExit(20000)) {
        Log 'windhawk -exit did not return within 20 s; killing it'
        try { $p.Kill() } catch { }
    }
    Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
    $deadline = (Get-Date).AddSeconds(20)
    while ((Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue) -and (Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 500
    }
    $left = @(Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue).Count
    $svcState = (Get-Service Windhawk).Status
    Log "windhawk processes left: $left; service: $svcState"
    if ($left -gt 0) { throw 'Windhawk processes refused to exit' }
    if ($svcState -ne 'Stopped') { throw 'Windhawk service did not stop' }
}

if ($Audit) {
    [ordered]@{
        installedVersion  = (Get-VersionOf "$pf\windhawk.exe")
        enginePath        = (Get-EnginePath)
        serviceStatus     = (Get-Service Windhawk).Status.ToString()
        windhawkProcesses = @(Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue).Count
        installerPresent  = (Test-Path $installer)
        installerSha256   = (Get-FileHash $installer -Algorithm SHA256 -ErrorAction SilentlyContinue).Hash
        backupPresent     = (Test-Path $manifestF)
        modKeys           = (Get-ModKeyCount)
        t3Running         = [bool](Get-Process -Name $t3Pattern -ErrorAction SilentlyContinue)
        styler            = (Get-StylerState)
        engineSettings    = (Get-EngineSettings)
        legacyUiMachine   = [Environment]::GetEnvironmentVariable('WINDHAWK_USE_VSCODIUM_UI', 'Machine')
    } | ConvertTo-Json -Depth 4
    return
}

if ($Backup) {
    Invoke-Backup
    return
}

if ($Install) {
    try {
        Remove-Item Env:ELECTRON_RUN_AS_NODE -ErrorAction SilentlyContinue
        $before = Get-VersionOf "$pf\windhawk.exe"
        if ($before -eq $toVer) { Log "already on $toVer; nothing to install"; Log 'install-complete'; return }
        if ($before -ne $fromVer) { throw "installed version is $before, expected $fromVer" }

        Log "waiting on the T3 Code gate (create $cancelFile to cancel)"
        $gate = Wait-ForT3Close
        if ($gate -eq 'cancelled') { Log 'install-cancelled: CANCEL file present; nothing changed'; return }
        if ($gate -eq 'timeout') { Log 'install-timeout: T3 Code stayed open past the wait limit; nothing changed'; return }
        Log 'T3 Code is closed; starting the update'

        Invoke-Backup
        $preState = [ordered]@{
            version    = $before
            enginePath = (Get-EnginePath)
            modKeys    = (Get-ModKeyCount)
            styler     = (Get-StylerState)
            engine     = (Get-EngineSettings)
        }

        Stop-WindhawkEngine

        Log 'running the offline installer silently (/S)'
        $inst = Start-Process -FilePath $installer -ArgumentList '/S' -Wait -PassThru
        Log ('installer exit code: ' + $inst.ExitCode)
        if ($inst.ExitCode -ne 0) { throw "installer exit code $($inst.ExitCode)" }
        Start-Sleep -Seconds 3

        $after = Get-VersionOf "$pf\windhawk.exe"
        Log "installed version: $after"
        if ($after -ne $toVer) { throw "installer left version $after" }
        $enginePath = Get-EnginePath
        Log "engine path: $enginePath"
        foreach ($arch in '32', '64', 'arm64') {
            if (-not (Test-Path "$pf\$enginePath\$arch\windhawk.dll")) { throw "engine DLL missing: $enginePath\$arch" }
        }
        $pending = (Get-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager' -Name PendingFileRenameOperations -ErrorAction SilentlyContinue).PendingFileRenameOperations
        $pendingWh = @($pending | Where-Object { $_ -match 'Windhawk' }).Count
        Log "pending renames touching Windhawk: $pendingWh"

        if ((Get-Service Windhawk).Status -ne 'Running') { Start-Service Windhawk; Start-Sleep -Seconds 5 }
        Log ('service: ' + (Get-Service Windhawk).Status)
        $tray = @(Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" | Where-Object { $_.CommandLine -match '-tray-only' }).Count
        if ($tray -eq 0) {
            Start-Process "$pf\windhawk.exe" -ArgumentList '-tray-only' | Out-Null
            Log 'started the tray (-tray-only)'
            Start-Sleep -Seconds 8
        }

        $explorerState = 'skipped: T3 Code is open again'
        if (-not (Get-Process -Name $t3Pattern -ErrorAction SilentlyContinue)) {
            Log 'restarting Explorer as the logged-on user (pre-approved shell restart)'
            Stop-Process -Name explorer -Force -ErrorAction SilentlyContinue
            Start-Sleep -Seconds 3
            $task = 'WindhawkA7ExplorerRestart'
            schtasks /Create /TN $task /TR 'explorer.exe' /SC ONCE /ST 23:59 /IT /F | Out-Null
            schtasks /Run /TN $task | Out-Null
            Start-Sleep -Seconds 5
            schtasks /Delete /TN $task /F | Out-Null
            $ex = Get-Process -Name explorer -ErrorAction SilentlyContinue
            if (-not $ex) {
                $explorerState = 'NOT RUNNING after restart'
            } else {
                $hooked = @($ex | ForEach-Object { $_.Modules } | Where-Object { $_.ModuleName -eq 'windhawk.dll' } | ForEach-Object { $_.FileName })
                $explorerState = 'running; windhawk.dll: ' + ($hooked -join ', ')
            }
        } else {
            Log 'T3 Code is open again; Explorer not restarted (restart it after T3 closes)'
        }
        Log "explorer: $explorerState"

        Start-Sleep -Seconds 10
        $postState = [ordered]@{
            version    = (Get-VersionOf "$pf\windhawk.exe")
            enginePath = $enginePath
            modKeys    = (Get-ModKeyCount)
            styler     = (Get-StylerState)
            engine     = (Get-EngineSettings)
        }
        Log ("mod keys: before {0}, after {1}" -f $preState.modKeys, $postState.modKeys)
        Log ("compiled 64-bit mod DLLs: " + @(Get-ChildItem "$pd\Engine\Mods\64" -ErrorAction SilentlyContinue).Count)

        [pscustomobject]@{
            task                           = 'Windhawk 2.0.0-alpha.6 -> 2.0.0-alpha.7'
            when                           = (Get-Date -Format 'o')
            installer                      = $installer
            installerSha256                = $instSha
            installerExitCode              = $inst.ExitCode
            before                         = $preState
            after                          = $postState
            explorer                       = $explorerState
            pendingRenamesTouchingWindhawk = $pendingWh
            backup                         = $bdir
            rollback                       = 'scripts\2026-10-11-windhawk-2a7-update.ps1 -Rollback (elevated)'
        } | ConvertTo-Json -Depth 5 | Set-Content $receipt -Encoding UTF8
        Log 'receipt written'
        Log 'install-complete'
    } catch {
        Log 'install-failed'
        Save-PhaseError 'install' $_
        throw
    }
    return
}

if ($Rollback) {
    try {
        Stop-WindhawkEngine

        Log 'restoring Program Files\Windhawk (mirror)'
        & robocopy $pfBak $pf /MIR /XJ /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File "$bdir\rollback-pf.log" -Encoding UTF8
        if ($LASTEXITCODE -ge 8) { throw "robocopy Program Files restore failed: $LASTEXITCODE" }

        Log 'restoring ProgramData\Windhawk (mirror)'
        & robocopy $pdBak $pd /MIR /XJ /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File "$bdir\rollback-pd.log" -Encoding UTF8
        if ($LASTEXITCODE -ge 8) { throw "robocopy ProgramData restore failed: $LASTEXITCODE" }

        Log 'restoring registry'
        & reg.exe delete 'HKLM\SOFTWARE\Windhawk' /f | Out-Null
        & reg.exe import $regBak | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "reg import failed: $LASTEXITCODE" }

        Start-Service Windhawk
        Start-Process "$pf\windhawk.exe" -ArgumentList '-tray-only' | Out-Null
        Start-Sleep -Seconds 8
        Log ('version after rollback: ' + (Get-VersionOf "$pf\windhawk.exe"))
        Log 'rollback-complete'
    } catch {
        Log 'rollback-failed'
        Save-PhaseError 'rollback' $_
        throw
    }
    return
}

throw 'no phase selected: use -Audit, -Backup, -Install or -Rollback'
