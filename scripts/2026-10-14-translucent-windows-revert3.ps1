<#
.SYNOPSIS
Reinstall the reviewed translucent-windows 1.8.3 build 256343 after the third
unattributed revert to stock 1.8.2 (2026-10-14 07:54 local, fresh build 137900),
and stage pristine copies for the drift guard.

Same signature as reverts 1-2: stock source recompiled through the engine in the
x86 -> x64 -> source-save order, ModsSource overwritten, SettingsChangeTime not
bumped by the install. This time the source save landed 4 ms before Windhawk's
own userprofile.json rewrite, so the app itself performed the install.

Actions: Audit (read only) | Install (backup + restore 1.8.3/256343 + stage guard copies) | Rollback.
Run elevated: Invoke-Elevated.ps1 -File <this> -ArgumentList "-Action Install"
#>
[CmdletBinding()]
param(
    [ValidateSet('Audit', 'Install', 'Rollback')]
    [string]$Action = 'Audit'
)

$ErrorActionPreference = 'Stop'

$ws        = 'H:\Windhawk Configuration'
$dev       = Join-Path $ws 'Windhawk\translucent-windows\translucent-windows.wh.cpp'
$bk        = Join-Path $ws 'backups\2026-10-14\translucent-windows-revert3'
$rep       = Join-Path $ws 'reports\2026-10-14-translucent-windows-revert3'
$guardDir  = Join-Path $ws 'Windhawk\translucent-windows\guard'
$src       = 'C:\ProgramData\Windhawk\ModsSource\translucent-windows.wh.cpp'
$modKey    = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'

$forkHash      = '70B64AF483BEB86C91B5D34213380BBE25579FD778C5BD2B15C44CFF5B6D851A'  # round-5 reviewed source
$stockHash     = '0F88018DB7C22FD37484C763182BC5587BDB21AD4E869C5D7099F6FAAEF3FCD1'  # stock 1.8.2, current ModsSource
$dll64Hash     = 'D284A5E33789960090D873B55B34F9DADF97935082944B9D724EBC8D1540C7D6'  # from the round-5 receipt
$fixDll        = 'translucent-windows_1.8.3_256343.dll'
$regBackup     = Join-Path $bk 'translucent-windows-before-revert3.reg'
$stockSrcCopy  = Join-Path $bk 'ModsSource-reverted-1.8.2-137900.wh.cpp'

if ($Action -ne 'Audit') {
    foreach ($d in $rep, $bk) {
        if (-not (Test-Path -LiteralPath $d)) { New-Item -ItemType Directory -Path $d | Out-Null }
    }
}

function Get-Sha([string]$Path) { (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash }

function Get-ModState {
    $k = Get-ItemProperty -LiteralPath $modKey
    $state = [ordered]@{
        version            = $k.Version
        libraryFileName    = $k.LibraryFileName
        disabled           = $k.Disabled
        settingsChangeTime = $k.SettingsChangeTime
    }
    $dlls = [ordered]@{}
    foreach ($arch in '64', '32') {
        $p = "C:\ProgramData\Windhawk\Engine\Mods\$arch\$($k.LibraryFileName)"
        $exists = Test-Path -LiteralPath $p
        $dlls[$arch] = [ordered]@{ path = $p; exists = $exists; sha256 = ($(if ($exists) { Get-Sha $p })) }
    }
    $state['dlls'] = $dlls
    $state['modsSourceSha256'] = $(if (Test-Path $src) { Get-Sha $src })
    return $state
}

function Get-MappedDlls {
    $found = @{}
    foreach ($name in 'explorer', 'WindowsTerminal', 'conhost') {
        foreach ($p in Get-Process -Name $name -ErrorAction SilentlyContinue) {
            foreach ($m in $p.Modules) {
                if ($m.ModuleName -like 'translucent-windows*') {
                    $found["$name $($p.Id)"] = $m.ModuleName
                }
            }
        }
    }
    return $found
}

function Write-Receipt([string]$Name, $Data) {
    $path = Join-Path $rep $Name
    $Data | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $path -Encoding UTF8
    Write-Output "receipt: $path"
}

function Set-FixState {
    Copy-Item -LiteralPath $dev -Destination $src -Force
    if ((Get-Sha $src) -ne $forkHash) { throw 'ModsSource readback does not match the reviewed fork source.' }

    Set-ItemProperty -LiteralPath $modKey -Name LibraryFileName -Value $fixDll -Type String
    Set-ItemProperty -LiteralPath $modKey -Name Version -Value '1.8.3' -Type String
    # -UFormat %s in PS 5.1 encodes local time as UTC (8h skew here); use the real UTC epoch.
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    Set-ItemProperty -LiteralPath $modKey -Name SettingsChangeTime -Value $now -Type DWord
}

try {
    switch ($Action) {

        'Audit' {
            Write-Output (Get-ModState | ConvertTo-Json -Depth 6)
            Write-Output (Get-MappedDlls | ConvertTo-Json)
        }

        'Install' {
            if ((Get-Sha $src) -ne $stockHash) { throw 'ModsSource is not the stock 1.8.2 the revert left behind. Inspect before installing.' }
            if ((Get-Sha $dev) -ne $forkHash)  { throw 'Workspace fork source does not match the reviewed round-5 copy.' }

            foreach ($arch in '64', '32') {
                $p = "C:\ProgramData\Windhawk\Engine\Mods\$arch\$fixDll"
                if (-not (Test-Path -LiteralPath $p)) { throw "missing $p" }
            }
            if ((Get-Sha "C:\ProgramData\Windhawk\Engine\Mods\64\$fixDll") -ne $dll64Hash) { throw 'x64 DLL hash does not match the round-5 receipt.' }

            # Back up the drifted state first: registry key plus the stock source.
            cmd.exe /d /c "reg.exe export HKLM\SOFTWARE\Windhawk\Engine\Mods\translucent-windows ""$regBackup"" /y >nul 2>&1"
            if ($LASTEXITCODE -ne 0) { throw "reg export exited $LASTEXITCODE." }
            Copy-Item -LiteralPath $src -Destination $stockSrcCopy -Force
            if ((Get-Sha $stockSrcCopy) -ne $stockHash) { throw 'Stock source backup hash mismatch.' }

            $before = Get-ModState
            Set-FixState
            Start-Sleep -Seconds 6   # engine watches SettingsChangeTime and hot-reloads the mod

            $after = Get-ModState
            if ($after.libraryFileName -ne $fixDll)   { throw "LibraryFileName readback is $($after.libraryFileName)." }
            if ($after.version -ne '1.8.3')           { throw "Version readback is $($after.version)." }
            if ($after.dlls['64'].sha256 -ne $dll64Hash) { throw 'x64 DLL hash changed on disk.' }
            if ([int]$after.disabled -ne 0)           { throw 'Mod is disabled.' }

            # Stage pristine copies for the drift guard: both DLLs and a full key export.
            foreach ($arch in '64', '32') {
                $dst = Join-Path $guardDir $arch
                New-Item -ItemType Directory -Path $dst -Force | Out-Null
                Copy-Item -LiteralPath "C:\ProgramData\Windhawk\Engine\Mods\$arch\$fixDll" -Destination (Join-Path $dst $fixDll) -Force
            }
            if ((Get-Sha (Join-Path $guardDir "64\$fixDll")) -ne $dll64Hash) { throw 'staged x64 guard copy hash mismatch.' }
            $staged32 = Get-Sha (Join-Path $guardDir "32\$fixDll")
            $pristineReg = Join-Path $guardDir 'translucent-windows-1.8.3-256343.reg'
            cmd.exe /d /c "reg.exe export HKLM\SOFTWARE\Windhawk\Engine\Mods\translucent-windows ""$pristineReg"" /y >nul 2>&1"
            if ($LASTEXITCODE -ne 0) { throw "pristine key export exited $LASTEXITCODE." }

            $mapped = Get-MappedDlls
            Write-Receipt 'receipt-reapply.json' ([ordered]@{
                action       = 'install'
                timestamp    = (Get-Date -Format o)
                reason       = 'third unattributed revert to stock 1.8.2 (fresh build 137900) at 2026-10-13T23:54Z; source save landed 4 ms before Windhawk userprofile.json rewrite'
                before       = $before
                after        = $after
                mappedDlls   = $mapped
                staged       = [ordered]@{ guardDir = $guardDir; dll32Sha256 = $staged32; pristineReg = $pristineReg }
                rollback     = $regBackup
            })
            Write-Output "installed: $($after.version) / $($after.libraryFileName)"
            Write-Output "staged: $guardDir (x86 sha256 $staged32)"
            Write-Output "mapped: $($mapped | ConvertTo-Json -Compress)"
        }

        'Rollback' {
            if (-not (Test-Path -LiteralPath $regBackup))    { throw "missing backup $regBackup" }
            if (-not (Test-Path -LiteralPath $stockSrcCopy)) { throw "missing backup $stockSrcCopy" }

            cmd.exe /d /c "reg.exe import ""$regBackup"" >nul 2>&1"
            if ($LASTEXITCODE -ne 0) { throw "reg import exited $LASTEXITCODE." }
            Copy-Item -LiteralPath $stockSrcCopy -Destination $src -Force
            # -UFormat %s in PS 5.1 encodes local time as UTC (8h skew here); use the real UTC epoch.
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
            Set-ItemProperty -LiteralPath $modKey -Name SettingsChangeTime -Value $now -Type DWord

            $after = Get-ModState
            Write-Receipt 'receipt-rollback.json' ([ordered]@{
                action = 'rollback'; timestamp = (Get-Date -Format o); after = $after
            })
            Write-Output "rolled back: $($after.version) / $($after.libraryFileName)"
        }
    }
}
catch {
    $msg = "$Action failed at line $($_.InvocationInfo.ScriptLineNumber): $($_.Exception.Message)"
    Set-Content -LiteralPath (Join-Path $rep "error-$Action.txt") -Value $msg -Encoding UTF8
    Write-Error $msg
    exit 1
}
