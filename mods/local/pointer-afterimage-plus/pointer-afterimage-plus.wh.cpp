// ==WindhawkMod==
// @id              pointer-afterimage-plus
// @name            Pointer Afterimage Plus
// @description     A real motion blur for the mouse pointer, made of fading afterimages of your own cursor, with an optional particle trail and click ripples
// @version         1.3.7
// @author          DavidHiFi, sidlikesgrapess
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @include         explorer.exe
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshcore -lwinmm -ld2d1 -ld3d11 -ldcomp -lshlwapi -lole32 -loleaut32 -luuid -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -ladvapi32
// @license         Unlicense
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Pointer Afterimage Plus
Based on Pointer Afterimage Motion Blur by sidlikesgrapess
([original project](https://github.com/sidlikesgrapess/CursorMotionBlur)).

A live motion blur for the mouse pointer, everywhere in Windows. While the
mouse moves, fading copies of your actual cursor are drawn along its recent
path, so it looks like a camera motion blur rather than a trail.

![Demo](https://raw.githubusercontent.com/sidlikesgrapess/CursorMotionBlur/main/assets/demo.gif)

## What is new in 1.3.0
- **Particle trail.** Small glowing dots drift and fade behind the pointer as
  it moves. Pick how many, how big, how long they last and their colour.
- **Click ripples.** A ring grows and fades out wherever you press the left or
  right button.
- Both are off until you turn them on, and both pause with the blur in
  fullscreen games. The idea and the look come from MCheng404's Mouse Trail
  mod, which this mod now replaces.

## What is new in 1.2.2
- **The taskbar no longer blinks over games.** Windows no longer mistakes the
  trail for a fullscreen app, so the taskbar stays on top when you alt-tab out
  of a fullscreen game.

## What is new in 1.2.1
- **No more trail leftovers.** Pieces of earlier trails no longer linger on
  screen around the pointer while it moves.

## What is new in 1.2.0
- **Drawn on the GPU.** The blur is composited with DirectComposition and
  drawn with Direct2D instead of building a bitmap on the CPU and handing it to
  Windows every frame. The look is the same.
- **Renderer setting.** GPU is the default. GDI is the older painter, kept for
  troubleshooting. If the GPU path cannot start or fails while running, the mod
  switches to GDI by itself and writes a log line saying which renderer armed.

## Features
- Uses your real cursor: your scheme, size and colour, and whatever shape it
  has right now. Works with any pointer size and monitor scaling.
- Optionally hides the real pointer during very fast movement so only the blur
  shows.
- Pauses itself while a fullscreen app or game is in front.
- Runs in its own small Windhawk process.
- With the GDI renderer, a small window in explorer.exe also lets the blur show
  above the Start menu.

## Limitations
- Click ripples come from the mouse itself, so none show while an
  administrator window (Task Manager, an admin terminal) is in front.
- The GPU renderer draws in the mod's own window, which sits above normal
  windows and the taskbar but not above the Start menu or Search. Pick the GDI
  renderer if you want the blur over those.
- In a few apps (Paint, Photos, File Explorer's address and search bars) the
  pointer can briefly flicker to the arrow while the blur is drawn. If it gets
  in the way, increase "Minimum blur speed": slower movements draw no blur.

## Resource use
- No drawing while the mouse is still, and almost none while it moves slower
  than "Minimum blur speed".
- The GPU renderer needs more memory than GDI because it loads Direct3D and
  Direct2D, and it uses almost no CPU while the mouse moves. GDI needs only a
  few MB and about 1-2.5% CPU while the mouse moves fast.

## Troubleshooting
- **The cursor stays invisible.** Disable and re-enable the mod, or open
  Settings > Bluetooth & devices > Mouse > Additional mouse settings > Pointers
  and click OK.
- **The blur is stuck at the wrong size or shape** after changing the pointer
  size or scheme. Disable and re-enable the mod.
- **Another tool's custom cursors get reset.** Restoring after hiding reloads
  the Windows cursor scheme, so turn hiding off if you use a tool that swaps
  the system cursors, such as the Shake to Find Cursor or macOS magnifying
  cursor mods.
- **The cursor hides too quickly or not at all.** Raise or lower "Hide above
  speed", or turn hiding off.
- **The blur seems slightly behind the pointer at high speed.** Windows draws
  the real pointer more directly than any window can be drawn, so every
  overlay is 1-2 frames behind. A faster refresh rate reduces this latency obviously.
- **No blur above the Start menu.** Switch Renderer to GDI.
- A standalone app version (no Windhawk needed) is on the
  [original homepage](https://github.com/sidlikesgrapess/CursorMotionBlur).

## Credits
- Cursor blur: sidlikesgrapess, Pointer Afterimage Motion Blur (Unlicense).
- Particle and ripple look: MCheng404, Mouse Trail (MIT). The effects here are
  written fresh for this renderer; no Mouse Trail code is copied.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- trailOpacity: 50
  $name: 'Trail opacity (%)'
  $description: '1 to 100 (Suggested: 50). How solid the blur is right behind the pointer.'
- trailMs: 25
  $name: 'Trail length (ms)'
  $description: '10 to 150 (Suggested: 25). How far back in time the blur reaches.'
- drawSpeed: 29
  $name: 'Minimum blur speed (cm/s)'
  $description: '0 to 50 (Suggested: 29). Slower moves draw no blur and use almost no CPU. 0 draws at any speed.'
- hideWhenFast: true
  $name: 'Hide the real cursor when moving very fast'
  $description: 'Swaps the system cursors for an invisible one while you move fast, and puts your cursor scheme back afterwards.'
- hideSpeed: 30
  $name: 'Hide above speed (cm/s)'
  $description: '20 to 300 (Suggested: 30). Measured on the main screen, so the same hand speed counts on every screen.'
- particles: false
  $name: 'Particle trail'
  $description: 'Small glowing dots that drift and fade behind the moving pointer.'
- particleAmount: 5
  $name: 'Particle amount'
  $description: '1 to 10 (Suggested: 5). How close together the dots are along the path.'
- particleSize: 3
  $name: 'Particle size'
  $description: '1 to 10 (Suggested: 3). Pixels at 100% scaling with the normal pointer size.'
- particleLife: 450
  $name: 'Particle lifetime (ms)'
  $description: '100 to 1500 (Suggested: 450). How long each dot takes to fade away.'
- particleColor: gradient
  $name: 'Particle colour'
  $options:
  - gradient: 'Blue to mauve'
  - blue: 'Blue'
  - mauve: 'Mauve'
- ripples: false
  $name: 'Click ripples'
  $description: 'A ring that grows and fades where you press the left or right button.'
- rippleSize: 36
  $name: 'Ripple size'
  $description: '20 to 120 (Suggested: 36). How wide the ring gets, in pixels at 100% scaling.'
- rippleMs: 400
  $name: 'Ripple duration (ms)'
  $description: '150 to 1000 (Suggested: 400). How long one ring takes to grow and fade.'
- pauseInFullscreen: true
  $name: 'Pause in fullscreen apps and games'
  $description: 'On, nothing is drawn while a game or video fills the screen.'
- renderer: gpu
  $name: 'Renderer'
  $description: 'GPU is suggested. GDI is the older painter, kept for troubleshooting and for drawing above the Start menu. If the GPU cannot start, the mod falls back to GDI by itself.'
  $options:
  - gpu: 'GPU (suggested)'
  - gdi: 'GDI (older, on the CPU)'
- settingsGlass: true
  $name: 'Blurred settings window'
  $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.
- nativeSettingsTitleBar: false
  $name: 'Native Windows title bar'
  $description: Use the Windows title bar and window buttons for this settings window. Applies when you save.
- settingsTrayIcon: true
  $name: 'Tray icon'
  $description: 'Click it to open these settings. Right-click it to pause the effects or open settings. When off, change settings in Windhawk.'
*/
// ==/WindhawkModSettings==

// How it works. Three threads:
//   sampler  reads the cursor position on every raw mouse report and decides when the real cursor should be hidden
//   hider    swaps the system cursors for an invisible one and back (restoring takes ~20 ms, so it runs on its own)
//   render   works out the fading copies along the recent path and shows them in a click-through window; it owns a
//            window that receives the raw mouse input. GPU renderer (default): the copies are drawn with Direct2D into a
//            DirectComposition surface, and one Commit moves and updates it. GDI renderer (legacy, also the automatic
//            fallback): the copies are blended by hand into one bitmap pushed through UpdateLayeredWindow, drawn in
//            explorer.exe's window above the Start menu when it provides one (see the end of the file)

#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <imm.h>
#include <atomic>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <set>
#include <string>
#include <vector>
#include <mmsystem.h>
#include <shellapi.h>
#include <sddl.h>
#include <shellscalingapi.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d2d1_1.h>
#include <dcomp.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Crisp icons (2026-11-26): tray icons are drawn at 4x the size the taskbar shows them and shrunk
// here with a box filter, so curves and glyph edges are smooth instead of stretched and stepped.
// The result carries straight alpha, which is what Windows expects in an icon.
static HICON Crisp_ShrinkIcon(HICON big, int factor) {
    if (!big || factor <= 1) return big;
    ICONINFO ii{};
    if (!GetIconInfo(big, &ii)) return big;
    HICON out = nullptr;
    BITMAP bm{};
    if (ii.hbmColor && GetObjectW(ii.hbmColor, sizeof(bm), &bm) && bm.bmWidth == bm.bmHeight &&
        bm.bmWidth >= factor && bm.bmWidth % factor == 0) {
        const int src = bm.bmWidth, n = src / factor;
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = src;
        bi.bmiHeader.biHeight = -src;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        unsigned int* in = new unsigned int[(size_t)src * src];
        HDC screen = GetDC(nullptr);
        if (GetDIBits(screen, ii.hbmColor, 0, src, in, &bi, DIB_RGB_COLORS) == src) {
            bool premul = true, anyAlpha = false;
            for (size_t i = 0; i < (size_t)src * src; i++) {
                unsigned int p = in[i], a = p >> 24;
                if (a) anyAlpha = true;
                if (((p >> 16) & 0xFF) > a || ((p >> 8) & 0xFF) > a || (p & 0xFF) > a) premul = false;
            }
            void* bits = nullptr;
            bi.bmiHeader.biWidth = n;
            bi.bmiHeader.biHeight = -n;
            HBITMAP color = anyAlpha ? CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0) : nullptr;
            if (color && bits) {
                unsigned int* px = (unsigned int*)bits;
                const unsigned int cnt = (unsigned int)(factor * factor);
                for (int y = 0; y < n; y++)
                    for (int x = 0; x < n; x++) {
                        unsigned int sa = 0, sr = 0, sg = 0, sb = 0;
                        for (int dy = 0; dy < factor; dy++)
                            for (int dx = 0; dx < factor; dx++) {
                                unsigned int p = in[(size_t)(y * factor + dy) * src + x * factor + dx], a = p >> 24;
                                unsigned int r = (p >> 16) & 0xFF, g = (p >> 8) & 0xFF, b = p & 0xFF;
                                if (!premul) {
                                    r = (r * a + 127) / 255;
                                    g = (g * a + 127) / 255;
                                    b = (b * a + 127) / 255;
                                }
                                sa += a; sr += r; sg += g; sb += b;
                            }
                        unsigned int a = (sa + cnt / 2) / cnt, r = 0, g = 0, b = 0;
                        if (a && sa) {
                            r = (sr * 255 + sa / 2) / sa; if (r > 255) r = 255;
                            g = (sg * 255 + sa / 2) / sa; if (g > 255) g = 255;
                            b = (sb * 255 + sa / 2) / sa; if (b > 255) b = 255;
                        }
                        px[(size_t)y * n + x] = a ? ((a << 24) | (r << 16) | (g << 8) | b) : 0;
                    }
                // A zero mask: with 32-bit colour Windows draws from the alpha channel.
                unsigned char* maskBits = new unsigned char[(size_t)((n + 15) / 16) * 2 * n]();
                HBITMAP mask = CreateBitmap(n, n, 1, 1, maskBits);
                delete[] maskBits;
                if (mask) {
                    ICONINFO o{TRUE, 0, 0, mask, color};
                    out = CreateIconIndirect(&o);
                    DeleteObject(mask);
                }
            }
            if (color) DeleteObject(color);
        }
        ReleaseDC(nullptr, screen);
        delete[] in;
    }
    if (ii.hbmColor) DeleteObject(ii.hbmColor);
    if (ii.hbmMask) DeleteObject(ii.hbmMask);
    if (!out) return big;
    DestroyIcon(big);
    return out;
}


constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();

#define HOLD_MS        10      // how long after the last fast moment the cursor may come back
#define SHOW_WINDOW_MS 12      // the speed that brings the cursor back is measured over just this many ms
// ~px of travel one copy covers at cursor size 32 (keeps the opacity independent of copy density)
#define COVER_PX       10.0
#define MAX_SAMPLES    512
#define MAX_COPIES     100     // the most copies spread along the trail in one frame
#define COPY_BUF       (MAX_SAMPLES + MAX_COPIES)
#define MAX_SPRITES    16      // cursor pictures kept before the cache is emptied
#define WM_APP_PAUSED  (WM_APP + 1)
#define WM_APP_WATCH   (WM_APP + 2)   // to explorer's window: wParam is the mod's process, to watch

struct Sample { int x, y; LONGLONG t; };
struct Sprite { int w, h, hx, hy, id; UINT32* px; };   // cursor picture at its own size: premultiplied BGRA, hotspot
struct Copy { int x, y; float a; };                   // one copy: top-left relative to the frame, opacity 0-1

// settings (written by WhTool_ModSettingsChanged, read by the threads)
// The settings window (the standard one, at the end of the file) and its tray menu.
namespace papset {
void OpenSettingsWindow();
void CloseSettingsWindow();
int ShowTrayMenu(HWND owner, POINT pt, bool paused);
extern std::atomic<HWND> g_settingsWnd;
}  // namespace papset

static std::atomic<int> g_opacity, g_trailMs, g_drawSpeedCm, g_hideWhenFast, g_hideSpeedCm, g_pauseInFullscreen;
static std::atomic<int> g_rendererWanted;   // 0 = GPU (DirectComposition + Direct2D), 1 = GDI (legacy)
static std::atomic<int> g_particles, g_pAmount, g_pSize, g_pLifeMs, g_pColor;   // colour: 0 gradient, 1 blue, 2 mauve
static std::atomic<int> g_ripples, g_rSize, g_rMs;

// shared between the threads (guarded by g_gate)
static CRITICAL_SECTION g_gate;
static Sample g_hist[MAX_SAMPLES];
static int g_histN;
static HCURSOR g_curHandle;
static bool g_curVisible, g_hideWanted;
static int g_monCursor = 32;          // cursor width on the monitor the cursor is on
static std::atomic<int> g_monGap{7};     // ms between frames: half a refresh of the monitor the cursor is on
static std::atomic<bool> g_blankActive;  // the system cursors are currently swapped for an invisible one
static std::atomic<bool> g_drawFailed;   // the overlay could not draw: then never hide the real cursor
static std::atomic<bool> g_monStale, g_spritesStale;   // display or cursor settings changed
static std::atomic<bool> g_recheck;      // settings or the active window changed: look at the window in front now
static std::atomic<bool> g_paused;       // a fullscreen app is in front, or paused from the tray
static std::atomic<bool> g_userPaused;   // paused from the tray menu (until the mod restarts)
static std::atomic<bool> g_drawing;      // the blur is drawn: above the minimum blur speed, or while the cursor is hidden
static std::atomic<HCURSOR> g_pictureOf; // the cursor whose picture the blur has: hiding waits until it is the current one
static std::atomic<bool> g_stop;
static std::atomic<HWND> g_wnd;          // the overlay window (owned by the render thread)

static HANDLE g_moved, g_mouseWake, g_hideChanged;   // auto-reset events
static HANDLE g_ready;                               // set when the render thread has set up (or failed to)
static HANDLE g_threads[3];
static LARGE_INTEGER g_freq, g_start;

static LONGLONG Now() {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return (t.QuadPart - g_start.QuadPart) * 1000 / g_freq.QuadPart;
}

static double Dist(Sample a, Sample b) {
    double dx = b.x - a.x, dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

static int Clamp(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

static void LoadSettings() {
    g_opacity = Clamp(Wh_GetIntSetting(L"trailOpacity"), 1, 100);
    g_trailMs = Clamp(Wh_GetIntSetting(L"trailMs"), 10, 150);
    g_hideWhenFast = Wh_GetIntSetting(L"hideWhenFast") != 0;
    g_hideSpeedCm = Clamp(Wh_GetIntSetting(L"hideSpeed"), 20, 300);
    g_drawSpeedCm = Clamp(Wh_GetIntSetting(L"drawSpeed"), 0, 50);
    g_pauseInFullscreen = Wh_GetIntSetting(L"pauseInFullscreen") != 0;
    PCWSTR renderer = Wh_GetStringSetting(L"renderer");
    g_rendererWanted = renderer && !_wcsicmp(renderer, L"gdi") ? 1 : 0;
    if (renderer) Wh_FreeStringSetting(renderer);
    g_pAmount = Clamp(Wh_GetIntSetting(L"particleAmount"), 1, 10);
    g_pSize = Clamp(Wh_GetIntSetting(L"particleSize"), 1, 10);
    g_pLifeMs = Clamp(Wh_GetIntSetting(L"particleLife"), 100, 1500);
    PCWSTR color = Wh_GetStringSetting(L"particleColor");
    g_pColor = color && !_wcsicmp(color, L"blue") ? 1 : color && !_wcsicmp(color, L"mauve") ? 2 : 0;
    if (color) Wh_FreeStringSetting(color);
    g_rSize = Clamp(Wh_GetIntSetting(L"rippleSize"), 20, 120);
    g_rMs = Clamp(Wh_GetIntSetting(L"rippleMs"), 150, 1000);
    g_particles = Wh_GetIntSetting(L"particles") != 0;   // last: the sampler reads these to decide what to wake
    g_ripples = Wh_GetIntSetting(L"ripples") != 0;
}

// A monitor's refresh rate.
static int RefreshRate(HMONITOR mon) {
    MONITORINFOEXW mi;
    mi.cbSize = sizeof(mi);
    DEVMODEW dm = {};
    dm.dmSize = sizeof(dm);
    if (GetMonitorInfoW(mon, &mi) && EnumDisplaySettingsW(mi.szDevice, ENUM_CURRENT_SETTINGS, &dm) &&
        dm.dmDisplayFrequency > 1)
        return dm.dmDisplayFrequency;
    return 60;
}

// A monitor's physical pixel density, from the size Windows reports for it (its DPI setting if that looks wrong).
static double PixelsPerCm(HMONITOR mon, UINT dpi) {
    double fallback = dpi / 2.54 < 20 ? 20 : dpi / 2.54;
    MONITORINFOEXW mi;
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(mon, &mi)) return fallback;
    HDC dc = CreateDCW(L"DISPLAY", mi.szDevice, nullptr, nullptr);
    if (!dc) return fallback;
    int mm = GetDeviceCaps(dc, HORZSIZE), px = GetDeviceCaps(dc, HORZRES);
    DeleteDC(dc);
    return mm >= 150 && mm <= 2500 && px >= 320 ? px / (mm / 10.0) : fallback;
}

static bool FullscreenAppRunning() {
    QUERY_USER_NOTIFICATION_STATE s;
    return SHQueryUserNotificationState(&s) == S_OK &&
           (s == QUNS_BUSY || s == QUNS_RUNNING_D3D_FULL_SCREEN || s == QUNS_PRESENTATION_MODE);
}

// The pointer size from Settings > Accessibility > Mouse pointer and touch, at 100% scaling: 32 px at size 1 and 16 px
// more per step. (The cursor pictures Windows hands out can stay at size 1 when this is larger.)
static int PointerSize() {
    DWORD size = 0, len = sizeof(size);
    if (RegGetValueW(HKEY_CURRENT_USER, L"Control Panel\\Cursors", L"CursorBaseSize", RRF_RT_REG_DWORD, nullptr, &size,
                     &len) == ERROR_SUCCESS && size >= 32 && size <= 256)
        return (int)size;
    return 32;
}

static void ReloadCursors() { SystemParametersInfoW(SPI_SETCURSORS, 0, nullptr, 0); }

// Whether our invisible cursor is in place, also kept in the mod's storage: if the process is ever killed while hiding,
// the next start knows to put the user's cursors back (and otherwise leaves the cursor scheme alone). That is a storage
// write per hide and per restore, only while hiding is switched on: a deliberate trade for being able to recover.
// The flag is per user, as the storage is shared by everyone signed in on the machine.
static WCHAR g_hiddenKey[256] = L"cursorsHidden";

// The flag's name with the user's SID in it.
static void BuildHiddenKey() {
    HANDLE token;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return;
    alignas(TOKEN_USER) BYTE buf[SECURITY_MAX_SID_SIZE + sizeof(TOKEN_USER)];
    DWORD len;
    LPWSTR sid;
    if (GetTokenInformation(token, TokenUser, buf, sizeof(buf), &len) &&
        ConvertSidToStringSidW(((TOKEN_USER*)buf)->User.Sid, &sid)) {
        swprintf_s(g_hiddenKey, L"cursorsHidden_%s", sid);
        LocalFree(sid);
    }
    CloseHandle(token);
}

static void SetBlank(bool on) {
    g_blankActive = on;
    Wh_SetIntValue(g_hiddenKey, on);
}

// A process's integrity level (medium for normal apps, high for administrator ones), or -1 if its token can't be read.
static int Integrity(HANDLE process) {
    int level = -1;
    HANDLE token;
    if (OpenProcessToken(process, TOKEN_QUERY, &token)) {
        alignas(TOKEN_MANDATORY_LABEL) BYTE buf[SECURITY_MAX_SID_SIZE + sizeof(TOKEN_MANDATORY_LABEL)];
        DWORD len;
        if (GetTokenInformation(token, TokenIntegrityLevel, buf, sizeof(buf), &len)) {
            PSID sid = ((TOKEN_MANDATORY_LABEL*)buf)->Label.Sid;
            level = (int)*GetSidSubAuthority(sid, *GetSidSubAuthorityCount(sid) - 1);
        }
        CloseHandle(token);
    }
    return level;
}

// Whether a window belongs to a process with a higher integrity level than this one (an administrator app such as
// Task Manager, an admin terminal or Windhawk itself): Windows sends this process no raw mouse input meanwhile.
static int g_ownIntegrity;   // set at start

static bool HigherRights(HWND w) {
    DWORD pid = 0;
    if (!w || !GetWindowThreadProcessId(w, &pid)) return false;
    HANDLE p = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!p) return true;
    int level = Integrity(p);
    CloseHandle(p);
    return level < 0 || level > g_ownIntegrity;
}

// ---- sampler ----

static DWORD WINAPI SampleThread(void*) {
    RECT monRect = {};          // the monitor the cursor is on
    HWND lastFront = nullptr;
    int pointerSize = 0;        // the pointer size set in Windows, at 100% scaling (0: not read yet)
    UINT mainDpi = 96;
    double mainPxPerCm = 0;     // pixel density of the main monitor (0: not measured yet)
    double hidePxPerCm = 38;    // turns the hide speed (cm/s on the main monitor) into px/s on the monitor in use
    LONGLONG lastMove = 0, lastFast = 0, lastDrawn = 0, lastLook = -1000, crossedAt = 0;
    bool paused = false, timerHigh = false, adminFront = false;
    bool fastEnough = false;    // above the minimum blur speed (switched only after 16 ms past the line)
    while (!g_stop) {
        // The window in front: whenever another window is activated (the shell hook says so, administrator windows
        // included), and every half second while the mouse moves, as an app can also go fullscreen in place.
        bool forced = g_recheck.exchange(false);
        LONGLONG t = Now();
        if (forced || t - lastLook >= 500) {
            lastLook = t;
            HWND front = GetForegroundWindow();
            bool frontChanged = front != lastFront;
            if (frontChanged) {
                lastFront = front;
                bool admin = HigherRights(front);
                if (admin != adminFront) Wh_Log(L"Administrator window in front: %d", admin);
                adminFront = admin;
            }
            // A fullscreen app: looked for when the front window changes, and while the mouse moves or the mod is
            // paused, as an app can also go fullscreen (or leave it) in place.
            if (forced || frontChanged || paused || t - lastMove < 1000) {
                bool was = paused;
                paused = g_userPaused || (g_pauseInFullscreen && FullscreenAppRunning());
                g_paused = paused;
                if (paused != was) {
                    Wh_Log(L"Paused (fullscreen app or tray): %d", paused);
                    // stop listening to the mouse during the game
                    if (g_wnd) PostMessageW(g_wnd, WM_APP_PAUSED, paused, 0);
                }
            }
        }
        if (paused) {
            EnterCriticalSection(&g_gate);
            g_curVisible = false;
            g_histN = 0;
            if (g_hideWanted) { g_hideWanted = false; SetEvent(g_hideChanged); }
            LeaveCriticalSection(&g_gate);
            if (timerHigh) { timeEndPeriod(1); timerHigh = false; }
            WaitForSingleObject(g_mouseWake, 500);
            continue;
        }

        CURSORINFO ci;
        ci.cbSize = sizeof(ci);
        bool showing = GetCursorInfo(&ci) && (ci.flags & CURSOR_SHOWING);
        // Crossing to another monitor (or display or cursor settings changed): measure it here, outside the lock, as
        // some of these calls are slow.
        bool stale = showing && g_monStale.exchange(false);
        bool newMon = showing && (stale || !PtInRect(&monRect, ci.ptScreenPos));
        int monCursor = 32;
        if (newMon) {
            HMONITOR mon = MonitorFromPoint(ci.ptScreenPos, MONITOR_DEFAULTTONEAREST);
            MONITORINFO mi;
            mi.cbSize = sizeof(mi);
            if (GetMonitorInfoW(mon, &mi)) monRect = mi.rcMonitor;
            UINT dpi = 96, dy;
            GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &dpi, &dy);
            if (stale || !pointerSize) pointerSize = PointerSize();
            monCursor = MulDiv(pointerSize, dpi, 96);
            int hz = RefreshRate(mon);
            // The hide speed is set in cm/s as measured on the main monitor. Windows moves the pointer further on a
            // monitor with more scaling (twice the pixels at 200%), so scale it by the DPI to hide at the same hand
            // speed on every monitor.
            if (stale || !mainPxPerCm) {
                POINT origin = {0, 0};
                HMONITOR mainMon = MonitorFromPoint(origin, MONITOR_DEFAULTTOPRIMARY);
                GetDpiForMonitor(mainMon, MDT_EFFECTIVE_DPI, &mainDpi, &dy);
                mainPxPerCm = PixelsPerCm(mainMon, mainDpi);
            }
            hidePxPerCm = mainPxPerCm * dpi / mainDpi;
            // Half a refresh: frames are not timed to the screen's refreshes, so a whole one would leave the blur
            // fresh on some refreshes and almost a refresh old on others, and it would jitter against the pointer.
            g_monGap = 500 / hz > 3 ? 500 / hz : 3;
        }

        EnterCriticalSection(&g_gate);
        if (!showing) {
            g_curVisible = false;
            g_histN = 0;
            if (g_hideWanted) { g_hideWanted = false; SetEvent(g_hideChanged); }
        } else {
            g_curVisible = true;
            if (!g_blankActive) g_curHandle = ci.hCursor;   // keep the real cursor's picture while it is hidden
            bool changed = g_histN == 0 || g_hist[g_histN - 1].x != ci.ptScreenPos.x ||
                           g_hist[g_histN - 1].y != ci.ptScreenPos.y;

            if (newMon) {   // drop the trail so it doesn't smear across the gap between monitors
                g_histN = 0;
                g_monCursor = monCursor;
            }

            LONGLONG now = Now();
            if (changed && g_histN && g_hist[g_histN - 1].t == now) {   // several reports within a ms: keep the newest
                g_hist[g_histN - 1].x = ci.ptScreenPos.x;
                g_hist[g_histN - 1].y = ci.ptScreenPos.y;
            } else if (changed || g_histN == 0 || now - g_hist[g_histN - 1].t >= 4) {
                if (g_histN == MAX_SAMPLES) {
                    memmove(g_hist, g_hist + 1, (MAX_SAMPLES - 1) * sizeof(Sample));
                    g_histN--;
                }
                g_hist[g_histN++] = {ci.ptScreenPos.x, ci.ptScreenPos.y, now};
            }
            if (changed) {
                if (now - lastMove >= 1000) lastLook = -1000;   // moving again: first see what is in front
                lastMove = now;
            }
            int drop = 0;
            while (g_histN - drop > 1 && now - g_hist[drop].t > g_trailMs) drop++;
            if (drop) {
                memmove(g_hist, g_hist + drop, (g_histN - drop) * sizeof(Sample));
                g_histN -= drop;
            }

            // Speed over the trail window: the blur is drawn above the draw speed and stops below half of it, each only
            // once the speed has stayed past that line for 16 ms (mouse reports arrive unevenly, so a single reading can
            // be a third off). The real cursor is hidden when very fast; bringing it back looks at only the last few ms
            // (from sample j on), so it returns as soon as the mouse stops or slows.
            LONGLONG dt = g_hist[g_histN - 1].t - g_hist[0].t;
            int j = g_histN - 1;
            while (j > 0 && now - g_hist[j - 1].t <= SHOW_WINDOW_MS) j--;
            double path = 0, recentPath = 0;
            for (int i = 1; i < g_histN; i++) {
                double d = Dist(g_hist[i - 1], g_hist[i]);
                path += d;
                if (i > j) recentPath += d;
            }
            double speed = dt >= 4 ? path * 1000.0 / dt : 0;
            double drawAt = g_drawSpeedCm * hidePxPerCm * (fastEnough ? 0.5 : 1);
            bool want = g_histN > 1 && (g_drawSpeedCm == 0 || (dt >= 4 && speed >= drawAt));
            if (want == fastEnough || g_histN < 2 || g_drawSpeedCm == 0) {
                crossedAt = 0;
                fastEnough = want;
            } else if (!crossedAt) {
                crossedAt = now;
            } else if (now - crossedAt >= 16) {
                crossedAt = 0;
                fastEnough = want;
            }
            bool wasHidden = g_hideWanted;
            if (!g_hideWhenFast || g_drawFailed) {
                g_hideWanted = false;
            } else if (dt >= 8) {
                double hide = g_hideSpeedCm * hidePxPerCm;   // px/s on this monitor, the same hand speed everywhere
                LONGLONG recentDt = now - g_hist[j].t;
                double recent = recentDt >= 4 ? recentPath * 1000.0 / recentDt : speed;
                if (speed > hide) {
                    g_hideWanted = true;
                    lastFast = now;
                } else if (g_hideWanted && recent < hide * 0.5 && now - lastFast > HOLD_MS) {
                    g_hideWanted = false;
                }
            }
            if (g_hideWanted && now - lastMove > HOLD_MS + SHOW_WINDOW_MS) g_hideWanted = false;   // stopped
            if (g_hideWanted != wasHidden) SetEvent(g_hideChanged);
            // The minimum blur speed only decides drawing; hiding goes by its own speed. A hidden cursor always gets its
            // blur, so the pointer never disappears.
            g_drawing = fastEnough || g_hideWanted;
            if ((changed || g_hideWanted != wasHidden) && g_drawing) {   // draw now
                lastDrawn = now;
                SetEvent(g_moved);
            } else if (changed && g_particles) {   // the particle trail follows every movement, at any speed
                SetEvent(g_moved);
            }
        }
        bool hidden = g_hideWanted;
        LeaveCriticalSection(&g_gate);

        // drawing (or the trail still fading), or the real cursor hidden: look often; below the draw speed, only on reports
        if (Now() - lastDrawn < g_trailMs + 40 || hidden) {
            if (!timerHigh) { timeBeginPeriod(1); timerHigh = true; }
            // look again on every mouse report; the timeout keeps the path ageing after a stop, and checks every 2 ms
            // while the real cursor is hidden so it comes back quickly
            WaitForSingleObject(g_mouseWake, hidden ? 2 : 10);
        } else {
            if (timerHigh) { timeEndPeriod(1); timerHigh = false; }
            // Sleep until the mouse moves or another window is activated; while an app hides the cursor, just look once
            // per report. While a window with more rights is in front no mouse reports arrive, so look at the cursor
            // every 10 ms instead, and every 100 ms once the mouse has been still for a second.
            if (fastEnough) {   // the trail has faded: the next movement starts below the minimum blur speed again
                fastEnough = false;
                g_drawing = false;
                crossedAt = 0;
            }
            DWORD poll = INFINITE;
            if (adminFront) poll = Now() - lastMove < 1000 ? 10 : 100;
            WaitForSingleObject(g_mouseWake, poll);
        }
    }
    if (timerHigh) timeEndPeriod(1);
    return 0;
}

// ---- hider ----

static DWORD WINAPI HideThread(void*) {
    // static system cursors blanked while the mouse is fast (the animated wait/app-starting ones are left alone)
    static const UINT ids[] = {32512, 32513, 32515, 32516, 32642, 32643, 32644,
                               32645, 32646, 32648, 32649, 32651, 32671, 32672};
    BYTE andMask[128], xorMask[128];
    memset(andMask, 0xFF, sizeof(andMask));
    memset(xorMask, 0, sizeof(xorMask));
    while (!g_stop) {
        EnterCriticalSection(&g_gate);
        bool want = g_hideWanted;
        HCURSOR cur = g_curHandle;
        LeaveCriticalSection(&g_gate);
        // Swap only once the blur has this cursor's picture: from the invisible one it can't be taken. The render thread
        // takes it on its next frame (a few ms) and wakes this thread.
        if (want && !g_blankActive && g_pictureOf == cur) {
            SetBlank(true);
            for (UINT id : ids) {
                HCURSOR c = CreateCursor(nullptr, 0, 0, 32, 32, andMask, xorMask);
                if (c && !SetSystemCursor(c, id)) DestroyCursor(c);   // on success the system owns it
            }
        } else if (!want && g_blankActive) {
            ReloadCursors();
            SetBlank(false);
        }
        WaitForSingleObject(g_hideChanged, INFINITE);
    }
    if (g_blankActive) {   // never leave the user with an invisible cursor
        ReloadCursors();
        SetBlank(false);
    }
    return 0;
}

// ---- cursor pictures (render thread only) ----

static struct { HCURSOR h; int size; Sprite* sp; } g_sprites[MAX_SPRITES];   // keyed by cursor and drawn size
static int g_nSprites, g_nextId;
// Cursors an app made invisible on purpose: no blur for them. Checked again after a while, because another tool that
// hides the cursor the way this mod does (swapping the system cursors) would otherwise switch the blur off for good.
static struct { HCURSOR h; LONGLONG t; } g_empties[MAX_SPRITES];
static int g_nEmpties;
static Sprite* g_lastSprite;             // the last real picture, drawn while the real cursor is hidden

// The standard cursors, with their names in the cursor scheme (HKCU\Control Panel\Cursors).
static const struct { WORD id; PCWSTR name; } kStandardCursors[] = {
    {32512, L"Arrow"},    {32513, L"IBeam"},    {32514, L"Wait"},     {32515, L"Crosshair"}, {32516, L"UpArrow"},
    {32631, L"NWPen"},    {32642, L"SizeNWSE"}, {32643, L"SizeNESW"}, {32644, L"SizeWE"},    {32645, L"SizeNS"},
    {32646, L"SizeAll"},  {32648, L"No"},       {32649, L"Hand"},     {32650, L"AppStarting"}, {32651, L"Help"},
    {32671, L"Pin"},      {32672, L"Person"},
};

// The cursor at size x size, for the caller to destroy: a standard cursor is loaded again from its scheme file (or from
// Windows' own cursors) at that size, so a large pointer stays sharp; any other is copied, enlarged if need be.
static HCURSOR AtSize(HCURSOR h, int size) {
    for (const auto& c : kStandardCursors) {
        if (LoadCursorW(nullptr, MAKEINTRESOURCEW(c.id)) != h) continue;
        WCHAR path[MAX_PATH];
        DWORD len = sizeof(path);
        HANDLE loaded = nullptr;
        if (RegGetValueW(HKEY_CURRENT_USER, L"Control Panel\\Cursors", c.name, RRF_RT_REG_SZ, nullptr, path, &len) ==
                ERROR_SUCCESS && path[0])
            loaded = LoadImageW(nullptr, path, IMAGE_CURSOR, size, size, LR_LOADFROMFILE);
        if (!loaded) loaded = LoadImageW(nullptr, MAKEINTRESOURCEW(c.id), IMAGE_CURSOR, size, size, 0);
        if (loaded) return (HCURSOR)loaded;
        break;
    }
    return (HCURSOR)CopyImage(h, IMAGE_CURSOR, size, size, 0);
}

// A cursor's picture size and hotspot.
static bool CursorInfo(HCURSOR h, int* w, int* ht, POINT* hot) {
    ICONINFO ii;
    if (!GetIconInfo(h, &ii)) return false;
    BITMAP bm = {};
    GetObjectW(ii.hbmColor ? ii.hbmColor : ii.hbmMask, sizeof(bm), &bm);
    *w = bm.bmWidth;
    *ht = ii.hbmColor ? bm.bmHeight : bm.bmHeight / 2;   // a monochrome mask holds AND and XOR halves
    *hot = {(LONG)ii.xHotspot, (LONG)ii.yHotspot};
    if (ii.hbmColor) DeleteObject(ii.hbmColor);
    if (ii.hbmMask) DeleteObject(ii.hbmMask);
    return true;
}

// Takes the cursor's picture by drawing it on black and on white: what shows through gives the opacity. It is taken at
// the size it will be drawn (up to 256 px): the cursor as it is when that is its size, else a copy at that size.
static Sprite* Grab(HCURSOR h, int size, bool* empty) {
    *empty = false;
    if (size > 256) size = 256;
    int w, ht;
    POINT hot;
    if (!CursorInfo(h, &w, &ht, &hot)) return nullptr;
    HCURSOR sized = w != size ? AtSize(h, size) : nullptr;
    if (sized && CursorInfo(sized, &w, &ht, &hot)) h = sized;
    if (w <= 0 || ht <= 0 || w > 256 || ht > 256) {
        if (sized) DestroyCursor(sized);
        return nullptr;
    }

    int n = w * ht;
    BITMAPINFO bi = {};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -ht, 1, 32, BI_RGB, 0, 0, 0, 0, 0};
    void* bits;
    HDC dc = CreateCompatibleDC(nullptr);
    HBITMAP dib = dc ? CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0) : nullptr;
    Sprite* sp = dib ? (Sprite*)malloc(sizeof(Sprite) + n * 4) : nullptr;
    if (sp) {
        HGDIOBJ old = SelectObject(dc, dib);
        UINT32 *px = (UINT32*)(sp + 1), *onWhite = (UINT32*)bits;
        memset(bits, 0, n * 4);
        DrawIconEx(dc, 0, 0, h, w, ht, 0, nullptr, DI_NORMAL);
        GdiFlush();
        memcpy(px, bits, n * 4);   // on black
        memset(bits, 0xFF, n * 4);
        DrawIconEx(dc, 0, 0, h, w, ht, 0, nullptr, DI_NORMAL);
        GdiFlush();
        bool any = false;
        for (int i = 0; i < n; i++) {
            UINT32 b = px[i];
            // how much of the background shows through
            int a = 255 - ((int)(onWhite[i] >> 8 & 255) - (int)(b >> 8 & 255));
            a = Clamp(a, 0, 255);
            // on black = premultiplied colour
            UINT32 r = b >> 16 & 255, g = b >> 8 & 255, bl = b & 255, ua = (UINT32)a;
            px[i] = ua << 24 | (r < ua ? r : ua) << 16 | (g < ua ? g : ua) << 8 | (bl < ua ? bl : ua);
            any |= a != 0;
        }
        SelectObject(dc, old);
        *sp = {w, ht, (int)hot.x, (int)hot.y, ++g_nextId, px};
        if (!any) { free(sp); sp = nullptr; *empty = true; }
    }
    if (dib) DeleteObject(dib);
    if (dc) DeleteDC(dc);
    if (sized) DestroyCursor(sized);
    return sp;
}

static void FreeSprites() {
    for (int i = 0; i < g_nSprites; i++) free(g_sprites[i].sp);
    g_nSprites = g_nEmpties = 0;
    g_lastSprite = nullptr;
}

static bool IsEmpty(HCURSOR h) {
    for (int i = 0; i < g_nEmpties; i++)
        if (g_empties[i].h == h) {
            if (Now() - g_empties[i].t < 2000) return true;
            g_empties[i] = g_empties[--g_nEmpties];   // look at it again
            return false;
        }
    return false;
}

static Sprite* GetSprite(HCURSOR h, int size) {
    for (int i = 0; i < g_nSprites; i++)
        if (g_sprites[i].h == h && g_sprites[i].size == size) return g_sprites[i].sp;
    if (IsEmpty(h)) return nullptr;
    bool hiddenBefore = g_blankActive, empty;
    Sprite* sp = Grab(h, size, &empty);
    // Only keep a picture taken while the real cursor is showing: blanking replaces the content under the same handle.
    if (sp && g_blankActive) { free(sp); sp = nullptr; }
    if (sp) {
        if (g_nSprites == MAX_SPRITES) FreeSprites();
        g_sprites[g_nSprites++] = {h, size, sp};
    }
    // Empty while our own blanking was off the whole time: the app itself shows an invisible cursor.
    if (empty && !hiddenBefore && !g_blankActive) {
        if (g_nEmpties == MAX_SPRITES) g_nEmpties = 0;
        g_empties[g_nEmpties++] = {h, Now()};
    }
    return sp;
}

// ---- drawing (render thread only) ----


static HDC g_memDc;
static HBITMAP g_dib;
static HGDIOBJ g_dibOld;
// the canvas: premultiplied BGRA, top-down, g_canvasW wide; frames use its top-left corner
static UINT32* g_bits;
static int g_canvasW, g_canvasH;
static UINT32* g_pic;          // the cursor picture at the drawn size
static int* g_span;            // per row of g_pic: first and one-past-last visible pixel
static int g_picId, g_picW, g_picH;
static bool g_shown;

static void ReleaseCanvas() {
    if (g_dib) {
        SelectObject(g_memDc, g_dibOld);
        DeleteObject(g_dib);
        g_dib = nullptr;
    }
    g_canvasW = g_canvasH = 0;
}

static void EnsureCanvas(int w, int h) {   // grows only, in 128 px steps
    if (g_dib && w <= g_canvasW && h <= g_canvasH) return;
    int nw = (w + 127) / 128 * 128, nh = (h + 127) / 128 * 128;
    if (nw < g_canvasW) nw = g_canvasW;
    if (nh < g_canvasH) nh = g_canvasH;
    ReleaseCanvas();
    BITMAPINFO bi = {};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), nw, -nh, 1, 32, BI_RGB, 0, 0, 0, 0, 0};
    g_dib = CreateDIBSection(g_memDc, &bi, DIB_RGB_COLORS, (void**)&g_bits, nullptr, 0);
    if (!g_dib) return;
    g_dibOld = SelectObject(g_memDc, g_dib);
    g_canvasW = nw;
    g_canvasH = nh;
}

// One pixel of the cursor picture resized to w x h, on premultiplied colours: the average of the pixels it covers when
// shrinking, bilinear when growing.
static UINT32 Pixel(const Sprite* sp, int x, int y, int w, int h) {
    float acc[4] = {}, n = 0;
    if (sp->w > w) {
        int x0 = x * sp->w / w, x1 = (x + 1) * sp->w / w, y0 = y * sp->h / h, y1 = (y + 1) * sp->h / h;
        if (x1 <= x0) x1 = x0 + 1;
        if (y1 <= y0) y1 = y0 + 1;
        for (int yy = y0; yy < y1; yy++)
            for (int xx = x0; xx < x1; xx++, n++)
                for (int s = 0; s < 4; s++) acc[s] += sp->px[yy * sp->w + xx] >> (8 * s) & 255;
    } else {
        float fx = (x + 0.5f) * sp->w / w - 0.5f, fy = (y + 0.5f) * sp->h / h - 0.5f;
        if (fx < 0) fx = 0;
        if (fy < 0) fy = 0;
        int x0 = (int)fx, y0 = (int)fy, x1 = x0 + 1 < sp->w ? x0 + 1 : x0, y1 = y0 + 1 < sp->h ? y0 + 1 : y0;
        float ax = fx - x0, ay = fy - y0, wt[4] = {(1 - ax) * (1 - ay), ax * (1 - ay), (1 - ax) * ay, ax * ay};
        UINT32 p[4] = {sp->px[y0 * sp->w + x0], sp->px[y0 * sp->w + x1],
                       sp->px[y1 * sp->w + x0], sp->px[y1 * sp->w + x1]};
        for (int i = 0; i < 4; i++)
            for (int s = 0; s < 4; s++) acc[s] += (p[i] >> (8 * s) & 255) * wt[i];
        n = 1;
    }
    UINT32 out = 0;
    for (int s = 0; s < 4; s++) out |= (UINT32)(acc[s] / n + 0.5f) << (8 * s);
    return out;
}

// The cursor picture at the drawn size, made again only when the cursor or the size changes.
static bool Resize(const Sprite* sp, int w, int h) {
    if (g_pic && g_picId == sp->id && g_picW == w && g_picH == h) return true;
    free(g_pic);
    g_pic = (UINT32*)malloc(w * h * 4 + h * 2 * sizeof(int));
    if (!g_pic) return false;
    g_span = (int*)(g_pic + w * h);
    g_picId = sp->id;
    g_picW = w;
    g_picH = h;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            g_pic[y * w + x] = w == sp->w && h == sp->h ? sp->px[y * w + x] : Pixel(sp, x, y, w, h);
    // most of a cursor is transparent: blending only touches the visible part of each row
    for (int y = 0; y < h; y++) {
        int a = 0, b = w;
        while (a < w && !g_pic[y * w + a]) a++;
        while (b > a && !g_pic[y * w + b - 1]) b--;
        g_span[2 * y] = a;
        g_span[2 * y + 1] = b;
    }
    return true;
}

// Draws the picture at (ox, oy) at opacity a (1-255): premultiplied "source over", two channels per multiplication.
static void Blend(int a, int ox, int oy) {
    UINT32 k = (UINT32)a + 1;   // 2-256, so full opacity is exact
    for (int y = 0; y < g_picH; y++) {
        UINT32* row = g_bits + (oy + y) * g_canvasW + ox;
        const UINT32* src = g_pic + y * g_picW;
        for (int x = g_span[2 * y]; x < g_span[2 * y + 1]; x++) {
            UINT32 s = src[x];
            if (!s) continue;
            s = ((s & 0xFF00FF) * k >> 8 & 0xFF00FF) | ((s >> 8 & 0xFF00FF) * k & 0xFF00FF00);
            UINT32 inv = 256 - (s >> 24), d = row[x];
            row[x] = s + (((d & 0xFF00FF) * inv >> 8 & 0xFF00FF) | ((d >> 8 & 0xFF00FF) * inv & 0xFF00FF00));
        }
    }
}

#define BAND_CLASS L"PointerAfterimagePlusBand"
#define OVERLAY_CLASS L"PointerAfterimagePlus"
static HWND g_band;     // the overlay explorer.exe made above the Start menu, if there is one
static HWND g_target;   // the window the blur is drawn in: g_band, else this process's own

static HWND g_bandFailed;   // a window of explorer's that could not be drawn in

// The shell explorer.exe's window above the Start menu (looked up afresh, so a reused handle is never drawn in).
static HWND FindBand() {
    DWORD shell = 0;
    if (HWND s = GetShellWindow()) GetWindowThreadProcessId(s, &shell);
    for (HWND b = FindWindowExW(nullptr, nullptr, BAND_CLASS, nullptr); b; b = FindWindowExW(nullptr, b, BAND_CLASS, nullptr)) {
        DWORD owner = 0;
        if (b != g_bandFailed && GetWindowThreadProcessId(b, &owner) && (!shell || owner == shell)) return b;
    }
    return nullptr;
}

// Shows or hides the window drawn in. g_band belongs to explorer.exe, so this doesn't wait for it to answer.
static void ShowTarget(bool show) {
    SetWindowPos(g_target, HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS |
                     (show ? SWP_SHOWWINDOW : SWP_HIDEWINDOW | SWP_NOZORDER));
}

// ---- particle trail and click ripples (render thread only) ----
// Small glowing dots dropped along the path the pointer travels, and a ring that grows and fades at each press of the
// left or right button. Both live in fixed pools and are drawn in the same overlay as the blur; once the last one has
// faded the overlay hides as before. The look follows MCheng404's Mouse Trail mod; the code is written for this renderer.

#define MAX_PARTICLES 256
#define MAX_RIPPLES   16
#define EMIT_BUDGET   48      // the most dots one frame adds
#define JUMP_PX       600.0   // a step longer than this (times the effect scale) is a jump, not a path: no dots across it

struct Particle { float x, y, vx, vy, r; LONGLONG born; BYTE c[3]; };
struct Ripple { int x, y; LONGLONG born; };

static Particle g_part[MAX_PARTICLES];
static int g_partN;
static Ripple g_ring[MAX_RIPPLES];
static int g_ringN;
static Sample g_emitFrom;     // where the particle trail last left off
static bool g_emitHave;
static double g_emitCarry;    // px travelled since the last dot
static UINT32 g_rng = 2463534242u;

static const BYTE kBlue[3] = {0x89, 0xB4, 0xFA}, kMauve[3] = {0xCB, 0xA6, 0xF7};   // Catppuccin Mocha, as R G B

static float Rand01() {   // xorshift32, 0 to 1
    g_rng ^= g_rng << 13;
    g_rng ^= g_rng >> 17;
    g_rng ^= g_rng << 5;
    return (g_rng >> 8) / 16777216.0f;
}

static void MixColor(float t, BYTE* out) {   // 0 blue, 1 mauve
    for (int i = 0; i < 3; i++) out[i] = (BYTE)(kBlue[i] + (kMauve[i] - kBlue[i]) * t + 0.5f);
}

// Effects grow with the pointer on screen: display scaling and the pointer size, up to three times.
static double FxScale(int monCursor) {
    double s = monCursor / 32.0;
    return s < 1 ? 1 : s > 3 ? 3 : s;
}

static void ClearEffects() {
    g_partN = g_ringN = 0;
    g_emitHave = false;
    g_emitCarry = 0;
}

static void AddParticle(float x, float y, LONGLONG born, double scale) {
    if (g_partN == MAX_PARTICLES) {   // full: the oldest dot goes first
        memmove(g_part, g_part + 1, (MAX_PARTICLES - 1) * sizeof(Particle));
        g_partN--;
    }
    Particle& p = g_part[g_partN++];
    float r = (float)(g_pSize * scale), ang = Rand01() * 6.2831853f, speed = (8 + Rand01() * 22) * (float)scale;
    p.x = x + (Rand01() - 0.5f) * r * 1.5f;
    p.y = y + (Rand01() - 0.5f) * r * 1.5f;
    p.vx = cosf(ang) * speed;   // a slow drift, in px/s
    p.vy = sinf(ang) * speed;
    p.r = r * (0.7f + Rand01() * 0.6f);
    p.born = born;
    int mode = g_pColor;
    // blue to mauve: the colour sweeps slowly back and forth over two seconds, so a stroke has one shade along it
    float sweep = fabsf((float)(born % 2000) / 1000.0f - 1.0f);
    float t = mode == 1 ? 0.0f : mode == 2 ? 1.0f : sweep * 0.8f + Rand01() * 0.2f;
    MixColor(t, p.c);
}

// Drops dots along the path since the last frame, one every (50 / amount) px.
static void EmitParticles(const Sample* pts, int np, double scale) {
    double spacing = 50.0 / g_pAmount * scale;
    int budget = EMIT_BUDGET;
    for (int i = 0; i < np; i++) {
        Sample b = pts[i];
        if (g_emitHave && (b.t < g_emitFrom.t || (b.x == g_emitFrom.x && b.y == g_emitFrom.y))) continue;
        if (!g_emitHave) {
            g_emitFrom = b;
            g_emitHave = true;
            g_emitCarry = 0;
            continue;
        }
        Sample a = g_emitFrom;
        g_emitFrom = b;
        double d = Dist(a, b);
        if (d > JUMP_PX * scale) {
            g_emitCarry = 0;
            continue;
        }
        LONGLONG at = b.t - a.t > 50 ? b.t - 8 : a.t;   // the first step after a rest: born now, not when it stopped
        double s = spacing - g_emitCarry;
        for (; s <= d && budget > 0; s += spacing, budget--) {
            double f = s / d;
            AddParticle((float)(a.x + (b.x - a.x) * f), (float)(a.y + (b.y - a.y) * f), at + (LONGLONG)((b.t - at) * f),
                        scale);
        }
        g_emitCarry = s <= d ? 0 : d - (s - spacing);
    }
}

static void AddRipple(int x, int y) {
    if (g_ringN == MAX_RIPPLES) {
        memmove(g_ring, g_ring + 1, (MAX_RIPPLES - 1) * sizeof(Ripple));
        g_ringN--;
    }
    g_ring[g_ringN++] = {x, y, Now()};
}

// Drops what has faded. Elapsed time comes from the clock, so a frame that arrives late just shows a later moment.
static void AgeEffects(LONGLONG now) {
    int life = g_pLifeMs, k = 0;
    for (int i = 0; i < g_partN; i++)
        if (now - g_part[i].born < life) g_part[k++] = g_part[i];
    g_partN = k;
    int ms = g_rMs;
    k = 0;
    for (int i = 0; i < g_ringN; i++)
        if (now - g_ring[i].born < ms) g_ring[k++] = g_ring[i];
    g_ringN = k;
}

// One dot now: place, radius and opacity.
static void ParticleAt(const Particle& p, LONGLONG now, float* x, float* y, float* r, float* a) {
    float age = (float)(now - p.born), u = age / g_pLifeMs;
    if (u < 0) u = 0;
    if (u > 1) u = 1;
    float sec = age / 1000.0f * (1 - 0.5f * u);   // the drift slows as it fades
    *x = p.x + p.vx * sec;
    *y = p.y + p.vy * sec;
    *r = p.r * (1 - 0.55f * u);
    *a = powf(1 - u, 1.5f) * 0.85f;
}

// One ring now: radius, stroke width and opacity. It eases out: fast at first, settling as it fades.
static void RippleAt(const Ripple& q, LONGLONG now, double scale, float* r, float* stroke, float* a) {
    float u = (float)(now - q.born) / g_rMs;
    if (u < 0) u = 0;
    if (u > 1) u = 1;
    float e = 1 - (1 - u) * (1 - u) * (1 - u);
    float r0 = (float)(3 * scale), r1 = (float)(g_rSize * scale / 2);
    *r = r0 + (r1 - r0) * e;
    *stroke = (float)(2 * scale) * (1 - 0.4f * u);
    *a = (1 - u) * (1 - u) * 0.9f;
}

// Widens box (screen pixels, right and bottom exclusive) to hold every dot and ring.
static void EffectBounds(LONGLONG now, double scale, RECT* box) {
    auto add = [&](float cx, float cy, float rad) {
        int l = (int)floorf(cx - rad) - 1, t = (int)floorf(cy - rad) - 1;
        int r = (int)ceilf(cx + rad) + 2, b = (int)ceilf(cy + rad) + 2;
        if (l < box->left) box->left = l;
        if (t < box->top) box->top = t;
        if (r > box->right) box->right = r;
        if (b > box->bottom) box->bottom = b;
    };
    for (int i = 0; i < g_partN; i++) {
        float x, y, r, a;
        ParticleAt(g_part[i], now, &x, &y, &r, &a);
        add(x, y, r * 2.2f);   // the glow around the dot
    }
    float maxR = (float)(g_rSize * scale / 2 + 2 * scale);
    for (int i = 0; i < g_ringN; i++) add((float)g_ring[i].x, (float)g_ring[i].y, maxR);
}

// GDI: one pixel of a straight colour at opacity a, premultiplied source over.
static void PutPx(UINT32* px, const BYTE* c, float a) {
    if (a <= 0.002f) return;
    if (a > 1) a = 1;
    UINT32 d = *px;
    float inv = 1 - a;
    UINT32 A = (UINT32)(a * 255 + (d >> 24) * inv + 0.5f);
    UINT32 R = (UINT32)(c[0] * a + (d >> 16 & 255) * inv + 0.5f);
    UINT32 G = (UINT32)(c[1] * a + (d >> 8 & 255) * inv + 0.5f);
    UINT32 B = (UINT32)(c[2] * a + (d & 255) * inv + 0.5f);
    *px = (A > 255 ? 255 : A) << 24 | (R > 255 ? 255 : R) << 16 | (G > 255 ? 255 : G) << 8 | (B > 255 ? 255 : B);
}

// GDI: an antialiased filled circle (ring = false) or ring of half-width half at (cx, cy) in frame pixels. A ring's
// colour runs blue to mauve from its top left to its bottom right.
static void GdiCircle(UINT32* bits, int stride, int w, int h, float cx, float cy, float r, float half, float a,
                      const BYTE* c, bool ring) {
    float ext = ring ? r + half + 1 : r + 1;
    int x0 = (int)floorf(cx - ext), x1 = (int)ceilf(cx + ext), y0 = (int)floorf(cy - ext), y1 = (int)ceilf(cy + ext);
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > w) x1 = w;
    if (y1 > h) y1 = h;
    BYTE grad[3];
    for (int y = y0; y < y1; y++) {
        for (int x = x0; x < x1; x++) {
            float dx = x + 0.5f - cx, dy = y + 0.5f - cy, d = sqrtf(dx * dx + dy * dy);
            float cov = ring ? half + 0.5f - fabsf(d - r) : r + 0.5f - d;
            if (cov <= 0) continue;
            if (cov > 1) cov = 1;
            const BYTE* col = c;
            if (ring) {
                float t = (dx + dy) / (2.83f * (r > 1 ? r : 1)) + 0.5f;
                MixColor(t < 0 ? 0 : t > 1 ? 1 : t, grad);
                col = grad;
            }
            PutPx(bits + y * stride + x, col, a * cov);
        }
    }
}

// GDI: every dot and ring into the canvas, whose top left is (ox, oy) on the screen.
static void DrawEffectsGdi(UINT32* bits, int stride, int w, int h, int ox, int oy, LONGLONG now, double scale) {
    for (int i = 0; i < g_partN; i++) {
        float x, y, r, a;
        ParticleAt(g_part[i], now, &x, &y, &r, &a);
        GdiCircle(bits, stride, w, h, x - ox, y - oy, r * 2.2f, 0, a * 0.22f, g_part[i].c, false);
        GdiCircle(bits, stride, w, h, x - ox, y - oy, r, 0, a, g_part[i].c, false);
    }
    for (int i = 0; i < g_ringN; i++) {
        float r, stroke, a;
        RippleAt(g_ring[i], now, scale, &r, &stroke, &a);
        GdiCircle(bits, stride, w, h, (float)(g_ring[i].x - ox), (float)(g_ring[i].y - oy), r, stroke / 2, a, kBlue, true);
    }
}


// ---- GPU renderer (render thread only) ----
// The overlay is a click-through window (transparent, layered and answering HTTRANSPARENT) with a DirectComposition
// target and no redirection bitmap: it is never drawn with UpdateLayeredWindow. It covers the whole virtual screen and never moves or resizes between frames: a frame draws
// the copies with Direct2D into a virtual surface and sets the visual's offset, and one Commit makes both appear
// together. Nothing is drawn while the pointer is idle (the window is hidden). The fade is part of each frame because
// every frame has a new shape, so there is nothing for a compositor animation to run on.

static bool g_gpuArmed;        // the overlay window is a DirectComposition one
static int g_requested = -1;   // the renderer setting the overlay was last built for

static struct {
    ID3D11Device* d3d;
    ID2D1Factory1* factory;
    ID2D1Device* d2d;
    IDCompositionDevice* dev;
    IDCompositionTarget* target;
    IDCompositionVisual* visual;
    IDCompositionVirtualSurface* surf;
    int surfW, surfH;
    ID2D1Bitmap* bmp;          // the cursor picture at the drawn size
    int bmpId, bmpW, bmpH;
    int vx, vy, vw, vh;        // the window rectangle last set
    ID2D1SolidColorBrush* dot;            // particle fill
    ID2D1GradientStopCollection* stops;   // blue to mauve
    ID2D1LinearGradientBrush* ring;       // ripple stroke
} g_gpu;

template <class T>
static void Rel(T*& p) {
    if (p) {
        p->Release();
        p = nullptr;
    }
}

static void GpuShutdown() {
    Rel(g_gpu.ring);
    Rel(g_gpu.stops);
    Rel(g_gpu.dot);
    Rel(g_gpu.bmp);
    Rel(g_gpu.surf);
    Rel(g_gpu.visual);
    Rel(g_gpu.target);
    Rel(g_gpu.dev);
    Rel(g_gpu.d2d);
    Rel(g_gpu.factory);
    Rel(g_gpu.d3d);
    g_gpu = {};
}

static bool GpuInit(HWND wnd) {
    HRESULT hr;
    D3D_FEATURE_LEVEL level;
    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0,
                           D3D11_SDK_VERSION, &g_gpu.d3d, &level, nullptr);
    if (FAILED(hr))
        hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0,
                               D3D11_SDK_VERSION, &g_gpu.d3d, &level, nullptr);
    if (FAILED(hr)) {
        Wh_Log(L"GpuInit: D3D11CreateDevice failed 0x%08lX", (unsigned long)hr);
        GpuShutdown();
        return false;
    }
    IDXGIDevice* dxgi = nullptr;
    if (FAILED(g_gpu.d3d->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi)) || !dxgi) {
        Wh_Log(L"GpuInit: no IDXGIDevice");
        GpuShutdown();
        return false;
    }
    D2D1_FACTORY_OPTIONS opts = {};
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &opts, (void**)&g_gpu.factory);
    if (SUCCEEDED(hr) && g_gpu.factory) hr = g_gpu.factory->CreateDevice(dxgi, &g_gpu.d2d);
    dxgi->Release();
    if (FAILED(hr) || !g_gpu.d2d) {
        Wh_Log(L"GpuInit: Direct2D failed 0x%08lX", (unsigned long)hr);
        GpuShutdown();
        return false;
    }
    HMODULE dcomp = LoadLibraryW(L"dcomp.dll");
    using CreateDevice2_t = HRESULT(WINAPI*)(IUnknown*, REFIID, void**);
    auto createDevice = dcomp ? (CreateDevice2_t)GetProcAddress(dcomp, "DCompositionCreateDevice2") : nullptr;
    if (!createDevice) {
        Wh_Log(L"GpuInit: no DCompositionCreateDevice2");
        GpuShutdown();
        return false;
    }
    hr = createDevice(g_gpu.d2d, __uuidof(IDCompositionDevice), (void**)&g_gpu.dev);
    if (FAILED(hr) || !g_gpu.dev) {
        Wh_Log(L"GpuInit: DCompositionCreateDevice2 failed 0x%08lX", (unsigned long)hr);
        GpuShutdown();
        return false;
    }
    hr = g_gpu.dev->CreateTargetForHwnd(wnd, TRUE, &g_gpu.target);
    if (SUCCEEDED(hr)) hr = g_gpu.dev->CreateVisual(&g_gpu.visual);
    if (SUCCEEDED(hr))
        hr = g_gpu.dev->CreateVirtualSurface(128, 128, DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ALPHA_MODE_PREMULTIPLIED,
                                             &g_gpu.surf);
    if (FAILED(hr) || !g_gpu.target || !g_gpu.visual || !g_gpu.surf) {
        Wh_Log(L"GpuInit: target, visual or surface failed 0x%08lX", (unsigned long)hr);
        GpuShutdown();
        return false;
    }
    g_gpu.surfW = g_gpu.surfH = 128;
    g_gpu.visual->SetContent(g_gpu.surf);
    g_gpu.target->SetRoot(g_gpu.visual);
    if (FAILED(g_gpu.dev->Commit())) {
        Wh_Log(L"GpuInit: first Commit failed");
        GpuShutdown();
        return false;
    }
    return true;
}

// Every dot and ring, under the blur. The brushes belong to the Direct2D device, so they outlive this one draw.
static bool DrawEffectsGpu(ID2D1DeviceContext* dc, int ox, int oy, LONGLONG now, double scale) {
    ID2D1RenderTarget* ctx = dc;   // the plain overloads: the device context hides some of them
    if (!g_gpu.dot) {
        D2D1_COLOR_F white = {1, 1, 1, 1};
        if (FAILED(ctx->CreateSolidColorBrush(&white, nullptr, &g_gpu.dot))) return false;
    }
    if (!g_gpu.ring) {
        D2D1_GRADIENT_STOP st[2] = {{0, {kBlue[0] / 255.0f, kBlue[1] / 255.0f, kBlue[2] / 255.0f, 1}},
                                    {1, {kMauve[0] / 255.0f, kMauve[1] / 255.0f, kMauve[2] / 255.0f, 1}}};
        if (!g_gpu.stops && FAILED(ctx->CreateGradientStopCollection(st, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &g_gpu.stops))) return false;
        D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES lp = {{0, 0}, {1, 1}};
        if (FAILED(ctx->CreateLinearGradientBrush(&lp, nullptr, g_gpu.stops, &g_gpu.ring))) return false;
    }
    for (int i = 0; i < g_partN; i++) {
        float x, y, r, a;
        ParticleAt(g_part[i], now, &x, &y, &r, &a);
        const BYTE* c = g_part[i].c;
        D2D1_COLOR_F col = {c[0] / 255.0f, c[1] / 255.0f, c[2] / 255.0f, a * 0.22f};
        D2D1_ELLIPSE e = {{x - ox, y - oy}, r * 2.2f, r * 2.2f};
        g_gpu.dot->SetColor(&col);
        ctx->FillEllipse(&e, g_gpu.dot);
        col.a = a;
        e.radiusX = e.radiusY = r;
        g_gpu.dot->SetColor(&col);
        ctx->FillEllipse(&e, g_gpu.dot);
    }
    for (int i = 0; i < g_ringN; i++) {
        float r, stroke, a;
        RippleAt(g_ring[i], now, scale, &r, &stroke, &a);
        float cx = (float)(g_ring[i].x - ox), cy = (float)(g_ring[i].y - oy);
        g_gpu.ring->SetStartPoint({cx - r, cy - r});
        g_gpu.ring->SetEndPoint({cx + r, cy + r});
        g_gpu.ring->SetOpacity(a);
        D2D1_ELLIPSE e = {{cx, cy}, r, r};
        ctx->DrawEllipse(&e, g_gpu.ring, stroke, nullptr);
    }
    return true;
}

// One frame: clears the surface, draws the effects, then every copy 1:1 at its opacity (premultiplied source over, like
// the GDI blend), moves the visual to the frame's place on the screen and commits. False on any failure (the caller falls
// back to GDI).
static bool DrawGpu(int sw, int sh, const Copy* c, int n, int x, int y, int w, int h, LONGLONG now, double scale) {
    int vx = GetSystemMetrics(SM_XVIRTUALSCREEN), vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int vw = GetSystemMetrics(SM_CXVIRTUALSCREEN), vh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    if (!g_gpu.surf || vw <= 0 || vh <= 0 || w <= 0 || h <= 0) return false;
    if (!g_shown || vx != g_gpu.vx || vy != g_gpu.vy || vw != g_gpu.vw || vh != g_gpu.vh) {
        SetWindowPos(g_wnd, HWND_TOPMOST, vx, vy, vw, vh, SWP_NOACTIVATE);
        g_gpu.vx = vx;
        g_gpu.vy = vy;
        g_gpu.vw = vw;
        g_gpu.vh = vh;
    }
    if (w > g_gpu.surfW || h > g_gpu.surfH) {   // grows only, in 128 px steps
        int nw = (w + 127) / 128 * 128, nh = (h + 127) / 128 * 128;
        if (nw < g_gpu.surfW) nw = g_gpu.surfW;
        if (nh < g_gpu.surfH) nh = g_gpu.surfH;
        if (FAILED(g_gpu.surf->Resize(nw, nh))) return false;
        g_gpu.surfW = nw;
        g_gpu.surfH = nh;
    }

    RECT rc = {0, 0, w, h};
    POINT off = {};
    ID2D1DeviceContext* ctx = nullptr;
    if (FAILED(g_gpu.surf->BeginDraw(&rc, __uuidof(ID2D1DeviceContext), (void**)&ctx, &off)) || !ctx) return false;
    D2D1_MATRIX_3X2_F move = {};
    move._11 = 1;
    move._22 = 1;
    move._31 = (float)off.x;
    move._32 = (float)off.y;
    ctx->SetTransform(move);
    D2D1_RECT_F clip = {0, 0, (float)w, (float)h};
    ctx->PushAxisAlignedClip(clip, D2D1_ANTIALIAS_MODE_ALIASED);
    D2D1_COLOR_F clear = {0, 0, 0, 0};
    ctx->Clear(&clear);
    bool ok = !(g_partN || g_ringN) || DrawEffectsGpu(ctx, x, y, now, scale);
    if (ok && n && (!g_gpu.bmp || g_gpu.bmpId != g_picId || g_gpu.bmpW != g_picW || g_gpu.bmpH != g_picH)) {
        Rel(g_gpu.bmp);
        D2D1_BITMAP_PROPERTIES props = {{DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED}, 96.0f, 96.0f};
        if (SUCCEEDED(ctx->CreateBitmap(D2D1_SIZE_U{(UINT32)g_picW, (UINT32)g_picH}, g_pic, (UINT32)g_picW * 4, props,
                                        &g_gpu.bmp))) {
            g_gpu.bmpId = g_picId;
            g_gpu.bmpW = g_picW;
            g_gpu.bmpH = g_picH;
        } else {
            ok = false;
        }
    }
    if (ok) {
        for (int i = 0; i < n; i++) {
            int a = (int)(c[i].a * 255 + 0.5f);
            if (a > 0 && c[i].x >= 0 && c[i].y >= 0 && c[i].x + sw <= w && c[i].y + sh <= h) {
                D2D1_RECT_F dst = {(float)c[i].x, (float)c[i].y, (float)(c[i].x + sw), (float)(c[i].y + sh)};
                ctx->DrawBitmap(g_gpu.bmp, &dst, a / 255.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, nullptr);
            }
        }
    }
    ctx->PopAxisAlignedClip();
    ctx->Release();
    HRESULT hr = g_gpu.surf->EndDraw();
    if (!ok || FAILED(hr)) return false;
    // The surface only grows, so pixels left over from a larger earlier frame sit outside this frame's rectangle: drop
    // them and clip the visual, or old trail pieces show around the new one.
    g_gpu.surf->Trim(&rc, 1);
    D2D_RECT_F vis = {0, 0, (float)w, (float)h};
    g_gpu.visual->SetClip(vis);
    g_gpu.visual->SetOffsetX((float)(x - vx));
    g_gpu.visual->SetOffsetY((float)(y - vy));
    if (FAILED(g_gpu.dev->Commit())) return false;
    if (!g_shown) {   // the surface is in place: show the window
        g_target = g_wnd;
        ShowTarget(true);
        g_shown = true;
    }
    return true;
}

static void FallbackToGdi(const WCHAR* why);   // below, with the window code

static bool DrawGdi(int sw, int sh, const Copy* c, int n, int x, int y, int w, int h, LONGLONG now, double scale) {
    EnsureCanvas(w, h);
    if (!g_dib) return false;
    for (int r = 0; r < h; r++) memset(g_bits + r * g_canvasW, 0, w * 4);
    if (g_partN || g_ringN) DrawEffectsGdi(g_bits, g_canvasW, w, h, x, y, now, scale);
    for (int i = 0; i < n; i++) {
        int a = (int)(c[i].a * 255 + 0.5f);
        if (a > 0 && c[i].x >= 0 && c[i].y >= 0 && c[i].x + sw <= w && c[i].y + sh <= h) Blend(a, c[i].x, c[i].y);
    }
    // The window is resized to every frame: keeping its size and only moving it is a little cheaper, but Windows can then
    // show the move a frame before the new picture, and the blur jitters.
    POINT dst = {x, y}, src = {0, 0};
    SIZE size = {w, h};
    BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    if (!g_shown) {   // a new stretch of movement: draw in explorer's window if it has one
        static HWND watching;
        g_band = FindBand();
        if (g_band && g_band != watching) {   // explorer hides its window as soon as this process ends, however
            PostMessageW(g_band, WM_APP_WATCH, GetCurrentProcessId(), 0);
            watching = g_band;
        }
        g_target = g_band ? g_band : g_wnd.load();
    }
    if (!UpdateLayeredWindow(g_target, nullptr, &dst, &size, g_memDc, &src, 0, &bf, ULW_ALPHA)) {
        if (g_target != g_band) return false;
        Wh_Log(L"Drawing in explorer's window failed (%lu), drawing in this process's own", GetLastError());
        if (g_shown) ShowTarget(false);
        g_bandFailed = g_band;
        g_band = nullptr;
        g_target = g_wnd;
        g_shown = false;
        if (!UpdateLayeredWindow(g_target, nullptr, &dst, &size, g_memDc, &src, 0, &bf, ULW_ALPHA)) return false;
    }
    if (!g_shown) {
        ShowTarget(true);
        g_shown = true;
    }
    return true;
}

// sp may be null when n is 0: a frame of only particles and ripples.
static bool Draw(const Sprite* sp, int sw, int sh, const Copy* c, int n, int x, int y, int w, int h, LONGLONG now,
                 double scale) {
    if (n && !Resize(sp, sw, sh)) return false;
    if (g_gpuArmed) {
        if (DrawGpu(sw, sh, c, n, x, y, w, h, now, scale)) return true;
        FallbackToGdi(L"a frame could not be drawn");
        if (!g_wnd) return false;
    }
    return DrawGdi(sw, sh, c, n, x, y, w, h, now, scale);
}

static bool Hide() {
    if (g_shown && g_gpuArmed && g_gpu.surf && g_gpu.dev) {   // empty the surface so the next show can't flash this trail
        g_gpu.surf->Trim(nullptr, 0);
        g_gpu.dev->Commit();
    }
    if (g_shown) {
        ShowTarget(false);
        g_shown = false;
    }
    return false;
}

// The blur's copies for this frame at their places on the screen, and the box they cover; 0 if there is no blur.
static int BuildBlur(const Sample* pts, int np, int size, HCURSOR handle, Copy* copies, const Sprite** spOut,
                     int* swOut, int* shOut, RECT* box) {
    if (np < 2 || !g_drawing) return 0;
    if (g_spritesStale && !g_blankActive) {   // the cursor scheme, size or colour may have changed
        g_spritesStale = 0;
        FreeSprites();
    }

    Sprite* sp;
    if (g_blankActive) {
        sp = g_lastSprite;   // the real cursor is hidden: keep drawing the picture taken before
    } else {
        if (IsEmpty(handle)) return 0;   // the app hid its cursor: don't blur the previous one
        sp = GetSprite(handle, size);
        if (sp) {
            g_lastSprite = sp;
            if (g_pictureOf != handle) {   // the hider may be waiting for this picture
                g_pictureOf = handle;
                SetEvent(g_hideChanged);
            }
        } else {
            sp = g_lastSprite;
        }
    }
    if (!sp) return 0;

    Sample last = pts[np - 1];
    bool anyMove = false;
    for (int i = 0; i < np && !anyMove; i++) anyMove = pts[i].x != last.x || pts[i].y != last.y;
    if (!anyMove) return 0;   // stationary: nothing to blur

    // the picture at the size Windows draws the cursor on this monitor
    double f = (double)size / sp->w;
    int sw = size, sh = (int)lround(sp->h * f), hx = (int)lround(sp->hx * f), hy = (int)lround(sp->hy * f);

    int minX = INT_MAX, minY = INT_MAX, maxX = INT_MIN, maxY = INT_MIN;
    double total = 0;
    for (int i = 0; i < np; i++) {
        if (pts[i].x - hx < minX) minX = pts[i].x - hx;
        if (pts[i].y - hy < minY) minY = pts[i].y - hy;
        if (pts[i].x - hx + sw > maxX) maxX = pts[i].x - hx + sw;
        if (pts[i].y - hy + sh > maxY) maxY = pts[i].y - hy + sh;
        if (i) total += Dist(pts[i - 1], pts[i]);
    }
    double step = total / MAX_COPIES > 1 ? total / MAX_COPIES : 1;   // dense, faint copies read as a smooth blur
    double cover = COVER_PX * size / 32.0, peak = g_opacity / 100.0, trail = g_trailMs;
    LONGLONG now = Now();
    int n = 0;
    for (int i = 1; i < np && n < COPY_BUF; i++) {
        Sample a = pts[i - 1], b = pts[i];
        double dx = b.x - a.x, dy = b.y - a.y, d = sqrt(dx * dx + dy * dy);
        if (d < 0.5) continue;
        int k = (int)(d / step);
        if (k < 1) k = 1;
        for (int c = 0; c < k && n < COPY_BUF; c++) {
            double t = (double)c / k;
            double age = (now - (a.t + (b.t - a.t) * t)) / trail;   // 0 at the pointer, 1 at the end of the trail
            if (age >= 1) continue;
            double life = 1.0 - age * age;   // nearly full strength behind the pointer, fading out toward the end
            // About cover/step copies overlap at each point; layered on top of each other they add up to the target
            // opacity when each has 1 - (1 - target)^(step/cover).
            double target = peak * life, overlap = cover / step;
            double alpha = overlap > 1 ? 1 - pow(1 - target, 1 / overlap) : target;
            if (alpha * 255 < 0.5) continue;
            copies[n++] = {(int)lround(a.x + dx * t) - hx, (int)lround(a.y + dy * t) - hy,
                           alpha > 1 ? 1.0f : (float)alpha};
        }
    }
    if (n) {
        *spOut = sp;
        *swOut = sw;
        *shOut = sh;
        *box = {minX, minY, maxX, maxY};
    }
    return n;
}

static bool g_fxOnly;   // the last frame drew particles or ripples but no blur: the render thread can go a little slower

// Draws one frame of the blur, the particles and the ripples; false if there is nothing to draw (then the overlay is
// hidden).
static bool Render() {
    static Sample pts[MAX_SAMPLES];
    static Copy copies[COPY_BUF];
    int np, size;
    HCURSOR handle;
    bool visible;
    EnterCriticalSection(&g_gate);
    visible = g_curVisible;
    handle = g_curHandle;
    size = g_monCursor;
    np = g_histN;
    memcpy(pts, g_hist, np * sizeof(Sample));
    LeaveCriticalSection(&g_gate);

    LONGLONG now = Now();
    double scale = FxScale(size);
    if (g_paused || (!g_particles && !g_ripples)) {   // paused for a fullscreen app, or both turned off
        ClearEffects();
    } else {
        if (!g_particles) g_partN = 0;
        if (!g_ripples) g_ringN = 0;
        AgeEffects(now);
        // no dots while the cursor is hidden by the app (or by Windows), and none across the gap that leaves
        if (g_particles && visible && np && (g_blankActive || !IsEmpty(handle)))
            EmitParticles(pts, np, scale);
        else
            g_emitHave = false;
    }

    const Sprite* sp = nullptr;
    int sw = 0, sh = 0;
    RECT box = {INT_MAX, INT_MAX, INT_MIN, INT_MIN};
    int n = visible ? BuildBlur(pts, np, size, handle, copies, &sp, &sw, &sh, &box) : 0;
    if (g_partN || g_ringN) EffectBounds(now, scale, &box);
    if (box.left >= box.right || box.top >= box.bottom) return Hide();
    for (int i = 0; i < n; i++) {
        copies[i].x -= box.left;
        copies[i].y -= box.top;
    }
    g_fxOnly = !n;
    g_drawFailed = !Draw(sp, sw, sh, copies, n, box.left, box.top, box.right - box.left, box.bottom - box.top, now, scale);
    if (g_drawFailed) return Hide();
    return true;
}

// Raw mouse input: while on, Windows tells the overlay about every mouse report (even while other apps are active), so
// the sampler can sleep until the mouse really moves. Off while paused for a fullscreen game.
static bool ListenToMouse(bool on) {
    // generic desktop / mouse
    RAWINPUTDEVICE mouse = {1, 2, on ? (DWORD)RIDEV_INPUTSINK : (DWORD)RIDEV_REMOVE, on ? g_wnd.load() : nullptr};
    if (RegisterRawInputDevices(&mouse, 1, sizeof(mouse))) return true;
    Wh_Log(L"RegisterRawInputDevices(%d) failed: %lu", on, GetLastError());
    return false;
}

static UINT g_shellHookMsg;   // the shell hook's message: a window was activated, created, destroyed...

static LRESULT CALLBACK OverlayProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    // Another window was activated (the high bit marks a fullscreen one): look at the window in front.
    if (msg == g_shellHookMsg && msg && (wp & 0x7FFF) == HSHELL_WINDOWACTIVATED) {
        g_recheck = true;
        SetEvent(g_mouseWake);
        return 0;
    }
    switch (msg) {
        case WM_INPUT: {   // wake the sampler for movement only (not for wheel or button reports)
            RAWINPUT ri;
            UINT size = sizeof(ri);
            if (GetRawInputData((HRAWINPUT)lp, RID_INPUT, &ri, &size, sizeof(RAWINPUTHEADER)) != (UINT)-1 &&
                ri.header.dwType == RIM_TYPEMOUSE) {
                if (ri.data.mouse.lLastX || ri.data.mouse.lLastY || (ri.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE))
                    SetEvent(g_mouseWake);
                // A press of the left or right button: one ripple where the pointer is (this is the render thread, so
                // the pool is ours). The input itself goes on untouched.
                CURSORINFO ci;
                ci.cbSize = sizeof(ci);
                if ((ri.data.mouse.usButtonFlags & (RI_MOUSE_LEFT_BUTTON_DOWN | RI_MOUSE_RIGHT_BUTTON_DOWN)) &&
                    g_ripples && !g_paused && GetCursorInfo(&ci) && (ci.flags & CURSOR_SHOWING)) {
                    AddRipple(ci.ptScreenPos.x, ci.ptScreenPos.y);
                    SetEvent(g_moved);
                }
            }
            break;   // then DefWindowProc, which cleans up after the input
        }
        case WM_NCHITTEST:   // never catches a click
            return HTTRANSPARENT;
        case WM_APP_PAUSED:
            ListenToMouse(!g_paused);
            return 0;
        case WM_SETTINGCHANGE:
        case WM_DISPLAYCHANGE:   // monitors, scaling or cursor scheme changed
            g_monStale = 1;
            g_spritesStale = 1;
            break;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

// Hides the overlay and tears down the window with everything that hangs on it (render thread only).
static void DestroyOverlay() {
    Hide();
    if (g_wnd) {
        HWND w = g_wnd;
        DeregisterShellHookWindow(w);
        ListenToMouse(false);
        GpuShutdown();
        DestroyWindow(w);
        g_wnd = nullptr;
    }
    g_gpuArmed = false;
    g_target = nullptr;
}

// Builds the overlay window for the wanted renderer. GPU falls back to GDI by itself if DirectComposition will not
// start; a window cannot have a DirectComposition target and be drawn with UpdateLayeredWindow, so a different renderer
// always means a new window. Logs which renderer armed.
static bool CreateOverlay(bool wantGpu, const WCHAR* reasonIfGdi) {
    HINSTANCE inst = GetModuleHandleW(nullptr);
    bool gpu = wantGpu;
    for (;;) {
        DWORD ex = WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE |
                   (gpu ? WS_EX_NOREDIRECTIONBITMAP : 0);
        HWND w = CreateWindowExW(ex, OVERLAY_CLASS, L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, inst, nullptr);
        if (!w) return false;
        // The overlay covers the whole screen; without this the taskbar treats each trail as a fullscreen app
        // and drops below a fullscreen game every time the trail shows.
        SetPropW(w, L"NonRudeHWND", (HANDLE)TRUE);
        g_wnd = w;
        if (!gpu) break;
        SetLayeredWindowAttributes(w, 0, 255, LWA_ALPHA);   // layered, so clicks pass through to other processes
        if (GpuInit(w)) break;
        DestroyWindow(w);
        g_wnd = nullptr;
        gpu = false;
        reasonIfGdi = L"DirectComposition init failed";
    }
    g_gpuArmed = gpu;
    g_band = nullptr;
    g_target = nullptr;
    g_shown = false;
    if (!ListenToMouse(!g_paused)) {
        DestroyOverlay();
        return false;
    }
    g_shellHookMsg = RegisterWindowMessageW(L"SHELLHOOK");
    if (!RegisterShellHookWindow(g_wnd)) Wh_Log(L"RegisterShellHookWindow failed");
    if (gpu)
        Wh_Log(L"Pointer Afterimage Plus renderer armed: gpu (DirectComposition + Direct2D)");
    else
        Wh_Log(L"Pointer Afterimage Plus renderer armed: gdi (legacy; %s)", reasonIfGdi);
    return true;
}

static void FallbackToGdi(const WCHAR* why) {
    Wh_Log(L"GPU renderer failed (%s), falling back to GDI", why);
    DestroyOverlay();
    if (!CreateOverlay(false, why)) Wh_Log(L"Could not set up the GDI overlay window either");
}

// Draws when the mouse moves, at most once per half refresh of the monitor, and keeps drawing until the trail has faded
// after a stop. Idle, it wakes once more to give back memory, then sleeps until the mouse moves.
static DWORD WINAPI RenderThread(void*) {
    HINSTANCE inst = GetModuleHandleW(nullptr);
    WNDCLASSW wc = {};
    wc.lpfnWndProc = OverlayProc;
    wc.hInstance = inst;
    wc.lpszClassName = OVERLAY_CLASS;
    RegisterClassW(&wc);
    g_memDc = CreateCompatibleDC(nullptr);
    g_requested = g_rendererWanted;
    if (!g_memDc || !CreateOverlay(g_requested == 0, L"selected in settings")) {
        Wh_Log(L"Could not set up the overlay window");
        DestroyOverlay();
    }
    SetEvent(g_ready);

    LONGLONG lastDraw = -1000;
    bool trimmed = true, pending = false;   // pending: the mouse moved, but too soon after the last frame
    bool timerHigh = false;                 // a 1 ms timer while frames are coming, so particles fade smoothly
    while (!g_stop && g_wnd) {
        if (g_shown != timerHigh) {
            if (g_shown) timeBeginPeriod(1); else timeEndPeriod(1);
            timerHigh = g_shown;
        }
        // Frames of only particles and ripples come once per refresh; the blur needs twice that to keep up with
        // the pointer (see the sampler).
        int gap = g_monGap.load() * (g_fxOnly ? 2 : 1);
        LONGLONG wait = gap - (Now() - lastDraw);
        DWORD timeout = pending || g_shown ? (wait > 0 ? (DWORD)wait : 0) : trimmed ? INFINITE : 1500;
        DWORD r = MsgWaitForMultipleObjects(1, &g_moved, FALSE, timeout, QS_ALLINPUT);
        if (g_stop) break;
        if (r == WAIT_OBJECT_0 + 1) {
            MSG m;
            while (PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&m);
            continue;
        }
        if (g_rendererWanted != g_requested) {   // the Renderer setting changed: a new window for the new renderer
            g_requested = g_rendererWanted;
            DestroyOverlay();
            if (!CreateOverlay(g_requested == 0, L"selected in settings")) {
                Wh_Log(L"Could not set up the overlay window");
                break;
            }
        }
        if (r == WAIT_OBJECT_0) pending = true;
        if (!pending && !g_shown) {   // idle for 1.5 s: give back the memory that can be rebuilt
            ReleaseCanvas();
            Rel(g_gpu.bmp);
            free(g_pic);
            g_pic = nullptr;
            trimmed = true;
            continue;
        }
        if (Now() - lastDraw < gap) continue;
        pending = false;
        if (Render()) {
            lastDraw = Now();
            trimmed = false;
        }
    }

    if (timerHigh) timeEndPeriod(1);
    DestroyOverlay();   // explorer's window stays, hidden, for the next start
    UnregisterClassW(wc.lpszClassName, inst);
    ReleaseCanvas();
    if (g_memDc) DeleteDC(g_memDc);
    g_memDc = nullptr;
    free(g_pic);
    g_pic = nullptr;
    FreeSprites();
    return 0;
}

// ---- mod lifecycle ----

static LPTOP_LEVEL_EXCEPTION_FILTER g_prevFilter;

// This process exists only for this mod: if it ever crashes while the real cursor is hidden, give the cursor back.
static LONG WINAPI CrashFilter(EXCEPTION_POINTERS* e) {
    if (g_blankActive) ReloadCursors();   // the stored flag stays set, so the next start checks again
    if (g_band) ShowWindowAsync(g_band, SW_HIDE);
    return g_prevFilter ? g_prevFilter(e) : EXCEPTION_CONTINUE_SEARCH;
}

// Signals every thread to finish, waits for them, and makes sure the user's cursors are back.
static void StopThreads() {
    g_stop = true;
    SetEvent(g_mouseWake);
    SetEvent(g_moved);
    SetEvent(g_hideChanged);
    for (HANDLE& t : g_threads)
        if (t) {
            WaitForSingleObject(t, 5000);
            CloseHandle(t);
            t = nullptr;
        }
    if (g_blankActive) {
        ReloadCursors();
        SetBlank(false);
    }
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-19-pointer-effects\gen_settings.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace papset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkPointerAfterimagePlusSettings";
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1, WM_APP_SETTINGS_ACTIVATE = WM_APP + 2;
HANDLE g_settingsThread = nullptr;
std::atomic<HWND> g_settingsWnd;
std::atomic<bool> g_settingsStop;
void Settings_Close();
static std::wstring GetStringSetting(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}
// SetForegroundWindow works when this process had the last input; an empty SendInput gives it.
static void ForceForeground(HWND hwnd) {
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}
static float SystemCornerRadius(bool) { return 8; }
static int GetState(PCWSTR key, int fallback) { return Wh_GetIntValue(key, fallback); }
static void SetState(PCWSTR key, int value) { Wh_SetIntValue(key, value); }
static std::wstring StateKey(PCWSTR window, PCWSTR field) { return std::wstring(window)+L"_"+field; }
static void ApplyDarkWindow(HWND hwnd) { BOOL dark=TRUE; DwmSetWindowAttribute(hwnd,20,&dark,sizeof(dark)); }
namespace mocha {
constexpr UINT32 base = 0x1E1E2E, mantle = 0x181825, crust = 0x11111B,
                 surface0 = 0x313244, surface1 = 0x45475A, surface2 = 0x585B70,
                 overlay0 = 0x6C7086, overlay1 = 0x7F849C, overlay2 = 0x9399B2,
                 subtext0 = 0xA6ADC8, subtext1 = 0xBAC2DE, text = 0xCDD6F4,
                 lavender = 0xB4BEFE, blue = 0x89B4FA, sapphire = 0x74C7EC,
                 sky = 0x89DCEB, teal = 0x94E2D5, green = 0xA6E3A1,
                 yellow = 0xF9E2AF, peach = 0xFAB387, maroon = 0xEBA0AC,
                 red = 0xF38BA8, mauve = 0xCBA6F7, pink = 0xF5C2E7,
                 flamingo = 0xF2CDCD, rosewater = 0xF5E0DC;
}  // namespace mocha
inline D2D1_COLOR_F D2DColor(UINT32 rgb, float a = 1.0f) {
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.0f, ((rgb >> 8) & 0xFF) / 255.0f,
                        (rgb & 0xFF) / 255.0f, a);
}
inline D2D1_COLOR_F D2DColorRef(COLORREF c, float a = 1.0f) {
    return D2D1::ColorF(GetRValue(c) / 255.0f, GetGValue(c) / 255.0f, GetBValue(c) / 255.0f, a);
}
inline COLORREF RefFromRgb(UINT32 rgb) { return RGB((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF); }

COLORREF ParseColorRef(const std::wstring& text, COLORREF fallback) {
    std::wstring hex = !text.empty() && text[0] == L'#' ? text.substr(1) : text;
    if (hex.size() != 6 || hex.find_first_not_of(L"0123456789abcdefABCDEF") !=
                               std::wstring::npos) {
        return fallback;
    }
    UINT rgb = wcstoul(hex.c_str(), nullptr, 16);
    return RGB(rgb >> 16, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

// ---------------------------------------------------------------------------
// 50-settings.cpp : the mod's own settings window. A sidebar of pages, grouped
// cards, toggles, dropdowns, sliders, key boxes and colour chips, all drawn
// with Direct2D in the style of Seamless Dictate's settings. It shows the same
// settings as Windhawk's page for this mod and saves them with one elevated
// windhawk-cli call, so the two stay in step. Windhawk then calls
// WhTool_ModSettingsChanged by itself.
//
// One window, one Direct2D target that fills the whole client rect (the window
// edge is rounded by DWM, never by us). Text typed into a number, text or colour
// box goes through one small native EDIT that sits on top of the box while it is
// edited. Key boxes read WM_KEYDOWN themselves.
// ---------------------------------------------------------------------------

template <class T>
class SetCom {
   public:
    T* p = nullptr;
    SetCom() = default;
    SetCom(const SetCom& o) : p(o.p) {
        if (p) p->AddRef();
    }
    SetCom& operator=(const SetCom& o) {
        if (o.p) o.p->AddRef();
        reset();
        p = o.p;
        return *this;
    }
    ~SetCom() { reset(); }
    void reset() {
        if (p) p->Release();
        p = nullptr;
    }
    T** put() {
        reset();
        return &p;
    }
    T* get() const { return p; }
    T* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

// One row of a tray menu (Set_TrayMenu). Every mod's tray menu is a list of these.
struct SetMenuItem {
    int id = 0;                    // What Set_TrayMenu returns when this row is picked.
    std::wstring glyph;            // FiraCode Nerd Font glyph for the leading column.
    std::wstring label;
    std::wstring hint;             // Grey text on the right, such as a hotkey.
    bool checked = false;          // Accent check mark on the right.
    bool separator = false;
    bool disabled = false;
    std::vector<SetMenuItem> sub;  // A submenu, drawn by the same renderer.
};

// One open level of a tray menu: its own popup window and Direct2D target.
struct SetMenuLevel {
    const std::vector<SetMenuItem>* items = nullptr;
    HWND hwnd = nullptr;
    SetCom<ID2D1HwndRenderTarget> rt;
    float scale = 1, wDip = 0, hDip = 0, itemH = 30, hintW = 0;
    std::vector<float> top, height;  // Per row, DIPs inside the window.
    int hover = -1;                  // Highlighted row.
    int open = -1;                   // Row whose submenu is the next level.
};

// A running tray menu. It owns its factories, so it runs on whatever thread owns the tray icon.
struct SetMenuSession {
    SetCom<ID2D1Factory> d2d;
    SetCom<IDWriteFactory> dw;
    SetCom<IDWriteTextFormat> fText, fHint, fGlyph, fGlyphS;
    std::vector<std::unique_ptr<SetMenuLevel>> levels;
    HINSTANCE inst = nullptr;
    std::wstring cls;
    float radius = 8;
    int result = 0;
    bool done = false;
    bool pressed = false;  // A button went down inside the menu; only then does a release pick a row.
    bool wasActive = false;
    float alpha = 1;
    ULONGLONG fadeStart = 0;
    int pendingLevel = -1, pendingItem = -1;  // Hover timer: open (item >= 0) or close a submenu after a delay.
};

struct SetField {
    enum Kind { Choice, Number, Text, Hotkey, Check, Color };
    Kind kind;
    PCWSTR key;
    PCWSTR label;
    PCWSTR desc = nullptr;
    PCWSTR def = L"";                                // The schema default ("Reset to suggested").
    std::vector<std::pair<PCWSTR, PCWSTR>> options;  // Value, label.
    int min = 0, max = 0;
    int page = 0;        // Which sidebar page shows it.
    PCWSTR group = L"";  // Heading above it on that page.
    std::wstring value;  // As loaded, so a save writes only what changed.
    std::wstring cur;    // What the window shows now.
    float fitW = 0;      // Box width that fits the text (Set_FitBoxes); 0 until measured.
    float fitText = -1;  // Measured text width behind fitW.
    std::wstring fitFor; // The text that was measured.
};

// Names, descriptions and option labels match the ==WindhawkModSettings== block word for word.
// Generated by work\2026-11-19-pointer-effects\gen_settings.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Number, L"trailOpacity", L"Trail opacity (%)", L"1 to 100 (Suggested: 50). How solid the blur is right behind the pointer.", L"50", {}, 1, 100, 0, L"Blur"},
{K::Number, L"trailMs", L"Trail length (ms)", L"10 to 150 (Suggested: 25). How far back in time the blur reaches.", L"25", {}, 10, 150, 0, L"Blur"},
{K::Number, L"drawSpeed", L"Minimum blur speed (cm/s)", L"0 to 50 (Suggested: 29). Slower moves draw no blur and use almost no CPU. 0 draws at any speed.", L"29", {}, 0, 50, 0, L"Blur"},
{K::Check, L"hideWhenFast", L"Hide the real cursor when moving very fast", L"Swaps the system cursors for an invisible one while you move fast, and puts your cursor scheme back afterwards.", L"1", {}, 0, 100, 0, L"Fast moves"},
{K::Number, L"hideSpeed", L"Hide above speed (cm/s)", L"20 to 300 (Suggested: 30). Measured on the main screen, so the same hand speed counts on every screen.", L"30", {}, 20, 300, 0, L"Fast moves"},
{K::Check, L"particles", L"Particle trail", L"Small glowing dots that drift and fade behind the moving pointer.", L"0", {}, 0, 100, 1, L"Particle trail"},
{K::Number, L"particleAmount", L"Particle amount", L"1 to 10 (Suggested: 5). How close together the dots are along the path.", L"5", {}, 1, 10, 1, L"Particle trail"},
{K::Number, L"particleSize", L"Particle size", L"1 to 10 (Suggested: 3). Pixels at 100% scaling with the normal pointer size.", L"3", {}, 1, 10, 1, L"Particle trail"},
{K::Number, L"particleLife", L"Particle lifetime (ms)", L"100 to 1500 (Suggested: 450). How long each dot takes to fade away.", L"450", {}, 100, 1500, 1, L"Particle trail"},
{K::Choice, L"particleColor", L"Particle colour", L"", L"gradient", {{L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}}, 0, 100, 1, L"Particle trail"},
{K::Check, L"ripples", L"Click ripples", L"A ring that grows and fades where you press the left or right button.", L"0", {}, 0, 100, 1, L"Click ripples"},
{K::Number, L"rippleSize", L"Ripple size", L"20 to 120 (Suggested: 36). How wide the ring gets, in pixels at 100% scaling.", L"36", {}, 20, 120, 1, L"Click ripples"},
{K::Number, L"rippleMs", L"Ripple duration (ms)", L"150 to 1000 (Suggested: 400). How long one ring takes to grow and fade.", L"400", {}, 150, 1000, 1, L"Click ripples"},
{K::Check, L"pauseInFullscreen", L"Pause in fullscreen apps and games", L"On, nothing is drawn while a game or video fills the screen.", L"1", {}, 0, 100, 2, L"Running"},
{K::Choice, L"renderer", L"Renderer", L"GPU is suggested. GDI is the older painter, kept for troubleshooting and for drawing above the Start menu. If the GPU cannot start, the mod falls back to GDI by itself.", L"gpu", {{L"gpu", L"GPU (suggested)"}, {L"gdi", L"GDI (older, on the CPU)"}}, 0, 100, 2, L"Running"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to open these settings. Right-click it to pause the effects or open settings. When off, change settings in Windhawk.", L"1", {}, 0, 100, 3, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Cursor blur", L"The fading copies of your pointer that follow it while it moves.", 0xE8B0},
{L"Effects", L"A particle trail behind the pointer and ripples where you click.", 0xF4A5},
{L"General", L"When the effects run, how they are drawn, and this window.", 0xE713},
{L"Look", L"Choose how this settings window looks and whether its tray icon is shown.", 0xE790},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
constexpr int kSetDropMax = 9;  // A dropdown with more options than this scrolls.
// The sidebar is a floating dock: dragged between min and max, or collapsed to an icon rail.
constexpr float kSetDockGap = 10, kSetRailDef = 232, kSetRailMin = 200, kSetRailMax = 380, kSetRailMini = 60,
                kSetRailSnap = 130, kSetEdgeGrab = 5;
// The footer is a floating pill dock at the bottom right of the page.
constexpr float kSetFootBtnH = 36, kSetFootPad = 8, kSetFootH = kSetFootBtnH + 2 * kSetFootPad, kSetFootGap = 14;
// The glass tint is one layer over the whole window, title bar included, so the two always match.
constexpr float kSetGlassTint = 0.55f, kSetNativeFade = 56;
constexpr float kSetEdgeW = 2, kSetRadius = 16;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://github.com/sidlikesgrapess/CursorMotionBlur";
constexpr PCWSTR kSetCrossOverUrl = L"https://windhawk.net/mods/mouse-trail";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BPointer%20Afterimage%20Plus%5D%20";
constexpr PCWSTR kSetTitle = L"Pointer Afterimage Plus";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;
constexpr float kSetMenuPad = 6, kSetMenuIconW = 22, kSetMenuSepH = 9, kSetMenuOverlap = 3, kSetMenuMinW = 190, kSetMenuMaxW = 640, kSetMenuBorderW = 2;
constexpr UINT kSetMenuSubDelayMs = 200, kSetMenuFadeMs = 90, kSetMenuTimerSub = 0x5E71, kSetMenuTimerFade = 0x5E72, kSetMenuTimerPoll = 0x5E73;

struct SetItem {
    enum Type { Group, Row, Banner, About, Link, Support } type = Row;
    int field = -1;  // Row: index into fields.
    float y = 0, h = 0;
    std::wstring text, sub, url;
};

// What the pointer is over. id picks the hover glow.
struct SetHit {
    enum Kind { None, Rail, Row, Control, Slider, Clear, Chip, Footer, Drop, Link, Scroll, Popup, Caption, RailToggle, RailEdge } kind = None;
    int a = -1, b = -1;
    int id = -1;
};

struct SetWindow {
    HWND hwnd = nullptr, edit = nullptr, owner = nullptr;
    HFONT editFont = nullptr;
    HBRUSH editBrush = nullptr;
    std::vector<SetField> fields = Set_MakeFields();
    std::vector<SetItem> items;
    UINT dpi = 96;
    float cw = 980, ch = 700;  // Content size in DIPs: the client area below the title bar.
    HICON iconSmall = nullptr, iconBig = nullptr;
    int capDown = 0;  // Title bar button held down: 1 minimize, 2 maximize, 3 close.
    bool capTracking = false, active = true;
    bool nativeTitle = false;  // Windows draws the title bar and its buttons.
    bool glass = false;        // Acrylic behind the window; the page is drawn see-through.
    ULONGLONG lastTick = 0;
    int page = 0, recording = -1, editing = -1, focus = -1, openSel = -1;
    bool kbd = false;  // Show the focus ring (after a Tab).
    D2D1_RECT_F dropRect{};
    int dropHover = -1, dropTop = 0;  // dropTop: first option shown when the dropdown scrolls.
    bool frameApplied = false;        // Set_ApplyFrame has run once.
    float scrollY = 0, scrollTarget = 0, contentH = 0, contentX = 0, contentW = 720, pageT = 1;
    SetHit hover;
    int dragSlider = -1;
    bool dragScroll = false, tracking = false, timer = false;
    float dragOff = 0;
    bool autoScroll = false, autoMoved = false;
    float autoX = 0, autoY = 0, autoA = 0, autoDir = 0;
    // Sidebar dock: railW is the chosen open width, railCur the drawn width (eased toward
    // kSetRailMini when collapsed). railGlow / footGlow ease the dock borders on hover.
    float railW = kSetRailDef, railCur = kSetRailDef, railGlow = 0, footGlow = 0;
    bool railCollapsed = false, dragRail = false;
    float mouseX = -1, mouseY = -1;
    std::map<int, float> glow;  // Eased hover amount by hit id.
    std::map<int, float> knob;  // Eased toggle position by field.
    std::wstring status;
    bool statusError = false;
    bool saving = false, destroyed = false, render = false;
    SetCom<ID2D1HwndRenderTarget> rt;
    SetCom<ID2D1BitmapRenderTarget> layer;  // The page, drawn off screen so the footer can blur it.
    D2D1_SIZE_F layerSize{};
    std::wstring family, iconFamily;
    SetCom<IDWriteTextFormat> fLabel, fHint, fTitle, fIntro, fSection, fValue, fValueC, fButton, fIcon, fIconS,
        fIconL, fBig, fSmall, fStatusLine, fCap, fCapGlyph, fRailName;
    RECT normalRect{};  // Last restored-state rect, remembered on close.
    COLORREF customColors[16] = {};
};

static std::shared_ptr<SetWindow> g_setWin;
static UINT g_setForceDpi;  // Harness renders at a chosen scale.
static SetCom<ID2D1Factory> g_setD2d;
static SetCom<IDWriteFactory> g_setDw;
static SetCom<IWICImagingFactory> g_setWic;
#ifdef SCM_HARNESS
static std::wstring g_setFakeKeyStatus;  // Lets the test render the hotkey warning line.
#endif

static float Set_Rad(const D2D1_RECT_F& r, float most = kSetRadius) {
    return std::min(most, std::min(r.right - r.left, r.bottom - r.top) / 2);
}

static std::wstring Set_WindowText(HWND hwnd) {
    std::wstring text(GetWindowTextLengthW(hwnd) + 1, L'\0');
    text.resize(GetWindowTextW(hwnd, text.data(), (int)text.size()));
    return text;
}

static std::wstring Set_KeyStatusText() {
#ifdef SCM_HARNESS
    if (!g_setFakeKeyStatus.empty()) return g_setFakeKeyStatus;
#endif
    return std::wstring();
}

// Quotes one argument the way CommandLineToArgvW reads it back.
static std::wstring Set_QuoteArg(const std::wstring& arg) {
    std::wstring out = L"\"";
    for (size_t i = 0;; i++) {
        size_t slashes = 0;
        while (i < arg.size() && arg[i] == L'\\') i++, slashes++;
        if (i == arg.size()) {
            out.append(slashes * 2, L'\\');
            break;
        }
        out.append(arg[i] == L'"' ? slashes * 2 + 1 : slashes, L'\\');
        out += arg[i];
    }
    return out + L"\"";
}

// windhawk-cli.exe sits three folders above the engine
// (<Windhawk>\Engine\<version>\<arch>\windhawk.dll), next to windhawk.exe.
static std::wstring Set_CliPath() {
    WCHAR path[MAX_PATH];
    if (HMODULE engine = GetModuleHandleW(L"windhawk.dll"); engine && GetModuleFileNameW(engine, path, MAX_PATH)) {
        std::wstring dir = path;
        for (int i = 0; i < 4 && dir.find_last_of(L'\\') != std::wstring::npos; i++) dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (GetFileAttributesW(dir.c_str()) != INVALID_FILE_ATTRIBUTES) return dir;
    }
    if (GetModuleFileNameW(nullptr, path, MAX_PATH)) {
        std::wstring dir = path;
        dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (GetFileAttributesW(dir.c_str()) != INVALID_FILE_ATTRIBUTES) return dir;
    }
    return {};
}

// ---- Factories and fonts ---------------------------------------------------

static bool Set_EnsureFactories() {
    if (!g_setD2d) {
        D2D1_FACTORY_OPTIONS o{};
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &o,
                                     (void**)g_setD2d.put())))
            return false;
    }
    if (!g_setDw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                               (IUnknown**)g_setDw.put())))
        return false;
    if (!g_setWic && FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                             __uuidof(IWICImagingFactory), (void**)g_setWic.put())))
        return false;
    return true;
}

static void Set_ReleaseFactories() {
    g_setWic.reset();
    g_setDw.reset();
    g_setD2d.reset();
}

static bool Set_FamilyExists(const std::wstring& name) {
    SetCom<IDWriteFontCollection> sys;
    if (name.empty() || FAILED(g_setDw->GetSystemFontCollection(sys.put(), FALSE))) return false;
    UINT32 index = 0;
    BOOL exists = FALSE;
    return SUCCEEDED(sys->FindFamilyName(name.c_str(), &index, &exists)) && exists;
}

// The font setting, or its Nerd Font build ("Fira Code" is installed as
// "FiraCode Nerd Font"), or Segoe UI.
static std::wstring Set_ResolveFamily() {
    if (Set_FamilyExists(std::wstring(L"FiraCode Nerd Font"))) return std::wstring(L"FiraCode Nerd Font");
    std::wstring joined;
    for (WCHAR c : std::wstring(L"FiraCode Nerd Font"))
        if (c != L' ') joined += c;
    for (const std::wstring& face : {joined + L" Nerd Font", std::wstring(L"FiraCode Nerd Font") + L" Nerd Font", joined})
        if (Set_FamilyExists(face)) return face;
    return L"Segoe UI";
}

static float Set_TextW(IDWriteTextFormat* fmt, const std::wstring& text);

static SetCom<IDWriteTextFormat> Set_Fmt(const std::wstring& family, float size, int weight, bool wrap,
                                         DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING,
                                         bool vcenter = false) {
    SetCom<IDWriteTextFormat> f;
    if (FAILED(g_setDw->CreateTextFormat(family.c_str(), nullptr, (DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STYLE_NORMAL,
                                         DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", f.put())))
        return f;
    f->SetWordWrapping(wrap ? DWRITE_WORD_WRAPPING_WRAP : DWRITE_WORD_WRAPPING_NO_WRAP);
    f->SetTextAlignment(align);
    f->SetParagraphAlignment(vcenter ? DWRITE_PARAGRAPH_ALIGNMENT_CENTER : DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    if (!wrap) {
        SetCom<IDWriteInlineObject> sign;
        g_setDw->CreateEllipsisTrimmingSign(f.get(), sign.put());
        DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        f->SetTrimming(&t, sign.get());
    }
    return f;
}

// std::wstring(L"FiraCode Nerd Font") at 500; emphasis is one step heavier, never past bold.
static float Set_MenuCornerRadius() {
    float radius = 8.0f;
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0,
                      KEY_READ | KEY_WOW64_64KEY, &key) == ERROR_SUCCESS) {
        DWORD disabled = 0, size = sizeof(disabled);
        bool off = RegQueryValueExW(key, L"Disabled", nullptr, nullptr, (BYTE*)&disabled, &size) == ERROR_SUCCESS && disabled;
        DWORD value = 0;
        size = sizeof(value);
        if (!off && RegGetValueW(key, L"Settings", L"radius", RRF_RT_REG_DWORD, nullptr, &value, &size) == ERROR_SUCCESS &&
            value > 0 && value <= 64)
            radius = (float)value;
        RegCloseKey(key);
    }
    return radius;
}

static SetMenuItem Set_MenuRow(int id, PCWSTR glyph, PCWSTR label, bool checked = false, bool disabled = false,
                               PCWSTR hint = L"") {
    SetMenuItem m;
    m.id = id;
    m.glyph = glyph ? glyph : L"";
    m.label = label ? label : L"";
    m.hint = hint ? hint : L"";
    m.checked = checked;
    m.disabled = disabled;
    return m;
}

static SetMenuItem Set_MenuSub(PCWSTR glyph, PCWSTR label, std::vector<SetMenuItem> sub, bool disabled = false) {
    SetMenuItem m = Set_MenuRow(0, glyph, label, false, disabled);
    m.sub = std::move(sub);
    return m;
}

static SetMenuItem Set_MenuSep() {
    SetMenuItem m;
    m.separator = true;
    return m;
}

static SetMenuSession*& Set_MenuCur() {
    static thread_local SetMenuSession* session = nullptr;  // One menu per thread; History menus run on the settings thread.
    return session;
}

static bool Set_MenuSelectable(const SetMenuItem& m) { return !m.separator && !m.disabled; }

static float Set_MenuTextW(SetMenuSession& s, IDWriteTextFormat* f, const std::wstring& text) {
    SetCom<IDWriteTextLayout> layout;
    DWRITE_TEXT_METRICS m{};
    if (text.empty() || !f || FAILED(s.dw->CreateTextLayout(text.c_str(), (UINT32)text.size(), f, 10000, 1000, layout.put())) ||
        FAILED(layout->GetMetrics(&m)))
        return 0;
    return m.widthIncludingTrailingWhitespace;
}

static bool Set_MenuFormats(SetMenuSession& s) {
    if (!s.d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), nullptr,
                                           (void**)s.d2d.put())))
        return false;
    if (!s.dw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)s.dw.put())))
        return false;
    std::wstring family = L"Segoe UI";
    SetCom<IDWriteFontCollection> sys;
    if (SUCCEEDED(s.dw->GetSystemFontCollection(sys.put(), FALSE))) {
        for (PCWSTR face : {L"FiraCode Nerd Font", L"FiraCodeNerdFont", L"FiraCode Nerd Font Mono"}) {
            UINT32 index = 0;
            BOOL exists = FALSE;
            if (SUCCEEDED(sys->FindFamilyName(face, &index, &exists)) && exists) {
                family = face;
                break;
            }
        }
    }
    auto make = [&](float size, DWRITE_TEXT_ALIGNMENT align, SetCom<IDWriteTextFormat>& out) {
        if (FAILED(s.dw->CreateTextFormat(family.c_str(), nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
                                          DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", out.put())))
            return false;
        out->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        out->SetTextAlignment(align);
        out->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        // Only a label wider than the widest menu (kSetMenuMaxW) is ever shortened, with an ellipsis.
        DWRITE_TRIMMING trim{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        SetCom<IDWriteInlineObject> sign;
        if (SUCCEEDED(s.dw->CreateEllipsisTrimmingSign(out.get(), sign.put()))) out->SetTrimming(&trim, sign.get());
        return true;
    };
    return make(13.5f, DWRITE_TEXT_ALIGNMENT_LEADING, s.fText) && make(12.5f, DWRITE_TEXT_ALIGNMENT_TRAILING, s.fHint) &&
           make(15, DWRITE_TEXT_ALIGNMENT_CENTER, s.fGlyph) && make(12, DWRITE_TEXT_ALIGNMENT_CENTER, s.fGlyphS);
}

static void Set_MenuLayout(SetMenuSession& s, SetMenuLevel& lv) {
    const auto& items = *lv.items;
    lv.itemH = 30;
    lv.top.assign(items.size(), 0);
    lv.height.assign(items.size(), 0);
    float textW = 0, hintW = 0, y = kSetMenuPad;
    for (size_t i = 0; i < items.size(); i++) {
        lv.top[i] = y;
        lv.height[i] = items[i].separator ? kSetMenuSepH : lv.itemH;
        y += lv.height[i];
        if (items[i].separator) continue;
        textW = std::max(textW, Set_MenuTextW(s, s.fText.get(), items[i].label));
        hintW = std::max(hintW, Set_MenuTextW(s, s.fHint.get(), items[i].hint));
    }
    lv.hintW = std::ceil(hintW);
    float w = kSetMenuPad * 2 + 8 + kSetMenuIconW + 10 + std::ceil(textW) + 2 + (hintW > 0 ? 24 + lv.hintW : 0) + 10 + 20 + 8;
    lv.wDip = std::ceil(std::clamp(w, kSetMenuMinW, kSetMenuMaxW));
    lv.hDip = std::ceil(y + kSetMenuPad);
}

static int Set_MenuItemAt(const SetMenuLevel& lv, float x, float y) {
    if (x < kSetMenuPad || x >= lv.wDip - kSetMenuPad) return -1;
    for (size_t i = 0; i < lv.top.size(); i++)
        if (y >= lv.top[i] && y < lv.top[i] + lv.height[i]) return (*lv.items)[i].separator ? -1 : (int)i;
    return -1;
}

static int Set_MenuNext(const SetMenuLevel& lv, int from, int dir) {
    int n = (int)lv.items->size();
    if (!n) return -1;
    int i = from < 0 ? (dir > 0 ? -1 : n) : from;
    for (int k = 0; k < n; k++) {
        i = ((i + dir) % n + n) % n;
        if (Set_MenuSelectable((*lv.items)[(size_t)i])) return i;
    }
    return -1;
}

static void Set_MenuPaint(SetMenuSession& s, SetMenuLevel& lv) {
    ID2D1RenderTarget* rt = lv.rt.get();
    SetCom<ID2D1SolidColorBrush> brush;
    if (FAILED(rt->CreateSolidColorBrush(D2DColor(mocha::text), brush.put()))) return;
    auto solid = [&](UINT32 rgb, float a) {
        brush->SetColor(D2DColor(rgb, a));
        return brush.get();
    };
    auto gradient = [&](D2D1_POINT_2F a, D2D1_POINT_2F b, D2D1_COLOR_F c1, D2D1_COLOR_F c2) {
        SetCom<ID2D1LinearGradientBrush> g;
        D2D1_GRADIENT_STOP stops[2] = {{0, c1}, {1, c2}};
        SetCom<ID2D1GradientStopCollection> coll;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())))
            rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(a, b), coll.get(), g.put());
        return g;
    };
    // Blue to mauve at 45 degrees across a rect, like Seamless Borders.
    auto accent = [&](const D2D1_RECT_F& r, float a) {
        float d = ((r.right - r.left) + (r.bottom - r.top)) / 2;
        return gradient({r.left, r.top}, {r.left + d, r.top + d}, D2DColor(mocha::blue, a), D2DColor(mocha::mauve, a));
    };
    const float w = lv.wDip, h = lv.hDip;
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    SetCom<ID2D1Layer> layer;
    bool faded = s.alpha < 0.999f && SUCCEEDED(rt->CreateLayer(nullptr, layer.put()));
    if (faded)
        rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), nullptr, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
                                            D2D1::IdentityMatrix(), std::max(0.0f, s.alpha)),
                      layer.get());
    // Dark Mocha over the acrylic blur; DWM rounds the window.
    auto tint = gradient({0, 0}, {0, h}, D2DColor(mocha::base, 0.80f), D2DColor(mocha::base, 0.84f));
    if (tint) rt->FillRectangle({0, 0, w, h}, tint.get());
    const auto& items = *lv.items;
    const float slotRight = w - kSetMenuPad - 8, slotLeft = slotRight - 20;
    for (size_t i = 0; i < items.size(); i++) {
        const SetMenuItem& m = items[i];
        D2D1_RECT_F r{kSetMenuPad, lv.top[i], w - kSetMenuPad, lv.top[i] + lv.height[i]};
        if (m.separator) {
            float y = std::floor((r.top + r.bottom) / 2);
            rt->FillRectangle({r.left + 8, y, r.right - 8, y + 1}, solid(mocha::surface1, 0.8f));
            continue;
        }
        bool hot = ((int)i == lv.hover || (int)i == lv.open) && !m.disabled;
        if (hot) {
            // The hover look of every card: a faint blue to mauve wash and the 2 px gradient ring.
            float ringW = kSetEdgeW, rad = std::min(12.0f, (r.bottom - r.top) / 2);
            D2D1_ROUNDED_RECT rr{{r.left + ringW / 2, r.top + ringW / 2, r.right - ringW / 2, r.bottom - ringW / 2}, rad, rad};
            auto fill = gradient({r.left, r.top}, {r.right, r.bottom}, D2DColor(mocha::blue, 0.16f), D2DColor(mocha::mauve, 0.16f));
            if (fill) rt->FillRoundedRectangle(rr, fill.get());
            auto ring = accent(r, 0.8f);
            if (ring) rt->DrawRoundedRectangle(rr, ring.get(), ringW);
        }
        UINT32 col = m.disabled ? mocha::overlay0 : mocha::text;
        if (!m.glyph.empty())
            rt->DrawText(m.glyph.c_str(), (UINT32)m.glyph.size(), s.fGlyph.get(),
                         {r.left + 8, r.top, r.left + 8 + kSetMenuIconW, r.bottom}, solid(col, 1));
        float textX = r.left + 8 + kSetMenuIconW + 10;
        float hintRight = slotLeft - 10, hintLeft = hintRight - lv.hintW;
        float textRight = lv.hintW > 0 ? hintLeft - 12 : slotLeft - 4;
        if (!m.label.empty())
            rt->DrawText(m.label.c_str(), (UINT32)m.label.size(), s.fText.get(), {textX, r.top, textRight, r.bottom},
                         solid(col, 1));
        if (!m.hint.empty())
            rt->DrawText(m.hint.c_str(), (UINT32)m.hint.size(), s.fHint.get(), {hintLeft, r.top, hintRight, r.bottom},
                         solid(m.disabled ? mocha::overlay0 : mocha::subtext0, 1));
        if (!m.sub.empty()) {
            rt->DrawText(L"", 1, s.fGlyphS.get(), {slotLeft, r.top, slotRight, r.bottom}, solid(col, 1));  // chevron_right
        } else if (m.checked) {
            rt->DrawText(L"", 1, s.fGlyph.get(), {slotLeft, r.top, slotRight, r.bottom},  // check
                         solid(m.disabled ? mocha::overlay0 : mocha::blue, 1));
        }
    }
    // The edge on DWM's real corner curve: 2 px, blue to mauve, inset half the stroke.
    const float bw = kSetMenuBorderW;
    D2D1_RECT_F edge{bw / 2, bw / 2, w - bw / 2, h - bw / 2};
    auto border = accent({0, 0, w, h}, 1);
    float r2 = std::max(0.0f, s.radius - bw / 2);
    if (border) rt->DrawRoundedRectangle({edge, r2, r2}, border.get(), bw);
    if (faded) rt->PopLayer();
}

static int Set_MenuIndexOf(HWND hwnd) {
    if (SetMenuSession* s = Set_MenuCur())
        for (size_t i = 0; i < s->levels.size(); i++)
            if (s->levels[i]->hwnd == hwnd) return (int)i;
    return -1;
}

static void Set_MenuInvalidate() {
    if (SetMenuSession* s = Set_MenuCur())
        for (auto& lv : s->levels)
            if (lv->hwnd) InvalidateRect(lv->hwnd, nullptr, FALSE);
}

static void Set_MenuCloseFrom(size_t n) {
    SetMenuSession* s = Set_MenuCur();
    if (!s) return;
    while (s->levels.size() > n) {
        HWND h = s->levels.back()->hwnd;
        s->levels.back()->rt.reset();
        s->levels.pop_back();
        if (h) DestroyWindow(h);
    }
    if (n > 0 && !s->levels.empty()) s->levels.back()->open = -1;
    Set_MenuInvalidate();
}

static void Set_MenuFinish(int id) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || s->done) return;
    s->result = id;
    s->done = true;
}

static void Set_MenuBackdrop(HWND hwnd) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    int corner = 2;  // DWMWCP_ROUND
    DwmSetWindowAttribute(hwnd, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner, sizeof(corner));
    COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: the menu draws its own edge.
    DwmSetWindowAttribute(hwnd, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
    int backdrop = 1;  // DWMSBT_NONE
    DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
    DWM_BLURBEHIND bb{};
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.fEnable = TRUE;
    bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
    DwmEnableBlurBehindWindow(hwnd, &bb);
    if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
    struct SetAccentPolicy { int state, flags, abgr, animation; };
    struct SetCompositionData { DWORD attribute; void* data; SIZE_T size; };
    using SetComposition_t = BOOL(WINAPI*)(HWND, SetCompositionData*);
    if (auto setComposition =
            (SetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute")) {
        SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};
        SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
        setComposition(hwnd, &data);
    }
}

static RECT Set_MenuWorkArea(POINT pt) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &mi);
    return mi.rcWork;
}

static bool Set_MenuCreateWindow(SetMenuSession& s, SetMenuLevel& lv, POINT at, const RECT* parent, int rowTopPx) {
    DWORD ex = WS_EX_TOOLWINDOW | WS_EX_TOPMOST | (parent ? WS_EX_NOACTIVATE : 0);
    HWND hwnd = CreateWindowExW(ex, s.cls.c_str(), L"", WS_POPUP, at.x, at.y, 1, 1, nullptr, nullptr, s.inst, nullptr);
    if (!hwnd) return false;
    lv.hwnd = hwnd;
    lv.scale = GetDpiForWindow(hwnd) / 96.0f;
    if (lv.scale <= 0) lv.scale = 1;
    Set_MenuLayout(s, lv);
    int w = (int)std::ceil(lv.wDip * lv.scale), h = (int)std::ceil(lv.hDip * lv.scale);
    RECT wa = Set_MenuWorkArea(parent ? POINT{parent->right, parent->top + rowTopPx} : at);
    int x = at.x, y = at.y;
    if (parent) {
        int overlap = (int)kSetMenuOverlap;
        x = parent->right - overlap;
        if (x + w > wa.right) x = parent->left - w + overlap;
        y = parent->top + rowTopPx - (int)(kSetMenuPad * lv.scale);
        if (y + h > wa.bottom) y = wa.bottom - h;
    } else {
        if (x + w > wa.right) x = at.x - w;
        if (y + h > wa.bottom) y = at.y - h;
    }
    x = std::clamp<int>(x, wa.left, std::max<int>(wa.left, wa.right - w));
    y = std::clamp<int>(y, wa.top, std::max<int>(wa.top, wa.bottom - h));
    Set_MenuBackdrop(hwnd);
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE | SWP_FRAMECHANGED);
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96 * lv.scale, 96 * lv.scale);
    s.d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU((UINT32)w, (UINT32)h)),
                                  lv.rt.put());
    return (bool)lv.rt;
}

static void Set_MenuOpenSub(size_t level, int item, bool keyboard) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || level >= s->levels.size()) return;
    SetMenuLevel& parent = *s->levels[level];
    const SetMenuItem& m = (*parent.items)[(size_t)item];
    if (m.sub.empty() || m.disabled) return;
    Set_MenuCloseFrom(level + 1);
    auto lv = std::make_unique<SetMenuLevel>();
    lv->items = &m.sub;
    RECT pr{};
    GetWindowRect(parent.hwnd, &pr);
    SetMenuLevel* raw = lv.get();
    s->levels.push_back(std::move(lv));
    parent.open = item;
    if (!Set_MenuCreateWindow(*s, *raw, POINT{pr.right, pr.top}, &pr, (int)(parent.top[(size_t)item] * parent.scale))) {
        Set_MenuCloseFrom(level + 1);
        return;
    }
    if (keyboard) raw->hover = Set_MenuNext(*raw, -1, +1);
    ShowWindow(raw->hwnd, SW_SHOWNOACTIVATE);
    Set_MenuInvalidate();
}

static void Set_MenuActivate(size_t level, int item, bool keyboard) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || level >= s->levels.size()) return;
    const SetMenuItem& m = (*s->levels[level]->items)[(size_t)item];
    if (!Set_MenuSelectable(m)) return;
    if (!m.sub.empty()) Set_MenuOpenSub(level, item, keyboard);
    else Set_MenuFinish(m.id);
}

static void Set_MenuHoverChanged(size_t level, int item) {
    SetMenuSession* s = Set_MenuCur();
    if (!s) return;
    SetMenuLevel& lv = *s->levels[level];
    HWND root = s->levels[0]->hwnd;
    KillTimer(root, kSetMenuTimerSub);
    s->pendingItem = -1;
    bool wantsSub = item >= 0 && Set_MenuSelectable((*lv.items)[(size_t)item]) && !(*lv.items)[(size_t)item].sub.empty();
    if (wantsSub && lv.open != item) {
        s->pendingLevel = (int)level;
        s->pendingItem = item;
        SetTimer(root, kSetMenuTimerSub, kSetMenuSubDelayMs, nullptr);
    } else if (!wantsSub && lv.open != -1 && s->levels.size() > level + 1) {
        s->pendingLevel = (int)level;
        s->pendingItem = -1;
        SetTimer(root, kSetMenuTimerSub, kSetMenuSubDelayMs, nullptr);
    }
}

static void Set_MenuKey(WPARAM vk) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || s->levels.empty()) return;
    size_t li = s->levels.size() - 1;
    SetMenuLevel& cur = *s->levels[li];
    const auto& items = *cur.items;
    switch (vk) {
        case VK_DOWN: cur.hover = Set_MenuNext(cur, cur.hover, +1); break;
        case VK_UP: cur.hover = Set_MenuNext(cur, cur.hover, -1); break;
        case VK_HOME: cur.hover = Set_MenuNext(cur, -1, +1); break;
        case VK_END: cur.hover = Set_MenuNext(cur, (int)items.size(), -1); break;
        case VK_RIGHT:
            if (cur.hover >= 0 && !items[(size_t)cur.hover].sub.empty()) Set_MenuActivate(li, cur.hover, true);
            break;
        case VK_LEFT:
            if (li > 0) Set_MenuCloseFrom(li);
            break;
        case VK_RETURN:
        case VK_SPACE:
            if (cur.hover >= 0) Set_MenuActivate(li, cur.hover, true);
            break;
        case VK_ESCAPE:
        case VK_MENU:
            if (li > 0 && vk == VK_ESCAPE) Set_MenuCloseFrom(li);
            else Set_MenuFinish(0);
            break;
        default: return;
    }
    Set_MenuInvalidate();
}

static LRESULT CALLBACK Set_MenuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetMenuSession* s = Set_MenuCur();
    int li = Set_MenuIndexOf(hwnd);
    if (!s || li < 0) return DefWindowProcW(hwnd, msg, wParam, lParam);
    SetMenuLevel& lv = *s->levels[(size_t)li];
    switch (msg) {
        case WM_ERASEBKGND: return 1;
        case WM_MOUSEACTIVATE: return li == 0 ? MA_ACTIVATE : MA_NOACTIVATE;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (lv.rt) {
                lv.rt->BeginDraw();
                Set_MenuPaint(*s, lv);
                if (lv.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
                    RECT rc;
                    GetClientRect(hwnd, &rc);
                    lv.rt.reset();
                    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                        D2D1_RENDER_TARGET_TYPE_DEFAULT,
                        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 96 * lv.scale,
                        96 * lv.scale);
                    s->d2d->CreateHwndRenderTarget(
                        props, D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU((UINT32)rc.right, (UINT32)rc.bottom)),
                        lv.rt.put());
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (s->pendingLevel > li) {  // The pointer reached a deeper level: keep it open.
                KillTimer(s->levels[0]->hwnd, kSetMenuTimerSub);
                s->pendingItem = s->pendingLevel = -1;
            }
            TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&tme);
            int i = Set_MenuItemAt(lv, (short)LOWORD(lParam) / lv.scale, (short)HIWORD(lParam) / lv.scale);
            if (i >= 0 && !Set_MenuSelectable((*lv.items)[(size_t)i])) i = -1;
            if (i != lv.hover) {
                lv.hover = i;
                Set_MenuHoverChanged((size_t)li, i);
                Set_MenuInvalidate();
            }
            return 0;
        }
        case WM_MOUSELEAVE:
            if (lv.hover != -1 && lv.open != lv.hover) {
                lv.hover = -1;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP: {
            if (!s->pressed) return 0;  // The release of the click that opened the menu.
            int i = Set_MenuItemAt(lv, (short)LOWORD(lParam) / lv.scale, (short)HIWORD(lParam) / lv.scale);
            if (i >= 0) Set_MenuActivate((size_t)li, i, false);
            return 0;
        }
        case WM_ACTIVATE:
            if (li == 0 && LOWORD(wParam) != WA_INACTIVE) s->wasActive = true;
            if (li == 0 && LOWORD(wParam) == WA_INACTIVE && Set_MenuIndexOf((HWND)lParam) < 0) Set_MenuFinish(0);
            return 0;
        case WM_TIMER:
            if (wParam == kSetMenuTimerSub) {
                KillTimer(hwnd, kSetMenuTimerSub);
                int pl = s->pendingLevel, pi = s->pendingItem;
                s->pendingLevel = s->pendingItem = -1;
                if (pl >= 0 && (size_t)pl < s->levels.size()) {
                    if (pi >= 0) Set_MenuOpenSub((size_t)pl, pi, false);
                    else Set_MenuCloseFrom((size_t)pl + 1);
                }
            } else if (wParam == kSetMenuTimerFade) {
                float t = std::min(1.0f, (GetTickCount64() - s->fadeStart) / (float)kSetMenuFadeMs);
                s->alpha = 1 - (1 - t) * (1 - t);
                if (t >= 1) KillTimer(hwnd, kSetMenuTimerFade);
                Set_MenuInvalidate();
            } else if (wParam == kSetMenuTimerPoll) {
                // Click-away when Windows kept the menu out of the foreground: a press outside every level.
                if (GetForegroundWindow() != s->levels[0]->hwnd &&
                    ((GetAsyncKeyState(VK_LBUTTON) | GetAsyncKeyState(VK_RBUTTON) | GetAsyncKeyState(VK_MBUTTON)) & 0x8000)) {
                    POINT pt;
                    GetCursorPos(&pt);
                    if (Set_MenuIndexOf(WindowFromPoint(pt)) < 0) Set_MenuFinish(0);
                }
            }
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static int Set_TrayMenu(HWND owner, const std::vector<SetMenuItem>& items, const POINT* at = nullptr) {
    if (Set_MenuCur()) {  // A second right-click while open closes the first menu.
        Set_MenuFinish(0);
        return 0;
    }
    if (items.empty()) return 0;
    POINT pt{};
    if (at) pt = *at;
    else GetCursorPos(&pt);
    SetMenuSession session;
    if (!Set_MenuFormats(session)) return 0;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)(void*)&Set_MenuProc, &session.inst);
    // One class per mod, even when several mods share a process.
    session.cls = L"SeamlessTrayMenu_" + std::to_wstring((unsigned long long)(uintptr_t)(void*)&Set_MenuProc);
    PCWSTR cls = session.cls.c_str();
    WNDCLASSEXW wc{sizeof(wc)};
    wc.hInstance = session.inst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpfnWndProc = Set_MenuProc;
    wc.lpszClassName = cls;
    RegisterClassExW(&wc);
    session.radius = Set_MenuCornerRadius();
    Set_MenuCur() = &session;
    session.levels.push_back(std::make_unique<SetMenuLevel>());
    SetMenuLevel* root = session.levels[0].get();
    root->items = &items;
    if (!Set_MenuCreateWindow(session, *root, pt, nullptr, 0)) {
        Set_MenuCloseFrom(0);
        Set_MenuCur() = nullptr;
        UnregisterClassW(cls, session.inst);
        return 0;
    }
    BOOL animations = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &animations, 0);
    session.alpha = animations ? 0.0f : 1.0f;
    session.fadeStart = GetTickCount64();
    if (owner && IsWindow(owner)) SetForegroundWindow(owner);  // Windows' tray rule; lets the menu take the foreground.
    ShowWindow(root->hwnd, SW_SHOW);
    if (!SetForegroundWindow(root->hwnd)) {
        DWORD fg = GetWindowThreadProcessId(GetForegroundWindow(), nullptr), me = GetCurrentThreadId();
        if (fg && fg != me && AttachThreadInput(me, fg, TRUE)) {
            SetForegroundWindow(root->hwnd);
            AttachThreadInput(me, fg, FALSE);
        }
    }
    SetFocus(root->hwnd);
    if (animations) SetTimer(root->hwnd, kSetMenuTimerFade, 15, nullptr);
    SetTimer(root->hwnd, kSetMenuTimerPoll, 50, nullptr);
    MSG m;
    while (!session.done) {
        BOOL got = GetMessageW(&m, nullptr, 0, 0);
        if (got <= 0) {
            if (got == 0) PostQuitMessage((int)m.wParam);
            break;
        }
        switch (m.message) {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                Set_MenuKey(m.wParam);
                continue;
            case WM_KEYUP:
            case WM_SYSKEYUP:
            case WM_CHAR:
            case WM_SYSCHAR:
                continue;
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_NCLBUTTONDOWN:
            case WM_NCRBUTTONDOWN:
                if (Set_MenuIndexOf(m.hwnd) < 0) {  // A click on another window of this thread closes the menu.
                    Set_MenuFinish(0);
                    continue;
                }
                session.pressed = true;
                break;
        }
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    int result = session.result;
    Set_MenuCloseFrom(0);
    Set_MenuCur() = nullptr;
    UnregisterClassW(cls, session.inst);
    if (owner && IsWindow(owner)) PostMessageW(owner, WM_NULL, 0, 0);
    return result;
}


static void Set_MakeFormats(SetWindow& w) {
    w.family = Set_ResolveFamily();
    w.iconFamily = Set_FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    int base = std::clamp(500, 100, 900);
    int bold = std::max(base, std::min(700, base + 100));
    const auto L_ = DWRITE_TEXT_ALIGNMENT_LEADING, C_ = DWRITE_TEXT_ALIGNMENT_CENTER;
    w.fLabel = Set_Fmt(w.family, 16, base, true);
    w.fHint = Set_Fmt(w.family, 12.5f, base, true);
    w.fTitle = Set_Fmt(w.family, 26, bold, false);
    w.fIntro = Set_Fmt(w.family, 13.5f, base, true);
    w.fSection = Set_Fmt(w.family, 10.5f, bold, false);
    w.fValue = Set_Fmt(w.family, 13, base, false, L_, true);
    w.fValueC = Set_Fmt(w.family, 13, base, false, C_, true);
    w.fButton = Set_Fmt(w.family, 13.5f, bold, false, C_, true);
    w.fBig = Set_Fmt(w.family, 20, bold, false);
    w.fSmall = Set_Fmt(w.family, 12, base, false, L_, true);
    w.fIcon = Set_Fmt(w.iconFamily, 16, 400, false, C_, true);
    w.fIconS = Set_Fmt(w.iconFamily, 12, 400, false, C_, true);
    w.fIconL = Set_Fmt(w.iconFamily, 34, 400, false, C_, true);
    w.fCap = Set_Fmt(w.family, 13, bold, false, L_, true);
    w.fCapGlyph = Set_Fmt(w.iconFamily, 10, 400, false, C_, true);
    w.fStatusLine = Set_Fmt(w.family, 12.5f, base, false, L_, true);
    // The sidebar name must never clip at the narrowest open width: 18 down to 15.5 (above 85%).
    const float railW = kSetRailMin - 90 - 10;
    for (float size = 18; size >= 15.5f; size -= 0.5f) {
        w.fRailName = Set_Fmt(w.family, size, bold, false, L_, true);
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Afterimage") <= railW) break;
    }
}

// ---- Values ----------------------------------------------------------------

static std::wstring Set_FieldValue(const SetField& f) {
    switch (f.kind) {
        case SetField::Number: {
            if (f.cur.empty()) return f.value;
            return std::to_wstring(std::clamp(_wtoi(f.cur.c_str()), f.min, f.max));
        }
        case SetField::Check:
            return f.cur == L"0" || f.cur.empty() ? L"0" : L"1";
        default:
            return f.cur;
    }
}

static void Set_PutValue(SetField& f, const std::wstring& value) {
    switch (f.kind) {
        case SetField::Choice: {
            int index = -1;
            for (size_t i = 0; i < f.options.size(); i++) {
                if (value == f.options[i].first) index = (int)i;
            }
            for (size_t i = 0; index < 0 && i < f.options.size(); i++) {
                if (wcscmp(f.def, f.options[i].first) == 0) index = (int)i;
            }
            f.cur = f.options[std::max(index, 0)].first;
            break;
        }
        case SetField::Check:
            f.cur = value != L"0" && !value.empty() ? L"1" : L"0";
            break;
        default:
            f.cur = value;
    }
}

static void Set_LoadFields(SetWindow& w) {
    for (auto& f : w.fields) {
        bool isInt = f.kind == SetField::Number || f.kind == SetField::Check;
        Set_PutValue(f, isInt ? std::to_wstring(Wh_GetIntSetting(f.key)) : GetStringSetting(f.key));
        f.value = Set_FieldValue(f);  // What the window shows, so an untouched field never saves.
    }
}

static int Set_ChangedCount(const SetWindow& w) {
    int n = 0;
    for (auto& f : w.fields)
        if (Set_FieldValue(f) != f.value) n++;
    return n;
}

static bool Set_ParseHex(const std::wstring& text, UINT32& rgb) {
    if (text.size() != 7 || text[0] != L'#') return false;
    UINT32 v = 0;
    for (size_t i = 1; i < 7; i++) {
        WCHAR c = text[i];
        int d = c >= L'0' && c <= L'9' ? c - L'0' : c >= L'a' && c <= L'f' ? c - L'a' + 10 : c >= L'A' && c <= L'F' ? c - L'A' + 10 : -1;
        if (d < 0) return false;
        v = v * 16 + (UINT32)d;
    }
    rgb = v;
    return true;
}

static std::wstring Set_HexFromRgb(UINT32 rgb) {
    WCHAR text[16];
    swprintf_s(text, L"#%06X", rgb & 0xFFFFFF);
    return text;
}

static const wchar_t* Set_ChoiceLabel(const SetField& f) {
    for (auto& o : f.options)
        if (f.cur == o.first) return o.second;
    return f.options.empty() ? L"" : f.options[0].second;
}

static bool Set_Anim(const SetWindow& w) {
    BOOL on = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &on, 0);
    return !w.render && on;
}

static void Set_Invalidate(SetWindow& w) {
    if (w.hwnd && !w.render) InvalidateRect(w.hwnd, nullptr, FALSE);
}

static void Set_SetStatus(SetWindow& w, PCWSTR text, bool error = false) {
    w.status = text;
    w.statusError = error;
    Set_Invalidate(w);
}

// ---- Text measuring ---------------------------------------------------------

static float Set_TextH(IDWriteTextFormat* fmt, const std::wstring& text, float width) {
    SetCom<IDWriteTextLayout> l;
    if (!fmt || FAILED(g_setDw->CreateTextLayout(text.c_str(), (UINT32)text.size(), fmt, width, 10000, l.put())))
        return 18;
    DWRITE_TEXT_METRICS m{};
    l->GetMetrics(&m);
    return m.height;
}

static float Set_TextW(IDWriteTextFormat* fmt, const std::wstring& text) {
    SetCom<IDWriteTextLayout> l;
    if (!fmt || FAILED(g_setDw->CreateTextLayout(text.c_str(), (UINT32)text.size(), fmt, 10000, 100, l.put())))
        return 0;
    DWRITE_TEXT_METRICS m{};
    l->GetMetrics(&m);
    return m.widthIncludingTrailingWhitespace;
}

// Boxes grow to fit their text, so no option, hotkey or value is ever cut off: a choice box fits
// its longest option, a hotkey or text box its value. A box never takes more than half the row;
// past that the dropdown list still shows every option in full. Text is measured only when it
// changes. Returns true when a width changed, so the page is laid out again.
static bool Set_FitBoxes(SetWindow& w) {
    if (!w.fValue) return false;
    bool changed = false;
    const float cap = std::floor(w.contentW * 0.5f);
    for (auto& f : w.fields) {
        float base, pad;
        std::wstring text;
        if (f.kind == SetField::Choice) {
            base = 200, pad = 46;  // 12 before the text, 30 for the arrow, 4 spare.
            for (const auto& o : f.options) text += std::wstring(o.second) + L'\n';
        } else if (f.kind == SetField::Hotkey) {
            base = 220, pad = 60;  // The key cap's own padding and the clear button.
            text = f.cur;
        } else if (f.kind == SetField::Text) {
            base = 280, pad = 26;
            text = f.cur;
        } else {
            continue;
        }
        if (f.fitText < 0 || text != f.fitFor) {
            float m = 0;
            if (f.kind == SetField::Choice) {
                for (const auto& o : f.options) m = std::max(m, Set_TextW(w.fValue.get(), o.second));
            } else {
                m = Set_TextW(w.fValue.get(), f.cur);
            }
            f.fitText = std::ceil(m);
            f.fitFor = text;
        }
        float want = std::min(std::max(base, f.fitText + pad), std::max(base, cap));
        if (fabsf(want - f.fitW) > 0.5f) {
            f.fitW = want;
            changed = true;
        }
    }
    return changed;
}

// ---- Layout -----------------------------------------------------------------

// The right-hand control's width, so the label column knows how much room it has.
static float Set_FitOr(const SetField& f, float base) { return f.fitW > 0 ? f.fitW : base; }

static float Set_ControlW(const SetField& f) {
    switch (f.kind) {
        case SetField::Check: return 40;
        case SetField::Choice: return Set_FitOr(f, 200);
        case SetField::Number: return f.max - f.min <= 100 ? 150 + 12 + 64 : 96;
        case SetField::Text: return Set_FitOr(f, 280);
        case SetField::Hotkey: return Set_FitOr(f, 220);
        case SetField::Color: return 362;
    }
    return 100;
}

// The page scrolls under the floating footer, so the view is the full height; contentH carries
// a bottom margin (Set_FootClear) so the last row can rise above the footer.
static float Set_ViewH(const SetWindow& w) { return w.ch; }
static float Set_FootClear() { return kSetFootH + kSetFootGap + 18; }

static D2D1_RECT_F Set_RailDock(const SetWindow& w) {
    return {kSetDockGap, kSetDockGap, kSetDockGap + w.railCur, std::max(kSetDockGap + 120, w.ch - kSetDockGap)};
}
// Right edge of the sidebar dock: the page starts after it.
static float Set_RailSpace(const SetWindow& w) { return kSetDockGap + w.railCur; }
// 0 collapsed to the icon rail, 1 fully open.
static float Set_RailOpen(const SetWindow& w) {
    return std::clamp((w.railCur - kSetRailMini) / std::max(1.0f, w.railW - kSetRailMini), 0.0f, 1.0f);
}
static D2D1_RECT_F Set_RailToggleRect(const SetWindow& w) {
    D2D1_RECT_F d = Set_RailDock(w);
    return {d.left + 12, d.top + 14, d.left + 48, d.top + 50};
}

// Everything a field's control is made of, in window DIPs for a given row.
struct SetParts {
    D2D1_RECT_F box{}, track{}, clear{}, chip[kSetChipCount]{};
    bool slider = false;
};

// A colour row needs 362 DIP for its hex box and chips; when that leaves the label under 200 DIP,
// the chips drop to a line of their own under the text.
constexpr float kSgcColorFullW = 362, kSgcLabelMinW = 200, kSgcChipLine = 30;
static bool ColorRowStacked(const SetField& f, float rowW) {
    return f.kind == SetField::Color && rowW - 2 * kSetRowPad - kSgcColorFullW - 24 < kSgcLabelMinW;
}
static float RowControlW(const SetField& f, float rowW) { return ColorRowStacked(f, rowW) ? 96 : Set_ControlW(f); }

static SetParts Set_Parts(const SetField& f, const D2D1_RECT_F& row) {
    SetParts p;
    float r = row.right - kSetRowPad, mid = (row.top + row.bottom) / 2, h = kSetBoxH / 2;
    switch (f.kind) {
        case SetField::Check:
            p.box = {r - 40, mid - 11, r, mid + 11};
            break;
        case SetField::Choice:
            p.box = {r - Set_FitOr(f, 200), mid - h, r, mid + h};
            break;
        case SetField::Number:
            if (f.max - f.min <= 100) {
                p.slider = true;
                p.box = {r - 64, mid - h, r, mid + h};
                p.track = {p.box.left - 12 - 150, mid - 2, p.box.left - 12, mid + 2};
            } else {
                p.box = {r - 96, mid - h, r, mid + h};
            }
            break;
        case SetField::Text:
            p.box = {r - Set_FitOr(f, 280), mid - h, r, mid + h};
            break;
        case SetField::Hotkey:
            p.box = {r - Set_FitOr(f, 220), mid - h, r, mid + h};
            p.clear = {p.box.right - 30, p.box.top, p.box.right, p.box.bottom};
            break;
        case SetField::Color: {
            p.box = {r - 96, mid - h, r, mid + h};
            float x = p.box.left - 12 - (kSetChipCount * 26 - 6);
            for (int i = 0; i < kSetChipCount; i++) p.chip[i] = {x + i * 26, mid - 10, x + i * 26 + 20, mid + 10};
            break;
        }
    }
    return p;
}

static bool Set_In(const D2D1_RECT_F& r, float x, float y) { return x >= r.left && x < r.right && y >= r.top && y < r.bottom; }

static D2D1_RECT_F Set_RowRect(const SetWindow& w, const SetItem& it) {
    return {w.contentX, it.y, w.contentX + w.contentW, it.y + it.h};  // Content y (not scrolled).
}

// Lays out the current page's items for the current width.
static void Set_BuildPage(SetWindow& w) {
    w.items.clear();
    const float space = Set_RailSpace(w), avail = w.cw - space;
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, kSetMaxW);
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), kSetPages[w.page].intro, w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
    if (w.page == 0) {
        std::wstring status = Set_KeyStatusText();
        if (!status.empty()) {
            SetItem it;
            it.type = SetItem::Banner;
            it.text = status;
            it.y = y;
            it.h = Set_TextH(w.fHint.get(), status, w.contentW - 32) + 28;
            y += it.h + kSetRowGap + 8;
            w.items.push_back(it);
        }
    }
    PCWSTR lastGroup = nullptr;
    for (size_t k = 0; k < w.fields.size(); k++) {
        const SetField& f = w.fields[k];
        if (f.page != w.page) continue;
        if (!lastGroup || wcscmp(lastGroup, f.group) != 0) {
            SetItem g;
            g.type = SetItem::Group;
            g.text = f.group;
            y += lastGroup ? 14 : 0;
            g.y = y;
            g.h = 22;
            y += g.h + 6;
            w.items.push_back(g);
            lastGroup = f.group;
        }
        SetItem it;
        it.type = SetItem::Row;
        it.field = (int)k;
        float textW = w.contentW - 2 * kSetRowPad - RowControlW(f, w.contentW) - 24;
        float lh = Set_TextH(w.fLabel.get(), f.label, textW);
        float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh) + (ColorRowStacked(f, w.contentW) ? kSgcChipLine : 0);
        y += it.h + kSetRowGap;
        w.items.push_back(it);
    }
    if (w.page == kSetAboutPage) {
        auto add = [&](SetItem::Type t, float h, PCWSTR text, PCWSTR sub, PCWSTR url) {
            SetItem it;
            it.type = t;
            it.y = y;
            it.h = h;
            it.text = text;
            it.sub = sub;
            it.url = url;
            y += h + kSetRowGap;
            w.items.push_back(it);
        };
        auto group = [&](PCWSTR text) {
            SetItem g;
            g.type = SetItem::Group;
            g.text = text;
            g.y = y + 14;
            g.h = 22;
            y = g.y + g.h + 6;
            w.items.push_back(g);
        };
        add(SetItem::About, 146, L"", L"", L"");
        add(SetItem::Support, 84, L"Like it? Help the mod keep going.",
            L"Free and open source. A tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        add(SetItem::Link, 56, L"Based on Pointer Afterimage Motion Blur", L"By sidlikesgrapess, the cursor blur", kSetDittoUrl);
        add(SetItem::Link, 56, L"Particle and ripple look from Mouse Trail", L"By MCheng404", kSetCrossOverUrl);
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/davids-windhawk-mods", kSetRepoUrl);
        add(SetItem::Link, 56, L"Report a problem", L"Opens a new issue on GitHub, with the mod's name filled in", kSetBugUrl);
    }
    w.contentH = y + Set_FootClear();
    w.scrollTarget = std::clamp(w.scrollTarget, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
    w.scrollY = std::clamp(w.scrollY, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
}

static const SetItem* Set_ItemOfField(const SetWindow& w, int field) {
    for (auto& it : w.items)
        if (it.type == SetItem::Row && it.field == field) return &it;
    return nullptr;
}

// The footer's status line: an explicit message, else the count of unsaved changes.
static std::wstring Set_FooterStatus(const SetWindow& w, UINT32* color) {
    std::wstring status = w.status;
    if (color) *color = w.statusError ? mocha::red : (status == L"Saved" ? mocha::green : mocha::subtext0);
    int changed = Set_ChangedCount(w);
    if (status.empty() && changed)
        status = changed == 1 ? L"1 change not saved" : std::to_wstring(changed) + L" changes not saved";
    return status;
}

constexpr float kSetFootW[3] = {172, 96, 100};  // Reset to suggested, Cancel, Save.

static float Set_FooterButtonsW() { return kSetFootW[0] + kSetFootW[1] + kSetFootW[2] + 2 * 8; }

// Width the status text gets inside the footer dock (0 when there is none).
static float Set_FooterStatusW(const SetWindow& w) {
    std::wstring s = Set_FooterStatus(w, nullptr);
    if (s.empty()) return 0;
    float room = w.contentW - Set_FooterButtonsW() - 2 * kSetFootPad - 30;
    return std::max(0.0f, std::min(Set_TextW(w.fStatusLine.get(), s) + 2, room));
}

// The pill that holds the status and the three buttons, sized to fit them, right-aligned to the page.
static D2D1_RECT_F Set_FooterDock(const SetWindow& w) {
    float sw = Set_FooterStatusW(w);
    float width = Set_FooterButtonsW() + 2 * kSetFootPad + (sw > 0 ? sw + 30 : 0);
    float right = w.contentX + w.contentW, bottom = w.ch - kSetFootGap;
    return {right - width, bottom - kSetFootH, right, bottom};
}

static D2D1_RECT_F Set_FooterButton(const SetWindow& w, int which) {  // 0 reset, 1 cancel, 2 save
    D2D1_RECT_F d = Set_FooterDock(w);
    float x = d.right - kSetFootPad, top = d.top + kSetFootPad;
    D2D1_RECT_F out{};
    for (int i = 2; i >= 0; i--) {
        out = {x - kSetFootW[i], top, x, top + kSetFootBtnH};
        if (i == which) return out;
        x -= kSetFootW[i] + 8;
    }
    return out;
}

static D2D1_RECT_F Set_RailRect(const SetWindow& w, int page) {
    D2D1_RECT_F d = Set_RailDock(w);
    float y = d.top + kSetRailTop + kSetRailPitch * page + (page == kSetAboutPage ? kSetAboutGap : 0);
    return {d.left + 8, y, d.right - 8, y + kSetRailItem};
}

static D2D1_RECT_F Set_SupportButton(const SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    return {r.right - kSetRowPad - 148, (r.top + r.bottom) / 2 - 18, r.right - kSetRowPad, (r.top + r.bottom) / 2 + 18};
}

static D2D1_RECT_F Set_ScrollThumb(const SetWindow& w) {
    float view = Set_ViewH(w), range = w.contentH - view;
    if (range <= 0) return {};
    float th = std::max(36.0f, view * view / w.contentH);
    float top = (w.scrollY / range) * (view - th - 8) + 4;
    return {w.cw - 18, top + 4, w.cw - 12, top + th - 4};
}

// ---- Painting ---------------------------------------------------------------

static D2D1_COLOR_F Set_A1(float a) { return D2DColorRef(RGB(137,180,250), a); }
static D2D1_COLOR_F Set_A2(float a) { return D2DColorRef(RGB(203,166,247), a); }

static float Set_Ease(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return 1 - (1 - t) * (1 - t) * (1 - t);
}

struct SetPaint {
    SetWindow& w;
    ID2D1RenderTarget* rt;
    SetCom<ID2D1SolidColorBrush> sb;
    float fade = 1;
    SetPaint(SetWindow& win, ID2D1RenderTarget* target) : w(win), rt(target) {
        rt->CreateSolidColorBrush(D2DColor(0), sb.put());
    }
    ID2D1SolidColorBrush* B(UINT32 rgb, float a = 1) {
        sb->SetColor(D2DColor(rgb, a * fade));
        return sb.get();
    }
    // Blue to mauve, left to right across r.
    SetCom<ID2D1LinearGradientBrush> G(const D2D1_RECT_F& r, float a = 1) {
        SetCom<ID2D1LinearGradientBrush> out;
        D2D1_GRADIENT_STOP stops[2] = {{0, Set_A1(a * fade)}, {1, Set_A2(a * fade)}};
        SetCom<ID2D1GradientStopCollection> coll;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())))
            rt->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, (r.top + r.bottom) / 2),
                                                    D2D1::Point2F(std::max(r.right, r.left + 1), (r.top + r.bottom) / 2)),
                coll.get(), out.put());
        return out;
    }
    void Fill(const D2D1_RECT_F& r, UINT32 c, float a = 1) { rt->FillRectangle(r, B(c, a)); }
    void Round(const D2D1_RECT_F& r, float rad, UINT32 c, float a = 1) {
        rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), B(c, a));
    }
    void Edge(const D2D1_RECT_F& r, float rad, UINT32 c, float a, float width = 1) {
        if (a <= 0.003f) return;
        float h = width / 2;
        rt->DrawRoundedRectangle(D2D1::RoundedRect({r.left + h, r.top + h, r.right - h, r.bottom - h}, rad - h, rad - h), B(c, a), width);
    }
    void GradFill(const D2D1_RECT_F& r, float rad, float a) {
        if (a <= 0.003f) return;
        if (auto g = G(r, a)) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), g.get());
    }
    void GradRing(const D2D1_RECT_F& r, float rad, float a, float width = 1.5f) {
        if (a <= 0.003f) return;
        D2D1_RECT_F in{r.left + width / 2, r.top + width / 2, r.right - width / 2, r.bottom - width / 2};
        if (auto g = G(r, a)) rt->DrawRoundedRectangle(D2D1::RoundedRect(in, rad, rad), g.get(), width);
    }
    void Text(IDWriteTextFormat* f, const std::wstring& s, const D2D1_RECT_F& r, UINT32 c, float a = 1) {
        if (!f || s.empty()) return;
        rt->DrawText(s.c_str(), (UINT32)s.size(), f, r, B(c, a), D2D1_DRAW_TEXT_OPTIONS_CLIP);
    }
    void Glyph(IDWriteTextFormat* f, WCHAR g, const D2D1_RECT_F& r, UINT32 c, float a = 1) {
        Text(f, std::wstring(1, g), r, c, a);
    }
};

static float Set_GlowOf(const SetWindow& w, int id) {
    auto it = w.glow.find(id);
    return it == w.glow.end() ? 0 : it->second;
}

// Ids that count as "pointer is here": the row (or rail item, button, link) and the control inside it.
static void Set_HoverIds(const SetHit& h, int ids[2]) {
    ids[0] = h.id;
    ids[1] = -1;
    if (h.kind == SetHit::Control || h.kind == SetHit::Slider || h.kind == SetHit::Clear || h.kind == SetHit::Chip)
        ids[1] = 6000 + h.a;
}

static bool Set_Valid(const SetWindow& w, int k) { return k >= 0 && k < (int)w.fields.size(); }

// Value boxes: a dark fill between mantle and surface0 (crust read as black), a resting
// overlay0 edge, and the blue to mauve ring on hover or while open.
constexpr UINT32 kSetBoxFill = 0x232434;
static void Set_DrawBox(SetPaint& p, SetWindow& w, int k, const D2D1_RECT_F& box, bool active) {
    const float rad = Set_Rad(box);
    p.Round(box, rad, kSetBoxFill);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.Edge(box, rad, mocha::overlay0, 0.7f * (1 - g));
    p.GradRing(box, rad, g);
}

static void Set_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) {
    const SetField& f = w.fields[it.field];
    int k = it.field;
    D2D1_RECT_F row = Set_RowRect(w, it);
    p.Round(row, kSetRadius, mocha::base);
    p.Round(row, kSetRadius, mocha::surface0, 0.32f);
    float hov = Set_GlowOf(w, 1000 + k);
    p.Edge(row, kSetRadius, mocha::surface2, 0.55f * (1 - hov));
    p.GradFill(row, kSetRadius, 0.13f * hov);
    p.GradRing(row, kSetRadius, hov);
    if (w.kbd && w.focus == k) p.GradRing(row, kSetRadius, 1.0f);

    float textW = w.contentW - 2 * kSetRowPad - Set_ControlW(f) - 24;
    float lh = Set_TextH(w.fLabel.get(), f.label, textW);
    float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = row.top + (it.h - lh - dh) / 2;
    p.Text(w.fLabel.get(), f.label, {row.left + kSetRowPad, top, row.left + kSetRowPad + textW, top + lh + 2}, mocha::text);
    if (f.desc && *f.desc)
        p.Text(w.fHint.get(), f.desc, {row.left + kSetRowPad, top + lh + 3, row.left + kSetRowPad + textW, top + lh + dh + 3},
               mocha::subtext0);

    SetParts pt = Set_Parts(f, row);
    const D2D1_RECT_F& b = pt.box;
    switch (f.kind) {
        case SetField::Check: {
            bool on = f.cur == L"1";
            float kn = w.knob.count(k) ? w.knob.at(k) : (on ? 1.0f : 0.0f);
            D2D1_RECT_F tr = pt.box;
            p.Round(tr, 11, mocha::surface1);
            p.GradFill(tr, 11, kn);
            float cx = tr.left + 11 + kn * 18, cy = (tr.top + tr.bottom) / 2;
            p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8, 8), p.B(on ? mocha::crust : mocha::text));
            break;
        }
        case SetField::Choice: {
            Set_DrawBox(p, w, k, b, w.openSel == k);
            p.Text(w.fValue.get(), Set_ChoiceLabel(f), {b.left + 12, b.top, b.right - 30, b.bottom}, mocha::text);
            p.Glyph(w.fIconS.get(), 0xE70D, {b.right - 30, b.top, b.right - 6, b.bottom}, mocha::subtext0);
            break;
        }
        case SetField::Number: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            if (!ed) p.Text(w.fValueC.get(), Set_FieldValue(f), b, mocha::text);
            if (pt.slider) {
                float v = (float)(_wtoi(Set_FieldValue(f).c_str()) - f.min) / (float)std::max(1, f.max - f.min);
                D2D1_RECT_F tr = pt.track;
                p.Round(tr, 2, mocha::surface1);
                D2D1_RECT_F fillR{tr.left, tr.top, tr.left + (tr.right - tr.left) * v, tr.bottom};
                p.GradFill(fillR, 2, 1);
                float cx = tr.left + (tr.right - tr.left) * v, cy = (tr.top + tr.bottom) / 2;
                float kg = std::max(Set_GlowOf(w, 6000 + k), w.dragSlider == k ? 1.0f : 0.0f);
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8 + kg, 8 + kg), p.B(mocha::text));
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 5, 5), p.B(mocha::crust));
            }
            break;
        }
        case SetField::Text: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            if (!ed) p.Text(w.fValue.get(), f.cur, {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::text);
            break;
        }
        case SetField::Hotkey: {
            bool rec = w.recording == k;
            Set_DrawBox(p, w, k, b, rec);
            if (rec) {
                p.Text(w.fValue.get(), L"Press keys...", {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::blue);
            } else if (f.cur.empty()) {
                p.Text(w.fValue.get(), L"Not set", {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::overlay0);
            } else {
                float tw = std::min(Set_TextW(w.fValue.get(), f.cur) + 16, b.right - b.left - 40);
                D2D1_RECT_F cap{b.left + 6, (b.top + b.bottom) / 2 - 12, b.left + 6 + tw, (b.top + b.bottom) / 2 + 12};
                p.Round(cap, 6, mocha::surface0);
                p.Text(w.fValueC.get(), f.cur, cap, mocha::text);
                float cg = Set_GlowOf(w, 7000 + k);
                p.Glyph(w.fIconS.get(), 0xE711, pt.clear, cg > 0.5f ? mocha::red : mocha::overlay1);
            }
            break;
        }
        case SetField::Color: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            UINT32 rgb = 0;
            bool okColor = Set_ParseHex(f.cur, rgb);
            if (okColor) {
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(b.left + 17, (b.top + b.bottom) / 2), 6, 6), p.B(rgb));
            }
            if (!ed) p.Text(w.fValue.get(), f.cur, {b.left + 30, b.top, b.right - 6, b.bottom}, okColor ? mocha::text : mocha::red);
            for (int i = 0; i < kSetChipCount; i++) {
                const D2D1_RECT_F& c = pt.chip[i];
                bool sel = okColor && (rgb & 0xFFFFFF) == kSetChips[i];
                p.Round(c, 6, kSetChips[i]);
                if (sel) {
                    D2D1_RECT_F ring{c.left - 3, c.top - 3, c.right + 3, c.bottom + 3};
                    p.GradRing(ring, 8, 1, 2);
                }
            }
            break;
        }
    }
}

static void Set_DrawGroup(SetPaint& p, SetWindow& w, const SetItem& it) {
    std::wstring up = it.text;
    CharUpperBuffW(up.data(), (DWORD)up.size());
    p.Text(w.fSection.get(), up, {w.contentX + 4, it.y, w.contentX + w.contentW, it.y + it.h}, mocha::overlay2);
}

// The resting card every row uses: base, a light lift and a soft gray edge that hands over to
// the hover ring.
static void Set_DrawCard(SetPaint& p, const D2D1_RECT_F& row, float hov) {
    p.Round(row, kSetRadius, mocha::base);
    p.Round(row, kSetRadius, mocha::surface0, 0.32f);
    p.Edge(row, kSetRadius, mocha::surface2, 0.55f * (1 - hov));
}

static void Set_DrawLinkRow(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, kSetRadius, 0.13f * hov);
    p.GradRing(row, kSetRadius, hov);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), 0xE8A7, {row.right - 46, row.top, row.right - 12, row.bottom}, mocha::subtext1);
}

static void Set_DrawSupport(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float card = std::max(Set_GlowOf(w, 3700 + idx), Set_GlowOf(w, 3500 + idx));
    Set_DrawCard(p, row, card);
    p.GradFill(row, kSetRadius, 0.13f * card);
    p.GradRing(row, kSetRadius, card);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 14, row.right - 180, row.top + 36}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 38, row.right - 180, row.bottom - 6}, mocha::subtext0);
    D2D1_RECT_F b = Set_SupportButton(w, it);
    float hov = Set_GlowOf(w, 3500 + idx);
    p.GradFill(b, Set_Rad(b), 0.85f + 0.15f * hov);
    p.GradRing(b, Set_Rad(b), hov);
    p.Text(w.fButton.get(), L"Open Ko-fi", b, mocha::crust);
}

static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3800 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    D2D1_RECT_F mark{row.left + 20, row.top + 20, row.left + 92, row.top + 92};
    {  // The glyph alone in the gradient, no plate (owner, 2026-11-24).
        D2D1_MATRIX_3X2_F old;
        p.rt->GetTransform(&old);
        const D2D1_POINT_2F mc{(mark.left + mark.right) / 2, (mark.top + mark.bottom) / 2};
        p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.75f, 1.75f, mc) * old);
        const WCHAR glyph = 0xE8B0;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Pointer Afterimage Plus", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  Unlicense  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"Unlicense  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Motion blur, particle trail and click ripples for the pointer.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"By DavidHiFi, from Pointer Afterimage by sidlikesgrapess.",
           {x, row.top + 112, row.right - 16, row.bottom - 8}, mocha::overlay2);
}

static void Set_DrawBanner(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    p.Round(r, kSetRadius, mocha::peach, 0.14f);
    p.Text(w.fHint.get(), it.text, {r.left + 16, r.top + 14, r.right - 16, r.bottom - 8}, mocha::peach);
}

// A floating dock: soft shadow, mantle fill, a quiet 1px edge at rest and the blue to mauve
// edge as the pointer comes over it.
static void Set_DrawDock(SetPaint& p, SetWindow& w, const D2D1_RECT_F& d, float rad, float fill, float glow) {
    p.Round({d.left, d.top + 3, d.right, d.bottom + 5}, rad + 2, mocha::crust, w.glass ? 0.28f : 0.5f);
    p.Round(d, rad, mocha::mantle, fill);  // Hover lights only the edge: a wash showed as a blue blob down the left.
    p.Edge(d, rad, mocha::surface1, 0.75f * (1 - glow));
    p.GradRing(d, rad, glow);
}

// Panel-left mark, as in T3's sidebar button: a window with its left pane shaded while open.
static void Set_DrawPanelIcon(SetPaint& p, const D2D1_RECT_F& r, float open, UINT32 c) {
    float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    D2D1_RECT_F box{cx - 9, cy - 7.5f, cx + 9, cy + 7.5f};
    p.Round({box.left + 1, box.top + 1, box.left + 6.5f, box.bottom - 1}, 1.5f, c, 0.25f + 0.35f * open);
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(box, 3, 3), p.B(c), 1.5f);
    p.rt->DrawLine({box.left + 6.5f, box.top + 0.75f}, {box.left + 6.5f, box.bottom - 0.75f}, p.B(c), 1.5f);
}

static void Set_DrawMark(SetPaint& p, IDWriteTextFormat* glyph, const D2D1_RECT_F& r, float a);
static void Set_DrawRail(SetPaint& p, SetWindow& w) {
    D2D1_RECT_F d = Set_RailDock(w);
    const float open = Set_RailOpen(w), textA = std::clamp((open - 0.45f) / 0.55f, 0.0f, 1.0f);
    // Over the resize edge or while dragging, the dock's own rounded border brightens and
    // thickens, so the handle follows the corners instead of floating as a separate line.
    float edge = std::max(Set_GlowOf(w, 41), w.dragRail ? 1.0f : 0.0f);
    Set_DrawDock(p, w, d, kSetRadius, w.glass ? 0.58f : 1.0f, std::max(w.railGlow * 0.85f, edge));

    D2D1_RECT_F tb = Set_RailToggleRect(w);
    float th = Set_GlowOf(w, 42);
    const float tr = Set_Rad(tb);
    p.Round(tb, tr, mocha::surface0, 0.45f + 0.25f * th);
    p.GradFill(tb, tr, 0.16f * th);
    p.GradRing(tb, tr, 0.9f * th);
    if (w.kbd && w.focus == -20) p.GradRing(tb, tr, 1);
    Set_DrawPanelIcon(p, tb, open, th > 0.5f ? mocha::text : mocha::subtext1);

    p.rt->PushAxisAlignedClip(D2D1::RectF(d.left, d.top, d.right - 6, d.bottom), D2D1_ANTIALIAS_MODE_ALIASED);
    if (textA > 0.003f) {
        float my = (tb.top + tb.bottom) / 2;
        Set_DrawMark(p, w.fIcon.get(), {d.left + 56, my - 13, d.left + 82, my + 13}, textA);
    }
    p.Text(w.fRailName.get(), L"Pointer", {d.left + 90, d.top + 9, d.left + w.railW - 10, d.top + 33}, mocha::text, textA);
    p.Text(w.fRailName.get(), L"Afterimage", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
    for (int i = 0; i < kSetPageCount; i++) {
        D2D1_RECT_F r = Set_RailRect(w, i);
        if (i == kSetAboutPage) {
            float ly = std::round(r.top - (kSetAboutGap + kSetRailPitch - kSetRailItem) / 2);
            p.Fill({r.left + 6, ly, r.right - 6, ly + 1}, mocha::surface1, 0.7f);
        }
        float hov = Set_GlowOf(w, 100 + i);
        bool act = i == w.page;
        const float rr = Set_Rad(r);
        if (act) {
            p.GradFill(r, rr, 0.22f);
            p.GradRing(r, rr, 0.5f);
            D2D1_RECT_F bar{r.left, r.top + 8, r.left + 3, r.bottom - 8};
            p.GradFill({bar.left, bar.top, bar.left + 3, bar.bottom}, 1.5f, 1);
        } else {
            p.Round(r, rr, mocha::surface0, 0.28f);
            p.Edge(r, rr, mocha::surface2, 0.5f * (1 - hov));
            p.GradFill(r, rr, 0.10f * hov);
            p.GradRing(r, rr, 0.8f * hov);
        }
        if (w.kbd && w.focus == -10 - i) p.GradRing(r, rr, 1);
        UINT32 c = act ? mocha::text : mocha::subtext1;
        // The glyph sits in a fixed 44-wide slot, so it stays centered in the collapsed rail.
        p.Glyph(w.fIcon.get(), kSetPages[i].glyph, {r.left, r.top, r.left + 44, r.bottom}, act ? mocha::blue : mocha::subtext0);
        p.Text(w.fValue.get(), kSetPages[i].name, {r.left + 50, r.top, r.left + w.railW - 24, r.bottom}, c, textA);
    }
#ifdef WH_MOD_VERSION
    p.Text(w.fSmall.get(), std::wstring(L"Version ") + WH_MOD_VERSION,
           {d.left + 18, d.bottom - 34, d.left + w.railW - 12, d.bottom - 12}, mocha::overlay1, textA);
#endif
    p.rt->PopAxisAlignedClip();
}

static void Set_DrawFooter(SetPaint& p, SetWindow& w) {
    D2D1_RECT_F d = Set_FooterDock(w);
    const float rad = kSetFootH / 2, brad = kSetFootBtnH / 2;
    // The same see-through mantle as the rail dock, so the blurred rows under the pill read as
    // real glass instead of a near-solid bar.
    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : (w.glass ? 0.58f : 0.85f));
    p.Edge(d, rad, mocha::overlay0, 0.9f * (1 - w.footGlow));
    p.GradRing(d, rad, w.footGlow);
    UINT32 sc;
    std::wstring status = Set_FooterStatus(w, &sc);
    float sw = Set_FooterStatusW(w);
    if (sw > 0) p.Text(w.fStatusLine.get(), status, {d.left + 18, d.top, d.left + 18 + sw, d.bottom}, sc);
    static const PCWSTR names[3] = {L"Reset to suggested", L"Cancel", L"Save"};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_FooterButton(w, i);
        float hov = Set_GlowOf(w, 10 + i);
        p.Round(b, brad, mocha::base, 0.98f);
        p.Edge(b, brad, mocha::overlay0, 0.78f * (1 - hov));
        p.GradRing(b, brad, hov);
        p.Text(w.fButton.get(), names[i], b, mocha::text, w.saving ? 0.5f : 1.0f);
        if (w.kbd && w.focus == -1 - i) p.GradRing(b, brad, 1);
    }
}


// Every scrollbar thumb in every mod: a top to bottom blue to mauve gradient, brighter while
// hovered or dragged. Never a flat grey thumb.
static void Set_ThumbFill(SetPaint& p, const D2D1_RECT_F& r, float a) {
    if (r.bottom <= r.top) return;
    float rad = (r.right - r.left) / 2;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (SUCCEEDED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) &&
        SUCCEEDED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, r.top), D2D1::Point2F(r.left, r.bottom)),
            coll.get(), g.put())))
        p.rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), g.get());
}

static int Set_DropVisible(const SetWindow& w) {
    return w.openSel < 0 ? 0 : std::min((int)w.fields[w.openSel].options.size(), kSetDropMax);
}

// Keeps option i inside the visible part of a scrolling dropdown.
static void Set_DropShow(SetWindow& w, int i) {
    int vis = Set_DropVisible(w), n = w.openSel < 0 ? 0 : (int)w.fields[w.openSel].options.size();
    if (i < 0 || vis <= 0) return;
    if (i < w.dropTop) w.dropTop = i;
    if (i >= w.dropTop + vis) w.dropTop = i - vis + 1;
    w.dropTop = std::clamp(w.dropTop, 0, std::max(0, n - vis));
}

static void Set_DrawPopup(SetPaint& p, SetWindow& w) {
    if (w.openSel < 0) return;
    const SetField& f = w.fields[w.openSel];
    const D2D1_RECT_F& r = w.dropRect;
    const int n = (int)f.options.size(), vis = Set_DropVisible(w);
    const bool scrolls = n > vis;
    D2D1_RECT_F shadow{r.left - 1, r.top + 3, r.right + 1, r.bottom + 5};
    p.Round(shadow, kSetRadius + 2, mocha::crust, 0.6f);
    p.Round(r, kSetRadius, mocha::mantle);
    p.GradRing(r, kSetRadius, 0.9f);
    const float right = r.right - (scrolls ? 12 : 4);
    for (int v = 0; v < vis; v++) {
        int i = w.dropTop + v;
        if (i >= n) break;
        D2D1_RECT_F it{r.left + 4, r.top + 4 + v * kSetDropItem, right, r.top + 4 + (v + 1) * kSetDropItem};
        bool sel = f.cur == f.options[i].first;
        if (i == w.dropHover) {
            p.GradFill(it, Set_Rad(it, kSetRadius - 4), 0.28f);  // Inset 4 in a 16 corner: 12.
            p.GradRing(it, Set_Rad(it, kSetRadius - 4), 0.6f);
        }
        p.Text(w.fValue.get(), f.options[i].second, {it.left + 10, it.top, it.right - 28, it.bottom}, sel ? mocha::blue : mocha::text);
        if (sel) p.Glyph(w.fIconS.get(), 0xE73E, {it.right - 28, it.top, it.right - 6, it.bottom}, mocha::blue);
    }
    if (scrolls) {
        float track = r.bottom - r.top - 12, th = std::max(24.0f, track * vis / n);
        float top = r.top + 6 + (track - th) * w.dropTop / std::max(1, n - vis);
        Set_ThumbFill(p, {r.right - 9, top, r.right - 5, top + th}, 0.85f);
    }
}

// Title bar buttons, in title bar DIPs: 0 minimize, 1 maximize or restore, 2 close.
static D2D1_RECT_F Set_CapButton(const SetWindow& w, int i) {
    float right = w.cw - (2 - i) * kSetCapBtnW;
    return {right - kSetCapBtnW, 0, right, kSetCapH};
}

// y is in content DIPs, so the title bar is y < 0.
static int Set_CapButtonAt(const SetWindow& w, float x, float y) {
    if (w.nativeTitle) return -1;
    for (int i = 0; i < 3; i++)
        if (Set_In(Set_CapButton(w, i), x, y + kSetCapH)) return i;
    return -1;
}

// Icon and title are centered on the whole width, laid out from the current size on every paint,
// so a move or snap can never leave them off center.
static D2D1_RECT_F Set_CapTitleRect(const SetWindow& w) {
    float tw = std::min(Set_TextW(w.fCap.get(), kSetTitle) + 2, std::max(0.0f, w.cw - 4 * kSetCapBtnW - 40));
    float x = std::round((w.cw - (16 + 8 + tw)) / 2);
    return {x, 0, x + 16 + 8 + tw, kSetCapH};
}

static void Set_DrawMark(SetPaint& p, IDWriteTextFormat* glyph, const D2D1_RECT_F& r, float a) {
    // The mod's glyph alone in the blue to mauve gradient on a clear background, no plate
    // (owner, 2026-11-24), scaled up about its centre to fill the room the plate had.
    const float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    const float ix = (r.right - r.left) * 0.31f, iy = (r.bottom - r.top) * 0.31f;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (FAILED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) ||
        FAILED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(cx - ix, cy - iy), D2D1::Point2F(cx + ix, cy + iy)),
            coll.get(), g.put())))
        return;
    D2D1_MATRIX_3X2_F old;
    p.rt->GetTransform(&old);
    p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.4f, 1.4f, D2D1::Point2F(cx, cy)) * old);
    const WCHAR mark = 0xE8B0;
    p.rt->DrawText(&mark, 1, glyph, r, g.get());
    p.rt->SetTransform(old);
}

static void Set_DrawCaption(SetPaint& p, SetWindow& w) {
    if (!w.glass) p.Fill({0, 0, w.cw, kSetCapH}, mocha::crust);  // Glass: the window tint already covers it.
    D2D1_RECT_F t = Set_CapTitleRect(w);
    float mid = kSetCapH / 2;
    Set_DrawMark(p, w.fCapGlyph.get(), {t.left, mid - 8, t.left + 16, mid + 8}, w.active ? 1.0f : 0.6f);
    p.Text(w.fCap.get(), kSetTitle, {t.left + 24, 0, t.right, kSetCapH}, w.active ? mocha::text : mocha::overlay1);
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_CapButton(w, i);
        float hov = Set_GlowOf(w, 20 + i);
        if (w.capDown == i + 1) hov = 1;
        if (i == 2) p.Fill(b, mocha::red, 0.92f * hov);
        else p.Fill(b, mocha::surface0, 0.85f * hov);
        UINT32 c = i == 2 && hov > 0.5f ? mocha::crust : (w.active ? mocha::text : mocha::overlay1);
        WCHAR glyph = i == 0 ? 0xE921 : i == 1 ? (w.hwnd && IsZoomed(w.hwnd) ? 0xE923 : 0xE922) : 0xE8BB;
        p.Glyph(w.fCapGlyph.get(), glyph, b, c);
    }
}

// Draws the whole window into rt (DIPs). The target's DPI does the scaling.
// The title bar is drawn first; everything else is in content DIPs, shifted down by kSetCapH.
static void Set_PlaceEdit(SetWindow& w);

static void Set_DrawAutoScroll(SetPaint& p, SetWindow& w, bool frosted) {
    if (w.autoA <= 0.003f) return;
    const float a = w.autoA, s = 0.8f + 0.2f * a, r = kSetAutoR * s, cx = w.autoX, cy = w.autoY;
    const D2D1_RECT_F disc{cx - r, cy - r, cx + r, cy + r};
    p.Round(disc, r, mocha::mantle, (frosted ? 0.86f : 1.0f) * a);  // Opaque when nothing blurs under it.
    p.GradRing(disc, r - 1, a, 2);
    auto arrow = [&](float dir, bool lit) {
        SetCom<ID2D1PathGeometry> g;
        SetCom<ID2D1GeometrySink> k;
        if (FAILED(g_setD2d->CreatePathGeometry(g.put())) || FAILED(g->Open(k.put()))) return;
        const float tip = cy + dir * r * 0.62f, foot = cy + dir * r * 0.30f, half = r * 0.22f;
        k->BeginFigure(D2D1::Point2F(cx, tip), D2D1_FIGURE_BEGIN_FILLED);
        k->AddLine(D2D1::Point2F(cx + half, foot));
        k->AddLine(D2D1::Point2F(cx - half, foot));
        k->EndFigure(D2D1_FIGURE_END_CLOSED);
        if (SUCCEEDED(k->Close())) p.rt->FillGeometry(g.get(), p.B(lit ? mocha::blue : mocha::overlay1, a));
    };
    arrow(-1, w.autoDir < 0);
    arrow(1, w.autoDir > 0);
    const float d = 2.5f * s;
    p.Round({cx - d, cy - d, cx + d, cy + d}, d, mocha::mauve, a);
}

static void Set_Draw(SetWindow& w, ID2D1RenderTarget* rt) {
    if (Set_FitBoxes(w)) {
        Set_BuildPage(w);
        Set_PlaceEdit(w);
    }
    SetPaint p(w, rt);
    const auto base = D2D1::Matrix3x2F::Translation(0, kSetCapH);
    rt->BeginDraw();
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (w.glass) {
        // One tint over the whole window, title bar included, so the page and the title bar are
        // the same material. With the Windows title bar (drawn by DWM with no tint) the tint fades
        // in over the top of the page instead, so there is no step at the seam (T3 pass 24 method).
        rt->Clear(D2D1::ColorF(0, 0));
        const float total = w.ch + kSetCapH;
        if (w.nativeTitle) {
            // The window's acrylic already carries the tint (Set_ApplyFrame), title bar included.
        } else if (false) {
            SetCom<ID2D1LinearGradientBrush> fade;
            D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::crust, kSetGlassTint)}, {1, D2DColor(mocha::crust, kSetGlassTint)}};
            SetCom<ID2D1GradientStopCollection> coll;
            if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())) &&
                SUCCEEDED(rt->CreateLinearGradientBrush(
                    D2D1::LinearGradientBrushProperties(D2D1::Point2F(0, 0), D2D1::Point2F(0, kSetNativeFade)), coll.get(),
                    fade.put())))
                rt->FillRectangle(D2D1::RectF(0, 0, w.cw, kSetNativeFade), fade.get());
            p.Fill({0, kSetNativeFade, w.cw, total}, mocha::crust, kSetGlassTint);
        } else {
            p.Fill({0, 0, w.cw, total}, mocha::crust, kSetGlassTint);
        }
    } else {
        rt->Clear(D2DColor(mocha::crust));
    }
    if (!w.nativeTitle) Set_DrawCaption(p, w);
    rt->SetTransform(base);
    float viewH = Set_ViewH(w);

    auto drawPage = [&](SetPaint& cp) {
        ID2D1RenderTarget* crt = cp.rt;
        crt->PushAxisAlignedClip(D2D1::RectF(Set_RailSpace(w) + 4, 0, w.cw, viewH), D2D1_ANTIALIAS_MODE_ALIASED);
        auto place = [&](int index, float& rise) {
            float t = w.pageT >= 1 ? 1.0f : Set_Ease(w.pageT * 1.7f - std::min(index, 9) * 0.07f);
            cp.fade = t;
            rise = (1 - t) * 10;
            crt->SetTransform(D2D1::Matrix3x2F::Translation(0, -w.scrollY + rise) * base);
        };
        float rise = 0;
        place(0, rise);
        cp.Text(w.fTitle.get(), kSetPages[w.page].name, {w.contentX, 36, w.contentX + w.contentW, 72}, mocha::text);
        place(1, rise);
        cp.Text(w.fIntro.get(), kSetPages[w.page].intro, {w.contentX, 76, w.contentX + w.contentW, 76 + 40}, mocha::subtext0);
        for (size_t i = 0; i < w.items.size(); i++) {
            const SetItem& it = w.items[i];
            if (it.y + it.h < w.scrollY - 20 || it.y > w.scrollY + viewH + 20) continue;
            place((int)i + 2, rise);
            switch (it.type) {
                case SetItem::Group: Set_DrawGroup(cp, w, it); break;
                case SetItem::Row: Set_DrawRow(cp, w, it); break;
                case SetItem::Banner: Set_DrawBanner(cp, w, it); break;
                case SetItem::About: Set_DrawAbout(cp, w, it, (int)i); break;
                case SetItem::Link: Set_DrawLinkRow(cp, w, it, (int)i); break;
                case SetItem::Support: Set_DrawSupport(cp, w, it, (int)i); break;
            }
        }
        cp.fade = 1;
        crt->SetTransform(base);
        crt->PopAxisAlignedClip();
    };

    // The footer dock floats over the page with a real blur of the rows under it, clipped to the
    // pill, all in this window. (An owned popup with its own backdrop showed square corners:
    // DWM paints an accent backdrop over the full window rectangle and ignores the region.)
    const D2D1_SIZE_F full = D2D1::SizeF(w.cw, w.ch + kSetCapH);
    bool blurred = false;
    if (!w.render) {
        if (w.layer && (w.layerSize.width != full.width || w.layerSize.height != full.height)) w.layer.reset();
        if (!w.layer && SUCCEEDED(rt->CreateCompatibleRenderTarget(full, w.layer.put()))) w.layerSize = full;
        SetCom<ID2D1Bitmap> page;
        SetCom<ID2D1DeviceContext> dc;
        SetCom<ID2D1Effect> blur;
        SetCom<ID2D1RoundedRectangleGeometry> pill;
        SetCom<ID2D1RectangleGeometry> all;
        SetCom<ID2D1PathGeometry> rest;
        D2D1_RECT_F d = Set_FooterDock(w);
        d.top += kSetCapH, d.bottom += kSetCapH;
        const float rad = kSetFootH / 2;
        if (w.layer && SUCCEEDED(rt->QueryInterface(__uuidof(ID2D1DeviceContext), (void**)dc.put())) &&
            SUCCEEDED(dc->CreateEffect(CLSID_D2D1GaussianBlur, blur.put())) &&
            SUCCEEDED(g_setD2d->CreateRoundedRectangleGeometry(D2D1::RoundedRect(d, rad, rad), pill.put())) &&
            SUCCEEDED(g_setD2d->CreateRectangleGeometry(D2D1::RectF(0, 0, full.width, full.height), all.put())) &&
            SUCCEEDED(g_setD2d->CreatePathGeometry(rest.put()))) {
            SetCom<ID2D1GeometrySink> sink;
            bool ok = SUCCEEDED(rest->Open(sink.put())) &&
                      SUCCEEDED(all->CombineWithGeometry(pill.get(), D2D1_COMBINE_MODE_EXCLUDE, nullptr, sink.get())) &&
                      SUCCEEDED(sink->Close());
            ID2D1BitmapRenderTarget* lt = w.layer.get();
            if (ok) {
                SetPaint lp(w, lt);
                lt->BeginDraw();
                lt->SetTransform(D2D1::Matrix3x2F::Identity());
                lt->Clear(D2D1::ColorF(0, 0));
                lt->SetTransform(base);
                drawPage(lp);
                ok = SUCCEEDED(lt->EndDraw()) && SUCCEEDED(lt->GetBitmap(page.put()));
            }
            if (!ok) w.layer.reset();
            if (ok) {
                rt->SetTransform(D2D1::Matrix3x2F::Identity());
                rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), rest.get()), nullptr);
                rt->DrawBitmap(page.get());
                rt->PopLayer();
                blur->SetInput(0, page.get());
                blur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 9.0f);
                blur->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
                rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pill.get()), nullptr);
                D2D1_RECT_F src{d.left - 1, d.top - 1, d.right + 1, d.bottom + 1};
                dc->DrawImage(blur.get(), D2D1::Point2F(src.left, src.top), src);
                rt->PopLayer();
                if (w.autoA > 0.003f) {  // The autoscroll disc frosts the rows under it the same way.
                    const float r = kSetAutoR * (0.8f + 0.2f * w.autoA), cx = w.autoX, cy = w.autoY + kSetCapH;
                    SetCom<ID2D1EllipseGeometry> disc;
                    if (SUCCEEDED(g_setD2d->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(cx, cy), r, r), disc.put()))) {
                        rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), disc.get()), nullptr);
                        D2D1_RECT_F ds{cx - r - 1, cy - r - 1, cx + r + 1, cy + r + 1};
                        dc->DrawImage(blur.get(), D2D1::Point2F(ds.left, ds.top), ds);
                        rt->PopLayer();
                    }
                }
                blurred = true;
            }
        }
    }
    if (!blurred) drawPage(p);
    rt->SetTransform(base);

    D2D1_RECT_F th = Set_ScrollThumb(w);
    Set_ThumbFill(p, th, w.dragScroll || w.hover.kind == SetHit::Scroll ? 1.0f : 0.7f);

    Set_DrawFooter(p, w);
    Set_DrawRail(p, w);
    Set_DrawPopup(p, w);
    Set_DrawAutoScroll(p, w, blurred);
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (false) p.GradRing({0, 0, w.cw, w.ch + kSetCapH}, SystemCornerRadius(false), 1, 1);
    HRESULT hr = rt->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) w.rt.reset(), w.layer.reset();
}

// ---- Hit testing --------------------------------------------------------------

static SetHit Set_Hit(SetWindow& w, float x, float y) {
    SetHit h;
    if (y < 0) {
        int b = Set_CapButtonAt(w, x, y);
        if (b >= 0) {
            h.kind = SetHit::Caption;
            h.a = b;
            h.id = 20 + b;
        }
        return h;
    }
    if (w.openSel >= 0) {
        if (Set_In(w.dropRect, x, y)) {
            int v = (int)((y - w.dropRect.top - 4) / kSetDropItem), i = w.dropTop + v;
            if (v >= 0 && v < Set_DropVisible(w) && i < (int)w.fields[w.openSel].options.size() &&
                y >= w.dropRect.top + 4 && x < w.dropRect.right - (Set_DropVisible(w) < (int)w.fields[w.openSel].options.size() ? 12 : 4)) {
                h.kind = SetHit::Drop;
                h.a = w.openSel;
                h.b = i;
            } else {
                h.kind = SetHit::Popup;
            }
        }
        return h;
    }
    D2D1_RECT_F dock = Set_RailDock(w);
    if (y >= dock.top + 14 && y < dock.bottom - 14 && fabsf(x - dock.right) <= kSetEdgeGrab) {
        h.kind = SetHit::RailEdge;
        h.id = 41;
        return h;
    }
    if (x < dock.right + kSetDockGap) {
        if (Set_In(Set_RailToggleRect(w), x, y)) {
            h.kind = SetHit::RailToggle;
            h.id = 42;
            return h;
        }
        for (int i = 0; i < kSetPageCount; i++) {
            if (Set_In(Set_RailRect(w, i), x, y)) {
                h.kind = SetHit::Rail;
                h.a = i;
                h.id = 100 + i;
                return h;
            }
        }
        return h;
    }
    D2D1_RECT_F foot = Set_FooterDock(w);
    if (Set_In(foot, x, y)) {
        for (int i = 0; i < 3; i++) {
            if (Set_In(Set_FooterButton(w, i), x, y)) {
                h.kind = SetHit::Footer;
                h.a = i;
                h.id = 10 + i;
                return h;
            }
        }
        return h;
    }
    D2D1_RECT_F th = Set_ScrollThumb(w);
    if (th.bottom > th.top && x >= w.cw - 16 && y >= th.top && y <= th.bottom) {
        h.kind = SetHit::Scroll;
        return h;
    }
    float cy = y + w.scrollY;
    for (size_t i = 0; i < w.items.size(); i++) {
        const SetItem& it = w.items[i];
        D2D1_RECT_F row = Set_RowRect(w, it);
        if (!Set_In(row, x, cy)) continue;
        if (it.type == SetItem::Link) {
            h.kind = SetHit::Link;
            h.a = (int)i;
            h.id = 3000 + (int)i;
        } else if (it.type == SetItem::Support) {
            h.id = 3700 + (int)i;  // The card lights up; only its button clicks.
            if (Set_In(Set_SupportButton(w, it), x, cy)) {
                h.kind = SetHit::Link;
                h.a = (int)i;
                h.id = 3500 + (int)i;
            }
        } else if (it.type == SetItem::About) {
            h.id = 3800 + (int)i;
        } else if (it.type == SetItem::Row) {
            const SetField& f = w.fields[it.field];
            SetParts pt = Set_Parts(f, row);
            h.a = it.field;
            h.id = 1000 + it.field;
            h.kind = f.kind == SetField::Check ? SetHit::Control : SetHit::Row;
            if (f.kind == SetField::Hotkey && !f.cur.empty() && w.recording != it.field && Set_In(pt.clear, x, cy)) {
                h.kind = SetHit::Clear;
            } else if (f.kind == SetField::Color) {
                for (int c = 0; c < kSetChipCount; c++) {
                    if (Set_In(pt.chip[c], x, cy)) {
                        h.kind = SetHit::Chip;
                        h.b = c;
                    }
                }
                if (h.kind != SetHit::Chip && Set_In(pt.box, x, cy)) h.kind = SetHit::Control;
            } else if (pt.slider &&
                       Set_In({pt.track.left - 8, pt.track.top - 10, pt.track.right + 8, pt.track.bottom + 10}, x, cy)) {
                h.kind = SetHit::Slider;
            } else if (Set_In(pt.box, x, cy)) {
                h.kind = SetHit::Control;
            }
        }
        return h;
    }
    return h;
}

static bool Set_Clickable(const SetHit& h) {
    return h.kind == SetHit::Rail || h.kind == SetHit::Footer || h.kind == SetHit::Control || h.kind == SetHit::Slider ||
           h.kind == SetHit::Clear || h.kind == SetHit::Chip || h.kind == SetHit::Drop || h.kind == SetHit::Link ||
           h.kind == SetHit::Scroll || h.kind == SetHit::RailToggle;
}

// Sidebar width from a drag: below the snap point it collapses to the icon rail.
static void Set_RailDragTo(SetWindow& w, float x) {
    float width = x - kSetDockGap;
    if (width < kSetRailSnap) {
        w.railCollapsed = true;
    } else {
        w.railCollapsed = false;
        w.railW = std::clamp(width, kSetRailMin, kSetRailMax);
        w.railCur = w.railW;
    }
    Set_BuildPage(w);
    Set_Invalidate(w);
}

static void Set_ToggleRail(SetWindow& w) {
    w.railCollapsed = !w.railCollapsed;
    if (!w.railCollapsed && w.railCur < kSetRailMini) w.railCur = kSetRailMini;
    Set_Invalidate(w);
}

// ---- Editing, recording, choosing -----------------------------------------------

static std::wstring Set_FormatHotkey(UINT mods, UINT vk) {
    std::wstring text = std::to_wstring(vk);
    if (!text.empty()) return text;
    // Fallback while the capture part is a stub.
    if (mods & MOD_CONTROL) text += L"Ctrl+";
    if (mods & MOD_ALT) text += L"Alt+";
    if (mods & MOD_SHIFT) text += L"Shift+";
    if (mods & MOD_WIN) text += L"Win+";
    WCHAR name[64] = {};
    LONG scan = (LONG)MapVirtualKeyW(vk, MAPVK_VK_TO_VSC) << 16;
    if (GetKeyNameTextW(scan, name, ARRAYSIZE(name)) > 0) {
        text += name;
    } else {
        text += std::to_wstring(vk);
    }
    return text;
}

static bool Set_IsModifier(UINT vk) {
    switch (vk) {
        case VK_SHIFT: case VK_LSHIFT: case VK_RSHIFT:
        case VK_CONTROL: case VK_LCONTROL: case VK_RCONTROL:
        case VK_MENU: case VK_LMENU: case VK_RMENU:
        case VK_LWIN: case VK_RWIN:
            return true;
    }
    return false;
}

static void Set_StopRecording(SetWindow& w) {
    if (w.recording < 0) return;
    w.recording = -1;
    if (w.status.rfind(L"Press the keys", 0) == 0) Set_SetStatus(w, L"");
    
    Set_Invalidate(w);
}

static void Set_StartRecording(SetWindow& w, int k) {
    Set_StopRecording(w);
    w.recording = k;
    // Our own keys would fire instead of reaching the window while it listens.
    if (!w.render) {
        SetFocus(w.hwnd);
    }
    Set_SetStatus(w, L"Press the keys you want. Esc cancels, Backspace clears.");
}

static void Set_ClosePopup(SetWindow& w) {
    if (w.openSel < 0) return;
    w.openSel = -1;
    w.dropHover = -1;
    w.dropTop = 0;
    Set_Invalidate(w);
}

static void Set_OpenPopup(SetWindow& w, int k) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    const SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float boxTop = pt.box.top - w.scrollY, boxBottom = pt.box.bottom - w.scrollY;
    const int n = (int)f.options.size(), vis = std::min(n, kSetDropMax);
    float h = (float)vis * kSetDropItem + 8;
    float top = boxBottom + 4;
    if (top + h > Set_ViewH(w) + 20 && boxTop - 4 - h > 0) top = boxTop - 4 - h;  // No room below: open upward.
    // As wide as the longest option (text, check mark, scrollbar), growing leftward from the box.
    float textW = 0;
    for (const auto& o : f.options) textW = std::max(textW, Set_TextW(w.fValue.get(), o.second));
    float width = std::max(pt.box.right - pt.box.left, std::ceil(textW) + 52 + (n > vis ? 8 : 0));
    float left = std::max(pt.box.right - width, Set_RailSpace(w) + 8);
    w.dropRect = {left, top, std::max(pt.box.right, left + width), top + h};
    w.openSel = k;
    w.dropHover = -1;
    w.dropTop = 0;
    for (int i = 0; i < n; i++)
        if (f.cur == f.options[i].first) w.dropHover = i;
    Set_DropShow(w, w.dropHover);
    Set_Invalidate(w);
}

static void Set_CommitEdit(SetWindow& w, bool apply) {
    if (w.editing < 0) return;
    int k = w.editing;
    w.editing = -1;  // Hiding the box ends its focus; this stops that from coming back here.
    SetField& f = w.fields[k];
    std::wstring text = w.edit ? Set_WindowText(w.edit) : L"";
    if (w.edit) ShowWindow(w.edit, SW_HIDE);
    if (apply) {
        switch (f.kind) {
            case SetField::Number:
                if (!text.empty()) f.cur = std::to_wstring(std::clamp(_wtoi(text.c_str()), f.min, f.max));
                break;
            case SetField::Color: {
                while (!text.empty() && text.back() == L' ') text.pop_back();
                while (!text.empty() && text.front() == L' ') text.erase(0, 1);
                if (!text.empty() && text[0] != L'#') text = L"#" + text;
                UINT32 rgb;
                if (Set_ParseHex(text, rgb)) {
                    f.cur = Set_HexFromRgb(rgb);
                    Set_SetStatus(w, L"");
                } else {
                    Set_SetStatus(w, L"Use a color like #89B4FA.", true);
                }
                break;
            }
            default:
                f.cur = text;
        }
    }
    if (!w.render && w.hwnd) SetFocus(w.hwnd);
    Set_Invalidate(w);
}

static void Set_PlaceEdit(SetWindow& w) {
    if (w.editing < 0 || !w.edit) return;
    const SetItem* it = Set_ItemOfField(w, w.editing);
    if (!it) return;
    SetParts pt = Set_Parts(w.fields[w.editing], Set_RowRect(w, *it));
    float left = pt.box.left + (w.fields[w.editing].kind == SetField::Color ? 30 : 10), right = pt.box.right - 8;
    float mid = (pt.box.top + pt.box.bottom) / 2 - w.scrollY + kSetCapH;
    float s = w.dpi / 96.0f;
    SetWindowPos(w.edit, HWND_TOP, (int)(left * s), (int)((mid - 10) * s), (int)((right - left) * s), (int)(20 * s),
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

static LRESULT CALLBACK Set_EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR) {
    SetWindow* w = g_setWin.get();
    if (w && w->edit == hwnd) {
        switch (msg) {
            case WM_KEYDOWN:
                if (wParam == VK_RETURN || wParam == VK_TAB) {
                    Set_CommitEdit(*w, true);
                    return 0;
                }
                if (wParam == VK_ESCAPE) {
                    Set_CommitEdit(*w, false);
                    return 0;
                }
                break;
            case WM_CHAR:
                if (wParam == VK_RETURN || wParam == VK_ESCAPE || wParam == VK_TAB) return 0;  // No beep.
                break;
            case WM_KILLFOCUS:
                if (w->editing >= 0) Set_CommitEdit(*w, true);
                break;
        }
    }
    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

static void Set_BeginEdit(SetWindow& w, int k) {
    Set_CommitEdit(w, true);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    SetField& f = w.fields[k];
    if (w.edit) DestroyWindow(w.edit);
    if (w.editFont) DeleteObject(w.editFont);
    DWORD style = WS_CHILD | ES_AUTOHSCROLL | (f.kind == SetField::Number ? ES_NUMBER | ES_CENTER : 0);
    // Over the extended frame GDI text would come out see-through; a layered child keeps it solid.
    w.edit = CreateWindowExW(w.glass ? WS_EX_LAYERED : 0, L"EDIT", L"", style, 0, 0, 10, 10, w.hwnd, nullptr,
                             GetModuleHandleW(nullptr), nullptr);
    if (!w.edit) return;
    if (w.glass) SetLayeredWindowAttributes(w.edit, 0, 255, LWA_ALPHA);
    int base = std::clamp(500, 100, 900);
    w.editFont = CreateFontW(-MulDiv(13, w.dpi, 96), 0, 0, 0, base, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                             CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, w.family.c_str());
    SendMessageW(w.edit, WM_SETFONT, (WPARAM)w.editFont, TRUE);
    SendMessageW(w.edit, EM_SETLIMITTEXT, f.kind == SetField::Number ? 6 : f.kind == SetField::Color ? 7 : 260, 0);
    SetWindowTextW(w.edit, f.kind == SetField::Number ? Set_FieldValue(f).c_str() : f.cur.c_str());
    SetWindowSubclass(w.edit, Set_EditProc, 1, 0);
    w.editing = k;
    Set_PlaceEdit(w);
    if (!w.render) SetFocus(w.edit);
    SendMessageW(w.edit, EM_SETSEL, 0, -1);
    Set_Invalidate(w);
}

static void Set_Choose(SetWindow& w, int k, int option) {
    SetField& f = w.fields[k];
    if (option >= 0 && option < (int)f.options.size()) f.cur = f.options[option].first;
    Set_ClosePopup(w);
}

static void Set_SliderTo(SetWindow& w, int k, float x) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float t = std::clamp((x - pt.track.left) / (pt.track.right - pt.track.left), 0.0f, 1.0f);
    f.cur = std::to_wstring(f.min + (int)(t * (f.max - f.min) + 0.5f));
    Set_Invalidate(w);
}

static void Set_Save(std::shared_ptr<SetWindow> keep);

static void Set_ResetToSuggested(SetWindow& w) {
    Set_CommitEdit(w, false);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    for (auto& f : w.fields) Set_PutValue(f, f.def);
    Set_SetStatus(w, L"Suggested values are filled in. Press Save to keep them.");
}

static void Set_BuildAndClamp(SetWindow& w) {
    Set_BuildPage(w);
    Set_PlaceEdit(w);
    Set_Invalidate(w);
}

static void Set_GoPage(SetWindow& w, int page) {
    page = std::clamp(page, 0, kSetPageCount - 1);
    Set_CommitEdit(w, true);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    if (page == w.page) return;
    w.page = page;
    w.scrollY = w.scrollTarget = 0;
    w.focus = -1;
    w.pageT = Set_Anim(w) ? 0.0f : 1.0f;
    Set_BuildAndClamp(w);
}

static void Set_OpenLink(PCWSTR url) {
#ifdef SCM_HARNESS
    Wh_Log(L"settings: would open %s", url);
#else
    ShellExecuteW(nullptr, L"open", url, nullptr, nullptr, SW_SHOWNORMAL);
#endif
}

// A click (or Space or Enter) on a field's control.
static void Set_ActivateField(SetWindow& w, int k, const SetHit* hit) {
    SetField& f = w.fields[k];
    if (w.recording >= 0 && w.recording != k) Set_StopRecording(w);
    switch (f.kind) {
        case SetField::Check:
            f.cur = f.cur == L"1" ? L"0" : L"1";
            Set_Invalidate(w);
            break;
        case SetField::Choice:
            if (w.openSel == k) {
                Set_ClosePopup(w);
            } else {
                Set_CommitEdit(w, true);
                Set_OpenPopup(w, k);
            }
            break;
        case SetField::Number:
        case SetField::Text:
            Set_BeginEdit(w, k);
            break;
        case SetField::Color:
            if (hit && hit->kind == SetHit::Chip) {
                Set_CommitEdit(w, false);
                f.cur = Set_HexFromRgb(kSetChips[hit->b]);
                Set_SetStatus(w, L"");
            } else {
                Set_BeginEdit(w, k);
            }
            break;
        case SetField::Hotkey:
            if (hit && hit->kind == SetHit::Clear) {
                f.cur.clear();
                Set_Invalidate(w);
            } else if (w.recording == k) {
                Set_StopRecording(w);
            } else {
                Set_CommitEdit(w, true);
                Set_StartRecording(w, k);
            }
            break;
    }
}

static void Set_FooterAction(SetWindow& w, int which) {
    if (which == 0) {
        Set_ResetToSuggested(w);
    } else if (which == 1) {
        if (!w.render) DestroyWindow(w.hwnd);  // w is gone after this.
    } else {
        Set_CommitEdit(w, true);
        if (g_setWin && g_setWin->hwnd == w.hwnd) Set_Save(g_setWin);
    }
}

// ---- Saving ---------------------------------------------------------------------

static std::wstring Set_ChangedParams(SetWindow& w, int& changed) {
    std::wstring params = L"--quiet mod settings set " + Set_QuoteArg(WH_MOD_ID);
    changed = 0;
    for (auto& f : w.fields) {
        std::wstring value = Set_FieldValue(f);
        if (value != f.value) {
            params += L" " + Set_QuoteArg(std::wstring(f.key) + L"=" + value);
            changed++;
        }
    }
    return params;
}

static void Set_ApplyFrame(SetWindow& w);

static void Set_Save(std::shared_ptr<SetWindow> keep) {
    SetWindow& w = *keep;
    if (w.saving) return;
    Set_StopRecording(w);
    int changed = 0;
    std::wstring params = Set_ChangedParams(w, changed);
    if (!changed) {
        Set_SetStatus(w, L"Nothing changed");
        return;
    }
    std::wstring cli = Set_CliPath();
#ifdef SCM_HARNESS
    // Tests check the command instead of running it.
    std::string line = WideToUtf8(Set_QuoteArg(cli.empty() ? L"windhawk-cli.exe" : cli) + L" " + params);
    HANDLE file = CreateFileW((StoragePath() + L"\\settings-save.txt").c_str(), GENERIC_WRITE, 0, nullptr,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    bool ok = file != INVALID_HANDLE_VALUE && WriteFile(file, line.data(), (DWORD)line.size(), &written, nullptr);
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    if (!ok) {
        Set_SetStatus(w, L"Couldn't write settings-save.txt", true);
        return;
    }
    for (auto& f : w.fields) f.value = Set_FieldValue(f);
    Set_SetStatus(w, L"Saved");
    return;
#else
    if (cli.empty()) {
        Set_SetStatus(w, L"Couldn't find windhawk-cli.exe, so nothing was saved", true);
        return;
    }
    SHELLEXECUTEINFOW info{sizeof(info)};
    info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;
    info.hwnd = w.hwnd;
    info.lpVerb = L"runas";
    info.lpFile = cli.c_str();
    info.lpParameters = params.c_str();
    info.nShow = SW_HIDE;
    if (!ShellExecuteExW(&info) || !info.hProcess) {
        DWORD error = GetLastError();
        if (error == ERROR_CANCELLED) {
            Set_SetStatus(w, L"Not saved. The admin prompt was turned down.", true);
        } else {
            WCHAR text[96];
            swprintf_s(text, L"Couldn't start windhawk-cli (error %lu)", error);
            Set_SetStatus(w, text, true);
        }
        return;
    }
    w.saving = true;
    Set_SetStatus(w, L"Saving...");
    // Keep painting and handling input while windhawk-cli works.
    bool quit = false, timedOut = false;
    int quitCode = 0;
    ULONGLONG deadline = GetTickCount64() + 15000;
    while (!quit && !w.destroyed) {
        ULONGLONG now = GetTickCount64();
        if (now >= deadline) {
            timedOut = true;
            break;
        }
        DWORD r = MsgWaitForMultipleObjects(1, &info.hProcess, FALSE, (DWORD)(deadline - now), QS_ALLINPUT);
        if (r == WAIT_OBJECT_0) break;
        if (r != WAIT_OBJECT_0 + 1) {
            timedOut = r == WAIT_TIMEOUT;
            break;
        }
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                quit = true;
                quitCode = (int)msg.wParam;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    DWORD code = 1;
    bool finished = WaitForSingleObject(info.hProcess, 0) == WAIT_OBJECT_0;
    if (finished) GetExitCodeProcess(info.hProcess, &code);
    if (!finished) TerminateProcess(info.hProcess, ERROR_TIMEOUT);
    CloseHandle(info.hProcess);
    w.saving = false;
    if (quit) PostQuitMessage(quitCode);
    if (w.destroyed || !IsWindow(w.hwnd)) return;
    if (!finished && timedOut) {
        Set_SetStatus(w, L"Windhawk didn't answer in 15 seconds. Settings may not be saved.", true);
    } else if (code == 0) {
        Set_LoadFields(w);  // Shows what was stored.
        Set_ApplyFrame(w);  // The title bar and glass switches take effect now, no reopen.
        Set_SetStatus(w, L"Saved");
    } else {
        Wh_Log(L"windhawk-cli exit code %lu", code);
        WCHAR text[96];
        swprintf_s(text, L"Windhawk didn't save the settings (code %lu)", code);
        Set_SetStatus(w, text, true);
    }
#endif
}

// ---- Animation tick ----------------------------------------------------------------

static bool Set_AutoScrollStart(SetWindow& w, float x, float y) {
    if (w.render || w.contentH - Set_ViewH(w) <= 0) return false;  // Nothing to scroll.
    Set_CommitEdit(w, true);
    Set_ClosePopup(w);
    w.autoScroll = true;
    w.autoMoved = false;
    w.autoX = x, w.autoY = y, w.autoDir = 0;
    w.hover = SetHit();
    SetCapture(w.hwnd);
    SetCursor(LoadCursorW(nullptr, IDC_SIZENS));
    Set_Invalidate(w);
    return true;
}

static void Set_AutoScrollStop(SetWindow& w) {
    if (!w.autoScroll) return;
    w.autoScroll = false;  // Before ReleaseCapture: its WM_CAPTURECHANGED comes straight back here.
    w.autoDir = 0;
    if (GetCapture() == w.hwnd) ReleaseCapture();
    Set_Invalidate(w);
}

static void Set_AutoScrollMove(SetWindow& w, bool held) {
    if (held && fabsf(w.mouseY - w.autoY) > kSetAutoDead) w.autoMoved = true;
    SetCursor(LoadCursorW(nullptr, IDC_SIZENS));
}

static bool Set_AutoScrollStep(SetWindow& w) {
    if (!w.autoScroll) return false;
    const float dy = w.mouseY - w.autoY, dist = fabsf(dy) - kSetAutoDead;
    const float dir = dist > 0 ? (dy > 0 ? 1.0f : -1.0f) : 0.0f;
    bool changed = dir != w.autoDir;
    w.autoDir = dir;
    if (dist <= 0) return changed;
    const float maxScroll = std::max(0.0f, w.contentH - Set_ViewH(w));
    const float next = std::clamp(w.scrollY + dir * std::min(kSetAutoMax, dist * kSetAutoGain), 0.0f, maxScroll);
    if (next == w.scrollY) return changed;
    w.scrollY = w.scrollTarget = next;
    Set_PlaceEdit(w);
    return true;
}

static bool Set_Tick(SetWindow& w) {
    bool moved = false, anim = Set_Anim(w);
    auto step = [&](float& v, float target, float rate) {
        float d = target - v;
        if (!anim || fabsf(d) < 0.02f) {
            if (v != target) {
                v = target;
                moved = true;
            }
            return;
        }
        v += d * rate;
        moved = true;
    };
    int ids[2];
    Set_HoverIds(w.hover, ids);
    for (int id : ids)
        if (id >= 0 && !w.glow.count(id)) w.glow[id] = 0;
    for (auto it = w.glow.begin(); it != w.glow.end();) {
        bool on = it->first == ids[0] || it->first == ids[1];
        step(it->second, on ? 1.0f : 0.0f, 0.3f);
        if (!on && it->second == 0) {
            it = w.glow.erase(it);
        } else {
            ++it;
        }
    }
    for (size_t k = 0; k < w.fields.size(); k++) {
        if (w.fields[k].kind != SetField::Check) continue;
        float target = w.fields[k].cur == L"1" ? 1.0f : 0.0f;
        if (!w.knob.count((int)k)) w.knob[(int)k] = target;
        step(w.knob[(int)k], target, 0.35f);
    }
    if (Set_AutoScrollStep(w)) moved = true;
    step(w.autoA, w.autoScroll ? 1.0f : 0.0f, 0.3f);
    if (w.scrollY != w.scrollTarget) {
        float d = w.scrollTarget - w.scrollY;
        if (!anim || fabsf(d) < 0.5f) {
            w.scrollY = w.scrollTarget;
        } else {
            w.scrollY += d * 0.25f;
        }
        moved = true;
        Set_PlaceEdit(w);
    }
    if (w.pageT < 1) {
        w.pageT = anim ? std::min(1.0f, w.pageT + 0.07f) : 1.0f;
        moved = true;
    }
    // Sidebar open / collapse, and the dock edges lighting up under the pointer.
    if (!w.dragRail) {
        float target = w.railCollapsed ? kSetRailMini : w.railW, d = target - w.railCur;
        if (d != 0) {
            w.railCur = (!anim || fabsf(d) < 0.6f) ? target : w.railCur + d * 0.28f;
            Set_BuildPage(w);
            Set_PlaceEdit(w);
            moved = true;
        }
    }
    bool inRail = w.mouseX >= 0 && Set_In(Set_RailDock(w), w.mouseX, w.mouseY);
    D2D1_RECT_F foot = Set_FooterDock(w);
    bool inFoot = w.mouseX >= 0 && Set_In(foot, w.mouseX, w.mouseY);
    step(w.railGlow, inRail ? 1.0f : 0.0f, 0.25f);
    step(w.footGlow, inFoot ? 1.0f : 0.0f, 0.25f);
    return moved;
}

// ---- Keyboard focus ----------------------------------------------------------------

// Focus order: the page's rows, then Reset, Cancel, Save (-1, -2, -3).
static std::vector<int> Set_FocusOrder(const SetWindow& w) {
    std::vector<int> order;
    for (auto& it : w.items)
        if (it.type == SetItem::Row) order.push_back(it.field);
    order.push_back(-1);
    order.push_back(-2);
    order.push_back(-3);
    return order;
}

static void Set_EnsureVisible(SetWindow& w, float top, float bottom) {
    float view = Set_ViewH(w);
    float clear = Set_FootClear() - 18;  // Keep focused rows above the floating footer.
    if (top - 16 < w.scrollTarget) {
        w.scrollTarget = top - 16;
    } else if (bottom + 16 + clear > w.scrollTarget + view) {
        w.scrollTarget = bottom + 16 + clear - view;
    }
    w.scrollTarget = std::clamp(w.scrollTarget, 0.0f, std::max(0.0f, w.contentH - view));
}

static void Set_MoveFocus(SetWindow& w, int dir) {
    Set_CommitEdit(w, true);
    Set_ClosePopup(w);
    std::vector<int> order = Set_FocusOrder(w);
    int index = -1;
    for (size_t i = 0; i < order.size(); i++)
        if (order[i] == w.focus) index = (int)i;
    index = index < 0 ? (dir > 0 ? 0 : (int)order.size() - 1) : (index + dir + (int)order.size()) % (int)order.size();
    w.focus = order[index];
    w.kbd = true;
    if (w.focus >= 0) {
        if (const SetItem* it = Set_ItemOfField(w, w.focus)) Set_EnsureVisible(w, it->y, it->y + it->h);
    }
    Set_Invalidate(w);
}

static void Set_Adjust(SetWindow& w, int dir) {
    if (w.focus < 0) return;
    SetField& f = w.fields[w.focus];
    if (f.kind == SetField::Number) {
        int span = f.max - f.min, step = span <= 100 ? 1 : span <= 3000 ? 10 : 100;
        f.cur = std::to_wstring(std::clamp(_wtoi(Set_FieldValue(f).c_str()) + dir * step, f.min, f.max));
    } else if (f.kind == SetField::Choice && !f.options.empty()) {
        int n = (int)f.options.size(), at = 0;
        for (int i = 0; i < n; i++)
            if (f.cur == f.options[i].first) at = i;
        f.cur = f.options[(at + dir + n) % n].first;
    } else if (f.kind == SetField::Check) {
        f.cur = dir > 0 ? L"1" : L"0";
    }
    Set_Invalidate(w);
}

static bool Set_OnKey(SetWindow& w, UINT vk) {
    if (w.saving) return true;
    if (w.recording >= 0) {
        if (Set_IsModifier(vk)) return true;
        UINT mods = 0;
        if (GetKeyState(VK_CONTROL) & 0x8000) mods |= MOD_CONTROL;
        if (GetKeyState(VK_MENU) & 0x8000) mods |= MOD_ALT;
        if (GetKeyState(VK_SHIFT) & 0x8000) mods |= MOD_SHIFT;
        if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000) mods |= MOD_WIN;
        SetField& f = w.fields[w.recording];
        if (vk == VK_ESCAPE && !mods) {
            // Cancel: keep what was there.
        } else if ((vk == VK_BACK || vk == VK_DELETE) && !mods) {
            f.cur.clear();
        } else {
            f.cur = Set_FormatHotkey(mods, vk);
        }
        Set_StopRecording(w);
        return true;
    }
    if (w.openSel >= 0) {
        const SetField& f = w.fields[w.openSel];
        int n = (int)f.options.size();
        if (vk == VK_ESCAPE) Set_ClosePopup(w);
        else if (vk == VK_UP) Set_DropShow(w, w.dropHover = w.dropHover < 0 ? n - 1 : (w.dropHover - 1 + n) % n);
        else if (vk == VK_DOWN) Set_DropShow(w, w.dropHover = w.dropHover < 0 ? 0 : (w.dropHover + 1) % n);
        else if (vk == VK_RETURN || vk == VK_SPACE) Set_Choose(w, w.openSel, w.dropHover);
        Set_Invalidate(w);
        return true;
    }
    bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0, shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
    if (ctrl && vk == 'B') {  // Same shortcut as T3's sidebar.
        Set_ToggleRail(w);
        return true;
    }
    float view = Set_ViewH(w), maxScroll = std::max(0.0f, w.contentH - view);
    switch (vk) {
        case VK_TAB:
            if (ctrl) Set_GoPage(w, (w.page + (shift ? kSetPageCount - 1 : 1)) % kSetPageCount);
            else Set_MoveFocus(w, shift ? -1 : 1);
            return true;
        case VK_SPACE:
        case VK_RETURN:
            w.kbd = true;
            if (w.focus >= 0) Set_ActivateField(w, w.focus, nullptr);
            else if (w.focus <= -1 && w.focus >= -3) Set_FooterAction(w, -1 - w.focus);
            return true;
        case VK_LEFT:
        case VK_RIGHT:
            w.kbd = true;
            Set_Adjust(w, vk == VK_RIGHT ? 1 : -1);
            return true;
        case VK_UP: w.scrollTarget = std::clamp(w.scrollTarget - 60, 0.0f, maxScroll); break;
        case VK_DOWN: w.scrollTarget = std::clamp(w.scrollTarget + 60, 0.0f, maxScroll); break;
        case VK_PRIOR: w.scrollTarget = std::clamp(w.scrollTarget - view * 0.9f, 0.0f, maxScroll); break;
        case VK_NEXT: w.scrollTarget = std::clamp(w.scrollTarget + view * 0.9f, 0.0f, maxScroll); break;
        case VK_HOME: w.scrollTarget = 0; break;
        case VK_END: w.scrollTarget = maxScroll; break;
        case VK_ESCAPE:
            if (!w.render) DestroyWindow(w.hwnd);
            return true;
        default:
            if (ctrl && vk >= '1' && vk <= '6') {
                Set_GoPage(w, (int)(vk - '1'));
                return true;
            }
            return false;
    }
    if (!Set_Anim(w)) w.scrollY = w.scrollTarget;
    Set_PlaceEdit(w);
    Set_Invalidate(w);
    return true;
}

// ---- Window ---------------------------------------------------------------------

static bool Set_EnsureRt(SetWindow& w) {
    if (w.rt) return true;
    if (!Set_EnsureFactories()) return false;
    RECT rc;
    GetClientRect(w.hwnd, &rc);
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        (float)w.dpi, (float)w.dpi);
    return SUCCEEDED(g_setD2d->CreateHwndRenderTarget(
        props, D2D1::HwndRenderTargetProperties(w.hwnd, D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom))),
        w.rt.put()));
}

static void Set_Relayout(SetWindow& w) {
    RECT rc;
    GetClientRect(w.hwnd, &rc);
    w.cw = rc.right * 96.0f / w.dpi;
    w.ch = std::max(0.0f, rc.bottom * 96.0f / w.dpi - kSetCapH);
    if (w.rt) w.rt->Resize(D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom)));
    Set_BuildAndClamp(w);
}

// A switch's stored value, found by the end of its key so a "SettingsWindow." prefix still matches.
static bool Set_FieldOn(const SetWindow& w, PCWSTR key, bool def) {
    // The window group wins over a module option with the same suffix.
    const std::wstring windowKey = std::wstring(L"SettingsWindow.") + key;
    for (const auto& f : w.fields)
        if (windowKey == f.key) return f.value == L"1";
    for (const auto& f : w.fields)
        if (wcscmp(f.key, key) == 0) return f.value == L"1";
    const size_t n = wcslen(key);
    for (const auto& f : w.fields) {
        const size_t m = wcslen(f.key);
        if (m >= n && wcscmp(f.key + m - n, key) == 0 && (m == n || f.key[m - n - 1] == L'.')) return f.value == L"1";
    }
    return def;
}

// "Native Windows title bar" and "Blurred settings window", applied to the live window: on first
// open and again whenever a save or a reload changes them, so neither needs a reopen.
static void Set_ApplyFrame(SetWindow& w) {
    if (w.render || !w.hwnd) return;
    const HWND hwnd = w.hwnd;
    const bool native = Set_FieldOn(w, L"nativeSettingsTitleBar", false), glass = Set_FieldOn(w, L"settingsGlass", true);
    const bool first = !w.frameApplied, wasGlass = w.glass;
    if (!first && native == w.nativeTitle && glass == w.glass) return;  // A title bar switch re-runs the accent below.
    w.frameApplied = true;
    w.nativeTitle = native;
    w.glass = glass;
    kSetCapH = native ? 0.0f : 40.0f;
    struct SetAccentPolicy { int state, flags, abgr, animation; };
    struct SetCompositionData { DWORD attribute; void* data; SIZE_T size; };
    using SetComposition_t = BOOL(WINAPI*)(HWND, SetCompositionData*);
    auto setComposition =
        (SetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (glass) {
        // Acrylic as one sheet over the whole window, the same material Seamless Flyouts
        // gives the Launchpad settings window in Explorer: the accent acrylic with an 85%
        // Mocha base tint, under the page's own crust tint. The system backdrop
        // (DWMSBT_TRANSIENTWINDOW) went light grey over bright windows and turned to a flat
        // grey slab when the window lost focus; the accent acrylic stays the same.
        int backdrop = 1;  // DWMSBT_NONE
        DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
        DWM_BLURBEHIND bb{};
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        bb.fEnable = TRUE;
        bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
        DwmEnableBlurBehindWindow(hwnd, &bb);
        if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
        if (setComposition) {
            // Same as the launcher grid. With the Windows title bar the tint is in here instead of
            // on the page, so the title bar gets it too: crust at the page's 55%.
            const int tint = native ? (int)(((DWORD)(kSetGlassTint * 255 + 0.5f) << 24) | (mocha::crust & 0xFF) << 16 |
                                            (mocha::crust & 0xFF00) | (mocha::crust >> 16 & 0xFF))
                                    : (int)0x012E1E1E;
            SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, tint, 0};
            SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(hwnd, &data);
        }
        MARGINS margins{-1, -1, -1, -1};
        DwmExtendFrameIntoClientArea(hwnd, &margins);
        COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
        DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
    } else if (wasGlass) {
        // Glass switched off while open: back to a plain solid window.
        if (setComposition) {
            SetAccentPolicy policy{0, 0, 0, 0};
            SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(hwnd, &data);
        }
        DWM_BLURBEHIND bb{};
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = FALSE;
        DwmEnableBlurBehindWindow(hwnd, &bb);
        MARGINS margins{0, 0, 0, 0};
        DwmExtendFrameIntoClientArea(hwnd, &margins);
        int backdrop = 0;  // DWMSBT_AUTO
        DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
        COLORREF caption = RefFromRgb(mocha::crust);
        DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
    }
    // With the frame extended DWM would draw its own minimize, maximize and close buttons over the
    // built-in title bar; without a system menu it draws none. The Windows title bar keeps it.
    // Minimize, maximize and close still work from the taskbar either way.
    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    SetWindowLongPtrW(hwnd, GWL_STYLE, native ? (style | WS_SYSMENU) : (style & ~WS_SYSMENU));
    // Set_WndProc's WM_NCCALCSIZE drops or keeps the system title bar to match.
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    if (!first) {
        Set_Relayout(w);
        RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW);
    }
}

static void Set_RememberRect(SetWindow& w) {
    if (w.render || IsIconic(w.hwnd) || IsZoomed(w.hwnd)) return;
    GetWindowRect(w.hwnd, &w.normalRect);
}

static LRESULT CALLBACK Set_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w) return DefWindowProcW(hwnd, msg, wParam, lParam);
    if (w->nativeTitle) {
        LRESULT r = 0;
        if (DwmDefWindowProc(hwnd, msg, wParam, lParam, &r)) return r;  // Hover and clicks on DWM's buttons.
    }
    auto dipX = [&](LPARAM l) { return (float)(short)LOWORD(l) * 96.0f / w->dpi; };
    auto dipY = [&](LPARAM l) { return (float)(short)HIWORD(l) * 96.0f / w->dpi - kSetCapH; };
    switch (msg) {
        case WM_APP_SETTINGS_RELOAD:
            if (!w->saving) {
                Set_LoadFields(*w);
                Set_ApplyFrame(*w);
            }
            return 0;
        case WM_APP_SETTINGS_ACTIVATE: ShowWindow(hwnd, SW_RESTORE); ForceForeground(hwnd); return 0;
        case WM_NCCALCSIZE:
            // No system title bar: keep the side and bottom frames, the client starts at the top edge.
            if (wParam && !w->render && !w->nativeTitle) {
                auto* nc = (NCCALCSIZE_PARAMS*)lParam;
                LONG top = nc->rgrc[0].top;
                LRESULT r = DefWindowProcW(hwnd, msg, wParam, lParam);
                nc->rgrc[0].top = top;
                if (IsZoomed(hwnd))
                    nc->rgrc[0].top += GetSystemMetricsForDpi(SM_CYSIZEFRAME, w->dpi) +
                                       GetSystemMetricsForDpi(SM_CXPADDEDBORDER, w->dpi);
                return r;
            }
            break;
        case WM_NCHITTEST: {
            if (w->render || w->nativeTitle) break;
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            ScreenToClient(hwnd, &pt);
            RECT rc;
            GetClientRect(hwnd, &rc);
            if (pt.x < 0 || pt.y < 0 || pt.x >= rc.right || pt.y >= rc.bottom) break;
            int frame = GetSystemMetricsForDpi(SM_CYSIZEFRAME, w->dpi) + GetSystemMetricsForDpi(SM_CXPADDEDBORDER, w->dpi);
            if (!IsZoomed(hwnd) && pt.y < frame)
                return pt.x < frame * 2 ? HTTOPLEFT : pt.x >= rc.right - frame * 2 ? HTTOPRIGHT : HTTOP;
            float x = pt.x * 96.0f / w->dpi, y = pt.y * 96.0f / w->dpi - kSetCapH;
            if (y < 0) return Set_CapButtonAt(*w, x, y) >= 0 ? HTCLIENT : HTCAPTION;
            return HTCLIENT;
        }
        case WM_ACTIVATE:
            w->active = LOWORD(wParam) != WA_INACTIVE;
            if (!w->active) Set_AutoScrollStop(*w);
            Set_Invalidate(*w);
            break;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
        case WM_PRINTCLIENT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (!w->render && Set_EnsureRt(*w)) Set_Draw(*w, w->rt.get());
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CTLCOLOREDIT: {
            HDC dc = (HDC)wParam;
            SetTextColor(dc, RefFromRgb(mocha::text));
            SetBkColor(dc, RefFromRgb(kSetBoxFill));
            return (LRESULT)w->editBrush;
        }
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED && !w->render) {
                Set_Relayout(*w);
                Set_RememberRect(*w);
                RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);  // No stale title bar after a snap.
            }
            return 0;
        case WM_MOVE:
            Set_RememberRect(*w);
            return 0;
        case WM_GETMINMAXINFO: {
            auto* mm = (MINMAXINFO*)lParam;
            RECT r{0, 0, MulDiv(760, w->dpi, 96), MulDiv(520, w->dpi, 96)};
            AdjustWindowRectExForDpi(&r, GetWindowLongW(hwnd, GWL_STYLE), FALSE, GetWindowLongW(hwnd, GWL_EXSTYLE),
                                     w->dpi);
            mm->ptMinTrackSize = {r.right - r.left, r.bottom - r.top};
            return 0;
        }
        case WM_DPICHANGED: {
            if (g_setForceDpi) return 0;
            Set_CommitEdit(*w, true);
            w->dpi = HIWORD(wParam);
            if (w->rt) w->rt->SetDpi((float)w->dpi, (float)w->dpi);
            auto* r = (RECT*)lParam;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            Set_Relayout(*w);
            return 0;
        }
        case WM_TIMER:
            if (wParam == kSetTimerId) {
                if (Set_Tick(*w)) Set_Invalidate(*w);
                return 0;
            }
            break;
        case WM_MOUSEMOVE: {
            if (w->saving) return 0;
#ifdef LP_TEST_HOVER  // Only the test script's moves (marked 0x8000), never a real cursor passing over.
            if (!(wParam & 0x8000)) return 0;
#endif
            float x = dipX(lParam), y = dipY(lParam);
#ifndef LP_TEST_HOVER  // The test build feeds pointer moves by message; a leave would undo them.
            if (!w->tracking && !w->render) {
#else
            if (false) {
#endif
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                TrackMouseEvent(&t);
                w->tracking = true;
            }
            w->mouseX = x;
            w->mouseY = y;
            if (w->autoScroll) {
                Set_AutoScrollMove(*w, (wParam & MK_MBUTTON) != 0);
                return 0;
            }
            if (w->dragRail) {
                Set_RailDragTo(*w, x - w->dragOff);
                return 0;
            }
            if (w->dragSlider >= 0) {
                Set_SliderTo(*w, w->dragSlider, x);
                return 0;
            }
            if (w->dragScroll) {
                D2D1_RECT_F th = Set_ScrollThumb(*w);
                float view = Set_ViewH(*w), thh = th.bottom - th.top, range = view - thh - 8;
                float t = range > 0 ? std::clamp((y - w->dragOff - 4) / range, 0.0f, 1.0f) : 0;
                w->scrollTarget = w->scrollY = t * std::max(0.0f, w->contentH - view);
                Set_PlaceEdit(*w);
                Set_Invalidate(*w);
                return 0;
            }
            SetHit h = Set_Hit(*w, x, y);
            int dh = h.kind == SetHit::Drop ? h.b : -1;
            if (h.kind != w->hover.kind || h.id != w->hover.id || h.a != w->hover.a || h.b != w->hover.b ||
                dh != w->dropHover) {
                w->hover = h;
                if (w->openSel >= 0) w->dropHover = dh;
                Set_Invalidate(*w);
            }
            return 0;
        }
        case WM_MOUSELEAVE: {
            POINT pointer; GetCursorPos(&pointer);
            w->tracking = false;
            w->hover = SetHit();
            if (!w->dragRail && !w->autoScroll) w->mouseX = w->mouseY = -1;
            Set_Invalidate(*w);
            return 0;
        }
        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT) {
                PCWSTR cur = w->dragRail || w->hover.kind == SetHit::RailEdge ? IDC_SIZEWE
                             : Set_Clickable(w->hover)                         ? IDC_HAND
                                                                               : IDC_ARROW;
                SetCursor(LoadCursorW(nullptr, cur));
                return TRUE;
            }
            break;
        case WM_LBUTTONDOWN: {
            if (w->saving) return 0;
            if (w->autoScroll) {  // A click ends autoscroll and does nothing else.
                Set_AutoScrollStop(*w);
                return 0;
            }
            if (!w->render) SetFocus(hwnd);
            w->kbd = false;
            float x = dipX(lParam), y = dipY(lParam);
            SetHit h = Set_Hit(*w, x, y);
            if (w->openSel >= 0) {  // The popup eats the click, whatever it hits.
                if (h.kind == SetHit::Drop) Set_Choose(*w, h.a, h.b);
                else Set_ClosePopup(*w);
                return 0;
            }
            Set_CommitEdit(*w, true);
            if (w->recording >= 0 && !(h.kind == SetHit::Control && h.a == w->recording)) Set_StopRecording(*w);
            w->hover = h;
            switch (h.kind) {
                case SetHit::Rail:
                    Set_GoPage(*w, h.a);
                    break;
                case SetHit::RailToggle:
                    Set_ToggleRail(*w);
                    break;
                case SetHit::RailEdge:
                    w->dragRail = true;
                    w->dragOff = x - Set_RailDock(*w).right;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                case SetHit::Footer:
                    Set_FooterAction(*w, h.a);
                    return 0;  // The window may be gone.
                case SetHit::Control:
                case SetHit::Clear:
                case SetHit::Chip:
                    w->focus = h.a;
                    Set_ActivateField(*w, h.a, &h);
                    break;
                case SetHit::Slider:
                    w->focus = h.a;
                    w->dragSlider = h.a;
                    SetCapture(hwnd);
                    Set_SliderTo(*w, h.a, x);
                    break;
                case SetHit::Scroll: {
                    w->dragScroll = true;
                    w->dragOff = y - Set_ScrollThumb(*w).top;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                }
                case SetHit::Link:
                    Set_OpenLink(w->items[h.a].url.c_str());
                    break;
                case SetHit::Caption:
                    w->capDown = h.a + 1;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                default:
                    break;
            }
            return 0;
        }
        case WM_LBUTTONUP:
        case WM_CAPTURECHANGED:
            if (msg == WM_CAPTURECHANGED && w->autoScroll && (HWND)lParam != hwnd) Set_AutoScrollStop(*w);
            if (w->capDown) {
                int b = w->capDown - 1;
                w->capDown = 0;
                if (msg == WM_LBUTTONUP) {
                    if (GetCapture() == hwnd) ReleaseCapture();
                    SetHit h = Set_Hit(*w, dipX(lParam), dipY(lParam));
                    if (h.kind == SetHit::Caption && h.a == b) {
                        if (b == 0) ShowWindow(hwnd, SW_MINIMIZE);
                        else if (b == 1) ShowWindow(hwnd, IsZoomed(hwnd) ? SW_RESTORE : SW_MAXIMIZE);
                        else PostMessageW(hwnd, WM_CLOSE, 0, 0);
                    }
                }
                Set_Invalidate(*w);
                return 0;
            }
            if (w->dragSlider >= 0 || w->dragScroll || w->dragRail) {
                w->dragSlider = -1;
                w->dragScroll = false;
                w->dragRail = false;
                if (msg == WM_LBUTTONUP && GetCapture() == hwnd) ReleaseCapture();
                Set_Invalidate(*w);
            }
            return 0;
        case WM_MBUTTONDOWN:
            if (w->saving) return 0;
            if (w->autoScroll) Set_AutoScrollStop(*w);  // Toggle mode: the next middle click ends it.
            else Set_AutoScrollStart(*w, dipX(lParam), dipY(lParam));
            return 0;
        case WM_MBUTTONUP:
            if (w->autoScroll && w->autoMoved) Set_AutoScrollStop(*w);  // Held and dragged: stop on release.
            return 0;
        case WM_RBUTTONDOWN:
        case WM_XBUTTONDOWN:
            if (w->autoScroll) {
                Set_AutoScrollStop(*w);
                return msg == WM_XBUTTONDOWN ? TRUE : 0;
            }
            break;
        case WM_MOUSEWHEEL: {
            Set_AutoScrollStop(*w);
            if (w->openSel >= 0 && Set_In(w->dropRect, w->mouseX, w->mouseY)) {
                int n = (int)w->fields[w->openSel].options.size(), vis = Set_DropVisible(*w);
                int step = GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? -3 : 3;
                w->dropTop = std::clamp(w->dropTop + step, 0, std::max(0, n - vis));
                SetHit h = Set_Hit(*w, w->mouseX, w->mouseY);
                w->hover = h;
                w->dropHover = h.kind == SetHit::Drop ? h.b : w->dropHover;
                Set_Invalidate(*w);
                return 0;
            }
            Set_CommitEdit(*w, true);
            Set_ClosePopup(*w);
            float delta = (float)GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            float maxScroll = std::max(0.0f, w->contentH - Set_ViewH(*w));
            w->scrollTarget = std::clamp(w->scrollTarget - delta * 72, 0.0f, maxScroll);
            if (!Set_Anim(*w)) w->scrollY = w->scrollTarget;
            Set_Invalidate(*w);
            return 0;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            if (w->autoScroll) {  // Any key ends autoscroll; Escape does nothing else.
                Set_AutoScrollStop(*w);
                if (wParam == VK_ESCAPE) return 0;
            }
            if (Set_OnKey(*w, (UINT)wParam)) return 0;
            // Without a system menu (glass title bar) Windows no longer turns Alt+F4 into a close.
            if (msg == WM_SYSKEYDOWN && wParam == VK_F4 && w->recording < 0) {
                PostMessageW(hwnd, WM_CLOSE, 0, 0);
                return 0;
            }
            break;
        case WM_CHAR:
        case WM_SYSCHAR:
            if (w->recording >= 0) return 0;
            break;
        case WM_KILLFOCUS:
            if (w->recording >= 0 && (HWND)wParam != w->edit) Set_StopRecording(*w);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY: {
            Set_StopRecording(*w);
            RemovePropW(hwnd, kSetAutoProp);
            if (w->timer) KillTimer(hwnd, kSetTimerId);
            if (!w->render && w->normalRect.right > w->normalRect.left) {
                const RECT& r = w->normalRect;
                SetState(StateKey(L"Settings", L"X").c_str(), r.left);
                SetState(StateKey(L"Settings", L"Y").c_str(), r.top);
                SetState(StateKey(L"Settings", L"CX").c_str(), r.right - r.left);
                SetState(StateKey(L"Settings", L"CY").c_str(), r.bottom - r.top);
            }
            if (!w->render) {
                SetState(StateKey(L"Settings", L"RailW").c_str(), (int)w->railW);
                SetState(StateKey(L"Settings", L"RailCollapsed").c_str(), w->railCollapsed ? 1 : 0);
            }
            return 0;
        }
        case WM_NCDESTROY: {
            if (w->editFont) DeleteObject(w->editFont);
            if (w->editBrush) DeleteObject(w->editBrush);
            if (w->iconSmall) DestroyIcon(w->iconSmall);
            if (w->iconBig) DestroyIcon(w->iconBig);
            if (w->owner) DestroyWindow(w->owner);
            w->destroyed = true;
            w->hwnd = nullptr;
            w->edit = nullptr;
            w->rt.reset();
            g_settingsWnd = nullptr; PostQuitMessage(0);
            g_setWin.reset();
            Set_ReleaseFactories();
            return DefWindowProcW(hwnd, msg, wParam, lParam);
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// Blue to mauve rounded square with a clipboard glyph, px pixels square.
static HICON Set_MakeIcon(const std::wstring& iconFamily, int px) {
    if (px <= 0 || !Set_EnsureFactories()) return nullptr;
    SetCom<IWICBitmap> bmp;
    SetCom<ID2D1RenderTarget> rt;
    if (FAILED(g_setWic->CreateBitmap(px, px, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnLoad, bmp.put())))
        return nullptr;
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
    if (FAILED(g_setD2d->CreateWicBitmapRenderTarget(bmp.get(), props, rt.put()))) return nullptr;
    float s = (float)px;
    SetWindow dummy;
    SetPaint p(dummy, rt.get());
    auto glyph = Set_Fmt(iconFamily, s * 0.6f, 400, false, DWRITE_TEXT_ALIGNMENT_CENTER, true);
    rt->BeginDraw();
    rt->Clear(D2D1::ColorF(0, 0));
    Set_DrawMark(p, glyph.get(), {0, 0, s, s}, 1);
    if (FAILED(rt->EndDraw())) return nullptr;
    std::vector<BYTE> pix((size_t)px * px * 4);
    if (FAILED(bmp->CopyPixels(nullptr, px * 4, (UINT)pix.size(), pix.data()))) return nullptr;
    for (size_t i = 0; i < pix.size(); i += 4) {  // Icons want straight alpha.
        BYTE a = pix[i + 3];
        if (a && a < 255)
            for (int c = 0; c < 3; c++) pix[i + c] = (BYTE)std::min(255, pix[i + c] * 255 / a);
    }
    BITMAPV5HEADER bi{};
    bi.bV5Size = sizeof(bi);
    bi.bV5Width = px;
    bi.bV5Height = -px;
    bi.bV5Planes = 1;
    bi.bV5BitCount = 32;
    bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask = 0x00FF0000;
    bi.bV5GreenMask = 0x0000FF00;
    bi.bV5BlueMask = 0x000000FF;
    bi.bV5AlphaMask = 0xFF000000;
    void* bits = nullptr;
    HDC dc = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, dc);
    if (!color || !bits) return nullptr;
    memcpy(bits, pix.data(), pix.size());
    std::vector<BYTE> maskBits((size_t)((px + 15) / 16) * 2 * px, 0);
    HBITMAP mask = CreateBitmap(px, px, 1, 1, maskBits.data());
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

// The class belongs to this DLL and goes away with the settings thread. Registered under
// Explorer's handle it outlived a mod update, and the next window ran the unloaded code.
static void Set_RegisterClass() {
    UnregisterClassW(kSettingsClass, GetModuleHandleW(nullptr));  // left by builds before 2.3.0
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = Set_WndProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kSettingsClass;
    RegisterClassExW(&wc);
}

// Builds the window, hidden. render: an off-screen copy that is never shown (tests and PNG output).
static bool Set_Create(bool render) {
    if (!Set_EnsureFactories()) return false;
    Set_RegisterClass();
    auto w = std::make_shared<SetWindow>();
    w->render = render;
    w->editBrush = CreateSolidBrush(RefFromRgb(kSetBoxFill));
    g_setWin = w;
    if (render) {
        // An owned window gets no taskbar button.
        w->owner = CreateWindowExW(WS_EX_TOOLWINDOW, L"STATIC", L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                                   GetModuleHandleW(nullptr), nullptr);
    }
    const int offX = GetSystemMetrics(SM_XVIRTUALSCREEN) - 6000, offY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    // The built-in title bar until Set_ApplyFrame reads the switches.
    kSetCapH = 40.0f;
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Pointer Afterimage Plus settings", style,
                                render ? offX : CW_USEDEFAULT, render ? offY : CW_USEDEFAULT, 800, 600, w->owner,
                                nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (!hwnd) {
        g_setWin.reset();
        return false;
    }
    w->hwnd = hwnd;
    SetPropW(hwnd, kSetAutoProp, (HANDLE)1);  // Seamless Autoscroll leaves this window to Set_AutoScroll*.
    w->dpi = g_setForceDpi ? g_setForceDpi : GetDpiForWindow(hwnd);
    ApplyDarkWindow(hwnd);
    COLORREF caption = RefFromRgb(mocha::crust), captionText = RefFromRgb(mocha::text);
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
    DwmSetWindowAttribute(hwnd, 36 /* DWMWA_TEXT_COLOR */, &captionText, sizeof(captionText));
    Set_MakeFormats(*w);
    Set_LoadFields(*w);
    if (!render) {
        w->railW = std::clamp((float)GetState(StateKey(L"Settings", L"RailW").c_str(), (int)kSetRailDef), kSetRailMin, kSetRailMax);
        w->railCollapsed = GetState(StateKey(L"Settings", L"RailCollapsed").c_str(), 0) != 0;
        w->railCur = w->railCollapsed ? kSetRailMini : w->railW;
    }
    if (!render) {
        w->iconSmall = Set_MakeIcon(w->iconFamily, GetSystemMetricsForDpi(SM_CXSMICON, w->dpi));
        w->iconBig = Set_MakeIcon(w->iconFamily, GetSystemMetricsForDpi(SM_CXICON, w->dpi));
        if (w->iconSmall) SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)w->iconSmall);
        if (w->iconBig) SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)w->iconBig);
        Set_ApplyFrame(*w);  // Title bar and glass; also drops the system title bar the first WM_NCCALCSIZE kept.
    }

    auto outer = [&](float cwDip, float chDip, SIZE& size) {
        RECT r{0, 0, MulDiv((int)cwDip, w->dpi, 96), MulDiv((int)chDip, w->dpi, 96)};
        AdjustWindowRectExForDpi(&r, style, FALSE, 0, w->dpi);
        size = {r.right - r.left, r.bottom - r.top};
    };
    SIZE size;
    if (render) {
        w->cw = 980;
        w->ch = 700;
        outer(w->cw, w->ch, size);
        SetWindowPos(hwnd, nullptr, offX, offY, size.cx, size.cy, SWP_NOZORDER | SWP_NOACTIVATE);
        Set_BuildPage(*w);
        return true;
    }
    outer(980, 720, size);
    POINT cursor;
    GetCursorPos(&cursor);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST), &mi);
    const RECT& work = mi.rcWork;
    int width = std::min((int)size.cx, (int)(work.right - work.left) * 9 / 10);
    int height = std::min((int)size.cy, (int)(work.bottom - work.top) * 9 / 10);
    RECT r{(work.left + work.right - width) / 2, (work.top + work.bottom - height) / 2, 0, 0};
    r.right = r.left + width;
    r.bottom = r.top + height;
    int cx = GetState(StateKey(L"Settings", L"CX").c_str(), 0);
    int cy = GetState(StateKey(L"Settings", L"CY").c_str(), 0);
    if (cx > 0 && cy > 0) {
        RECT saved{GetState(StateKey(L"Settings", L"X").c_str(), 0), GetState(StateKey(L"Settings", L"Y").c_str(), 0),
                   0, 0};
        saved.right = saved.left + cx;
        saved.bottom = saved.top + cy;
        if (MonitorFromRect(&saved, MONITOR_DEFAULTTONULL)) r = saved;
    }
    SetWindowPos(hwnd, nullptr, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_NOZORDER | SWP_NOACTIVATE);
    // The monitor it landed on may have a different scale.
    UINT dpi = GetDpiForWindow(hwnd);
    if (!g_setForceDpi && dpi != w->dpi) w->dpi = dpi;
    Set_Relayout(*w);
    w->pageT = Set_Anim(*w) ? 0.0f : 1.0f;
    w->timer = SetTimer(hwnd, kSetTimerId, 15, nullptr) != 0;
    return true;
}

void Settings_Open() {
    if (g_setWin && g_setWin->hwnd && !g_setWin->render) {
        HWND hwnd = g_setWin->hwnd;
        if (IsIconic(hwnd)) ShowWindow(hwnd, SW_RESTORE);
        SetForegroundWindow(hwnd);
        return;
    }
    if (g_setWin) Settings_Close();
    if (!Set_Create(false)) return;
    HWND hwnd = g_setWin->hwnd;
    ShowWindow(hwnd, SW_SHOW);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}

void Settings_Close() {
    if (g_setWin && g_setWin->hwnd) DestroyWindow(g_setWin->hwnd);
    g_setWin.reset();
}

bool Settings_IsOpen() { return g_setWin && g_setWin->hwnd && !g_setWin->render; }


DWORD WINAPI SettingsThread(void*) {
 SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
 CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
 Settings_Open();
 if (g_setWin) g_settingsWnd=g_setWin->hwnd;
 MSG msg;
 while (g_settingsWnd && GetMessageW(&msg,nullptr,0,0)>0) { TranslateMessage(&msg); DispatchMessageW(&msg); }
 Settings_Close(); UnregisterClassW(kSettingsClass,(HINSTANCE)&__ImageBase); Set_ReleaseFactories(); CoUninitialize(); return 0;
}
void OpenSettingsWindow() {
 if (HWND hwnd=g_settingsWnd) { PostMessageW(hwnd,WM_APP_SETTINGS_ACTIVATE,0,0); return; }
 if(g_settingsThread) { if(WaitForSingleObject(g_settingsThread,0)==WAIT_TIMEOUT) return; CloseHandle(g_settingsThread); }
 g_settingsStop=false; g_settingsThread=CreateThread(nullptr,0,SettingsThread,nullptr,0,nullptr);
}
void CloseSettingsWindow() {
 g_settingsStop=true;
 if(HWND hwnd=g_settingsWnd) PostMessageW(hwnd,WM_CLOSE,0,0);
 if(g_settingsThread) { WaitForSingleObject(g_settingsThread,15000); CloseHandle(g_settingsThread); g_settingsThread=nullptr; }
}
// The tray icon's right-click menu. Returns 1 for Pause, 2 for Settings, 0 for nothing.
int ShowTrayMenu(HWND owner, POINT pt, bool paused) {
    std::vector<SetMenuItem> rows;
    rows.push_back(Set_MenuRow(1, L"\uEAD1", L"Pause the effects", paused));
    rows.push_back(Set_MenuSep());
    rows.push_back(Set_MenuRow(2, L"\uEB51", L"Settings"));
    return Set_TrayMenu(owner, rows, &pt);
}
}  // namespace papset

// ---- Tray icon (tool process only) -------------------------------------------------------------------------------
// Click opens the settings window; right-click shows Pause and Settings. The badge is the shared rounded blue to mauve
// plate with the pointer cut out, grey while paused. Pause lasts until it is clicked again or the mod restarts.

static constexpr UINT WM_APP_TRAY = WM_APP + 20, WM_APP_TRAY_REFRESH = WM_APP + 21;
static HANDLE g_trayThread;
static std::atomic<HWND> g_trayWnd;
static UINT g_taskbarCreated;
static bool g_trayShown;
static HICON g_trayIcon;

static HICON MakeTrayIcon_Big(bool off) {
    int size = GetSystemMetricsForDpi(SM_CXICON, GetDpiForSystem()) * 4;
    if (size < 16) size = 16;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    void* glyphBits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    HBITMAP glyph = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &glyphBits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color || !glyph) {
        if (color) DeleteObject(color);
        if (glyph) DeleteObject(glyph);
        return nullptr;
    }
    HDC dc = CreateCompatibleDC(nullptr);
    HGDIOBJ old = SelectObject(dc, glyph);
    memset(glyphBits, 0, (size_t)size * size * 4);
    HFONT font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xE8B0, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {off ? 0x6C / 255.f : 0x89 / 255.f, off ? 0x70 / 255.f : 0xB4 / 255.f, off ? 0x86 / 255.f : 0xFA / 255.f};
    const float c1[3] = {off ? 0x58 / 255.f : 0xCB / 255.f, off ? 0x5B / 255.f : 0xA6 / 255.f, off ? 0x70 / 255.f : 0xF7 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = base * cov;
            }
            px[y * size + x] = ((uint32_t)(cov * 255 + 0.5f) << 24) | ((uint32_t)(rgb[0] * 255 + 0.5f) << 16) |
                               ((uint32_t)(rgb[1] * 255 + 0.5f) << 8) | (uint32_t)(rgb[2] * 255 + 0.5f);
        }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    DeleteObject(glyph);
    return icon;
}

// Drawn at 4x and shrunk, so the icon is smooth at the size it is shown.
static HICON MakeTrayIcon(bool off) { return Crisp_ShrinkIcon(MakeTrayIcon_Big(off), 4); }

static void UpdateTray(HWND hwnd, bool recreate) {
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = kTrayId;
    if (!Wh_GetIntSetting(L"settingsTrayIcon")) {
        if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayShown = false;
        return;
    }
    HICON icon = MakeTrayIcon(g_userPaused);
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_APP_TRAY;
    nid.hIcon = icon;
    wcscpy_s(nid.szTip, g_userPaused ? L"Pointer Afterimage Plus (paused)" : L"Pointer Afterimage Plus");
    if (recreate) g_trayShown = false;
    if (!g_trayShown) {
        Shell_NotifyIconW(NIM_DELETE, &nid);
        if (Shell_NotifyIconW(NIM_ADD, &nid)) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
            g_trayShown = true;
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = icon;
}

static void SetUserPaused(HWND tray, bool on) {
    g_userPaused = on;
    Wh_Log(L"Paused from the tray: %d", on);
    g_recheck = true;
    SetEvent(g_mouseWake);
    SetEvent(g_moved);
    UpdateTray(tray, false);
}

static LRESULT CALLBACK TrayProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        UpdateTray(hwnd, true);
        return 0;
    }
    switch (msg) {
        case WM_APP_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    papset::OpenSettingsWindow();
                    break;
                case WM_CONTEXTMENU: {
                    POINT pt{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)};
                    SetForegroundWindow(hwnd);
                    int cmd = papset::ShowTrayMenu(hwnd, pt, g_userPaused);
                    if (cmd == 1) SetUserPaused(hwnd, !g_userPaused);
                    else if (cmd == 2) papset::OpenSettingsWindow();
                    break;
                }
            }
            return 0;
        case WM_APP_TRAY_REFRESH:
            UpdateTray(hwnd, false);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY: {
            NOTIFYICONDATAW nid{};
            nid.cbSize = sizeof(nid);
            nid.hWnd = hwnd;
            nid.uID = kTrayId;
            if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
            g_trayShown = false;
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI TrayThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HINSTANCE inst = (HINSTANCE)&__ImageBase;
    WNDCLASSW wc{};
    wc.lpfnWndProc = TrayProc;
    wc.hInstance = inst;
    wc.lpszClassName = L"PointerAfterimagePlusTray";
    RegisterClassW(&wc);
    // A hidden top-level window, not a message-only one: only top-level windows hear TaskbarCreated.
    HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Pointer Afterimage Plus", WS_POPUP, 0, 0, 0, 0,
                                nullptr, nullptr, inst, nullptr);
    if (!hwnd) {
        UnregisterClassW(wc.lpszClassName, inst);
        return 0;
    }
    g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(hwnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
    g_trayWnd = hwnd;
    UpdateTray(hwnd, true);
    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    g_trayWnd = nullptr;
    if (IsWindow(hwnd)) DestroyWindow(hwnd);
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    UnregisterClassW(wc.lpszClassName, inst);
    return 0;
}

static void StopTrayThread() {
    if (!g_trayThread) return;
    if (HWND hwnd = g_trayWnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
    if (WaitForSingleObject(g_trayThread, 5000) == WAIT_TIMEOUT) Wh_Log(L"The tray thread did not stop");
    CloseHandle(g_trayThread);
    g_trayThread = nullptr;
}

BOOL WhTool_ModInit() {
    Wh_Log(L"Init");
    LoadSettings();
    QueryPerformanceFrequency(&g_freq);
    QueryPerformanceCounter(&g_start);
    InitializeCriticalSection(&g_gate);
    g_ownIntegrity = Integrity(GetCurrentProcess());
    BuildHiddenKey();
    if (Wh_GetIntValue(g_hiddenKey, 0)) {   // an earlier run was killed while hiding the cursor
        Wh_Log(L"Restoring the cursors after an earlier run");
        ReloadCursors();
        Wh_SetIntValue(g_hiddenKey, 0);
    }
    g_prevFilter = SetUnhandledExceptionFilter(CrashFilter);
    if (HWND band = FindWindowW(BAND_CLASS, nullptr)) ShowWindowAsync(band, SW_HIDE);   // left by an earlier run

    // Windows 11 ignores a finer timer for a process with no visible window; the short waits here need it while moving.
    PROCESS_POWER_THROTTLING_STATE pt = {PROCESS_POWER_THROTTLING_CURRENT_VERSION,
                                         PROCESS_POWER_THROTTLING_IGNORE_TIMER_RESOLUTION, 0};
    SetProcessInformation(GetCurrentProcess(), ProcessPowerThrottling, &pt, sizeof(pt));

    g_moved = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_mouseWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_hideChanged = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_moved || !g_mouseWake || !g_hideChanged || !g_ready) return FALSE;

    // The render thread first: it creates the overlay window that receives the mouse input, and the others need it.
    LPTHREAD_START_ROUTINE procs[3] = {RenderThread, SampleThread, HideThread};
    for (int i = 0; i < 3; i++) {
        g_threads[i] = CreateThread(nullptr, 0, procs[i], nullptr, 0, nullptr);
        if (!g_threads[i]) {
            Wh_Log(L"CreateThread failed");
            StopThreads();
            return FALSE;
        }
        if (i < 2) SetThreadPriority(g_threads[i], THREAD_PRIORITY_ABOVE_NORMAL);
        if (i == 0 && (WaitForSingleObject(g_ready, 5000) != WAIT_OBJECT_0 || !g_wnd)) {
            StopThreads();
            return FALSE;
        }
    }
    g_trayThread = CreateThread(nullptr, 0, TrayThread, nullptr, 0, nullptr);
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    Wh_Log(L"SettingsChanged");
    LoadSettings();
    g_recheck = true;
    SetEvent(g_mouseWake);
    SetEvent(g_moved);   // lets the render thread notice a Renderer change right away
    if (HWND hwnd = papset::g_settingsWnd) PostMessageW(hwnd, papset::WM_APP_SETTINGS_RELOAD, 0, 0);
    if (HWND hwnd = g_trayWnd) PostMessageW(hwnd, WM_APP_TRAY_REFRESH, 0, 0);
}

void WhTool_ModUninit() {
    Wh_Log(L"Uninit");
    papset::CloseSettingsWindow();
    StopTrayThread();
    StopThreads();
    SetUnhandledExceptionFilter(g_prevFilter);
}

// ---- explorer.exe: a window above the Start menu ----
// Windows lets only some of its own processes put a window above the Start menu, Search and the notification centre,
// and explorer.exe is one of them. In explorer.exe the mod only creates that window (in the UIAccess band, or the
// system tools band) and runs its message loop; the mod's own process finds it and draws in it. Nothing else runs here.

extern "C" IMAGE_DOS_HEADER __ImageBase;   // this mod's module
static HANDLE g_bandThread;
static DWORD g_bandThreadId;

static DWORD WINAPI BandThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);   // the mod's process draws in pixels
    HINSTANCE inst = (HINSTANCE)&__ImageBase;
    WNDCLASSW wc = {};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = inst;
    wc.lpszClassName = BAND_CLASS;
    RegisterClassW(&wc);
    using CreateWindowInBand_t = HWND(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU,
                                               HINSTANCE, LPVOID, DWORD);
    auto createInBand = (CreateWindowInBand_t)GetProcAddress(GetModuleHandleW(L"user32.dll"), "CreateWindowInBand");
    HWND w = nullptr;
    static const DWORD bands[] = {2, 16};   // ZBID_UIACCESS, ZBID_SYSTEM_TOOLS
    for (DWORD band : bands) {
        if (!createInBand) break;
        w = createInBand(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
                         BAND_CLASS, L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, inst, nullptr, band);
        Wh_Log(L"CreateWindowInBand(%lu): %p (%lu)", band, w, w ? 0 : GetLastError());
        if (w) {
            SetPropW(w, L"NonRudeHWND", (HANDLE)TRUE);   // see CreateOverlay
            break;
        }
    }
    // The mod's process draws in the window and tells it which process it is; when that process ends, however it
    // ends, the window hides, so a crashed or killed mod never leaves its last frame on screen.
    HANDLE watched = nullptr;
    for (bool quit = !w; !quit;) {
        if (MsgWaitForMultipleObjects(watched ? 1 : 0, &watched, FALSE, INFINITE, QS_ALLINPUT) == WAIT_OBJECT_0 &&
            watched) {
            ShowWindow(w, SW_HIDE);
            if (Wh_GetIntValue(g_hiddenKey, 0)) {   // it was killed while hiding the cursor: put the cursors back now
                Wh_Log(L"The mod's process ended while hiding the cursor: restoring the cursors");
                ReloadCursors();
                Wh_SetIntValue(g_hiddenKey, 0);
            }
            CloseHandle(watched);
            watched = nullptr;
            continue;
        }
        MSG m;
        while (!quit && PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE)) {
            if (m.message == WM_QUIT) {
                quit = true;
            } else if (m.message == WM_APP_WATCH && m.hwnd == w) {
                // only a process that owns the mod's own window
                DWORD pid = (DWORD)m.wParam, owner;
                for (HWND t = FindWindowExW(nullptr, nullptr, OVERLAY_CLASS, nullptr); t;
                     t = FindWindowExW(nullptr, t, OVERLAY_CLASS, nullptr)) {
                    if (!GetWindowThreadProcessId(t, &owner) || owner != pid) continue;
                    if (HANDLE h = OpenProcess(SYNCHRONIZE, FALSE, pid)) {
                        if (watched) CloseHandle(watched);
                        watched = h;
                    }
                    break;
                }
            } else {
                DispatchMessageW(&m);
            }
        }
    }
    if (watched) CloseHandle(watched);
    if (w) DestroyWindow(w);
    UnregisterClassW(BAND_CLASS, inst);
    return 0;
}

// Only the shell's explorer.exe makes the window: not folder windows in processes of their own, and not the brief ones
// that hand a path to the shell ("Show in folder", explorer.exe C:\...). Once the desktop exists, its owner is the
// shell; while explorer is starting there is none yet, and the command line tells.
static bool IsShellExplorer() {
    if (HWND shell = GetShellWindow()) {
        DWORD owner = 0;
        GetWindowThreadProcessId(shell, &owner);
        return owner == GetCurrentProcessId();
    }
    WCHAR cmd[1024];
    wcsncpy_s(cmd, GetCommandLineW(), _TRUNCATE);
    _wcslwr_s(cmd);
    return !wcsstr(cmd, L"/factory") && !wcsstr(cmd, L"/separate") && !wcsstr(cmd, L"-embedding");
}

static void StopBandThread() {
    if (!g_bandThread) return;
    do PostThreadMessageW(g_bandThreadId, WM_QUIT, 0, 0);   // again while its message queue may not exist yet
    while (WaitForSingleObject(g_bandThread, 50) == WAIT_TIMEOUT);
    CloseHandle(g_bandThread);
    g_bandThread = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process
//
// The mod will load and run in a dedicated windhawk.exe process.
//
// Paste the code below as part of the mod code, and use these callbacks:
// * WhTool_ModInit
// * WhTool_ModSettingsChanged
// * WhTool_ModUninit
//
// Currently, other callbacks are not supported.

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;
bool g_isExplorer;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    WCHAR exe[MAX_PATH];
    GetModuleFileNameW(nullptr, exe, ARRAYSIZE(exe));
    const WCHAR* name = wcsrchr(exe, L'\\');
    if (name && !_wcsicmp(name + 1, L"explorer.exe")) {
        if (!IsShellExplorer()) return FALSE;
        g_isExplorer = true;
        BuildHiddenKey();
        g_bandThread = CreateThread(nullptr, 0, BandThread, nullptr, 0, &g_bandThreadId);
        return TRUE;
    }

    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) {
                isCurrentToolModProcess = true;
            }
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded) {
        return FALSE;
    }

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex =
            CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

        DWORD entryPointRVA = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRVA;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR
    commandLine[MAX_PATH + 2 +
                (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher || g_isExplorer) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isExplorer) {
        StopBandThread();
        return;
    }

    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}
