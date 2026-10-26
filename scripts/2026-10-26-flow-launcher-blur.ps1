# 2026-10-26: add Flow Launcher to translucent-windows (acrylicblur, same tint as the
# other 30 apps) and keep window-borders out of it. Run elevated.
# Rollback: -Action Rollback re-imports the two keys saved by Install.
param([ValidateSet('Install','Rollback')][string]$Action = 'Install')
$ErrorActionPreference = 'Stop'
$exe = 'Flow.Launcher.exe'
$tw = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\translucent-windows'
$wb = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@window-borders'
$bk = 'H:\Windhawk Configuration\backups\2026-10-26-flow-launcher-blur'
function Stamp($k) { Set-ItemProperty $k SettingsChangeTime ([int][double]::Parse((Get-Date -UFormat %s))) -Type DWord }

if ($Action -eq 'Rollback') {
    reg import "$bk\translucent-windows.reg" | Out-Null
    reg import "$bk\window-borders.reg" | Out-Null
    Stamp $tw; Stamp $wb
    "rolled back"; return
}

New-Item -ItemType Directory -Force $bk | Out-Null
if (-not (Test-Path "$bk\translucent-windows.reg")) {
    reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\translucent-windows' "$bk\translucent-windows.reg" /y | Out-Null
    reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@window-borders' "$bk\window-borders.reg" /y | Out-Null
}

$inc = (Get-ItemProperty $tw).IncludeCustom -split '\|'
if ($inc -notcontains $exe) { Set-ItemProperty $tw IncludeCustom (($inc + $exe) -join '|') -Type String }

$s = "$tw\Settings"
$names = (Get-ItemProperty $s).PSObject.Properties.Name
$targets = $names | ? { $_ -match '^RuledPrograms\[\d+\]\.target$' } | % { (Get-ItemProperty $s).$_ }
if ($targets -notcontains $exe) {
    $i = 1 + ($names | ? { $_ -match '^RuledPrograms\[(\d+)\]' } | % { [int]($_ -replace '^RuledPrograms\[(\d+)\].*', '$1') } | Measure -Maximum).Maximum
    # WPF app: like WindowsTerminal, no theme-background or accent-control patching.
    Set-ItemProperty $s "RuledPrograms[$i].target" $exe -Type String
    Set-ItemProperty $s "RuledPrograms[$i].BackgroundEffects.type" 'acrylicblur' -Type String
    Set-ItemProperty $s "RuledPrograms[$i].BackgroundEffects.AccentBlurBehind" 'AA1E1E2E' -Type String
    Set-ItemProperty $s "RuledPrograms[$i].RenderingMod.ThemeBackground" 0 -Type DWord
    Set-ItemProperty $s "RuledPrograms[$i].RenderingMod.AccentColorControls" 0 -Type DWord
}

$ex = (Get-ItemProperty $wb).Exclude -split '\|'
if ($ex -notcontains $exe) { Set-ItemProperty $wb Exclude (($ex + $exe) -join '|') -Type String }

Stamp $tw; Stamp $wb
"include has flow: $(((Get-ItemProperty $tw).IncludeCustom -split '\|') -contains $exe)"
"borders exclude has flow: $(((Get-ItemProperty $wb).Exclude -split '\|') -contains $exe)"
$p = Get-ItemProperty $s
$p.PSObject.Properties | ? { $_.Name -like 'RuledPrograms*' -and $_.Value -eq $exe } | % { $_.Name }
