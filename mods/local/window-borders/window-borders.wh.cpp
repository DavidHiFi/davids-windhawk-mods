// ==WindhawkMod==
// @id              window-borders
// @name            Window Borders
// @description     Smooth, rounded window borders with their own colors for active and background windows
// @version         1.0.0
// @author          DavidHiFi, Guerra24, glzr-io
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         *
// @exclude         windhawk-ui.exe
// @exclude         dwm.exe
// @compilerOptions -ldwmapi -luser32 -lgdi32 -lshcore
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
Draws a colored border around your windows, with one color for the window you
are using and another for background windows.

There are two styles. **Overlay** (the default) draws its own smooth border on
top of the window frame: you pick the width, the corner radius and the gap, it
can use a gradient, and it fades when focus moves. **Thin** colors the 1 px line
Windows 11 already draws and changes nothing else.

## Features
- **Follows your accent.** The active border uses your Windows accent color and
  updates live when you change it. Any hex color like #89b4fa works too.
- **Hides when it should.** No border on maximized, minimized or fullscreen
  windows, or on windows parked on another virtual desktop.
- **Never in the way.** Clicks go straight through the border, and it never
  takes focus.
- **Clean off switch.** Disabling the mod removes every border and restores the
  Windows default line.

## Notes
- Windows 11 22H2 or newer.
- Made to replace the Windows border everywhere, so it loads into every app.
  If another mod already colors the border in an app, add that app to this
  mod's exclusion list in Windhawk so the two don't fight.
- Overlay borders move with the window from inside the app, so they keep up
  with dragging; an app that is frozen will freeze its border too.
- Some apps draw no frame at all by design, and they get no border.

## Credits
Based on [Windows 11 Accent Window Border](https://windhawk.net/mods/win11-accent-border)
by [Guerra24](https://github.com/Guerra24), the border re-apply approach used by
[GlazeWM](https://github.com/glzr-io/glazewm), and the overlay design of
[tacky-borders](https://github.com/luke-you/tacky-borders) by luke-you and
[cute-borders](https://github.com/keifufu/cute-borders) by keifufu (both MIT).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- mode: overlay
  $name: Border style
  $description: >-
    Overlay draws its own smooth border with any width, rounded corners,
    gradients and a fade on focus changes. Thin uses the 1 px line Windows
    already draws.
  $options:
  - overlay: Overlay (thick, rounded, animated)
  - dwm: Thin Windows border
- focusedColor: accent
  $name: Focused color
  $description: >-
    Border color of the window you are using. "accent" follows your Windows
    accent color. Use a hex color like #89b4fa for anything else.
- unfocusedColor: transparent
  $name: Unfocused color
  $description: >-
    Border color of background windows. "transparent" hides the border there.
    Use a hex color like #45475a for a dim border instead.
- overlay:
  - width: 2
    $name: Width
    $description: Border thickness in pixels at 100% scaling.
  - offset: -1
    $name: Gap
    $description: >-
      Space between the window edge and the border, in pixels. A negative value
      lets the border overlap the window edge.
  - radius: 8
    $name: Corner radius
    $description: >-
      Roundness of the window corners in pixels. 8 matches Windows 11; 0 gives
      square corners.
  - style: gradient
    $name: Fill
    $options:
    - solid: Solid color
    - gradient: Gradient on the active window
  - gradientTo: "#cba6f7"
    $name: Gradient end color
    $description: The active border fades from the focused color to this one.
  - gradientAngle: 45
    $name: Gradient angle
    $description: Direction of the gradient in degrees.
  - fadeMs: 150
    $name: Fade time
    $description: >-
      How long the color takes to change when focus moves, in milliseconds. 0
      switches instantly.
  $name: Overlay border
- fixAfterMs: 50
  $name: Color hold time
  $description: >-
    How long to wait before applying the color again after a focus change, in
    milliseconds. This wins against apps that paint their own border color a
    moment later. Set 0 to turn the re-apply off.
- specialWindows: false
  $name: Decorate frameless windows
  $description: >-
    Also color windows without a normal frame, like some launchers and tools.
- additionalEvents: false
  $name: Hook extra activation events
  $description: >-
    Helps with apps that handle activation in their own way. Only turn this on
    if the border color does not follow focus in one app.
*/
// ==/WindhawkModSettings==

#include <dwmapi.h>
#include <shellscalingapi.h>
#include <windhawk_api.h>

#include <atomic>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <vector>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

enum ColorKind {
    COLORK_ACCENT,
    COLORK_NONE,
    COLORK_DEFAULT,
    COLORK_SOLID,
};

struct BorderColor {
    ColorKind kind = COLORK_ACCENT;
    COLORREF rgb = 0;
};

static BorderColor g_focused;
static BorderColor g_unfocused;
static COLORREF g_accentColor = 0;
static UINT g_fixAfterMs = 50;
static bool g_specialWindows = false;
static bool g_additionalEvents = false;

struct OverlaySettings {
    int width = 2;
    int offset = 0;
    int radius = 8;
    bool gradient = false;
    COLORREF gradientTo = RGB(0xcb, 0xa6, 0xf7);
    int gradientAngle = 45;
    UINT fadeMs = 150;
};

static std::atomic<bool> g_overlayMode{true};
static OverlaySettings g_overlay;

static const COLORREF kColorDefault = DWMWA_COLOR_DEFAULT;  // 0xFFFFFFFF
static const COLORREF kColorNone = DWMWA_COLOR_NONE;        // 0xFFFFFFFE

static bool IsValidWindow(HWND hWnd) {
    DWORD dwStyle = (DWORD)GetWindowLongPtrW(hWnd, GWL_STYLE);
    // Better exclude context menus
    if ((dwStyle & WS_THICKFRAME) == WS_THICKFRAME ||
        (dwStyle & WS_CAPTION) == WS_CAPTION) {
        return true;
    }

    return g_specialWindows && (dwStyle & WS_OVERLAPPED) == WS_OVERLAPPED &&
           (dwStyle & WS_POPUP) != WS_POPUP;
}

static bool IsWindowFocused(HWND hWnd) {
    return GetForegroundWindow() == hWnd;
}

static void ApplyColorToWindow(HWND hWnd, const BorderColor& color) {
    if (!IsValidWindow(hWnd)) {
        return;
    }

    COLORREF value;
    if (g_overlayMode) {
        // The overlay draws the border; keep the thin native line out of the way.
        value = color.kind == COLORK_DEFAULT ? kColorDefault : kColorNone;
        DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &value, sizeof(value));
        return;
    }
    switch (color.kind) {
        case COLORK_NONE:
            value = kColorNone;
            break;
        case COLORK_DEFAULT:
            value = kColorDefault;
            break;
        case COLORK_ACCENT:
            value = g_accentColor;
            break;
        default:
            value = color.rgb;
            break;
    }

    DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &value, sizeof(value));
}

static const BorderColor& ColorForWindow(HWND hWnd) {
    return IsWindowFocused(hWnd) ? g_focused : g_unfocused;
}

static void LoadAccentColor() {
    DWORD color = 0;
    DWORD colorSize = sizeof(color);
    if (RegGetValueW(HKEY_CURRENT_USER,
                     L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Accent",
                     L"AccentColorMenu", RRF_RT_REG_DWORD, nullptr, &color,
                     &colorSize) == ERROR_SUCCESS) {
        g_accentColor = (color & 0xFF0000) | (color & 0xFF00) | (color & 0xFF);
    }
}

static void ParseColor(PCWSTR s, BorderColor* out) {
    out->kind = COLORK_ACCENT;
    if (!s || !*s) {
        return;
    }

    if (_wcsicmp(s, L"accent") == 0) {
        return;
    }
    if (_wcsicmp(s, L"transparent") == 0) {
        out->kind = COLORK_NONE;
        return;
    }
    if (_wcsicmp(s, L"default") == 0) {
        out->kind = COLORK_DEFAULT;
        return;
    }

    if (s[0] == L'#' && wcslen(s) >= 7) {
        auto hexVal = [](wchar_t c) -> int {
            if (c >= L'0' && c <= L'9') return c - L'0';
            if (c >= L'a' && c <= L'f') return c - L'a' + 10;
            if (c >= L'A' && c <= L'F') return c - L'A' + 10;
            return -1;
        };

        int d[6];
        bool ok = true;
        for (int i = 0; i < 6; i++) {
            d[i] = hexVal(s[1 + i]);
            ok = ok && d[i] >= 0;
        }
        if (ok) {
            out->kind = COLORK_SOLID;
            out->rgb = RGB((d[0] << 4) | d[1], (d[2] << 4) | d[3],
                           (d[4] << 4) | d[5]);
        }
    }
}

static void LoadSettings() {
    PCWSTR s;

    s = Wh_GetStringSetting(L"focusedColor");
    ParseColor(s, &g_focused);
    Wh_FreeStringSetting(s);

    s = Wh_GetStringSetting(L"unfocusedColor");
    ParseColor(s, &g_unfocused);
    Wh_FreeStringSetting(s);

    int fixAfterMs = Wh_GetIntSetting(L"fixAfterMs");
    g_fixAfterMs = fixAfterMs > 0 ? (UINT)fixAfterMs : 0;

    g_specialWindows = Wh_GetIntSetting(L"specialWindows") != 0;
    g_additionalEvents = Wh_GetIntSetting(L"additionalEvents") != 0;

    s = Wh_GetStringSetting(L"mode");
    g_overlayMode = !s || wcscmp(s, L"dwm") != 0;
    Wh_FreeStringSetting(s);

    g_overlay.width = Wh_GetIntSetting(L"overlay.width");
    if (g_overlay.width < 1) g_overlay.width = 1;
    if (g_overlay.width > 32) g_overlay.width = 32;
    g_overlay.offset = Wh_GetIntSetting(L"overlay.offset");
    if (g_overlay.offset < -8) g_overlay.offset = -8;
    if (g_overlay.offset > 32) g_overlay.offset = 32;
    g_overlay.radius = Wh_GetIntSetting(L"overlay.radius");
    if (g_overlay.radius < 0) g_overlay.radius = 0;
    if (g_overlay.radius > 64) g_overlay.radius = 64;

    s = Wh_GetStringSetting(L"overlay.style");
    g_overlay.gradient = s && wcscmp(s, L"gradient") == 0;
    Wh_FreeStringSetting(s);

    BorderColor to;
    s = Wh_GetStringSetting(L"overlay.gradientTo");
    ParseColor(s, &to);
    Wh_FreeStringSetting(s);
    g_overlay.gradientTo = to.kind == COLORK_SOLID ? to.rgb : RGB(0xcb, 0xa6, 0xf7);
    g_overlay.gradientAngle = Wh_GetIntSetting(L"overlay.gradientAngle");

    int fadeMs = Wh_GetIntSetting(L"overlay.fadeMs");
    g_overlay.fadeMs = fadeMs > 0 ? (UINT)(fadeMs > 2000 ? 2000 : fadeMs) : 0;

    LoadAccentColor();
}

// ---------------------------------------------------------------------------
// Worker thread: applies the colors again once, a short while after each
// focus change, so apps that set their own border color lose the race.
// ---------------------------------------------------------------------------

static constexpr UINT_PTR kReapplyTimerId = 0x5742;  // 'WB'
static constexpr UINT WM_APP_SCHEDULE_REAPPLY = WM_APP + 0x5742;

static std::atomic<HWND> g_workerWindow{nullptr};
static std::atomic<DWORD> g_workerThreadId{0};
static HANDLE g_workerThread = nullptr;
static CRITICAL_SECTION g_pendingCs;
static std::vector<HWND> g_pendingWindows;

static BOOL CALLBACK CollectWindowsCallback(HWND hWnd, LPARAM lParam) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId() && IsValidWindow(hWnd)) {
        auto* list = (std::vector<HWND>*)lParam;
        list->push_back(hWnd);
    }
    return TRUE;
}

static LRESULT CALLBACK WorkerWndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                      LPARAM lParam) {
    switch (uMsg) {
        case WM_TIMER:
            if (wParam == kReapplyTimerId) {
                KillTimer(hWnd, kReapplyTimerId);

                std::vector<HWND> pending;
                EnterCriticalSection(&g_pendingCs);
                pending.swap(g_pendingWindows);
                LeaveCriticalSection(&g_pendingCs);

                for (HWND hWndPending : pending) {
                    if (IsWindow(hWndPending)) {
                        ApplyColorToWindow(hWndPending, ColorForWindow(hWndPending));
                    }
                }
            }
            break;

        case WM_APP_SCHEDULE_REAPPLY:
            if (g_fixAfterMs) {
                SetTimer(hWnd, kReapplyTimerId, g_fixAfterMs, nullptr);
            }
            return 0;

        default:
            break;
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

static DWORD WINAPI WorkerThreadProc(LPVOID) {
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WorkerWndProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.lpszClassName = L"WindhawkLocalWindowBordersWorker";
    if (!RegisterClassExW(&wc)) {
        return 0;
    }

    HWND hWnd = CreateWindowExW(0, wc.lpszClassName, L"Window Borders worker",
                                0, 0, 0, 0, 0, HWND_MESSAGE, nullptr,
                                wc.hInstance, nullptr);
    if (!hWnd) {
        return 0;
    }

    g_workerWindow.store(hWnd, std::memory_order_release);
    g_workerThreadId.store(GetCurrentThreadId(), std::memory_order_release);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    DestroyWindow(hWnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}

static void ScheduleReapply() {
    if (!g_fixAfterMs) {
        return;
    }

    HWND hWndWorker = g_workerWindow.load(std::memory_order_acquire);
    if (!hWndWorker) {
        return;
    }

    EnterCriticalSection(&g_pendingCs);
    g_pendingWindows.clear();
    EnumWindows(CollectWindowsCallback, (LPARAM)&g_pendingWindows);
    LeaveCriticalSection(&g_pendingCs);

    PostMessageW(hWndWorker, WM_APP_SCHEDULE_REAPPLY, 0, 0);
}

// ---------------------------------------------------------------------------
// Hooks
// ---------------------------------------------------------------------------

static void SetBorderColorAndSchedule(HWND hWnd, BOOL activate) {
    if (!IsValidWindow(hWnd)) {
        return;
    }

    ApplyColorToWindow(hWnd, activate ? g_focused : g_unfocused);
    ScheduleReapply();
}

static void HandleActivateMessage(HWND hWnd, UINT uMsg, WPARAM wParam) {
    switch (uMsg) {
        case WM_ACTIVATEAPP:
            if (g_additionalEvents) {
                SetBorderColorAndSchedule(hWnd, wParam && GetForegroundWindow() == hWnd);
            }
            break;
        case WM_ACTIVATE:
        case WM_NCACTIVATE:
            SetBorderColorAndSchedule(hWnd, (BOOL)wParam);
            break;
        case WM_DWMCOLORIZATIONCOLORCHANGED:
            LoadAccentColor();
            SetBorderColorAndSchedule(hWnd, IsWindowFocused(hWnd));
            break;
        default:
            break;
    }
}

static void OverlayOnMessage(HWND hWnd, UINT uMsg, WPARAM wParam);

using DefWindowProcA_t = decltype(&DefWindowProcA);
static DefWindowProcA_t DefWindowProcA_orig;
static LRESULT WINAPI DefWindowProcA_hook(HWND hWnd, UINT uMsg, WPARAM wParam,
                                          LPARAM lParam) {
    LRESULT result = DefWindowProcA_orig(hWnd, uMsg, wParam, lParam);
    HandleActivateMessage(hWnd, uMsg, wParam);
    OverlayOnMessage(hWnd, uMsg, wParam);
    return result;
}

using DefWindowProcW_t = decltype(&DefWindowProcW);
static DefWindowProcW_t DefWindowProcW_orig;
static LRESULT WINAPI DefWindowProcW_hook(HWND hWnd, UINT uMsg, WPARAM wParam,
                                          LPARAM lParam) {
    LRESULT result = DefWindowProcW_orig(hWnd, uMsg, wParam, lParam);
    HandleActivateMessage(hWnd, uMsg, wParam);
    OverlayOnMessage(hWnd, uMsg, wParam);
    return result;
}

using DefDlgProcA_t = decltype(&DefDlgProcA);
static DefDlgProcA_t DefDlgProcA_orig;
static LRESULT WINAPI DefDlgProcA_hook(HWND hWnd, UINT uMsg, WPARAM wParam,
                                       LPARAM lParam) {
    LRESULT result = DefDlgProcA_orig(hWnd, uMsg, wParam, lParam);
    if (uMsg == WM_NCACTIVATE) {
        SetBorderColorAndSchedule(hWnd, (BOOL)wParam);
    }
    OverlayOnMessage(hWnd, uMsg, wParam);
    return result;
}

using DefDlgProcW_t = decltype(&DefDlgProcW);
static DefDlgProcW_t DefDlgProcW_orig;
static LRESULT WINAPI DefDlgProcW_hook(HWND hWnd, UINT uMsg, WPARAM wParam,
                                       LPARAM lParam) {
    LRESULT result = DefDlgProcW_orig(hWnd, uMsg, wParam, lParam);
    if (uMsg == WM_NCACTIVATE) {
        SetBorderColorAndSchedule(hWnd, (BOOL)wParam);
    }
    OverlayOnMessage(hWnd, uMsg, wParam);
    return result;
}

// ---------------------------------------------------------------------------
// Overlay mode: four thin click-through layered strips per decorated window
// (top, bottom, left, right), created on that window's own thread and owned
// by it, so they follow the window in z-order, minimize with it and are
// destroyed with it. Strips keep the surfaces small: a full-window layered
// bitmap would cost DWM tens of megabytes per window.
// ---------------------------------------------------------------------------

struct RingColor {
    float r = 0, g = 0, b = 0, a = 0;
};

// BEGIN RING RENDERER (also compiled by the offline render test)
static float Clamp01(float v) {
    return v < 0 ? 0 : (v > 1 ? 1 : v);
}

static RingColor LerpColor(const RingColor& x, const RingColor& y, float t) {
    return {x.r + (y.r - x.r) * t, x.g + (y.g - x.g) * t,
            x.b + (y.b - x.b) * t, x.a + (y.a - x.a) * t};
}

// Rows/columns from each canvas edge that can hold ring pixels.
static int RingBand(int pad, float radius, float offset) {
    float inside = (offset < 0 ? -offset : 0) + 1;
    return pad + (int)ceilf(radius > inside ? radius : inside) + 1;
}

// The canvas is the window frame grown by pad on every side (fw x fh pixels
// in total). Draws the part of an anti-aliased rounded ring that falls inside
// the strip at (sx, sy, sw, sh) of that canvas into a zeroed, top-down,
// premultiplied BGRA buffer of sw x sh pixels. The ring spans
// [offset, offset + width] outside the frame edge.
static void RenderRing(uint32_t* px, int sx, int sy, int sw, int sh, int fw, int fh,
                       int pad, float radius, float offset, float width,
                       RingColor c1, RingColor c2, float angleDeg) {
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
            RingColor c =
                solid ? c1
                      : LerpColor(c1, c2,
                                  Clamp01((fx * dx + fy * dy) / span * 0.5f + 0.5f));
            float a = c.a * cov;
            px[y * sw + x] = ((uint32_t)(a * 255 + 0.5f) << 24) |
                             ((uint32_t)(c.r * a * 255 + 0.5f) << 16) |
                             ((uint32_t)(c.g * a * 255 + 0.5f) << 8) |
                             (uint32_t)(c.b * a * 255 + 0.5f);
        }
    }
}

// Splits the canvas into top, bottom, left and right strips. Returns how many
// are non-empty (left/right vanish on very short windows).
static int RingStrips(int fw, int fh, int band, RECT out[4]) {
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

static constexpr UINT_PTR kFadeTimerId = 1;
static constexpr UINT_PTR kPollTimerId = 2;
static constexpr UINT kPollMs = 200;
static constexpr UINT WM_APP_OVERLAY_DESTROY = WM_APP + 0x5743;
static constexpr UINT WM_APP_OVERLAY_REFRESH = WM_APP + 0x5744;
static const wchar_t kOverlayClass[] = L"WindhawkLocalWindowBordersOverlay";

struct Overlay {
    HWND parts[4] = {};  // parts[0] owns the timers
    HWND target = nullptr;
    bool focused = false;
    bool shown = false;
    RingColor cur1, cur2, from1, from2, to1, to2;
    DWORD fadeStart = 0;
    bool fading = false;
    RECT frame = {};
    UINT dpi = 0;
    bool dirty = true;
};

static UINT g_syncMsg = 0;
static CRITICAL_SECTION g_overlayCs;
static std::unordered_map<HWND, Overlay*> g_overlays;  // target -> overlay
static bool g_overlayClassRegistered = false;
// Threads currently running overlay code; unload waits for this to drain.
static std::atomic<int> g_overlayBusy{0};

struct OverlayBusyScope {
    OverlayBusyScope() { g_overlayBusy++; }
    ~OverlayBusyScope() { g_overlayBusy--; }
};

// Every overlay call works in physical pixels, whatever DPI mode the app's
// thread runs in: DWM frame bounds are physical, and so are the strips.
struct PhysicalDpiScope {
    DPI_AWARENESS_CONTEXT old;
    PhysicalDpiScope()
        : old(SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {}
    ~PhysicalDpiScope() {
        if (old) SetThreadDpiAwarenessContext(old);
    }
};

static Overlay* FindOverlay(HWND target) {
    EnterCriticalSection(&g_overlayCs);
    auto it = g_overlays.find(target);
    Overlay* ov = it == g_overlays.end() ? nullptr : it->second;
    LeaveCriticalSection(&g_overlayCs);
    return ov;
}

static RingColor ToRing(COLORREF c, float a) {
    return {GetRValue(c) / 255.0f, GetGValue(c) / 255.0f, GetBValue(c) / 255.0f, a};
}

static void StateColors(bool focused, RingColor* c1, RingColor* c2) {
    const BorderColor& bc = focused ? g_focused : g_unfocused;
    if (bc.kind == COLORK_ACCENT || bc.kind == COLORK_SOLID) {
        *c1 = ToRing(bc.kind == COLORK_ACCENT ? g_accentColor : bc.rgb, 1);
        *c2 = focused && g_overlay.gradient ? ToRing(g_overlay.gradientTo, 1) : *c1;
        return;
    }
    // Hidden in this state: keep the other state's colors and fade them out.
    const BorderColor& other = focused ? g_unfocused : g_focused;
    COLORREF rgb = other.kind == COLORK_SOLID ? other.rgb : g_accentColor;
    *c1 = ToRing(rgb, 0);
    *c2 = !focused && g_overlay.gradient ? ToRing(g_overlay.gradientTo, 0) : *c1;
}

static bool GetFrame(HWND target, RECT* rc) {
    if (SUCCEEDED(DwmGetWindowAttribute(target, DWMWA_EXTENDED_FRAME_BOUNDS, rc,
                                        sizeof(*rc)))) {
        return rc->right > rc->left && rc->bottom > rc->top;
    }
    return GetWindowRect(target, rc) && rc->right > rc->left;
}

// Where Windows would not draw a frame, the overlay stays hidden too.
static bool FrameVisible(HWND target, const RECT& frame, HMONITOR monitor) {
    if (!IsWindowVisible(target) || IsIconic(target) || IsZoomed(target)) {
        return false;
    }
    BOOL cloaked = FALSE;
    if (SUCCEEDED(DwmGetWindowAttribute(target, DWMWA_CLOAKED, &cloaked,
                                        sizeof(cloaked))) &&
        cloaked) {
        return false;
    }
    MONITORINFO mi = {sizeof(mi)};
    if (GetMonitorInfoW(monitor, &mi) && frame.left <= mi.rcMonitor.left &&
        frame.top <= mi.rcMonitor.top && frame.right >= mi.rcMonitor.right &&
        frame.bottom >= mi.rcMonitor.bottom) {
        return false;  // fullscreen app or game
    }
    return true;
}

static bool IsOverlayTarget(HWND hWnd) {
    DWORD style = (DWORD)GetWindowLongPtrW(hWnd, GWL_STYLE);
    return !(style & WS_CHILD) && IsValidWindow(hWnd);
}

static int OverlayPad(UINT dpi, int* width, int* offset) {
    float scale = dpi / 96.0f;
    *width = (int)ceilf(g_overlay.width * scale);
    *offset = (int)roundf(g_overlay.offset * scale);
    return *width + (*offset > 0 ? *offset : 0) + 1;
}

static void PaintOverlay(Overlay* ov) {
    int width, offset;
    int pad = OverlayPad(ov->dpi, &width, &offset);
    float radius = g_overlay.radius * ov->dpi / 96.0f;
    int fw = ov->frame.right - ov->frame.left + pad * 2;
    int fh = ov->frame.bottom - ov->frame.top + pad * 2;
    RECT strips[4];
    int count = RingStrips(fw, fh, RingBand(pad, radius, (float)offset), strips);

    HDC dc = CreateCompatibleDC(nullptr);
    for (int i = 0; i < 4; i++) {
        HWND part = ov->parts[i];
        if (!part) continue;
        if (i >= count) {
            ShowWindow(part, SW_HIDE);
            continue;
        }
        const RECT& s = strips[i];
        int sw = s.right - s.left, sh = s.bottom - s.top;
        BITMAPINFO bi = {};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = sw;
        bi.bmiHeader.biHeight = -sh;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        void* bits = nullptr;
        HBITMAP bmp = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!bmp) continue;
        RenderRing((uint32_t*)bits, s.left, s.top, sw, sh, fw, fh, pad, radius,
                   (float)offset, (float)width, ov->cur1, ov->cur2,
                   (float)g_overlay.gradientAngle);
        HGDIOBJ old = SelectObject(dc, bmp);
        POINT dst = {ov->frame.left - pad + s.left, ov->frame.top - pad + s.top};
        SIZE size = {sw, sh};
        POINT src = {0, 0};
        BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        UpdateLayeredWindow(part, nullptr, &dst, &size, dc, &src, 0, &blend, ULW_ALPHA);
        SelectObject(dc, old);
        DeleteObject(bmp);
    }
    DeleteDC(dc);
    ov->dirty = false;
}

// Size unchanged: slide the strips without repainting.
static void MoveOverlay(Overlay* ov) {
    int width, offset;
    int pad = OverlayPad(ov->dpi, &width, &offset);
    float radius = g_overlay.radius * ov->dpi / 96.0f;
    int fw = ov->frame.right - ov->frame.left + pad * 2;
    int fh = ov->frame.bottom - ov->frame.top + pad * 2;
    RECT strips[4];
    int count = RingStrips(fw, fh, RingBand(pad, radius, (float)offset), strips);
    for (int i = 0; i < count; i++) {
        if (!ov->parts[i]) continue;
        POINT dst = {ov->frame.left - pad + strips[i].left,
                     ov->frame.top - pad + strips[i].top};
        UpdateLayeredWindow(ov->parts[i], nullptr, &dst, nullptr, nullptr, nullptr,
                            0, nullptr, 0);
    }
}

static void ShowOverlay(Overlay* ov, bool show) {
    if (show == ov->shown) {
        return;
    }
    ov->shown = show;
    for (HWND part : ov->parts) {
        if (!part) continue;
        if (!show) {
            ShowWindow(part, SW_HIDE);
            continue;
        }
        // Directly above the target, never above windows that cover it. When
        // the window above is a topmost one (the taskbar, say) and the target
        // is not, the top of the normal band is the same spot.
        HWND above = GetWindow(ov->target, GW_HWNDPREV);
        bool targetTopmost = GetWindowLongPtrW(ov->target, GWL_EXSTYLE) & WS_EX_TOPMOST;
        if (above && !targetTopmost &&
            (GetWindowLongPtrW(above, GWL_EXSTYLE) & WS_EX_TOPMOST)) {
            above = HWND_TOP;
        }
        UINT flags = SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER |
                     SWP_SHOWWINDOW;
        if (above == part) {
            flags |= SWP_NOZORDER;
        }
        SetWindowPos(part, above ? above : HWND_TOP, 0, 0, 0, 0, flags);
    }
}

static void StartFade(Overlay* ov) {
    StateColors(ov->focused, &ov->to1, &ov->to2);
    ov->dirty = true;
    if (!g_overlay.fadeMs || !ov->shown) {
        ov->cur1 = ov->to1;
        ov->cur2 = ov->to2;
        ov->fading = false;
        KillTimer(ov->parts[0], kFadeTimerId);
        return;
    }
    ov->from1 = ov->cur1;
    ov->from2 = ov->cur2;
    ov->fadeStart = GetTickCount();
    ov->fading = true;
    SetTimer(ov->parts[0], kFadeTimerId, 16, nullptr);
}

static void SyncOverlay(HWND target, int focusHint);

static void FadeStep(Overlay* ov) {
    UINT fadeMs = g_overlay.fadeMs;
    float t = fadeMs ? Clamp01((GetTickCount() - ov->fadeStart) / (float)fadeMs) : 1;
    float e = 1 - (1 - t) * (1 - t);  // ease out
    ov->cur1 = LerpColor(ov->from1, ov->to1, e);
    ov->cur2 = LerpColor(ov->from2, ov->to2, e);
    if (t >= 1) {
        ov->fading = false;
        KillTimer(ov->parts[0], kFadeTimerId);
    }
    ov->dirty = true;
    SyncOverlay(ov->target, -1);
}

static void DestroyOverlay(Overlay* ov) {
    // Each strip's WM_NCDESTROY clears its slot; the last one frees ov.
    HWND parts[4];
    memcpy(parts, ov->parts, sizeof(parts));
    for (HWND part : parts) {
        if (part) DestroyWindow(part);
    }
}

static Overlay* CreateOverlay(HWND target, bool focused) {
    Overlay* ov = new Overlay();
    ov->target = target;
    ov->focused = focused;
    StateColors(focused, &ov->cur1, &ov->cur2);
    ov->to1 = ov->cur1;
    ov->to2 = ov->cur2;

    DWORD exStyle = WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW |
                    WS_EX_NOACTIVATE;
    if (GetWindowLongPtrW(target, GWL_EXSTYLE) & WS_EX_TOPMOST) {
        exStyle |= WS_EX_TOPMOST;
    }
    for (int i = 0; i < 4; i++) {
        HWND part = CreateWindowExW(exStyle, kOverlayClass, L"", WS_POPUP | WS_DISABLED,
                                    0, 0, 0, 0, target, nullptr,
                                    (HINSTANCE)&__ImageBase, ov);
        if (!part) {
            if (ov->parts[0]) {
                DestroyOverlay(ov);  // frees ov
            } else {
                delete ov;
            }
            return nullptr;
        }
        ov->parts[i] = part;
    }
    EnterCriticalSection(&g_overlayCs);
    g_overlays[target] = ov;
    LeaveCriticalSection(&g_overlayCs);
    SetTimer(ov->parts[0], kPollTimerId, kPollMs, nullptr);
    return ov;
}

// Runs on the target's thread. focusHint: 1 focused, 0 not, -1 ask Windows.
static void SyncOverlay(HWND target, int focusHint) {
    if (!g_overlayMode || !g_overlayClassRegistered) {
        return;
    }
    Overlay* ov = FindOverlay(target);
    if (!ov && !IsOverlayTarget(target)) {
        return;
    }
    PhysicalDpiScope dpiScope;
    bool focused = focusHint >= 0 ? focusHint != 0 : GetForegroundWindow() == target;

    RECT frame;
    HMONITOR monitor = nullptr;
    bool visible = GetFrame(target, &frame);
    if (visible) {
        monitor = MonitorFromRect(&frame, MONITOR_DEFAULTTONEAREST);
        visible = FrameVisible(target, frame, monitor);
    }
    if (!ov) {
        if (!visible) {
            return;
        }
        RingColor c1, c2;
        StateColors(focused, &c1, &c2);
        if (c1.a == 0) {
            return;  // nothing to draw yet; created on the next focus change
        }
        ov = CreateOverlay(target, focused);
        if (!ov) {
            return;
        }
    } else if (focused != ov->focused) {
        ov->focused = focused;
        StartFade(ov);
    }

    if (!visible) {
        ShowOverlay(ov, false);
        return;
    }

    UINT dpiX = 96, dpiY = 96;
    if (FAILED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)) || !dpiX) {
        dpiX = 96;
    }
    if (!EqualRect(&frame, &ov->frame) || dpiX != ov->dpi) {
        bool resized = frame.right - frame.left != ov->frame.right - ov->frame.left ||
                       frame.bottom - frame.top != ov->frame.bottom - ov->frame.top;
        if (resized || dpiX != ov->dpi) {
            ov->dirty = true;
        }
        ov->frame = frame;
        ov->dpi = dpiX;
        if (!ov->dirty) {
            MoveOverlay(ov);
        }
    }
    if (ov->dirty) {
        PaintOverlay(ov);
    }

    bool drawn = ov->cur1.a > 0 || ov->cur2.a > 0 || ov->fading;
    if (!drawn && !ov->fading) {
        // Faded out for good: free the surfaces instead of keeping them hidden.
        DestroyOverlay(ov);
        return;
    }
    ShowOverlay(ov, drawn);
}

static LRESULT CALLBACK OverlayWndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                       LPARAM lParam) {
    OverlayBusyScope busy;
    if (uMsg == WM_NCCREATE) {
        SetWindowLongPtrW(hWnd, GWLP_USERDATA,
                          (LONG_PTR)((CREATESTRUCTW*)lParam)->lpCreateParams);
    }
    Overlay* ov = (Overlay*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    switch (uMsg) {
        case WM_NCHITTEST:
            return HTTRANSPARENT;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_TIMER:
            if (ov && wParam == kFadeTimerId) {
                FadeStep(ov);
            } else if (ov && wParam == kPollTimerId) {
                SyncOverlay(ov->target, -1);
            }
            return 0;
        case WM_APP_OVERLAY_REFRESH:
            if (ov) {
                StartFade(ov);
                SyncOverlay(ov->target, -1);
            }
            return 0;
        case WM_APP_OVERLAY_DESTROY:
            if (ov) DestroyOverlay(ov);
            return 0;
        case WM_NCDESTROY:
            if (ov) {
                SetWindowLongPtrW(hWnd, GWLP_USERDATA, 0);
                bool last = true;
                for (HWND& part : ov->parts) {
                    if (part == hWnd) part = nullptr;
                    if (part) last = false;
                }
                if (last) {
                    EnterCriticalSection(&g_overlayCs);
                    auto it = g_overlays.find(ov->target);
                    if (it != g_overlays.end() && it->second == ov) {
                        g_overlays.erase(it);
                    }
                    LeaveCriticalSection(&g_overlayCs);
                    delete ov;
                }
            }
            break;
    }
    return DefWindowProcW_orig(hWnd, uMsg, wParam, lParam);
}

static void OverlayOnMessage(HWND hWnd, UINT uMsg, WPARAM wParam) {
    if (!g_overlayMode) {
        return;
    }
    switch (uMsg) {
        case WM_NCACTIVATE:
        case WM_WINDOWPOSCHANGED:
        case WM_SIZE:
        case WM_ACTIVATE:
        case WM_DPICHANGED:
        case WM_DWMCOLORIZATIONCOLORCHANGED:
            break;
        default:
            if (!g_syncMsg || uMsg != g_syncMsg) {
                return;
            }
            break;
    }
    // Child controls send these by the thousand during layout; skip them first.
    if (GetWindowLongPtrW(hWnd, GWL_STYLE) & WS_CHILD) {
        return;
    }
    OverlayBusyScope busy;
    if (uMsg == WM_NCACTIVATE) {
        SyncOverlay(hWnd, wParam ? 1 : 0);
        return;
    }
    if (uMsg == WM_DWMCOLORIZATIONCOLORCHANGED) {
        if (Overlay* ov = FindOverlay(hWnd)) {
            StartFade(ov);
        }
    }
    SyncOverlay(hWnd, -1);
}

// Strip windows of every overlay; primaryOnly returns one per overlay.
static std::vector<HWND> OverlayWindows(bool primaryOnly) {
    std::vector<HWND> list;
    EnterCriticalSection(&g_overlayCs);
    for (auto& entry : g_overlays) {
        for (HWND part : entry.second->parts) {
            if (part) {
                list.push_back(part);
                if (primaryOnly) break;
            }
        }
    }
    LeaveCriticalSection(&g_overlayCs);
    return list;
}

// Runs on the engine thread, not the overlays' threads, so every call is
// bounded: a hung app costs at most 200 ms per overlay.
static void BroadcastToOverlays(UINT msg) {
    for (HWND hwnd : OverlayWindows(true)) {
        SendMessageTimeoutW(hwnd, msg, 0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 200,
                            nullptr);
    }
}

static BOOL CALLBACK PostSyncCallback(HWND hWnd, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId() && IsOverlayTarget(hWnd)) {
        PostMessageW(hWnd, g_syncMsg, 0, 0);
    }
    return TRUE;
}

static void DestroyAllOverlays() {
    BroadcastToOverlays(WM_APP_OVERLAY_DESTROY);
    // Anything left belongs to a thread that did not answer. Point it at the
    // system window procedure so it never calls into the unloaded mod, and let
    // that thread close it whenever it wakes up.
    auto systemProc = (LONG_PTR)GetProcAddress(GetModuleHandleW(L"user32.dll"),
                                               "DefWindowProcW");
    for (HWND hwnd : OverlayWindows(false)) {
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
        SetWindowLongPtrW(hwnd, GWLP_WNDPROC, systemProc);
        PostMessageW(hwnd, WM_CLOSE, 0, 0);
    }
    EnterCriticalSection(&g_overlayCs);
    g_overlays.clear();  // the unanswered entries leak on purpose
    LeaveCriticalSection(&g_overlayCs);
}

static BOOL CALLBACK ApplyAllCallback(HWND hWnd, LPARAM lParam) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId()) {
        SetBorderColorAndSchedule(hWnd, IsWindowFocused(hWnd));
    }
    return TRUE;
}

static BOOL CALLBACK ResetAllCallback(HWND hWnd, LPARAM lParam) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId() && IsValidWindow(hWnd)) {
        COLORREF value = kColorDefault;
        DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &value, sizeof(value));
    }
    return TRUE;
}

// ---------------------------------------------------------------------------
// Mod entry points
// ---------------------------------------------------------------------------

BOOL Wh_ModInit() {
    Wh_Log(L"Init");

    InitializeCriticalSectionAndSpinCount(&g_pendingCs, 0x400);
    InitializeCriticalSectionAndSpinCount(&g_overlayCs, 0x400);
    g_syncMsg = RegisterWindowMessageW(L"WindhawkLocalWindowBordersSync");

    LoadSettings();

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = OverlayWndProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.lpszClassName = kOverlayClass;
    g_overlayClassRegistered = RegisterClassExW(&wc) != 0;
    if (!g_overlayClassRegistered) {
        Wh_Log(L"Overlay class failed (%u); overlay mode off", GetLastError());
    }

    g_workerThread = CreateThread(nullptr, 0, WorkerThreadProc, nullptr, 0,
                                  nullptr);
    if (!g_workerThread) {
        Wh_Log(L"Worker thread failed; re-apply disabled");
    }

    Wh_SetFunctionHook((void*)DefWindowProcW, (void*)DefWindowProcW_hook,
                       (void**)&DefWindowProcW_orig);

    Wh_SetFunctionHook((void*)DefWindowProcA, (void*)DefWindowProcA_hook,
                       (void**)&DefWindowProcA_orig);

    Wh_SetFunctionHook((void*)DefDlgProcW, (void*)DefDlgProcW_hook,
                       (void**)&DefDlgProcW_orig);

    Wh_SetFunctionHook((void*)DefDlgProcA, (void*)DefDlgProcA_hook,
                       (void**)&DefDlgProcA_orig);

    return TRUE;
}

void Wh_ModAfterInit() {
    Wh_Log(L"AfterInit");
    EnumWindows(ApplyAllCallback, 0);
    EnumWindows(PostSyncCallback, 0);
}

void Wh_ModBeforeUninit() {
    Wh_Log(L"BeforeUninit");

    g_overlayMode = false;
    DestroyAllOverlays();
    // Let threads already inside overlay code leave it before the DLL goes.
    for (int i = 0; i < 100 && g_overlayBusy > 0; i++) {
        Sleep(10);
    }
    EnumWindows(ResetAllCallback, 0);

    DWORD tid = g_workerThreadId.load(std::memory_order_acquire);
    if (tid) {
        PostThreadMessageW(tid, WM_QUIT, 0, 0);
    }
    if (g_workerThread) {
        WaitForSingleObject(g_workerThread, 1000);
        CloseHandle(g_workerThread);
        g_workerThread = nullptr;
    }

    // g_pendingCs is not deleted: a hooked DefWindowProc on another thread can
    // still be inside ScheduleReapply during unload.
}

void Wh_ModSettingsChanged() {
    Wh_Log(L"SettingsChanged");

    EnumWindows(ResetAllCallback, 0);
    LoadSettings();
    if (g_overlayMode) {
        BroadcastToOverlays(WM_APP_OVERLAY_REFRESH);
    } else {
        DestroyAllOverlays();
    }
    EnumWindows(ApplyAllCallback, 0);
    EnumWindows(PostSyncCallback, 0);
}

void Wh_ModUninit() {
    Wh_Log(L"Uninit");
    if (g_overlayClassRegistered) {
        UnregisterClassW(kOverlayClass, (HINSTANCE)&__ImageBase);
    }
}
