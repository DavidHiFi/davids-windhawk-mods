# Cleans probe artifacts and applies clock-inset shave rules in one .reg import.
$esc = { param($s) $s -replace '"', '""' }
$k = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$lines = [System.Collections.Generic.List[string]]::new()
$lines.Add('Windows Registry Editor Version 5.00')
$lines.Add('')
$lines.Add("[$k]")
# rule 60: kill malformed/marker styles, keep margin-0 probe result only as comment
$lines.Add('"controlStyles[60].styles[1]"="//"')
$lines.Add('"controlStyles[60].styles[9]"="//"')
# rule 61: kill green probe style (margin+width are the live fix)
$lines.Add('"controlStyles[61].styles[2]"="//"')
# rule 62: comment target (no effect, unused)
$lines.Add('"controlStyles[62].target"="//"')
# rule 63: comment target (no styles, unused)
$lines.Add('"controlStyles[63].target"="//"')
# rule 64: clock content presenter padding to zero (shave left inset)
$lines.Add('"controlStyles[64].target"="SystemTray.OmniButtonLeft > Grid > ContentPresenter"')
$lines.Add('"controlStyles[64].styles[0]"="Padding=0,0,0,0"')
# rule 65: clock button padding to zero
$lines.Add('"controlStyles[65].target"="SystemTray.OmniButtonLeft"')
$lines.Add('"controlStyles[65].styles[0]"="Padding=0,0,0,0"')
$lines.Add('')
$tmp = Join-Path $env:TEMP 'styler-clean.reg'
Set-Content -Path $tmp -Value $lines -Encoding Unicode
reg import $tmp
Remove-Item $tmp -ErrorAction SilentlyContinue
$t = [int][double]::Parse((Get-Date -UFormat %s))
reg add 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' /v SettingsChangeTime /t REG_DWORD /d $t /f
