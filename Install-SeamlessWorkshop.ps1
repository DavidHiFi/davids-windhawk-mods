<#
Installs Seamless Workshop, a Windhawk mod, from the latest GitHub release. One command does it all:

    irm https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/Install-SeamlessWorkshop.ps1 | iex

What it does:
  1. Finds Windhawk. If it is missing or older than the 2.0 alpha, it runs Update-Windhawk.ps1 from this repo first,
     which downloads the official Windhawk installer and checks its hash and signature.
  2. Downloads seamless-workshop.wh.cpp and its .sha256 file from the latest release.
  3. Throws the download away if it does not match its checksum.
  4. Skips the install if this version or a newer one is already installed.
  5. Installs the mod with "windhawk-cli mod install --file", asking for admin rights if needed.

Options when run as a file:
  -Check               do steps 1 to 4 and report, change nothing
  -SkipWindhawkUpdate  stop with a message instead of installing or updating Windhawk
  -Force               install even when the same version is already there
#>
[CmdletBinding()]
param(
    [string]$Repo = 'DavidHiFi/seamless-workshop',
    [string]$WindhawkDir,
    [switch]$Check,
    [switch]$SkipWindhawkUpdate,
    [switch]$Force
)

function Install-SeamlessWorkshop {
    param([string]$Repo, [string]$WindhawkDir, [bool]$Check, [bool]$SkipWindhawkUpdate, [bool]$Force)
    $ErrorActionPreference = 'Stop'
    $ProgressPreference = 'SilentlyContinue'
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
    $updaterRepo = 'https://github.com/DavidHiFi/seamless-workshop#installation'
    $updaterRaw = 'https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/Update-Windhawk.ps1'
    $isAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole(
        [Security.Principal.WindowsBuiltInRole]::Administrator)

    function Fail([string]$Message) {
        Write-Host ''
        Write-Host 'Seamless Workshop was not installed.' -ForegroundColor Red
        Write-Host $Message
        return $false
    }

    function Find-Windhawk {
        $dirs = @()
        if ($WindhawkDir) { $dirs += $WindhawkDir }
        $dirs += (Join-Path $env:ProgramFiles 'Windhawk')
        if (${env:ProgramFiles(x86)}) { $dirs += (Join-Path ${env:ProgramFiles(x86)} 'Windhawk') }
        $running = Get-Process windhawk -ErrorAction SilentlyContinue | Select-Object -First 1
        if ($running -and $running.Path) { $dirs += (Split-Path $running.Path -Parent) }
        $dir = $dirs | Where-Object { Test-Path -LiteralPath (Join-Path $_ 'windhawk.exe') } | Select-Object -First 1
        $info = [pscustomobject]@{ Dir = $dir; Cli = $null; Version = $null; Ok = $false; Why = '' }
        if (-not $dir) { $info.Why = 'Windhawk is not installed.'; return $info }
        $cli = Join-Path $dir 'windhawk-cli.exe'
        if (-not (Test-Path -LiteralPath $cli)) { $info.Why = 'This Windhawk is too old: it has no command-line tool.'; return $info }
        $info.Cli = $cli
        $m = [regex]::Match((& $cli --version 2>$null | Out-String), '(\d+)\.(\d+)\.(\d+)')
        if (-not $m.Success) { $info.Why = 'Could not read the Windhawk version.'; return $info }
        $info.Version = $m.Value
        if ([int]$m.Groups[1].Value -lt 2) { $info.Why = "Windhawk $($m.Value) is too old. Seamless Workshop needs the 2.0 alpha or newer."; return $info }
        $info.Ok = $true
        return $info
    }

    # 1. Windhawk, updated to the alpha when it is missing or too old
    $wh = Find-Windhawk
    if (-not $wh.Ok) {
        if ($Check -or $SkipWindhawkUpdate) {
            return (Fail "$($wh.Why) Get the latest alpha with $updaterRepo, then run this again.")
        }
        Write-Host "$($wh.Why) Getting the latest Windhawk alpha first."
        $updater = Join-Path $env:TEMP ('Update-Windhawk-' + [guid]::NewGuid().ToString('N').Substring(0, 8) + '.ps1')
        try {
            Invoke-WebRequest -UseBasicParsing $updaterRaw -OutFile $updater
            $updArgs = "-NoProfile -ExecutionPolicy Bypass -File `"$updater`""
            if ($isAdmin) {
                $p = Start-Process powershell.exe -ArgumentList $updArgs -Wait -PassThru
            } else {
                Write-Host 'Windows will ask for admin rights so Windhawk can be installed.'
                $p = Start-Process powershell.exe -ArgumentList $updArgs -Verb RunAs -Wait -PassThru
            }
        } catch {
            return (Fail "Could not run the Windhawk updater: $($_.Exception.Message). Try $updaterRepo by hand.")
        } finally {
            Remove-Item -LiteralPath $updater -Force -ErrorAction SilentlyContinue
        }
        $wh = Find-Windhawk
        if (-not $wh.Ok) {
            return (Fail "The Windhawk update did not finish ($($wh.Why)) Try $updaterRepo by hand, then run this again.")
        }
    }
    Write-Host "Found Windhawk $($wh.Version) in $($wh.Dir)"

    # 2. Download the mod and its checksum
    $base = "https://github.com/$Repo/releases/latest/download"
    $work = Join-Path $env:TEMP ('seamless-workshop-' + [guid]::NewGuid().ToString('N').Substring(0, 8))
    New-Item -ItemType Directory -Path $work -Force | Out-Null
    try {
        $file = Join-Path $work 'seamless-workshop.wh.cpp'
        $sumFile = Join-Path $work 'seamless-workshop.wh.cpp.sha256'
        try {
            Invoke-WebRequest -UseBasicParsing "$base/seamless-workshop.wh.cpp" -OutFile $file
            Invoke-WebRequest -UseBasicParsing "$base/seamless-workshop.wh.cpp.sha256" -OutFile $sumFile
        } catch {
            return (Fail "Could not download the latest release from https://github.com/$Repo/releases ($($_.Exception.Message))")
        }

        # 3. Check the checksum
        $want = ([regex]::Match((Get-Content -LiteralPath $sumFile -Raw), '[0-9a-fA-F]{64}')).Value
        $have = (Get-FileHash -LiteralPath $file -Algorithm SHA256).Hash
        if (-not $want -or $want -ne $have) {
            return (Fail 'The download does not match its checksum, so it was thrown away. Try again later, or install it by hand from the release page.')
        }
        $newVer = ([regex]::Match((Get-Content -LiteralPath $file -TotalCount 12 | Out-String), '@version\s+(\S+)')).Groups[1].Value
        Write-Host "Downloaded Seamless Workshop $newVer. The checksum matches."

        # 4. Already installed?
        $installed = Join-Path $env:ProgramData 'Windhawk\ModsSource\local@seamless-workshop.wh.cpp'
        $oldVer = ''
        if (Test-Path -LiteralPath $installed) {
            $oldVer = ([regex]::Match((Get-Content -LiteralPath $installed -TotalCount 12 | Out-String), '@version\s+(\S+)')).Groups[1].Value
        }
        $upToDate = $false
        if ($oldVer -and $newVer) {
            try { $upToDate = [version]$oldVer -ge [version]$newVer } catch { $upToDate = $oldVer -eq $newVer }
        }
        if ($upToDate -and -not $Force) {
            Write-Host ''
            Write-Host "Seamless Workshop $oldVer is already installed and up to date. Nothing to do." -ForegroundColor Green
            Write-Host 'It updates itself from now on. Click its tray icon to open it.'
            return $true
        }
        if ($Check) {
            Write-Host "Check only: would install $newVer$(if ($oldVer) { " over $oldVer" })."
            return $true
        }

        # 5. Install through the Windhawk command-line tool
        $cliArgs = "mod install --file `"$file`""
        try {
            if ($isAdmin) {
                $p = Start-Process -FilePath $wh.Cli -ArgumentList $cliArgs -WindowStyle Hidden -PassThru -Wait
            } else {
                Write-Host 'Windows will ask for admin rights so Windhawk can install the mod.'
                $p = Start-Process -FilePath $wh.Cli -ArgumentList $cliArgs -Verb RunAs -WindowStyle Hidden -PassThru -Wait
            }
        } catch {
            return (Fail "The install did not start: $($_.Exception.Message)")
        }
        if ($p.ExitCode -ne 0) {
            return (Fail "Windhawk could not install the mod (exit code $($p.ExitCode)). Open Windhawk and check that it is running, then try again.")
        }
    } finally {
        Remove-Item -LiteralPath $work -Recurse -Force -ErrorAction SilentlyContinue
    }

    Write-Host ''
    Write-Host "Seamless Workshop $newVer is installed." -ForegroundColor Green
    Write-Host 'Click its tray icon to open it. To get every DavidHiFi mod set up the way he runs them,'
    Write-Host "open Updates and choose Apply DavidHiFi's whole setup. It keeps itself and your mods up to date from there."
    return $true
}

$ok = Install-SeamlessWorkshop -Repo $Repo -WindhawkDir $WindhawkDir -Check:$Check -SkipWindhawkUpdate:$SkipWindhawkUpdate -Force:$Force
if ($PSCommandPath -and -not $ok) { exit 1 }
