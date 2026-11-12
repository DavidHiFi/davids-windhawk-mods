# ELEVATED. Turns "Native Windows title bar" off in Launchpad and Color Picker (Color Picker's wrong
# default had turned it on), after exporting both registry keys. Undo: import the .reg files.
$stamp = Get-Date -Format 'yyyyMMdd-HHmm'
$bk = "H:\Windhawk Configuration\backups\settings-material"
foreach ($pair in @(@('local@seamless-launchpad', 'nativeSettingsTitleBar'),
                    @('local@seamless-color-picker', 'SettingsWindow.nativeSettingsTitleBar'))) {
    $id, $name = $pair
    $k = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
    reg export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$bk\$id-key-$stamp-native.reg" /y | Out-Null
    $old = (Get-ItemProperty "$k\Settings").$name
    Set-ItemProperty "$k\Settings" -Name $name -Value 0 -Type DWord
    Set-ItemProperty $k -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
    "$id $name old=$old new=$((Get-ItemProperty "$k\Settings").$name) backup=$id-key-$stamp-native.reg"
}
