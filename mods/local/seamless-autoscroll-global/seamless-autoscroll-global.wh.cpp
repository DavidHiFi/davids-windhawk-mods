// ==WindhawkMod==
// @id              seamless-autoscroll-global
// @name            Seamless Autoscroll Global
// @description     The frosted autoscroll circle in every app the per-app mod does not cover, with the same look
// @version         1.0.0
// @author          DavidHiFi, crazyboyybs
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         GPL-3.0
// @include         windhawk.exe
// @include         windhawk-mod.exe
// @include         windhawk-mod-elevated.exe
// @compilerOptions -DWIN32_LEAN_AND_MEAN -luser32 -ladvapi32 -lole32 -loleaut32 -ldwmapi -lruntimeobject -lgdi32 -lshell32
// ==/WindhawkMod==

// Source code is published under The GNU General Public License v3.0.

// ==WindhawkModReadme==
/*
# Seamless Autoscroll Global

Made by **DavidHiFi**. Based on
[AutoScroll Win32](https://windhawk.net/mods/autoscroll-win32) by
[crazyboyybs](https://github.com/crazyboyybs). The scrolling engine and the
indicator are the ones from Seamless Autoscroll.

Seamless Autoscroll loads inside a list of apps. This companion runs once for
the whole desktop and covers everything that list misses: File Manager tools,
PDF readers, chat apps you add later, anything new you install. Same frosted
glass circle, same colors, same feel, everywhere, so the plain white one never
shows up again.

![Seamless Autoscroll Global preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-autoscroll-global.png)

## How it works

- It follows the settings of Seamless Autoscroll. Change them there and this
  one keeps up on its own. It has no settings of its own.
- Where Seamless Autoscroll is already loaded in an app, this one steps aside,
  so there is never a double circle.
- In browsers it replaces the browser's own white circle with the frosted one,
  even in browsers Seamless Autoscroll does not know.
- In fullscreen games it does nothing at all, so middle clicks in games stay
  exactly as they are.

## Notes

- Keep both mods on. Seamless Autoscroll does the apps it knows best, this one
  picks up the rest. Turning this one off brings the white circle back in the
  apps it covers.
- In an app neither mod knows, a quick middle click with no scrolling may do
  nothing. The frosted scroll itself always works.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- toggleMode: false
  $name: Click to start and stop
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- horizontal: true
  $name: Scroll sideways too
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- deadzone: 8
  $name: Still zone (px)
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- speed: 150
  $name: Full speed distance (px)
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- speedMult: 30
  $name: Top speed
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- blockMiddleRelease: false
  $name: Hide the button release from apps
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- showIndicator: true
  $name: Show the indicator
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- size: 44
  $name: Indicator size (px)
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- glassBlur: true
  $name: Glass blur
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- blurAmount: 18
  $name: Blur strength
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- backgroundColor: "#1E1E2E"
  $name: Background color
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- backgroundOpacity: 70
  $name: Background opacity (%)
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- borderStyle: gradient
  $name: Ring style
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
  $options:
  - gradient: Gradient
  - solid: Solid color
  - none: No ring
- borderColor: "#89B4FA"
  $name: Ring color
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- borderColor2: "#CBA6F7"
  $name: Ring gradient end color
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- gradientAngle: 45
  $name: Gradient angle
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- borderWidth: 2
  $name: Ring thickness (px)
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- arrowColor: "#CDD6F4"
  $name: Arrow color
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- arrowOpacity: 40
  $name: Idle arrow opacity (%)
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- arrowActiveColor: "#89B4FA"
  $name: Active arrow color
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- dotColor: "#CBA6F7"
  $name: Center dot color
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- animations: true
  $name: Animations
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- animationMs: 160
  $name: Animation length (ms)
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
- popScale: 80
  $name: Starting size (%)
  $description: "Follows Seamless Autoscroll. Shown here so both mods agree."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
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
#include <string>
#include <thread>

// ===========================================================================
// Settings. The real values are mirrored from Seamless Autoscroll every few
// seconds; the block above only exists so both mods agree on the names.
// ===========================================================================
static std::atomic<int>  g_deadzonePx{8};
static std::atomic<int>  g_speedPx{150};
static std::atomic<bool> g_horzEnabled{true};
static std::atomic<int>  g_speedMult{30};
static std::atomic<bool> g_showIndicator{true};
static std::atomic<bool> g_toggleMode{false};
static std::atomic<bool> g_blockMiddleRelease{false};

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

static std::atomic<bool> g_suppressNextMBUp{false};

// ===========================================================================
// Autoscroll state (same engine as Seamless Autoscroll)
// ===========================================================================
static std::atomic<HWND> g_targetHwnd{nullptr};
static std::atomic<int>  g_originX{0};
static std::atomic<int>  g_originY{0};

static const UINT WM_IND_SHOW   = WM_USER + 1;
static const UINT WM_IND_HIDE   = WM_USER + 2;
static const UINT WM_IND_UPDATE = WM_USER + 3;

static std::atomic<bool> g_threadRunning{false};
static std::thread*      g_scrollThread = nullptr;

static std::atomic<HWND> g_indicatorHwnd{nullptr};
static std::thread*      g_indicatorThread = nullptr;
static std::atomic<bool> g_indicatorExited{true};

static HANDLE g_scrollEvent = nullptr;

static std::atomic<bool> g_scrolledSinceStart{false};
static std::atomic<bool> g_indUpdatePending{false};
static std::atomic<DWORD> g_frameMs{16};

// Set while a gesture we own is running. The mouse hook reads it.
static std::atomic<bool> g_active{false};
// True when the current gesture swallowed the middle button down, so the
// paired up must be swallowed too.
static std::atomic<bool> g_ateDown{false};

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
                        (int)WHEEL_DELTA);
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
    g_active.store(true, std::memory_order_release);
    if (g_scrollEvent) SetEvent(g_scrollEvent);
    HWND ind = g_indicatorHwnd.load(std::memory_order_acquire);
    if (ind) PostMessageW(ind, WM_IND_SHOW, 0, 0);
}

static void StopAutoscroll() {
    g_targetHwnd.store(nullptr, std::memory_order_release);
    g_active.store(false, std::memory_order_release);
    g_ateDown.store(false, std::memory_order_release);
    HWND ind = g_indicatorHwnd.load(std::memory_order_acquire);
    if (ind) PostMessageW(ind, WM_IND_HIDE, 0, 0);
}

// ===========================================================================
// Who owns the click: the per-app mod covers the apps on its Include list,
// fullscreen games are left completely alone, everything else is ours.
// ===========================================================================
static SRWLOCK g_coverLock = SRWLOCK_INIT;
static std::wstring g_coverList;      // Include list of seamless-autoscroll
static std::wstring g_coverLower;     // lowercase copy

static void Lower(std::wstring& s) {
    for (auto& c : s) c = (wchar_t)towlower(c);
}

// Name matches one entry of the pipe-separated list. An entry ending in *
// matches by prefix, the way Windhawk matches process names.
static bool MatchesList(const std::wstring& list, const std::wstring& name) {
    size_t pos = 0;
    while (pos < list.size()) {
        size_t bar = list.find(L'|', pos);
        if (bar == std::wstring::npos) bar = list.size();
        std::wstring entry = list.substr(pos, bar - pos);
        pos = bar + 1;
        if (entry.empty()) continue;
        bool prefix = false;
        if (!entry.empty() && entry.back() == L'*') {
            prefix = true;
            entry.pop_back();
        }
        if (prefix) {
            if (name.size() >= entry.size() &&
                name.compare(0, entry.size(), entry) == 0) return true;
        } else if (name == entry) {
            return true;
        }
    }
    return false;
}

// Chromium browsers the per-app mod does not know draw their own white circle
// on middle down, so our down must be swallowed there. Any app on the covered
// list is left to the per-app mod, which already handles its browsers.
static bool IsChromiumImage(const std::wstring& exe) {
    static const wchar_t* kNames[] = {
        L"chrome.exe", L"msedge.exe", L"brave.exe", L"vivaldi.exe",
        L"chromium.exe", L"opera.exe", L"thorium.exe", L"arc.exe",
        L"msedgewebview2.exe", L"helium.exe", L"min.exe", L"supermium.exe",
        L"iridium.exe", L"ungoogled-chromium.exe", L"librewolf.exe",
        L"waterfox.exe", L"floorp.exe", L"zen.exe", L"dia.exe",
    };
    for (const wchar_t* n : kNames) {
        if (_wcsicmp(exe.c_str(), n) == 0) return true;
    }
    return false;
}

static bool ProcessNameForWindow(HWND hwnd, std::wstring& name) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (!pid) return false;
    HANDLE proc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!proc) return false;
    wchar_t path[MAX_PATH]{};
    DWORD size = MAX_PATH;
    bool ok = QueryFullProcessImageNameW(proc, 0, path, &size) != 0;
    CloseHandle(proc);
    if (!ok) return false;
    const wchar_t* slash = wcsrchr(path, L'\\');
    name = slash ? slash + 1 : path;
    Lower(name);
    return true;
}

// A fullscreen window covering a whole monitor is a game or a video. Pass
// everything through untouched there.
static bool ForegroundFullscreen(POINT pt) {
    HWND hwnd = WindowFromPoint(pt);
    if (!hwnd) hwnd = GetForegroundWindow();
    if (!hwnd) return false;
    hwnd = GetAncestor(hwnd, GA_ROOT);
    HMONITOR mon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(mon, &mi)) return false;
    RECT wr{};
    if (!GetWindowRect(hwnd, &wr)) return false;
    return wr.left <= mi.rcMonitor.left && wr.top <= mi.rcMonitor.top &&
           wr.right >= mi.rcMonitor.right && wr.bottom >= mi.rcMonitor.bottom;
}

static HWND ScrollTargetForPoint(POINT pt) {
    GUITHREADINFO gti{};
    gti.cbSize = sizeof(gti);
    HWND hwnd = nullptr;
    if (GetGUIThreadInfo(0, &gti) && gti.hwndFocus) {
        hwnd = gti.hwndFocus;
    }
    if (!hwnd) {
        hwnd = WindowFromPoint(pt);
        if (hwnd) hwnd = GetAncestor(hwnd, GA_ROOT);
    }
    if (hwnd && !IsWindowVisible(hwnd)) hwnd = WindowFromPoint(pt);
    return hwnd;
}

// ===========================================================================
// Global mouse hook. Runs on its own thread with a message window; the hook
// callback does only light work and posts to the indicator.
// ===========================================================================
static HWND  g_hookWnd = nullptr;
static HHOOK g_hook = nullptr;
static HHOOK g_kbdHook = nullptr;
static DWORD g_hookThreadId = 0;
static std::thread* g_hookThread = nullptr;

static const UINT kHookClose = WM_APP + 1;

// Esc stops a running scroll, the same as the per-app mod. The key is never
// swallowed.
LRESULT CALLBACK GlobalKeyProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && wp == WM_KEYDOWN && lp) {
        auto* info = reinterpret_cast<KBDLLHOOKSTRUCT*>(lp);
        if (info->vkCode == VK_ESCAPE &&
            g_active.load(std::memory_order_acquire))
            StopAutoscroll();
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

LRESULT CALLBACK GlobalMouseProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && lp) {
        auto* info = reinterpret_cast<MSLLHOOKSTRUCT*>(lp);
        if (wp == WM_MBUTTONDOWN) {
            std::wstring exe;
            HWND target = ScrollTargetForPoint(info->pt);
            HWND root = target ? GetAncestor(target, GA_ROOT) : nullptr;
            bool covered = false;
            if (root && ProcessNameForWindow(root, exe)) {
                AcquireSRWLockShared(&g_coverLock);
                covered = MatchesList(g_coverLower, exe);
                ReleaseSRWLockShared(&g_coverLock);
            }
            // Settings windows of our own mods run their middle-click
            // autoscroll and mark themselves; leave them alone.
            bool owned = root && GetPropW(root, L"SeamlessOwnAutoscroll");
            if (covered || owned || ForegroundFullscreen(info->pt))
                return CallNextHookEx(nullptr, code, wp, lp);

            bool toggleMode = g_toggleMode.load(std::memory_order_relaxed);
            if (g_active.load(std::memory_order_acquire)) {
                if (toggleMode) {
                    StopAutoscroll();
                    g_suppressNextMBUp.store(true, std::memory_order_relaxed);
                    return 1;
                }
                return CallNextHookEx(nullptr, code, wp, lp);
            }
            g_ateDown.store(false, std::memory_order_relaxed);
            StartAutoscroll(target ? target : WindowFromPoint(info->pt),
                            info->pt);
            // Toggle mode consumes every middle click, the same as the
            // per-app mod, so the app never sees it.
            if (toggleMode) return 1;
            // Chromium draws its own white circle on middle down; swallow it
            // so only ours shows, then drive the scroll with wheel posts.
            if (IsChromiumImage(exe)) {
                g_ateDown.store(true, std::memory_order_release);
                return 1;
            }
            // Hold mode passes the down through, the same as the per-app mod.
            return CallNextHookEx(nullptr, code, wp, lp);
        }
        if (wp == WM_LBUTTONDOWN || wp == WM_RBUTTONDOWN ||
            wp == WM_XBUTTONDOWN) {
            if (g_active.load(std::memory_order_acquire)) StopAutoscroll();
            return CallNextHookEx(nullptr, code, wp, lp);
        }
        if (wp == WM_MBUTTONUP) {
            if (g_suppressNextMBUp.exchange(false, std::memory_order_relaxed))
                return 1;
            if (!g_active.load(std::memory_order_acquire))
                return CallNextHookEx(nullptr, code, wp, lp);
            bool ate = g_ateDown.load(std::memory_order_acquire);
            bool toggleMode = g_toggleMode.load(std::memory_order_relaxed);
            StopAutoscroll();
            bool swallow = ate
                || g_blockMiddleRelease.load(std::memory_order_relaxed)
                || g_scrolledSinceStart.load(std::memory_order_relaxed);
            if (swallow) {
                // Hold mode let the down through, so the app may hold the
                // mouse capture; end it without a click action.
                HWND target = ScrollTargetForPoint(info->pt);
                if (target)
                    SendMessageTimeoutW(target, WM_CANCELMODE, 0, 0,
                                        SMTO_ABORTIFHUNG, 200, nullptr);
                return 1;
            }
            if (toggleMode) return 1;
            return CallNextHookEx(nullptr, code, wp, lp);
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

static LRESULT CALLBACK HookWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case kHookClose:
        if (g_hook) {
            UnhookWindowsHookEx(g_hook);
            g_hook = nullptr;
        }
        if (g_kbdHook) {
            UnhookWindowsHookEx(g_kbdHook);
            g_kbdHook = nullptr;
        }
        DestroyWindow(hwnd);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// Plain cdecl entry: this toolchain's std::thread rejects a WINAPI function.
static DWORD HookThreadProc() {
    static const wchar_t kClass[] = L"WH_SeamlessAutoscrollGlobalHook";
    HMODULE hMod = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCWSTR>(&HookWndProc), &hMod);
    if (!hMod) return 1;

    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc   = HookWndProc;
    wc.hInstance     = hMod;
    wc.lpszClassName = kClass;
    if (!RegisterClassExW(&wc)) return 1;

    g_hookWnd = CreateWindowExW(0, kClass, L"", WS_POPUP, 0, 0, 0, 0,
                                nullptr, nullptr, hMod, nullptr);
    if (!g_hookWnd) return 1;

    g_hookThreadId = GetCurrentThreadId();
    g_kbdHook = SetWindowsHookExW(WH_KEYBOARD_LL, GlobalKeyProc, hMod, 0);
    g_hook = SetWindowsHookExW(WH_MOUSE_LL, GlobalMouseProc, hMod, 0);

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}

// ===========================================================================
// Indicator: copied from Seamless Autoscroll, a click-through window whose
// content is a Windows.UI.Composition tree drawn by the GPU.
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

struct ICompositorDesktopInteropLocal : ::IUnknown {
    virtual HRESULT __stdcall CreateDesktopWindowTarget(HWND window,
                                                        BOOL isTopmost,
                                                        void** target) = 0;
    virtual HRESULT __stdcall EnsureOnThread(DWORD threadId) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<ICompositorDesktopInteropLocal>{
    0x29E691FA, 0x4567, 0x4DCA, {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}};

constexpr DWORD kDwmUseHostBackdropBrush = 17;

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
            case 1: v = PropertyValue::CreateUInt32(1); break;
            case 2: v = PropertyValue::CreateUInt32(1); break;
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
    static const wchar_t kClass[] = L"WH_SeamlessAutoscrollGlobalIndicator";

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
// Settings mirror. Reads Seamless Autoscroll's settings and its Include list
// from the registry every two seconds and applies what changed.
// ===========================================================================
static const wchar_t kSourceModsKey[] =
    L"SOFTWARE\\Windhawk\\Engine\\Mods\\local@seamless-autoscroll";
static const wchar_t kSourceSettingsKey[] =
    L"SOFTWARE\\Windhawk\\Engine\\Mods\\local@seamless-autoscroll\\Settings";

static DWORD RegDw(HKEY key, const wchar_t* name, DWORD fallback) {
    DWORD v = 0, size = sizeof(v), type = 0;
    if (RegGetValueW(key, nullptr, name, RRF_RT_REG_DWORD, &type, &v,
                     &size) == ERROR_SUCCESS && size == sizeof(v))
        return v;
    return fallback;
}

static std::wstring RegStr(HKEY key, const wchar_t* name) {
    wchar_t buf[512]{};
    DWORD size = sizeof(buf) - sizeof(wchar_t), type = 0;
    if (RegGetValueW(key, nullptr, name, RRF_RT_REG_SZ, &type, buf,
                     &size) == ERROR_SUCCESS) {
        buf[511] = 0;
        return buf;
    }
    return {};
}

static Rgba ParseColor(const std::wstring& s, Rgba fallback) {
    std::wstring p = s;
    while (!p.empty() && (p.front() == L' ' || p.front() == L'#')) p.erase(p.begin());
    while (!p.empty() && p.back() == L' ') p.pop_back();
    if (p.size() != 6 && p.size() != 8) return fallback;
    wchar_t* end = nullptr;
    unsigned long v = wcstoul(p.c_str(), &end, 16);
    if (!end || *end) return fallback;
    if (p.size() == 6)
        return {255, (BYTE)(v >> 16), (BYTE)(v >> 8), (BYTE)v};
    return {(BYTE)(v >> 24), (BYTE)(v >> 16), (BYTE)(v >> 8), (BYTE)v};
}

static int Clamp(int v, int lo, int hi) { return std::clamp(v, lo, hi); }

static bool ApplyMirror() {
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, kSourceSettingsKey, 0,
                      KEY_QUERY_VALUE, &key) != ERROR_SUCCESS)
        return false;

    int deadzone  = Clamp((int)RegDw(key, L"deadzone", 8), 0, 64);
    int speed     = Clamp((int)RegDw(key, L"speed", 150), deadzone + 1, 500);
    int speedMult = Clamp((int)RegDw(key, L"speedMult", 30), 1, 100);

    g_deadzonePx.store(deadzone, std::memory_order_relaxed);
    g_speedPx.store(speed, std::memory_order_relaxed);
    g_horzEnabled.store(RegDw(key, L"horizontal", 1) != 0, std::memory_order_relaxed);
    g_speedMult.store(speedMult, std::memory_order_relaxed);
    g_showIndicator.store(RegDw(key, L"showIndicator", 1) != 0, std::memory_order_relaxed);
    g_toggleMode.store(RegDw(key, L"toggleMode", 0) != 0, std::memory_order_relaxed);
    g_blockMiddleRelease.store(RegDw(key, L"blockMiddleRelease", 0) != 0,
                               std::memory_order_relaxed);

    Look d;
    Look L;
    L.sizeDip      = Clamp((int)RegDw(key, L"size", 44), 24, 96);
    L.blur         = RegDw(key, L"glassBlur", 1) != 0;
    L.blurAmount   = (float)Clamp((int)RegDw(key, L"blurAmount", 18), 0, 40);
    L.background   = ParseColor(RegStr(key, L"backgroundColor"), d.background);
    L.bgOpacity    = Clamp((int)RegDw(key, L"backgroundOpacity", 70), 0, 100) / 100.0f;
    std::wstring style = RegStr(key, L"borderStyle");
    L.borderStyle = BorderStyle::Gradient;
    if (style == L"solid") L.borderStyle = BorderStyle::Solid;
    else if (style == L"none") L.borderStyle = BorderStyle::None;
    L.border1      = ParseColor(RegStr(key, L"borderColor"), d.border1);
    L.border2      = ParseColor(RegStr(key, L"borderColor2"), d.border2);
    L.gradAngle    = (float)Clamp((int)RegDw(key, L"gradientAngle", 45), 0, 360);
    L.borderWidth  = (float)Clamp((int)RegDw(key, L"borderWidth", 2), 1, 6);
    L.arrow        = ParseColor(RegStr(key, L"arrowColor"), d.arrow);
    L.arrowOpacity = Clamp((int)RegDw(key, L"arrowOpacity", 40), 0, 100) / 100.0f;
    L.arrowActive  = ParseColor(RegStr(key, L"arrowActiveColor"), d.arrowActive);
    L.dot          = ParseColor(RegStr(key, L"dotColor"), d.dot);
    L.animate      = RegDw(key, L"animations", 1) != 0;
    L.animMs       = Clamp((int)RegDw(key, L"animationMs", 160), 50, 400);
    L.popScale     = Clamp((int)RegDw(key, L"popScale", 80), 50, 100) / 100.0f;
    RegCloseKey(key);

    bool lookChanged = memcmp(&L, &g_look, sizeof(Look)) != 0;
    g_look = L;

    // The per-app mod's Include list: apps it covers, we leave alone.
    std::wstring cover;
    HKEY modsKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, kSourceModsKey, 0, KEY_QUERY_VALUE,
                      &modsKey) == ERROR_SUCCESS) {
        cover = RegStr(modsKey, L"Include");
        RegCloseKey(modsKey);
    }
    Lower(cover);
    {
        AcquireSRWLockExclusive(&g_coverLock);
        g_coverLower = cover;
        ReleaseSRWLockExclusive(&g_coverLock);
    }
    return lookChanged;
}

static std::thread* g_mirrorThread = nullptr;
static std::atomic<bool> g_mirrorRunning{false};

// Defined in the lifecycle section below.
static void StopIndicator();
static void StartIndicator();

static void MirrorThreadProc() {
    while (g_mirrorRunning.load(std::memory_order_relaxed)) {
        bool lookChanged = ApplyMirror();
        if (lookChanged) {
            // The indicator thread reads the look, so rebuild it.
            StopAutoscroll();
            StopIndicator();
            StartIndicator();
        }
        // Sleep in short steps so shutdown stays quick.
        for (int i = 0; i < 20 && g_mirrorRunning.load(std::memory_order_relaxed); ++i)
            Sleep(100);
    }
}

// ===========================================================================
// Lifecycle
// ===========================================================================
static void JoinAndDeleteThread(std::thread*& p) {
    if (!p) return;
    if (p->joinable()) p->join();
    delete p;
    p = nullptr;
}

static void StopIndicator() {
    if (!g_indicatorThread) return;
    // The window may still be coming up; post close until the thread exits.
    for (int i = 0; i < 40 && !g_indicatorExited.load(std::memory_order_acquire);
         ++i) {
        HWND ind = g_indicatorHwnd.load(std::memory_order_acquire);
        if (ind) PostMessageW(ind, WM_CLOSE, 0, 0);
        Sleep(50);
    }
    JoinAndDeleteThread(g_indicatorThread);
}

static void StartIndicator() {
    g_indicatorExited.store(false, std::memory_order_release);
    g_indicatorThread = new std::thread(IndicatorThreadProc);
}

// The unelevated host hands over to an elevated one, the same way Seamless
// Window Manager runs its global helper.
static BOOL CALLBACK CloseFalseFailureBox(HWND hwnd, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != GetCurrentProcessId()) return TRUE;
    WCHAR cls[16]{};
    WCHAR title[32]{};
    GetClassNameW(hwnd, cls, ARRAYSIZE(cls));
    GetWindowTextW(hwnd, title, ARRAYSIZE(title));
    if (wcscmp(cls, L"#32770") == 0 && wcscmp(title, L"Windhawk") == 0) {
        PostMessageW(hwnd, WM_CLOSE, 0, 0);
        Wh_Log(L"Closed false tool-mod failure box");
    }
    return TRUE;
}

static DWORD WINAPI FalseFailureBoxThreadProc(LPVOID) {
    for (int i = 0; i < 60; i++) {
        EnumWindows(CloseFalseFailureBox, 0);
        Sleep(250);
    }
    return 0;
}

BOOL WhTool_ModInit() {
    HANDLE token;
    TOKEN_ELEVATION elevation{};
    DWORD bytes = 0;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return FALSE;
    bool queried = GetTokenInformation(token, TokenElevation, &elevation,
                                       sizeof(elevation), &bytes);
    CloseHandle(token);
    if (!queried) return FALSE;
    if (!elevation.TokenIsElevated) {
        SHELLEXECUTEINFOW launch{sizeof(launch)};
        launch.fMask = SEE_MASK_FLAG_NO_UI;
        launch.lpVerb = L"runas";
        WCHAR self[MAX_PATH];
        if (!GetModuleFileNameW(nullptr, self, MAX_PATH)) return FALSE;
        launch.lpFile = self;
        launch.lpParameters = L"-windhawk-tool-mod \"" WH_MOD_ID L"\"";
        launch.nShow = SW_HIDE;
        // Returning FALSE exits with code 1, which Windhawk reports as a
        // failed tool mod. The admin copy takes over, so leave cleanly.
        if (ShellExecuteExW(&launch)) ExitProcess(0);
        return FALSE;
    }
    if (HANDLE boxThread = CreateThread(nullptr, 0, FalseFailureBoxThreadProc,
                                        nullptr, 0, nullptr)) {
        CloseHandle(boxThread);
    }

    ApplyMirror();

    g_scrollEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g_scrollEvent) {
        Wh_Log(L"CreateEventW failed (%lu)", GetLastError());
        return FALSE;
    }
    g_threadRunning.store(true, std::memory_order_relaxed);
    g_scrollThread = new std::thread(ScrollThreadProc);

    g_hookThread = new std::thread(HookThreadProc);
    // Wait for the hook to come up before reporting success.
    for (int i = 0; i < 100 && !g_hook; ++i) Sleep(10);
    if (!g_hook) {
        Wh_Log(L"mouse hook failed to start");
        return FALSE;
    }

    if (g_showIndicator.load(std::memory_order_relaxed)) StartIndicator();

    g_mirrorRunning.store(true, std::memory_order_relaxed);
    g_mirrorThread = new std::thread(MirrorThreadProc);
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    // The settings live in Seamless Autoscroll; the mirror picks them up on
    // its own within two seconds.
}

void WhTool_ModUninit() {
    g_mirrorRunning.store(false, std::memory_order_relaxed);
    JoinAndDeleteThread(g_mirrorThread);

    StopAutoscroll();
    g_threadRunning.store(false, std::memory_order_relaxed);
    if (g_scrollEvent) SetEvent(g_scrollEvent);
    JoinAndDeleteThread(g_scrollThread);
    if (g_scrollEvent) {
        CloseHandle(g_scrollEvent);
        g_scrollEvent = nullptr;
    }

    if (g_hookWnd) {
        PostMessageW(g_hookWnd, kHookClose, 0, 0);
    }
    JoinAndDeleteThread(g_hookThread);
    g_hookWnd = nullptr;
    g_hookThreadId = 0;

    StopIndicator();
}

// Windhawk 2 ships the tool mod launcher as a header. Windhawk 1.x does not,
// so it gets the launcher at the end of this file.
#if __has_include(<windhawk_tool_mod.h>)
#include <windhawk_tool_mod.h>
#else

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

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
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
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}

#endif
