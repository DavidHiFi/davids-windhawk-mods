<#
.SYNOPSIS
  Moves two local Windhawk mods to new ids without the owner's name:
    local@davids-audio-visualizer         -> local@taskbar-audio-visualizer (1.2.0)
    local@explorer-font-changer-davidhifi -> local@shell-font-changer       (1.1.0)

.DESCRIPTION
  -Audit     Read-only. Prints both keys, files, storage and loaded state.
  -Backup    Exports the old keys and copies old source, DLLs and storage into
             backups\2026-10-04\mod-id-migration\<old-id>\. Install runs it too.
  -Install   Needs admin. Copies source and prebuilt DLLs, clones the Mods and
             ModsWritable registry keys and the mod-storage folder, disables the
             old id, then enables the new one. Bumps SettingsChangeTime on both.
  -Rollback  Needs admin. Disables the new id and re-enables the old one. Leaves
             the new files and keys in place.

  Never runs windhawk.exe -restart. Old keys, sources, DLLs and storage stay.
  Build the DLLs first into work\id-migrate\build\{64,32} (see the note).
#>
[CmdletBinding()]
param([switch]$Audit, [switch]$Backup, [switch]$Install, [switch]$Rollback,
      [string]$LogPath)
$ErrorActionPreference = 'Stop'
if ($LogPath) { Start-Transcript -Path $LogPath -Force | Out-Null }

$root     = Split-Path $PSScriptRoot -Parent
$build    = Join-Path $root 'work\id-migrate\build'
$srcDir   = Join-Path $root 'work\mod-polish-20261004\src'
$backupDir = Join-Path $root 'backups\2026-10-04\mod-id-migration'
$data     = 'C:\ProgramData\Windhawk'
$modsKey  = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$wrKey    = 'HKLM\SOFTWARE\Windhawk\Engine\ModsWritable'
$storage  = "$data\Engine\ModsWritable\mod-storage"

$mods = @(
    @{ Old = 'local@davids-audio-visualizer';         New = 'local@taskbar-audio-visualizer'
       Version = '1.2.0'; Source = 'taskbar-audio-visualizer.wh.cpp' },
    @{ Old = 'local@explorer-font-changer-davidhifi'; New = 'local@shell-font-changer'
       Version = '1.1.0'; Source = 'shell-font-changer.wh.cpp' }
)

function Test-Admin {
    ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()
    ).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}
function Get-RegPs($key) { 'Registry::' + ($key -replace '^HKLM', 'HKEY_LOCAL_MACHINE') }
function Get-Unix { [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds() }
function Invoke-Reg {
    & reg.exe @args | Out-Null
    if ($LASTEXITCODE) { throw "reg $($args -join ' ') failed ($LASTEXITCODE)" }
}

function Show-Audit {
    foreach ($m in $mods) {
        foreach ($id in $m.Old, $m.New) {
            "=== $id"
            $k = Get-RegPs "$modsKey\$id"
            if (Test-Path $k) {
                $p = Get-ItemProperty $k
                "  Disabled=$($p.Disabled) Version=$($p.Version) LibraryFileName=$($p.LibraryFileName) SettingsChangeTime=$($p.SettingsChangeTime)"
                "  Settings values: $(@((Get-Item (Join-Path $k 'Settings') -EA SilentlyContinue).Property).Count)"
            } else { '  (no Mods key)' }
            $w = Get-RegPs "$wrKey\$id\LocalStorage"
            if (Test-Path $w) { "  LocalStorage: $((Get-Item $w).Property -join ', ')" }
            if (Test-Path "$storage\$id") { "  mod-storage: $((Get-ChildItem "$storage\$id" -Name) -join ', ')" }
            $srcFile = "$data\ModsSource\$id.wh.cpp"
            if (Test-Path $srcFile) { "  source sha256 $((Get-FileHash $srcFile).Hash)" }
            if ($p -and $p.LibraryFileName) {
                foreach ($arch in '64', '32') {
                    $dll = "$data\Engine\Mods\$arch\$($p.LibraryFileName)"
                    if (Test-Path $dll) { "  $arch $((Get-FileHash $dll).Hash)" }
                }
            }
            $p = $null
        }
    }
    '=== loaded'
    Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" |
        Where-Object CommandLine -match 'audio-visualizer' |
        ForEach-Object { "  windhawk.exe pid $($_.ProcessId): $($_.CommandLine)" }
    Get-Process explorer -EA SilentlyContinue | ForEach-Object {
        $_.Modules | Where-Object ModuleName -match 'font-changer' |
            ForEach-Object { "  explorer: $($_.FileName)" }
    }
}

function Invoke-Backup {
    foreach ($m in $mods) {
        $dst = Join-Path $backupDir $m.Old
        New-Item "$dst\Mods\64", "$dst\Mods\32", "$dst\ModsSource" -ItemType Directory -Force | Out-Null
        Invoke-Reg export "$modsKey\$($m.Old)" "$dst\Mods-key.reg" /y
        if (Test-Path (Get-RegPs "$wrKey\$($m.Old)")) {
            Invoke-Reg export "$wrKey\$($m.Old)" "$dst\ModsWritable-key.reg" /y
        }
        Copy-Item "$data\ModsSource\$($m.Old).wh.cpp" "$dst\ModsSource\" -Force
        foreach ($arch in '64', '32') {
            Copy-Item "$data\Engine\Mods\$arch\$($m.Old)_*.dll" "$dst\Mods\$arch\" -Force
        }
        if (Test-Path "$storage\$($m.Old)") {
            Copy-Item "$storage\$($m.Old)" "$dst\mod-storage" -Recurse -Force
        }
        "backup: $dst"
    }
}

function Set-Enabled($id, [int]$disabled) {
    Invoke-Reg add "$modsKey\$id" /v Disabled /t REG_DWORD /d $disabled /f
    Invoke-Reg add "$modsKey\$id" /v SettingsChangeTime /t REG_DWORD /d (Get-Unix) /f
}

function Invoke-Install {
    if (-not (Test-Admin)) { throw 'Install needs an elevated shell' }
    Invoke-Backup
    foreach ($m in $mods) {
        $dllName = "$($m.New)_$($m.Version)_1.dll"
        foreach ($arch in '64', '32') {
            $from = "$build\$arch\$dllName"
            if (-not (Test-Path $from)) { throw "missing build $from" }
            Copy-Item $from "$data\Engine\Mods\$arch\$dllName" -Force
        }
        Copy-Item (Join-Path $srcDir $m.Source) "$data\ModsSource\$($m.New).wh.cpp" -Force

        # Clone every value and subkey, then mark the copy disabled until the old id is off.
        Invoke-Reg copy "$modsKey\$($m.Old)" "$modsKey\$($m.New)" /s /f
        Invoke-Reg add "$modsKey\$($m.New)" /v Disabled /t REG_DWORD /d 1 /f
        Invoke-Reg add "$modsKey\$($m.New)" /v LibraryFileName /t REG_SZ /d $dllName /f
        Invoke-Reg add "$modsKey\$($m.New)" /v Version /t REG_SZ /d $m.Version /f
        if (Test-Path (Get-RegPs "$wrKey\$($m.Old)")) {
            Invoke-Reg copy "$wrKey\$($m.Old)" "$wrKey\$($m.New)" /s /f
        }
        if ((Test-Path "$storage\$($m.Old)") -and -not (Test-Path "$storage\$($m.New)")) {
            Copy-Item "$storage\$($m.Old)" "$storage\$($m.New)" -Recurse
        }

        Set-Enabled $m.Old 1
        Start-Sleep -Seconds 3
        Set-Enabled $m.New 0
        "installed $($m.New) ($dllName); $($m.Old) disabled"
    }
}

function Invoke-Rollback {
    if (-not (Test-Admin)) { throw 'Rollback needs an elevated shell' }
    foreach ($m in $mods) {
        if (Test-Path (Get-RegPs "$modsKey\$($m.New)")) { Set-Enabled $m.New 1 }
        Start-Sleep -Seconds 3
        Set-Enabled $m.Old 0
        "rolled back to $($m.Old)"
    }
}

try {
    if ($Install)  { Invoke-Install }
    elseif ($Rollback) { Invoke-Rollback }
    elseif ($Backup) { Invoke-Backup }
    Show-Audit
} finally {
    if ($LogPath) { Stop-Transcript | Out-Null }
}
