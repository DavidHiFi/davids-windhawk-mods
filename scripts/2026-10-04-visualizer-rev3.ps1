<#
.SYNOPSIS
Audit or roll back taskbar-audio-visualizer revision 3.

.DESCRIPTION
-Audit    reads the registry, the installed DLLs and the string probes, then
          prints whether revision 3 is live. It changes nothing.
-Rollback points the mod back at the revision 2 DLLs kept in
          backups\2026-10-04\mod-polish-final, using the same disable, wait,
          relabel, bump order as the installer. Run it through
          work\mod-polish-20261004\rollback-visualizer-rev3.cmd, which writes a
          log next to this script.

.PARAMETER Audit
See above.

.PARAMETER Rollback
See above.
#>
[CmdletBinding(DefaultParameterSetName = 'Audit')]
param(
    [Parameter(Mandatory, ParameterSetName = 'Audit')][switch]$Audit,
    [Parameter(Mandatory, ParameterSetName = 'Rollback')][switch]$Rollback
)
$ErrorActionPreference = 'Stop'
$id = 'local@taskbar-audio-visualizer'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$data = 'C:\ProgramData\Windhawk'
$rev2 = "${id}_1.2.0_2.dll"
$rev3 = "${id}_1.2.0_3.dll"

function Get-Strings([string]$DllPath) {
    $u16 = [System.Text.Encoding]::Unicode.GetString([System.IO.File]::ReadAllBytes($DllPath))
    [ordered]@{
        bodyNew  = $u16.Contains('Taskbar Audio Visualizer found something worth flagging')
        bodyOld  = $u16.Contains("Tourne'Table found")
        threadNew = $u16.Contains('TaskbarAudioVisualizer-Capture') -and $u16.Contains('TaskbarAudioVisualizer-Render')
        threadOld = $u16.Contains('DavidsAudioVisualizer-Render')
        classNew = $u16.Contains('TaskbarAudioVisualizerCapturePicker')
        classOld = $u16.Contains('DavidsAudioVisualizerCapturePicker')
    }
}

if ($Audit) {
    $p = Get-ItemProperty $key
    $lib = $p.LibraryFileName
    $arch = if (Test-Path "$data\Engine\Mods\64\$lib") { '64' } else { '32' }
    [pscustomobject]@{
        library      = $lib
        disabled     = $p.Disabled
        strings      = (Get-Strings "$data\Engine\Mods\$arch\$lib" | ConvertTo-Json -Compress)
        toolProcesses = @(Get-CimInstance Win32_Process -Filter "name='windhawk.exe'" | Where-Object { $_.CommandLine -like "*-tool-mod*`"$id`"*" }).Count
        sourceMatchesRepo = ((Get-FileHash "$data\ModsSource\$id.wh.cpp").Hash -eq
            (Get-FileHash 'H:\Windhawk Configuration\davids-windhawk-mods\mods\local\taskbar-audio-visualizer\taskbar-audio-visualizer.wh.cpp').Hash)
    } | ConvertTo-Json -Depth 4
    return
}

$p = Get-ItemProperty $key
Write-Output "before: LibraryFileName=$($p.LibraryFileName) Disabled=$($p.Disabled)"
Set-ItemProperty $key Disabled 1
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
$deadline = [DateTime]::UtcNow.AddSeconds(25)
do {
    $running = @(Get-CimInstance Win32_Process -Filter "name='windhawk.exe'" | Where-Object { $_.CommandLine -like "*-tool-mod*`"$id`"*" })
    if (-not $running.Count) { break }
    Start-Sleep -Milliseconds 250
} while ([DateTime]::UtcNow -lt $deadline)
if ($running.Count) { throw 'Tool process did not exit; left disabled' }
Set-ItemProperty $key LibraryFileName $rev2
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Set-ItemProperty $key Disabled $p.Disabled
Start-Sleep -Seconds 2
$after = Get-ItemProperty $key
if ($after.LibraryFileName -ne $rev2) { throw "Rollback failed: $($after.LibraryFileName)" }
foreach ($arch in '64', '32') {
    if (Test-Path "$data\Engine\Mods\$arch\$rev2") { Write-Output "$arch rev2 present: $((Get-FileHash "$data\Engine\Mods\$arch\$rev2").Hash)" }
}
Write-Output "after: LibraryFileName=$($after.LibraryFileName) Disabled=$($after.Disabled)"
