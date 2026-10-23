# Taskbar AI Quota Bars Plus: readme wording only (no code change).
# Replaces "local to this machine" with the public sentence used in the repo, so the
# mod's readme on the machine matches GitHub. Run through Invoke-Elevated.ps1.
#
#   -Audit     report what would change, change nothing
#   -Install   back up once, apply, read back, write a receipt
#   -Rollback  restore the backup and verify its hash

[CmdletBinding()]
param([switch]$Audit, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'

$live = 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-ai-quota-plus.wh.cpp'
$dir = 'H:\Windhawk Configuration\backups\2026-10-13-ai-quota-readme'
$backup = Join-Path $dir 'local@taskbar-ai-quota-plus.wh.cpp.before'
$receipt = Join-Path $dir 'receipt.json'
$old = "Fork-specific changes are local to this machine; upstream issues and suggestions go to`n[the original mod](https://github.com/Cleroth/windhawk-taskbar-ai-quota/issues/new)."
$new = "Changes in this fork are developed in the DavidHiFi repository; upstream issues and`nsuggestions go to [the original mod](https://github.com/Cleroth/windhawk-taskbar-ai-quota/issues/new)."

function Get-Text([string]$p) {
  $raw = [IO.File]::ReadAllText($p)
  [pscustomobject]@{ Raw = $raw; Norm = $raw -replace "`r`n", "`n"; Crlf = $raw.Contains("`r`n") }
}
function Get-Hash([string]$p) { (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

$t = Get-Text $live
$oldN = ([regex]::Matches($t.Norm, [regex]::Escape($old))).Count
$newN = ([regex]::Matches($t.Norm, [regex]::Escape($new))).Count
"live file: $live"
"old sentence matches: $oldN   new sentence matches: $newN   sha256: $(Get-Hash $live)"

if ($Audit) { "audit only, nothing changed"; return }

if ($Rollback) {
  if (-not (Test-Path $backup)) { throw "no backup at $backup" }
  Copy-Item -LiteralPath $backup -Destination $live -Force
  $r = Get-Hash $live
  $rc = Get-Content -LiteralPath $receipt -Raw | ConvertFrom-Json
  if ($r -ne $rc.sha256_before) { throw "rollback hash mismatch: $r" }
  "rolled back; sha256 matches receipt"
  return
}

if (-not $Install) { throw "pass -Audit, -Install or -Rollback" }
if ($oldN -eq 0 -and $newN -eq 1) { "already applied, nothing to do"; return }
if ($oldN -ne 1) { throw "expected exactly one old sentence, found $oldN" }

New-Item -ItemType Directory -Force -Path $dir | Out-Null
$before = Get-Hash $live
if (-not (Test-Path $backup)) { Copy-Item -LiteralPath $live -Destination $backup }

$bom = (([IO.File]::ReadAllBytes($live))[0..2] -join ',') -eq '239,187,191'
$out = $t.Norm.Replace($old, $new)
if ($t.Crlf) { $out = $out -replace "`n", "`r`n" }
[IO.File]::WriteAllText($live, $out, (New-Object System.Text.UTF8Encoding($bom)))

$after = Get-Text $live
$ok = (([regex]::Matches($after.Norm, [regex]::Escape($new))).Count -eq 1) -and (([regex]::Matches($after.Norm, [regex]::Escape($old))).Count -eq 0)
if (-not $ok) { throw "read-back failed; restore with -Rollback" }

[pscustomobject]@{
  time = (Get-Date).ToString('o')
  file = $live
  action = 'readme sentence: local to this machine -> repo wording'
  sha256_before = $before
  sha256_after = Get-Hash $live
  backup = $backup
  verified = $ok
} | ConvertTo-Json | Set-Content -LiteralPath $receipt -Encoding UTF8
"applied and verified; receipt: $receipt"
