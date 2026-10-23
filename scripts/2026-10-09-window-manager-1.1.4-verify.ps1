<#
.SYNOPSIS
    Verifies local@window-manager 1.1.4: Alt+right-drag resizes borderless
    windows (Ditto quick-paste style), with no regressions on normal windows.

.DESCRIPTION
    Compiles a tiny GUI-subsystem WinForms app with two windows - a normal
    resizable one and a borderless popup (FormBorderStyle=None: WS_POPUP, no
    caption, no sizing border, same style bits as Ditto's QPaste popup and the
    Flow Launcher window) - and drives them with injected input:

      1. Alt+right-drag on the BORDERLESS window resizes it (the 1.1.4 fix)
      2. Alt+right-drag on the NORMAL window still resizes it (regression)
      3. Alt+left-drag on the normal window still moves it (regression)
      4. Right-click while moving still toggles maximize, and it sticks

    Waits for the user to be idle before injecting input and restores the
    cursor afterwards. Read-only with respect to system settings.
#>
[CmdletBinding()]
param(
    [int]$IdleMs = 3000,
    [int]$IdleTimeoutSec = 90,
    [string]$ReportDir = 'H:\Windhawk Configuration\reports\2026-10-09-window-manager-1.1.4'
)
$ErrorActionPreference = 'Stop'
if (-not (Test-Path -LiteralPath $ReportDir)) { New-Item -ItemType Directory -Path $ReportDir -Force | Out-Null }
$logPath = Join-Path $ReportDir 'verify.log'
$results = New-Object System.Collections.Generic.List[object]
function Log {
    param([string]$Message)
    $line = '{0} {1}' -f (Get-Date -Format 'HH:mm:ss.fff'), $Message
    Write-Host $line
    Add-Content -LiteralPath $logPath -Value $line -Encoding UTF8
}
function Add-Result {
    param([string]$Name, [bool]$Pass, [string]$Detail)
    $results.Add([pscustomobject]@{ Test = $Name; Pass = $Pass; Detail = $Detail })
    $tag = if ($Pass) { 'PASS' } else { 'FAIL' }
    Log "  [$tag] $Name - $Detail"
}

Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
public static class N {
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
    [StructLayout(LayoutKind.Sequential)] public struct LASTINPUTINFO { public uint cbSize; public uint dwTime; }
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT r);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern void SwitchToThisWindow(IntPtr hWnd, bool fUnknown);
    [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool fAttach);
    [DllImport("user32.dll")] public static extern bool IsZoomed(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool IsWindow(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr hWnd, int cmd);
    [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
    [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
    [DllImport("user32.dll")] public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
    [DllImport("user32.dll")] public static extern void mouse_event(uint dwFlags, int dx, int dy, uint dwData, UIntPtr dwExtraInfo);
    [DllImport("user32.dll")] public static extern bool GetLastInputInfo(ref LASTINPUTINFO plii);
    [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint pid);
    [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] public static extern IntPtr FindWindowW(string cls, string title);
    public const uint KEYUP = 2, MOVE = 1, LDOWN = 2, LUP = 4, RDOWN = 8, RUP = 16;
}
'@

$VK_ALT = 0x12
$SW_RESTORE = 9
function Move-Cursor { param([int]$X, [int]$Y); [N]::SetCursorPos($X, $Y) | Out-Null; Start-Sleep -Milliseconds 80 }
function Invoke-Drag {
    param([int]$SX, [int]$SY, [int]$DX, [int]$DY, [string]$Button = 'left', [int]$Steps = 12, [IntPtr]$Window = [IntPtr]::Zero)
    Move-Cursor $SX $SY
    if ($Window -ne [IntPtr]::Zero -and [N]::GetForegroundWindow() -ne $Window) { [void](Focus-Window $Window) }
    $down = if ($Button -eq 'right') { [N]::RDOWN } else { [N]::LDOWN }
    $up   = if ($Button -eq 'right') { [N]::RUP }   else { [N]::LUP }
    [N]::mouse_event($down, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 150
    $lx = 0; $ly = 0
    for ($i = 1; $i -le $Steps; $i++) {
        $tx = [int][Math]::Round($DX * $i / $Steps); $ty = [int][Math]::Round($DY * $i / $Steps)
        [N]::mouse_event([N]::MOVE, $tx - $lx, $ty - $ly, 0, [UIntPtr]::Zero)
        $lx = $tx; $ly = $ty; Start-Sleep -Milliseconds 25
    }
    Start-Sleep -Milliseconds 100
    [N]::mouse_event($up, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 200
}
function Get-Rect { param([IntPtr]$H); $r = New-Object 'N+RECT'; [N]::GetWindowRect($H, [ref]$r) | Out-Null; $r }
function Get-Idle {
    $lii = New-Object 'N+LASTINPUTINFO'; $lii.cbSize = 8
    [N]::GetLastInputInfo([ref]$lii) | Out-Null
    [Math]::Abs([int]([uint32][Environment]::TickCount - $lii.dwTime))
}
function Wait-Idle {
    $t0 = Get-Date
    while (((Get-Date) - $t0).TotalSeconds -lt $IdleTimeoutSec) {
        $idle = Get-Idle
        if ($idle -ge $IdleMs) { Log "user idle ${idle}ms; starting input tests"; return $true }
        Start-Sleep -Milliseconds 500
    }
    return $false
}
function Wait-Window {
    param([string]$Title, [int]$TimeoutSec = 20)
    $deadline = (Get-Date).AddSeconds($TimeoutSec)
    while ((Get-Date) -lt $deadline) {
        $h = [N]::FindWindowW([NullString]::Value, $Title)
        if ($h -ne [IntPtr]::Zero) { return $h }
        Start-Sleep -Milliseconds 300
    }
    return [IntPtr]::Zero
}
function Focus-Window {
    param([IntPtr]$H)
    $curThread = [N]::GetCurrentThreadId()
    for ($i = 0; $i -lt 10; $i++) {
        if ([N]::GetForegroundWindow() -eq $H) { return $true }
        $fg = [N]::GetForegroundWindow()
        $fgPid = [uint32]0
        $fgThread = if ($fg -ne [IntPtr]::Zero) { [N]::GetWindowThreadProcessId($fg, [ref]$fgPid) } else { 0 }
        if ($fgThread -ne 0 -and $fgThread -ne $curThread) { [N]::AttachThreadInput($fgThread, $curThread, $true) | Out-Null }
        [N]::SetForegroundWindow($H) | Out-Null; [N]::BringWindowToTop($H) | Out-Null
        if ($fgThread -ne 0 -and $fgThread -ne $curThread) { [N]::AttachThreadInput($fgThread, $curThread, $false) | Out-Null }
        Start-Sleep -Milliseconds 200
        if ([N]::GetForegroundWindow() -eq $H) { return $true }
        [N]::SwitchToThisWindow($H, $true); Start-Sleep -Milliseconds 200
    }
    return ([N]::GetForegroundWindow() -eq $H)
}

Log '=== window-manager 1.1.4 borderless-resize verification ==='

# preconditions: the 1.1.4 mod live, new setting on
$mod = Get-ItemProperty -LiteralPath 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@window-manager'
$st = Get-ItemProperty -LiteralPath 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@window-manager\Settings'
Log ("live: Disabled={0} Version={1} Library={2} sizeWithoutBorder={3}" -f $mod.Disabled, $mod.Version, $mod.LibraryFileName, $st.sizeWindowsWithoutSizingBorder)
if ($mod.Disabled -ne 0 -or $mod.Version -ne '1.1.4' -or $st.sizeWindowsWithoutSizingBorder -ne 1) {
    Log 'FAIL: preconditions not met'; exit 3
}

$cursor0 = New-Object 'N+POINT'; [N]::GetCursorPos([ref]$cursor0) | Out-Null
if (-not (Wait-Idle)) { Log 'FAIL: user did not go idle; aborting before injecting input'; exit 5 }

$rand = Get-Random
$titleNormal = 'WMVerify-Normal-{0}' -f $rand
$titleBare = 'WMVerify-Borderless-{0}' -f $rand
$exe = Join-Path $env:TEMP ('wmverify-{0}.exe' -f $rand)
$csharp = @'
using System;
using System.Drawing;
using System.Windows.Forms;
public class F : Form {
    public F(string title, bool borderless) {
        Text = title; TopMost = true;
        ClientSize = new Size(560, 380);
        StartPosition = FormStartPosition.Manual;
        var wa = Screen.PrimaryScreen.WorkingArea;
        Left = wa.Left + (wa.Width - Width) / 2;
        Top = wa.Top + (wa.Height - Height) / 2;
        if (borderless) { FormBorderStyle = FormBorderStyle.None; }
    }
    [STAThread]
    public static void Main(string[] args) {
        Application.Run(new F(args[0], args.Length > 1 && args[1] == "bare"));
    }
}
'@
Add-Type -TypeDefinition $csharp -OutputAssembly $exe -OutputType WindowsApplication -ReferencedAssemblies 'System.Windows.Forms', 'System.Drawing', 'System'
Log "compiled: $exe"

$child = $null
try {
    Start-Process -FilePath $exe -ArgumentList $titleNormal | Out-Null
    Start-Process -FilePath $exe -ArgumentList $titleBare, 'bare' | Out-Null
    $hNormal = Wait-Window $titleNormal
    $hBare = Wait-Window $titleBare
    if ($hNormal -eq [IntPtr]::Zero -or $hBare -eq [IntPtr]::Zero) { Log 'FAIL: test windows did not appear'; exit 4 }
    Log "normal=$hNormal borderless=$hBare"
    Start-Sleep -Milliseconds 1500

    # real-click activation so programmatic focus is not reverted (harness trap)
    foreach ($h in @($hNormal, $hBare)) {
        [void](Focus-Window $h)
        $r = Get-Rect $h
        Move-Cursor ($r.Left + 100) ($r.Top + 60)
        [N]::mouse_event([N]::LDOWN, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 60
        [N]::mouse_event([N]::LUP, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 300
    }

    # 1. THE FIX: Alt+right-drag resizes the borderless window
    [void](Focus-Window $hBare)
    $r0 = Get-Rect $hBare
    $w0 = $r0.Right - $r0.Left; $h0 = $r0.Bottom - $r0.Top
    [N]::keybd_event($VK_ALT, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 80
    Invoke-Drag -Button right -SX ($r0.Right - 30) -SY ($r0.Bottom - 30) -DX 120 -DY 80 -Window $hBare
    [N]::keybd_event($VK_ALT, 0, [N]::KEYUP, [UIntPtr]::Zero); Start-Sleep -Milliseconds 500
    $r1 = Get-Rect $hBare
    $dw = ($r1.Right - $r1.Left) - $w0; $dh = ($r1.Bottom - $r1.Top) - $h0
    Add-Result 'borderless Alt+right-drag resize' (([Math]::Abs($dw - 120) -le 45) -and ([Math]::Abs($dh - 80) -le 45)) ("size delta ($dw,$dh), expected (120,80)")

    # 2. Regression: normal window still resizes
    [void](Focus-Window $hNormal)
    $r0 = Get-Rect $hNormal
    $w0 = $r0.Right - $r0.Left; $h0 = $r0.Bottom - $r0.Top
    [N]::keybd_event($VK_ALT, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 80
    Invoke-Drag -Button right -SX ($r0.Right - 14) -SY ($r0.Bottom - 14) -DX 120 -DY 80 -Window $hNormal
    [N]::keybd_event($VK_ALT, 0, [N]::KEYUP, [UIntPtr]::Zero); Start-Sleep -Milliseconds 500
    $r1 = Get-Rect $hNormal
    $dw = ($r1.Right - $r1.Left) - $w0; $dh = ($r1.Bottom - $r1.Top) - $h0
    Add-Result 'normal Alt+right-drag resize' (([Math]::Abs($dw - 120) -le 45) -and ([Math]::Abs($dh - 80) -le 45)) ("size delta ($dw,$dh), expected (120,80)")

    # 3. Regression: normal window still moves
    [void](Focus-Window $hNormal)
    $r0 = Get-Rect $hNormal
    [N]::keybd_event($VK_ALT, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 80
    Invoke-Drag -SX ($r0.Left + 200) -SY ($r0.Top + 60) -DX 140 -DY 90 -Window $hNormal
    [N]::keybd_event($VK_ALT, 0, [N]::KEYUP, [UIntPtr]::Zero); Start-Sleep -Milliseconds 500
    $r1 = Get-Rect $hNormal
    $dx = $r1.Left - $r0.Left; $dy = $r1.Top - $r0.Top
    Add-Result 'normal Alt+left-drag move' (([Math]::Abs($dx - 140) -le 35) -and ([Math]::Abs($dy - 90) -le 35)) ("moved by ($dx,$dy), expected (140,90)")

    # 4. Regression: right-click while moving toggles maximize and it sticks
    [void](Focus-Window $hNormal)
    if ([N]::IsZoomed($hNormal)) { [N]::ShowWindow($hNormal, $SW_RESTORE) | Out-Null; Start-Sleep -Milliseconds 300 }
    $r0 = Get-Rect $hNormal
    [N]::keybd_event($VK_ALT, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 80
    [void](Focus-Window $hNormal)
    Move-Cursor ($r0.Left + 200) ($r0.Top + 60)
    [N]::mouse_event([N]::LDOWN, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 150
    for ($i = 1; $i -le 8; $i++) { [N]::mouse_event([N]::MOVE, 16, 10, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 25 }
    Start-Sleep -Milliseconds 150
    [N]::mouse_event([N]::RDOWN, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 80
    [N]::mouse_event([N]::RUP, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 500
    $heldZoom = [N]::IsZoomed($hNormal)
    [N]::mouse_event([N]::LUP, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 250
    [N]::keybd_event($VK_ALT, 0, [N]::KEYUP, [UIntPtr]::Zero); Start-Sleep -Milliseconds 900
    $stickZoom = [N]::IsZoomed($hNormal)
    Add-Result 'right-click-while-moving maximize sticks' ($heldZoom -and $stickZoom) ("maximized while held=$heldZoom, after release=$stickZoom")
    if ($stickZoom) { [N]::ShowWindow($hNormal, $SW_RESTORE) | Out-Null; Start-Sleep -Milliseconds 300 }
}
finally {
    Get-Process | Where-Object { $_.Path -eq $exe } | Stop-Process -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath $exe -Force -ErrorAction SilentlyContinue
    Start-Sleep -Milliseconds 400
    [N]::SetCursorPos($cursor0.X, $cursor0.Y) | Out-Null
}

$failed = @($results | Where-Object { -not $_.Pass }).Count
Log ('=== result: {0}/{1} passed ===' -f ($results.Count - $failed), $results.Count)
$receipt = [ordered]@{ timestamp = (Get-Date -Format o); results = $results }
$receipt | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $ReportDir 'verify-receipt.json') -Encoding UTF8
if ($failed -gt 0) { exit 2 }
exit 0
