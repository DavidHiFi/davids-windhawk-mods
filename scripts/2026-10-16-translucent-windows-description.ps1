<#
.SYNOPSIS
Humanizes the local@translucent-windows fork description, per docs\mod-style-guide.md.

The fork still carries upstream's generic line ("Enables native translucent
effects in Windows 11"). Every other local mod names what the user gets, so
this rewrites it to: "Blur, acrylic and mica for app windows, with per-app
rules and custom themes" (76 chars, one line, no trailing period). All facts
come from the mod's own readme (Blur/Acrylic/Mica/MicaAlt effects, custom
theme rendering, per-process rules).

Metadata-only: no recompile, no DLL change, no settings touched. Same safe
process as the 2026-10-16 author-credit change: back up both source copies +
guard script, suspend the drift guard, apply one byte-exact edit to each copy,
verify identical + parser-clean, repoint the guard's $forkHash, receipt, resume.

Actions: Install (default) | Audit | Rollback.
#>
[CmdletBinding()]
param(
    [ValidateSet('Install', 'Audit', 'Rollback')]
    [string]$Action = 'Install'
)

$ErrorActionPreference = 'Stop'
$ws        = 'H:\Windhawk Configuration'
$src       = 'C:\ProgramData\Windhawk\ModsSource\local@translucent-windows.wh.cpp'
$dev       = Join-Path $ws 'Windhawk\translucent-windows\local@translucent-windows.wh.cpp'
$guard     = Join-Path $ws 'scripts\2026-10-15-translucent-windows-guard.ps1'
$suspend   = 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend'
$glog      = 'C:\ProgramData\Windhawk\ModsWritable\translucent-windows-guard.log'
$rep       = Join-Path $ws 'reports\2026-10-16-translucent-windows-description'
$bak       = Join-Path $ws 'backups\2026-10-16\translucent-windows-description'
$cli       = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$oldHash   = '90E6F83DE06D1720BF0FC8E542C0FC514660FF1888B085EA2D76ADF5B33986A1'

$oldDesc = '// @description     Enables native translucent effects in Windows 11'
$newDesc = '// @description     Blur, acrylic and mica for app windows, with per-app rules and custom themes'

function Get-Sha([string]$Path) { (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash }

function Edit-Description([string]$Path) {
    $data = [System.IO.File]::ReadAllBytes($Path)
    $pat = [System.Text.Encoding]::UTF8.GetBytes($oldDesc)
    $rep2 = [System.Text.Encoding]::UTF8.GetBytes($newDesc)
    $hits = @()
    for ($i = 0; $i -le $data.Length - $pat.Length; $i++) {
        if ($data[$i] -ne $pat[0]) { continue }
        $ok = $true
        for ($j = 1; $j -lt $pat.Length; $j++) { if ($data[$i + $j] -ne $pat[$j]) { $ok = $false; break } }
        if ($ok) { $hits += $i; $i += $pat.Length - 1 }
    }
    if ($hits.Count -eq 1) {
        if ($hits[0] -gt 0 -and $data[$hits[0] - 1] -ne 0x0A) { throw "pattern not at line start in $Path" }
        $out = New-Object byte[] ($data.Length - $pat.Length + $rep2.Length)
        [Array]::Copy($data, 0, $out, 0, $hits[0])
        [Array]::Copy($rep2, 0, $out, $hits[0], $rep2.Length)
        [Array]::Copy($data, $hits[0] + $pat.Length, $out, $hits[0] + $rep2.Length, $data.Length - $hits[0] - $pat.Length)
        [System.IO.File]::WriteAllBytes($Path, $out)
        Write-Output "  $Path`: description rewritten"
    }
    elseif ($hits.Count -eq 0) {
        $hasNew = ([System.Text.Encoding]::UTF8.GetString([System.IO.File]::ReadAllBytes($Path)) -like "*$newDesc*")
        if (-not $hasNew) { throw "description pattern not found in $Path and replacement absent" }
        Write-Output "  $Path`: already has the new description"
    }
    else { throw "description pattern occurs $($hits.Count) times in ${Path}" }
}

function Assert-CopiesIdentical {
    $srcHash = Get-Sha $src
    $devHash = Get-Sha $dev
    if ($srcHash -ne $devHash) { throw "copy mismatch: $srcHash vs $devHash" }
    return $srcHash
}

try {
    if ($Action -eq 'Audit') {
        [ordered]@{
            srcHash        = Get-Sha $src
            devHash        = Get-Sha $dev
            guardSuspended = (Test-Path -LiteralPath $suspend)
            descLines      = @((Select-String -LiteralPath $src, $dev -Pattern '^// @description').Line)
        } | ConvertTo-Json
        return
    }

    if ($Action -eq 'Rollback') {
        if (-not (Test-Path (Join-Path $bak 'local@translucent-windows.wh.cpp'))) { throw 'backup missing' }
        New-Item -ItemType File -Path $suspend -Force | Out-Null
        Copy-Item (Join-Path $bak 'local@translucent-windows.wh.cpp') $src -Force
        Copy-Item (Join-Path $bak 'local@translucent-windows.wh.cpp') $dev -Force
        if ((Assert-CopiesIdentical) -ne $oldHash) { throw 'rollback hash mismatch' }
        $gb = [System.IO.File]::ReadAllBytes($guard)
        $hasBom = ($gb.Length -ge 3 -and $gb[0] -eq 0xEF -and $gb[1] -eq 0xBB -and $gb[2] -eq 0xBF)
        $enc = New-Object System.Text.UTF8Encoding($hasBom)
        $gtext = [System.IO.File]::ReadAllText($guard, $enc)
        $curHash = (Select-String -LiteralPath $guard -Pattern '\$forkHash\s*=\s*''([0-9A-F]{64})''').Matches[0].Groups[1].Value
        if ($curHash -ne $oldHash) {
            if (([regex]::Matches($gtext, [regex]::Escape($curHash))).Count -ne 1) { throw 'guard hash not unique' }
            [System.IO.File]::WriteAllText($guard, $gtext.Replace($curHash, $oldHash), $enc)
        }
        Write-Output "rolled back to $oldHash; guard hash restored"
        Add-Content -LiteralPath $glog -Value ("{0} description change rolled back; source hash {1}; guard resumed" -f (Get-Date -Format o), $oldHash) -Encoding UTF8
        Remove-Item -LiteralPath $suspend -Force -ErrorAction SilentlyContinue
        return
    }

    # ---- Install ----
    if ((Get-Sha $src) -ne $oldHash -or (Get-Sha $dev) -ne $oldHash) {
        throw "unexpected source state: src=$((Get-Sha $src)), dev=$((Get-Sha $dev)) (expected $oldHash); run -Action Audit"
    }

    New-Item -ItemType Directory -Path $bak, $rep -Force | Out-Null
    Copy-Item $src (Join-Path $bak 'local@translucent-windows.wh.cpp') -Force
    Copy-Item $guard (Join-Path $bak '2026-10-15-translucent-windows-guard.ps1') -Force
    Write-Output 'backed up: ModsSource copy + guard script'

    New-Item -ItemType File -Path $suspend -Force | Out-Null
    Write-Output 'guard suspended'

    Write-Output 'editing ModsSource copy:'
    Edit-Description $src
    Write-Output 'editing dev copy:'
    Edit-Description $dev

    $newHash = Assert-CopiesIdentical
    if ($newHash -eq $oldHash) { throw 'source hash unchanged after edits' }
    Write-Output "new source hash: $newHash"

    $meta = (& $cli source meta $src 2>&1) -join "`n"
    if ($LASTEXITCODE -ne 0) { throw "source meta failed: $meta" }
    if ($meta -notmatch 'id:\s*translucent-windows') { throw "unexpected id in parse result: $meta" }
    if ($meta -notmatch '(?s)description:[^\r\n]*Blur, acrylic and mica') { throw "description not parsed as expected: $meta" }
    if ($meta -notmatch 'author:[^\r\n]*DavidHiFi[^\r\n]*Undisputed00x') { throw "author not parsed as expected: $meta" }
    Write-Output 'parser OK: id, description, author'

    $gb = [System.IO.File]::ReadAllBytes($guard)
    $hasBom = ($gb.Length -ge 3 -and $gb[0] -eq 0xEF -and $gb[1] -eq 0xBB -and $gb[2] -eq 0xBF)
    $enc = New-Object System.Text.UTF8Encoding($hasBom)
    $gtext = [System.IO.File]::ReadAllText($guard, $enc)
    $oldCount = ([regex]::Matches($gtext, [regex]::Escape($oldHash))).Count
    $newCount = ([regex]::Matches($gtext, [regex]::Escape($newHash))).Count
    if ($oldCount -eq 1 -and $newCount -eq 0) {
        [System.IO.File]::WriteAllText($guard, $gtext.Replace($oldHash, $newHash), $enc)
        Write-Output 'guard fork hash updated'
    }
    elseif ($oldCount -eq 0 -and $newCount -eq 1) {
        Write-Output 'guard fork hash already up to date'
    }
    else { throw "guard script in unexpected state: old x$oldCount, new x$newCount" }
    $gverify = [System.IO.File]::ReadAllText($guard, $enc)
    if ($gverify -notmatch [regex]::Escape($newHash) -or $gverify -match [regex]::Escape($oldHash)) { throw 'guard update verification failed' }

    $list = (& $cli --json mod list 2>$null) -join "`n"
    $entry = $null
    try { $entry = ($list | ConvertFrom-Json) | Where-Object { $_.id -eq 'local@translucent-windows' } | Select-Object -First 1 } catch { }
    $engineOk = $null -ne $entry -and $entry.enabled -eq $true -and $entry.updateAvailable -eq $false
    if (-not $engineOk) { Write-Output "engine check inconclusive (non-fatal): $($entry | ConvertTo-Json -Compress)" }
    else { Write-Output "engine OK: $($entry.id) $($entry.version), author $($entry.author), enabled, no update offer" }

    [ordered]@{
        action             = 'description-humanize'
        date               = '2026-10-16'
        cause              = 'Fork carried the generic upstream description. Style guide: one line, under ~100 chars, no trailing period, say what the user gets. New: Blur, acrylic and mica for app windows, with per-app rules and custom themes.'
        changed            = @($src, $dev, $guard)
        edits              = @('@description rewritten (76 chars, no trailing period)')
        backup             = $bak
        oldSourceSha256    = $oldHash
        newSourceSha256    = $newHash
        parserCheck        = 'windhawk-cli source meta: id, description, author OK'
        engineCheckEnabled = [bool]$engineOk
        dllsRebuilt        = $false
    } | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $rep 'receipt.json') -Encoding UTF8

    Add-Content -LiteralPath $glog -Value ("{0} description humanized per style guide; source hash {1}; guard resumed" -f (Get-Date -Format o), $newHash) -Encoding UTF8
    Remove-Item -LiteralPath $suspend -Force -ErrorAction SilentlyContinue
    Write-Output 'DONE'
}
catch {
    Write-Output "FAILED: $($_.Exception.Message)"
    try {
        Add-Content -LiteralPath $glog -Value ("{0} description FAILED: {1}; guard left suspended" -f (Get-Date -Format o), $_.Exception.Message) -Encoding UTF8
    } catch { }
    exit 1
}
