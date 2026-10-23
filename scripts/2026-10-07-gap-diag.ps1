Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap("H:\Windhawk Configuration\reports\2026-10-07-tray-gap\traybar-0.png", $false)
$br=28; $bgg=28; $bb=40
foreach($x in 2400..2559){
  $maxd=0; $my=-1
  for($y=3;$y -lt 47;$y++){
    $c=$bmp.GetPixel($x,$y)
    if($c.A -lt 200){continue}
    $d=[Math]::Abs($c.R-$br)+[Math]::Abs($c.G-$bgg)+[Math]::Abs($c.B-$bb)
    if($d -gt $maxd){$maxd=$d;$my=$y}
  }
  "{0} maxd={1} row={2}" -f $x,$maxd,$my
}
