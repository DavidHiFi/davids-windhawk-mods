# Sets one Fullscreen Start Plus setting and bumps SettingsChangeTime so the mod
# reloads it. Run elevated. Example: -Name monitor -Value 1 -Type String
param([string]$Name, [string]$Value, [ValidateSet('String', 'DWord')] [string]$Type = 'String')
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@fullscreen-start-plus'
$v = if ($Type -eq 'DWord') { [int]$Value } else { $Value }
Set-ItemProperty "$key\Settings" -Name $Name -Value $v -Type $Type
Set-ItemProperty $key -Name SettingsChangeTime -Value ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
"$Name = $((Get-ItemProperty "$key\Settings").$Name)"
