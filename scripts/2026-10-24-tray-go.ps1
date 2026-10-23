# Prepared 2026-10-24 for the owner's "go". Two modes:
#   -Measure          read-only: capture the top strip, report left and right cluster offset from the pill center
#   -Apply -Delta N   guarded write: shift rule 63 (tray cluster) by -N px (N = measured right offset, + = too low)
# Run -Apply elevated (scripts\Invoke-Elevated.ps1). Law (measured 2026-10-21): cluster center = pill center + (top - bottom margin)/2.
param([switch]$Measure, [switch]$Apply, [double]$Delta = 0,
      [string]$Out = "H:\Windhawk Configuration\reports\2026-10-24-tray-go")
$ErrorActionPreference = "Stop"
New-Item -ItemType Directory -Force $Out | Out-Null
$ks = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler"
$name = 'controlStyles[63].styles[1]'

if ($Measure) {
    Add-Type -AssemblyName System.Drawing
    $bmp = New-Object System.Drawing.Bitmap 2560, 64
    $g = [System.Drawing.Graphics]::FromImage($bmp); $g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size 2560, 64)); $g.Dispose()
    $bmp.Save("$Out\strip-$(Get-Date -Format HHmmss).png", [System.Drawing.Imaging.ImageFormat]::Png)
    function Rows($x0, $x1) { $r = @(); for ($y = 0; $y -lt 64; $y++) { $n = 0; for ($x = $x0; $x -lt $x1; $x += 2) { $c = $bmp.GetPixel($x, $y); if ([Math]::Max($c.R, [Math]::Max($c.G, $c.B)) -gt 90) { $n++ } }; $r += $n }; $r }
    $right = Rows 1990 2530; $left = Rows 30 700
    $rings = @(0..63 | Where-Object { $right[$_] -ge 200 })
    $top = $rings | Where-Object { $_ -lt 32 } | Select-Object -Last 1; $bot = $rings | Where-Object { $_ -ge 32 } | Select-Object -First 1
    if ($null -eq $top -or $null -eq $bot) { "RING NOT FOUND (styler off or bar not at top): $($rings -join ' ')"; exit 1 }
    $pill = ($top + $bot) / 2.0; "pill rows $top..$bot center $pill"
    foreach ($side in @(@{n='left'; r=$left}, @{n='right'; r=$right})) {
        $ink = @(($top + 2)..($bot - 2) | Where-Object { $side.r[$_] -gt 2 })
        if (-not $ink) { "$($side.n): no ink"; continue }
        $d = [Math]::Round(($ink[0] + $ink[-1]) / 2.0 - $pill, 1)
        "$($side.n): rows $($ink[0])..$($ink[-1]) offset $d px ($(if ([Math]::Abs($d) -le 1.5) {'CENTERED'} elseif ($d -gt 0) {'TOO LOW'} else {'TOO HIGH'}))"
    }
    $bmp.Dispose(); exit 0
}

if ($Apply) {
    $log = "$Out\apply-$(Get-Date -Format HHmmss).txt"
    reg export "HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler" "$Out\styler-before.reg" /y | Out-Null
    $cur = (Get-ItemProperty "$ks\Settings").$name
    if ($cur -notmatch '^Margin=0,(-?\d+),0,(-?\d+)$') { "ABORT: unexpected $name = $cur" | Tee-Object $log; exit 1 }
    $net = [int]$Matches[1] - [int]$Matches[2] - [int][Math]::Round(2 * $Delta)
    $new = "Margin=0,$([Math]::Max($net,0)),0,$([Math]::Max(-$net,0))"
    Set-ItemProperty "$ks\Settings" $name $new -Type String
    $now = [DateTimeOffset]::Now.ToUnixTimeSeconds(); Set-ItemProperty $ks SettingsChangeTime $now -Type DWord
    $rb = (Get-ItemProperty "$ks\Settings").$name; $sct = (Get-ItemProperty $ks).SettingsChangeTime
    "was $cur -> wrote $new; readback $rb; SCT $sct; $(if ($rb -eq $new -and $sct -eq $now) {'VERDICT: APPLIED'} else {'VERDICT: FAILED'})" | Tee-Object $log
    "rollback: reg import `"$Out\styler-before.reg`"" | Tee-Object $log -Append
}
