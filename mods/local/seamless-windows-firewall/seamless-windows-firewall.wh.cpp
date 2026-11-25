// ==WindhawkMod==
// @id              seamless-windows-firewall
// @name            Seamless Windows Firewall
// @description     Block or allow any app's internet in one click, from the tray icon or a shortcut
// @version         1.2.5
// @author          DavidHiFi, Ashix
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @include         windhawk-mod.exe
// @include         windhawk-mod-elevated.exe
// @architecture    x86-64
// @compilerOptions -DWIN32_LEAN_AND_MEAN -lfwpuclnt -lrpcrt4 -lole32 -loleaut32 -luuid -lshell32 -lgdi32 -lgdiplus -ld2d1 -ldwrite -ldwmapi -luser32 -lcomctl32 -liphlpapi -ladvapi32 -lshlwapi -lwindowscodecs -luxtheme -lcomdlg32 -limm32 -lversion
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Windows Firewall

Cut any app off the internet with one click, and give it back just as fast. It
works next to Windows Firewall and leaves your own firewall rules alone.

![Seamless Windows Firewall preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-windows-firewall.png)

## Features
- **One click per app.** The panel lists your running apps. Click one to block
  it, click again to allow it.
- **Three ways to block.** Fully offline, out only (the app can't reach the
  internet) or in only (nothing can connect to the app).
- **Nothing sticks by accident.** Blocks last until you allow the app again,
  turn the mod off or restart Windows. If the mod ever crashes, every app gets
  its internet back.
- **Always blocked list.** Apps you add in the settings are blocked each time
  the mod starts.
- **Cycle Mode.** Double-click an app to switch it between blocked and allowed
  on a timer: for a set number of rounds, for a set time, or until you stop it.
  The panel shows the timer while it runs.
- **Tray icon.** Click it to open the panel in the middle of the screen.
  Right-click for the settings and for allowing every blocked app at once.
- **Safe by default.** Core Windows parts, Windhawk itself and your antivirus
  can never be blocked. You get a warning box before blocking a remote desktop
  or VPN app while one is in use.
- **Its own connection box.** When an app wants other devices to connect to
  it, such as a game hosting a match, the mod asks in its own frosted box
  instead of the Windows Firewall pop-up. Windows Firewall keeps guarding, and
  your answer is saved as a normal firewall rule.
- **Right-click menu for apps.** Right-click any program file for Block in
  Windows Firewall, Allow again and Open the firewall panel. A block made there
  is a normal firewall rule and stays after a restart. Turn the menu off under
  Blocking, Right-click menu.

## Default shortcuts

| Shortcut | What it does |
|---|---|
| Ctrl+Alt+F | Block or allow the app in front |
| Ctrl+Alt+Shift+F | Open or close the panel |
| (none) | Allow every blocked app again |

Change or clear any of them in the settings.

## Notes
- Blocking needs administrator rights, so the mod runs in Windhawk's
  administrator helper.
- The Blocked list has a second view, Blocked by Windows Firewall, that shows
  the apps your own firewall rules block. Change those in Windows Defender
  Firewall.

## What's new in 1.2.5
- Right-click any program file to block it in Windows Firewall, allow it again
  or open the panel. It does the same job as Firewall App Blocker's menu, so
  you no longer need that app. Turn the menu off under Blocking, Right-click
  menu; nothing of it is left while the mod is off.
- The panel and the connection box now fade and slide in when they open and out
  when they close. Turn it off, or pick a speed, under Look, Motion. They stay
  still when Windows animation effects are off.
- The connection box is real frosted glass now. Before, it looked flat.
- The tray and settings icon is the shield alone in the blue to mauve
  gradient, with no plate behind it.

## What's new in 1.2.2
- No more edge pill and no more opening on hover. The mod lives in the tray:
  click the icon, or press Ctrl+Alt+Shift+F, and the panel opens in the middle
  of that screen. Click anywhere else to close it.

## What's new in 1.2.1
- The connection box now shows straight away on a busy PC. Before, it could stay
  invisible, and the panel could stall while opening.

## What's new in 1.2.0
- The Windows Firewall pop-up ("allow this app?") is replaced by the mod's own
  frosted box, in the middle of the screen. Allow or Block saves a normal
  Windows Firewall rule for that app, the same as the Windows pop-up did.
- The box never takes the keyboard from the app you are using, and it waits
  while a game runs full screen. Until you answer, Windows keeps the app
  blocked, the same as before.
- Turn it off under Blocking, Connection requests. Windows' own pop-up comes
  back as soon as it is off or the mod stops.

## 1.1.1
- The warning box is a little clearer glass, so the panel's colours show
  softly through it, the same frosted look as the rest of the mod.

## 1.1.0
- The warnings before blocking a VPN or remote app, and before stopping a
  timer, now open in the same frosted Mocha box as the panel instead of the
  plain Windows message box. On a risky question the safe button is picked
  first, so Enter keeps things as they are. Y says yes, Esc or N says no,
  Tab moves between the buttons.
- First release (1.0.0): a port of !Net with the Mocha look, the shared
  settings window, a tray icon, an edge pill and Ctrl+Alt+F shortcuts.

## Credits
Based on [!Net](https://windhawk.net/mods/not-net) by Ashix.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- defaultDirection: "fully_offline"
  $name: "What a block stops"
  $description: "Fully offline stops traffic both ways. The other two stop only one way. You can change it per app in the panel."
  $options:
  - fully_offline: "Fully offline (in and out)"
  - cant_reach_internet: "Can't reach the internet (out only)"
  - cant_be_reached: "Can't be reached (in only)"
- includeChildProcesses: true
  $name: "Block helper programs too"
  $description: "Also blocks the other programs in the app's own folder, such as its updater or web helper."
- lockSystemProcesses: true
  $name: "Keep Windows helpers safe"
  $description: "Windows itself, Windhawk and your antivirus are always safe from a block. On, Windows' smaller helpers are locked too."
- warnOnVpnOrRemote: true
  $name: "Warn before blocking a VPN or remote desktop"
  $description: "Blocking one of these can cut off the connection you are using right now."
- replaceFirewallPrompt: true
  $name: "Ask with our own box"
  $description: "When an app wants other devices to connect to it, such as a game hosting a match, this box asks instead of the Windows Firewall pop-up. Windows Firewall keeps guarding, and your answer is saved as a normal firewall rule."
- allowOnPublicNetworks: false
  $name: "Allow on public networks too"
  $description: "Off, Allow lets the app in on home and work networks only. On a public network you are using right now, Allow always covers it."
- contextMenu: true
  $name: "Right-click menu for apps"
  $description: "Adds Seamless Windows Firewall to the right-click menu of every program file, with Block, Allow again and Open the panel. A block made there stays after a restart, like a normal firewall rule."
- windowSizePreset: "default"
  $name: "Panel size"
  $options:
  - default: "Normal (436 by 480)"
  - large: "Large (680 by 680)"
  - extralarge: "Extra large (840 by 840)"
- defaultFilter: "user"
  $name: "List shown first"
  $description: "The tab the panel opens on."
  $options:
  - user: "Running apps"
  - allowed: "Allowed"
  - blocked: "Blocked"
  - system: "System apps"
  - excluded: "Hidden apps"
- showNonActionableInRunning: false
  $name: "Show locked apps in Running"
  $description: "Also list Windows helpers and apps that Windows Firewall already blocks, even though you cannot change them here."
- showTooltips: false
  $name: "Tooltips"
  $description: "Show a short tip when the pointer rests on a button, a switch or the clock."
- hideDuringCapture: true
  $name: "Hide from screenshots and recordings"
  $description: "The panel stays out of screen captures, streams and screen sharing."
- enableCycleScheduler: true
  $name: "Cycle Mode"
  $description: "Block and allow an app on a timer. Double-click or right-click an app in the panel to set it up."
- rememberCycleTemplates: true
  $name: "Remember each app's timer"
  $description: "The last timer you used for an app fills in next time. It never starts by itself."
- showCycleMs: false
  $name: "Milliseconds box"
  $description: "Show a box for milliseconds in the timer window."
- toggleForegroundApp: "Ctrl+Alt+F"
  $name: "Block or allow the app in front"
  $description: "Press the keys in the box. Backspace clears it."
- expandCollapsePill: "Ctrl+Alt+Shift+F"
  $name: "Open or close the panel"
- restoreAll: ""
  $name: "Allow every blocked app again"
  $description: "Off by default. Pick keys that no other app uses."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it to open the panel. Right-click it for settings and more. When off, use the shortcut."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- flyoutAnimation: true
  $name: "Open and close animation"
  $description: "The panel and the connection box fade and slide in when they open and out when they close. They stay still when Windows animation effects are off."
- animationSpeed: "global"
  $name: "Animation speed"
  $description: "How quick the animations play. Follow the global speed uses the speed shared by all DavidHiFi mods."
  $options:
  - global: "Follow the global speed"
  - veryQuick: "Very quick"
  - quick: "Quick"
  - normal: "Normal"
  - relaxed: "Relaxed"
  - slow: "Slow"
- autoBlockedApps:
  - - appPath: ""
      $name: "Program path"
      $description: "The full path of the program, such as C:\\Games\\game.exe."
    - direction: fully_offline
      $name: "What the block stops"
      $options:
      - fully_offline: "Fully offline (in and out)"
      - cant_reach_internet: "Can't reach the internet (out only)"
      - cant_be_reached: "Can't be reached (in only)"
    - includeChildProcesses: true
      $name: "Block helper programs too"
  $name: "Always blocked apps"
  $description: "Blocked every time the mod starts. Edit this list here on Windhawk's page."
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <shellapi.h>
#include <shlobj.h>
#include <tlhelp32.h>
#include <iphlpapi.h>
#include <rpc.h>
#include <fwpmu.h>
#include <netfw.h>
#include <oleauto.h>
#include <gdiplus.h>
#include <d2d1.h>
#include <dwrite.h>
#include <shlwapi.h>
#include <uxtheme.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <imm.h>

// Official Microsoft SDK WFP GUIDs (omitted in MinGW-w64 fwpmu.h)
static const GUID kWfpCondAleAppId = {
    0xd78e1e87, 0x8644, 0x4ea5, { 0x94, 0x37, 0xd8, 0x09, 0xec, 0xef, 0xc9, 0x71 }
};
static const GUID kWfpSublayerUniversal = {
    0xeebecc03, 0xced4, 0x4380, { 0x81, 0x9a, 0x27, 0x34, 0x39, 0x7b, 0x2b, 0x74 }
};
static const GUID kWfpLayerAleAuthConnectV4 = {
    0xc38d57d1, 0x05a7, 0x4c33, { 0x90, 0x4f, 0x7f, 0xbc, 0xee, 0xe6, 0x0e, 0x82 }
};
static const GUID kWfpLayerAleAuthConnectV6 = {
    0x4a72393b, 0x319f, 0x44bc, { 0x84, 0xc3, 0xba, 0x54, 0xdc, 0xb3, 0xb6, 0xb4 }
};
static const GUID kWfpLayerAleAuthRecvAcceptV4 = {
    0xe1cd9fe7, 0xf4b5, 0x4273, { 0x96, 0xc0, 0x59, 0x2e, 0x48, 0x7b, 0x86, 0x50 }
};
static const GUID kWfpLayerAleAuthRecvAcceptV6 = {
    0xa3b42c97, 0x9f04, 0x4672, { 0xb8, 0x7e, 0xce, 0xe9, 0xc4, 0x83, 0x25, 0x7f }
};

#ifndef FWPM_SESSION_DYNAMIC
#define FWPM_SESSION_DYNAMIC 0x00000001
#endif
#ifndef NET_FW_IP_PROTOCOL_ANY
#define NET_FW_IP_PROTOCOL_ANY 256
#endif

#include <algorithm>
#include <atomic>
#include <cmath>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cwctype>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <cwchar>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include <windhawk_tool_mod.h>

// The settings window, tray menu and glass come from the shared settings engine (swfset,
// at the end of this file).
namespace swfset {
void OpenSettingsWindow();
void CloseSettingsWindow();
struct TrayRow {
    int id = 0;
    std::wstring glyph, label, hint;
    bool checked = false, disabled = false, separator = false;
    std::vector<TrayRow> sub;
};
int ShowTrayMenu(HWND owner, const POINT* at, const std::vector<TrayRow>& rows);
extern std::atomic<HWND> g_settingsWnd;
}  // namespace swfset
std::wstring Hotkey_Format(UINT mods, UINT vk);

#ifndef DWMWA_WINDOW_CORNER_PREFERENCE
#define DWMWA_WINDOW_CORNER_PREFERENCE 33
#endif
#ifndef DWMWCP_DONOTROUND
#define DWMWCP_DONOTROUND 1
#endif
#ifndef DWMWCP_ROUND
#define DWMWCP_ROUND 2
#endif
#ifndef DWMWCP_ROUNDSMALL
#define DWMWCP_ROUNDSMALL 3
#endif
#ifndef WDA_NONE
#define WDA_NONE 0x00000000
#endif
#ifndef WDA_EXCLUDEFROMCAPTURE
#define WDA_EXCLUDEFROMCAPTURE 0x00000011
#endif

// ============================================================================
// Constants & Enums
// ============================================================================

constexpr wchar_t kWndClass[]       = L"SeamlessFirewall_FloatingWnd_v1";
constexpr wchar_t kCtrlWndClass[]   = L"SeamlessFirewall_ControlWnd_v1";
constexpr wchar_t kCyclePopupClass[] = L"SeamlessFirewall_CyclePopup_v1";
constexpr wchar_t kRulePrefix[]     = L"SeamlessFirewall_";
constexpr wchar_t kTrayTip[]        = L"Seamless Windows Firewall";

constexpr UINT WM_APP_RELOAD_SETTINGS = WM_APP + 101;
constexpr UINT WM_APP_TRAY_CALLBACK   = WM_APP + 102;
constexpr UINT WM_APP_REFRESH_APPS    = WM_APP + 103;
constexpr UINT WM_APP_FOREGROUND_CHG  = WM_APP + 104;
constexpr UINT WM_APP_CYCLE_STATE     = WM_APP + 105;
constexpr UINT WM_APP_CYCLE_APPLY     = WM_APP + 106;

constexpr UINT_PTR TIMER_COLLAPSE     = 1;
constexpr UINT_PTR TIMER_ANIM_VSYNC   = 2;
constexpr UINT_PTR TIMER_FULLSCREEN   = 3;
constexpr UINT_PTR TIMER_HOVER_SENSOR    = 4;
constexpr UINT_PTR TIMER_CYCLE_UI        = 5;
constexpr UINT_PTR TIMER_DEBOUNCE_REFRESH = 6;
constexpr UINT_PTR TIMER_WIDGET_PROXIMITY = 86;
constexpr UINT_PTR TIMER_OUTSIDE_CLICK    = 87;
constexpr UINT_PTR TIMER_LATE_CHILD_POLL  = 88;
constexpr UINT_PTR TIMER_EVENT_FLUSH      = 91;
constexpr UINT_PTR TIMER_WARM_PANEL       = 92;

// Windows open and close all the time on a busy PC (consoles, tooltips, menus). One posted
// message per event kept this thread's queue full, and Windows only hands out timer ticks
// when the queue is empty, so the panel animation and the connection box's fade-in never
// ran. The hook now only marks what changed and one short timer handles it. The hook runs
// on this thread, so plain flags are enough.
static bool g_evFgDirty = false, g_evAppsDirty = false, g_evFlushArmed = false;

constexpr int HK_TOGGLE_FG   = 1;
constexpr int HK_EXPAND_PILL = 2;
constexpr int HK_RESTORE_ALL = 3;

enum class Direction {
    FullyOffline = 0,
    CantReachInternet = 1,
    CantBeReached = 2
};

enum class DockEdge { Right = 0, Left = 1, Top = 2, Bottom = 3, TopLeft = 4, BottomLeft = 5, BottomRight = 6 };
static bool IsCornerDock(DockEdge e) {
    return e == DockEdge::TopLeft || e == DockEdge::BottomLeft || e == DockEdge::BottomRight;
}
enum class PillIndicatorMode { Always = 0, Pulse = 1 };
enum class AppFilter { Allowed = 0, Blocked, UserApps, SystemApps, Excluded };
enum class FullscreenBehavior { Hide = 0, Allow = 1 };
enum class SizePreset { Default = 0, Large, ExtraLarge };
enum class UiState { Line = 0, Panel };
enum class PulseKind { None = 0, AllowedGreen, BlockedRed };
enum class CycleWidgetAction { SchedulerOnly = 0, NavigatePill = 1 };

// ============================================================================
// Settings & Data Models
// ============================================================================

struct AutoBlockRuleCfg {
    std::wstring appPath;
    Direction direction = Direction::FullyOffline;
    bool includeChildProcesses = true;
};

struct HotkeyBinding {
    UINT modifiers = 0;
    UINT vk = 0;
    std::wstring raw;
};

struct ModSettings {
    Direction defaultDirection = Direction::FullyOffline;
    bool includeChildProcesses = true;

    bool showPill = true;
    bool trayIcon = true;
    DockEdge dockEdge = DockEdge::Right;
    PillIndicatorMode pillIndicatorMode = PillIndicatorMode::Always;
    bool hoverExpand = true;
    bool expandHoverHitArea = false;
    int hoverHitMarginPx = 12;
    int panelEdgeOffsetPx = 8;
    AppFilter defaultFilter = AppFilter::UserApps;
    bool showNonActionableInRunning = false;
    bool showTooltips = false;
    bool followCursorMonitor = true;
    bool rememberWindowPosition = true;
    SizePreset windowSizePreset = SizePreset::Default;
    bool flyoutAnimation = true;
    int animationSpeed = 0;  // 0 follows the global speed, 1 very quick to 5 slow

    FullscreenBehavior fullscreenBehavior = FullscreenBehavior::Hide;
    bool hideDuringCapture = true;
    bool enableCycleScheduler = true;
    bool rememberCycleTemplates = true;
    bool showCycleMs = false;
    bool showCycleWidget = true;
    int cycleWidgetSize = 5;
    CycleWidgetAction cycleWidgetAction = CycleWidgetAction::SchedulerOnly;

    bool lockSystemProcesses = true;
    bool warnOnVpnOrRemote = true;
    bool replaceFirewallPrompt = true;
    bool allowOnPublicNetworks = false;
    bool contextMenu = true;

    HotkeyBinding hkToggleFg;
    HotkeyBinding hkExpandPill;
    HotkeyBinding hkRestoreAll;

    std::vector<AutoBlockRuleCfg> autoBlockedApps;
};

struct WfpFilterEntry {
    UINT64 filterId = 0;
    std::wstring exePath;
};

struct BlockState {
    bool blocked = false;
    bool includeChildProcesses = true;
    Direction direction = Direction::FullyOffline;
    std::vector<WfpFilterEntry> sessionFilters;
    std::vector<std::wstring> blockedChildren;
    std::unordered_set<std::wstring> blockedChildPaths;
    std::unordered_set<std::wstring> allowedChildPaths;
};

struct AppEntry {
    std::wstring exePath;
    std::wstring displayPath;
    std::wstring name;
    DWORD primaryPid = 0;
    std::vector<DWORD> pids;
    bool isForeground = false;
    bool hasVisibleWindow = false;
    bool hasLiveNetwork = false;
    bool isSystemApp = false;
    bool isImmutableLocked = false;
    bool isCriticalLocked = false;
    bool isOtherSessionOrUser = false;
    bool isVpnOrRemote = false;
    bool isExcluded = false;
    bool exeExists = true;
    bool isExternalBlocked = false;
    int externalBlockMask = 0;
    std::wstring externalRuleName;
    BlockState block;
};

struct MotionClock {
    LARGE_INTEGER freq{};
    LARGE_INTEGER start{};
    double durationMs = 240.0;
    double fromVal = 0.0;
    double toVal = 0.0;
    double currentVal = 0.0;
    bool active = false;
    int ease = 0;  // 0 in and out, 1 out (opening), 2 in (closing)

    void Init() { QueryPerformanceFrequency(&freq); }

    void Start(double target, double durMs, int easeMode = 0) {
        if (freq.QuadPart == 0) Init();
        ease = easeMode;
        QueryPerformanceCounter(&start);
        fromVal = currentVal;
        toVal = target;
        durationMs = std::max(1.0, durMs);
        active = (std::abs(toVal - fromVal) > 0.0005);
        if (!active) currentVal = toVal;
    }

    static double EaseInOutCubic(double t) {
        t = std::clamp(t, 0.0, 1.0);
        return (t < 0.5) ? (4.0 * t * t * t) : (1.0 - std::pow(-2.0 * t + 2.0, 3.0) / 2.0);
    }

    bool Step() {
        if (!active) return false;
        LARGE_INTEGER now{};
        QueryPerformanceCounter(&now);
        double elapsedMs = (double)(now.QuadPart - start.QuadPart) * 1000.0 / (double)freq.QuadPart;
        double t = elapsedMs / durationMs;
        if (t >= 1.0) {
            currentVal = toVal;
            active = false;
            return false;
        }
        double e = ease == 1 ? 1.0 - std::pow(1.0 - t, 3.0) : ease == 2 ? t * t * t : EaseInOutCubic(t);
        currentVal = fromVal + (toVal - fromVal) * e;
        return true;
    }
};

struct PulseState {
    PulseKind kind = PulseKind::None;
    LARGE_INTEGER freq{};
    LARGE_INTEGER start{};
    double durationMs = 1500.0;
    double intensity = 0.0;
    bool active = false;

    void Trigger(PulseKind k, double durMs = 1500.0) {
        if (freq.QuadPart == 0) QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
        kind = k;
        durationMs = durMs;
        intensity = 1.0;
        active = (k != PulseKind::None);
    }

    bool Step() {
        if (!active) return false;
        LARGE_INTEGER now{};
        QueryPerformanceCounter(&now);
        double elapsedMs = (double)(now.QuadPart - start.QuadPart) * 1000.0 / (double)freq.QuadPart;
        if (elapsedMs >= durationMs) {
            intensity = 0.0;
            active = false;
            kind = PulseKind::None;
            return false;
        }
        double t = elapsedMs / durationMs;
        double env = (t < 0.15) ? std::sin((t / 0.15) * 1.5707963)
                                : (0.5 * (1.0 + std::cos(((t - 0.15) / 0.85) * 3.14159265)));
        intensity = std::clamp(env, 0.0, 1.0);
        return true;
    }
};

struct DragController {
    bool dragging = false;
    POINT cursorAnchor{};
    RECT startRect{};
    int axisMode = 0;
};

// ============================================================================
// Global State
// ============================================================================

static std::mutex g_settingsMtx;
static ModSettings g_settings;
static int g_lastSettingDockEdge = -1;
static int g_posX = 0;
static int g_posY = 0;
static bool g_posLoaded = false;
// 1.2.2: there is no edge pill. The panel opens in the middle of the screen the pointer is on
// (the tray icon's screen after a tray click) and hides again when it closes.
static HMONITOR g_panelMon = nullptr;
static bool g_panelMoved = false;
static POINT g_panelMovedPos{};
static bool g_panelWasOpen = false;
static DWORD g_panelClosedTick = 0;

static std::mutex g_engineMtx;
static HANDLE g_wfpEngine = nullptr;
static GUID g_sublayerGuid{};
static bool g_hasCustomSublayer = false;
static std::unordered_map<std::wstring, BlockState> g_blocks;
static std::unordered_map<std::wstring, Direction> g_pendingDirs; // remembers direction choice before blocking
static std::unordered_set<std::wstring> g_excludedExes;

static HANDLE g_uiThread = nullptr;
static DWORD g_uiThreadId = 0;
static HANDLE g_uiReadyEvent = nullptr;

static HWND g_hWnd = nullptr;
static HWND g_hCtrlWnd = nullptr;
static HWND g_hTooltip = nullptr;
static NOTIFYICONDATAW g_nid{};
static bool g_trayAdded = false;
static UINT g_wmTaskbarCreated = 0;

static HWINEVENTHOOK g_hookFg = nullptr;
static HWINEVENTHOOK g_hookCreate = nullptr;

static ULONG_PTR g_gdiplusToken = 0;
static std::unordered_map<std::wstring, HICON> g_iconCache;

static UiState g_uiState = UiState::Line;
static bool g_pinned = false;
static bool g_mouseInside = false;
static bool g_hiddenByFullscreen = false;
static bool g_lastRoundedFrame = false;
static bool g_glassApplied = false;
static bool g_panelGlassOn = false;
// Open and close motion: while it plays the panel is a layered solid frame with the glass
// off, moved and faded each step from a kept copy (nothing redrawn).
static bool g_panelFading = false;
static bool g_panelClosing = false;  // the close is playing; clicks and keys do nothing
static HDC g_fadeDC = nullptr;
static HBITMAP g_fadeBmp = nullptr;
static HGDIOBJ g_fadeOld = nullptr;
static SIZE g_fadeSz{};
static MotionClock g_expandClock;
static MotionClock g_scrollClock;
static PulseState g_pillPulse;
static DragController g_drag;

static AppFilter g_activeFilter = AppFilter::UserApps;
static bool g_userRunningOnly = true;
static bool g_blockedFirewallOnly = false;
static bool g_userPinnedFilter = false;
static int g_maxScrollPx = 0;
static int g_hoverHitId = -1;
static int g_pressedHitId = -1;
static int g_kbSelectedIdx = -1;
static int g_lastListH = 300;
static int g_lastRowStride = 54;

static std::vector<AppEntry> g_appList;
static std::wstring g_lastFgExe;
static bool g_lastFgIsOtherSessionOrUser = false;
static std::mutex g_otherSessionCacheMtx;
static std::unordered_set<std::wstring> g_cachedOtherSessionOnlyExes;
static bool g_otherSessionCacheInitialized = false;
static std::wstring g_statusBanner;
static bool g_needsElevation = false;

struct HitRect {
    RECT rc{};
    int id = 0;
    int rowIndex = -1;
    std::wstring tooltip;
    enum Kind {
        None = 0, PinBtn, RestoreAllBtn, SettingsBtn, ElevateBtn,
        FilterChip, RowToggle, RowDirection, RowExclude, RowExternalLocked, RowBody, HeaderDrag
    } kind = None;
};
static std::vector<HitRect> g_hitRects;


// ============================================================================
// Forward Declarations
// ============================================================================

static void LoadSettings();
static void SaveExcludedApps();
static void LoadExcludedApps();
static void LogAudit(const std::wstring& msg);
static std::wstring ToLower(std::wstring s);
static std::wstring GetFileNameOnly(const std::wstring& path);
static Direction ParseDirection(PCWSTR s);
static const wchar_t* DirectionLabel(Direction d);
static const wchar_t* DirectionShortLabel(Direction d);
static void RefreshAppList();
static bool ApplyBlock(std::wstring exePath, Direction dir, bool includeChildren, bool askUser = true);
static bool ApplyAllow(std::wstring exePath);
static void RestoreAllSessionBlocks();
static void UpdateWindowGeometry(bool immediate);
constexpr UINT WM_APP_OUTSIDE_CLICK = WM_APP + 109;
static HHOOK g_outsideMouseHook = nullptr;
// While the panel is open, every mouse press anywhere is passed to the panel's window, which
// closes the panel when the press is outside it. A polled button state missed short clicks.
static LRESULT CALLBACK OutsideMouseProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION && g_hWnd &&
        (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN || wParam == WM_MBUTTONDOWN))
        PostMessageW(g_hWnd, WM_APP_OUTSIDE_CLICK, 0, 0);
    return CallNextHookEx(nullptr, code, wParam, lParam);
}
static void SyncOutsideMouseHook(bool want) {
    if (want && !g_outsideMouseHook && g_hWnd &&
        GetWindowThreadProcessId(g_hWnd, nullptr) == GetCurrentThreadId()) {
        HMODULE mod = nullptr;
        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           reinterpret_cast<LPCWSTR>(&OutsideMouseProc), &mod);
        g_outsideMouseHook = SetWindowsHookExW(WH_MOUSE_LL, OutsideMouseProc, mod, 0);
    } else if (!want && g_outsideMouseHook) {
        UnhookWindowsHookEx(g_outsideMouseHook);
        g_outsideMouseHook = nullptr;
    }
}
static void RequestRepaint(const RECT* dirty = nullptr);
static void OpenWindhawkSettingsUI();
static void TriggerForegroundPulse(const std::wstring& fgExe);

// ============================================================================
// Cycle Mode Data Models & Forward Declarations
// ============================================================================

enum class CycleRunMode { UntilStopped = 0, ForCycles, ForDuration };
enum class CyclePhase { Blocked = 0, Allowed };

struct CycleConfig {
    uint64_t blockMs = 10000;
    uint64_t allowMs = 5000;
    CycleRunMode runMode = CycleRunMode::UntilStopped;
    uint64_t runValue = 0; // cycle count for ForCycles, or total ms for ForDuration
    bool focusedOnly = true;
    bool allowWhenUnfocused = true;
    uint64_t targetEndUtcMs = 0; // >0 when synced with Windows clock
    Direction direction = Direction::FullyOffline;
};

struct CycleStatusSnapshot {
    bool active = false;
    std::wstring exePath;
    std::wstring displayPath;
    Direction direction = Direction::FullyOffline;
    CyclePhase phase = CyclePhase::Blocked;
    uint64_t phaseRemainingMs = 0;
    bool pausedByFocus = false;
    bool pausedByUser = false;
    uint64_t completedCycles = 0;
    uint64_t targetCycles = 0;
    CycleRunMode runMode = CycleRunMode::UntilStopped;
    uint64_t totalRemainingMs = 0;
    bool focusedOnly = true;
    bool allowWhenUnfocused = true;
    uint64_t blockMs = 10000;
    uint64_t allowMs = 5000;
};

static bool StartCycleForApp(std::wstring exePath, const CycleConfig& cfg, std::wstring& outErr);
static bool StopCycleForApp(const std::wstring& exePath, bool setAllowed);
static void StopAllCycles(bool setAllowed);
static bool GetCycleSnapshot(const std::wstring& exePath, CycleStatusSnapshot& outSnap);
static bool HasAnyActiveCycle();
static bool ToggleCyclePauseForApp(const std::wstring& exePath, bool& outNowPaused);
static bool GetWidgetCycleTarget(CycleStatusSnapshot& outSnap);
static void NotifyCycleFocusChanged(const std::wstring& fgExeLower);
static void NotifyCycleSystemResume();
static HWND g_hCyclePopup = nullptr;
static HWND g_hCycleWidget = nullptr;
// The Mocha yes/no box (replaces the stock Windows message box). question = blue "?" icon.
static HWND g_hConfirm = nullptr;
static bool FwConfirm(const wchar_t* title, const wchar_t* body, const wchar_t* yes, const wchar_t* no,
                      bool danger, bool question);
static void OpenCyclePopupForApp(const AppEntry& app);
static void SyncCycleWidgetWindow(bool reposition);
static void DestroyCycleWidgetWindow();


// ============================================================================
// Utility & Elevation Helpers
// ============================================================================

static std::wstring ToLower(std::wstring s) {
    for (auto& ch : s) ch = (wchar_t)towlower(ch);
    return s;
}

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return L"";
    size_t b = s.find_last_not_of(L" \t\r\n");
    return s.substr(a, b - a + 1);
}

static std::wstring GetFileNameOnly(const std::wstring& path) {
    size_t pos = path.find_last_of(L"\\/");
    return (pos == std::wstring::npos) ? path : path.substr(pos + 1);
}

static bool FileExistsW(const std::wstring& path) {
    if (path.empty()) return false;
    PVOID oldRedir = nullptr;
    BOOL redirDisabled = Wow64DisableWow64FsRedirection(&oldRedir);
    DWORD attr = GetFileAttributesW(path.c_str());
    if (redirDisabled) Wow64RevertWow64FsRedirection(oldRedir);
    return (attr != INVALID_FILE_ATTRIBUTES) && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

static bool IsProcessElevated() {
    HANDLE hToken = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) return false;
    TOKEN_ELEVATION elev{};
    DWORD retLen = 0;
    bool isElev = GetTokenInformation(hToken, TokenElevation, &elev, sizeof(elev), &retLen) && elev.TokenIsElevated != 0;
    CloseHandle(hToken);
    return isElev;
}

static void LoadExcludedApps() {
    g_excludedExes.clear();
    int count = Wh_GetIntValue(L"excludedCount", 0);
    for (int i = 0; i < count; ++i) {
        std::wstring key = L"excluded_" + std::to_wstring(i);
        wchar_t buf[1024]{};
        if (Wh_GetStringValue(key.c_str(), buf, ARRAYSIZE(buf)) > 0) {
            std::wstring item = ToLower(Trim(buf));
            if (!item.empty()) g_excludedExes.insert(item);
        }
    }
}

static void SaveExcludedApps() {
    int prevCount = Wh_GetIntValue(L"excludedCount", 0);
    int newCount = (int)g_excludedExes.size();
    Wh_SetIntValue(L"excludedCount", newCount);
    int idx = 0;
    for (const auto& ex : g_excludedExes) {
        std::wstring key = L"excluded_" + std::to_wstring(idx++);
        Wh_SetStringValue(key.c_str(), ex.c_str());
    }
    for (int i = newCount; i < prevCount; ++i) {
        std::wstring key = L"excluded_" + std::to_wstring(i);
        Wh_DeleteValue(key.c_str());
    }
}

static Direction ParseDirection(PCWSTR s) {
    if (!s) return Direction::FullyOffline;
    std::wstring v = ToLower(s);
    if (v == L"cant_reach_internet" || v == L"outbound") return Direction::CantReachInternet;
    if (v == L"cant_be_reached" || v == L"inbound") return Direction::CantBeReached;
    return Direction::FullyOffline;
}

static const wchar_t* DirectionLabel(Direction d) {
    switch (d) {
        case Direction::CantReachInternet: return L"Out only: the app can't reach the internet";
        case Direction::CantBeReached:     return L"In only: nothing can connect to the app";
        default:                           return L"Fully offline: blocks traffic both ways";
    }
}

static const wchar_t* DirectionShortLabel(Direction d) {
    switch (d) {
        case Direction::CantReachInternet: return L"Outbound";
        case Direction::CantBeReached:     return L"Inbound";
        default:                           return L"Offline";
    }
}

static int DpiScale(int px, UINT dpi) {
    return MulDiv(px, (int)dpi, 96);
}

static void LogAudit(const std::wstring& msg) {
    Wh_Log(L"%s", msg.c_str());
}

// ============================================================================
// Safety Classification
// ============================================================================

static const std::wstring& GetSelfDirLower() {
    static std::wstring s_dir = []() {
        wchar_t buf[MAX_PATH * 2]{};
        DWORD len = GetModuleFileNameW(nullptr, buf, ARRAYSIZE(buf));
        std::wstring p = (len > 0 && len < ARRAYSIZE(buf)) ? ToLower(std::wstring(buf, len)) : L"";
        size_t pos = p.find_last_of(L"\\/");
        return (pos != std::wstring::npos) ? p.substr(0, pos + 1) : L"";
    }();
    return s_dir;
}

static bool IsImmutableProtectedExe(const std::wstring& lowerExePath) {
    if (lowerExePath.empty()) return false;
    std::wstring name = GetFileNameOnly(lowerExePath);
    if (name == L"system") return true;

    bool hasDir = (lowerExePath.find_first_of(L"\\/") != std::wstring::npos);
    bool inWinSys = !hasDir ||
                    lowerExePath.find(L"\\windows\\system32\\") != std::wstring::npos ||
                    lowerExePath.find(L"\\windows\\syswow64\\") != std::wstring::npos ||
                    lowerExePath.find(L"\\windows\\winsxs\\") != std::wstring::npos;

    // Core OS kernel, session managers, and Windows Security / SmartScreen in System32/SysWOW64
    static const wchar_t* kCoreWinSys[] = {
        L"svchost.exe", L"lsass.exe", L"services.exe", L"csrss.exe",
        L"winlogon.exe", L"smss.exe", L"wininit.exe", L"ntoskrnl.exe",
        L"smartscreen.exe", L"securityhealthservice.exe", L"securityhealthsystray.exe"
    };
    if (inWinSys) {
        for (auto* c : kCoreWinSys) {
            if (name == c) return true;
        }
    }

    // Windhawk hosts (1.7.3 & 2.0) in Windhawk's install folder
    if (name == L"windhawk.exe" || name == L"windhawk-mod.exe" ||
        name == L"windhawk-mod-elevated.exe" || name == L"windhawk-mod-uiaccess.exe") {
        const std::wstring& selfDir = GetSelfDirLower();
        if (!hasDir ||
            (!selfDir.empty() && lowerExePath.compare(0, selfDir.size(), selfDir) == 0) ||
            lowerExePath.find(L"\\windhawk\\") != std::wstring::npos) {
            return true;
        }
    }

    // Microsoft Defender platform & service executables
    if (name == L"msmpeng.exe" || name == L"nissrv.exe" ||
        name == L"mpcmdrun.exe" || name == L"mpdefendercoreservice.exe") {
        if (!hasDir || inWinSys ||
            lowerExePath.find(L"\\microsoft\\windows defender\\") != std::wstring::npos ||
            lowerExePath.find(L"\\windows defender\\") != std::wstring::npos ||
            lowerExePath.find(L"\\windows defender advanced threat protection\\") != std::wstring::npos) {
            return true;
        }
    }

    // Third-party AV / EDR executables: require Program Files / ProgramData / System32 AND vendor folder match
    bool inProtectedRoot = !hasDir || inWinSys ||
                           lowerExePath.find(L"\\program files\\") != std::wstring::npos ||
                           lowerExePath.find(L"\\program files (x86)\\") != std::wstring::npos ||
                           lowerExePath.find(L"\\programdata\\") != std::wstring::npos;
    if (!inProtectedRoot) return false;

    struct VendorAvRule {
        const wchar_t* exeName;
        const wchar_t* vendorDir;
    };
    static const VendorAvRule kVendorAv[] = {
        // Kaspersky
        {L"avp.exe", L"\\kaspersky"}, {L"avpui.exe", L"\\kaspersky"},
        // Bitdefender
        {L"vsserv.exe", L"\\bitdefender"}, {L"bdservicehost.exe", L"\\bitdefender"},
        {L"bdagent.exe", L"\\bitdefender"}, {L"updatesrv.exe", L"\\bitdefender"},
        // ESET
        {L"ekrn.exe", L"\\eset"}, {L"egui.exe", L"\\eset"}, {L"eguiproxy.exe", L"\\eset"},
        // Malwarebytes
        {L"mbamservice.exe", L"\\malwarebytes"}, {L"mbam.exe", L"\\malwarebytes"}, {L"mbamtray.exe", L"\\malwarebytes"},
        // Avast / AVG
        {L"avastsvc.exe", L"\\avast"}, {L"avastui.exe", L"\\avast"}, {L"afwserv.exe", L"\\avast"},
        {L"avgsvc.exe", L"\\avg"}, {L"avgui.exe", L"\\avg"},
        // McAfee / Trellix
        {L"mcshield.exe", L"\\mcafee"}, {L"mfemms.exe", L"\\mcafee"}, {L"mfevtps.exe", L"\\mcafee"}, {L"masvc.exe", L"\\mcafee"},
        {L"mcshield.exe", L"\\trellix"}, {L"mfemms.exe", L"\\trellix"}, {L"mfevtps.exe", L"\\trellix"}, {L"masvc.exe", L"\\trellix"},
        // Trend Micro
        {L"coreframeworkhost.exe", L"\\trend micro"}, {L"coreserviceshell.exe", L"\\trend micro"},
        {L"ntrtscan.exe", L"\\trend micro"}, {L"tmccsf.exe", L"\\trend micro"},
        // Sophos
        {L"sophosfs.exe", L"\\sophos"}, {L"sophoshealth.exe", L"\\sophos"},
        {L"sophosnetfilter.exe", L"\\sophos"}, {L"sspservice.exe", L"\\sophos"}, {L"savservice.exe", L"\\sophos"},
        // Norton / Symantec
        {L"nortonsecurity.exe", L"\\norton"}, {L"ns.exe", L"\\norton"}, {L"ccsvchst.exe", L"\\norton"},
        {L"nortonsecurity.exe", L"\\symantec"}, {L"ns.exe", L"\\symantec"}, {L"ccsvchst.exe", L"\\symantec"}, {L"symcorpui.exe", L"\\symantec"},
        // CrowdStrike Falcon & SentinelOne
        {L"csfalconservice.exe", L"\\crowdstrike"}, {L"csfalconcontainer.exe", L"\\crowdstrike"},
        {L"sentinelagent.exe", L"\\sentinelone"}, {L"sentinelservicehost.exe", L"\\sentinelone"},
        {L"sentinelstaticengine.exe", L"\\sentinelone"}, {L"sentinelui.exe", L"\\sentinelone"}
    };
    for (const auto& rule : kVendorAv) {
        if (name == rule.exeName && (!hasDir || lowerExePath.find(rule.vendorDir) != std::wstring::npos)) {
            return true;
        }
    }
    return false;
}

static bool IsCriticalSystemExe(const std::wstring& lowerExePath) {
    if (IsImmutableProtectedExe(lowerExePath)) return true;
    std::wstring name = GetFileNameOnly(lowerExePath);
    static const wchar_t* kCritical[] = {
        L"dwm.exe", L"wuauclt.exe", L"usoclient.exe",
        L"audiodg.exe", L"fontdrvhost.exe", L"sihost.exe",
        L"conhost.exe", L"ctfmon.exe", L"wlanext.exe", L"dashost.exe",
        L"searchhost.exe", L"startmenuexperiencehost.exe", L"shellexperiencehost.exe",
        L"taskmgr.exe"
    };
    for (auto* c : kCritical) {
        if (name == c) return true;
    }
    return false;
}

static bool IsSystemPath(const std::wstring& lowerExePath) {
    if (lowerExePath.find(L"\\windows\\system32\\") != std::wstring::npos) return true;
    if (lowerExePath.find(L"\\windows\\syswow64\\") != std::wstring::npos) return true;
    if (lowerExePath.find(L"\\windows\\") != std::wstring::npos &&
        lowerExePath.find(L"\\windowsapps\\") == std::wstring::npos) {
        return true;
    }
    return false;
}

static bool IsVpnOrRemoteExe(const std::wstring& lowerExePath) {
    std::wstring name = GetFileNameOnly(lowerExePath);
    static const wchar_t* kRemote[] = {
        L"mstsc.exe", L"msrdc.exe", L"teamviewer.exe", L"anydesk.exe",
        L"rustdesk.exe", L"parsec.exe", L"openvpn.exe", L"openvpn-gui.exe",
        L"wireguard.exe", L"tailscaled.exe", L"tailscale-ipn.exe", L"tailscale.exe",
        L"zerotier-one_x64.exe", L"nordvpn.exe", L"protonvpn.exe", L"protonvpn.service.exe",
        L"mullvad-vpn.exe", L"mullvad-daemon.exe", L"expressvpn.exe", L"surfshark.exe",
        L"cloudflare-warp.exe", L"warp-svc.exe", L"sunshine.exe", L"moonlight.exe",
        L"splashtop.exe", L"chrome_remote_desktop_host.exe", L"nomachine.exe",
        L"nxplayer.exe", L"hamachi-2.exe", L"radmin.exe", L"vncviewer.exe"
    };
    for (auto* r : kRemote) {
        if (name == r) return true;
    }
    if (GetSystemMetrics(SM_REMOTESESSION) != 0 &&
        (name == L"rdpclip.exe" || name == L"tstheme.exe")) {
        return true;
    }
    return false;
}

// ============================================================================
// Process & Network Discovery
// ============================================================================

static std::wstring QueryProcessExePath(DWORD pid) {
    if (pid == 0 || pid == 4) return L"";
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProc) return L"";
    wchar_t buf[MAX_PATH * 2]{};
    DWORD len = (DWORD)(sizeof(buf) / sizeof(buf[0]));
    std::wstring result;
    if (QueryFullProcessImageNameW(hProc, 0, buf, &len)) {
        result.assign(buf, len);
    }
    CloseHandle(hProc);
    return result;
}

static std::vector<BYTE> ExtractProcessUserSidBytes(HANDLE hProc) {
    std::vector<BYTE> out;
    if (!hProc) return out;
    HANDLE hTok = nullptr;
    if (!OpenProcessToken(hProc, TOKEN_QUERY, &hTok)) return out;
    DWORD len = 0;
    GetTokenInformation(hTok, TokenUser, nullptr, 0, &len);
    if (len > 0) {
        std::vector<BYTE> buf(len);
        if (GetTokenInformation(hTok, TokenUser, buf.data(), len, &len)) {
            auto* tu = reinterpret_cast<TOKEN_USER*>(buf.data());
            if (tu->User.Sid && IsValidSid(tu->User.Sid)) {
                DWORD sidLen = GetLengthSid(tu->User.Sid);
                out.assign(reinterpret_cast<BYTE*>(tu->User.Sid),
                           reinterpret_cast<BYTE*>(tu->User.Sid) + sidLen);
            }
        }
    }
    CloseHandle(hTok);
    return out;
}

static const std::vector<BYTE>& GetCurrentUserSidBytes() {
    static std::vector<BYTE> s_sid = []() {
        return ExtractProcessUserSidBytes(GetCurrentProcess());
    }();
    return s_sid;
}

static const std::vector<BYTE>& GetInteractiveShellUserSidBytes() {
    static std::mutex s_shellMtx;
    static DWORD s_cachedShellPid = 0;
    static std::vector<BYTE> s_cachedShellSid;

    HWND hShell = GetShellWindow();
    DWORD shellPid = 0;
    if (hShell) GetWindowThreadProcessId(hShell, &shellPid);

    std::lock_guard<std::mutex> lk(s_shellMtx);
    if (shellPid != 0 && shellPid == s_cachedShellPid && !s_cachedShellSid.empty()) {
        return s_cachedShellSid;
    }
    s_cachedShellPid = shellPid;
    s_cachedShellSid.clear();
    if (shellPid != 0) {
        HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, shellPid);
        if (hProc) {
            s_cachedShellSid = ExtractProcessUserSidBytes(hProc);
            CloseHandle(hProc);
        }
    }
    return s_cachedShellSid;
}

static bool IsProcessInCurrentUserSession(DWORD pid, HANDLE hExistingProc = nullptr) {
    if (pid == 0 || pid == 4) return false;
    static DWORD s_selfSession = []() {
        DWORD sid = 0;
        ProcessIdToSessionId(GetCurrentProcessId(), &sid);
        return sid;
    }();
    DWORD procSession = 0;
    if (!ProcessIdToSessionId(pid, &procSession)) return false;
    if (procSession == 0 || procSession != s_selfSession) return false;

    const auto& selfSid = GetCurrentUserSidBytes();
    if (selfSid.empty()) return true;

    HANDLE hProc = hExistingProc ? hExistingProc : OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    // If a protection/anti-cheat driver shields a process in the user's own interactive session from handle/token queries,
    // treat it as belonging to the current interactive user rather than locking it as Session 0 / Other User.
    if (!hProc) return true;
    std::vector<BYTE> procSid = ExtractProcessUserSidBytes(hProc);
    if (!hExistingProc) CloseHandle(hProc);
    if (procSid.empty()) return true;

    if (EqualSid(reinterpret_cast<PSID>(const_cast<BYTE*>(selfSid.data())),
                 reinterpret_cast<PSID>(procSid.data()))) {
        return true;
    }
    // Support Over-the-Shoulder UAC where a Standard desktop user elevates Windhawk with a separate Admin account
    const auto& shellSid = GetInteractiveShellUserSidBytes();
    if (!shellSid.empty() &&
        EqualSid(reinterpret_cast<PSID>(const_cast<BYTE*>(shellSid.data())),
                 reinterpret_cast<PSID>(procSid.data()))) {
        return true;
    }
    return false;
}

struct ProcessSnapshotItem {
    DWORD pid = 0;
    DWORD parentPid = 0;
    std::wstring exePath;
    bool isCurrentUserSession = false;
};

static void UpdateOtherSessionCacheFromSnap(const std::vector<ProcessSnapshotItem>& snap) {
    std::unordered_set<std::wstring> curUserSet;
    std::unordered_set<std::wstring> otherSet;
    for (const auto& item : snap) {
        std::wstring low = ToLower(item.exePath);
        if (low.empty()) continue;
        if (item.isCurrentUserSession) curUserSet.insert(low);
        else otherSet.insert(low);
    }
    std::unordered_set<std::wstring> onlyOther;
    for (const auto& low : otherSet) {
        if (curUserSet.count(low) == 0) onlyOther.insert(low);
    }
    std::lock_guard<std::mutex> lk(g_otherSessionCacheMtx);
    g_cachedOtherSessionOnlyExes = std::move(onlyOther);
    g_otherSessionCacheInitialized = true;
}

static std::vector<ProcessSnapshotItem> CaptureProcessSnapshot() {
    std::vector<ProcessSnapshotItem> out;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return out;
    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);
    if (Process32FirstW(snap, &pe)) {
        do {
            DWORD pid = pe.th32ProcessID;
            if (pid == 0 || pid == 4) continue;
            HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
            if (!hProc) continue;
            wchar_t buf[MAX_PATH * 2]{};
            DWORD len = (DWORD)(sizeof(buf) / sizeof(buf[0]));
            if (QueryFullProcessImageNameW(hProc, 0, buf, &len) && len > 0) {
                std::wstring path(buf, len);
                bool inCurSession = IsProcessInCurrentUserSession(pid, hProc);
                out.push_back({pid, pe.th32ParentProcessID, std::move(path), inCurSession});
            }
            CloseHandle(hProc);
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    UpdateOtherSessionCacheFromSnap(out);
    return out;
}

static bool IsExeOnlyInOtherSessionOrUser(const std::wstring& lowerExePath,
                                          const std::vector<ProcessSnapshotItem>* optSnap = nullptr) {
    if (lowerExePath.empty()) return false;
    if (optSnap) {
        bool hasCurrentUser = false;
        bool hasOther = false;
        for (const auto& item : *optSnap) {
            if (ToLower(item.exePath) == lowerExePath) {
                if (item.isCurrentUserSession) hasCurrentUser = true;
                else hasOther = true;
            }
        }
        return hasOther && !hasCurrentUser;
    }
    if (!g_lastFgExe.empty() && lowerExePath == g_lastFgExe) {
        return g_lastFgIsOtherSessionOrUser;
    }
    {
        std::lock_guard<std::mutex> lk(g_otherSessionCacheMtx);
        if (g_otherSessionCacheInitialized) {
            return g_cachedOtherSessionOnlyExes.count(lowerExePath) > 0;
        }
    }
    auto localSnap = CaptureProcessSnapshot();
    return IsExeOnlyInOtherSessionOrUser(lowerExePath, &localSnap);
}

static std::vector<std::wstring> CollectChildExePathsFromSnap(const std::wstring& parentLowerPath,
                                                               const std::vector<ProcessSnapshotItem>& snap) {
    std::vector<std::wstring> result;
    std::unordered_set<DWORD> rootPids;
    std::unordered_map<DWORD, std::vector<DWORD>> childrenMap;
    std::unordered_map<DWORD, std::wstring> pidToPath;

    for (const auto& item : snap) {
        if (!item.isCurrentUserSession) continue;
        std::wstring low = ToLower(item.exePath);
        pidToPath[item.pid] = low;
        childrenMap[item.parentPid].push_back(item.pid);
        if (low == parentLowerPath) {
            rootPids.insert(item.pid);
        }
    }

    std::unordered_set<DWORD> visited;
    std::vector<DWORD> stack(rootPids.begin(), rootPids.end());
    std::unordered_set<std::wstring> uniqueExes;
    if (!IsImmutableProtectedExe(parentLowerPath)) {
        uniqueExes.insert(parentLowerPath);
    }

    size_t slashPos = parentLowerPath.find_last_of(L"\\/");
    std::wstring rootDir = (slashPos != std::wstring::npos) ? parentLowerPath.substr(0, slashPos + 1) : L"";
    wchar_t winDirBuf[MAX_PATH]{};
    std::wstring winDir;
    if (GetWindowsDirectoryW(winDirBuf, ARRAYSIZE(winDirBuf)) > 0) {
        winDir = ToLower(winDirBuf);
        if (!winDir.empty() && winDir.back() != L'\\') winDir.push_back(L'\\');
    }
    auto isSharedRuntime = [](const std::wstring& p) -> bool {
        std::wstring fn = GetFileNameOnly(p);
        static const wchar_t* kShared[] = {
            L"msedgewebview2.exe", L"powershell.exe", L"pwsh.exe", L"cmd.exe",
            L"conhost.exe", L"git.exe", L"node.exe", L"python.exe", L"pythonw.exe"
        };
        for (auto* s : kShared) if (fn == s) return true;
        return false;
    };

    while (!stack.empty()) {
        DWORD cur = stack.back();
        stack.pop_back();
        if (!visited.insert(cur).second) continue;
        auto itPath = pidToPath.find(cur);
        if (itPath != pidToPath.end() && !IsImmutableProtectedExe(itPath->second) && !IsCriticalSystemExe(itPath->second)) {
            const std::wstring& cp = itPath->second;
            bool inRoot = !rootDir.empty() && cp.size() >= rootDir.size() &&
                          cp.compare(0, rootDir.size(), rootDir) == 0;
            bool inWinDir = !winDir.empty() && cp.size() >= winDir.size() &&
                            cp.compare(0, winDir.size(), winDir) == 0;
            if (cp == parentLowerPath || (inRoot && !inWinDir && !isSharedRuntime(cp))) {
                uniqueExes.insert(cp);
            }
        }
        auto itCh = childrenMap.find(cur);
        if (itCh != childrenMap.end()) {
            for (DWORD ch : itCh->second) {
                stack.push_back(ch);
            }
        }
    }
    result.assign(uniqueExes.begin(), uniqueExes.end());
    return result;
}

static std::unordered_set<DWORD> GetPidsWithLiveNetwork() {
    std::unordered_set<DWORD> pids;
    DWORD size = 0;
    if (GetExtendedTcpTable(nullptr, &size, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) == ERROR_INSUFFICIENT_BUFFER && size > 0) {
        std::vector<BYTE> buf(size);
        if (GetExtendedTcpTable(buf.data(), &size, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) == NO_ERROR) {
            auto* tbl = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buf.data());
            for (DWORD i = 0; i < tbl->dwNumEntries; ++i) {
                pids.insert(tbl->table[i].dwOwningPid);
            }
        }
    }
    size = 0;
    if (GetExtendedTcpTable(nullptr, &size, FALSE, AF_INET6, TCP_TABLE_OWNER_PID_ALL, 0) == ERROR_INSUFFICIENT_BUFFER && size > 0) {
        std::vector<BYTE> buf(size);
        if (GetExtendedTcpTable(buf.data(), &size, FALSE, AF_INET6, TCP_TABLE_OWNER_PID_ALL, 0) == NO_ERROR) {
            auto* tbl = reinterpret_cast<PMIB_TCP6TABLE_OWNER_PID>(buf.data());
            for (DWORD i = 0; i < tbl->dwNumEntries; ++i) {
                pids.insert(tbl->table[i].dwOwningPid);
            }
        }
    }
    size = 0;
    if (GetExtendedUdpTable(nullptr, &size, FALSE, AF_INET, UDP_TABLE_OWNER_PID, 0) == ERROR_INSUFFICIENT_BUFFER && size > 0) {
        std::vector<BYTE> buf(size);
        if (GetExtendedUdpTable(buf.data(), &size, FALSE, AF_INET, UDP_TABLE_OWNER_PID, 0) == NO_ERROR) {
            auto* tbl = reinterpret_cast<PMIB_UDPTABLE_OWNER_PID>(buf.data());
            for (DWORD i = 0; i < tbl->dwNumEntries; ++i) {
                pids.insert(tbl->table[i].dwOwningPid);
            }
        }
    }
    size = 0;
    if (GetExtendedUdpTable(nullptr, &size, FALSE, AF_INET6, UDP_TABLE_OWNER_PID, 0) == ERROR_INSUFFICIENT_BUFFER && size > 0) {
        std::vector<BYTE> buf(size);
        if (GetExtendedUdpTable(buf.data(), &size, FALSE, AF_INET6, UDP_TABLE_OWNER_PID, 0) == NO_ERROR) {
            auto* tbl = reinterpret_cast<PMIB_UDP6TABLE_OWNER_PID>(buf.data());
            for (DWORD i = 0; i < tbl->dwNumEntries; ++i) {
                pids.insert(tbl->table[i].dwOwningPid);
            }
        }
    }
    return pids;
}

struct EnumWinCtx {
    std::unordered_set<DWORD> visiblePids;
};

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    if (!IsWindowVisible(hwnd)) return TRUE;
    if (GetWindow(hwnd, GW_OWNER) != nullptr) return TRUE;
    LONG exStyle = GetWindowLongW(hwnd, GWL_EXSTYLE);
    if (exStyle & WS_EX_TOOLWINDOW) return TRUE;
    RECT rc{};
    if (!GetWindowRect(hwnd, &rc) || (rc.right - rc.left) <= 0 || (rc.bottom - rc.top) <= 0) return TRUE;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid) {
        reinterpret_cast<EnumWinCtx*>(lParam)->visiblePids.insert(pid);
    }
    return TRUE;
}

// ============================================================================
// WFP Dynamic Session Engine
// ============================================================================

static bool EnsureWfpEngineLocked() {
    if (g_wfpEngine) return true;
    FWPM_SESSION0 session{};
    session.flags = FWPM_SESSION_DYNAMIC;
    static wchar_t sName[] = L"Seamless Windows Firewall session";
    session.displayData.name = sName;
    DWORD err = FwpmEngineOpen0(nullptr, RPC_C_AUTHN_WINNT, nullptr, &session, &g_wfpEngine);
    if (err != ERROR_SUCCESS) {
        Wh_Log(L"FwpmEngineOpen0 failed: 0x%08X", err);
        g_wfpEngine = nullptr;
        return false;
    }

    if (!g_hasCustomSublayer) {
        if (UuidCreate(&g_sublayerGuid) == RPC_S_OK) {
            FWPM_SUBLAYER0 sub{};
            sub.subLayerKey = g_sublayerGuid;
            static wchar_t subName[] = L"Seamless Windows Firewall sublayer";
            sub.displayData.name = subName;
            sub.displayData.description = subName;
            sub.flags = 0;
            sub.weight = 0xFFFF;
            DWORD subErr = FwpmSubLayerAdd0(g_wfpEngine, &sub, nullptr);
            if (subErr == ERROR_SUCCESS || subErr == (DWORD)FWP_E_ALREADY_EXISTS) {
                g_hasCustomSublayer = true;
            } else {
                g_sublayerGuid = kWfpSublayerUniversal;
                g_hasCustomSublayer = true;
            }
        } else {
            g_sublayerGuid = kWfpSublayerUniversal;
            g_hasCustomSublayer = true;
        }
    }
    return true;
}

static void CloseWfpEngineLocked() {
    if (g_wfpEngine) {
        FwpmEngineClose0(g_wfpEngine);
        g_wfpEngine = nullptr;
        g_hasCustomSublayer = false;
    }
}

static bool AddWfpBlockForExeLocked(const std::wstring& exePath, Direction dir, std::vector<WfpFilterEntry>& outFilters, bool& outAccessDenied) {
    outAccessDenied = false;
    if (!EnsureWfpEngineLocked()) return false;

    FWP_BYTE_BLOB* appBlob = nullptr;
    PVOID oldRedir = nullptr;
    BOOL redirDisabled = Wow64DisableWow64FsRedirection(&oldRedir);
    DWORD err = FwpmGetAppIdFromFileName0(exePath.c_str(), &appBlob);
    if (redirDisabled) Wow64RevertWow64FsRedirection(oldRedir);

    if (err != ERROR_SUCCESS || !appBlob) {
        Wh_Log(L"FwpmGetAppIdFromFileName0 failed for %s: 0x%08X", exePath.c_str(), err);
        return false;
    }

    auto addLayer = [&](const GUID& layerKey) -> bool {
        FWPM_FILTER_CONDITION0 cond{};
        cond.fieldKey = kWfpCondAleAppId;
        cond.matchType = FWP_MATCH_EQUAL;
        cond.conditionValue.type = FWP_BYTE_BLOB_TYPE;
        cond.conditionValue.byteBlob = appBlob;

        FWPM_FILTER0 filter{};
        static wchar_t fName[] = L"SeamlessFirewall_SessionBlock";
        filter.displayData.name = fName;
        filter.layerKey = layerKey;
        filter.subLayerKey = g_sublayerGuid;
        filter.action.type = FWP_ACTION_BLOCK;
        filter.flags = 0;
        filter.weight.type = FWP_UINT8;
        filter.weight.uint8 = 15;
        filter.numFilterConditions = 1;
        filter.filterCondition = &cond;

        UINT64 filterId = 0;
        DWORD addErr = FwpmFilterAdd0(g_wfpEngine, &filter, nullptr, &filterId);
        if (addErr == ERROR_SUCCESS) {
            outFilters.push_back({filterId, exePath});
            return true;
        }
        if (addErr == ERROR_ACCESS_DENIED) outAccessDenied = true;
        Wh_Log(L"FwpmFilterAdd0 failed: 0x%08X", addErr);
        return false;
    };

    bool anyAdded = false;
    if (dir == Direction::FullyOffline || dir == Direction::CantReachInternet) {
        anyAdded |= addLayer(kWfpLayerAleAuthConnectV4);
        anyAdded |= addLayer(kWfpLayerAleAuthConnectV6);
    }
    if (dir == Direction::FullyOffline || dir == Direction::CantBeReached) {
        anyAdded |= addLayer(kWfpLayerAleAuthRecvAcceptV4);
        anyAdded |= addLayer(kWfpLayerAleAuthRecvAcceptV6);
    }

    FwpmFreeMemory0(reinterpret_cast<void**>(&appBlob));
    return anyAdded;
}

static void RemoveWfpFiltersLocked(std::vector<WfpFilterEntry>& filters) {
    if (!g_wfpEngine) {
        filters.clear();
        return;
    }
    for (const auto& f : filters) {
        FwpmFilterDeleteById0(g_wfpEngine, f.filterId);
    }
    filters.clear();
}

struct ExtFwInfo {
    int dirMask = 0;
    std::wstring ruleName;
};
static std::mutex g_extFwMtx;
static std::unordered_map<std::wstring, ExtFwInfo> g_extFwBlocks;
static ULONGLONG g_extFwScanTick = 0;

static std::unordered_map<std::wstring, ExtFwInfo> GetCachedExternalFirewallBlocks() {
    std::lock_guard<std::mutex> lk(g_extFwMtx);
    return g_extFwBlocks;
}

static std::unordered_map<std::wstring, ExtFwInfo> ScanExternalFirewallBlocks(bool force = false) {
    ULONGLONG now = GetTickCount64();
    {
        std::lock_guard<std::mutex> lk(g_extFwMtx);
        if (!force && g_extFwScanTick != 0 && (now - g_extFwScanTick) < 15000) {
            return g_extFwBlocks;
        }
    }

    std::unordered_map<std::wstring, ExtFwInfo> fresh;
    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    INetFwPolicy2* pPolicy = nullptr;
    if (SUCCEEDED(CoCreateInstance(__uuidof(NetFwPolicy2), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPolicy))) && pPolicy) {
        long currentProfiles = NET_FW_PROFILE2_ALL;
        pPolicy->get_CurrentProfileTypes(&currentProfiles);

        INetFwRules* pRules = nullptr;
        if (SUCCEEDED(pPolicy->get_Rules(&pRules)) && pRules) {
            IUnknown* pUnk = nullptr;
            if (SUCCEEDED(pRules->get__NewEnum(&pUnk)) && pUnk) {
                IEnumVARIANT* pEnum = nullptr;
                if (SUCCEEDED(pUnk->QueryInterface(IID_PPV_ARGS(&pEnum))) && pEnum) {
                    VARIANT var{};
                    ULONG fetched = 0;
                    while (pEnum->Next(1, &var, &fetched) == S_OK && fetched == 1) {
                        if (var.vt == VT_DISPATCH && var.pdispVal) {
                            INetFwRule* pRule = nullptr;
                            if (SUCCEEDED(var.pdispVal->QueryInterface(IID_PPV_ARGS(&pRule))) && pRule) {
                                VARIANT_BOOL enabled = VARIANT_FALSE;
                                NET_FW_ACTION action = NET_FW_ACTION_ALLOW;
                                long profiles = 0;
                                if (SUCCEEDED(pRule->get_Enabled(&enabled)) && enabled == VARIANT_TRUE &&
                                    SUCCEEDED(pRule->get_Action(&action)) && action == NET_FW_ACTION_BLOCK &&
                                    SUCCEEDED(pRule->get_Profiles(&profiles)) &&
                                    ((profiles & currentProfiles) != 0 || profiles == NET_FW_PROFILE2_ALL)) {
                                    BSTR bName = nullptr;
                                    bool isOurs = false;
                                    std::wstring ruleNameStr;
                                    if (SUCCEEDED(pRule->get_Name(&bName)) && bName) {
                                        if (wcsncmp(bName, kRulePrefix, wcslen(kRulePrefix)) == 0) {
                                            isOurs = true;
                                        } else {
                                            ruleNameStr = bName;
                                        }
                                        SysFreeString(bName);
                                    }
                                    if (!isOurs) {
                                        auto isWildcardOrEmpty = [](BSTR b) {
                                            if (!b || !*b) return true;
                                            return wcscmp(b, L"*") == 0 || _wcsicmp(b, L"All") == 0;
                                        };
                                        long proto = NET_FW_IP_PROTOCOL_ANY;
                                        pRule->get_Protocol(&proto);
                                        BSTR bLP = nullptr, bRP = nullptr, bRA = nullptr, bLA = nullptr;
                                        pRule->get_LocalPorts(&bLP);
                                        pRule->get_RemotePorts(&bRP);
                                        pRule->get_RemoteAddresses(&bRA);
                                        pRule->get_LocalAddresses(&bLA);
                                        bool isBlanket = (proto == NET_FW_IP_PROTOCOL_ANY) &&
                                                         isWildcardOrEmpty(bLP) && isWildcardOrEmpty(bRP) &&
                                                         isWildcardOrEmpty(bRA) && isWildcardOrEmpty(bLA);
                                        if (bLP) SysFreeString(bLP);
                                        if (bRP) SysFreeString(bRP);
                                        if (bRA) SysFreeString(bRA);
                                        if (bLA) SysFreeString(bLA);

                                        if (isBlanket) {
                                            BSTR bApp = nullptr;
                                            if (SUCCEEDED(pRule->get_ApplicationName(&bApp)) && bApp) {
                                                if (*bApp) {
                                                    std::wstring rawApp(bApp);
                                                    static BOOL s_isWow64 = []() {
                                                        BOOL w = FALSE;
                                                        IsWow64Process(GetCurrentProcess(), &w);
                                                        return w;
                                                    }();
                                                    if (s_isWow64 && _wcsnicmp(rawApp.c_str(), L"%ProgramFiles%", 14) == 0) {
                                                        rawApp = L"%ProgramW6432%" + rawApp.substr(14);
                                                    }
                                                    wchar_t expanded[MAX_PATH * 2]{};
                                                    DWORD expLen = ExpandEnvironmentStringsW(rawApp.c_str(), expanded, ARRAYSIZE(expanded));
                                                    std::wstring appLow = ToLower((expLen > 0 && expLen < ARRAYSIZE(expanded)) ? expanded : rawApp);
                                                    NET_FW_RULE_DIRECTION fwDir = NET_FW_RULE_DIR_OUT;
                                                    pRule->get_Direction(&fwDir);
                                                    int bit = (fwDir == NET_FW_RULE_DIR_IN) ? 2 : 1;
                                                    auto& info = fresh[appLow];
                                                    info.dirMask |= bit;
                                                    if (info.ruleName.empty() && !ruleNameStr.empty()) {
                                                        info.ruleName = ruleNameStr;
                                                    }
                                                }
                                                SysFreeString(bApp);
                                            }
                                        }
                                    }
                                }
                                pRule->Release();
                            }
                        }
                        VariantClear(&var);
                    }
                    pEnum->Release();
                }
                pUnk->Release();
            }
            pRules->Release();
        }
        pPolicy->Release();
    }
    if (SUCCEEDED(hrCo)) CoUninitialize();

    {
        std::lock_guard<std::mutex> lk(g_extFwMtx);
        g_extFwBlocks = fresh;
        g_extFwScanTick = now;
    }
    return fresh;
}

// ============================================================================
// High-Level Block / Allow / Restore / Pulse Operations
// ============================================================================

static void TriggerPulse(PulseKind kind) {
    if (!g_hWnd) return;
    g_pillPulse.Trigger(kind, 1500.0);
    SetTimer(g_hWnd, TIMER_ANIM_VSYNC, 16, nullptr);
    RequestRepaint();
}

static bool IsDesktopOrShellWindow(HWND hwnd) {
    if (!hwnd || !IsWindow(hwnd)) return true;
    wchar_t cls[128]{};
    if (GetClassNameW(hwnd, cls, ARRAYSIZE(cls)) > 0) {
        if (wcscmp(cls, L"Progman") == 0 ||
            wcscmp(cls, L"WorkerW") == 0 ||
            wcscmp(cls, L"Shell_TrayWnd") == 0 ||
            wcscmp(cls, L"Shell_SecondaryTrayWnd") == 0 ||
            wcscmp(cls, L"NotifyIconOverflowWindow") == 0 ||
            wcscmp(cls, L"Windows.UI.Core.CoreWindow") == 0 ||
            wcscmp(cls, L"TaskListThumbnailWnd") == 0) {
            return true;
        }
    }
    return false;
}

static void SyncForegroundStateAndFilter(bool allowFilterJump) {
    HWND fg = GetForegroundWindow();
    if (fg == g_hWnd) return;

    if (g_hCyclePopup && fg == g_hCyclePopup) return;
    if (g_hCycleWidget && fg == g_hCycleWidget) return;

    if (!fg || IsDesktopOrShellWindow(fg)) {
        g_lastFgExe.clear();
        g_lastFgIsOtherSessionOrUser = false;
        NotifyCycleFocusChanged(L"");
        if (g_statusBanner.find(L"Windows Defender Firewall") != std::wstring::npos) {
            g_statusBanner.clear();
        }
        return;
    }

    DWORD pid = 0;
    GetWindowThreadProcessId(fg, &pid);
    DWORD resolvedPid = pid;
    std::wstring exe = pid ? QueryProcessExePath(pid) : L"";
    std::wstring low = ToLower(exe);
    if (GetFileNameOnly(low) == L"applicationframehost.exe") {
        struct UwpCtx { DWORD hostPid; DWORD childPid; std::wstring childExe; } uwp{pid, 0, L""};
        struct UwpEnum {
            static BOOL CALLBACK Proc(HWND ch, LPARAM lp) {
                auto* ctx = reinterpret_cast<UwpCtx*>(lp);
                DWORD cpid = 0;
                GetWindowThreadProcessId(ch, &cpid);
                if (cpid && cpid != ctx->hostPid) {
                    std::wstring ce = QueryProcessExePath(cpid);
                    if (!ce.empty()) { ctx->childPid = cpid; ctx->childExe = ce; return FALSE; }
                }
                return TRUE;
            }
        };
        EnumChildWindows(fg, UwpEnum::Proc, reinterpret_cast<LPARAM>(&uwp));
        if (!uwp.childExe.empty()) { resolvedPid = uwp.childPid; exe = uwp.childExe; low = ToLower(exe); }
    }
    if (exe.empty()) {
        g_lastFgExe.clear();
        g_lastFgIsOtherSessionOrUser = false;
        NotifyCycleFocusChanged(L"");
        return;
    }
    g_lastFgExe = low;
    g_lastFgIsOtherSessionOrUser = resolvedPid ? !IsProcessInCurrentUserSession(resolvedPid) : false;
    NotifyCycleFocusChanged(low);

    auto extFw = (g_extFwScanTick == 0) ? ScanExternalFirewallBlocks(false) : GetCachedExternalFirewallBlocks();
    auto itExt = extFw.find(low);
    bool isExtBlk = (itExt != extFw.end() && itExt->second.dirMask != 0);

    bool isNetBlk = false;
    {
        std::lock_guard<std::mutex> lk(g_engineMtx);
        auto it = g_blocks.find(low);
        isNetBlk = (it != g_blocks.end() && it->second.blocked);
    }

    if (allowFilterJump && !g_userPinnedFilter) {
        if (isExtBlk) {
            g_activeFilter = AppFilter::Blocked;
            g_blockedFirewallOnly = true;
            g_statusBanner = L"Windows Firewall already blocks this app. Change it in Windows Defender Firewall.";
        } else {
            if (g_activeFilter == AppFilter::Blocked && g_blockedFirewallOnly) {
                ModSettings defS;
                { std::lock_guard<std::mutex> lk(g_settingsMtx); defS = g_settings; }
                g_activeFilter = defS.defaultFilter;
                g_blockedFirewallOnly = false;
            } else if (isNetBlk && g_activeFilter == AppFilter::Blocked) {
                g_blockedFirewallOnly = false;
            }
            if (g_statusBanner.find(L"Windows Defender Firewall") != std::wstring::npos) {
                g_statusBanner.clear();
            }
        }
    }
}

static void TriggerForegroundPulse(const std::wstring& fgExe) {
    std::wstring low = ToLower(fgExe);
    if (low.empty() || g_excludedExes.count(low)) {
        g_pillPulse.active = false;
        g_pillPulse.kind = PulseKind::None;
        RequestRepaint();
        return;
    }

    bool isBlocked = false;
    {
        std::lock_guard<std::mutex> lk(g_engineMtx);
        auto it = g_blocks.find(low);
        isBlocked = (it != g_blocks.end() && it->second.blocked);
    }
    if (!isBlocked) {
        auto extFw = (g_extFwScanTick == 0) ? ScanExternalFirewallBlocks(false) : GetCachedExternalFirewallBlocks();
        auto itExt = extFw.find(low);
        isBlocked = (itExt != extFw.end() && itExt->second.dirMask != 0);
    }
    TriggerPulse(isBlocked ? PulseKind::BlockedRed : PulseKind::AllowedGreen);
}

static bool ApplyBlock(std::wstring exePath, Direction dir, bool includeChildren, bool askUser) {
    std::wstring low = ToLower(exePath);
    if (g_excludedExes.count(low)) {
        g_statusBanner = L"This app is on your hidden list.";
        return false;
    }
    if (IsImmutableProtectedExe(low)) {
        g_statusBanner = L"Core OS & security software cannot be blocked.";
        return false;
    }
    bool lockCrit = true;
    bool warnVpn = true;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        lockCrit = g_settings.lockSystemProcesses;
        warnVpn = g_settings.warnOnVpnOrRemote;
    }
    if (lockCrit && IsCriticalSystemExe(low)) {
        g_statusBanner = L"System-critical process is locked.";
        return false;
    }
    auto snap = CaptureProcessSnapshot();
    if (IsExeOnlyInOtherSessionOrUser(low, &snap)) {
        g_statusBanner = L"Session 0 / other-user process is isolated and locked.";
        return false;
    }
    if (warnVpn && askUser && IsVpnOrRemoteExe(low)) {
        if (!FwConfirm(L"Block a VPN or remote app?",
                       L"Blocking this app may cut your VPN or Remote Desktop connection.",
                       L"Block anyway", L"Keep it", true, false))
            return false;
    }

    std::vector<std::wstring> targets;
    if (includeChildren) {
        targets = CollectChildExePathsFromSnap(low, snap);
    }
    if (targets.empty()) targets.push_back(low);
    targets.erase(std::remove_if(targets.begin(), targets.end(),
        [lockCrit](const std::wstring& t) {
            return IsImmutableProtectedExe(t) ||
                   (lockCrit && IsCriticalSystemExe(t));
        }), targets.end());
    if (targets.empty()) return false;

    std::lock_guard<std::mutex> lk(g_engineMtx);
    std::vector<WfpFilterEntry> newFilters;
    bool anyOk = false;
    bool accessDenied = false;

    for (const auto& t : targets) {
        bool denied = false;
        anyOk |= AddWfpBlockForExeLocked(t, dir, newFilters, denied);
        accessDenied |= denied;
    }

    if (!anyOk) {
        RemoveWfpFiltersLocked(newFilters);
        if (accessDenied || !IsProcessElevated()) {
            g_needsElevation = true;
            g_statusBanner = L"Windhawk needs to run as administrator to block apps.";
        } else {
            g_statusBanner = L"Could not add WFP filter for this app.";
        }
        LogAudit(L"BLOCK FAILED: " + exePath);
        return false;
    }

    g_needsElevation = false;
    auto& state = g_blocks[low];
    RemoveWfpFiltersLocked(state.sessionFilters);
    state.blocked = true;
    state.includeChildProcesses = includeChildren;
    state.direction = dir;
    state.sessionFilters = std::move(newFilters);
    state.blockedChildren.clear();
    state.blockedChildPaths.clear();
    for (const auto& t : targets) {
        if (t != low) {
            state.blockedChildPaths.insert(t);
            state.blockedChildren.push_back(GetFileNameOnly(t));
        }
    }

    LogAudit(L"BLOCK [SESSION] " + exePath + L" (" + DirectionShortLabel(dir) + L")");
    g_statusBanner.clear();
    TriggerPulse(PulseKind::BlockedRed);
    return true;
}

static void SyncLateChildBlocks() {
    std::vector<std::pair<std::wstring, Direction>> toCheck;
    {
        std::lock_guard<std::mutex> lk(g_engineMtx);
        for (const auto& kv : g_blocks) {
            if (kv.second.blocked && kv.second.includeChildProcesses) {
                toCheck.push_back({kv.first, kv.second.direction});
            }
        }
    }
    if (toCheck.empty()) return;
    auto snap = CaptureProcessSnapshot();
    for (const auto& item : toCheck) {
        auto children = CollectChildExePathsFromSnap(item.first, snap);
        std::lock_guard<std::mutex> lk(g_engineMtx);
        auto it = g_blocks.find(item.first);
        if (it == g_blocks.end() || !it->second.blocked) continue;
        for (const auto& ch : children) {
            if (ch == item.first) continue;
            if (it->second.blockedChildPaths.count(ch)) continue;
            if (it->second.allowedChildPaths.count(ch)) continue;
            bool denied = false;
            if (AddWfpBlockForExeLocked(ch, item.second, it->second.sessionFilters, denied)) {
                it->second.blockedChildPaths.insert(ch);
                it->second.blockedChildren.push_back(GetFileNameOnly(ch));
            }
        }
    }
}

static bool ApplyAllow(std::wstring exePath) {
    std::wstring low = ToLower(exePath);
    {
        std::lock_guard<std::mutex> lk(g_engineMtx);
        auto it = g_blocks.find(low);
        if (it != g_blocks.end()) {
            RemoveWfpFiltersLocked(it->second.sessionFilters);
            g_blocks.erase(it);
        } else {
            for (auto& kv : g_blocks) {
                if (!kv.second.blockedChildPaths.count(low)) continue;
                std::wstring childFn = GetFileNameOnly(low);
                kv.second.blockedChildPaths.erase(low);
                kv.second.allowedChildPaths.insert(low);
                kv.second.blockedChildren.erase(
                    std::remove(kv.second.blockedChildren.begin(), kv.second.blockedChildren.end(), childFn),
                    kv.second.blockedChildren.end());
                std::vector<WfpFilterEntry> kept;
                for (const auto& f : kv.second.sessionFilters) {
                    if (ToLower(f.exePath) == low) {
                        if (g_wfpEngine) FwpmFilterDeleteById0(g_wfpEngine, f.filterId);
                    } else {
                        kept.push_back(f);
                    }
                }
                kv.second.sessionFilters = std::move(kept);
            }
        }
    }
    LogAudit(L"ALLOW " + exePath);
    g_statusBanner.clear();
    TriggerPulse(PulseKind::AllowedGreen);
    return true;
}


// ============================================================================
// Cycle Mode Scheduler
// ============================================================================

struct CycleRuntime {
    std::wstring exePath;     // normalized lowercase
    std::wstring displayPath; // original case for ApplyBlock/ApplyAllow
    CycleConfig cfg;
    CyclePhase phase = CyclePhase::Blocked;
    double phaseStartMs = 0.0;
    double phaseTargetMs = 0.0;
    double totalEndMs = 0.0;
    uint64_t completedCycles = 0;
    bool pausedByFocus = false;
    bool pausedByUser = false;
    double pauseStartMs = 0.0;
    double lastProcCheckMs = 0.0;
    bool includeChildren = true;
};

static std::mutex g_cycleMtx;
static std::condition_variable g_cycleCv;
static std::unordered_map<std::wstring, CycleRuntime> g_cycles;
static std::unordered_map<std::wstring, CycleConfig> g_cycleTemplates;
static std::wstring g_cycleFgExe;
static std::wstring g_lastWidgetCycleExe;

static void LoadCycleTemplates() {
    std::unordered_map<std::wstring, CycleConfig> loaded;
    int count = Wh_GetIntValue(L"cycleTemplateCount", 0);
    for (int i = 0; i < count && i < 256; ++i) {
        std::wstring kKey = L"cycleTplKey_" + std::to_wstring(i);
        std::wstring vKey = L"cycleTplVal_" + std::to_wstring(i);
        wchar_t keyBuf[1024]{};
        wchar_t valBuf[256]{};
        if (Wh_GetStringValue(kKey.c_str(), keyBuf, ARRAYSIZE(keyBuf)) > 0 &&
            Wh_GetStringValue(vKey.c_str(), valBuf, ARRAYSIZE(valBuf)) > 0) {
            std::wstring exeLow = ToLower(Trim(keyBuf));
            if (exeLow.empty()) continue;
            std::vector<std::wstring> parts;
            std::wstringstream wss(valBuf);
            std::wstring tok;
            while (std::getline(wss, tok, L'|')) parts.push_back(tok);
            if (parts.size() == 6) {
                uint64_t bMs = (uint64_t)_wcstoui64(parts[0].c_str(), nullptr, 10);
                uint64_t aMs = (uint64_t)_wcstoui64(parts[1].c_str(), nullptr, 10);
                int rMode = _wtoi(parts[2].c_str());
                uint64_t rVal = (uint64_t)_wcstoui64(parts[3].c_str(), nullptr, 10);
                int foc = _wtoi(parts[4].c_str());
                int allowUnfoc = _wtoi(parts[5].c_str());
                if (bMs >= 100 && aMs >= 100 && rMode >= 0 && rMode <= 2) {
                    CycleConfig cfg;
                    cfg.blockMs = bMs;
                    cfg.allowMs = aMs;
                    cfg.runMode = (CycleRunMode)rMode;
                    cfg.runValue = rVal;
                    cfg.focusedOnly = (foc != 0);
                    cfg.allowWhenUnfocused = (allowUnfoc != 0);
                    loaded[exeLow] = cfg;
                }
            }
        }
    }
    std::lock_guard<std::mutex> lk(g_cycleMtx);
    g_cycleTemplates = std::move(loaded);
}

static void SaveCycleTemplates() {
    std::vector<std::pair<std::wstring, CycleConfig>> items;
    {
        std::lock_guard<std::mutex> lk(g_cycleMtx);
        items.reserve(g_cycleTemplates.size());
        for (const auto& kv : g_cycleTemplates) {
            items.push_back(kv);
        }
    }
    if (items.size() > 256) items.resize(256);
    int prevCount = std::min(Wh_GetIntValue(L"cycleTemplateCount", 0), 256);
    int newCount = (int)items.size();
    Wh_SetIntValue(L"cycleTemplateCount", newCount);
    for (int i = 0; i < newCount; ++i) {
        std::wstring kKey = L"cycleTplKey_" + std::to_wstring(i);
        std::wstring vKey = L"cycleTplVal_" + std::to_wstring(i);
        const CycleConfig& c = items[i].second;
        wchar_t valBuf[256]{};
        swprintf_s(valBuf, L"%llu|%llu|%d|%llu|%d|%d",
                   (unsigned long long)c.blockMs,
                   (unsigned long long)c.allowMs,
                   (int)c.runMode,
                   (unsigned long long)c.runValue,
                   c.focusedOnly ? 1 : 0,
                   c.allowWhenUnfocused ? 1 : 0);
        Wh_SetStringValue(kKey.c_str(), items[i].first.c_str());
        Wh_SetStringValue(vKey.c_str(), valBuf);
    }
    for (int i = newCount; i < prevCount; ++i) {
        std::wstring kKey = L"cycleTplKey_" + std::to_wstring(i);
        std::wstring vKey = L"cycleTplVal_" + std::to_wstring(i);
        Wh_DeleteValue(kKey.c_str());
        Wh_DeleteValue(vKey.c_str());
    }
}
struct CyclePendingAction {
    enum Kind { SwitchBlock, SwitchAllow, EndAllow, WipeExited } kind;
    std::wstring displayPath;
    Direction dir = Direction::FullyOffline;
    bool includeChildren = true;
};
static std::vector<CyclePendingAction> g_pendingCycleActions;
static HANDLE g_cycleThread = nullptr;
static std::atomic<bool> g_cycleStopping{false};

static uint64_t UtcNowMs() {
    FILETIME ft{};
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER ui{};
    ui.LowPart = ft.dwLowDateTime;
    ui.HighPart = ft.dwHighDateTime;
    return ui.QuadPart / 10000ULL;
}

static double QpcNowMs() {
    static LARGE_INTEGER freq = []() {
        LARGE_INTEGER f{};
        QueryPerformanceFrequency(&f);
        return f;
    }();
    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    if (freq.QuadPart <= 0) return (double)GetTickCount64();
    return (double)now.QuadPart * 1000.0 / (double)freq.QuadPart;
}

static std::wstring FormatDurationCompact(uint64_t ms) {
    wchar_t buf[64]{};
    if (ms < 1000ULL) {
        swprintf_s(buf, L"%llums", (unsigned long long)ms);
    } else if (ms < 60000ULL) {
        uint64_t sec = (ms + 999ULL) / 1000ULL;
        swprintf_s(buf, L"%llus", (unsigned long long)sec);
    } else if (ms < 3600000ULL) {
        uint64_t totalSec = (ms + 999ULL) / 1000ULL;
        uint64_t m = totalSec / 60ULL;
        uint64_t s = totalSec % 60ULL;
        if (s == 0) swprintf_s(buf, L"%llum", (unsigned long long)m);
        else swprintf_s(buf, L"%llu:%02llu", (unsigned long long)m, (unsigned long long)s);
    } else {
        uint64_t totalSec = (ms + 999ULL) / 1000ULL;
        uint64_t h = totalSec / 3600ULL;
        uint64_t m = (totalSec % 3600ULL) / 60ULL;
        uint64_t s = totalSec % 60ULL;
        swprintf_s(buf, L"%llu:%02llu:%02llu", (unsigned long long)h, (unsigned long long)m, (unsigned long long)s);
    }
    return buf;
}

static bool IsAnyProcessAliveForExe(const std::wstring& lowerExePath) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return true; // fail-open on transient snapshot error
    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);
    bool found = false;
    std::wstring targetName = GetFileNameOnly(lowerExePath);
    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, targetName.c_str()) == 0) {
                std::wstring full = ToLower(QueryProcessExePath(pe.th32ProcessID));
                if (full.empty() || full == lowerExePath) {
                    found = true;
                    break;
                }
            }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    return found;
}

static CycleStatusSnapshot BuildSnapshotLocked(const CycleRuntime& rt, double nowMs) {
    CycleStatusSnapshot snap;
    snap.active = true;
    snap.exePath = rt.exePath;
    snap.displayPath = rt.displayPath;
    snap.direction = rt.cfg.direction;
    snap.phase = rt.phase;
    snap.pausedByFocus = rt.pausedByFocus;
    snap.pausedByUser = rt.pausedByUser;
    snap.completedCycles = rt.completedCycles;
    snap.targetCycles = (rt.cfg.runMode == CycleRunMode::ForCycles) ? rt.cfg.runValue : 0;
    snap.runMode = rt.cfg.runMode;
    snap.focusedOnly = rt.cfg.focusedOnly;
    snap.allowWhenUnfocused = rt.cfg.allowWhenUnfocused;
    snap.blockMs = rt.cfg.blockMs;
    snap.allowMs = rt.cfg.allowMs;

    double effNow = (rt.pausedByFocus || rt.pausedByUser) ? rt.pauseStartMs : nowMs;
    double remPhase = std::max(0.0, rt.phaseTargetMs - effNow);
    snap.phaseRemainingMs = (uint64_t)std::llround(remPhase);

    if (rt.cfg.runMode == CycleRunMode::ForDuration) {
        double remTot = std::max(0.0, rt.totalEndMs - effNow);
        snap.totalRemainingMs = (uint64_t)std::llround(remTot);
    }
    return snap;
}

static void PostCycleUiSync() {
    if (g_hWnd) PostMessageW(g_hWnd, WM_APP_CYCLE_STATE, 0, 0);
}

static bool StartCycleForApp(std::wstring exePath, const CycleConfig& cfg, std::wstring& outErr) {
    std::wstring low = ToLower(Trim(exePath));
    if (low.empty()) {
        outErr = L"No application path provided.";
        return false;
    }
    if (cfg.blockMs < 100 || cfg.allowMs < 100) {
        outErr = L"Minimum phase duration is 100 ms.";
        return false;
    }
    if (cfg.runMode == CycleRunMode::ForCycles && cfg.runValue < 1) {
        outErr = L"Cycle count must be at least 1.";
        return false;
    }
    if (cfg.runMode == CycleRunMode::ForDuration && cfg.runValue < 100) {
        outErr = L"Total duration must be at least 100 ms.";
        return false;
    }
    if (g_excludedExes.count(low)) {
        outErr = L"This app is on your hidden list.";
        return false;
    }
    if (IsImmutableProtectedExe(low)) {
        outErr = L"Core OS & security software is permanently protected.";
        return false;
    }
    if (IsExeOnlyInOtherSessionOrUser(low)) {
        outErr = L"Session 0 / other-user process cannot be cycled.";
        return false;
    }
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        if (!g_settings.enableCycleScheduler) {
            outErr = L"Cycle scheduler is off in Windhawk Settings.";
            return false;
        }
        if (g_settings.lockSystemProcesses && IsCriticalSystemExe(low)) {
            outErr = L"Not allowed on locked system processes.";
            return false;
        }
    }
    auto extFw = GetCachedExternalFirewallBlocks();
    auto itExt = extFw.find(low);
    if (itExt != extFw.end() && itExt->second.dirMask != 0) {
        outErr = L"Windows Firewall already blocks this app, so it can't run on a timer.";
        return false;
    }

    bool incChildren = true;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        incChildren = g_settings.includeChildProcesses;
    }

    bool startUnfocusedAllowed = false;
    {
        std::lock_guard<std::mutex> lk(g_cycleMtx);
        startUnfocusedAllowed = (cfg.focusedOnly && cfg.allowWhenUnfocused && g_cycleFgExe != low);
    }

    // Always starts with Blocked unless focusedOnly + allowWhenUnfocused and app is currently unfocused
    if (!startUnfocusedAllowed) {
        if (!ApplyBlock(exePath, cfg.direction, incChildren, true)) {
            outErr = g_statusBanner.empty() ? L"Failed to apply initial block." : g_statusBanner;
            return false;
        }
    } else {
        bool warnVpn = true;
        {
            std::lock_guard<std::mutex> lk(g_settingsMtx);
            warnVpn = g_settings.warnOnVpnOrRemote;
        }
        if (warnVpn && IsVpnOrRemoteExe(low)) {
            if (!FwConfirm(L"Put a VPN or remote app on a timer?",
                           L"The timer blocks this app on and off, which may cut your VPN or Remote Desktop connection.",
                           L"Start anyway", L"Keep it", true, false)) {
                outErr = L"Cancelled by user.";
                return false;
            }
        }
        ApplyAllow(exePath);
    }

    double nowMs = QpcNowMs();
    {
        std::lock_guard<std::mutex> lk(g_cycleMtx);
        CycleRuntime rt;
        rt.exePath = low;
        rt.displayPath = exePath;
        rt.cfg = cfg;
        rt.phase = CyclePhase::Blocked;
        rt.phaseStartMs = nowMs;
        rt.phaseTargetMs = nowMs + (double)cfg.blockMs;
        rt.totalEndMs = (cfg.runMode == CycleRunMode::ForDuration) ? (nowMs + (double)cfg.runValue) : 0.0;
        rt.completedCycles = 0;
        rt.includeChildren = incChildren;
        rt.lastProcCheckMs = nowMs;
        rt.pausedByUser = false;
        rt.pausedByFocus = (cfg.focusedOnly && g_cycleFgExe != low);
        if (rt.pausedByFocus) rt.pauseStartMs = nowMs;

        g_cycles[low] = std::move(rt);
        g_lastWidgetCycleExe = low;
    }
    bool rememberTpl = true;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        rememberTpl = g_settings.rememberCycleTemplates;
    }
    if (rememberTpl) {
        {
            std::lock_guard<std::mutex> lk(g_cycleMtx);
            g_cycleTemplates[low] = cfg;
        }
        SaveCycleTemplates();
    }
    g_cycleCv.notify_all();
    LogAudit(L"CYCLE START " + exePath + L" (Block " + FormatDurationCompact(cfg.blockMs) +
             L" -> Allow " + FormatDurationCompact(cfg.allowMs) + L")");
    PostCycleUiSync();
    return true;
}

static bool StopCycleForApp(const std::wstring& exePath, bool setAllowed) {
    std::wstring low = ToLower(Trim(exePath));
    std::wstring disp;
    {
        std::lock_guard<std::mutex> lk(g_cycleMtx);
        auto it = g_cycles.find(low);
        if (it == g_cycles.end()) return false;
        disp = it->second.displayPath;
        g_cycles.erase(it);
        if (g_lastWidgetCycleExe == low) g_lastWidgetCycleExe.clear();
    }
    g_cycleCv.notify_all();
    if (setAllowed) {
        ApplyAllow(disp);
    }
    LogAudit(L"CYCLE STOP " + disp);
    PostCycleUiSync();
    return true;
}

static void StopAllCycles(bool setAllowed) {
    std::vector<std::wstring> toAllow;
    {
        std::lock_guard<std::mutex> lk(g_cycleMtx);
        if (g_cycles.empty()) return;
        for (const auto& kv : g_cycles) {
            toAllow.push_back(kv.second.displayPath);
        }
        g_cycles.clear();
        g_lastWidgetCycleExe.clear();
    }
    g_cycleCv.notify_all();
    if (setAllowed) {
        for (const auto& p : toAllow) ApplyAllow(p);
    }
    LogAudit(L"CYCLE STOP ALL");
    PostCycleUiSync();
}

static bool GetCycleSnapshot(const std::wstring& exePath, CycleStatusSnapshot& outSnap) {
    std::wstring low = ToLower(exePath);
    double nowMs = QpcNowMs();
    std::lock_guard<std::mutex> lk(g_cycleMtx);
    auto it = g_cycles.find(low);
    if (it == g_cycles.end()) return false;
    outSnap = BuildSnapshotLocked(it->second, nowMs);
    return true;
}

static bool HasAnyActiveCycle() {
    std::lock_guard<std::mutex> lk(g_cycleMtx);
    return !g_cycles.empty();
}

static bool ToggleCyclePauseForApp(const std::wstring& exePath, bool& outNowPaused) {
    std::wstring low = ToLower(Trim(exePath));
    double nowMs = QpcNowMs();
    std::wstring disp;
    {
        std::lock_guard<std::mutex> lk(g_cycleMtx);
        auto it = g_cycles.find(low);
        if (it == g_cycles.end()) return false;
        CycleRuntime& rt = it->second;
        bool wasPaused = rt.pausedByFocus || rt.pausedByUser;
        rt.pausedByUser = !rt.pausedByUser;
        bool nowPaused = rt.pausedByFocus || rt.pausedByUser;
        if (!wasPaused && nowPaused) {
            rt.pauseStartMs = nowMs;
        } else if (wasPaused && !nowPaused) {
            double pausedDelta = std::max(0.0, nowMs - rt.pauseStartMs);
            rt.phaseStartMs += pausedDelta;
            rt.phaseTargetMs += pausedDelta;
            if (rt.cfg.runMode == CycleRunMode::ForDuration) {
                rt.totalEndMs += pausedDelta;
            }
        }
        outNowPaused = rt.pausedByUser;
        disp = rt.displayPath;
    }
    g_cycleCv.notify_all();
    LogAudit(std::wstring(outNowPaused ? L"CYCLE PAUSE " : L"CYCLE RESUME ") + disp);
    PostCycleUiSync();
    return true;
}

static bool GetWidgetCycleTarget(CycleStatusSnapshot& outSnap) {
    double nowMs = QpcNowMs();
    std::lock_guard<std::mutex> lk(g_cycleMtx);
    if (g_cycles.empty()) return false;
    if (!g_cycleFgExe.empty()) {
        auto itFg = g_cycles.find(g_cycleFgExe);
        if (itFg != g_cycles.end()) {
            outSnap = BuildSnapshotLocked(itFg->second, nowMs);
            return true;
        }
    }
    if (!g_lastWidgetCycleExe.empty()) {
        auto itLast = g_cycles.find(g_lastWidgetCycleExe);
        if (itLast != g_cycles.end()) {
            outSnap = BuildSnapshotLocked(itLast->second, nowMs);
            return true;
        }
    }
    outSnap = BuildSnapshotLocked(g_cycles.begin()->second, nowMs);
    return true;
}

static void NotifyCycleFocusChanged(const std::wstring& fgExeLower) {
    double nowMs = QpcNowMs();
    bool changed = false;
    std::vector<CyclePendingAction> focusActions;
    {
        std::lock_guard<std::mutex> lk(g_cycleMtx);
        if (g_cycleFgExe == fgExeLower) return;
        g_cycleFgExe = fgExeLower;
        if (!fgExeLower.empty() && g_cycles.count(fgExeLower)) {
            g_lastWidgetCycleExe = fgExeLower;
            changed = true;
        }

        for (auto& kv : g_cycles) {
            CycleRuntime& rt = kv.second;
            if (!rt.cfg.focusedOnly) continue;
            bool shouldBeFocused = (rt.exePath == fgExeLower);
            if (!shouldBeFocused && !rt.pausedByFocus) {
                if (!rt.pausedByUser) rt.pauseStartMs = nowMs;
                rt.pausedByFocus = true;
                if (rt.cfg.allowWhenUnfocused && rt.phase == CyclePhase::Blocked) {
                    focusActions.push_back({CyclePendingAction::SwitchAllow, rt.displayPath, rt.cfg.direction, rt.includeChildren});
                }
                changed = true;
            } else if (shouldBeFocused && rt.pausedByFocus) {
                rt.pausedByFocus = false;
                if (!rt.pausedByUser) {
                    double pausedDelta = std::max(0.0, nowMs - rt.pauseStartMs);
                    rt.phaseStartMs += pausedDelta;
                    rt.phaseTargetMs += pausedDelta;
                    if (rt.cfg.runMode == CycleRunMode::ForDuration) {
                        rt.totalEndMs += pausedDelta;
                    }
                }
                if (rt.cfg.allowWhenUnfocused && rt.phase == CyclePhase::Blocked) {
                    focusActions.push_back({CyclePendingAction::SwitchBlock, rt.displayPath, rt.cfg.direction, rt.includeChildren});
                }
                changed = true;
            }
        }
    }
    for (const auto& act : focusActions) {
        if (act.kind == CyclePendingAction::SwitchAllow) {
            ApplyAllow(act.displayPath);
        } else if (act.kind == CyclePendingAction::SwitchBlock) {
            ApplyBlock(act.displayPath, act.dir, act.includeChildren, false);
        }
    }
    if (changed) {
        g_cycleCv.notify_all();
        PostCycleUiSync();
    }
}

static void NotifyCycleSystemResume() {
    double nowMs = QpcNowMs();
    {
        std::lock_guard<std::mutex> lk(g_cycleMtx);
        for (auto& kv : g_cycles) {
            CycleRuntime& rt = kv.second;
            if (rt.pausedByFocus || rt.pausedByUser) {
                double pausedDelta = std::max(0.0, nowMs - rt.pauseStartMs);
                rt.phaseStartMs += pausedDelta;
                rt.phaseTargetMs += pausedDelta;
                if (rt.cfg.runMode == CycleRunMode::ForDuration) rt.totalEndMs += pausedDelta;
                rt.pauseStartMs = nowMs;
            } else if (nowMs > rt.phaseTargetMs) {
                double dur = (double)(rt.phase == CyclePhase::Blocked ? rt.cfg.blockMs : rt.cfg.allowMs);
                if (nowMs - rt.phaseTargetMs >= dur) {
                    rt.phaseStartMs = nowMs;
                    rt.phaseTargetMs = nowMs + dur;
                }
            }
        }
    }
    g_cycleCv.notify_all();
    PostCycleUiSync();
}

static DWORD WINAPI CycleSchedulerThreadProc(LPVOID) {
    while (!g_cycleStopping.load()) {
        std::vector<CyclePendingAction> actions;
        double nextWakeMs = 250.0;

        std::vector<std::wstring> dueProcChecks;
        {
            std::unique_lock<std::mutex> lk(g_cycleMtx);
            if (g_cycles.empty()) {
                g_cycleCv.wait(lk, []() { return g_cycleStopping.load() || !g_cycles.empty(); });
                if (g_cycleStopping.load()) break;
            }
            double nowMs = QpcNowMs();
            for (auto& kv : g_cycles) {
                if (nowMs - kv.second.lastProcCheckMs >= 500.0) {
                    kv.second.lastProcCheckMs = nowMs;
                    dueProcChecks.push_back(kv.first);
                }
            }
        }

        std::unordered_set<std::wstring> deadExes;
        for (const auto& exeLow : dueProcChecks) {
            if (g_cycleStopping.load()) break;
            if (!IsAnyProcessAliveForExe(exeLow)) {
                deadExes.insert(exeLow);
            }
        }

        {
            std::lock_guard<std::mutex> lk(g_cycleMtx);
            if (g_cycleStopping.load()) break;

            double nowMs = QpcNowMs();
            std::vector<std::wstring> toErase;

            for (auto& kv : g_cycles) {
                CycleRuntime& rt = kv.second;

                if (deadExes.count(kv.first)) {
                    actions.push_back({CyclePendingAction::WipeExited, rt.displayPath, rt.cfg.direction, rt.includeChildren});
                    toErase.push_back(kv.first);
                    continue;
                }

                if (rt.pausedByFocus || rt.pausedByUser) {
                    nextWakeMs = std::min(nextWakeMs, 250.0);
                    continue;
                }

                // Check total duration limit (monotonic OR Windows wall-clock target)
                if (rt.cfg.runMode == CycleRunMode::ForDuration &&
                    (nowMs >= rt.totalEndMs || (rt.cfg.targetEndUtcMs > 0 && UtcNowMs() >= rt.cfg.targetEndUtcMs))) {
                    actions.push_back({CyclePendingAction::EndAllow, rt.displayPath, rt.cfg.direction, rt.includeChildren});
                    toErase.push_back(kv.first);
                    continue;
                }

                // Check phase transition
                if (nowMs >= rt.phaseTargetMs) {
                    if (rt.phase == CyclePhase::Blocked) {
                        rt.phase = CyclePhase::Allowed;
                        double allowDur = (double)rt.cfg.allowMs;
                        rt.phaseStartMs = (nowMs - rt.phaseTargetMs < allowDur) ? rt.phaseTargetMs : nowMs;
                        rt.phaseTargetMs = rt.phaseStartMs + allowDur;
                        actions.push_back({CyclePendingAction::SwitchAllow, rt.displayPath, rt.cfg.direction, rt.includeChildren});
                    } else {
                        rt.completedCycles++;
                        if (rt.cfg.runMode == CycleRunMode::ForCycles && rt.completedCycles >= rt.cfg.runValue) {
                            actions.push_back({CyclePendingAction::EndAllow, rt.displayPath, rt.cfg.direction, rt.includeChildren});
                            toErase.push_back(kv.first);
                            continue;
                        }
                        rt.phase = CyclePhase::Blocked;
                        double blockDur = (double)rt.cfg.blockMs;
                        rt.phaseStartMs = (nowMs - rt.phaseTargetMs < blockDur) ? rt.phaseTargetMs : nowMs;
                        rt.phaseTargetMs = rt.phaseStartMs + blockDur;
                        actions.push_back({CyclePendingAction::SwitchBlock, rt.displayPath, rt.cfg.direction, rt.includeChildren});
                    }
                }

                double rem = std::max(5.0, rt.phaseTargetMs - nowMs);
                if (rt.cfg.runMode == CycleRunMode::ForDuration) {
                    rem = std::min(rem, std::max(5.0, rt.totalEndMs - nowMs));
                }
                nextWakeMs = std::min(nextWakeMs, rem);
            }

            for (const auto& k : toErase) {
                g_cycles.erase(k);
            }
        }

        if (!actions.empty()) {
            {
                std::lock_guard<std::mutex> lk(g_cycleMtx);
                g_pendingCycleActions.insert(g_pendingCycleActions.end(),
                                             std::make_move_iterator(actions.begin()),
                                             std::make_move_iterator(actions.end()));
            }
            if (g_hWnd) PostMessageW(g_hWnd, WM_APP_CYCLE_APPLY, 0, 0);
        }

        {
            std::unique_lock<std::mutex> lk(g_cycleMtx);
            if (!g_cycleStopping.load() && !g_cycles.empty()) {
                int waitMs = std::clamp((int)std::floor(nextWakeMs), 5, 250);
                g_cycleCv.wait_for(lk, std::chrono::milliseconds(waitMs), []() { return g_cycleStopping.load(); });
            }
        }
    }
    return 0;
}

static void StartCycleEngine() {
    g_cycleStopping = false;
    if (!g_cycleThread) {
        g_cycleThread = CreateThread(nullptr, 0, CycleSchedulerThreadProc, nullptr, 0, nullptr);
    }
}

static void ShutdownCycleEngine() {
    StopAllCycles(false);
    g_cycleStopping = true;
    g_cycleCv.notify_all();
    if (g_cycleThread) {
        WaitForSingleObject(g_cycleThread, 3000);
        CloseHandle(g_cycleThread);
        g_cycleThread = nullptr;
    }
}

static void RestoreAllSessionBlocks() {
    StopAllCycles(false);
    std::lock_guard<std::mutex> lk(g_engineMtx);
    for (auto it = g_blocks.begin(); it != g_blocks.end();) {
        RemoveWfpFiltersLocked(it->second.sessionFilters);
        it = g_blocks.erase(it);
    }
    LogAudit(L"RESTORE ALL session blocks");
    g_statusBanner = L"All session blocks cleared.";
    TriggerPulse(PulseKind::AllowedGreen);
}

static std::unordered_map<std::wstring, std::pair<Direction, bool>> g_lastAutoBlocked;

static void SyncAutoBlockedApps() {
    std::vector<AutoBlockRuleCfg> rules;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        rules = g_settings.autoBlockedApps;
    }
    std::unordered_map<std::wstring, std::pair<Direction, bool>> nextMap;
    for (const auto& r : rules) {
        if (r.appPath.empty()) continue;
        std::wstring low = ToLower(r.appPath);
        if (g_excludedExes.count(low)) continue;
        if (FileExistsW(r.appPath)) {
            nextMap[low] = {r.direction, r.includeChildProcesses};
        }
    }
    for (const auto& prev : g_lastAutoBlocked) {
        if (!nextMap.count(prev.first)) {
            ApplyAllow(prev.first);
        }
    }
    for (const auto& cur : nextMap) {
        auto itPrev = g_lastAutoBlocked.find(cur.first);
        if (itPrev == g_lastAutoBlocked.end() || itPrev->second != cur.second) {
            ApplyBlock(cur.first, cur.second.first, cur.second.second, false);
        }
    }
    g_lastAutoBlocked = std::move(nextMap);
}

static int CountBlockedApps() {
    std::lock_guard<std::mutex> lk(g_engineMtx);
    int c = 0;
    for (const auto& kv : g_blocks) {
        if (kv.second.blocked) ++c;
    }
    return c;
}

// ============================================================================
// App List Builder
// ============================================================================

static void RefreshAppList() {
    HWND fgWnd = GetForegroundWindow();
    bool isOwnWnd = (fgWnd == g_hWnd) ||
                    (g_hCyclePopup && fgWnd == g_hCyclePopup) ||
                    (g_hCycleWidget && fgWnd == g_hCycleWidget);
    if (!isOwnWnd) {
        if (!fgWnd || IsDesktopOrShellWindow(fgWnd)) {
            g_lastFgExe.clear();
            g_lastFgIsOtherSessionOrUser = false;
        } else {
            DWORD fgPid = 0;
            GetWindowThreadProcessId(fgWnd, &fgPid);
            if (fgPid != GetCurrentProcessId()) {
                std::wstring q = fgPid ? ToLower(QueryProcessExePath(fgPid)) : L"";
                if (!q.empty()) {
                    g_lastFgExe = q;
                    g_lastFgIsOtherSessionOrUser = !IsProcessInCurrentUserSession(fgPid);
                } else {
                    g_lastFgExe.clear();
                    g_lastFgIsOtherSessionOrUser = false;
                }
            }
        }
    }
    std::wstring fgExe = g_lastFgExe;

    EnumWinCtx winCtx;
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&winCtx));
    auto netPids = GetPidsWithLiveNetwork();
    auto snap = CaptureProcessSnapshot();
    auto extFw = ScanExternalFirewallBlocks(false);

    Direction defDir;
    bool lockCritSetting = true;
    bool showNonActionable = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        defDir = g_settings.defaultDirection;
        lockCritSetting = g_settings.lockSystemProcesses;
        showNonActionable = g_settings.showNonActionableInRunning;
    }

    std::unordered_map<std::wstring, AppEntry> mapEntries;
    std::unordered_set<std::wstring> hasCurrentUserPid;
    std::unordered_set<std::wstring> hasOtherSessionPid;

    for (const auto& p : snap) {
        std::wstring low = ToLower(p.exePath);
        if (low.empty()) continue;
        if (p.isCurrentUserSession) hasCurrentUserPid.insert(low);
        else hasOtherSessionPid.insert(low);

        auto& e = mapEntries[low];
        if (e.exePath.empty()) {
            e.exePath = low;
            e.displayPath = p.exePath;
            e.name = GetFileNameOnly(p.exePath);
            e.primaryPid = p.pid;
            e.isSystemApp = IsSystemPath(low);
            e.isImmutableLocked = IsImmutableProtectedExe(low);
            e.isCriticalLocked = IsCriticalSystemExe(low);
            e.isVpnOrRemote = IsVpnOrRemoteExe(low);
            e.isExcluded = g_excludedExes.count(low) > 0;
            e.exeExists = FileExistsW(p.exePath);
            auto itExt = extFw.find(low);
            if (itExt != extFw.end() && itExt->second.dirMask != 0) {
                e.isExternalBlocked = true;
                e.externalBlockMask = itExt->second.dirMask;
                e.externalRuleName = itExt->second.ruleName;
            }
            auto itDir = g_pendingDirs.find(low);
            e.block.direction = (itDir != g_pendingDirs.end()) ? itDir->second : defDir;
        }
        e.pids.push_back(p.pid);
        if (p.isCurrentUserSession) {
            if (low == fgExe) e.isForeground = true;
            if (winCtx.visiblePids.count(p.pid)) e.hasVisibleWindow = true;
            if (netPids.count(p.pid)) e.hasLiveNetwork = true;
        }
    }

    for (auto& kv : mapEntries) {
        kv.second.isOtherSessionOrUser =
            (hasCurrentUserPid.count(kv.first) == 0 && hasOtherSessionPid.count(kv.first) > 0);
    }

    {
        std::lock_guard<std::mutex> lk(g_engineMtx);
        for (const auto& kv : g_blocks) {
            auto& e = mapEntries[kv.first];
            if (e.exePath.empty()) {
                e.exePath = kv.first;
                e.displayPath = kv.first;
                e.name = GetFileNameOnly(kv.first);
                e.isSystemApp = IsSystemPath(kv.first);
                e.isImmutableLocked = IsImmutableProtectedExe(kv.first);
                e.isCriticalLocked = IsCriticalSystemExe(kv.first);
                e.isVpnOrRemote = IsVpnOrRemoteExe(kv.first);
                e.isExcluded = g_excludedExes.count(kv.first) > 0;
                e.exeExists = FileExistsW(kv.first);
            }
            e.block = kv.second;
            for (const auto& chLow : kv.second.blockedChildPaths) {
                auto itCh = mapEntries.find(chLow);
                if (itCh != mapEntries.end() && !itCh->second.block.blocked) {
                    itCh->second.block.blocked = true;
                    itCh->second.block.direction = kv.second.direction;
                }
            }
        }
    }

    if (g_activeFilter == AppFilter::Blocked && g_blockedFirewallOnly) {
        for (const auto& kv : extFw) {
            if ((kv.second.dirMask & 1) == 0) continue;
            if (!mapEntries.count(kv.first)) {
                AppEntry e;
                e.exePath = kv.first;
                e.displayPath = kv.first;
                e.name = GetFileNameOnly(kv.first);
                e.isSystemApp = IsSystemPath(kv.first);
                e.isImmutableLocked = IsImmutableProtectedExe(kv.first);
                e.isCriticalLocked = IsCriticalSystemExe(kv.first);
                e.isVpnOrRemote = IsVpnOrRemoteExe(kv.first);
                e.isExcluded = g_excludedExes.count(kv.first) > 0;
                e.isExternalBlocked = true;
                e.externalBlockMask = kv.second.dirMask;
                e.externalRuleName = kv.second.ruleName;
                mapEntries[kv.first] = std::move(e);
            }
        }
    }

    for (const auto& ex : g_excludedExes) {
        if (!mapEntries.count(ex)) {
            AppEntry e;
            e.exePath = ex;
            e.displayPath = ex;
            e.name = GetFileNameOnly(ex);
            e.isExcluded = true;
            e.isSystemApp = IsSystemPath(ex);
            e.isImmutableLocked = IsImmutableProtectedExe(ex);
            e.isCriticalLocked = IsCriticalSystemExe(ex);
            e.exeExists = FileExistsW(ex);
            mapEntries[ex] = std::move(e);
        }
    }

    std::vector<AppEntry> filtered;
    filtered.reserve(mapEntries.size());

    for (auto& kv : mapEntries) {
        AppEntry& e = kv.second;
        bool isRunning = !e.pids.empty();
        bool isOpenOrNet = e.isForeground || e.hasVisibleWindow || e.hasLiveNetwork;

        if (g_activeFilter == AppFilter::Excluded) {
            if (!e.isExcluded) continue;
        } else if (g_activeFilter == AppFilter::Blocked) {
            if (e.isExcluded) continue;
            if (g_blockedFirewallOnly) {
                if (!e.isExternalBlocked) continue;
            } else {
                if (!e.block.blocked) continue;
            }
        } else {
            if (e.isExcluded) continue;
            bool isLockedEntry = e.isImmutableLocked || e.isOtherSessionOrUser || (e.isCriticalLocked && lockCritSetting);
            bool isNonActionable = e.isExternalBlocked || (!e.block.blocked && isLockedEntry);
            if (g_activeFilter == AppFilter::Allowed) {
                if (isNonActionable || e.isOtherSessionOrUser || e.block.blocked || !isOpenOrNet) continue;
            }
            if (g_activeFilter == AppFilter::UserApps) {
                if (e.isSystemApp || e.isOtherSessionOrUser) continue;
                if (!showNonActionable && isNonActionable) continue;
                if (g_userRunningOnly && !isOpenOrNet && !e.block.blocked) continue;
                if (!g_userRunningOnly && !isRunning && !e.block.blocked) continue;
            }
            if (g_activeFilter == AppFilter::SystemApps) {
                if (e.isExternalBlocked) continue;
                if (!e.isSystemApp || (!isRunning && !e.block.blocked)) continue;
            }
        }

        filtered.push_back(std::move(e));
    }

    std::sort(filtered.begin(), filtered.end(), [lockCritSetting](const AppEntry& a, const AppEntry& b) {
        if (a.isForeground != b.isForeground) return a.isForeground > b.isForeground;
        bool aBlk = a.block.blocked || a.isExternalBlocked;
        bool bBlk = b.block.blocked || b.isExternalBlocked;
        if (aBlk != bBlk) return aBlk > bBlk;
        bool aLocked = !aBlk && (a.isImmutableLocked || a.isOtherSessionOrUser || (a.isCriticalLocked && lockCritSetting));
        bool bLocked = !bBlk && (b.isImmutableLocked || b.isOtherSessionOrUser || (b.isCriticalLocked && lockCritSetting));
        if (aLocked != bLocked) return aLocked < bLocked;
        if (a.hasVisibleWindow != b.hasVisibleWindow) return a.hasVisibleWindow > b.hasVisibleWindow;
        return ToLower(a.name) < ToLower(b.name);
    });

    g_appList = std::move(filtered);
    if (g_appList.empty()) g_kbSelectedIdx = -1;
    else if (g_kbSelectedIdx >= (int)g_appList.size()) g_kbSelectedIdx = (int)g_appList.size() - 1;
}

// ============================================================================
// Icon Cache
// ============================================================================

static HICON GetAppIconCached(const std::wstring& exePath, UINT dpi) {
    std::wstring key = exePath + L"@" + std::to_wstring(dpi);
    auto it = g_iconCache.find(key);
    if (it != g_iconCache.end()) return it->second;

    int sz = DpiScale(20, dpi);
    HICON hIcon = nullptr;
    if (FileExistsW(exePath)) {
        PVOID oldRedir = nullptr;
        BOOL redirDisabled = Wow64DisableWow64FsRedirection(&oldRedir);
        PrivateExtractIconsW(exePath.c_str(), 0, sz, sz, &hIcon, nullptr, 1, 0);
        if (redirDisabled) Wow64RevertWow64FsRedirection(oldRedir);
    }
    if (!hIcon) {
        SHSTOCKICONINFO sii{};
        sii.cbSize = sizeof(sii);
        if (SUCCEEDED(SHGetStockIconInfo(SIID_APPLICATION, SHGSI_ICON | SHGSI_SMALLICON, &sii))) {
            hIcon = sii.hIcon;
        }
    }
    g_iconCache[key] = hIcon;
    return hIcon;
}

static void ClearIconCache() {
    for (auto& kv : g_iconCache) {
        if (kv.second) DestroyIcon(kv.second);
    }
    g_iconCache.clear();
}

// ============================================================================
// Capture Guard & Fullscreen Gate
// ============================================================================

static void ApplyCaptureExclusionToWindow(HWND hwnd) {
    if (!hwnd || !IsWindow(hwnd)) return;
    bool hideCap = true;
    { std::lock_guard<std::mutex> lk(g_settingsMtx); hideCap = g_settings.hideDuringCapture; }
    SetWindowDisplayAffinity(hwnd, hideCap ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE);
}

static void ApplyCaptureExclusionAll() {
    ApplyCaptureExclusionToWindow(g_hWnd);
    ApplyCaptureExclusionToWindow(g_hCycleWidget);
    ApplyCaptureExclusionToWindow(g_hCyclePopup);
}

static bool IsFullscreenActive() {
    QUERY_USER_NOTIFICATION_STATE quns{};
    if (SUCCEEDED(SHQueryUserNotificationState(&quns))) {
        if (quns == QUNS_BUSY || quns == QUNS_RUNNING_D3D_FULL_SCREEN || quns == QUNS_PRESENTATION_MODE) {
            return true;
        }
    }
    HWND fg = GetForegroundWindow();
    if (!fg || fg == g_hWnd) return false;
    HMONITOR mon = MonitorFromWindow(fg, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    if (GetMonitorInfoW(mon, &mi)) {
        RECT rc{};
        if (GetWindowRect(fg, &rc)) {
            if (rc.left <= mi.rcMonitor.left && rc.top <= mi.rcMonitor.top &&
                rc.right >= mi.rcMonitor.right && rc.bottom >= mi.rcMonitor.bottom) {
                wchar_t cls[64]{};
                GetClassNameW(fg, cls, 64);
                if (wcscmp(cls, L"Progman") != 0 && wcscmp(cls, L"WorkerW") != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

// ============================================================================
// Hotkeys & Settings UI
// ============================================================================

struct KeyName {
    UINT vk;
    const wchar_t* name;
};
// Canonical names first; later entries for the same key are accepted aliases.
static const KeyName kKeyNames[] = {
    {VK_SPACE, L"Space"},   {VK_TAB, L"Tab"},         {VK_RETURN, L"Enter"},   {VK_ESCAPE, L"Esc"},
    {VK_INSERT, L"Insert"}, {VK_DELETE, L"Delete"},   {VK_HOME, L"Home"},      {VK_END, L"End"},
    {VK_PRIOR, L"PageUp"},  {VK_NEXT, L"PageDown"},   {VK_UP, L"Up"},          {VK_DOWN, L"Down"},
    {VK_LEFT, L"Left"},     {VK_RIGHT, L"Right"},     {VK_OEM_3, L"`"},        {VK_OEM_MINUS, L"-"},
    {VK_OEM_PLUS, L"="},    {VK_OEM_4, L"["},         {VK_OEM_6, L"]"},        {VK_OEM_5, L"\\"},
    {VK_OEM_1, L";"},       {VK_OEM_7, L"'"},         {VK_OEM_COMMA, L","},    {VK_OEM_PERIOD, L"."},
    {VK_OEM_2, L"/"},       {VK_PAUSE, L"Pause"},     {VK_SNAPSHOT, L"PrintScreen"},
    {VK_RETURN, L"Return"}, {VK_ESCAPE, L"Escape"},   {VK_INSERT, L"Ins"},     {VK_DELETE, L"Del"},
    {VK_PRIOR, L"PgUp"},    {VK_NEXT, L"PgDn"},
};

static UINT KeyFromName(const std::wstring& n) {
    if (n.size() == 1) {
        wchar_t c = (wchar_t)towupper(n[0]);
        if ((c >= L'A' && c <= L'Z') || (c >= L'0' && c <= L'9')) return c;
    }
    if (n.size() >= 2 && (n[0] == L'F' || n[0] == L'f') && iswdigit(n[1])) {
        int f = _wtoi(n.c_str() + 1);
        if (f >= 1 && f <= 24 && std::to_wstring(f) == n.substr(1)) return VK_F1 + f - 1;
        return 0;
    }
    if (n.size() == 7 && !_wcsnicmp(n.c_str(), L"Numpad", 6) && iswdigit(n[6])) return VK_NUMPAD0 + (n[6] - L'0');
    for (const auto& k : kKeyNames)
        if (!_wcsicmp(n.c_str(), k.name)) return k.vk;
    return 0;
}

bool Hotkey_Parse(const std::wstring& text, UINT& mods, UINT& vk) {
    mods = 0;
    vk = 0;
    std::vector<std::wstring> parts;
    size_t start = 0;
    while (true) {
        size_t plus = text.find(L'+', start);
        parts.push_back(Trim(text.substr(start, plus == std::wstring::npos ? std::wstring::npos : plus - start)));
        if (plus == std::wstring::npos) break;
        start = plus + 1;
    }
    for (size_t i = 0; i + 1 < parts.size(); i++) {
        const wchar_t* p = parts[i].c_str();
        if (!_wcsicmp(p, L"Ctrl") || !_wcsicmp(p, L"Control")) mods |= MOD_CONTROL;
        else if (!_wcsicmp(p, L"Alt")) mods |= MOD_ALT;
        else if (!_wcsicmp(p, L"Shift")) mods |= MOD_SHIFT;
        else if (!_wcsicmp(p, L"Win") || !_wcsicmp(p, L"Windows")) mods |= MOD_WIN;
        else return (mods = 0), false;
    }
    vk = parts.back().empty() ? 0 : KeyFromName(parts.back());
    if (!vk) mods = 0;
    return vk != 0;
}

std::wstring Hotkey_Format(UINT mods, UINT vk) {
    std::wstring key;
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) key = std::wstring(1, (wchar_t)vk);
    else if (vk >= VK_F1 && vk <= VK_F24) key = L"F" + std::to_wstring(vk - VK_F1 + 1);
    else if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) key = L"Numpad" + std::to_wstring(vk - VK_NUMPAD0);
    else
        for (const auto& k : kKeyNames)
            if (k.vk == vk) {
                key = k.name;
                break;
            }
    if (key.empty()) return {};
    std::wstring out;
    if (mods & MOD_CONTROL) out += L"Ctrl+";
    if (mods & MOD_ALT) out += L"Alt+";
    if (mods & MOD_SHIFT) out += L"Shift+";
    if (mods & MOD_WIN) out += L"Win+";
    return out + key;
}

// An empty box means no shortcut.
static HotkeyBinding ParseHotkeyString(PCWSTR str) {
    HotkeyBinding hb;
    if (!str || !*str) return hb;
    hb.raw = str;
    UINT mods = 0, vk = 0;
    if (!Hotkey_Parse(str, mods, vk)) return hb;
    hb.modifiers = mods | MOD_NOREPEAT;
    hb.vk = vk;
    return hb;
}

static void RegisterAllHotkeys(HWND hwnd) {
    for (int id = 1; id <= 3; ++id) UnregisterHotKey(hwnd, id);
    ModSettings s;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        s = g_settings;
    }
    auto reg = [&](int id, const HotkeyBinding& hb, const wchar_t* label) {
        if (hb.vk == 0) return;
        if (!RegisterHotKey(hwnd, id, hb.modifiers, hb.vk)) {
            Wh_Log(L"Hotkey conflict: %s (%s) already in use.", label, hb.raw.c_str());
        }
    };
    reg(HK_TOGGLE_FG, s.hkToggleFg, L"toggleForegroundApp");
    reg(HK_EXPAND_PILL, s.hkExpandPill, L"expandCollapsePill");
    reg(HK_RESTORE_ALL, s.hkRestoreAll, L"restoreAll");
}

static void OpenWindhawkSettingsUI() {
    swfset::OpenSettingsWindow();
}

static void LoadSettings() {
    ModSettings next;

    auto sDir = WindhawkUtils::StringSetting::make(L"defaultDirection");
    next.defaultDirection = ParseDirection(sDir.get());

    next.includeChildProcesses = Wh_GetIntSetting(L"includeChildProcesses") != 0;

    auto sEdge = WindhawkUtils::StringSetting::make(L"dockEdge");
    {
        std::wstring e = ToLower(sEdge.get());
        if (e == L"left") next.dockEdge = DockEdge::Left;
        else if (e == L"top") next.dockEdge = DockEdge::Top;
        else if (e == L"bottom") next.dockEdge = DockEdge::Bottom;
        else if (e == L"top_left") next.dockEdge = DockEdge::TopLeft;
        else if (e == L"bottom_left") next.dockEdge = DockEdge::BottomLeft;
        else if (e == L"bottom_right") next.dockEdge = DockEdge::BottomRight;
        else next.dockEdge = DockEdge::Right;
    }

    auto sInd = WindhawkUtils::StringSetting::make(L"pillIndicatorMode");
    next.pillIndicatorMode = (ToLower(sInd.get()) == L"pulse") ? PillIndicatorMode::Pulse : PillIndicatorMode::Always;

    next.hoverExpand = Wh_GetIntSetting(L"hoverExpand") != 0;
    next.expandHoverHitArea = Wh_GetIntSetting(L"expandHoverHitArea") != 0;
    int rawMargin = Wh_GetIntSetting(L"hoverHitMarginPx");
    next.hoverHitMarginPx = (rawMargin > 0) ? std::clamp(rawMargin, 4, 40) : 12;
    int rawOffset = Wh_GetIntSetting(L"panelEdgeOffsetPx");
    next.panelEdgeOffsetPx = (rawOffset >= 0) ? std::clamp(rawOffset, 0, 12) : 8;

    auto sFilter = WindhawkUtils::StringSetting::make(L"defaultFilter");
    {
        std::wstring f = ToLower(sFilter.get());
        if (f == L"blocked") next.defaultFilter = AppFilter::Blocked;
        else if (f == L"allowed") next.defaultFilter = AppFilter::Allowed;
        else if (f == L"system") next.defaultFilter = AppFilter::SystemApps;
        else if (f == L"excluded") next.defaultFilter = AppFilter::Excluded;
        else next.defaultFilter = AppFilter::UserApps;
    }

    next.showNonActionableInRunning = Wh_GetIntSetting(L"showNonActionableInRunning") != 0;
    next.showTooltips = Wh_GetIntSetting(L"showTooltips") != 0;
    next.followCursorMonitor = Wh_GetIntSetting(L"followCursorMonitor") != 0;
    next.rememberWindowPosition = Wh_GetIntSetting(L"rememberWindowPosition") != 0;

    auto sPreset = WindhawkUtils::StringSetting::make(L"windowSizePreset");
    {
        std::wstring p = ToLower(sPreset.get());
        if (p == L"large") next.windowSizePreset = SizePreset::Large;
        else if (p == L"extralarge") next.windowSizePreset = SizePreset::ExtraLarge;
        else next.windowSizePreset = SizePreset::Default;
    }

    next.flyoutAnimation = Wh_GetIntSetting(L"flyoutAnimation") != 0;
    {
        auto sSpeed = WindhawkUtils::StringSetting::make(L"animationSpeed");
        std::wstring v = ToLower(sSpeed.get());
        next.animationSpeed = v == L"veryquick" ? 1 : v == L"quick" ? 2 : v == L"normal" ? 3
                            : v == L"relaxed"   ? 4 : v == L"slow"  ? 5 : 0;
    }

    auto sFs = WindhawkUtils::StringSetting::make(L"fullscreenBehavior");
    {
        std::wstring v = ToLower(sFs.get());
        next.fullscreenBehavior = (v == L"allow") ? FullscreenBehavior::Allow : FullscreenBehavior::Hide;
    }

    next.hideDuringCapture = Wh_GetIntSetting(L"hideDuringCapture") != 0;
    next.enableCycleScheduler = Wh_GetIntSetting(L"enableCycleScheduler") != 0;
    next.rememberCycleTemplates = Wh_GetIntSetting(L"rememberCycleTemplates") != 0;
    next.showCycleMs = Wh_GetIntSetting(L"showCycleMs") != 0;
    next.showCycleWidget = Wh_GetIntSetting(L"showCycleWidget") != 0;
    next.cycleWidgetSize = std::clamp(Wh_GetIntSetting(L"cycleWidgetSize"), 0, 10);
    auto sCycAct = WindhawkUtils::StringSetting::make(L"cycleWidgetAction");
    next.cycleWidgetAction = (_wcsicmp(sCycAct.get(), L"navigate_pill") == 0)
        ? CycleWidgetAction::NavigatePill
        : CycleWidgetAction::SchedulerOnly;

    next.lockSystemProcesses = Wh_GetIntSetting(L"lockSystemProcesses") != 0;
    next.warnOnVpnOrRemote = Wh_GetIntSetting(L"warnOnVpnOrRemote") != 0;
    next.replaceFirewallPrompt = Wh_GetIntSetting(L"replaceFirewallPrompt") != 0;
    next.allowOnPublicNetworks = Wh_GetIntSetting(L"allowOnPublicNetworks") != 0;
    next.contextMenu = Wh_GetIntSetting(L"contextMenu") != 0;

    auto readHk = [&](PCWSTR key) {
        auto raw = WindhawkUtils::StringSetting::make(key);
        return ParseHotkeyString(raw.get());
    };
    next.hkToggleFg   = readHk(L"toggleForegroundApp");
    next.hkExpandPill = readHk(L"expandCollapsePill");
    next.hkRestoreAll = readHk(L"restoreAll");

    // No edge pill, no hover reveal, no clock button beside the pill (owner, 2026-11-24).
    next.showPill = false;
    next.hoverExpand = false;
    next.expandHoverHitArea = false;
    next.showCycleWidget = false;
    next.followCursorMonitor = false;
    next.rememberWindowPosition = false;
    next.cycleWidgetAction = CycleWidgetAction::SchedulerOnly;
    next.fullscreenBehavior = FullscreenBehavior::Allow;
    next.trayIcon = Wh_GetIntSetting(L"settingsTrayIcon") != 0;

    for (int i = 0; i < 64; ++i) {
        auto app = WindhawkUtils::StringSetting::make(L"autoBlockedApps[%d].appPath", i);
        if (!*app.get()) break;
        AutoBlockRuleCfg r;
        r.appPath = app.get();
        auto dir = WindhawkUtils::StringSetting::make(L"autoBlockedApps[%d].direction", i);
        r.direction = ParseDirection(dir.get());
        r.includeChildProcesses = Wh_GetIntSetting(L"autoBlockedApps[%d].includeChildProcesses", i) != 0;
        next.autoBlockedApps.push_back(std::move(r));
    }

    int settingEdgeInt = (int)next.dockEdge;
    if (g_lastSettingDockEdge == -1) {
        int ov = Wh_GetIntValue(L"dockEdgeOverride", -1);
        if (ov >= 0 && ov <= 6) next.dockEdge = (DockEdge)ov;
    } else if (settingEdgeInt != g_lastSettingDockEdge) {
        Wh_SetIntValue(L"dockEdgeOverride", settingEdgeInt);
    } else {
        int ov = Wh_GetIntValue(L"dockEdgeOverride", -1);
        if (ov >= 0 && ov <= 6) next.dockEdge = (DockEdge)ov;
    }
    g_lastSettingDockEdge = settingEdgeInt;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        g_settings = std::move(next);
        g_activeFilter = g_settings.defaultFilter;
        if (g_activeFilter == AppFilter::SystemApps) {
            g_statusBanner = L"System apps are for experts. Leave them alone unless you know what each one does.";
        }
    }
}

// ============================================================================
// Rounded Geometry, Clean Pill Frame, Crisp Rendering
// ============================================================================

static void AddRoundedRectPath(Gdiplus::GraphicsPath& path, Gdiplus::REAL x, Gdiplus::REAL y,
                               Gdiplus::REAL w, Gdiplus::REAL h, Gdiplus::REAL r) {
    Gdiplus::REAL d = std::min(r * 2.0f, std::min(w, h));
    if (d <= 0.5f) {
        path.AddRectangle(Gdiplus::RectF(x, y, w, h));
        return;
    }
    path.AddArc(x, y, d, d, 180.0f, 90.0f);
    path.AddArc(x + w - d, y, d, d, 270.0f, 90.0f);
    path.AddArc(x + w - d, y + h - d, d, d, 0.0f, 90.0f);
    path.AddArc(x, y + h - d, d, d, 90.0f, 90.0f);
    path.CloseFigure();
}

static void FillRoundedRect(Gdiplus::Graphics& g, const Gdiplus::Brush& br,
                            Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL w, Gdiplus::REAL h, Gdiplus::REAL r) {
    Gdiplus::GraphicsPath path;
    AddRoundedRectPath(path, x, y, w, h, r);
    g.FillPath(&br, &path);
}

static void DrawRoundedRect(Gdiplus::Graphics& g, const Gdiplus::Pen& pen,
                            Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL w, Gdiplus::REAL h, Gdiplus::REAL r) {
    Gdiplus::GraphicsPath path;
    AddRoundedRectPath(path, x, y, w, h, r);
    g.DrawPath(&pen, &path);
}

// ---------------------------------------------------------------------------
// Mocha look: palette, glass and edge helpers shared by the panel, pill and popups.
// ---------------------------------------------------------------------------
namespace fwc {
constexpr DWORD base = 0x1E1E2E, mantle = 0x181825, crust = 0x11111B;
constexpr DWORD surface0 = 0x313244, surface1 = 0x45475A, surface2 = 0x585B70;
constexpr DWORD overlay0 = 0x6C7086, overlay2 = 0x9399B2;
constexpr DWORD subtext0 = 0xA6ADC8, subtext1 = 0xBAC2DE, text = 0xCDD6F4;
constexpr DWORD blue = 0x89B4FA, mauve = 0xCBA6F7, green = 0xA6E3A1, red = 0xF38BA8;
constexpr DWORD yellow = 0xF9E2AF, peach = 0xFAB387;
}  // namespace fwc

static Gdiplus::Color Moc(DWORD rgb, double a = 1.0) {
    return Gdiplus::Color((BYTE)std::clamp((int)std::lround(a * 255.0), 0, 255), (BYTE)(rgb >> 16),
                          (BYTE)(rgb >> 8), (BYTE)rgb);
}

static DWORD MocMix(DWORD a, DWORD b, double t) {
    t = std::clamp(t, 0.0, 1.0);
    auto ch = [&](int s) {
        int x = (int)((a >> s) & 0xFF), y = (int)((b >> s) & 0xFF);
        return (DWORD)std::clamp((int)std::lround(x + (y - x) * t), 0, 255) << s;
    };
    return ch(16) | ch(8) | ch(0);
}

static COLORREF MocRef(DWORD rgb) {
    return RGB((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

static const wchar_t* FwTextFace() {
    static int ok = -1;
    if (ok < 0) {
        Gdiplus::FontFamily ff(L"FiraCode Nerd Font");
        ok = ff.IsAvailable() ? 1 : 0;
    }
    return ok ? L"FiraCode Nerd Font" : L"Segoe UI";
}

static const wchar_t* FwIconFace() {
    static int ok = -1;
    if (ok < 0) {
        Gdiplus::FontFamily ff(L"Segoe Fluent Icons");
        ok = ff.IsAvailable() ? 1 : 0;
    }
    return ok ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
}

static void FwRound(Gdiplus::Graphics& g, Gdiplus::Color c, Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL w,
                    Gdiplus::REAL h, Gdiplus::REAL r) {
    Gdiplus::SolidBrush br(c);
    FillRoundedRect(g, br, x, y, w, h, r);
}

// A stroke of width sw sits sw/2 inside the shape, on radius r - sw/2, so it never shaves.
static void FwEdge(Gdiplus::Graphics& g, Gdiplus::Color c, Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL w,
                   Gdiplus::REAL h, Gdiplus::REAL r, Gdiplus::REAL sw) {
    Gdiplus::Pen pen(c, sw);
    Gdiplus::REAL i = sw * 0.5f;
    DrawRoundedRect(g, pen, x + i, y + i, w - sw, h - sw, std::max(0.0f, r - i));
}

static void FwGradBrushInit(Gdiplus::LinearGradientBrush*& out, Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL w,
                            Gdiplus::REAL h, double a) {
    out = new Gdiplus::LinearGradientBrush(Gdiplus::RectF(x, y, std::max(1.0f, w), std::max(1.0f, h)),
                                           Moc(fwc::blue, a), Moc(fwc::mauve, a),
                                           Gdiplus::LinearGradientModeForwardDiagonal);
    out->SetWrapMode(Gdiplus::WrapModeTileFlipXY);
}

static void FwGradFill(Gdiplus::Graphics& g, Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL w, Gdiplus::REAL h,
                       Gdiplus::REAL r, double a = 1.0) {
    Gdiplus::LinearGradientBrush* br = nullptr;
    FwGradBrushInit(br, x, y, w, h, a);
    FillRoundedRect(g, *br, x, y, w, h, r);
    delete br;
}

static void FwGradEdge(Gdiplus::Graphics& g, Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL w, Gdiplus::REAL h,
                       Gdiplus::REAL r, Gdiplus::REAL sw, double a = 1.0) {
    Gdiplus::LinearGradientBrush* br = nullptr;
    FwGradBrushInit(br, x, y, w, h, a);
    Gdiplus::Pen pen(br, sw);
    Gdiplus::REAL i = sw * 0.5f;
    DrawRoundedRect(g, pen, x + i, y + i, w - sw, h - sw, std::max(0.0f, r - i));
    delete br;
}

// The live window corner radius from the corner-radius mod (8 when it is off), in 96-dpi pixels.
static int PanelCornerRadius() {
    int radius = 8;
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0,
                      KEY_READ | KEY_WOW64_64KEY, &key) == ERROR_SUCCESS) {
        DWORD disabled = 0, size = sizeof(disabled);
        bool off = RegQueryValueExW(key, L"Disabled", nullptr, nullptr, (BYTE*)&disabled, &size) == ERROR_SUCCESS &&
                   disabled;
        DWORD value = 0;
        size = sizeof(value);
        if (!off && RegGetValueW(key, L"Settings", L"radius", RRF_RT_REG_DWORD, nullptr, &value, &size) ==
                        ERROR_SUCCESS &&
            value > 0 && value <= 64)
            radius = (int)value;
        RegCloseKey(key);
    }
    return radius;
}

// Windows' own "Transparency effects" switch. Off means the panel is solid Mocha.
static bool TransparencyOn() {
    DWORD v = 1, size = sizeof(v);
    if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                     L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &v, &size) != ERROR_SUCCESS)
        return true;
    return v != 0;
}

// The settings window's glass (frosted like Explorer) on the open panel; nothing on the pill.
static void ApplyPanelGlass(HWND hwnd, bool on) {
    if (!hwnd) return;
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: the panel draws its own edge.
    DwmSetWindowAttribute(hwnd, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
    if (on) {
        int backdrop = 1;  // DWMSBT_NONE
        DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
    }
    DWM_BLURBEHIND bb{};
    bb.dwFlags = DWM_BB_ENABLE | (on ? DWM_BB_BLURREGION : 0);
    bb.fEnable = on ? TRUE : FALSE;
    bb.hRgnBlur = on ? CreateRectRgn(0, 0, -1, -1) : nullptr;
    DwmEnableBlurBehindWindow(hwnd, &bb);
    if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
    struct FwAccentPolicy { int state, flags, abgr, animation; };
    struct FwCompositionData { DWORD attribute; void* data; SIZE_T size; };
    using FwSetComposition_t = BOOL(WINAPI*)(HWND, FwCompositionData*);
    if (auto setComposition = (FwSetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"),
                                                                        "SetWindowCompositionAttribute")) {
        FwAccentPolicy policy = on ? FwAccentPolicy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0}
                                   : FwAccentPolicy{0, 0, 0, 0};
        FwCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
        setComposition(hwnd, &data);
    }
}

// Open and close motion for the panel and the boxes. The mod's own switch, the switch every
// DavidHiFi mod follows (HKCU\Software\DavidHiFi\Motion, written by Seamless Workshop) and
// Windows "Animation effects" all have to allow it. scale stretches the time: 2 = twice as long.
static bool FwMotion(double* scale) {
    bool modOn = true;
    int level = 0;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        modOn = g_settings.flyoutAnimation;
        level = g_settings.animationSpeed;
    }
    static constexpr double kLevels[] = {1.0, 0.5, 0.75, 1.0, 1.5, 2.0};
    bool globalOn = true;
    double globalScale = 1.0;
    HKEY key = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\DavidHiFi\\Motion", 0, KEY_QUERY_VALUE, &key) ==
        ERROR_SUCCESS) {
        DWORD value = 0, type = 0, size = sizeof(value);
        if (RegQueryValueExW(key, L"Enabled", nullptr, &type, (BYTE*)&value, &size) == ERROR_SUCCESS &&
            type == REG_DWORD)
            globalOn = value != 0;
        WCHAR text[32] = {};
        size = sizeof(text) - sizeof(WCHAR);
        if (RegQueryValueExW(key, L"Speed", nullptr, &type, (BYTE*)text, &size) == ERROR_SUCCESS) {
            if (type == REG_DWORD) {
                globalScale = std::clamp((double)*(DWORD*)text, 25.0, 400.0) / 100.0;
            } else if (type == REG_SZ) {
                static const wchar_t* kNames[] = {L"", L"veryQuick", L"quick", L"normal", L"relaxed", L"slow"};
                for (int i = 1; i < 6; i++)
                    if (_wcsicmp(text, kNames[i]) == 0) globalScale = kLevels[i];
            }
        }
        RegCloseKey(key);
    }
    if (scale) *scale = (level > 0 && level < 6) ? kLevels[level] : globalScale;
    BOOL anim = TRUE;
    if (!SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &anim, 0)) anim = TRUE;
    return modOn && globalOn && anim;
}

static double FwNowMs() {
    static LARGE_INTEGER freq{};
    if (!freq.QuadPart) QueryPerformanceFrequency(&freq);
    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    return (double)now.QuadPart * 1000.0 / (double)freq.QuadPart;
}

// A top-down 32-bit premultiplied drawing surface with its own DC (for icons and clipping).
struct FwLayer {
    HDC dc = nullptr;
    HBITMAP bmp = nullptr;
    HGDIOBJ old = nullptr;
    void* bits = nullptr;
    int w = 0, h = 0;
    bool Make(HDC ref, int cw, int ch) {
        w = cw;
        h = ch;
        dc = CreateCompatibleDC(ref);
        BITMAPINFO bmi{};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = cw;
        bmi.bmiHeader.biHeight = -ch;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmp = CreateDIBSection(ref, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!dc || !bmp || !bits) return false;
        old = SelectObject(dc, bmp);
        memset(bits, 0, (size_t)cw * (size_t)ch * 4);
        return true;
    }
    ~FwLayer() {
        if (dc && old) SelectObject(dc, old);
        if (bmp) DeleteObject(bmp);
        if (dc) DeleteDC(dc);
    }
};

// ---------------------------------------------------------------------------
// The Mocha yes/no box: frosted glass, one 2px window edge, the panel's buttons.
// Enter or Space picks the focused button, Esc or N says no, Y says yes, Tab and
// the arrow keys move between the two.
// ---------------------------------------------------------------------------
constexpr wchar_t kConfirmClass[] = L"SeamlessFirewall_Confirm_v1";
constexpr UINT_PTR TIMER_CONFIRM_FADE = 90;

struct FwConfirmState {
    std::wstring title, body, yes, no;
    bool danger = false, question = false, glass = false;
    bool inside = false, tracking = false, done = false, result = false;
    int hover = 0;  // 1 = no button, 2 = yes button
    int focus = 2;
    RECT rcNo{}, rcYes{};
    int bodyTop = 0, bodyH = 0;
    DWORD openTick = 0;
    // A box that does not wait (the connection request) posts doneMsg to doneTo with the
    // answer in wParam and its own window in lParam instead of ending a message loop.
    HWND doneTo = nullptr;
    UINT doneMsg = 0;
    // Open and close motion: a solid frame fades and slides while the window is layered.
    // Once the open settles the layer goes and the glass comes on (a layered window
    // only shows a flat blur); the close switches the glass off again first.
    bool settled = false, closing = false;
    double animStart = 0.0, animMs = 0.0, vis = 0.0, closeFrom = 1.0;
    int finalX = 0, finalY = 0, slidePx = 0;
};
static FwConfirmState* g_confirm = nullptr;

static int FwConfirmHit(const FwConfirmState* st, POINT pt) {
    if (PtInRect(&st->rcYes, pt)) return 2;
    if (PtInRect(&st->rcNo, pt)) return 1;
    return 0;
}

static SIZE FwConfirmLayout(HWND hwnd, FwConfirmState* st) {
    UINT dpi = GetDpiForWindow(hwnd);
    int pad = DpiScale(20, dpi);
    int w = DpiScale(380, dpi);
    int textX = pad + DpiScale(34, dpi);
    const wchar_t* face = FwTextFace();
    Gdiplus::Font bodyFont(face, (Gdiplus::REAL)DpiScale(12, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    Gdiplus::Font btnFont(face, (Gdiplus::REAL)DpiScale(12, dpi), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    HDC dc = GetDC(hwnd);
    Gdiplus::RectF bodyBox, yesBox, noBox;
    {
        Gdiplus::Graphics g(dc);
        g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
        Gdiplus::RectF lay(0, 0, (Gdiplus::REAL)(w - textX - pad), 4000.0f);
        g.MeasureString(st->body.c_str(), -1, &bodyFont, lay, &bodyBox);
        Gdiplus::PointF o(0, 0);
        g.MeasureString(st->yes.c_str(), -1, &btnFont, o, &yesBox);
        g.MeasureString(st->no.c_str(), -1, &btnFont, o, &noBox);
    }
    ReleaseDC(hwnd, dc);
    st->bodyTop = pad + DpiScale(24, dpi);
    st->bodyH = (int)std::ceil(bodyBox.Height) + DpiScale(2, dpi);
    int btnTop = st->bodyTop + st->bodyH + DpiScale(20, dpi);
    int btnH = DpiScale(32, dpi);
    int minW = DpiScale(88, dpi), side = DpiScale(18, dpi), gap = DpiScale(8, dpi);
    int yesW = std::max(minW, (int)std::ceil(yesBox.Width) + 2 * side);
    int noW = std::max(minW, (int)std::ceil(noBox.Width) + 2 * side);
    st->rcYes = RECT{w - pad - yesW, btnTop, w - pad, btnTop + btnH};
    st->rcNo = RECT{st->rcYes.left - gap - noW, btnTop, st->rcYes.left - gap, btnTop + btnH};
    return SIZE{w, btnTop + btnH + pad};
}

static void FwConfirmPaint(HWND hwnd, FwConfirmState* st) {
    PAINTSTRUCT ps{};
    HDC hdc = BeginPaint(hwnd, &ps);
    RECT rc{};
    GetClientRect(hwnd, &rc);
    int w = rc.right, h = rc.bottom;
    FwLayer layer;
    if (w > 0 && h > 0 && st && layer.Make(hdc, w, h)) {
        UINT dpi = GetDpiForWindow(hwnd);
        Gdiplus::Bitmap canvas(w, h, w * 4, PixelFormat32bppPARGB, (BYTE*)layer.bits);
        Gdiplus::Graphics g(&canvas);
        g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
        g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
        g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

        // Frosted Mocha while the glass is on, solid Mocha otherwise. The box always sits on the
        // dark panel, so its fill is lighter than the panel's or the colour under it never moves.
        g.Clear(Moc(fwc::base, st->glass ? 0.40 : 1.0));
        Gdiplus::REAL winR = (Gdiplus::REAL)DpiScale(PanelCornerRadius(), dpi);
        Gdiplus::REAL ew = (Gdiplus::REAL)std::max(2, DpiScale(2, dpi));
        if (st->inside)
            FwGradEdge(g, 0, 0, (Gdiplus::REAL)w, (Gdiplus::REAL)h, winR, ew);
        else
            FwEdge(g, Moc(fwc::surface2), 0, 0, (Gdiplus::REAL)w, (Gdiplus::REAL)h, winR, ew);

        const wchar_t* face = FwTextFace();
        Gdiplus::Font titleFont(face, (Gdiplus::REAL)DpiScale(15, dpi), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::Font bodyFont(face, (Gdiplus::REAL)DpiScale(12, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
        Gdiplus::Font btnFont(face, (Gdiplus::REAL)DpiScale(12, dpi), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::Font iconFont(FwIconFace(), (Gdiplus::REAL)DpiScale(18, dpi), Gdiplus::FontStyleRegular,
                               Gdiplus::UnitPixel);
        Gdiplus::SolidBrush textBr(Moc(fwc::text)), subBr(Moc(fwc::subtext1)), crustBr(Moc(fwc::crust));
        Gdiplus::SolidBrush iconBr(Moc(st->question ? fwc::blue : fwc::peach));
        Gdiplus::StringFormat sfCenter, sfLeft;
        sfCenter.SetAlignment(Gdiplus::StringAlignmentCenter);
        sfCenter.SetLineAlignment(Gdiplus::StringAlignmentCenter);
        sfLeft.SetLineAlignment(Gdiplus::StringAlignmentCenter);
        sfLeft.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);
        sfLeft.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

        int pad = DpiScale(20, dpi);
        int textX = pad + DpiScale(34, dpi);
        Gdiplus::RectF iconRf((Gdiplus::REAL)pad, (Gdiplus::REAL)pad, (Gdiplus::REAL)DpiScale(24, dpi),
                              (Gdiplus::REAL)DpiScale(24, dpi));
        g.DrawString(st->question ? L"\xE9CE" : L"\xE7BA", -1, &iconFont, iconRf, &sfCenter, &iconBr);
        Gdiplus::RectF titleRf((Gdiplus::REAL)textX, (Gdiplus::REAL)pad, (Gdiplus::REAL)(w - textX - pad),
                               (Gdiplus::REAL)DpiScale(24, dpi));
        g.DrawString(st->title.c_str(), -1, &titleFont, titleRf, &sfLeft, &textBr);
        Gdiplus::RectF bodyRf((Gdiplus::REAL)textX, (Gdiplus::REAL)st->bodyTop, (Gdiplus::REAL)(w - textX - pad),
                              (Gdiplus::REAL)st->bodyH);
        g.DrawString(st->body.c_str(), -1, &bodyFont, bodyRf, nullptr, &subBr);

        Gdiplus::REAL rad = (Gdiplus::REAL)DpiScale(8, dpi);
        Gdiplus::REAL ew2 = (Gdiplus::REAL)std::max(2, DpiScale(2, dpi));
        auto rf = [](const RECT& r) {
            return Gdiplus::RectF((Gdiplus::REAL)r.left, (Gdiplus::REAL)r.top, (Gdiplus::REAL)(r.right - r.left),
                                  (Gdiplus::REAL)(r.bottom - r.top));
        };
        // "No": Mocha surface with one 2px edge, grey at rest, blue to mauve on hover or focus.
        {
            Gdiplus::RectF r = rf(st->rcNo);
            bool lit = st->hover == 1 || st->focus == 1;
            FwRound(g, Moc(st->hover == 1 ? fwc::surface1 : fwc::surface0, 0.85), r.X, r.Y, r.Width, r.Height, rad);
            if (lit) FwGradEdge(g, r.X, r.Y, r.Width, r.Height, rad, ew2);
            else FwEdge(g, Moc(fwc::surface2), r.X, r.Y, r.Width, r.Height, rad, ew2);
            g.DrawString(st->no.c_str(), -1, &btnFont, r, &sfCenter, lit ? &textBr : &subBr);
        }
        // "Yes": red when it cuts something off, the accent gradient otherwise; hover lifts it,
        // focus draws a light 2px ring inside it.
        {
            Gdiplus::RectF r = rf(st->rcYes);
            if (st->danger) FwRound(g, Moc(fwc::red), r.X, r.Y, r.Width, r.Height, rad);
            else FwGradFill(g, r.X, r.Y, r.Width, r.Height, rad);
            if (st->hover == 2) FwRound(g, Moc(fwc::text, 0.14), r.X, r.Y, r.Width, r.Height, rad);
            if (st->focus == 2) FwEdge(g, Moc(fwc::text, 0.85), r.X, r.Y, r.Width, r.Height, rad, ew2);
            g.DrawString(st->yes.c_str(), -1, &btnFont, r, &sfCenter, &crustBr);
        }
        BitBlt(hdc, 0, 0, w, h, layer.dc, 0, 0, SRCCOPY);
    }
    EndPaint(hwnd, &ps);
}

// The open has settled: drop the layer so DWM blurs behind the box, and draw the glass.
static void FwBoxSettle(HWND hwnd, FwConfirmState* st) {
    if (!st || st->settled || st->closing) return;
    KillTimer(hwnd, TIMER_CONFIRM_FADE);
    st->settled = true;
    st->vis = 1.0;
    SetWindowPos(hwnd, nullptr, st->finalX, st->finalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    LONG_PTR ex = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    if (ex & WS_EX_LAYERED) SetWindowLongPtrW(hwnd, GWL_EXSTYLE, ex & ~WS_EX_LAYERED);
    bool glass = TransparencyOn();
    ApplyPanelGlass(hwnd, glass);
    st->glass = glass;
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
}

// The box has its final place and size and is not shown yet.
static void FwBoxStartOpen(HWND hwnd, FwConfirmState* st, int x, int y) {
    st->finalX = x;
    st->finalY = y;
    st->openTick = GetTickCount();
    double scale = 1.0;
    if (!FwMotion(&scale)) {
        FwBoxSettle(hwnd, st);
        return;
    }
    st->slidePx = MulDiv(8, (int)GetDpiForWindow(hwnd), 96);
    st->animMs = 160.0 * scale;
    st->animStart = 0.0;  // set on the first tick, after the first paint
    st->vis = 0.0;
    SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
    SetWindowPos(hwnd, nullptr, x, y + st->slidePx, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    SetTimer(hwnd, TIMER_CONFIRM_FADE, 10, nullptr);
}

static void FwBoxCloseDone(HWND hwnd, FwConfirmState* st) {
    KillTimer(hwnd, TIMER_CONFIRM_FADE);
    st->done = true;
    ShowWindow(hwnd, SW_HIDE);
    if (st->doneMsg && st->doneTo) PostMessageW(st->doneTo, st->doneMsg, st->result ? 1 : 0, (LPARAM)hwnd);
}

// One step of the open or close: alpha and an 8 DIP slide, nothing redrawn.
static void FwBoxStep(HWND hwnd, FwConfirmState* st) {
    if (st->animStart <= 0.0) st->animStart = FwNowMs();
    double t = st->animMs > 0.0 ? std::clamp((FwNowMs() - st->animStart) / st->animMs, 0.0, 1.0) : 1.0;
    double e = st->closing ? st->closeFrom * (1.0 - t * t * t) : 1.0 - std::pow(1.0 - t, 3.0);
    st->vis = e;
    SetLayeredWindowAttributes(hwnd, 0, (BYTE)std::clamp((int)std::lround(255.0 * e), 0, 255), LWA_ALPHA);
    SetWindowPos(hwnd, nullptr, st->finalX, st->finalY + (int)std::lround((1.0 - e) * st->slidePx), 0, 0,
                 SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    if (t >= 1.0) {
        if (st->closing) FwBoxCloseDone(hwnd, st);
        else FwBoxSettle(hwnd, st);
    }
}

static void FwConfirmFinish(HWND hwnd, FwConfirmState* st, bool yes) {
    if (!st || st->done || st->closing) return;
    st->result = yes;
    if (GetCapture() == hwnd) ReleaseCapture();
    double scale = 1.0;
    if (!FwMotion(&scale) || !IsWindowVisible(hwnd)) {
        FwBoxCloseDone(hwnd, st);
        return;
    }
    KillTimer(hwnd, TIMER_CONFIRM_FADE);
    st->closeFrom = st->settled ? 1.0 : std::clamp(st->vis, 0.0, 1.0);
    if (st->settled) {
        RECT wr{};
        GetWindowRect(hwnd, &wr);
        st->finalX = wr.left;
        st->finalY = wr.top;
    }
    if (!st->slidePx) st->slidePx = MulDiv(8, (int)GetDpiForWindow(hwnd), 96);
    st->closing = true;
    // Never fade the glass: switch it off and fade a solid frame instead.
    ApplyPanelGlass(hwnd, false);
    st->glass = false;
    LONG_PTR ex = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    if (!(ex & WS_EX_LAYERED)) SetWindowLongPtrW(hwnd, GWL_EXSTYLE, ex | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, (BYTE)std::lround(255.0 * st->closeFrom), LWA_ALPHA);
    RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
    st->animMs = 120.0 * scale;
    st->animStart = FwNowMs();
    SetTimer(hwnd, TIMER_CONFIRM_FADE, 10, nullptr);
}

static LRESULT CALLBACK FwConfirmProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE) {
        auto* cs = reinterpret_cast<CREATESTRUCTW*>(lParam);
        if (cs && cs->lpCreateParams) SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
    }
    FwConfirmState* st = reinterpret_cast<FwConfirmState*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    if (!st) st = g_confirm;
    // A box that is fading out takes no more clicks or keys.
    if (st && st->closing &&
        ((msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) || msg == WM_KEYDOWN || msg == WM_CHAR))
        return 0;
    switch (msg) {
        case WM_CREATE: {
            BOOL dark = TRUE;
            DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
            DWORD pref = DWMWCP_ROUND;
            DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &pref, sizeof(pref));
            MARGINS m{-1, -1, -1, -1};
            DwmExtendFrameIntoClientArea(hwnd, &m);
            // The glass comes on once the open has settled (FwBoxSettle).
            ApplyPanelGlass(hwnd, false);
            if (st) st->glass = false;
            return 0;
        }
        case WM_NCACTIVATE:
            return TRUE;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
            FwConfirmPaint(hwnd, st);
            return 0;
        case WM_TIMER:
            if (wParam == TIMER_CONFIRM_FADE && st) FwBoxStep(hwnd, st);
            return 0;
        case WM_SETCURSOR:
            if (st && LOWORD(lParam) == HTCLIENT) {
                POINT pt{};
                GetCursorPos(&pt);
                ScreenToClient(hwnd, &pt);
                SetCursor(LoadCursorW(nullptr, FwConfirmHit(st, pt) ? IDC_HAND : IDC_ARROW));
                return TRUE;
            }
            break;
        case WM_MOUSEMOVE:
            if (st) {
                if (!st->tracking) {
                    TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
                    TrackMouseEvent(&tme);
                    st->tracking = true;
                }
                POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                int hov = FwConfirmHit(st, pt);
                if (hov != st->hover || !st->inside) {
                    st->hover = hov;
                    st->inside = true;
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
            }
            return 0;
        case WM_MOUSELEAVE:
            if (st) {
                st->tracking = false;
                st->inside = false;
                st->hover = 0;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_LBUTTONDOWN:
            SetCapture(hwnd);
            return 0;
        case WM_LBUTTONUP: {
            ReleaseCapture();
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            int hit = st ? FwConfirmHit(st, pt) : 0;
            if (hit) FwConfirmFinish(hwnd, st, hit == 2);
            return 0;
        }
        case WM_KEYDOWN:
            if (!st) return 0;
            switch (wParam) {
                case VK_RETURN:
                case VK_SPACE:
                    FwConfirmFinish(hwnd, st, st->focus == 2);
                    break;
                case VK_ESCAPE:
                case 'N':
                    FwConfirmFinish(hwnd, st, false);
                    break;
                case 'Y':
                    FwConfirmFinish(hwnd, st, true);
                    break;
                case VK_TAB:
                case VK_LEFT:
                case VK_RIGHT:
                    st->focus = (st->focus == 2) ? 1 : 2;
                    InvalidateRect(hwnd, nullptr, FALSE);
                    break;
            }
            return 0;
        case WM_CLOSE:
            FwConfirmFinish(hwnd, st, false);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static bool FwConfirm(const wchar_t* title, const wchar_t* body, const wchar_t* yes, const wchar_t* no,
                      bool danger, bool question) {
    if (g_hConfirm) return false;  // one question at a time; a second one counts as "no"
    static bool registered = false;
    HINSTANCE inst = GetModuleHandleW(nullptr);
    if (!registered) {
        WNDCLASSEXW wc{sizeof(wc)};
        wc.lpfnWndProc = FwConfirmProc;
        wc.hInstance = inst;
        wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wc.lpszClassName = kConfirmClass;
        registered = RegisterClassExW(&wc) != 0 || GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
    }
    HWND owner = (g_hCyclePopup && IsWindow(g_hCyclePopup)) ? g_hCyclePopup : g_hWnd;

    // Centre on the open panel, or on the screen under the pointer when the panel is closed.
    RECT anchor{};
    bool onPanel = g_hWnd && g_uiState == UiState::Panel && GetWindowRect(g_hWnd, &anchor);
    POINT cpt{};
    GetCursorPos(&cpt);
    HMONITOR mon = onPanel ? MonitorFromRect(&anchor, MONITOR_DEFAULTTONEAREST)
                           : MonitorFromPoint(cpt, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    if (!onPanel) anchor = mi.rcWork;
    int cx = (anchor.left + anchor.right) / 2, cy = (anchor.top + anchor.bottom) / 2;

    FwConfirmState st;
    st.title = title;
    st.body = body;
    st.yes = yes;
    st.no = no;
    st.danger = danger;
    st.focus = danger ? 1 : 2;  // a risky box starts on the safe button, so Enter keeps things as they are
    st.question = question;
    g_confirm = &st;
    HWND hwnd = registered ? CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED, kConfirmClass, title,
                                             WS_POPUP, cx, cy, 10, 10, owner, nullptr, inst, nullptr)
                           : nullptr;
    if (!hwnd) {
        // Never skip the safety question: fall back to the stock box if ours cannot open.
        g_confirm = nullptr;
        std::wstring text = std::wstring(body) + L"\n\n" + yes + L"?";
        return MessageBoxW(owner, text.c_str(), L"Seamless Windows Firewall",
                           MB_YESNO | (question ? MB_ICONQUESTION : MB_ICONWARNING) | MB_TOPMOST) == IDYES;
    }
    g_hConfirm = hwnd;
    SIZE sz = FwConfirmLayout(hwnd, &st);
    int x = std::clamp(cx - (int)sz.cx / 2, (int)mi.rcWork.left, (int)mi.rcWork.right - (int)sz.cx);
    int y = std::clamp(cy - (int)sz.cy / 2, (int)mi.rcWork.top, (int)mi.rcWork.bottom - (int)sz.cy);
    SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, sz.cx, sz.cy, SWP_NOACTIVATE);
    FwBoxStartOpen(hwnd, &st, x, y);

    bool ownerEnabled = owner && IsWindowEnabled(owner);
    if (ownerEnabled) EnableWindow(owner, FALSE);
    ShowWindow(hwnd, SW_SHOW);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    bool quit = false;
    WPARAM quitCode = 0;
    MSG m{};
    while (!st.done) {
        BOOL r = GetMessageW(&m, nullptr, 0, 0);
        if (r == 0) {
            quit = true;
            quitCode = m.wParam;
            break;
        }
        if (r < 0) break;
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    bool result = st.done && st.result;
    if (ownerEnabled && IsWindow(owner)) EnableWindow(owner, TRUE);
    DestroyWindow(hwnd);
    g_hConfirm = nullptr;
    g_confirm = nullptr;
    // Hand focus back only to a window the owner had open; a closed pill never takes it.
    if (owner && IsWindow(owner) && (owner == g_hCyclePopup || g_uiState == UiState::Panel))
        SetForegroundWindow(owner);
    if (quit) PostQuitMessage((int)quitCode);
    return result;
}

// ---------------------------------------------------------------------------
// Connection requests: our own box in place of the Windows Firewall pop-up.
// Windows Firewall keeps guarding. Its "allow this app?" pop-up is switched off per
// profile while this runs and put back as it was when the setting goes off or the mod
// stops. A worker looks every 2 s for apps in the user's session that wait for other
// devices (a listening TCP port, or a fixed UDP port) and have no inbound rule yet. Each
// one gets the frosted box, once per session; the answer is saved as a normal inbound
// firewall rule. Until then Windows keeps the app blocked, as it did with its own pop-up.
// ---------------------------------------------------------------------------
constexpr UINT WM_APP_LISTEN_FOUND = WM_APP + 107;
constexpr UINT WM_APP_LISTEN_DONE  = WM_APP + 108;

struct ListenAsk {
    std::wstring path;  // as Windows reports it
    std::wstring name;  // the app's own description, or its file name
    int port = 0;
};

static std::mutex g_listenMtx;
static std::condition_variable g_listenCv;
static bool g_listenStop = false;
static HANDLE g_listenThread = nullptr;
static std::atomic<bool> g_listenRunning{false};
static std::unordered_set<std::wstring> g_listenSeen;  // worker thread only while it runs
static std::vector<std::unique_ptr<ListenAsk>> g_listenQueue;  // UI thread
static HWND g_hListenBox = nullptr;
static std::unique_ptr<FwConfirmState> g_listenBoxState;
static std::unique_ptr<ListenAsk> g_listenCurrent;
static bool g_listenPromptsOff = false;

struct ListenRuleCache {
    std::unordered_set<std::wstring> apps;     // lower-case, expanded paths with any inbound rule
    std::vector<std::pair<int, int>> ports;    // inbound allow rules for any app, by local port
    ULONGLONG tick = 0;
};
static ListenRuleCache g_listenRules;  // worker thread only

template <class F>
static bool WithFwPolicy(F&& fn) {
    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    INetFwPolicy2* p = nullptr;
    bool ok = SUCCEEDED(CoCreateInstance(__uuidof(NetFwPolicy2), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&p))) &&
              p;
    if (ok) {
        fn(p);
        p->Release();
    }
    if (SUCCEEDED(hrCo)) CoUninitialize();
    return ok;
}

struct FwProfileKey {
    NET_FW_PROFILE_TYPE2 type;
    const wchar_t* key;
};
static const FwProfileKey kFwProfiles[] = {
    {NET_FW_PROFILE2_DOMAIN, L"fwPromptOrig_domain"},
    {NET_FW_PROFILE2_PRIVATE, L"fwPromptOrig_private"},
    {NET_FW_PROFILE2_PUBLIC, L"fwPromptOrig_public"},
};

// Switch the Windows pop-up off, keeping what each profile had so it can be put back.
static void ListenPromptsTakeOver() {
    WithFwPolicy([](INetFwPolicy2* p) {
        for (const auto& pk : kFwProfiles) {
            VARIANT_BOOL cur = VARIANT_FALSE;
            if (FAILED(p->get_NotificationsDisabled(pk.type, &cur))) continue;
            if (Wh_GetIntValue(pk.key, -1) == -1) Wh_SetIntValue(pk.key, cur == VARIANT_TRUE ? 1 : 0);
            if (cur != VARIANT_TRUE) {
                HRESULT hr = p->put_NotificationsDisabled(pk.type, VARIANT_TRUE);
                if (FAILED(hr)) Wh_Log(L"Could not switch off the Windows pop-up for %s: 0x%08X", pk.key, (unsigned)hr);
            }
        }
    });
    g_listenPromptsOff = true;
    LogAudit(L"Connection requests: the Windows Firewall pop-up is switched off; this mod asks instead.");
}

// Put the Windows pop-up back the way each profile had it. Also runs at start with the
// setting off, so a crash never leaves the pop-up switched off for good.
static void ListenPromptsGiveBack() {
    bool any = false;
    WithFwPolicy([&](INetFwPolicy2* p) {
        for (const auto& pk : kFwProfiles) {
            int v = Wh_GetIntValue(pk.key, -1);
            if (v == -1) continue;
            HRESULT hr = p->put_NotificationsDisabled(pk.type, v ? VARIANT_TRUE : VARIANT_FALSE);
            if (SUCCEEDED(hr)) {
                Wh_DeleteValue(pk.key);
                any = true;
            } else {
                Wh_Log(L"Could not put back the Windows pop-up for %s: 0x%08X", pk.key, (unsigned)hr);
            }
        }
    });
    g_listenPromptsOff = false;
    if (any) LogAudit(L"Connection requests: the Windows Firewall pop-up is back.");
}

// True when a profile in use has the firewall on and blocks unasked inbound traffic, the
// only case in which Windows would have shown its pop-up.
static bool InboundBlockedByDefault(bool* onPublic) {
    bool blocked = false;
    WithFwPolicy([&](INetFwPolicy2* p) {
        long cur = 0;
        if (FAILED(p->get_CurrentProfileTypes(&cur))) return;
        if (onPublic) *onPublic = (cur & NET_FW_PROFILE2_PUBLIC) != 0;
        for (const auto& pk : kFwProfiles) {
            if (!(cur & pk.type)) continue;
            VARIANT_BOOL on = VARIANT_FALSE, all = VARIANT_FALSE;
            NET_FW_ACTION def = NET_FW_ACTION_ALLOW;
            if (SUCCEEDED(p->get_FirewallEnabled(pk.type, &on)) && on == VARIANT_TRUE &&
                SUCCEEDED(p->get_DefaultInboundAction(pk.type, &def)) && def == NET_FW_ACTION_BLOCK &&
                SUCCEEDED(p->get_BlockAllInboundTraffic(pk.type, &all)) && all != VARIANT_TRUE)
                blocked = true;
        }
    });
    return blocked;
}

static int ListenPortFromNet(DWORD p) {
    return (int)(((p & 0xFF) << 8) | ((p >> 8) & 0xFF));
}

// pid -> the first port it waits on. Loopback-only sockets never reach other devices, and
// UDP ports Windows hands out by itself (49152 and up) are an app talking out, not waiting.
static std::unordered_map<DWORD, int> CollectListeners() {
    std::unordered_map<DWORD, int> out;
    auto add = [&](DWORD pid, int port) {
        if (pid > 4 && out.find(pid) == out.end()) out[pid] = port;
    };
    auto grab = [](auto fn, std::vector<BYTE>& buf) {
        DWORD size = 0;
        for (int i = 0; i < 4; ++i) {
            DWORD r = fn(buf.empty() ? nullptr : buf.data(), &size);
            if (r == NO_ERROR) return true;
            if (r != ERROR_INSUFFICIENT_BUFFER) return false;
            buf.resize(size + 4096);
        }
        return false;
    };
    std::vector<BYTE> buf;
    if (grab([](void* b, DWORD* s) { return GetExtendedTcpTable(b, s, FALSE, AF_INET, TCP_TABLE_OWNER_PID_LISTENER, 0); },
             buf)) {
        auto* t = reinterpret_cast<MIB_TCPTABLE_OWNER_PID*>(buf.data());
        for (DWORD i = 0; i < t->dwNumEntries; ++i) {
            const auto& r = t->table[i];
            if ((r.dwLocalAddr & 0xFF) == 127) continue;
            add(r.dwOwningPid, ListenPortFromNet(r.dwLocalPort));
        }
    }
    buf.clear();
    if (grab([](void* b, DWORD* s) { return GetExtendedTcpTable(b, s, FALSE, AF_INET6, TCP_TABLE_OWNER_PID_LISTENER, 0); },
             buf)) {
        auto* t = reinterpret_cast<MIB_TCP6TABLE_OWNER_PID*>(buf.data());
        static const UCHAR kLoop6[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
        for (DWORD i = 0; i < t->dwNumEntries; ++i) {
            const auto& r = t->table[i];
            if (memcmp(r.ucLocalAddr, kLoop6, 16) == 0) continue;
            add(r.dwOwningPid, ListenPortFromNet(r.dwLocalPort));
        }
    }
    buf.clear();
    if (grab([](void* b, DWORD* s) { return GetExtendedUdpTable(b, s, FALSE, AF_INET, UDP_TABLE_OWNER_PID, 0); }, buf)) {
        auto* t = reinterpret_cast<MIB_UDPTABLE_OWNER_PID*>(buf.data());
        for (DWORD i = 0; i < t->dwNumEntries; ++i) {
            const auto& r = t->table[i];
            int port = ListenPortFromNet(r.dwLocalPort);
            if ((r.dwLocalAddr & 0xFF) == 127 || port < 1 || port > 49151) continue;
            add(r.dwOwningPid, port);
        }
    }
    buf.clear();
    if (grab([](void* b, DWORD* s) { return GetExtendedUdpTable(b, s, FALSE, AF_INET6, UDP_TABLE_OWNER_PID, 0); }, buf)) {
        auto* t = reinterpret_cast<MIB_UDP6TABLE_OWNER_PID*>(buf.data());
        static const UCHAR kLoop6[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
        for (DWORD i = 0; i < t->dwNumEntries; ++i) {
            const auto& r = t->table[i];
            int port = ListenPortFromNet(r.dwLocalPort);
            if (memcmp(r.ucLocalAddr, kLoop6, 16) == 0 || port < 1 || port > 49151) continue;
            add(r.dwOwningPid, port);
        }
    }
    return out;
}

static std::wstring ListenExpandLower(const wchar_t* s) {
    if (!s || !*s) return L"";
    wchar_t buf[MAX_PATH * 2]{};
    DWORD n = ExpandEnvironmentStringsW(s, buf, ARRAYSIZE(buf));
    return ToLower((n > 0 && n <= ARRAYSIZE(buf)) ? std::wstring(buf) : std::wstring(s));
}

static void ListenParsePorts(const wchar_t* s, std::vector<std::pair<int, int>>& out) {
    if (!s || !*s) return;
    std::wstring t(s);
    size_t i = 0;
    while (i < t.size()) {
        size_t j = t.find(L',', i);
        if (j == std::wstring::npos) j = t.size();
        std::wstring part = t.substr(i, j - i);
        wchar_t* end = nullptr;
        long a = wcstol(part.c_str(), &end, 10);
        if (end != part.c_str() && a > 0) {
            long b = a;
            if (end && *end == L'-') b = wcstol(end + 1, nullptr, 10);
            if (b >= a) out.emplace_back((int)a, (int)b);
        }
        i = j + 1;
    }
}

static void ListenRefreshRules() {
    ULONGLONG now = GetTickCount64();
    if (g_listenRules.tick && now - g_listenRules.tick < 5000) return;
    ListenRuleCache fresh;
    WithFwPolicy([&](INetFwPolicy2* p) {
        long cur = NET_FW_PROFILE2_ALL;
        p->get_CurrentProfileTypes(&cur);
        INetFwRules* rules = nullptr;
        if (FAILED(p->get_Rules(&rules)) || !rules) return;
        IUnknown* unk = nullptr;
        IEnumVARIANT* en = nullptr;
        if (SUCCEEDED(rules->get__NewEnum(&unk)) && unk && SUCCEEDED(unk->QueryInterface(IID_PPV_ARGS(&en))) && en) {
            VARIANT var;
            VariantInit(&var);
            ULONG got = 0;
            while (en->Next(1, &var, &got) == S_OK && got == 1) {
                INetFwRule* r = nullptr;
                if (var.vt == VT_DISPATCH && var.pdispVal && SUCCEEDED(var.pdispVal->QueryInterface(IID_PPV_ARGS(&r))) &&
                    r) {
                    NET_FW_RULE_DIRECTION dir = NET_FW_RULE_DIR_OUT;
                    if (SUCCEEDED(r->get_Direction(&dir)) && dir == NET_FW_RULE_DIR_IN) {
                        BSTR app = nullptr, svc = nullptr, lp = nullptr;
                        r->get_ApplicationName(&app);
                        if (app && *app && wcscmp(app, L"*") != 0) {
                            // Any inbound rule for the app, allow or block, on or off, is an answer
                            // already given; Windows never asked again either.
                            fresh.apps.insert(ListenExpandLower(app));
                        } else {
                            VARIANT_BOOL on = VARIANT_FALSE;
                            NET_FW_ACTION act = NET_FW_ACTION_BLOCK;
                            long prof = 0;
                            r->get_ServiceName(&svc);
                            if ((!svc || !*svc || wcscmp(svc, L"*") == 0) && SUCCEEDED(r->get_Enabled(&on)) &&
                                on == VARIANT_TRUE && SUCCEEDED(r->get_Action(&act)) && act == NET_FW_ACTION_ALLOW &&
                                SUCCEEDED(r->get_Profiles(&prof)) && (prof & cur) && SUCCEEDED(r->get_LocalPorts(&lp)))
                                ListenParsePorts(lp, fresh.ports);
                        }
                        if (app) SysFreeString(app);
                        if (svc) SysFreeString(svc);
                        if (lp) SysFreeString(lp);
                    }
                    r->Release();
                }
                VariantClear(&var);
            }
            en->Release();
        }
        if (unk) unk->Release();
        rules->Release();
    });
    fresh.tick = now;
    g_listenRules = std::move(fresh);
}

static std::wstring ListenFriendlyName(const std::wstring& path) {
    std::wstring file = GetFileNameOnly(path);
    DWORD dummy = 0;
    DWORD size = GetFileVersionInfoSizeW(path.c_str(), &dummy);
    if (size) {
        std::vector<BYTE> data(size);
        if (GetFileVersionInfoW(path.c_str(), 0, size, data.data())) {
            struct LangCp { WORD lang, cp; };
            LangCp* tr = nullptr;
            UINT trLen = 0;
            std::vector<std::wstring> keys;
            if (VerQueryValueW(data.data(), L"\\VarFileInfo\\Translation", (void**)&tr, &trLen) && tr &&
                trLen >= sizeof(LangCp)) {
                wchar_t k[64];
                swprintf_s(k, L"\\StringFileInfo\\%04x%04x\\FileDescription", tr[0].lang, tr[0].cp);
                keys.push_back(k);
            }
            keys.push_back(L"\\StringFileInfo\\040904b0\\FileDescription");
            keys.push_back(L"\\StringFileInfo\\040904e4\\FileDescription");
            for (const auto& k : keys) {
                wchar_t* v = nullptr;
                UINT len = 0;
                if (VerQueryValueW(data.data(), k.c_str(), (void**)&v, &len) && v && len > 1) {
                    std::wstring d(v);
                    while (!d.empty() && iswspace(d.back())) d.pop_back();
                    while (!d.empty() && iswspace(d.front())) d.erase(d.begin());
                    if (!d.empty() && d.size() < 80) return d;
                }
            }
        }
    }
    return file;
}

static void ListenScanOnce() {
    auto hits = CollectListeners();
    if (hits.empty()) return;
    DWORD self = GetCurrentProcessId();
    struct Cand { std::wstring path, lower; int port; };
    std::vector<Cand> cands;
    std::unordered_set<std::wstring> batch;
    for (const auto& [pid, port] : hits) {
        if (pid == self) continue;
        DWORD sid = 0;
        if (!ProcessIdToSessionId(pid, &sid) || sid == 0) continue;  // services answer to their own rules
        std::wstring path = QueryProcessExePath(pid);
        if (path.empty()) continue;
        std::wstring lower = ToLower(path);
        if (g_listenSeen.count(lower) || batch.count(lower)) continue;
        if (IsSystemPath(lower) || IsCriticalSystemExe(lower) || lower.find(L"\\windowsapps\\") != std::wstring::npos ||
            lower.find(L"\\windhawk\\") != std::wstring::npos)
            continue;
        batch.insert(lower);
        cands.push_back({path, lower, port});
    }
    if (cands.empty()) return;
    bool onPublic = false;
    if (!InboundBlockedByDefault(&onPublic)) return;  // nothing would be blocked, so nothing to ask
    ListenRefreshRules();
    for (auto& c : cands) {
        g_listenSeen.insert(c.lower);
        if (g_listenRules.apps.count(c.lower)) continue;
        bool portOpen = false;
        for (const auto& pr : g_listenRules.ports)
            if (c.port >= pr.first && c.port <= pr.second) portOpen = true;
        if (portOpen) continue;
        auto* a = new ListenAsk{c.path, ListenFriendlyName(c.path), c.port};
        HWND w = g_hWnd;
        if (!w || !PostMessageW(w, WM_APP_LISTEN_FOUND, 0, (LPARAM)a)) {
            delete a;
            g_listenSeen.erase(c.lower);
        } else {
            Wh_Log(L"Connection request: %s on port %d", c.path.c_str(), c.port);
        }
    }
}

static DWORD WINAPI ListenThreadProc(LPVOID) {
    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    std::unique_lock<std::mutex> lk(g_listenMtx);
    while (!g_listenStop) {
        lk.unlock();
        ListenScanOnce();
        lk.lock();
        g_listenCv.wait_for(lk, std::chrono::seconds(2), [] { return g_listenStop; });
    }
    lk.unlock();
    if (SUCCEEDED(hrCo)) CoUninitialize();
    return 0;
}

static void ListenWatchStart() {
    if (g_listenThread) return;
    {
        std::lock_guard<std::mutex> lk(g_listenMtx);
        g_listenStop = false;
    }
    g_listenRunning = true;
    g_listenThread = CreateThread(nullptr, 0, ListenThreadProc, nullptr, 0, nullptr);
    if (!g_listenThread) g_listenRunning = false;
}

static void ListenWatchStop() {
    if (g_listenThread) {
        {
            std::lock_guard<std::mutex> lk(g_listenMtx);
            g_listenStop = true;
        }
        g_listenCv.notify_all();
        WaitForSingleObject(g_listenThread, 10000);
        CloseHandle(g_listenThread);
        g_listenThread = nullptr;
    }
    g_listenRunning = false;
    g_listenSeen.clear();
    g_listenRules = ListenRuleCache{};
}

static bool EnsureConfirmClass() {
    static bool registered = false;
    if (!registered) {
        WNDCLASSEXW wc{sizeof(wc)};
        wc.lpfnWndProc = FwConfirmProc;
        wc.hInstance = GetModuleHandleW(nullptr);
        wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wc.lpszClassName = kConfirmClass;
        registered = RegisterClassExW(&wc) != 0 || GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
    }
    return registered;
}

static void ListenCloseBox() {
    if (g_hListenBox && IsWindow(g_hListenBox)) DestroyWindow(g_hListenBox);
    g_hListenBox = nullptr;
    g_listenBoxState.reset();
    g_listenCurrent.reset();
    g_listenQueue.clear();
}

static void ShowNextListenBox() {
    if (g_listenQueue.empty() || !EnsureConfirmClass()) return;
    std::unique_ptr<ListenAsk> a = std::move(g_listenQueue.front());
    g_listenQueue.erase(g_listenQueue.begin());

    bool publicToo = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        publicToo = g_settings.allowOnPublicNetworks;
    }
    bool onPublic = false;
    InboundBlockedByDefault(&onPublic);

    auto st = std::make_unique<FwConfirmState>();
    st->title = L"Let other devices connect?";
    std::wstring file = GetFileNameOnly(a->path);
    std::wstring who = (_wcsicmp(a->name.c_str(), file.c_str()) == 0) ? a->name : (a->name + L" (" + file + L")");
    st->body = who + L" is waiting for other devices to connect to it";
    if (a->port) st->body += L" on port " + std::to_wstring(a->port);
    st->body += L". Windows Firewall keeps it blocked until you choose.";
    if (onPublic)
        st->body += L" You are on a public network, so Allow lets it in here too.";
    else if (!publicToo)
        st->body += L" Allow lets it in on home and work networks.";
    st->yes = L"Allow";
    st->no = L"Block";
    st->question = true;
    st->focus = 2;
    st->doneTo = g_hWnd;
    st->doneMsg = WM_APP_LISTEN_DONE;

    POINT cpt{};
    GetCursorPos(&cpt);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(cpt, MONITOR_DEFAULTTOPRIMARY), &mi);
    int cx = (mi.rcWork.left + mi.rcWork.right) / 2, cy = (mi.rcWork.top + mi.rcWork.bottom) / 2;
    // No owner and never activated: the box sits on top and waits, but the app you are
    // typing in keeps the keyboard. A click on a button still answers it.
    HWND hwnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE, kConfirmClass,
                                st->title.c_str(), WS_POPUP, cx, cy, 10, 10, nullptr, nullptr,
                                GetModuleHandleW(nullptr), st.get());
    if (!hwnd) {
        Wh_Log(L"Connection request box could not open (%u); Windows keeps %s blocked.", GetLastError(),
               a->path.c_str());
        return;
    }
    SIZE sz = FwConfirmLayout(hwnd, st.get());
    int x = std::clamp(cx - (int)sz.cx / 2, (int)mi.rcWork.left, (int)mi.rcWork.right - (int)sz.cx);
    int y = std::clamp(cy - (int)sz.cy / 2, (int)mi.rcWork.top, (int)mi.rcWork.bottom - (int)sz.cy);
    SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, sz.cx, sz.cy, SWP_NOACTIVATE);
    FwBoxStartOpen(hwnd, st.get(), x, y);
    ShowWindow(hwnd, SW_SHOWNOACTIVATE);
    g_hListenBox = hwnd;
    g_listenBoxState = std::move(st);
    g_listenCurrent = std::move(a);
}

// Shows the next request, and keeps the open one out of the way while a game or video
// fills the screen.
static void ListenPump(bool fullscreen) {
    if (g_hListenBox) {
        FwConfirmState* bs = g_listenBoxState.get();
        if (!IsWindow(g_hListenBox) || !bs || bs->done || bs->closing) return;
        bool vis = IsWindowVisible(g_hListenBox) != FALSE;
        // Never leave the box half drawn if its animation ticks were held up.
        if (!bs->settled && GetTickCount() - bs->openTick > (DWORD)(bs->animMs + 400.0))
            FwBoxSettle(g_hListenBox, bs);
        if (fullscreen && vis) {
            ShowWindow(g_hListenBox, SW_HIDE);
        } else if (!fullscreen && !vis) {
            FwBoxSettle(g_hListenBox, bs);
            SetWindowPos(g_hListenBox, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            ShowWindow(g_hListenBox, SW_SHOWNOACTIVATE);
        }
        return;
    }
    if (!fullscreen && !g_listenQueue.empty()) ShowNextListenBox();
}

static void AddListenRule(const ListenAsk& a, bool allow) {
    bool publicToo = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        publicToo = g_settings.allowOnPublicNetworks;
    }
    HRESULT result = E_FAIL;
    WithFwPolicy([&](INetFwPolicy2* p) {
        long cur = 0;
        p->get_CurrentProfileTypes(&cur);
        long profiles = NET_FW_PROFILE2_ALL;
        if (allow) {
            profiles = NET_FW_PROFILE2_PRIVATE | NET_FW_PROFILE2_DOMAIN;
            if (publicToo || (cur & NET_FW_PROFILE2_PUBLIC)) profiles |= NET_FW_PROFILE2_PUBLIC;
        }
        INetFwRules* rules = nullptr;
        if (FAILED(p->get_Rules(&rules)) || !rules) return;
        INetFwRule* r = nullptr;
        if (SUCCEEDED(CoCreateInstance(__uuidof(NetFwRule), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&r))) && r) {
            std::wstring nm = L"Seamless Firewall: " + a.name;
            std::wstring desc = allow ? L"Allowed from the Seamless Windows Firewall connection box."
                                      : L"Blocked from the Seamless Windows Firewall connection box.";
            BSTR bName = SysAllocString(nm.c_str());
            BSTR bDesc = SysAllocString(desc.c_str());
            BSTR bApp = SysAllocString(a.path.c_str());
            BSTR bGrp = SysAllocString(L"Seamless Windows Firewall");
            r->put_Name(bName);
            r->put_Description(bDesc);
            r->put_ApplicationName(bApp);
            r->put_Grouping(bGrp);
            r->put_Protocol(NET_FW_IP_PROTOCOL_ANY);
            r->put_Direction(NET_FW_RULE_DIR_IN);
            r->put_Action(allow ? NET_FW_ACTION_ALLOW : NET_FW_ACTION_BLOCK);
            r->put_Profiles(profiles);
            r->put_Enabled(VARIANT_TRUE);
            result = rules->Add(r);
            SysFreeString(bName);
            SysFreeString(bDesc);
            SysFreeString(bApp);
            SysFreeString(bGrp);
            r->Release();
        }
        rules->Release();
    });
    if (SUCCEEDED(result))
        LogAudit(std::wstring(allow ? L"Connection request allowed: " : L"Connection request blocked: ") + a.path);
    else
        Wh_Log(L"Could not save the firewall rule for %s: 0x%08X", a.path.c_str(), (unsigned)result);
}

static void ListenBoxAnswered(HWND box, bool allow) {
    if (!box || box != g_hListenBox) return;
    if (g_listenCurrent) AddListenRule(*g_listenCurrent, allow);
    DestroyWindow(box);
    g_hListenBox = nullptr;
    g_listenBoxState.reset();
    g_listenCurrent.reset();
    ListenPump(IsFullscreenActive());
}

// Turns the feature on or off to match the setting. UI thread.
static void ListenSync() {
    bool on = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        on = g_settings.replaceFirewallPrompt;
    }
    if (on && IsProcessElevated()) {
        if (!g_listenPromptsOff) ListenPromptsTakeOver();
        ListenWatchStart();
    } else {
        ListenWatchStop();
        ListenCloseBox();
        ListenPromptsGiveBack();
    }
}

static void SyncHoverSensorTimer(HWND hwnd) {
    if (!hwnd) return;
    bool needSensor = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        needSensor = (g_uiState == UiState::Line) && g_settings.hoverExpand && g_settings.showPill &&
                     g_settings.expandHoverHitArea && !g_hiddenByFullscreen;
    }
    if (needSensor) SetTimer(hwnd, TIMER_HOVER_SENSOR, 75, nullptr);
    else KillTimer(hwnd, TIMER_HOVER_SENSOR);
}

static void SetWindowFrameMode(HWND hwnd, bool roundedPanel) {
    if (roundedPanel && HasAnyActiveCycle()) SetTimer(hwnd, TIMER_CYCLE_UI, 250, nullptr);
    else if (!roundedPanel) KillTimer(hwnd, TIMER_CYCLE_UI);
    if (!hwnd) return;
    // Closed, and while the panel fades, it is a layered window. Open and settled it is a
    // plain window, so DWM can blur behind it.
    bool wantLayered = !roundedPanel || g_panelFading;
    LONG_PTR ex = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    bool hasLayered = (ex & WS_EX_LAYERED) != 0;
    if (wantLayered != hasLayered) {
        SetWindowLongPtrW(hwnd, GWL_EXSTYLE, wantLayered ? (ex | WS_EX_LAYERED) : (ex & ~WS_EX_LAYERED));
    }
    if (g_lastRoundedFrame != roundedPanel || !g_glassApplied) {
        DWORD pref = roundedPanel ? DWMWCP_ROUND : DWMWCP_DONOTROUND;
        DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &pref, sizeof(pref));
        MARGINS m = roundedPanel ? MARGINS{-1, -1, -1, -1} : MARGINS{0, 0, 0, 0};
        DwmExtendFrameIntoClientArea(hwnd, &m);
        g_lastRoundedFrame = roundedPanel;
    }
    bool wantGlass = roundedPanel && !g_panelFading && TransparencyOn();
    if (!g_glassApplied || wantGlass != g_panelGlassOn) {
        ApplyPanelGlass(hwnd, wantGlass);
        g_panelGlassOn = wantGlass;
        g_glassApplied = true;
    }
}

static UINT GetDpiForMonitorSafe(HMONITOR mon, HWND fallback) {
    UINT dx = 0, dy = 0;
    using GetDpiForMonitorFn = HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*);
    static GetDpiForMonitorFn fn = []() -> GetDpiForMonitorFn {
        HMODULE m = LoadLibraryW(L"shcore.dll");
        return m ? (GetDpiForMonitorFn)GetProcAddress(m, "GetDpiForMonitor") : nullptr;
    }();
    if (fn && mon && SUCCEEDED(fn(mon, 0, &dx, &dy)) && dx) return dx;
    return fallback ? GetDpiForWindow(fallback) : 96;
}

static SIZE GetExpandedLogicalSize() {
    ModSettings s;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        s = g_settings;
    }
    switch (s.windowSizePreset) {
        case SizePreset::Large:      return {680, 680};
        case SizePreset::ExtraLarge: return {840, 840};
        default:                     return {436, 480};
    }
}

static HMONITOR GetTargetMonitor(bool followCursor) {
    if (followCursor && !g_drag.dragging) {
        POINT cur{};
        if (GetCursorPos(&cur)) return MonitorFromPoint(cur, MONITOR_DEFAULTTONEAREST);
    }
    return g_hWnd ? MonitorFromWindow(g_hWnd, MONITOR_DEFAULTTONEAREST)
                  : MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY);
}

static void ComputeTargetRect(double progress, RECT& outRc) {
    HMONITOR mon = g_panelMon ? g_panelMon : MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    RECT wa = mi.rcWork;
    UINT dpi = GetDpiForMonitorSafe(mon, g_hWnd);

    SIZE expLog = GetExpandedLogicalSize();
    int expW = std::min(DpiScale(expLog.cx, dpi), (int)(wa.right - wa.left));
    int expH = std::min(DpiScale(expLog.cy, dpi), (int)(wa.bottom - wa.top));
    // Full size the whole time; the open and close only slide it 8 DIP and fade it.
    int curW = std::max(1, expW);
    int curH = std::max(1, expH);
    int slide = (int)std::lround((1.0 - std::clamp(progress, 0.0, 1.0)) * DpiScale(8, dpi));

    int fullL = wa.left + (wa.right - wa.left - expW) / 2;
    int fullT = wa.top + (wa.bottom - wa.top - expH) / 2;
    if (g_panelMoved) {
        fullL = std::clamp((int)g_panelMovedPos.x, (int)wa.left, (int)wa.right - expW);
        fullT = std::clamp((int)g_panelMovedPos.y, (int)wa.top, (int)wa.bottom - expH);
    }
    outRc.left = fullL + (expW - curW) / 2;
    outRc.top = fullT + (expH - curH) / 2 + slide;
    outRc.right = outRc.left + curW;
    outRc.bottom = outRc.top + curH;
}

static void PanelDropFadeFrame() {
    if (g_fadeDC) {
        SelectObject(g_fadeDC, g_fadeOld);
        DeleteDC(g_fadeDC);
        g_fadeDC = nullptr;
    }
    if (g_fadeBmp) {
        DeleteObject(g_fadeBmp);
        g_fadeBmp = nullptr;
    }
    g_fadeSz = {};
}

// Keeps the last solid frame, so each animation step only moves and fades it.
static void PanelKeepFadeFrame(HDC src, int w, int h) {
    if (!g_fadeDC || g_fadeSz.cx != w || g_fadeSz.cy != h) {
        PanelDropFadeFrame();
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = w;
        bi.bmiHeader.biHeight = -h;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        void* bits = nullptr;
        g_fadeBmp = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!g_fadeBmp) return;
        g_fadeDC = CreateCompatibleDC(nullptr);
        g_fadeOld = SelectObject(g_fadeDC, g_fadeBmp);
        g_fadeSz = {w, h};
    }
    BitBlt(g_fadeDC, 0, 0, w, h, src, 0, 0, SRCCOPY);
}

// One step of the panel's open or close: move and fade the kept frame.
static void PanelFadeFrame(HWND hwnd) {
    RECT rc{};
    ComputeTargetRect(g_expandClock.currentVal, rc);
    if (!g_fadeDC || g_fadeSz.cx != rc.right - rc.left || g_fadeSz.cy != rc.bottom - rc.top) {
        SetWindowPos(hwnd, HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
                     SWP_NOACTIVATE | SWP_NOCOPYBITS);
        RequestRepaint();
        return;
    }
    POINT pt{rc.left, rc.top};
    SIZE sz = g_fadeSz;
    POINT src{0, 0};
    BYTE a = (BYTE)std::clamp((int)std::lround(g_expandClock.currentVal * 255.0), 0, 255);
    BLENDFUNCTION bf{AC_SRC_OVER, 0, a, AC_SRC_ALPHA};
    UpdateLayeredWindow(hwnd, nullptr, &pt, &sz, g_fadeDC, &src, 0, &bf, ULW_ALPHA);
}

static void PanelFinishClose() {
    g_expandClock.currentVal = 0.0;
    g_expandClock.active = false;
    g_panelFading = false;
    g_panelClosing = false;
    if (!g_hWnd) return;
    ShowWindow(g_hWnd, SW_HIDE);
    SetWindowFrameMode(g_hWnd, false);
    PanelDropFadeFrame();
    SyncHoverSensorTimer(g_hWnd);
    SyncCycleWidgetWindow(true);
}

// The open has settled: drop the layer, switch the glass on and draw it once.
static void PanelFinishOpen(HWND hwnd) {
    g_panelFading = false;
    RECT rc{};
    ComputeTargetRect(1.0, rc);
    SetWindowFrameMode(hwnd, true);
    SetWindowPos(hwnd, HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
                 SWP_NOACTIVATE | SWP_FRAMECHANGED);
    RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
    PanelDropFadeFrame();
}

static void UpdateWindowGeometry(bool immediate) {
    if (!g_hWnd) return;
    bool open = g_uiState != UiState::Line;
    bool shown = IsWindowVisible(g_hWnd) != FALSE;
    double scale = 1.0;
    bool motion = !immediate && FwMotion(&scale);
    // A fresh open picks the screen under the pointer; one that cuts a close short carries
    // on from where the close got to.
    if (open && !g_panelWasOpen && !shown) {
        POINT cur{};
        GetCursorPos(&cur);
        g_panelMon = MonitorFromPoint(cur, MONITOR_DEFAULTTOPRIMARY);
        g_panelMoved = false;
        g_expandClock.currentVal = 0.0;
        g_expandClock.active = false;
    }
    if (!open && g_panelWasOpen) g_panelClosedTick = GetTickCount();
    g_panelWasOpen = open;
    if (!open) {
        KillTimer(g_hWnd, TIMER_OUTSIDE_CLICK);
        SyncOutsideMouseHook(false);
        if (motion && shown && g_expandClock.currentVal > 0.01) {
            // The glass goes off first, then a solid frame fades out and slides down 8 DIP.
            g_panelClosing = true;
            g_panelFading = true;
            SetWindowFrameMode(g_hWnd, true);
            if (!g_fadeDC) RedrawWindow(g_hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
            g_expandClock.Start(0.0, 120.0 * scale, 2);
            SetTimer(g_hWnd, TIMER_ANIM_VSYNC, 10, nullptr);
            return;
        }
        PanelFinishClose();
        return;
    }
    g_panelClosing = false;
    bool wasFading = g_panelFading;
    if (!motion) {
        g_expandClock.currentVal = 1.0;
        g_expandClock.active = false;
    } else {
        if (g_expandClock.currentVal < 0.999 && !g_fadeDC) {
            g_panelFading = true;
            SetWindowFrameMode(g_hWnd, true);
            RECT rc0{};
            ComputeTargetRect(g_expandClock.currentVal, rc0);
            SetWindowPos(g_hWnd, HWND_TOPMOST, rc0.left, rc0.top, rc0.right - rc0.left, rc0.bottom - rc0.top,
                         SWP_NOACTIVATE | SWP_SHOWWINDOW);
            RedrawWindow(g_hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
        }
        g_expandClock.Start(1.0, 160.0 * scale, 1);
    }
    g_panelFading = g_expandClock.active;
    SetWindowFrameMode(g_hWnd, true);
    RECT rc{};
    ComputeTargetRect(g_expandClock.currentVal, rc);
    SetWindowPos(g_hWnd, HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
    if (g_panelFading) {
        SetTimer(g_hWnd, TIMER_ANIM_VSYNC, 10, nullptr);
    } else if (wasFading) {
        RedrawWindow(g_hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
        PanelDropFadeFrame();
    }
    SyncHoverSensorTimer(g_hWnd);
    if (g_hWnd) {
        if (g_uiState == UiState::Panel && !g_pinned) SetTimer(g_hWnd, TIMER_OUTSIDE_CLICK, 50, nullptr);
        else KillTimer(g_hWnd, TIMER_OUTSIDE_CLICK);
        SyncOutsideMouseHook(g_uiState == UiState::Panel && !g_pinned);
    }
    SyncCycleWidgetWindow(true);
    if (!(g_panelFading && g_fadeDC)) RequestRepaint();
}

static void RequestRepaint(const RECT* dirty) {
    if (g_hWnd) InvalidateRect(g_hWnd, dirty, FALSE);
}

static BYTE LerpByte(BYTE a, BYTE b, double t) {
    return (BYTE)std::clamp((int)std::round(a + (b - a) * t), 0, 255);
}

static void PaintFloatingWindow(HWND hwnd) {
    PAINTSTRUCT ps{};
    HDC hdcScreen = BeginPaint(hwnd, &ps);
    RECT rcClient{};
    GetClientRect(hwnd, &rcClient);
    int w = rcClient.right - rcClient.left;
    int h = rcClient.bottom - rcClient.top;
    if (w <= 0 || h <= 0) {
        EndPaint(hwnd, &ps);
        return;
    }

    UINT dpi = GetDpiForWindow(hwnd);
    FwLayer baseL;
    if (!baseL.Make(hdcScreen, w, h)) {
        EndPaint(hwnd, &ps);
        return;
    }
    HDC memDC = baseL.dc;
    const Gdiplus::REAL sw = (Gdiplus::REAL)std::max(2, DpiScale(2, dpi));

    bool showPill = true;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        showPill = g_settings.showPill;
    }
    bool lineSettled = g_uiState == UiState::Line && !g_expandClock.active && g_expandClock.currentVal < 0.05;

    if (lineSettled) {
        // The edge pill. With the pill turned off it paints nothing at all, so it is invisible
        // and clicks pass through; the panel still opens from the tray icon and the shortcut.
        if (showPill) {
            Gdiplus::Bitmap bm(w, h, w * 4, PixelFormat32bppPARGB, (BYTE*)baseL.bits);
            Gdiplus::Graphics g(&bm);
            g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
            g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);

            PillIndicatorMode indMode;
            {
                std::lock_guard<std::mutex> lk(g_settingsMtx);
                indMode = g_settings.pillIndicatorMode;
            }

            DWORD target = fwc::surface2;
            double k = 0.0;
            if (indMode == PillIndicatorMode::Always) {
                std::wstring fgLow = g_lastFgExe;
                if (!fgLow.empty() && !g_excludedExes.count(fgLow)) {
                    bool fgBlocked = false;
                    {
                        std::lock_guard<std::mutex> lk(g_engineMtx);
                        auto it = g_blocks.find(fgLow);
                        fgBlocked = (it != g_blocks.end() && it->second.blocked);
                    }
                    if (!fgBlocked) {
                        std::lock_guard<std::mutex> lk(g_extFwMtx);
                        auto itExt = g_extFwBlocks.find(fgLow);
                        fgBlocked = (itExt != g_extFwBlocks.end() && itExt->second.dirMask != 0);
                    }
                    target = fgBlocked ? fwc::red : fwc::green;
                    k = 1.0;
                }
            } else {
                k = g_pillPulse.active ? g_pillPulse.intensity : 0.0;
                if (g_pillPulse.kind == PulseKind::AllowedGreen) target = fwc::green;
                else if (g_pillPulse.kind == PulseKind::BlockedRed) target = fwc::red;
            }

            Gdiplus::Color pillCol = Moc(MocMix(fwc::surface2, target, k));
            DockEdge dEdge;
            { std::lock_guard<std::mutex> lk(g_settingsMtx); dEdge = g_settings.dockEdge; }
            if (IsCornerDock(dEdge)) {
                Gdiplus::REAL t = (Gdiplus::REAL)std::min(DpiScale(6, dpi), std::min(w, h));
                Gdiplus::REAL r = t * 0.5f;
                if (dEdge == DockEdge::TopLeft) {
                    FwRound(g, pillCol, 0.0f, 0.0f, (Gdiplus::REAL)w, t, r);
                    FwRound(g, pillCol, 0.0f, 0.0f, t, (Gdiplus::REAL)h, r);
                } else if (dEdge == DockEdge::BottomLeft) {
                    FwRound(g, pillCol, 0.0f, (Gdiplus::REAL)h - t, (Gdiplus::REAL)w, t, r);
                    FwRound(g, pillCol, 0.0f, 0.0f, t, (Gdiplus::REAL)h, r);
                } else {
                    FwRound(g, pillCol, 0.0f, (Gdiplus::REAL)h - t, (Gdiplus::REAL)w, t, r);
                    FwRound(g, pillCol, (Gdiplus::REAL)w - t, 0.0f, t, (Gdiplus::REAL)h, r);
                }
            } else {
                Gdiplus::REAL capR = std::min((Gdiplus::REAL)w, (Gdiplus::REAL)h) * 0.5f;
                FwRound(g, pillCol, 0.0f, 0.0f, (Gdiplus::REAL)w, (Gdiplus::REAL)h, capR);
                if (HasAnyActiveCycle()) {
                    Gdiplus::SolidBrush dotBr(Moc(fwc::yellow));
                    int d = std::max(3, DpiScale(4, dpi));
                    g.FillEllipse(&dotBr, (Gdiplus::REAL)((w - d) / 2.0f), (Gdiplus::REAL)((h - d) / 2.0f),
                                  (Gdiplus::REAL)d, (Gdiplus::REAL)d);
                }
            }
        }
    } else {
        int blockedCount = CountBlockedApps();
        bool glass = TransparencyOn() && !g_panelFading;  // never fade the glass: solid while it moves
        Gdiplus::REAL R = (Gdiplus::REAL)DpiScale(PanelCornerRadius(), dpi);

        // Panel material and its one edge: grey at rest, blue to mauve while the pointer is inside.
        {
            Gdiplus::Bitmap bm(w, h, w * 4, PixelFormat32bppPARGB, (BYTE*)baseL.bits);
            Gdiplus::Graphics gb(&bm);
            gb.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
            gb.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
            Gdiplus::SolidBrush fill(Moc(fwc::base, glass ? 0.55 : 1.0));
            gb.FillRectangle(&fill, 0, 0, w, h);
            if (g_mouseInside) FwGradEdge(gb, 0, 0, (Gdiplus::REAL)w, (Gdiplus::REAL)h, R, sw);
            else FwEdge(gb, Moc(fwc::surface2), 0, 0, (Gdiplus::REAL)w, (Gdiplus::REAL)h, R, sw);
        }

        FwLayer contentL;
        if (contentL.Make(hdcScreen, w, h)) {
            HDC cDC = contentL.dc;
            Gdiplus::Bitmap cbm(w, h, w * 4, PixelFormat32bppPARGB, (BYTE*)contentL.bits);
            Gdiplus::Graphics g(&cbm);
            g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
            g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
            g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

            g_hitRects.clear();
            int pad = DpiScale(14, dpi);
            int y = pad;

            int hdrH = DpiScale(30, dpi);
            g_hitRects.push_back({{0, 0, w - DpiScale(120, dpi), hdrH + pad}, 1, -1, L"", HitRect::HeaderDrag});

            const wchar_t* face = FwTextFace();
            Gdiplus::Font titleFont(face, (Gdiplus::REAL)DpiScale(15, dpi), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
            Gdiplus::Font uiFont(face, (Gdiplus::REAL)DpiScale(13, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
            Gdiplus::Font smallFont(face, (Gdiplus::REAL)DpiScale(11, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
            Gdiplus::Font iconFont(FwIconFace(), (Gdiplus::REAL)DpiScale(13, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

            Gdiplus::SolidBrush textBr(Moc(fwc::text));
            Gdiplus::SolidBrush mutedBr(Moc(fwc::subtext0));
            Gdiplus::SolidBrush dimBr(Moc(fwc::overlay0));
            Gdiplus::SolidBrush crustBr(Moc(fwc::crust));
            Gdiplus::SolidBrush yellowBr(Moc(fwc::yellow));
            Gdiplus::SolidBrush mauveBr(Moc(fwc::mauve));
            Gdiplus::SolidBrush greenBr(Moc(fwc::green));
            Gdiplus::SolidBrush redBr(Moc(fwc::red));

            Gdiplus::StringFormat sfLeft;
            sfLeft.SetAlignment(Gdiplus::StringAlignmentNear);
            sfLeft.SetLineAlignment(Gdiplus::StringAlignmentCenter);
            sfLeft.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);
            sfLeft.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

            Gdiplus::StringFormat sfCenter;
            sfCenter.SetAlignment(Gdiplus::StringAlignmentCenter);
            sfCenter.SetLineAlignment(Gdiplus::StringAlignmentCenter);
            sfCenter.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

            Gdiplus::REAL ctlRad = (Gdiplus::REAL)DpiScale(8, dpi);
            Gdiplus::REAL rowRad = (Gdiplus::REAL)DpiScale(10, dpi);

            // Rest: a light Mocha box with a grey 2px edge. Hover: one step lighter with the
            // blue to mauve edge. On: the blue to mauve fill with dark text.
            auto box = [&](const RECT& r, Gdiplus::REAL rad, bool on, bool hov) {
                Gdiplus::REAL x = (Gdiplus::REAL)r.left, yy = (Gdiplus::REAL)r.top;
                Gdiplus::REAL bw = (Gdiplus::REAL)(r.right - r.left), bh = (Gdiplus::REAL)(r.bottom - r.top);
                if (on) {
                    FwGradFill(g, x, yy, bw, bh, rad);
                    return;
                }
                FwRound(g, hov ? Moc(fwc::surface1, 0.70) : Moc(fwc::surface0, 0.55), x, yy, bw, bh, rad);
                if (hov) FwGradEdge(g, x, yy, bw, bh, rad, sw);
                else FwEdge(g, Moc(fwc::surface2), x, yy, bw, bh, rad, sw);
            };
            auto rf = [](const RECT& r) {
                return Gdiplus::RectF((Gdiplus::REAL)r.left, (Gdiplus::REAL)r.top, (Gdiplus::REAL)(r.right - r.left),
                                      (Gdiplus::REAL)(r.bottom - r.top));
            };

            int dot = DpiScale(8, dpi);
            g.FillEllipse(blockedCount > 0 ? &redBr : &greenBr, (Gdiplus::REAL)pad,
                          (Gdiplus::REAL)(y + (hdrH - dot) / 2), (Gdiplus::REAL)dot, (Gdiplus::REAL)dot);
            Gdiplus::RectF titleRf((Gdiplus::REAL)(pad + DpiScale(16, dpi)), (Gdiplus::REAL)y,
                                   (Gdiplus::REAL)std::max(40, w - DpiScale(120, dpi) - pad - DpiScale(16, dpi)),
                                   (Gdiplus::REAL)hdrH);
            wchar_t hdrTxt[64]{};
            swprintf_s(hdrTxt, L"Firewall  \u00B7  %d blocked", blockedCount);
            g.DrawString(hdrTxt, -1, &titleFont, titleRf, &sfLeft, &textBr);

            int btnSz = DpiScale(28, dpi);
            int bx = w - pad - btnSz;
            auto drawIconBtn = [&](int id, HitRect::Kind kind, const wchar_t* glyph, bool active, const wchar_t* tip) {
                RECT r{bx, y + DpiScale(1, dpi), bx + btnSz, y + DpiScale(1, dpi) + btnSz};
                bool hov = g_hoverHitId == id;
                box(r, ctlRad, active, hov);
                g.DrawString(glyph, -1, &iconFont, rf(r), &sfCenter, active ? &crustBr : (hov ? &textBr : &mutedBr));
                g_hitRects.push_back({r, id, -1, tip, kind});
                bx -= (btnSz + DpiScale(6, dpi));
            };
            drawIconBtn(10, HitRect::SettingsBtn,   L"\xE713", false, L"Settings");
            drawIconBtn(11, HitRect::RestoreAllBtn, L"\xE72C", false, L"Allow every blocked app again");
            drawIconBtn(12, HitRect::PinBtn,        L"\xE718", g_pinned, g_pinned ? L"Pinned open. Click to let it hide again" : L"Keep the panel open");

            y += hdrH + DpiScale(10, dpi);

            struct FilterItem { AppFilter f; const wchar_t* label; int gapAfter; const wchar_t* tip; };
            const wchar_t* userLbl = g_userRunningOnly ? L"Running" : L"User";
            const wchar_t* blkLbl  = g_blockedFirewallOnly ? L"Blocked \u00B7 FW" : L"Blocked";
            FilterItem chips[] = {
                {AppFilter::Allowed,    L"Allowed", 6,  L"Show apps currently allowed online"},
                {AppFilter::Blocked,    blkLbl,     10, L"Blocked apps. Click again to see the apps Windows Firewall blocks"},
                {AppFilter::UserApps,   userLbl,    6,  L"Your apps. Click again to switch between running and all"},
                {AppFilter::SystemApps, L"System",  6,  L"Show Windows system processes"},
                {AppFilter::Excluded,   L"Hidden",  0,  L"Apps you hid from the list"}
            };
            int chipW[5]{};
            int chipPad = DpiScale(20, dpi);
            int chipTotal = 0;
            for (int i = 0; i < 5; ++i) {
                Gdiplus::RectF box2;
                g.MeasureString(chips[i].label, -1, &smallFont, Gdiplus::PointF(0, 0), &sfCenter, &box2);
                chipW[i] = (int)std::ceil(box2.Width);
                chipTotal += chipW[i] + DpiScale(chips[i].gapAfter, dpi);
            }
            int room = w - 2 * pad - chipTotal;
            chipPad = std::clamp(room / 5, DpiScale(10, dpi), DpiScale(20, dpi));
            int fx = pad;
            int chipH = DpiScale(26, dpi);
            for (int i = 0; i < 5; ++i) {
                int cw = chipW[i] + chipPad;
                RECT cr{fx, y, fx + cw, y + chipH};
                bool sel = (g_activeFilter == chips[i].f);
                bool hov = (g_hoverHitId == 20 + i);
                box(cr, ctlRad, sel, hov);
                g.DrawString(chips[i].label, -1, &smallFont, rf(cr), &sfCenter,
                             sel ? &crustBr : (hov ? &textBr : &mutedBr));
                g_hitRects.push_back({cr, 20 + i, (int)chips[i].f, chips[i].tip, HitRect::FilterChip});
                fx += cw + DpiScale(chips[i].gapAfter, dpi);
            }
            y += chipH + DpiScale(10, dpi);

            if (!g_statusBanner.empty()) {
                int banH = DpiScale(26, dpi);
                Gdiplus::RectF stRf((Gdiplus::REAL)pad, (Gdiplus::REAL)y, (Gdiplus::REAL)(w - 2 * pad), (Gdiplus::REAL)banH);
                g.DrawString(g_statusBanner.c_str(), -1, &smallFont, stRf, &sfLeft, &yellowBr);
                y += banH + DpiScale(6, dpi);
            }

            int listTop = y;
            int listBottom = h - pad;
            int listH = std::max(1, listBottom - listTop);
            int rowStride = DpiScale(54, dpi);
            g_lastListH = listH;
            g_lastRowStride = rowStride;
            int rowInnerH = DpiScale(48, dpi);
            int totalH = (int)g_appList.size() * rowStride;
            g_maxScrollPx = std::max(0, totalH - listH);
            if (g_scrollClock.toVal > g_maxScrollPx) g_scrollClock.Start((double)g_maxScrollPx, 60.0);
            int scrollPx = (int)std::round(std::clamp(g_scrollClock.currentVal, 0.0, (double)g_maxScrollPx));

            g.SetClip(Gdiplus::Rect(pad, listTop, w - 2 * pad, listH));
            HRGN gdiClip = CreateRectRgn(pad, listTop, w - pad, listBottom);
            SelectClipRgn(cDC, gdiClip);

            bool lockCrit = false;
            {
                std::lock_guard<std::mutex> lk(g_settingsMtx);
                lockCrit = g_settings.lockSystemProcesses;
            }

            for (int idx = 0; idx < (int)g_appList.size(); ++idx) {
                int ry = listTop + idx * rowStride - scrollPx;
                if (ry + rowInnerH <= listTop || ry >= listBottom) continue;

                const AppEntry& app = g_appList[idx];
                RECT rowRc{pad, ry, w - pad, ry + rowInnerH};
                Gdiplus::REAL rx = (Gdiplus::REAL)rowRc.left, ryf = (Gdiplus::REAL)rowRc.top;
                Gdiplus::REAL rw = (Gdiplus::REAL)(rowRc.right - rowRc.left);
                Gdiplus::REAL rh = (Gdiplus::REAL)(rowRc.bottom - rowRc.top);

                int ctlBase = 1000 + idx * 4;
                bool rowHov = (g_hoverHitId == 2000 + idx) || (g_hoverHitId >= ctlBase && g_hoverHitId <= ctlBase + 3);
                bool isKbSel = (idx == g_kbSelectedIdx);
                FwRound(g, Moc(fwc::surface0, rowHov || isKbSel ? 0.45 : 0.32), rx, ryf, rw, rh, rowRad);
                if (app.isForeground) FwRound(g, Moc(fwc::blue, 0.10), rx, ryf, rw, rh, rowRad);
                if (rowHov || isKbSel) FwGradEdge(g, rx, ryf, rw, rh, rowRad, sw);
                else FwEdge(g, Moc(fwc::surface2, 0.55), rx, ryf, rw, rh, rowRad, sw);
                if (rowRc.top >= listTop && rowRc.bottom <= listBottom) {
                    g_hitRects.push_back({rowRc, 2000 + idx, idx, L"Double-click or right-click for Cycle Mode", HitRect::RowBody});
                }

                HICON hIcon = GetAppIconCached(app.displayPath, dpi);
                if (hIcon) {
                    g.Flush(Gdiplus::FlushIntentionSync);
                    DrawIconEx(cDC, rowRc.left + DpiScale(10, dpi), rowRc.top + DpiScale(14, dpi),
                               hIcon, DpiScale(20, dpi), DpiScale(20, dpi), 0, nullptr, DI_NORMAL);
                }

                int textX = rowRc.left + DpiScale(38, dpi);
                bool critProtected = !app.block.blocked && !app.isExternalBlocked &&
                                     (app.isImmutableLocked || app.isOtherSessionOrUser || (app.isCriticalLocked && lockCrit));
                int rightCtrlW = (app.isExcluded || critProtected) ? DpiScale(90, dpi)
                               : (app.isExternalBlocked ? DpiScale(154, dpi) : DpiScale(182, dpi));
                int textW = std::max<int>(40, (int)rw - DpiScale(38, dpi) - rightCtrlW);

                CycleStatusSnapshot cyc;
                bool hasCyc = !app.isExcluded && !app.isExternalBlocked && GetCycleSnapshot(app.exePath, cyc);
                int nameX = textX;
                int nameW = textW;
                if (hasCyc) {
                    int icSz = DpiScale(15, dpi);
                    Gdiplus::RectF icRf((Gdiplus::REAL)nameX, (Gdiplus::REAL)(rowRc.top + DpiScale(7, dpi)),
                                        (Gdiplus::REAL)icSz, (Gdiplus::REAL)DpiScale(16, dpi));
                    g.DrawString(L"\xE916", -1, &iconFont, icRf, &sfCenter, &mauveBr);
                    nameX += icSz + DpiScale(3, dpi);
                    nameW = std::max(20, nameW - icSz - DpiScale(3, dpi));
                }
                Gdiplus::RectF nameRf((Gdiplus::REAL)nameX, (Gdiplus::REAL)(rowRc.top + DpiScale(6, dpi)),
                                      (Gdiplus::REAL)nameW, (Gdiplus::REAL)DpiScale(18, dpi));
                g.DrawString(app.name.c_str(), -1, &uiFont, nameRf, &sfLeft, &textBr);

                std::wstring sub;
                const Gdiplus::SolidBrush* subBrush = app.isForeground ? &yellowBr : &mutedBr;
                if (hasCyc) {
                    bool isCycPaused = cyc.pausedByFocus || cyc.pausedByUser;
                    if (isCycPaused) {
                        sub = L"Paused";
                    } else {
                        sub = std::wstring(cyc.phase == CyclePhase::Blocked ? L"Blocked \u00B7 " : L"Allowed \u00B7 ")
                            + FormatDurationCompact(cyc.phaseRemainingMs) + L" left";
                    }
                    if (cyc.runMode == CycleRunMode::ForCycles) {
                        sub += L" \u00B7 Cycle " + std::to_wstring(cyc.completedCycles + 1) + L"/" + std::to_wstring(cyc.targetCycles);
                    } else if (cyc.runMode == CycleRunMode::ForDuration) {
                        sub += L" \u00B7 " + FormatDurationCompact(cyc.totalRemainingMs) + L" left";
                    }
                    subBrush = isCycPaused ? &mutedBr : (cyc.phase == CyclePhase::Blocked ? &redBr : &greenBr);
                } else {
                    sub = app.isExcluded ? L"Hidden" : (app.isForeground ? L"Active now" : (app.hasVisibleWindow ? L"Running" : L"Background"));
                    if (app.isExternalBlocked) {
                        const wchar_t* dirTxt = (app.externalBlockMask == 1) ? L"Outbound" : ((app.externalBlockMask == 2) ? L"Inbound" : L"Offline");
                        sub = !app.externalRuleName.empty()
                            ? (std::wstring(L"Rule: ") + app.externalRuleName + L" (" + dirTxt + L")")
                            : (std::wstring(L"Blocked by Windows Firewall (") + dirTxt + L")");
                    } else if (critProtected) {
                        if (app.isImmutableLocked) sub += L" \u00B7 Core / Security Protected";
                        else if (app.isOtherSessionOrUser) sub += L" \u00B7 Session 0 / Other User";
                        else sub += L" \u00B7 Protected";
                    }
                    else if (app.isVpnOrRemote) sub += L" \u00B7 VPN / Remote";
                }
                Gdiplus::RectF subRf((Gdiplus::REAL)textX, (Gdiplus::REAL)(rowRc.top + DpiScale(24, dpi)),
                                     (Gdiplus::REAL)textW, (Gdiplus::REAL)DpiScale(16, dpi));
                g.DrawString(sub.c_str(), -1, &smallFont, subRf, &sfLeft, subBrush);

                int ctlH = DpiScale(26, dpi);
                int ctlY = rowRc.top + (rowInnerH - ctlH) / 2;

                if (app.isExcluded) {
                    int resW = DpiScale(72, dpi);
                    RECT resRc{rowRc.right - resW - DpiScale(10, dpi), ctlY, rowRc.right - DpiScale(10, dpi), ctlY + ctlH};
                    bool hov = g_hoverHitId == ctlBase + 2;
                    box(resRc, ctlRad, false, hov);
                    g.DrawString(L"Restore", -1, &smallFont, rf(resRc), &sfCenter, &textBr);
                    if (resRc.top >= listTop && resRc.bottom <= listBottom) {
                        g_hitRects.push_back({resRc, ctlBase + 2, idx, L"Put this app back on the list", HitRect::RowExclude});
                    }
                } else if (app.isExternalBlocked) {
                    int lockW = DpiScale(136, dpi);
                    RECT lockRc{rowRc.right - lockW - DpiScale(10, dpi), ctlY, rowRc.right - DpiScale(10, dpi), ctlY + ctlH};
                    Gdiplus::RectF lr = rf(lockRc);
                    FwRound(g, Moc(fwc::yellow, 0.10), lr.X, lr.Y, lr.Width, lr.Height, ctlRad);
                    FwEdge(g, Moc(fwc::yellow, 0.70), lr.X, lr.Y, lr.Width, lr.Height, ctlRad, sw);
                    g.DrawString(L"Blocked \u00B7 Firewall", -1, &smallFont, lr, &sfCenter, &yellowBr);
                    if (lockRc.top >= listTop && lockRc.bottom <= listBottom) {
                        g_hitRects.push_back({lockRc, ctlBase + 3, idx, L"Firewall can't change this app. Edit its rule in Windows Defender Firewall.", HitRect::RowExternalLocked});
                    }
                } else if (critProtected) {
                    int togW = DpiScale(64, dpi);
                    RECT togRc{rowRc.right - togW - DpiScale(10, dpi), ctlY,
                               rowRc.right - DpiScale(10, dpi), ctlY + ctlH};
                    Gdiplus::RectF tr = rf(togRc);
                    FwRound(g, Moc(fwc::surface0, 0.40), tr.X, tr.Y, tr.Width, tr.Height, ctlRad);
                    FwEdge(g, Moc(fwc::surface2, 0.70), tr.X, tr.Y, tr.Width, tr.Height, ctlRad, sw);
                    g.DrawString(L"Locked", -1, &smallFont, tr, &sfCenter, &dimBr);
                    if (togRc.top >= listTop && togRc.bottom <= listBottom) {
                        const wchar_t* lockTip = app.isImmutableLocked
                            ? L"Core OS or security software is permanently protected"
                            : (app.isOtherSessionOrUser
                                ? L"Session 0 or other-user process is isolated and locked"
                                : L"System-critical process is locked (Safety settings)");
                        g_hitRects.push_back({togRc, ctlBase, idx, lockTip, HitRect::RowToggle});
                    }
                } else {
                    int exSz = DpiScale(24, dpi);
                    RECT exRc{rowRc.right - DpiScale(176, dpi), ctlY + DpiScale(1, dpi),
                              rowRc.right - DpiScale(176, dpi) + exSz, ctlY + DpiScale(1, dpi) + exSz};
                    bool exHov = g_hoverHitId == ctlBase + 2;
                    box(exRc, ctlRad, false, exHov);
                    g.DrawString(L"\u00D7", -1, &smallFont, rf(exRc), &sfCenter, exHov ? &textBr : &mutedBr);
                    if (exRc.top >= listTop && exRc.bottom <= listBottom) {
                        g_hitRects.push_back({exRc, ctlBase + 2, idx, L"Hide this app from the list", HitRect::RowExclude});
                    }

                    int dirW = DpiScale(72, dpi);
                    RECT dirRc{rowRc.right - DpiScale(146, dpi), ctlY,
                               rowRc.right - DpiScale(146, dpi) + dirW, ctlY + ctlH};
                    bool isBlocked = app.block.blocked;
                    bool dirHov = g_hoverHitId == ctlBase + 1;
                    Gdiplus::RectF dr = rf(dirRc);
                    if (isBlocked) {
                        FwRound(g, Moc(fwc::red, 0.16), dr.X, dr.Y, dr.Width, dr.Height, ctlRad);
                        if (dirHov) FwGradEdge(g, dr.X, dr.Y, dr.Width, dr.Height, ctlRad, sw);
                        else FwEdge(g, Moc(fwc::red, 0.85), dr.X, dr.Y, dr.Width, dr.Height, ctlRad, sw);
                    } else {
                        box(dirRc, ctlRad, false, dirHov);
                    }
                    g.DrawString(DirectionShortLabel(app.block.direction), -1, &smallFont, dr, &sfCenter,
                                 isBlocked ? &redBr : (dirHov ? &textBr : &mutedBr));
                    if (dirRc.top >= listTop && dirRc.bottom <= listBottom) {
                        std::wstring dTip = isBlocked
                            ? (std::wstring(L"Active block: ") + DirectionLabel(app.block.direction))
                            : (std::wstring(L"Mode when blocked: ") + DirectionLabel(app.block.direction) + L" (click to change)");
                        g_hitRects.push_back({dirRc, ctlBase + 1, idx, dTip, HitRect::RowDirection});
                    }

                    int togW = DpiScale(60, dpi);
                    RECT togRc{rowRc.right - togW - DpiScale(10, dpi), ctlY,
                               rowRc.right - DpiScale(10, dpi), ctlY + ctlH};
                    bool allowed = !isBlocked;
                    bool togHov = g_hoverHitId == ctlBase;
                    Gdiplus::RectF tr = rf(togRc);
                    FwRound(g, Moc(allowed ? fwc::green : fwc::red), tr.X, tr.Y, tr.Width, tr.Height, ctlRad);
                    if (togHov) FwGradEdge(g, tr.X, tr.Y, tr.Width, tr.Height, ctlRad, sw);
                    g.DrawString(allowed ? L"Allowed" : L"Blocked", -1, &smallFont, tr, &sfCenter, &crustBr);
                    if (togRc.top >= listTop && togRc.bottom <= listBottom) {
                        std::wstring togTip = allowed
                            ? L"Internet allowed. Click to block this app"
                            : L"Internet blocked. Click to allow this app";
                        if (!allowed && !app.block.blockedChildren.empty()) {
                            togTip += L" (also blocks: ";
                            for (size_t ci = 0; ci < app.block.blockedChildren.size(); ++ci) {
                                if (ci > 0) togTip += L", ";
                                togTip += app.block.blockedChildren[ci];
                            }
                            togTip += L")";
                        }
                        g_hitRects.push_back({togRc, ctlBase, idx, togTip, HitRect::RowToggle});
                    }
                }
            }

            g.Flush(Gdiplus::FlushIntentionSync);
            SelectClipRgn(cDC, nullptr);
            DeleteObject(gdiClip);
            g.ResetClip();

            // The whole window fades as one; the content is always drawn in full.
            BYTE ca = 255;
            if (ca > 0) {
                BLENDFUNCTION cbf{AC_SRC_OVER, 0, ca, AC_SRC_ALPHA};
                GdiAlphaBlend(memDC, 0, 0, w, h, cDC, 0, 0, w, h, cbf);
            }
        }
    }

    bool isLayered = (GetWindowLongPtrW(hwnd, GWL_EXSTYLE) & WS_EX_LAYERED) != 0;
    if (isLayered && g_panelFading) {
        PanelKeepFadeFrame(memDC, w, h);
        PanelFadeFrame(hwnd);
    } else if (isLayered) {
        RECT wr{};
        GetWindowRect(hwnd, &wr);
        POINT ptDst{wr.left, wr.top};
        SIZE sz{w, h};
        POINT ptSrc{0, 0};
        BLENDFUNCTION bf{AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        UpdateLayeredWindow(hwnd, hdcScreen, &ptDst, &sz, memDC, &ptSrc, 0, &bf, ULW_ALPHA);
    } else {
        BitBlt(hdcScreen, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
    }
    EndPaint(hwnd, &ps);
}

// On a cold PC the first open stalled for seconds while the panel's fonts and app icons
// loaded, so the open started late. Load them once, quietly, soon after the mod starts.
static void WarmPanelDraw(HWND hwnd) {
    if (g_uiState != UiState::Line) return;
    UINT dpi = GetDpiForWindow(hwnd);
    {
        Gdiplus::Bitmap bm(96, 32, PixelFormat32bppPARGB);
        Gdiplus::Graphics g(&bm);
        g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
        Gdiplus::SolidBrush br(Gdiplus::Color(255, 255, 255, 255));
        Gdiplus::RectF rf(0, 0, 96, 32);
        const wchar_t* face = FwTextFace();
        Gdiplus::Font f1(face, (Gdiplus::REAL)DpiScale(15, dpi), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::Font f2(face, (Gdiplus::REAL)DpiScale(13, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
        Gdiplus::Font f3(face, (Gdiplus::REAL)DpiScale(11, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
        Gdiplus::Font f4(FwIconFace(), (Gdiplus::REAL)DpiScale(13, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
        for (Gdiplus::Font* f : {&f1, &f2, &f3}) g.DrawString(L"Allowed 0", -1, f, rf, nullptr, &br);
        g.DrawString(L"\xE713\xE72C\xE718\xE916", -1, &f4, rf, nullptr, &br);
    }
    RefreshAppList();
    for (const AppEntry& app : g_appList) GetAppIconCached(app.displayPath, dpi);
}

// ============================================================================
// Tray Icon & Tooltip Helpers
// ============================================================================

constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();

// A rounded square in the blue to mauve gradient with a shield glyph, drawn with GDI so the
// tray never shares the settings window's Direct2D factories. Shared with the app icon.
static HICON MakeBadgeIcon(int size) {
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
    WCHAR face[64]{};
    GetTextFaceW(dc, 64, face);
    if (_wcsicmp(face, L"Segoe Fluent Icons") != 0) {
        SelectObject(dc, oldFont);
        DeleteObject(font);
        font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                           ANTIALIASED_QUALITY, 0, L"Segoe MDL2 Assets");
        oldFont = SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xEA18, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    // Mocha blue 89B4FA to mauve CBA6F7, the glyph alone on a clear background.
    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = base * cov;  // Premultiplied; clear where there is no glyph.
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

static void RemoveTrayIcon() {
    if (g_trayAdded) {
        Shell_NotifyIconW(NIM_DELETE, &g_nid);
        g_trayAdded = false;
    }
    if (g_nid.hIcon) {
        DestroyIcon(g_nid.hIcon);
        g_nid.hIcon = nullptr;
    }
}

static void AddTrayIcon(HWND hwnd) {
    bool want = true;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        want = g_settings.trayIcon;
    }
    if (!want) {
        RemoveTrayIcon();
        return;
    }
    if (g_trayAdded) return;
    g_nid = NOTIFYICONDATAW{};
    g_nid.cbSize = sizeof(g_nid);
    g_nid.hWnd = hwnd;
    g_nid.uID = kTrayId;
    g_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    g_nid.uCallbackMessage = WM_APP_TRAY_CALLBACK;
    g_nid.hIcon = MakeBadgeIcon(GetSystemMetricsForDpi(SM_CXSMICON, GetDpiForWindow(hwnd)));
    if (!g_nid.hIcon) g_nid.hIcon = CopyIcon(LoadIconW(nullptr, IDI_SHIELD));
    wcscpy_s(g_nid.szTip, kTrayTip);
    Shell_NotifyIconW(NIM_DELETE, &g_nid);  // A copy left by a crashed run.
    if (Shell_NotifyIconW(NIM_ADD, &g_nid)) {
        g_trayAdded = true;
        g_nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &g_nid);
    }
}

static void TogglePanelFromTray() {
    if (g_uiState == UiState::Line && GetTickCount() - g_panelClosedTick < 400) return;
    g_uiState = (g_uiState == UiState::Line) ? UiState::Panel : UiState::Line;
    if (g_uiState == UiState::Panel) {
        g_userPinnedFilter = false;
        SyncForegroundStateAndFilter(true);
        RefreshAppList();
    } else {
        g_kbSelectedIdx = -1;
        g_userPinnedFilter = false;
    }
    UpdateWindowGeometry(false);
}

static void ShowTrayContextMenu(HWND hwnd, POINT pt) {
    std::vector<swfset::TrayRow> rows;
    swfset::TrayRow r;
    r.id = 1;
    r.glyph = L"\xE8A7";
    r.label = (g_uiState == UiState::Line) ? L"Open the panel" : L"Close the panel";
    rows.push_back(r);
    r = {};
    r.id = 2;
    r.glyph = L"\xE72C";
    r.label = L"Allow every blocked app";
    r.disabled = CountBlockedApps() == 0;
    rows.push_back(r);
    r = {};
    r.separator = true;
    rows.push_back(r);
    r = {};
    r.id = 3;
    r.glyph = L"\xE718";
    r.label = L"Keep the panel open";
    r.checked = g_pinned;
    rows.push_back(r);
    r = {};
    r.id = 4;
    r.glyph = L"\xE713";
    r.label = L"Settings";
    rows.push_back(r);

    int cmd = swfset::ShowTrayMenu(hwnd, &pt, rows);
    if (cmd == 1) {
        TogglePanelFromTray();
    } else if (cmd == 2) {
        RestoreAllSessionBlocks();
        RefreshAppList();
        RequestRepaint();
    } else if (cmd == 3) {
        g_pinned = !g_pinned;
        if (g_pinned && g_uiState == UiState::Line) {
            g_uiState = UiState::Panel;
            RefreshAppList();
            UpdateWindowGeometry(false);
        }
        RequestRepaint();
    } else if (cmd == 4) {
        OpenWindhawkSettingsUI();
    }
}

static void InitTooltip(HWND hwnd) {
    INITCOMMONCONTROLSEX icc{sizeof(icc), ICC_WIN95_CLASSES};
    InitCommonControlsEx(&icc);
    g_hTooltip = CreateWindowExW(WS_EX_TOPMOST, TOOLTIPS_CLASSW, nullptr,
                                 WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                 hwnd, nullptr, GetModuleHandleW(nullptr), nullptr);
    if (g_hTooltip) SetWindowTheme(g_hTooltip, L"DarkMode_Explorer", nullptr);
    if (g_hTooltip) {
        TOOLINFOW ti{sizeof(ti)};
        ti.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
        ti.hwnd = hwnd;
        ti.uId = (UINT_PTR)hwnd;
        ti.lpszText = const_cast<LPWSTR>(L"");
        SendMessageW(g_hTooltip, TTM_ADDTOOLW, 0, (LPARAM)&ti);
        SendMessageW(g_hTooltip, TTM_SETMAXTIPWIDTH, 0, 320);
        SendMessageW(g_hTooltip, TTM_SETDELAYTIME, TTDT_INITIAL, 300);
    }
}

static void UpdateTooltipText(HWND hwnd, const wchar_t* text) {
    if (!g_hTooltip) return;
    bool showTips = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        showTips = g_settings.showTooltips;
    }
    TOOLINFOW ti{sizeof(ti)};
    ti.hwnd = hwnd;
    ti.uId = (UINT_PTR)hwnd;
    ti.lpszText = const_cast<LPWSTR>((showTips && text) ? text : L"");
    SendMessageW(g_hTooltip, TTM_UPDATETIPTEXTW, 0, (LPARAM)&ti);
}

// ============================================================================
// Window Procedure & Interaction State Machine
// ============================================================================

static const HitRect* HitTestControl(POINT pt) {
    for (auto it = g_hitRects.rbegin(); it != g_hitRects.rend(); ++it) {
        if (PtInRect(&it->rc, pt)) return &(*it);
    }
    return nullptr;
}

static void HandleClickAction(const HitRect& hr) {
    if (hr.kind == HitRect::PinBtn) {
        g_pinned = !g_pinned;
        RequestRepaint();
    } else if (hr.kind == HitRect::RestoreAllBtn) {
        RestoreAllSessionBlocks();
        RefreshAppList();
        RequestRepaint();
    } else if (hr.kind == HitRect::SettingsBtn) {
        OpenWindhawkSettingsUI();
    } else if (hr.kind == HitRect::FilterChip) {
        g_userPinnedFilter = true;
        AppFilter nextF = (AppFilter)hr.rowIndex;
        if (nextF == AppFilter::UserApps && g_activeFilter == AppFilter::UserApps) {
            g_userRunningOnly = !g_userRunningOnly;
        } else if (nextF == AppFilter::Blocked && g_activeFilter == AppFilter::Blocked) {
            g_blockedFirewallOnly = !g_blockedFirewallOnly;
        } else if (nextF == AppFilter::Blocked) {
            g_blockedFirewallOnly = false;
        }
        if (nextF == AppFilter::Blocked && g_blockedFirewallOnly) {
            g_statusBanner = L"Windows Firewall already blocks this app. Change it in Windows Defender Firewall.";
        } else if (nextF == AppFilter::SystemApps) {
            g_statusBanner = L"System apps are for experts. Leave them alone unless you know what each one does.";
        } else {
            g_statusBanner.clear();
        }
        g_activeFilter = nextF;
        g_scrollClock.Start(0.0, 60.0);
        RefreshAppList();
        RequestRepaint();
    } else if (hr.kind == HitRect::RowExternalLocked) {
        g_statusBanner = L"Firewall can't change this app. Edit its rule in Windows Defender Firewall.";
        RequestRepaint();
    } else if (hr.kind == HitRect::RowExclude && hr.rowIndex >= 0 && hr.rowIndex < (int)g_appList.size()) {
        AppEntry app = g_appList[hr.rowIndex];
        if (app.isExternalBlocked) {
            g_statusBanner = L"Firewall can't change this app. Edit its rule in Windows Defender Firewall.";
            RequestRepaint();
            return;
        }
        std::wstring low = ToLower(app.displayPath);
        if (app.isExcluded) {
            g_excludedExes.erase(low);
            LogAudit(L"UNEXCLUDE " + app.displayPath);
        } else {
            ApplyAllow(app.displayPath);
            g_excludedExes.insert(low);
            LogAudit(L"EXCLUDE " + app.displayPath);
        }
        SaveExcludedApps();
        RefreshAppList();
        RequestRepaint();
    } else if (hr.kind == HitRect::RowToggle && hr.rowIndex >= 0 && hr.rowIndex < (int)g_appList.size()) {
        AppEntry app = g_appList[hr.rowIndex];
        if (app.isExternalBlocked) {
            g_statusBanner = L"Firewall can't change this app. Edit its rule in Windows Defender Firewall.";
            RequestRepaint();
            return;
        }
        CycleStatusSnapshot cyc;
        if (GetCycleSnapshot(app.exePath, cyc)) {
            if (!FwConfirm(L"Stop the timer?",
                           L"This app is switching between blocked and allowed on a timer. Stop the timer and "
                           L"change it by hand?",
                           L"Stop timer", L"Keep timer", false, true))
                return;
            StopCycleForApp(app.displayPath, false);
        }
        bool blockedNow = false;
        {
            std::lock_guard<std::mutex> lk(g_engineMtx);
            auto it = g_blocks.find(app.exePath);
            if (it != g_blocks.end() && it->second.blocked) blockedNow = true;
            else {
                for (const auto& bkv : g_blocks) {
                    if (bkv.second.blocked && bkv.second.blockedChildPaths.count(app.exePath)) {
                        blockedNow = true;
                        break;
                    }
                }
            }
        }
        if (blockedNow) {
            ApplyAllow(app.displayPath);
        } else {
            ModSettings s;
            {
                std::lock_guard<std::mutex> lk(g_settingsMtx);
                s = g_settings;
            }
            std::wstring low = ToLower(app.displayPath);
            auto itDir = g_pendingDirs.find(low);
            Direction dir = (itDir != g_pendingDirs.end()) ? itDir->second : s.defaultDirection;
            ApplyBlock(app.displayPath, dir, s.includeChildProcesses, true);
        }
        RefreshAppList();
        RequestRepaint();
    } else if (hr.kind == HitRect::RowDirection && hr.rowIndex >= 0 && hr.rowIndex < (int)g_appList.size()) {
        AppEntry app = g_appList[hr.rowIndex];
        if (app.isExternalBlocked) {
            g_statusBanner = L"Firewall can't change this app. Edit its rule in Windows Defender Firewall.";
            RequestRepaint();
            return;
        }
        std::wstring low = ToLower(app.displayPath);
        Direction nextDir = (Direction)(((int)app.block.direction + 1) % 3);
        g_pendingDirs[low] = nextDir;
        if (app.block.blocked) {
            bool isDirectRoot = false;
            {
                std::lock_guard<std::mutex> lk(g_engineMtx);
                isDirectRoot = (g_blocks.find(low) != g_blocks.end());
            }
            if (!isDirectRoot) ApplyAllow(app.displayPath);
            ApplyBlock(app.displayPath, nextDir, app.block.includeChildProcesses, true);
        }
        RefreshAppList();
        RequestRepaint();
    }
}


// ============================================================================
// Cycle Mode Popup Dialog (Pure GDI+ #000000 Inputs, Dirty Rects, Clock Sync)
// ============================================================================

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif
#ifndef DWMWA_SYSTEMBACKDROP_TYPE
#define DWMWA_SYSTEMBACKDROP_TYPE 38
#endif
#ifndef DWMSBT_TRANSIENTWINDOW
#define DWMSBT_TRANSIENTWINDOW 3
#endif

constexpr wchar_t kCycleRunDropClass[] = L"SeamlessFirewall_CycleRunDrop_v1";
constexpr UINT_PTR TIMER_CYCLE_POPUP_ANIM  = 77;
constexpr UINT_PTR TIMER_CYCLE_POPUP_CARET = 78;
constexpr UINT_PTR TIMER_CYCLE_POPUP_OPEN   = 79;
constexpr UINT_PTR TIMER_CYCLE_POPUP_RESIZE = 80;
constexpr UINT_PTR TIMER_CYCLE_CLOCK_COMMIT = 81;
constexpr uint64_t kCycleMaxMs = 99ULL * 3600000ULL;

enum CycleFieldId {
    CF_NONE = -1,
    CF_BLK_H = 0, CF_BLK_M, CF_BLK_S, CF_BLK_MS,
    CF_ALW_H,     CF_ALW_M, CF_ALW_S, CF_ALW_MS,
    CF_RUN_CYC,
    CF_RUN_H,     CF_RUN_M, CF_RUN_S, CF_RUN_MS,
    CF_CLK_H,     CF_CLK_M,
    CF_COUNT
};

struct DurationGroupState {
    std::wstring txtH = L"0";
    std::wstring txtM = L"00";
    std::wstring txtS = L"10";
    std::wstring txtMs = L"000";

    RECT rcH{};
    RECT rcM{};
    RECT rcS{};
    RECT rcMs{};

    bool showHours = false;
    uint64_t totalMs = 0;

    double animVal = 0.0;
    LARGE_INTEGER animStart{};
    bool animating = false;
};

struct CycleHitRect {
    RECT rc{};
    int id = 0;
    enum Kind {
        None = 0, InputBox, RunDropdown, SyncClockToggle, ClockFormat12h, FocusToggle, AllowUnfocusedToggle, CancelBtn, PrimaryBtn
    } kind = None;
    int fieldId = CF_NONE;
};

struct CyclePopupState {
    std::wstring exePath;
    std::wstring displayPath;
    std::wstring appName;
    Direction direction = Direction::FullyOffline;
    bool isRunning = false;
    bool hasBackdropBlur = false;
    bool showMs = false;

    HWND hwnd = nullptr;
    HWND hRunDrop = nullptr;
    int runDropHoverIdx = -1;
    bool openingRunDrop = false;
    bool modalOpen = false;

    DurationGroupState blockGrp;
    DurationGroupState allowGrp;
    DurationGroupState runTimeGrp;

    std::wstring runCyclesTxt = L"5";
    RECT rcRunCycles{};
    RECT rcRunDrop{};

    bool syncWithWindows = false;
    bool clock12Hour = true;
    bool clockIsPm = false;
    bool clockEditing = false;
    std::wstring clkHourTxt = L"12";
    std::wstring clkMinTxt  = L"00";
    RECT rcClkH{};
    RECT rcClkM{};
    RECT rcClkAmPm{};
    uint64_t computedClockMs = 0;
    uint64_t computedTargetUtcMs = 0;

    int runModeIdx = 0; // 0=Until stopped, 1=For N cycles, 2=For a set time
    bool focusedOnly = true;
    bool allowWhenUnfocused = true;

    int focusedField = CF_BLK_S;
    bool replaceOnType = false;
    bool caretVisible = true;

    bool valid = true;
    bool warnSub1s = false;
    std::wstring summaryText;

    int hoverId = -1;
    RECT hoverRc{};
    std::vector<CycleHitRect> hits;
    RECT rcSummary{};
    RECT rcBtnPrimary{};
    bool sideBySideBlockAllow = false;
    MotionClock openClock;
    MotionClock heightClock;
    int targetX = 0;
    int targetY = 0;
    int targetW = 0;
    int targetH = 0;
};

static CyclePopupState* g_cyclePopupState = nullptr;
static bool g_cyclePopupInside = false;

static uint64_t ParseDigitsU64(const std::wstring& s) {
    if (s.empty()) return 0ULL;
    return (uint64_t)_wcstoui64(s.c_str(), nullptr, 10);
}

static void DecomposeMs(uint64_t ms, uint64_t& outH, uint64_t& outM, uint64_t& outS, uint64_t& outMs) {
    if (ms > kCycleMaxMs) ms = kCycleMaxMs;
    outH = ms / 3600000ULL;
    ms %= 3600000ULL;
    outM = ms / 60000ULL;
    ms %= 60000ULL;
    outS = ms / 1000ULL;
    outMs = ms % 1000ULL;
}

static uint64_t ComputeDurationGroupRawMs(const DurationGroupState& grp, bool showMs) {
    uint64_t h = grp.showHours ? ParseDigitsU64(grp.txtH) : 0ULL;
    uint64_t m = ParseDigitsU64(grp.txtM);
    uint64_t s = ParseDigitsU64(grp.txtS);
    uint64_t ms = showMs ? ParseDigitsU64(grp.txtMs) : 0ULL;
    uint64_t total = h * 3600000ULL + m * 60000ULL + s * 1000ULL + ms;
    return std::min<uint64_t>(total, kCycleMaxMs);
}

static void WriteDurationGroupMs(DurationGroupState& grp, uint64_t totalMs, bool animateMerge) {
    if (totalMs > kCycleMaxMs) totalMs = kCycleMaxMs;
    uint64_t nh = 0, nm = 0, ns = 0, nms = 0;
    DecomposeMs(totalMs, nh, nm, ns, nms);
    grp.totalMs = totalMs;
    grp.showHours = (nh > 0);

    wchar_t bufM[16]{}, bufS[16]{}, bufMs[16]{};
    swprintf_s(bufM, L"%02llu", (unsigned long long)nm);
    swprintf_s(bufS, L"%02llu", (unsigned long long)ns);
    swprintf_s(bufMs, L"%03llu", (unsigned long long)nms);

    grp.txtH = grp.showHours ? std::to_wstring(nh) : L"0";
    grp.txtM = bufM;
    grp.txtS = bufS;
    grp.txtMs = bufMs;

    if (animateMerge) {
        QueryPerformanceCounter(&grp.animStart);
        grp.animVal = 1.0;
        grp.animating = true;
    }
}

static int ClockTo24Hour(uint64_t hh, bool is12h, bool isPm) {
    if (!is12h) return (hh <= 23) ? (int)hh : -1;
    if (hh < 1 || hh > 12) return -1;
    if (hh == 12) return isPm ? 12 : 0;
    return isPm ? (int)(hh + 12) : (int)hh;
}

static void PopulateClockFromWindows(CyclePopupState* st) {
    if (!st) return;
    SYSTEMTIME lt{};
    GetLocalTime(&lt);
    wchar_t bH[8]{}, bM[8]{};
    if (st->clock12Hour) {
        st->clockIsPm = (lt.wHour >= 12);
        int h12 = lt.wHour % 12;
        if (h12 == 0) h12 = 12;
        swprintf_s(bH, L"%02d", h12);
    } else {
        swprintf_s(bH, L"%02u", (unsigned)lt.wHour);
    }
    swprintf_s(bM, L"%02u", (unsigned)lt.wMinute);
    st->clkHourTxt = bH;
    st->clkMinTxt = bM;
}

static void LayoutCyclePopup(CyclePopupState* st, UINT dpi, bool animateResize = false);

static bool AutoCarryDurationGroup(CyclePopupState* st, DurationGroupState& grp) {
    uint64_t h = grp.showHours ? ParseDigitsU64(grp.txtH) : 0ULL;
    uint64_t m = ParseDigitsU64(grp.txtM);
    uint64_t s = ParseDigitsU64(grp.txtS);
    uint64_t ms = (st && st->showMs) ? ParseDigitsU64(grp.txtMs) : 0ULL;

    uint64_t total = std::min<uint64_t>(kCycleMaxMs, h * 3600000ULL + m * 60000ULL + s * 1000ULL + ms);
    uint64_t nh = 0, nm = 0, ns = 0, nms = 0;
    DecomposeMs(total, nh, nm, ns, nms);

    bool needsCarry = (ms > 999 || s > 59 || m > 59 || h != nh || grp.showHours != (nh > 0));
    bool visChanged = (grp.showHours != (nh > 0));

    WriteDurationGroupMs(grp, total, needsCarry);
    if (needsCarry && st && st->hwnd) {
        SetTimer(st->hwnd, TIMER_CYCLE_POPUP_ANIM, 16, nullptr);
    }
    if (visChanged && st && st->hwnd) {
        LayoutCyclePopup(st, GetDpiForWindow(st->hwnd));
    }
    return needsCarry;
}

static std::wstring* GetFieldTextPtr(CyclePopupState* st, int fieldId, RECT* outRc = nullptr) {
    if (!st) return nullptr;
    auto ret = [&](std::wstring& s, const RECT& r) -> std::wstring* {
        if (outRc) *outRc = r;
        return &s;
    };
    switch (fieldId) {
        case CF_BLK_H:  return ret(st->blockGrp.txtH, st->blockGrp.rcH);
        case CF_BLK_M:  return ret(st->blockGrp.txtM, st->blockGrp.rcM);
        case CF_BLK_S:  return ret(st->blockGrp.txtS, st->blockGrp.rcS);
        case CF_BLK_MS: return ret(st->blockGrp.txtMs, st->blockGrp.rcMs);
        case CF_ALW_H:  return ret(st->allowGrp.txtH, st->allowGrp.rcH);
        case CF_ALW_M:  return ret(st->allowGrp.txtM, st->allowGrp.rcM);
        case CF_ALW_S:  return ret(st->allowGrp.txtS, st->allowGrp.rcS);
        case CF_ALW_MS: return ret(st->allowGrp.txtMs, st->allowGrp.rcMs);
        case CF_RUN_CYC: return ret(st->runCyclesTxt, st->rcRunCycles);
        case CF_RUN_H:  return ret(st->runTimeGrp.txtH, st->runTimeGrp.rcH);
        case CF_RUN_M:  return ret(st->runTimeGrp.txtM, st->runTimeGrp.rcM);
        case CF_RUN_S:  return ret(st->runTimeGrp.txtS, st->runTimeGrp.rcS);
        case CF_RUN_MS: return ret(st->runTimeGrp.txtMs, st->runTimeGrp.rcMs);
        case CF_CLK_H:  return ret(st->clkHourTxt, st->rcClkH);
        case CF_CLK_M:  return ret(st->clkMinTxt, st->rcClkM);
    }
    return nullptr;
}

static DurationGroupState* GetDurationGroupByField(CyclePopupState* st, int fieldId) {
    if (!st) return nullptr;
    if (fieldId >= CF_BLK_H && fieldId <= CF_BLK_MS) return &st->blockGrp;
    if (fieldId >= CF_ALW_H && fieldId <= CF_ALW_MS) return &st->allowGrp;
    if (fieldId >= CF_RUN_H && fieldId <= CF_RUN_MS) return &st->runTimeGrp;
    return nullptr;
}

static const wchar_t* RunModeDisplayLabel(int idx) {
    switch (idx) {
        case 1: return L"For N cycles";
        case 2: return L"For a set time";
        default: return L"Until stopped";
    }
}



static uint64_t ComputeNext12hDiffSeconds(uint64_t hh, uint64_t mm, int nowSec, bool& outIsPm) {
    int hAm = (hh == 12) ? 0 : (int)hh;
    int hPm = (hh == 12) ? 12 : (int)(hh + 12);
    int secAm = hAm * 3600 + (int)mm * 60;
    int secPm = hPm * 3600 + (int)mm * 60;
    uint64_t waitAm = (secAm > nowSec) ? (uint64_t)(secAm - nowSec) : (uint64_t)(secAm + 86400 - nowSec);
    uint64_t waitPm = (secPm > nowSec) ? (uint64_t)(secPm - nowSec) : (uint64_t)(secPm + 86400 - nowSec);
    if (waitAm <= waitPm) {
        outIsPm = false;
        return waitAm;
    }
    outIsPm = true;
    return waitPm;
}

static void AutoCalculateAmPm(CyclePopupState* st) {
    if (!st || !st->clock12Hour) return;
    uint64_t hh = ParseDigitsU64(st->clkHourTxt);
    uint64_t mm = ParseDigitsU64(st->clkMinTxt);
    if (hh < 1 || hh > 12 || mm > 59) return;
    SYSTEMTIME ltNow{};
    GetLocalTime(&ltNow);
    int nowSec = ltNow.wHour * 3600 + ltNow.wMinute * 60 + ltNow.wSecond;
    ComputeNext12hDiffSeconds(hh, mm, nowSec, st->clockIsPm);
}

static void CommitClockFields(CyclePopupState* st) {
    if (!st) return;
    st->clockEditing = false;
    if (st->hwnd) KillTimer(st->hwnd, TIMER_CYCLE_CLOCK_COMMIT);
    uint64_t hh = ParseDigitsU64(st->clkHourTxt);
    uint64_t mm = ParseDigitsU64(st->clkMinTxt);
    bool hValid = st->clock12Hour ? (hh >= 1 && hh <= 12) : (hh <= 23);
    bool mValid = (mm <= 59);
    if (hValid && !st->clkHourTxt.empty()) {
        wchar_t bH[8]{};
        swprintf_s(bH, L"%02llu", (unsigned long long)hh);
        st->clkHourTxt = bH;
    }
    if (mValid && !st->clkMinTxt.empty()) {
        wchar_t bM[8]{};
        swprintf_s(bM, L"%02llu", (unsigned long long)mm);
        st->clkMinTxt = bM;
    }
    AutoCalculateAmPm(st);
    if (st->hwnd) {
        if (st->rcClkH.right > st->rcClkH.left) InvalidateRect(st->hwnd, &st->rcClkH, FALSE);
        if (st->rcClkM.right > st->rcClkM.left) InvalidateRect(st->hwnd, &st->rcClkM, FALSE);
    }
}

static void UpdateCyclePopupSummary(CyclePopupState* st, bool repaintSummary = true) {
    if (!st) return;
    uint64_t bMs = ComputeDurationGroupRawMs(st->blockGrp, st->showMs);
    uint64_t aMs = ComputeDurationGroupRawMs(st->allowGrp, st->showMs);
    st->blockGrp.totalMs = bMs;
    st->allowGrp.totalMs = aMs;

    st->warnSub1s = false;
    st->computedClockMs = 0;
    st->computedTargetUtcMs = 0;

    bool prevValid = st->valid;
    if (bMs < 100 || aMs < 100) {
        st->valid = false;
        st->summaryText = L"Min 100 ms";
    } else if (st->runModeIdx == 1 && ParseDigitsU64(st->runCyclesTxt) < 1) {
        st->valid = false;
        st->summaryText = L"Min 1 cycle";
    } else if (st->runModeIdx == 2 && st->syncWithWindows) {
        uint64_t hh = ParseDigitsU64(st->clkHourTxt);
        uint64_t mm = ParseDigitsU64(st->clkMinTxt);
        if (st->clockEditing) {
            if (st->clock12Hour && hh >= 1 && hh <= 12 && mm <= 59) {
                bool prevPm = st->clockIsPm;
                AutoCalculateAmPm(st);
                if (prevPm != st->clockIsPm && st->hwnd && st->rcClkAmPm.right > st->rcClkAmPm.left) {
                    InvalidateRect(st->hwnd, &st->rcClkAmPm, FALSE);
                }
            }
            st->valid = true;
            st->summaryText = L"Editing target time...";
        } else if (st->clock12Hour) {
            if (hh < 1 || hh > 12 || mm > 59) {
                st->valid = false;
                st->summaryText = L"Use 01\u201312 : 00\u201359";
            } else {
                SYSTEMTIME ltNow{};
                GetLocalTime(&ltNow);
                int nowSec = ltNow.wHour * 3600 + ltNow.wMinute * 60 + ltNow.wSecond;
                uint64_t diffSec = ComputeNext12hDiffSeconds(hh, mm, nowSec, st->clockIsPm);
                uint64_t diffMs = diffSec * 1000ULL;
                st->computedClockMs = diffMs;
                st->computedTargetUtcMs = UtcNowMs() + diffMs;
                st->valid = true;
                if (bMs < 1000 || aMs < 1000) st->warnSub1s = true;
                wchar_t tBuf[24]{};
                swprintf_s(tBuf, L"%02llu:%02llu %s", (unsigned long long)hh, (unsigned long long)mm, st->clockIsPm ? L"PM" : L"AM");
                st->summaryText = L"Blocked " + FormatDurationCompact(bMs) + L" \u2192 Allowed " + FormatDurationCompact(aMs) + L" \u00b7 until " + tBuf;
                if (st->warnSub1s) st->summaryText += L"  (\u26a0 < 1s)";
                if (st->hwnd && st->rcClkAmPm.right > st->rcClkAmPm.left) InvalidateRect(st->hwnd, &st->rcClkAmPm, FALSE);
            }
        } else {
            if (hh > 23 || mm > 59) {
                st->valid = false;
                st->summaryText = L"Use 00\u201323 : 00\u201359";
            } else {
                SYSTEMTIME ltNow{};
                GetLocalTime(&ltNow);
                int nowSec = ltNow.wHour * 3600 + ltNow.wMinute * 60 + ltNow.wSecond;
                int tgtSec = (int)hh * 3600 + (int)mm * 60;
                if (tgtSec <= nowSec) {
                    st->valid = false;
                    st->summaryText = L"Enter a future time";
                } else {
                    uint64_t diffMs = (uint64_t)(tgtSec - nowSec) * 1000ULL;
                    st->computedClockMs = diffMs;
                    st->computedTargetUtcMs = UtcNowMs() + diffMs;
                    st->valid = true;
                    if (bMs < 1000 || aMs < 1000) st->warnSub1s = true;
                    wchar_t tBuf[24]{};
                    swprintf_s(tBuf, L"%02llu:%02llu", (unsigned long long)hh, (unsigned long long)mm);
                    st->summaryText = L"Blocked " + FormatDurationCompact(bMs) + L" \u2192 Allowed " + FormatDurationCompact(aMs) + L" \u00b7 until " + tBuf;
                    if (st->warnSub1s) st->summaryText += L"  (\u26a0 < 1s)";
                }
            }
        }
    } else if (st->runModeIdx == 2 && ComputeDurationGroupRawMs(st->runTimeGrp, st->showMs) < 100) {
        st->valid = false;
        st->summaryText = L"Min 100 ms";
    } else {
        st->valid = true;
        if (bMs < 1000 || aMs < 1000) st->warnSub1s = true;
        st->summaryText = L"Blocked " + FormatDurationCompact(bMs) + L" \u2192 Allowed " + FormatDurationCompact(aMs);
        if (st->runModeIdx == 1) {
            uint64_t cnt = ParseDigitsU64(st->runCyclesTxt);
            st->summaryText += L" \u00b7 " + std::to_wstring(cnt) + (cnt == 1 ? L" cycle" : L" cycles");
        } else if (st->runModeIdx == 2) {
            uint64_t rMs = ComputeDurationGroupRawMs(st->runTimeGrp, st->showMs);
            st->summaryText += L" \u00b7 for " + FormatDurationCompact(rMs);
        }
        if (st->warnSub1s) st->summaryText += L"  (\u26a0 < 1s)";
    }

    if (repaintSummary && st->hwnd) {
        InvalidateRect(st->hwnd, &st->rcSummary, FALSE);
        if (prevValid != st->valid) {
            InvalidateRect(st->hwnd, &st->rcBtnPrimary, FALSE);
        }
    }
}

static void LayoutCyclePopup(CyclePopupState* st, UINT dpi, bool animateResize) {
    if (!st || !st->hwnd) return;
    int pad = DpiScale(16, dpi);
    int boxH = DpiScale(36, dpi);
    int boxGap = DpiScale(10, dpi);
    int secGap = DpiScale(14, dpi);
    int lblH = DpiScale(18, dpi);
    int lblGap = DpiScale(6, dpi);
    int subLblH = DpiScale(14, dpi);
    int subLblGap = DpiScale(3, dpi);
    int titleH = DpiScale(22, dpi);
    int titleGap = DpiScale(14, dpi);

    int boxW = DpiScale(64, dpi);
    int msW  = DpiScale(70, dpi);
    int hrsW = DpiScale(48, dpi);

    st->sideBySideBlockAllow = (!st->showMs && !st->blockGrp.showHours && !st->allowGrp.showHours);
    int colGap = DpiScale(20, dpi);
    int twoBoxW = boxW * 2 + boxGap;
    bool anyHours = st->blockGrp.showHours || st->allowGrp.showHours ||
                    (st->runModeIdx == 2 && !st->syncWithWindows && st->runTimeGrp.showHours);
    int baseGroupW = st->sideBySideBlockAllow
        ? (twoBoxW * 2 + colGap)
        : (boxW + boxGap + boxW + (st->showMs ? (boxGap + msW) : 0));
    int maxGroupW = st->sideBySideBlockAllow
        ? std::max<int>(baseGroupW, (st->runModeIdx == 2 && !st->syncWithWindows && st->runTimeGrp.showHours) ? (hrsW + boxGap + twoBoxW) : baseGroupW)
        : (baseGroupW + (anyHours ? (hrsW + boxGap) : 0));
    int winW = pad * 2 + std::max<int>(DpiScale(240, dpi), maxGroupW);

    auto layoutDurationAt = [&](DurationGroupState& grp, int xStart, int yTop) -> int {
        int x = xStart;
        grp.rcH  = grp.showHours ? RECT{x, yTop, x + hrsW, yTop + boxH} : RECT{0, 0, 0, 0};
        if (grp.showHours) x += hrsW + boxGap;
        grp.rcM  = {x, yTop, x + boxW, yTop + boxH};
        x += boxW + boxGap;
        grp.rcS  = {x, yTop, x + boxW, yTop + boxH};
        x += boxW + boxGap;
        grp.rcMs = st->showMs ? RECT{x, yTop, x + msW, yTop + boxH} : RECT{0, 0, 0, 0};
        return yTop + boxH + subLblGap + subLblH;
    };
    auto layoutDuration = [&](DurationGroupState& grp, int yTop) -> int {
        return layoutDurationAt(grp, pad, yTop);
    };

    int y = pad + titleH + titleGap;
    if (st->sideBySideBlockAllow) {
        y += lblH + lblGap;
        int allowX = pad + twoBoxW + colGap;
        layoutDurationAt(st->blockGrp, pad, y);
        y = layoutDurationAt(st->allowGrp, allowX, y) + secGap;
    } else {
        y += lblH + lblGap;
        y = layoutDuration(st->blockGrp, y) + secGap;
        y += lblH + lblGap;
        y = layoutDuration(st->allowGrp, y) + secGap;
    }

    y += lblH + lblGap;
    st->rcRunDrop = {pad, y, winW - pad, y + boxH};
    y += boxH;

    if (st->runModeIdx == 1) {
        y += boxGap;
        st->rcRunCycles = {pad, y, pad + DpiScale(92, dpi), y + boxH};
        y += boxH;
    } else if (st->runModeIdx == 2) {
        y += DpiScale(10, dpi);
        y += DpiScale(22, dpi) + DpiScale(8, dpi); // Sync with Windows clock row
        if (st->syncWithWindows) {
            st->rcClkH = {pad, y, pad + boxW, y + boxH};
            st->rcClkM = {pad + boxW + DpiScale(16, dpi), y, pad + boxW * 2 + DpiScale(16, dpi), y + boxH};
            st->rcClkAmPm = st->clock12Hour
                ? RECT{st->rcClkM.right + DpiScale(10, dpi), y, st->rcClkM.right + DpiScale(60, dpi), y + boxH}
                : RECT{0, 0, 0, 0};
            y += boxH + subLblGap + subLblH;
        } else {
            y = layoutDuration(st->runTimeGrp, y);
        }
    }

    y += DpiScale(16, dpi);
    int chkH = DpiScale(22, dpi);
    y += chkH + DpiScale(8, dpi);
    if (st->focusedOnly) {
        y += chkH + DpiScale(8, dpi);
    }

    int sumH = DpiScale(16, dpi);
    st->rcSummary = {pad, y, winW - pad, y + sumH};
    y += sumH + DpiScale(14, dpi);

    int btnW = DpiScale(88, dpi);
    int btnH = DpiScale(32, dpi);
    st->rcBtnPrimary = {winW - pad - btnW, y, winW - pad, y + btnH};
    int totalH = y + btnH + pad;

    RECT curRc{};
    GetWindowRect(st->hwnd, &curRc);
    HMONITOR mon = MonitorFromWindow(st->hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    int edgeOffPx = 0;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        edgeOffPx = DpiScale(g_settings.panelEdgeOffsetPx, dpi);
    }
    int minX = (int)mi.rcWork.left + edgeOffPx;
    int maxX = std::max(minX, (int)mi.rcWork.right - edgeOffPx - winW);
    int minY = (int)mi.rcWork.top + edgeOffPx;
    int maxY = std::max(minY, (int)mi.rcWork.bottom - edgeOffPx - totalH);
    int nx = std::clamp((int)curRc.left, minX, maxX);
    int ny = std::clamp((int)curRc.top, minY, maxY);
    st->targetX = nx;
    st->targetY = ny;
    st->targetW = winW;
    st->targetH = totalH;
    if (animateResize && IsWindowVisible(st->hwnd)) {
        int prevH = curRc.bottom - curRc.top;
        if (std::abs(prevH - totalH) > 1) {
            st->heightClock.Init();
            st->heightClock.currentVal = (double)prevH;
            st->heightClock.Start((double)totalH, 160.0);
            SetTimer(st->hwnd, TIMER_CYCLE_POPUP_RESIZE, 10, nullptr);
        } else {
            SetWindowPos(st->hwnd, HWND_TOPMOST, nx, ny, winW, totalH, SWP_NOACTIVATE);
        }
    } else {
        SetWindowPos(st->hwnd, HWND_TOPMOST, nx, ny, winW, totalH, SWP_NOACTIVATE);
    }
    InvalidateRect(st->hwnd, nullptr, FALSE);
}

static void PaintCyclePopup(HWND hwnd, CyclePopupState* st) {
    PAINTSTRUCT ps{};
    HDC hdcScreen = BeginPaint(hwnd, &ps);
    RECT rc{};
    GetClientRect(hwnd, &rc);
    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;
    if (w <= 0 || h <= 0 || !st) {
        EndPaint(hwnd, &ps);
        return;
    }

    UINT dpi = GetDpiForWindow(hwnd);
    HDC memDC = CreateCompatibleDC(hdcScreen);
    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP hBmp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ oldBmp = SelectObject(memDC, hBmp);
    if (bits) memset(bits, 0, (size_t)w * (size_t)h * 4);

    if (bits) {
        // Premultiplied drawing, so the glass under the extended frame shows through the fill.
        Gdiplus::Bitmap canvas(w, h, w * 4, PixelFormat32bppPARGB, (BYTE*)bits);
        Gdiplus::Graphics g(&canvas);
        g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
        g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
        g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

        // Frosted Mocha like Explorer while the glass is on, solid Mocha otherwise; one 2px edge on
        // the live window radius, grey at rest and blue to mauve while the pointer is inside.
        g.Clear(Moc(fwc::base, st->hasBackdropBlur ? 0.55 : 1.0));
        {
            Gdiplus::REAL winR = (Gdiplus::REAL)DpiScale(PanelCornerRadius(), dpi);
            Gdiplus::REAL ew = (Gdiplus::REAL)std::max(2, DpiScale(2, dpi));
            if (g_cyclePopupInside)
                FwGradEdge(g, 0, 0, (Gdiplus::REAL)w, (Gdiplus::REAL)h, winR, ew);
            else
                FwEdge(g, Moc(fwc::surface2), 0, 0, (Gdiplus::REAL)w, (Gdiplus::REAL)h, winR, ew);
        }

        const wchar_t* face = FwTextFace();
        Gdiplus::Font titleFont(face, (Gdiplus::REAL)DpiScale(15, dpi), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::Font secFont(face, (Gdiplus::REAL)DpiScale(12, dpi), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::Font numFont(face, (Gdiplus::REAL)DpiScale(14, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
        Gdiplus::Font uiFont(face, (Gdiplus::REAL)DpiScale(12, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
        Gdiplus::Font subFont(face, (Gdiplus::REAL)DpiScale(11, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
        Gdiplus::Font glyphFont(FwIconFace(), (Gdiplus::REAL)DpiScale(10, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

        Gdiplus::SolidBrush whiteBr(Moc(fwc::text));
        Gdiplus::SolidBrush labelBr(Moc(fwc::subtext1));
        Gdiplus::SolidBrush mutedBr(Moc(fwc::overlay2));
        Gdiplus::SolidBrush warnBr(Moc(fwc::yellow));
        Gdiplus::SolidBrush crustBr(Moc(fwc::crust));

        Gdiplus::SolidBrush inputBr(Moc(fwc::mantle, 0.85));
        Gdiplus::SolidBrush surfRestBr(Moc(fwc::surface0, 0.85));
        Gdiplus::SolidBrush surfHoverBr(Moc(fwc::surface1, 0.85));
        Gdiplus::REAL ew2 = (Gdiplus::REAL)std::max(2, DpiScale(2, dpi));
        // One 2px edge per box: grey at rest, the gradient on hover or focus, so nothing jumps.
        auto edge = [&](const RECT& r, Gdiplus::REAL rr, bool lit) {
            Gdiplus::REAL x = (Gdiplus::REAL)r.left, y = (Gdiplus::REAL)r.top;
            Gdiplus::REAL bw = (Gdiplus::REAL)(r.right - r.left), bh = (Gdiplus::REAL)(r.bottom - r.top);
            if (lit) FwGradEdge(g, x, y, bw, bh, rr, ew2);
            else FwEdge(g, Moc(fwc::surface2), x, y, bw, bh, rr, ew2);
        };
        auto checkBox = [&](int x, int y, int sz, Gdiplus::REAL rr, bool on, bool hov) {
            RECT r{x, y, x + sz, y + sz};
            if (on) {
                FwGradFill(g, (Gdiplus::REAL)x, (Gdiplus::REAL)y, (Gdiplus::REAL)sz, (Gdiplus::REAL)sz, rr);
                Gdiplus::RectF ckRf((Gdiplus::REAL)x, (Gdiplus::REAL)y, (Gdiplus::REAL)sz, (Gdiplus::REAL)sz);
                Gdiplus::StringFormat sfc;
                sfc.SetAlignment(Gdiplus::StringAlignmentCenter);
                sfc.SetLineAlignment(Gdiplus::StringAlignmentCenter);
                g.DrawString(L"\xE73E", -1, &glyphFont, ckRf, &sfc, &crustBr);
            } else {
                FillRoundedRect(g, hov ? surfHoverBr : surfRestBr, (Gdiplus::REAL)x, (Gdiplus::REAL)y,
                                (Gdiplus::REAL)sz, (Gdiplus::REAL)sz, rr);
                edge(r, rr, hov);
            }
        };

        Gdiplus::StringFormat sfLeft;
        sfLeft.SetAlignment(Gdiplus::StringAlignmentNear);
        sfLeft.SetLineAlignment(Gdiplus::StringAlignmentCenter);
        sfLeft.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);
        sfLeft.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

        Gdiplus::StringFormat sfCenter;
        sfCenter.SetAlignment(Gdiplus::StringAlignmentCenter);
        sfCenter.SetLineAlignment(Gdiplus::StringAlignmentCenter);
        sfCenter.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

        st->hits.clear();

        int pad = DpiScale(16, dpi);
        int titleH = DpiScale(22, dpi);
        int titleGap = DpiScale(14, dpi);
        int lblH = DpiScale(18, dpi);
        int lblGap = DpiScale(6, dpi);
        int subLblH = DpiScale(14, dpi);
        int subLblGap = DpiScale(3, dpi);
        int boxH = DpiScale(36, dpi);
        int boxGap = DpiScale(10, dpi);
        int secGap = DpiScale(14, dpi);
        Gdiplus::REAL rad = (Gdiplus::REAL)DpiScale(10, dpi);

        std::wstring title = L"Cycle \u00b7 " + st->appName;
        Gdiplus::RectF titleRf((Gdiplus::REAL)pad, (Gdiplus::REAL)pad, (Gdiplus::REAL)(w - 2 * pad), (Gdiplus::REAL)titleH);
        g.DrawString(title.c_str(), -1, &titleFont, titleRf, &sfLeft, &whiteBr);

        auto drawNumBox = [&](const RECT& r, int fieldId, const std::wstring& txt, double animPulse, const wchar_t* subLbl) {
            if (r.right <= r.left) return;
            FillRoundedRect(g, inputBr, (Gdiplus::REAL)r.left, (Gdiplus::REAL)r.top,
                            (Gdiplus::REAL)(r.right - r.left), (Gdiplus::REAL)(r.bottom - r.top), rad);
            if (animPulse > 0.01) {
                Gdiplus::SolidBrush pulseBr(Moc(fwc::mauve, animPulse * 0.22));
                FillRoundedRect(g, pulseBr, (Gdiplus::REAL)r.left, (Gdiplus::REAL)r.top,
                                (Gdiplus::REAL)(r.right - r.left), (Gdiplus::REAL)(r.bottom - r.top), rad);
            }
            edge(r, rad, st->focusedField == fieldId && GetFocus() == hwnd);

            Gdiplus::RectF tRf((Gdiplus::REAL)r.left, (Gdiplus::REAL)r.top,
                               (Gdiplus::REAL)(r.right - r.left), (Gdiplus::REAL)(r.bottom - r.top));
            bool isEmpty = txt.empty();
            const std::wstring& disp = isEmpty ? L"0" : txt;
            g.DrawString(disp.c_str(), -1, &numFont, tRf, &sfCenter, isEmpty ? &mutedBr : &whiteBr);

            if (st->focusedField == fieldId && st->caretVisible && GetFocus() == hwnd) {
                Gdiplus::REAL cx = (Gdiplus::REAL)r.left + (Gdiplus::REAL)(r.right - r.left) * 0.5f;
                if (!isEmpty) {
                    Gdiplus::RectF measured{};
                    g.MeasureString(disp.c_str(), -1, &numFont, Gdiplus::PointF(0, 0), &measured);
                    cx = (Gdiplus::REAL)r.left + ((Gdiplus::REAL)(r.right - r.left) + measured.Width) * 0.5f + 1.0f;
                }
                cx = std::min<Gdiplus::REAL>(cx, (Gdiplus::REAL)(r.right - DpiScale(6, dpi)));
                Gdiplus::Pen caretPen(Moc(fwc::text, 0.92), 1.5f);
                g.DrawLine(&caretPen, cx, (Gdiplus::REAL)(r.top + DpiScale(8, dpi)), cx, (Gdiplus::REAL)(r.bottom - DpiScale(8, dpi)));
            }

            if (subLbl) {
                Gdiplus::RectF subRf((Gdiplus::REAL)r.left, (Gdiplus::REAL)(r.bottom + subLblGap),
                                     (Gdiplus::REAL)(r.right - r.left), (Gdiplus::REAL)subLblH);
                g.DrawString(subLbl, -1, &subFont, subRf, &sfCenter, &mutedBr);
            }
            st->hits.push_back({r, 100 + fieldId, CycleHitRect::InputBox, fieldId});
        };

        auto drawDurationSection = [&](const wchar_t* secTitle, const DurationGroupState& grp, int baseId, int yStart) -> int {
            Gdiplus::RectF sRf((Gdiplus::REAL)pad, (Gdiplus::REAL)yStart, (Gdiplus::REAL)(w - 2 * pad), (Gdiplus::REAL)lblH);
            g.DrawString(secTitle, -1, &secFont, sRf, &sfLeft, &labelBr);
            double ap = grp.animating ? grp.animVal : 0.0;
            if (grp.showHours) drawNumBox(grp.rcH, baseId + 0, grp.txtH, ap, L"h");
            drawNumBox(grp.rcM, baseId + 1, grp.txtM, ap, L"min");
            drawNumBox(grp.rcS, baseId + 2, grp.txtS, ap, L"sec");
            if (st->showMs) drawNumBox(grp.rcMs, baseId + 3, grp.txtMs, ap, L"ms");
            return yStart + lblH + lblGap + boxH + subLblGap + subLblH;
        };

        int y = pad + titleH + titleGap;
        if (st->sideBySideBlockAllow) {
            int allowX = st->allowGrp.rcM.left;
            Gdiplus::RectF bRf((Gdiplus::REAL)pad, (Gdiplus::REAL)y, (Gdiplus::REAL)DpiScale(120, dpi), (Gdiplus::REAL)lblH);
            g.DrawString(L"Block", -1, &secFont, bRf, &sfLeft, &labelBr);
            Gdiplus::RectF aRf((Gdiplus::REAL)allowX, (Gdiplus::REAL)y, (Gdiplus::REAL)DpiScale(120, dpi), (Gdiplus::REAL)lblH);
            g.DrawString(L"Allow", -1, &secFont, aRf, &sfLeft, &labelBr);
            double apB = st->blockGrp.animating ? st->blockGrp.animVal : 0.0;
            double apA = st->allowGrp.animating ? st->allowGrp.animVal : 0.0;
            drawNumBox(st->blockGrp.rcM, CF_BLK_H + 1, st->blockGrp.txtM, apB, L"min");
            drawNumBox(st->blockGrp.rcS, CF_BLK_H + 2, st->blockGrp.txtS, apB, L"sec");
            drawNumBox(st->allowGrp.rcM, CF_ALW_H + 1, st->allowGrp.txtM, apA, L"min");
            drawNumBox(st->allowGrp.rcS, CF_ALW_H + 2, st->allowGrp.txtS, apA, L"sec");
            y += lblH + lblGap + boxH + subLblGap + subLblH + secGap;
        } else {
            y = drawDurationSection(L"Block", st->blockGrp, CF_BLK_H, y) + secGap;
            y = drawDurationSection(L"Allow", st->allowGrp, CF_ALW_H, y) + secGap;
        }

        // Run section
        Gdiplus::RectF runLblRf((Gdiplus::REAL)pad, (Gdiplus::REAL)y, (Gdiplus::REAL)(w - 2 * pad), (Gdiplus::REAL)lblH);
        g.DrawString(L"Run", -1, &secFont, runLblRf, &sfLeft, &labelBr);
        y += lblH + lblGap;

        bool dropOpen = (st->hRunDrop && IsWindow(st->hRunDrop));
        bool dropHov = dropOpen || (st->hoverId == 1);
        FillRoundedRect(g, dropHov ? surfHoverBr : surfRestBr,
                        (Gdiplus::REAL)st->rcRunDrop.left, (Gdiplus::REAL)st->rcRunDrop.top,
                        (Gdiplus::REAL)(st->rcRunDrop.right - st->rcRunDrop.left),
                        (Gdiplus::REAL)(st->rcRunDrop.bottom - st->rcRunDrop.top), rad);
        edge(st->rcRunDrop, rad, dropHov);
        int chevW = DpiScale(28, dpi);
        Gdiplus::RectF rTxtRf((Gdiplus::REAL)(st->rcRunDrop.left + DpiScale(12, dpi)),
                              (Gdiplus::REAL)st->rcRunDrop.top,
                              (Gdiplus::REAL)std::max<int>(20, (int)(st->rcRunDrop.right - st->rcRunDrop.left) - chevW - DpiScale(12, dpi)),
                              (Gdiplus::REAL)boxH);
        g.DrawString(RunModeDisplayLabel(st->runModeIdx), -1, &uiFont, rTxtRf, &sfLeft, &whiteBr);
        Gdiplus::RectF rChvRf((Gdiplus::REAL)(st->rcRunDrop.right - chevW - DpiScale(4, dpi)),
                              (Gdiplus::REAL)st->rcRunDrop.top, (Gdiplus::REAL)chevW, (Gdiplus::REAL)boxH);
        g.DrawString(dropOpen ? L"\xE70E" : L"\xE70D", -1, &glyphFont, rChvRf, &sfCenter, &mutedBr);
        st->hits.push_back({st->rcRunDrop, 1, CycleHitRect::RunDropdown, CF_NONE});
        y += boxH;

        if (st->runModeIdx == 1) {
            y += boxGap;
            drawNumBox(st->rcRunCycles, CF_RUN_CYC, st->runCyclesTxt, 0.0, nullptr);
            Gdiplus::RectF cycLbl((Gdiplus::REAL)(st->rcRunCycles.right + DpiScale(10, dpi)),
                                  (Gdiplus::REAL)y, (Gdiplus::REAL)DpiScale(90, dpi), (Gdiplus::REAL)boxH);
            g.DrawString(L"cycles", -1, &uiFont, cycLbl, &sfLeft, &mutedBr);
            y += boxH;
        } else if (st->runModeIdx == 2) {
            y += DpiScale(10, dpi);
            int syncH = DpiScale(22, dpi);
            int sBox = DpiScale(15, dpi);
            int sY = y + (syncH - sBox) / 2;
            RECT syncHit{pad, y, w - pad, y + syncH};
            Gdiplus::REAL chkRad = (Gdiplus::REAL)DpiScale(4, dpi);
            checkBox(pad, sY, sBox, chkRad, st->syncWithWindows, st->hoverId == 5);
            int fmtW = DpiScale(42, dpi);
            syncHit.right = w - pad - fmtW - DpiScale(6, dpi);
            Gdiplus::RectF syncTxt((Gdiplus::REAL)(pad + sBox + DpiScale(8, dpi)), (Gdiplus::REAL)y,
                                   (Gdiplus::REAL)(syncHit.right - (pad + sBox + DpiScale(8, dpi))), (Gdiplus::REAL)syncH);
            g.DrawString(L"Sync with Windows clock", -1, &subFont, syncTxt, &sfLeft, &labelBr);
            st->hits.push_back({syncHit, 5, CycleHitRect::SyncClockToggle, CF_NONE});

            if (st->syncWithWindows) {
                RECT fmtRc{w - pad - fmtW, y, w - pad, y + syncH};
                FillRoundedRect(g, (st->hoverId == 6) ? surfHoverBr : surfRestBr,
                                (Gdiplus::REAL)fmtRc.left, (Gdiplus::REAL)fmtRc.top,
                                (Gdiplus::REAL)fmtW, (Gdiplus::REAL)syncH, (Gdiplus::REAL)DpiScale(6, dpi));
                edge(fmtRc, (Gdiplus::REAL)DpiScale(6, dpi), st->hoverId == 6);
                Gdiplus::RectF fmtRf((Gdiplus::REAL)fmtRc.left, (Gdiplus::REAL)fmtRc.top, (Gdiplus::REAL)fmtW, (Gdiplus::REAL)syncH);
                g.DrawString(st->clock12Hour ? L"12h" : L"24h", -1, &subFont, fmtRf, &sfCenter, &labelBr);
                st->hits.push_back({fmtRc, 6, CycleHitRect::ClockFormat12h, CF_NONE});
            }
            y += syncH + DpiScale(8, dpi);

            if (st->syncWithWindows) {
                drawNumBox(st->rcClkH, CF_CLK_H, st->clkHourTxt, 0.0, st->clock12Hour ? L"hr (12h)" : L"hr (24h)");
                Gdiplus::RectF colRf((Gdiplus::REAL)st->rcClkH.right, (Gdiplus::REAL)y,
                                     (Gdiplus::REAL)(st->rcClkM.left - st->rcClkH.right), (Gdiplus::REAL)boxH);
                g.DrawString(L":", -1, &secFont, colRf, &sfCenter, &mutedBr);
                drawNumBox(st->rcClkM, CF_CLK_M, st->clkMinTxt, 0.0, L"min");
                if (st->clock12Hour && st->rcClkAmPm.right > st->rcClkAmPm.left) {
                    FillRoundedRect(g, surfRestBr,
                                    (Gdiplus::REAL)st->rcClkAmPm.left, (Gdiplus::REAL)st->rcClkAmPm.top,
                                    (Gdiplus::REAL)(st->rcClkAmPm.right - st->rcClkAmPm.left),
                                    (Gdiplus::REAL)(st->rcClkAmPm.bottom - st->rcClkAmPm.top), rad);
                    edge(st->rcClkAmPm, rad, false);
                    Gdiplus::RectF apRf((Gdiplus::REAL)st->rcClkAmPm.left, (Gdiplus::REAL)st->rcClkAmPm.top,
                                        (Gdiplus::REAL)(st->rcClkAmPm.right - st->rcClkAmPm.left),
                                        (Gdiplus::REAL)(st->rcClkAmPm.bottom - st->rcClkAmPm.top));
                    g.DrawString(st->clockIsPm ? L"PM" : L"AM", -1, &uiFont, apRf, &sfCenter, &labelBr);
                }
                y += boxH + subLblGap + subLblH;
            } else {
                double ap = st->runTimeGrp.animating ? st->runTimeGrp.animVal : 0.0;
                if (st->runTimeGrp.showHours) drawNumBox(st->runTimeGrp.rcH, CF_RUN_H, st->runTimeGrp.txtH, ap, L"h");
                drawNumBox(st->runTimeGrp.rcM, CF_RUN_M, st->runTimeGrp.txtM, ap, L"min");
                drawNumBox(st->runTimeGrp.rcS, CF_RUN_S, st->runTimeGrp.txtS, ap, L"sec");
                if (st->showMs) drawNumBox(st->runTimeGrp.rcMs, CF_RUN_MS, st->runTimeGrp.txtMs, ap, L"ms");
                y += boxH + subLblGap + subLblH;
            }
        }

        // Focus toggle
        y += DpiScale(16, dpi);
        int chkH = DpiScale(22, dpi);
        int boxSz = DpiScale(16, dpi);
        int boxY = y + (chkH - boxSz) / 2;
        RECT chkHit{pad, y, w - pad, y + chkH};
        Gdiplus::REAL chkRad = (Gdiplus::REAL)DpiScale(4, dpi);
        checkBox(pad, boxY, boxSz, chkRad, st->focusedOnly, st->hoverId == 2);
        Gdiplus::RectF chkTxt((Gdiplus::REAL)(pad + boxSz + DpiScale(10, dpi)), (Gdiplus::REAL)y,
                              (Gdiplus::REAL)(w - 2 * pad - boxSz - DpiScale(10, dpi)), (Gdiplus::REAL)chkH);
        g.DrawString(L"Only while app is focused", -1, &uiFont, chkTxt, &sfLeft, &whiteBr);
        st->hits.push_back({chkHit, 2, CycleHitRect::FocusToggle, CF_NONE});
        y += chkH + DpiScale(8, dpi);

        if (st->focusedOnly) {
            int subPad = pad;
            int subBoxY = y + (chkH - boxSz) / 2;
            RECT subHit{subPad, y, w - pad, y + chkH};
            checkBox(subPad, subBoxY, boxSz, chkRad, st->allowWhenUnfocused, st->hoverId == 7);
            Gdiplus::RectF subTxt((Gdiplus::REAL)(subPad + boxSz + DpiScale(10, dpi)), (Gdiplus::REAL)y,
                                  (Gdiplus::REAL)(w - pad - (subPad + boxSz + DpiScale(10, dpi))), (Gdiplus::REAL)chkH);
            g.DrawString(L"Allow internet when out of focus", -1, &uiFont, subTxt, &sfLeft, &labelBr);
            st->hits.push_back({subHit, 7, CycleHitRect::AllowUnfocusedToggle, CF_NONE});
            y += chkH + DpiScale(8, dpi);
        }

        // Live summary
        Gdiplus::RectF sumRf((Gdiplus::REAL)st->rcSummary.left, (Gdiplus::REAL)st->rcSummary.top,
                             (Gdiplus::REAL)(st->rcSummary.right - st->rcSummary.left),
                             (Gdiplus::REAL)(st->rcSummary.bottom - st->rcSummary.top));
        g.DrawString(st->summaryText.c_str(), -1, &subFont, sumRf, &sfLeft,
                     (!st->valid || st->warnSub1s) ? &warnBr : &mutedBr);
        y = st->rcSummary.bottom + DpiScale(14, dpi);

        // Buttons
        int btnW = DpiScale(88, dpi);
        int btnH = DpiScale(32, dpi);
        RECT cancelRc{pad, y, pad + DpiScale(72, dpi), y + btnH};
        FillRoundedRect(g, (st->hoverId == 3) ? surfHoverBr : surfRestBr, (Gdiplus::REAL)cancelRc.left,
                        (Gdiplus::REAL)cancelRc.top, (Gdiplus::REAL)(cancelRc.right - cancelRc.left),
                        (Gdiplus::REAL)btnH, rad);
        edge(cancelRc, rad, st->hoverId == 3);
        Gdiplus::RectF cRf((Gdiplus::REAL)cancelRc.left, (Gdiplus::REAL)cancelRc.top,
                           (Gdiplus::REAL)(cancelRc.right - cancelRc.left), (Gdiplus::REAL)btnH);
        g.DrawString(L"Cancel", -1, &uiFont, cRf, &sfCenter, (st->hoverId == 3) ? &whiteBr : &mutedBr);
        st->hits.push_back({cancelRc, 3, CycleHitRect::CancelBtn, CF_NONE});

        RECT primRc = st->rcBtnPrimary;
        bool pHov = (st->hoverId == 4);
        bool enabled = st->isRunning || st->valid;
        // Start wears the accent gradient, Stop is Mocha red; hover lifts either a touch.
        Gdiplus::REAL px = (Gdiplus::REAL)primRc.left, py = (Gdiplus::REAL)primRc.top;
        if (!enabled) {
            FwRound(g, Moc(fwc::surface0, 0.85), px, py, (Gdiplus::REAL)btnW, (Gdiplus::REAL)btnH, rad);
            edge(RECT{primRc.left, primRc.top, primRc.left + btnW, primRc.top + btnH}, rad, false);
        } else if (st->isRunning) {
            FwRound(g, Moc(fwc::red), px, py, (Gdiplus::REAL)btnW, (Gdiplus::REAL)btnH, rad);
        } else {
            FwGradFill(g, px, py, (Gdiplus::REAL)btnW, (Gdiplus::REAL)btnH, rad);
        }
        if (enabled && pHov) FwRound(g, Moc(fwc::text, 0.14), px, py, (Gdiplus::REAL)btnW, (Gdiplus::REAL)btnH, rad);
        Gdiplus::RectF pRf(px, py, (Gdiplus::REAL)btnW, (Gdiplus::REAL)btnH);
        g.DrawString(st->isRunning ? L"Stop" : L"Start", -1, &secFont, pRf, &sfCenter, enabled ? &crustBr : &mutedBr);
        st->hits.push_back({primRc, 4, CycleHitRect::PrimaryBtn, CF_NONE});
    }

    BitBlt(hdcScreen, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBmp);
    DeleteObject(hBmp);
    DeleteDC(memDC);
    EndPaint(hwnd, &ps);
}

static void ExecuteCyclePrimaryAction(CyclePopupState* st) {
    if (!st) return;
    if (st->isRunning) {
        StopCycleForApp(st->displayPath, true);
        RefreshAppList();
        RequestRepaint();
        DestroyWindow(st->hwnd);
        return;
    }
    AutoCarryDurationGroup(st, st->blockGrp);
    AutoCarryDurationGroup(st, st->allowGrp);
    if (st->runModeIdx == 2 && !st->syncWithWindows) AutoCarryDurationGroup(st, st->runTimeGrp);
    if (st->runModeIdx == 2 && st->syncWithWindows) CommitClockFields(st);
    UpdateCyclePopupSummary(st);
    if (!st->valid) return;

    CycleConfig cfg;
    cfg.blockMs = st->blockGrp.totalMs;
    cfg.allowMs = st->allowGrp.totalMs;
    cfg.runMode = (CycleRunMode)st->runModeIdx;
    if (st->runModeIdx == 1) {
        cfg.runValue = ParseDigitsU64(st->runCyclesTxt);
    } else if (st->runModeIdx == 2) {
        if (st->syncWithWindows) {
            cfg.runValue = st->computedClockMs;
            cfg.targetEndUtcMs = st->computedTargetUtcMs;
        } else {
            cfg.runValue = st->runTimeGrp.totalMs;
        }
    }
    cfg.focusedOnly = st->focusedOnly;
    cfg.allowWhenUnfocused = st->focusedOnly && st->allowWhenUnfocused;
    cfg.direction = st->direction;

    std::wstring displayPath = st->displayPath;
    HWND hwnd = st->hwnd;
    std::wstring err;
    st->modalOpen = true;
    bool ok = StartCycleForApp(displayPath, cfg, err);
    if (!IsWindow(hwnd)) return;
    st->modalOpen = false;
    if (ok) {
        RefreshAppList();
        RequestRepaint();
        DestroyWindow(hwnd);
    } else {
        st->valid = false;
        st->summaryText = err;
        InvalidateRect(hwnd, &st->rcSummary, FALSE);
    }
}

static void CommitActiveDurationCarry(CyclePopupState* st) {
    if (!st) return;
    if (st->focusedField == CF_CLK_H || st->focusedField == CF_CLK_M) {
        CommitClockFields(st);
    }
    if (DurationGroupState* grp = GetDurationGroupByField(st, st->focusedField)) {
        AutoCarryDurationGroup(st, *grp);
    }
}

static void CycleStepField(CyclePopupState* st, bool reverse) {
    if (!st) return;
    std::vector<int> order;
    auto pushGrp = [&](const DurationGroupState& grp, int baseId) {
        if (grp.showHours) order.push_back(baseId + 0);
        order.push_back(baseId + 1);
        order.push_back(baseId + 2);
        if (st->showMs) order.push_back(baseId + 3);
    };
    pushGrp(st->blockGrp, CF_BLK_H);
    pushGrp(st->allowGrp, CF_ALW_H);
    if (st->runModeIdx == 1) order.push_back(CF_RUN_CYC);
    else if (st->runModeIdx == 2) {
        if (st->syncWithWindows) { order.push_back(CF_CLK_H); order.push_back(CF_CLK_M); }
        else pushGrp(st->runTimeGrp, CF_RUN_H);
    }
    if (order.empty()) return;

    int curPos = -1;
    for (int i = 0; i < (int)order.size(); ++i) {
        if (order[i] == st->focusedField) { curPos = i; break; }
    }
    int nextPos = reverse ? ((curPos <= 0) ? (int)order.size() - 1 : curPos - 1)
                          : ((curPos < 0 || curPos + 1 >= (int)order.size()) ? 0 : curPos + 1);

    CommitActiveDurationCarry(st);
    RECT oldRc{};
    GetFieldTextPtr(st, st->focusedField, &oldRc);
    st->focusedField = order[nextPos];
    st->replaceOnType = true;
    st->caretVisible = true;
    RECT newRc{};
    GetFieldTextPtr(st, st->focusedField, &newRc);
    if (oldRc.right > oldRc.left) InvalidateRect(st->hwnd, &oldRc, FALSE);
    if (newRc.right > newRc.left) InvalidateRect(st->hwnd, &newRc, FALSE);
    UpdateCyclePopupSummary(st);
}

static LRESULT CALLBACK CycleRunDropWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    CyclePopupState* st = g_cyclePopupState;
    switch (msg) {
        case WM_CREATE: {
            DWORD pref = DWMWCP_ROUND;
            DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &pref, sizeof(pref));
            MARGINS m{-1, -1, -1, -1};
            DwmExtendFrameIntoClientArea(hwnd, &m);
            ApplyPanelGlass(hwnd, TransparencyOn());
            ApplyCaptureExclusionToWindow(hwnd);
            return 0;
        }
        case WM_ACTIVATE: {
            if (LOWORD(wParam) == WA_INACTIVE) {
                DestroyWindow(hwnd);
            }
            return 0;
        }
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps{};
            HDC hdcScreen = BeginPaint(hwnd, &ps);
            RECT rc{};
            GetClientRect(hwnd, &rc);
            int w = rc.right - rc.left;
            int h = rc.bottom - rc.top;
            if (w > 0 && h > 0 && st) {
                UINT dpi = GetDpiForWindow(hwnd);
                HDC memDC = CreateCompatibleDC(hdcScreen);
                BITMAPINFO bmi{};
                bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                bmi.bmiHeader.biWidth = w;
                bmi.bmiHeader.biHeight = -h;
                bmi.bmiHeader.biPlanes = 1;
                bmi.bmiHeader.biBitCount = 32;
                bmi.bmiHeader.biCompression = BI_RGB;
                void* bits = nullptr;
                HBITMAP hBmp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
                HGDIOBJ oldBmp = SelectObject(memDC, hBmp);
                if (bits) memset(bits, 0, (size_t)w * (size_t)h * 4);

                if (bits) {
                    Gdiplus::Bitmap canvas(w, h, w * 4, PixelFormat32bppPARGB, (BYTE*)bits);
                    Gdiplus::Graphics g(&canvas);
                    g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
                    g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
                    g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

                    // A floating list: frosted Mocha (solid when transparency is off), one 2px grey
                    // edge on the live window radius.
                    g.Clear(Moc(fwc::base, TransparencyOn() ? 0.6 : 1.0));
                    FwEdge(g, Moc(fwc::surface2), 0, 0, (Gdiplus::REAL)w, (Gdiplus::REAL)h,
                           (Gdiplus::REAL)DpiScale(PanelCornerRadius(), dpi),
                           (Gdiplus::REAL)std::max(2, DpiScale(2, dpi)));

                    Gdiplus::Font uiFont(FwTextFace(), (Gdiplus::REAL)DpiScale(12, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
                    Gdiplus::Font glyphFont(FwIconFace(), (Gdiplus::REAL)DpiScale(11, dpi), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
                    Gdiplus::SolidBrush whiteBr(Moc(fwc::text));
                    Gdiplus::SolidBrush terraBr(Moc(fwc::mauve));
                    Gdiplus::SolidBrush hoverBr(Moc(fwc::surface1, 0.75));

                    Gdiplus::StringFormat sfLeft;
                    sfLeft.SetAlignment(Gdiplus::StringAlignmentNear);
                    sfLeft.SetLineAlignment(Gdiplus::StringAlignmentCenter);
                    Gdiplus::StringFormat sfCenter;
                    sfCenter.SetAlignment(Gdiplus::StringAlignmentCenter);
                    sfCenter.SetLineAlignment(Gdiplus::StringAlignmentCenter);

                    int pad = DpiScale(6, dpi);
                    int itemH = DpiScale(34, dpi);
                    Gdiplus::REAL rad = (Gdiplus::REAL)DpiScale(6, dpi);
                    for (int i = 0; i < 3; ++i) {
                        int iy = pad + i * itemH;
                        if (i == st->runDropHoverIdx) {
                            FillRoundedRect(g, hoverBr, (Gdiplus::REAL)pad, (Gdiplus::REAL)iy,
                                            (Gdiplus::REAL)(w - 2 * pad), (Gdiplus::REAL)itemH, rad);
                            FwGradEdge(g, (Gdiplus::REAL)pad, (Gdiplus::REAL)iy, (Gdiplus::REAL)(w - 2 * pad),
                                       (Gdiplus::REAL)itemH, rad, (Gdiplus::REAL)std::max(2, DpiScale(2, dpi)));
                        }
                        if (i == st->runModeIdx) {
                            Gdiplus::RectF ckRf((Gdiplus::REAL)(pad + DpiScale(6, dpi)), (Gdiplus::REAL)iy,
                                                (Gdiplus::REAL)DpiScale(18, dpi), (Gdiplus::REAL)itemH);
                            g.DrawString(L"\xE73E", -1, &glyphFont, ckRf, &sfCenter, &terraBr);
                        }
                        Gdiplus::RectF txtRf((Gdiplus::REAL)(pad + DpiScale(28, dpi)), (Gdiplus::REAL)iy,
                                             (Gdiplus::REAL)(w - 2 * pad - DpiScale(32, dpi)), (Gdiplus::REAL)itemH);
                        g.DrawString(RunModeDisplayLabel(i), -1, &uiFont, txtRf, &sfLeft, &whiteBr);
                    }
                }

                BitBlt(hdcScreen, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
                SelectObject(memDC, oldBmp);
                DeleteObject(hBmp);
                DeleteDC(memDC);
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (!st) break;
            UINT dpi = GetDpiForWindow(hwnd);
            int pad = DpiScale(6, dpi);
            int itemH = DpiScale(34, dpi);
            int y = GET_Y_LPARAM(lParam);
            int idx = (y >= pad) ? ((y - pad) / itemH) : -1;
            if (idx < 0 || idx > 2) idx = -1;
            if (idx != st->runDropHoverIdx) {
                st->runDropHoverIdx = idx;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }
        case WM_LBUTTONUP: {
            if (!st) break;
            UINT dpi = GetDpiForWindow(hwnd);
            int pad = DpiScale(6, dpi);
            int itemH = DpiScale(34, dpi);
            int y = GET_Y_LPARAM(lParam);
            int idx = (y >= pad) ? ((y - pad) / itemH) : -1;
            if (idx >= 0 && idx <= 2) {
                st->runModeIdx = idx;
                if (idx == 2 && st->syncWithWindows) PopulateClockFromWindows(st);
                LayoutCyclePopup(st, GetDpiForWindow(st->hwnd), true);
                UpdateCyclePopupSummary(st);
            }
            SetForegroundWindow(st->hwnd);
            DestroyWindow(hwnd);
            return 0;
        }
        case WM_KEYDOWN: {
            if (!st) break;
            if (wParam == VK_ESCAPE) {
                SetForegroundWindow(st->hwnd);
                DestroyWindow(hwnd);
                return 0;
            }
            if (wParam == VK_UP) {
                st->runDropHoverIdx = (st->runDropHoverIdx <= 0) ? 2 : st->runDropHoverIdx - 1;
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            if (wParam == VK_DOWN) {
                st->runDropHoverIdx = (st->runDropHoverIdx < 0 || st->runDropHoverIdx >= 2) ? 0 : st->runDropHoverIdx + 1;
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            if (wParam == VK_RETURN) {
                if (st->runDropHoverIdx >= 0 && st->runDropHoverIdx <= 2) {
                    st->runModeIdx = st->runDropHoverIdx;
                    if (st->runModeIdx == 2 && st->syncWithWindows) PopulateClockFromWindows(st);
                    LayoutCyclePopup(st, GetDpiForWindow(st->hwnd), true);
                    UpdateCyclePopupSummary(st);
                }
                SetForegroundWindow(st->hwnd);
                DestroyWindow(hwnd);
                return 0;
            }
            break;
        }
        case WM_DESTROY:
            if (st) {
                st->hRunDrop = nullptr;
                if (st->hwnd && IsWindow(st->hwnd)) {
                    InvalidateRect(st->hwnd, &st->rcRunDrop, FALSE);
                }
            }
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static void OpenCustomRunDropdown(CyclePopupState* st) {
    if (!st || !st->hwnd) return;
    if (st->hRunDrop && IsWindow(st->hRunDrop)) {
        DestroyWindow(st->hRunDrop);
        return;
    }

    static bool dropReg = false;
    if (!dropReg) {
        WNDCLASSEXW dwc{sizeof(dwc)};
        dwc.lpfnWndProc = CycleRunDropWndProc;
        dwc.hInstance = GetModuleHandleW(nullptr);
        dwc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        dwc.lpszClassName = kCycleRunDropClass;
        RegisterClassExW(&dwc);
        dropReg = true;
    }

    UINT dpi = GetDpiForWindow(st->hwnd);
    int pad = DpiScale(6, dpi);
    int itemH = DpiScale(34, dpi);
    int dropW = st->rcRunDrop.right - st->rcRunDrop.left;
    int dropH = pad * 2 + 3 * itemH;
    POINT pt{st->rcRunDrop.left, st->rcRunDrop.bottom + DpiScale(4, dpi)};
    ClientToScreen(st->hwnd, &pt);

    st->runDropHoverIdx = st->runModeIdx;
    st->openingRunDrop = true;
    st->hRunDrop = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        kCycleRunDropClass, L"", WS_POPUP,
        pt.x, pt.y, dropW, dropH,
        st->hwnd, nullptr, GetModuleHandleW(nullptr), nullptr);
    st->openingRunDrop = false;
    if (st->hRunDrop) {
        ShowWindow(st->hRunDrop, SW_SHOW);
        SetForegroundWindow(st->hRunDrop);
        SetFocus(st->hRunDrop);
        InvalidateRect(st->hwnd, &st->rcRunDrop, FALSE);
    }
}

static LRESULT CALLBACK CyclePopupWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    CyclePopupState* st = g_cyclePopupState;
    switch (msg) {
        case WM_CREATE: {
            BOOL dark = TRUE;
            DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
            DWORD pref = DWMWCP_ROUND;
            DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &pref, sizeof(pref));
            MARGINS m{-1, -1, -1, -1};
            DwmExtendFrameIntoClientArea(hwnd, &m);
            // The panel's own frosted glass; solid Mocha when Windows' transparency is off.
            bool glass = TransparencyOn();
            ApplyPanelGlass(hwnd, glass);
            if (st) st->hasBackdropBlur = glass;
            g_cyclePopupInside = false;
            SetTimer(hwnd, TIMER_CYCLE_POPUP_CARET, 520, nullptr);
            return 0;
        }
        case WM_NCACTIVATE:
            return TRUE;
        case WM_MOUSEACTIVATE:
            SetForegroundWindow(hwnd);
            SetFocus(hwnd);
            return MA_ACTIVATE;
        case WM_SETFOCUS:
        case WM_KILLFOCUS:
            if (st && st->focusedField != CF_NONE) {
                RECT fRc{};
                if (GetFieldTextPtr(st, st->focusedField, &fRc) && fRc.right > fRc.left) {
                    InvalidateRect(hwnd, &fRc, FALSE);
                }
            }
            return 0;
        case WM_ACTIVATE: {
            if (LOWORD(wParam) == WA_INACTIVE && st) {
                if (st->modalOpen || st->openingRunDrop || (st->hRunDrop && IsWindow(st->hRunDrop)) || g_hConfirm)
                    return 0;
                PostMessageW(hwnd, WM_CLOSE, 0, 0);
            }
            return 0;
        }
        case WM_DPICHANGED: {
            if (st) LayoutCyclePopup(st, HIWORD(wParam));
            return 0;
        }
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
            PaintCyclePopup(hwnd, st);
            return 0;
        case WM_TIMER: {
            if (!st) return 0;
            if (wParam == TIMER_CYCLE_POPUP_RESIZE) {
                bool more = st->heightClock.Step();
                int curH = (int)std::round(st->heightClock.currentVal);
                SetWindowPos(hwnd, HWND_TOPMOST, st->targetX, st->targetY, st->targetW, curH, SWP_NOACTIVATE);
                if (!more) {
                    KillTimer(hwnd, TIMER_CYCLE_POPUP_RESIZE);
                    SetWindowPos(hwnd, HWND_TOPMOST, st->targetX, st->targetY, st->targetW, st->targetH, SWP_NOACTIVATE);
                }
            } else if (wParam == TIMER_CYCLE_POPUP_OPEN) {
                bool more = st->openClock.Step();
                double p = st->openClock.currentVal;
                BYTE alpha = (BYTE)std::clamp((int)std::round(p * 255.0), 0, 255);
                int offsetY = (int)std::round((1.0 - p) * (double)DpiScale(10, GetDpiForWindow(hwnd)));
                SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA);
                SetWindowPos(hwnd, HWND_TOPMOST, st->targetX, st->targetY + offsetY, 0, 0,
                             SWP_NOSIZE | SWP_NOACTIVATE);
                if (!more) {
                    KillTimer(hwnd, TIMER_CYCLE_POPUP_OPEN);
                    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
                    SetWindowPos(hwnd, HWND_TOPMOST, st->targetX, st->targetY, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
                }
            } else if (wParam == TIMER_CYCLE_CLOCK_COMMIT) {
                CommitClockFields(st);
                UpdateCyclePopupSummary(st);
            } else if (wParam == TIMER_CYCLE_POPUP_CARET) {
                if (st->focusedField != CF_NONE) {
                    st->caretVisible = !st->caretVisible;
                    RECT fRc{};
                    if (GetFieldTextPtr(st, st->focusedField, &fRc) && fRc.right > fRc.left) {
                        InvalidateRect(hwnd, &fRc, FALSE);
                    }
                }
            } else if (wParam == TIMER_CYCLE_POPUP_ANIM) {
                LARGE_INTEGER freq{}, now{};
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&now);
                auto stepAnim = [&](DurationGroupState& grp) -> bool {
                    if (!grp.animating) return false;
                    double ms = (double)(now.QuadPart - grp.animStart.QuadPart) * 1000.0 / (double)freq.QuadPart;
                    if (ms >= 120.0) { grp.animVal = 0.0; grp.animating = false; return false; }
                    grp.animVal = 1.0 - (ms / 120.0);
                    return true;
                };
                bool m1 = stepAnim(st->blockGrp);
                bool m2 = stepAnim(st->allowGrp);
                bool m3 = stepAnim(st->runTimeGrp);
                auto invGrp = [&](const DurationGroupState& grp) {
                    if (grp.rcM.right <= grp.rcM.left) return;
                    RECT r{grp.showHours ? grp.rcH.left : grp.rcM.left, grp.rcM.top,
                           st->showMs ? grp.rcMs.right : grp.rcS.right, grp.rcS.bottom};
                    InvalidateRect(hwnd, &r, FALSE);
                };
                if (m1 || st->blockGrp.animVal == 0.0) invGrp(st->blockGrp);
                if (m2 || st->allowGrp.animVal == 0.0) invGrp(st->allowGrp);
                if (m3 || st->runTimeGrp.animVal == 0.0) invGrp(st->runTimeGrp);
                if (!(m1 || m2 || m3)) KillTimer(hwnd, TIMER_CYCLE_POPUP_ANIM);
            }
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (!st) break;
            TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&tme);
            if (!g_cyclePopupInside) {
                g_cyclePopupInside = true;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            int newHover = -1;
            RECT newHoverRc{};
            for (const auto& h : st->hits) {
                if (h.kind != CycleHitRect::InputBox && PtInRect(&h.rc, pt)) {
                    newHover = h.id;
                    newHoverRc = h.rc;
                    break;
                }
            }
            if (newHover != st->hoverId) {
                if (st->hoverId != -1 && st->hoverRc.right > st->hoverRc.left) {
                    InvalidateRect(hwnd, &st->hoverRc, FALSE);
                }
                st->hoverId = newHover;
                st->hoverRc = newHoverRc;
                if (st->hoverId != -1 && st->hoverRc.right > st->hoverRc.left) {
                    InvalidateRect(hwnd, &st->hoverRc, FALSE);
                }
            }
            return 0;
        }
        case WM_MOUSELEAVE: {
            if (st && st->hoverId != -1) {
                if (st->hoverRc.right > st->hoverRc.left) InvalidateRect(hwnd, &st->hoverRc, FALSE);
                st->hoverId = -1;
                st->hoverRc = {};
            }
            if (g_cyclePopupInside) {
                g_cyclePopupInside = false;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }
        case WM_LBUTTONDOWN: {
            if (!st) break;
            SetForegroundWindow(hwnd);
            SetFocus(hwnd);
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            for (const auto& h : st->hits) {
                if (!PtInRect(&h.rc, pt)) continue;
                if (h.kind == CycleHitRect::InputBox) {
                    if (st->focusedField != h.fieldId) {
                        CommitActiveDurationCarry(st);
                        RECT oldRc{};
                        GetFieldTextPtr(st, st->focusedField, &oldRc);
                        st->focusedField = h.fieldId;
                        if (oldRc.right > oldRc.left) InvalidateRect(hwnd, &oldRc, FALSE);
                        UpdateCyclePopupSummary(st);
                    }
                    st->replaceOnType = true;
                    st->caretVisible = true;
                    InvalidateRect(hwnd, &h.rc, FALSE);
                    return 0;
                }
                CommitActiveDurationCarry(st);
                if (h.kind == CycleHitRect::RunDropdown) {
                    OpenCustomRunDropdown(st);
                } else if (h.kind == CycleHitRect::SyncClockToggle) {
                    st->syncWithWindows = !st->syncWithWindows;
                    st->clockEditing = false;
                    if (st->syncWithWindows) {
                        PopulateClockFromWindows(st);
                        st->focusedField = CF_CLK_H;
                        st->replaceOnType = true;
                    }
                    LayoutCyclePopup(st, GetDpiForWindow(hwnd), true);
                    UpdateCyclePopupSummary(st);
                } else if (h.kind == CycleHitRect::ClockFormat12h) {
                    int curH24 = ClockTo24Hour(ParseDigitsU64(st->clkHourTxt), st->clock12Hour, st->clockIsPm);
                    st->clock12Hour = !st->clock12Hour;
                    if (curH24 >= 0) {
                        wchar_t bH[8]{};
                        if (st->clock12Hour) {
                            st->clockIsPm = (curH24 >= 12);
                            int h12 = curH24 % 12; if (h12 == 0) h12 = 12;
                            swprintf_s(bH, L"%02d", h12);
                        } else {
                            swprintf_s(bH, L"%02d", curH24);
                        }
                        st->clkHourTxt = bH;
                    } else {
                        PopulateClockFromWindows(st);
                    }
                    st->clockEditing = false;
                    LayoutCyclePopup(st, GetDpiForWindow(hwnd), false);
                    UpdateCyclePopupSummary(st);
                } else if (h.kind == CycleHitRect::FocusToggle) {
                    st->focusedOnly = !st->focusedOnly;
                    LayoutCyclePopup(st, GetDpiForWindow(hwnd), true);
                    UpdateCyclePopupSummary(st);
                } else if (h.kind == CycleHitRect::AllowUnfocusedToggle) {
                    st->allowWhenUnfocused = !st->allowWhenUnfocused;
                    InvalidateRect(hwnd, &h.rc, FALSE);
                    UpdateCyclePopupSummary(st);
                } else if (h.kind == CycleHitRect::CancelBtn) {
                    DestroyWindow(hwnd);
                } else if (h.kind == CycleHitRect::PrimaryBtn) {
                    ExecuteCyclePrimaryAction(st);
                }
                return 0;
            }
            CommitActiveDurationCarry(st);
            UpdateCyclePopupSummary(st);
            return 0;
        }
        case WM_CHAR: {
            if (!st || st->focusedField == CF_NONE) break;
            if (wParam >= L'0' && wParam <= L'9') {
                RECT fRc{};
                if (std::wstring* pTxt = GetFieldTextPtr(st, st->focusedField, &fRc)) {
                    if (st->replaceOnType) {
                        pTxt->clear();
                        st->replaceOnType = false;
                    } else if (st->focusedField != CF_CLK_H && st->focusedField != CF_CLK_M && *pTxt == L"0") {
                        pTxt->clear();
                    }
                    size_t maxLen = (st->focusedField == CF_CLK_H || st->focusedField == CF_CLK_M) ? 2 : 6;
                    if (st->focusedField == CF_CLK_H || st->focusedField == CF_CLK_M) {
                        st->clockEditing = true;
                        SetTimer(hwnd, TIMER_CYCLE_CLOCK_COMMIT, 1500, nullptr);
                    }
                    if (pTxt->size() < maxLen) {
                        pTxt->push_back((wchar_t)wParam);
                        st->caretVisible = true;
                        InvalidateRect(hwnd, &fRc, FALSE);
                        UpdateCyclePopupSummary(st);
                        if (st->focusedField == CF_CLK_H && pTxt->size() == 2) {
                            CycleStepField(st, false);
                            if (st->focusedField == CF_CLK_M) {
                                st->clockEditing = true;
                                SetTimer(hwnd, TIMER_CYCLE_CLOCK_COMMIT, 1500, nullptr);
                            }
                        }
                    }
                }
                return 0;
            }
            return 0;
        }
        case WM_KEYDOWN: {
            if (!st) break;
            if (wParam == VK_ESCAPE) {
                DestroyWindow(hwnd);
                return 0;
            }
            if (wParam == VK_RETURN) {
                st->clockEditing = false;
                UpdateCyclePopupSummary(st);
                ExecuteCyclePrimaryAction(st);
                return 0;
            }
            if (wParam == VK_TAB || wParam == VK_LEFT || wParam == VK_RIGHT) {
                bool rev = (wParam == VK_LEFT) || (wParam == VK_TAB && (GetKeyState(VK_SHIFT) & 0x8000) != 0);
                CycleStepField(st, rev);
                return 0;
            }
            if (wParam == VK_DELETE && st->focusedField != CF_NONE) {
                RECT fRc{};
                if (std::wstring* pTxt = GetFieldTextPtr(st, st->focusedField, &fRc)) {
                    pTxt->clear();
                    st->replaceOnType = false;
                    if (st->focusedField == CF_CLK_H || st->focusedField == CF_CLK_M) {
                        st->clockEditing = true;
                        SetTimer(hwnd, TIMER_CYCLE_CLOCK_COMMIT, 1500, nullptr);
                    }
                    st->caretVisible = true;
                    InvalidateRect(hwnd, &fRc, FALSE);
                    UpdateCyclePopupSummary(st);
                }
                return 0;
            }
            if (wParam == VK_BACK && st->focusedField != CF_NONE) {
                RECT fRc{};
                if (std::wstring* pTxt = GetFieldTextPtr(st, st->focusedField, &fRc)) {
                    st->replaceOnType = false;
                    if (st->focusedField == CF_CLK_H || st->focusedField == CF_CLK_M) {
                        st->clockEditing = true;
                        SetTimer(hwnd, TIMER_CYCLE_CLOCK_COMMIT, 1500, nullptr);
                    }
                    if (!pTxt->empty()) pTxt->pop_back();
                    st->caretVisible = true;
                    InvalidateRect(hwnd, &fRc, FALSE);
                    UpdateCyclePopupSummary(st);
                }
                return 0;
            }
            if ((wParam == VK_UP || wParam == VK_DOWN) && st->focusedField != CF_NONE) {
                RECT fRc{};
                if (std::wstring* pTxt = GetFieldTextPtr(st, st->focusedField, &fRc)) {
                    int64_t val = (int64_t)ParseDigitsU64(*pTxt) + ((wParam == VK_UP) ? 1 : -1);
                    if (val < 0) val = 0;
                    if (st->focusedField == CF_CLK_H) {
                        val = st->clock12Hour ? std::clamp<int64_t>(val, 1, 12) : std::clamp<int64_t>(val, 0, 23);
                        st->clockEditing = false;
                    } else if (st->focusedField == CF_CLK_M) {
                        val = std::clamp<int64_t>(val, 0, 59);
                        st->clockEditing = false;
                    }
                    *pTxt = std::to_wstring(val);
                    st->replaceOnType = false;
                    st->caretVisible = true;
                    if (DurationGroupState* grp = GetDurationGroupByField(st, st->focusedField)) {
                        AutoCarryDurationGroup(st, *grp);
                    }
                    InvalidateRect(hwnd, &fRc, FALSE);
                    UpdateCyclePopupSummary(st);
                }
                return 0;
            }
            break;
        }
        case WM_DESTROY: {
            KillTimer(hwnd, TIMER_CYCLE_POPUP_ANIM);
            KillTimer(hwnd, TIMER_CYCLE_POPUP_CARET);
            KillTimer(hwnd, TIMER_CYCLE_POPUP_OPEN);
            KillTimer(hwnd, TIMER_CYCLE_POPUP_RESIZE);
            KillTimer(hwnd, TIMER_CYCLE_CLOCK_COMMIT);
            g_hCyclePopup = nullptr;
            if (st) {
                if (st->hRunDrop && IsWindow(st->hRunDrop)) DestroyWindow(st->hRunDrop);
                delete st;
                g_cyclePopupState = nullptr;
            }
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static void OpenCyclePopupForApp(const AppEntry& app) {
    bool schedEnabled = false;
    bool showMs = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        schedEnabled = g_settings.enableCycleScheduler;
        showMs = g_settings.showCycleMs;
    }
    if (!schedEnabled) {
        g_statusBanner = L"Cycle scheduler is off \u2014 enable it in Windhawk Settings.";
        RequestRepaint();
        return;
    }
    if (app.isExcluded || app.isExternalBlocked) {
        g_statusBanner = app.isExcluded ? L"This app is on your hidden list." : L"Windows Firewall already blocks this app, so it can't run on a timer.";
        RequestRepaint();
        return;
    }
    if (app.isImmutableLocked || IsImmutableProtectedExe(app.exePath)) {
        g_statusBanner = L"Core OS & security software is permanently protected.";
        RequestRepaint();
        return;
    }
    if (app.isOtherSessionOrUser || IsExeOnlyInOtherSessionOrUser(app.exePath)) {
        g_statusBanner = L"Session 0 / other-user process is isolated and locked.";
        RequestRepaint();
        return;
    }
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        if (g_settings.lockSystemProcesses && app.isCriticalLocked) {
            g_statusBanner = L"Not allowed on locked system processes.";
            RequestRepaint();
            return;
        }
    }

    if (g_hCyclePopup && IsWindow(g_hCyclePopup)) {
        DestroyWindow(g_hCyclePopup);
    }

    static bool regDone = false;
    if (!regDone) {
        WNDCLASSEXW pwc{sizeof(pwc)};
        pwc.lpfnWndProc = CyclePopupWndProc;
        pwc.hInstance = GetModuleHandleW(nullptr);
        pwc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        pwc.lpszClassName = kCyclePopupClass;
        RegisterClassExW(&pwc);
        regDone = true;
    }

    auto* st = new CyclePopupState();
    st->exePath = app.exePath;
    st->displayPath = app.displayPath;
    st->appName = app.name;
    st->direction = app.block.direction;
    st->showMs = showMs;

    CycleStatusSnapshot activeSnap;
    st->isRunning = GetCycleSnapshot(app.exePath, activeSnap);

    CycleConfig defCfg;
    if (st->isRunning) {
        defCfg.blockMs = activeSnap.blockMs;
        defCfg.allowMs = activeSnap.allowMs;
        defCfg.runMode = activeSnap.runMode;
        defCfg.runValue = (activeSnap.runMode == CycleRunMode::ForCycles) ? activeSnap.targetCycles : activeSnap.totalRemainingMs;
        defCfg.focusedOnly = activeSnap.focusedOnly;
        defCfg.allowWhenUnfocused = activeSnap.allowWhenUnfocused;
    } else {
        bool rememberTpl = true;
        {
            std::lock_guard<std::mutex> lk(g_settingsMtx);
            rememberTpl = g_settings.rememberCycleTemplates;
        }
        if (rememberTpl) {
            std::lock_guard<std::mutex> lk(g_cycleMtx);
            auto itTpl = g_cycleTemplates.find(app.exePath);
            if (itTpl != g_cycleTemplates.end()) {
                defCfg = itTpl->second;
            }
        }
    }

    WriteDurationGroupMs(st->blockGrp, defCfg.blockMs, false);
    WriteDurationGroupMs(st->allowGrp, defCfg.allowMs, false);
    st->runModeIdx = (int)defCfg.runMode;
    st->runCyclesTxt = std::to_wstring((defCfg.runMode == CycleRunMode::ForCycles && defCfg.runValue > 0) ? defCfg.runValue : 5ULL);
    WriteDurationGroupMs(st->runTimeGrp,
                         (defCfg.runMode == CycleRunMode::ForDuration && defCfg.runValue >= 100) ? defCfg.runValue : 300000ULL,
                         false);
    PopulateClockFromWindows(st);
    st->focusedOnly = defCfg.focusedOnly;
    st->allowWhenUnfocused = defCfg.allowWhenUnfocused;
    st->focusedField = CF_BLK_S;
    st->replaceOnType = true;

    g_cyclePopupState = st;

    POINT pt{};
    GetCursorPos(&pt);
    // Create hidden first, lay out to exact DPI size, then show without flash
    HWND hPopup = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED,
        kCyclePopupClass, L"Cycle Mode", WS_POPUP,
        pt.x, pt.y, 260, 260,
        g_hWnd, nullptr, GetModuleHandleW(nullptr), nullptr);
    if (!hPopup) {
        delete st;
        g_cyclePopupState = nullptr;
        return;
    }
    st->hwnd = hPopup;
    g_hCyclePopup = hPopup;

    LayoutCyclePopup(st, GetDpiForWindow(hPopup));
    UpdateCyclePopupSummary(st, false);
    st->openClock.Init();
    st->openClock.currentVal = 0.0;
    st->openClock.Start(1.0, 160.0);
    SetLayeredWindowAttributes(hPopup, 0, 0, LWA_ALPHA);
    SetWindowPos(hPopup, HWND_TOPMOST, st->targetX, st->targetY + DpiScale(10, GetDpiForWindow(hPopup)),
                 st->targetW, st->targetH, SWP_NOACTIVATE);
    ShowWindow(hPopup, SW_SHOW);
    SetForegroundWindow(hPopup);
    SetFocus(hPopup);
    SetTimer(hPopup, TIMER_CYCLE_POPUP_OPEN, 10, nullptr);
}


// ============================================================================
// Cycle Scheduler Clock Widget (Near Collapsed Pill)
// ============================================================================

constexpr wchar_t kCycleWidgetClass[] = L"SeamlessFirewall_CycleWidget_v1";
constexpr UINT_PTR TIMER_WIDGET_SINGLE_CLICK = 82;
constexpr UINT_PTR TIMER_WIDGET_TICK         = 83;
constexpr UINT_PTR TIMER_NAVIGATE_OPEN_CYCLE = 84;
constexpr UINT_PTR TIMER_WIDGET_REVEAL_ANIM  = 85;
static HWND g_hWidgetTooltip = nullptr;
static bool g_cycleWidgetHover = false;
static bool g_cycleWidgetPressed = false;
static bool g_widgetRevealed = false;
static MotionClock g_widgetRevealClock;
static std::wstring g_widgetClickExe;
static AppEntry g_pendingNavigateCycleApp;
static bool g_hasPendingNavigateCycle = false;

static bool IsExeEligibleForCycle(const std::wstring& exeLower) {
    if (exeLower.empty()) return false;
    if (g_excludedExes.count(exeLower)) return false;
    if (IsImmutableProtectedExe(exeLower)) return false;
    if (exeLower == g_lastFgExe) {
        if (g_lastFgIsOtherSessionOrUser) return false;
    } else if (IsExeOnlyInOtherSessionOrUser(exeLower)) {
        return false;
    }
    bool lockCrit = true;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        lockCrit = g_settings.lockSystemProcesses;
    }
    if (lockCrit && IsCriticalSystemExe(exeLower)) return false;
    if (g_extFwScanTick == 0) ScanExternalFirewallBlocks(false);
    std::lock_guard<std::mutex> lk(g_extFwMtx);
    auto itExt = g_extFwBlocks.find(exeLower);
    if (itExt != g_extFwBlocks.end() && itExt->second.dirMask != 0) return false;
    return true;
}

static bool ShouldWidgetBeAvailable() {
    bool showWidget = true;
    bool schedEnabled = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        showWidget = g_settings.showCycleWidget;
        schedEnabled = g_settings.enableCycleScheduler;
    }
    if (!showWidget || !schedEnabled || g_uiState != UiState::Line || g_hiddenByFullscreen) return false;
    return HasAnyActiveCycle() || IsExeEligibleForCycle(g_lastFgExe);
}

static void UpdateWidgetTooltipText(HWND hwnd) {
    if (!g_hWidgetTooltip) return;
    bool showTips = false;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        showTips = g_settings.showTooltips;
    }
    std::wstring tip;
    if (showTips) {
        CycleStatusSnapshot snap;
        if (GetWidgetCycleTarget(snap)) {
            std::wstring appName = GetFileNameOnly(snap.displayPath);
            if (snap.pausedByFocus || snap.pausedByUser) {
                tip = appName + L" \u00b7 Paused \u00b7 Click to resume, double-click to open";
            } else {
                tip = appName + L" \u00b7 " + (snap.phase == CyclePhase::Blocked ? L"Blocked " : L"Allowed ") +
                      FormatDurationCompact(snap.phaseRemainingMs) + L" left \u00b7 Click to pause, double-click to open";
            }
        } else if (!g_lastFgExe.empty()) {
            tip = GetFileNameOnly(g_lastFgExe) + L" \u00b7 Click to schedule Cycle Mode";
        } else {
            tip = L"Cycle Mode. Click to open the timer";
        }
    }
    TOOLINFOW ti{sizeof(ti)};
    ti.hwnd = hwnd;
    ti.uId = (UINT_PTR)hwnd;
    ti.lpszText = const_cast<LPWSTR>(tip.c_str());
    SendMessageW(g_hWidgetTooltip, TTM_UPDATETIPTEXTW, 0, (LPARAM)&ti);
}

static void NavigatePillAndOpenCycle(const std::wstring& targetExeLower) {
    if (!g_hWnd) return;
    KillTimer(g_hWnd, TIMER_COLLAPSE);
    g_uiState = UiState::Panel;
    g_userPinnedFilter = false;
    SyncForegroundStateAndFilter(true);
    RefreshAppList();
    auto findIdx = [&]() -> int {
        for (int i = 0; i < (int)g_appList.size(); ++i) {
            if (g_appList[i].exePath == targetExeLower) return i;
        }
        return -1;
    };
    int foundIdx = findIdx();
    if (foundIdx < 0 && !targetExeLower.empty()) {
        g_activeFilter = IsSystemPath(targetExeLower) ? AppFilter::SystemApps : AppFilter::UserApps;
        g_userRunningOnly = false;
        g_statusBanner.clear();
        RefreshAppList();
        foundIdx = findIdx();
    }
    if (foundIdx >= 0) {
        g_kbSelectedIdx = foundIdx;
        UINT dpi = GetDpiForWindow(g_hWnd);
        int rowStride = (g_lastRowStride > 0) ? g_lastRowStride : DpiScale(54, dpi);
        int listH = (g_lastListH > 0) ? g_lastListH : DpiScale(GetExpandedLogicalSize().cy - 110, dpi);
        int topPx = foundIdx * rowStride;
        int botPx = topPx + rowStride;
        double curScroll = g_scrollClock.toVal;
        if (topPx < (int)curScroll) {
            g_scrollClock.Start((double)topPx, 90.0);
        } else if (botPx > (int)curScroll + listH) {
            double nextS = std::min((double)g_maxScrollPx, (double)(botPx - listH));
            g_scrollClock.Start(nextS, 90.0);
        }
        g_pendingNavigateCycleApp = g_appList[foundIdx];
        g_hasPendingNavigateCycle = true;
        SetTimer(g_hWnd, TIMER_NAVIGATE_OPEN_CYCLE, 250, nullptr);
    }
    UpdateWindowGeometry(false);
    SetForegroundWindow(g_hWnd);
}

static void OpenCycleTargetFromWidget(const CycleStatusSnapshot* activeSnap) {
    CycleWidgetAction action = CycleWidgetAction::SchedulerOnly;
    Direction defDir = Direction::FullyOffline;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        action = g_settings.cycleWidgetAction;
        defDir = g_settings.defaultDirection;
    }
    AppEntry targetApp;
    if (activeSnap) {
        targetApp.exePath = activeSnap->exePath;
        targetApp.displayPath = activeSnap->displayPath;
        targetApp.name = GetFileNameOnly(activeSnap->displayPath);
        targetApp.block.direction = activeSnap->direction;
    } else if (!g_lastFgExe.empty()) {
        targetApp.exePath = g_lastFgExe;
        targetApp.displayPath = g_lastFgExe;
        targetApp.name = GetFileNameOnly(g_lastFgExe);
        targetApp.isExcluded = g_excludedExes.count(g_lastFgExe) > 0;
        targetApp.isImmutableLocked = IsImmutableProtectedExe(g_lastFgExe);
        targetApp.isCriticalLocked = IsCriticalSystemExe(g_lastFgExe);
        targetApp.isOtherSessionOrUser = g_lastFgIsOtherSessionOrUser;
        auto extFw = GetCachedExternalFirewallBlocks();
        auto itExt = extFw.find(g_lastFgExe);
        if (itExt != extFw.end() && itExt->second.dirMask != 0) targetApp.isExternalBlocked = true;
        auto itDir = g_pendingDirs.find(g_lastFgExe);
        targetApp.block.direction = (itDir != g_pendingDirs.end()) ? itDir->second : defDir;
    } else {
        if (g_hWnd) {
            g_uiState = UiState::Panel;
            g_userPinnedFilter = false;
            SyncForegroundStateAndFilter(true);
            RefreshAppList();
            UpdateWindowGeometry(false);
            SetForegroundWindow(g_hWnd);
        }
        return;
    }
    if (action == CycleWidgetAction::NavigatePill) {
        NavigatePillAndOpenCycle(targetApp.exePath);
    } else {
        OpenCyclePopupForApp(targetApp);
        if ((!g_hCyclePopup || !IsWindow(g_hCyclePopup)) && g_uiState == UiState::Line && !g_statusBanner.empty() && g_hWnd) {
            g_uiState = UiState::Panel;
            RefreshAppList();
            UpdateWindowGeometry(false);
        }
    }
}

static void ComputeCycleWidgetRect(RECT& outRc, double revealProgress = 1.0) {
    UINT dpi = g_hWnd ? GetDpiForWindow(g_hWnd) : 96;
    ModSettings s;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        s = g_settings;
    }

    RECT pillRc{};
    ComputeTargetRect(0.0, pillRc);

    HMONITOR mon = GetTargetMonitor(s.followCursorMonitor);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    RECT wa = mi.rcWork;

    int sizeStep = std::clamp(s.cycleWidgetSize, 0, 10);
    int w = DpiScale(24 + sizeStep * 4, dpi);
    int h = DpiScale(20 + sizeStep * 4, dpi);
    int gap = DpiScale(4, dpi);
    int slideOff = (int)std::round((1.0 - std::clamp(revealProgress, 0.0, 1.0)) * (double)DpiScale(6, dpi));
    int x = 0;
    int y = 0;

    switch (s.dockEdge) {
        case DockEdge::Left:
            x = wa.left - slideOff;
            y = pillRc.bottom + gap;
            if (y + h > wa.bottom) y = pillRc.top - gap - h;
            break;
        case DockEdge::Top:
            x = pillRc.right + gap;
            if (x + w > wa.right) x = pillRc.left - gap - w;
            y = wa.top - slideOff;
            break;
        case DockEdge::Bottom:
            x = pillRc.right + gap;
            if (x + w > wa.right) x = pillRc.left - gap - w;
            y = wa.bottom - h + slideOff;
            break;
        case DockEdge::TopLeft: {
            int d = DpiScale(21, dpi);
            x = wa.left + d - w / 2;
            y = wa.top + d - h / 2 - slideOff;
            break;
        }
        case DockEdge::BottomLeft: {
            int d = DpiScale(21, dpi);
            x = wa.left + d - w / 2;
            y = wa.bottom - d - h / 2 + slideOff;
            break;
        }
        case DockEdge::BottomRight: {
            int d = DpiScale(21, dpi);
            x = wa.right - d - w / 2;
            y = wa.bottom - d - h / 2 + slideOff;
            break;
        }
        default:
            x = wa.right - w + slideOff;
            y = pillRc.bottom + gap;
            if (y + h > wa.bottom) y = pillRc.top - gap - h;
            break;
    }

    x = std::clamp(x, (int)wa.left - slideOff, (int)wa.right - w + slideOff);
    y = std::clamp(y, (int)wa.top - slideOff, (int)wa.bottom - h + slideOff);
    outRc = {x, y, x + w, y + h};
}

static ID2D1Factory* g_d2dFactory = nullptr;
static IDWriteFactory* g_dwriteFactory = nullptr;
static ID2D1DCRenderTarget* g_d2dDcRt = nullptr;
static ID2D1SolidColorBrush* g_d2dFallbackBrush = nullptr;
static IDWriteTextFormat* g_dwriteEmojiFormat = nullptr;
static int g_cachedEmojiSizeStep = -1;
static UINT g_cachedEmojiDpi = 0;

static void RenderCycleWidgetLayered(HWND hwnd) {
    if (!hwnd || !IsWindow(hwnd)) return;
    RECT wrc{};
    ComputeCycleWidgetRect(wrc, g_widgetRevealClock.currentVal);
    int w = wrc.right - wrc.left;
    int h = wrc.bottom - wrc.top;
    if (w <= 0 || h <= 0) return;

    int sizeStep = 5;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        sizeStep = std::clamp(g_settings.cycleWidgetSize, 0, 10);
    }

    UINT dpi = GetDpiForWindow(hwnd);
    HDC hdcScreen = GetDC(nullptr);
    HDC memDC = CreateCompatibleDC(hdcScreen);
    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP hBmp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ oldBmp = SelectObject(memDC, hBmp);

    // 1/255 alpha keeps the entire hit rect clickable with zero visible border or fill
    if (bits) {
        uint32_t* px = static_cast<uint32_t*>(bits);
        size_t total = (size_t)w * (size_t)h;
        for (size_t i = 0; i < total; ++i) px[i] = 0x01000000u;
    }

    CycleStatusSnapshot snap;
    bool hasSnap = GetWidgetCycleTarget(snap);
    bool isPaused = hasSnap && (snap.pausedByFocus || snap.pausedByUser);
    BYTE alpha = (BYTE)std::clamp((int)std::round(g_widgetRevealClock.currentVal * 255.0), 0, 255);
    float scale = (float)dpi / 96.0f;
    float pressDy = g_cycleWidgetPressed ? 1.0f * scale : 0.0f;

    // A round Mocha badge with a stopwatch icon (no emoji): grey edge at rest, blue to mauve
    // while hovered; pause bars when the timer waits; a green or red dot for the phase.
    if (bits) {
        Gdiplus::Bitmap canvas(w, h, w * 4, PixelFormat32bppPARGB, (BYTE*)bits);
        Gdiplus::Graphics g(&canvas);
        g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
        g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
        g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
        float sizeMul = 1.0f + (float)sizeStep * 0.18f;
        Gdiplus::REAL d = (Gdiplus::REAL)std::min(w, h) - 2.0f * scale;
        Gdiplus::REAL bx = ((Gdiplus::REAL)w - d) * 0.5f, by = ((Gdiplus::REAL)h - d) * 0.5f + pressDy;
        Gdiplus::REAL ew = std::max(2.0f, 2.0f * scale);
        FwRound(g, Moc(g_cycleWidgetHover ? fwc::surface1 : fwc::surface0, 0.92), bx, by, d, d, d * 0.5f);
        if (g_cycleWidgetHover)
            FwGradEdge(g, bx, by, d, d, d * 0.5f, ew);
        else
            FwEdge(g, Moc(fwc::surface2), bx, by, d, d, d * 0.5f, ew);
        Gdiplus::REAL cx = (Gdiplus::REAL)w * 0.5f;
        Gdiplus::REAL cy = (Gdiplus::REAL)h * 0.5f + pressDy;
        if (hasSnap && isPaused) {
            Gdiplus::Pen pen(Moc(fwc::subtext0), std::max(1.5f, 1.55f * scale * sizeMul));
            pen.SetStartCap(Gdiplus::LineCapRound);
            pen.SetEndCap(Gdiplus::LineCapRound);
            Gdiplus::REAL dx = 2.6f * scale * sizeMul;
            Gdiplus::REAL hy = 4.2f * scale * sizeMul;
            g.DrawLine(&pen, cx - dx, cy - hy, cx - dx, cy + hy);
            g.DrawLine(&pen, cx + dx, cy - hy, cx + dx, cy + hy);
        } else {
            float iconPx = (10.0f + (float)sizeStep * 1.6f) * scale;
            Gdiplus::Font iconFont(FwIconFace(), iconPx, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
            Gdiplus::SolidBrush iconBr(Moc(fwc::text));
            Gdiplus::StringFormat sfCenter;
            sfCenter.SetAlignment(Gdiplus::StringAlignmentCenter);
            sfCenter.SetLineAlignment(Gdiplus::StringAlignmentCenter);
            Gdiplus::RectF rf(bx, by, d, d);
            g.DrawString(L"\xE916", -1, &iconFont, rf, &sfCenter, &iconBr);
        }
        if (hasSnap && !isPaused) {
            DWORD phaseCol = (snap.phase == CyclePhase::Blocked) ? fwc::red : fwc::green;
            float dotD = std::max(4.0f, (4.5f + (float)sizeStep * 0.5f) * scale);
            float dotX = (float)w - dotD - 1.5f * scale;
            float dotY = (float)h - dotD - 1.5f * scale + pressDy;
            Gdiplus::SolidBrush ringBr(Moc(fwc::crust));
            g.FillEllipse(&ringBr, dotX - scale, dotY - scale, dotD + 2.0f * scale, dotD + 2.0f * scale);
            Gdiplus::SolidBrush dotBr(Moc(phaseCol));
            g.FillEllipse(&dotBr, dotX, dotY, dotD, dotD);
        }
    }

    POINT ptDst{wrc.left, wrc.top};
    SIZE sz{w, h};
    POINT ptSrc{0, 0};
    BLENDFUNCTION bf{AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA};
    UpdateLayeredWindow(hwnd, hdcScreen, &ptDst, &sz, memDC, &ptSrc, 0, &bf, ULW_ALPHA);

    SelectObject(memDC, oldBmp);
    DeleteObject(hBmp);
    DeleteDC(memDC);
    ReleaseDC(nullptr, hdcScreen);
}

static LRESULT CALLBACK CycleWidgetWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            ApplyCaptureExclusionToWindow(hwnd);
            g_hWidgetTooltip = CreateWindowExW(WS_EX_TOPMOST, TOOLTIPS_CLASSW, nullptr,
                                               WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                               hwnd, nullptr, GetModuleHandleW(nullptr), nullptr);
            if (g_hWidgetTooltip) SetWindowTheme(g_hWidgetTooltip, L"DarkMode_Explorer", nullptr);
            if (g_hWidgetTooltip) {
                TOOLINFOW ti{sizeof(ti)};
                ti.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
                ti.hwnd = hwnd;
                ti.uId = (UINT_PTR)hwnd;
                ti.lpszText = const_cast<LPWSTR>(L"");
                SendMessageW(g_hWidgetTooltip, TTM_ADDTOOLW, 0, (LPARAM)&ti);
                SendMessageW(g_hWidgetTooltip, TTM_SETMAXTIPWIDTH, 0, 320);
                SendMessageW(g_hWidgetTooltip, TTM_SETDELAYTIME, TTDT_INITIAL, 300);
            }
            return 0;
        }
        case WM_NCACTIVATE:
            return TRUE;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps{};
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            RenderCycleWidgetLayered(hwnd);
            return 0;
        }
        case WM_DPICHANGED:
            SyncCycleWidgetWindow(true);
            return 0;
        case WM_MOUSEMOVE: {
            if (!g_cycleWidgetHover) {
                g_cycleWidgetHover = true;
                TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
                TrackMouseEvent(&tme);
                UpdateWidgetTooltipText(hwnd);
                RenderCycleWidgetLayered(hwnd);
            }
            return 0;
        }
        case WM_MOUSELEAVE: {
            g_cycleWidgetHover = false;
            g_cycleWidgetPressed = false;
            if (g_hWidgetTooltip) {
                TOOLINFOW ti{sizeof(ti)};
                ti.hwnd = hwnd;
                ti.uId = (UINT_PTR)hwnd;
                ti.lpszText = const_cast<LPWSTR>(L"");
                SendMessageW(g_hWidgetTooltip, TTM_UPDATETIPTEXTW, 0, (LPARAM)&ti);
            }
            RenderCycleWidgetLayered(hwnd);
            return 0;
        }
        case WM_LBUTTONDOWN: {
            g_cycleWidgetPressed = true;
            RenderCycleWidgetLayered(hwnd);
            return 0;
        }
        case WM_LBUTTONUP: {
            g_cycleWidgetPressed = false;
            RenderCycleWidgetLayered(hwnd);
            CycleStatusSnapshot snap;
            if (GetWidgetCycleTarget(snap)) {
                g_widgetClickExe = snap.exePath;
                SetTimer(hwnd, TIMER_WIDGET_SINGLE_CLICK, GetDoubleClickTime(), nullptr);
            } else if (!g_hCyclePopup || !IsWindow(g_hCyclePopup)) {
                OpenCycleTargetFromWidget(nullptr);
            }
            return 0;
        }
        case WM_LBUTTONDBLCLK: {
            KillTimer(hwnd, TIMER_WIDGET_SINGLE_CLICK);
            g_cycleWidgetPressed = false;
            RenderCycleWidgetLayered(hwnd);
            CycleStatusSnapshot snap;
            if (GetWidgetCycleTarget(snap)) {
                OpenCycleTargetFromWidget(&snap);
            } else if (!g_hCyclePopup || !IsWindow(g_hCyclePopup)) {
                OpenCycleTargetFromWidget(nullptr);
            }
            return 0;
        }
        case WM_TIMER: {
            if (wParam == TIMER_WIDGET_SINGLE_CLICK) {
                KillTimer(hwnd, TIMER_WIDGET_SINGLE_CLICK);
                if (!g_widgetClickExe.empty()) {
                    bool nowPaused = false;
                    ToggleCyclePauseForApp(g_widgetClickExe, nowPaused);
                }
                RenderCycleWidgetLayered(hwnd);
            } else if (wParam == TIMER_WIDGET_REVEAL_ANIM) {
                bool more = g_widgetRevealClock.Step();
                RenderCycleWidgetLayered(hwnd);
                if (!more) {
                    KillTimer(hwnd, TIMER_WIDGET_REVEAL_ANIM);
                    if (!g_widgetRevealed && IsWindowVisible(hwnd)) {
                        ShowWindow(hwnd, SW_HIDE);
                    }
                }
            } else if (wParam == TIMER_WIDGET_TICK) {
                if (!HasAnyActiveCycle()) {
                    KillTimer(hwnd, TIMER_WIDGET_TICK);
                    if (IsWindowVisible(hwnd)) RenderCycleWidgetLayered(hwnd);
                } else if (IsWindowVisible(hwnd)) {
                    if (g_cycleWidgetHover) UpdateWidgetTooltipText(hwnd);
                    RenderCycleWidgetLayered(hwnd);
                }
            }
            return 0;
        }
        case WM_DESTROY: {
            KillTimer(hwnd, TIMER_WIDGET_SINGLE_CLICK);
            KillTimer(hwnd, TIMER_WIDGET_TICK);
            KillTimer(hwnd, TIMER_WIDGET_REVEAL_ANIM);
            g_widgetRevealed = false;
            if (g_hWidgetTooltip) { DestroyWindow(g_hWidgetTooltip); g_hWidgetTooltip = nullptr; }
            g_cycleWidgetHover = false;
            g_cycleWidgetPressed = false;
            g_hCycleWidget = nullptr;
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static void DestroyCycleWidgetWindow() {
    if (g_hCycleWidget && IsWindow(g_hCycleWidget)) {
        DestroyWindow(g_hCycleWidget);
    }
    g_hCycleWidget = nullptr;
}

static void SetCycleWidgetRevealed(bool reveal) {
    if (!ShouldWidgetBeAvailable()) reveal = false;
    if (reveal == g_widgetRevealed && (!reveal || (g_hCycleWidget && IsWindowVisible(g_hCycleWidget)))) {
        return;
    }
    g_widgetRevealed = reveal;
    if (reveal && (!g_hCycleWidget || !IsWindow(g_hCycleWidget))) {
        static bool widgetReg = false;
        if (!widgetReg) {
            WNDCLASSEXW wwc{sizeof(wwc)};
            wwc.style = CS_DBLCLKS;
            wwc.lpfnWndProc = CycleWidgetWndProc;
            wwc.hInstance = GetModuleHandleW(nullptr);
            wwc.hCursor = LoadCursorW(nullptr, IDC_HAND);
            wwc.lpszClassName = kCycleWidgetClass;
            RegisterClassExW(&wwc);
            widgetReg = true;
        }
        g_widgetRevealClock.Init();
        g_widgetRevealClock.currentVal = 0.0;
        RECT wrc{};
        ComputeCycleWidgetRect(wrc, 0.0);
        g_hCycleWidget = CreateWindowExW(
            WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED,
            kCycleWidgetClass, L"Seamless Windows Firewall clock", WS_POPUP,
            wrc.left, wrc.top, wrc.right - wrc.left, wrc.bottom - wrc.top,
            nullptr, nullptr, GetModuleHandleW(nullptr), nullptr);
        if (!g_hCycleWidget) return;
    }
    if (!g_hCycleWidget || !IsWindow(g_hCycleWidget)) return;

    if (reveal) {
        ShowWindow(g_hCycleWidget, SW_SHOWNOACTIVATE);
        g_widgetRevealClock.Start(1.0, 180.0);
        SetTimer(g_hCycleWidget, TIMER_WIDGET_REVEAL_ANIM, 10, nullptr);
        if (HasAnyActiveCycle()) SetTimer(g_hCycleWidget, TIMER_WIDGET_TICK, 500, nullptr);
        RenderCycleWidgetLayered(g_hCycleWidget);
    } else {
        KillTimer(g_hCycleWidget, TIMER_WIDGET_TICK);
        if (IsWindowVisible(g_hCycleWidget)) {
            g_widgetRevealClock.Start(0.0, 160.0);
            SetTimer(g_hCycleWidget, TIMER_WIDGET_REVEAL_ANIM, 10, nullptr);
        }
    }
}

static void SyncCycleWidgetWindow(bool reposition) {
    bool available = ShouldWidgetBeAvailable();
    if (g_hWnd) {
        if (available) SetTimer(g_hWnd, TIMER_WIDGET_PROXIMITY, 75, nullptr);
        else KillTimer(g_hWnd, TIMER_WIDGET_PROXIMITY);
    }
    if (!available) {
        if (g_hCycleWidget && IsWindow(g_hCycleWidget) && IsWindowVisible(g_hCycleWidget)) {
            if (g_uiState != UiState::Line || g_hiddenByFullscreen) {
                KillTimer(g_hCycleWidget, TIMER_WIDGET_REVEAL_ANIM);
                KillTimer(g_hCycleWidget, TIMER_WIDGET_TICK);
                g_widgetRevealed = false;
                g_widgetRevealClock.currentVal = 0.0;
                ShowWindow(g_hCycleWidget, SW_HIDE);
            } else {
                SetCycleWidgetRevealed(false);
            }
        }
        return;
    }
    if (g_hCycleWidget && IsWindow(g_hCycleWidget) && IsWindowVisible(g_hCycleWidget)) {
        if (HasAnyActiveCycle()) SetTimer(g_hCycleWidget, TIMER_WIDGET_TICK, 500, nullptr);
        else KillTimer(g_hCycleWidget, TIMER_WIDGET_TICK);
        if (reposition) RenderCycleWidgetLayered(g_hCycleWidget);
    }
}

static LRESULT CALLBACK FloatingWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (g_wmTaskbarCreated && msg == g_wmTaskbarCreated) {
        g_trayAdded = false;
        AddTrayIcon(hwnd);
        return 0;
    }
    // A panel that is fading out takes no more clicks or keys.
    if (g_panelClosing && ((msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) || msg == WM_KEYDOWN || msg == WM_CHAR))
        return 0;
    switch (msg) {
        case WM_CREATE: {
            g_wmTaskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
            if (g_wmTaskbarCreated) ChangeWindowMessageFilterEx(hwnd, g_wmTaskbarCreated, MSGFLT_ALLOW, nullptr);
            ChangeWindowMessageFilterEx(hwnd, WM_APP_TRAY_CALLBACK, MSGFLT_ALLOW, nullptr);
            SetWindowFrameMode(hwnd, false);
            ApplyCaptureExclusionToWindow(hwnd);
            RegisterAllHotkeys(hwnd);
            AddTrayIcon(hwnd);
            InitTooltip(hwnd);
            if (!IsProcessElevated()) {
                g_needsElevation = true;
                g_statusBanner = L"Windhawk needs to run as administrator to block apps.";
            }
            SetTimer(hwnd, TIMER_FULLSCREEN, 1000, nullptr);
            SetTimer(hwnd, TIMER_LATE_CHILD_POLL, 3000, nullptr);
            SetTimer(hwnd, TIMER_WARM_PANEL, 2000, nullptr);
            SyncHoverSensorTimer(hwnd);
            ListenSync();
            return 0;
        }
        case WM_NCACTIVATE:
            return TRUE;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
            PaintFloatingWindow(hwnd);
            return 0;
        case WM_DPICHANGED:
            ClearIconCache();
            UpdateWindowGeometry(true);
            return 0;
        case WM_MOUSEMOVE: {
            if (!g_mouseInside) {
                g_mouseInside = true;
                TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
                TrackMouseEvent(&tme);
                RequestRepaint();
                KillTimer(hwnd, TIMER_COLLAPSE);
                bool hoverExp = true;
                {
                    std::lock_guard<std::mutex> lk(g_settingsMtx);
                    hoverExp = g_settings.hoverExpand;
                }
                if (hoverExp && g_uiState == UiState::Line) {
                    g_uiState = UiState::Panel;
                    g_userPinnedFilter = false;
                    SyncForegroundStateAndFilter(true);
                    RefreshAppList();
                    UpdateWindowGeometry(false);
                }
            }
            if (g_drag.dragging) {
                POINT cur{};
                GetCursorPos(&cur);
                RECT rc = g_drag.startRect;
                int w = rc.right - rc.left;
                int h = rc.bottom - rc.top;
                HMONITOR mon = MonitorFromPoint(cur, MONITOR_DEFAULTTONEAREST);
                MONITORINFO mi{sizeof(mi)};
                GetMonitorInfoW(mon, &mi);
                int nx = (g_drag.axisMode == 1) ? rc.left : std::clamp((int)(cur.x - g_drag.cursorAnchor.x), (int)mi.rcWork.left, (int)mi.rcWork.right - w);
                int ny = (g_drag.axisMode == 2) ? rc.top  : std::clamp((int)(cur.y - g_drag.cursorAnchor.y), (int)mi.rcWork.top, (int)mi.rcWork.bottom - h);
                SetWindowPos(hwnd, HWND_TOPMOST, nx, ny, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);
                return 0;
            }
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            const HitRect* hr = HitTestControl(pt);
            int newHover = hr ? hr->id : -1;
            if (newHover != g_hoverHitId) {
                g_hoverHitId = newHover;
                UpdateTooltipText(hwnd, hr ? hr->tooltip.c_str() : L"");
                RequestRepaint();
            }
            return 0;
        }
        case WM_ACTIVATE: {
            if (LOWORD(wParam) == WA_INACTIVE && !g_pinned && g_uiState == UiState::Panel && !g_drag.dragging) {
                HWND newActive = reinterpret_cast<HWND>(lParam);
                if ((!g_hCyclePopup || !IsWindow(g_hCyclePopup)) && (!g_hCycleWidget || newActive != g_hCycleWidget) &&
                    (!g_hConfirm || newActive != g_hConfirm)) {
                    g_hasPendingNavigateCycle = false;
                    KillTimer(hwnd, TIMER_NAVIGATE_OPEN_CYCLE);
                    KillTimer(hwnd, TIMER_OUTSIDE_CLICK);
                    g_uiState = UiState::Line;
                    g_kbSelectedIdx = -1;
                    g_userPinnedFilter = false;
                    UpdateWindowGeometry(false);
                }
            }
            return 0;
        }
        case WM_MOUSELEAVE: {
            g_mouseInside = false;
            g_hoverHitId = -1;
            UpdateTooltipText(hwnd, L"");
            RequestRepaint();
            return 0;
        }
        case WM_LBUTTONDOWN: {
            if (g_hCyclePopup && IsWindow(g_hCyclePopup)) DestroyWindow(g_hCyclePopup);
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            const HitRect* hr = HitTestControl(pt);
            if (hr && hr->kind == HitRect::HeaderDrag) {
                SetCapture(hwnd);
                g_drag.dragging = true;
                POINT cur{};
                GetCursorPos(&cur);
                GetWindowRect(hwnd, &g_drag.startRect);
                g_drag.cursorAnchor = {cur.x - g_drag.startRect.left, cur.y - g_drag.startRect.top};
                g_drag.axisMode = 0;
                return 0;
            }
            if (hr) {
                if (hr->rowIndex >= 0 && (hr->kind == HitRect::RowToggle || hr->kind == HitRect::RowDirection ||
                                          hr->kind == HitRect::RowExclude || hr->kind == HitRect::RowExternalLocked)) {
                    g_kbSelectedIdx = hr->rowIndex;
                }
                g_pressedHitId = hr->id;
                HandleClickAction(*hr);
            }
            if (g_uiState == UiState::Panel) SetForegroundWindow(hwnd);
            return 0;
        }
        case WM_LBUTTONDBLCLK: {
            if (g_uiState != UiState::Panel) break;
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            const HitRect* hr = HitTestControl(pt);
            if (hr && hr->rowIndex >= 0 && hr->rowIndex < (int)g_appList.size() &&
                (hr->kind == HitRect::RowBody || hr->kind == HitRect::RowDirection)) {
                OpenCyclePopupForApp(g_appList[hr->rowIndex]);
            }
            return 0;
        }
        case WM_RBUTTONUP: {
            if (g_uiState != UiState::Panel) break;
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            const HitRect* hr = HitTestControl(pt);
            if (hr && hr->rowIndex >= 0 && hr->rowIndex < (int)g_appList.size()) {
                AppEntry app = g_appList[hr->rowIndex];
                CycleStatusSnapshot cyc;
                bool active = GetCycleSnapshot(app.exePath, cyc);
                std::vector<swfset::TrayRow> rows;
                swfset::TrayRow r;
                r.id = 1;
                r.glyph = L"\xE916";
                r.label = L"Block on a timer...";
                rows.push_back(r);
                if (active) {
                    r = {};
                    r.id = 2;
                    r.glyph = L"\xE71A";
                    r.label = L"Stop the timer";
                    rows.push_back(r);
                }
                POINT scr = pt;
                ClientToScreen(hwnd, &scr);
                int cmd = swfset::ShowTrayMenu(hwnd, &scr, rows);
                if (cmd == 1) OpenCyclePopupForApp(app);
                else if (cmd == 2) {
                    StopCycleForApp(app.displayPath, true);
                    RefreshAppList();
                    RequestRepaint();
                }
            }
            return 0;
        }
        case WM_LBUTTONUP: {
            if (g_drag.dragging) {
                g_drag.dragging = false;
                ReleaseCapture();
                RECT rc{};
                GetWindowRect(hwnd, &rc);
                g_panelMon = MonitorFromRect(&rc, MONITOR_DEFAULTTONEAREST);
                g_panelMoved = true;
                g_panelMovedPos = POINT{rc.left, rc.top};
                UpdateWindowGeometry(false);
            }
            g_pressedHitId = -1;
            return 0;
        }
        case WM_CAPTURECHANGED: {
            if (g_drag.dragging) {
                g_drag.dragging = false;
                SetWindowPos(hwnd, HWND_TOPMOST, g_drag.startRect.left, g_drag.startRect.top,
                             0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
            }
            return 0;
        }
        case WM_MOUSEWHEEL: {
            UINT dpi = GetDpiForWindow(hwnd);
            int delta = GET_WHEEL_DELTA_WPARAM(wParam);
            double stepPx = (double)DpiScale(72, dpi) * ((double)delta / (double)WHEEL_DELTA);
            double nextTarget = std::clamp(g_scrollClock.toVal - stepPx, 0.0, (double)g_maxScrollPx);
            g_scrollClock.Start(nextTarget, 75.0);
            SetTimer(hwnd, TIMER_ANIM_VSYNC, 10, nullptr);
            return 0;
        }
        case WM_TIMER: {
            if (wParam == TIMER_COLLAPSE) {
                KillTimer(hwnd, TIMER_COLLAPSE);
                if (!g_mouseInside && !g_pinned && g_uiState != UiState::Line) {
                    g_hasPendingNavigateCycle = false;
                    KillTimer(hwnd, TIMER_NAVIGATE_OPEN_CYCLE);
                    g_uiState = UiState::Line;
                    g_kbSelectedIdx = -1;
                    g_userPinnedFilter = false;
                    UpdateWindowGeometry(false);
                }
            } else if (wParam == TIMER_ANIM_VSYNC) {
                bool wasExpandActive = g_expandClock.active;
                bool wasScroll = g_scrollClock.active;
                bool fadeTick = wasExpandActive && g_panelFading;
                bool moreExpand = g_expandClock.Step();
                bool moreScroll = g_scrollClock.Step();
                bool morePulse  = g_pillPulse.Step();
                if (fadeTick) {
                    PanelFadeFrame(hwnd);
                } else if (wasExpandActive || moreExpand) {
                    RECT rc{};
                    ComputeTargetRect(g_expandClock.currentVal, rc);
                    SetWindowPos(hwnd, HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
                                 SWP_NOACTIVATE | SWP_NOCOPYBITS);
                }
                if (wasExpandActive && !moreExpand) {
                    if (g_panelClosing) {
                        PanelFinishClose();
                    } else if (g_panelFading) {
                        PanelFinishOpen(hwnd);
                    } else if (g_uiState == UiState::Line) {
                        SetWindowFrameMode(hwnd, false);
                        SyncCycleWidgetWindow(true);
                    }
                }
                if (!fadeTick || wasScroll || morePulse) RequestRepaint();
                if (!moreExpand && !moreScroll && !morePulse) {
                    KillTimer(hwnd, TIMER_ANIM_VSYNC);
                }
            } else if (wParam == TIMER_HOVER_SENSOR) {
                ModSettings s;
                {
                    std::lock_guard<std::mutex> lk(g_settingsMtx);
                    s = g_settings;
                }
                if (g_uiState == UiState::Line && s.hoverExpand && s.expandHoverHitArea &&
                    !g_hiddenByFullscreen && !g_drag.dragging) {
                    POINT cur{};
                    GetCursorPos(&cur);
                    RECT rc{};
                    GetWindowRect(hwnd, &rc);
                    UINT dpi = GetDpiForWindow(hwnd);
                    int m = DpiScale(s.hoverHitMarginPx, dpi);
                    InflateRect(&rc, m, m);
                    bool overWidget = false;
                    if (g_hCycleWidget && IsWindowVisible(g_hCycleWidget)) {
                        RECT wrc{};
                        GetWindowRect(g_hCycleWidget, &wrc);
                        overWidget = g_cycleWidgetHover || PtInRect(&wrc, cur);
                    }
                    if (!overWidget && PtInRect(&rc, cur)) {
                        KillTimer(hwnd, TIMER_HOVER_SENSOR);
                        KillTimer(hwnd, TIMER_COLLAPSE);
                        g_uiState = UiState::Panel;
                        g_userPinnedFilter = false;
                        SyncForegroundStateAndFilter(true);
                        RefreshAppList();
                        UpdateWindowGeometry(false);
                    }
                }
            } else if (wParam == TIMER_WIDGET_PROXIMITY) {
                bool followMon = false;
                { std::lock_guard<std::mutex> lk(g_settingsMtx); followMon = g_settings.followCursorMonitor; }
                if (followMon && g_uiState == UiState::Line && !g_drag.dragging && !g_hiddenByFullscreen &&
                    !g_panelClosing) {
                    if (GetTargetMonitor(true) != MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST)) {
                        UpdateWindowGeometry(true);
                    }
                }
                if (!ShouldWidgetBeAvailable()) {
                    if (g_widgetRevealed) SetCycleWidgetRevealed(false);
                    KillTimer(hwnd, TIMER_WIDGET_PROXIMITY);
                } else {
                    POINT cur{};
                    GetCursorPos(&cur);
                    RECT pillRc{}, wrc{};
                    ComputeTargetRect(0.0, pillRc);
                    ComputeCycleWidgetRect(wrc, 1.0);
                    RECT zone{};
                    UnionRect(&zone, &pillRc, &wrc);
                    UINT dpi = GetDpiForWindow(hwnd);
                    int prox = DpiScale(42, dpi);
                    InflateRect(&zone, prox, prox);
                    bool inZone = g_cycleWidgetHover || PtInRect(&zone, cur);
                    if (inZone != g_widgetRevealed) {
                        SetCycleWidgetRevealed(inZone);
                    }
                }
            } else if (wParam == TIMER_LATE_CHILD_POLL) {
                SyncLateChildBlocks();
            } else if (wParam == TIMER_EVENT_FLUSH) {
                KillTimer(hwnd, TIMER_EVENT_FLUSH);
                g_evFlushArmed = false;
                bool fg = g_evFgDirty, apps = g_evAppsDirty;
                g_evFgDirty = g_evAppsDirty = false;
                if (fg) SendMessageW(hwnd, WM_APP_FOREGROUND_CHG, 0, 0);
                if (apps) SendMessageW(hwnd, WM_APP_REFRESH_APPS, 0, 0);
            } else if (wParam == TIMER_WARM_PANEL) {
                KillTimer(hwnd, TIMER_WARM_PANEL);
                WarmPanelDraw(hwnd);
            } else if (wParam == TIMER_DEBOUNCE_REFRESH) {
                KillTimer(hwnd, TIMER_DEBOUNCE_REFRESH);
                SyncLateChildBlocks();
                if (g_uiState != UiState::Line) {
                    RefreshAppList();
                    RequestRepaint();
                }
            } else if (wParam == TIMER_OUTSIDE_CLICK) {
                if (g_uiState != UiState::Panel || g_pinned) {
                    KillTimer(hwnd, TIMER_OUTSIDE_CLICK);
                } else if (!g_drag.dragging && !(g_hCyclePopup && IsWindow(g_hCyclePopup))) {
                    bool btnDown = ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0) ||
                                   ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0);
                    if (btnDown) SendMessageW(hwnd, WM_APP_OUTSIDE_CLICK, 0, 0);
                }
            } else if (wParam == TIMER_NAVIGATE_OPEN_CYCLE) {
                KillTimer(hwnd, TIMER_NAVIGATE_OPEN_CYCLE);
                if (g_hasPendingNavigateCycle && g_uiState == UiState::Panel) {
                    g_hasPendingNavigateCycle = false;
                    OpenCyclePopupForApp(g_pendingNavigateCycleApp);
                } else {
                    g_hasPendingNavigateCycle = false;
                }
            } else if (wParam == TIMER_CYCLE_UI) {
                if (g_uiState == UiState::Panel && HasAnyActiveCycle()) {
                    RequestRepaint();
                } else {
                    KillTimer(hwnd, TIMER_CYCLE_UI);
                }
            } else if (wParam == TIMER_FULLSCREEN) {
                FullscreenBehavior fb = FullscreenBehavior::Hide;
                {
                    std::lock_guard<std::mutex> lk(g_settingsMtx);
                    fb = g_settings.fullscreenBehavior;
                }
                bool fsActive = IsFullscreenActive();
                ListenPump(fsActive);
                bool shouldHide = (fb == FullscreenBehavior::Hide) && fsActive;
                if (shouldHide && g_hCyclePopup && IsWindow(g_hCyclePopup)) {
                    DestroyWindow(g_hCyclePopup);
                }
                if (shouldHide && g_panelClosing) PanelFinishClose();
                if (shouldHide && IsWindowVisible(hwnd)) {
                    ShowWindow(hwnd, SW_HIDE);
                    g_hiddenByFullscreen = true;
                    SyncCycleWidgetWindow(false);
                } else if (!shouldHide && g_hiddenByFullscreen) {
                    ShowWindow(hwnd, SW_SHOWNOACTIVATE);
                    g_hiddenByFullscreen = false;
                    SyncCycleWidgetWindow(false);
                }
            }
            return 0;
        }
        case WM_KEYDOWN: {
            if (g_uiState != UiState::Panel) break;
            if (wParam == VK_ESCAPE) {
                g_hasPendingNavigateCycle = false;
                KillTimer(hwnd, TIMER_NAVIGATE_OPEN_CYCLE);
                g_uiState = UiState::Line;
                g_kbSelectedIdx = -1;
                g_userPinnedFilter = false;
                UpdateWindowGeometry(false);
                return 0;
            }
            if (g_appList.empty()) return 0;
            auto ensureVisible = [&](int idx) {
                int topPx = idx * g_lastRowStride;
                int botPx = topPx + g_lastRowStride;
                double curScroll = g_scrollClock.toVal;
                if (topPx < (int)curScroll) {
                    g_scrollClock.Start((double)topPx, 90.0);
                    SetTimer(hwnd, TIMER_ANIM_VSYNC, 10, nullptr);
                } else if (botPx > (int)curScroll + g_lastListH) {
                    double nextS = std::min((double)g_maxScrollPx, (double)(botPx - g_lastListH));
                    g_scrollClock.Start(nextS, 90.0);
                    SetTimer(hwnd, TIMER_ANIM_VSYNC, 10, nullptr);
                }
            };
            if (wParam == VK_DOWN) {
                g_kbSelectedIdx = (g_kbSelectedIdx < 0) ? 0 : std::min((int)g_appList.size() - 1, g_kbSelectedIdx + 1);
                ensureVisible(g_kbSelectedIdx);
                RequestRepaint();
                return 0;
            } else if (wParam == VK_UP) {
                g_kbSelectedIdx = (g_kbSelectedIdx <= 0) ? 0 : g_kbSelectedIdx - 1;
                ensureVisible(g_kbSelectedIdx);
                RequestRepaint();
                return 0;
            } else if ((wParam == VK_RETURN || wParam == VK_SPACE) && g_kbSelectedIdx >= 0 && g_kbSelectedIdx < (int)g_appList.size()) {
                HitRect syn{{}, 0, g_kbSelectedIdx, L"", HitRect::RowToggle};
                HandleClickAction(syn);
                return 0;
            } else if ((wParam == VK_LEFT || wParam == VK_RIGHT) && g_kbSelectedIdx >= 0 && g_kbSelectedIdx < (int)g_appList.size()) {
                HitRect syn{{}, 0, g_kbSelectedIdx, L"", HitRect::RowDirection};
                HandleClickAction(syn);
                return 0;
            }
            break;
        }
        case WM_HOTKEY: {
            int hkId = (int)wParam;
            if (hkId == HK_TOGGLE_FG) {
                HWND fg = GetForegroundWindow();
                DWORD pid = 0;
                if (fg && fg != hwnd) GetWindowThreadProcessId(fg, &pid);
                std::wstring exe = pid ? QueryProcessExePath(pid) : L"";
                if (!exe.empty()) {
                    std::wstring low = ToLower(exe);
                    auto extFw = ScanExternalFirewallBlocks();
                    auto itExt = extFw.find(low);
                    if (itExt != extFw.end() && itExt->second.dirMask != 0) {
                        g_activeFilter = AppFilter::Blocked;
                        g_blockedFirewallOnly = true;
                        g_statusBanner = L"Windows Firewall already blocks this app. Change it in Windows Defender Firewall.";
                        TriggerPulse(PulseKind::BlockedRed);
                        if (g_uiState == UiState::Line) {
                            g_uiState = UiState::Panel;
                            RefreshAppList();
                            UpdateWindowGeometry(false);
                        } else {
                            RefreshAppList();
                            RequestRepaint();
                        }
                        return 0;
                    }
                    bool isBlocked = false;
                    {
                        std::lock_guard<std::mutex> lk(g_engineMtx);
                        auto it = g_blocks.find(low);
                        isBlocked = (it != g_blocks.end() && it->second.blocked);
                    }
                    if (isBlocked) ApplyAllow(exe);
                    else {
                        ModSettings s;
                        {
                            std::lock_guard<std::mutex> lk(g_settingsMtx);
                            s = g_settings;
                        }
                        auto itDir = g_pendingDirs.find(low);
                        Direction dir = (itDir != g_pendingDirs.end()) ? itDir->second : s.defaultDirection;
                        ApplyBlock(exe, dir, s.includeChildProcesses, true);
                    }
                    RefreshAppList();
                    RequestRepaint();
                }
            } else if (hkId == HK_EXPAND_PILL) {
                g_uiState = (g_uiState == UiState::Line) ? UiState::Panel : UiState::Line;
                if (g_uiState == UiState::Panel) {
                    g_userPinnedFilter = false;
                    SyncForegroundStateAndFilter(true);
                    RefreshAppList();
                    g_kbSelectedIdx = g_appList.empty() ? -1 : 0;
                    SetForegroundWindow(hwnd);
                } else {
                    g_kbSelectedIdx = -1;
                    g_userPinnedFilter = false;
                }
                UpdateWindowGeometry(false);
            } else if (hkId == HK_RESTORE_ALL) {
                RestoreAllSessionBlocks();
                RefreshAppList();
                RequestRepaint();
            }
            return 0;
        }
        case WM_APP_OUTSIDE_CLICK: {
            if (g_uiState != UiState::Panel || g_pinned) { SyncOutsideMouseHook(false); return 0; }
            if (g_drag.dragging || (g_hCyclePopup && IsWindow(g_hCyclePopup))) return 0;
            POINT cur{};
            GetCursorPos(&cur);
            RECT prc{};
            GetWindowRect(hwnd, &prc);
            bool keep = PtInRect(&prc, cur) != FALSE;
            for (HWND other : {g_hCycleWidget, g_hConfirm, g_hListenBox}) {
                if (keep || !other || !IsWindowVisible(other)) continue;
                RECT orc{};
                GetWindowRect(other, &orc);
                keep = PtInRect(&orc, cur) != FALSE;
            }
            if (keep) return 0;
            KillTimer(hwnd, TIMER_OUTSIDE_CLICK);
            g_hasPendingNavigateCycle = false;
            KillTimer(hwnd, TIMER_NAVIGATE_OPEN_CYCLE);
            g_uiState = UiState::Line;
            g_kbSelectedIdx = -1;
            g_userPinnedFilter = false;
            UpdateWindowGeometry(false);
            return 0;
        }
        case WM_APP_TRAY_CALLBACK: {
            switch (LOWORD(lParam)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    TogglePanelFromTray();
                    break;
                case WM_CONTEXTMENU:
                    ShowTrayContextMenu(hwnd, POINT{GET_X_LPARAM(wParam), GET_Y_LPARAM(wParam)});
                    break;
            }
            return 0;
        }
        case WM_APP_FOREGROUND_CHG: {
            SyncForegroundStateAndFilter(g_uiState != UiState::Line);
            if (g_uiState == UiState::Line) {
                TriggerForegroundPulse(g_lastFgExe);
                SyncCycleWidgetWindow(false);
                RequestRepaint();
            } else {
                RefreshAppList();
                RequestRepaint();
            }
            return 0;
        }
        case WM_APP_REFRESH_APPS: {
            bool hasChildBlocks = false;
            if (g_uiState == UiState::Line) {
                std::lock_guard<std::mutex> lk(g_engineMtx);
                for (const auto& kv : g_blocks) {
                    if (kv.second.blocked && kv.second.includeChildProcesses) { hasChildBlocks = true; break; }
                }
            }
            if (g_uiState != UiState::Line || hasChildBlocks) {
                SetTimer(hwnd, TIMER_DEBOUNCE_REFRESH, 300, nullptr);
            }
            return 0;
        }
        case WM_SETTINGCHANGE: {
            if (lParam && !lstrcmpiW((LPCWSTR)lParam, L"ImmersiveColorSet")) {
                g_glassApplied = false;
                g_lastRoundedFrame = !g_lastRoundedFrame;
                SetWindowFrameMode(hwnd, (g_uiState == UiState::Panel) || g_expandClock.active);
                RequestRepaint();
            }
            if (g_hCycleWidget && IsWindow(g_hCycleWidget) && IsWindowVisible(g_hCycleWidget)) {
                RenderCycleWidgetLayered(g_hCycleWidget);
            }
            return 0;
        }
        case WM_APP_CYCLE_APPLY: {
            std::vector<CyclePendingAction> actions;
            {
                std::lock_guard<std::mutex> lk(g_cycleMtx);
                actions.swap(g_pendingCycleActions);
            }
            for (const auto& act : actions) {
                if (act.kind == CyclePendingAction::SwitchBlock || act.kind == CyclePendingAction::SwitchAllow) {
                    std::wstring low = ToLower(act.displayPath);
                    std::lock_guard<std::mutex> lk(g_cycleMtx);
                    auto itC = g_cycles.find(low);
                    if (itC == g_cycles.end()) continue;
                    if (act.kind == CyclePendingAction::SwitchBlock &&
                        itC->second.pausedByFocus && itC->second.cfg.allowWhenUnfocused) {
                        continue;
                    }
                }
                if (act.kind == CyclePendingAction::SwitchBlock) {
                    ApplyBlock(act.displayPath, act.dir, act.includeChildren, false);
                } else if (act.kind == CyclePendingAction::SwitchAllow) {
                    ApplyAllow(act.displayPath);
                } else if (act.kind == CyclePendingAction::EndAllow) {
                    ApplyAllow(act.displayPath);
                    LogAudit(L"CYCLE COMPLETED " + act.displayPath);
                } else if (act.kind == CyclePendingAction::WipeExited) {
                    ApplyAllow(act.displayPath);
                    LogAudit(L"CYCLE WIPED (process exited) " + act.displayPath);
                }
            }
            if (!actions.empty()) {
                if (g_uiState != UiState::Line) RefreshAppList();
                SyncCycleWidgetWindow(true);
                RequestRepaint();
            }
            return 0;
        }
        case WM_APP_CYCLE_STATE: {
            if (HasAnyActiveCycle() && g_uiState == UiState::Panel) {
                SetTimer(hwnd, TIMER_CYCLE_UI, 250, nullptr);
            } else if (!HasAnyActiveCycle()) {
                KillTimer(hwnd, TIMER_CYCLE_UI);
            }
            if (g_uiState != UiState::Line) RefreshAppList();
            SyncCycleWidgetWindow(true);
            RequestRepaint();
            return 0;
        }
        case WM_APP_LISTEN_FOUND: {
            std::unique_ptr<ListenAsk> a(reinterpret_cast<ListenAsk*>(lParam));
            if (a && g_listenRunning) {
                g_listenQueue.push_back(std::move(a));
                ListenPump(IsFullscreenActive());
            }
            return 0;
        }
        case WM_APP_LISTEN_DONE:
            ListenBoxAnswered(reinterpret_cast<HWND>(lParam), wParam != 0);
            return 0;
        case WM_POWERBROADCAST: {
            if (wParam == PBT_APMRESUMESUSPEND || wParam == PBT_APMRESUMEAUTOMATIC) {
                NotifyCycleSystemResume();
            }
            return TRUE;
        }
        case WM_DESTROY: {
            KillTimer(hwnd, TIMER_COLLAPSE);
            KillTimer(hwnd, TIMER_ANIM_VSYNC);
            PanelDropFadeFrame();
            KillTimer(hwnd, TIMER_FULLSCREEN);
            KillTimer(hwnd, TIMER_HOVER_SENSOR);
            KillTimer(hwnd, TIMER_CYCLE_UI);
            KillTimer(hwnd, TIMER_NAVIGATE_OPEN_CYCLE);
            KillTimer(hwnd, TIMER_LATE_CHILD_POLL);
            KillTimer(hwnd, TIMER_DEBOUNCE_REFRESH);
            KillTimer(hwnd, TIMER_WIDGET_PROXIMITY);
            KillTimer(hwnd, TIMER_OUTSIDE_CLICK);
            SyncOutsideMouseHook(false);
            if (g_hCyclePopup && IsWindow(g_hCyclePopup)) DestroyWindow(g_hCyclePopup);
            DestroyCycleWidgetWindow();
            ListenWatchStop();
            ListenCloseBox();
            for (int id = 1; id <= 3; ++id) UnregisterHotKey(hwnd, id);
            if (g_hTooltip) { DestroyWindow(g_hTooltip); g_hTooltip = nullptr; }
            RemoveTrayIcon();
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// ============================================================================
// Right-click menu for program files (took over from Sordum's Firewall App
// Blocker menu, 1.2.5). Explorer runs
//   "<Windhawk>\windhawk-mod.exe" -windhawk-tool-mod "<id>" -swf-block "<file>"
// Windhawk loads this mod into that normal-rights copy. The object below
// catches the command as the mod loads, before the tool code runs, hands it to
// the running elevated copy and ends that copy at once.
// ============================================================================

constexpr ULONG_PTR kCtxCopyTag = 0x53574631;  // 'SWF1'
constexpr UINT WM_APP_CTX_DONE = WM_APP + 120;
constexpr wchar_t kCtxKey[] = L"Software\\Classes\\exefile\\shell\\SeamlessFirewall";

struct ContextMenuForwarder {
    ContextMenuForwarder() {
        const wchar_t* cmd = GetCommandLineW();
        if (!cmd || !wcsstr(cmd, L"-windhawk-tool-mod \"" WH_MOD_ID L"\"")) return;
        const wchar_t* a = wcsstr(cmd, L" -swf-");
        if (!a) return;
        a += 6;
        wchar_t verb = 0;
        if (!wcsncmp(a, L"block", 5)) {
            verb = L'B';
            a += 5;
        } else if (!wcsncmp(a, L"allow", 5)) {
            verb = L'A';
            a += 5;
        } else if (!wcsncmp(a, L"open", 4)) {
            verb = L'O';
            a += 4;
        }
        if (verb) {
            while (*a == L' ') a++;
            std::wstring path;
            if (*a == L'"') {
                const wchar_t* e = wcschr(a + 1, L'"');
                path.assign(a + 1, e ? e : a + 1 + wcslen(a + 1));
            } else {
                path = a;
            }
            while (!path.empty() && path.back() == L' ') path.pop_back();
            std::wstring msg(1, verb);
            msg += L'|' + std::to_wstring(GetCurrentProcessId()) + L'|' + path;
            if (HWND target = FindWindowExW(HWND_MESSAGE, nullptr, kCtrlWndClass, nullptr)) {
                COPYDATASTRUCT cds{kCtxCopyTag, (DWORD)((msg.size() + 1) * sizeof(wchar_t)), (void*)msg.c_str()};
                DWORD_PTR res = 0;
                SendMessageTimeoutW(target, WM_COPYDATA, 0, (LPARAM)&cds, SMTO_ABORTIFHUNG | SMTO_BLOCK, 5000, &res);
            }
        }
        // This copy only carried the request. It never runs the tool itself.
        TerminateProcess(GetCurrentProcess(), 0);
    }
};
static ContextMenuForwarder g_contextMenuForwarder;

struct CtxJob {
    wchar_t verb = 0;
    std::wstring path;
    Direction dir = Direction::FullyOffline;
    int result = 0;  // rules added or removed; -1 refused
};

static bool ProcessIsSystem() {
    HANDLE tok = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &tok)) return false;
    BYTE buf[256];
    DWORD len = 0;
    bool sys = false;
    if (GetTokenInformation(tok, TokenUser, buf, sizeof(buf), &len))
        sys = IsWellKnownSid(((TOKEN_USER*)buf)->User.Sid, WinLocalSystemSid) != FALSE;
    CloseHandle(tok);
    return sys;
}

static std::wstring CtxForwarderExe() {
    WCHAR self[MAX_PATH];
    DWORD n = GetModuleFileNameW(nullptr, self, ARRAYSIZE(self));
    if (!n || n == ARRAYSIZE(self)) return L"";
    std::wstring dir(self, n);
    size_t slash = dir.find_last_of(L'\\');
    if (slash == std::wstring::npos) return L"";
    std::wstring exe = dir.substr(0, slash) + L"\\windhawk-mod.exe";
    if (GetFileAttributesW(exe.c_str()) != INVALID_FILE_ATTRIBUTES) return exe;
    // Windhawk 1.7 has no windhawk-mod.exe: tool mods run inside windhawk.exe
    // itself, so the menu command goes through that copy instead.
    if (ToLower(dir.substr(slash + 1)) == L"windhawk.exe") return dir;
    return L"";
}

// Writes or removes the menu. Off, or when the mod stops, nothing of it is left.
static void ContextMenuSync(bool on) {
    HKEY root = ProcessIsSystem() ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER;
    HKEY probe = nullptr;
    bool had = RegOpenKeyExW(root, kCtxKey, 0, KEY_READ, &probe) == ERROR_SUCCESS;
    if (probe) RegCloseKey(probe);
    std::wstring exe = on ? CtxForwarderExe() : L"";
    if (on && exe.empty()) {
        Wh_Log(L"Right-click menu: no Windhawk helper found next to this copy, menu left off");
        on = false;
    }
    if (!on) {
        if (had) {
            RegDeleteTreeW(root, kCtxKey);
            SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
            LogAudit(L"Right-click menu removed.");
        }
        return;
    }
    auto setSz = [&](const std::wstring& sub, const wchar_t* name, const std::wstring& val, DWORD type = REG_SZ) {
        RegSetKeyValueW(root, (std::wstring(kCtxKey) + sub).c_str(), name, type, val.c_str(),
                        (DWORD)((val.size() + 1) * sizeof(wchar_t)));
    };
    const std::wstring base = L"\"" + exe + L"\" -windhawk-tool-mod \"" WH_MOD_ID L"\" ";
    setSz(L"", L"MUIVerb", L"Seamless Windows Firewall");
    setSz(L"", L"SubCommands", L"");
    setSz(L"", L"Position", L"Bottom");
    setSz(L"", L"Icon", L"%SystemRoot%\\System32\\FirewallControlPanel.dll,0", REG_EXPAND_SZ);
    setSz(L"\\shell\\1_Block", L"MUIVerb", L"Block in Windows Firewall");
    setSz(L"\\shell\\1_Block", L"Icon", L"%SystemRoot%\\System32\\imageres.dll,-105", REG_EXPAND_SZ);
    setSz(L"\\shell\\1_Block\\command", nullptr, base + L"-swf-block \"%1\"");
    setSz(L"\\shell\\2_Allow", L"MUIVerb", L"Allow again (remove the block)");
    setSz(L"\\shell\\2_Allow", L"Icon", L"%SystemRoot%\\System32\\imageres.dll,-106", REG_EXPAND_SZ);
    setSz(L"\\shell\\2_Allow\\command", nullptr, base + L"-swf-allow \"%1\"");
    setSz(L"\\shell\\3_Open", L"MUIVerb", L"Open the firewall panel");
    setSz(L"\\shell\\3_Open", L"Icon", L"%SystemRoot%\\System32\\FirewallControlPanel.dll,0", REG_EXPAND_SZ);
    DWORD sepBefore = 0x20;  // ECF_SEPARATORBEFORE
    RegSetKeyValueW(root, (std::wstring(kCtxKey) + L"\\shell\\3_Open").c_str(), L"CommandFlags", REG_DWORD, &sepBefore,
                    sizeof(sepBefore));
    setSz(L"\\shell\\3_Open\\command", nullptr, base + L"-swf-open");
    if (!had) {
        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
        LogAudit(L"Right-click menu added.");
    }
}

template <class F>
static void ForEachFwRule(INetFwPolicy2* p, F&& fn) {
    INetFwRules* rules = nullptr;
    if (FAILED(p->get_Rules(&rules)) || !rules) return;
    IUnknown* unk = nullptr;
    IEnumVARIANT* en = nullptr;
    if (SUCCEEDED(rules->get__NewEnum(&unk)) && unk && SUCCEEDED(unk->QueryInterface(IID_PPV_ARGS(&en))) && en) {
        VARIANT var;
        VariantInit(&var);
        ULONG got = 0;
        while (en->Next(1, &var, &got) == S_OK && got == 1) {
            INetFwRule* r = nullptr;
            if (var.vt == VT_DISPATCH && var.pdispVal && SUCCEEDED(var.pdispVal->QueryInterface(IID_PPV_ARGS(&r))) &&
                r) {
                fn(rules, r);
                r->Release();
            }
            VariantClear(&var);
        }
        en->Release();
    }
    if (unk) unk->Release();
    rules->Release();
}

static bool FwRuleIsBlockFor(INetFwRule* r, const std::wstring& low, NET_FW_RULE_DIRECTION* dirOut) {
    NET_FW_ACTION act = NET_FW_ACTION_ALLOW;
    if (FAILED(r->get_Action(&act)) || act != NET_FW_ACTION_BLOCK) return false;
    BSTR app = nullptr;
    r->get_ApplicationName(&app);
    bool match = app && *app && ListenExpandLower(app) == low;
    if (app) SysFreeString(app);
    if (match && dirOut) r->get_Direction(dirOut);
    return match;
}

// A block that stays after a restart: normal Windows Firewall rules, the way
// Firewall App Blocker made them, in our own rule group.
static int ContextMenuBlock(const std::wstring& path, Direction dir) {
    std::wstring low = ToLower(path);
    bool lockCrit = true;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        lockCrit = g_settings.lockSystemProcesses;
    }
    if (IsImmutableProtectedExe(low) || (lockCrit && IsCriticalSystemExe(low))) return -1;
    bool wantOut = dir == Direction::FullyOffline || dir == Direction::CantReachInternet;
    bool wantIn = dir == Direction::FullyOffline || dir == Direction::CantBeReached;
    int added = 0;
    WithFwPolicy([&](INetFwPolicy2* p) {
        bool haveOut = false, haveIn = false;
        ForEachFwRule(p, [&](INetFwRules*, INetFwRule* r) {
            VARIANT_BOOL on = VARIANT_FALSE;
            NET_FW_RULE_DIRECTION d = NET_FW_RULE_DIR_OUT;
            if (FwRuleIsBlockFor(r, low, &d) && SUCCEEDED(r->get_Enabled(&on)) && on == VARIANT_TRUE) {
                (d == NET_FW_RULE_DIR_IN ? haveIn : haveOut) = true;
            }
        });
        INetFwRules* rules = nullptr;
        if (FAILED(p->get_Rules(&rules)) || !rules) return;
        auto add = [&](NET_FW_RULE_DIRECTION d) {
            INetFwRule* r = nullptr;
            if (FAILED(CoCreateInstance(__uuidof(NetFwRule), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&r))) || !r)
                return;
            std::wstring nm = L"Seamless Firewall: " + GetFileNameOnly(path) +
                              (d == NET_FW_RULE_DIR_IN ? L" (in)" : L" (out)");
            BSTR bName = SysAllocString(nm.c_str());
            BSTR bDesc = SysAllocString(L"Blocked from the Seamless Windows Firewall right-click menu.");
            BSTR bApp = SysAllocString(path.c_str());
            BSTR bGrp = SysAllocString(L"Seamless Windows Firewall");
            r->put_Name(bName);
            r->put_Description(bDesc);
            r->put_ApplicationName(bApp);
            r->put_Grouping(bGrp);
            r->put_Protocol(NET_FW_IP_PROTOCOL_ANY);
            r->put_Direction(d);
            r->put_Action(NET_FW_ACTION_BLOCK);
            r->put_Profiles(NET_FW_PROFILE2_ALL);
            r->put_Enabled(VARIANT_TRUE);
            HRESULT hr = rules->Add(r);
            if (SUCCEEDED(hr)) added++;
            else Wh_Log(L"Right-click block: could not add a rule: 0x%08X", (unsigned)hr);
            SysFreeString(bName);
            SysFreeString(bDesc);
            SysFreeString(bApp);
            SysFreeString(bGrp);
            r->Release();
        };
        if (wantOut && !haveOut) add(NET_FW_RULE_DIR_OUT);
        if (wantIn && !haveIn) add(NET_FW_RULE_DIR_IN);
        rules->Release();
    });
    return added;
}

// Removes every block rule for this exact file, whoever made it (the same as
// Firewall App Blocker's Remove). Allow rules stay.
static int ContextMenuAllow(const std::wstring& path) {
    std::wstring low = ToLower(path);
    int removed = 0;
    WithFwPolicy([&](INetFwPolicy2* p) {
        std::vector<std::wstring> doomed;
        ForEachFwRule(p, [&](INetFwRules*, INetFwRule* r) {
            if (!FwRuleIsBlockFor(r, low, nullptr)) return;
            // Rules can share a name, and Remove takes a name, so each one gets a
            // name of its own first.
            GUID g{};
            WCHAR gs[64];
            if (FAILED(CoCreateGuid(&g)) || !StringFromGUID2(g, gs, ARRAYSIZE(gs))) return;
            std::wstring nm = std::wstring(L"SeamlessFirewall_remove_") + gs;
            BSTR b = SysAllocString(nm.c_str());
            if (SUCCEEDED(r->put_Name(b))) doomed.push_back(nm);
            SysFreeString(b);
        });
        INetFwRules* rules = nullptr;
        if (FAILED(p->get_Rules(&rules)) || !rules) return;
        for (const auto& nm : doomed) {
            BSTR b = SysAllocString(nm.c_str());
            if (SUCCEEDED(rules->Remove(b))) removed++;
            SysFreeString(b);
        }
        rules->Release();
    });
    return removed;
}

static DWORD WINAPI ContextMenuWorker(LPVOID param) {
    CtxJob* job = (CtxJob*)param;
    job->result = job->verb == L'B' ? ContextMenuBlock(job->path, job->dir) : ContextMenuAllow(job->path);
    ScanExternalFirewallBlocks(true);
    if (!g_hCtrlWnd || !PostMessageW(g_hCtrlWnd, WM_APP_CTX_DONE, 1, (LPARAM)job)) delete job;
    return 0;
}

static bool CtxSenderIsOurs(DWORD pid) {
    std::wstring want = ToLower(CtxForwarderExe());
    if (want.empty() || !pid) return false;
    HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!h) return false;
    WCHAR img[MAX_PATH];
    DWORD n = ARRAYSIZE(img);
    bool ok = QueryFullProcessImageNameW(h, 0, img, &n) && ToLower(std::wstring(img, n)) == want;
    CloseHandle(h);
    return ok;
}

// A request from the menu: only from Windhawk's own helper, only right after a
// real click or key press, and only while the menu setting is on.
static void ContextMenuRequest(const std::wstring& s) {
    if (s.size() < 3 || s[1] != L'|') return;
    wchar_t verb = s[0];
    size_t bar = s.find(L'|', 2);
    if (bar == std::wstring::npos) return;
    DWORD pid = (DWORD)wcstoul(s.substr(2, bar - 2).c_str(), nullptr, 10);
    std::wstring path = s.substr(bar + 1);
    bool on = false;
    Direction dir = Direction::FullyOffline;
    {
        std::lock_guard<std::mutex> lk(g_settingsMtx);
        on = g_settings.contextMenu;
        dir = g_settings.defaultDirection;
    }
    LASTINPUTINFO li{sizeof(li)};
    bool recent = GetLastInputInfo(&li) && GetTickCount() - li.dwTime < 15000;
    if (!on || !recent || !CtxSenderIsOurs(pid)) {
        LogAudit(L"Right-click request ignored (" + std::wstring(!on ? L"menu off" : !recent ? L"no recent input"
                                                                                        : L"unknown sender") +
                 L"): " + path);
        return;
    }
    if (verb == L'O') {
        PostMessageW(g_hCtrlWnd, WM_APP_CTX_DONE, 3, 0);
        return;
    }
    if (verb != L'B' && verb != L'A') return;
    std::wstring low = ToLower(path);
    if (path.size() < 8 || path[1] != L':' || low.compare(low.size() - 4, 4, L".exe") != 0 ||
        GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES) {
        LogAudit(L"Right-click request ignored (not a program file): " + path);
        return;
    }
    CtxJob* job = new CtxJob{verb, path, dir, 0};
    HANDLE t = CreateThread(nullptr, 0, ContextMenuWorker, job, 0, nullptr);
    if (t) CloseHandle(t);
    else delete job;
}

static void ContextMenuDone(WPARAM kind, LPARAM lParam) {
    if (kind == 3) {
        if (g_hWnd && g_uiState == UiState::Line) TogglePanelFromTray();
        return;
    }
    std::unique_ptr<CtxJob> job((CtxJob*)lParam);
    if (!job) return;
    std::wstring name = GetFileNameOnly(job->path);
    if (job->verb == L'B') {
        if (job->result < 0) {
            g_statusBanner = L"Core OS & security software cannot be blocked.";
            LogAudit(L"Right-click BLOCK refused (protected): " + job->path);
        } else {
            LogAudit(L"Right-click BLOCK " + job->path + L" (" + std::to_wstring(job->result) + L" rules added)");
            TriggerPulse(PulseKind::BlockedRed);
        }
    } else {
        LogAudit(L"Right-click ALLOW " + job->path + L" (" + std::to_wstring(job->result) + L" rules removed)");
        ApplyAllow(job->path);  // Also lifts a block made in the panel; pulses green.
    }
    if (g_uiState == UiState::Panel) RefreshAppList();
    RequestRepaint();
}

static LRESULT CALLBACK ControlWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_COPYDATA) {
        auto* cds = (const COPYDATASTRUCT*)lParam;
        if (!cds || cds->dwData != kCtxCopyTag || !cds->lpData || cds->cbData < 4 * sizeof(wchar_t) ||
            cds->cbData > 8192)
            return FALSE;
        std::wstring s((const wchar_t*)cds->lpData, cds->cbData / sizeof(wchar_t));
        while (!s.empty() && s.back() == 0) s.pop_back();
        ContextMenuRequest(s);
        return TRUE;
    }
    if (msg == WM_APP_CTX_DONE) {
        ContextMenuDone(wParam, lParam);
        return 0;
    }
    if (msg == WM_APP_RELOAD_SETTINGS) {
        LoadSettings();
        if (!g_settings.enableCycleScheduler) StopAllCycles(true);
        if (!g_settings.rememberCycleTemplates) {
            {
                std::lock_guard<std::mutex> lk(g_cycleMtx);
                g_cycleTemplates.clear();
            }
            SaveCycleTemplates();
        }
        SyncAutoBlockedApps();
        ContextMenuSync(g_settings.contextMenu);
        if (g_hWnd) {
            ListenSync();
            ApplyCaptureExclusionAll();
            RegisterAllHotkeys(g_hWnd);
            AddTrayIcon(g_hWnd);
            SyncHoverSensorTimer(g_hWnd);
            UpdateWindowGeometry(true);
            RequestRepaint();
        }
        if (HWND s = swfset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD event, HWND hwnd, LONG idObject, LONG, DWORD, DWORD) {
    if (!g_hWnd || !hwnd || hwnd == g_hWnd) return;
    if (event == EVENT_SYSTEM_FOREGROUND || event == EVENT_SYSTEM_SWITCHEND || event == EVENT_SYSTEM_MINIMIZEEND) {
        PostMessageW(g_hWnd, WM_APP_FOREGROUND_CHG, 0, 0);
    } else if (event == EVENT_OBJECT_DESTROY && idObject == OBJID_WINDOW) {
        g_evFgDirty = g_evAppsDirty = true;
    } else if (event == EVENT_OBJECT_CREATE && idObject == OBJID_WINDOW) {
        g_evAppsDirty = true;
    } else {
        return;
    }
    if (!g_evFlushArmed) {
        g_evFlushArmed = true;
        SetTimer(g_hWnd, TIMER_EVENT_FLUSH, 60, nullptr);
    }
}

// ============================================================================
// UI Thread & Windhawk Tool Mod Lifecycle
// ============================================================================

static DWORD WINAPI UiThreadProc(LPVOID) {
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    Gdiplus::GdiplusStartupInput gpsi;
    Gdiplus::GdiplusStartup(&g_gdiplusToken, &gpsi, nullptr);
    g_expandClock.Init();
    g_scrollClock.Init();

    WNDCLASSEXW wc{sizeof(wc)};
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = FloatingWndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kWndClass;
    RegisterClassExW(&wc);

    WNDCLASSEXW cwc{sizeof(cwc)};
    cwc.lpfnWndProc = ControlWndProc;
    cwc.hInstance = GetModuleHandleW(nullptr);
    cwc.lpszClassName = kCtrlWndClass;
    RegisterClassExW(&cwc);

    g_hCtrlWnd = CreateWindowExW(0, kCtrlWndClass, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, cwc.hInstance, nullptr);
    // The right-click menu's helper runs with normal rights; let its hand-off through.
    if (g_hCtrlWnd) ChangeWindowMessageFilterEx(g_hCtrlWnd, WM_COPYDATA, MSGFLT_ALLOW, nullptr);

    RECT initRc{};
    ComputeTargetRect(0.0, initRc);
    g_hWnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        kWndClass, L"Seamless Windows Firewall", WS_POPUP,
        initRc.left, initRc.top, initRc.right - initRc.left, initRc.bottom - initRc.top,
        nullptr, nullptr, wc.hInstance, nullptr);

    if (g_hWnd) {
        UpdateWindowGeometry(true);
        UpdateWindow(g_hWnd);
        PostMessageW(g_hWnd, WM_APP_FOREGROUND_CHG, 0, 0);
    }

    g_hookFg = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_MINIMIZEEND, nullptr,
                               WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    g_hookCreate = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_DESTROY, nullptr,
                                   WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

    if (g_uiReadyEvent) SetEvent(g_uiReadyEvent);

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (g_hookFg) { UnhookWinEvent(g_hookFg); g_hookFg = nullptr; }
    if (g_hookCreate) { UnhookWinEvent(g_hookCreate); g_hookCreate = nullptr; }

    if (g_hCtrlWnd) { DestroyWindow(g_hCtrlWnd); g_hCtrlWnd = nullptr; }
    ClearIconCache();
    UnregisterClassW(kWndClass, wc.hInstance);
    UnregisterClassW(kCtrlWndClass, cwc.hInstance);

    if (g_dwriteEmojiFormat) { g_dwriteEmojiFormat->Release(); g_dwriteEmojiFormat = nullptr; }
    if (g_d2dFallbackBrush) { g_d2dFallbackBrush->Release(); g_d2dFallbackBrush = nullptr; }
    if (g_d2dDcRt) { g_d2dDcRt->Release(); g_d2dDcRt = nullptr; }
    if (g_dwriteFactory) { g_dwriteFactory->Release(); g_dwriteFactory = nullptr; }
    if (g_d2dFactory) { g_d2dFactory->Release(); g_d2dFactory = nullptr; }
    if (g_gdiplusToken) { Gdiplus::GdiplusShutdown(g_gdiplusToken); g_gdiplusToken = 0; }
    CoUninitialize();
    return 0;
}

// ---------------------------------------------------------------------------------------------
// Menu room: shared by Seamless Flyouts and the tool mods' menu look.
// - Every popup menu window in this process is caught as it is created, title bar (system)
//   menus included, which never pass through TrackPopupMenu.
// - Menus that Windows draws get 2 px more frame on every side, so the hover has the same room
//   from the border as in Explorer's own desktop menu (4 px at the sides, 6 px top and bottom).
//   Menus with owner-drawn rows (Explorer) already have it and are left alone.
// - A submenu opens touching its parent, and while the pointer heads for an open submenu the
//   parent ignores it, so rows crossed on the way don't swap the submenu (released after a
//   short rest, so stopping on a row still opens that row).
// - A menu too tall for its monitor gets shorter rows while it is open, so the last item
//   shows without scroll arrows. Windows reads row spacing once per process, so the spacing is
//   reloaded (FlushMenuThemes) when such a menu opens and again when the menu closes.
// ---------------------------------------------------------------------------------------------
#include <algorithm>
#include <atomic>
#include <mutex>
#include <vector>
#include <commctrl.h>

namespace SeamlessMenuRoom {

constexpr UINT_PTR kRoomId = 0x6D55;
constexpr INT kRowMargin = 6;                  // row top and bottom margin of the menu look
constexpr INT kMinRowMargin = 2;
static const WCHAR* const kPadProp = L"SeamlessMenuRoomPad";
static const WCHAR* const kSizeProp = L"SeamlessMenuRoomSize";
static const WCHAR* const kSeqProp = L"SeamlessMenuRoomSeq";   // creation order of menu windows
constexpr UINT kAimHoldMs = 250;               // how long the pointer may rest before a held move counts

static std::atomic<INT> g_rowMargin{kRowMargin};
static HWINEVENTHOOK g_createHook = nullptr, g_menuHook = nullptr;
static VOID (*g_onCreate)(HWND) = nullptr;
using Flush_t = VOID(WINAPI*)();
static Flush_t g_flush = nullptr;
static thread_local HHOOK t_loopHook = nullptr;
static thread_local INT t_trackDepth = 0;
static thread_local BOOL t_menuMode = FALSE;
static std::atomic<ULONG> g_seq{0};
static thread_local HHOOK t_aimHook = nullptr;
static thread_local POINT t_apex = {LONG_MIN, LONG_MIN};
static thread_local MSG t_held = {};
static thread_local UINT_PTR t_aimTimer = 0;
static thread_local DWORD t_holdStart = 0;
constexpr DWORD kAimMaxMs = 700;               // a hold never lasts longer than this

// Row top and bottom margin to report for Menu part 27 / POPUPITEM, property 10000.
static INT RowMargin() { return g_rowMargin.load(); }

static UINT DpiOf(HWND h)
{
    UINT d = h ? GetDpiForWindow(h) : 0;
    if (!d) d = GetDpiForSystem();
    return d ? d : USER_DEFAULT_SCREEN_DPI;
}

static BOOL IsPopupMenuWindow(HWND h)
{
    WCHAR cls[16];
    return h && GetClassNameW(h, cls, ARRAYSIZE(cls)) && wcscmp(cls, L"#32768") == 0;
}

static BOOL HasOwnerDraw(HMENU m)
{
    INT n = GetMenuItemCount(m);
    for (INT i = 0; i < n; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (GetMenuItemInfoW(m, i, TRUE, &mii) && (mii.fType & MFT_OWNERDRAW)) return TRUE;
    }
    return FALSE;
}

// The nearest visible menu window of this thread made before (parent) or after (child) h.
struct RelativeFind { HWND self; ULONG_PTR seq; BOOL child; HWND best; ULONG_PTR bestSeq; };
static BOOL CALLBACK FindRelative(HWND h, LPARAM l)
{
    auto* f = reinterpret_cast<RelativeFind*>(l);
    if (h == f->self || !IsWindowVisible(h) || !IsPopupMenuWindow(h)) return TRUE;
    ULONG_PTR s = (ULONG_PTR)GetPropW(h, kSeqProp);
    if (!s) return TRUE;
    BOOL better = f->child ? (s > f->seq && (!f->best || s < f->bestSeq))
                           : (s < f->seq && (!f->best || s > f->bestSeq));
    if (better) { f->best = h; f->bestSeq = s; }
    return TRUE;
}
static HWND RelativeMenu(HWND h, BOOL child)
{
    RelativeFind f = {h, (ULONG_PTR)GetPropW(h, kSeqProp), child, nullptr, 0};
    if (!f.seq) return nullptr;
    EnumThreadWindows(GetCurrentThreadId(), FindRelative, reinterpret_cast<LPARAM>(&f));
    return f.best;
}

// Pull a submenu in so it touches its parent (never pushes it further away or off screen).
static VOID SnapToParent(HWND h, WINDOWPOS* wp)
{
    HWND parent = RelativeMenu(h, FALSE);
    RECT pr;
    if (!parent || !GetWindowRect(parent, &pr)) return;
    INT cx = wp->cx;
    if ((wp->flags & SWP_NOSIZE) || cx <= 0) {
        RECT r;
        if (!GetWindowRect(h, &r)) return;
        cx = r.right - r.left;
    }
    LONG mid = (pr.left + pr.right) / 2;
    if (wp->x >= mid) {
        if (pr.right < wp->x) wp->x = pr.right;
    } else if (wp->x + cx <= mid) {
        if (pr.left - cx > wp->x) wp->x = pr.left - cx;
    }
}

static BOOL InTriangle(POINT p, POINT a, POINT b, POINT c)
{
    auto side = [](POINT o, POINT u, POINT v) {
        return (LONGLONG)(u.x - o.x) * (v.y - o.y) - (LONGLONG)(u.y - o.y) * (v.x - o.x);
    };
    LONGLONG d1 = side(p, a, b), d2 = side(p, b, c), d3 = side(p, c, a);
    BOOL neg = d1 < 0 || d2 < 0 || d3 < 0, pos = d1 > 0 || d2 > 0 || d3 > 0;
    return !(neg && pos);
}

static VOID DropHeld()
{
    if (t_aimTimer) KillTimer(nullptr, t_aimTimer);
    t_aimTimer = 0;
    t_held = {};
}

// The pointer rested: let the last held move through, from where it stopped. The timer has no
// callback (a pending one could outlive the mod's unload); AimProc sees its WM_TIMER.
static VOID AimRelease()
{
    MSG m = t_held;
    DropHeld();
    if (m.hwnd && IsWindow(m.hwnd)) {
        t_apex = m.pt;
        PostMessageW(m.hwnd, m.message, m.wParam, m.lParam);
    }
}

// TRUE: hold this move, the pointer is on its way to the open submenu.
static BOOL HoldForSubmenu(const MSG* m)
{
    POINT p = m->pt;
    HWND under = WindowFromPoint(p);
    HWND sub = nullptr;
    if (under && IsPopupMenuWindow(under) && GetWindowThreadProcessId(under, nullptr) == GetCurrentThreadId())
        sub = RelativeMenu(under, TRUE);
    RECT sr, pr;
    if (!sub || !GetWindowRect(sub, &sr) || !GetWindowRect(under, &pr) || t_apex.x == LONG_MIN ||
        (p.x == t_apex.x && p.y == t_apex.y)) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    LONG edge = sr.left >= (pr.left + pr.right) / 2 ? sr.left : sr.right;
    INT slack = MulDiv(6, DpiOf(under), USER_DEFAULT_SCREEN_DPI);
    POINT b = {edge, sr.top - slack}, c = {edge, sr.bottom + slack};
    if (!InTriangle(p, t_apex, b, c)) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    if (!t_held.hwnd) t_holdStart = GetTickCount();
    else if (GetTickCount() - t_holdStart > kAimMaxMs) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    t_held = *m;
    if (t_aimTimer) KillTimer(nullptr, t_aimTimer);
    t_aimTimer = SetTimer(nullptr, 0, kAimHoldMs, nullptr);
    if (!t_aimTimer) { t_held = {}; t_apex = p; return FALSE; }
    return TRUE;
}

static LRESULT CALLBACK AimProc(INT code, WPARAM w, LPARAM l)
{
    if (code == MSGF_MENU && l) {
        auto* m = reinterpret_cast<MSG*>(l);
        if (m->message == WM_TIMER && !m->hwnd && t_aimTimer && m->wParam == t_aimTimer) {
            AimRelease();
            return TRUE;
        }
        if (m->message == WM_MOUSEMOVE || m->message == WM_NCMOUSEMOVE) {
            if (HoldForSubmenu(m)) return TRUE;
        } else if ((m->message >= WM_LBUTTONDOWN && m->message <= WM_MBUTTONDBLCLK) ||
                   (m->message >= WM_NCLBUTTONDOWN && m->message <= WM_NCMBUTTONDBLCLK) ||
                   m->message == WM_KEYDOWN) {
            DropHeld();
            t_apex = {LONG_MIN, LONG_MIN};
        }
    }
    return CallNextHookEx(nullptr, code, w, l);
}

static LRESULT CALLBACK RoomProc(HWND h, UINT msg, WPARAM w, LPARAM l, UINT_PTR, DWORD_PTR)
{
    if (msg == WM_WINDOWPOSCHANGING && l) {
        auto* wp = reinterpret_cast<WINDOWPOS*>(l);
        // Grow only the size Windows asks for, never a size this proc already produced.
        if (!(wp->flags & SWP_NOSIZE) && wp->cx > 0 && wp->cy > 0 &&
            (DWORD)MAKELONG(wp->cx, wp->cy) != (DWORD)(ULONG_PTR)GetPropW(h, kSizeProp)) {
            HMENU m = (HMENU)SendMessageW(h, MN_GETHMENU, 0, 0);
            INT pad = (m && !HasOwnerDraw(m)) ? MulDiv(2, DpiOf(h), USER_DEFAULT_SCREEN_DPI) : 0;
            SetPropW(h, kPadProp, (HANDLE)(INT_PTR)pad);
            if (pad) {
                wp->cx += 2 * pad;
                wp->cy += 2 * pad;
                if (!(wp->flags & SWP_NOMOVE)) {
                    RECT r = {wp->x, wp->y, wp->x + wp->cx, wp->y + wp->cy};
                    MONITORINFO mi = {sizeof(mi)};
                    if (GetMonitorInfoW(MonitorFromRect(&r, MONITOR_DEFAULTTONEAREST), &mi)) {
                        if (r.right > mi.rcMonitor.right) wp->x = std::max(mi.rcMonitor.left, wp->x - (r.right - mi.rcMonitor.right));
                        if (r.bottom > mi.rcMonitor.bottom) wp->y = std::max(mi.rcMonitor.top, wp->y - (r.bottom - mi.rcMonitor.bottom));
                    }
                }
            }
            SetPropW(h, kSizeProp, (HANDLE)(ULONG_PTR)(DWORD)MAKELONG(wp->cx, wp->cy));
        }
        if (!(wp->flags & SWP_NOMOVE)) SnapToParent(h, wp);
    }
    if (msg == WM_NCDESTROY) {
        RemovePropW(h, kPadProp);
        RemovePropW(h, kSizeProp);
        RemovePropW(h, kSeqProp);
        RemoveWindowSubclass(h, RoomProc, kRoomId);
        return DefSubclassProc(h, msg, w, l);
    }
    LRESULT result = DefSubclassProc(h, msg, w, l);
    if (msg == WM_NCCALCSIZE && l) {
        INT pad = (INT)(INT_PTR)GetPropW(h, kPadProp);
        if (pad > 0) InflateRect(reinterpret_cast<RECT*>(l), -pad, -pad);
    }
    return result;
}

static VOID ResetRows()
{
    if (g_rowMargin.exchange(kRowMargin) != kRowMargin && g_flush) g_flush();
}

// Picks the largest row margin (6 down to 2) at which the whole menu fits its monitor.
static VOID FitMenu(HMENU m, HWND owner)
{
    if (!m || !g_flush || HasOwnerDraw(m)) return;
    INT rows = 0, seps = 0, n = GetMenuItemCount(m);
    for (INT i = 0; i < n; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (!GetMenuItemInfoW(m, i, TRUE, &mii)) continue;
        (mii.fType & MFT_SEPARATOR) ? seps++ : rows++;
    }
    MONITORINFO mi = {sizeof(mi)};
    if (!rows || !GetMonitorInfoW(MonitorFromWindow(owner, MONITOR_DEFAULTTONEAREST), &mi)) return;
    UINT dpi = DpiOf(owner);
    auto px = [dpi](INT v) { return MulDiv(v, dpi, USER_DEFAULT_SCREEN_DPI); };
    INT avail = mi.rcWork.bottom - mi.rcWork.top - px(8);
    INT pick = kRowMargin;
    for (; pick > kMinRowMargin; pick--) {
        INT cut = px(2 * (kRowMargin - pick));   // rows measure 29 px and separators 17 px at margin 6
        if (rows * (px(29) - cut) + seps * (px(17) - cut) + px(10) <= avail) break;
    }
    if (pick < g_rowMargin.load()) {
        g_rowMargin = pick;
        g_flush();
    }
}

static LRESULT CALLBACK LoopProc(INT code, WPARAM w, LPARAM l)
{
    if (code == HC_ACTION && l) {
        auto* c = reinterpret_cast<CWPSTRUCT*>(l);
        if (c->message == WM_INITMENUPOPUP) FitMenu((HMENU)c->wParam, c->hwnd);
        else if (c->message == WM_EXITMENULOOP) ResetRows();
    }
    return CallNextHookEx(nullptr, code, w, l);
}
// Every live loop hook, so Uninit can remove the ones other threads still hold.
static std::mutex g_hooksLock;
static std::vector<HHOOK> g_hooks;
static VOID SyncLoopHook()
{
    BOOL want = t_trackDepth > 0 || t_menuMode;
    if (want && !t_loopHook) {
        t_loopHook = SetWindowsHookExW(WH_CALLWNDPROC, LoopProc, nullptr, GetCurrentThreadId());
        if (t_loopHook) { std::lock_guard<std::mutex> g(g_hooksLock); g_hooks.push_back(t_loopHook); }
    } else if (!want && t_loopHook) {
        {
            std::lock_guard<std::mutex> g(g_hooksLock);
            auto it = std::find(g_hooks.begin(), g_hooks.end(), t_loopHook);
            if (it != g_hooks.end()) { g_hooks.erase(it); UnhookWindowsHookEx(t_loopHook); }
        }
        t_loopHook = nullptr;
        ResetRows();
    }
    if (want && !t_aimHook) {
        t_apex = {LONG_MIN, LONG_MIN};
        t_aimHook = SetWindowsHookExW(WH_MSGFILTER, AimProc, nullptr, GetCurrentThreadId());
        if (t_aimHook) { std::lock_guard<std::mutex> g(g_hooksLock); g_hooks.push_back(t_aimHook); }
    } else if (!want && t_aimHook) {
        {
            std::lock_guard<std::mutex> g(g_hooksLock);
            auto it = std::find(g_hooks.begin(), g_hooks.end(), t_aimHook);
            if (it != g_hooks.end()) { g_hooks.erase(it); UnhookWindowsHookEx(t_aimHook); }
        }
        t_aimHook = nullptr;
        DropHeld();
    }
}

// Wrap TrackPopupMenu(Ex) with these (menu-bar menus are covered by the menu events).
static VOID BeginTrack() { t_trackDepth++; SyncLoopHook(); }
static VOID EndTrack() { if (t_trackDepth > 0) t_trackDepth--; SyncLoopHook(); }

static VOID CALLBACK OnEvent(HWINEVENTHOOK, DWORD ev, HWND h, LONG obj, LONG child, DWORD, DWORD)
{
    if (ev == EVENT_OBJECT_CREATE) {
        if (obj != OBJID_WINDOW || child != CHILDID_SELF || !IsPopupMenuWindow(h) ||
            GetWindowThreadProcessId(h, nullptr) != GetCurrentThreadId())
            return;
        SetPropW(h, kSeqProp, (HANDLE)(ULONG_PTR)++g_seq);
        if (g_onCreate) g_onCreate(h);
        SetWindowSubclass(h, RoomProc, kRoomId, 0);
    } else if (ev == EVENT_SYSTEM_MENUSTART) {
        t_menuMode = TRUE;
        SyncLoopHook();
    } else if (ev == EVENT_SYSTEM_MENUEND) {
        t_menuMode = FALSE;
        SyncLoopHook();
    }
}

// onCreate (optional) runs for each new popup menu window, on its own thread, after creation.
static VOID Init(VOID (*onCreate)(HWND))
{
    g_onCreate = onCreate;
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    g_flush = ux ? (Flush_t)GetProcAddress(ux, MAKEINTRESOURCEA(136)) : nullptr;
    HMODULE self = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCWSTR>(&OnEvent), &self);
    DWORD pid = GetCurrentProcessId();
    g_createHook = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_CREATE, self, OnEvent, pid, 0, WINEVENT_INCONTEXT);
    g_menuHook = SetWinEventHook(EVENT_SYSTEM_MENUSTART, EVENT_SYSTEM_MENUEND, self, OnEvent, pid, 0, WINEVENT_INCONTEXT);
}

static VOID Uninit()
{
    for (HWINEVENTHOOK* hk : {&g_createHook, &g_menuHook})
        if (*hk) { UnhookWinEvent(*hk); *hk = nullptr; }
    {
        std::lock_guard<std::mutex> g(g_hooksLock);
        for (HHOOK hk : g_hooks) UnhookWindowsHookEx(hk);
        g_hooks.clear();
    }
    ResetRows();
}

}  // namespace SeamlessMenuRoom
// ---------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------
// Seamless menu look for this mod's own menus.
// Windhawk runs tool mods in their own process, where Seamless Flyouts cannot reach, so the
// menus this mod shows get the same look here: blurred Catppuccin Mocha body, rounded corners,
// roomy rows, separators that run to the border, the blue to mauve hover pill, and
// submenus that open beside their parent with a small gap. Only this process is touched.
// ---------------------------------------------------------------------------------------------
#include <d2d1.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <commctrl.h>

// ---------------------------------------------------------------------------------------------
// Menu pill: the one hover look for every menu row, the same pill Seamless Clipboard Manager
// draws: a soft blue to mauve fill (16 %) and a 1 px blue to mauve ring (80 %), radius 8.
// Drawn at the row's real size each time, because a stretched nine-grid can't hold a gradient.
// ---------------------------------------------------------------------------------------------
namespace SeamlessMenuPill {

static BOOL Draw(ID2D1Factory* factory, HDC hdc, const RECT& r, UINT dpi)
{
    INT w = r.right - r.left, h = r.bottom - r.top;
    if (!factory || !hdc || w <= 2 || h <= 2) return FALSE;
    HDC dc = CreateCompatibleDC(hdc);
    if (!dc) return FALSE;
    BITMAPINFO bmi = {};
    bmi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB};
    VOID* bits = nullptr;
    HBITMAP bmp = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!bmp) { DeleteDC(dc); return FALSE; }
    HGDIOBJ old = SelectObject(dc, bmp);
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_SOFTWARE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0,
        D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE, D2D1_FEATURE_LEVEL_DEFAULT);
    ID2D1DCRenderTarget* rt = nullptr;
    RECT rc = {0, 0, w, h};
    BOOL ok = FALSE;
    if (SUCCEEDED(factory->CreateDCRenderTarget(&props, &rt)) && SUCCEEDED(rt->BindDC(dc, &rc))) {
        FLOAT s = (dpi ? dpi : USER_DEFAULT_SCREEN_DPI) / (FLOAT)USER_DEFAULT_SCREEN_DPI;
        FLOAT ringW = s < 1.5f ? 1.f : 2.f;
        FLOAT rad = std::min(8.f * s, std::min((FLOAT)w, (FLOAT)h) / 2.f);
        D2D1_ROUNDED_RECT rr = {{ringW / 2, ringW / 2, w - ringW / 2, h - ringW / 2}, rad, rad};
        auto gradient = [&](FLOAT a) {
            ID2D1LinearGradientBrush* brush = nullptr;
            ID2D1GradientStopCollection* stops = nullptr;
            D2D1_GRADIENT_STOP st[2] = {{0.f, {137 / 255.f, 180 / 255.f, 250 / 255.f, a}},
                                        {1.f, {203 / 255.f, 166 / 255.f, 247 / 255.f, a}}};
            if (SUCCEEDED(rt->CreateGradientStopCollection(st, 2, &stops)))
                rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties({0, 0}, {(FLOAT)w, (FLOAT)h}),
                                              stops, &brush);
            if (stops) stops->Release();
            return brush;
        };
        rt->BeginDraw();
        rt->Clear({0, 0, 0, 0});
        ID2D1LinearGradientBrush* fill = gradient(0.16f);
        ID2D1LinearGradientBrush* ring = gradient(0.8f);
        if (fill) rt->FillRoundedRectangle(&rr, fill);
        if (ring) rt->DrawRoundedRectangle(&rr, ring, ringW);
        ok = SUCCEEDED(rt->EndDraw()) && fill && ring;
        if (fill) fill->Release();
        if (ring) ring->Release();
    }
    if (rt) rt->Release();
    if (ok) {
        BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        ok = GdiAlphaBlend(hdc, r.left, r.top, w, h, dc, 0, 0, w, h, bf);
    }
    SelectObject(dc, old);
    DeleteObject(bmp);
    DeleteDC(dc);
    return ok;
}

}  // namespace SeamlessMenuPill

namespace SeamlessMenuSkin {

constexpr COLORREF kMenuTint = 0xA01B1111;        // Seamless Flyouts "MenuBlur" A011111B
constexpr UINT_PTR kSubclassId = 0x6D54;
constexpr UINT kAccentAcrylic = 4, kWcaAccentPolicy = 19;

struct AccentPolicy { DWORD state, flags, color, animation; };
struct CompositionData { DWORD attrib; PVOID data; SIZE_T size; };
using SetWca_t = BOOL(WINAPI*)(HWND, CompositionData*);
using GetThemeClass_t = HRESULT(WINAPI*)(HTHEME, LPWSTR, INT);

static ID2D1Factory* g_factory = nullptr;
static HDC g_hoverDC = nullptr, g_sepDC = nullptr;
static UINT g_edgesMsg = 0;

static decltype(&DrawThemeBackground) DrawThemeBackground_orig = nullptr;
static decltype(&DrawThemeBackgroundEx) DrawThemeBackgroundEx_orig = nullptr;
static decltype(&GetThemeColor) GetThemeColor_orig = nullptr;
static decltype(&GetThemeMargins) GetThemeMargins_orig = nullptr;
static decltype(&GetThemeFont) GetThemeFont_orig = nullptr;
static decltype(&DwmSetWindowAttribute) DwmSetWindowAttribute_orig = nullptr;
static decltype(&TrackPopupMenu) TrackPopupMenu_orig = nullptr;
static decltype(&TrackPopupMenuEx) TrackPopupMenuEx_orig = nullptr;

static UINT Dpi() { UINT d = GetDpiForSystem(); return d ? d : USER_DEFAULT_SCREEN_DPI; }

static BOOL IsMenuWindow(HWND hWnd)
{
    WCHAR cls[16];
    return hWnd && GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) && wcscmp(cls, L"#32768") == 0;
}

static BOOL IsMenuTheme(HTHEME hTheme)
{
    static auto getClass = (GetThemeClass_t)GetProcAddress(GetModuleHandleW(L"uxtheme.dll"), MAKEINTRESOURCEA(74));
    WCHAR buf[64] = {};
    return getClass && SUCCEEDED(getClass(hTheme, buf, ARRAYSIZE(buf))) && wcscmp(buf, L"Menu") == 0;
}

static D2D1_COLOR_F Argb(BYTE a, BYTE r, BYTE g, BYTE b) { return {r / 255.f, g / 255.f, b / 255.f, a / 255.f}; }

// A small premultiplied 32-bit bitmap drawn once with Direct2D and stretched as a nine-grid.
static HDC MakeCache(INT w, INT h, BOOL separator)
{
    if (!g_factory) return nullptr;
    HDC dc = CreateCompatibleDC(nullptr);
    if (!dc) return nullptr;
    BITMAPINFO bmi = {};
    bmi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB};
    VOID* bits = nullptr;
    HBITMAP bmp = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!bmp) { DeleteDC(dc); return nullptr; }
    SelectObject(dc, bmp);
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_SOFTWARE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0,
        D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE, D2D1_FEATURE_LEVEL_DEFAULT);
    ID2D1DCRenderTarget* rt = nullptr;
    RECT rc = {0, 0, w, h};
    if (FAILED(g_factory->CreateDCRenderTarget(&props, &rt)) || FAILED(rt->BindDC(dc, &rc))) {
        if (rt) rt->Release();
        DeleteDC(dc); DeleteObject(bmp);
        return nullptr;
    }
    ID2D1SolidColorBrush *a = nullptr, *b = nullptr;
    rt->BeginDraw();
    if (separator) {
        rt->CreateSolidColorBrush(Argb(255, 69, 71, 90), &a);
        if (a) rt->DrawLine({0, h / 2.f}, {(FLOAT)w, h / 2.f}, a);
    } else {
        auto r = D2D1::RoundedRect(D2D1::RectF(0.5f, 0.5f, w - 0.5f, h - 0.5f), 6.f, 6.f);
        rt->CreateSolidColorBrush(Argb(190, 69, 71, 90), &a);
        rt->CreateSolidColorBrush(Argb(255, 137, 180, 250), &b);
        if (a) rt->FillRoundedRectangle(&r, a);
        if (b) rt->DrawRoundedRectangle(&r, b, 1.f);
    }
    HRESULT hr = rt->EndDraw();
    if (a) a->Release();
    if (b) b->Release();
    rt->Release();
    if (FAILED(hr)) { DeleteDC(dc); DeleteObject(bmp); return nullptr; }
    return dc;
}

static VOID Blend(HDC dst, INT x, INT y, INT w, INT h, HDC src, INT sx, INT sy, INT sw, INT sh)
{
    if (w <= 0 || h <= 0 || sw <= 0 || sh <= 0) return;
    BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    GdiAlphaBlend(dst, x, y, w, h, src, sx, sy, sw, sh, bf);
}

static VOID NineGrid(HDC hdc, HDC src, const RECT* d, INT l, INT t, INT r, INT b)
{
    BITMAP bm = {};
    GetObject(GetCurrentObject(src, OBJ_BITMAP), sizeof(bm), &bm);
    INT sw = bm.bmWidth, sh = bm.bmHeight, dw = d->right - d->left, dh = d->bottom - d->top;
    l = std::min(l, dw); r = std::min(r, dw - l); t = std::min(t, dh); b = std::min(b, dh - t);
    if (l + r >= sw || t + b >= sh) { Blend(hdc, d->left, d->top, dw, dh, src, 0, 0, sw, sh); return; }
    INT cw = dw - l - r, ch = dh - t - b, scw = sw - l - r, sch = sh - t - b;
    Blend(hdc, d->left + l, d->top + t, cw, ch, src, l, t, scw, sch);
    Blend(hdc, d->left, d->top, l, t, src, 0, 0, l, t);
    Blend(hdc, d->left + l, d->top, cw, t, src, l, 0, scw, t);
    Blend(hdc, d->right - r, d->top, r, t, src, sw - r, 0, r, t);
    Blend(hdc, d->left, d->top + t, l, ch, src, 0, t, l, sch);
    Blend(hdc, d->right - r, d->top + t, r, ch, src, sw - r, t, r, sch);
    Blend(hdc, d->left, d->bottom - b, l, b, src, 0, sh - b, l, b);
    Blend(hdc, d->left + l, d->bottom - b, cw, b, src, l, sh - b, scw, b);
    Blend(hdc, d->right - r, d->bottom - b, r, b, src, sw - r, sh - b, r, b);
}

static VOID ApplyEffects(HWND hWnd)
{
    static auto setWca = (SetWca_t)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
    DWM_BLURBEHIND bb = {DWM_BB_ENABLE | DWM_BB_BLURREGION | DWM_BB_TRANSITIONONMAXIMIZED, TRUE, CreateRectRgn(0, 0, -1, -1), TRUE};
    DwmEnableBlurBehindWindow(hWnd, &bb);
    DeleteObject(bb.hRgnBlur);
    AccentPolicy ap = {kAccentAcrylic, 0, kMenuTint, 0};
    CompositionData data = {kWcaAccentPolicy, &ap, sizeof(ap)};
    if (setWca) setWca(hWnd, &data);
    UINT corner = DWMWCP_ROUND;
    DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
}

// Separator lines stop at the client edge; copy each one across the thin menu frame so it
// meets the border.
static BOOL IsSeparatorPixel(COLORREF c)
{
    return abs(GetRValue(c) - 69) <= 8 && abs(GetGValue(c) - 71) <= 8 && abs(GetBValue(c) - 90) <= 8;
}
static VOID PaintSeparatorEdges(HWND hWnd)
{
    if (!g_sepDC || !IsWindowVisible(hWnd)) return;
    HMENU hMenu = (HMENU)SendMessageW(hWnd, MN_GETHMENU, 0, 0);
    if (!hMenu) return;
    RECT wr, cr;
    GetWindowRect(hWnd, &wr);
    GetClientRect(hWnd, &cr);
    POINT org = {0, 0};
    ClientToScreen(hWnd, &org);
    INT cl = org.x - wr.left, cw = cr.right, winW = wr.right - wr.left;
    if (cl <= 0 || cw <= 0) return;
    HDC wdc = GetWindowDC(hWnd);
    if (!wdc) return;
    INT count = GetMenuItemCount(hMenu);
    for (INT i = 0; i < count; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (!GetMenuItemInfoW(hMenu, i, TRUE, &mii) || !(mii.fType & MFT_SEPARATOR)) continue;
        RECT ir;
        if (!GetMenuItemRect(hWnd, hMenu, i, &ir)) continue;
        for (INT y = ir.top - wr.top; y < ir.bottom - wr.top; y++) {
            if (!IsSeparatorPixel(GetPixel(wdc, cl, y)) || !IsSeparatorPixel(GetPixel(wdc, cl + cw - 1, y))) continue;
            RECT left = {0, y - 2, cl, y + 3}, right = {cl + cw, y - 2, winW, y + 3};
            NineGrid(wdc, g_sepDC, &left, 0, 5, 0, 0);
            NineGrid(wdc, g_sepDC, &right, 0, 5, 0, 0);
        }
    }
    ReleaseDC(hWnd, wdc);
}

struct ParentSearch { HWND self; RECT r; HWND parent; RECT pr; BOOL right; };
static BOOL CALLBACK FindParent(HWND hWnd, LPARAM lParam)
{
    auto* f = reinterpret_cast<ParentSearch*>(lParam);
    if (hWnd == f->self || !IsWindowVisible(hWnd) || !IsMenuWindow(hWnd)) return TRUE;
    RECT p;
    GetWindowRect(hWnd, &p);
    if (f->r.top >= p.bottom || f->r.bottom <= p.top) return TRUE;
    BOOL right = f->r.left > p.left && f->r.left < p.right + 2 && f->r.right > p.right;
    BOOL left = f->r.right < p.right && f->r.right > p.left - 2 && f->r.left < p.left;
    if (!right && !left) return TRUE;
    f->parent = hWnd; f->pr = p; f->right = right;
    return FALSE;
}
// Submenus open over the parent's edge; move them beside it with an 8 px gap.
static VOID PlaceSubmenu(HWND hWnd, WINDOWPOS* wp)
{
    RECT cur;
    GetWindowRect(hWnd, &cur);
    INT w = (wp->flags & SWP_NOSIZE) ? cur.right - cur.left : wp->cx;
    INT h = (wp->flags & SWP_NOSIZE) ? cur.bottom - cur.top : wp->cy;
    if (w <= 0 || h <= 0) return;
    ParentSearch f = {hWnd, {wp->x, wp->y, wp->x + w, wp->y + h}, nullptr, {}, FALSE};
    EnumThreadWindows(GetCurrentThreadId(), FindParent, reinterpret_cast<LPARAM>(&f));
    if (!f.parent) return;
    UINT dpi = GetDpiForWindow(hWnd);
    INT gap = MulDiv(8, dpi ? dpi : Dpi(), USER_DEFAULT_SCREEN_DPI);
    MONITORINFO mi = {sizeof(mi)};
    if (!GetMonitorInfoW(MonitorFromRect(&f.pr, MONITOR_DEFAULTTONEAREST), &mi)) return;
    INT toRight = f.pr.right + gap, toLeft = f.pr.left - gap - w;
    if (f.right)
        wp->x = (toRight + w <= mi.rcWork.right) ? toRight : (toLeft >= mi.rcWork.left ? toLeft : wp->x);
    else
        wp->x = (toLeft >= mi.rcWork.left) ? toLeft : (toRight + w <= mi.rcWork.right ? toRight : wp->x);
}

static LRESULT CALLBACK MenuProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR)
{
    if (msg == g_edgesMsg && g_edgesMsg) { PaintSeparatorEdges(hWnd); return 0; }
    if (msg == WM_TIMER && wParam == kSubclassId) {
        KillTimer(hWnd, kSubclassId);
        PaintSeparatorEdges(hWnd);
        return 0;
    }
    if (msg == WM_NCDESTROY) {
        KillTimer(hWnd, kSubclassId);
        RemoveWindowSubclass(hWnd, MenuProc, kSubclassId);
        return DefSubclassProc(hWnd, msg, wParam, lParam);
    }
    if (msg == WM_WINDOWPOSCHANGING && lParam && !(reinterpret_cast<WINDOWPOS*>(lParam)->flags & SWP_NOMOVE))
        PlaceSubmenu(hWnd, reinterpret_cast<WINDOWPOS*>(lParam));
    if (msg == WM_NCPAINT)
        ApplyEffects(hWnd);
    LRESULT result = DefSubclassProc(hWnd, msg, wParam, lParam);
    if (msg == WM_CREATE)
        ApplyEffects(hWnd);
    if (msg == WM_NCPAINT || msg == WM_PAINT)
        PostMessageW(hWnd, g_edgesMsg, 0, 0);
    if (msg == WM_WINDOWPOSCHANGED && lParam && (reinterpret_cast<WINDOWPOS*>(lParam)->flags & SWP_SHOWWINDOW)) {
        PostMessageW(hWnd, g_edgesMsg, 0, 0);
        SetTimer(hWnd, kSubclassId, 150, nullptr);
    }
    return result;
}

// Every popup menu window of this process, title bar menus included (those never pass
// through TrackPopupMenu, so they used to keep a black, unblurred body).
static VOID OnMenuCreated(HWND hWnd)
{
    // The CBT hook and the create-event hook can both reach this window.
    static const WCHAR* const kSkinProp = L"SeamlessMenuSkinAttached";
    if (GetPropW(hWnd, kSkinProp)) return;
    SetPropW(hWnd, kSkinProp, (HANDLE)1);
    SetWindowSubclass(hWnd, MenuProc, kSubclassId, 0);
    ApplyEffects(hWnd);
}

// Delivered synchronously on this thread during the menu window's creation, before
// its first paint, so the black body never shows without the acrylic behind it.
static LRESULT CALLBACK MenuCbtProc(INT code, WPARAM w, LPARAM l)
{
    if (code == HCBT_CREATEWND) {
        HWND created = reinterpret_cast<HWND>(w);
        WCHAR cls[16];
        if (GetClassNameW(created, cls, ARRAYSIZE(cls)) &&
            wcscmp(cls, L"#32768") == 0)
            OnMenuCreated(created);
    }
    return CallNextHookEx(nullptr, code, w, l);
}
static HHOOK InstallMenuCbtHook()
{
    return SetWindowsHookExW(WH_CBT, MenuCbtProc, nullptr, GetCurrentThreadId());
}

static BOOL WINAPI TrackPopupMenu_hook(HMENU m, UINT f, INT x, INT y, INT r, HWND h, const RECT* rc)
{
    SeamlessMenuRoom::BeginTrack();
    HHOOK cbt = InstallMenuCbtHook();
    BOOL ret = TrackPopupMenu_orig(m, f, x, y, r, h, rc);
    if (cbt) UnhookWindowsHookEx(cbt);
    SeamlessMenuRoom::EndTrack();
    return ret;
}
static BOOL WINAPI TrackPopupMenuEx_hook(HMENU m, UINT f, INT x, INT y, HWND h, LPTPMPARAMS p)
{
    SeamlessMenuRoom::BeginTrack();
    HHOOK cbt = InstallMenuCbtHook();
    BOOL ret = TrackPopupMenuEx_orig(m, f, x, y, h, p);
    if (cbt) UnhookWindowsHookEx(cbt);
    SeamlessMenuRoom::EndTrack();
    return ret;
}

// Returns TRUE when the menu part was drawn here.
static BOOL PaintMenuPart(HDC hdc, INT part, INT state, LPCRECT pRect, LPCRECT pClip)
{
    if (part == 26) { part = 27; state = 2; }                   // keyboard focus: same hover
    if ((part == 27 || part == MENU_POPUPITEM) && state == 2) {
        // Keep the same gap above and below as at the sides, so the first and last rows'
        // rounded hover stays clear of the menu's own rounded corners.
        RECT rc = *pRect;
        InflateRect(&rc, 0, -MulDiv(2, Dpi(), USER_DEFAULT_SCREEN_DPI));
        return SeamlessMenuPill::Draw(g_factory, hdc, rc, Dpi());
    }
    if (part == MENU_POPUPSEPARATOR) {
        if (!g_sepDC) g_sepDC = MakeCache(1, 5, TRUE);
        if (!g_sepDC) return FALSE;
        RECT rc = *pRect;
        INT reach = MulDiv(64, Dpi(), USER_DEFAULT_SCREEN_DPI);
        rc.left -= reach; rc.right += reach;
        NineGrid(hdc, g_sepDC, &rc, 1, 5, 0, 0);
        return TRUE;
    }
    if (part == MENU_POPUPBACKGROUND || part == MENU_POPUPBORDERS || part == MENU_POPUPGUTTER ||
        part == MENU_POPUPCHECKBACKGROUND || part == 27 || part == MENU_POPUPITEM) {
        RECT rc = *pRect;
        if (pClip) IntersectRect(&rc, pRect, pClip);
        FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));   // clear: the blur shows through
        return TRUE;
    }
    return FALSE;
}

static HRESULT WINAPI DrawThemeBackground_hook(HTHEME t, HDC hdc, INT part, INT state, LPCRECT r, LPCRECT clip)
{
    if (r && IsMenuTheme(t) && PaintMenuPart(hdc, part, state, r, clip)) return S_OK;
    return DrawThemeBackground_orig(t, hdc, part, state, r, clip);
}
static HRESULT WINAPI DrawThemeBackgroundEx_hook(HTHEME t, HDC hdc, INT part, INT state, LPCRECT r, const DTBGOPTS* o)
{
    LPCRECT clip = (o && (o->dwFlags & DTBG_CLIPRECT)) ? &o->rcClip : nullptr;
    if (r && IsMenuTheme(t) && PaintMenuPart(hdc, part, state, r, clip)) return S_OK;
    return DrawThemeBackgroundEx_orig(t, hdc, part, state, r, o);
}
static HRESULT WINAPI GetThemeColor_hook(HTHEME t, INT part, INT state, INT prop, COLORREF* c)
{
    HRESULT hr = GetThemeColor_orig(t, part, state, prop, c);
    if (!c || !IsMenuTheme(t)) return hr;
    if (prop == TMT_TEXTCOLOR && (part == MENU_POPUPITEM || part == 27) && state != 3 && state != 4) {
        *c = RGB(205, 214, 244);
        return S_OK;
    }
    if (prop == TMT_FILLCOLOR || prop == TMT_FILLCOLORHINT) { *c = RGB(0, 0, 0); return S_OK; }
    return hr;
}
static HRESULT WINAPI GetThemeMargins_hook(HTHEME t, HDC hdc, INT part, INT state, INT prop, LPRECT prc, MARGINS* m)
{
    HRESULT hr = GetThemeMargins_orig(t, hdc, part, state, prop, prc, m);
    if (m && IsMenuTheme(t) && (part == MENU_POPUPITEM || part == 27 || part == 26)) {
        if (prop == TMT_CONTENTMARGINS) *m = {2, 2, 8, 8};
        else if (prop == TMT_SIZINGMARGINS) *m = {10, 10, 10, 10};
        else if (prop == 10000) *m = {0, 0, SeamlessMenuRoom::RowMargin(), SeamlessMenuRoom::RowMargin()};
    }
    return hr;
}
static HRESULT WINAPI GetThemeFont_hook(HTHEME t, HDC hdc, INT part, INT state, INT prop, LOGFONTW* f)
{
    HRESULT hr = GetThemeFont_orig(t, hdc, part, state, prop, f);
    if (SUCCEEDED(hr) && f && prop == TMT_FONT && IsMenuTheme(t) && wcscmp(f->lfFaceName, L"Segoe UI") == 0) {
        wcscpy_s(f->lfFaceName, LF_FACESIZE, L"FiraCode Nerd Font Med");
        f->lfHeight = -MulDiv(14, Dpi(), USER_DEFAULT_SCREEN_DPI);
        f->lfWeight = 500;
        f->lfQuality = CLEARTYPE_QUALITY;
        f->lfPitchAndFamily = DEFAULT_PITCH;
    }
    return hr;
}
static HRESULT WINAPI DwmSetWindowAttribute_hook(HWND h, DWORD attr, LPCVOID v, DWORD cb)
{
    if (attr == DWMWA_WINDOW_CORNER_PREFERENCE && IsMenuWindow(h)) {
        UINT corner = DWMWCP_ROUND;
        return DwmSetWindowAttribute_orig(h, attr, &corner, sizeof(corner));
    }
    return DwmSetWindowAttribute_orig(h, attr, v, cb);
}

template <typename T>
static VOID Hook(HMODULE mod, LPCSTR name, T hook, T* orig)
{
    if (auto p = mod ? GetProcAddress(mod, name) : nullptr)
        Wh_SetFunctionHook((void*)p, (void*)hook, (void**)orig);
}

// Call from the mod's init, before it returns (hooks are applied when init finishes).
static VOID Init()
{
    D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), nullptr, (void**)&g_factory);
    g_edgesMsg = RegisterWindowMessageW(L"SeamlessFlyouts_MenuSeparatorEdges");
    HMODULE ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE dwm = LoadLibraryExW(L"dwmapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE u32 = GetModuleHandleW(L"user32.dll");
    // Dark menus in this process (SetPreferredAppMode ForceDark, then FlushMenuThemes).
    using SetMode_t = INT(WINAPI*)(INT);
    using Flush_t = VOID(WINAPI*)();
    if (auto setMode = ux ? (SetMode_t)GetProcAddress(ux, MAKEINTRESOURCEA(135)) : nullptr) setMode(2);
    if (auto flush = ux ? (Flush_t)GetProcAddress(ux, MAKEINTRESOURCEA(136)) : nullptr) flush();
    Hook(ux, "DrawThemeBackground", DrawThemeBackground_hook, &DrawThemeBackground_orig);
    Hook(ux, "DrawThemeBackgroundEx", DrawThemeBackgroundEx_hook, &DrawThemeBackgroundEx_orig);
    Hook(ux, "GetThemeColor", GetThemeColor_hook, &GetThemeColor_orig);
    Hook(ux, "GetThemeMargins", GetThemeMargins_hook, &GetThemeMargins_orig);
    Hook(ux, "GetThemeFont", GetThemeFont_hook, &GetThemeFont_orig);
    Hook(dwm, "DwmSetWindowAttribute", DwmSetWindowAttribute_hook, &DwmSetWindowAttribute_orig);
    Hook(u32, "TrackPopupMenu", TrackPopupMenu_hook, &TrackPopupMenu_orig);
    Hook(u32, "TrackPopupMenuEx", TrackPopupMenuEx_hook, &TrackPopupMenuEx_orig);
    SeamlessMenuRoom::Init(OnMenuCreated);
}

static VOID Uninit()
{
    SeamlessMenuRoom::Uninit();
    for (HDC* dc : {&g_hoverDC, &g_sepDC})
        if (*dc) {
            HGDIOBJ bmp = GetCurrentObject(*dc, OBJ_BITMAP);
            DeleteDC(*dc);
            DeleteObject(bmp);
            *dc = nullptr;
        }
    if (g_factory) { g_factory->Release(); g_factory = nullptr; }
}

}  // namespace SeamlessMenuSkin

BOOL WhTool_ModInit() {
    SeamlessMenuSkin::Init();
    LoadSettings();
    LoadExcludedApps();
    LoadCycleTemplates();
    SyncAutoBlockedApps();

    g_uiReadyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, &g_uiThreadId);
    if (!g_uiThread) {
        if (g_uiReadyEvent) { CloseHandle(g_uiReadyEvent); g_uiReadyEvent = nullptr; }
        return FALSE;
    }
    if (g_uiReadyEvent) {
        WaitForSingleObject(g_uiReadyEvent, 5000);
        CloseHandle(g_uiReadyEvent);
        g_uiReadyEvent = nullptr;
    }
    StartCycleEngine();
    ContextMenuSync(g_settings.contextMenu);
    LogAudit(L"Seamless Windows Firewall started.");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_hCtrlWnd) {
        PostMessageW(g_hCtrlWnd, WM_APP_RELOAD_SETTINGS, 0, 0);
    }
}

void WhTool_ModUninit() {
    swfset::CloseSettingsWindow();
    ShutdownCycleEngine();
    if (g_hWnd) {
        PostMessageW(g_hWnd, WM_CLOSE, 0, 0);
    } else if (g_uiThreadId) {
        PostThreadMessageW(g_uiThreadId, WM_QUIT, 0, 0);
    }
    if (g_uiThread) {
        WaitForSingleObject(g_uiThread, 5000);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }

    RestoreAllSessionBlocks();
    {
        std::lock_guard<std::mutex> lk(g_engineMtx);
        CloseWfpEngineLocked();
    }
    // The Windows pop-up comes back whenever the mod stops.
    ListenWatchStop();
    ListenPromptsGiveBack();
    ContextMenuSync(false);  // No menu entry is left behind while the mod is off.
    LogAudit(L"Seamless Windows Firewall stopped cleanly.");
    SeamlessMenuSkin::Uninit();
}

// ============================================================================
// Launcher: the firewall needs administrator rights, so only Windhawk's
// elevated helper starts the tool process.
// ============================================================================

BOOL WhToolLauncher_ModInit(BOOL* bLaunch) {
    *bLaunch = IsProcessElevated() ? TRUE : FALSE;
    return TRUE;
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-22-seamless-windows-firewall\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace swfset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessWindowsFirewallSettings";
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
// Generated by work\2026-11-22-seamless-windows-firewall\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Choice, L"defaultDirection", L"What a block stops", L"Fully offline stops traffic both ways. The other two stop only one way. You can change it per app in the panel.", L"fully_offline", {{L"fully_offline", L"Fully offline (in and out)"}, {L"cant_reach_internet", L"Can't reach the internet (out only)"}, {L"cant_be_reached", L"Can't be reached (in only)"}}, 0, 100, 0, L"Blocking"},
{K::Check, L"includeChildProcesses", L"Block helper programs too", L"Also blocks the other programs in the app's own folder, such as its updater or web helper.", L"1", {}, 0, 100, 0, L"Blocking"},
{K::Check, L"lockSystemProcesses", L"Keep Windows helpers safe", L"Windows itself, Windhawk and your antivirus are always safe from a block. On, Windows' smaller helpers are locked too.", L"1", {}, 0, 100, 0, L"Safety"},
{K::Check, L"warnOnVpnOrRemote", L"Warn before blocking a VPN or remote desktop", L"Blocking one of these can cut off the connection you are using right now.", L"1", {}, 0, 100, 0, L"Safety"},
{K::Check, L"replaceFirewallPrompt", L"Ask with our own box", L"When an app wants other devices to connect to it, such as a game hosting a match, this box asks instead of the Windows Firewall pop-up. Windows Firewall keeps guarding, and your answer is saved as a normal firewall rule.", L"1", {}, 0, 100, 0, L"Connection requests"},
{K::Check, L"allowOnPublicNetworks", L"Allow on public networks too", L"Off, Allow lets the app in on home and work networks only. On a public network you are using right now, Allow always covers it.", L"0", {}, 0, 100, 0, L"Connection requests"},
{K::Check, L"contextMenu", L"Right-click menu for apps", L"Adds Seamless Windows Firewall to the right-click menu of every program file, with Block, Allow again and Open the panel. A block made there stays after a restart, like a normal firewall rule.", L"1", {}, 0, 100, 0, L"Right-click menu"},
{K::Choice, L"windowSizePreset", L"Panel size", L"", L"default", {{L"default", L"Normal (436 by 480)"}, {L"large", L"Large (680 by 680)"}, {L"extralarge", L"Extra large (840 by 840)"}}, 0, 100, 1, L"Panel"},
{K::Choice, L"defaultFilter", L"List shown first", L"The tab the panel opens on.", L"user", {{L"user", L"Running apps"}, {L"allowed", L"Allowed"}, {L"blocked", L"Blocked"}, {L"system", L"System apps"}, {L"excluded", L"Hidden apps"}}, 0, 100, 1, L"Panel"},
{K::Check, L"showNonActionableInRunning", L"Show locked apps in Running", L"Also list Windows helpers and apps that Windows Firewall already blocks, even though you cannot change them here.", L"0", {}, 0, 100, 1, L"Panel"},
{K::Check, L"showTooltips", L"Tooltips", L"Show a short tip when the pointer rests on a button, a switch or the clock.", L"0", {}, 0, 100, 1, L"Panel"},
{K::Check, L"hideDuringCapture", L"Hide from screenshots and recordings", L"The panel stays out of screen captures, streams and screen sharing.", L"1", {}, 0, 100, 1, L"Panel"},
{K::Check, L"enableCycleScheduler", L"Cycle Mode", L"Block and allow an app on a timer. Double-click or right-click an app in the panel to set it up.", L"1", {}, 0, 100, 2, L"Cycle Mode"},
{K::Check, L"rememberCycleTemplates", L"Remember each app's timer", L"The last timer you used for an app fills in next time. It never starts by itself.", L"1", {}, 0, 100, 2, L"Cycle Mode"},
{K::Check, L"showCycleMs", L"Milliseconds box", L"Show a box for milliseconds in the timer window.", L"0", {}, 0, 100, 2, L"Cycle Mode"},
{K::Hotkey, L"toggleForegroundApp", L"Block or allow the app in front", L"Press the keys in the box. Backspace clears it.", L"Ctrl+Alt+F", {}, 0, 100, 3, L"Shortcuts"},
{K::Hotkey, L"expandCollapsePill", L"Open or close the panel", L"", L"Ctrl+Alt+Shift+F", {}, 0, 100, 3, L"Shortcuts"},
{K::Hotkey, L"restoreAll", L"Allow every blocked app again", L"Off by default. Pick keys that no other app uses.", L"", {}, 0, 100, 3, L"Shortcuts"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to open the panel. Right-click it for settings and more. When off, use the shortcut.", L"1", {}, 0, 100, 4, L"Tray icon"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 4, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 4, L"Settings window"},
{K::Check, L"flyoutAnimation", L"Open and close animation", L"The panel and the connection box fade and slide in when they open and out when they close. They stay still when Windows animation effects are off.", L"1", {}, 0, 100, 4, L"Motion"},
{K::Choice, L"animationSpeed", L"Animation speed", L"How quick the animations play. Follow the global speed uses the speed shared by all DavidHiFi mods.", L"global", {{L"global", L"Follow the global speed"}, {L"veryQuick", L"Very quick"}, {L"quick", L"Quick"}, {L"normal", L"Normal"}, {L"relaxed", L"Relaxed"}, {L"slow", L"Slow"}}, 0, 100, 4, L"Motion"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Blocking", L"How a block works, the apps kept safe from it, and apps that ask to be reached.", 0xE72E},
{L"Panel", L"The panel the tray icon opens, and its app list.", 0xE8A7},
{L"Cycle Mode", L"Block and allow an app on a timer.", 0xE916},
{L"Shortcuts", L"Keys that block the app in front, open the panel and undo every block.", 0xE765},
{L"Look", L"The tray icon, motion and this settings window.", 0xE790},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;
constexpr int kSetDropMax = 9;  // A dropdown with more options than this scrolls.

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
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
constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/not-net";
constexpr PCWSTR kSetKsUrl = L"https://github.com/k-ashix";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Windows%20Firewall%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Windows Firewall";
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
    bool nativeButtons = false;  // Own title bar, but Windows draws minimize, maximize and close.
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
            rt->DrawText(L"\uEAB6", 1, s.fGlyphS.get(), {slotLeft, r.top, slotRight, r.bottom}, solid(col, 1));  // chevron_right
        } else if (m.checked) {
            rt->DrawText(L"\uEAB2", 1, s.fGlyph.get(), {slotLeft, r.top, slotRight, r.bottom},  // check
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Firewall") <= railW) break;
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

// ---- Layout -----------------------------------------------------------------

// The right-hand control's width, so the label column knows how much room it has.
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
        float textW = w.contentW - 2 * kSetRowPad - Set_ControlW(f) - 24;
        float lh = Set_TextH(w.fLabel.get(), f.label, textW);
        float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh);
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
        add(SetItem::Link, 56, L"Based on !Net by Ashix", L"The original Windhawk mod", kSetDittoUrl);
        add(SetItem::Link, 56, L"Ashix on GitHub", L"github.com/k-ashix", kSetKsUrl);
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
    {  // The glyph alone in the gradient, no plate (owner, 2026-11-24).
        D2D1_MATRIX_3X2_F old;
        p.rt->GetTransform(&old);
        const D2D1_POINT_2F mc{(mark.left + mark.right) / 2, (mark.top + mark.bottom) / 2};
        p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.75f, 1.75f, mc) * old);
        const WCHAR glyph = 0xEA18;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Windows Firewall", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Cut any app off the internet in one click, and let it back on just as fast.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, based on !Net by Ashix.",
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
    p.Text(w.fRailName.get(), L"Firewall", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    const WCHAR mark = 0xEA18;
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

static std::wstring Set_FormatHotkey(UINT mods, UINT vk) { return ::Hotkey_Format(mods, vk); }

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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Windows Firewall settings", style,
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
// The tray menu: the engine's own menu (Set_TrayMenu), rows in the order they always had.
static std::vector<SetMenuItem> TrayItems(const std::vector<TrayRow>& rows) {
    std::vector<SetMenuItem> out;
    for (const TrayRow& r : rows) {
        if (r.separator) out.push_back(Set_MenuSep());
        else if (!r.sub.empty()) out.push_back(Set_MenuSub(r.glyph.c_str(), r.label.c_str(), TrayItems(r.sub), r.disabled));
        else out.push_back(Set_MenuRow(r.id, r.glyph.c_str(), r.label.c_str(), r.checked, r.disabled, r.hint.c_str()));
    }
    return out;
}
int ShowTrayMenu(HWND owner, const POINT* at, const std::vector<TrayRow>& rows) {
    return Set_TrayMenu(owner, TrayItems(rows), at);
}
}  // namespace swfset
