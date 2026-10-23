param(
    [string]$JobFile = 'H:\System Configuration\scripts\2026-10-02-tourne-av\trayfix-job.json',
    [string]$LogPath = 'H:\System Configuration\scripts\2026-10-02-tourne-av\trayfix-elev.log'
)

# Runs under Windows PowerShell 5.1 (elevated wrapper).
# Removes the controlStyles[60] SystemTray.OmniButton Margin := -12,0,0,0 rule
# that pulls the ethernet tray button 12px left, onto the Better Volume Mixer
# icon. Values are recorded in the job file's backup before deletion.

function Write-Log([string]$msg) {
    $line = "{0} {1}" -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'), $msg
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
    Write-Output $line
}

$ErrorActionPreference = 'Stop'
$modKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$settingsKey = "$modKey\Settings"
$targetName = 'controlStyles[60].target'
$styleName = 'controlStyles[60].styles[0]'

try {
    if (-not (Test-Path -LiteralPath $JobFile)) { throw "job file not found: $JobFile" }
    $job = Get-Content -LiteralPath $JobFile -Raw | ConvertFrom-Json
    if ([string]$job.action -ne 'Remove60') { throw "bad action '$($job.action)'" }

    $key = Get-Item -LiteralPath $settingsKey
    $beforeTarget = if ($key.GetValueNames() -contains $targetName) { [string]$key.GetValue($targetName) } else { $null }
    $beforeStyle = if ($key.GetValueNames() -contains $styleName) { [string]$key.GetValue($styleName) } else { $null }
    Write-Log "before: target=$beforeTarget style0=$beforeStyle"

    $regKey = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey(
        'SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings', $true)
    if ($null -eq $regKey) { throw 'Settings key not openable for write' }
    if ($null -ne $beforeTarget) {
        $regKey.DeleteValue($targetName, $false)
        Write-Log "removed $targetName"
    }
    if ($null -ne $beforeStyle) {
        $regKey.DeleteValue($styleName, $false)
        Write-Log "removed $styleName"
    }
    $regKey.Close()

    $now = [DateTimeOffset]::Now.ToUnixTimeSeconds()
    if ($now -le 1790554512) { $now = 1790554513 }
    New-ItemProperty -Path $modKey -Name 'SettingsChangeTime' -Value ([int]$now) -PropertyType DWord -Force | Out-Null
    Write-Log "SettingsChangeTime -> $now"

    $verify = Get-Item -LiteralPath $settingsKey
    Write-Log ("VERIFY target present = {0}" -f ($verify.GetValueNames() -contains $targetName))
    Write-Log 'OK Remove60'
    exit 0
}
catch {
    Write-Log "FAIL: $($_.Exception.Message)"
    exit 1
}
