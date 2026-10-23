import ctypes as c, ctypes.wintypes as w, time, json, sys
u=c.WinDLL('user32',use_last_error=True)
u.FindWindowW.restype=w.HWND
u.GetForegroundWindow.restype=w.HWND
u.GetWindowThreadProcessId.argtypes=[w.HWND,c.POINTER(w.DWORD)]
u.SendMessageTimeoutW.argtypes=[w.HWND,w.UINT,w.WPARAM,w.LPARAM,w.UINT,w.UINT,c.POINTER(c.c_size_t)]
class GTI(c.Structure):
    _fields_=[('cb',w.DWORD),('flags',w.DWORD),('active',w.HWND),('focus',w.HWND),('capture',w.HWND),('menu',w.HWND),('move',w.HWND),('caret',w.HWND),('rc',w.RECT)]
class WP(c.Structure):
    _fields_=[('length',w.UINT),('flags',w.UINT),('show',w.UINT),('min',w.POINT),('max',w.POINT),('normal',w.RECT)]
def rect(h):
    r=w.RECT(); u.GetWindowRect(h,c.byref(r)); return [r.left,r.top,r.right,r.bottom]
def state(h):
    g=GTI();g.cb=c.sizeof(g);tid=u.GetWindowThreadProcessId(h,None);u.GetGUIThreadInfo(tid,c.byref(g))
    result=c.c_size_t(); ok=u.SendMessageTimeoutW(h,0,0,0,2,700,c.byref(result))
    return dict(rect=rect(h),flags=g.flags,capture=g.capture,move=g.move,responding=bool(ok),zoomed=bool(u.IsZoomed(h)))
def key(v,up=False):u.keybd_event(v,0,2 if up else 0,0)
h=u.FindWindowW('SDL_app','Steam')
if not h:raise SystemExit('Steam window missing')
original=WP();original.length=c.sizeof(original);u.GetWindowPlacement(h,c.byref(original))
cursor=w.POINT();u.GetCursorPos(c.byref(cursor));fg=u.GetForegroundWindow()
rows=[]
resize=len(sys.argv)>2 and sys.argv[2]=='resize'
down=8 if resize else 2; up=16 if resize else 4
try:
    u.PostMessageW(h,0x1f,0,0)
    u.ShowWindowAsync(h,9);time.sleep(.5)
    key(0x12);key(0x12,True);u.SetForegroundWindow(h);time.sleep(.3)
    for i in range(int(sys.argv[1]) if len(sys.argv)>1 else 1):
        before=state(h);r=rect(h);x=r[0]+min(650,(r[2]-r[0])//2);y=r[1]+150
        u.SetCursorPos(x,y);key(0x12);time.sleep(.15);u.mouse_event(down,0,0,0,0);time.sleep(.1)
        for n in range(1,9):u.SetCursorPos(x+n*8,y+n*4);time.sleep(.035)
        during=state(h)
        u.mouse_event(up,0,0,0,0);key(0x12,True);time.sleep(.4)
        after=state(h);rows.append(dict(before=before,during=during,after=after))
        if after['move'] or after['capture'] or not after['responding']:
            key(0x1b);key(0x1b,True);u.PostMessageW(h,0x1f,0,0);time.sleep(.3);break
finally:
    u.mouse_event(up,0,0,0,0);key(0x12,True)
    u.SetWindowPlacement(h,c.byref(original));u.SetCursorPos(cursor.x,cursor.y)
    if fg:u.SetForegroundWindow(fg)
print(json.dumps(rows,indent=2))
