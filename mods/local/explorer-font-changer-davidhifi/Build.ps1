[CmdletBinding()]
param(
    [switch]$Test,
    [string]$WindhawkRoot = 'C:\Program Files\Windhawk',
    [string]$EngineVersion = '1.7.3_2',
    [string]$ModData = 'C:\ProgramData\Windhawk',
    [string]$OutputDirectory = "$PSScriptRoot\build"
)
$ErrorActionPreference = 'Stop'
$compiler = "$WindhawkRoot\Compiler\bin\clang++.exe"
$include = "$WindhawkRoot\Compiler\include"
$source = "$PSScriptRoot\explorer-font-changer-davidhifi.wh.cpp"
New-Item -ItemType Directory -Force $OutputDirectory | Out-Null
Set-Content "$OutputDirectory\modid.h" '#define WH_MOD_ID L"local@explorer-font-changer-davidhifi"' -Encoding ascii
foreach ($arch in @('64','32')) {
    $target = if ($arch -eq '64') {'x86_64-w64-mingw32'} else {'i686-w64-mingw32'}
    & $compiler '-std=c++23' '-O2' '-shared' '-target' $target '-DUNICODE' '-D_UNICODE' '-DWH_MOD' '-include' "$OutputDirectory\modid.h" '-include' 'windhawk_api.h' '-I' $include '-Wl,--export-all-symbols' $source "$WindhawkRoot\Engine\$EngineVersion\$arch\windhawk.lib" '-lgdi32' '-luxtheme' '-ldwrite' '-o' "$OutputDirectory\local@explorer-font-changer-davidhifi_1.0.1_1_$arch.dll"
    if ($LASTEXITCODE) {throw "Build failed for $arch"}
}
if ($Test) {
    & $compiler '-std=c++23' '-O2' '-target' 'x86_64-w64-mingw32' '-DUNICODE' '-D_UNICODE' '-DWH_MOD' '-DWH_EDITING' '-include' 'windhawk_api.h' '-I' $include "$PSScriptRoot\tests\font-tests.cpp" '-lgdi32' '-luxtheme' '-ldwrite' '-o' "$OutputDirectory\font-tests.exe"
    if ($LASTEXITCODE) {throw 'Test build failed'}
    # The compiler imports libc++.whl and libunwind.whl using Windhawk's names.
    $savedPath = $env:PATH
    $env:PATH = "$ModData\Engine\Mods\64;$savedPath"
    try { & "$OutputDirectory\font-tests.exe" | Tee-Object "$OutputDirectory\test-results.txt" }
    finally { $env:PATH = $savedPath }
    if ($LASTEXITCODE) {throw 'Tests failed'}
}
Get-FileHash "$OutputDirectory\*.dll" | Select-Object Path,Hash | ConvertTo-Json | Set-Content "$OutputDirectory\hashes.json"
