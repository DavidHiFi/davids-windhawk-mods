# Proof image: test window sent to monitor 3 with Alt+Shift+Right, pointer drawn at its real position.
import sys, time
sys.path.insert(0, r'H:\Windhawk Configuration\reports\2026-10-04-window-manager')
import wmtest as w
from PIL import ImageGrab, ImageDraw
p, h = w.spawn('WMP proof', text='Window Manager Plus')
try:
    r0 = w.rect(h); w.u.SetCursorPos(r0[0] + 20, r0[1] + 20)
    w.focus(h); w.chord(0x12, 0x10, 0x27); time.sleep(0.8)
    pt = w.W.POINT(); w.u.GetCursorPos(w.ctypes.byref(pt))
    img = ImageGrab.grab(all_screens=True)
    ox = min(m['mon'][0] for m in w.MONS); oy = min(m['mon'][1] for m in w.MONS)
    x, y = pt.x - ox, pt.y - oy
    d = ImageDraw.Draw(img)
    d.ellipse((x-40, y-40, x+40, y+40), outline='#ff3b30', width=6)
    img.save(r'H:\Windhawk Configuration\work\2026-10-24-window-manager-plus-proof.png')
    print(w.state(h), pt.x, pt.y, img.size)
finally:
    p.terminate()
