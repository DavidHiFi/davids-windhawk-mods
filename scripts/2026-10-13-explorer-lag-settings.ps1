param(
    [switch]$Backup,
    [switch]$Apply,
    [string]$Rollback = ''
)

# Explorer lag fix, settings only (no code changes):
#   file-explorer-details-autofit-columns : passiveTriggers 1 -> 0
#       (auto-fit no longer runs on folder open/navigate or minimize/restore; the
#        four explicit refresh triggers still fit: F5, Ctrl+R, refresh button, menu)
#   explorer-details-better-file-sizes    : calculateFolderSizes everything -> withShiftKey
#       (folder sizes stay in the Size column, computed only while Shift is held on
#        load or refresh; no Everything lookups on normal navigation)
#   (no switch)  print current values
#   -Backup      reg export both Settings keys to backups\2026-10-13\explorer-lag\settings
#   -Apply       write the new values and bump SettingsChangeTime (elevated shell)
#   -Rollback    import the .reg files from a backup folder and bump SettingsChangeTime (elevated shell)

$ErrorActionPreference = 'Stop'
$modsRoot  = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-13\explorer-lag\settings'

$targets = [ordered]@{
    'file-explorer-details-autofit-columns' = [ordered]@{ passiveTriggers = 0 }
    'explorer-details-better-file-sizes'    = [ordered]@{ calculateFolderSizes = 'withShiftKey' }
}

function Test-Admin {
    $id = [Security.Principal.WindowsIdentity]::GetCurrent()
    return ([Security.Principal.WindowsPrincipal]$id).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

function Set-ChangeTime([string]$ModId) {
    $now = [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    Set-ItemProperty -Path (Join-Path $modsRoot $ModId) -Name SettingsChangeTime -Value $now -Type DWord
}

if ($Backup) {
    New-Item -ItemType Directory -Force -Path $backupDir | Out-Null
    foreach ($id in $targets.Keys) {
        $file = Join-Path $backupDir "$id.settings.reg"
        if (Test-Path -LiteralPath $file) { throw "backup exists, refusing to overwrite: $file" }
        & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id\Settings" $file /y | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "reg export failed: $id" }
    }
    Get-ChildItem -LiteralPath $backupDir | Select-Object Name, Length | Format-Table -AutoSize | Out-String
}

if ($Apply) {
    if (-not (Test-Admin)) { throw 'Apply needs an elevated shell' }
    foreach ($id in $targets.Keys) {
        $setKey = Join-Path $modsRoot "$id\Settings"
        foreach ($name in $targets[$id].Keys) {
            $value = $targets[$id][$name]
            if ($value -is [string]) {
                Set-ItemProperty -Path $setKey -Name $name -Value $value -Type String
            } else {
                Set-ItemProperty -Path $setKey -Name $name -Value ([int]$value) -Type DWord
            }
        }
        Set-ChangeTime -ModId $id
    }
}

if ($Rollback) {
    if (-not (Test-Admin)) { throw 'Rollback needs an elevated shell' }
    foreach ($id in $targets.Keys) {
        $file = Join-Path $Rollback "$id.settings.reg"
        if (Test-Path -LiteralPath $file) {
            & reg.exe import $file | Out-Null
            Set-ChangeTime -ModId $id
        }
    }
}

foreach ($id in $targets.Keys) {
    $item = Get-Item -Path (Join-Path $modsRoot "$id\Settings")
    foreach ($name in $targets[$id].Keys) {
        $kind = if ($item.GetValueNames() -contains $name) { $item.GetValueKind($name) } else { 'absent' }
        '{0}\{1} = {2} ({3})' -f $id, $name, $item.GetValue($name), $kind
    }
}
