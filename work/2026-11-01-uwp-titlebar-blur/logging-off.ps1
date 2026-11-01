# Turns the mod's debug logging back off (run elevated).
Set-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@remove-uwp-title-bars-plus' LoggingEnabled 0 -Type DWord
(Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@remove-uwp-title-bars-plus').LoggingEnabled
