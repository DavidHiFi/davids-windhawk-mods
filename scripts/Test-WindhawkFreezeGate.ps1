# Freeze gate: run before starting Windhawk, or installing, enabling or widening any mod.
# Exit 0 = PASS, 1 = FAIL. Read-only. Why: notes\2026-10-25-freeze11-agent-tests.md
$ErrorActionPreference = 'Stop'
$root = 'HKLM:\SOFTWARE\Windhawk'
$src  = 'C:\ProgramData\Windhawk\ModsSource'

# Mods that froze the PC, or the fork that replaced the catalog blur mod. Never installed again.
$banned = 'tray-utility-customizer', 'uwp-assets-redirect', 'local@translucent-windows-plus'
# Allowed exceptions, each with the reason the owner accepted it.
$allowCritical = @{
  'local@theme-tool-plus' = 'theme signature bypass must load in winlogon/logonui (2026-10-16)'
  'uxtheme-hook'          = 'same bypass, upstream mod'
}
$allowEveryApp = @{
  'win11-custom-title-bar-colours' = 'installed 2026-08-30, ran for months without a freeze'
  'local@window-borders'           = 'owner 2026-10-25: replaces the Windows border in every app; skips the translucent-windows apps'
}
$critical = '(?i)(^|\\)(dwm|winlogon|logonui|csrss|lsass|smss|wininit)\.exe$'
$lookApis = 'DwmSetWindowAttribute', 'SetWindowCompositionAttribute', 'DwmExtendFrameIntoClientArea', 'DwmEnableBlurBehindWindow'

$fail = @(); $warn = @()
# The engine keeps its own copy under Engine\Settings; the app-level Settings key
# holds the user-facing exclusion list. Reading the wrong one made the first two
# checks below test $null and never fire (fixed 2026-10-25).
$eng = Get-ItemProperty "$root\Engine\Settings"
$app = Get-ItemProperty "$root\Settings"
if ($eng.InjectIntoCriticalProcesses -eq 1) { $fail += 'engine: "inject into critical processes" is on' }
if (($eng.Include -split '\|') -match $critical) { $fail += "engine: global include list names a system process ($($eng.Include))" }
if (($app.Exclude -split '\|') -notcontains 'dwm.exe') { $warn += 'dwm.exe is not on the global exclusion list (engine cannot inject into it while InjectIntoCriticalProcesses=0)' }

foreach ($k in Get-ChildItem "$root\Engine\Mods") {
  $id = $k.PSChildName; $p = Get-ItemProperty $k.PSPath
  if ($id -in $banned) { $fail += "${id}: banned mod is installed"; continue }
  if ($p.Disabled -eq 1) { continue }
  $targets = @(if ($p.IncludeExcludeCustomOnly -eq 1) { $p.IncludeCustom } else { $p.Include; $p.IncludeCustom }) -split '\|' | ? { $_ }
  if (($targets -match $critical) -and -not $allowCritical[$id]) { $fail += "${id}: loads into a system process ($(($targets -match $critical) -join ', '))" }
  if ($targets -contains '*') {
    $f = Join-Path $src "$id.wh.cpp"
    $hits = if (Test-Path $f) { $t = [IO.File]::ReadAllText($f); $lookApis | ? { $t.Contains($_) } }
    if ($hits) {
      if ($allowEveryApp[$id]) { $warn += "${id}: restyles windows in every app (allowed: $($allowEveryApp[$id]))" }
      else { $fail += "${id}: restyles windows in every app ($($hits -join ', ')); give it a short app list" }
    }
  }
}

$resets = Get-WinEvent -FilterHashtable @{ LogName = 'System'; Id = 41; StartTime = (Get-Date).AddHours(-24) } -EA SilentlyContinue
if ($resets) { $warn += "$(@($resets).Count) hard reset(s) in the last 24 hours, latest $($resets[0].TimeCreated.ToString('M/d h:mm tt'))" }

$warn | % { "WARN  $_" }
$fail | % { "FAIL  $_" }
if ($fail) { 'GATE: FAIL. Fix every FAIL line before starting Windhawk or changing mods.'; exit 1 }
'GATE: PASS'; exit 0
