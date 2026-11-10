#include <windowsx.h>
#include <map>
#include <memory>
#include <wincodec.h>
// ==WindhawkMod==
// @id              seamless-launchpad
// @name            Seamless Launchpad
// @description     A fullscreen GPU rendered grid of all your apps in place of Start, with instant search, adjustable blur, wiggle edit mode and power buttons
// @version         2.4.2
// @author          DavidHiFi, Rafael Mendes
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -lshell32 -lshcore -ldwmapi -ld2d1 -ldwrite -ld3d11 -ldxgi -lole32 -luuid -lcomdlg32 -luxtheme -lpropsys -lpowrprof -lwindowscodecs -lole32 -limm32 -lcomctl32
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Launchpad

Replaces the Start menu with a fullscreen grid of all your apps, in the style
of the macOS Launchpad, with instant search and a blurred background.

![Seamless Launchpad preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-launchpad.png)

## Features
- **Fullscreen.** Fills the monitor the mouse is on, or one monitor you pick.
  It leaves the taskbar, side bars and the Standalone Dock visible, or covers
  the whole screen if you turn that on.
- **Your choice of apps.** The "All apps" list of Start, your desktop icons,
  both together, or only the apps you pin. With only pinned apps, search still
  finds every app, and right-click pins or unpins one.
- **Scroll or pages.** One list that scrolls, or pages that flip left and
  right with dots below, like Launchpad.
- **Instant search.** Just type. Case and accents don't matter, and names that
  start with your text come first. The search box is a real text field, with a
  blinking caret and click-and-drag selection, and Ctrl+A, copy, cut and paste
  work as usual.
- **GPU rendered.** The grid, the blur and the folder glass all rasterize on
  the GPU (Direct2D over Direct3D), so it stays snappy at any resolution.
- **Wiggle edit mode.** Grab and hold any icon and every icon starts to
  wiggle, like iOS, while you arrange them.
- **Adjustable blur.** Pick the blur type, strength, opacity and color of the
  background. The search bar, folder glass, dots and power bar use the
  Catppuccin Mocha palette.
- **Opens like Start.** The Windows key, Ctrl+Esc and the Start button of the
  taskbar or the Standalone Dock all open it.
- **Your own Windows key.** The Windows key, Shift + Windows key and the Start
  button can each open this grid, the original Start, or a program of your
  choice, such as a launcher. The program starts even when it isn't running,
  so this replaces the same feature of Open-Shell.
- **Your own order.** Drag icons to move them, across pages and in and out
  of folders. Drop an app on another to make a folder.
- **Right-click menu.** Open, run as administrator, open the file location
  or the shortcut location, change the icon, pin or unpin, or remove an app
  from the grid.
- **Power buttons.** A small glass bar at the bottom with Lock, Sign out,
  Sleep, Hibernate, Restart and Shut down. Pick which ones show, or hide the
  bar. The first click asks ("Click again to restart") and a second click on
  the same button does it. Turn on **No confirmation** to act on the first
  click.
- **Works over administrator windows.** Windows keeps keys pressed in an app
  running as administrator away from Explorer, so Shift + Windows key can't
  open the grid there. The optional helper in the `helper` folder of this
  mod's repository runs as administrator and fixes that (see its README).

## Keyboard and mouse
| Key | Action |
| --- | --- |
| Type | Search |
| Backspace, Ctrl+Backspace, Delete | Delete the selection, a letter, or the last word |
| Ctrl+A, Ctrl+C, Ctrl+X, Ctrl+V | Select all, copy, cut, paste |
| Left, Right, Home, End | Move the caret in the search; hold Shift to select. With an empty search, Left and Right pick an app |
| Up, Down, Enter | Pick an app and open it. While searching, the first result is already picked |
| Esc | Clear the search, or close when the search is empty |
| Mouse wheel, Page Up, Page Down | Scroll, or flip pages |
| Sideways scroll, page dots | Flip pages |
| The ... button, top right | Open this mod's own settings window (it saves to the same settings as Windhawk's page), bring back removed apps, or sort A to Z |
| Grab and hold an icon | All icons wiggle; drag to move it. Hold it at the screen's edge to flip the page |
| Drop an app on another | Make a folder. Drop more apps on it to add them |
| Hold an app over a folder | The folder opens, so you can place it inside |
| Drag an app out of an open folder | Take it out of the folder |
| Type in an open folder | Rename it |
| Right-click an icon | Its menu. Right-click empty space for the ... menu |
| Power buttons, bottom | Lock, sign out, sleep, hibernate, restart or shut down. Click twice, or once with No confirmation on |

Your order, folders, removed apps and icons are kept in Windhawk's storage
folder for this mod. New apps go at the end.

Clicking outside the icons or switching to another window closes it.

## Blur types
- **Adjustable** (default): a blurred snapshot of the screen, taken when Start
  opens. It stays still while Start is open.
- **Windows acrylic** and **Windows blur**: drawn by Windows, so they follow
  what changes behind them. Windows fixes their strength, so the strength
  setting doesn't apply.
- **No blur**: only the color.

## Notes
- Disable the original Fullscreen Start (Launchpad style) before you enable
  this mod. Both replace Start, so only one should run.
- This mod used to be called Fullscreen Start Plus. If you used that one,
  disable it. On its first run this mod copies your order, folders, pins and
  icons from the old mod's storage folder.
- The power buttons never force apps to close. If an app has unsaved work,
  Windows asks about it as usual. Hibernate shows only when hibernation is on
  in Windows.
- Set **Windows key**, **Shift + Windows key** or **Start button** to "Open
  the original Start" to get the normal Start menu for that action. Shift +
  Windows key opens it by default.
- If Open-Shell or another Start replacement also takes the Windows key, turn
  that feature off there, or it gets the key first.
- The first time the mod loads, Windhawk downloads the symbols of
  `twinui.pcshell.dll`, which can take a minute.
- Setting changes apply the next time Start opens.

## Credits
Based on [Fullscreen Start (Launchpad style)](https://windhawk.net/mods/fullscreen-start)
by [Rafael Mendes](https://github.com/RafaelMendes1407). MIT.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- winKeyAction: grid
  $name: Windows key
  $description: Also Ctrl+Esc.
  $options:
  - grid: Open this grid
  - start: Open the original Start
  - program: Run the program below
- shiftWinKeyAction: start
  $name: Shift + Windows key
  $options:
  - grid: Open this grid
  - start: Open the original Start
  - program: Run the program below
- startButtonAction: grid
  $name: Start button
  $description: The taskbar Start button, the Standalone Dock's, and every other way Start opens that is not the keyboard.
  $options:
  - grid: Open this grid
  - start: Open the original Start
  - program: Run the program below
- program: ""
  $name: Program
  $description: 'What "Run the program below" starts. A command line such as "C:\Program Files\App\app.exe" --flag, or a shortcut, file, folder or web address'
- monitor: mouse
  $name: Monitor
  $description: Where the grid opens. Monitors 2 to 4 are the other monitors, counted left to right. If the picked monitor is not connected, it opens where the mouse is.
  $options:
  - mouse: The monitor with the mouse
  - "1": Main monitor
  - "2": Monitor 2
  - "3": Monitor 3
  - "4": Monitor 4
- appSource: allApps
  $name: Apps to show
  $description: With pinned apps, search still finds every app. Right-click an app to pin or unpin it.
  $options:
  - allApps: Start menu apps (the All apps list)
  - desktop: Desktop icons
  - both: Start menu apps and desktop icons
  - pinned: Only the apps you pin
- gridLayout: scroll
  $name: Layout
  $description: How the grid is arranged.
  $options:
  - scroll: One list that scrolls up and down
  - pages: Pages that flip left and right, like Launchpad
- gridColumns: 0
  $name: Columns
  $description: "0 to 30. 0 picks a number that fits the screen (Suggested: 0)."
- coverScreen: false
  $name: Cover the whole screen
  $description: On, the grid also covers the taskbar, side bars and the Standalone Dock. Off, they stay visible.
- gridIconSize: 72
  $name: Icon size
  $description: "24 to 192 (Suggested: 72). Pixels at 100% scaling."
- showLabels: true
  $name: Icon labels
  $description: On, the app name shows under each icon. Off, icons only.
- normalizeIcons: true
  $name: Fill small icons
  $description: Scale small or padded icons to full size.
- blurMode: custom
  $name: Background blur
  $description: The kind of blur behind the grid.
  $options:
  - custom: Adjustable (uses the strength below)
  - acrylic: Windows acrylic (DWM)
  - blur: Windows blur (DWM)
  - none: No blur
- blurAmount: 60
  $name: Blur strength
  $description: "0 to 100 (Suggested: 60). Only for the adjustable blur. The Windows ones have a fixed strength."
- backgroundOpacity: 30
  $name: Background opacity (%)
  $description: "0 to 100 (Suggested: 30). 0 leaves only the blur, 100 covers everything with the color."
- tintColor: "#000000"
  $name: Background color
  $description: In hexadecimal, like #1E1E2E.
- accentColor: "#89B4FA"
  $name: Accent color
  $description: In hexadecimal, like #89B4FA. Tints the glows and highlights.
- glowStrength: 60
  $name: Glow strength
  $description: "0 to 100 (Suggested: 60). How strongly hovered buttons glow."
- glowSize: 14
  $name: Glow size
  $description: "4 to 40 (Suggested: 14). How far a glow spreads, in DIP at 100% scaling."
- chromeOpacity: 90
  $name: Search bar and dock opacity (%)
  $description: "0 to 100 (Suggested: 90). How solid the search bar and the power dock are."
- powerBar: true
  $name: Power dock
  $description: The pill of power buttons at the bottom of the grid.
- dockAlignment: center
  $name: Dock position
  $description: Where the power dock sits along the bottom edge.
  $options:
  - left: Left
  - center: Center
  - right: Right
- powerButtons:
  - lock: true
    $name: Lock
  - signOut: true
    $name: Sign out
  - sleep: true
    $name: Sleep
  - hibernate: true
    $name: Hibernate
    $description: Shows only when hibernation is turned on in Windows.
  - restart: true
    $name: Restart
  - shutDown: true
    $name: Shut down
  $name: Power dock buttons
- powerNoConfirm: false
  $name: Skip confirmation
  $description: On, a power button acts on the first click. Off, the first click arms it and a second click on the same button confirms.
- wiggle: true
  $name: Edit mode wiggle
  $description: While you drag an icon, all icons wiggle like on iOS.
- holdTime: 420
  $name: Drag hold time
  $description: "150 to 1500 (Suggested: 420). Milliseconds to hold an icon before dragging starts."
- animations: true
  $name: Animations
  $description: Off, everything snaps instantly. Opening, folders, hover fades, tile moves and wiggle all turn off.
- settingsGlass: true
  $name: Blurred settings window
  $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.
- nativeSettingsTitleBar: false
  $name: Native Windows title bar
  $description: Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.
- settingsTitleButtons: native
  $name: Title bar buttons
  $description: Who draws minimize, maximize and close on the window's own title bar. Windows buttons look like every other app's, title bar mods included. Save, then reopen settings to apply.
  $options:
  - native: Windows buttons (like other apps)
  - builtin: Built-in buttons
- settingsTrayIcon: true
  $name: Tray icon
  $description: A Launchpad icon in the system tray. Click it to open these settings, right-click it for a menu.
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <knownfolders.h>
#include <shellscalingapi.h>
#include <commdlg.h>
#include <uxtheme.h>
#include <dwmapi.h>
#include <propsys.h>
#include <powrprof.h>
// Otherwise the Win32 macro renames ID2D1RenderTarget::DrawText.
#undef DrawText
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d3d11.h>
#include <dwrite.h>
#include <wrl/client.h>
#include <windhawk_utils.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

using Microsoft::WRL::ComPtr;

extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace {

constexpr WCHAR kWindowClass[] = L"WindhawkSeamlessLaunchpad";
constexpr WCHAR kBackdropClass[] = L"WindhawkSeamlessLaunchpadBackdrop";
constexpr WCHAR kAppsFolder[] = L"shell:AppsFolder\\";

// From the Standalone Dock mod: the edge strip it takes.
constexpr WCHAR kDockClass[] = L"WindhawkMacDock";
constexpr WCHAR kDockPlateClass[] = L"WindhawkMacDockPlate";
constexpr WCHAR kDockEdgeProp[] = L"WindhawkMacDock.Edge";
constexpr WCHAR kDockReservedProp[] = L"WindhawkMacDock.Reserved";

constexpr UINT WM_APP_TOGGLE = WM_APP + 1;
constexpr UINT WM_APP_APPS = WM_APP + 2;  // lParam: new AppList*.
constexpr UINT WM_APP_RELOAD = WM_APP + 3;
constexpr UINT WM_APP_QUIT = WM_APP + 4;
constexpr UINT WM_APP_RUN = WM_APP + 5;
constexpr UINT WM_APP_SHIFT_WIN = WM_APP + 6;

constexpr UINT_PTR kTimerFrame = 1;
constexpr UINT_PTR kTimerFirstLoad = 4;
constexpr UINT_PTR kTimerShiftWin = 5;
constexpr UINT_PTR kTimerCaret = 6;  // The search caret's blink.
constexpr UINT_PTR kTimerPowerArm = 7;  // An unconfirmed power button resets.

constexpr GUID kBhidEnumItems = {
    0x94f60519,
    0x2850,
    0x4924,
    {0xaa, 0x5a, 0xd1, 0x5e, 0x84, 0x86, 0x80, 0x39}};

double Now() {
    static LARGE_INTEGER frequency = [] {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        return f;
    }();
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / frequency.QuadPart;
}

std::wstring ToLower(std::wstring text) {
    if (!text.empty()) {
        LCMapStringEx(LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, text.data(),
                      (int)text.size(), text.data(), (int)text.size(),
                      nullptr, nullptr, 0);
    }
    return text;
}

bool EndsWith(const std::wstring& text, const std::wstring& suffix) {
    return text.size() >= suffix.size() &&
           text.compare(text.size() - suffix.size(), suffix.size(), suffix) ==
               0;
}

////////////////////////////////////////////////////////////////////////////////
// Settings

enum class BlurMode { Custom, Acrylic, Blur, None };
enum class AppSource { AllApps, Desktop, Both, Pinned };
enum class KeyAction { Grid, Start, Program };
enum class DockAlign { Left, Center, Right };

struct Settings {
    BlurMode blurMode = BlurMode::Custom;
    int blurAmount = 60;
    float opacity = 0.3f;
    D2D1_COLOR_F tint{0, 0, 0, 1};
    int iconSize = 72;
    int columns = 0;
    bool pages = false;
    bool coverScreen = false;
    AppSource source = AppSource::AllApps;
    int monitor = 0;  // 0: the one with the mouse; 1: main; 2+: the others, left to right.
    std::wstring program;
    bool powerBar = true;
    bool powerShown[6] = {true, true, true, true, true, true};  // kPower order.
    bool powerNoConfirm = false;
    // 3.0.0 look and feel. Defaults here; schema and parsing in LoadSettings.
    D2D1_COLOR_F accent{0x89 / 255.0f, 0xB4 / 255.0f, 0xFA / 255.0f, 1};  // Mocha blue.
    float glowStrength = 0.6f;    // 0..1, hover/focus glow alpha.
    int glowSize = 14;            // DIP, glow spread.
    float chromeOpacity = 0.9f;   // 0..1, search bar and dock fill (Mocha base).
    DockAlign dockAlign = DockAlign::Center;
    bool wiggle = true;           // Edit-mode wiggle while dragging.
    bool animations = true;       // Off: every transition snaps.
    bool trayIcon = true;         // A tray icon that opens the settings.
    int holdMs = 420;             // Press time before an icon lifts for dragging.
    bool showLabels = true;
    bool normalizeIcons = true;   // Scale small/padded icons up to the grid size, no frame.
};

enum class PowerAction { Lock, SignOut, Sleep, Hibernate, Restart, ShutDown };

struct PowerButton {
    PCWSTR key;     // Under powerButtons. in the settings.
    PCWSTR label;
    PCWSTR verb;    // "Click again to <verb>".
    WCHAR glyph;    // Segoe Fluent Icons.
    bool danger;    // Armed in red rather than blue.
};

constexpr PowerButton kPower[] = {
    {L"lock", L"Lock", L"lock", 0xE72E, false},
    {L"signOut", L"Sign out", L"sign out", 0xF3B1, true},
    {L"sleep", L"Sleep", L"sleep", 0xE708, false},
    {L"hibernate", L"Hibernate", L"hibernate", 0xE823, false},
    {L"restart", L"Restart", L"restart", 0xE72C, true},
    {L"shutDown", L"Shut down", L"shut down", 0xE7E8, true},
};

Settings g_settings;

// The mod's own switch plus the Windows "Animation effects" setting.
bool Animate() {
    BOOL enabled = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &enabled, 0);
    return g_settings.animations && enabled;
}
// Also read in the ShowStartView hook, on Explorer's threads.
std::atomic<KeyAction> g_winKeyAction{KeyAction::Grid};
std::atomic<KeyAction> g_shiftWinKeyAction{KeyAction::Start};
std::atomic<KeyAction> g_startButtonAction{KeyAction::Grid};

std::wstring GetStringSetting(PCWSTR name) {
    return WindhawkUtils::StringSetting::make(name).get();
}

// Wh_GetIntSetting returns 0 for a key the registry does not have yet, which
// silently turns features off on a script-installed mod until the first
// settings save. Fall back to the schema default while the key is missing.
int IntSetting(PCWSTR name, int def) {
    std::wstring value = GetStringSetting(name);
    return value.empty() ? def : _wtoi(value.c_str());
}

D2D1_COLOR_F ParseColor(std::wstring text, D2D1_COLOR_F fallback) {
    text.erase(std::remove_if(text.begin(), text.end(), iswspace), text.end());
    if (!text.empty() && text[0] == L'#') {
        text.erase(0, 1);
    }
    if (text.size() != 6 ||
        !std::all_of(text.begin(), text.end(), iswxdigit)) {
        return fallback;
    }
    UINT rgb = wcstoul(text.c_str(), nullptr, 16);
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.0f,
                        ((rgb >> 8) & 0xFF) / 255.0f, (rgb & 0xFF) / 255.0f);
}

void LoadSettings() {
    Settings s;
    std::wstring mode = GetStringSetting(L"blurMode");
    s.blurMode = mode == L"acrylic" ? BlurMode::Acrylic
                 : mode == L"blur"  ? BlurMode::Blur
                 : mode == L"none"  ? BlurMode::None
                                    : BlurMode::Custom;
    s.blurAmount = std::clamp(Wh_GetIntSetting(L"blurAmount"), 0, 100);
    s.opacity =
        std::clamp(Wh_GetIntSetting(L"backgroundOpacity"), 0, 100) / 100.0f;
    s.tint = ParseColor(GetStringSetting(L"tintColor"), s.tint);
    s.iconSize = std::clamp(Wh_GetIntSetting(L"gridIconSize"), 24, 192);
    s.columns = std::clamp(Wh_GetIntSetting(L"gridColumns"), 0, 30);
    s.pages = GetStringSetting(L"gridLayout") == L"pages";
    s.coverScreen = Wh_GetIntSetting(L"coverScreen") != 0;
    std::wstring source = GetStringSetting(L"appSource");
    s.source = source == L"desktop"  ? AppSource::Desktop
               : source == L"both"   ? AppSource::Both
               : source == L"pinned" ? AppSource::Pinned
                                     : AppSource::AllApps;
    s.monitor = std::max(0, _wtoi(GetStringSetting(L"monitor").c_str()));
    s.program = GetStringSetting(L"program");
    s.powerBar = Wh_GetIntSetting(L"powerBar") != 0;
    for (int i = 0; i < 6; i++) {
        s.powerShown[i] =
            Wh_GetIntSetting(L"powerButtons.%s", kPower[i].key) != 0;
    }
    s.powerNoConfirm = Wh_GetIntSetting(L"powerNoConfirm") != 0;
    s.accent = ParseColor(GetStringSetting(L"accentColor"),
                          D2D1::ColorF(0x89B4FA));
    s.glowStrength =
        std::clamp(IntSetting(L"glowStrength", 60), 0, 100) / 100.0f;
    s.glowSize = std::clamp(IntSetting(L"glowSize", 14), 4, 40);
    s.chromeOpacity =
        std::clamp(IntSetting(L"chromeOpacity", 90), 0, 100) / 100.0f;
    std::wstring dock = ToLower(GetStringSetting(L"dockAlignment"));
    s.dockAlign = dock == L"left"    ? DockAlign::Left
                  : dock == L"right" ? DockAlign::Right
                                     : DockAlign::Center;
    s.wiggle = IntSetting(L"wiggle", 1) != 0;
    s.animations = IntSetting(L"animations", 1) != 0;
    s.holdMs = std::clamp(IntSetting(L"holdTime", 420), 150, 1500);
    s.showLabels = IntSetting(L"showLabels", 1) != 0;
    s.normalizeIcons = IntSetting(L"normalizeIcons", 1) != 0;
    s.trayIcon = IntSetting(L"settingsTrayIcon", 1) != 0;
    g_settings = s;
    auto action = [](PCWSTR name) {
        std::wstring value = GetStringSetting(name);
        return value == L"start"     ? KeyAction::Start
               : value == L"program" ? KeyAction::Program
                                     : KeyAction::Grid;
    };
    g_winKeyAction = action(L"winKeyAction");
    g_shiftWinKeyAction = action(L"shiftWinKeyAction");
    g_startButtonAction = action(L"startButtonAction");
}

// Runs the "program" setting: a command line, or else anything ShellExecute
// opens (a shortcut, file, folder or web address).
void RunProgram() {
    std::wstring command = g_settings.program;
    command.erase(0, command.find_first_not_of(L" \t"));
    command.erase(command.find_last_not_of(L" \t") + 1);
    if (command.empty()) {
        return;
    }
    STARTUPINFOW si{sizeof(si)};
    PROCESS_INFORMATION pi{};
    std::wstring line = command;
    if (CreateProcessW(nullptr, line.data(), nullptr, nullptr, FALSE, 0,
                       nullptr, nullptr, &si, &pi)) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return;
    }
    if (command.size() > 1 && command.front() == L'"' &&
        command.back() == L'"') {
        command = command.substr(1, command.size() - 2);
    }
    ShellExecuteW(nullptr, nullptr, command.c_str(), nullptr, nullptr,
                  SW_SHOWNORMAL);
}

////////////////////////////////////////////////////////////////////////////////
// App list
//
// Comes from the virtual folder "shell:AppsFolder" (the "All apps" list of
// Start), the desktop, or Start's pins, depending on the setting. It's read on
// a separate thread, with the icons, and handed ready to the window.

struct App {
    std::wstring name;
    std::wstring target;  // shell:AppsFolder\... or a path, opened with ShellExecute.
    bool desktop = false;  // Came from the desktop.
    std::vector<UINT32> pixels;  // Square icon, premultiplied BGRA.
    int iconSize = 0;
    ComPtr<ID2D1Bitmap> bitmap;
    UINT generation = 0;
};
using AppList = std::vector<std::shared_ptr<App>>;

// The globals that hold COM objects (D2D bitmaps, factories, text formats) are
// released by the Start thread before it ends (no_destroy): when Explorer
// exits, Wh_ModUninit isn't called, the thread is already gone, and static
// destructors would release them on the exiting thread under the loader lock.
[[clang::no_destroy]] AppList g_apps;
bool g_appsLoaded;
double g_appsTime;
int g_appsKey;  // AppsKey() of the loaded list.

HANDLE g_worker;
std::atomic<bool> g_workerStop;
std::atomic<HWND> g_wnd;

// Bounds of the pixels whose alpha is over a threshold, optionally inside a
// clip box.
struct IconBox {
    int left = 0, top = 0, right = -1, bottom = -1;
    bool empty() const { return right < left || bottom < top; }
    int width() const { return right - left + 1; }
    int height() const { return bottom - top + 1; }
};

static IconBox ContentBounds(const std::vector<UINT32>& pixels, int width,
                             int height, UINT32 threshold,
                             const IconBox& clip) {
    IconBox b;
    b.left = clip.right + 1;
    b.top = clip.bottom + 1;
    for (int y = std::max(0, clip.top); y <= std::min(height - 1, clip.bottom);
         y++) {
        for (int x = std::max(0, clip.left);
             x <= std::min(width - 1, clip.right); x++) {
            if ((pixels[(size_t)y * width + x] >> 24) > threshold) {
                b.left = std::min(b.left, x);
                b.right = std::max(b.right, x);
                b.top = std::min(b.top, y);
                b.bottom = std::max(b.bottom, y);
            }
        }
    }
    return b;
}

// Some icons arrive as a small image centred on a large canvas, often inside
// a thin frame the shell drew: a near-opaque ring of one colour along the
// edge over a faint fill. Strips such a ring, but only when what is left
// inside is really smaller, so full-bleed icons keep their edges.
static void StripIconFrame(const std::vector<UINT32>& pixels, int width,
                           int height, IconBox& box) {
    // A side is a frame line when nearly all of it is opaque in one colour.
    auto frameLine = [&](bool vertical, int pos, int from, int to) {
        int dense = 0, total = 0;
        UINT minR = 255, maxR = 0, minG = 255, maxG = 0, minB = 255, maxB = 0;
        for (int i = from; i <= to; i++) {
            UINT32 p = vertical ? pixels[(size_t)i * width + pos]
                                : pixels[(size_t)pos * width + i];
            total++;
            if ((p >> 24) <= 200) {
                continue;
            }
            dense++;
            UINT r = (p >> 16) & 0xFF, g = (p >> 8) & 0xFF, b = p & 0xFF;
            minR = std::min(minR, r);
            maxR = std::max(maxR, r);
            minG = std::min(minG, g);
            maxG = std::max(maxG, g);
            minB = std::min(minB, b);
            maxB = std::max(maxB, b);
        }
        return dense && dense * 10 >= total * 9 && maxR - minR < 40 &&
               maxG - minG < 40 && maxB - minB < 40;
    };
    int strip[4] = {};  // Left, top, right, bottom.
    for (int step = 0; step < 12; step++) {
        if (frameLine(false, box.top + strip[1], box.left + strip[0],
                      box.right - strip[2])) {
            strip[1]++;
        }
        if (frameLine(false, box.bottom - strip[3], box.left + strip[0],
                      box.right - strip[2])) {
            strip[3]++;
        }
        if (frameLine(true, box.left + strip[0], box.top + strip[1],
                      box.bottom - strip[3])) {
            strip[0]++;
        }
        if (frameLine(true, box.right - strip[2], box.top + strip[1],
                      box.bottom - strip[3])) {
            strip[2]++;
        }
    }
    if (!strip[0] && !strip[1] && !strip[2] && !strip[3]) {
        return;
    }
    IconBox rest;
    rest.left = box.left + strip[0];
    rest.top = box.top + strip[1];
    rest.right = box.right - strip[2];
    rest.bottom = box.bottom - strip[3];
    if (rest.empty()) {
        return;
    }
    IconBox dense = ContentBounds(pixels, width, height, 200, rest);
    if (dense.empty()) {
        dense = ContentBounds(pixels, width, height, 8, rest);
    }
    if (dense.empty() ||
        std::max(dense.width(), dense.height()) * 4 >=
            std::max(box.width(), box.height()) * 3) {
        return;  // The icon fills the box: the edges were its own.
    }
    box = dense;
}

// Box-average resample of a region, in premultiplied pixels.
static std::vector<UINT32> Resample(const std::vector<UINT32>& pixels,
                                    int width, int height, const IconBox& box,
                                    int outW, int outH) {
    std::vector<UINT32> out((size_t)outW * outH, 0);
    for (int oy = 0; oy < outH; oy++) {
        int sy0 = box.top + (int)((double)oy * box.height() / outH);
        int sy1 = std::max(
            sy0 + 1, box.top + (int)((double)(oy + 1) * box.height() / outH));
        for (int ox = 0; ox < outW; ox++) {
            int sx0 = box.left + (int)((double)ox * box.width() / outW);
            int sx1 = std::max(sx0 + 1, box.left +
                                            (int)((double)(ox + 1) *
                                                  box.width() / outW));
            UINT a = 0, r = 0, g = 0, b = 0, n = 0;
            for (int sy = sy0; sy < std::min(sy1, height); sy++) {
                for (int sx = sx0; sx < std::min(sx1, width); sx++) {
                    UINT p = pixels[(size_t)sy * width + sx];
                    a += p >> 24;
                    r += (p >> 16) & 0xFF;
                    g += (p >> 8) & 0xFF;
                    b += p & 0xFF;
                    n++;
                }
            }
            if (!n) {
                continue;
            }
            out[(size_t)oy * outW + ox] =
                ((a / n) << 24) | ((r / n) << 16) | ((g / n) << 8) | (b / n);
        }
    }
    return out;
}

// Centres a side*side square crop of the source into the app's pixels.
static void CenterCopy(const std::vector<UINT32>& pixels, int width,
                       int height, int cx, int cy, int side, App& app) {
    app.iconSize = side;
    app.pixels.assign((size_t)side * side, 0);
    int x0 = cx - side / 2, y0 = cy - side / 2;
    for (int y = 0; y < side; y++) {
        int sy = y0 + y;
        if (sy < 0 || sy >= height) {
            continue;
        }
        for (int x = 0; x < side; x++) {
            int sx = x0 + x;
            if (sx >= 0 && sx < width) {
                app.pixels[(size_t)y * side + x] = pixels[sy * width + sx];
            }
        }
    }
}

// Normalizes the alpha, then crops the icon to its content. The shell often
// returns a small image centred in a large canvas, sometimes inside a thin
// frame. With "Normalize icons" the content is also scaled up to the icon
// size, aspect kept, so every icon reads at the same size; without it only
// the old small-icon crop applies.
void FinishIcon(std::vector<UINT32> pixels, int width, int height, App& app) {
    if (std::none_of(pixels.begin(), pixels.end(),
                     [](UINT32 p) { return (p >> 24) != 0; })) {
        for (auto& p : pixels) {
            p |= 0xFF000000;
        }
    }
    bool premultiplied =
        std::none_of(pixels.begin(), pixels.end(), [](UINT32 p) {
            UINT a = p >> 24;
            return ((p >> 16) & 0xFF) > a || ((p >> 8) & 0xFF) > a ||
                   (p & 0xFF) > a;
        });
    if (!premultiplied) {
        for (auto& p : pixels) {
            UINT a = p >> 24;
            UINT r = ((p >> 16) & 0xFF) * a / 255;
            UINT g = ((p >> 8) & 0xFF) * a / 255;
            UINT b = (p & 0xFF) * a / 255;
            p = (a << 24) | (r << 16) | (g << 8) | b;
        }
    }

    IconBox box = ContentBounds(pixels, width, height, 8,
                                {0, 0, width - 1, height - 1});
    if (box.empty()) {
        return;
    }
    int full = std::max(width, height);
    if (!g_settings.normalizeIcons) {
        // The old crop: a small icon centred in padding, no resampling.
        int content = std::max(box.width(), box.height());
        if (content < full * 0.6f) {
            CenterCopy(pixels, width, height, (box.left + box.right + 1) / 2,
                       (box.top + box.bottom + 1) / 2,
                       std::min(full, (int)std::ceil(content * 1.08f)), app);
        } else {
            CenterCopy(pixels, width, height, width / 2, height / 2, full,
                       app);
        }
        return;
    }

    // Drop a shell-drawn frame, then find the real icon in what is left: the
    // dense pixels, ignoring the faint fill a frame canvas comes with.
    StripIconFrame(pixels, width, height, box);
    IconBox dense = ContentBounds(pixels, width, height, 200, box);
    if (dense.empty()) {
        dense = box;
    }
    int content = std::max(dense.width(), dense.height());
    if (content * 20 >= full * 17) {
        // Already near full size: centre it, no resampling, no upscaling.
        CenterCopy(pixels, width, height, (dense.left + dense.right + 1) / 2,
                   (dense.top + dense.bottom + 1) / 2, full, app);
        return;
    }
    // Resample the content up to the icon size, aspect kept, centred.
    float k = (float)full / content;
    int outW = std::max(1, (int)std::lround(dense.width() * k));
    int outH = std::max(1, (int)std::lround(dense.height() * k));
    std::vector<UINT32> scaled =
        Resample(pixels, width, height, dense, outW, outH);
    app.iconSize = full;
    app.pixels.assign((size_t)full * full, 0);
    int x0 = (full - outW) / 2, y0 = (full - outH) / 2;
    for (int y = 0; y < outH; y++) {
        for (int x = 0; x < outW; x++) {
            app.pixels[(size_t)(y0 + y) * full + x0 + x] =
                scaled[(size_t)y * outW + x];
        }
    }
}

// The default flags give the item's icon; without SIIGBF_ICONONLY a picture
// gives its own image.
void LoadAppIcon(IShellItem* item,
                 int size,
                 App& app,
                 SIIGBF flags = SIIGBF_ICONONLY | SIIGBF_BIGGERSIZEOK) {
    ComPtr<IShellItemImageFactory> factory;
    HBITMAP bitmap = nullptr;
    if (FAILED(item->QueryInterface(IID_PPV_ARGS(&factory))) ||
        FAILED(factory->GetImage(SIZE{size, size}, flags, &bitmap))) {
        return;
    }
    BITMAP bm{};
    if (GetObjectW(bitmap, sizeof(bm), &bm) && bm.bmWidth > 0) {
        int width = bm.bmWidth, height = std::abs(bm.bmHeight);
        std::vector<UINT32> pixels((size_t)width * height);
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = width;
        bi.bmiHeader.biHeight = -height;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        HDC dc = GetDC(nullptr);
        int lines = GetDIBits(dc, bitmap, 0, height, pixels.data(), &bi,
                              DIB_RGB_COLORS);
        ReleaseDC(nullptr, dc);
        if (lines) {
            FinishIcon(std::move(pixels), width, height, app);
        }
    }
    DeleteObject(bitmap);
}

// Uninstallers, documents and website links that some programs put in the
// Start menu.
bool ShouldSkip(const std::wstring& name, const std::wstring& parsing) {
    std::wstring lowerName = ToLower(name);
    std::wstring lowerTarget = ToLower(parsing);
    if (lowerName.empty() ||
        lowerTarget.find(L"\\unins0") != std::wstring::npos ||
        lowerTarget.find(L"\\uninst.exe") != std::wstring::npos ||
        lowerTarget.find(L"\\uninstall.exe") != std::wstring::npos ||
        lowerTarget.rfind(L"http://", 0) == 0 ||
        lowerTarget.rfind(L"https://", 0) == 0) {
        return true;
    }
    for (PCWSTR ext : {L".chm", L".txt", L".pdf", L".rtf", L".htm", L".html"}) {
        if (EndsWith(lowerTarget, ext)) {
            return true;
        }
    }
    return false;
}

bool NameLess(const std::wstring& a, const std::wstring& b) {
    return CompareStringEx(LOCALE_NAME_USER_DEFAULT,
                           LINGUISTIC_IGNORECASE | SORT_DIGITSASNUMBERS,
                           a.c_str(), (int)a.size(), b.c_str(), (int)b.size(),
                           nullptr, nullptr, 0) == CSTR_LESS_THAN;
}

void AddApp(IShellItem* item,
            std::wstring target,
            int iconPixels,
            AppList& list,
            bool desktop = false) {
    PWSTR name = nullptr;
    if (SUCCEEDED(item->GetDisplayName(SIGDN_NORMALDISPLAY, &name)) && *name) {
        auto app = std::make_shared<App>();
        app->name = name;
        // With file extensions shown, shortcuts are named "Brave.lnk".
        std::wstring lower = ToLower(app->name);
        if (lower.size() > 4 &&
            (EndsWith(lower, L".lnk") || EndsWith(lower, L".url"))) {
            app->name.resize(app->name.size() - 4);
        }
        app->target = std::move(target);
        app->desktop = desktop;
        LoadAppIcon(item, iconPixels, *app);
        list.push_back(std::move(app));
    }
    CoTaskMemFree(name);
}

void AddStartApps(int iconPixels, AppList& list) {
    ComPtr<IShellItem> folder;
    ComPtr<IEnumShellItems> items;
    if (FAILED(SHCreateItemFromParsingName(L"shell:AppsFolder", nullptr,
                                           IID_PPV_ARGS(&folder))) ||
        FAILED(folder->BindToHandler(nullptr, kBhidEnumItems,
                                     IID_PPV_ARGS(&items)))) {
        return;
    }
    ComPtr<IShellItem> item;
    while (!g_workerStop &&
           items->Next(1, item.ReleaseAndGetAddressOf(), nullptr) == S_OK) {
        PWSTR name = nullptr, parsing = nullptr;
        if (SUCCEEDED(item->GetDisplayName(SIGDN_NORMALDISPLAY, &name)) &&
            SUCCEEDED(item->GetDisplayName(SIGDN_PARENTRELATIVEPARSING,
                                           &parsing)) &&
            !ShouldSkip(name, parsing)) {
            AddApp(item.Get(), std::wstring(kAppsFolder) + parsing, iconPixels,
                   list);
        }
        CoTaskMemFree(name);
        CoTaskMemFree(parsing);
    }
}

// Everything on the desktop: the user's own and the one shared by all users.
void AddDesktopItems(int iconPixels, AppList& list) {
    for (const KNOWNFOLDERID* id :
         {&FOLDERID_Desktop, &FOLDERID_PublicDesktop}) {
        ComPtr<IShellItem> folder;
        ComPtr<IEnumShellItems> items;
        if (FAILED(SHGetKnownFolderItem(*id, KF_FLAG_DEFAULT, nullptr,
                                        IID_PPV_ARGS(&folder))) ||
            FAILED(folder->BindToHandler(nullptr, kBhidEnumItems,
                                         IID_PPV_ARGS(&items)))) {
            continue;
        }
        ComPtr<IShellItem> item;
        while (!g_workerStop &&
               items->Next(1, item.ReleaseAndGetAddressOf(), nullptr) == S_OK) {
            SFGAOF attributes = 0;
            PWSTR path = nullptr;
            if (SUCCEEDED(item->GetAttributes(SFGAO_HIDDEN, &attributes)) &&
                !(attributes & SFGAO_HIDDEN) &&
                SUCCEEDED(item->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING,
                                               &path))) {
                AddApp(item.Get(), path, iconPixels, list, true);
            }
            CoTaskMemFree(path);
        }
    }
}

// Reads the JSON string whose opening quote is json[i]; i ends past the
// closing quote.
std::wstring ReadJsonString(const std::wstring& json, size_t& i) {
    std::wstring out;
    for (i++; i < json.size() && json[i] != L'"'; i++) {
        if (json[i] != L'\\' || i + 1 >= json.size()) {
            out += json[i];
            continue;
        }
        WCHAR c = json[++i];
        switch (c) {
            case L'n':
                out += L'\n';
                break;
            case L't':
                out += L'\t';
                break;
            case L'r':
                out += L'\r';
                break;
            case L'b':
                out += L'\b';
                break;
            case L'f':
                out += L'\f';
                break;
            case L'u':
                if (i + 4 < json.size()) {
                    out += (WCHAR)wcstoul(json.substr(i + 1, 4).c_str(),
                                          nullptr, 16);
                    i += 4;
                }
                break;
            default:  // \" \\ \/
                out += c;
                break;
        }
    }
    i++;
    return out;
}

// Start's pins in their order, as Windows' own Export-StartLayout writes them:
// {"pinnedList":[{"desktopAppLink":"%APPDATA%\\...\\X.lnk"},
// {"packagedAppId":"Microsoft.WindowsCalculator_8wekyb3d8bbwe!App"}]}.
// The file Start keeps them in (start2.bin) is encrypted, so the export is the
// supported way to read them.
std::wstring ExportStartLayout() {
    WCHAR temp[MAX_PATH], system[MAX_PATH];
    if (!GetTempPathW(MAX_PATH, temp) ||
        !GetSystemDirectoryW(system, MAX_PATH)) {
        return {};
    }
    std::wstring path = std::wstring(temp) + L"seamless-launchpad-pins.json";
    DeleteFileW(path.c_str());
    std::wstring quoted;  // Inside '...' a quote is written twice.
    for (WCHAR c : path) {
        quoted += c;
        if (c == L'\'') {
            quoted += c;
        }
    }
    std::wstring command = L"\"" + std::wstring(system) +
                           L"\\WindowsPowerShell\\v1.0\\powershell.exe\" "
                           L"-NoProfile -NonInteractive -ExecutionPolicy Bypass "
                           L"-Command \"Export-StartLayout -Path '" +
                           quoted + L"'\"";
    STARTUPINFOW si{sizeof(si)};
    PROCESS_INFORMATION pi{};
    if (!CreateProcessW(nullptr, command.data(), nullptr, nullptr, FALSE,
                        CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
        return {};
    }
    CloseHandle(pi.hThread);
    for (int waited = 0;
         WaitForSingleObject(pi.hProcess, 100) == WAIT_TIMEOUT; waited++) {
        if (g_workerStop || waited > 300) {
            TerminateProcess(pi.hProcess, 1);
            break;
        }
    }
    CloseHandle(pi.hProcess);

    std::string bytes;
    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
                              nullptr, OPEN_EXISTING, 0, nullptr);
    if (file != INVALID_HANDLE_VALUE) {
        DWORD size = GetFileSize(file, nullptr), read = 0;
        if (size != INVALID_FILE_SIZE && size < (16 << 20)) {
            bytes.resize(size);
            if (!ReadFile(file, bytes.data(), size, &read, nullptr)) {
                read = 0;
            }
            bytes.resize(read);
        }
        CloseHandle(file);
        DeleteFileW(path.c_str());
    }
    int length = MultiByteToWideChar(CP_UTF8, 0, bytes.data(),
                                     (int)bytes.size(), nullptr, 0);
    std::wstring json(length, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, bytes.data(), (int)bytes.size(),
                        json.data(), length);
    return json;
}

// False when the pins couldn't be read at all.
bool AddStartPins(int iconPixels, AppList& list) {
    std::wstring json = ExportStartLayout();
    if (json.find(L"\"pinnedList\"") == std::wstring::npos) {
        return false;
    }
    for (size_t i = json.find(L'"'); i != std::wstring::npos && !g_workerStop;
         i = json.find(L'"', i)) {
        std::wstring key = ReadJsonString(json, i);
        size_t value = json.find_first_not_of(L" \t\r\n", i);
        if (value == std::wstring::npos || json[value] != L':') {
            continue;
        }
        value = json.find_first_not_of(L" \t\r\n", value + 1);
        if (value != std::wstring::npos && json[value] == L'{' &&
            key == L"secondaryTile") {
            // A pinned website. Its packagedAppId is the browser, which would
            // show up as a plain browser tile, so the whole object is skipped.
            int depth = 0;
            for (i = value; i < json.size();) {
                if (json[i] == L'"') {
                    ReadJsonString(json, i);
                    continue;
                }
                if (json[i] == L'{') {
                    depth++;
                } else if (json[i] == L'}' && --depth == 0) {
                    i++;
                    break;
                }
                i++;
            }
            continue;
        }
        if (value == std::wstring::npos || json[value] != L'"') {
            continue;
        }
        i = value;
        std::wstring pin = ReadJsonString(json, i);
        std::wstring target;
        if (key == L"desktopAppLink") {
            WCHAR expanded[MAX_PATH * 2];
            DWORD n = ExpandEnvironmentStringsW(pin.c_str(), expanded,
                                                ARRAYSIZE(expanded));
            target = n && n <= ARRAYSIZE(expanded) ? expanded : pin;
        } else if (key == L"desktopAppId" || key == L"packagedAppId") {
            target = std::wstring(kAppsFolder) + pin;
        } else {
            continue;
        }
        ComPtr<IShellItem> item;
        if (SUCCEEDED(SHCreateItemFromParsingName(target.c_str(), nullptr,
                                                  IID_PPV_ARGS(&item)))) {
            AddApp(item.Get(), target, iconPixels, list);
        }
    }
    return true;
}

std::wstring StoragePath(const std::wstring& file);
void WriteLines(const std::wstring& path,
                const std::vector<std::wstring>& lines);

// The first time "only the apps you pin" is used, the pins start as Start's
// own, matched by name to the apps already read. Written even when Start's
// pins can't be read, so the slow export runs once.
void SeedPins(int iconPixels, AppList& list) {
    std::wstring path = StoragePath(L"pins.txt");
    if (path.empty() ||
        GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES) {
        return;
    }
    AppList pins;
    AddStartPins(iconPixels, pins);
    std::vector<std::wstring> lines;
    for (auto& pin : pins) {
        auto same = std::find_if(list.begin(), list.end(), [&](const auto& a) {
            return ToLower(a->name) == ToLower(pin->name);
        });
        lines.push_back(L"pin\t" +
                        (same != list.end() ? (*same)->target : pin->target));
        if (same == list.end()) {
            list.push_back(std::move(pin));
        }
    }
    if (!g_workerStop) {
        WriteLines(path, lines);
    }
}

AppList* EnumerateApps(int iconPixels, AppSource source) {
    auto list = std::make_unique<AppList>();
    // Pinned: every app is read, so the search finds the ones not pinned.
    if (source != AppSource::Desktop) {
        AddStartApps(iconPixels, *list);
    }
    if (source != AppSource::AllApps) {
        AddDesktopItems(iconPixels, *list);
    }
    if (source == AppSource::Pinned) {
        SeedPins(iconPixels, *list);
    }

    std::stable_sort(list->begin(), list->end(),
                     [](const auto& a, const auto& b) {
                         return NameLess(a->name, b->name);
                     });
    // The same app may show up twice (user and all-users shortcut). A desktop
    // shortcut named like a Start app is dropped too: the stable sort keeps
    // the Start app, added first.
    list->erase(std::unique(list->begin(), list->end(),
                            [](const auto& a, const auto& b) {
                                return a->name == b->name &&
                                       (a->desktop != b->desktop ||
                                        ToLower(a->target) ==
                                            ToLower(b->target));
                            }),
                list->end());
    return list.release();
}

// What a loaded list depends on: the icon size and the source.
// Bumped when the icon pipeline changes, so a stale list with old-style
// framed icons can't be reused within a session.
constexpr int kIconPipelineVersion = 3;

int AppsKey(int iconPixels, AppSource source) {
    return iconPixels | ((int)source << 16) | (kIconPipelineVersion << 24);
}

DWORD WINAPI LoadAppsThread(void* param) {
    int key = (int)(INT_PTR)param;
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    AppList* list =
        EnumerateApps(key & 0xFFFF, (AppSource)((key >> 16) & 0xFF));
    CoUninitialize();
    HWND wnd = g_wnd;
    if (g_workerStop || !wnd ||
        !PostMessageW(wnd, WM_APP_APPS, key, (LPARAM)list)) {
        delete list;
    }
    return 0;
}

// Icons are read at the size of the monitor with the largest scaling.
int IconPixels() {
    UINT maxDpi = 96;
    EnumDisplayMonitors(
        nullptr, nullptr,
        [](HMONITOR monitor, HDC, LPRECT, LPARAM param) -> BOOL {
            UINT dpiX = 96, dpiY = 96;
            if (SUCCEEDED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX,
                                           &dpiY))) {
                *(UINT*)param = std::max(*(UINT*)param, dpiX);
            }
            return TRUE;
        },
        (LPARAM)&maxDpi);
    return std::min(256, (int)std::ceil(g_settings.iconSize * maxDpi / 96.0));
}

int AppsKey() {
    return AppsKey(IconPixels(), g_settings.source);
}

void StartLoadingApps() {
    if (g_worker) {
        if (WaitForSingleObject(g_worker, 0) == WAIT_TIMEOUT) {
            return;  // Already reading.
        }
        CloseHandle(g_worker);
        g_worker = nullptr;
    }
    g_appsTime = Now();
    g_worker = CreateThread(nullptr, 0, LoadAppsThread,
                            (void*)(INT_PTR)AppsKey(), 0, nullptr);
}

////////////////////////////////////////////////////////////////////////////////
// Arrangement
//
// The order of the grid, its folders and the apps removed from it, saved as
// text in the mod's storage folder: one file per "Apps to show" choice, and
// one for the replaced icons. Apps are known by their target, and apps that
// aren't in the file yet go at the end.

struct Folder;

// One icon of the grid: an app or a folder.
struct Tile {
    std::shared_ptr<App> app;
    std::shared_ptr<Folder> folder;
};
using Tiles = std::vector<Tile>;

struct Folder {
    std::wstring name;
    Tiles apps;
};

[[clang::no_destroy]] Tiles g_tiles;
[[clang::no_destroy]] std::set<std::wstring> g_hidden;  // Removed apps' keys.
[[clang::no_destroy]] std::map<std::wstring, std::wstring> g_customIcons;  // Key: picture.
// Keys of the pinned apps, kept in pins.txt. Only with "only the apps you pin".
[[clang::no_destroy]] std::set<std::wstring> g_pins;

bool PinnedOnly() {
    return ((g_appsKey >> 16) & 0xFF) == (int)AppSource::Pinned;
}

// Not on the grid: removed, or not pinned when only pinned apps show.
bool OffGrid(const std::wstring& key) {
    return g_hidden.count(key) || (PinnedOnly() && !g_pins.count(key));
}

std::wstring AppKey(const App& app) {
    return ToLower(app.target);
}

// This mod was called Fullscreen Start Plus before 2.0. When its own storage
// folder has no files yet, copy the old mod's order, folders, pins and icons.
// Runs once, at the start of the grid's thread.
void MigrateOldStorage() {
    WCHAR buffer[MAX_PATH];
    if (!Wh_GetModStoragePath(buffer, ARRAYSIZE(buffer))) {
        return;
    }
    std::wstring dir = buffer;
    SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
    WIN32_FIND_DATAW data;
    HANDLE find = FindFirstFileW((dir + L"\\*.txt").c_str(), &data);
    if (find != INVALID_HANDLE_VALUE) {
        FindClose(find);
        return;
    }
    std::wstring parent = dir.substr(0, dir.find_last_of(L'\\'));
    for (PCWSTR old : {L"local@fullscreen-start-plus", L"fullscreen-start-plus"}) {
        std::wstring from = parent + L"\\" + old;
        find = FindFirstFileW((from + L"\\*.txt").c_str(), &data);
        if (find == INVALID_HANDLE_VALUE) {
            continue;
        }
        int copied = 0;
        do {
            if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                CopyFileW((from + L"\\" + data.cFileName).c_str(),
                          (dir + L"\\" + data.cFileName).c_str(), TRUE)) {
                copied++;
            }
        } while (FindNextFileW(find, &data));
        FindClose(find);
        Wh_Log(L"Copied %d files from %s", copied, from.c_str());
        return;
    }
}

std::wstring StoragePath(const std::wstring& file) {
    WCHAR dir[MAX_PATH];
    if (!Wh_GetModStoragePath(dir, ARRAYSIZE(dir))) {
        return {};
    }
    SHCreateDirectoryExW(nullptr, dir, nullptr);
    return std::wstring(dir) + L"\\" + file;
}

std::wstring LayoutFile() {
    static constexpr PCWSTR names[] = {L"allApps", L"desktop", L"both",
                                       L"pinned"};
    return std::wstring(L"layout-") + names[std::clamp((g_appsKey >> 16) & 0xFF, 0, 3)] +
           L".txt";
}

// Tab-separated fields of each line of a UTF-8 file.
std::vector<std::vector<std::wstring>> ReadLines(const std::wstring& path) {
    std::vector<std::vector<std::wstring>> lines;
    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
                              nullptr, OPEN_EXISTING, 0, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return lines;
    }
    std::string bytes;
    DWORD size = GetFileSize(file, nullptr), read = 0;
    if (size != INVALID_FILE_SIZE && size < (8 << 20)) {
        bytes.resize(size);
        if (!ReadFile(file, bytes.data(), size, &read, nullptr)) {
            read = 0;
        }
        bytes.resize(read);
    }
    CloseHandle(file);
    int length = MultiByteToWideChar(CP_UTF8, 0, bytes.data(),
                                     (int)bytes.size(), nullptr, 0);
    std::wstring text(length, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, bytes.data(), (int)bytes.size(),
                        text.data(), length);
    std::vector<std::wstring> fields(1);
    for (WCHAR c : text + L"\n") {
        if (c == L'\n') {
            if (fields.size() > 1 || !fields[0].empty()) {
                lines.push_back(std::move(fields));
            }
            fields.assign(1, {});
        } else if (c == L'\t') {
            fields.emplace_back();
        } else if (c != L'\r') {
            fields.back() += c;
        }
    }
    return lines;
}

// Written whole to a temporary file first, so a crash can't leave half a file.
void WriteLines(const std::wstring& path,
                const std::vector<std::wstring>& lines) {
    if (path.empty()) {
        return;
    }
    std::wstring text;
    for (const auto& line : lines) {
        text += line + L"\r\n";
    }
    int length = WideCharToMultiByte(CP_UTF8, 0, text.data(), (int)text.size(),
                                     nullptr, 0, nullptr, nullptr);
    std::string bytes(length, '\0');
    WideCharToMultiByte(CP_UTF8, 0, text.data(), (int)text.size(),
                        bytes.data(), length, nullptr, nullptr);
    std::wstring temp = path + L".tmp";
    HANDLE file = CreateFileW(temp.c_str(), GENERIC_WRITE, 0, nullptr,
                              CREATE_ALWAYS, 0, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        Wh_Log(L"Can't write %s: %u", temp.c_str(), GetLastError());
        return;
    }
    DWORD written = 0;
    bool ok = WriteFile(file, bytes.data(), (DWORD)bytes.size(), &written,
                        nullptr) &&
              written == bytes.size();
    CloseHandle(file);
    if (!ok || !MoveFileExW(temp.c_str(), path.c_str(),
                            MOVEFILE_REPLACE_EXISTING)) {
        Wh_Log(L"Can't save %s: %u", path.c_str(), GetLastError());
        DeleteFileW(temp.c_str());
    }
}

// The arrangement as the lines of its file:
// hidden<TAB>target, app<TAB>target, folder<TAB>name, in<TAB>target (an app
// of the folder above).
std::vector<std::wstring> ArrangementLines() {
    std::vector<std::wstring> lines;
    for (const auto& key : g_hidden) {
        lines.push_back(L"hidden\t" + key);
    }
    for (const auto& tile : g_tiles) {
        if (tile.app) {
            lines.push_back(L"app\t" + tile.app->target);
            continue;
        }
        lines.push_back(L"folder\t" + (tile.folder->name.empty()
                                            ? std::wstring(L"Folder")
                                            : tile.folder->name));
        for (const auto& app : tile.folder->apps) {
            lines.push_back(L"in\t" + app.app->target);
        }
    }
    return lines;
}

// Empty folders go, and a folder with one app becomes that app.
void TidyTiles() {
    Tiles tidy;
    for (auto& tile : g_tiles) {
        if (tile.folder && tile.folder->apps.size() < 2) {
            if (!tile.folder->apps.empty()) {
                tidy.push_back(tile.folder->apps[0]);
            }
        } else {
            tidy.push_back(std::move(tile));
        }
    }
    g_tiles.swap(tidy);
}

void ArrangeTiles(const std::vector<std::wstring>& lines) {
    std::vector<std::vector<std::wstring>> parsed;
    for (const auto& line : lines) {
        std::vector<std::wstring> fields(1);
        for (WCHAR c : line) {
            if (c == L'\t') {
                fields.emplace_back();
            } else {
                fields.back() += c;
            }
        }
        parsed.push_back(std::move(fields));
    }
    g_hidden.clear();
    for (const auto& f : parsed) {
        if (f.size() >= 2 && f[0] == L"hidden") {
            g_hidden.insert(ToLower(f[1]));
        }
    }
    std::map<std::wstring, std::shared_ptr<App>> byKey;
    for (const auto& app : g_apps) {
        byKey.emplace(AppKey(*app), app);
    }
    std::set<std::wstring> placed;
    auto take = [&](const std::wstring& target) -> std::shared_ptr<App> {
        std::wstring key = ToLower(target);
        auto it = byKey.find(key);
        if (it == byKey.end() || OffGrid(key) || !placed.insert(key).second) {
            return nullptr;
        }
        return it->second;
    };
    g_tiles.clear();
    std::shared_ptr<Folder> folder;
    for (const auto& f : parsed) {
        if (f.size() < 2) {
            continue;
        }
        if (f[0] == L"folder") {
            folder = std::make_shared<Folder>();
            folder->name = f[1];
            g_tiles.push_back({nullptr, folder});
        } else if (f[0] == L"in" && folder) {
            if (auto app = take(f[1])) {
                folder->apps.push_back({std::move(app), nullptr});
            }
        } else if (f[0] == L"app") {
            folder = nullptr;
            if (auto app = take(f[1])) {
                g_tiles.push_back({std::move(app), nullptr});
            }
        }
    }
    for (const auto& app : g_apps) {
        if (auto taken = take(app->target)) {
            g_tiles.push_back({std::move(taken), nullptr});
        }
    }
    TidyTiles();
}

void SaveTiles() {
    WriteLines(StoragePath(LayoutFile()), ArrangementLines());
}

// A picture (or the icon of a file) in place of an app's icon.
bool LoadIconFile(const std::wstring& path, int size, App& app) {
    ComPtr<IShellItem> item;
    if (FAILED(SHCreateItemFromParsingName(path.c_str(), nullptr,
                                           IID_PPV_ARGS(&item)))) {
        return false;
    }
    App loaded;
    LoadAppIcon(item.Get(), size, loaded, SIIGBF_BIGGERSIZEOK);
    if (loaded.pixels.empty()) {
        return false;
    }
    app.pixels = std::move(loaded.pixels);
    app.iconSize = loaded.iconSize;
    app.bitmap.Reset();
    app.generation = 0;  // Remade on the next draw.
    return true;
}

// The app's own icon again.
void ReloadAppIcon(int size, App& app) {
    ComPtr<IShellItem> item;
    if (SUCCEEDED(SHCreateItemFromParsingName(app.target.c_str(), nullptr,
                                              IID_PPV_ARGS(&item)))) {
        App loaded;
        LoadAppIcon(item.Get(), size, loaded);
        app.pixels = std::move(loaded.pixels);
        app.iconSize = loaded.iconSize;
        app.bitmap.Reset();
        app.generation = 0;
    }
}

void SaveCustomIcons() {
    std::vector<std::wstring> lines;
    for (const auto& [key, path] : g_customIcons) {
        lines.push_back(L"icon\t" + key + L"\t" + path);
    }
    WriteLines(StoragePath(L"icons.txt"), lines);
}

void ApplyCustomIcons(int size) {
    g_customIcons.clear();
    for (const auto& f : ReadLines(StoragePath(L"icons.txt"))) {
        if (f.size() >= 3 && f[0] == L"icon") {
            g_customIcons[ToLower(f[1])] = f[2];
        }
    }
    for (const auto& app : g_apps) {
        auto it = g_customIcons.find(AppKey(*app));
        if (it != g_customIcons.end()) {
            LoadIconFile(it->second, size, *app);
        }
    }
}

void SavePins() {
    std::vector<std::wstring> lines;
    for (const auto& key : g_pins) {
        lines.push_back(L"pin\t" + key);
    }
    WriteLines(StoragePath(L"pins.txt"), lines);
}

void LoadTiles() {
    g_pins.clear();
    for (const auto& f : ReadLines(StoragePath(L"pins.txt"))) {
        if (f.size() >= 2 && f[0] == L"pin") {
            g_pins.insert(ToLower(f[1]));
        }
    }
    std::vector<std::wstring> lines;
    for (const auto& f : ReadLines(StoragePath(LayoutFile()))) {
        std::wstring line;
        for (size_t i = 0; i < f.size(); i++) {
            line += (i ? L"\t" : L"") + f[i];
        }
        lines.push_back(std::move(line));
    }
    ArrangeTiles(lines);
}

////////////////////////////////////////////////////////////////////////////////
// Search

std::wstring g_query;
// The search field is a small text editor: a caret and a selection anchor as
// UTF-16 indices into g_query (the selection is the span between them), a
// tick that times the caret's blink, and the state of a drag-selection.
size_t g_caret = 0;
size_t g_anchor = 0;
UINT64 g_caretTick = 0;
bool g_searchDrag = false;
UINT64 g_lastSearchClick = 0;
int g_lastSearchX = -1000;
// The arrangement, or the apps the search finds.
[[clang::no_destroy]] Tiles g_visible;

// 0: the name starts with the text; 1: a word of the name starts with it;
// 2: it's in the middle; -1: it isn't there. Ignoring case and accents.
int MatchRank(const std::wstring& name, const std::wstring& word) {
    int pos = FindNLSStringEx(
        LOCALE_NAME_USER_DEFAULT,
        FIND_FROMSTART | LINGUISTIC_IGNORECASE | LINGUISTIC_IGNOREDIACRITIC,
        name.c_str(), (int)name.size(), word.c_str(), (int)word.size(),
        nullptr, nullptr, nullptr, 0);
    if (pos < 0) {
        return -1;
    }
    if (pos == 0) {
        return 0;
    }
    return iswalnum(name[pos - 1]) ? 2 : 1;
}

void UpdateFilter() {
    if (g_query.empty()) {
        g_visible = g_tiles;
        return;
    }
    std::vector<std::wstring> words;
    size_t start = 0;
    while (start < g_query.size()) {
        size_t end = g_query.find(L' ', start);
        if (end == std::wstring::npos) {
            end = g_query.size();
        }
        if (end > start) {
            words.push_back(g_query.substr(start, end - start));
        }
        start = end + 1;
    }

    std::vector<std::pair<int, int>> ranked;  // (position, index)
    for (int i = 0; i < (int)g_apps.size(); i++) {
        if (g_hidden.count(AppKey(*g_apps[i]))) {
            continue;
        }
        int rank = 0;
        for (size_t w = 0; w < words.size() && rank >= 0; w++) {
            int r = MatchRank(g_apps[i]->name, words[w]);
            rank = r < 0 ? -1 : (w == 0 ? r : rank);
        }
        if (rank >= 0) {
            // With only pinned apps, the pinned ones come first.
            bool off = PinnedOnly() && !g_pins.count(AppKey(*g_apps[i]));
            ranked.emplace_back(rank + (off ? 3 : 0), i);
        }
    }
    std::stable_sort(ranked.begin(), ranked.end(),
                     [](const auto& a, const auto& b) {
                         return a.first < b.first;
                     });
    g_visible.clear();
    for (const auto& r : ranked) {
        g_visible.push_back({g_apps[r.second], nullptr});
    }
}

////////////////////////////////////////////////////////////////////////////////
// Available area
//
// The monitor's work area already excludes the visible taskbar and the side
// bars that reserve space. The Standalone Dock usually doesn't reserve it (it
// hides by itself), so its strip is removed separately.

RECT AvailableArea(HMONITOR monitor) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(monitor, &mi);
    if (g_settings.coverScreen) {
        return mi.rcMonitor;
    }
    struct Search {
        HMONITOR monitor;
        RECT monitorRect;
        RECT area;
    } search{monitor, mi.rcMonitor, mi.rcWork};

    EnumWindows(
        [](HWND hwnd, LPARAM param) -> BOOL {
            auto* s = (Search*)param;
            WCHAR className[64];
            if (!GetClassNameW(hwnd, className, ARRAYSIZE(className)) ||
                wcscmp(className, kDockClass) ||
                MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL) != s->monitor) {
                return TRUE;
            }
            int edge = (int)(INT_PTR)GetPropW(hwnd, kDockEdgeProp);
            int reserved = (int)(INT_PTR)GetPropW(hwnd, kDockReservedProp);
            const RECT& m = s->monitorRect;
            RECT& a = s->area;
            switch (edge) {
                case 1:
                    a.bottom = std::min<LONG>(a.bottom, m.bottom - reserved);
                    break;
                case 2:
                    a.left = std::max<LONG>(a.left, m.left + reserved);
                    break;
                case 3:
                    a.right = std::min<LONG>(a.right, m.right - reserved);
                    break;
            }
            return TRUE;
        },
        (LPARAM)&search);

    // A giant Dock can't reduce the area to zero.
    RECT& a = search.area;
    if (a.right - a.left < 200 || a.bottom - a.top < 200) {
        a = mi.rcWork;
    }
    return a;
}

// Monitor 1 is the main one, the rest follow from left to right (then top to
// bottom). A number with no monitor behind it falls back to the mouse.
HMONITOR ChosenMonitor() {
    POINT pt;
    GetCursorPos(&pt);
    HMONITOR mouse = MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);
    if (g_settings.monitor <= 0) {
        return mouse;
    }
    struct Entry {
        bool primary;
        RECT rc;
        HMONITOR monitor;
    };
    std::vector<Entry> monitors;
    EnumDisplayMonitors(
        nullptr, nullptr,
        [](HMONITOR monitor, HDC, LPRECT, LPARAM param) -> BOOL {
            MONITORINFO mi{sizeof(mi)};
            GetMonitorInfoW(monitor, &mi);
            ((std::vector<Entry>*)param)
                ->push_back({(mi.dwFlags & MONITORINFOF_PRIMARY) != 0,
                             mi.rcMonitor, monitor});
            return TRUE;
        },
        (LPARAM)&monitors);
    std::stable_sort(monitors.begin(), monitors.end(),
                     [](const Entry& a, const Entry& b) {
                         if (a.primary != b.primary) {
                             return a.primary;
                         }
                         if (a.rc.left != b.rc.left) {
                             return a.rc.left < b.rc.left;
                         }
                         return a.rc.top < b.rc.top;
                     });
    if (g_settings.monitor > (int)monitors.size()) {
        return mouse;
    }
    return monitors[g_settings.monitor - 1].monitor;
}

// Puts the Dock windows above Start, which leaves the Dock's strip free.
// The background ones first: the Dock window is owned by one of them and stays above.
void RaiseDockWindows() {
    // Collects before moving: raising a window changes the order FindWindowEx
    // walks, and with two Docks it kept alternating between them endlessly.
    std::vector<HWND> windows;
    for (PCWSTR className : {kDockPlateClass, kDockClass}) {
        HWND hwnd = nullptr;
        while ((hwnd = FindWindowExW(nullptr, hwnd, className, nullptr))) {
            if (IsWindowVisible(hwnd)) {
                windows.push_back(hwnd);
            }
        }
    }
    // Without waiting for the Dock thread: the request goes to its queue.
    for (HWND hwnd : windows) {
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Drawing

[[clang::no_destroy]] ComPtr<ID2D1Factory> g_d2d;
[[clang::no_destroy]] ComPtr<IDWriteFactory> g_dwrite;
[[clang::no_destroy]] ComPtr<ID3D11Device> g_d3d;
[[clang::no_destroy]] ComPtr<ID2D1Device> g_d2dDevice;
[[clang::no_destroy]] ComPtr<ID2D1DeviceContext> g_target;
[[clang::no_destroy]] ComPtr<ID2D1SolidColorBrush> g_brush;
[[clang::no_destroy]] ComPtr<ID2D1Bitmap1> g_frame;  // The GPU frame.
[[clang::no_destroy]] ComPtr<ID3D11Texture2D> g_staging;
int g_frameWidth = 0, g_frameHeight = 0;
UINT g_targetGeneration = 1;

struct Surface {
    HDC dc = nullptr;
    HBITMAP bitmap = nullptr;
    HGDIOBJ old = nullptr;
    int width = 0, height = 0;
};
Surface g_surface;

void FreeSurface(Surface& s) {
    if (s.dc) {
        SelectObject(s.dc, s.old);
        DeleteObject(s.bitmap);
        DeleteDC(s.dc);
    }
    s = {};
}

bool EnsureSurface(Surface& s, int width, int height) {
    if (s.dc && s.width == width && s.height == height) {
        return true;
    }
    FreeSurface(s);
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = width;
    bi.bmiHeader.biHeight = -height;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    s.dc = CreateCompatibleDC(nullptr);
    s.bitmap = CreateDIBSection(s.dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!s.bitmap) {
        DeleteDC(s.dc);
        s = {};
        return false;
    }
    s.old = SelectObject(s.dc, s.bitmap);
    s.width = width;
    s.height = height;
    return true;
}

void ResetTarget();

[[clang::no_destroy]] ComPtr<ID2D1LinearGradientBrush> g_hoverGradient;

bool EnsureTarget() {
    if (g_target) {
        return true;
    }
    // A real GPU context: the grid rasterizes on the GPU and each frame is
    // copied back into the layered-window DIB. WARP is the fallback.
    for (D3D_DRIVER_TYPE type :
         {D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP}) {
        if (SUCCEEDED(D3D11CreateDevice(
                nullptr, type, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                nullptr, 0, D3D11_SDK_VERSION, &g_d3d, nullptr, nullptr))) {
            break;
        }
        g_d3d.Reset();
    }
    if (!g_d3d) {
        return false;
    }
    ComPtr<IDXGIDevice> dxgi;
    ComPtr<ID2D1Factory1> factory1;
    if (FAILED(g_d3d.As(&dxgi)) || FAILED(g_d2d.As(&factory1)) ||
        FAILED(factory1->CreateDevice(dxgi.Get(), &g_d2dDevice)) ||
        FAILED(g_d2dDevice->CreateDeviceContext(
            D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &g_target))) {
        ResetTarget();
        return false;
    }
    g_target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    g_target->CreateSolidColorBrush(D2D1::ColorF(0, 0), &g_brush);
    g_targetGeneration++;
    return true;
}

void ResetTarget() {
    g_frame.Reset();
    g_staging.Reset();
    g_frameWidth = g_frameHeight = 0;
    g_hoverGradient.Reset();
    g_brush.Reset();
    g_target.Reset();
    g_d2dDevice.Reset();
    g_d3d.Reset();
}

// The GPU frame target and the staging texture it is copied back through.
// Recreated whenever the window size changes.
bool EnsureFrame(int width, int height) {
    if (g_frame && g_frameWidth == width && g_frameHeight == height) {
        return true;
    }
    g_frame.Reset();
    g_staging.Reset();
    D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                          D2D1_ALPHA_MODE_PREMULTIPLIED),
        96, 96);
    if (FAILED(g_target->CreateBitmap(D2D1::SizeU(width, height), nullptr, 0,
                                      props, &g_frame))) {
        return false;
    }
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    ComPtr<ID3D11DeviceContext> ctx;
    g_d3d->GetImmediateContext(&ctx);
    if (FAILED(g_d3d->CreateTexture2D(&desc, nullptr, &g_staging))) {
        g_frame.Reset();
        return false;
    }
    g_frameWidth = width;
    g_frameHeight = height;
    return true;
}

// Copies the rendered frame from the GPU into the layered-window DIB.
void PresentFrame() {
    if (!g_frame || !g_staging || !g_surface.bitmap) {
        return;
    }
    DIBSECTION ds{};
    if (GetObjectW(g_surface.bitmap, sizeof(ds), &ds) != sizeof(ds) ||
        !ds.dsBm.bmBits) {
        return;
    }
    ComPtr<IDXGISurface> surface;
    ComPtr<ID3D11Texture2D> texture;
    if (FAILED(g_frame->GetSurface(&surface)) ||
        FAILED(surface.As(&texture))) {
        return;
    }
    ComPtr<ID3D11DeviceContext> ctx;
    g_d3d->GetImmediateContext(&ctx);
    ctx->CopyResource(g_staging.Get(), texture.Get());
    D3D11_MAPPED_SUBRESOURCE mapped{};
    if (FAILED(ctx->Map(g_staging.Get(), 0, D3D11_MAP_READ, 0, &mapped))) {
        return;
    }
    int width = ds.dsBm.bmWidth, height = ds.dsBm.bmHeight;
    size_t span = (size_t)width * 4;
    const BYTE* src = (const BYTE*)mapped.pData;
    BYTE* dst = (BYTE*)ds.dsBm.bmBits;
    for (int y = 0; y < height; y++) {
        memcpy(dst + (size_t)y * span, src + (size_t)y * mapped.RowPitch,
               span);
    }
    ctx->Unmap(g_staging.Get(), 0);
}

ID2D1Bitmap* GetBitmap(App& app) {
    if (app.pixels.empty()) {
        return nullptr;
    }
    if (app.generation != g_targetGeneration) {
        app.generation = g_targetGeneration;
        app.bitmap.Reset();
        g_target->CreateBitmap(
            D2D1::SizeU(app.iconSize, app.iconSize), app.pixels.data(),
            app.iconSize * 4,
            D2D1::BitmapProperties(
                D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                                  D2D1_ALPHA_MODE_PREMULTIPLIED),
                96, 96),
            &app.bitmap);
    }
    return app.bitmap.Get();
}

D2D1_COLOR_F Alpha(D2D1_COLOR_F c, float a) {
    c.a = a;
    return c;
}

void Fill(const D2D1_RECT_F& r, D2D1_COLOR_F color, float radius = 0) {
    g_brush->SetColor(color);
    if (radius > 0) {
        g_target->FillRoundedRectangle(D2D1::RoundedRect(r, radius, radius),
                                       g_brush.Get());
    } else {
        g_target->FillRectangle(r, g_brush.Get());
    }
}

////////////////////////////////////////////////////////////////////////////////
// Background
//
// Adjustable: a screenshot taken before the window appears, uploaded once and
// then scaled down and blurred on the GPU as an effect graph. Downscaling
// first makes a strong blur cheap.

struct Backdrop {
    ComPtr<ID2D1Bitmap> bitmap;
    int width = 0, height = 0;  // Blurred size.
    float sourceWidth = 0, sourceHeight = 0;  // Part used, in blurred pixels.
};
[[clang::no_destroy]] Backdrop g_backdropImage;

// Scales source down by f and gaussian-blurs it by sigma / f into a new sw x
// sh GPU bitmap. rect is the part of source used; the rest is cropped.
ComPtr<ID2D1Bitmap1> BlurToBitmap(ID2D1Bitmap* source,
                                  const D2D1_RECT_F& rect, int f, float sigma,
                                  int sw, int sh) {
    D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                          D2D1_ALPHA_MODE_PREMULTIPLIED),
        96, 96);
    ComPtr<ID2D1Bitmap1> target, small;
    ComPtr<ID2D1Effect> blur;
    if (FAILED(g_target->CreateBitmap(D2D1::SizeU(sw, sh), nullptr, 0, props,
                                      &small)) ||
        FAILED(g_target->CreateBitmap(D2D1::SizeU(sw, sh), nullptr, 0, props,
                                      &target)) ||
        FAILED(g_target->CreateEffect(CLSID_D2D1GaussianBlur, &blur))) {
        return nullptr;
    }
    // Pass 1: the part of source in rect, scaled down by f.
    g_target->BeginDraw();
    g_target->SetTarget(small.Get());
    g_target->Clear(D2D1::ColorF(0, 0));
    g_target->DrawBitmap(source, D2D1::RectF(0, 0, (float)sw, (float)sh), 1.0f,
                         D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect);
    if (FAILED(g_target->EndDraw())) {
        return nullptr;
    }
    // Pass 2: a gaussian blur of what pass 1 drew.
    blur->SetInput(0, small.Get());
    blur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, sigma / f);
    blur->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
    g_target->BeginDraw();
    g_target->SetTarget(target.Get());
    g_target->Clear(D2D1::ColorF(0, 0));
    g_target->DrawImage(blur.Get(), nullptr, nullptr,
                        D2D1_INTERPOLATION_MODE_LINEAR);
    if (FAILED(g_target->EndDraw())) {
        return nullptr;
    }
    return target;
}

void CaptureBackdrop(const RECT& rc, float sigma) {
    g_backdropImage = {};
    int width = rc.right - rc.left, height = rc.bottom - rc.top;
    if (width <= 0 || height <= 0 || !EnsureTarget()) {
        return;
    }

    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = width;
    bi.bmiHeader.biHeight = -height;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    HDC dc = CreateCompatibleDC(screen);
    HBITMAP bitmap =
        CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!bitmap) {
        DeleteDC(dc);
        ReleaseDC(nullptr, screen);
        return;
    }
    HGDIOBJ old = SelectObject(dc, bitmap);
    // Without CAPTUREBLT, which makes the cursor flicker; the screen composed
    // by DWM already includes layered windows.
    BitBlt(dc, 0, 0, width, height, screen, rc.left, rc.top, SRCCOPY);
    GdiFlush();

    D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                          D2D1_ALPHA_MODE_PREMULTIPLIED),
        96, 96);
    ComPtr<ID2D1Bitmap> full;
    bool uploaded =
        SUCCEEDED(g_target->CreateBitmap(D2D1::SizeU(width, height), bits,
                                         width * 4, props, &full));
    SelectObject(dc, old);
    DeleteObject(bitmap);
    DeleteDC(dc);
    ReleaseDC(nullptr, screen);
    if (!uploaded) {
        return;
    }

    int f = sigma >= 3 ? std::clamp((int)(sigma / 3), 1, 16) : 1;
    int sw = (width + f - 1) / f, sh = (height + f - 1) / f;
    ComPtr<ID2D1Bitmap1> blurred = BlurToBitmap(
        full.Get(), D2D1::RectF(0, 0, (float)width, (float)height), f, sigma,
        sw, sh);
    if (!blurred) {
        return;
    }
    g_backdropImage.bitmap = blurred.Get();
    g_backdropImage.width = sw;
    g_backdropImage.height = sh;
    g_backdropImage.sourceWidth = (float)width / f;
    g_backdropImage.sourceHeight = (float)height / f;
}

ID2D1Bitmap* GetBackdropBitmap() {
    return g_backdropImage.bitmap.Get();
}

// The open folder's panel is frosted glass: the grid under it, blurred. The
// blur is taken from the window surface right after the grid is drawn and
// kept while nothing under the panel moves.
struct PanelBlur {
    ComPtr<ID2D1Bitmap> bitmap;
    D2D1_RECT_F rect{};  // Window pixels it was taken from.
    int x = 0, y = 0, factor = 1;
    const void* folder = nullptr;
    float scroll = 0;
    UINT generation = 0;
};
[[clang::no_destroy]] PanelBlur g_panelBlur;

void CapturePanelBlur(const D2D1_RECT_F& rect, const void* folder,
                      float scroll, float scale) {
    g_panelBlur = {};
    g_panelBlur.rect = rect;
    g_panelBlur.folder = folder;
    g_panelBlur.scroll = scroll;
    g_panelBlur.generation = g_targetGeneration;
    if (!g_frame) {
        return;
    }
    // The blur source is the frame just drawn, still on the GPU; only the
    // region under the panel is used.
    int x0 = std::clamp((int)std::floor(rect.left), 0, g_frameWidth);
    int y0 = std::clamp((int)std::floor(rect.top), 0, g_frameHeight);
    int x1 = std::clamp((int)std::ceil(rect.right), 0, g_frameWidth);
    int y1 = std::clamp((int)std::ceil(rect.bottom), 0, g_frameHeight);
    if (x1 <= x0 || y1 <= y0) {
        return;
    }
    float sigma = 24 * scale;
    int f = std::clamp((int)(sigma / 3), 1, 16);
    int sw = (x1 - x0 + f - 1) / f, sh = (y1 - y0 + f - 1) / f;
    ComPtr<ID2D1Bitmap1> blurred =
        BlurToBitmap(g_frame.Get(),
                     D2D1::RectF((float)x0, (float)y0, (float)x1, (float)y1),
                     f, sigma, sw, sh);
    if (!blurred) {
        return;
    }
    g_panelBlur.bitmap = blurred.Get();
    g_panelBlur.x = x0;
    g_panelBlur.y = y0;
    g_panelBlur.factor = f;
}

bool PanelBlurFresh(const D2D1_RECT_F& rect, const void* folder,
                    float scroll) {
    const PanelBlur& b = g_panelBlur;
    return b.folder == folder && b.generation == g_targetGeneration &&
           b.scroll == scroll && std::abs(b.rect.left - rect.left) < 0.5f &&
           std::abs(b.rect.top - rect.top) < 0.5f &&
           std::abs(b.rect.right - rect.right) < 0.5f &&
           std::abs(b.rect.bottom - rect.bottom) < 0.5f;
}

// Paints the kept blur into rect (window pixels, identity transform).
void DrawPanelBlur(const D2D1_RECT_F& rect, float radius) {
    const PanelBlur& b = g_panelBlur;
    if (!b.bitmap) {
        return;
    }
    ComPtr<ID2D1BitmapBrush> brush;
    g_target->CreateBitmapBrush(
        b.bitmap.Get(),
        D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_CLAMP,
                                    D2D1_EXTEND_MODE_CLAMP,
                                    D2D1_BITMAP_INTERPOLATION_MODE_LINEAR),
        &brush);
    if (!brush) {
        return;
    }
    brush->SetTransform(D2D1::Matrix3x2F::Scale((float)b.factor,
                                                (float)b.factor) *
                        D2D1::Matrix3x2F::Translation((float)b.x, (float)b.y));
    g_target->FillRoundedRectangle(D2D1::RoundedRect(rect, radius, radius),
                                   brush.Get());
}

// Acrylic and Windows blur: a regular window with the DWM effect sits right
// below the layered window where everything is drawn, like in the Dock.

struct AccentPolicy {
    INT accentState;
    INT accentFlags;
    INT gradientColor;
    INT animationId;
};

struct WindowCompositionAttribData {
    DWORD attrib;
    PVOID data;
    SIZE_T size;
};

constexpr DWORD WCA_ACCENT_POLICY = 19;
constexpr INT ACCENT_DISABLED = 0;
constexpr INT ACCENT_ENABLE_BLURBEHIND = 3;
constexpr INT ACCENT_ENABLE_ACRYLICBLURBEHIND = 4;
constexpr DWORD kDwmUseImmersiveDarkMode = 20;
constexpr DWORD kDwmWindowCornerPreference = 33;
constexpr DWORD kDwmBorderColor = 34;

HWND g_backdrop;

void SetAccent(HWND hwnd, INT state, DWORD abgr) {
    using SetWindowCompositionAttribute_t =
        BOOL(WINAPI*)(HWND, WindowCompositionAttribData*);
    static auto setWindowCompositionAttribute =
        (SetWindowCompositionAttribute_t)GetProcAddress(
            GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (!setWindowCompositionAttribute) {
        return;
    }
    AccentPolicy policy{state, state ? 2 : 0, (INT)abgr, 0};
    WindowCompositionAttribData data{WCA_ACCENT_POLICY, &policy,
                                     sizeof(policy)};
    setWindowCompositionAttribute(hwnd, &data);
}

void ApplyBackdropEffect() {
    // Makes DWM respect the window's alpha channel, without blur.
    DWM_BLURBEHIND blur{};
    blur.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    blur.fEnable = TRUE;
    blur.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
    DwmEnableBlurBehindWindow(g_backdrop, &blur);
    DeleteObject(blur.hRgnBlur);

    BOOL dark = TRUE;
    DwmSetWindowAttribute(g_backdrop, kDwmUseImmersiveDarkMode, &dark,
                          sizeof(dark));
    UINT corner = 1;  // DWMWCP_DONOTROUND
    DwmSetWindowAttribute(g_backdrop, kDwmWindowCornerPreference, &corner,
                          sizeof(corner));
    COLORREF border = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
    DwmSetWindowAttribute(g_backdrop, kDwmBorderColor, &border,
                          sizeof(border));

    // The color is drawn on the top window, with the chosen opacity; acrylic
    // only requires a nonzero alpha.
    D2D1_COLOR_F c = g_settings.tint;
    DWORD abgr = (1u << 24) | ((DWORD)(c.b * 255) << 16) |
                 ((DWORD)(c.g * 255) << 8) | (DWORD)(c.r * 255);
    switch (g_settings.blurMode) {
        case BlurMode::Acrylic:
            SetAccent(g_backdrop, ACCENT_ENABLE_ACRYLICBLURBEHIND, abgr);
            break;
        case BlurMode::Blur:
            SetAccent(g_backdrop, ACCENT_ENABLE_BLURBEHIND, 0);
            break;
        default:
            SetAccent(g_backdrop, ACCENT_DISABLED, 0);
            break;
    }
}

bool UsesDwmBackdrop() {
    return g_settings.blurMode == BlurMode::Acrylic ||
           g_settings.blurMode == BlurMode::Blur;
}

////////////////////////////////////////////////////////////////////////////////
// Layout

struct Layout {
    RECT area{};  // Window position on screen.
    int width = 0, height = 0;
    float scale = 1;
    float icon = 72, labelHeight = 20, cellWidth = 140, cellHeight = 140;
    float cellSpare = 0;  // Extra row height that fills the screen with pages.
    float cellPad = 6;
    int columns = 1;
    float gridLeft = 0;
    float viewTop = 0, viewBottom = 0;  // Visible range, in whole rows.
    int visibleRows = 1;
    float contentHeight = 0;
    int perPage = 1, pages = 1;  // With the pages layout.
    float dotsY = 0;             // Center of the page dots.
    D2D1_RECT_F search{};
    D2D1_RECT_F menuButton{};  // The "..." button, inside the search bar's
                               // right inner edge.
    D2D1_RECT_F clearButton{};  // Clear (x), left of "...", while typing.
    D2D1_RECT_F powerBar{};    // The power dock pill, aligned by dockAlignment.
    std::vector<int> powerItems;  // kPower indices shown, left to right.
    float powerButton = 36, powerGap = 6;
};

Layout g_layout;
// Set from GetPwrCapabilities each time the grid opens.
bool g_canSleep = true, g_canHibernate = false;
// Pixels: down the list, or, with pages, across the row of pages.
float g_scroll, g_scrollTarget;
int g_wheelDelta;  // Wheel accumulated until it completes a row (touchpads).

[[clang::no_destroy]] ComPtr<IDWriteTextFormat> g_labelFormat, g_searchFormat,
    g_messageFormat, g_iconFormat, g_tipFormat;
float g_formatScale;

void EnsureFormats(float scale) {
    if (g_labelFormat && g_formatScale == scale) {
        return;
    }
    g_formatScale = scale;
    auto make = [&](float size, DWRITE_FONT_WEIGHT weight,
                    DWRITE_TEXT_ALIGNMENT align,
                    ComPtr<IDWriteTextFormat>& format,
                    PCWSTR family = L"Segoe UI Variable Text") {
        format.Reset();
        g_dwrite->CreateTextFormat(family, nullptr, weight,
                                   DWRITE_FONT_STYLE_NORMAL,
                                   DWRITE_FONT_STRETCH_NORMAL, size * scale,
                                   L"", &format);
        if (!format) {
            return;
        }
        format->SetTextAlignment(align);
        format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        DWRITE_TRIMMING trimming{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        ComPtr<IDWriteInlineObject> ellipsis;
        g_dwrite->CreateEllipsisTrimmingSign(format.Get(), &ellipsis);
        format->SetTrimming(&trimming, ellipsis.Get());
    };
    make(12.5f, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER,
         g_labelFormat);
    make(15, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING,
         g_searchFormat);
    make(16, DWRITE_FONT_WEIGHT_SEMI_LIGHT, DWRITE_TEXT_ALIGNMENT_CENTER,
         g_messageFormat);
    make(12.5f, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER,
         g_tipFormat);
    // Windows 11 has Segoe Fluent Icons; Windows 10 only the older MDL2 font,
    // which has the same code points for these glyphs.
    ComPtr<IDWriteFontCollection> fonts;
    UINT32 index;
    BOOL fluent = FALSE;
    if (SUCCEEDED(g_dwrite->GetSystemFontCollection(&fonts))) {
        fonts->FindFamilyName(L"Segoe Fluent Icons", &index, &fluent);
    }
    make(15, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER,
         g_iconFormat, fluent ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets");
}

float MaxScroll() {
    if (g_settings.pages) {
        return (g_layout.pages - 1) * (float)g_layout.width;
    }
    return std::max(0.0f, g_layout.contentHeight -
                              (g_layout.viewBottom - g_layout.viewTop));
}

void ComputeLayout() {
    Layout& L = g_layout;
    float s = L.scale;
    float W = (float)L.width, H = (float)L.height;

    float searchWidth = std::min(320 * s, W - 40 * s);
    float searchTop = std::round(std::max(28 * s, H * 0.045f));
    L.search = D2D1::RectF(std::round((W - searchWidth) / 2), searchTop,
                           std::round((W + searchWidth) / 2),
                           searchTop + std::round(36 * s));

    L.icon = std::round(g_settings.iconSize * s);
    L.labelHeight = std::round(20 * s);
    L.cellPad = std::round(6 * s);
    L.cellHeight = std::round(L.icon + L.labelHeight + 46 * s);
    L.viewTop = L.search.bottom + std::round(28 * s);
    // The "..." button sits at the bar's right inner edge, half the bar's
    // height, like StartPad's; the clear (x) button goes left of it.
    float button = std::round(18 * s);
    float ccx = L.search.right - std::round(21.6f * s);
    float cy = (L.search.top + L.search.bottom) / 2;
    L.menuButton = D2D1::RectF(ccx - button / 2, cy - button / 2,
                               ccx + button / 2, cy + button / 2);
    L.clearButton = D2D1::RectF(L.menuButton.left - 2 * s - button,
                                cy - button / 2, L.menuButton.left - 2 * s,
                                cy + button / 2);

    float side = std::max(48 * s, W * 0.07f);
    float available = std::max(L.icon * 2, W - 2 * side);
    float minCell = std::max(L.icon * 1.8f, L.icon + 64 * s);
    L.columns = g_settings.columns > 0
                    ? g_settings.columns
                    : std::clamp((int)(available / minCell), 2, 14);
    // With few columns on a wide screen, the icons don't spread out too much.
    L.cellWidth = std::floor(
        std::min(available / L.columns, std::max(minCell, L.icon * 2.6f)));
    L.gridLeft = std::round((W - L.cellWidth * L.columns) / 2);

    // Only whole rows are visible; scrolling moves row by row. Pages keep
    // room below for the dots.
    float bottomRoom = std::round((g_settings.pages ? 44 : 16) * s);

    // The power bar: a pill of round buttons, centered at the bottom, with
    // the grid (and the page dots) above it.
    L.powerItems.clear();
    if (g_settings.powerBar) {
        for (int i = 0; i < (int)ARRAYSIZE(kPower); i++) {
            auto action = (PowerAction)i;
            if (g_settings.powerShown[i] &&
                (action != PowerAction::Sleep || g_canSleep) &&
                (action != PowerAction::Hibernate || g_canHibernate)) {
                L.powerItems.push_back(i);
            }
        }
    }
    L.powerBar = {};
    if (!L.powerItems.empty()) {
        L.powerButton = std::round(36 * s);
        L.powerGap = std::round(6 * s);
        float pad = std::round(5 * s);
        int n = (int)L.powerItems.size();
        float barWidth = n * L.powerButton + (n - 1) * L.powerGap + 2 * pad;
        float barHeight = L.powerButton + 2 * pad;
        float bottom = H - std::round(std::max(22 * s, H * 0.028f));
        // A DPI scaled margin in from the edge the setting picks.
        float edge = std::round(24 * s);
        float left = g_settings.dockAlign == DockAlign::Left  ? edge
                     : g_settings.dockAlign == DockAlign::Right
                         ? W - barWidth - edge
                         : std::round((W - barWidth) / 2);
        L.powerBar = D2D1::RectF(left, bottom - barHeight, left + barWidth,
                                 bottom);
        bottomRoom = H - L.powerBar.top +
                     std::round((g_settings.pages ? 30 : 10) * s);
    }

    L.visibleRows =
        std::max(1, (int)((H - bottomRoom - L.viewTop) / L.cellHeight));
    L.cellSpare = 0;
    if (g_settings.pages) {
        // Pages don't scroll, so the rows spread out to the dots instead of
        // leaving the part of a row that doesn't fit empty at the bottom.
        float rowHeight =
            std::floor((H - bottomRoom - L.viewTop) / L.visibleRows);
        L.cellSpare = std::max(0.0f, rowHeight - L.cellHeight);
        L.cellHeight += L.cellSpare;
    }
    L.viewBottom = L.viewTop + L.visibleRows * L.cellHeight;
    L.dotsY = std::round(
        (L.viewBottom + (L.powerItems.empty() ? H : L.powerBar.top)) / 2);

    int count = (int)g_visible.size();
    int rows = (count + L.columns - 1) / L.columns;
    L.contentHeight = rows * L.cellHeight;
    L.perPage = L.visibleRows * L.columns;
    L.pages = std::max(1, (count + L.perPage - 1) / L.perPage);
    g_scrollTarget = std::clamp(g_scrollTarget, 0.0f, MaxScroll());
    g_scroll = std::clamp(g_scroll, 0.0f, MaxScroll());
}

struct Cell {
    D2D1_RECT_F highlight, icon, label;
};

// The cell whose top left corner is x, y.
Cell MakeCell(float x, float y) {
    const Layout& L = g_layout;
    Cell c;
    c.highlight = D2D1::RectF(x + L.cellPad, y, x + L.cellWidth - L.cellPad,
                              y + L.cellHeight - L.cellSpare - L.cellPad * 2);
    float iconLeft = std::round(x + (L.cellWidth - L.icon) / 2);
    float iconTop = std::round(y + 10 * L.scale);
    c.icon = D2D1::RectF(iconLeft, iconTop, iconLeft + L.icon, iconTop + L.icon);
    float labelTop = c.icon.bottom + std::round(8 * L.scale);
    c.label = D2D1::RectF(x + L.cellPad + 4 * L.scale, labelTop,
                          x + L.cellWidth - L.cellPad - 4 * L.scale,
                          labelTop + L.labelHeight);
    return c;
}

Cell CellAt(int index) {
    const Layout& L = g_layout;
    float x, y;
    if (g_settings.pages) {
        int page = index / L.perPage, slot = index % L.perPage;
        x = L.gridLeft + (slot % L.columns) * L.cellWidth +
            page * (float)L.width - std::round(g_scroll);
        y = L.viewTop + (slot / L.columns) * L.cellHeight;
    } else {
        int row = index / L.columns, col = index % L.columns;
        x = L.gridLeft + col * L.cellWidth;
        y = L.viewTop + row * L.cellHeight - std::round(g_scroll);
    }
    y += std::round(L.cellSpare / 2);  // Centered in a stretched row.
    return MakeCell(x, y);
}

////////////////////////////////////////////////////////////////////////////////
// Hover glow
//
// A soft halo in the accent colour behind the icon of the hovered or
// keyboard-selected tile. Blurring is expensive, so one bitmap per icon size
// and spread is built once and reused; each tile only fades its opacity,
// eased over ~150 ms. Built outside the frame's BeginDraw, in Render.

struct GlowCache {
    ComPtr<ID2D1Bitmap1> bitmap;
    int size = 0;         // Device pixels the halo bitmap covers.
    UINT generation = 0;  // g_targetGeneration it was built for.
};
[[clang::no_destroy]] GlowCache g_glow;

void StartFrames();
float Ease(float t);

ID2D1Bitmap1* EnsureGlowBitmap(int icon, float scale) {
    int spread = (int)std::round(g_settings.glowSize * scale);
    int size = icon + spread * 2;
    if (g_glow.bitmap && g_glow.size == size &&
        g_glow.generation == g_targetGeneration) {
        return g_glow.bitmap.Get();
    }
    int f = 4;  // The source renders at a quarter size; the blur smooths it.
    int small = std::max(16, size / f);
    D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                          D2D1_ALPHA_MODE_PREMULTIPLIED),
        96, 96);
    ComPtr<ID2D1Bitmap1> source;
    if (FAILED(g_target->CreateBitmap(D2D1::SizeU(small, small), nullptr, 0,
                                      props, &source))) {
        return nullptr;
    }
    g_target->BeginDraw();
    g_target->SetTarget(source.Get());
    g_target->Clear(D2D1::ColorF(0, 0));
    float margin = (float)spread / f;
    // The solid rect reaches a few pixels past the icon, so the halo is at
    // full strength right at the icon's edge instead of half.
    float overhang = 4.0f / f;
    D2D1_RECT_F rect = D2D1::RectF(margin - overhang, margin - overhang,
                                   small - margin + overhang,
                                   small - margin + overhang);
    float radius = std::max(2.0f, icon * 0.28f / f + overhang);
    g_brush->SetColor(Alpha(g_settings.accent, 1.0f));
    g_target->FillRoundedRectangle(D2D1::RoundedRect(rect, radius, radius),
                                   g_brush.Get());
    if (FAILED(g_target->EndDraw())) {
        return nullptr;
    }
    // The sigma is in small-bitmap pixels; drawn back up it blurs like
    // 0.35 * spread device pixels would - tight enough to stay bright at the
    // icon's edge on the dark backdrop.
    g_glow.bitmap = BlurToBitmap(
        source.Get(), D2D1::RectF(0, 0, (float)small, (float)small), 1,
        0.35f * spread / f, small, small);
    g_glow.size = size;
    g_glow.generation = g_targetGeneration;
    return g_glow.bitmap ? g_glow.bitmap.Get() : nullptr;
}

struct GlowFade {
    const void* key = nullptr;  // The tile's app or folder.
    float alpha = 0;            // 0..1, eased when drawn.
    double last = 0;
};
constexpr int kGlowSlots = 4;
[[clang::no_destroy]] GlowFade g_glowFades[kGlowSlots];
bool g_glowAnimating;  // A fade is under way; OnFrame keeps rendering.

// Advances the tile's fade and returns the eased alpha to draw with.
float GlowAlpha(const void* key, bool on) {
    GlowFade* slot = nullptr;
    for (auto& s : g_glowFades) {
        if (s.key == key) {
            slot = &s;
            break;
        }
    }
    if (!slot && on) {
        for (auto& s : g_glowFades) {
            if (!s.key) {
                slot = &s;
                break;
            }
        }
        if (!slot) {
            for (auto& s : g_glowFades) {
                if (!slot || s.alpha < slot->alpha) {
                    slot = &s;
                }
            }
        }
        slot->key = key;
        slot->alpha = 0;
        slot->last = Now();
    }
    if (!slot) {
        return 0;
    }
    double now = Now();
    float dt = (float)std::clamp(now - slot->last, 0.0, 0.1);
    if (!Animate()) {
        dt = 1.0f;
    }
    slot->last = now;
    slot->alpha = std::clamp(slot->alpha + (on ? dt : -dt) / 0.15f, 0.0f, 1.0f);
    if (slot->alpha > 0 && slot->alpha < 1) {
        g_glowAnimating = true;
        StartFrames();
    } else if (!on) {
        slot->key = nullptr;  // Faded out: freed for the next tile.
    }
    return Ease(slot->alpha);
}

bool InRect(const D2D1_RECT_F& r, float x, float y) {
    return x >= r.left && x < r.right && y >= r.top && y < r.bottom;
}

// Position in the grid under the point (window coordinates), counting the
// places past the last icon, or -1 outside the rows.
int GridIndexAt(int px, int py) {
    const Layout& L = g_layout;
    float x = (float)px, y = (float)py;
    int page = 0;
    if (g_settings.pages) {
        x += std::round(g_scroll);
        page = (int)std::floor(x / L.width);
        x -= page * (float)L.width;
    }
    if (y < L.viewTop || y >= L.viewBottom || x < L.gridLeft ||
        x >= L.gridLeft + L.cellWidth * L.columns || page < 0) {
        return -1;
    }
    int col = (int)((x - L.gridLeft) / L.cellWidth);
    int row = (int)((y - L.viewTop +
                     (g_settings.pages ? 0 : std::round(g_scroll))) /
                    L.cellHeight);
    return row < 0 ? -1 : page * L.perPage + row * L.columns + col;
}

// An open folder: a panel over the grid with its name and its apps.
[[clang::no_destroy]] std::shared_ptr<Folder> g_openFolder;
bool g_folderRenaming = false;
bool g_folderTitleHover = false;
// The folder fading out after a close, and the open/close progress (0 to 1).
[[clang::no_destroy]] std::shared_ptr<Folder> g_closingFolder;
float g_folderAnim = 1;
int g_folderRow;  // First row shown, when not all of them fit.

struct FolderLayout {
    D2D1_RECT_F panel, title;
    float left, top, cellHeight;  // Of the icons.
    int columns, rows, visibleRows;
};

FolderLayout GetFolderLayout() {
    const Layout& L = g_layout;
    float s = L.scale;
    FolderLayout F{};
    int count = g_openFolder ? (int)g_openFolder->apps.size() : 0;
    F.columns = std::min(L.columns, std::max(3, std::min(count, 6)));
    F.rows = std::max(1, (count + F.columns - 1) / F.columns);
    F.cellHeight = L.cellHeight - L.cellSpare;
    float pad = std::round(20 * s), titleHeight = std::round(56 * s);
    int fit = std::max(1, (int)((L.viewBottom - L.viewTop - titleHeight - pad) /
                                F.cellHeight));
    F.visibleRows = std::min(F.rows, fit);
    float width = F.columns * L.cellWidth + 2 * pad;
    float height = titleHeight + F.visibleRows * F.cellHeight + pad;
    float left = std::round((L.width - width) / 2);
    float top = std::round(
        std::max(L.viewTop, (L.viewTop + L.viewBottom - height) / 2));
    F.panel = D2D1::RectF(left, top, left + width, top + height);
    F.title = D2D1::RectF(left + pad, top + pad / 2, left + width - pad,
                          top + titleHeight);
    F.left = left + pad;
    F.top = top + titleHeight;
    return F;
}

Cell FolderCellAt(int index) {
    FolderLayout F = GetFolderLayout();
    return MakeCell(F.left + (index % F.columns) * g_layout.cellWidth,
                    F.top + (index / F.columns - g_folderRow) * F.cellHeight);
}

int FolderIndexAt(int px, int py) {
    FolderLayout F = GetFolderLayout();
    float x = px - F.left, y = py - F.top;
    if (x < 0 || x >= F.columns * g_layout.cellWidth || y < 0 ||
        y >= F.visibleRows * F.cellHeight) {
        return -1;
    }
    return ((int)(y / F.cellHeight) + g_folderRow) * F.columns +
           (int)(x / g_layout.cellWidth);
}

// What takes the pointer and the keys: the open folder, or the grid.
const Tiles& Items() {
    return g_openFolder ? g_openFolder->apps : g_visible;
}

int Columns() {
    return g_openFolder ? GetFolderLayout().columns : g_layout.columns;
}

Cell ItemCell(int index) {
    return g_openFolder ? FolderCellAt(index) : CellAt(index);
}

// Position in Items() of the icon under the point, or -1.
int ItemAt(int x, int y) {
    int index = g_openFolder ? FolderIndexAt(x, y) : GridIndexAt(x, y);
    if (index < 0 || index >= (int)Items().size() ||
        !InRect(ItemCell(index).highlight, (float)x, (float)y)) {
        return -1;
    }
    return index;
}

// While dragging: the place under the point (the last one when past the
// end), or -1.
int SlotAt(int x, int y) {
    int index = g_openFolder ? FolderIndexAt(x, y) : GridIndexAt(x, y);
    return index < 0 ? -1 : std::min(index, (int)Items().size() - 1);
}

// The page dot under the point, or -1. The click area is larger than the dot.
int PageDotAt(int px, int py) {
    const Layout& L = g_layout;
    if (!g_settings.pages || L.pages < 2) {
        return -1;
    }
    float step = 20 * L.scale;
    float left = L.width / 2.0f - L.pages * step / 2;
    float x = (float)px, y = (float)py;
    if (std::abs(y - L.dotsY) > 14 * L.scale || x < left ||
        x >= left + L.pages * step) {
        return -1;
    }
    return (int)((x - left) / step);
}

////////////////////////////////////////////////////////////////////////////////
// Screen state and drawing

bool g_shown;        // The windows are on screen (opening, open or closing).
bool g_closing;
float g_appear;      // 0 closed, 1 open.
float g_wiggle;      // Edit mode envelope: ramps to 1 while an icon is held.
double g_lastFrame;
double g_lastClosed;  // When it closed by losing focus.
bool g_frameTimer;
int g_hover = -1, g_selected = -1, g_pressed = -1;
bool g_pressedEmpty;
bool g_trackingMouse;
bool g_menuHover;
bool g_searchHover;   // The pointer rests on the search bar.
bool g_clearHover;    // ... on the clear (x) button.
float g_searchGlow;   // 0..1, the bar's eased accent glow.
float g_btnGlow;      // 0..1, the "..." button's eased hover fill.

// Dragging an icon: it keeps a place in the grid or folder, drawn empty, and
// moves to the place the pointer rests on.
struct Drag {
    bool pending = false;  // Pressed on an icon; a drag once it moves.
    bool active = false;
    POINT start{}, at{};
    double pressTime = 0;  // When the press started, for the hold time.
    D2D1_POINT_2F grab{};  // Pointer minus the icon's corner.
    Tile tile;
    int target = -1;  // The icon to drop it into (makes or fills a folder).
    int slot = -1;    // The place under the pointer.
    int edge = 0;     // -1 or 1 while resting at an edge: flips or scrolls.
    bool inPanel = false;  // Has been inside the open folder.
    double targetTime = 0, slotTime = 0, edgeTime = 0;
    std::vector<std::wstring> backup;  // The arrangement before, for Esc.
};
[[clang::no_destroy]] Drag g_drag;
bool g_modal;  // A dialog of the grid is open: losing the focus is expected.

void EndDrag(bool drop);
void StartDrag();
void DragTick();

constexpr float kTwoPi = 6.2831853f;

float Ease(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return 1 - (1 - t) * (1 - t) * (1 - t);
}

// A button's hit area runs a little past what is drawn.
bool InButton(const D2D1_RECT_F& r, float x, float y) {
    float pad = 6 * g_layout.scale;
    return InRect(D2D1::RectF(r.left - pad, r.top - pad, r.right + pad,
                              r.bottom + pad),
                  x, y);
}

// Mocha blue to mauve across a rect, at an opacity. Falls back to the solid accent.
ID2D1Brush* HoverBrush(const D2D1_RECT_F& r, float opacity) {
    if (!g_hoverGradient) {
        D2D1_GRADIENT_STOP stops[] = {
            {0, D2D1::ColorF(0x89B4FA)}, {1, D2D1::ColorF(0xCBA6F7)}};
        ComPtr<ID2D1GradientStopCollection> collection;
        if (SUCCEEDED(g_target->CreateGradientStopCollection(stops, 2, &collection))) {
            g_target->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(
                    D2D1::Point2F(r.left, r.top), D2D1::Point2F(r.right, r.top)),
                collection.Get(), &g_hoverGradient);
        }
    }
    if (!g_hoverGradient) {
        g_brush->SetColor(Alpha(g_settings.accent, opacity));
        return g_brush.Get();
    }
    g_hoverGradient->SetStartPoint(D2D1::Point2F(r.left, r.top));
    g_hoverGradient->SetEndPoint(D2D1::Point2F(r.right, r.bottom));
    g_hoverGradient->SetOpacity(opacity);
    return g_hoverGradient.Get();
}

// The clean hover box shared by tiles, search, menu and power buttons: a thin
// halo of 1px strokes fading outward, a faint face and a crisp edge, all in
// the blue to mauve gradient.
void DrawHoverBox(const D2D1_RECT_F& box, float radius, float alpha,
                  float maxSpread = 1e6f) {
    if (alpha <= 0.001f) {
        return;
    }
    float s = g_layout.scale;
    int spread = std::max(1, (int)std::min(g_settings.glowSize * s, maxSpread * s));
    for (int j = spread; j > 0; --j) {
        float d = (float)j;
        float falloff = 1.0f - d / (spread + 1.0f);
        auto halo = D2D1::RectF(box.left - d, box.top - d, box.right + d, box.bottom + d);
        g_target->DrawRoundedRectangle(
            D2D1::RoundedRect(halo, radius + d, radius + d),
            HoverBrush(halo, alpha * g_settings.glowStrength * 0.055f * falloff * falloff), s);
    }
    g_target->FillRoundedRectangle(D2D1::RoundedRect(box, radius, radius),
                                   HoverBrush(box, alpha * 0.12f));
    // 1.6 px: a 1 px edge looked jagged on the rounded corners.
    float w = 1.6f * s, in = w / 2;
    auto edge = D2D1::RectF(box.left + in, box.top + in, box.right - in, box.bottom - in);
    g_target->DrawRoundedRectangle(D2D1::RoundedRect(edge, radius - in, radius - in),
                                   HoverBrush(box, alpha * 0.85f), w);
}

// A soft accent glow out of a rounded rect: wide overlapping strokes with
// falling alpha blend into a smooth fade, cheap on the GPU (no blur).
void DrawGlow(const D2D1_RECT_F& r, float radius, float spread, float alpha,
              int layers) {
    float step = spread / layers;
    float width = std::max(1.0f, g_layout.scale) + step * 2.2f;
    for (int i = layers; i >= 1; i--) {
        float t = ((float)i - 0.5f) / layers;
        float off = spread * t;
        g_brush->SetColor(Alpha(g_settings.accent, alpha * (1 - t) * 0.35f));
        g_target->DrawRoundedRectangle(
            D2D1::RoundedRect(
                D2D1::RectF(r.left - off, r.top - off, r.right + off,
                            r.bottom + off),
                radius + off, radius + off),
            g_brush.Get(), width);
    }
}

void DrawMenuButton() {
    const D2D1_RECT_F& r = g_layout.menuButton;
    float s = g_layout.scale;
    float radius = (r.bottom - r.top) / 2;
    DrawHoverBox(r, radius, g_btnGlow, 6);
    float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    g_brush->SetColor(D2D1::ColorF(0xCDD6F4, 0.75f + 0.2f * g_btnGlow));
    for (int i = -1; i <= 1; i++) {
        g_target->FillEllipse(
            D2D1::Ellipse(D2D1::Point2F(cx + i * 4.5f * s, cy), 1.5f * s,
                          1.5f * s),
            g_brush.Get());
    }
}

void DrawClearButton() {
    if (g_openFolder || g_query.empty()) {
        return;
    }
    const D2D1_RECT_F& r = g_layout.clearButton;
    float s = g_layout.scale;
    float radius = (r.bottom - r.top) / 2;
    if (g_clearHover) {
        Fill(r, D2D1::ColorF(0x45475A, 0.55f), radius);
    }
    float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    float arm = 4 * s;
    g_brush->SetColor(D2D1::ColorF(0x7F849C, g_clearHover ? 0.95f : 0.8f));
    g_target->DrawLine(D2D1::Point2F(cx - arm, cy - arm),
                       D2D1::Point2F(cx + arm, cy + arm), g_brush.Get(),
                       1.4f * s);
    g_target->DrawLine(D2D1::Point2F(cx - arm, cy + arm),
                       D2D1::Point2F(cx + arm, cy - arm), g_brush.Get(),
                       1.4f * s);
}

////////////////////////////////////////////////////////////////////////////////
// Power dock: a solid Mocha pill of round buttons at the bottom, aligned by
// the dock position setting. Without "Skip confirmation", the first click
// arms a button (colored, "Click again to ...") and a second click on it
// runs the action.

int g_powerHover = -1;    // Slot in g_layout.powerItems.
int g_powerPressed = -1;
int g_powerArmed = -1;
// Eased glows, one per button (by kPower index) and one for the dock border.
float g_powerGlow[6];
float g_powerDockGlow;

void HideNow();
void StartFrames();

void RefreshPowerCaps() {
    SYSTEM_POWER_CAPABILITIES caps{};
    if (GetPwrCapabilities(&caps)) {
        // MinGW's header calls AoAc (modern standby) spare2[2]; the Windows
        // SDK names the three bytes Hiberboot, WakeAlarmPresent and AoAc.
        g_canSleep = caps.SystemS1 || caps.SystemS2 || caps.SystemS3 ||
                     caps.spare2[2];
        g_canHibernate = caps.SystemS4 && caps.HiberFilePresent;
    }
}

D2D1_RECT_F PowerButtonRect(int slot) {
    const Layout& L = g_layout;
    float pad = (L.powerBar.bottom - L.powerBar.top - L.powerButton) / 2;
    float left = L.powerBar.left + pad + slot * (L.powerButton + L.powerGap);
    float top = L.powerBar.top + pad;
    return D2D1::RectF(left, top, left + L.powerButton, top + L.powerButton);
}

// The slot under the point, counting the gaps so the bar has no dead spots.
int PowerAt(int x, int y) {
    const Layout& L = g_layout;
    if (L.powerItems.empty() || !InRect(L.powerBar, (float)x, (float)y)) {
        return -1;
    }
    float pad = (L.powerBar.bottom - L.powerBar.top - L.powerButton) / 2;
    float step = L.powerButton + L.powerGap;
    int slot = (int)std::floor((x - L.powerBar.left - pad + L.powerGap / 2) /
                               step);
    return std::clamp(slot, 0, (int)L.powerItems.size() - 1);
}

void DisarmPower() {
    if (g_powerArmed >= 0) {
        g_powerArmed = -1;
        KillTimer(g_wnd, kTimerPowerArm);
        StartFrames();  // The glow eases back out.
    }
}

void EnablePrivilege(PCWSTR name) {
    HANDLE token;
    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) {
        return;
    }
    TOKEN_PRIVILEGES tp{1};
    if (LookupPrivilegeValueW(nullptr, name, &tp.Privileges[0].Luid)) {
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges(token, FALSE, &tp, 0, nullptr, nullptr);
    }
    CloseHandle(token);
}

// Shut down like Start does: a fast startup shutdown when that's on.
bool FastStartupOn() {
    DWORD value = 0, size = sizeof(value);
    return RegGetValueW(HKEY_LOCAL_MACHINE,
                        L"SYSTEM\\CurrentControlSet\\Control\\Session "
                        L"Manager\\Power",
                        L"HiberbootEnabled", RRF_RT_REG_DWORD, nullptr, &value,
                        &size) == ERROR_SUCCESS &&
           value == 1;
}

// Off the UI thread: sleep and hibernate return only after the PC wakes.
// Holds a reference to this DLL so unloading the mod meanwhile is safe.
DWORD WINAPI PowerThread(void* param) {
    auto action = (PowerAction)(INT_PTR)param;
    // Never EWX_FORCE: apps with unsaved work get to ask, as with Start.
    DWORD reason = SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER |
                   SHTDN_REASON_FLAG_PLANNED;
    BOOL ok = TRUE;
    switch (action) {
        case PowerAction::Lock:
            ok = LockWorkStation();
            break;
        case PowerAction::SignOut:
            ok = ExitWindowsEx(EWX_LOGOFF, reason);
            break;
        case PowerAction::Sleep:
        case PowerAction::Hibernate:
            EnablePrivilege(SE_SHUTDOWN_NAME);
            ok = SetSuspendState(action == PowerAction::Hibernate, FALSE,
                                 FALSE);
            if (!ok && action == PowerAction::Sleep) {
                // Modern standby PCs can't be suspended by a program;
                // turning the screen off lets them go to sleep.
                if (HWND wnd = g_wnd) {
                    PostMessageW(wnd, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
                    ok = TRUE;
                }
            }
            break;
        case PowerAction::Restart:
            EnablePrivilege(SE_SHUTDOWN_NAME);
            ok = ExitWindowsEx(EWX_REBOOT, reason);
            break;
        case PowerAction::ShutDown:
            EnablePrivilege(SE_SHUTDOWN_NAME);
            ok = ExitWindowsEx(
                EWX_POWEROFF | (FastStartupOn() ? EWX_HYBRID_SHUTDOWN : 0),
                reason);
            break;
    }
    if (!ok) {
        Wh_Log(L"Power action %s failed: %u", kPower[(int)action].key,
               GetLastError());
    }
    FreeLibraryAndExitThread((HMODULE)&__ImageBase, 0);
    return 0;  // Unreachable live: the API exits the thread. Keeps test hosts returning.
}

void RunPowerAction(PowerAction action) {
    Wh_Log(L"Power action: %s", kPower[(int)action].key);
    DisarmPower();
    HideNow();  // At once: no closing animation over a lock or sleep.
    HMODULE self;
    if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                            (PCWSTR)&PowerThread, &self)) {
        return;
    }
    HANDLE thread = CreateThread(nullptr, 0, PowerThread,
                                 (void*)(INT_PTR)action, 0, nullptr);
    if (thread) {
        CloseHandle(thread);
    } else {
        FreeLibrary(self);
    }
}

void PowerClick(int slot) {
    if (slot < 0 || slot >= (int)g_layout.powerItems.size()) {
        return;
    }
    if (!g_settings.powerNoConfirm && g_powerArmed != slot) {
        g_powerArmed = slot;
        SetTimer(g_wnd, kTimerPowerArm, 4000, nullptr);
        StartFrames();  // The armed glow fades in.
        return;
    }
    RunPowerAction((PowerAction)g_layout.powerItems[slot]);
}

void DrawPowerBar() {
    const Layout& L = g_layout;
    if (L.powerItems.empty()) {
        return;
    }
    float s = L.scale;
    const D2D1_RECT_F& bar = L.powerBar;
    float radius = (bar.bottom - bar.top) / 2;

    // The pill: Mocha crust, never thinner than 0.94 so the glyphs keep their
    // contrast over a bright wallpaper, with a Surface2 edge that lifts toward
    // the accent while the pointer is over the dock.
    Fill(bar,
         Alpha(D2D1::ColorF(0x181825),
               std::max(0.94f, g_settings.chromeOpacity)),
         radius);
    D2D1_COLOR_F edge{0x58 / 255.0f, 0x5B / 255.0f, 0x70 / 255.0f, 1};
    edge.r += (g_settings.accent.r - edge.r) * 0.25f * g_powerDockGlow;
    edge.g += (g_settings.accent.g - edge.g) * 0.25f * g_powerDockGlow;
    edge.b += (g_settings.accent.b - edge.b) * 0.25f * g_powerDockGlow;
    g_brush->SetColor(edge);
    g_target->DrawRoundedRectangle(
        D2D1::RoundedRect(D2D1::RectF(bar.left + 0.5f, bar.top + 0.5f,
                                      bar.right - 0.5f, bar.bottom - 0.5f),
                          radius - 0.5f, radius - 0.5f),
        g_brush.Get(), 1);

    DrawHoverBox(bar, radius, g_powerDockGlow, 4);

    // The glows first, so a halo may pass over its neighbours' edges.
    for (int slot = 0; slot < (int)L.powerItems.size(); slot++) {
        float glow = g_powerGlow[L.powerItems[slot]];
        if (glow <= 0.001f) {
            continue;
        }
        glow = glow * glow * (3 - 2 * glow);  // Smoothstep over the fade.
        const PowerButton& b = kPower[L.powerItems[slot]];
        // Danger stays red while armed, the rest glow in the accent.
        D2D1_COLOR_F color = slot == g_powerArmed && b.danger
                                 ? D2D1::ColorF(0xF38BA8)
                                 : g_settings.accent;
        if (slot == g_powerArmed) {
            continue;
        }
        (void)color;
        D2D1_RECT_F r = PowerButtonRect(slot);
        DrawHoverBox(r, L.powerButton / 2, glow, 4);
    }

    for (int slot = 0; slot < (int)L.powerItems.size(); slot++) {
        const PowerButton& b = kPower[L.powerItems[slot]];
        D2D1_RECT_F r = PowerButtonRect(slot);
        float half = L.powerButton / 2;
        bool hover = slot == g_powerHover && !g_openFolder;
        bool pressed = hover && slot == g_powerPressed;
        float glow = g_powerGlow[L.powerItems[slot]];
        glow = glow * glow * (3 - 2 * glow);
        D2D1_COLOR_F glyph;
        if (slot == g_powerArmed) {
            // Catppuccin red for what ends the session, accent for the rest.
            Fill(r, b.danger ? D2D1::ColorF(0xF38BA8) : g_settings.accent,
                 half);
            glyph = D2D1::ColorF(0x1E1E2E);
        } else {
            // Rest: full Mocha text. Hover: brightens to white so the glyph
            // stands out on the accent glow.
            D2D1_COLOR_F base{0xCD / 255.0f, 0xD6 / 255.0f, 0xF4 / 255.0f, 1};
            base.r += (1 - base.r) * glow;
            base.g += (1 - base.g) * glow;
            base.b += (1 - base.b) * glow;
            glyph = Alpha(base, pressed ? 0.6f : 1.0f);
        }
        if (g_iconFormat) {
            g_brush->SetColor(glyph);
            g_target->DrawText(&b.glyph, 1, g_iconFormat.Get(), r,
                               g_brush.Get());
        }
    }

    // The label of the button under the mouse, or the confirmation prompt,
    // in a small pill above the bar.
    int tipSlot = g_powerArmed >= 0 ? g_powerArmed
                  : g_openFolder    ? -1
                                    : g_powerHover;
    if (tipSlot < 0 || !g_tipFormat) {
        return;
    }
    const PowerButton& b = kPower[L.powerItems[tipSlot]];
    std::wstring text = tipSlot == g_powerArmed
                            ? std::wstring(L"Click again to ") + b.verb
                            : std::wstring(b.label);
    ComPtr<IDWriteTextLayout> layout;
    g_dwrite->CreateTextLayout(text.c_str(), (UINT32)text.size(),
                               g_tipFormat.Get(), 1000 * s, 100 * s, &layout);
    if (!layout) {
        return;
    }
    DWRITE_TEXT_METRICS m{};
    layout->GetMetrics(&m);
    D2D1_RECT_F button = PowerButtonRect(tipSlot);
    float w = std::ceil(m.width) + 24 * s, h = std::round(28 * s);
    float cx = (button.left + button.right) / 2;
    float left = std::round(std::clamp(cx - w / 2, 8 * s, L.width - w - 8 * s));
    float bottom = bar.top - std::round(8 * s);
    D2D1_RECT_F tip = D2D1::RectF(left, bottom - h, left + w, bottom);
    Fill(tip, Alpha(D2D1::ColorF(0x1E1E2E), 0.92f), h / 2);
    g_brush->SetColor(D2D1::ColorF(0x45475A));
    g_target->DrawRoundedRectangle(
        D2D1::RoundedRect(D2D1::RectF(tip.left + 0.5f, tip.top + 0.5f,
                                      tip.right - 0.5f, tip.bottom - 0.5f),
                          h / 2 - 0.5f, h / 2 - 0.5f),
        g_brush.Get(), 1);
    g_brush->SetColor(tipSlot == g_powerArmed
                          ? (b.danger ? D2D1::ColorF(0xF38BA8)
                                      : g_settings.accent)
                          : D2D1::ColorF(0xCDD6F4));
    g_target->DrawText(text.c_str(), (UINT32)text.size(), g_tipFormat.Get(),
                       tip, g_brush.Get());
}

////////////////////////////////////////////////////////////////////////////////
// The search field as a text editor: caret, selection and the usual keys.
// Positions are UTF-16 indices into g_query; a step crosses a whole surrogate
// pair so characters outside the basic plane stay whole.

void QueryChanged();
void Render();

// The field the editor works on: the search box, or a folder's name while
// its folder is open.
std::wstring& EditText() {
    return g_openFolder ? g_openFolder->name : g_query;
}

size_t MaxEditChars() {
    return g_openFolder ? 60 : 200;
}

// A rename only redraws; the search also refilters the apps.
void EditChanged() {
    if (g_openFolder) {
        Render();
    } else {
        QueryChanged();
    }
}

bool SearchSelection(size_t* from, size_t* to) {
    size_t size = EditText().size();
    *from = std::min(std::min(g_anchor, g_caret), size);
    *to = std::min(std::max(g_anchor, g_caret), size);
    return *from != *to;
}

size_t CaretStep(size_t pos, int dir) {
    const std::wstring& text = EditText();
    if (dir < 0) {
        pos = std::min(pos, text.size());
        if (pos >= 2 && IS_LOW_SURROGATE(text[pos - 1]) &&
            IS_HIGH_SURROGATE(text[pos - 2])) {
            return pos - 2;
        }
        return pos ? pos - 1 : 0;
    }
    if (pos + 1 < text.size() && IS_HIGH_SURROGATE(text[pos]) &&
        IS_LOW_SURROGATE(text[pos + 1])) {
        return pos + 2;
    }
    return std::min(pos + 1, text.size());
}

bool IsWordChar(WCHAR ch) {
    return iswalnum(ch) || ch == L'_';
}

size_t WordStart(size_t pos) {
    const std::wstring& text = EditText();
    size_t i = std::min(pos, text.size());
    while (i > 0 && !IsWordChar(text[i - 1])) {
        i--;
    }
    while (i > 0 && IsWordChar(text[i - 1])) {
        i--;
    }
    return i;
}

size_t WordEnd(size_t pos) {
    const std::wstring& text = EditText();
    size_t n = text.size(), i = std::min(pos, n);
    while (i < n && !IsWordChar(text[i])) {
        i++;
    }
    while (i < n && IsWordChar(text[i])) {
        i++;
    }
    return i;
}

void TouchCaret() {  // Restarts the blink, like after every keystroke.
    g_caretTick = GetTickCount64();
}

// Undo and redo for the field being edited. A snapshot is the whole field,
// which is small. Consecutive keystrokes of one kind merge into one step;
// pastes and cuts stay their own step. The folder's history resets each time
// a folder opens, so one folder's steps never land on another's name.
struct EditSnapshot {
    std::wstring text;
    size_t caret;
    size_t anchor;
};
struct EditHistory {
    std::vector<EditSnapshot> undo;
    std::vector<EditSnapshot> redo;
    int lastOp = 0;  // 0 paste or cut, 1 typing, 2 delete
    size_t lastEnd = 0;
    ULONGLONG lastTick = 0;
};
EditHistory g_hist[2];

void EditPush(int op) {  // Snapshot the field before a mutation.
    EditHistory& h = g_hist[g_openFolder != nullptr];
    ULONGLONG now = GetTickCount64();
    bool merge = (op == 1 || op == 2) && op == h.lastOp &&
                 now - h.lastTick < 1000 && g_caret == h.lastEnd &&
                 !h.undo.empty();
    if (!merge) {
        h.undo.push_back({EditText(), g_caret, g_anchor});
        if (h.undo.size() > 100) {
            h.undo.erase(h.undo.begin());
        }
        h.redo.clear();
    }
    h.lastOp = op;
    h.lastTick = now;
}

void EditDone() {  // Remember where the mutation left the caret, for merging.
    g_hist[g_openFolder != nullptr].lastEnd = g_caret;
}

void UndoEdit() {
    EditHistory& h = g_hist[g_openFolder != nullptr];
    if (h.undo.empty()) {
        return;
    }
    h.redo.push_back({EditText(), g_caret, g_anchor});
    if (h.redo.size() > 100) {
        h.redo.erase(h.redo.begin());
    }
    EditSnapshot s = h.undo.back();
    h.undo.pop_back();
    EditText() = s.text;
    g_caret = std::min(s.caret, EditText().size());
    g_anchor = std::min(s.anchor, EditText().size());
    h.lastOp = 0;
    TouchCaret();
    EditChanged();
}

void RedoEdit() {
    EditHistory& h = g_hist[g_openFolder != nullptr];
    if (h.redo.empty()) {
        return;
    }
    h.undo.push_back({EditText(), g_caret, g_anchor});
    if (h.undo.size() > 100) {
        h.undo.erase(h.undo.begin());
    }
    EditSnapshot s = h.redo.back();
    h.redo.pop_back();
    EditText() = s.text;
    g_caret = std::min(s.caret, EditText().size());
    g_anchor = std::min(s.anchor, EditText().size());
    h.lastOp = 0;
    TouchCaret();
    EditChanged();
}

bool CaretVisible() {
    UINT blink = GetCaretBlinkTime();
    if (!blink || blink > 5000) {
        blink = 530;  // The Windows default.
    }
    return (GetTickCount64() - g_caretTick) / blink % 2 == 0;
}

void SetCaret(size_t pos, bool extend) {
    g_caret = std::min(pos, EditText().size());
    if (!extend) {
        g_anchor = g_caret;
    }
    g_hist[g_openFolder != nullptr].lastOp = 0;  // A caret move starts a new
    TouchCaret();                                // undo step, like anywhere.
}

bool DeleteSelection() {
    size_t from, to;
    if (!SearchSelection(&from, &to)) {
        return false;
    }
    EditText().erase(from, to - from);
    g_caret = g_anchor = from;
    TouchCaret();
    return true;
}

void InsertAtCaret(std::wstring text) {
    DeleteSelection();
    size_t max = MaxEditChars();
    size_t room = max - std::min(EditText().size(), max);
    if (text.size() > room) {
        text.resize(room);
    }
    if (text.empty()) {
        return;
    }
    g_caret = std::min(g_caret, EditText().size());
    EditText().insert(g_caret, text);
    g_caret = g_anchor = g_caret + text.size();
    TouchCaret();
}

void CopySelection(bool cut) {
    size_t from, to;
    if (!SearchSelection(&from, &to) || !OpenClipboard(g_wnd)) {
        return;
    }
    if (EmptyClipboard()) {
        if (HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE,
                                      (to - from + 1) * sizeof(WCHAR))) {
            if (WCHAR* p = (WCHAR*)GlobalLock(mem)) {
                memcpy(p, EditText().c_str() + from,
                       (to - from) * sizeof(WCHAR));
                p[to - from] = 0;
                GlobalUnlock(mem);
                if (!SetClipboardData(CF_UNICODETEXT, mem)) {
                    GlobalFree(mem);
                }
            } else {
                GlobalFree(mem);
            }
        }
    }
    CloseClipboard();
    if (cut) {
        EditPush(0);
        DeleteSelection();
        EditDone();
        EditChanged();
    }
}

// The search field's text box, or the open folder's name.
D2D1_RECT_F FolderTitlePill() {
    auto title = GetFolderLayout().title;
    float scale = g_layout.scale;
    float width = 140 * scale;
    if (g_openFolder && g_dwrite && g_messageFormat) {
        ComPtr<IDWriteTextLayout> layout;
        const auto& name = g_openFolder->name;
        if (SUCCEEDED(g_dwrite->CreateTextLayout(name.c_str(), (UINT32)name.size(),
                g_messageFormat.Get(), 10000, 100 * scale, &layout))) {
            DWRITE_TEXT_METRICS metrics{};
            layout->GetMetrics(&metrics);
            width = std::max(width, metrics.widthIncludingTrailingWhitespace + 36 * scale);
        }
    }
    width = std::min(width, title.right-title.left);
    float cx = (title.left+title.right)/2, cy = (title.top+title.bottom)/2;
    return D2D1::RectF(cx-width/2, cy-17*scale, cx+width/2, cy+17*scale);
}

D2D1_RECT_F EditBox(bool folder) {
    if (folder) {
        auto r = FolderTitlePill();
        r.left += 14 * g_layout.scale;
        r.right -= 14 * g_layout.scale;
        return r;
    }
    const D2D1_RECT_F& r = g_layout.search;
    float s = g_layout.scale;
    // A few DIP right of the magnifier, and never under the bar's buttons.
    float right = g_query.empty() ? g_layout.menuButton.left
                                  : g_layout.clearButton.left;
    return D2D1::RectF(r.left + 36 * s, r.top, right - 4 * s, r.bottom);
}

// A text field as drawn: its layout, the box it is clipped to, and where the
// layout's left edge sits. Text too long for the box slides so the caret
// stays in view; a folder name that fits stays centered. A null layout when
// there is no format.
struct EditView {
    ComPtr<IDWriteTextLayout> layout;
    D2D1_RECT_F box;
    float originX;
};

EditView GetEditView(bool folder) {
    EditView v{};
    v.box = EditBox(folder);
    v.originX = v.box.left;
    IDWriteTextFormat* format =
        folder ? g_messageFormat.Get() : g_searchFormat.Get();
    if (!format || (folder && !g_openFolder)) {
        return v;
    }
    const std::wstring& text = folder ? g_openFolder->name : g_query;
    g_dwrite->CreateTextLayout(text.c_str(), (UINT32)text.size(), format,
                               10000, v.box.bottom - v.box.top, &v.layout);
    if (!v.layout) {
        return v;
    }
    v.layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    DWRITE_TEXT_METRICS metrics{};
    v.layout->GetMetrics(&metrics);
    float width = metrics.widthIncludingTrailingWhitespace;
    float room = v.box.right - v.box.left - 3 * g_layout.scale;
    if (folder && width <= room) {
        v.originX =
            std::round(v.box.left + (v.box.right - v.box.left - width) / 2);
        return v;
    }
    float endShift = std::max(0.0f, width - room);
    float shift = endShift;
    DWRITE_HIT_TEST_METRICS m{};
    float x = 0, y = 0;
    bool editing = folder ? g_folderRenaming : !g_openFolder;
    if (editing &&
        SUCCEEDED(v.layout->HitTestTextPosition(
            (UINT32)std::min(g_caret, text.size()), FALSE, &x, &y, &m))) {
        if (x - shift < 0) {
            shift = std::min(std::max(x, 0.0f), endShift);
        }
        if (x - shift > room) {
            shift = std::min(std::max(x - room, 0.0f), endShift);
        }
    }
    v.originX = v.box.left - shift;
    return v;
}

// The caret index under a mouse x, in the field being edited.
size_t CaretAtPoint(float x) {
    EditView v = GetEditView(g_openFolder != nullptr);
    size_t size = EditText().size();
    if (!v.layout) {
        return size;
    }
    BOOL trailing = FALSE, inside = FALSE;
    DWRITE_HIT_TEST_METRICS m{};
    float px = std::max(
        std::min(std::max(x, v.box.left), v.box.right) - v.originX, 0.0f);
    if (FAILED(v.layout->HitTestPoint(px, (v.box.bottom - v.box.top) / 2,
                                      &trailing, &inside, &m))) {
        return size;
    }
    return std::min((size_t)(m.textPosition + (trailing ? m.length : 0)), size);
}

// The text, with the selection behind it and a caret that blinks like
// everywhere else in Windows, when this is the field being edited.
void DrawEditView(const EditView& v, bool editing, float caretHeight) {
    if (!v.layout) {
        return;
    }
    const D2D1_RECT_F& box = v.box;
    float caretW = std::max(1.0f, g_layout.scale);
    g_target->PushAxisAlignedClip(
        D2D1::RectF(box.left - caretW - 1, box.top, box.right, box.bottom),
        D2D1_ANTIALIAS_MODE_ALIASED);
    size_t selFrom, selTo;
    if (editing && SearchSelection(&selFrom, &selTo)) {
        DWRITE_HIT_TEST_METRICS rects[8];
        UINT32 count = 0;
        if (SUCCEEDED(v.layout->HitTestTextRange((UINT32)selFrom,
                                                 (UINT32)(selTo - selFrom), 0,
                                                 0, rects, 8, &count))) {
            g_brush->SetColor(D2D1::ColorF(0x89B4FA, 0.35f));
            for (UINT32 i = 0; i < count && i < 8; i++) {
                g_target->FillRectangle(
                    D2D1::RectF(v.originX + rects[i].left,
                                box.top + rects[i].top,
                                v.originX + rects[i].left + rects[i].width,
                                box.top + rects[i].top + rects[i].height),
                    g_brush.Get());
            }
        }
    }
    g_brush->SetColor(D2D1::ColorF(0xCDD6F4, 0.95f));
    g_target->DrawTextLayout(D2D1::Point2F(v.originX, box.top), v.layout.Get(),
                             g_brush.Get());
    if (editing && CaretVisible()) {
        DWRITE_HIT_TEST_METRICS m{};
        float x = 0, y = 0;
        v.layout->HitTestTextPosition(
            (UINT32)std::min(g_caret, EditText().size()), FALSE, &x, &y, &m);
        // Just left of the insertion point, so it never touches the first
        // glyph.
        float caretX = std::round(v.originX + (float)x) - caretW;
        float mid = (box.top + box.bottom) / 2;
        Fill(D2D1::RectF(caretX, mid - caretHeight / 2, caretX + caretW,
                         mid + caretHeight / 2),
             Alpha(g_settings.accent, 0.9f));
    }
    g_target->PopAxisAlignedClip();
}

void DrawSearchBox() {
    const Layout& L = g_layout;
    float s = L.scale;
    const D2D1_RECT_F& r = L.search;
    float radius = (r.bottom - r.top) / 2;
    Fill(r, Alpha(D2D1::ColorF(0x1E1E2E), g_settings.chromeOpacity), radius);
    // Surface1 border at rest, fading out as the hover box takes over.
    g_brush->SetColor(D2D1::ColorF(0x45475A, 1.0f - g_searchGlow));
    g_target->DrawRoundedRectangle(
        D2D1::RoundedRect(D2D1::RectF(r.left + 0.5f, r.top + 0.5f,
                                      r.right - 0.5f, r.bottom - 0.5f),
                          radius - 0.5f, radius - 0.5f),
        g_brush.Get(), 1);
    DrawHoverBox(r, radius, g_searchGlow, 6);

    // Magnifying glass.
    float cx = r.left + 18 * s, cy = (r.top + r.bottom) / 2 - 1 * s;
    g_brush->SetColor(D2D1::ColorF(0xA6ADC8, 0.85f));
    g_target->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 5.5f * s, 5.5f * s),
                          g_brush.Get(), 1.6f * s);
    g_target->DrawLine(D2D1::Point2F(cx + 4 * s, cy + 4 * s),
                       D2D1::Point2F(cx + 8.5f * s, cy + 8.5f * s),
                       g_brush.Get(), 1.6f * s);

    D2D1_RECT_F text = D2D1::RectF(r.left + 36 * s, r.top,
                                   L.menuButton.left - 4 * s, r.bottom);
    if (!g_searchFormat) {
        return;
    }
    if (g_query.empty()) {
        // The placeholder sits a little right of the caret, so the blinking
        // bar never touches the "S".
        D2D1_RECT_F hint = text;
        hint.left += 7 * s;
        g_brush->SetColor(D2D1::ColorF(0x7F849C, 0.9f));  // Overlay1.
        g_target->DrawText(L"Search", 6, g_searchFormat.Get(), hint,
                           g_brush.Get());
    }

    DrawEditView(GetEditView(false), !g_openFolder, 18 * s);
}

void DrawMessage(PCWSTR text) {
    const Layout& L = g_layout;
    if (!g_messageFormat) {
        return;
    }
    g_brush->SetColor(D2D1::ColorF(0xA6ADC8, 0.85f));
    g_target->DrawText(text, (UINT32)wcslen(text), g_messageFormat.Get(),
                       D2D1::RectF(0, L.viewTop, (float)L.width,
                                   L.viewTop + 120 * L.scale),
                       g_brush.Get());
}

bool IsDragged(const Tile& tile) {
    return g_drag.active && tile.app == g_drag.tile.app &&
           tile.folder == g_drag.tile.folder;
}

const std::wstring& TileName(const Tile& tile) {
    return tile.folder ? tile.folder->name : tile.app->name;
}

void DrawTileIcon(const Tile& tile, const D2D1_RECT_F& r, float opacity) {
    float side = r.right - r.left;
    if (tile.folder) {
        // A rounded square with the first nine apps.
        Fill(r, D2D1::ColorF(0x313244, 0.55f * opacity), side * 0.22f);
        // A resting edge (Mocha overlay0) so the folder stands off the backdrop.
        float w = 1.25f * g_layout.scale, in = w / 2;
        g_brush->SetColor(D2D1::ColorF(0x6C7086, 0.6f * opacity));
        g_target->DrawRoundedRectangle(
            D2D1::RoundedRect(D2D1::RectF(r.left + in, r.top + in, r.right - in, r.bottom - in),
                              side * 0.22f - in, side * 0.22f - in),
            g_brush.Get(), w);
        float pad = side * 0.12f, gap = side * 0.04f;
        float mini = (side - 2 * pad - 2 * gap) / 3;
        const Tiles& apps = tile.folder->apps;
        for (int i = 0; i < 9 && i < (int)apps.size(); i++) {
            float x = r.left + pad + (i % 3) * (mini + gap);
            float y = r.top + pad + (i / 3) * (mini + gap);
            if (ID2D1Bitmap* bitmap = GetBitmap(*apps[i].app)) {
                g_target->DrawBitmap(bitmap,
                                     D2D1::RectF(x, y, x + mini, y + mini),
                                     opacity,
                                     D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
            }
        }
        return;
    }
    // No backplate: an icon without a bitmap draws as nothing, like
    // Launchpad's blank tiles.
    if (ID2D1Bitmap* bitmap = GetBitmap(*tile.app)) {
        g_target->DrawBitmap(bitmap, r, opacity,
                             D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    }
}

// live: the icon takes the pointer and keys (not the grid behind a folder).
struct TileMotion {
    const void* key;
    D2D1_POINT_2F from;
};
std::vector<TileMotion> g_tileMotion;
double g_tileMotionStart = 0;
bool g_tileMotionAnimating = false;

const void* MotionKey(const Tile& tile) {
    return tile.folder ? (const void*)tile.folder.get() : (const void*)tile.app.get();
}

Cell AnimatedCell(const Tile& tile, Cell cell) {
    float t = std::clamp((float)((Now() - g_tileMotionStart) / 0.20), 0.0f, 1.0f);
    if (t >= 1) return cell;
    for (const auto& motion : g_tileMotion) {
        if (motion.key != MotionKey(tile)) continue;
        float remaining = (1-t)*(1-t)*(1-t);
        float dx = (motion.from.x-cell.icon.left)*remaining;
        float dy = (motion.from.y-cell.icon.top)*remaining;
        for (auto rect : {&cell.icon, &cell.label, &cell.highlight}) {
            rect->left += dx; rect->right += dx;
            rect->top += dy; rect->bottom += dy;
        }
        g_tileMotionAnimating |= std::abs(dx) > 0.1f || std::abs(dy) > 0.1f;
        break;
    }
    return cell;
}

void CaptureTileMotion() {
    if (!Animate()) { g_tileMotion.clear(); return; }
    std::vector<TileMotion> next;
    const Tiles& tiles = g_openFolder ? g_openFolder->apps : g_visible;
    for (int i = 0; i < (int)tiles.size(); ++i) {
        Cell c = AnimatedCell(tiles[i], g_openFolder ? FolderCellAt(i) : CellAt(i));
        next.push_back({MotionKey(tiles[i]), {c.icon.left, c.icon.top}});
    }
    g_tileMotion = std::move(next);
    g_tileMotionStart = Now();
    StartFrames();
}

void DrawTile(const Tile& tile, const Cell& c, int i, bool live) {
    if (IsDragged(tile)) {
        return;  // Its place stays empty; the icon follows the pointer.
    }
    float s = g_layout.scale;
    D2D1_MATRIX_3X2_F base;
    bool wiggle = g_wiggle > 0.001f;
    if (wiggle) {
        // Edit mode: every icon rocks around its center, neighbours out of
        // phase, with the hold ramping the angle in and out.
        g_target->GetTransform(&base);
        float cx = (c.icon.left + c.icon.right) / 2;
        float cy = (c.icon.top + c.icon.bottom) / 2;
        float angle = 2.4f * g_wiggle *
                      std::sin((float)Now() * kTwoPi * 3.1f +
                               (c.icon.left - c.icon.top) * 0.02f);
        g_target->SetTransform(D2D1::Matrix3x2F::Rotation(
                                    angle, D2D1::Point2F(cx, cy)) *
                                base);
    }
    if (live) {
        const void* key = tile.folder ? (const void*)tile.folder.get()
                                      : (const void*)tile.app.get();
        float alpha = GlowAlpha(key, i == g_selected || i == g_hover);
        if (alpha > 0.001f) {
            auto box = c.highlight;
            box.bottom = std::max(box.bottom, c.label.bottom + 6 * s);
            float radius = 7 * s;
            DrawHoverBox(box, radius, alpha);
        }
    }
    if (live && i == g_drag.target) {
        float grow = 8 * s;
        Fill(D2D1::RectF(c.icon.left - grow, c.icon.top - grow,
                         c.icon.right + grow, c.icon.bottom + grow),
             D2D1::ColorF(0x89B4FA, 0.3f), 18 * s);
    }
    DrawTileIcon(tile, c.icon, live && i == g_pressed ? 0.6f : 1.0f);
    if (g_settings.showLabels && g_labelFormat) {
        // Light shadow so the name reads well over any background.
        const std::wstring& name = TileName(tile);
        D2D1_RECT_F shadow = c.label;
        shadow.top += 1 * s;
        shadow.bottom += 1 * s;
        g_brush->SetColor(D2D1::ColorF(0, 0, 0, 0.45f));
        g_target->DrawText(name.c_str(), (UINT32)name.size(),
                           g_labelFormat.Get(), shadow, g_brush.Get());
        g_brush->SetColor(D2D1::ColorF(0xCDD6F4, 0.98f));
        g_target->DrawText(name.c_str(), (UINT32)name.size(),
                           g_labelFormat.Get(), c.label, g_brush.Get());
    }
    if (wiggle) {
        g_target->SetTransform(base);
    }
}

void DrawFolder() {
    if (!g_openFolder) {
        return;
    }
    const Layout& L = g_layout;
    float s = L.scale;
    FolderLayout F = GetFolderLayout();
    Fill(F.panel, D2D1::ColorF(0x1E1E2E, 0.62f), 24 * s);
    g_brush->SetColor(D2D1::ColorF(0x45475A, 0.35f));
    g_target->DrawRoundedRectangle(
        D2D1::RoundedRect(D2D1::RectF(F.panel.left + 0.5f, F.panel.top + 0.5f,
                                      F.panel.right - 0.5f,
                                      F.panel.bottom - 0.5f),
                          24 * s, 24 * s),
        g_brush.Get(), 1);

    auto title = FolderTitlePill();
    Fill(title, D2D1::ColorF(0x1E1E2E, 0.80f), 17*s);
    g_brush->SetColor(D2D1::ColorF(0x585B70, 0.85f));
    g_target->DrawRoundedRectangle(D2D1::RoundedRect(title,17*s,17*s),g_brush.Get(),s);
    DrawHoverBox(title,17*s,(g_folderTitleHover || g_folderRenaming) ? 1.0f : 0.0f,4);
    DrawEditView(GetEditView(true), g_folderRenaming, 20 * s);

    const Tiles& apps = g_openFolder->apps;
    g_target->PushAxisAlignedClip(
        D2D1::RectF(F.panel.left, F.top, F.panel.right,
                    F.top + F.visibleRows * F.cellHeight),
        D2D1_ANTIALIAS_MODE_ALIASED);
    int first = g_folderRow * F.columns;
    int last = std::min((int)apps.size(),
                        (g_folderRow + F.visibleRows) * F.columns);
    for (int i = first; i < last; i++) {
        DrawTile(apps[i], AnimatedCell(apps[i], FolderCellAt(i)), i, true);
    }
    g_target->PopAxisAlignedClip();
}

void DrawDragged() {
    if (!g_drag.active) {
        return;
    }
    float icon = g_layout.icon, size = std::round(icon * 1.06f);
    float x = g_drag.at.x - g_drag.grab.x - (size - icon) / 2;
    float y = g_drag.at.y - g_drag.grab.y - (size - icon) / 2;
    DrawTileIcon(g_drag.tile, D2D1::RectF(x, y, x + size, y + size), 0.92f);
}

void DrawGrid() {
    const Layout& L = g_layout;
    float s = L.scale;
    if (!g_appsLoaded && g_apps.empty()) {
        DrawMessage(L"Loading apps\u2026");
        return;
    }
    if (g_visible.empty()) {
        DrawMessage(!g_query.empty() ? L"No apps found"
                    : PinnedOnly()
                        ? L"Nothing pinned yet. Type to find an app, then "
                          L"right-click it to pin it"
                        : L"No apps");
        return;
    }

    g_target->PushAxisAlignedClip(
        D2D1::RectF(0, L.viewTop, (float)L.width, L.viewBottom),
        D2D1_ANTIALIAS_MODE_ALIASED);
    int first, last;
    if (g_settings.pages) {  // The one or two pages on screen.
        int page = std::max(0, (int)(g_scroll / L.width));
        first = page * L.perPage;
        last = std::min((int)g_visible.size(), (page + 2) * L.perPage);
    } else {
        int firstRow = std::max(0, (int)(g_scroll / L.cellHeight));
        int lastRow =
            (int)((g_scroll + L.viewBottom - L.viewTop) / L.cellHeight) + 1;
        first = firstRow * L.columns;
        last = std::min((int)g_visible.size(), (lastRow + 1) * L.columns);
    }
    for (int i = first; i < last; i++) {
        DrawTile(g_visible[i], AnimatedCell(g_visible[i], CellAt(i)), i, !g_openFolder);
    }
    g_target->PopAxisAlignedClip();

    if (g_settings.pages) {
        // One dot per page; the current one is brighter.
        if (L.pages >= 1) {
            float step = 20 * s, r = 3.5f * s;
            float left = L.width / 2.0f - L.pages * step / 2 + step / 2;
            float current = g_scroll / L.width;
            for (int i = 0; i < L.pages; i++) {
                float closeness = std::max(0.0f, 1 - std::abs(current - i));
                g_brush->SetColor(D2D1::ColorF(0xCDD6F4, 0.25f + 0.65f * closeness));
                g_target->FillEllipse(
                    D2D1::Ellipse(D2D1::Point2F(left + i * step, L.dotsY), r, r),
                    g_brush.Get());
            }
        }
        return;
    }

    // Subtle scroll bar, only when there's something to scroll.
    float maxScroll = MaxScroll();
    if (maxScroll > 0) {
        float track = L.viewBottom - L.viewTop;
        float thumb = std::max(40 * s, track * track / L.contentHeight);
        float top = L.viewTop + (track - thumb) * (g_scroll / maxScroll);
        float right = (float)L.width - 10 * s;
        Fill(D2D1::RectF(right - 4 * s, top, right, top + thumb),
             D2D1::ColorF(0x45475A, 0.8f), 2 * s);
    }
}

void Render() {
    if (!g_shown || !EnsureTarget()) {
        return;
    }
    const Layout& L = g_layout;
    if (!EnsureSurface(g_surface, L.width, L.height) ||
        !EnsureFrame(L.width, L.height)) {
        return;
    }
    // The halo is blurred once per size, outside the frame's BeginDraw.
    if ((g_hover >= 0 || g_selected >= 0) &&
        g_settings.glowStrength > 0.001f) {
        EnsureGlowBitmap((int)L.icon, L.scale);
    }
    g_target->SetTarget(g_frame.Get());
    float W = (float)L.width, H = (float)L.height;
    g_target->BeginDraw();
    g_target->SetTransform(D2D1::Matrix3x2F::Identity());
    // Minimum alpha instead of zero: fully transparent pixels of a layered
    // window let the click pass through to what's behind.
    g_target->Clear(D2D1::ColorF(0, 0, 0, 1 / 255.0f));
    if (g_settings.blurMode == BlurMode::Custom) {
        if (ID2D1Bitmap* bitmap = GetBackdropBitmap()) {
            g_target->DrawBitmap(
                bitmap, D2D1::RectF(0, 0, W, H), 1,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                D2D1::RectF(0, 0, g_backdropImage.sourceWidth,
                            g_backdropImage.sourceHeight));
        }
    }
    Fill(D2D1::RectF(0, 0, W, H), Alpha(g_settings.tint, g_settings.opacity));

    // When opening, the grid arrives from slightly larger, like in Launchpad.
    float zoom = 1.06f - 0.06f * Ease(g_appear);
    g_target->SetTransform(
        D2D1::Matrix3x2F::Scale(zoom, zoom, D2D1::Point2F(W / 2, H / 2)));
    DrawSearchBox();
    DrawMenuButton();
    DrawClearButton();
    DrawGrid();
    DrawPowerBar();
    // A closing folder keeps drawing until its fade ends.
    std::shared_ptr<Folder> realOpen = g_openFolder;
    if (!g_openFolder && g_closingFolder) {
        g_openFolder = g_closingFolder;
    }
    bool folderLayer = false;
    if (g_openFolder) {
        float e = Ease(std::clamp(g_folderAnim, 0.0f, 1.0f));
        // Dim the grid, then lay the folder's glass over it: a blur of the
        // pixels just drawn, read back from the surface when they changed.
        Fill(D2D1::RectF(0, 0, W, H), D2D1::ColorF(0x11111B, 0.35f * e));
        D2D1_MATRIX_3X2_F m;
        g_target->GetTransform(&m);
        D2D1_RECT_F panel = GetFolderLayout().panel;
        // The panel grows from 92% around its centre as it fades in.
        float k = 0.92f + 0.08f * e;
        m = D2D1::Matrix3x2F::Scale(
                k, k,
                D2D1::Point2F((panel.left + panel.right) / 2,
                              (panel.top + panel.bottom) / 2)) *
            D2D1::Matrix3x2F(m._11, m._12, m._21, m._22, m._31, m._32);
        D2D1_RECT_F dev = D2D1::RectF(
            panel.left * m._11 + m._31, panel.top * m._22 + m._32,
            panel.right * m._11 + m._31, panel.bottom * m._22 + m._32);
        const void* folder = g_openFolder.get();
        g_target->SetTransform(D2D1::Matrix3x2F::Identity());
        if (g_drag.active || !PanelBlurFresh(dev, folder, g_scroll)) {
            if (g_target->EndDraw() == D2DERR_RECREATE_TARGET) {
                ResetTarget();
                return;
            }
            CapturePanelBlur(dev, folder, g_scroll, L.scale);
            g_target->SetTarget(g_frame.Get());
            g_target->BeginDraw();
        }
        if (e < 0.999f) {
            g_target->PushLayer(
                D2D1::LayerParameters1(D2D1::InfiniteRect(), nullptr,
                                       D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
                                       D2D1::IdentityMatrix(), e),
                nullptr);
            folderLayer = true;
        }
        DrawPanelBlur(dev, 24 * L.scale * m._11);
        g_target->SetTransform(m);
    }
    DrawFolder();
    if (folderLayer) {
        g_target->PopLayer();
    }
    g_openFolder = realOpen;
    DrawDragged();
    g_target->SetTransform(D2D1::Matrix3x2F::Identity());

    if (g_target->EndDraw() == D2DERR_RECREATE_TARGET) {
        ResetTarget();
        return;
    }
    PresentFrame();
    POINT dst{L.area.left, L.area.top}, src{0, 0};
    SIZE size{L.width, L.height};
    BLENDFUNCTION blend{AC_SRC_OVER, 0, (BYTE)std::lround(255 * Ease(g_appear)),
                        AC_SRC_ALPHA};
    UpdateLayeredWindow(g_wnd, nullptr, &dst, &size, g_surface.dc, &src, 0,
                        &blend, ULW_ALPHA);
}

void StartFrames() {
    if (!g_frameTimer) {
        g_frameTimer = true;
        g_lastFrame = Now();
        SetTimer(g_wnd, kTimerFrame, 10, nullptr);
    }
}

void HideNow() {
    EndDrag(false);
    g_searchDrag = false;
    KillTimer(g_wnd, kTimerCaret);
    DisarmPower();
    g_powerHover = g_powerPressed = -1;
    std::fill(std::begin(g_powerGlow), std::end(g_powerGlow), 0.0f);
    g_powerDockGlow = 0;
    if (g_openFolder) {
        SaveTiles();  // Keeps a new folder name.
        g_openFolder = nullptr;
    }
    g_closingFolder = nullptr;
    g_folderAnim = 0;
    HWND wnd = g_wnd;
    ShowWindow(wnd, SW_HIDE);
    ShowWindow(g_backdrop, SW_HIDE);
    g_shown = false;
    g_closing = false;
    g_appear = 0;
    g_backdropImage = {};
    g_panelBlur = {};
    FreeSurface(g_surface);
    g_trackingMouse = false;
    g_menuHover = g_clearHover = g_searchHover = false;
    g_searchGlow = g_btnGlow = 0;
}

void OnFrame() {
    double now = Now();
    float dt = (float)std::clamp(now - g_lastFrame, 0.0, 0.05);
    g_lastFrame = now;
    if (!Animate()) {
        dt = 1.0f;  // Every step below lands on its target this frame.
    }
    bool animating = false;

    // Folders fade and grow in over about 180 ms, and out the same way.
    if (g_openFolder || g_closingFolder) {
        float folderTarget = g_openFolder ? 1.0f : 0.0f;
        if (g_folderAnim != folderTarget) {
            float step = dt / 0.18f;
            g_folderAnim = g_folderAnim < folderTarget
                               ? std::min(folderTarget, g_folderAnim + step)
                               : std::max(folderTarget, g_folderAnim - step);
            animating = true;
        }
        if (!g_openFolder && g_folderAnim <= 0) {
            g_closingFolder = nullptr;
            g_panelBlur = {};
        }
    }

    float target = g_closing ? 0.0f : 1.0f;
    if (g_appear != target) {
        float speed = g_closing ? 1 / 0.14f : 1 / 0.2f;
        g_appear = g_closing ? std::max(0.0f, g_appear - dt * speed)
                             : std::min(1.0f, g_appear + dt * speed);
        animating = g_appear != target;
    }
    if (g_scroll != g_scrollTarget) {
        g_scroll += (g_scrollTarget - g_scroll) * std::min(1.0f, dt * 16);
        if (std::abs(g_scrollTarget - g_scroll) < 0.5f) {
            g_scroll = g_scrollTarget;
        }
        animating |= g_scroll != g_scrollTarget;
    }

    // Edit mode only once the drag is real: the press moved past the system
    // drag threshold or has been held for the hold time. A plain click never
    // wiggles.
    float wiggleTarget =
        g_drag.active && g_settings.wiggle && Animate() ? 1.0f : 0.0f;
    if (g_wiggle != wiggleTarget) {
        g_wiggle += (wiggleTarget - g_wiggle) * std::min(1.0f, dt * 12);
        if (std::abs(wiggleTarget - g_wiggle) < 0.01f) {
            g_wiggle = wiggleTarget;
        }
        animating = true;
    }
    if (g_wiggle > 0.001f) {
        animating = true;
    }

    // A press held still for the hold time lifts the icon into edit mode.
    if (g_drag.pending && !g_drag.active &&
        now - g_drag.pressTime >= g_settings.holdMs / 1000.0) {
        StartDrag();
        animating = true;
    }

    // The search bar's accent glow eases in and out, about 140 ms.
    float glowTarget =
        g_searchHover || g_clearHover || !g_query.empty() ? 1.0f : 0.0f;
    if (g_searchGlow != glowTarget) {
        g_searchGlow +=
            (glowTarget - g_searchGlow) * std::min(1.0f, (float)(dt * 18));
        if (std::abs(glowTarget - g_searchGlow) < 0.01f) {
            g_searchGlow = glowTarget;
        }
        animating = true;
    }
    float btnTarget = g_menuHover ? 1.0f : 0.0f;
    if (g_btnGlow != btnTarget) {
        g_btnGlow += (btnTarget - g_btnGlow) * std::min(1.0f, (float)(dt * 18));
        if (std::abs(btnTarget - g_btnGlow) < 0.01f) {
            g_btnGlow = btnTarget;
        }
        animating = true;
    }

    // The power dock glows fade over about 140 ms.
    for (int slot = 0; slot < (int)g_layout.powerItems.size(); slot++) {
        float& value = g_powerGlow[g_layout.powerItems[slot]];
        float target =
            slot == g_powerHover || slot == g_powerArmed ? 1.0f : 0.0f;
        if (value != target) {
            float step = dt / 0.14f;
            value = value < target ? std::min(target, value + step)
                                   : std::max(target, value - step);
            animating = true;
        }
    }
    float dockTarget = g_powerHover >= 0 ? 1.0f : 0.0f;
    if (g_powerDockGlow != dockTarget) {
        float step = dt / 0.14f;
        g_powerDockGlow =
            g_powerDockGlow < dockTarget
                ? std::min(dockTarget, g_powerDockGlow + step)
                : std::max(dockTarget, g_powerDockGlow - step);
        animating = true;
    }

    if (g_drag.active) {
        DragTick();
        animating = true;
    }

    if (g_closing && g_appear <= 0) {
        HideNow();
        animating = false;
    } else {
        g_glowAnimating = false;
        g_tileMotionAnimating = false;
        Render();
        animating |= g_glowAnimating || g_tileMotionAnimating;
    }
    if (!animating) {
        KillTimer(g_wnd, kTimerFrame);
        g_frameTimer = false;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Opening and closing

// SetForegroundWindow succeeds when the calling process received the last
// input event; an empty SendInput provides it.
void ForceForeground(HWND hwnd) {
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}

void PlaceWindows() {
    const RECT& a = g_layout.area;
    // Always on top: Windows sometimes leaves "always on top" windows (the
    // Dock included) below regular ones, and positioning below the Dock
    // put Start behind the windows.
    SetWindowPos(g_wnd, HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    if (!g_settings.coverScreen) {
        RaiseDockWindows();
    }
    if (UsesDwmBackdrop()) {
        SetWindowPos(g_backdrop, g_wnd, a.left, a.top, a.right - a.left,
                     a.bottom - a.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }
}

void Open() {
    if (g_shown) {
        if (g_closing) {  // Reopened in the middle of closing.
            g_closing = false;
            ForceForeground(g_wnd);
            PlaceWindows();
            StartFrames();
        }
        return;
    }

    HMONITOR monitor = ChosenMonitor();
    UINT dpiX = 96, dpiY = 96;
    GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY);

    Layout& L = g_layout;
    L.area = AvailableArea(monitor);
    L.width = L.area.right - L.area.left;
    L.height = L.area.bottom - L.area.top;
    L.scale = dpiX / 96.0f;
    EnsureFormats(L.scale);

    g_query.clear();
    g_caret = g_anchor = 0;
    g_hist[0] = {};  // A fresh search starts a fresh history.
    g_searchDrag = false;
    TouchCaret();
    g_hover = g_selected = g_pressed = -1;
    g_scroll = g_scrollTarget = 0;
    g_wheelDelta = 0;
    g_openFolder = nullptr;
    g_folderRow = 0;
    g_powerHover = g_powerPressed = g_powerArmed = -1;
    RefreshPowerCaps();
    UpdateFilter();
    ComputeLayout();

    // The background screenshot is taken before any of the mod's windows appear.
    if (g_settings.blurMode == BlurMode::Custom) {
        CaptureBackdrop(L.area, g_settings.blurAmount / 100.0f * 60 * L.scale);
    }
    if (UsesDwmBackdrop()) {
        ApplyBackdropEffect();
    }

    g_shown = true;
    g_closing = false;
    g_appear = 0;
    Render();
    ShowWindow(g_wnd, SW_SHOW);
    UINT blink = GetCaretBlinkTime();
    SetTimer(g_wnd, kTimerCaret, blink ? blink : 530, nullptr);
    ForceForeground(g_wnd);
    PlaceWindows();
    StartFrames();

    if (!g_appsLoaded || Now() - g_appsTime > 60 ||
        g_appsKey != AppsKey()) {
        StartLoadingApps();
    }
}

void Close() {
    if (!g_shown || g_closing) {
        return;
    }
    g_closing = true;
    g_pressed = g_powerPressed = -1;
    DisarmPower();
    EndDrag(false);
    if (g_openFolder) {
        SaveTiles();  // Keeps a new folder name.
    }
    if (GetCapture() == g_wnd) {
        ReleaseCapture();
    }
    StartFrames();
}

void Toggle() {
    if (g_shown && !g_closing) {
        Close();
    } else {
        Open();
    }
}

// A packaged app with no Start-menu shortcut: runas on its raw AppsFolder
// target is a silent no-op, so a temporary .lnk aimed at the target carries
// the elevation instead — the shell brokers that into an elevated launch
// (verified: the spawned Terminal answers the elevation token query).
void LaunchTarget(const std::wstring& target, PCWSTR verb);
void ElevateViaTempLnk(const std::wstring& target) {
    PWSTR temp = nullptr;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &temp))) {
        return;
    }
    std::wstring dir = std::wstring(temp) + L"\\SeamlessLaunchpad";
    CoTaskMemFree(temp);
    CreateDirectoryW(dir.c_str(), nullptr);
    std::wstring lnk = dir + L"\\Run as administrator.lnk";

    IShellLinkW* link = nullptr;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER,
                                   IID_PPV_ARGS(&link)))) {
        link->SetPath(target.c_str());
        IPersistFile* file = nullptr;
        if (SUCCEEDED(link->QueryInterface(IID_PPV_ARGS(&file)))) {
            file->Save(lnk.c_str(), TRUE);
            file->Release();
        }
        link->Release();
        LaunchTarget(lnk, L"runas");
    }
}

void LaunchTarget(const std::wstring& target, PCWSTR verb = nullptr) {
    SHELLEXECUTEINFOW sei{sizeof(sei)};
    sei.fMask = SEE_MASK_ASYNCOK;
    sei.lpVerb = verb;
    sei.lpFile = target.c_str();
    sei.nShow = SW_SHOWNORMAL;
    AllowSetForegroundWindow(ASFW_ANY);
    ShellExecuteExW(&sei);
    Close();
}

// The settings window, from the "..." menu. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessLaunchpadSettings";
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1, WM_APP_SETTINGS_ACTIVATE = WM_APP + 2;
HANDLE g_settingsThread = nullptr;
std::atomic<HWND> g_settingsWnd;
std::atomic<bool> g_settingsStop;
void Settings_Close();
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
};

// Names, descriptions and option labels match the ==WindhawkModSettings== block word for word.
// Generated by test-settings\gen_table.py from src\00-header.cpp.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Choice, L"winKeyAction", L"Windows key", L"Also Ctrl+Esc.", L"grid", {{L"grid", L"Open this grid"}, {L"start", L"Open the original Start"}, {L"program", L"Run the program below"}}, 0, 100, 0, L"Open Launchpad"},
{K::Choice, L"shiftWinKeyAction", L"Shift + Windows key", L"", L"start", {{L"grid", L"Open this grid"}, {L"start", L"Open the original Start"}, {L"program", L"Run the program below"}}, 0, 100, 0, L"Open Launchpad"},
{K::Choice, L"startButtonAction", L"Start button", L"The taskbar Start button, the Standalone Dock's, and every other way Start opens that is not the keyboard.", L"grid", {{L"grid", L"Open this grid"}, {L"start", L"Open the original Start"}, {L"program", L"Run the program below"}}, 0, 100, 0, L"Open Launchpad"},
{K::Text, L"program", L"Program", L"What \"Run the program below\" starts. A command line such as \"C:\\Program Files\\App\\app.exe\" --flag, or a shortcut, file, folder or web address", L"", {}, 0, 100, 0, L"Open Launchpad"},
{K::Choice, L"monitor", L"Monitor", L"Where the grid opens. Monitors 2 to 4 are the other monitors, counted left to right. If the picked monitor is not connected, it opens where the mouse is.", L"mouse", {{L"mouse", L"The monitor with the mouse"}, {L"1", L"Main monitor"}, {L"2", L"Monitor 2"}, {L"3", L"Monitor 3"}, {L"4", L"Monitor 4"}}, 0, 100, 1, L"Grid"},
{K::Choice, L"appSource", L"Apps to show", L"With pinned apps, search still finds every app. Right-click an app to pin or unpin it.", L"allApps", {{L"allApps", L"Start menu apps (the All apps list)"}, {L"desktop", L"Desktop icons"}, {L"both", L"Start menu apps and desktop icons"}, {L"pinned", L"Only the apps you pin"}}, 0, 100, 1, L"Grid"},
{K::Choice, L"gridLayout", L"Layout", L"How the grid is arranged.", L"scroll", {{L"scroll", L"One list that scrolls up and down"}, {L"pages", L"Pages that flip left and right, like Launchpad"}}, 0, 100, 1, L"Grid"},
{K::Number, L"gridColumns", L"Columns", L"0 to 30. 0 picks a number that fits the screen (Suggested: 0).", L"0", {}, 0, 30, 1, L"Grid"},
{K::Check, L"coverScreen", L"Cover the whole screen", L"On, the grid also covers the taskbar, side bars and the Standalone Dock. Off, they stay visible.", L"0", {}, 0, 100, 1, L"Grid"},
{K::Number, L"gridIconSize", L"Icon size", L"24 to 192 (Suggested: 72). Pixels at 100% scaling.", L"72", {}, 24, 192, 1, L"Grid"},
{K::Check, L"showLabels", L"Icon labels", L"On, the app name shows under each icon. Off, icons only.", L"1", {}, 0, 100, 1, L"Grid"},
{K::Check, L"normalizeIcons", L"Fill small icons", L"Scale small or padded icons to full size.", L"1", {}, 0, 100, 1, L"Grid"},
{K::Choice, L"blurMode", L"Background blur", L"The kind of blur behind the grid.", L"custom", {{L"custom", L"Adjustable (uses the strength below)"}, {L"acrylic", L"Windows acrylic (DWM)"}, {L"blur", L"Windows blur (DWM)"}, {L"none", L"No blur"}}, 0, 100, 2, L"Appearance"},
{K::Number, L"blurAmount", L"Blur strength", L"0 to 100 (Suggested: 60). Only for the adjustable blur. The Windows ones have a fixed strength.", L"60", {}, 0, 100, 2, L"Appearance"},
{K::Number, L"backgroundOpacity", L"Background opacity (%)", L"0 to 100 (Suggested: 30). 0 leaves only the blur, 100 covers everything with the color.", L"30", {}, 0, 100, 2, L"Appearance"},
{K::Color, L"tintColor", L"Background color", L"In hexadecimal, like #1E1E2E.", L"#000000", {}, 0, 100, 2, L"Appearance"},
{K::Color, L"accentColor", L"Accent color", L"In hexadecimal, like #89B4FA. Tints the glows and highlights.", L"#89B4FA", {}, 0, 100, 2, L"Appearance"},
{K::Number, L"glowStrength", L"Glow strength", L"0 to 100 (Suggested: 60). How strongly hovered buttons glow.", L"60", {}, 0, 100, 2, L"Appearance"},
{K::Number, L"glowSize", L"Glow size", L"4 to 40 (Suggested: 14). How far a glow spreads, in DIP at 100% scaling.", L"14", {}, 4, 40, 2, L"Appearance"},
{K::Number, L"chromeOpacity", L"Search bar and dock opacity (%)", L"0 to 100 (Suggested: 90). How solid the search bar and the power dock are.", L"90", {}, 0, 100, 2, L"Appearance"},
{K::Check, L"powerBar", L"Power dock", L"The pill of power buttons at the bottom of the grid.", L"1", {}, 0, 100, 3, L"Power buttons"},
{K::Choice, L"dockAlignment", L"Dock position", L"Where the power dock sits along the bottom edge.", L"center", {{L"left", L"Left"}, {L"center", L"Center"}, {L"right", L"Right"}}, 0, 100, 3, L"Power buttons"},
{K::Check, L"powerButtons.lock", L"Lock", L"", L"1", {}, 0, 100, 3, L"Power buttons"},
{K::Check, L"powerButtons.signOut", L"Sign out", L"", L"1", {}, 0, 100, 3, L"Power buttons"},
{K::Check, L"powerButtons.sleep", L"Sleep", L"", L"1", {}, 0, 100, 3, L"Power buttons"},
{K::Check, L"powerButtons.hibernate", L"Hibernate", L"Shows only when hibernation is turned on in Windows.", L"1", {}, 0, 100, 3, L"Power buttons"},
{K::Check, L"powerButtons.restart", L"Restart", L"", L"1", {}, 0, 100, 3, L"Power buttons"},
{K::Check, L"powerButtons.shutDown", L"Shut down", L"", L"1", {}, 0, 100, 3, L"Power buttons"},
{K::Check, L"powerNoConfirm", L"Skip confirmation", L"On, a power button acts on the first click. Off, the first click arms it and a second click on the same button confirms.", L"0", {}, 0, 100, 3, L"Power buttons"},
{K::Check, L"wiggle", L"Edit mode wiggle", L"While you drag an icon, all icons wiggle like on iOS.", L"1", {}, 0, 100, 1, L"Grid"},
{K::Number, L"holdTime", L"Drag hold time", L"150 to 1500 (Suggested: 420). Milliseconds to hold an icon before dragging starts.", L"420", {}, 150, 1500, 1, L"Grid"},
{K::Check, L"animations", L"Animations", L"Off, everything snaps instantly. Opening, folders, hover fades, tile moves and wiggle all turn off.", L"1", {}, 0, 100, 1, L"Grid"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.", L"1", {}, 0, 100, 2, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.", L"0", {}, 0, 100, 2, L"Settings window"},
{K::Choice, L"settingsTitleButtons", L"Title bar buttons", L"Who draws minimize, maximize and close on the window's own title bar. Windows buttons look like every other app's, title bar mods included. Save, then reopen settings to apply.", L"native", {{L"native", L"Windows buttons (like other apps)"}, {L"builtin", L"Built-in buttons"}}, 0, 100, 2, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"A Launchpad icon in the system tray. Click it to open these settings, right-click it for a menu.", L"1", {}, 0, 100, 2, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Keys", L"Choose how you open Launchpad and other programs.", 0xE765},
{L"Grid", L"Apps, icon sizes, pages and motion.", 0xE80A},
{L"Look", L"Blur, colors, glow, search bar and this window.", 0xE790},
{L"Power", L"Choose which power actions appear in the dock.", 0xE7E8},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
// The sidebar is a floating dock: dragged between min and max, or collapsed to an icon rail.
constexpr float kSetDockGap = 10, kSetRailDef = 232, kSetRailMin = 200, kSetRailMax = 380, kSetRailMini = 60,
                kSetRailSnap = 130, kSetEdgeGrab = 5;
// The footer is a floating pill dock at the bottom right of the page.
constexpr float kSetFootBtnH = 36, kSetFootPad = 8, kSetFootH = kSetFootBtnH + 2 * kSetFootPad, kSetFootGap = 14;
// The glass tint is one layer over the whole window, title bar included, so the two always match.
constexpr float kSetGlassTint = 0.42f, kSetNativeFade = 56;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/fullscreen-start";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Launchpad%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Launchpad";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;

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
    int dropHover = -1;
    float scrollY = 0, scrollTarget = 0, contentH = 0, contentX = 0, contentW = 720, pageT = 1;
    SetHit hover;
    int dragSlider = -1;
    bool dragScroll = false, tracking = false, timer = false;
    float dragOff = 0;
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
static void Set_MakeFormats(SetWindow& w) {
    w.family = Set_ResolveFamily();
    w.iconFamily = Set_FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    int base = std::clamp(500, 100, 900);
    int bold = std::max(base, std::min(700, base + 100));
    const auto L_ = DWRITE_TEXT_ALIGNMENT_LEADING, C_ = DWRITE_TEXT_ALIGNMENT_CENTER;
    w.fLabel = Set_Fmt(w.family, 14, base, true);
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Launchpad") <= railW) break;
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
    return !w.render && g_settings.animations && on;
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
static float Set_ControlW(const SetField& f) {
    switch (f.kind) {
        case SetField::Check: return 40;
        case SetField::Choice: return 200;
        case SetField::Number: return f.max - f.min <= 100 ? 150 + 12 + 64 : 96;
        case SetField::Text: return 280;
        case SetField::Hotkey: return 220;
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
            p.box = {r - 200, mid - h, r, mid + h};
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
            p.box = {r - 280, mid - h, r, mid + h};
            break;
        case SetField::Hotkey:
            p.box = {r - 220, mid - h, r, mid + h};
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
        add(SetItem::Link, 56, L"Based on Fullscreen Start by Rafael Mendes", L"The original Windhawk mod", kSetDittoUrl);
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

static void Set_DrawBox(SetPaint& p, SetWindow& w, int k, const D2D1_RECT_F& box, bool active) {
    p.Round(box, 8, mocha::crust);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.GradRing(box, 8, g);
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
    float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = row.top + (it.h - lh - dh) / 2;
    p.Text(w.fLabel.get(), f.label, {row.left + kSetRowPad, top, row.left + kSetRowPad + textW, top + lh + 2}, mocha::text);
    if (f.desc)
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
    p.Glyph(w.fIconL.get(), 0xE80A, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Launchpad", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Apps, folders and search in one fullscreen grid, in place of Start.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, based on Fullscreen Start by Rafael Mendes.",
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
    p.Text(w.fRailName.get(), L"Launchpad", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
        p.Text(w.fLabel.get(), kSetPages[i].name, {r.left + 50, r.top + 8, r.left + w.railW - 24, r.bottom}, c, textA);
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
    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : 0.85f);
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


static void Set_DrawPopup(SetPaint& p, SetWindow& w) {
    if (w.openSel < 0) return;
    const SetField& f = w.fields[w.openSel];
    const D2D1_RECT_F& r = w.dropRect;
    D2D1_RECT_F shadow{r.left - 1, r.top + 3, r.right + 1, r.bottom + 5};
    p.Round(shadow, 12, mocha::crust, 0.6f);
    p.Round(r, 10, mocha::mantle);
    p.GradRing(r, 10, 0.9f);
    for (size_t i = 0; i < f.options.size(); i++) {
        D2D1_RECT_F it{r.left + 4, r.top + 4 + i * kSetDropItem, r.right - 4, r.top + 4 + (i + 1) * kSetDropItem};
        bool sel = f.cur == f.options[i].first;
        if ((int)i == w.dropHover) {
            p.GradFill(it, 6, 0.28f);
            p.GradRing(it, 6, 0.6f, 1);
        }
        p.Text(w.fValue.get(), f.options[i].second, {it.left + 10, it.top, it.right - 28, it.bottom}, sel ? mocha::blue : mocha::text);
        if (sel) p.Glyph(w.fIconS.get(), 0xE73E, {it.right - 28, it.top, it.right - 6, it.bottom}, mocha::blue);
    }
}

// Title bar buttons, in title bar DIPs: 0 minimize, 1 maximize or restore, 2 close.
static D2D1_RECT_F Set_CapButton(const SetWindow& w, int i) {
    float right = w.cw - (2 - i) * kSetCapBtnW;
    return {right - kSetCapBtnW, 0, right, kSetCapH};
}

// y is in content DIPs, so the title bar is y < 0.
static int Set_CapButtonAt(const SetWindow& w, float x, float y) {
    if (w.nativeTitle || w.nativeButtons) return -1;
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
    p.Glyph(glyph, 0xE80A, r, mocha::crust);
}

static void Set_DrawCaption(SetPaint& p, SetWindow& w) {
    if (!w.glass) p.Fill({0, 0, w.cw, kSetCapH}, mocha::crust);  // Glass: the window tint already covers it.
    D2D1_RECT_F t = Set_CapTitleRect(w);
    float mid = kSetCapH / 2;
    Set_DrawMark(p, w.fCapGlyph.get(), {t.left, mid - 8, t.left + 16, mid + 8}, w.active ? 1.0f : 0.6f);
    p.Text(w.fCap.get(), kSetTitle, {t.left + 24, 0, t.right, kSetCapH}, w.active ? mocha::text : mocha::overlay1);
    if (w.nativeButtons) return;  // DWM draws them over this title bar.
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
static void Set_Draw(SetWindow& w, ID2D1RenderTarget* rt) {
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
            D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::crust, 0)}, {1, D2DColor(mocha::crust, kSetGlassTint)}};
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
                blurred = true;
            }
        }
    }
    if (!blurred) drawPage(p);
    rt->SetTransform(base);

    D2D1_RECT_F th = Set_ScrollThumb(w);
    if (th.bottom > th.top) p.Round(th, 3, w.dragScroll ? mocha::overlay1 : mocha::surface2, 0.9f);

    Set_DrawFooter(p, w);
    Set_DrawRail(p, w);
    Set_DrawPopup(p, w);
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
            int i = (int)((y - w.dropRect.top - 4) / kSetDropItem);
            if (i >= 0 && i < (int)w.fields[w.openSel].options.size() && y >= w.dropRect.top + 4) {
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
    Set_Invalidate(w);
}

static void Set_OpenPopup(SetWindow& w, int k) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    const SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float boxTop = pt.box.top - w.scrollY, boxBottom = pt.box.bottom - w.scrollY;
    float h = (float)f.options.size() * kSetDropItem + 8;
    float top = boxBottom + 4;
    if (top + h > Set_ViewH(w) + 20 && boxTop - 4 - h > 0) top = boxTop - 4 - h;  // No room below: open upward.
    w.dropRect = {pt.box.left, top, pt.box.right, top + h};
    w.openSel = k;
    w.dropHover = -1;
    for (size_t i = 0; i < f.options.size(); i++)
        if (f.cur == f.options[i].first) w.dropHover = (int)i;
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
        else if (vk == VK_UP) w.dropHover = (w.dropHover - 1 + n) % n;
        else if (vk == VK_DOWN) w.dropHover = (w.dropHover + 1) % n;
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

static void Set_RememberRect(SetWindow& w) {
    if (w.render || IsIconic(w.hwnd) || IsZoomed(w.hwnd)) return;
    GetWindowRect(w.hwnd, &w.normalRect);
}

static LRESULT CALLBACK Set_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w) return DefWindowProcW(hwnd, msg, wParam, lParam);
    if (w->nativeButtons || w->nativeTitle) {
        LRESULT r = 0;
        if (DwmDefWindowProc(hwnd, msg, wParam, lParam, &r)) return r;  // Hover and clicks on DWM's buttons.
    }
    auto dipX = [&](LPARAM l) { return (float)(short)LOWORD(l) * 96.0f / w->dpi; };
    auto dipY = [&](LPARAM l) { return (float)(short)HIWORD(l) * 96.0f / w->dpi - kSetCapH; };
    switch (msg) {
        case WM_APP_SETTINGS_RELOAD: if (!w->saving) Set_LoadFields(*w); return 0;
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
            SetBkColor(dc, RefFromRgb(mocha::crust));
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
            if (!w->dragRail) w->mouseX = w->mouseY = -1;
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
        case WM_MOUSEWHEEL: {
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
    w->editBrush = CreateSolidBrush(RefFromRgb(mocha::crust));
    g_setWin = w;
    if (render) {
        // An owned window gets no taskbar button.
        w->owner = CreateWindowExW(WS_EX_TOOLWINDOW, L"STATIC", L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                                   GetModuleHandleW(nullptr), nullptr);
    }
    const int offX = GetSystemMetrics(SM_XVIRTUALSCREEN) - 6000, offY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    w->nativeTitle = !render && (Wh_GetIntSetting(L"nativeSettingsTitleBar") != 0 ||
        GetStringSetting(L"settingsTitleButtons") != L"builtin");
    w->nativeButtons = !render && !w->nativeTitle && GetStringSetting(L"settingsTitleButtons") != L"builtin";
    w->glass = !render && Wh_GetIntSetting(L"settingsGlass") != 0;
    kSetCapH = w->nativeTitle ? 0.0f : 40.0f;
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Launchpad settings", style,
                                render ? offX : CW_USEDEFAULT, render ? offY : CW_USEDEFAULT, 800, 600, w->owner,
                                nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (!hwnd) {
        g_setWin.reset();
        return false;
    }
    w->hwnd = hwnd;
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
        if (w->glass) {
            // Windows acrylic as one sheet over the whole window, the way T3 (Electron
            // backgroundMaterial "acrylic") does it: the system backdrop with the frame extended
            // into the full client area, and no caption color, so the title bar and the page are
            // the same material and turn solid together when the window loses focus.
            int backdrop = 3;  // DWMSBT_TRANSIENTWINDOW
            DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
            MARGINS margins{-1, -1, -1, -1};
            DwmExtendFrameIntoClientArea(hwnd, &margins);
            COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
            DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
        } else if (w->nativeButtons) {
            // Solid window: DWM draws its buttons only where the frame reaches, so extend it
            // over the title bar strip.
            MARGINS margins{0, 0, MulDiv((int)kSetCapH, w->dpi, 96), 0};
            DwmExtendFrameIntoClientArea(hwnd, &margins);
        }
        // With the frame extended, DWM draws its own minimize, maximize and close buttons in the
        // corner. "Windows buttons" keeps them (Set_WndProc passes their hover and clicks to
        // DwmDefWindowProc); "Built-in buttons" drops the system menu so DWM draws none and the
        // window draws its own. Minimize, maximize and close still work from the taskbar.
        if (!w->nativeTitle && !w->nativeButtons)
            SetWindowLongPtrW(hwnd, GWL_STYLE, GetWindowLongPtrW(hwnd, GWL_STYLE) & ~WS_SYSMENU);
        // The first WM_NCCALCSIZE ran before w->hwnd was set; drop the system title bar now.
        SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
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

void EnsureVisible(int index) {
    if (index < 0) {
        return;
    }
    if (g_openFolder) {
        FolderLayout F = GetFolderLayout();
        int row = index / F.columns;
        g_folderRow = std::clamp(g_folderRow, row - F.visibleRows + 1, row);
        return;
    }
    const Layout& L = g_layout;
    if (g_settings.pages) {
        g_scrollTarget = (index / L.perPage) * (float)L.width;
        return;
    }
    int row = index / L.columns;
    int firstRow = (int)std::lround(g_scrollTarget / L.cellHeight);
    if (row < firstRow) {
        g_scrollTarget = row * L.cellHeight;
    } else if (row >= firstRow + L.visibleRows) {
        g_scrollTarget = (row - L.visibleRows + 1) * L.cellHeight;
    }
    g_scrollTarget = std::clamp(g_scrollTarget, 0.0f, MaxScroll());
}

// With pages, any number of rows flips one page that way.
void ScrollRows(int rows) {
    if (g_settings.pages) {
        float width = (float)g_layout.width;
        float target =
            (std::lround(g_scrollTarget / width) + (rows > 0 ? 1 : -1)) * width;
        g_scrollTarget = std::clamp(target, 0.0f, MaxScroll());
        StartFrames();
        return;
    }
    float cell = g_layout.cellHeight;
    float target = (std::lround(g_scrollTarget / cell) + rows) * cell;
    g_scrollTarget = std::clamp(target, 0.0f, MaxScroll());
    StartFrames();
}

////////////////////////////////////////////////////////////////////////////////
// Folders, dragging and the right-click menus

// After the arrangement changed.
void Refresh() {
    UpdateFilter();
    ComputeLayout();
    Render();
}

int IndexOf(const Tiles& tiles, const Tile& tile) {
    for (int i = 0; i < (int)tiles.size(); i++) {
        if (tiles[i].app == tile.app && tiles[i].folder == tile.folder) {
            return i;
        }
    }
    return -1;
}

// After a change that may have left the open folder with one app or none.
void DropGoneFolder() {
    TidyTiles();
    if (g_openFolder && IndexOf(g_tiles, {nullptr, g_openFolder}) < 0) {
        g_openFolder = nullptr;
    }
    g_hover = g_selected = g_pressed = -1;
}

void OpenFolder(std::shared_ptr<Folder> folder) {
    g_folderRenaming = false;
    g_folderTitleHover = false;
    g_openFolder = std::move(folder);
    g_closingFolder = nullptr;
    g_folderAnim = Animate() ? 0.0f : 1.0f;
    if (g_folderAnim < 1) {
        StartFrames();
    }
    g_folderRow = 0;
    g_hover = g_selected = g_pressed = -1;
    g_searchDrag = false;
    g_hist[1] = {};  // Fresh history per folder.
    SetCaret(EditText().size(), false);  // At the end of the name.
    Render();
}

void CloseFolder() {
    if (!g_openFolder) {
        return;
    }
    if (Animate()) {
        g_closingFolder = g_openFolder;
        StartFrames();
    }
    g_folderRenaming = false;
    g_folderTitleHover = false;
    g_openFolder = nullptr;
    g_hover = g_selected = g_pressed = -1;
    g_searchDrag = false;
    SetCaret(g_query.size(), false);
    SaveTiles();  // Keeps a new name.
    Refresh();
}

void ActivateItem(int index) {
    const Tiles& items = Items();
    if (index < 0 || index >= (int)items.size()) {
        return;
    }
    if (items[index].folder) {
        OpenFolder(items[index].folder);
    } else {
        LaunchTarget(items[index].app->target);
    }
}

// Where the click doesn't count as one on empty space.
bool ClickKeepsOpen(int x, int y) {
    return g_openFolder ? InRect(GetFolderLayout().panel, (float)x, (float)y)
                        : InRect(g_layout.search, (float)x, (float)y) ||
                              PowerAt(x, y) >= 0;
}

// The words both names start with ("Microsoft Edge" and "Microsoft Teams"
// give "Microsoft"), or "Folder".
std::wstring FolderName(const std::wstring& a, const std::wstring& b) {
    size_t same = 0;
    for (size_t i = 0;; i++) {
        bool endA = i == a.size() || a[i] == L' ';
        bool endB = i == b.size() || b[i] == L' ';
        if (endA && endB) {
            same = i;
            if (i == a.size() || i == b.size()) {
                break;
            }
            continue;
        }
        if (endA || endB || towlower(a[i]) != towlower(b[i])) {
            break;
        }
    }
    return same ? a.substr(0, same) : L"Folder";
}

void StartDrag() {
    const Tiles& items = Items();
    int i = g_pressed;
    g_drag.pending = false;
    if (i < 0 || i >= (int)items.size() || !g_query.empty()) {
        return;
    }
    Cell c = ItemCell(i);
    g_drag.active = true;
    g_drag.tile = items[i];
    g_drag.at = g_drag.start;
    g_drag.grab = D2D1::Point2F(g_drag.start.x - c.icon.left,
                                g_drag.start.y - c.icon.top);
    g_drag.target = g_drag.slot = -1;
    g_drag.edge = 0;
    g_drag.inPanel = g_openFolder != nullptr;
    g_drag.backup = ArrangementLines();
    g_hover = g_selected = g_pressed = -1;
    StartFrames();
}

void DragMove(int x, int y) {
    const Layout& L = g_layout;
    double now = Now();
    g_drag.at = {x, y};
    if (g_openFolder) {
        if (InRect(GetFolderLayout().panel, (float)x, (float)y)) {
            g_drag.inPanel = true;
        } else if (g_drag.inPanel) {
            // Out of the folder, into the grid right after it.
            Tiles& apps = g_openFolder->apps;
            int i = IndexOf(apps, g_drag.tile);
            if (i >= 0) {
                apps.erase(apps.begin() + i);
                int f = IndexOf(g_tiles, {nullptr, g_openFolder});
                g_tiles.insert(g_tiles.begin() + (f + 1), g_drag.tile);
            }
            g_openFolder = nullptr;
            UpdateFilter();
            ComputeLayout();
        }
    }

    // Over the middle of another icon: dropping there makes or fills a folder.
    // The rest of that icon moves nothing, so reaching the middle doesn't
    // shuffle the icons first.
    int target = -1;
    bool overIcon = false;
    if (!g_openFolder && g_drag.tile.app) {
        int i = ItemAt(x, y);
        if (i >= 0 && !IsDragged(g_visible[i])) {
            D2D1_RECT_F r = CellAt(i).icon;
            overIcon = InRect(r, (float)x, (float)y);
            float in = (r.right - r.left) * 0.2f;
            if (InRect(D2D1::RectF(r.left + in, r.top + in, r.right - in,
                                   r.bottom - in),
                       (float)x, (float)y)) {
                target = i;
            }
        }
    }
    if (target != g_drag.target) {
        g_drag.target = target;
        g_drag.targetTime = now;
    }
    int slot = overIcon ? -1 : SlotAt(x, y);
    if (slot != g_drag.slot) {
        g_drag.slot = slot;
        g_drag.slotTime = now;
    }

    int edge = 0;
    if (!g_openFolder) {
        if (g_settings.pages) {
            float zone =
                std::max(36 * L.scale, std::min(L.gridLeft, L.width * 0.06f));
            edge = x < zone ? -1 : x >= L.width - zone ? 1 : 0;
        } else {
            edge = y < L.viewTop ? -1 : y >= L.viewBottom ? 1 : 0;
        }
    }
    if (edge != g_drag.edge) {
        g_drag.edge = edge;
        g_drag.edgeTime = now;
    }
}

// Each frame of a drag: what happens when the pointer rests somewhere.
void DragTick() {
    // The page or rows under a still pointer move while scrolling.
    DragMove(g_drag.at.x, g_drag.at.y);
    double now = Now();
    if (g_drag.edge &&
        now - g_drag.edgeTime >= (g_settings.pages ? 0.6 : 0.3)) {
        g_drag.edgeTime = now;
        ScrollRows(g_drag.edge);
    }

    int t = g_drag.target;
    if (t >= 0 && t < (int)g_visible.size() && g_visible[t].folder &&
        now - g_drag.targetTime >= 0.7) {
        // Resting on a folder opens it, to place the app inside.
        std::shared_ptr<Folder> folder = g_visible[t].folder;
        int i = IndexOf(g_tiles, g_drag.tile);
        if (i >= 0) {
            g_tiles.erase(g_tiles.begin() + i);
        }
        folder->apps.push_back(g_drag.tile);
        UpdateFilter();
        ComputeLayout();
        OpenFolder(folder);
        FolderLayout F = GetFolderLayout();
        g_folderRow = F.rows - F.visibleRows;
        g_drag.target = g_drag.slot = -1;
        g_drag.edge = 0;
        g_drag.inPanel = false;
        return;
    }

    if (g_drag.slot >= 0 && now - g_drag.slotTime >= 0.2) {
        Tiles& tiles = g_openFolder ? g_openFolder->apps : g_tiles;
        int from = IndexOf(tiles, g_drag.tile);
        int to = std::min(g_drag.slot, (int)tiles.size() - 1);
        if (from >= 0 && to != from) {
            CaptureTileMotion();
            Tile tile = tiles[from];
            tiles.erase(tiles.begin() + from);
            tiles.insert(tiles.begin() + to, tile);
            if (!g_openFolder) {
                UpdateFilter();
                ComputeLayout();
            }
        }
    }
}

// drop: keep the new place (and make or fill a folder); otherwise everything
// goes back.
void EndDrag(bool drop) {
    g_drag.pending = false;
    if (!g_drag.active) {
        return;
    }
    CaptureTileMotion();
    if (drop) {
        for (auto& motion : g_tileMotion) {
            if (motion.key == MotionKey(g_drag.tile)) {
                float size = std::round(g_layout.icon * 1.06f);
                motion.from = {g_drag.at.x-g_drag.grab.x-(size-g_layout.icon)/2,
                               g_drag.at.y-g_drag.grab.y-(size-g_layout.icon)/2};
            }
        }
    }
    g_drag.active = false;
    Tile tile = std::move(g_drag.tile);
    g_drag.tile = {};
    int target = g_drag.target;
    g_drag.target = g_drag.slot = -1;
    g_drag.edge = 0;
    if (!drop) {
        g_openFolder = nullptr;
        ArrangeTiles(g_drag.backup);
    } else if (target >= 0 && target < (int)g_tiles.size()) {
        Tile onto = g_tiles[target];
        int from = IndexOf(g_tiles, tile);
        if (onto.folder) {
            onto.folder->apps.push_back(tile);
        } else {
            auto folder = std::make_shared<Folder>();
            folder->name = FolderName(onto.app->name, tile.app->name);
            folder->apps = {onto, tile};
            g_tiles[target] = {nullptr, folder};
        }
        if (from >= 0) {
            g_tiles.erase(g_tiles.begin() + from);
        }
    }
    g_drag.backup.clear();
    DropGoneFolder();
    if (drop) {
        SaveTiles();
    }
    Refresh();
}

// What an app's menu needs.
struct AppPaths {
    std::wstring file;      // The program it starts, when that's a file.
    std::wstring folder;    // A Store app's install folder.
    std::wstring shortcut;  // Its shortcut in the Start menu or on the desktop.
};

std::wstring ItemString(IShellItem2* item, PCWSTR property) {
    PROPERTYKEY key;
    PWSTR value = nullptr;
    std::wstring result;
    if (SUCCEEDED(PSGetPropertyKeyFromName(property, &key)) &&
        SUCCEEDED(item->GetString(key, &value))) {
        result = value;
        CoTaskMemFree(value);
    }
    return result;
}

bool FileExists(const std::wstring& path) {
    return !path.empty() &&
           GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}

// Start lists the shortcuts in these two folders and their subfolders. The
// one named like the app, or else the one that starts the same file.
std::wstring FindStartShortcut(const std::wstring& name,
                               const std::wstring& file) {
    std::vector<std::wstring> dirs, links;
    for (REFKNOWNFOLDERID id : {FOLDERID_Programs, FOLDERID_CommonPrograms}) {
        PWSTR root = nullptr;
        if (SUCCEEDED(SHGetKnownFolderPath(id, 0, nullptr, &root))) {
            dirs.push_back(root);
        }
        CoTaskMemFree(root);
    }
    while (!dirs.empty() && links.size() < 5000) {
        std::wstring dir = std::move(dirs.back());
        dirs.pop_back();
        WIN32_FIND_DATAW fd;
        HANDLE find = FindFirstFileW((dir + L"\\*").c_str(), &fd);
        if (find == INVALID_HANDLE_VALUE) {
            continue;
        }
        do {
            std::wstring path = dir + L"\\" + fd.cFileName;
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (fd.cFileName[0] != L'.' &&
                    !(fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) {
                    dirs.push_back(path);
                }
            } else if (EndsWith(ToLower(path), L".lnk")) {
                links.push_back(path);
            }
        } while (FindNextFileW(find, &fd));
        FindClose(find);
    }

    std::wstring wanted = L"\\" + ToLower(name) + L".lnk";
    for (const auto& link : links) {
        if (EndsWith(ToLower(link), wanted)) {
            return link;
        }
    }
    ComPtr<IShellLinkW> shellLink;
    ComPtr<IPersistFile> persist;
    if (file.empty() ||
        FAILED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER,
                                IID_PPV_ARGS(&shellLink))) ||
        FAILED(shellLink.As(&persist))) {
        return {};
    }
    std::wstring lowerFile = ToLower(file);
    for (const auto& link : links) {
        WCHAR target[MAX_PATH];
        if (SUCCEEDED(persist->Load(link.c_str(), STGM_READ)) &&
            shellLink->GetPath(target, ARRAYSIZE(target), nullptr, 0) == S_OK &&
            ToLower(target) == lowerFile) {
            return link;
        }
    }
    return {};
}

AppPaths GetAppPaths(const App& app) {
    AppPaths paths;
    std::wstring lower = ToLower(app.target);
    bool fromAppsFolder = lower.rfind(ToLower(kAppsFolder), 0) == 0;
    ComPtr<IShellItem2> item;
    if (SUCCEEDED(SHCreateItemFromParsingName(app.target.c_str(), nullptr,
                                              IID_PPV_ARGS(&item)))) {
        paths.file = ItemString(item.Get(), L"System.Link.TargetParsingPath");
        paths.folder =
            ItemString(item.Get(), L"System.AppUserModel.PackageInstallPath");
    }
    if (!fromAppsFolder) {
        if (EndsWith(lower, L".lnk")) {
            paths.shortcut = app.target;
        } else if (paths.file.empty()) {
            paths.file = app.target;
        }
    }
    // Control Panel and the like point to "::{...}", not a file.
    if (paths.file.rfind(L"::", 0) == 0 || !FileExists(paths.file)) {
        paths.file.clear();
    }
    if (paths.shortcut.empty() && fromAppsFolder && paths.folder.empty()) {
        paths.shortcut = FindStartShortcut(app.name, paths.file);
    }
    return paths;
}

void ShowInFolder(const std::wstring& path) {
    PIDLIST_ABSOLUTE pidl = nullptr;
    if (SUCCEEDED(SHParseDisplayName(path.c_str(), nullptr, &pidl, 0,
                                     nullptr))) {
        SHOpenFolderAndSelectItems(pidl, 0, nullptr, 0);
        CoTaskMemFree(pidl);
    }
}

bool PickIconFile(HWND hwnd, std::wstring& path) {
    WCHAR file[MAX_PATH] = L"";
    OPENFILENAMEW ofn{sizeof(ofn)};
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter =
        L"Pictures and icons\0*.ico;*.png;*.jpg;*.jpeg;*.bmp;*.gif;*.exe\0"
        L"All files\0*.*\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = ARRAYSIZE(file);
    ofn.lpstrTitle = L"Choose a picture for the icon";
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST |
                OFN_NOCHANGEDIR;
    g_modal = true;
    BOOL ok = GetOpenFileNameW(&ofn);
    g_modal = false;
    if (g_shown && !g_closing) {
        ForceForeground(hwnd);
    }
    if (ok) {
        path = file;
    }
    return ok;
}

// Takes the app off the grid: removed, or unpinned when only pinned apps show.
void RemoveApp(const std::shared_ptr<App>& app) {
    if (PinnedOnly()) {
        g_pins.erase(AppKey(*app));
        SavePins();
    } else {
        g_hidden.insert(AppKey(*app));
    }
    auto drop = [&](Tiles& tiles) {
        tiles.erase(std::remove_if(tiles.begin(), tiles.end(),
                                   [&](const Tile& t) { return t.app == app; }),
                    tiles.end());
    };
    drop(g_tiles);
    for (auto& tile : g_tiles) {
        if (tile.folder) {
            drop(tile.folder->apps);
        }
    }
    DropGoneFolder();
    SaveTiles();
    Refresh();
}

void TakeOutOfFolder(const Tile& tile) {
    if (!g_openFolder) {
        return;
    }
    Tiles& apps = g_openFolder->apps;
    int i = IndexOf(apps, tile);
    if (i < 0) {
        return;
    }
    apps.erase(apps.begin() + i);
    int f = IndexOf(g_tiles, {nullptr, g_openFolder});
    g_tiles.insert(g_tiles.begin() + (f + 1), tile);
    DropGoneFolder();
    SaveTiles();
    Refresh();
}

void Ungroup(const std::shared_ptr<Folder>& folder) {
    int f = IndexOf(g_tiles, {nullptr, folder});
    if (f < 0) {
        return;
    }
    Tiles apps = folder->apps;
    g_tiles.erase(g_tiles.begin() + f);
    g_tiles.insert(g_tiles.begin() + f, apps.begin(), apps.end());
    DropGoneFolder();
    SaveTiles();
    Refresh();
}

// An "&" in a menu would underline the next letter.
std::wstring MenuText(const std::wstring& text) {
    std::wstring out;
    for (WCHAR c : text) {
        if (c == L'&') {
            out += L'&';
        }
        out += c;
    }
    return out;
}

// Store apps and shell-resolved exes live behind an AppsFolder target; their
// elevation goes through a temporary .lnk, never the raw target.
bool IsPackagedTarget(const std::wstring& target) {
    return ToLower(target).rfind(ToLower(kAppsFolder), 0) == 0;
}

void ShowTileMenu(HWND hwnd, int index, POINT pt) {
    enum {
        kOpen = 1,
        kRunAs,
        kFileLocation,
        kShortcutLocation,
        kChangeIcon,
        kRestoreIcon,
        kOutOfFolder,
        kRemove,
        kProperties,
        kUngroup,
        kPin,
    };
    Tile tile = Items()[index];
    g_selected = index;
    Render();
    HMENU menu = CreatePopupMenu();
    AppPaths paths;
    std::wstring key;
    if (tile.folder) {
        AppendMenuW(menu, MF_STRING, kOpen, L"Open");
        AppendMenuW(menu, MF_STRING, kUngroup, L"Take the apps out");
    } else {
        paths = GetAppPaths(*tile.app);
        key = AppKey(*tile.app);
        AppendMenuW(menu, MF_STRING, kOpen, L"Open");
        // Anything with a launchable file can be elevated: a classic .exe,
        // any Start-menu shortcut, or a packaged app through a temporary
        // .lnk aimed at its AppsFolder target.
        if (!paths.shortcut.empty() || !paths.folder.empty() ||
            IsPackagedTarget(tile.app->target) ||
            (!paths.file.empty() && EndsWith(ToLower(paths.file), L".exe"))) {
            AppendMenuW(menu, MF_STRING, kRunAs, L"Run as administrator");
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu,
                    MF_STRING | (paths.file.empty() && paths.folder.empty()
                                     ? MF_GRAYED
                                     : 0),
                    kFileLocation, L"Open file location");
        AppendMenuW(menu, MF_STRING | (paths.shortcut.empty() ? MF_GRAYED : 0),
                    kShortcutLocation, L"Open shortcut location");
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu, MF_STRING, kChangeIcon, L"Change icon\u2026");
        if (g_customIcons.count(key)) {
            AppendMenuW(menu, MF_STRING, kRestoreIcon,
                        L"Restore original icon");
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        if (g_openFolder) {
            AppendMenuW(menu, MF_STRING, kOutOfFolder, L"Take out of folder");
        }
        if (!PinnedOnly()) {
            AppendMenuW(menu, MF_STRING, kRemove, L"Remove from this grid");
        } else if (g_pins.count(key)) {
            AppendMenuW(menu, MF_STRING, kRemove, L"Unpin from this grid");
        } else {
            AppendMenuW(menu, MF_STRING, kPin, L"Pin to this grid");
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu,
                    MF_STRING | (paths.shortcut.empty() && paths.file.empty()
                                     ? MF_GRAYED
                                     : 0),
                    kProperties, L"Properties");
    }
    SetMenuDefaultItem(menu, kOpen, FALSE);
    g_modal = true;
    int command = TrackPopupMenuEx(
        menu, TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_NONOTIFY, pt.x, pt.y, hwnd,
        nullptr);
    g_modal = false;
    DestroyMenu(menu);

    int size = g_appsKey & 0xFFFF;
    const std::wstring& linkOrFile =
        paths.shortcut.empty() ? paths.file : paths.shortcut;
    switch (command) {
        case kOpen:
            if (tile.folder) {
                OpenFolder(tile.folder);
            } else {
                LaunchTarget(tile.app->target);
            }
            break;
        case kUngroup:
            Ungroup(tile.folder);
            break;
        case kRunAs:
            // A Store app's .lnk brokers an elevated launch; the raw
            // AppsFolder target — with or without a real exe inside it — is
            // a silent no-op. Packaged apps go through the temporary .lnk.
            if (IsPackagedTarget(tile.app->target)) {
                ElevateViaTempLnk(tile.app->target);
            } else {
                LaunchTarget(linkOrFile, L"runas");
            }
            break;
        case kFileLocation:
            if (paths.file.empty()) {
                LaunchTarget(paths.folder);
            } else {
                Close();
                ShowInFolder(paths.file);
            }
            break;
        case kShortcutLocation:
            Close();
            ShowInFolder(paths.shortcut);
            break;
        case kChangeIcon: {
            std::wstring picture;
            if (PickIconFile(hwnd, picture)) {
                if (LoadIconFile(picture, size, *tile.app)) {
                    g_customIcons[key] = picture;
                    SaveCustomIcons();
                } else {
                    Wh_Log(L"No picture in %s", picture.c_str());
                }
            }
            Render();
            break;
        }
        case kRestoreIcon:
            g_customIcons.erase(key);
            SaveCustomIcons();
            ReloadAppIcon(size, *tile.app);
            Render();
            break;
        case kOutOfFolder:
            TakeOutOfFolder(tile);
            break;
        case kRemove:
            RemoveApp(tile.app);
            break;
        case kPin:
            g_pins.insert(key);
            SavePins();
            g_hidden.erase(key);
            g_tiles.push_back(tile);  // At the end of the grid.
            SaveTiles();
            Refresh();
            break;
        case kProperties:
            Close();
            SHObjectProperties(nullptr, SHOP_FILEPATH, linkOrFile.c_str(),
                               nullptr);
            break;
    }
}

// The menu key: the menu of the selected icon.
void ShowSelectedMenu() {
    if (g_drag.active || g_selected < 0 || g_selected >= (int)Items().size()) {
        return;
    }
    Cell c = ItemCell(g_selected);
    POINT pt{(LONG)c.icon.left, (LONG)c.icon.bottom};
    ClientToScreen(g_wnd, &pt);
    ShowTileMenu(g_wnd, g_selected, pt);
}

// The "..." menu, below the button, or at the pointer after a right-click on
// empty space.
void ShowOptionsMenu(HWND hwnd, POINT pt, bool underButton) {
    enum { kOpenSettings = 1, kRestoreAll, kSort, kRestoreFirst = 100 };
    // Removed apps that are still installed, A to Z like the list.
    std::vector<std::shared_ptr<App>> removed;
    for (const auto& app : g_apps) {
        if (g_hidden.count(AppKey(*app)) && removed.size() < 500) {
            removed.push_back(app);
        }
    }
    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, kOpenSettings, L"Open settings");
    HMENU sub = CreatePopupMenu();
    for (int i = 0; i < (int)removed.size(); i++) {
        AppendMenuW(sub, MF_STRING, kRestoreFirst + i,
                    MenuText(removed[i]->name).c_str());
    }
    if (!removed.empty()) {
        AppendMenuW(sub, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(sub, MF_STRING, kRestoreAll, L"Bring them all back");
    }
    AppendMenuW(menu, MF_POPUP | (removed.empty() ? MF_GRAYED : 0),
                (UINT_PTR)sub, L"Bring back a removed app");
    AppendMenuW(menu,
                MF_STRING | (!g_appsLoaded ? MF_GRAYED : 0),
                kSort, L"Sort A to Z");
    UINT flags = TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_NONOTIFY |
                 (underButton ? TPM_RIGHTALIGN | TPM_TOPALIGN : 0);
    g_modal = true;
    int command = TrackPopupMenuEx(menu, flags, pt.x, pt.y, hwnd, nullptr);
    g_modal = false;
    DestroyMenu(menu);

    if (command == kOpenSettings) {
        HideNow();
        OpenSettingsWindow();
    } else if (command == kRestoreAll ||
               (command >= kRestoreFirst &&
                command < kRestoreFirst + (int)removed.size())) {
        if (command == kRestoreAll) {
            for (const auto& app : removed) {
                g_hidden.erase(AppKey(*app));
            }
        } else {
            g_hidden.erase(AppKey(*removed[command - kRestoreFirst]));
        }
        ArrangeTiles(ArrangementLines());  // They come back at the end.
        DropGoneFolder();
        SaveTiles();
        Refresh();
    } else if (command == kSort) {
        g_modal = true;
        int answer = MessageBoxW(
            hwnd,
            L"Put every app back in A to Z order and out of its folder? "
            L"Removed apps stay removed.",
            L"Sort A to Z", MB_OKCANCEL | MB_ICONQUESTION);
        g_modal = false;
        if (g_shown && !g_closing) {
            ForceForeground(hwnd);
        }
        if (answer == IDOK) {
            std::vector<std::wstring> lines;
            for (const auto& key : g_hidden) {
                lines.push_back(L"hidden\t" + key);
            }
            ArrangeTiles(lines);
            DropGoneFolder();
            g_scroll = g_scrollTarget = 0;
            SaveTiles();
            Refresh();
        }
    }
}

void QueryChanged() {
    UpdateFilter();
    g_hover = -1;
    g_selected = g_query.empty() || g_visible.empty() ? -1 : 0;
    g_scroll = g_scrollTarget = 0;
    ComputeLayout();
    StartFrames();  // The glow eases in as typing starts.
    Render();
}

void PasteText() {
    if (!OpenClipboard(g_wnd)) {
        return;
    }
    if (HANDLE data = GetClipboardData(CF_UNICODETEXT)) {
        if (auto* text = (PCWSTR)GlobalLock(data)) {
            std::wstring line = text;
            GlobalUnlock(data);
            line = line.substr(0, line.find_first_of(L"\r\n"));
            // Tabs would split the saved folder name; typed ones never get in.
            std::erase_if(line, [](WCHAR c) { return c < 32; });
            EditPush(0);
            InsertAtCaret(line);
            EditDone();
        }
    }
    CloseClipboard();
    EditChanged();
}

void OnChar(WCHAR ch) {
    if (g_openFolder && !g_folderRenaming) return;
    if (g_drag.active || g_drag.pending) {
        return;
    }
    switch (ch) {
        case 8: {  // Backspace: the selection, or a code point before the caret.
            size_t from, to;
            if (SearchSelection(&from, &to) || g_caret > 0) {
                EditPush(2);
                if (!DeleteSelection()) {
                    size_t prev = CaretStep(g_caret, -1);
                    EditText().erase(prev, g_caret - prev);
                    g_caret = g_anchor = prev;
                }
                EditChanged();
                EditDone();
            }
            TouchCaret();
            return;
        }
        case 0x7F: {  // Ctrl+Backspace: the word before the caret.
            size_t from, to;
            if (SearchSelection(&from, &to) || g_caret > 0) {
                EditPush(2);
                if (!DeleteSelection()) {
                    size_t start = WordStart(g_caret);
                    EditText().erase(start, g_caret - start);
                    g_caret = g_anchor = start;
                }
                EditChanged();
                EditDone();
            }
            TouchCaret();
            return;
        }
        case 0x01:  // Ctrl+A: select all.
            g_anchor = 0;
            g_caret = EditText().size();
            TouchCaret();
            Render();
            return;
        case 0x03:  // Ctrl+C
            CopySelection(false);
            return;
        case 0x18:  // Ctrl+X
            CopySelection(true);
            return;
        case 0x16:  // Ctrl+V
            PasteText();
            return;
        case 0x1A:  // Ctrl+Z: undo; Ctrl+Shift+Z: redo.
            if (GetKeyState(VK_SHIFT) < 0) {
                RedoEdit();
            } else {
                UndoEdit();
            }
            return;
        case 0x19:  // Ctrl+Y: redo.
            RedoEdit();
            return;
    }
    if (ch >= 32 && EditText().size() < MaxEditChars()) {
        EditPush(1);
        InsertAtCaret(std::wstring(1, ch));
        EditDone();
        EditChanged();
    }
}

void MoveSelection(int delta) {
    const Tiles& items = Items();
    if (items.empty()) {
        return;
    }
    int count = (int)items.size();
    if (g_selected < 0) {
        g_selected = 0;
    } else {
        int next = g_selected + delta;
        if (next >= 0 && next < count) {
            g_selected = next;
        } else if (delta > 0 && delta == Columns()) {
            g_selected = count - 1;  // Down on the last incomplete row.
        }
    }
    EnsureVisible(g_selected);
    Render();
    StartFrames();
}

void OnKeyDown(WPARAM key) {
    if (g_drag.active && key != VK_ESCAPE) return;
    if (g_openFolder && g_folderRenaming && (key == VK_RETURN || key == VK_ESCAPE)) {
        g_folderRenaming = false;
        g_searchDrag = false;
        g_anchor = g_caret;
        SaveTiles();
        Render();
        return;
    }
    if (g_openFolder && !g_folderRenaming) {
        switch (key) {
            case VK_LEFT: MoveSelection(-1); break;
            case VK_RIGHT: MoveSelection(1); break;
            case VK_UP: MoveSelection(-Columns()); break;
            case VK_DOWN: MoveSelection(Columns()); break;
            case VK_RETURN: if (g_selected >= 0) ActivateItem(g_selected); break;
            case VK_ESCAPE: break;
            case VK_APPS: ShowSelectedMenu(); break;
        }
        if (key != VK_ESCAPE) return;
    }
    if (g_drag.active && key != VK_ESCAPE) {
        return;
    }
    switch (key) {
        case VK_ESCAPE:
            if (g_drag.active) {
                EndDrag(false);
                ReleaseCapture();
            } else if (g_powerArmed >= 0) {
                DisarmPower();
                Render();
            } else if (g_openFolder) {
                CloseFolder();
            } else if (!g_query.empty()) {
                EditPush(0);  // Ctrl+Z brings the cleared search back.
                g_query.clear();
                g_caret = g_anchor = 0;
                QueryChanged();
            } else {
                Close();
            }
            break;
        case VK_RETURN:
            if (g_selected >= 0) {
                ActivateItem(g_selected);
            } else if (!g_query.empty() && !g_visible.empty()) {
                ActivateItem(0);
            }
            break;
        case VK_APPS:
            ShowSelectedMenu();
            break;
        case VK_LEFT:
            if (!EditText().empty()) {
                bool word = GetKeyState(VK_CONTROL) < 0;
                SetCaret(word ? WordStart(g_caret) : CaretStep(g_caret, -1),
                         GetKeyState(VK_SHIFT) < 0);
                Render();
            } else {
                MoveSelection(-1);
            }
            break;
        case VK_RIGHT:
            if (!EditText().empty()) {
                bool word = GetKeyState(VK_CONTROL) < 0;
                SetCaret(word ? WordEnd(g_caret) : CaretStep(g_caret, 1),
                         GetKeyState(VK_SHIFT) < 0);
                Render();
            } else {
                MoveSelection(1);
            }
            break;
        case VK_UP:
            MoveSelection(-Columns());
            break;
        case VK_DOWN:
            MoveSelection(Columns());
            break;
        case VK_PRIOR:
            if (!g_openFolder) {
                ScrollRows(-g_layout.visibleRows);
            }
            break;
        case VK_NEXT:
            if (!g_openFolder) {
                ScrollRows(g_layout.visibleRows);
            }
            break;
        case VK_HOME:
            if (!EditText().empty()) {
                SetCaret(0, GetKeyState(VK_SHIFT) < 0);
                Render();
            }
            break;
        case VK_END:
            if (!EditText().empty()) {
                SetCaret(EditText().size(), GetKeyState(VK_SHIFT) < 0);
                Render();
            }
            break;
        case VK_DELETE:
            if (!EditText().empty()) {
                size_t dfrom, dto;
                if (SearchSelection(&dfrom, &dto) || g_caret < EditText().size()) {
                    EditPush(2);
                    bool changed = DeleteSelection();
                    if (!changed) {
                        size_t next = CaretStep(g_caret, 1);
                        if (next != g_caret) {
                            EditText().erase(g_caret, next - g_caret);
                            changed = true;
                        }
                    }
                    if (changed) {
                        EditChanged();
                        EditDone();
                    }
                }
                TouchCaret();
            }
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Opening instead of the Windows Start
//
// Every way of opening Start (Windows key, Ctrl+Esc, the taskbar's Start
// button, WM_SYSCOMMAND/SC_TASKLIST from the Dock) goes through
// XamlLauncher::ShowStartView in twinui.pcshell.dll. The hook asks the mod's
// window to toggle and doesn't call the original, so the Windows Start never
// opens.

// Observed on Windows 11 build 26300: the Windows key and Ctrl+Esc arrive as
// method 1 with flag 8; WM_SYSCOMMAND/SC_TASKLIST (the Dock's Start button)
// also arrives as method 1, without that flag.
constexpr int kShowMethodKeyboard = 1;
constexpr int kShowFlagKeyboard = 0x8;

bool IsKeyboardShow(int showMethod, int showFlags) {
    return showMethod == kShowMethodKeyboard && (showFlags & kShowFlagKeyboard);
}

// Shift + Windows key
//
// Windows doesn't open Start for the Windows key pressed with Shift, so
// ShowStartView never sees it. A low-level keyboard hook on its own thread
// (the window thread can be busy drawing) watches for a Windows key press
// with Shift down during it, and no other key pressed in between (Shift+Win+S and
// the like stay Windows shortcuts). For the grid and the original Start, the
// window presses Ctrl+Esc once the keys are up, and the ShowStartView hook
// gives that one the Shift + Windows key action.
//
// Windows keeps keys typed in an administrator window from this hook, and
// drops the Ctrl+Esc it would press there. The optional helper
// (helper/launchpad-keys.cpp) runs as administrator with the same hook. While its
// window exists, this hook leaves the key to it, and the helper sends
// WM_APP_SHIFT_WIN with wParam 1, then presses Ctrl+Esc itself if the answer
// is 1.
constexpr WCHAR kHelperClass[] = L"SeamlessLaunchpadKeys";

std::atomic<ULONGLONG> g_shiftWinUntil;
HANDLE g_keyThread;
DWORD g_keyThreadId;

LRESULT CALLBACK KeyboardHook(int code, WPARAM wParam, LPARAM lParam) {
    // Keyboards that send Shift+Win from one key (macro keys) let go of Shift
    // a moment before Win, so Shift counts if it was down at any point.
    static bool winDown, otherKey, withShift;
    if (code == HC_ACTION) {
        DWORD vk = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
        bool up = wParam == WM_KEYUP || wParam == WM_SYSKEYUP;
        bool shift = vk == VK_SHIFT || vk == VK_LSHIFT || vk == VK_RSHIFT;
        if (vk == VK_LWIN || vk == VK_RWIN) {
            if (!up && !winDown) {
                winDown = true;
                otherKey = false;
                withShift = GetAsyncKeyState(VK_SHIFT) < 0;
            } else if (up && winDown) {
                winDown = false;
                HWND wnd = g_wnd;
                if (!otherKey && withShift && wnd &&
                    !FindWindowW(kHelperClass, nullptr)) {
                    PostMessageW(wnd, WM_APP_SHIFT_WIN, 0, 0);
                }
            }
        } else if (shift && !up && winDown) {
            withShift = true;
        } else if (!up && !shift && winDown) {
            otherKey = true;
        }
    }
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

DWORD WINAPI KeyThread(void*) {
    HHOOK hook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardHook,
                                   GetModuleHandleW(nullptr), 0);
    if (!hook) {
        Wh_Log(L"Keyboard hook failed: %u", GetLastError());
        return 0;
    }
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    }
    UnhookWindowsHookEx(hook);
    return 0;
}

bool OwnsTaskbar() {
    DWORD pid = 0;
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    return tray && GetWindowThreadProcessId(tray, &pid) &&
           pid == GetCurrentProcessId();
}

using XamlLauncher_ShowStartView_t = HRESULT(WINAPI*)(void* pThis,
                                                      int showMethod,
                                                      int showFlags);
XamlLauncher_ShowStartView_t XamlLauncher_ShowStartView_Original;
HRESULT WINAPI XamlLauncher_ShowStartView_Hook(void* pThis,
                                               int showMethod,
                                               int showFlags) {
    Wh_Log(L"> method %d, flags %d", showMethod, showFlags);
    KeyAction action = GetTickCount64() < g_shiftWinUntil
                           ? g_shiftWinKeyAction.load()
                       : IsKeyboardShow(showMethod, showFlags)
                           ? g_winKeyAction.load()
                           : g_startButtonAction.load();
    g_shiftWinUntil = 0;
    HWND wnd = g_wnd;
    if (action == KeyAction::Start || !wnd) {
        return XamlLauncher_ShowStartView_Original(pThis, showMethod,
                                                   showFlags);
    }
    PostMessageW(wnd, action == KeyAction::Program ? WM_APP_RUN
                                                   : WM_APP_TOGGLE,
                 0, 0);
    return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
// Windows


void OnAppsLoaded(AppList* list, int key) {
    if (g_drag.active || g_modal) {
        // Not under a dragged icon or an open menu: read again on the next
        // open.
        delete list;
        g_appsTime = 0;
        return;
    }
    if (g_openFolder) {
        SaveTiles();  // A name being typed.
        g_openFolder = nullptr;
    }
    g_apps = list ? std::move(*list) : AppList{};
    delete list;
    g_appsLoaded = true;
    g_appsKey = key;
    LoadTiles();
    ApplyCustomIcons(key & 0xFFFF);
    if (key != AppsKey()) {
        // The settings changed while this list was read: the reload then
        // found the worker busy. It has posted and is about to end.
        WaitForSingleObject(g_worker, 1000);
        StartLoadingApps();
    }
    if (g_shown) {
        UpdateFilter();
        int count = (int)g_visible.size();
        if (g_selected >= count) {
            g_selected = count ? 0 : -1;
        }
        g_hover = g_pressed = -1;
        ComputeLayout();
        Render();
    }
}

// The tray icon (Look > Tray icon): click opens the settings, right-click shows a menu.
// It lives on the grid's window and thread, like the rest of Launchpad.
constexpr UINT WM_APP_TRAY = WM_APP + 21;
constexpr UINT kTrayId = 1;
static HICON g_trayIcon;
static bool g_trayShown;
static UINT g_taskbarCreated;

// A blue to mauve rounded square with a 3 by 3 grid of dots, drawn per pixel so no
// resource file is needed.
static HICON MakeTrayIcon(int size) {
    BITMAPV5HEADER bi{};
    bi.bV5Size = sizeof(bi); bi.bV5Width = size; bi.bV5Height = -size; bi.bV5Planes = 1;
    bi.bV5BitCount = 32; bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask = 0x00FF0000; bi.bV5GreenMask = 0x0000FF00; bi.bV5BlueMask = 0x000000FF; bi.bV5AlphaMask = 0xFF000000;
    void* bits = nullptr;
    HDC dc = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, dc);
    if (!color) return nullptr;
    auto px = (UINT32*)bits;
    const float n = (float)size, rad = n * 0.26f, ss = 4;
    auto inRound = [&](float x, float y) {
        float cx = std::clamp(x, rad, n - rad), cy = std::clamp(y, rad, n - rad);
        return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= rad * rad;
    };
    auto inDot = [&](float x, float y) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                float cx = n * (0.3f + 0.2f * i), cy = n * (0.3f + 0.2f * j), r = n * 0.065f;
                if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r) return true;
            }
        return false;
    };
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float cover = 0, dot = 0;
            for (int sy = 0; sy < ss; sy++)
                for (int sx = 0; sx < ss; sx++) {
                    float fx = x + (sx + 0.5f) / ss, fy = y + (sy + 0.5f) / ss;
                    if (inRound(fx, fy)) { cover++; if (inDot(fx, fy)) dot++; }
                }
            cover /= ss * ss; dot /= ss * ss;
            float t = std::clamp((x + y) / (2.0f * n), 0.0f, 1.0f);
            // 0x89B4FA to 0xCBA6F7, with the dots in crust (0x11111B).
            float r = (0x89 + (0xCB - 0x89) * t), g = (0xB4 + (0xA6 - 0xB4) * t), b = (0xFA + (0xF7 - 0xFA) * t);
            float k = cover > 0 ? dot / cover : 0;
            r = r * (1 - k) + 0x11 * k; g = g * (1 - k) + 0x11 * k; b = b * (1 - k) + 0x1B * k;
            BYTE a = (BYTE)(cover * 255 + 0.5f);
            px[y * size + x] = ((UINT32)a << 24) | ((UINT32)(r * cover) << 16) | ((UINT32)(g * cover) << 8) | (UINT32)(b * cover);
        }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

static void UpdateTrayIcon(HWND hwnd) {
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = hwnd;
    nid.uID = kTrayId;
    if (!g_settings.trayIcon) {
        if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayShown = false;
        return;
    }
    if (!g_trayIcon) g_trayIcon = MakeTrayIcon(GetSystemMetricsForDpi(SM_CXSMICON, GetDpiForSystem()));
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_APP_TRAY;
    nid.hIcon = g_trayIcon;
    wcscpy_s(nid.szTip, L"Seamless Launchpad");
    if (g_trayShown && Shell_NotifyIconW(NIM_MODIFY, &nid)) return;
    g_trayShown = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
    if (g_trayShown) {
        nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nid);
    }
}

static void RemoveTrayIcon(HWND hwnd) {
    if (g_trayShown) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = hwnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayShown = false;
    }
    if (g_trayIcon) {
        DestroyIcon(g_trayIcon);
        g_trayIcon = nullptr;
    }
}

static void OnTrayMessage(HWND hwnd, LPARAM lParam) {
    switch (LOWORD(lParam)) {
        case NIN_SELECT:
        case NIN_KEYSELECT:
            OpenSettingsWindow();
            break;
        case WM_CONTEXTMENU: {
            HMENU menu = CreatePopupMenu();
            AppendMenuW(menu, MF_STRING, 1, L"Settings");
            AppendMenuW(menu, MF_STRING, 2, L"Open Launchpad");
            SetMenuDefaultItem(menu, 1, FALSE);
            POINT pt;
            GetCursorPos(&pt);
            SetForegroundWindow(hwnd);
            int cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON, pt.x, pt.y, hwnd, nullptr);
            DestroyMenu(menu);
            if (cmd == 1) OpenSettingsWindow();
            if (cmd == 2) PostMessageW(hwnd, WM_APP_TOGGLE, 0, 0);
            break;
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        g_trayShown = false;  // The new taskbar has no icons yet.
        UpdateTrayIcon(hwnd);
        return 0;
    }
    switch (msg) {
        case WM_APP + 20: OpenSettingsWindow(); return 0;
        case WM_APP_TRAY: OnTrayMessage(hwnd, lParam); return 0;
        case WM_APP_TOGGLE:
            // Clicking the taskbar's Start button while this one is open first
            // takes the focus (which closes it) and then asks for Start: that
            // click was meant to close it.
            if ((!g_shown || g_closing) && Now() - g_lastClosed < 0.5) {
                return 0;
            }
            Toggle();
            return 0;

        case WM_APP_APPS:
            OnAppsLoaded((AppList*)lParam, (int)wParam);
            return 0;

        case WM_APP_RELOAD:
            LoadSettings();
            UpdateTrayIcon(hwnd);
            if (g_shown) {
                HideNow();
            }
            if (g_appsKey != AppsKey()) {
                StartLoadingApps();
            }
            return 0;

        case WM_APP_RUN:
            if (g_shown) {
                HideNow();
            }
            RunProgram();
            return 0;

        case WM_APP_SHIFT_WIN:
            // Explorer runs this mod in each of its processes; only the
            // taskbar's one answers the key.
            if (!OwnsTaskbar()) {
                return 0;
            }
            if (g_shiftWinKeyAction == KeyAction::Program) {
                PostMessageW(hwnd, WM_APP_RUN, 0, 0);
                return 0;
            }
            if (g_shown && g_shiftWinKeyAction == KeyAction::Start) {
                HideNow();
            }
            if (wParam == 1) {
                // The helper presses Ctrl+Esc once the keys are up.
                g_shiftWinUntil = GetTickCount64() + 3000;
                return 1;
            }
            // The grid and the original Start open through Ctrl+Esc, once
            // Shift is up (with Shift it's Task Manager): only a Start that
            // Windows opens may take the foreground. SC_TASKLIST to the
            // taskbar does nothing here.
            SetTimer(hwnd, kTimerShiftWin, 20, nullptr);
            return 0;

        case WM_APP_QUIT:
            RemoveTrayIcon(hwnd);
            DestroyWindow(hwnd);
            return 0;

        case WM_TIMER:
            switch (wParam) {
                case kTimerFrame:
                    OnFrame();
                    break;
                case kTimerShiftWin:
                    if (GetAsyncKeyState(VK_SHIFT) >= 0 &&
                        GetAsyncKeyState(VK_LWIN) >= 0 &&
                        GetAsyncKeyState(VK_RWIN) >= 0) {
                        KillTimer(hwnd, kTimerShiftWin);
                        g_shiftWinUntil = GetTickCount64() + 1000;
                        INPUT keys[4] = {};
                        WORD vks[4] = {VK_CONTROL, VK_ESCAPE, VK_ESCAPE,
                                       VK_CONTROL};
                        for (int i = 0; i < 4; i++) {
                            keys[i].type = INPUT_KEYBOARD;
                            keys[i].ki.wVk = vks[i];
                            keys[i].ki.dwFlags = i < 2 ? 0 : KEYEVENTF_KEYUP;
                        }
                        SendInput(4, keys, sizeof(INPUT));
                    }
                    break;
                case kTimerPowerArm:
                    DisarmPower();
                    Render();
                    break;
                case kTimerCaret:
                    // The search caret blinks by plain redraws.
                    if (g_shown && (!g_openFolder || g_folderRenaming)) {
                        Render();
                    }
                    break;
                case kTimerFirstLoad:
                    // Only in the process that owns the taskbar: short-lived
                    // explorer.exe processes (explorer.exe /select,...) get
                    // the mod too, and exit before they'd need the list.
                    if (OwnsTaskbar()) {
                        KillTimer(hwnd, kTimerFirstLoad);
                        if (!g_appsLoaded) {
                            StartLoadingApps();
                        }
                    }
                    break;
            }
            return 0;

        case WM_ACTIVATE:
            if (LOWORD(wParam) == WA_INACTIVE && g_shown && !g_closing &&
                !g_modal) {
                g_lastClosed = Now();
                Close();
            }
            return 0;

        case WM_MOUSEMOVE: {
            if (!g_trackingMouse) {
                TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
                g_trackingMouse = TrackMouseEvent(&tme);
            }
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            if (g_searchDrag) {
                SetCaret(CaretAtPoint((float)x), true);
                Render();
                return 0;
            }
            // A drag is real past the system drag threshold only.
            if (g_drag.pending && !g_drag.active &&
                (std::abs(x - g_drag.start.x) >
                     GetSystemMetrics(SM_CXDRAG) ||
                 std::abs(y - g_drag.start.y) >
                     GetSystemMetrics(SM_CYDRAG))) {
                StartDrag();
            }
            if (g_drag.active) {
                DragMove(x, y);
                return 0;
            }
            bool titleHover = g_openFolder && InRect(FolderTitlePill(), (float)x, (float)y);
            if (titleHover != g_folderTitleHover) {
                g_folderTitleHover = titleHover;
                Render();
            }
            int hover = ItemAt(x, y);
            bool menuHover =
                !g_openFolder && InButton(g_layout.menuButton, (float)x, (float)y);
            bool clearHover = !g_openFolder && !g_query.empty() &&
                              InButton(g_layout.clearButton, (float)x, (float)y);
            bool searchHover = !g_openFolder && !menuHover && !clearHover &&
                               InRect(g_layout.search, (float)x, (float)y);
            int powerHover = g_openFolder ? -1 : PowerAt(x, y);
            if (hover != g_hover || menuHover != g_menuHover ||
                clearHover != g_clearHover ||
                searchHover != g_searchHover ||
                powerHover != g_powerHover) {
                g_hover = hover;
                g_menuHover = menuHover;
                g_clearHover = clearHover;
                g_searchHover = searchHover;
                g_powerHover = powerHover;
                StartFrames();  // The bar's glow eases between states.
                Render();
                StartFrames();
            }
            return 0;
        }

        case WM_MOUSELEAVE:
            g_folderTitleHover = false;
            g_trackingMouse = false;
            if (g_hover >= 0 || g_menuHover || g_clearHover || g_searchHover ||
                g_powerHover >= 0) {
                g_hover = -1;
                g_menuHover = false;
                g_clearHover = false;
                g_searchHover = false;
                g_powerHover = -1;
                StartFrames();
                Render();
                StartFrames();
            }
            return 0;

        case WM_LBUTTONDOWN: {
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            if (g_closing) {
                return 0;  // A click during the closing fade does nothing.
            }
            if (!g_openFolder) {
                int power = PowerAt(x, y);
                if (power >= 0) {
                    g_powerPressed = power;
                    SetCapture(hwnd);
                    Render();
                    return 0;
                }
                if (g_powerArmed >= 0) {
                    DisarmPower();  // A click elsewhere cancels the prompt.
                }
                if (InButton(g_layout.menuButton, (float)x, (float)y)) {
                    POINT pt{(LONG)g_layout.menuButton.right,
                             (LONG)g_layout.menuButton.bottom + 4};
                    ClientToScreen(hwnd, &pt);
                    ShowOptionsMenu(hwnd, pt, true);
                    return 0;
                }
                if (!g_query.empty() &&
                    InButton(g_layout.clearButton, (float)x, (float)y)) {
                    EditPush(0);  // Ctrl+Z brings the cleared search back.
                    g_query.clear();
                    g_caret = g_anchor = 0;
                    g_clearHover = false;
                    QueryChanged();
                    return 0;
                }
                int dot = PageDotAt(x, y);
                if (dot >= 0) {
                    g_scrollTarget = dot * (float)g_layout.width;
                    StartFrames();
                    return 0;
                }
            }
            bool editHit = InRect(g_openFolder ? FolderTitlePill() : EditBox(false), (float)x, (float)y);
            if (g_openFolder && g_folderRenaming && !editHit) {
                g_folderRenaming = false;
                SaveTiles();
            }
            if (editHit) {
                if (g_openFolder) g_folderRenaming = true;
                // A click in the search field, or in an open folder's name,
                // places the caret; holding the button and moving selects
                // text. A second click on the same spot selects the word.
                UINT64 tick = GetTickCount64();
                bool dbl = tick - g_lastSearchClick <=
                               GetDoubleClickTime() &&
                           std::abs(x - g_lastSearchX) <=
                               4 * g_layout.scale;
                g_lastSearchClick = tick;
                g_lastSearchX = x;
                if (dbl) {
                    size_t pos = CaretAtPoint((float)x);
                    g_anchor = WordStart(pos);
                    g_caret = WordEnd(pos);
                } else {
                    SetCaret(CaretAtPoint((float)x), false);
                }
                g_searchDrag = true;
                SetCapture(hwnd);
                Render();
                return 0;
            }
            if (g_anchor != g_caret) {
                g_anchor = g_caret;  // A click elsewhere drops the selection.
            }
            SetCapture(hwnd);
            g_pressed = ItemAt(x, y);
            g_pressedEmpty = g_pressed < 0 && !ClickKeepsOpen(x, y);
            g_drag.pending = g_pressed >= 0 && g_query.empty();
            g_drag.pressTime = Now();
            g_drag.start = {x, y};
            if (g_drag.pending) {
                StartFrames();  // Ticks the hold time toward the edit mode.
            }
            Render();
            return 0;
        }

        case WM_LBUTTONUP: {
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            g_searchDrag = false;
            bool dragged = g_drag.active;
            // ReleaseCapture fires WM_CAPTURECHANGED synchronously, and that
            // handler clears the press; snapshot it before the capture goes.
            int powerPressed = g_powerPressed;
            EndDrag(true);  // Before the capture goes, which would undo it.
            if (GetCapture() == hwnd) {
                ReleaseCapture();
            }
            g_powerPressed = -1;
            if (powerPressed >= 0) {
                if (PowerAt(x, y) == powerPressed) {
                    PowerClick(powerPressed);  // May hide the grid.
                }
                Render();
                return 0;
            }
            int pressed = g_pressed;
            bool pressedEmpty = g_pressedEmpty;
            g_pressed = -1;
            g_pressedEmpty = false;
            if (dragged) {
                return 0;
            }
            int item = ItemAt(x, y);
            if (pressed >= 0 && item == pressed) {
                ActivateItem(item);
            } else if (pressedEmpty && item < 0 && !ClickKeepsOpen(x, y)) {
                // Clicking on empty space closes, like in Launchpad.
                if (g_openFolder) {
                    CloseFolder();
                } else {
                    Close();
                }
            } else {
                Render();
            }
            return 0;
        }

        case WM_CAPTURECHANGED:
            EndDrag(false);  // Another window took the mouse.
            g_searchDrag = false;
            g_powerPressed = -1;
            return 0;

        case WM_RBUTTONUP: {
            if (g_drag.active) {
                return 0;
            }
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            POINT pt{x, y};
            ClientToScreen(hwnd, &pt);
            int item = ItemAt(x, y);
            if (item >= 0) {
                ShowTileMenu(hwnd, item, pt);
            } else if (!g_openFolder) {
                ShowOptionsMenu(hwnd, pt, false);
            }
            return 0;
        }

        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
            if (g_openFolder) {
                if (msg == WM_MOUSEWHEEL) {
                    g_wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
                    if (std::abs(g_wheelDelta) >= WHEEL_DELTA) {
                        FolderLayout F = GetFolderLayout();
                        g_folderRow =
                            std::clamp(g_folderRow - g_wheelDelta / WHEEL_DELTA,
                                       0, F.rows - F.visibleRows);
                        g_wheelDelta %= WHEEL_DELTA;
                        Render();
                    }
                }
                return 0;
            }
            // Sideways (tilt wheel, touchpad swipe) only flips pages.
            if (msg == WM_MOUSEHWHEEL && !g_settings.pages) {
                return 0;
            }
            g_wheelDelta += msg == WM_MOUSEWHEEL
                                ? GET_WHEEL_DELTA_WPARAM(wParam)
                                : -GET_WHEEL_DELTA_WPARAM(wParam);
            if (std::abs(g_wheelDelta) >= WHEEL_DELTA) {
                ScrollRows(-g_wheelDelta / WHEEL_DELTA);
                g_wheelDelta %= WHEEL_DELTA;
            }
            return 0;

        case WM_KEYDOWN:
            OnKeyDown(wParam);
            return 0;

        case WM_CHAR:
            OnChar((WCHAR)wParam);
            return 0;

        case WM_CLOSE:  // Alt+F4
            Close();
            return 0;

        case WM_DPICHANGED:
            return 0;  // Position and scaling are computed when opening.

        case WM_DISPLAYCHANGE:
        case WM_SETTINGCHANGE:
            if (g_shown && (msg == WM_DISPLAYCHANGE || wParam == SPI_SETWORKAREA)) {
                HideNow();
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK BackdropWndProc(HWND hwnd,
                                 UINT msg,
                                 WPARAM wParam,
                                 LPARAM lParam) {
    switch (msg) {
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_NCHITTEST:
            return HTTRANSPARENT;
        case WM_ERASEBKGND: {
            // Black with zero alpha: only the DWM effect shows.
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect((HDC)wParam, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
            return 1;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC dc = BeginPaint(hwnd, &ps);
            FillRect(dc, &ps.rcPaint, (HBRUSH)GetStockObject(BLACK_BRUSH));
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

HANDLE g_thread;
HANDLE g_readyEvent;

DWORD WINAPI StartThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    OleInitialize(nullptr);
    LoadSettings();
    MigrateOldStorage();  // Before the app loading reads the folder.

    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, g_d2d.GetAddressOf());
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                        (IUnknown**)g_dwrite.GetAddressOf());

    HINSTANCE instance = (HINSTANCE)&__ImageBase;
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kWindowClass;
    RegisterClassExW(&wc);

    WNDCLASSEXW bc{sizeof(bc)};
    bc.lpfnWndProc = BackdropWndProc;
    bc.hInstance = instance;
    bc.lpszClassName = kBackdropClass;
    RegisterClassExW(&bc);

    g_backdrop = CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE |
            WS_EX_TRANSPARENT,
        kBackdropClass, L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, instance,
        nullptr);
    HWND wnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED,
                               kWindowClass, L"Start", WS_POPUP, 0, 0, 0, 0,
                               nullptr, nullptr, instance, nullptr);
    bool ok = g_d2d && g_dwrite && g_backdrop && wnd;
    if (ok) {
        g_wnd = wnd;
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(wnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        UpdateTrayIcon(wnd);
        // The app list is read a bit later, so it doesn't weigh on explorer's
        // startup.
        SetTimer(wnd, kTimerFirstLoad, 3000, nullptr);
    }
    SetEvent(g_readyEvent);

    if (ok) {
        MSG msg;
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    } else {
        Wh_Log(L"Failed to create Start");
        if (wnd) {
            DestroyWindow(wnd);
        }
    }
    g_wnd = nullptr;

    g_workerStop = true;
    if (g_worker) {
        WaitForSingleObject(g_worker, INFINITE);
        CloseHandle(g_worker);
        g_worker = nullptr;
    }
    // A list delivered after the window stopped handling messages.
    MSG msg;
    while (PeekMessageW(&msg, nullptr, WM_APP_APPS, WM_APP_APPS, PM_REMOVE)) {
        delete (AppList*)msg.lParam;
    }

    if (g_backdrop) {
        DestroyWindow(g_backdrop);
        g_backdrop = nullptr;
    }
    AppList().swap(g_apps);  // Also frees the memory (no_destroy).
    Tiles().swap(g_tiles);
    Tiles().swap(g_visible);
    g_openFolder = nullptr;
    g_drag = {};
    g_backdropImage = {};
    g_panelBlur = {};
    FreeSurface(g_surface);
    g_labelFormat.Reset();
    g_searchFormat.Reset();
    g_messageFormat.Reset();
    g_iconFormat.Reset();
    g_tipFormat.Reset();
    ResetTarget();
    g_dwrite.Reset();
    g_d2d.Reset();
    UnregisterClassW(kWindowClass, instance);
    UnregisterClassW(kBackdropClass, instance);
    OleUninitialize();
    return 0;
}

// With "Launch folder windows in a separate process", folder windows run in
// their own explorer.exe, which never shows Start.
bool IsFolderWindowsProcess() {
    std::wstring commandLine = ToLower(GetCommandLineW());
    return commandLine.find(L"/factory") != std::wstring::npos ||
           commandLine.find(L"-embedding") != std::wstring::npos ||
           commandLine.find(L"/separate") != std::wstring::npos;
}

bool HookShowStartView() {
    HMODULE module = LoadLibraryExW(L"twinui.pcshell.dll", nullptr,
                                    LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!module) {
        Wh_Log(L"Couldn't load twinui.pcshell.dll");
        return false;
    }
    // twinui.pcshell.dll
    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {
            {LR"(public: virtual long __cdecl XamlLauncher::ShowStartView(enum IMMERSIVELAUNCHERSHOWMETHOD,enum IMMERSIVELAUNCHERSHOWFLAGS))"},
            &XamlLauncher_ShowStartView_Original,
            XamlLauncher_ShowStartView_Hook,
        },
    };
    if (!WindhawkUtils::HookSymbols(module, hooks, ARRAYSIZE(hooks))) {
        Wh_Log(L"HookSymbols failed");
        return false;
    }
    return true;
}

}  // namespace

BOOL Wh_ModInit() {
    Wh_Log(L">");

    if (IsFolderWindowsProcess()) {
        Wh_Log(L"Folder windows process; Start stays in the taskbar's one");
        return FALSE;
    }
    LoadSettings();
    if (!HookShowStartView()) {
        return FALSE;
    }
    g_readyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, StartThread, nullptr, 0, nullptr);
    if (!g_thread) {
        CloseHandle(g_readyEvent);
        g_readyEvent = nullptr;
        return FALSE;
    }
    g_keyThread =
        CreateThread(nullptr, 0, KeyThread, nullptr, 0, &g_keyThreadId);
    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L">");

    if (!g_thread) {
        CloseSettingsWindow();
        return;
    }
    if (g_keyThread) {
        // Repeated: the thread may not have its message queue yet.
        do {
            PostThreadMessageW(g_keyThreadId, WM_QUIT, 0, 0);
        } while (WaitForSingleObject(g_keyThread, 100) == WAIT_TIMEOUT);
        CloseHandle(g_keyThread);
        g_keyThread = nullptr;
    }
    WaitForSingleObject(g_readyEvent, INFINITE);
    if (HWND wnd = g_wnd) {
        PostMessageW(wnd, WM_APP_QUIT, 0, 0);
    }
    WaitForSingleObject(g_thread, INFINITE);
    CloseHandle(g_thread);
    g_thread = nullptr;
    CloseHandle(g_readyEvent);
    g_readyEvent = nullptr;
    // Last: until the grid's thread ends, its "..." menu can open the window.
    CloseSettingsWindow();
}

void Wh_ModSettingsChanged() {
    Wh_Log(L">");

    if (HWND wnd = g_wnd) {
        PostMessageW(wnd, WM_APP_RELOAD, 0, 0);
    }
    if (HWND wnd = g_settingsWnd) {
        PostMessageW(wnd, WM_APP_SETTINGS_RELOAD, 0, 0);
    }
}
