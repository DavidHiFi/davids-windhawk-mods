<#
.SYNOPSIS
Move the translucent-windows fork (local@translucent-windows 1.8.3) to the Translucent
Windows Plus id (local@translucent-windows-plus), then retire the old id.

WHY THIS SCRIPT EXISTS
Same proven recipe as scripts\2026-10-15-translucent-windows-local-install.ps1: build
x64 and x86 with the bundled clang, pass the mod id through a force-included header,
clone the registry key, point LibraryFileName at the new DLLs, drop the source into
ModsSource, then remove the old key and source. The drift guard is suspended and
disabled before the cutover, so it cannot restore the old id while the move runs.
The new guard is written by step 9 and installed separately (-Action InstallGuard on
scripts\2026-10-24-translucent-windows-plus-guard.ps1) after the readback passes.

Actions: Install | Rollback. Run elevated through
  H:\System Configuration\scripts\Invoke-Elevated.ps1
Engine libraries are read from Engine\2.0.0 (the 2.0.0_1 folder no longer exists).
#>
[CmdletBinding()]
param(
    [ValidateSet('Install', 'Rollback')]
    [string]$Action = 'Install'
)

$ErrorActionPreference = 'Stop'

$ws         = 'H:\Windhawk Configuration'
$date       = '2026-10-24'
$version    = '1.8.3'
$oldId      = 'local@translucent-windows'
$newId      = 'local@translucent-windows-plus'
$oldDll     = 'local@translucent-windows_1.8.3_2.dll'
$newDll     = 'local@translucent-windows-plus_1.8.3_1.dll'
$oldKeyReg  = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$oldId"
$newKeyReg  = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$newId"
$oldKey     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$oldId"
$newKey     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$newId"
$modsSource = 'C:\ProgramData\Windhawk\ModsSource'
$oldSrc     = Join-Path $modsSource 'local@translucent-windows.wh.cpp'
$newSrc     = Join-Path $modsSource 'local@translucent-windows-plus.wh.cpp'
$mods64     = 'C:\ProgramData\Windhawk\Engine\Mods\64'
$mods32     = 'C:\ProgramData\Windhawk\Engine\Mods\32'
$devDir     = Join-Path $ws 'Windhawk\translucent-windows-plus'
$staged     = Join-Path $devDir 'local@translucent-windows-plus.wh.cpp'
$buildDir   = Join-Path $devDir 'build-local'
$guardDir   = Join-Path $devDir 'guard'
$bkd        = Join-Path $ws "backups\$date-translucent-windows-plus"
$rep        = Join-Path $ws "reports\$date-translucent-windows-plus"
$log        = Join-Path $rep 'migrate-log.txt'
$compiler   = 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe'
$incDir     = 'C:\Program Files\Windhawk\Compiler\include'
$engineRoot = 'C:\Program Files\Windhawk\Engine\2.0.0'
$cli        = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$suspend    = 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend'
$taskName   = 'TranslucentWindowsGuard'
$oldGuard   = Join-Path $ws 'scripts\2026-10-15-translucent-windows-guard.ps1'
$newGuard   = Join-Path $ws 'scripts\2026-10-24-translucent-windows-plus-guard.ps1'
$guardTpl   = $oldGuard

function Write-Log([string]$m) {
    Add-Content -LiteralPath $log -Value ("{0} {1}" -f (Get-Date -Format o), $m) -Encoding UTF8
    Write-Output $m
}

function Get-Sha([string]$p) { (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

function Stop-Guard {
    New-Item -ItemType Directory -Path (Split-Path $suspend -Parent) -Force | Out-Null
    Set-Content -LiteralPath $suspend -Value ("suspended by migrate " + (Get-Date -Format o)) -Encoding UTF8
    if (Get-ScheduledTask -TaskName $taskName -ErrorAction SilentlyContinue) {
        Disable-ScheduledTask -TaskName $taskName | Out-Null
    }
    Write-Log 'guard suspended (marker written) and task disabled'
}

New-Item $rep -ItemType Directory -Force | Out-Null
New-Item $bkd -ItemType Directory -Force | Out-Null

switch ($Action) {

    'Install' {
        Write-Log '=== migrate to translucent-windows-plus: install start ==='

        # 0. prechecks
        if ((Get-Service Windhawk -ErrorAction Stop).Status -ne 'Running') { throw 'Windhawk service not running' }
        foreach ($p in @($staged, $compiler, "$incDir\windhawk_api.h", "$engineRoot\64\windhawk.lib", "$engineRoot\32\windhawk.lib", $cli, "$bkd\before-local-translucent-windows.reg")) {
            if (-not (Test-Path -LiteralPath $p)) { throw "missing: $p" }
        }
        if (-not (Test-Path $oldKey)) { throw 'old key not found; nothing to migrate' }
        if (Test-Path $newKey) { throw "new key already exists: $newKey" }
        if (Test-Path $newSrc) { throw 'new source already in ModsSource' }
        if ((Get-Sha $staged) -eq (Get-Sha $oldSrc)) { throw 'staged source is identical to the old source; metadata edits missing' }
        $oldCount = (Get-Item "$oldKey\Settings").ValueCount
        Write-Log "prechecks ok (old settings=$oldCount)"

        # 1. back up the live DLLs and the old source
        Copy-Item "$mods64\$oldDll" (Join-Path $bkd "x64-$oldDll") -Force
        Copy-Item "$mods32\$oldDll" (Join-Path $bkd "x86-$oldDll") -Force
        Copy-Item $oldSrc (Join-Path $bkd 'local@translucent-windows.wh.cpp.before') -Force
        Write-Log 'live DLLs and old source backed up'

        # 2. stop the guard so it cannot restore the old id during the move
        Stop-Guard

        # 3. build x64 and x86 with the bundled clang; the mod id comes from a force-included header
        New-Item $buildDir -ItemType Directory -Force | Out-Null
        $modIdHeader = Join-Path $buildDir 'translucent-windows-plus-modid.h'
        Set-Content -LiteralPath $modIdHeader -Value ('#define WH_MOD_ID L"{0}"' -f $newId) -Encoding Ascii
        $targets = @(
            [pscustomobject]@{ Arch = 'x86_64-w64-mingw32'; Lib = "$engineRoot\64\windhawk.lib"; Out = Join-Path $buildDir 'local@translucent-windows-plus_1.8.3_1_64.dll' },
            [pscustomobject]@{ Arch = 'i686-w64-mingw32';   Lib = "$engineRoot\32\windhawk.lib"; Out = Join-Path $buildDir 'local@translucent-windows-plus_1.8.3_1_32.dll' }
        )
        foreach ($t in $targets) {
            Write-Log "compiling $(Split-Path $t.Out -Leaf) ($($t.Arch))"
            $compileArgs = @(
                '-std=c++23', '-O2', '-shared',
                '-target', $t.Arch,
                '-DUNICODE', '-D_UNICODE',
                '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00', '-D_WIN32_IE=0x0A00', '-DNTDDI_VERSION=0x0A000008',
                '-D__USE_MINGW_ANSI_STDIO=0', '-DWH_MOD', '-fms-extensions',
                '-Wno-microsoft-template', '-Wno-microsoft-enum-forward-reference',
                '-Wno-pragma-pack', '-Wno-pragma-system-header-outside-header',
                '-Wno-unknown-pragmas', '-Wno-invalid-offsetof',
                '-include', $modIdHeader, '-include', 'windhawk_api.h', '-I', $incDir,
                '-Wl,--export-all-symbols', '-Wl,--allow-multiple-definition',
                $staged, $t.Lib,
                '-ld2d1', '-ldwrite', '-ldwmapi', '-luxtheme', '-lcomctl32', '-lgdi32',
                '-luser32', '-lole32', '-ladvapi32', '-lshlwapi', '-lversion', '-lmsimg32',
                '-lshcore', '-loleaut32', '-luuid', '-lwindowscodecs',
                '-ffp-exception-behavior=maytrap',
                '-o', $t.Out
            )
            $cout = & $compiler @compileArgs 2>&1
            $cout | Select-Object -Last 15 | ForEach-Object { Write-Log "clang: $_" }
            if ($LASTEXITCODE -ne 0) { throw "clang failed for $($t.Arch) (exit $LASTEXITCODE)" }
            if (-not (Test-Path $t.Out)) { throw "no output DLL: $($t.Out)" }
            Write-Log "built $(Split-Path $t.Out -Leaf) ($((Get-Item $t.Out).Length) bytes)"
        }
        $build64 = Join-Path $buildDir 'local@translucent-windows-plus_1.8.3_1_64.dll'
        $build32 = Join-Path $buildDir 'local@translucent-windows-plus_1.8.3_1_32.dll'

        # 4. place the DLLs and the new source. A DLL that is already mapped by running processes
        # cannot be overwritten; the in-place copy (same code, same id) is kept, and step 9 hashes
        # whichever file is actually in place.
        foreach ($pair in @(@{ Src = $build64; Dst = "$mods64\$newDll" }, @{ Src = $build32; Dst = "$mods32\$newDll" })) {
            try {
                Copy-Item -LiteralPath $pair.Src -Destination $pair.Dst -Force -ErrorAction Stop
                Write-Log "placed $(Split-Path $pair.Dst -Leaf)"
            } catch {
                if (-not (Test-Path -LiteralPath $pair.Dst)) { throw }
                Write-Log "kept in-place DLL (copy refused, file is mapped): $($pair.Dst)"
            }
        }
        Copy-Item $staged $newSrc -Force
        Write-Log 'new source placed'

        # 5. clone the key to the new id and point it at the new DLLs
        reg.exe copy $oldKeyReg $newKeyReg /s /f | Out-Null
        if (-not (Test-Path $newKey)) { throw 'reg copy failed' }
        Set-ItemProperty -Path $newKey -Name 'LibraryFileName' -Value $newDll -Type String
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        Set-ItemProperty -Path $newKey -Name 'SettingsChangeTime' -Value $now -Type DWord
        $p = Get-ItemProperty $newKey
        if ($p.Version -ne $version) { throw "version mismatch: $($p.Version)" }
        if ($p.Disabled -ne 0)       { throw 'new mod disabled' }
        if ($p.Include -ne '*')      { throw "include mismatch: $($p.Include)" }
        $newCount = (Get-Item "$newKey\Settings").ValueCount
        if ($newCount -ne $oldCount) { throw "settings count mismatch: old=$oldCount new=$newCount" }
        Write-Log "new key: lib=$($p.LibraryFileName) version=$($p.Version) settings=$newCount"

        # 6. retire the old key, source and DLL
        reg.exe delete $oldKeyReg /f | Out-Null
        if (Test-Path $oldKey) { throw 'old key still present after delete' }
        Remove-Item -LiteralPath $oldSrc -Force
        Remove-Item -LiteralPath "$mods64\$oldDll", "$mods32\$oldDll" -Force -ErrorAction SilentlyContinue
        $stillThere = @("$mods64\$oldDll", "$mods32\$oldDll") | Where-Object { Test-Path $_ }
        if ($stillThere) { Write-Log ("old DLL kept (still mapped by running processes): " + ($stillThere -join ', ')) }
        Write-Log 'old key and source retired'

        # 7. read back through the engine
        Start-Sleep -Seconds 3
        $listJson = (& $cli mod list --json 2>&1) -join "`n"
        Set-Content -LiteralPath (Join-Path $rep 'mod-list-after-install.json') -Value $listJson -Encoding UTF8
        if ($listJson -notmatch [regex]::Escape('translucent-windows-plus')) { throw 'new id not present in mod list' }
        Write-Log 'engine mod list contains translucent-windows-plus'

        # 8. pristine copies for the new guard
        New-Item (Join-Path $guardDir '64') -ItemType Directory -Force | Out-Null
        New-Item (Join-Path $guardDir '32') -ItemType Directory -Force | Out-Null
        Copy-Item "$mods64\$newDll" (Join-Path $guardDir "64\$newDll") -Force
        Copy-Item "$mods32\$newDll" (Join-Path $guardDir "32\$newDll") -Force
        reg.exe export $newKeyReg (Join-Path $guardDir 'local@translucent-windows-plus-1.8.3-1.reg') /y | Out-Null

        # 9. generate the new guard from the old one, with the new constants
        $hash64 = Get-Sha "$mods64\$newDll"
        $hash32 = Get-Sha "$mods32\$newDll"
        $srcHash = Get-Sha $staged
        $gText = Get-Content -LiteralPath $guardTpl -Raw
        $pairs = @(
            @('Windhawk\translucent-windows\local@translucent-windows.wh.cpp', 'Windhawk\translucent-windows-plus\local@translucent-windows-plus.wh.cpp'),
            @('ModsSource\local@translucent-windows.wh.cpp', 'ModsSource\local@translucent-windows-plus.wh.cpp'),
            @('Mods\local@translucent-windows''', 'Mods\local@translucent-windows-plus'''),
            @('local@translucent-windows_1.8.3_2.dll', 'local@translucent-windows-plus_1.8.3_1.dll'),
            @('local@translucent-windows-1.8.3-2.reg', 'local@translucent-windows-plus-1.8.3-1.reg'),
            @('8280803C303E8B8A931AA5D4BD3B19C38ADC4C7B80A53E8E31518F66AAC5F809', $srcHash),
            @('7665FBCB07A157AAE201059D49C39929F4251401A41BCED272F7A44BC8987E57', $hash64),
            @('52C48DF65A282BEB415C859E18741420BCF25F28A5A70318B43F7903D01B37D3', $hash32),
            @('Windhawk\translucent-windows\guard', 'Windhawk\translucent-windows-plus\guard'),
            @('reports\2026-10-15-translucent-windows-guard', 'reports\2026-10-24-translucent-windows-plus-guard')
        )
        foreach ($pr in $pairs) {
            if (-not $gText.Contains($pr[0])) { throw "guard template is missing: $($pr[0])" }
            $gText = $gText.Replace($pr[0], $pr[1])
        }
        Set-Content -LiteralPath $newGuard -Value $gText -Encoding UTF8
        Write-Log "new guard script written: $newGuard"

        # 10. receipt
        $receipt = [ordered]@{
            action            = 'migrate-to-translucent-windows-plus'
            date              = $date
            oldId             = $oldId
            newId             = $newId
            newLibraryFile   = $newDll
            settingsCount     = $newCount
            stagedSourceSha256 = $srcHash
            dll64Sha256       = $hash64
            dll32Sha256       = $hash32
            guardState        = 'suspended and disabled until InstallGuard runs'
            backupDir         = $bkd
        }
        $receipt | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $rep 'receipt-install.json') -Encoding UTF8
        Write-Log '=== install done. guard still suspended. next: InstallGuard on the new guard script ==='
    }

    'Rollback' {
        Write-Log '=== rollback to translucent-windows start ==='
        Stop-Guard
        if (Test-Path $newKey) { reg.exe delete $newKeyReg /f | Out-Null }
        Remove-Item -LiteralPath $newSrc -Force -ErrorAction SilentlyContinue
        Remove-Item -LiteralPath "$mods64\$newDll", "$mods32\$newDll" -Force -ErrorAction SilentlyContinue
        reg.exe import (Join-Path $bkd 'before-local-translucent-windows.reg') | Out-Null
        Copy-Item (Join-Path $bkd 'local@translucent-windows.wh.cpp.before') $oldSrc -Force
        Copy-Item (Join-Path $bkd "x64-$oldDll") "$mods64\$oldDll" -Force
        Copy-Item (Join-Path $bkd "x86-$oldDll") "$mods32\$oldDll" -Force
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        Set-ItemProperty -Path $oldKey -Name 'SettingsChangeTime' -Value $now -Type DWord
        $p = Get-ItemProperty $oldKey
        Write-Log "rollback key: lib=$($p.LibraryFileName) version=$($p.Version) disabled=$($p.Disabled)"
        & $oldGuard -Action InstallGuard | Out-Null
        Write-Log 'old guard re-registered; suspend marker cleared'
    }
}
