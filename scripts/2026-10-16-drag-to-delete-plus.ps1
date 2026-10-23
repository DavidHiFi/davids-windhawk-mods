<#
.SYNOPSIS
    Builds and installs the drag-to-delete-plus fork 1.0.0, and retires the original drag-to-delete.

.DESCRIPTION
    -Build     compile the fork source with the Windhawk-bundled clang (x64) into
               %TEMP%\drag-to-delete-plus\local@drag-to-delete-plus_1.0.0_1.dll
    -Install   silent elevated child: registry backups (fork + original) into
               backups\2026-10-16\drag-to-delete-plus, copy DLL and source into
               ProgramData, register the fork's mod key, point LibraryFileName at
               the new revision, disable the original drag-to-delete, bump
               SettingsChangeTime, and write the receipt into reports\2026-10-16-drag-to-delete-plus.
               Hot reload only; no engine restart.
    -Audit     read back the installed state of both mods (read-only).
    -Rollback  re-enable the original drag-to-delete and disable the fork.
#>
param(
    [switch]$Build,
    [switch]$Install,
    [switch]$InstallCore,
    [switch]$Audit,
    [switch]$Rollback,
    [switch]$RollbackCore
)
$ErrorActionPreference = 'Stop'
$base = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$id = 'local@drag-to-delete-plus'
$originalId = 'drag-to-delete'
$version = '1.1.0'
$library = 'local@drag-to-delete-plus_1.1.0_3.dll'
$repo = 'H:\Windhawk Configuration\davids-windhawk-mods\mods\local\drag-to-delete-plus\drag-to-delete-plus.wh.cpp'
$sync = 'H:\Windhawk Configuration\reports\2026-10-16-drag-to-delete-plus'
$backup = 'H:\Windhawk Configuration\backups\2026-10-16\drag-to-delete-plus'
$buildDir = 'H:\Windhawk Configuration\drag-to-delete-plus-build'
$out = Join-Path $buildDir $library
$compiler = 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe'
$includeDir = 'C:\Program Files\Windhawk\Compiler\include'
$engineLib = 'C:\Program Files\Windhawk\Engine\2.0.0_1\64\windhawk.lib'
$modSource = 'C:\ProgramData\Windhawk\ModsSource\local@drag-to-delete-plus.wh.cpp'
$modDll = "C:\ProgramData\Windhawk\Engine\Mods\64\$library"
$stamp = { [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds() }

if ($Build) {
    if (!(Test-Path $compiler)) { throw 'Compiler missing.' }
    if (!(Test-Path $engineLib)) { throw "Engine lib missing: $engineLib" }
    New-Item $buildDir -ItemType Directory -Force | Out-Null
    $modid = Join-Path $buildDir 'modid.h'
    Set-Content -LiteralPath $modid -Value '#define WH_MOD_ID L"local@drag-to-delete-plus"' -Encoding Ascii
    & $compiler -std=c++23 -O2 -shared -target x86_64-w64-mingw32 `
        -DUNICODE -D_UNICODE -DWINVER=0x0A00 -D_WIN32_WINNT=0x0A00 -D_WIN32_IE=0x0A00 -DNTDDI_VERSION=0x0A000008 `
        -D__USE_MINGW_ANSI_STDIO=0 -DWH_MOD `
        -include $modid -include windhawk_api.h -I $includeDir `
        -Wno-pragma-pack -Wno-pragma-system-header-outside-header '-Wl,--export-all-symbols' `
        $repo $engineLib -lole32 -lgdi32 -lshell32 -lgdiplus `
        -o $out
    if ($LASTEXITCODE -ne 0 -or !(Test-Path $out)) { throw "Build failed (exit=$LASTEXITCODE)" }
    [ordered]@{ Library = $library; Sha256 = (Get-FileHash $out -Algorithm SHA256).Hash; Bytes = (Get-Item $out).Length } |
        ConvertTo-Json | Set-Content (Join-Path $buildDir 'build.json') -Encoding UTF8
    Get-Content (Join-Path $buildDir 'build.json')
}

if ($InstallCore) {
    # Pre-change registry backups (fork may not exist yet; original must).
    New-Item $backup -ItemType Directory -Force | Out-Null
    & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$originalId" "$backup\original-drag-to-delete.reg" /y | Out-Null
    & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$originalId\Settings" "$backup\original-drag-to-delete-settings.reg" /y 2>$null | Out-Null
    if (Test-Path "$base\$id") {
        & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\fork-before.reg" /y | Out-Null
    }
    Copy-Item "C:\ProgramData\Windhawk\ModsSource\$originalId.wh.cpp" "$backup\original-drag-to-delete.wh.cpp" -Force

    Copy-Item $out $modDll -Force
    Copy-Item $repo $modSource -Force

    $key = "$base\$id"
    if (!(Test-Path $key)) { New-Item $key -Force | Out-Null }
    New-ItemProperty -Path $key -Name Include -Value 'explorer.exe' -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name Exclude -Value '' -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name LibraryFileName -Value $library -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name Version -Value $version -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name Disabled -Value 0 -PropertyType DWord -Force | Out-Null
    New-ItemProperty -Path $key -Name Architecture -Value '' -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name SettingsChangeTime -Value (& $stamp) -PropertyType DWord -Force | Out-Null

    # Retire the original so both never hook DoDragDrop.
    $originalBefore = $null
    if (Test-Path "$base\$originalId") {
        $originalBefore = Get-ItemProperty "$base\$originalId" | Select-Object Disabled, LibraryFileName
        Set-ItemProperty "$base\$originalId" Disabled 1 -Type DWord
        New-ItemProperty -Path "$base\$originalId" -Name SettingsChangeTime -Value (& $stamp) -PropertyType DWord -Force | Out-Null
    }

    New-Item $sync -ItemType Directory -Force | Out-Null
    [ordered]@{
        Time = (Get-Date).ToString('o')
        Id = $id
        Version = $version
        Library = $library
        LibrarySha256 = (Get-FileHash $out -Algorithm SHA256).Hash
        InstalledDllSha256 = (Get-FileHash $modDll -Algorithm SHA256).Hash
        SourceSha256 = (Get-FileHash $repo -Algorithm SHA256).Hash
        RegistryReadback = (Get-ItemProperty $key | Select-Object LibraryFileName, Version, Disabled, Include, SettingsChangeTime)
        OriginalBefore = $originalBefore
        OriginalAfter = (Get-ItemProperty "$base\$originalId" -ErrorAction SilentlyContinue | Select-Object Disabled, LibraryFileName)
    } | ConvertTo-Json -Depth 5 | Set-Content "$sync\install-receipt.json" -Encoding UTF8
    exit 0
}

if ($Install) {
    if (!(Test-Path $out)) { throw 'Build missing; run -Build first.' }
    $errLog = Join-Path $buildDir 'install-error.log'
    Remove-Item $errLog -Force -ErrorAction SilentlyContinue
    $argLine = "-NoProfile -ExecutionPolicy Bypass -Command `"try { & '$PSCommandPath' -InstallCore; exit 0 } catch { Set-Content -Path '$errLog' -Value (`$_.Exception | Out-String); exit 1 }`""
    $p = Start-Process pwsh -ArgumentList $argLine -Verb RunAs -Wait -PassThru -WindowStyle Hidden
    if ($p.ExitCode -ne 0) {
        if (Test-Path $errLog) { Get-Content $errLog | Write-Output }
        throw "Elevated install failed (exit=$($p.ExitCode))"
    }
    Start-Sleep -Seconds 2
    Get-ItemProperty "$base\$id" | Select-Object LibraryFileName, Version, Disabled, Include, SettingsChangeTime | Format-List
    Get-ItemProperty "$base\$originalId" -ErrorAction SilentlyContinue | Select-Object PSChildName, Disabled | Format-List
    if (Test-Path "$sync\install-receipt.json") { 'receipt: OK' } else { 'receipt: MISSING' }
}

if ($Audit) {
    Get-ItemProperty "$base\$id" -ErrorAction SilentlyContinue | Select-Object PSChildName, Disabled, Version, LibraryFileName, Include, SettingsChangeTime | Format-List
    Get-ItemProperty "$base\$originalId" -ErrorAction SilentlyContinue | Select-Object PSChildName, Disabled, LibraryFileName | Format-List
    Get-ChildItem 'C:\ProgramData\Windhawk\Engine\Mods\64' -Filter '*drag-to-delete*' | Select-Object Name, Length, LastWriteTime | Format-Table -AutoSize
}

if ($RollbackCore) {
    if (Test-Path "$base\$originalId") {
        Set-ItemProperty "$base\$originalId" Disabled 0 -Type DWord
        New-ItemProperty -Path "$base\$originalId" -Name SettingsChangeTime -Value (& $stamp) -PropertyType DWord -Force | Out-Null
    }
    Set-ItemProperty "$base\$id" Disabled 1 -Type DWord
    New-ItemProperty -Path "$base\$id" -Name SettingsChangeTime -Value (& $stamp) -PropertyType DWord -Force | Out-Null
    exit 0
}

if ($Rollback) {
    $argLine = "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`" -RollbackCore"
    $p = Start-Process pwsh -ArgumentList $argLine -Verb RunAs -Wait -PassThru -WindowStyle Hidden
    if ($p.ExitCode -ne 0) { throw "Elevated rollback failed (exit=$($p.ExitCode))" }
    Get-ItemProperty "$base\$id" | Select-Object Disabled
    Get-ItemProperty "$base\$originalId" | Select-Object Disabled
}
