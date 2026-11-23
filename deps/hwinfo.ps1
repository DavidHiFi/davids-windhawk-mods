<#
HWiNFO for the Seamless Taskbar stats: the newest beta from REALiX, the sensor feed on, and a
small job that keeps it running hidden from every sign-in.
Seamless Workshop runs this: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
status reads this PC only. check also asks hwinfo.com for the newest beta. Run as admin.
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto)
$ErrorActionPreference = 'Continue'; $ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
$task = 'Seamless HWiNFO'
$keepDir = Join-Path $env:ProgramData 'SeamlessWorkshop\deps'
$script:latest = ''

function Find-Exe {
    $p = Get-Process HWiNFO64 -ErrorAction SilentlyContinue | Where-Object { $_.Path } | Select-Object -First 1
    if ($p) { return $p.Path }
    $keys = 'HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\*', 'HKLM:\Software\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\*',
            'HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall\*'
    foreach ($u in (Get-ItemProperty $keys -ErrorAction SilentlyContinue | Where-Object { $_.DisplayName -like 'HWiNFO*64*' -and $_.InstallLocation })) {
        $f = Join-Path $u.InstallLocation 'HWiNFO64.EXE'
        if (Test-Path $f) { return $f }
    }
    $f = Join-Path $env:ProgramFiles 'HWiNFO64\HWiNFO64.EXE'
    if (Test-Path $f) { return $f }
    $null
}

# 8.61-6125 is shown as 8.61.6125 so the Workshop can compare it.
function Ver($f) {
    if (-not $f -or -not (Test-Path $f)) { return '' }
    $v = (Get-Item $f).VersionInfo
    "$($v.FileMajorPart).$($v.FileMinorPart).$($v.FileBuildPart)"
}

function Done([bool]$ok, [string]$message, [bool]$later = $false) {
    $exe = Find-Exe
    $j = [ordered]@{ ok = $ok; installed = [bool]$exe; version = (Ver $exe); latest = $script:latest; message = $message; later = $later } | ConvertTo-Json -Compress
    if ($Out) { [IO.File]::WriteAllText($Out, $j, (New-Object Text.UTF8Encoding($false))) } else { $j }
    exit 0
}

# hwinfo.com/ver.txt names the newest builds, beta included: HW64UPD:8.61-6125=<download>.
function Get-Latest {
    try {
        $t = (Invoke-WebRequest 'https://www.hwinfo.com/ver.txt' -UseBasicParsing -TimeoutSec 30).Content
        if ($t -is [byte[]]) { $t = [Text.Encoding]::ASCII.GetString($t) }
        $best = $null
        foreach ($m in [regex]::Matches($t, '(?m)^HW64UPD:(\d+)\.(\d+)-(\d+)=(\S+)')) {
            $url = $m.Groups[4].Value
            if ($url -notmatch '^https://(dl\.dappcdn\.com/hwinfo/|(www\.)?hwinfo\.com/)') { continue }
            $v = [version]"$($m.Groups[1].Value).$($m.Groups[2].Value).$($m.Groups[3].Value)"
            if (-not $best -or $v -gt $best.v) { $best = @{ v = $v; url = $url } }
        }
        if ($best) { $script:latest = $best.v.ToString() }
        $best
    } catch { $null }
}

function Test-Newer([string]$a, [string]$b) {
    if (-not $a) { return $false }
    if (-not $b) { return $true }
    try { [version]$a -gt [version]$b } catch { $false }
}

function Test-Feed {
    try {
        $m = [IO.MemoryMappedFiles.MemoryMappedFile]::OpenExisting('Global\HWiNFO_SENS_SM2', [IO.MemoryMappedFiles.MemoryMappedFileRights]::Read)
        $m.Dispose(); $true
    } catch { $false }
}

function Stop-HWiNFO {
    $was = [bool](Get-Process HWiNFO64 -ErrorAction SilentlyContinue)
    Get-Process HWiNFO64 -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
    for ($i = 0; $i -lt 10 -and (Get-Process HWiNFO64 -ErrorAction SilentlyContinue); $i++) { Start-Sleep 1 }
    $was
}

function Start-HWiNFO($exe) {
    if (Get-ScheduledTask -TaskName $task -ErrorAction SilentlyContinue) { Start-ScheduledTask -TaskName $task }
    else { Start-Process $exe -WindowStyle Minimized }
}

# Downloads the beta, checks REALiX signed it, then swaps the program file. The settings file stays.
function Install-Beta($best, $dir) {
    $tmp = Join-Path $env:TEMP ('seamless-hwinfo-' + [guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Force $tmp | Out-Null
    try {
        $pkg = Join-Path $tmp 'update.7z'
        Invoke-WebRequest $best.url -OutFile $pkg -UseBasicParsing -TimeoutSec 300
        $x = Join-Path $tmp 'x'; New-Item -ItemType Directory -Force $x | Out-Null
        & "$env:SystemRoot\System32\tar.exe" -xf $pkg -C $x 2>&1 | Out-Null
        $new = Get-ChildItem $x -Recurse -Filter 'HWiNFO64.exe' | Select-Object -First 1
        if (-not $new) { return 'The download from hwinfo.com had no program in it.' }
        $sig = Get-AuthenticodeSignature $new.FullName
        if ($sig.Status -ne 'Valid' -or $sig.SignerCertificate.Subject -notmatch 'REALiX') { return 'The download was not signed by REALiX, so it was not used.' }
        New-Item -ItemType Directory -Force $dir | Out-Null
        $exe = Join-Path $dir 'HWiNFO64.EXE'
        $was = Stop-HWiNFO
        if (Test-Path $exe) { Copy-Item $exe "$exe.old" -Force }
        Copy-Item $new.FullName $exe -Force
        if ((Ver $exe) -ne $best.v.ToString()) {
            if (Test-Path "$exe.old") { Copy-Item "$exe.old" $exe -Force }
            if ($was) { Start-HWiNFO $exe }
            return 'The new version did not go in. The old one is back.'
        }
        if ($was) { Start-HWiNFO $exe }
        ''
    } catch { "The download from hwinfo.com failed. $($_.Exception.Message)" }
    finally { Remove-Item $tmp -Recurse -Force -ErrorAction SilentlyContinue }
}

# Sensors only, started hidden, the feed the taskbar reads switched on, no update prompts of its
# own (the Workshop updates it). Other lines the user has are kept.
function Set-Ini($ini) {
    $want = [ordered]@{ OpenSystemSummary = 0; OpenSensors = 1; MinimalizeMainWnd = 1; MinimalizeSensors = 1; MinimalizeSensorsClose = 1
        ShowWelcomeAndProgress = 0; PersistentDriver = 1; Theme = 1; SnapshotPolling = 1; DisableBlockingWarning = 1; SensorsSM = 1
        AutoUpdate = 0; AutoUpdateBetaDisable = 0 }
    $old = @(); if (Test-Path $ini) { $old = @(Get-Content $ini) }
    $lines = $old
    if (-not ($lines -match '^\[Settings\]')) { $lines = @('[Settings]') + $lines }
    foreach ($k in $want.Keys) {
        $hit = $false
        $lines = @($lines | ForEach-Object { if ($_ -match "^$k=") { $hit = $true; "$k=$($want[$k])" } else { $_ } })
        if (-not $hit) {
            $i = [array]::IndexOf($lines, '[Settings]')
            $lines = @($lines[0..$i]) + "$k=$($want[$k])" + @($lines | Select-Object -Skip ($i + 1))
        }
    }
    if (($old -join "`n") -eq ($lines -join "`n")) { return }
    if (Test-Path $ini) { Copy-Item $ini "$ini.bak-$(Get-Date -Format yyyyMMdd-HHmm)" -Force }
    Set-Content $ini $lines -Encoding ascii
}

# The keeper starts HWiNFO when it is not running and restarts it when the feed went quiet
# (the free version turns the feed off after 12 hours).
function Set-Keeper($exe) {
    New-Item -ItemType Directory -Force $keepDir | Out-Null
    $body = @'
$exe = '__EXE__'
function FeedUp { try { $m = [IO.MemoryMappedFiles.MemoryMappedFile]::OpenExisting('Global\HWiNFO_SENS_SM2', [IO.MemoryMappedFiles.MemoryMappedFileRights]::Read); $m.Dispose(); $true } catch { $false } }
$p = Get-Process HWiNFO64 -ErrorAction SilentlyContinue | Select-Object -First 1
if ($p -and ((Get-Date) - $p.StartTime).TotalMinutes -lt 3) { exit }
if ($p -and (FeedUp) -and ((Get-Date) - $p.StartTime).TotalHours -lt 11) { exit }
if ($p) { $p | Stop-Process -Force; Start-Sleep 3 }
if (Test-Path $exe) { Start-Process $exe -WindowStyle Minimized }
'@
    $body.Replace('__EXE__', $exe.Replace("'", "''")) | Set-Content "$keepDir\hwinfo-keep.ps1" -Encoding ascii
    ('CreateObject("WScript.Shell").Run "powershell -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File ""' + "$keepDir\hwinfo-keep.ps1" + '""", 0, False') |
        Set-Content "$keepDir\hwinfo-keep.vbs" -Encoding ascii
    $user = (Get-CimInstance Win32_ComputerSystem).UserName
    if (-not $user) { $user = "$env:USERDOMAIN\$env:USERNAME" }
    $a = New-ScheduledTaskAction -Execute 'wscript.exe' -Argument "`"$keepDir\hwinfo-keep.vbs`""
    $t1 = New-ScheduledTaskTrigger -AtLogOn -User $user
    $t2 = New-ScheduledTaskTrigger -Once -At (Get-Date).Date -RepetitionInterval (New-TimeSpan -Minutes 30)
    $p = New-ScheduledTaskPrincipal -UserId $user -LogonType Interactive -RunLevel Highest
    $s = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -ExecutionTimeLimit (New-TimeSpan -Minutes 5)
    Register-ScheduledTask -TaskName $task -Action $a -Trigger $t1, $t2 -Principal $p -Settings $s -Force | Out-Null
}

$exe = Find-Exe
switch ($Mode) {
    'status' { Done $true '' }
    'check' { $null = Get-Latest; Done $true '' }
    'update' {
        if (-not $exe) { Done $false 'HWiNFO is not installed.' }
        $best = Get-Latest
        if (-not $best) { Done $false 'Could not reach hwinfo.com. The Workshop tries again later.' }
        if (-not (Test-Newer $best.v.ToString() (Ver $exe))) { Done $true '' }
        $err = Install-Beta $best (Split-Path $exe)
        if ($err) { Done $false $err }
        Done $true "HWiNFO $($best.v) is in. Your settings stayed."
    }
    'install' {
        $best = Get-Latest
        if (-not $exe -and (Get-Command winget -ErrorAction SilentlyContinue)) {
            winget install -e --id REALiX.HWiNFO --silent --accept-package-agreements --accept-source-agreements --disable-interactivity 2>&1 | Out-Null
            $exe = Find-Exe
        }
        # No package manager: the program file alone runs fine from its own folder.
        if (-not $exe -and $best) {
            $err = Install-Beta $best (Join-Path $env:ProgramFiles 'HWiNFO64')
            if ($err) { Done $false $err }
            $exe = Find-Exe
        }
        if (-not $exe) { Done $false 'HWiNFO did not install. Check the internet connection and try again.' }
        if ($best -and (Test-Newer $best.v.ToString() (Ver $exe))) { $null = Install-Beta $best (Split-Path $exe) }
        $null = Stop-HWiNFO
        Set-Ini (Join-Path (Split-Path $exe) 'HWiNFO64.INI')
        Set-Keeper $exe
        Start-HWiNFO $exe
        $ok = $false
        for ($i = 0; $i -lt 20 -and -not $ok; $i++) { Start-Sleep 3; $ok = Test-Feed }
        if ($ok) { Done $true "HWiNFO $(Ver $exe) is running with the sensor feed on." }
        if (Get-Process HWiNFO64 -ErrorAction SilentlyContinue) { Done $true "HWiNFO $(Ver $exe) is running. The taskbar stats appear within a minute." }
        Done $false 'HWiNFO is installed but did not start.'
    }
    'remove' {
        Unregister-ScheduledTask -TaskName $task -Confirm:$false -ErrorAction SilentlyContinue
        Remove-Item "$keepDir\hwinfo-keep.*" -Force -ErrorAction SilentlyContinue
        $null = Stop-HWiNFO
        if ($exe) {
            $dir = Split-Path $exe
            $un = Join-Path $dir 'unins000.exe'
            if (Test-Path $un) { Start-Process $un -ArgumentList '/VERYSILENT', '/SUPPRESSMSGBOXES', '/NORESTART' -Wait -WindowStyle Hidden }
            else { Remove-Item $dir -Recurse -Force -ErrorAction SilentlyContinue }
        }
        if (Find-Exe) { Done $false 'HWiNFO could not be removed. Close it and try again.' }
        Done $true 'HWiNFO is removed.'
    }
}
