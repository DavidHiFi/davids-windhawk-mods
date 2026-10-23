<#
.SYNOPSIS
Drift guard for the translucent-windows fork under its local@ id (1.8.3, local
build 1). Checks the mod key, ModsSource and both DLLs every 5 minutes (plus at
logon) and heals any silent revert from the pristine copies staged in
Windhawk\translucent-windows-plus\guard.

This replaces the 2026-10-14 guard, which watched the old catalog id
"translucent-windows" - that id is gone (2026-10-15 id migration: the catalog
machinery kept offering a phantom 1.8.2 "update" and silently reinstalling
stock builds; the fork now lives as local@translucent-windows, which the app
never tracks against the catalog). Pristine copies for the new id were
restaged from the live install; the old set is archived under
guard\archive-256343.

Settings edits through the engine are safe - they only bump SettingsChangeTime,
which the guard ignores. For source edits or rebuilds, suspend the guard first
and let the new InstallGuard clear the marker (or delete it by hand):

  New-Item C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend -Force
  Remove-Item C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend

If the engine ever recompiles the mod itself (new _N DLL name), suspend the
guard, restage pristine copies, and update the hashes here.

To retire the guard entirely: Disable-ScheduledTask -TaskName TranslucentWindowsGuard

Actions: Audit | Enforce (used by the scheduled task) | InstallGuard | RemoveGuard.
Install elevated (registers the task and clears the suspend marker):
  powershell.exe -NoProfile -ExecutionPolicy Bypass -File <this> -Action InstallGuard
#>
[CmdletBinding()]
param(
    [ValidateSet('Audit', 'Enforce', 'InstallGuard', 'RemoveGuard')]
    [string]$Action = 'Audit'
)

$ErrorActionPreference = 'Stop'

$ws        = 'H:\Windhawk Configuration'
$dev       = Join-Path $ws 'Windhawk\translucent-windows-plus\local@translucent-windows-plus.wh.cpp'
$src       = 'C:\ProgramData\Windhawk\ModsSource\local@translucent-windows-plus.wh.cpp'
$modKey    = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@translucent-windows-plus'
$modKeyReg = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@translucent-windows-plus'
$fixDll    = 'local@translucent-windows-plus_1.8.3_1.dll'
$forkHash  = '3A9212A1168AFEF874DB3AEBFBD6C97B8338282A39B09518650FF95030D7CCAF'
$dll64Hash = 'BDA532B9732A58B96E22AA5025F00F2B77DB6612B571E92835285627F149A658'
$dll32Hash = 'F1B002236AECCA8A8BFC20CEFDF0D20C03727C4384CF76C14521A181EAA81A9B'
$guardDir  = Join-Path $ws 'Windhawk\translucent-windows-plus\guard'
$rep       = Join-Path $ws 'reports\2026-10-24-translucent-windows-plus-guard'
$log       = 'C:\ProgramData\Windhawk\ModsWritable\translucent-windows-guard.log'
$stampFile = 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.stamp'
$suspend   = 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend'
$taskName  = 'TranslucentWindowsGuard'

function Get-Sha([string]$Path) { (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash }

function Write-Log([string]$Line) {
    try {
        $dir = Split-Path $log -Parent
        if (-not (Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
        Add-Content -LiteralPath $log -Value ("{0} {1}" -f (Get-Date -Format o), $Line) -Encoding UTF8
    } catch { }
}

function Get-ModState {
    $k = Get-ItemProperty -LiteralPath $modKey
    $p64 = "C:\ProgramData\Windhawk\Engine\Mods\64\$fixDll"
    $p32 = "C:\ProgramData\Windhawk\Engine\Mods\32\$fixDll"
    return [ordered]@{
        libraryFileName = $k.LibraryFileName
        version         = $k.Version
        disabled        = $k.Disabled
        srcSha256       = $(if (Test-Path $src) { Get-Sha $src })
        dll64Sha256     = $(if (Test-Path $p64) { Get-Sha $p64 })
        dll32Sha256     = $(if (Test-Path $p32) { Get-Sha $p32 })
    }
}

function Repair-Dll([string]$Arch, [string]$Want) {
    $live = "C:\ProgramData\Windhawk\Engine\Mods\$Arch\$fixDll"
    $pristine = Join-Path $guardDir "$Arch\$fixDll"
    $liveSha = $(if (Test-Path -LiteralPath $live) { Get-Sha $live })
    if ($liveSha -eq $Want) { return }
    if (-not (Test-Path -LiteralPath $pristine) -or (Get-Sha $pristine) -ne $Want) {
        throw "no pristine $Arch copy to restore from."
    }
    $stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    if (Test-Path -LiteralPath $live) {
        Move-Item -LiteralPath $live -Destination "$live.bad-$stamp" -Force -ErrorAction SilentlyContinue
    }
    Copy-Item -LiteralPath $pristine -Destination $live -Force
    if ((Get-Sha $live) -ne $Want) { throw "$Arch DLL restore failed." }
}

try {
    switch ($Action) {

        'Audit' {
            Write-Output (Get-ModState | ConvertTo-Json)
            Write-Output "suspendMarker: $(Test-Path $suspend)"
            $t = Get-ScheduledTask -TaskName $taskName -ErrorAction SilentlyContinue
            if ($t) { Write-Output "task: $($t.State)"; Write-Output ((Get-ScheduledTaskInfo -TaskName $taskName) | Select-Object LastRunTime, NextRunTime | ConvertTo-Json -Compress) }
            else { Write-Output 'task: not registered' }
        }

        'Enforce' {
            if (Test-Path $suspend) { Write-Log 'suspended by marker, skipping'; exit 0 }

            $st = Get-ModState
            $issues = @()
            if ($st.libraryFileName -ne $fixDll)      { $issues += "LibraryFileName=$($st.libraryFileName)" }
            if ($st.version -ne '1.8.3')              { $issues += "Version=$($st.version)" }
            if ([int]$st.disabled -ne 0)              { $issues += "Disabled=$($st.disabled)" }
            if ($st.srcSha256 -ne $forkHash)          { $issues += 'ModsSource drifted' }
            if ($st.dll64Sha256 -ne $dll64Hash)       { $issues += 'x64 DLL drifted' }
            if ($st.dll32Sha256 -ne $dll32Hash)       { $issues += 'x86 DLL drifted' }

            if ($issues.Count -eq 0) {
                try { Set-Content -LiteralPath $stampFile -Value (Get-Date -Format o) -Encoding UTF8 } catch { }
                exit 0
            }

            Write-Log ("DRIFT: " + ($issues -join '; '))
            $stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
            $bkd = Join-Path (Join-Path $ws 'backups') (Join-Path (Get-Date -Format 'yyyy-MM-dd') "guard-$stamp")
            New-Item -ItemType Directory -Path $bkd -Force | Out-Null
            cmd.exe /d /c "reg.exe export ""$modKeyReg"" ""$(Join-Path $bkd 'mod-key-drifted.reg')"" /y >nul 2>&1"
            if ($st.srcSha256) { Copy-Item -LiteralPath $src -Destination (Join-Path $bkd 'ModsSource-drifted.wh.cpp') -Force }

            Repair-Dll '64' $dll64Hash
            Repair-Dll '32' $dll32Hash

            if (-not (Test-Path -LiteralPath $dev) -or (Get-Sha $dev) -ne $forkHash) {
                throw 'workspace staged source is not the reviewed copy; refusing to heal.'
            }
            Copy-Item -LiteralPath $dev -Destination $src -Force
            if ((Get-Sha $src) -ne $forkHash) { throw 'ModsSource readback failed after heal.' }

            $pristineReg = Join-Path $guardDir 'local@translucent-windows-plus-1.8.3-1.reg'
            $imported = $false
            if (Test-Path -LiteralPath $pristineReg) {
                cmd.exe /d /c "reg.exe import ""$pristineReg"" >nul 2>&1"
                $imported = ($LASTEXITCODE -eq 0)
            }
            if (-not $imported) {
                Set-ItemProperty -LiteralPath $modKey -Name LibraryFileName -Value $fixDll -Type String
                Set-ItemProperty -LiteralPath $modKey -Name Version -Value '1.8.3' -Type String
                Set-ItemProperty -LiteralPath $modKey -Name Disabled -Value 0 -Type DWord
            }
            # -UFormat %s in PS 5.1 encodes local time as UTC (8h skew here); use the real UTC epoch.
            $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
            Set-ItemProperty -LiteralPath $modKey -Name SettingsChangeTime -Value $now -Type DWord

            $after = Get-ModState
            if ($after.libraryFileName -ne $fixDll -or $after.version -ne '1.8.3' -or [int]$after.disabled -ne 0 -or $after.srcSha256 -ne $forkHash -or $after.dll64Sha256 -ne $dll64Hash) {
                Write-Log 'HEAL FAILED: readback mismatch'
                exit 3
            }
            Write-Log ("HEALED: " + ($issues -join '; '))
            if (-not (Test-Path -LiteralPath $rep)) { New-Item -ItemType Directory -Path $rep -Force | Out-Null }
            [ordered]@{ action = 'heal'; timestamp = (Get-Date -Format o); issues = $issues; backup = $bkd; after = $after } |
                ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $rep "heal-$stamp.json") -Encoding UTF8
        }

        'InstallGuard' {
            $guardScript = $PSCommandPath
            # $taskAction, not $action: it would collide with the $Action parameter (case-insensitive ValidateSet).
            # Launch hidden through the shared VBS launcher: a direct powershell.exe task
            # action (even with -WindowStyle Hidden) opens a visible console for a split
            # second on every run (2026-10-15 popup recurrence). The task's RunLevel
            # Highest still applies to the whole wscript -> powershell child chain.
            $taskAction = New-ScheduledTaskAction -Execute 'wscript.exe' `
                -Argument ('//nologo "H:\System Configuration\scripts\Run-PowerShellHidden.vbs" "' + $guardScript + '" -Action Enforce') `
                -WorkingDirectory $ws
            $tRepeat = New-ScheduledTaskTrigger -Once -At (Get-Date).AddMinutes(1) `
                -RepetitionInterval (New-TimeSpan -Minutes 5) -RepetitionDuration (New-TimeSpan -Days 3650)
            $tLogon = New-ScheduledTaskTrigger -AtLogOn -User "$env:USERDOMAIN\$env:USERNAME"
            $principal = New-ScheduledTaskPrincipal -UserId "$env:USERDOMAIN\$env:USERNAME" -LogonType Interactive -RunLevel Highest
            $settings = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries `
                -StartWhenAvailable -ExecutionTimeLimit (New-TimeSpan -Minutes 10) -MultipleInstances IgnoreNew
            Register-ScheduledTask -TaskName $taskName -Action $taskAction -Trigger $tRepeat, $tLogon `
                -Principal $principal -Settings $settings -Force | Out-Null
            # The migration left the guard suspended; protection resumes with the new pristine state.
            Remove-Item -LiteralPath $suspend -Force -ErrorAction SilentlyContinue
            Write-Log 'guard task installed (local@ id); suspend marker cleared'
            Write-Output "task registered: $taskName (every 5 min + at logon, highest privileges)"
            & $guardScript -Action Audit
        }

        'RemoveGuard' {
            Unregister-ScheduledTask -TaskName $taskName -Confirm:$false
            Write-Log 'guard task removed'
            Write-Output "task removed: $taskName"
        }
    }
}
catch {
    $msg = "$Action failed at line $($_.InvocationInfo.ScriptLineNumber): $($_.Exception.Message)"
    Write-Log "ERROR: $msg"
    Write-Output $msg
    exit 1
}

