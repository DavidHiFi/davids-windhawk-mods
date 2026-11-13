# Waits (checking every 30 s) until the owner has not touched the PC for -Seconds, then exits 0.
# Exits 1 after -MaxMinutes. Reads input time only.
param([int]$Seconds = 300, [int]$MaxMinutes = 110)
Add-Type -Namespace W -Name I -MemberDefinition '[StructLayout(LayoutKind.Sequential)] public struct L { public uint cb; public uint t; } [DllImport("user32.dll")] public static extern bool GetLastInputInfo(ref L l);'
$end = (Get-Date).AddMinutes($MaxMinutes)
while ((Get-Date) -lt $end) {
    $l = New-Object W.I+L; $l.cb = 8
    [W.I]::GetLastInputInfo([ref]$l) | Out-Null
    $idle = [int](([Environment]::TickCount - $l.t) / 1000)
    if ($idle -ge $Seconds) { "idle $idle s at $(Get-Date -Format 'h:mm tt')"; exit 0 }
    Start-Sleep -Seconds 30
}
"owner stayed active until $(Get-Date -Format 'h:mm tt')"; exit 1
