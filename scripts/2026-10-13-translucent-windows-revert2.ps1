<#
.SYNOPSIS
Reinstall the reviewed translucent-windows 1.8.3 build 256343 after the second
unattributed revert to stock 1.8.2 (2026-10-13 11:58, build 598230).

Stock 1.8.2 skips CASCADIA_HOSTING_WINDOW_CLASS in EnableBlurBehind, so Windows
Terminal falls back to its own profile accent: opacity 0 with acrylic off, which
is a plain transparent gradient - a see-through window with no blur.

Actions: Audit (read only) | Install (backup + restore 1.8.3/256343) | Rollback.
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
$bk        = Join-Path $ws 'backups\2026-10-13\translucent-windows-revert2'
$rep       = Join-Path $ws 'reports\2026-10-13-terminal-titlebar-revert2'
$src       = 'C:\ProgramData\Windhawk\ModsSource\translucent-windows.wh.cpp'
$modKey    = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'

$forkHash      = '70B64AF483BEB86C91B5D34213380BBE25579FD778C5BD2B15C44CFF5B6D851A'  # round-5 reviewed source
$stockHash     = '0F88018DB7C22FD37484C763182BC5587BDB21AD4E869C5D7099F6FAAEF3FCD1'  # stock 1.8.2, current ModsSource
$dll64Hash     = 'D284A5E33789960090D873B55B34F9DADF97935082944B9D724EBC8D1540C7D6'  # from the round-5 receipt
$fixDll        = 'translucent-windows_1.8.3_256343.dll'
$regBackup     = Join-Path $bk 'translucent-windows-before-revert2.reg'
$stockSrcCopy  = Join-Path $bk 'ModsSource-reverted-1.8.2-598230.wh.cpp'

# backups\ and reports\ are written by the elevated run; this session's sandbox
# is denied writes to both singleton trees (2026-10-13, same as the explorer-speed run).
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
    # Which translucent-windows DLL each live host process has mapped.
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
    $now = [int][double]::Parse((Get-Date -UFormat %s))
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

            # Back up the reverted state first: registry key plus the stock source.
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

            $mapped = Get-MappedDlls
            Write-Receipt 'receipt-reapply.json' ([ordered]@{
                action       = 'install'
                timestamp    = (Get-Date -Format o)
                reason       = 'second unattributed revert to stock 1.8.2 (build 598230) at 2026-10-13 11:58; Terminal lost accent blur and fell back to its own opacity-0 transparent gradient'
                before       = $before
                after        = $after
                mappedDlls   = $mapped
                rollback     = $regBackup
            })
            Write-Output "installed: $($after.version) / $($after.libraryFileName)"
            Write-Output "mapped: $($mapped | ConvertTo-Json -Compress)"
        }

        'Rollback' {
            if (-not (Test-Path -LiteralPath $regBackup))    { throw "missing backup $regBackup" }
            if (-not (Test-Path -LiteralPath $stockSrcCopy)) { throw "missing backup $stockSrcCopy" }

            cmd.exe /d /c "reg.exe import ""$regBackup"" >nul 2>&1"
            if ($LASTEXITCODE -ne 0) { throw "reg import exited $LASTEXITCODE." }
            Copy-Item -LiteralPath $stockSrcCopy -Destination $src -Force
            $now = [int][double]::Parse((Get-Date -UFormat %s))
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
