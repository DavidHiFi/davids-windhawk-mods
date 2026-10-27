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
$retiredLocalIds = @('local@start-everything')
# The installed copy lacks this repo copy's build fix (WS_EX_NOREDIRECTIONBITMAP guard), so keep the repo copy.
$keepRepoSource = @('local@remove-uwp-title-bars-plus')
$repo = Split-Path $PSScriptRoot -Parent
$src  = 'C:\ProgramData\Windhawk\ModsSource'
if (-not (Test-Path -LiteralPath $src)) { throw "ModsSource not found at $src" }

# Where the local (my) mods live in the repo. Other local@ mods use mods\local\<name>\<name>.wh.cpp; everything else is a catalog copy.
$localPaths = [ordered]@{
    'local@start-everything-plus' = 'mods\local\start-everything-plus\start-everything-plus.wh.cpp'
    'local@taskbar-audio-visualizer' = 'mods\local\taskbar-audio-visualizer\taskbar-audio-visualizer.wh.cpp'
    'local@window-manager' = 'mods\local\window-manager\window-manager.wh.cpp'
    'local@taskbar-weather' = 'mods\local\taskbar-weather\taskbar-weather.wh.cpp'
    'local@taskbar-system-info-weather' = 'mods\local\taskbar-system-info-weather\taskbar-system-info-weather.wh.cpp'
    'local@alt-snap-drag'             = 'mods\local\alt-snap-drag\alt-snap.wh.cpp'
    'local@taskbar-ai-quota-opencode' = 'mods\local\taskbar-ai-quota-opencode\taskbar-ai-quota-opencode.wh.cpp'
    'npp-taskdlg-textcolor'           = 'mods\local\npp-taskdlg-textcolor\npp-taskdlg-textcolor.wh.cpp'
    'local@translucent-flyouts'       = 'mods\local\translucent-flyouts\translucent-flyouts.wh.cpp'
    'local@better-volume-mixer-plus'  = 'mods\local\better-volume-mixer-plus\better-volume-mixer-plus.wh.cpp'
    'local@shell-font-changer-plus' = 'mods\local\shell-font-changer-plus\shell-font-changer-plus.wh.cpp'
    'local@windhawk-styler' = 'mods\local\windhawk-styler\windhawk-styler.wh.cpp'
}
# Values the source headers do not carry.
$licenseOverride = @{
    'local@window-manager' = 'GPL-3.0'
    'local@alt-snap-drag'   = 'GPL-3.0'
    'npp-taskdlg-textcolor' = 'MIT'
}
$upstreamOverride = @{
    'local@start-everything-plus' = 'https://windhawk.net/mods/start-everything'
    'local@taskbar-audio-visualizer' = 'https://windhawk.net/mods/tourne-table-desktop-audio-visualizer'
    'local@alt-snap-drag'             = 'https://windhawk.net/mods/alt-drag'
    'local@taskbar-ai-quota-opencode' = 'https://windhawk.net/mods/taskbar-ai-quota'
    'local@better-volume-mixer-plus'  = 'https://windhawk.net/mods/better-volume-mixer'
    'local@shell-font-changer-plus' = 'https://windhawk.net/mods/explorer-font-changer'
}
# Local mods that are not installed on this machine: id -> source and repo dest.
$offlineLocal = [ordered]@{
    'center-titlebar-fork' = @{
        src  = 'H:\Windhawk Configuration\Windhawk\center-titlebar-fork\center-titlebar-fork.wh.cpp'
        dest = 'mods\local\center-titlebar-fork\center-titlebar-fork.wh.cpp'
    }
}

function Test-LocalId {
    param([string]$Id)
    $Id.StartsWith('local@') -or $localPaths.Contains($Id)
}

function Get-LocalPath {
    param([string]$Id)
    if ($localPaths.Contains($Id)) { return $localPaths[$Id] }
    $name = $Id -replace '^local@', ''
    "mods\local\$name\$name.wh.cpp"
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
        if ($id -in $retiredLocalIds) { continue }
        if ($id -in $keepRepoSource) { Write-Warning "kept the repo copy of $id; the installed copy lacks its build fix"; continue }
        $dest = if (Test-LocalId $id) { Join-Path $repo (Get-LocalPath $id) } else { Join-Path $repo "mods\catalog\$($f.Name)" }
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
    if ($k.PSChildName -in $retiredLocalIds) { continue }
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
# Keep the saved state of mods that are not installed here.
$prevState = Join-Path $repo 'settings\mods-state.json'
if (Test-Path -LiteralPath $prevState) {
    foreach ($p in (Get-Content -LiteralPath $prevState -Raw | ConvertFrom-Json).PSObject.Properties) {
        if ($p.Name -notin $mods.id -and $p.Name -notin $retiredLocalIds) { $state[$p.Name] = $p.Value }
    }
}
$state | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $repo 'settings\mods-state.json')

$settings = [ordered]@{}
foreach ($k in Get-ChildItem "$base\*\Settings") {
    $id = Split-Path (Split-Path $k.PSPath -Parent) -Leaf
    if ($id -in $retiredLocalIds) { continue }
    $v = Get-ItemProperty $k.PSPath
    $vals = [ordered]@{}
    foreach ($p in $v.PSObject.Properties | Where-Object { $_.Name -notmatch '^PS' }) { $vals[$p.Name] = $p.Value }
    # Never publish the weather location from local settings.
    if ($id -match '^(local@)?taskbar-weather$') {
        foreach ($name in 'latitude', 'longitude', 'placeName') { $vals[$name] = '' }
    }
    # API keys stay out of the public repo, same rule as the quota file below. Numbers are left alone.
    foreach ($name in @($vals.Keys)) {
        if ($name -match '(?i)(api[-_]?key|secret|password|token)$' -and $vals[$name] -is [string]) { $vals[$name] = '' }
    }
    $settings[$id] = $vals
}
# Keep the saved settings of mods that are not installed here.
$prevSettings = Join-Path $repo 'settings\mods-settings.json'
if (Test-Path -LiteralPath $prevSettings) {
    foreach ($p in (Get-Content -LiteralPath $prevSettings -Raw | ConvertFrom-Json).PSObject.Properties) {
        if ($p.Name -notin $mods.id -and $p.Name -notin $retiredLocalIds) { $settings[$p.Name] = $p.Value }
    }
}
$settings | ConvertTo-Json -Depth 10 | Set-Content (Join-Path $repo 'settings\mods-settings.json')

& reg.exe export 'HKLM\SOFTWARE\Windhawk\Settings' (Join-Path $repo 'settings\windhawk-app-settings.reg') /y | Out-Null
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Settings' (Join-Path $repo 'settings\windhawk-engine-settings.reg') /y | Out-Null

$ls = [ordered]@{}
foreach ($id in 'taskbar-ai-quota', 'local@taskbar-ai-quota-opencode') {
    $v = Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\ModsWritable\$id\LocalStorage" -ErrorAction SilentlyContinue
    if ($v.settings_v1) { $ls[$id] = [ordered]@{ settings_v1 = ($v.settings_v1 | ConvertFrom-Json) } }
}
if ($ls.Count) { $ls | ConvertTo-Json -Depth 8 | Set-Content (Join-Path $repo 'settings\quota-mod-localstorage.json') }
# API keys stay out of the public repo: blank them in the live export and in the file already in the repo.
$lsFile = Join-Path $repo 'settings\quota-mod-localstorage.json'
if (Test-Path -LiteralPath $lsFile) {
    $quota = Get-Content -LiteralPath $lsFile -Raw | ConvertFrom-Json
    foreach ($id in $quota.PSObject.Properties.Name) {
        foreach ($a in $quota.$id.settings_v1.accounts) {
            foreach ($n in @($a.PSObject.Properties.Name | Where-Object { $_ -match 'Key|Token|Secret|Password' })) { $a.$n = '' }
        }
    }
    $quota | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $lsFile
}

Copy-Item 'C:\ProgramData\Windhawk\userprofile.json' (Join-Path $repo 'settings\windhawk-userprofile.json') -Force

# --- manifest ---
$manifestMods = foreach ($m in $mods) {
    $id = $m.id
    $origin = if (Test-LocalId $id) { 'local' } else { 'catalog' }
    $srcFile = Join-Path $src "$id.wh.cpp"
    $h = if (Test-Path -LiteralPath $srcFile) { Get-ModHeader -Path $srcFile } else { [pscustomobject]@{ name = ''; author = ''; github = ''; version = ''; license = '' } }
    $license = if ($licenseOverride.ContainsKey($id)) { $licenseOverride[$id] } elseif ($h.license) { $h.license } else { '' }
    $upstream = if ($upstreamOverride.ContainsKey($id)) { $upstreamOverride[$id] } elseif ($origin -eq 'catalog') { "https://windhawk.net/mods/$id" } else { '' }
    $source = if ($origin -eq 'local') { (Get-LocalPath $id) -replace '\\', '/' } else { "mods/catalog/$id.wh.cpp" }
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
# Entries published before that are not installed here stay listed, marked not enabled.
$have = @($manifestMods.id)
$prevManifest = Join-Path $repo 'manifest.json'
if (Test-Path -LiteralPath $prevManifest) {
    foreach ($p in (Get-Content -LiteralPath $prevManifest -Raw | ConvertFrom-Json).mods) {
        if ($p.id -in $have -or $p.id -in $retiredLocalIds) { continue }
        $p.enabled = $false
        $manifestMods += $p
        $have += $p.id
    }
}
# Local mods whose source is in the repo but that are not listed yet. Windhawk may store them with or without local@.
foreach ($f in Get-ChildItem -LiteralPath (Join-Path $repo 'mods\local') -Filter '*.wh.cpp' -Recurse -File | Where-Object { $_.Directory.Parent.Name -eq 'local' }) {
    $h = Get-ModHeader -Path $f.FullName
    if (-not $h.id -or $h.id -in $have -or "local@$($h.id)" -in $have) { continue }
    $manifestMods += [pscustomobject]@{
        id = $h.id; name = $h.name; author = $h.author; github = $h.github; version = $h.version; license = $h.license
        origin = 'local'; upstream = ''; source = $f.FullName.Substring($repo.Length + 1) -replace '\\', '/'; enabled = $false
    }
    $have += $h.id
}
$manifest = [ordered]@{
    name            = 'davids-windhawk-mods'
    description     = 'A full Windhawk setup: every mod source and every setting.'
    generatedAt     = (Get-Date).ToString('yyyy-MM-ddTHH:mm:sszzz')
    windhawkVersion = (Get-Item 'C:\Program Files\Windhawk\windhawk.exe').VersionInfo.ProductVersion
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
if ($extra.Count) { Write-Warning "catalog sources with no manifest entry: $($extra -join ', ')" }
if ($missing.Count) { Write-Warning "listed catalog mods with no source file: $($missing -join ', ')" }
Write-Output 'repo rebuilt'
