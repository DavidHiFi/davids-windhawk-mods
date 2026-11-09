"""Open the notification panel, invoke the first group's "..." through UIA (no cursor move),
map the panel's windows and child windows, screenshot, then close with Esc."""
import ctypes, os, subprocess, sys, time
from ctypes import wintypes as w
from PIL import ImageGrab
u = ctypes.windll.user32; u.SetProcessDPIAware()
u.WindowFromPoint.argtypes = [w.POINT]; u.WindowFromPoint.restype = w.HWND
out = r'H:\Windhawk Configuration\work\nc-menu'
tag = sys.argv[1] if len(sys.argv) > 1 else 'probe'
def desc(h):
    c = ctypes.create_unicode_buffer(256); t = ctypes.create_unicode_buffer(256)
    u.GetClassNameW(h, c, 256); u.GetWindowTextW(h, t, 256)
    r = w.RECT(); u.GetWindowRect(h, ctypes.byref(r)); p = w.DWORD(); u.GetWindowThreadProcessId(h, ctypes.byref(p))
    return f'{hex(h or 0)} pid={p.value} [{c.value}] "{t.value}" ({r.left},{r.top},{r.right},{r.bottom}) vis={u.IsWindowVisible(h)} ex={u.GetWindowLongW(h,-20)&0xffffffff:#x}'
def kids(h, d=1):
    rows = []
    CB = ctypes.WINFUNCTYPE(w.BOOL, w.HWND, w.LPARAM)
    def cb(c, _):
        if u.GetParent(c) == h: rows.append(('  ' * d) + desc(c)); rows.extend(kids(c, d + 1))
        return True
    u.EnumChildWindows(h, CB(cb), 0)
    return rows
def panel():
    h = u.WindowFromPoint(w.POINT(2350, 200))
    return u.GetAncestor(h, 2)
os.startfile('ms-actioncenter:')
for _ in range(20):
    time.sleep(0.15)
    root = panel(); c = ctypes.create_unicode_buffer(64); u.GetClassNameW(root, c, 64)
    if c.value == 'Windows.UI.Core.CoreWindow': break
print('panel', desc(root))
if c.value != 'Windows.UI.Core.CoreWindow':
    sys.exit('panel did not open; nothing touched')
for k in kids(root): print(k)
ps = r"""
Add-Type -AssemblyName UIAutomationClient, UIAutomationTypes
$A = [System.Windows.Automation.AutomationElement]
$w = $A::FromHandle([IntPtr]%d)
$b = $w.FindFirst([System.Windows.Automation.TreeScope]::Descendants, (New-Object System.Windows.Automation.PropertyCondition($A::AutomationIdProperty, 'SettingsButton')))
if (-not $b) { 'no button'; exit 1 }
"button $($b.Current.Name) $($b.Current.BoundingRectangle)"
$b.GetCurrentPattern([System.Windows.Automation.InvokePattern]::Pattern).Invoke()
""" % root
r = subprocess.run(['powershell.exe', '-NoProfile', '-Command', ps], capture_output=True, text=True, creationflags=0x08000000)
print(r.stdout.strip(), r.stderr.strip()[-300:])
t0 = time.time(); last = None
while time.time() - t0 < float(os.environ.get('NC_WATCH', '0.8')):
    top = desc(u.WindowFromPoint(w.POINT(2300, 320))).split(' (')[0]
    if top != last: print(f'{time.time()-t0:5.2f}s top@2300 {top}'); last = top
    time.sleep(0.05)
sw = u.GetSystemMetrics(0)
ImageGrab.grab().crop((sw - 1100, 0, sw, 600)).save(os.path.join(out, tag + '.png'))
for x, y in [(2000, 320), (2150, 320), (2300, 320)]:
    print('at', x, y, desc(u.WindowFromPoint(w.POINT(x, y))))
if '--lower' in sys.argv:
    pop = u.WindowFromPoint(w.POINT(2000, 320))
    cc = ctypes.create_unicode_buffer(64); u.GetClassNameW(pop, cc, 64)
    if cc.value != 'Xaml_WindowedPopupClass': sys.exit('menu not found; nothing touched')
    print('lower menu under panel', u.SetWindowPos(pop, root, 0, 0, 0, 0, 0x13))
    time.sleep(0.15)
    print('after lower at 2300', desc(u.WindowFromPoint(w.POINT(2300, 320))).split(' (')[0])
    ImageGrab.grab().crop((sw - 1100, 0, sw, 600)).save(os.path.join(out, tag + '-lowered.png'))
if '--raisecore' in sys.argv:
    print('raise panel', u.SetWindowPos(root, w.HWND(-1), 0, 0, 0, 0, 0x13), ctypes.GetLastError())
    time.sleep(0.15)
    print('after panel raise at 2300', desc(u.WindowFromPoint(w.POINT(2300, 320))))
    ImageGrab.grab().crop((sw - 1100, 0, sw, 600)).save(os.path.join(out, tag + '-core.png'))
if '--raise' in sys.argv:
    pop = u.WindowFromPoint(w.POINT(2000, 320))
    print('raise', u.SetWindowPos(pop, w.HWND(-1), 0, 0, 0, 0, 0x13), ctypes.GetLastError())
    time.sleep(0.3)
    print('after at 2300', desc(u.WindowFromPoint(w.POINT(2300, 320))))
    ImageGrab.grab().crop((sw - 1100, 0, sw, 600)).save(os.path.join(out, tag + '-raised.png'))
h = u.GetTopWindow(None); i = 0
while h and i < 40 and '--z' in sys.argv:
    p = w.DWORD(); u.GetWindowThreadProcessId(h, ctypes.byref(p))
    if u.IsWindowVisible(h): print('z', i, desc(h))
    h = u.GetWindow(h, 2); i += 1
for _ in range(2):
    fp = w.DWORD(); u.GetWindowThreadProcessId(u.GetForegroundWindow(), ctypes.byref(fp))
    pp = w.DWORD(); u.GetWindowThreadProcessId(root, ctypes.byref(pp))
    if fp.value != pp.value: print('panel not foreground, no Esc'); break
    u.keybd_event(0x1B, 0, 0, 0); u.keybd_event(0x1B, 0, 2, 0); time.sleep(0.3)
