# Passive drag-to-delete-plus live verifier. NO synthetic input at all: it
# polls the screen for the overlay (which appears during ANY real file drag
# the user performs) and captures rim measurements the moment it shows.
# Param: -OutDir evidence directory. Run elevated (CopyFromScreen is fine
# unelevated, but keep parity with the other scripts).

param([string]$OutDir = 'H:\Windhawk Configuration\reports\2026-10-18-drag-to-delete-plus-live',
      [int]$TimeoutSec = 150)

Add-Type -ReferencedAssemblies System.Drawing.dll -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class DtdW {
    [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
    public struct POINT { public int X, Y; }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

New-Item $OutDir -ItemType Directory -Force | Out-Null
$screen = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
$cxAim = [int]($screen.Width / 2)
$deadline = (Get-Date).AddSeconds($TimeoutSec)
$summary = [ordered]@{ Time = (Get-Date).ToString('o'); Screen = "$($screen.Width)x$($screen.Height)"; AimX = $cxAim; Mode = 'passive-watch' }

function Test-RingPx([System.Drawing.Bitmap]$bmp, [int]$x, [int]$y) {
    $c = $bmp.GetPixel($x, $y)
    return ($c.B -gt 70 -and $c.B -lt 240 -and ($c.B - $c.R) -gt 12)
}

function Test-RingBand([System.Drawing.Bitmap]$bmp, [int]$cx, [int]$cy, [int]$r) {
    $ok = 0
    foreach ($side in 'l', 'r', 't', 'b') {
        $flags = New-Object System.Collections.ArrayList
        for ($o = -5; $o -le 5; $o++) {
            switch ($side) {
                'l' { [void]$flags.Add((Test-RingPx $bmp ($cx - $r + $o) $cy)) }
                'r' { [void]$flags.Add((Test-RingPx $bmp ($cx + $r + $o) $cy)) }
                't' { [void]$flags.Add((Test-RingPx $bmp $cx ($cy - $r + $o))) }
                'b' { [void]$flags.Add((Test-RingPx $bmp $cx ($cy + $r + $o))) }
            }
        }
        $first = -1; $last = -1
        for ($i = 0; $i -lt 11; $i++) { if ($flags[$i]) { if ($first -lt 0) { $first = $i }; $last = $i } }
        if ($first -ge 1 -and $last -le 9 -and ($last - $first) -le 5) { $ok++ }
    }
    return ($ok -ge 3)
}

function Test-LabelPresent([System.Drawing.Bitmap]$bmp, [int]$cx, [int]$cy, [int]$r) {
    $y0 = $cy + $r + 6; $y1 = $cy + $r + 24
    for ($y = $y0; $y -le $y1; $y++) {
        for ($x = $cx - 80; $x -le $cx + 80; $x++) {
            $c = $bmp.GetPixel($x, $y)
            if ($c.B -gt 225 -and $c.R -gt 195) { return $true }
            if ($c.R -lt 70 -and $c.B -lt 80) { return $true }
        }
    }
    return $false
}

function Find-TargetByGeometry([System.Drawing.Bitmap]$bmp) {
    $cx = $cxAim
    $radii = @(34, 35, 33, 36, 32, 37, 31, 38, 30, 39, 40, 41, 42, 43, 44, 45, 46)
    $cys = @(108, 107, 109, 106, 110, 105, 111, 104, 112, 103, 113, 102, 114, 101, 115, 100, 116)
    foreach ($r in $radii) {
        foreach ($cy in $cys) {
            if ((Test-RingBand $bmp $cx $cy $r) -and (Test-LabelPresent $bmp $cx $cy $r)) {
                return @{ cx = $cx; cy = $cy; r = $r; top = ($cy - $r); bottom = ($cy + $r) }
            }
        }
    }
    return $null
}

function Measure-Rim([System.Drawing.Bitmap]$bmp, [hashtable]$t) {
    $res = [ordered]@{}
    foreach ($side in 'bottom', 'top', 'left', 'right') {
        $in = @(0, 0, 0); $out = @(0, 0, 0)
        for ($k = 0; $k -lt 3; $k++) {
            switch ($side) {
                'bottom' { $ci = $bmp.GetPixel($t.cx, $t.bottom - 5 - $k); $co = $bmp.GetPixel($t.cx, $t.bottom + 2 + $k) }
                'top'    { $ci = $bmp.GetPixel($t.cx, $t.top + 5 + $k);    $co = $bmp.GetPixel($t.cx, $t.top - 6 - $k) }
                'left'   { $ci = $bmp.GetPixel($t.cx - $t.r + 5 + $k, $t.cy); $co = $bmp.GetPixel($t.cx - $t.r - 6 - $k, $t.cy) }
                'right'  { $ci = $bmp.GetPixel($t.cx + $t.r - 5 - $k, $t.cy); $co = $bmp.GetPixel($t.cx + $t.r + 6 + $k, $t.cy) }
            }
            $i0 = [int]$in[0] + [int]$ci.R; $i1 = [int]$in[1] + [int]$ci.G; $i2 = [int]$in[2] + [int]$ci.B
            $in = @($i0, $i1, $i2)
            $o0 = [int]$out[0] + [int]$co.R; $o1 = [int]$out[1] + [int]$co.G; $o2 = [int]$out[2] + [int]$co.B
            $out = @($o0, $o1, $o2)
        }
        $inS = ($in | ForEach-Object { [int]($_ / 3) }); $outS = ($out | ForEach-Object { [int]($_ / 3) })
        $d0 = [Math]::Abs([int]$inS[0] - [int]$outS[0])
        $d1 = [Math]::Abs([int]$inS[1] - [int]$outS[1])
        $d2 = [Math]::Abs([int]$inS[2] - [int]$outS[2])
        $res[$side] = @{ inside = $inS; outside = $outS; maxDelta = [Math]::Max($d0, [Math]::Max($d1, $d2)) }
    }
    return $res
}

$best = $null; $bestShot = $null; $bestScore = 999; $poll = 0
try {
    while ((Get-Date) -lt $deadline -and -not $best) {
        $poll++
        $bmp = New-Object System.Drawing.Bitmap($screen.Width, $screen.Height)
        $g = [System.Drawing.Graphics]::FromImage($bmp)
        $g.CopyFromScreen(0, 0, 0, 0, $bmp.Size)
        $g.Dispose()
        $t = Find-TargetByGeometry $bmp
        if ($t) {
            # First detection: give the appear animation ~700ms to settle, then
            # capture the measurement frames.
            Start-Sleep -Milliseconds 700
            $bmp2 = New-Object System.Drawing.Bitmap($screen.Width, $screen.Height)
            $g2 = [System.Drawing.Graphics]::FromImage($bmp2)
            $g2.CopyFromScreen(0, 0, 0, 0, $bmp2.Size)
            $g2.Dispose()
            $t2 = Find-TargetByGeometry $bmp2
            if ($t2) {
                $best = $t2; $bestShot = $bmp2
                $bmp2.Save((Join-Path $OutDir '03-drag-rest.png'), [System.Drawing.Imaging.ImageFormat]::Png)
            } else { $bmp2.Dispose() }
            $bmp.Dispose()
            continue
        }
        if ($poll -eq 1 -or ($poll % 40) -eq 0) {
            $bmp.Save((Join-Path $OutDir ('08-watch-poll-{0:d3}.png' -f $poll)), [System.Drawing.Imaging.ImageFormat]::Png)
        }
        $bmp.Dispose()
        Start-Sleep -Milliseconds 250
    }

    if (-not $best) {
        $summary.Detected = $false
        $summary.Polls = $poll
        throw "Overlay not seen within the watch window ($poll polls)"
    }

    $summary.Detected = $true
    $summary.Target = $best
    $summary.CursorDuringDrag = $null
    $p = New-Object DtdW+POINT
    if ([DtdW]::GetCursorPos([ref]$p)) { $summary.CursorDuringDrag = "$($p.X),$($p.Y)" }
    $summary.Rim = Measure-Rim $bestShot $best

    # Zoomed evidence: whole target + bottom rim (the old artifact zone).
    $pad = 44
    $cw = 2 * ($best.r + $pad); $ch = 2 * ($best.r + $pad)
    $cx0 = [Math]::Max(0, $best.cx - [int]($cw / 2)); $cy0 = [Math]::Max(0, $best.cy - [int]($ch / 2))
    $cw3 = $cw * 3; $ch3 = $ch * 3
    $crop = New-Object System.Drawing.Bitmap($cw3, $ch3)
    $dstRect = New-Object System.Drawing.Rectangle(0, 0, $cw3, $ch3)
    $srcRect = New-Object System.Drawing.Rectangle($cx0, $cy0, $cw, $ch)
    $g = [System.Drawing.Graphics]::FromImage($crop)
    $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
    $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
    $g.DrawImage($bestShot, $dstRect, $srcRect, [System.Drawing.GraphicsUnit]::Pixel)
    $g.Dispose()
    $crop.Save((Join-Path $OutDir '05-target-rest-zoom-3x.png'), [System.Drawing.Imaging.ImageFormat]::Png)
    $crop.Dispose()

    $bz = 180; $bz4 = $bz * 4; $bh4 = 120 * 4
    $bsx = $best.cx - [int]($bz / 2)
    $bcrop = New-Object System.Drawing.Bitmap($bz4, $bh4)
    $bdst = New-Object System.Drawing.Rectangle(0, 0, $bz4, $bh4)
    $bsrc = New-Object System.Drawing.Rectangle($bsx, $best.cy, $bz, 120)
    $g = [System.Drawing.Graphics]::FromImage($bcrop)
    $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
    $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
    $g.DrawImage($bestShot, $bdst, $bsrc, [System.Drawing.GraphicsUnit]::Pixel)
    $g.Dispose()
    $bcrop.Save((Join-Path $OutDir '07-bottom-rim-zoom-4x.png'), [System.Drawing.Imaging.ImageFormat]::Png)
    $bcrop.Dispose()
}
catch {
    $summary.Error = $_.Exception.Message
}
finally {
    if ($bestShot) { $bestShot.Dispose() }
    $summary | ConvertTo-Json -Depth 6 | Set-Content (Join-Path $OutDir 'watch-summary.json') -Encoding UTF8
}
if ($summary.Error) { exit 1 } else { exit 0 }
