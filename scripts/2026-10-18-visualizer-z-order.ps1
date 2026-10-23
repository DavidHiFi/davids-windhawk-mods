<#
.SYNOPSIS
Audit, install or roll back taskbar-audio-visualizer revision 1.3.2_2, where the strip is a child of the taskbar.

.DESCRIPTION
-Audit    prints the mod key, the two revision DLLs, the source hashes and the
          string probes. It changes nothing and needs no elevation.
-Install  backs up the mod key, copies the source into ModsSource, copies the
          built 64-bit and 32-bit DLLs into Engine\Mods as revision 1.3.2_2, then
          moves LibraryFileName with the disable, wait, relabel, bump order.
          Needs elevation: run it through Invoke-Elevated.ps1.
-Rollback points the mod back at revision 1.3.2_1 with the same order.

The engine keeps a loaded DLL mapped, so the new build gets a new file name
and the old file is left in place for rollback.

.PARAMETER Audit
See above.

.PARAMETER Install
See above.

.PARAMETER Rollback
See above.
#>
[CmdletBinding(DefaultParameterSetName = 'Audit')]
param(
    [Parameter(Mandatory, ParameterSetName = 'Audit')][switch]$Audit,
    [Parameter(Mandatory, ParameterSetName = 'Install')][switch]$Install,
    [Parameter(Mandatory, ParameterSetName = 'Rollback')][switch]$Rollback
)
$ErrorActionPreference = 'Stop'
$id = 'local@taskbar-audio-visualizer'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$data = 'C:\ProgramData\Windhawk'
$wk = 'H:\Windhawk Configuration\backups\2026-10-18-visualizer-z-order'
$srcWork = 'H:\Windhawk Configuration\work\taskbar-audio-visualizer-z-order\taskbar-audio-visualizer.wh.cpp'
$rev1 = "${id}_1.3.2_1.dll"
$rev2 = "${id}_1.3.2_3.dll"

function Get-Probe([string]$path) {
    $u16 = [System.Text.Encoding]::Unicode.GetString([System.IO.File]::ReadAllBytes($path))
    [ordered]@{
        overlayClass = $u16.Contains('DesktopAudioVisOverlay_')
        followLog    = $u16.Contains('[Follow] taskbar auto-hide mode')
    }
}

function Wait-ToolExit {
    $deadline = [DateTime]::UtcNow.AddSeconds(25)
    do {
        $running = @(Get-CimInstance Win32_Process -Filter "name='windhawk.exe'" |
            Where-Object { $_.CommandLine -like "*-tool-mod*`"$id`"*" })
        if (-not $running.Count) { return }
        Start-Sleep -Milliseconds 250
    } while ([DateTime]::UtcNow -lt $deadline)
    throw 'Tool process did not exit; the mod is left disabled.'
}

function Set-Revision([string]$library) {
    $p = Get-ItemProperty $key
    Write-Output "before: LibraryFileName=$($p.LibraryFileName) Disabled=$($p.Disabled)"
    Set-ItemProperty $key Disabled 1
    Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    Wait-ToolExit
    Set-ItemProperty $key LibraryFileName $library
    Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
    Set-ItemProperty $key Disabled $p.Disabled
    Start-Sleep -Seconds 2
    $after = Get-ItemProperty $key
    if ($after.LibraryFileName -ne $library) { throw "Switch failed: $($after.LibraryFileName)" }
    Write-Output "after:  LibraryFileName=$($after.LibraryFileName) Disabled=$($after.Disabled)"
}

if ($Audit) {
    $p = Get-ItemProperty $key
    [pscustomobject]@{
        library        = $p.LibraryFileName
        disabled       = $p.Disabled
        rev1_64_exists = Test-Path "$data\Engine\Mods\64\$rev1"
        rev2_64_exists = Test-Path "$data\Engine\Mods\64\$rev2"
        rev2_32_exists = Test-Path "$data\Engine\Mods\32\$rev2"
        rev2_64_probe  = if (Test-Path "$data\Engine\Mods\64\$rev2") { Get-Probe "$data\Engine\Mods\64\$rev2" | ConvertTo-Json -Compress } else { $null }
        built_64_hash  = if (Test-Path "$wk\build\local@taskbar-audio-visualizer_1.3.2_2_64.dll") { (Get-FileHash "$wk\build\local@taskbar-audio-visualizer_1.3.2_2_64.dll").Hash } else { $null }
        built_32_hash  = if (Test-Path "$wk\build\local@taskbar-audio-visualizer_1.3.2_2_32.dll") { (Get-FileHash "$wk\build\local@taskbar-audio-visualizer_1.3.2_2_32.dll").Hash } else { $null }
        modsSource_hash = (Get-FileHash "$data\ModsSource\$id.wh.cpp").Hash
        workCopy_hash   = (Get-FileHash $srcWork).Hash
    } | ConvertTo-Json -Depth 4
    return
}

if ($Install) {
    New-Item -ItemType Directory -Path $wk -Force | Out-Null
    $backup = Join-Path $wk 'mod-key-before.reg'
    if (-not (Test-Path $backup)) {
        & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" $backup /y | Out-Null
        Write-Output "registry backup: $backup"
    }
    Copy-Item $srcWork "$data\ModsSource\$id.wh.cpp" -Force
    Copy-Item "$wk\build\local@taskbar-audio-visualizer_1.3.2_2_64.dll" "$data\Engine\Mods\64\$rev2" -Force
    Copy-Item "$wk\build\local@taskbar-audio-visualizer_1.3.2_2_32.dll" "$data\Engine\Mods\32\$rev2" -Force
    if ((Get-FileHash "$data\ModsSource\$id.wh.cpp").Hash -ne (Get-FileHash $srcWork).Hash) { throw 'ModsSource copy does not match the work copy' }
    Set-ItemProperty $key Include 'explorer.exe'
    Set-Revision $rev2
    Write-Output "installed probe (64): $((Get-Probe "$data\Engine\Mods\64\$rev2") | ConvertTo-Json -Compress)"
    return
}

if ($Rollback) {
    Set-Revision $rev1
    return
}
