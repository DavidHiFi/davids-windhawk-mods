param([string]$Src)
$content = Get-Content $Src -Raw
$content = $content -replace 'MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F11','MOD_CONTROL | MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, VK_F12'
$content = $content -replace 'Ctrl\+Alt\+F11','Ctrl+Alt+Shift+F12'
$content = $content -replace 'Panic hotkey triggered \(Ctrl\+Alt\+F11\)','Panic hotkey triggered (Ctrl+Alt+Shift+F12)'
Set-Content $Src -Value $content -Encoding UTF8 -Force
Write-Output "edited; VK_F12 count=$( ($content -split 'VK_F12').Length - 1 )"
