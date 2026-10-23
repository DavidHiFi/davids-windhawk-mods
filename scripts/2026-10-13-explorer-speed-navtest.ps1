param(
    [string[]]$Paths = @('C:\', 'H:\Windhawk Configuration\notes', 'C:\Users\localuser\AppData\Local', 'H:\Windhawk Configuration'),
    [string]$Label = 'run',
    [int]$TimeoutSec = 90
)

# Times Explorer navigation through a window this script owns.
# Ms = time from Navigate() until the window reports the new location and is no longer busy.
# The auto-fit and content animation keep running for a few hundred ms after that.

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

$rows = @()
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
    $ms = $sw.ElapsedMilliseconds
    $resp = (Get-Process -Name explorer | Select-Object -First 1).Responding
    $rows += [pscustomobject]@{ Label = $Label; Path = $p; Ms = $ms; Done = $done; ExplorerResponding = $resp }
    Start-Sleep -Milliseconds 1000
}

$rows | Format-Table -AutoSize | Out-String -Width 220
try { $win.Quit() } catch { }
