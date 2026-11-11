// ==WindhawkMod==
// @id              seamless-borders
// @name            Seamless Borders
// @description     Colored borders around windows, menus and notification banners
// @version         1.0.4
// @author          DavidHiFi, m417z, Kanak415, leshaalexey, Guerra24, lukeyou05
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         GPL-3.0
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lole32 -lwevtapi -ld2d1 -ld3d11 -ldwmapi -luser32 -lgdi32 -lshcore -lshell32
// ==/WindhawkMod==

// Source code is published under The GNU General Public License v3.0.
//
// For bug reports and feature requests, please open an issue here:
// https://github.com/DavidHiFi/davids-windhawk-mods/issues

// ==WindhawkModReadme==
/*
# Seamless Borders

Colored borders for windows, menus and notification cards, with separate active and background colors.

![Window border preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/window-borders.png)

The preview shows window borders. Notification animation is still being tested.

## Features
- **Borders that follow focus.** The window you are using gets one color,
  background windows get another, and the color fades between them. The
  active color can follow your Windows accent color.
- **Notification borders (experimental).** Draws a border around the card
  found in each notification capture. Animation timing still needs live testing.
- **Gradients.** Each border can fade from one color to another at any
  angle.
- **Menus too (optional).** Right-click menus get the active border, so
  menus match your windows.
- **Never in the way.** Borders are click-through and never take focus, and
  the borders run in their own small Windhawk process, so a hanging app
  can't take the borders down with it.

## Setup

- Windows 11 22H2 or newer and Windhawk 2.0 or newer.

## Notes

- The taskbar, Start menu and notification center keep their own look;
  other mods style those.
- Menus draw square unless something rounds them; the "Corner radius"
  setting rounds them too, or match "Menu corner radius" to what you see.
- The border is drawn from outside the app, so during a fast drag it can
  trail the window edge by a frame.
- Window corner rounding remains controlled by Custom Window Corner Radius.
  Match the border radius to its window radius. This border host never loads in DWM.
- Disable other external border mods before using this mod.
- Notification borders are experimental. Their placement and timing depend
  on what Windows returns when the notification card is captured.

## Credits

Based on [Custom Window Corner Radius](https://windhawk.net/mods/custom-corner-radius)
by [m417z](https://github.com/m417z), originally submitted by
[Kanak415](https://github.com/kanak-buet19) with the maximized and snapped
option from a [mod](https://github.com/ramensoftware/windhawk-mods/pull/5022) by
[Alexey Lavrinenko](https://github.com/leshaalexey). Published under GPL-3.0
like the original. The rule that picks which windows get a border comes from
[Windows 11 Accent Window Border](https://windhawk.net/mods/win11-accent-border)
by [Guerra24](https://github.com/Guerra24), and drawing borders from a
separate process is the idea behind
[Tacky Borders](https://github.com/lukeyou05/tacky-borders) by
[lukeyou05](https://github.com/lukeyou05). No code was copied from either.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- radius: 16
  $name: Border corner radius
  $description: Roundness of window borders. Match this to your window corners.
- focusedColor: accent
  $name: Active window color
  $description: >-
    Border color of the window you are using. "accent" follows your Windows
    accent color. Use a hex color like #89b4fa for anything else.
- focusedColorTo: "#cba6f7"
  $name: Active window end color
  $description: With the gradient on, the active border fades into this color.
- unfocusedColor: "#585b70"
  $name: Background window color
  $description: Border color of every other window, as a hex color.
- unfocusedColorTo: "#585b70"
  $name: Background window end color
  $description: >-
    With the gradient on, background borders fade into this color. Keep it the
    same as the background window color for a plain line.
- gradient: true
  $name: Gradient
  $description: Fade each border from its color to its end color.
- gradientAngle: 45
  $name: Gradient angle
  $description: Direction of the gradient in degrees.
- width: 2
  $name: Width
  $description: Border thickness in pixels at 100% scaling.
- gap: -1
  $name: Gap
  $description: >-
    Space between the window edge and the border, in pixels. A negative value
    lets the border overlap the window edge.
- fadeMs: 150
  $name: Fade time
  $description: >-
    How long the color takes to change when focus moves, in milliseconds. 0
    switches instantly.
- menus: false
  $name: Menus
  $description: >-
    Also draw the active window border around right-click menus and their
    submenus.
- menuRadius: 8
  $name: Menu corner radius
  $description: >-
    Roundness of menu borders in pixels. Match it to your menu corners; 8 is
    the Windows 11 default.
- menuGradientAngle: 0
  $name: Menu gradient angle
  $description: >-
    Direction of the menu border gradient in degrees (0 to 360). 0 runs
    left to right, like the taskbar menus.
- toast: true
  $name: Notification borders
  $description: >-
    Also draw the active window border around toast notifications. The ring
    rides the notification card while it slides in and out, then rests on it.
- toastRadius: 8
  $name: Notification corner radius
  $description: >-
    Roundness of notification rings in pixels. 8 matches the Windows 11
    default card corners.
- toastGap: 0
  $name: Notification gap
  $description: >-
    Space between the notification card edge and the ring, in pixels. A
    negative value lets the ring overlap the card edge.
- exclude: [""]
  $name: Skip these apps
  $description: >-
    Program file names whose windows get no border, for example notepad.exe.
*/
// ==/WindhawkModSettings==

// Window, menu and notification borders run in a dedicated tool host.

#include <windhawk_utils.h>

#include <initguid.h>  // Must appear before propkey.h

#include <d2d1_1.h>
#include <d3d11.h>
#include <dwmapi.h>
#include <propkey.h>
#include <propsys.h>
#include <shellapi.h>
#include <shellscalingapi.h>
#include <winevt.h>
#include <winrt/base.h>
#include <winternl.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <limits>
#include <mutex>
#include <regex>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

// Creates one smooth ring around every normal window and every toast card.
// The mod runs as a Windhawk tool mod: it lives in its own windhawk.exe
// process and injects no code into other apps. WinEvent hooks report window
// moves, shows, hides and focus changes, and each ring is drawn in its own
// click-through layered windows. Toasts are sampled by a second thread that
// reads the card's pixels directly, so its ring rides the slide-in, the
// fade-out and the settled banner.

namespace borders {

#ifndef PW_RENDERFULLCONTENT
// PrintWindow flag that lets it capture DWM-composited content (Win8+). Newer
// SDKs define it; define it here so any SDK builds.
#define PW_RENDERFULLCONTENT 0x00000002
#endif

constexpr wchar_t kMainClass[] = L"SeamlessBordersMain";
constexpr wchar_t kPartClass[] = L"SeamlessBordersPart";
constexpr wchar_t kToastClass[] = L"SeamlessBordersToast";
constexpr UINT kReloadMsg = WM_APP + 1;
constexpr UINT_PTR kResyncTimer = 1;
constexpr UINT_PTR kFadeTimer = 2;
constexpr UINT kFadeFrameMs = 16;
constexpr UINT kResyncMs = 500;

struct Ring {
    float r = 0, g = 0, b = 0, a = 0;
};

struct Config {
    int width = 2;
    int gap = -1;
    int radius = 16;
    int fadeMs = 150;
    int gradientAngle = 45;
    int menuRadius = 8;
    int menuGradientAngle = 0;
    bool menus = false;
    bool gradient = true;
    bool focusedAccent = true;
    bool toast = true;
    int toastRadius = 8;
    int toastGap = 0;
    COLORREF focused = RGB(0x89, 0xb4, 0xfa);
    COLORREF focusedTo = RGB(0xcb, 0xa6, 0xf7);
    COLORREF unfocused = RGB(0x58, 0x5b, 0x70);
    COLORREF unfocusedTo = RGB(0x58, 0x5b, 0x70);
    std::vector<std::wstring> exclude;
};

// Four strips per window, so a big window never needs one huge bitmap.
struct Overlay {
    HWND parts[4] = {};
    RECT frame = {};
    UINT dpi = 96;
    bool focused = false;
    bool shown = false;
    bool dirty = true;
    bool fading = false;
    bool menu = false;
    DWORD fadeStart = 0;
    int fadeMs = 0;
    Ring cur1, cur2, from1, from2, to1, to2;
};

enum class Kind { None, Window, Menu };

SRWLOCK g_cfgLock = SRWLOCK_INIT;
Config g_cfg;
HINSTANCE g_instance = (HINSTANCE)&__ImageBase;
HANDLE g_thread = nullptr;
HANDLE g_ready = nullptr;
HWND g_main = nullptr;
COLORREF g_accent = 0;
std::unordered_map<HWND, Overlay> g_overlays;
std::unordered_map<DWORD, bool> g_pidExcluded;
HANDLE g_pacerWake = nullptr;
std::atomic<bool> g_fadingAny{false};
std::atomic<bool> g_fadePending{false};
std::atomic<bool> g_resyncPending{false};

HANDLE g_toastThread = nullptr;         // dedicated process only
std::atomic<bool> g_toastStop{false};   // set once, on uninit
std::atomic<bool> g_toastReload{false};

// ---------------------------------------------------------------------------
// Pacing
// ---------------------------------------------------------------------------

// The only clock. Posts a fade frame every kFadeFrameMs while a fade runs and a
// resync every kResyncMs. SetTimer's synthesized WM_TIMER can starve forever
// under a WinEvent flood; posted messages always process. The pending flags
// keep at most one of each tick in the queue.
DWORD WINAPI PacerThread(LPVOID stop) {
    HANDLE waits[2] = {(HANDLE)stop, g_pacerWake};
    DWORD lastResync = GetTickCount();
    for (;;) {
        DWORD r = WaitForMultipleObjects(2, waits, FALSE, g_fadingAny ? kFadeFrameMs : kResyncMs);
        if (r == WAIT_OBJECT_0 || r == WAIT_FAILED) {
            break;
        }
        if (g_fadingAny && !g_fadePending.exchange(true)) {
            PostMessageW(g_main, WM_TIMER, kFadeTimer, 0);
        }
        if (GetTickCount() - lastResync >= kResyncMs) {
            lastResync = GetTickCount();
            if (!g_resyncPending.exchange(true)) {
                PostMessageW(g_main, WM_TIMER, kResyncTimer, 0);
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Settings
// ---------------------------------------------------------------------------

int ReadInt(const wchar_t* name, int lo, int hi) {
    int v = Wh_GetIntSetting(name);
    return v < lo ? lo : (v > hi ? hi : v);
}

COLORREF ParseHex(const std::wstring& text, COLORREF fallback) {
    std::wstring hex = !text.empty() && text[0] == L'#' ? text.substr(1) : text;
    if (hex.size() != 6) {
        return fallback;
    }
    wchar_t* end = nullptr;
    unsigned long v = wcstoul(hex.c_str(), &end, 16);
    if (*end) {
        return fallback;
    }
    return RGB((v >> 16) & 0xff, (v >> 8) & 0xff, v & 0xff);
}

std::wstring ReadString(const wchar_t* name) {
    PCWSTR value = Wh_GetStringSetting(name);
    std::wstring text = value;
    Wh_FreeStringSetting(value);
    size_t first = text.find_first_not_of(L" ");
    return first == std::wstring::npos ? L""
                                       : text.substr(first, text.find_last_not_of(L" ") - first + 1);
}

void LoadConfig() {
    AcquireSRWLockExclusive(&g_cfgLock);

    g_cfg = Config{};
    g_cfg.width = ReadInt(L"width", 1, 32);
    g_cfg.gap = ReadInt(L"gap", -8, 32);
    // A negative radius means "keep DWM's own corner radius", which isn't a
    // number the border can draw with. It then uses the Win11 default.
    int radius = Wh_GetIntSetting(L"radius");
    g_cfg.radius = radius < 0 ? 8 : (radius > 64 ? 64 : radius);
    g_cfg.fadeMs = ReadInt(L"fadeMs", 0, 2000);
    g_cfg.gradientAngle = ReadInt(L"gradientAngle", 0, 360);
    g_cfg.gradient = Wh_GetIntSetting(L"gradient") != 0;
    g_cfg.menus = Wh_GetIntSetting(L"menus") != 0;
    g_cfg.menuRadius = ReadInt(L"menuRadius", 0, 64);
    g_cfg.menuGradientAngle = ReadInt(L"menuGradientAngle", 0, 360);
    g_cfg.toast = Wh_GetIntSetting(L"toast") != 0;
    g_cfg.toastRadius = ReadInt(L"toastRadius", 0, 64);
    g_cfg.toastGap = ReadInt(L"toastGap", -8, 32);

    std::wstring focused = ReadString(L"focusedColor");
    g_cfg.focusedAccent = focused.empty() || _wcsicmp(focused.c_str(), L"accent") == 0;
    g_cfg.focused = ParseHex(focused, g_cfg.focused);
    g_cfg.focusedTo = ParseHex(ReadString(L"focusedColorTo"), g_cfg.focusedTo);
    g_cfg.unfocused = ParseHex(ReadString(L"unfocusedColor"), g_cfg.unfocused);
    g_cfg.unfocusedTo = ParseHex(ReadString(L"unfocusedColorTo"), g_cfg.unfocusedTo);

    for (int i = 0;; i++) {
        PCWSTR value = Wh_GetStringSetting(L"exclude[%d]", i);
        bool end = !*value;
        std::wstring item = value;
        Wh_FreeStringSetting(value);
        if (end) {
            break;
        }
        size_t first = item.find_first_not_of(L" ");
        if (first != std::wstring::npos) {
            g_cfg.exclude.push_back(item.substr(first, item.find_last_not_of(L" ") - first + 1));
        }
    }

    ReleaseSRWLockExclusive(&g_cfgLock);
}

// The toast thread takes a snapshot instead of touching g_cfg, so a settings
// reload on the ring thread can never show it a half-written config.
Config SnapshotConfig() {
    AcquireSRWLockShared(&g_cfgLock);
    Config cfg = g_cfg;
    ReleaseSRWLockShared(&g_cfgLock);
    return cfg;
}

// ---------------------------------------------------------------------------
// Colors
// ---------------------------------------------------------------------------

COLORREF AccentRgb() {
    DWORD argb = 0;
    BOOL opaque = FALSE;
    if (FAILED(DwmGetColorizationColor(&argb, &opaque))) {
        return RGB(0x89, 0xb4, 0xfa);
    }
    return RGB((argb >> 16) & 0xff, (argb >> 8) & 0xff, argb & 0xff);
}

Ring ToRing(COLORREF c) {
    return {GetRValue(c) / 255.0f, GetGValue(c) / 255.0f, GetBValue(c) / 255.0f, 1.0f};
}

void StateColors(bool focused, Ring* c1, Ring* c2) {
    COLORREF rgb = focused ? (g_cfg.focusedAccent ? AccentRgb() : g_cfg.focused) : g_cfg.unfocused;
    COLORREF to = focused ? g_cfg.focusedTo : g_cfg.unfocusedTo;
    *c1 = ToRing(rgb);
    *c2 = g_cfg.gradient ? ToRing(to) : *c1;
}

// StateColors from a snapshot, for the toast thread. Toasts always wear the
// active color; they never show the background one.
void ToastStateColors(const Config& cfg, Ring* c1, Ring* c2) {
    COLORREF rgb = cfg.focusedAccent ? AccentRgb() : cfg.focused;
    *c1 = ToRing(rgb);
    *c2 = cfg.gradient ? ToRing(cfg.focusedTo) : *c1;
}

// ---------------------------------------------------------------------------
// Ring renderer
// ---------------------------------------------------------------------------

// BEGIN RING RENDERER
float Clamp01(float v) {
    return v < 0 ? 0 : (v > 1 ? 1 : v);
}

Ring LerpColor(const Ring& x, const Ring& y, float t) {
    return {x.r + (y.r - x.r) * t, x.g + (y.g - x.g) * t, x.b + (y.b - x.b) * t,
            x.a + (y.a - x.a) * t};
}

// Rows/columns from each canvas edge that can hold ring pixels.
int RingBand(int pad, float radius, float offset) {
    float inside = (offset < 0 ? -offset : 0) + 1;
    return pad + (int)ceilf(radius > inside ? radius : inside) + 1;
}

// The canvas is the window frame grown by pad on every side (fw x fh pixels).
// Draws the part of the ring inside the strip (sx, sy, sw, sh) into a zeroed,
// top-down, premultiplied BGRA buffer. The ring spans [offset, offset + width]
// outside the frame edge.
void RenderRing(uint32_t* px, int sx, int sy, int sw, int sh, int fw, int fh, int pad,
                float radius, float offset, float width, Ring c1, Ring c2, float angleDeg) {
    float cx = fw / 2.0f, cy = fh / 2.0f;
    float hx = fw / 2.0f - pad, hy = fh / 2.0f - pad;
    if (hx <= 0 || hy <= 0) {
        return;
    }
    float r = radius;
    if (r > hx) r = hx;
    if (r > hy) r = hy;

    float rad = angleDeg * 3.14159265f / 180.0f;
    float dx = cosf(rad), dy = sinf(rad);
    float span = fabsf(hx * dx) + fabsf(hy * dy) + pad;
    bool solid = c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;

    for (int y = 0; y < sh; y++) {
        for (int x = 0; x < sw; x++) {
            float fx = sx + x + 0.5f - cx, fy = sy + y + 0.5f - cy;
            float qx = fabsf(fx) - (hx - r), qy = fabsf(fy) - (hy - r);
            float ox = qx > 0 ? qx : 0, oy = qy > 0 ? qy : 0;
            float inner = qx > qy ? qx : qy;
            float d = sqrtf(ox * ox + oy * oy) + (inner < 0 ? inner : 0) - r;
            float cov = Clamp01(d - offset + 0.5f) * Clamp01(offset + width - d + 0.5f);
            if (cov <= 0) {
                continue;
            }
            Ring c = solid ? c1
                           : LerpColor(c1, c2, Clamp01((fx * dx + fy * dy) / span * 0.5f + 0.5f));
            float a = c.a * cov;
            px[y * sw + x] = ((uint32_t)(a * 255 + 0.5f) << 24) |
                             ((uint32_t)(c.r * a * 255 + 0.5f) << 16) |
                             ((uint32_t)(c.g * a * 255 + 0.5f) << 8) |
                             (uint32_t)(c.b * a * 255 + 0.5f);
        }
    }
}

// Splits the canvas into top, bottom, left and right strips. Returns how many
// are non-empty (left and right vanish on very short windows).
int RingStrips(int fw, int fh, int band, RECT out[4]) {
    if (band * 2 >= fh) {
        band = (fh + 1) / 2;
    }
    out[0] = {0, 0, fw, band};
    out[1] = {0, fh - band, fw, fh};
    out[2] = {0, band, band, fh - band};
    out[3] = {fw - band, band, fw, fh - band};
    return fh - band * 2 > 0 ? 4 : 2;
}

// END RING RENDERER

struct Shape {
    int pad = 0, width = 0, offset = 0, fw = 0, fh = 0, count = 0;
    float radius = 0;
    RECT strips[4] = {};
};

Shape ShapeFor(const Overlay& ov) {
    Shape s;
    float scale = ov.dpi / 96.0f;
    s.width = (int)ceilf(g_cfg.width * scale);
    s.offset = (int)roundf(g_cfg.gap * scale);
    s.pad = s.width + (s.offset > 0 ? s.offset : 0) + 1;
    s.radius = (ov.menu ? g_cfg.menuRadius : g_cfg.radius) * scale;
    s.fw = ov.frame.right - ov.frame.left + s.pad * 2;
    s.fh = ov.frame.bottom - ov.frame.top + s.pad * 2;
    s.count = RingStrips(s.fw, s.fh, RingBand(s.pad, s.radius, (float)s.offset), s.strips);
    return s;
}

// ---------------------------------------------------------------------------
// Overlay windows
// ---------------------------------------------------------------------------

bool CreateParts(HWND target, Overlay& ov) {
    DWORD ex = WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE;
    if (GetWindowLongPtrW(target, GWL_EXSTYLE) & WS_EX_TOPMOST) {
        ex |= WS_EX_TOPMOST;
    }
    for (int i = 0; i < 4; i++) {
        ov.parts[i] = CreateWindowExW(ex, kPartClass, L"", WS_POPUP | WS_DISABLED, 0, 0, 0, 0,
                                      nullptr, nullptr, g_instance, nullptr);
        if (!ov.parts[i]) {
            for (int j = 0; j < i; j++) {
                DestroyWindow(ov.parts[j]);
            }
            return false;
        }
    }
    return true;
}

void DestroyOverlay(HWND target) {
    auto it = g_overlays.find(target);
    if (it == g_overlays.end()) {
        return;
    }
    for (HWND part : it->second.parts) {
        DestroyWindow(part);
    }
    g_overlays.erase(it);
}

void DestroyAllOverlays() {
    std::vector<HWND> targets;
    for (auto& entry : g_overlays) {
        targets.push_back(entry.first);
    }
    for (HWND target : targets) {
        DestroyOverlay(target);
    }
}

// Keeps the strips directly above their target: the ring sits over the window
// it belongs to and under anything that covers that window.
void Restack(Overlay& ov, HWND target) {
    bool targetTopmost = GetWindowLongPtrW(target, GWL_EXSTYLE) & WS_EX_TOPMOST;
    // A window can join or leave the topmost band after its ring was made
    // (pin-on-top tools); the strips follow it so they never sink below it.
    if (targetTopmost != ((GetWindowLongPtrW(ov.parts[0], GWL_EXSTYLE) & WS_EX_TOPMOST) != 0)) {
        for (HWND part : ov.parts) {
            SetWindowPos(part, targetTopmost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
        }
    }
    HWND above = GetWindow(target, GW_HWNDPREV);
    if (above && !targetTopmost && (GetWindowLongPtrW(above, GWL_EXSTYLE) & WS_EX_TOPMOST)) {
        above = HWND_TOP;
    }
    if (above == ov.parts[3]) {
        return;
    }
    for (HWND part : ov.parts) {
        SetWindowPos(part, above ? above : HWND_TOP, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
        above = part;
    }
}

void PaintStrips(Overlay& ov) {
    Shape s = ShapeFor(ov);
    HDC dc = CreateCompatibleDC(nullptr);
    for (int i = 0; i < 4; i++) {
        HWND part = ov.parts[i];
        if (i >= s.count) {
            ShowWindow(part, SW_HIDE);
            continue;
        }
        const RECT& strip = s.strips[i];
        int sw = strip.right - strip.left, sh = strip.bottom - strip.top;
        BITMAPINFO bi = {};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = sw;
        bi.bmiHeader.biHeight = -sh;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        void* bits = nullptr;
        HBITMAP bmp = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!bmp) {
            continue;
        }
        RenderRing((uint32_t*)bits, strip.left, strip.top, sw, sh, s.fw, s.fh, s.pad, s.radius,
                   (float)s.offset, (float)s.width, ov.cur1, ov.cur2,
                   (float)(ov.menu ? g_cfg.menuGradientAngle : g_cfg.gradientAngle));
        HGDIOBJ old = SelectObject(dc, bmp);
        POINT dst = {ov.frame.left - s.pad + strip.left, ov.frame.top - s.pad + strip.top};
        SIZE size = {sw, sh};
        POINT src = {0, 0};
        BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        UpdateLayeredWindow(part, nullptr, &dst, &size, dc, &src, 0, &blend, ULW_ALPHA);
        SelectObject(dc, old);
        DeleteObject(bmp);
        ShowWindow(part, SW_SHOWNOACTIVATE);
    }
    DeleteDC(dc);
    ov.dirty = false;
    ov.shown = true;
}

// Same size, new position: slide the strips without repainting.
void MoveStrips(Overlay& ov) {
    Shape s = ShapeFor(ov);
    for (int i = 0; i < s.count; i++) {
        POINT dst = {ov.frame.left - s.pad + s.strips[i].left,
                     ov.frame.top - s.pad + s.strips[i].top};
        UpdateLayeredWindow(ov.parts[i], nullptr, &dst, nullptr, nullptr, nullptr, 0, nullptr, 0);
    }
}

void HideStrips(Overlay& ov) {
    if (!ov.shown) {
        return;
    }
    for (HWND part : ov.parts) {
        ShowWindow(part, SW_HIDE);
    }
    ov.shown = false;
}

// Fades from the current colors to the overlay's state colors over ms.
void StartFade(Overlay& ov, int ms) {
    StateColors(ov.focused, &ov.to1, &ov.to2);
    ov.dirty = true;
    if (ms <= 0) {
        ov.cur1 = ov.to1;
        ov.cur2 = ov.to2;
        ov.fading = false;
        return;
    }
    ov.from1 = ov.cur1;
    ov.from2 = ov.cur2;
    ov.fadeStart = GetTickCount();
    ov.fadeMs = ms;
    ov.fading = true;
    g_fadingAny = true;
    SetEvent(g_pacerWake);
}

// Moves one fade forward to now. Lands exactly on the target colors.
void StepFade(Overlay& ov) {
    float t = Clamp01((float)(GetTickCount() - ov.fadeStart) / ov.fadeMs);
    float e = 1 - (1 - t) * (1 - t);  // ease out
    ov.cur1 = t < 1 ? LerpColor(ov.from1, ov.to1, e) : ov.to1;
    ov.cur2 = t < 1 ? LerpColor(ov.from2, ov.to2, e) : ov.to2;
    ov.fading = t < 1;
    ov.dirty = true;
}

void FadeAll() {
    bool any = false;
    for (auto& entry : g_overlays) {
        Overlay& ov = entry.second;
        if (!ov.fading) {
            continue;
        }
        StepFade(ov);
        if (ov.shown) {
            PaintStrips(ov);
        }
        any = any || ov.fading;
    }
    g_fadingAny = any;
}


// ---------------------------------------------------------------------------
// Which windows get a ring
// ---------------------------------------------------------------------------

// Our own windows and the excluded programs get no ring. Cached per process.
bool ProcessExcluded(HWND hwnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (!pid || pid == GetCurrentProcessId()) {
        return true;
    }
    auto it = g_pidExcluded.find(pid);
    if (it != g_pidExcluded.end()) {
        return it->second;
    }
    if (g_pidExcluded.size() > 256) {
        g_pidExcluded.clear();  // pids of exited processes get reused
    }
    bool excluded = false;
    HANDLE proc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (proc) {
        wchar_t path[MAX_PATH];
        DWORD len = MAX_PATH;
        if (QueryFullProcessImageNameW(proc, 0, path, &len)) {
            const wchar_t* name = wcsrchr(path, L'\\');
            name = name ? name + 1 : path;
            for (const std::wstring& ex : g_cfg.exclude) {
                if (_wcsicmp(name, ex.c_str()) == 0) {
                    excluded = true;
                }
            }
        }
        CloseHandle(proc);
    }
    g_pidExcluded[pid] = excluded;
    return excluded;
}

// Window: a caption or sizing frame, or a frameless app window that would show
// in Alt+Tab (unowned, not a tool window, can take focus). Menu: a classic
// Win32 menu (#32768), only with the Menus setting on. Toasts and the other
// ImmersiveShell CoreWindows get nothing: the toast sampler draws their rings,
// and a second border tucked behind the toast would only double it.
// Tooltips, other popups and the shell's own surfaces get nothing. Pure, so
// it can be unit tested.
// BEGIN CLASSIFIER
Kind ClassifyWindow(DWORD style, DWORD ex, bool owned, const wchar_t* cls, bool menusOn) {
    if (style & WS_CHILD) {
        return Kind::None;
    }
    if (wcscmp(cls, L"#32768") == 0) {
        return menusOn ? Kind::Menu : Kind::None;
    }
    if (wcscmp(cls, L"Windows.UI.Core.CoreWindow") == 0) {
        return Kind::None;
    }
    bool framed = (style & WS_THICKFRAME) == WS_THICKFRAME || (style & WS_CAPTION) == WS_CAPTION;
    // win11-accent-border's "special windows" rule: any top-level window that is
    // not a popup (Flow Launcher, WPF and other custom-drawn windows).
    bool special = !(style & WS_POPUP);
    if (!framed && !special) {
        bool appWindow = ex & WS_EX_APPWINDOW;
        if ((ex & WS_EX_NOACTIVATE) || ((ex & WS_EX_TOOLWINDOW) && !appWindow) ||
            (owned && !appWindow)) {
            return Kind::None;
        }
    }
    if (!framed) {
        for (const wchar_t* shell : {L"Progman", L"WorkerW", L"Shell_TrayWnd",
                                     L"Shell_SecondaryTrayWnd"}) {
            if (wcscmp(cls, shell) == 0) {
                return Kind::None;
            }
        }
    }
    return Kind::Window;
}

// END CLASSIFIER

Kind Classify(HWND hwnd) {
    wchar_t cls[64] = {};
    GetClassNameW(hwnd, cls, 64);
    Kind kind = ClassifyWindow((DWORD)GetWindowLongPtrW(hwnd, GWL_STYLE),
                               (DWORD)GetWindowLongPtrW(hwnd, GWL_EXSTYLE),
                               GetWindow(hwnd, GW_OWNER) != nullptr, cls, g_cfg.menus);
    return kind != Kind::None && ProcessExcluded(hwnd) ? Kind::None : kind;
}

// False when the window is hidden, minimized, cloaked on another desktop,
// maximized or fullscreen. Those states get no ring. Menus skip the opacity
// rule (they fade in from nearly clear) and may be as small as 8 px.
bool GetDrawFrame(HWND target, RECT* frame, bool menu) {
    if (!IsWindowVisible(target) || IsIconic(target) || IsZoomed(target)) {
        return false;
    }
    BOOL cloaked = FALSE;
    if (SUCCEEDED(DwmGetWindowAttribute(target, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) &&
        cloaked) {
        return false;
    }
    // Near-invisible layered windows are helpers, not something you look at
    // (RHI parks a 2% opacity drag-and-drop target over its logo).
    BYTE alpha = 255;
    DWORD layeredFlags = 0;
    if (!menu && (GetWindowLongPtrW(target, GWL_EXSTYLE) & WS_EX_LAYERED) &&
        GetLayeredWindowAttributes(target, nullptr, &alpha, &layeredFlags) &&
        (layeredFlags & LWA_ALPHA) && alpha < 64) {
        return false;
    }
    if (FAILED(DwmGetWindowAttribute(target, DWMWA_EXTENDED_FRAME_BOUNDS, frame,
                                     sizeof(*frame)))) {
        return false;
    }
    // Tiny helper windows and windows parked off every screen get no ring.
    // 40 px keeps a bare Flow Launcher search bar (58 px tall) in.
    int minSize = menu ? 8 : 40;
    if (frame->right - frame->left < minSize || frame->bottom - frame->top < minSize) {
        return false;
    }
    HMONITOR monitor = MonitorFromRect(frame, MONITOR_DEFAULTTONULL);
    MONITORINFO mi = {sizeof(mi)};
    if (!monitor) {
        return false;
    }
    if (GetMonitorInfoW(monitor, &mi) &&
        frame->left <= mi.rcMonitor.left && frame->top <= mi.rcMonitor.top &&
        frame->right >= mi.rcMonitor.right && frame->bottom >= mi.rcMonitor.bottom) {
        return false;
    }
    return true;
}

// Brings one window's ring in line with the window. Runs on the ring thread only.
void SyncTarget(HWND target) {
    Kind kind = Classify(target);
    if (kind == Kind::None) {
        DestroyOverlay(target);
        return;
    }
    bool menu = kind == Kind::Menu;
    RECT frame = {};
    auto it = g_overlays.find(target);
    if (!GetDrawFrame(target, &frame, menu)) {
        // A closed menu is gone for good; its next opening fades in fresh.
        if (menu) {
            DestroyOverlay(target);
        } else if (it != g_overlays.end()) {
            HideStrips(it->second);
        }
        return;
    }

    UINT dpi = 96, dpiY = 96;
    HMONITOR monitor = MonitorFromRect(&frame, MONITOR_DEFAULTTONEAREST);
    if (FAILED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpi, &dpiY)) || !dpi) {
        dpi = 96;
    }
    // Menus never take focus, so they always wear the active color.
    bool focused = menu || GetForegroundWindow() == target;

    if (it == g_overlays.end()) {
        Overlay fresh;
        if (!CreateParts(target, fresh)) {
            return;
        }
        fresh.menu = menu;
        fresh.focused = focused;
        StateColors(focused, &fresh.cur1, &fresh.cur2);
        fresh.to1 = fresh.cur1;
        fresh.to2 = fresh.cur2;
        it = g_overlays.emplace(target, fresh).first;
        if (menu) {
            // Fade in alongside the menu's own fade.
            it->second.cur1.a = it->second.cur2.a = 0;
            StartFade(it->second, std::min(g_cfg.fadeMs, 120));
        }
    }
    Overlay& ov = it->second;
    if (focused != ov.focused) {
        ov.focused = focused;
        StartFade(ov, g_cfg.fadeMs);
    }
    // Advance any running fade here too, so a ring lands on its exact color
    // even if fade ticks fall behind.
    if (ov.fading) {
        StepFade(ov);
    }

    bool resized = frame.right - frame.left != ov.frame.right - ov.frame.left ||
                   frame.bottom - frame.top != ov.frame.bottom - ov.frame.top;
    bool moved = !EqualRect(&frame, &ov.frame);
    bool rescaled = dpi != ov.dpi;
    ov.frame = frame;
    ov.dpi = dpi;
    if (resized || rescaled || ov.dirty || !ov.shown) {
        PaintStrips(ov);
    } else if (moved) {
        MoveStrips(ov);
    }
    Restack(ov, target);
}

BOOL CALLBACK SyncWindow(HWND hwnd, LPARAM seen) {
    ((std::vector<HWND>*)seen)->push_back(hwnd);
    SyncTarget(hwnd);
    return TRUE;
}

// Full pass: every top-level window, plus a check that the accent color is
// current. Called on a timer, on focus changes and at startup.
void ResyncAll() {
    COLORREF accent = AccentRgb();
    if (accent != g_accent) {
        g_accent = accent;
        for (auto& entry : g_overlays) {
            if (entry.second.focused) {
                StartFade(entry.second, g_cfg.fadeMs);
            }
        }
    }
    // A ring whose window is no longer top-level (destroyed, or re-parented into
    // another window) would otherwise float on screen with nothing under it.
    std::vector<HWND> seen;
    EnumWindows(SyncWindow, (LPARAM)&seen);
    std::vector<HWND> gone;
    for (auto& entry : g_overlays) {
        if (std::find(seen.begin(), seen.end(), entry.first) == seen.end()) {
            gone.push_back(entry.first);
        }
    }
    for (HWND target : gone) {
        DestroyOverlay(target);
    }
}

void CALLBACK OnWinEvent(HWINEVENTHOOK, DWORD event, HWND hwnd, LONG idObject, LONG idChild,
                         DWORD, DWORD) {
    if (event == EVENT_SYSTEM_FOREGROUND) {
        ResyncAll();
        return;
    }
    // Menu popup events name the menu window with OBJID_CLIENT.
    if (hwnd && (event == EVENT_SYSTEM_MENUPOPUPSTART || event == EVENT_SYSTEM_MENUPOPUPEND)) {
        if (event == EVENT_SYSTEM_MENUPOPUPEND) {
            DestroyOverlay(hwnd);
        } else {
            SyncTarget(hwnd);
        }
        return;
    }
    if (!hwnd || idObject != OBJID_WINDOW || idChild != CHILDID_SELF) {
        return;
    }
    if (event == EVENT_OBJECT_DESTROY) {
        DestroyOverlay(hwnd);
        return;
    }
    if (GetWindowLongPtrW(hwnd, GWL_STYLE) & WS_CHILD) {
        DestroyOverlay(hwnd);
        return;
    }
    SyncTarget(hwnd);
}

LRESULT CALLBACK PartProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_NCHITTEST:
            return HTTRANSPARENT;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

LRESULT CALLBACK MainProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_TIMER:
            if (wp == kResyncTimer) {
                g_resyncPending = false;
                ResyncAll();
            } else if (wp == kFadeTimer) {
                g_fadePending = false;
                FadeAll();
            }
            return 0;
        case kReloadMsg:
            // New settings: rebuild every ring with the new look and app list.
            DestroyAllOverlays();
            g_pidExcluded.clear();
            LoadConfig();
            g_toastReload = true;
            ResyncAll();
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// The ring thread owns every ring window and the WinEvent hooks, which deliver
// their events through this thread's message loop.
DWORD WINAPI RingThread(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    LoadConfig();

    WNDCLASSEXW mainClass = {sizeof(mainClass)};
    mainClass.lpfnWndProc = MainProc;
    mainClass.hInstance = g_instance;
    mainClass.lpszClassName = kMainClass;
    RegisterClassExW(&mainClass);

    WNDCLASSEXW partClass = {sizeof(partClass)};
    partClass.lpfnWndProc = PartProc;
    partClass.hInstance = g_instance;
    partClass.lpszClassName = kPartClass;
    RegisterClassExW(&partClass);

    g_main = CreateWindowExW(0, kMainClass, L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                             g_instance, nullptr);
    SetEvent(g_ready);
    if (!g_main) {
        Wh_Log(L"CreateWindowExW failed: %u", GetLastError());
        return 1;
    }

    const DWORD events[] = {
        EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_MINIMIZESTART, EVENT_SYSTEM_MINIMIZEEND,
        EVENT_SYSTEM_MOVESIZEEND, EVENT_OBJECT_CREATE, EVENT_OBJECT_SHOW,
        EVENT_OBJECT_HIDE, EVENT_OBJECT_DESTROY, EVENT_OBJECT_LOCATIONCHANGE,
        EVENT_OBJECT_CLOAKED, EVENT_OBJECT_UNCLOAKED,
        EVENT_SYSTEM_MENUPOPUPSTART, EVENT_SYSTEM_MENUPOPUPEND,
    };
    std::vector<HWINEVENTHOOK> hooks;
    for (DWORD event : events) {
        HWINEVENTHOOK hook = SetWinEventHook(event, event, nullptr, OnWinEvent, 0, 0,
                                             WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        if (hook) {
            hooks.push_back(hook);
        }
    }

    HANDLE pacerStop = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_pacerWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    HANDLE pacer = nullptr;
    if (pacerStop && g_pacerWake) {
        pacer = CreateThread(nullptr, 0, PacerThread, pacerStop, 0, nullptr);
    }
    if (!pacer) {
        Wh_Log(L"Pacer thread failed: %u", GetLastError());
    }
    ResyncAll();

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (pacerStop) {
        SetEvent(pacerStop);
    }
    if (pacer) {
        WaitForSingleObject(pacer, 5000);
        CloseHandle(pacer);
    }
    if (pacerStop) {
        CloseHandle(pacerStop);
    }
    if (g_pacerWake) {
        CloseHandle(g_pacerWake);
        g_pacerWake = nullptr;
    }
    for (HWINEVENTHOOK hook : hooks) {
        UnhookWinEvent(hook);
    }
    DestroyAllOverlays();
    return 0;
}


// ---------------------------------------------------------------------------
// Toast sampler
// ---------------------------------------------------------------------------

// Toast cards are ImmersiveShell CoreWindows titled "New notification". They
// can't be hooked or subclassed from outside, but PrintWindow still reads their
// pixels (with PW_RENDERFULLCONTENT), and that is all the ring needs: each
// sample yields the visible card rectangle and its current opacity, which is
// everything the ring needs to follow the slide animation on screen. The ring
// follows each sampled card rectangle. Capture and drawing can still lag
// behind the compositor during animation.

constexpr int kToastHiddenAlpha = 12;    // card opacity below this hides the ring
constexpr int kToastHeadroomPx = 10;     // slack beyond the ring band on each side
constexpr DWORD kToastHotPaceMs = 9;     // pacing when the sample itself is cheap
constexpr DWORD kToastIdleMs = 10;       // pacing while no toast is up
constexpr DWORD kToastOffMs = 200;       // pacing while the setting is off

// A DIB, top-down, kept selected into its own memory DC.
struct ToastSurface {
    HDC mdc = nullptr;
    HBITMAP bmp = nullptr;
    HGDIOBJ previous = nullptr;
    uint8_t* bits = nullptr;
    int w = 0;
    int h = 0;
};

struct ToastState {
    HWND ring = nullptr;
    ToastSurface grab;    // reads the card
    ToastSurface canvas;  // draws the ring, one card rect + margin wide
    RECT canvasPos = {};
    bool visible = false;
    // Card rect in toast-local pixels, from the last sample.
    int cardLeft = 0, cardTop = 0, cardW = 0, cardH = 0, cardAlpha = 0;
    int fullCardW = 0, fullCardH = 0;
    int printMs = 0;
    // DPI-scaled ring geometry for the current card.
    float ringWidth = 2, ringGap = 0, ringRadius = 8;
    int margin = 12;
};

void FreeSurface(ToastSurface* s) {
    if (s->bmp) {
        if (s->mdc) {
            SelectObject(s->mdc, s->previous);
        }
        DeleteObject(s->bmp);
        s->bmp = nullptr;
    }
    if (s->mdc) {
        DeleteDC(s->mdc);
        s->mdc = nullptr;
    }
    s->previous = nullptr;
    s->bits = nullptr;
    s->w = 0;
    s->h = 0;
}

// Rebuilds the surface when its size is new; keeps it (and its selection)
// across samples - a per-sample CreateDIBSection doubles the sampling cost.
bool EnsureSurface(ToastSurface* s, int w, int h) {
    if (s->mdc && s->w == w && s->h == h) {
        return true;
    }
    FreeSurface(s);
    if (w <= 0 || h <= 0) {
        return false;
    }
    BITMAPINFO bi = {};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;  // top-down
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    s->bmp = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!s->bmp) {
        return false;
    }
    s->mdc = CreateCompatibleDC(nullptr);
    if (!s->mdc) {
        FreeSurface(s);
        return false;
    }
    s->previous = SelectObject(s->mdc, s->bmp);
    if (!s->previous || s->previous == HGDI_ERROR) {
        FreeSurface(s);
        return false;
    }
    s->bits = (uint8_t*)bits;
    s->w = w;
    s->h = h;
    return true;
}

// The first visible toast: same class as every ImmersiveShell CoreWindow
// (start menu, flyouts), so title filtering and the cloak check do the work.
HWND FindToast() {
    HWND hwnd = nullptr;
    while ((hwnd = FindWindowExW(nullptr, hwnd, L"Windows.UI.Core.CoreWindow",
                                 L"New notification")) != nullptr) {
        if (!IsWindowVisible(hwnd)) {
            continue;
        }
        BOOL cloaked = FALSE;
        if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) &&
            cloaked) {
            continue;
        }
        return hwnd;
    }
    return nullptr;
}

// Some Windows builds return an opaque black canvas even outside the card.
// In that format RGB, not alpha, identifies the captured outline and text.
bool AnalyzeToastPixels(const uint8_t* px, int w, int h, ToastState* t) {
    if (w <= 0 || h <= 0) return false;
    bool opaque = true;
    for (size_t i = 0; i < (size_t)w * h; i++) {
        if (px[i * 4 + 3] != 255) {
            opaque = false;
            break;
        }
    }
    int minX = w, minY = h, maxX = -1, maxY = -1, opacity = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            const uint8_t* p = px + ((size_t)y * w + x) * 4;
            int signal = opaque ? std::max({p[0], p[1], p[2]}) : p[3];
            if (signal > (opaque ? 8 : 16)) {
                minX = std::min(minX, x);
                maxX = std::max(maxX, x);
                minY = std::min(minY, y);
                maxY = std::max(maxY, y);
                opacity = std::max(opacity, signal);
            }
        }
    }
    if (maxX < 0) return false;
    // An opaque, filled capture has no separable card silhouette.
    if (opaque && minX == 0 && minY == 0 && maxX == w - 1 && maxY == h - 1)
        return false;
    t->cardLeft = minX;
    t->cardTop = minY;
    t->cardW = maxX - minX + 1;
    t->cardH = maxY - minY + 1;
    t->cardAlpha = opacity;
    return true;
}

// Reads one card sample. Returns false without touching the outputs when the
// toast can't be read this cycle (PrintWindow failure, gone window).
bool SampleToastCard(HWND toast, ToastState* t) {
    RECT toastRect;
    if (!GetWindowRect(toast, &toastRect)) {
        return false;
    }
    int w = toastRect.right - toastRect.left;
    int h = toastRect.bottom - toastRect.top;
    if (w <= 0 || h <= 0 || !EnsureSurface(&t->grab, w, h)) {
        return false;
    }

    LARGE_INTEGER qpcStart, qpcEnd, qpcFreq;
    QueryPerformanceCounter(&qpcStart);
    ZeroMemory(t->grab.bits, (size_t)w * h * 4);
    BOOL ok = PrintWindow(toast, t->grab.mdc, PW_RENDERFULLCONTENT);
    QueryPerformanceCounter(&qpcEnd);
    QueryPerformanceFrequency(&qpcFreq);
    t->printMs = ok ? (int)((qpcEnd.QuadPart - qpcStart.QuadPart) * 1000 / qpcFreq.QuadPart)
                    : 0;
    if (!ok) {
        return false;
    }

    if (!AnalyzeToastPixels(t->grab.bits, w, h, t)) {
        return false;
    }
    // A sliding card is clipped at the host's right edge. Keep the width of
    // the complete card so the ring slides instead of shrinking around it.
    if (t->cardLeft + t->cardW >= w && t->cardLeft > 0) {
        int dpi = GetDpiForWindow(toast);
        int defaultWidth = w - MulDiv(32, dpi ? dpi : 96, 96);
        t->cardW = std::max(t->cardW, t->fullCardW ? t->fullCardW : defaultWidth);
        if (t->fullCardH) t->cardH = t->fullCardH;
    } else {
        t->fullCardW = t->cardW;
        t->fullCardH = t->cardH;
    }
    return true;
}

// Sizes and positions the ring canvas for the toast as it sits right now.
bool EnsureToastCanvas(ToastState* t, const Config& cfg, HWND toast) {
    RECT toastRect;
    if (!GetWindowRect(toast, &toastRect)) {
        return false;
    }

    UINT dpi = 96, dpiY = 96;
    HMONITOR monitor = MonitorFromRect(&toastRect, MONITOR_DEFAULTTONEAREST);
    if (FAILED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpi, &dpiY)) || !dpi) {
        dpi = 96;
    }
    float scale = dpi / 96.0f;
    t->ringWidth = cfg.width * scale;
    t->ringGap = cfg.toastGap * scale;
    t->ringRadius = cfg.toastRadius * scale;
    t->margin =
        (int)ceilf((t->ringGap > 0 ? t->ringGap : 0) + t->ringWidth +
                   kToastHeadroomPx * scale) + 2;

    int x0 = toastRect.left + t->cardLeft - t->margin;
    int y0 = toastRect.top + t->cardTop - t->margin;
    int w = t->cardW + 2 * t->margin;
    int h = t->cardH + 2 * t->margin;
    if (!EnsureSurface(&t->canvas, w, h)) {
        return false;
    }
    t->canvasPos = RECT{x0, y0, x0 + w, y0 + h};
    return true;
}

void HideToastRing(ToastState* t) {
    if (t->visible) {
        ShowWindow(t->ring, SW_HIDE);
        t->visible = false;
    }
}

void DropToastSurfaces(ToastState* t) {
    FreeSurface(&t->grab);
    FreeSurface(&t->canvas);
}

// Draws the ring for one card sample and stacks the ring window a notch above
// the toast, both every cycle, using the latest sampled card rectangle.
void DrawToastRing(ToastState* t, const Config& cfg, HWND toast) {
    uint32_t* px = (uint32_t*)t->canvas.bits;
    int w = t->canvas.w, h = t->canvas.h;
    ZeroMemory(px, (size_t)w * h * 4);

    Ring c1, c2;
    ToastStateColors(cfg, &c1, &c2);

    float rad = cfg.gradientAngle * 3.14159265f / 180.0f;
    float dx = cosf(rad), dy = sinf(rad);
    bool solid = c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;

    // Card rect in canvas pixels; the canvas origin is the toast rect minus
    // the margin.
    float ccx = t->margin + t->cardW / 2.0f;
    float ccy = t->margin + t->cardH / 2.0f;
    float hx = t->cardW / 2.0f - t->ringRadius, hy = t->cardH / 2.0f - t->ringRadius;
    hx = hx < 0.5f ? 0.5f : hx;
    hy = hy < 0.5f ? 0.5f : hy;

    // The gradient spans the whole canvas, same as the window rings.
    float gcx = w / 2.0f, gcy = h / 2.0f;
    float span = fabsf(gcx * dx) + fabsf(gcy * dy);
    float alphaScale = t->cardAlpha / 255.0f;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            float fx = x + 0.5f - ccx, fy = y + 0.5f - ccy;
            float qx = fabsf(fx) - hx, qy = fabsf(fy) - hy;
            float ox = qx > 0 ? qx : 0, oy = qy > 0 ? qy : 0;
            float inner = qx > qy ? qx : qy;
            float d = sqrtf(ox * ox + oy * oy) + (inner < 0 ? inner : 0) - t->ringRadius;
            float cov = Clamp01(d - t->ringGap + 0.5f) *
                        Clamp01(t->ringGap + t->ringWidth - d + 0.5f);
            if (cov <= 0) {
                continue;
            }
            Ring c = solid ? c1
                           : LerpColor(c1, c2, Clamp01(((x + 0.5f - gcx) * dx +
                                                        (y + 0.5f - gcy) * dy) /
                                                           span * 0.5f + 0.5f));
            float a = c.a * cov * alphaScale;
            px[y * w + x] = ((uint32_t)(a * 255 + 0.5f) << 24) |
                            ((uint32_t)(c.r * a * 255 + 0.5f) << 16) |
                            ((uint32_t)(c.g * a * 255 + 0.5f) << 8) |
                            (uint32_t)(c.b * a * 255 + 0.5f);
        }
    }

    POINT dst = {t->canvasPos.left, t->canvasPos.top};
    SIZE size = {w, h};
    POINT src = {0, 0};
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    if (!UpdateLayeredWindow(t->ring, nullptr, &dst, &size, t->canvas.mdc, &src, 0, &blend,
                             ULW_ALPHA)) {
        Wh_Log(L"ULW failed: %u", GetLastError());
        return;
    }
    if (!t->visible) {
        ShowWindow(t->ring, SW_SHOWNOACTIVATE);
        t->visible = true;
    }
    // Directly above the toast: nothing else that covers the toast covers the
    // ring. Per-sample; the toast re-stacks itself as it animates.
    HWND above = GetWindow(toast, GW_HWNDPREV);
    if (above != t->ring) {
        SetWindowPos(t->ring, above ? above : HWND_TOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

// Sleeps out the pacing gap, then reports whether an uninit landed.
bool ToastStopped(DWORD ms) {
    MSG msg;
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    Sleep(ms);
    return g_toastStop;
}

// One toast at a time (the newest visible banner); the sampler hides the ring
// whenever the card fades out and redraws it whenever a new card shows up.
DWORD WINAPI ToastThread(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    WNDCLASSEXW toastClass = {sizeof(toastClass)};
    toastClass.lpfnWndProc = PartProc;
    toastClass.hInstance = g_instance;
    toastClass.lpszClassName = kToastClass;
    RegisterClassExW(&toastClass);

    Config cfg = SnapshotConfig();
    ToastState t;
    t.ring = CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW |
                                 WS_EX_NOACTIVATE | WS_EX_TOPMOST,
                             kToastClass, L"", WS_POPUP | WS_VISIBLE, 0, 0, 0, 0, nullptr,
                             nullptr, g_instance, nullptr);
    if (!t.ring) {
        Wh_Log(L"Toast ring window failed: %u", GetLastError());
        return 1;
    }

    HWND lastToast = nullptr;

    for (;;) {
        if (g_toastStop) {
            break;
        }

        if (!cfg.toast) {
            HideToastRing(&t);
            DropToastSurfaces(&t);
            lastToast = nullptr;
            if (ToastStopped(kToastOffMs)) {
                break;
            }
            if (g_toastReload.exchange(false)) {
                cfg = SnapshotConfig();
            }
            continue;
        }

        HWND toast = FindToast();
        if (!toast) {
            HideToastRing(&t);
            DropToastSurfaces(&t);
            lastToast = nullptr;
            if (ToastStopped(kToastIdleMs)) {
                break;
            }
            if (g_toastReload.exchange(false)) {
                cfg = SnapshotConfig();
            }
            continue;
        }

        if (toast != lastToast) {
            lastToast = toast;
            t.fullCardW = t.fullCardH = 0;
        }

        if (!SampleToastCard(toast, &t)) {
            // Unreadable window: hide and try again at the hot pace.
            HideToastRing(&t);
            if (ToastStopped(kToastHotPaceMs)) {
                break;
            }
            if (g_toastReload.exchange(false)) {
                cfg = SnapshotConfig();
            }
            continue;
        }

        if (t.cardAlpha < kToastHiddenAlpha) {
            HideToastRing(&t);
            if (ToastStopped(kToastHotPaceMs)) {
                break;
            }
            if (g_toastReload.exchange(false)) {
                cfg = SnapshotConfig();
            }
            continue;
        }

        if (EnsureToastCanvas(&t, cfg, toast)) {
            DrawToastRing(&t, cfg, toast);
        } else {
            HideToastRing(&t);
        }

        // Keep sampling at the same pace so dismissal is detected promptly.
        if (ToastStopped(t.printMs < 5 ? kToastHotPaceMs : 0)) {
            break;
        }
        if (g_toastReload.exchange(false)) {
            cfg = SnapshotConfig();
        }
    }

    HideToastRing(&t);
    DropToastSurfaces(&t);
    DestroyWindow(t.ring);
    return 0;
}

}  // namespace borders

using namespace borders;

// Runs only in the dedicated windhawk.exe tool process.
BOOL WhTool_ModInit() {
    g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, RingThread, nullptr, 0, nullptr);
    if (!g_thread) {
        Wh_Log(L"CreateThread failed: %u", GetLastError());
        return false;
    }
    WaitForSingleObject(g_ready, 5000);

    g_toastThread = CreateThread(nullptr, 0, ToastThread, nullptr, 0, nullptr);
    if (!g_toastThread) {
        Wh_Log(L"CreateThread (toast) failed: %u", GetLastError());
        return false;
    }
    return g_main != nullptr;
}

void WhTool_ModSettingsChanged() {
    if (g_main) {
        PostMessageW(g_main, kReloadMsg, 0, 0);
    }
}

void WhTool_ModUninit() {
    g_toastStop = true;
    if (g_toastThread) {
        if (WaitForSingleObject(g_toastThread, 10000) == WAIT_TIMEOUT) {
            Wh_Log(L"Toast thread didn't stop in time");
        }
        CloseHandle(g_toastThread);
        g_toastThread = nullptr;
    }
    if (g_main) {
        PostMessageW(g_main, WM_CLOSE, 0, 0);
    }
    if (g_thread) {
        WaitForSingleObject(g_thread, 5000);
        CloseHandle(g_thread);
        g_thread = nullptr;
    }
}

#include <windhawk_tool_mod.h>
