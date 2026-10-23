$ErrorActionPreference='Stop'
$base='C:\ProgramData\Windhawk'
$repo='H:\Windhawk Configuration\davids-windhawk-mods\mods\local\shell-font-changer'
foreach($arch in '64','32') {
    $expected=(Get-FileHash "$repo\build\local@shell-font-changer_1.2.1_1_$arch.dll").Hash
    $actual=(Get-FileHash "$base\Engine\Mods\$arch\local@shell-font-changer_1.2.1_1.dll").Hash
    if($actual -ne $expected){throw 'Hash mismatch'}
    Write-Output "$arch DLL hash matches"
}
if((Get-FileHash "$repo\shell-font-changer.wh.cpp").Hash -ne (Get-FileHash "$base\ModsSource\local@shell-font-changer.wh.cpp").Hash){throw 'Source mismatch'}
Get-Process explorer,StartMenuExperienceHost,ShellHost,SearchHost,SystemSettings -ErrorAction SilentlyContinue | ForEach-Object {
    $name=$_.ProcessName
    try {$_.Modules | Where-Object ModuleName -Like '*shell-font-changer*' | ForEach-Object {Write-Output "$name $($_.ModuleName)"}} catch {Write-Output "$name modules unavailable"}
}

