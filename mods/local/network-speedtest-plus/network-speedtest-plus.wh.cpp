// ==WindhawkMod==
// @id              network-speedtest-plus
// @name            Network Speed Test Plus
// @description     Tray speed test button next to the network icon, plus the Windows 11 network menu speed test as a native flyout: ping, jitter, download and upload measured against Cloudflare, live gauge, results chart with copy. Mocha glass, FiraCode, gradient hover. No browser, no separate app.
// @version         2.4.0
// @author          DavidHiFi, Alessandro-Vecchio
// @github          https://github.com/DavidHiFi
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @include         ShellHost.exe
// @include         ShellExperienceHost.exe
// @include         SystemSettings.exe
// @include         RuntimeBroker.exe
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -DWIN32_LEAN_AND_MEAN -lshlwapi -lshell32 -lole32 -ladvapi32 -luser32 -lgdi32 -ld2d1 -ld3d11 -ldcomp -ldwrite -ldwmapi -lwinhttp -liphlpapi -lshcore -luuid -loleacc -loleaut32 -lwindowscodecs -luxtheme -lcomctl32 -lws2_32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Network Menu Speed Test Plus

## What's new in 2.4.0

- The speed test window now fades and slides in when it opens, and back out
  when it closes. It slides down from a top taskbar and up from a bottom one.
- Two new settings under Appearance: **Open and close animation** turns it on
  or off, and **Animation speed** picks how quick it plays. The default follows
  the global speed shared by all DavidHiFi mods.
- The animation also stays off when Windows "Animation effects" is off.

Based on Network Menu Speed Test by Alessandro-Vecchio.

Windows 11's network menu ("Run internet speed test") opens

    https://go.microsoft.com/fwlink/?linkid=2324916

in the default browser, which redirects to a Bing search page.

This mod intercepts that URL in the shell processes and replaces it with a
native flyout. The window, the gauge, the result cards and the speed
measurement all live inside the mod: no external application or protocol
handler is involved. The test talks to the public Cloudflare speed test
endpoints (`speed.cloudflare.com`), the same stateless endpoints used by the
website.

### Screenshots

| Light theme | Dark theme |
| --- | --- |
| ![Light theme](https://raw.githubusercontent.com/Alessandro-Vecchio/windhawk-mods/assets/light.png) | ![Dark theme](https://raw.githubusercontent.com/Alessandro-Vecchio/windhawk-mods/assets/dark.png) |

| Desktop Acrylic | Results card |
| --- | --- |
| ![Desktop Acrylic](https://raw.githubusercontent.com/Alessandro-Vecchio/windhawk-mods/assets/acrylic.png) | ![Results card](https://raw.githubusercontent.com/Alessandro-Vecchio/windhawk-mods/assets/results.png) |

### Data usage

The test transfers real data with a per-direction budget of **512 MB**. Lines
at or below ~340 Mbps complete the full 12 s window per direction without
reaching the budget; faster lines end the phase once the budget is spent
(minimum 4 s window, and the result divides bytes by the time the transfer
was actually moving data). Total usage stays under ~1 GB regardless of line
speed, and the results card shows the bytes used ("Data used: 762 MB", also
included in the clipboard text).

The **Start the test automatically** setting defaults to `auto`: the test
starts when the flyout opens, except when Windows reports the connection as
metered - then the flyout opens idle and waits for a click on Start.

**Coexistence**: the mod [perform-speedtest-redirect](https://windhawk.net/mods/perform-speedtest-redirect)
intercepts the same URL launches. If both are enabled, whichever mod hooks
the launch first wins - disable the other one to keep this mod's flyout.

The flyout opens above the taskbar, on the monitor under the mouse. It closes
when you click outside, but never while a measurement is running.

It is keyboard accessible (Tab / Enter / Esc with a WinUI-style focus ring),
exposed to screen readers through MSAA (`WM_GETOBJECT`), and honours the
"Animation effects" system setting: with animations off every transition is
instant, the open and close animation included. The error view shrinks the
window to fit its content.

## Settings

- **Extra URL patterns**: additional substrings separated by `|`.
- **Fall back to the web page**: if the flyout cannot start, run the original
  URL instead of doing nothing.
- **Also intercept browser process launches**: catch the network menu launching
  the browser directly through `CreateProcessW`. The launch returns
  `ERROR_CANCELLED` because no browser process is created; turning it off makes
  the menu open the browser normally when the shell skips the shell-execute
  path.
- **Start the test automatically**: `auto` starts the test when the flyout
  opens, but waits for a click when Windows reports the connection as metered;
  `always` starts unconditionally; `never` always waits for a click.
- **Language**: `auto` (follows the Windows display language), `it` or `en`.
- **Tray button**: a speed test button in the taskbar tray, next to the network
  icon. A left click opens the flyout and starts the test right away, even on
  a metered connection. Right-click does nothing; the icon can be hidden into
  the overflow like any other tray icon.
- **Open and close animation**: the window fades and slides in and out. On by
  default.
- **Animation speed**: how quick the window's animations play. Follow the
  global speed (the default) uses the speed shared by all DavidHiFi mods,
  stored in `HKCU\Software\DavidHiFi\Motion`.

Diagnostics go to the Windhawk mod log: enable logging for this mod from its
Details page in Windhawk when you need them.

Note: when the network menu launches the browser directly through
`CreateProcessW`, the flyout is shown but process creation returns
`ERROR_CANCELLED`: the hook never reports success without creating the
requested browser process.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- extraPatterns: ""
  $name: Extra URL patterns
  $description: Additional substrings separated by | (example speedtest.net|ookla.com).
- fallbackToOriginal: true
  $name: Fall back to the web page
  $description: If the native flyout cannot start, open the original web page instead of doing nothing.
- interceptProcessLaunch: true
  $name: Also intercept browser process launches
  $description: Catch direct browser launches from the network menu. The launch returns ERROR_CANCELLED because no browser process is created.
- autoStart: auto
  $name: Start the test automatically
  $description: Starts the test when the flyout opens. Auto waits for a click on metered connections. Never requires a click every time.
  $options:
  - auto: Auto (waits on metered connections)
  - always: Always
  - never: Never (click to start)
- language: auto
  $name: Language
  $description: Language of the flyout texts. Auto follows the Windows display language.
  $options:
  - auto: Automatic (Windows display language)
  - it: Italiano
  - en: English
- flyoutPosition: auto
  $name: Where the window opens
  $description: Corner of the screen the speed test window opens in, on the screen under the mouse. Auto opens it next to the tray, at the taskbar's edge.
  $options:
  - auto: Auto (next to the tray)
  - topRight: Top right
  - topLeft: Top left
  - bottomRight: Bottom right
  - bottomLeft: Bottom left
  - center: Center of the screen
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: Tray icon
  $description: Show the speed test tray icon. Right-click it for settings.
- networkDisplay: always
  $name: Network name
  $description: Choose how the flyout shows the network name.
  $options:
  - always: Always show
  - hover: Blurred until hover
  - click: Blurred until click
  - hidden: Hidden
- serverDisplay: always
  $name: Test server
  $description: Choose how the flyout shows the test server.
  $options:
  - always: Always show
  - hover: Blurred until hover
  - click: Blurred until click
  - hidden: Hidden
- ipDisplay: hidden
  $name: Public IP address
  $description: Choose how the flyout shows the public ip address.
  $options:
  - always: Always show
  - hover: Blurred until hover
  - click: Blurred until click
  - hidden: Hidden
- countryDisplay: hidden
  $name: Country or region
  $description: Choose how the flyout shows the country or region.
  $options:
  - always: Always show
  - hover: Blurred until hover
  - click: Blurred until click
  - hidden: Hidden
- flyoutAnimation: true
  $name: Open and close animation
  $description: The window fades and slides in when it opens and out when it closes. It also stays still when Windows animation effects are off.
- animationSpeed: global
  $name: Animation speed
  $description: How quick the window's animations play. Follow the global speed uses the speed shared by all DavidHiFi mods.
  $options:
  - global: Follow the global speed
  - veryQuick: Very quick
  - quick: Quick
  - normal: Normal
  - relaxed: Relaxed
  - slow: Slow
- flyoutBorderWidth: 3
  $name: Border width
  $description: Thickness of the speed test window border at 100% scaling.
- flyoutBorderRest: "#585B70"
  $name: Resting color
  $description: Hex color for the resting color of the speed test window border.
- flyoutBorderHoverStart: "#89B4FA"
  $name: Hover start color
  $description: Hex color for the hover start color of the speed test window border.
- flyoutBorderHoverEnd: "#CBA6F7"
  $name: Hover end color
  $description: Hex color for the hover end color of the speed test window border.
*/
// ==/WindhawkModSettings==

#include <windows.h>
// WIN32_LEAN_AND_MEAN (set in @compilerOptions) makes windows.h skip these:
// - shellapi.h: the hooks use SHELLEXECUTEINFOW/ShellExecuteW.
// - winsock2.h/ws2tcpip.h: iptypes.h (IP_ADAPTER_ADDRESSES) is built on the
//   Winsock address types, and the adapter matching uses SOCKADDR_IN6. The mod
//   itself never calls Winsock functions.
#include <shellapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windowsx.h>
#include <shlwapi.h>
#include <shellscalingapi.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <dcomp.h>
#include <dwrite.h>
#include <dwmapi.h>
#include <oleacc.h>
#include <winhttp.h>
#include <iphlpapi.h>
#include <iptypes.h>
#include <netlistmgr.h>
#include <cmath>
#include <algorithm>
#include <deque>
#include <string>
#include <string_view>
#include <vector>
#include <cstdio>
#include <cwchar>
#include <new>
#include <atomic>
#include <memory>
#include <map>
#include <tuple>
#include <wincodec.h>
#include <uxtheme.h>

#include <windhawk_utils.h>

constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();

using ShellExecuteExW_t = decltype(&ShellExecuteExW);
using ShellExecuteW_t = decltype(&ShellExecuteW);
using CreateProcessW_t = decltype(&CreateProcessW);

static ShellExecuteExW_t ShellExecuteExW_Original;
static ShellExecuteW_t ShellExecuteW_Original;
static CreateProcessW_t CreateProcessW_Original;

static std::vector<std::wstring> g_patterns;
// Settings are reloaded by Windhawk on its own thread while the shell hooks
// read the patterns from arbitrary threads. Swapping the vector under a lock
// prevents a hook from walking a vector that is being rebuilt.
static SRWLOCK g_patternsLock = SRWLOCK_INIT;
static std::atomic<bool> g_fallbackToOriginal = true;
static std::atomic<bool> g_interceptProcessLaunch = true;
// Start mode for the flyout: 0 = auto (start unless the connection is
// metered), 1 = always start, 2 = never start (wait for the Start button).
static std::atomic<int> g_autoStart = 0;

// Tray button state; the window itself lives in the tray button section.
static std::atomic<bool> g_trayEnabled{true};
// A tray click promises the test: the show handler consumes this and starts
// the measurement right away, even on a metered link.
static std::atomic<bool> g_startFromTray{false};
// Where the flyout opens: 0 auto (tray edge), 1 top right, 2 top left,
// 3 bottom right, 4 bottom left, 5 centre.
static std::atomic<int> g_flyoutPosition{0};
// Open and close animation switch, and the speed: 0 follows the global speed
// in HKCU\Software\DavidHiFi\Motion, 1..5 = very quick .. slow.
static std::atomic<bool> g_flyoutAnimation{true};
static std::atomic<int> g_animationSpeed{0};

// The flyout window handle and the mod's own image base. Declared here
// because the tray button, which lives before the flyout section, uses both.
static HWND g_flyoutHwnd = nullptr;
extern "C" IMAGE_DOS_HEADER __ImageBase;

// ---------------------------------------------------------------------------
// UI strings (Italian / English, chosen from the Windows display language)
// ---------------------------------------------------------------------------

struct UiStrings {
    PCWSTR ready;
    PCWSTR starting;
    PCWSTR connecting;
    PCWSTR completed;
    PCWSTR canceled;
    PCWSTR stopping;
    PCWSTR error;
    PCWSTR ping;
    PCWSTR download;
    PCWSTR upload;
    PCWSTR jitter;
    PCWSTR dataUsed;
    PCWSTR copy;
    PCWSTR copied;
    PCWSTR start;
    PCWSTR stop;
    PCWSTR repeat;
    PCWSTR resultsTitle;
    PCWSTR failedTitle;
    PCWSTR failedHint;
    PCWSTR retry;
    PCWSTR closeName;
    PCWSTR server;
    PCWSTR errConnect;
    PCWSTR errPing;
    PCWSTR errCanceled;
    PCWSTR errUpload;
    PCWSTR errDownload;
    PCWSTR errUnexpected;
};

static const UiStrings kStringsIt = {
    L"Pronto", L"Avvio", L"Connessione", L"Completato", L"Annullato",
    L"Arresto\x2026", L"Errore", L"Ping", L"Download", L"Upload", L"Jitter",
    L"Dati usati", L"Copia", L"Copiato", L"Avvia", L"Interrompi", L"Ripeti",
    L"Risultati del test", L"Test non riuscito",
    L"Riprova tra qualche istante.", L"Riprova", L"Chiudi", L"Server",
    L"Impossibile collegarsi al server.",
    L"Impossibile misurare il ping: richieste fallite.",
    L"Test annullato.",
    L"Upload: il server non ha ricevuto dati. Riprova tra qualche minuto.",
    L"Download: il server non ha restituito dati. Riprova tra qualche minuto.",
    L"Errore imprevisto durante il test.",
};

static const UiStrings kStringsEn = {
    L"Ready", L"Starting", L"Connecting", L"Completed", L"Canceled",
    L"Stopping\x2026", L"Error", L"Ping", L"Download", L"Upload", L"Jitter",
    L"Data used", L"Copy", L"Copied", L"Start", L"Stop", L"Repeat",
    L"Test results", L"Test failed",
    L"Try again in a moment.", L"Retry", L"Close", L"Server",
    L"Could not connect to the server.",
    L"Could not measure the ping: requests failed.",
    L"Test canceled.",
    L"Upload: the server received no data. Try again in a few minutes.",
    L"Download: the server returned no data. Try again in a few minutes.",
    L"Unexpected error during the test.",
};

class UiStringsRef {
public:
    explicit UiStringsRef(const UiStrings* strings) : strings_(strings) {}

    const UiStrings* operator->() const {
        return strings_.load(std::memory_order_relaxed);
    }

    UiStringsRef& operator=(const UiStrings* strings) {
        strings_.store(strings, std::memory_order_relaxed);
        return *this;
    }

    bool operator==(const UiStrings* strings) const {
        return strings_.load(std::memory_order_relaxed) == strings;
    }

private:
    std::atomic<const UiStrings*> strings_;
};

static UiStringsRef g_str(&kStringsIt);

static void SelectLanguage(PCWSTR language) {
    bool english = false;
    if (_wcsicmp(language, L"en") == 0) {
        english = true;
    } else if (_wcsicmp(language, L"it") == 0) {
        english = false;
    } else {
        LANGID lang = GetUserDefaultUILanguage();
        english = PRIMARYLANGID(lang) != LANG_ITALIAN;
    }
    g_str = english ? &kStringsEn : &kStringsIt;
}

static std::vector<std::wstring> SplitPatterns(PCWSTR text) {
    std::vector<std::wstring> result;
    std::wstring current;
    for (PCWSTR p = text; p && *p; p++) {
        if (*p == L'|') {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
        } else if (*p != L' ' && *p != L'\t') {
            current.push_back(*p);
        }
    }
    if (!current.empty()) {
        result.push_back(current);
    }
    return result;
}

enum class DetailMode : unsigned { Always, Hover, Click, Hidden };
static unsigned g_detailModes = 0xF0;
static std::atomic<unsigned> g_pendingDetailModes{0xF0};

static DetailMode DetailDisplay(size_t index) {
    return static_cast<DetailMode>((g_detailModes >> (index * 2)) & 3);
}

static std::atomic<int> g_borderWidth{3};
static std::atomic<UINT32> g_borderRest{0x585B70};
static std::atomic<UINT32> g_borderHoverStart{0x89B4FA};
static std::atomic<UINT32> g_borderHoverEnd{0xCBA6F7};

static UINT32 ReadBorderColor(PCWSTR key, UINT32 fallback) {
    auto value = WindhawkUtils::StringSetting::make(key);
    std::wstring_view hex(value.get());
    if (hex.size() != 7 || hex.front() != L'#' ||
        hex.substr(1).find_first_not_of(L"0123456789abcdefABCDEF") != std::wstring_view::npos)
        return fallback;
    return static_cast<UINT32>(wcstoul(value.get() + 1, nullptr, 16));
}

static void LoadSettings() {
    int width = Wh_GetIntSetting(L"flyoutBorderWidth");
    g_borderWidth.store(width ? std::clamp(width, 1, 6) : 3);
    g_borderRest.store(ReadBorderColor(L"flyoutBorderRest", 0x585B70));
    g_borderHoverStart.store(ReadBorderColor(L"flyoutBorderHoverStart", 0x89B4FA));
    g_borderHoverEnd.store(ReadBorderColor(L"flyoutBorderHoverEnd", 0xCBA6F7));
    const PCWSTR keys[] = {L"networkDisplay", L"serverDisplay", L"ipDisplay", L"countryDisplay"};
    unsigned modes = 0;
    for (size_t i = 0; i < ARRAYSIZE(keys); ++i) {
        auto value = WindhawkUtils::StringSetting::make(keys[i]);
        DetailMode mode = i < 2 ? DetailMode::Always : DetailMode::Hidden;
        if (wcscmp(value.get(), L"always") == 0) mode = DetailMode::Always;
        if (wcscmp(value.get(), L"hover") == 0) mode = DetailMode::Hover;
        if (wcscmp(value.get(), L"click") == 0) mode = DetailMode::Click;
        if (wcscmp(value.get(), L"hidden") == 0) mode = DetailMode::Hidden;
        modes |= static_cast<unsigned>(mode) << (i * 2);
    }
    g_pendingDetailModes.store(modes);
    auto extra = WindhawkUtils::StringSetting::make(L"extraPatterns");
    std::vector<std::wstring> patterns = SplitPatterns(extra.get());
    AcquireSRWLockExclusive(&g_patternsLock);
    g_patterns.swap(patterns);
    ReleaseSRWLockExclusive(&g_patternsLock);

    g_fallbackToOriginal.store(Wh_GetIntSetting(L"fallbackToOriginal") != 0,
                               std::memory_order_relaxed);
    g_interceptProcessLaunch.store(
        Wh_GetIntSetting(L"interceptProcessLaunch") != 0,
        std::memory_order_relaxed);
    auto autoStart = WindhawkUtils::StringSetting::make(L"autoStart");
    int startMode = 0;
    if (wcscmp(autoStart.get(), L"always") == 0) {
        startMode = 1;
    } else if (wcscmp(autoStart.get(), L"never") == 0) {
        startMode = 2;
    }
    g_autoStart.store(startMode, std::memory_order_relaxed);
    auto language = WindhawkUtils::StringSetting::make(L"language");
    SelectLanguage(*language.get() ? language.get() : L"auto");
    g_trayEnabled.store(Wh_GetIntSetting(L"settingsTrayIcon") != 0,
                        std::memory_order_relaxed);
    auto position = WindhawkUtils::StringSetting::make(L"flyoutPosition");
    static const PCWSTR kPositions[] = {L"auto",       L"topRight",
                                        L"topLeft",    L"bottomRight",
                                        L"bottomLeft", L"center"};
    int positionIndex = 0;
    for (int i = 0; i < (int)ARRAYSIZE(kPositions); i++) {
        if (_wcsicmp(position.get(), kPositions[i]) == 0) {
            positionIndex = i;
            break;
        }
    }
    g_flyoutPosition.store(positionIndex, std::memory_order_relaxed);
    g_flyoutAnimation.store(Wh_GetIntSetting(L"flyoutAnimation") != 0,
                            std::memory_order_relaxed);
    auto speed = WindhawkUtils::StringSetting::make(L"animationSpeed");
    static const PCWSTR kSpeeds[] = {L"global", L"veryQuick", L"quick",
                                     L"normal", L"relaxed",   L"slow"};
    int speedIndex = 0;
    for (int i = 0; i < (int)ARRAYSIZE(kSpeeds); i++) {
        if (_wcsicmp(speed.get(), kSpeeds[i]) == 0) {
            speedIndex = i;
            break;
        }
    }
    g_animationSpeed.store(speedIndex, std::memory_order_relaxed);
}

// ---------------------------------------------------------------------------
// URL matching
// ---------------------------------------------------------------------------

static bool IsSpeedTestUrl(PCWSTR url) {
    if (!url || !*url) {
        return false;
    }

    // The links shipped by the Windows 11 network flyout/tray menu and the
    // page they redirect to. Keep this list narrow: the hook must never touch
    // ordinary web searches.
    static const PCWSTR kDefaultPatterns[] = {
        L"linkid=2325015",
        L"linkid=2324916",
        L"form=wspeed",
    };
    for (PCWSTR pattern : kDefaultPatterns) {
        if (StrStrIW(url, pattern)) {
            return true;
        }
    }

    // User-supplied extra patterns only apply to actual web URLs: the hooks
    // also see file names and command lines (a document, a launcher, ...), and
    // a file whose name contains a pattern must not be cancelled. The empty
    // check above already returned, so only the scheme matters here.
    if (!(url[0] == L'h' || url[0] == L'H')) {
        return false;
    }
    if (!StrStrIW(url, L"://")) {
        return false;
    }

    bool matched = false;
    AcquireSRWLockShared(&g_patternsLock);
    for (const auto& pattern : g_patterns) {
        if (StrStrIW(url, pattern.c_str())) {
            matched = true;
            break;
        }
    }
    ReleaseSRWLockShared(&g_patternsLock);
    return matched;
}

// ---------------------------------------------------------------------------
// Flyout activation across the shell processes
// ---------------------------------------------------------------------------

static constexpr PCWSTR kFlyoutClass = L"SpeedTestFlyout_Native";
static UINT g_showMessage = 0;

static BOOL CALLBACK FindFlyoutCallback(HWND hwnd, LPARAM param) {
    wchar_t className[64] = {};
    if (GetClassNameW(hwnd, className, ARRAYSIZE(className)) &&
        _wcsicmp(className, kFlyoutClass) == 0) {
        *(HWND*)param = hwnd;
        return FALSE;
    }
    return TRUE;
}

static HWND FindFlyoutHost(DWORD* hostPid = nullptr) {
    // FindWindow is unreliable for this window class across shell processes,
    // so walk the top-level windows instead.
    HWND hwnd = nullptr;
    EnumWindows(FindFlyoutCallback, (LPARAM)&hwnd);
    if (hwnd && hostPid) {
        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        *hostPid = pid;
    }
    return hwnd;
}

static bool ShowNativeFlyout() {
    // This runs inside a shell or process-launch hook, on whatever thread the
    // caller uses to launch the browser. Never wait for the UI here: a
    // blocking hook can re-enter the shell's XAML while it is starting a
    // process. If the host isn't there yet, fail fast and let the caller fall
    // back to the original URL.
    if (!g_showMessage) {
        Wh_Log(L"Registered flyout message is unavailable");
        return false;
    }

    DWORD hostPid = 0;
    HWND hwnd = FindFlyoutHost(&hostPid);
    if (!hwnd) {
        Wh_Log(L"Flyout host window not found");
        return false;
    }
    // The foreground grant belongs to the process the click happened in; the
    // flyout window lives in the host process (usually explorer.exe). Grant it
    // permission to take the foreground before posting the show request,
    // otherwise SetForegroundWindow inside the flyout can fail and the window
    // opens without focus (Esc/Tab dead).
    if (hostPid) {
        AllowSetForegroundWindow(hostPid);
    }
    if (!PostMessageW(hwnd, g_showMessage, 0, 0)) {
        Wh_Log(L"Flyout message post failed (error %u)", GetLastError());
        return false;
    }
    Wh_Log(L"Flyout requested");
    return true;
}

// ---------------------------------------------------------------------------
// Tray button: a normal tray icon in the taskbar tray, left click opens the
// flyout and starts the test. It carries a fixed GUID of our own, so the
// taskbar treats it like any other tray icon: it keeps its spot across
// sessions and can be hidden into the overflow or dragged back.
// ---------------------------------------------------------------------------

static constexpr wchar_t kTrayClass[] = L"NetworkSpeedTestPlus_TrayButton";
// A tray GUID is tied to the executable that first registered it. 2.0 ran
// in explorer.exe; 2.1 runs in the mod's own process, so it has a new GUID.
static constexpr GUID kTrayIconGuid = {
    0x6F3E9A51, 0x2C47, 0x4D8B,
    {0x9E, 0x25, 0x71, 0xB4, 0x3D, 0x8C, 0xA6, 0xF1}};
static const UINT kTrayCallbackMessage = WM_APP + 20;
static const UINT kTrayToggleMessage = WM_APP + 21;
static HWND g_trayHwnd = nullptr;
// Set when the icon is registered with the tray. The taskbar broadcasts
// TaskbarCreated whenever its tray is (re)created; a mod initialized
// before that moment must retry there or its button never appears.
static UINT g_taskbarCreatedMessage = 0;
static bool g_trayIconAdded = false;
static bool AddTrayIcon(HWND hwnd);

// The shared badge: a rounded square (radius 0.26 of the icon) in the blue to
// mauve gradient, with the flyout's gauge as the glyph in crust. Drawn per
// pixel like every other mod's tray badge, at the tray's real size.
static HICON CreateTrayIcon() {
    const int size = GetSystemMetrics(SM_CXSMICON);
    if (size <= 0) {
        return nullptr;
    }
    HDC screen = GetDC(nullptr);
    if (!screen) {
        return nullptr;
    }
    BITMAPV5HEADER header = {};
    header.bV5Size = sizeof(header);
    header.bV5Width = size;
    header.bV5Height = size;
    header.bV5Planes = 1;
    header.bV5BitCount = 32;
    header.bV5Compression = BI_BITFIELDS;
    header.bV5RedMask = 0x00FF0000;
    header.bV5GreenMask = 0x0000FF00;
    header.bV5BlueMask = 0x000000FF;
    header.bV5AlphaMask = 0xFF000000;
    void* bits = nullptr;
    void* glyphBits = nullptr;
    HBITMAP color = CreateDIBSection(screen, (BITMAPINFO*)&header,
                                     DIB_RGB_COLORS, &bits, nullptr, 0);
    HBITMAP glyph = CreateDIBSection(screen, (BITMAPINFO*)&header,
                                     DIB_RGB_COLORS, &glyphBits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color || !glyph || !bits || !glyphBits) {
        if (color) {
            DeleteObject(color);
        }
        if (glyph) {
            DeleteObject(glyph);
        }
        return nullptr;
    }

    // Glyph layer: white gauge on black, so the green channel is the coverage.
    HDC gdc = CreateCompatibleDC(nullptr);
    HGDIOBJ oldGlyph = SelectObject(gdc, glyph);
    RECT glyphRect = {0, 0, size, size};
    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(gdc, &glyphRect, black);
    DeleteObject(black);
    float s = (float)size;
    float cx = s * 0.5f;
    float cy = s * 0.57f;
    float radius = s * 0.30f;
    const double pi = 3.14159265358979323846;
    HPEN pen = CreatePen(PS_SOLID, std::max(1, (int)std::lround(s * 0.085f)),
                         RGB(255, 255, 255));
    HGDIOBJ oldPen = SelectObject(gdc, pen);
    // The 270-degree ring, from 135 degrees clockwise to 45 degrees. GDI runs
    // counterclockwise from 3 o'clock, so start and end swap.
    double start = 135.0 * pi / 180.0;
    double end = 45.0 * pi / 180.0;
    Arc(gdc, (int)(cx - radius), (int)(cy - radius), (int)(cx + radius),
        (int)(cy + radius), (int)(cx + radius * cos(start)),
        (int)(cy - radius * sin(start)), (int)(cx + radius * cos(end)),
        (int)(cy - radius * sin(end)));
    // Needle up-right, like a test in flight.
    double needle = 55.0 * pi / 180.0;
    MoveToEx(gdc, (int)cx, (int)cy, nullptr);
    LineTo(gdc, (int)(cx + radius * 0.72 * cos(needle)),
           (int)(cy - radius * 0.72 * sin(needle)));
    SelectObject(gdc, oldPen);
    DeleteObject(pen);
    float dot = std::max(1.0f, s * 0.055f);
    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
    HGDIOBJ oldBrush = SelectObject(gdc, white);
    Ellipse(gdc, (int)(cx - dot), (int)(cy - dot), (int)(cx + dot),
            (int)(cy + dot));
    SelectObject(gdc, oldBrush);
    DeleteObject(white);
    GdiFlush();
    SelectObject(gdc, oldGlyph);
    DeleteDC(gdc);

    // Mocha blue 89B4FA to mauve CBA6F7, glyph in crust 11111B.
    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
    const float ink[3] = {0x11 / 255.f, 0x11 / 255.f, 0x1B / 255.f};
    float plate = size * 0.26f, half = size / 2.0f;
    UINT32* px = (UINT32*)bits;
    const UINT32* gp = (const UINT32*)glyphBits;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            // Signed distance to the rounded square, for a soft edge.
            float qx = std::fabs(x + 0.5f - half) - (half - plate);
            float qy = std::fabs(y + 0.5f - half) - (half - plate);
            float ox = std::max(qx, 0.0f), oy = std::max(qy, 0.0f);
            float d = std::sqrt(ox * ox + oy * oy) +
                      std::min(std::max(qx, qy), 0.0f) - plate;
            float a = std::clamp(0.5f - d, 0.0f, 1.0f);
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = (base + (ink[i] - base) * cov) * a;  // Premultiplied.
            }
            px[y * size + x] =
                ((UINT32)(a * 255 + 0.5f) << 24) |
                ((UINT32)(rgb[0] * 255 + 0.5f) << 16) |
                ((UINT32)(rgb[1] * 255 + 0.5f) << 8) |
                (UINT32)(rgb[2] * 255 + 0.5f);
        }
    }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO info = {};
    info.fIcon = TRUE;
    info.hbmMask = mask;
    info.hbmColor = color;
    HICON icon = CreateIconIndirect(&info);
    DeleteObject(mask);
    DeleteObject(color);
    DeleteObject(glyph);
    return icon;
}

namespace speedset {
void ShowMenu(HWND owner);
void OpenSettingsWindow();
void CloseSettingsWindow();
void ReloadSettingsWindow();
}

static LRESULT CALLBACK TrayWndProc(HWND hwnd, UINT message, WPARAM wParam,
                                    LPARAM lParam) {
    if (g_taskbarCreatedMessage && message == g_taskbarCreatedMessage) {
        // The taskbar was created or rebuilt and the tray starts empty:
        // register the icon again. The mod runs in its own process now, so
        // it outlives the shell: re-add every time, not only after a failed
        // first registration.
        if (g_trayHwnd) {
            g_trayIconAdded = AddTrayIcon(hwnd);
        }
        return 0;
    }
    switch (message) {
        case kTrayCallbackMessage:
            if (lParam == WM_RBUTTONUP) {
                speedset::ShowMenu(hwnd);
            } else if (lParam == WM_LBUTTONUP && g_flyoutHwnd) {
                g_startFromTray.store(true, std::memory_order_relaxed);
                if (!ShowNativeFlyout()) {
                    g_startFromTray.store(false, std::memory_order_relaxed);
                }
            }
            return 0;

        case WM_DESTROY: {
            NOTIFYICONDATA nid = {sizeof(nid)};
            nid.hWnd = hwnd;
            nid.uID = kTrayId;
            // The icon is GUID-registered: the delete needs the same flag,
            // or the GUID stays claimed and the next add fails.
            nid.uFlags = NIF_GUID;
            nid.guidItem = kTrayIconGuid;
            Shell_NotifyIconW(NIM_DELETE, &nid);
            if (hwnd == g_trayHwnd) {
                g_trayHwnd = nullptr;
            }
            return 0;
        }
    }
    return DefWindowProcW(hwnd, message, wParam, lParam);
}

static bool AddTrayIcon(HWND hwnd) {
    HICON icon = CreateTrayIcon();
    NOTIFYICONDATA nid = {sizeof(nid)};
    nid.hWnd = hwnd;
    nid.uID = kTrayId;
    // NIF_GUID makes the tray register the icon under its GUID, which gives
    // it its own entry in NotifyIconSettings (promotable) instead of
    // colliding with another icon on (executable, uID).
    nid.uFlags = NIF_MESSAGE | NIF_TIP | NIF_SHOWTIP | NIF_GUID;
    nid.uCallbackMessage = kTrayCallbackMessage;
    nid.guidItem = kTrayIconGuid;
    lstrcpynW(nid.szTip, L"Speed test", ARRAYSIZE(nid.szTip));
    if (icon) {
        nid.uFlags |= NIF_ICON;
        nid.hIcon = icon;
    }
    bool added = Shell_NotifyIconW(NIM_ADD, &nid) != 0;
    if (!added) {
        // Still registered (a TaskbarCreated that did not clear the tray):
        // refresh it instead.
        added = Shell_NotifyIconW(NIM_MODIFY, &nid) != 0;
    }
    if (icon) {
        DestroyIcon(icon);
    }
    return added;
}

static void AddTrayButton() {
    if (g_trayHwnd || !g_trayEnabled.load(std::memory_order_relaxed)) {
        return;
    }
    WNDCLASSW windowClass = {};
    windowClass.lpfnWndProc = TrayWndProc;
    windowClass.hInstance = (HINSTANCE)&__ImageBase;
    windowClass.lpszClassName = kTrayClass;
    RegisterClassW(&windowClass);
    HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW, kTrayClass, L"Speed test",
                                WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                                windowClass.hInstance, nullptr);
    if (!hwnd) {
        return;
    }
    g_trayHwnd = hwnd;
    if (g_taskbarCreatedMessage) {
        ChangeWindowMessageFilterEx(hwnd, g_taskbarCreatedMessage, MSGFLT_ALLOW,
                                    nullptr);
    }
    ChangeWindowMessageFilterEx(hwnd, kTrayCallbackMessage, MSGFLT_ALLOW,
                                nullptr);
    g_trayIconAdded = AddTrayIcon(hwnd);
    // A failed registration means the tray did not exist yet (engine boot
    // order); TrayWndProc retries when the taskbar broadcasts
    // TaskbarCreated. The window stays alive so that listener survives.
}

static void RemoveTrayButton() {
    if (g_trayHwnd) {
        // WM_DESTROY removes the icon.
        DestroyWindow(g_trayHwnd);
        g_trayHwnd = nullptr;
        g_trayIconAdded = false;
    }
    UnregisterClassW(kTrayClass, (HINSTANCE)&__ImageBase);
}

static void ToggleTrayButton(bool enable) {
    if (enable) {
        AddTrayButton();
    } else {
        RemoveTrayButton();
    }
}

// ---------------------------------------------------------------------------
// Hooks
// ---------------------------------------------------------------------------

static BOOL WINAPI ShellExecuteExW_Hook(SHELLEXECUTEINFOW* sei) {
    if (sei && IsSpeedTestUrl(sei->lpFile)) {
        Wh_Log(L"ShellExecuteExW match url=%s", sei->lpFile ? sei->lpFile : L"(null)");

        if (ShowNativeFlyout()) {
            if (sei->fMask & SEE_MASK_NOCLOSEPROCESS) {
                sei->hProcess = nullptr;
            }
            sei->hInstApp = (HINSTANCE)33;
            return TRUE;
        }

        if (!g_fallbackToOriginal.load(std::memory_order_relaxed)) {
            SetLastError(ERROR_FILE_NOT_FOUND);
            return FALSE;
        }
    }

    return ShellExecuteExW_Original(sei);
}

static HINSTANCE WINAPI ShellExecuteW_Hook(HWND hwnd, LPCWSTR lpOperation,
                                           LPCWSTR lpFile, LPCWSTR lpParameters,
                                           LPCWSTR lpDirectory, INT nShowCmd) {
    if (IsSpeedTestUrl(lpFile)) {
        Wh_Log(L"ShellExecuteW url=%s", lpFile);
        if (ShowNativeFlyout()) {
            return (HINSTANCE)33;
        }
        if (!g_fallbackToOriginal.load(std::memory_order_relaxed)) {
            SetLastError(ERROR_FILE_NOT_FOUND);
            return (HINSTANCE)ERROR_FILE_NOT_FOUND;
        }
    }

    return ShellExecuteW_Original(hwnd, lpOperation, lpFile, lpParameters,
                                  lpDirectory, nShowCmd);
}

static BOOL WINAPI CreateProcessW_Hook(LPCWSTR lpApplicationName,
                                       LPWSTR lpCommandLine,
                                       LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                       LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                       BOOL bInheritHandles, DWORD dwCreationFlags,
                                       LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
                                       LPSTARTUPINFOW lpStartupInfo,
                                       LPPROCESS_INFORMATION lpProcessInformation) {
    if (g_interceptProcessLaunch.load(std::memory_order_relaxed) &&
        (IsSpeedTestUrl(lpCommandLine) || IsSpeedTestUrl(lpApplicationName))) {
        Wh_Log(L"CreateProcessW match app=%s",
               lpApplicationName ? lpApplicationName : L"(null)");

        if (ShowNativeFlyout()) {
            if (lpProcessInformation) {
                *lpProcessInformation = {};
            }
            SetLastError(ERROR_CANCELLED);
            return FALSE;
        }

        if (!g_fallbackToOriginal.load(std::memory_order_relaxed)) {
            SetLastError(ERROR_FILE_NOT_FOUND);
            return FALSE;
        }
    }

    return CreateProcessW_Original(lpApplicationName, lpCommandLine,
                                   lpProcessAttributes, lpThreadAttributes,
                                   bInheritHandles, dwCreationFlags, lpEnvironment,
                                   lpCurrentDirectory, lpStartupInfo,
                                   lpProcessInformation);
}

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------

static constexpr float kWidth = 400.0f;
// Gauge and results share a height; the error card is much shorter, so the
// window animates between the two layouts instead of leaving an empty gap.
static constexpr float kGaugeHeight = 456.0f;
static constexpr float kErrorHeight = 340.0f;
static constexpr wchar_t kTextFamily[] = L"FiraCode Nerd Font";
static constexpr wchar_t kDisplayFamily[] = L"FiraCode Nerd Font";
static constexpr wchar_t kIconFamily[] = L"Segoe Fluent Icons";

static ULONGLONG Now() {
    return GetTickCount64();
}

static float Clamp01(float v) {
    return v < 0 ? 0 : (v > 1 ? 1 : v);
}

static double Clamp(double v, double lo, double hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

static std::wstring FormatNumber(double value) {
    wchar_t buffer[48];
    if (value >= 100) {
        swprintf(buffer, 48, L"%.0f", value);
    } else {
        swprintf(buffer, 48, L"%.1f", value);
    }
    wchar_t decimalSeparator = g_str == &kStringsEn ? L'.' : L',';
    for (wchar_t* p = buffer; *p; p++) {
        if (*p == L'.') {
            *p = decimalSeparator;
        }
    }
    return buffer;
}

static std::wstring FormatScale(double value) {
    wchar_t buffer[48];
    swprintf(buffer, 48, L"%.0f", value);
    return buffer;
}

static std::wstring FormatClock(const SYSTEMTIME& t) {
    wchar_t buffer[16];
    swprintf(buffer, 16, L"%02u:%02u", t.wHour, t.wMinute);
    return buffer;
}

static std::wstring FormatDate(const SYSTEMTIME& t) {
    wchar_t buffer[24];
    if (g_str == &kStringsEn) {
        swprintf(buffer, 24, L"%02u/%02u/%04u %02u:%02u", t.wMonth, t.wDay,
                 t.wYear, t.wHour, t.wMinute);
    } else {
        swprintf(buffer, 24, L"%02u/%02u/%04u %02u:%02u", t.wDay, t.wMonth,
                 t.wYear, t.wHour, t.wMinute);
    }
    return buffer;
}

static unsigned NextRandom() {
    static volatile LONG seed = (LONG)GetTickCount64();
    unsigned x = (unsigned)InterlockedIncrement(&seed);
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x ? x : 0x9E3779B9u;
}

static double Percentile(std::vector<double> values, double percentile) {
    if (values.empty()) {
        return 0;
    }
    std::sort(values.begin(), values.end());
    if (values.size() == 1) {
        return values[0];
    }
    double rank = percentile / 100.0 * (values.size() - 1);
    size_t low = (size_t)std::floor(rank);
    size_t high = (size_t)std::ceil(rank);
    if (low == high) {
        return values[low];
    }
    return values[low] + (values[high] - values[low]) * (rank - low);
}

static double ChartAxisMax(double peak) {
    double value = std::max(peak * 1.04, 10.0);
    double step;
    if (value > 2000) {
        step = 500;
    } else if (value > 1000) {
        step = 250;
    } else if (value > 500) {
        step = 100;
    } else if (value > 200) {
        step = 50;
    } else if (value > 100) {
        step = 25;
    } else {
        step = 10;
    }
    return std::ceil(value / step) * step;
}

// ---------------------------------------------------------------------------
// Palette
// ---------------------------------------------------------------------------

struct Palette {
    D2D1_COLOR_F background;
    D2D1_COLOR_F text;
    D2D1_COLOR_F secondary;
    D2D1_COLOR_F tertiary;
    D2D1_COLOR_F cardFill;
    D2D1_COLOR_F cardStroke;
    D2D1_COLOR_F controlFill;
    D2D1_COLOR_F track;
    D2D1_COLOR_F download;
    D2D1_COLOR_F upload;
    D2D1_COLOR_F jitter;
    D2D1_COLOR_F positive;
    D2D1_COLOR_F negative;
    D2D1_COLOR_F accent;
    D2D1_COLOR_F accentText;
    D2D1_COLOR_F label;
};

static D2D1_COLOR_F Col(UINT32 rgb, float alpha = 1.0f) {
    D2D1_COLOR_F c;
    c.r = ((rgb >> 16) & 0xFF) / 255.0f;
    c.g = ((rgb >> 8) & 0xFF) / 255.0f;
    c.b = (rgb & 0xFF) / 255.0f;
    c.a = alpha;
    return c;
}

static D2D1_COLOR_F WithAlpha(D2D1_COLOR_F c, float alpha) {
    c.a *= alpha;
    return c;
}

static D2D1_COLOR_F Lighten(D2D1_COLOR_F c, float amount) {
    c.r += (1.0f - c.r) * amount;
    c.g += (1.0f - c.g) * amount;
    c.b += (1.0f - c.b) * amount;
    return c;
}

// Pressed controls get a darker fill in Fluent; Lighten() cannot do that.
static D2D1_COLOR_F Shade(D2D1_COLOR_F c, float amount) {
    c.r *= (1.0f - amount);
    c.g *= (1.0f - amount);
    c.b *= (1.0f - amount);
    return c;
}

// The shell flyouts follow the *system* theme, and the DWM backdrop material is
// tinted from the system palette as well. Reading AppsUseLightTheme here would
// mix a dark surface with a light material (or the other way round).
static bool ReadSystemLightTheme() {
    DWORD value = 1;
    DWORD size = sizeof(value);
    if (RegGetValueW(HKEY_CURRENT_USER,
                     L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                     L"SystemUsesLightTheme", RRF_RT_REG_DWORD, nullptr, &value,
                     &size) != ERROR_SUCCESS) {
        return false;
    }
    return value != 0;
}

static bool ReadTransparencyEnabled() {
    DWORD value = 0;
    DWORD size = sizeof(value);
    if (RegGetValueW(HKEY_CURRENT_USER,
                     L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                     L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &value,
                     &size) != ERROR_SUCCESS) {
        return false;
    }
    return value != 0;
}

static DWORD WindowsBuild() {
    static DWORD build = 0;
    if (!build) {
        using RtlGetVersion_t = LONG(WINAPI*)(OSVERSIONINFOW*);
        auto rtlGetVersion = (RtlGetVersion_t)GetProcAddress(
            GetModuleHandleW(L"ntdll.dll"), "RtlGetVersion");
        OSVERSIONINFOW info = {};
        info.dwOSVersionInfoSize = sizeof(info);
        build = (rtlGetVersion && rtlGetVersion(&info) == 0 && info.dwBuildNumber)
                    ? info.dwBuildNumber
                    : 1;
    }
    return build;
}

// DWMWA_SYSTEMBACKDROP_TYPE only exists from build 22621, and even there DWM
// draws no material when composition is off, on remote sessions or in high
// contrast. Painting a translucent scrim in those cases would leave a
// see-through window with no blur behind it, which looks broken; the caller
// keeps the solid surface instead.
static bool MaterialSupported() {
    if (WindowsBuild() < 22621) {
        return false;
    }
    BOOL composition = FALSE;
    if (FAILED(DwmIsCompositionEnabled(&composition)) || !composition) {
        return false;
    }
    if (GetSystemMetrics(SM_REMOTESESSION)) {
        return false;
    }
    HIGHCONTRASTW contrast = {sizeof(contrast)};
    if (SystemParametersInfoW(SPI_GETHIGHCONTRAST, sizeof(contrast), &contrast, 0) &&
        (contrast.dwFlags & HCF_HIGHCONTRASTON)) {
        return false;
    }
    return true;
}

static Palette MakePalette(bool light) {
    Palette p = {};
    if (light) {
        p.background = Col(0xF3F3F3);
        p.text = Col(0x1A1A1A);
        p.secondary = Col(0x5D5D5D);
        p.tertiary = Col(0x767676);
        p.cardFill = Col(0xFFFFFF, 0.70f);
        p.cardStroke = Col(0x000000, 0.06f);
        p.controlFill = Col(0x000000, 0.04f);
        p.track = Col(0xE4E4E4);
        p.download = Col(0x0B6BCB);
        p.upload = Col(0x6B3FA0);
        p.jitter = Col(0x0F6E66);
        p.positive = Col(0x0F7B0F);
        p.negative = Col(0xC42B1C);
        p.accent = Col(0x005FB8);
        p.accentText = Col(0xFFFFFF);
        p.label = Col(0x6B6B6B);
    } else {
        // The house Mocha palette. Dark is pinned, the light branch below is
        // dead by choice: the look never follows the system theme.
        p.background = Col(0x181825);
        p.text = Col(0xCDD6F4);
        p.secondary = Col(0xA6ADC8);
        p.tertiary = Col(0x9399B2);
        p.cardFill = Col(0x313244, 0.60f);
        p.cardStroke = Col(0xCDD6F4, 0.10f);
        p.controlFill = Col(0xCDD6F4, 0.06f);
        p.track = Col(0x45475A);
        p.download = Col(0x89B4FA);
        p.upload = Col(0xCBA6F7);
        p.jitter = Col(0x94E2D5);
        p.positive = Col(0xA6E3A1);
        p.negative = Col(0xF38BA8);
        p.accent = Col(0x89B4FA);
        p.accentText = Col(0x11111B);
        p.label = Col(0xA6ADC8);
    }
    return p;
}

// ---------------------------------------------------------------------------
// Network name for the footline
// ---------------------------------------------------------------------------

struct NetworkInfo {
    std::wstring name;
    const wchar_t* glyph = L"\xE774";
};

static PIP_ADAPTER_ADDRESSES GetAdapterAddressesList(
    std::vector<BYTE>* buffer) {
    ULONG size = (ULONG)buffer->size();
    ULONG flags = GAA_FLAG_INCLUDE_GATEWAYS | GAA_FLAG_SKIP_ANYCAST |
                  GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER;
    for (int attempt = 0; attempt < 3; attempt++) {
        buffer->resize(size);
        ULONG result = GetAdaptersAddresses(AF_UNSPEC, flags, nullptr,
                                            (PIP_ADAPTER_ADDRESSES)buffer->data(),
                                            &size);
        if (result == ERROR_SUCCESS) {
            return (PIP_ADAPTER_ADDRESSES)buffer->data();
        }
        if (result != ERROR_BUFFER_OVERFLOW) {
            return nullptr;
        }
    }
    return nullptr;
}

// Profile name for the footline: on Wi-Fi this is the SSID, on Ethernet the
// user-visible connection name - what the Windows network flyout shows. The
// Network List Manager knows it; the match to the adapter is by interface
// GUID. An empty result means the caller falls back to the adapter
// description.
static std::wstring NetworkProfileName(PIP_ADAPTER_ADDRESSES adapter) {
    INetworkListManager* manager = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_NetworkListManager, nullptr,
                                  CLSCTX_ALL, IID_PPV_ARGS(&manager));
    if (FAILED(hr)) {
        return L"";
    }

    std::wstring name;
    // IP_ADAPTER_ADDRESSES::AdapterName is the interface GUID as an ANSI
    // string, e.g. "{B49A9A0D-...}".
    wchar_t adapterName[64] = {};
    GUID adapterGuid = {};
    if (adapter->AdapterName &&
        MultiByteToWideChar(CP_ACP, 0, adapter->AdapterName, -1, adapterName,
                            64) > 0 &&
        SUCCEEDED(CLSIDFromString(adapterName, &adapterGuid))) {
        IEnumNetworkConnections* enumerator = nullptr;
        if (SUCCEEDED(manager->GetNetworkConnections(&enumerator))) {
            INetworkConnection* connection = nullptr;
            while (enumerator->Next(1, &connection, nullptr) == S_OK) {
                VARIANT_BOOL connected = VARIANT_FALSE;
                GUID id = {};
                if (connection->get_IsConnected(&connected) == S_OK &&
                    connected != VARIANT_FALSE &&
                    connection->GetAdapterId(&id) == S_OK &&
                    IsEqualGUID(id, adapterGuid)) {
                    INetwork* network = nullptr;
                    BSTR connectionName = nullptr;
                    if (connection->GetNetwork(&network) == S_OK && network) {
                        if (network->GetName(&connectionName) == S_OK &&
                            connectionName) {
                            name = connectionName;
                        }
                        if (connectionName) {
                            SysFreeString(connectionName);
                        }
                        network->Release();
                    }
                }
                connection->Release();
                if (!name.empty()) {
                    break;
                }
            }
            enumerator->Release();
        }
    }
    manager->Release();
    return name;
}

static NetworkInfo NetworkInfoFromAdapter(PIP_ADAPTER_ADDRESSES adapter) {
    NetworkInfo info;
    info.name = NetworkProfileName(adapter);
    if (info.name.empty()) {
        info.name = adapter->Description ? adapter->Description : L"";
    }
    info.glyph =
        adapter->IfType == IF_TYPE_IEEE80211 ? L"\xE701" : L"\xE839";
    return info;
}

static NetworkInfo ReadNetwork() {
    NetworkInfo info;
    std::vector<BYTE> buffer(16 * 1024);
    PIP_ADAPTER_ADDRESSES addresses = GetAdapterAddressesList(&buffer);
    if (!addresses) {
        return info;
    }

    PIP_ADAPTER_ADDRESSES best = nullptr;
    PIP_ADAPTER_ADDRESSES fallback = nullptr;
    for (auto* a = addresses; a; a = a->Next) {
        if (a->OperStatus != IfOperStatusUp ||
            a->IfType == IF_TYPE_SOFTWARE_LOOPBACK ||
            a->IfType == IF_TYPE_TUNNEL) {
            continue;
        }
        if (!fallback) {
            fallback = a;
        }
        if (a->FirstGatewayAddress) {
            best = a;
            break;
        }
    }
    if (!best) {
        best = fallback;
    }
    if (!best) {
        return info;
    }

    return NetworkInfoFromAdapter(best);
}

static NetworkInfo ReadNetworkByIndex(ULONG interfaceIndex,
                                      ADDRESS_FAMILY addressFamily) {
    NetworkInfo info;
    std::vector<BYTE> buffer(16 * 1024);
    PIP_ADAPTER_ADDRESSES addresses = GetAdapterAddressesList(&buffer);
    if (!addresses) {
        return info;
    }

    for (auto* adapter = addresses; adapter; adapter = adapter->Next) {
        bool matches = addressFamily == AF_INET
                           ? adapter->IfIndex == interfaceIndex
                           : addressFamily == AF_INET6 &&
                                 adapter->Ipv6IfIndex == interfaceIndex;
        if (adapter->OperStatus == IfOperStatusUp &&
            adapter->IfType != IF_TYPE_SOFTWARE_LOOPBACK && matches) {
            return NetworkInfoFromAdapter(adapter);
        }
    }
    return info;
}

static bool SameAddress(const SOCKADDR_STORAGE& address,
                        const SOCKADDR* candidate) {
    if (!candidate || address.ss_family != candidate->sa_family) {
        return false;
    }
    if (address.ss_family == AF_INET) {
        const auto* a = (const SOCKADDR_IN*)&address;
        const auto* b = (const SOCKADDR_IN*)candidate;
        return a->sin_addr.s_addr == b->sin_addr.s_addr;
    }
    if (address.ss_family == AF_INET6) {
        const auto* a = (const SOCKADDR_IN6*)&address;
        const auto* b = (const SOCKADDR_IN6*)candidate;
        return memcmp(&a->sin6_addr, &b->sin6_addr, sizeof(IN6_ADDR)) == 0 &&
               (!a->sin6_scope_id || !b->sin6_scope_id ||
                a->sin6_scope_id == b->sin6_scope_id);
    }
    return false;
}

static ULONG InterfaceIndexForLocalAddress(
    const SOCKADDR_STORAGE& localAddress, ADDRESS_FAMILY* addressFamily) {
    if (addressFamily) {
        *addressFamily = AF_UNSPEC;
    }
    std::vector<BYTE> buffer(16 * 1024);
    PIP_ADAPTER_ADDRESSES addresses = GetAdapterAddressesList(&buffer);
    if (!addresses) {
        return 0;
    }

    for (auto* adapter = addresses; adapter; adapter = adapter->Next) {
        if (adapter->OperStatus != IfOperStatusUp ||
            adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK) {
            continue;
        }
        for (auto* unicast = adapter->FirstUnicastAddress; unicast;
             unicast = unicast->Next) {
            if (SameAddress(localAddress, unicast->Address.lpSockaddr)) {
                 if (addressFamily) {
                     *addressFamily = localAddress.ss_family;
                 }
                return localAddress.ss_family == AF_INET ? adapter->IfIndex
                                                          : adapter->Ipv6IfIndex;
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Test state shared between the worker and the UI thread
// ---------------------------------------------------------------------------

enum class Phase {
    Idle,
    Warmup,
    Latency,
    Download,
    Upload,
    Stopping,
    Done,
    Error,
    Canceled,
};

struct Sample {
    double value;
    bool upload;
};

struct TestState {
    Phase phase = Phase::Idle;
    double currentMbps = 0;
    double download = 0;
    double upload = 0;
    double ping = 0;
    double jitter = 0;
    bool hasPing = false;
    bool hasJitter = false;
    bool hasResult = false;
    std::wstring caption;
    std::wstring error;
    std::wstring server = L"Cloudflare";
    std::wstring publicIp, country;
    SYSTEMTIME when = {};
    // Total bytes moved by the test, warm-up included, across both phases.
    LONGLONG dataUsed = 0;
    std::vector<Sample> samples;
};

static SRWLOCK g_stateLock = SRWLOCK_INIT;
static TestState g_state;
static std::atomic<LONG> g_cancelRequested = 0;

static TestState CopyState() {
    TestState copy;
    AcquireSRWLockShared(&g_stateLock);
    copy = g_state;
    ReleaseSRWLockShared(&g_stateLock);
    return copy;
}

static bool StateRunning(const TestState& s) {
    return s.phase == Phase::Warmup || s.phase == Phase::Latency ||
           s.phase == Phase::Download || s.phase == Phase::Upload ||
           s.phase == Phase::Stopping;
}

static bool TestRunning() {
    return StateRunning(CopyState());
}

static void StateReset() {
    AcquireSRWLockExclusive(&g_stateLock);
    g_state = TestState();
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateSetPhase(Phase phase, PCWSTR caption) {
    AcquireSRWLockExclusive(&g_stateLock);
    if (g_state.phase != Phase::Stopping) {
        g_state.phase = phase;
        g_state.caption = caption ? caption : L"";
        g_state.currentMbps = 0;
        g_state.error.clear();
    }
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateSetCaption(PCWSTR caption) {
    AcquireSRWLockExclusive(&g_stateLock);
    if (g_state.phase != Phase::Stopping) {
        g_state.caption = caption ? caption : L"";
    }
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateSetCurrent(double mbps) {
    AcquireSRWLockExclusive(&g_stateLock);
    if (g_state.phase != Phase::Stopping) {
        g_state.currentMbps = mbps;
    }
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateSetLatency(double ping, bool hasPing, double jitter, bool hasJitter) {
    AcquireSRWLockExclusive(&g_stateLock);
    if (g_state.phase != Phase::Stopping) {
        g_state.ping = ping;
        g_state.hasPing = hasPing;
        g_state.jitter = jitter;
        g_state.hasJitter = hasJitter;
    }
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateAddSample(double value, bool upload) {
    if (!(value >= 0) || value > 1000000) {
        return;
    }
    AcquireSRWLockExclusive(&g_stateLock);
    if (g_state.phase != Phase::Stopping) {
        if (g_state.samples.size() >= 240) {
            g_state.samples.erase(g_state.samples.begin());
        }
        g_state.samples.push_back({value, upload});
    }
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateSetMeasured(bool upload, double mbps) {
    AcquireSRWLockExclusive(&g_stateLock);
    if (g_state.phase != Phase::Stopping) {
        if (upload) {
            g_state.upload = mbps;
        } else {
            g_state.download = mbps;
        }
        g_state.currentMbps = mbps;
    }
    ReleaseSRWLockExclusive(&g_stateLock);
}

// Called from the test thread after each transfer phase: warm-up included,
// because the user pays for every byte, not just the measured ones.
static void StateAddDataUsed(LONGLONG bytes) {
    AcquireSRWLockExclusive(&g_stateLock);
    g_state.dataUsed += bytes;
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateSetServer(const std::wstring& server, const std::wstring& ip,
                           const std::wstring& country) {
    AcquireSRWLockExclusive(&g_stateLock);
    g_state.server = server.empty() ? L"Cloudflare" : server;
    g_state.publicIp = ip;
    g_state.country = country;
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateFinish(double download, double upload, double ping, double jitter,
                        bool hasLatency) {
    AcquireSRWLockExclusive(&g_stateLock);
    if (g_state.phase == Phase::Stopping) {
        g_state.phase = Phase::Canceled;
        g_state.caption = g_str->canceled;
        g_state.currentMbps = 0;
        ReleaseSRWLockExclusive(&g_stateLock);
        return;
    }
    g_state.phase = Phase::Done;
    g_state.caption = g_str->completed;
    g_state.download = download;
    g_state.upload = upload;
    g_state.ping = ping;
    g_state.jitter = jitter;
    g_state.hasPing = hasLatency;
    g_state.hasJitter = hasLatency;
    g_state.hasResult = true;
    GetLocalTime(&g_state.when);
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateFail(const std::wstring& message) {
    AcquireSRWLockExclusive(&g_stateLock);
    g_state.phase = Phase::Error;
    g_state.caption = g_str->error;
    g_state.error = message;
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void StateCanceled() {
    AcquireSRWLockExclusive(&g_stateLock);
    g_state.phase = Phase::Canceled;
    g_state.caption = g_str->canceled;
    g_state.currentMbps = 0;
    ReleaseSRWLockExclusive(&g_stateLock);
}

static void RequestTestCancel() {
    g_cancelRequested.store(1, std::memory_order_relaxed);
    AcquireSRWLockExclusive(&g_stateLock);
    if (StateRunning(g_state)) {
        g_state.phase = Phase::Stopping;
        g_state.caption = g_str->stopping;
        g_state.currentMbps = 0;
    }
    ReleaseSRWLockExclusive(&g_stateLock);
}

// ---------------------------------------------------------------------------
// Cloudflare measurement engine (WinHTTP)
// ---------------------------------------------------------------------------

static constexpr PCWSTR kHost = L"speed.cloudflare.com";

// UI host window and the running measurement thread (only in Explorer).
// g_flyoutHwnd is declared up top with the tray button section.
static HANDLE g_testThread = nullptr;

static bool CancelRequested(const std::atomic<LONG>* stop = nullptr) {
    return g_cancelRequested.load(std::memory_order_relaxed) != 0 ||
           (stop && stop->load(std::memory_order_relaxed) != 0);
}

struct TransferCounter {
    std::atomic<LONGLONG> bytes = 0;
    // Per-phase data budget in bytes (0 = unlimited). Workers stop requesting
    // new transfers once it is spent, and read/write loops cut in-flight
    // transfers short when they notice; the partial bytes still count, so the
    // total never overshoots the budget by much. Full-window measurement is
    // unaffected at or below the budget line (~340 Mbps); faster lines end the
    // phase early and the result divides by the actual elapsed time.
    LONGLONG budget = 0;

    bool BudgetExceeded() const {
        return budget > 0 &&
               bytes.load(std::memory_order_relaxed) >= budget;
    }
};

static void AddBytes(TransferCounter* counter, long long count) {
    counter->bytes.fetch_add(count, std::memory_order_relaxed);
}

class HttpClient {
public:
    HttpClient() = default;
    HttpClient(const HttpClient&) = delete;
    HttpClient& operator=(const HttpClient&) = delete;

    ~HttpClient() { Close(); }

    bool Open() {
        Close();
        session_ = WinHttpOpen(L"NetworkMenuSpeedTest/1.0",
                               WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
                               WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
        if (!session_) {
            return false;
        }
        // Resolve/connect stay short so a cancel or a mod unload can unwind a
        // blocked worker promptly. The send timeout is long because it bounds
        // WinHttpWriteData when the TCP window is full: with 8 parallel upload
        // workers on a slow line a 256 KB block can legitimately take tens of
        // seconds, and a 3 s limit failed the upload incorrectly. Cancellation
        // is signalled through the stop flag; workers check it between blocks.
        if (!WinHttpSetTimeouts(session_, 3000, 3000, 30000, 3000)) {
            DWORD error = GetLastError();
            Close();
            SetLastError(error);
            return false;
        }
        connect_ = WinHttpConnect(session_, kHost, INTERNET_DEFAULT_HTTPS_PORT, 0);
        return connect_ != nullptr;
    }

    void Close() {
        if (connect_) {
            WinHttpCloseHandle(connect_);
            connect_ = nullptr;
        }
        if (session_) {
            WinHttpCloseHandle(session_);
            session_ = nullptr;
        }
    }

    bool Get(PCWSTR path, std::wstring* body,
             const std::atomic<LONG>* stop,
             WINHTTP_CONNECTION_INFO* connectionInfo = nullptr) {
        DWORD status = 0;
        HINTERNET request = OpenRequest(L"GET", path);
        if (!request) {
            return false;
        }
        bool ok = SendAndReceive(request, 0, stop, &status);
        if (ok && connectionInfo) {
            *connectionInfo = {};
            connectionInfo->cbSize = sizeof(*connectionInfo);
            DWORD size = sizeof(*connectionInfo);
            if (!WinHttpQueryOption(request, WINHTTP_OPTION_CONNECTION_INFO,
                                    connectionInfo, &size)) {
                Wh_Log(L"WinHTTP connection info query failed (error %u)",
                       GetLastError());
            }
        }
        if (ok && body) {
            ok = ReadAll(request, body, stop);
        }
        WinHttpCloseHandle(request);
        return ok && status >= 200 && status < 300;
    }

    bool Download(PCWSTR path, TransferCounter* counter,
                  const std::atomic<LONG>* stop,
                  DWORD* statusOut) {
        DWORD status = 0;
        HINTERNET request = OpenRequest(L"GET", path);
        if (!request) {
            return false;
        }
        bool ok = SendAndReceive(request, 0, stop, &status);
        if (ok) {
            char buffer[64 * 1024];
            for (;;) {
                if (CancelRequested(stop) ||
                    counter->BudgetExceeded()) {
                    ok = false;
                    break;
                }
                DWORD read = 0;
                if (!WinHttpReadData(request, buffer, sizeof(buffer), &read)) {
                    ok = false;
                    break;
                }
                if (read == 0) {
                    break;
                }
                AddBytes(counter, read);
            }
        }
        WinHttpCloseHandle(request);
        if (statusOut) {
            *statusOut = status;
        }
        bool success = ok && status >= 200 && status < 300;
        return success;
    }

    bool Upload(PCWSTR path, const char* data, DWORD size,
                TransferCounter* counter, const std::atomic<LONG>* stop,
                DWORD* statusOut) {
        DWORD status = 0;
        HINTERNET request = OpenRequest(L"POST", path);
        if (!request) {
            return false;
        }

        wchar_t headers[] = L"Content-Type: application/octet-stream\r\n";
        bool ok = !CancelRequested(stop) &&
                  WinHttpSendRequest(request, headers, (DWORD)-1L,
                                     WINHTTP_NO_REQUEST_DATA, 0, size, 0) != FALSE;

        DWORD sentTotal = 0;
        const DWORD chunk = 32 * 1024;
        while (ok && sentTotal < size) {
            if (CancelRequested(stop) || counter->BudgetExceeded()) {
                ok = false;
                break;
            }
            DWORD part = std::min(chunk, size - sentTotal);
            DWORD written = 0;
            if (!WinHttpWriteData(request, data + sentTotal, part, &written) ||
                written == 0) {
                ok = false;
                break;
            }
            AddBytes(counter, written);
            sentTotal += written;
        }

        if (ok) {
            ok = WinHttpReceiveResponse(request, nullptr) != FALSE;
            if (ok) {
                DWORD sizeOfStatus = sizeof(status);
                ok = WinHttpQueryHeaders(
                         request,
                         WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                         WINHTTP_HEADER_NAME_BY_INDEX, &status, &sizeOfStatus,
                         WINHTTP_NO_HEADER_INDEX) != FALSE;
            }
        }
        if (CancelRequested(stop)) {
            ok = false;
        }

        WinHttpCloseHandle(request);
        if (statusOut) {
            *statusOut = status;
        }
        bool success = ok && status >= 200 && status < 300;
        return success;
    }

private:
    HINTERNET OpenRequest(PCWSTR method, PCWSTR path) {
        if (!connect_) {
            return nullptr;
        }
        return WinHttpOpenRequest(connect_, method, path, nullptr, WINHTTP_NO_REFERER,
                                  WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    }

    bool SendAndReceive(HINTERNET request, DWORD bodySize,
                        const std::atomic<LONG>* stop,
                        DWORD* statusOut) {
        if (CancelRequested(stop)) {
            return false;
        }
        wchar_t headers[] = L"Cache-Control: no-cache\r\n";
        if (!WinHttpSendRequest(request, headers, (DWORD)-1L, WINHTTP_NO_REQUEST_DATA,
                                bodySize, 0, 0)) {
            return false;
        }
        if (CancelRequested(stop)) {
            return false;
        }
        if (!WinHttpReceiveResponse(request, nullptr)) {
            return false;
        }
        if (CancelRequested(stop)) {
            return false;
        }
        DWORD status = 0;
        DWORD size = sizeof(status);
        if (!WinHttpQueryHeaders(
                request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                WINHTTP_HEADER_NAME_BY_INDEX, &status, &size,
                WINHTTP_NO_HEADER_INDEX)) {
            return false;
        }
        if (statusOut) {
            *statusOut = status;
        }
        return true;
    }

    bool ReadAll(HINTERNET request, std::wstring* body,
                 const std::atomic<LONG>* stop) {
        std::string bytes;
        char buffer[16 * 1024];
        for (;;) {
            if (CancelRequested(stop)) {
                return false;
            }
            DWORD read = 0;
            if (!WinHttpReadData(request, buffer, sizeof(buffer), &read)) {
                return false;
            }
            if (read == 0) {
                break;
            }
            bytes.append(buffer, read);
        }
        body->assign(bytes.begin(), bytes.end());
        return true;
    }

    HINTERNET session_ = nullptr;
    HINTERNET connect_ = nullptr;
};

// ---------------------------------------------------------------------------
// Measurement phases
// ---------------------------------------------------------------------------

static constexpr int kDownloadChunk = 8'000'000;
static constexpr int kUploadChunk = 4'000'000;
static constexpr int kDownloadWorkers = 12;
static constexpr int kUploadWorkers = 8;
static constexpr int kTransferWarmupMs = 2000;
static constexpr int kTransferMeasureMs = 10000;
// Per-direction data budget. Warm-up and measured bytes both count. At or
// below ~340 Mbps the full 12 s window completes before the budget is spent
// and measurement is unchanged; faster lines end the phase as soon as the
// budget is exhausted and report bytes over the actual elapsed time, so the
// worst case for the whole test stays around 1 GB regardless of line speed.
static constexpr LONGLONG kTransferBudgetBytes = 512'000'000;
// Warm-up alone stops well before the full budget so that faster lines keep
// enough data left for a meaningful measured interval.
static constexpr LONGLONG kWarmupBudgetBytes = 128'000'000;
// Even when the budget ends a phase early, keep sampling for at least this
// long so the reported average is not just the initial ramp.
static constexpr int kTransferMinMeasureMs = 4000;
static constexpr int kLatencySamples = 12;
static constexpr int kLatencyWarmup = 2;

static std::wstring Widen(const std::string& text) {
    std::wstring result;
    result.reserve(text.size());
    for (unsigned char c : text) {
        result.push_back((wchar_t)c);
    }
    return result;
}

static void ReadTrace(std::wstring* server, std::wstring* ip, std::wstring* country,
                      ULONG* interfaceIndex,
                      ADDRESS_FAMILY* interfaceFamily) {
    if (interfaceIndex) {
        *interfaceIndex = 0;
    }
    if (interfaceFamily) {
        *interfaceFamily = AF_UNSPEC;
    }
    HttpClient client;
    if (!client.Open()) {
        return;
    }
    std::wstring body;
    WINHTTP_CONNECTION_INFO connectionInfo = {};
    if (!client.Get(L"/cdn-cgi/trace", &body, nullptr, &connectionInfo)) {
        return;
    }
    if (interfaceIndex) {
        *interfaceIndex = InterfaceIndexForLocalAddress(
            connectionInfo.LocalAddress, interfaceFamily);
    }

    size_t start = 0;
    while (start < body.size()) {
        size_t end = body.find(L'\n', start);
        if (end == std::wstring::npos) {
            end = body.size();
        }
        std::wstring line = body.substr(start, end - start);
        size_t eq = line.find(L'=');
        if (eq != std::wstring::npos) {
            std::wstring key = line.substr(0, eq);
            std::wstring value = line.substr(eq + 1);
            if (key == L"colo") {
                if (value.size() == 3 && value.find_first_not_of(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::wstring::npos)
                    *server = value;
            } else if (key == L"loc") {
                if (value.size() == 2 && value.find_first_not_of(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::wstring::npos)
                    *country = value;
            } else if (key == L"ip") {
                IN_ADDR ipv4{};
                IN6_ADDR ipv6{};
                if (InetPtonW(AF_INET, value.c_str(), &ipv4) == 1 ||
                    InetPtonW(AF_INET6, value.c_str(), &ipv6) == 1)
                    *ip = value;
            }
        }
        start = end + 1;
    }

}

// Time a small uncached request through WinHTTP so the latency probe follows
// the same proxy, DNS, IPv4/IPv6, and routing path as the transfer test.
static bool ProbeHttp(HttpClient& client, double* milliseconds) {
    LARGE_INTEGER frequency = {};
    LARGE_INTEGER started = {};
    if (!QueryPerformanceFrequency(&frequency) || frequency.QuadPart <= 0 ||
        !QueryPerformanceCounter(&started)) {
        return false;
    }

    wchar_t path[96];
    swprintf(path, 96, L"/cdn-cgi/trace?ping=%u", NextRandom());
    std::wstring body;
    bool ok = client.Get(path, &body, nullptr);

    LARGE_INTEGER finished = {};
    if (!ok || !QueryPerformanceCounter(&finished) ||
        finished.QuadPart <= started.QuadPart) {
        return false;
    }
    *milliseconds = (finished.QuadPart - started.QuadPart) * 1000.0 /
                    frequency.QuadPart;
    return true;
}

static void MeasureLatency(double* pingOut, double* jitterOut) {
    HttpClient client;
    if (!client.Open()) {
        DWORD error = GetLastError();
        Wh_Log(L"WinHTTP open failed for latency probe (error %u)", error);
        throw std::wstring(g_str->errConnect);
    }

    std::vector<double> samples;
    samples.reserve(kLatencySamples);
    int failures = 0;

    for (int i = 0; i < kLatencySamples; i++) {
        if (CancelRequested()) {
            throw std::wstring(g_str->errCanceled);
        }

        double milliseconds = 0;
        bool ok = ProbeHttp(client, &milliseconds);
        if (CancelRequested()) {
            throw std::wstring(g_str->errCanceled);
        }
        if (ok && i >= kLatencyWarmup) {
            samples.push_back(milliseconds);
        } else if (!ok) {
            failures++;
        }

        if (!samples.empty()) {
            double ping = Percentile(samples, 50);
            StateSetLatency(ping, true, 0, false);
        }
        StateSetCaption(g_str->ping);

        Sleep(30);
    }

    if (samples.empty()) {
        throw std::wstring(g_str->errPing);
    }

    double ping = Percentile(samples, 50);
    double jitter = 0;
    if (samples.size() > 1) {
        double total = 0;
        for (size_t i = 1; i < samples.size(); i++) {
            total += std::fabs(samples[i] - samples[i - 1]);
        }
        jitter = total / (samples.size() - 1);
    }

    if (failures > 0) {
        Wh_Log(L"%d latency probes failed", failures);
    }
    *pingOut = ping;
    *jitterOut = jitter;
}

struct DownloadJob {
    TransferCounter* counter;
    const std::atomic<LONG>* stop;
    DWORD requests;
    DWORD failures;
};

struct UploadJob {
    TransferCounter* counter;
    const std::atomic<LONG>* stop;
    const char* data;
    DWORD size;
    DWORD requests;
    DWORD failures;
};

static DWORD WINAPI DownloadWorker(LPVOID parameter) {
    auto* job = (DownloadJob*)parameter;
    HttpClient client;
    if (!client.Open()) {
        DWORD error = GetLastError();
        job->failures++;
        Wh_Log(L"Download worker could not open WinHTTP session (error %u)",
               error);
        return 0;
    }

    while (!CancelRequested(job->stop) && !job->counter->BudgetExceeded()) {
        wchar_t path[96];
        swprintf(path, 96, L"/__down?bytes=%d&r=%u", kDownloadChunk, NextRandom());
        DWORD status = 0;
        job->requests++;
        bool ok = client.Download(path, job->counter, job->stop, &status);
        if (!ok && !CancelRequested(job->stop)) {
            // A transfer cut short by the data budget is not a failure: the
            // request would have succeeded.
            if (job->counter->BudgetExceeded()) {
                break;
            }
            job->failures++;
            Sleep(status == 429 ? 500 : 250);
        }
    }
    return 0;
}

static DWORD WINAPI UploadWorker(LPVOID parameter) {
    auto* job = (UploadJob*)parameter;
    HttpClient client;
    if (!client.Open()) {
        DWORD error = GetLastError();
        job->failures++;
        Wh_Log(L"Upload worker could not open WinHTTP session (error %u)",
               error);
        return 0;
    }

    while (!CancelRequested(job->stop) && !job->counter->BudgetExceeded()) {
        DWORD status = 0;
        job->requests++;
        bool ok = client.Upload(L"/__up", job->data, job->size, job->counter,
                                job->stop, &status);
        if (!ok && !CancelRequested(job->stop)) {
            // A transfer cut short by the data budget is not a failure: the
            // request would have succeeded.
            if (job->counter->BudgetExceeded()) {
                break;
            }
            job->failures++;
            Sleep(status == 429 ? 500 : 250);
        }
    }
    return 0;
}

struct WorkerGroup {
    HANDLE* handles;
    int count;
    std::atomic<LONG>* stop;

    void Stop() {
        stop->store(1, std::memory_order_relaxed);
        for (int i = 0; i < count; i++) {
            if (handles[i]) {
                DWORD result = WaitForSingleObject(handles[i], INFINITE);
                if (result != WAIT_OBJECT_0) {
                    Wh_Log(L"Transfer worker wait failed (error %u)",
                           GetLastError());
                }
                CloseHandle(handles[i]);
                handles[i] = nullptr;
            }
        }
    }

    ~WorkerGroup() { Stop(); }
};

static bool TransferWorkerRunning(HANDLE* workers, int count) {
    for (int i = 0; i < count; i++) {
        if (WaitForSingleObject(workers[i], 0) == WAIT_TIMEOUT) {
            return true;
        }
    }
    return false;
}

static double MeasureTransfer(bool upload) {
    TransferCounter counter;
    counter.budget = kTransferBudgetBytes;
    std::atomic<LONG> stop = 0;

    const int workerCount = upload ? kUploadWorkers : kDownloadWorkers;
    HANDLE workers[kDownloadWorkers > kUploadWorkers ? kDownloadWorkers
                                                      : kUploadWorkers] = {};
    DownloadJob downloadJobs[kDownloadWorkers] = {};
    UploadJob uploadJobs[kUploadWorkers] = {};
    std::vector<char> uploadData;

    if (upload) {
        uploadData.resize(kUploadChunk);
        for (size_t i = 0; i < uploadData.size(); i++) {
            uploadData[i] = (char)(NextRandom() & 0xFF);
        }
    }

    WorkerGroup workerGroup = {workers, workerCount, &stop};
    for (int i = 0; i < workerCount; i++) {
        if (upload) {
            uploadJobs[i] = {&counter, &stop, uploadData.data(),
                             (DWORD)uploadData.size(), 0, 0};
            workers[i] = CreateThread(nullptr, 0, UploadWorker, &uploadJobs[i], 0, nullptr);
        } else {
            downloadJobs[i] = {&counter, &stop, 0, 0};
            workers[i] = CreateThread(nullptr, 0, DownloadWorker, &downloadJobs[i], 0, nullptr);
        }
        if (!workers[i]) {
            DWORD error = GetLastError();
            workerGroup.Stop();
            Wh_Log(L"Unable to create %s worker %d (error %u)",
                   upload ? L"upload" : L"download", i, error);
            throw std::wstring(g_str->errUnexpected);
        }
    }

    // Warm-up data is counted as it arrives, then excluded by taking a byte
    // baseline immediately before the measured interval. Warm-up also stops
    // early once its own budget is spent: the workers keep running and the
    // in-flight data flows into the measured window instead of exhausting the
    // total budget before it starts.
    ULONGLONG warmupStart = Now();
    while (Now() - warmupStart < kTransferWarmupMs) {
        if (CancelRequested()) {
            workerGroup.Stop();
            throw std::wstring(g_str->errCanceled);
        }
        bool anyWorkerRunning = TransferWorkerRunning(workers, workerCount);
        if (!anyWorkerRunning) {
            if (counter.BudgetExceeded()) {
                break;
            }
            workerGroup.Stop();
            throw std::wstring(upload ? g_str->errUpload : g_str->errDownload);
        }
        if (counter.BudgetExceeded() ||
            counter.bytes.load(std::memory_order_relaxed) >=
                kWarmupBudgetBytes) {
            break;
        }
        Sleep(100);
    }

    LONGLONG base = counter.bytes.load(std::memory_order_relaxed);
    ULONGLONG measuredStart = Now();
    // Time of the last byte that arrived: the result divides by the time the
    // transfer was actually moving data, not by the full window, so a phase
    // ended early by the budget is not diluted with idle tail time.
    ULONGLONG lastTraffic = measuredStart;
    LONGLONG prevTotal = base;
    std::deque<std::pair<ULONGLONG, LONGLONG>> window;
    std::vector<double> speeds;
    double current = 0;
    // Once the budget is spent the display stops updating: the tail after the
    // in-flight transfers drain is idle time and would otherwise paint a
    // meaningless drop toward zero on the gauge and the chart.
    bool budgetSpent = counter.BudgetExceeded();

    while (Now() - measuredStart < kTransferMeasureMs) {
        if (CancelRequested()) {
            workerGroup.Stop();
            throw std::wstring(g_str->errCanceled);
        }
        Sleep(100);

        ULONGLONG now = Now();
        LONGLONG total = counter.bytes.load(std::memory_order_relaxed);
        if (total > prevTotal) {
            lastTraffic = now;
            prevTotal = total;
        }
        if (!budgetSpent && counter.BudgetExceeded()) {
            budgetSpent = true;
        }
        window.push_back({now, total});
        while (window.size() > 2 && now - window.front().first > 1000) {
            window.pop_front();
        }
        if (window.size() >= 2) {
            double seconds = (window.back().first - window.front().first) / 1000.0;
            if (seconds > 0.05) {
                current = (window.back().second - window.front().second) * 8.0 /
                          seconds / 1'000'000.0;
            }
        }

        if (!budgetSpent) {
            StateSetCurrent(current);
            StateSetCaption(upload ? g_str->upload : g_str->download);
            StateAddSample(current, upload);
            if (current > 0 && Now() - measuredStart > 500) {
                speeds.push_back(current);
            }
        }

        // The budget can end the phase early on fast lines: once it is spent,
        // keep sampling while the in-flight transfers drain, and never end
        // before the minimum window so the average is not just the ramp.
        if (counter.BudgetExceeded() &&
            !TransferWorkerRunning(workers, workerCount) &&
            Now() - measuredStart >= kTransferMinMeasureMs) {
            break;
        }
    }

    LONGLONG total = counter.bytes.load(std::memory_order_relaxed);
    workerGroup.Stop();

    if (CancelRequested()) {
        throw std::wstring(g_str->errCanceled);
    }

    // Divide by the time the transfer was actually moving data. On the full
    // 10 s window this is effectively the same; on budget-shortened phases it
    // excludes the idle tail left after the in-flight transfers drained.
    double seconds = (lastTraffic - measuredStart) / 1000.0;
    long long bytes = total - base;
    if (bytes <= 0 || seconds <= 0) {
        throw std::wstring(upload
                               ? g_str->errUpload
                               : g_str->errDownload);
    }

    // Report exactly what the connection moved: total bytes over the measured
    // window. No percentile uplift and no multiplier, so the figure cannot be
    // inflated. The spread below is only diagnostic.
    double mbps = bytes * 8.0 / seconds / 1'000'000.0;
    Wh_Log(L"%s: %.1f Mbps measured avg (spread p10 %.1f / p50 %.1f / p90 %.1f)",
        upload ? L"upload" : L"download", mbps,
        speeds.empty() ? 0.0 : Percentile(speeds, 10),
        speeds.empty() ? 0.0 : Percentile(speeds, 50),
        speeds.empty() ? 0.0 : Percentile(speeds, 90));

    DWORD requests = 0;
    DWORD failures = 0;
    for (int i = 0; i < workerCount; i++) {
        requests += upload ? uploadJobs[i].requests : downloadJobs[i].requests;
        failures += upload ? uploadJobs[i].failures : downloadJobs[i].failures;
    }
    Wh_Log(L"%s: %u requests, %u failures, %.0f ms each (total window %.0f ms)",
        upload ? L"upload" : L"download", requests, failures,
        requests ? seconds * 1000.0 * workerCount / requests : 0.0,
        seconds * 1000.0);

    StateSetMeasured(upload, mbps);
    StateAddDataUsed(counter.bytes.load(std::memory_order_relaxed));
    // Do not append the window average to the chart: the chart shows the
    // 100 ms samples, and the average would appear as an artificial last point.
    return mbps;
}

static void RunTestWorker() {
    try {
        if (CancelRequested()) {
            throw std::wstring(g_str->errCanceled);
        }
        StateSetPhase(Phase::Warmup, g_str->connecting);

        std::wstring server = L"Cloudflare";
        ULONG interfaceIndex = 0;
        ADDRESS_FAMILY interfaceFamily = AF_UNSPEC;
        std::wstring ip, country;
        ReadTrace(&server, &ip, &country, &interfaceIndex, &interfaceFamily);
        StateSetServer(server, ip, country);
        if (interfaceIndex && g_flyoutHwnd) {
            PostMessageW(g_flyoutHwnd, WM_APP + 4, interfaceIndex,
                         interfaceFamily);
        }

        if (CancelRequested()) {
            throw std::wstring(g_str->errCanceled);
        }

        StateSetPhase(Phase::Latency, g_str->ping);
        double ping = 0;
        double jitter = 0;
        bool hasLatency = false;
        try {
            MeasureLatency(&ping, &jitter);
            hasLatency = true;
            StateSetLatency(ping, true, jitter, true);
        } catch (const std::wstring& error) {
            if (CancelRequested()) {
                throw;
            }
            Wh_Log(L"Latency unavailable; continuing with throughput test: %s",
                   error.c_str());
            StateSetLatency(0, false, 0, false);
        }

        if (CancelRequested()) {
            throw std::wstring(g_str->errCanceled);
        }

        StateSetPhase(Phase::Download, g_str->download);
        double download = MeasureTransfer(false);

        if (CancelRequested()) {
            throw std::wstring(g_str->errCanceled);
        }

        StateSetPhase(Phase::Upload, g_str->upload);
        double upload = MeasureTransfer(true);

        StateFinish(download, upload, ping, jitter, hasLatency);
        if (g_flyoutHwnd) {
            PostMessageW(g_flyoutHwnd, WM_APP + 1, 0, 0);
        }
    } catch (const std::wstring& error) {
        if (CancelRequested()) {
            StateCanceled();
        } else {
            StateFail(error);
        }
        if (g_flyoutHwnd) {
            PostMessageW(g_flyoutHwnd, WM_APP + 1, 0, 0);
        }
    } catch (...) {
        if (CancelRequested()) {
            StateCanceled();
        } else {
            StateFail(g_str->errUnexpected);
        }
        if (g_flyoutHwnd) {
            PostMessageW(g_flyoutHwnd, WM_APP + 1, 0, 0);
        }
    }
}

static DWORD WINAPI TestWorkerThread(LPVOID) {
    RunTestWorker();
    return 0;
}

// ---------------------------------------------------------------------------
// Direct2D surface
// ---------------------------------------------------------------------------

static ID2D1Factory* g_d2dFactory = nullptr;
static IDWriteFactory* g_dwriteFactory = nullptr;
static ID2D1RenderTarget* g_renderTarget = nullptr;
static ID2D1HwndRenderTarget* g_hwndTarget = nullptr;
static ID2D1StrokeStyle* g_roundStroke = nullptr;

// DirectComposition path. It is always attempted first because the flyout
// window keeps WS_EX_NOREDIRECTIONBITMAP, so an ID2D1HwndRenderTarget has no
// redirection surface to present into; the HWND target below is only reached
// if D3D/DComp is unavailable (e.g. no GPU and no WARP). When the system
// transparency setting is off, the composition surface is painted with a
// solid background instead of showing the DWM backdrop through.
static bool g_composition = false;
static ID3D11Device* g_d3dDevice = nullptr;
static IDXGIDevice* g_dxgiDevice = nullptr;
static IDXGISwapChain1* g_swapChain = nullptr;
static IDCompositionDevice* g_dcompDevice = nullptr;
static IDCompositionTarget* g_dcompTarget = nullptr;
static IDCompositionVisual* g_dcompVisual = nullptr;
// Open and close animation: the root visual's opacity and vertical offset,
// played by the compositor so it never waits on the UI thread.
static IDCompositionEffectGroup* g_dcompEffect = nullptr;
static IDCompositionAnimation* g_motionOpacity = nullptr;
static IDCompositionAnimation* g_motionOffset = nullptr;
static ID2D1DeviceContext* g_context = nullptr;
static ID2D1Bitmap1* g_contextBitmap = nullptr;
static UINT g_targetWidth = 0;
static UINT g_targetHeight = 0;
static float g_targetDpi = 0;

// Acrylic grain. Windows paints a very faint noise texture over the material to
// hide banding in the blur. DWM's backdrop carries its own, but the dark tint
// flattens it, so an equivalent texture is drawn here (below the content).
static ID2D1Bitmap* g_noiseBitmap = nullptr;
static ID2D1BitmapBrush* g_noiseBrush = nullptr;
static constexpr int kNoiseSize = 128;
static constexpr float kNoiseOpacity = 0.06f;

static Palette g_palette = {};
static bool g_dark = true;
static bool g_systemLight = false;
static bool g_transparencyEnabled = false;
static bool g_materialSupported = false;
static bool g_translucent = false;
static float g_dpi = 96.0f;
static float g_scale = 1.0f;

// Re-reads everything that decides the surface look. Called when the window is
// opened and when Windows reports a theme/transparency change, never from the
// render loop.
static void RefreshAppearance() {
    // Dark is pinned: the house look never follows the system theme. The
    // system read stays only so a future light variant has the plumbing.
    ReadSystemLightTheme();
    g_systemLight = false;
    g_dark = true;
    g_palette = MakePalette(false);
    g_transparencyEnabled = ReadTransparencyEnabled();
    g_materialSupported = MaterialSupported();
    g_translucent = g_materialSupported && g_transparencyEnabled;
}

// Edges we draw sit on the live corner radius: the custom-corner-radius
// mod's radius (16 here) scaled by DPI. Cards take the window radius minus
// their inset, controls the small radius. Never a hard-coded 8.
static float WindowRadius() {
    DWORD radius = 0;
    DWORD size = sizeof(radius);
    RegGetValueW(HKEY_LOCAL_MACHINE,
                 L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius\\Settings",
                 L"radius", RRF_RT_REG_DWORD, nullptr, &radius, &size);
    return radius > 0 && radius <= 64 ? static_cast<float>(radius) : 8.0f;
}

static float CardRadius() {
    return std::max(6.0f, WindowRadius() - 4.0f);
}

static float ControlRadius() {
    return std::max(4.0f, WindowRadius() * 0.5f);
}

struct TextKey {
    float size;
    int weight;
    int align;
    int valign;
    bool wrap;
    int family;
    bool english;

    bool operator==(const TextKey& other) const {
        return size == other.size && weight == other.weight &&
               align == other.align && valign == other.valign &&
               wrap == other.wrap && family == other.family &&
               english == other.english;
    }
};

static std::vector<std::pair<TextKey, IDWriteTextFormat*>> g_textFormats;

static PCWSTR FamilyName(int family) {
    switch (family) {
        case 1:
            return kDisplayFamily;
        case 2:
            return kIconFamily;
        default:
            return kTextFamily;
    }
}

static IDWriteTextFormat* GetTextFormat(float size, DWRITE_FONT_WEIGHT weight,
                                        DWRITE_TEXT_ALIGNMENT align,
                                        DWRITE_PARAGRAPH_ALIGNMENT valign,
                                        bool wrap, int family) {
    bool english = g_str == &kStringsEn;
    if (family != 2) weight = DWRITE_FONT_WEIGHT_MEDIUM;
    TextKey key = {size, (int)weight, (int)align, (int)valign, wrap, family,
                   english};
    for (const auto& entry : g_textFormats) {
        if (entry.first == key) {
            return entry.second;
        }
    }
    if (!g_dwriteFactory) {
        return nullptr;
    }

    IDWriteTextFormat* format = nullptr;
    if (FAILED(g_dwriteFactory->CreateTextFormat(
            FamilyName(family), nullptr, weight, DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL, size,
            english ? L"en-US" : L"it-IT", &format))) {
        return nullptr;
    }
    format->SetTextAlignment(align);
    format->SetParagraphAlignment(valign);
    format->SetWordWrapping(wrap ? DWRITE_WORD_WRAPPING_WRAP
                                 : DWRITE_WORD_WRAPPING_NO_WRAP);
    g_textFormats.push_back({key, format});
    return format;
}

static D2D1_RECT_F Rect(float left, float top, float right, float bottom) {
    D2D1_RECT_F r;
    r.left = left;
    r.top = top;
    r.right = right;
    r.bottom = bottom;
    return r;
}

struct BrushEntry {
    D2D1_COLOR_F color;
    ID2D1SolidColorBrush* brush;
};

static std::vector<BrushEntry> g_brushes;

static bool SameColor(D2D1_COLOR_F a, D2D1_COLOR_F b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

static void ReleaseBrushes() {
    for (auto& entry : g_brushes) {
        entry.brush->Release();
    }
    g_brushes.clear();
}

// Brushes are cached per colour and handed out with an extra AddRef, so the
// call sites can keep releasing the returned brush.
static ID2D1SolidColorBrush* Brush(D2D1_COLOR_F color) {
    if (!g_renderTarget) {
        return nullptr;
    }
    for (const auto& entry : g_brushes) {
        if (SameColor(entry.color, color)) {
            entry.brush->AddRef();
            return entry.brush;
        }
    }
    if (g_brushes.size() >= 128) {
        ReleaseBrushes();
    }
    ID2D1SolidColorBrush* brush = nullptr;
    if (FAILED(g_renderTarget->CreateSolidColorBrush(color, &brush))) {
        return nullptr;
    }
    g_brushes.push_back({color, brush});
    brush->AddRef();
    return brush;
}

static void FillRounded(D2D1_RECT_F rect, float radius, D2D1_COLOR_F color) {
    ID2D1SolidColorBrush* brush = Brush(color);
    if (!brush) {
        return;
    }
    D2D1_ROUNDED_RECT rr = {rect, radius, radius};
    g_renderTarget->FillRoundedRectangle(rr, brush);
    brush->Release();
}

static void StrokeRounded(D2D1_RECT_F rect, float radius, D2D1_COLOR_F color,
                          float width = 1.0f) {
    ID2D1SolidColorBrush* brush = Brush(color);
    if (!brush) {
        return;
    }
    D2D1_ROUNDED_RECT rr = {rect, radius, radius};
    g_renderTarget->DrawRoundedRectangle(rr, brush, width);
    brush->Release();
}

// The house hover edge: the same 2 px, the blue to mauve gradient at 45
// degrees, so the edge never jumps when the pointer arrives.
static void StrokeGradient(D2D1_RECT_F rect, float radius, float width = 2.0f,
                           UINT32 start = 0x89B4FA, UINT32 end = 0xCBA6F7,
                           bool diagonal45 = false) {
    if (!g_renderTarget) {
        return;
    }
    D2D1_GRADIENT_STOP stops[2] = {{0.0f, Col(start)}, {1.0f, Col(end)}};
    ID2D1GradientStopCollection* collection = nullptr;
    if (FAILED(g_renderTarget->CreateGradientStopCollection(
            stops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &collection))) {
        return;
    }
    ID2D1LinearGradientBrush* brush = nullptr;
    D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES props = {};
    props.startPoint = {rect.left, rect.top};
    props.endPoint = {rect.right, rect.bottom};
    if (diagonal45) {
        float span = ((rect.right - rect.left) + (rect.bottom - rect.top)) / 2.0f;
        props.endPoint = {rect.left + span, rect.top + span};
    }
    D2D1_BRUSH_PROPERTIES brushProps = {};
    brushProps.opacity = 1.0f;
    brushProps.transform = D2D1::IdentityMatrix();
    if (SUCCEEDED(g_renderTarget->CreateLinearGradientBrush(
            &props, &brushProps, collection, &brush))) {
        D2D1_ROUNDED_RECT rr = {rect, radius, radius};
        g_renderTarget->DrawRoundedRectangle(rr, brush, width);
        brush->Release();
    }
    collection->Release();
}

// WinUI focus visual: a 2 px neutral ring around the control, offset by 1 px
// so it never sits on the control's own border, plus a 1 px inner stroke in
// the opposite tone, as in the system focus visuals. The ring is deliberately
// neutral (light-on-dark / dark-on-light), not the accent color.
static void DrawFocusRing(D2D1_RECT_F rect, float radius, float alpha) {
    D2D1_RECT_F outer = Rect(rect.left - 3.0f, rect.top - 3.0f,
                             rect.right + 3.0f, rect.bottom + 3.0f);
    D2D1_COLOR_F ring = WithAlpha(g_palette.text, alpha);
    D2D1_COLOR_F inner = g_systemLight ? Col(0xFFFFFF, alpha)
                                       : Col(0x000000, alpha);
    StrokeRounded(outer, radius + 3.0f, ring, 2.0f);
    StrokeRounded(Rect(outer.left + 1.0f, outer.top + 1.0f, outer.right - 1.0f,
                       outer.bottom - 1.0f),
                  radius + 2.0f, inner, 1.0f);
}

static void FillRect(D2D1_RECT_F rect, D2D1_COLOR_F color) {
    ID2D1SolidColorBrush* brush = Brush(color);
    if (!brush) {
        return;
    }
    g_renderTarget->FillRectangle(rect, brush);
    brush->Release();
}

static void ReleaseNoise() {
    if (g_noiseBrush) {
        g_noiseBrush->Release();
        g_noiseBrush = nullptr;
    }
    if (g_noiseBitmap) {
        g_noiseBitmap->Release();
        g_noiseBitmap = nullptr;
    }
}

// Builds the grain once per render target. Values are centred on the dark
// palette colour and painted at a very low opacity, so the average colour does
// not shift: only ~2 levels of texture, like the shell material.
static bool EnsureNoise() {
    if (g_noiseBrush) {
        return true;
    }
    if (!g_renderTarget) {
        return false;
    }

    std::vector<UINT32> pixels((size_t)kNoiseSize * kNoiseSize);
    UINT32 state = 0x9E3779B9u;
    for (auto& pixel : pixels) {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        int level = 0x2C + (int)(state % 61) - 30;
        if (level < 0) {
            level = 0;
        } else if (level > 255) {
            level = 255;
        }
        pixel = 0xFF000000u | ((UINT32)level << 16) | ((UINT32)level << 8) |
                (UINT32)level;
    }

    D2D1_BITMAP_PROPERTIES props = {};
    props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
    props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
    props.dpiX = 96.0f;
    props.dpiY = 96.0f;
    if (FAILED(g_renderTarget->CreateBitmap(
            D2D1::SizeU(kNoiseSize, kNoiseSize), pixels.data(),
            kNoiseSize * sizeof(UINT32), &props, &g_noiseBitmap))) {
        return false;
    }

    D2D1_BITMAP_BRUSH_PROPERTIES brushProps = {};
    brushProps.extendModeX = D2D1_EXTEND_MODE_WRAP;
    brushProps.extendModeY = D2D1_EXTEND_MODE_WRAP;
    brushProps.interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
    if (FAILED(g_renderTarget->CreateBitmapBrush(g_noiseBitmap, &brushProps,
                                                nullptr, &g_noiseBrush))) {
        ReleaseNoise();
        return false;
    }
    return true;
}

static void DrawLine(float x1, float y1, float x2, float y2, D2D1_COLOR_F color,
                     float width = 1.0f) {
    ID2D1SolidColorBrush* brush = Brush(color);
    if (!brush) {
        return;
    }
    g_renderTarget->DrawLine({x1, y1}, {x2, y2}, brush, width);
    brush->Release();
}

static void FillCircle(float cx, float cy, float radius, D2D1_COLOR_F color) {
    ID2D1SolidColorBrush* brush = Brush(color);
    if (!brush) {
        return;
    }
    D2D1_ELLIPSE ellipse = {{cx, cy}, radius, radius};
    g_renderTarget->FillEllipse(ellipse, brush);
    brush->Release();
}

static void Text(const std::wstring& text, D2D1_RECT_F rect, float size,
                 D2D1_COLOR_F color, DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL,
                 DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING,
                 DWRITE_PARAGRAPH_ALIGNMENT valign = DWRITE_PARAGRAPH_ALIGNMENT_NEAR,
                 int family = 0, bool wrap = false, bool tabular = false) {
    if (text.empty()) {
        return;
    }
    IDWriteTextFormat* format = GetTextFormat(size, weight, align, valign, wrap, family);
    ID2D1SolidColorBrush* brush = Brush(color);
    if (!format || !brush) {
        if (brush) {
            brush->Release();
        }
        return;
    }

    if (!tabular || !g_dwriteFactory) {
        g_renderTarget->DrawTextW(text.c_str(), (UINT32)text.size(), format, rect, brush,
                                  D2D1_DRAW_TEXT_OPTIONS_NONE);
        brush->Release();
        return;
    }

    IDWriteTextLayout* layout = nullptr;
    if (FAILED(g_dwriteFactory->CreateTextLayout(
            text.c_str(), (UINT32)text.size(), format,
            std::max(1.0f, rect.right - rect.left), std::max(1.0f, rect.bottom - rect.top),
            &layout))) {
        brush->Release();
        return;
    }
    // Tabular figures keep the width of every digit identical, so a live value
    // does not jitter while it changes. The layout is drawn from the rect's
    // top-left corner; alignment still comes from the text format.
    IDWriteTypography* typography = nullptr;
    if (SUCCEEDED(g_dwriteFactory->CreateTypography(&typography))) {
        DWRITE_FONT_FEATURE feature = {DWRITE_FONT_FEATURE_TAG_TABULAR_FIGURES, 1};
        typography->AddFontFeature(feature);
        layout->SetTypography(typography, {0, (UINT32)text.size()});
        typography->Release();
    }
    g_renderTarget->DrawTextLayout({rect.left, rect.top}, layout, brush,
                                   D2D1_DRAW_TEXT_OPTIONS_NONE);
    layout->Release();
    brush->Release();
}

static float MeasureWidth(const std::wstring& text, float size,
                          DWRITE_FONT_WEIGHT weight, int family = 0,
                          bool tabular = false) {
    if (!g_dwriteFactory || text.empty()) {
        return 0;
    }
    IDWriteTextFormat* format = GetTextFormat(size, weight,
                                              DWRITE_TEXT_ALIGNMENT_LEADING,
                                              DWRITE_PARAGRAPH_ALIGNMENT_NEAR,
                                              false, family);
    if (!format) {
        return 0;
    }
    IDWriteTextLayout* layout = nullptr;
    if (FAILED(g_dwriteFactory->CreateTextLayout(
            text.c_str(), (UINT32)text.size(), format, 1000, 1000, &layout))) {
        return 0;
    }
    // A tabular measure must use the same typography as the drawing, or the
    // measured width drifts away from the rendered one (proportional digits
    // such as "1" are narrower than their tabular cell).
    if (tabular) {
        IDWriteTypography* typography = nullptr;
        if (SUCCEEDED(g_dwriteFactory->CreateTypography(&typography))) {
            DWRITE_FONT_FEATURE feature = {DWRITE_FONT_FEATURE_TAG_TABULAR_FIGURES, 1};
            typography->AddFontFeature(feature);
            layout->SetTypography(typography, {0, (UINT32)text.size()});
            typography->Release();
        }
    }
    DWRITE_TEXT_METRICS metrics = {};
    layout->GetMetrics(&metrics);
    layout->Release();
    return metrics.width;
}

// Distance between the top of a single-line layout and its baseline. Used to
// align two texts of different sizes on the same baseline (value + unit)
// instead of aligning their box bottoms, which made the unit drift down under
// short glyphs such as the em dash placeholder.
static float BaselineOffset(float size, int family = 0) {
    if (!g_dwriteFactory) {
        return size * 0.9f;
    }
    IDWriteTextFormat* format = GetTextFormat(size, DWRITE_FONT_WEIGHT_NORMAL,
                                              DWRITE_TEXT_ALIGNMENT_LEADING,
                                              DWRITE_PARAGRAPH_ALIGNMENT_NEAR,
                                              false, family);
    if (!format) {
        return size * 0.9f;
    }
    float baseline = size * 0.9f;
    IDWriteTextLayout* layout = nullptr;
    if (SUCCEEDED(g_dwriteFactory->CreateTextLayout(L"0", 1, format, 1000, 1000,
                                                    &layout))) {
        DWRITE_LINE_METRICS metrics = {};
        UINT32 count = 0;
        if (SUCCEEDED(layout->GetLineMetrics(&metrics, 1, &count)) && count > 0) {
            baseline = metrics.baseline;
        }
        layout->Release();
    }
    return baseline;
}

// Fits a single line of text into maxWidth, appending an ellipsis only when the
// full string does not fit: SSIDs and adapter descriptions can be longer than
// the footline, and cutting them at a fixed character count would hide part of
// the name.
static std::wstring Ellipsize(const std::wstring& text, float maxWidth, float size,
                              DWRITE_FONT_WEIGHT weight, int family = 0) {
    if (text.empty() || MeasureWidth(text, size, weight, family) <= maxWidth) {
        return text;
    }
    std::wstring result = text;
    while (!result.empty() &&
           MeasureWidth(result + L"\x2026", size, weight, family) > maxWidth) {
        result.pop_back();
    }
    return result + L"\x2026";
}

static ID2D1PathGeometry* CreateArcPath(float cx, float cy, float radius,
                                        float startDegrees, float sweepDegrees) {
    if (!g_d2dFactory || sweepDegrees <= 0.1f) {
        return nullptr;
    }

    ID2D1PathGeometry* geometry = nullptr;
    if (FAILED(g_d2dFactory->CreatePathGeometry(&geometry))) {
        return nullptr;
    }
    ID2D1GeometrySink* sink = nullptr;
    if (FAILED(geometry->Open(&sink))) {
        geometry->Release();
        return nullptr;
    }

    const float pi = 3.14159265358979323846f;
    auto point = [&](float angle) {
        float radians = angle * pi / 180.0f;
        return D2D1_POINT_2F{cx + radius * cosf(radians), cy + radius * sinf(radians)};
    };

    sink->BeginFigure(point(startDegrees), D2D1_FIGURE_BEGIN_HOLLOW);
    D2D1_ARC_SEGMENT arc = {};
    arc.point = point(startDegrees + sweepDegrees);
    arc.size = {radius, radius};
    arc.rotationAngle = 0;
    arc.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
    arc.arcSize = sweepDegrees > 180.0f ? D2D1_ARC_SIZE_LARGE : D2D1_ARC_SIZE_SMALL;
    sink->AddArc(arc);
    sink->EndFigure(D2D1_FIGURE_END_OPEN);
    sink->Close();
    sink->Release();
    return geometry;
}

static void DrawArc(float cx, float cy, float radius, float fraction,
                    D2D1_COLOR_F color, float width) {
    ID2D1PathGeometry* path = CreateArcPath(cx, cy, radius, 135.0f, 270.0f * fraction);
    if (!path) {
        return;
    }
    ID2D1SolidColorBrush* brush = Brush(color);
    if (brush) {
        g_renderTarget->DrawGeometry(path, brush, width, g_roundStroke);
        brush->Release();
    }
    path->Release();
}

// ---------------------------------------------------------------------------
// Chart
// ---------------------------------------------------------------------------

static ID2D1PathGeometry* BuildSeriesPath(const std::vector<double>& values,
                                          float left, float right, float axisMax,
                                          float baseline, float top, bool area) {
    if (values.size() < 2 || right - left < 2 || !g_d2dFactory) {
        return nullptr;
    }

    ID2D1PathGeometry* geometry = nullptr;
    if (FAILED(g_d2dFactory->CreatePathGeometry(&geometry))) {
        return nullptr;
    }
    ID2D1GeometrySink* sink = nullptr;
    if (FAILED(geometry->Open(&sink))) {
        geometry->Release();
        return nullptr;
    }

    float span = right - left;
    auto y = [&](double value) {
        double fraction = Clamp(value / axisMax, 0, 1);
        return baseline - (float)fraction * (baseline - top);
    };

    if (area) {
        sink->BeginFigure({left, baseline}, D2D1_FIGURE_BEGIN_FILLED);
        for (size_t i = 0; i < values.size(); i++) {
            float t = (float)i / (float)(values.size() - 1);
            sink->AddLine({left + span * t, y(values[i])});
        }
        sink->AddLine({right, baseline});
        sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    } else {
        sink->BeginFigure({left, y(values[0])}, D2D1_FIGURE_BEGIN_HOLLOW);
        for (size_t i = 1; i < values.size(); i++) {
            float t = (float)i / (float)(values.size() - 1);
            sink->AddLine({left + span * t, y(values[i])});
        }
        sink->EndFigure(D2D1_FIGURE_END_OPEN);
    }

    sink->Close();
    sink->Release();
    return geometry;
}

static void DrawChart(const std::vector<Sample>& samples,
                      D2D1_RECT_F area, float alpha) {
    if (samples.size() < 2) {
        return;
    }

    std::vector<double> down;
    std::vector<double> up;
    double downPeak = 0;
    double upPeak = 0;
    for (const auto& sample : samples) {
        if (sample.upload) {
            upPeak = std::max(upPeak, sample.value);
            up.push_back(sample.value);
        } else {
            downPeak = std::max(downPeak, sample.value);
            down.push_back(sample.value);
        }
    }
    // Both curves share one scale so the two halves can be compared at a
    // glance; with two independent axes a 200 Mbps upload looked as tall as a
    // 900 Mbps download.
    double axis = ChartAxisMax(std::max(std::max(downPeak, upPeak), 1.0));

    const float top = area.top + 17;
    const float baseline = area.bottom - 3;
    const float width = area.right - area.left;

    DrawLine(area.left, top, area.right, top,
             WithAlpha(g_palette.cardStroke, alpha * 2.0f));
    DrawLine(area.left, (top + baseline) / 2, area.right, (top + baseline) / 2,
             WithAlpha(g_palette.cardStroke, alpha * 2.0f));
    DrawLine(area.left, baseline, area.right, baseline,
             WithAlpha(g_palette.cardStroke, alpha * 2.4f));

    bool hasDown = down.size() >= 2;
    bool hasUp = up.size() >= 2;
    if (!hasDown && !hasUp) {
        return;
    }

    float downLeft = area.left;
    float downRight = area.right;
    float upLeft = area.left;
    float upRight = area.right;
    if (hasDown && hasUp) {
        // Download and upload have very different ranges. Each series keeps its
        // own half of the chart, but both use the shared `axis` above so their
        // heights are comparable.
        float zone = (width - 16) / 2;
        downRight = area.left + zone;
        upLeft = area.left + zone + 16;
    } else if (!hasUp) {
        upLeft = area.right;
    } else {
        downRight = area.left;
    }

    if (hasDown) {
        ID2D1PathGeometry* fill = BuildSeriesPath(down, downLeft, downRight, (float)axis,
                                                  baseline, top, true);
        if (fill) {
            ID2D1SolidColorBrush* brush = Brush(WithAlpha(g_palette.download, alpha * 0.10f));
            if (brush) {
                g_renderTarget->FillGeometry(fill, brush);
                brush->Release();
            }
            fill->Release();
        }
        ID2D1PathGeometry* line = BuildSeriesPath(down, downLeft, downRight, (float)axis,
                                                  baseline, top, false);
        if (line) {
            ID2D1SolidColorBrush* brush = Brush(WithAlpha(g_palette.download, alpha));
            if (brush) {
                g_renderTarget->DrawGeometry(line, brush, 2.0f, g_roundStroke);
                brush->Release();
            }
            line->Release();
        }
    }

    if (hasUp) {
        ID2D1PathGeometry* fill = BuildSeriesPath(up, upLeft, upRight, (float)axis,
                                                  baseline, top, true);
        if (fill) {
            ID2D1SolidColorBrush* brush = Brush(WithAlpha(g_palette.upload, alpha * 0.10f));
            if (brush) {
                g_renderTarget->FillGeometry(fill, brush);
                brush->Release();
            }
            fill->Release();
        }
        ID2D1PathGeometry* line = BuildSeriesPath(up, upLeft, upRight, (float)axis,
                                                  baseline, top, false);
        if (line) {
            ID2D1SolidColorBrush* brush = Brush(WithAlpha(g_palette.upload, alpha));
            if (brush) {
                g_renderTarget->DrawGeometry(line, brush, 2.0f, g_roundStroke);
                brush->Release();
            }
            line->Release();
        }
    }

    if (hasDown || hasUp) {
        Text(FormatScale(axis) + L" Mbps",
             Rect(area.left, area.top - 4, area.right, area.top + 12), 10,
             WithAlpha(g_palette.tertiary, alpha), DWRITE_FONT_WEIGHT_NORMAL,
             DWRITE_TEXT_ALIGNMENT_LEADING);
    }
}

// ---------------------------------------------------------------------------
// Flyout UI state and drawing
// ---------------------------------------------------------------------------

enum class View {
    Gauge,
    Results,
    Error,
};

enum class Hot {
    None,
    Start,
    Copy,
    Close,
    Settings,
    Retry,
};

static View g_view = View::Gauge;
static View g_animFrom = View::Gauge;
static bool g_animating = false;
static ULONGLONG g_animStart = 0;
// Material state. DWM applies DWMWA_SYSTEMBACKDROP_TYPE asynchronously and
// there is no query for "the material is attached", so the first frames are
// painted with an opaque scrim that then fades out. The attribute is always
// set to NONE while the window is hidden, so showing it is a real state change
// and DWM is guaranteed to recompute the material.
static ULONGLONG g_scrimFadeAt = 0;

static constexpr float kScrimSettleMs = 60.0f;
static constexpr float kScrimFadeMs = 200.0f;

// The house glass over DWM's Desktop Acrylic: a Mocha fill at 0.80, so no
// text behind the flyout ever reads through. A window that lost the material
// falls back to the same colour opaque (the scrim alpha of 1).
static constexpr float kMochaTintAlpha = 0.80f;

static bool ScrimFading() {
    // The extra 50 ms forces one final frame at alpha 0 after the fade, so the
    // surface is never left with the last interpolated (non-zero) alpha.
    return g_scrimFadeAt &&
           Now() - g_scrimFadeAt <
               (ULONGLONG)(kScrimSettleMs + kScrimFadeMs + 50.0f);
}

static float ScrimAlpha() {
    if (!g_scrimFadeAt) {
        return 1.0f;
    }
    float elapsed = (float)(Now() - g_scrimFadeAt);
    if (elapsed <= kScrimSettleMs) {
        return 1.0f;
    }
    float t = (elapsed - kScrimSettleMs) / kScrimFadeMs;
    if (t >= 1.0f) {
        return 0.0f;
    }
    // Ease-out: the material is already there, the scrim just dissolves.
    float eased = 1.0f - (1.0f - t) * (1.0f - t);
    return 1.0f - eased;
}

static ULONGLONG g_copyUntil = 0;
static double g_gaugeShown = 0;
static Hot g_hot = Hot::None;
static Hot g_pressed = Hot::None;
static Hot g_focus = Hot::None;
static NetworkInfo g_network;
static bool g_uiVisible = false;
static HWND g_previousForeground = nullptr;
static UINT g_mouseButtonsDown = 0;

static HANDLE g_uiThread = nullptr;
static DWORD g_uiThreadId = 0;
static volatile LONG g_shutdown = 0;

static UINT MouseButtonsDown() {
    constexpr int buttons[] = {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1,
                               VK_XBUTTON2};
    UINT state = 0;
    for (size_t i = 0; i < ARRAYSIZE(buttons); i++) {
        if (GetAsyncKeyState(buttons[i]) & 0x8000) {
            state |= 1u << i;
        }
    }
    return state;
}

// Fluent motion is 167-250 ms; 250 ms keeps the transitions readable while
// staying in the range of the shell flyouts. Users who turn "Animation
// effects" off get an instant swap.
static constexpr float kAnimMs = 250.0f;
static constexpr D2D1_RECT_F kSettingsRect = {316.0f, 9.0f, 348.0f, 39.0f};
static constexpr D2D1_RECT_F kCloseRect = {352.0f, 9.0f, 384.0f, 39.0f};
static constexpr D2D1_RECT_F kCopyRect = {292.0f, 60.0f, 364.0f, 86.0f};
static constexpr D2D1_RECT_F kCardRect = {20.0f, 48.0f, 380.0f, 372.0f};
// Error layout, authored for the 340 px window: the card ends 44 px above the
// bottom so the footline keeps its usual place underneath.
static constexpr D2D1_RECT_F kErrorRect = {20.0f, 56.0f, 380.0f, 296.0f};
static constexpr D2D1_RECT_F kRetryRect = {144.0f, 230.0f, 256.0f, 262.0f};

// Height the window is laid out at right now. It animates between
// ViewHeight() values; every rect below the content top reads it.
static float g_layoutHeight = kGaugeHeight;
static float g_heightFrom = kGaugeHeight;

static constexpr float kDetailRow = 24.0f;
static constexpr PCWSTR kDetailLabels[] = {L"Network", L"Test server", L"Public IP", L"Country"};
static int g_hoverDetail = -1;
static unsigned g_clickedDetails = 0;
static float g_detailOpacity[4] = {};
static ULONGLONG g_detailTick = 0;

static int DetailCount() {
    int count = 0;
    for (size_t i = 0; i < ARRAYSIZE(kDetailLabels); ++i)
        count += DetailDisplay(i) != DetailMode::Hidden;
    return count;
}

static float ViewHeight(View view) {
    float height = view == View::Error ? kErrorHeight : kGaugeHeight;
    return height + (DetailCount() - 1) * kDetailRow;
}

static D2D1_RECT_F DetailRect(int row) {
    float top = g_layoutHeight - 10.0f - (DetailCount() - row) * kDetailRow;
    return Rect(20, top, 380, top + kDetailRow);
}

static int DetailAt(float x, float y) {
    int row = 0;
    for (size_t i = 0; i < ARRAYSIZE(kDetailLabels); ++i) {
        if (DetailDisplay(i) == DetailMode::Hidden) continue;
        auto rect = DetailRect(row++);
        if (x >= 145 && x < rect.right && y >= rect.top && y < rect.bottom)
            return static_cast<int>(i);
    }
    return -1;
}

static void ResetDetailReveal() {
    g_hoverDetail = -1;
    g_clickedDetails = 0;
    g_detailTick = 0;
    std::fill(std::begin(g_detailOpacity), std::end(g_detailOpacity), 0.0f);
}

static bool AnimationsEnabled() {
    BOOL enabled = TRUE;
    if (!SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &enabled, 0)) {
        return true;
    }
    return enabled != FALSE;
}

// Shared motion settings for every DavidHiFi mod, written by Seamless
// Workshop: HKCU\Software\DavidHiFi\Motion, Enabled (DWORD, 0 = all window
// animations off) and Speed (a level name, or a DWORD percent of normal).
// A missing key means on at normal speed.
static float SpeedLevelScale(int level) {
    static constexpr float kScales[] = {1.0f, 0.5f, 0.75f, 1.0f, 1.5f, 2.0f};
    return level > 0 && level < (int)ARRAYSIZE(kScales) ? kScales[level] : 1.0f;
}

static void ReadGlobalMotion(bool* enabled, float* scale) {
    *enabled = true;
    *scale = 1.0f;
    HKEY key = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\DavidHiFi\\Motion", 0,
                      KEY_QUERY_VALUE, &key) != ERROR_SUCCESS) {
        return;
    }
    DWORD value = 0, type = 0, size = sizeof(value);
    if (RegQueryValueExW(key, L"Enabled", nullptr, &type, (BYTE*)&value,
                         &size) == ERROR_SUCCESS &&
        type == REG_DWORD) {
        *enabled = value != 0;
    }
    WCHAR text[32] = {};
    size = sizeof(text) - sizeof(WCHAR);
    if (RegQueryValueExW(key, L"Speed", nullptr, &type, (BYTE*)text, &size) ==
        ERROR_SUCCESS) {
        if (type == REG_DWORD) {
            DWORD percent = *(DWORD*)text;
            *scale = std::clamp((float)percent, 25.0f, 400.0f) / 100.0f;
        } else if (type == REG_SZ) {
            static const PCWSTR kNames[] = {L"", L"veryQuick", L"quick",
                                            L"normal", L"relaxed", L"slow"};
            for (int i = 1; i < (int)ARRAYSIZE(kNames); i++) {
                if (_wcsicmp(text, kNames[i]) == 0) {
                    *scale = SpeedLevelScale(i);
                }
            }
        }
    }
    RegCloseKey(key);
}

// Duration multiplier for every animation in the flyout, refreshed each time
// it opens. 1 = normal; 2 = twice as long.
static float g_motionScale = 1.0f;
// The open and close animation may play: the mod's own switch, the global
// switch and Windows "Animation effects" all have to allow it.
static bool g_motionAllowed = true;

static void RefreshMotion() {
    bool globalEnabled = true;
    float globalScale = 1.0f;
    ReadGlobalMotion(&globalEnabled, &globalScale);
    int level = g_animationSpeed.load(std::memory_order_relaxed);
    g_motionScale = level == 0 ? globalScale : SpeedLevelScale(level);
    g_motionAllowed = globalEnabled &&
                      g_flyoutAnimation.load(std::memory_order_relaxed) &&
                      AnimationsEnabled();
}

// Keyboard focus is only drawn while the window really has it, so the ring
// does not linger after the flyout loses activation.
static bool FocusVisible() {
    return g_focus != Hot::None && g_flyoutHwnd && GetFocus() == g_flyoutHwnd;
}

static float AnimT() {
    return Clamp01((float)(Now() - g_animStart) / (kAnimMs * g_motionScale));
}

static float AnimOut() {
    return 1.0f - Clamp01(AnimT() / 0.38f);
}

static float AnimIn() {
    return Clamp01((AnimT() - 0.38f) / 0.62f);
}

static bool InRect(D2D1_RECT_F rect, float x, float y) {
    return x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom;
}

struct GaugeTick {
    PCWSTR label;
    double mbps;
    double fraction;
    float width;
};

static constexpr GaugeTick kGaugeTicks[] = {
    {L"0", 0, 0.0, 28},       {L"5", 5, 0.12, 28},
    {L"10", 10, 0.24, 32},   {L"50", 50, 0.36, 32},
    {L"100", 100, 0.50, 38}, {L"250", 250, 0.625, 38},
    {L"500", 500, 0.75, 38}, {L"750", 750, 0.88, 38},
    {L"1000+", 1000, 1.0, 48},
};

static double GaugeFraction(double mbps) {
    constexpr double kGaugeMaxMbps = 1000.0;
    double value = Clamp(mbps, 0.0, kGaugeMaxMbps);
    if (!std::isfinite(value)) {
        return 0;
    }
    if (value <= 0) {
        return 0;
    }

    for (size_t i = 1; i < ARRAYSIZE(kGaugeTicks); i++) {
        const GaugeTick& lower = kGaugeTicks[i - 1];
        const GaugeTick& upper = kGaugeTicks[i];
        if (value <= upper.mbps) {
            double progress = lower.mbps == 0
                                  ? std::log1p(value) / std::log1p(upper.mbps)
                                  : std::log(value / lower.mbps) /
                                        std::log(upper.mbps / lower.mbps);
            return lower.fraction +
                   (upper.fraction - lower.fraction) * progress;
        }
    }
    return 1.0;
}

static PCWSTR StartButtonLabel(const TestState& state) {
    if (StateRunning(state)) {
        return g_str->stop;
    }
    if (state.phase == Phase::Done || state.phase == Phase::Canceled ||
        g_view == View::Results) {
        return g_str->repeat;
    }
    return g_str->start;
}

static bool IsRepeatButton(const TestState& state) {
    return !StateRunning(state) &&
           (state.phase == Phase::Done || state.phase == Phase::Canceled ||
            g_view == View::Results);
}

static D2D1_RECT_F StartButtonRect(const TestState& state) {
    PCWSTR label = StartButtonLabel(state);
    DWRITE_FONT_WEIGHT weight = StateRunning(state)
                                   ? DWRITE_FONT_WEIGHT_NORMAL
                                   : DWRITE_FONT_WEIGHT_SEMI_BOLD;
    float width = MeasureWidth(label, 13, weight) + 32.0f;
    if (IsRepeatButton(state)) {
        width += 22.0f;
    }
    width = std::max(width, 76.0f);
    float left = (kWidth - width) / 2.0f;
    return Rect(left, 382.0f, left + width, 416.0f);
}

static Hot HitTest(float x, float y) {
    if (InRect(kSettingsRect, x, y)) return Hot::Settings;
    if (InRect(kCloseRect, x, y)) {
        return Hot::Close;
    }
    if (g_view == View::Error) {
        return InRect(kRetryRect, x, y) ? Hot::Retry : Hot::None;
    }
    if (g_view == View::Results && InRect(kCopyRect, x, y)) {
        return Hot::Copy;
    }
    if (InRect(StartButtonRect(CopyState()), x, y)) {
        return Hot::Start;
    }
    return Hot::None;
}

static void DrawGauge(float alpha, const TestState& state) {
    if (alpha <= 0.001f) {
        return;
    }

    const float cx = kWidth / 2;
    const float cy = 162.0f;
    const float radius = 96.0f;
    const float stroke = 13.0f;

    DrawArc(cx, cy, radius, 1.0f, WithAlpha(g_palette.track, alpha), stroke);
    if (g_gaugeShown > 0.003) {
        D2D1_COLOR_F color =
            state.phase == Phase::Upload ? g_palette.upload : g_palette.download;
        DrawArc(cx, cy, radius, (float)g_gaugeShown, WithAlpha(color, alpha), stroke);
    }

    std::wstring value = L"\x2014";
    std::wstring unit = L"Mbps";
    if (state.phase != Phase::Latency && state.phase != Phase::Warmup &&
        state.phase != Phase::Stopping && state.phase != Phase::Canceled &&
        state.phase != Phase::Idle) {
        value = FormatNumber(state.currentMbps);
    }

    Text(value, Rect(20, 124, 380, 178), 44, WithAlpha(g_palette.text, alpha),
         DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_TEXT_ALIGNMENT_CENTER,
         DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 1, false, true);
    Text(unit, Rect(20, 178, 380, 198), 15, WithAlpha(g_palette.secondary, alpha),
         DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER);
    Text(state.caption, Rect(20, 202, 380, 220), 13,
         WithAlpha(g_palette.secondary, alpha), DWRITE_FONT_WEIGHT_NORMAL,
         DWRITE_TEXT_ALIGNMENT_CENTER);

    // Tick labels follow the same logarithmic scale as the arc.
    const float labelRadius = radius + 22.0f;
    for (const GaugeTick& tick : kGaugeTicks) {
        double angle = (135.0 + 270.0 * tick.fraction) *
                       3.14159265358979323846 / 180.0;
        float x = cx + labelRadius * (float)std::cos(angle);
        float y = cy + labelRadius * (float)std::sin(angle);
        Text(tick.label, Rect(x - tick.width / 2, y - 9,
                              x + tick.width / 2, y + 9),
             11, WithAlpha(g_palette.tertiary, alpha),
             DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER,
             DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }
}

static void DrawMetricLabel(float x, float y, PCWSTR glyph, D2D1_COLOR_F color,
                            PCWSTR label, float alpha) {
    Text(glyph, Rect(x, y - 1, x + 18, y + 17), 13, WithAlpha(color, alpha),
         DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING,
         DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 2);
    Text(label, Rect(x + 19, y, x + 160, y + 17), 12,
         WithAlpha(g_palette.secondary, alpha));
}

static void DrawValue(float x, float y, bool hasValue, double value, PCWSTR unit,
                      float fontSize, float alpha) {
    std::wstring text = hasValue ? FormatNumber(value) : L"\x2014";
    Text(text, Rect(x, y, x + 170, y + fontSize * 1.35f), fontSize,
         WithAlpha(g_palette.text, alpha), DWRITE_FONT_WEIGHT_SEMI_BOLD,
         DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR, 1, false, true);
    // Tabular measure: the drawn value uses tabular figures, so the unit must
    // be placed from the same width or it can touch the last digit.
    float width = MeasureWidth(text, fontSize, DWRITE_FONT_WEIGHT_SEMI_BOLD, 1, true);
    // The unit rides the value's baseline: box-bottom alignment drags the unit
    // down under glyphs without descenders, such as the em dash placeholder.
    float unitTop = y + BaselineOffset(fontSize, 1) - BaselineOffset(12, 0);
    Text(unit, Rect(x + width + 5, unitTop, x + width + 80, unitTop + 18), 12,
         WithAlpha(g_palette.secondary, alpha), DWRITE_FONT_WEIGHT_NORMAL,
         DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
}

static void DrawLatency(float x, float y, PCWSTR label, bool hasValue, double value,
                        float alpha) {
    float labelWidth = std::max(MeasureWidth(g_str->ping, 12, DWRITE_FONT_WEIGHT_MEDIUM),
                                MeasureWidth(g_str->jitter, 12, DWRITE_FONT_WEIGHT_MEDIUM));
    float valueX = x + std::ceil(labelWidth) + 9;
    Text(label, Rect(x, y + 3, valueX - 5, y + 20), 12,
         WithAlpha(g_palette.secondary, alpha));
    std::wstring text = hasValue ? FormatNumber(value) : L"\x2014";
    Text(text, Rect(valueX, y, x + 125, y + 20), 13,
         WithAlpha(g_palette.text, alpha), DWRITE_FONT_WEIGHT_MEDIUM,
         DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR, 0, false, true);
    float width = MeasureWidth(text, 13, DWRITE_FONT_WEIGHT_MEDIUM, 0, true);
    float unitTop = y + BaselineOffset(13, 0) - BaselineOffset(11, 0);
    Text(L"ms", Rect(valueX + width + 5, unitTop, x + 150, unitTop + 17), 11,
         WithAlpha(g_palette.secondary, alpha));
}

static void DrawLiveStats(float alpha, const TestState& state) {
    if (alpha <= 0.001f) {
        return;
    }

    DrawLine(20, 282, 380, 282, WithAlpha(g_palette.cardStroke, alpha * 1.6f));

    bool hasDown = state.phase == Phase::Download || state.phase == Phase::Upload ||
                   state.phase == Phase::Done;
    bool hasUp = state.phase == Phase::Upload || state.phase == Phase::Done;

    double down = state.phase == Phase::Download ? state.currentMbps : state.download;
    double up = state.phase == Phase::Upload ? state.currentMbps : state.upload;

    DrawMetricLabel(20, 288, L"\xE896", g_palette.download, g_str->download, alpha);
    DrawMetricLabel(200, 288, L"\xE898", g_palette.upload, g_str->upload, alpha);
    DrawValue(20, 304, hasDown, down, L"Mbps", 32, alpha);
    DrawValue(200, 304, hasUp, up, L"Mbps", 32, alpha);

    DrawLatency(20, 352, g_str->ping, state.hasPing, state.ping, alpha);
    DrawLatency(200, 352, g_str->jitter, state.hasJitter, state.jitter, alpha);
}

static void DrawCopyButton(float alpha) {
    bool copied = Now() < g_copyUntil;
    bool hover = g_hot == Hot::Copy;
    bool pressed = g_pressed == Hot::Copy;
    D2D1_RECT_F rect = kCopyRect;

    FillRounded(rect, ControlRadius(),
                WithAlpha(g_palette.controlFill, alpha * (pressed ? 2.4f : (hover ? 1.8f : 1.0f))));
    if (hover && !pressed && !copied) {
        StrokeGradient(rect, ControlRadius());
    } else {
        StrokeRounded(rect, ControlRadius(),
                      WithAlpha(g_palette.cardStroke, alpha * 2.0f), 2.0f);
    }

    PCWSTR glyph = copied ? L"\xE73E" : L"\xE8C8";
    PCWSTR label = copied ? g_str->copied : g_str->copy;
    Text(glyph, Rect(rect.left + 9, rect.top, rect.left + 24, rect.bottom), 12,
         WithAlpha(g_palette.text, alpha), DWRITE_FONT_WEIGHT_NORMAL,
         DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 2);
    Text(label, Rect(rect.left + 26, rect.top, rect.right - 4, rect.bottom), 12,
         WithAlpha(g_palette.text, alpha), DWRITE_FONT_WEIGHT_NORMAL,
         DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if (g_focus == Hot::Copy && FocusVisible()) {
        DrawFocusRing(rect, ControlRadius(), alpha);
    }
}

static void DrawResults(float alpha, const TestState& state) {
    if (alpha <= 0.001f) {
        return;
    }

    FillRounded(kCardRect, CardRadius(), WithAlpha(g_palette.cardFill, alpha));
    StrokeRounded(kCardRect, CardRadius(),
                  WithAlpha(g_palette.cardStroke, alpha * 2.0f), 2.0f);

    Text(g_str->resultsTitle, Rect(36, 62, 260, 82), 13,
         WithAlpha(g_palette.text, alpha), DWRITE_FONT_WEIGHT_SEMI_BOLD);
    DrawCopyButton(alpha);

    DrawChart(state.samples, Rect(36, 94, 364, 198), alpha);

    // Caption row: server and time on the left, data used on the right.
    std::wstring caption = FormatClock(state.when);
    Text(caption, Rect(36, 214, 248, 230), 11, WithAlpha(g_palette.secondary, alpha));

    wchar_t dataText[64];
    swprintf(dataText, 64, L"%s: %.0f MB",
             g_str->dataUsed, state.dataUsed / 1'000'000.0);
    Text(std::wstring(dataText), Rect(248, 214, 364, 230), 11,
         WithAlpha(g_palette.secondary, alpha), DWRITE_FONT_WEIGHT_NORMAL,
         DWRITE_TEXT_ALIGNMENT_TRAILING);

    DrawMetricLabel(36, 236, L"\xE896", g_palette.download, g_str->download, alpha);
    DrawMetricLabel(216, 236, L"\xE898", g_palette.upload, g_str->upload, alpha);
    DrawValue(36, 252, true, state.download, L"Mbps", 30, alpha);
    DrawValue(216, 252, true, state.upload, L"Mbps", 30, alpha);

    DrawLatency(36, 310, g_str->ping, state.hasPing, state.ping, alpha);
    DrawLatency(216, 310, g_str->jitter, state.hasJitter, state.jitter, alpha);
}

static void DrawError(float alpha, const TestState& state) {
    FillRounded(kErrorRect, CardRadius(), WithAlpha(g_palette.cardFill, alpha));
    StrokeRounded(kErrorRect, CardRadius(),
                  WithAlpha(g_palette.cardStroke, alpha * 2.0f), 2.0f);

    Text(L"\xEA39", Rect(20, 74, 380, 106), 26, WithAlpha(g_palette.negative, alpha),
         DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER,
         DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 2);
    Text(g_str->failedTitle, Rect(20, 112, 380, 134), 15,
         WithAlpha(g_palette.text, alpha), DWRITE_FONT_WEIGHT_SEMI_BOLD,
         DWRITE_TEXT_ALIGNMENT_CENTER);
    Text(state.error.empty() ? g_str->failedHint : state.error,
         Rect(52, 142, 348, 218), 12, WithAlpha(g_palette.secondary, alpha),
         DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER,
         DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 0, true);

    bool hover = g_hot == Hot::Retry;
    bool pressed = g_pressed == Hot::Retry;
    FillRounded(kRetryRect, ControlRadius(),
                WithAlpha(pressed ? Shade(g_palette.accent, 0.18f)
                                  : Lighten(g_palette.accent, hover ? 0.18f : 0.0f),
                          alpha));
    if (hover && !pressed) {
        StrokeGradient(kRetryRect, ControlRadius());
    }
    Text(g_str->retry, kRetryRect, 13, WithAlpha(g_palette.accentText, alpha),
         DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_TEXT_ALIGNMENT_CENTER,
         DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if (g_focus == Hot::Retry && FocusVisible()) {
        DrawFocusRing(kRetryRect, ControlRadius(), alpha);
    }
}

static void DrawButton(float alpha, const TestState& state) {
    bool running = StateRunning(state);
    PCWSTR label = StartButtonLabel(state);
    bool repeat = IsRepeatButton(state);
    bool hover = g_hot == Hot::Start;
    bool pressed = g_pressed == Hot::Start;

    D2D1_RECT_F rect = StartButtonRect(state);
    DWRITE_FONT_WEIGHT weight = running ? DWRITE_FONT_WEIGHT_NORMAL
                                        : DWRITE_FONT_WEIGHT_SEMI_BOLD;
    if (running) {
        float fill = pressed ? 3.0f : (hover ? 2.2f : 1.2f);
        FillRounded(rect, ControlRadius(),
                    WithAlpha(g_palette.controlFill, alpha * fill));
        if (hover && !pressed) {
            StrokeGradient(rect, ControlRadius());
        } else {
            StrokeRounded(rect, ControlRadius(),
                          WithAlpha(g_palette.cardStroke, alpha * 2.0f), 2.0f);
        }
    } else {
        D2D1_COLOR_F fill = pressed ? Shade(g_palette.accent, 0.18f)
                                    : Lighten(g_palette.accent, hover ? 0.18f : 0.0f);
        FillRounded(rect, ControlRadius(), WithAlpha(fill, alpha));
        if (hover && !pressed) {
            StrokeGradient(rect, ControlRadius());
        }
    }
    D2D1_COLOR_F textColor =
        running ? g_palette.text : g_palette.accentText;
    if (repeat) {
        float labelWidth = MeasureWidth(label, 13, weight);
        float contentWidth = 16.0f + 6.0f + labelWidth;
        float contentLeft = (rect.left + rect.right - contentWidth) / 2.0f;
        Text(L"\xE72C", Rect(contentLeft, rect.top, contentLeft + 16.0f, rect.bottom),
             14, WithAlpha(textColor, alpha), weight,
             DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 2);
        Text(label,
             Rect(contentLeft + 22.0f, rect.top,
                  contentLeft + contentWidth, rect.bottom),
             13, WithAlpha(textColor, alpha), weight,
             DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    } else {
        Text(label, rect, 13, WithAlpha(textColor, alpha), weight,
             DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }
    if (g_focus == Hot::Start && FocusVisible()) {
        DrawFocusRing(rect, ControlRadius(), alpha);
    }
}

static void DrawTitle(float alpha) {
    Text(L"Speedtest", Rect(16, 15, 200, 33), 12,
         WithAlpha(g_palette.text, alpha * 0.85f));

    for (auto [hot, rect, glyph] : {
             std::tuple{Hot::Settings, kSettingsRect, L"\xE713"},
             std::tuple{Hot::Close, kCloseRect, L"\xE711"}}) {
        bool hover = g_hot == hot;
        bool pressed = g_pressed == hot;
        FillRounded(rect, ControlRadius(),
                    WithAlpha(g_palette.controlFill, alpha * (pressed ? 2.4f : hover ? 1.6f : 1.0f)));
        if (hover && !pressed) {
            StrokeGradient(rect, ControlRadius());
        } else {
            StrokeRounded(rect, ControlRadius(), Col(pressed ? 0xCBA6F7 : 0x45475A, alpha), 2.0f);
        }
        Text(glyph, rect, 11, WithAlpha(g_palette.text, alpha),
             DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER,
             DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 2);
        if (g_focus == hot && FocusVisible()) DrawFocusRing(rect, ControlRadius(), alpha);
    }
}

static void BoxBlurBgra(std::vector<uint32_t>& pixels, int width, int height, int radius) {
    if (radius < 1 || width <= 0 || height <= 0) return;
    std::vector<uint32_t> scratch(pixels.size());
    auto pass = [&](const std::vector<uint32_t>& src, std::vector<uint32_t>& dst,
                    bool horizontal) {
        int length = horizontal ? width : height;
        int lines = horizontal ? height : width;
        int window = radius * 2 + 1;
        for (int line = 0; line < lines; line++) {
            auto at = [&](int i) -> uint32_t {
                if (i < 0 || i >= length) return 0;
                return horizontal ? src[(size_t)line * width + i] : src[(size_t)i * width + line];
            };
            int sum[4] = {0, 0, 0, 0};
            for (int i = -radius; i <= radius; i++) {
                uint32_t c = at(i);
                for (int k = 0; k < 4; k++) sum[k] += (int)((c >> (8 * k)) & 0xFF);
            }
            for (int i = 0; i < length; i++) {
                uint32_t out = 0;
                for (int k = 0; k < 4; k++) {
                    out |= (uint32_t)std::clamp((sum[k] + window / 2) / window, 0, 255) << (8 * k);
                }
                if (horizontal) dst[(size_t)line * width + i] = out;
                else dst[(size_t)i * width + line] = out;
                uint32_t add = at(i + radius + 1);
                uint32_t sub = at(i - radius);
                for (int k = 0; k < 4; k++) {
                    sum[k] += (int)((add >> (8 * k)) & 0xFF) - (int)((sub >> (8 * k)) & 0xFF);
                }
            }
        }
    };
    for (int round = 0; round < 3; round++) {
        pass(pixels, scratch, true);
        pass(scratch, pixels, false);
    }
}

struct DetailBitmap {
    std::wstring text;
    ID2D1Bitmap* bitmap = nullptr;
    float margin = 0;
};
static DetailBitmap g_detailBitmaps[4];

static void ClearDetailBitmaps() {
    for (auto& entry : g_detailBitmaps) {
        if (entry.bitmap) entry.bitmap->Release();
        entry = {};
    }
}

template <class T>
static auto ReleaseDetailResource(T* resource) {
    return std::unique_ptr<T, void(*)(T*)>(resource, [](T* p) { p->Release(); });
}

static void MakeBlurredDetail(DetailBitmap& entry, const std::wstring& text) {
    if (entry.text == text) return;
    if (entry.bitmap) entry.bitmap->Release();
    entry = {text};
    IWICImagingFactory* factory = nullptr;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                IID_PPV_ARGS(&factory)))) return;
    auto factoryOwner = ReleaseDetailResource(factory);
    int radius = std::max(2, static_cast<int>(std::lround(2.5 * g_scale)));
    int margin = radius * 3 + 2;
    int width = static_cast<int>(std::ceil(235 * g_scale)) + 2 * margin;
    int height = static_cast<int>(std::ceil(18 * g_scale)) + 2 * margin;
    IWICBitmap* bitmap = nullptr;
    if (FAILED(factory->CreateBitmap(width, height, GUID_WICPixelFormat32bppPBGRA,
                                     WICBitmapCacheOnLoad, &bitmap))) return;
    auto bitmapOwner = ReleaseDetailResource(bitmap);
    ID2D1RenderTarget* target = nullptr;
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_SOFTWARE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), g_dpi, g_dpi);
    if (FAILED(g_d2dFactory->CreateWicBitmapRenderTarget(bitmap, props, &target))) return;
    auto targetOwner = ReleaseDetailResource(target);
    ID2D1SolidColorBrush* brush = nullptr;
    if (FAILED(target->CreateSolidColorBrush(g_palette.secondary, &brush))) return;
    auto brushOwner = ReleaseDetailResource(brush);
    auto format = GetTextFormat(11, DWRITE_FONT_WEIGHT_MEDIUM, DWRITE_TEXT_ALIGNMENT_LEADING,
                                DWRITE_PARAGRAPH_ALIGNMENT_NEAR, false, 0);
    if (!format) return;
    entry.margin = margin / g_scale;
    float pad = entry.margin;
    target->BeginDraw();
    target->Clear(D2D1::ColorF(0, 0));
    target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    target->DrawTextW(text.c_str(), static_cast<UINT32>(text.size()), format,
                      Rect(pad, pad, pad + 235, pad + 18), brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
    if (FAILED(target->EndDraw())) return;
    std::vector<uint32_t> pixels(static_cast<size_t>(width) * height);
    if (FAILED(bitmap->CopyPixels(nullptr, width * 4, static_cast<UINT>(pixels.size() * 4),
                                  reinterpret_cast<BYTE*>(pixels.data())))) return;
    BoxBlurBgra(pixels, width, height, radius);
    g_renderTarget->CreateBitmap(D2D1::SizeU(width, height), pixels.data(), width * 4,
        D2D1::BitmapProperties(props.pixelFormat, g_dpi, g_dpi), &entry.bitmap);
}

static void DrawNetworkDetails(const TestState& state) {
    const std::wstring values[] = {g_network.name, state.server, state.publicIp, state.country};
    int row = 0;
    for (size_t i = 0; i < ARRAYSIZE(kDetailLabels); ++i) {
        DetailMode mode = DetailDisplay(i);
        if (mode == DetailMode::Hidden) continue;
        auto rect = DetailRect(row++);
        rect.top += 3;
        Text(kDetailLabels[i], Rect(rect.left, rect.top, 137, rect.bottom), 11, g_palette.secondary);
        rect.left = 145;
        if (values[i].empty()) {
            Text(L"Unavailable", rect, 11, g_palette.secondary);
            continue;
        }
        auto text = Ellipsize(values[i], rect.right - rect.left, 11, DWRITE_FONT_WEIGHT_MEDIUM);
        float opacity = mode == DetailMode::Always ? 1.0f : g_detailOpacity[i];
        if (opacity < 1.0f) {
            auto& entry = g_detailBitmaps[i];
            MakeBlurredDetail(entry, text);
            if (entry.bitmap) {
                auto size = entry.bitmap->GetSize();
                float left = rect.left - entry.margin, top = rect.top - entry.margin;
                g_renderTarget->DrawBitmap(entry.bitmap, Rect(left, top, left + size.width, top + size.height),
                                           1.0f - opacity);
            } else {
                Text(L"Hidden", rect, 11, WithAlpha(g_palette.secondary, 1.0f - opacity));
            }
        }
        if (opacity > 0.0f) Text(text, rect, 11, WithAlpha(g_palette.secondary, opacity));
    }
}

static void DrawView(View view, float alpha, const TestState& state) {
    if (alpha <= 0.001f) {
        return;
    }
    switch (view) {
        case View::Gauge:
            DrawGauge(alpha, state);
            DrawLiveStats(alpha, state);
            break;
        case View::Results:
            DrawResults(alpha, state);
            break;
        case View::Error:
            DrawError(alpha, state);
            break;
    }
}

static bool g_borderHovered = false;

static void DrawFrame(const TestState& state) {
    if (!g_renderTarget) {
        return;
    }

    // The material itself is drawn by DWM behind the composition surface: the
    // surface stays transparent so the Desktop Acrylic tint and blur are the
    // only background. Painting the palette colour on top as well would stack
    // two tints, flatten the blur and make the flyout look like flat grey glass
    // instead of the shell material.
    bool translucent = g_composition && g_translucent;
    D2D1_COLOR_F background = g_palette.background;
    float scrim = translucent ? ScrimAlpha() : 1.0f;
    background.a = scrim;
    g_renderTarget->Clear(background);

    // DWM's Desktop Acrylic is much lighter than the material the shell paints
    // in its dark flyouts. A black tint restores that tone; a lighter white
    // tint in light mode reduces backdrop show-through without removing blur.
    if (translucent && scrim < 1.0f) {
        float tintAlpha = kMochaTintAlpha * (1.0f - scrim);
        D2D1_COLOR_F tint = Col(0x181825, tintAlpha);
        FillRect(Rect(-2.0f, -2.0f, kWidth + 2.0f, g_layoutHeight + 2.0f), tint);

        // The stronger dark tint flattens DWM's grain, so restore a faint
        // texture there to keep banding from showing in the blur.
        if (g_dark && EnsureNoise()) {
            g_noiseBrush->SetOpacity(kNoiseOpacity * (1.0f - scrim));
            g_renderTarget->FillRectangle(
                Rect(-2.0f, -2.0f, kWidth + 2.0f, g_layoutHeight + 2.0f),
                g_noiseBrush);
        }
    }

    if (g_animating) {
        DrawView(g_animFrom, AnimOut(), state);
        DrawView(g_view, AnimIn(), state);
    } else {
        DrawView(g_view, 1.0f, state);
    }

    float buttonAlpha = g_animating ? AnimIn() : 1.0f;
    if (g_view != View::Error || (g_animating && g_animFrom != View::Error)) {
        DrawButton(buttonAlpha, state);
    }

    DrawNetworkDetails(state);
    DrawTitle(1.0f);
    float width = static_cast<float>(g_borderWidth.load());
    float inset = width / 2.0f;
    auto bounds = Rect(inset, inset, kWidth - inset, g_layoutHeight - inset);
    float radius = std::max(0.0f, WindowRadius() - inset);
    if (g_borderHovered) {
        StrokeGradient(bounds, radius, width, g_borderHoverStart.load(), g_borderHoverEnd.load(), true);
    } else {
        StrokeRounded(bounds, radius, Col(g_borderRest.load()), width);
    }
}

// ---------------------------------------------------------------------------
// Direct2D lifetime
// ---------------------------------------------------------------------------

static void ReleaseTargets() {
    ClearDetailBitmaps();
    // Brushes belong to the render target: drop them before the target goes.
    ReleaseBrushes();
    ReleaseNoise();
    if (g_contextBitmap) {
        g_contextBitmap->Release();
        g_contextBitmap = nullptr;
    }
    if (g_context) {
        g_context->SetTarget(nullptr);
        g_context->Release();
        g_context = nullptr;
    }
    if (g_renderTarget) {
        g_renderTarget->Release();
        g_renderTarget = nullptr;
    }
    if (g_hwndTarget) {
        g_hwndTarget->Release();
        g_hwndTarget = nullptr;
    }
    if (g_motionOpacity) {
        g_motionOpacity->Release();
        g_motionOpacity = nullptr;
    }
    if (g_motionOffset) {
        g_motionOffset->Release();
        g_motionOffset = nullptr;
    }
    if (g_dcompEffect) {
        g_dcompEffect->Release();
        g_dcompEffect = nullptr;
    }
    if (g_dcompVisual) {
        g_dcompVisual->Release();
        g_dcompVisual = nullptr;
    }
    if (g_dcompTarget) {
        g_dcompTarget->Release();
        g_dcompTarget = nullptr;
    }
    if (g_dcompDevice) {
        g_dcompDevice->Release();
        g_dcompDevice = nullptr;
    }
    if (g_swapChain) {
        g_swapChain->Release();
        g_swapChain = nullptr;
    }
    if (g_dxgiDevice) {
        g_dxgiDevice->Release();
        g_dxgiDevice = nullptr;
    }
    if (g_d3dDevice) {
        g_d3dDevice->Release();
        g_d3dDevice = nullptr;
    }
    g_composition = false;
    g_targetWidth = 0;
    g_targetHeight = 0;
    g_targetDpi = 0;
}

static void ReleaseGraphics() {
    ReleaseTargets();
    if (g_roundStroke) {
        g_roundStroke->Release();
        g_roundStroke = nullptr;
    }
    for (auto& entry : g_textFormats) {
        entry.second->Release();
    }
    g_textFormats.clear();
    if (g_dwriteFactory) {
        g_dwriteFactory->Release();
        g_dwriteFactory = nullptr;
    }
    if (g_d2dFactory) {
        g_d2dFactory->Release();
        g_d2dFactory = nullptr;
    }
}

static bool BindCompositionTarget() {
    if (!g_context || !g_swapChain) {
        return false;
    }
    if (g_contextBitmap) {
        g_contextBitmap->Release();
        g_contextBitmap = nullptr;
    }

    IDXGISurface* surface = nullptr;
    if (FAILED(g_swapChain->GetBuffer(0, __uuidof(IDXGISurface),
                                      (void**)&surface))) {
        return false;
    }

    D2D1_BITMAP_PROPERTIES1 properties = {};
    properties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
    properties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
    properties.dpiX = g_dpi;
    properties.dpiY = g_dpi;
    properties.bitmapOptions =
        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

    HRESULT hr = g_context->CreateBitmapFromDxgiSurface(surface, &properties,
                                                        &g_contextBitmap);
    surface->Release();
    if (FAILED(hr)) {
        return false;
    }

    g_context->SetTarget(g_contextBitmap);
    g_context->SetDpi(g_dpi, g_dpi);
    g_context->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    g_context->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    g_targetDpi = g_dpi;
    return true;
}

// Builds a DirectComposition swapchain with an alpha channel. The flyout keeps
// painting the same way, but the background can now be fully transparent so
// the DWM backdrop (Desktop Acrylic) is the only background.
static bool CreateCompositionTarget(HWND hwnd, UINT width, UINT height) {
    D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_0,
                                  D3D_FEATURE_LEVEL_10_1};
    // Hardware first; retry with WARP so VMs, RDP sessions and machines
    // without usable graphics still get the composition surface. Without this
    // fallback those sessions would fall through to the (in this window
    // shape invisible) HwndRenderTarget path below.
    HRESULT d3dHr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                   D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 2,
                                   D3D11_SDK_VERSION, &g_d3dDevice, nullptr,
                                   nullptr);
    if (FAILED(d3dHr)) {
        d3dHr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr,
                               D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 2,
                               D3D11_SDK_VERSION, &g_d3dDevice, nullptr,
                               nullptr);
    }
    if (FAILED(d3dHr)) {
        return false;
    }
    if (FAILED(g_d3dDevice->QueryInterface(__uuidof(IDXGIDevice),
                                           (void**)&g_dxgiDevice))) {
        return false;
    }

    ID2D1Device* d2dDevice = nullptr;
    ID2D1Factory1* factory1 = nullptr;
    if (FAILED(g_d2dFactory->QueryInterface(__uuidof(ID2D1Factory1),
                                            (void**)&factory1))) {
        return false;
    }
    // The device must come from the same factory that created the stroke style
    // and path geometries, otherwise every draw call fails with WRONG_FACTORY.
    HRESULT hr = factory1->CreateDevice(g_dxgiDevice, &d2dDevice);
    factory1->Release();
    if (FAILED(hr)) {
        return false;
    }
    hr = d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
                                        &g_context);
    d2dDevice->Release();
    if (FAILED(hr)) {
        return false;
    }

    IDXGIAdapter* adapter = nullptr;
    if (FAILED(g_dxgiDevice->GetAdapter(&adapter))) {
        return false;
    }
    IDXGIFactory2* factory = nullptr;
    hr = adapter->GetParent(__uuidof(IDXGIFactory2), (void**)&factory);
    adapter->Release();
    if (FAILED(hr)) {
        return false;
    }

    DXGI_SWAP_CHAIN_DESC1 description = {};
    description.Width = width;
    description.Height = height;
    description.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    description.SampleDesc.Count = 1;
    description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    description.BufferCount = 2;
    description.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    description.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
    hr = factory->CreateSwapChainForComposition(g_d3dDevice, &description,
                                                nullptr, &g_swapChain);
    factory->Release();
    if (FAILED(hr)) {
        return false;
    }

    if (FAILED(DCompositionCreateDevice(g_dxgiDevice,
                                        __uuidof(IDCompositionDevice),
                                        (void**)&g_dcompDevice))) {
        return false;
    }
    if (FAILED(g_dcompDevice->CreateTargetForHwnd(hwnd, TRUE, &g_dcompTarget)) ||
        FAILED(g_dcompDevice->CreateVisual(&g_dcompVisual))) {
        return false;
    }
    if (FAILED(g_dcompVisual->SetContent(g_swapChain)) ||
        FAILED(g_dcompTarget->SetRoot(g_dcompVisual)) ||
        FAILED(g_dcompDevice->Commit())) {
        return false;
    }

    g_composition = true;
    g_targetWidth = width;
    g_targetHeight = height;
    if (!BindCompositionTarget()) {
        return false;
    }

    // g_renderTarget is a separate reference so the painting code keeps using
    // one interface whatever path produced it.
    return SUCCEEDED(g_context->QueryInterface(__uuidof(ID2D1RenderTarget),
                                               (void**)&g_renderTarget));
}

static bool EnsureRenderTarget() {
    if (g_renderTarget) {
        return true;
    }
    if (!g_d2dFactory || !g_flyoutHwnd) {
        return false;
    }

    RECT client = {};
    GetClientRect(g_flyoutHwnd, &client);
    UINT width = (UINT)std::max<LONG>(1, client.right - client.left);
    UINT height = (UINT)std::max<LONG>(1, client.bottom - client.top);

    // The material needs per-pixel alpha, so the composition surface is the
    // default path; the HWND target stays as a fallback if D3D is unavailable.
    if (CreateCompositionTarget(g_flyoutHwnd, width, height)) {
        Wh_Log(L"render target: composition (acrylic) %ux%u", width, height);
        return true;
    }
    ReleaseTargets();

    D2D1_RENDER_TARGET_PROPERTIES properties = {};
    properties.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
    properties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
    properties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
    properties.usage = D2D1_RENDER_TARGET_USAGE_NONE;
    properties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
    properties.dpiX = g_dpi;
    properties.dpiY = g_dpi;

    D2D1_HWND_RENDER_TARGET_PROPERTIES hwndProperties = {};
    hwndProperties.hwnd = g_flyoutHwnd;
    hwndProperties.pixelSize = {width, height};
    hwndProperties.presentOptions = D2D1_PRESENT_OPTIONS_NONE;

    if (FAILED(g_d2dFactory->CreateHwndRenderTarget(properties, hwndProperties,
                                                    &g_hwndTarget))) {
        g_hwndTarget = nullptr;
        return false;
    }
    if (FAILED(g_hwndTarget->QueryInterface(__uuidof(ID2D1RenderTarget),
                                            (void**)&g_renderTarget))) {
        return false;
    }
    g_targetWidth = width;
    g_targetHeight = height;
    Wh_Log(L"render target: hwnd %ux%u (translucent %d)", width, height,
        g_translucent ? 1 : 0);
    return true;
}

static void ResizeRenderTarget() {
    if (!g_renderTarget || !g_flyoutHwnd) {
        return;
    }
    RECT client = {};
    GetClientRect(g_flyoutHwnd, &client);
    UINT width = (UINT)std::max<LONG>(1, client.right - client.left);
    UINT height = (UINT)std::max<LONG>(1, client.bottom - client.top);

    if (g_composition && g_context && g_swapChain) {
        if (width == g_targetWidth && height == g_targetHeight &&
            g_dpi == g_targetDpi) {
            return;
        }
        g_context->SetTarget(nullptr);
        if (g_contextBitmap) {
            g_contextBitmap->Release();
            g_contextBitmap = nullptr;
        }
        if (SUCCEEDED(g_swapChain->ResizeBuffers(0, width, height,
                                                 DXGI_FORMAT_UNKNOWN, 0)) &&
            BindCompositionTarget()) {
            g_targetWidth = width;
            g_targetHeight = height;
            return;
        }
        // The swapchain is gone: fall back to the HWND path on the next paint.
        ReleaseTargets();
        return;
    }

    if (g_hwndTarget) {
        g_hwndTarget->Resize({width, height});
        g_hwndTarget->SetDpi(g_dpi, g_dpi);
        g_targetWidth = width;
        g_targetHeight = height;
        g_targetDpi = g_dpi;
    }
}

// ---------------------------------------------------------------------------
// Actions
// ---------------------------------------------------------------------------

static void BeginView(View target, bool animate = true) {
    if (target == g_view && !g_animating) {
        return;
    }
    View previous = g_animating ? g_animFrom : g_view;
    g_animFrom = previous;
    g_view = target;
    g_heightFrom = g_layoutHeight;
    g_animStart = Now();
    g_animating = animate && previous != target && AnimationsEnabled();
    if (g_view != previous) {
        g_focus = Hot::None;
        if (g_flyoutHwnd) {
            NotifyWinEvent(EVENT_OBJECT_REORDER, g_flyoutHwnd, OBJID_CLIENT,
                           CHILDID_SELF);
        }
    }
}

static void CopyResult(HWND hwnd, const TestState& state) {
    if (!state.hasResult) {
        return;
    }
    std::wstring text =
        L"Speedtest \x00B7 " + FormatNumber(state.download) + L" Mbps download \x00B7 " +
        FormatNumber(state.upload) + L" Mbps upload \x00B7 " +
        (state.hasPing ? FormatNumber(state.ping) : L"\x2014") + L" ms ping \x00B7 " +
        (state.hasJitter ? FormatNumber(state.jitter) : L"\x2014") + L" ms jitter \x00B7 " +
        std::to_wstring((state.dataUsed + 500000) / 1000000) + L" MB data used";
    text += L"\r\n";
    if (DetailDisplay(1) == DetailMode::Always) text += state.server + L" \x00B7 ";
    text += FormatDate(state.when);

    size_t bytes = (text.size() + 1) * sizeof(wchar_t);
    HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (!memory) {
        Wh_Log(L"Clipboard allocation failed (error %u)", GetLastError());
        return;
    }

    void* target = GlobalLock(memory);
    if (!target) {
        Wh_Log(L"Clipboard memory lock failed (error %u)", GetLastError());
        GlobalFree(memory);
        return;
    }
    memcpy(target, text.c_str(), bytes);
    GlobalUnlock(memory);

    bool copied = false;
    DWORD error = ERROR_SUCCESS;
    for (int attempt = 0; attempt < 5; attempt++) {
        if (OpenClipboard(hwnd)) {
            if (EmptyClipboard()) {
                if (SetClipboardData(CF_UNICODETEXT, memory)) {
                    memory = nullptr;
                    copied = true;
                } else {
                    error = GetLastError();
                }
            } else {
                error = GetLastError();
            }
            CloseClipboard();
            break;
        }
        error = GetLastError();
        Sleep(20);
    }
    if (memory) {
        GlobalFree(memory);
    }
    if (copied) {
        g_copyUntil = Now() + 1600;
    } else {
        Wh_Log(L"Copying test results to the clipboard failed (error %u)",
               error);
    }
    InvalidateRect(hwnd, nullptr, FALSE);
}

static constexpr UINT_PTR kRetryStartTimer = 7;

static void StartOrCancelTest(HWND hwnd) {
    if (InterlockedCompareExchange(&g_shutdown, 0, 0)) {
        return;
    }

    TestState state = CopyState();
    if (StateRunning(state)) {
        RequestTestCancel();
        InvalidateRect(hwnd, nullptr, FALSE);
        return;
    }

    if (g_testThread) {
        // The previous worker may still be unwinding (it already set
        // Canceled/Done/Error but its transfer threads are still stopping).
        // Never start a second run beside it: both would write the same
        // shared test state and transfer workers. Wait a moment, and if it is
        // still busy, retry from a timer instead of orphaning the thread.
        DWORD wait = WaitForSingleObject(g_testThread, 250);
        if (wait == WAIT_TIMEOUT) {
            g_cancelRequested.store(1, std::memory_order_relaxed);
            StateSetCaption(g_str->stopping);
            SetTimer(hwnd, kRetryStartTimer, 250, nullptr);
            InvalidateRect(hwnd, nullptr, FALSE);
            return;
        }
        CloseHandle(g_testThread);
        g_testThread = nullptr;
    }
    KillTimer(hwnd, kRetryStartTimer);

    StateReset();
    StateSetCaption(g_str->starting);
    // Mark the run as active before the worker starts, so a focus change in the
    // first few hundred milliseconds cannot dismiss the flyout mid-test.
    StateSetPhase(Phase::Warmup, g_str->starting);
    g_cancelRequested.store(0, std::memory_order_relaxed);
    g_copyUntil = 0;
    g_gaugeShown = 0;
    g_network = ReadNetwork();
    BeginView(View::Gauge);

    if (InterlockedCompareExchange(&g_shutdown, 0, 0)) {
        g_cancelRequested.store(1, std::memory_order_relaxed);
        StateCanceled();
        return;
    }

    g_testThread = CreateThread(nullptr, 0, TestWorkerThread, nullptr, 0, nullptr);
    if (!g_testThread) {
        DWORD error = GetLastError();
        Wh_Log(L"Speed test worker creation failed (error %u)", error);
        StateFail(g_str->errUnexpected);
        SetTimer(hwnd, 1, 16, nullptr);
        InvalidateRect(hwnd, nullptr, FALSE);
        return;
    }
    SetTimer(hwnd, 1, 16, nullptr);
    InvalidateRect(hwnd, nullptr, FALSE);
}

// ---------------------------------------------------------------------------
// Show / hide / paint
// ---------------------------------------------------------------------------

// DWM backdrop. Windows 11 flyouts use Desktop Acrylic: DWM blurs whatever is
// behind the window and the premultiplied swap chain lets it show through.
// When the user turns transparency effects off, the plain solid surface is
// used instead (Windows does the same in its own apps).
//
// The frame is extended once at creation time (see UiThreadProc): on a
// captionless popup with zero margins DWM keeps the solid fallback. Runtime
// calls only flip the attribute, which must *change* for DWM to recompute the
// material -- that is why it is always set to NONE while hidden.
static void ApplyBackdrop(HWND hwnd, bool enable) {
    BOOL dark = g_dark ? TRUE : FALSE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark,
                          sizeof(dark));

    int backdrop = enable ? 3 /* DWMSBT_TRANSIENTWINDOW */
                          : 1 /* DWMSBT_NONE */;
    DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop,
                          sizeof(backdrop));
}

// Re-reads theme and transparency and re-applies the material. DWM ignores a
// write with the same value, so a state flip is applied as NONE -> ON.
static void RefreshBackdrop(HWND hwnd) {
    bool wasTranslucent = g_translucent;
    RefreshAppearance();
    if (g_translucent == wasTranslucent) {
        ApplyBackdrop(hwnd, g_translucent);
        return;
    }
    ApplyBackdrop(hwnd, false);
    if (g_translucent) {
        ApplyBackdrop(hwnd, true);
        g_scrimFadeAt = Now();
    } else {
        g_scrimFadeAt = 0;
    }
    InvalidateRect(hwnd, nullptr, FALSE);
}

static HMONITOR MonitorUnderCursor() {
    POINT cursor = {};
    GetCursorPos(&cursor);
    return MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST);
}

struct TaskbarEnumContext {
    HMONITOR monitor;
    HWND found;
};

static BOOL CALLBACK FindTaskbarForMonitorEnumProc(HWND hwnd, LPARAM lParam) {
    TaskbarEnumContext* ctx = (TaskbarEnumContext*)lParam;
    wchar_t className[32];
    if (GetClassNameW(hwnd, className, ARRAYSIZE(className)) &&
        (!wcscmp(className, L"Shell_TrayWnd") ||
         !wcscmp(className, L"Shell_SecondaryTrayWnd")) &&
        IsWindowVisible(hwnd) &&
        MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST) == ctx->monitor) {
        ctx->found = hwnd;
        return FALSE;
    }
    return TRUE;
}

static HWND FindTaskbarForMonitor(HMONITOR monitor) {
    TaskbarEnumContext ctx = {monitor, nullptr};
    EnumWindows(FindTaskbarForMonitorEnumProc, (LPARAM)&ctx);
    return ctx.found;
}

static bool g_anchorTop = false;

static void PositionFlyout(HWND hwnd, HMONITOR monitor) {
    MONITORINFO info = {sizeof(info)};
    if (!monitor || !GetMonitorInfoW(monitor, &info)) {
        return;
    }

    UINT dpiX = 96;
    UINT dpiY = 96;
    GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
    g_dpi = (float)(dpiX ? dpiX : 96);
    g_scale = g_dpi / 96.0f;

    int width = (int)std::lround(kWidth * g_scale);
    int height = (int)std::lround(g_layoutHeight * g_scale);
    int margin = (int)std::lround(12 * g_scale);
    int x = info.rcWork.right - width - margin;
    int y = info.rcWork.bottom - height - margin;
    // Flyouts grow from the tray edge, and the tray is not always at the
    // bottom: on a top-docked taskbar the bottom-right anchor would open the
    // window diagonally opposite the button. Find this monitor's taskbar and
    // anchor at its inner edge instead.
    const RECT& work = info.rcWork;
    switch (g_flyoutPosition.load(std::memory_order_relaxed)) {
        case 1:  // Top right.
            y = work.top + margin;
            break;
        case 2:  // Top left.
            x = work.left + margin;
            y = work.top + margin;
            break;
        case 3:  // Bottom right: the defaults above.
            break;
        case 4:  // Bottom left.
            x = work.left + margin;
            break;
        case 5:  // Centre.
            x = work.left + (work.right - work.left - width) / 2;
            y = work.top + (work.bottom - work.top - height) / 2;
            break;
        default: {  // Auto: the tray edge of this monitor's taskbar.
            HWND taskbar = FindTaskbarForMonitor(monitor);
            RECT tb = {};
            if (taskbar && GetWindowRect(taskbar, &tb)) {
                int midY = (info.rcMonitor.top + info.rcMonitor.bottom) / 2;
                if (tb.top < midY) {
                    y = work.top + margin;
                }
            }
            break;
        }
    }

    // The open animation slides away from the edge the window sits against:
    // down from a top bar, up from a bottom one (and up for the centre).
    g_anchorTop = y < (work.top + work.bottom - height) / 2;

    // Position and size only: visibility is controlled by ShowFlyoutWindow so
    // the first frame can be presented before the window becomes visible.
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, width, height, SWP_NOACTIVATE);
    ResizeRenderTarget();
}

// True when Windows reports the current connection as metered (Fixed or
// Variable cost). Windows knows this from the user's "metered connection"
// setting or a cellular profile; unknown costs and query failures count as
// unmetered so a detection problem never blocks the auto path.
static bool IsConnectionMetered() {
    INetworkCostManager* costManager = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_NetworkListManager, nullptr, CLSCTX_ALL,
                                  IID_PPV_ARGS(&costManager));
    if (FAILED(hr)) {
        Wh_Log(L"NetworkCostManager unavailable (hr 0x%08X)", (unsigned)hr);
        return false;
    }
    DWORD cost = NLM_CONNECTION_COST_UNKNOWN;
    hr = costManager->GetCost(&cost, nullptr);
    costManager->Release();
    if (FAILED(hr)) {
        Wh_Log(L"GetCost failed (hr 0x%08X)", (unsigned)hr);
        return false;
    }
    bool metered = (cost & (NLM_CONNECTION_COST_FIXED |
                            NLM_CONNECTION_COST_VARIABLE |
                            NLM_CONNECTION_COST_ROAMING)) != 0;
    Wh_Log(L"connection cost %u -> metered %d", (unsigned)cost, metered);
    return metered;
}

// ---------------------------------------------------------------------------
// Open and close animation
// ---------------------------------------------------------------------------
// The root visual fades and slides 8 px from its anchor edge. The DWM glass
// cannot fade, so it stays off while the window moves: the open plays over
// the solid frame and the glass comes on (with the usual scrim fade) once it
// settles; the close turns the glass off first and fades the solid frame.

static constexpr UINT_PTR kOpenDoneTimer = 8;
static constexpr UINT_PTR kCloseDoneTimer = 9;
static constexpr float kOpenMs = 160.0f;
static constexpr float kCloseMs = 120.0f;
static constexpr float kSlideDip = 8.0f;

static bool g_closing = false;
static ULONGLONG g_motionAt = 0;
static bool g_motionOpening = false;
static float g_motionFrom = 1.0f;
static float g_motionTo = 1.0f;
static float g_motionMs = 1.0f;

static bool EnsureMotion() {
    if (!g_composition || !g_dcompDevice || !g_dcompVisual) {
        return false;
    }
    if (!g_dcompEffect) {
        if (FAILED(g_dcompDevice->CreateEffectGroup(&g_dcompEffect))) {
            g_dcompEffect = nullptr;
            return false;
        }
        g_dcompVisual->SetEffect(g_dcompEffect);
    }
    if (!g_motionOpacity &&
        FAILED(g_dcompDevice->CreateAnimation(&g_motionOpacity))) {
        g_motionOpacity = nullptr;
        return false;
    }
    if (!g_motionOffset &&
        FAILED(g_dcompDevice->CreateAnimation(&g_motionOffset))) {
        g_motionOffset = nullptr;
        return false;
    }
    return true;
}

// Opening eases out (fast start, soft landing); closing eases in.
static float MotionCurve(float u, bool opening) {
    return opening ? 1.0f - (1.0f - u) * (1.0f - u) * (1.0f - u) : u * u;
}

static void SetMotionCurve(IDCompositionAnimation* animation, float from,
                           float to, float seconds, bool opening) {
    float d = to - from;
    float s = seconds;
    animation->Reset();
    if (opening) {
        animation->AddCubic(0.0, from, 3.0f * d / s, -3.0f * d / (s * s),
                            d / (s * s * s));
    } else {
        animation->AddCubic(0.0, from, 0.0f, d / (s * s), 0.0f);
    }
    animation->End(seconds, to);
}

// Opacity the window shows right now, so an interrupted open or close
// carries on from where it is instead of jumping.
static float MotionOpacityNow(bool visible) {
    if (!visible) {
        return 0.0f;
    }
    if (!g_motionAt) {
        return 1.0f;
    }
    float u = Clamp01((float)(Now() - g_motionAt) / g_motionMs);
    return g_motionFrom + (g_motionTo - g_motionFrom) * MotionCurve(u, g_motionOpening);
}

static bool PlayMotion(bool opening, float from) {
    if (!EnsureMotion()) {
        return false;
    }
    float to = opening ? 1.0f : 0.0f;
    float full = (opening ? kOpenMs : kCloseMs) * g_motionScale;
    float ms = std::max(1.0f, full * std::fabs(to - from));
    float slide = kSlideDip * g_scale * (g_anchorTop ? -1.0f : 1.0f);
    SetMotionCurve(g_motionOpacity, from, to, ms / 1000.0f, opening);
    SetMotionCurve(g_motionOffset, slide * (1.0f - from), slide * (1.0f - to),
                   ms / 1000.0f, opening);
    g_dcompEffect->SetOpacity(g_motionOpacity);
    g_dcompVisual->SetOffsetY(g_motionOffset);
    if (FAILED(g_dcompDevice->Commit())) {
        return false;
    }
    g_motionAt = Now();
    g_motionOpening = opening;
    g_motionFrom = from;
    g_motionTo = to;
    g_motionMs = ms;
    return true;
}

static void ResetMotion() {
    g_motionAt = 0;
    if (!g_dcompEffect || !g_dcompVisual || !g_dcompDevice) {
        return;
    }
    g_dcompEffect->SetOpacity(1.0f);
    g_dcompVisual->SetOffsetY(0.0f);
    g_dcompDevice->Commit();
}

// The glass comes on once the open animation has settled.
static void FinishOpen(HWND hwnd) {
    KillTimer(hwnd, kOpenDoneTimer);
    if (g_uiVisible && !g_closing && g_translucent) {
        ApplyBackdrop(hwnd, true);
        g_scrimFadeAt = Now();
        InvalidateRect(hwnd, nullptr, FALSE);
    }
}

static void FinishHide(HWND hwnd) {
    KillTimer(hwnd, kCloseDoneTimer);
    g_closing = false;
    ShowWindow(hwnd, SW_HIDE);
    ResetMotion();
}

static void ShowFlyoutWindow(HWND hwnd) {
    if (!hwnd) {
        return;
    }

    // A show during the close animation turns it round from where it is.
    float fromOpacity = g_closing || g_uiVisible ? MotionOpacityNow(true) : 0.0f;
    if (g_closing) {
        KillTimer(hwnd, kCloseDoneTimer);
        g_closing = false;
    }
    KillTimer(hwnd, kOpenDoneTimer);

    bool startTest = !TestRunning();
    if (startTest) {
        StateReset();
        g_gaugeShown = 0;
        g_view = View::Gauge;
        g_animating = false;
        g_copyUntil = 0;
        g_hot = Hot::None;
        g_pressed = Hot::None;
        g_focus = Hot::None;
        g_network = ReadNetwork();

        // Opening the flyout is the request to measure: no need to press
        // Start. The preference and the metered-connection flag gate it: with
        // "auto" a metered connection (Fixed/Variable cost in Windows) opens
        // the flyout idle so the user starts the transfer consciously, and
        // "never" always does. The idle view already carries the Start button.
        int startMode = g_autoStart.load(std::memory_order_relaxed);
        if (startMode == 0 && IsConnectionMetered()) {
            startMode = 2;
        }
        if (g_startFromTray.load(std::memory_order_relaxed)) {
            // A tray click promised the test: run it right away even on a
            // metered link, then hand the decision back to the settings.
            g_startFromTray.store(false, std::memory_order_relaxed);
            startMode = 1;
        }
        if (startMode == 2) {
            StateSetCaption(g_str->ready);
            g_focus = Hot::Start;
            startTest = false;
        }
    }
    g_detailModes = g_pendingDetailModes.load();
    ResetDetailReveal();
    g_layoutHeight = ViewHeight(g_view);
    g_heightFrom = g_layoutHeight;

    RefreshAppearance();
    RefreshMotion();

    // Start from the solid surface and present one fully opaque frame before
    // the window becomes visible. The material is turned on only afterwards:
    // before that DWM does not attach it.
    ApplyBackdrop(hwnd, false);
    g_scrimFadeAt = 0;

    PositionFlyout(hwnd, MonitorUnderCursor());
    InvalidateRect(hwnd, nullptr, FALSE);
    UpdateWindow(hwnd);

    // The first composed frame is already the start of the fade, so the
    // window never flashes in at full strength.
    bool animated = g_motionAllowed && fromOpacity < 0.99f &&
                    PlayMotion(true, fromOpacity);
    if (!animated) {
        ResetMotion();
    }

    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE |
                     SWP_SHOWWINDOW);
    g_previousForeground = GetForegroundWindow();
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    g_uiVisible = true;
    g_mouseButtonsDown = MouseButtonsDown();
    SetTimer(hwnd, 1, 16, nullptr);
    InvalidateRect(hwnd, nullptr, FALSE);
    UpdateWindow(hwnd);

    // Now that the window is visible, setting the attribute is a real change.
    // The scrim stays up for the first frames and then fades to transparent.
    // With the open animation the glass waits until the window has settled.
    if (animated) {
        SetTimer(hwnd, kOpenDoneTimer, (UINT)std::ceil(g_motionMs), nullptr);
    } else {
        FinishOpen(hwnd);
    }

    if (startTest) {
        StartOrCancelTest(hwnd);
    }
}

static void HideFlyoutWindow(HWND hwnd, bool restoreForeground = true) {
    if (!hwnd || g_closing) {
        return;
    }
    bool visible = IsWindowVisible(hwnd) != FALSE;
    float fromOpacity = MotionOpacityNow(visible);
    KillTimer(hwnd, 1);
    KillTimer(hwnd, kRetryStartTimer);
    KillTimer(hwnd, kOpenDoneTimer);
    // Leave the material off so the next show is a state change DWM honours.
    // It goes off before the close animation too: the glass cannot fade.
    ApplyBackdrop(hwnd, false);
    g_scrimFadeAt = 0;
    g_uiVisible = false;
    g_hot = Hot::None;
    g_pressed = Hot::None;
    g_focus = Hot::None;
    // A flyout hands focus back to the window it was opened from.
    if (restoreForeground && g_previousForeground && g_previousForeground != hwnd &&
        IsWindow(g_previousForeground)) {
        SetForegroundWindow(g_previousForeground);
    }
    g_previousForeground = nullptr;

    if (visible && g_motionAllowed && fromOpacity > 0.01f) {
        // Repaint with the solid scrim the fade starts from.
        InvalidateRect(hwnd, nullptr, FALSE);
        UpdateWindow(hwnd);
        if (PlayMotion(false, fromOpacity)) {
            g_closing = true;
            // One extra frame so the last, fully clear one is composed.
            SetTimer(hwnd, kCloseDoneTimer, (UINT)std::ceil(g_motionMs) + 16,
                     nullptr);
            return;
        }
    }
    FinishHide(hwnd);
}

// ---------------------------------------------------------------------------
// Actions and keyboard focus
// ---------------------------------------------------------------------------

// One entry point for mouse clicks, keyboard activation and MSAA, so all three
// paths behave identically.
static void ActivateHot(HWND hwnd, Hot hot) {
    if (g_closing) {
        return;  // A click on the window while it fades out does nothing.
    }
    switch (hot) {
        case Hot::Settings:
            speedset::OpenSettingsWindow();
            break;
        case Hot::Close:
            if (TestRunning()) {
                RequestTestCancel();
            }
            HideFlyoutWindow(hwnd);
            break;
        case Hot::Start:
        case Hot::Retry:
            StartOrCancelTest(hwnd);
            break;
        case Hot::Copy:
            CopyResult(hwnd, CopyState());
            break;
        default:
            break;
    }
}

static int AccChildId(Hot hot) {
    switch (hot) {
        case Hot::Settings:
            return 4;
        case Hot::Close:
            return 1;
        case Hot::Start:
        case Hot::Retry:
            return 2;
        case Hot::Copy:
            return 3;
        default:
            return 0;
    }
}

static Hot HotFromAccChild(int id) {
    switch (id) {
        case 4:
            return Hot::Settings;
        case 1:
            return Hot::Close;
        case 2:
            return g_view == View::Error ? Hot::Retry : Hot::Start;
        case 3:
            return Hot::Copy;
        default:
            return Hot::None;
    }
}

static std::vector<Hot> FocusOrder() {
    std::vector<Hot> order;
    order.push_back(Hot::Settings);
    order.push_back(Hot::Close);
    if (g_view == View::Error) {
        order.push_back(Hot::Retry);
        return order;
    }
    if (g_view == View::Results) {
        order.push_back(Hot::Copy);
    }
    order.push_back(Hot::Start);
    return order;
}

static void MoveFocus(int delta) {
    std::vector<Hot> order = FocusOrder();
    if (order.empty()) {
        return;
    }
    int index = -1;
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i] == g_focus) {
            index = (int)i;
        }
    }
    int next = index < 0 ? (delta > 0 ? 0 : (int)order.size() - 1)
                         : (index + delta + (int)order.size()) % (int)order.size();
    if (order[next] == g_focus) {
        return;
    }
    g_focus = order[next];
    NotifyWinEvent(EVENT_OBJECT_FOCUS, g_flyoutHwnd, OBJID_CLIENT,
                   AccChildId(g_focus));
    InvalidateRect(g_flyoutHwnd, nullptr, FALSE);
}

static bool IsAvailableHot(Hot hot) {
    switch (hot) {
        case Hot::Settings:
        case Hot::Close:
            return true;
        case Hot::Start:
            return g_view != View::Error;
        case Hot::Copy:
            return g_view == View::Results;
        case Hot::Retry:
            return g_view == View::Error;
        default:
            return false;
    }
}

static D2D1_RECT_F HotRect(Hot hot) {
    switch (hot) {
        case Hot::Settings:
            return kSettingsRect;
        case Hot::Start:
            return StartButtonRect(CopyState());
        case Hot::Copy:
            return kCopyRect;
        case Hot::Close:
            return kCloseRect;
        case Hot::Retry:
            return kRetryRect;
        default:
            return Rect(0, 0, 0, 0);
    }
}

class FlyoutAccessible final : public IAccessible {
public:
    explicit FlyoutAccessible(HWND hwnd) : hwnd_(hwnd) {}

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override {
        if (!object) {
            return E_POINTER;
        }
        *object = nullptr;
        if (riid == IID_IUnknown || riid == IID_IDispatch || riid == IID_IAccessible) {
            *object = static_cast<IAccessible*>(this);
            AddRef();
            return S_OK;
        }
        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE AddRef() override {
        return (ULONG)InterlockedIncrement(&references_);
    }

    ULONG STDMETHODCALLTYPE Release() override {
        LONG remaining = InterlockedDecrement(&references_);
        if (remaining == 0) {
            delete this;
        }
        return (ULONG)remaining;
    }

    HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT* count) override {
        if (!count) {
            return E_POINTER;
        }
        *count = 0;
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT, LCID, ITypeInfo**) override {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID,
                                             DISPID*) override {
        return DISP_E_UNKNOWNNAME;
    }

    HRESULT STDMETHODCALLTYPE Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*,
                                     VARIANT*, EXCEPINFO*, UINT*) override {
        return DISP_E_MEMBERNOTFOUND;
    }

    HRESULT STDMETHODCALLTYPE get_accParent(IDispatch** parent) override {
        if (!parent) {
            return E_POINTER;
        }
        *parent = nullptr;
        return S_FALSE;
    }

    HRESULT STDMETHODCALLTYPE get_accChildCount(long* count) override {
        if (!count) {
            return E_POINTER;
        }
        *count = (long)FocusOrder().size();
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE get_accChild(VARIANT, IDispatch** child) override {
        if (!child) {
            return E_POINTER;
        }
        *child = nullptr;
        return S_FALSE;
    }

    HRESULT STDMETHODCALLTYPE get_accName(VARIANT child, BSTR* name) override {
        if (!name) {
            return E_POINTER;
        }
        PCWSTR value = nullptr;
        if (IsSelf(child)) {
            value = L"Speedtest";
        } else {
            Hot hot = ChildHot(child);
            if (!IsAvailableHot(hot)) {
                return E_INVALIDARG;
            }
            switch (hot) {
                case Hot::Settings:
                    value = L"Settings";
                    break;
                case Hot::Close:
                    value = g_str->closeName;
                    break;
                case Hot::Copy:
                    value = g_str->copy;
                    break;
                case Hot::Retry:
                    value = g_str->retry;
                    break;
                case Hot::Start: {
                    TestState state = CopyState();
                    value = StartButtonLabel(state);
                    break;
                }
                default:
                    return E_INVALIDARG;
            }
        }
        *name = SysAllocString(value);
        return *name ? S_OK : E_OUTOFMEMORY;
    }

    HRESULT STDMETHODCALLTYPE get_accValue(VARIANT child, BSTR* value) override {
        if (!value) {
            return E_POINTER;
        }
        if (!IsSelf(child)) {
            *value = nullptr;
            return S_FALSE;
        }
        TestState state = CopyState();
        std::wstring status = state.caption;
        if (state.phase == Phase::Download || state.phase == Phase::Upload) {
            status += L" ";
            status += FormatNumber(state.currentMbps);
            status += L" Mbps";
        }
        *value = SysAllocString(status.c_str());
        return *value ? S_OK : E_OUTOFMEMORY;
    }

    HRESULT STDMETHODCALLTYPE put_accValue(VARIANT, BSTR) override {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_accDescription(VARIANT child,
                                                  BSTR* description) override {
        if (!description) {
            return E_POINTER;
        }
        *description = nullptr;
        return IsValidChild(child) ? S_FALSE : E_INVALIDARG;
    }

    HRESULT STDMETHODCALLTYPE get_accRole(VARIANT child, VARIANT* role) override {
        if (!role) {
            return E_POINTER;
        }
        if (!IsValidChild(child)) {
            return E_INVALIDARG;
        }
        VariantInit(role);
        role->vt = VT_I4;
        role->lVal = IsSelf(child) ? ROLE_SYSTEM_WINDOW : ROLE_SYSTEM_PUSHBUTTON;
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE get_accState(VARIANT child, VARIANT* state) override {
        if (!state) {
            return E_POINTER;
        }
        if (!IsValidChild(child)) {
            return E_INVALIDARG;
        }
        VariantInit(state);
        state->vt = VT_I4;
        if (!IsSelf(child)) {
            Hot hot = ChildHot(child);
            state->lVal = STATE_SYSTEM_FOCUSABLE;
            if (hot == g_focus && GetFocus() == hwnd_) {
                state->lVal |= STATE_SYSTEM_FOCUSED;
            }
        } else {
            state->lVal = 0;
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE get_accHelp(VARIANT, BSTR* help) override {
        if (!help) {
            return E_POINTER;
        }
        *help = nullptr;
        return S_FALSE;
    }

    HRESULT STDMETHODCALLTYPE get_accHelpTopic(BSTR* helpFile, VARIANT,
                                                long* topic) override {
        if (!helpFile || !topic) {
            return E_POINTER;
        }
        *helpFile = nullptr;
        *topic = 0;
        return S_FALSE;
    }

    HRESULT STDMETHODCALLTYPE get_accKeyboardShortcut(VARIANT child,
                                                       BSTR* shortcut) override {
        if (!shortcut) {
            return E_POINTER;
        }
        if (!IsValidChild(child) || IsSelf(child)) {
            return E_INVALIDARG;
        }
        *shortcut = SysAllocString(g_str == &kStringsIt ? L"Tab / Invio"
                                                        : L"Tab / Enter");
        return *shortcut ? S_OK : E_OUTOFMEMORY;
    }

    HRESULT STDMETHODCALLTYPE get_accFocus(VARIANT* child) override {
        if (!child) {
            return E_POINTER;
        }
        VariantInit(child);
        if (g_focus == Hot::None || !IsAvailableHot(g_focus)) {
            child->vt = VT_EMPTY;
        } else {
            child->vt = VT_I4;
            child->lVal = AccChildId(g_focus);
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE get_accSelection(VARIANT* selection) override {
        return get_accFocus(selection);
    }

    HRESULT STDMETHODCALLTYPE get_accDefaultAction(VARIANT child,
                                                    BSTR* action) override {
        if (!action) {
            return E_POINTER;
        }
        if (!IsValidChild(child) || IsSelf(child)) {
            return E_INVALIDARG;
        }
        *action = SysAllocString(g_str == &kStringsIt ? L"Attiva" : L"Activate");
        return *action ? S_OK : E_OUTOFMEMORY;
    }

    HRESULT STDMETHODCALLTYPE accSelect(long flags, VARIANT child) override {
        if (!IsValidChild(child) || IsSelf(child)) {
            return E_INVALIDARG;
        }
        if (flags & SELFLAG_TAKEFOCUS) {
            Hot hot = ChildHot(child);
            g_focus = hot;
            SetFocus(hwnd_);
            NotifyWinEvent(EVENT_OBJECT_FOCUS, hwnd_, OBJID_CLIENT, AccChildId(hot));
            InvalidateRect(hwnd_, nullptr, FALSE);
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE accLocation(long* left, long* top, long* width,
                                          long* height, VARIANT child) override {
        if (!left || !top || !width || !height) {
            return E_POINTER;
        }
        if (!IsValidChild(child)) {
            return E_INVALIDARG;
        }

        RECT windowRect = {};
        if (!GetWindowRect(hwnd_, &windowRect)) {
            return HRESULT_FROM_WIN32(GetLastError());
        }
        if (IsSelf(child)) {
            *left = windowRect.left;
            *top = windowRect.top;
            *width = windowRect.right - windowRect.left;
            *height = windowRect.bottom - windowRect.top;
            return S_OK;
        }

        D2D1_RECT_F rect = HotRect(ChildHot(child));
        *left = windowRect.left + (long)std::lround(rect.left * g_scale);
        *top = windowRect.top + (long)std::lround(rect.top * g_scale);
        *width = (long)std::lround((rect.right - rect.left) * g_scale);
        *height = (long)std::lround((rect.bottom - rect.top) * g_scale);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE accNavigate(long direction, VARIANT start,
                                           VARIANT* end) override {
        if (!end) {
            return E_POINTER;
        }
        VariantInit(end);
        std::vector<Hot> order = FocusOrder();
        if (order.empty()) {
            return S_FALSE;
        }
        int index = -1;
        if (start.vt == VT_I4 && start.lVal != CHILDID_SELF) {
            Hot current = HotFromAccChild(start.lVal);
            for (size_t i = 0; i < order.size(); i++) {
                if (order[i] == current) {
                    index = (int)i;
                    break;
                }
            }
        }
        int next = -1;
        if (direction == NAVDIR_FIRSTCHILD) {
            next = 0;
        } else if (direction == NAVDIR_LASTCHILD) {
            next = (int)order.size() - 1;
        } else if (direction == NAVDIR_NEXT && index >= 0 &&
                   index + 1 < (int)order.size()) {
            next = index + 1;
        } else if (direction == NAVDIR_PREVIOUS && index > 0) {
            next = index - 1;
        }
        if (next < 0) {
            return S_FALSE;
        }
        end->vt = VT_I4;
        end->lVal = AccChildId(order[(size_t)next]);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE accHitTest(long x, long y, VARIANT* child) override {
        if (!child) {
            return E_POINTER;
        }
        VariantInit(child);
        POINT point = {x, y};
        if (!ScreenToClient(hwnd_, &point)) {
            return HRESULT_FROM_WIN32(GetLastError());
        }
        Hot hot = HitTest((float)point.x / g_scale, (float)point.y / g_scale);
        child->vt = VT_I4;
        child->lVal = hot == Hot::None ? CHILDID_SELF : AccChildId(hot);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE accDoDefaultAction(VARIANT child) override {
        if (!IsValidChild(child) || IsSelf(child)) {
            return E_INVALIDARG;
        }
        return PostMessageW(hwnd_, WM_APP + 3, AccChildId(ChildHot(child)), 0)
                   ? S_OK
                   : HRESULT_FROM_WIN32(GetLastError());
    }

    HRESULT STDMETHODCALLTYPE put_accName(VARIANT, BSTR) override {
        return E_NOTIMPL;
    }

private:
    bool IsSelf(const VARIANT& child) const {
        return child.vt == VT_I4 && child.lVal == CHILDID_SELF;
    }

    Hot ChildHot(const VARIANT& child) const {
        return child.vt == VT_I4 ? HotFromAccChild(child.lVal) : Hot::None;
    }

    bool IsValidChild(const VARIANT& child) const {
        return IsSelf(child) || IsAvailableHot(ChildHot(child));
    }

    volatile LONG references_ = 1;
    HWND hwnd_;
};

static FlyoutAccessible* g_accessible = nullptr;

static void TickFlyout(HWND hwnd) {
    // Repaint only when something actually changes: idle frames would make
    // DWM re-composite the acrylic material for nothing and stutter the
    // scrim fade.
    POINT borderPointer{};
    bool hovered = GetCursorPos(&borderPointer) && WindowFromPoint(borderPointer) == hwnd;
    bool repaint = ScrimFading() || hovered != g_borderHovered;
    g_borderHovered = hovered;

    TestState state = CopyState();
    UINT mouseButtonsDown = MouseButtonsDown();
    UINT newlyPressedButtons = mouseButtonsDown & ~g_mouseButtonsDown;
    g_mouseButtonsDown = mouseButtonsDown;
    if (g_uiVisible && newlyPressedButtons && !StateRunning(state)) {
        POINT cursor = {};
        RECT flyout = {};
        if (GetCursorPos(&cursor) && GetWindowRect(hwnd, &flyout) &&
            !PtInRect(&flyout, cursor)) {
            HideFlyoutWindow(hwnd, false);
            return;
        }
    }

    // The ring shows throughput. Start each transfer phase from an empty ring
    // instead of letting the small latency arc decay into a visible blob while
    // the download figure is still 0.0.
    static Phase lastPhase = Phase::Idle;
    if (state.phase != lastPhase) {
        NotifyWinEvent(EVENT_OBJECT_VALUECHANGE, hwnd, OBJID_CLIENT, CHILDID_SELF);
        if (state.phase == Phase::Warmup || state.phase == Phase::Download ||
            state.phase == Phase::Upload || state.phase == Phase::Stopping ||
            state.phase == Phase::Idle || state.phase == Phase::Canceled) {
            g_gaugeShown = 0;
            repaint = true;
        }
        lastPhase = state.phase;
    }

    if (g_testThread && !StateRunning(state)) {
        if (WaitForSingleObject(g_testThread, 0) == WAIT_OBJECT_0) {
            CloseHandle(g_testThread);
            g_testThread = nullptr;
        }
    }

    View previousView = g_view;
    bool previousAnimating = g_animating;
    if (state.phase == Phase::Done && g_view != View::Results && !g_animating) {
        BeginView(View::Results);
    } else if (state.phase == Phase::Error && g_view != View::Error) {
        BeginView(View::Error);
        g_hot = Hot::None;
    } else if (state.phase == Phase::Canceled && g_view == View::Results) {
        BeginView(View::Gauge);
    }

    unsigned modes = g_pendingDetailModes.load();
    if (modes != g_detailModes) {
        g_detailModes = modes;
        ResetDetailReveal();
        repaint = true;
    }
    ULONGLONG now = Now();
    float step = !AnimationsEnabled() ? 1.0f :
                 static_cast<float>(std::min<ULONGLONG>(150, now - g_detailTick)) / 150.0f;
    g_detailTick = now;
    for (size_t i = 0; i < ARRAYSIZE(kDetailLabels); ++i) {
        bool show = (DetailDisplay(i) == DetailMode::Hover && g_hoverDetail == static_cast<int>(i)) ||
                    (DetailDisplay(i) == DetailMode::Click && (g_clickedDetails & (1u << i)));
        float old = g_detailOpacity[i];
        g_detailOpacity[i] = show ? std::min(1.0f, old + step) : std::max(0.0f, old - step);
        repaint |= old != g_detailOpacity[i];
    }

    float previousHeight = g_layoutHeight;
    if (g_animating) {
        float t = AnimT();
        float eased = t * t * (3.0f - 2.0f * t);
        float targetHeight = ViewHeight(g_view);
        g_layoutHeight = g_heightFrom + (targetHeight - g_heightFrom) * eased;
    } else {
        g_layoutHeight = ViewHeight(g_view);
    }
    if (std::fabs(g_layoutHeight - previousHeight) > 0.25f) {
        PositionFlyout(hwnd, MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST));
        repaint = true;
    }

    if (g_view != previousView || g_animating != previousAnimating) {
        repaint = true;
    }

    double target = 0;
    if (state.phase == Phase::Latency) {
        // Show idle latency only in the lower stats and keep the speed ring empty.
        target = 0;
    } else if (state.phase == Phase::Download || state.phase == Phase::Upload) {
        target = state.currentMbps;
    } else if (state.phase == Phase::Done) {
        target = state.download;
    }
    double targetFraction = GaugeFraction(target);
    double previousGauge = g_gaugeShown;
    g_gaugeShown += (targetFraction - g_gaugeShown) * 0.18;
    if (std::fabs(targetFraction - g_gaugeShown) < 0.0015) {
        g_gaugeShown = targetFraction;
    }
    if (std::fabs(g_gaugeShown - previousGauge) > 0.0005) {
        repaint = true;
    }

    if (g_animating && AnimT() >= 1.0f) {
        g_animating = false;
        repaint = true;
    }

    // A running test updates live figures every tick; the copy toast has a
    // deadline that needs a final repaint to disappear.
    if (StateRunning(state) || g_animating) {
        repaint = true;
    }
    if (g_copyUntil) {
        if (Now() < g_copyUntil) {
            repaint = true;
        } else {
            g_copyUntil = 0;
            repaint = true;
        }
    }

    if (repaint) {
        InvalidateRect(hwnd, nullptr, FALSE);
    }
}

static LRESULT CALLBACK FlyoutWndProc(HWND hwnd, UINT message, WPARAM wParam,
                                      LPARAM lParam) {
    switch (message) {
        case WM_ERASEBKGND:
            return 1;

        case WM_GETOBJECT:
            if ((LONG)lParam == OBJID_CLIENT) {
                if (!g_accessible) {
                    g_accessible = new (std::nothrow) FlyoutAccessible(hwnd);
                }
                return g_accessible
                           ? LresultFromObject(IID_IAccessible, wParam, g_accessible)
                           : 0;
            }
            break;

        case WM_PAINT: {
            PAINTSTRUCT paint = {};
            HDC dc = BeginPaint(hwnd, &paint);
            if (EnsureRenderTarget()) {
                g_renderTarget->BeginDraw();
                TestState state = CopyState();
                DrawFrame(state);
                HRESULT result = g_renderTarget->EndDraw();
                if (result == D2DERR_RECREATE_TARGET) {
                    ReleaseTargets();
                } else if (FAILED(result)) {
                    static int endDrawFailures = 0;
                    if (endDrawFailures++ < 3) {
                        Wh_Log(L"EndDraw failed 0x%08X", (unsigned)result);
                    }
                    ReleaseTargets();
                } else if (g_composition && g_swapChain) {
                    // Sync interval 0: the swap chain is composed by DWM on
                    // its own clock, so waiting for a vblank here only blocks
                    // the UI thread inside WM_PAINT.
                    HRESULT present = g_swapChain->Present(0, 0);
                    if (FAILED(present)) {
                        Wh_Log(L"Present failed 0x%08X", (unsigned)present);
                        ReleaseTargets();
                    }
                }
            }
            EndPaint(hwnd, &paint);
            return 0;
        }

        case WM_SIZE:
            if (g_renderTarget) {
                ResizeRenderTarget();
            }
            return 0;

        case WM_TIMER:
            if (wParam == 1) {
                TickFlyout(hwnd);
            } else if (wParam == kRetryStartTimer) {
                KillTimer(hwnd, kRetryStartTimer);
                if (!StateRunning(CopyState())) {
                    StartOrCancelTest(hwnd);
                }
            } else if (wParam == kOpenDoneTimer) {
                FinishOpen(hwnd);
            } else if (wParam == kCloseDoneTimer) {
                FinishHide(hwnd);
            }
            return 0;

        case WM_MOUSEMOVE: {
            float x = (float)GET_X_LPARAM(lParam) / g_scale;
            float y = (float)GET_Y_LPARAM(lParam) / g_scale;
            g_hoverDetail = DetailAt(x, y);
            Hot hot = HitTest(x, y);
            bool focusChanged = g_focus != Hot::None;
            if (hot != g_hot || focusChanged) {
                g_hot = hot;
                g_focus = Hot::None;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            TRACKMOUSEEVENT track = {sizeof(track), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&track);
            return 0;
        }

        case WM_MOUSELEAVE:
            g_hoverDetail = -1;
            if (g_hot != Hot::None) {
                g_hot = Hot::None;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;

        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT) {
                POINT point = {};
                GetCursorPos(&point);
                ScreenToClient(hwnd, &point);
                int detail = DetailAt(point.x / g_scale, point.y / g_scale);
                Hot hot = HitTest((float)point.x / g_scale, (float)point.y / g_scale);
                if (hot != Hot::None || (detail >= 0 && DetailDisplay(detail) == DetailMode::Click)) {
                    SetCursor(LoadCursorW(nullptr, IDC_HAND));
                    return TRUE;
                }
            }
            break;

        case WM_LBUTTONDOWN: {
            float x = (float)GET_X_LPARAM(lParam) / g_scale;
            float y = (float)GET_Y_LPARAM(lParam) / g_scale;
            g_pressed = HitTest(x, y);
            if (g_pressed != Hot::None) {
                SetCapture(hwnd);
            }
            return 0;
        }

        case WM_LBUTTONUP: {
            float x = (float)GET_X_LPARAM(lParam) / g_scale;
            float y = (float)GET_Y_LPARAM(lParam) / g_scale;
            int detail = DetailAt(x, y);
            if (detail >= 0 && DetailDisplay(detail) == DetailMode::Click)
                g_clickedDetails ^= 1u << detail;
            Hot hot = HitTest(x, y);
            Hot pressed = g_pressed;
            g_pressed = Hot::None;
            if (GetCapture() == hwnd) {
                ReleaseCapture();
            }
            if (hot != Hot::None && hot == pressed) {
                ActivateHot(hwnd, hot);
            }
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }

        case WM_KEYDOWN:
            if (wParam == VK_TAB) {
                MoveFocus((GetKeyState(VK_SHIFT) & 0x8000) ? -1 : 1);
                return 0;
            }
            if ((wParam == VK_RETURN || wParam == VK_SPACE) &&
                g_focus != Hot::None) {
                ActivateHot(hwnd, g_focus);
                return 0;
            }
            if (wParam == VK_ESCAPE) {
                if (TestRunning()) {
                    RequestTestCancel();
                } else {
                    HideFlyoutWindow(hwnd);
                }
                return 0;
            }
            break;

        case WM_ACTIVATE:
            if (LOWORD(wParam) == WA_INACTIVE && g_uiVisible &&
                !TestRunning()) {
                HideFlyoutWindow(hwnd, false);
            }
            // Let DefWindowProc run so the click-back focus handling continues;
            // returning 0 here left the previously active window without
            // restored focus.
            break;

        case WM_DPICHANGED: {
            UINT dpi = HIWORD(wParam);
            if (dpi == 0) {
                dpi = LOWORD(wParam);
            }
            if (dpi) {
                g_dpi = (float)dpi;
                g_scale = g_dpi / 96.0f;
            }
            // Re-anchor to the work area instead of the suggested rect: the
            // flyout is positioned manually above the taskbar.
            PositionFlyout(hwnd, MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST));
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }

        case WM_SETTINGCHANGE:
            // Follow a light/dark switch or a transparency toggle without
            // waiting for the next time the flyout is opened.
            if (wParam == 0 && lParam &&
                _wcsicmp((PCWSTR)lParam, L"ImmersiveColorSet") == 0) {
                RefreshBackdrop(hwnd);
            }
            return 0;

        case WM_THEMECHANGED:
            // High contrast and theme switches arrive here as well; the
            // capability check decides whether the material may stay on.
            RefreshBackdrop(hwnd);
            return 0;

        case WM_DWMCOMPOSITIONCHANGED:
            RefreshBackdrop(hwnd);
            return 0;

        case WM_CLOSE:
            if (TestRunning()) {
                RequestTestCancel();
            }
            HideFlyoutWindow(hwnd);
            return 0;

        case WM_DESTROY:
            if (g_accessible) {
                // A client (Narrator, Inspect, ...) may still hold a
                // reference; disconnect it from this object's vtable so a
                // late call after the DLL is unloaded cannot crash the host.
                CoDisconnectObject(g_accessible, 0);
                g_accessible->Release();
                g_accessible = nullptr;
            }
            g_flyoutHwnd = nullptr;
            PostQuitMessage(0);
            return 0;

        default:
            if (message == WM_APP + 2) {
                DestroyWindow(hwnd);
                return 0;
            }
            if (message == g_showMessage) {
                ShowFlyoutWindow(hwnd);
                return 0;
            }
            if (message == kTrayToggleMessage) {
                ToggleTrayButton(wParam != 0);
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            if (message == WM_APP + 1) {
                TickFlyout(hwnd);
                return 0;
            }
            if (message == WM_APP + 4) {
                NetworkInfo network = ReadNetworkByIndex(
                    (ULONG)wParam, (ADDRESS_FAMILY)lParam);
                if (!network.name.empty()) {
                    g_network = network;
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
                return 0;
            }
            if (message == WM_APP + 3) {
                Hot hot = HotFromAccChild((int)wParam);
                if (IsAvailableHot(hot)) {
                    ActivateHot(hwnd, hot);
                }
                return 0;
            }
            break;
    }

    return DefWindowProcW(hwnd, message, wParam, lParam);
}

// ---------------------------------------------------------------------------
// UI thread and module lifecycle
// ---------------------------------------------------------------------------

// Returns the module of the calling code (the mod DLL), not the host. Used as
// the window class instance so registration/unregistration is scoped to the
// mod's own module, as Windhawk conventions expect.
// The module handle of the mod image: the class name then belongs to the
// mod and disappears with it, not with the host. Declared up top with the
// tray button section; this is the same linker-provided symbol.
extern "C" IMAGE_DOS_HEADER __ImageBase;

static DWORD WINAPI UiThreadProc(LPVOID) {
    HRESULT comResult = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    bool comInitialized = SUCCEEDED(comResult);
    if (FAILED(comResult) && comResult != RPC_E_CHANGED_MODE) {
        Wh_Log(L"COM initialization failed (error 0x%08X)", (unsigned)comResult);
    }

    RefreshAppearance();

    WNDCLASSEXW windowClass = {sizeof(windowClass)};
    // No CS_DROPSHADOW: it draws a square shadow around the window rect, which
    // stays square while DWM clips the material to rounded corners.
    windowClass.style = 0;
    windowClass.lpfnWndProc = FlyoutWndProc;
    windowClass.hInstance = (HINSTANCE)&__ImageBase;
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.hbrBackground = nullptr;
    windowClass.lpszClassName = kFlyoutClass;
    if (!RegisterClassExW(&windowClass)) {
        Wh_Log(L"RegisterClassExW failed (error %u)", GetLastError());
        if (comInitialized) {
            CoUninitialize();
        }
        return 1;
    }

    HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST |
                                    WS_EX_NOREDIRECTIONBITMAP,
                                kFlyoutClass, L"Speedtest", WS_POPUP, 0, 0,
                                (int)std::lround(kWidth), (int)std::lround(kGaugeHeight),
                                nullptr, nullptr, windowClass.hInstance, nullptr);
    if (!hwnd) {
        Wh_Log(L"CreateWindowExW failed (error %u)", GetLastError());
        UnregisterClassW(kFlyoutClass, windowClass.hInstance);
        if (comInitialized) {
            CoUninitialize();
        }
        return 1;
    }
    g_flyoutHwnd = hwnd;
    // The shell hooks post the show request from explorer.exe and the shell
    // hosts; let it through even if this process runs with higher rights.
    ChangeWindowMessageFilterEx(hwnd, g_showMessage, MSGFLT_ALLOW, nullptr);

    // The tray button lives on the same thread as the flyout and dies with it.
    AddTrayButton();

    // Rounded corners and a solid frame on Windows 11.
    int corner = 2;  // DWMWCP_ROUND
    DwmSetWindowAttribute(hwnd, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner,
                          sizeof(corner));

    COLORREF border = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
    DwmSetWindowAttribute(hwnd, 34 /* DWMWA_BORDER_COLOR */, &border, sizeof(border));

    // Desktop Acrylic is composed over the whole window only when the frame is
    // extended: on a captionless popup with zero margins DWM keeps the solid
    // fallback. This is a one-time setup; the runtime state is driven by
    // ApplyBackdrop().
    MARGINS margins = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    ApplyBackdrop(hwnd, false);

    D2D1_FACTORY_OPTIONS options = {};
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                                 __uuidof(ID2D1Factory), &options,
                                 (void**)&g_d2dFactory))) {
        g_d2dFactory = nullptr;
    }
    if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                  __uuidof(IDWriteFactory),
                                  (IUnknown**)&g_dwriteFactory))) {
        g_dwriteFactory = nullptr;
    }

    D2D1_STROKE_STYLE_PROPERTIES strokeProperties = {};
    strokeProperties.startCap = D2D1_CAP_STYLE_ROUND;
    strokeProperties.endCap = D2D1_CAP_STYLE_ROUND;
    strokeProperties.dashCap = D2D1_CAP_STYLE_ROUND;
    strokeProperties.lineJoin = D2D1_LINE_JOIN_ROUND;
    if (g_d2dFactory) {
        g_d2dFactory->CreateStrokeStyle(strokeProperties, nullptr, 0, &g_roundStroke);
    }

    Wh_Log(L"Flyout window ready");

    // A mod unload can arrive while this thread is still starting up. In that
    // case the message loop would never receive WM_QUIT, so check the flag
    // before entering it.
    if (InterlockedCompareExchange(&g_shutdown, 0, 0)) {
        DestroyWindow(hwnd);
    } else {
        MSG msg;
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    if (IsWindow(hwnd)) {
        DestroyWindow(hwnd);
    }
    g_cancelRequested.store(1, std::memory_order_relaxed);
    // The test thread is owned (and waited for) by WhTool_ModUninit, which runs
    // before the DLL is unloaded. Waiting here as well could keep the UI
    // thread alive past that point.
    ReleaseGraphics();
    g_flyoutHwnd = nullptr;
    RemoveTrayButton();
    UnregisterClassW(kFlyoutClass, windowClass.hInstance);
    if (comInitialized) {
        CoUninitialize();
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Process roles
// ---------------------------------------------------------------------------
// 2.0 hosted the flyout, the tray button and the test inside explorer.exe, and
// a fault in that code took the whole taskbar down (8:52 am, 2026-11-19).
// From 2.1 the mod is a Windhawk tool mod:
// - windhawk.exe only asks Windhawk to start the mod's own process.
// - The mod's own process (WhTool_*) runs the flyout, tray button and test.
// - explorer.exe and the shell hosts (WhToolLauncher_*) only keep the small
//   hooks that turn the network menu's speed test link into a show request.

static bool IsCurrentExe(PCWSTR exe) {
    wchar_t path[MAX_PATH * 2] = {};
    DWORD length = GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    if (!length || length >= ARRAYSIZE(path)) {
        return false;
    }
    PCWSTR name = wcsrchr(path, L'\\');
    name = name ? name + 1 : path;
    return _wcsicmp(name, exe) == 0;
}

static void RegisterSharedMessages() {
    g_showMessage = RegisterWindowMessageW(L"SpeedTestFlyout.Show");
    if (!g_showMessage) {
        Wh_Log(L"RegisterWindowMessage failed (error %u)", GetLastError());
    }
    g_taskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
}

static void InstallShellHooks() {
    // Import-form hooks: referencing ShellExecuteExW/ShellExecuteW makes the
    // mod import shell32 (a KnownDLL, so it is loaded with the mod), and the
    // two hooks can no longer be silently missing in a host that loads
    // shell32 later.
    if (!WindhawkUtils::SetFunctionHook(ShellExecuteExW, ShellExecuteExW_Hook,
                                        &ShellExecuteExW_Original)) {
        Wh_Log(L"Unable to hook ShellExecuteExW");
    }
    if (!WindhawkUtils::SetFunctionHook(ShellExecuteW, ShellExecuteW_Hook,
                                        &ShellExecuteW_Original)) {
        Wh_Log(L"Unable to hook ShellExecuteW");
    }

    HMODULE kernelBase = GetModuleHandleW(L"kernelbase.dll");
    HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
    HMODULE kernel = kernelBase ? kernelBase : kernel32;
    auto createProcessW = kernel
                              ? (CreateProcessW_t)GetProcAddress(kernel, "CreateProcessW")
                              : nullptr;
    if (createProcessW &&
        !WindhawkUtils::SetFunctionHook(createProcessW, CreateProcessW_Hook,
                                        &CreateProcessW_Original)) {
        Wh_Log(L"Unable to hook CreateProcessW");
    }
}

// --- Shell processes and windhawk.exe -------------------------------------

BOOL WhToolLauncher_ModInit(BOOL* launch) {
    if (IsCurrentExe(L"windhawk.exe")) {
        *launch = TRUE;
        return TRUE;
    }
    *launch = FALSE;
    LoadSettings();
    RegisterSharedMessages();
    InstallShellHooks();
    Wh_Log(L"Speed test link hooks loaded (pid %u)", GetCurrentProcessId());
    return TRUE;
}

void WhToolLauncher_ModSettingsChanged(BOOL* reload) {
    if (IsCurrentExe(L"windhawk.exe")) {
        *reload = FALSE;
        return;
    }
    LoadSettings();
    *reload = FALSE;
}

// --- The mod's own process -----------------------------------------------

BOOL WhTool_ModInit() {
    LoadSettings();
    InterlockedExchange(&g_shutdown, 0);
    RegisterSharedMessages();
    if (!g_showMessage) {
        return FALSE;
    }
    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0,
                              &g_uiThreadId);
    if (!g_uiThread) {
        Wh_Log(L"UI thread creation failed (error %u)", GetLastError());
        return FALSE;
    }
    Wh_Log(L"Speed test flyout process started (pid %u)",
           GetCurrentProcessId());
    return TRUE;
}

void WhTool_ModUninit() {
    g_cancelRequested.store(1, std::memory_order_relaxed);
    InterlockedExchange(&g_shutdown, 1);

    if (g_flyoutHwnd && !PostMessageW(g_flyoutHwnd, WM_APP + 2, 0, 0)) {
        Wh_Log(L"Posting flyout shutdown message failed (error %u)",
               GetLastError());
    }

    if (g_uiThread && g_uiThreadId) {
        // The thread queue may not exist yet; retry until it is ready or the
        // startup path observes g_shutdown and exits.
        while (WaitForSingleObject(g_uiThread, 0) == WAIT_TIMEOUT) {
            if (PostThreadMessageW(g_uiThreadId, WM_QUIT, 0, 0)) {
                break;
            }
            Sleep(10);
        }
        // The process exits right after this; a bounded wait is enough to
        // take the tray icon down cleanly.
        if (WaitForSingleObject(g_uiThread, 10000) != WAIT_OBJECT_0) {
            Wh_Log(L"UI thread did not stop in 10 s");
        }
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
        g_uiThreadId = 0;
    }

    speedset::CloseSettingsWindow();

    if (g_testThread) {
        if (WaitForSingleObject(g_testThread, 10000) != WAIT_OBJECT_0) {
            Wh_Log(L"Test thread did not stop in 10 s");
        }
        CloseHandle(g_testThread);
        g_testThread = nullptr;
    }
}

void WhTool_ModSettingsChanged() {
    LoadSettings();
    speedset::ReloadSettingsWindow();
    if (g_flyoutHwnd) {
        PostMessageW(g_flyoutHwnd, kTrayToggleMessage,
                     g_trayEnabled.load(std::memory_order_relaxed) ? 1 : 0, 0);
    }
}

extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace speedset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkNetworkSpeedTestSettings";
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
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
        {K::Number, L"flyoutBorderWidth", L"Border width", L"Thickness of the speed test window border at 100% scaling.", L"3", {}, 1, 6, 2, L"Flyout border"},
        {K::Color, L"flyoutBorderRest", L"Resting color", L"Hex color for the resting color of the speed test window border.", L"#585B70", {}, 0, 100, 2, L"Flyout border"},
        {K::Color, L"flyoutBorderHoverStart", L"Hover start color", L"Hex color for the hover start color of the speed test window border.", L"#89B4FA", {}, 0, 100, 2, L"Flyout border"},
        {K::Color, L"flyoutBorderHoverEnd", L"Hover end color", L"Hex color for the hover end color of the speed test window border.", L"#CBA6F7", {}, 0, 100, 2, L"Flyout border"},
        {K::Check, L"flyoutAnimation", L"Open and close animation", L"The window fades and slides in when it opens and out when it closes. It also stays still when Windows animation effects are off.", L"1", {}, 0, 100, 2, L"Motion"},
        {K::Choice, L"animationSpeed", L"Animation speed", L"How quick the window's animations play. Follow the global speed uses the speed shared by all DavidHiFi mods.", L"global", {{L"global", L"Follow the global speed"}, {L"veryQuick", L"Very quick"}, {L"quick", L"Quick"}, {L"normal", L"Normal"}, {L"relaxed", L"Relaxed"}, {L"slow", L"Slow"}}, 0, 100, 2, L"Motion"},
        {K::Choice, L"networkDisplay", L"Network name", L"Choose how the flyout shows the network name.", L"always", {{L"always", L"Always show"}, {L"hover", L"Blurred until hover"}, {L"click", L"Blurred until click"}, {L"hidden", L"Hidden"}}, 0, 100, 1, L"Network details"},
        {K::Choice, L"serverDisplay", L"Test server", L"Choose how the flyout shows the test server.", L"always", {{L"always", L"Always show"}, {L"hover", L"Blurred until hover"}, {L"click", L"Blurred until click"}, {L"hidden", L"Hidden"}}, 0, 100, 1, L"Network details"},
        {K::Choice, L"ipDisplay", L"Public IP address", L"Choose how the flyout shows the public ip address.", L"hidden", {{L"always", L"Always show"}, {L"hover", L"Blurred until hover"}, {L"click", L"Blurred until click"}, {L"hidden", L"Hidden"}}, 0, 100, 1, L"Network details"},
        {K::Choice, L"countryDisplay", L"Country or region", L"Choose how the flyout shows the country or region.", L"hidden", {{L"always", L"Always show"}, {L"hover", L"Blurred until hover"}, {L"click", L"Blurred until click"}, {L"hidden", L"Hidden"}}, 0, 100, 1, L"Network details"},
        {K::Text, L"extraPatterns", L"Extra URL patterns", L"Additional substrings separated by | (example speedtest.net|ookla.com).", L"", {}, 0, 100, 0, L"Speed test"},
        {K::Check, L"fallbackToOriginal", L"Fall back to the web page", L"If the native flyout cannot start, open the original web page instead of doing nothing.", L"1", {}, 0, 100, 0, L"Speed test"},
        {K::Check, L"interceptProcessLaunch", L"Also intercept browser process launches", L"Catch direct browser launches from the network menu. The launch returns ERROR_CANCELLED because no browser process is created.", L"1", {}, 0, 100, 0, L"Speed test"},
        {K::Choice, L"autoStart", L"Start the test automatically", L"Starts the test when the flyout opens. Auto waits for a click on metered connections. Never requires a click every time.", L"auto", {{L"auto", L"Auto (waits on metered connections)"}, {L"always", L"Always"}, {L"never", L"Never (click to start)"}}, 0, 100, 0, L"Speed test"},
        {K::Choice, L"language", L"Language", L"Language of the flyout texts. Auto follows the Windows display language.", L"auto", {{L"auto", L"Automatic (Windows display language)"}, {L"it", L"Italiano"}, {L"en", L"English"}}, 0, 100, 0, L"Speed test"},
        {K::Choice, L"flyoutPosition", L"Where the window opens", L"Corner of the screen the speed test window opens in, on the screen under the mouse. Auto opens it next to the tray, at the taskbar's edge.", L"auto", {{L"auto", L"Auto (next to the tray)"}, {L"topRight", L"Top right"}, {L"topLeft", L"Top left"}, {L"bottomRight", L"Bottom right"}, {L"bottomLeft", L"Bottom left"}, {L"center", L"Center of the screen"}}, 0, 100, 0, L"Speed test"},
        {K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 3, L"Settings window"},
        {K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 3, L"Settings window"},
        {K::Check, L"settingsTrayIcon", L"Tray icon", L"Show the speed test tray icon. Right-click it for settings.", L"1", {}, 0, 100, 3, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
    {L"Speed test", L"Choose when and where the speed test opens.", 0xE9D9},
    {L"Network details", L"Choose which details appear and when they are readable.", 0xE968},
    {L"Appearance", L"Set the border and how the window opens and closes.", 0xE790},
    {L"Look", L"Choose how this settings window looks and whether its tray icon is shown.", 0xE790},
    {L"About", L"Version, credits and support.", 0xE946},
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
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/network-speedtest-native";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BNetwork%20Speed%20Test%20Plus%5D%20";
constexpr PCWSTR kSetTitle = L"Network Speed Test Plus";
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
            // The hover look of every card: a faint blue to mauve wash and a 1 px gradient ring.
            float rad = 8, ringW = 1;
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

// ---- Tray menu -------------------------------------------------------------



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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Speed test") <= railW) break;
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
    const bool stacked = ColorRowStacked(f, row.right - row.left);
    float r = row.right - kSetRowPad, mid = (row.top + row.bottom - (stacked ? kSgcChipLine : 0)) / 2,
          h = kSetBoxH / 2;
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
            float x = stacked ? row.left + kSetRowPad : p.box.left - 12 - (kSetChipCount * 26 - 6);
            float cy = stacked ? row.bottom - 24 : mid;
            for (int i = 0; i < kSetChipCount; i++) p.chip[i] = {x + i * 26, cy - 10, x + i * 26 + 20, cy + 10};
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
        float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
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
        add(SetItem::Link, 56, L"Network Speed Test Native", L"Original mod by Alessandro-Vecchio", kSetDittoUrl);
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
    p.Round(box, 8, kSetBoxFill);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.Edge(box, 8, mocha::overlay0, 0.7f * (1 - g), 1.25f);
    p.GradRing(box, 8, g, 1.75f);
}

static void Set_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) {
    const SetField& f = w.fields[it.field];
    int k = it.field;
    D2D1_RECT_F row = Set_RowRect(w, it);
    p.Round(row, 10, mocha::base);
    p.Round(row, 10, mocha::surface0, 0.32f);
    float hov = Set_GlowOf(w, 1000 + k);
    p.Edge(row, 10, mocha::surface2, 0.55f * (1 - hov));
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    if (w.kbd && w.focus == k) p.GradRing(row, 10, 1.0f, 2.0f);

    float textW = w.contentW - 2 * kSetRowPad - RowControlW(f, w.contentW) - 24;
    float lh = Set_TextH(w.fLabel.get(), f.label, textW);
    float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = row.top + (it.h - (ColorRowStacked(f, w.contentW) ? kSgcChipLine : 0) - lh - dh) / 2;
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
    p.Round(row, 10, mocha::base);
    p.Round(row, 10, mocha::surface0, 0.32f);
    p.Edge(row, 10, mocha::surface2, 0.55f * (1 - hov));
}

static void Set_DrawLinkRow(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), 0xE8A7, {row.right - 46, row.top, row.right - 12, row.bottom}, mocha::subtext1);
}

static void Set_DrawSupport(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float card = std::max(Set_GlowOf(w, 3700 + idx), Set_GlowOf(w, 3500 + idx));
    Set_DrawCard(p, row, card);
    p.GradFill(row, 10, 0.13f * card);
    p.GradRing(row, 10, card, 1.5f);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 14, row.right - 180, row.top + 36}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 38, row.right - 180, row.bottom - 6}, mocha::subtext0);
    D2D1_RECT_F b = Set_SupportButton(w, it);
    float hov = Set_GlowOf(w, 3500 + idx);
    p.GradFill(b, 8, 0.85f + 0.15f * hov);
    p.GradRing(b, 8, hov, 2);
    p.Text(w.fButton.get(), L"Open Ko-fi", b, mocha::crust);
}

static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3800 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    D2D1_RECT_F mark{row.left + 20, row.top + 20, row.left + 92, row.top + 92};
    p.GradFill(mark, 18, 1);
    p.Glyph(w.fIconL.get(), 0xE9D9, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Network Speed Test Plus", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Measure download, upload and latency from the taskbar.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Based on Network Speed Test Native by Alessandro-Vecchio.",
           {x, row.top + 112, row.right - 16, row.bottom - 8}, mocha::overlay2);
}

static void Set_DrawBanner(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    p.Round(r, 10, mocha::peach, 0.14f);
    p.Text(w.fHint.get(), it.text, {r.left + 16, r.top + 14, r.right - 16, r.bottom - 8}, mocha::peach);
}

// A floating dock: soft shadow, mantle fill, a quiet 1px edge at rest and the blue to mauve
// edge as the pointer comes over it.
static void Set_DrawDock(SetPaint& p, SetWindow& w, const D2D1_RECT_F& d, float rad, float fill, float glow) {
    p.Round({d.left, d.top + 3, d.right, d.bottom + 5}, rad + 2, mocha::crust, w.glass ? 0.28f : 0.5f);
    p.Round(d, rad, mocha::mantle, fill);  // Hover lights only the edge: a wash showed as a blue blob down the left.
    D2D1_RECT_F in{d.left + 0.5f, d.top + 0.5f, d.right - 0.5f, d.bottom - 0.5f};
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(in, rad, rad), p.B(mocha::surface1, 0.75f * (1 - glow)), 1);
    p.GradRing(d, rad, glow, 1.5f);
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
    Set_DrawDock(p, w, d, 14, w.glass ? 0.58f : 1.0f, std::max(w.railGlow * 0.85f, edge));
    if (edge > 0.003f) p.GradRing(d, 13, edge, 2.25f);

    D2D1_RECT_F tb = Set_RailToggleRect(w);
    float th = Set_GlowOf(w, 42);
    p.Round(tb, 9, mocha::surface0, 0.45f + 0.25f * th);
    p.GradFill(tb, 9, 0.16f * th);
    p.GradRing(tb, 9, 0.9f * th, 1.25f);
    if (w.kbd && w.focus == -20) p.GradRing(tb, 9, 1, 2);
    Set_DrawPanelIcon(p, tb, open, th > 0.5f ? mocha::text : mocha::subtext1);

    p.rt->PushAxisAlignedClip(D2D1::RectF(d.left, d.top, d.right - 6, d.bottom), D2D1_ANTIALIAS_MODE_ALIASED);
    if (textA > 0.003f) {
        float my = (tb.top + tb.bottom) / 2;
        Set_DrawMark(p, w.fIcon.get(), {d.left + 56, my - 13, d.left + 82, my + 13}, textA);
    }
    p.Text(w.fRailName.get(), L"Seamless", {d.left + 90, d.top + 9, d.left + w.railW - 10, d.top + 33}, mocha::text, textA);
    p.Text(w.fRailName.get(), L"Speed test", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
    for (int i = 0; i < kSetPageCount; i++) {
        D2D1_RECT_F r = Set_RailRect(w, i);
        if (i == kSetAboutPage) {
            float ly = std::round(r.top - (kSetAboutGap + kSetRailPitch - kSetRailItem) / 2);
            p.Fill({r.left + 6, ly, r.right - 6, ly + 1}, mocha::surface1, 0.7f);
        }
        float hov = Set_GlowOf(w, 100 + i);
        bool act = i == w.page;
        if (act) {
            p.GradFill(r, 8, 0.22f);
            p.GradRing(r, 8, 0.5f, 1);
            D2D1_RECT_F bar{r.left, r.top + 8, r.left + 3, r.bottom - 8};
            p.GradFill({bar.left, bar.top, bar.left + 3, bar.bottom}, 1.5f, 1);
        } else {
            p.Round(r, 8, mocha::surface0, 0.28f);
            p.Edge(r, 8, mocha::surface2, 0.5f * (1 - hov));
            p.GradFill(r, 8, 0.10f * hov);
            p.GradRing(r, 8, 0.8f * hov, 1.25f);
        }
        if (w.kbd && w.focus == -10 - i) p.GradRing(r, 8, 1, 2);
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
    const D2D1_RECT_F edge{d.left + 2, d.top + 2, d.right - 2, d.bottom - 2};
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(edge, rad - 2, rad - 2),
                              p.B(mocha::overlay0, 0.9f * (1 - w.footGlow)), 2.75f);
    p.GradRing(d, rad - 1.5f, w.footGlow, 3.0f);
    UINT32 sc;
    std::wstring status = Set_FooterStatus(w, &sc);
    float sw = Set_FooterStatusW(w);
    if (sw > 0) p.Text(w.fStatusLine.get(), status, {d.left + 18, d.top, d.left + 18 + sw, d.bottom}, sc);
    static const PCWSTR names[3] = {L"Reset to suggested", L"Cancel", L"Save"};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_FooterButton(w, i);
        float hov = Set_GlowOf(w, 10 + i);
        p.Round(b, brad, mocha::base, 0.98f);
        p.Edge(b, brad, mocha::overlay0, 0.78f * (1 - hov), 1.75f);
        p.GradRing(b, brad - 1, hov, 2.25f);
        p.Text(w.fButton.get(), names[i], b, mocha::text, w.saving ? 0.5f : 1.0f);
        if (w.kbd && w.focus == -1 - i) p.GradRing(b, brad, 1, 2);
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
    p.Round(shadow, 12, mocha::crust, 0.6f);
    p.Round(r, 10, mocha::mantle);
    p.GradRing(r, 10, 0.9f);
    const float right = r.right - (scrolls ? 12 : 4);
    for (int v = 0; v < vis; v++) {
        int i = w.dropTop + v;
        if (i >= n) break;
        D2D1_RECT_F it{r.left + 4, r.top + 4 + v * kSetDropItem, right, r.top + 4 + (v + 1) * kSetDropItem};
        bool sel = f.cur == f.options[i].first;
        if (i == w.dropHover) {
            p.GradFill(it, 6, 0.28f);
            p.GradRing(it, 6, 0.6f, 1);
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
    float s = r.right - r.left;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (SUCCEEDED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) &&
        SUCCEEDED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, r.top), D2D1::Point2F(r.right, r.bottom)),
            coll.get(), g.put())))
        p.rt->FillRoundedRectangle(D2D1::RoundedRect(r, s * 0.24f, s * 0.24f), g.get());
    p.Glyph(glyph, 0xE9D9, r, mocha::crust);
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
    if (!first && native == w.nativeTitle && glass == w.glass) return;
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
            SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};  // same as the launcher grid
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Network Speed Test Plus settings", style,
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

void ReloadSettingsWindow() {
    if (HWND hwnd = g_settingsWnd) PostMessageW(hwnd, WM_APP_SETTINGS_RELOAD, 0, 0);
}

void ShowMenu(HWND owner) {
    POINT point{};
    if (!GetCursorPos(&point)) return;
    const std::vector<SetMenuItem> items = {
        Set_MenuRow(1, L"⚙", L"Settings"),
    };
    if (Set_TrayMenu(owner, items, &point) == 1) OpenSettingsWindow();
}
}  // namespace speedset

#include <windhawk_tool_mod.h>
