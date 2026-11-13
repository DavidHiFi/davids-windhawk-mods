# Seamless Wobbly Windows 1.1.1 and later: at the first moment the owner has been away 5 min and the
# desktop lock is free, installs the staged source (elevated, refuses if the live source moved
# from -BaseHash), checks the registry version, then runs the glow drag test on the main screen.
# One check a minute for up to -MaxMinutes. Exit 0 = installed and tested, 1 = no slot, 2 = failed.
# The caller holds the windhawk-engine lock.
param([Parameter(Mandatory)][string]$BaseHash, [string]$Version = '1.1.1', [int]$MaxMinutes = 110, [switch]$TestOnly)
$env:PATH = "C:\Users\localuser\AppData\Local\Programs\Python\Python313;" + $env:PATH
$me = 'e1584b96-f091-475c-8818-d1f8cd98cb1f'
$work = 'H:\Windhawk Configuration\work\2026-11-11-wobbly'
Add-Type -Namespace W -Name I -MemberDefinition '[StructLayout(LayoutKind.Sequential)] public struct L{public uint cb; public uint t;} [DllImport("user32.dll")] public static extern bool GetLastInputInfo(ref L l);'
function Get-IdleSeconds { $l = New-Object W.I+L; $l.cb = 8; [void][W.I]::GetLastInputInfo([ref]$l); [int](([uint32][Environment]::TickCount - $l.t) / 1000) }
$end = (Get-Date).AddMinutes($MaxMinutes)
while ((Get-Date) -lt $end) {
    if ((Get-IdleSeconds) -ge 300) {
        coop.cmd --as $me lock desktop --reason "wobble ${Version}: install, then drag a test window and record the main screen (~40 s)" --wait 60 --ttl 300 *> $null
        if ($LASTEXITCODE -eq 0) {
            try {
                $i = Get-IdleSeconds
                if ($i -ge 260) {
                    "idle $i s at $(Get-Date -Format 'h:mm:ss tt')"
                    if (-not $TestOnly) {
                    & 'H:\System Configuration\scripts\Invoke-Elevated.ps1' -File 'H:\Windhawk Configuration\scripts\2026-11-13-wobbly-install.ps1' `
                        -ArgumentList "-Staged '$work\local@seamless-wobbly-windows.wh.cpp' -BaseHash $BaseHash"    # single quotes: the wrapper double-quotes the whole command
                    Get-Content "$work\install.log"
                    $v = (Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@seamless-wobbly-windows').Version
                    "registry version $v"
                    if ($v -ne $Version) { "not installed"; exit 2 }
                    # The engine takes about 20 s to restart the glow tool; the test window must open after.
                    Start-Sleep 40
                    }
                    $out = "$work\live-$Version-$(Get-Date -Format HHmmss)"
                    $env:WOBBLE_MONITOR = '3'
                    python "H:\Windhawk Configuration\scripts\2026-11-13-wobbly-glow-test.py" $out
                    "test rc $LASTEXITCODE"
                    "out: $out"
                    exit 0
                }
            } finally { coop.cmd --as $me unlock desktop *> $null }
        }
    }
    Start-Sleep 60
}
"no slot by $(Get-Date -Format 'h:mm tt')"; exit 1
