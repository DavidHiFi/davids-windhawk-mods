#requires -Version 5.1
<#
  Windhawk elevated-window baseline tests.

  Roles:
    orch        (default, medium) orchestrates all phases, writes result JSON
    elev        elevated helper actions: runall | launch | snap | kill | inspect
                (invoked through a silent RunAs cmd wrapper; UAC dialogs are
                disabled on this machine)
    hotkey-wait medium child: registers a spare hotkey and waits for WM_HOTKEY

  Result JSON: reports\2026-10-02-windhawk-elev-test\result.json
#>
[CmdletBinding()]
param(
    [ValidateSet('orch', 'elev', 'hotkey-wait')]
    [string]$Role = 'orch',

    [ValidateSet('', 'runall', 'launch', 'snap', 'kill', 'inspect')]
    [string]$ElevAction = '',

    [int]$TargetPid = 0,

    # comma list (double-quoted when passed through cmd): AltU, AltShiftRight, CtrlAltShiftY
    [string]$Combo = 'AltU',

    [string]$ResultPath = '',
    [string]$LogDir = '',
    [string]$ReadyPath = '',
    [string]$HotkeyResultPath = ''
)

$ErrorActionPreference = 'Stop'

if (-not $LogDir) {
    $LogDir = Join-Path $PSScriptRoot '..\reports\2026-10-02-windhawk-elev-test'
}
$LogDir = [System.IO.Path]::GetFullPath($LogDir)

Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

public static class WH {
    [StructLayout(LayoutKind.Sequential)]
    public struct RECT { public int Left, Top, Right, Bottom; }

    [StructLayout(LayoutKind.Sequential)]
    public struct MSG {
        public IntPtr hwnd; public uint message; public IntPtr wParam;
        public IntPtr lParam; public uint time; public POINT pt;
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct POINT { public int x, y; }

    [StructLayout(LayoutKind.Sequential)]
    public struct KEYBDINPUT {
        public ushort wVk; public ushort wScan; public uint dwFlags;
        public uint time; public IntPtr dwExtraInfo;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct MOUSEINPUT { public int dx, dy; public uint mouseData, dwFlags, time; public IntPtr dwExtra; }

    [StructLayout(LayoutKind.Sequential)]
    public struct HARDWAREINPUT { public uint uMsg; public ushort wL, wH; }

    // Native INPUT is 40 bytes on x64: the union is sized by MOUSEINPUT, not
    // KEYBDINPUT. A 32-byte union makes SendInput fail with ERROR_INVALID_PARAMETER.
    [StructLayout(LayoutKind.Explicit)]
    public struct INPUTUNION {
        [FieldOffset(0)] public KEYBDINPUT ki;
        [FieldOffset(0)] public MOUSEINPUT mi;
        [FieldOffset(0)] public HARDWAREINPUT hi;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct INPUT { public uint type; public INPUTUNION u; }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct WNDCLASS {
        public uint style;
        public WndProcDelegate lpfnWndProc;
        public int cbClsExtra, cbWndExtra;
        public IntPtr hInstance, hIcon, hCursor, hbrBackground;
        public string lpszMenuName, lpszClassName;
    }

    public delegate IntPtr WndProcDelegate(IntPtr h, uint msg, IntPtr w, IntPtr l);
    delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);
    static WndProcDelegate s_wndProcKeep;   // keep alive for native callbacks

    [DllImport("user32.dll", SetLastError = true)]
    static extern bool EnumWindows(EnumWindowsProc cb, IntPtr lParam);
    [DllImport("user32.dll")]
    static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint pid);
    [DllImport("user32.dll")]
    public static extern bool IsWindowVisible(IntPtr hWnd);
    [DllImport("user32.dll")]
    static extern IntPtr GetWindow(IntPtr hWnd, uint cmd);
    [DllImport("user32.dll", SetLastError = true)]
    static extern bool GetWindowRect(IntPtr hWnd, out RECT rect);
    [DllImport("user32.dll", SetLastError = true)]
    public static extern bool SetWindowPos(IntPtr hWnd, IntPtr insertAfter,
        int x, int y, int cx, int cy, uint flags);
    [DllImport("user32.dll")]
    public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll", SetLastError = true)]
    public static extern bool SetForegroundWindow(IntPtr hWnd);
    [DllImport("user32.dll")]
    static extern int GetWindowTextLength(IntPtr hWnd);
    [DllImport("user32.dll")]
    static extern int GetWindowText(StringBuilder sb, int max);
    [DllImport("user32.dll", CharSet = CharSet.Auto)]
    static extern int GetClassName(IntPtr hWnd, StringBuilder sb, int max);
    [DllImport("user32.dll")]
    static extern bool BringWindowToTop(IntPtr hWnd);
    [DllImport("user32.dll")]
    static extern bool ShowWindow(IntPtr hWnd, int cmd);
    [DllImport("user32.dll")]
    static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool attach);
    [DllImport("kernel32.dll")]
    static extern uint GetCurrentThreadId();
    [DllImport("user32.dll")]
    static extern bool RegisterHotKey(IntPtr hWnd, int id, uint fsModifiers, uint vk);
    [DllImport("user32.dll")]
    static extern bool UnregisterHotKey(IntPtr hWnd, int id);
    [DllImport("user32.dll")]
    static extern bool PeekMessage(out MSG m, IntPtr hWnd, uint min, uint max, uint flags);
    [DllImport("user32.dll")]
    static extern bool GetMessage(out MSG m, IntPtr hWnd, uint min, uint max);
    [DllImport("user32.dll")]
    static extern bool TranslateMessage(ref MSG m);
    [DllImport("user32.dll")]
    static extern IntPtr DispatchMessage(ref MSG m);
    [DllImport("user32.dll")]
    static extern IntPtr DefWindowProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)]
    static extern ushort RegisterClass(ref WNDCLASS lpWndClass);
    [DllImport("user32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    static extern IntPtr CreateWindowEx(uint exStyle, string cls, string title,
        uint style, int x, int y, int w, int h, IntPtr parent, IntPtr menu,
        IntPtr hInstance, IntPtr param);
    [DllImport("user32.dll")]
    static extern bool UpdateWindow(IntPtr hWnd);
    [DllImport("user32.dll")]
    static extern bool DestroyWindow(IntPtr hWnd);
    [DllImport("user32.dll")]
    static extern IntPtr LoadCursor(IntPtr hInstance, IntPtr name);
    [DllImport("kernel32.dll", CharSet = CharSet.Unicode)]
    static extern IntPtr GetModuleHandle(string name);
    [DllImport("user32.dll")]
    public static extern uint SendInput(uint n, INPUT[] p, int cbSize);
    [DllImport("user32.dll")]
    static extern bool SetCursorPos(int x, int y);
    [DllImport("user32.dll")]
    static extern bool GetCursorPos(out POINT p);
    [DllImport("kernel32.dll")]
    static extern IntPtr OpenProcess(uint access, bool inherit, uint pid);
    [DllImport("kernel32.dll")]
    static extern bool CloseHandle(IntPtr h);
    [DllImport("advapi32.dll", SetLastError = true)]
    static extern bool OpenProcessToken(IntPtr process, uint access, out IntPtr token);
    [DllImport("advapi32.dll", SetLastError = true)]
    static extern bool GetTokenInformation(IntPtr token, int cls, ref int info, int len, out int retLen);

    const uint PROCESS_QUERY_LIMITED = 0x1000;
    const uint TOKEN_QUERY = 0x0008;
    const uint GW_OWNER = 4;

    public delegate bool Visit(IntPtr hwnd);

    public static bool EnumAllWindows(Visit cb) {
        return EnumWindows((h, l) => cb(h), IntPtr.Zero);
    }

    public static long PidOfWindow(IntPtr hwnd) {
        uint pid;
        GetWindowThreadProcessId(hwnd, out pid);
        return pid;
    }

    public static bool IsMainWindow(IntPtr hwnd) {
        return IsWindowVisible(hwnd)
            && GetWindow(hwnd, GW_OWNER) == IntPtr.Zero
            && GetWindowTextLength(hwnd) > 0;
    }

    public static string TitleOf(IntPtr hwnd) {
        int len = GetWindowTextLength(hwnd);
        var sb = new StringBuilder(len + 1);
        GetWindowText(sb, sb.Capacity);
        return sb.ToString();
    }

    public static string ClassOf(IntPtr hwnd) {
        var sb = new StringBuilder(256);
        GetClassName(hwnd, sb, sb.Capacity);
        return sb.ToString();
    }

    public static long FindMainWindow(long pid) {
        long found = 0;
        EnumAllWindows(h => {
            if (found == 0 && PidOfWindow(h) == (uint)pid && IsMainWindow(h)) {
                found = h.ToInt64();
            }
            return true;
        });
        return found;
    }

    // Untitled-window fallback: first visible unowned window with a real rect.
    public static long FindVisibleTopWindow(long pid) {
        long found = 0;
        EnumAllWindows(h => {
            if (found == 0 && PidOfWindow(h) == (uint)pid && IsWindowVisible(h)
                && GetWindow(h, GW_OWNER) == IntPtr.Zero) {
                RECT r;
                if (GetWindowRect(h, out r) && (r.Right - r.Left) > 50 && (r.Bottom - r.Top) > 50) {
                    found = h.ToInt64();
                }
            }
            return true;
        });
        return found;
    }

    public static long FindWindowByTitle(string title) {
        long found = 0;
        EnumAllWindows(h => {
            if (found == 0 && IsMainWindow(h) && TitleOf(h) == title) {
                found = h.ToInt64();
            }
            return true;
        });
        return found;
    }

    public static string ListWindows(long pid) {
        var sb = new StringBuilder();
        EnumAllWindows(h => {
            if (PidOfWindow(h) == (uint)pid) {
                sb.Append(h.ToInt64()).Append('|')
                  .Append(IsWindowVisible(h) ? "vis" : "hid").Append('|')
                  .Append(GetWindow(h, GW_OWNER) != IntPtr.Zero ? "owned" : "top").Append('|')
                  .Append(TitleOf(h)).Append('|')
                  .Append(ClassOf(h)).Append(';');
            }
            return true;
        });
        return sb.Length == 0 ? "none" : sb.ToString();
    }

    public static string GetRect(long hwnd) {
        RECT r;
        if (!GetWindowRect(new IntPtr(hwnd), out r)) return "err" + Marshal.GetLastWin32Error();
        return r.Left + "," + r.Top + "," + r.Right + "," + r.Bottom;
    }

    public static string MoveBy(long hwnd, int dx, int dy) {
        RECT r;
        if (!GetWindowRect(new IntPtr(hwnd), out r)) return "pre-err" + Marshal.GetLastWin32Error();
        bool ok = SetWindowPos(new IntPtr(hwnd), IntPtr.Zero,
            r.Left + dx, r.Top + dy, 0, 0,
            0x0001 /*NOSIZE*/ | 0x0002 /*NOMOVE*/ | 0x0004 /*NOZORDER*/ | 0x0010 /*NOACTIVATE*/);
        int err = ok ? 0 : Marshal.GetLastWin32Error();
        Thread.Sleep(300);
        RECT r2;
        GetWindowRect(new IntPtr(hwnd), out r2);
        bool moved = (r2.Left != r.Left || r2.Top != r.Top);
        return "setOk=" + ok + " win32Err=" + err + " moved=" + moved +
               " before=" + r.Left + "," + r.Top + " after=" + r2.Left + "," + r2.Top;
    }

    // Returns "already" / "*-setfg" on success, "fg-failed ..." otherwise.
    public static string FocusWindow(long hwnd) {
        IntPtr h = new IntPtr(hwnd);
        if (GetForegroundWindow() == h) return "already";
        uint dummyPid;
        uint fg = GetWindowThreadProcessId(GetForegroundWindow(), out dummyPid);
        uint me = GetCurrentThreadId();

        ShowWindow(h, 9 /*SW_RESTORE*/);
        BringWindowToTop(h);
        SetForegroundWindow(h);
        Thread.Sleep(150);
        if (GetForegroundWindow() == h) return "plain-setfg";

        AttachThreadInput(me, fg, true);
        SetForegroundWindow(h);
        Thread.Sleep(150);
        AttachThreadInput(me, fg, false);
        if (GetForegroundWindow() == h) return "attach-setfg";

        // Tap F24 (no-op key): injected input grants foreground rights to the
        // injector; avoids ALT, which Electron/Chrome windows tend to swallow.
        for (int i = 0; i < 3; i++) {
            KeyEvent(0x87, false); KeyEvent(0x87, true);
            Thread.Sleep(80);
            SetForegroundWindow(h);
            Thread.Sleep(120);
            if (GetForegroundWindow() == h) return "f24-setfg";
        }
        for (int i = 0; i < 2; i++) {
            KeyEvent(0x12, false); KeyEvent(0x12, true);
            Thread.Sleep(80);
            SetForegroundWindow(h);
            Thread.Sleep(120);
            if (GetForegroundWindow() == h) return "alt-setfg";
        }
        long cur = PidOfWindow(GetForegroundWindow());
        return "fg-failed currentFgPid=" + cur + " fgClass=" + ClassOf(GetForegroundWindow());
    }

    static void KeyEvent(ushort vk, bool up) {
        var inputs = new INPUT[1];
        inputs[0].type = 1; // INPUT_KEYBOARD
        inputs[0].u.ki.wVk = vk;
        inputs[0].u.ki.dwFlags = up ? 0x0002u : 0u;
        SendInput(1, inputs, Marshal.SizeOf(typeof(INPUT)));
    }

    static void KeyTap(ushort vk) { KeyEvent(vk, false); KeyEvent(vk, true); }

    public static string SendCombo(string combo) {
        switch (combo.Trim().Trim('\'', '"')) {
            case "AltU":
                KeyEvent(0x12, false); KeyTap(0x55); KeyEvent(0x12, true);
                return "sent AltU";
            case "AltShiftRight":
                KeyEvent(0x12, false); KeyEvent(0x10, false);
                KeyTap(0x27);
                KeyEvent(0x10, true); KeyEvent(0x12, true);
                return "sent AltShiftRight";
            case "CtrlAltShiftY":
                KeyEvent(0x11, false); KeyEvent(0x12, false); KeyEvent(0x10, false);
                KeyTap(0x59);
                KeyEvent(0x10, true); KeyEvent(0x12, true); KeyEvent(0x11, true);
                return "sent CtrlAltShiftY";
            default:
                return "unknown-combo " + combo;
        }
    }

    static void MouseEvent(uint flags, uint data) {
        var inputs = new INPUT[1];
        inputs[0].type = 0; // INPUT_MOUSE
        inputs[0].u.mi.dwFlags = flags;
        inputs[0].u.mi.mouseData = data;
        SendInput(1, inputs, Marshal.SizeOf(typeof(INPUT)));
    }

    // T7: medium-injected Alt+left-drag against the target window, the way
    // alt-snap-drag expects it (moveTrigger = Alt + left, delay 0, title-bar
    // optional). Reports whether the window moved.
    public static string AltDragTest(long hwnd) {
        IntPtr h = new IntPtr(hwnd);
        string focus = FocusWindow(hwnd);
        if (focus.StartsWith("fg-failed")) return "drag-skipped focus=" + focus;
        RECT r;
        if (!GetWindowRect(h, out r)) return "pre-err" + Marshal.GetLastWin32Error();
        string before = r.Left + "," + r.Top + "," + r.Right + "," + r.Bottom;
        int sx = r.Left + Math.Max(80, (r.Right - r.Left) / 3);
        int sy = r.Top + 20;
        var log = new System.Text.StringBuilder();
        bool ok = SetCursorPos(sx, sy);
        Thread.Sleep(150);
        POINT cp;
        GetCursorPos(out cp);
        log.Append(" set=").Append(ok).Append(" c0=").Append(cp.x).Append(',').Append(cp.y);
        KeyEvent(0x12, false);                 // Alt down
        Thread.Sleep(80);
        MouseEvent(0x0002, 0);                 // LEFTDOWN
        Thread.Sleep(120);
        GetCursorPos(out cp);
        log.Append(" downC=").Append(cp.x).Append(',').Append(cp.y)
            .Append(" fg=").Append(PidOfWindow(GetForegroundWindow()));
        int dx = 170, dy = 90;
        for (int i = 1; i <= 6; i++) {
            SetCursorPos(sx + dx * i / 6, sy + dy * i / 6);
            Thread.Sleep(60);
            if (i == 3) {
                GetCursorPos(out cp);
                RECT rm;
                GetWindowRect(h, out rm);
                log.Append(" midC=").Append(cp.x).Append(',').Append(cp.y)
                    .Append(" midRect=").Append(rm.Left).Append(',').Append(rm.Top);
            }
        }
        Thread.Sleep(150);
        GetCursorPos(out cp);
        RECT rEnd;
        GetWindowRect(h, out rEnd);
        log.Append(" preUpC=").Append(cp.x).Append(',').Append(cp.y)
            .Append(" preUpRect=").Append(rEnd.Left).Append(',').Append(rEnd.Top);
        MouseEvent(0x0004, 0);                 // LEFTUP
        Thread.Sleep(80);
        KeyEvent(0x12, true);                  // Alt up
        Thread.Sleep(900);
        RECT r2;
        GetWindowRect(h, out r2);
        string after = r2.Left + "," + r2.Top + "," + r2.Right + "," + r2.Bottom;
        GetCursorPos(out cp);
        bool changed = (r2.Left != r.Left || r2.Top != r.Top);
        return "focus=" + focus + " before=" + before + " after=" + after +
               " changed=" + changed + " endC=" + cp.x + "," + cp.y + log.ToString();
    }

    public static bool SelfElevated() {
        IntPtr proc = OpenProcess(PROCESS_QUERY_LIMITED, false,
            (uint)System.Diagnostics.Process.GetCurrentProcess().Id);
        if (proc == IntPtr.Zero) return false;
        IntPtr tok;
        bool ok = OpenProcessToken(proc, TOKEN_QUERY, out tok);
        CloseHandle(proc);
        if (!ok) return false;
        int info = 0, ret;
        ok = GetTokenInformation(tok, 20 /*TokenElevation*/, ref info, 4, out ret);
        CloseHandle(tok);
        return ok && info != 0;
    }

    public static bool ProcessElevated(long pid) {
        IntPtr proc = OpenProcess(PROCESS_QUERY_LIMITED, false, (uint)pid);
        if (proc == IntPtr.Zero) return false;
        IntPtr tok;
        bool ok = OpenProcessToken(proc, TOKEN_QUERY, out tok);
        CloseHandle(proc);
        if (!ok) return false;
        int info = 0, ret;
        ok = GetTokenInformation(tok, 20, ref info, 4, out ret);
        CloseHandle(tok);
        return ok && info != 0;
    }

    public static string ProcessElevatedEx(long pid) {
        IntPtr proc = OpenProcess(PROCESS_QUERY_LIMITED, false, (uint)pid);
        if (proc == IntPtr.Zero) return "notopen-err" + Marshal.GetLastWin32Error();
        CloseHandle(proc);
        return ProcessElevated(pid) ? "elevated" : "medium";
    }

    public static string ListMatchingModules(long pid, string pattern) {
        try {
            var p = System.Diagnostics.Process.GetProcessById((int)pid);
            var sb = new StringBuilder();
            foreach (System.Diagnostics.ProcessModule m in p.Modules) {
                if (m.ModuleName.IndexOf(pattern, StringComparison.OrdinalIgnoreCase) >= 0 ||
                    m.ModuleName.IndexOf("snap", StringComparison.OrdinalIgnoreCase) >= 0 ||
                    m.ModuleName.IndexOf("drag", StringComparison.OrdinalIgnoreCase) >= 0) {
                    sb.Append(m.ModuleName).Append(';');
                }
            }
            return sb.Length == 0 ? "none" : sb.ToString();
        } catch (Exception e) {
            return "enum-fail:" + e.GetType().Name + ":" + e.Message;
        }
    }

    // Spare-hotkey waiter: register Ctrl+Alt+Shift+Y on this thread, pump.
    public static string WaitHotkey(int timeoutMs) {
        const int id = 0x5753;
        uint mods = 0x0002 | 0x0001 | 0x0004; // CONTROL|ALT|SHIFT
        if (!RegisterHotKey(IntPtr.Zero, id, mods, 0x59)) {
            return "register-fail-" + Marshal.GetLastWin32Error();
        }
        var deadline = DateTime.UtcNow.AddMilliseconds(timeoutMs);
        string outcome = "timeout";
        MSG m;
        while (DateTime.UtcNow < deadline) {
            while (PeekMessage(out m, IntPtr.Zero, 0, 0, 1)) {
                if (m.message == 0x0312) { // WM_HOTKEY
                    outcome = "received-wparam" + m.wParam.ToInt64();
                    goto done;
                }
                TranslateMessage(ref m);
                DispatchMessage(ref m);
            }
            Thread.Sleep(30);
        }
    done:
        UnregisterHotKey(IntPtr.Zero, id);
        return outcome;
    }

    // Own medium test window on a background thread (medium by construction).
    static long s_testHwnd = 0;
    public static long CreateTestWindow(string title) {
        s_testHwnd = 0;
        var ready = new ManualResetEvent(false);
        var t = new Thread(() => {
            s_wndProcKeep = TestWndProc;
            var wc = new WNDCLASS {
                lpfnWndProc = s_wndProcKeep,
                hInstance = GetModuleHandle(null),
                lpszClassName = "WHTestWin" + GetCurrentThreadId(),
                hCursor = LoadCursor(IntPtr.Zero, (IntPtr)32512),
                hbrBackground = (IntPtr)6,               // COLOR_WINDOW+1
            };
            if (RegisterClass(ref wc) == 0) { ready.Set(); return; }
            IntPtr h = CreateWindowEx(0, wc.lpszClassName, title,
                0x00CF0000 /*WS_OVERLAPPEDWINDOW*/,
                120, 140, 460, 320,
                IntPtr.Zero, IntPtr.Zero, wc.hInstance, IntPtr.Zero);
            if (h != IntPtr.Zero) {
                ShowWindow(h, 5 /*SW_SHOW*/);
                UpdateWindow(h);
                s_testHwnd = h.ToInt64();
            }
            ready.Set();
            MSG m;
            while (GetMessage(out m, IntPtr.Zero, 0, 0)) {
                TranslateMessage(ref m);
                DispatchMessage(ref m);
            }
        });
        t.IsBackground = true;
        t.Start();
        ready.WaitOne(5000);
        Thread.Sleep(300);
        return s_testHwnd;
    }

    static IntPtr TestWndProc(IntPtr h, uint msg, IntPtr w, IntPtr l) {
        return DefWindowProc(h, msg, w, l);
    }
}
'@

function Write-JsonResult([string]$Path, $Object) {
    $dir = Split-Path -Parent $Path
    if ($dir -and -not (Test-Path $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
    $Object | ConvertTo-Json -Depth 10 | Set-Content -LiteralPath $Path -Encoding UTF8
}

function Wait-ForFile([string]$Path, [int]$TimeoutSec) {
    $deadline = (Get-Date).AddSeconds($TimeoutSec)
    while ((Get-Date) -lt $deadline) {
        if ((Test-Path -LiteralPath $Path) -and (Get-Item -LiteralPath $Path).Length -gt 0) { return $true }
        Start-Sleep -Milliseconds 150
    }
    return $false
}

function Invoke-ElevatedAction {
    param([string]$ArgsString, [string]$OutFile)
    $cmdPath = Join-Path $LogDir 'run-elev.cmd'
    $ps = "powershell.exe -NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`" $ArgsString -LogDir `"$LogDir`" -ResultPath `"$OutFile`""
    "@echo off`r`n$ps > `"$OutFile.console.log`" 2>&1" | Set-Content -LiteralPath $cmdPath -Encoding ASCII
    if (Test-Path -LiteralPath $OutFile) { Remove-Item -LiteralPath $OutFile -Force }
    $p = Start-Process -FilePath $cmdPath -Verb RunAs -PassThru -WindowStyle Hidden
    $null = $p.WaitForExit(240000)
    if (-not (Wait-ForFile -Path $OutFile -TimeoutSec 10)) {
        $console = if (Test-Path "$OutFile.console.log") { (Get-Content "$OutFile.console.log" -Raw) } else { 'no console log' }
        return [pscustomobject]@{ elevRan = $false; reason = "no result file; console: $console" }
    }
    $r = Get-Content -LiteralPath $OutFile -Raw | ConvertFrom-Json
    $r | Add-Member -NotePropertyName elevRan -NotePropertyValue $true
    return $r
}

function Send-ComboSet {
    # focus + send a list of combos against one window; skips on failed focus
    param($Hwnd, [string[]]$Combos, [string]$Label)
    $out = @()
    foreach ($c in $Combos) {
        $c = $c.Trim().Trim("'", '"')
        if (-not $c) { continue }
        $entry = [ordered]@{ target = $Label; hwnd = $Hwnd; combo = $c }
        $entry.focus = [WH]::FocusWindow($Hwnd)
        $entry.focused = ($entry.focus -notlike 'fg-failed*')
        if ($entry.focused) {
            $entry.before = [WH]::GetRect($Hwnd)
            $entry.sent = [WH]::SendCombo($c)
            Start-Sleep -Milliseconds 900
            $entry.after = [WH]::GetRect($Hwnd)
            $entry.changed = ($entry.before -ne $entry.after)
            $entry.fgAfterPid = [WH]::PidOfWindow([WH]::GetForegroundWindow())
        }
        $out += [pscustomobject]$entry
    }
    return $out
}

function Start-ElevatedMmc {
    $r = [ordered]@{ launched = $false }
    $t0 = Get-Date
    Start-Process -FilePath "$env:SystemRoot\System32\mmc.exe" `
        -ArgumentList "$env:SystemRoot\System32\taskschd.msc"
    $proc = $null
    $lastHwnd = 0
    $stableCount = 0
    $deadline = (Get-Date).AddSeconds(120)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 500
        $alive = Get-Process mmc -ErrorAction SilentlyContinue |
            Where-Object { $_.StartTime -ge $t0.AddSeconds(-3) } | Select-Object -First 1
        if (-not $alive) {
            if ((Get-Date) -gt $t0.AddSeconds(8)) { $r.note = 'mmc exited after start'; return $r }
            continue
        }
        $proc = $alive
        $hwnd = [WH]::FindMainWindow($proc.Id)
        $accept = $false
        if ($hwnd) {
            $accept = $true   # titled main window: ready
        } else {
            # Untitled fallback: e.g. elevated Task Scheduler keeps an empty
            # title for minutes. Accept once the same visible top window has
            # been stable for 2s and at least 15s have elapsed.
            $hwnd = [WH]::FindVisibleTopWindow($proc.Id)
            if ($hwnd -and $hwnd -eq $lastHwnd) { $stableCount++ } else { $stableCount = 0 }
            $lastHwnd = $hwnd
            if ($hwnd -and $stableCount -ge 4 -and ((Get-Date) - $t0).TotalSeconds -ge 15) {
                $accept = $true
            }
        }
        if ($accept) {
            Start-Sleep -Milliseconds 1200   # settle
            $r.launched = $true
            $r.pid = $proc.Id
            $r.hwnd = $hwnd
            $r.title = [WH]::TitleOf($hwnd)
            $r.cls = [WH]::ClassOf($hwnd)
            $r.rect = [WH]::GetRect($hwnd)
            $r.targetElevation = [WH]::ProcessElevatedEx($proc.Id)
            $r.elapsedSec = [math]::Round(((Get-Date) - $t0).TotalSeconds, 1)
            return $r
        }
    }
    $r.note = "timed out waiting for a usable window"
    if ($proc) {
        $r.pid = $proc.Id
        $r.windows = [WH]::ListWindows($proc.Id)
        $r.targetElevation = [WH]::ProcessElevatedEx($proc.Id)
    }
    $r.elapsedSec = [math]::Round(((Get-Date) - $t0).TotalSeconds, 1)
    return $r
}

# ------------------------------------------------------------------ roles ---

if ($Role -eq 'hotkey-wait') {
    if (-not $HotkeyResultPath) { $HotkeyResultPath = Join-Path $LogDir 'hotkey-wait.json' }
    if (-not $ReadyPath) { $ReadyPath = Join-Path $LogDir 'hotkey-wait.ready' }
    "ready" | Set-Content -LiteralPath $ReadyPath -Encoding ASCII   # liveness marker before register
    $outcome = [WH]::WaitHotkey(150000)
    Write-JsonResult -Path $HotkeyResultPath -Object @{
        outcome      = $outcome
        selfElevated = [WH]::SelfElevated()
        pid          = $PID
        at           = (Get-Date).ToString('o')
    }
    exit 0
}

if ($Role -eq 'elev') {
    if (-not $ResultPath) { throw "elev role requires -ResultPath" }
    $out = [ordered]@{ action = $ElevAction; selfElevated = [WH]::SelfElevated(); at = (Get-Date).ToString('o') }
    switch ($ElevAction) {
        'launch' { $out.launch = Start-ElevatedMmc }
        'runall' {
            $l = Start-ElevatedMmc
            $out.elevated = $l
            $out.results = @()
            if ($l.launched) {
                $out.results += Send-ComboSet -Hwnd ([long]$l.hwnd) -Combos ($Combo -split ',') -Label 'elevated-mmc'
            }
            $out.ok = $true
        }
        'snap' {
            $hwnd = [WH]::FindMainWindow($TargetPid)
            $out.targetPid = $TargetPid
            $out.hwnd = $hwnd
            if (-not $hwnd) { $out.ok = $false; $out.error = 'no window for pid' }
            else {
                $out.results = Send-ComboSet -Hwnd $hwnd -Combos ($Combo -split ',') -Label "pid$TargetPid"
                $out.ok = $true
            }
        }
        'kill' {
            Stop-Process -Id $TargetPid -Force -ErrorAction SilentlyContinue
            Start-Sleep -Milliseconds 400
            $alive = $null -ne (Get-Process -Id $TargetPid -ErrorAction SilentlyContinue)
            $out.killed = -not $alive
            $out.ok = $true
        }
        'inspect' {
            $out.targetPid = $TargetPid
            $out.targetElevation = [WH]::ProcessElevatedEx($TargetPid)
            $out.modules = [WH]::ListMatchingModules($TargetPid, 'windhawk')
            $out.ok = $true
        }
        default { throw "unknown ElevAction $ElevAction" }
    }
    Write-JsonResult -Path $ResultPath -Object $out
    exit 0
}

# ------------------------------------------------------------------- orch ---

New-Item -ItemType Directory -Path $LogDir -Force | Out-Null
$result = [ordered]@{
    startedAt         = (Get-Date).ToString('s')
    selfElevation     = [WH]::ProcessElevatedEx($PID)
    windhawkProcesses = @()
    toolModProcesses  = @()
    phases            = [ordered]@{}
    notes             = @()
}
$elevMmcPid = 0
$npProc = $null

try {
    $whProcs = Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" -ErrorAction SilentlyContinue
    foreach ($p in $whProcs) {
        $result.windhawkProcesses += "pid=$($p.ProcessId) cmd=$($p.CommandLine)"
        if ($p.CommandLine -match 'tool-mod') { $result.toolModProcesses += "pid=$($p.ProcessId) cmd=$($p.CommandLine)" }
    }
    $stray = @(Get-Process mmc -ErrorAction SilentlyContinue)
    if ($stray.Count) {
        foreach ($sp in $stray) {
            $result.notes += "stray mmc at start (pid $($sp.Id)) - killing elevated"
            try {
                $null = Invoke-ElevatedAction -ArgsString "-Role elev -ElevAction kill -TargetPid $($sp.Id)" `
                    -OutFile (Join-Path $LogDir ("kill-stray-" + $sp.Id + ".json"))
            } catch { $result.notes += "stray kill failed: $_" }
        }
    }

    # --- control A: our own medium test window (guaranteed medium) -----------
    $ctrlTitle = 'WH-ctrl-window'
    $testHwnd = [WH]::CreateTestWindow($ctrlTitle)
    $ctrlEntry = [ordered]@{
        hwnd     = $testHwnd
        elevation = 'medium (own process)'
        rect     = $(if ($testHwnd) { [WH]::GetRect($testHwnd) } else { 'none' })
    }
    if ($testHwnd) {
        $ctrlEntry.results = @(Send-ComboSet -Hwnd $testHwnd -Combos @('AltU') -Label 'medium-testwindow')
    } else {
        $ctrlEntry.note = 'failed to create test window'
    }
    $result.phases.controlTestWindow = $ctrlEntry

    # --- control B: notepad if this machine has one --------------------------
    $npT0 = Get-Date
    $npHwnd = 0
    $npProc = $null
    $npEntry = [ordered]@{ found = $false }
    try {
        Start-Process "$env:SystemRoot\System32\notepad.exe"
        $deadline = (Get-Date).AddSeconds(15)
        while ((Get-Date) -lt $deadline -and -not $npHwnd) {
            Start-Sleep -Milliseconds 400
            $npProc = Get-Process | Where-Object {
                $_.ProcessName -match '^notepad' -and $_.StartTime -ge $npT0.AddSeconds(-5) -and $_.MainWindowHandle -ne 0
            } | Select-Object -First 1
            if ($npProc) { $npHwnd = [WH]::FindMainWindow($npProc.Id) }
        }
    } catch {
        $npEntry.note = "notepad unavailable: $($_.Exception.Message)"
    }
    if ($npProc) {
        $npEntry.found = [bool]$npHwnd
        $npEntry.pid = $npProc.Id
        $npEntry.elevation = [WH]::ProcessElevatedEx($npProc.Id)
        if ($npHwnd) {
            $npEntry.rect = [WH]::GetRect($npHwnd)
            if ($npEntry.elevation -eq 'medium') {
                $npEntry.results = @(Send-ComboSet -Hwnd $npHwnd -Combos @('AltU') -Label 'medium-notepad')
            } else {
                $npEntry.note = 'notepad not medium; send skipped'
            }
        } else {
            $npEntry.note = 'notepad process found but no titled window'
        }
    } else {
        if (-not $npEntry.note) { $npEntry.note = 'no notepad window appeared' }
    }
    $result.phases.controlNotepad = $npEntry

    # --- medium hotkey waiter ------------------------------------------------
    $hrPath = Join-Path $LogDir 'hotkey-wait.json'
    $readyPath = Join-Path $LogDir 'hotkey-ready.txt'
    Remove-Item $hrPath, $readyPath -Force -ErrorAction SilentlyContinue
    $waiter = Start-Process -FilePath 'powershell.exe' -PassThru -WindowStyle Hidden -ArgumentList @(
        '-NoProfile', '-ExecutionPolicy', 'Bypass', '-File', "`"$PSCommandPath`"",
        '-Role', 'hotkey-wait', '-LogDir', "`"$LogDir`"",
        '-HotkeyResultPath', "`"$hrPath`"", '-ReadyPath', "`"$readyPath`""
    )
    $readyOk = Wait-ForFile -Path $readyPath -TimeoutSec 15
    $result.phases.hotkeyWaiterReady = $readyOk

    # --- single elevated run: launch + focus + send --------------------------
    $runall = Invoke-ElevatedAction `
        -ArgsString "-Role elev -ElevAction runall -Combo `"AltU,AltShiftRight,CtrlAltShiftY`"" `
        -OutFile (Join-Path $LogDir 'runall.json')
    $result.phases.runall = $runall
    if ($runall.elevated -and $runall.elevated.pid) { $elevMmcPid = [int]$runall.elevated.pid }
    $elevMmcHwnd = 0
    if ($runall.elevated -and $runall.elevated.hwnd) { $elevMmcHwnd = [long]$runall.elevated.hwnd }

    # --- T2 readout ----------------------------------------------------------
    if ($readyOk) {
        Wait-ForFile -Path $hrPath -TimeoutSec 160 | Out-Null
        if (Test-Path $hrPath) {
            $result.phases.t2_mediumHotkeyWhileElevatedForeground = (Get-Content $hrPath -Raw | ConvertFrom-Json)
        } else {
            $result.phases.t2_mediumHotkeyWhileElevatedForeground = 'waiter produced no result within 160s'
        }
    } else {
        $result.phases.t2_mediumHotkeyWhileElevatedForeground = 'waiter failed to start'
    }
    if (-not $waiter.HasExited) { Stop-Process -Id $waiter.Id -Force -ErrorAction SilentlyContinue }

    # --- T1: medium SetWindowPos on the elevated window ----------------------
    if ($elevMmcPid) {
        $elevHwnd = $elevMmcHwnd
        if (-not $elevHwnd -or [WH]::GetRect($elevHwnd) -like 'err*') {
            $elevHwnd = [WH]::FindMainWindow($elevMmcPid)
        }
        if (-not $elevHwnd) { $elevHwnd = [WH]::FindVisibleTopWindow($elevMmcPid) }
        if ($elevHwnd) {
            $result.phases.t1_mediumSetWindowPosOnElevated = [WH]::MoveBy($elevHwnd, 113, 47)
        } else {
            $result.phases.t1_mediumSetWindowPosOnElevated =
                "elevated mmc (pid $elevMmcPid) has no window now; windows=" + [WH]::ListWindows($elevMmcPid)
        }
    } else {
        $result.phases.t1_mediumSetWindowPosOnElevated = 'no elevated mmc was launched'
    }

    # --- T7: medium Alt+left-drag (alt-snap-drag) on the elevated window -----
    if ($elevMmcHwnd) {
        $result.phases.t7_mediumAltDragOnElevated = [WH]::AltDragTest($elevMmcHwnd)
    } else {
        $result.phases.t7_mediumAltDragOnElevated = 'no elevated mmc window'
    }

    # --- inspection: engine/mods inside the elevated process? ----------------
    if ($elevMmcPid) {
        $result.phases.elevatedProcessInspection = Invoke-ElevatedAction `
            -ArgsString "-Role elev -ElevAction inspect -TargetPid $elevMmcPid" `
            -OutFile (Join-Path $LogDir 'inspect-mmc.json')
    }
}
finally {
    # --- cleanup -------------------------------------------------------------
    if ($elevMmcPid) {
        try {
            $result.phases.cleanup = Invoke-ElevatedAction `
                -ArgsString "-Role elev -ElevAction kill -TargetPid $elevMmcPid" `
                -OutFile (Join-Path $LogDir 'kill.json')
        } catch {
            $result.phases.cleanup = "kill failed: $_"
        }
    }
    if ($npProc -and -not $npProc.HasExited) {
        if ($npEntry.elevation -eq 'medium') {
            Stop-Process -Id $npProc.Id -Force -ErrorAction SilentlyContinue
        } else {
            try {
                $null = Invoke-ElevatedAction -ArgsString "-Role elev -ElevAction kill -TargetPid $($npProc.Id)" `
                    -OutFile (Join-Path $LogDir 'kill-notepad.json')
            } catch { }
        }
    }
    $result.finishedAt = (Get-Date).ToString('s')
    $outPath = Join-Path $LogDir 'result.json'
    Write-JsonResult -Path $outPath -Object $result
    Write-Output "RESULT: $outPath"
    $result | ConvertTo-Json -Depth 10
}
