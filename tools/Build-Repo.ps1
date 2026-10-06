<#
.SYNOPSIS
Rebuilds this repo's generated files from the live Windhawk install.

.DESCRIPTION
Refreshes mods/catalog, mods/local, manifest.json, the catalog table, and the
settings exports (JSON and .reg) from C:\ProgramData\Windhawk and the registry.
The script only reads the system; it writes inside this repo. Run it after
changing mods or settings, review with git diff, and commit.

.PARAMETER SkipSources
Leave the mod source files alone and refresh only settings and metadata.

.EXAMPLE
.\Build-Repo.ps1
Full refresh.
#>
[CmdletBinding()]
param([switch]$SkipSources)

$ErrorActionPreference = 'Stop'
$repo = Split-Path $PSScriptRoot -Parent
$src  = 'C:\ProgramData\Windhawk\ModsSource'
if (-not (Test-Path -LiteralPath $src)) { throw "ModsSource not found at $src" }

# Where the local (my) mods live in the repo; everything else is a catalog copy.
$localPaths = [ordered]@{
    'local@taskbar-audio-visualizer' = 'mods\local\taskbar-audio-visualizer\taskbar-audio-visualizer.wh.cpp'
    'local@window-manager' = 'mods\local\window-manager\window-manager.wh.cpp'
    'local@taskbar-weather' = 'mods\local\taskbar-weather\taskbar-weather.wh.cpp'
    'local@taskbar-system-info-weather' = 'mods\local\taskbar-system-info-weather\taskbar-system-info-weather.wh.cpp'
    'local@alt-snap-drag'             = 'mods\local\alt-snap-drag\alt-snap.wh.cpp'
    'local@taskbar-ai-quota-opencode' = 'mods\local\taskbar-ai-quota-opencode\taskbar-ai-quota-opencode.wh.cpp'
    'npp-taskdlg-textcolor'           = 'mods\local\npp-taskdlg-textcolor\npp-taskdlg-textcolor.wh.cpp'
    'local@translucent-flyouts'       = 'mods\local\translucent-flyouts\translucent-flyouts.wh.cpp'
    'local@better-volume-mixer-plus'  = 'mods\local\better-volume-mixer-plus\better-volume-mixer-plus.wh.cpp'
    'local@shell-font-changer' = 'mods\local\shell-font-changer\shell-font-changer.wh.cpp'
    'local@windhawk-styler' = 'mods\local\windhawk-styler\windhawk-styler.wh.cpp'
}
# Values the source headers do not carry.
$licenseOverride = @{
    'local@window-manager' = 'GPL-3.0'
    'local@alt-snap-drag'   = 'GPL-3.0'
    'npp-taskdlg-textcolor' = 'MIT'
}
$upstreamOverride = @{
    'local@taskbar-audio-visualizer' = 'https://windhawk.net/mods/tourne-table-desktop-audio-visualizer'
    'local@alt-snap-drag'             = 'https://windhawk.net/mods/alt-drag'
    'local@taskbar-ai-quota-opencode' = 'https://windhawk.net/mods/taskbar-ai-quota'
    'local@better-volume-mixer-plus'  = 'https://windhawk.net/mods/better-volume-mixer'
    'local@shell-font-changer' = 'https://windhawk.net/mods/explorer-font-changer'
}
# Local mods that are not installed on this machine: id -> source and repo dest.
$offlineLocal = [ordered]@{
    'center-titlebar-fork' = @{
        src  = 'H:\Windhawk Configuration\Windhawk\center-titlebar-fork\center-titlebar-fork.wh.cpp'
        dest = 'mods\local\center-titlebar-fork\center-titlebar-fork.wh.cpp'
    }
}

function Get-ModHeader {
    param([string]$Path)
    $head = Get-Content -LiteralPath $Path -TotalCount 40
    $get = { param($tag) ($head | Where-Object { $_ -match "//\s*@$tag\s+(.+)" } | Select-Object -First 1) -replace ".*//\s*@$tag\s+", '' }
    [pscustomobject]@{
        id      = & $get 'id'
        name    = & $get 'name'
        version = & $get 'version'
        author  = & $get 'author'
        github  = & $get 'github'
        license = & $get 'license'
    }
}

# --- mod sources ---
if (-not $SkipSources) {
    foreach ($f in Get-ChildItem -LiteralPath $src -File -Filter '*.wh.cpp') {
        $id = $f.Name -replace '\.wh\.cpp$', ''
        $dest = if ($localPaths.Contains($id)) { Join-Path $repo $localPaths[$id] } else { Join-Path $repo "mods\catalog\$($f.Name)" }
        New-Item -ItemType Directory -Path (Split-Path $dest -Parent) -Force | Out-Null
        Copy-Item -LiteralPath $f.FullName -Destination $dest -Force
    }
    foreach ($id in $offlineLocal.Keys) {
        $o = $offlineLocal[$id]
        if (-not (Test-Path -LiteralPath $o.src)) { Write-Warning "offline local source missing: $($o.src)"; continue }
        $dest = Join-Path $repo $o.dest
        New-Item -ItemType Directory -Path (Split-Path $dest -Parent) -Force | Out-Null
        Copy-Item -LiteralPath $o.src -Destination $dest -Force
    }
}

# --- registry state and per-mod settings ---
$base = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$mods = foreach ($k in Get-ChildItem $base) {
    $p = Get-ItemProperty $k.PSPath -ErrorAction SilentlyContinue
    [pscustomobject]@{
        id           = $k.PSChildName
        disabled     = ([int]($p.Disabled ?? 0)) -ne 0
        include      = [string]$p.Include
        exclude      = [string]$p.Exclude
        architecture = [string]$p.Architecture
        version      = [string]$p.Version
    }
}
$state = [ordered]@{}
foreach ($m in $mods) {
    $state[$m.id] = [ordered]@{ disabled = $m.disabled; include = $m.include; exclude = $m.exclude; architecture = $m.architecture; version = $m.version }
}
$state | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $repo 'settings\mods-state.json')

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
    $settings[$id] = $vals
}
$settings | ConvertTo-Json -Depth 6 | Set-Content (Join-Path $repo 'settings\mods-settings.json')

& reg.exe export 'HKLM\SOFTWARE\Windhawk\Settings' (Join-Path $repo 'settings\windhawk-app-settings.reg') /y | Out-Null
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Settings' (Join-Path $repo 'settings\windhawk-engine-settings.reg') /y | Out-Null

$ls = [ordered]@{}
foreach ($id in 'taskbar-ai-quota', 'local@taskbar-ai-quota-opencode') {
    $v = Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\ModsWritable\$id\LocalStorage" -ErrorAction SilentlyContinue
    if ($v.settings_v1) { $ls[$id] = [ordered]@{ settings_v1 = ($v.settings_v1 | ConvertFrom-Json) } }
}
if ($ls.Count) { $ls | ConvertTo-Json -Depth 8 | Set-Content (Join-Path $repo 'settings\quota-mod-localstorage.json') }

Copy-Item 'C:\ProgramData\Windhawk\userprofile.json' (Join-Path $repo 'settings\windhawk-userprofile.json') -Force

# --- manifest ---
$manifestMods = foreach ($m in $mods) {
    $id = $m.id
    $origin = if ($localPaths.Contains($id)) { 'local' } else { 'catalog' }
    $srcFile = Join-Path $src "$id.wh.cpp"
    $h = if (Test-Path -LiteralPath $srcFile) { Get-ModHeader -Path $srcFile } else { [pscustomobject]@{ name = ''; author = ''; github = ''; version = ''; license = '' } }
    $license = if ($licenseOverride.ContainsKey($id)) { $licenseOverride[$id] } elseif ($h.license) { $h.license } else { '' }
    $upstream = if ($upstreamOverride.ContainsKey($id)) { $upstreamOverride[$id] } elseif ($origin -eq 'catalog') { "https://windhawk.net/mods/$id" } else { '' }
    $source = if ($origin -eq 'local') { $localPaths[$id] -replace '\\', '/' } else { "mods/catalog/$id.wh.cpp" }
    [pscustomobject]@{
        id       = $id
        name     = $h.name
        author   = $h.author
        github   = $h.github
        version  = $(if ($m.version) { $m.version } else { $h.version })
        license  = $license
        origin   = $origin
        upstream = $upstream
        source   = $source
        enabled  = -not $m.disabled
    }
}
$manifestMods = @($manifestMods)
foreach ($id in $offlineLocal.Keys) {
    $o = $offlineLocal[$id]
    if (-not (Test-Path -LiteralPath $o.src)) { continue }
    $h = Get-ModHeader -Path $o.src
    $manifestMods += [pscustomobject]@{
        id       = $id
        name     = $h.name
        author   = $h.author
        github   = $h.github
        version  = $h.version
        license  = $h.license
        origin   = 'local'
        upstream = 'https://windhawk.net/mods/center-titlebar'
        source   = $o.dest -replace '\\', '/'
        enabled  = $false
    }
}
$manifest = [ordered]@{
    name            = 'davids-windhawk-mods'
    description     = 'A full Windhawk setup: every mod source and every setting.'
    generatedAt     = (Get-Date).ToString('yyyy-MM-ddTHH:mm:sszzz')
    windhawkVersion = '1.7.3'
    counts          = [ordered]@{
        mods    = $manifestMods.Count
        enabled = @($manifestMods | Where-Object { $_.enabled }).Count
        local   = @($manifestMods | Where-Object { $_.origin -eq 'local' }).Count
    }
    mods            = $manifestMods
}
$manifest | ConvertTo-Json -Depth 6 | Set-Content (Join-Path $repo 'manifest.json')

# --- catalog table ---
$cat = $manifestMods | Where-Object { $_.origin -eq 'catalog' } | Sort-Object id
$lines = @(
    '# Catalog mods'
    ''
    'Copies of the [Windhawk catalog](https://windhawk.net/mods) mods this setup runs, exactly as installed on the machine. Each mod is its author''s work and keeps its own license; names link to the author''s page when the source header has one.'
    ''
    '| Mod | Author | Version | Runs | License |'
    '| --- | --- | --- | --- | --- |'
)
foreach ($c in $cat) {
    $author = $c.author -replace ' <.*>', ''
    if ($c.github) { $author = "[$author]($($c.github))" }
    $runs = if ($c.enabled) { 'yes' } else { 'no' }
    $lines += "| [$($c.id)](./$($c.id).wh.cpp) | $author | $($c.version) | $runs | $($c.license) |"
}
Set-Content (Join-Path $repo 'mods\catalog\README.md') ($lines -join "`n")

# --- sanity ---
$catalogFiles = Get-ChildItem (Join-Path $repo 'mods\catalog') -File -Filter '*.wh.cpp'
$wanted = @($manifestMods | Where-Object { $_.origin -eq 'catalog' } | ForEach-Object { "$($_.id).wh.cpp" })
$extra = @($catalogFiles | Where-Object { $_.Name -notin $wanted } | ForEach-Object { $_.Name })
$missing = @($wanted | Where-Object { $_ -notin $catalogFiles.Name })
Write-Output "manifest mods: $($manifestMods.Count), local: $($manifest.counts.local), enabled: $($manifest.counts.enabled)"
if ($extra.Count) { Write-Warning "catalog sources with no installed mod: $($extra -join ', ')" }
if ($missing.Count) { Write-Warning "installed mods with no source: $($missing -join ', ')" }
Write-Output 'repo rebuilt'
