Add-Type -AssemblyName System.Drawing
$out = "H:\Windhawk Configuration\reports\2026-10-07-tray-gap"

# BEFORE: gap-zoom.png is already a 6x zoom of x=2380..2560 (1080x300)
$before = New-Object System.Drawing.Bitmap("$out\gap-zoom.png", $false)

# AFTER: same region, same 6x zoom, from the current traybar-0.png
$src = New-Object System.Drawing.Bitmap("$out\traybar-0.png", $false)
$cx = 2380; $cw = 180; $scale = 6
$crop = New-Object System.Drawing.Bitmap $cw, 50
$g = [System.Drawing.Graphics]::FromImage($crop)
$g.DrawImage($src, (New-Object System.Drawing.Rectangle 0, 0, $cw, 50), (New-Object System.Drawing.Rectangle $cx, 0, $cw, 50), [System.Drawing.GraphicsUnit]::Pixel)
$g.Dispose()
$src.Dispose()
$after = New-Object System.Drawing.Bitmap ($cw * $scale), (50 * $scale)
$g = [System.Drawing.Graphics]::FromImage($after)
$g.InterpolationMode = 'NearestNeighbor'
$g.DrawImage($crop, 0, 0, $cw * $scale, 50 * $scale)
$g.Dispose()
$crop.Dispose()

$labelH = 30
$H = $before.Height + $after.Height + 3 * $labelH + 10
$W = [Math]::Max($before.Width, $after.Width) + 16
$canvas = New-Object System.Drawing.Bitmap $W, $H
$g = [System.Drawing.Graphics]::FromImage($canvas)
$g.Clear([System.Drawing.Color]::FromArgb(20, 20, 28))
$font = New-Object System.Drawing.Font 'Segoe UI', 15
$white = [System.Drawing.Brushes]::White
$y = 6
$g.DrawString('BEFORE (x2380-2560, 6x): ~25px dead gap between ethernet icon and clock', $font, $white, 8, $y); $y += $labelH
$g.DrawImage($before, 8, $y); $y += $before.Height + $labelH
$g.DrawString('AFTER: gap closed to ~10px, even with the rest of the tray', $font, $white, 8, $y); $y += $labelH
$g.DrawImage($after, 8, $y)
$g.Dispose()
$canvas.Save("$out\before-after.png")
$canvas.Dispose()
$before.Dispose(); $after.Dispose()
'ok'
