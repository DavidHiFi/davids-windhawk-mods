# Explorer styler: OS26 theme + tabless title, hidden search box, left command bar.
# Rollback: reg import backups\2026-10-27\explorer-styler-tabless\settings-before.reg, then bump SettingsChangeTime.
param([switch]$Rollback)
$ErrorActionPreference = 'Stop'
$mod = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\windows-11-file-explorer-styler'
$key = "$mod\Settings"
$bak = 'H:\Windhawk Configuration\backups\2026-10-27\explorer-styler-tabless\settings-before.reg'
if ($Rollback) {
    reg import $bak | Out-Null
} else {
    if (-not (Test-Path $bak)) { reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-file-explorer-styler\Settings' $bak /y | Out-Null }
    $styles = [ordered]@{
        # Tabless theme: the single tab becomes a plain window title
        'Grid#TabContainerGrid > Border' = @('Visibility=Collapsed')
        'Grid#TabContainer > Button#CloseButton' = @('Visibility=Collapsed')
        'Grid#TabContainer' = @('BorderThickness=0', 'Padding=1,0,0,1')
        'FileExplorerExtensions.FileExplorerTabControl' = @('Height=36')
        'Viewbox#IconBox' = @('Margin=0,0,4,0')
        'TabViewItem' = @('Margin=0,-8,0,0')
        # Undo the OS26 tab pill so the title has no box around it
        'TabViewItem > Grid#LayoutRoot' = @('BorderThickness=0', 'Background=Transparent')
        'TabViewItem > Grid#LayoutRoot@CommonStates' = @('Background@Selected=Transparent', 'Background@PointerOverSelected=Transparent', 'Background@Normal=Transparent', 'Background@PointerOver=Transparent')
        # Hide the search box; the address bar takes its column
        'AutoSuggestBox#FileExplorerSearchBox' = @('Visibility=Collapsed')
        'Grid#FileExplorerAddressBarGrid' = @('Grid.ColumnSpan=2', 'Margin=-6,0,10,0')
        # Command bar on the left instead of centered
        'CommandBar#FileExplorerCommandBar' = @('HorizontalAlignment=Left')
        # OS26 draws a second blurred pill inside greyed-out buttons; it renders as a ragged double ring
        'Microsoft.UI.Xaml.Controls.AppBarButton > Grid@CommonStates' = @('Background@Disabled=Transparent', 'BorderThickness@Disabled=0')
        'Microsoft.UI.Xaml.Controls.AppBarButton#backButton > Grid@CommonStates' = @('Background@Disabled=Transparent', 'BorderThickness@Disabled=0')
        'Microsoft.UI.Xaml.Controls.AppBarButton#forwardButton > Grid@CommonStates' = @('Background@Disabled=Transparent', 'BorderThickness@Disabled=0')
        'Microsoft.UI.Xaml.Controls.AppBarButton#upButton > Grid@CommonStates' = @('Background@Disabled=Transparent', 'BorderThickness@Disabled=0')
        # Details sits right after View: both bars get auto-width columns, the spare space goes last
        'FileExplorerExtensions.CommandBarControl_Wave1 > Grid, Grid#CommandBarControlRootGrid' = @('ColumnDefinitions:=<ColumnDefinitionCollection><ColumnDefinition Width="Auto"/><ColumnDefinition Width="Auto"/><ColumnDefinition Width="*"/></ColumnDefinitionCollection>')
    }
    # .NET calls: the PowerShell cmdlets treat the [n] in value names as wildcards
    $rk = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey('SOFTWARE\Windhawk\Engine\Mods\windows-11-file-explorer-styler\Settings', $true)
    foreach ($n in $rk.GetValueNames()) { if ($n.StartsWith('controlStyles')) { $rk.DeleteValue($n) } }
    $i = 0
    foreach ($t in $styles.Keys) {
        $rk.SetValue("controlStyles[$i].target", $t, 'String')
        $j = 0
        foreach ($s in $styles[$t]) { $rk.SetValue("controlStyles[$i].styles[$j]", $s, 'String'); $j++ }
        $i++
    }
    $rk.Close()
}
Set-ItemProperty $mod -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
