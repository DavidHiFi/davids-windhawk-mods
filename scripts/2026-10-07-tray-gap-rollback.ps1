# Rolls back the 2026-10-07 tray-gap change: restores sysTraySpacing=6 and
# comments out rule 61 (Margin=0,0,-10,0) plus the inert probe rules, then bumps.
$k = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$lines = [System.Collections.Generic.List[string]]::new()
$lines.Add('Windows Registry Editor Version 5.00')
$lines.Add('')
$lines.Add("[$k]")
$lines.Add('"styleConstants[9]"="sysTraySpacing = 6"')
foreach ($i in 60..65) {
  $lines.Add('"controlStyles[' + $i + '].target"="//"')
  $lines.Add('"controlStyles[' + $i + '].styles[0]"="//"')
  $lines.Add('"controlStyles[' + $i + '].styles[1]"="//"')
  $lines.Add('"controlStyles[' + $i + '].styles[2]"="//"')
  $lines.Add('"controlStyles[' + $i + '].styles[9]"="//"')
}
$lines.Add('')
$tmp = Join-Path $env:TEMP 'styler-rollback-traygap.reg'
Set-Content -Path $tmp -Value $lines -Encoding Unicode
reg import $tmp
Remove-Item $tmp -ErrorAction SilentlyContinue
$t = [int][double]::Parse((Get-Date -UFormat %s))
reg add 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' /v SettingsChangeTime /t REG_DWORD /d $t /f
