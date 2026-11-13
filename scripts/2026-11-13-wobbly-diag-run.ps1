# Runs the glow diagnosis (test window up to 45 s, no clicks or keys) once the owner has been
# away 4 min and the desktop lock is free. Prints the glow tool's threads and memory around it.
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
        coop.cmd --as $me lock desktop --reason "wobble glow diagnosis: opens a test window up to 45 s, no input" --wait 60 --ttl 150 *> $null
        if ($LASTEXITCODE -eq 0) {
            try {
                if ((Get-IdleSeconds) -ge 200) {
                    "idle at $(Get-Date -Format 'h:mm:ss tt')"
                    Show-Tool
                    python -I "H:\Windhawk Configuration\scripts\2026-11-13-wobbly-glow-diag.py"
                    "diag rc $LASTEXITCODE"
                    Show-Tool
                    exit 0
                }
            } finally { coop.cmd --as $me unlock desktop *> $null }
        }
    }
    Start-Sleep 60
}
"no slot by $(Get-Date -Format 'h:mm tt')"; exit 1
