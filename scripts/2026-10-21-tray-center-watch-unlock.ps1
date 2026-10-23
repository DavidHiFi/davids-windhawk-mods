Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
public class DT {
    [DllImport("user32.dll")] public static extern IntPtr OpenInputDesktop(uint flags, bool inherit, uint access);
    [DllImport("user32.dll")] public static extern bool CloseDesktop(IntPtr h);
}
'@
Add-Type -AssemblyName System.Drawing
$dir = "C:\Users\localuser\AppData\Local\Temp\dsh-XBo3bx\tbfix"
New-Item -ItemType Directory -Force -Path $dir | Out-Null
"watch-unlock started $(Get-Date -Format 'M/d/yyyy h:mm:ss tt')" | Out-File "$dir\watch-unlock-log.txt" -Encoding utf8
$unlocked = $false
for ($i = 0; $i -lt 720; $i++) {
    $h = [DT]::OpenInputDesktop(0, $false, 0x0200)
    if ($h -ne [IntPtr]::Zero) { [DT]::CloseDesktop($h) | Out-Null; $unlocked = $true; "input desktop accessible at $(Get-Date -Format 'h:mm:ss tt') (iter $i)" | Out-File "$dir\watch-unlock-log.txt" -Append -Encoding utf8; break }
    Start-Sleep -Seconds 10
}
if (-not $unlocked) { "TIMEOUT: still locked after 2 hours" | Out-File "$dir\watch-unlock-log.txt" -Append -Encoding utf8; "RESULT: TIMEOUT" | Out-File "$dir\unlock-result.txt" -Encoding utf8; exit 0 }
Start-Sleep -Seconds 4
$bmp = New-Object System.Drawing.Bitmap -ArgumentList 2560, 64
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(2560, 64)))
$g.Dispose()
$bmp.Save("$dir\unlocked.png", [System.Drawing.Imaging.ImageFormat]::Png)
$counts = @()
for ($y = 0; $y -lt 64; $y++) {
    $ink = 0
    for ($x = 1990; $x -lt 2530; $x += 2) {
        $c = $bmp.GetPixel($x, $y)
        if ([Math]::Max($c.R, [Math]::Max($c.G, $c.B)) -gt 90) { $ink++ }
    }
    $counts += $ink
}
$rings = @(); for ($y = 0; $y -lt 64; $y++) { if ($counts[$y] -ge 200) { $rings += $y } }
$ringTop = ($rings | Where-Object { $_ -lt 32 } | Select-Object -Last 1)
$ringBot = ($rings | Where-Object { $_ -ge 32 } | Select-Object -First 1)
if ($null -eq $ringTop -or $null -eq $ringBot) {
    "RESULT: CAPTURED-BUT-NO-RING rings=$($rings -join ',')" | Out-File "$dir\unlock-result.txt" -Encoding utf8
} else {
    $pillCenter = ($ringTop + $ringBot) / 2.0
    $inkRows = @(); for ($y = $ringTop + 2; $y -lt $ringBot - 1; $y++) { if ($counts[$y] -gt 2) { $inkRows += $y } }
    $cTop = $inkRows[0]; $cBot = $inkRows[-1]; $cCenter = ($cTop + $cBot) / 2.0
    $d = [Math]::Round($cCenter - $pillCenter, 1)
    $verdict = if ([Math]::Abs($d) -le 1.5) { "CENTERED (delta $d)" } elseif ($d -gt 0) { "TOO LOW by $d" } else { "TOO HIGH by $([Math]::Abs($d))" }
    "RESULT: $verdict | pill $($ringTop)..$($ringBot) center $([Math]::Round($pillCenter,1)) | content $cTop..$cBot center $([Math]::Round($cCenter,1))" | Out-File "$dir\unlock-result.txt" -Encoding utf8
}
$w = 2560; $h = 256
$bmp2 = New-Object System.Drawing.Bitmap -ArgumentList $w, $h
$g2 = [System.Drawing.Graphics]::FromImage($bmp2)
$g2.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g2.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
$dst = New-Object System.Drawing.Rectangle 0, 0, $w, $h
$srcRect = New-Object System.Drawing.Rectangle 0, 0, 2560, 64
$g2.DrawImage($bmp, $dst, $srcRect, [System.Drawing.GraphicsUnit]::Pixel)
$g2.Dispose()
$bmp2.Save("$dir\unlocked-4x.png", [System.Drawing.Imaging.ImageFormat]::Png)
$bmp2.Dispose()
$bmp.Dispose()
"done $(Get-Date -Format 'h:mm:ss tt')" | Out-File "$dir\watch-unlock-log.txt" -Append -Encoding utf8
