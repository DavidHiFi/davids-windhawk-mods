[CmdletBinding()]
param(
    [string]$WindhawkRoot = 'C:\Program Files\Windhawk',
    [string]$EngineVersion = '',
    [string]$OutputDirectory = (Join-Path $PSScriptRoot 'build')
)
$ErrorActionPreference = 'Stop'
if (-not $EngineVersion) {
    $engine = Get-ChildItem (Join-Path $WindhawkRoot 'Engine') -Directory |
        Where-Object { Test-Path (Join-Path $_.FullName '64\windhawk.lib') } |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if (-not $engine) { throw 'No Windhawk engine import library found.' }
    $EngineVersion = $engine.Name
}
$compiler = Join-Path $WindhawkRoot 'Compiler\bin\clang++.exe'
$include = Join-Path $WindhawkRoot 'Compiler\include'
$source = Join-Path $PSScriptRoot 'window-manager.wh.cpp'
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
$header = Join-Path $OutputDirectory 'mod-id.h'
Set-Content -LiteralPath $header -Value '#define WH_MOD_ID L"local@window-manager"' -Encoding ASCII
foreach ($target in @(@('64', 'x86_64-w64-mingw32'), @('32', 'i686-w64-mingw32'))) {
    $lib = Join-Path $WindhawkRoot "Engine\$EngineVersion\$($target[0])\windhawk.lib"
    if (-not (Test-Path $lib)) { throw "Import library missing: $lib" }
    $output = Join-Path $OutputDirectory "window-manager-$($target[0]).dll"
    $arguments = @(
        '-std=c++23', '-O2', '-shared', '-target', $target[1],
        '-DUNICODE', '-D_UNICODE', '-DWH_MOD',
        '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00', '-D_WIN32_IE=0x0A00',
        '-DNTDDI_VERSION=0x0A000008', '-D__USE_MINGW_ANSI_STDIO=0',
        '-include', $header, '-include', 'windhawk_api.h', '-I', $include,
        '-Wl,--export-all-symbols', $source, $lib,
        '-luser32', '-ldwmapi', '-lgdi32', '-lshcore', '-lcomctl32', '-lshell32',
        '-o', $output
    )
    & $compiler @arguments
    if ($LASTEXITCODE -ne 0) { throw "Build failed for $($target[0])-bit target." }
    Get-FileHash -LiteralPath $output -Algorithm SHA256
}
