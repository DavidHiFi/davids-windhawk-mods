import ctypes as c, ctypes.wintypes as w, time, json
u=c.WinDLL('user32')
u.FindWindowW.restype=w.HWND
class GTI(c.Structure):
    _fields_=[('cb',w.DWORD),('flags',w.DWORD),('active',w.HWND),('focus',w.HWND),('capture',w.HWND),('menu',w.HWND),('move',w.HWND),('caret',w.HWND),('rc',w.RECT)]
def st(h):
    g=GTI();g.cb=c.sizeof(g);u.GetGUIThreadInfo(u.GetWindowThreadProcessId(h,None),c.byref(g))
    return dict(zoomed=bool(u.IsZoomed(h)),capture=bool(g.capture),move=bool(g.move),menu=bool(g.menu),flags=g.flags)
def key(v,up=False):u.keybd_event(v,0,2 if up else 0,0)
h=u.FindWindowW('SDL_app','Steam'); rows=[]
u.ShowWindow(h,1);time.sleep(.8);u.SetForegroundWindow(h);time.sleep(.3)
for i in range(4):
    r=w.RECT();u.GetWindowRect(h,c.byref(r));x=(r.left+r.right)//2;y=r.top+150
    before=st(h)
    u.SetCursorPos(x,y);key(0x12);time.sleep(.15);u.mouse_event(2,0,0,0,0);time.sleep(.1)
    for n in range(1,8):u.SetCursorPos(x+n*8,y+n*4);time.sleep(.035)
    during=st(h);u.mouse_event(8,0,0,0,0);time.sleep(.1);u.mouse_event(16,0,0,0,0);time.sleep(.1)
    u.mouse_event(4,0,0,0,0);key(0x12,True);time.sleep(.6)
    rows.append(dict(before=before,during=during,after=st(h)))
print(json.dumps(rows))
