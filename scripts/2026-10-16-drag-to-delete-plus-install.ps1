# Drag to Delete Plus 1.0.0 revision 2 install.
# Refreshes both architecture DLLs from the repo build (the loaded 64-bit _1 was
# stale and the 32-bit one was missing), points LibraryFileName at the new
# revision, bumps SettingsChangeTime, and verifies by readback.
# Run elevated. -Rollback restores the _1 library name and removes the _2 files.
param([switch]$Rollback)

$ErrorActionPreference = 'Stop'
$modId     = 'local@drag-to-delete-plus'
$libNew    = "${modId}_1.0.0_2.dll"
$libOld    = "${modId}_1.0.0_1.dll"
$modKey    = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$modId"
$build     = 'H:\Windhawk Configuration\davids-windhawk-mods\mods\local\drag-to-delete-plus\build'
$backup    = 'H:\Windhawk Configuration\backups\2026-10-16\drag-to-delete-plus'
$report    = 'H:\Windhawk Configuration\reports\2026-10-16-drag-to-delete-plus-install'

New-Item $report -ItemType Directory -Force | Out-Null
function Log($m) { Add-Content -Path "$report\install.log" -Value ("[{0}] {1}" -f (Get-Date -Format 'hh:mm:ss tt'), $m) }

if ($Rollback) {
    $before = (Get-ItemProperty $modKey).LibraryFileName
    Set-ItemProperty $modKey -Name LibraryFileName -Value $libOld
    Set-ItemProperty $modKey -Name SettingsChangeTime -Value ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
    Remove-Item "C:\ProgramData\Windhawk\Engine\Mods\64\$libNew", "C:\ProgramData\Windhawk\Engine\Mods\32\$libNew" -Force -ErrorAction SilentlyContinue
    $after = (Get-ItemProperty $modKey).LibraryFileName
    if ($after -ne $libOld) { throw "Rollback failed: LibraryFileName=$after" }
    Log "rollback: $before -> $after"
    [ordered]@{ action = 'rollback'; library = $after } | ConvertTo-Json | Set-Content "$report\rollback-receipt.json" -Encoding UTF8
    exit 0
}

# 1. Backup the mod key before touching anything.
New-Item $backup -ItemType Directory -Force | Out-Null
reg export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$modId" "$backup\mod-key-before.reg" /y | Out-Null
if (!(Test-Path "$backup\mod-key-before.reg")) { throw 'reg export produced no file' }
$before = Get-ItemProperty $modKey
Log ("backup ok; before: Library={0} SettingsChangeTime={1}" -f $before.LibraryFileName, $before.SettingsChangeTime)

# 2. Copy the fresh revision DLLs into the engine mod folders.
Copy-Item "$build\drag-to-delete-plus-64.dll" "C:\ProgramData\Windhawk\Engine\Mods\64\$libNew" -Force
Copy-Item "$build\drag-to-delete-plus-32.dll" "C:\ProgramData\Windhawk\Engine\Mods\32\$libNew" -Force
Log 'copied 64 + 32 revision 2 DLLs'

# 3. Point the mod at the new revision and bump the change marker.
Set-ItemProperty $modKey -Name LibraryFileName -Value $libNew
Set-ItemProperty $modKey -Name SettingsChangeTime -Value ([DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord

# 4. Verify by readback, never by assuming.
$after = Get-ItemProperty $modKey
$h64 = (Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$libNew" -Algorithm SHA256).Hash
$h32 = (Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\32\$libNew" -Algorithm SHA256).Hash
$s64 = (Get-FileHash "$build\drag-to-delete-plus-64.dll" -Algorithm SHA256).Hash
$s32 = (Get-FileHash "$build\drag-to-delete-plus-32.dll" -Algorithm SHA256).Hash
if ($after.LibraryFileName -ne $libNew) { throw "readback mismatch: LibraryFileName=$($after.LibraryFileName)" }
if ($h64 -ne $s64 -or $h32 -ne $s32) { throw 'DLL hash mismatch after copy' }
Log ("after: Library={0} SettingsChangeTime={1} hashes match build" -f $after.LibraryFileName, $after.SettingsChangeTime)

[ordered]@{
    when               = (Get-Date).ToString('o')
    action             = 'install revision 2'
    libraryFileName    = $after.LibraryFileName
    settingsChangeTime = $after.SettingsChangeTime
    include            = $after.Include
    version            = $after.Version
    disabled           = $after.Disabled
    dll64Sha256        = $h64
    dll32Sha256        = $h32
    source             = "$build"
    backup             = "$backup\mod-key-before.reg"
} | ConvertTo-Json | Set-Content "$report\receipt.json" -Encoding UTF8
Log 'receipt written'
