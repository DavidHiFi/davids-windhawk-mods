<#
.SYNOPSIS
Windhawk 1.7.3 -> 2.0.0-alpha.6 update. Run elevated (via Invoke-Elevated / lockrun wrapper).

Phases:
  -Audit     print state, change nothing
  -Backup    reg export + tree copies (strict for critical, tolerant for volatile) + UI hash snapshot
  -Install   stop engine, NSIS /S install, verify, keep legacy styled UI, re-apply styler runtime if overwritten
  -Rollback  stop, mirror-restore both dirs, reg delete+import, start 1.7.3

All phases append to backups\2026-10-08\windhawk-2a6-update\phase-log.txt and write
errors to <phase>-error.txt there - never rely on the caller's output capture.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Backup,
    [switch]$Install,
    [switch]$Rollback
)

$ErrorActionPreference = 'Stop'
$root      = 'H:\Windhawk Configuration'
$bdir      = "$root\backups\2026-10-08\windhawk-2a6-update"
$installer = "$bdir\installer\windhawk_setup_offline.exe"
$instSha   = 'EAC905E2E0D87C53241F3A06721124B83A56E7736695EEDF1E1A40B536523D23'
$pf        = 'C:\Program Files\Windhawk'
$pfBak     = "$bdir\ProgramFiles-Windhawk"
$pd        = 'C:\ProgramData\Windhawk'
$pdBak     = "$bdir\ProgramData-Windhawk"
$regBak    = "$bdir\windhawk-registry-HKLM.reg"
$uiHashes  = "$bdir\ui-hashes-before.json"
$receipt   = "$bdir\receipt.json"
$manifest  = "$root\backups\2026-10-07-native-v15\runtime\manifest.json"
$fixture   = 'C:\Users\localuser\WindhawkStylerTest'
$phaseLog  = "$bdir\phase-log.txt"

function Log($m) {
    $line = "[{0}] {1}" -f (Get-Date -Format 'HH:mm:ss'), $m
    Write-Output $line
    Add-Content -Path $phaseLog -Value $line -Encoding UTF8
}

function Save-PhaseError($phase, $err) {
    "$((Get-Date -Format 'HH:mm:ss')) $phase" | Set-Content "$bdir\$phase-error.txt" -Encoding UTF8
    $err | Add-Content "$bdir\$phase-error.txt" -Encoding UTF8
}

function Copy-Tree($src, $dst, $tolerant) {
    $name = Split-Path $src -Leaf
    $rclog = "$bdir\robocopy-$name.log"
    & robocopy $src $dst /E /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File $rclog -Encoding UTF8
    $code = $LASTEXITCODE
    if ($code -ge 8) {
        if ($tolerant) {
            Log ("WARNING: {0} exit {1} - locked/volatile files skipped (see {2})" -f $src, $code, $rclog)
        } else {
            throw "robocopy $src failed: exit $code (log: $rclog)"
        }
    } else {
        Log ("copied {0} (robocopy exit {1})" -f $src, $code)
    }
}

function Get-UiHashes {
    $out = @{}
    Get-ChildItem "$pf\UI" -Recurse -File -ErrorAction SilentlyContinue | ForEach-Object {
        $rel = $_.FullName.Substring(($pf + '\UI\').Length)
        $out[$rel] = (Get-FileHash -LiteralPath $_.FullName).Hash
    }
    return $out
}

function Get-ModKeyCount {
    $k = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
    if (Test-Path $k) { return @(Get-ChildItem $k -ErrorAction SilentlyContinue).Count }
    return 0
}

if ($Audit) {
    [ordered]@{
        InstalledVersion  = (Get-Item "$pf\windhawk.exe" -ErrorAction SilentlyContinue).VersionInfo.FileVersion
        InstallerPresent  = (Test-Path $installer)
        InstallerSha256   = (Get-FileHash $installer -Algorithm SHA256 -ErrorAction SilentlyContinue).Hash
        RegBackupPresent  = (Test-Path $regBak)
        PfBackupPresent   = (Test-Path $pfBak)
        PdBackupPresent   = (Test-Path "$pdBak\ModsSource")
        UiHashesPresent   = (Test-Path $uiHashes)
        WindhawkProcesses = @(Get-Process windhawk -ErrorAction SilentlyContinue).Count
        ModKeys           = Get-ModKeyCount
    } | ConvertTo-Json
    return
}

if ($Backup) {
    try {
        if (-not (Test-Path $installer)) { throw "installer missing: $installer" }
        if ((Get-FileHash $installer -Algorithm SHA256).Hash -ne $instSha) { throw 'installer hash mismatch' }
        New-Item -ItemType Directory -Force -Path $bdir, $pdBak | Out-Null

        if (-not (Test-Path $regBak)) {
            Log 'exporting HKLM\SOFTWARE\Windhawk'
            & reg.exe export 'HKLM\SOFTWARE\Windhawk' $regBak /y | Out-Null
            if ($LASTEXITCODE -ne 0) { throw "reg export failed: $LASTEXITCODE" }
            Log ('registry exported: ' + (Get-Item $regBak).Length + ' bytes')
        } else { Log 'registry export already present' }

        Log 'copying Program Files\Windhawk (resumes, strict)'
        Copy-Tree $pf $pfBak $false
        if ((Get-FileHash "$pf\windhawk.exe").Hash -ne (Get-FileHash "$pfBak\windhawk.exe").Hash) { throw 'PF backup verify failed (windhawk.exe hash)' }

        Log 'copying ProgramData\Windhawk subtrees'
        Copy-Tree "$pd\Engine\Mods"        "$pdBak\Engine\Mods"        $false
        Copy-Tree "$pd\Engine\Symbols"     "$pdBak\Engine\Symbols"     $true
        Copy-Tree "$pd\Engine\ModsWritable" "$pdBak\Engine\ModsWritable" $true
        Copy-Tree "$pd\ModsSource"         "$pdBak\ModsSource"         $false
        Copy-Tree "$pd\UIData"             "$pdBak\UIData"             $true
        Copy-Tree "$pd\EditorWorkspace"    "$pdBak\EditorWorkspace"    $false
        Get-ChildItem $pd -File -ErrorAction SilentlyContinue  | Copy-Item -Destination $pdBak -Force
        Get-ChildItem "$pd\Engine" -File -ErrorAction SilentlyContinue | Copy-Item -Destination "$pdBak\Engine" -Force

        Log 'hashing UI folder (pre-install snapshot)'
        Get-UiHashes | ConvertTo-Json | Set-Content $uiHashes -Encoding UTF8

        $manifest2 = [ordered]@{
            when        = (Get-Date -Format 'o')
            registry    = (Get-Item $regBak).Length
            uiFiles     = @((Get-Content $uiHashes -Raw | ConvertFrom-Json).PSObject.Properties).Count
            modKeys     = Get-ModKeyCount
        }
        $manifest2 | ConvertTo-Json | Set-Content "$bdir\backup-manifest.json" -Encoding UTF8
        Log 'backup complete'
    } catch {
        Save-PhaseError 'backup' $_
        throw
    }
    return
}

if ($Install) {
    try {
        foreach ($f in @($regBak, $uiHashes)) { if (-not (Test-Path $f)) { throw "backup missing: $f - run -Backup first" } }
        if (-not (Test-Path $pfBak)) { throw "backup dir missing: $pfBak - run -Backup first" }
        Remove-Item Env:ELECTRON_RUN_AS_NODE -ErrorAction SilentlyContinue

        $oldVersion = (Get-Item "$pf\windhawk.exe").VersionInfo.FileVersion
        Log "old version: $oldVersion"

        # keep the styled legacy UI as the default UI after the update
        $env:WINDHAWK_USE_VSCODIUM_UI = '1'
        [Environment]::SetEnvironmentVariable('WINDHAWK_USE_VSCODIUM_UI', '1', 'Machine')
        Log 'WINDHAWK_USE_VSCODIUM_UI=1 set (process + machine)'

        Log 'stopping Windhawk (-exit, bounded wait, then force)'
        & "$pf\windhawk.exe" -exit 2>$null | Out-Null
        $deadline = (Get-Date).AddSeconds(25)
        do { Start-Sleep -Milliseconds 500 } while (@(Get-Process windhawk -ErrorAction SilentlyContinue).Count -gt 0 -and (Get-Date) -lt $deadline)
        Get-Process windhawk -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
        Start-Sleep -Seconds 2
        $left = @(Get-Process windhawk -ErrorAction SilentlyContinue).Count
        Log ('windhawk processes now: ' + $left)
        if ($left -gt 0) { throw 'windhawk processes refused to die' }

        Log 'running installer /S'
        $p = Start-Process -FilePath $installer -ArgumentList '/S' -Wait -PassThru
        Log ('installer exit code: ' + $p.ExitCode)
        Start-Sleep -Seconds 5

        $newVersion = (Get-Item "$pf\windhawk.exe" -ErrorAction SilentlyContinue).VersionInfo.FileVersion
        Log "installed version: $newVersion"
        if (-not $newVersion -or $newVersion -eq $oldVersion) {
            Get-Process windhawk_setup*, windhawk -ErrorAction SilentlyContinue | Select-Object Name, Id | Format-Table -AutoSize
            throw "installer did not update windhawk.exe (still $oldVersion)"
        }
        Log ('engine folders: ' + ((Get-ChildItem "$pf\Engine" -Directory -ErrorAction SilentlyContinue | Select-Object -ExpandProperty Name) -join ', '))

        Log ('windhawk processes after install: ' + @(Get-Process windhawk -ErrorAction SilentlyContinue).Count)
        if (@(Get-Process windhawk -ErrorAction SilentlyContinue).Count -eq 0) {
            Log 'starting windhawk -tray-only'
            Start-Process "$pf\windhawk.exe" -ArgumentList '-tray-only'
            Start-Sleep -Seconds 10
        }
        Log ('windhawk processes after start: ' + @(Get-Process windhawk -ErrorAction SilentlyContinue).Count)

        Log 'diffing UI folder against pre-install snapshot'
        $pre = @{}
        (Get-Content $uiHashes -Raw | ConvertFrom-Json).PSObject.Properties | ForEach-Object { $pre[$_.Name] = $_.Value }
        $post = Get-UiHashes
        $changed = New-Object System.Collections.Generic.List[string]
        foreach ($k in $post.Keys) {
            if (-not $pre.ContainsKey($k)) { $changed.Add("ADDED  $k") }
            elseif ($pre[$k] -ne $post[$k]) { $changed.Add("CHANGED $k") }
        }
        foreach ($k in $pre.Keys) { if (-not $post.ContainsKey($k)) { $changed.Add("REMOVED $k") } }
        Log ('UI files changed: ' + $changed.Count)
        $changed | Set-Content "$bdir\ui-changed.txt" -Encoding UTF8

        $restoreNote = 'not needed (UI untouched)'
        $changedRel = @($changed | ForEach-Object { ($_ -split ' ', 2)[1] })
        if ($changed.Count -gt 0 -and (Test-Path $manifest) -and (Test-Path "$fixture\runtime32")) {
            $rows = @(Get-Content $manifest -Raw | ConvertFrom-Json)
            $vscRow = $rows | Where-Object { $_.Relative -eq 'VSCodium.exe' }
            $baseOk = ($null -ne $vscRow) -and ($post['VSCodium.exe'] -eq $vscRow.OriginalHash)
            $targets = @($changedRel | Where-Object { $rows.Relative -contains $_ })
            if ($baseOk -and $targets.Count -gt 0) {
                Log ('base UI is stock 1.74.2 and ' + $targets.Count + ' styler runtime files were overwritten - re-applying')
                $map = @{}
                Get-ChildItem "$fixture\runtime32" -Recurse -File | Where-Object { $_.FullName -notlike "$fixture\runtime32\resources\*" } | ForEach-Object {
                    $rel = $_.FullName.Substring("$fixture\runtime32\".Length)
                    if ($rel -eq 'electron.exe') { $rel = 'VSCodium.exe' }
                    $map[$rel] = $_.FullName
                }
                foreach ($module in 'spdlog','windows-mutex','windows-process-tree','node-pty') {
                    Get-ChildItem "$fixture\addons\node_modules\$module\build\Release\*.node" -ErrorAction SilentlyContinue | ForEach-Object {
                        $map["resources\app\node_modules.asar.unpacked\$module\build\Release\$($_.Name)"] = $_.FullName
                    }
                }
                $map['resources\app\extensions\windhawk\dist\33ff5c221241d3c55cad12b54045a5a1.node'] = "$fixture\addons\node_modules\fs-ext\build\Release\fs_ext.node"
                $ok = $true
                foreach ($rel in $targets) {
                    $src = $map[$rel]
                    $row = $rows | Where-Object { $_.Relative -eq $rel }
                    if ((-not $src) -or (-not (Test-Path $src)) -or ((Get-FileHash $src).Hash -ne $row.NewHash)) {
                        $ok = $false
                        Log "no verified source for $rel"
                    }
                }
                if ($ok) {
                    foreach ($rel in $targets) { Copy-Item $map[$rel] (Join-Path "$pf\UI" $rel) -Force }
                    $restored = $true
                    $restoreNote = "re-applied $($targets.Count) prepared runtime files from fixture (hash-verified)"
                    Log $restoreNote
                } else {
                    $restoreNote = 'SKIPPED: some files had no verified source - styler-fix must re-apply'
                    Log $restoreNote
                }
            } else {
                $restoreNote = "SKIPPED: baseOk=$baseOk, in-scope targets=$($targets.Count) - styler-fix must review"
                Log $restoreNote
            }
        }

        Log ('mod keys now: ' + (Get-ModKeyCount))
        $mods64 = @(Get-ChildItem "$pd\Engine\Mods\64" -ErrorAction SilentlyContinue).Count
        $mods32 = @(Get-ChildItem "$pd\Engine\Mods\32" -ErrorAction SilentlyContinue).Count
        Log "compiled mod DLLs: 64-bit=$mods64 32-bit=$mods32"

        [pscustomobject]@{
            task              = 'Windhawk 1.7.3 -> 2.0.0-alpha.6'
            when              = (Get-Date -Format 'o')
            installer         = $installer
            installerSha256   = $instSha
            oldVersion        = $oldVersion
            newVersion        = $newVersion
            installerExitCode = $p.ExitCode
            windhawkProcesses = @(Get-Process windhawk -ErrorAction SilentlyContinue).Count
            modKeys           = Get-ModKeyCount
            uiFilesChanged    = $changed.Count
            uiRestore         = $restoreNote
            legacyUiEnvVar    = 'WINDHAWK_USE_VSCODIUM_UI=1 (machine)'
            rollback          = "scripts\2026-10-08-windhawk-2a6-update.ps1 -Rollback (elevated)"
        } | ConvertTo-Json | Set-Content $receipt -Encoding UTF8
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
        Log 'ROLLBACK: stopping Windhawk'
        & "$pf\windhawk.exe" -exit 2>$null | Out-Null
        $deadline = (Get-Date).AddSeconds(25)
        do { Start-Sleep -Milliseconds 500 } while (@(Get-Process windhawk -ErrorAction SilentlyContinue).Count -gt 0 -and (Get-Date) -lt $deadline)
        Get-Process windhawk -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
        Start-Sleep -Seconds 2

        Log 'restoring Program Files\Windhawk (mirror)'
        & robocopy $pfBak $pf /MIR /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File "$bdir\rollback-pf.log" -Encoding UTF8
        if ($LASTEXITCODE -ge 8) { throw "robocopy PF restore failed: $LASTEXITCODE" }

        Log 'restoring ProgramData\Windhawk (mirror)'
        & robocopy $pdBak $pd /MIR /R:0 /W:0 /NFL /NDL /NP /NJH /NJS | Out-File "$bdir\rollback-pd.log" -Encoding UTF8
        if ($LASTEXITCODE -ge 8) { throw "robocopy PD restore failed: $LASTEXITCODE" }

        Log 'restoring registry'
        & reg.exe delete 'HKLM\SOFTWARE\Windhawk' /f 2>$null | Out-Null
        & reg.exe import $regBak | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "reg import failed: $LASTEXITCODE" }

        [Environment]::SetEnvironmentVariable('WINDHAWK_USE_VSCODIUM_UI', $null, 'Machine')

        Log 'starting windhawk -tray-only'
        Remove-Item Env:ELECTRON_RUN_AS_NODE -ErrorAction SilentlyContinue
        Start-Process "$pf\windhawk.exe" -ArgumentList '-tray-only'
        Start-Sleep -Seconds 8
        Log ('version after rollback: ' + (Get-Item "$pf\windhawk.exe").VersionInfo.FileVersion)
        Log 'rollback-complete'
    } catch {
        Log 'rollback-failed'
        Save-PhaseError 'rollback' $_
        throw
    }
    return
}

throw 'no phase selected: use -Audit, -Backup, -Install or -Rollback'
