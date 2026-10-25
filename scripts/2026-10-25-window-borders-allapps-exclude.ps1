# Sets local@window-borders Exclude to the installer's list plus the translucent-windows
# apps without recopying the DLL (it is loaded everywhere), then bumps SettingsChangeTime.
param([switch]$Elevated)
if (-not $Elevated) { & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList '-Elevated'; exit 0 }
$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@window-borders'
$src = Get-Content 'H:\Windhawk Configuration\Windhawk\window-borders\Install-window-borders.ps1' -Raw
$base = [regex]::Match($src, "\`$exclude = '([^']+)'").Groups[1].Value
$tw = Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\translucent-windows\Settings' -ErrorAction SilentlyContinue
$twApps = @($tw.PSObject.Properties | Where-Object { "$($_.Value)" -match '^[^\/|]+\.exe$' } | ForEach-Object { $_.Value })
$ex = (@($base) + $twApps) -join '|'
reg.exe export ($key -replace '^HKLM:', 'HKLM') "H:\Windhawk Configuration\backups\2026-10-25\window-borders\mod-key-before-exclude.reg" /y | Out-Null
Set-ItemProperty $key -Name Exclude -Value $ex
Set-ItemProperty $key -Name SettingsChangeTime -Value ([int][DateTimeOffset]::Now.ToUnixTimeSeconds()) -Type DWord
"Exclude now: $((Get-ItemProperty $key).Exclude)"
