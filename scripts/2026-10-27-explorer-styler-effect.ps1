# Set the explorer styler's backgroundTranslucentEffect ('' = theme default, leaves the backdrop alone) and reload the mod.
param([string]$Effect = '')
$k = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey('SOFTWARE\Windhawk\Engine\Mods\windows-11-file-explorer-styler', $true)
$k.OpenSubKey('Settings', $true).SetValue('backgroundTranslucentEffect', $Effect, 'String')
$k.SetValue('SettingsChangeTime', [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds(), 'DWord')
