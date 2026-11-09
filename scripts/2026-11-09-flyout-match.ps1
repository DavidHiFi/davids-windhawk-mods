# Taskbar right-click menus copy the desktop and title-bar menu look.
# Taskbar styler settings only (hot reload, no rebuilds, no Explorer restart):
#   - new constant $MenuMaterial: Mocha base blur at 40% (desktop menus use 661E1E2E acrylic)
#   - menu rule (MenuFlyoutPresenter > Border): that blur, 2 px diagonal blue-to-mauve border,
#     corner radius 16
#   - item rules: FiraCode 13 px regular, white text, compact 24 px rows
#   - separator rule: thin grey line inset from the border
# Covers every taskbar menu: open apps, empty taskbar area (Seamless Taskbar Utilities),
# clock, media player, AI usage, tray drawer.
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$modKey  = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$set     = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$bakDir  = 'H:\Windhawk Configuration\backups\2026-11-09\flyout-match'
$bak     = Join-Path $bakDir 'taskbar-styler-before.reg'
$receipt = Join-Path $bakDir 'receipt.json'

$material = '<AcrylicBrush BackgroundSource="HostBackdrop" TintColor="#1E1E2E" TintOpacity="0.40" FallbackColor="#F01E1E2E"/>'
$border = '<LinearGradientBrush StartPoint="0,0" EndPoint="1,1"><GradientStop Color="#89B4FA" Offset="0"/><GradientStop Color="#CBA6F7" Offset="1"/></LinearGradientBrush>'
$itemStyles = @('FontFamily=FiraCode Nerd Font', 'FontSize=13', 'FontWeight=Normal', 'Foreground=White', 'MinHeight=0', 'Height=26', 'Padding=4,0,8,0')
$rules = [ordered]@{
    'MenuFlyoutPresenter'          = @('Background:=$MenuMaterial', "BorderBrush:=$border", 'BorderThickness=2', 'CornerRadius=16')
    'MenuFlyoutPresenter > Border' = @('CornerRadius=16')
    'MenuFlyoutItem'               = $itemStyles
    'ToggleMenuFlyoutItem'         = $itemStyles
    'MenuFlyoutSubItem'            = $itemStyles
    'MenuFlyoutSeparator'          = @('Padding=4,3,4,3', 'Background=#7F849C')
}

function Bump { Set-ItemProperty ($set -replace '\\Settings$','') -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord }
function RuleIndex($it, $names, $target) {
    $i = 0
    while ($names -contains "controlStyles[$i].target") { if ($it.GetValue("controlStyles[$i].target") -eq $target) { return $i }; $i++ }
    return -1
}

if ($Audit) {
    $it = Get-Item $set; $names = $it.GetValueNames()
    $names | Where-Object { $_ -match '^styleConstants' } | ForEach-Object { "$_ = $($it.GetValue($_))" }
    foreach ($t in $rules.Keys) {
        $r = RuleIndex $it $names $t
        if ($r -lt 0) { "[$t] not present"; continue }
        $names | Where-Object { $_.StartsWith("controlStyles[$r].") } | ForEach-Object { "$_ = $($it.GetValue($_))" }
    }
    exit 0
}

if ($Rollback) {
    if (-not (Test-Path $bak)) { 'no backup'; exit 1 }
    # Targeted: put rule 51 back to the taskbar material only, drop the rules and the
    # constant this script added (receipt), keep every other thread's later changes.
    $r = Get-Content $receipt | ConvertFrom-Json
    $mine = @($r.rules.PSObject.Properties.Value) | Where-Object { $_ -ne 51 }
    $rk = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey('SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings', $true)
    foreach ($n in $rk.GetValueNames()) {
        if ($n.StartsWith('controlStyles[51].styles[') -and $n -ne 'controlStyles[51].styles[0]') { $rk.DeleteValue($n) }
        foreach ($i in $mine) { if ($n.StartsWith("controlStyles[$i].")) { $rk.DeleteValue($n) } }
        if ($n -eq "styleConstants[$($r.constantSlot)]") { $rk.DeleteValue($n) }
    }
    $rk.SetValue('controlStyles[51].styles[0]', 'Background:=$TaskbarMaterial')
    $rk.Close()
    Bump
    "rolled back (rules $($mine -join ','), constant $($r.constantSlot) removed; rule 51 restored)"; exit 0
}

if (-not $Install) { 'use -Audit, -Install or -Rollback'; exit 1 }

New-Item -ItemType Directory -Force $bakDir | Out-Null
if (-not (Test-Path $bak)) { reg export $modKey $bak /y | Out-Null }
$it = Get-Item $set
$names = $it.GetValueNames()

$c = 0; $slot = -1
while ($names -contains "styleConstants[$c]") { if ($it.GetValue("styleConstants[$c]") -like 'MenuMaterial=*') { $slot = $c }; $c++ }
if ($slot -lt 0) { $slot = $c }
Set-ItemProperty $set -Name "styleConstants[$slot]" -Value "MenuMaterial=$material" -Type String

$next = 0; while ($names -contains "controlStyles[$next].target") { $next++ }
$used = @{}
foreach ($t in $rules.Keys) {
    $r = RuleIndex $it $names $t
    if ($r -lt 0) { $r = $next; $next++ }
    else { foreach ($n in $names) { if ($n.StartsWith("controlStyles[$r].styles[")) { Remove-ItemProperty $set -Name $n } } }
    Set-ItemProperty $set -Name "controlStyles[$r].target" -Value $t -Type String
    $s = 0; foreach ($v in $rules[$t]) { Set-ItemProperty $set -Name "controlStyles[$r].styles[$s]" -Value $v -Type String; $s++ }
    $used[$t] = $r
}
Bump

@{ when = (Get-Date).ToString('s'); constantSlot = $slot; rules = $used; backup = $bak } | ConvertTo-Json | Set-Content $receipt
"installed: constant $slot, rules $(($used.Values | Sort-Object) -join ','); backup $bak"
