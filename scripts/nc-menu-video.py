"""Video proof for the group "..." menu: opens the notification panel, opens the first group's
menu through UI Automation (no pointer), holds, closes, opens again. Writes a cropped MP4 and
GIF. Silent: every console child runs hidden. Esc is sent only while the panel has focus."""
import ctypes
from ctypes import wintypes as w
import os
import subprocess
import sys
import time

sys.path.insert(0, r'H:\System Configuration\agent-tools\VideoCapture')
import vcap

u = ctypes.windll.user32
u.SetProcessDPIAware()
u.WindowFromPoint.argtypes = [w.POINT]
u.WindowFromPoint.restype = w.HWND
take = sys.argv[1]
out = r'H:\Windhawk Configuration\reports'


def cls(h):
    b = ctypes.create_unicode_buffer(64)
    u.GetClassNameW(h, b, 64)
    return b.value


def panel():
    h = u.GetAncestor(u.WindowFromPoint(w.POINT(2350, 200)), 2)
    return h if cls(h) == 'Windows.UI.Core.CoreWindow' else None


def invoke(root):
    ps = r"""
Add-Type -AssemblyName UIAutomationClient, UIAutomationTypes
$A = [System.Windows.Automation.AutomationElement]
$b = $A::FromHandle([IntPtr]%d).FindFirst([System.Windows.Automation.TreeScope]::Descendants,
  (New-Object System.Windows.Automation.PropertyCondition($A::AutomationIdProperty, 'SettingsButton')))
if (-not $b) { 'no button'; exit 1 }
$b.GetCurrentPattern([System.Windows.Automation.InvokePattern]::Pattern).Invoke()
""" % root
    r = subprocess.run(['powershell.exe', '-NoProfile', '-Command', ps], capture_output=True, text=True,
                       creationflags=subprocess.CREATE_NO_WINDOW)
    assert r.returncode == 0, r.stdout + r.stderr


def esc(root):
    fp, pp = w.DWORD(), w.DWORD()
    u.GetWindowThreadProcessId(u.GetForegroundWindow(), ctypes.byref(fp))
    u.GetWindowThreadProcessId(root, ctypes.byref(pp))
    if fp.value != pp.value:
        return False
    u.keybd_event(0x1B, 0, 0, 0)
    u.keybd_event(0x1B, 0, 2, 0)
    return True


def menu_on_top():
    return cls(u.WindowFromPoint(w.POINT(2300, 300))) == 'Xaml_WindowedPopupClass'


rec = vcap.Recorder(os.path.join(out, take), monitor=1, audio_pid=0, cursor=False)
rec.start()
root = None
try:
    time.sleep(0.5)
    os.startfile('ms-actioncenter:')
    for _ in range(30):
        time.sleep(0.1)
        root = panel()
        if root:
            break
    assert root, 'Notification panel did not open'
    time.sleep(1.0)
    for round_ in range(2):
        invoke(root)
        time.sleep(0.4)
        print('menu fully on top', round_, menu_on_top())
        time.sleep(1.8)
        esc(root)
        time.sleep(0.9)
finally:
    if root:
        esc(root)
    time.sleep(0.6)
    print('stop', rec.stop())

video = os.path.join(out, take, 'video.mkv')
crop = 'crop=620:360:1940:60'
mp4 = os.path.join(out, take + '.mp4')
gif = os.path.join(out, take + '.gif')
webp = os.path.join(out, take + '.webp')
vcap.run_hidden(['ffmpeg', '-y', '-hide_banner', '-loglevel', 'error', '-i', video, '-vf',
                 crop + ',fps=60,scale=1240:-2:flags=lanczos,format=yuv420p', '-c:v', 'libx264',
                 '-crf', '16', '-preset', 'slow', '-movflags', '+faststart', '-an', mp4], check=True)
vcap.run_hidden(['ffmpeg', '-y', '-hide_banner', '-loglevel', 'error', '-i', video, '-filter_complex',
                 crop + ',fps=20,scale=620:-1:flags=lanczos,split[a][b];[a]palettegen=stats_mode=diff[p];'
                 '[b][p]paletteuse=dither=sierra2_4a', gif], check=True)
vcap.run_hidden(['ffmpeg', '-y', '-hide_banner', '-loglevel', 'error', '-i', video, '-vf',
                 crop + ',fps=20,scale=620:-1:flags=lanczos', '-c:v', 'libwebp', '-loop', '0',
                 '-quality', '80', webp], check=True)
print(mp4)
print(gif)
print(webp)
