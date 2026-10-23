<#
.SYNOPSIS
Build and direct-install the translucent-windows fork under the local@ id.

WHY THIS SCRIPT EXISTS
The windhawk-cli of this build (2.0.0-alpha.7) rejects '@' in mod ids
("Mod id must only contain 0-9, a-z, and a hyphen") even though the engine
itself runs the machine's 14 existing local@ mods fine - so the migration's
`mod install --file` step failed AFTER the old id had already been removed
cleanly (which is the part that kills the phantom update offer). This script
finishes the migration the proven 2026-10-04 way: build x64+x86 with the
bundled clang (mod id via a force-included header, -DWH_MOD only), place the
DLLs, clone the backed-up key with reg copy, point LibraryFileName at the new
DLLs, and drop the source into ModsSource. The engine picks the mod up live.

The source is the staged local@translucent-windows.wh.cpp from the migration
(identical to the reviewed 1.8.3 blur-fix fork except the @id line); settings
come from the migration backup's full key export (156 values + ExcludeCustom).

Actions: Install | Rollback. Run elevated:
  powershell.exe -NoProfile -ExecutionPolicy Bypass -File <this> -Action Install
#>
[CmdletBinding()]
param(
    [ValidateSet('Install', 'Rollback')]
    [string]$Action = 'Install'
)

$ErrorActionPreference = 'Stop'

$ws         = 'H:\Windhawk Configuration'
$oldId      = 'translucent-windows'
$newId      = 'local@translucent-windows'
$version    = '1.8.3'
$newDll     = 'local@translucent-windows_1.8.3_1.dll'
$oldKeyReg  = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$oldId"
$newKeyReg  = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$newId"
$oldKey     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$oldId"
$newKey     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$newId"
$modsSource = 'C:\ProgramData\Windhawk\ModsSource'
$devDir     = Join-Path $ws 'Windhawk\translucent-windows'
$staged     = Join-Path $devDir 'local@translucent-windows.wh.cpp'
$buildDir   = Join-Path $devDir 'build-local'
$guardDir   = Join-Path $devDir 'guard'
$bkd        = Join-Path $ws 'backups\2026-10-15\translucent-windows-id-migration'
$rep        = Join-Path $ws 'reports\2026-10-15-translucent-windows-id-migration'
$log        = Join-Path $rep 'local-install.log'
$compiler   = 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe'
$incDir     = 'C:\Program Files\Windhawk\Compiler\include'
$engineRoot = 'C:\Program Files\Windhawk\Engine\2.0.0_1'
$mods64     = 'C:\ProgramData\Windhawk\Engine\Mods\64'
$mods32     = 'C:\ProgramData\Windhawk\Engine\Mods\32'
$cli        = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$suspend    = 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend'
$profileJ   = 'C:\ProgramData\Windhawk\userprofile.json'

function Write-Log([string]$m) {
    Add-Content -LiteralPath $log -Value ("{0} {1}" -f (Get-Date -Format o), $m) -Encoding UTF8
    Write-Output $m
}

function Get-Sha([string]$p) { (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

function Get-ProfileModNames {
    if (Test-Path $profileJ) {
        try {
            $mods = (Get-Content $profileJ -Raw | ConvertFrom-Json).mods
            if ($mods) { return @($mods.PSObject.Properties.Name) }
        } catch { }
    }
    return @()
}

New-Item $rep -ItemType Directory -Force | Out-Null

switch ($Action) {

    'Install' {
        Write-Log '=== local build + install start ==='

        # 0. prechecks
        if ((Get-Service Windhawk -ErrorAction Stop).Status -ne 'Running') { throw 'Windhawk service not running' }
        foreach ($p in @($staged, "$bkd\translucent-windows-before-migration.reg", $compiler, "$incDir\windhawk_api.h", "$engineRoot\64\windhawk.lib", "$engineRoot\32\windhawk.lib")) {
            if (-not (Test-Path $p)) { throw "missing: $p" }
        }
        if (Test-Path $newKey) { throw "new key already exists: $newKey" }
        if (Test-Path "$modsSource\local@translucent-windows.wh.cpp") { throw 'new source already in ModsSource' }
        Write-Log 'prechecks ok'

        # 1. repair the migration backup's arch DLL names (x64 copy was overwritten there)
        Copy-Item "$guardDir\64\translucent-windows_1.8.3_256343.dll" "$bkd\translucent-windows_1.8.3_256343_64.dll" -Force
        Copy-Item "$guardDir\32\translucent-windows_1.8.3_256343.dll" "$bkd\translucent-windows_1.8.3_256343_32.dll" -Force
        Write-Log 'backup arch DLLs re-staged from guard copies (suffixed names)'

        # 2. build x64 + x86 with the bundled clang, mod id via force-included header
        New-Item $buildDir -ItemType Directory -Force | Out-Null
        $modIdHeader = Join-Path $buildDir 'translucent-windows-modid.h'
        Set-Content -LiteralPath $modIdHeader -Value ('#define WH_MOD_ID L"{0}"' -f $newId) -Encoding Ascii
        $targets = @(
            [pscustomobject]@{ Arch = 'x86_64-w64-mingw32'; Lib = "$engineRoot\64\windhawk.lib"; Out = Join-Path $buildDir 'local@translucent-windows_1.8.3_1_64.dll' },
            [pscustomobject]@{ Arch = 'i686-w64-mingw32';  Lib = "$engineRoot\32\windhawk.lib"; Out = Join-Path $buildDir 'local@translucent-windows_1.8.3_1_32.dll' }
        )
        foreach ($t in $targets) {
            Write-Log "compiling $(Split-Path $t.Out -Leaf) ($($t.Arch)) ..."
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

        # 3. place DLLs and source
        Copy-Item (Join-Path $buildDir 'local@translucent-windows_1.8.3_1_64.dll') "$mods64\$newDll" -Force
        Copy-Item (Join-Path $buildDir 'local@translucent-windows_1.8.3_1_32.dll') "$mods32\$newDll" -Force
        Copy-Item $staged "$modsSource\local@translucent-windows.wh.cpp" -Force
        Write-Log 'DLLs and source placed'

        # 4. clone the backed-up key to the new id, then drop the transient old key
        reg.exe import "$bkd\translucent-windows-before-migration.reg" | Out-Null
        if (-not (Test-Path $oldKey)) { throw 'old key did not come back from backup import' }
        reg.exe copy $oldKeyReg $newKeyReg /s /f | Out-Null
        if (-not (Test-Path $newKey)) { throw 'reg copy failed' }
        reg.exe delete $oldKeyReg /f | Out-Null
        if (Test-Path $oldKey) { throw 'old key still present' }
        Write-Log 'key cloned to local@ id, old key removed'

        # 5. point the new key at the new DLLs, bump SCT (UTC-correct)
        Set-ItemProperty -Path $newKey -Name 'LibraryFileName' -Value $newDll -Type String
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        Set-ItemProperty -Path $newKey -Name 'SettingsChangeTime' -Value $now -Type DWord
        $p = Get-ItemProperty $newKey
        if ($p.Version -ne $version) { throw "version mismatch: $($p.Version)" }
        if ($p.Disabled -ne 0)       { throw 'new mod disabled' }
        if ($p.Include -ne '*')      { throw "include mismatch: $($p.Include)" }
        $settingsCount = (Get-Item "$newKey\Settings").ValueCount
        Write-Log "new key: lib=$($p.LibraryFileName) version=$($p.Version) settings=$settingsCount excludeCustom=$($p.ExcludeCustom)"
        if ($settingsCount -ne 156) { throw "expected 156 settings, found $settingsCount" }

        # 6. verify through the app and in memory
        Start-Sleep -Seconds 3
        $listJson = (& $cli mod list --json 2>&1) -join "`n"
        if ($listJson -notmatch [regex]::Escape($newId)) { throw 'new id not present in mod list' }
        if ($listJson -match '(?<!local@)"translucent-windows"') { Write-Log 'WARN: old id still listed by mod list' }
        $names = Get-ProfileModNames
        if ($names -contains $oldId) { Write-Log 'WARN: profile entry for old id present' } else { Write-Log 'profile entry for old id: absent' }
        if ($names -contains $newId) { Write-Log 'note: new id tracked in profile' } else { Write-Log 'new id not tracked in profile (expected for local@ ids)' }

        $newLoaded = 0; $oldLoaded = 0; $unopenable = 0
        Get-Process | ForEach-Object {
            try {
                foreach ($m in ($_.Modules | Where-Object { $_.ModuleName -like '*translucent-windows*' })) {
                    if ($m.ModuleName -like 'local@*') { $script:newLoaded++ } else { $script:oldLoaded++ }
                }
            } catch { $script:unopenable++ }
        }
        Write-Log "census: new=$newLoaded old=$oldLoaded unopenable=$unopenable"

        # 7. restage the guard pristine copies for the new id (archive the old ones)
        $archive = Join-Path $guardDir 'archive-256343'
        New-Item $archive -ItemType Directory -Force | Out-Null
        foreach ($d in @('64', '32')) {
            if (Test-Path (Join-Path $guardDir $d)) { Move-Item (Join-Path $guardDir $d) (Join-Path $archive $d) -Force }
            New-Item (Join-Path $guardDir $d) -ItemType Directory -Force | Out-Null
        }
        Copy-Item "$mods64\$newDll" "$guardDir\64\$newDll" -Force
        Copy-Item "$mods32\$newDll" "$guardDir\32\$newDll" -Force
        Move-Item "$guardDir\translucent-windows-1.8.3-256343.reg" "$archive\translucent-windows-1.8.3-256343.reg" -Force -ErrorAction SilentlyContinue
        reg.exe export $newKeyReg "$guardDir\local@translucent-windows-1.8.3-1.reg" /y | Out-Null
        Write-Log 'guard pristine copies restaged for local@ id'

        # 8. receipt
        $receipt = [ordered]@{
            action             = 'local-build-install'
            date               = '2026-10-15'
            newId              = $newId
            libraryFileName    = $newDll
            dll64Sha256        = Get-Sha "$mods64\$newDll"
            dll32Sha256        = Get-Sha "$mods32\$newDll"
            stagedSourceSha256 = (Get-Sha $staged)
            settingsCount      = $settingsCount
            excludeCustom      = $p.ExcludeCustom
            censusNewLoaded    = $newLoaded
            censusOldLoaded    = $oldLoaded
            profileOldEntryAbsent = -not ($names -contains $oldId)
            backupDir          = $bkd
        }
        $receipt | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $rep 'receipt-local-install.json') -Encoding UTF8
        Write-Log '=== local build + install done (guard stays suspended until the re-pointed guard is installed) ==='
    }

    'Rollback' {
        Write-Log '=== local-install rollback start ==='
        if (Test-Path $newKey) { reg.exe delete $newKeyReg /f | Out-Null }
        Remove-Item "$modsSource\local@translucent-windows.wh.cpp" -Force -ErrorAction SilentlyContinue
        Remove-Item "$mods64\$newDll", "$mods32\$newDll" -Force -ErrorAction SilentlyContinue
        reg.exe import "$bkd\translucent-windows-before-migration.reg" | Out-Null
        Copy-Item "$bkd\translucent-windows.wh.cpp" "$modsSource\translucent-windows.wh.cpp" -Force
        Copy-Item "$bkd\translucent-windows_1.8.3_256343_64.dll" "$mods64\translucent-windows_1.8.3_256343.dll" -Force
        Copy-Item "$bkd\translucent-windows_1.8.3_256343_32.dll" "$mods32\translucent-windows_1.8.3_256343.dll" -Force
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        Set-ItemProperty -Path $oldKey -Name 'SettingsChangeTime' -Value $now -Type DWord
        $p = Get-ItemProperty $oldKey
        Write-Log "rollback done: lib=$($p.LibraryFileName) version=$($p.Version) disabled=$($p.Disabled)"
        Write-Log 'NOTE: guard suspend marker left in place on purpose.'
    }
}
