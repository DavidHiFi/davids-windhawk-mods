# Waits for the owner to be away (5 min idle) WITHOUT holding the engine lock,
# then takes the lock and gives the install test a short window to get the desktop lock.
# If another thread has the desktop, it lets the engine lock go and tries again later.
param([string]$BaseHash, [string]$Version, [int]$MaxMinutes = 110)
$me = 'e1584b96-f091-475c-8818-d1f8cd98cb1f'
Add-Type -Namespace WQ -Name Idle -MemberDefinition '[StructLayout(LayoutKind.Sequential)] public struct L{public uint cb; public uint t;} [DllImport("user32.dll")] public static extern bool GetLastInputInfo(ref L l);'
function Get-IdleSeconds { $l = New-Object WQ.Idle+L; $l.cb = 8; [void][WQ.Idle]::GetLastInputInfo([ref]$l); [int](([uint32][Environment]::TickCount - $l.t) / 1000) }
$end = (Get-Date).AddMinutes($MaxMinutes)
while ((Get-Date) -lt $end) {
    if ((Get-IdleSeconds) -lt 300) { Start-Sleep -Seconds 60; continue }
    coop.cmd --as $me lock windhawk-engine --reason "wobble $Version install and test (owner idle)" --wait 300 --ttl 900 *> $null
    if ($LASTEXITCODE -ne 0) { "engine lock busy at $(Get-Date -Format 'h:mm tt')"; Start-Sleep -Seconds 60; continue }
    $rc = 1
    try {
        & 'H:\Windhawk Configuration\scripts\2026-11-13-wobbly-install-test.ps1' -BaseHash $BaseHash -Version $Version -Effect '' -MaxMinutes 4 2>&1 | Select-Object -Last 40
        $rc = $LASTEXITCODE
    } finally {
        coop.cmd --as $me unlock windhawk-engine *> $null
        "unlocked ($LASTEXITCODE)"
    }
    "install test rc $rc"
    if ($rc -ne 1) { exit $rc }
    Start-Sleep -Seconds 120
}
"gave up by $(Get-Date -Format 'h:mm tt')"; exit 3
