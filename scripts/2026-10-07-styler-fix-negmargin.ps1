# Proper fix: pull the network button flush against the clock with a negative
# left margin. Button size untouched (no clipping); the seam closes because the
# tray is right-packed. Keeps sysTraySpacing=0. Clears the inert OmniButtonLeft
# rule 60.
$k = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$lines = [System.Collections.Generic.List[string]]::new()
$lines.Add('Windows Registry Editor Version 5.00')
$lines.Add('')
$lines.Add("[$k]")
$lines.Add('"controlStyles[60].target"="//"')
$lines.Add('"controlStyles[60].styles[0]"="//"')
$lines.Add('"controlStyles[61].target"="SystemTray.OmniButton#ControlCenterButton"')
$lines.Add('"controlStyles[61].styles[0]"="Margin=0,0,-10,0"')
$lines.Add('"controlStyles[61].styles[1]"="//"')
$lines.Add('"controlStyles[61].styles[2]"="//"')
$lines.Add('"controlStyles[61].styles[9]"="//"')
$lines.Add('')
$tmp = Join-Path $env:TEMP 'styler-fix-negmargin.reg'
Set-Content -Path $tmp -Value $lines -Encoding Unicode
reg import $tmp
Remove-Item $tmp -ErrorAction SilentlyContinue
$t = [int][double]::Parse((Get-Date -UFormat %s))
reg add 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' /v SettingsChangeTime /t REG_DWORD /d $t /f
