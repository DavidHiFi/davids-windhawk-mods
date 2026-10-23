param([string]$In, [string]$Out, [int]$RightPx = 960, [int]$Zoom = 3)
Add-Type -AssemblyName System.Drawing
$src = [System.Drawing.Image]::FromFile($In)
$cropW = [Math]::Min($RightPx, $src.Width)
$cropH = $src.Height
$srcX = $src.Width - $cropW
$bw = $cropW * $Zoom
$bh = $cropH * $Zoom
$bmp = New-Object System.Drawing.Bitmap($bw, $bh)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
$g.DrawImage($src, [System.Drawing.Rectangle]::new(0, 0, $bw, $bh), [System.Drawing.Rectangle]::new($srcX, 0, $cropW, $cropH), [System.Drawing.GraphicsUnit]::Pixel)
$g.Dispose()
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
$src.Dispose()
Write-Output "crop x=$srcX w=$cropW zoom=$Zoom -> $Out"