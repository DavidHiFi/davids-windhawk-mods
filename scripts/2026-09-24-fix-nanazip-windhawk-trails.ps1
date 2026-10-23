# Applied 2026-09-24: disable translucent-windows per-app effects for
# NanaZip.Modern.FileManager.exe (RuledPrograms[21]) that caused drag-select
# repaint trails. Original values backed up in
# backups\2026-09-24-translucent-windows-windhawk.reg
# Rollback: reg import that .reg file, then restart Windhawk service.

$ErrorActionPreference = 'Stop'
$logPath = 'H:\System Configuration\reports\2026-09-24-nanazip-windhawk-fix.log'
function Log([string]$m) { $m | Add-Content -LiteralPath $logPath }
Set-Content -LiteralPath $logPath -Value "start $(Get-Date -Format o) elev=$(([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator))"

$settingsKey = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\translucent-windows\Settings'
$modKey      = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'

try {
    $target = (& reg.exe query "$settingsKey" /v "RuledPrograms[21].target") -join "`n"
    if ($target -notmatch 'NanaZip\.Modern\.FileManager\.exe') {
        throw "RuledPrograms[21].target mismatch: $target"
    }

    $beforeType = ((& reg.exe query "$settingsKey" /v "RuledPrograms[21].BackgroundEffects.type") -join "`n")
    $beforeTheme = ((& reg.exe query "$settingsKey" /v "RuledPrograms[21].RenderingMod.ThemeBackground") -join "`n")
    $beforeAccent = ((& reg.exe query "$settingsKey" /v "RuledPrograms[21].RenderingMod.AccentColorControls") -join "`n")
    Log "BEFORE type: $beforeType"
    Log "BEFORE theme: $beforeTheme"
    Log "BEFORE accent: $beforeAccent"

    & reg.exe add "$settingsKey" /v "RuledPrograms[21].BackgroundEffects.type" /t REG_SZ /d "none" /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg add type failed: $LASTEXITCODE" }
    & reg.exe add "$settingsKey" /v "RuledPrograms[21].RenderingMod.ThemeBackground" /t REG_DWORD /d 0 /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg add theme failed: $LASTEXITCODE" }
    & reg.exe add "$settingsKey" /v "RuledPrograms[21].RenderingMod.AccentColorControls" /t REG_DWORD /d 0 /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg add accent failed: $LASTEXITCODE" }

    $now = [int64][double]::Parse((Get-Date -UFormat %s))
    & reg.exe add "$modKey" /v "SettingsChangeTime" /t REG_QWORD /d $now /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg add SettingsChangeTime failed: $LASTEXITCODE" }

    $afterType = ((& reg.exe query "$settingsKey" /v "RuledPrograms[21].BackgroundEffects.type") -join "`n")
    $afterTheme = ((& reg.exe query "$settingsKey" /v "RuledPrograms[21].RenderingMod.ThemeBackground") -join "`n")
    $afterAccent = ((& reg.exe query "$settingsKey" /v "RuledPrograms[21].RenderingMod.AccentColorControls") -join "`n")
    Log "AFTER type: $afterType"
    Log "AFTER theme: $afterTheme"
    Log "AFTER accent: $afterAccent"

    if ($afterType -notmatch 'none' -or $afterTheme -notmatch '0x0\s+0x0?$' -and $afterTheme -notmatch '\s+0$') {
        # loose check below is authoritative
        $okType = $afterType -match 'none'
        $okTheme = [bool]($afterTheme -match '0x0\b' -or $afterTheme -match '\b0\b')
        $okAccent = [bool]($afterAccent -match '0x0\b' -or $afterAccent -match '\b0\b')
        if (-not ($okType -and $okTheme -and $okAccent)) {
            throw "Verification failed type=$okType theme=$okTheme accent=$okAccent"
        }
    }

    Log "restarting Windhawk"
    Restart-Service -Name Windhawk -Force
    Log "Windhawk service restarted OK"
    Log "done $(Get-Date -Format o)"
    exit 0
} catch {
    Log "FAIL: $($_.Exception.Message)"
    exit 1
}
