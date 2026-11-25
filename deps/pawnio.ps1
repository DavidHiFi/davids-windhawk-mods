<#
PawnIO for processor temperature, power and clocks (Seamless FPS Overlay, Seamless Taskbar):
the signed driver from namazso, the newest release from GitHub.
Seamless Workshop runs this: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
status reads this PC only. check also asks GitHub for the newest release. Run as admin.
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto)
$ErrorActionPreference = 'Continue'; $ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
$script:latest = ''

function Get-Entry {
    $keys = 'HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\*', 'HKLM:\Software\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\*'
    Get-ItemProperty $keys -ErrorAction SilentlyContinue | Where-Object { $_.DisplayName -eq 'PawnIO' } | Select-Object -First 1
}

function Test-Running { [bool](Get-Service PawnIO -ErrorAction SilentlyContinue | Where-Object Status -eq 'Running') }

# 2.2.0.0 is shown as 2.2.0 so the Workshop can compare it with the release tag.
function Ver {
    $e = Get-Entry
    if (-not $e -or -not $e.DisplayVersion) { return '' }
    try { $v = [version]$e.DisplayVersion; "$($v.Major).$($v.Minor).$([math]::Max(0, $v.Build))" } catch { [string]$e.DisplayVersion }
}

function Done([bool]$ok, [string]$message, [bool]$later = $false) {
    $j = [ordered]@{ ok = $ok; installed = [bool](Get-Entry); version = (Ver); latest = $script:latest; message = $message; later = $later } | ConvertTo-Json -Compress
    if ($Out) { [IO.File]::WriteAllText($Out, $j, (New-Object Text.UTF8Encoding($false))) } else { $j }
    exit 0
}

# The newest PawnIO.Setup release on GitHub and its PawnIO_setup.exe.
function Get-Latest {
    try {
        $r = Invoke-RestMethod 'https://api.github.com/repos/namazso/PawnIO.Setup/releases/latest' -TimeoutSec 30 -Headers @{ 'User-Agent' = 'SeamlessWorkshop' }
        $a = $r.assets | Where-Object { $_.name -eq 'PawnIO_setup.exe' } | Select-Object -First 1
        if (-not $a -or $a.browser_download_url -notmatch '^https://github\.com/namazso/PawnIO\.Setup/releases/download/') { return $null }
        $tag = $r.tag_name -replace '^v', ''
        if ($tag -notmatch '\.') { $tag += '.0' }
        $v = [version]$tag
        $script:latest = "$($v.Major).$($v.Minor).$([math]::Max(0, $v.Build))"
        @{ v = $script:latest; url = $a.browser_download_url }
    } catch { $null }
}

function Test-Newer([string]$a, [string]$b) {
    if (-not $a) { return $false }
    if (-not $b) { return $true }
    try { [version]$a -gt [version]$b } catch { $false }
}

# Downloads the setup, checks namazso signed it, then runs it silently. It upgrades in place.
function Install-Setup($best) {
    $tmp = Join-Path $env:TEMP ('seamless-pawnio-' + [guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Force $tmp | Out-Null
    try {
        $exe = Join-Path $tmp 'PawnIO_setup.exe'
        Invoke-WebRequest $best.url -OutFile $exe -UseBasicParsing -TimeoutSec 300
        $sig = Get-AuthenticodeSignature $exe
        if ($sig.Status -ne 'Valid' -or $sig.SignerCertificate.Subject -notmatch 'O=namazso') { return 'The download was not signed by namazso, so it was not used.' }
        $p = Start-Process $exe -ArgumentList '-install', '-silent' -Wait -PassThru -WindowStyle Hidden
        # 3010 means it went in and Windows wants a restart to finish.
        if ($p.ExitCode -eq 3010) { return 'restart' }
        if ($p.ExitCode -ne 0) { return "The PawnIO setup stopped with code $($p.ExitCode)." }
        ''
    } catch { "The download from GitHub failed. $($_.Exception.Message)" }
    finally { Remove-Item $tmp -Recurse -Force -ErrorAction SilentlyContinue }
}

switch ($Mode) {
    'status' { Done $true '' }
    'check' { $null = Get-Latest; Done $true '' }
    'update' {
        if (-not (Get-Entry)) { Done $false 'PawnIO is not installed.' }
        $best = Get-Latest
        if (-not $best) { Done $false 'Could not reach GitHub. The Workshop tries again later.' }
        if (-not (Test-Newer $best.v (Ver))) { Done $true '' }
        $err = Install-Setup $best
        if ($err -eq 'restart') { Done $true "PawnIO $($best.v) is in. It finishes after the next restart." $true }
        if ($err) { Done $false $err }
        Done $true "PawnIO $($best.v) is in."
    }
    'install' {
        if ((Get-Entry) -and (Test-Running)) {
            $best = Get-Latest
            if (-not $best -or -not (Test-Newer $best.v (Ver))) { Done $true "PawnIO $(Ver) is already running." }
        } else { $best = Get-Latest }
        if (-not $best -and -not (Get-Entry) -and (Get-Command winget -ErrorAction SilentlyContinue)) {
            winget install -e --id namazso.PawnIO --silent --accept-package-agreements --accept-source-agreements --disable-interactivity 2>&1 | Out-Null
        } elseif ($best) {
            $err = Install-Setup $best
            if ($err -eq 'restart') { Done $true 'PawnIO is in. Processor readings start after the next restart.' $true }
            if ($err) { Done $false $err }
        }
        if (-not (Get-Entry)) { Done $false 'PawnIO did not install. Check the internet connection and try again.' }
        for ($i = 0; $i -lt 10 -and -not (Test-Running); $i++) { Start-Sleep 1 }
        if (Test-Running) { Done $true "PawnIO $(Ver) is running. Processor readings show within a few seconds." }
        Done $true 'PawnIO is in. Processor readings start after the next restart.' $true
    }
    'remove' {
        $e = Get-Entry
        if ($e) {
            $un = Join-Path $e.InstallLocation 'uninstall.exe'
            if (Test-Path $un) { Start-Process $un -ArgumentList '-uninstall', '-silent' -Wait -WindowStyle Hidden }
        }
        if (Get-Entry) { Done $false 'PawnIO could not be removed. Close apps that read sensors and try again.' }
        Done $true 'PawnIO is removed. Processor temperature and power show a dash now.'
    }
}
