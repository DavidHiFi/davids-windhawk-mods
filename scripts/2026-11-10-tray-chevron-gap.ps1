param([ValidateSet('Audit','Install','Rollback')][string]$Action='Audit',[string]$Margin='Margin=0,0,-4,0')
# Tray: the hidden-icons button sat 4 px further from the recycle bin than the icons sit from each other.
# Styler rule 54 (SystemTray.ChevronIconView) gets a negative right margin to close that gap.
$ErrorActionPreference='Stop'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$settings="$key\Settings"
$backup='H:\Windhawk Configuration\backups\2026-11-10-tray-chevron-gap'
$name='controlStyles[54].styles[0]'
$target=(Get-Item $settings).GetValue('controlStyles[54].target')
if($target -ne 'SystemTray.ChevronIconView'){throw "Rule 54 target changed: $target"}
if($Action -eq 'Audit'){(Get-Item $settings).GetValue($name);return}
New-Item $backup -ItemType Directory -Force | Out-Null
if($Action -eq 'Install'){
    if(-not(Test-Path "$backup\styler.reg")){
        & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' "$backup\styler.reg" /y | Out-Null
        if($LASTEXITCODE){throw 'Backup failed'}
        (Get-Item $settings).GetValue($name) | Set-Content "$backup\old-value.txt"
    }
    Set-ItemProperty $settings $name $Margin
}else{
    $old=(Get-Content "$backup\old-value.txt" -Raw).Trim()
    Set-ItemProperty $settings $name $old
}
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
$value=(Get-Item $settings).GetValue($name)
[ordered]@{Date=(Get-Date).ToString('o');Action=$Action;Rule54=$value;Restart=$false} | ConvertTo-Json | Set-Content "$backup\receipt-$Action.json"
$value
