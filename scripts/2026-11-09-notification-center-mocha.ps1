<#
Notification center Catppuccin Mocha restyle (windows-11-notification-center-styler).
Keeps theme FrostyGlass, overrides its constants (glass, border, radius) and adds
FiraCode Nerd Font Medium on every text label, Mocha text colours, mantle cards
and the blue-ring hover on the panel buttons.

  -Audit     print current settings count
  -Install   back up the mod key, write the new settings, bump SettingsChangeTime
  -Rollback  re-import the backup .reg and bump SettingsChangeTime
Run elevated.
#>
param([switch]$Audit, [switch]$Install, [switch]$Rollback, [ValidateSet('Top','Bottom')][string]$Position = 'Top', [string]$ExtraFile = '')
$ErrorActionPreference = 'Stop'
$modKey = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-notification-center-styler'
$psKey  = "Registry::$modKey"
$set    = "$psKey\Settings"
$bakDir = 'H:\Windhawk Configuration\backups\2026-11-09\notification-center'
$bak    = Join-Path $bakDir 'notification-center-styler-before.reg'
$receipt = Join-Path $bakDir 'receipt.json'

function Bump { Set-ItemProperty $psKey -Name SettingsChangeTime -Type DWord -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) }

if ($Audit) { (Get-Item $set).GetValueNames().Count; Get-ItemProperty $set | Format-List; exit 0 }

if ($Rollback) {
    if (-not (Test-Path $bak)) { throw "no backup at $bak" }
    Remove-Item $set -Recurse -Force
    reg import $bak 2>&1 | Out-Null
    Bump
    "rolled back from $bak"
    exit 0
}

if (-not $Install) { 'use -Audit, -Install or -Rollback'; exit 1 }

New-Item -ItemType Directory -Force $bakDir | Out-Null
if (-not (Test-Path $bak)) { reg export $modKey $bak /y | Out-Null }

$font  = 'FiraCode Nerd Font, Segoe UI Variable Text, Segoe UI'
$text  = '#CDD6F4'; $sub = '#A6ADC8'; $blue = '#89B4FA'; $mauve = '#CBA6F7'
$grad  = '<LinearGradientBrush StartPoint="0,0.5" EndPoint="1,0.5"><GradientStop Color="#FF89B4FA" Offset="0"/><GradientStop Color="#FFCBA6F7" Offset="1"/></LinearGradientBrush>'

# Theme constant overrides (user constants win over FrostyGlass's own).
$constants = @(
    'Background=<WindhawkBlur BlurAmount="48" TintColor="#181825" TintOpacity="0.32" TintLuminosityOpacity="0.45" TintSaturation="1.4" NoiseOpacity="0.04" NoiseDensity="0.8" FallbackColor="#F0181825"/>',
    "BorderBrush=$grad",
    'BorderThickness=2',
    'CornerRadius=15'
)

# Main text: Fira Medium + text colour. Secondary text: Fira Medium + subtext colour.
$mainText = @(
    'Button#DateTextButtonWithClock > Grid > Border#Border > ContentPresenter#ContentPresenter',
    'MenuFlyoutItem > Grid > TextBlock',
    'StackPanel#PrimaryAndSecondaryTextContainer > TextBlock#Title',
    'StackPanel#PrimaryAndSecondaryTextContainer > TextBlock#TitleText',
    'TextBlock#TitleText',
    'ToolTip > ContentPresenter#LayoutRoot > TextBlock',
    'Grid#WeekDayNames > TextBlock',
    'CalendarViewDayItem > TextBlock',
    'Button#HeaderButton > ContentPresenter#Text > TextBlock',
    'TextBlock#ClockWithMeridian',
    'TextBlock#DurationTextBlock',
    'TextBlock#StartButtonText',
    'TextBlock#StopButtonText',
    'TextBlock#NoNotificationsTextBlock',
    'TextBlock#PageTitleText',
    'TextBlock#PageTitle',
    'Button[AutomationProperties.AutomationId=Microsoft.QuickAction.Battery] > ContentPresenter#ContentPresenter > StackPanel > TextBlock',
    'Grid#GroupTitleGrid > TextBlock#Title',
    'NetworkUX.View.EntityListItemControl#EntityListItemControl > Grid > TextBlock',
    'ActionCenter.ClearAllButton#ClearAllButtonControl > Button#ClearAll > ContentPresenter#ContentPresenter@CommonStates > TextBlock',
    'ContentControl#QuickActionContentControl > ContentPresenter > Grid > StackPanel > TextBlock',
    'TextBlock#AppNameText',
    'Grid#RootGrid > ContentPresenter#Content > TextBlock',
    'TextBlock#MixerGroupTitle',
    'TextBlock#SpatialGroupTitle',
    'TextBlock#OutputGroupTitle',
    'Button#DisconnectButton > ContentPresenter#ContentPresenter > TextBlock',
    'StackPanel > StackPanel > CheckBox > Grid#RootGrid > ContentPresenter#ContentPresenter > TextBlock',
    'StackPanel > StackPanel > Button > ContentPresenter#ContentPresenter > TextBlock',
    'TextBlock#ProjectInterfaceDeviceTileTextDeviceName',
    'Button#DateTextButtonWithClockOld > Grid > Border#Border > ContentPresenter#ContentPresenter > TextBlock',
    'TextBlock#ClockWithMeridianOld',
    'StackPanel#MainContent > TextBlock#Title2',
    'TextBlock#SubgroupTitleText',
    'TextBlock#SenderName',
    'TextBlock#FocusingText',
    'Windows.UI.Xaml.Controls.Primitives.CalendarPanel#YearViewPanel > Windows.UI.Xaml.Controls.Primitives.CalendarViewItem > TextBlock',
    'NetworkUX.View.CFEWiFiPassKey > StackPanel > TextBlock#WiFiPassKeyLabel',
    'NetworkUX.View.CFEConnectionCompletion > StackPanel > Button > ContentPresenter#ContentPresenter > TextBlock'
)
$subText = @(
    'Grid#DoNotDisturbSubtext > TextBlock[2]',
    'StackPanel#PrimaryAndSecondaryTextContainer > TextBlock#Subtitle',
    'StackPanel#PrimaryAndSecondaryTextContainer > TextBlock#SubtitleText',
    'TextBlock#StatusText',
    'TextBlock[AutomationProperties.AutomationId=TextTopologyTileDescription]',
    'StackPanel#TextContentPanel > TextBlock',
    'TextBlock#TimeStamp',
    'TextBlock[AutomationProperties.AutomationId=TextBluetoothDisabled]',
    'TextBlock[AutomationProperties.AutomationId=HeaderBluetoothDisabled]',
    'TextBlock[AutomationProperties.AutomationId=YourDevices]',
    'TextBlock[AutomationProperties.AutomationId=NewDevices]',
    'StackPanel#OffUxPanel > TextBlock',
    'NetworkUX.View.EntityListItemControl#EntityListItemControl > Grid > StackPanel > TextBlock',
    'TextBlock[AutomationProperties.AutomationId=TextDeviceListEmpty]',
    'TextBlock[AutomationProperties.AutomationId=AvailableDisplaysTextBlock]',
    'TextBlock#ProjectInterfaceDeviceTileTextDeviceStatus',
    'StackPanel#MainContent > TextBlock#MessageText',
    'StackPanel#MainContent > TextBlock#MessageText2',
    'TextBlock#Attribution',
    'TextBlock#VerbText',
    'NetworkUX.View.CFEConnectionCompletion > StackPanel > TextBlock#ErrorMessageLabel'
)

$rules = [System.Collections.Generic.List[object]]::new()
foreach ($t in $mainText) { $rules.Add(@($t, "FontFamily=$font", 'FontWeight=Medium', "Foreground=$text")) }
foreach ($t in $subText)  { $rules.Add(@($t, "FontFamily=$font", 'FontWeight=Medium', "Foreground=$sub")) }
# Section heading in the primary accent.
$rules.Add(@('TextBlock#NotificationsTextBlock', "FontFamily=$font", 'FontWeight=SemiBold', "Foreground=$blue"))
# Notification cards: mantle fill, grey dock border, radius 8.
$rules.Add(@('ActionCenter.FlexibleItemView > Grid#MainGrid > Grid#ItemGrid > Grid > Border#ItemOpaquePlating', 'Background=#99181825', 'BorderBrush=#E645475A', 'BorderThickness=1', 'CornerRadius=8'))
$rules.Add(@('ActionCenter.FlexibleItemView', 'CornerRadius=8'))
# Panel buttons: resting mantle pill, blue ring on hover, mauve on press.
foreach ($b in @(
    'ActionCenter.ClearAllButton#ClearAllButtonControl > Button#ClearAll > ContentPresenter#ContentPresenter@CommonStates',
    'Grid#FocusControlGrid > Button#StartButton > ContentPresenter#ContentPresenter@CommonStates',
    'Grid#FocusControlGrid > Button#StopButton > ContentPresenter#ContentPresenter@CommonStates',
    'Grid#FocusStateGrid > Grid#FocusTimeSelector > Button#IncreaseTimeButton > ContentPresenter#ContentPresenter@CommonStates',
    'Grid#FocusStateGrid > Grid#FocusTimeSelector > Button#DecreaseTimeButton > ContentPresenter#ContentPresenter@CommonStates',
    'Button#ExpandCollapseButton > ContentPresenter#ContentPresenter@CommonStates'
)) {
    $rules.Add(@($b, 'CornerRadius=8', 'BorderThickness=1', 'Background=#80181825', 'BorderBrush=#E645475A',
        'Background@PointerOver=#BF181825', "BorderBrush@PointerOver=$blue",
        'Background@Pressed=#BF181825', "BorderBrush@Pressed=$mauve"))
}
# Focus start glyph and +/- glyphs in blue.
foreach ($g in @(
    'Grid#FocusControlGrid > Button#StartButton > ContentPresenter#ContentPresenter@CommonStates > StackPanel > FontIcon > Grid > TextBlock',
    'Grid#FocusStateGrid > Grid#FocusTimeSelector > Button#IncreaseTimeButton > ContentPresenter#ContentPresenter@CommonStates > FontIcon > Grid > TextBlock',
    'Grid#FocusStateGrid > Grid#FocusTimeSelector > Button#DecreaseTimeButton > ContentPresenter#ContentPresenter@CommonStates > FontIcon > Grid > TextBlock'
)) { $rules.Add(@($g, "Foreground=$blue")) }

# Fira everywhere: page-level font is inherited by any text without its own font.
$rules.Add(@('ActionCenter.NotificationCenterPage', "FontFamily=$font", 'FontWeight=Medium', "Foreground=$text"))
$rules.Add(@('StackPanel#CalendarHeader > Button#DateTextButton > Grid > Border#Border > ContentPresenter#ContentPresenter > TextBlock', "FontFamily=$font", 'FontWeight=Medium', "Foreground=$text"))
foreach ($t in @('Button#DateTextButton', 'Button#SeeMoreLessButton', 'Windows.UI.Xaml.Controls.Primitives.ToggleButton#DoNotDisturbButton', 'Button#DismissButton', 'Button#SettingsButton', 'Button#ExpandButton')) {
    $rules.Add(@($t, "FontFamily=$font", 'FontWeight=Medium', "FocusVisualPrimaryBrush=$blue", 'FocusVisualSecondaryBrush=Transparent'))
}
foreach ($t in @(
    'StackPanel#CalendarHeader > TextBlock',
    'StackPanel#CalendarHeader > Button#DateTextButton > ContentPresenter#ContentPresenter > TextBlock',
    'StackPanel#CalendarHeader > Button > Grid > Border#Border > ContentPresenter#ContentPresenter > TextBlock',
    'Border#CalendarHeaderMinimizedOverlay > TextBlock',
    'Button#SeeMoreLessButton > ContentPresenter#ContentPresenter > TextBlock',
    'Button#SeeMoreLessButton > ContentPresenter#ContentPresenter > StackPanel > TextBlock'
)) { $rules.Add(@($t, "FontFamily=$font", 'FontWeight=Medium', "Foreground=$text")) }
$rules.Add(@('Windows.UI.Xaml.Controls.Primitives.ToggleButton#DoNotDisturbButton', 'UseSystemFocusVisuals=False', 'CornerRadius=8', 'BorderThickness=1', 'BorderBrush=#E645475A', 'Background=#80181825'))
$rules.Add(@('TextBlock#NotificationSettingsButtonText', "FontFamily=$font", 'FontWeight=Medium', "Foreground=$sub"))
# Hover: same pill as the other panel buttons for the header/footer buttons.
foreach ($b in @(
    'Button#SeeMoreLessButton > ContentPresenter#ContentPresenter@CommonStates',
    'Button#DateTextButton > Grid > Border#Border@CommonStates',
    'Windows.UI.Xaml.Controls.Primitives.ToggleButton#DoNotDisturbButton > ContentPresenter#ContentPresenter@CommonStates',
    'Button#DismissButton > ContentPresenter#ContentPresenter@CommonStates',
    'Button#SettingsButton > ContentPresenter#ContentPresenter@CommonStates'
)) {
    $rules.Add(@($b, 'CornerRadius=8', 'BorderThickness=1', 'BorderBrush=Transparent',
        'Background@PointerOver=#BF181825', "BorderBrush@PointerOver=$blue",
        'Background@Pressed=#BF181825', "BorderBrush@Pressed=$mauve"))
}

# Opening position. Top = one dock right under the clock (taskbar on top);
# Bottom = Windows default (no position rules). These rules show in the
# styler's settings in Windhawk and can be edited or deleted there.
if ($Position -eq 'Top') {
    $root = 'ActionCenter.NotificationCenterPage > Grid#RootGrid > Grid#RootContent'
    # Second row height follows the calendar's real height, which clips the
    # 8000 px padding below it (that padding pushes the content to the top).
    $rules.Add(@($root, 'RowDefinitions:=<RowDefinitionCollection><RowDefinition Height="Auto"/><RowDefinition Height="{{calH}}"/></RowDefinitionCollection>', 'VerticalAlignment=Top'))
    # Notifications: top half of the dock (rounded top, no bottom edge).
    $rules.Add(@("$root > Grid#NotificationCenterGrid", 'MaxHeight=900', 'Margin=12,8,12,0', 'CornerRadius=15,15,0,0', 'BorderThickness=2,2,2,0', 'Background:=$Background', 'BorderBrush:=$BorderBrush'))
    # Calendar holder: invisible, carries the push-to-top padding.
    $rules.Add(@("$root > Grid#CalendarCenterGrid", 'Background=Transparent', 'BorderThickness=0', 'BorderBrush=Transparent', 'CornerRadius=0', 'Height=9000', 'Padding=0,0,0,8000', 'Margin=12,0,12,0'))
    $rules.Add(@('Grid#CalendarCenterGrid > ActionCenter.ClockCalendarView#ClockCalendarView', 'VerticalAlignment=Top', 'Margin=0', 'Padding=0', 'CornerRadius=0', 'ActualHeight=>calH'))
    # Square, flush seam: no inner rounding or overlay box where the halves meet.
    $rules.Add(@('ActionCenter.ClockCalendarView#ClockCalendarView > Grid > Grid#CalendarSection', 'CornerRadius=0', 'BorderThickness=0', 'Background=Transparent'))
    $rules.Add(@('ActionCenter.ClockCalendarView#ClockCalendarView > Grid > Grid#CalendarSection > Border#CalendarHeaderMinimizedOverlay', 'CornerRadius=0', 'BorderThickness=0', 'Background=Transparent'))
    # Calendar: bottom half of the dock (no top edge, rounded bottom).
    $rules.Add(@('Grid#CalendarCenterGrid > ActionCenter.ClockCalendarView#ClockCalendarView > Grid', 'Background:=$Background', 'BorderBrush:=$BorderBrush', 'BorderThickness=2,0,2,2', 'CornerRadius=0,0,15,15', 'Margin=0', 'Padding=0'))
}

if ($ExtraFile -eq 'test') { $ExtraFile = Join-Path $bakDir 'extra-test.txt' }
$extraLines = if ($ExtraFile -and (Test-Path $ExtraFile)) { Get-Content $ExtraFile } else { @() }
foreach ($x in ($extraLines | Where-Object { $_ -and $_ -notmatch '^#' })) { $rules.Add(@($x -split '\|\|')) }

# Find first free controlStyles index (keep existing 0..n rules).
$names = (Get-Item $set).GetValueNames()
$start = 0
while ($names -contains "controlStyles[$start].target") { $start++ }
# Re-runs: drop rules this script added before (tagged by receipt start index).
if (Test-Path $receipt) {
    $prev = Get-Content $receipt | ConvertFrom-Json
    $start = [int]$prev.firstIndex
    # Brackets are wildcards for Remove-ItemProperty; delete through .NET instead.
    $rk = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey('SOFTWARE\Windhawk\Engine\Mods\windows-11-notification-center-styler\Settings', $true)
    foreach ($n in $names) { if ($n -match '^controlStyles\[(\d+)\]' -and [int]$Matches[1] -ge $start) { $rk.DeleteValue($n) } }
    $rk.Close()
}

$i = $start
foreach ($r in $rules) {
    Set-ItemProperty $set -Name "controlStyles[$i].target" -Value $r[0] -Type String
    for ($s = 1; $s -lt $r.Count; $s++) { Set-ItemProperty $set -Name "controlStyles[$i].styles[$($s-1)]" -Value $r[$s] -Type String }
    $i++
}
for ($c = 0; $c -lt $constants.Count; $c++) { Set-ItemProperty $set -Name "styleConstants[$c]" -Value $constants[$c] -Type String }
Bump

@{ when = (Get-Date).ToString('s'); firstIndex = $start; lastIndex = $i - 1; constants = $constants.Count; backup = $bak } |
    ConvertTo-Json | Set-Content $receipt
"installed rules $start..$($i-1), constants $($constants.Count); backup $bak"
(Get-Item $set).GetValueNames().Count
