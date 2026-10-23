# Window Manager: the in-mod Credits text names AltSnap's original author, Stefan Sundin,
# as well as RamonUnch. The @author line already lists him; this brings the readme in line.
# Run through Invoke-Elevated.ps1.
#
#   -Audit     report the match count, change nothing
#   -Install   back up once, apply, read back, write a receipt
#   -Rollback  restore the backup and verify its hash

[CmdletBinding()]
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'

$live = 'C:\ProgramData\Windhawk\ModsSource\local@window-manager.wh.cpp'
$dir = 'H:\Windhawk Configuration\backups\2026-10-13-window-manager-credit'
$backup = Join-Path $dir 'local@window-manager.wh.cpp.before'
$receipt = Join-Path $dir 'receipt.json'
$old = '[AltSnap](https://github.com/RamonUnch/AltSnap) by RamonUnch),'
$new = '[AltSnap](https://github.com/RamonUnch/AltSnap) by Stefan Sundin and RamonUnch),'

function Get-Hash([string]$p) { (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

$raw = [IO.File]::ReadAllText($live)
$oldN = ([regex]::Matches($raw, [regex]::Escape($old))).Count
$newN = ([regex]::Matches($raw, [regex]::Escape($new))).Count
"live file: $live"
"old credit matches: $oldN   new credit matches: $newN   sha256: $(Get-Hash $live)"

if ($Audit) { "audit only, nothing changed"; return }

if ($Rollback) {
  if (-not (Test-Path $backup)) { throw "no backup at $backup" }
  Copy-Item -LiteralPath $backup -Destination $live -Force
  $rc = Get-Content -LiteralPath $receipt -Raw | ConvertFrom-Json
  if ((Get-Hash $live) -ne $rc.sha256_before) { throw "rollback hash mismatch" }
  "rolled back; sha256 matches receipt"
  return
}

if (-not $Install) { throw "pass -Audit, -Install or -Rollback" }
if ($oldN -eq 0 -and $newN -eq 1) { "already applied, nothing to do"; return }
if ($oldN -ne 1) { throw "expected exactly one old credit, found $oldN" }

New-Item -ItemType Directory -Force -Path $dir | Out-Null
$before = Get-Hash $live
if (-not (Test-Path $backup)) { Copy-Item -LiteralPath $live -Destination $backup }

$b = [IO.File]::ReadAllBytes($live)
$bom = ($b.Length -ge 3 -and $b[0] -eq 0xEF -and $b[1] -eq 0xBB -and $b[2] -eq 0xBF)
[IO.File]::WriteAllText($live, $raw.Replace($old, $new), (New-Object System.Text.UTF8Encoding($bom)))

$after = [IO.File]::ReadAllText($live)
$ok = (([regex]::Matches($after, [regex]::Escape($new))).Count -eq 1) -and (([regex]::Matches($after, [regex]::Escape($old))).Count -eq 0)
if (-not $ok) { throw "read-back failed; restore with -Rollback" }

[pscustomobject]@{
  time = (Get-Date).ToString('o')
  file = $live
  action = 'Credits: add Stefan Sundin to the AltSnap line'
  sha256_before = $before
  sha256_after = Get-Hash $live
  backup = $backup
  verified = $ok
} | ConvertTo-Json | Set-Content -LiteralPath $receipt -Encoding UTF8
"applied and verified; receipt: $receipt"
