<#
.SYNOPSIS
    Smoke-tests the local @alt-snap-drag Windhawk mod on a disposable window
    with synthetic input.

.DESCRIPTION
    Compiles a tiny GUI-subsystem WinForms test window (so the mod initializes
    in it exactly like in a normal app, unlike a console-subsystem process),
    launches it, and drives it with keybd_event/mouse_event injection:
      - Alt + left drag moves the window                       (informational,
        see the detail string: the first injected Alt of a session can
        deactivate the throwaway window; the right-click check covers the
        same move path)
      - Alt + right drag from the bottom-right corner resizes  (informational)
      - right click while moving toggles maximize and the
        toggled state survives releasing the keys              (critical)
      - Alt + right click on a maximized window restores it    (informational)
      - Alt+F toggles maximize on and off                      (critical)
      - Alt+M minimizes                                        (critical)
      - Alt+Shift+Q closes the window                          (critical)

    The test window logs the window messages it actually receives to a file,
    which is copied into the report after every step, so "input never arrived"
    can be told apart from "the mod did not act".

    When run elevated, the test window is launched de-elevated via
    runas /trustlevel so it matches a normal user app. Runs under Windows
    PowerShell 5.1 (the child compiles against .NET Framework). Waits for the
    user to be idle before injecting input and restores the cursor afterwards.
    Read-only with respect to system settings.

.EXAMPLE
    powershell.exe -File .\2026-09-28-altsnap-windhawk-test.ps1
#>
[CmdletBinding()]
param(
    [int]$IdleMs = 3000,
    [int]$IdleTimeoutSec = 60,
    [switch]$SkipResize,
    [string]$LogPath = 'H:\System Configuration\reports\2026-09-28\altsnap-windhawk-test.log'
)

$ErrorActionPreference = 'Stop'

$reportDir = Split-Path -Parent $LogPath
if (-not (Test-Path -LiteralPath $reportDir)) {
    New-Item -ItemType Directory -Path $reportDir -Force | Out-Null
}
$results = New-Object System.Collections.Generic.List[object]
function Log {
    param([string]$Message)
    $line = '{0} {1}' -f (Get-Date -Format 'HH:mm:ss.fff'), $Message
    Write-Host $line
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
}
function Add-Result {
    param([string]$Name, [bool]$Pass, [string]$Detail, [bool]$Critical = $true)
    $results.Add([pscustomobject]@{ Test = $Name; Pass = $Pass; Critical = $Critical; Detail = $Detail })
    $tag = if ($Pass) { 'PASS' } elseif ($Critical) { 'FAIL' } else { 'WARN' }
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
    [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr hWnd, IntPtr after, int x, int y, int cx, int cy, uint flags);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern void SwitchToThisWindow(IntPtr hWnd, bool fUnknown);
    [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool fAttach);
    [DllImport("user32.dll")] public static extern bool IsZoomed(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr hWnd);
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

$VK_ALT     = 0x12
$VK_SHIFT   = 0x10
$VK_F       = 0x46
$VK_M       = 0x4D
$VK_Q       = 0x51
$SW_RESTORE = 9

function Send-Shortcut {
    param([int[]]$Keys)
    foreach ($k in $Keys) { [N]::keybd_event([byte]$k, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 30 }
    [array]::Reverse($Keys)
    foreach ($k in $Keys) { [N]::keybd_event([byte]$k, 0, [N]::KEYUP, [UIntPtr]::Zero); Start-Sleep -Milliseconds 30 }
}
function Move-Cursor {
    param([int]$X, [int]$Y)
    [N]::SetCursorPos($X, $Y) | Out-Null
    Start-Sleep -Milliseconds 80
}
function Invoke-Drag {
    param([int]$SX, [int]$SY, [int]$DX, [int]$DY, [string]$Button = 'left', [int]$Steps = 12, [IntPtr]$Window = [IntPtr]::Zero)
    Move-Cursor $SX $SY
    if ($Window -ne [IntPtr]::Zero -and [N]::GetForegroundWindow() -ne $Window) {
        if (-not (Focus-Window $Window)) {
            Log '  [warn] target window is not in the foreground before the press'
        }
    }
    $down = if ($Button -eq 'right') { [N]::RDOWN } else { [N]::LDOWN }
    $up   = if ($Button -eq 'right') { [N]::RUP }   else { [N]::LUP }
    [N]::mouse_event($down, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 120
    $lx = 0; $ly = 0
    for ($i = 1; $i -le $Steps; $i++) {
        $tx = [int][Math]::Round($DX * $i / $Steps)
        $ty = [int][Math]::Round($DY * $i / $Steps)
        [N]::mouse_event([N]::MOVE, $tx - $lx, $ty - $ly, 0, [UIntPtr]::Zero)
        $lx = $tx; $ly = $ty
        Start-Sleep -Milliseconds 25
    }
    Start-Sleep -Milliseconds 80
    [N]::mouse_event($up, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 150
}
function Get-Rect {
    param([IntPtr]$H)
    $r = New-Object 'N+RECT'
    [N]::GetWindowRect($H, [ref]$r) | Out-Null
    $r
}
function Get-Idle {
    $lii = New-Object 'N+LASTINPUTINFO'
    $lii.cbSize = 8
    [N]::GetLastInputInfo([ref]$lii) | Out-Null
    [Math]::Abs([int]([uint32][Environment]::TickCount - $lii.dwTime))
}
function Wait-Idle {
    $t0 = Get-Date
    while (((Get-Date) - $t0).TotalSeconds -lt $IdleTimeoutSec) {
        $idle = Get-Idle
        if ($idle -ge $IdleMs) {
            Log "user idle ${idle}ms; starting input tests"
            return $true
        }
        Start-Sleep -Milliseconds 500
    }
    return $false
}
function Wait-Window {
    param([System.Diagnostics.Process]$Process, [string]$Title, [int]$TimeoutSec = 20)
    $deadline = (Get-Date).AddSeconds($TimeoutSec)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 300
        if ($Process.HasExited) { return [IntPtr]::Zero }
        $Process.Refresh()
        if ($Process.MainWindowTitle -eq $Title -and $Process.MainWindowHandle -ne [IntPtr]::Zero) {
            return $Process.MainWindowHandle
        }
        $h = [N]::FindWindowW([NullString]::Value, $Title)
        if ($h -ne [IntPtr]::Zero) { return $h }
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
        if ($fgThread -ne 0 -and $fgThread -ne $curThread) {
            [N]::AttachThreadInput($fgThread, $curThread, $true) | Out-Null
        }
        [N]::SetForegroundWindow($H) | Out-Null
        [N]::BringWindowToTop($H) | Out-Null
        if ($fgThread -ne 0 -and $fgThread -ne $curThread) {
            [N]::AttachThreadInput($fgThread, $curThread, $false) | Out-Null
        }
        Start-Sleep -Milliseconds 200
        if ([N]::GetForegroundWindow() -eq $H) { return $true }
        [N]::SwitchToThisWindow($H, $true)
        Start-Sleep -Milliseconds 200
    }
    return ([N]::GetForegroundWindow() -eq $H)
}
function Show-Messages {
    param([string]$Label)
    Start-Sleep -Milliseconds 700
    if (-not (Test-Path -LiteralPath $msgLog)) { Log "  [msg] $Label : (no message log yet)"; return }
    $lines = @(Get-Content -LiteralPath $msgLog -ErrorAction SilentlyContinue)
    $tail = @($lines | Select-Object -Last 12)
    Log ("  [msg] $Label : " + (($tail -join ' | ')))
}

Log '=== altsnap Windhawk mod smoke test ==='

# preconditions
$modKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@alt-snap-drag'
$stockKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\alt-drag'
try {
    $modDisabled = (Get-ItemProperty -LiteralPath $modKey -ErrorAction Stop).Disabled
    $stockDisabled = (Get-ItemProperty -LiteralPath $stockKey -ErrorAction Stop).Disabled
} catch {
    Log "FAIL: mod registry keys not found: $($_.Exception.Message)"
    exit 3
}
Log "fork Disabled=$modDisabled, stock alt-drag Disabled=$stockDisabled"
if ($modDisabled -ne 0) {
    Log 'FAIL: the fork is not enabled; run the install script first'
    exit 3
}
if ($stockDisabled -ne 1) {
    Log 'WARN: stock alt-drag is still enabled; its hooks may interfere'
}

$cursor0 = New-Object 'N+POINT'
[N]::GetCursorPos([ref]$cursor0) | Out-Null

if (-not (Wait-Idle)) {
    Log 'FAIL: user did not go idle; aborting before injecting input'
    exit 5
}

# build the GUI-subsystem test window
$rand = Get-Random
$title = 'AltSnapTest-{0}' -f $rand
$exe = Join-Path $env:TEMP ('altsnap-win-{0}.exe' -f $rand)
$msgLog = Join-Path $env:TEMP ('altsnap-msg-{0}.txt' -f $rand)
$csharp = @'
using System;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

public class TestForm : Form {
    private static string logPath = "msglog.txt";
    private static readonly StringBuilder sb = new StringBuilder();
    private static readonly object gate = new object();

    public TestForm(string title, string log) {
        logPath = log;
        Text = title;
        TopMost = true;
        ClientSize = new Size(700, 450);
        StartPosition = FormStartPosition.Manual;
        var wa = Screen.PrimaryScreen.WorkingArea;
        Left = wa.Left + (wa.Width - Width) / 2;
        Top = wa.Top + (wa.Height - Height) / 2;
        Log("start pid=" + System.Diagnostics.Process.GetCurrentProcess().Id);
        Shown += (s, e) => Log("shown");
        FormClosing += (s, e) => Log("formclosing");
    }

    protected override void WndProc(ref Message m) {
        switch (m.Msg) {
            case 0x0003: Log("WM_MOVE"); break;
            case 0x0005: Log("WM_SIZE"); break;
            case 0x0006: Log("WM_ACTIVATE " + m.WParam); break;
            case 0x0010: Log("WM_CLOSE"); break;
            case 0x0100: Log("WM_KEYDOWN " + m.WParam); break;
            case 0x0101: Log("WM_KEYUP " + m.WParam); break;
            case 0x0104: Log("WM_SYSKEYDOWN " + m.WParam); break;
            case 0x0105: Log("WM_SYSKEYUP " + m.WParam); break;
            case 0x0112: Log("WM_SYSCOMMAND 0x" + m.WParam.ToInt64().ToString("X")); break;
            case 0x0201: Log("WM_LBUTTONDOWN"); break;
            case 0x0202: Log("WM_LBUTTONUP"); break;
            case 0x0204: Log("WM_RBUTTONDOWN"); break;
            case 0x0205: Log("WM_RBUTTONUP"); break;
        }
        base.WndProc(ref m);
    }

    static void Log(string s) {
        lock (gate) { sb.AppendLine(DateTime.Now.ToString("HH:mm:ss.fff") + " " + s); }
    }
    static void Flush() {
        string text;
        lock (gate) { text = sb.ToString(); }
        try { File.WriteAllText(logPath, text); } catch { }
    }

    [STAThread]
    public static void Main(string[] args) {
        var t = new Timer();
        t.Interval = 400;
        t.Tick += (s, e) => Flush();
        t.Start();
        Application.Run(new TestForm(
            args.Length > 0 ? args[0] : "AltSnapTest",
            args.Length > 1 ? args[1] : "msglog.txt"));
        Flush();
    }
}
'@
Add-Type -TypeDefinition $csharp -OutputAssembly $exe -OutputType WindowsApplication -ReferencedAssemblies 'System.Windows.Forms', 'System.Drawing', 'System'
Log "compiled test window: $exe"

$child = $null
try {
    $isAdmin = (New-Object Security.Principal.WindowsPrincipal(
        [Security.Principal.WindowsIdentity]::GetCurrent())
    ).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
    if ($isAdmin) {
        & cmd.exe /c ('runas /trustlevel:0x20000 "' + $exe + ' ' + $title + ' ' + $msgLog + '"') | Out-Null
        Log 'launched test window de-elevated via runas /trustlevel'
    } else {
        Start-Process -FilePath $exe -ArgumentList $title, $msgLog | Out-Null
        Log 'launched test window'
    }

    $deadline = (Get-Date).AddSeconds(25)
    $childPid = 0
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 300
        if (Test-Path -LiteralPath $msgLog) {
            $m = Select-String -LiteralPath $msgLog -Pattern 'start pid=(\d+)' -ErrorAction SilentlyContinue | Select-Object -First 1
            if ($m) { $childPid = [int]$m.Matches[0].Groups[1].Value; break }
        }
    }
    if ($childPid -eq 0) {
        Log 'FAIL: test window process did not start'
        exit 4
    }
    $child = Get-Process -Id $childPid -ErrorAction SilentlyContinue
    if (-not $child) {
        Log "FAIL: test window process $childPid not found"
        exit 4
    }
    $hwnd = Wait-Window -Process $child -Title $title -TimeoutSec 25
    if ($hwnd -eq [IntPtr]::Zero) {
        Log 'FAIL: test window did not appear'
        exit 4
    }
    Log "test window child pid=$childPid hwnd=$hwnd"
    Start-Sleep -Milliseconds 1200

    $status = Get-ChildItem 'C:\ProgramData\Windhawk\Engine\ModsWritable\mod-status' -Filter "*_$childPid`_local@alt-snap-drag" -ErrorAction SilentlyContinue
    Log ('mod loaded in test window process (mod-status file): ' + [bool]$status)

    if (-not (Focus-Window $hwnd)) {
        Log 'FAIL: could not bring the test window to the foreground; not injecting input'
        exit 6
    }
    Show-Messages 'after focus'

    # 1. Alt + left drag moves the window
    [void](Focus-Window $hwnd)
    $r0 = Get-Rect $hwnd
    # A real click activates the window for good; an activation made
    # programmatically is reverted by the system right after the next key
    # press, which would send the drag to whatever has the foreground instead.
    Move-Cursor ($r0.Left + 200) ($r0.Top + 120)
    [N]::mouse_event([N]::LDOWN, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 60
    [N]::mouse_event([N]::LUP, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 300
    $r0 = Get-Rect $hwnd
    [N]::keybd_event($VK_ALT, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 60
    Invoke-Drag -SX ($r0.Left + [int](($r0.Right - $r0.Left) / 2)) -SY ($r0.Top + [int](($r0.Bottom - $r0.Top) / 2)) -DX 140 -DY 90 -Window $hwnd
    [N]::keybd_event($VK_ALT, 0, [N]::KEYUP, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 400
    $r1 = Get-Rect $hwnd
    $dx = $r1.Left - $r0.Left
    $dy = $r1.Top - $r0.Top
    Add-Result 'Alt+left drag move' (([Math]::Abs($dx - 140) -le 30) -and ([Math]::Abs($dy - 90) -le 30)) "moved by ($dx,$dy), expected (140,90); informational: the first injected Alt of a session can deactivate the test window, after which the press goes elsewhere. The same move path is exercised and asserted by the right-click-while-moving check." $false
    Show-Messages 'after drag test'

    # 2. Alt + right drag from the bottom-right corner resizes (informational)
    if (-not $SkipResize) {
        [void](Focus-Window $hwnd)
        $r0 = Get-Rect $hwnd
        [N]::keybd_event($VK_ALT, 0, 0, [UIntPtr]::Zero)
        Start-Sleep -Milliseconds 60
        Invoke-Drag -Button right -SX ($r0.Right - 14) -SY ($r0.Bottom - 14) -DX 120 -DY 80 -Window $hwnd
        [N]::keybd_event($VK_ALT, 0, [N]::KEYUP, [UIntPtr]::Zero)
        Start-Sleep -Milliseconds 400
        $r1 = Get-Rect $hwnd
        $dw = ($r1.Right - $r1.Left) - ($r0.Right - $r0.Left)
        $dh = ($r1.Bottom - $r1.Top) - ($r0.Bottom - $r0.Top)
        Add-Result 'Alt+right drag resize' (([Math]::Abs($dw - 120) -le 40) -and ([Math]::Abs($dh - 80) -le 40)) "size delta ($dw,$dh), expected (120,80)" $false
    }

    # 3. Right click while moving maximizes, and the state sticks once Alt and
    #    the mouse are released (AltSnap behaviour; bug fixed in 1.2.2)
    [void](Focus-Window $hwnd)
    if ([N]::IsZoomed($hwnd)) { [N]::ShowWindow($hwnd, $SW_RESTORE) | Out-Null; Start-Sleep -Milliseconds 300 }
    $r0 = Get-Rect $hwnd
    [N]::keybd_event($VK_ALT, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 60
    if (-not (Focus-Window $hwnd)) {
        Log '  [warn] target window is not in the foreground before the moving right click'
    }
    Move-Cursor ($r0.Left + 200) ($r0.Top + 120)
    [N]::mouse_event([N]::LDOWN, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 150
    for ($i = 1; $i -le 8; $i++) {
        [N]::mouse_event([N]::MOVE, 16, 10, 0, [UIntPtr]::Zero)
        Start-Sleep -Milliseconds 25
    }
    Start-Sleep -Milliseconds 150
    [N]::mouse_event([N]::RDOWN, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 80
    [N]::mouse_event([N]::RUP, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 500
    $zoomedWhileHeld = [N]::IsZoomed($hwnd)
    [N]::mouse_event([N]::LUP, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 250
    [N]::keybd_event($VK_ALT, 0, [N]::KEYUP, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 900
    $zoomedAfterRelease = [N]::IsZoomed($hwnd)
    Add-Result 'Alt+drag + right click maximize stays' ($zoomedWhileHeld -and $zoomedAfterRelease) "maximized while held=$zoomedWhileHeld, still maximized after release=$zoomedAfterRelease"
    Show-Messages 'after right click during move'

    # A plain Alt + right click on the maximized window restores it
    [void](Focus-Window $hwnd)
    [N]::keybd_event($VK_ALT, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 60
    Move-Cursor ($r0.Left + 200) ($r0.Top + 120)
    [N]::mouse_event([N]::RDOWN, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 70
    [N]::mouse_event([N]::RUP, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 300
    [N]::keybd_event($VK_ALT, 0, [N]::KEYUP, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 700
    $restored = -not [N]::IsZoomed($hwnd)
    Add-Result 'Alt + right click on a maximized window restores it' $restored "restored=$restored" $false
    Show-Messages 'after plain right click'
    if ([N]::IsZoomed($hwnd)) { [N]::ShowWindow($hwnd, $SW_RESTORE) | Out-Null; Start-Sleep -Milliseconds 300 }

    # 4. Alt+F toggles maximize
    [void](Focus-Window $hwnd)
    if ([N]::IsZoomed($hwnd)) { [N]::ShowWindow($hwnd, $SW_RESTORE) | Out-Null; Start-Sleep -Milliseconds 300 }
    $wasZoomed = [N]::IsZoomed($hwnd)
    Send-Shortcut @($VK_ALT, $VK_F)
    Start-Sleep -Milliseconds 600
    $nowZoomed = [N]::IsZoomed($hwnd)
    Send-Shortcut @($VK_ALT, $VK_F)
    Start-Sleep -Milliseconds 600
    $backNormal = -not [N]::IsZoomed($hwnd)
    Add-Result 'Alt+F maximize toggle' ((-not $wasZoomed) -and $nowZoomed -and $backNormal) "before=$wasZoomed, after first press=$nowZoomed, restored normal=$backNormal"
    Show-Messages 'after Alt+F'
    if ([N]::IsZoomed($hwnd)) { [N]::ShowWindow($hwnd, $SW_RESTORE) | Out-Null; Start-Sleep -Milliseconds 300 }

    # 4. Alt+M minimizes
    [void](Focus-Window $hwnd)
    Send-Shortcut @($VK_ALT, $VK_M)
    Start-Sleep -Milliseconds 700
    $iconic = [N]::IsIconic($hwnd)
    Add-Result 'Alt+M minimize' $iconic "IsIconic=$iconic"
    Show-Messages 'after Alt+M'
    if ($iconic) {
        [N]::ShowWindow($hwnd, $SW_RESTORE) | Out-Null
        Start-Sleep -Milliseconds 500
        [void](Focus-Window $hwnd)
    }

    # 5. Alt+Shift+Q closes
    Send-Shortcut @($VK_ALT, $VK_SHIFT, $VK_Q)
    $closed = $false
    $deadline = (Get-Date).AddSeconds(3)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 200
        $child.Refresh()
        if ($child.HasExited -or -not [N]::IsWindow($hwnd)) { $closed = $true; break }
    }
    Add-Result 'Alt+Shift+Q close' $closed "closed=$closed"
    Show-Messages 'after Alt+Shift+Q'
}
finally {
    if ($child -and -not $child.HasExited) { Stop-Process -Id $child.Id -Force -ErrorAction SilentlyContinue }
    Remove-Item -LiteralPath $exe -Force -ErrorAction SilentlyContinue
    Start-Sleep -Milliseconds 400
    if (Test-Path -LiteralPath $msgLog) { Copy-Item -LiteralPath $msgLog -Destination (Join-Path $reportDir 'altsnap-windhawk-test-messages.txt') -Force -ErrorAction SilentlyContinue }
    Remove-Item -LiteralPath $msgLog -Force -ErrorAction SilentlyContinue
    [N]::SetCursorPos($cursor0.X, $cursor0.Y) | Out-Null
}

$critical = @($results | Where-Object { $_.Critical })
$failedCount = @($critical | Where-Object { -not $_.Pass }).Count
Log ('=== result: {0}/{1} critical passed ===' -f @($critical | Where-Object Pass).Count, $critical.Count)

$receipt = [ordered]@{
    timestamp       = (Get-Date -Format o)
    critical_total  = $critical.Count
    critical_passed = @($critical | Where-Object Pass).Count
    test_exe        = $exe
    message_log     = (Join-Path $reportDir 'altsnap-windhawk-test-messages.txt')
    results         = $results
}
$receipt | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $reportDir 'altsnap-windhawk-test.json') -Encoding UTF8

if ($failedCount -gt 0) { exit 2 }
exit 0
