# 2026-10-09 taskbar frost pass 2: one more small step of frost, mocha base kept.
# Change: windows-11-taskbar-styler Settings styleConstants[18] (taskbarFill).
#   TintOpacity 0.8 -> 0.75 (a small step, blur and tint color unchanged)
#   TintColor stays #1E1E2E (30,30,46, Catppuccin Mocha base, as the user asked)
#   TintLuminosityOpacity stays 0.8, BlurAmount stays 110
#   FallbackColor #CC1E1E2E -> #BF1E1E2E (alpha echo of 0.75)
# Modes:
#   Audit   (non-elevated): fresh full backup, live-value check, before shot,
#           and builds pass2.reg with the SettingsChangeTime marker BAKED IN,
#           so the import applies the value and bumps the marker atomically.
#   Apply   (elevated):     one reg import, readback check, writes its own
#           result file so a lost stdout still leaves evidence.
#   Capture (non-elevated): after shot + composite + receipt.
#   Rollback (elevated):    import the pass-2 full backup and bump the marker.
# Lesson from pass 1: never split the registry write and the marker bump across
# two steps in the elevated child; the child can die between them. Bake the
# marker into the .reg instead.

param([Parameter(Position = 0)][ValidateSet('Audit', 'Apply', 'Capture', 'Rollback')][string]$Mode = 'Audit')
$ErrorActionPreference = 'Stop'
$modKey = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$psModKey = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$setKey = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$valueName = 'styleConstants[18]'
$fromValue = 'taskbarFill = <WindhawkBlur BlurAmount="110" TintColor="#1E1E2E" TintOpacity="0.8" TintLuminosityOpacity="0.8" FallbackColor="#CC1E1E2E"/>'
$toValue = 'taskbarFill = <WindhawkBlur BlurAmount="110" TintColor="#1E1E2E" TintOpacity="0.75" TintLuminosityOpacity="0.8" FallbackColor="#BF1E1E2E"/>'
$ws = 'H:\Windhawk Configuration'
$backupDir = "$ws\backups\2026-10-09\taskbar-frost-2"
$reportDir = "$ws\reports\2026-10-09-taskbar-frost-pass2"

Add-Type @'
using System;using System.Runtime.InteropServices;
public class TBRect2 {
  [StructLayout(LayoutKind.Sequential)] public struct RECT {public int Left,Top,Right,Bottom;}
  [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c,string n);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
}
'@
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms

function Get-Fill {
  (Get-ItemProperty -LiteralPath "Registry::$setKey" -Name $valueName).$valueName
}

function Shot([string]$path) {
  $h = [TBRect2]::FindWindow('Shell_TrayWnd', $null)
  if ($h -eq [IntPtr]::Zero) { throw 'Shell_TrayWnd not found' }
  $r = New-Object TBRect2+RECT
  [void][TBRect2]::GetWindowRect($h, [ref]$r)
  $p = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
  $x1 = [Math]::Max($p.X, $r.Left - 10); $y1 = [Math]::Max($p.Y, $r.Top - 10)
  $x2 = [Math]::Min($p.Right, $r.Right + 10); $y2 = [Math]::Min($p.Bottom, $r.Bottom + 10)
  $w = $x2 - $x1; $hh = $y2 - $y1
  if ($w -le 0 -or $hh -le 0) { throw 'taskbar rect outside primary screen' }
  $bmp = New-Object System.Drawing.Bitmap $w, $hh
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen($x1, $y1, 0, 0, $bmp.Size)
  $g.Dispose()
  $bmp.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
  $bmp.Dispose()
  "$path ($w x $hh)"
}

function Composite([string]$beforePath, [string]$afterPath, [string]$outPath) {
  $b = [System.Drawing.Bitmap]::new($beforePath, $false)
  $a = [System.Drawing.Bitmap]::new($afterPath, $false)
  $labelH = 28
  $W = [Math]::Max($b.Width, $a.Width) + 16
  $H = $b.Height + $a.Height + 3 * $labelH + 12
  $c = New-Object System.Drawing.Bitmap $W, $H
  $g = [System.Drawing.Graphics]::FromImage($c)
  $g.Clear([System.Drawing.Color]::FromArgb(20, 20, 28))
  $font = New-Object System.Drawing.Font 'Segoe UI', 13
  $white = [System.Drawing.Brushes]::White
  $y = 4
  $g.DrawString('BEFORE: TintOpacity 0.8, BlurAmount 110', $font, $white, 8, $y); $y += $labelH
  $g.DrawImage($b, 8, $y); $y += $b.Height + $labelH
  $g.DrawString('AFTER: TintOpacity 0.75 (mocha base #1E1E2E unchanged)', $font, $white, 8, $y); $y += $labelH
  $g.DrawImage($a, 8, $y)
  $g.Dispose(); $c.Save($outPath, [System.Drawing.Imaging.ImageFormat]::Png); $c.Dispose()
  $b.Dispose(); $a.Dispose()
  $outPath
}

function Receipt([string]$markerNote) {
  $marker = (Get-ItemProperty 'Registry::HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' -Name SettingsChangeTime).SettingsChangeTime
  [pscustomobject]@{
    change        = 'taskbarFill pass 2: TintOpacity 0.8 -> 0.75; TintColor #1E1E2E, BlurAmount 110, TintLuminosityOpacity 0.8 all unchanged; FallbackColor alpha CC -> BF'
    registryValue = "$setKey\$valueName"
    before        = $fromValue
    after         = $toValue
    backup        = "$backupDir\mod-key-full-pass2.reg"
    rollback      = "pwsh -File `"$ws\scripts\2026-10-09-taskbar-frost-pass2.ps1`" Rollback"
    settingsChangeTime = $marker
    markerNote    = $markerNote
    appliedAt     = (Get-Date).ToString('s')
    evidence      = @("$reportDir\before-2.png", "$reportDir\after-2.png", "$reportDir\before-after-2.png")
  } | ConvertTo-Json | Set-Content "$reportDir\receipt.json" -Encoding UTF8
}

# Result file the Apply mode writes from inside the elevated child, so the
# outcome is readable even when the child's stdout dies with it.
function Report([string]$status, [string]$detail) {
  Set-Content "$reportDir\apply-result.txt" -Value "$status | $detail" -Encoding UTF8
}

switch ($Mode) {
  'Audit' {
    New-Item -ItemType Directory -Force -Path $backupDir, $reportDir | Out-Null
    $cur = Get-Fill
    Set-Content "$backupDir\from-value.txt" -Value $cur -Encoding UTF8
    if ($cur -ne $fromValue) {
      Write-Warning "Live value is not the expected pass-1 state. Refusing."
      "ACTUAL:   $cur"
      "EXPECTED: $fromValue"
      exit 1
    }
    reg export $modKey "$backupDir\mod-key-full-pass2.reg" /y | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg export failed (exit $LASTEXITCODE)" }
    # Build the apply .reg: the new value plus the reload marker in one file.
    $ts = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $lines = [System.Collections.Generic.List[string]]::new()
    $lines.Add('Windows Registry Editor Version 5.00')
    $lines.Add('')
    $lines.Add("[$psModKey]")
    $lines.Add('"SettingsChangeTime"=dword:' + $ts.ToString('x8'))
    $lines.Add('')
    $lines.Add("[$setKey]")
    $lines.Add('"' + $valueName + '"="' + ($toValue -replace '"', '\"') + '"')
    Set-Content "$backupDir\pass2.reg" -Value $lines -Encoding Unicode
    $shot = Shot "$reportDir\before-2.png"
    "AUDIT2 OK. Backup + pass2.reg (marker baked) in $backupDir. $shot"
  }
  'Apply' {
    try {
      reg import "$backupDir\pass2.reg" 2>&1 | ForEach-Object { "$_" } | Out-Null
      if ($LASTEXITCODE -ne 0) { throw "reg import exit $LASTEXITCODE" }
      $now = Get-Fill
      if ($now -ne $toValue) { throw "readback mismatch: $now" }
      Report 'OK' "value applied and marker imported; readback matches"
      'APPLY2 OK'
    } catch {
      Report 'FAIL' ("$_" -replace '\r?\n', ' | ')
      throw
    }
  }
  'Capture' {
    $cur = Get-Fill
    if ($cur -ne $toValue) { throw "live value is not the new fill.`nACTUAL: $cur" }
    $marker = (Get-ItemProperty 'Registry::HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' -Name SettingsChangeTime).SettingsChangeTime
    $age = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds() - $marker
    if ($age -gt 600) { throw "SettingsChangeTime stale ($age s old); the mod has not reloaded." }
    # The marker must be the one baked into pass2.reg, proving the import (and
    # with it the reload) really landed. Found the hard way 2026-10-09: a value
    # can apply while the marker section is skipped, leaving the old look on
    # screen while the registry reads new.
    $bakedLine = (Select-String -Path "$backupDir\pass2.reg" -Pattern '"SettingsChangeTime"=dword:([0-9a-f]+)').Matches[0]
    $baked = [Convert]::ToUInt32($bakedLine.Groups[1].Value, 16)
    if ($marker -lt $baked) { throw "live marker $marker is older than the baked marker $baked; the marker section did not import and no manual bump happened." }
    Start-Sleep -Seconds 2
    $shot = Shot "$reportDir\after-2.png"
    $comp = Composite "$reportDir\before-2.png" "$reportDir\after-2.png" "$reportDir\before-after-2.png"
    Receipt "marker baked into pass2.reg at audit time"
    "CAPTURE2 OK. Evidence: $comp"
  }
  'Rollback' {
    reg import "$backupDir\mod-key-full-pass2.reg"
    if ($LASTEXITCODE -ne 0) { throw "reg import failed (exit $LASTEXITCODE)" }
    $t = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    reg add $modKey /v SettingsChangeTime /t REG_DWORD /d $t /f | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "marker bump failed" }
    $now = Get-Fill
    if ($now -ne $fromValue) { throw "rollback readback mismatch.`nACTUAL: $now" }
    "ROLLBACK2 OK (back to pass-1 state: TintOpacity 0.8)"
  }
}
