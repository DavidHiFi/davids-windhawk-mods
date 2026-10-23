$ErrorActionPreference='Stop'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-weather'
$original=Get-ItemPropertyValue "$key\Settings" leftOffset
try {
 Set-ItemProperty "$key\Settings" leftOffset ($original+60)
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 Start-Sleep -Seconds 5
 & 'H:\System Configuration\scripts\taskbar-weather\Audit-WidgetFit.ps1' | Set-Content 'H:\System Configuration\reports\2026-10-03\taskbar-weather\widget-fit-shifted.json'
 Copy-Item 'H:\System Configuration\reports\2026-10-03\taskbar-weather\widget-fit-live.png' 'H:\System Configuration\reports\2026-10-03\taskbar-weather\widget-fit-shifted.png'
} finally {
 Set-ItemProperty "$key\Settings" leftOffset $original
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 Start-Sleep -Seconds 5
 & 'H:\System Configuration\scripts\taskbar-weather\Audit-WidgetFit.ps1' | Set-Content 'H:\System Configuration\reports\2026-10-03\taskbar-weather\widget-fit-restored.json'
 if((Get-ItemPropertyValue "$key\Settings" leftOffset) -ne $original){throw 'Position restore failed'}
}
