[CmdletBinding()]
param([string]$OutputDirectory=$PSScriptRoot)
$ErrorActionPreference='Stop'
$id='local@davids-audio-visualizer'
$compiler='C:\Program Files\Windhawk\Compiler\bin\clang++.exe'
New-Item $OutputDirectory -ItemType Directory -Force | Out-Null
Set-Content "$OutputDirectory\modid.h" ('#define WH_MOD_ID L"{0}"' -f $id) -Encoding Ascii
foreach($arch in @('64','32')) {
    $target=if($arch -eq '64'){'x86_64-w64-mingw32'}else{'i686-w64-mingw32'}
    $argsList=@('-std=c++23','-O2','-shared','-target',$target,
        '-DUNICODE','-D_UNICODE','-DWINVER=0x0A00','-D_WIN32_WINNT=0x0A00',
        '-D_WIN32_IE=0x0A00','-DNTDDI_VERSION=0x0A000008','-D__USE_MINGW_ANSI_STDIO=0',
        '-DWH_MOD','-include',"$OutputDirectory\modid.h",'-include','windhawk_api.h',
        '-I','C:\Program Files\Windhawk\Compiler\include','-Wno-pragma-pack',
        '-Wno-pragma-system-header-outside-header','-Wl,--export-all-symbols',
        "$PSScriptRoot\davids-audio-visualizer.wh.cpp",
        "C:\Program Files\Windhawk\Engine\1.7.3_2\$arch\windhawk.lib",'-o',
        "$OutputDirectory\${id}_1.0.0_1_${arch}.dll")
    $libs='-ldxgi -ld2d1 -ld3d11 -ldcomp -ldwmapi -ldwrite -lgdi32 -lshcore -lshlwapi -lole32 -lshell32 -lksuser -lwindowscodecs -lruntimeobject -lwindowsapp -luuid -luser32 -ladvapi32'.Split(' ')
    & $compiler @argsList @libs
    if($LASTEXITCODE){throw "Build failed for $arch"}
    Get-FileHash "$OutputDirectory\${id}_1.0.0_1_${arch}.dll"
}
