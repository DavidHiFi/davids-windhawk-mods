# Installs local@window-manager 1.1.4 rev 1: Alt+right-drag resize now covers
# windows without a sizing border (Ditto quick-paste popup, Flow Launcher)
# via the new sizeWindowsWithoutSizingBorder setting (default on).
# Run -Install / -Rollback elevated. Pattern follows
# scripts\2026-10-04-window-manager.ps1: never restart the engine, reload the
# single mod by bumping SettingsChangeTime.
[CmdletBinding()]
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$root    = 'H:\Windhawk Configuration'
$build   = Join-Path $root 'Windhawk\window-pack'
$backup  = Join-Path $root 'backups\2026-10-09\window-manager-1.1.4'
$report  = Join-Path $root 'reports\2026-10-09-window-manager-1.1.4'
$wh      = 'C:\ProgramData\Windhawk'
$id      = 'local@window-manager'
$key     = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$oldDll  = 'local@window-manager_1.1.3_1.dll'
$newDll  = 'local@window-manager_1.1.4_1.dll'
$newVer  = '1.1.4'

function Now { [int][DateTimeOffset]::Now.ToUnixTimeSeconds() }

function Wait-ToolExit {
    for ($i = 0; $i -lt 40; $i++) {
        $p = Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" |
            Where-Object { $_.CommandLine -match 'window-manager' }
        if (-not $p) { return }
        Start-Sleep -Milliseconds 500
    }
    throw 'Old tool process did not exit within 20 s.'
}

function Get-State {
    $s = [ordered]@{}
    if (Test-Path $key) {
        $p = Get-ItemProperty $key
        $s.mod = [ordered]@{ Disabled = $p.Disabled; Version = $p.Version
            LibraryFileName = $p.LibraryFileName; Include = $p.Include
            SettingsChangeTime = $p.SettingsChangeTime }
        $st = Get-ItemProperty "$key\Settings" -ErrorAction SilentlyContinue
        $s.settings = [ordered]@{
            sizeTrigger = "$($st.'sizeTrigger.button')+$($st.'sizeTrigger.alt')"
            dragWindowsWithoutTitleBar = $st.dragWindowsWithoutTitleBar
            sizeWindowsWithoutSizingBorder = $st.sizeWindowsWithoutSizingBorder
            rightClickAction = $st.rightClickAction }
    } else { $s.mod = 'missing' }
    $s.files = @(foreach ($a in '64', '32') {
        $f = Join-Path $wh "Engine\Mods\$a\$newDll"
        if (Test-Path $f) { [ordered]@{ arch = $a; sha256 = (Get-FileHash $f).Hash } }
    })
    $src = Join-Path $wh "ModsSource\$id.wh.cpp"
    if (Test-Path $src) { $s.source = (Get-FileHash $src).Hash }
    $s
}

if ($Audit) { Get-State | ConvertTo-Json -Depth 5; return }

if ($Install) {
    New-Item -ItemType Directory -Force $backup, $report | Out-Null
    $regBackup = Join-Path $backup "$id-before-1.1.4.reg"
    & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" $regBackup /y | Out-Null
    if ($LASTEXITCODE) { throw 'reg export failed' }
    Copy-Item (Join-Path $wh "ModsSource\$id.wh.cpp") (Join-Path $backup "$id-before-1.1.4.wh.cpp") -Force
    Set-ItemProperty $key Disabled 1
    Set-ItemProperty $key SettingsChangeTime (Now)
    Wait-ToolExit
    foreach ($a in '64', '32') {
        $from = Join-Path $build ("local@window-manager_1.1.4_1_$a.dll")
        $to = Join-Path $wh "Engine\Mods\$a\$newDll"
        if (-not (Test-Path $from)) { throw "Build output missing: $from" }
        if (-not (Test-Path $to) -or (Get-FileHash $to).Hash -ne (Get-FileHash $from).Hash) {
            Copy-Item $from $to -Force
        }
    }
    Copy-Item (Join-Path $build 'window-manager.wh.cpp') (Join-Path $wh "ModsSource\$id.wh.cpp") -Force
    Set-ItemProperty $key LibraryFileName $newDll
    Set-ItemProperty $key Version $newVer
    New-ItemProperty "$key\Settings" -Name 'sizeWindowsWithoutSizingBorder' -Value 1 -PropertyType DWord -Force | Out-Null
    Set-ItemProperty $key Disabled 0
    Set-ItemProperty $key SettingsChangeTime (Now)
    Start-Sleep -Seconds 8
    $state = Get-State
    $state | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $report 'install-state.json') -Encoding UTF8
    $state | ConvertTo-Json -Depth 5
    return
}

if ($Rollback) {
    if (-not (Test-Path $key)) { throw 'mod key missing, cannot roll back' }
    Set-ItemProperty $key Disabled 1
    Set-ItemProperty $key SettingsChangeTime (Now)
    Wait-ToolExit
    Set-ItemProperty $key LibraryFileName $oldDll
    Set-ItemProperty $key Version '1.1.3'
    Remove-ItemProperty "$key\Settings" -Name 'sizeWindowsWithoutSizingBorder' -ErrorAction SilentlyContinue
    Set-ItemProperty $key Disabled 0
    Set-ItemProperty $key SettingsChangeTime (Now)
    Start-Sleep -Seconds 8
    Get-State | ConvertTo-Json -Depth 5
    return
}

'Use -Audit, -Install or -Rollback.'
