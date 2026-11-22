<#
.SYNOPSIS
Installs Windhawk fresh or updates an existing install to the newest alpha release on GitHub.

.DESCRIPTION
Downloads the official installer from ramensoftware/windhawk, then checks three things before
running it: the SHA256 hash against the release digest, the Authenticode signature against the
Windhawk author's certificate, and the installer's file version against the release tag.
The install itself is the official installer in silent mode, so mods and their settings are kept.

  (no switch)   install or update to the newest pre-release
  -Check        show the installed and newest versions, change nothing
  -Tag X        install one specific release, for example -Tag 2.0.0-alpha.8
  -Offline      use windhawk_setup_offline.exe (about 178 MB) instead of the small web setup
  -SelfTest     run the version-comparison checks and exit
  -Pause        wait for Enter at the end (used by the self-elevation relaunch)

Run it with Windows PowerShell:
  powershell -NoProfile -ExecutionPolicy Bypass -File .\Update-Windhawk.ps1
A normal, non-admin run asks for administrator permission by itself.
#>
[CmdletBinding()]
param(
    [switch]$Check,
    [switch]$Offline,
    [switch]$SelfTest,
    [switch]$Pause,
    [string]$Tag
)

$ErrorActionPreference = 'Stop'
$repo       = 'ramensoftware/windhawk'
$apiBase    = "https://api.github.com/repos/$repo"
$signer     = 'Michael Maltsev'
$webAsset   = 'windhawk_setup.exe'
$offlineAsset = 'windhawk_setup_offline.exe'

if ($PSVersionTable.PSVersion.Major -le 5) {
    [Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
}

function Compare-Core([string]$X, [string]$Y) {
    $xs = $X.Split('.'); $ys = $Y.Split('.')
    for ($i = 0; $i -lt [Math]::Max($xs.Count, $ys.Count); $i++) {
        $x = if ($i -lt $xs.Count) { $xs[$i] } else { '0' }
        $y = if ($i -lt $ys.Count) { $ys[$i] } else { '0' }
        if ($x -eq $y) { continue }
        $xn = [long]0; $yn = [long]0
        if ([long]::TryParse($x, [ref]$xn) -and [long]::TryParse($y, [ref]$yn)) { return [Math]::Sign($xn - $yn) }
        return [Math]::Sign([string]::Compare($x, $y, $true))
    }
    return 0
}

function Compare-Prerelease([string]$X, [string]$Y) {
    if ($X -eq $Y) { return 0 }
    if (-not $X) { return 1 }   # a plain version is newer than any pre-release of it
    if (-not $Y) { return -1 }
    $xs = $X.Split('.'); $ys = $Y.Split('.')
    for ($i = 0; $i -lt [Math]::Max($xs.Count, $ys.Count); $i++) {
        if ($i -ge $xs.Count) { return -1 }
        if ($i -ge $ys.Count) { return 1 }
        $x = $xs[$i]; $y = $ys[$i]
        if ($x -eq $y) { continue }
        $xn = [long]0; $yn = [long]0
        if ([long]::TryParse($x, [ref]$xn) -and [long]::TryParse($y, [ref]$yn)) { return [Math]::Sign($xn - $yn) }
        if ([long]::TryParse($x, [ref]$xn)) { return -1 }   # numbers sort before words
        if ([long]::TryParse($y, [ref]$yn)) { return 1 }
        return [Math]::Sign([string]::Compare($x, $y, $true))
    }
    return 0
}

function Compare-Version([string]$A, [string]$B) {
    if ($A -eq $B) { return 0 }
    $a = $A.TrimStart('v', 'V'); $b = $B.TrimStart('v', 'V')
    if ($a -eq $b) { return 0 }
    $aParts = $a -split '-', 2; $bParts = $b -split '-', 2
    $aPre = ''; $bPre = ''
    if ($aParts.Count -gt 1) { $aPre = $aParts[1] }
    if ($bParts.Count -gt 1) { $bPre = $bParts[1] }
    $core = Compare-Core $aParts[0] $bParts[0]
    if ($core -ne 0) { return $core }
    return Compare-Prerelease $aPre $bPre
}

function Get-UninstallKey {
    $key = Get-ItemProperty 'HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\Windhawk' -ErrorAction SilentlyContinue
    if (-not $key) {
        $key = Get-ItemProperty 'HKLM:\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\Windhawk' -ErrorAction SilentlyContinue
    }
    return $key
}

function Get-InstallDir {
    $key = Get-UninstallKey
    if ($key -and $key.InstallLocation) { return $key.InstallLocation.TrimEnd('\') }
    if (Test-Path "$env:ProgramFiles\Windhawk\windhawk.exe") { return "$env:ProgramFiles\Windhawk" }
    return $null
}

function Get-InstalledVersion([string]$Dir) {
    $key = Get-UninstallKey
    if ($key -and $key.DisplayVersion) { return $key.DisplayVersion }
    if (-not $Dir) { return $null }
    $exe = Join-Path $Dir 'windhawk.exe'
    if (Test-Path $exe) { return (Get-Item $exe).VersionInfo.FileVersion }
    return $null
}

function Test-Administrator {
    $identity = [Security.Principal.WindowsIdentity]::GetCurrent()
    return (New-Object Security.Principal.WindowsPrincipal($identity)).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

if ($SelfTest) {
    $cases = @(
        @('1.7.3',         '2.0.0-alpha.8', -1),
        @('2.0.0-alpha.8', '2.0.0-alpha.8',  0),
        @('2.0.0-alpha.8', '2.0.0-alpha.10', -1),
        @('2.0.0-alpha.8', '2.0.0-beta.1',   -1),
        @('2.0.0-alpha.8', '2.0.0',          -1),
        @('v1.7.3',        '1.7.3',           0),
        @('2.0.0-alpha.8', '1.7.3',           1)
    )
    foreach ($c in $cases) {
        $got = Compare-Version $c[0] $c[1]
        if ($got -ne $c[2]) { throw ("compare {0} vs {1}: got {2}, expected {3}" -f $c[0], $c[1], $got, $c[2]) }
    }
    Write-Host ("selftest: all {0} version comparisons passed" -f $cases.Count)
    return
}

$exitCode = 0
try {
    $headers = @{ 'User-Agent' = 'windhawk-alpha-updater-script' }

    if ($Tag) {
        $release = Invoke-RestMethod -Uri "$apiBase/releases/tags/$Tag" -Headers $headers
    } else {
        Write-Host 'Looking up the newest Windhawk pre-release...'
        $releases = Invoke-RestMethod -Uri "$apiBase/releases?per_page=30" -Headers $headers
        $release = $releases | Where-Object { $_.prerelease } | Sort-Object { $_.published_at } -Descending | Select-Object -First 1
    }
    if (-not $release) { throw "no Windhawk pre-release found on GitHub ($repo)" }
    $targetTag = $release.tag_name

    $assetName = $webAsset
    if ($Offline) { $assetName = $offlineAsset }
    $asset = $release.assets | Where-Object { $_.name -eq $assetName } | Select-Object -First 1
    if (-not $asset -or -not $asset.digest) { throw "$assetName with a sha256 digest was not found on $targetTag" }
    $expectedSha = ($asset.digest -replace '^sha256:', '')

    $installDir = Get-InstallDir
    $installed = $null
    if ($installDir) { $installed = Get-InstalledVersion $installDir }

    Write-Host ("Installed Windhawk : " + $(if ($installed) { $installed } else { 'not installed' }))
    Write-Host ("Target release     : $targetTag")

    if ($Check) { return }

    if ($installed) {
        $cmp = Compare-Version $installed $targetTag
        if ($cmp -eq 0) { Write-Host "Already on $targetTag. Nothing to do."; return }
        if ($cmp -gt 0) { Write-Host "Installed $installed is newer than $targetTag. Nothing to do."; return }
        Write-Host ("Updating {0} to {1}..." -f $installed, $targetTag)
    } else {
        Write-Host "Windhawk is not installed. Installing $targetTag..."
    }

    if (-not (Test-Administrator)) {
        if (-not $PSCommandPath) { throw 'run this script as a saved .ps1 file so it can ask for administrator permission' }
        Write-Host 'Asking for administrator permission...'
        $argLine = '-NoProfile -ExecutionPolicy Bypass -File "' + $PSCommandPath + '"'
        if ($Offline) { $argLine += ' -Offline' }
        if ($Tag)     { $argLine += ' -Tag "' + $Tag + '"' }
        $argLine += ' -Pause'
        try { Start-Process -FilePath 'powershell.exe' -ArgumentList $argLine -Verb RunAs | Out-Null }
        catch { throw 'administrator permission was declined; nothing was changed' }
        return
    }

    $dlDir = Join-Path (Join-Path $env:TEMP 'windhawk-alpha-updater') $targetTag
    New-Item -ItemType Directory -Force -Path $dlDir | Out-Null
    $installerFile = Join-Path $dlDir $assetName
    $sizeMb = [Math]::Round($asset.size / 1MB, 1)
    Write-Host ("Downloading {0} ({1} MB)..." -f $assetName, $sizeMb)
    $web = New-Object System.Net.WebClient
    $web.DownloadFile($asset.browser_download_url, $installerFile)

    $actualSha = (Get-FileHash $installerFile -Algorithm SHA256).Hash
    if (-not $actualSha.Equals($expectedSha, [StringComparison]::OrdinalIgnoreCase)) {
        throw "SHA256 mismatch: got $actualSha, release says $expectedSha"
    }
    Write-Host 'SHA256 matches the release digest.'

    $sig = Get-AuthenticodeSignature $installerFile
    $subject = ''
    if ($sig.SignerCertificate) { $subject = $sig.SignerCertificate.Subject }
    if ($sig.Status -ne 'Valid' -or $subject -notmatch [regex]::Escape($signer)) {
        throw "signature check failed: status $($sig.Status), signer $subject"
    }
    Write-Host "Authenticode signature valid: $subject"

    $fileVersion = (Get-Item $installerFile).VersionInfo.FileVersion
    if ($fileVersion -ne $targetTag) { throw "installer file version $fileVersion does not match tag $targetTag" }
    Write-Host 'Installer file version matches the tag.'

    if ($installDir) {
        Write-Host 'Stopping Windhawk...'
        Stop-Service -Name Windhawk -Force -ErrorAction SilentlyContinue
        $proc = Start-Process -FilePath (Join-Path $installDir 'windhawk.exe') -ArgumentList '-exit' -WindowStyle Hidden -PassThru -ErrorAction SilentlyContinue
        if ($proc -and -not $proc.WaitForExit(20000)) { try { $proc.Kill() } catch { } }
        Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
        Start-Sleep -Seconds 2
    }

    Write-Host 'Running the installer (silent)...'
    $inst = Start-Process -FilePath $installerFile -ArgumentList '/S' -Wait -PassThru
    if ($inst.ExitCode -ne 0) { throw "installer exit code $($inst.ExitCode)" }
    Start-Sleep -Seconds 3

    $newDir = Get-InstallDir
    $now = $null
    if ($newDir) { $now = Get-InstalledVersion $newDir }
    if ($now -ne $targetTag) { throw "installer finished but the version is $now, expected $targetTag" }

    $svc = Get-Service -Name Windhawk -ErrorAction SilentlyContinue
    if ($svc -and $svc.Status -ne 'Running') { Start-Service -Name Windhawk -ErrorAction SilentlyContinue; Start-Sleep -Seconds 3 }
    if (-not (Get-Process -Name 'windhawk*' -ErrorAction SilentlyContinue)) {
        Start-Process -FilePath (Join-Path $newDir 'windhawk.exe') -ArgumentList '-tray-only' | Out-Null
        Start-Sleep -Seconds 2
    }

    Write-Host ''
    Write-Host "Windhawk $targetTag is installed." -ForegroundColor Green
    Write-Host 'Mods and their settings were kept.'
    Write-Host 'Programs that were open during the update keep the old engine code until they restart; a reboot clears that.'
} catch {
    Write-Host ''
    Write-Host ('FAILED: ' + $_.Exception.Message) -ForegroundColor Red
    Write-Host 'Nothing was installed or updated unless the message above says the installer already ran.'
    $exitCode = 1
}

if ($Pause) { Read-Host 'Press Enter to close' | Out-Null }
exit $exitCode
