# Migrates local@david-window-pack 1.0.0 to local@window-manager 1.1.0
# (monitor-move fix for maximized windows). Run -Install / -Rollback elevated.
[CmdletBinding()]
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$root    = 'H:\Windhawk Configuration'
$build   = Join-Path $root 'Windhawk\window-pack'
$backup  = Join-Path $root 'backups\2026-10-04\window-manager'
$report  = Join-Path $root 'reports\2026-10-04-window-manager'
$wh      = 'C:\ProgramData\Windhawk'
$oldId   = 'local@david-window-pack'
$newId   = 'local@window-manager'
$oldKey  = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$oldId"
$newKey  = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$newId"
$newDll  = 'local@window-manager_1.1.0_2.dll'

function Now { [int][DateTimeOffset]::Now.ToUnixTimeSeconds() }

# A new tool process cannot register its hotkeys while the previous one still
# holds them, so wait until every window-pack/window-manager tool process exits.
function Wait-ToolExit {
    for ($i = 0; $i -lt 40; $i++) {
        $p = Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" |
            Where-Object { $_.CommandLine -match 'window-pack|window-manager' }
        if (-not $p) { return }
        Start-Sleep -Milliseconds 500
    }
    throw 'Old tool process did not exit within 20 s.'
}

function Get-State {
    $s = [ordered]@{}
    foreach ($k in @($oldKey, $newKey)) {
        if (Test-Path $k) {
            $p = Get-ItemProperty $k
            $s[$k] = [ordered]@{ Disabled = $p.Disabled; Version = $p.Version
                LibraryFileName = $p.LibraryFileName; SettingsChangeTime = $p.SettingsChangeTime
                SettingsValues = @((Get-Item "$k\Settings" -ErrorAction SilentlyContinue).Property).Count }
        } else { $s[$k] = 'missing' }
    }
    $s.files = @(foreach ($a in '64', '32') {
        $f = Join-Path $wh "Engine\Mods\$a\$newDll"
        if (Test-Path $f) { [ordered]@{ path = $f; sha256 = (Get-FileHash $f).Hash } } })
    $src = Join-Path $wh "ModsSource\$newId.wh.cpp"
    if (Test-Path $src) { $s.source = [ordered]@{ path = $src; sha256 = (Get-FileHash $src).Hash } }
    $s.toolProcesses = @(Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" |
        Where-Object { $_.CommandLine -match 'window-pack|window-manager' } |
        ForEach-Object { "$($_.ProcessId) $($_.CommandLine)" })
    $s
}

if ($Audit) { Get-State | ConvertTo-Json -Depth 5; return }

if ($Install) {
    New-Item -ItemType Directory -Force $backup, $report | Out-Null
    $regBackup = Join-Path $backup "$oldId.reg"
    if (-not (Test-Path $regBackup)) {
        & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$oldId" $regBackup /y | Out-Null
        if ($LASTEXITCODE) { throw 'reg export failed' }
        Copy-Item (Join-Path $wh "ModsSource\$oldId.wh.cpp") $backup
        foreach ($a in '64', '32') {
            New-Item -ItemType Directory -Force (Join-Path $backup $a) | Out-Null
            Copy-Item (Join-Path $wh "Engine\Mods\$a\$oldId*.dll") (Join-Path $backup $a)
        }
    }
    if (Test-Path $newKey) {
        & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$newId" (Join-Path $backup "$newId-before.reg") /y | Out-Null
    }
    # Old and new must never run together: disable the old one first.
    Set-ItemProperty $oldKey Disabled 1
    Set-ItemProperty $oldKey SettingsChangeTime (Now)
    # Reinstall over an existing new key: unload the current revision first.
    if (Test-Path $newKey) {
        Set-ItemProperty $newKey Disabled 1
        Set-ItemProperty $newKey SettingsChangeTime (Now)
    }
    Wait-ToolExit
    foreach ($a in '64', '32') {
        # Loaded DLLs stay mapped and cannot be overwritten; skip identical files.
        $from = Join-Path $build "local@window-manager_1.1.0_2_$a.dll"
        $to = Join-Path $wh "Engine\Mods\$a\$newDll"
        if (-not (Test-Path $to) -or (Get-FileHash $to).Hash -ne (Get-FileHash $from).Hash) {
            Copy-Item $from $to -Force
        }
    }
    Copy-Item (Join-Path $build 'window-manager.wh.cpp') (Join-Path $wh "ModsSource\$newId.wh.cpp") -Force
    if (-not (Test-Path $newKey)) {
        & reg.exe copy "HKLM\SOFTWARE\Windhawk\Engine\Mods\$oldId" "HKLM\SOFTWARE\Windhawk\Engine\Mods\$newId" /s /f | Out-Null
        if ($LASTEXITCODE) { throw 'reg copy failed' }
        Set-ItemProperty $newKey Disabled 1
    }
    Set-ItemProperty $newKey LibraryFileName $newDll
    Set-ItemProperty $newKey Version '1.1.0'
    Set-ItemProperty $newKey SettingsChangeTime (Now)
    Set-ItemProperty $newKey Disabled 0
    Start-Sleep -Seconds 6
    $state = Get-State
    $state | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $report 'install-state.json') -Encoding UTF8
    $state | ConvertTo-Json -Depth 5
    return
}

if ($Rollback) {
    if (Test-Path $newKey) {
        Set-ItemProperty $newKey Disabled 1
        Set-ItemProperty $newKey SettingsChangeTime (Now)
    }
    Wait-ToolExit
    Set-ItemProperty $oldKey Disabled 0
    Set-ItemProperty $oldKey SettingsChangeTime (Now)
    Start-Sleep -Seconds 6
    Get-State | ConvertTo-Json -Depth 5
    return
}
'Use -Audit, -Install or -Rollback.'
