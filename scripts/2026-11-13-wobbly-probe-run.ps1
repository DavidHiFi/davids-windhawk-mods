# Runs the glow probe (opens the test window for 16 s, no clicks or keys) once the owner has
# been away 4 min and the desktop lock is free. Then prints the glow tool's thread count and memory.
param([int]$MaxMinutes = 110)
$env:PATH = "C:\Users\localuser\AppData\Local\Programs\Python\Python313;" + $env:PATH
$me = 'e1584b96-f091-475c-8818-d1f8cd98cb1f'
Add-Type -Namespace W -Name I -MemberDefinition '[StructLayout(LayoutKind.Sequential)] public struct L{public uint cb; public uint t;} [DllImport("user32.dll")] public static extern bool GetLastInputInfo(ref L l);'
function Get-IdleSeconds { $l = New-Object W.I+L; $l.cb = 8; [void][W.I]::GetLastInputInfo([ref]$l); [int](([uint32][Environment]::TickCount - $l.t) / 1000) }
function Show-Tool {
    Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" | Where-Object CommandLine -match 'seamless-wobbly' |
        ForEach-Object { $p = Get-Process -Id $_.ProcessId; "tool pid $($p.Id) threads $($p.Threads.Count) MB $([int]($p.WorkingSet64/1MB)) cpu $([math]::Round($p.CPU,2))" }
}
$end = (Get-Date).AddMinutes($MaxMinutes)
while ((Get-Date) -lt $end) {
    if ((Get-IdleSeconds) -ge 240) {
        coop.cmd --as $me lock desktop --reason "wobble glow probe: opens a test window 16 s, no input" --wait 60 --ttl 120 *> $null
        if ($LASTEXITCODE -eq 0) {
            try {
                if ((Get-IdleSeconds) -ge 200) {
                    "idle at $(Get-Date -Format 'h:mm:ss tt')"
                    Show-Tool
                    python "H:\Windhawk Configuration\scripts\2026-11-13-wobbly-glow-probe.py" "H:\Windhawk Configuration\work\2026-11-11-wobbly\probe-1.1.1-$(Get-Date -Format HHmmss)" 3
                    "probe rc $LASTEXITCODE"
                    Show-Tool
                    exit 0
                }
            } finally { coop.cmd --as $me unlock desktop *> $null }
        }
    }
    Start-Sleep 60
}
"no slot by $(Get-Date -Format 'h:mm tt')"; exit 1
