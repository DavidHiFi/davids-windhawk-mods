<#
Mocha Steam, DavidHiFi's Steam theme for Millennium, with his plugins and settings: installs or
updates it from his GitHub releases through the release's own setup script.
Seamless Workshop runs this: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
status reads this PC only. check also asks GitHub for the newest release. Run as admin.
Steam has to close for the theme to change. That happens only when someone clicks Install or
Update, never while a game runs, and Steam opens again after.
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto)
$ErrorActionPreference = 'Continue'; $ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
# The version the Workshop put in. A copy set up some other way has none, and is never updated by itself.
$marker = Join-Path $env:ProgramData 'SeamlessWorkshop\extras\mocha-steam.version'
$script:latest = ''

function Find-Steam {
    $c = @()
    $p = (Get-ItemProperty 'HKCU:\Software\Valve\Steam' -ErrorAction SilentlyContinue).SteamPath
    if ($p) { $c += $p.Replace('/', '\') }
    $p = (Get-ItemProperty 'HKLM:\Software\WOW6432Node\Valve\Steam' -ErrorAction SilentlyContinue).InstallPath
    if ($p) { $c += $p }
    $c += Join-Path ${env:ProgramFiles(x86)} 'Steam'
    foreach ($d in $c) { if (Test-Path (Join-Path $d 'steam.exe')) { return $d.TrimEnd('\') } }
    $null
}

$steam = Find-Steam
function Theme { if ($steam) { Join-Path $steam 'millennium\themes\MochaSteam' } else { $null } }

function Done([bool]$ok, [string]$message, [bool]$later = $false) {
    $t = Theme
    $installed = [bool]($t -and (Test-Path $t))
    $v = ''
    if ($installed -and (Test-Path $marker)) { $v = ([string](Get-Content $marker -TotalCount 1)).Trim(); if ($v -notmatch '^\d+(\.\d+)*$') { $v = '' } }
    $j = [ordered]@{ ok = $ok; installed = $installed; version = $v; latest = $script:latest; message = $message; later = $later } | ConvertTo-Json -Compress
    if ($Out) { [IO.File]::WriteAllText($Out, $j, (New-Object Text.UTF8Encoding($false))) } else { $j }
    exit 0
}

function Get-Latest {
    try {
        $r = Invoke-RestMethod 'https://api.github.com/repos/DavidHiFi/MochaSteam/releases/latest' -UseBasicParsing -TimeoutSec 30
        $v = ([string]$r.tag_name).TrimStart('v')
        if ($v -notmatch '^\d+(\.\d+)*$') { return $null }
        $zip = $r.assets | Where-Object { $_.name -like 'MochaSteam-*.zip' } | Select-Object -First 1
        if (-not $zip) { return $null }
        $script:latest = $v
        @{ v = $v; url = $zip.browser_download_url }
    } catch { $null }
}

function Test-Newer([string]$a, [string]$b) {
    if (-not $a) { return $false }
    if (-not $b) { return $true }
    try { [version]$a -gt [version]$b } catch { $false }
}

function Get-SteamProcs {
    Get-Process steam -ErrorAction SilentlyContinue | Where-Object { try { $_.Path -eq (Join-Path $steam 'steam.exe') } catch { $false } }
}

# Steam says which game runs. While one does, Steam stays as it is.
function Test-Game {
    $id = (Get-ItemProperty 'HKCU:\Software\Valve\Steam' -ErrorAction SilentlyContinue).RunningAppID
    $id -and [int]$id -ne 0
}

function Close-Steam {
    if (-not (Get-SteamProcs)) { return $true }
    Start-Process (Join-Path $steam 'steam.exe') -ArgumentList '-shutdown'
    for ($i = 0; $i -lt 45 -and (Get-SteamProcs); $i++) { Start-Sleep 2 }
    -not (Get-SteamProcs)
}

# Through Explorer, so Steam runs as the user and not as admin.
function Open-Steam { Start-Process explorer.exe -ArgumentList "`"$(Join-Path $steam 'steam.exe')`"" }

$t = Theme
$have = [bool]($t -and (Test-Path $t))
switch ($Mode) {
    'status' { Done $true '' }
    'check' { $null = Get-Latest; Done $true '' }
    { $_ -in 'install', 'update' } {
        if (-not $steam) { Done $false 'Steam is not installed.' }
        $best = Get-Latest
        if (-not $best) { Done $false 'Could not reach GitHub. The Workshop tries again later.' }
        if ($Mode -eq 'update' -and $have -and (Test-Path $marker) -and -not (Test-Newer $best.v ([string](Get-Content $marker -TotalCount 1)).Trim())) { Done $true '' }
        $millennium = Test-Path (Join-Path $steam 'millennium')
        $open = [bool](Get-SteamProcs)
        if ($Auto) {
            if ($open) { Done $false 'Goes in when Steam is closed.' $true }
            if (-not $millennium) { Done $false 'Steam needs Millennium first. Click Install here to set it up.' }
        }
        if (Test-Game) { Done $false 'A game is running. Click again when it is closed.' }
        if ($best.url -notlike 'https://github.com/DavidHiFi/MochaSteam/releases/download/*') { Done $false 'The download was not from DavidHiFi.' }
        if (-not (Close-Steam)) { Done $false 'Steam did not close. Close it, then click again.' }
        $tmp = Join-Path $env:TEMP ('seamless-mochasteam-' + [guid]::NewGuid().ToString('N'))
        New-Item -ItemType Directory -Force $tmp | Out-Null
        $err = ''
        try {
            $zip = Join-Path $tmp 'release.zip'
            Invoke-WebRequest $best.url -OutFile $zip -UseBasicParsing -TimeoutSec 300
            Expand-Archive $zip -DestinationPath (Join-Path $tmp 'x') -Force
            $setup = Get-ChildItem (Join-Path $tmp 'x') -Recurse -Filter 'Install-MochaSetup.ps1' | Select-Object -First 1
            if (-not $setup) { $err = 'The release had no setup in it.' }
            else {
                $args2 = @('-NoProfile', '-NonInteractive', '-ExecutionPolicy', 'Bypass', '-File', "`"$($setup.FullName)`"", '-SteamPath', "`"$steam`"")
                if ($Auto) { $args2 += '-SkipMillenniumInstall' }
                $p = Start-Process powershell.exe -ArgumentList $args2 -Wait -PassThru -WindowStyle Hidden
                if ($p.ExitCode -ne 0) { $err = 'The Mocha Steam setup did not finish. Nothing you had was lost: it keeps backups in Steam.' }
            }
        } catch { $err = "The download from GitHub failed. $($_.Exception.Message)" }
        finally { Remove-Item $tmp -Recurse -Force -ErrorAction SilentlyContinue }
        if (-not $err) {
            New-Item -ItemType Directory -Force (Split-Path $marker) | Out-Null
            Set-Content $marker $best.v -Encoding ascii
        }
        if ($open) { Open-Steam }
        if ($err) { Done $false $err }
        Done $true "Mocha Steam $($best.v) is in.$(if ($open) { ' Steam opened again.' })"
    }
    'remove' {
        if (-not $have) { Remove-Item $marker -Force -ErrorAction SilentlyContinue; Done $true 'Mocha Steam is not on this PC.' }
        if (Test-Game) { Done $false 'A game is running. Click again when it is closed.' }
        $open = [bool](Get-SteamProcs)
        if (-not (Close-Steam)) { Done $false 'Steam did not close. Close it, then click again.' }
        # Moved aside, not deleted: Steam\millennium\_backups keeps it.
        $bak = Join-Path $steam "millennium\_backups\$(Get-Date -Format yyyyMMdd-HHmmss)-removed"
        New-Item -ItemType Directory -Force $bak | Out-Null
        Move-Item $t (Join-Path $bak 'MochaSteam') -Force -ErrorAction SilentlyContinue
        $plugin = Join-Path $steam 'millennium\plugins\mochasteam-material'
        if (Test-Path $plugin) { Move-Item $plugin (Join-Path $bak 'mochasteam-material') -Force -ErrorAction SilentlyContinue }
        Remove-Item $marker -Force -ErrorAction SilentlyContinue
        if ($open) { Open-Steam }
        if (Test-Path $t) { Done $false 'Mocha Steam could not be removed. Close Steam and try again.' }
        Done $true 'Mocha Steam is removed. Steam uses its own look again.'
    }
}
