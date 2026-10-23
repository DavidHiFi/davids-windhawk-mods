# Print the vertical ink band (first/last row with >2 bright pixels) for x >= From.
param([string]$In, [int]$From, [int]$Threshold = 70)
Add-Type -AssemblyName System.Drawing
$fullPath = (Get-Item $In).FullName
$bmp = New-Object System.Drawing.Bitmap -ArgumentList $fullPath
$first = -1; $last = -1
for ($y = 0; $y -lt $bmp.Height; $y++) {
    $ink = 0
    for ($x = $From; $x -lt $bmp.Width; $x++) {
        $c = $bmp.GetPixel($x, $y)
        if ((0.299 * $c.R + 0.587 * $c.G + 0.114 * $c.B) -gt $Threshold) { $ink++ }
    }
    if ($ink -gt 2) {
        if ($first -lt 0) { $first = $y }
        $last = $y
    }
}
$bmp.Dispose()
Write-Output ("ink band rows: $first..$last of $($bmp.Height-1)")
