param([string]$Src)
$content = Get-Content $Src -Raw
$blob = 'MOD_CONTROL | MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, VK_F12|MOD_CONTROL | MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, VK_F12|MOD_CONTROL | MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, VK_F12'
$fix = 'MOD_CONTROL | MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, VK_F12'
$before = ([regex]::Matches($content, $blob)).Count
$content = $content.Replace($blob, $fix)
Set-Content $Src -Value $content -Encoding UTF8 -Force
Write-Output "fixed-blobs=$before"
$after = ([regex]::Matches($content, 'MOD_CONTROL \| MOD_ALT \| MOD_SHIFT \| MOD_NOREPEAT, VK_F12')).Count
Write-Output "VK_F12-calls=$after"
$bad = ([regex]::Matches($content, 'VK_F12\|')).Count
Write-Output "concat-leftovers=$bad"