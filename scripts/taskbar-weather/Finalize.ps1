$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$mod='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
Set-ItemProperty $mod Disabled 1
Set-ItemProperty $mod SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Start-Sleep -Seconds 4
$disabled=& "$root\scripts\taskbar-weather\Audit-Live.ps1"
$disabled | Set-Content "$root\reports\2026-09-30\taskbar-weather\scoped-disable.json"
if(($disabled | ConvertFrom-Json).WindowPresent){throw 'Weather window did not disappear on disable'}
Set-ItemProperty "$mod\Settings" updateMinutes 10
Set-ItemProperty $mod Disabled 0
Set-ItemProperty $mod SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
'Scoped removal verified. Automatic interval restored to ten minutes. No process restarted.'
