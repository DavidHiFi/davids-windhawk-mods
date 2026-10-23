<#
.SYNOPSIS
    Live visual verification for Drag to Delete Plus 1.1.0 rev2 (vertical
    backdrop-matched gradient). Reuses the user's existing Explorer window as
    the drag source: moves it to a known spot on top for a few seconds, drags
    a file from it toward the staging point, captures the overlay, measures
    rim blending at top/bottom/side, then cancels the drag with ESC and
    restores the window exactly. Nothing is ever dropped: ESC lands before
    the button is released on every attempt.
#>
param(
    [string]$OutDir = 'H:\Windhawk Configuration\reports\2026-10-18-drag-to-delete-plus-live'
)
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

Add-Type -ReferencedAssemblies System.Drawing.dll -TypeDefinition @"
using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;

public static class Dtd {
    [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
    [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint d, UIntPtr e);
    [DllImport("user32.dll")] public static extern void keybd_event(byte k, byte s, uint f, UIntPtr e);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] private static extern int GetClassNameW(IntPtr h, StringBuilder sb, int max);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] private static extern int GetWindowTextW(IntPtr h, StringBuilder sb, int max);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool MoveWindow(IntPtr h, int x, int y, int w, int ht, bool repaint);
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int cmd);
    [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr after, int x, int y, int w, int ht, uint flags);
    [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
    [DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h, uint msg, IntPtr w, IntPtr l);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] public static extern IntPtr FindWindowW(string cls, string title);
    [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
    [DllImport("user32.dll")] public static extern short GetAsyncKeyState(int k);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    public delegate bool EnumProc(IntPtr h, IntPtr l);
    public struct RECT { public int Left, Top, Right, Bottom; }
    public const uint LEFTDOWN = 0x02, LEFTUP = 0x04;
    public static int LastError;

    // True while the left button is physically held; catches the case where
    // the user's own mouse released our synthetic drag mid-flight.
    public static bool LeftButtonDown() { return (GetAsyncKeyState(0x01) & 0x8000) != 0; }

    // True while the mod's overlay window exists AND is shown — fires when
    // the DoDragDrop hook raised the target even if the paint then failed.
    public static bool OverlayVisible() {
        IntPtr h = FindWindowW("WindhawkDragToDeletePlusOverlay", null);
        return (h != IntPtr.Zero) && IsWindowVisible(h);
    }

    public static string WindowsList() {
        var sb2 = new StringBuilder();
        EnumWindows(delegate(IntPtr h, IntPtr l) {
            var sb = new StringBuilder(256);
            if (GetClassNameW(h, sb, 256) > 0 && sb.ToString() == "CabinetWClass") {
                var t = new StringBuilder(512);
                GetWindowTextW(h, t, 512);
                sb2.Append(h.ToInt64() + " | " + t.ToString() + "\n");
            }
            return true;
        }, IntPtr.Zero);
        return sb2.ToString();
    }

    public static IntPtr WindowWithTitle(string needle) {
        IntPtr hit = IntPtr.Zero;
        EnumWindows(delegate(IntPtr h, IntPtr l) {
            var t = new StringBuilder(512);
            if (GetWindowTextW(h, t, 512) > 0 && t.ToString().Contains(needle)) { hit = h; return false; }
            return true;
        }, IntPtr.Zero);
        return hit;
    }

    public static IntPtr WindowWithClass(string cls, int minWidth) {
        IntPtr hit = IntPtr.Zero; int best = 0;
        EnumWindows(delegate(IntPtr h, IntPtr l) {
            var sb = new StringBuilder(256);
            if (GetClassNameW(h, sb, 256) > 0 && sb.ToString() == cls) {
                RECT r;
                if (GetWindowRect(h, out r)) {
                    int w = r.Right - r.Left;
                    if (w > minWidth && w > best) { best = w; hit = h; }
                }
            }
            return true;
        }, IntPtr.Zero);
        return hit;
    }

    public static int[] RectOf(IntPtr h) {
        RECT r;
        if (!GetWindowRect(h, out r)) return null;
        return new int[] { r.Left, r.Top, r.Right, r.Bottom };
    }

    public static void CancelDrag() {
        keybd_event(0x1B, 0, 0, UIntPtr.Zero);
        System.Threading.Thread.Sleep(120);
        keybd_event(0x1B, 0, 2, UIntPtr.Zero);
        System.Threading.Thread.Sleep(120);
        mouse_event(LEFTUP, 0, 0, 0, UIntPtr.Zero);
    }

    public static bool IsRingPixel(Bitmap bmp, int x, int y) {
        Color c = bmp.GetPixel(x, y);
        return c.B > 70 && c.B < 160 && (c.B - c.R) > 12;
    }
}
"@

New-Item $OutDir -ItemType Directory -Force | Out-Null
$screen = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
$cxAim = [int]($screen.Width / 2)
$summary = [ordered]@{ Time = (Get-Date).ToString('o'); Screen = "$($screen.Width)x$($screen.Height)"; AimX = $cxAim }
$hwnd = [IntPtr]::Zero; $browser = [IntPtr]::Zero
$dragActive = $false
$errText = $null

function Save-Shot([string]$name) {
    $bmp = New-Object System.Drawing.Bitmap($screen.Width, $screen.Height)
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen(0, 0, 0, 0, $bmp.Size)
    $g.Dispose()
    $bmp.Save((Join-Path $OutDir $name), [System.Drawing.Imaging.ImageFormat]::Png)
    return $bmp
}

# Locate the overlay by its trash-icon glyph: bright pixels in a narrow
# column at top-center, scanned only above the label band. The icon is
# horizontally centered on the monitor and vertically centered in the
# circle, so its row span gives the circle's cy. Returns $null when absent.
function Find-IconCy([System.Drawing.Bitmap]$bmp) {
    $cx = $cxAim
    $top = -1; $bot = -1; $total = 0
    for ($y = 55; $y -le 142; $y++) {
        $row = 0
        for ($x = $cx - 26; $x -le $cx + 26; $x++) {
            $c = $bmp.GetPixel($x, $y)
            if ($c.B -gt 190 -and $c.R -gt 170) { $row++ }
        }
        if ($row -ge 2) { if ($top -lt 0) { $top = $y }; $bot = $y; $total += $row }
    }
    if ($top -lt 0 -or ($bot - $top) -lt 12 -or $total -lt 40) { return $null }
    return @{ cy = [int](($top + $bot) / 2); top = $top; bottom = $bot }
}

# First row of the hint label's light text below the icon; the mod lays the
# label out at cy + r + 6, so this yields the true drawn radius.
function Find-LabelTop([System.Drawing.Bitmap]$bmp, [int]$iconBottom) {
    $cx = $cxAim
    for ($y = $iconBottom + 8; $y -le $iconBottom + 45; $y++) {
        $row = 0
        for ($x = $cx - 80; $x -le $cx + 80; $x++) {
            $c = $bmp.GetPixel($x, $y)
            if ($c.B -gt 200 -and ($c.B - $c.R) -gt 15) { $row++ }
        }
        if ($row -ge 3) { return $y }
    }
    return $null
}

function Find-TargetByGeometry([System.Drawing.Bitmap]$bmp) {
    $icon = Find-IconCy $bmp
    if (-not $icon) { return $null }
    $cy = $icon.cy
    $labelTop = Find-LabelTop $bmp $icon.bottom
    $r = 34
    if ($labelTop) { $r = $labelTop - 6 - $cy }
    if ($r -lt 20 -or $r -gt 60) { $r = 34 }
    return @{ cx = $cxAim; cy = $cy; r = $r; top = ($cy - $r); bottom = ($cy + $r); iconTop = $icon.top; iconBottom = $icon.bottom; labelTop = $labelTop }
}

function Measure-Rim([System.Drawing.Bitmap]$bmp, [hashtable]$t) {
    # Measure the fill-to-backdrop delta at the TRUE drawn radius (derived
    # from the label position) and one pixel either side of it. Bottom
    # outside samples are guarded against the label text.
    $res = [ordered]@{}
    $labelTop = $t.labelTop
    if (-not $labelTop) { $labelTop = $t.cy + $t.r + 6 }
    foreach ($side in 'bottom', 'top', 'left', 'right') {
        $maxDelta = 0; $worstR = 0; $worstIn = $null; $worstOut = $null
        foreach ($rr in ($t.r - 1), $t.r, ($t.r + 1)) {
            $in = @(0, 0, 0); $out = @(0, 0, 0); $no = 0
            for ($k = 0; $k -lt 3; $k++) {
                switch ($side) {
                    'bottom' {
                        $iy = $t.cy + $rr - 5 - $k; $oy = $t.cy + $rr + 2 + $k
                        if ($oy -lt ($labelTop - 1)) {
                            $ci = $bmp.GetPixel($t.cx, $iy); $co = $bmp.GetPixel($t.cx, $oy)
                            $in = @(([int]$in[0] + [int]$ci.R), ([int]$in[1] + [int]$ci.G), ([int]$in[2] + [int]$ci.B))
                            $out = @(([int]$out[0] + [int]$co.R), ([int]$out[1] + [int]$co.G), ([int]$out[2] + [int]$co.B))
                            $no++
                        }
                    }
                    'top'    {
                        $ci = $bmp.GetPixel($t.cx, ($t.cy - $rr + 5 + $k)); $co = $bmp.GetPixel($t.cx, ($t.cy - $rr - 6 - $k))
                        $in = @(([int]$in[0] + [int]$ci.R), ([int]$in[1] + [int]$ci.G), ([int]$in[2] + [int]$ci.B))
                        $out = @(([int]$out[0] + [int]$co.R), ([int]$out[1] + [int]$co.G), ([int]$out[2] + [int]$co.B))
                        $no++
                    }
                    'left'   {
                        $ci = $bmp.GetPixel(($t.cx - $rr + 5 + $k), $t.cy); $co = $bmp.GetPixel(($t.cx - $rr - 6 - $k), $t.cy)
                        $in = @(([int]$in[0] + [int]$ci.R), ([int]$in[1] + [int]$ci.G), ([int]$in[2] + [int]$ci.B))
                        $out = @(([int]$out[0] + [int]$co.R), ([int]$out[1] + [int]$co.G), ([int]$out[2] + [int]$co.B))
                        $no++
                    }
                    'right'  {
                        $ci = $bmp.GetPixel(($t.cx + $rr - 5 - $k), $t.cy); $co = $bmp.GetPixel(($t.cx + $rr + 6 + $k), $t.cy)
                        $in = @(([int]$in[0] + [int]$ci.R), ([int]$in[1] + [int]$ci.G), ([int]$in[2] + [int]$ci.B))
                        $out = @(([int]$out[0] + [int]$co.R), ([int]$out[1] + [int]$co.G), ([int]$out[2] + [int]$co.B))
                        $no++
                    }
                }
            }
            if ($no -lt 1) { continue }
            $d = 0
            for ($ch = 0; $ch -lt 3; $ch++) {
                $di = [Math]::Abs(([int]([int]$in[$ch] / $no)) - ([int]([int]$out[$ch] / $no)))
                if ($di -gt $d) { $d = $di }
            }
            if ($d -gt $maxDelta) {
                $maxDelta = $d; $worstR = $rr
                $worstIn = @([int]([int]$in[0] / $no), [int]([int]$in[1] / $no), [int]([int]$in[2] / $no))
                $worstOut = @([int]([int]$out[0] / $no), [int]([int]$out[1] / $no), [int]([int]$out[2] / $no))
            }
        }
        $res[$side] = @{ maxDelta = $maxDelta; worstAtR = $worstR; inside = $worstIn; outside = $worstOut }
    }
    return $res
}

try {
    $tmpDir = $null; $closeMine = $false
    $explorerHwnd = [Dtd]::WindowWithTitle('File Explorer')
    if ($explorerHwnd -eq [IntPtr]::Zero) {
        # No Explorer window exists: a fresh folder opens in its own window.
        $tmpDir = Join-Path $env:ProgramData 'dtd-verify'
        New-Item $tmpDir -ItemType Directory -Force | Out-Null
        Set-Content (Join-Path $tmpDir 'drag-me.txt') 'drag-to-delete-plus live verification scratch'
        Start-Process explorer.exe $tmpDir
        $deadline = (Get-Date).AddSeconds(10)
        do {
            Start-Sleep -Milliseconds 400
            $explorerHwnd = [Dtd]::WindowWithTitle('dtd-verify')
        } while ($explorerHwnd -eq [IntPtr]::Zero -and (Get-Date) -lt $deadline)
        if ($explorerHwnd -ne [IntPtr]::Zero) { $closeMine = $true }
    }
    if ($explorerHwnd -eq [IntPtr]::Zero) { throw 'No File Explorer window available for the drag source' }
    Write-Output ("stage: source window ready hwnd={0} scratch={1}" -f $explorerHwnd, $closeMine)
    $hwnd = $explorerHwnd
    $summary.UsedScratchWindow = $closeMine
    $r4 = [Dtd]::RectOf($hwnd)
    if (-not $r4) { throw 'GetWindowRect failed' }
    $rx = [int]$r4[0]; $ry = [int]$r4[1]
    $rw = [int]$r4[2] - [int]$r4[0]; $rh = [int]$r4[3] - [int]$r4[1]
    $oldRect = @($rx, $ry, $rw, $rh)
    $wasMaximized = ($rw -ge $screen.Width - 8 -and $rh -ge $screen.Height - 8)
    $summary.ExplorerWindow = "$($oldRect -join 'x')" + $(if ($wasMaximized) { ' (maximized)' })
    $summary.ExplorerRectBefore = $oldRect

    # Bring the window up at a known spot that keeps the top-center scan
    # region clean; remember the original rect to restore afterwards.
    [Dtd]::ShowWindow($hwnd, 9) | Out-Null
    [Dtd]::MoveWindow($hwnd, 60, 500, 800, 500, $true) | Out-Null
    # TOPMOST, not just TOP: the user's own windows (Windhawk UI etc.) steal
    # HWND_TOP back the moment they interact, and then our clicks land in
    # THEIR window instead of the file list.
    [Dtd]::SetWindowPos($hwnd, [IntPtr](-1), 0, 0, 0, 0, 0x0003) | Out-Null  # HWND_TOPMOST
    [Dtd]::SetForegroundWindow($hwnd) | Out-Null
    Write-Output 'stage: window positioned topmost'
    Start-Sleep -Milliseconds 900

    $winX = 60; $winY = 500
    # Warm-up: the first mousedown after window activation tends to be consumed
    # as the activating click (the drag only engages from the second press),
    # so burn one throwaway drag before the real attempts.
    [Dtd]::SetCursorPos(460, 670) | Out-Null
    Start-Sleep -Milliseconds 120
    [Dtd]::mouse_event([Dtd]::LEFTDOWN, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 130
    for ($i = 1; $i -le 8; $i++) {
        [Dtd]::SetCursorPos((460 + $i * 10), 670) | Out-Null
        Start-Sleep -Milliseconds 10
    }
    [Dtd]::CancelDrag()
    $dragActive = $false
    Start-Sleep -Milliseconds 400
    # Details-view rows start ~y+155; keep x past the nav pane (x+300).
    $candidates = @(@(400, 170), @(550, 170), @(700, 170), @(300, 170),
                    @(400, 204), @(550, 204), @(700, 204), @(300, 204),
                    @(400, 240), @(550, 240), @(700, 240), @(300, 240),
                    @(400, 274), @(550, 274), @(700, 274), @(300, 274),
                    @(400, 310), @(550, 310))
    $t = $null; $shotC = $null; $attempt = 0
    foreach ($c in $candidates) {
        $attempt++
        Write-Output ("stage: attempt {0} from {1},{2}" -f $attempt, $c[0], $c[1])
        $sx = $winX + $c[0]; $sy = $winY + $c[1]
        [Dtd]::SetCursorPos($sx, $sy) | Out-Null
        Start-Sleep -Milliseconds 120
        [Dtd]::mouse_event([Dtd]::LEFTDOWN, 0, 0, 0, [UIntPtr]::Zero)
        $dragActive = $true
        Start-Sleep -Milliseconds 130
        for ($i = 1; $i -le 14; $i++) {
            $t2 = $i / 14.0
            [Dtd]::SetCursorPos([int]($sx + ($cxAim - $sx) * $t2), [int]($sy + (620 - $sy) * $t2)) | Out-Null
            Start-Sleep -Milliseconds 12
        }
        Start-Sleep -Milliseconds 650
        if (-not [Dtd]::LeftButtonDown()) {
            # The drag died mid-flight (user's mouse released the button).
            $dragActive = $false
            $summary.DragDied = ([int]$summary.DragDied + 1)
            Start-Sleep -Milliseconds 300
            continue
        }
        $ovVisible = [Dtd]::OverlayVisible()
        if ($ovVisible) { $summary.OverlayVisibleAt = $attempt }
        $shot = Save-Shot ("03-drag-rest-a$attempt.png")
        $t = Find-TargetByGeometry $shot
        if ($t) { $shotC = $shot; $summary.DragFrom = "$($c[0]),$($c[1])"; break }
        if ($ovVisible) {
            # The mod raised its overlay window during the drag, but nothing
            # measurable was painted: the paint produced a transparent frame.
            $summary.PaintBroken = $true
            [Dtd]::CancelDrag(); $dragActive = $false
            throw "Overlay window was VISIBLE on attempt $attempt but the ring was not detectable (paint produced nothing visible?)"
        }
        [Dtd]::CancelDrag()
        $dragActive = $false
        Start-Sleep -Milliseconds 350
        $shot.Dispose()
    }
    if (-not $t) {
        $why = 'the overlay window never became visible (drag never engaged)'
        if ($summary.OverlayVisibleAt) { $why = 'the overlay was visible but never detectable' }
        throw "No detectable overlay in $attempt drag attempts: $why"
    }
    $summary.Attempts = $attempt
    $summary.Target = $t
    $shotC.Save((Join-Path $OutDir '03-drag-rest.png'), [System.Drawing.Imaging.ImageFormat]::Png)

    # Hover the center for the money shot, then measure rim blending on the
    # clean rest frame.
    [Dtd]::SetCursorPos($t.cx, $t.cy) | Out-Null
    Start-Sleep -Milliseconds 650
    $shotD = Save-Shot '04-drag-hover.png'
    [Dtd]::SetCursorPos($cxAim, 620) | Out-Null
    Start-Sleep -Milliseconds 250

    $summary.Rim = Measure-Rim $shotC $t
    Write-Output ('stage: rim measured ' + (($summary.Rim.GetEnumerator() | Where-Object { $_.Key -ne 'worstOverall' } | ForEach-Object { "$($_.Key)=$($_.Value.maxDelta)" }) -join ' '))

    [Dtd]::CancelDrag()
    $dragActive = $false
    Start-Sleep -Milliseconds 400

    # Zoomed evidence crops: whole target and the bottom rim (old artifact zone).
    $pad = 44
    $cw = 2 * ($t.r + $pad); $ch = 2 * ($t.r + $pad)
    $cx0 = [Math]::Max(0, $t.cx - [int]($cw / 2)); $cy0 = [Math]::Max(0, $t.cy - [int]($ch / 2))
    $cw3 = $cw * 3; $ch3 = $ch * 3
    foreach ($pair in @(@($shotC, '05-target-rest-zoom-3x.png'), @($shotD, '06-target-hover-zoom-3x.png'))) {
        $crop = New-Object System.Drawing.Bitmap($cw3, $ch3)
        $dstRect = New-Object System.Drawing.Rectangle(0, 0, $cw3, $ch3)
        $srcRect = New-Object System.Drawing.Rectangle($cx0, $cy0, $cw, $ch)
        $g = [System.Drawing.Graphics]::FromImage($crop)
        $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
        $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
        $g.DrawImage($pair[0], $dstRect, $srcRect, [System.Drawing.GraphicsUnit]::Pixel)
        $g.Dispose()
        $crop.Save((Join-Path $OutDir $pair[1]), [System.Drawing.Imaging.ImageFormat]::Png)
        $crop.Dispose()
    }
    $bz = 180; $bz4 = $bz * 4; $bh4 = 120 * 4
    $bsx = $t.cx - [int]($bz / 2)
    $bcrop = New-Object System.Drawing.Bitmap($bz4, $bh4)
    $bdst = New-Object System.Drawing.Rectangle(0, 0, $bz4, $bh4)
    $bsrc = New-Object System.Drawing.Rectangle($bsx, $t.cy, $bz, 120)
    $g = [System.Drawing.Graphics]::FromImage($bcrop)
    $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
    $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
    $g.DrawImage($shotC, $bdst, $bsrc, [System.Drawing.GraphicsUnit]::Pixel)
    $g.Dispose()
    $bcrop.Save((Join-Path $OutDir '07-bottom-rim-zoom-4x.png'), [System.Drawing.Imaging.ImageFormat]::Png)
    $bcrop.Dispose()
}
catch {
    $errText = $_.Exception.Message + ' @ ' + $_.InvocationInfo.PositionMessage
    $summary.Error = $errText
}
finally {
    try { if ($dragActive) { [Dtd]::CancelDrag() } } catch {}
    try {
        if ($hwnd -and $hwnd -ne [IntPtr]::Zero) {
            if ($closeMine) {
                [Dtd]::PostMessageW($hwnd, 0x0010, [IntPtr]::Zero, [IntPtr]::Zero) | Out-Null
            }
            else {
                [Dtd]::SetWindowPos($hwnd, [IntPtr](-2), 0, 0, 0, 0, 0x0003) | Out-Null  # HWND_NOTOPMOST
                if ($wasMaximized) { [Dtd]::ShowWindow($hwnd, 3) | Out-Null }   # SW_MAXIMIZE
                else { [Dtd]::MoveWindow($hwnd, $oldRect[0], $oldRect[1], $oldRect[2], $oldRect[3], $true) | Out-Null }
            }
        }
    } catch {}
    try { if ($tmpDir -and (Test-Path $tmpDir)) { Start-Sleep -Milliseconds 500; Remove-Item $tmpDir -Recurse -Force -ErrorAction SilentlyContinue } } catch {}
    try {
        # Put the browser back on top so the user's stacking is undisturbed.
        if (-not $browser -or $browser -eq [IntPtr]::Zero) { $browser = [Dtd]::WindowWithClass('MozillaWindowClass', 800) }
        if ($browser -and $browser -ne [IntPtr]::Zero) { [Dtd]::SetWindowPos($browser, [IntPtr]::Zero, 0, 0, 0, 0, 0x0003) | Out-Null }
    } catch {}
    $summary.Restored = $true
    try { $summary | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $OutDir 'verify-summary.json') -Encoding UTF8 } catch {}
}
if ($errText) { throw $errText }
$summary | ConvertTo-Json -Depth 5
