// ==WindhawkMod==
// @id              local@seamless-power-action-countdown
// @name            Seamless Power Action Countdown
// @description     Mocha glass countdown before shutdown, restart, sleep or hibernation. Any key or click cancels.
// @version         2.0.1
// @author          DavidHiFi, Nerdworld
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         explorer.exe
// @include         RuntimeBroker.exe
// @architecture    x86-64
// @compilerOptions -lole32 -lgdi32 -lgdiplus
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Power Action Countdown

A clean countdown before Windows shuts down, restarts, sleeps or hibernates.
Any key, click or scroll cancels it. The overlay matches the Mocha rice: real
acrylic glass, FiraCode Nerd Font and a smooth blue to mauve gradient.

![Seamless Power Action Countdown preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-power-action-countdown.png)

## Features

- **Cancellable countdown.** Any keyboard key, mouse button, scroll wheel or
  touchscreen press cancels the action. Mouse movement is ignored, and the
  cancelling input is never passed to the app underneath.
- **Per-action timing.** Separate countdowns for shutdown, restart, sleep and
  hibernation, 0 to 30 seconds. A value of 0 runs the action at once.
- **Your background.** Glassy acrylic, plain blur, solid color or fully
  transparent, with any color and strength you like.
- **Your font.** Any font family and weight installed on the PC. Medium
  FiraCode Nerd Font is the default.
- **Gradient overlay.** A smooth blue to mauve wash over the whole screen and
  the text, with an adjustable strength.

## How to use

The countdown shows on the primary monitor when a power action is started
through the Start menu and other shell paths. Press any key, click a mouse
button or scroll to cancel.

Moving the mouse alone does not cancel the countdown.

## Notes

- Power actions from shutdown.exe, Task Manager or the Ctrl+Alt+Delete screen
  are not covered unless they call a hooked shell API.
- If a countdown should not appear for one action, set that action to 0.

## Credits

Based on [Power Action Countdown](https://windhawk.net/mods/power-action-countdown)
by Nerdworld. MIT.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- shutdownCountdownSeconds: 5
  $name: Shutdown countdown in seconds
  $description: 0 to 30. 0 shuts down at once (Suggested: 5).
- restartCountdownSeconds: 5
  $name: Restart countdown in seconds
  $description: 0 to 30. 0 restarts at once (Suggested: 5).
- sleepCountdownSeconds: 5
  $name: Sleep countdown in seconds
  $description: 0 to 30. 0 sleeps at once (Suggested: 5).
- hibernateCountdownSeconds: 5
  $name: Hibernation countdown in seconds
  $description: 0 to 30. 0 hibernates at once (Suggested: 5).
- look:
  - backgroundMaterial: glass
    $name: Background material
    $description: The surface behind the countdown (Suggested: Glass).
    $options:
    - glass: Glass (acrylic blur)
    - blur: Blur (frost, no tint)
    - mocha: Mocha (solid color)
    - clear: Transparent (no material)
  - backgroundColor: "#181825"
    $name: Background color
    $description: Hex like #181825 (Suggested: Catppuccin Mocha mantle #181825).
  - backgroundOpacity: 92
    $name: Background strength (%)
    $description: Glass tint strength. 0 shows the blurred desktop as it is, 100 is a solid color (Suggested: 92).
  - openCloseAnimation: true
    $name: Open and close animation
    $description: When on, the overlay fades in with a soft zoom and fades out (Suggested: on).
  - gradientOverlay: true
    $name: Gradient overlay
    $description: When on, a smooth gradient washes the whole overlay and the text (Suggested: on).
  - gradientStartColor: "#89B4FA"
    $name: Gradient start color
    $description: Top of the gradient. Hex like #89B4FA (Suggested: Mocha blue #89B4FA).
  - gradientEndColor: "#CBA6F7"
    $name: Gradient end color
    $description: Bottom of the gradient. Hex like #CBA6F7 (Suggested: Mocha mauve #CBA6F7).
  - gradientAreaOpacity: 20
    $name: Gradient strength over the background (%)
    $description: How visible the gradient wash over the whole area is, 0 to 100 (Suggested: 20).
  $name: Look
  $description: Background material, colors and the gradient overlay.
- font:
  - fontFamily: FiraCode Nerd Font
    $name: Font
    $description: Any font installed on the PC. Falls back to Segoe UI (Suggested: FiraCode Nerd Font).
  - fontWeight: medium
    $name: Font weight
    $description: How thick the text is (Suggested: Medium).
    $options:
    - light: Light
    - regular: Regular
    - medium: Medium
    - semibold: Semibold
    - bold: Bold
  - textColor: "#89B4FA"
    $name: Text color
    $description: Used when the gradient overlay is off. Hex like #89B4FA (Suggested: Mocha blue #89B4FA).
  $name: Font
  $description: Font family, weight and text color.
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windhawk_utils.h>
#include <objbase.h>
#include <objidl.h>
#include <gdiplus.h>

#include <algorithm>
#include <atomic>
#include <cwchar>
#include <iterator>
#include <string>

namespace {

constexpr int kMaximumCountdownSeconds = 30;
constexpr UINT kCancelCountdownMessage = WM_APP + 1;
constexpr UINT_PTR kCountdownTimerId = 1;
constexpr UINT kCountdownTimerIntervalMs = 250;
constexpr UINT_PTR kAnimationTimerId = 2;
constexpr UINT kAnimationTimerIntervalMs = 16;
constexpr UINT kFadeInMs = 180;
constexpr UINT kFadeOutMs = 120;
constexpr NTSTATUS kStatusCancelled = static_cast<NTSTATUS>(0xC0000120L);

// User32 window composition accent (used by every glass surface on this PC).
constexpr DWORD kWcaAccentPolicy = 19;
constexpr INT kAccentDisabled = 0;
constexpr INT kAccentEnableBlurBehind = 3;
constexpr INT kAccentEnableAcrylicBlurBehind = 4;

enum class PowerAction {
    Shutdown,
    Restart,
    Sleep,
    Hibernate,
};

enum class BackgroundMaterial {
    Glass,
    Blur,
    Mocha,
    Clear,
};

struct LookSettings {
    BackgroundMaterial material = BackgroundMaterial::Glass;
    COLORREF backgroundColor = RGB(0x18, 0x18, 0x25);
    int backgroundOpacity = 92;  // 0..100
    bool gradientOverlay = true;
    COLORREF gradientStartColor = RGB(0x89, 0xB4, 0xFA);
    COLORREF gradientEndColor = RGB(0xCB, 0xA6, 0xF7);
    int gradientAreaOpacity = 20;  // 0..100
    COLORREF textColor = RGB(0x89, 0xB4, 0xFA);
    std::wstring fontFamily = L"FiraCode Nerd Font";
    int fontWeight = 500;  // FW_*
    const wchar_t* fontWeightSuffix = L" Med";
    bool openCloseAnimation = true;
};

struct UiStrings {
    const wchar_t* shutdown;
    const wchar_t* restart;
    const wchar_t* sleep;
    const wchar_t* hibernate;
    const wchar_t* genericAction;
    const wchar_t* cancelHint;
};

struct CountdownThreadContext {
    PowerAction action;
    int seconds;
    HANDLE doneEvent;
    ULONGLONG endTick;
    int displayedSeconds;
    bool proceed;
    HHOOK keyboardHook;
    HHOOK mouseHook;
    bool swallowedKeys[256]{};
    bool swallowedMouseButtons[4]{};
    // Overlay open/close animation: 0 none, 1 fading in, 2 fading out.
    int animationPhase = 0;
    ULONGLONG animationStart = 0;
    bool countdownFinished = false;
};

std::atomic<int> g_shutdownCountdownSeconds{5};
std::atomic<int> g_restartCountdownSeconds{5};
std::atomic<int> g_sleepCountdownSeconds{5};
std::atomic<int> g_hibernateCountdownSeconds{5};
std::atomic<bool> g_unloading{false};
std::atomic<HWND> g_countdownWindow{nullptr};
std::atomic<CountdownThreadContext*> g_inputContext{nullptr};

LookSettings g_look;
ULONG_PTR g_gdiplusToken = 0;

HMODULE g_modModule = nullptr;
ATOM g_countdownWindowClassAtom = 0;
wchar_t g_countdownWindowClassName[96]{};
HANDLE g_countdownStopEvent = nullptr;
HANDLE g_countdownIdleEvent = nullptr;
SRWLOCK g_countdownLifecycleLock = SRWLOCK_INIT;

thread_local bool g_bypassHooks = false;

struct BypassHooksGuard {
    bool previous;

    BypassHooksGuard() : previous(g_bypassHooks) {
        g_bypassHooks = true;
    }

    ~BypassHooksGuard() {
        g_bypassHooks = previous;
    }
};

struct CountdownActivityGuard {
    bool active = false;

    bool Begin() {
        AcquireSRWLockExclusive(&g_countdownLifecycleLock);
        if (!g_unloading.load(std::memory_order_acquire)) {
            ResetEvent(g_countdownIdleEvent);
            ResetEvent(g_countdownStopEvent);
            active = true;
        }
        ReleaseSRWLockExclusive(&g_countdownLifecycleLock);
        return active;
    }

    ~CountdownActivityGuard() {
        if (active) {
            SetEvent(g_countdownIdleEvent);
        }
    }
};

using ExitWindowsEx_t = decltype(&ExitWindowsEx);
using InitiateShutdownW_t = decltype(&InitiateShutdownW);
using InitiateSystemShutdownExW_t = decltype(&InitiateSystemShutdownExW);
using SetSystemPowerState_t = decltype(&SetSystemPowerState);
using NtInitiatePowerAction_t = NTSTATUS(NTAPI*)(
    POWER_ACTION, SYSTEM_POWER_STATE, ULONG, BOOLEAN);
using NtSetSystemPowerState_t = NTSTATUS(NTAPI*)(
    POWER_ACTION, SYSTEM_POWER_STATE, ULONG);

ExitWindowsEx_t ExitWindowsEx_Original = nullptr;
InitiateShutdownW_t InitiateShutdownW_Original = nullptr;
InitiateSystemShutdownExW_t InitiateSystemShutdownExW_Original = nullptr;
SetSystemPowerState_t SetSystemPowerState_Original = nullptr;
NtInitiatePowerAction_t NtInitiatePowerAction_Original = nullptr;
NtSetSystemPowerState_t NtSetSystemPowerState_Original = nullptr;

int ClampCountdownSetting(int seconds) {
    return std::clamp(seconds, 0, kMaximumCountdownSeconds);
}

int ClampPercent(int value) {
    return std::clamp(value, 0, 100);
}

bool ColorFromHex(const wchar_t* text, COLORREF* color) {
    if (!text) {
        return false;
    }

    const wchar_t* cursor = text;
    if (*cursor == L'#') {
        cursor++;
    }

    const auto digit = [](wchar_t c) -> int {
        if (c >= L'0' && c <= L'9') return c - L'0';
        if (c >= L'a' && c <= L'f') return 10 + (c - L'a');
        if (c >= L'A' && c <= L'F') return 10 + (c - L'A');
        return -1;
    };

    auto takeTwo = [&]() -> int {
        int high = digit(*cursor);
        if (high < 0) return -1;
        cursor++;
        int low = digit(*cursor);
        if (low < 0) return -1;
        cursor++;
        return (high << 4) | low;
    };

    // #AARRGGBB
    const size_t length = wcslen(cursor);
    int alpha = 255;
    if (length == 8) {
        alpha = takeTwo();
        if (alpha < 0) {
            return false;
        }
    }

    if (length != 6 && length != 8) {
        return false;
    }

    int red = takeTwo();
    int green = takeTwo();
    int blue = takeTwo();
    if (red < 0 || green < 0 || blue < 0 || alpha < 0) {
        return false;
    }

    // Store as COLORREF (0x00BBGGRR); alpha is handled by the opacity setting.
    *color = RGB(red, green, blue);
    return true;
}

void ApplyWeightOption(const wchar_t* option, LookSettings* look) {
    if (wcscmp(option, L"light") == 0) {
        look->fontWeight = 300;
        look->fontWeightSuffix = L" Light";
    } else if (wcscmp(option, L"regular") == 0) {
        look->fontWeight = 400;
        look->fontWeightSuffix = L"";
    } else if (wcscmp(option, L"semibold") == 0) {
        look->fontWeight = 600;
        look->fontWeightSuffix = L" SemBd";
    } else if (wcscmp(option, L"bold") == 0) {
        look->fontWeight = 700;
        look->fontWeightSuffix = L" Bold";
    } else {
        look->fontWeight = 500;
        look->fontWeightSuffix = L" Med";
    }
}

// Bumped on every settings reload so the accent re-applies even when the
// material and alpha did not change (the tint color might have).
std::atomic<DWORD> g_lookGeneration{0};

void LoadSettings() {
    g_shutdownCountdownSeconds.store(
        ClampCountdownSetting(
            Wh_GetIntSetting(L"shutdownCountdownSeconds")),
        std::memory_order_relaxed);
    g_restartCountdownSeconds.store(
        ClampCountdownSetting(
            Wh_GetIntSetting(L"restartCountdownSeconds")),
        std::memory_order_relaxed);
    g_sleepCountdownSeconds.store(
        ClampCountdownSetting(
            Wh_GetIntSetting(L"sleepCountdownSeconds")),
        std::memory_order_relaxed);
    g_hibernateCountdownSeconds.store(
        ClampCountdownSetting(
            Wh_GetIntSetting(L"hibernateCountdownSeconds")),
        std::memory_order_relaxed);

    LookSettings look;

    PCWSTR material = Wh_GetStringSetting(L"look.backgroundMaterial");
    if (wcscmp(material, L"blur") == 0) {
        look.material = BackgroundMaterial::Blur;
    } else if (wcscmp(material, L"mocha") == 0) {
        look.material = BackgroundMaterial::Mocha;
    } else if (wcscmp(material, L"clear") == 0) {
        look.material = BackgroundMaterial::Clear;
    } else {
        look.material = BackgroundMaterial::Glass;
    }
    Wh_FreeStringSetting(material);

    PCWSTR backgroundColor = Wh_GetStringSetting(L"look.backgroundColor");
    if (!ColorFromHex(backgroundColor, &look.backgroundColor)) {
        look.backgroundColor = RGB(0x18, 0x18, 0x25);
    }
    Wh_FreeStringSetting(backgroundColor);

    look.backgroundOpacity = ClampPercent(Wh_GetIntSetting(L"look.backgroundOpacity"));

    look.openCloseAnimation =
        Wh_GetIntSetting(L"look.openCloseAnimation") != 0;

    look.gradientOverlay = Wh_GetIntSetting(L"look.gradientOverlay") != 0;

    PCWSTR gradientStart = Wh_GetStringSetting(L"look.gradientStartColor");
    if (!ColorFromHex(gradientStart, &look.gradientStartColor)) {
        look.gradientStartColor = RGB(0x89, 0xB4, 0xFA);
    }
    Wh_FreeStringSetting(gradientStart);

    PCWSTR gradientEnd = Wh_GetStringSetting(L"look.gradientEndColor");
    if (!ColorFromHex(gradientEnd, &look.gradientEndColor)) {
        look.gradientEndColor = RGB(0xCB, 0xA6, 0xF7);
    }
    Wh_FreeStringSetting(gradientEnd);

    look.gradientAreaOpacity = ClampPercent(Wh_GetIntSetting(L"look.gradientAreaOpacity"));

    PCWSTR textColor = Wh_GetStringSetting(L"font.textColor");
    if (!ColorFromHex(textColor, &look.textColor)) {
        look.textColor = RGB(0x89, 0xB4, 0xFA);
    }
    Wh_FreeStringSetting(textColor);

    PCWSTR fontFamily = Wh_GetStringSetting(L"font.fontFamily");
    look.fontFamily = *fontFamily ? fontFamily : L"FiraCode Nerd Font";
    Wh_FreeStringSetting(fontFamily);

    PCWSTR fontWeight = Wh_GetStringSetting(L"font.fontWeight");
    ApplyWeightOption(*fontWeight ? fontWeight : L"medium", &look);
    Wh_FreeStringSetting(fontWeight);

    g_look = std::move(look);
    g_lookGeneration.fetch_add(1, std::memory_order_relaxed);
}

int GetCountdownSeconds(PowerAction action) {
    switch (action) {
        case PowerAction::Shutdown:
            return g_shutdownCountdownSeconds.load(
                std::memory_order_relaxed);
        case PowerAction::Restart:
            return g_restartCountdownSeconds.load(
                std::memory_order_relaxed);
        case PowerAction::Sleep:
            return g_sleepCountdownSeconds.load(
                std::memory_order_relaxed);
        case PowerAction::Hibernate:
            return g_hibernateCountdownSeconds.load(
                std::memory_order_relaxed);
    }

    return 0;
}

const UiStrings& GetUiStrings() {
    static const UiStrings english{
        .shutdown = L"Shut down",
        .restart = L"Restart",
        .sleep = L"Sleep",
        .hibernate = L"Hibernate",
        .genericAction = L"Power action",
        .cancelHint =
            L"Press any key, click a mouse button, or use the mouse wheel "
            L"to cancel. Mouse movement is ignored.",
    };

    static const UiStrings german{
        .shutdown = L"Herunterfahren",
        .restart = L"Neustart",
        .sleep = L"Standby",
        .hibernate = L"Ruhezustand",
        .genericAction = L"Energieaktion",
        .cancelHint =
            L"Taste, Mausklick oder Mausrad bricht ab. "
            L"Mausbewegungen werden ignoriert.",
    };

    const LANGID language = GetUserDefaultUILanguage();
    return PRIMARYLANGID(language) == LANG_GERMAN ? german : english;
}

const wchar_t* GetActionTitle(PowerAction action) {
    const UiStrings& strings = GetUiStrings();

    switch (action) {
        case PowerAction::Shutdown:
            return strings.shutdown;
        case PowerAction::Restart:
            return strings.restart;
        case PowerAction::Sleep:
            return strings.sleep;
        case PowerAction::Hibernate:
            return strings.hibernate;
    }

    return strings.genericAction;
}

DWORD AbgrTint(COLORREF color, BYTE alpha) {
    return (static_cast<DWORD>(alpha) << 24) |
           (static_cast<DWORD>(GetBValue(color)) << 16) |
           (static_cast<DWORD>(GetGValue(color)) << 8) |
           static_cast<DWORD>(GetRValue(color));
}

void SetOverlayAccent(HWND hWnd, INT accentState, BYTE tintAlpha) {
    struct AccentPolicy {
        INT state;
        INT flags;
        INT gradientColor;
        INT animationId;
    };
    struct WindowCompositionAttribData {
        DWORD attribute;
        PVOID data;
        SIZE_T sizeOfData;
    };

    using SetWindowCompositionAttribute_t =
        BOOL(WINAPI*)(HWND, WindowCompositionAttribData*);
    static auto setWindowCompositionAttribute =
        reinterpret_cast<SetWindowCompositionAttribute_t>(
            GetProcAddress(GetModuleHandleW(L"user32.dll"),
                           "SetWindowCompositionAttribute"));
    if (!setWindowCompositionAttribute) {
        return;
    }

    const INT tint = accentState == kAccentEnableAcrylicBlurBehind
                         ? static_cast<INT>(AbgrTint(g_look.backgroundColor,
                                                     tintAlpha))
                         : 0;

    AccentPolicy policy{accentState, accentState ? 2 : 0, tint, 0};
    WindowCompositionAttribData data{kWcaAccentPolicy, &policy,
                                     sizeof(policy)};
    setWindowCompositionAttribute(hWnd, &data);
}

// The material is the DWM accent itself: acrylic glass or frost compositing
// behind the layered surface, tinted through the accent's gradient color so
// the blur shows through. alphaScale (0-255) fades the tint together with
// the surface pixels during the open and close animation.
void ApplyOverlayMaterial(HWND hWnd, BYTE alphaScale) {
    struct MaterialState {
        DWORD generation;
        int material;
        int alpha;
    };
    static MaterialState applied{0, -1, -1};

    const DWORD generation = g_lookGeneration.load(std::memory_order_relaxed);
    const int material = static_cast<int>(g_look.material);
    const int alpha = g_look.backgroundOpacity * alphaScale / 255;
    if (applied.generation == generation && applied.material == material &&
        applied.alpha == alpha) {
        return;
    }
    applied = {generation, material, alpha};

    switch (g_look.material) {
        case BackgroundMaterial::Glass:
            SetOverlayAccent(hWnd, kAccentEnableAcrylicBlurBehind,
                             static_cast<BYTE>(alpha));
            break;

        case BackgroundMaterial::Blur:
            SetOverlayAccent(hWnd, kAccentEnableBlurBehind, 0);
            break;

        default:
            SetOverlayAccent(hWnd, kAccentDisabled, 0);
            break;
    }
}

void ConfigureOverlayWindow(HWND hWnd) {
    using DwmSetWindowAttribute_t =
        HRESULT(WINAPI*)(HWND, DWORD, LPCVOID, DWORD);
    static auto dwmSetWindowAttribute =
        reinterpret_cast<DwmSetWindowAttribute_t>(
            reinterpret_cast<void*>(GetProcAddress(
                GetModuleHandleW(L"dwmapi.dll"), "DwmSetWindowAttribute")));

    if (dwmSetWindowAttribute) {
        const DWORD noNonClientRendering = 1;  // DWMNCRP_DISABLED.
        dwmSetWindowAttribute(hWnd, 2, &noNonClientRendering,
                              sizeof(noNonClientRendering));
        const BOOL noTransitions = TRUE;
        dwmSetWindowAttribute(hWnd, 3, &noTransitions,
                              sizeof(noTransitions));
        const COLORREF noBorder = 0xFFFFFFFE;  // DWMWA_COLOR_NONE.
        dwmSetWindowAttribute(hWnd, 34, &noBorder, sizeof(noBorder));
        const DWORD noBackdrop = 1;  // DWMSBT_NONE.
        dwmSetWindowAttribute(hWnd, 38, &noBackdrop, sizeof(noBackdrop));
        const DWORD doNotRound = 1;  // DWMWCP_DONOTROUND.
        dwmSetWindowAttribute(hWnd, 33, &doNotRound, sizeof(doNotRound));
    }
    ApplyOverlayMaterial(hWnd, 255);
}

void EnsureCountdownAlwaysOnTop(HWND hWnd) {
    if (!IsWindow(hWnd)) {
        return;
    }

    SetWindowPos(
        hWnd,
        HWND_TOPMOST,
        0,
        0,
        0,
        0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE |
            SWP_NOOWNERZORDER | SWP_SHOWWINDOW);
}

void StartFadeOut(HWND hWnd, CountdownThreadContext* context) {
    context->animationPhase = 2;
    context->animationStart = GetTickCount64();
    SetTimer(hWnd, kAnimationTimerId, kAnimationTimerIntervalMs, nullptr);
}

void CancelCountdown(HWND hWnd) {
    auto* context = reinterpret_cast<CountdownThreadContext*>(
        GetWindowLongPtrW(hWnd, GWLP_USERDATA));
    if (!context) {
        return;
    }

    context->proceed = false;

    if (context->animationPhase == 2) {
        return;  // Already fading out; the fade destroys the window.
    }

    if (g_look.openCloseAnimation) {
        StartFadeOut(hWnd, context);
        return;
    }

    DestroyWindow(hWnd);
}

bool PostCancelToCountdown() {
    HWND hWnd = g_countdownWindow.load(std::memory_order_acquire);
    return hWnd && IsWindow(hWnd) &&
           PostMessageW(hWnd, kCancelCountdownMessage, 0, 0);
}

bool IsKeyboardReleaseMessage(WPARAM wParam) {
    return wParam == WM_KEYUP || wParam == WM_SYSKEYUP;
}

bool IsKeyboardPressMessage(WPARAM wParam) {
    return wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN;
}

bool IsMouseReleaseMessage(WPARAM message) {
    switch (message) {
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
            return true;
        default:
            return false;
    }
}

bool IsMousePressMessage(WPARAM message) {
    switch (message) {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
            return true;
        default:
            return false;
    }
}

int GetMouseButtonIndex(WPARAM message) {
    switch (message) {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            return 0;
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            return 1;
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
            return 2;
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
            return 3;
        default:
            return -1;
    }
}

LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    auto* context = g_inputContext.load(std::memory_order_acquire);
    if (code == HC_ACTION && context) {
        const auto* keyboard = reinterpret_cast<const KBDLLHOOKSTRUCT*>(lParam);
        const unsigned int vk = keyboard ? keyboard->vkCode : 0;
        if (vk < std::size(context->swallowedKeys)) {
            if (IsKeyboardPressMessage(wParam) && PostCancelToCountdown()) {
                context->swallowedKeys[vk] = true;
                return 1;
            }
            if (IsKeyboardReleaseMessage(wParam) && context->swallowedKeys[vk]) {
                context->swallowedKeys[vk] = false;
                return 1;
            }
        }
    }
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int code, WPARAM wParam, LPARAM lParam) {
    auto* context = g_inputContext.load(std::memory_order_acquire);
    if (code == HC_ACTION && context) {
        const int buttonIndex = GetMouseButtonIndex(wParam);
        if (IsMousePressMessage(wParam) && PostCancelToCountdown()) {
            if (buttonIndex >= 0) context->swallowedMouseButtons[buttonIndex] = true;
            return 1;
        }
        if (IsMouseReleaseMessage(wParam) && buttonIndex >= 0 &&
            context->swallowedMouseButtons[buttonIndex]) {
            context->swallowedMouseButtons[buttonIndex] = false;
            return 1;
        }
    }
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

bool EnsureGdiPlus() {
    if (g_gdiplusToken) {
        return true;
    }

    Gdiplus::GdiplusStartupInput startupInput;
    return Gdiplus::GdiplusStartup(&g_gdiplusToken, &startupInput, nullptr) ==
           Gdiplus::Ok;
}

void ShutdownGdiPlus() {
    if (g_gdiplusToken) {
        Gdiplus::GdiplusShutdown(g_gdiplusToken);
        g_gdiplusToken = 0;
    }
}

Gdiplus::Font* CreateOverlayFont(const std::wstring& faceName, float pixels) {
    Gdiplus::FontFamily family(faceName.c_str());
    if (family.GetLastStatus() != Gdiplus::Ok) {
        return nullptr;
    }

    auto* font = new Gdiplus::Font(
        &family, pixels, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    if (font->GetLastStatus() == Gdiplus::Ok) {
        return font;
    }

    delete font;
    return nullptr;
}

// Nerd fonts expose weights as their own families ("... Med", "... SemBd"),
// so the weight option appends the matching suffix. Plain families and
// Segoe UI stay as fallbacks.
Gdiplus::Font* CreateUiFont(float pixels) {
    std::wstring face = g_look.fontFamily;
    if (auto* font = CreateOverlayFont(face + g_look.fontWeightSuffix,
                                       pixels)) {
        return font;
    }

    if (g_look.fontWeightSuffix && *g_look.fontWeightSuffix) {
        if (auto* font = CreateOverlayFont(face, pixels)) {
            return font;
        }
    }

    if (auto* font = CreateOverlayFont(L"Segoe UI", pixels)) {
        return font;
    }

    return nullptr;
}

Gdiplus::Brush* CreateTextBrush(const Gdiplus::RectF& textBlock,
                                bool gradientOverlay) {
    if (!gradientOverlay) {
        return new Gdiplus::SolidBrush(Gdiplus::Color(
            255, GetRValue(g_look.textColor), GetGValue(g_look.textColor),
            GetBValue(g_look.textColor)));
    }

    return new Gdiplus::LinearGradientBrush(
        textBlock,
        Gdiplus::Color(255, GetRValue(g_look.gradientStartColor),
                       GetGValue(g_look.gradientStartColor),
                       GetBValue(g_look.gradientStartColor)),
        Gdiplus::Color(255, GetRValue(g_look.gradientEndColor),
                       GetGValue(g_look.gradientEndColor),
                       GetBValue(g_look.gradientEndColor)),
        90.0f, TRUE);
}

// UpdateLayeredWindow expects premultiplied alpha; GDI+ writes straight
// alpha, so multiply the channels once after drawing.
void PremultiplyPixels(BYTE* bits, int width, int height) {
    for (int y = 0; y < height; y++) {
        BYTE* row = bits + static_cast<size_t>(y) * width * 4;
        for (int x = 0; x < width; x++) {
            BYTE* pixel = row + x * 4;
            const BYTE alpha = pixel[3];
            if (alpha == 255) {
                continue;
            }
            if (alpha == 0) {
                pixel[0] = pixel[1] = pixel[2] = 0;
                continue;
            }
            pixel[0] = static_cast<BYTE>(pixel[0] * alpha / 255);
            pixel[1] = static_cast<BYTE>(pixel[1] * alpha / 255);
            pixel[2] = static_cast<BYTE>(pixel[2] * alpha / 255);
        }
    }
}

Gdiplus::RectF ZoomRectAroundCenter(const Gdiplus::RectF& rect,
                                    float widthF,
                                    float heightF,
                                    float zoom) {
    if (zoom == 1.0f) {
        return rect;
    }

    const float centerX = widthF / 2.0f;
    const float centerY = heightF / 2.0f;
    return Gdiplus::RectF(
        centerX + (rect.X - centerX) * zoom,
        centerY + (rect.Y - centerY) * zoom,
        rect.Width * zoom,
        rect.Height * zoom);
}

void PaintCountdownOverlay(HWND hWnd,
                           CountdownThreadContext* context,
                           float zoom = 1.0f,
                           BYTE forcedAlpha = 255) {
    if (!IsWindow(hWnd) || !EnsureGdiPlus()) {
        return;
    }

    RECT clientRect;
    if (!GetClientRect(hWnd, &clientRect)) {
        return;
    }

    const int width = clientRect.right - clientRect.left;
    const int height = clientRect.bottom - clientRect.top;
    if (width <= 0 || height <= 0) {
        return;
    }

    HDC windowDc = GetDC(hWnd);
    if (!windowDc) {
        return;
    }

    HDC memoryDc = CreateCompatibleDC(windowDc);
    if (!memoryDc) {
        ReleaseDC(hWnd, windowDc);
        return;
    }

    BITMAPINFO bitmapInfo{};
    bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = -height;  // Top-down.
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    HBITMAP bitmap = CreateDIBSection(windowDc, &bitmapInfo, DIB_RGB_COLORS,
                                      &bits, nullptr, 0);
    if (!bitmap || !bits) {
        if (bitmap) {
            DeleteObject(bitmap);
        }
        DeleteDC(memoryDc);
        ReleaseDC(hWnd, windowDc);
        return;
    }

    HGDIOBJ oldBitmap = SelectObject(memoryDc, bitmap);
    memset(bits, 0, static_cast<size_t>(width) * 4 * height);

    UINT dpi = GetDpiForWindow(hWnd);
    if (!dpi) {
        dpi = 96;
    }
    const float scale = dpi / 96.0f;
    // The original design sizes its text in points; GDI+ fonts take the em
    // size in pixels (1 pt = dpi/72 px).
    const float pointSize = dpi / 72.0f;
    const float widthF = static_cast<float>(width);
    const float heightF = static_cast<float>(height);
    const float centerY = heightF / 2.0f;

    {
        Gdiplus::Graphics graphics(memoryDc);
        graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
        graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
        graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
        graphics.SetPageUnit(Gdiplus::UnitPixel);
        graphics.SetTextRenderingHint(
            Gdiplus::TextRenderingHintAntiAliasGridFit);

        // Base background: a solid fill for Mocha only. Glass and blur get
        // the real DWM material (the accent compositing behind the layered
        // surface); the surface stays clear so the blur shows through, with
        // the glass tint carried by the accent's gradient color.
        if (g_look.material == BackgroundMaterial::Mocha) {
            Gdiplus::SolidBrush background(Gdiplus::Color(
                255, GetRValue(g_look.backgroundColor),
                GetGValue(g_look.backgroundColor),
                GetBValue(g_look.backgroundColor)));
            graphics.FillRectangle(&background, 0, 0, width, height);
        }

        // Gradient wash over the whole area.
        if (g_look.gradientOverlay && g_look.gradientAreaOpacity > 0) {
            const BYTE alpha = static_cast<BYTE>(
                g_look.gradientAreaOpacity * 255 / 100);
            const BYTE fadedAlpha = static_cast<BYTE>(alpha * 0.55f);
            Gdiplus::LinearGradientBrush wash(
                Gdiplus::RectF(0.0f, 0.0f, widthF, heightF),
                Gdiplus::Color(alpha, GetRValue(g_look.gradientStartColor),
                               GetGValue(g_look.gradientStartColor),
                               GetBValue(g_look.gradientStartColor)),
                Gdiplus::Color(fadedAlpha, GetRValue(g_look.gradientEndColor),
                               GetGValue(g_look.gradientEndColor),
                               GetBValue(g_look.gradientEndColor)),
                90.0f, TRUE);
            graphics.FillRectangle(&wash, 0, 0, width, height);
        }

        // One gradient flows through the whole text block: number, title,
        // hint.
        const Gdiplus::RectF textBlock = ZoomRectAroundCenter(
            Gdiplus::RectF(0.0f, centerY - MulDiv(120, dpi, 96), widthF,
                           290.0f * scale),
            widthF, heightF, zoom);
        Gdiplus::Brush* textBrush =
            CreateTextBrush(textBlock, g_look.gradientOverlay);
        if (textBrush) {
            Gdiplus::StringFormat centered;
            centered.SetAlignment(Gdiplus::StringAlignmentCenter);
            centered.SetLineAlignment(Gdiplus::StringAlignmentCenter);
            centered.SetFormatFlags(
                Gdiplus::StringFormatFlagsNoFitBlackBox |
                Gdiplus::StringFormatFlagsMeasureTrailingSpaces);

            Gdiplus::Font* numberFont = CreateUiFont(96.0f * pointSize);
            Gdiplus::Font* titleFont = CreateUiFont(28.0f * pointSize);
            Gdiplus::Font* infoFont = CreateUiFont(16.0f * pointSize);

            wchar_t numberText[16];
            swprintf(numberText, std::size(numberText), L"%d",
                     context ? context->displayedSeconds : 0);

            const Gdiplus::RectF numberRect = ZoomRectAroundCenter(
                Gdiplus::RectF(0.0f, centerY - 120.0f * scale, widthF,
                               140.0f * scale),
                widthF, heightF, zoom);
            const Gdiplus::RectF titleRect = ZoomRectAroundCenter(
                Gdiplus::RectF(0.0f, centerY + 20.0f * scale, widthF,
                               60.0f * scale),
                widthF, heightF, zoom);
            const Gdiplus::RectF infoRect = ZoomRectAroundCenter(
                Gdiplus::RectF(40.0f * scale, centerY + 95.0f * scale,
                               widthF - 80.0f * scale, 75.0f * scale),
                widthF, heightF, zoom);

            if (numberFont) {
                graphics.DrawString(numberText, -1, numberFont, numberRect,
                                    &centered, textBrush);
            }

            if (titleFont) {
                const wchar_t* title =
                    context ? GetActionTitle(context->action)
                            : GetUiStrings().genericAction;
                graphics.DrawString(title, -1, titleFont, titleRect,
                                    &centered, textBrush);
            }

            if (infoFont) {
                graphics.DrawString(GetUiStrings().cancelHint, -1, infoFont,
                                    infoRect, &centered, textBrush);
            }

            delete numberFont;
            delete titleFont;
            delete infoFont;
            delete textBrush;
        }
    }

    PremultiplyPixels(static_cast<BYTE*>(bits), width, height);

    SIZE size{width, height};
    POINT source{0, 0};
    BLENDFUNCTION blend{
        AC_SRC_OVER,
        0,
        forcedAlpha,
        AC_SRC_ALPHA,
    };

    const BOOL updated = UpdateLayeredWindow(hWnd, windowDc, nullptr, &size,
                                             memoryDc, &source, 0, &blend,
                                             ULW_ALPHA);
    if (!updated) {
        Wh_Log(L"UpdateLayeredWindow failed: %lu", GetLastError());
    }

    // The material's tint follows the same fade the surface pixels do.
    ApplyOverlayMaterial(hWnd, forcedAlpha);

    SelectObject(memoryDc, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(memoryDc);
    ReleaseDC(hWnd, windowDc);
}

LRESULT CALLBACK CountdownWindowProc(HWND hWnd,
                                     UINT message,
                                     WPARAM wParam,
                                     LPARAM lParam) {
    auto* context = reinterpret_cast<CountdownThreadContext*>(
        GetWindowLongPtrW(hWnd, GWLP_USERDATA));

    if (message == WM_NCCREATE) {
        auto* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
        context = static_cast<CountdownThreadContext*>(create->lpCreateParams);
        SetWindowLongPtrW(hWnd, GWLP_USERDATA,
                          reinterpret_cast<LONG_PTR>(context));
    }

    switch (message) {
        case WM_CREATE:
            SetTimer(hWnd, kCountdownTimerId,
                     kCountdownTimerIntervalMs, nullptr);
            return 0;

        case WM_TIMER:
            if (wParam == kCountdownTimerId) {
                EnsureCountdownAlwaysOnTop(hWnd);

                if (!context || context->countdownFinished) {
                    return 0;
                }

                const ULONGLONG now = GetTickCount64();
                if (now >= context->endTick) {
                    context->displayedSeconds = 0;
                    context->countdownFinished = true;
                    context->proceed = true;

                    if (g_look.openCloseAnimation) {
                        StartFadeOut(hWnd, context);
                        return 0;
                    }

                    DestroyWindow(hWnd);
                    return 0;
                }

                const ULONGLONG remainingMs = context->endTick - now;
                const int remainingSeconds =
                    static_cast<int>((remainingMs + 999) / 1000);

                if (remainingSeconds != context->displayedSeconds) {
                    context->displayedSeconds = remainingSeconds;
                    PaintCountdownOverlay(hWnd, context);
                }
                return 0;
            }

            if (wParam == kAnimationTimerId) {
                if (!context) {
                    KillTimer(hWnd, kAnimationTimerId);
                    return 0;
                }

                const ULONGLONG now = GetTickCount64();
                if (context->animationPhase == 1) {
                    const float progress = std::min(
                        1.0f,
                        static_cast<float>(now - context->animationStart) /
                            kFadeInMs);
                    const float eased =
                        1.0f - (1.0f - progress) * (1.0f - progress) *
                                   (1.0f - progress);
                    PaintCountdownOverlay(
                        hWnd, context, 1.05f - 0.05f * eased,
                        static_cast<BYTE>(255.0f * eased));
                    if (progress >= 1.0f) {
                        context->animationPhase = 0;
                        KillTimer(hWnd, kAnimationTimerId);
                    }
                } else if (context->animationPhase == 2) {
                    const float progress = std::min(
                        1.0f,
                        static_cast<float>(now - context->animationStart) /
                            kFadeOutMs);
                    const float eased = progress * progress;
                    PaintCountdownOverlay(
                        hWnd, context, 1.0f + 0.02f * eased,
                        static_cast<BYTE>(255.0f * (1.0f - eased)));
                    if (progress >= 1.0f) {
                        context->animationPhase = 0;
                        KillTimer(hWnd, kAnimationTimerId);
                        DestroyWindow(hWnd);
                    }
                } else {
                    KillTimer(hWnd, kAnimationTimerId);
                }
                return 0;
            }
            break;

        case kCancelCountdownMessage:
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
        case WM_POINTERDOWN:
            CancelCountdown(hWnd);
            return 0;

        // WM_MOUSEMOVE and WM_POINTERUPDATE are deliberately ignored.

        case WM_WINDOWPOSCHANGING: {
            auto* windowPos = reinterpret_cast<WINDOWPOS*>(lParam);
            if (windowPos) {
                windowPos->hwndInsertAfter = HWND_TOPMOST;
                windowPos->flags &= ~SWP_NOZORDER;
                windowPos->flags |= SWP_NOOWNERZORDER;
            }
            break;
        }

        case WM_CLOSE:
            CancelCountdown(hWnd);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT paint;
            if (HDC hdc = BeginPaint(hWnd, &paint)) {
                EndPaint(hWnd, &paint);
            }
            if (context) {
                PaintCountdownOverlay(hWnd, context);
            }
            return 0;
        }

        case WM_ERASEBKGND:
            return 1;

        case WM_DESTROY:
            KillTimer(hWnd, kCountdownTimerId);
            KillTimer(hWnd, kAnimationTimerId);
            if (g_countdownWindow.load(std::memory_order_relaxed) == hWnd) {
                g_countdownWindow.store(nullptr, std::memory_order_release);
            }
            return 0;
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);
}

RECT GetPrimaryMonitorRectangle() {
    POINT primaryMonitorPoint{0, 0};
    HMONITOR primaryMonitor = MonitorFromPoint(
        primaryMonitorPoint, MONITOR_DEFAULTTOPRIMARY);

    MONITORINFO monitorInfo{
        .cbSize = sizeof(monitorInfo),
    };

    if (primaryMonitor && GetMonitorInfoW(primaryMonitor, &monitorInfo)) {
        return monitorInfo.rcMonitor;
    }

    return RECT{
        .left = 0,
        .top = 0,
        .right = GetSystemMetrics(SM_CXSCREEN),
        .bottom = GetSystemMetrics(SM_CYSCREEN),
    };
}

void InstallCountdownInputHooks(CountdownThreadContext* context) {
    context->keyboardHook = SetWindowsHookExW(
        WH_KEYBOARD_LL, LowLevelKeyboardProc, g_modModule, 0);
    if (!context->keyboardHook) {
        Wh_Log(L"SetWindowsHookExW(WH_KEYBOARD_LL) failed: %lu",
               GetLastError());
    }

    context->mouseHook = SetWindowsHookExW(
        WH_MOUSE_LL, LowLevelMouseProc, g_modModule, 0);
    if (!context->mouseHook) {
        Wh_Log(L"SetWindowsHookExW(WH_MOUSE_LL) failed: %lu",
               GetLastError());
    }
}

void UninstallCountdownInputHooks(CountdownThreadContext* context) {
    if (context->keyboardHook) {
        UnhookWindowsHookEx(context->keyboardHook);
        context->keyboardHook = nullptr;
    }

    if (context->mouseHook) {
        UnhookWindowsHookEx(context->mouseHook);
        context->mouseHook = nullptr;
    }
}

DWORD WINAPI CountdownThreadProc(void* parameter) {
    auto* context = static_cast<CountdownThreadContext*>(parameter);
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    context->proceed = true;  // Fail open until the UI is fully established.

    if (WaitForSingleObject(g_countdownStopEvent, 0) == WAIT_OBJECT_0 ||
        g_unloading.load(std::memory_order_acquire)) {
        context->proceed = false;
        SetEvent(context->doneEvent);
        return 0;
    }

    EnsureGdiPlus();

    const RECT monitorRect = GetPrimaryMonitorRectangle();
    const int width = monitorRect.right - monitorRect.left;
    const int height = monitorRect.bottom - monitorRect.top;

    context->endTick =
        GetTickCount64() + static_cast<ULONGLONG>(context->seconds) * 1000;
    context->displayedSeconds = context->seconds;
    context->proceed = false;
    context->keyboardHook = nullptr;
    context->mouseHook = nullptr;

    HWND hWnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        g_countdownWindowClassName,
        L"Power action countdown",
        WS_POPUP,
        monitorRect.left,
        monitorRect.top,
        width,
        height,
        nullptr,
        nullptr,
        g_modModule,
        context);

    if (!hWnd) {
        Wh_Log(L"CreateWindowExW failed: %lu", GetLastError());
        context->proceed = true;
        ShutdownGdiPlus();
        SetEvent(context->doneEvent);
        return 0;
    }

    ConfigureOverlayWindow(hWnd);

    if (g_look.openCloseAnimation) {
        // First frame is fully transparent; the fade-in repaints from the
        // animation timer right after the window shows.
        PaintCountdownOverlay(hWnd, context, 1.05f, 0);
        context->animationPhase = 1;
        context->animationStart = GetTickCount64();
    } else {
        PaintCountdownOverlay(hWnd, context);
    }

    g_countdownWindow.store(hWnd, std::memory_order_release);
    g_inputContext.store(context, std::memory_order_release);
    InstallCountdownInputHooks(context);

    ShowWindow(hWnd, SW_SHOW);
    SetWindowPos(hWnd, HWND_TOPMOST, monitorRect.left, monitorRect.top,
                 width, height, SWP_SHOWWINDOW | SWP_NOACTIVATE);
    UpdateWindow(hWnd);

    if (context->animationPhase == 1) {
        SetTimer(hWnd, kAnimationTimerId, kAnimationTimerIntervalMs, nullptr);
    }

    // Don't merge this thread's input queue with another process. The normal
    // foreground request is sufficient on shell-initiated power actions, and
    // the low-level input hooks provide cancellation even if activation fails.
    SetForegroundWindow(hWnd);
    SetActiveWindow(hWnd);
    SetFocus(hWnd);

    Wh_Log(L"Countdown foreground activation: %ls",
           GetForegroundWindow() == hWnd ? L"successful" : L"failed");

    bool running = true;
    while (running && IsWindow(hWnd)) {
        const DWORD waitResult = MsgWaitForMultipleObjects(
            1, &g_countdownStopEvent, FALSE, INFINITE, QS_ALLINPUT);

        if (waitResult == WAIT_OBJECT_0) {
            context->proceed = false;
            if (IsWindow(hWnd)) {
                DestroyWindow(hWnd);
            }
            break;
        }

        if (waitResult != WAIT_OBJECT_0 + 1) {
            Wh_Log(L"Countdown thread wait failed: %lu", GetLastError());
            context->proceed = true;
            if (IsWindow(hWnd)) {
                DestroyWindow(hWnd);
            }
            break;
        }

        MSG message;
        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageW(&message);

            if (!IsWindow(hWnd)) {
                running = false;
                break;
            }
        }
    }

    UninstallCountdownInputHooks(context);
    g_inputContext.store(nullptr, std::memory_order_release);

    if (IsWindow(hWnd)) {
        DestroyWindow(hWnd);
    }

    g_countdownWindow.store(nullptr, std::memory_order_release);
    ShutdownGdiPlus();
    SetEvent(context->doneEvent);
    return 0;
}

HANDLE AcquireCountdownMutex() {
    wchar_t mutexName[96];
    swprintf(mutexName, std::size(mutexName),
             L"Local\\Windhawk_%ls", WH_MOD_ID);

    HANDLE mutex = CreateMutexW(nullptr, FALSE, mutexName);
    if (!mutex) {
        return nullptr;
    }

    const DWORD waitResult = WaitForSingleObject(mutex, 0);
    if (waitResult != WAIT_OBJECT_0 && waitResult != WAIT_ABANDONED) {
        CloseHandle(mutex);
        return INVALID_HANDLE_VALUE;
    }

    return mutex;
}

void ReleaseCountdownMutex(HANDLE mutex) {
    if (mutex && mutex != INVALID_HANDLE_VALUE) {
        ReleaseMutex(mutex);
        CloseHandle(mutex);
    }
}

bool WaitForCountdownWithoutPumpingPostedMessages(HANDLE doneEvent) {
    HANDLE handles[] = {doneEvent};
    for (;;) {
        DWORD index = 0;
        HRESULT hr = CoWaitForMultipleHandles(
            COWAIT_DISPATCH_CALLS, INFINITE, std::size(handles), handles, &index);
        if (SUCCEEDED(hr) && index == 0) return true;
        if (hr == RPC_S_CALLPENDING) continue;
        Wh_Log(L"CoWaitForMultipleHandles failed: 0x%08X",
               static_cast<unsigned int>(hr));
        return false;
    }
}

bool RunCountdown(PowerAction action, int seconds) {
    HANDLE mutex = AcquireCountdownMutex();
    if (mutex == INVALID_HANDLE_VALUE) {
        Wh_Log(L"A countdown is already active; blocking duplicate action");
        return false;
    }

    if (!mutex) {
        Wh_Log(L"CreateMutexW failed: %lu; allowing power action",
               GetLastError());
        return true;
    }

    CountdownActivityGuard activity;
    if (!activity.Begin()) {
        ReleaseCountdownMutex(mutex);
        return true;
    }

    HANDLE doneEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!doneEvent) {
        Wh_Log(L"CreateEventW failed: %lu; allowing power action",
               GetLastError());
        ReleaseCountdownMutex(mutex);
        return true;
    }

    CountdownThreadContext context{
        .action = action,
        .seconds = seconds,
        .doneEvent = doneEvent,
        .endTick = 0,
        .displayedSeconds = seconds,
        .proceed = true,
        .keyboardHook = nullptr,
        .mouseHook = nullptr,
    };

    HANDLE thread = CreateThread(
        nullptr, 0, CountdownThreadProc, &context, 0, nullptr);
    if (!thread) {
        Wh_Log(L"CreateThread failed: %lu; allowing power action",
               GetLastError());
        CloseHandle(doneEvent);
        ReleaseCountdownMutex(mutex);
        return true;
    }

    const bool waited =
        WaitForCountdownWithoutPumpingPostedMessages(doneEvent);
    if (!waited) {
        SetEvent(g_countdownStopEvent);
    }

    // The event reports that cleanup has finished; waiting for the thread
    // handle additionally guarantees that no countdown-thread instruction is
    // still executing in the mod DLL.
    WaitForSingleObject(thread, INFINITE);

    CloseHandle(thread);
    CloseHandle(doneEvent);
    ReleaseCountdownMutex(mutex);

    const bool proceed = waited ? context.proceed : true;
    Wh_Log(L"Countdown result: %ls", proceed ? L"execute" : L"cancel");
    return proceed;
}

bool IsLocalMachineName(const wchar_t* machineName) {
    if (!machineName || !*machineName) {
        return true;
    }

    while (*machineName == L'\\') {
        machineName++;
    }

    wchar_t localName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD localNameLength = std::size(localName);
    if (!GetComputerNameW(localName, &localNameLength)) {
        return false;
    }

    return _wcsicmp(machineName, localName) == 0 ||
           _wcsicmp(machineName, L"localhost") == 0 ||
           _wcsicmp(machineName, L".") == 0;
}

bool ConfirmAction(PowerAction action, const wchar_t* apiName) {
    if (g_unloading.load(std::memory_order_acquire)) {
        return true;
    }

    const int seconds = GetCountdownSeconds(action);
    if (seconds == 0) {
        Wh_Log(L"Intercepted %ls in process %lu; countdown disabled",
               apiName, GetCurrentProcessId());
        return true;
    }

    Wh_Log(L"Intercepted %ls in process %lu; countdown: %d seconds",
           apiName, GetCurrentProcessId(), seconds);
    return RunCountdown(action, seconds);
}

BOOL WINAPI ExitWindowsEx_Hook(UINT flags, DWORD reason) {
    if (g_bypassHooks || g_unloading.load(std::memory_order_acquire)) {
        return ExitWindowsEx_Original(flags, reason);
    }

    constexpr UINT kShutdownFlags =
        EWX_SHUTDOWN | EWX_POWEROFF | EWX_HYBRID_SHUTDOWN;

    const bool isShutdown = (flags & kShutdownFlags) != 0;
    const bool isRestart = (flags & EWX_REBOOT) != 0;

    PowerAction action{};
    bool handledAction = false;

    if (isRestart) {
        action = PowerAction::Restart;
        handledAction = true;
    } else if (isShutdown) {
        action = PowerAction::Shutdown;
        handledAction = true;
    }

    if (handledAction && !ConfirmAction(action, L"ExitWindowsEx")) {
        SetLastError(ERROR_CANCELLED);
        return FALSE;
    }

    BypassHooksGuard bypass;
    return ExitWindowsEx_Original(flags, reason);
}

DWORD WINAPI InitiateShutdownW_Hook(LPWSTR machineName,
                                    LPWSTR message,
                                    DWORD gracePeriod,
                                    DWORD shutdownFlags,
                                    DWORD reason) {
    if (g_bypassHooks || g_unloading.load(std::memory_order_acquire)) {
        return InitiateShutdownW_Original(machineName, message, gracePeriod,
                                          shutdownFlags, reason);
    }

    const bool isRestart = (shutdownFlags & SHUTDOWN_RESTART) != 0;

    if (IsLocalMachineName(machineName)) {
        const PowerAction action = isRestart
                                       ? PowerAction::Restart
                                       : PowerAction::Shutdown;
        if (!ConfirmAction(action, L"InitiateShutdownW")) {
            return ERROR_CANCELLED;
        }
    }

    BypassHooksGuard bypass;
    return InitiateShutdownW_Original(machineName, message, gracePeriod,
                                      shutdownFlags, reason);
}

BOOL WINAPI InitiateSystemShutdownExW_Hook(LPWSTR machineName,
                                           LPWSTR message,
                                           DWORD timeout,
                                           BOOL forceAppsClosed,
                                           BOOL rebootAfterShutdown,
                                           DWORD reason) {
    if (g_bypassHooks || g_unloading.load(std::memory_order_acquire)) {
        return InitiateSystemShutdownExW_Original(
            machineName, message, timeout, forceAppsClosed,
            rebootAfterShutdown, reason);
    }

    if (IsLocalMachineName(machineName)) {
        const PowerAction action = rebootAfterShutdown
                                       ? PowerAction::Restart
                                       : PowerAction::Shutdown;
        if (!ConfirmAction(action, L"InitiateSystemShutdownExW")) {
            SetLastError(ERROR_CANCELLED);
            return FALSE;
        }
    }

    BypassHooksGuard bypass;
    return InitiateSystemShutdownExW_Original(
        machineName, message, timeout, forceAppsClosed,
        rebootAfterShutdown, reason);
}

BOOL WINAPI SetSystemPowerState_Hook(BOOL suspend, BOOL force) {
    if (g_bypassHooks || g_unloading.load(std::memory_order_acquire)) {
        return SetSystemPowerState_Original(suspend, force);
    }

    const PowerAction action = suspend
                                   ? PowerAction::Sleep
                                   : PowerAction::Hibernate;
    if (!ConfirmAction(action, L"SetSystemPowerState")) {
        SetLastError(ERROR_CANCELLED);
        return FALSE;
    }

    BypassHooksGuard bypass;
    return SetSystemPowerState_Original(suspend, force);
}

bool MapNativePowerAction(POWER_ACTION systemAction,
                          SYSTEM_POWER_STATE minimumState,
                          PowerAction* action) {
    switch (systemAction) {
        case PowerActionSleep:
            *action = minimumState == PowerSystemHibernate
                          ? PowerAction::Hibernate
                          : PowerAction::Sleep;
            return true;

        case PowerActionHibernate:
            *action = PowerAction::Hibernate;
            return true;

        case PowerActionShutdownReset:
            *action = PowerAction::Restart;
            return true;

        case PowerActionShutdown:
        case PowerActionShutdownOff:
            *action = PowerAction::Shutdown;
            return true;

        default:
            return false;
    }
}

NTSTATUS NTAPI NtInitiatePowerAction_Hook(POWER_ACTION systemAction,
                                          SYSTEM_POWER_STATE minimumState,
                                          ULONG flags,
                                          BOOLEAN asynchronous) {
    if (g_bypassHooks || g_unloading.load(std::memory_order_acquire)) {
        return NtInitiatePowerAction_Original(systemAction, minimumState,
                                              flags, asynchronous);
    }

    PowerAction action{};
    if (MapNativePowerAction(systemAction, minimumState, &action) &&
        !ConfirmAction(action, L"NtInitiatePowerAction")) {
        return kStatusCancelled;
    }

    BypassHooksGuard bypass;
    return NtInitiatePowerAction_Original(systemAction, minimumState,
                                          flags, asynchronous);
}

NTSTATUS NTAPI NtSetSystemPowerState_Hook(POWER_ACTION systemAction,
                                          SYSTEM_POWER_STATE minimumState,
                                          ULONG flags) {
    if (g_bypassHooks || g_unloading.load(std::memory_order_acquire)) {
        return NtSetSystemPowerState_Original(systemAction, minimumState,
                                              flags);
    }

    PowerAction action{};
    if (MapNativePowerAction(systemAction, minimumState, &action) &&
        !ConfirmAction(action, L"NtSetSystemPowerState")) {
        return kStatusCancelled;
    }

    BypassHooksGuard bypass;
    return NtSetSystemPowerState_Original(systemAction, minimumState, flags);
}

bool InitializeModModuleHandle() {
    return GetModuleHandleExW(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        reinterpret_cast<LPCWSTR>(&CountdownWindowProc),
        &g_modModule) != FALSE;
}

bool RegisterCountdownWindowClass() {
    swprintf(g_countdownWindowClassName,
             std::size(g_countdownWindowClassName),
             L"Windhawk_%ls_%lu",
             WH_MOD_ID,
             GetCurrentProcessId());

    WNDCLASSEXW windowClass{
        .cbSize = sizeof(windowClass),
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = CountdownWindowProc,
        .hInstance = g_modModule,
        .hCursor = LoadCursorW(nullptr, IDC_ARROW),
        .lpszClassName = g_countdownWindowClassName,
    };

    g_countdownWindowClassAtom = RegisterClassExW(&windowClass);
    if (!g_countdownWindowClassAtom) {
        Wh_Log(L"RegisterClassExW failed: %lu", GetLastError());
        return false;
    }

    return true;
}

template <typename FunctionPointer>
bool HookExport(const wchar_t* moduleName, const char* functionName,
                FunctionPointer hookFunction, FunctionPointer* originalFunction) {
    HMODULE module = GetModuleHandleW(moduleName);
    if (!module) {
        Wh_Log(L"Module %ls isn't loaded; skipping %S", moduleName, functionName);
        return false;
    }
    auto target = reinterpret_cast<FunctionPointer>(GetProcAddress(module, functionName));
    if (!target) {
        Wh_Log(L"Couldn't find %S in %ls", functionName, moduleName);
        return false;
    }
    if (!WindhawkUtils::SetFunctionHook(target, hookFunction, originalFunction)) {
        Wh_Log(L"Couldn't hook %S", functionName);
        return false;
    }
    Wh_Log(L"Hooked %S", functionName);
    return true;
}

void CloseLifecycleHandles() {
    if (g_countdownStopEvent) {
        CloseHandle(g_countdownStopEvent);
        g_countdownStopEvent = nullptr;
    }

    if (g_countdownIdleEvent) {
        CloseHandle(g_countdownIdleEvent);
        g_countdownIdleEvent = nullptr;
    }
}

}  // namespace

BOOL Wh_ModInit() {
    LoadSettings();

    wchar_t processPath[MAX_PATH]{};
    GetModuleFileNameW(nullptr, processPath, std::size(processPath));
    Wh_Log(L"Initializing in process %lu: %ls",
           GetCurrentProcessId(), processPath);

    if (!InitializeModModuleHandle()) {
        Wh_Log(L"Couldn't resolve the mod module handle: %lu",
               GetLastError());
        return FALSE;
    }

    g_countdownStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_countdownIdleEvent = CreateEventW(nullptr, TRUE, TRUE, nullptr);
    if (!g_countdownStopEvent || !g_countdownIdleEvent) {
        Wh_Log(L"Couldn't create lifecycle events: %lu", GetLastError());
        CloseLifecycleHandles();
        return FALSE;
    }

    if (!RegisterCountdownWindowClass()) {
        // Never reuse an existing class: its WndProc might belong to an
        // unloaded instance of this mod.
        CloseLifecycleHandles();
        return FALSE;
    }

    bool hooked = false;
    hooked |= HookExport(L"user32.dll", "ExitWindowsEx",
                         ExitWindowsEx_Hook,
                         &ExitWindowsEx_Original);
    hooked |= HookExport(L"advapi32.dll", "InitiateShutdownW",
                         InitiateShutdownW_Hook,
                         &InitiateShutdownW_Original);
    hooked |= HookExport(L"advapi32.dll", "InitiateSystemShutdownExW",
                         InitiateSystemShutdownExW_Hook,
                         &InitiateSystemShutdownExW_Original);
    hooked |= HookExport(L"kernel32.dll", "SetSystemPowerState",
                         SetSystemPowerState_Hook,
                         &SetSystemPowerState_Original);
    hooked |= HookExport(L"ntdll.dll", "NtInitiatePowerAction",
                         NtInitiatePowerAction_Hook,
                         &NtInitiatePowerAction_Original);
    hooked |= HookExport(L"ntdll.dll", "NtSetSystemPowerState",
                         NtSetSystemPowerState_Hook,
                         &NtSetSystemPowerState_Original);

    if (!hooked) {
        Wh_Log(L"No supported power API could be hooked");
        UnregisterClassW(g_countdownWindowClassName, g_modModule);
        g_countdownWindowClassAtom = 0;
        CloseLifecycleHandles();
        return FALSE;
    }

    return TRUE;
}

void Wh_ModBeforeUninit() {
    AcquireSRWLockExclusive(&g_countdownLifecycleLock);
    g_unloading.store(true, std::memory_order_release);
    if (g_countdownStopEvent) {
        SetEvent(g_countdownStopEvent);
    }
    ReleaseSRWLockExclusive(&g_countdownLifecycleLock);

    if (g_countdownIdleEvent) {
        if (WaitForSingleObject(g_countdownIdleEvent, INFINITE) == WAIT_FAILED) {
            Wh_Log(L"Failed waiting for the countdown thread to stop: %lu",
                   GetLastError());
        }
    }
}

void Wh_ModUninit() {
    if (g_countdownWindowClassAtom) {
        if (!UnregisterClassW(g_countdownWindowClassName, g_modModule)) {
            Wh_Log(L"UnregisterClassW failed: %lu", GetLastError());
        }
        g_countdownWindowClassAtom = 0;
    }

    CloseLifecycleHandles();
}

void Wh_ModSettingsChanged() {
    LoadSettings();
    HWND openCountdown = g_countdownWindow.load(std::memory_order_acquire);
    if (openCountdown && IsWindow(openCountdown)) {
        RedrawWindow(openCountdown, nullptr, nullptr,
                     RDW_INVALIDATE | RDW_NOERASE | RDW_NOFRAME);
    }
}
