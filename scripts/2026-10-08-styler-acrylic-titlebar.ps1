<#
.SYNOPSIS
Styler 2.0.4 acrylic title bar deploy. Run elevated via Invoke-Elevated.ps1.

Phases:
  -Audit     print mod key state, deployed DLL, UI processes, source version
  -Install   sync source -> ModsSource, compile, verify mod key (Include!)
  -Rollback  restore the 2.0.2 source from backup, recompile, verify

All output also lands in backups\2026-10-08\styler-2.0.3-acrylic-titlebar\phase-log.txt.
The 2.0.2 fallback (titleBarAcrylic=false) needs no redeploy: set the registry
value HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler\Settings\titleBarAcrylic
to 0 and restart the UI.
#>
[CmdletBinding()]
param(
    [switch]$Audit,
    [switch]$Install,
    [switch]$Rollback
)

$ErrorActionPreference = 'Continue'
$root    = 'H:\Windhawk Configuration'
$src     = "$root\work\windhawk-styler\tauri20\windhawk-styler.wh.cpp"
$bak     = "$root\backups\2026-10-08\styler-2.0.3-acrylic-titlebar"
$srcDest = 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp'
$modKey  = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$log     = "$bak\phase-log.txt"

function Log($m) {
    $line = "[{0}] {1}" -f (Get-Date -Format 'HH:mm:ss'), $m
    Write-Output $line
    Add-Content -Path $log -Value $line
}

function Show-State {
    Log "=== mod key ==="
    $k = Get-ItemProperty $modKey
    Log ("Version: {0}" -f $k.Version)
    Log ("LibraryFileName: {0}" -f $k.LibraryFileName)
    Log ("Include: {0}" -f $k.Include)
    Log ("Disabled: {0}" -f $k.Disabled)
    $dll = Join-Path 'C:\ProgramData\Windhawk\Engine\Mods\64' $k.LibraryFileName
    if (Test-Path $dll) { Log ("DLL present: {0} ({1} bytes)" -f $dll, (Get-Item $dll).Length) }
    else { Log "DLL MISSING: $dll" }
    Log "=== UI processes ==="
    Get-CimInstance Win32_Process -Filter "Name='windhawk-ui.exe'" |
        ForEach-Object { Log ("pid {0} started {1}" -f $_.ProcessId, $_.CreationDate) }
    Log ("source @version: " + ((Select-String -Path $src -Pattern '@version\s+(\S+)').Matches[0].Groups[1].Value))
    Log ("source hash: " + (Get-FileHash $src).Hash)
    if (Test-Path $srcDest) { Log ("ModsSource hash: " + (Get-FileHash $srcDest).Hash) }
}

if ($Audit) {
    Show-State
    exit 0
}

if ($Install -or $Rollback) {
    if ($Install) {
        Copy-Item $src $srcDest -Force
        Log "source synced (2.0.4)"
    } else {
        Copy-Item "$bak\ModsSource.pre-2.0.3.wh.cpp" $srcDest -Force
        Log "2.0.2 source restored from backup"
    }
    Log ("hash now: " + (Get-FileHash $srcDest).Hash)

    Log "=== compile ==="
    $out = cmd /c '"C:\Program Files\Windhawk\windhawk-cli.exe" mod compile local@windhawk-styler 2>&1' | Out-String
    $out.Trim() -split "`n" | ForEach-Object { Log $_ }
    Log ("compile exit: $LASTEXITCODE")

    Start-Sleep -Seconds 12
    $k = Get-ItemProperty $modKey
    Log ("mod key after: Version={0} LibraryFileName={1} Include={2}" -f $k.Version, $k.LibraryFileName, $k.Include)
    if (-not $k.Include) { Log "WARN: Include is EMPTY - set it to windhawk-ui.exe" }
    Show-State
    exit 0
}

Show-State
