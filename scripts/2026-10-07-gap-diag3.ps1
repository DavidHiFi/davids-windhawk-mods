Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap("H:\Windhawk Configuration\reports\2026-10-07-tray-gap\traybar-0.png", $false)
$br=28; $bgg=28; $bb=40
$runs=@(); $cur=$null; $start=2400
foreach($x in 2400..2559){
  $maxd=0
  for($y=4;$y -lt 46;$y++){
    $c=$bmp.GetPixel($x,$y)
    if($c.A -lt 200){continue}
    $d=[Math]::Abs($c.R-$br)+[Math]::Abs($c.G-$bgg)+[Math]::Abs($c.B-$bb)
    if($d -gt $maxd){$maxd=$d}
  }
  $content = $maxd -gt 100   # ignore faint border AA; glyphs/text are bright
  if($x -eq 2400){$cur=$content;$start=$x;continue}
  if($content -ne $cur){
    $runs+=[pscustomobject]@{Type=if($cur){'CONTENT'}else{'GAP'};From=$start;To=$x-1;W=$x-$start}
    $cur=$content;$start=$x
  }
}
$runs+=[pscustomobject]@{Type=if($cur){'CONTENT'}else{'GAP'};From=$start;To=2559;W=2560-$start}
$runs | ForEach-Object { "{0} x={1}..{2} w={3}" -f $_.Type,$_.From,$_.To,$_.W }
