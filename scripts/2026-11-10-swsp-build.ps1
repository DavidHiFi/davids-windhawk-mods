# Offline build of Simple Window Switcher Plus (64 and 32 bit) with Windhawk's
# bundled clang, same flags as the engine (WH_MOD). Touches nothing in Windhawk.
# Output: work\2026-11-10-swsp\swsp64.dll, swsp32.dll, build.log. Runs at Idle priority.
param(
    [string]$Source = 'H:\Windhawk Configuration\work\2026-11-10-swsp\swsp.wh.cpp',
    [string]$OutDir = 'H:\Windhawk Configuration\work\2026-11-10-swsp',
    [string]$WindhawkRoot = 'C:\Program Files\Windhawk'
)
$ErrorActionPreference = 'Stop'
$compiler = Join-Path $WindhawkRoot 'Compiler\bin\clang++.exe'
$include = Join-Path $WindhawkRoot 'Compiler\include'
$engine = Get-ChildItem (Join-Path $WindhawkRoot 'Engine') -Directory |
    Where-Object { Test-Path (Join-Path $_.FullName '64\windhawk.lib') } |
    Sort-Object { [version]($_.Name -replace '_.*$', '') } | Select-Object -Last 1
$text = Get-Content -LiteralPath $Source -Raw
$options = [regex]::Match($text, '(?m)^//\s*@compilerOptions\s+(.+)$').Groups[1].Value.Trim() -split '\s+'
$idHeader = Join-Path $OutDir 'modid.h'
Set-Content -LiteralPath $idHeader -Value '#define WH_MOD_ID L"local@simple-window-switcher-plus"' -Encoding Ascii
$log = Join-Path $OutDir 'build.log'
"$(Get-Date -Format 'h:mm:ss tt') build against $($engine.Name)" | Set-Content $log
$ok = $true
foreach ($arch in @(@{n='64'; t='x86_64-w64-mingw32'}, @{n='32'; t='i686-w64-mingw32'})) {
    $out = Join-Path $OutDir "swsp$($arch.n).dll"
    $lib = Join-Path $engine.FullName "$($arch.n)\windhawk.lib"
    $args = @('-std=c++23', '-O2', '-shared', '-target', $arch.t,
        '-DUNICODE', '-D_UNICODE', '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00',
        '-D_WIN32_IE=0x0A00', '-DNTDDI_VERSION=0x0A000008', '-D__USE_MINGW_ANSI_STDIO=0',
        '-DWH_MOD', '-include', $idHeader, '-include', 'windhawk_api.h', '-I', $include,
        '-Wno-pragma-pack', '-Wno-pragma-system-header-outside-header',
        '-Wl,--export-all-symbols', $Source, $lib) + $options + @('-o', $out)
    $quoted = $args | ForEach-Object { if ($_ -match '\s') { '"' + $_ + '"' } else { $_ } }
    $errFile = Join-Path $OutDir "build$($arch.n).err"
    $p = Start-Process $compiler -ArgumentList $quoted -PassThru -WindowStyle Hidden `
        -RedirectStandardError $errFile -RedirectStandardOutput "$errFile.out"
    try { $p.PriorityClass = 'Idle' } catch {}
    $p.WaitForExit()
    Get-Content $errFile | Add-Content $log
    if ($p.ExitCode -ne 0 -or -not (Test-Path $out)) { "BUILD $($arch.n) FAILED exit $($p.ExitCode)" | Tee-Object $log -Append; $ok = $false }
    else { "BUILD $($arch.n) OK $((Get-Item $out).Length) bytes" | Tee-Object $log -Append }
}
if (-not $ok) { exit 1 }
