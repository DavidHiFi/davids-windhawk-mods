$ErrorActionPreference = "Stop"
$bdir = "H:\Windhawk Configuration\backups\2026-10-21-tray-center"
$log = "$bdir\log-elevated-$(Get-Date -Format HHmmss).txt"
function L($m) { $m | Out-File $log -Append -Encoding utf8 }
try {
    $ks = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler"
    $cur = (Get-ItemProperty "$ks\Settings").'controlStyles[63].styles[1]'
    L "current styles[1]: $cur"
    if ($cur -ne 'Margin=0,4,0,0') { L "VERDICT: FAILED - unexpected current value: $cur"; exit 1 }
    Set-ItemProperty -Path "$ks\Settings" -Name 'controlStyles[63].styles[1]' -Value 'Margin=0,0,0,0' -Type String
    L "wrote styles[1] = Margin=0,0,0,0"
    $now = [DateTimeOffset]::Now.ToUnixTimeSeconds()
    Set-ItemProperty -Path $ks -Name SettingsChangeTime -Value $now -Type DWORD
    L "bumped SCT to $now"
    $v1 = (Get-ItemProperty "$ks\Settings").'controlStyles[63].styles[1]'
    $v2 = (Get-ItemProperty $ks).SettingsChangeTime
    L "readback styles[1]: $v1"
    L "readback SCT: $v2 (expected $now) match=$($v2 -eq $now)"
    L "lib: $((Get-ItemProperty $ks).LibraryFileName)"
    if ($v1 -eq 'Margin=0,0,0,0' -and $v2 -eq $now) { L "VERDICT: APPLIED" } else { L "VERDICT: FAILED - readback mismatch" }
} catch {
    L "VERDICT: FAILED - $($_.Exception.Message)"
}
