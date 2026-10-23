[CmdletBinding()]
param([switch]$Install,[switch]$Rollback,[switch]$Audit)
$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$backup="$root\backups\2026-09-30\taskbar-weather"
$receipt="$root\reports\2026-09-30\taskbar-weather\installed.json"
$mod='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$monitor='HKLM:\SOFTWARE\Windhawk\Engine\Mods\taskbar-system-info'
$source="$root\work\taskbar-weather\taskbar-weather.wh.cpp"
$dll="$root\work\taskbar-weather\local@taskbar-weather_1.0.0_1.dll"
$settings=@(
 @{Path='HKCU:\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced';Name='TaskbarDa';Value=0},
 @{Path='HKCU:\SOFTWARE\Policies\Microsoft\Dsh';Name='AllowNewsAndInterests';Value=0},
 @{Path='HKLM:\SOFTWARE\Policies\Microsoft\Dsh';Name='AllowNewsAndInterests';Value=0},
 @{Path="$monitor\Settings";Name='leftOffset';Value=256}
)
function Read-Value($path,$name){
 $key=Get-Item -LiteralPath $path -ErrorAction SilentlyContinue
 if($key -and $key.GetValueNames() -contains $name){@{Path=$path;Name=$name;Exists=$true;Value=$key.GetValue($name);Kind=$key.GetValueKind($name).ToString()}}
 else{@{Path=$path;Name=$name;Exists=$false}}
}
function Write-Value($path,$name,$value,$kind='DWord'){
 $existing=Read-Value $path $name
 if($existing.Exists -and $existing.Value -eq $value){Write-Output "Already set $name";return}
 if(!(Test-Path -LiteralPath $path)){New-Item -Path $path -Force | Out-Null}
 New-ItemProperty -LiteralPath $path -Name $name -Value $value -PropertyType $kind -Force | Out-Null
 if((Get-ItemPropertyValue -LiteralPath $path -Name $name) -ne $value){throw "Read-back failed for $name"}
 Write-Output "Verified $name"
}
if(!$Install -and !$Rollback){
 foreach($s in $settings){Read-Value $s.Path $s.Name | ConvertTo-Json -Compress}
 if(Test-Path $mod){Get-ItemProperty $mod | Select-Object Disabled,LibraryFileName,Include,Version}
 exit
}
$admin=([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if(!$admin){throw 'Run through the saved silent-elevation cmd wrapper.'}
$now=[int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
if($Install){
 $resume=Test-Path "$backup\before.json"
 if((Test-Path $mod) -and (!$resume -or (Get-ItemProperty $mod).Disabled -eq 0)){throw 'Weather mod already enabled or has no rollback snapshot. Audit before replacing.'}
 $location=Get-Content "$root\work\taskbar-weather\private-location.json" -Raw | ConvertFrom-Json
 foreach($f in @($source,$dll)){if(!(Test-Path $f)){throw "Missing build file $f"}}
 New-Item -ItemType Directory -Force $backup | Out-Null
 if(!$resume){
  @($settings | ForEach-Object {Read-Value $_.Path $_.Name}) | ConvertTo-Json -Depth 5 | Set-Content "$backup\before.json" -Encoding UTF8
  Copy-Item $source "$backup\installed-source.wh.cpp"
  Copy-Item $dll "$backup\installed.dll"
 }
 Copy-Item $source 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-weather.wh.cpp'
 Copy-Item $dll 'C:\ProgramData\Windhawk\Engine\Mods\64\local@taskbar-weather_1.0.0_1.dll'
 Write-Value $mod Disabled 1
 foreach($kv in @(@('LibraryFileName','local@taskbar-weather_1.0.0_1.dll'),@('Include','explorer.exe'),@('Name','Independent Taskbar Weather'),@('Version','1.0.0'),@('Author','DavidHiFi'))){Write-Value $mod $kv[0] $kv[1] String}
 foreach($kv in @(@('latitude',$location.latitude),@('longitude',$location.longitude),@('fontFamily','Segoe UI'))){Write-Value "$mod\Settings" $kv[0] $kv[1] String}
 foreach($kv in @(@('updateMinutes',10),@('leftOffset',16),@('width',220),@('fontSize',12))){Write-Value "$mod\Settings" $kv[0] $kv[1]}
 foreach($s in $settings){Write-Value $s.Path $s.Name $s.Value}
 Write-Value $monitor SettingsChangeTime $now
 Write-Value $mod Disabled 0
 Write-Value $mod SettingsChangeTime $now
 Get-Process Widgets,WidgetService -ErrorAction SilentlyContinue | Stop-Process -Force
 [pscustomobject]@{Timestamp=(Get-Date).ToString('o');DllHash=(Get-FileHash $dll).Hash;SourceHash=(Get-FileHash $source).Hash;Include='explorer.exe';WidgetsPolicy=0;TaskbarDa=0;MonitorOffset=256;LocationSource='previous weather cache, automatically detected';ExplorerRestarted=$false;GlobalWindhawkRestarted=$false;VisualVerified=$false} | ConvertTo-Json | Set-Content $receipt -Encoding UTF8
 'Weather installed. Verify engine load and appearance separately.'
}
if($Rollback){
 if(!(Test-Path "$backup\before.json")){throw 'No rollback snapshot'}
 if(Test-Path $mod){Write-Value $mod Disabled 1;Write-Value $mod SettingsChangeTime $now}
 $localMonitor='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-system-info-weather'
 if(Test-Path $localMonitor){Write-Value $localMonitor Disabled 1;Write-Value $localMonitor SettingsChangeTime $now}
 if(Test-Path "$backup\monitor-before.reg"){
  Write-Value $monitor Disabled 1
  Write-Value $monitor SettingsChangeTime $now
  Start-Sleep -Seconds 4
  Copy-Item "$backup\monitor-source-before.wh.cpp" 'C:\ProgramData\Windhawk\ModsSource\taskbar-system-info.wh.cpp' -Force
  & reg.exe import "$backup\monitor-before.reg"
  if($LASTEXITCODE){throw 'Monitor registry restore failed'}
 }
 foreach($s in (Get-Content "$backup\before.json" -Raw | ConvertFrom-Json)){
  if($s.Exists){Write-Value $s.Path $s.Name $s.Value $s.Kind}
  else{Remove-ItemProperty -LiteralPath $s.Path -Name $s.Name -ErrorAction SilentlyContinue;"Removed previously absent $($s.Name)"}
 }
 Write-Value $monitor SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 'Rollback values restored. Weather DLL and source retained, disabled. No application restarted.'
}
