# Opens the glow test window (no clicks, no keys), records the main screen and
# prints what the glow tool publishes for it every 0.5 s. Usage: probe.py <new dir> [monitor]
import ctypes, ctypes.wintypes as W, json, os, struct, subprocess, sys, time

k = ctypes.WinDLL("kernel32", use_last_error=True)
u = ctypes.WinDLL("user32")
k.OpenFileMappingW.restype = W.HANDLE
k.MapViewOfFile.restype = ctypes.c_void_p
k.MapViewOfFile.argtypes = [W.HANDLE, W.DWORD, W.DWORD, W.DWORD, ctypes.c_size_t]
k.UnmapViewOfFile.argtypes = [ctypes.c_void_p]
k.CloseHandle.argtypes = [W.HANDLE]


def read_map():
    h = k.OpenFileMappingW(4, False, "Local\\SeamlessWobblyWindows.Glow")
    if not h:
        return None
    p = k.MapViewOfFile(h, 4, 0, 0, 56 + 1600)
    b = ctypes.string_at(p, 56 + 1600)
    k.UnmapViewOfFile(p)
    k.CloseHandle(h)
    seq, ver, run, anim, base, mt, mq, rate, cnt, watch = struct.unpack_from("<iIIIqdqdII", b, 0)
    e = {}
    for i in range(min(cnt, 100)):
        hw, live, off, fr = struct.unpack_from("<IIff", b, 56 + 16 * i)
        e[hw] = (live, round(off, 2), round(fr, 2))
    return {"running": run, "animated": anim, "count": cnt, "e": e, "watch": watch}


def tool_windows(target):
    """Top-level windows directly below the target (the glow window sits there)."""
    out = []
    h = u.GetWindow(target, 2)  # GW_HWNDNEXT
    buf = ctypes.create_unicode_buffer(128)
    r = W.RECT()
    for _ in range(3):
        if not h:
            break
        u.GetClassNameW(h, buf, 128)
        u.GetWindowRect(h, ctypes.byref(r))
        out.append((hex(h), buf.value, u.IsWindowVisible(h), (r.left, r.top, r.right, r.bottom)))
        h = u.GetWindow(h, 2)
    return out


def main(out, monitor):
    sys.path.insert(0, r"H:\System Configuration\agent-tools\VideoCapture")
    import vcap
    test = os.path.join(os.path.dirname(os.path.abspath(__file__)), "2026-11-13-wobbly-glow-test.py")
    win = subprocess.Popen([sys.executable, test, "--window", "16"], stdout=subprocess.PIPE, text=True,
                           creationflags=subprocess.CREATE_NO_WINDOW)
    h = int(win.stdout.readline())
    rec = vcap.Recorder(out, audio_pid=0, monitor=monitor)
    rec.start()
    log = []
    try:
        for _ in range(24):
            m = read_map()
            log.append({"t": round(rec.elapsed(), 2), "fg": u.GetForegroundWindow() == h,
                        "running": m and m["running"], "entry": m and m["e"].get(h),
                        "below": tool_windows(h)})
            time.sleep(0.5)
    finally:
        rec.stop()
        u.PostMessageW(h, 0x0010, 0, 0)
        try:
            win.wait(5)
        except subprocess.TimeoutExpired:
            win.kill()
    for row in log:
        print(json.dumps(row))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]) if len(sys.argv) > 2 else 3)
