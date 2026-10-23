<#
.SYNOPSIS
Build and direct-install the translucent-windows fork 1.8.3 local build 2
(PowerToys Settings acrylic rule + generalized caption hook).

WHY
The fork's caption hook was CASCADIA_HOSTING_WINDOW_CLASS-gated, so only
Windows Terminal got DWMWA_COLOR_NONE on the title bar. This build generalizes
it: ANY ruled window whose rule sets AcrylicSystemBackdrop or AccentBlurBehind
gets caption (35) + border (34) forced to DWMWA_COLOR_NONE. It also adds
RuledPrograms[30] for PowerToys.Settings.exe (acrylicblur + AA1E1E2E tint,
AccentColorControls 0, ThemeBackground 0 - the round-5 CMD recipe).

The build uses the bundled clang (mod id via a force-included header, -DWH_MOD
only) because windhawk-cli rejects '@' in mod ids. LibraryFileName is pointed
at the _2 DLLs in place - the key already exists and keeps all its settings.

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
$newId      = 'local@translucent-windows'
$version    = '1.8.3'
$newDll     = 'local@translucent-windows_1.8.3_2.dll'
$modKeyReg  = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$newId"
$modKey     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$newId"
$settings   = "$modKey\Settings"
$modsSource = 'C:\ProgramData\Windhawk\ModsSource'
$devDir     = Join-Path $ws 'Windhawk\translucent-windows'
$staged     = Join-Path $devDir 'local@translucent-windows.wh.cpp'
$buildDir   = Join-Path $devDir 'build-local'
$guardDir   = Join-Path $devDir 'guard'
$bkd        = Join-Path $ws 'backups\2026-10-16\powertoys-acrylic'
$rep        = 'H:\System Configuration\reports\2026-10-16-powertoys-acrylic-global'
$log        = Join-Path $rep 'build-install.log'
$compiler   = 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe'
$incDir     = 'C:\Program Files\Windhawk\Compiler\include'
$engineRoot = 'C:\Program Files\Windhawk\Engine\2.0.0_1'
$mods64     = 'C:\ProgramData\Windhawk\Engine\Mods\64'
$mods32     = 'C:\ProgramData\Windhawk\Engine\Mods\32'
$cli        = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$suspend    = 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend'
$forkHash   = '8280803C303E8B8A931AA5D4BD3B19C38ADC4C7B80A53E8E31518F66AAC5F809'
$rule       = 30   # PowerToys.Settings.exe - next free index (0..29 in use)

function Write-Log([string]$m) {
    Add-Content -LiteralPath $log -Value ("{0} {1}" -f (Get-Date -Format o), $m) -Encoding UTF8
    Write-Output $m
}

function Get-Sha([string]$p) { (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

New-Item $rep -ItemType Directory -Force | Out-Null

switch ($Action) {

    'Install' {
        Write-Log '=== 1.8.3 build-2 install start ==='

        # 0. prechecks
        if ((Get-Service Windhawk -ErrorAction Stop).Status -ne 'Running') { throw 'Windhawk service not running' }
        foreach ($p in @($staged, $compiler, "$incDir\windhawk_api.h", "$engineRoot\64\windhawk.lib", "$engineRoot\32\windhawk.lib")) {
            if (-not (Test-Path $p)) { throw "missing: $p" }
        }
        if ((Get-Sha $staged) -ne $forkHash) { throw "staged source hash mismatch - expected the generalized caption-hook edit $forkHash" }
        if (-not (Test-Path $suspend)) { throw 'guard suspend marker missing - suspend the guard first' }
        foreach ($p in @("$mods64\$newDll", "$mods32\$newDll")) { if (Test-Path $p) { throw "build-2 DLL already present: $p" } }
        Write-Log 'prechecks ok (source hash, suspend marker, no stale _2 DLLs)'

        # 1. build x64 + x86 with the bundled clang, mod id via force-included header
        New-Item $buildDir -ItemType Directory -Force | Out-Null
        $modIdHeader = Join-Path $buildDir 'translucent-windows-modid.h'
        Set-Content -LiteralPath $modIdHeader -Value ('#define WH_MOD_ID L"{0}"' -f $newId) -Encoding Ascii
        $targets = @(
            [pscustomobject]@{ Arch = 'x86_64-w64-mingw32'; Lib = "$engineRoot\64\windhawk.lib"; Out = Join-Path $buildDir 'local@translucent-windows_1.8.3_2_64.dll' },
            [pscustomobject]@{ Arch = 'i686-w64-mingw32';  Lib = "$engineRoot\32\windhawk.lib"; Out = Join-Path $buildDir 'local@translucent-windows_1.8.3_2_32.dll' }
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

        # 2. place DLLs and source
        Copy-Item (Join-Path $buildDir 'local@translucent-windows_1.8.3_2_64.dll') "$mods64\$newDll" -Force
        Copy-Item (Join-Path $buildDir 'local@translucent-windows_1.8.3_2_32.dll') "$mods32\$newDll" -Force
        Copy-Item $staged "$modsSource\local@translucent-windows.wh.cpp" -Force
        Write-Log 'DLLs and source placed'

        # 3. point the key at build 2, add the PowerToys rule, bump SCT (UTC-correct)
        Set-ItemProperty -Path $modKey -Name 'LibraryFileName' -Value $newDll -Type String
        New-ItemProperty -Path $settings -Name "RuledPrograms[$rule].target" -Value 'PowerToys.Settings.exe' -PropertyType 'String' -Force | Out-Null
        foreach ($v in @(
            [pscustomobject]@{ N = "RuledPrograms[$rule].BackgroundEffects.type";             V = 'acrylicblur'; T = 'String' },
            [pscustomobject]@{ N = "RuledPrograms[$rule].BackgroundEffects.AccentBlurBehind"; V = 'AA1E1E2E';    T = 'String' },
            [pscustomobject]@{ N = "RuledPrograms[$rule].RenderingMod.AccentColorControls";   V = 0;             T = 'DWord' },
            [pscustomobject]@{ N = "RuledPrograms[$rule].RenderingMod.ThemeBackground";       V = 0;             T = 'DWord' }
        )) {
            New-ItemProperty -Path $settings -Name $v.N -Value $v.V -PropertyType $v.T -Force | Out-Null
        }
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        Set-ItemProperty -Path $modKey -Name 'SettingsChangeTime' -Value $now -Type DWord

        # 4. verify readback
        $p = Get-ItemProperty $modKey
        if ($p.Version -ne $version)  { throw "version mismatch: $($p.Version)" }
        if ($p.Disabled -ne 0)        { throw 'mod disabled' }
        if ($p.Include -ne '*')       { throw "include mismatch: $($p.Include)" }
        if ($p.LibraryFileName -ne $newDll) { throw "LibraryFileName not applied: $($p.LibraryFileName)" }
        $sv2 = Get-ItemProperty $settings
        if ($sv2."RuledPrograms[$rule].target" -ne 'PowerToys.Settings.exe') { throw 'rule 30 target missing' }
        if ($sv2."RuledPrograms[$rule].BackgroundEffects.type" -ne 'acrylicblur') { throw 'rule 30 type missing' }
        if ($sv2."RuledPrograms[$rule].BackgroundEffects.AccentBlurBehind" -ne 'AA1E1E2E') { throw 'rule 30 tint missing' }
        if ([int]$sv2."RuledPrograms[$rule].RenderingMod.AccentColorControls" -ne 0) { throw 'rule 30 AccentColorControls missing' }
        if ([int]$sv2."RuledPrograms[$rule].RenderingMod.ThemeBackground" -ne 0) { throw 'rule 30 ThemeBackground missing' }
        $settingsCount = (Get-Item $settings).ValueCount
        Write-Log "key: lib=$($p.LibraryFileName) version=$($p.Version) settings=$settingsCount (was 156, +5 rule values)"
        if ($settingsCount -ne 161) { throw "expected 161 settings, found $settingsCount" }

        # 5. verify through the app
        Start-Sleep -Seconds 3
        $listJson = (& $cli mod list --json 2>&1) -join "`n"
        if ($listJson -notmatch [regex]::Escape($newId)) { throw 'mod id not present in mod list' }
        $newLoaded = 0; $unopenable = 0
        Get-Process | ForEach-Object {
            try {
                foreach ($m in ($_.Modules | Where-Object { $_.ModuleName -like '*translucent-windows*' })) {
                    if ($m.ModuleName -like 'local@*') { $script:newLoaded++ }
                }
            } catch { $script:unopenable++ }
        }
        Write-Log "census: local@ loaded=$newLoaded unopenable=$unopenable"

        # 6. restage guard pristine copies (archive the build-1 set)
        $archive = Join-Path $guardDir 'archive-183-1'
        New-Item $archive -ItemType Directory -Force | Out-Null
        foreach ($d in @('64', '32')) {
            if (Test-Path (Join-Path $guardDir $d)) { Move-Item (Join-Path $guardDir $d) (Join-Path $archive $d) -Force }
            New-Item (Join-Path $guardDir $d) -ItemType Directory -Force | Out-Null
        }
        Copy-Item "$mods64\$newDll" "$guardDir\64\$newDll" -Force
        Copy-Item "$mods32\$newDll" "$guardDir\32\$newDll" -Force
        Move-Item "$guardDir\local@translucent-windows-1.8.3-1.reg" "$archive\local@translucent-windows-1.8.3-1.reg" -Force -ErrorAction SilentlyContinue
        reg.exe export $modKeyReg "$guardDir\local@translucent-windows-1.8.3-2.reg" /y | Out-Null
        if (-not (Test-Path "$guardDir\local@translucent-windows-1.8.3-2.reg")) { throw 'pristine reg export missing' }
        Write-Log 'guard pristine copies restaged for build 2 (old set archived)'

        # 7. receipt
        $receipt = [ordered]@{
            action             = 'build-2-install'
            date               = '2026-10-16'
            modId              = $newId
            libraryFileName    = $newDll
            forkSourceSha256   = $forkHash
            dll64Sha256        = Get-Sha "$mods64\$newDll"
            dll32Sha256        = Get-Sha "$mods32\$newDll"
            rule30             = [ordered]@{
                target              = 'PowerToys.Settings.exe'
                backgroundEffects   = 'acrylicblur / AA1E1E2E'
                accentColorControls = 0
                themeBackground     = 0
            }
            settingsCount      = $settingsCount
            censusLoaded       = $newLoaded
            guardArchive       = $archive
        }
        $receipt | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $rep 'receipt-build2-install.json') -Encoding UTF8
        Write-Log '=== build-2 install done (guard stays suspended until its constants are updated) ==='
    }

    'Rollback' {
        Write-Log '=== build-2 rollback start ==='
        $oldDll = 'local@translucent-windows_1.8.3_1.dll'
        Set-ItemProperty -Path $modKey -Name 'LibraryFileName' -Value $oldDll -Type String
        foreach ($n in @(
            "RuledPrograms[$rule].target",
            "RuledPrograms[$rule].BackgroundEffects.type",
            "RuledPrograms[$rule].BackgroundEffects.AccentBlurBehind",
            "RuledPrograms[$rule].RenderingMod.AccentColorControls",
            "RuledPrograms[$rule].RenderingMod.ThemeBackground"
        )) { Remove-ItemProperty -Path $settings -Name $n -ErrorAction SilentlyContinue }
        Remove-Item "$mods64\$newDll", "$mods32\$newDll" -Force -ErrorAction SilentlyContinue
        Copy-Item "$bkd\ModsSource-before.wh.cpp" "$modsSource\local@translucent-windows.wh.cpp" -Force
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        Set-ItemProperty -Path $modKey -Name 'SettingsChangeTime' -Value $now -Type DWord
        $p = Get-ItemProperty $modKey
        Write-Log "rollback done: lib=$($p.LibraryFileName); rule 30 removed; ModsSource restored from backup"
        Write-Log 'NOTE: guard suspend marker left in place on purpose.'
    }
}
