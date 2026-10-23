#requires -Version 5.1
# Probe: why does SetForegroundWindow fail from this process? (medium, read-only)
$ErrorActionPreference = 'Stop'
Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

public static class FP {
    [StructLayout(LayoutKind.Sequential)]
    public struct MSG { public IntPtr h; public uint msg; public IntPtr w; public IntPtr l; public uint t; public int x, y; }
    [StructLayout(LayoutKind.Sequential)]
    public struct KEYBDINPUT { public ushort wVk; public ushort wScan; public uint dwFlags; public uint time; public IntPtr dwExtra; }
    [StructLayout(LayoutKind.Sequential)]
    public struct MOUSEINPUT { public int dx, dy; public uint mouseData, dwFlags, time; public IntPtr dwExtra; }
    [StructLayout(LayoutKind.Sequential)]
    public struct HARDWAREINPUT { public uint uMsg; public ushort wL, wH; }
    [StructLayout(LayoutKind.Explicit)]
    public struct IU {
        [FieldOffset(0)] public KEYBDINPUT ki;
        [FieldOffset(0)] public MOUSEINPUT mi;
        [FieldOffset(0)] public HARDWAREINPUT hi;
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct INPUT { public uint type; public IU u; }

    delegate bool EnumProc(IntPtr h, IntPtr l);
    public delegate IntPtr WndProc(IntPtr h, uint m, IntPtr w, IntPtr l);

    [DllImport("user32.dll", SetLastError = true)] static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] static extern bool BringWindowToTop(IntPtr h);
    [DllImport("user32.dll")] static extern bool ShowWindow(IntPtr h, int c);
    [DllImport("user32.dll")] static extern bool AttachThreadInput(uint a, uint b, bool on);
    [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
    [DllImport("kernel32.dll")] static extern uint GetCurrentThreadId();
    [DllImport("user32.dll", SetLastError = true)] static extern uint SendInput(uint n, INPUT[] p, int sz);
    [DllImport("user32.dll")] static extern bool EnumWindows(EnumProc cb, IntPtr l);
    [DllImport("user32.dll")] static extern bool IsWindowVisible(IntPtr h);
    [DllImport("user32.dll")] static extern bool IsHungAppWindow(IntPtr h);
    [DllImport("user32.dll")] static extern IntPtr GetWindow(IntPtr h, uint c);
    [DllImport("user32.dll")] static extern int GetWindowTextLength(IntPtr h);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] static extern int GetClassName(IntPtr h, StringBuilder s, int n);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] static extern ushort RegisterClass(ref WC c);
    [DllImport("user32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    static extern IntPtr CreateWindowEx(uint x, string cls, string title, uint style,
        int a, int b, int w, int h, IntPtr p, IntPtr m, IntPtr i, IntPtr d);
    [DllImport("user32.dll")] static extern IntPtr DefWindowProc(IntPtr h, uint m, IntPtr w, IntPtr l);
    [DllImport("user32.dll")] static extern bool UpdateWindow(IntPtr h);
    [DllImport("user32.dll")] static extern IntPtr LoadCursor(IntPtr i, IntPtr n);
    [DllImport("kernel32.dll", CharSet = CharSet.Unicode)] static extern IntPtr GetModuleHandle(string n);
    [DllImport("user32.dll")] static extern bool GetMessage(out MSG m, IntPtr h, uint a, uint b);
    [DllImport("user32.dll")] static extern bool TranslateMessage(ref MSG m);
    [DllImport("user32.dll")] static extern IntPtr DispatchMessage(ref MSG m);

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct WC {
        public uint style; public WndProc lpfn; public int a, b;
        public IntPtr i, ic, cu, br; public string mn, cn;
    }

    static WndProc s_keep;
    static IntPtr WndP(IntPtr h, uint m, IntPtr w, IntPtr l) { return DefWindowProc(h, m, w, l); }

    public static string Run() {
        var log = new StringBuilder();
        // foreground identity
        IntPtr fg = GetForegroundWindow();
        uint fpid; GetWindowThreadProcessId(fg, out fpid);
        var cls = new StringBuilder(256); GetClassName(fg, cls, 256);
        var ttl = new StringBuilder(512); GetWindowText(fg, ttl, 512);
        log.Append("fg pid=").Append(fpid).Append(" class=").Append(cls)
           .Append(" title=").Append(ttl.ToString().Substring(0, Math.Min(40, ttl.Length)))
           .Append(" hung=").Append(IsHungAppWindow(fg)).AppendLine();

        // create own window on background thread
        IntPtr hwnd = IntPtr.Zero;
        var ready = new ManualResetEvent(false);
        var t = new Thread(() => {
            s_keep = WndP;
            var wc = new WC { lpfn = s_keep, i = GetModuleHandle(null),
                cn = "FPProbe" + GetCurrentThreadId(), cu = LoadCursor(IntPtr.Zero, (IntPtr)32512), br = (IntPtr)6 };
            if (RegisterClass(ref wc) == 0) { ready.Set(); return; }
            hwnd = CreateWindowEx(0, wc.cn, "FP-probe", 0x00CF0000, 200, 200, 400, 300,
                IntPtr.Zero, IntPtr.Zero, wc.i, IntPtr.Zero);
            if (hwnd != IntPtr.Zero) { ShowWindow(hwnd, 5); UpdateWindow(hwnd); }
            ready.Set();
            MSG m;
            while (GetMessage(out m, IntPtr.Zero, 0, 0)) { TranslateMessage(ref m); DispatchMessage(ref m); }
        });
        t.IsBackground = true; t.Start();
        ready.WaitOne(5000); Thread.Sleep(200);
        log.Append("own hwnd=0x").Append(hwnd.ToInt64().ToString("X")).AppendLine();

        uint me = GetCurrentThreadId();
        uint dummy; uint fgT = GetWindowThreadProcessId(fg, out dummy);

        // 1 plain
        bool r = SetForegroundWindow(hwnd);
        int e = Marshal.GetLastWin32Error();
        Thread.Sleep(200);
        log.Append("plain: ret=").Append(r).Append(" err=").Append(e)
           .Append(" nowFg=").Append((GetForegroundWindow() == hwnd) ? "OWN" : "other").AppendLine();

        // 2 attach
        bool ar = AttachThreadInput(me, fgT, true);
        e = Marshal.GetLastWin32Error();
        r = SetForegroundWindow(hwnd);
        int e2 = Marshal.GetLastWin32Error();
        AttachThreadInput(me, fgT, false);
        Thread.Sleep(200);
        log.Append("attach: attachRet=").Append(ar).Append(" attachErr=").Append(e)
           .Append(" sfgRet=").Append(r).Append(" sfgErr=").Append(e2)
           .Append(" nowFg=").Append((GetForegroundWindow() == hwnd) ? "OWN" : "other").AppendLine();

        // 3 F24 tap via SendInput
        var ins = new INPUT[4];
        for (int i = 0; i < 4; i++) {
            ins[i].type = 1;
            ins[i].u.ki.wVk = 0x87;
            ins[i].u.ki.dwFlags = (i % 2 == 1) ? 0x0002u : 0u;
        }
        uint sent = SendInput(4, ins, Marshal.SizeOf(typeof(INPUT)));
        e = Marshal.GetLastWin32Error();
        log.Append("inputSize=").Append(Marshal.SizeOf(typeof(INPUT)))
           .Append(" sendInput F24: sent=").Append(sent).Append("/4 err=").Append(e).AppendLine();
        Thread.Sleep(120);
        r = SetForegroundWindow(hwnd);
        e2 = Marshal.GetLastWin32Error();
        Thread.Sleep(200);
        log.Append("afterF24: sfgRet=").Append(r).Append(" err=").Append(e2)
           .Append(" nowFg=").Append((GetForegroundWindow() == hwnd) ? "OWN" : "other").AppendLine();

        // 4 BringWindowToTop + z-order
        BringWindowToTop(hwnd);
        r = SetForegroundWindow(hwnd);
        e2 = Marshal.GetLastWin32Error();
        Thread.Sleep(200);
        log.Append("afterTop: sfgRet=").Append(r).Append(" err=").Append(e2)
           .Append(" nowFg=").Append((GetForegroundWindow() == hwnd) ? "OWN" : "other").AppendLine();

        // 5 final state
        fg = GetForegroundWindow();
        GetWindowThreadProcessId(fg, out fpid);
        log.Append("final fg pid=").Append(fpid).AppendLine();
        return log.ToString();
    }
}
'@
[FP]::Run()
