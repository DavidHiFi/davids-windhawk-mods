# Retarget snap-commander and move-window-to-monitor tool hosts to dwm.exe.
# Mode: apply (writes HKLM, needs elevation). Backs up both mod keys first,
# then sets IncludeExcludeCustomOnly=1 (UI: "Ignore mod inclusion/exclusion
# lists") and IncludeCustom=dwm.exe (UI: custom process inclusion list),
# bumping SettingsChangeTime so the engine re-evaluates. Rolls back on failure.
# Change log printed and appended to the output log by the wrapper.

$ErrorActionPreference = 'Stop'

$backupDir = 'H:\System Configuration\backups'
$mods = @('snap-commander', 'move-window-to-monitor')

function Get-RegValue([string]$path, [string]$name) {
    try {
        $item = Get-ItemProperty -Path $path -Name $name -ErrorAction Stop
        return $item.$name
    } catch {
        return $null
    }
}

Write-Output "[$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')] start dwm retarget"

# 1. Backup each mod key before any write.
foreach ($mod in $mods) {
    $key = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$mod"
    $file = Join-Path $backupDir "2026-10-02-windhawk-$mod-before.reg"
    & reg.exe export $key $file /y | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg export failed for $mod (exit $LASTEXITCODE)" }
    Write-Output "backup: $file"
}

# 2. Record old values, then write new ones.
$old = @{}
foreach ($mod in $mods) {
    $path = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$mod"
    $old[$mod] = @{
        IncludeExcludeCustomOnly = Get-RegValue $path 'IncludeExcludeCustomOnly'
        IncludeCustom            = Get-RegValue $path 'IncludeCustom'
        SettingsChangeTime       = Get-RegValue $path 'SettingsChangeTime'
    }
    $oc = if ($null -eq $old[$mod].IncludeExcludeCustomOnly) { '(absent)' } else { $old[$mod].IncludeExcludeCustomOnly }
    $ic = if ($null -eq $old[$mod].IncludeCustom) { '(absent)' } else { "'$($old[$mod].IncludeCustom)'" }
    $st = if ($null -eq $old[$mod].SettingsChangeTime) { '(absent)' } else { $old[$mod].SettingsChangeTime }
    Write-Output "old[$mod]: IncludeExcludeCustomOnly=$oc IncludeCustom=$ic SettingsChangeTime=$st"
}

$now = [int][DateTimeOffset]::Now.ToUnixTimeSeconds()
foreach ($mod in $mods) {
    $path = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$mod"
    try {
        Set-ItemProperty -Path $path -Name 'IncludeExcludeCustomOnly' -Value 1 -Type DWord
        Set-ItemProperty -Path $path -Name 'IncludeCustom' -Value 'dwm.exe' -Type String
        Set-ItemProperty -Path $path -Name 'SettingsChangeTime' -Value $now -Type DWord
    } catch {
        Write-Output "ERROR writing $mod : $($_.Exception.Message)"
        # Roll back this mod to its old values (absent values are removed).
        foreach ($name in 'IncludeExcludeCustomOnly', 'IncludeCustom', 'SettingsChangeTime') {
            $cur = Get-RegValue $path $name
            $was = $old[$mod][$name]
            try {
                if ($null -eq $was) {
                    if ($null -ne $cur) { Remove-ItemProperty -Path $path -Name $name -ErrorAction SilentlyContinue }
                } else {
                    Set-ItemProperty -Path $path -Name $name -Value $was
                }
            } catch {}
        }
        throw
    }
    Write-Output "new[$mod]: IncludeExcludeCustomOnly=1 IncludeCustom='dwm.exe' SettingsChangeTime=$now"
}

# 3. Verify the writes by independent read.
foreach ($mod in $mods) {
    $path = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$mod"
    $ioc = Get-RegValue $path 'IncludeExcludeCustomOnly'
    $icu = Get-RegValue $path 'IncludeCustom'
    if ($ioc -ne 1 -or $icu -ne 'dwm.exe') { throw "verify failed for $mod (IncludeExcludeCustomOnly=$ioc IncludeCustom=$icu)" }
    Write-Output "verify[$mod]: ok"
}

Write-Output "[$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')] done"
