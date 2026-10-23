Add-Type -AssemblyName System.Drawing
$out = "C:\Users\localuser\AppData\Local\Temp\dsh-XBo3bx\tbfix\live.png"
$bmp = New-Object System.Drawing.Bitmap -ArgumentList 2560, 64
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(2560, 64)))
$g.Dispose()
$bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Png)
# ink rows for the right side (x1990-2530) and left app icons (x20-300)
foreach ($z in @(@("right", 1990, 2530), @("left", 20, 300))) {
    $name = $z[0]; $x0 = $z[1]; $x1 = $z[2]
    $rows = @()
    for ($y = 0; $y -lt 64; $y++) {
        $ink = 0
        for ($x = $x0; $x -lt $x1; $x += 2) {
            $c = $bmp.GetPixel($x, $y)
            if ([Math]::Max($c.R, [Math]::Max($c.G, $c.B)) -gt 90) { $ink++ }
        }
        if ($ink -gt 2) { $rows += "$y($ink)" }
    }
    "$name ink: $($rows -join ' ')"
}
# quota zone colorful
$sat = 0; $total = 0
for ($x = 1850; $x -lt 2130; $x += 2) { for ($y = 6; $y -lt 42; $y += 2) { $c = $bmp.GetPixel($x, $y); $total++; $mx = [Math]::Max($c.R, [Math]::Max($c.G, $c.B)); $mn = [Math]::Min($c.R, [Math]::Min($c.G, $c.B)); if ($mx -gt 90 -and ($mx - $mn) -gt 40) { $sat++ } } }
"quota colorful: $([Math]::Round(100.0 * $sat / $total, 1))%"
$bmp.Dispose()
