<#
.SYNOPSIS
Migrate the translucent-windows fork to a local@ id so the Windhawk catalog
machinery can no longer see it. The phantom "update to 1.8.2" offer and the
silent stock reinstalls both come from that machinery: userprofile.json tracked
the catalog id with latestVersion 1.8.2 (the real upstream latest by
Undisputed00x) against the installed custom 1.8.3, and the app treats any
difference as an update. The catalog's versions.json confirms 1.8.2 is the
latest published version; 1.8.3 only ever existed here.

What this does:
  1. suspends the drift guard (marker file),
  2. backs up the old key, source, both DLLs and userprofile.json,
  3. stages local@translucent-windows.wh.cpp from the reviewed fork source -
     the ONLY change is the @id line; code is byte-identical otherwise,
  4. removes the old id through windhawk-cli (the app's own uninstall, which
     also clears the profile entry, so nothing can be reconciled or offered),
  5. installs the new id through windhawk-cli (compiles locally, x86 + x64),
  6. restores all 156 Settings values plus ExcludeCustom from the backup,
     bumps SettingsChangeTime (UTC-correct),
  7. verifies registry, CLI mod list, profile entry and module census,
  8. writes a receipt. The guard stays suspended; the re-pointed guard script
     (2026-10-15-translucent-windows-guard.ps1) removes the marker on install.

Rollback: -Action Rollback (removes the new id, re-imports the old key,
restores source and DLLs).

Run elevated, e.g.:
  Invoke-Elevated.ps1 -File <this> -ArgumentList "-Action Install"
#>
[CmdletBinding()]
param(
    [ValidateSet('Audit', 'Install', 'Rollback')]
    [string]$Action = 'Audit'
)

$ErrorActionPreference = 'Stop'

$ws        = 'H:\Windhawk Configuration'
$cli       = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$oldId     = 'translucent-windows'
$newId     = 'local@translucent-windows'
$oldKeyReg = "HKLM\SOFTWARE\Windhawk\Engine\Mods\$oldId"
$oldKey    = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$oldId"
$newKey    = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$newId"
$oldSrc    = 'C:\ProgramData\Windhawk\ModsSource\translucent-windows.wh.cpp'
$devFork   = Join-Path $ws 'Windhawk\translucent-windows\translucent-windows.wh.cpp'
$devNew    = Join-Path $ws 'Windhawk\translucent-windows\local@translucent-windows.wh.cpp'
$mods64    = 'C:\ProgramData\Windhawk\Engine\Mods\64'
$mods32    = 'C:\ProgramData\Windhawk\Engine\Mods\32'
$oldDll    = 'translucent-windows_1.8.3_256343.dll'
$forkSha   = '70B64AF483BEB86C91B5D34213380BBE25579FD778C5BD2B15C44CFF5B6D851A'
$suspend   = 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend'
$date      = '2026-10-15'
$bkd       = Join-Path $ws "backups\$date\translucent-windows-id-migration"
$rep       = Join-Path $ws "reports\$date-translucent-windows-id-migration"
$log       = Join-Path $rep 'install.log'
$profileJ  = 'C:\ProgramData\Windhawk\userprofile.json'

function Write-Log([string]$m) {
    Add-Content -LiteralPath $log -Value ("{0} {1}" -f (Get-Date -Format o), $m) -Encoding UTF8
    Write-Output $m
}

function Get-Sha([string]$p) { (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash }

function Get-ProfileModNames {
    if (Test-Path $profileJ) {
        try {
            $mods = (Get-Content $profileJ -Raw | ConvertFrom-Json).mods
            if ($mods) { return @($mods.PSObject.Properties.Name) }
        } catch { }
    }
    return @()
}

New-Item $rep -ItemType Directory -Force | Out-Null

switch ($Action) {

    'Audit' {
        Write-Output "old key: $(Test-Path $oldKey)"
        Write-Output "new key: $(Test-Path $newKey)"
        Write-Output "old source: $(Test-Path $oldSrc)"
        if (Test-Path $oldKey) {
            $p = Get-ItemProperty $oldKey
            Write-Output "old lib=$($p.LibraryFileName) version=$($p.Version) disabled=$($p.Disabled)"
        }
        Write-Output "profile has old id: $(Get-ProfileModNames -contains $oldId)"
        Write-Output "profile has new id: $(Get-ProfileModNames -contains $newId)"
        Write-Output "guard suspended: $(Test-Path $suspend)"
    }

    'Install' {
        Write-Log '=== install start ==='
        New-Item $bkd -ItemType Directory -Force | Out-Null

        # 0. prechecks
        if ((Get-Service Windhawk -ErrorAction Stop).Status -ne 'Running') { throw 'Windhawk service not running' }
        if (-not (Test-Path $oldKey))  { throw "old key missing: $oldKey" }
        if (-not (Test-Path $oldSrc))  { throw "old source missing: $oldSrc" }
        if (-not (Test-Path $devFork)) { throw "reviewed fork missing: $devFork" }
        if (Test-Path $newKey)         { throw "new key already exists: $newKey" }
        $srcSha = Get-Sha $oldSrc
        if ($srcSha -ne $forkSha) { throw "installed source hash unexpected: $srcSha" }
        $oldProps = Get-ItemProperty $oldKey
        if ($oldProps.Version -ne '1.8.3') { throw "unexpected installed version: $($oldProps.Version)" }
        $settingsCount = (Get-Item "$oldKey\Settings").ValueCount
        Remove-Item (Join-Path (Split-Path $devFork) '_write-probe.txt') -Force -ErrorAction SilentlyContinue
        Write-Log "precheck ok: settings=$settingsCount lib=$($oldProps.LibraryFileName) excludeCustom=$($oldProps.ExcludeCustom)"

        # 1. suspend the drift guard before anything moves
        New-Item $suspend -ItemType File -Force | Out-Null
        Write-Log 'guard suspended'

        # 2. backup
        reg.exe export $oldKeyReg "$bkd\translucent-windows-before-migration.reg" /y | Out-Null
        if (-not (Test-Path "$bkd\translucent-windows-before-migration.reg")) { throw 'reg export failed' }
        Copy-Item $oldSrc "$bkd\translucent-windows.wh.cpp" -Force
        Copy-Item "$mods64\$oldDll" $bkd -Force
        Copy-Item "$mods32\$oldDll" $bkd -Force
        Copy-Item $profileJ "$bkd\userprofile.json.before" -Force
        Write-Log "backup done -> $bkd"

        # 3. stage the local@ source: only the @id line differs from the reviewed fork
        $bytes = [IO.File]::ReadAllBytes($devFork)
        $hasBom = ($bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF)
        $enc = New-Object System.Text.UTF8Encoding($hasBom)
        $text = $enc.GetString($bytes)
        if ($text[0] -eq [char]0xFEFF) { $text = $text.Substring(1) }
        $newText = $text -replace '(?m)^// @id(\s+)translucent-windows\s*$', ('// @id$1' + $newId)
        if ($newText -eq $text) { throw 'no @id replacement made' }
        [IO.File]::WriteAllText($devNew, $newText, $enc)
        [IO.File]::Copy($devNew, "$bkd\local@translucent-windows.wh.cpp", $true)
        $stagedSha = Get-Sha $devNew
        Write-Log "staged source: $stagedSha"

        # 4. remove the old id through the app (clears config, source, DLLs, profile entry)
        $out = & $cli mod remove $oldId --yes 2>&1
        $out | ForEach-Object { Write-Log "cli remove: $_" }
        if ($LASTEXITCODE -ne 0) { throw "mod remove failed (exit $LASTEXITCODE)" }
        if (Test-Path $oldKey) { throw 'old key still present after remove' }
        if (Test-Path $oldSrc) { throw 'old source still present after remove' }
        Write-Log 'old id removed'

        # 5. install the new id from the staged source (local compile, x86 + x64)
        $out = & $cli mod install --file $devNew 2>&1
        $out | ForEach-Object { Write-Log "cli install: $_" }
        if ($LASTEXITCODE -ne 0) { throw "mod install failed (exit $LASTEXITCODE)" }

        $lib = (Get-ItemProperty $newKey).LibraryFileName
        if (-not $lib) { throw 'new key has no LibraryFileName' }
        if (-not (Test-Path "$mods64\$lib")) { throw "missing x64 DLL: $mods64\$lib" }
        if (-not (Test-Path "$mods32\$lib")) { throw "missing x86 DLL: $mods32\$lib" }
        Write-Log "installed: $lib"

        # 6. restore settings from the backup (Settings sections only, key path rewritten)
        $lines = Get-Content "$bkd\translucent-windows-before-migration.reg"
        $outLines = New-Object System.Collections.Generic.List[string]
        $outLines.Add($lines[0])
        $keep = $false
        foreach ($line in $lines) {
            if ($line.StartsWith('[')) {
                $keep = ($line -eq "[HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\$oldId\Settings]")
                if ($keep) {
                    $outLines.Add($line.Replace("\Engine\Mods\$oldId", "\Engine\Mods\$newId"))
                }
            } elseif ($keep) {
                $outLines.Add($line)
            }
        }
        $settingsReg = Join-Path $rep 'settings-migrated.reg'
        $u16 = New-Object System.Text.UnicodeEncoding($true, $true)
        [IO.File]::WriteAllLines($settingsReg, $outLines, $u16)
        $kept = @($outLines | Where-Object { $_ -match '^("|@)' })
        Write-Log "settings filter captured $($kept.Count) value lines (old count $settingsCount)"
        if ($kept.Count -lt $settingsCount) { throw "settings filter dropped values ($($kept.Count) < $settingsCount)" }
        reg.exe import $settingsReg | Out-Null
        $newCount = (Get-Item "$newKey\Settings").ValueCount
        if ($newCount -ne $settingsCount) { throw "settings import mismatch: $newCount vs $settingsCount" }
        Write-Log "settings imported: $newCount values"

        if ($oldProps.ExcludeCustom) {
            Set-ItemProperty -Path $newKey -Name 'ExcludeCustom' -Value $oldProps.ExcludeCustom -Type String
            Write-Log "restored ExcludeCustom=$($oldProps.ExcludeCustom)"
        }
        foreach ($v in @('Exclude', 'Architecture')) {
            if ($oldProps.$v) {
                Set-ItemProperty -Path $newKey -Name $v -Value $oldProps.$v -Type String
                Write-Log "restored $v=$($oldProps.$v)"
            }
        }
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        Set-ItemProperty -Path $newKey -Name 'SettingsChangeTime' -Value $now -Type DWord
        Write-Log "SettingsChangeTime -> $now"

        # 7. verify
        $p = Get-ItemProperty $newKey
        if ($p.Version -ne '1.8.3')  { throw "new version mismatch: $($p.Version)" }
        if ($p.Disabled -ne 0)       { throw 'new mod is disabled' }
        if ($p.LibraryFileName -ne $lib) { throw 'LibraryFileName changed after settings import' }

        $listJson = (& $cli mod list --json 2>&1) -join "`n"
        if ($listJson -notmatch [regex]::Escape($newId)) { throw 'new id not present in mod list' }
        if ($listJson -match '(?<!local@)"translucent-windows"') { Write-Log 'WARN: old id still listed by mod list' }

        Start-Sleep -Seconds 2
        $names = Get-ProfileModNames
        if ($names -contains $oldId) { Write-Log 'WARN: profile entry for old id still present' } else { Write-Log 'profile entry for old id: gone' }
        if ($names -contains $newId) { Write-Log 'note: new id present in profile' } else { Write-Log 'new id not tracked in profile (expected for local@ ids)' }

        $newLoaded = 0; $oldLoaded = 0; $unopenable = 0
        Get-Process | ForEach-Object {
            try {
                foreach ($m in ($_.Modules | Where-Object { $_.ModuleName -like '*translucent-windows*' })) {
                    if ($m.ModuleName -like 'local@*') { $script:newLoaded++ } else { $script:oldLoaded++ }
                }
            } catch { $script:unopenable++ }
        }
        Write-Log "census: new=$newLoaded old=$oldLoaded unopenable=$unopenable"

        # 8. receipt (guard stays suspended; the new guard install clears the marker)
        $receipt = [ordered]@{
            action             = 'install'
            date               = $date
            oldId              = $oldId
            newId              = $newId
            oldSourceSha256    = $srcSha
            stagedSourceSha256 = $stagedSha
            libraryFileName    = $lib
            dll64Sha256        = Get-Sha "$mods64\$lib"
            dll32Sha256        = Get-Sha "$mods32\$lib"
            settingsCount      = $newCount
            excludeCustom      = $oldProps.ExcludeCustom
            profileOldEntryGone = -not ($names -contains $oldId)
            censusNewLoaded    = $newLoaded
            censusOldLoaded    = $oldLoaded
            backupDir          = $bkd
        }
        $receipt | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $rep 'receipt.json') -Encoding UTF8
        Write-Log '=== install done; guard remains suspended until the re-pointed guard is installed ==='
    }

    'Rollback' {
        Write-Log '=== rollback start ==='
        if (-not (Test-Path $bkd)) { throw "backup dir missing: $bkd" }
        New-Item $suspend -ItemType File -Force | Out-Null
        if (Test-Path $newKey) {
            $out = & $cli mod remove $newId --yes 2>&1
            $out | ForEach-Object { Write-Log "cli remove new: $_" }
        }
        reg.exe import "$bkd\translucent-windows-before-migration.reg" | Out-Null
        Copy-Item "$bkd\translucent-windows.wh.cpp" $oldSrc -Force
        Copy-Item "$bkd\translucent-windows_1.8.3_256343_64.dll" "$mods64\$oldDll" -Force
        Copy-Item "$bkd\translucent-windows_1.8.3_256343_32.dll" "$mods32\$oldDll" -Force
        $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
        Set-ItemProperty -Path $oldKey -Name 'SettingsChangeTime' -Value $now -Type DWord
        $p = Get-ItemProperty $oldKey
        Write-Log "rollback done: lib=$($p.LibraryFileName) version=$($p.Version) disabled=$($p.Disabled)"
        Write-Log 'NOTE: the guard suspend marker was left in place; remove it only when the guard watches the old id again.'
    }
}
