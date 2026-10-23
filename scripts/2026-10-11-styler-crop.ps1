# Crop and enlarge a region of a PNG, so small details (a 1px border arc at a
# rounded corner) are visible when the image is viewed. Nearest-neighbour
# scaling keeps the pixel colors exact.
#
#   .\2026-10-11-styler-crop.ps1 -In shot.png -Out corner.png -X 40 -Y 300 -W 60 -H 60 -Scale 8
param(
    [Parameter(Mandatory)][string]$In,
    [Parameter(Mandatory)][string]$Out,
    [Parameter(Mandatory)][int]$X,
    [Parameter(Mandatory)][int]$Y,
    [int]$W = 60,
    [int]$H = 60,
    [int]$Scale = 8
)
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$src = [System.Drawing.Bitmap]::FromFile((Resolve-Path $In).Path)
try {
    $cw = [Math]::Min($W, $src.Width - $X)
    $ch = [Math]::Min($H, $src.Height - $Y)
    $dst = New-Object System.Drawing.Bitmap ($cw * $Scale), ($ch * $Scale)
    $g = [System.Drawing.Graphics]::FromImage($dst)
    $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
    $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
    $g.DrawImage($src, [System.Drawing.Rectangle]::new(0, 0, $cw * $Scale, $ch * $Scale),
                 [System.Drawing.Rectangle]::new($X, $Y, $cw, $ch), [System.Drawing.GraphicsUnit]::Pixel)
    $dst.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
    $g.Dispose(); $dst.Dispose()
} finally { $src.Dispose() }
"saved $Out (${cw}x${ch} -> x$Scale)"
