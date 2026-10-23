param(
    [switch]$Backup,
    [switch]$Apply,
    [string]$Rollback = ''
)

# Explorer speed: Set A (timing) and Set B (one size source).
#   (no switch)  print current values
#   -Backup      export the three mod keys to backups\2026-10-13\explorer-speed (no writes to Windhawk)
#   -Apply       write the new values and bump SettingsChangeTime (elevated shell)
#   -Rollback    import the .reg files from a backup folder and bump SettingsChangeTime (elevated shell)

$ErrorActionPreference = 'Stop'
$modsRoot  = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-13\explorer-speed'

$targets = [ordered]@{
    'file-explorer-content-animation'       = [ordered]@{ navigationDelay = 0; duration = 150; firstOpenDelay = 100 }
    'file-explorer-details-autofit-columns' = [ordered]@{ elastic = 0; delay = 150 }
    'explorer-size-on-disk-column'          = [ordered]@{ folderSizes = 'disabled' }
}

function Test-Admin {
    $id = [Security.Principal.WindowsIdentity]::GetCurrent()
    return ([Security.Principal.WindowsPrincipal]$id).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

function Set-ChangeTime {
    param([string]$ModId)
    $now = [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    Set-ItemProperty -Path (Join-Path $modsRoot $ModId) -Name SettingsChangeTime -Value $now -Type DWord
}

if ($Backup) {
    New-Item -ItemType Directory -Force -Path $backupDir | Out-Null
    foreach ($id in $targets.Keys) {
        & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" (Join-Path $backupDir "$id.reg") /y | Out-Null
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
        $file = Join-Path $Rollback "$id.reg"
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
