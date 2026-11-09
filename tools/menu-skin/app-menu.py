"""Open an app's menu-bar dropdown with WM_SYSCOMMAND SC_KEYMENU (no cursor move, no
click), select an item the way a hover does, crop the dropdown, then Esc twice.
Usage: python -I app-menu.py <out.png> <pid> <accelerator letter> [item index]"""
import ctypes, sys, time
from ctypes import wintypes
from PIL import ImageGrab

u = ctypes.windll.user32
u.SendMessageW.restype = ctypes.c_ssize_t
u.SendMessageW.argtypes = [wintypes.HWND, ctypes.c_uint, ctypes.c_size_t, ctypes.c_ssize_t]
u.PostMessageW.argtypes = [wintypes.HWND, ctypes.c_uint, ctypes.c_size_t, ctypes.c_ssize_t]
u.GetMenu.restype = wintypes.HMENU
proto = ctypes.WINFUNCTYPE(wintypes.BOOL, wintypes.HWND, wintypes.LPARAM)
out, pid, key = sys.argv[1], int(sys.argv[2]), sys.argv[3]
item = int(sys.argv[4]) if len(sys.argv) > 4 else 0


def windows(want_menu):
    found = []
    def cb(h, _):
        p = wintypes.DWORD(); u.GetWindowThreadProcessId(h, ctypes.byref(p))
        b = ctypes.create_unicode_buffer(64); u.GetClassNameW(h, b, 64)
        if not u.IsWindowVisible(h):
            return True
        if want_menu and b.value == "#32768":
            r = wintypes.RECT(); u.GetWindowRect(h, ctypes.byref(r))
            found.append((h, r.left, r.top, r.right, r.bottom))
        elif not want_menu and p.value == pid and u.GetMenu(h):
            found.append(h)
        return True
    u.EnumWindows(proto(cb), 0)
    return found


mains = windows(False)
if not mains:
    sys.exit("no window with a menu bar for pid %d" % pid)
main = mains[0]
print("iconic", bool(u.IsIconic(main)))
u.SendNotifyMessageW(main, 0x0112, 0xF100, ord(key.lower()))  # SC_KEYMENU + letter, sent so DefWindowProc runs it
m = []
for _ in range(30):
    time.sleep(0.1)
    m = windows(True)
    if m:
        break
if not m:
    u.PostMessageW(main, 0x0100, 0x1B, 0)
    sys.exit("no dropdown opened")
h, l, t, r, b = m[0]
time.sleep(0.4)
u.SendMessageW(h, 0x01E5, item, 0)  # MN_SELECTITEM
time.sleep(0.5)
pad = 40
ImageGrab.grab(all_screens=True).crop((l + 1920 - pad, t + 1080 - pad, r + 1920 + pad, b + 1080 + pad)).save(out)
print("menu", l, t, r, b, "size", r - l, b - t)
for _ in range(2):
    for x in windows(True):
        u.PostMessageW(x[0], 0x0100, 0x1B, 0)
    u.PostMessageW(main, 0x0100, 0x1B, 0)
    time.sleep(0.2)
