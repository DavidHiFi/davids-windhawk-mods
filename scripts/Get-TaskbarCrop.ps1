# Crop+zoom the quota area of the taskbar capture. Writes only to %TEMP%.
param([string]$In, [string]$Out, [int]$X, [int]$Y, [int]$W, [int]$H, [int]$Zoom = 3)

Add-Type -AssemblyName System.Drawing
$src = [System.Drawing.Image]::FromFile($In)
$bmpW = $W * $Zoom
$bmpH = $H * $Zoom
$bmp = New-Object System.Drawing.Bitmap -ArgumentList $bmpW, $bmpH
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$destRect = New-Object System.Drawing.Rectangle -ArgumentList 0, 0, $bmpW, $bmpH
$srcRect = New-Object System.Drawing.Rectangle -ArgumentList $X, $Y, $W, $H
$g.DrawImage($src, $destRect, $srcRect, [System.Drawing.GraphicsUnit]::Pixel)
$g.Dispose()
$ms = New-Object System.IO.MemoryStream
$bmp.Save($ms, [System.Drawing.Imaging.ImageFormat]::Png)
$src.Dispose()
$bmp.Dispose()
[System.IO.File]::WriteAllBytes($Out, $ms.ToArray())
$ms.Dispose()
"saved $Out $((Get-Item $Out).Length) bytes"
