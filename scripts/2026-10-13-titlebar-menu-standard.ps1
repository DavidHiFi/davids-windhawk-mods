# Windhawk title bar menu: put windhawk-ui.exe on translucent-flyouts' process block list so
# the Windhawk window uses the plain Windows system menu. Writes the setting and bumps
# SettingsChangeTime, the same marker a save in the Windhawk UI writes.
# Run elevated: Invoke-Elevated.ps1 -File <this script> -ArgumentList "-Action Apply"
[CmdletBinding()]
param(
    [ValidateSet('Audit', 'Apply', 'Cycle', 'Rollback')]
    [string]$Action = 'Audit'
)
$ErrorActionPreference = 'Stop'
$root = 'H:\Windhawk Configuration'
$modKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@translucent-flyouts'
$settingsKey = "$modKey\Settings"
$name = 'advancedFunctions.processBlockList'
$target = 'windhawk-ui.exe'
$backup = Join-Path $root 'backups\2026-10-13\titlebar-menu-standard'
$receiptPath = Join-Path $backup 'receipt.json'

if ($Action -eq 'Audit') {
    $mod = Get-ItemProperty $modKey
    $settings = Get-ItemProperty $settingsKey -ErrorAction SilentlyContinue
    [ordered]@{
        version = $mod.Version
        library = $mod.LibraryFileName
        settingsChangeTime = $mod.SettingsChangeTime
        processBlockList = if ($settings) { $settings.$name } else { $null }
    } | ConvertTo-Json
    exit 0
}

if ($Action -eq 'Apply') {
    if (Test-Path -LiteralPath $receiptPath) { throw "Receipt exists, roll back first: $receiptPath" }
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    $regBackup = Join-Path $backup 'translucent-flyouts.reg'
    reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@translucent-flyouts' $regBackup /y | Out-Null
    if ($LASTEXITCODE) { throw 'Registry export failed.' }
    $before = (Get-ItemProperty $settingsKey -ErrorAction SilentlyContinue).$name
    $now = [DateTimeOffset]::Now.ToUnixTimeSeconds()
    Set-ItemProperty -Path $settingsKey -Name $name -Value $target -Type String
    Set-ItemProperty -Path $modKey -Name SettingsChangeTime -Value $now -Type DWord
    $after = (Get-ItemProperty $settingsKey).$name
    if ($after -ne $target) { throw 'Readback mismatch.' }
    $receipt = [ordered]@{
        date = '2026-10-13'
        mod = 'local@translucent-flyouts'
        setting = $name
        before = $before
        after = $after
        settingsChangeTime = $now
        registryBackup = $regBackup
    }
    $receipt | ConvertTo-Json | Set-Content -LiteralPath $receiptPath -Encoding UTF8
    $receipt | ConvertTo-Json
    exit 0
}

# Cycle = switch the mod off and on, which starts it again in every process and reads the block list.
if ($Action -eq 'Cycle') {
    $disabledBefore = (Get-ItemProperty $modKey).Disabled
    foreach ($value in 1, 0) {
        Set-ItemProperty -Path $modKey -Name Disabled -Value $value -Type DWord
        Set-ItemProperty -Path $modKey -Name SettingsChangeTime -Value ([DateTimeOffset]::Now.ToUnixTimeSeconds()) -Type DWord
        Start-Sleep -Seconds 4
    }
    [ordered]@{
        disabledBefore = $disabledBefore
        disabledNow = (Get-ItemProperty $modKey).Disabled
        settingsChangeTime = (Get-ItemProperty $modKey).SettingsChangeTime
    } | ConvertTo-Json
    exit 0
}

if (-not (Test-Path -LiteralPath $receiptPath)) { throw "Receipt missing: $receiptPath" }
$receipt = Get-Content -LiteralPath $receiptPath -Raw | ConvertFrom-Json
if ($receipt.before) {
    Set-ItemProperty -Path $settingsKey -Name $name -Value $receipt.before -Type String
} else {
    Remove-ItemProperty -Path $settingsKey -Name $name -ErrorAction SilentlyContinue
}
$now = [DateTimeOffset]::Now.ToUnixTimeSeconds()
Set-ItemProperty -Path $modKey -Name SettingsChangeTime -Value $now -Type DWord
Rename-Item -LiteralPath $receiptPath -NewName 'receipt.rolled-back.json'
$after = (Get-ItemProperty $settingsKey -ErrorAction SilentlyContinue).$name
[ordered]@{ processBlockList = $after; settingsChangeTime = $now } | ConvertTo-Json
