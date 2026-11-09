"""Live hover proof for the notification panel: records the screen while the pointer glides
over the bell, the group title and its two buttons. Writes a cropped MP4 and GIF. Silent:
every console child runs through vcap's hidden runners."""
import ctypes
from ctypes import wintypes
import os
import sys
import time

sys.path.insert(0, r'H:\System Configuration\agent-tools\VideoCapture')
import vcap

u = ctypes.windll.user32
u.SetProcessDPIAware()
take = sys.argv[1]
out = r'H:\Windhawk Configuration\reports'


class LII(ctypes.Structure):
    _fields_ = [('cbSize', wintypes.UINT), ('dwTime', wintypes.DWORD)]


lii = LII(ctypes.sizeof(LII), 0)
u.GetLastInputInfo(ctypes.byref(lii))
idle = (ctypes.windll.kernel32.GetTickCount() - lii.dwTime) / 1000
#  --approved: the owner said in chat they are away (other agents' synthetic input resets idle).
assert idle >= 20 or '--approved' in sys.argv, f'Owner active {idle:.0f}s ago; no pointer test'

u.WindowFromPoint.argtypes = [wintypes.POINT]
u.WindowFromPoint.restype = wintypes.HWND


def panel_visible():
    name = ctypes.create_unicode_buffer(256)
    u.GetClassNameW(u.WindowFromPoint(wintypes.POINT(2350, 247)), name, 256)
    return name.value == 'Windows.UI.Core.CoreWindow'


pos = wintypes.POINT()
u.GetCursorPos(ctypes.byref(pos))
home = (pos.x, pos.y)


def glide(x, y, steps=24):
    p = wintypes.POINT()
    u.GetCursorPos(ctypes.byref(p))
    for i in range(1, steps + 1):
        u.SetCursorPos(round(p.x + (x - p.x) * i / steps), round(p.y + (y - p.y) * i / steps))
        #  A zero-length move is ignored by XAML; a real 1 px there-and-back raises pointer-over.
        u.mouse_event(1, 1, 0, 0, 0)
        u.mouse_event(1, -1, 0, 0, 0)
        time.sleep(0.012)


rec = vcap.Recorder(os.path.join(out, take), monitor=1, audio_pid=0, cursor=True)
rec.start()
try:
    for attempt in range(3):
        if panel_visible():
            break
        os.startfile('ms-actioncenter:')
        time.sleep(1.2)
    assert panel_visible(), 'Notification panel did not open'
    glide(2228, 160)
    time.sleep(1.0)
    for x, y in [(2411, 96), (2228, 160), (2350, 247), (2476, 247), (2513, 247), (2350, 247), (2228, 160)]:
        glide(x, y)
        time.sleep(1.1)
finally:
    u.SetCursorPos(*home)
    u.keybd_event(27, 0, 0, 0)
    u.keybd_event(27, 0, 2, 0)
    time.sleep(0.6)
    print('stop', rec.stop())

video = os.path.join(out, take, 'video.mkv')
crop = 'crop=330:300:2215:60'
mp4 = os.path.join(out, take + '.mp4')
gif = os.path.join(out, take + '.gif')
vcap.run_hidden(['ffmpeg', '-hide_banner', '-loglevel', 'error', '-i', video, '-vf',
                 crop + ',fps=60,scale=660:-2:flags=lanczos,format=yuv420p', '-c:v', 'libx264',
                 '-crf', '16', '-preset', 'slow', '-movflags', '+faststart', '-an', mp4], check=True)
vcap.run_hidden(['ffmpeg', '-hide_banner', '-loglevel', 'error', '-i', video, '-filter_complex',
                 crop + ',fps=24,scale=495:-1:flags=lanczos,split[a][b];[a]palettegen=stats_mode=diff[p];'
                 '[b][p]paletteuse=dither=sierra2_4a', gif], check=True)
print(mp4)
print(gif)
