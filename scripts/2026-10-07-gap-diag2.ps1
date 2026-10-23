Add-Type -AssemblyName System.Drawing
$src = New-Object System.Drawing.Bitmap("H:\Windhawk Configuration\reports\2026-10-07-tray-gap\traybar-0.png", $false)
# crop x 2380..2560, zoom 6x
$cx=2380; $cw=180
$crop = New-Object System.Drawing.Bitmap $cw,50
$g=[System.Drawing.Graphics]::FromImage($crop)
$g.DrawImage($src,(New-Object System.Drawing.Rectangle 0,0,$cw,50),(New-Object System.Drawing.Rectangle $cx,0,$cw,50),[System.Drawing.GraphicsUnit]::Pixel)
$g.Dispose()
$big=New-Object System.Drawing.Bitmap ($cw*6),300
$g2=[System.Drawing.Graphics]::FromImage($big)
$g2.InterpolationMode='NearestNeighbor'
$g2.DrawImage($crop,0,0,($cw*6),300)
$g2.Dispose()
$big.Save("H:\Windhawk Configuration\reports\2026-10-07-tray-gap\gap-zoom.png")
# rows profile for the 2420-2435 block: which rows have content
$br=28;$bgg=28;$bb=40
foreach($y in 0..49){
  $line=""
  foreach($x in 2415..2440){
    $c=$src.GetPixel($x,$y)
    if($c.A -lt 200){$line+=" ";continue}
    $d=[Math]::Abs($c.R-$br)+[Math]::Abs($c.G-$bgg)+[Math]::Abs($c.B-$bb)
    if($d -gt 200){$line+="#"} elseif($d -gt 60){$line+="+"} elseif($d -gt 40){$line+="."} else {$line+=" "}
  }
  "{0:d2} {1}" -f $y,$line
}
