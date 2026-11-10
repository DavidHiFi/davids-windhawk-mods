<#
Simple Window Switcher Plus 1.0.3 -> 1.0.4: Mocha gradient borders on every Vista card,
solid Mocha base title pill with a blue-to-mauve border that lights up on hover.
Run elevated (Invoke-Elevated.ps1 -File <this> -ArgumentList "-Install").
  -Install   copies the work source in, writes the new look settings, compiles with windhawk-cli
  -Rollback  restores the 1.0.3 source and settings from backups\2026-11-10\swsp, recompiles
Backups were taken first: backups\2026-11-10\swsp\*.bak-20261110-2143.
#>
param([switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$id   = 'local@simple-window-switcher-plus'
$src  = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$key  = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$bak  = 'H:\Windhawk Configuration\backups\2026-11-10\swsp'
$work = 'H:\Windhawk Configuration\work\2026-11-10-swsp\swsp.wh.cpp'
$cli  = 'C:\Program Files\Windhawk\windhawk-cli.exe'

function Compile {
    $psi = New-Object System.Diagnostics.ProcessStartInfo $cli, "mod compile $id"
    $psi.UseShellExecute = $false; $psi.CreateNoWindow = $true
    $psi.RedirectStandardOutput = $true; $psi.RedirectStandardError = $true
    $p = [System.Diagnostics.Process]::Start($psi)
    try { $p.PriorityClass = 'Idle' } catch {}
    $errTask = $p.StandardError.ReadToEndAsync()
    $out = $p.StandardOutput.ReadToEnd(); $p.WaitForExit()
    "compile exit $($p.ExitCode)"; ($out + $errTask.Result) -split "`n" | Select-Object -Last 15
    if ($p.ExitCode -ne 0) { throw 'compile failed' }
}

if ($Install) {
    Copy-Item -LiteralPath $work $src -Force
    $s = "$key\Settings"
    $look = [ordered]@{
        'CardBorder.enabled' = 1; 'CardBorder.startColor' = '#89B4FA'; 'CardBorder.endColor' = '#CBA6F7'
        'CardBorder.width' = 2; 'CardBorder.restingOpacity' = 40
        'TitlePill.tintColor' = '#1E1E2E'; 'TitlePill.tintOpacity' = 100
        'TitlePill.textColor' = '#CDD6F4'; 'TitlePill.borderColor' = '#89B4FA'
        'TitlePill.borderColorEnd' = '#CBA6F7'; 'TitlePill.borderOpacity' = 45
        'TitlePill.hoverBorderOpacity' = 100; 'TitlePill.borderWidth' = 2
    }
    foreach ($n in $look.Keys) {
        $v = $look[$n]; $t = if ($v -is [string]) { 'String' } else { 'DWord' }
        New-ItemProperty -Path $s -Name $n -Value $v -PropertyType $t -Force | Out-Null
    }
    Compile
}
if ($Rollback) {
    $old = Get-ChildItem $bak -Filter "$id.wh.cpp.bak-*" | Sort-Object Name | Select-Object -First 1
    $reg = Get-ChildItem $bak -Filter 'settings.bak-*.reg' | Sort-Object Name | Select-Object -First 1
    Copy-Item -LiteralPath $old.FullName $src -Force
    Remove-Item -LiteralPath "$key\Settings" -Recurse -Force
    & reg.exe import $reg.FullName 2>&1 | Out-Null
    Compile
}
$p = Get-ItemProperty $key
"Version $($p.Version)  Library $($p.LibraryFileName)  Disabled $($p.Disabled)"
