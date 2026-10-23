#Requires -Version 5.1
<#
  Organize E:\ Storage drive. Read-only dry-run by default.
  -Move  : perform moves, rewrite .lnk targets/working dirs, HKCU Classes
           shell commands, Explorer TypedPaths, Extreme Injector settings.xml,
           Notepad++ config.xml backup path, internal tool .lnk files.

  Never touches:
    E:\MessageLogger          (live Discord media sink, active writes)
    E:\Miscallaneous\Scripts  (canonical path: H:\Claude launchers, docs, self .lnk)
    system dirs               ($RECYCLE.BIN, Recovery, System Volume Information)
#>
[CmdletBinding(SupportsShouldProcess = $true)]
param(
  [switch]$Move,
  [string]$ManifestPath = "H:\System Configuration\backups\2026-09-24/e-drive-move-manifest.csv",
  [string]$LogPath = "H:\System Configuration\reports\2026-09-24-e-organize.log"
)

$ErrorActionPreference = 'Stop'
$manifest = [System.Collections.Generic.List[object]]::new()
$script:LogLines = [System.Collections.Generic.List[string]]::new()

function Write-Log([string]$msg) {
  $line = "[{0}] {1}" -f (Get-Date -Format 's'), $msg
  $script:LogLines.Add($line)
  Write-Host $line
}

function Ensure-Dir([string]$path) {
  if (-not (Test-Path -LiteralPath $path)) {
    if ($Move) {
      New-Item -ItemType Directory -Path $path -Force | Out-Null
      Write-Log "MKDIR $path"
    } else {
      Write-Log "MKDIR(dry) $path"
    }
  }
}

function Move-Safe {
  param(
    [Parameter(Mandatory)][string]$Source,
    [Parameter(Mandatory)][string]$DestinationDir
  )
  if (-not (Test-Path -LiteralPath $Source)) {
    Write-Log "SKIP missing $Source"
    return $null
  }
  $item = Get-Item -LiteralPath $Source -Force -ErrorAction Stop
  if (-not $Move) { Ensure-Dir $DestinationDir } else { Ensure-Dir $DestinationDir }
  $dest = Join-Path $DestinationDir $item.Name
  if (Test-Path -LiteralPath $dest) {
    $base = [System.IO.Path]::GetFileNameWithoutExtension($item.Name)
    $ext = [System.IO.Path]::GetExtension($item.Name)
    $n = 2
    do {
      $dest = Join-Path $DestinationDir ("{0} ({1}){2}" -f $base, $n, $ext)
      $n++
    } while (Test-Path -LiteralPath $dest)
  }
  if (-not $Move) {
    Write-Log "DRY  $Source -> $dest"
    $manifest.Add([pscustomobject]@{
      Action = 'Move'; Source = $Source; Dest = $dest
      Type = if ($item.PSIsContainer) { 'Dir' } else { 'File' }
      Bytes = if ($item.PSIsContainer) {
        (Get-ChildItem -LiteralPath $Source -Recurse -File -Force -EA SilentlyContinue | Measure-Object Length -Sum).Sum
      } else { $item.Length }
      Status = 'DryRun'
    })
    return $dest
  }
  try {
    Move-Item -LiteralPath $Source -Destination $dest -Force -ErrorAction Stop
    $bytes = if ($item.PSIsContainer) {
      (Get-ChildItem -LiteralPath $dest -Recurse -File -Force -EA SilentlyContinue | Measure-Object Length -Sum).Sum
    } else { $item.Length }
    $manifest.Add([pscustomobject]@{
      Action = 'Move'; Source = $Source; Dest = $dest
      Type = if ($item.PSIsContainer) { 'Dir' } else { 'File' }
      Bytes = $bytes; Status = 'Moved'
    })
    Write-Log "MOVE $Source -> $dest"
    return $dest
  } catch {
    $manifest.Add([pscustomobject]@{
      Action = 'Move'; Source = $Source; Dest = $dest
      Type = '?'; Bytes = 0; Status = "FAIL: $($_.Exception.Message)"
    })
    Write-Log "FAIL $Source :: $($_.Exception.Message)"
    return $null
  }
}

function Update-RegistryValue {
  param(
    [Parameter(Mandatory)][string]$Key,
    [Parameter(Mandatory)][string]$Name,
    [Parameter(Mandatory)][string]$OldPath,
    [Parameter(Mandatory)][string]$NewPath
  )
  try {
    $cur = (Get-ItemProperty -LiteralPath $Key -Name $Name -EA Stop).$Name
  } catch {
    return
  }
  if ($cur -isnot [string] -or -not $cur.Contains($OldPath)) { return }
  $new = $cur.Replace($OldPath, $NewPath)
  if ($new -eq $cur) { return }
  if (-not $Move) {
    $manifest.Add([pscustomobject]@{
      Action = 'Reg'; Source = "$Key\$Name"; Dest = $new
      Type = 'REG_SZ'; Bytes = 0; Status = 'DryRun'
    })
    Write-Log "DRY  REG $Key\$Name : $cur -> $new"
    return
  }
  try {
    Set-ItemProperty -LiteralPath $Key -Name $Name -Value $new -Type String -ErrorAction Stop
    $manifest.Add([pscustomobject]@{
      Action = 'Reg'; Source = "$Key\$Name"; Dest = $new
      Type = 'REG_SZ'; Bytes = 0; Status = 'Updated'
    })
    Write-Log "REG  $Key\$Name -> $new"
  } catch {
    $manifest.Add([pscustomobject]@{
      Action = 'Reg'; Source = "$Key\$Name"; Dest = $new
      Type = 'REG_SZ'; Bytes = 0; Status = "FAIL: $($_.Exception.Message)"
    })
    Write-Log "REG FAIL $Key\$Name :: $($_.Exception.Message)"
  }
}

function Update-ShortcutPaths {
  param(
    [Parameter(Mandatory)][string[]]$Roots,
    [Parameter(Mandatory)][hashtable]$PathMap
  )
  $sh = New-Object -ComObject WScript.Shell
  foreach ($root in $Roots) {
    if (-not (Test-Path -LiteralPath $root)) { continue }
    Get-ChildItem -LiteralPath $root -Recurse -Include *.lnk -File -EA SilentlyContinue | ForEach-Object {
      try { $s = $sh.CreateShortcut($_.FullName) } catch { return }
      $changed = $false
      foreach ($old in $PathMap.Keys) {
        $new = $PathMap[$old]
        $oldTrim = $old.TrimEnd('\')
        $newTrim = $new.TrimEnd('\')
        if ($s.TargetPath) {
          if ($s.TargetPath.Equals($oldTrim, [StringComparison]::OrdinalIgnoreCase)) {
            $s.TargetPath = $newTrim
            $changed = $true
          } elseif ($s.TargetPath.StartsWith($old, [StringComparison]::OrdinalIgnoreCase)) {
            $s.TargetPath = $new + $s.TargetPath.Substring($old.Length)
            $changed = $true
          }
        }
        if ($s.WorkingDirectory) {
          if ($s.WorkingDirectory.Equals($oldTrim, [StringComparison]::OrdinalIgnoreCase)) {
            $s.WorkingDirectory = $newTrim
            $changed = $true
          } elseif ($s.WorkingDirectory.StartsWith($old, [StringComparison]::OrdinalIgnoreCase)) {
            $s.WorkingDirectory = $new + $s.WorkingDirectory.Substring($old.Length)
            $changed = $true
          }
        }
      }
      if (-not $changed) { return }
      if (-not $Move) {
        $manifest.Add([pscustomobject]@{
          Action = 'Lnk'; Source = $_.FullName; Dest = $s.TargetPath
          Type = 'lnk'; Bytes = 0; Status = 'DryRun'
        })
        Write-Log "DRY  LNK $($_.FullName) -> $($s.TargetPath)"
        return
      }
      try {
        $s.Save()
        $manifest.Add([pscustomobject]@{
          Action = 'Lnk'; Source = $_.FullName; Dest = $s.TargetPath
          Type = 'lnk'; Bytes = 0; Status = 'Updated'
        })
        Write-Log "LNK  $($_.FullName) -> $($s.TargetPath)"
      } catch {
        $manifest.Add([pscustomobject]@{
          Action = 'Lnk'; Source = $_.FullName; Dest = $s.TargetPath
          Type = 'lnk'; Bytes = 0; Status = "FAIL: $($_.Exception.Message)"
        })
        Write-Log "LNK FAIL $($_.FullName) :: $($_.Exception.Message)"
      }
    }
  }
}

function Update-TextPaths {
  param(
    [Parameter(Mandatory)][string]$Path,
    [Parameter(Mandatory)][hashtable]$PathMap,
    [string]$Label = 'Text'
  )
  if (-not (Test-Path -LiteralPath $Path)) { return }
  $raw = Get-Content -LiteralPath $Path -Raw -EA SilentlyContinue
  if (-not $raw) { return }
  $new = $raw
  $matched = $false
  foreach ($old in $PathMap.Keys) {
    if ($new.Contains($old)) {
      $new = $new.Replace($old, $PathMap[$old])
      $matched = $true
    }
  }
  if (-not $matched) { return }
  if (-not $Move) {
    $manifest.Add([pscustomobject]@{
      Action = $Label; Source = $Path; Dest = '(path rewrite)'
      Type = 'file'; Bytes = 0; Status = 'DryRun'
    })
    Write-Log "DRY  $Label rewrite $Path"
    return
  }
  try {
    Set-Content -LiteralPath $Path -Value $new -NoNewline -Encoding UTF8 -ErrorAction Stop
    $manifest.Add([pscustomobject]@{
      Action = $Label; Source = $Path; Dest = '(path rewrite)'
      Type = 'file'; Bytes = 0; Status = 'Updated'
    })
    Write-Log "$Label rewrite $Path"
  } catch {
    $manifest.Add([pscustomobject]@{
      Action = $Label; Source = $Path; Dest = '(path rewrite)'
      Type = 'file'; Bytes = 0; Status = "FAIL: $($_.Exception.Message)"
    })
    Write-Log "$Label FAIL $Path :: $($_.Exception.Message)"
  }
}

Write-Log "=== E: organize start Move=$Move ==="

# ---------- path map: old absolute prefix -> new ----------
# Live portable tools move under E:\Software with link/registry rewrite.
# MessageLogger and Miscallaneous\Scripts stay (not in this map).
$pathMap = [ordered]@{
  'E:\Cold War Stuffs\'       = 'E:\Software\Cold War Stuffs\'
  'E:\Cherax\'                = 'E:\Software\Cherax\'
  'E:\Sordum Software Suite\' = 'E:\Software\Sordum Software Suite\'
  'E:\nvidiaProfileInspector\' = 'E:\Software\nvidiaProfileInspector\'
  'E:\NVPI-R\'                = 'E:\Software\NVPI-R\'
  'E:\Notepad++\'             = 'E:\Software\Notepad++\'
  # archive moves keep the leaf folder name (Move-Safe appends Name under Dest)
  'E:\SteaMidra\'             = 'E:\_Archive\01-Backups\SteaMidra\'
  'E:\UniGet UI\'             = 'E:\_Archive\01-Backups\UniGet UI\'
  'E:\Everything Database\'   = 'E:\_Archive\01-Backups\Everything Database\'
  'E:\Windhawk\'              = 'E:\_Archive\02-Software\Windhawk\'
  'E:\PowerToys\'             = 'E:\_Archive\02-Software\PowerToys\'
  'E:\FabFilter Presets\'     = 'E:\_Archive\05-Audio\FabFilter Presets\'
}

# ---------- 1. Category tree ----------
$roots = [ordered]@{
  Software = 'E:\Software'
  Backups  = 'E:\_Archive\01-Backups'
  SoftArch = 'E:\_Archive\02-Software'
  Games    = 'E:\_Archive\03-Games'
  Misc     = 'E:\_Archive\04-Misc'
  Audio    = 'E:\_Archive\05-Audio'
  Config   = 'E:\_Archive\06-Config'
}
foreach ($k in $roots.Keys) { Ensure-Dir $roots[$k] }

# ---------- 2. Move live portable tools -> E:\Software ----------
# (shortcuts + HKCU Classes + TypedPaths rewritten after these)
$softwareMoves = [ordered]@{
  'Cold War Stuffs'       = $roots.Software
  'Cherax'                = $roots.Software
  'Sordum Software Suite' = $roots.Software
  'nvidiaProfileInspector' = $roots.Software
  'NVPI-R'                = $roots.Software
  'Notepad++'             = $roots.Software
}
foreach ($name in $softwareMoves.Keys) {
  $src = "E:\$name"
  if (Test-Path -LiteralPath $src) { Move-Safe -Source $src -DestinationDir $softwareMoves[$name] | Out-Null }
}

# ---------- 3. Move archive / backup / notes content ----------
$archiveMoves = @(
  @{ Src = 'E:\SteaMidra';        Dst = $roots.Backups }
  @{ Src = 'E:\UniGet UI';        Dst = $roots.Backups }
  @{ Src = 'E:\Everything Database'; Dst = $roots.Backups }
  @{ Src = 'E:\Windhawk';         Dst = $roots.SoftArch }
  @{ Src = 'E:\PowerToys';        Dst = $roots.SoftArch }
  @{ Src = 'E:\FabFilter Presets'; Dst = $roots.Audio }
)
foreach ($m in $archiveMoves) {
  if (Test-Path -LiteralPath $m.Src) { Move-Safe -Source $m.Src -DestinationDir $m.Dst | Out-Null }
}

# ---------- 4. Miscallaneous: keep Scripts; move everything else ----------
$misc = 'E:\Miscallaneous'
$scriptsKeep = Join-Path $misc 'Scripts'
if (Test-Path -LiteralPath $misc) {
  # nested stale Everything DB under Misc (same leaf name as root DB -> suffix on collision handled by Move-Safe)
  $miscEdb = Join-Path $misc 'Everything Database'
  if (Test-Path -LiteralPath $miscEdb) {
    Move-Safe -Source $miscEdb -DestinationDir $roots.Backups | Out-Null
  }
  # child dirs (except Scripts and already-moved EDB)
  Get-ChildItem -LiteralPath $misc -Directory -Force -EA SilentlyContinue | ForEach-Object {
    if ($_.FullName -ieq $scriptsKeep) {
      Write-Log "PROTECT $($_.FullName) (canonical Scripts path)"
      return
    }
    if ($_.Name -ieq 'Everything Database') { return }
    $n = $_.Name
    $dst = if ($n -match 'Assassin|CE Table|Cheat') {
      $roots.Games
    } elseif ($n -match 'CoD|FF Tool|fastfile') {
      $roots.Games
    } else {
      $roots.Misc
    }
    Move-Safe -Source $_.FullName -DestinationDir $dst | Out-Null
  }
  # loose files in Misc root -> Misc archive (regs / tools)
  Get-ChildItem -LiteralPath $misc -File -Force -EA SilentlyContinue | ForEach-Object {
    $dst = if ($_.Extension -eq '.reg') { $roots.Config } else { $roots.Misc }
    Move-Safe -Source $_.FullName -DestinationDir $dst | Out-Null
  }
}

# ---------- 5. Rewrite external shortcuts (Desktop / Start Menu / H:\Claude) ----------
# Scripts launchers under H:\Claude must NOT be rewritten (Scripts not in pathMap).
$lnkRoots = @(
  'H:\Claude'
  "$env:USERPROFILE\Desktop"
  'C:\Users\Public\Desktop'
  "$env:APPDATA\Microsoft\Windows\Start Menu"
  'C:\ProgramData\Microsoft\Windows\Start Menu'
  "$env:APPDATA\Microsoft\Internet Explorer\Quick Launch"
)
# Apply pathMap only to tool prefixes; Scripts path never appears in pathMap.
$pathMapHashtable = @{}
foreach ($k in $pathMap.Keys) { $pathMapHashtable[$k] = $pathMap[$k] }
Update-ShortcutPaths -Roots $lnkRoots -PathMap $pathMapHashtable

# ---------- 6. Rewrite internal .lnk under moved Software tools ----------
if (Test-Path -LiteralPath $roots.Software) {
  Update-ShortcutPaths -Roots @($roots.Software) -PathMap $pathMapHashtable
}

# ---------- 7. HKCU\Software\Classes shell commands (.nip openers) ----------
Update-RegistryValue -Key 'HKCU:\Software\Classes\Applications\nvidiaProfileInspector.exe\DefaultIcon' -Name '(default)' `
  -OldPath 'E:\nvidiaProfileInspector\' -NewPath 'E:\Software\nvidiaProfileInspector\'
Update-RegistryValue -Key 'HKCU:\Software\Classes\Applications\nvidiaProfileInspector.exe\shell\open\command' -Name '(default)' `
  -OldPath 'E:\nvidiaProfileInspector\' -NewPath 'E:\Software\nvidiaProfileInspector\'
Update-RegistryValue -Key 'HKCU:\Software\Classes\Applications\NVPI-R.exe\DefaultIcon' -Name '(default)' `
  -OldPath 'E:\NVPI-R\' -NewPath 'E:\Software\NVPI-R\'
Update-RegistryValue -Key 'HKCU:\Software\Classes\Applications\NVPI-R.exe\shell\open\command' -Name '(default)' `
  -OldPath 'E:\NVPI-R\' -NewPath 'E:\Software\NVPI-R\'

# ---------- 8. Explorer TypedPaths (MRU address bar) ----------
$typed = 'HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\TypedPaths'
try {
  $vals = Get-ItemProperty -LiteralPath $typed -EA Stop
  foreach ($p in $vals.PSObject.Properties) {
    if ($p.Name -notlike 'url*') { continue }
    $v = [string]$p.Value
    $nv = $v
    foreach ($old in $pathMap.Keys) {
      $oldTrim = $old.TrimEnd('\')
      if ($nv.Equals($oldTrim, [StringComparison]::OrdinalIgnoreCase)) {
        $nv = $pathMap[$old].TrimEnd('\')
        break
      }
      if ($nv.StartsWith($old, [StringComparison]::OrdinalIgnoreCase)) {
        $nv = $pathMap[$old] + $nv.Substring($old.Length)
        break
      }
    }
    if ($nv -eq $v) { continue }
    if (-not $Move) {
      Write-Log "DRY  TypedPaths $($p.Name): $v -> $nv"
      $manifest.Add([pscustomobject]@{ Action = 'TypedPath'; Source = $p.Name; Dest = $nv; Type = 'REG_SZ'; Bytes = 0; Status = 'DryRun' })
      continue
    }
    try {
      Set-ItemProperty -LiteralPath $typed -Name $p.Name -Value $nv -Type String -ErrorAction Stop
      Write-Log "TypedPath $($p.Name) -> $nv"
      $manifest.Add([pscustomobject]@{ Action = 'TypedPath'; Source = $p.Name; Dest = $nv; Type = 'REG_SZ'; Bytes = 0; Status = 'Updated' })
    } catch {
      Write-Log "TypedPath FAIL $($p.Name) :: $($_.Exception.Message)"
      $manifest.Add([pscustomobject]@{ Action = 'TypedPath'; Source = $p.Name; Dest = $nv; Type = 'REG_SZ'; Bytes = 0; Status = "FAIL: $($_.Exception.Message)" })
    }
  }
} catch {
  Write-Log "TypedPaths skip :: $($_.Exception.Message)"
}

# ---------- 9. App config path rewrites ----------
# Extreme Injector module paths
Update-TextPaths -Path 'E:\Software\Cold War Stuffs\Extreme Injector\settings.xml' -PathMap $pathMapHashtable -Label 'ExtInject'
# Notepad++ backup/openSaveDir (config moved with folder)
Update-TextPaths -Path 'E:\Software\Notepad++\config.xml' -PathMap $pathMapHashtable -Label 'Notepad++'
# If dry-run, also rewrite in-place path in original location if still present
if (-not $Move) {
  Update-TextPaths -Path 'E:\Cold War Stuffs\Extreme Injector\settings.xml' -PathMap $pathMapHashtable -Label 'ExtInject'
  Update-TextPaths -Path 'E:\Notepad++\config.xml' -PathMap $pathMapHashtable -Label 'Notepad++'
}

# ---------- 10. Write outputs ----------
if ($manifest.Count -gt 0) {
  $dir = Split-Path $ManifestPath -Parent
  Ensure-Dir $dir
  if (-not (Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
  $manifest | Export-Csv -LiteralPath $ManifestPath -NoTypeInformation -Encoding UTF8
  Write-Log "Manifest: $ManifestPath ($($manifest.Count) rows)"
}
$dir = Split-Path $LogPath -Parent
if (-not (Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
$script:LogLines | Out-File -LiteralPath $LogPath -Encoding utf8

# ---------- 11. Post summary (file/byte counts excl. system dirs) ----------
$sysNames = @('$RECYCLE.BIN', 'Recovery', 'System Volume Information')
$files = Get-ChildItem 'E:\' -Recurse -File -Force -EA SilentlyContinue |
  Where-Object { $ok = $true; foreach ($s in $sysNames) { if ($_.FullName -like "E:\$s\*") { $ok = $false; break } }; $ok }
$sum = $files | Measure-Object -Sum Length
Write-Log "POST files=$($sum.Count) bytes=$($sum.Sum)"
Write-Log "=== done Move=$Move ==="
