# Install Windhawk Styler 2.0.35 (list-view theming) as a new revision.
# Backs up the mod key and current source, drops the new DLL, points
# LibraryFileName at it, bumps SettingsChangeTime, and reads everything back.
$ErrorActionPreference = 'Stop'
$date = '2026-10-11'
$backup = "H:\Windhawk Configuration\backups\$date\styler-listview"
New-Item -ItemType Directory -Force -Path $backup | Out-Null
$log = @()

# 1. Backup: registry key + current source copy.
$key = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$regKey = "Registry::$key"
reg export $key "$backup\local@windhawk-styler.reg" /y | Out-Null
Copy-Item "C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp" "$backup\local@windhawk-styler.2.0.34.wh.cpp" -Force
$before = Get-ItemProperty $regKey
$log += "backup: reg + source done; before LibraryFileName=$($before.LibraryFileName) Version=$($before.Version) SettingsChangeTime=$($before.SettingsChangeTime)"

# 2. New DLL into the engine folder.
$suffix = Get-Date -Format HHmmss
$dllName = "local@windhawk-styler_2.0.35_$suffix.dll"
$src = "H:\Windhawk Configuration\work\styler-release\mods\local\windhawk-styler\build\windhawk-styler-64.dll"
Copy-Item $src "C:\ProgramData\Windhawk\Engine\Mods\64\$dllName" -Force
$hash = (Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$dllName" -Algorithm SHA256).Hash
$log += "installed DLL: $dllName sha256=$hash"

# 3. Update the engine's mod source.
Copy-Item "H:\Windhawk Configuration\work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp" "C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp" -Force
$srcHash = (Get-FileHash "C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp" -Algorithm SHA256).Hash
$log += "ModsSource updated sha256=$srcHash"

# 4. Registry: point at the new revision and bump the change marker.
$now = [DateTimeOffset]::Now.ToUnixTimeSeconds()
Set-ItemProperty $regKey -Name LibraryFileName -Value $dllName
Set-ItemProperty $regKey -Name Version -Value '2.0.35'
Set-ItemProperty $regKey -Name SettingsChangeTime -Value $now -Type DWord

# 5. Read back.
$after = Get-ItemProperty $regKey
$log += "readback: LibraryFileName=$($after.LibraryFileName) Version=$($after.Version) SettingsChangeTime=$($after.SettingsChangeTime) (wanted $now)"
if ($after.LibraryFileName -ne $dllName -or $after.SettingsChangeTime -ne $now) { throw 'readback mismatch' }

# Receipt.
$receipt = [ordered]@{
    date        = $date
    mod         = 'local@windhawk-styler'
    fromVersion = $before.Version
    toVersion   = '2.0.35'
    change      = 'List view (ant-table) theming: card color, borders, header overlay, hover, accent sorters/selection, text color; translucent tables blur like dialogs'
    dll         = $dllName
    dllSha256   = $hash
    modsSourceSha256 = $srcHash
    registryBackup   = "$backup\local@windhawk-styler.reg"
    sourceBackup     = "$backup\local@windhawk-styler.2.0.34.wh.cpp"
    settingsChangeTime = $now
}
$receipt | ConvertTo-Json | Set-Content "$backup\receipt.json"
$log

