"""Start Notepad++ without taking focus, check the Seamless Flyouts DLL is in it, open its
editor context menu with a posted WM_CONTEXTMENU (no cursor move), capture, close it all.
Usage: python -I npp-menu.py <out.png> <dll name>"""
import ctypes, subprocess, sys, time
from ctypes import wintypes
from PIL import ImageGrab

u = ctypes.windll.user32
u.FindWindowW.restype = wintypes.HWND
u.FindWindowExW.restype = wintypes.HWND
u.PostMessageW.argtypes = [wintypes.HWND, ctypes.c_uint, ctypes.c_size_t, ctypes.c_ssize_t]
u.SendMessageW.restype = ctypes.c_ssize_t
u.SendMessageW.argtypes = [wintypes.HWND, ctypes.c_uint, ctypes.c_size_t, ctypes.c_ssize_t]
proto = ctypes.WINFUNCTYPE(wintypes.BOOL, wintypes.HWND, wintypes.LPARAM)
out, dll = sys.argv[1], sys.argv[2]
exe = r"C:\Program Files\Notepad++\notepad++.exe"


def menus():
    found = []
    def cb(h, _):
        b = ctypes.create_unicode_buffer(64); u.GetClassNameW(h, b, 64)
        if b.value == "#32768" and u.IsWindowVisible(h):
            r = wintypes.RECT(); u.GetWindowRect(h, ctypes.byref(r))
            found.append((h, r.left, r.top, r.right, r.bottom))
        return True
    u.EnumWindows(proto(cb), 0)
    return found


ctypes.windll.shell32.ShellExecuteW(None, "open", exe, "-nosession -multiInst", None, 4)  # SW_SHOWNOACTIVATE
main = None
for _ in range(50):
    time.sleep(0.2)
    main = u.FindWindowW("Notepad++", None)
    if main:
        break
if not main:
    sys.exit("Notepad++ window not found")
time.sleep(2.0)
pid = wintypes.DWORD(); u.GetWindowThreadProcessId(main, ctypes.byref(pid))
mods = subprocess.run(["tasklist", "/m", dll, "/fi", "PID eq %d" % pid.value], capture_output=True,
                      text=True, creationflags=0x08000000).stdout
print("pid", pid.value, "loaded", str(pid.value) in mods)
sci = u.FindWindowExW(main, None, "Scintilla", None)
r = wintypes.RECT(); u.GetWindowRect(sci, ctypes.byref(r))
x, y = r.left + 120, r.top + 60
u.PostMessageW(sci, 0x007B, sci, (y << 16) | (x & 0xFFFF))  # WM_CONTEXTMENU
m = []
for _ in range(30):
    time.sleep(0.1)
    m = menus()
    if m:
        break
if m:
    h, l, t, rr, b = m[0]
    time.sleep(0.4)
    u.SendMessageW(h, 0x01E5, 1, 0)  # MN_SELECTITEM
    time.sleep(0.5)
    pad = 40
    ImageGrab.grab(all_screens=True).crop((l + 1920 - pad, t + 1080 - pad, rr + 1920 + pad, b + 1080 + pad)).save(out)
    print("menu", l, t, rr, b, "size", rr - l, b - t)
    for x_ in menus():
        u.PostMessageW(x_[0], 0x0100, 0x1B, 0)
    time.sleep(0.3)
else:
    print("no menu opened")
print("alive", bool(u.IsWindow(main)))
u.PostMessageW(main, 0x0010, 0, 0)  # WM_CLOSE (new empty instance, nothing to save)
