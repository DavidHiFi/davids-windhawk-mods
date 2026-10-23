[CmdletBinding()]
param([switch]$Restore)
$ErrorActionPreference='Stop'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$value=if($Restore){10}else{1}
Set-ItemProperty "$key\Settings" updateMinutes $value
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
if((Get-ItemProperty "$key\Settings").updateMinutes -ne $value){throw 'Interval read-back failed'}
"Verified update interval $value minutes. Only this mod reloads."
