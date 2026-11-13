# Elevated. Restarts only the glow worker thread inside the Seamless Wobbly Windows glow tool:
# glow.enabled 0 then 1, each with a SettingsChangeTime bump so the engine tells the mod live.
# The wobble side in other processes only re-reads its settings. Backs up the mod key first.
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@seamless-wobbly-windows'
$dir = 'H:\Windhawk Configuration\backups\2026-11-13\seamless-wobbly-windows'
$stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@seamless-wobbly-windows' "$dir\mod-key-before-worker-restart-$stamp.reg" /y | Out-Null
"backup exit $LASTEXITCODE"
$old = (Get-ItemProperty -LiteralPath $key).SettingsChangeTime
"SettingsChangeTime was $old"
Set-ItemProperty -LiteralPath "$key\Settings" -Name 'glow.enabled' -Value 0 -Type DWord
Set-ItemProperty -LiteralPath $key -Name SettingsChangeTime -Value ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
"$(Get-Date -Format 'h:mm:ss tt') glow.enabled 0"
Start-Sleep 4
Set-ItemProperty -LiteralPath "$key\Settings" -Name 'glow.enabled' -Value 1 -Type DWord
Set-ItemProperty -LiteralPath $key -Name SettingsChangeTime -Value ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds() + 1) -Type DWord
"$(Get-Date -Format 'h:mm:ss tt') glow.enabled 1"
"glow.enabled now $((Get-ItemProperty -LiteralPath "$key\Settings").'glow.enabled')"
