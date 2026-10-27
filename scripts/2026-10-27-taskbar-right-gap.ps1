# Evens the taskbar's inner gaps: the clock sat ~17px from the right border, the system monitor ~11px from the left.
# taskbarRightOffset 24 -> 20. Run elevated.
# Rollback: this script -Rollback (reg import of the backup, then marker bump).
param([switch]$Rollback)
$path = 'SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$bak = 'H:\Windhawk Configuration\backups\2026-10-27-taskbar-styler-before-right-gap.reg'
if ($Rollback) { reg import $bak | Out-Null } else {
    if (-not (Test-Path $bak)) { reg export "HKLM\$path" $bak /y | Out-Null }
    $s = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey("$path\Settings", $true)
    $s.SetValue('styleConstants[1]', 'taskbarRightOffset = 20', [Microsoft.Win32.RegistryValueKind]::String); $s.Close()
}
$k = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey($path, $true)
$k.SetValue('SettingsChangeTime', [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds(), [Microsoft.Win32.RegistryValueKind]::DWord); $k.Close()

