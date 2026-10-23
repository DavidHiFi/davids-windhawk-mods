#Requires -RunAsAdministrator
# Evens the tray network-to-clock gap. -Rollback restores the pre-change backup.
param([switch]$Rollback)
$ErrorActionPreference='Stop'
if ($Rollback) {
  reg import "H:\Windhawk Configuration\backups\2026-10-11-tray-gap-even\windows-11-taskbar-styler-before.reg"
} else {
  $k="HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings"
  Set-ItemProperty -Path $k -Name "controlStyles[61].styles[0]" -Value "Margin=0,0,-4,0"
}
$t=[int][double]::Parse((Get-Date -UFormat %s))
Set-ItemProperty -Path "HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler" -Name SettingsChangeTime -Value $t -Type DWord
Get-ItemPropertyValue -Path "HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings" -Name "controlStyles[61].styles[0]"
