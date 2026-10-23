<#
.SYNOPSIS
Credits DavidHiFi in the local@translucent-windows fork metadata, per docs\mod-style-guide.md.

The fork kept upstream's metadata (author Undisputed00x only). The style guide
requires @author to list DavidHiFi first, then the original creator, with the
@github link pointing at DavidHiFi, and a "Based on ..." line at the top of the
readme Credits section. Three byte-exact edits in each of the two source copies
(C:\ProgramData\Windhawk\ModsSource and the workspace dev copy):

  1. @author   Undisputed00x                     -> DavidHiFi, Undisputed00x
  2. @github   https://github.com/Undisputed00x  -> https://github.com/DavidHiFi
  3. Credits:  insert the Based-on line (plus the '#' separator the upstream
     readme uses) above the existing WinExperiments paragraph.

Name, id, description, version and the DLLs are untouched: the metadata block is
app-layer (the UI parses the source; the compiled DLLs keep their hashes and the
correct embedded id), exactly like the 2026-10-15 metadata-id fix.

Process (elevated, idempotent):
  1. backs up both source copies and the guard script,
  2. suspends the drift guard (it hashes ModsSource every 5 minutes),
  3. applies the three edits to both copies, byte-exact, line-start asserted,
  4. verifies the copies are identical and parse via windhawk-cli source meta,
  5. repoints the guard's $forkHash to the new source hash,
  6. writes a receipt and resumes the guard.

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
$rep       = Join-Path $ws 'reports\2026-10-16-translucent-windows-author-credit'
$bak       = Join-Path $ws 'backups\2026-10-16\translucent-windows-author-credit'
$cli       = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$oldHash   = 'F694DA98C260CCF01FF8C7E765463CC6F98F54A99010651C9B7FE8D9EFCD7878'

$oldAuthor = '// @author          Undisputed00x'
$newAuthor = '// @author          DavidHiFi, Undisputed00x'
$oldGithub = '// @github          https://github.com/Undisputed00x'
$newGithub = '// @github          https://github.com/DavidHiFi'
$creditAnchor = 'The custom theme is a close copy of the Rectify 11 theme created by'
$creditLine   = 'Based on [Translucent Windows](https://windhawk.net/mods/translucent-windows) by [Undisputed00x](https://github.com/Undisputed00x).'

function Get-Sha([string]$Path) { (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash }

function Edit-Source([string]$Path) {
    $nl = if ([System.IO.File]::ReadAllBytes($Path).Length -gt 1) { "`r`n" } else { "`n" }

    # Replace the first occurrence of $from with $to; $from must sit at a line
    # start and occur exactly once (except for the idempotent no-op cases).
    foreach ($pair in @(@($oldAuthor, $newAuthor), @($oldGithub, $newGithub))) {
        $from, $to = $pair
        $data = [System.IO.File]::ReadAllBytes($Path)
        $pat = [System.Text.Encoding]::UTF8.GetBytes($from)
        $rep2 = [System.Text.Encoding]::UTF8.GetBytes($to)
        $hits = @()
        for ($i = 0; $i -le $data.Length - $pat.Length; $i++) {
            if ($data[$i] -ne $pat[0]) { continue }
            $ok = $true
            for ($j = 1; $j -lt $pat.Length; $j++) { if ($data[$i + $j] -ne $pat[$j]) { $ok = $false; break } }
            if ($ok) { $hits += $i; $i += $pat.Length - 1 }
        }
        if ($hits.Count -eq 1) {
            if ($hits[0] -gt 0 -and $data[$hits[0] - 1] -ne 0x0A) { throw "pattern not at line start in $Path (offset $($hits[0]))" }
            $out = New-Object byte[] ($data.Length - $pat.Length + $rep2.Length)
            [Array]::Copy($data, 0, $out, 0, $hits[0])
            [Array]::Copy($rep2, 0, $out, $hits[0], $rep2.Length)
            [Array]::Copy($data, $hits[0] + $pat.Length, $out, $hits[0] + $rep2.Length, $data.Length - $hits[0] - $pat.Length)
            [System.IO.File]::WriteAllBytes($Path, $out)
            Write-Output "  $Path`: '$($from.Trim())' -> '$($to.Trim())'"
        }
        elseif ($hits.Count -eq 0) {
            # idempotent: accept only if the target text is already there
            $hasNew = ([System.Text.Encoding]::UTF8.GetString([System.IO.File]::ReadAllBytes($Path)) -like "*$to*")
            if (-not $hasNew) { throw "pattern not found in $Path and replacement absent: $($from.Trim())" }
            Write-Output "  $Path`: already has '$($to.Trim())'"
        }
        else { throw "pattern occurs $($hits.Count) times in ${Path}: $($from.Trim())" }
    }

    # Credits insert, also idempotent (skipped when the line is already present).
    $data = [System.IO.File]::ReadAllBytes($Path)
    $text = [System.Text.Encoding]::UTF8.GetString($data)
    $insert = $creditLine + $nl + '#' + $nl
    if ($text.Contains($insert)) {
        Write-Output "  $Path`: credits line already present"
    }
    else {
        $anchorIdx = $text.IndexOf($creditAnchor)
        if ($anchorIdx -lt 0) { throw "credits anchor not found in $Path" }
        if ($text.IndexOf($creditAnchor, $anchorIdx + 1) -ge 0) { throw 'credits anchor not unique' }
        if ($anchorIdx -gt 0 -and $text[$anchorIdx - 1] -ne "`n") { throw 'credits anchor not at line start' }
        $newText = $text.Remove($anchorIdx, 0).Insert($anchorIdx, $insert)
        [System.IO.File]::WriteAllBytes($Path, [System.Text.Encoding]::UTF8.GetBytes($newText))
        Write-Output "  $Path`: credits line inserted"
    }
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
            authorLines    = @((Select-String -LiteralPath $src, $dev -Pattern '^// @author').Line)
            githubLines    = @((Select-String -LiteralPath $src, $dev -Pattern '^// @github').Line)
            hasBasedOn     = @((Select-String -LiteralPath $src -Pattern ([regex]::Escape('Based on [Translucent Windows]'))).Count -gt 0)
        } | ConvertTo-Json
        return
    }

    if ($Action -eq 'Rollback') {
        if (-not (Test-Path (Join-Path $bak 'local@translucent-windows.wh.cpp'))) { throw 'backup missing' }
        New-Item -ItemType File -Path $suspend -Force | Out-Null
        Copy-Item (Join-Path $bak 'local@translucent-windows.wh.cpp') $src -Force
        Copy-Item (Join-Path $bak 'local@translucent-windows.wh.cpp') $dev -Force
        if ((Assert-CopiesIdentical) -ne $oldHash) { throw 'rollback hash mismatch' }
        # Restore the guard hash the same way Install replaced it.
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
        Add-Content -LiteralPath $glog -Value ("{0} author-credit change rolled back; source hash {1}; guard resumed" -f (Get-Date -Format o), $oldHash) -Encoding UTF8
        Remove-Item -LiteralPath $suspend -Force -ErrorAction SilentlyContinue
        return
    }

    # ---- Install ----
    if ((Get-Sha $src) -ne $oldHash -or (Get-Sha $dev) -ne $oldHash) {
        throw "unexpected source state: src=$((Get-Sha $src)), dev=$((Get-Sha $dev)) (expected $oldHash); run -Action Audit"
    }

    New-Item -ItemType Directory -Path $bak, $rep -Force | Out-Null
    Copy-Item $src (Join-Path $bak 'local@translucent-windows.wh.cpp') -Force
    Copy-Item $dev (Join-Path $bak 'local@translucent-windows.wh.cpp') -Force
    Copy-Item $guard (Join-Path $bak '2026-10-15-translucent-windows-guard.ps1') -Force
    Write-Output 'backed up: both source copies + guard script'

    New-Item -ItemType File -Path $suspend -Force | Out-Null
    Write-Output 'guard suspended'

    Write-Output 'editing ModsSource copy:'
    Edit-Source $src
    Write-Output 'editing dev copy:'
    Edit-Source $dev

    $newHash = Assert-CopiesIdentical
    if ($newHash -eq $oldHash) { throw 'source hash unchanged after edits' }
    Write-Output "new source hash: $newHash"

    # Parser check - the same metadata parser the UI uses.
    $meta = (& $cli source meta $src 2>&1) -join "`n"
    if ($LASTEXITCODE -ne 0) { throw "source meta failed: $meta" }
    if ($meta -notmatch 'id:\s*translucent-windows') { throw "unexpected id in parse result: $meta" }
    if ($meta -notmatch 'author:[^\r\n]*DavidHiFi[^\r\n]*Undisputed00x') { throw "author not parsed as expected: $meta" }
    Write-Output 'parser OK: id=translucent-windows, author=DavidHiFi, Undisputed00x'

    # Repoint the drift guard (exactly one occurrence of the old hash expected).
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

    # Engine state: mod still enabled, still no update offer.
    $list = (& $cli --json mod list 2>&1) -join "`n"
    $entry = $null
    try { $entry = ($list | ConvertFrom-Json) | Where-Object { $_.id -eq 'local@translucent-windows' -or $_.id -eq 'translucent-windows' } | Select-Object -First 1 } catch { }
    $engineOk = $null -ne $entry -and $entry.enabled -eq $true -and $entry.updateAvailable -eq $false
    if (-not $engineOk) { Write-Output "engine check inconclusive (non-fatal): $list" }

    [ordered]@{
        action             = 'author-credit-metadata-fix'
        date               = '2026-10-16'
        cause              = 'Fork metadata credited only the original author. Style guide: @author lists DavidHiFi first, then the original creator (Undisputed00x); @github points at DavidHiFi; readme Credits open with a Based-on line.'
        changed            = @($src, $dev, $guard)
        edits              = @('@author DavidHiFi, Undisputed00x', '@github https://github.com/DavidHiFi', 'Credits: Based on Translucent Windows by Undisputed00x')
        backup             = $bak
        oldSourceSha256    = $oldHash
        newSourceSha256    = $newHash
        parserCheck        = 'windhawk-cli source meta: id=translucent-windows, author=DavidHiFi, Undisputed00x'
        engineCheckEnabled = [bool]$engineOk
        dllsRebuilt        = $false
        dllHashes          = @('E42532BE147E15C5854B30C099CC9310D07C436FE4458CEA329044038764A0C4', '21E15343388283B0F69E37EB685E132793B72CC3D0DA4C3D90A40B5AC43F4D01')
    } | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $rep 'receipt.json') -Encoding UTF8

    Add-Content -LiteralPath $glog -Value ("{0} author credit added to metadata (DavidHiFi first per style guide); source hash {1}; guard resumed" -f (Get-Date -Format o), $newHash) -Encoding UTF8
    Remove-Item -LiteralPath $suspend -Force -ErrorAction SilentlyContinue
    Write-Output 'DONE'
}
catch {
    Write-Output "FAILED: $($_.Exception.Message)"
    try {
        Add-Content -LiteralPath $glog -Value ("{0} author-credit FAILED: {1}; guard left suspended" -f (Get-Date -Format o), $_.Exception.Message) -Encoding UTF8
    } catch { }
    exit 1
}
