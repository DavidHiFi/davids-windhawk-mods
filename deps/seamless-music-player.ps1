<#
Seamless Music Player, DavidHiFi's Windows music player: installs or updates it from his GitHub releases.
Seamless Workshop runs this: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
status reads this PC only. check also asks GitHub for the newest release. Needs no admin rights.
It is portable: the zip unpacks into the user's programs folder, no setup program.
It never closes the player: while it is open, an update waits. Removing keeps the music library and settings.
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto,
      [string]$LocalZip, [string]$LocalVersion, [string]$InstallRoot, [switch]$NoShortcut, [switch]$NoStart)
$ErrorActionPreference = 'Continue'; $ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
$appName = 'Seamless Music Player'
$exeName = 'Seamless Music Player.exe'
$regName = 'SeamlessMusicPlayer'
if ($InstallRoot) { $regName = 'SeamlessMusicPlayer-Test' }
$script:latest = ''

function Install-Dir {
    if ($InstallRoot) { return $InstallRoot }
    Join-Path ([Environment]::GetFolderPath('LocalApplicationData')) 'Programs\Seamless Music Player'
}

function Shortcut-Path {
    Join-Path ([Environment]::GetFolderPath('StartMenu')) 'Programs\Seamless Music Player.lnk'
}

function Find-App {
    $u = Get-ItemProperty ('HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall\' + $regName) -ErrorAction SilentlyContinue
    if ($u -and $u.InstallLocation -and (Test-Path (Join-Path $u.InstallLocation $exeName))) {
        $v = [string]$u.DisplayVersion
        if ($v -notmatch '^\d+(\.\d+)*$') { $v = '' }
        return @{ dir = $u.InstallLocation.TrimEnd('\'); version = $v }
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
        $r = Invoke-RestMethod 'https://api.github.com/repos/DavidHiFi/seamless-music-player/releases/latest' -UseBasicParsing -TimeoutSec 30
        $v = ([string]$r.tag_name).TrimStart('v')
        if ($v -notmatch '^\d+(\.\d+)*$') { return $null }
        $zip = $r.assets | Where-Object { $_.name -eq "SeamlessMusicPlayer-$v-win64.zip" } | Select-Object -First 1
        $sums = $r.assets | Where-Object { $_.name -eq 'SHA256SUMS' } | Select-Object -First 1
        if (-not $zip -or -not $sums) { return $null }
        $script:latest = $v
        @{ v = $v; name = $zip.name; url = $zip.browser_download_url; sums = $sums.browser_download_url }
    } catch { $null }
}

function Get-Release {
    if ($LocalZip) {
        if (-not (Test-Path $LocalZip)) { return $null }
        $v = $LocalVersion; if (-not $v) { $v = '0.0.0' }
        @{ v = $v; name = [IO.Path]::GetFileName($LocalZip); local = $true }
    } else { Get-Latest }
}

function Test-Newer([string]$a, [string]$b) {
    if (-not $a) { return $false }
    if (-not $b) { return $true }
    try { [version]$a -gt [version]$b } catch { $false }
}

# The player is open.
function Test-Open { [bool](Get-Process $appName -ErrorAction SilentlyContinue) }

# Checks a file against a SHA256SUMS listing. Returns '' when it matches, otherwise why not.
function Test-Sums([string]$sums, [string]$name, [string]$file, [bool]$local) {
    $want = ''
    foreach ($line in ($sums -split "`n")) { if ($line -match '^([0-9a-fA-F]{64})\s+\*?(\S+)\s*$' -and $Matches[2] -eq $name) { $want = $Matches[1].ToLower() } }
    $have = (Get-FileHash $file -Algorithm SHA256).Hash.ToLower()
    if (-not $want -or $want -ne $have) {
        if ($local) { return 'The zip did not match the checksum beside it, so it was not used.' }
        return 'The download did not match the checksum DavidHiFi published, so it was not used.'
    }
    ''
}

# Unpacks the zip into the user's programs folder, after checking it against the checksum list.
function Install-Release($best) {
    $tmp = Join-Path ([IO.Path]::GetTempPath()) ('seamless-music-player-' + [guid]::NewGuid().ToString('N'))
    $null = New-Item -ItemType Directory -Force $tmp
    try {
        $zip = Join-Path $tmp $best.name
        if ($best.local) {
            $sumsFile = Join-Path (Split-Path $LocalZip -Parent) 'SHA256SUMS'
            if (-not (Test-Path $sumsFile)) { return 'No SHA256SUMS beside the zip, so it was not used.' }
            $err = Test-Sums (Get-Content $sumsFile -Raw) $best.name $LocalZip $true
            if ($err) { return $err }
            Copy-Item $LocalZip $zip
        } else {
            if ($best.url -notlike 'https://github.com/DavidHiFi/seamless-music-player/releases/download/*') { return 'The download was not from DavidHiFi.' }
            Invoke-WebRequest $best.url -OutFile $zip -UseBasicParsing -TimeoutSec 600
            $sums = (Invoke-WebRequest $best.sums -UseBasicParsing -TimeoutSec 60).Content
            if ($sums -is [byte[]]) { $sums = [Text.Encoding]::ASCII.GetString($sums) }
            $err = Test-Sums $sums $best.name $zip $false
            if ($err) { return $err }
        }
        $stage = Join-Path $tmp 'stage'
        Expand-Archive $zip $stage -Force
        $exe = Join-Path $stage $exeName
        if (-not (Test-Path $exe)) {
            $sub = Get-ChildItem $stage -Directory | Select-Object -First 1
            if ($sub -and (Test-Path (Join-Path $sub.FullName $exeName))) { $stage = $sub.FullName }
        }
        if (-not (Test-Path (Join-Path $stage $exeName))) { return 'The zip did not hold the player.' }
        $dest = Install-Dir
        if (-not (Test-Path $dest)) { $null = New-Item -ItemType Directory -Force $dest }
        Copy-Item (Join-Path $stage '*') $dest -Recurse -Force
        Write-Uninstall $dest
        if (-not $NoShortcut) { Write-Shortcut $dest }
        Write-UninstallKey $dest $best.v
        ''
    } catch {
        if ($LocalZip) { "The install failed. $($_.Exception.Message)" } else { "The download from GitHub failed. $($_.Exception.Message)" }
    }
    finally { Remove-Item $tmp -Recurse -Force -ErrorAction SilentlyContinue }
}

# Writes the small uninstaller the Windows uninstall entry points at. Same job as -Mode remove.
function Write-Uninstall([string]$dir) {
    $tmpl = @'
$ErrorActionPreference = 'Continue'
$dir = '<DIR>'
$key = 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall\<KEY>'
if (Get-Process 'Seamless Music Player' -ErrorAction SilentlyContinue) { exit 1 }
if (-not '<KEY>'.EndsWith('-Test')) {
    $lnk = Join-Path ([Environment]::GetFolderPath('StartMenu')) 'Programs\Seamless Music Player.lnk'
    if (Test-Path $lnk) { Remove-Item $lnk -Force -ErrorAction SilentlyContinue }
}
if (Test-Path $key) { Remove-Item $key -Recurse -Force -ErrorAction SilentlyContinue }
if (Test-Path $dir) { Get-ChildItem $dir -Exclude 'uninstall.ps1' | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue }
Start-Process cmd.exe -ArgumentList '/c', ('timeout /t 2 /nobreak >nul & rd /s /q "{0}"' -f $dir) -WindowStyle Hidden
exit 0
'@
    [IO.File]::WriteAllText((Join-Path $dir 'uninstall.ps1'), $tmpl.Replace('<DIR>', $dir).Replace('<KEY>', $regName), (New-Object Text.UTF8Encoding($false)))
}

function Write-Shortcut([string]$dir) {
    $sp = Shortcut-Path
    $w = New-Object -ComObject WScript.Shell
    $s = $w.CreateShortcut($sp)
    $s.TargetPath = Join-Path $dir $exeName
    $s.WorkingDirectory = $dir
    $s.Save()
}

function Write-UninstallKey([string]$dir, [string]$v) {
    $key = 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall\' + $regName
    $null = New-Item -Path $key -Force
    $size = 0
    Get-ChildItem $dir -Recurse -File -ErrorAction SilentlyContinue | ForEach-Object { $size += $_.Length }
    $kb = [int][math]::Round($size / 1KB)
    Set-ItemProperty $key DisplayName $appName
    Set-ItemProperty $key DisplayVersion $v
    Set-ItemProperty $key Publisher 'DavidHiFi'
    Set-ItemProperty $key InstallLocation $dir
    Set-ItemProperty $key DisplayIcon (Join-Path $dir $exeName)
    Set-ItemProperty $key UninstallString ("powershell -NoProfile -WindowStyle Hidden -ExecutionPolicy Bypass -File `"$dir\uninstall.ps1`"")
    Set-ItemProperty $key NoModify -Type DWord 1
    Set-ItemProperty $key NoRepair -Type DWord 1
    Set-ItemProperty $key EstimatedSize -Type DWord $kb
}

# Starts it through Explorer, so it never runs with admin rights.
function Start-App($a) {
    Start-Process explorer.exe -ArgumentList "`"$(Join-Path $a.dir $exeName)`""
}

function Remove-App($a) {
    if (-not $InstallRoot -and (Test-Path (Shortcut-Path))) { Remove-Item (Shortcut-Path) -Force -ErrorAction SilentlyContinue }
    Remove-Item ('HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall\' + $regName) -Recurse -Force -ErrorAction SilentlyContinue
    if ($a.dir -and (Test-Path $a.dir)) { Remove-Item $a.dir -Recurse -Force -ErrorAction SilentlyContinue }
}

$a = Find-App
switch ($Mode) {
    'status' { Done $true '' }
    'check' { $null = Get-Release; Done $true '' }
    { $_ -in 'install', 'update' } {
        $best = Get-Release
        if (-not $best) {
            if ($LocalZip) { Done $false 'The test zip was not found.' }
            Done $false 'Could not reach GitHub. The Workshop tries again later.'
        }
        if ($a -and -not (Test-Newer $best.v $a.version)) { Done $true '' }
        if (Test-Open) {
            if ($Auto) { Done $false "Goes in when $appName is closed." $true }
            Done $false "Close $appName first, then click again."
        }
        $fresh = -not $a
        $err = Install-Release $best
        if ($err) { Done $false $err }
        $a = Find-App
        if (-not $a -or (Test-Newer $best.v $a.version)) { Done $false 'The new version did not go in.' }
        if ($fresh -and -not $NoStart) { Start-App $a; Done $true "$appName $($a.version) is installed and running." }
        if ($fresh) { Done $true "$appName $($a.version) is installed." }
        Done $true "$appName $($a.version) is in. Your library and settings stayed."
    }
    'remove' {
        if (-not $a) { Done $true "$appName is not on this PC." }
        if (Test-Open) { Done $false "Close $appName first, then click again." }
        Remove-App $a
        if (Find-App) { Done $false "$appName could not be removed." }
        Done $true "$appName is removed. Your music library and settings were kept."
    }
}
