# Row histogram for a specific x-window; prints first/last ink rows and pill-relative centers.
param([string]$In, [int]$X0, [int]$X1, [int]$Threshold = 60)
Add-Type -AssemblyName System.Drawing
$fullPath = (Get-Item $In).FullName
$bmp = New-Object System.Drawing.Bitmap -ArgumentList $fullPath
$first = -1; $last = -1
for ($y = 0; $y -lt $bmp.Height; $y++) {
    $ink = 0
    for ($x = $X0; $x -lt $X1; $x++) {
        if ($x -ge $bmp.Width) { break }
        $c = $bmp.GetPixel($x, $y)
        if ((0.299 * $c.R + 0.587 * $c.G + 0.114 * $c.B) -gt $Threshold) { $ink++ }
    }
    if ($ink -gt 1) {
        Write-Output ("row {0,2}  ink {1}" -f $y, $ink)
        if ($first -lt 0) { $first = $y }
        $last = $y
    }
}
$bmp.Dispose()
Write-Output "=> band $first..$last"
