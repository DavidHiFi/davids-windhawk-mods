// ==WindhawkMod==
// @id              seamless-autoscroll
// @name            Seamless Autoscroll
// @description     Hold the middle mouse button and move to scroll, like in a browser, with a frosted glass indicator
// @version         1.0.0
// @author          DavidHiFi, crazyboyybs
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         explorer.exe
// @compilerOptions -DWIN32_LEAN_AND_MEAN -luser32 -ladvapi32 -lole32 -loleaut32 -ldwmapi -lruntimeobject
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Autoscroll

Made by **DavidHiFi**. Based on
[AutoScroll Win32](https://windhawk.net/mods/autoscroll-win32) by
[crazyboyybs](https://github.com/crazyboyybs).

Hold the middle mouse button in File Explorer (or any app you add) and move the
mouse to scroll, the way browsers do. A small frosted glass circle marks where
you started and lights up the way you are scrolling.

![Seamless Autoscroll preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-autoscroll.png)

## Features

- **Browser-style scrolling.** The farther you move from the starting point,
  the faster it scrolls, up, down and sideways.
- **Frosted glass indicator.** Real blur of what is behind it, drawn by the
  graphics card, with a Catppuccin Mocha tint and a blue to mauve ring.
- **Your colors.** Background, ring, arrows and center dot each have their own
  color, plus ring style, thickness, gradient angle, blur and opacity.
- **Smooth motion.** The circle fades and grows in, and the arrows fade as you
  change direction. Turn it off or set the speed.
- **Hold or toggle.** Hold the button to scroll, or click once to start and
  again to stop.
- **Works with Smooth Scroll.** It sends normal mouse wheel messages, so Smooth
  Scroll Win32 animates them like real wheel turns.

## How to use

1. Hold the middle mouse button anywhere you can scroll.
2. Move the mouse away from the circle. Farther means faster.
3. Let go to stop. Escape or any other mouse button also stops it.

A quick middle click with no scrolling still reaches the app, so opening a
folder in a new tab keeps working.

## Notes

- Turn off **AutoScroll Win32** if you have it. Both together scroll twice.
- To use it in other apps, add them under **Advanced > Include processes**.
- The blur follows the Windows transparency effects setting. With it off, the
  circle shows a plain tinted background.

## Credits

Based on [AutoScroll Win32](https://windhawk.net/mods/autoscroll-win32) by
[crazyboyybs](https://github.com/crazyboyybs). The scrolling engine is theirs;
the indicator was redrawn for this version.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- toggleMode: false
  $name: Click to start and stop
  $description: "When on, one middle click starts scrolling and the next one stops it. When off, hold the button to scroll."
- horizontal: true
  $name: Scroll sideways too
  $description: "When on, moving left or right scrolls sideways."
- deadzone: 8
  $name: Still zone (px)
  $description: "How far the mouse can move before scrolling starts. 0 to 64 (Suggested: 8)."
- speed: 150
  $name: Full speed distance (px)
  $description: "How far from the start the mouse must be for full speed. 20 to 500 (Suggested: 150)."
- speedMult: 30
  $name: Top speed
  $description: "Fastest scroll, in tenths of a wheel notch per frame. 1 to 100 (Suggested: 30)."
- blockMiddleRelease: false
  $name: Hide the button release from apps
  $description: "When on, apps never see the middle button let go. Useful for tools like Direct Folders that act on it."
- showIndicator: true
  $name: Show the indicator
  $description: "When off, scrolling works with no circle on screen."
- size: 44
  $name: Indicator size (px)
  $description: "Width of the circle at 100% display scale. 24 to 96 (Suggested: 44)."
- glassBlur: true
  $name: Glass blur
  $description: "When on, what is behind the circle is blurred. When off, the background is a plain color."
- blurAmount: 18
  $name: Blur strength
  $description: "0 to 40 (Suggested: 18). Higher values melt the content behind into color."
- backgroundColor: "#1E1E2E"
  $name: Background color
  $description: "Tint over the blur, as #RRGGBB (Suggested: #1E1E2E, Mocha Base)."
- backgroundOpacity: 70
  $name: Background opacity (%)
  $description: "0 to 100 (Suggested: 70). Lower shows more of the blur."
- borderStyle: gradient
  $name: Ring style
  $options:
  - gradient: Gradient
  - solid: Solid color
  - none: No ring
- borderColor: "#89B4FA"
  $name: Ring color
  $description: "Solid ring color, and where the gradient starts (Suggested: #89B4FA, Mocha Blue)."
- borderColor2: "#CBA6F7"
  $name: Ring gradient end color
  $description: "Where the gradient ends (Suggested: #CBA6F7, Mocha Mauve)."
- gradientAngle: 45
  $name: Gradient angle
  $description: "Direction of the gradient in degrees, 0 is left to right. 0 to 360 (Suggested: 45)."
- borderWidth: 2
  $name: Ring thickness (px)
  $description: "1 to 6 (Suggested: 2)."
- arrowColor: "#CDD6F4"
  $name: Arrow color
  $description: "Arrows you are not scrolling toward (Suggested: #CDD6F4, Mocha Text)."
- arrowOpacity: 40
  $name: Idle arrow opacity (%)
  $description: "0 to 100 (Suggested: 40)."
- arrowActiveColor: "#89B4FA"
  $name: Active arrow color
  $description: "Arrows you are scrolling toward (Suggested: #89B4FA, Mocha Blue)."
- dotColor: "#CBA6F7"
  $name: Center dot color
  $description: "Suggested: #CBA6F7, Mocha Mauve."
- animations: true
  $name: Animations
  $description: "When on, the circle fades and grows in and out, and arrows fade between states."
- animationMs: 160
  $name: Animation length (ms)
  $description: "50 to 400 (Suggested: 160)."
- popScale: 80
  $name: Starting size (%)
  $description: "How big the circle is when it starts growing in. 50 to 100 (Suggested: 80)."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <dispatcherqueue.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.Numerics.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Composition.Desktop.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <thread>

// ===========================================================================
// Settings
// ===========================================================================
static std::atomic<int>  g_deadzonePx{8};
static std::atomic<int>  g_speedPx{150};
static std::atomic<bool> g_horzEnabled{true};
static std::atomic<int>  g_speedMult{30};
static std::atomic<bool> g_showIndicator{true};
static std::atomic<bool> g_toggleMode{false};
static std::atomic<bool> g_blockMiddleRelease{false};

// Indicator look. Written only while the indicator thread is stopped (see
// Wh_ModSettingsChanged), read only by that thread.
struct Rgba { BYTE a, r, g, b; };
enum class BorderStyle { Gradient, Solid, None };
struct Look {
    int         sizeDip      = 44;
    bool        blur         = true;
    float       blurAmount   = 18.0f;
    Rgba        background   = {255, 0x1E, 0x1E, 0x2E};
    float       bgOpacity    = 0.70f;
    BorderStyle borderStyle  = BorderStyle::Gradient;
    Rgba        border1      = {255, 0x89, 0xB4, 0xFA};
    Rgba        border2      = {255, 0xCB, 0xA6, 0xF7};
    float       gradAngle    = 45.0f;
    float       borderWidth  = 2.0f;
    Rgba        arrow        = {255, 0xCD, 0xD6, 0xF4};
    float       arrowOpacity = 0.40f;
    Rgba        arrowActive  = {255, 0x89, 0xB4, 0xFA};
    Rgba        dot          = {255, 0xCB, 0xA6, 0xF7};
    bool        animate      = true;
    int         animMs       = 160;
    float       popScale     = 0.80f;
};
static Look g_look;

// Used in toggle mode: suppress the WM_MBUTTONUP paired with the
// stop-click WM_MBUTTONDOWN (which is swallowed to prevent apps seeing it).
static std::atomic<bool> g_suppressNextMBUp{false};

// ===========================================================================
// Autoscroll state
// ===========================================================================
static std::atomic<HWND> g_targetHwnd{nullptr};
static std::atomic<int>  g_originX{0};
static std::atomic<int>  g_originY{0};

// Custom messages driving the indicator window from the scroll thread.
static const UINT WM_IND_SHOW   = WM_USER + 1;
static const UINT WM_IND_HIDE   = WM_USER + 2;
static const UINT WM_IND_UPDATE = WM_USER + 3;

// Raw pointers (not value std::threads): Windhawk does not call Wh_ModUninit
// when the host exits, and a joinable global std::thread would call
// std::terminate() at CRT shutdown and take explorer.exe down with it.
static std::atomic<bool> g_threadRunning{false};
static std::thread*      g_scrollThread = nullptr;

static std::atomic<HWND> g_indicatorHwnd{nullptr};
static std::thread*      g_indicatorThread = nullptr;
static std::atomic<bool> g_indicatorExited{true};

// Auto-reset event that wakes the scroll thread when a gesture starts.
static HANDLE g_scrollEvent = nullptr;

// Set when a scroll event was actually posted since the gesture started.
// Decides whether WM_MBUTTONUP is swallowed or passed on (quick click).
static std::atomic<bool> g_scrolledSinceStart{false};

// Keeps at most one WM_IND_UPDATE queued so SHOW/HIDE are never delayed.
static std::atomic<bool> g_indUpdatePending{false};

// Refresh interval of the target window's monitor, cached per gesture.
static std::atomic<DWORD> g_frameMs{16};

// ===========================================================================
// Scroll thread
// ===========================================================================
static void ScrollThreadProc() {
    while (g_threadRunning.load(std::memory_order_relaxed)) {
        WaitForSingleObject(g_scrollEvent, INFINITE);
        if (!g_threadRunning.load(std::memory_order_relaxed)) break;

        while (g_threadRunning.load(std::memory_order_relaxed)) {
            HWND hwnd = g_targetHwnd.load(std::memory_order_acquire);
            if (!hwnd) break;

            if (!IsWindow(hwnd)) {
                HWND expected = hwnd;
                g_targetHwnd.compare_exchange_strong(
                    expected, nullptr,
                    std::memory_order_release,
                    std::memory_order_relaxed);
                break;
            }

            DWORD frameMs = g_frameMs.load(std::memory_order_relaxed);

            POINT cursor{};
            GetCursorPos(&cursor);

            int dy = cursor.y - g_originY.load(std::memory_order_relaxed);
            int dx = cursor.x - g_originX.load(std::memory_order_relaxed);

            int   deadzone   = g_deadzonePx.load(std::memory_order_relaxed);
            int   speedRange = std::max(1,
                g_speedPx.load(std::memory_order_relaxed) - deadzone);
            float maxNotches = g_speedMult.load(std::memory_order_relaxed) / 10.0f;

            {
                int absDy = std::abs(dy);
                if (absDy > deadzone) {
                    float t     = std::min(1.0f, (float)(absDy - deadzone) / speedRange);
                    int   delta = std::min(
                        (int)(t * t * t * maxNotches * WHEEL_DELTA),
                        (int)WHEEL_DELTA);  // 1 notch max: prevents queue buildup
                    if (delta > 0) {
                        if (dy > 0) delta = -delta;
                        g_scrolledSinceStart.store(true, std::memory_order_relaxed);
                        PostMessageW(hwnd, WM_MOUSEWHEEL,
                            MAKEWPARAM(0, (SHORT)delta),
                            MAKELPARAM(cursor.x, cursor.y));
                    }
                }
            }

            if (g_horzEnabled.load(std::memory_order_relaxed)) {
                int absDx = std::abs(dx);
                if (absDx > deadzone) {
                    float t     = std::min(1.0f, (float)(absDx - deadzone) / speedRange);
                    int   delta = std::min(
                        (int)(t * t * t * maxNotches * WHEEL_DELTA),
                        (int)WHEEL_DELTA);
                    if (delta > 0) {
                        // WM_MOUSEHWHEEL: positive means tilted right, so only
                        // a leftward drag negates it.
                        if (dx < 0) delta = -delta;
                        g_scrolledSinceStart.store(true, std::memory_order_relaxed);
                        PostMessageW(hwnd, WM_MOUSEHWHEEL,
                            MAKEWPARAM(0, (SHORT)delta),
                            MAKELPARAM(cursor.x, cursor.y));
                    }
                }
            }

            HWND ind = g_indicatorHwnd.load(std::memory_order_relaxed);
            if (ind && !g_indUpdatePending.exchange(true, std::memory_order_relaxed)) {
                PostMessageW(ind, WM_IND_UPDATE, 0, 0);
            }

            Sleep(frameMs);
        }
    }
}

// ===========================================================================
// Autoscroll state transitions
// ===========================================================================
static DWORD CalcFrameMs(HWND hwnd) {
    HMONITOR hmon = hwnd
        ? MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY)
        : MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFOEXW mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(hmon, &mi)) return 16;
    DEVMODEW dm{};
    dm.dmSize = sizeof(dm);
    if (!EnumDisplaySettingsW(mi.szDevice, ENUM_CURRENT_SETTINGS, &dm)
        || dm.dmDisplayFrequency == 0) return 16;
    return std::max((DWORD)1, 1000u / dm.dmDisplayFrequency);
}

static void StartAutoscroll(HWND hwnd, POINT screenOrigin) {
    g_frameMs.store(CalcFrameMs(hwnd), std::memory_order_relaxed);
    g_originX.store(screenOrigin.x, std::memory_order_relaxed);
    g_originY.store(screenOrigin.y, std::memory_order_relaxed);
    g_scrolledSinceStart.store(false, std::memory_order_relaxed);
    g_targetHwnd.store(hwnd, std::memory_order_release);
    if (g_scrollEvent) SetEvent(g_scrollEvent);
    HWND ind = g_indicatorHwnd.load(std::memory_order_acquire);
    if (ind) PostMessageW(ind, WM_IND_SHOW, 0, 0);
}

static void StopAutoscroll() {
    g_targetHwnd.store(nullptr, std::memory_order_release);
    HWND ind = g_indicatorHwnd.load(std::memory_order_acquire);
    if (ind) PostMessageW(ind, WM_IND_HIDE, 0, 0);
}

// ===========================================================================
// Message handler shared by the PeekMessage and DispatchMessage hooks.
// Returns true when the message is consumed and must be suppressed.
// ===========================================================================
static bool HandleMsg(const MSG* pMsg) {
    if (!pMsg || pMsg->message == WM_NULL) return false;

    const bool isActive = (g_targetHwnd.load(std::memory_order_acquire) != nullptr);

    switch (pMsg->message) {

    // Hold mode passes DOWN through (keeps open-in-new-tab). Toggle mode
    // swallows every DOWN: passing it lets Explorer SetCapture and eat the
    // UP in an inner loop before our hook sees it.
    case WM_MBUTTONDOWN: {
        POINT pt = { GET_X_LPARAM(pMsg->lParam),
                     GET_Y_LPARAM(pMsg->lParam) };
        ClientToScreen(pMsg->hwnd, &pt);
        if (g_toggleMode.load(std::memory_order_relaxed)) {
            if (isActive) {
                StopAutoscroll();
                g_suppressNextMBUp.store(true, std::memory_order_relaxed);
            } else {
                StartAutoscroll(pMsg->hwnd, pt);
            }
            return true;
        }
        StartAutoscroll(pMsg->hwnd, pt);
        break;
    }

    case WM_MBUTTONUP: {
        if (g_suppressNextMBUp.exchange(false, std::memory_order_relaxed))
            return true;

        bool toggleMode = g_toggleMode.load(std::memory_order_relaxed);

        if (!toggleMode && isActive)
            StopAutoscroll();

        if (toggleMode && isActive)
            return true;

        bool swallow = g_blockMiddleRelease.load(std::memory_order_relaxed)
                    || g_scrolledSinceStart.load(std::memory_order_relaxed);
        if (swallow) {
            // Hold mode let DOWN through, so clear Explorer's capture state
            // without firing a click action.
            if (!toggleMode) {
                SendMessageW(pMsg->hwnd, WM_CANCELMODE, 0, 0);
                ReleaseCapture();
            }
            return true;
        }
        break;
    }

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_XBUTTONDOWN:
        if (isActive) StopAutoscroll();
        break;

    case WM_KEYDOWN:
        if (isActive && pMsg->wParam == VK_ESCAPE) {
            StopAutoscroll();
            return true;
        }
        break;

    case WM_ACTIVATEAPP:
        if (isActive && !pMsg->wParam) StopAutoscroll();
        break;

    default:
        break;
    }
    return false;
}

// PeekMessage hooks. GetMessage is deliberately not hooked: a thread blocked
// inside a hooked GetMessage keeps the mod from unloading in explorer.exe.
// GetMessage loops are still covered through DispatchMessage.
using PeekMessageW_t = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
static PeekMessageW_t g_origPeekMessageW = nullptr;

BOOL WINAPI PeekMessageW_Hook(
    LPMSG lpMsg, HWND hWnd, UINT wMin, UINT wMax, UINT wRemoveMsg)
{
    BOOL ret = g_origPeekMessageW(lpMsg, hWnd, wMin, wMax, wRemoveMsg);
    if (ret && lpMsg && (wRemoveMsg & PM_REMOVE) && HandleMsg(lpMsg))
        lpMsg->message = WM_NULL;
    return ret;
}

using PeekMessageA_t = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
static PeekMessageA_t g_origPeekMessageA = nullptr;

BOOL WINAPI PeekMessageA_Hook(
    LPMSG lpMsg, HWND hWnd, UINT wMin, UINT wMax, UINT wRemoveMsg)
{
    BOOL ret = g_origPeekMessageA(lpMsg, hWnd, wMin, wMax, wRemoveMsg);
    if (ret && lpMsg && (wRemoveMsg & PM_REMOVE) && HandleMsg(lpMsg))
        lpMsg->message = WM_NULL;
    return ret;
}

using DispatchMessageW_t = LRESULT(WINAPI*)(const MSG*);
static DispatchMessageW_t g_origDispatchMessageW = nullptr;

LRESULT WINAPI DispatchMessageW_Hook(const MSG* pMsg) {
    if (!pMsg) return 0;
    if (HandleMsg(pMsg)) return 0;
    return g_origDispatchMessageW(pMsg);
}

using DispatchMessageA_t = LRESULT(WINAPI*)(const MSG*);
static DispatchMessageA_t g_origDispatchMessageA = nullptr;

LRESULT WINAPI DispatchMessageA_Hook(const MSG* pMsg) {
    if (!pMsg) return 0;
    if (HandleMsg(pMsg)) return 0;
    return g_origDispatchMessageA(pMsg);
}

// ===========================================================================
// Indicator: a click-through window whose content is a Windows.UI.Composition
// tree, so the GPU draws and animates it. The glass is DWM's host backdrop
// with an extra Gaussian blur, clipped to a circle.
// ===========================================================================
namespace wuc = winrt::Windows::UI::Composition;
using winrt::Windows::Foundation::Numerics::float2;
using winrt::Windows::Foundation::Numerics::float3;

static const int DIR_UP    = 1;
static const int DIR_DOWN  = 2;
static const int DIR_LEFT  = 4;
static const int DIR_RIGHT = 8;
static const UINT_PTR kHideTimer = 1;

static int GetActiveDirs() {
    POINT cursor{};
    GetCursorPos(&cursor);
    int dy  = cursor.y - g_originY.load(std::memory_order_relaxed);
    int dx  = cursor.x - g_originX.load(std::memory_order_relaxed);
    int dz  = g_deadzonePx.load(std::memory_order_relaxed);
    int dir = 0;
    if (dy < -dz) dir |= DIR_UP;
    if (dy >  dz) dir |= DIR_DOWN;
    if (dx < -dz) dir |= DIR_LEFT;
    if (dx >  dz) dir |= DIR_RIGHT;
    return dir;
}

// Interop for a composition target on a desktop window.
struct ICompositorDesktopInteropLocal : ::IUnknown {
    virtual HRESULT __stdcall CreateDesktopWindowTarget(HWND window,
                                                        BOOL isTopmost,
                                                        void** target) = 0;
    virtual HRESULT __stdcall EnsureOnThread(DWORD threadId) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<ICompositorDesktopInteropLocal>{
    0x29E691FA, 0x4567, 0x4DCA, {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}};

// DWMWA_USE_HOSTBACKDROPBRUSH: needed for a desktop app to get the blur.
constexpr DWORD kDwmUseHostBackdropBrush = 17;

// Direct2D effect interop (windows.graphics.effects.interop.h is not in the
// toolchain).
struct IGraphicsEffectD2D1InteropLocal : ::IUnknown {
    virtual HRESULT __stdcall GetEffectId(GUID* id) = 0;
    virtual HRESULT __stdcall GetNamedPropertyMapping(LPCWSTR name, UINT* index,
                                                      int* mapping) = 0;
    virtual HRESULT __stdcall GetPropertyCount(UINT* count) = 0;
    virtual HRESULT __stdcall GetProperty(UINT index, void** value) = 0;
    virtual HRESULT __stdcall GetSource(UINT index, void** source) = 0;
    virtual HRESULT __stdcall GetSourceCount(UINT* count) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<IGraphicsEffectD2D1InteropLocal>{
    0x2FC57384, 0xA068, 0x44D7, {0xA3, 0x31, 0x30, 0x98, 0x2F, 0xCF, 0x71, 0x77}};

struct GlassBlurEffect
    : winrt::implements<GlassBlurEffect,
                        winrt::Windows::Graphics::Effects::IGraphicsEffect,
                        winrt::Windows::Graphics::Effects::IGraphicsEffectSource,
                        IGraphicsEffectD2D1InteropLocal> {
    GlassBlurEffect(float sigma,
                    winrt::Windows::Graphics::Effects::IGraphicsEffectSource source)
        : m_sigma(sigma), m_source(std::move(source)) {}
    winrt::hstring Name() { return m_name; }
    void Name(winrt::hstring const& name) { m_name = name; }
    HRESULT __stdcall GetEffectId(GUID* id) override {
        // CLSID_D2D1GaussianBlur
        *id = {0x1FEB6D69, 0x2FE6, 0x4AC9, {0x8C, 0x58, 0x1D, 0x7F, 0x93, 0xE7, 0xA6, 0xA5}};
        return S_OK;
    }
    HRESULT __stdcall GetNamedPropertyMapping(LPCWSTR, UINT*, int*) override {
        return E_INVALIDARG;
    }
    HRESULT __stdcall GetPropertyCount(UINT* count) override {
        *count = 3;
        return S_OK;
    }
    HRESULT __stdcall GetProperty(UINT index, void** value) override {
        using winrt::Windows::Foundation::PropertyValue;
        winrt::Windows::Foundation::IInspectable v;
        switch (index) {
            case 0: v = PropertyValue::CreateSingle(m_sigma); break;
            case 1: v = PropertyValue::CreateUInt32(1 /* BALANCED */); break;
            case 2: v = PropertyValue::CreateUInt32(1 /* BORDER_MODE_HARD */); break;
            default: return E_INVALIDARG;
        }
        *value = winrt::detach_abi(v.as<winrt::Windows::Foundation::IPropertyValue>());
        return S_OK;
    }
    HRESULT __stdcall GetSource(UINT index, void** source) override {
        if (index != 0) return E_INVALIDARG;
        winrt::Windows::Graphics::Effects::IGraphicsEffectSource copy = m_source;
        *source = winrt::detach_abi(copy);
        return S_OK;
    }
    HRESULT __stdcall GetSourceCount(UINT* count) override {
        *count = 1;
        return S_OK;
    }

   private:
    winrt::hstring m_name = L"GlassBlur";
    float m_sigma;
    winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source;
};

static winrt::Windows::UI::Color ToColor(Rgba c, float opacity = 1.0f) {
    float a = std::clamp(c.a / 255.0f * opacity, 0.0f, 1.0f);
    return {(BYTE)std::lround(a * 255.0f), c.r, c.g, c.b};
}

class Indicator {
   public:
    bool Create(HINSTANCE hInst, const wchar_t* className);
    void Destroy();
    void Show();
    void Hide();
    void OnHideTimer();
    void Update(int dirs);
    HWND Hwnd() const { return m_hwnd; }

   private:
    void Build(UINT dpi);
    void FadeTo(wuc::Visual const& v, float to, float from = -1.0f);
    void ScaleTo(wuc::Visual const& v, float to, float from = -1.0f);
    wuc::CompositionSpriteShape Line(float2 a, float2 b,
                                     wuc::CompositionBrush const& brush, float w);
    wuc::ShapeVisual Chevron(float2 tip, float2 b1, float2 b2,
                             winrt::Windows::UI::Color color, float w);
    int AnimMs() const { return g_look.animate ? g_look.animMs : 0; }

    HWND m_hwnd = nullptr;
    winrt::Windows::System::DispatcherQueueController m_queue{nullptr};
    wuc::Compositor m_comp{nullptr};
    wuc::Desktop::DesktopWindowTarget m_target{nullptr};
    wuc::ContainerVisual m_root{nullptr};
    wuc::CompositionEasingFunction m_ease{nullptr};
    wuc::Visual m_idle[4]{nullptr, nullptr, nullptr, nullptr};
    wuc::Visual m_active[4]{nullptr, nullptr, nullptr, nullptr};
    UINT m_dpi = 0;
    int m_winPx = 0;
    bool m_visible = false;
    int m_lastDirs = -1;
};

bool Indicator::Create(HINSTANCE hInst, const wchar_t* className) {
    using CreateController_t = HRESULT(WINAPI*)(DispatcherQueueOptions, void**);
    HMODULE messaging =
        LoadLibraryExW(L"CoreMessaging.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    auto createController = messaging
        ? (CreateController_t)GetProcAddress(messaging, "CreateDispatcherQueueController")
        : nullptr;
    if (!createController) {
        Wh_Log(L"indicator: CreateDispatcherQueueController missing");
        return false;
    }
    try {
        DispatcherQueueOptions options{sizeof(options), DQTYPE_THREAD_CURRENT,
                                       DQTAT_COM_STA};
        winrt::check_hresult(createController(options, winrt::put_abi(m_queue)));
        m_comp = wuc::Compositor();
        m_ease = m_comp.CreateCubicBezierEasingFunction({0.0f, 0.0f}, {0.2f, 1.0f});

        m_hwnd = CreateWindowExW(
            WS_EX_NOREDIRECTIONBITMAP | WS_EX_LAYERED | WS_EX_TRANSPARENT |
            WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
            className, L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, hInst, this);
        if (!m_hwnd) {
            Wh_Log(L"indicator: CreateWindowExW failed (%lu)", GetLastError());
            return false;
        }
        SetLayeredWindowAttributes(m_hwnd, 0, 255, LWA_ALPHA);
        BOOL hostBackdrop = TRUE;
        DwmSetWindowAttribute(m_hwnd, kDwmUseHostBackdropBrush, &hostBackdrop,
                              sizeof(hostBackdrop));
        auto interop = m_comp.as<ICompositorDesktopInteropLocal>();
        winrt::check_hresult(
            interop->CreateDesktopWindowTarget(m_hwnd, TRUE, winrt::put_abi(m_target)));
        Build(GetDpiForSystem());
        return true;
    } catch (winrt::hresult_error const& e) {
        Wh_Log(L"indicator: composition setup failed (%08X)", (unsigned)e.code());
        return false;
    }
}

wuc::CompositionSpriteShape Indicator::Line(float2 a, float2 b,
                                            wuc::CompositionBrush const& brush,
                                            float w) {
    auto geo = m_comp.CreateLineGeometry();
    geo.Start(a);
    geo.End(b);
    auto shape = m_comp.CreateSpriteShape(geo);
    shape.StrokeBrush(brush);
    shape.StrokeThickness(w);
    shape.StrokeStartCap(wuc::CompositionStrokeCap::Round);
    shape.StrokeEndCap(wuc::CompositionStrokeCap::Round);
    return shape;
}

wuc::ShapeVisual Indicator::Chevron(float2 tip, float2 b1, float2 b2,
                                    winrt::Windows::UI::Color color, float w) {
    auto brush = m_comp.CreateColorBrush(color);
    auto v = m_comp.CreateShapeVisual();
    v.Size({(float)m_winPx, (float)m_winPx});
    v.Shapes().Append(Line(b1, tip, brush, w));
    v.Shapes().Append(Line(tip, b2, brush, w));
    return v;
}

void Indicator::Build(UINT dpi) {
    if (dpi == 0) dpi = 96;
    m_dpi = dpi;
    const Look& L = g_look;
    float scale = dpi / 96.0f;
    float size  = std::round(L.sizeDip * scale);
    float bw    = L.borderStyle == BorderStyle::None ? 0.0f
                                                     : std::max(1.0f, L.borderWidth * scale);
    float pad   = 2.0f;
    m_winPx     = (int)std::ceil(size + pad * 2);
    float c     = m_winPx / 2.0f;
    float r     = size / 2.0f;

    m_root = m_comp.CreateContainerVisual();
    m_root.Size({(float)m_winPx, (float)m_winPx});
    m_root.CenterPoint({c, c, 0.0f});
    m_target.Root(m_root);

    // Glass: host backdrop plus extra blur, clipped to the circle.
    if (L.blur) {
        auto glass = m_comp.CreateSpriteVisual();
        glass.Size({size, size});
        glass.Offset({c - r, c - r, 0.0f});
        try {
            if (L.blurAmount > 0.0f) {
                auto effect = winrt::make<GlassBlurEffect>(
                    L.blurAmount, wuc::CompositionEffectSourceParameter(L"Backdrop"));
                auto brush = m_comp.CreateEffectFactory(effect).CreateBrush();
                brush.SetSourceParameter(L"Backdrop", m_comp.CreateHostBackdropBrush());
                glass.Brush(brush);
            } else {
                glass.Brush(m_comp.CreateHostBackdropBrush());
            }
        } catch (winrt::hresult_error const& e) {
            Wh_Log(L"indicator: extra blur unavailable (%08X)", (unsigned)e.code());
            glass.Brush(m_comp.CreateHostBackdropBrush());
        }
        auto clipGeo = m_comp.CreateEllipseGeometry();
        clipGeo.Center({r, r});
        clipGeo.Radius({r, r});
        glass.Clip(m_comp.CreateGeometricClip(clipGeo));
        m_root.Children().InsertAtTop(glass);
    }

    // Tint and ring in one shape visual.
    auto body = m_comp.CreateShapeVisual();
    body.Size({(float)m_winPx, (float)m_winPx});
    {
        auto fillGeo = m_comp.CreateEllipseGeometry();
        fillGeo.Center({c, c});
        fillGeo.Radius({r, r});
        auto fill = m_comp.CreateSpriteShape(fillGeo);
        fill.FillBrush(m_comp.CreateColorBrush(ToColor(L.background, L.bgOpacity)));
        body.Shapes().Append(fill);
    }
    if (bw > 0.0f) {
        auto ringGeo = m_comp.CreateEllipseGeometry();
        float rr = r - bw / 2.0f;
        ringGeo.Center({c, c});
        ringGeo.Radius({rr, rr});
        auto ring = m_comp.CreateSpriteShape(ringGeo);
        ring.StrokeThickness(bw);
        if (L.borderStyle == BorderStyle::Gradient) {
            auto grad = m_comp.CreateLinearGradientBrush();
            float rad = L.gradAngle * 3.14159265f / 180.0f;
            float dx = std::cos(rad) * 0.5f, dy = std::sin(rad) * 0.5f;
            grad.StartPoint({0.5f - dx, 0.5f - dy});
            grad.EndPoint({0.5f + dx, 0.5f + dy});
            grad.ColorStops().Append(m_comp.CreateColorGradientStop(0.0f, ToColor(L.border1)));
            grad.ColorStops().Append(m_comp.CreateColorGradientStop(1.0f, ToColor(L.border2)));
            ring.StrokeBrush(grad);
        } else {
            ring.StrokeBrush(m_comp.CreateColorBrush(ToColor(L.border1)));
        }
        body.Shapes().Append(ring);
    }
    {
        auto dotGeo = m_comp.CreateEllipseGeometry();
        float dr = 2.5f * scale;
        dotGeo.Center({c, c});
        dotGeo.Radius({dr, dr});
        auto dot = m_comp.CreateSpriteShape(dotGeo);
        dot.FillBrush(m_comp.CreateColorBrush(ToColor(L.dot)));
        body.Shapes().Append(dot);
    }
    m_root.Children().InsertAtTop(body);

    // Arrows: an idle and an active layer each, cross-faded.
    float rc   = r - 1.0f;
    float off  = rc * 0.58f;
    float arm  = rc * 0.15f;
    float half = rc * 0.13f;
    float sw   = size * 0.048f;
    const float2 tips[4] = {{c, c - off}, {c, c + off}, {c - off, c}, {c + off, c}};
    const float2 b1s[4]  = {{c - half, c - off + arm}, {c - half, c + off - arm},
                            {c - off + arm, c - half}, {c + off - arm, c - half}};
    const float2 b2s[4]  = {{c + half, c - off + arm}, {c + half, c + off - arm},
                            {c - off + arm, c + half}, {c + off - arm, c + half}};
    for (int i = 0; i < 4; ++i) {
        auto idle = Chevron(tips[i], b1s[i], b2s[i], ToColor(L.arrow), sw);
        idle.Opacity(L.arrowOpacity);
        auto active = Chevron(tips[i], b1s[i], b2s[i], ToColor(L.arrowActive), sw);
        active.Opacity(0.0f);
        m_root.Children().InsertAtTop(idle);
        m_root.Children().InsertAtTop(active);
        m_idle[i] = idle;
        m_active[i] = active;
    }
    m_lastDirs = 0;
}

void Indicator::FadeTo(wuc::Visual const& v, float to, float from) {
    v.StopAnimation(L"Opacity");
    int ms = AnimMs();
    if (ms <= 0) {
        v.Opacity(to);
        return;
    }
    auto a = m_comp.CreateScalarKeyFrameAnimation();
    if (from >= 0.0f) a.InsertKeyFrame(0.0f, from);
    a.InsertKeyFrame(1.0f, to, m_ease);
    a.Duration(std::chrono::milliseconds(ms));
    v.StartAnimation(L"Opacity", a);
}

void Indicator::ScaleTo(wuc::Visual const& v, float to, float from) {
    v.StopAnimation(L"Scale");
    int ms = AnimMs();
    if (ms <= 0) {
        v.Scale({to, to, 1.0f});
        return;
    }
    auto a = m_comp.CreateVector3KeyFrameAnimation();
    if (from >= 0.0f) a.InsertKeyFrame(0.0f, {from, from, 1.0f});
    a.InsertKeyFrame(1.0f, {to, to, 1.0f}, m_ease);
    a.Duration(std::chrono::milliseconds(ms));
    v.StartAnimation(L"Scale", a);
}

void Indicator::Show() {
    if (!m_root) return;
    try {
        HWND target = g_targetHwnd.load(std::memory_order_relaxed);
        UINT dpi = target ? GetDpiForWindow(target) : GetDpiForSystem();
        if (dpi == 0) dpi = 96;
        if (dpi != m_dpi) Build(dpi);

        KillTimer(m_hwnd, kHideTimer);
        int ox = g_originX.load(std::memory_order_relaxed);
        int oy = g_originY.load(std::memory_order_relaxed);
        SetWindowPos(m_hwnd, HWND_TOPMOST, ox - m_winPx / 2, oy - m_winPx / 2,
                     m_winPx, m_winPx, SWP_NOACTIVATE | SWP_SHOWWINDOW);

        for (int i = 0; i < 4; ++i) {
            m_idle[i].StopAnimation(L"Opacity");
            m_idle[i].Opacity(g_look.arrowOpacity);
            m_active[i].StopAnimation(L"Opacity");
            m_active[i].Opacity(0.0f);
        }
        m_lastDirs = 0;

        bool fromHidden = !m_visible;
        FadeTo(m_root, 1.0f, fromHidden ? 0.0f : -1.0f);
        ScaleTo(m_root, 1.0f, fromHidden ? g_look.popScale : -1.0f);
        m_visible = true;
    } catch (winrt::hresult_error const& e) {
        Wh_Log(L"indicator: show failed (%08X)", (unsigned)e.code());
    }
}

void Indicator::Hide() {
    if (!m_visible || !m_root) return;
    int ms = AnimMs();
    if (ms <= 0) {
        OnHideTimer();
        return;
    }
    try {
        FadeTo(m_root, 0.0f);
        ScaleTo(m_root, g_look.popScale);
    } catch (winrt::hresult_error const&) {
    }
    SetTimer(m_hwnd, kHideTimer, (UINT)ms + 30, nullptr);
}

void Indicator::OnHideTimer() {
    KillTimer(m_hwnd, kHideTimer);
    ShowWindow(m_hwnd, SW_HIDE);
    m_visible = false;
}

void Indicator::Update(int dirs) {
    if (!m_visible || dirs == m_lastDirs) return;
    const int flags[4] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
    try {
        for (int i = 0; i < 4; ++i) {
            bool was = (m_lastDirs & flags[i]) != 0;
            bool now = (dirs & flags[i]) != 0;
            if (was == now) continue;
            FadeTo(m_active[i], now ? 1.0f : 0.0f);
            FadeTo(m_idle[i], now ? 0.0f : g_look.arrowOpacity);
        }
    } catch (winrt::hresult_error const& e) {
        Wh_Log(L"indicator: update failed (%08X)", (unsigned)e.code());
    }
    m_lastDirs = dirs;
}

void Indicator::Destroy() {
    for (auto& v : m_idle) v = nullptr;
    for (auto& v : m_active) v = nullptr;
    m_root = nullptr;
    m_ease = nullptr;
    m_target = nullptr;
    if (m_hwnd && IsWindow(m_hwnd)) DestroyWindow(m_hwnd);
    m_hwnd = nullptr;
    m_comp = nullptr;
    if (m_queue) {
        auto queue = std::move(m_queue);
        try {
            auto shutdown = queue.ShutdownQueueAsync();
            for (int i = 0; i < 100 &&
                 shutdown.Status() == winrt::Windows::Foundation::AsyncStatus::Started;
                 i++) {
                MsgWaitForMultipleObjects(0, nullptr, FALSE, 10, QS_ALLINPUT);
                MSG msg;
                while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
                    DispatchMessageW(&msg);
                }
            }
        } catch (winrt::hresult_error const& e) {
            Wh_Log(L"indicator: queue shutdown failed (%08X)", (unsigned)e.code());
        }
    }
}

static LRESULT CALLBACK IndicatorWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NCCREATE) {
        auto* cs = reinterpret_cast<CREATESTRUCTW*>(lp);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
        return TRUE;
    }
    auto* ind = reinterpret_cast<Indicator*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    switch (msg) {
    case WM_NCHITTEST:
        return HTTRANSPARENT;
    case WM_IND_SHOW:
        if (ind) ind->Show();
        return 0;
    case WM_IND_UPDATE:
        g_indUpdatePending.store(false, std::memory_order_relaxed);
        if (ind) ind->Update(GetActiveDirs());
        return 0;
    case WM_IND_HIDE:
        g_indUpdatePending.store(false, std::memory_order_relaxed);
        if (ind) ind->Hide();
        return 0;
    case WM_TIMER:
        if (wp == kHideTimer && ind) ind->OnHideTimer();
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

static HMODULE GetCurrentModuleHandle() {
    HMODULE mod = nullptr;
    GetModuleHandleExW(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        reinterpret_cast<LPCWSTR>(&GetCurrentModuleHandle), &mod);
    return mod;
}

static void IndicatorThreadProc() {
    static const wchar_t kClass[] = L"WH_SeamlessAutoscrollIndicator";

    HMODULE hMod = GetCurrentModuleHandle();
    if (!hMod) {
        Wh_Log(L"indicator: GetCurrentModuleHandle failed");
        return;
    }

    WNDCLASSEXW wc{};
    wc.cbSize        = sizeof(wc);
    wc.lpfnWndProc   = IndicatorWndProc;
    wc.hInstance     = hMod;
    wc.lpszClassName = kClass;
    // No fallback on ERROR_CLASS_ALREADY_EXISTS: a class left by an unloaded
    // instance points at unmapped code.
    if (!RegisterClassExW(&wc)) {
        Wh_Log(L"indicator: RegisterClassExW failed (%lu)", GetLastError());
        return;
    }

    {
        Indicator ind;
        if (ind.Create(hMod, kClass)) {
            g_indicatorHwnd.store(ind.Hwnd(), std::memory_order_release);
            MSG msg{};
            while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
        }
        g_indicatorHwnd.store(nullptr, std::memory_order_release);
        g_indicatorExited.store(true, std::memory_order_release);
        ind.Destroy();
    }
    UnregisterClassW(kClass, hMod);
}

// ===========================================================================
// Settings
// ===========================================================================
static Rgba ReadColor(const wchar_t* name, Rgba fallback) {
    PCWSTR s = Wh_GetStringSetting(name);
    Rgba out = fallback;
    if (s) {
        const wchar_t* p = s;
        while (*p == L' ' || *p == L'#') ++p;
        size_t len = wcslen(p);
        while (len && p[len - 1] == L' ') --len;
        wchar_t* end = nullptr;
        wchar_t buf[9] = {};
        if (len == 6 || len == 8) {
            wcsncpy(buf, p, len);
            unsigned long v = wcstoul(buf, &end, 16);
            if (end && *end == 0) {
                if (len == 6)
                    out = {255, (BYTE)(v >> 16), (BYTE)(v >> 8), (BYTE)v};
                else
                    out = {(BYTE)(v >> 24), (BYTE)(v >> 16), (BYTE)(v >> 8), (BYTE)v};
            }
        }
        Wh_FreeStringSetting(s);
    }
    return out;
}

static int ReadInt(const wchar_t* name, int lo, int hi) {
    return std::clamp(Wh_GetIntSetting(name), lo, hi);
}

static void LoadSettings() {
    int deadzone  = ReadInt(L"deadzone", 0, 64);
    int speed     = std::clamp(Wh_GetIntSetting(L"speed"), deadzone + 1, 500);
    int speedMult = ReadInt(L"speedMult", 1, 100);

    g_deadzonePx        .store(deadzone,                                  std::memory_order_relaxed);
    g_speedPx           .store(speed,                                     std::memory_order_relaxed);
    g_horzEnabled       .store(Wh_GetIntSetting(L"horizontal") != 0,      std::memory_order_relaxed);
    g_speedMult         .store(speedMult,                                 std::memory_order_relaxed);
    g_showIndicator     .store(Wh_GetIntSetting(L"showIndicator") != 0,   std::memory_order_relaxed);
    g_toggleMode        .store(Wh_GetIntSetting(L"toggleMode") != 0,      std::memory_order_relaxed);
    g_blockMiddleRelease.store(Wh_GetIntSetting(L"blockMiddleRelease") != 0, std::memory_order_relaxed);

    Look d;
    Look L;
    L.sizeDip      = ReadInt(L"size", 24, 96);
    L.blur         = Wh_GetIntSetting(L"glassBlur") != 0;
    L.blurAmount   = (float)ReadInt(L"blurAmount", 0, 40);
    L.background   = ReadColor(L"backgroundColor", d.background);
    L.bgOpacity    = ReadInt(L"backgroundOpacity", 0, 100) / 100.0f;
    PCWSTR style = Wh_GetStringSetting(L"borderStyle");
    L.borderStyle = BorderStyle::Gradient;
    if (style) {
        if (wcscmp(style, L"solid") == 0) L.borderStyle = BorderStyle::Solid;
        else if (wcscmp(style, L"none") == 0) L.borderStyle = BorderStyle::None;
        Wh_FreeStringSetting(style);
    }
    L.border1      = ReadColor(L"borderColor", d.border1);
    L.border2      = ReadColor(L"borderColor2", d.border2);
    L.gradAngle    = (float)ReadInt(L"gradientAngle", 0, 360);
    L.borderWidth  = (float)ReadInt(L"borderWidth", 1, 6);
    L.arrow        = ReadColor(L"arrowColor", d.arrow);
    L.arrowOpacity = ReadInt(L"arrowOpacity", 0, 100) / 100.0f;
    L.arrowActive  = ReadColor(L"arrowActiveColor", d.arrowActive);
    L.dot          = ReadColor(L"dotColor", d.dot);
    L.animate      = Wh_GetIntSetting(L"animations") != 0;
    L.animMs       = ReadInt(L"animationMs", 50, 400);
    L.popScale     = ReadInt(L"popScale", 50, 100) / 100.0f;
    g_look = L;
}

// ===========================================================================
// Windhawk lifecycle
// ===========================================================================
static bool HookFn(void* target, void* hook, void** orig,
                   const wchar_t* name, bool fatal = false) {
    if (Wh_SetFunctionHook(target, hook, orig)) return true;
    Wh_Log(L"failed to hook %s", name);
    if (!fatal) *orig = nullptr;
    return !fatal;
}

static void JoinAndDeleteThread(std::thread*& p) {
    if (!p) return;
    if (p->joinable()) p->join();
    delete p;
    p = nullptr;
}

static void StopIndicator() {
    if (!g_indicatorThread) return;
    // The thread may still be creating its window; wait for it to appear or
    // for the thread to give up, so the join below cannot hang.
    for (int i = 0; i < 200 && !g_indicatorExited.load(std::memory_order_acquire); ++i) {
        HWND ind = g_indicatorHwnd.load(std::memory_order_acquire);
        if (ind) {
            PostMessageW(ind, WM_CLOSE, 0, 0);
            break;
        }
        Sleep(10);
    }
    JoinAndDeleteThread(g_indicatorThread);
}

static void StartIndicator() {
    g_indicatorExited.store(false, std::memory_order_release);
    g_indicatorThread = new std::thread(IndicatorThreadProc);
}

BOOL Wh_ModInit() {
    LoadSettings();

    HookFn((void*)PeekMessageW, (void*)PeekMessageW_Hook,
           (void**)&g_origPeekMessageW, L"PeekMessageW");
    HookFn((void*)PeekMessageA, (void*)PeekMessageA_Hook,
           (void**)&g_origPeekMessageA, L"PeekMessageA");

    if (!HookFn((void*)DispatchMessageW, (void*)DispatchMessageW_Hook,
                (void**)&g_origDispatchMessageW, L"DispatchMessageW", true))
        return FALSE;
    HookFn((void*)DispatchMessageA, (void*)DispatchMessageA_Hook,
           (void**)&g_origDispatchMessageA, L"DispatchMessageA");

    return TRUE;
}

void Wh_ModAfterInit() {
    g_scrollEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g_scrollEvent) {
        Wh_Log(L"CreateEventW failed (%lu), scroll thread not started", GetLastError());
        return;
    }
    g_threadRunning.store(true, std::memory_order_relaxed);
    g_scrollThread = new std::thread(ScrollThreadProc);
    if (g_showIndicator.load(std::memory_order_relaxed))
        StartIndicator();
}

void Wh_ModSettingsChanged() {
    StopAutoscroll();
    // The indicator thread reads g_look, so stop it before reloading and
    // start a fresh one with the new look.
    StopIndicator();
    LoadSettings();
    if (g_showIndicator.load(std::memory_order_relaxed))
        StartIndicator();
}

void Wh_ModBeforeUninit() {
    StopAutoscroll();
    HWND ind = g_indicatorHwnd.load(std::memory_order_acquire);
    if (ind) PostMessageW(ind, WM_CLOSE, 0, 0);
}

void Wh_ModUninit() {
    g_threadRunning.store(false, std::memory_order_relaxed);
    if (g_scrollEvent) SetEvent(g_scrollEvent);
    JoinAndDeleteThread(g_scrollThread);
    if (g_scrollEvent) { CloseHandle(g_scrollEvent); g_scrollEvent = nullptr; }
    JoinAndDeleteThread(g_indicatorThread);

    g_origPeekMessageW     = nullptr;
    g_origPeekMessageA     = nullptr;
    g_origDispatchMessageW = nullptr;
    g_origDispatchMessageA = nullptr;
}
