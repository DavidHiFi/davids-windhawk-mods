<#
Simple Window Switcher Plus: title pill fill to darker Mocha glass (house dock recipe).
Settings only, applied live (engine watches the Mods key; SettingsChangeTime bumped).
Run elevated. -Rollback restores the export taken first.
#>
param([switch]$Rollback)
$ErrorActionPreference = 'Stop'
$id  = 'local@simple-window-switcher-plus'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$bak = 'H:\Windhawk Configuration\backups\2026-11-11\swsp'
New-Item -ItemType Directory -Force $bak | Out-Null
$reg = Join-Path $bak 'settings.bak-20261111-0150.reg'
if ($Rollback) {
    Remove-Item -LiteralPath "$key\Settings" -Recurse -Force
    & reg.exe import $reg 2>&1 | Out-Null
} else {
    if (-not (Test-Path $reg)) { & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id\Settings" $reg /y | Out-Null }
    $s = "$key\Settings"
    New-ItemProperty -Path $s -Name 'TitlePill.tintColor'   -Value '#11111B' -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $s -Name 'TitlePill.tintOpacity' -Value 70 -PropertyType DWord -Force | Out-Null
    New-ItemProperty -Path $s -Name 'TitlePill.blur'        -Value 30 -PropertyType DWord -Force | Out-Null
    New-ItemProperty -Path $s -Name 'TitlePill.noise'       -Value 4  -PropertyType DWord -Force | Out-Null
}
$t = [DateTimeOffset]::UtcNow.ToUnixTimeMilliseconds()
New-ItemProperty -Path $key -Name 'SettingsChangeTime' -Value ([int]($t / 1000)) -PropertyType DWord -Force | Out-Null
Get-ItemProperty "$key\Settings" | Select-Object 'TitlePill.tintColor','TitlePill.tintOpacity','TitlePill.blur','TitlePill.noise' | Format-List | Out-String
