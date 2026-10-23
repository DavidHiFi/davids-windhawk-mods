# Measure vertical ink extents in the taskbar strip: per-row count of non-background pixels.
param([string]$In, [int]$From = 1280)
Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap($In)
print = 'row ink'
$rows = @()
for ($y = 0; $y -lt $bmp.Height; $y++) {
    $ink = 0
    for ($x = $From; $x -lt $bmp.Width; $x++) {
        $c = $bmp.GetPixel($x, $y)
        $lum = 0.299*$c.R + 0.587*$c.G + 0.114*$c.B
        if ($lum -gt 70) { $ink++ }
    }
    $rows += [pscustomobject]@{ Row = $y; Ink = $ink }
}
$bmp.Dispose()
$rows | Format-Table -AutoSize | Out-String | Write-Output