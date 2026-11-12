# Seamless Sound Manager: install the Windhawk port, retire the Sound Manager app, or roll back.
# Run ELEVATED (Invoke-Elevated.ps1). -Audit only reads.
#   -Audit      the mod, the app's task and process, and the file types
#   -Install    back up the app's task and file types, install the mod, restart its helper,
#               then turn the app's task off and stop the app (the app stays installed)
#   -Rollback   remove the mod, put the file types back, turn the app's task on and start it
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$id = 'local@seamless-sound-manager'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$work = 'H:\Windhawk Configuration\work\2026-11-11-sound-manager'
$built = "$work\build\seamless-sound-manager.wh.cpp"
$base = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$task = '\SoundManager-S-1-5-21-2602432160-4233293278-3745949008-1001'
$backup = 'H:\Windhawk Configuration\backups\2026-11-12\sound-manager'
$receipt = 'H:\Windhawk Configuration\reports\2026-11-11-seamless-sound-manager-receipt.json'
$classes = @('.ths', '.soundpack', 'ths_auto_file', 'soundpack_auto_file')

function Invoke-Hidden([string]$Exe, [string]$ArgLine, [int]$Seconds = 30) {
    $out = [IO.Path]::GetTempFileName(); $err = [IO.Path]::GetTempFileName()
    $p = Start-Process $Exe -ArgumentList $ArgLine -WindowStyle Hidden -PassThru -RedirectStandardOutput $out -RedirectStandardError $err
    $null = $p.Handle
    if (-not $p.WaitForExit($Seconds * 1000)) { $p.Kill(); Write-Host "TIMEOUT: $Exe $ArgLine"; return 124 }
    Get-Content $out, $err -ErrorAction SilentlyContinue | Where-Object { $_ } | ForEach-Object { Write-Host "  $_" }
    Remove-Item $out, $err -ErrorAction SilentlyContinue
    return $p.ExitCode
}
function Helper {
    for ($i = 0; $i -lt 10; $i++) {
        $h = @(Get-CimInstance Win32_Process -Filter "Name='windhawk-mod.exe' OR Name='windhawk.exe'" |
               Where-Object { $_.CommandLine -like "*-tool-mod `"$id`"*" })
        if ($h.Count) { return ,$h }
        Start-Sleep -Seconds 2
    }
    return ,@()
}
function ModState {
    $k = "$base\$id"
    if (-not (Test-Path $k)) { return "mod: not installed" }
    $v = Get-ItemProperty $k
    "mod: version=$($v.Version) disabled=$([int]$v.Disabled)"
}
function TaskState {
    $t = Get-ScheduledTask -TaskPath '\' -TaskName $task.TrimStart('\') -ErrorAction SilentlyContinue
    if (-not $t) { return 'app task: missing' }
    "app task: $($t.State)"
}
function AppProcs { @(Get-Process SoundManager -ErrorAction SilentlyContinue) }

if ($Audit -or -not ($Install -or $Rollback)) {
    ModState
    "helper running: $((Helper).Count)"
    TaskState
    "app processes: $((AppProcs).Count)"
    foreach ($c in $classes) {
        $k = "HKCU:\Software\Classes\$c"
        $cmd = (Get-ItemProperty "$k\shell\import\command" -ErrorAction SilentlyContinue).'(default)'
        $def = (Get-ItemProperty $k -ErrorAction SilentlyContinue).'(default)'
        "$c : $(if (Test-Path $k) { "default=$def open=$cmd" } else { 'none' })"
    }
    exit 0
}

if ($Install) {
    New-Item -ItemType Directory -Force $backup | Out-Null
    if (-not (Test-Path "$backup\task.xml")) {
        Export-ScheduledTask -TaskPath '\' -TaskName $task.TrimStart('\') | Set-Content "$backup\task.xml" -Encoding Unicode
    }
    foreach ($c in $classes) {
        $f = "$backup\classes$($c.Replace('.', '_')).reg"
        if ((Test-Path "HKCU:\Software\Classes\$c") -and -not (Test-Path $f)) {
            & reg.exe export "HKCU\Software\Classes\$c" $f /y | Out-Null
        }
    }
    if (-not (Test-Path "$backup\AppEvents.reg")) { & reg.exe export 'HKCU\AppEvents' "$backup\AppEvents.reg" /y | Out-Null }
    $ini = "$env:APPDATA\SoundManager\SoundManager.ini"
    if ((Test-Path $ini) -and -not (Test-Path "$backup\SoundManager.ini")) { Copy-Item $ini "$backup\SoundManager.ini" }
    "backup: $((Get-ChildItem $backup).Name -join ', ')"

    $installed = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
    $same = (Test-Path $installed) -and ([IO.File]::ReadAllText($installed).Replace("`r`n", "`n") -eq [IO.File]::ReadAllText($built).Replace("`r`n", "`n"))
    if ($same) {
        'install: this build is already installed'
    } else {
        $ver = ([regex]::Match([IO.File]::ReadAllText($built), '//\s*@version\s+(\S+)')).Groups[1].Value
        $staged = "C:\Users\Public\seamless-sound-manager-$ver.wh.cpp"
        Copy-Item $built $staged -Force
        $baseHash = if (Test-Path $installed) { (Get-FileHash $installed -Algorithm SHA256).Hash } else { 'new' }
        & 'H:\Windhawk Configuration\scripts\Install-StagedMod.ps1' -Id $id -Staged $staged -BaseHash $baseHash
        if ($LASTEXITCODE -ne 0) { "FATAL: install failed, the app is left as it was"; exit 1 }
    }
    ModState
    & 'H:\Windhawk Configuration\scripts\2026-11-10-tool-mod-restart.ps1' -Id $id
    $h = @(Helper)
    if (-not $h.Count) { 'FATAL: the mod helper is not running, the app is left as it was'; exit 2 }

    # Retire the app: its task off, its process stopped. It stays installed so rollback is one step.
    $null = Disable-ScheduledTask -TaskPath '\' -TaskName $task.TrimStart('\')
    AppProcs | Stop-Process -Force
    TaskState
    "app processes: $((AppProcs).Count)"
    [ordered]@{
        when = (Get-Date).ToString('s'); mod = $id; source = $built
        sourceSha256 = (Get-FileHash $built -Algorithm SHA256).Hash
        version = (Get-ItemProperty "$base\$id").Version; helperPid = ($h.ProcessId -join ',')
        appTask = (TaskState); backup = $backup
    } | ConvertTo-Json | Set-Content $receipt -Encoding UTF8
    "receipt: $receipt"
    exit 0
}

if ($Rollback) {
    if (Test-Path "$base\$id") { "remove mod: exit=$(Invoke-Hidden $cli "mod remove $id --yes --json" 60)" }
    Get-ChildItem $backup -Filter 'classes*.reg' -ErrorAction SilentlyContinue | ForEach-Object {
        "restore $($_.Name): exit=$(Invoke-Hidden 'reg.exe' "import `"$($_.FullName)`"")"
    }
    $null = Enable-ScheduledTask -TaskPath '\' -TaskName $task.TrimStart('\')
    if (-not (AppProcs).Count) { Start-ScheduledTask -TaskPath '\' -TaskName $task.TrimStart('\'); Start-Sleep 3 }
    ModState; TaskState
    "app processes: $((AppProcs).Count)"
}
