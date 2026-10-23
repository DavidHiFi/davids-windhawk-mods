param(
    [string[]]$Paths = @('C:\', 'D:\Configuration Files', 'H:\Windhawk Configuration\notes', 'C:\Users\localuser\AppData\Local', 'H:\Windhawk Configuration'),
    [string]$Label = 'run',
    [int]$Rounds = 3,
    [int]$TimeoutSec = 60
)

# Median navigation time per folder across several rounds.
# Ms = time from Navigate() until the window reports the new location and is no longer busy.
# Uses one window this script owns; it opens and closes that window.

$ErrorActionPreference = 'Stop'
$start = 'C:\Users\localuser'
$sh = New-Object -ComObject Shell.Application

function Find-Window([string]$path) {
    $want = ([Uri]$path).AbsoluteUri.TrimEnd('/')
    foreach ($w in $sh.Windows()) {
        try {
            if ($w.LocationURL -and $w.LocationURL.TrimEnd('/') -eq $want) { return $w }
        } catch { }
    }
    return $null
}

Start-Process -FilePath 'explorer.exe' -ArgumentList ('"' + $start + '"')
$win = $null
for ($i = 0; $i -lt 80 -and -not $win; $i++) {
    Start-Sleep -Milliseconds 250
    $win = Find-Window $start
}
if (-not $win) { throw 'test window not found' }

$raw = @()
for ($r = 1; $r -le $Rounds; $r++) {
    foreach ($p in $Paths) {
        $want = ([Uri]$p).AbsoluteUri.TrimEnd('/')
        $sw = [Diagnostics.Stopwatch]::StartNew()
        $win.Navigate($p)
        $done = $false
        while ($sw.Elapsed.TotalSeconds -lt $TimeoutSec) {
            Start-Sleep -Milliseconds 20
            $loc = $win.LocationURL
            if ($loc -and $loc.TrimEnd('/') -eq $want -and -not $win.Busy) { $done = $true; break }
        }
        $raw += [pscustomobject]@{ Path = $p; Round = $r; Ms = $sw.ElapsedMilliseconds; Done = $done }
        Start-Sleep -Milliseconds 700
    }
}

$summary = $Paths | ForEach-Object {
    $p = $_
    $ms = @($raw | Where-Object { $_.Path -eq $p } | ForEach-Object { $_.Ms } | Sort-Object)
    $n = $ms.Count
    $median = if ($n % 2) { $ms[[int][math]::Floor($n / 2)] } else { [math]::Round(($ms[$n / 2 - 1] + $ms[$n / 2]) / 2) }
    [pscustomobject]@{ Label = $Label; Path = $p; MedianMs = $median; MinMs = $ms[0]; MaxMs = $ms[-1]; Runs = ($ms -join ' ') }
}
$summary | Format-Table -AutoSize | Out-String -Width 250
try { $win.Quit() } catch { }
[pscustomobject]@{ Label = $Label; Summary = $summary } | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path 'H:\Windhawk Configuration\reports\2026-10-13-explorer-lag' ("bench-$Label.json")) -Encoding utf8
