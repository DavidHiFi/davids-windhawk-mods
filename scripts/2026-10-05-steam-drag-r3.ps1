[CmdletBinding()]
param([switch]$Audit,[switch]$Install,[switch]$Rollback)
$ErrorActionPreference='Stop'
$root='H:\Windhawk Configuration'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@window-manager'
$backup=Join-Path $root 'backups\2026-10-05-steam-drag'
$source='C:\ProgramData\Windhawk\ModsSource\local@window-manager.wh.cpp'
if($Audit -or (-not $Install -and -not $Rollback)) {Get-ItemProperty $key; return}
if($Install){
    if(Test-Path $backup){$skipBackup=$true}
    if(-not $skipBackup){New-Item -ItemType Directory $backup | Out-Null
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@window-manager' (Join-Path $backup 'before.reg') /y
    if($LASTEXITCODE){throw 'Registry backup failed'}
    Copy-Item $source (Join-Path $backup 'source.wh.cpp')
    Get-ItemProperty $key | Select-Object LibraryFileName,Version | ConvertTo-Json | Set-Content (Join-Path $backup 'before.json')}
}
Set-ItemProperty $key Disabled 1
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::Now.ToUnixTimeSeconds())
for($i=0;$i -lt 40;$i++){
    $tool=Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" | Where-Object CommandLine -Match '-tool-mod.*local@window-manager'
    if(-not $tool){break};Start-Sleep -Milliseconds 500
}
if($tool){throw 'Previous tool process did not exit; mod left disabled.'}
if($Install){
    foreach($arch in '64','32'){
        $from=Join-Path $root "Windhawk\window-pack\local@window-manager_1.1.1_3_$arch.dll"
        $to="C:\ProgramData\Windhawk\Engine\Mods\$arch\local@window-manager_1.1.1_3.dll"
        Copy-Item $from $to
        if((Get-FileHash $from).Hash -ne (Get-FileHash $to).Hash){throw 'DLL hash mismatch'}
    }
    Copy-Item (Join-Path $root 'Windhawk\window-pack\window-manager.wh.cpp') $source -Force
    Set-ItemProperty $key LibraryFileName 'local@window-manager_1.1.1_3.dll'
    Set-ItemProperty $key Version '1.1.1'
}else{
    $old=Get-Content (Join-Path $backup 'before.json') -Raw | ConvertFrom-Json
    Copy-Item (Join-Path $backup 'source.wh.cpp') $source -Force
    Set-ItemProperty $key LibraryFileName $old.LibraryFileName
    Set-ItemProperty $key Version $old.Version
}
Set-ItemProperty $key Disabled 0
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::Now.ToUnixTimeSeconds())
Start-Sleep -Seconds 5
Get-ItemProperty $key | Select-Object Disabled,LibraryFileName,Version,SettingsChangeTime
