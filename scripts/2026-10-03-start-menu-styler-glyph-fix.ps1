# Restores the four Segoe Fluent glyph values the Textual-mode paste dropped.
# -Rollback re-imports the reg export taken before the change.
param([switch]$Rollback)
$ErrorActionPreference = 'Stop'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-start-menu-styler'
$bak = 'H:\Windhawk Configuration\backups\2026-10-03\start-menu-styler-glyphs\start-menu-styler.reg'
$log = 'H:\Windhawk Configuration\backups\2026-10-03\start-menu-styler-glyphs\apply.log'
if ($Rollback) { reg import $bak; "rolled back" | Out-File $log -Append }
else {
  if (-not (Test-Path $bak)) { reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-start-menu-styler' $bak /y | Out-Null }
  $g = { param($h) [string][char]$h }
  $s = "$key\Settings"
  Set-ItemProperty $s 'controlStyles[21].target' ("Windows.UI.Xaml.Controls.TextBlock[Text=" + (& $g 0xE7E8) + "]")
  Set-ItemProperty $s 'controlStyles[21].styles[0]' ("Text=" + ((0xE72E,0xE708,0xE7E8,0xE777 | % { & $g $_ }) -join '  '))
  Set-ItemProperty $s 'controlStyles[22].target' ("Windows.UI.Xaml.Controls.TextBlock[Text=" + (& $g 0xF78B) + "]")
  Set-ItemProperty $s 'controlStyles[23].target' ("Windows.UI.Xaml.Controls.TextBlock[Text=" + (& $g 0xE713) + "]")
  "applied" | Out-File $log -Append
}
Set-ItemProperty $key 'SettingsChangeTime' ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
"done $(Get-Date -Format o)" | Out-File $log -Append
