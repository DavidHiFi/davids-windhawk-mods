<#
.SYNOPSIS
Applies the metadata-updated Windhawk mod sources (author, github, homepage,
license) from staging over the live ModsSource files.

.DESCRIPTION
For each staged mod source: backs up the current file into
backups\2026-09-30\modsource\, copies the staged file into
C:\ProgramData\Windhawk\ModsSource, then verifies the copy by SHA256 and writes
a receipt. Metadata-only change; the Windhawk engine is not restarted and no
mod is rebuilt.

.PARAMETER Audit
Report what would change; write nothing.

.EXAMPLE
.\2026-09-30-apply-modsource-metadata.ps1 -Audit
.EXAMPLE
.\2026-09-30-apply-modsource-metadata.ps1
#>
[CmdletBinding()]
param([switch]$Audit)

$ErrorActionPreference = 'Stop'

$stage  = 'H:\Windhawk Configuration\Windhawk\staged\2026-09-30-modsource-metadata'
$target = 'C:\ProgramData\Windhawk\ModsSource'
$backup = 'H:\Windhawk Configuration\backups\2026-09-30\modsource'
$files  = @(
    'local@alt-snap-drag.wh.cpp',
    'local@taskbar-ai-quota-opencode.wh.cpp',
    'npp-taskdlg-textcolor.wh.cpp',
    'local@translucent-flyouts.wh.cpp'
)

$results = foreach ($f in $files) {
    $s = Join-Path $stage $f
    $t = Join-Path $target $f
    if (-not (Test-Path -LiteralPath $s)) { throw "staged file missing: $s" }
    if (-not (Test-Path -LiteralPath $t)) { throw "target file missing: $t" }

    $sHash = (Get-FileHash -LiteralPath $s -Algorithm SHA256).Hash
    $tHash = (Get-FileHash -LiteralPath $t -Algorithm SHA256).Hash
    $changed = ($tHash -ne $sHash)

    if ($Audit) {
        [pscustomobject]@{ file = $f; changed = $changed; oldSha256 = $tHash; newSha256 = $sHash; verified = $null }
    } else {
        if (-not (Test-Path -LiteralPath $backup)) { New-Item -ItemType Directory -Path $backup -Force | Out-Null }
        Copy-Item -LiteralPath $t -Destination (Join-Path $backup $f) -Force
        Copy-Item -LiteralPath $s -Destination $t -Force
        $newHash = (Get-FileHash -LiteralPath $t -Algorithm SHA256).Hash
        [pscustomobject]@{ file = $f; changed = $changed; oldSha256 = $tHash; newSha256 = $newHash; verified = ($newHash -eq $sHash) }
    }
}

$results | ForEach-Object { [pscustomobject]@{ file = $_.file; changed = $_.changed; old = $_.oldSha256.Substring(0, 12); new = $_.newSha256.Substring(0, 12); verified = $_.verified } } | Format-Table -AutoSize | Out-String | Write-Output

if (-not $Audit) {
    $receipt = [ordered]@{
        timestamp = (Get-Date).ToString('yyyy-MM-ddTHH:mm:sszzz')
        action    = 'ModsSource metadata apply: author/github/homepage/license'
        backupDir = $backup
        files     = @($results | ForEach-Object { [ordered]@{ file = $_.file; oldSha256 = $_.oldSha256; newSha256 = $_.newSha256; verified = $_.verified } })
    }
    $receipt | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $backup 'apply-receipt.json')
    Write-Output "receipt: $backup\apply-receipt.json"
    if (@($results | Where-Object { -not $_.verified }).Count) { Write-Output 'ERROR: verify failed'; exit 1 }
    Write-Output 'all copies verified'
}
