# Glow live test for Seamless Wobbly Windows 1.1.0 (copy of 2026-11-12-wobbly-live-test.py).
# The test window is acrylic (system backdrop 3, frame extended over the client), so the glow
# process gives it a glow; the drags check the glow is painted inside the wobble.
#   python this.py <new out dir>            drives the test window and records the primary screen
#   python this.py --window <seconds>       (internal) the test window itself
# Run only while the owner is away, under `coop lock desktop`. Restores the cursor.
import ctypes
import ctypes.wintypes as W
import json
import os
import shutil
import subprocess
import tempfile
import sys
import time

u32 = ctypes.WinDLL("user32", use_last_error=True)
g32 = ctypes.WinDLL("gdi32")
dwm = ctypes.WinDLL("dwmapi")
k32 = ctypes.WinDLL("kernel32")
u32.SetProcessDpiAwarenessContext(ctypes.c_void_p(-4))  # per-monitor v2

WNDPROC = ctypes.WINFUNCTYPE(ctypes.c_ssize_t, W.HWND, W.UINT, W.WPARAM, W.LPARAM)
u32.DefWindowProcW.argtypes = [W.HWND, W.UINT, W.WPARAM, W.LPARAM]
u32.DefWindowProcW.restype = ctypes.c_ssize_t
u32.CreateWindowExW.restype = W.HWND
u32.CreateWindowExW.argtypes = [W.DWORD, W.LPCWSTR, W.LPCWSTR, W.DWORD, ctypes.c_int, ctypes.c_int,
                                ctypes.c_int, ctypes.c_int, W.HWND, W.HMENU, W.HINSTANCE, W.LPVOID]


class WNDCLASSW(ctypes.Structure):
    _fields_ = [("style", W.UINT), ("proc", WNDPROC), ("cls", ctypes.c_int), ("wnd", ctypes.c_int),
                ("inst", W.HINSTANCE), ("icon", W.HICON), ("cursor", W.HANDLE), ("bg", W.HBRUSH),
                ("menu", W.LPCWSTR), ("name", W.LPCWSTR)]


class PAINTSTRUCT(ctypes.Structure):
    _fields_ = [("hdc", W.HDC), ("erase", W.BOOL), ("rc", W.RECT), ("r", W.BOOL), ("i", W.BOOL),
                ("x", ctypes.c_byte * 32)]


def window_main(seconds):
    bands = [0xA8F3E5, 0xF7E2A6, 0xA6C9F7, 0xC3A6F5, 0xA1E3A6, 0xF5C2E7]  # BGR-ish pastels

    def proc(h, m, w, l):
        if m == 0x000F:  # WM_PAINT
            ps = PAINTSTRUCT()
            dc = u32.BeginPaint(h, ctypes.byref(ps))
            rc = W.RECT()
            u32.GetClientRect(h, ctypes.byref(rc))
            u32.FillRect(dc, ctypes.byref(rc), g32.GetStockObject(4))  # black: the backdrop shows
            for i, c in enumerate((0x2E1E1E, 0x443231)):              # Mocha base, surface0 cards
                br = g32.CreateSolidBrush(c)
                r = W.RECT(40 + i * 440, 120, 400 + i * 440, 420)
                u32.FillRect(dc, ctypes.byref(r), br)
                g32.DeleteObject(br)
            u32.EndPaint(h, ctypes.byref(ps))
            return 0
        if m == 0x0112 and (w & 0xFFF0) == 0xF100:  # SC_KEYMENU: no menu mode after Alt
            return 0
        if m == 0x0113 and w == 2:  # WM_TIMER 2: acrylic again if another mod reset it
            cur = ctypes.c_int(0)
            dwm.DwmGetWindowAttribute(W.HWND(h), 38, ctypes.byref(cur), 4)
            if cur.value != 3:
                pdwm.DwmSetWindowAttribute(W.HWND(h), 38, ctypes.byref(acrylic), 4)
            return 0
        if m == 0x0113:  # WM_TIMER: time is up
            u32.DestroyWindow(h)
            return 0
        if m == 0x0002:  # WM_DESTROY
            u32.PostQuitMessage(0)
            return 0
        return u32.DefWindowProcW(h, m, w, l)

    cb = WNDPROC(proc)
    inst = k32.GetModuleHandleW(None)
    wc = WNDCLASSW(0x3, cb, 0, 0, inst, None, u32.LoadCursorW(None, 32512), None, None, "WobbleTestWnd")
    u32.RegisterClassW(ctypes.byref(wc))
    # Hidden owner: Seamless Window Manager does not tile owned windows.
    owner = u32.CreateWindowExW(0, "WobbleTestWnd", "owner", 0x80000000, 0, 0, 1, 1, None, None, inst, None)
    hwnd = u32.CreateWindowExW(0, "WobbleTestWnd", "Wobble glow test", 0x00CF0000, 300, 200, 960, 620,
                               owner, None, inst, None)
    # Asks the glow process (1.1.2 and later) to report which of its checks this window passes.
    u32.SetPropW(W.HWND(hwnd), "SeamlessWobblyWindows.GlowWatch", W.HANDLE(1))
    one = ctypes.c_int(1)
    dwm.DwmSetWindowAttribute(W.HWND(hwnd), 20, ctypes.byref(one), 4)        # dark mode
    margins = (ctypes.c_int * 4)(-1, -1, -1, -1)
    dwm.DwmExtendFrameIntoClientArea(W.HWND(hwnd), margins)
    acrylic = ctypes.c_int(3)
    # Seamless Flyouts hooks DwmSetWindowAttribute in every process and turns an acrylic
    # request into its own accent blur, which reads back as 0 from outside. A private copy
    # of dwmapi.dll is not hooked, so this window asks DWM for acrylic the way a program
    # does on a PC without that mod.
    private = os.path.join(tempfile.gettempdir(), "wobbly-glowtest-dwmapi.dll")
    if not os.path.exists(private):
        shutil.copyfile(os.path.join(os.environ["SystemRoot"], "System32", "dwmapi.dll"), private)
    pdwm = ctypes.WinDLL(private)
    pdwm.DwmSetWindowAttribute.argtypes = [W.HWND, W.DWORD, ctypes.c_void_p, W.DWORD]
    set_hr = pdwm.DwmSetWindowAttribute(W.HWND(hwnd), 38, ctypes.byref(acrylic), 4)  # acrylic backdrop
    u32.ShowWindow(hwnd, 5)
    u32.SetTimer(hwnd, 1, int(seconds * 1000), None)
    # Window Animations re-applies the backdrop after its open animation through the same
    # hook, which sets it back to 0; check twice a second.
    u32.SetTimer(hwnd, 2, 500, None)
    print(int(hwnd), flush=True)
    # Second line: did the backdrop stick (read inside this process)?
    back = ctypes.c_int(-1)
    get_hr = dwm.DwmGetWindowAttribute(W.HWND(hwnd), 38, ctypes.byref(back), 4)
    print(json.dumps({"set_hr": hex(set_hr & 0xFFFFFFFF), "get_hr": hex(get_hr & 0xFFFFFFFF),
                      "backdrop": back.value}), flush=True)
    msg = W.MSG()
    while u32.GetMessageW(ctypes.byref(msg), None, 0, 0) > 0:
        u32.TranslateMessage(ctypes.byref(msg))
        u32.DispatchMessageW(ctypes.byref(msg))


# ---------- driver ----------

class MOUSEINPUT(ctypes.Structure):
    _fields_ = [("dx", ctypes.c_long), ("dy", ctypes.c_long), ("data", W.DWORD), ("flags", W.DWORD),
                ("time", W.DWORD), ("extra", ctypes.c_size_t)]


class KEYBDINPUT(ctypes.Structure):
    _fields_ = [("vk", W.WORD), ("scan", W.WORD), ("flags", W.DWORD), ("time", W.DWORD),
                ("extra", ctypes.c_size_t)]


class _U(ctypes.Union):
    _fields_ = [("mi", MOUSEINPUT), ("ki", KEYBDINPUT), ("pad", ctypes.c_byte * 32)]


class INPUT(ctypes.Structure):
    _fields_ = [("type", W.DWORD), ("u", _U)]


VX, VY = u32.GetSystemMetrics(76), u32.GetSystemMetrics(77)
VW, VH = u32.GetSystemMetrics(78), u32.GetSystemMetrics(79)


def send(*inputs):
    arr = (INPUT * len(inputs))(*inputs)
    u32.SendInput(len(inputs), arr, ctypes.sizeof(INPUT))


def mouse(x, y, flags=0):
    i = INPUT(0)
    i.u.mi = MOUSEINPUT(round((x - VX) * 65535 / (VW - 1)), round((y - VY) * 65535 / (VH - 1)), 0,
                        0x0001 | 0x8000 | 0x4000 | flags, 0, 0)  # MOVE|ABSOLUTE|VIRTUALDESK
    return i


def key(vk, up=False):
    i = INPUT(1)
    i.u.ki = KEYBDINPUT(vk, 0, 0x0002 if up else 0, 0, 0)
    return i


def rect(h):
    r = W.RECT()
    u32.GetWindowRect(h, ctypes.byref(r))
    return (r.left, r.top, r.right, r.bottom)


def cloaked(h):
    v = ctypes.c_int(0)
    dwm.DwmGetWindowAttribute(W.HWND(h), 14, ctypes.byref(v), 4)
    return v.value


def overlay_visible():
    h = u32.FindWindowW("SeamlessWobblyOverlay", None)
    return bool(h) and bool(u32.IsWindowVisible(h))


def explorer_pid():
    pid = W.DWORD()
    u32.GetWindowThreadProcessId(u32.FindWindowW("Shell_TrayWnd", None), ctypes.byref(pid))
    return pid.value


def drag(h, start, path, alt=False, step_ms=8):
    """Press at start, move through path, release. Returns cloak/overlay samples taken mid-drag."""
    samples = []
    if alt:
        send(key(0xA4)); time.sleep(0.05)
    send(mouse(*start)); time.sleep(0.05)
    send(mouse(*start, 0x0002)); time.sleep(0.12)
    x0, y0 = start
    for n, (x, y) in enumerate(path):
        # Interpolate so the cursor travels like a hand would.
        steps = max(1, int(max(abs(x - x0), abs(y - y0)) / 14))
        for s in range(1, steps + 1):
            send(mouse(x0 + (x - x0) * s // steps, y0 + (y - y0) * s // steps))
            time.sleep(step_ms / 1000)
        x0, y0 = x, y
        samples.append({"cloaked": cloaked(h), "overlay": overlay_visible()})
    time.sleep(0.05)
    send(mouse(x0, y0, 0x0004))
    if alt:
        time.sleep(0.03); send(key(0xA4, up=True))
    return samples


def driver(out):
    sys.path.insert(0, r"H:\System Configuration\agent-tools\VideoCapture")
    import vcap

    os.makedirs(os.path.dirname(out), exist_ok=True)
    report = {"explorer_pid_before": explorer_pid()}
    cur = W.POINT()
    u32.GetCursorPos(ctypes.byref(cur))
    win = subprocess.Popen([sys.executable, os.path.abspath(__file__), "--window", "60"],
                           stdout=subprocess.PIPE, text=True, creationflags=subprocess.CREATE_NO_WINDOW)
    h = int(win.stdout.readline())
    report["window_backdrop"] = win.stdout.readline().strip()
    rec = None
    # What the glow process publishes for the test window, every 100 ms.
    import importlib.util, threading
    spec = importlib.util.spec_from_file_location(
        "probe", os.path.join(os.path.dirname(os.path.abspath(__file__)), "2026-11-13-wobbly-glow-probe.py"))
    probe = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(probe)
    maplog, stop = [], threading.Event()
    quns = ctypes.c_int(0)

    def watch():
        while not stop.wait(0.1):
            m = probe.read_map()
            ctypes.windll.shell32.SHQueryUserNotificationState(ctypes.byref(quns))
            if m is not None and rec is not None:
                maplog.append((round(rec.elapsed(), 2), quns.value, m["running"], m["count"], m["e"].get(h), hex(m["watch"] & 0xFF00FFFF)))
    watcher = threading.Thread(target=watch, daemon=True)
    try:
        time.sleep(0.8)
        # gfxcapture monitor index of the primary screen; it moves when screens change
        # (1 on 2026-11-12, 3 on 2026-11-13). Probe with a 1 s take and check 2560x1440.
        rec = vcap.Recorder(out, audio_pid=0, monitor=int(os.environ.get("WOBBLE_MONITOR", "3")))
        rec.start()
        watcher.start()
        time.sleep(0.5)

        time.sleep(3.0)    # the glow process finds new windows on its 2 s poll
        u32.SetForegroundWindow(h)
        time.sleep(0.6)
        report["rec_t_glow_ready"] = rec.elapsed()
        bd = ctypes.c_int(-1)
        dwm.DwmGetWindowAttribute(W.HWND(h), 38, ctypes.byref(bd), 4)
        report["backdrop_seen_outside"] = bd.value

        # 1. Caption drag with a zigzag, then held still for a second (glow keeps moving).
        l, t, r, b = rect(h)
        report["before"] = (l, t, r, b)
        grab = (l + 300, t + 14)
        path = [(grab[0] + 260, grab[1] + 90), (grab[0] + 60, grab[1] + 220), (grab[0] + 420, grab[1] + 160)]
        samples = []
        send(mouse(*grab)); time.sleep(0.05)
        send(mouse(*grab, 0x0002)); time.sleep(0.12)
        x0, y0 = grab
        for (x, y) in path:
            steps = max(1, int(max(abs(x - x0), abs(y - y0)) / 14))
            for s in range(1, steps + 1):
                send(mouse(x0 + (x - x0) * s // steps, y0 + (y - y0) * s // steps))
                time.sleep(0.008)
            x0, y0 = x, y
            samples.append({"cloaked": cloaked(h), "overlay": overlay_visible()})
        report["rec_t_hold"] = rec.elapsed()
        time.sleep(1.2)
        samples.append({"held": True, "cloaked": cloaked(h), "overlay": overlay_visible()})
        report["rec_t_release"] = rec.elapsed()
        send(mouse(x0, y0, 0x0004))
        report["drag_mid"] = samples
        time.sleep(1.6)
        report["drag_after"] = {"rect": rect(h), "cloaked": cloaked(h), "overlay": overlay_visible()}

        # 2. Quick flick and release.
        l, t, r, b = rect(h)
        grab = (l + 300, t + 14)
        report["rec_t_flick"] = rec.elapsed()
        report["flick_mid"] = drag(h, grab, [(grab[0] - 360, grab[1] + 40)], step_ms=3)
        time.sleep(1.6)
        report["flick_after"] = {"rect": rect(h), "cloaked": cloaked(h), "overlay": overlay_visible()}

        # 3. Alt-drag (Seamless Window Manager).
        l, t, r, b = rect(h)
        grab = (l + 700, (t + b) // 2)
        report["rec_t_alt"] = rec.elapsed()
        report["alt_mid"] = drag(h, grab, [(grab[0] - 300, grab[1] - 80), (grab[0] - 100, grab[1] - 200)], alt=True)
        time.sleep(1.6)
        report["alt_after"] = {"rect": rect(h), "cloaked": cloaked(h), "overlay": overlay_visible()}
    finally:
        stop.set()
        if watcher.is_alive():
            watcher.join(1)
        # Only the changes, to keep the report short.
        report["map"] = [r for i, r in enumerate(maplog) if i == 0 or r[1:] != maplog[i - 1][1:]]
        if rec:
            report["recorder_rc"] = rec.stop()
        u32.SetCursorPos(cur.x, cur.y)
        u32.PostMessageW(h, 0x0010, 0, 0)  # WM_CLOSE
        try:
            win.wait(5)
        except subprocess.TimeoutExpired:
            win.kill()
    report["explorer_pid_after"] = explorer_pid()
    report["cursor_restored"] = (cur.x, cur.y)
    if rec:
        report["share"] = vcap.share(rec.video, os.path.join(out, "share.mp4"))
    print(json.dumps(report, indent=1))


if __name__ == "__main__":
    if sys.argv[1] == "--window":
        window_main(float(sys.argv[2]))
    else:
        driver(sys.argv[1])
