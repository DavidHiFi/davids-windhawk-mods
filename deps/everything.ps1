<#
Everything (the newest 1.5 beta from voidtools) for the mods that size and search folders with it,
set up the way DavidHiFi has it: every fixed drive indexed, folder sizes on, no tray icon, running
in the background from every sign-in.
Seamless Workshop runs this: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
status reads this PC only. check also asks voidtools.com for the newest beta. Run as admin.
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto)
$ErrorActionPreference = 'Continue'; $ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
$task = 'Seamless Everything'
# His settings file, and its fingerprint: a copy that does not match is not used.
$iniUrl = 'https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/deps/everything.ini'
$iniSha = '1594d2a9fe99cc9940b326bc6ae148692e315cc4c9f73d28439adc259ad7dd46'
$keys = 'HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\*', 'HKLM:\Software\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\*',
        'HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall\*'
$script:latest = ''

function Find-Exe {
    $p = Get-Process Everything -ErrorAction SilentlyContinue | Where-Object { $_.Path } | Select-Object -First 1
    if ($p) { return $p.Path }
    foreach ($u in (Get-ItemProperty $keys -ErrorAction SilentlyContinue | Where-Object { $_.DisplayName -like 'Everything*' -and $_.InstallLocation })) {
        $f = Join-Path $u.InstallLocation 'Everything.exe'
        if (Test-Path $f) { return $f }
    }
    $f = Join-Path $env:ProgramFiles 'Everything\Everything.exe'
    if (Test-Path $f) { return $f }
    $null
}

function Ver($f) {
    if (-not $f -or -not (Test-Path $f)) { return '' }
    $v = (Get-Item $f).VersionInfo
    "$($v.FileMajorPart).$($v.FileMinorPart).$($v.FileBuildPart).$($v.FilePrivatePart)"
}

function Done([bool]$ok, [string]$message, [bool]$later = $false) {
    $exe = Find-Exe
    $j = [ordered]@{ ok = $ok; installed = [bool]$exe; version = (Ver $exe); latest = $script:latest; message = $message; later = $later } | ConvertTo-Json -Compress
    if ($Out) { [IO.File]::WriteAllText($Out, $j, (New-Object Text.UTF8Encoding($false))) } else { $j }
    exit 0
}

# The beta page names the newest setup file: Everything-1.5.0.1424b.x64-Setup.exe.
function Get-Latest {
    try {
        $page = (Invoke-WebRequest 'https://www.voidtools.com/everything-1.5a/' -UseBasicParsing -TimeoutSec 30).Content
        $m = [regex]::Matches($page, 'Everything-1\.5\.0\.(\d+)[ab]\.x64-Setup\.exe') | Sort-Object { [int]$_.Groups[1].Value } -Descending | Select-Object -First 1
        if (-not $m) { return $null }
        $script:latest = "1.5.0.$($m.Groups[1].Value)"
        @{ v = $script:latest; file = $m.Value }
    } catch { $null }
}

function Test-Newer([string]$a, [string]$b) {
    if (-not $a) { return $false }
    if (-not $b) { return $true }
    try { [version]$a -gt [version]$b } catch { $false }
}

# The signed-in user, also when an admin account gave the rights.
function Get-User {
    $user = (Get-CimInstance Win32_ComputerSystem).UserName
    if (-not $user) { $user = "$env:USERDOMAIN\$env:USERNAME" }
    $sid = $null
    try { $sid = (New-Object Security.Principal.NTAccount($user)).Translate([Security.Principal.SecurityIdentifier]).Value } catch {}
    $appdata = $null
    if ($sid) { $appdata = (Get-ItemProperty "Registry::HKEY_USERS\$sid\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" -ErrorAction SilentlyContinue).AppData }
    if (-not $appdata) { $appdata = $env:APPDATA }
    @{ name = $user; sid = $sid; appdata = $appdata }
}

function Stop-Everything {
    $was = [bool](Get-Process Everything -ErrorAction SilentlyContinue | Where-Object { $_.SessionId -ne 0 })
    Get-Process Everything -ErrorAction SilentlyContinue | Where-Object { $_.SessionId -ne 0 } | Stop-Process -Force -ErrorAction SilentlyContinue
    for ($i = 0; $i -lt 10 -and (Get-Process Everything -ErrorAction SilentlyContinue | Where-Object { $_.SessionId -ne 0 }); $i++) { Start-Sleep 1 }
    $was
}

# Startup through the Workshop's job only, so there is one copy and it runs without admin rights.
function Clear-RunEntries($u) {
    $runs = @('HKLM:\Software\Microsoft\Windows\CurrentVersion\Run')
    if ($u.sid) { $runs += "Registry::HKEY_USERS\$($u.sid)\Software\Microsoft\Windows\CurrentVersion\Run" }
    foreach ($run in $runs) {
        $props = (Get-ItemProperty $run -ErrorAction SilentlyContinue).PSObject.Properties | Where-Object { $_.Name -like 'Everything*' }
        foreach ($p in $props) { Remove-ItemProperty $run -Name $p.Name -ErrorAction SilentlyContinue }
    }
}

# Downloads the setup from voidtools, checks voidtools signed it, and runs it quietly.
function Install-Setup($best, $dir) {
    $tmp = Join-Path $env:TEMP ('seamless-everything-' + [guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Force $tmp | Out-Null
    try {
        $setup = Join-Path $tmp $best.file
        Invoke-WebRequest "https://www.voidtools.com/$($best.file)" -OutFile $setup -UseBasicParsing -TimeoutSec 300
        $sig = Get-AuthenticodeSignature $setup
        if ($sig.Status -ne 'Valid' -or $sig.SignerCertificate.Subject -notmatch 'voidtools') { return 'The download was not signed by voidtools, so it was not used.' }
        Start-Process $setup -ArgumentList '/S', "/D=$dir" -Wait -WindowStyle Hidden
        ''
    } catch { "The download from voidtools.com failed. $($_.Exception.Message)" }
    finally { Remove-Item $tmp -Recurse -Force -ErrorAction SilentlyContinue }
}

function Start-Everything($exe) {
    if (Get-ScheduledTask -TaskName $task -ErrorAction SilentlyContinue) { Start-ScheduledTask -TaskName $task }
    else { Start-Process explorer.exe -ArgumentList "`"$exe`"" }
}

$exe = Find-Exe
switch ($Mode) {
    'status' { Done $true '' }
    'check' { $null = Get-Latest; Done $true '' }
    'update' {
        if (-not $exe) { Done $false 'Everything is not installed.' }
        $best = Get-Latest
        if (-not $best) { Done $false 'Could not reach voidtools.com. The Workshop tries again later.' }
        if (-not (Test-Newer $best.v (Ver $exe))) { Done $true '' }
        $dir = Split-Path $exe
        # The setup may write its own files over these. They hold how this copy runs, so they come back.
        $keep = @{}
        foreach ($n in 'Everything.ini', 'no_alpha_instance') { $f = Join-Path $dir $n; if (Test-Path $f) { $keep[$n] = [IO.File]::ReadAllBytes($f) } }
        $was = Stop-Everything
        $err = Install-Setup $best $dir
        $null = Stop-Everything
        foreach ($n in $keep.Keys) { [IO.File]::WriteAllBytes((Join-Path $dir $n), $keep[$n]) }
        Clear-RunEntries (Get-User)
        if ($was) { Start-Everything $exe }
        if ($err) { Done $false $err }
        if (Test-Newer $best.v (Ver $exe)) { Done $false 'The new version did not go in.' }
        Done $true "Everything $($best.v) is in. Your settings stayed."
    }
    'install' {
        $u = Get-User
        $best = Get-Latest
        $dir = if ($exe) { Split-Path $exe } else { Join-Path $env:ProgramFiles 'Everything' }
        if (-not $exe -or ($best -and (Test-Newer $best.v (Ver $exe)))) {
            $null = Stop-Everything
            $err = if ($best) { Install-Setup $best $dir } else { 'Could not reach voidtools.com.' }
            $exe = Find-Exe
            if (-not $exe -and (Get-Command winget -ErrorAction SilentlyContinue)) {
                winget install -e --id voidtools.Everything.Beta --silent --accept-package-agreements --accept-source-agreements --disable-interactivity 2>&1 | Out-Null
                $exe = Find-Exe
            }
            if (-not $exe) { Done $false "Everything did not install. $err" }
            $dir = Split-Path $exe
        }
        $null = Stop-Everything
        Start-Sleep 1

        # One plain copy that keeps its settings in the user's own folder, with his settings in it.
        Set-Content (Join-Path $dir 'no_alpha_instance') '' -NoNewline -ErrorAction SilentlyContinue
        $appIni = Join-Path $dir 'Everything.ini'
        if (-not (Test-Path $appIni) -or -not (Select-String -Path $appIni -Pattern '^app_data=1' -Quiet)) {
            Set-Content $appIni "[Everything]`r`napp_data=1`r`nrun_as_admin=0`r`nallow_ipc=1" -Encoding ascii
        }
        $note = ''
        $cfgDir = Join-Path $u.appdata 'Everything'
        New-Item -ItemType Directory -Force $cfgDir | Out-Null
        $cfg = Join-Path $cfgDir 'Everything.ini'
        try {
            $raw = (Invoke-WebRequest $iniUrl -UseBasicParsing -TimeoutSec 60).RawContentStream.ToArray()
            $sha = [BitConverter]::ToString([Security.Cryptography.SHA256]::Create().ComputeHash($raw)).Replace('-', '').ToLower()
            if ($sha -ne $iniSha) { $note = ' His search settings did not match, so the ones you had stayed.' }
            else {
                if (Test-Path $cfg) { Copy-Item $cfg "$cfg.bak-$(Get-Date -Format yyyyMMdd-HHmm)" -Force }
                [IO.File]::WriteAllBytes($cfg, $raw)
            }
        } catch { $note = ' His search settings could not be downloaded, so the ones you had stayed.' }

        # The service reads the drives so Everything never needs admin rights to stay current.
        if (-not (Get-Service Everything -ErrorAction SilentlyContinue)) { Start-Process $exe -ArgumentList '-install-service' -Wait -WindowStyle Hidden }
        Set-Service Everything -StartupType Automatic -ErrorAction SilentlyContinue
        Start-Service Everything -ErrorAction SilentlyContinue
        Clear-RunEntries $u
        $a = New-ScheduledTaskAction -Execute $exe -Argument '-startup'
        $t = New-ScheduledTaskTrigger -AtLogOn -User $u.name
        $p = New-ScheduledTaskPrincipal -UserId $u.name -LogonType Interactive -RunLevel Limited
        $s = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -ExecutionTimeLimit ([TimeSpan]::Zero)
        Register-ScheduledTask -TaskName $task -Action $a -Trigger $t -Principal $p -Settings $s -Force | Out-Null
        Start-ScheduledTask -TaskName $task
        $up = $false
        for ($i = 0; $i -lt 10 -and -not $up; $i++) { Start-Sleep 2; $up = [bool](Get-Process Everything -ErrorAction SilentlyContinue | Where-Object { $_.SessionId -ne 0 }) }
        if (-not $up) { Done $false "Everything $(Ver $exe) is installed but did not start.$note" }
        Done $true "Everything $(Ver $exe) is running in the background.$note"
    }
    'remove' {
        Unregister-ScheduledTask -TaskName $task -Confirm:$false -ErrorAction SilentlyContinue
        if (-not $exe) { Done $true 'Everything is not on this PC.' }
        $dir = Split-Path $exe
        $null = Stop-Everything
        if (Get-Service Everything -ErrorAction SilentlyContinue) { Start-Process $exe -ArgumentList '-uninstall-service' -Wait -WindowStyle Hidden }
        # The service copy can take a few seconds to go after -uninstall-service returns, and the
        # program file stays locked until it has.
        for ($i = 0; $i -lt 15 -and ((Get-Process Everything -ErrorAction SilentlyContinue) -or (Get-Service Everything -ErrorAction SilentlyContinue)); $i++) {
            Get-Process Everything -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
            Start-Sleep 1
        }
        Clear-RunEntries (Get-User)
        # Its setup has no quiet uninstall, so the same steps by hand: menu shortcuts, the entry in
        # Installed apps, the program folder. The user's own settings and search history stay.
        $sh = New-Object -ComObject WScript.Shell
        foreach ($menu in "$env:ProgramData\Microsoft\Windows\Start Menu\Programs", "$env:APPDATA\Microsoft\Windows\Start Menu\Programs") {
            Get-ChildItem $menu -Filter 'Everything*.lnk' -ErrorAction SilentlyContinue | Where-Object { $sh.CreateShortcut($_.FullName).TargetPath -like "$dir\*" } |
                Remove-Item -Force -ErrorAction SilentlyContinue
        }
        Get-ChildItem ($keys -replace '\\\*$', '') -ErrorAction SilentlyContinue | Where-Object {
            $p = Get-ItemProperty $_.PSPath -ErrorAction SilentlyContinue
            $p.DisplayName -like 'Everything*' -and $p.InstallLocation -and ($p.InstallLocation.TrimEnd('\') -eq $dir.TrimEnd('\'))
        } | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
        for ($i = 0; $i -lt 5 -and (Test-Path $dir); $i++) {
            Remove-Item $dir -Recurse -Force -ErrorAction SilentlyContinue
            if (Test-Path $dir) { Start-Sleep 2 }
        }
        if (Test-Path $exe) { Done $false 'Everything could not be removed. Close it and try again.' }
        Done $true 'Everything is removed. Your search settings were kept.'
    }
}
