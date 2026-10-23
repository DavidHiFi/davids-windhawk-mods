[CmdletBinding()]
param([switch]$Audit,[switch]$Install,[switch]$Rollback)
$ErrorActionPreference='Stop'
$root='H:\Windhawk Configuration'
$id='local@windhawk-styler'
$key="HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$backup=Join-Path $root 'backups\2026-10-05\windhawk-styler'
$report=Join-Path $root 'reports\2026-10-05-windhawk-styler'
$build=Join-Path $root 'work\windhawk-styler'
$data='C:\ProgramData\Windhawk'
function State {
    $state=[ordered]@{time=(Get-Date -Format o);mod=$id}
    if(Test-Path $key){$state.registry=Get-ItemProperty $key | Select-Object LibraryFileName,Include,Version,Disabled,SettingsChangeTime;$state.settings=Get-ItemProperty "$key\Settings" | Select-Object backgroundColor,backgroundOpacity,blur,cardColor,cardOpacity,controlColor,accentColor,textColor,fontFamily,nativeTitleBar}
    $state.files=@(foreach($arch in '64','32'){
        $p=Join-Path $data "Engine\Mods\$arch\$($state.registry.LibraryFileName)"
        if(Test-Path $p){[ordered]@{path=$p;sha256=(Get-FileHash $p).Hash}}
    })
    $state.processes=@(Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" | Where-Object CommandLine -match 'tool-mod.*windhawk-styler' | Select-Object ProcessId,CommandLine)
    $state
}
if($Audit){State | ConvertTo-Json -Depth 6;return}
if($Rollback){
    Set-ItemProperty $key Disabled 1
    Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::Now.ToUnixTimeSeconds())
    Start-Sleep -Seconds 5
    State | ConvertTo-Json -Depth 6
    return
}
if($Install){throw 'Use work/windhawk-styler/v3/Build.ps1 and the install scripts in work/windhawk-styler/v3/elev to update the installed 1.3.0 build.'}
throw 'Choose -Audit or -Rollback.'
