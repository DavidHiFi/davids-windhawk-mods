"""List every process that owns a visible top-level window and say whether the Seamless
Flyouts DLL is loaded in it. Usage: python -I coverage.py <dll name>"""
import ctypes, subprocess, sys
from ctypes import wintypes

u = ctypes.windll.user32
proto = ctypes.WINFUNCTYPE(wintypes.BOOL, wintypes.HWND, wintypes.LPARAM)
pids = set()
def cb(h, _):
    if u.IsWindowVisible(h) or "--all" in sys.argv:
        p = wintypes.DWORD(); u.GetWindowThreadProcessId(h, ctypes.byref(p)); pids.add(p.value)
    return True
u.EnumWindows(proto(cb), 0)

def csv(args):
    out = subprocess.run(["tasklist", "/fo", "csv", "/nh"] + args, capture_output=True, text=True,
                         creationflags=0x08000000).stdout
    rows = {}
    for line in out.splitlines():
        parts = [x.strip('"') for x in line.split('","')]
        if len(parts) > 1 and parts[1].isdigit():
            rows[int(parts[1])] = parts[0]
    return rows

names = csv([])
loaded = csv(["/m", sys.argv[1]])
seen = {}
for p in pids:
    n = names.get(p, "?")
    seen.setdefault(n, set()).add(p in loaded)
for n in sorted(seen, key=str.lower):
    v = seen[n]
    print(("yes " if all(v) else "part" if any(v) else "NO  "), n)
