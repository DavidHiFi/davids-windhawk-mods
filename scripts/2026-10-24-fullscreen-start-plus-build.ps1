<#
.SYNOPSIS
    Compiles Fullscreen Start Plus with Windhawk's bundled clang, outside the engine.

.DESCRIPTION
    Same flags the Windhawk editor uses (WH_MOD, not WH_EDITING), x64 only to
    match the mod's @architecture. Links windhawk.lib from the installed engine
    folder plus the libraries in @compilerOptions. Touches nothing in Windhawk:
    the DLL and log go to work\2026-10-24-fullscreen-start-plus\build.

.EXAMPLE
    .\2026-10-24-fullscreen-start-plus-build.ps1
#>
[CmdletBinding()]
param(
    [string]$Source = 'H:\Windhawk Configuration\work\2026-10-24-fullscreen-start-plus\repo\mods\local\fullscreen-start-plus\fullscreen-start-plus.wh.cpp',
    [string]$OutDir = 'H:\Windhawk Configuration\work\2026-10-24-fullscreen-start-plus\build',
    [string]$WindhawkRoot = 'C:\Program Files\Windhawk'
)
$ErrorActionPreference = 'Stop'

New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$compiler = Join-Path $WindhawkRoot 'Compiler\bin\clang++.exe'
$include = Join-Path $WindhawkRoot 'Compiler\include'
# Newest engine folder, e.g. Engine\2.0.0.
$engine = Get-ChildItem (Join-Path $WindhawkRoot 'Engine') -Directory |
    Sort-Object { [version]($_.Name -replace '_.*$', '') } | Select-Object -Last 1
$lib = Join-Path $engine.FullName '64\windhawk.lib'

$text = Get-Content -LiteralPath $Source -Raw
$id = [regex]::Match($text, '(?m)^//\s*@id\s+(\S+)').Groups[1].Value
$version = [regex]::Match($text, '(?m)^//\s*@version\s+(\S+)').Groups[1].Value
$options = [regex]::Match($text, '(?m)^//\s*@compilerOptions\s+(.+)$').Groups[1].Value.Trim() -split '\s+'

# PowerShell mangles -DWH_MOD_ID=L"..." on the command line, so it goes in a header.
$idHeader = Join-Path $OutDir 'mod-id.h'
Set-Content -LiteralPath $idHeader -Value ('#define WH_MOD_ID L"local@{0}"' -f $id) -Encoding Ascii

$out = Join-Path $OutDir ('{0}_{1}_64.dll' -f $id, $version)
$log = Join-Path $OutDir 'build.log'
$compileArgs = @(
    '-std=c++23', '-O2', '-shared', '-target', 'x86_64-w64-mingw32',
    '-DUNICODE', '-D_UNICODE', '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00',
    '-D_WIN32_IE=0x0A00', '-DNTDDI_VERSION=0x0A000008', '-D__USE_MINGW_ANSI_STDIO=0',
    '-DWH_MOD', '-include', $idHeader, '-include', 'windhawk_api.h', '-I', $include,
    '-Wno-pragma-pack', '-Wno-pragma-system-header-outside-header',
    '-Wl,--export-all-symbols', $Source, $lib
) + $options + @('-o', $out)

"$(Get-Date -Format 'yyyy-MM-dd h:mm:ss tt') $id $version against $($engine.Name)" | Set-Content -LiteralPath $log
& $compiler @compileArgs 2>&1 | ForEach-Object { "$_" } | Tee-Object -FilePath $log -Append
if ($LASTEXITCODE -ne 0 -or -not (Test-Path -LiteralPath $out)) {
    "BUILD FAILED (exit $LASTEXITCODE)" | Tee-Object -FilePath $log -Append
    exit 1
}
$hash = (Get-FileHash -LiteralPath $out -Algorithm SHA256).Hash
"BUILD OK $out $((Get-Item $out).Length) bytes sha256=$hash" | Tee-Object -FilePath $log -Append
