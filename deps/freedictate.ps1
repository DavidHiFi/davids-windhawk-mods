<#
FreeDictate, DavidHiFi's offline dictation app: installs or updates it from his GitHub releases.
Seamless Workshop runs this: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
status reads this PC only. check also asks GitHub for the newest release. Needs no admin rights.
It never closes FreeDictate: while it is open, an update waits.
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto)
$ErrorActionPreference = 'Continue'; $ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
$appKey = '{7C8F2A4E-5D1B-4B7E-9C3A-FD1C7A7E3D10}_is1'
$script:latest = ''

function Find-App {
    foreach ($root in 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall', 'HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall',
                      'HKLM:\Software\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall') {
        $u = Get-ItemProperty (Join-Path $root $appKey) -ErrorAction SilentlyContinue
        if ($u -and $u.InstallLocation -and (Test-Path (Join-Path $u.InstallLocation 'FreeDictate.exe'))) {
            $v = [string]$u.DisplayVersion
            if ($v -notmatch '^\d+(\.\d+)*$') { $v = '' }
            return @{ dir = $u.InstallLocation.TrimEnd('\'); version = $v }
        }
    }
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
    try {
        $r = Invoke-RestMethod 'https://api.github.com/repos/DavidHiFi/freedictate/releases/latest' -UseBasicParsing -TimeoutSec 30
        $v = ([string]$r.tag_name).TrimStart('v')
        if ($v -notmatch '^\d+(\.\d+)*$') { return $null }
        $setup = $r.assets | Where-Object { $_.name -eq "FreeDictate-$v-Setup.exe" } | Select-Object -First 1
        $sums = $r.assets | Where-Object { $_.name -eq 'SHA256SUMS' } | Select-Object -First 1
        if (-not $setup -or -not $sums) { return $null }
        $script:latest = $v
        @{ v = $v; url = $setup.browser_download_url; name = $setup.name; sums = $sums.browser_download_url }
    } catch { $null }
}

function Test-Newer([string]$a, [string]$b) {
    if (-not $a) { return $false }
    if (-not $b) { return $true }
    try { [version]$a -gt [version]$b } catch { $false }
}

# FreeDictate, or its Discord stream helper, is open.
function Test-Open { [bool](Get-Process FreeDictate, yapfast -ErrorAction SilentlyContinue) }

# Downloads the setup, checks it against the release's checksum list, runs it quietly for this user.
function Install-Release($best) {
    $tmp = Join-Path $env:TEMP ('seamless-freedictate-' + [guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Force $tmp | Out-Null
    try {
        if ($best.url -notlike 'https://github.com/DavidHiFi/freedictate/releases/download/*') { return 'The download was not from DavidHiFi.' }
        $setup = Join-Path $tmp $best.name
        Invoke-WebRequest $best.url -OutFile $setup -UseBasicParsing -TimeoutSec 600
        $sums = (Invoke-WebRequest $best.sums -UseBasicParsing -TimeoutSec 60).Content
        if ($sums -is [byte[]]) { $sums = [Text.Encoding]::ASCII.GetString($sums) }
        $want = ''
        foreach ($line in ($sums -split "`n")) { if ($line -match '^([0-9a-fA-F]{64})\s+\*?(\S+)\s*$' -and $Matches[2] -eq $best.name) { $want = $Matches[1].ToLower() } }
        $have = (Get-FileHash $setup -Algorithm SHA256).Hash.ToLower()
        if (-not $want -or $want -ne $have) { return 'The download did not match the checksum DavidHiFi published, so it was not used.' }
        $p = Start-Process $setup -ArgumentList '/VERYSILENT', '/CURRENTUSER', '/SUPPRESSMSGBOXES', '/NORESTART', '/NOCLOSEAPPLICATIONS' -Wait -PassThru -WindowStyle Hidden
        if ($p.ExitCode -ne 0) { return "The setup stopped with code $($p.ExitCode)." }
        ''
    } catch { "The download from GitHub failed. $($_.Exception.Message)" }
    finally { Remove-Item $tmp -Recurse -Force -ErrorAction SilentlyContinue }
}

# Starts it the way it starts at sign-in, so it never runs with admin rights.
function Start-App($a) {
    $task = Get-ScheduledTask -TaskName 'FreeDictate' -ErrorAction SilentlyContinue
    if ($task -and $task.State -ne 'Disabled') { Start-ScheduledTask -TaskName 'FreeDictate' }
    else { Start-Process explorer.exe -ArgumentList "`"$(Join-Path $a.dir 'FreeDictate.exe')`"" }
}

$a = Find-App
switch ($Mode) {
    'status' { Done $true '' }
    'check' { $null = Get-Latest; Done $true '' }
    { $_ -in 'install', 'update' } {
        $best = Get-Latest
        if (-not $best) { Done $false 'Could not reach GitHub. The Workshop tries again later.' }
        if ($a -and -not (Test-Newer $best.v $a.version)) { Done $true '' }
        if (Test-Open) {
            if ($Auto) { Done $false 'Goes in when FreeDictate is closed.' $true }
            Done $false 'Close FreeDictate first, then click again.'
        }
        $fresh = -not $a
        $err = Install-Release $best
        if ($err) { Done $false $err }
        $a = Find-App
        if (-not $a -or (Test-Newer $best.v $a.version)) { Done $false 'The new version did not go in.' }
        if ($fresh) { Start-App $a; Done $true "FreeDictate $($a.version) is installed and running." }
        Done $true "FreeDictate $($a.version) is in. Your settings stayed."
    }
    'remove' {
        if (-not $a) { Done $true 'FreeDictate is not on this PC.' }
        if (Test-Open) { Done $false 'Close FreeDictate first, then click again.' }
        $un = Join-Path $a.dir 'unins000.exe'
        if (-not (Test-Path $un)) { Done $false 'Its uninstaller is missing. Remove it from Installed apps.' }
        Start-Process $un -ArgumentList '/VERYSILENT', '/SUPPRESSMSGBOXES', '/NORESTART' -Wait -WindowStyle Hidden
        for ($i = 0; $i -lt 10 -and (Find-App); $i++) { Start-Sleep 1 }
        if (Find-App) { Done $false 'FreeDictate could not be removed.' }
        Done $true 'FreeDictate is removed. Your settings and history were kept.'
    }
}
