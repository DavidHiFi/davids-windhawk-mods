# 2026-10-09 taskbar frost: make the taskbar pill read as more frosted glass.
# Change: windows-11-taskbar-styler Settings styleConstants[18] (taskbarFill).
#   TintOpacity 0.92 -> 0.8  (more of the blurred wallpaper shows through)
#   BlurAmount  80   -> 110  (stronger smear behind the tint)
#   FallbackColor #EB... -> #CC...  (fallback alpha matches 0.8)
# Modes: -Audit (backup + before shot) | -Install (apply + verify + after shot)
#        | -Finish (evidence only, for a rerun after the elevated child died
#        mid-install: the value is live but the marker bump and shots are missing)
#        | -Rollback.
# Trap, measured 2026-10-09: the elevated 5.1 child imported the value, then
# crashed with an empty log before Bump. After an install crash, read the value
# back, bump if stale, then run -Finish non-elevated for the evidence.
param([Parameter(Position = 0)][ValidateSet('Audit', 'Install', 'Finish', 'Rollback')][string]$Mode = 'Audit')
$ErrorActionPreference = 'Stop'
$modKey = 'HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler'
$setKey = 'HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings'
$valueName = 'styleConstants[18]'
$oldFill = 'taskbarFill = <WindhawkBlur BlurAmount="80" TintColor="#1E1E2E" TintOpacity="0.92" TintLuminosityOpacity="0.8" FallbackColor="#EB1E1E2E"/>'
$newFill = 'taskbarFill = <WindhawkBlur BlurAmount="110" TintColor="#1E1E2E" TintOpacity="0.8" TintLuminosityOpacity="0.8" FallbackColor="#CC1E1E2E"/>'
$ws = 'H:\Windhawk Configuration'
$backupDir = "$ws\backups\2026-10-09\taskbar-frost"
$reportDir = "$ws\reports\2026-10-09-taskbar-frost"

Add-Type @'
using System;using System.Runtime.InteropServices;
public class TBRect {
  [StructLayout(LayoutKind.Sequential)] public struct RECT {public int Left,Top,Right,Bottom;}
  [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c,string n);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
}
'@
Add-Type -AssemblyName System.Drawing

function Get-Fill {
  (Get-ItemProperty -LiteralPath "Registry::$setKey" -Name $valueName).$valueName
}

function Bump {
  # Hot-reload marker on the mod key; the mod re-applies styles without a restart.
  $t = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
  reg add $modKey /v SettingsChangeTime /t REG_DWORD /d $t /f | Out-Null
  if ($LASTEXITCODE -ne 0) { throw "SettingsChangeTime bump failed (exit $LASTEXITCODE)" }
}

function Shot([string]$path) {
  # Taskbar strip (any edge), padded 10px and clamped to the primary screen so
  # the pill's rounded edge and some wallpaper are in frame.
  $h = [TBRect]::FindWindow('Shell_TrayWnd', $null)
  if ($h -eq [IntPtr]::Zero) { throw 'Shell_TrayWnd not found' }
  $r = New-Object TBRect+RECT
  [void][TBRect]::GetWindowRect($h, [ref]$r)
  Add-Type -AssemblyName System.Windows.Forms
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

function Receipt {
  $marker = (Get-ItemProperty 'Registry::HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' -Name SettingsChangeTime).SettingsChangeTime
  [pscustomobject]@{
    change        = 'taskbarFill: TintOpacity 0.92 -> 0.8, BlurAmount 80 -> 110, FallbackColor alpha EB -> CC'
    registryValue = "$setKey\$valueName"
    before        = $oldFill
    after         = $newFill
    backup        = "$backupDir\mod-key-full.reg"
    rollback      = "$ws\scripts\2026-10-09-taskbar-frost.ps1 -Rollback"
    settingsChangeTime = $marker
    appliedAt     = (Get-Date).ToString('s')
    evidence      = @("$reportDir\before.png", "$reportDir\after.png", "$reportDir\before-after.png")
  } | ConvertTo-Json | Set-Content "$reportDir\receipt.json" -Encoding UTF8
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
  $g.DrawString('BEFORE: TintOpacity 0.92, BlurAmount 80', $font, $white, 8, $y); $y += $labelH
  $g.DrawImage($b, 8, $y); $y += $b.Height + $labelH
  $g.DrawString('AFTER: TintOpacity 0.8, BlurAmount 110 (more frost)', $font, $white, 8, $y); $y += $labelH
  $g.DrawImage($a, 8, $y)
  $g.Dispose(); $c.Save($outPath, [System.Drawing.Imaging.ImageFormat]::Png); $c.Dispose()
  $b.Dispose(); $a.Dispose()
  $outPath
}

switch ($Mode) {
  'Audit' {
    New-Item -ItemType Directory -Force -Path $backupDir, $reportDir | Out-Null
    $cur = Get-Fill
    Set-Content -LiteralPath "$backupDir\old-value.txt" -Value $cur -Encoding UTF8
    if ($cur -ne $oldFill) {
      Write-Warning "Live value does not match the expected pre-change string. Refusing to install against an unexpected base."
      "ACTUAL: $cur"
      "EXPECTED: $oldFill"
      exit 1
    }
    reg export $modKey "$backupDir\mod-key-full.reg" /y | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "reg export failed (exit $LASTEXITCODE)" }
    $shot = Shot "$reportDir\before.png"
    "AUDIT OK. Backup: $backupDir\mod-key-full.reg. $shot"
  }
  'Install' {
    $cur = Get-Fill
    if ($cur -eq $newFill) { 'Already applied, nothing to do.'; exit 0 }
    if ($cur -ne $oldFill) {
      Write-Warning "Live value changed since audit; refusing to blind-install."
      "ACTUAL: $cur"; exit 1
    }
    $lines = [System.Collections.Generic.List[string]]::new()
    $lines.Add('Windows Registry Editor Version 5.00')
    $lines.Add('')
    $lines.Add("[$setKey]")
    $lines.Add('"' + $valueName + '"="' + ($newFill -replace '"', '\"') + '"')
    $tmp = "$backupDir\install.reg"
    Set-Content -Path $tmp -Value $lines -Encoding Unicode
    reg import $tmp
    if ($LASTEXITCODE -ne 0) { throw "reg import failed (exit $LASTEXITCODE)" }
    Remove-Item $tmp -ErrorAction SilentlyContinue
    Bump
    $now = Get-Fill
    if ($now -ne $newFill) { throw "Readback mismatch.`nACTUAL: $now" }
    Start-Sleep -Seconds 2
    $shot = Shot "$reportDir\after.png"
    $comp = Composite "$reportDir\before.png" "$reportDir\after.png" "$reportDir\before-after.png"
    Receipt
    "INSTALL OK. Verified readback. Evidence: $comp"
  }
  'Finish' {
    # Evidence pass for an install that landed but died before its own capture.
    $cur = Get-Fill
    if ($cur -ne $newFill) { throw "Live value is not the new fill.`nACTUAL: $cur" }
    $marker = (Get-ItemProperty 'Registry::HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler' -Name SettingsChangeTime).SettingsChangeTime
    $age = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds() - $marker
    if ($age -gt 600) { throw "SettingsChangeTime is stale ($age s old); bump it first, the mod has not reloaded." }
    Start-Sleep -Seconds 2
    $shot = Shot "$reportDir\after.png"
    $comp = Composite "$reportDir\before.png" "$reportDir\after.png" "$reportDir\before-after.png"
    Receipt
    "FINISH OK. Marker age ${age}s. Evidence: $comp"
  }
  'Rollback' {
    reg import "$backupDir\mod-key-full.reg"
    if ($LASTEXITCODE -ne 0) { throw "reg import failed (exit $LASTEXITCODE)" }
    Bump
    $now = Get-Fill
    if ($now -ne $oldFill) { throw "Rollback readback mismatch.`nACTUAL: $now" }
    $shot = Shot "$reportDir\rollback.png"
    "ROLLBACK OK. $shot"
  }
}
