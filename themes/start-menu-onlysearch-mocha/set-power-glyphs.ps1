# Writes the six private-use glyph values of the OnlySearch Mocha theme into the
# Start Menu Styler settings, for when a Textual-mode paste dropped them.
# Run elevated after the theme has been saved once. Applies live.
#Requires -RunAsAdministrator
$ErrorActionPreference = 'Stop'
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-start-menu-styler'
$s = "$key\Settings"
$c = { param($h) [string][char]$h }

$want = @{
    "Windows.UI.Xaml.Controls.TextBlock[Text=$(& $c 0xE7E8)]" = 'power'
    "Windows.UI.Xaml.Controls.TextBlock[Text=$(& $c 0xF78B)]" = 'settings-alt'
    "Windows.UI.Xaml.Controls.TextBlock[Text=$(& $c 0xE713)]" = 'settings'
}
$props = (Get-ItemProperty $s).PSObject.Properties | Where-Object Name -Match '^controlStyles\[\d+\]\.target$'
$blank = @($props | Where-Object Value -EQ 'Windows.UI.Xaml.Controls.TextBlock[Text=]' |
    Sort-Object { [int]($_.Name -replace '^controlStyles\[(\d+)\].*', '$1') })
$targets = @($want.Keys | Sort-Object { @('power','settings-alt','settings').IndexOf($want[$_]) })
if ($blank.Count -ne 3) { throw "expected 3 blank glyph targets, found $($blank.Count); nothing changed" }

for ($i = 0; $i -lt 3; $i++) {
    Set-ItemProperty $s $blank[$i].Name $targets[$i]
}
$row = ((0xE72E, 0xE708, 0xE7E8, 0xE777) | ForEach-Object { & $c $_ }) -join '  '
Set-ItemProperty $s ($blank[0].Name -replace 'target$', 'styles[0]') "Text=$row"
Set-ItemProperty $key 'SettingsChangeTime' ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
'glyphs written'
