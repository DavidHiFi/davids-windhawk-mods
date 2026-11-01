// ==WindhawkMod==
// @id              window-borders
// @name            Window Borders
// @description     Smooth, rounded borders around your windows, with one color for the active window and another for the rest
// @version         2.1.0
// @author          DavidHiFi, Guerra24, lukeyou05
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @compilerOptions -ldwmapi -luser32 -lgdi32 -lshcore -lshell32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
Draws a smooth, rounded border around every normal window. The window you are
using gets one color and background windows get another, and the color fades
when focus moves.

## Features
- **Follows your accent.** The active border can use your Windows accent color
  and updates when you change it. Any hex color like #89b4fa works too.
- **Gradients.** Each border can fade from one color to another at any angle.
- **Hides when it should.** No border on maximized, minimized or fullscreen
  windows, or on windows parked on another virtual desktop.
- **Menus too (optional).** Turn on "Menus" and right-click menus and their
  submenus get the active window border, so menus match your windows.
- **Never in the way.** Clicks go straight through the border, and it never
  takes focus.
- **Stays out of your apps.** The mod runs in its own small Windhawk process
  and loads into no other program, so it works the same in every app and an
  app that hangs can't take the border down with it.

## Notes
- Windows 11 22H2 or newer and Windhawk 2.0 or newer.
- Menus covers classic Win32 menus, the kind most right-click menus use. Menus
  drawn by an app itself (browsers, Discord) keep their own look.
- Menus draw square unless something rounds them; match "Menu corner radius" to
  what you see, or set it to 0 for square menus.
- The border is drawn from outside the app, so during a fast drag it can trail
  the window edge by a frame.
- Turning the mod off removes every border at once.

## Credits
The "special windows" rule that picks which windows get a border comes from
[Windows 11 Accent Window Border](https://windhawk.net/mods/win11-accent-border)
by [Guerra24](https://github.com/Guerra24). Drawing borders from a separate
process with click-through windows is the idea behind
[Tacky Borders](https://github.com/lukeyou05/tacky-borders) by
[lukeyou05](https://github.com/lukeyou05). No code was copied from either.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
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
- radius: 16
  $name: Corner radius
  $description: >-
    Roundness of the border corners in pixels. Match it to your window corners;
    8 is the Windows 11 default and 0 gives square corners.
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
- exclude: [""]
  $name: Skip these apps
  $description: >-
    Program file names whose windows get no border, for example notepad.exe.
*/
// ==/WindhawkModSettings==

// Draws one smooth ring around every normal window. The mod runs as a Windhawk
// tool mod: it lives in its own windhawk.exe process and injects no code into
// other apps. WinEvent hooks report window moves, shows, hides and focus
// changes, and each ring is drawn in its own click-through layered windows.

#include <dwmapi.h>
#include <shellapi.h>
#include <shellscalingapi.h>
#include <windhawk_api.h>
#include <windows.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace {

constexpr wchar_t kMainClass[] = L"WindowBordersMain";
constexpr wchar_t kPartClass[] = L"WindowBordersPart";
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
    bool menus = false;
    bool gradient = true;
    bool focusedAccent = true;
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
    g_cfg = Config{};
    g_cfg.width = ReadInt(L"width", 1, 32);
    g_cfg.gap = ReadInt(L"gap", -8, 32);
    g_cfg.radius = ReadInt(L"radius", 0, 64);
    g_cfg.fadeMs = ReadInt(L"fadeMs", 0, 2000);
    g_cfg.gradientAngle = ReadInt(L"gradientAngle", 0, 360);
    g_cfg.gradient = Wh_GetIntSetting(L"gradient") != 0;
    g_cfg.menus = Wh_GetIntSetting(L"menus") != 0;
    g_cfg.menuRadius = ReadInt(L"menuRadius", 0, 64);

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
                   (float)s.offset, (float)s.width, ov.cur1, ov.cur2, (float)g_cfg.gradientAngle);
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
// Win32 menu (#32768), only with the Menus setting on. Tooltips, other popups
// and the shell's own surfaces get nothing. Pure, so it can be unit tested.
// BEGIN CLASSIFIER
Kind ClassifyWindow(DWORD style, DWORD ex, bool owned, const wchar_t* cls, bool menusOn) {
    if (style & WS_CHILD) {
        return Kind::None;
    }
    if (wcscmp(cls, L"#32768") == 0) {
        return menusOn ? Kind::Menu : Kind::None;
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

}  // namespace

bool WhTool_ModInit() {
    g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, RingThread, nullptr, 0, nullptr);
    if (!g_thread) {
        Wh_Log(L"CreateThread failed: %u", GetLastError());
        return false;
    }
    WaitForSingleObject(g_ready, 5000);
    return g_main != nullptr;
}

void WhTool_ModSettingsChanged() {
    if (g_main) {
        PostMessageW(g_main, kReloadMsg, 0, 0);
    }
}

void WhTool_ModUninit() {
    if (g_main) {
        PostMessageW(g_main, WM_CLOSE, 0, 0);
    }
    if (g_thread) {
        WaitForSingleObject(g_thread, 5000);
        CloseHandle(g_thread);
    }
}


#include <windhawk_tool_mod.h>
