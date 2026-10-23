param([string]$Out = "C:\Users\localuser\AppData\Local\Temp\dsh-XBo3bx\tbfix\verify.png")
Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap -ArgumentList 2560, 64
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(2560, 64)))
$g.Dispose()
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$stamp = Get-Date -Format "M/d/yyyy h:mm:ss tt"
"captured: $stamp"
$counts = @()
for ($y = 0; $y -lt 64; $y++) {
    $ink = 0
    for ($x = 1990; $x -lt 2530; $x += 2) {
        $c = $bmp.GetPixel($x, $y)
        if ([Math]::Max($c.R, [Math]::Max($c.G, $c.B)) -gt 90) { $ink++ }
    }
    $counts += $ink
}
# ring rows: full-width bright lines (>=200 samples)
$rings = @(); for ($y = 0; $y -lt 64; $y++) { if ($counts[$y] -ge 200) { $rings += $y } }
$ringTop = ($rings | Where-Object { $_ -lt 32 } | Select-Object -Last 1)
$ringBot = ($rings | Where-Object { $_ -ge 32 } | Select-Object -First 1)
if ($null -eq $ringTop -or $null -eq $ringBot) { "RING NOT FOUND: $($rings -join ' ')"; $bmp.Dispose(); exit 1 }
$pillCenter = ($ringTop + $ringBot) / 2.0
# content rows: ink between the rings, excluding ring rows and 1px around them
$inkRows = @(); for ($y = $ringTop + 2; $y -lt $ringBot - 1; $y++) { if ($counts[$y] -gt 2) { $inkRows += $y } }
if ($inkRows.Count -eq 0) { "NO CONTENT INK"; $bmp.Dispose(); exit 1 }
$cTop = $inkRows[0]; $cBot = $inkRows[-1]
$cCenter = ($cTop + $cBot) / 2.0
"ring rows: $ringTop..$ringBot (pill center $([Math]::Round($pillCenter, 1)))"
"content ink rows: $cTop..$cBot (center $([Math]::Round($cCenter, 1)))"
$delta = [Math]::Round($cCenter - $pillCenter, 1)
"offset: $delta px (positive = too low)"
if ([Math]::Abs($delta) -le 1.5) { "VERDICT: CENTERED" } elseif ($delta -gt 0) { "VERDICT: TOO LOW by $delta" } else { "VERDICT: TOO HIGH by $([Math]::Abs($delta))" }
# 4x view for the eye
$w = 2560; $h = 64 * 4
$bmp2 = New-Object System.Drawing.Bitmap -ArgumentList $w, $h
$g2 = [System.Drawing.Graphics]::FromImage($bmp2)
$g2.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g2.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
$dst = New-Object System.Drawing.Rectangle 0, 0, $w, $h
$srcRect = New-Object System.Drawing.Rectangle 0, 0, 2560, 64
$g2.DrawImage($bmp, $dst, $srcRect, [System.Drawing.GraphicsUnit]::Pixel)
$g2.Dispose()
$bmp2.Save(($Out -replace '\.png$', '-4x.png'), [System.Drawing.Imaging.ImageFormat]::Png)
$bmp2.Dispose()
$bmp.Dispose()
