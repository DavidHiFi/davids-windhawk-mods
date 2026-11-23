<#
Logitech G HUB, which the Logitech battery tray mod reads the battery level from.
Seamless Workshop runs this: -Mode status|check|install|update|remove -Out <answer file> [-Auto]
status and check read this PC only: G HUB keeps itself up to date, so there is nothing to compare.
Run as admin. On its own it only goes in when a Logitech device is plugged in.
#>
param([ValidateSet('status', 'check', 'install', 'update', 'remove')][string]$Mode = 'status', [string]$Out, [switch]$Auto)
$ErrorActionPreference = 'Continue'; $ProgressPreference = 'SilentlyContinue'
$script:latest = ''

function Find-App {
    foreach ($root in 'HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall', 'HKLM:\Software\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall',
                      'HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall') {
        foreach ($k in (Get-ChildItem $root -ErrorAction SilentlyContinue)) {
            $u = Get-ItemProperty $k.PSPath -ErrorAction SilentlyContinue
            if ($u.DisplayName -eq 'Logitech G HUB') {
                $v = ([string]$u.DisplayVersion) -replace '[^\d.]', ''
                $v = $v.Trim('.')
                if ($v -notmatch '^\d+(\.\d+)*$') { $v = '' }
                return @{ version = $v; uninstall = [string]$u.UninstallString; dir = [string]$u.InstallLocation }
            }
        }
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

# Logitech's USB vendor number. Any device, wired or through a receiver, shows it.
function Test-Logitech { [bool](Get-PnpDevice -PresentOnly -ErrorAction SilentlyContinue | Where-Object { $_.InstanceId -match 'VID_046D' } | Select-Object -First 1) }

$a = Find-App
switch ($Mode) {
    { $_ -in 'status', 'check' } { Done $true '' }
    { $_ -in 'install', 'update' } {
        if ($a) { Done $true '' }  # G HUB updates itself.
        if ($Auto -and -not (Test-Logitech)) { Done $false 'Goes in when a Logitech device is plugged in.' $true }
        if (-not (Get-Command winget -ErrorAction SilentlyContinue)) { Done $false 'This PC has no winget. Get G HUB from logitechg.com.' }
        $before = @(Get-Process lghub -ErrorAction SilentlyContinue | ForEach-Object Id)
        winget install -e --id Logitech.GHUB --silent --accept-package-agreements --accept-source-agreements --disable-interactivity 2>&1 | Out-Null
        for ($i = 0; $i -lt 30 -and -not (Find-App); $i++) { Start-Sleep 2 }
        if (-not (Find-App)) { Done $false 'G HUB did not install. Get it from logitechg.com.' }
        # Its setup opens the G HUB window. When nobody asked, it goes back to the tray.
        if ($Auto) {
            for ($i = 0; $i -lt 15; $i++) {
                $w = Get-Process lghub -ErrorAction SilentlyContinue | Where-Object { $before -notcontains $_.Id -and $_.MainWindowHandle -ne 0 }
                if ($w) { $w | ForEach-Object { [void]$_.CloseMainWindow() }; break }
                Start-Sleep 2
            }
        }
        Done $true 'G HUB is in. The battery tray mod can read your Logitech devices now.'
    }
    'remove' {
        if (-not $a) { Done $true 'G HUB is not on this PC.' }
        if (Get-Command winget -ErrorAction SilentlyContinue) {
            winget uninstall -e --id Logitech.GHUB --silent --accept-source-agreements --disable-interactivity 2>&1 | Out-Null
        }
        if ((Find-App) -and $a.uninstall) {
            $un = $a.uninstall
            if ($un -match '^"([^"]+)"\s*(.*)$') { $exe = $Matches[1]; $rest = $Matches[2] } else { $exe = $un; $rest = '' }
            if (Test-Path $exe) { Start-Process $exe -ArgumentList ("$rest --silent").Trim() -Wait -WindowStyle Hidden }
        }
        for ($i = 0; $i -lt 15 -and (Find-App); $i++) { Start-Sleep 2 }
        if (Find-App) { Done $false 'G HUB could not be removed. Remove it from Installed apps.' }
        # Its uninstaller leaves its own "Are you sure?" window open after the work is done.
        Start-Sleep 3
        Get-Process lghub* -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
        Done $true 'G HUB is removed.'
    }
}
