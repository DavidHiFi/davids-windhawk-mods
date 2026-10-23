# Reverts the clip-causing rules 60/61 (Width=16 etc.), keeps sysTraySpacing=0.
$k = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$lines = [System.Collections.Generic.List[string]]::new()
$lines.Add('Windows Registry Editor Version 5.00')
$lines.Add('')
$lines.Add("[$k]")
foreach ($i in 60,61) {
  $lines.Add('"controlStyles[' + $i + '].target"="//"')
  $lines.Add('"controlStyles[' + $i + '].styles[0]"="//"')
  $lines.Add('"controlStyles[' + $i + '].styles[1]"="//"')
  $lines.Add('"controlStyles[' + $i + '].styles[2]"="//"')
  $lines.Add('"controlStyles[' + $i + '].styles[9]"="//"')
}
$lines.Add('')
$tmp = Join-Path $env:TEMP 'styler-revert-clip.reg'
Set-Content -Path $tmp -Value $lines -Encoding Unicode
reg import $tmp
Remove-Item $tmp -ErrorAction SilentlyContinue
$t = [int][double]::Parse((Get-Date -UFormat %s))
reg add 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' /v SettingsChangeTime /t REG_DWORD /d $t /f
