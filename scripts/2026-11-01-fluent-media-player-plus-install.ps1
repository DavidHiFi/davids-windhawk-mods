# 2026-11-01 Taskbar Fluent Media Player Plus: install the merged player + visualizer with the owner's
# Catppuccin Mocha look, and turn off the two mods it replaces. Run elevated (Invoke-Elevated.ps1 -File).
#   -Mode Audit     show the three mod keys, change nothing
#   -Mode Install   back up, copy source + DLL, create the key with merged settings, disable the originals
#   -Mode Rollback  turn the originals back on and the Plus mod off
param([ValidateSet('Audit', 'Install', 'Rollback')][string]$Mode = 'Audit',
      [string]$Lib = 'local@taskbar-fluent-media-player-plus_1.7.2_1.dll')
$ErrorActionPreference = 'Stop'

$ws     = 'H:\Windhawk Configuration'
$work   = "$ws\work\2026-11-01-fluent-media-player-plus"
$backup = "$ws\backups\2026-11-01-fluent-media-player-plus"
$id     = 'local@taskbar-fluent-media-player-plus'
$mods   = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$key    = "$mods\$id"
$player = "$mods\taskbar-fluent-media-player"
$viz    = "$mods\local@taskbar-audio-visualizer"
$src    = 'C:\ProgramData\Windhawk\ModsSource'
$mods64 = 'C:\ProgramData\Windhawk\Engine\Mods\64'
function Now { [int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds() }
function Bump($k) { Set-ItemProperty $k -Name SettingsChangeTime -Value (Now) -Type DWord }
function Disabled($k) { if (Test-Path $k) { (Get-ItemProperty $k).Disabled } else { 'absent' } }
$out = @("$((Get-Date).ToString('yyyy-MM-dd h:mm:ss tt')) mode=$Mode")

# Owner's look: Catppuccin Mocha text, blue artist line, mauve buttons, Fira Code like the system stats,
# always visible, fixed width so the bars beside it never jump.
$overrides = [ordered]@{
    'MainSettings.PlayerSetting.position'                          = 'taskbar_after_system_info'
    'MainSettings.PlayerSetting.playerMargin'                      = '8 6'
    'MainSettings.PlayerSetting.playerHeight'                      = '36 36'
    'MainSettings.AlbumArtSetting.albumArtWidth'                   = '28 28'
    'MainSettings.AlbumArtSetting.albumArtHeight'                  = '28 28'
    'MainSettings.AlbumArtSetting.albumArtMargin'                  = '4 0'
    'MainSettings.TextAreaSetting.textAreaWidth'                   = '116 116'
    'MainSettings.TextAreaSetting.textAreaMargin'                  = '8 4'
    'MainSettings.MediaButtonsSettings.buttonSize'                 = 26
    'MainSettings.MediaButtonsSettings.mediaButtonsMargin'         = '0 4'
    'BehaviorSettings.hideWhenNoMedia'                             = 0
    # A soft Mocha surface0 pill gives the player an edge without glass or glow.
    'AppearanceSettings.BackgroundStyleSettings.backgroundType'    = 'solid'
    'AppearanceSettings.BackgroundStyleSettings.solidColor'        = '49 50 68'
    'AppearanceSettings.BackgroundStyleSettings.solidOpacity'      = 60
    'AppearanceSettings.BackgroundStyleSettings.cornerRadius'      = '10'
    'AppearanceSettings.TitleTextStyleSettings.titleFontWeight'    = 'Medium'
    'AppearanceSettings.AlbumArtDisplaySettings.albumArtEmptyBehavior' = 'show_icon'
    'AppearanceSettings.AlbumArtDisplaySettings.emptyIconSize'     = 14
    'AppearanceSettings.AlbumArtDisplaySettings.pauseOverlayOpacity' = 45
    'AppearanceSettings.MediaButtonsStyleSettings.buttonColor'     = '203 166 247'
    'AppearanceSettings.MediaButtonsStyleSettings.buttonCornerRadius' = '6'
    'AppearanceSettings.TitleTextStyleSettings.titleColor'         = '205 214 244'
    'AppearanceSettings.TitleTextStyleSettings.titleFont'          = 'custom'
    'AppearanceSettings.TitleTextStyleSettings.titleFontFamily'    = 'FiraCode Nerd Font'
    'AppearanceSettings.TitleTextStyleSettings.titleFontSize'      = 11
    'AppearanceSettings.ArtistTextStyleSettings.artistColor'       = '137 180 250'
    'AppearanceSettings.ArtistTextStyleSettings.artistColorOpacity' = 100
    'AppearanceSettings.ArtistTextStyleSettings.artistFont'        = 'custom'
    'AppearanceSettings.ArtistTextStyleSettings.artistFontFamily'  = 'FiraCode Nerd Font'
    'AppearanceSettings.ArtistTextStyleSettings.artistFontSize'    = 10
    'AppearanceSettings.AlbumArtDisplaySettings.emptyIconColor'    = '203 166 247'
    'AppearanceSettings.AlbumArtDisplaySettings.emptyIconOpacity'  = 80
    'AppearanceSettings.AlbumArtDisplaySettings.albumArtCornerRadius' = '6'
    'ContextMenuSettings.contextMenuIconColor'                     = '203 166 247'
    'PlayerMenuSettings.placementMode'                             = 'near'
    'PlayerMenuSettings.PlayerMenuSettingsNear.miniPlayerVerticalPlacementNear' = 'bottom'
}

function Copy-Values($fromKey, $toKey, [scriptblock]$keep, [string]$prefix = '') {
    $item = Get-Item $fromKey
    foreach ($name in $item.GetValueNames()) {
        if (-not (& $keep $name)) { continue }
        $kind = $item.GetValueKind($name)
        $value = $item.GetValue($name, $null, 'DoNotExpandEnvironmentNames')
        New-ItemProperty -Path $toKey -Name "$prefix$name" -Value $value -PropertyType $kind -Force | Out-Null
    }
}

if ($Mode -eq 'Audit') {
    $out += "plus: disabled=$(Disabled $key) lib=$(if (Test-Path $key) { (Get-ItemProperty $key).LibraryFileName })"
    $out += "player: disabled=$(Disabled $player)   visualizer: disabled=$(Disabled $viz)"
} elseif ($Mode -eq 'Install') {
    New-Item $backup -ItemType Directory -Force | Out-Null
    if (-not (Test-Path "$backup\taskbar-fluent-media-player.reg")) {
        reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\taskbar-fluent-media-player' "$backup\taskbar-fluent-media-player.reg" /y | Out-Null
        reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-audio-visualizer' "$backup\taskbar-audio-visualizer.reg" /y | Out-Null
        Copy-Item "$src\taskbar-fluent-media-player.wh.cpp", "$src\local@taskbar-audio-visualizer.wh.cpp" $backup
    }
    Copy-Item "$work\$id.wh.cpp" "$src\$id.wh.cpp" -Force
    # A loaded DLL is locked; only copy when the engine copy differs or is missing.
    if (-not (Test-Path "$mods64\$lib") -or (Get-FileHash "$mods64\$lib").Hash -ne (Get-FileHash "$work\build\x64\$lib").Hash) {
        Copy-Item "$work\build\x64\$lib" "$mods64\$lib" -Force
    }
    if ((Get-FileHash "$mods64\$lib").Hash -ne (Get-FileHash "$work\build\x64\$lib").Hash) { throw 'DLL copy mismatch' }

    if (-not (Test-Path $key)) {
        New-Item "$key\Settings" -Force | Out-Null
        Copy-Values "$player\Settings" "$key\Settings" { param($n) $n -notmatch 'Visualizer(Functions|Style)Settings' }
        Copy-Values "$viz\Settings" "$key\Settings" { param($n) $n -notlike 'media_controls.*' } 'Visualizer.'
    }
    foreach ($k in $overrides.Keys) {
        $v = $overrides[$k]
        $type = if ($v -is [int]) { 'DWord' } else { 'String' }
        New-ItemProperty -Path "$key\Settings" -Name $k -Value $v -PropertyType $type -Force | Out-Null
    }
    Set-ItemProperty $key -Name LibraryFileName -Value $Lib -Type String
    Set-ItemProperty $key -Name Version -Value ($Lib -replace '^.*_(\d+\.\d+\.\d+)_\d+\.dll$','$1') -Type String
    Set-ItemProperty $key -Name Include -Value 'explorer.exe' -Type String
    Set-ItemProperty $key -Name Exclude -Value '' -Type String
    Set-ItemProperty $key -Name Architecture -Value 'x86-64' -Type String
    Set-ItemProperty $key -Name LoggingEnabled -Value 0 -Type DWord

    # Originals off first, so the old visualizer's tool process and the old player let go before ours starts.
    Set-ItemProperty $player -Name Disabled -Value 1 -Type DWord; Bump $player
    Set-ItemProperty $viz -Name Disabled -Value 1 -Type DWord; Bump $viz
    Start-Sleep -Seconds 3
    Set-ItemProperty $key -Name Disabled -Value 0 -Type DWord; Bump $key

    $s = Get-ItemProperty "$key\Settings"
    $bad = @($overrides.Keys | Where-Object { "$($s.$_)" -ne "$($overrides[$_])" })
    if ($bad -or (Get-ItemProperty $key).LibraryFileName -ne $Lib -or (Disabled $key) -ne 0 -or (Disabled $player) -ne 1 -or (Disabled $viz) -ne 1) {
        throw "readback mismatch: $($bad -join ', ')"
    }
    $vizCount = @((Get-Item "$key\Settings").GetValueNames() | Where-Object { $_ -like 'Visualizer.*' }).Count
    $out += "installed $Lib; position=$($s.'MainSettings.PlayerSetting.position') hideWhenNoMedia=$($s.'BehaviorSettings.hideWhenNoMedia') visualizer values=$vizCount; originals Disabled=1"
} else {
    Set-ItemProperty $key -Name Disabled -Value 1 -Type DWord; Bump $key
    Start-Sleep -Seconds 3
    Set-ItemProperty $player -Name Disabled -Value 0 -Type DWord; Bump $player
    Set-ItemProperty $viz -Name Disabled -Value 0 -Type DWord; Bump $viz
    $out += "rolled back: plus Disabled=$(Disabled $key) player Disabled=$(Disabled $player) visualizer Disabled=$(Disabled $viz)"
}
$out | Set-Content "$work\$Mode-result.txt" -Encoding UTF8
$out
