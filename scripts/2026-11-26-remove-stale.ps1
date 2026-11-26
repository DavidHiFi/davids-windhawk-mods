# Removes stale Windhawk mods found by the 2026-11-26 audit (work\2026-11-26-mod-audit). Run elevated.
#   (no switch)  list what would go
#   -Install     turn each one off (Set-ModState.ps1 -Off), back up its key, source and DLLs, remove it
#   -Rollback    put every backed-up file and key back (they come back turned off)
param([switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$env:COOP_AGENT = 'edfb0d83-a11e-45d2-a626-d2bc5afb784b'
$root = 'H:\Windhawk Configuration'
$backup = Join-Path $root 'backups\2026-11-26-remove-stale'
$mods = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$data = 'C:\ProgramData\Windhawk'
$log = Join-Path $backup 'run.log'
# why each one is stale
$ids = [ordered]@{
  'local@helium-acrylic'             = 'off; merged into Seamless Chromium Browsers'
  'brave-acrylic'                    = 'off; merged into Seamless Chromium Browsers, Brave not installed'
  'edge-window-tab-manager-block'    = 'Edge (msedge.exe) not installed'
  'mspaint-dark'                     = 'Paint (mspaint.exe and the Store Paint) not installed'
  'notepad-dark-mode'                = 'Notepad (notepad.exe and the Store Notepad) not installed'
  'windows-sandbox-close-no-confirm' = 'Windows Sandbox not set up (no WindowsSandboxRemoteSession.exe)'
}
$keep = @('local@seamless-chromium-browsers', 'local@seamless-title-bars', 'local@seamless-workshop')
New-Item -ItemType Directory -Path $backup -Force | Out-Null
function Write-Log($m) { $m; $m | Add-Content -Path $log -Encoding utf8 }

if ($Rollback) {
  foreach ($f in Get-ChildItem "$backup\files" -File -Recurse) {
    $rel = $f.FullName.Substring(("$backup\files\").Length)
    $dst = Join-Path $data $rel; New-Item -ItemType Directory (Split-Path $dst) -Force | Out-Null
    Copy-Item -LiteralPath $f.FullName -Destination $dst -Force
  }
  foreach ($id in $ids.Keys) { if (Test-Path "$backup\$id.reg") { & reg.exe import "$backup\$id.reg"; Write-Log "restored $id" } }
  exit 0
}
foreach ($id in $keep) { if (!(Test-Path "$mods\$id")) { throw "Missing protected mod $id" } }
if (!$Install) { foreach ($id in $ids.Keys) { "REMOVE $id ($($ids[$id])) present=$(Test-Path "$mods\$id")" }; exit 0 }

$before = @{}; foreach ($id in $keep) { $before[$id] = Get-ItemProperty "$mods\$id" | Select-Object Disabled, LibraryFileName, Version }
$removed = @()
foreach ($id in $ids.Keys) {
  if (!(Test-Path "$mods\$id")) { Write-Log "skip $id (not installed)"; continue }
  if ((Get-ItemProperty "$mods\$id").Disabled -ne 1) {
    & "$root\scripts\Set-ModState.ps1" -Id $id -Off | ForEach-Object { Write-Log "  $_" }
    if ((Get-ItemProperty "$mods\$id").Disabled -ne 1) { throw "Could not turn off $id" }
  }
  & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$backup\$id.reg" /y | Out-Null
  if ($LASTEXITCODE) { throw "Export failed $id" }
  $files = @(Get-Item "$data\ModsSource\$id.wh.cpp" -ErrorAction SilentlyContinue)
  foreach ($arch in '64', '32', 'arm64') { $files += @(Get-ChildItem "$data\Engine\Mods\$arch" -Filter "$id`_*.dll" -ErrorAction SilentlyContinue) }
  foreach ($f in $files) {
    $rel = $f.FullName.Substring($data.Length + 1); $dst = Join-Path "$backup\files" $rel
    New-Item -ItemType Directory (Split-Path $dst) -Force | Out-Null; Copy-Item -LiteralPath $f.FullName -Destination $dst -Force
    if ((Get-FileHash $f.FullName).Hash -ne (Get-FileHash $dst).Hash) { throw "Backup mismatch $($f.Name)" }
  }
  $psi = New-Object System.Diagnostics.ProcessStartInfo
  $psi.FileName = 'C:\Program Files\Windhawk\windhawk-cli.exe'; $psi.Arguments = "--yes mod remove $id"
  $psi.UseShellExecute = $false; $psi.CreateNoWindow = $true; $psi.RedirectStandardOutput = $true; $psi.RedirectStandardError = $true
  $p = [System.Diagnostics.Process]::Start($psi); $o = $p.StandardOutput.ReadToEndAsync(); $e = $p.StandardError.ReadToEndAsync()
  if (!$p.WaitForExit(15000)) { $p.Kill(); throw "Removal timed out $id" }
  ($o.Result + $e.Result) | Set-Content "$backup\$id.log" -Encoding utf8
  if ($p.ExitCode -ne 0 -or (Test-Path "$mods\$id") -or (Test-Path "$data\ModsSource\$id.wh.cpp")) { throw "Removal failed $id (exit $($p.ExitCode))" }
  Write-Log "removed $id ($($files.Count) files backed up)"; $removed += $id
}
foreach ($id in $keep) {
  $after = Get-ItemProperty "$mods\$id" | Select-Object Disabled, LibraryFileName, Version
  if (($before[$id] | ConvertTo-Json -Compress) -ne ($after | ConvertTo-Json -Compress)) { throw "Protected state changed $id" }
}
@{ removed = $removed; why = $ids; preserved = $keep; verified = $true; time = (Get-Date -Format o)
   rollback = 'Run scripts\2026-11-26-remove-stale.ps1 -Rollback elevated' } | ConvertTo-Json -Depth 4 | Set-Content "$backup\receipt.json" -Encoding utf8
Write-Log "done: $($removed.Count) removed"
