# Seamless Volume Mixer 1.3.0 (App Volume Booster merged in).
#   -Audit     read-only: installed version, source hash, booster leftovers
#   -Install   back up, copy the 1.3.0 source to ModsSource, compile, reload, remove app-volume-booster
#   -Rollback  restore the 1.2.1 mixer source and the booster from the 2026-11-07 backups
# Install and Rollback need admin (run through Invoke-Elevated.ps1). Each run writes a receipt JSON.
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
if (-not ($Audit -or $Install -or $Rollback)) { $Audit = $true }

$root    = 'H:\Windhawk Configuration'
$id      = 'local@better-volume-mixer-plus'
$src     = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$pkg     = "$root\work\2026-11-07-volmixer-1.3.0\$id.wh.cpp"
$bak     = "$root\backups\2026-11-07-volmixer-boost-merge"
$modKey  = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$boostKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\app-volume-booster'
$boostSrc = 'C:\ProgramData\Windhawk\ModsSource\app-volume-booster.wh.cpp'
$cli     = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$stamp   = Get-Date -Format 'yyyyMMdd-HHmm'
$receipt = [ordered]@{ time = (Get-Date).ToString('s'); mode = ''; steps = @() }

function Step($m) { $receipt.steps += $m; Write-Output $m }
function Cli([string]$a) {
    $p = New-Object System.Diagnostics.Process
    $p.StartInfo.FileName = $cli; $p.StartInfo.Arguments = $a
    $p.StartInfo.UseShellExecute = $false; $p.StartInfo.CreateNoWindow = $true
    $p.StartInfo.RedirectStandardOutput = $true; $p.StartInfo.RedirectStandardError = $true
    $p.Start() | Out-Null
    $e = $p.StandardError.ReadToEndAsync(); $o = $p.StandardOutput.ReadToEnd(); $p.WaitForExit()
    Step "cli $a -> exit $($p.ExitCode) $($o.Trim()) $($e.Result.Trim())"
    if ($p.ExitCode -ne 0) { throw "windhawk-cli failed: $a" }
}
function Reload {
    Set-ItemProperty $modKey -Name Disabled -Value 1 -Type DWord; Start-Sleep -Seconds 5
    Set-ItemProperty $modKey -Name Disabled -Value 0 -Type DWord; Step 'mixer reloaded (Disabled 1 -> 0)'
}
function State {
    $m = Get-ItemProperty $modKey -EA SilentlyContinue
    [ordered]@{
        mixerVersion   = $m.Version
        mixerLibrary   = $m.LibraryFileName
        sourceHash     = if (Test-Path $src) { (Get-FileHash $src).Hash } else { $null }
        packageHash    = if (Test-Path $pkg) { (Get-FileHash $pkg).Hash } else { $null }
        includeCustom  = $m.IncludeCustom
        boosterKey     = Test-Path $boostKey
        boosterSource  = Test-Path $boostSrc
        boosterDlls    = @(Get-ChildItem 'C:\ProgramData\Windhawk\Engine\Mods' -Recurse -Filter 'app-volume-booster_*' -EA SilentlyContinue).Count
    }
}

if ($Audit)   { $receipt.mode = 'audit' }
if ($Install) {
    $receipt.mode = 'install'
    Copy-Item $src "$bak\$id.wh.cpp.bak-$stamp"; Step "backed up current source to $bak"
    Copy-Item $pkg $src -Force; Step 'copied 1.3.0 source to ModsSource'
    Cli "mod compile $id"; Reload
    if (Test-Path $boostKey) { Cli '--yes mod remove app-volume-booster' } else { Step 'app-volume-booster already absent' }
}
if ($Rollback) {
    $receipt.mode = 'rollback'
    Copy-Item "$bak\$id.wh.cpp.bak-20261107-1015" $src -Force; Step 'restored 1.2.1 mixer source'
    Cli "mod compile $id"; Reload
    Copy-Item "$bak\app-volume-booster.wh.cpp.bak-20261107-1015" $boostSrc -Force
    & reg.exe import "$bak\booster-mods-key-20261107-1015.reg" 2>&1 | Out-Null; Step 'restored booster source and registry key'
    Cli 'mod compile app-volume-booster'
}
$receipt.state = State
$receipt.state.GetEnumerator() | ForEach-Object { Write-Output ("{0,-14} {1}" -f $_.Key, $_.Value) }
$out = "$root\reports\2026-11-07-volmixer-boost-$($receipt.mode)-$stamp.json"
$receipt | ConvertTo-Json -Depth 4 | Out-File $out -Encoding utf8
Write-Output "receipt: $out"
