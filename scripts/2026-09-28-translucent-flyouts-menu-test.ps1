<#
.SYNOPSIS
    Screenshot-test for the local translucent-flyouts Windhawk mod, using the
    isolated FlyoutTestWindow app (a native #32768 context menu on a timer).

.DESCRIPTION
    1. Builds scripts\tools\FlyoutTestWindow.exe if needed.
    2. Launches it (menu shows 1.5 s after start, app exits after 9 s).
    3. Waits for the menu, screenshots a region around the window (the menu
       extends beyond it) into reports\2026-09-28\.
    4. Copies the mod probe log for that process into the report folder.

    No synthetic input; nothing else on the desktop is touched.

.EXAMPLE
    pwsh -File .\2026-09-28-translucent-flyouts-menu-test.ps1
#>
[CmdletBinding()]
param(
    [string]$ReportDir = 'H:\Windhawk Configuration\reports\2026-09-28',
    [string]$LogPath = 'H:\Windhawk Configuration\reports\2026-09-28\translucent-flyouts-menu-test.log',
    [string]$ToolExe = 'H:\Windhawk Configuration\scripts\tools\FlyoutTestWindow.exe',
    [string]$ToolSrc = 'H:\Windhawk Configuration\scripts\tools\FlyoutTestWindow.cs',
    [string]$ProbeDir = 'C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage\local@translucent-flyouts',
    [int]$MenuWaitMs = 2600,
    [int]$HoldMs = 4000,
    [ValidateSet('menu', 'tooltip', 'nativetip', 'dropdown')]
    [string]$Mode = 'menu'
)

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
if (-not (Test-Path -LiteralPath $ReportDir)) { New-Item -ItemType Directory -Path $ReportDir -Force | Out-Null }
function Log {
    param([string]$Message)
    $line = '{0} {1}' -f (Get-Date -Format 'HH:mm:ss.fff'), $Message
    Write-Host $line
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
}

Add-Type -TypeDefinition @'
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
public static class Win {
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT r);
    [DllImport("user32.dll")] public static extern int GetSystemMetrics(int index);
    public delegate bool EnumProc(IntPtr hWnd, IntPtr lParam);
    [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr lParam);
    [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
    [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
    // All visible windows of the process: returns "class|left|top|right|bottom" lines.
    public static string VisibleWindows(uint target) {
        var sb = new StringBuilder();
        EnumWindows(delegate(IntPtr h, IntPtr l) {
            uint pid; GetWindowThreadProcessId(h, out pid);
            if (pid != target || !IsWindowVisible(h)) return true;
            RECT r; GetWindowRect(h, out r);
            if (r.Right <= r.Left || r.Bottom <= r.Top) return true;
            var cn = new StringBuilder(256); GetClassName(h, cn, 256);
            sb.AppendLine(string.Format("{0}|{1}|{2}|{3}|{4}", cn, r.Left, r.Top, r.Right, r.Bottom));
            return true;
        }, IntPtr.Zero);
        return sb.ToString();
    }
}
'@

function Save-Screenshot {
    param([string]$Path, [System.Drawing.Rectangle]$Rect)
    Add-Type -AssemblyName System.Drawing
    $bmp = New-Object System.Drawing.Bitmap($Rect.Width, $Rect.Height)
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen($Rect.Left, $Rect.Top, 0, 0, $bmp.Size)
    $bmp.Save($Path, [System.Drawing.Imaging.ImageFormat]::Png)
    $g.Dispose(); $bmp.Dispose()
}

Log '=== translucent-flyouts menu test (isolated app) ==='

if (-not (Test-Path -LiteralPath $ToolExe)) {
    Log "building test app: $ToolExe"
    & powershell.exe -NoProfile -ExecutionPolicy Bypass -File (Join-Path (Split-Path $ToolExe -Parent) 'Build-FlyoutTestWindow.ps1')
}

$before = @(
    Get-ChildItem -LiteralPath $ProbeDir -Filter ('probe-{0}-*.log' -f (Split-Path $ToolExe -Leaf)) -ErrorAction SilentlyContinue
    Get-ChildItem -LiteralPath $ProbeDir -Filter ('tf-{0}-*.log' -f (Split-Path $ToolExe -Leaf)) -ErrorAction SilentlyContinue
) | Select-Object -ExpandProperty FullName

$proc = Start-Process -FilePath $ToolExe -ArgumentList @(2600, 9000, $Mode) -PassThru
Log "test app pid=$($proc.Id) mode=$Mode"
$hwnd = [IntPtr]::Zero
$deadline = (Get-Date).AddSeconds(10)
while ((Get-Date) -lt $deadline) {
    Start-Sleep -Milliseconds 200
    $proc.Refresh()
    if ($proc.HasExited) { break }
    if ($proc.MainWindowHandle -ne [IntPtr]::Zero) { $hwnd = $proc.MainWindowHandle; break }
}
if ($hwnd -eq [IntPtr]::Zero) { Log 'test app window not found'; exit 4 }
Log "window hwnd=$hwnd"

$rect = New-Object Win+RECT
[Win]::GetWindowRect($hwnd, [ref]$rect) | Out-Null
Log "window rect=$($rect.Left),$($rect.Top),$($rect.Right),$($rect.Bottom)"

Start-Sleep -Milliseconds $MenuWaitMs

$screenW = [Win]::GetSystemMetrics(0)
$screenH = [Win]::GetSystemMetrics(1)
$capLeft = [Math]::Max(0, $rect.Left - 20)
$capTop = [Math]::Max(0, $rect.Top - 20)
$capRight = [Math]::Min($screenW, $rect.Right + 420)
$capBottom = [Math]::Min($screenH, $rect.Bottom + 320)
# Include any visible popup/flyout window of the process (tooltips track the
# cursor, combo dropdowns sit below the combo box, menus beside the form).
foreach ($line in ([Win]::VisibleWindows([uint32]$proc.Id) -split "`r?`n")) {
    if (-not $line) { continue }
    $parts = $line.Split('|')
    if ($parts.Count -ne 5) { continue }
    $l = [int]$parts[1]; $t = [int]$parts[2]; $r = [int]$parts[3]; $b = [int]$parts[4]
    $capLeft = [Math]::Max(0, [Math]::Min($capLeft, $l - 30))
    $capTop = [Math]::Max(0, [Math]::Min($capTop, $t - 30))
    $capRight = [Math]::Min($screenW, [Math]::Max($capRight, $r + 30))
    $capBottom = [Math]::Min($screenH, [Math]::Max($capBottom, $b + 30))
    Log "popup: $line"
}
$capture = [System.Drawing.Rectangle]::new($capLeft, $capTop, ($capRight - $capLeft), ($capBottom - $capTop))
$stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$png = Join-Path $ReportDir "translucent-flyouts-$Mode-$stamp.png"
Save-Screenshot -Path $png -Rect $capture
Log "screenshot: $png"

Start-Sleep -Milliseconds $HoldMs
if (-not $proc.HasExited) { $proc.WaitForExit(8000) | Out-Null }
if (-not $proc.HasExited) { $proc.Kill() }

Start-Sleep -Milliseconds 400
$after = @(
    Get-ChildItem -LiteralPath $ProbeDir -Filter ('probe-{0}-*.log' -f (Split-Path $ToolExe -Leaf)) -ErrorAction SilentlyContinue
    Get-ChildItem -LiteralPath $ProbeDir -Filter ('tf-{0}-*.log' -f (Split-Path $ToolExe -Leaf)) -ErrorAction SilentlyContinue
) | Where-Object { $before -notcontains $_.FullName } | Select-Object -First 1
if ($after) {
    $copy = Join-Path $ReportDir 'translucent-flyouts-menu-probe.log'
    Copy-Item -LiteralPath $after.FullName -Destination $copy -Force
    Log "probe log: $($after.FullName) -> $copy"
    Get-Content -LiteralPath $copy -Encoding Unicode | ForEach-Object { Log "  $_" }
} else {
    Log 'no probe log for the test app process (mod not injected?)'
}
Log '=== done ==='
