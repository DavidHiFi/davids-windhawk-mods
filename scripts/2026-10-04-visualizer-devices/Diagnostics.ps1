$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@davids-audio-visualizer'
Set-ItemProperty "$key\Settings" 'diagnostics.enabled' 1
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
