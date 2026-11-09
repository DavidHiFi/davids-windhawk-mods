# Seamless Flyouts (was Translucent Windows Plus) menu rows (1.9.2) and edge-to-edge separators (1.9.3, 1.9.4).
# menus (theme margins 6 -> 8, plus an owner-draw row boost for Explorer's own menus).
# Run elevated. Usage: -Install | -Rollback
param([switch]$Install, [switch]$Rollback, [string]$Staged, [switch]$NoBackup)
$ErrorActionPreference = 'Stop'
$id     = 'local@seamless-flyouts'
$live   = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$staged = if ($Staged) { $Staged } else { 'H:\Windhawk Configuration\work\2026-11-09-flyout-match\seamless-flyouts-2.0.0.wh.cpp' }
$bakDir = 'H:\Windhawk Configuration\backups\2026-11-09\flyout-match'
$cli    = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$log    = Join-Path $bakDir 'menu-rows-receipt.txt'
function Say($t) { "$(Get-Date -Format 'h:mm:ss tt') $t" | Tee-Object -FilePath $log -Append }
function Compile {
    $o = Join-Path $bakDir 'compile-menu-rows.out'; $e = "$o.err"
    $p = Start-Process $cli -ArgumentList @('mod', 'compile', $id, '--json') -WindowStyle Hidden -PassThru -Wait `
        -RedirectStandardOutput $o -RedirectStandardError $e
    Say "compile exit=$($p.ExitCode)"
    if ($p.ExitCode -ne 0) { Get-Content $o, $e | Select-Object -Last 15 | ForEach-Object { Say "  $_" }; throw 'compile failed' }
}
if ($Install) {
    $bak = Join-Path $bakDir "$id.wh.cpp.bak-$(Get-Date -Format yyyyMMdd-HHmm)-rows"
    if (-not $NoBackup) { Copy-Item $live $bak; Say "backup $bak" }
    Copy-Item $staged $live -Force; Say "installed $(Split-Path $staged -Leaf)"
    Compile
} elseif ($Rollback) {
    $bak = Get-ChildItem $bakDir -Filter "$id.wh.cpp.bak-*-rows" | Sort-Object Name | Select-Object -Last 1
    Copy-Item $bak.FullName $live -Force; Say "restored $($bak.Name)"
    Compile
} else { 'use -Install or -Rollback' }
