# Finalizes the tray-gap change: comments out the inert shave rules 64/65,
# keeps the live fix (sysTraySpacing=0, rules 60/61), bumps SettingsChangeTime.
$k = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$lines = [System.Collections.Generic.List[string]]::new()
$lines.Add('Windows Registry Editor Version 5.00')
$lines.Add('')
$lines.Add("[$k]")
$lines.Add('"controlStyles[64].target"="//"')
$lines.Add('"controlStyles[64].styles[0]"="//"')
$lines.Add('"controlStyles[65].target"="//"')
$lines.Add('"controlStyles[65].styles[0]"="//"')
$lines.Add('')
$tmp = Join-Path $env:TEMP 'styler-final-traygap.reg'
Set-Content -Path $tmp -Value $lines -Encoding Unicode
reg import $tmp
Remove-Item $tmp -ErrorAction SilentlyContinue
$t = [int][double]::Parse((Get-Date -UFormat %s))
reg add 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' /v SettingsChangeTime /t REG_DWORD /d $t /f
