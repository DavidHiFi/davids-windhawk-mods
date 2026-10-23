<#
.SYNOPSIS
Updates the Windhawk engine to a preview (alpha) release from GitHub: check, prepare, launch, install, rollback.
Works for any ramensoftware/windhawk pre-release that ships windhawk_setup_offline.exe. Run it with the
Windows PowerShell 5.1 host: powershell.exe -NoProfile -ExecutionPolicy Bypass -File <this script> -Check

  -Check                   read-only: installed version, newest pre-release, whether an update is due
  -Prepare [-Tag X]        download the offline installer, check its SHA256 digest, Authenticode signer and
                           file version. Changes nothing in Windhawk. Writes prepare.json.
  -Launch [-BackupDir D]   start the install detached and elevated, then poll its phase log. Takes the coop
                           lock windhawk-engine first when -CoopId is given. Never touches T3 Code.
  -AllowT3Open             with -Launch: install even though T3 Code is open. The Explorer restart is skipped,
                           so T3 and Explorer keep the old engine code until T3 closes and Explorer restarts or
                           the PC reboots. Freeze risk: see notes\2026-10-11-windhawk-2a7-update.md.
  -Install -BackupDir D    elevated, started by -Launch: wait until no T3 Code process runs, back up, stop the
                           service and every Windhawk process, run the installer silently, verify, start the
                           service and tray, restart Explorer, write receipt.json, release the coop lock.
  -Rollback -BackupDir D   elevated: wait for T3 Code to close, stop, mirror-restore Program Files and
                           ProgramData from the backup, import the registry, start the service and tray.

The backup folder is backups\<date>\windhawk-<from>-to-<to>\. Create CANCEL in it to stop an install that is
still waiting for T3 Code. Markers in phase-log.txt: install-complete, install-failed, install-cancelled,
install-timeout, rollback-complete, rollback-failed.
#>
[CmdletBinding()]
param(
    [string]$Tag,
    [switch]$Check,
    [switch]$Prepare,
    [switch]$Launch,
    [switch]$Install,
    [switch]$Rollback,
    [string]$BackupDir,
    [string]$CoopId,
    [switch]$AllowT3Open,
    [string]$CoopPython = 'C:\Users\localuser\AppData\Local\Programs\Python\Python313\python.exe',
    [int]$PollSeconds = 21600
)

$ErrorActionPreference = 'Stop'
$repo       = 'ramensoftware/windhawk'
$asset      = 'windhawk_setup_offline.exe'
$signer     = 'Michael Maltsev'
$root       = 'H:\Windhawk Configuration'
$backupsDir = "$root\backups"
$coopScript = 'H:\Claude\tools\AgentCoop\coop.py'
$pf         = 'C:\Program Files\Windhawk'
$pd         = 'C:\ProgramData\Windhawk'
$regKey     = 'HKLM\SOFTWARE\Windhawk'
$regPs      = 'HKLM:\SOFTWARE\Windhawk'
$stylerKey  = "$regPs\Engine\Mods\local@windhawk-styler"
$settingsKey = "$regPs\Engine\Settings"
$t3Pattern  = 'T3 Code*'
$t3WaitSec  = 21600
$scriptPath = $MyInvocation.MyCommand.Path

function Log([string]$Message) {
    $line = '[{0}] {1}' -f (Get-Date -Format 'HH:mm:ss'), $Message
    Write-Host $line
    # The launcher polls this file while the install writes it, so either side can hit a sharing error. Retry.
    if ($script:phaseLog) {
        for ($try = 1; $try -le 20; $try++) {
            try { Add-Content -Path $script:phaseLog -Value $line -Encoding UTF8; break }
            catch { Start-Sleep -Milliseconds 250 }
        }
    }
}

# The final result goes to its own file, written once with a rename, so the launcher never reads a log that
# is still being appended to. A contention test lost 143 of 400 appended lines while reporting success.
function Mark([string]$Marker) {
    Log $Marker
    if ($script:bdir) {
        $tmp = "$script:bdir\result.tmp"
        Set-Content -Path $tmp -Value $Marker -Encoding ASCII
        Move-Item -Path $tmp -Destination "$script:bdir\result.txt" -Force
    }
}

function Save-PhaseError([string]$Phase, $Err) {
    if (-not $script:bdir) { return }
    $file = "$script:bdir\$Phase-error.txt"
    "$((Get-Date -Format 'HH:mm:ss')) $Phase" | Set-Content $file -Encoding UTF8
    $Err | Out-String | Add-Content $file -Encoding UTF8
}

function Get-VersionOf([string]$Exe) {
    return (Get-Item $Exe -ErrorAction SilentlyContinue).VersionInfo.FileVersion
}

function Get-ModKeyCount {
    if (Test-Path $regPs) { return @(Get-ChildItem "$regPs\Engine\Mods" -ErrorAction SilentlyContinue).Count }
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

function Resolve-Tag {
    if ($Tag) { return $Tag }
    $releases = gh release list -R $repo --limit 15 --json tagName,isPrerelease,publishedAt | ConvertFrom-Json
    $pre = $releases | Where-Object { $_.isPrerelease } | Sort-Object publishedAt -Descending | Select-Object -First 1
    if (-not $pre) { throw "no pre-release found in $repo" }
    return $pre.tagName
}

function Read-Prep([string]$Dir) {
    if (-not $Dir) {
        $latest = Get-ChildItem "$backupsDir\*\windhawk-*-to-*\prepare.json" -ErrorAction SilentlyContinue |
            Sort-Object LastWriteTime -Descending | Select-Object -First 1
        if (-not $latest) { throw 'no prepare.json found: run -Prepare first' }
        $Dir = Split-Path $latest.FullName -Parent
    }
    $file = "$Dir\prepare.json"
    if (-not (Test-Path $file)) { throw "prepare.json missing in $Dir" }
    $prep = Get-Content $file -Raw | ConvertFrom-Json
    $prep | Add-Member -NotePropertyName dir -NotePropertyValue $Dir -Force
    return $prep
}

function Initialize-Phase([string]$Dir) {
    $script:bdir = $Dir
    $script:phaseLog = "$Dir\phase-log.txt"
    New-Item -ItemType Directory -Force -Path $Dir | Out-Null
}

function Copy-Tree([string]$Src, [string]$Dst, [bool]$Strict) {
    if (-not (Test-Path $Src)) { Log "skipped missing $Src"; return }
    $rclog = "$script:bdir\robocopy-" + ($Dst.Substring($script:bdir.Length + 1) -replace '[\\/]', '_') + '.log'
    & robocopy $Src $Dst /E /XJ /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File $rclog -Encoding UTF8
    $code = $LASTEXITCODE
    if ($code -ge 8) {
        if ($Strict) { throw "robocopy $Src failed: exit $code (log: $rclog)" }
        Log ("WARNING: {0} exit {1}; locked or volatile files skipped ({2})" -f $Src, $code, $rclog)
    } else {
        Log ("copied {0} (robocopy exit {1})" -f $Src, $code)
    }
}

function Invoke-Backup([string]$InstallerPath, [string]$ExpectedSha) {
    $pfBak = "$script:bdir\ProgramFiles-Windhawk"
    $pdBak = "$script:bdir\ProgramData-Windhawk"
    $regBak = "$script:bdir\windhawk-registry-HKLM.reg"
    try {
        if ((Get-FileHash $InstallerPath -Algorithm SHA256).Hash -ne $ExpectedSha) { throw 'installer hash mismatch' }
        New-Item -ItemType Directory -Force -Path "$pdBak\Engine" | Out-Null

        Log "exporting $regKey"
        & reg.exe export $regKey $regBak /y | Out-Null
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
        $manifest | ConvertTo-Json -Depth 4 | Set-Content "$script:bdir\backup-manifest.json" -Encoding UTF8
        Log 'backup complete'
    } catch {
        Save-PhaseError 'backup' $_
        throw
    }
}

function Wait-ForT3Close([string]$Dir) {
    $deadline = (Get-Date).AddSeconds($t3WaitSec)
    $announced = $false
    while (Get-Process -Name $t3Pattern -ErrorAction SilentlyContinue) {
        if (Test-Path "$Dir\CANCEL") { return 'cancelled' }
        if ((Get-Date) -gt $deadline) { return 'timeout' }
        if (-not $announced) { Log 'waiting: T3 Code is open; the engine stays up until it closes'; $announced = $true }
        Start-Sleep -Seconds 5
    }
    if (Test-Path "$Dir\CANCEL") { return 'cancelled' }
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

function Start-WindhawkEngine {
    if ((Get-Service Windhawk).Status -ne 'Running') { Start-Service Windhawk; Start-Sleep -Seconds 5 }
    Log ('service: ' + (Get-Service Windhawk).Status)
    $tray = @(Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" | Where-Object { $_.CommandLine -match '-tray-only' }).Count
    if ($tray -eq 0) {
        Start-Process "$pf\windhawk.exe" -ArgumentList '-tray-only' | Out-Null
        Log 'started the tray (-tray-only)'
        Start-Sleep -Seconds 8
    }
}

function Restart-Explorer {
    Log 'restarting Explorer as the logged-on user (pre-approved shell restart)'
    Stop-Process -Name explorer -Force -ErrorAction SilentlyContinue
    Start-Sleep -Seconds 3
    # A scheduled task launches Explorer at Medium integrity; a plain Start-Process from an elevated shell would not.
    $task = 'WindhawkAlphaExplorerRestart'
    schtasks /Create /TN $task /TR 'explorer.exe' /SC ONCE /ST 23:59 /IT /F | Out-Null
    schtasks /Run /TN $task | Out-Null
    Start-Sleep -Seconds 5
    schtasks /Delete /TN $task /F | Out-Null
    $ex = Get-Process -Name explorer -ErrorAction SilentlyContinue
    if (-not $ex) { return 'NOT RUNNING after restart' }
    $hooked = @($ex | ForEach-Object { $_.Modules } | Where-Object { $_.ModuleName -eq 'windhawk.dll' } | ForEach-Object { $_.FileName })
    return 'running; windhawk.dll: ' + ($hooked -join ', ')
}

function Invoke-CoopUnlock {
    # -C is required: an elevated process starts in System32, so coop would look in the wrong project
    # and report the lock as not held. Measured 2026-10-11 with a probe lock.
    if (-not $CoopId) { return }
    $out = & $CoopPython -I $coopScript -C $root unlock windhawk-engine --as $CoopId 2>&1
    if ($LASTEXITCODE -eq 0) { Log (($out | Out-String).Trim()) } else { Log ("WARNING: coop unlock failed (exit $LASTEXITCODE): " + ($out | Out-String).Trim()) }
}

# ---------------------------------------------------------------- Check
if ($Check) {
    $target = Resolve-Tag
    $installed = Get-VersionOf "$pf\windhawk.exe"
    [ordered]@{
        installedVersion = $installed
        newestPrerelease = $target
        updateDue        = ($installed -ne $target)
        serviceStatus    = (Get-Service Windhawk).Status.ToString()
        t3Running        = [bool](Get-Process -Name $t3Pattern -ErrorAction SilentlyContinue)
        modKeys          = (Get-ModKeyCount)
        styler           = (Get-StylerState)
        legacyUiMachine  = [Environment]::GetEnvironmentVariable('WINDHAWK_USE_VSCODIUM_UI', 'Machine')
    } | ConvertTo-Json -Depth 4
    return
}

# ---------------------------------------------------------------- Prepare
if ($Prepare) {
    $tagName = Resolve-Tag
    $to = $tagName
    $from = Get-VersionOf "$pf\windhawk.exe"
    if ($from -eq $to) { Write-Host "already on $to; nothing to prepare"; return }
    $dir = "$backupsDir\$(Get-Date -Format 'yyyy-MM-dd')\windhawk-$from-to-$to"
    Initialize-Phase $dir
    New-Item -ItemType Directory -Force -Path "$dir\installer" | Out-Null
    Log "preparing $from -> $to in $dir"

    $release = gh release view $tagName -R $repo --json assets | ConvertFrom-Json
    $asset_ = $release.assets | Where-Object { $_.name -eq $asset } | Select-Object -First 1
    if (-not $asset_ -or -not $asset_.digest) { throw "$asset with a sha256 digest not found on $tagName" }
    $expectedSha = ($asset_.digest -replace '^sha256:', '').ToUpper()

    gh release download $tagName -R $repo -p $asset -D "$dir\installer" --clobber
    if ($LASTEXITCODE -ne 0) { throw "gh release download failed: $LASTEXITCODE" }
    $installerPath = "$dir\installer\$asset"
    $actualSha = (Get-FileHash $installerPath -Algorithm SHA256).Hash
    if ($actualSha -ne $expectedSha) { throw "SHA256 mismatch: got $actualSha, release says $expectedSha" }
    Log "SHA256 matches the release digest"

    $sig = Get-AuthenticodeSignature $installerPath
    $subject = $sig.SignerCertificate.Subject
    if ($sig.Status -ne 'Valid' -or $subject -notmatch [regex]::Escape($signer)) {
        throw "Authenticode check failed: status $($sig.Status), signer $subject"
    }
    Log "Authenticode valid: $subject"

    $fileVersion = (Get-Item $installerPath).VersionInfo.FileVersion
    if ($fileVersion -ne $to) { throw "installer file version $fileVersion does not match tag $to" }
    Log "installer file version $fileVersion matches the tag"

    [ordered]@{
        tag             = $tagName
        from            = $from
        to              = $to
        installerPath   = $installerPath
        installerSha256 = $actualSha
        signer          = $subject
        assetBytes      = (Get-Item $installerPath).Length
        preparedAt      = (Get-Date -Format 'o')
    } | ConvertTo-Json | Set-Content "$dir\prepare.json" -Encoding UTF8
    Log "prepared: $dir\prepare.json"
    Write-Host "Next: powershell -File `"$scriptPath`" -Launch -BackupDir `"$dir`" [-CoopId <thread id>]"
    return
}

# ---------------------------------------------------------------- Launch
if ($Launch) {
    $prep = Read-Prep $BackupDir
    Initialize-Phase $prep.dir
    $installed = Get-VersionOf "$pf\windhawk.exe"
    if ($installed -ne $prep.from) { throw "installed version is $installed, prepared for $($prep.from)" }
    if ($CoopId) {
        & $CoopPython -I $coopScript -C $root lock windhawk-engine --as $CoopId --reason "Windhawk $($prep.to) install armed; waits for T3 Code to close" --ttl 25200
        if ($LASTEXITCODE -ne 0) { Write-Host 'windhawk-engine is held by another thread; not launching'; exit 4 }
    }
    Remove-Item Env:ELECTRON_RUN_AS_NODE -ErrorAction SilentlyContinue
    Remove-Item "$($prep.dir)\result.txt" -ErrorAction SilentlyContinue
    $argLine = '-NoProfile -ExecutionPolicy Bypass -File "{0}" -Install -BackupDir "{1}"' -f $scriptPath, $prep.dir
    if ($CoopId) { $argLine += ' -CoopId "{0}" -CoopPython "{1}"' -f $CoopId, $CoopPython }
    if ($AllowT3Open) { $argLine += ' -AllowT3Open' }
    Start-Process powershell.exe -ArgumentList $argLine -Verb RunAs -WindowStyle Hidden | Out-Null
    Write-Host "launched install of $($prep.to) elevated and detached; polling $script:phaseLog"

    $deadline = (Get-Date).AddSeconds($PollSeconds)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Seconds 5
        $result = if (Test-Path "$($prep.dir)\result.txt") { (Get-Content "$($prep.dir)\result.txt" -Raw -ErrorAction SilentlyContinue) } else { '' }
        if ($result -match 'install-complete') { Invoke-CoopUnlock; Write-Host 'COMPLETE'; exit 0 }
        if ($result -match 'install-failed') { Invoke-CoopUnlock; Write-Host 'FAILED - read the *-error.txt in the backup folder'; exit 2 }
        if ($result -match 'install-cancelled|install-timeout') { Invoke-CoopUnlock; Write-Host 'NOT RUN'; exit 3 }
    }
    Write-Host 'STILL RUNNING - waiting on T3 Code or a slow install; keep reading phase-log.txt'
    exit 4
}

# ---------------------------------------------------------------- Install (elevated)
if ($Install) {
    $prep = Read-Prep $BackupDir
    Initialize-Phase $prep.dir
    try {
        Remove-Item Env:ELECTRON_RUN_AS_NODE -ErrorAction SilentlyContinue
        $before = Get-VersionOf "$pf\windhawk.exe"
        if ($before -eq $prep.to) { Log "already on $($prep.to)"; Mark 'install-complete'; return }
        if ($before -ne $prep.from) { throw "installed version is $before, prepared for $($prep.from)" }

        if ($AllowT3Open) {
            Log 'AllowT3Open: installing with T3 Code open; Explorer restart is skipped'
            $gate = 'clear'
        } else {
            Log "waiting on the T3 Code gate (create $($prep.dir)\CANCEL to cancel)"
            $gate = Wait-ForT3Close $prep.dir
        }
        if ($gate -eq 'cancelled') { Mark 'install-cancelled: CANCEL file present; nothing changed'; return }
        if ($gate -eq 'timeout') { Mark 'install-timeout: T3 Code stayed open past the wait limit; nothing changed'; return }
        Log 'T3 Code is closed; starting the update'

        Invoke-Backup $prep.installerPath $prep.installerSha256
        $preState = [ordered]@{ version = $before; enginePath = (Get-EnginePath); modKeys = (Get-ModKeyCount); styler = (Get-StylerState); engine = (Get-EngineSettings) }

        Stop-WindhawkEngine

        Log 'running the offline installer silently (/S)'
        $inst = Start-Process -FilePath $prep.installerPath -ArgumentList '/S' -Wait -PassThru
        Log ('installer exit code: ' + $inst.ExitCode)
        if ($inst.ExitCode -ne 0) { throw "installer exit code $($inst.ExitCode)" }
        Start-Sleep -Seconds 3

        $after = Get-VersionOf "$pf\windhawk.exe"
        Log "installed version: $after"
        if ($after -ne $prep.to) { throw "installer left version $after, expected $($prep.to)" }
        $enginePath = Get-EnginePath
        Log "engine path: $enginePath"
        foreach ($arch in '32', '64', 'arm64') {
            if (-not (Test-Path "$pf\$enginePath\$arch\windhawk.dll")) { throw "engine DLL missing: $enginePath\$arch" }
        }
        $pending = (Get-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager' -Name PendingFileRenameOperations -ErrorAction SilentlyContinue).PendingFileRenameOperations
        $pendingWh = @($pending | Where-Object { $_ -match 'Windhawk' }).Count
        Log "pending renames touching Windhawk: $pendingWh"

        Start-WindhawkEngine

        $explorerState = 'skipped: T3 Code is open again'
        if (-not (Get-Process -Name $t3Pattern -ErrorAction SilentlyContinue)) {
            $explorerState = Restart-Explorer
        } else {
            Log 'T3 Code is open again; Explorer not restarted (restart it after T3 closes)'
        }
        Log "explorer: $explorerState"

        Start-Sleep -Seconds 10
        $postState = [ordered]@{ version = (Get-VersionOf "$pf\windhawk.exe"); enginePath = $enginePath; modKeys = (Get-ModKeyCount); styler = (Get-StylerState); engine = (Get-EngineSettings) }
        Log ("mod keys: before {0}, after {1}" -f $preState.modKeys, $postState.modKeys)
        Log ("compiled 64-bit mod DLLs: " + @(Get-ChildItem "$pd\Engine\Mods\64" -ErrorAction SilentlyContinue).Count)

        [pscustomobject]@{
            task                           = "Windhawk $($prep.from) -> $($prep.to)"
            when                           = (Get-Date -Format 'o')
            installerSha256                = $prep.installerSha256
            installerExitCode              = $inst.ExitCode
            before                         = $preState
            after                          = $postState
            explorer                       = $explorerState
            pendingRenamesTouchingWindhawk = $pendingWh
            backup                         = $prep.dir
            rollback                       = "scripts\windhawk-alpha-update.ps1 -Rollback -BackupDir `"$($prep.dir)`""
        } | ConvertTo-Json -Depth 5 | Set-Content "$($prep.dir)\receipt.json" -Encoding UTF8
        Log 'receipt written'
        Mark 'install-complete'
    } catch {
        Mark 'install-failed'
        Save-PhaseError 'install' $_
        throw
    } finally {
        Invoke-CoopUnlock
    }
    return
}

# ---------------------------------------------------------------- Rollback (elevated)
if ($Rollback) {
    $prep = Read-Prep $BackupDir
    Initialize-Phase $prep.dir
    $pfBak = "$($prep.dir)\ProgramFiles-Windhawk"
    $pdBak = "$($prep.dir)\ProgramData-Windhawk"
    $regBak = "$($prep.dir)\windhawk-registry-HKLM.reg"
    try {
        $gate = Wait-ForT3Close $prep.dir
        if ($gate -ne 'clear') { Mark "rollback-failed: gate returned $gate; nothing changed"; return }
        Stop-WindhawkEngine

        Log 'restoring Program Files\Windhawk (mirror)'
        & robocopy $pfBak $pf /MIR /XJ /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File "$($prep.dir)\rollback-pf.log" -Encoding UTF8
        if ($LASTEXITCODE -ge 8) { throw "robocopy Program Files restore failed: $LASTEXITCODE" }

        Log 'restoring ProgramData\Windhawk (mirror)'
        & robocopy $pdBak $pd /MIR /XJ /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File "$($prep.dir)\rollback-pd.log" -Encoding UTF8
        if ($LASTEXITCODE -ge 8) { throw "robocopy ProgramData restore failed: $LASTEXITCODE" }

        Log 'restoring registry'
        & reg.exe delete $regKey /f | Out-Null
        & reg.exe import $regBak | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "reg import failed: $LASTEXITCODE" }

        Start-WindhawkEngine
        Log ('version after rollback: ' + (Get-VersionOf "$pf\windhawk.exe"))
        Mark 'rollback-complete'
    } catch {
        Mark 'rollback-failed'
        Save-PhaseError 'rollback' $_
        throw
    }
    return
}

Write-Host 'Choose one: -Check, -Prepare, -Launch, -Install, -Rollback (see the header of this script).'
exit 1
