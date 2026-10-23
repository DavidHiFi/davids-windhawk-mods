# Read-only truth check for the input-death hunt logging state, 2026-10-22.
# Run elevated so process and service visibility are complete. Pure ASCII.
$svc = Get-Service -Name Windhawk
Write-Output ("engine {0} startType={1}" -f $svc.Status, $svc.StartType)
$dbg = @(Get-Process -Name DbgViewMini -ErrorAction SilentlyContinue)
Write-Output ("dbgview running: {0}" -f $dbg.Count)
foreach ($d in $dbg) {
    Write-Output ("pid {0} start {1}" -f $d.Id, $d.StartTime.ToString("HH:mm:ss"))
}
$mods = @(Get-ChildItem "HKLM:\SOFTWARE\Windhawk\Engine\Mods")
$on = @($mods | Where-Object { (Get-ItemProperty $_.PSPath -ErrorAction SilentlyContinue).LoggingEnabled -eq 1 })
Write-Output ("logging on {0} of {1}" -f $on.Count, $mods.Count)
$log = "H:\System Configuration\work\reports\windhog-dbgview-143006.txt"
if (Test-Path $log) {
    Write-Output ("capture log bytes {0}" -f (Get-Item $log).Length)
} else {
    Write-Output "capture log missing"
}
