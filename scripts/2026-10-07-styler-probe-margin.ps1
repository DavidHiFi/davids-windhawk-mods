# Probe round 2: Margin-based, since transforms are stomped by state animations.
# rule 60: OmniButtonLeft (clock candidate) left margin 30
# rule 61: OmniButton#ControlCenterButton (network candidate) right margin 30
$k = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$lines = [System.Collections.Generic.List[string]]::new()
$lines.Add('Windows Registry Editor Version 5.00')
$lines.Add('')
$lines.Add("[$k]")
$lines.Add('"controlStyles[60].target"="SystemTray.OmniButtonLeft"')
$lines.Add('"controlStyles[60].styles[0]"="Margin=30,0,0,0"')
$lines.Add('"controlStyles[61].target"="SystemTray.OmniButton#ControlCenterButton"')
$lines.Add('"controlStyles[61].styles[0]"="Margin=0,0,30,0"')
$lines.Add('')
$tmp = Join-Path $env:TEMP 'styler-probe-margin.reg'
Set-Content -Path $tmp -Value $lines -Encoding Unicode
reg import $tmp
Remove-Item $tmp -ErrorAction SilentlyContinue
$t = [int][double]::Parse((Get-Date -UFormat %s))
reg add 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' /v SettingsChangeTime /t REG_DWORD /d $t /f
