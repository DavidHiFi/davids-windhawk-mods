# Sets one controlStyles entry on the taskbar-styler mod. Writes a temp .reg file
# (UTF-16, value names quoted) and imports it elevated, to dodge inline quoting traps.
# args: -Index N -Target "selector" [-StyleName k -StyleValue v] [-Probe red|green] [-BumpOnly]
param(
  [int]$Index = -1,
  [string]$Target,
  [string]$StyleName,
  [string]$StyleValue,
  [string]$Probe,
  [switch]$BumpOnly
)
$key = "HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler"
if (-not $BumpOnly) {
  $esc = { param($s) $s -replace '"', '""' }
  $lines = [System.Collections.Generic.List[string]]::new()
  $lines.Add('Windows Registry Editor Version 5.00')
  $lines.Add('')
  $lines.Add('[HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings]')
  if ($Target) {
    $lines.Add(('"controlStyles[{0}].target"' -f $Index) + '="' + (& $esc $Target) + '"')
  }
  if ($StyleName -and $StyleValue) {
    $lines.Add(('"controlStyles[{0}].styles[{1}]"' -f $Index, $StyleName) + '="' + (& $esc $StyleValue) + '"')
  }
  if ($Probe -eq 'red') {
    $lines.Add('"controlStyles[' + $Index + '].styles[9]"="Background=<SolidColorBrush Color=""#FF0000""/>"')
  }
  if ($Probe -eq 'green') {
    $lines.Add('"controlStyles[' + $Index + '].styles[9]"="Background=<SolidColorBrush Color=""#00FF00""/>"')
  }
  if ($Probe -eq 'clear') {
    # remove probe styles by setting them to comments (mod skips commented styles)
    $lines.Add('"controlStyles[' + $Index + '].styles[9]"="//probe cleared"')
  }
  $lines.Add('')
  $tmp = Join-Path $env:TEMP ("styler-rule-$Index.reg")
  Set-Content -Path $tmp -Value $lines -Encoding Unicode
  reg import $tmp
  Remove-Item $tmp -ErrorAction SilentlyContinue
}
$t = [int][double]::Parse((Get-Date -UFormat %s))
reg add "$key" /v SettingsChangeTime /t REG_DWORD /d $t /f
if ($Target) { reg query "$key\Settings" /v ("controlStyles[$Index].target") 2>$null }
if ($StyleName) { reg query "$key\Settings" /v ("controlStyles[$Index].styles[$StyleName]") 2>$null }
