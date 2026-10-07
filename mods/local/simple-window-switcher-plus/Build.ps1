[CmdletBinding()]
param(
 [string]$WindhawkRoot='C:\Program Files\Windhawk',
 [string]$EngineVersion='',
 [string]$OutputDirectory=''
)
$ErrorActionPreference='Stop'
if(-not $OutputDirectory){$OutputDirectory=Join-Path $PSScriptRoot 'build'}
if(-not $EngineVersion){
 $engine=Get-ChildItem (Join-Path $WindhawkRoot 'Engine') -Directory |
  Where-Object {Test-Path (Join-Path $_.FullName '64\windhawk.lib')} |
  Sort-Object LastWriteTime -Descending | Select-Object -First 1
 if(-not $engine){throw 'Windhawk engine import library not found'}
 $EngineVersion=$engine.Name
}
New-Item -ItemType Directory $OutputDirectory -Force|Out-Null
$header=Join-Path $OutputDirectory 'mod-id.h'
Set-Content $header '#define WH_MOD_ID L"local@simple-window-switcher-plus"' -Encoding ascii
$source=Join-Path $PSScriptRoot 'simple-window-switcher-plus.wh.cpp'
$libs='d3d11','dxgi','d2d1','dcomp','dwrite','dwmapi','ole32','oleaut32','uuid','runtimeobject','windowscodecs','shcore','shell32','gdi32','uxtheme','shlwapi','comctl32','gdiplus','version','user32','advapi32'
foreach($arch in '64','32'){
 $target=if($arch -eq '64'){'x86_64-w64-mingw32'}else{'i686-w64-mingw32'}
 $output=Join-Path $OutputDirectory "simple-window-switcher-plus-$arch.dll"
 $arguments=@('-std=c++23','-O2','-shared','-target',$target,'-DUNICODE','-D_UNICODE','-DWINVER=0x0A00','-D_WIN32_WINNT=0x0A00','-D_WIN32_IE=0x0A00','-DNTDDI_VERSION=0x0A000008','-D__USE_MINGW_ANSI_STDIO=0','-DWH_MOD','-include',$header,'-include','windhawk_api.h','-I',(Join-Path $WindhawkRoot 'Compiler\include'),'-Wno-pragma-pack','-Wno-pragma-system-header-outside-header','-Wl,--export-all-symbols',$source,(Join-Path $WindhawkRoot "Engine\$EngineVersion\$arch\windhawk.lib"))
 $arguments+=@($libs|ForEach-Object{"-l$_"})
 $arguments+=@('-o',$output)
 & (Join-Path $WindhawkRoot 'Compiler\bin\clang++.exe') @arguments
 if($LASTEXITCODE){throw "Build failed for $arch-bit target"}
 Get-FileHash $output -Algorithm SHA256
}
