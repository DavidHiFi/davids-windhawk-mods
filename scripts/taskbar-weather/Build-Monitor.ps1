$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$header="$root\work\taskbar-weather\monitor-id.h"
Set-Content $header '#define WH_MOD_ID L"local@taskbar-system-info-weather"' -Encoding Ascii
$output="$root\work\taskbar-weather\local@taskbar-system-info-weather_1.0.0_1.dll"
$argsList=@('-std=c++23','-O2','-shared','-target','x86_64-w64-mingw32','-DUNICODE','-D_UNICODE','-DWINVER=0x0A00','-D_WIN32_WINNT=0x0A00','-DWH_MOD','-include',$header,'-include','windhawk_api.h','-I','C:\Program Files\Windhawk\Compiler\include','-Wl,--export-all-symbols',"$root\work\taskbar-weather\taskbar-system-info.wh.cpp",'C:\Program Files\Windhawk\Engine\1.7.3_2\64\windhawk.lib','-lole32','-loleaut32','-lruntimeobject','-lpdh','-ldxgi','-lcomctl32','-DWIN32_LEAN_AND_MEAN','-o',$output)
& 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe' @argsList 2>&1 | Tee-Object "$root\reports\2026-09-30\taskbar-weather\monitor-build.log"
if($LASTEXITCODE -ne 0){throw 'Monitor build failed'}
Get-FileHash $output | Select-Object Hash
