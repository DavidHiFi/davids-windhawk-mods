# Sync the davids-windhawk-mods settings snapshot's windows-11-taskbar-styler
# block to the live registry values for this mod.
# -Diff:  print-only comparison.
# -Apply: patch settings/mods-settings.json (sysTraySpacing, taskbarFill, and
#         the 17 controlStyles[60..65] entries missing since the tray-gap
#         session), validate the JSON, and re-diff. Refuses unless each needle
#         matches exactly once and every patch lands.
param([Parameter(Position = 0)][ValidateSet('Diff', 'Apply')][string]$Mode = 'Diff')
$ErrorActionPreference = 'Stop'
$repo = 'H:\Windhawk Configuration\davids-windhawk-mods'
$file = "$repo\settings\mods-settings.json"
$modId = 'windows-11-taskbar-styler'
$liveKey = 'Registry::HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'

function Get-SnapshotBlock {
  $doc = Get-Content $file -Raw | ConvertFrom-Json
  $block = $doc.$modId
  $snap = @{}
  foreach ($p in $block.PSObject.Properties) { $snap[$p.Name] = [string]$p.Value }
  $snap
}

function Get-LiveValues {
  $live = @{}
  $item = Get-Item $liveKey
  foreach ($n in $item.GetValueNames()) { $live[$n] = [string]$item.GetValue($n) }
  $live
}

function Show-Diff {
  $snap = Get-SnapshotBlock
  $live = Get-LiveValues
  "snapshot-only keys (in snapshot, not in live registry):"
  foreach ($k in $snap.Keys) { if (-not $live.ContainsKey($k)) { "  $k = $($snap[$k])" } }
  "live-only keys (in live registry, missing from snapshot):"
  foreach ($k in $live.Keys) { if (-not $snap.ContainsKey($k)) { "  $k = $($live[$k])" } }
  "value mismatches:"
  foreach ($k in $snap.Keys) {
    if ($live.ContainsKey($k) -and $snap[$k] -ne $live[$k]) {
      "  $k"
      "    snapshot: $($snap[$k])"
      "    live:     $($live[$k])"
    }
  }
  "counts: snapshot $($snap.Count), live $($live.Count)"
}

# The 17 live-only values, in the registry's own enumeration order, so the
# snapshot keeps mirroring registry order.
$appendValues = [ordered]@{
  'controlStyles[60].target' = '//'
  'controlStyles[60].styles[0]' = '//'
  'controlStyles[61].target' = 'SystemTray.OmniButton#ControlCenterButton'
  'controlStyles[61].styles[0]' = 'Margin=0,0,-10,0'
  'controlStyles[62].target' = '//'
  'controlStyles[62].styles[0]' = 'Visibility=Collapsed'
  'controlStyles[61].styles[1]' = '//'
  'controlStyles[60].styles[1]' = '//'
  'controlStyles[61].styles[2]' = '//'
  'controlStyles[63].target' = '//'
  'controlStyles[60].styles[9]' = '//'
  'controlStyles[64].target' = '//'
  'controlStyles[64].styles[0]' = '//'
  'controlStyles[65].target' = '//'
  'controlStyles[65].styles[0]' = '//'
  'controlStyles[60].styles[2]' = '//'
  'controlStyles[61].styles[9]' = '//'
}

# Needle/replacement pairs, matching the file's own JSON escaping.
$needleSpacing = '    "styleConstants[9]": "sysTraySpacing = 6",'
$newSpacing = '    "styleConstants[9]": "sysTraySpacing = 0",'
$needleFill = '    "styleConstants[18]": "taskbarFill = <WindhawkBlur BlurAmount=\"80\" TintColor=\"#1E1E2E\" TintOpacity=\"0.92\" TintLuminosityOpacity=\"0.8\" FallbackColor=\"#EB1E1E2E\"/>",'
$newFill = '    "styleConstants[18]": "taskbarFill = <WindhawkBlur BlurAmount=\"110\" TintColor=\"#1E1E2E\" TintOpacity=\"0.75\" TintLuminosityOpacity=\"0.8\" FallbackColor=\"#BF1E1E2E\"/>",'

switch ($Mode) {
  'Diff' { Show-Diff }
  'Apply' {
    # Preserve the file's exact encoding and line endings.
    $bytes = [System.IO.File]::ReadAllBytes($file)
    $hasBom = $bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF
    $raw = [System.IO.File]::ReadAllText($file)
    $eol = if ($raw.Contains("`r`n")) { "`r`n" } else { "`n" }
    $lines = [System.Collections.Generic.List[string]]($raw -split "`r`n|`n")

    $c1 = ([regex]::Matches($raw, [regex]::Escape($needleSpacing))).Count
    $c2 = ([regex]::Matches($raw, [regex]::Escape($needleFill))).Count
    if ($c1 -ne 1 -or $c2 -ne 1) { throw "needle count mismatch: spacing=$c1 fill=$c2 (must each be 1)" }

    # Find the snapshot-line for controlStyles[59].styles[0] directly followed
    # by the block's closing brace. Match by prefix: the value holds an
    # invisible PUA glyph, so only the prefix is safe to compare.
    $tailIndex = -1
    for ($i = 0; $i -lt $lines.Count - 1; $i++) {
      if ($lines[$i].StartsWith('    "controlStyles[59].styles[0]": "Text=') -and $lines[$i + 1] -eq '  },') {
        $tailIndex = $i
        break
      }
    }
    if ($tailIndex -lt 0) { throw 'tail insertion point not found' }

    $newLines = [System.Collections.Generic.List[string]]::new()
    for ($i = 0; $i -lt $lines.Count; $i++) {
      $line = $lines[$i]
      if ($line -eq $needleSpacing) { $newLines.Add($newSpacing) }
      elseif ($line -eq $needleFill) { $newLines.Add($newFill) }
      else { $newLines.Add($line) }
      if ($i -eq $tailIndex) {
        # The tail line was the block's last property and has no trailing
        # comma; the inserted keys now follow it, so it needs one. The last
        # inserted key stays comma-less because the block closes after it.
        if (-not $newLines[$newLines.Count - 1].EndsWith(',')) { $newLines[$newLines.Count - 1] += ',' }
        $keys = @($appendValues.Keys)
        for ($j = 0; $j -lt $keys.Count; $j++) {
          $k = $keys[$j]
          $v = $appendValues[$k] -replace '\\', '\\' -replace '"', '\"'
          $comma = if ($j -lt $keys.Count - 1) { ',' } else { '' }
          $newLines.Add('    "' + $k + '": "' + $v + '"' + $comma)
        }
      }
    }

    $tailEol = if ($raw.EndsWith("`n")) { $eol } else { '' }
    $out = ($newLines -join $eol) + $tailEol
    $enc = if ($hasBom) { [System.Text.UTF8Encoding]::new($true) } else { [System.Text.UTF8Encoding]::new($false) }
    [System.IO.File]::WriteAllText($file, $out, $enc)

    # Validate: parses as JSON and the block now matches the registry.
    $null = Get-Content $file -Raw | ConvertFrom-Json
    "APPLY OK: JSON valid. Post-apply diff:"
    Show-Diff
  }
}
