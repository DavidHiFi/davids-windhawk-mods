[CmdletBinding()]
param([switch]$Audit)
$ErrorActionPreference = 'Stop'
$root = 'H:\Windhawk Configuration'
$report = Join-Path $root 'reports\2026-10-09-styler-audit'
New-Item -ItemType Directory -Force -Path $report | Out-Null
'processes' | Set-Content "$report\audit-progress.txt"
$processes = @(Get-CimInstance Win32_Process | Where-Object {
    $_.Name -match '^windhawk|^VSCodium\.exe$' -or
    ($_.Name -eq 'msedgewebview2.exe' -and $_.CommandLine -match 'windhawk')
} | Select-Object Name,ProcessId,ParentProcessId,ExecutablePath,CommandLine,CreationDate)
'mods' | Add-Content "$report\audit-progress.txt"
$mods = @(Get-ChildItem 'HKLM:\SOFTWARE\Windhawk\Engine\Mods' | ForEach-Object {
    $key = Get-ItemProperty $_.PSPath
    $src = "C:\ProgramData\Windhawk\ModsSource\$($_.PSChildName).wh.cpp"
    $metadata = if (Test-Path -LiteralPath $src) { Get-Content -LiteralPath $src -TotalCount 35 } else { @() }
    $libraries = @(foreach ($arch in '64','32') {
        $dll = "C:\ProgramData\Windhawk\Engine\Mods\$arch\$($key.LibraryFileName)"
        if (Test-Path -LiteralPath $dll -PathType Leaf) {
            [ordered]@{arch=$arch;path=$dll;sha256=(Get-FileHash -LiteralPath $dll).Hash}
        }
    })
    [ordered]@{id=$_.PSChildName;disabled=$key.Disabled;include=$key.Include;exclude=$key.Exclude;
        architecture=$key.Architecture;version=$key.Version;library=$key.LibraryFileName;
        sourceExists=(Test-Path -LiteralPath $src);metadata=$metadata;libraries=$libraries}
})
$loaded = @()
$events = @()
$state = [ordered]@{time=(Get-Date -Format o);
    version=(Get-Item 'C:\Program Files\Windhawk\windhawk.exe').VersionInfo.FileVersion;
    uiSwitch=[ordered]@{machine=[Environment]::GetEnvironmentVariable('WINDHAWK_USE_VSCODIUM_UI','Machine');user=[Environment]::GetEnvironmentVariable('WINDHAWK_USE_VSCODIUM_UI','User');process=$env:WINDHAWK_USE_VSCODIUM_UI};
    service=(Get-CimInstance Win32_Service -Filter "Name='Windhawk'" | Select-Object State,StartMode,PathName);
    processes=$processes;loaded=$loaded;mods=$mods;events=$events}
$state | ConvertTo-Json -Depth 9 | Set-Content -LiteralPath "$report\audit-latest.json" -Encoding UTF8
$state | Select-Object time,version,uiSwitch,service | ConvertTo-Json -Depth 4
$processes | Format-Table Name,ProcessId,ParentProcessId,ExecutablePath -AutoSize
$loaded | ConvertTo-Json -Depth 4
Write-Output "Mod count: $($mods.Count). Enabled with no library: $(@($mods | Where-Object { !$_.disabled -and !$_.libraries.Count }).Count)."
Write-Output 'Application events are collected separately with wevtutil.'
