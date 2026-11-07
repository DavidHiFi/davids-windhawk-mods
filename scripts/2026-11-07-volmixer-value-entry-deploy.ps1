# Seamless Volume Mixer 1.3.1: type exact compressor values.
#   -Install   back up current source, copy the 1.3.1 work copy, compile, reload
#   -Rollback  restore the newest pre-1.3.1 backup, compile, reload
# Needs admin (run through Invoke-Elevated.ps1). Writes a receipt to reports\.
param([switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$root   = 'H:\Windhawk Configuration'
$id     = 'local@better-volume-mixer-plus'
$src    = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$pkg    = "$root\work\2026-11-07-volmixer-1.3.1\$id.wh.cpp"
$bak    = "$root\backups\$id.wh.cpp.pre-1.3.1"
$modKey = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$cli    = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$stamp  = Get-Date -Format 'yyyyMMdd-HHmm'
$log    = @()
function Step($m) { $script:log += $m; Write-Output $m }
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
    Set-ItemProperty $modKey -Name Disabled -Value 0 -Type DWord; Step 'reloaded (Disabled 1 -> 0)'
}
if ($Install) {
    if (-not (Test-Path $bak)) { Copy-Item $src $bak; Step "backed up to $bak" }
    Copy-Item $pkg $src -Force; Step 'copied 1.3.1 source'
    Cli "mod compile $id"; Reload
}
if ($Rollback) {
    Copy-Item $bak $src -Force; Step 'restored pre-1.3.1 source'
    Cli "mod compile $id"; Reload
}
$m = Get-ItemProperty $modKey
Step "version=$($m.Version) library=$($m.LibraryFileName)"
$log | Out-File "$root\reports\2026-11-07-volmixer-value-entry-$stamp.log" -Encoding utf8
