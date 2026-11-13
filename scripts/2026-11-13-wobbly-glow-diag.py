# Finds which state keeps the glow tool from making a glow. Opens the test window (no clicks,
# no keys) and reads the shared map every 0.5 s through three phases:
#   A  as it is now
#   B  after posting "settings changed" to the tool's controller window (rebuilds a missing
#      compositor, clears the failed list, refreshes)
#   C  after restarting the glow worker thread (elevated helper, glow.enabled 0 then 1)
# Phase C runs only if B shows nothing. Prints JSON rows. Caller holds the desktop lock.
import ctypes, ctypes.wintypes as W, json, os, subprocess, sys, time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import importlib.util
spec = importlib.util.spec_from_file_location("probe", os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                                                    "2026-11-13-wobbly-glow-probe.py"))
probe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(probe)

u = ctypes.WinDLL("user32")
u.FindWindowExW.restype = W.HWND
u.FindWindowExW.argtypes = [W.HWND, W.HWND, W.LPCWSTR, W.LPCWSTR]
HWND_MESSAGE = W.HWND(-3)
here = os.path.dirname(os.path.abspath(__file__))
log = []
t0 = time.time()


def sample(phase, h, seconds):
    end = time.time() + seconds
    while time.time() < end:
        m = probe.read_map()
        log.append({"t": round(time.time() - t0, 2), "phase": phase,
                    "running": m and m["running"], "count": m and m["count"],
                    "entry": m and m["e"].get(h), "below": probe.tool_windows(h)[:1]})
        time.sleep(0.5)
    return bool(log[-1]["entry"])


win = subprocess.Popen([sys.executable, os.path.join(here, "2026-11-13-wobbly-glow-test.py"), "--window", "45"],
                       stdout=subprocess.PIPE, text=True, creationflags=subprocess.CREATE_NO_WINDOW)
h = int(win.stdout.readline())
try:
    fixed = sample("A", h, 5)
    if not fixed:
        ctl = u.FindWindowExW(HWND_MESSAGE, None, "SeamlessWobblyGlow", None)
        log.append({"t": round(time.time() - t0, 2), "phase": "B", "controller": hex(ctl or 0),
                    "posted": bool(ctl and u.PostMessageW(ctl, 0x8002, 0, 0))})
        fixed = sample("B", h, 8)
    if not fixed:
        r = subprocess.run(["powershell.exe", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File",
                            r"H:\System Configuration\scripts\Invoke-Elevated.ps1", "-File",
                            os.path.join(here, "2026-11-13-wobbly-glow-worker-restart.ps1")],
                           capture_output=True, text=True, timeout=60,
                           creationflags=subprocess.CREATE_NO_WINDOW)
        log.append({"t": round(time.time() - t0, 2), "phase": "C", "elevated": r.stdout.strip()[-600:]})
        sample("C", h, 12)
finally:
    u.PostMessageW(h, 0x0010, 0, 0)
    try:
        win.wait(5)
    except subprocess.TimeoutExpired:
        win.kill()
for row in log:
    print(json.dumps(row))
