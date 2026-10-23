param(
    [switch]$Audit,
    [switch]$Apply,
    [string]$Rollback = ''
)

# Removes the saved "Size on disk" column (property System.FileAllocationSize, pid 18)
# from Explorer folder-view bags (ShellBags ColInfo values). Those saved views were
# written while the Size-on-disk mod was active, so folders keep showing the column
# after the mod is disabled.
#
# ColInfo layout (measured 2026-10-13):
#   bytes 0-39   header; uint32 column count at offset 32; uint32 entry size (24) at offset 36
#   bytes 40+    one 24-byte entry per column: property-set GUID (16), pid (4), width (4)
#
# Only the matching 24-byte entry is removed and the count is decremented. Every other
# byte, including column order and widths, is kept.
#
#   (no switch)  print what would change (same as -Audit)
#   -Audit       list every affected value; no writes
#   -Apply       export both Bags roots to backups (refuses to overwrite), then edit ColInfo
#                values; run with Explorer stopped (the cycle driver does that)
#   -Rollback d  import the two .reg exports from folder d

$ErrorActionPreference = 'Stop'
$roots = @(
    'HKCU:\Software\Microsoft\Windows\Shell\Bags',
    'HKCU:\Software\Classes\Local Settings\Software\Microsoft\Windows\Shell\Bags'
)
$regRoots = @(
    'HKCU\Software\Microsoft\Windows\Shell\Bags',
    'HKCU\Software\Classes\Local Settings\Software\Microsoft\Windows\Shell\Bags'
)
$backupDir = 'H:\Windhawk Configuration\backups\2026-10-13\explorer-lag\shellbags'
$storageFmt = [byte[]](0x30,0xF1,0x25,0xB7,0xEF,0x47,0x1A,0x10,0xA5,0xF1,0x02,0x60,0x8C,0x9E,0xEB,0xAC)
$sizeOnDiskPid = 18

function Get-Plan([byte[]]$d) {
    # Returns $null when the value is not a ColInfo we understand or has no Size-on-disk entry.
    if ($d.Length -lt 40 -or $d.Length % 8 -ne 0) { return $null }
    $count = [BitConverter]::ToUInt32($d, 32)
    $entrySize = [BitConverter]::ToUInt32($d, 36)
    if ($entrySize -ne 24 -or $d.Length -ne (40 + 24 * $count)) { return $null }
    $drop = @()
    for ($i = 0; $i -lt $count; $i++) {
        $off = 40 + 24 * $i
        $isStorage = $true
        for ($j = 0; $j -lt 16; $j++) { if ($d[$off + $j] -ne $storageFmt[$j]) { $isStorage = $false; break } }
        if ($isStorage -and [BitConverter]::ToUInt32($d, $off + 16) -eq $sizeOnDiskPid) { $drop += $i }
    }
    if ($drop.Count -eq 0) { return $null }
    $keep = New-Object System.Collections.Generic.List[byte]
    $keep.AddRange([byte[]]$d[0..39])
    for ($i = 0; $i -lt $count; $i++) {
        if ($drop -contains $i) { continue }
        $keep.AddRange([byte[]]$d[(40 + 24 * $i)..(40 + 24 * $i + 23)])
    }
    $new = $keep.ToArray()
    $newCount = [BitConverter]::GetBytes([uint32]($count - $drop.Count))
    [Array]::Copy($newCount, 0, $new, 32, 4)
    if ($new.Length -ne (40 + 24 * ($count - $drop.Count))) { throw 'internal length check failed' }
    return [pscustomobject]@{ New = $new; Removed = $drop.Count; OldCount = $count }
}

function Get-Affected {
    $list = @()
    foreach ($r in $roots) {
        if (-not (Test-Path -LiteralPath $r)) { continue }
        Get-ChildItem -LiteralPath $r -Recurse -ErrorAction SilentlyContinue | ForEach-Object {
            $key = $_
            if ($key.GetValueNames() -contains 'ColInfo' -and $key.GetValueKind('ColInfo') -eq 'Binary') {
                $d = [byte[]]$key.GetValue('ColInfo')
                $plan = Get-Plan $d
                if ($plan) { $list += [pscustomobject]@{ Path = $key.PSPath; Key = $key.Name; Plan = $plan } }
            }
        }
    }
    return $list
}

if ($Rollback) {
    foreach ($rr in $regRoots) {
        $file = Join-Path $Rollback (($rr -replace '[\\ ]', '_') + '.reg')
        if (-not (Test-Path -LiteralPath $file)) { throw "missing export: $file" }
        & reg.exe import $file | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "reg import failed: $file" }
        "imported $file"
    }
    return
}

$affected = Get-Affected
"values with Size on disk: $($affected.Count)"
"entries to remove: $(($affected | ForEach-Object { $_.Plan.Removed } | Measure-Object -Sum).Sum)"
if ($Audit -or -not $Apply) {
    $affected | ForEach-Object { '{0}  count {1} -> {2}' -f $_.Key, $_.Plan.OldCount, ($_.Plan.OldCount - $_.Plan.Removed) } | Select-Object -First 80
    return
}

New-Item -ItemType Directory -Force -Path $backupDir | Out-Null
for ($i = 0; $i -lt $regRoots.Count; $i++) {
    $file = Join-Path $backupDir (($regRoots[$i] -replace '[\\ ]', '_') + '.reg')
    if (Test-Path -LiteralPath $file) { throw "backup exists, refusing to overwrite: $file" }
    & reg.exe export $regRoots[$i] $file | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg export failed: $($regRoots[$i])" }
    "backup: $file"
}

foreach ($a in $affected) {
    Set-ItemProperty -LiteralPath $a.Path -Name ColInfo -Value $a.Plan.New -Type Binary
}

# Read back: no Size-on-disk entry may remain, and every count must match its length.
$left = Get-Affected
"readback: values still containing Size on disk: $($left.Count)"
"edited: $($affected.Count) values, $(($affected | ForEach-Object { $_.Plan.Removed } | Measure-Object -Sum).Sum) entries removed"
