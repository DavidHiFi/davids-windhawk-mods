<#
Taskbar progress as a thin underline bar (windows-11-taskbar-styler).
Replaces the full-button progress block with a 3 px rounded bar where the
Pill Plus underline sits: faint track, solid accent fill, peach when paused,
red on error.
  -Audit    print the current values
  -Install  write the new values (run elevated) and hot-reload the mod
  -Rollback re-import the backup and hot-reload
#>
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$mod = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$set = "$mod\Settings"
$backup = 'H:\Windhawk Configuration\backups\2026-10-31\taskbar-progress\taskbar-styler-before.reg'

$values = [ordered]@{
  'styleConstants[20]'      = 'progressColor = <SolidColorBrush Color="{ThemeResource AdaptiveAccent}" Opacity="1"/>'
  'controlStyles[7].styles[0]'  = 'Canvas.ZIndex = 5'
  'controlStyles[7].styles[1]'  = 'MinWidth = {{BtnW-20}}'
  'controlStyles[7].styles[2]'  = 'MaxWidth = {{BtnW-20}}'
  'controlStyles[7].styles[3]'  = 'HorizontalAlignment = 1'
  'controlStyles[7].styles[5]'  = 'Height := 3'
  'controlStyles[7].styles[6]'  = 'Margin := 0,0,0,4'
  'controlStyles[7].styles[7]'  = 'VerticalAlignment = 2'
  'controlStyles[7].styles[8]'  = '// Progress shows as a 3 px bar where the Pill Plus underline sits (Pill.Dimensions 16,3, margin 4),'
  'controlStyles[7].styles[9]'  = '// a little wider than the underline so the fill reads. Centred under the icon.'
  'controlStyles[7].styles[10]' = '// Fixed height and margin track Pill Plus. ZIndex 5 lifts the bar over its ElasticPillOpen underline.'
  'controlStyles[8].styles[1]'  = 'CornerRadius := 1.5'
  'controlStyles[8].styles[3]'  = '// Rounded ends to match the underline (Pill.PillRadius).'
  'controlStyles[10].styles[0]' = 'Fill := <SolidColorBrush Color="#45475A"/>'
  'controlStyles[10].styles[1]' = 'Height = Auto'
  'controlStyles[10].styles[2]' = 'RadiusX := 1.5'
  'controlStyles[10].styles[3]' = 'RadiusY := 1.5'
  'controlStyles[10].styles[4]' = '// Solid Catppuccin surface1 track, opaque so the underline beneath never shows through. Height released from the native 1 px.'
  'controlStyles[11].styles[1]' = 'RadiusX := 1.5'
  'controlStyles[11].styles[2]' = 'RadiusY := 1.5'
  'controlStyles[11].styles[4]' = 'Fill@Paused := <SolidColorBrush Color="#FAB387"/>'
  'controlStyles[11].styles[5]' = 'Fill@Error := <SolidColorBrush Color="#F38BA8"/>'
  'controlStyles[11].styles[6]' = 'Fill@IndeterminatePaused := <SolidColorBrush Color="#FAB387"/>'
  'controlStyles[11].styles[7]' = 'Fill@IndeterminateError := <SolidColorBrush Color="#F38BA8"/>'
  'controlStyles[11].styles[8]' = '// Determinate fill | indeterminate sweep | trailing sweep. Catppuccin peach = paused, red = error.'
}

function Bump { Set-ItemProperty $mod -Name SettingsChangeTime -Type DWord -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) }

if ($Audit) { $p = Get-ItemProperty $set; foreach ($k in $values.Keys) { "$k = $($p.$k)" }; return }
if ($Install) {
  foreach ($k in $values.Keys) { Set-ItemProperty $set -Name $k -Type String -Value $values[$k] }
  Bump
  $p = Get-ItemProperty $set; $bad = @($values.Keys | ? { $p.$_ -ne $values[$_] })
  if ($bad) { throw "Mismatch: $($bad -join ', ')" }
  "Installed $($values.Count) values"
  return
}
if ($Rollback) {
  Remove-Item $set -Recurse -Force
  reg import $backup
  Bump
  'Rolled back'
}

