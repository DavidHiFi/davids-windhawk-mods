# Live check for Window Manager Plus: Alt+Shift+Right on an owned test window,
# then confirm the pointer sits in the middle of the window on its new monitor.
# Run under: coop lock desktop --as <id> -- python <this file>
import sys, time, json
sys.path.insert(0, r'H:\Windhawk Configuration\reports\2026-10-04-window-manager')
import wmtest as w
p, h = w.spawn('WMP cursor test')
try:
    res = []
    for vk, name in ((0x27, 'right'), (0x25, 'left')):
        m0 = w.idx(h)
        r0 = w.rect(h)
        w.u.SetCursorPos(r0[0] + 20, r0[1] + 20)
        w.focus(h)
        w.chord(0x12, 0x10, vk)
        time.sleep(1.0)
        pt = w.W.POINT(); w.u.GetCursorPos(w.ctypes.byref(pt))
        r1 = w.rect(h)
        cx, cy = (r1[0] + r1[2]) // 2, (r1[1] + r1[3]) // 2
        ok = w.idx(h) != m0 and abs(pt.x - cx) <= 8 and abs(pt.y - cy) <= 8
        res.append(dict(key=name, mon_before=m0, mon_after=w.idx(h), cursor=(pt.x, pt.y), window_center=(cx, cy), ok=ok))
    print(json.dumps(res, indent=1))
finally:
    p.terminate()
