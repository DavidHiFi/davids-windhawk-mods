[CmdletBinding()]
param(
    [ValidateSet('Audit', 'Install', 'Rollback')]
    [string]$Action = 'Audit'
)

# Windhawk Styler 2.0.41 -> 2.0.42: one shared ring on every box, accent on
# the remaining antd defaults (ribbon, spinner, tab and button hovers, selected
# menu and select items). Audit, install and rollback in one script, with a
# registry export, the installed source copy and a JSON receipt.

$ErrorActionPreference = 'Stop'
$root = 'H:\Windhawk Configuration'
$modKey = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$registryKey = "Registry::$modKey"
$backup = Join-Path $root 'backups\2026-10-11\styler-ring-accent-2042'
$receiptPath = Join-Path $backup 'receipt.json'
$installedSource = 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp'
$workSource = Join-Path $root 'work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp'
$buildDll = Join-Path $root 'work\styler-release\mods\local\windhawk-styler\build\windhawk-styler-64.dll'
$fromVersion = '2.0.41'
$toVersion = '2.0.42'

if ($Action -eq 'Audit') {
    $mod = Get-ItemProperty $registryKey
    $dllPath = "C:\ProgramData\Windhawk\Engine\Mods\64\$($mod.LibraryFileName)"
    [ordered]@{
        version = $mod.Version
        libraryFileName = $mod.LibraryFileName
        settingsChangeTime = $mod.SettingsChangeTime
        installedSourceSha256 = if (Test-Path -LiteralPath $installedSource) { (Get-FileHash $installedSource -Algorithm SHA256).Hash } else { $null }
        libraryExists = Test-Path -LiteralPath $dllPath
        librarySha256 = if (Test-Path -LiteralPath $dllPath) { (Get-FileHash $dllPath -Algorithm SHA256).Hash } else { $null }
    } | ConvertTo-Json
    exit 0
}

if ($Action -eq 'Install') {
    $before = Get-ItemProperty $registryKey
    if ($before.Version -ne $fromVersion) { throw "Expected $fromVersion before install, found $($before.Version)." }
    if (-not (Test-Path -LiteralPath $buildDll -PathType Leaf)) { throw "Build DLL missing: $buildDll" }
    $sourceVersion = Get-Content -LiteralPath $workSource -TotalCount 8 | Where-Object { $_ -match '^// @version' } | Select-Object -First 1
    if ($sourceVersion -notmatch [regex]::Escape($toVersion)) { throw "Worktree source is not version $toVersion." }

    if (-not (Test-Path -LiteralPath $backup)) { New-Item -ItemType Directory -Path $backup -Force | Out-Null }
    $registryBackup = Join-Path $backup 'local@windhawk-styler.reg'
    $sourceBackup = Join-Path $backup "installed-$fromVersion.wh.cpp"
    if (-not (Test-Path -LiteralPath $registryBackup)) {
        reg.exe export $modKey $registryBackup /y | Out-Null
        if ($LASTEXITCODE -ne 0) { throw 'Registry export failed.' }
    }
    if (-not (Test-Path -LiteralPath $sourceBackup)) { Copy-Item -LiteralPath $installedSource -Destination $sourceBackup }

    $dllName = 'local@windhawk-styler_{0}_{1}.dll' -f $toVersion, (Get-Date -Format HHmmss)
    $dllPath = "C:\ProgramData\Windhawk\Engine\Mods\64\$dllName"
    Copy-Item -LiteralPath $buildDll -Destination $dllPath
    $dllHash = (Get-FileHash -LiteralPath $dllPath -Algorithm SHA256).Hash
    Copy-Item -LiteralPath $workSource -Destination $installedSource -Force
    $sourceHash = (Get-FileHash -LiteralPath $installedSource -Algorithm SHA256).Hash

    $now = [DateTimeOffset]::Now.ToUnixTimeSeconds()
    Set-ItemProperty $registryKey -Name LibraryFileName -Value $dllName
    Set-ItemProperty $registryKey -Name Version -Value $toVersion
    Set-ItemProperty $registryKey -Name SettingsChangeTime -Value $now -Type DWord
    $after = Get-ItemProperty $registryKey
    if ($after.LibraryFileName -ne $dllName -or $after.Version -ne $toVersion -or $after.SettingsChangeTime -ne $now) { throw 'Registry readback mismatch.' }

    $receipt = [ordered]@{
        date = '2026-10-11'
        mod = 'local@windhawk-styler'
        fromVersion = $before.Version
        fromLibraryFileName = $before.LibraryFileName
        toVersion = $toVersion
        libraryFileName = $dllName
        dllSha256 = $dllHash
        modsSourceSha256 = $sourceHash
        registryBackup = $registryBackup
        sourceBackup = $sourceBackup
        settingsChangeTime = $now
        change = 'One shared 1px ring over every box, so the outline is the same color around the corners; accent on antd ribbon, spinner, tab and button hovers, selected menu and select items.'
    }
    $receipt | ConvertTo-Json | Set-Content -LiteralPath $receiptPath -Encoding UTF8
    $receipt | ConvertTo-Json
    exit 0
}

if (-not (Test-Path -LiteralPath $receiptPath -PathType Leaf)) { throw "Receipt missing: $receiptPath" }
$receipt = Get-Content -LiteralPath $receiptPath -Raw | ConvertFrom-Json
if (-not (Test-Path -LiteralPath $receipt.sourceBackup -PathType Leaf)) { throw "Source backup missing: $($receipt.sourceBackup)" }
Copy-Item -LiteralPath $receipt.sourceBackup -Destination $installedSource -Force
Set-ItemProperty $registryKey -Name LibraryFileName -Value $receipt.fromLibraryFileName
Set-ItemProperty $registryKey -Name Version -Value $receipt.fromVersion
$now = [DateTimeOffset]::Now.ToUnixTimeSeconds()
Set-ItemProperty $registryKey -Name SettingsChangeTime -Value $now -Type DWord
$after = Get-ItemProperty $registryKey
if ($after.LibraryFileName -ne $receipt.fromLibraryFileName -or $after.Version -ne $receipt.fromVersion) { throw 'Rollback readback mismatch.' }
[ordered]@{ version = $after.Version; libraryFileName = $after.LibraryFileName; settingsChangeTime = $after.SettingsChangeTime; sourceSha256 = (Get-FileHash $installedSource -Algorithm SHA256).Hash } | ConvertTo-Json
