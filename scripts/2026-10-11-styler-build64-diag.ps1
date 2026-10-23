# One-off: compile 64-bit styler with full error output.
$ErrorActionPreference = 'Continue'
$WindhawkRoot = 'C:\Program Files\Windhawk'
$engine = Get-ChildItem "$WindhawkRoot\Engine" -Directory |
    Where-Object { Test-Path (Join-Path $_.FullName '64\windhawk.lib') } |
    Sort-Object LastWriteTime -Descending | Select-Object -First 1
Write-Host "engine: $($engine.Name)"
$dir = "H:\Windhawk Configuration\work\styler-release\mods\local\windhawk-styler"
$src = Join-Path $dir 'windhawk-styler.wh.cpp'
$hdr = Join-Path $dir 'build\mod-id.h'
Set-Content -LiteralPath $hdr -Value '#define WH_MOD_ID L"local@windhawk-styler"' -Encoding ASCII
$out = Join-Path $dir 'build\windhawk-styler-64.dll'
$args = @(
    '-std=c++23', '-O2', '-shared', '-target', 'x86_64-w64-mingw32',
    '-DUNICODE', '-D_UNICODE', '-DWH_MOD',
    '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00', '-D_WIN32_IE=0x0A00',
    '-DNTDDI_VERSION=0x0A000008', '-D__USE_MINGW_ANSI_STDIO=0',
    '-include', $hdr, '-include', 'windhawk_api.h', '-I', "$WindhawkRoot\Compiler\include",
    '-Wl,--export-all-symbols', $src, "$WindhawkRoot\Engine\$($engine.Name)\64\windhawk.lib",
    '-lbcrypt', '-luser32', '-ldwmapi', '-lgdi32', '-lshcore', '-lcomctl32', '-lshell32', '-lws2_32', '-ladvapi32', '-luxtheme',
    '-o', $out
)
& "$WindhawkRoot\Compiler\bin\clang++.exe" @args 2>&1 | ForEach-Object { "$_" } | Select-Object -First 50
Write-Host "exit: $LASTEXITCODE"
