<#
The download engine for the Seamless Download Manager mod, from DavidHiFi's GitHub releases.
Seamless Workshop runs this: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
status reads this PC only. check also asks GitHub for the newest release. Needs no admin rights.
Each engine version has its own file name, so a new one never touches the copy the mod has open,
and older versions are left alone. -From <folder> takes the release files from a folder (for testing).
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto,
      [string]$From)
$ErrorActionPreference = 'Continue'; $ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
# The engine version the mod loads. Bumped together with the mod.
$need = '0.1.3'
$repo = 'DavidHiFi/seamless-download-manager'
$dir = Join-Path $env:LOCALAPPDATA 'SeamlessDownloadManager\engine'
$script:latest = ''

function Get-Name([string]$v) { "seamless_download_core-$v.dll" }

function Find-App {
    $f = Join-Path $dir (Get-Name $need)
    if (Test-Path -LiteralPath $f) { return @{ version = $need; file = $f } }
    $null
}

function Done([bool]$ok, [string]$message, [bool]$later = $false) {
    $a = Find-App
    $v = ''; if ($a) { $v = $a.version }
    $j = [ordered]@{ ok = $ok; installed = [bool]$a; version = $v; latest = $script:latest; message = $message; later = $later } | ConvertTo-Json -Compress
    if ($Out) { [IO.File]::WriteAllText($Out, $j, (New-Object Text.UTF8Encoding($false))) } else { $j }
    exit 0
}

function Get-Latest {
    if ($From) { $script:latest = $need; return }
    try {
        $r = Invoke-RestMethod "https://api.github.com/repos/$repo/releases/latest" -UseBasicParsing -TimeoutSec 30
        $v = ([string]$r.tag_name).TrimStart('v')
        if ($v -match '^\d+(\.\d+)*$') { $script:latest = $v }
    } catch { }
}

# Reads the first 64-character hash in a .sha256 file.
function Read-Sum([string]$text) {
    if ($text -match '([0-9a-fA-F]{64})') { return $Matches[1].ToLower() }
    ''
}

# Fetches the engine and its checksum, checks them, then moves it into place.
function Install-Engine([string]$v) {
    $name = Get-Name $v
    $tmp = Join-Path $env:TEMP ('seamless-download-core-' + [guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Force $tmp | Out-Null
    try {
        $file = Join-Path $tmp $name
        if ($From) {
            $src = Join-Path $From $name
            if (-not (Test-Path -LiteralPath $src) -or -not (Test-Path -LiteralPath "$src.sha256")) { return "The test folder has no $name with its checksum." }
            Copy-Item -LiteralPath $src $file
            $want = Read-Sum ([IO.File]::ReadAllText("$src.sha256"))
        } else {
            $base = "https://github.com/$repo/releases/download/v$v"
            Invoke-WebRequest "$base/$name" -OutFile $file -UseBasicParsing -TimeoutSec 600
            $sum = (Invoke-WebRequest "$base/$name.sha256" -UseBasicParsing -TimeoutSec 60).Content
            if ($sum -is [byte[]]) { $sum = [Text.Encoding]::ASCII.GetString($sum) }
            $want = Read-Sum $sum
        }
        $have = (Get-FileHash -LiteralPath $file -Algorithm SHA256).Hash.ToLower()
        if (-not $want -or $want -ne $have) { return 'The download did not match the checksum DavidHiFi published, so it was not used.' }
        New-Item -ItemType Directory -Force $dir | Out-Null
        Move-Item -LiteralPath $file (Join-Path $dir $name) -Force
        ''
    } catch { "The download from GitHub failed. $($_.Exception.Message)" }
    finally { Remove-Item $tmp -Recurse -Force -ErrorAction SilentlyContinue }
}

switch ($Mode) {
    'status' { Done $true '' }
    'check' { Get-Latest; Done $true '' }
    { $_ -in 'install', 'update' } {
        if (Find-App) { Get-Latest; Done $true '' }
        $err = Install-Engine $need
        if ($err) {
            if ($Auto) { Done $false "$err The Workshop tries again later." $true }
            Done $false $err
        }
        Get-Latest
        Done $true 'The download engine is in. The download manager starts it by itself.'
    }
    'remove' {
        if (-not (Test-Path -LiteralPath $dir)) { Done $true 'The download engine is not on this PC.' }
        $kept = 0
        foreach ($f in Get-ChildItem -LiteralPath $dir -Filter 'seamless_download_core-*.dll' -ErrorAction SilentlyContinue) {
            try { Remove-Item -LiteralPath $f.FullName -Force -ErrorAction Stop } catch { $kept++ }
        }
        if ($kept) { Done $false 'The download manager is still using the engine. Turn the mod off first, then click again.' }
        Done $true 'The download engine is removed. Your downloads and settings were kept.'
    }
}
