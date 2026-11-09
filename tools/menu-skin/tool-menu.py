"""Open a tool mod's tray menu by posting its tray callback (no cursor move), select an
item the way a hover does (MN_SELECTITEM), crop the menu plus a margin, then Esc.
Usage: python -I tool-menu.py <out.png> <window class> <callback msg> [item index]"""
import ctypes, sys, time
from ctypes import wintypes
from PIL import ImageGrab

u = ctypes.windll.user32
u.FindWindowW.restype = wintypes.HWND
u.SendMessageW.restype = ctypes.c_ssize_t
u.SendMessageW.argtypes = [wintypes.HWND, ctypes.c_uint, ctypes.c_size_t, ctypes.c_ssize_t]
u.PostMessageW.argtypes = [wintypes.HWND, ctypes.c_uint, ctypes.c_size_t, ctypes.c_ssize_t]
proto = ctypes.WINFUNCTYPE(wintypes.BOOL, wintypes.HWND, wintypes.LPARAM)
out, cls, msg = sys.argv[1], sys.argv[2], int(sys.argv[3], 0)
item = int(sys.argv[4]) if len(sys.argv) > 4 else 0


def menus():
    found = []
    def cb(h, _):
        b = ctypes.create_unicode_buffer(64)
        u.GetClassNameW(h, b, 64)
        if b.value == "#32768" and u.IsWindowVisible(h):
            r = wintypes.RECT(); u.GetWindowRect(h, ctypes.byref(r))
            found.append((h, r.left, r.top, r.right, r.bottom))
        return True
    u.EnumWindows(proto(cb), 0)
    return found


hwnd = u.FindWindowW(cls, None)
if not hwnd:
    sys.exit("window not found: " + cls)
u.PostMessageW(hwnd, msg, 0, 0x7B)  # WM_CONTEXTMENU in LOWORD (tray version 4 and older)
m = []
for _ in range(40):
    time.sleep(0.1)
    m = menus()
    if m:
        break
if not m:
    sys.exit("no menu opened")
h, l, t, r, b = m[0]
time.sleep(0.4)
u.SendMessageW(h, 0x01E5, item, 0)  # MN_SELECTITEM
time.sleep(0.5)
img = ImageGrab.grab(all_screens=True)
ox, oy = 1920, 1080
pad = 40
img.crop((l + ox - pad, t + oy - pad, r + ox + pad, b + oy + pad)).save(out)
print("menu", l, t, r, b, "size", r - l, b - t)
u.PostMessageW(h, 0x0100, 0x1B, 0)  # Esc
time.sleep(0.3)
for x in menus():
    u.PostMessageW(x[0], 0x0100, 0x1B, 0)
