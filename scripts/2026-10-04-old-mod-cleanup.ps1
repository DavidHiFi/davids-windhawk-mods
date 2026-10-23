<#
Removes the three renamed mods' old entries from Windhawk so its installed list
only shows the new names. Each old mod was already disabled and replaced:

  local@david-window-pack               -> local@window-manager
  local@davids-audio-visualizer         -> local@taskbar-audio-visualizer
  local@explorer-font-changer-davidhifi -> local@shell-font-changer

  -Audit     list what exists for the old ids
  -Remove    export everything to backups, then delete the old registry keys,
             the old ModsSource files and the old mod-storage folders
  -Rollback  re-import the exported keys and restore the files (disabled, as
             they were)
Run elevated. Old DLLs in Engine\Mods stay on disk; they are not listed by the UI.
#>
param([switch]$Audit, [switch]$Remove, [switch]$Rollback)
$ErrorActionPreference = 'Stop'

$ids     = 'local@david-window-pack', 'local@davids-audio-visualizer', 'local@explorer-font-changer-davidhifi'
$backup  = 'H:\Windhawk Configuration\backups\2026-10-04\old-mod-cleanup'
$report  = 'H:\Windhawk Configuration\reports\2026-10-04-old-mod-cleanup'
$data    = 'C:\ProgramData\Windhawk'
New-Item $backup, $report -ItemType Directory -Force | Out-Null

$rows = foreach ($id in $ids) {
    $keys = @{
        Mods         = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id"
        ModsWritable = "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\$id"
    }
    $source  = "$data\ModsSource\$id.wh.cpp"
    $storage = "$data\Engine\ModsWritable\mod-storage\$id"
    $b = Join-Path $backup $id
    New-Item $b -ItemType Directory -Force | Out-Null

    if ($Remove) {
        if ((Get-ItemProperty "Registry::$($keys.Mods)" -ErrorAction SilentlyContinue).Disabled -ne 1) {
            throw "$id is not disabled; refusing to remove it"
        }
        foreach ($k in $keys.Keys) {
            if (Test-Path "Registry::$($keys[$k])") {
                reg export $keys[$k] "$b\$k.reg" /y | Out-Null
                if (-not (Test-Path "$b\$k.reg")) { throw "export failed: $($keys[$k])" }
                Remove-Item "Registry::$($keys[$k])" -Recurse
            }
        }
        if (Test-Path $source)  { Copy-Item $source $b -Force; Remove-Item $source }
        if (Test-Path $storage) { Copy-Item $storage "$b\mod-storage" -Recurse -Force; Remove-Item $storage -Recurse }
    } elseif ($Rollback) {
        foreach ($k in $keys.Keys) { if (Test-Path "$b\$k.reg") { reg import "$b\$k.reg" 2>&1 | Out-Null } }
        if (Test-Path "$b\$id.wh.cpp")   { Copy-Item "$b\$id.wh.cpp" $source -Force }
        if (Test-Path "$b\mod-storage")  { Copy-Item "$b\mod-storage" $storage -Recurse -Force }
    }

    [pscustomobject]@{
        id           = $id
        modsKey      = Test-Path "Registry::$($keys.Mods)"
        writableKey  = Test-Path "Registry::$($keys.ModsWritable)"
        source       = Test-Path $source
        storage      = Test-Path $storage
        backupFiles  = (Get-ChildItem $b -Recurse -File | Measure-Object).Count
    }
}
$rows | Format-Table -AutoSize | Out-String -Width 200
$mode = if ($Remove) { 'remove' } elseif ($Rollback) { 'rollback' } else { 'audit' }
$rows | ConvertTo-Json | Set-Content "$report\receipt-$mode.json" -Encoding UTF8
