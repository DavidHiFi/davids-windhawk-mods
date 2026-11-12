param([int]$On,[string]$Log)
$k='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@better-volume-mixer-plus'
& { Set-ItemProperty "$k\Settings" trayVolumeNumber $On -Type DWord
    Set-ItemProperty $k SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
    "trayVolumeNumber=$On" } *> $Log
