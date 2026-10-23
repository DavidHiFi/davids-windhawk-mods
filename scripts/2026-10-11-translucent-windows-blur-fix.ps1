# Installs or rolls back the local translucent-windows 1.8.3 blur fix.
#
# Install: ModsSource must still match the 1.8.2 backup. The reviewed patched
# source in Windhawk\translucent-windows is copied in and compiled with
# windhawk-cli, then the registry and the loaded DLL are read back.
# Rollback: the 1.8.2 source and the registry values come back from the backup.
#
# Run through H:\System Configuration\scripts\Invoke-Elevated.ps1 (ModsSource and
# HKLM need admin). Writes a receipt JSON into reports\.

param(
    [ValidateSet('Install', 'Rollback', 'Reapply')]
    [string]$Action = 'Install'
)

$ErrorActionPreference = 'Stop'

$ws      = 'H:\Windhawk Configuration'
$dev     = Join-Path $ws 'Windhawk\translucent-windows\translucent-windows.wh.cpp'
$bk      = Join-Path $ws 'backups\2026-10-11\translucent-windows-blur-fix'
$rep     = Join-Path $ws 'reports\2026-10-11-translucent-windows-blur-fix'
$src     = 'C:\ProgramData\Windhawk\ModsSource\translucent-windows.wh.cpp'
$cli     = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$modKey  = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'
$regFile = Join-Path $bk 'translucent-windows-before.reg'
$origSrc = Join-Path $bk 'translucent-windows-1.8.2.wh.cpp'
$before  = Get-Content -LiteralPath (Join-Path $bk 'before.json') -Raw | ConvertFrom-Json

$origHash  = '0F88018DB7C22FD37484C763182BC5587BDB21AD4E869C5D7099F6FAAEF3FCD1'
$fixedHash = 'B1B90657902323F5A0AF79D13BF66BC66CAAA9792E2B733761B44B837413DB0B'

if (-not (Test-Path -LiteralPath $rep)) { New-Item -ItemType Directory -Path $rep | Out-Null }

function Get-Sha([string]$Path) {
    return (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash
}

function Get-ModState {
    $k = Get-ItemProperty -LiteralPath $modKey
    $state = [ordered]@{
        version            = $k.Version
        libraryFileName    = $k.LibraryFileName
        include            = $k.Include
        exclude            = $k.Exclude
        excludeCustom      = $k.ExcludeCustom
        disabled           = $k.Disabled
        settingsChangeTime = $k.SettingsChangeTime
    }
    $dlls = [ordered]@{}
    foreach ($arch in '64', '32') {
        $p = "C:\ProgramData\Windhawk\Engine\Mods\$arch\$($k.LibraryFileName)"
        $exists = Test-Path -LiteralPath $p
        $hash = $null
        if ($exists) { $hash = Get-Sha $p }
        $dlls[$arch] = [ordered]@{ path = $p; exists = $exists; sha256 = $hash }
    }
    $state['dlls'] = $dlls
    return $state
}

function Import-RegFile([string]$Path) {
    # reg.exe reports success on stderr, which PowerShell would turn into a terminating
    # error under ErrorActionPreference=Stop. Run it through cmd so only the exit code counts.
    cmd.exe /d /c "reg.exe import ""$Path"" >nul 2>&1"
    if ($LASTEXITCODE -ne 0) { throw "reg import exited $LASTEXITCODE for $Path." }
}

function Get-LoadedFixModules {
    # Which translucent-windows DLL the running explorer.exe has mapped.
    $names = @()
    foreach ($p in Get-Process -Name explorer -ErrorAction SilentlyContinue) {
        foreach ($m in $p.Modules) {
            if ($m.ModuleName -like 'translucent-windows*') { $names += $m.FileName }
        }
    }
    return @($names | Sort-Object -Unique)
}

function Write-Receipt([string]$Name, $Data) {
    $path = Join-Path $rep $Name
    $Data | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $path -Encoding UTF8
    Write-Output "receipt: $path"
}

function Install-Fix {
    if ((Get-Sha $src) -ne $origHash) {
        throw 'ModsSource no longer matches the 1.8.2 backup. Stop and inspect it before installing.'
    }
    if ((Get-Sha $dev) -ne $fixedHash) {
        throw "Patched source $dev does not match the reviewed copy."
    }

    Copy-Item -LiteralPath $dev -Destination $src -Force
    if ((Get-Sha $src) -ne $fixedHash) { throw 'ModsSource readback does not match the patched source.' }

    $out = Join-Path $rep 'compile-out.txt'
    $err = Join-Path $rep 'compile-err.txt'
    $proc = Start-Process -FilePath $cli -ArgumentList 'mod compile translucent-windows' `
        -WindowStyle Hidden -Wait -PassThru -RedirectStandardOutput $out -RedirectStandardError $err
    if ($proc.ExitCode -ne 0) { throw "windhawk-cli mod compile exited $($proc.ExitCode). See $out and $err." }

    $after = Get-ModState
    if ($after.version -ne '1.8.3') { throw "Version readback is $($after.version), expected 1.8.3." }
    if ($after.libraryFileName -eq $before.libraryFileName) { throw 'LibraryFileName did not change.' }
    foreach ($arch in '64', '32') {
        if (-not $after.dlls[$arch].exists) { throw "$arch-bit DLL missing: $($after.dlls[$arch].path)" }
    }
    if ($after.include -ne $before.include -or $after.excludeCustom -ne $before.excludeCustom -or
        [int]$after.disabled -ne [int]$before.disabled) {
        throw 'Include, ExcludeCustom or Disabled changed during compile.'
    }

    # Make the engine reload the mod in live processes, then read what explorer maps.
    $now = [int64](([DateTime]::UtcNow) - [DateTime]::new(1970, 1, 1)).TotalSeconds
    Set-ItemProperty -LiteralPath $modKey -Name SettingsChangeTime -Value ([int]$now) -Type DWord
    Start-Sleep -Seconds 5
    $loaded = Get-LoadedFixModules

    Write-Receipt 'receipt-install.json' ([ordered]@{
        action          = 'install'
        timestamp       = (Get-Date -Format o)
        sourceBefore    = $origHash
        sourceAfter     = $fixedHash
        compileExitCode = $proc.ExitCode
        before          = $before
        after           = $after
        loadedInExplorer = $loaded
    })
    Write-Output "installed: version $($after.version), $($after.libraryFileName)"
    Write-Output "loaded in explorer.exe: $($loaded -join ', ')"
}

function Restore-Original {
    if ((Get-Sha $origSrc) -ne $origHash) { throw 'Backup source hash does not match 1.8.2.' }

    Copy-Item -LiteralPath $origSrc -Destination $src -Force
    if ((Get-Sha $src) -ne $origHash) { throw 'ModsSource readback does not match the 1.8.2 source.' }

    Import-RegFile $regFile

    # The restored SettingsChangeTime is older than the current one, so bump it to make the engine reload.
    $now = [int64](([DateTime]::UtcNow) - [DateTime]::new(1970, 1, 1)).TotalSeconds
    Set-ItemProperty -LiteralPath $modKey -Name SettingsChangeTime -Value ([int]$now) -Type DWord

    $after = Get-ModState
    if ($after.version -ne $before.version -or $after.libraryFileName -ne $before.libraryFileName) {
        throw 'Registry readback does not match before.json.'
    }
    foreach ($arch in '64', '32') {
        if (-not $after.dlls[$arch].exists) { throw "$arch-bit DLL missing: $($after.dlls[$arch].path)" }
    }

    Write-Receipt 'receipt-rollback.json' ([ordered]@{
        action       = 'rollback'
        timestamp    = (Get-Date -Format o)
        sourceAfter  = $origHash
        after        = $after
    })
    Write-Output "rolled back: version $($after.version), $($after.libraryFileName)"
}

function Restore-Fix {
    # Puts the reviewed source and the fixed registry state back. No recompile:
    # the 1.8.3 DLL is still on disk and may be mapped into explorer.exe.
    $fixReg = Join-Path $rep 'fix-state.reg'
    if ((Get-Sha $dev) -ne $fixedHash) { throw "Patched source $dev does not match the reviewed copy." }

    Copy-Item -LiteralPath $dev -Destination $src -Force
    if ((Get-Sha $src) -ne $fixedHash) { throw 'ModsSource readback does not match the patched source.' }

    Import-RegFile $fixReg

    $now = [int64](([DateTime]::UtcNow) - [DateTime]::new(1970, 1, 1)).TotalSeconds
    Set-ItemProperty -LiteralPath $modKey -Name SettingsChangeTime -Value ([int]$now) -Type DWord
    Start-Sleep -Seconds 5

    $after = Get-ModState
    if ($after.version -ne '1.8.3') { throw "Version readback is $($after.version), expected 1.8.3." }
    if (-not $after.dlls['64'].exists) { throw "64-bit DLL missing: $($after.dlls['64'].path)" }
    $loaded = Get-LoadedFixModules

    Write-Receipt 'receipt-reapply.json' ([ordered]@{
        action           = 'reapply'
        timestamp        = (Get-Date -Format o)
        sourceAfter      = $fixedHash
        after            = $after
        loadedInExplorer = $loaded
    })
    Write-Output "reapplied: version $($after.version), $($after.libraryFileName)"
    Write-Output "loaded in explorer.exe: $($loaded -join ', ')"
}

try {
    switch ($Action) {
        'Install'  { Install-Fix }
        'Rollback' { Restore-Original }
        'Reapply'  { Restore-Fix }
    }
} catch {
    # The elevated launcher keeps stdout only, so leave the reason in reports\ as well.
    $msg = "$Action failed at line $($_.InvocationInfo.ScriptLineNumber): $($_.Exception.Message)"
    Set-Content -LiteralPath (Join-Path $rep "error-$Action.txt") -Value $msg -Encoding UTF8
    Write-Output $msg
    exit 1
}
