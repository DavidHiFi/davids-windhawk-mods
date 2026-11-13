# Read-only probe: for each visible, uncloaked top-level window of the named processes,
# reports DWM system backdrop type, host-backdrop flag and the accent policy
# (GetWindowCompositionAttribute WCA_ACCENT_POLICY), to choose the signal that says
# "a glow behind this window shows through it".
# Usage: python -I 2026-11-13-wobbly-translucency-probe.py helium.exe brave.exe
import ctypes, ctypes.wintypes as wt, sys, os
u = ctypes.WinDLL("user32", use_last_error=True)
d = ctypes.WinDLL("dwmapi")
k = ctypes.WinDLL("kernel32")
names = {n.lower() for n in sys.argv[1:]}
class ACCENT(ctypes.Structure):
    _fields_ = [("state", ctypes.c_int), ("flags", ctypes.c_int), ("color", ctypes.c_uint), ("anim", ctypes.c_int)]
class WCAD(ctypes.Structure):
    _fields_ = [("attr", ctypes.c_int), ("data", ctypes.c_void_p), ("size", ctypes.c_size_t)]
gwca = u.GetWindowCompositionAttribute
gwca.argtypes = [wt.HWND, ctypes.POINTER(WCAD)]
def exe_of(h):
    pid = wt.DWORD(); u.GetWindowThreadProcessId(h, ctypes.byref(pid))
    hp = k.OpenProcess(0x1000, False, pid.value)
    if not hp: return ""
    buf = ctypes.create_unicode_buffer(520); n = wt.DWORD(520)
    k.QueryFullProcessImageNameW(hp, 0, buf, ctypes.byref(n)); k.CloseHandle(hp)
    return os.path.basename(buf.value).lower()
@ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)
def cb(h, _):
    if not u.IsWindowVisible(h) or u.IsIconic(h): return True
    cloak = ctypes.c_int(0); d.DwmGetWindowAttribute(wt.HWND(h), 14, ctypes.byref(cloak), 4)
    if cloak.value: return True
    exe = exe_of(h)
    if exe not in names: return True
    rc = wt.RECT(); u.GetWindowRect(h, ctypes.byref(rc))
    if rc.right - rc.left < 200: return True
    bd = ctypes.c_int(-1); hr1 = d.DwmGetWindowAttribute(wt.HWND(h), 38, ctypes.byref(bd), 4)
    hb = ctypes.c_int(-1); hr2 = d.DwmGetWindowAttribute(wt.HWND(h), 17, ctypes.byref(hb), 4)
    ac = ACCENT(); w = WCAD(19, ctypes.cast(ctypes.byref(ac), ctypes.c_void_p), ctypes.sizeof(ac))
    ok = gwca(wt.HWND(h), ctypes.byref(w))
    cls = ctypes.create_unicode_buffer(128); u.GetClassNameW(wt.HWND(h), cls, 128)
    ex = u.GetWindowLongW(wt.HWND(h), -20) & 0xFFFFFFFF
    print({"exe": exe, "class": cls.value, "backdrop": bd.value if hr1 == 0 else None,
           "hostBackdrop": hb.value if hr2 == 0 else None,
           "accent": (ac.state, hex(ac.flags), hex(ac.color)) if ok else None,
           "layered": bool(ex & 0x80000)})
    return True
u.EnumWindows(cb, 0)
