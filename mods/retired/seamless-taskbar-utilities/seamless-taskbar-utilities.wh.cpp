// ==WindhawkMod==
// @id              seamless-taskbar-utilities
// @name            Seamless Taskbar Utilities
// @description     Quick system tools in the taskbar right-click menu, with a Catppuccin Mocha menu and result cards
// @version         1.7.1
// @author          DavidHiFi, Marco Petrucci
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -DWIN32_LEAN_AND_MEAN -lole32 -loleaut32 -lruntimeobject -lshell32 -lws2_32 -liphlpapi -lwininet -luser32 -luuid -lpropsys -lshlwapi -lwindowscodecs
// @license         GPL-3.0
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Taskbar Utilities

Right-click an empty spot on the taskbar to restart Explorer, clear temp files,
free up memory and more. Results show up in a small card above the taskbar.
Nothing asks for admin rights.

![Seamless Taskbar Utilities preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-taskbar-utilities.png)

## Features
- **Restart Explorer.** Restarts the taskbar and desktop in one click.
- **Clean Temp.** Deletes the files in your temp folders that nothing is using
  right now, and can empty the Recycle Bin too.
- **Reduce Memory.** Asks your running apps to hand back memory they are not
  using, then shows how much came back.
- **Restart Graphics Driver.** Same as pressing Win + Ctrl + Shift + B. Handy
  when the screen goes black or flickers.
- **Get IP Address.** Lists your local addresses, and your public one if you
  turn that on. It can copy them for you.
- **Rebuild Icon and Thumbnail Cache.** Fixes blank or wrong icons and
  thumbnails without restarting Explorer.
- **Clean DNS Cache.** Clears saved website addresses when a site will not load
  after a change.
- **Auto-hide taskbar.** Turns taskbar auto-hide on or off in one click. The
  box beside it shows whether it is on.
- **Icon separators.** Choose Add separator in the menu, then drag the thin
  blue to mauve divider between your taskbar icons. Right-click one to
  remove it. Width, color and look are in the settings.
- **Your look.** The whole taskbar menu and the cards get the same font,
  blue icons and a blue to mauve gradient border, including the stock Task
  Manager and Taskbar settings items. The clock's right-click menu gets the
  same look, and the menus use the same blurred background as the taskbar.
  The default is FiraCode Nerd Font Medium on Catppuccin Mocha.

## Notes
- Every tool can be hidden or renamed in the settings.
- Public IP lookup is off by default. When on, it asks api.ipify.org.
- If the font is not installed, the menu and cards fall back to Segoe UI.

## Credits
Based on [Taskbar System Utilities](https://windhawk.net/mods/taskbar-system-utilities)
by Marco Petrucci, which adapts the menu hooks from Taskbar Restart Explorer by
Mgrmjp. The auto-hide switch follows
[Windows 11 Taskbar Auto-Hide in Context](https://windhawk.net/mods/taskbar-autohide-in-context)
by oyrslyng. The icon separators come from
[Taskbar Icon Separators](https://windhawk.net/mods/taskbar-icon-separators)
by meteoni, with custom icon support by phntsm. GPL-3.0 license, which the
separators code requires.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- restartExplorer:
  - enabled: true
    $name: Show in menu
  - label: Restart Explorer
    $name: Menu text
  $name: Restart Explorer
  $description: Restarts the taskbar and desktop.
- cleanTemp:
  - enabled: true
    $name: Show in menu
  - label: Clean Temp
    $name: Menu text
  - cleanRecycleBin: false
    $name: Empty Recycle Bin too
    $description: When on, the Recycle Bin on every drive is emptied for good.
  - showCard: true
    $name: Show result card
    $description: When on, a card shows how many files went and how much space came back.
  $name: Clean Temp
  $description: Deletes temp files that nothing is using.
- reduceMemory:
  - enabled: true
    $name: Show in menu
  - label: Reduce Memory
    $name: Menu text
  - showCard: true
    $name: Show result card
    $description: When on, a card shows how much memory came back.
  $name: Reduce Memory
  $description: Asks running apps to give back memory they are not using.
- restartGpu:
  - enabled: true
    $name: Show in menu
  - label: Restart Graphics Driver
    $name: Menu text
  $name: Restart Graphics Driver
  $description: Presses Win + Ctrl + Shift + B for you.
- getIp:
  - enabled: true
    $name: Show in menu
  - label: Get IP Address
    $name: Menu text
  - queryPublicIp: false
    $name: Show public IP
    $description: When on, asks api.ipify.org for your public address. Off keeps everything on your PC.
  - copyToClipboard: false
    $name: Copy to clipboard
    $description: When on, the addresses are copied as soon as they show up.
  $name: Get IP Address
  $description: Shows your network addresses.
- rebuildCache:
  - enabled: true
    $name: Show in menu
  - label: Rebuild Icon & Thumbnail Cache
    $name: Menu text
  - showCard: true
    $name: Show result card
    $description: When on, a card shows what was cleared and rebuilt.
  $name: Rebuild Icon and Thumbnail Cache
  $description: Fixes blank or wrong icons and thumbnails.
- flushDns:
  - enabled: true
    $name: Show in menu
  - label: Clean DNS Cache
    $name: Menu text
  - showCard: true
    $name: Show result card
    $description: When on, a card confirms the cache was cleared.
  $name: Clean DNS Cache
  $description: Clears saved website addresses.
- autoHide:
  - enabled: true
    $name: Show in menu
  - label: Auto-hide taskbar
    $name: Menu text
  $name: Auto-hide taskbar
  $description: Turns taskbar auto-hide on or off. The box beside it shows whether it is on.
- iconSeparators:
  - enabled: true
    $name: Turn on separators
    $description: Adds thin dividers you can place between taskbar icons. Changing this reloads the mod.
  - label: Add separator
    $name: Menu text
  - interaction: contextMenu
    $name: How to add and remove
    $description: 'Right-click menu: Add separator in this menu, right-click a separator to remove it. Middle click: middle-click empty taskbar space to add, middle-click a separator to remove it.'
    $options:
    - contextMenu: Right-click menu
    - middleClick: Middle click
  - width: 20
    $name: Width
    $description: 'Space each separator takes, in pixels. Range 1 to 1000 (Suggested: 20).'
  - color: gradient
    $name: Color
    $description: Changing this reloads the mod.
    $options:
    - gradient: Blue to mauve gradient
    - solid: One color (start color)
    - original: Original grey
  - colorStart: "#89B4FA"
    $name: Start color
    $description: 'Top of the separator, as #RRGGBB (Suggested: #89B4FA, Mocha blue).'
  - colorEnd: "#CBA6F7"
    $name: End color
    $description: 'Bottom of the separator, as #RRGGBB (Suggested: #CBA6F7, Mocha mauve).'
  - alpha: 230
    $name: Opacity
    $description: 'How solid the separator looks. Range 0 to 255 (Suggested: 230).'
  - brightness: 168
    $name: Grey brightness
    $description: 'Only for Original grey. 0 is black, 255 is white (Suggested: 168).'
  - rotation: 0
    $name: Rotation
    $description: 'Turns the separator, in degrees clockwise. Range 0 to 359 (Suggested: 0).'
  - customIcon: ""
    $name: Custom icon
    $description: Optional full path to an .ico file. The color and rotation apply to it too.
  $name: Icon separators
  $description: Dividers between taskbar icons. Add them from the taskbar menu and drag them into place.
- look:
  - fontFamily: FiraCode Nerd Font
    $name: Font
    $description: 'Used for the menu items and the cards. Leave empty for Segoe UI. Falls back to Segoe UI if the font is not installed (Suggested: FiraCode Nerd Font).'
  - fontWeight: medium
    $name: Font weight
    $description: 'How thick the text is (Suggested: Medium).'
    $options:
    - light: Light
    - regular: Regular
    - medium: Medium
    - semibold: Semibold
    - bold: Bold
  - border: gradient
    $name: Border
    $description: 'The outline around the menu and each result card (Suggested: Gradient).'
    $options:
    - gradient: Gradient
    - solid: One color
    - none: No border
  - gradientStart: "#89B4FA"
    $name: Gradient start color
    $description: 'Left side of the gradient, and the color for a one-color border. Hex like #89B4FA (Suggested: Mocha blue #89B4FA).'
  - gradientEnd: "#CBA6F7"
    $name: Gradient end color
    $description: 'Right side of the gradient. Hex like #CBA6F7 (Suggested: Mocha mauve #CBA6F7).'
  - borderWidth: 2
    $name: Border width
    $description: '1 to 4 pixels (Suggested: 2).'
  - matchTaskbar: true
    $name: Match the taskbar background
    $description: 'When on, the menus and cards use the exact same blurred background as your taskbar, so a taskbar theme change carries over. When off, or if the taskbar background is not found, they use the Mocha background below (Suggested: on).'
  - cardOpacity: 90
    $name: Card background strength
    $description: 'How solid the Mocha background of the menu and cards is when they do not match the taskbar, 85 to 100. Higher hides more of what is behind (Suggested: 90).'
  - colorIcons: true
    $name: Blue menu icons
    $description: When on, every menu icon uses Mocha blue, the stock ones too. When off, they match the menu text.
  $name: Look
  $description: Font, border and colors for the menu items and the result cards.
*/
// ==/WindhawkModSettings==

// clang-format off
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <roapi.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <propkey.h>
#include <propvarutil.h>
#include <wincodec.h>
#include <wininet.h>
// clang-format on

#include <windhawk_utils.h>

#undef GetCurrentTime

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.h>
#include <winrt/base.h>

#include <algorithm>
#include <atomic>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cwctype>
#include <iterator>
#include <list>
#include <new>
#include <optional>
#include <shared_mutex>
#include <cwchar>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>


// Taskbar Icon Separators by meteoni (GPL-3.0), merged as the icon separators
// feature. Kept in its own namespace so its helpers never meet ours.
void ThemeWholeMenu(winrt::Windows::UI::Xaml::Controls::MenuFlyout const& menu);

namespace sep {
using namespace winrt::Windows::UI::Xaml;

// -----------------------------------------------------------------------------
// Private taskbar PinManager COM ABI, verified on the current Windows build.
// -----------------------------------------------------------------------------

static const CLSID CLSID_PinManager = {
    0xA5C8D635, 0xB4ED, 0x452B,
    {0x81, 0x09, 0x95, 0x01, 0x78, 0x10, 0x96, 0xD1}
};

static const IID IID_IPinManagerInterop2 = {
    0x87D9E034, 0x56D0, 0x4F8C,
    {0xBE, 0x59, 0x99, 0x7B, 0x01, 0x75, 0x47, 0x10}
};

static const IID IID_IPinManagerInterop3 = {
    0x27216D91, 0x78B8, 0x406D,
    {0x85, 0xC4, 0x5F, 0xDB, 0xF5, 0x1C, 0xD1, 0x6B}
};

enum PINNEDLISTMODIFYCALLER : int {
    // Observed from a native modern taskbar unpin on this build.
    PMC_JUMPVIEWBROKER = 11,

    PMC_TASKBANDINSERT = 23,
    PMC_TASKBANDMODIFY = 24,
    PMC_TASKBANDPIN = 25,
    PMC_TASKBANDPINGROUP = 26,
    PMC_TASKBANDREORDER = 27,
};

struct IPinManagerInterop2 : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE PinItemToTaskbarShim(
        PCUIDLIST_ABSOLUTE pidl,
        PINNEDLISTMODIFYCALLER caller) = 0;

    virtual HRESULT STDMETHODCALLTYPE PinItemFromTrustedCaller(
        PCUIDLIST_ABSOLUTE pidl,
        PINNEDLISTMODIFYCALLER caller) = 0;

    virtual HRESULT STDMETHODCALLTYPE ApplyPrependDefaultTaskbarLayout() = 0;
    virtual HRESULT STDMETHODCALLTYPE ApplyAppendDefaultTaskbarLayout() = 0;

    virtual HRESULT STDMETHODCALLTYPE ApplyInPlaceTaskbarLayout(
        int layoutType) = 0;

    virtual HRESULT STDMETHODCALLTYPE ApplyReorderTaskbarLayout(
        int layoutType,
        int value) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnpinTaskbarItem(
        PCUIDLIST_ABSOLUTE pidl,
        PINNEDLISTMODIFYCALLER caller) = 0;

    virtual HRESULT STDMETHODCALLTYPE UpdatePinnedTaskbarItem(
        PCUIDLIST_ABSOLUTE oldPidl,
        PCUIDLIST_ABSOLUTE newPidl,
        PINNEDLISTMODIFYCALLER caller) = 0;
};

struct IPinManagerInterop3 : IPinManagerInterop2 {
    virtual HRESULT STDMETHODCALLTYPE MoveTaskbarPin(
        PCUIDLIST_ABSOLUTE pidl,
        int index,
        PINNEDLISTMODIFYCALLER caller) = 0;
};

// -----------------------------------------------------------------------------
// Settings/state.
// -----------------------------------------------------------------------------

struct SeparatorSetting {
    int ordinal;       // Current mod-state row, 1-based (logging only).
    int sourceIndex;   // Current mod-state vector index, 0-based.
    int targetIndex;   // Zero-based pinned-list ordinal passed to MoveTaskbarPin.
    double width;      // FrameworkElement::MaxWidth for the separator slot.
    std::wstring stableId; // Persistent internal identity, independent of array order.
    std::wstring identity; // AppUserModelID / shortcut stem derived from stableId.
};

struct Settings {
    std::wstring identifierPrefix;
    double width = 20.0;
    std::vector<SeparatorSetting> separators;
};

static Settings g_settings;
static Settings g_appliedSettings;
static SeparatorSetting g_refreshPulseSetting;
static std::vector<SeparatorSetting> g_storedSeparatorSettings;
static std::shared_mutex g_settingsMutex;
// Serializes native Add/drag/Unpin mutations with state-file writes and the
// global Windhawk width-setting callback.
static std::mutex g_settingsMutationMutex;

enum class InteractionMode : int {
    ContextMenu,
    MiddleClick,
};

static std::atomic<InteractionMode> g_interactionMode =
    InteractionMode::ContextMenu;
// Runtime capabilities are published only after the relevant optional symbols
// have been resolved. Keeping them atomic avoids reading function-pointer slots
// concurrently with a late Taskbar.View/taskbar.dll installation.
static std::atomic<bool> g_contextMenuInteractionAvailable = false;
static std::atomic<bool> g_middleClickInteractionAvailable = false;
static std::atomic<bool> g_separatorContextSuppressionAvailable = false;

static constexpr int kDefaultIconBrightness = 168;
static constexpr int kDefaultIconAlpha = 173;
// Increment this whenever the generated artwork/encoding changes in a way that
// should force Explorer to see a completely new shell identity even when the
// user-facing appearance settings are unchanged.
static constexpr int kIconGenerationRevision = 1;
struct IconAppearanceSettings {
    int rotation = 0;
    int brightness = kDefaultIconBrightness;
    int alpha = kDefaultIconAlpha;
    unsigned long long customIconHash = 0;
    std::vector<BYTE> customIconBytes;
    // 0 = original grey, 1 = one color, 2 = start to end gradient.
    int tint = 0;
    BYTE r0 = 0, g0 = 0, b0 = 0, r1 = 0, g1 = 0, b1 = 0;
    unsigned long long tintHash = 0;
};

static IconAppearanceSettings g_iconAppearance;

static std::wstring g_storagePath;
static std::wstring g_bundledIconPath;
static std::wstring g_separatorStatePath;

// True after native state changes in memory and until the backend worker has
// durably written the matching separator-state snapshot.
static bool g_separatorStateDirty = false;  // guarded by g_settingsMutationMutex

static std::atomic<bool> g_taskbarViewDllHooked = false;
static std::atomic<bool> g_taskbarDllHooked = false;
static std::atomic<bool> g_taskbarViewHookInstallationClaimed = false;
static std::atomic<bool> g_taskbarDllHookInstallationClaimed = false;
static std::atomic<unsigned int> g_hookInstallersInFlight = 0;
static std::atomic<bool> g_loadLibraryWatcherInstalled = false;
static std::atomic<bool> g_unloading = false;
// Closed at the start of Wh_ModBeforeUninit, before the broader unloading flag
// is set. This prevents late module-load callbacks from claiming new hook work.
static std::atomic<bool> g_hookInstallationClosed = false;
// True only while this mod intentionally tears down its own pins. User-facing
// Add/Unpin callbacks must not mutate desired state during that window.
static std::atomic<bool> g_internalCleanupInProgress = false;
// This mutex protects only backend worker handles/lifetime. Hook installation
// deliberately never takes it, especially from LoadLibraryExW_Hook.
static std::mutex g_lifecycleMutex;
static bool g_backendStopped = false;
static std::atomic<bool> g_backendHasConverged = false;
// Incremented only by taskbar lifecycle starts. The backend keeps its own
// handled generation so a reconstruction that arrives during a convergence
// pass can never be lost by a boolean clear.
static std::atomic<unsigned long long> g_taskbarRefreshGeneration = 0;
static HANDLE g_backendThread = nullptr;
static HANDLE g_backendStopEvent = nullptr;
static HANDLE g_backendWakeEvent = nullptr;
static thread_local HANDLE g_currentBackendStopEvent = nullptr;
static thread_local HANDLE g_currentBackendWakeEvent = nullptr;

static constexpr wchar_t kSeparatorIdentitySuffix[] = L"8F31A7D2";
static constexpr wchar_t kSeparatorIdentifierPrefix[] = L"WindhawkSeparator";
static constexpr wchar_t kSeparatorStateFileName[] = L"separator-state-v1.txt";

// Read-only compatibility key used only for the one-time migration from the
// pre-p42 builds. New builds never write separator configuration to Windhawk
// values/settings; the authoritative separator list lives in mod storage.
static constexpr wchar_t kLegacyIdentityManifestValueName[] =
    L"separatorIdentityManifestV1";

// Reserved outside the supported separator range. The helper is used only for
// taskbar startup/reconstruction and backing-file recovery, where Explorer may
// need a concrete pin-list mutation to reconcile stale taskbar visuals.
static constexpr int kRefreshPulseOrdinal = 100001;

// -----------------------------------------------------------------------------
// Embedded icon.
//
// Compact five-frame 32-bit ICO generated from the separator artwork.
// Keeps native 16/24/32/48 px taskbar frames plus a crisp 256 px fallback.
// Main stroke max alpha is ~68% to retain the original separator's subtlety.
// -----------------------------------------------------------------------------

static constexpr unsigned char kSeparatorIcon[] = {
    0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x10, 0x10, 0x00, 0x00, 0x01, 0x00,
    0x20, 0x00, 0x96, 0x00, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0x18, 0x18,
    0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0xA3, 0x00, 0x00, 0x00, 0xEC, 0x00,
    0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0xD7, 0x00,
    0x00, 0x00, 0x8F, 0x01, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x01, 0x00,
    0x20, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x66, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0xFB, 0x02, 0x00, 0x00, 0x3E, 0x03,
    0x00, 0x00, 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00,
    0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0xF3, 0xFF, 0x61, 0x00,
    0x00, 0x00, 0x5D, 0x49, 0x44, 0x41, 0x54, 0x78, 0xDA, 0xC5, 0x8F, 0xB1,
    0x0D, 0x80, 0x40, 0x0C, 0x03, 0x1D, 0x44, 0xC1, 0x38, 0x4C, 0xC5, 0x6A,
    0xC9, 0x18, 0x4C, 0x85, 0x28, 0x90, 0x4C, 0xF3, 0x75, 0x1C, 0x7D, 0x84,
    0x70, 0x7B, 0xD2, 0xE5, 0x02, 0x88, 0x45, 0x84, 0x65, 0x7C, 0xC9, 0xA0,
    0xBB, 0x1B, 0xC9, 0x63, 0x5A, 0x30, 0xB6, 0x77, 0x05, 0x5B, 0x06, 0xD7,
    0x0C, 0x9A, 0x99, 0x14, 0x54, 0x0A, 0x30, 0x5D, 0x40, 0x52, 0x1E, 0x51,
    0x05, 0xA6, 0x8E, 0x54, 0x5E, 0x60, 0x47, 0x40, 0x00, 0xCF, 0xAF, 0x05,
    0x72, 0x15, 0xC1, 0xD5, 0x15, 0xDC, 0x5D, 0xC1, 0x89, 0x2F, 0xF7, 0x02,
    0x23, 0xAF, 0x11, 0x61, 0xB9, 0x24, 0x17, 0xE9, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 0x89, 0x50, 0x4E, 0x47,
    0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x08, 0x06, 0x00, 0x00,
    0x00, 0xE0, 0x77, 0x3D, 0xF8, 0x00, 0x00, 0x00, 0x6A, 0x49, 0x44, 0x41,
    0x54, 0x78, 0xDA, 0xE5, 0x93, 0xB1, 0x0D, 0x80, 0x30, 0x0C, 0x04, 0xCF,
    0x09, 0x05, 0x03, 0xB0, 0x30, 0xD3, 0x24, 0x53, 0x31, 0x07, 0x08, 0xA4,
    0xA7, 0x62, 0x00, 0x17, 0x8F, 0x22, 0xC5, 0xF5, 0x4B, 0xA7, 0xB7, 0xCF,
    0x30, 0xDA, 0xF4, 0xDE, 0x6B, 0x26, 0x5F, 0x32, 0xE1, 0xD6, 0x5A, 0x95,
    0xB4, 0xDB, 0x00, 0x40, 0x00, 0x9B, 0x13, 0x00, 0xB0, 0xD8, 0xC2, 0x11,
    0x01, 0xB0, 0x0E, 0xD5, 0xA0, 0xB8, 0xAD, 0xB3, 0x03, 0x52, 0x75, 0x25,
    0x7D, 0x26, 0x59, 0x35, 0xB5, 0x5B, 0x64, 0x5F, 0x91, 0xF5, 0xC8, 0xFA,
    0xC3, 0xA2, 0x7B, 0xAE, 0x3F, 0x18, 0x12, 0x70, 0xBA, 0x01, 0x8F, 0x5B,
    0xD3, 0xCB, 0x0D, 0x38, 0x98, 0x6A, 0x5E, 0xAA, 0x6E, 0x15, 0x90, 0x48,
    0x17, 0x18, 0x68, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE,
    0x42, 0x60, 0x82, 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00,
    0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x20, 0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 0x7A, 0x7A, 0xF4,
    0x00, 0x00, 0x00, 0x9E, 0x49, 0x44, 0x41, 0x54, 0x78, 0xDA, 0xED, 0x95,
    0xC1, 0x0D, 0x02, 0x31, 0x0C, 0x04, 0xC7, 0xE1, 0xC4, 0x87, 0x2F, 0x7D,
    0x50, 0x0A, 0x0F, 0x8A, 0x8C, 0x8B, 0xA0, 0x16, 0x2A, 0xB8, 0x02, 0x90,
    0x38, 0x58, 0x3E, 0xA1, 0x81, 0x04, 0x69, 0x85, 0xC8, 0x4A, 0x79, 0xC6,
    0x9E, 0xD8, 0x6B, 0x07, 0x7E, 0x59, 0x99, 0x19, 0x99, 0x59, 0x46, 0x62,
    0x74, 0x5F, 0xAE, 0xB5, 0x86, 0xA4, 0x45, 0xD2, 0xC5, 0x02, 0x00, 0x04,
    0x70, 0x06, 0x4E, 0x2E, 0x00, 0x80, 0x03, 0x70, 0x74, 0x02, 0x14, 0x60,
    0xE7, 0x04, 0x88, 0x51, 0x80, 0xA5, 0x3B, 0x73, 0x04, 0x2D, 0xF9, 0xDE,
    0x69, 0xC2, 0x32, 0xF2, 0x88, 0x6F, 0xB4, 0x60, 0x58, 0x13, 0xA0, 0xBB,
    0x7F, 0x92, 0x3E, 0x3E, 0x88, 0xBF, 0xDF, 0x03, 0xE1, 0xDC, 0x03, 0x76,
    0x0F, 0xCC, 0x31, 0x7C, 0xB5, 0x63, 0x05, 0x78, 0xCE, 0x4D, 0x38, 0x01,
    0x5C, 0x00, 0x02, 0x36, 0xE0, 0xEE, 0xAC, 0x80, 0xDC, 0x53, 0x60, 0x1F,
    0xC3, 0x0D, 0x78, 0x38, 0x3D, 0xB0, 0x02, 0x37, 0xCB, 0x67, 0xD4, 0x74,
    0x6D, 0x55, 0x98, 0xEA, 0xD6, 0x1B, 0x1B, 0x0D, 0x24, 0x96, 0xB9, 0xB5,
    0x4C, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42,
    0x60, 0x82, 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00,
    0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
    0x00, 0x30, 0x08, 0x06, 0x00, 0x00, 0x00, 0x57, 0x02, 0xF9, 0x87, 0x00,
    0x00, 0x00, 0x9F, 0x49, 0x44, 0x41, 0x54, 0x78, 0xDA, 0xED, 0x96, 0x31,
    0x0E, 0x02, 0x31, 0x0C, 0x04, 0x37, 0x84, 0x82, 0x07, 0xF0, 0xDC, 0x6B,
    0x78, 0x4D, 0xFC, 0x2A, 0xDE, 0x01, 0xE2, 0x24, 0xD3, 0xE4, 0x9A, 0x13,
    0xA2, 0x0B, 0x1B, 0x60, 0xB6, 0x89, 0x94, 0xC2, 0xD1, 0x66, 0x64, 0x7B,
    0x25, 0xF4, 0xC3, 0x8A, 0x88, 0x1A, 0x11, 0x75, 0xE4, 0x1B, 0x87, 0x6F,
    0xFF, 0xA4, 0xE3, 0x88, 0xA2, 0xAD, 0xB5, 0x2A, 0x49, 0x99, 0x79, 0xE9,
    0x57, 0x0B, 0x04, 0x3E, 0x49, 0x40, 0x52, 0xE9, 0xE7, 0x79, 0xB4, 0x01,
    0x08, 0x98, 0xEB, 0x43, 0xE0, 0x75, 0x03, 0x94, 0xAD, 0x05, 0x74, 0x82,
    0x00, 0x3D, 0x30, 0xB9, 0x30, 0x80, 0x01, 0xA6, 0xD0, 0x00, 0x65, 0xE6,
    0x3E, 0x13, 0x41, 0xC0, 0x95, 0x46, 0xD9, 0x03, 0xEE, 0x2C, 0xC4, 0x14,
    0x72, 0x4F, 0x21, 0x08, 0xB8, 0xA6, 0x50, 0x42, 0x60, 0x92, 0xBC, 0xFE,
    0x80, 0x00, 0x06, 0x30, 0x80, 0x01, 0x0C, 0xFC, 0xF5, 0x1E, 0xB8, 0x41,
    0xC0, 0x4C, 0x60, 0x85, 0x80, 0x39, 0x8D, 0xDE, 0x21, 0x60, 0x26, 0x70,
    0x85, 0x00, 0x42, 0xE8, 0xAD, 0x9E, 0x87, 0xF7, 0x18, 0x47, 0xDD, 0x53,
    0x1E, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42,
    0x60, 0x82, 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00,
    0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x08, 0x06, 0x00, 0x00, 0x00, 0x5C, 0x72, 0xA8, 0x66, 0x00,
    0x00, 0x02, 0xC2, 0x49, 0x44, 0x41, 0x54, 0x78, 0xDA, 0xED, 0xDD, 0xC1,
    0x6D, 0xC2, 0x50, 0x10, 0x45, 0x51, 0x7F, 0x60, 0x41, 0x01, 0x14, 0xE7,
    0x62, 0xD8, 0xA4, 0x1A, 0xBB, 0x2A, 0xEA, 0x48, 0x44, 0xA2, 0xA1, 0x04,
    0x7E, 0xB2, 0x8A, 0xDF, 0x9C, 0xB3, 0xB6, 0x58, 0x8C, 0xA5, 0xAB, 0x59,
    0x8C, 0xCC, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x34, 0x8C, 0xA0, 0x8F, 0x7D, 0xDF, 0xCF, 0xB3, 0xCF,
    0xAE, 0xEB, 0xFA, 0x63, 0x62, 0xF9, 0x4E, 0x46, 0x00, 0x02, 0x00, 0x08,
    0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00,
    0x80, 0x00, 0x00, 0xC7, 0x77, 0x31, 0x82, 0xE3, 0xDB, 0xB6, 0x6D, 0xEA,
    0xC2, 0xAF, 0xAA, 0x3E, 0x7E, 0xF1, 0xB3, 0x77, 0x93, 0xB5, 0x01, 0x00,
    0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08,
    0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0xFC, 0x67, 0x4E, 0x81,
    0x33, 0xCC, 0x7E, 0xDC, 0xF5, 0x66, 0x54, 0xD8, 0x00, 0x00, 0x01, 0x00,
    0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04,
    0x00, 0x10, 0x00, 0x40, 0x00, 0x80, 0x14, 0x4E, 0x81, 0xBD, 0x6F, 0x6C,
    0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00,
    0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0xC0, 0x91, 0xB9, 0x0C, 0x0B,
    0x30, 0xC6, 0xEC, 0x37, 0x41, 0x97, 0xAB, 0x69, 0x61, 0x03, 0x00, 0x04,
    0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00,
    0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x52, 0x38, 0x05, 0xF6, 0xBE,
    0xB1, 0x01, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00,
    0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08,
    0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00,
    0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00,
    0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08,
    0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0xF0, 0x9E,
    0xFF, 0x8B, 0x0F, 0x50, 0x55, 0xB3, 0x8F, 0x0E, 0xD3, 0xC2, 0x06, 0x00,
    0x08, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08,
    0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0xA4, 0x70, 0x0A, 0x9C,
    0x61, 0x78, 0xDF, 0xD8, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00,
    0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x10, 0x00, 0xA0,
    0x29, 0x97, 0x61, 0x01, 0xC6, 0xF0, 0xAD, 0x4F, 0x6C, 0x00, 0x80, 0x00,
    0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00,
    0x08, 0x00, 0x08, 0x00, 0x20, 0x00, 0x40, 0x3F, 0x4E, 0x81, 0x03, 0x54,
    0x95, 0x21, 0x60, 0x03, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00,
    0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x01,
    0x00, 0xDA, 0x71, 0x0A, 0x9C, 0xC1, 0x2D, 0x30, 0x36, 0x00, 0x40, 0x00,
    0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00,
    0x04, 0x00, 0x04, 0x00, 0xE8, 0xCA, 0x25, 0x60, 0x2F, 0x4F, 0x23, 0xC0,
    0x06, 0x00, 0x08, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02,
    0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00,
    0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80,
    0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02,
    0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00,
    0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80,
    0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02,
    0x00, 0x08, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x7D, 0x5C,
    0x8C, 0xA0, 0x95, 0x4F, 0x23, 0xC0, 0x06, 0x00, 0x08, 0x00, 0x08, 0x00,
    0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80,
    0x00, 0x00, 0x02, 0x00, 0xA4, 0x70, 0x0A, 0xDC, 0xCB, 0xB7, 0x11, 0x60,
    0x03, 0x00, 0x04, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01,
    0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x80, 0x30, 0x2E, 0x01, 0x33,
    0xD4, 0xE4, 0x73, 0x5F, 0x46, 0x85, 0x0D, 0x00, 0x10, 0x00, 0x10, 0x00,
    0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00,
    0x01, 0x00, 0x04, 0x00, 0x48, 0xE1, 0x14, 0x38, 0xC3, 0xEC, 0x29, 0xF0,
    0xC3, 0xA8, 0xB0, 0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20,
    0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xF2,
    0x02, 0x89, 0xB8, 0x19, 0xBE, 0xE1, 0x19, 0xC6, 0xA9, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82,
};

// -----------------------------------------------------------------------------
// Small helpers.
// -----------------------------------------------------------------------------

static std::wstring JoinPath(
    const std::wstring& directory,
    const std::wstring& fileName) {
    if (directory.empty()) {
        return fileName;
    }

    if (directory.back() == L'\\' || directory.back() == L'/') {
        return directory + fileName;
    }

    return directory + L"\\" + fileName;
}

static std::wstring BuildIconGenerationToken(
    const IconAppearanceSettings& appearance) {
    wchar_t token[96] = {};

    if (!appearance.customIconBytes.empty() || appearance.tint) {
        swprintf_s(
            token,
            L"g%d-r%d-b%d-a%d-c%016llx",
            kIconGenerationRevision,
            appearance.rotation,
            appearance.brightness,
            appearance.alpha,
            appearance.customIconHash ^ appearance.tintHash);
    } else {
        swprintf_s(
            token,
            L"g%d-r%d-b%d-a%d",
            kIconGenerationRevision,
            appearance.rotation,
            appearance.brightness,
            appearance.alpha);
    }

    return token;
}

static std::wstring BuildBundledIconFileName(
    const IconAppearanceSettings& appearance) {
    return L"separator-icon-" +
        BuildIconGenerationToken(appearance) +
        L".ico";
}

static void ConfigureAppearanceGenerationPaths() {
    g_bundledIconPath = JoinPath(
        g_storagePath,
        BuildBundledIconFileName(g_iconAppearance));
}

static std::wstring BuildSeparatorIdentity(
    std::wstring_view prefix,
    std::wstring_view stableId) {
    // stableId is the durable identity stored in separator-state-v1.txt. The
    // generation suffix is deliberately shell-facing only: an icon appearance
    // change produces a fresh .lnk path and AppUserModelID without disturbing
    // the user's persisted separator positions.
    return std::wstring(prefix) +
           L"." +
           kSeparatorIdentitySuffix +
           L"." +
           std::wstring(stableId) +
           L"." +
           BuildIconGenerationToken(g_iconAppearance);
}

static std::wstring GetSeparatorShortcutPath(
    const SeparatorSetting& separator) {
    return JoinPath(
        g_storagePath,
        separator.identity + L".lnk");
}

static bool FileExists(const std::wstring& path) {
    DWORD attrs = GetFileAttributesW(path.c_str());
    return attrs != INVALID_FILE_ATTRIBUTES &&
           !(attrs & FILE_ATTRIBUTE_DIRECTORY);
}

static bool DeleteFileIfPresent(const std::wstring& path) {
    if (!FileExists(path)) {
        return true;
    }

    if (DeleteFileW(path.c_str())) {
        return true;
    }

    Wh_Log(
        L"[FILES] DeleteFileW('%s') failed error=%u",
        path.c_str(),
        GetLastError());

    return false;
}

// The private mod storage directory is the durable ownership record. Every
// shortcut in it was created by this mod, including shortcuts from an older
// settings snapshot or an interrupted refresh pulse.
static std::vector<std::wstring> EnumerateSeparatorShortcuts() {
    std::vector<std::wstring> paths;
    WIN32_FIND_DATAW findData = {};
    HANDLE find = FindFirstFileW(
        JoinPath(g_storagePath, L"*.lnk").c_str(),
        &findData);

    if (find == INVALID_HANDLE_VALUE) {
        return paths;
    }

    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            paths.push_back(
                JoinPath(g_storagePath, findData.cFileName));
        }
    } while (FindNextFileW(find, &findData));

    FindClose(find);
    std::sort(paths.begin(), paths.end());
    return paths;
}

static bool IsValidIconGenerationToken(std::wstring_view token) {
    if (token.empty()) {
        return false;
    }

    std::wstring candidate(token);
    int revision = 0;
    int rotation = 0;
    int brightness = 0;
    int alpha = 0;
    unsigned long long customIconHash = 0;
    int consumed = 0;

    int matched = swscanf(
        candidate.c_str(),
        L"g%d-r%d-b%d-a%d-c%16llx%n",
        &revision,
        &rotation,
        &brightness,
        &alpha,
        &customIconHash,
        &consumed);

    if (matched == 5 &&
        consumed == static_cast<int>(candidate.size())) {
        // BuildIconGenerationToken always writes exactly 16 hexadecimal hash
        // digits. Keep ownership recognition equally strict so cleanup never
        // adopts a merely prefix-compatible filename that this mod can't emit.
        const size_t hashMarker = candidate.rfind(L"-c");
        const bool hashWidthValid =
            hashMarker != std::wstring::npos &&
            candidate.size() - hashMarker - 2 == 16 &&
            std::all_of(
                candidate.begin() + hashMarker + 2,
                candidate.end(),
                [](wchar_t ch) {
                    return (ch >= L'0' && ch <= L'9') ||
                           (ch >= L'a' && ch <= L'f') ||
                           (ch >= L'A' && ch <= L'F');
                });

        return hashWidthValid &&
            revision > 0 &&
            rotation >= 0 && rotation < 360 &&
            brightness >= 0 && brightness <= 255 &&
            alpha >= 0 && alpha <= 255;
    }

    consumed = 0;
    matched = swscanf(
        candidate.c_str(),
        L"g%d-r%d-b%d-a%d%n",
        &revision,
        &rotation,
        &brightness,
        &alpha,
        &consumed);

    return matched == 4 &&
        consumed == static_cast<int>(candidate.size()) &&
        revision > 0 &&
        rotation >= 0 && rotation < 360 &&
        brightness >= 0 && brightness <= 255 &&
        alpha >= 0 && alpha <= 255;
}

static bool IsOwnedBundledIconArtifactName(std::wstring_view fileName) {
    std::wstring candidate(fileName);
    if (candidate.size() > 4 &&
        _wcsicmp(candidate.c_str() + candidate.size() - 4, L".tmp") == 0) {
        candidate.resize(candidate.size() - 4);
    }

    // Fixed-name artifact from 1.0.25 and earlier.
    if (_wcsicmp(candidate.c_str(), L"separator.ico") == 0) {
        return true;
    }

    static constexpr std::wstring_view currentPrefix = L"separator-icon-";
    static constexpr std::wstring_view icoSuffix = L".ico";
    std::wstring_view candidateView(candidate);
    if (candidateView.size() > currentPrefix.size() + icoSuffix.size() &&
        candidateView.substr(0, currentPrefix.size()) == currentPrefix &&
        candidateView.substr(candidateView.size() - icoSuffix.size()) == icoSuffix) {
        std::wstring_view generation = candidateView.substr(
            currentPrefix.size(),
            candidateView.size() - currentPrefix.size() - icoSuffix.size());
        if (IsValidIconGenerationToken(generation)) {
            return true;
        }
    }

    // Appearance-keyed names used by 1.0.22-1.0.24. Keep recognizing them
    // strictly as legacy mod-owned artifacts so successful convergence can
    // purge every obsolete icon generation.
    int revision = 0;
    int rotation = 0;
    int brightness = 0;
    int alpha = 0;
    int consumed = 0;
    int matched = swscanf(
        candidate.c_str(),
        L"separator-icon-v%d-r%d-b%d-a%d.ico%n",
        &revision,
        &rotation,
        &brightness,
        &alpha,
        &consumed);

    return matched == 4 &&
        consumed == static_cast<int>(candidate.size()) &&
        revision > 0 &&
        (rotation == 0 || rotation == 90 ||
         rotation == 180 || rotation == 270) &&
        brightness >= 0 && brightness <= 255 &&
        alpha >= 0 && alpha <= 255;
}

static std::vector<std::wstring> EnumerateBundledIconArtifacts() {
    std::vector<std::wstring> paths;
    if (g_storagePath.empty()) {
        return paths;
    }
    WIN32_FIND_DATAW findData = {};
    HANDLE find = FindFirstFileW(
        JoinPath(g_storagePath, L"separator*.ico*").c_str(),
        &findData);

    if (find == INVALID_HANDLE_VALUE) {
        return paths;
    }

    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            IsOwnedBundledIconArtifactName(findData.cFileName)) {
            paths.push_back(
                JoinPath(g_storagePath, findData.cFileName));
        }
    } while (FindNextFileW(find, &findData));

    FindClose(find);
    std::sort(paths.begin(), paths.end());
    return paths;
}

static bool PathsEqualOrdinalIgnoreCase(
    std::wstring_view first,
    std::wstring_view second) {
    if (first.size() > INT_MAX || second.size() > INT_MAX) {
        return false;
    }

    return CompareStringOrdinal(
               first.data(),
               static_cast<int>(first.size()),
               second.data(),
               static_cast<int>(second.size()),
               TRUE) == CSTR_EQUAL;
}

static void DeleteAllBundledIconArtifacts() {
    if (g_storagePath.empty()) {
        return;
    }

    for (const auto& path : EnumerateBundledIconArtifacts()) {
        DeleteFileIfPresent(path);
    }
}

static bool DeleteStaleBundledIconArtifacts() {
    if (g_storagePath.empty() || g_bundledIconPath.empty()) {
        return true;
    }

    bool success = true;
    const std::wstring currentTemporaryPath =
        g_bundledIconPath + L".tmp";

    // Only call this after a successful convergence: at that point every
    // surviving owned shortcut has been verified/recreated against the current
    // appearance path. Until then an interrupted older reload may still have a
    // live shortcut referencing one of these previous cache files.
    for (const auto& path : EnumerateBundledIconArtifacts()) {
        if (PathsEqualOrdinalIgnoreCase(path, g_bundledIconPath) ||
            PathsEqualOrdinalIgnoreCase(path, currentTemporaryPath)) {
            continue;
        }

        if (!DeleteFileIfPresent(path)) {
            success = false;
        }
    }

    // A completed atomic write never needs its temporary sibling. Keeping this
    // separate also cleans a .tmp left by an interrupted process without
    // touching the current final icon.
    if (!DeleteFileIfPresent(currentTemporaryPath)) {
        success = false;
    }

    return success;
}

static std::wstring GetShortcutIdentity(const std::wstring& path) {
    size_t fileNameStart = path.find_last_of(L"\\/");
    fileNameStart = fileNameStart == std::wstring::npos
                        ? 0
                        : fileNameStart + 1;

    size_t extension = path.find_last_of(L'.');
    if (extension == std::wstring::npos || extension < fileNameStart) {
        extension = path.size();
    }

    return path.substr(fileNameStart, extension - fileNameStart);
}

static bool IsIdentityInSettings(
    const Settings& settings,
    std::wstring_view identity) {
    return std::any_of(
        settings.separators.begin(),
        settings.separators.end(),
        [identity](const SeparatorSetting& separator) {
            return identity == std::wstring_view(separator.identity);
        });
}


struct LegacySeparatorIdentitySeed {
    std::wstring stableId;
    int sourceIndex;
    int targetIndex;
};

static bool IsValidStableId(std::wstring_view value) {
    if (value.empty() || value.size() > 64) {
        return false;
    }

    return std::all_of(
        value.begin(),
        value.end(),
        [](wchar_t ch) {
            return std::iswalnum(ch) ||
                   ch == L'-' || ch == L'_';
        });
}

static std::optional<std::wstring> ExtractStableIdFromSeparatorIdentity(
    std::wstring_view identity) {
    static const std::wstring marker =
        std::wstring(L".") +
        kSeparatorIdentitySuffix +
        L".";

    size_t markerPosition = identity.rfind(marker);
    if (markerPosition == std::wstring_view::npos) {
        return std::nullopt;
    }

    std::wstring_view payload = identity.substr(
        markerPosition + marker.size());
    if (payload.empty()) {
        return std::nullopt;
    }

    // <=1.0.25 identities ended immediately after stableId. 1.0.26+ appends
    // one validated appearance generation token. Accept both so stale task
    // groups remain inert during upgrade and state-less legacy adoption can
    // recover the same durable stable ID before replacing their shell objects.
    std::wstring_view stableId = payload;
    size_t generationSeparator = payload.rfind(L'.');
    if (generationSeparator != std::wstring_view::npos) {
        stableId = payload.substr(0, generationSeparator);
        std::wstring_view generation = payload.substr(generationSeparator + 1);
        if (!IsValidIconGenerationToken(generation)) {
            return std::nullopt;
        }
    }

    if (!IsValidStableId(stableId)) {
        return std::nullopt;
    }

    return std::wstring(stableId);
}


static bool ParseWideInt(
    std::wstring_view text,
    int* valueOut) {
    if (!valueOut) {
        return false;
    }

    while (!text.empty() && std::iswspace(text.front())) {
        text.remove_prefix(1);
    }
    while (!text.empty() && std::iswspace(text.back())) {
        text.remove_suffix(1);
    }
    if (text.empty()) {
        return false;
    }

    std::wstring copy(text);
    wchar_t* end = nullptr;
    long value = std::wcstol(
        copy.c_str(),
        &end,
        10);

    if (!end || *end != L'\0' ||
        value < INT_MIN || value > INT_MAX) {
        return false;
    }

    *valueOut = static_cast<int>(value);
    return true;
}

static std::vector<LegacySeparatorIdentitySeed>
LoadLegacyIdentityManifest() {
    std::vector<wchar_t> buffer(65536);
    size_t length = Wh_GetStringValue(
        kLegacyIdentityManifestValueName,
        buffer.data(),
        buffer.size());

    if (!length) {
        return {};
    }

    std::vector<LegacySeparatorIdentitySeed> result;
    std::wstring_view data(buffer.data(), length);
    size_t lineStart = 0;

    while (lineStart < data.size()) {
        size_t lineEnd = data.find(L'\n', lineStart);
        if (lineEnd == std::wstring_view::npos) {
            lineEnd = data.size();
        }

        std::wstring_view line =
            data.substr(lineStart, lineEnd - lineStart);
        if (!line.empty() && line.back() == L'\r') {
            line.remove_suffix(1);
        }

        // Legacy format:
        // stableId<TAB>sourceIndex<TAB>targetIndex<TAB>width
        std::wstring_view fields[4];
        size_t fieldStart = 0;
        bool valid = true;

        for (int field = 0; field < 4; field++) {
            size_t fieldEnd =
                field == 3
                    ? line.size()
                    : line.find(L'\t', fieldStart);

            if (fieldEnd == std::wstring_view::npos ||
                fieldStart > line.size()) {
                valid = false;
                break;
            }

            fields[field] =
                line.substr(fieldStart, fieldEnd - fieldStart);
            fieldStart = fieldEnd + 1;
        }

        if (valid && IsValidStableId(fields[0])) {
            int sourceIndex = 0;
            int targetIndex = 0;
            int ignoredWidth = 0;

            if (ParseWideInt(fields[1], &sourceIndex) &&
                ParseWideInt(fields[2], &targetIndex) &&
                ParseWideInt(fields[3], &ignoredWidth) &&
                sourceIndex >= -1 &&
                targetIndex >= -1) {
                result.push_back({
                    .stableId = std::wstring(fields[0]),
                    .sourceIndex = sourceIndex,
                    .targetIndex = targetIndex,
                });
            }
        }

        lineStart = lineEnd + 1;
    }

    return result;
}

static void AppendHex(
    std::wstring& output,
    unsigned long long value,
    int digits) {
    static constexpr wchar_t kHexDigits[] =
        L"0123456789abcdef";

    for (int digit = digits - 1; digit >= 0; digit--) {
        output.push_back(
            kHexDigits[
                (value >> (digit * 4)) & 0xF]);
    }
}

static bool GenerateRandomBytes(
    BYTE* buffer,
    ULONG size) {
    using BCryptGenRandom_t =
        LONG(WINAPI*)(
            void* algorithm,
            BYTE* buffer,
            ULONG size,
            ULONG flags);

    static BCryptGenRandom_t bcryptGenRandom = [] {
        HMODULE bcrypt =
            GetModuleHandleW(L"bcrypt.dll");
        if (!bcrypt) {
            bcrypt = LoadLibraryExW(
                L"bcrypt.dll",
                nullptr,
                LOAD_LIBRARY_SEARCH_SYSTEM32);
        }

        return bcrypt
                   ? reinterpret_cast<BCryptGenRandom_t>(
                         GetProcAddress(
                             bcrypt,
                             "BCryptGenRandom"))
                   : nullptr;
    }();

    // BCRYPT_USE_SYSTEM_PREFERRED_RNG.
    constexpr ULONG kUseSystemPreferredRng = 0x00000002;

    return bcryptGenRandom &&
        bcryptGenRandom(
            nullptr,
            buffer,
            size,
            kUseSystemPreferredRng) >= 0;
}

static std::wstring GenerateStableId() {
    BYTE randomBytes[16] = {};

    if (GenerateRandomBytes(
            randomBytes,
            ARRAYSIZE(randomBytes))) {
        std::wstring result = L"g";
        result.reserve(33);

        for (BYTE byte : randomBytes) {
            AppendHex(result, byte, 2);
        }

        return result;
    }

    // BCryptGenRandom should always be available on supported Windows
    // versions. Retain a process-local fallback so a native Add action doesn't
    // fail merely because random generation unexpectedly did.
    static std::atomic<unsigned long long> counter{0};
    LARGE_INTEGER performanceCounter = {};
    QueryPerformanceCounter(&performanceCounter);

    unsigned long long seed =
        static_cast<unsigned long long>(
            performanceCounter.QuadPart) ^
        (GetTickCount64() << 17) ^
        (static_cast<unsigned long long>(
             GetCurrentProcessId()) << 32) ^
        GetCurrentThreadId();

    std::wstring result = L"g";
    AppendHex(result, seed, 16);
    AppendHex(
        result,
        counter.fetch_add(
            1,
            std::memory_order_relaxed),
        16);
    return result;
}


static bool ParseStateInt(
    std::string_view text,
    int* valueOut) {
    if (!valueOut || text.empty()) {
        return false;
    }

    std::string copy(text);
    char* end = nullptr;
    long value = std::strtol(
        copy.c_str(),
        &end,
        10);

    if (!end || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        return false;
    }

    *valueOut = static_cast<int>(value);
    return true;
}

static bool ReadSeparatorStateFile(
    double width,
    Settings* settingsOut,
    bool* existsOut,
    bool* contentInvalidOut) {
    if (!settingsOut || !existsOut || !contentInvalidOut) {
        return false;
    }

    *existsOut = false;
    *contentInvalidOut = false;
    settingsOut->identifierPrefix = kSeparatorIdentifierPrefix;
    settingsOut->width = width;
    settingsOut->separators.clear();

    DWORD attrs =
        GetFileAttributesW(g_separatorStatePath.c_str());
    if (attrs == INVALID_FILE_ATTRIBUTES) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND ||
            GetLastError() == ERROR_PATH_NOT_FOUND) {
            return true;
        }

        Wh_Log(
            L"[STATE] GetFileAttributesW('%s') failed error=%u",
            g_separatorStatePath.c_str(),
            GetLastError());
        return false;
    }

    if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
        Wh_Log(
            L"[STATE] State path is unexpectedly a directory: '%s'",
            g_separatorStatePath.c_str());
        return false;
    }

    *existsOut = true;

    HANDLE file =
        CreateFileW(
            g_separatorStatePath.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr);

    if (file == INVALID_HANDLE_VALUE) {
        Wh_Log(
            L"[STATE] CreateFileW('%s') for read failed error=%u",
            g_separatorStatePath.c_str(),
            GetLastError());
        return false;
    }

    LARGE_INTEGER size = {};
    if (!GetFileSizeEx(file, &size)) {
        DWORD error = GetLastError();
        CloseHandle(file);
        Wh_Log(
            L"[STATE] GetFileSizeEx failed error=%u",
            error);
        return false;
    }

    if (size.QuadPart < 0 ||
        size.QuadPart > 1024 * 1024) {
        CloseHandle(file);
        Wh_Log(
            L"[STATE] Invalid state-file size=%lld",
            static_cast<long long>(size.QuadPart));
        *contentInvalidOut = true;
        return false;
    }

    std::string data(
        static_cast<size_t>(size.QuadPart),
        '\0');

    DWORD bytesRead = 0;
    BOOL readOk =
        data.empty() ||
        ReadFile(
            file,
            data.data(),
            static_cast<DWORD>(data.size()),
            &bytesRead,
            nullptr);
    DWORD readError = readOk ? ERROR_SUCCESS : GetLastError();
    CloseHandle(file);

    if (!readOk || bytesRead != data.size()) {
        Wh_Log(
            L"[STATE] ReadFile failed/incomplete error=%u read=%u expected=%zu",
            readError,
            bytesRead,
            data.size());
        return false;
    }

    size_t lineStart = 0;
    bool headerSeen = false;
    constexpr size_t kMaxSeparators = 256;

    while (lineStart <= data.size()) {
        size_t lineEnd = data.find('\n', lineStart);
        if (lineEnd == std::string::npos) {
            lineEnd = data.size();
        }

        std::string_view line(
            data.data() + lineStart,
            lineEnd - lineStart);
        if (!line.empty() && line.back() == '\r') {
            line.remove_suffix(1);
        }

        if (!headerSeen) {
            if (line != "v1") {
                Wh_Log(L"[STATE] Unsupported/corrupt separator state header");
                *contentInvalidOut = true;
                return false;
            }
            headerSeen = true;
        } else if (!line.empty()) {
            size_t tab = line.find('\t');
            if (tab == std::string_view::npos ||
                tab == 0 ||
                tab + 1 >= line.size()) {
                Wh_Log(L"[STATE] Malformed separator state row");
                *contentInvalidOut = true;
                return false;
            }

            std::string_view stableIdAscii =
                line.substr(0, tab);
            std::wstring stableId;
            stableId.reserve(stableIdAscii.size());

            bool asciiOnly = true;
            for (unsigned char ch : stableIdAscii) {
                if (ch >= 0x80) {
                    asciiOnly = false;
                    break;
                }
                stableId.push_back(
                    static_cast<wchar_t>(ch));
            }

            int targetIndex = 0;
            if (!asciiOnly ||
                !IsValidStableId(stableId) ||
                !ParseStateInt(
                    line.substr(tab + 1),
                    &targetIndex) ||
                targetIndex < -1) {
                Wh_Log(L"[STATE] Invalid separator state row");
                *contentInvalidOut = true;
                return false;
            }

            if (settingsOut->separators.size() >=
                kMaxSeparators) {
                Wh_Log(
                    L"[STATE] Too many separators in state file");
                *contentInvalidOut = true;
                return false;
            }

            if (std::any_of(
                    settingsOut->separators.begin(),
                    settingsOut->separators.end(),
                    [&stableId](const SeparatorSetting& existing) {
                        return existing.stableId == stableId;
                    })) {
                Wh_Log(
                    L"[STATE] Duplicate stable ID in state file: '%s'",
                    stableId.c_str());
                *contentInvalidOut = true;
                return false;
            }

            int sourceIndex =
                static_cast<int>(
                    settingsOut->separators.size());

            settingsOut->separators.push_back({
                .ordinal = sourceIndex + 1,
                .sourceIndex = sourceIndex,
                .targetIndex = targetIndex,
                .width = width,
                .stableId = stableId,
                .identity = BuildSeparatorIdentity(
                    settingsOut->identifierPrefix,
                    stableId),
            });
        }

        if (lineEnd == data.size()) {
            break;
        }
        lineStart = lineEnd + 1;
    }

    if (!headerSeen) {
        Wh_Log(L"[STATE] Empty/corrupt separator state file");
        *contentInvalidOut = true;
        return false;
    }

    return true;
}

static bool SaveSeparatorStateFile(
    const Settings& settings) {
    std::string serialized = "v1\n";

    for (const auto& separator : settings.separators) {
        if (!IsValidStableId(separator.stableId) ||
            separator.targetIndex < -1) {
            Wh_Log(
                L"[STATE] Refusing to persist invalid separator state");
            return false;
        }

        for (wchar_t ch : separator.stableId) {
            if (ch > 0x7F) {
                Wh_Log(
                    L"[STATE] Refusing to persist non-ASCII stable ID");
                return false;
            }
            serialized.push_back(
                static_cast<char>(ch));
        }

        serialized.push_back('\t');
        serialized +=
            std::to_string(separator.targetIndex);
        serialized.push_back('\n');
    }

    std::wstring temporaryPath =
        g_separatorStatePath + L".tmp";

    HANDLE file =
        CreateFileW(
            temporaryPath.c_str(),
            GENERIC_WRITE,
            0,
            nullptr,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            nullptr);

    if (file == INVALID_HANDLE_VALUE) {
        Wh_Log(
            L"[STATE] CreateFileW('%s') for write failed error=%u",
            temporaryPath.c_str(),
            GetLastError());
        return false;
    }

    DWORD written = 0;
    BOOL writeOk =
        serialized.empty() ||
        WriteFile(
            file,
            serialized.data(),
            static_cast<DWORD>(serialized.size()),
            &written,
            nullptr);
    DWORD writeError =
        writeOk ? ERROR_SUCCESS : GetLastError();

    BOOL flushOk =
        writeOk && FlushFileBuffers(file);
    DWORD flushError =
        flushOk ? ERROR_SUCCESS : GetLastError();

    CloseHandle(file);

    if (!writeOk ||
        written != serialized.size() ||
        !flushOk) {
        Wh_Log(
            L"[STATE] State write failed error=%u flushError=%u written=%u expected=%zu",
            writeError,
            flushError,
            written,
            serialized.size());
        DeleteFileW(temporaryPath.c_str());
        return false;
    }

    if (!MoveFileExW(
            temporaryPath.c_str(),
            g_separatorStatePath.c_str(),
            MOVEFILE_REPLACE_EXISTING |
                MOVEFILE_WRITE_THROUGH)) {
        Wh_Log(
            L"[STATE] Atomic state replace failed error=%u",
            GetLastError());
        DeleteFileW(temporaryPath.c_str());
        return false;
    }

    return true;
}

static double LoadSeparatorWidthSetting() {
    constexpr int kDefaultWidth = 20;
    constexpr int kMinWidth = 1;
    constexpr int kMaxWidth = 1000;

    int configuredWidth =
        Wh_GetIntSetting(L"iconSeparators.width");

    if (configuredWidth == 0) {
        configuredWidth = kDefaultWidth;
    }

    int width =
        std::clamp(
            configuredWidth,
            kMinWidth,
            kMaxWidth);

    if (width != configuredWidth) {
        Wh_Log(
            L"[SETTINGS] Clamped separator width from %d to %d",
            configuredWidth,
            width);
    }

    return static_cast<double>(width);
}

static InteractionMode LoadInteractionModeSetting() {
    std::wstring mode =
        WindhawkUtils::StringSetting::make(
            L"iconSeparators.interaction").get();

    if (_wcsicmp(mode.c_str(), L"middleClick") == 0) {
        return InteractionMode::MiddleClick;
    }

    return InteractionMode::ContextMenu;
}

static bool LoadCustomIconFile(
    const std::wstring& path,
    std::vector<BYTE>* bytesOut,
    unsigned long long* hashOut) {
    if (!bytesOut || !hashOut || path.empty()) {
        return false;
    }

    bytesOut->clear();
    *hashOut = 0;

    HANDLE file = CreateFileW(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        Wh_Log(
            L"[ICON] Couldn't open custom icon '%s' error=%u; using bundled icon",
            path.c_str(),
            GetLastError());
        return false;
    }

    LARGE_INTEGER size = {};
    constexpr LONGLONG kMaximumCustomIconSize = 32LL * 1024 * 1024;
    if (!GetFileSizeEx(file, &size) ||
        size.QuadPart < 6 ||
        size.QuadPart > kMaximumCustomIconSize) {
        Wh_Log(
            L"[ICON] Custom icon '%s' has an invalid size; using bundled icon",
            path.c_str());
        CloseHandle(file);
        return false;
    }

    bytesOut->resize(static_cast<size_t>(size.QuadPart));
    DWORD bytesRead = 0;
    BOOL readOk = ReadFile(
        file,
        bytesOut->data(),
        static_cast<DWORD>(bytesOut->size()),
        &bytesRead,
        nullptr);
    CloseHandle(file);

    if (!readOk || bytesRead != bytesOut->size()) {
        Wh_Log(
            L"[ICON] Couldn't read custom icon '%s'; using bundled icon",
            path.c_str());
        bytesOut->clear();
        return false;
    }

    const auto readLe16 = [bytesOut](size_t offset) -> unsigned int {
        return static_cast<unsigned int>((*bytesOut)[offset]) |
            (static_cast<unsigned int>((*bytesOut)[offset + 1]) << 8);
    };
    const auto readLe32 = [bytesOut](size_t offset) -> unsigned long {
        return static_cast<unsigned long>((*bytesOut)[offset]) |
            (static_cast<unsigned long>((*bytesOut)[offset + 1]) << 8) |
            (static_cast<unsigned long>((*bytesOut)[offset + 2]) << 16) |
            (static_cast<unsigned long>((*bytesOut)[offset + 3]) << 24);
    };

    const unsigned int reserved = readLe16(0);
    const unsigned int type = readLe16(2);
    const unsigned int frameCount = readLe16(4);
    const size_t directorySize =
        6 + static_cast<size_t>(frameCount) * 16;

    bool valid =
        reserved == 0 && type == 1 &&
        frameCount > 0 && frameCount <= 32 &&
        directorySize <= bytesOut->size();

    if (valid) {
        for (unsigned int i = 0; i < frameCount; i++) {
            const size_t entry = 6 + static_cast<size_t>(i) * 16;
            const unsigned int width =
                (*bytesOut)[entry] ? (*bytesOut)[entry] : 256;
            const unsigned int height =
                (*bytesOut)[entry + 1] ? (*bytesOut)[entry + 1] : 256;
            const unsigned long imageSize = readLe32(entry + 8);
            const unsigned long imageOffset = readLe32(entry + 12);

            if (width != height ||
                !imageSize ||
                imageOffset < directorySize ||
                imageOffset > bytesOut->size() ||
                imageSize > bytesOut->size() - imageOffset) {
                valid = false;
                break;
            }
        }
    }

    if (!valid) {
        Wh_Log(
            L"[ICON] Custom icon '%s' isn't a structurally valid ICO; using bundled icon",
            path.c_str());
        bytesOut->clear();
        return false;
    }

    unsigned long long hash = 14695981039346656037ULL;
    for (BYTE byte : *bytesOut) {
        hash ^= byte;
        hash *= 1099511628211ULL;
    }
    *hashOut = hash;
    return true;
}

static IconAppearanceSettings LoadIconAppearanceSettings() {
    IconAppearanceSettings settings;

    int configuredRotation = Wh_GetIntSetting(L"iconSeparators.rotation");

    int rotation = configuredRotation % 360;
    if (rotation < 0) {
        rotation += 360;
    }
    if (rotation != configuredRotation) {
        Wh_Log(
            L"[SETTINGS] Normalized icon rotation from %d to %d degrees",
            configuredRotation,
            rotation);
    }

    int brightness = Wh_GetIntSetting(L"iconSeparators.brightness");
    int alpha = Wh_GetIntSetting(L"iconSeparators.alpha");

    int clampedBrightness = std::clamp(brightness, 0, 255);
    int clampedAlpha = std::clamp(alpha, 0, 255);

    if (clampedBrightness != brightness) {
        Wh_Log(
            L"[SETTINGS] Clamped icon brightness from %d to %d",
            brightness,
            clampedBrightness);
    }
    if (clampedAlpha != alpha) {
        Wh_Log(
            L"[SETTINGS] Clamped icon alpha from %d to %d",
            alpha,
            clampedAlpha);
    }

    settings.rotation = rotation;
    settings.brightness = clampedBrightness;
    settings.alpha = clampedAlpha;
    std::wstring customIconPath =
        WindhawkUtils::StringSetting::make(
            L"iconSeparators.customIcon").get();

    // Paths are often pasted from Explorer/terminal output with surrounding
    // quotes. Strip one matching pair, but leave unmatched quotes untouched so
    // an accidental typo fails visibly instead of silently changing the path.
    if (customIconPath.size() >= 2) {
        const wchar_t first = customIconPath.front();
        const wchar_t last = customIconPath.back();
        if ((first == L'\"' && last == L'\"') ||
            (first == L'\'' && last == L'\'')) {
            customIconPath = customIconPath.substr(
                1,
                customIconPath.size() - 2);
        }
    }

    if (!customIconPath.empty()) {
        LoadCustomIconFile(
            customIconPath,
            &settings.customIconBytes,
            &settings.customIconHash);
    }

    {
        auto mode = WindhawkUtils::StringSetting::make(L"iconSeparators.color");
        std::wstring_view m = mode.get();
        settings.tint = m == L"original" ? 0 : m == L"solid" ? 1 : 2;
    }
    if (settings.tint) {
        auto parse = [](const wchar_t* name, unsigned long fallback) {
            auto s = WindhawkUtils::StringSetting::make(name);
            std::wstring v = s.get();
            if (!v.empty() && v[0] == L'#') {
                v.erase(0, 1);
            }
            if (v.size() == 8) {
                v.erase(0, 2);
            }
            wchar_t* end = nullptr;
            unsigned long c = v.size() == 6 ? wcstoul(v.c_str(), &end, 16) : 0;
            return v.size() == 6 && end && *end == L'\0' ? c : fallback;
        };
        unsigned long c0 = parse(L"iconSeparators.colorStart", 0x89B4FA);
        unsigned long c1 = settings.tint == 2
                               ? parse(L"iconSeparators.colorEnd", 0xCBA6F7)
                               : c0;
        settings.r0 = BYTE(c0 >> 16); settings.g0 = BYTE(c0 >> 8); settings.b0 = BYTE(c0);
        settings.r1 = BYTE(c1 >> 16); settings.g1 = BYTE(c1 >> 8); settings.b1 = BYTE(c1);
        // FNV-1a over the tint so a color change gives a fresh icon file.
        unsigned long long h = 1469598103934665603ULL;
        for (unsigned long long v : {(unsigned long long)settings.tint,
                                     (unsigned long long)c0,
                                     (unsigned long long)c1}) {
            h = (h ^ v) * 1099511628211ULL;
        }
        settings.tintHash = h;
    }

    return settings;
}

static bool IconAppearanceSettingsEqual(
    const IconAppearanceSettings& left,
    const IconAppearanceSettings& right) {
    return left.rotation == right.rotation &&
        left.brightness == right.brightness &&
        left.alpha == right.alpha &&
        left.customIconBytes.empty() == right.customIconBytes.empty() &&
        left.customIconHash == right.customIconHash &&
        left.tint == right.tint &&
        left.tintHash == right.tintHash;
}

static const wchar_t* InteractionModeName(
    InteractionMode mode) {
    return mode == InteractionMode::MiddleClick
               ? L"middleClick"
               : L"contextMenu";
}

static bool IsContextMenuInteractionMode() {
    return g_interactionMode.load(
               std::memory_order_acquire) ==
        InteractionMode::ContextMenu;
}

static bool IsMiddleClickInteractionMode() {
    return g_interactionMode.load(
               std::memory_order_acquire) ==
        InteractionMode::MiddleClick;
}

static InteractionMode ResolveInteractionModeAgainstCapabilities(
    InteractionMode requestedMode) {
    const bool contextAvailable =
        g_contextMenuInteractionAvailable.load(std::memory_order_acquire);
    const bool middleAvailable =
        g_middleClickInteractionAvailable.load(std::memory_order_acquire);

    if (requestedMode == InteractionMode::ContextMenu &&
        !contextAvailable && middleAvailable) {
        return InteractionMode::MiddleClick;
    }

    if (requestedMode == InteractionMode::MiddleClick &&
        !middleAvailable && contextAvailable) {
        return InteractionMode::ContextMenu;
    }

    // If both frontends are unavailable, preserve the user's configured mode.
    // This makes the degraded state explicit in logs without pretending the
    // other equally-unavailable frontend is a meaningful fallback.
    return requestedMode;
}

static void ApplyInteractionModeCapabilityFallback(
    const wchar_t* logCategory) {
    InteractionMode requested =
        g_interactionMode.load(std::memory_order_acquire);
    InteractionMode resolved =
        ResolveInteractionModeAgainstCapabilities(requested);

    if (resolved != requested) {
        g_interactionMode.store(resolved, std::memory_order_release);
        Wh_Log(
            L"[%s] Interaction mode %s unavailable; falling back to %s",
            logCategory,
            InteractionModeName(requested),
            InteractionModeName(resolved));
    }
}

static bool AdoptLegacySeparatorShortcuts(
    Settings* settings) {
    if (!settings) {
        return false;
    }

    const auto shortcutPaths =
        EnumerateSeparatorShortcuts();

    if (shortcutPaths.empty()) {
        return true;
    }

    const std::wstring refreshPulseStableId =
        std::to_wstring(kRefreshPulseOrdinal);

    bool sawUnrecognizedShortcut = false;
    size_t adoptedCount = 0;

    for (const auto& path : shortcutPaths) {
        std::wstring identity =
            GetShortcutIdentity(path);

        auto stableId =
            ExtractStableIdFromSeparatorIdentity(
                identity);
        if (!stableId) {
            sawUnrecognizedShortcut = true;
            Wh_Log(
                L"[STATE] Legacy shortcut identity couldn't be parsed: '%s'",
                identity.c_str());
            continue;
        }

        // A refresh helper can survive an interrupted old backend pass. It is
        // not a user separator and may be cleaned as stale after migration.
        if (*stableId == refreshPulseStableId) {
            continue;
        }

        if (std::any_of(
                settings->separators.begin(),
                settings->separators.end(),
                [&stableId](const SeparatorSetting& separator) {
                    return separator.stableId == *stableId;
                })) {
            continue;
        }

        const int sourceIndex =
            static_cast<int>(
                settings->separators.size());

        settings->separators.push_back({
            .ordinal = sourceIndex + 1,
            .sourceIndex = sourceIndex,
            // The old shortcut proves ownership but not its pin-list index.
            // Keep it unanchored at Windows' native end until the user drags it;
            // the ordinary TryMoveGroup path then records a durable position.
            .targetIndex = -1,
            .width = settings->width,
            .stableId = *stableId,
            // The old/no-generation shortcut is evidence for the durable stable
            // ID only. Desired state immediately uses the current shell generation
            // so this same convergence pass unpins the legacy shortcut and creates
            // the fresh .lnk/AUMID instead of postponing migration to next startup.
            .identity = BuildSeparatorIdentity(
                settings->identifierPrefix,
                *stableId),
        });

        adoptedCount++;
    }

    if (sawUnrecognizedShortcut) {
        // No authoritative state file exists yet. Even a partially successful
        // adoption must not authorize stale cleanup to delete an owned artifact
        // that this migration couldn't identify.
        Wh_Log(
            L"[STATE] Refusing migration while unrecognized legacy "
            L"shortcut artifacts exist");
        return false;
    }

    if (adoptedCount > 0) {
        Wh_Log(
            L"[STATE] Adopted %zu legacy separator shortcut(s) from mod storage",
            adoptedCount);
    }

    return true;
}


static bool MigrateLegacySeparatorState(
    double width,
    Settings* settingsOut) {
    if (!settingsOut) {
        return false;
    }

    Settings migrated;
    migrated.identifierPrefix =
        kSeparatorIdentifierPrefix;
    migrated.width = width;

    auto legacySeeds =
        LoadLegacyIdentityManifest();

    if (!legacySeeds.empty()) {
        // The old manifest was already ordered in the mod's logical separator
        // order. Keep every stable ID and target position, but ignore its old
        // per-row width: p42 has one global width setting.
        for (const auto& seed : legacySeeds) {
            if (!IsValidStableId(seed.stableId) ||
                seed.targetIndex < -1) {
                continue;
            }

            if (std::any_of(
                    migrated.separators.begin(),
                    migrated.separators.end(),
                    [&seed](const SeparatorSetting& existing) {
                        return existing.stableId == seed.stableId;
                    })) {
                continue;
            }

            int sourceIndex =
                static_cast<int>(
                    migrated.separators.size());

            migrated.separators.push_back({
                .ordinal = sourceIndex + 1,
                .sourceIndex = sourceIndex,
                .targetIndex = seed.targetIndex,
                .width = width,
                .stableId = seed.stableId,
                .identity = BuildSeparatorIdentity(
                    migrated.identifierPrefix,
                    seed.stableId),
            });
        }
    } else {
        // Older builds without an identity manifest: import the old visible
        // separator rows once. Numeric IDs preserve the pre-stable-ID shortcut
        // names for the ordinary migration case.
        constexpr int kMaxSeparators = 256;

        for (int i = 0; i < kMaxSeparators; i++) {
            int position =
                Wh_GetIntSetting(
                    L"separators[%d].index",
                    i);

            if (position == 0) {
                break;
            }

            int targetIndex = -1;
            if (position == -1) {
                targetIndex = -1;
            } else if (position >= 1) {
                targetIndex = position - 1;
            } else {
                continue;
            }

            std::wstring stableId =
                std::to_wstring(i + 1);

            migrated.separators.push_back({
                .ordinal = i + 1,
                .sourceIndex = i,
                .targetIndex = targetIndex,
                .width = width,
                .stableId = stableId,
                .identity = BuildSeparatorIdentity(
                    migrated.identifierPrefix,
                    stableId),
            });
        }
    }

    // Published v0.5.38 could have live separator shortcuts even when its
    // default settings row was never explicitly persisted. If the legacy
    // settings sources found nothing, recover those owned shortcuts before
    // creating the new authoritative state file.
    if (migrated.separators.empty() &&
        !AdoptLegacySeparatorShortcuts(
            &migrated)) {
        return false;
    }

    if (!SaveSeparatorStateFile(migrated)) {
        Wh_Log(
            L"[STATE] Failed to create p42 separator state during migration");
        return false;
    }

    Wh_Log(
        L"[STATE] Migrated %zu separator(s) into '%s'",
        migrated.separators.size(),
        g_separatorStatePath.c_str());

    *settingsOut = std::move(migrated);
    return true;
}

static bool LoadSettingsFromStorage(
    Settings* settingsOut,
    SeparatorSetting* refreshPulseOut,
    bool* stateNeedsSaveOut) {
    if (!settingsOut || !refreshPulseOut || !stateNeedsSaveOut) {
        return false;
    }

    *stateNeedsSaveOut = false;

    double width =
        LoadSeparatorWidthSetting();

    bool stateExists = false;
    bool contentInvalid = false;
    Settings settings;

    if (!ReadSeparatorStateFile(
            width,
            &settings,
            &stateExists,
            &contentInvalid)) {
        if (!contentInvalid) {
            return false;
        }

        Settings recovered;
        recovered.identifierPrefix =
            kSeparatorIdentifierPrefix;
        recovered.width = width;

        if (!AdoptLegacySeparatorShortcuts(&recovered)) {
            Wh_Log(
                L"[STATE] State recovery couldn't adopt every owned shortcut");
            return false;
        }

        DWORD attributes =
            GetFileAttributesW(g_separatorStatePath.c_str());
        if (attributes != INVALID_FILE_ATTRIBUTES &&
            !(attributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::wstring backupPath =
                g_separatorStatePath +
                L".invalid-" +
                std::to_wstring(GetTickCount64());

            if (MoveFileExW(
                    g_separatorStatePath.c_str(),
                    backupPath.c_str(),
                    MOVEFILE_WRITE_THROUGH)) {
                Wh_Log(
                    L"[STATE] Moved invalid state file aside as '%s'",
                    backupPath.c_str());
            } else {
                Wh_Log(
                    L"[STATE] Couldn't move invalid state file aside "
                    L"error=%u; recovery will retry persistence in place",
                    GetLastError());
            }
        }

        settings = std::move(recovered);
        stateExists = true;
        *stateNeedsSaveOut = true;

        Wh_Log(
            L"[STATE] Recovered %zu separator(s) from owned shortcuts",
            settings.separators.size());
    }

    if (!stateExists &&
        !MigrateLegacySeparatorState(
            width,
            &settings)) {
        return false;
    }

    *refreshPulseOut = {
        .ordinal = kRefreshPulseOrdinal,
        .sourceIndex = -1,
        .targetIndex = 0,
        .width = width,
        .stableId = std::to_wstring(
            kRefreshPulseOrdinal),
        .identity = BuildSeparatorIdentity(
            settings.identifierPrefix,
            std::to_wstring(
                kRefreshPulseOrdinal)),
    };

    Wh_Log(
        L"[STATE] Loaded %zu separator(s) from mod storage; width=%d",
        settings.separators.size(),
        static_cast<int>(width));

    *settingsOut = std::move(settings);
    return true;
}

static const SeparatorSetting* FindSeparatorByIdentity(
    const Settings& settings,
    std::wstring_view identity) {
    auto it = std::find_if(
        settings.separators.begin(),
        settings.separators.end(),
        [identity](const SeparatorSetting& separator) {
            return separator.identity ==
                std::wstring(identity);
        });

    return it == settings.separators.end()
               ? nullptr
               : &*it;
}

static void AppendStoredSeparatorCandidate(
    std::vector<SeparatorSetting>& stored,
    const SeparatorSetting& candidate,
    const Settings& desiredSettings,
    const SeparatorSetting& refreshPulse) {
    if (candidate.identity.empty() ||
        IsIdentityInSettings(
            desiredSettings,
            candidate.identity) ||
        candidate.identity == refreshPulse.identity) {
        return;
    }

    if (std::any_of(
            stored.begin(),
            stored.end(),
            [&candidate](const SeparatorSetting& existing) {
                return existing.identity == candidate.identity;
            })) {
        return;
    }

    SeparatorSetting copy = candidate;
    copy.ordinal = 0;
    stored.push_back(std::move(copy));
}

static std::vector<SeparatorSetting>
BuildStoredSeparatorSettings(
    const Settings& desiredSettings,
    const SeparatorSetting& refreshPulse,
    const Settings& appliedSettings,
    const Settings* previousDesiredSettings = nullptr,
    const SeparatorSetting* previousRefreshPulse = nullptr,
    const std::vector<SeparatorSetting>* retainedStoredSettings = nullptr) {
    std::vector<SeparatorSetting> stored;

    // Keep identities from earlier transitions until a successful backend
    // pass proves that their backing shortcuts are gone. This also covers a
    // previous backend snapshot that was superseded before it created/pinned
    // all of its files: if one such item appears late, it is still styled and
    // inert rather than briefly becoming an ordinary taskbar button.
    if (retainedStoredSettings) {
        for (const auto& separator : *retainedStoredSettings) {
            AppendStoredSeparatorCandidate(
                stored,
                separator,
                desiredSettings,
                refreshPulse);
        }
    }

    if (previousDesiredSettings) {
        for (const auto& separator :
             previousDesiredSettings->separators) {
            AppendStoredSeparatorCandidate(
                stored,
                separator,
                desiredSettings,
                refreshPulse);
        }
    }

    if (previousRefreshPulse) {
        AppendStoredSeparatorCandidate(
            stored,
            *previousRefreshPulse,
            desiredSettings,
            refreshPulse);
    }

    const double defaultWidth =
        !appliedSettings.separators.empty()
            ? appliedSettings.separators.front().width
            : (!desiredSettings.separators.empty()
                   ? desiredSettings.separators.front().width
                   : 20.0);

    for (const auto& path : EnumerateSeparatorShortcuts()) {
        std::wstring identity =
            GetShortcutIdentity(path);

        if (identity.empty() ||
            IsIdentityInSettings(
                desiredSettings,
                identity) ||
            identity == refreshPulse.identity) {
            continue;
        }

        if (std::any_of(
                stored.begin(),
                stored.end(),
                [&identity](const SeparatorSetting& existing) {
                    return existing.identity == identity;
                })) {
            continue;
        }

        const SeparatorSetting* known =
            FindSeparatorByIdentity(
                appliedSettings,
                identity);

        if (!known && previousDesiredSettings) {
            known = FindSeparatorByIdentity(
                *previousDesiredSettings,
                identity);
        }

        if (known) {
            AppendStoredSeparatorCandidate(
                stored,
                *known,
                desiredSettings,
                refreshPulse);
        } else {
            stored.push_back({
                .ordinal = 0,
                .sourceIndex = -1,
                .targetIndex = 0,
                .width = defaultWidth,
                .stableId = {},
                .identity = std::move(identity),
            });
        }
    }

    return stored;
}

static bool SettingsRequireBackendReconcile(
    const Settings& oldSettings,
    const Settings& newSettings);

static bool SettingsSnapshotsEqual(
    const Settings& a,
    const Settings& b) {
    if (a.identifierPrefix != b.identifierPrefix ||
        a.separators.size() != b.separators.size()) {
        return false;
    }

    for (size_t i = 0; i < a.separators.size(); i++) {
        const auto& left = a.separators[i];
        const auto& right = b.separators[i];

        if (left.ordinal != right.ordinal ||
            left.sourceIndex != right.sourceIndex ||
            left.targetIndex != right.targetIndex ||
            left.width != right.width ||
            left.stableId != right.stableId ||
            left.identity != right.identity) {
            return false;
        }
    }

    return true;
}

static void RefreshStoredSeparatorSettings() {
    Settings desired;
    Settings applied;
    SeparatorSetting refreshPulse;

    {
        std::shared_lock lock(g_settingsMutex);
        desired = g_settings;
        applied = g_appliedSettings;
        refreshPulse = g_refreshPulseSetting;
    }

    auto stored =
        BuildStoredSeparatorSettings(
            desired,
            refreshPulse,
            applied);

    {
        std::unique_lock lock(g_settingsMutex);

        // The desired settings might have changed while the filesystem was
        // enumerated. In that case the settings-change path will rebuild this
        // snapshot again.
        if (SettingsSnapshotsEqual(
                desired,
                g_settings)) {
            g_storedSeparatorSettings =
                std::move(stored);
        }
    }
}

static bool WriteBinaryFile(
    const std::wstring& path,
    const void* data,
    DWORD size) {
    HANDLE file = CreateFileW(
        path.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ,
        nullptr,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    if (file == INVALID_HANDLE_VALUE) {
        Wh_Log(
            L"[FILES] CreateFileW('%s') failed error=%u",
            path.c_str(),
            GetLastError());
        return false;
    }

    DWORD written = 0;
    BOOL ok = WriteFile(
        file,
        data,
        size,
        &written,
        nullptr);

    DWORD error = ok ? ERROR_SUCCESS : GetLastError();
    CloseHandle(file);

    if (!ok || written != size) {
        Wh_Log(
            L"[FILES] WriteFile('%s') failed/incomplete "
            L"error=%u written=%u expected=%u",
            path.c_str(),
            error,
            written,
            size);
        return false;
    }

    return true;
}

static bool WriteBinaryFileAtomically(
    const std::wstring& path,
    const void* data,
    DWORD size) {
    const std::wstring temporaryPath = path + L".tmp";
    if (!WriteBinaryFile(temporaryPath, data, size)) {
        DeleteFileW(temporaryPath.c_str());
        return false;
    }

    if (!MoveFileExW(
            temporaryPath.c_str(),
            path.c_str(),
            MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        Wh_Log(
            L"[FILES] Atomic file replace failed path='%s' error=%u",
            path.c_str(),
            GetLastError());
        DeleteFileW(temporaryPath.c_str());
        return false;
    }

    return true;
}


struct DecodedIconFrame {
    UINT width = 0;
    UINT height = 0;
    UINT stride = 0;
    std::vector<BYTE> pixels;
};

static BYTE ScaleIconChannel(
    BYTE value,
    int requestedMaximum,
    int sourceMaximum) {
    int scaled =
        (static_cast<int>(value) * requestedMaximum + sourceMaximum / 2) /
        sourceMaximum;
    return static_cast<BYTE>(std::clamp(scaled, 0, 255));
}

static bool TransformIconFrame(
    DecodedIconFrame* frame,
    const IconAppearanceSettings& appearance) {
    if (!frame || frame->pixels.empty()) {
        return false;
    }

    if (appearance.tint && frame->width > 0 && frame->height > 0 &&
        frame->stride >= frame->width * 4) {
        const double span =
            std::max(1, static_cast<int>(frame->width + frame->height) - 2);
        for (size_t i = 0; i + 3 < frame->pixels.size(); i += 4) {
            const size_t y = i / frame->stride;
            const size_t x = (i % frame->stride) / 4;
            const double t = std::clamp((x + y) / span, 0.0, 1.0);
            auto mix = [t](BYTE a, BYTE b) {
                return static_cast<BYTE>(std::lround(a + (b - a) * t));
            };
            frame->pixels[i + 0] = mix(appearance.b0, appearance.b1);
            frame->pixels[i + 1] = mix(appearance.g0, appearance.g1);
            frame->pixels[i + 2] = mix(appearance.r0, appearance.r1);
            frame->pixels[i + 3] = static_cast<BYTE>(
                (frame->pixels[i + 3] * appearance.alpha + 127) / 255);
        }
    } else
    for (size_t i = 0; i + 3 < frame->pixels.size(); i += 4) {
        // Preserve the source artwork's anti-aliasing by scaling its existing
        // straight-alpha BGRA channels instead of flattening non-zero pixels.
        for (size_t channel = 0; channel < 3; channel++) {
            frame->pixels[i + channel] = ScaleIconChannel(
                frame->pixels[i + channel],
                appearance.brightness,
                kDefaultIconBrightness);
        }
        frame->pixels[i + 3] = ScaleIconChannel(
            frame->pixels[i + 3],
            appearance.alpha,
            kDefaultIconAlpha);
    }

    if (appearance.rotation == 0) {
        return true;
    }
    if (appearance.rotation < 0 ||
        appearance.rotation >= 360 ||
        frame->width != frame->height ||
        frame->stride != frame->width * 4) {
        return false;
    }

    // Keep the original lossless pixel-copy paths for cardinal rotations.
    // Besides avoiding interpolation blur, this preserves byte-identical output
    // for the four rotations supported by earlier versions of the mod.
    if (appearance.rotation == 90 ||
        appearance.rotation == 180 ||
        appearance.rotation == 270) {
        std::vector<BYTE> rotated(frame->pixels.size());
        for (UINT y = 0; y < frame->height; y++) {
            for (UINT x = 0; x < frame->width; x++) {
                UINT dstX = x;
                UINT dstY = y;

                switch (appearance.rotation) {
                    case 90:
                        dstX = frame->height - 1 - y;
                        dstY = x;
                        break;
                    case 180:
                        dstX = frame->width - 1 - x;
                        dstY = frame->height - 1 - y;
                        break;
                    case 270:
                        dstX = y;
                        dstY = frame->width - 1 - x;
                        break;
                }

                const size_t sourceOffset =
                    static_cast<size_t>(y) * frame->stride + x * 4;
                const size_t destinationOffset =
                    static_cast<size_t>(dstY) * frame->stride + dstX * 4;
                std::copy_n(
                    frame->pixels.data() + sourceOffset,
                    4,
                    rotated.data() + destinationOffset);
            }
        }

        frame->pixels = std::move(rotated);
        return true;
    }

    // Arbitrary rotations use inverse mapping and bilinear interpolation around
    // the frame center. Interpolate colors in premultiplied-alpha space so
    // transparent source pixels can't introduce dark fringes around the stroke.
    constexpr double kPi = 3.1415926535897932384626433832795;
    const double radians =
        static_cast<double>(appearance.rotation) * kPi / 180.0;
    const double cosine = std::cos(radians);
    const double sine = std::sin(radians);
    const double centerX = (static_cast<double>(frame->width) - 1.0) / 2.0;
    const double centerY = (static_cast<double>(frame->height) - 1.0) / 2.0;

    std::vector<BYTE> rotated(frame->pixels.size(), 0);

    for (UINT dstY = 0; dstY < frame->height; dstY++) {
        for (UINT dstX = 0; dstX < frame->width; dstX++) {
            const double relativeX = static_cast<double>(dstX) - centerX;
            const double relativeY = static_cast<double>(dstY) - centerY;

            const double sourceX =
                cosine * relativeX + sine * relativeY + centerX;
            const double sourceY =
                -sine * relativeX + cosine * relativeY + centerY;

            const int x0 = static_cast<int>(std::floor(sourceX));
            const int y0 = static_cast<int>(std::floor(sourceY));
            const double fractionX = sourceX - x0;
            const double fractionY = sourceY - y0;

            double alpha = 0.0;
            double premultiplied[3] = {};

            for (int sampleY = 0; sampleY < 2; sampleY++) {
                const int y = y0 + sampleY;
                if (y < 0 || y >= static_cast<int>(frame->height)) {
                    continue;
                }

                const double weightY =
                    sampleY ? fractionY : 1.0 - fractionY;

                for (int sampleX = 0; sampleX < 2; sampleX++) {
                    const int x = x0 + sampleX;
                    if (x < 0 || x >= static_cast<int>(frame->width)) {
                        continue;
                    }

                    const double weightX =
                        sampleX ? fractionX : 1.0 - fractionX;
                    const double weight = weightX * weightY;
                    const size_t sourceOffset =
                        static_cast<size_t>(y) * frame->stride +
                        static_cast<size_t>(x) * 4;
                    const double sourceAlpha =
                        frame->pixels[sourceOffset + 3];

                    alpha += weight * sourceAlpha;
                    for (size_t channel = 0; channel < 3; channel++) {
                        premultiplied[channel] +=
                            weight *
                            frame->pixels[sourceOffset + channel] *
                            sourceAlpha;
                    }
                }
            }

            const size_t destinationOffset =
                static_cast<size_t>(dstY) * frame->stride + dstX * 4;

            if (alpha > 0.0) {
                for (size_t channel = 0; channel < 3; channel++) {
                    rotated[destinationOffset + channel] =
                        static_cast<BYTE>(std::clamp(
                            static_cast<int>(std::lround(
                                premultiplied[channel] / alpha)),
                            0,
                            255));
                }
                rotated[destinationOffset + 3] =
                    static_cast<BYTE>(std::clamp(
                        static_cast<int>(std::lround(alpha)),
                        0,
                        255));
            }
        }
    }

    frame->pixels = std::move(rotated);
    return true;
}

static void AppendLe16(std::vector<BYTE>* output, WORD value) {
    output->push_back(static_cast<BYTE>(value & 0xFF));
    output->push_back(static_cast<BYTE>((value >> 8) & 0xFF));
}

static void AppendLe32(std::vector<BYTE>* output, DWORD value) {
    output->push_back(static_cast<BYTE>(value & 0xFF));
    output->push_back(static_cast<BYTE>((value >> 8) & 0xFF));
    output->push_back(static_cast<BYTE>((value >> 16) & 0xFF));
    output->push_back(static_cast<BYTE>((value >> 24) & 0xFF));
}

static void WriteLe32(BYTE* data, DWORD value) {
    data[0] = static_cast<BYTE>(value & 0xFF);
    data[1] = static_cast<BYTE>((value >> 8) & 0xFF);
    data[2] = static_cast<BYTE>((value >> 16) & 0xFF);
    data[3] = static_cast<BYTE>((value >> 24) & 0xFF);
}

static bool BuildDibIconFrame(
    const DecodedIconFrame& frame,
    std::vector<BYTE>* output) {
    if (!output || !frame.width || !frame.height ||
        frame.width != frame.height || frame.width > 256 ||
        frame.stride != frame.width * 4 || frame.pixels.empty()) {
        return false;
    }

    const UINT xorSize = frame.stride * frame.height;
    const UINT maskStride = ((frame.width + 31) / 32) * 4;
    const UINT maskSize = maskStride * frame.height;

    output->clear();
    output->reserve(40 + xorSize + maskSize);

    // A 32-bit ICO DIB stores twice the logical height: XOR color bitmap plus
    // the 1-bpp AND transparency mask. Pixel rows are bottom-up BGRA.
    AppendLe32(output, 40);                    // BITMAPINFOHEADER::biSize
    AppendLe32(output, frame.width);           // biWidth
    AppendLe32(output, frame.height * 2);      // biHeight
    AppendLe16(output, 1);                     // biPlanes
    AppendLe16(output, 32);                    // biBitCount
    AppendLe32(output, BI_RGB);                // biCompression
    AppendLe32(output, xorSize);               // biSizeImage
    AppendLe32(output, 0);                     // biXPelsPerMeter
    AppendLe32(output, 0);                     // biYPelsPerMeter
    AppendLe32(output, 0);                     // biClrUsed
    AppendLe32(output, 0);                     // biClrImportant

    for (UINT y = frame.height; y-- > 0;) {
        const BYTE* row =
            frame.pixels.data() +
            static_cast<size_t>(y) * frame.stride;
        output->insert(
            output->end(),
            row,
            row + frame.stride);
    }

    std::vector<BYTE> mask(maskStride, 0);
    for (UINT y = frame.height; y-- > 0;) {
        std::fill(mask.begin(), mask.end(), 0);
        const BYTE* row =
            frame.pixels.data() +
            static_cast<size_t>(y) * frame.stride;
        for (UINT x = 0; x < frame.width; x++) {
            if (row[x * 4 + 3] == 0) {
                mask[x / 8] |= static_cast<BYTE>(0x80 >> (x % 8));
            }
        }
        output->insert(output->end(), mask.begin(), mask.end());
    }

    return true;
}

static bool BuildCustomizedSeparatorIcon(
    const IconAppearanceSettings& appearance,
    std::vector<BYTE>* output) {
    const bool usingCustomIcon = !appearance.customIconBytes.empty();
    const BYTE* sourceBytes = usingCustomIcon
        ? appearance.customIconBytes.data()
        : kSeparatorIcon;
    const size_t sourceSize = usingCustomIcon
        ? appearance.customIconBytes.size()
        : sizeof(kSeparatorIcon);

    if (!output || !sourceBytes || !sourceSize || sourceSize > MAXDWORD) {
        return false;
    }

    winrt::com_ptr<IWICImagingFactory> factory;
    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(IWICImagingFactory),
        factory.put_void());
    if (FAILED(hr)) {
        Wh_Log(
            L"[ICON] WIC factory creation failed hr=0x%08X",
            static_cast<unsigned int>(hr));
        return false;
    }

    winrt::com_ptr<IWICStream> stream;
    hr = factory->CreateStream(stream.put());
    if (SUCCEEDED(hr)) {
        hr = stream->InitializeFromMemory(
            const_cast<BYTE*>(sourceBytes),
            static_cast<DWORD>(sourceSize));
    }

    winrt::com_ptr<IWICBitmapDecoder> decoder;
    if (SUCCEEDED(hr)) {
        hr = factory->CreateDecoderFromStream(
            stream.get(),
            nullptr,
            WICDecodeMetadataCacheOnLoad,
            decoder.put());
    }

    UINT frameCount = 0;
    if (SUCCEEDED(hr)) {
        hr = decoder->GetFrameCount(&frameCount);
    }
    if (FAILED(hr) || !frameCount || frameCount > 32) {
        Wh_Log(
            L"[ICON] Embedded ICO decoder setup failed hr=0x%08X frames=%u",
            static_cast<unsigned int>(hr),
            frameCount);
        return false;
    }

    std::vector<DecodedIconFrame> frames;
    std::vector<std::vector<BYTE>> dibFrames;
    frames.reserve(frameCount);
    dibFrames.reserve(frameCount);

    std::optional<DecodedIconFrame> customLargeFrame;
    std::optional<std::vector<BYTE>> customLargeDib;

    for (UINT i = 0; i < frameCount; i++) {
        winrt::com_ptr<IWICBitmapFrameDecode> sourceFrame;
        hr = decoder->GetFrame(i, sourceFrame.put());

        UINT width = 0;
        UINT height = 0;
        if (SUCCEEDED(hr)) {
            hr = sourceFrame->GetSize(&width, &height);
        }
        if (FAILED(hr) || !width || width > 256 ||
            height != width) {
            Wh_Log(
                L"[ICON] Invalid embedded ICO frame %u hr=0x%08X size=%ux%u",
                i,
                static_cast<unsigned int>(hr),
                width,
                height);
            return false;
        }

        // Taskbar pins don't need a 256px frame when a smaller taskbar-sized
        // frame is available. For custom icons, defer one 256px candidate and
        // keep it only if no smaller frame survives decoding.
        if (!usingCustomIcon && width == 256) {
            continue;
        }

        winrt::com_ptr<IWICFormatConverter> converter;
        hr = factory->CreateFormatConverter(converter.put());
        if (SUCCEEDED(hr)) {
            hr = converter->Initialize(
                sourceFrame.get(),
                GUID_WICPixelFormat32bppBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.0,
                WICBitmapPaletteTypeCustom);
        }
        if (FAILED(hr)) {
            Wh_Log(
                L"[ICON] Failed to convert ICO frame %u hr=0x%08X",
                i,
                static_cast<unsigned int>(hr));
            return false;
        }

        DecodedIconFrame frame;
        frame.width = width;
        frame.height = height;
        frame.stride = width * 4;
        frame.pixels.resize(
            static_cast<size_t>(frame.stride) * height);

        hr = converter->CopyPixels(
            nullptr,
            frame.stride,
            static_cast<UINT>(frame.pixels.size()),
            frame.pixels.data());
        if (FAILED(hr) || !TransformIconFrame(&frame, appearance)) {
            Wh_Log(
                L"[ICON] Failed to read/transform ICO frame %u hr=0x%08X",
                i,
                static_cast<unsigned int>(hr));
            return false;
        }

        std::vector<BYTE> dib;
        if (!BuildDibIconFrame(frame, &dib)) {
            Wh_Log(L"[ICON] Failed to build ICO DIB frame %u", i);
            return false;
        }

        if (usingCustomIcon && width == 256) {
            if (!customLargeFrame) {
                customLargeFrame = std::move(frame);
                customLargeDib = std::move(dib);
            }
            continue;
        }

        frames.push_back(std::move(frame));
        dibFrames.push_back(std::move(dib));
    }

    if (frames.empty() && customLargeFrame && customLargeDib) {
        frames.push_back(std::move(*customLargeFrame));
        dibFrames.push_back(std::move(*customLargeDib));
    }

    constexpr size_t kIcoHeaderSize = 6;
    constexpr size_t kIcoEntrySize = 16;
    const UINT outputFrameCount =
        static_cast<UINT>(frames.size());
    if (!outputFrameCount) {
        return false;
    }
    const size_t directorySize =
        kIcoHeaderSize +
        static_cast<size_t>(outputFrameCount) * kIcoEntrySize;

    output->assign(directorySize, 0);
    (*output)[2] = 1;  // ICONDIR::idType = 1
    (*output)[4] = static_cast<BYTE>(outputFrameCount & 0xFF);
    (*output)[5] = static_cast<BYTE>((outputFrameCount >> 8) & 0xFF);

    size_t nextOffset = directorySize;
    for (UINT i = 0; i < outputFrameCount; i++) {
        const auto& frame = frames[i];
        const auto& dib = dibFrames[i];
        if (dib.size() > MAXDWORD || nextOffset > MAXDWORD ||
            dib.size() > MAXDWORD - nextOffset) {
            output->clear();
            return false;
        }

        BYTE* entry =
            output->data() + kIcoHeaderSize +
            static_cast<size_t>(i) * kIcoEntrySize;
        entry[0] = frame.width == 256 ? 0 : static_cast<BYTE>(frame.width);
        entry[1] = frame.height == 256 ? 0 : static_cast<BYTE>(frame.height);
        entry[4] = 1;   // planes
        entry[6] = 32;  // bit depth
        WriteLe32(entry + 8, static_cast<DWORD>(dib.size()));
        WriteLe32(entry + 12, static_cast<DWORD>(nextOffset));

        output->insert(output->end(), dib.begin(), dib.end());
        nextOffset += dib.size();
    }

    return true;
}

static const std::vector<BYTE>*
GetConfiguredBundledSeparatorIconBytes() {
    // Appearance changes reload the mod. Cache only a successful build so a
    // transient WIC failure can still be retried by the backend.
    static std::vector<BYTE> cachedIconBytes;
    if (!cachedIconBytes.empty()) {
        return &cachedIconBytes;
    }

    std::vector<BYTE> iconBytes;

    if (!g_iconAppearance.customIconBytes.empty()) {
        // Always pass custom files through WIC once, even for the neutral
        // appearance. The lightweight ICO-directory check at settings load is
        // intentionally cheap; decoding here proves every frame we will hand to
        // Explorer is actually readable and canonicalizes it into our known
        // 32-bit DIB representation. Neutral brightness/alpha are exact identity
        // operations, so this doesn't alter the decoded pixels.
        if (!BuildCustomizedSeparatorIcon(
                g_iconAppearance,
                &iconBytes) ||
            iconBytes.empty() ||
            iconBytes.size() > MAXDWORD) {
            Wh_Log(
                L"[ICON] Custom icon couldn't be decoded safely; using bundled icon");

            IconAppearanceSettings bundledAppearance = g_iconAppearance;
            bundledAppearance.customIconBytes.clear();
            bundledAppearance.customIconHash = 0;
            iconBytes.clear();

            if (bundledAppearance.rotation == 0 &&
                bundledAppearance.brightness == kDefaultIconBrightness &&
                bundledAppearance.alpha == kDefaultIconAlpha &&
                !bundledAppearance.tint) {
                iconBytes.assign(
                    std::begin(kSeparatorIcon),
                    std::end(kSeparatorIcon));
            } else if (!BuildCustomizedSeparatorIcon(
                           bundledAppearance,
                           &iconBytes) ||
                       iconBytes.empty() ||
                       iconBytes.size() > MAXDWORD) {
                return nullptr;
            }
        }
    } else if (g_iconAppearance.rotation == 0 &&
               g_iconAppearance.brightness == kDefaultIconBrightness &&
               g_iconAppearance.alpha == kDefaultIconAlpha &&
               !g_iconAppearance.tint) {
        iconBytes.assign(
            std::begin(kSeparatorIcon),
            std::end(kSeparatorIcon));
    } else if (!BuildCustomizedSeparatorIcon(
                   g_iconAppearance,
                   &iconBytes) ||
               iconBytes.empty() ||
               iconBytes.size() > MAXDWORD) {
        return nullptr;
    }

    cachedIconBytes = std::move(iconBytes);
    return &cachedIconBytes;
}

static bool TryBinaryFileEquals(
    const std::wstring& path,
    const BYTE* expected,
    size_t expectedSize,
    bool* matchesOut) {
    if ((!expected && expectedSize != 0) || !matchesOut) {
        return false;
    }

    *matchesOut = false;

    HANDLE file = CreateFileW(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_NOT_FOUND ||
            error == ERROR_PATH_NOT_FOUND) {
            return true;
        }
        return false;
    }

    LARGE_INTEGER fileSize = {};
    if (!GetFileSizeEx(file, &fileSize) ||
        fileSize.QuadPart < 0) {
        CloseHandle(file);
        return false;
    }

    if (static_cast<unsigned long long>(fileSize.QuadPart) !=
        static_cast<unsigned long long>(expectedSize)) {
        CloseHandle(file);
        return true;
    }

    BYTE buffer[64 * 1024];
    size_t offset = 0;
    while (offset < expectedSize) {
        DWORD chunk = static_cast<DWORD>(
            std::min<size_t>(sizeof(buffer), expectedSize - offset));
        DWORD read = 0;
        if (!ReadFile(file, buffer, chunk, &read, nullptr) ||
            read != chunk) {
            CloseHandle(file);
            return false;
        }
        if (memcmp(buffer, expected + offset, chunk) != 0) {
            CloseHandle(file);
            return true;
        }
        offset += chunk;
    }

    CloseHandle(file);
    *matchesOut = true;
    return true;
}

enum class ConfiguredIconDiskState {
    Match,
    Mismatch,
    Error,
};

static ConfiguredIconDiskState GetConfiguredBundledIconDiskState() {
    if (g_bundledIconPath.empty()) {
        return ConfiguredIconDiskState::Error;
    }

    const std::vector<BYTE>* expected =
        GetConfiguredBundledSeparatorIconBytes();
    if (!expected) {
        return ConfiguredIconDiskState::Error;
    }

    bool matches = false;
    if (!TryBinaryFileEquals(
            g_bundledIconPath,
            expected->data(),
            expected->size(),
            &matches)) {
        return ConfiguredIconDiskState::Error;
    }

    return matches
               ? ConfiguredIconDiskState::Match
               : ConfiguredIconDiskState::Mismatch;
}

static bool WriteConfiguredBundledSeparatorIcon() {
    const std::vector<BYTE>* iconBytes =
        GetConfiguredBundledSeparatorIconBytes();
    if (!iconBytes) {
        return false;
    }

    if (!g_iconAppearance.customIconBytes.empty() ||
        g_iconAppearance.rotation != 0 ||
        g_iconAppearance.brightness != kDefaultIconBrightness ||
        g_iconAppearance.alpha != kDefaultIconAlpha) {
        Wh_Log(
            L"[ICON] Prepared %s icon rotation=%d brightness=%d alpha=%d size=%zu",
            g_iconAppearance.customIconBytes.empty() ? L"bundled" : L"custom",
            g_iconAppearance.rotation,
            g_iconAppearance.brightness,
            g_iconAppearance.alpha,
            iconBytes->size());
    }

    return WriteBinaryFileAtomically(
        g_bundledIconPath,
        iconBytes->data(),
        static_cast<DWORD>(iconBytes->size()));
}

static bool LoadSettings() {
    Settings settings;
    SeparatorSetting refreshPulse;
    bool stateNeedsSave = false;

    if (!LoadSettingsFromStorage(
            &settings,
            &refreshPulse,
            &stateNeedsSave)) {
        Wh_Log(L"[STATE] Failed to load separator state");
        return false;
    }

    std::unique_lock lock(g_settingsMutex);
    g_settings = std::move(settings);
    g_appliedSettings = {};
    g_refreshPulseSetting =
        std::move(refreshPulse);
    g_storedSeparatorSettings.clear();
    g_separatorStateDirty = stateNeedsSave;
    return true;
}

static const SeparatorSetting* FindSeparatorByStableId(
    const Settings& settings,
    std::wstring_view stableId) {
    auto it = std::find_if(
        settings.separators.begin(),
        settings.separators.end(),
        [stableId](const SeparatorSetting& separator) {
            return separator.stableId ==
                std::wstring(stableId);
        });

    return it == settings.separators.end()
               ? nullptr
               : &*it;
}

static bool SettingsRequireBackendReconcile(
    const Settings& oldSettings,
    const Settings& newSettings) {
    if (oldSettings.identifierPrefix !=
        newSettings.identifierPrefix) {
        return true;
    }

    if (oldSettings.separators.size() !=
        newSettings.separators.size()) {
        return true;
    }

    for (const auto& oldSeparator :
         oldSettings.separators) {
        const SeparatorSetting* newSeparator =
            FindSeparatorByStableId(
                newSettings,
                oldSeparator.stableId);

        if (!newSeparator ||
            oldSeparator.identity != newSeparator->identity ||
            oldSeparator.targetIndex != newSeparator->targetIndex) {
            return true;
        }
    }

    return false;
}

static bool InitializeStoragePath() {
    wchar_t buffer[32768] = {};

    size_t chars =
        Wh_GetModStoragePath(buffer, ARRAYSIZE(buffer));

    if (!chars || !buffer[0]) {
        Wh_Log(L"[FILES] Wh_GetModStoragePath failed");
        return false;
    }

    g_storagePath = buffer;

    // The API provides a usable mod storage directory, but this is harmless
    // if the directory already exists.
    if (!CreateDirectoryW(g_storagePath.c_str(), nullptr)) {
        DWORD error = GetLastError();
        if (error != ERROR_ALREADY_EXISTS) {
            Wh_Log(
                L"[FILES] CreateDirectoryW('%s') failed error=%u",
                g_storagePath.c_str(),
                error);
            return false;
        }
    }

    g_bundledIconPath.clear();
    g_separatorStatePath =
        JoinPath(
            g_storagePath,
            kSeparatorStateFileName);

    return true;
}

static bool GetShortcutIconLocation(
    const std::wstring& shortcutPath,
    std::wstring* iconPathOut,
    int* iconIndexOut) {
    if (!iconPathOut || !iconIndexOut) {
        return false;
    }

    iconPathOut->clear();
    *iconIndexOut = 0;

    IShellLinkW* shellLink = nullptr;
    HRESULT hr = CoCreateInstance(
        CLSID_ShellLink,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&shellLink));
    if (FAILED(hr) || !shellLink) {
        return false;
    }

    IPersistFile* persistFile = nullptr;
    hr = shellLink->QueryInterface(
        IID_PPV_ARGS(&persistFile));
    if (SUCCEEDED(hr) && persistFile) {
        hr = persistFile->Load(
            shortcutPath.c_str(),
            STGM_READ);
    }

    wchar_t iconPath[32768] = {};
    int iconIndex = 0;
    if (SUCCEEDED(hr)) {
        hr = shellLink->GetIconLocation(
            iconPath,
            ARRAYSIZE(iconPath),
            &iconIndex);
    }

    if (persistFile) {
        persistFile->Release();
    }
    shellLink->Release();

    if (FAILED(hr) || !iconPath[0]) {
        return false;
    }

    *iconPathOut = iconPath;
    *iconIndexOut = iconIndex;
    return true;
}

static bool ShortcutUsesConfiguredBundledIcon(
    const std::wstring& shortcutPath) {
    std::wstring iconPath;
    int iconIndex = 0;
    if (!GetShortcutIconLocation(
            shortcutPath,
            &iconPath,
            &iconIndex)) {
        Wh_Log(
            L"[ICON] Can't read icon location from owned shortcut '%s'; recycling it",
            shortcutPath.c_str());
        return false;
    }

    if (iconIndex != 0 ||
        !PathsEqualOrdinalIgnoreCase(iconPath, g_bundledIconPath)) {
        Wh_Log(
            L"[ICON] Owned shortcut has stale icon location path='%s' index=%d expected='%s'; recycling it",
            iconPath.c_str(),
            iconIndex,
            g_bundledIconPath.c_str());
        return false;
    }

    return true;
}


// -----------------------------------------------------------------------------
// TaskListButton separator width styling.
//
// Separator width is owned through the XAML FrameworkElement::MaxWidth
// property only. No private TaskListButton extent fields or private layout
// entry points are modified.
// -----------------------------------------------------------------------------

using TaskListButton_UpdateVisualStates_t = void(WINAPI*)(void* pThis);
static TaskListButton_UpdateVisualStates_t
    g_taskListButtonUpdateVisualStatesOriginal;

static void QueueBackendWork();
static void FlushPendingSeparatorStateSynchronously();
static void RefreshTrackedSeparatorVisualStates();
using TaskListButton_OnDragCompletedGesture_t =
    void(WINAPI*)(void* pThis);
static TaskListButton_OnDragCompletedGesture_t
    g_taskListButtonOnDragCompletedGestureOriginal;

static void WINAPI TaskListButton_OnDragCompletedGesture_Hook(
    void* pThis) {
    g_taskListButtonOnDragCompletedGestureOriginal(
        pThis);

    if (!g_unloading) {
        bool stateDirty = false;
        {
            std::lock_guard<std::mutex> mutationLock(
                g_settingsMutationMutex);
            stateDirty = g_separatorStateDirty;
        }

        if (stateDirty) {
            // Refresh presentation only after the native drag has completely
            // unwound. This closes an unanchored separator's persistent guide
            // as soon as TryMoveGroup has assigned its first concrete index.
            RefreshTrackedSeparatorVisualStates();

            // The taskbar UI thread only signals work. The backend worker owns
            // the durable write so drag completion never blocks on disk I/O.
            QueueBackendWork();
        }

    }
}

static FrameworkElement GetTaskListButtonElement(void* pThis) {
    FrameworkElement element = nullptr;

    // Same C++/WinRT subobject adjustment used by the existing taskbar mods.
    IUnknown* xamlUnknown =
        reinterpret_cast<IUnknown*>(pThis) + 3;

    HRESULT hr = xamlUnknown->QueryInterface(
        winrt::guid_of<FrameworkElement>(),
        winrt::put_abi(element));

    if (FAILED(hr)) {
        return nullptr;
    }

    return element;
}

static FrameworkElement FindChildByName(
    const FrameworkElement& root,
    std::wstring_view name) {
    if (!root) {
        return nullptr;
    }

    try {
        int childCount =
            winrt::Windows::UI::Xaml::Media::
                VisualTreeHelper::GetChildrenCount(root);

        for (int i = 0; i < childCount; i++) {
            auto childObject =
                winrt::Windows::UI::Xaml::Media::
                    VisualTreeHelper::GetChild(root, i);

            auto child =
                childObject.try_as<FrameworkElement>();

            if (!child) {
                continue;
            }

            auto childName = child.Name();
            std::wstring_view childNameView{
                childName.c_str(),
                childName.size()
            };

            if (childNameView == name) {
                return child;
            }

            if (auto nested =
                    FindChildByName(child, name)) {
                return nested;
            }
        }
    } catch (...) {
        // The visual tree can change while the taskbar is reconciling items.
        // Treat that as a transient miss; UpdateVisualStates will run again.
    }

    return nullptr;
}

static bool ContainsIdentityToken(
    std::wstring_view text,
    std::wstring_view identity) {
    size_t position = text.find(identity);
    while (position != std::wstring_view::npos) {
        const size_t end = position + identity.size();
        const auto isIdentityCharacter = [](wchar_t ch) {
            return std::iswalnum(ch) ||
                   ch == L'_' || ch == L'-' || ch == L'.';
        };

        const bool validStart =
            position == 0 ||
            !isIdentityCharacter(text[position - 1]);
        const bool validEnd =
            end == text.size() ||
            !isIdentityCharacter(text[end]);

        if (validStart && validEnd) {
            return true;
        }

        position = text.find(identity, position + 1);
    }

    return false;
}

static std::optional<std::wstring>
ExtractStableIdFromSeparatorIdentityToken(
    std::wstring_view text) {
    static const std::wstring marker =
        std::wstring(L".") + kSeparatorIdentitySuffix + L".";

    const auto isStableIdCharacter = [](wchar_t ch) {
        return std::iswalnum(ch) || ch == L'-' || ch == L'_';
    };
    const auto isIdentityCharacter = [](wchar_t ch) {
        return std::iswalnum(ch) ||
               ch == L'_' || ch == L'-' || ch == L'.';
    };

    size_t markerPosition = text.find(marker);
    while (markerPosition != std::wstring_view::npos) {
        const size_t stableStart =
            markerPosition + marker.size();
        size_t stableEnd = stableStart;
        while (stableEnd < text.size() &&
               isStableIdCharacter(text[stableEnd])) {
            stableEnd++;
        }

        std::wstring_view stableId =
            text.substr(stableStart, stableEnd - stableStart);
        if (IsValidStableId(stableId)) {
            size_t tokenEnd = stableEnd;
            bool generationValid = true;

            if (stableEnd < text.size() && text[stableEnd] == L'.') {
                const size_t generationStart = stableEnd + 1;
                size_t generationEnd = generationStart;
                while (generationEnd < text.size() &&
                       isIdentityCharacter(text[generationEnd])) {
                    generationEnd++;
                }

                generationValid = IsValidIconGenerationToken(
                    text.substr(
                        generationStart,
                        generationEnd - generationStart));
                tokenEnd = generationEnd;
            }

            if (generationValid &&
                (tokenEnd == text.size() ||
                 !isIdentityCharacter(text[tokenEnd]))) {
                return std::wstring(stableId);
            }
        }

        markerPosition = text.find(
            marker,
            markerPosition + marker.size());
    }

    return std::nullopt;
}

static bool FindSeparatorByAutomationName(
    std::wstring_view name,
    SeparatorSetting* separatorOut = nullptr) {
    if (name.empty()) {
        return false;
    }

    // Almost every TaskListButton is unrelated to this mod. Reject it with a
    // single search before comparing complete identities from the settings or
    // durable storage snapshots.
    static const std::wstring identityMarker =
        std::wstring(L".") + kSeparatorIdentitySuffix + L".";
    if (name.find(identityMarker) == std::wstring_view::npos) {
        return false;
    }

    std::shared_lock lock(g_settingsMutex);

    const auto copyMatch =
        [separatorOut](const SeparatorSetting& separator) {
            if (separatorOut) {
                *separatorOut = separator;
            }
            return true;
        };

    for (const auto& separator : g_settings.separators) {
        if (ContainsIdentityToken(name, separator.identity)) {
            return copyMatch(separator);
        }
    }

    for (const auto& separator : g_storedSeparatorSettings) {
        if (ContainsIdentityToken(name, separator.identity)) {
            return copyMatch(separator);
        }
    }

    if (ContainsIdentityToken(
            name,
            g_refreshPulseSetting.identity)) {
        return copyMatch(g_refreshPulseSetting);
    }

    // During an appearance-generation migration, an old taskbar button can
    // remain alive briefly after its backing .lnk has become stale. Exact shell
    // identity matching above intentionally won't match it. Recover its durable
    // stable ID from either the <=1.0.25 unsuffixed form or a valid generated
    // form, then use the current desired separator only for presentation. Native
    // activation suppression remains stricter and validates the task group's
    // actual AppUserModelID independently.
    if (auto stableId =
            ExtractStableIdFromSeparatorIdentityToken(name)) {
        if (const SeparatorSetting* desired =
                FindSeparatorByStableId(
                    g_settings,
                    *stableId)) {
            return copyMatch(*desired);
        }
    }

    return false;
}

static bool GetSeparatorForElement(
    const FrameworkElement& element,
    SeparatorSetting* separatorOut = nullptr) {
    if (!element) {
        return false;
    }

    winrt::hstring automationName;

    try {
        automationName =
            winrt::Windows::UI::Xaml::Automation::
                AutomationProperties::GetName(element);
    } catch (...) {
        return false;
    }

    std::wstring_view name{
        automationName.c_str(),
        automationName.size()
    };

    return FindSeparatorByAutomationName(
        name,
        separatorOut);
}

static bool GetSeparatorForTaskListButton(
    void* pThis,
    FrameworkElement* elementOut = nullptr,
    SeparatorSetting* separatorOut = nullptr) {
    FrameworkElement element =
        GetTaskListButtonElement(pThis);

    if (!GetSeparatorForElement(
            element,
            separatorOut)) {
        return false;
    }

    if (elementOut) {
        *elementOut = element;
    }

    return true;
}

struct SeparatorVisualState {
    winrt::weak_ref<FrameworkElement> element;
    void* taskListButton;

    bool maxWidthCaptured = false;
    winrt::Windows::Foundation::IInspectable originalMaxWidthLocalValue{
        nullptr};

    winrt::weak_ref<FrameworkElement> iconPanel;
    bool iconPanelAlignmentCaptured = false;
    winrt::Windows::Foundation::IInspectable
        originalIconPanelAlignmentLocalValue{nullptr};
    bool iconPanelToolTipCaptured = false;
    winrt::Windows::Foundation::IInspectable
        originalIconPanelToolTipLocalValue{nullptr};

    winrt::weak_ref<FrameworkElement> icon;
    bool iconAlignmentCaptured = false;
    winrt::Windows::Foundation::IInspectable
        originalIconAlignmentLocalValue{nullptr};

    winrt::weak_ref<FrameworkElement> backgroundElement;
    bool backgroundOpacityCaptured = false;
    winrt::Windows::Foundation::IInspectable
        originalBackgroundOpacityLocalValue{nullptr};

    bool taskListButtonToolTipCaptured = false;
    winrt::Windows::Foundation::IInspectable
        originalTaskListButtonToolTipLocalValue{nullptr};

    // targetIndex == -1 presentation. The Popup is created asynchronously after
    // TaskListButton::UpdateVisualStates has unwound, and is kept open until the
    // first successful native drag assigns a concrete targetIndex.
    winrt::Windows::UI::Xaml::Controls::Primitives::Popup
        anchorHintPopup{nullptr};
    winrt::Windows::Foundation::IAsyncAction
        anchorHintAction{nullptr};
    std::wstring anchorHintIdentity;
    bool anchorHintQueued = false;
};

// XAML references are released explicitly on their UI thread during unload;
// don't release them from TLS destruction after Explorer's XAML teardown.
[[clang::no_destroy]] static thread_local
    std::optional<std::list<SeparatorVisualState>>
        g_separatorVisualStates{std::in_place};
static thread_local bool g_updatingSeparatorVisualStates;

struct SeparatorVisualStateUpdateGuard {
    ~SeparatorVisualStateUpdateGuard() {
        g_updatingSeparatorVisualStates = false;
    }
};

static void CloseSeparatorAnchorHint(
    SeparatorVisualState& state) {
    state.anchorHintQueued = false;
    state.anchorHintIdentity.clear();

    // RunAsync work is cancellable. This matters on mod unload: no queued
    // dispatcher delegate may retain a callback into code after the mod is gone.
    if (state.anchorHintAction) {
        try {
            state.anchorHintAction.Cancel();
        } catch (...) {
        }
        state.anchorHintAction = nullptr;
    }

    if (!state.anchorHintPopup) {
        return;
    }

    try {
        state.anchorHintPopup.IsOpen(false);
    } catch (...) {
    }

    state.anchorHintPopup = nullptr;
}

static void PruneExpiredSeparatorVisualStates() {
    for (auto it = g_separatorVisualStates->begin();
         it != g_separatorVisualStates->end();) {
        if (!it->element.get()) {
            CloseSeparatorAnchorHint(*it);
            it = g_separatorVisualStates->erase(it);
        } else {
            ++it;
        }
    }
}

static auto FindSeparatorVisualState(void* taskListButton) {
    return std::find_if(
        g_separatorVisualStates->begin(),
        g_separatorVisualStates->end(),
        [taskListButton](const SeparatorVisualState& state) {
            return state.taskListButton == taskListButton;
        });
}

static HWND FindTaskbarWindowForCurrentThread() {
    struct EnumContext {
        DWORD processId;
        DWORD threadId;
        HWND window;
    } context{
        GetCurrentProcessId(),
        GetCurrentThreadId(),
        nullptr,
    };

    EnumWindows(
        [](HWND window, LPARAM lParam) -> BOOL {
            auto* context =
                reinterpret_cast<EnumContext*>(lParam);

            DWORD processId = 0;
            DWORD threadId =
                GetWindowThreadProcessId(
                    window,
                    &processId);
            if (!threadId ||
                processId != context->processId ||
                threadId != context->threadId) {
                return TRUE;
            }

            wchar_t className[64] = {};
            if (!GetClassNameW(
                    window,
                    className,
                    ARRAYSIZE(className))) {
                return TRUE;
            }

            if (_wcsicmp(className, L"Shell_TrayWnd") != 0 &&
                _wcsicmp(className, L"Shell_SecondaryTrayWnd") != 0) {
                return TRUE;
            }

            context->window = window;
            return FALSE;
        },
        reinterpret_cast<LPARAM>(&context));

    return context.window;
}

static winrt::Windows::UI::Xaml::Controls::Primitives::PopupPlacementMode
GetSeparatorAnchorHintPlacement() {
    using winrt::Windows::UI::Xaml::Controls::Primitives::PopupPlacementMode;

    HWND taskbarWindow =
        FindTaskbarWindowForCurrentThread();
    RECT taskbarRect = {};
    MONITORINFO monitorInfo = {sizeof(monitorInfo)};

    if (taskbarWindow &&
        GetWindowRect(taskbarWindow, &taskbarRect)) {
        HMONITOR monitor =
            MonitorFromWindow(
                taskbarWindow,
                MONITOR_DEFAULTTONEAREST);
        if (monitor &&
            GetMonitorInfoW(monitor, &monitorInfo)) {
            LONG width =
                taskbarRect.right - taskbarRect.left;
            LONG height =
                taskbarRect.bottom - taskbarRect.top;

            auto distance = [](LONG a, LONG b) -> LONG {
                return a >= b ? a - b : b - a;
            };

            bool vertical = height > width;
            if (vertical) {
                LONG leftDistance =
                    distance(
                        taskbarRect.left,
                        monitorInfo.rcMonitor.left);
                LONG rightDistance =
                    distance(
                        taskbarRect.right,
                        monitorInfo.rcMonitor.right);

                return leftDistance <= rightDistance
                           ? PopupPlacementMode::Right
                           : PopupPlacementMode::Left;
            }

            LONG topDistance =
                distance(
                    taskbarRect.top,
                    monitorInfo.rcMonitor.top);
            LONG bottomDistance =
                distance(
                    taskbarRect.bottom,
                    monitorInfo.rcMonitor.bottom);

            return topDistance <= bottomDistance
                       ? PopupPlacementMode::Bottom
                       : PopupPlacementMode::Top;
        }
    }

    // If taskbar geometry is temporarily unavailable during shell reconstruction,
    // use the normal horizontal taskbar's desktop-side placement as a fallback.
    return PopupPlacementMode::Top;
}

static void ShowQueuedSeparatorAnchorHint(
    void* taskListButton,
    winrt::weak_ref<FrameworkElement> weakElement,
    std::wstring identity) {
    if (g_updatingSeparatorVisualStates) {
        return;
    }
    g_updatingSeparatorVisualStates = true;
    SeparatorVisualStateUpdateGuard updateGuard;

    auto stateIt =
        FindSeparatorVisualState(taskListButton);
    if (stateIt == g_separatorVisualStates->end()) {
        return;
    }

    SeparatorVisualState& state = *stateIt;

    // A recycled TaskListButton can queue a second request before an older one
    // runs. Only the request for the currently tracked identity owns this state.
    if (state.anchorHintIdentity != identity) {
        return;
    }

    state.anchorHintQueued = false;
    state.anchorHintAction = nullptr;

    if (g_unloading ||
        g_internalCleanupInProgress.load(std::memory_order_acquire)) {
        CloseSeparatorAnchorHint(state);
        return;
    }

    FrameworkElement element = weakElement.get();
    FrameworkElement trackedElement = state.element.get();
    if (!element ||
        !trackedElement ||
        winrt::get_abi(element) != winrt::get_abi(trackedElement)) {
        CloseSeparatorAnchorHint(state);
        return;
    }

    SeparatorSetting separator;
    if (!GetSeparatorForElement(
            element,
            &separator) ||
        separator.identity != identity) {
        CloseSeparatorAnchorHint(state);
        return;
    }

    // Recognition intentionally outlives desired state while native removal is
    // converging. The guide belongs only to a separator that is still desired
    // and still intentionally unanchored.
    bool desiredUnanchored = false;
    {
        std::shared_lock lock(g_settingsMutex);
        const SeparatorSetting* desired =
            FindSeparatorByIdentity(
                g_settings,
                identity);
        if (desired && desired->targetIndex < 0) {
            separator = *desired;
            desiredUnanchored = true;
        }
    }
    if (!desiredUnanchored) {
        CloseSeparatorAnchorHint(state);
        return;
    }

    try {
        using namespace winrt::Windows::UI;
        using namespace winrt::Windows::UI::Xaml::Controls;
        using namespace winrt::Windows::UI::Xaml::Controls::Primitives;
        using namespace winrt::Windows::UI::Xaml::Media;

        XamlRoot xamlRoot = element.XamlRoot();
        if (!xamlRoot) {
            return;
        }

        Popup popup;
        popup.XamlRoot(xamlRoot);
        popup.IsLightDismissEnabled(false);
        popup.ShouldConstrainToRootBounds(false);
        popup.IsHitTestVisible(false);

        // XAML Popup hosts can still intercept pointer input at the island/window
        // level even when the child tree is not hit-testable. Put the guide on
        // the desktop side of the taskbar so it doesn't cover the drag target.
        auto placement =
            GetSeparatorAnchorHintPlacement();
        bool horizontalCallout =
            placement == PopupPlacementMode::Left ||
            placement == PopupPlacementMode::Right;

        StackPanel callout;
        callout.Orientation(
            horizontalCallout
                ? Orientation::Horizontal
                : Orientation::Vertical);
        if (horizontalCallout) {
            callout.VerticalAlignment(VerticalAlignment::Center);
        } else {
            callout.HorizontalAlignment(HorizontalAlignment::Center);
        }
        callout.IsHitTestVisible(false);

        bool lightTheme =
            element.ActualTheme() == ElementTheme::Light;

        Color backgroundColor =
            lightTheme
                ? Color{0xF7, 0xF9, 0xF9, 0xF9}
                : Color{0xF7, 0x2B, 0x2B, 0x2B};
        Color foregroundColor =
            lightTheme
                ? Color{0xFF, 0x1B, 0x1B, 0x1B}
                : Color{0xFF, 0xFF, 0xFF, 0xFF};
        Color borderColor =
            lightTheme
                ? Color{0x24, 0x00, 0x00, 0x00}
                : Color{0x28, 0xFF, 0xFF, 0xFF};

        SolidColorBrush backgroundBrush{backgroundColor};
        SolidColorBrush foregroundBrush{foregroundColor};
        SolidColorBrush borderBrush{borderColor};

        Border card;
        card.Background(backgroundBrush);
        card.BorderBrush(borderBrush);
        card.BorderThickness(Thickness{1, 1, 1, 1});
        card.CornerRadius(CornerRadius{8, 8, 8, 8});
        card.Padding(Thickness{12, 7, 12, 7});
        card.IsHitTestVisible(false);

        TextBlock label;
        label.Text(L"Drag to anchor this separator");
        label.FontSize(12);
        label.Foreground(foregroundBrush);
        label.TextWrapping(TextWrapping::NoWrap);
        label.IsHitTestVisible(false);
        card.Child(label);

        // A short stem visually ties the callout to the narrow separator slot.
        Border stem;
        if (horizontalCallout) {
            stem.Width(6);
            stem.Height(2);
            stem.VerticalAlignment(VerticalAlignment::Center);
        } else {
            stem.Width(2);
            stem.Height(6);
            stem.HorizontalAlignment(HorizontalAlignment::Center);
        }
        stem.Background(backgroundBrush);
        stem.IsHitTestVisible(false);

        const bool stemFirst =
            placement == PopupPlacementMode::Right ||
            placement == PopupPlacementMode::Bottom;
        if (stemFirst) {
            callout.Children().Append(stem);
            callout.Children().Append(card);
        } else {
            callout.Children().Append(card);
            callout.Children().Append(stem);
        }
        popup.Child(callout);

        // Windows 11 Popup has a real PlacementTarget. Let XAML own the
        // relationship instead of copying target coordinates into detached
        // HorizontalOffset/VerticalOffset values. This makes the guide follow
        // native drag transforms, virtual-desktop relayouts, animations and
        // container movement automatically.
        popup.PlacementTarget(element);
        popup.DesiredPlacement(placement);

        state.anchorHintPopup = popup;
        state.anchorHintIdentity = identity;

        popup.IsOpen(true);

        Wh_Log(
            L"[NATIVE-ADD] Showing persistent anchor guide identity='%s'",
            identity.c_str());
    } catch (...) {
        state.anchorHintPopup = nullptr;
        Wh_Log(
            L"[NATIVE-ADD] Failed to show persistent anchor guide identity='%s'",
            identity.c_str());
    }
}

static void UpdateSeparatorAnchorHint(
    SeparatorVisualState& state,
    const FrameworkElement& element,
    const SeparatorSetting& separator) {
    if (!element ||
        g_unloading ||
        g_internalCleanupInProgress.load(std::memory_order_acquire) ||
        separator.targetIndex >= 0) {
        CloseSeparatorAnchorHint(state);
        return;
    }

    bool stillDesiredUnanchored = false;
    {
        std::shared_lock lock(g_settingsMutex);
        const SeparatorSetting* desired =
            FindSeparatorByIdentity(
                g_settings,
                separator.identity);
        stillDesiredUnanchored =
            desired && desired->targetIndex < 0;
    }
    if (!stillDesiredUnanchored) {
        CloseSeparatorAnchorHint(state);
        return;
    }

    if ((state.anchorHintPopup || state.anchorHintQueued) &&
        state.anchorHintIdentity != separator.identity) {
        CloseSeparatorAnchorHint(state);
    }

    if (state.anchorHintPopup &&
        state.anchorHintIdentity == separator.identity) {
        try {
            if (state.anchorHintPopup.IsOpen()) {
                // PlacementTarget keeps the Popup attached to the live
                // TaskListButton; no manual coordinate refresh is needed.
                return;
            }
        } catch (...) {
        }

        CloseSeparatorAnchorHint(state);
    }

    if (state.anchorHintQueued &&
        state.anchorHintIdentity == separator.identity) {
        return;
    }

    // Never create/open the Popup from inside UpdateVisualStates itself.
    // Constructing popup presentation while TaskListButton is still
    // materializing can re-enter XAML/layout at a fragile point. Queue one
    // low-priority dispatcher callback and revalidate identity/state there.
    try {
        auto dispatcher = element.Dispatcher();
        if (!dispatcher) {
            return;
        }

        state.anchorHintIdentity = separator.identity;
        state.anchorHintQueued = true;

        auto weakElement =
            winrt::make_weak(element);
        void* taskListButton =
            state.taskListButton;
        std::wstring identity =
            separator.identity;

        state.anchorHintAction =
            dispatcher.RunAsync(
                winrt::Windows::UI::Core::
                    CoreDispatcherPriority::Low,
                winrt::Windows::UI::Core::DispatchedHandler{
                    [taskListButton,
                     weakElement,
                     identity = std::move(identity)]() mutable {
                        ShowQueuedSeparatorAnchorHint(
                            taskListButton,
                            weakElement,
                            std::move(identity));
                    }});
    } catch (...) {
        state.anchorHintQueued = false;
        state.anchorHintIdentity.clear();
    }
}

static void ApplySeparatorMaxWidthOverride(
    SeparatorVisualState& state,
    const FrameworkElement& element,
    const SeparatorSetting& separator) {
    if (!state.maxWidthCaptured) {
        try {
            state.originalMaxWidthLocalValue =
                element.ReadLocalValue(
                    FrameworkElement::MaxWidthProperty());
            state.maxWidthCaptured = true;
        } catch (...) {
            return;
        }
    }

    try {
        if (element.MaxWidth() != separator.width) {
            element.MaxWidth(separator.width);
        }
    } catch (...) {
        // Treat taskbar reconstruction as a transient miss.
    }
}

static void CenterSeparatorIcon(
    SeparatorVisualState& state,
    const FrameworkElement& iconPanel) {
    if (!iconPanel) {
        return;
    }

    try {
        // Once a TaskListButton gets narrower than the normal icon slot, the
        // stock template can effectively left-anchor the icon content. Center
        // both the slot and the actual Icon child instead of using a magic
        // pixel translation, so the correction adapts to icon-size mods/DPI.
        auto trackedIconPanel = state.iconPanel.get();
        if (!trackedIconPanel ||
            winrt::get_abi(trackedIconPanel) != winrt::get_abi(iconPanel)) {
            state.iconPanel = winrt::make_weak(iconPanel);
            state.originalIconPanelAlignmentLocalValue =
                iconPanel.ReadLocalValue(
                    FrameworkElement::HorizontalAlignmentProperty());
            state.iconPanelAlignmentCaptured = true;
            state.originalIconPanelToolTipLocalValue =
                iconPanel.ReadLocalValue(
                    winrt::Windows::UI::Xaml::Controls::
                        ToolTipService::ToolTipProperty());
            state.iconPanelToolTipCaptured = true;
        }

        iconPanel.HorizontalAlignment(
            HorizontalAlignment::Center);

        if (auto icon =
                FindChildByName(
                    iconPanel,
                    L"Icon")) {
            auto trackedIcon = state.icon.get();
            if (!trackedIcon ||
                winrt::get_abi(trackedIcon) != winrt::get_abi(icon)) {
                state.icon = winrt::make_weak(icon);
                state.originalIconAlignmentLocalValue =
                    icon.ReadLocalValue(
                        FrameworkElement::HorizontalAlignmentProperty());
                state.iconAlignmentCaptured = true;
            }

            icon.HorizontalAlignment(
                HorizontalAlignment::Center);
        }
    } catch (...) {
        // Cosmetic only. Leave the stock layout intact on a future template.
    }
}

static void SuppressSeparatorHoverChrome(
    SeparatorVisualState& state,
    const FrameworkElement& taskListButton,
    const FrameworkElement& iconPanel) {
    if (!taskListButton) {
        return;
    }

    try {
        // Taskbar.TaskListLabeledButtonPanel owns the task-button CommonStates.
        // Its Border#BackgroundElement is the rounded hover/press surface.
        // Keep it in the tree (so layout is unaffected) and make only that
        // surface invisible for separator buttons.
        if (iconPanel) {
            if (auto backgroundElement =
                    FindChildByName(
                        iconPanel,
                        L"BackgroundElement")) {
                auto trackedBackground = state.backgroundElement.get();
                if (!trackedBackground ||
                    winrt::get_abi(trackedBackground) !=
                        winrt::get_abi(backgroundElement)) {
                    state.backgroundElement =
                        winrt::make_weak(backgroundElement);
                    state.originalBackgroundOpacityLocalValue =
                        backgroundElement.ReadLocalValue(
                            UIElement::OpacityProperty());
                    state.backgroundOpacityCaptured = true;
                }

                backgroundElement.Opacity(0.0);
            }
        }

        // The persistent anchor guide is a separate Popup. Keep every ordinary
        // taskbar tooltip silent so it never competes with that presentation.
        if (!state.taskListButtonToolTipCaptured) {
            state.originalTaskListButtonToolTipLocalValue =
                taskListButton.ReadLocalValue(
                    winrt::Windows::UI::Xaml::Controls::
                        ToolTipService::ToolTipProperty());
            state.taskListButtonToolTipCaptured = true;
        }

        winrt::Windows::Foundation::IInspectable noToolTip{nullptr};
        winrt::Windows::UI::Xaml::Controls::ToolTipService::
            SetToolTip(
                taskListButton,
                noToolTip);

        if (iconPanel) {
            winrt::Windows::UI::Xaml::Controls::ToolTipService::
                SetToolTip(
                    iconPanel,
                    noToolTip);
        }
    } catch (...) {
        // Cosmetic only. The taskbar model hooks below still suppress click and
        // tooltip text even if a future template changes the XAML subtree.
    }
}


static void RestoreDependencyPropertyLocalValue(
    const DependencyObject& object,
    const DependencyProperty& property,
    const winrt::Windows::Foundation::IInspectable& originalLocalValue) {
    if (originalLocalValue == DependencyProperty::UnsetValue()) {
        object.ClearValue(property);
    } else {
        object.SetValue(property, originalLocalValue);
    }
}

static void RestoreSeparatorVisualState(
    std::list<SeparatorVisualState>::iterator stateIt) {
    SeparatorVisualState& state = *stateIt;

    CloseSeparatorAnchorHint(state);

    auto element = state.element.get();

    // The FrameworkElement weak reference is the lifetime authority for the
    // raw TaskListButton implementation pointer stored alongside it.
    if (!element) {
        g_separatorVisualStates->erase(stateIt);
        return;
    }

    try {
        if (state.maxWidthCaptured) {
            RestoreDependencyPropertyLocalValue(
                element,
                FrameworkElement::MaxWidthProperty(),
                state.originalMaxWidthLocalValue);
        }
    } catch (...) {
    }

    try {
        if (state.taskListButtonToolTipCaptured) {
            RestoreDependencyPropertyLocalValue(
                element,
                winrt::Windows::UI::Xaml::Controls::
                    ToolTipService::ToolTipProperty(),
                state.originalTaskListButtonToolTipLocalValue);
        }
    } catch (...) {
    }

    if (auto iconPanel = state.iconPanel.get()) {
        try {
            if (state.iconPanelAlignmentCaptured) {
                RestoreDependencyPropertyLocalValue(
                    iconPanel,
                    FrameworkElement::HorizontalAlignmentProperty(),
                    state.originalIconPanelAlignmentLocalValue);
            }
            if (state.iconPanelToolTipCaptured) {
                RestoreDependencyPropertyLocalValue(
                    iconPanel,
                    winrt::Windows::UI::Xaml::Controls::
                        ToolTipService::ToolTipProperty(),
                    state.originalIconPanelToolTipLocalValue);
            }
        } catch (...) {
        }
    }

    if (auto icon = state.icon.get()) {
        try {
            if (state.iconAlignmentCaptured) {
                RestoreDependencyPropertyLocalValue(
                    icon,
                    FrameworkElement::HorizontalAlignmentProperty(),
                    state.originalIconAlignmentLocalValue);
            }
        } catch (...) {
        }
    }

    if (auto backgroundElement = state.backgroundElement.get()) {
        try {
            if (state.backgroundOpacityCaptured) {
                RestoreDependencyPropertyLocalValue(
                    backgroundElement,
                    UIElement::OpacityProperty(),
                    state.originalBackgroundOpacityLocalValue);
            }
        } catch (...) {
        }
    }

    g_separatorVisualStates->erase(stateIt);
}

using RunFromWindowThreadProc = void(WINAPI*)(void* parameter);

struct RunFromWindowThreadParameters {
    RunFromWindowThreadProc procedure;
    void* parameter;
    bool executed;
};

static UINT GetRunFromWindowThreadMessage() {
    static const UINT message = RegisterWindowMessageW(
        L"Windhawk_RunFromWindowThread_" WH_MOD_ID);
    return message;
}

static LRESULT CALLBACK RunFromWindowThreadHook(
    int code,
    WPARAM wParam,
    LPARAM lParam) {
    if (code == HC_ACTION) {
        const auto* windowMessage =
            reinterpret_cast<const CWPSTRUCT*>(lParam);
        if (windowMessage->message == GetRunFromWindowThreadMessage() &&
            windowMessage->lParam) {
            auto* parameters =
                reinterpret_cast<RunFromWindowThreadParameters*>(
                    windowMessage->lParam);
            if (!parameters->executed) {
                parameters->executed = true;
                parameters->procedure(parameters->parameter);
            }
        }
    }

    return CallNextHookEx(nullptr, code, wParam, lParam);
}

static bool RunFromWindowThread(
    HWND window,
    RunFromWindowThreadProc procedure,
    void* parameter) {
    DWORD threadId = GetWindowThreadProcessId(window, nullptr);
    UINT message = GetRunFromWindowThreadMessage();
    if (!threadId || !message) {
        return false;
    }

    if (threadId == GetCurrentThreadId()) {
        procedure(parameter);
        return true;
    }

    HHOOK hook = SetWindowsHookExW(
        WH_CALLWNDPROC,
        RunFromWindowThreadHook,
        nullptr,
        threadId);
    if (!hook) {
        return false;
    }

    RunFromWindowThreadParameters parameters = {
        procedure,
        parameter,
        false,
    };
    // Keep the stack-backed parameter alive until the target thread has
    // finished processing the hook callback. UnhookWindowsHookEx doesn't wait
    // for a callback that was already entered.
    SendMessageW(
        window,
        message,
        0,
        reinterpret_cast<LPARAM>(&parameters));
    UnhookWindowsHookEx(hook);
    return parameters.executed;
}

static void RevokeTaskbarUiCallbacksOnCurrentThread();

static void WINAPI RestoreSeparatorVisualStatesOnCurrentThread(void*) {
    // XAML menus/items can outlive the stack frame that created them. Revoke
    // every callback into this module on the owning taskbar UI thread before
    // Windhawk is allowed to unload our code.
    RevokeTaskbarUiCallbacksOnCurrentThread();

    g_updatingSeparatorVisualStates = true;
    SeparatorVisualStateUpdateGuard updateGuard;
    PruneExpiredSeparatorVisualStates();

    while (!g_separatorVisualStates->empty()) {
        RestoreSeparatorVisualState(g_separatorVisualStates->begin());
    }
}

static void RestoreTrackedSeparatorVisualStates() {
    struct EnumContext {
        std::vector<DWORD> processedThreadIds;
    } context;

    EnumWindows(
        [](HWND window, LPARAM lParam) -> BOOL {
            DWORD processId = 0;
            DWORD threadId =
                GetWindowThreadProcessId(window, &processId);
            if (!threadId || processId != GetCurrentProcessId()) {
                return TRUE;
            }

            wchar_t className[64] = {};
            if (!GetClassNameW(
                    window,
                    className,
                    ARRAYSIZE(className)) ||
                (_wcsicmp(className, L"Shell_TrayWnd") != 0 &&
                 _wcsicmp(className, L"Shell_SecondaryTrayWnd") != 0)) {
                return TRUE;
            }

            auto* context = reinterpret_cast<EnumContext*>(lParam);
            if (std::find(
                    context->processedThreadIds.begin(),
                    context->processedThreadIds.end(),
                    threadId) != context->processedThreadIds.end()) {
                return TRUE;
            }

            context->processedThreadIds.push_back(threadId);
            if (!RunFromWindowThread(
                    window,
                    RestoreSeparatorVisualStatesOnCurrentThread,
                    nullptr)) {
                Wh_Log(
                    L"[UNINIT] Failed to restore taskbar visuals on thread %u",
                    threadId);
            }

            return TRUE;
        },
        reinterpret_cast<LPARAM>(&context));
}

static void WINAPI RefreshSeparatorVisualStatesOnCurrentThread(void*) {
    g_updatingSeparatorVisualStates = true;
    SeparatorVisualStateUpdateGuard updateGuard;
    PruneExpiredSeparatorVisualStates();

    for (auto it = g_separatorVisualStates->begin();
         it != g_separatorVisualStates->end();) {
        auto current = it++;

        SeparatorVisualState& state = *current;
        auto element = state.element.get();

        SeparatorSetting separator;
        if (!element ||
            g_unloading ||
            !GetSeparatorForElement(
                element,
                &separator)) {
            RestoreSeparatorVisualState(current);
            continue;
        }

        ApplySeparatorMaxWidthOverride(
            state,
            element,
            separator);

        FrameworkElement iconPanel =
            FindChildByName(element, L"IconPanel");
        CenterSeparatorIcon(state, iconPanel);
        SuppressSeparatorHoverChrome(
            state,
            element,
            iconPanel);
        UpdateSeparatorAnchorHint(
            state,
            element,
            separator);
        }
}

static void RefreshTrackedSeparatorVisualStates() {
    struct EnumContext {
        std::vector<DWORD> processedThreadIds;
    } context;

    EnumWindows(
        [](HWND window, LPARAM lParam) -> BOOL {
            DWORD processId = 0;
            DWORD threadId =
                GetWindowThreadProcessId(window, &processId);
            if (!threadId || processId != GetCurrentProcessId()) {
                return TRUE;
            }

            wchar_t className[64] = {};
            if (!GetClassNameW(
                    window,
                    className,
                    ARRAYSIZE(className)) ||
                (_wcsicmp(className, L"Shell_TrayWnd") != 0 &&
                 _wcsicmp(className, L"Shell_SecondaryTrayWnd") != 0)) {
                return TRUE;
            }

            auto* context =
                reinterpret_cast<EnumContext*>(lParam);
            if (std::find(
                    context->processedThreadIds.begin(),
                    context->processedThreadIds.end(),
                    threadId) !=
                context->processedThreadIds.end()) {
                return TRUE;
            }

            context->processedThreadIds.push_back(threadId);

            if (!RunFromWindowThread(
                    window,
                    RefreshSeparatorVisualStatesOnCurrentThread,
                    nullptr)) {
                Wh_Log(
                    L"[SETTINGS] Failed to refresh taskbar visuals on thread %u",
                    threadId);
            }

            return TRUE;
        },
        reinterpret_cast<LPARAM>(&context));
}

// Native empty-taskbar context menu frontend.
//
// This follows the same Taskbar.View menu construction path used by
// Taskbar Restart Explorer: mark
// the ShowTaskbarSettingsContextMenu build scope, intercept the first
// IVector<MenuFlyoutItemBase>::Append, and add one native MenuFlyoutItem.
static void RequestBackendReconcile();
static void AddSeparatorFromUserAction();

static constexpr wchar_t kAddSeparatorMenuText[] = L"Add separator";
static constexpr wchar_t kAddSeparatorMenuName[] = L"WindhawkAddSeparatorItem";
static constexpr wchar_t kAddSeparatorMenuDividerName[] =
    L"WindhawkAddSeparatorDivider";

static thread_local int g_taskbarSettingsMenuDepth = 0;
static thread_local bool g_taskbarSettingsMenuInjected = false;

struct AddMenuCallbackRegistration {
    winrt::weak_ref<winrt::Windows::UI::Xaml::Controls::MenuFlyoutItem> item;
    winrt::event_token clickToken{};
};

struct SeparatorMenuCallbackRegistration {
    winrt::weak_ref<winrt::Windows::UI::Xaml::Controls::MenuFlyout> menu;
    winrt::weak_ref<winrt::Windows::UI::Xaml::Controls::MenuFlyoutItem> item;
    winrt::event_token clickToken{};
    winrt::event_token closedToken{};
};

// XAML objects are apartment-affine. Keep only weak references and their event
// tokens on the UI thread which registered them. Expired entries are cheap to
// prune; live entries are explicitly revoked during Wh_ModBeforeUninit.
static thread_local std::vector<AddMenuCallbackRegistration>
    g_addMenuCallbackRegistrations;
static thread_local std::vector<SeparatorMenuCallbackRegistration>
    g_separatorMenuCallbackRegistrations;

static void PruneExpiredTaskbarUiCallbackRegistrations() {
    std::erase_if(
        g_addMenuCallbackRegistrations,
        [](const AddMenuCallbackRegistration& registration) {
            try {
                return !registration.item.get();
            } catch (...) {
                return true;
            }
        });

    std::erase_if(
        g_separatorMenuCallbackRegistrations,
        [](const SeparatorMenuCallbackRegistration& registration) {
            try {
                return !registration.menu.get();
            } catch (...) {
                return true;
            }
        });
}

static bool IsNamedMenuItem(
    winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase const& item,
    const wchar_t* name) {
    try {
        if (auto element = item.try_as<FrameworkElement>()) {
            return std::wstring_view(element.Name().c_str()) == name;
        }
    } catch (...) {
    }
    return false;
}

static bool IsMenuSeparator(
    winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase const& item) {
    try {
        return !!item.try_as<
            winrt::Windows::UI::Xaml::Controls::MenuFlyoutSeparator>();
    } catch (...) {
        return false;
    }
}

static void OnAddSeparatorMenuClick(
    winrt::Windows::Foundation::IInspectable const&,
    RoutedEventArgs const&) {
    if (IsContextMenuInteractionMode()) {
        AddSeparatorFromUserAction();
    }
}

using MenuFlyoutItemBaseVector_Append_t =
    void(__cdecl*)(
        void* pThis,
        winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase const& item);
static MenuFlyoutItemBaseVector_Append_t
    g_menuFlyoutItemBaseVectorAppendOriginal;

static void AppendAddSeparatorMenuItems(void* vectorThis) {
    using namespace winrt::Windows::UI::Xaml::Controls;

    MenuFlyoutItem item;
    item.Name(kAddSeparatorMenuName);
    item.Tag(winrt::box_value(winrt::hstring{kAddSeparatorMenuName}));
    item.Text(kAddSeparatorMenuText);

    FontIcon icon;
    icon.FontFamily(
        winrt::Windows::UI::Xaml::Media::FontFamily(
            L"Segoe Fluent Icons"));
    icon.Glyph(L"\xE710");
    icon.FontSize(16);
    item.Icon(icon);

    PruneExpiredTaskbarUiCallbackRegistrations();
    winrt::event_token clickToken =
        item.Click(RoutedEventHandler{&OnAddSeparatorMenuClick});
    g_addMenuCallbackRegistrations.push_back({
        .item = winrt::make_weak(item),
        .clickToken = clickToken,
    });

    MenuFlyoutSeparator divider;
    divider.Name(kAddSeparatorMenuDividerName);
    divider.Tag(
        winrt::box_value(
            winrt::hstring{kAddSeparatorMenuDividerName}));

    g_menuFlyoutItemBaseVectorAppendOriginal(vectorThis, item);
    g_menuFlyoutItemBaseVectorAppendOriginal(vectorThis, divider);

    g_taskbarSettingsMenuInjected = true;
    Wh_Log(L"[NATIVE-ADD] Injected Add separator into taskbar context menu");
}

static void __cdecl MenuFlyoutItemBaseVector_Append_Hook(
    void* pThis,
    winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase const& item) {
    if (!g_unloading &&
        IsContextMenuInteractionMode() &&
        g_taskbarSettingsMenuDepth > 0 &&
        !g_taskbarSettingsMenuInjected) {
        try {
            if (!IsMenuSeparator(item) &&
                !IsNamedMenuItem(item, kAddSeparatorMenuName) &&
                !IsNamedMenuItem(item, kAddSeparatorMenuDividerName)) {
                AppendAddSeparatorMenuItems(pThis);
            }
        } catch (...) {
            Wh_Log(L"[NATIVE-ADD] Menu append inspection failed; skipping injection");
        }
    }

    g_menuFlyoutItemBaseVectorAppendOriginal(pThis, item);
}

struct ScopedTaskbarSettingsMenuBuild {
    bool outer = false;

    ScopedTaskbarSettingsMenuBuild() {
        outer = g_taskbarSettingsMenuDepth++ == 0;
        if (outer) {
            g_taskbarSettingsMenuInjected = false;
        }
    }

    ~ScopedTaskbarSettingsMenuBuild() {
        if (outer && !g_taskbarSettingsMenuInjected && !g_unloading) {
            Wh_Log(L"[NATIVE-ADD] No taskbar menu append observed; injection skipped");
        }
        g_taskbarSettingsMenuDepth--;
    }
};

using ContextMenus_ShowTaskbarSettingsContextMenu_t =
    void(__cdecl*)(
        FrameworkElement const& target,
        void* taskbarSettings,
        winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const& args,
        unsigned long long options);
static ContextMenus_ShowTaskbarSettingsContextMenu_t
    g_contextMenusShowTaskbarSettingsContextMenuOriginal;

static void __cdecl ContextMenus_ShowTaskbarSettingsContextMenu_Hook(
    FrameworkElement const& target,
    void* taskbarSettings,
    winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const& args,
    unsigned long long options) {
    if (!IsContextMenuInteractionMode()) {
        g_contextMenusShowTaskbarSettingsContextMenuOriginal(
            target,
            taskbarSettings,
            args,
            options);
        return;
    }

    ScopedTaskbarSettingsMenuBuild scopedBuild;
    g_contextMenusShowTaskbarSettingsContextMenuOriginal(
        target,
        taskbarSettings,
        args,
        options);
}

// Modern per-item taskbar context-menu paths.
//
// Different Windows 11 builds route the request through slightly different
// Taskbar.View entry points, so retain all three proven hooks. Every route feeds
// the same tiny handler: identify our separator, suppress the stock JumpView,
// and show a one-item explorer-hosted XAML MenuFlyout. The first route that
// reaches the handler opens the flyout; the remaining callbacks for the same
// request only suppress their native path.
using TaskListButton_OnContextRequested_t =
    void(WINAPI*)(
        void* pThis,
        winrt::Windows::UI::Xaml::UIElement const& sender,
        winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const& args);

static TaskListButton_OnContextRequested_t
    g_taskListButtonOnContextRequestedOriginal;

using TaskListButtonHandlers_HandleContextRequested_t =
    void(WINAPI*)(
        winrt::Windows::UI::Xaml::UIElement const& sender,
        winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const& args);

static TaskListButtonHandlers_HandleContextRequested_t
    g_taskListButtonHandlersHandleContextRequestedOriginal;

using TaskbarResources_OnTaskListButtonContextRequested_t =
    void(WINAPI*)(
        void* pThis,
        winrt::Windows::UI::Xaml::UIElement const& sender,
        winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const& args);

static TaskbarResources_OnTaskListButtonContextRequested_t
    g_taskbarResourcesOnTaskListButtonContextRequestedOriginal;

static std::atomic<bool> g_separatorContextMenuOpen = false;

static void RemoveSeparatorByIdentity(
    std::wstring identity);

static void ReleaseSeparatorMenuRegistration(
    const winrt::Windows::Foundation::IInspectable& sender) {
    try {
        auto senderMenu =
            sender.try_as<
                winrt::Windows::UI::Xaml::Controls::MenuFlyout>();
        if (!senderMenu) {
            return;
        }

        void* senderAbi = winrt::get_abi(senderMenu);
        for (auto it = g_separatorMenuCallbackRegistrations.begin();
             it != g_separatorMenuCallbackRegistrations.end();
             ++it) {
            auto menu = it->menu.get();
            if (!menu || winrt::get_abi(menu) != senderAbi) {
                continue;
            }

            if (auto item = it->item.get()) {
                try {
                    item.Click(it->clickToken);
                } catch (...) {
                }
            }

            // It is legal to remove an event handler while that event is being
            // dispatched. Doing so prevents a closed flyout retained by XAML
            // from keeping a callback into this module until object destruction.
            try {
                menu.Closed(it->closedToken);
            } catch (...) {
            }

            g_separatorMenuCallbackRegistrations.erase(it);
            return;
        }
    } catch (...) {
    }
}

static void OnSeparatorContextMenuClosed(
    winrt::Windows::Foundation::IInspectable const& sender,
    winrt::Windows::Foundation::IInspectable const&) {
    g_separatorContextMenuOpen = false;
    ReleaseSeparatorMenuRegistration(sender);
}

static void OnSeparatorUnpinMenuClick(
    winrt::Windows::Foundation::IInspectable const& sender,
    RoutedEventArgs const&) {
    // The target TaskListButton may disappear before FlyoutBase::Closed is
    // delivered. Release the de-duplication gate at command dispatch too.
    g_separatorContextMenuOpen = false;

    if (g_unloading ||
        g_internalCleanupInProgress.load()) {
        return;
    }

    try {
        auto item =
            sender.try_as<
                winrt::Windows::UI::Xaml::Controls::MenuFlyoutItem>();
        if (!item) {
            return;
        }

        auto tag = item.Tag();
        if (!tag) {
            return;
        }

        winrt::hstring identity =
            winrt::unbox_value<winrt::hstring>(tag);
        if (identity.empty()) {
            return;
        }

        RemoveSeparatorByIdentity(
            std::wstring(identity.c_str(), identity.size()));
    } catch (...) {
        Wh_Log(L"[CTX] Separator Unpin callback failed");
    }
}

static void ShowSeparatorContextMenu(
    const FrameworkElement& target,
    const SeparatorSetting& separator) {
    if (!target ||
        separator.identity.empty() ||
        g_unloading) {
        return;
    }

    bool expected = false;
    if (!g_separatorContextMenuOpen.compare_exchange_strong(
            expected,
            true)) {
        return;
    }

    try {
        using namespace winrt::Windows::UI::Xaml::Controls;
        using namespace winrt::Windows::UI::Xaml::Controls::Primitives;

        MenuFlyout menu;
        menu.Placement(FlyoutPlacementMode::Top);

        MenuFlyoutItem unpin;
        unpin.Text(L"Remove separator");
        unpin.Tag(
            winrt::box_value(
                winrt::hstring{separator.identity}));

        FontIcon icon;
        icon.FontFamily(
            winrt::Windows::UI::Xaml::Media::FontFamily(
                L"Segoe Fluent Icons"));
        // Segoe Fluent Icons: Remove (minus sign).
        icon.Glyph(L"\xE738");
        icon.FontSize(16);
        unpin.Icon(icon);

        PruneExpiredTaskbarUiCallbackRegistrations();
        winrt::event_token clickToken =
            unpin.Click(
                RoutedEventHandler{
                    &OnSeparatorUnpinMenuClick});

        menu.Items().Append(unpin);
        winrt::event_token closedToken =
            menu.Closed(
                winrt::Windows::Foundation::
                    EventHandler<winrt::Windows::Foundation::IInspectable>{
                        &OnSeparatorContextMenuClosed});

        g_separatorMenuCallbackRegistrations.push_back({
            .menu = winrt::make_weak(menu),
            .item = winrt::make_weak(unpin),
            .clickToken = clickToken,
            .closedToken = closedToken,
        });

        ::ThemeWholeMenu(menu);
        menu.ShowAt(target);
        Wh_Log(
            L"[CTX] Opened separator context menu identity='%s'",
            separator.identity.c_str());
    } catch (...) {
        g_separatorContextMenuOpen = false;
        Wh_Log(L"[CTX] Failed to show separator context menu");
    }
}

static void RevokeTaskbarUiCallbacksOnCurrentThread() {
    for (const auto& registration : g_addMenuCallbackRegistrations) {
        try {
            if (auto item = registration.item.get()) {
                item.Click(registration.clickToken);
            }
        } catch (...) {
        }
    }
    g_addMenuCallbackRegistrations.clear();

    // Revoke before hiding so Hide() cannot dispatch Closed back into this mod.
    for (const auto& registration : g_separatorMenuCallbackRegistrations) {
        try {
            if (auto item = registration.item.get()) {
                item.Click(registration.clickToken);
            }
        } catch (...) {
        }

        try {
            if (auto menu = registration.menu.get()) {
                menu.Closed(registration.closedToken);
                menu.Hide();
            }
        } catch (...) {
        }
    }
    g_separatorMenuCallbackRegistrations.clear();
    g_separatorContextMenuOpen.store(false, std::memory_order_release);
}

static bool TryHandleSeparatorContextRequest(
    const FrameworkElement& element,
    const SeparatorSetting* knownSeparator = nullptr) {
    if (g_unloading || !element) {
        return false;
    }

    SeparatorSetting separator;
    if (knownSeparator) {
        separator = *knownSeparator;
    } else if (!GetSeparatorForElement(
                   element,
                   &separator)) {
        return false;
    }

    if (IsContextMenuInteractionMode()) {
        ShowSeparatorContextMenu(
            element,
            separator);
    }

    // In middle-click mode the separator right-click is still consumed. Letting
    // the stock JumpView expose an ordinary Unpin command would desynchronize
    // Windows' pin list from our mod-owned state.
    return true;
}

static void WINAPI TaskListButton_OnContextRequested_Hook(
    void* pThis,
    winrt::Windows::UI::Xaml::UIElement const& sender,
    winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const& args) {
    FrameworkElement element = nullptr;
    SeparatorSetting separator;

    if (!g_unloading &&
        GetSeparatorForTaskListButton(
            pThis,
            &element,
            &separator)) {
        TryHandleSeparatorContextRequest(
            element,
            &separator);
        return;
    }

    g_taskListButtonOnContextRequestedOriginal(
        pThis,
        sender,
        args);
}

static void WINAPI TaskListButtonHandlers_HandleContextRequested_Hook(
    winrt::Windows::UI::Xaml::UIElement const& sender,
    winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const& args) {
    auto element = sender.try_as<FrameworkElement>();
    if (TryHandleSeparatorContextRequest(element)) {
        return;
    }

    g_taskListButtonHandlersHandleContextRequestedOriginal(
        sender,
        args);
}

static void WINAPI TaskbarResources_OnTaskListButtonContextRequested_Hook(
    void* pThis,
    winrt::Windows::UI::Xaml::UIElement const& sender,
    winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const& args) {
    auto element = sender.try_as<FrameworkElement>();
    if (TryHandleSeparatorContextRequest(element)) {
        return;
    }

    g_taskbarResourcesOnTaskListButtonContextRequestedOriginal(
        pThis,
        sender,
        args);
}

using TaskbarController_OnPointerPressedHandler_t =
    void(WINAPI*)(
        void* pThis,
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& args);
static TaskbarController_OnPointerPressedHandler_t
    g_taskbarControllerOnPointerPressedHandlerOriginal;

static std::wstring GetRuntimeClassName(
    const DependencyObject& object) {
    if (!object) {
        return {};
    }

    try {
        winrt::hstring className =
            winrt::get_class_name(object);
        return std::wstring(
            className.c_str(),
            className.size());
    } catch (...) {
        return {};
    }
}

static bool IsTaskbarBackgroundClass(
    std::wstring_view className) {
    return className == L"Taskbar.TaskbarBackground";
}

static bool IsTaskbarFrameClass(
    std::wstring_view className) {
    return className == L"Taskbar.TaskbarFrame";
}

static bool IsSystemTrayTaskbarElement(
    std::wstring_view className) {
    return className.starts_with(L"SystemTray.");
}

static bool IsButtonBaseElement(
    const DependencyObject& object) {
    if (!object) {
        return false;
    }

    try {
        return !!object.try_as<
            winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase>();
    } catch (...) {
        return false;
    }
}

static bool TryHandleMiddleClickInteraction(
    const winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs& args) {
    if (!IsMiddleClickInteractionMode() ||
        g_unloading ||
        g_internalCleanupInProgress.load(std::memory_order_acquire)) {
        return false;
    }

    try {
        auto point = args.GetCurrentPoint(nullptr);
        if (!point ||
            !point.Properties().IsMiddleButtonPressed()) {
            return false;
        }

        DependencyObject current =
            args.OriginalSource().try_as<DependencyObject>();
        bool reachedTaskbarFrame = false;
        bool sawRootGrid = false;
        bool sawClickableControl = false;

        while (current) {
            std::wstring className =
                GetRuntimeClassName(current);

            if (className == L"Taskbar.TaskListButton") {
                if (auto element = current.try_as<FrameworkElement>()) {
                    SeparatorSetting separator;
                    if (GetSeparatorForElement(
                            element,
                            &separator)) {
                        // Mark the routed event handled before publishing desired
                        // state so no downstream middle-click action can launch the
                        // inert shortcut while the backend removes it.
                        args.Handled(true);
                        RemoveSeparatorByIdentity(
                            separator.identity);
                        Wh_Log(
                            L"[MIDDLE] Remove separator identity='%s'",
                            separator.identity.c_str());
                        return true;
                    }
                }

                // A normal task button is never empty taskbar space. Stop here
                // instead of later seeing its common TaskbarFrame ancestor.
                return false;
            }

            // Don't immediately reject ButtonBase descendants: a routed
            // separator click can originate below the owning TaskListButton.
            // Remember the interactive ancestry and only use it to veto an
            // eventual background classification if no TaskListButton was found.
            if (IsButtonBaseElement(current)) {
                sawClickableControl = true;
            }

            // The system tray is a distinct subtree and can be rejected
            // immediately; no separator TaskListButton lives under it.
            if (IsSystemTrayTaskbarElement(className)) {
                return false;
            }

            if (IsTaskbarBackgroundClass(className)) {
                if (sawClickableControl) {
                    return false;
                }

                args.Handled(true);
                AddSeparatorFromUserAction();
                Wh_Log(L"[MIDDLE] Add separator from TaskbarBackground");
                return true;
            }

            if (auto element = current.try_as<FrameworkElement>()) {
                // On some taskbar templates the hit-tested empty-space source is
                // RootGrid/BackgroundFill rather than a visual descendant of the
                // TaskbarBackground control. Record those known background-layer
                // names and finish classification when we reach TaskbarFrame.
                const winrt::hstring name = element.Name();
                std::wstring_view nameView(
                    name.c_str(),
                    name.size());
                if (nameView == L"RootGrid" ||
                    nameView == L"BackgroundFill") {
                    sawRootGrid = true;
                }
            }

            if (IsTaskbarFrameClass(className)) {
                reachedTaskbarFrame = true;
                break;
            }

            current =
                winrt::Windows::UI::Xaml::Media::
                    VisualTreeHelper::GetParent(current);
        }

        // The current Windows 11 template can report Grid#RootGrid itself for
        // otherwise empty space, making TaskbarBackground a sibling rather than
        // an ancestor of OriginalSource. Only take this fallback after the walk
        // has ruled out task buttons/ButtonBase/SystemTray descendants.
        if (reachedTaskbarFrame &&
            sawRootGrid &&
            !sawClickableControl) {
            args.Handled(true);
            AddSeparatorFromUserAction();
            Wh_Log(L"[MIDDLE] Add separator from taskbar RootGrid background");
            return true;
        }
    } catch (...) {
        Wh_Log(L"[MIDDLE] Pointer inspection failed; using stock behavior");
    }

    return false;
}

static void WINAPI TaskbarController_OnPointerPressedHandler_Hook(
    void* pThis,
    winrt::Windows::Foundation::IInspectable const& sender,
    winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& args) {
    if (TryHandleMiddleClickInteraction(args)) {
        return;
    }

    g_taskbarControllerOnPointerPressedHandlerOriginal(
        pThis,
        sender,
        args);
}

static void WINAPI TaskListButton_UpdateVisualStates_Hook(
    void* pThis) {
    // Preserve the original precedence: Windows and every downstream hook,
    // including Taskbar height and icon size, finish first.
    g_taskListButtonUpdateVisualStatesOriginal(pThis);

    // Layout/property updates below can synchronously re-enter this hook. The
    // nested frame has already run the original function; only suppress our
    // own registry mutations until the outer frame completes.
    if (g_updatingSeparatorVisualStates) {
        return;
    }
    g_updatingSeparatorVisualStates = true;
    SeparatorVisualStateUpdateGuard updateGuard;

    FrameworkElement element =
        GetTaskListButtonElement(pThis);
    SeparatorSetting separator;
    bool isSeparator =
        GetSeparatorForElement(
            element,
            &separator);

    PruneExpiredSeparatorVisualStates();
    auto stateIt = FindSeparatorVisualState(pThis);

    // ItemsRepeater recycles TaskListButton containers. Undo every property
    // owned by this mod as soon as a container stops representing a separator.
    if (!isSeparator || !element || g_unloading) {
        if (stateIt != g_separatorVisualStates->end()) {
            RestoreSeparatorVisualState(stateIt);
        }
        return;
    }

    if (stateIt == g_separatorVisualStates->end()) {
        g_separatorVisualStates->push_back({
            .element = winrt::make_weak(element),
            .taskListButton = pThis,
        });
        stateIt = std::prev(g_separatorVisualStates->end());
    }

    SeparatorVisualState& state = *stateIt;

    ApplySeparatorMaxWidthOverride(
        state,
        element,
        separator);

    // If unload began while width was being applied, undo this button instead
    // of applying the remaining separator-only properties.
    if (g_unloading) {
        RestoreSeparatorVisualState(stateIt);
        return;
    }

    FrameworkElement iconPanel =
        FindChildByName(element, L"IconPanel");
    CenterSeparatorIcon(state, iconPanel);
    SuppressSeparatorHoverChrome(state, element, iconPanel);
    UpdateSeparatorAnchorHint(state, element, separator);
}

static HMODULE GetTaskbarViewModuleHandle() {
    HMODULE module = GetModuleHandleW(L"Taskbar.View.dll");

    if (!module) {
        module = GetModuleHandleW(L"ExplorerExtensions.dll");
    }

    return module;
}

static bool HookTaskbarViewDllSymbols(HMODULE module) {
    // Taskbar.View.dll, ExplorerExtensions.dll
    WindhawkUtils::SYMBOL_HOOK taskbarViewHooks[] = {
        {
            {
                LR"(private: void __cdecl winrt::Taskbar::implementation::TaskbarController::OnPointerPressedHandler(struct winrt::Windows::Foundation::IInspectable const &,struct winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const &))"
            },
            &g_taskbarControllerOnPointerPressedHandlerOriginal,
            TaskbarController_OnPointerPressedHandler_Hook,
            true,
        },
        {
            {
                LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::UpdateVisualStates(void))"
            },
            &g_taskListButtonUpdateVisualStatesOriginal,
            TaskListButton_UpdateVisualStates_Hook,
        },
        {
            {
                LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::OnDragCompletedGesture(void))"
            },
            &g_taskListButtonOnDragCompletedGestureOriginal,
            TaskListButton_OnDragCompletedGesture_Hook,
            true,
        },
        {
            {
                LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::OnContextRequested(struct winrt::Windows::UI::Xaml::UIElement const &,struct winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const &))"
            },
            &g_taskListButtonOnContextRequestedOriginal,
            TaskListButton_OnContextRequested_Hook,
            true,
        },
        {
            {
                LR"(public: static void __cdecl winrt::Taskbar::implementation::TaskListButtonHandlers::HandleContextRequested(struct winrt::Windows::UI::Xaml::UIElement const &,struct winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const &))"
            },
            &g_taskListButtonHandlersHandleContextRequestedOriginal,
            TaskListButtonHandlers_HandleContextRequested_Hook,
            true,
        },
        {
            {
                LR"(public: void __cdecl winrt::Taskbar::implementation::TaskbarResources::OnTaskListButtonContextRequested(struct winrt::Windows::UI::Xaml::UIElement const &,struct winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const &))"
            },
            &g_taskbarResourcesOnTaskListButtonContextRequestedOriginal,
            TaskbarResources_OnTaskListButtonContextRequested_Hook,
            true,
        },
    };

    if (!WindhawkUtils::HookSymbols(
            module,
            taskbarViewHooks,
            ARRAYSIZE(taskbarViewHooks))) {
        Wh_Log(L"[STYLE] HookSymbols(Taskbar view) failed");
        return false;
    }

    const bool hasContextRequestRoute =
        g_taskListButtonOnContextRequestedOriginal ||
        g_taskListButtonHandlersHandleContextRequestedOriginal ||
        g_taskbarResourcesOnTaskListButtonContextRequestedOriginal;
    // Seamless Taskbar Utilities adds the menu item from its own menu hook.
    const bool hasAddMenuRoute = true;
    const bool hasMiddleClickRoute =
        g_taskbarControllerOnPointerPressedHandlerOriginal != nullptr;

    const bool contextInteractionAvailable =
        hasAddMenuRoute && hasContextRequestRoute;
    g_contextMenuInteractionAvailable.store(
        contextInteractionAvailable,
        std::memory_order_release);
    g_middleClickInteractionAvailable.store(
        hasMiddleClickRoute,
        std::memory_order_release);
    if (hasContextRequestRoute) {
        g_separatorContextSuppressionAvailable.store(
            true,
            std::memory_order_release);
    }

    Wh_Log(
        L"[STYLE] Interaction routes: addMenu=%d context(button=%d handlers=%d resources=%d) middleClick=%d",
        hasAddMenuRoute ? 1 : 0,
        g_taskListButtonOnContextRequestedOriginal ? 1 : 0,
        g_taskListButtonHandlersHandleContextRequestedOriginal ? 1 : 0,
        g_taskbarResourcesOnTaskListButtonContextRequestedOriginal ? 1 : 0,
        hasMiddleClickRoute ? 1 : 0);

    if (!contextInteractionAvailable) {
        Wh_Log(
            L"[STYLE] Context-menu interaction is unavailable/partial on this build");
    }
    if (!hasMiddleClickRoute) {
        Wh_Log(
            L"[STYLE] Middle-click interaction route is unavailable on this build");
    }

    // Both frontends are hooked opportunistically, so a missing selected route
    // can fall back immediately without a mod reload. Do this symmetrically in
    // either direction.
    ApplyInteractionModeCapabilityFallback(L"STYLE");

    Wh_Log(L"[STYLE] Taskbar view hooks installed; widthMode=MaxWidth");

    return true;
}


static bool HookTaskbarDllSymbols(HMODULE taskbarDll);
static HWND FindCurrentProcessTaskbarWnd();
static void StartBackendWorker(bool refreshIfAlreadyRunning);

class HookInstallerScope {
public:
    HookInstallerScope() {
        if (g_hookInstallationClosed.load(std::memory_order_acquire)) {
            return;
        }

        g_hookInstallersInFlight.fetch_add(
            1,
            std::memory_order_acq_rel);

        // Close the race where unload begins between the first closed check and
        // publishing this installer as in-flight.
        if (g_hookInstallationClosed.load(std::memory_order_acquire)) {
            g_hookInstallersInFlight.fetch_sub(
                1,
                std::memory_order_acq_rel);
            return;
        }

        active_ = true;
    }

    ~HookInstallerScope() {
        if (active_) {
            g_hookInstallersInFlight.fetch_sub(
                1,
                std::memory_order_acq_rel);
        }
    }

    explicit operator bool() const {
        return active_;
    }

private:
    bool active_ = false;
};

static void DrainHookInstallers() {
    constexpr ULONGLONG kDrainTimeoutMs = 2000;
    constexpr DWORD kDrainSleepMs = 5;

    const ULONGLONG started = GetTickCount64();
    while (g_hookInstallersInFlight.load(
               std::memory_order_acquire) != 0 &&
           GetTickCount64() - started < kDrainTimeoutMs) {
        Sleep(kDrainSleepMs);
    }

    const unsigned int remaining =
        g_hookInstallersInFlight.load(std::memory_order_acquire);
    if (remaining != 0) {
        Wh_Log(
            L"[HOOK] Timed out draining %u in-flight hook installer(s); proceeding with unload",
            remaining);
    }
}

static bool InstallTaskbarViewHooks(
    HMODULE module,
    bool applyOperations) {
    HookInstallerScope installer;
    if (!installer || g_unloading) {
        return false;
    }

    if (g_taskbarViewDllHooked.load(std::memory_order_acquire)) {
        return true;
    }

    bool expected = false;
    if (!g_taskbarViewHookInstallationClaimed.compare_exchange_strong(
            expected,
            true,
            std::memory_order_acq_rel)) {
        return g_taskbarViewDllHooked.load(std::memory_order_acquire);
    }

    // No mod mutex is held while entering the Windhawk symbol/hook engine.
    if (!HookTaskbarViewDllSymbols(module)) {
        return false;
    }

    // If unload started while symbol resolution was in progress, don't enter
    // another engine operation from this late installer.
    if (g_hookInstallationClosed.load(std::memory_order_acquire) ||
        g_unloading) {
        return false;
    }

    if (applyOperations && !Wh_ApplyHookOperations()) {
        Wh_Log(L"[STYLE] Wh_ApplyHookOperations failed");
        return false;
    }

    g_taskbarViewDllHooked.store(true, std::memory_order_release);
    return true;
}

static bool InstallTaskbarDllHooks(
    HMODULE module,
    bool applyOperations) {
    HookInstallerScope installer;
    if (!installer || g_unloading) {
        return false;
    }

    if (g_taskbarDllHooked.load(std::memory_order_acquire)) {
        return true;
    }

    bool expected = false;
    if (!g_taskbarDllHookInstallationClaimed.compare_exchange_strong(
            expected,
            true,
            std::memory_order_acq_rel)) {
        return g_taskbarDllHooked.load(std::memory_order_acquire);
    }

    // Resolve every taskbar.dll symbol in one HookSymbols call. Besides being
    // faster, this avoids invalidating WindhawkUtils' per-module symbol cache.
    if (!HookTaskbarDllSymbols(module)) {
        return false;
    }

    if (g_hookInstallationClosed.load(std::memory_order_acquire) ||
        g_unloading) {
        return false;
    }

    if (applyOperations && !Wh_ApplyHookOperations()) {
        Wh_Log(L"[TASKBAR] Wh_ApplyHookOperations failed");
        return false;
    }

    g_taskbarDllHooked.store(true, std::memory_order_release);
    return true;
}

static void OnModuleLoaded(LPCWSTR lpLibFileName, HMODULE module) {

    if (!module ||
        g_hookInstallationClosed.load(std::memory_order_acquire) ||
        g_unloading) {
        return;
    }

    if (!g_taskbarViewDllHooked &&
        GetTaskbarViewModuleHandle() == module) {
        Wh_Log(
            L"[STYLE] Taskbar view module loaded: %s",
            lpLibFileName ? lpLibFileName : L"<unknown>");

        InstallTaskbarViewHooks(module, true);
    }

    if (!g_taskbarDllHooked.load(std::memory_order_acquire) &&
        GetModuleHandleW(L"taskbar.dll") == module) {
        Wh_Log(
            L"[TASKBAR] taskbar.dll loaded; installing taskbar hooks");
        InstallTaskbarDllHooks(module, true);

        // Do not scan windows or create the backend worker from inside a
        // LoadLibraryExW hook. TrayUI::StartTaskbar and Wh_ModAfterInit own
        // backend readiness/startup outside the loader-lock-sensitive path.
    }
}

static bool InstallLoadLibraryWatcher() {
    // The mod-wide LoadLibraryExW hook calls OnModuleLoaded.
    g_loadLibraryWatcherInstalled = true;
    return true;
}

static bool InitializeTaskbarStylingHooks() {
    if (HMODULE module = GetTaskbarViewModuleHandle()) {
        return InstallTaskbarViewHooks(module, false);
    }

    Wh_Log(
        L"[STYLE] Taskbar view module not loaded yet; "
        L"installing LoadLibraryExW watcher");

    return InstallLoadLibraryWatcher();
}



// -----------------------------------------------------------------------------
// Separator interaction suppression.
//
// Taskbar.View owns modern context requests and the drag-completion boundary;
// those are handled above. taskbar.dll is used only for model-level semantic
// actions that already expose the exact ITaskGroup:
//
// - CTaskListWnd::HandleClick:
//     swallow activation for our separator groups.
// - CTaskListWnd::OnContextMenu:
//     suppress the legacy separator context-menu route.
// - CTaskBtnGroup::ShouldShowToolTip:
//     legacy tooltip gate fallback.
// - CTaskGroup::GetToolTipText:
//     directly report no tooltip text for separator groups.
//
// CTaskListWnd::TryMoveGroup is observed (never blocked) so successful native
// pinned-item drags can be mirrored into the mod-owned state file. Separator
// Unpin is a direct command from our Explorer-hosted MenuFlyout to desired state.
// -----------------------------------------------------------------------------

static void* g_taskGroupGetAppIdAddress;
static void* g_taskBtnGroupGetGroupAddress;
static void* g_taskListWndVtableITaskListUI;

using TaskListWnd_HandleClick_t =
    HRESULT(WINAPI*)(
        void* pThis,
        void* taskGroup,
        void* taskItem,
        const void* launcherOptions);

static TaskListWnd_HandleClick_t
    g_taskListWndHandleClickOriginal;

using TaskListWnd_OnContextMenu_t =
    void(WINAPI*)(
        void* pThis,
        POINT point,
        HWND hwnd,
        bool keyboardInvoked,
        void* taskGroup,
        void* taskItem);

static TaskListWnd_OnContextMenu_t
    g_taskListWndOnContextMenuOriginal;

using TaskBtnGroup_ShouldShowToolTip_t =
    int(WINAPI*)(
        void* pThis,
        void* taskItem);

static TaskBtnGroup_ShouldShowToolTip_t
    g_taskBtnGroupShouldShowToolTipOriginal;


using TaskGroup_GetToolTipText_t =
    HRESULT(WINAPI*)(
        void* pThis,
        void* taskItem,
        wchar_t* text,
        int cchText);

static TaskGroup_GetToolTipText_t
    g_taskGroupGetToolTipTextOriginal;

static bool IsSeparatorTaskGroup(void* taskGroup) {
    if (!taskGroup || !g_taskGroupGetAppIdAddress) {
        return false;
    }

    using CTaskGroup_GetAppID_t =
        const wchar_t*(WINAPI*)(void* pThis);

    auto getAppId =
        reinterpret_cast<CTaskGroup_GetAppID_t>(
            g_taskGroupGetAppIdAddress);

    const wchar_t* appId = getAppId(taskGroup);
    if (!appId || !*appId) {
        return false;
    }

    // Recognition here must outlive the desired/storage snapshots. A pointer
    // gesture can remove a separator from desired state and the backend can
    // unpin/delete its shortcut before Windows finishes dispatching the same
    // mouse gesture through CTaskListWnd::HandleClick. If identity recognition
    // depended on g_settings/g_storedSeparatorSettings, that late callback could
    // fall through and try to launch the now-deleted .lnk. The suffix is this
    // mod's private AppUserModelID namespace, and the stable-ID parser also
    // validates the trailing component, so a still-alive task group remains
    // inert for its entire native lifetime.
    return ExtractStableIdFromSeparatorIdentity(
               std::wstring_view(appId))
        .has_value();
}

static HRESULT WINAPI TaskListWnd_HandleClick_Hook(
    void* pThis,
    void* taskGroup,
    void* taskItem,
    const void* launcherOptions) {
    if (!g_unloading &&
        IsSeparatorTaskGroup(taskGroup)) {
        return S_OK;
    }

    return g_taskListWndHandleClickOriginal(
        pThis,
        taskGroup,
        taskItem,
        launcherOptions);
}

static void WINAPI TaskListWnd_OnContextMenu_Hook(
    void* pThis,
    POINT point,
    HWND hwnd,
    bool keyboardInvoked,
    void* taskGroup,
    void* taskItem) {
    if (!g_unloading &&
        IsSeparatorTaskGroup(taskGroup)) {
        Wh_Log(L"[CTX] Suppressed legacy separator context menu");
        return;
    }

    g_taskListWndOnContextMenuOriginal(
        pThis,
        point,
        hwnd,
        keyboardInvoked,
        taskGroup,
        taskItem);
}

static int WINAPI TaskBtnGroup_ShouldShowToolTip_Hook(
    void* pThis,
    void* taskItem) {
    if (!g_unloading &&
        pThis &&
        g_taskBtnGroupGetGroupAddress) {
        using CTaskBtnGroup_GetGroup_t =
            void*(WINAPI*)(void* pThis);

        auto getGroup =
            reinterpret_cast<CTaskBtnGroup_GetGroup_t>(
                g_taskBtnGroupGetGroupAddress);

        void* taskGroup = getGroup(pThis);

        if (IsSeparatorTaskGroup(taskGroup)) {
            return FALSE;
        }
    }

    return g_taskBtnGroupShouldShowToolTipOriginal(
        pThis,
        taskItem);
}


static HRESULT WINAPI TaskGroup_GetToolTipText_Hook(
    void* pThis,
    void* taskItem,
    wchar_t* text,
    int cchText) {
    if (!g_unloading &&
        IsSeparatorTaskGroup(pThis)) {
        if (text && cchText > 0) {
            text[0] = L'\0';
        }

        // Explicitly report "no tooltip text".
        return S_FALSE;
    }

    return g_taskGroupGetToolTipTextOriginal(
        pThis,
        taskItem,
        text,
        cchText);
}


using TaskListWnd_IsPinned_t =
    bool(WINAPI*)(void* pThis, void* taskGroup);
static TaskListWnd_IsPinned_t
    g_taskListWndIsPinned;

using TaskListWnd_GetRelativeTaskOrder_t =
    int(WINAPI*)(void* pThis, void* taskGroup);
static TaskListWnd_GetRelativeTaskOrder_t
    g_taskListWndGetRelativeTaskOrder;
static TaskListWnd_GetRelativeTaskOrder_t
    g_taskListWndMultiGetRelativeTaskOrder;

using TaskListWnd_GetButtonGroupCount_t =
    int(WINAPI*)(void* pThis);
static TaskListWnd_GetButtonGroupCount_t
    g_taskListWndGetButtonGroupCount;

using TaskListWnd_TryMoveGroup_t =
    bool(WINAPI*)(void* pThis, void* taskGroup, unsigned int index);
static TaskListWnd_TryMoveGroup_t
    g_taskListWndTryMoveGroupOriginal;

using TaskListWnd_HandleWinNumHotKey_t =
    HRESULT(WINAPI*)(void* pThis, short index, unsigned short flags);
static TaskListWnd_HandleWinNumHotKey_t
    g_taskListWndHandleWinNumHotKeyOriginal;

using TaskListWndMulti_IsPinned_t =
    bool(WINAPI*)(void* pThis, void* taskGroup);
static TaskListWndMulti_IsPinned_t
    g_taskListWndMultiIsPinned;

using TaskListWndMulti_TryMoveGroup_t =
    bool(WINAPI*)(void* pThis, void* taskGroup, unsigned int index);
static TaskListWndMulti_TryMoveGroup_t
    g_taskListWndMultiTryMoveGroupOriginal;

static thread_local int g_tryMoveGroupHookDepth = 0;

static std::wstring CopyTaskGroupAppId(void* taskGroup) {
    if (!taskGroup || !g_taskGroupGetAppIdAddress) {
        return {};
    }

    using CTaskGroup_GetAppID_t =
        const wchar_t*(WINAPI*)(void* pThis);
    auto getAppId =
        reinterpret_cast<CTaskGroup_GetAppID_t>(
            g_taskGroupGetAppIdAddress);

    const wchar_t* appId = getAppId(taskGroup);
    return appId ? std::wstring(appId) : std::wstring();
}

static void ApplyPinnedMoveToSnapshot(
    Settings& settings,
    std::wstring_view movedAppId,
    int oldIndex,
    int newIndex) {
    if (oldIndex == newIndex) {
        return;
    }

    SeparatorSetting* movedSeparator = nullptr;
    for (auto& separator : settings.separators) {
        if (separator.identity == movedAppId) {
            movedSeparator = &separator;
            break;
        }
    }

    for (auto& separator : settings.separators) {
        if (&separator == movedSeparator || separator.targetIndex < 0) {
            continue;
        }

        if (oldIndex < newIndex) {
            if (separator.targetIndex > oldIndex &&
                separator.targetIndex <= newIndex) {
                separator.targetIndex--;
            }
        } else {
            if (separator.targetIndex >= newIndex &&
                separator.targetIndex < oldIndex) {
                separator.targetIndex++;
            }
        }
    }

    if (movedSeparator) {
        movedSeparator->targetIndex = newIndex;
    }
}


// -----------------------------------------------------------------------------
// Win+number compensation.
//
// targetIndex is deliberately *not* used here. GetRelativeTaskOrder/TryMoveGroup
// expose pinned-list ordinals, while CTaskListWnd::HandleWinNumHotKey indexes the
// live task-button-group array, which also contains running non-pinned groups.
// Walk that live array on the taskbar UI thread and skip separator groups there.
// -----------------------------------------------------------------------------

static bool TryProbeButtonGroupsArrayOffset(size_t* offsetOut) {
    if (!offsetOut || !g_taskListWndGetButtonGroupCount) {
        return false;
    }

    constexpr size_t kProbeSize = 256;
    int values[kProbeSize];
    int* pointers[kProbeSize];

    for (size_t i = 0; i < kProbeSize; i++) {
        values[i] = static_cast<int>(i);
        pointers[i] = &values[i];
    }

    int probe =
        g_taskListWndGetButtonGroupCount(pointers);
    if (probe <= 0 ||
        static_cast<size_t>(probe) >= kProbeSize) {
        return false;
    }

    *offsetOut = static_cast<size_t>(probe);
    return true;
}

static bool TryReadTaskButtonGroupDpa(
    void* taskListWnd,
    size_t offset,
    int* countOut,
    void*** itemsOut) {
    if (!taskListWnd || !countOut || !itemsOut ||
        !g_taskListWndVtableITaskListUI) {
        return false;
    }

    // GetButtonGroupCount's member offset is relative to the ITaskListUI
    // subobject, while HandleWinNumHotKey can provide another subobject.
    constexpr size_t kMaxSubobjectSlots = 32;
    void** taskListUi = reinterpret_cast<void**>(taskListWnd);
    size_t slot = 0;
    while (slot < kMaxSubobjectSlots &&
           *taskListUi != g_taskListWndVtableITaskListUI) {
        slot++;
        taskListUi++;
    }
    if (slot == kMaxSubobjectSlots) {
        return false;
    }

    auto dpa = reinterpret_cast<unsigned char*>(
        taskListUi[offset]);
    if (!dpa) {
        return false;
    }

    *countOut = *reinterpret_cast<int*>(dpa);
    *itemsOut = *reinterpret_cast<void***>(
        dpa + sizeof(void*));
    return true;
}

static std::optional<size_t> GetButtonGroupsArrayOffset() {
    // 0 = uninitialized, kUnavailable = permanently unavailable for this
    // process, otherwise the value is offset+1. Caching failure matters because
    // Win+N is a hot input path and a changed private ABI should be probed once.
    static constexpr size_t kUnavailable = static_cast<size_t>(-1);
    static std::atomic<size_t> cachedOffsetPlusOne{0};

    size_t cached =
        cachedOffsetPlusOne.load(std::memory_order_acquire);
    if (cached == kUnavailable) {
        return std::nullopt;
    }
    if (cached != 0) {
        return cached - 1;
    }

    size_t offset = 0;
    if (!TryProbeButtonGroupsArrayOffset(&offset)) {
        cachedOffsetPlusOne.store(
            kUnavailable,
            std::memory_order_release);
        Wh_Log(
            L"[WINNUM] Button-group offset probe failed; disabling compensation");
        return std::nullopt;
    }

    cachedOffsetPlusOne.store(
        offset + 1,
        std::memory_order_release);
    Wh_Log(
        L"[WINNUM] Live button-group DPA member offset=%zu",
        offset);
    return offset;
}

static bool GetTaskButtonGroups(
    void* taskListWnd,
    int* countOut,
    void*** itemsOut) {
    if (!taskListWnd || !countOut || !itemsOut) {
        return false;
    }

    auto offset = GetButtonGroupsArrayOffset();
    if (!offset) {
        return false;
    }

    int count = 0;
    void** items = nullptr;
    if (!TryReadTaskButtonGroupDpa(
            taskListWnd,
            *offset,
            &count,
            &items)) {
        Wh_Log(
            L"[WINNUM] Live button-group DPA read failed; using stock Win+N");
        return false;
    }

    constexpr int kMaxReasonableButtonGroups = 4096;
    if (count < 0 || count > kMaxReasonableButtonGroups ||
        (count > 0 && !items)) {
        Wh_Log(
            L"[WINNUM] Invalid live button-group array count=%d items=%p",
            count,
            items);
        return false;
    }

    *countOut = count;
    *itemsOut = items;
    return true;
}

static short CompensateWinNumHotKeyIndex(
    void* taskListWnd,
    short logicalIndex) {
    // Win+1..Win+0 reaches this layer as zero-based 0..9. Leave any unexpected
    // internal/special value alone rather than changing undocumented behavior.
    if (logicalIndex < 0 || logicalIndex > 9 ||
        g_unloading ||
        g_internalCleanupInProgress.load(std::memory_order_acquire) ||
        !g_taskBtnGroupGetGroupAddress ||
        !g_taskListWndVtableITaskListUI ||
        !g_taskListWndGetButtonGroupCount) {
        return logicalIndex;
    }

    int count = 0;
    void** groups = nullptr;
    if (!GetTaskButtonGroups(
            taskListWnd,
            &count,
            &groups)) {
        return logicalIndex;
    }

    using CTaskBtnGroup_GetGroup_t =
        void*(WINAPI*)(void* pThis);
    auto getGroup =
        reinterpret_cast<CTaskBtnGroup_GetGroup_t>(
            g_taskBtnGroupGetGroupAddress);

    int remaining = logicalIndex;
    for (int i = 0;
         i < count && i <= SHRT_MAX;
         i++) {
        void* taskBtnGroup = groups[i];
        if (!taskBtnGroup) {
            // Don't risk translating against a partially mutating/corrupt list.
            return logicalIndex;
        }

        void* taskGroup = getGroup(taskBtnGroup);
        if (!taskGroup) {
            return logicalIndex;
        }

        if (IsSeparatorTaskGroup(taskGroup)) {
            continue;
        }

        if (remaining == 0) {
            return static_cast<short>(i);
        }

        remaining--;
    }

    // Fewer ordinary groups than the requested slot. Feed stock code a
    // guaranteed one-past-end physical index so a separator can't accidentally
    // become the target merely because it made the raw group array long enough.
    return count <= SHRT_MAX
               ? static_cast<short>(count)
               : logicalIndex;
}

static HRESULT WINAPI TaskListWnd_HandleWinNumHotKey_Hook(
    void* pThis,
    short index,
    unsigned short flags) {
    short compensatedIndex =
        CompensateWinNumHotKeyIndex(
            pThis,
            index);

    if (compensatedIndex != index) {
        Wh_Log(
            L"[WINNUM] logical=%d physical=%d flags=0x%04X",
            static_cast<int>(index),
            static_cast<int>(compensatedIndex),
            static_cast<unsigned int>(flags));
    }

    return g_taskListWndHandleWinNumHotKeyOriginal(
        pThis,
        compensatedIndex,
        flags);
}


// -----------------------------------------------------------------------------
// Native taskbar mutation persistence.
//
// Windhawk no longer owns separator position/list configuration. TryMoveGroup
// mirrors native reorder operations into the in-memory separator state. The
// Taskbar.View drag-completion hook queues one backend persistence pass when
// the drag ends. Add and Unpin have their own discrete commit points and queue
// the same worker; live taskbar UI callbacks never perform synchronous disk I/O.
// -----------------------------------------------------------------------------

static void FlushPendingSeparatorStateSynchronously() {
    Settings snapshot;

    {
        std::lock_guard<std::mutex> mutationLock(
            g_settingsMutationMutex);

        if (!g_separatorStateDirty) {
            return;
        }

        {
            std::shared_lock lock(g_settingsMutex);
            snapshot = g_settings;
        }

        // Teardown-only fallback. Live taskbar paths never call this function.
        if (SaveSeparatorStateFile(snapshot)) {
            g_separatorStateDirty = false;
            Wh_Log(L"[STATE] Persisted pending separator state during teardown");
        } else {
            Wh_Log(L"[STATE] Failed to persist pending separator state during teardown");
        }
    }
}

static void RecordNativePinnedMove(
    std::wstring_view movedAppId,
    int oldIndex,
    int newIndex) {
    if (oldIndex < 0 ||
        newIndex < 0 ||
        oldIndex == newIndex) {
        return;
    }

    std::lock_guard<std::mutex> mutationLock(
        g_settingsMutationMutex);

    bool touchesSeparator = false;

    {
        std::unique_lock lock(g_settingsMutex);

        Settings before = g_settings;

        ApplyPinnedMoveToSnapshot(
            g_settings,
            movedAppId,
            oldIndex,
            newIndex);

        touchesSeparator =
            !SettingsSnapshotsEqual(
                before,
                g_settings);

        if (!touchesSeparator) {
            return;
        }

        // Windows already performed this move. Mirror it into the applied and
        // stale-artifact snapshots immediately so the backend never "corrects"
        // the user's native taskbar order while the drag is still in progress.
        ApplyPinnedMoveToSnapshot(
            g_appliedSettings,
            movedAppId,
            oldIndex,
            newIndex);

        for (auto& stored :
             g_storedSeparatorSettings) {
            if (stored.identity == movedAppId) {
                stored.targetIndex = newIndex;
                continue;
            }

            if (stored.targetIndex < 0) {
                continue;
            }

            if (oldIndex < newIndex) {
                if (stored.targetIndex > oldIndex &&
                    stored.targetIndex <= newIndex) {
                    stored.targetIndex--;
                }
            } else if (
                stored.targetIndex >= newIndex &&
                stored.targetIndex < oldIndex) {
                stored.targetIndex++;
            }
        }

        g_separatorStateDirty = true;
    }

    Wh_Log(
        L"[NATIVE-MOVE] staged native pinned move appId='%s' %d -> %d",
        std::wstring(movedAppId).c_str(),
        oldIndex,
        newIndex);

    // Normally the Taskbar.View drag-completion hook queues one persistence
    // pass after the gesture fully unwinds. That presentation callback is an
    // optional private symbol, though, while TryMoveGroup can still be available.
    // Preserve crash durability on such builds by waking the worker immediately.
    if (!g_taskbarViewDllHooked.load(std::memory_order_acquire) ||
        !g_taskListButtonOnDragCompletedGestureOriginal) {
        QueueBackendWork();
    }
}

static bool RunTryMoveGroupObserver(
    TaskListWnd_TryMoveGroup_t original,
    TaskListWnd_IsPinned_t isPinnedFunction,
    TaskListWnd_GetRelativeTaskOrder_t getRelativeTaskOrder,
    const wchar_t* route,
    void* pThis,
    void* taskGroup,
    unsigned int index) {
    const bool outer =
        g_tryMoveGroupHookDepth++ == 0;

    int oldIndex = -1;
    int newIndex = -1;
    bool pinned = false;
    std::wstring appId;

    if (!g_unloading &&
        outer &&
        taskGroup &&
        getRelativeTaskOrder &&
        isPinnedFunction) {
        oldIndex =
            getRelativeTaskOrder(
                pThis,
                taskGroup);
        pinned =
            isPinnedFunction(
                pThis,
                taskGroup);
        appId =
            CopyTaskGroupAppId(taskGroup);
    }

    bool result =
        original(
            pThis,
            taskGroup,
            index);

    if (!g_unloading &&
        outer &&
        taskGroup &&
        getRelativeTaskOrder) {
        newIndex =
            getRelativeTaskOrder(
                pThis,
                taskGroup);
    }

    --g_tryMoveGroupHookDepth;

    if (!g_unloading &&
        outer &&
        result &&
        pinned &&
        !appId.empty() &&
        oldIndex >= 0 &&
        newIndex >= 0 &&
        oldIndex != newIndex) {
        Wh_Log(
            L"[NATIVE-MOVE] %s appId='%s' relative=%d -> %d argTarget=%u",
            route,
            appId.c_str(),
            oldIndex,
            newIndex,
            index);

        RecordNativePinnedMove(
            appId,
            oldIndex,
            newIndex);
    }

    return result;
}

static bool WINAPI TaskListWnd_TryMoveGroup_Hook(
    void* pThis,
    void* taskGroup,
    unsigned int index) {
    return RunTryMoveGroupObserver(
        g_taskListWndTryMoveGroupOriginal,
        g_taskListWndIsPinned,
        g_taskListWndGetRelativeTaskOrder,
        L"CTaskListWnd::TryMoveGroup",
        pThis,
        taskGroup,
        index);
}

static bool WINAPI TaskListWndMulti_TryMoveGroup_Hook(
    void* pThis,
    void* taskGroup,
    unsigned int index) {
    return RunTryMoveGroupObserver(
        reinterpret_cast<TaskListWnd_TryMoveGroup_t>(
            g_taskListWndMultiTryMoveGroupOriginal),
        reinterpret_cast<TaskListWnd_IsPinned_t>(
            g_taskListWndMultiIsPinned),
        g_taskListWndMultiGetRelativeTaskOrder,
        L"CTaskListWndMulti::TryMoveGroup",
        pThis,
        taskGroup,
        index);
}

static void ShiftSeparatorTargetsAfterRemoval(
    Settings& settings,
    std::wstring_view removedIdentity,
    int removedIndex) {
    settings.separators.erase(
        std::remove_if(
            settings.separators.begin(),
            settings.separators.end(),
            [removedIdentity](const SeparatorSetting& separator) {
                return separator.identity ==
                    removedIdentity;
            }),
        settings.separators.end());

    if (removedIndex >= 0) {
        for (auto& separator :
             settings.separators) {
            if (separator.targetIndex >
                removedIndex) {
                separator.targetIndex--;
            }
        }
    }

    for (size_t i = 0;
         i < settings.separators.size();
         i++) {
        settings.separators[i].sourceIndex =
            static_cast<int>(i);
        settings.separators[i].ordinal =
            static_cast<int>(i) + 1;
    }
}


static void RemoveSeparatorByIdentity(
    std::wstring identity) {
    if (identity.empty() ||
        g_unloading ||
        g_internalCleanupInProgress.load()) {
        return;
    }

    Settings updated;
    int removedIndex = -1;

    {
        std::lock_guard<std::mutex> mutationLock(
            g_settingsMutationMutex);

        if (g_unloading ||
            g_internalCleanupInProgress.load(std::memory_order_acquire)) {
            return;
        }

        {
            std::shared_lock lock(g_settingsMutex);
            updated = g_settings;

            const SeparatorSetting* existing =
                FindSeparatorByIdentity(
                    g_settings,
                    identity);
            if (!existing) {
                return;
            }

            removedIndex = existing->targetIndex;
        }

        ShiftSeparatorTargetsAfterRemoval(
            updated,
            identity,
            removedIndex);

        {
            std::unique_lock lock(g_settingsMutex);
            g_settings = updated;
            g_backendHasConverged = false;
        }

        // The backend worker persists this snapshot before it is allowed to
        // unpin anything, preserving persist-before-mutate without blocking
        // the taskbar UI thread on FlushFileBuffers/MoveFileEx.
        g_separatorStateDirty = true;
    }

    Wh_Log(
        L"[NATIVE-UNPIN] Removed separator from desired state identity='%s' index=%d",
        identity.c_str(),
        removedIndex);

    // Keep the old applied/stored snapshots until the backend has actually
    // unpinned the shortcut. That keeps the still-visible button recognized,
    // styled, and inert during the short convergence window.
    QueueBackendWork();
}

using TrayUI_StartTaskbar_t =
    void(WINAPI*)(void* pThis);

static TrayUI_StartTaskbar_t
    g_trayUIStartTaskbarOriginal;

static void WINAPI TrayUI_StartTaskbar_Hook(void* pThis) {
    g_trayUIStartTaskbarOriginal(pThis);

    if (g_unloading) {
        return;
    }

    Wh_Log(L"[LIFECYCLE] TrayUI::StartTaskbar completed");
    // A repeated TrayUI::StartTaskbar is an in-process reconstruction and must
    // force one lifecycle refresh even when the persistent backend is running.
    StartBackendWorker(true);
}

static bool HookTaskbarDllSymbols(HMODULE taskbarDll) {
    WindhawkUtils::SYMBOL_HOOK taskbarDllHooks[] = {
        {
            {
                LR"(public: virtual void __cdecl TrayUI::StartTaskbar(void))"
            },
            &g_trayUIStartTaskbarOriginal,
            TrayUI_StartTaskbar_Hook,
        },
        {
            {
                LR"(public: virtual unsigned short const * __cdecl CTaskGroup::GetAppID(void))"
            },
            &g_taskGroupGetAppIdAddress,
            nullptr,
        },
        {
            {
                LR"(public: virtual bool __cdecl CTaskListWnd::IsPinned(struct ITaskGroup *))"
            },
            &g_taskListWndIsPinned,
            nullptr,
        },
        {
            {
                LR"(public: virtual int __cdecl CTaskListWnd::GetRelativeTaskOrder(struct ITaskGroup *))"
            },
            &g_taskListWndGetRelativeTaskOrder,
            nullptr,
        },
        {
            {
                LR"(const CTaskListWnd::`vftable'{for `ITaskListUI'})"
            },
            &g_taskListWndVtableITaskListUI,
            nullptr,
            true,
        },
        {
            {
                LR"(public: virtual int __cdecl CTaskListWnd::GetButtonGroupCount(void))"
            },
            &g_taskListWndGetButtonGroupCount,
            nullptr,
            true,
        },
        {
            {
                LR"(public: virtual long __cdecl CTaskListWnd::HandleWinNumHotKey(short,unsigned short))"
            },
            &g_taskListWndHandleWinNumHotKeyOriginal,
            TaskListWnd_HandleWinNumHotKey_Hook,
            true,
        },
        {
            {
                LR"(public: virtual bool __cdecl CTaskListWnd::TryMoveGroup(struct ITaskGroup *,unsigned int))"
            },
            &g_taskListWndTryMoveGroupOriginal,
            TaskListWnd_TryMoveGroup_Hook,
        },
        {
            {
                LR"(public: virtual bool __cdecl CTaskListWndMulti::IsPinned(struct ITaskGroup *))"
            },
            &g_taskListWndMultiIsPinned,
            nullptr,
            true,
        },
        {
            {
                LR"(public: virtual int __cdecl CTaskListWndMulti::GetRelativeTaskOrder(struct ITaskGroup *))"
            },
            &g_taskListWndMultiGetRelativeTaskOrder,
            nullptr,
            true,
        },
        {
            {
                LR"(public: virtual bool __cdecl CTaskListWndMulti::TryMoveGroup(struct ITaskGroup *,unsigned int))"
            },
            &g_taskListWndMultiTryMoveGroupOriginal,
            TaskListWndMulti_TryMoveGroup_Hook,
            true,
        },
        {
            {
                LR"(public: virtual long __cdecl CTaskGroup::GetToolTipText(struct ITaskItem *,unsigned short *,int))"
            },
            &g_taskGroupGetToolTipTextOriginal,
            TaskGroup_GetToolTipText_Hook,
            true,
        },
        {
            {
                LR"(public: virtual struct ITaskGroup * __cdecl CTaskBtnGroup::GetGroup(void))"
            },
            &g_taskBtnGroupGetGroupAddress,
            nullptr,
            true,
        },
        {
            {
                LR"(public: virtual long __cdecl CTaskListWnd::HandleClick(struct ITaskGroup *,struct ITaskItem *,struct winrt::Windows::System::LauncherOptions const &))"
            },
            &g_taskListWndHandleClickOriginal,
            TaskListWnd_HandleClick_Hook,
            true,
        },
        {
            {
                LR"(public: virtual void __cdecl CTaskListWnd::OnContextMenu(struct tagPOINT,struct HWND__ *,bool,struct ITaskGroup *,struct ITaskItem *))"
            },
            &g_taskListWndOnContextMenuOriginal,
            TaskListWnd_OnContextMenu_Hook,
            true,
        },
        {
            {
                LR"(public: virtual int __cdecl CTaskBtnGroup::ShouldShowToolTip(struct ITaskItem *))"
            },
            &g_taskBtnGroupShouldShowToolTipOriginal,
            TaskBtnGroup_ShouldShowToolTip_Hook,
            true,
        },
    };

    if (!WindhawkUtils::HookSymbols(
            taskbarDll,
            taskbarDllHooks,
            ARRAYSIZE(taskbarDllHooks))) {
        Wh_Log(L"[TASKBAR] HookSymbols(taskbar.dll) failed");
        return false;
    }

    if (g_taskListWndOnContextMenuOriginal) {
        g_separatorContextSuppressionAvailable.store(
            true,
            std::memory_order_release);
    }

    Wh_Log(
        L"[TASKBAR] taskbar.dll hooks installed in one symbol pass; "
        L"WinNum=%d TaskListUI=%d ButtonGroups=%d GetGroup=%d LegacyContextSuppress=%d",
        g_taskListWndHandleWinNumHotKeyOriginal ? 1 : 0,
        g_taskListWndVtableITaskListUI ? 1 : 0,
        g_taskListWndGetButtonGroupCount ? 1 : 0,
        g_taskBtnGroupGetGroupAddress ? 1 : 0,
        g_taskListWndOnContextMenuOriginal ? 1 : 0);
    return true;
}


// -----------------------------------------------------------------------------
// Shortcut creation.
// -----------------------------------------------------------------------------

static HRESULT SetShortcutAppId(
    IShellLinkW* shellLink,
    const std::wstring& appId) {
    IPropertyStore* propertyStore = nullptr;

    HRESULT hr = shellLink->QueryInterface(
        IID_PPV_ARGS(&propertyStore));

    if (FAILED(hr)) {
        return hr;
    }

    PROPVARIANT value;
    PropVariantInit(&value);

    hr = InitPropVariantFromString(
        appId.c_str(),
        &value);

    if (SUCCEEDED(hr)) {
        hr = propertyStore->SetValue(
            PKEY_AppUserModel_ID,
            value);
    }

    if (SUCCEEDED(hr)) {
        hr = propertyStore->Commit();
    }

    PropVariantClear(&value);
    propertyStore->Release();

    return hr;
}

static HRESULT CreateSeparatorShortcut(
    const SeparatorSetting& separator,
    const std::wstring& shortcutPath) {
    IShellLinkW* shellLink = nullptr;

    HRESULT hr = CoCreateInstance(
        CLSID_ShellLink,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&shellLink));

    if (FAILED(hr)) {
        return hr;
    }

    wchar_t systemDirectory[MAX_PATH] = {};

    UINT systemDirectoryLength =
        GetSystemDirectoryW(
            systemDirectory,
            ARRAYSIZE(systemDirectory));

    if (!systemDirectoryLength ||
        systemDirectoryLength >= ARRAYSIZE(systemDirectory)) {
        shellLink->Release();
        return HRESULT_FROM_WIN32(GetLastError());
    }

    std::wstring target =
        JoinPath(systemDirectory, L"systray.exe");
    bool useCmdFallback = !FileExists(target);

    if (useCmdFallback) {
        target = JoinPath(systemDirectory, L"cmd.exe");
        if (!FileExists(target)) {
            shellLink->Release();
            return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
        }
    }

    // systray.exe is an inert Windows stub, so a stranded shortcut doesn't
    // launch a console or perform an action if it is clicked. It isn't a
    // documented Windows 11 contract, so retain a hidden, immediately exiting
    // command processor as a compatibility fallback.
    hr = shellLink->SetPath(target.c_str());

    if (SUCCEEDED(hr) && useCmdFallback) {
        hr = shellLink->SetArguments(L"/d /c exit");
    }

    if (SUCCEEDED(hr)) {
        hr = shellLink->SetShowCmd(SW_HIDE);
    }

    if (SUCCEEDED(hr)) {
        hr = shellLink->SetIconLocation(
            g_bundledIconPath.c_str(),
            0);
    }

    if (SUCCEEDED(hr)) {
        hr = shellLink->SetDescription(
            separator.identity.c_str());
    }

    // Give every separator a distinct AppUserModelID so the Shell considers
    // them distinct taskbar identities even though they share the same inert
    // launch target.
    if (SUCCEEDED(hr)) {
        hr = SetShortcutAppId(
            shellLink,
            separator.identity);
    }

    if (SUCCEEDED(hr)) {
        IPersistFile* persistFile = nullptr;

        hr = shellLink->QueryInterface(
            IID_PPV_ARGS(&persistFile));

        if (SUCCEEDED(hr)) {
            hr = persistFile->Save(
                shortcutPath.c_str(),
                TRUE);

            persistFile->Release();
        }
    }

    if (SUCCEEDED(hr)) {
        // The shortcut has just been recreated after any required icon refresh.
        // Notify the Shell about this exact item as a targeted hint; don't
        // globally invalidate Explorer's icon/association caches.
        SHChangeNotify(
            SHCNE_UPDATEITEM,
            SHCNF_PATHW | SHCNF_FLUSHNOWAIT,
            shortcutPath.c_str(),
            nullptr);
    }

    shellLink->Release();

    return hr;
}

// -----------------------------------------------------------------------------
// PIDL + PinManager helpers.
// -----------------------------------------------------------------------------

static HRESULT GetPidlForPath(
    const std::wstring& path,
    PIDLIST_ABSOLUTE* pidl) {
    *pidl = nullptr;

    SFGAOF attrs = 0;

    HRESULT hr = SHParseDisplayName(
        path.c_str(),
        nullptr,
        pidl,
        0,
        &attrs);

    return hr;
}

static HRESULT CreatePinManager(
    IPinManagerInterop3** pinManager) {
    *pinManager = nullptr;

    IPinManagerInterop2* interop2 = nullptr;

    HRESULT hr = CoCreateInstance(
        CLSID_PinManager,
        nullptr,
        CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER,
        IID_IPinManagerInterop2,
        reinterpret_cast<void**>(&interop2));

    if (FAILED(hr)) {
        Wh_Log(
            L"[PIN] CoCreateInstance(IPinManagerInterop2) "
            L"failed hr=0x%08X",
            static_cast<unsigned int>(hr));
        return hr;
    }

    hr = interop2->QueryInterface(
        IID_IPinManagerInterop3,
        reinterpret_cast<void**>(pinManager));

    interop2->Release();

    if (FAILED(hr)) {
        Wh_Log(
            L"[PIN] QueryInterface(IPinManagerInterop3) "
            L"failed hr=0x%08X",
            static_cast<unsigned int>(hr));
    }

    return hr;
}

static bool IsBackendStopRequested();
static bool IsBackendPassSuperseded();

static bool UnpinAndDeleteShortcut(
    IPinManagerInterop3* pinManager,
    const std::wstring& shortcutPath,
    const wchar_t* logCategory,
    bool recoverMissingPin = true) {
    PIDLIST_ABSOLUTE pidl = nullptr;
    HRESULT hr = GetPidlForPath(shortcutPath, &pidl);

    if (FAILED(hr) || !pidl) {
        Wh_Log(
            L"[%s] Can't resolve owned shortcut '%s'; keeping it",
            logCategory,
            shortcutPath.c_str());
        return false;
    }

    HRESULT unpinHr =
        pinManager->UnpinTaskbarItem(
            pidl,
            PMC_JUMPVIEWBROKER);

    // A shortcut can exist even if Explorer died before the matching pin.
    // Establish a known pinned state, then remove it, so such backing files
    // don't become permanent false failures in future cleanup passes.
    HRESULT pinHr = S_OK;
    if (FAILED(unpinHr) && recoverMissingPin) {
        pinHr =
            pinManager->PinItemFromTrustedCaller(
                pidl,
                PMC_TASKBANDPIN);
        if (SUCCEEDED(pinHr)) {
            unpinHr =
                pinManager->UnpinTaskbarItem(
                    pidl,
                    PMC_JUMPVIEWBROKER);
        }
    }

    CoTaskMemFree(pidl);

    if (FAILED(unpinHr)) {
        if (recoverMissingPin) {
            Wh_Log(
                L"[%s] Failed to remove owned shortcut '%s' "
                L"pinHr=0x%08X unpinHr=0x%08X",
                logCategory,
                shortcutPath.c_str(),
                static_cast<unsigned int>(pinHr),
                static_cast<unsigned int>(unpinHr));
        } else {
            Wh_Log(
                L"[%s] Failed to unpin owned shortcut '%s' "
                L"hr=0x%08X; recovery disabled after hook removal",
                logCategory,
                shortcutPath.c_str(),
                static_cast<unsigned int>(unpinHr));
        }
        return false;
    }

    if (!DeleteFileIfPresent(shortcutPath)) {
        return false;
    }

    // Pair the later targeted shortcut update with an explicit deletion hint.
    // This keeps Explorer from treating a same-path recreated .lnk as a silent
    // in-place mutation during an icon appearance refresh.
    SHChangeNotify(
        SHCNE_DELETE,
        SHCNF_PATHW | SHCNF_FLUSHNOWAIT,
        shortcutPath.c_str(),
        nullptr);
    return true;
}

static bool CleanupStaleSeparatorShortcuts(
    IPinManagerInterop3* pinManager,
    const Settings& settings) {
    std::vector<std::wstring> stalePaths;
    const auto shortcutPaths = EnumerateSeparatorShortcuts();

    size_t staleIdentityCount = 0;
    size_t staleIconCount = 0;

    ConfiguredIconDiskState iconState =
        GetConfiguredBundledIconDiskState();
    if (iconState == ConfiguredIconDiskState::Error) {
        // Don't destroy otherwise-good pins if WIC or storage is temporarily
        // unavailable. A later backend retry can reassess the same state.
        Wh_Log(
            L"[ICON] Can't verify configured separator icon generation; leaving live shortcuts untouched for this retry");
        return false;
    }

    const bool iconContentsStale =
        iconState == ConfiguredIconDiskState::Mismatch;

    if (iconContentsStale && !shortcutPaths.empty()) {
        Wh_Log(
            L"[ICON] Current separator icon generation doesn't match configured appearance; recycling separator shortcuts before regenerating it");
    }

    for (const auto& path : shortcutPaths) {
        // Exact shell identity is intentional here. The durable stable ID may
        // match, but an old/no-generation .lnk must still be unpinned and deleted
        // before the current generation is created. This bounds storage to one
        // shortcut generation after every successful convergence.
        bool identityIsDesired =
            IsIdentityInSettings(
                settings,
                GetShortcutIdentity(path));

        if (!identityIsDesired) {
            stalePaths.push_back(path);
            staleIdentityCount++;
            continue;
        }

        // The current generation ICO is the single authoritative artwork file. Never
        // replace its bytes underneath a live pin: if its contents changed, destroy
        // every desired backing shortcut first and recreate the pins afterward.
        // Exact shell-identity matching above independently catches every old/no-
        // generation .lnk so upgrades cannot accumulate shortcut generations.
        if (iconContentsStale ||
            !ShortcutUsesConfiguredBundledIcon(path)) {
            stalePaths.push_back(path);
            staleIconCount++;
        }
    }

    if (stalePaths.empty()) {
        return true;
    }

    Wh_Log(
        L"[SYNC] Recycling %zu shortcut(s): staleIdentity=%zu staleIcon=%zu",
        stalePaths.size(),
        staleIdentityCount,
        staleIconCount);

    bool success = true;
    for (auto it = stalePaths.rbegin();
         it != stalePaths.rend();
         ++it) {
        if (IsBackendPassSuperseded()) {
            return false;
        }

        if (!UnpinAndDeleteShortcut(
                pinManager,
                *it,
                L"SYNC")) {
            success = false;
        }
    }

    return success;
}

// -----------------------------------------------------------------------------
// Creation / positioning.
// -----------------------------------------------------------------------------

static bool PrepareSeparatorFiles(
    const Settings& settings,
    const Settings& appliedSettings,
    const SeparatorSetting& refreshPulse,
    bool lifecycleRefreshRequested,
    std::vector<std::wstring>* identitiesToPin,
    bool* recoveryDetected) {
    if (IsBackendPassSuperseded()) {
        return false;
    }

    identitiesToPin->clear();
    *recoveryDetected = false;

    if (settings.separators.empty()) {
        Wh_Log(L"[PIN] No separators configured");
        return true;
    }

    // Exactly one generated ICO is authoritative for the current shell generation.
    // CleanupStaleSeparatorShortcuts removes old shortcut generations first, and
    // stale ICO generations are purged only after convergence succeeds.
    ConfiguredIconDiskState iconState =
        GetConfiguredBundledIconDiskState();
    if (iconState == ConfiguredIconDiskState::Error) {
        Wh_Log(L"[PIN] Failed to verify current separator icon generation");
        return false;
    }
    if (iconState == ConfiguredIconDiskState::Mismatch) {
        if (!WriteConfiguredBundledSeparatorIcon()) {
            Wh_Log(L"[PIN] Failed to create current separator icon generation");
            return false;
        }

        SHChangeNotify(
            SHCNE_UPDATEITEM,
            SHCNF_PATHW | SHCNF_FLUSHNOWAIT,
            g_bundledIconPath.c_str(),
            nullptr);
    }

    // Shortcut/AUMID identity includes the appearance generation. Within one
    // generation, surviving shortcuts remain immutable; across generations the
    // stale cleanup above destroys them before these fresh paths are created.
    for (const auto& separator : settings.separators) {
        if (IsBackendPassSuperseded()) {
            return false;
        }

        std::wstring shortcutPath =
            GetSeparatorShortcutPath(separator);
        bool shortcutCreated = false;

        if (!FileExists(shortcutPath)) {
            HRESULT hr =
                CreateSeparatorShortcut(
                    separator,
                    shortcutPath);

            if (FAILED(hr)) {
                Wh_Log(
                    L"[PIN] Failed to create separator #%d hr=0x%08X",
                    separator.ordinal,
                    static_cast<unsigned int>(hr));
                return false;
            }

            shortcutCreated = true;
        }

        // Pin only identities that aren't part of the last converged snapshot,
        // plus a survivor whose backing file had to be recovered. This keeps
        // ordinary add/remove/reorder operations from re-asserting every
        // already-correct pinned item.
        const SeparatorSetting* appliedSeparator =
            FindSeparatorByStableId(
                appliedSettings,
                separator.stableId);

        if (shortcutCreated ||
            !appliedSeparator ||
            appliedSeparator->identity != separator.identity) {
            identitiesToPin->push_back(
                separator.identity);
        }

        // Recreating the backing shortcut for a separator that belonged to the
        // last converged snapshot is recovery, not an ordinary Add. That is the
        // only non-lifecycle convergence which still needs the transient pulse.
        if (shortcutCreated &&
            appliedSeparator &&
            appliedSeparator->identity == separator.identity) {
            *recoveryDetected = true;
        }
    }

    if (IsBackendPassSuperseded()) {
        return false;
    }

    if (lifecycleRefreshRequested || *recoveryDetected) {
        // The refresh helper is intentionally transient, so recreating it is
        // safe. Ordinary Add/Remove passes never create it anymore.
        std::wstring refreshShortcutPath =
            GetSeparatorShortcutPath(refreshPulse);
        HRESULT refreshHr =
            CreateSeparatorShortcut(
                refreshPulse,
                refreshShortcutPath);

        if (FAILED(refreshHr)) {
            Wh_Log(
                L"[REFRESH] Failed to create pin-pulse shortcut hr=0x%08X",
                static_cast<unsigned int>(refreshHr));
            return false;
        }
    }

    return true;
}

static bool InitializeTaskbarDllHooks() {
    if (HMODULE taskbarDll = GetModuleHandleW(L"taskbar.dll")) {
        return InstallTaskbarDllHooks(taskbarDll, false);
    }

    Wh_Log(
        L"[TASKBAR] taskbar.dll isn't loaded yet; "
        L"installing LoadLibraryExW watcher");
    return InstallLoadLibraryWatcher();
}

static bool IsBackendStopRequested() {
    return g_currentBackendStopEvent &&
        WaitForSingleObject(
            g_currentBackendStopEvent,
            0) == WAIT_OBJECT_0;
}

static bool IsBackendReconcileRequested() {
    return g_currentBackendWakeEvent &&
        WaitForSingleObject(
            g_currentBackendWakeEvent,
            0) == WAIT_OBJECT_0;
}

static bool IsBackendPassSuperseded() {
    return IsBackendStopRequested() ||
        IsBackendReconcileRequested();
}

enum class BackendWaitResult {
    Timeout,
    Stop,
    Reconcile,
    Failed,
};

static BackendWaitResult WaitForBackendStopOrReconcile(
    DWORD timeout) {
    HANDLE events[] = {
        g_currentBackendStopEvent,
        g_currentBackendWakeEvent,
    };

    if (!events[0] || !events[1]) {
        return BackendWaitResult::Failed;
    }

    DWORD result = WaitForMultipleObjects(
        ARRAYSIZE(events),
        events,
        FALSE,
        timeout);

    switch (result) {
        case WAIT_TIMEOUT:
            return BackendWaitResult::Timeout;
        case WAIT_OBJECT_0:
            return BackendWaitResult::Stop;
        case WAIT_OBJECT_0 + 1:
            return BackendWaitResult::Reconcile;
        default:
            return BackendWaitResult::Failed;
    }
}

static bool PinSeparators(
    IPinManagerInterop3* pinManager,
    const Settings& settings,
    const std::vector<std::wstring>& identitiesToPin) {
    bool success = true;

    // Only new/recovered identities need a pin mutation. Existing stable pins
    // are left untouched and are handled solely by the positioning pass.
    for (const auto& separator : settings.separators) {
        if (std::find(
                identitiesToPin.begin(),
                identitiesToPin.end(),
                separator.identity) == identitiesToPin.end()) {
            continue;
        }

        if (IsBackendPassSuperseded()) {
            return false;
        }

        std::wstring shortcutPath =
            GetSeparatorShortcutPath(separator);

        PIDLIST_ABSOLUTE pidl = nullptr;

        HRESULT hr = GetPidlForPath(
            shortcutPath,
            &pidl);

        if (FAILED(hr) || !pidl) {
            Wh_Log(
                L"[PIN] Can't resolve separator #%d hr=0x%08X",
                separator.ordinal,
                static_cast<unsigned int>(hr));
            success = false;
            continue;
        }

        HRESULT pinHr =
            pinManager->PinItemFromTrustedCaller(
                pidl,
                PMC_TASKBANDPIN);

        if (FAILED(pinHr)) {
            Wh_Log(
                L"[PIN] Failed to pin separator #%d hr=0x%08X",
                separator.ordinal,
                static_cast<unsigned int>(pinHr));
            success = false;
        }

        CoTaskMemFree(pidl);
    }

    return success;
}

static bool PositionSeparators(
    IPinManagerInterop3* pinManager,
    const Settings& settings) {
    bool success = true;

    // Moving in ascending destination order makes multiple requested positions
    // deterministic as items are pulled forward from their initial appended
    // locations.
    std::vector<SeparatorSetting> moveOrder =
        settings.separators;

    std::stable_sort(
        moveOrder.begin(),
        moveOrder.end(),
        [](const SeparatorSetting& a, const SeparatorSetting& b) {
            return a.targetIndex < b.targetIndex;
        });

    for (const auto& separator : moveOrder) {
        if (IsBackendPassSuperseded()) {
            return false;
        }

        // targetIndex=-1 is an intentional unanchored state. Leave the
        // separator where Windows appended it until the user drags it once.
        if (separator.targetIndex < 0) {
            Wh_Log(
                L"[MOVE] Separator #%d left at native appended position",
                separator.ordinal);
            continue;
        }

        std::wstring shortcutPath =
            GetSeparatorShortcutPath(separator);

        PIDLIST_ABSOLUTE pidl = nullptr;

        HRESULT hr = GetPidlForPath(
            shortcutPath,
            &pidl);

        if (FAILED(hr) || !pidl) {
            Wh_Log(
                L"[MOVE] Can't resolve separator #%d hr=0x%08X",
                separator.ordinal,
                static_cast<unsigned int>(hr));
            success = false;
            continue;
        }

        HRESULT moveHr =
            pinManager->MoveTaskbarPin(
                pidl,
                separator.targetIndex,
                PMC_TASKBANDREORDER);

        if (FAILED(moveHr)) {
            Wh_Log(
                L"[MOVE] Failed to move separator #%d to index=%d "
                L"hr=0x%08X",
                separator.ordinal,
                separator.targetIndex,
                static_cast<unsigned int>(moveHr));
            success = false;
        }

        CoTaskMemFree(pidl);
    }

    return success;
}

static bool PulseTaskbarPinList(
    IPinManagerInterop3* pinManager,
    const SeparatorSetting& refreshPulse) {
    if (IsBackendPassSuperseded()) {
        return false;
    }

    std::wstring shortcutPath =
        GetSeparatorShortcutPath(refreshPulse);

    PIDLIST_ABSOLUTE pidl = nullptr;
    HRESULT hr = GetPidlForPath(shortcutPath, &pidl);

    if (FAILED(hr) || !pidl) {
        Wh_Log(
            L"[REFRESH] Can't resolve pin-pulse shortcut hr=0x%08X",
            static_cast<unsigned int>(hr));
        return false;
    }

    HRESULT pinHr =
        pinManager->PinItemFromTrustedCaller(
            pidl,
            PMC_TASKBANDPIN);

    if (FAILED(pinHr)) {
        Wh_Log(
            L"[REFRESH] Failed to pin transient refresh item hr=0x%08X",
            static_cast<unsigned int>(pinHr));
        CoTaskMemFree(pidl);
        return false;
    }

    // Once the helper is pinned, always attempt the matching unpin even if an
    // unload was requested in between. Wh_ModBeforeUninit joins this worker
    // before general cleanup, so completing the pair can't race shutdown.
    HRESULT unpinHr =
        pinManager->UnpinTaskbarItem(
            pidl,
            PMC_JUMPVIEWBROKER);

    CoTaskMemFree(pidl);

    if (SUCCEEDED(unpinHr)) {
        return DeleteFileIfPresent(shortcutPath);
    }

    Wh_Log(
        L"[REFRESH] Failed to unpin transient refresh item hr=0x%08X",
        static_cast<unsigned int>(unpinHr));

    // Keep the shortcut when unpinning fails so a later retry or unload can
    // resolve the same PIDL and remove the helper safely.
    return false;
}

static bool ConvergeSeparatorPins(
    const Settings& settings,
    const Settings& appliedSettings,
    const SeparatorSetting& refreshPulse,
    bool lifecycleRefreshRequested) {
    if (settings.separators.empty() &&
        EnumerateSeparatorShortcuts().empty()) {
        DeleteAllBundledIconArtifacts();
        return true;
    }

    constexpr int kConvergeAttempts = 5;
    constexpr DWORD kInitialRetryDelay = 250;
    constexpr DWORD kRetryBackoff = 2;
    DWORD retryDelay = kInitialRetryDelay;
    bool staleCleanupComplete = false;
    bool filesPrepared = false;
    bool recoveryDetected = false;
    std::vector<std::wstring> identitiesToPin;

    for (int attempt = 1;
         attempt <= kConvergeAttempts;
         ++attempt) {
        if (IsBackendStopRequested()) {
            Wh_Log(L"[SYNC] Separator reconciliation cancelled");
            return false;
        }

        if (IsBackendReconcileRequested()) {
            Wh_Log(L"[SYNC] Reconciliation superseded by newer settings");
            return false;
        }

        Wh_Log(
            L"[SYNC] Separator reconciliation attempt %d/%d",
            attempt,
            kConvergeAttempts);

        IPinManagerInterop3* pinManager = nullptr;
        HRESULT hr = CreatePinManager(&pinManager);

        bool staleShortcutsRemoved = staleCleanupComplete;
        bool filesReady = filesPrepared;
        bool pinsReady = false;
        bool positioned = false;
        bool refreshed = false;

        if (SUCCEEDED(hr) && pinManager) {
            // Storage is the durable list of shortcut artifacts this mod owns.
            // Remove only identities not present in the desired snapshot;
            // unchanged separators are never unpinned during live refresh.
            if (!staleCleanupComplete) {
                staleCleanupComplete =
                    CleanupStaleSeparatorShortcuts(
                        pinManager,
                        settings);
                staleShortcutsRemoved = staleCleanupComplete;
            }

            if (staleShortcutsRemoved && !filesPrepared) {
                filesPrepared =
                    PrepareSeparatorFiles(
                        settings,
                        appliedSettings,
                        refreshPulse,
                        lifecycleRefreshRequested,
                        &identitiesToPin,
                        &recoveryDetected);
                filesReady = filesPrepared;
            }

            if (staleShortcutsRemoved && filesReady &&
                settings.separators.empty()) {
                DeleteAllBundledIconArtifacts();
                pinsReady = true;
                positioned = true;
                refreshed = true;
            } else if (staleShortcutsRemoved && filesReady) {
                pinsReady =
                    PinSeparators(
                        pinManager,
                        settings,
                        identitiesToPin);

                if (pinsReady) {
                    positioned =
                        PositionSeparators(
                            pinManager,
                            settings);

                    if (positioned) {
                        if (lifecycleRefreshRequested || recoveryDetected) {
                            Wh_Log(
                                L"[REFRESH] Pulsing pin list reason=%s",
                                lifecycleRefreshRequested
                                    ? (recoveryDetected
                                           ? L"taskbar-lifecycle+recovery"
                                           : L"taskbar-lifecycle")
                                    : L"recovery");
                            refreshed =
                                PulseTaskbarPinList(
                                    pinManager,
                                    refreshPulse);
                        } else {
                            // Add, remove and ordinary reorder persistence are
                            // already backed by a real native pin-list mutation.
                            refreshed = true;
                        }
                    }
                } else {
                    Wh_Log(
                        L"[SYNC] Pin pass incomplete; skipping move pass");
                }
            }

            pinManager->Release();
        }

        if (staleShortcutsRemoved && filesReady &&
            pinsReady && positioned && refreshed) {
            // Only now is it safe to remove obsolete icon generations: every
            // surviving .lnk has been recreated/verified against the one current
            // authoritative ICO. A failed/partial pass deliberately keeps old
            // artifacts because a stranded shortcut may still reference one.
            if (!settings.separators.empty() &&
                !DeleteStaleBundledIconArtifacts()) {
                // Dead icon generations are no longer referenced by any owned
                // shortcut after convergence. A transient deletion failure is
                // therefore observable but must not turn a healthy pin state
                // into a failed reconciliation; later passes/teardown retry it.
                Wh_Log(
                    L"[ICON] Some obsolete separator icon artifacts couldn't be deleted; keeping converged pin state");
            }

            Wh_Log(
                L"[SYNC] Separator state converged on attempt %d",
                attempt);
            return true;
        }

        if (IsBackendStopRequested()) {
            Wh_Log(L"[SYNC] Separator reconciliation cancelled");
            return false;
        }

        if (attempt < kConvergeAttempts) {
            Wh_Log(
                L"[SYNC] Reconciliation attempt failed; "
                L"retrying in %u ms",
                retryDelay);

            BackendWaitResult waitResult =
                WaitForBackendStopOrReconcile(retryDelay);

            if (waitResult == BackendWaitResult::Stop) {
                Wh_Log(L"[SYNC] Separator reconciliation cancelled");
                return false;
            }

            if (waitResult == BackendWaitResult::Reconcile) {
                Wh_Log(L"[SYNC] Reconciliation superseded by newer settings");
                return false;
            }

            if (waitResult == BackendWaitResult::Failed) {
                Wh_Log(
                    L"[SYNC] Reconciliation retry wait failed error=%u",
                    GetLastError());
                return false;
            }

            retryDelay *= kRetryBackoff;
        }
    }

    Wh_Log(
        L"[SYNC] Separator state did not converge after %d attempts",
        kConvergeAttempts);
    return false;
}

// -----------------------------------------------------------------------------
// Destruction / cleanup.
// -----------------------------------------------------------------------------

static bool SeparatorShortcutArtifactsExist() {
    return !EnumerateSeparatorShortcuts().empty();
}

static bool UnpinAndDeleteSeparators(bool recoverMissingPins) {
    std::vector<std::wstring> shortcutPaths =
        EnumerateSeparatorShortcuts();

    if (shortcutPaths.empty()) {
        DeleteAllBundledIconArtifacts();
        return true;
    }

    IPinManagerInterop3* pinManager = nullptr;

    HRESULT hr = CreatePinManager(&pinManager);

    if (FAILED(hr) || !pinManager) {
        Wh_Log(
            L"[CLEANUP] Can't acquire PinManager; "
            L"leaving backing files in place to avoid broken pins");
        return false;
    }

    bool allUnpinned = true;

    // Storage is authoritative: remove current separators, stale settings
    // identities, and a refresh helper left by an interrupted pulse alike.
    for (auto it = shortcutPaths.rbegin();
         it != shortcutPaths.rend();
         ++it) {
        if (!UnpinAndDeleteShortcut(
                pinManager,
                *it,
                L"CLEANUP",
                recoverMissingPins)) {
            allUnpinned = false;
        }
    }

    pinManager->Release();

    if (allUnpinned) {
        DeleteAllBundledIconArtifacts();
    } else {
        Wh_Log(
            L"[CLEANUP] At least one unpin failed; "
            L"keeping mod-owned shortcuts and all icon variants in place");
    }

    return allUnpinned;
}

// -----------------------------------------------------------------------------
// Windhawk lifetime.
// -----------------------------------------------------------------------------

static HWND FindCurrentProcessTaskbarWnd();

struct BackendThreadParameters {
    HANDLE stopEvent;
    HANDLE wakeEvent;
};

static DWORD WINAPI BackendThreadProc(void* parameter) {
    auto* parameters =
        static_cast<BackendThreadParameters*>(parameter);
    HANDLE stopEvent = parameters->stopEvent;
    HANDLE wakeEvent = parameters->wakeEvent;
    delete parameters;

    g_currentBackendStopEvent = stopEvent;
    g_currentBackendWakeEvent = wakeEvent;

    Wh_Log(L"[INIT] Separator backend worker starting");

    HRESULT hrInit =
        CoInitializeEx(
            nullptr,
            COINIT_APARTMENTTHREADED);

    if (FAILED(hrInit)) {
        Wh_Log(
            L"[INIT] Backend worker CoInitializeEx failed hr=0x%08X",
            static_cast<unsigned int>(hrInit));
        g_currentBackendStopEvent = nullptr;
        g_currentBackendWakeEvent = nullptr;
        return 0;
    }

    // A failed state write is retried with bounded exponential backoff. After
    // the final retry, stay asleep until a fresh explicit wake (Add/Remove/
    // drag/settings/lifecycle) rather than hammering the storage path forever.
    static constexpr DWORD kStateWriteRetryDelaysMs[] = {
        250,
        500,
        1000,
        2000,
        4000,
    };
    size_t stateWriteFailureCount = 0;
    unsigned long long handledTaskbarRefreshGeneration = 0;

    for (;;) {
        // A request that arrived before this iteration is represented by the
        // snapshot we are about to take. A newer request arriving afterwards
        // re-signals the manual-reset event and supersedes this pass.
        ResetEvent(wakeEvent);

        Settings settings;
        Settings appliedSettings;
        SeparatorSetting refreshPulse;
        bool stateDirty = false;
        const unsigned long long taskbarRefreshGeneration =
            g_taskbarRefreshGeneration.load(std::memory_order_acquire);
        const bool lifecycleRefreshRequested =
            taskbarRefreshGeneration != handledTaskbarRefreshGeneration;

        {
            // Keep the established mutation->settings lock order, but only for
            // the cheap in-memory snapshot. Disk I/O happens after both locks
            // have been released.
            std::lock_guard<std::mutex> mutationLock(
                g_settingsMutationMutex);
            std::shared_lock lock(g_settingsMutex);
            settings = g_settings;
            appliedSettings = g_appliedSettings;
            refreshPulse = g_refreshPulseSetting;
            stateDirty = g_separatorStateDirty;
        }

        bool stateReady = true;
        if (stateDirty) {
            stateReady = SaveSeparatorStateFile(settings);

            if (stateReady) {
                stateWriteFailureCount = 0;

                bool snapshotStillCurrent = false;
                {
                    std::lock_guard<std::mutex> mutationLock(
                        g_settingsMutationMutex);
                    std::shared_lock lock(g_settingsMutex);
                    snapshotStillCurrent =
                        SettingsSnapshotsEqual(
                            settings,
                            g_settings);
                    if (snapshotStillCurrent) {
                        g_separatorStateDirty = false;
                    }
                }

                if (!snapshotStillCurrent) {
                    Wh_Log(
                        L"[STATE] Persisted snapshot was superseded; "
                        L"writing the newer state next");
                    continue;
                }

                Wh_Log(L"[STATE] Persisted separator state on backend worker");
            } else if (!IsBackendStopRequested()) {
                stateWriteFailureCount++;
                Wh_Log(
                    L"[STATE] Failed to persist separator state (failure %zu); "
                    L"PinManager convergence deferred",
                    stateWriteFailureCount);
            }
        } else {
            stateWriteFailureCount = 0;
        }

        if (IsBackendStopRequested()) {
            break;
        }

        bool needsReconcile =
            lifecycleRefreshRequested ||
            !g_backendHasConverged.load(std::memory_order_acquire) ||
            SettingsRequireBackendReconcile(
                appliedSettings,
                settings);

        bool success = stateReady;
        if (stateReady && needsReconcile) {
            success =
                ConvergeSeparatorPins(
                    settings,
                    appliedSettings,
                    refreshPulse,
                    lifecycleRefreshRequested);

            if (success) {
                {
                    std::unique_lock lock(g_settingsMutex);

                    // Record what the pin backend actually converged to. If
                    // only presentation/logging metadata changed while it was
                    // working, adopt the newer snapshot too because no further
                    // PinManager work is required.
                    g_appliedSettings = settings;

                    if (!SettingsRequireBackendReconcile(
                            settings,
                            g_settings)) {
                        g_appliedSettings = g_settings;
                        g_backendHasConverged.store(
                            true,
                            std::memory_order_release);
                    } else {
                        g_backendHasConverged.store(
                            false,
                            std::memory_order_release);
                    }
                }

                // Consume exactly the lifecycle generation this pass observed.
                // If another reconstruction arrived while convergence was in
                // flight, its larger generation remains pending for the next
                // iteration (and its wake event supersedes this pass as usual).
                if (lifecycleRefreshRequested) {
                    handledTaskbarRefreshGeneration =
                        taskbarRefreshGeneration;
                }

                // Directory enumeration belongs to the worker as well. No
                // taskbar UI callback scans mod storage anymore.
                RefreshStoredSeparatorSettings();
            }
        }

        if (!success && !IsBackendStopRequested()) {
            g_backendHasConverged.store(
                false,
                std::memory_order_release);

            if (!IsBackendReconcileRequested()) {
                if (stateReady) {
                    Wh_Log(
                        L"[SYNC] One or more separator operations failed; "
                        L"waiting for another settings/retry request");
                } else if (
                    stateWriteFailureCount <=
                    ARRAYSIZE(kStateWriteRetryDelaysMs)) {
                    Wh_Log(
                        L"[STATE] Retrying state persistence in %u ms",
                        kStateWriteRetryDelaysMs[
                            stateWriteFailureCount - 1]);
                } else {
                    Wh_Log(
                        L"[STATE] State persistence retry limit reached; "
                        L"waiting for the next explicit wake");
                }
            }
        }

        if (IsBackendStopRequested()) {
            break;
        }

        HANDLE events[] = {
            stopEvent,
            wakeEvent,
        };

        DWORD timeout = INFINITE;
        if (!stateReady &&
            stateWriteFailureCount > 0 &&
            stateWriteFailureCount <=
                ARRAYSIZE(kStateWriteRetryDelaysMs)) {
            timeout =
                kStateWriteRetryDelaysMs[
                    stateWriteFailureCount - 1];
        }

        DWORD waitResult =
            WaitForMultipleObjects(
                ARRAYSIZE(events),
                events,
                FALSE,
                timeout);

        if (waitResult == WAIT_OBJECT_0) {
            break;
        }

        if (waitResult == WAIT_TIMEOUT && !stateReady) {
            continue;
        }

        if (waitResult == WAIT_OBJECT_0 + 1) {
            // A real user/settings/lifecycle request gets a fresh retry budget.
            stateWriteFailureCount = 0;
            continue;
        }

        Wh_Log(
            L"[SYNC] Backend wait failed result=0x%08X error=%u",
            waitResult,
            GetLastError());
        break;
    }

    CoUninitialize();
    g_currentBackendStopEvent = nullptr;
    g_currentBackendWakeEvent = nullptr;

    Wh_Log(L"[INIT] Separator backend worker finished");
    return 0;
}

static HWND FindCurrentProcessTaskbarWnd() {
    HWND taskbarWnd = nullptr;

    EnumWindows(
        [](HWND window, LPARAM lParam) -> BOOL {
            DWORD processId = 0;
            wchar_t className[32] = {};
            if (GetWindowThreadProcessId(window, &processId) &&
                processId == GetCurrentProcessId() &&
                GetClassNameW(
                    window,
                    className,
                    ARRAYSIZE(className)) &&
                _wcsicmp(className, L"Shell_TrayWnd") == 0) {
                *reinterpret_cast<HWND*>(lParam) = window;
                return FALSE;
            }

            return TRUE;
        },
        reinterpret_cast<LPARAM>(&taskbarWnd));

    return taskbarWnd;
}

static bool CleanupSeparatorArtifacts(bool recoverMissingPins) {
    // Icon files don't affect the pin list. If no owned shortcuts survive, no
    // separator can still depend on any generated/legacy icon variant, so clean
    // that cache even during the brief part of Explorer teardown where
    // Shell_TrayWnd is already gone.
    if (!SeparatorShortcutArtifactsExist()) {
        DeleteAllBundledIconArtifacts();
        return true;
    }

    // Shared mod storage may be visible to several explorer.exe instances.
    // Only the process that owns Shell_TrayWnd may mutate the taskbar pin list.
    // If shortcuts do survive and this process isn't the owner, keep *all* icon
    // variants too: one of those shortcuts can legitimately reference an older
    // appearance after an interrupted reload.
    if (!FindCurrentProcessTaskbarWnd()) {
        return true;
    }

    HRESULT hrInit =
        CoInitializeEx(
            nullptr,
            COINIT_APARTMENTTHREADED);

    const bool shouldUninitialize = SUCCEEDED(hrInit);

    if (hrInit != RPC_E_CHANGED_MODE && FAILED(hrInit)) {
        Wh_Log(
            L"[CLEANUP] CoInitializeEx failed hr=0x%08X; "
            L"can't safely remove separators",
            static_cast<unsigned int>(hrInit));
        return false;
    }

    bool success =
        UnpinAndDeleteSeparators(recoverMissingPins);

    if (shouldUninitialize) {
        CoUninitialize();
    }

    return success;
}

static bool StartBackendWorkerLocked() {
    if (g_backendStopped) {
        return true;
    }

    if (g_backendThread) {
        DWORD threadState =
            WaitForSingleObject(
                g_backendThread,
                0);

        if (threadState == WAIT_TIMEOUT) {
            return true;
        }

        if (threadState == WAIT_FAILED) {
            Wh_Log(
                L"[INIT] Backend worker handle wait failed error=%u; "
                L"recreating worker",
                GetLastError());
        }

        // The long-lived worker should normally only exit during shutdown.
        // If initialization/waiting failed, allow a later readiness/settings
        // event to create a fresh worker.
        CloseHandle(g_backendThread);
        g_backendThread = nullptr;

        if (g_backendWakeEvent) {
            CloseHandle(g_backendWakeEvent);
            g_backendWakeEvent = nullptr;
        }

        if (g_backendStopEvent) {
            CloseHandle(g_backendStopEvent);
            g_backendStopEvent = nullptr;
        }
    }

    g_backendStopEvent =
        CreateEventW(
            nullptr,
            TRUE,
            FALSE,
            nullptr);

    if (!g_backendStopEvent) {
        Wh_Log(
            L"[INIT] CreateEvent for backend stop failed error=%u",
            GetLastError());
        return false;
    }

    g_backendWakeEvent =
        CreateEventW(
            nullptr,
            TRUE,
            FALSE,
            nullptr);

    if (!g_backendWakeEvent) {
        Wh_Log(
            L"[INIT] CreateEvent for backend wake failed error=%u",
            GetLastError());
        CloseHandle(g_backendStopEvent);
        g_backendStopEvent = nullptr;
        return false;
    }

    auto* parameters =
        new (std::nothrow) BackendThreadParameters{
            .stopEvent = g_backendStopEvent,
            .wakeEvent = g_backendWakeEvent,
        };

    if (!parameters) {
        Wh_Log(L"[INIT] Failed to allocate backend worker parameters");
        CloseHandle(g_backendWakeEvent);
        CloseHandle(g_backendStopEvent);
        g_backendWakeEvent = nullptr;
        g_backendStopEvent = nullptr;
        return false;
    }

    g_backendThread =
        CreateThread(
            nullptr,
            0,
            BackendThreadProc,
            parameters,
            0,
            nullptr);

    if (!g_backendThread) {
        Wh_Log(
            L"[INIT] CreateThread for backend worker failed error=%u",
            GetLastError());
        delete parameters;
        CloseHandle(g_backendWakeEvent);
        CloseHandle(g_backendStopEvent);
        g_backendWakeEvent = nullptr;
        g_backendStopEvent = nullptr;
        return false;
    }

    return true;
}

static void StartBackendWorker(bool refreshIfAlreadyRunning) {
    std::lock_guard<std::mutex> lock(g_lifecycleMutex);

    if (g_unloading || g_backendStopped) {
        return;
    }

    bool workerWasRunning =
        g_backendThread &&
        WaitForSingleObject(
            g_backendThread,
            0) == WAIT_TIMEOUT;

    // A newly created backend always represents initial taskbar attachment. A
    // repeated TrayUI::StartTaskbar is reconstruction and requests another
    // lifecycle generation. Wh_ModAfterInit passes false so it can't duplicate
    // a startup already observed through TrayUI::StartTaskbar.
    const bool lifecycleRefreshRequested =
        !workerWasRunning || refreshIfAlreadyRunning;

    if (lifecycleRefreshRequested) {
        g_taskbarRefreshGeneration.fetch_add(
            1,
            std::memory_order_acq_rel);
        g_backendHasConverged.store(
            false,
            std::memory_order_release);
    }

    if (!StartBackendWorkerLocked()) {
        Wh_Log(L"[INIT] Failed to start separator backend worker");
        return;
    }

    if (workerWasRunning &&
        lifecycleRefreshRequested &&
        g_backendWakeEvent) {
        SetEvent(g_backendWakeEvent);
    }
}

static void RequestBackendReconcile() {
    std::lock_guard<std::mutex> lock(g_lifecycleMutex);

    if (g_unloading || g_backendStopped) {
        return;
    }

    // Preserve the Stage A readiness policy: if the taskbar hasn't been
    // created yet, TrayUI::StartTaskbar will start the worker later and it
    // will consume the newest desired settings snapshot.
    if (!g_backendThread &&
        !FindCurrentProcessTaskbarWnd()) {
        return;
    }

    // Always go through StartBackendWorkerLocked. Besides creating a missing
    // worker, it notices a worker that exited unexpectedly and recreates it.
    if (!StartBackendWorkerLocked()) {
        Wh_Log(
            L"[SYNC] Failed to start separator backend worker");
        return;
    }

    if (g_backendWakeEvent) {
        SetEvent(g_backendWakeEvent);
    }
}


static bool SignalBackendWorker() {
    std::lock_guard<std::mutex> lock(g_lifecycleMutex);

    if (g_unloading || g_backendStopped ||
        !g_backendThread || !g_backendWakeEvent) {
        return false;
    }

    if (WaitForSingleObject(
            g_backendThread,
            0) != WAIT_TIMEOUT) {
        return false;
    }

    return SetEvent(g_backendWakeEvent) != FALSE;
}

static void QueueBackendWork() {
    // Native taskbar callbacks normally arrive after TrayUI::StartTaskbar, so
    // the hot path is a single SetEvent. Fall back to the existing worker
    // readiness logic only if the worker is unexpectedly absent.
    if (!SignalBackendWorker()) {
        RequestBackendReconcile();
    }
}

static void AddSeparatorFromUserAction() {
    if (g_unloading ||
        g_internalCleanupInProgress.load(std::memory_order_acquire)) {
        return;
    }

    std::wstring addedIdentity;

    {
        // Serialize only the desired-state mutation itself. QueueBackendWork()
        // takes g_lifecycleMutex, so call it after this scope to keep the lock
        // graph strictly mutation/settings -> release -> lifecycle.
        std::lock_guard<std::mutex> mutationLock(
            g_settingsMutationMutex);

        // Recheck after acquiring the mutation lock: shutdown may have closed
        // user interactions while this callback was waiting behind a state write.
        if (g_unloading ||
            g_internalCleanupInProgress.load(std::memory_order_acquire)) {
            return;
        }

        Settings updated;
        {
            std::shared_lock lock(g_settingsMutex);
            updated = g_settings;
        }

        std::wstring stableId;
        const auto alreadyUsed =
            [&updated](std::wstring_view candidate) {
                return std::any_of(
                    updated.separators.begin(),
                    updated.separators.end(),
                    [candidate](const SeparatorSetting& separator) {
                        return separator.stableId ==
                            candidate;
                    });
            };

        do {
            stableId = GenerateStableId();
        } while (alreadyUsed(stableId));

        int sourceIndex =
            static_cast<int>(
                updated.separators.size());

        updated.separators.push_back({
            .ordinal = sourceIndex + 1,
            .sourceIndex = sourceIndex,
            // Explicitly unanchored. Windows appends it at the native end; the
            // first user drag records the concrete position through TryMoveGroup.
            .targetIndex = -1,
            .width = updated.width,
            .stableId = stableId,
            .identity = BuildSeparatorIdentity(
                updated.identifierPrefix,
                stableId),
        });

        addedIdentity =
            updated.separators.back().identity;

        {
            std::unique_lock lock(g_settingsMutex);
            g_settings = updated;
            g_backendHasConverged = false;
        }

        // Publish the desired state immediately, but let the backend worker make
        // it durable before PinManager is allowed to create the new pin.
        g_separatorStateDirty = true;
    }

    Wh_Log(
        L"[NATIVE-ADD] Added separator identity='%s' at native end",
        addedIdentity.c_str());

    QueueBackendWork();
}

static void StopBackendWorker() {
    HANDLE thread = nullptr;
    HANDLE stopEvent = nullptr;
    HANDLE wakeEvent = nullptr;

    {
        std::lock_guard<std::mutex> lock(g_lifecycleMutex);

        // Permanent latch: no loader-hook callback or settings callback can
        // create/wake a worker after shutdown begins.
        g_backendStopped = true;
        g_backendHasConverged = false;

        stopEvent =
            std::exchange(
                g_backendStopEvent,
                nullptr);
        wakeEvent =
            std::exchange(
                g_backendWakeEvent,
                nullptr);
        thread =
            std::exchange(
                g_backendThread,
                nullptr);

        if (stopEvent) {
            SetEvent(stopEvent);
        }
        if (wakeEvent) {
            SetEvent(wakeEvent);
        }
    }

    // Don't hold g_lifecycleMutex while joining the worker.
    if (thread) {
        if (WaitForSingleObject(thread, 0) == WAIT_TIMEOUT) {
            Wh_Log(L"[UNINIT] Waiting for separator backend worker");
        }

        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    }

    if (wakeEvent) {
        CloseHandle(wakeEvent);
    }

    if (stopEvent) {
        CloseHandle(stopEvent);
    }
}

static bool IsMainExplorerProcess() {
    HWND shellWindow = GetShellWindow();
    if (shellWindow) {
        DWORD shellProcessId = 0;
        GetWindowThreadProcessId(
            shellWindow,
            &shellProcessId);
        if (shellProcessId == GetCurrentProcessId()) {
            return true;
        }
    }

    // During an Explorer restart, GetShellWindow can be null or can still
    // refer to the previous, dying shell. Exclude known folder-process command
    // lines while allowing the replacement shell to wait for its own taskbar.
    std::wstring commandLine = GetCommandLineW();
    std::transform(
        commandLine.begin(),
        commandLine.end(),
        commandLine.begin(),
        [](wchar_t ch) { return std::towlower(ch); });

    return commandLine.find(L" /factory") == std::wstring::npos &&
           commandLine.find(L" /separate") == std::wstring::npos &&
           commandLine.find(L" -embedding") == std::wstring::npos;
}

BOOL ExplorerModInit() {
    if (!IsMainExplorerProcess()) {
        return FALSE;
    }

    Wh_Log(L"[INIT] Taskbar Icon Separators loading");

    if (!InitializeStoragePath()) {
        return FALSE;
    }

    g_interactionMode.store(
        LoadInteractionModeSetting(),
        std::memory_order_release);
    g_iconAppearance = LoadIconAppearanceSettings();
    ConfigureAppearanceGenerationPaths();

    Wh_Log(
        L"[SETTINGS] Interaction=%s icon(rotation=%d brightness=%d alpha=%d source=%s path='%s')",
        InteractionModeName(
            g_interactionMode.load(std::memory_order_acquire)),
        g_iconAppearance.rotation,
        g_iconAppearance.brightness,
        g_iconAppearance.alpha,
        g_iconAppearance.customIconBytes.empty() ? L"bundled" : L"custom",
        g_bundledIconPath.c_str());

    if (!LoadSettings()) {
        return FALSE;
    }

    if (!InitializeTaskbarStylingHooks()) {
        Wh_Log(
            L"[INIT] TaskListButton styling hooks unavailable");
    }

    if (!InitializeTaskbarDllHooks()) {
        Wh_Log(
            L"[INIT] taskbar.dll hooks unavailable");
    }

    // Hook operations installed during Wh_ModInit are applied automatically
    // before Wh_ModAfterInit. Missing taskbar hooks remain independent from
    // the pin-list backend and can still be installed on a late module load.
    return TRUE;
}

void ExplorerModAfterInit() {
    // Close the small race where the module wasn't present in Wh_ModInit but
    // appeared before/around Wh_ModAfterInit.
    if (!g_taskbarViewDllHooked) {
        if (HMODULE module = GetTaskbarViewModuleHandle()) {
            InstallTaskbarViewHooks(module, true);
        }
    }

    if (!g_taskbarDllHooked.load(std::memory_order_acquire)) {
        if (HMODULE module = GetModuleHandleW(L"taskbar.dll")) {
            InstallTaskbarDllHooks(module, true);
        }
    }

    // If the mod is enabled after Explorer already created the taskbar,
    // TrayUI::StartTaskbar has already returned and won't fire for us.
    if (FindCurrentProcessTaskbarWnd()) {
        Wh_Log(L"[LIFECYCLE] Existing taskbar window found; starting backend");
        // Late attach needs an initial refresh only when it actually creates the
        // worker. If TrayUI::StartTaskbar already started it, don't manufacture
        // a duplicate reconstruction pulse from Wh_ModAfterInit.
        StartBackendWorker(false);
    } else {
        Wh_Log(L"[LIFECYCLE] Waiting for TrayUI::StartTaskbar");
    }
}

void ExplorerModBeforeUninit() {
    // Hook APIs are legal only until this callback returns. Close every late
    // installation path first, then give already-entered installers a short,
    // bounded chance to leave the Windhawk hook engine. Never block unload
    // indefinitely waiting on engine work from another thread.
    g_hookInstallationClosed.store(true, std::memory_order_release);

    // Close user Add/Remove entry points immediately as teardown begins. A
    // callback that already passed its first guard rechecks this flag after
    // taking the mutation mutex, so no desired-state mutation can race the
    // installer drain or the final synchronous state flush.
    g_internalCleanupInProgress.store(true, std::memory_order_release);

    DrainHookInstallers();

    // Join the worker first so there can be no concurrent state-file writer.
    // Then perform one teardown-only synchronous durability fallback for a
    // missed drag-completion signal or an in-flight native mutation.
    StopBackendWorker();
    FlushPendingSeparatorStateSynchronously();

    // Remove pins while the styling and input hooks can still keep a transient
    // recovery pin styled and inert.
    CleanupSeparatorArtifacts(true);

    // Stop applying separator state before releasing the cleanup guard.
    g_unloading = true;
    g_internalCleanupInProgress = false;

    // Restore every tracked container on its owning taskbar UI thread before
    // Windhawk removes the hooks.
    RestoreTrackedSeparatorVisualStates();
}

void ExplorerModUninit() {
    Wh_Log(L"[UNINIT] Taskbar Icon Separators unloading");

    // Defensive in case an older Windhawk build skips Wh_ModBeforeUninit.
    g_unloading.store(true, std::memory_order_release);
    g_internalCleanupInProgress.store(true, std::memory_order_release);
    StopBackendWorker();
    FlushPendingSeparatorStateSynchronously();

    // Hooks may already be gone here, so never recover an absent pin by
    // temporarily pinning it again. Cleanup is also restricted to the
    // explorer.exe instance that actually owns the taskbar.
    CleanupSeparatorArtifacts(false);

    // Wh_ModBeforeUninit normally does this while hooks are still installed.
    // Keep a best-effort defensive pass here as well so a skipped BeforeUninit
    // doesn't leave XAML delegates pointing into an unloading module.
    RestoreTrackedSeparatorVisualStates();
    g_internalCleanupInProgress.store(false, std::memory_order_release);

    Wh_Log(L"[UNINIT] Taskbar Icon Separators unloaded");
}

BOOL ExplorerModSettingsChanged(BOOL* bReload) {
    if (bReload) {
        *bReload = FALSE;
    }

    // Existing .lnk/icon state deliberately isn't rewritten in place because
    // Explorer caches taskbar groups and shortcut imagery aggressively. Appearance
    // changes reload the mod; the new generation changes the ICO path, shortcut
    // path and AppUserModelID, while persisted stable IDs/positions stay unchanged.
    // Reconciliation purges all older shortcut/icon generations before converging.
    IconAppearanceSettings newIconAppearance =
        LoadIconAppearanceSettings();
    if (!IconAppearanceSettingsEqual(
            newIconAppearance,
            g_iconAppearance)) {
        Wh_Log(
            L"[SETTINGS] Separator icon appearance changed; requesting reload");
        if (bReload) {
            *bReload = TRUE;
        }
        return TRUE;
    }

    InteractionMode newInteractionMode =
        LoadInteractionModeSetting();

    if (g_taskbarViewDllHooked.load(std::memory_order_acquire)) {
        InteractionMode resolvedMode =
            ResolveInteractionModeAgainstCapabilities(
                newInteractionMode);
        if (resolvedMode != newInteractionMode) {
            Wh_Log(
                L"[SETTINGS] Requested interaction mode %s unavailable; using %s",
                InteractionModeName(newInteractionMode),
                InteractionModeName(resolvedMode));
            newInteractionMode = resolvedMode;
        }
    }

    if (newInteractionMode == InteractionMode::MiddleClick &&
        !g_separatorContextSuppressionAvailable.load(
            std::memory_order_acquire)) {
        Wh_Log(
            L"[SETTINGS] Warning: no separator right-click suppression route is currently available");
    }

    InteractionMode oldInteractionMode =
        g_interactionMode.exchange(
            newInteractionMode,
            std::memory_order_acq_rel);

    if (newInteractionMode != oldInteractionMode) {
        Wh_Log(
            L"[SETTINGS] Interaction mode changed %s -> %s",
            InteractionModeName(oldInteractionMode),
            InteractionModeName(newInteractionMode));
    }

    double newWidth =
        LoadSeparatorWidthSetting();

    {
        std::lock_guard<std::mutex> mutationLock(
            g_settingsMutationMutex);
        std::unique_lock lock(g_settingsMutex);

        g_settings.width = newWidth;
        g_appliedSettings.width = newWidth;

        for (auto& separator :
             g_settings.separators) {
            separator.width = newWidth;
        }
        for (auto& separator :
             g_appliedSettings.separators) {
            separator.width = newWidth;
        }
        for (auto& separator :
             g_storedSeparatorSettings) {
            separator.width = newWidth;
        }

        g_refreshPulseSetting.width =
            newWidth;
    }

    Wh_Log(
        L"[SETTINGS] Applied global separator width=%d",
        static_cast<int>(newWidth));

    // Width is presentation-only. Native separator positions and identities
    // live in the mod-storage state file and never require PinManager work.
    RefreshTrackedSeparatorVisualStates();

    return TRUE;
}


}  // namespace sep

std::atomic<bool> g_sepActive{false};

namespace wf = winrt::Windows::Foundation;
namespace wu = winrt::Windows::UI;
namespace wut = winrt::Windows::UI::Text;
namespace wux = winrt::Windows::UI::Xaml;
namespace wuxc = winrt::Windows::UI::Xaml::Controls;
namespace wuxcp = winrt::Windows::UI::Xaml::Controls::Primitives;
namespace wuxi = winrt::Windows::UI::Xaml::Input;
namespace wuxm = winrt::Windows::UI::Xaml::Media;

// ============================================================================
// Global State & Thread / Window Synchronization
// ============================================================================

struct ModSettings {
    bool showRestartExplorer = true;
    std::wstring textRestartExplorer = L"Restart Explorer";

    bool showCleanTemp = true;
    std::wstring textCleanTemp = L"Clean Temp";
    bool cleanRecycleBin = false;
    bool notifyCleanTemp = true;

    bool showReduceMemory = true;
    std::wstring textReduceMemory = L"Reduce Memory";
    bool notifyReduceMemory = true;

    bool showRestartGpu = true;
    std::wstring textRestartGpu = L"Restart Graphics Driver";

    bool showGetIp = true;
    std::wstring textGetIp = L"Get IP Address";
    bool queryPublicIp = false;
    bool copyIpToClipboard = false;

    bool showRebuildCache = true;
    std::wstring textRebuildCache = L"Rebuild Icon & Thumbnail Cache";
    bool notifyRebuildCache = true;

    bool showFlushDns = true;
    std::wstring textFlushDns = L"Clean DNS Cache";
    bool notifyFlushDns = true;

    bool showAutoHide = true;
    std::wstring textAutoHide = L"Auto-hide taskbar";
    bool separators = true;
    std::wstring textAddSeparator = L"Add separator";

    std::wstring fontFamily = L"FiraCode Nerd Font";
    uint16_t fontWeight = 500;
    int borderStyle = 0;  // 0 gradient, 1 solid, 2 none
    wu::Color gradientStart{255, 0x89, 0xB4, 0xFA};
    wu::Color gradientEnd{255, 0xCB, 0xA6, 0xF7};
    int borderWidth = 2;
    int cardOpacity = 90;
    bool matchTaskbar = true;
    bool colorIcons = true;
};

std::mutex g_settingsMutex;
ModSettings g_settings;

static constexpr wchar_t kGuardItemName[] = L"WindhawkSystemUtilitiesGuardItem";

std::atomic<bool> g_taskbarViewModuleHooked{false};
std::atomic<bool> g_restartStarted{false};
std::atomic<bool> g_unloading{false};

thread_local int g_taskbarSettingsMenuDepth = 0;
thread_local bool g_currentMenuInjected = false;
// The window that was in front before the taskbar menu opened; focus goes back
// to it after auto-hide is turned on, so the taskbar can slide away.
std::atomic<HWND> g_menuPrevForeground{nullptr};

// Accessed only on the taskbar UI thread
winrt::weak_ref<wux::FrameworkElement> g_lastTargetWeak;
winrt::weak_ref<wuxc::Flyout> g_activeFlyoutWeak;
winrt::weak_ref<wuxc::Button> g_activeOkButtonWeak;
winrt::event_token g_activeOkClickToken{};

std::mutex g_threadsMutex;
std::vector<HANDLE> g_threads;
std::mutex g_dispatchMutex;

ModSettings GetSettingsSnapshot() {
    std::lock_guard<std::mutex> lock(g_settingsMutex);
    return g_settings;
}

HWND FindCurrentProcessTaskbarWnd() {
    HWND hTaskbarWnd = nullptr;
    EnumWindows(
        [](HWND hWnd, LPARAM lParam) -> BOOL {
            DWORD dwProcessId = 0;
            if (GetWindowThreadProcessId(hWnd, &dwProcessId) &&
                dwProcessId == GetCurrentProcessId()) {
                WCHAR szClassName[32];
                if (GetClassNameW(hWnd, szClassName, ARRAYSIZE(szClassName)) &&
                    _wcsicmp(szClassName, L"Shell_TrayWnd") == 0) {
                    *reinterpret_cast<HWND*>(lParam) = hWnd;
                    return FALSE;
                }
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&hTaskbarWnd));
    return hTaskbarWnd;
}

bool RunFromWindowThread(HWND hWnd, std::function<void()> proc) {
    DWORD dwThreadId = GetWindowThreadProcessId(hWnd, nullptr);
    if (!dwThreadId) {
        return false;
    }

    if (dwThreadId == GetCurrentThreadId()) {
        proc();
        return true;
    }

    static const UINT runMsg =
        RegisterWindowMessageW(L"Windhawk_RunFromWindowThread_" WH_MOD_ID);

    struct CallWndProcParam {
        std::function<void()>* proc;
    };

    HHOOK hook = SetWindowsHookExW(
        WH_CALLWNDPROC,
        [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT {
            if (nCode == HC_ACTION) {
                const CWPSTRUCT* cwp =
                    reinterpret_cast<const CWPSTRUCT*>(lParam);
                if (cwp->message == runMsg) {
                    auto* param =
                        reinterpret_cast<CallWndProcParam*>(cwp->lParam);
                    (*param->proc)();
                }
            }
            return CallNextHookEx(nullptr, nCode, wParam, lParam);
        },
        nullptr, dwThreadId);
    if (!hook) {
        return false;
    }

    CallWndProcParam param{&proc};
    SendMessageW(hWnd, runMsg, 0, reinterpret_cast<LPARAM>(&param));
    UnhookWindowsHookEx(hook);
    return true;
}

template <typename F>
void RunAsyncTracked(F&& fn) {
    std::lock_guard<std::mutex> lock(g_threadsMutex);
    if (g_unloading.load()) {
        return;
    }

    for (auto it = g_threads.begin(); it != g_threads.end();) {
        if (WaitForSingleObject(*it, 0) == WAIT_OBJECT_0) {
            CloseHandle(*it);
            it = g_threads.erase(it);
        } else {
            ++it;
        }
    }

    auto task = std::make_unique<std::function<void()>>(std::forward<F>(fn));
    HANDLE thread = CreateThread(
        nullptr, 0,
        [](void* p) -> DWORD {
            std::unique_ptr<std::function<void()>> task(
                static_cast<std::function<void()>*>(p));
            try {
                (*task)();
            } catch (...) {
                Wh_Log(L"Background task threw an exception");
            }
            return 0;
        },
        task.get(), 0, nullptr);

    if (thread) {
        task.release();
        g_threads.push_back(thread);
    }
}

// ============================================================================
// Native XAML Flyout Card Builder (Theme-Aware & Unload-Safe)
// ============================================================================

using DialogRow = std::pair<std::wstring, std::wstring>;

// Catppuccin Mocha
constexpr wu::Color kBase{255, 0x1E, 0x1E, 0x2E};
constexpr wu::Color kCrust{255, 0x11, 0x11, 0x1B};
constexpr wu::Color kText{255, 0xCD, 0xD6, 0xF4};
constexpr wu::Color kSubtext{255, 0xA6, 0xAD, 0xC8};
constexpr wu::Color kBlue{255, 0x89, 0xB4, 0xFA};
constexpr wu::Color kLavender{255, 0xB4, 0xBE, 0xFE};
constexpr wu::Color kMauve{255, 0xCB, 0xA6, 0xF7};
constexpr wu::Color kGreen{255, 0xA6, 0xE3, 0xA1};
constexpr wu::Color kRed{255, 0xF3, 0x8B, 0xA8};

wuxm::SolidColorBrush MakeBrush(wu::Color c, uint8_t alpha = 255) {
    c.A = alpha;
    return wuxm::SolidColorBrush(c);
}

wuxm::FontFamily MakeFont(const ModSettings& cfg) {
    if (cfg.fontFamily.empty()) {
        return wuxm::FontFamily(L"Segoe UI Variable Text, Segoe UI");
    }
    return wuxm::FontFamily(winrt::hstring(
        cfg.fontFamily + L", Segoe UI Variable Text, Segoe UI"));
}

wuxc::FontIcon CreateFluentIcon(const wchar_t* glyph, double size = 16.0) {
    wuxc::FontIcon icon;
    icon.FontFamily(wuxm::FontFamily(L"Segoe Fluent Icons"));
    icon.Glyph(glyph);
    icon.FontSize(size);
    return icon;
}

wuxc::TextBlock MakeText(const std::wstring& value,
                         double size,
                         wu::Color color,
                         const ModSettings& cfg) {
    wuxc::TextBlock block;
    block.Text(value);
    block.FontSize(size);
    block.FontFamily(MakeFont(cfg));
    block.FontWeight(wut::FontWeight{cfg.fontWeight});
    block.Foreground(MakeBrush(color));
    block.VerticalAlignment(wux::VerticalAlignment::Center);
    return block;
}

wuxm::Brush MakeBorderBrush(const ModSettings& cfg) {
    if (cfg.borderStyle == 1) {
        return MakeBrush(cfg.gradientStart);
    }
    wuxm::LinearGradientBrush grad;
    grad.StartPoint({0, 0.5f});
    grad.EndPoint({1, 0.5f});
    wuxm::GradientStop a;
    a.Color(cfg.gradientStart);
    a.Offset(0.0);
    wuxm::GradientStop b;
    b.Color(cfg.gradientEnd);
    b.Offset(1.0);
    grad.GradientStops().Append(a);
    grad.GradientStops().Append(b);
    return grad;
}

// The taskbar's own background (Rectangle#BackgroundFill inside
// TaskbarBackground). The taskbar styler paints it, so handing the same brush
// to the menus and cards keeps one material for the whole bar.
winrt::weak_ref<winrt::Windows::UI::Xaml::Shapes::Rectangle> g_taskbarFillWeak;

winrt::Windows::UI::Xaml::Shapes::Rectangle FindTaskbarFill(
    wux::DependencyObject const& root) {
    std::vector<std::pair<wux::DependencyObject, int>> stack{{root, 0}};
    int visited = 0;
    while (!stack.empty() && visited++ < 4000) {
        auto [node, depth] = stack.back();
        stack.pop_back();
        if (auto rect = node.try_as<winrt::Windows::UI::Xaml::Shapes::Rectangle>()) {
            if (rect.Name() == L"BackgroundFill") {
                return rect;
            }
        }
        if (depth >= 30) {
            continue;
        }
        int n = wuxm::VisualTreeHelper::GetChildrenCount(node);
        for (int i = n - 1; i >= 0; i--) {
            stack.push_back({wuxm::VisualTreeHelper::GetChild(node, i), depth + 1});
        }
    }
    return nullptr;
}

wuxm::Brush TaskbarMaterial(wux::FrameworkElement const& anchor) {
    try {
        auto rect = g_taskbarFillWeak.get();
        if (!rect) {
            for (auto el : {anchor, g_lastTargetWeak.get()}) {
                if (!el || !el.XamlRoot()) {
                    continue;
                }
                if (auto content = el.XamlRoot().Content()) {
                    rect = FindTaskbarFill(content);
                    if (rect) {
                        g_taskbarFillWeak = rect;
                        break;
                    }
                }
            }
        }
        if (rect) {
            return rect.Fill();
        }
    } catch (...) {
    }
    return nullptr;
}

// Menu and card background: the taskbar's material when "Match the taskbar"
// is on and the taskbar is found, else the Mocha acrylic.
wuxm::Brush MenuBackground(wux::FrameworkElement const& anchor,
                           const ModSettings& cfg) {
    if (cfg.matchTaskbar) {
        auto brush = TaskbarMaterial(anchor);
        Wh_SetIntValue(L"menuMaterialFromTaskbar", brush ? 1 : 0);
        if (brush) {
            return brush;
        }
    }
    wuxm::AcrylicBrush acrylic;
    acrylic.BackgroundSource(wuxm::AcrylicBackgroundSource::HostBackdrop);
    acrylic.TintColor(kBase);
    acrylic.TintOpacity(cfg.cardOpacity / 100.0);
    acrylic.FallbackColor(kBase);
    return acrylic;
}

void CloseActiveFlyoutOnUIThread() {
    try {
        if (auto btn = g_activeOkButtonWeak.get()) {
            if (g_activeOkClickToken) {
                btn.Click(g_activeOkClickToken);
            }
        }
    } catch (...) {
    }
    g_activeOkButtonWeak = nullptr;
    g_activeOkClickToken = {};

    try {
        if (auto fl = g_activeFlyoutWeak.get()) {
            fl.Hide();
        }
    } catch (...) {
    }
    g_activeFlyoutWeak = nullptr;
}

void ShowModernXAMLCardOnUIThread(const std::wstring& titleText,
                                  const wchar_t* glyphIcon,
                                  const std::vector<DialogRow>& rows,
                                  const std::wstring& footerNote = L"",
                                  bool failed = false) {
    if (g_unloading.load()) {
        return;
    }

    try {
        CloseActiveFlyoutOnUIThread();

        auto target = g_lastTargetWeak.get();
        if (!target || !target.XamlRoot()) {
            Wh_Log(L"Cannot display XAML card: target or XamlRoot unavailable");
            return;
        }

        auto cfg = GetSettingsSnapshot();
        const double radius = 12.0;

        wuxc::Flyout flyout;
        flyout.ShouldConstrainToRootBounds(false);
        flyout.Placement(wuxcp::FlyoutPlacementMode::Top);
        flyout.XamlRoot(target.XamlRoot());

        // Clear the presenter so only our card draws, and match its corners
        // so the presenter does not clip the border.
        wux::Interop::TypeName presenterType{
            winrt::hstring{winrt::name_of<wuxc::FlyoutPresenter>()},
            wux::Interop::TypeKind::Metadata};
        wux::Style presenterStyle(presenterType);
        presenterStyle.Setters().Append(
            wux::Setter(wuxc::Control::PaddingProperty(),
                        winrt::box_value(wux::Thickness{0, 0, 0, 0})));
        presenterStyle.Setters().Append(
            wux::Setter(wuxc::Control::BorderThicknessProperty(),
                        winrt::box_value(wux::Thickness{0, 0, 0, 0})));
        presenterStyle.Setters().Append(wux::Setter(
            wuxc::Control::BackgroundProperty(), MakeBrush(kBase, 0)));
        presenterStyle.Setters().Append(wux::Setter(
            wuxc::Control::CornerRadiusProperty(),
            winrt::box_value(wux::CornerRadius{radius, radius, radius, radius})));
        flyout.FlyoutPresenterStyle(presenterStyle);

        wuxc::Border card;
        card.Background(MenuBackground(target, cfg));
        if (cfg.borderStyle != 2) {
            double w = cfg.borderWidth;
            card.BorderBrush(MakeBorderBrush(cfg));
            card.BorderThickness({w, w, w, w});
        }
        card.CornerRadius({radius, radius, radius, radius});
        card.Padding({22, 20, 22, 18});
        card.Width(380);

        wuxc::StackPanel mainStack;
        mainStack.Spacing(14);

        // Header: tinted icon badge and title.
        wuxc::StackPanel headerStack;
        headerStack.Orientation(wuxc::Orientation::Horizontal);
        headerStack.Spacing(12);

        wuxc::Border iconBadge;
        iconBadge.Background(MakeBrush(kBlue, 0x26));
        iconBadge.CornerRadius({8, 8, 8, 8});
        iconBadge.Width(36);
        iconBadge.Height(36);

        auto headerIcon = CreateFluentIcon(glyphIcon, 18.0);
        headerIcon.Foreground(MakeBrush(kBlue));
        headerIcon.HorizontalAlignment(wux::HorizontalAlignment::Center);
        headerIcon.VerticalAlignment(wux::VerticalAlignment::Center);
        iconBadge.Child(headerIcon);
        headerStack.Children().Append(iconBadge);
        headerStack.Children().Append(MakeText(titleText, 16, kText, cfg));
        mainStack.Children().Append(headerStack);

        // Rows of label and value.
        wuxc::Border metricsBox;
        metricsBox.Background(MakeBrush({255, 0x31, 0x32, 0x44}, 0x99));
        metricsBox.BorderBrush(MakeBrush({255, 0x45, 0x47, 0x5A}, 0x99));
        metricsBox.BorderThickness({1, 1, 1, 1});
        metricsBox.CornerRadius({8, 8, 8, 8});
        metricsBox.Padding({14, 12, 14, 12});

        wuxc::StackPanel rowsStack;
        rowsStack.Spacing(8);

        for (const auto& [label, val] : rows) {
            wuxc::Grid rowGrid;
            wuxc::ColumnDefinition col0;
            col0.Width(wux::GridLength{1.0, wux::GridUnitType::Auto});
            wuxc::ColumnDefinition col1;
            col1.Width(wux::GridLength{1.0, wux::GridUnitType::Star});
            rowGrid.ColumnDefinitions().Append(col0);
            rowGrid.ColumnDefinitions().Append(col1);

            auto lblBlock = MakeText(label, 13, kSubtext, cfg);
            lblBlock.Margin({0, 0, 16, 0});
            rowGrid.Children().Append(lblBlock);
            wuxc::Grid::SetColumn(lblBlock, 0);

            auto valBlock = MakeText(val, 13, kText, cfg);
            valBlock.HorizontalAlignment(wux::HorizontalAlignment::Right);
            valBlock.TextAlignment(wux::TextAlignment::Right);
            valBlock.TextWrapping(wux::TextWrapping::Wrap);
            valBlock.IsTextSelectionEnabled(true);
            rowGrid.Children().Append(valBlock);
            wuxc::Grid::SetColumn(valBlock, 1);

            rowsStack.Children().Append(rowGrid);
        }

        metricsBox.Child(rowsStack);
        mainStack.Children().Append(metricsBox);

        // Footer: status note and OK button.
        wuxc::Grid footerGrid;

        if (!footerNote.empty()) {
            wuxc::StackPanel noteStack;
            noteStack.Orientation(wuxc::Orientation::Horizontal);
            noteStack.Spacing(6);
            noteStack.VerticalAlignment(wux::VerticalAlignment::Center);

            auto noteIcon =
                CreateFluentIcon(failed ? L"\xE783" : L"\xE73E", 13.0);
            noteIcon.Foreground(MakeBrush(failed ? kRed : kGreen));
            noteStack.Children().Append(noteIcon);
            noteStack.Children().Append(MakeText(footerNote, 12, kSubtext, cfg));

            footerGrid.Children().Append(noteStack);
        }

        wuxc::Button okButton;
        okButton.Content(winrt::box_value(L"OK"));
        okButton.FontFamily(MakeFont(cfg));
        okButton.FontWeight(wut::FontWeight{cfg.fontWeight});
        okButton.Width(76);
        okButton.Height(30);
        okButton.CornerRadius({8, 8, 8, 8});
        okButton.BorderThickness({0, 0, 0, 0});
        okButton.HorizontalAlignment(wux::HorizontalAlignment::Right);
        // Lightweight styling so hover and press stay Mocha instead of the
        // system grey: blue at rest, lavender on hover, mauve when pressed.
        auto res = okButton.Resources();
        auto put = [&](const wchar_t* key, wuxm::SolidColorBrush brush) {
            res.Insert(winrt::box_value(key), brush);
        };
        put(L"ButtonBackground", MakeBrush(kBlue));
        put(L"ButtonBackgroundPointerOver", MakeBrush(kLavender));
        put(L"ButtonBackgroundPressed", MakeBrush(kMauve));
        put(L"ButtonForeground", MakeBrush(kCrust));
        put(L"ButtonForegroundPointerOver", MakeBrush(kCrust));
        put(L"ButtonForegroundPressed", MakeBrush(kCrust));
        put(L"ButtonBorderBrush", MakeBrush(kBlue, 0));
        put(L"ButtonBorderBrushPointerOver", MakeBrush(kBlue, 0));
        put(L"ButtonBorderBrushPressed", MakeBrush(kBlue, 0));
        okButton.Background(MakeBrush(kBlue));
        okButton.Foreground(MakeBrush(kCrust));

        winrt::weak_ref<wuxc::Flyout> weakFlyout(flyout);
        g_activeFlyoutWeak = flyout;
        g_activeOkButtonWeak = okButton;
        g_activeOkClickToken = okButton.Click(
            [weakFlyout](wf::IInspectable const&, wux::RoutedEventArgs const&) {
                if (auto fl = weakFlyout.get()) {
                    fl.Hide();
                }
            });

        footerGrid.Children().Append(okButton);
        mainStack.Children().Append(footerGrid);

        card.Child(mainStack);
        flyout.Content(card);
        flyout.ShowAt(target);
    } catch (...) {
        Wh_Log(L"Failed to display XAML Flyout card");
    }
}

void DispatchXAMLCardSync(const std::wstring& titleText,
                          const wchar_t* glyphIcon,
                          const std::vector<DialogRow>& rows,
                          const std::wstring& footerNote = L"",
                          bool failed = false) {
    std::lock_guard<std::mutex> lock(g_dispatchMutex);
    if (g_unloading.load()) {
        return;
    }

    HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
    if (!hTaskbarWnd) {
        return;
    }

    RunFromWindowThread(hTaskbarWnd, [&]() {
        if (!g_unloading.load()) {
            ShowModernXAMLCardOnUIThread(titleText, glyphIcon, rows,
                                         footerNote, failed);
        }
    });
}

bool CopyTextToClipboard(const std::wstring& text) {
    HWND tempOwner = CreateWindowExW(0, L"STATIC", nullptr, 0, 0, 0, 0, 0,
                                     HWND_MESSAGE, nullptr, nullptr, nullptr);
    HWND owner = tempOwner ? tempOwner : GetShellWindow();

    bool opened = false;
    for (int i = 0; i < 6 && !opened; ++i) {
        opened = OpenClipboard(owner) != FALSE;
        if (!opened) {
            Sleep(25);
        }
    }

    bool copied = false;
    if (opened) {
        EmptyClipboard();
        size_t byteSize = (text.size() + 1) * sizeof(wchar_t);
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, byteSize);
        if (hMem) {
            if (void* ptr = GlobalLock(hMem)) {
                memcpy(ptr, text.c_str(), byteSize);
                GlobalUnlock(hMem);
                if (SetClipboardData(CF_UNICODETEXT, hMem)) {
                    copied = true;
                } else {
                    GlobalFree(hMem);
                }
            } else {
                GlobalFree(hMem);
            }
        }
        CloseClipboard();
    }

    if (tempOwner) {
        DestroyWindow(tempOwner);
    }
    return copied;
}

// ============================================================================
// Native Action Implementations
// ============================================================================

// 1. Restart Explorer
void OnRestartExplorerClick(wf::IInspectable const&,
                            wux::RoutedEventArgs const&) {
    if (g_restartStarted.exchange(true)) {
        return;
    }

    wchar_t sysDir[MAX_PATH] = {};
    if (GetSystemDirectoryW(sysDir, MAX_PATH) == 0) {
        g_restartStarted = false;
        return;
    }

    std::wstring cmdPath = std::wstring(sysDir) + L"\\cmd.exe";
    wchar_t cmdArgs[] =
        L"/d /c \"taskkill /f /im explorer.exe >nul 2>nul & start \"\" "
        L"explorer.exe\"";

    STARTUPINFOW si = {};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi = {};

    if (CreateProcessW(cmdPath.c_str(), cmdArgs, nullptr, nullptr, FALSE,
                       CREATE_NO_WINDOW | CREATE_NEW_PROCESS_GROUP, nullptr,
                       nullptr, &si, &pi)) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    } else {
        g_restartStarted = false;
    }
}

// 2. Clean Temp
struct CleanStats {
    DWORD filesDeleted = 0;
    DWORD filesSkipped = 0;
    ULONGLONG bytesFreed = 0;
};

std::wstring ToExtendedPath(const std::wstring& path) {
    if (path.rfind(L"\\\\?\\", 0) == 0) {
        return path;
    }
    return L"\\\\?\\" + path;
}

bool IsSafeCleanTarget(const std::wstring& path) {
    if (path.size() < 4) {
        return false;
    }

    auto equalsEnv = [&](const wchar_t* var) {
        wchar_t buf[MAX_PATH] = {};
        DWORD n = GetEnvironmentVariableW(var, buf, MAX_PATH);
        if (n == 0 || n >= MAX_PATH) {
            return false;
        }
        std::wstring v(buf);
        while (!v.empty() && v.back() == L'\\') {
            v.pop_back();
        }
        return _wcsicmp(v.c_str(), path.c_str()) == 0;
    };

    return !(equalsEnv(L"USERPROFILE") || equalsEnv(L"SystemRoot") ||
             equalsEnv(L"SystemDrive"));
}

void CleanDirectoryRecursive(const std::wstring& dirPath,
                             bool removeRoot,
                             CleanStats& stats) {
    if (g_unloading.load()) {
        return;
    }

    std::wstring searchMask = dirPath + L"\\*";
    WIN32_FIND_DATAW fd;
    HANDLE hFind = FindFirstFileW(searchMask.c_str(), &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (wcscmp(fd.cFileName, L".") == 0 ||
            wcscmp(fd.cFileName, L"..") == 0) {
            continue;
        }

        std::wstring fullPath = dirPath + L"\\" + fd.cFileName;

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) {
                CleanDirectoryRecursive(fullPath, true, stats);
            }
        } else {
            ULONGLONG fileSize =
                (static_cast<ULONGLONG>(fd.nFileSizeHigh) << 32) |
                fd.nFileSizeLow;
            if (DeleteFileW(fullPath.c_str())) {
                stats.filesDeleted++;
                stats.bytesFreed += fileSize;
            } else {
                stats.filesSkipped++;
            }
        }
    } while (!g_unloading.load() && FindNextFileW(hFind, &fd));

    FindClose(hFind);

    if (removeRoot && !g_unloading.load()) {
        RemoveDirectoryW(dirPath.c_str());
    }
}

void OnCleanTempClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        auto cfg = GetSettingsSnapshot();
        CleanStats stats;

        wchar_t tempPath[MAX_PATH] = {};
        if (GetTempPathW(MAX_PATH, tempPath) > 0) {
            std::wstring userTemp(tempPath);
            while (!userTemp.empty() && userTemp.back() == L'\\') {
                userTemp.pop_back();
            }
            if (IsSafeCleanTarget(userTemp)) {
                CleanDirectoryRecursive(ToExtendedPath(userTemp), false, stats);
            } else {
                Wh_Log(L"Temp path rejected by safety check: %s",
                       userTemp.c_str());
            }
        }

        wchar_t winDir[MAX_PATH] = {};
        if (GetWindowsDirectoryW(winDir, MAX_PATH) >= 3) {
            std::wstring sysTemp = std::wstring(winDir) + L"\\Temp";
            CleanDirectoryRecursive(ToExtendedPath(sysTemp), false, stats);
        }

        if (cfg.cleanRecycleBin && !g_unloading.load()) {
            SHEmptyRecycleBinW(
                nullptr, nullptr,
                SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
        }

        if (cfg.notifyCleanTemp && !g_unloading.load()) {
            double mbFreed =
                static_cast<double>(stats.bytesFreed) / (1024.0 * 1024.0);
            wchar_t mbBuf[64] = {};
            swprintf_s(mbBuf, L"%.2f MB", mbFreed);

            std::vector<DialogRow> rows = {
                {L"Deleted files", std::to_wstring(stats.filesDeleted)},
                {L"Locked / skipped", std::to_wstring(stats.filesSkipped)},
                {L"Space recovered", mbBuf},
            };

            std::wstring footer =
                (stats.filesDeleted == 0 && stats.filesSkipped == 0)
                    ? L"No removable temp files found"
                    : L"Cleanup completed";

            DispatchXAMLCardSync(L"Temporary Files Cleaned", L"\xE74D", rows,
                                 footer);
        }
    });
}

// 3. Reduce Memory
void OnReduceMemoryClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        auto cfg = GetSettingsSnapshot();

        MEMORYSTATUSEX memBefore = {sizeof(memBefore)};
        GlobalMemoryStatusEx(&memBefore);

        std::vector<DWORD> pids(1024);
        DWORD bytesReturned = 0;
        while (K32EnumProcesses(pids.data(),
                                static_cast<DWORD>(pids.size() * sizeof(DWORD)),
                                &bytesReturned)) {
            if (bytesReturned < pids.size() * sizeof(DWORD)) {
                break;
            }
            pids.resize(pids.size() * 2);
        }

        DWORD currentPid = GetCurrentProcessId();
        DWORD count = bytesReturned / sizeof(DWORD);
        DWORD trimmedCount = 0;
        DWORD skippedCount = 0;

        for (DWORD i = 0; i < count && !g_unloading.load(); ++i) {
            if (pids[i] == 0 || pids[i] == 4 || pids[i] == currentPid) {
                continue;
            }

            HANDLE hProc = OpenProcess(
                PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_SET_QUOTA, FALSE,
                pids[i]);
            if (hProc) {
                if (K32EmptyWorkingSet(hProc)) {
                    trimmedCount++;
                } else {
                    skippedCount++;
                }
                CloseHandle(hProc);
            } else {
                skippedCount++;
            }
        }

        if (cfg.notifyReduceMemory && !g_unloading.load()) {
            MEMORYSTATUSEX memAfter = {sizeof(memAfter)};
            GlobalMemoryStatusEx(&memAfter);

            double freedMb = 0.0;
            if (memAfter.ullAvailPhys > memBefore.ullAvailPhys) {
                freedMb = static_cast<double>(memAfter.ullAvailPhys -
                                              memBefore.ullAvailPhys) /
                          (1024.0 * 1024.0);
            }
            double availGb = static_cast<double>(memAfter.ullAvailPhys) /
                             (1024.0 * 1024.0 * 1024.0);

            wchar_t freedBuf[64] = {};
            swprintf_s(freedBuf, L"%.1f MB", freedMb);

            wchar_t availBuf[64] = {};
            swprintf_s(availBuf, L"%.2f GB (%lu%% used)", availGb,
                       memAfter.dwMemoryLoad);

            std::vector<DialogRow> rows = {
                {L"Processes optimized", std::to_wstring(trimmedCount)},
                {L"Processes skipped", std::to_wstring(skippedCount)},
                {L"RAM recovered", freedBuf},
                {L"Available RAM", availBuf},
            };

            DispatchXAMLCardSync(L"Memory Optimized", L"\xE950", rows,
                                 L"Working sets trimmed");
        }
    });
}

// 4. Restart Graphics Driver
void OnRestartGpuClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        Sleep(150);
        if (g_unloading.load()) {
            return;
        }

        static constexpr WORD kKeys[] = {VK_LWIN, VK_CONTROL, VK_SHIFT, 'B'};
        INPUT inputs[8] = {};

        for (size_t i = 0; i < 4; ++i) {
            inputs[i].type = INPUT_KEYBOARD;
            inputs[i].ki.wVk = kKeys[i];

            inputs[i + 4].type = INPUT_KEYBOARD;
            inputs[i + 4].ki.wVk = kKeys[3 - i];
            inputs[i + 4].ki.dwFlags = KEYEVENTF_KEYUP;
        }

        if (SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT)) !=
            ARRAYSIZE(inputs)) {
            Wh_Log(L"SendInput failed: %lu", GetLastError());
        }
    });
}

// 5. Get IP (Preferred Local Adapters + Optional Public IP)
std::vector<DialogRow> GetLocalAdapterIPs(std::wstring& clipboardText) {
    std::vector<DialogRow> rows;
    clipboardText.clear();

    ULONG flags = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
                  GAA_FLAG_SKIP_DNS_SERVER;
    ULONG outBufLen = 15000;
    std::vector<BYTE> buffer(outBufLen);

    DWORD dwRetVal = GetAdaptersAddresses(
        AF_UNSPEC, flags, nullptr,
        reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data()), &outBufLen);
    if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
        buffer.resize(outBufLen);
        dwRetVal = GetAdaptersAddresses(
            AF_UNSPEC, flags, nullptr,
            reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data()), &outBufLen);
    }

    if (dwRetVal != NO_ERROR) {
        rows.emplace_back(L"Status", L"Failed to query adapters");
        return rows;
    }

    for (auto* adapter = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());
         adapter != nullptr; adapter = adapter->Next) {
        if (adapter->OperStatus != IfOperStatusUp ||
            adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK) {
            continue;
        }

        bool hasIpv4 = false;
        bool hasIpv6 = false;

        for (auto* unicast = adapter->FirstUnicastAddress; unicast != nullptr;
             unicast = unicast->Next) {
            if (unicast->DadState != IpDadStatePreferred) {
                continue;
            }

            SOCKADDR* addr = unicast->Address.lpSockaddr;
            if (!addr) {
                continue;
            }

            wchar_t ipStr[INET6_ADDRSTRLEN] = {};
            if (addr->sa_family == AF_INET && !hasIpv4) {
                auto* sa4 = reinterpret_cast<sockaddr_in*>(addr);
                const auto* bytes =
                    reinterpret_cast<const uint8_t*>(&sa4->sin_addr);
                // Skip addresses APIPA 169.254.0.0/16
                if (bytes[0] == 169 && bytes[1] == 254) {
                    continue;
                }
                if (InetNtopW(AF_INET, &sa4->sin_addr, ipStr,
                              ARRAYSIZE(ipStr))) {
                    hasIpv4 = true;
                }
            } else if (addr->sa_family == AF_INET6 && !hasIpv6) {
                auto* sa6 = reinterpret_cast<sockaddr_in6*>(addr);
                // Skip link-local addresses (fe80::/10)
                if (IN6_IS_ADDR_LINKLOCAL(&sa6->sin6_addr)) {
                    continue;
                }
                if (InetNtopW(AF_INET6, &sa6->sin6_addr, ipStr,
                              ARRAYSIZE(ipStr))) {
                    hasIpv6 = true;
                }
            }

            if (ipStr[0] != L'\0') {
                std::wstring label =
                    adapter->FriendlyName ? adapter->FriendlyName : L"Adapter";
                if (addr->sa_family == AF_INET6) {
                    label += L" (IPv6)";
                }
                rows.emplace_back(label, ipStr);
                if (!clipboardText.empty()) {
                    clipboardText += L"\r\n";
                }
                clipboardText += label + L": " + ipStr;
            }
        }
    }

    if (rows.empty()) {
        rows.emplace_back(L"Network", L"Disconnected");
    }

    return rows;
}

std::mutex g_inetMutex;
HINTERNET g_activeInternet = nullptr;

void CancelActivePublicIpRequest() {
    std::lock_guard<std::mutex> lock(g_inetMutex);
    if (g_activeInternet) {
        InternetCloseHandle(g_activeInternet);
        g_activeInternet = nullptr;
    }
}

std::wstring GetPublicIP() {
    std::wstring result = L"Unavailable";
    HINTERNET hInternet =
        InternetOpenW(L"SeamlessTaskbarUtilities/" WH_MOD_VERSION,
                      INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
    if (!hInternet) {
        return result;
    }

    {
        std::lock_guard<std::mutex> lock(g_inetMutex);
        if (g_unloading.load()) {
            InternetCloseHandle(hInternet);
            return result;
        }
        g_activeInternet = hInternet;
    }

    DWORD timeout = 2500;
    InternetSetOptionW(hInternet, INTERNET_OPTION_CONNECT_TIMEOUT, &timeout,
                       sizeof(timeout));
    InternetSetOptionW(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &timeout,
                       sizeof(timeout));

    HINTERNET hConnect =
        InternetOpenUrlW(hInternet, L"https://api.ipify.org", nullptr, 0,
                         INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE |
                             INTERNET_FLAG_SECURE,
                         0);
    if (hConnect) {
        char buffer[64] = {};
        DWORD bytesRead = 0;
        if (!g_unloading.load() &&
            InternetReadFile(hConnect, buffer, sizeof(buffer) - 1,
                             &bytesRead) &&
            bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::string raw(buffer);
            while (!raw.empty() &&
                   std::isspace(static_cast<unsigned char>(raw.back()))) {
                raw.pop_back();
            }

            in_addr addr4;
            in6_addr addr6;
            if (InetPtonA(AF_INET, raw.c_str(), &addr4) == 1 ||
                InetPtonA(AF_INET6, raw.c_str(), &addr6) == 1) {
                wchar_t wbuffer[64] = {};
                MultiByteToWideChar(CP_UTF8, 0, raw.c_str(), -1, wbuffer, 64);
                result = wbuffer;
            }
        }
        InternetCloseHandle(hConnect);
    }

    {
        std::lock_guard<std::mutex> lock(g_inetMutex);
        if (g_activeInternet == hInternet) {
            g_activeInternet = nullptr;
            InternetCloseHandle(hInternet);
        }
    }
    return result;
}

void OnGetIpClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        auto cfg = GetSettingsSnapshot();

        std::wstring clipboardText;
        std::vector<DialogRow> rows = GetLocalAdapterIPs(clipboardText);

        if (cfg.queryPublicIp && !g_unloading.load()) {
            std::wstring publicIp = GetPublicIP();
            rows.insert(rows.begin(), {L"Public IP", publicIp});
            if (!clipboardText.empty()) {
                clipboardText =
                    L"Public IP: " + publicIp + L"\r\n" + clipboardText;
            } else {
                clipboardText = L"Public IP: " + publicIp;
            }
        }

        if (g_unloading.load()) {
            return;
        }

        std::wstring footer;
        if (cfg.copyIpToClipboard && !clipboardText.empty()) {
            if (CopyTextToClipboard(clipboardText)) {
                footer = L"Copied to clipboard";
            }
        }

        DispatchXAMLCardSync(L"Network IP Addresses", L"\xE968", rows, footer);
    });
}

// 6. Rebuild Icon & Thumbnail Cache
void OnRebuildCacheClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        auto cfg = GetSettingsSnapshot();

        DWORD thumbsDeleted = 0;
        DWORD thumbsSkipped = 0;
        ULONGLONG bytesFreed = 0;

        // Best-effort delete of thumbnail cache files.
        wchar_t localAppData[MAX_PATH] = {};
        DWORD localLen =
            GetEnvironmentVariableW(L"LOCALAPPDATA", localAppData, MAX_PATH);
        if (localLen > 0 && localLen < MAX_PATH) {
            std::wstring explorerDir =
                std::wstring(localAppData) + L"\\Microsoft\\Windows\\Explorer";

            std::wstring searchMask = explorerDir + L"\\thumbcache_*.db";
            WIN32_FIND_DATAW fd;
            HANDLE hFind = FindFirstFileW(searchMask.c_str(), &fd);
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    if (g_unloading.load()) {
                        break;
                    }
                    if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        continue;
                    }

                    std::wstring fullPath = explorerDir + L"\\" + fd.cFileName;
                    ULONGLONG fileSize =
                        (static_cast<ULONGLONG>(fd.nFileSizeHigh) << 32) |
                        fd.nFileSizeLow;

                    if (DeleteFileW(ToExtendedPath(fullPath).c_str())) {
                        thumbsDeleted++;
                        bytesFreed += fileSize;
                    } else {
                        thumbsSkipped++;
                    }
                } while (FindNextFileW(hFind, &fd));
                FindClose(hFind);
            }
        }

        // Rebuild icon cache without restarting Explorer via ie4uinit.exe
        // -show.
        bool iconsRebuilt = false;
        if (!g_unloading.load()) {
            wchar_t sysDir[MAX_PATH] = {};
            DWORD sysLen = GetSystemDirectoryW(sysDir, MAX_PATH);
            if (sysLen > 0 && sysLen < MAX_PATH) {
                std::wstring exePath = std::wstring(sysDir) + L"\\ie4uinit.exe";

                STARTUPINFOW si = {};
                si.cb = sizeof(si);
                si.dwFlags = STARTF_USESHOWWINDOW;
                si.wShowWindow = SW_HIDE;
                PROCESS_INFORMATION pi = {};

                wchar_t cmdLine[] = L"ie4uinit.exe -show";
                if (CreateProcessW(exePath.c_str(), cmdLine, nullptr, nullptr,
                                   FALSE, CREATE_NO_WINDOW, nullptr, nullptr,
                                   &si, &pi)) {
                    DWORD waitRes = WaitForSingleObject(pi.hProcess, 5000);
                    DWORD exitCode = 1;
                    GetExitCodeProcess(pi.hProcess, &exitCode);
                    CloseHandle(pi.hThread);
                    CloseHandle(pi.hProcess);
                    iconsRebuilt = (waitRes == WAIT_OBJECT_0 && exitCode == 0);
                } else {
                    Wh_Log(L"ie4uinit.exe launch failed: %lu", GetLastError());
                }
            }
        }

        if (cfg.notifyRebuildCache && !g_unloading.load()) {
            double mbFreed =
                static_cast<double>(bytesFreed) / (1024.0 * 1024.0);
            wchar_t mbBuf[64] = {};
            swprintf_s(mbBuf, L"%.2f MB", mbFreed);

            std::vector<DialogRow> rows = {
                {L"Thumbnail files deleted", std::to_wstring(thumbsDeleted)},
                {L"Locked / skipped", std::to_wstring(thumbsSkipped)},
                {L"Space recovered", mbBuf},
                {L"Icon cache", iconsRebuilt ? L"Rebuilt" : L"Failed"},
            };

            std::wstring footer;
            if (!iconsRebuilt) {
                footer = L"Icon rebuild failed";
            } else if (thumbsSkipped > 0) {
                footer = L"Some thumbnails locked by Explorer";
            } else {
                footer = L"Cache rebuilt successfully";
            }

            DispatchXAMLCardSync(L"Cache Rebuilt", L"\xE8B9", rows, footer,
                                 !iconsRebuilt);
        }
    });
}

// 7. Clean DNS Cache
using DnsFlushResolverCache_t = BOOL(WINAPI*)();

void OnFlushDnsClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        BOOL flushed = FALSE;
        if (HMODULE hDnsApi = LoadLibraryExW(L"dnsapi.dll", nullptr,
                                             LOAD_LIBRARY_SEARCH_SYSTEM32)) {
            auto pFlush = reinterpret_cast<DnsFlushResolverCache_t>(
                GetProcAddress(hDnsApi, "DnsFlushResolverCache"));
            if (pFlush)
                flushed = pFlush();
            FreeLibrary(hDnsApi);
        }

        auto cfg = GetSettingsSnapshot();
        if (cfg.notifyFlushDns && !g_unloading.load()) {
            std::vector<DialogRow> rows = {
                {L"Resolver Cache", flushed ? L"Flushed" : L"Failed"},
                {L"Method", L"dnsapi.dll (In-Memory)"},
            };
            DispatchXAMLCardSync(L"DNS Cache", L"\xE774", rows,
                                 flushed ? L"Cache cleared successfully"
                                         : L"Error flushing cache",
                                 !flushed);
        }
    });
}

// ============================================================================
// Taskbar Context Menu Injection Hooks
// ============================================================================

bool HStringEquals(winrt::hstring const& value, const wchar_t* text) {
    return std::wstring_view(value.c_str(), value.size()) == text;
}

bool IsNamedItem(wuxc::MenuFlyoutItemBase const& baseItem,
                 const wchar_t* name) {
    try {
        if (auto frameworkElement = baseItem.try_as<wux::FrameworkElement>()) {
            return HStringEquals(frameworkElement.Name(), name);
        }
    } catch (...) {
    }
    return false;
}

bool IsSeparator(wuxc::MenuFlyoutItemBase const& baseItem) {
    try {
        return !!baseItem.try_as<wuxc::MenuFlyoutSeparator>();
    } catch (...) {
    }
    return false;
}

using MenuFlyoutItemBaseVector_Append_t =
    void(__cdecl*)(void* pThis, wuxc::MenuFlyoutItemBase const& item);
MenuFlyoutItemBaseVector_Append_t MenuFlyoutItemBaseVector_Append_Original;

struct MenuItemSpec {
    bool enabled;
    std::wstring text;
    const wchar_t* glyph;
    void (*handler)(wf::IInspectable const&, wux::RoutedEventArgs const&);
};

constexpr wu::Color kMantle{255, 0x18, 0x18, 0x25};
constexpr wu::Color kSurface1{255, 0x45, 0x47, 0x5A};

void InsertResource(wux::ResourceDictionary const& res,
                    const wchar_t* key,
                    wf::IInspectable const& value) {
    auto boxedKey = winrt::box_value(winrt::hstring(key));
    if (res.HasKey(boxedKey)) {
        res.Remove(boxedKey);
    }
    res.Insert(boxedKey, value);
}

// Mocha acrylic and the gradient border on the menu itself. Walks up from a
// loaded item to its MenuFlyoutPresenter; the presenter template binds
// Background, BorderBrush and BorderThickness, so local values win.
void ThemeMenuItemOnce(wf::IInspectable const& obj, int depth);

// Also sweeps the presenter's rows: other mods (Taskbar App Memory's Remember
// positions) append through their own hook, so our Append hook never sees them.
void ThemeMenuPresenter(wux::DependencyObject node) {
    auto cfg = GetSettingsSnapshot();
    for (int depth = 0; node && depth < 16; depth++) {
        if (auto presenter = node.try_as<wuxc::MenuFlyoutPresenter>()) {
            presenter.Background(MenuBackground(presenter, cfg));
            if (cfg.borderStyle != 2) {
                double w = cfg.borderWidth;
                presenter.BorderBrush(MakeBorderBrush(cfg));
                presenter.BorderThickness({w, w, w, w});
            }
            try {
                for (auto const& obj : presenter.Items()) {
                    ThemeMenuItemOnce(obj, 0);
                }
            } catch (...) {
                Wh_Log(L"Menu row sweep failed");
            }
            return;
        }
        node = wuxm::VisualTreeHelper::GetParent(node);
    }
}

void ThemeMenuIcon(wuxc::IconElement const& icon, const ModSettings& cfg) {
    if (cfg.colorIcons && icon) {
        icon.Foreground(MakeBrush(kBlue));
    }
}

// Menu pill: the one hover look for every menu row, the same pill Seamless Clipboard Manager
// draws: a soft blue to mauve fill (16 %) and a 1 px blue to mauve ring (80 %), radius 8.
// The taskbar's menu template never applies the ring resources, so the ring is set on the item
// while the pointer is over it. An item whose submenu is open keeps its ring until a sibling
// takes the pointer.
namespace SeamlessXamlPill {
namespace wux = winrt::Windows::UI::Xaml;
static wux::Media::Brush Brush(uint8_t alpha)
{
    wux::Media::LinearGradientBrush brush;
    brush.StartPoint({0.f, 0.f});
    brush.EndPoint({1.f, 1.f});
    wux::Media::GradientStop a, b;
    a.Color(winrt::Windows::UI::Color{alpha, 0x89, 0xB4, 0xFA});
    a.Offset(0.0);
    b.Color(winrt::Windows::UI::Color{alpha, 0xCB, 0xA6, 0xF7});
    b.Offset(1.0);
    brush.GradientStops().Append(a);
    brush.GradientStops().Append(b);
    return brush;
}
static wux::Media::Brush Fill() { return Brush(0x29); }
static wux::Media::Brush Ring() { return Brush(0xCC); }
static std::vector<winrt::weak_ref<wux::Controls::Control>> g_lit, g_hooked;
// TRUE the first time an item is seen (menus can be themed again on every open).
static bool FirstTime(wux::Controls::Control const& item)
{
    bool seen = false;
    for (auto it = g_hooked.begin(); it != g_hooked.end();) {
        auto c = it->get();
        if (!c) { it = g_hooked.erase(it); continue; }
        if (c == item) seen = true;
        ++it;
    }
    if (!seen) g_hooked.push_back(winrt::make_weak(item));
    return !seen;
}
static void Light(wux::Controls::Control const& item, bool on)
{
    try {
        item.BorderBrush(on ? Ring() : wux::Media::Brush(wux::Media::SolidColorBrush(winrt::Windows::UI::Color{0, 0x89, 0xB4, 0xFA})));
    } catch (...) {}
}
static void Forget(wux::Controls::Control const& item)
{
    for (auto it = g_lit.begin(); it != g_lit.end();) {
        auto c = it->get();
        if (!c || c == item) it = g_lit.erase(it); else ++it;
    }
}
static void OnEnter(wux::Controls::Control const& item)
{
    auto parent = wux::Media::VisualTreeHelper::GetParent(item);
    for (auto it = g_lit.begin(); it != g_lit.end();) {
        auto c = it->get();
        if (!c) { it = g_lit.erase(it); continue; }
        if (c != item && wux::Media::VisualTreeHelper::GetParent(c) == parent) { Light(c, false); it = g_lit.erase(it); continue; }
        ++it;
    }
    Light(item, true);
    Forget(item);
    g_lit.push_back(winrt::make_weak(item));
}
// Fill and ring resources for every pointer state, plus the pointer handlers.
static void Apply(wux::Controls::Control const& item, wux::ResourceDictionary const& res)
{
    auto put = [&](const wchar_t* key, winrt::Windows::Foundation::IInspectable const& value) {
        auto k = winrt::box_value(winrt::hstring(key));
        try { if (res.HasKey(k)) res.Remove(k); res.Insert(k, value); } catch (...) {}
    };
    for (auto key : {L"MenuFlyoutItemRevealBackgroundPointerOver", L"MenuFlyoutItemBackgroundPointerOver",
                     L"MenuFlyoutItemRevealBackgroundPressed", L"MenuFlyoutItemBackgroundPressed",
                     L"MenuFlyoutSubItemRevealBackgroundPointerOver", L"MenuFlyoutSubItemBackgroundPointerOver",
                     L"MenuFlyoutSubItemRevealBackgroundPressed", L"MenuFlyoutSubItemBackgroundPressed",
                     L"MenuFlyoutSubItemRevealBackgroundSubMenuOpened", L"MenuFlyoutSubItemBackgroundSubMenuOpened",
                     L"ToggleMenuFlyoutItemRevealBackgroundPointerOver", L"ToggleMenuFlyoutItemBackgroundPointerOver",
                     L"ToggleMenuFlyoutItemRevealBackgroundPressed", L"ToggleMenuFlyoutItemBackgroundPressed"})
        put(key, Fill());
    for (auto key : {L"MenuFlyoutItemRevealBorderBrushPointerOver", L"MenuFlyoutItemBorderBrushPointerOver",
                     L"MenuFlyoutItemRevealBorderBrushPressed", L"MenuFlyoutItemBorderBrushPressed",
                     L"MenuFlyoutSubItemRevealBorderBrushPointerOver", L"MenuFlyoutSubItemBorderBrushPointerOver",
                     L"MenuFlyoutSubItemRevealBorderBrushPressed", L"MenuFlyoutSubItemBorderBrushPressed",
                     L"MenuFlyoutSubItemRevealBorderBrushSubMenuOpened", L"MenuFlyoutSubItemBorderBrushSubMenuOpened",
                     L"ToggleMenuFlyoutItemRevealBorderBrushPointerOver", L"ToggleMenuFlyoutItemRevealBorderBrushPressed"})
        put(key, Ring());
    item.BorderThickness({1, 1, 1, 1});
    item.CornerRadius({8, 8, 8, 8});
    Light(item, false);
    if (!FirstTime(item)) return;
    item.AddHandler(wux::UIElement::PointerEnteredEvent(), winrt::box_value(wux::Input::PointerEventHandler(
        [](winrt::Windows::Foundation::IInspectable const& sender, wux::Input::PointerRoutedEventArgs const&) {
            try { OnEnter(sender.as<wux::Controls::Control>()); } catch (...) {}
        })), true);
    item.AddHandler(wux::UIElement::PointerExitedEvent(), winrt::box_value(wux::Input::PointerEventHandler(
        [](winrt::Windows::Foundation::IInspectable const& sender, wux::Input::PointerRoutedEventArgs const&) {
            try {
                if (sender.try_as<wux::Controls::MenuFlyoutSubItem>()) return;
                auto c = sender.as<wux::Controls::Control>();
                Light(c, false);
                Forget(c);
            } catch (...) {}
        })), true);
    item.Unloaded([](winrt::Windows::Foundation::IInspectable const& sender, wux::RoutedEventArgs const&) {
        try { auto c = sender.as<wux::Controls::Control>(); Light(c, false); Forget(c); } catch (...) {}
    });
}
}  // namespace SeamlessXamlPill

// Applies to every item in the taskbar menu, ours and the stock ones, so
// Task Manager and Taskbar settings match. Hover is the menu pill (SeamlessXamlPill).
void ThemeMenuItem(wuxc::MenuFlyoutItemBase const& base) {
    auto cfg = GetSettingsSnapshot();
    if (auto separator = base.try_as<wuxc::MenuFlyoutSeparator>()) {
        separator.Background(MakeBrush(kSurface1));
        return;
    }

    base.FontFamily(MakeFont(cfg));
    base.FontWeight(wut::FontWeight{cfg.fontWeight});
    base.Foreground(MakeBrush(kText));
    auto res = base.Resources();
    auto text = MakeBrush(kText);
    SeamlessXamlPill::Apply(base, res);
    InsertResource(res, L"MenuFlyoutItemForegroundPointerOver", text);
    InsertResource(res, L"MenuFlyoutItemForegroundPressed", text);
    for (auto key : {L"MenuFlyoutSubItemForegroundPointerOver",
                     L"MenuFlyoutSubItemForegroundPressed",
                     L"MenuFlyoutSubItemForegroundSubMenuOpened",
                     L"MenuFlyoutSubItemChevron",
                     L"MenuFlyoutSubItemChevronPointerOver",
                     L"MenuFlyoutSubItemChevronPressed",
                     L"MenuFlyoutSubItemChevronSubMenuOpened",
                     L"ToggleMenuFlyoutItemForegroundPointerOver",
                     L"ToggleMenuFlyoutItemForegroundPressed"}) {
        InsertResource(res, key, text);
    }
    if (cfg.colorIcons) {
        auto blue = MakeBrush(kBlue);
        for (auto key : {L"ToggleMenuFlyoutItemCheckGlyphForeground",
                         L"ToggleMenuFlyoutItemCheckGlyphForegroundPointerOver",
                         L"ToggleMenuFlyoutItemCheckGlyphForegroundPressed"}) {
            InsertResource(res, key, blue);
        }
    }

    if (auto item = base.try_as<wuxc::MenuFlyoutItem>()) {
        ThemeMenuIcon(item.Icon(), cfg);
        item.Loaded([](wf::IInspectable const& sender, wux::RoutedEventArgs const&) {
            try {
                auto loaded = sender.as<wuxc::MenuFlyoutItem>();
                ThemeMenuIcon(loaded.Icon(), GetSettingsSnapshot());
                ThemeMenuPresenter(loaded);
            } catch (...) {
                Wh_Log(L"Menu theming on load failed");
            }
        });
    } else if (auto sub = base.try_as<wuxc::MenuFlyoutSubItem>()) {
        // Submenus other mods add (Taskbar App Memory's Remember positions).
        ThemeMenuIcon(sub.Icon(), cfg);
        sub.Loaded([](wf::IInspectable const& sender, wux::RoutedEventArgs const&) {
            try {
                auto loaded = sender.as<wuxc::MenuFlyoutSubItem>();
                ThemeMenuIcon(loaded.Icon(), GetSettingsSnapshot());
                ThemeMenuPresenter(loaded);
            } catch (...) {
                Wh_Log(L"Submenu theming on load failed");
            }
        });
    }
}

// Themes a row once, and the rows of its submenu, so the submenu's own
// presenter gets the Mocha look when those rows load.
void ThemeMenuItemOnce(wf::IInspectable const& obj, int depth) {
    auto item = obj ? obj.try_as<wuxc::MenuFlyoutItemBase>() : nullptr;
    if (!item) {
        return;
    }
    auto marker = winrt::box_value(winrt::hstring(L"SeamlessTaskbarUtilitiesThemed"));
    auto res = item.Resources();
    if (!res.HasKey(marker)) {
        ThemeMenuItem(item);
        res.Insert(marker, winrt::box_value(true));
    }
    if (depth < 3) {
        if (auto sub = item.try_as<wuxc::MenuFlyoutSubItem>()) {
            for (auto const& child : sub.Items()) {
                ThemeMenuItemOnce(child, depth + 1);
            }
        }
    }
}

// Auto-hide taskbar, after Windows 11 Taskbar Auto-Hide in Context by
// oyrslyng: ABM_SETSTATE on the main taskbar, the switch in Taskbar settings.
bool IsTaskbarAutoHide() {
    APPBARDATA abd{sizeof(abd)};
    abd.hWnd = FindWindowW(L"Shell_TrayWnd", nullptr);
    return abd.hWnd && (SHAppBarMessage(ABM_GETSTATE, &abd) & ABS_AUTOHIDE);
}

void OnAutoHideClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    HWND prev = g_menuPrevForeground.load();
    RunAsyncTracked([prev]() {
        APPBARDATA abd{sizeof(abd)};
        abd.hWnd = FindWindowW(L"Shell_TrayWnd", nullptr);
        if (!abd.hWnd) {
            return;
        }
        bool hide = !(SHAppBarMessage(ABM_GETSTATE, &abd) & ABS_AUTOHIDE);
        abd.lParam = hide ? ABS_AUTOHIDE : ABS_ALWAYSONTOP;
        SHAppBarMessage(ABM_SETSTATE, &abd);
        Wh_Log(L"Taskbar auto-hide %s", hide ? L"on" : L"off");
        if (!hide) {
            return;
        }
        // The taskbar only slides away once it loses focus: after the menu
        // closes, hand focus back to the window that had it, or the desktop.
        Sleep(120);
        if (g_unloading.load()) {
            return;
        }
        HWND target = prev && IsWindow(prev) && IsWindowVisible(prev)
                          ? prev
                          : FindWindowW(L"Progman", nullptr);
        if (target) {
            SetForegroundWindow(target);
        }
    });
}

void AppendInjectedItems(void* vectorThis) {
    auto cfg = GetSettingsSnapshot();

    const MenuItemSpec specs[] = {
        {cfg.showRestartExplorer, cfg.textRestartExplorer, L"\xE72C",
         &OnRestartExplorerClick},
        {cfg.showCleanTemp, cfg.textCleanTemp, L"\xE74D", &OnCleanTempClick},
        {cfg.showReduceMemory, cfg.textReduceMemory, L"\xE950",
         &OnReduceMemoryClick},
        {cfg.showRestartGpu, cfg.textRestartGpu, L"\xE7F4", &OnRestartGpuClick},
        {cfg.showGetIp, cfg.textGetIp, L"\xE968", &OnGetIpClick},
        {cfg.showRebuildCache, cfg.textRebuildCache, L"\xE8B9",
         &OnRebuildCacheClick},
        {cfg.showFlushDns, cfg.textFlushDns, L"\xE774", &OnFlushDnsClick},
        {cfg.showAutoHide, cfg.textAutoHide,
         cfg.showAutoHide && IsTaskbarAutoHide() ? L"\xE73A" : L"\xE739",
         &OnAutoHideClick},
        {cfg.separators && g_sepActive.load() &&
             sep::IsContextMenuInteractionMode(),
         cfg.textAddSeparator, L"\xE710", &sep::OnAddSeparatorMenuClick},
    };

    bool anyInjected = false;
    for (const auto& spec : specs) {
        if (!spec.enabled) {
            continue;
        }

        wuxc::MenuFlyoutItem menuItem;
        if (!anyInjected) {
            menuItem.Name(kGuardItemName);
        }
        menuItem.Text(spec.text);
        menuItem.Icon(CreateFluentIcon(spec.glyph));
        menuItem.Click(wux::RoutedEventHandler{spec.handler});
        ThemeMenuItem(menuItem);

        MenuFlyoutItemBaseVector_Append_Original(vectorThis, menuItem);
        anyInjected = true;
    }

    if (anyInjected) {
        wuxc::MenuFlyoutSeparator separator;
        ThemeMenuItem(separator);
        MenuFlyoutItemBaseVector_Append_Original(vectorThis, separator);
        g_currentMenuInjected = true;
    }
}

void __cdecl MenuFlyoutItemBaseVector_Append_Hook(
    void* pThis,
    wuxc::MenuFlyoutItemBase const& item) {
    if (g_taskbarSettingsMenuDepth > 0 && !g_currentMenuInjected) {
        try {
            if (!IsSeparator(item) && !IsNamedItem(item, kGuardItemName)) {
                AppendInjectedItems(pThis);
            }
        } catch (...) {
            Wh_Log(L"Taskbar menu append inspection failed");
        }
    }
    if (g_taskbarSettingsMenuDepth > 0) {
        try {
            ThemeMenuItem(item);
        } catch (...) {
            Wh_Log(L"Stock menu item theming failed");
        }
    }

    MenuFlyoutItemBaseVector_Append_Original(pThis, item);
}

struct ScopedTaskbarSettingsMenuBuild {
    bool outer = false;

    ScopedTaskbarSettingsMenuBuild() {
        outer = g_taskbarSettingsMenuDepth++ == 0;
        if (outer) {
            g_currentMenuInjected = false;
        }
    }

    ~ScopedTaskbarSettingsMenuBuild() { g_taskbarSettingsMenuDepth--; }
};

using ContextMenus_ShowTaskbarSettingsContextMenu_t =
    void(__cdecl*)(wux::FrameworkElement const& target,
                   void* taskbarSettings,
                   wuxi::ContextRequestedEventArgs const& args,
                   unsigned long long options);
ContextMenus_ShowTaskbarSettingsContextMenu_t
    ContextMenus_ShowTaskbarSettingsContextMenu_Original;

void __cdecl ContextMenus_ShowTaskbarSettingsContextMenu_Hook(
    wux::FrameworkElement const& target,
    void* taskbarSettings,
    wuxi::ContextRequestedEventArgs const& args,
    unsigned long long options) {
    try {
        if (target && target.XamlRoot()) {
            g_lastTargetWeak = target;
        }
    } catch (...) {
    }
    HWND foreground = GetForegroundWindow();
    if (foreground && foreground != FindWindowW(L"Shell_TrayWnd", nullptr)) {
        g_menuPrevForeground = foreground;
    }

    ScopedTaskbarSettingsMenuBuild scopedBuild;

    ContextMenus_ShowTaskbarSettingsContextMenu_Original(
        target, taskbarSettings, args, options);
}

// The clock's right-click menu (Adjust date and time, Notifications settings)
// is a MenuFlyout that SystemTray.dll keeps on the clock's Grid. Every tray
// icon menu, the clock's included, opens through
// ContextMenuPositionHelper::ShowContextMenuFlyout(grid, ...), which calls the
// flyout's ShowAt through its vtable. Hooking that one function themes the
// menu just before it opens. Counter: LocalStorage\attachedMenuShows.
const wchar_t kThemedMarker[] = L"SeamlessTaskbarUtilitiesThemed";
std::atomic<int> g_attachedMenuShows{0};

void ThemeWholeMenu(wuxc::MenuFlyout const& menu) {
    auto cfg = GetSettingsSnapshot();
    if (!menu.MenuFlyoutPresenterStyle()) {
        wux::Style style(winrt::xaml_typename<wuxc::MenuFlyoutPresenter>());
        style.Setters().Append(wux::Setter(wuxc::Control::BackgroundProperty(),
                                           MenuBackground(nullptr, cfg)));
        if (cfg.borderStyle != 2) {
            double w = cfg.borderWidth;
            style.Setters().Append(wux::Setter(wuxc::Control::BorderBrushProperty(),
                                               MakeBorderBrush(cfg)));
            style.Setters().Append(wux::Setter(wuxc::Control::BorderThicknessProperty(),
                                               winrt::box_value(wux::Thickness{w, w, w, w})));
        }
        menu.MenuFlyoutPresenterStyle(style);
    }
    for (auto const& item : menu.Items()) {
        ThemeMenuItemOnce(item, 0);
    }
}

bool ThemeFlyout(wuxcp::FlyoutBase const& flyout) {
    if (auto menu = flyout ? flyout.try_as<wuxc::MenuFlyout>() : nullptr) {
        ThemeWholeMenu(menu);
        return true;
    }
    return false;
}

void ThemeTrayIconMenu(wuxc::Grid const& grid) {
    try {
        if (!grid) {
            return;
        }
        bool themed = ThemeFlyout(wuxcp::FlyoutBase::GetAttachedFlyout(grid));
        themed |= ThemeFlyout(grid.ContextFlyout());
        if (themed) {
            Wh_SetIntValue(L"attachedMenuShows", ++g_attachedMenuShows);
        }
    } catch (...) {
        Wh_Log(L"Tray icon menu theming failed");
    }
}

using ShowContextMenuFlyout_t = void(__cdecl*)(wuxc::Grid const& grid,
                                               double scale,
                                               int taskbarLocation,
                                               void* const& xamlRoot);
ShowContextMenuFlyout_t ShowContextMenuFlyout_Original;
std::atomic<bool> g_systemTrayModuleHooked{false};

void __cdecl ShowContextMenuFlyout_Hook(wuxc::Grid const& grid,
                                        double scale,
                                        int taskbarLocation,
                                        void* const& xamlRoot) {
    ThemeTrayIconMenu(grid);
    ShowContextMenuFlyout_Original(grid, scale, taskbarLocation, xamlRoot);
}

void HookSystemTraySymbols(HMODULE module, bool applyHookOperations) {
    if (!module || g_systemTrayModuleHooked.exchange(true)) {
        return;
    }
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {
                LR"(void __cdecl ContextMenuPositionHelper::ShowContextMenuFlyout(struct winrt::Windows::UI::Xaml::Controls::Grid const &,double,enum winrt::WindowsUdk::UI::Shell::TaskbarLocation,struct winrt::Windows::UI::Xaml::XamlRoot const &))",
            },
            &ShowContextMenuFlyout_Original,
            ShowContextMenuFlyout_Hook,
        },
    };
    if (!HookSymbols(module, symbolHooks, ARRAYSIZE(symbolHooks))) {
        Wh_Log(L"Failed to hook SystemTray tray menu");
        return;
    }
    Wh_SetIntValue(L"attachedMenuShows", 0);
    if (applyHookOperations) {
        Wh_ApplyHookOperations();
    }
}
// ============================================================================
// Symbol Hooking & Mod Lifecycle
// ============================================================================

using RtlGetVersion_t = LONG(WINAPI*)(OSVERSIONINFOW* versionInfo);

DWORD GetWindowsBuild() {
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    auto rtlGetVersion = ntdll ? reinterpret_cast<RtlGetVersion_t>(
                                     GetProcAddress(ntdll, "RtlGetVersion"))
                               : nullptr;
    if (!rtlGetVersion) {
        return 0;
    }

    OSVERSIONINFOW versionInfo = {};
    versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);

    if (rtlGetVersion(&versionInfo) != 0) {
        return 0;
    }

    return versionInfo.dwBuildNumber;
}

HMODULE GetTaskbarViewModuleHandle() {
    HMODULE module = GetModuleHandleW(L"Taskbar.View.dll");
    if (!module) {
        module = GetModuleHandleW(L"ExplorerExtensions.dll");
    }
    return module;
}

bool HookTaskbarViewDllSymbols(HMODULE module) {
    // Taskbar.View.dll, ExplorerExtensions.dll
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {
                LR"(void __cdecl winrt::Taskbar::implementation::ContextMenus::ShowTaskbarSettingsContextMenu(struct winrt::Windows::UI::Xaml::FrameworkElement const &,struct winrt::WindowsUdk::UI::Shell::TaskbarSettings const &,struct winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const &,unsigned __int64))",
            },
            &ContextMenus_ShowTaskbarSettingsContextMenu_Original,
            ContextMenus_ShowTaskbarSettingsContextMenu_Hook,
        },
        {
            {
                LR"(public: __cdecl winrt::impl::consume_Windows_Foundation_Collections_IVector<struct winrt::Windows::Foundation::Collections::IVector<struct winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase>,struct winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase>::Append(struct winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase const &)const )",
            },
            &MenuFlyoutItemBaseVector_Append_Original,
            MenuFlyoutItemBaseVector_Append_Hook,
        },
    };

    return HookSymbols(module, symbolHooks, ARRAYSIZE(symbolHooks));
}

void HandleLoadedModuleIfTaskbarView(HMODULE module, bool applyHookOperations) {
    if (!module || g_taskbarViewModuleHooked.load()) {
        return;
    }

    if (GetTaskbarViewModuleHandle() != module) {
        return;
    }

    if (g_taskbarViewModuleHooked.exchange(true)) {
        return;
    }

    if (HookTaskbarViewDllSymbols(module)) {
        if (applyHookOperations) {
            Wh_ApplyHookOperations();
        }
    } else {
        Wh_Log(L"Failed to hook Taskbar.View symbols");
    }
}

using LoadLibraryExW_t = decltype(&LoadLibraryExW);
LoadLibraryExW_t LoadLibraryExW_Original;

HMODULE WINAPI LoadLibraryExW_Hook(LPCWSTR lpLibFileName,
                                   HANDLE hFile,
                                   DWORD dwFlags) {
    HMODULE module = LoadLibraryExW_Original(lpLibFileName, hFile, dwFlags);
    if (module) {
        HandleLoadedModuleIfTaskbarView(module, true);
        if (g_sepActive.load()) {
            sep::OnModuleLoaded(lpLibFileName, module);
        }
        if (!g_systemTrayModuleHooked.load() &&
            module == GetModuleHandleW(L"SystemTray.dll")) {
            HookSystemTraySymbols(module, true);
        }
    }
    return module;
}

std::wstring LoadStringSetting(const wchar_t* name,
                               const wchar_t* defaultValue) {
    auto val = WindhawkUtils::StringSetting::make(name);
    return val.get()[0] != L'\0' ? val.get() : defaultValue;
}

int ClampInt(int value, int lo, int hi) {
    return value < lo ? lo : value > hi ? hi : value;
}

// Reads "#RRGGBB" or "#AARRGGBB"; anything else keeps the fallback.
wu::Color ParseColor(const wchar_t* name, wu::Color fallback) {
    auto setting = WindhawkUtils::StringSetting::make(name);
    std::wstring s = setting.get();
    if (!s.empty() && s[0] == L'#') {
        s.erase(0, 1);
    }
    if (s.size() != 6 && s.size() != 8) {
        return fallback;
    }
    wchar_t* end = nullptr;
    unsigned long v = wcstoul(s.c_str(), &end, 16);
    if (!end || *end != L'\0') {
        return fallback;
    }
    uint8_t a = s.size() == 8 ? static_cast<uint8_t>(v >> 24) : 255;
    return wu::Color{a, static_cast<uint8_t>(v >> 16),
                     static_cast<uint8_t>(v >> 8), static_cast<uint8_t>(v)};
}

void LoadSettings() {
    ModSettings fresh;
    fresh.showRestartExplorer = Wh_GetIntSetting(L"restartExplorer.enabled");
    fresh.textRestartExplorer =
        LoadStringSetting(L"restartExplorer.label", L"Restart Explorer");

    fresh.showCleanTemp = Wh_GetIntSetting(L"cleanTemp.enabled");
    fresh.textCleanTemp = LoadStringSetting(L"cleanTemp.label", L"Clean Temp");
    fresh.cleanRecycleBin = Wh_GetIntSetting(L"cleanTemp.cleanRecycleBin");
    fresh.notifyCleanTemp = Wh_GetIntSetting(L"cleanTemp.showCard");

    fresh.showReduceMemory = Wh_GetIntSetting(L"reduceMemory.enabled");
    fresh.textReduceMemory =
        LoadStringSetting(L"reduceMemory.label", L"Reduce Memory");
    fresh.notifyReduceMemory = Wh_GetIntSetting(L"reduceMemory.showCard");

    fresh.showRestartGpu = Wh_GetIntSetting(L"restartGpu.enabled");
    fresh.textRestartGpu =
        LoadStringSetting(L"restartGpu.label", L"Restart Graphics Driver");

    fresh.showGetIp = Wh_GetIntSetting(L"getIp.enabled");
    fresh.textGetIp = LoadStringSetting(L"getIp.label", L"Get IP Address");
    fresh.queryPublicIp = Wh_GetIntSetting(L"getIp.queryPublicIp");
    fresh.copyIpToClipboard = Wh_GetIntSetting(L"getIp.copyToClipboard");

    fresh.showRebuildCache = Wh_GetIntSetting(L"rebuildCache.enabled");
    fresh.textRebuildCache = LoadStringSetting(
        L"rebuildCache.label", L"Rebuild Icon & Thumbnail Cache");
    fresh.notifyRebuildCache = Wh_GetIntSetting(L"rebuildCache.showCard");

    fresh.showFlushDns = Wh_GetIntSetting(L"flushDns.enabled");
    fresh.textFlushDns =
        LoadStringSetting(L"flushDns.label", L"Clean DNS Cache");
    fresh.notifyFlushDns = Wh_GetIntSetting(L"flushDns.showCard");

    fresh.showAutoHide = Wh_GetIntSetting(L"autoHide.enabled");
    fresh.textAutoHide =
        LoadStringSetting(L"autoHide.label", L"Auto-hide taskbar");

    fresh.separators = Wh_GetIntSetting(L"iconSeparators.enabled");
    fresh.textAddSeparator =
        LoadStringSetting(L"iconSeparators.label", L"Add separator");

    {
        auto font = WindhawkUtils::StringSetting::make(L"look.fontFamily");
        fresh.fontFamily = font.get();
    }
    {
        auto weight = WindhawkUtils::StringSetting::make(L"look.fontWeight");
        std::wstring_view w = weight.get();
        fresh.fontWeight = w == L"light"      ? 300
                           : w == L"regular"  ? 400
                           : w == L"semibold" ? 600
                           : w == L"bold"     ? 700
                                              : 500;
    }
    {
        auto border = WindhawkUtils::StringSetting::make(L"look.border");
        std::wstring_view b = border.get();
        fresh.borderStyle = b == L"solid" ? 1 : b == L"none" ? 2 : 0;
    }
    fresh.gradientStart = ParseColor(L"look.gradientStart", fresh.gradientStart);
    fresh.gradientEnd = ParseColor(L"look.gradientEnd", fresh.gradientEnd);
    fresh.borderWidth = ClampInt(Wh_GetIntSetting(L"look.borderWidth"), 1, 4);
    fresh.cardOpacity = ClampInt(Wh_GetIntSetting(L"look.cardOpacity"), 85, 100);
    fresh.matchTaskbar = Wh_GetIntSetting(L"look.matchTaskbar");
    fresh.colorIcons = Wh_GetIntSetting(L"look.colorIcons");

    std::lock_guard<std::mutex> lock(g_settingsMutex);
    g_settings = std::move(fresh);
}

BOOL Wh_ModInit() {
    g_unloading.store(false);
    LoadSettings();

    DWORD build = GetWindowsBuild();
    if (build && build < 22000) {
        Wh_Log(L"Unsupported Windows build %lu", build);
        return TRUE;
    }

    if (HMODULE taskbarViewModule = GetTaskbarViewModuleHandle()) {
        g_taskbarViewModuleHooked.store(true);
        if (!HookTaskbarViewDllSymbols(taskbarViewModule)) {
            Wh_Log(L"Failed to hook Taskbar.View symbols during init");
        }
    }
    HookSystemTraySymbols(GetModuleHandleW(L"SystemTray.dll"), false);

    HMODULE kernelBase = GetModuleHandleW(L"kernelbase.dll");
    auto loadLibraryExW =
        kernelBase ? reinterpret_cast<LoadLibraryExW_t>(
                         GetProcAddress(kernelBase, "LoadLibraryExW"))
                   : nullptr;
    if (loadLibraryExW) {
        WindhawkUtils::SetFunctionHook(loadLibraryExW, LoadLibraryExW_Hook,
                                       &LoadLibraryExW_Original);
    }

    if (GetSettingsSnapshot().separators) {
        g_sepActive.store(sep::ExplorerModInit());
        if (!g_sepActive.load()) {
            Wh_Log(L"Icon separators did not start in this process");
        }
    }

    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_systemTrayModuleHooked.load()) {
        HookSystemTraySymbols(GetModuleHandleW(L"SystemTray.dll"), true);
    }
    if (!g_taskbarViewModuleHooked.load()) {
        if (HMODULE taskbarViewModule = GetTaskbarViewModuleHandle()) {
            HandleLoadedModuleIfTaskbarView(taskbarViewModule, true);
        }
    }
    if (g_sepActive.load()) {
        sep::ExplorerModAfterInit();
    }
}

BOOL Wh_ModSettingsChanged(BOOL* bReload) {
    const bool wasSeparators = GetSettingsSnapshot().separators;
    LoadSettings();
    if (GetSettingsSnapshot().separators != wasSeparators) {
        *bReload = TRUE;
        return TRUE;
    }
    if (g_sepActive.load()) {
        return sep::ExplorerModSettingsChanged(bReload);
    }
    *bReload = FALSE;
    return TRUE;
}

void Wh_ModBeforeUninit() {
    if (g_sepActive.load()) {
        sep::ExplorerModBeforeUninit();
    }
}

void Wh_ModUninit() {
    if (g_sepActive.load()) {
        sep::ExplorerModUninit();
    }

    std::vector<HANDLE> threads;
    {
        std::lock_guard<std::mutex> lock(g_threadsMutex);
        g_unloading.store(true);
        threads.swap(g_threads);
    }

    CancelActivePublicIpRequest();

    for (HANDLE thread : threads) {
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    }

    if (HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd()) {
        RunFromWindowThread(hTaskbarWnd,
                            []() { CloseActiveFlyoutOnUIThread(); });
    }
}
