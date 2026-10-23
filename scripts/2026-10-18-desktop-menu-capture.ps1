<#
.SYNOPSIS
    Opens the real Explorer desktop context menu without moving the mouse or clicking, captures
    it to PNG, cancels it, and copies the translucent-flyouts log for that Explorer process.

.DESCRIPTION
    Runs under `coop --project machine lock desktop` (the menu and the Explorer restart touch the
    shared desktop). Steps:
      1. Restart explorer.exe (pre-approved on this machine) so it loads the current mod DLL.
      2. Confirm the mod DLL is mapped into the new Explorer process.
      3. Post WM_CONTEXTMENU to the desktop icon list. Posting does not move the cursor.
      4. Find the visible popup menu window (class #32768), capture its rectangle to PNG.
      5. Cancel the menu with WM_CANCELMODE, then Escape if it is still up.
      6. Copy the Explorer flyout log to reports\ and print the counts of each log tag.
#>
[CmdletBinding()]
param(
    [string]$OutDir = 'H:\Windhawk Configuration\reports\2026-10-18-flyout-border',
    [string]$Tag = '0.6.48-diag',
    [int]$ClickX = 900,
    [int]$ClickY = 500,
    [int]$DelayMs = 0,
    [switch]$SkipRestart
)

$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$stamp = Get-Date -Format 'HHmmss'
$logOut = Join-Path $OutDir "desktop-menu-$Tag-$stamp.txt"
function Say([string]$m) { $line = "{0} {1}" -f (Get-Date -Format 'HH:mm:ss'), $m; $line; Add-Content -LiteralPath $logOut -Value $line }

Add-Type -AssemblyName System.Drawing
Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class DeskMenu {
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] public static extern IntPtr FindWindow(string cls, string title);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] public static extern IntPtr FindWindowEx(IntPtr parent, IntPtr after, string cls, string title);
    [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);
    [DllImport("user32.dll")] public static extern IntPtr SendMessageTimeout(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam, uint flags, uint timeout, out IntPtr result);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT rc);
    [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint pid);
}
"@

if (-not $SkipRestart) {
    Say 'restarting explorer.exe'
    Stop-Process -Name explorer -Force -ErrorAction SilentlyContinue
    Start-Sleep -Seconds 2
    Start-Process explorer.exe
    Start-Sleep -Seconds 10
}

$exp = Get-Process explorer | Sort-Object StartTime -Descending | Select-Object -First 1
Say "explorer pid=$($exp.Id) started=$($exp.StartTime)"
$mods = $exp.Modules | Where-Object { $_.ModuleName -like 'local@translucent-flyouts*' } | ForEach-Object { $_.ModuleName }
Say ("mod modules mapped: " + ($(if ($mods) { $mods -join ', ' } else { 'NONE' })))

$progman = [DeskMenu]::FindWindow('Progman', 'Program Manager')
$defView = [DeskMenu]::FindWindowEx($progman, [IntPtr]::Zero, 'SHELLDLL_DefView', $null)
$list    = [DeskMenu]::FindWindowEx($defView, [IntPtr]::Zero, 'SysListView32', 'FolderView')
Say "progman=$progman defview=$defView listview=$list"
if ($list -eq [IntPtr]::Zero) { throw 'desktop icon list not found' }

function Find-Popup {
    $found = New-Object System.Collections.Generic.List[object]
    $h = [IntPtr]::Zero
    do {
        $h = [DeskMenu]::FindWindowEx([IntPtr]::Zero, $h, '#32768', $null)
        if ($h -ne [IntPtr]::Zero -and [DeskMenu]::IsWindowVisible($h)) {
            $r = New-Object DeskMenu+RECT
            [void][DeskMenu]::GetWindowRect($h, [ref]$r)
            $w = $r.Right - $r.Left; $hh = $r.Bottom - $r.Top
            if ($w -gt 60 -and $hh -gt 60) { $found.Add([pscustomobject]@{ H = $h; R = $r; W = $w; Hh = $hh }) }
        }
    } while ($h -ne [IntPtr]::Zero)
    $found | Sort-Object { $_.W * $_.Hh } -Descending | Select-Object -First 1
}

$cl = [IntPtr](((($ClickY -band 0xFFFF) -shl 16) -bor ($ClickX -band 0xFFFF)))
$sl = $cl
$attempts = @(
    @{ Name = 'list right-button down/up (client point)'; Run = {
        [void][DeskMenu]::PostMessage($list, 0x0204, [IntPtr]2, $cl)   # WM_RBUTTONDOWN
        Start-Sleep -Milliseconds 60
        [void][DeskMenu]::PostMessage($list, 0x0205, [IntPtr]::Zero, $cl) } },  # WM_RBUTTONUP
    @{ Name = 'defview WM_CONTEXTMENU (screen point)'; Run = {
        [void][DeskMenu]::PostMessage($defView, 0x007B, $defView, $sl) } },
    @{ Name = 'progman WM_CONTEXTMENU (screen point)'; Run = {
        [void][DeskMenu]::PostMessage($progman, 0x007B, $progman, $sl) } }
)
$pick = $null
foreach ($a in $attempts) {
    Say "attempt: $($a.Name)"
    & $a.Run
    for ($i = 0; $i -lt 8 -and -not $pick; $i++) {
        Start-Sleep -Milliseconds 300
        $pick = Find-Popup
    }
    if ($pick) { break }
}
Say ("popup found: " + [bool]$pick)
if (-not $pick) { Say 'NO MENU FOUND'; exit 3 }
$menu = $pick.H; $rect = $pick.R
$menu = $pick.H; $rect = $pick.R
Say ("menu hwnd=0x{0:X} rect={1},{2},{3},{4} size={5}x{6}" -f $menu.ToInt64(), $rect.Left, $rect.Top, $rect.Right, $rect.Bottom, $pick.W, $pick.Hh)
[uint32]$ownerPid = 0
[void][DeskMenu]::GetWindowThreadProcessId($menu, [ref]$ownerPid)
$owner = Get-Process -Id $ownerPid -ErrorAction SilentlyContinue
Say ("menu owner pid={0} process={1}" -f $ownerPid, $(if ($owner) { $owner.ProcessName } else { 'unknown' }))

$png = Join-Path $OutDir "desktop-menu-$Tag-$stamp.png"
# The watcher rings on a 250 ms timer and the menu's buffered blits can erase an
# earlier ring; give the last ring time to land before reading the screen.
if ($DelayMs -gt 0) { Start-Sleep -Milliseconds $DelayMs }
$bmp = New-Object System.Drawing.Bitmap $pick.W, $pick.Hh
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($rect.Left, $rect.Top, 0, 0, (New-Object System.Drawing.Size $pick.W, $pick.Hh))
$g.Dispose()
$bmp.Save($png, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
Say "saved $png"

[IntPtr]$out = [IntPtr]::Zero
[void][DeskMenu]::SendMessageTimeout($menu, 0x001F, [IntPtr]::Zero, [IntPtr]::Zero, 0x0002, 2000, [ref]$out)  # WM_CANCELMODE
Start-Sleep -Milliseconds 800
if ([DeskMenu]::IsWindowVisible($menu)) {
    [void][DeskMenu]::PostMessage($menu, 0x0100, [IntPtr]0x1B, [IntPtr]::Zero)   # WM_KEYDOWN Escape
    Start-Sleep -Milliseconds 300
}
Say ("menu still visible after cancel: " + [DeskMenu]::IsWindowVisible($menu))

$logFile = Get-ChildItem 'C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage\local@translucent-flyouts' -Filter "tf-*-$($exp.Id).log" -ErrorAction SilentlyContinue | Select-Object -First 1
if ($logFile) {
    $dest = Join-Path $OutDir "tf-explorer-$Tag-$stamp.log"
    Copy-Item -LiteralPath $logFile.FullName -Destination $dest -Force
    $lines = Get-Content -LiteralPath $dest -Encoding Unicode
    Say "log copied to $dest ($($lines.Count) lines)"
    $lines | ForEach-Object { if ($_ -match '^\s*\[(\w+)\]') { $matches[1] } } | Group-Object | ForEach-Object { Say ("  tag {0}: {1}" -f $_.Name, $_.Count) }
} else {
    Say 'no tf log for this explorer pid yet'
}
