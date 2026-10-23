# Measures per-column content in the taskbar tray region to find the gap between
# the ethernet icon and the clock. Writes gap runs > 2px with their x ranges.
param(
  [string]$Image = "H:\Windhawk Configuration\reports\2026-10-07-tray-gap\traybar-0.png",
  [int]$FromX = 1900,
  [int]$ToX = 0
)
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap($Image, $false)
if ($ToX -le 0) { $ToX = $bmp.Width }
# background = most common color in region (sample row corners)
$bgCount = @{}
for ($x = $FromX; $x -lt $ToX; $x += 3) {
  foreach ($y in @(5, 15, 25, 35, 45)) {
    $c = $bmp.GetPixel($x, $y)
    if ($c.A -lt 200) { continue }
    $k = "{0:X2}{1:X2}{2:X2}" -f (([int][Math]::Round($c.R/4))*4), (([int][Math]::Round($c.G/4))*4), (([int][Math]::Round($c.B/4))*4)
    if ($bgCount.ContainsKey($k)) { $bgCount[$k]++ } else { $bgCount[$k] = 1 }
  }
}
$bg = ($bgCount.GetEnumerator() | Sort-Object Value -Descending | Select-Object -First 1).Key
$br = [Convert]::ToInt32($bg.Substring(0,2),16); $bgg = [Convert]::ToInt32($bg.Substring(2,2),16); $bb = [Convert]::ToInt32($bg.Substring(4,2),16)
Write-Output "image ${ToX}x50, background=$bg (R$br G$bgg B$bb)"
$cols = New-Object bool[] ($ToX - $FromX)
for ($x = $FromX; $x -lt $ToX; $x++) {
  $maxDev = 0
  for ($y = 3; $y -lt 47; $y++) {
    $c = $bmp.GetPixel($x, $y)
    if ($c.A -lt 200) { continue }
    $d = [Math]::Abs($c.R-$br) + [Math]::Abs($c.G-$bgg) + [Math]::Abs($c.B-$bb)
    if ($d -gt $maxDev) { $maxDev = $d }
  }
  $cols[$x - $FromX] = ($maxDev -gt 40)
}
# runs
$runs = @()
$cur = $cols[0]; $start = 0
for ($i = 1; $i -lt $cols.Length; $i++) {
  if ($cols[$i] -ne $cur) {
    $runs += [pscustomobject]@{ Type = if ($cur) {'CONTENT'} else {'GAP'}; From = $FromX + $start; To = $FromX + $i - 1; W = $i - $start }
    $cur = $cols[$i]; $start = $i
  }
}
$runs += [pscustomobject]@{ Type = if ($cur) {'CONTENT'} else {'GAP'}; From = $FromX + $start; To = $FromX + $cols.Length - 1; W = $cols.Length - $start }
$runs | Where-Object { $_.W -ge 2 } | ForEach-Object { "{0} x={1}..{2} w={3}" -f $_.Type, $_.From, $_.To, $_.W }
