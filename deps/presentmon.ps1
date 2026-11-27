<#
Intel PresentMon 2.6.0, standalone console tool used by Seamless FPS Overlay.
Workshop calls: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
The signed executable is installed under Program Files and launched only while frame latency is enabled.
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto)
$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12

$script:version = '2.6.0'
$script:url = 'https://github.com/GameTechDev/PresentMon/releases/download/v2.6.0/PresentMon-2.6.0-x64.exe'
$script:sha256 = 'b2a706bc6ad475749e3b7e3409263aa1e6906d45bdcf993f6dbc0f660188f1af'
$base = [Microsoft.Win32.RegistryKey]::OpenBaseKey([Microsoft.Win32.RegistryHive]::LocalMachine, [Microsoft.Win32.RegistryView]::Registry64)
$versionKey = $null
try {
    $versionKey = $base.OpenSubKey('SOFTWARE\Microsoft\Windows\CurrentVersion')
    if (-not $versionKey) { throw 'The Windows Program Files folder could not be found.' }
    $programFiles = [string]$versionKey.GetValue('ProgramFilesDir')
} finally {
    if ($versionKey) { $versionKey.Dispose() }
    $base.Dispose()
}
if (-not $programFiles) { throw 'The Windows Program Files folder could not be found.' }
$script:dir = Join-Path $programFiles 'DavidHiFi\PresentMon'
$script:file = Join-Path $script:dir 'PresentMon-2.6.0-x64.exe'
$script:latest = $script:version

function Test-Installed {
    if (-not (Test-Path -LiteralPath $script:file)) { return $false }
    $hash = (Get-FileHash -LiteralPath $script:file -Algorithm SHA256).Hash.ToLowerInvariant()
    $sig = Get-AuthenticodeSignature -LiteralPath $script:file
    return ($hash -eq $script:sha256 -and $sig.Status -eq 'Valid' -and
            $sig.SignerCertificate.Subject -match 'O=Intel Corporation')
}

function Done([bool]$ok, [string]$message = '') {
    $installed = Test-Installed
    $j = [ordered]@{ ok = $ok; installed = $installed; version = $(if ($installed) { $script:version } else { '' }); latest = $script:latest; message = $message; later = $false } | ConvertTo-Json -Compress
    if ($Out) { [IO.File]::WriteAllText($Out, $j, (New-Object Text.UTF8Encoding($false))) } else { $j }
    exit 0
}

function Install-PresentMon {
    $download = Join-Path $script:dir ('PresentMon-' + [guid]::NewGuid().ToString('N') + '.download.exe')
    try {
        New-Item -ItemType Directory -Path $script:dir -Force | Out-Null
        Invoke-WebRequest -Uri $script:url -OutFile $download -UseBasicParsing -TimeoutSec 300
        $hash = (Get-FileHash -LiteralPath $download -Algorithm SHA256).Hash.ToLowerInvariant()
        if ($hash -ne $script:sha256) { return 'The PresentMon download did not match Intel''s published file.' }
        $sig = Get-AuthenticodeSignature -LiteralPath $download
        if ($sig.Status -ne 'Valid' -or $sig.SignerCertificate.Subject -notmatch 'O=Intel Corporation') {
            return 'The PresentMon download was not signed by Intel, so it was not installed.'
        }
        Move-Item -LiteralPath $download -Destination $script:file -Force
        if (-not (Test-Installed)) { return 'PresentMon did not pass its signature and hash check after install.' }
        return ''
    } catch {
        return "PresentMon could not be downloaded. $($_.Exception.Message)"
    } finally {
        Remove-Item -LiteralPath $download -Force -ErrorAction SilentlyContinue
    }
}

switch ($Mode) {
    'status' {
        if (Test-Installed) { Done $true 'PresentMon is installed and its signature checks out.' }
        if (Test-Path -LiteralPath $script:file) { Done $false 'The PresentMon file failed its signature or hash check.' }
        Done $true 'PresentMon is not installed.'
    }
    'check' { Done $true '' }
    'install' {
        if (Test-Installed) { Done $true 'PresentMon 2.6.0 is already installed.' }
        $err = Install-PresentMon
        if ($err) { Done $false $err }
        Done $true 'PresentMon 2.6.0 is installed.'
    }
    'update' {
        if (Test-Installed) { Done $true 'PresentMon 2.6.0 is current.' }
        $err = Install-PresentMon
        if ($err) { Done $false $err }
        Done $true 'PresentMon 2.6.0 is installed.'
    }
    'remove' {
        if (Test-Path -LiteralPath $script:file) { Remove-Item -LiteralPath $script:file -Force }
        if (Test-Path -LiteralPath $script:file) { Done $false 'PresentMon could not be removed.' }
        Done $true 'PresentMon is removed.'
    }
}
