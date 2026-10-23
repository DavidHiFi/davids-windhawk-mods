<#
Applies the 2026-10-04 name, description and readme polish to installed local
mods whose ids stay the same. Only the metadata and readme blocks change; the
code is identical, so no rebuild or engine restart is needed.

  -Audit     show which installed sources differ from the polished ones
  -Install   back up the installed sources, then copy the polished ones in
  -Rollback  restore the backed-up sources
Run elevated (ModsSource is admin-only). Writes a log next to the receipt.
#>
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'

$root    = 'H:\Windhawk Configuration'
$staged  = "$root\work\mod-polish-20261004\src"
$backup  = "$root\backups\2026-10-04\mod-metadata-polish"
$report  = "$root\reports\2026-10-04-mod-metadata-polish"
$modsSrc = 'C:\ProgramData\Windhawk\ModsSource'

# installed file name -> polished staged file
$map = [ordered]@{
    'local@alt-snap-drag.wh.cpp'               = 'alt-snap-drag.wh.cpp'
    'local@better-volume-mixer-plus.wh.cpp'    = 'better-volume-mixer-plus.wh.cpp'
    'local@taskbar-ai-quota-opencode.wh.cpp'   = 'taskbar-ai-quota-opencode.wh.cpp'
    'local@taskbar-weather.wh.cpp'             = 'taskbar-weather.wh.cpp'
    'local@translucent-flyouts.wh.cpp'         = 'translucent-flyouts.wh.cpp'
    'local@taskbar-system-info-weather.wh.cpp' = 'taskbar-system-info-weather.wh.cpp'
    'npp-taskdlg-textcolor.wh.cpp'             = 'npp-taskdlg-textcolor.new.wh.cpp'
}

New-Item $report -ItemType Directory -Force | Out-Null
$rows = foreach ($k in $map.Keys) {
    $live = Join-Path $modsSrc $k
    $new  = Join-Path $staged $map[$k]
    $bak  = Join-Path $backup $k
    if ($Install) {
        New-Item $backup -ItemType Directory -Force | Out-Null
        if (-not (Test-Path $bak)) { Copy-Item $live $bak }
        Copy-Item $new $live -Force
    } elseif ($Rollback) {
        Copy-Item $bak $live -Force
    }
    [pscustomobject]@{
        file       = $k
        liveSha256 = (Get-FileHash $live).Hash
        newSha256  = (Get-FileHash $new).Hash
        backupSha256 = if (Test-Path $bak) { (Get-FileHash $bak).Hash } else { $null }
        applied    = (Get-FileHash $live).Hash -eq (Get-FileHash $new).Hash
    }
}
$rows | Format-Table -AutoSize | Out-String -Width 220
$mode = if ($Install) { 'install' } elseif ($Rollback) { 'rollback' } else { 'audit' }
$rows | ConvertTo-Json | Set-Content "$report\receipt-$mode.json" -Encoding UTF8
