# Applies the "one giant rounded pill" restyle to the Windhawk
# windows-11-taskbar-styler mod settings (HKLM).
#
#   .\Set-TaskbarGiantPill.ps1 -Audit    # read-only: print old -> new values
#   .\Set-TaskbarGiantPill.ps1           # write the values (needs admin)
#
# Every changed value is printed with its original value so it can be put back
# by hand, and the whole mod key is exported to the backup folder first by the
# caller. Rollback: import backups\2026-09-25\windhawk-taskbar-styler-before-pill.reg.

[CmdletBinding()]
param(
    [switch]$Audit
)

$ErrorActionPreference = 'Stop'

$modPath = 'SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$settingsPath = "$modPath\Settings"

$id = [Security.Principal.WindowsIdentity]::GetCurrent()
$principal = New-Object Security.Principal.WindowsPrincipal($id)
$isAdmin = $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

# key = registry value name, value = new content
$changes = [ordered]@{
    # Left inset of the weather widget: 12 -> 16, so content clears the pill edge.
    'styleConstants[0]'            = 'taskbarLeftOffset = 16'
    # Right inset of the tray/clock group: 12 -> 24, same reason on the right end.
    'styleConstants[1]'            = 'taskbarRightOffset = 24'
    # No fill and no border on pinned/running app buttons, tray segments,
    # weather widget, overflow button: the boxes disappear.
    'styleConstants[16]'           = 'buttonFill = <SolidColorBrush Color="#00000000"/>'
    'styleConstants[17]'           = 'buttonBorderColor = <SolidColorBrush Color="#00000000"/>'
    # The one pill itself: frosted Catppuccin Mocha (#1E1E2E).
    'styleConstants[18]'           = 'taskbarFill = <WindhawkBlur BlurAmount="80" TintColor="#1E1E2E" TintOpacity="0.92" TintLuminosityOpacity="0.8" FallbackColor="#EB1E1E2E"/>'
    # Rectangle#BackgroundFill: rounded into a pill and outlined. This element is a
    # Shapes.Rectangle, so corners are RadiusX/RadiusY -- CornerRadius is not a valid
    # property there and one invalid setter makes the mod drop this whole style set
    # (Fill, Margin and Stroke included). Inset remainder lives here; the Grid below
    # carries the rest.
    'controlStyles[1].styles[2]'   = 'Margin=2,1,2,1'
    'controlStyles[1].styles[3]'   = 'RadiusX=15'
    'controlStyles[1].styles[4]'   = 'Stroke:=<SolidColorBrush Color="#9945475A"/>'
    'controlStyles[1].styles[5]'   = 'StrokeThickness=2'
    'controlStyles[1].styles[6]'   = 'RadiusY=15'
    # Rectangle#BackgroundStroke: the old full-width top hairline goes away.
    'controlStyles[2].styles[4]'   = 'Visibility=Collapsed'
    # App button minimum width. The stock formula in this preset reserves two icon
    # widths (2*24+2 = 50 px), which is what made the icons sit far apart. One icon
    # width plus 14 px keeps them readable but closes the gap, and it lands on the
    # 38 px TaskbarButtonWidth the taskbar-icon-size mod already asks for.
    'controlStyles[16].styles[0]'  = 'MinWidth := {{max(34,(ImageIconWidth+14))}}'
    # The hover/active highlight (Border#BackgroundElement) and the icon were each
    # anchored to the left of the button, so the box landed 4 px left of the icon.
    # The icon now centres itself in the button instead of being shoved right by a
    # fixed 10 px translate, the hover scale pivots on the icon centre, and the
    # highlight margins are symmetric so the box centres on the same slot.
    # Round 4: the box's slot is 36 px, so side margins of 1 make it 34 px wide,
    # matching its 34 px height (was 28 wide with margins of 4, 1 px either side
    # of the icon).
    'controlStyles[4].styles[2]'   = 'Margin := 1,{{($taskbarTopOffset-$taskbarBottomOffset)/2-2}},1,{{($taskbarBottomOffset-$taskbarTopOffset)/2-2}}'
    # Round 4: a pinned app that is not running used the full-height pill geometry
    # with a transparent 2 px border inside it, so its hover box showed as 32x38 with
    # radius 7 next to the 34x34 radius 5 box of running apps. Both states now share
    # one geometry. The pinned pill fill and border are transparent anyway, so only
    # the hover box changes.
    'controlStyles[4].styles[1]'   = 'Height@NoRunningIndicator := {{TaskbarHeight-($taskbarBottomOffset+$taskbarTopOffset)-2*($highlightOffset)}}'
    'controlStyles[4].styles[3]'   = 'Margin@NoRunningIndicator := 1,{{($taskbarTopOffset-$taskbarBottomOffset)/2-2}},1,{{($taskbarBottomOffset-$taskbarTopOffset)/2-2}}'
    'controlStyles[4].styles[7]'   = 'BorderThickness@NoRunningIndicator = 0'
    'controlStyles[4].styles[9]'   = 'CornerRadius@NoRunningIndicator := $highlightRadius'
    'controlStyles[15].styles[2]'  = 'HorizontalAlignment = 1'
    'controlStyles[15].styles[4]'  = 'RenderTransformOrigin = 0.5,0.5'
    # Round 4: the box centres on the 40 px button (MinWidth below), but the icon
    # centres in the icon column, which taskbar-icon-size sets to its 38 px
    # TaskbarButtonWidth. That left the icon 1 px left of the box on every button,
    # so the icon moves right by (40-38)/2 = 1. The scale comes first in the hover
    # group so the 1 px shift is not scaled down to 0.9.
    'controlStyles[15].styles[5]'  = 'RenderTransform := <TranslateTransform X="1" Y="0" />'
    'controlStyles[15].styles[6]'  = 'RenderTransform@InactivePointerOver := <TransformGroup><ScaleTransform ScaleX = "0.9" ScaleY = "0.9" /><TranslateTransform X="1" Y="0" /></TransformGroup>'
    # The background layer's Grid: carries most of the inset. It is not touched by
    # TaskbarBackground.OnApplyTemplate, so 6,3 here plus 2,1 on the Rectangle
    # lands at 8,4,8,4 when both apply and 6,3 if only this one survives.
    'controlStyles[58].target'     = 'Taskbar.TaskbarBackground#BackgroundControl > Grid'
    'controlStyles[58].styles[0]'  = 'Margin=6,3,6,3'
    'controlStyles[58].styles[1]'  = '// Background layer inset: makes the taskbar read as one floating pill.'
}

$localKey = [Microsoft.Win32.Registry]::LocalMachine
# Writable handle only when actually applying; audit mode needs read access only.
$settingsKey = $localKey.OpenSubKey($settingsPath, (-not $Audit))

if (-not $settingsKey) {
    throw "Cannot open $settingsPath for writing."
}

$plan = foreach ($name in $changes.Keys) {
    $old = $settingsKey.GetValue($name)
    if ($null -eq $old) { $old = '<not set>' }
    [pscustomobject]@{
        Name  = $name
        Old   = $old
        New   = $changes[$name]
    }
}

$settingsKey.Close()

Write-Output ''
Write-Output 'Planned changes (old -> new):'
$plan | ForEach-Object {
    Write-Output ("  " + $_.Name)
    Write-Output ("      old: " + $_.Old)
    Write-Output ("      new: " + $_.New)
}
Write-Output ''

if ($Audit) {
    Write-Output 'Audit mode: nothing was written.'
    return
}

if (-not $isAdmin) {
    throw 'This script must run elevated (HKLM settings key). Re-run it from an elevated PowerShell.'
}

$settingsKey = $localKey.OpenSubKey($settingsPath, $true)
foreach ($name in $changes.Keys) {
    $settingsKey.SetValue($name, $changes[$name], [Microsoft.Win32.RegistryValueKind]::String)
}
$settingsKey.Close()

# Windhawk uses this to notice that a mod's settings changed.
$modKey = $localKey.OpenSubKey($modPath, $true)
$now = [uint32]([DateTimeOffset]::Now.ToUnixTimeSeconds())
$modKey.SetValue('SettingsChangeTime', [int]$now, [Microsoft.Win32.RegistryValueKind]::DWord)
$modKey.Close()

Write-Output "Wrote $($changes.Count) values and bumped SettingsChangeTime to $now."

$verifyKey = $localKey.OpenSubKey($settingsPath, $false)
$mismatch = foreach ($name in $changes.Keys) {
    if ([string]$verifyKey.GetValue($name) -ne [string]$changes[$name]) { $name }
}
$verifyKey.Close()

if ($mismatch) {
    throw ('Verification failed for: ' + ($mismatch -join ', '))
}
Write-Output 'Verified: registry matches the planned values.'
