# Freeze #6 timeline evidence image, 2026-10-22. Offline GDI render. Pure ASCII.
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$lines = @(
    '10:07 AM   WER: simple-window-switcher unloaded-DLL crash of explorer.exe',
    '10:52 AM   WER: taskbar-audio-visualizer crashes explorer.exe (access violation)',
    ' 1:08 PM   Other thread arms retest: engine ON all mods (21 procs)',
    ' 2:08 PM   WER: audio-visualizer crashes explorer again, seconds before storm',
    ' 2:08-2:11 Storm test: engine refresh + 4 waves x 12 windows, then dead',
    ' 2:11 PM   FREEZE #5 hard reset #1 (unclean, event 6008), during the storm',
    ' 2:29 PM   Logging applied to all mod keys (me), engine down, verified 130/130',
    ' 2:30 PM   [WH] listener live; 2:33 proven with injected test line',
    ' 2:55 PM   Other thread rearms: engine booted again, logging now active',
    ' 3:00 PM   FREEZE #6 AT IDLE (unclean), capture ran to 3:00:27 then silence',
    ' 3:01 PM   Owner hard reset #2, boot 3:00:53, engine OFF + Manual (safe now)'
)
$lines2 = @(
    'Freeze-time mod inventory (sampler scan 3:00:14 PM):',
    '  explorer.exe   56 mod DLLs (copy-queue, ai-quota-plus, shortcut-actions,',
    '                 theme-tool-plus, window-manager, taskbar-styler and more)',
    '  dwm.exe         2 (caption-buttons-customizer, custom-corner-radius)',
    '  winlogon.exe    1 (theme-tool-plus)',
    'Recording: 340,094 lines covering 2:55:11-3:00:27; init peak 5,672 lines/s;',
    'the death minute had 3 lines: logging was quiet at death, not the cause.',
    'WER + repeat offenders: taskbar-audio-visualizer crashed explorer 3x today',
    '(now disabled); simple-window-switcher-plus STILL enabled;',
    'fix-basic-caption-text throws engine exceptions every ~5 s per process.'
)
$w = 1200
$h = 90 + 34 * $lines.Count + 60 + 30 * $lines2.Count
$bmp = New-Object System.Drawing.Bitmap($w, $h)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::AntiAlias
$bg = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(22, 25, 32))
$g.FillRectangle($bg, 0, 0, $w, $h)
$tf = New-Object System.Drawing.Font('Segoe UI', 16, [System.Drawing.FontStyle]::Bold)
$ff = New-Object System.Drawing.Font('Consolas', 11.5)
$tw = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(238, 238, 244))
$ac = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(150, 215, 160))
$bd = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(205, 208, 216))
$orange = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(235, 180, 110))
$g.DrawString('The two freezes the capture caught - measured timeline, Oct 22', $tf, $tw, 24, 18)
$y = 76
foreach ($l in $lines) {
    $b = if ($l -match 'FREEZE') { $orange } elseif ($l -match 'Logging|\[WH\]') { $ac } else { $bd }
    $g.DrawString($l, $ff, $b, 30, $y)
    $y += 34
}
$y += 42
foreach ($l in $lines2) {
    $g.DrawString($l, $ff, $bd, 30, $y)
    $y += 30
}
$g.Dispose()
$out = 'H:\Windhawk Configuration\reports\2026-10-22-freeze6-timeline.png'
$bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"saved $out $((Get-Item $out).Length) bytes"
