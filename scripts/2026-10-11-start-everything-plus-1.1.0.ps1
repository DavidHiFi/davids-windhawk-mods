<#
.SYNOPSIS
    Builds and installs the start-everything-plus fork 1.1.0 (upstream 1.1 merge).

.DESCRIPTION
    -Build    compile the fork source with the Windhawk-bundled clang (x64) into
              reports\2026-10-11-start-everything-sync\local@start-everything-plus_1.1.0_710105.dll
    -Install  copy the DLL and source into ProgramData via a silent elevated child,
              point the mod key at the new revision, bump SettingsChangeTime, and
              write install-receipt.json. Hot reload only; no engine restart.
    -Audit    read back the installed state.
    -Rollback restore the 1.0.4 build from backups\2026-10-11\start-everything-plus.

    Registry backup: backups\2026-10-11\start-everything-plus\mod-settings.reg
    (exported before any change).
#>
param(
    [switch]$Build,[switch]$Install,[switch]$InstallCore,
    [switch]$Audit,[switch]$Rollback,[switch]$RollbackCore
)
$ErrorActionPreference='Stop'
$base='HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$id='local@start-everything-plus'
$version='1.1.0'
$library='local@start-everything-plus_1.1.0_710107.dll'
$oldLibrary='local@start-everything-plus_1.0.4_710104.dll'
$repo='H:\Windhawk Configuration\davids-windhawk-mods\mods\local\start-everything-plus\start-everything-plus.wh.cpp'
$sync='H:\Windhawk Configuration\reports\2026-10-11-start-everything-sync'
$out=Join-Path $sync $library
$compiler='C:\Program Files\Windhawk\Compiler\bin\clang++.exe'
$includeDir='C:\Program Files\Windhawk\Compiler\include'
$engineLib='C:\Program Files\Windhawk\Engine\2.0.0_1\64\windhawk.lib'
$backup='H:\Windhawk Configuration\backups\2026-10-11\start-everything-plus'
$modSource='C:\ProgramData\Windhawk\ModsSource\local@start-everything-plus.wh.cpp'
$modDll="C:\ProgramData\Windhawk\Engine\Mods\64\$library"
$oldModDll="C:\ProgramData\Windhawk\Engine\Mods\64\$oldLibrary"
function Stamp { New-ItemProperty "$base\$id" SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null }

if ($Build) {
    if (!(Test-Path $compiler)) { throw 'Compiler missing.' }
    if (!(Test-Path $engineLib)) { throw "Engine lib missing: $engineLib" }
    $modid=Join-Path $env:TEMP 'se-plus-modid.h'
    Set-Content -LiteralPath $modid -Value '#define WH_MOD_ID L"local@start-everything-plus"' -Encoding Ascii
    & $compiler -std=c++23 -O2 -shared -target x86_64-w64-mingw32 `
        -DUNICODE -D_UNICODE -DWINVER=0x0A00 -D_WIN32_WINNT=0x0A00 -D_WIN32_IE=0x0A00 -DNTDDI_VERSION=0x0A000008 `
        -D__USE_MINGW_ANSI_STDIO=0 -DWH_MOD `
        -include $modid -include windhawk_api.h -I $includeDir `
        -Wno-pragma-pack -Wno-pragma-system-header-outside-header '-Wl,--export-all-symbols' `
        $repo $engineLib -lole32 -loleaut32 -lruntimeobject -luuid -lshell32 -lshlwapi -lcomctl32 -ldwmapi -luser32 -liphlpapi -lgdi32 `
        -o $out
    if ($LASTEXITCODE -ne 0 -or !(Test-Path $out)) { throw "Build failed (exit=$LASTEXITCODE)" }
    [ordered]@{ Library=$library; Sha256=(Get-FileHash $out -Algorithm SHA256).Hash; Bytes=(Get-Item $out).Length } |
        ConvertTo-Json | Set-Content "$sync\build.json" -Encoding UTF8
    Get-Content "$sync\build.json"
}

if ($InstallCore) {
    Copy-Item $out $modDll -Force
    Copy-Item $repo $modSource -Force
    Set-ItemProperty "$base\$id" LibraryFileName $library
    Set-ItemProperty "$base\$id" Version $version
    Set-ItemProperty "$base\$id" Disabled 0 -Type DWord
    Stamp
    exit 0
}

if ($Install) {
    if (!(Test-Path $out)) { throw 'Build missing; run -Build first.' }
    if (!(Test-Path "$backup\mod-settings.reg")) { throw 'Pre-change registry backup missing.' }
    $argLine = "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`" -InstallCore"
    $p = Start-Process pwsh -ArgumentList $argLine -Verb RunAs -Wait -PassThru -WindowStyle Hidden
    if ($p.ExitCode -ne 0) { throw "Elevated install failed (exit=$($p.ExitCode))" }
    Start-Sleep -Seconds 2
    $readback = Get-ItemProperty "$base\$id" | Select-Object LibraryFileName,Version,Disabled,SettingsChangeTime
    [ordered]@{
        Time=(Get-Date).ToString('o'); Id=$id; Version=$version; Library=$library
        LibrarySha256=(Get-FileHash $out -Algorithm SHA256).Hash
        InstalledDllSha256=(Get-FileHash $modDll -Algorithm SHA256).Hash
        RegistryReadback=$readback
    } | ConvertTo-Json | Set-Content "$sync\install-receipt.json" -Encoding UTF8
    $readback | Format-List
}

if ($Audit) {
    Get-ItemProperty "$base\$id" | Select-Object PSChildName,Disabled,Version,LibraryFileName,SettingsChangeTime | Format-List
    Get-ChildItem "C:\ProgramData\Windhawk\Engine\Mods\64" -Filter "*start-everything-plus*" | Select-Object Name,Length,LastWriteTime | Format-Table -AutoSize
}

if ($RollbackCore) {
    Copy-Item "$backup\$oldLibrary" $oldModDll -Force
    Copy-Item "$backup\ModsSource-local@start-everything-plus.wh.cpp" $modSource -Force
    Set-ItemProperty "$base\$id" LibraryFileName $oldLibrary
    Set-ItemProperty "$base\$id" Version '1.0.4'
    Set-ItemProperty "$base\$id" Disabled 0 -Type DWord
    Stamp
    exit 0
}

if ($Rollback) {
    if (!(Test-Path "$backup\$oldLibrary")) { throw 'Rollback backup missing.' }
    $argLine = "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`" -RollbackCore"
    $p = Start-Process pwsh -ArgumentList $argLine -Verb RunAs -Wait -PassThru -WindowStyle Hidden
    if ($p.ExitCode -ne 0) { throw "Elevated rollback failed (exit=$($p.ExitCode))" }
    Get-ItemProperty "$base\$id" | Select-Object PSChildName,Disabled,Version,LibraryFileName | Format-List
}
