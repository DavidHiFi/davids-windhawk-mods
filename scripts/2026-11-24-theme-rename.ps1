<#
Rename the bundled theme Main 01 to DavidHiFi's Theme and give it the riced cursors (2026-11-24).
Source: work\theme-pack\out\stage-v2 (built by build_pack_v2.py, the same files as pack v2).
  -Install   back up, copy the v2 files into the pack folder, swap Main 01.theme for the new theme,
             point CurrentTheme, the cursor roles and the mod's theme setting at it, apply cursors live.
  -Rollback  put Main 01 and the old registry values back.
Run elevated (C:\Windows and HKLM).
#>
param([switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$ws     = 'H:\Windhawk Configuration'
$stage  = Join-Path $ws 'work\theme-pack\out\stage-v2'
$bk     = Join-Path $ws 'backups\2026-11-24-theme-rename'
$themes = 'C:\WINDOWS\Resources\Themes'
$pack   = Join-Path $themes 'Theme Tool Plus'
$name   = "DavidHiFi's Theme"
$curSet = 'Catppuccin-Mocha-Seamless-Cursors'
$curDir = Join-Path $pack "Cursors\$curSet"
$oldCur = "C:\WINDOWS\Cursors\$curSet"
$chrome = 'C:\WINDOWS\Cursors\Catppuccin-Mocha-Dark-Cursors\chromium'
$newChrome = Join-Path $ws 'tools\catppuccin-cur\out-mocha2\chromium'
$cKey   = 'HKCU:\Control Panel\Cursors'
$tKey   = 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Themes'
$mKey   = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@theme-tool-plus\Settings'

Add-Type -Namespace Rice -Name Cur2 -MemberDefinition '[DllImport("user32.dll", EntryPoint="SystemParametersInfoW")] public static extern bool SPI(uint a, uint b, System.IntPtr c, uint d);'

$roles = [ordered]@{
    Arrow = 'normal-select.cur'; Help = 'help-select.cur'; AppStarting = 'working-in-background.ani'
    Wait = 'busy.ani'; Crosshair = 'precision-select.cur'; IBeam = 'text-select.cur'
    NWPen = 'handwriting.cur'; No = 'unavailable.cur'; SizeNS = 'vertical-resize.cur'
    SizeWE = 'horizontal-resize.cur'; SizeNWSE = 'diagonal-resize-1.cur'; SizeNESW = 'diagonal-resize-2.cur'
    SizeAll = 'move.cur'; UpArrow = 'alt-select.cur'; Hand = 'link-select.cur'
}

if ($Install) {
    New-Item -ItemType Directory -Force $bk | Out-Null
    if (-not (Test-Path "$bk\themes-before.reg")) {
        reg export 'HKCU\Software\Microsoft\Windows\CurrentVersion\Themes' "$bk\themes-before.reg" /y | Out-Null
        reg export 'HKCU\Control Panel\Cursors' "$bk\cursors-before.reg" /y | Out-Null
        reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@theme-tool-plus\Settings' "$bk\mod-settings-before.reg" /y | Out-Null
        Copy-Item -LiteralPath "$themes\Main 01.theme" "$bk\Main 01.theme"
        Copy-Item -LiteralPath "$pack\pack.ini" "$bk\pack.ini"
        Copy-Item -LiteralPath $chrome "$bk\chromium-before" -Recurse
    }
    # pack folder: v2 files
    New-Item -ItemType Directory -Force $curDir | Out-Null
    Get-ChildItem -LiteralPath (Join-Path $stage "Cursors\$curSet") -File | Copy-Item -Destination $curDir -Force
    Copy-Item -LiteralPath (Join-Path $stage "themes\$name.theme") (Join-Path $pack "themes\$name.theme") -Force
    Copy-Item -LiteralPath (Join-Path $stage "Wallpapers\$name.jpg") (Join-Path $pack "Wallpapers\$name.jpg") -Force
    Copy-Item -LiteralPath (Join-Path $stage 'pack.ini') (Join-Path $pack 'pack.ini') -Force
    # the installed theme
    $newTheme = Join-Path $themes "$name.theme"
    Copy-Item -LiteralPath (Join-Path $stage "themes\$name.theme") $newTheme -Force
    Set-ItemProperty $tKey CurrentTheme $newTheme
    # cursors: the theme's own folder, applied live
    foreach ($r in $roles.Keys) { Set-ItemProperty $cKey $r (Join-Path $curDir $roles[$r]) }
    Set-ItemProperty $cKey '(default)' $curSet
    Set-ItemProperty $cKey 'Scheme Source' 1 -Type DWord
    $order = 'Arrow','Help','AppStarting','Wait','Crosshair','IBeam','NWPen','No','SizeNS','SizeWE','SizeNWSE','SizeNESW','SizeAll','UpArrow','Hand'
    Set-ItemProperty "$cKey\Schemes" $curSet (($order | ForEach-Object { Join-Path $curDir $roles[$_] }) -join ',') -Type ExpandString
    [void][Rice.Cur2]::SPI(0x57, 0, [IntPtr]::Zero, 3)
    # browser cursors (chromium-cursor-remap) in the same look
    Get-ChildItem -LiteralPath $newChrome -File | Copy-Item -Destination $chrome -Force
    # the mod's picked theme
    if ((Get-ItemProperty $mKey).themeName -eq 'Main 01') { Set-ItemProperty $mKey themeName $name }
    # old copies
    Remove-Item -LiteralPath "$themes\Main 01.theme", "$pack\themes\Main 01.theme", "$pack\Wallpapers\Main 01.jpg" -ErrorAction SilentlyContinue
    if (Test-Path -LiteralPath $oldCur) { Remove-Item -LiteralPath $oldCur -Recurse -Force }
    # read back
    $bad = @()
    if ((Get-ItemProperty $tKey).CurrentTheme -ne $newTheme) { $bad += 'CurrentTheme' }
    $bad += $roles.Keys | Where-Object { (Get-ItemProperty $cKey).$_ -ne (Join-Path $curDir $roles[$_]) -or -not (Test-Path -LiteralPath (Join-Path $curDir $roles[$_])) }
    if ((Get-ItemProperty $mKey).themeName -ne $name) { $bad += 'mod themeName' }
    if (Test-Path -LiteralPath "$themes\Main 01.theme") { $bad += 'old theme still there' }
    if ($bad) { throw "read-back failed: $($bad -join ', ')" }
    "installed: $name is current, 15 cursors from the theme folder, mod setting renamed"
}
elseif ($Rollback) {
    Copy-Item -LiteralPath "$bk\Main 01.theme" "$themes\Main 01.theme" -Force
    Copy-Item -LiteralPath "$bk\Main 01.theme" "$pack\themes\Main 01.theme" -Force
    Copy-Item -LiteralPath "$bk\pack.ini" "$pack\pack.ini" -Force
    Copy-Item -LiteralPath "$pack\Wallpapers\$name.jpg" "$pack\Wallpapers\Main 01.jpg" -Force
    reg import "$bk\themes-before.reg" 2>$null
    reg import "$bk\cursors-before.reg" 2>$null
    reg import "$bk\mod-settings-before.reg" 2>$null
    Get-ChildItem -LiteralPath "$bk\chromium-before" -File | Copy-Item -Destination $chrome -Force
    Remove-Item -LiteralPath (Join-Path $themes "$name.theme") -ErrorAction SilentlyContinue
    [void][Rice.Cur2]::SPI(0x57, 0, [IntPtr]::Zero, 3)
    'rolled back (cursors-before.reg points at C:\WINDOWS\Cursors\Catppuccin-Mocha-Seamless-Cursors: run 2026-11-24-cursor-rice.ps1 -Install first if that folder is gone)'
}
else { 'use -Install or -Rollback' }
