<#
.SYNOPSIS
Writes a portable export of this machine's live Windhawk state.

.DESCRIPTION
Collects everything Build-Repo.ps1 needs to rebuild the repo: mod sources,
per-mod state and settings, the app and engine .reg files, userprofile.json,
the quota mod's local storage, the Windhawk editor settings and mod-storage.
Secrets (API keys, tokens, passwords) and the weather location are blanked in
the export. Run it on the machine that has Windhawk, move the folder
anywhere, then rebuild there with Build-Repo.ps1 -FromExport <dir>.

.EXAMPLE
.\Dump-WindhawkState.ps1 -OutPath H:\tmp\wh-export
#>
[CmdletBinding()]
param([Parameter(Mandatory = $true)][string]$OutPath)

$ErrorActionPreference = 'Stop'
$OutPath = (New-Item -ItemType Directory -Path $OutPath -Force).FullName
$src = 'C:\ProgramData\Windhawk\ModsSource'
if (-not (Test-Path -LiteralPath $src)) { throw "ModsSource not found at $src" }

# --- mod sources ---
New-Item -ItemType Directory -Path (Join-Path $OutPath 'ModsSource') -Force | Out-Null
Copy-Item -Path (Join-Path $src '*.wh.cpp') -Destination (Join-Path $OutPath 'ModsSource') -Force

# --- per-mod state ---
$base = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$state = [ordered]@{}
foreach ($k in Get-ChildItem $base) {
    $p = Get-ItemProperty $k.PSPath -ErrorAction SilentlyContinue
    $disabled = 0
    if ($null -ne $p.Disabled) { $disabled = [int]$p.Disabled }
    $state[$k.PSChildName] = [ordered]@{
        disabled     = $disabled -ne 0
        include      = [string]$p.Include
        exclude      = [string]$p.Exclude
        architecture = [string]$p.Architecture
        version      = [string]$p.Version
    }
}
$state | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $OutPath 'mods-state.json')

# --- per-mod settings, with the same redaction Build-Repo applies ---
$settings = [ordered]@{}
foreach ($k in Get-ChildItem "$base\*\Settings") {
    $id = Split-Path (Split-Path $k.PSPath -Parent) -Leaf
    $v = Get-ItemProperty $k.PSPath
    $vals = [ordered]@{}
    foreach ($p in $v.PSObject.Properties | Where-Object { $_.Name -notmatch '^PS' }) { $vals[$p.Name] = $p.Value }
    # Never publish the weather location from local settings.
    if ($id -match '^(local@)?taskbar-weather$') {
        foreach ($name in 'latitude', 'longitude', 'placeName') { $vals[$name] = '' }
    }
    # API keys and locations stay out of the export. Numbers are left alone.
    foreach ($name in @($vals.Keys)) {
        if ($name -match '(?i)(api[-_]?key|secret|password|token)$' -and $vals[$name] -is [string]) { $vals[$name] = '' }
        if ($name -match '(?i)(latitude|longitude|placename)$' -or $name -match '(?i)weather\.location$') { $vals[$name] = '' }
    }
    $settings[$id] = $vals
}
$settings | ConvertTo-Json -Depth 10 | Set-Content -LiteralPath (Join-Path $OutPath 'mods-settings.json')

# --- app and engine settings as .reg ---
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Settings' (Join-Path $OutPath 'windhawk-app-settings.reg') /y | Out-Null
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Settings' (Join-Path $OutPath 'windhawk-engine-settings.reg') /y | Out-Null

# --- userprofile.json ---
Copy-Item -LiteralPath 'C:\ProgramData\Windhawk\userprofile.json' -Destination (Join-Path $OutPath 'windhawk-userprofile.json') -Force

# --- quota mod local storage (API keys blanked) ---
$ls = [ordered]@{}
foreach ($id in 'taskbar-ai-quota', 'local@taskbar-ai-quota-opencode') {
    $v = Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\ModsWritable\$id\LocalStorage" -ErrorAction SilentlyContinue
    if ($v.settings_v1) { $ls[$id] = [ordered]@{ settings_v1 = ($v.settings_v1 | ConvertFrom-Json) } }
}
foreach ($id in @($ls.Keys)) {
    $accounts = $ls.$id.settings_v1.accounts
    if (-not $accounts) { continue }
    foreach ($a in $accounts) {
        foreach ($n in @($a.PSObject.Properties.Name | Where-Object { $_ -match 'Key|Token|Secret|Password' })) { $a.$n = '' }
    }
}
$ls | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath (Join-Path $OutPath 'quota-localstorage.json')

# --- editor settings and mod-storage (were copied by hand before; part of the setup) ---
$editor = 'C:\ProgramData\Windhawk\UIData\user-data\User\settings.json'
if (Test-Path -LiteralPath $editor) { Copy-Item -LiteralPath $editor -Destination (Join-Path $OutPath 'editor-settings.json') -Force }
$ms = 'C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage'
if (Test-Path -LiteralPath $ms) {
    $sum = (Get-ChildItem $ms -Recurse -File | Measure-Object -Property Length -Sum).Sum
    if ($sum -lt 100MB) { Copy-Item $ms -Destination (Join-Path $OutPath 'mod-storage') -Recurse -Force }
    else { Write-Warning "mod-storage is $([math]::Round($sum / 1MB)) MB, skipped" }
}

# --- engine version ---
$exe = 'C:\Program Files\Windhawk\windhawk.exe'
if (Test-Path -LiteralPath $exe) { (Get-Item -LiteralPath $exe).VersionInfo.ProductVersion | Set-Content -LiteralPath (Join-Path $OutPath 'windhawk-version.txt') }

$files = Get-ChildItem $OutPath -Recurse -File
Write-Output ("export: {0} files, {1} KB -> {2}" -f $files.Count, [math]::Round(($files | Measure-Object -Property Length -Sum).Sum / 1KB), $OutPath)
