param(
    [string]$JobFile = 'H:\System Configuration\scripts\2026-10-02-taskbar-gaps\elev-job.json',
    [string]$StateFile = 'H:\System Configuration\backups\2026-10-02-taskbar-gaps\styler-controlstyle-state.json',
    [string]$LogPath = 'H:\System Configuration\scripts\2026-10-02-taskbar-gaps\elev.log'
)

# Runs under Windows PowerShell 5.1 (elevated wrapper), so no PS7-only syntax.
# The caller writes $JobFile before elevating; this script takes no arguments so
# the elevated cmd wrapper needs none either.

function Write-Log([string]$msg) {
    $line = "{0} {1}" -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'), $msg
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
    Write-Output $line
}

function Read-JsonFile([string]$path) {
    if (-not (Test-Path -LiteralPath $path)) { return $null }
    # -Encoding UTF8 is required: this script runs in PowerShell 5.1, whose
    # Get-Content default is ANSI and would mangle non-ASCII registry values
    # (styler rule controlStyles[59] holds private-use glyph code points).
    return (Get-Content -LiteralPath $path -Raw -Encoding UTF8 | ConvertFrom-Json)
}

$ErrorActionPreference = 'Stop'
$modKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$settingsKey = "$modKey\Settings"

try {
    $job = Read-JsonFile $JobFile
    if ($null -eq $job) { throw "job file not found: $JobFile" }

    $action = [string]$job.action
    $Index = [int]$job.index
    $Target = [string]$job.target
    $Style0 = [string]$job.style0

    if ($action -ne 'Apply' -and $action -ne 'Restore') { throw "bad action '$action'" }

    $targetName = "controlStyles[$Index].target"
    $styleName = "controlStyles[$Index].styles[0]"

    $key = Get-Item -LiteralPath $settingsKey
    $names = $key.GetValueNames()

    if ($action -eq 'Apply') {
        if (-not $Target -or -not $Style0) { throw 'Apply requires target and style0 in the job file' }

        $state = Read-JsonFile $StateFile
        if ($null -eq $state) { $state = New-Object psobject }
        $prop = $state.PSObject.Properties[$Index.ToString()]
        if ($null -eq $prop) {
            $orig = [pscustomobject]@{
                target    = $null
                hadTarget = ($names -contains $targetName)
                hadStyle0 = ($names -contains $styleName)
                style0    = $null
            }
            if ($orig.hadTarget) { $orig.target = [string]$key.GetValue($targetName) }
            if ($orig.hadStyle0) { $orig.style0 = [string]$key.GetValue($styleName) }
            $state | Add-Member -NotePropertyName $Index.ToString() -NotePropertyValue $orig -Force
            $state | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $StateFile -Encoding UTF8
            Write-Log "saved original controlStyles[$Index] -> $StateFile"
        }

        New-ItemProperty -Path $settingsKey -Name $targetName -Value $Target -PropertyType String -Force | Out-Null
        New-ItemProperty -Path $settingsKey -Name $styleName -Value $Style0 -PropertyType String -Force | Out-Null
        Write-Log "APPLIED controlStyles[$Index].target = $Target"
        Write-Log "APPLIED controlStyles[$Index].styles[0] = $Style0"
    }
    else {
        $state = Read-JsonFile $StateFile
        if ($null -eq $state) { throw "no state file at $StateFile" }
        $prop = $state.PSObject.Properties[$Index.ToString()]
        if ($null -eq $prop) { throw "state file has no entry for index $Index" }
        $orig = $prop.Value

        if ($orig.hadTarget) {
            New-ItemProperty -Path $settingsKey -Name $targetName -Value ([string]$orig.target) -PropertyType String -Force | Out-Null
            Write-Log "RESTORED controlStyles[$Index].target = $($orig.target)"
        }
        else {
            Remove-Item -Path $settingsKey -Name $targetName -ErrorAction SilentlyContinue
            Write-Log "RESTORED controlStyles[$Index].target -> removed (did not exist)"
        }

        if ($orig.hadStyle0) {
            New-ItemProperty -Path $settingsKey -Name $styleName -Value ([string]$orig.style0) -PropertyType String -Force | Out-Null
            Write-Log "RESTORED controlStyles[$Index].styles[0] = $($orig.style0)"
        }
        else {
            Remove-Item -Path $settingsKey -Name $styleName -ErrorAction SilentlyContinue
            Write-Log "RESTORED controlStyles[$Index].styles[0] -> removed (did not exist)"
        }

        $state.PSObject.Properties.Remove($Index.ToString())
        if ($state.PSObject.Properties.Count -eq 0) { Remove-Item -LiteralPath $StateFile -Force }
        else { $state | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $StateFile -Encoding UTF8 }
    }

    $now = [DateTimeOffset]::Now.ToUnixTimeSeconds()
    if ($now -le 1790554512) { $now = 1790554513 }
    New-ItemProperty -Path $modKey -Name 'SettingsChangeTime' -Value ([int]$now) -PropertyType DWord -Force | Out-Null
    Write-Log "SettingsChangeTime -> $now"

    $verify = Get-Item -LiteralPath $settingsKey
    Write-Log ("VERIFY {0} = {1}" -f $targetName, $verify.GetValue($targetName))
    Write-Log ("VERIFY {0} = {1}" -f $styleName, $verify.GetValue($styleName))
    Write-Log "OK $action"
    exit 0
}
catch {
    Write-Log "FAIL: $($_.Exception.Message)"
    exit 1
}
