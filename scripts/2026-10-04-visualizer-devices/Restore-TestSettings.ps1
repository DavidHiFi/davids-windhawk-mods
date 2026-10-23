$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@davids-audio-visualizer'
Set-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\ModsWritable\local@davids-audio-visualizer\LocalStorage' captureEndpointId ''
Set-ItemProperty "$key\Settings" 'diagnostics.enabled' 0
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
