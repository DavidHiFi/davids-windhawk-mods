<#
.SYNOPSIS
Rebuilds this repo's generated files from the live Windhawk install.

.DESCRIPTION
Refreshes mods/catalog, mods/local, manifest.json, the catalog table, and the
settings exports (JSON and .reg) from C:\ProgramData\Windhawk and the registry.
The repo is kept an exact mirror of the machine: mods that are no longer
installed are removed from the sources, the manifest, the settings and the
catalog table, together with their previews and mod-storage folders. The
script only reads the system; it writes inside this repo. Run it after
changing mods or settings, review with git diff, and commit.

To rebuild the repo from a different machine, dump that machine's state with
Dump-WindhawkState.ps1, move the export folder over, then run

    .\Build-Repo.ps1 -FromExport <dir>

.PARAMETER SkipSources
Leave the mod source files alone and refresh only settings and metadata.

.PARAMETER FromExport
Path to a Dump-WindhawkState.ps1 export. Rebuilds from the export instead of
the local Windhawk install.

.EXAMPLE
.\Build-Repo.ps1
Full refresh from the local machine.

.EXAMPLE
.\Build-Repo.ps1 -FromExport H:\tmp\wh-export
Full refresh from an export made on another machine.
#>
[CmdletBinding()]
param(
    [switch]$SkipSources,
    [string]$FromExport
)

$ErrorActionPreference = 'Stop'
$retiredLocalIds = @('local@start-everything', 'center-titlebar-fork', 'local@center-titlebar-fork')
$keepRepoSource = @()
$repo = Split-Path $PSScriptRoot -Parent

$export = $null
if ($FromExport) {
    $export = $FromExport
    if (-not (Test-Path -LiteralPath (Join-Path $export 'ModsSource'))) { throw "Export has no ModsSource folder: $export" }
    $src = Join-Path $export 'ModsSource'
} else {
    $src = 'C:\ProgramData\Windhawk\ModsSource'
    if (-not (Test-Path -LiteralPath $src)) { throw "ModsSource not found at $src" }
}

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
    'local@windhawk-enhanced-styler' = 'mods\local\windhawk-enhanced-styler\windhawk-enhanced-styler.wh.cpp'
    'local@seamless-explorer-view' = 'mods\local\seamless-explorer-view\seamless-explorer-view.wh.cpp'
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
    'local@seamless-explorer-view' = 'https://windhawk.net/mods/gpu-accelerated-explorer-view'
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

function Convert-JsonToMap {
    param($Json)
    $map = [ordered]@{}
    if ($Json) { foreach ($p in $Json.PSObject.Properties) { $map[$p.Name] = $p.Value } }
    $map
}

# --- live state: the registry here, or the export's JSON files ---
if ($export) {
    $liveState = Convert-JsonToMap (Get-Content -LiteralPath (Join-Path $export 'mods-state.json') -Raw | ConvertFrom-Json)
    $liveSettings = Convert-JsonToMap (Get-Content -LiteralPath (Join-Path $export 'mods-settings.json') -Raw | ConvertFrom-Json)
    $liveLocalStorage = Convert-JsonToMap (Get-Content -LiteralPath (Join-Path $export 'quota-localstorage.json') -Raw | ConvertFrom-Json)
} else {
    $base = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
    $liveState = [ordered]@{}
    foreach ($k in Get-ChildItem $base) {
        $p = Get-ItemProperty $k.PSPath -ErrorAction SilentlyContinue
        $disabled = 0
        if ($null -ne $p.Disabled) { $disabled = [int]$p.Disabled }
        $liveState[$k.PSChildName] = [ordered]@{
            disabled     = $disabled -ne 0
            include      = [string]$p.Include
            exclude      = [string]$p.Exclude
            architecture = [string]$p.Architecture
            version      = [string]$p.Version
        }
    }
    # Same redaction Dump-WindhawkState.ps1 applies: weather location and secret-looking values stay out.
    $liveSettings = [ordered]@{}
    foreach ($k in Get-ChildItem "$base\*\Settings") {
        $id = Split-Path (Split-Path $k.PSPath -Parent) -Leaf
        $v = Get-ItemProperty $k.PSPath
        $vals = [ordered]@{}
        foreach ($p in $v.PSObject.Properties | Where-Object { $_.Name -notmatch '^PS' }) { $vals[$p.Name] = $p.Value }
        if ($id -match '^(local@)?taskbar-weather$') {
            foreach ($name in 'latitude', 'longitude', 'placeName') { $vals[$name] = '' }
        }
        foreach ($name in @($vals.Keys)) {
            if ($name -match '(?i)(api[-_]?key|secret|password|token)$' -and $vals[$name] -is [string]) { $vals[$name] = '' }
            if ($name -match '(?i)(latitude|longitude|placename)$' -or $name -match '(?i)weather\.location$') { $vals[$name] = '' }
        }
        $liveSettings[$id] = $vals
    }
    $liveLocalStorage = [ordered]@{}
    foreach ($id in 'taskbar-ai-quota', 'local@taskbar-ai-quota-opencode') {
        $v = Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\ModsWritable\$id\LocalStorage" -ErrorAction SilentlyContinue
        if ($v.settings_v1) { $liveLocalStorage[$id] = [ordered]@{ settings_v1 = ($v.settings_v1 | ConvertFrom-Json) } }
    }
    foreach ($id in @($liveLocalStorage.Keys)) {
        $accounts = $liveLocalStorage.$id.settings_v1.accounts
        if (-not $accounts) { continue }
        foreach ($a in $accounts) {
            foreach ($n in @($a.PSObject.Properties.Name | Where-Object { $_ -match 'Key|Token|Secret|Password' })) { $a.$n = '' }
        }
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
}

# --- per-mod state: only what is installed now ---
$mods = [ordered]@{}
foreach ($id in $liveState.Keys) {
    if ($id -in $retiredLocalIds) { continue }
    $mods[$id] = $liveState[$id]
}
$installedIds = @($mods.Keys)

$state = [ordered]@{}
foreach ($id in $installedIds) {
    $m = $mods[$id]
    $state[$id] = [ordered]@{ disabled = [bool]$m.disabled; include = [string]$m.include; exclude = [string]$m.exclude; architecture = [string]$m.architecture; version = [string]$m.version }
}
$state | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $repo 'settings\mods-state.json')

$settings = [ordered]@{}
foreach ($id in $installedIds) {
    if (-not $liveSettings.Contains($id)) { continue }
    $settings[$id] = $liveSettings[$id]
}
$settings | ConvertTo-Json -Depth 10 | Set-Content (Join-Path $repo 'settings\mods-settings.json')

if ($export) {
    Copy-Item -LiteralPath (Join-Path $export 'windhawk-app-settings.reg') (Join-Path $repo 'settings\windhawk-app-settings.reg') -Force
    Copy-Item -LiteralPath (Join-Path $export 'windhawk-engine-settings.reg') (Join-Path $repo 'settings\windhawk-engine-settings.reg') -Force
    Copy-Item -LiteralPath (Join-Path $export 'windhawk-userprofile.json') (Join-Path $repo 'settings\windhawk-userprofile.json') -Force
    $lsFile = Join-Path $repo 'settings\quota-mod-localstorage.json'
    $ls = [ordered]@{}
    foreach ($id in 'taskbar-ai-quota', 'local@taskbar-ai-quota-opencode') {
        if ($liveLocalStorage.Contains($id)) { $ls[$id] = $liveLocalStorage[$id] }
    }
    $ls | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $lsFile
} else {
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Settings' (Join-Path $repo 'settings\windhawk-app-settings.reg') /y | Out-Null
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Settings' (Join-Path $repo 'settings\windhawk-engine-settings.reg') /y | Out-Null
    Copy-Item 'C:\ProgramData\Windhawk\userprofile.json' (Join-Path $repo 'settings\windhawk-userprofile.json') -Force
    $ls = [ordered]@{}
    foreach ($id in 'taskbar-ai-quota', 'local@taskbar-ai-quota-opencode') {
        $v = Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\ModsWritable\$id\LocalStorage" -ErrorAction SilentlyContinue
        if ($v.settings_v1) { $ls[$id] = [ordered]@{ settings_v1 = ($v.settings_v1 | ConvertFrom-Json) } }
    }
    $ls | ConvertTo-Json -Depth 8 | Set-Content (Join-Path $repo 'settings\quota-mod-localstorage.json')
    # API keys stay out of the public repo: blank them in the file just written.
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
}

# --- manifest: every mod installed now, plus sources on disk with no registry entry ---
$manifestMods = foreach ($id in $installedIds) {
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
        version  = $(if ($mods[$id].version) { $mods[$id].version } else { $h.version })
        license  = $license
        origin   = $origin
        upstream = $upstream
        source   = $source
        enabled  = -not $mods[$id].disabled
    }
}
$manifestMods = @($manifestMods)
$have = @($manifestMods.id)
foreach ($f in Get-ChildItem -LiteralPath $src -File -Filter '*.wh.cpp') {
    $id = $f.Name -replace '\.wh\.cpp$', ''
    if ($id -in $retiredLocalIds -or $id -in $have -or "local@$id" -in $have -or ($id -replace '^local@', '') -in $have) { continue }
    $h = Get-ModHeader -Path $f.FullName
    $origin = if (Test-LocalId $id) { 'local' } else { 'catalog' }
    $source = if ($origin -eq 'local') { (Get-LocalPath $id) -replace '\\', '/' } else { "mods/catalog/$($f.Name)" }
    $manifestMods += [pscustomobject]@{
        id = $id; name = $h.name; author = $h.author; github = $h.github; version = $h.version; license = $h.license
        origin = $origin; upstream = $(if ($origin -eq 'catalog') { "https://windhawk.net/mods/$id" } else { '' }); source = $source; enabled = $false
    }
    $have += $id
}

# --- remove everything that is no longer installed ---
$removed = @()
$wantedCatalog = @($manifestMods | Where-Object { $_.origin -eq 'catalog' } | ForEach-Object { "$($_.id).wh.cpp" })
foreach ($f in Get-ChildItem -LiteralPath (Join-Path $repo 'mods\catalog') -File -Filter '*.wh.cpp') {
    if ($f.Name -notin $wantedCatalog) { $removed += $f.FullName.Substring($repo.Length + 1); Remove-Item -LiteralPath $f.FullName -Force }
}
$localTops = @{}
foreach ($id in $manifestMods.id) {
    if (-not (Test-LocalId $id)) { continue }
    $p = Join-Path $repo (Get-LocalPath $id)
    $top = $p.Substring((Join-Path $repo 'mods\local').Length + 1).Split('\')[0]
    $localTops[$top] = $true
}
foreach ($d in Get-ChildItem -LiteralPath (Join-Path $repo 'mods\local') -Directory) {
    $isMod = (Get-ChildItem -LiteralPath $d.FullName -File -Filter '*.wh.cpp' | Measure-Object).Count -gt 0
    if ($isMod -and -not $localTops.ContainsKey($d.Name)) { $removed += $d.FullName.Substring($repo.Length + 1); Remove-Item -LiteralPath $d.FullName -Recurse -Force }
}
foreach ($d in Get-ChildItem -LiteralPath (Join-Path $repo 'mod-storage') -Directory -ErrorAction SilentlyContinue) {
    if ($d.Name -notin $manifestMods.id -and ("local@$($d.Name)" -notin $manifestMods.id)) { $removed += $d.FullName.Substring($repo.Length + 1); Remove-Item -LiteralPath $d.FullName -Recurse -Force }
}
# Previews: keep referenced ones and those of installed local mods, drop the rest.
$mediaDir = Join-Path $repo 'media\previews'
if (Test-Path -LiteralPath $mediaDir) {
    $mdFiles = Get-ChildItem $repo -Recurse -File -Include *.md | ForEach-Object { $_.FullName }
    $refs = @()
    if ($mdFiles) { $refs = @(Select-String -Path $mdFiles -Pattern 'previews/([\w\-\.]+\.(?:png|gif))' -ErrorAction SilentlyContinue | ForEach-Object { $_.Matches[0].Groups[1].Value } | Select-Object -Unique) }
    foreach ($f in Get-ChildItem -LiteralPath $mediaDir -File) {
        $modFor = $f.BaseName
        $keptForMod = ($manifestMods | Where-Object { $_.origin -eq 'local' -and ($_.id -replace '^local@', '') -eq $modFor }).Count -gt 0
        if ($f.Name -notin $refs -and -not $keptForMod) { $removed += $f.FullName.Substring($repo.Length + 1); Remove-Item -LiteralPath $f.FullName -Force }
    }
}
if ($removed.Count) { Write-Output ("removed {0} path(s) no longer installed:`n  {1}" -f $removed.Count, ($removed -join "`n  ")) }

# --- manifest ---
$manifest = [ordered]@{
    name            = 'davids-windhawk-mods'
    description     = 'A full Windhawk setup: every mod source and every setting.'
    generatedAt     = (Get-Date).ToString('yyyy-MM-ddTHH:mm:sszzz')
    windhawkVersion = $(if ($export) { $v = Join-Path $export 'windhawk-version.txt'; if (Test-Path $v) { (Get-Content $v -Raw).Trim() } else { '' } } else { (Get-Item 'C:\Program Files\Windhawk\windhawk.exe').VersionInfo.ProductVersion })
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
