<#
.SYNOPSIS
Fixes the "Something went wrong / MODS_LOAD_FAILED" error for local@translucent-windows.

The app's metadata parser (shared by the UI and the CLI) rejects '@' inside the
@id line. For a local fork stored as local@<catalog-id>.wh.cpp, the @id line must
keep the CATALOG id - the local@ prefix lives only in the source filename and the
registry key (this is how every other local fork on this machine is shaped, e.g.
local@translucent-flyouts). The 2026-10-15 migration wrongly wrote the prefixed
id into @id, so the UI failed to load the mod's metadata and raised
MODS_LOAD_FAILED repeatedly. The engine itself was never affected (it reads the
compiled DLL, whose embedded id is correct).

This script (elevated, idempotent):
  1. suspends the drift guard (it hashes ModsSource every 5 minutes),
  2. rewrites the @id line in ModsSource and the workspace dev copy (byte-exact),
  3. verifies both copies are identical and parse via windhawk-cli source meta,
  4. updates the guard's $forkHash constant to the new source hash,
  5. writes a receipt, logs, and clears the guard suspend marker.
On failure the guard stays suspended (a resumed guard would heal-fight the new
source hash) and the failure is written to the guard log.

The DLLs are NOT rebuilt: the metadata block is app-layer; the compiled DLLs
already embed the correct local@translucent-windows id and their hashes are
unchanged.

Actions: Install (default) | Audit (read-only state print).
#>
[CmdletBinding()]
param(
    [ValidateSet('Install', 'Audit')]
    [string]$Action = 'Install'
)

$ErrorActionPreference = 'Stop'
$ws      = 'H:\Windhawk Configuration'
$src     = 'C:\ProgramData\Windhawk\ModsSource\local@translucent-windows.wh.cpp'
$dev     = Join-Path $ws 'Windhawk\translucent-windows\local@translucent-windows.wh.cpp'
$guard   = Join-Path $ws 'scripts\2026-10-15-translucent-windows-guard.ps1'
$suspend = 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend'
$glog    = 'C:\ProgramData\Windhawk\ModsWritable\translucent-windows-guard.log'
$rep     = Join-Path $ws 'reports\2026-10-15-translucent-windows-id-migration'
$cli     = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$oldHash = 'B6F8DF550AD7F01103B8FC234D83AEF268EE234779A1B0BAA738BE221EA7B080'
$oldId   = 'local@translucent-windows'
$newId   = 'translucent-windows'

function Get-Sha([string]$Path) { (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash }

# Byte-exact first-occurrence replace. Asserts the match starts a line so a
# substring elsewhere (e.g. in the readme) can never be rewritten. The Windhawk
# UI's failed-mod retry loop opens the source in bursts (the same loop that
# spams the toasts), so read and write both retry across lock windows.
function Replace-First([string]$Path, [string]$From, [string]$To) {
    $patB = [System.Text.Encoding]::ASCII.GetBytes($From)
    $newB = [System.Text.Encoding]::ASCII.GetBytes($To)
    for ($attempt = 1; $attempt -le 40; $attempt++) {
        $data = $null
        try { $data = [System.IO.File]::ReadAllBytes($Path) }
        catch [System.IO.IOException] { Start-Sleep -Milliseconds 700; continue }
        $limit = [Math]::Min($data.Length, 65536) - $patB.Length
        $found = -1
        for ($i = 0; $i -le $limit; $i++) {
            if ($data[$i] -ne $patB[0]) { continue }
            $ok = $true
            for ($j = 1; $j -lt $patB.Length; $j++) {
                if ($data[$i + $j] -ne $patB[$j]) { $ok = $false; break }
            }
            if ($ok) {
                if ($i -gt 0 -and $data[$i - 1] -ne 0x0A) { throw "match in $Path is not at a line start (offset $i)" }
                $found = $i
                break
            }
        }
        if ($found -lt 0) { throw "pattern not found in $Path" }
        $out = New-Object byte[] ($data.Length - $patB.Length + $newB.Length)
        [Array]::Copy($data, 0, $out, 0, $found)
        [Array]::Copy($newB, 0, $out, $found, $newB.Length)
        [Array]::Copy($data, $found + $patB.Length, $out, $found + $newB.Length, $data.Length - $found - $patB.Length)
        try {
            [System.IO.File]::WriteAllBytes($Path, $out)
            return $true
        }
        catch [System.IO.IOException] { Start-Sleep -Milliseconds 700; continue }
    }
    throw "could not rewrite ${Path}: still locked after 40 attempts (is the Windhawk window open?)"
}

try {
    if ($Action -eq 'Audit') {
        $idLine = [System.IO.File]::ReadLines($src) | Where-Object { $_ -match '^//\s*@id\s' } | Select-Object -First 1
        [ordered]@{
            srcHash        = Get-Sha $src
            devHash        = Get-Sha $dev
            guardSuspended = (Test-Path -LiteralPath $suspend)
            idLine         = $idLine
        } | ConvertTo-Json
        return
    }

    New-Item -ItemType File -Path $suspend -Force | Out-Null
    Write-Output 'guard suspended'

    $idLine = [System.IO.File]::ReadLines($src) | Where-Object { $_ -match '^//\s*@id\s' } | Select-Object -First 1
    if (-not $idLine) { throw 'no @id line found in the ModsSource copy' }

    if ($idLine -match ('^//\s*@id\s+' + [regex]::Escape($newId) + '\s*$')) {
        Write-Output 'source @id already fixed; skipping rewrite'
    }
    elseif ($idLine -match ('^//\s*@id\s+' + [regex]::Escape($oldId) + '\s*$')) {
        $fixed = $idLine.Replace($oldId, $newId)
        if (-not (Replace-First $src $idLine $fixed)) { throw '@id line bytes not found in ModsSource copy' }
        if (-not (Replace-First $dev $idLine $fixed)) { throw '@id line bytes not found in dev copy' }
        Write-Output "rewrote: '$idLine' -> '$fixed'"
    }
    else {
        throw "unexpected @id line: $idLine"
    }

    $srcHash = Get-Sha $src
    $devHash = Get-Sha $dev
    if ($srcHash -ne $devHash) { throw "copy mismatch after rewrite: $srcHash vs $devHash" }
    if ($srcHash -eq $oldHash) { throw 'source hash unchanged after rewrite' }
    Write-Output "new source hash: $srcHash"

    # Parser check - the same metadata parser the UI uses.
    $meta = (& $cli source meta $src 2>&1) -join "`n"
    if ($LASTEXITCODE -ne 0) { throw "source meta failed: $meta" }
    if ($meta -notmatch "id:\s*$([regex]::Escape($newId))") { throw "unexpected parse result: $meta" }
    Write-Output "parser OK: id=$newId"

    # Point the drift guard at the new hash (exactly one occurrence expected).
    $gb = [System.IO.File]::ReadAllBytes($guard)
    $hasBom = ($gb.Length -ge 3 -and $gb[0] -eq 0xEF -and $gb[1] -eq 0xBB -and $gb[2] -eq 0xBF)
    $enc = New-Object System.Text.UTF8Encoding($hasBom)
    $gtext = [System.IO.File]::ReadAllText($guard, $enc)
    $oldCount = ([regex]::Matches($gtext, [regex]::Escape($oldHash))).Count
    $newCount = ([regex]::Matches($gtext, [regex]::Escape($srcHash))).Count
    if ($oldCount -eq 1 -and $newCount -eq 0) {
        [System.IO.File]::WriteAllText($guard, $gtext.Replace($oldHash, $srcHash), $enc)
        Write-Output 'guard fork hash updated'
    }
    elseif ($oldCount -eq 0 -and $newCount -eq 1) {
        Write-Output 'guard fork hash already up to date'
    }
    else {
        throw "guard script in unexpected state: old hash x$oldCount, new hash x$newCount"
    }
    # Verify from disk, not from the in-memory string.
    $gverify = [System.IO.File]::ReadAllText($guard, $enc)
    if ($gverify -notmatch [regex]::Escape($srcHash) -or $gverify -match [regex]::Escape($oldHash)) {
        throw 'guard update verification failed'
    }

    [ordered]@{
        action          = 'metadata-id-fix'
        date            = '2026-10-15'
        cause           = 'UI MODS_LOAD_FAILED: metadata @id carried the local@ prefix; the parser (UI and CLI) rejects @ inside @id. Local forks keep the catalog id in @id; the prefix lives only in the filename and registry key.'
        changed         = @($src, $dev, $guard)
        oldSourceSha256 = $oldHash
        newSourceSha256 = $srcHash
        parserCheck     = 'windhawk-cli source meta: id=translucent-windows'
        dllsRebuilt     = $false
        dllHashes       = @('E42532BE147E15C5854B30C099CC9310D07C436FE4458CEA329044038764A0C4', '21E15343388283B0F69E37EB685E132793B72CC3D0DA4C3D90A40B5AC43F4D01')
    } | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $rep 'metadata-fix.json') -Encoding UTF8

    Add-Content -LiteralPath $glog -Value ("{0} metadata @id fixed (UI MODS_LOAD_FAILED cause); source hash {1}; guard resumed" -f (Get-Date -Format o), $srcHash) -Encoding UTF8
    Remove-Item -LiteralPath $suspend -Force -ErrorAction SilentlyContinue
    Write-Output 'DONE'
}
catch {
    Write-Output "FAILED: $($_.Exception.Message)"
    try {
        Add-Content -LiteralPath $glog -Value ("{0} metadata-fix FAILED: {1}; guard left suspended" -f (Get-Date -Format o), $_.Exception.Message) -Encoding UTF8
    } catch { }
    exit 1
}
