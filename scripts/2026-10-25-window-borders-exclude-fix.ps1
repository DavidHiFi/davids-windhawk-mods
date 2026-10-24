# Fix local@window-borders Exclude: the engine reads Include/Exclude as a REG_SZ
# joined with '|' (like translucent-flyouts), not a REG_MULTI_SZ, so the earlier
# install injected the mod into Discord, Ableton and Stream Deck. Elevated only.
# Rollback: reg import backups\2026-10-25\window-borders\mod-key-before-exclude-fix.reg
param([switch]$Elevated)
$ErrorActionPreference = 'Stop'
$log = 'H:\Windhawk Configuration\backups\2026-10-25\window-borders\exclude-fix.log'
if (-not $Elevated) {
    & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File $PSCommandPath -ArgumentList '-Elevated'
    exit 0
}
Start-Transcript -Path $log -Force | Out-Null
try {
    $key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@window-borders'
    reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@window-borders' 'H:\Windhawk Configuration\backups\2026-10-25\window-borders\mod-key-before-exclude-fix.reg' /y | Out-Null
    $exclude = 'windhawk-ui.exe|dwm.exe|Discord*.exe|StreamDeck*.exe|Stream Deck*.exe|Matrix*.exe|Voicemeeter*.exe|Ableton*.exe'
    Remove-ItemProperty -Path $key -Name Exclude -ErrorAction SilentlyContinue
    New-ItemProperty -Path $key -Name Exclude -Value $exclude -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name SettingsChangeTime -Value ([DateTimeOffset]::Now.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null
    $k = Get-Item $key
    "Exclude kind = $($k.GetValueKind('Exclude')); value = $($k.GetValue('Exclude'))"
} catch { "ERROR: $($_.Exception.Message)" }
finally { Stop-Transcript | Out-Null }
