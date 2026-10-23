[CmdletBinding()]
param()
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$source="$root\work\taskbar-weather\taskbar-weather.wh.cpp"
# Name the DLL after the source's @version so earlier builds stay available for rollback.
$version=(Select-String -Path $source -Pattern '^// @version\s+(\S+)').Matches[0].Groups[1].Value
$output="$root\work\taskbar-weather\local@taskbar-weather_${version}_1.dll"
$header="$root\work\taskbar-weather\mod-id.h"
Set-Content $header '#define WH_MOD_ID L"local@taskbar-weather"' -Encoding Ascii
$argsList=@('-std=c++23','-O2','-shared','-target','x86_64-w64-mingw32','-DUNICODE','-D_UNICODE','-DWINVER=0x0A00','-D_WIN32_WINNT=0x0A00','-DWH_MOD','-include',$header,'-include','windhawk_api.h','-I','C:\Program Files\Windhawk\Compiler\include','-Wl,--export-all-symbols',$source,'C:\Program Files\Windhawk\Engine\1.7.3_2\64\windhawk.lib','-lwinhttp','-lgdiplus','-lgdi32','-luser32','-ld2d1','-ldwrite','-o',$output)
$log=& 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe' @argsList 2>&1
$code=$LASTEXITCODE
@("$(Get-Date -Format o) clang++ exit $code")+@($log | ForEach-Object {"$_"}) | Set-Content "$root\reports\2026-09-30\taskbar-weather\build.log"
$log
if($code -ne 0){throw 'Weather build failed'}
Get-FileHash $output | Select-Object Algorithm,Hash,Path
