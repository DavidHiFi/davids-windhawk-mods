[CmdletBinding()]
param([switch]$Audit)
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$job="$root\work\memory-align"
$source="$job\repo\mods\local\taskbar-system-info-weather\taskbar-system-info-weather.wh.cpp"
$compiler='C:\Program Files\Windhawk\Compiler\bin\clang++.exe'
$engine='C:\Program Files\Windhawk\Engine\1.7.3_2\64\windhawk.lib'
if($Audit){Get-Item $source,$compiler,$engine | Select-Object FullName,Length;exit}
New-Item -ItemType Directory -Force "$root\reports\2026-10-03\memory-align" | Out-Null
Set-Content "$job\modid.h" '#define WH_MOD_ID L"local@taskbar-system-info-weather"' -Encoding Ascii
$log="$root\reports\2026-10-03\memory-align\build.log"
Set-Content $log "Build started $((Get-Date).ToString('o'))"
$argsList=@('-std=c++23','-O2','-shared','-target','x86_64-w64-mingw32','-DUNICODE','-D_UNICODE','-DWINVER=0x0A00','-D_WIN32_WINNT=0x0A00','-DWH_MOD','-include',"$job\modid.h",'-include','windhawk_api.h','-I','C:\Program Files\Windhawk\Compiler\include','-Wl,--export-all-symbols',$source,$engine,'-lole32','-loleaut32','-lruntimeobject','-lpdh','-ldxgi','-lcomctl32','-liphlpapi','-DWIN32_LEAN_AND_MEAN','-o',"$job\system-info.dll")
& $compiler @argsList 2>&1 | Tee-Object -Append $log
if($LASTEXITCODE){throw "Compiler failed: $LASTEXITCODE"}
Get-FileHash "$job\system-info.dll"
[ordered]@{Timestamp=(Get-Date).ToString('o');ExitCode=0;SourceHash=(Get-FileHash $source).Hash;DllHash=(Get-FileHash "$job\system-info.dll").Hash;Compiler=$compiler;Architecture='x86-64'} | ConvertTo-Json | Set-Content "$root\reports\2026-10-03\memory-align\build-result.json"
Add-Content $log 'PASS: compiler exit 0; hashes recorded in build-result.json'




