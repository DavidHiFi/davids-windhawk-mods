// ==WindhawkMod==
// @id              fullscreen-start-plus
// @name            Fullscreen Start Plus
// @description     A fullscreen grid of all your apps in place of Start, with instant search and adjustable blur
// @version         1.6.1
// @author          DavidHiFi, Rafael Mendes
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -lshell32 -lshcore -ldwmapi -ld2d1 -ldwrite -lole32 -luuid -lcomdlg32 -luxtheme -lpropsys
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Fullscreen Start Plus

Replaces the Start menu with a fullscreen grid of all your apps, in the style
of the macOS Launchpad, with instant search and a blurred background.

![Fullscreen Start Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/fullscreen-start-plus.png)

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
- **Adjustable blur.** Pick the blur type, strength, opacity and color of the
  background.
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
| Drag an icon | Move it. Hold it at the screen's edge to flip the page |
| Drop an app on another | Make a folder. Drop more apps on it to add them |
| Hold an app over a folder | The folder opens, so you can place it inside |
| Drag an app out of an open folder | Take it out of the folder |
| Type in an open folder | Rename it |
| Right-click an icon | Its menu. Right-click empty space for the ... menu |

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
- blurMode: custom
  $name: Blur type
  $options:
  - custom: Adjustable (uses the strength below)
  - acrylic: Windows acrylic (DWM)
  - blur: Windows blur (DWM)
  - none: No blur
- blurAmount: 60
  $name: Blur strength (0 to 100)
  $description: Only for the adjustable blur. The Windows one has a fixed strength
- backgroundOpacity: 30
  $name: Background color opacity (%)
  $description: 0 leaves only the blur; 100 covers everything with the color
- tintColor: "#000000"
  $name: Background color
  $description: In hexadecimal, like #1E1E2E
- appSource: allApps
  $name: Apps to show
  $description: With pinned apps, search still finds every app. Right-click an app to pin or unpin it
  $options:
  - allApps: Start menu apps (the All apps list)
  - desktop: Desktop icons
  - both: Start menu apps and desktop icons
  - pinned: Only the apps you pin
- gridIconSize: 72
  $name: Icon size (pixels at 100% scaling)
- gridColumns: 0
  $name: Grid columns
  $description: 0 picks based on the screen size
- gridLayout: scroll
  $name: Layout
  $options:
  - scroll: One list that scrolls up and down
  - pages: Pages that flip left and right, like Launchpad
- coverScreen: false
  $name: Cover the whole screen
  $description: Also covers the taskbar, side bars and the Standalone Dock. When off, they stay visible
- monitor: mouse
  $name: Monitor
  $description: Where Start opens. Monitors 2 to 4 are the others, counted from left to right. If the picked monitor isn't connected, it opens where the mouse is
  $options:
  - mouse: The monitor with the mouse
  - "1": Main monitor
  - "2": Monitor 2
  - "3": Monitor 3
  - "4": Monitor 4
- winKeyAction: grid
  $name: Windows key
  $description: Also Ctrl+Esc
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
  $description: Of the taskbar and of the Standalone Dock mod, and the other ways Start opens that aren't the keyboard
  $options:
  - grid: Open this grid
  - start: Open the original Start
  - program: Run the program below
- program: ""
  $name: Program
  $description: 'What "Run the program below" starts. A command line such as "C:\Program Files\App\app.exe" --flag, or a shortcut, file, folder or web address'
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
// Otherwise the Win32 macro renames ID2D1RenderTarget::DrawText.
#undef DrawText
#include <d2d1_1.h>
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

constexpr WCHAR kWindowClass[] = L"WindhawkFullscreenStartPlus";
constexpr WCHAR kBackdropClass[] = L"WindhawkFullscreenStartPlusBackdrop";
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
};

Settings g_settings;
// Also read in the ShowStartView hook, on Explorer's threads.
std::atomic<KeyAction> g_winKeyAction{KeyAction::Grid};
std::atomic<KeyAction> g_shiftWinKeyAction{KeyAction::Start};
std::atomic<KeyAction> g_startButtonAction{KeyAction::Grid};

std::wstring GetStringSetting(PCWSTR name) {
    return WindhawkUtils::StringSetting::make(name).get();
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

// Normalizes the alpha and enlarges small icons centered in a large image
// (old exes without a 256 px icon), otherwise they would look tiny.
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

    int left = width, top = height, right = -1, bottom = -1;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if ((pixels[y * width + x] >> 24) > 8) {
                left = std::min(left, x);
                right = std::max(right, x);
                top = std::min(top, y);
                bottom = std::max(bottom, y);
            }
        }
    }
    if (right < 0) {
        return;
    }
    int full = std::max(width, height);
    int content = std::max(right - left + 1, bottom - top + 1);
    int side, cx, cy;
    if (content < full * 0.6f) {
        side = std::min(full, (int)std::ceil(content * 1.08f));
        cx = (left + right + 1) / 2;
        cy = (top + bottom + 1) / 2;
    } else {
        side = full;
        cx = width / 2;
        cy = height / 2;
    }

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
    std::wstring path = std::wstring(temp) + L"fullscreen-start-plus-pins.json";
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
int AppsKey(int iconPixels, AppSource source) {
    return iconPixels | ((int)source << 16);
}

DWORD WINAPI LoadAppsThread(void* param) {
    int key = (int)(INT_PTR)param;
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    AppList* list = EnumerateApps(key & 0xFFFF, (AppSource)(key >> 16));
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
    return (g_appsKey >> 16) == (int)AppSource::Pinned;
}

// Not on the grid: removed, or not pinned when only pinned apps show.
bool OffGrid(const std::wstring& key) {
    return g_hidden.count(key) || (PinnedOnly() && !g_pins.count(key));
}

std::wstring AppKey(const App& app) {
    return ToLower(app.target);
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
    return std::wstring(L"layout-") + names[std::clamp(g_appsKey >> 16, 0, 3)] +
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
[[clang::no_destroy]] ComPtr<ID2D1DCRenderTarget> g_target;
[[clang::no_destroy]] ComPtr<ID2D1SolidColorBrush> g_brush;
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

bool EnsureTarget() {
    if (g_target) {
        return true;
    }
    auto props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                          D2D1_ALPHA_MODE_PREMULTIPLIED),
        96, 96);
    if (FAILED(g_d2d->CreateDCRenderTarget(&props, &g_target))) {
        return false;
    }
    g_target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    g_target->CreateSolidColorBrush(D2D1::ColorF(0, 0), &g_brush);
    g_targetGeneration++;
    return true;
}

void ResetTarget() {
    g_brush.Reset();
    g_target.Reset();
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
// Adjustable: a screenshot taken before the window appears, downscaled and
// blurred (three box blur passes, which approximate a gaussian blur) and
// stretched back with linear interpolation. Downscaling first makes a
// strong blur cheap.

struct Backdrop {
    std::vector<UINT32> pixels;
    int width = 0, height = 0;  // Downscaled size.
    float sourceWidth = 0, sourceHeight = 0;  // Part used, in downscaled pixels.
    ComPtr<ID2D1Bitmap> bitmap;
    UINT generation = 0;
};
[[clang::no_destroy]] Backdrop g_backdropImage;

void BoxBlurPass(const UINT32* src,
                 UINT32* dst,
                 int lines,
                 int length,
                 int lineStep,
                 int step,
                 int radius) {
    int window = 2 * radius + 1;
    for (int line = 0; line < lines; line++) {
        const UINT32* s = src + (size_t)line * lineStep;
        UINT32* d = dst + (size_t)line * lineStep;
        auto at = [&](int i) {
            return s[(size_t)std::clamp(i, 0, length - 1) * step];
        };
        int sum[3] = {};
        for (int i = -radius; i <= radius; i++) {
            UINT32 p = at(i);
            sum[0] += p & 0xFF;
            sum[1] += (p >> 8) & 0xFF;
            sum[2] += (p >> 16) & 0xFF;
        }
        for (int i = 0; i < length; i++) {
            d[(size_t)i * step] = 0xFF000000 | ((sum[2] / window) << 16) |
                                  ((sum[1] / window) << 8) | (sum[0] / window);
            UINT32 in = at(i + radius + 1), out = at(i - radius);
            sum[0] += (int)(in & 0xFF) - (int)(out & 0xFF);
            sum[1] += (int)((in >> 8) & 0xFF) - (int)((out >> 8) & 0xFF);
            sum[2] += (int)((in >> 16) & 0xFF) - (int)((out >> 16) & 0xFF);
        }
    }
}

void CaptureBackdrop(const RECT& rc, float sigma) {
    g_backdropImage = {};
    int width = rc.right - rc.left, height = rc.bottom - rc.top;
    if (width <= 0 || height <= 0) {
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
    ReleaseDC(nullptr, screen);

    // Downscale by averaging f x f blocks.
    int f = sigma >= 3 ? std::clamp((int)(sigma / 3), 1, 16) : 1;
    int sw = (width + f - 1) / f, sh = (height + f - 1) / f;
    std::vector<UINT32> small((size_t)sw * sh);
    const UINT32* full = (const UINT32*)bits;
    for (int y = 0; y < sh; y++) {
        for (int x = 0; x < sw; x++) {
            int sum[3] = {}, count = 0;
            for (int yy = y * f; yy < std::min(height, (y + 1) * f); yy++) {
                for (int xx = x * f; xx < std::min(width, (x + 1) * f); xx++) {
                    UINT32 p = full[(size_t)yy * width + xx];
                    sum[0] += p & 0xFF;
                    sum[1] += (p >> 8) & 0xFF;
                    sum[2] += (p >> 16) & 0xFF;
                    count++;
                }
            }
            small[(size_t)y * sw + x] = 0xFF000000 |
                                        ((sum[2] / count) << 16) |
                                        ((sum[1] / count) << 8) |
                                        (sum[0] / count);
        }
    }
    SelectObject(dc, old);
    DeleteObject(bitmap);
    DeleteDC(dc);

    // Three box blurs with this width add up to the desired deviation.
    float s = sigma / f;
    int radius = (int)std::lround((std::sqrt(4 * s * s + 1) - 1) / 2);
    if (radius > 0) {
        std::vector<UINT32> temp(small.size());
        for (int pass = 0; pass < 3; pass++) {
            BoxBlurPass(small.data(), temp.data(), sh, sw, sw, 1, radius);
            BoxBlurPass(temp.data(), small.data(), sw, sh, 1, sw, radius);
        }
    }

    g_backdropImage.pixels = std::move(small);
    g_backdropImage.width = sw;
    g_backdropImage.height = sh;
    g_backdropImage.sourceWidth = (float)width / f;
    g_backdropImage.sourceHeight = (float)height / f;
}

ID2D1Bitmap* GetBackdropBitmap() {
    Backdrop& b = g_backdropImage;
    if (b.pixels.empty()) {
        return nullptr;
    }
    if (b.generation != g_targetGeneration) {
        b.generation = g_targetGeneration;
        b.bitmap.Reset();
        g_target->CreateBitmap(
            D2D1::SizeU(b.width, b.height), b.pixels.data(), b.width * 4,
            D2D1::BitmapProperties(
                D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                                  D2D1_ALPHA_MODE_PREMULTIPLIED),
                96, 96),
            &b.bitmap);
    }
    return b.bitmap.Get();
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
    D2D1_RECT_F menuButton{};  // The "..." button, top right.
};

Layout g_layout;
// Pixels: down the list, or, with pages, across the row of pages.
float g_scroll, g_scrollTarget;
int g_wheelDelta;  // Wheel accumulated until it completes a row (touchpads).

[[clang::no_destroy]] ComPtr<IDWriteTextFormat> g_labelFormat, g_searchFormat,
    g_messageFormat;
float g_formatScale;

void EnsureFormats(float scale) {
    if (g_labelFormat && g_formatScale == scale) {
        return;
    }
    g_formatScale = scale;
    auto make = [&](float size, DWRITE_FONT_WEIGHT weight,
                    DWRITE_TEXT_ALIGNMENT align,
                    ComPtr<IDWriteTextFormat>& format) {
        format.Reset();
        g_dwrite->CreateTextFormat(L"Segoe UI Variable Text", nullptr, weight,
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
    float button = std::round(36 * s), margin = std::round(24 * s);
    L.menuButton = D2D1::RectF(W - margin - button, searchTop, W - margin,
                               searchTop + button);

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
    L.dotsY = std::round((L.viewBottom + H) / 2);

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
double g_lastFrame;
double g_lastClosed;  // When it closed by losing focus.
bool g_frameTimer;
int g_hover = -1, g_selected = -1, g_pressed = -1;
bool g_pressedEmpty;
bool g_trackingMouse;
bool g_menuHover;

// Dragging an icon: it keeps a place in the grid or folder, drawn empty, and
// moves to the place the pointer rests on.
struct Drag {
    bool pending = false;  // Pressed on an icon; a drag once it moves.
    bool active = false;
    POINT start{}, at{};
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
void DragTick();

float Ease(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return 1 - (1 - t) * (1 - t) * (1 - t);
}

void DrawMenuButton() {
    const D2D1_RECT_F& r = g_layout.menuButton;
    float s = g_layout.scale;
    if (g_menuHover) {
        Fill(r, D2D1::ColorF(1, 1, 1, 0.14f), (r.bottom - r.top) / 2);
    }
    float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    g_brush->SetColor(D2D1::ColorF(1, 1, 1, g_menuHover ? 0.95f : 0.75f));
    for (int i = -1; i <= 1; i++) {
        g_target->FillEllipse(
            D2D1::Ellipse(D2D1::Point2F(cx + i * 6 * s, cy), 1.8f * s, 1.8f * s),
            g_brush.Get());
    }
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
    *from = std::min(g_anchor, g_caret);
    *to = std::max(g_anchor, g_caret);
    return *from != *to;
}

size_t CaretStep(size_t pos, int dir) {
    const std::wstring& text = EditText();
    if (dir < 0) {
        pos = std::min(pos, text.size());
        if (pos >= 2 && IS_HIGH_SURROGATE(text[pos - 1]) &&
            IS_LOW_SURROGATE(text[pos - 2])) {
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

bool CaretVisible() {
    UINT blink = GetCaretBlinkTime();
    if (!blink || blink > 5000) {
        blink = 530;  // The Windows default.
    }
    return (GetTickCount64() - g_caretTick) / blink % 2 == 0;
}

void SetCaret(size_t pos, bool extend) {
    g_caret = std::min(pos, g_query.size());
    if (!extend) {
        g_anchor = g_caret;
    }
    TouchCaret();
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
    g_query.insert(g_caret, text);
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
        DeleteSelection();
        EditChanged();
    }
}

// The text layout the search box draws with, and how far the text is slid
// left so the caret stays in view. A null layout when there is no format.
ComPtr<IDWriteTextLayout> SearchLayout(float* shift) {
    *shift = 0;
    if (!g_searchFormat) {
        return nullptr;
    }
    const D2D1_RECT_F& r = g_layout.search;
    float s = g_layout.scale;
    D2D1_RECT_F text = D2D1::RectF(r.left + 34 * s, r.top, r.right - 14 * s,
                                   r.bottom);
    ComPtr<IDWriteTextLayout> layout;
    g_dwrite->CreateTextLayout(g_query.c_str(), (UINT32)g_query.size(),
                               g_searchFormat.Get(), 10000,
                               text.bottom - text.top, &layout);
    if (!layout) {
        return nullptr;
    }
    layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    DWRITE_TEXT_METRICS metrics{};
    layout->GetMetrics(&metrics);
    float room = text.right - text.left - 3 * s;
    float endShift =
        std::max(0.0f, metrics.widthIncludingTrailingWhitespace - room);
    float result = endShift;
    DWRITE_HIT_TEST_METRICS m{};
    float x = 0, y = 0;
    if (SUCCEEDED(layout->HitTestTextPosition(
            (UINT32)std::min(g_caret, g_query.size()), FALSE, &x, &y, &m))) {
        float caretX = (float)x;
        if (caretX - result < 0) {
            result = std::min(std::max(caretX, 0.0f), endShift);
        }
        if (caretX - result > room) {
            result = std::min(std::max(caretX - room, 0.0f), endShift);
        }
    }
    *shift = result;
    return layout;
}

// The caret index under a mouse x, in the search field's text area.
size_t CaretAtPoint(float x) {
    float shift = 0;
    auto layout = SearchLayout(&shift);
    if (!layout) {
        return g_query.size();
    }
    const D2D1_RECT_F& r = g_layout.search;
    float s = g_layout.scale;
    D2D1_RECT_F text = D2D1::RectF(r.left + 34 * s, r.top, r.right - 14 * s,
                                   r.bottom);
    BOOL trailing = FALSE, inside = FALSE;
    DWRITE_HIT_TEST_METRICS m{};
    float px = std::min(std::max(x - (text.left - shift), 0.0f),
                        text.right - text.left);
    if (FAILED(layout->HitTestPoint(px, (text.bottom - text.top) / 2, &trailing,
                                    &inside, &m))) {
        return g_query.size();
    }
    return std::min((size_t)(m.textPosition + (trailing ? m.length : 0)),
                    g_query.size());
}

void DrawSearchBox() {
    const Layout& L = g_layout;
    float s = L.scale;
    const D2D1_RECT_F& r = L.search;
    float radius = (r.bottom - r.top) / 2;
    Fill(r, D2D1::ColorF(1, 1, 1, 0.14f), radius);
    g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.22f));
    g_target->DrawRoundedRectangle(
        D2D1::RoundedRect(D2D1::RectF(r.left + 0.5f, r.top + 0.5f,
                                      r.right - 0.5f, r.bottom - 0.5f),
                          radius, radius),
        g_brush.Get(), 1);

    // Magnifying glass.
    float cx = r.left + 18 * s, cy = (r.top + r.bottom) / 2 - 1 * s;
    g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.75f));
    g_target->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 5.5f * s, 5.5f * s),
                          g_brush.Get(), 1.6f * s);
    g_target->DrawLine(D2D1::Point2F(cx + 4 * s, cy + 4 * s),
                       D2D1::Point2F(cx + 8.5f * s, cy + 8.5f * s),
                       g_brush.Get(), 1.6f * s);

    D2D1_RECT_F text = D2D1::RectF(r.left + 34 * s, r.top, r.right - 14 * s,
                                   r.bottom);
    if (!g_searchFormat) {
        return;
    }
    if (g_query.empty()) {
        g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.55f));
        g_target->DrawText(L"Search", 6, g_searchFormat.Get(), text,
                           g_brush.Get());
    }

    // The typed text, slid so the caret stays in view, with the selection
    // behind it and a caret that blinks like everywhere else in Windows.
    float shift = 0;
    ComPtr<IDWriteTextLayout> layout = SearchLayout(&shift);
    if (!layout) {
        return;
    }
    float originX = text.left - shift;
    g_target->PushAxisAlignedClip(text, D2D1_ANTIALIAS_MODE_ALIASED);
    size_t selFrom, selTo;
    if (SearchSelection(&selFrom, &selTo)) {
        DWRITE_HIT_TEST_METRICS rects[8];
        UINT32 count = 0;
        if (SUCCEEDED(layout->HitTestTextRange((UINT32)selFrom,
                                               (UINT32)(selTo - selFrom), 0, 0,
                                               rects, 8, &count))) {
            g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.28f));
            for (UINT32 i = 0; i < count && i < 8; i++) {
                g_target->FillRectangle(
                    D2D1::RectF(originX + rects[i].left,
                                text.top + rects[i].top,
                                originX + rects[i].left + rects[i].width,
                                text.top + rects[i].top + rects[i].height),
                    g_brush.Get());
            }
        }
    }
    g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.95f));
    g_target->DrawTextLayout(D2D1::Point2F(originX, text.top), layout.Get(),
                             g_brush.Get());
    if (CaretVisible()) {
        DWRITE_HIT_TEST_METRICS m{};
        float x = 0, y = 0;
        layout->HitTestTextPosition(
            (UINT32)std::min(g_caret, g_query.size()), FALSE, &x, &y, &m);
        float caretX = std::round(originX + (float)x) + 1;
        float caretH = 18 * s;
        float mid = (text.top + text.bottom) / 2;
        Fill(D2D1::RectF(caretX, mid - caretH / 2, caretX + std::max(1.0f, s),
                         mid + caretH / 2),
             D2D1::ColorF(1, 1, 1, 0.9f));
    }
    g_target->PopAxisAlignedClip();
}

void DrawMessage(PCWSTR text) {
    const Layout& L = g_layout;
    if (!g_messageFormat) {
        return;
    }
    g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.7f));
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
        Fill(r, D2D1::ColorF(1, 1, 1, 0.16f * opacity), side * 0.22f);
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
    if (ID2D1Bitmap* bitmap = GetBitmap(*tile.app)) {
        g_target->DrawBitmap(bitmap, r, opacity,
                             D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    } else {
        Fill(r, D2D1::ColorF(1, 1, 1, 0.12f * opacity), 14 * g_layout.scale);
    }
}

// live: the icon takes the pointer and keys (not the grid behind a folder).
void DrawTile(const Tile& tile, const Cell& c, int i, bool live) {
    if (IsDragged(tile)) {
        return;  // Its place stays empty; the icon follows the pointer.
    }
    float s = g_layout.scale;
    if (live && (i == g_selected || i == g_hover)) {
        Fill(c.highlight,
             D2D1::ColorF(1, 1, 1, i == g_selected ? 0.18f : 0.10f), 12 * s);
    }
    if (live && i == g_drag.target) {
        float grow = 8 * s;
        Fill(D2D1::RectF(c.icon.left - grow, c.icon.top - grow,
                         c.icon.right + grow, c.icon.bottom + grow),
             D2D1::ColorF(1, 1, 1, 0.28f), 18 * s);
    }
    DrawTileIcon(tile, c.icon, live && i == g_pressed ? 0.6f : 1.0f);
    if (g_labelFormat) {
        // Light shadow so the name reads well over any background.
        const std::wstring& name = TileName(tile);
        D2D1_RECT_F shadow = c.label;
        shadow.top += 1 * s;
        shadow.bottom += 1 * s;
        g_brush->SetColor(D2D1::ColorF(0, 0, 0, 0.45f));
        g_target->DrawText(name.c_str(), (UINT32)name.size(),
                           g_labelFormat.Get(), shadow, g_brush.Get());
        g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.95f));
        g_target->DrawText(name.c_str(), (UINT32)name.size(),
                           g_labelFormat.Get(), c.label, g_brush.Get());
    }
}

void DrawFolder() {
    if (!g_openFolder) {
        return;
    }
    const Layout& L = g_layout;
    float s = L.scale;
    FolderLayout F = GetFolderLayout();
    Fill(D2D1::RectF(0, 0, (float)L.width, (float)L.height),
         D2D1::ColorF(0, 0, 0, 0.3f));
    Fill(F.panel, D2D1::ColorF(0.13f, 0.13f, 0.15f, 0.88f), 24 * s);

    // The name, with a caret: typing renames it.
    const std::wstring& name = g_openFolder->name;
    ComPtr<IDWriteTextLayout> layout;
    if (g_messageFormat) {
        g_dwrite->CreateTextLayout(name.c_str(), (UINT32)name.size(),
                                   g_messageFormat.Get(),
                                   F.title.right - F.title.left,
                                   F.title.bottom - F.title.top, &layout);
    }
    if (layout) {
        g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.95f));
        g_target->DrawTextLayout(D2D1::Point2F(F.title.left, F.title.top),
                                 layout.Get(), g_brush.Get());
        DWRITE_TEXT_METRICS m{};
        layout->GetMetrics(&m);
        float x = std::round(F.title.left + m.left +
                             m.widthIncludingTrailingWhitespace) +
                  2 * s;
        float mid = (F.title.top + F.title.bottom) / 2;
        Fill(D2D1::RectF(x, mid - 10 * s, x + std::max(1.0f, s), mid + 10 * s),
             D2D1::ColorF(1, 1, 1, 0.6f));
    }

    const Tiles& apps = g_openFolder->apps;
    g_target->PushAxisAlignedClip(
        D2D1::RectF(F.panel.left, F.top, F.panel.right,
                    F.top + F.visibleRows * F.cellHeight),
        D2D1_ANTIALIAS_MODE_ALIASED);
    int first = g_folderRow * F.columns;
    int last = std::min((int)apps.size(),
                        (g_folderRow + F.visibleRows) * F.columns);
    for (int i = first; i < last; i++) {
        DrawTile(apps[i], FolderCellAt(i), i, true);
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
        DrawMessage(L"Loading apps…");
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
        DrawTile(g_visible[i], CellAt(i), i, !g_openFolder);
    }
    g_target->PopAxisAlignedClip();

    if (g_settings.pages) {
        // One dot per page; the current one is brighter.
        if (L.pages > 1) {
            float step = 20 * s, r = 3.5f * s;
            float left = L.width / 2.0f - L.pages * step / 2 + step / 2;
            float current = g_scroll / L.width;
            for (int i = 0; i < L.pages; i++) {
                float closeness = std::max(0.0f, 1 - std::abs(current - i));
                g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.3f + 0.6f * closeness));
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
             D2D1::ColorF(1, 1, 1, 0.28f), 2 * s);
    }
}

void Render() {
    if (!g_shown || !EnsureTarget()) {
        return;
    }
    const Layout& L = g_layout;
    if (!EnsureSurface(g_surface, L.width, L.height)) {
        return;
    }
    RECT bind{0, 0, L.width, L.height};
    if (FAILED(g_target->BindDC(g_surface.dc, &bind))) {
        return;
    }
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
    DrawGrid();
    DrawFolder();
    DrawDragged();
    g_target->SetTransform(D2D1::Matrix3x2F::Identity());

    if (g_target->EndDraw() == D2DERR_RECREATE_TARGET) {
        ResetTarget();
        return;
    }
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
    if (g_openFolder) {
        SaveTiles();  // Keeps a new folder name.
        g_openFolder = nullptr;
    }
    HWND wnd = g_wnd;
    ShowWindow(wnd, SW_HIDE);
    ShowWindow(g_backdrop, SW_HIDE);
    g_shown = false;
    g_closing = false;
    g_appear = 0;
    g_backdropImage = {};
    FreeSurface(g_surface);
    g_trackingMouse = false;
}

void OnFrame() {
    double now = Now();
    float dt = (float)std::clamp(now - g_lastFrame, 0.0, 0.05);
    g_lastFrame = now;
    bool animating = false;

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

    if (g_drag.active) {
        DragTick();
        animating = true;
    }

    if (g_closing && g_appear <= 0) {
        HideNow();
        animating = false;
    } else {
        Render();
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
    g_searchDrag = false;
    TouchCaret();
    g_hover = g_selected = g_pressed = -1;
    g_scroll = g_scrollTarget = 0;
    g_wheelDelta = 0;
    g_openFolder = nullptr;
    g_folderRow = 0;
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
    g_pressed = -1;
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
struct SettingField {
    enum Kind { Header, Choice, Number, Text, Check, Color };
    Kind kind;
    PCWSTR key;
    PCWSTR label;
    std::vector<std::pair<PCWSTR, PCWSTR>> options;  // Value, label.
    int min = 0, max = 0;
    HWND labelWnd = nullptr;
    HWND control = nullptr;
    HWND swatch = nullptr;  // Color only.
    std::wstring value;     // As loaded, so a save writes only what changed.
};

std::vector<std::pair<PCWSTR, PCWSTR>> KeyActionOptions() {
    return {{L"grid", L"Open this grid"},
            {L"start", L"Open the original Start"},
            {L"program", L"Run the program below"}};
}

std::vector<SettingField> MakeSettingFields() {
    using F = SettingField;
    return {
        {F::Header, nullptr, L"Look"},
        {F::Choice,
         L"blurMode",
         L"Blur type",
         {{L"custom", L"Adjustable"},
          {L"acrylic", L"Windows acrylic"},
          {L"blur", L"Windows blur"},
          {L"none", L"No blur"}}},
        {F::Number, L"blurAmount", L"Blur strength (0 to 100)", {}, 0, 100},
        {F::Number, L"backgroundOpacity", L"Color opacity (%)", {}, 0, 100},
        {F::Color, L"tintColor", L"Background color"},
        {F::Header, nullptr, L"Grid"},
        {F::Choice,
         L"appSource",
         L"Apps to show",
         {{L"allApps", L"Start menu apps (All apps)"},
          {L"desktop", L"Desktop icons"},
          {L"both", L"Start menu apps and desktop icons"},
          {L"pinned", L"Only the apps you pin"}}},
        {F::Choice,
         L"gridLayout",
         L"Layout",
         {{L"scroll", L"One list that scrolls"},
          {L"pages", L"Pages that flip left and right"}}},
        {F::Number, L"gridIconSize", L"Icon size (pixels)", {}, 24, 192},
        {F::Number, L"gridColumns", L"Columns (0 picks for you)", {}, 0, 30},
        {F::Check, L"coverScreen", L"Cover the whole screen"},
        {F::Choice,
         L"monitor",
         L"Monitor",
         {{L"mouse", L"The monitor with the mouse"},
          {L"1", L"Main monitor"},
          {L"2", L"Monitor 2"},
          {L"3", L"Monitor 3"},
          {L"4", L"Monitor 4"}}},
        {F::Header, nullptr, L"Keys"},
        {F::Choice, L"winKeyAction", L"Windows key", KeyActionOptions()},
        {F::Choice, L"shiftWinKeyAction", L"Shift + Windows key",
         KeyActionOptions()},
        {F::Choice, L"startButtonAction", L"Start button", KeyActionOptions()},
        {F::Text, L"program", L"Program"},
    };
}

constexpr WCHAR kSettingsClass[] = L"WindhawkFullscreenStartPlusSettings";
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1;
constexpr UINT WM_APP_SETTINGS_ACTIVATE = WM_APP + 2;
enum { kSaveButton = IDOK, kCloseButton = IDCANCEL, kFirstControl = 100 };

struct SettingsWindow {
    HWND hwnd = nullptr;
    std::vector<SettingField> fields = MakeSettingFields();
    HWND status = nullptr, save = nullptr, close = nullptr;
    HFONT font = nullptr, bold = nullptr;
    HICON smallIcon = nullptr, bigIcon = nullptr;
    HBRUSH background = nullptr, input = nullptr;
    bool dark = false;
    bool saving = false;
    COLORREF customColors[16] = {};
};

HANDLE g_settingsThread;
std::atomic<HWND> g_settingsWnd;
std::atomic<bool> g_settingsStop;

bool IsDarkMode() {
    DWORD light = 1, size = sizeof(light);
    RegGetValueW(HKEY_CURRENT_USER,
                 L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\"
                 L"Personalize",
                 L"AppsUseLightTheme", RRF_RT_REG_DWORD, nullptr, &light,
                 &size);
    return light == 0;
}

COLORREF ParseColorRef(const std::wstring& text, COLORREF fallback) {
    std::wstring hex = !text.empty() && text[0] == L'#' ? text.substr(1) : text;
    if (hex.size() != 6 || hex.find_first_not_of(L"0123456789abcdefABCDEF") !=
                               std::wstring::npos) {
        return fallback;
    }
    UINT rgb = wcstoul(hex.c_str(), nullptr, 16);
    return RGB(rgb >> 16, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

std::wstring WindowString(HWND hwnd) {
    std::wstring text(GetWindowTextLengthW(hwnd) + 1, L'\0');
    text.resize(GetWindowTextW(hwnd, text.data(), (int)text.size()));
    return text;
}

// Quotes one argument the way CommandLineToArgvW reads it back.
std::wstring QuoteArg(const std::wstring& arg) {
    std::wstring out = L"\"";
    for (size_t i = 0;; i++) {
        size_t slashes = 0;
        while (i < arg.size() && arg[i] == L'\\') {
            i++, slashes++;
        }
        if (i == arg.size()) {
            out.append(slashes * 2, L'\\');
            break;
        }
        out.append(arg[i] == L'"' ? slashes * 2 + 1 : slashes, L'\\');
        out += arg[i];
    }
    return out + L"\"";
}

// windhawk-cli.exe sits three folders above the engine:
// <Windhawk>\Engine\<version>\<arch>\windhawk.dll.
std::wstring WindhawkCliPath() {
    HMODULE engine = GetModuleHandleW(L"windhawk.dll");
    WCHAR path[MAX_PATH];
    if (!engine || !GetModuleFileNameW(engine, path, MAX_PATH)) {
        return {};
    }
    std::wstring dir = path;
    for (int i = 0; i < 4; i++) {
        dir.resize(dir.find_last_of(L'\\'));
    }
    dir += L"\\windhawk-cli.exe";
    return GetFileAttributesW(dir.c_str()) == INVALID_FILE_ATTRIBUTES
               ? std::wstring()
               : dir;
}

std::wstring FieldValue(const SettingField& f) {
    switch (f.kind) {
        case SettingField::Choice: {
            int i = (int)SendMessageW(f.control, CB_GETCURSEL, 0, 0);
            return i >= 0 && i < (int)f.options.size() ? f.options[i].first
                                                       : f.value;
        }
        case SettingField::Number: {
            std::wstring text = WindowString(f.control);
            if (text.empty()) {
                return f.value;
            }
            return std::to_wstring(
                std::clamp(_wtoi(text.c_str()), f.min, f.max));
        }
        case SettingField::Check:
            return SendMessageW(f.control, BM_GETCHECK, 0, 0) == BST_CHECKED
                       ? L"1"
                       : L"0";
        default:
            return WindowString(f.control);
    }
}

void LoadSettingFields(SettingsWindow& w) {
    for (auto& f : w.fields) {
        if (f.kind == SettingField::Header) {
            continue;
        }
        f.value = f.kind == SettingField::Number || f.kind == SettingField::Check
                      ? std::to_wstring(Wh_GetIntSetting(f.key))
                      : GetStringSetting(f.key);
        switch (f.kind) {
            case SettingField::Choice: {
                int index = 0;
                for (size_t i = 0; i < f.options.size(); i++) {
                    if (f.value == f.options[i].first) {
                        index = (int)i;
                    }
                }
                SendMessageW(f.control, CB_SETCURSEL, index, 0);
                break;
            }
            case SettingField::Check:
                SendMessageW(f.control, BM_SETCHECK,
                             f.value != L"0" ? BST_CHECKED : BST_UNCHECKED, 0);
                break;
            default:
                SetWindowTextW(f.control, f.value.c_str());
        }
        if (f.swatch) {
            InvalidateRect(f.swatch, nullptr, TRUE);
        }
    }
}

// Runs windhawk-cli elevated with the changed settings, pumping messages while
// it works.
void SaveSettingFields(SettingsWindow& w) {
    std::wstring params = L"--quiet mod settings set " + QuoteArg(WH_MOD_ID);
    int changed = 0;
    for (auto& f : w.fields) {
        if (f.kind != SettingField::Header) {
            std::wstring value = FieldValue(f);
            if (value != f.value) {
                params += L" " + QuoteArg(std::wstring(f.key) + L"=" + value);
                changed++;
            }
        }
    }
    if (!changed) {
        SetWindowTextW(w.status, L"Nothing changed");
        return;
    }
    std::wstring cli = WindhawkCliPath();
    if (cli.empty()) {
        SetWindowTextW(w.status, L"windhawk-cli.exe not found");
        return;
    }
    SHELLEXECUTEINFOW info{sizeof(info)};
    info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC;
    info.hwnd = w.hwnd;
    info.lpVerb = L"runas";
    info.lpFile = cli.c_str();
    info.lpParameters = params.c_str();
    info.nShow = SW_HIDE;
    if (!ShellExecuteExW(&info) || !info.hProcess) {
        SetWindowTextW(w.status, GetLastError() == ERROR_CANCELLED
                                     ? L"Not saved"
                                     : L"Couldn't start windhawk-cli");
        return;
    }
    w.saving = true;
    EnableWindow(w.save, FALSE);
    SetWindowTextW(w.status, L"Saving...");
    bool quit = false;
    while (!quit && !g_settingsStop &&
           MsgWaitForMultipleObjects(1, &info.hProcess, FALSE, 15000,
                                     QS_ALLINPUT) == WAIT_OBJECT_0 + 1) {
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                quit = true;
                break;
            }
            if (!IsDialogMessageW(w.hwnd, &msg)) {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
        }
    }
    DWORD code = 1;
    if (WaitForSingleObject(info.hProcess, 0) == WAIT_OBJECT_0) {
        GetExitCodeProcess(info.hProcess, &code);
    }
    CloseHandle(info.hProcess);
    w.saving = false;
    if (quit || !IsWindow(w.hwnd)) {
        PostQuitMessage(0);
        return;
    }
    EnableWindow(w.save, TRUE);
    if (code == 0) {
        LoadSettingFields(w);  // Shows what was stored, numbers clamped.
        SetWindowTextW(w.status, L"Saved");
    } else {
        Wh_Log(L"windhawk-cli exit code %u", code);
        SetWindowTextW(w.status, L"Windhawk didn't save the settings");
    }
}

// The window icon: a 3x3 grid of rounded tiles, like the grid itself, drawn
// with antialiased edges into a 32-bit icon.
HICON MakeGridIcon(int size) {
    BITMAPINFO bi{};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), size, -size, 1, 32, BI_RGB};
    DWORD* pixels = nullptr;
    HBITMAP color =
        CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, (void**)&pixels, nullptr, 0);
    if (!color) {
        return nullptr;
    }
    const float gap = size / 10.0f, tile = (size - gap * 4) / 3,
                radius = tile / 4;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            float alpha = 0;
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    // Signed distance to the rounded tile, sampled at the pixel
                    // center.
                    float cx = gap + col * (tile + gap) + tile / 2;
                    float cy = gap + row * (tile + gap) + tile / 2;
                    float dx = std::max(std::fabs(x + 0.5f - cx) - tile / 2 + radius, 0.0f);
                    float dy = std::max(std::fabs(y + 0.5f - cy) - tile / 2 + radius, 0.0f);
                    float d = std::sqrt(dx * dx + dy * dy) - radius;
                    alpha = std::max(alpha, std::clamp(0.5f - d, 0.0f, 1.0f));
                }
            }
            BYTE a = (BYTE)std::lround(alpha * 255);
            // #60A5FA, premultiplied.
            pixels[y * size + x] = (a << 24) | ((0x60 * a / 255) << 16) |
                                   ((0xA5 * a / 255) << 8) | (0xFA * a / 255);
        }
    }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO info{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&info);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

void LayoutSettingsWindow(SettingsWindow& w, UINT dpi) {
    auto px = [dpi](int v) { return MulDiv(v, dpi, 96); };
    if (w.font) {
        DeleteObject(w.font);
        DeleteObject(w.bold);
    }
    LOGFONTW lf{};
    lf.lfHeight = -MulDiv(9, dpi, 72);
    // Grayscale, since ClearType's colored edges show on the blurred sheet.
    lf.lfQuality = ANTIALIASED_QUALITY;
    wcscpy_s(lf.lfFaceName, L"Segoe UI");
    w.font = CreateFontIndirectW(&lf);
    lf.lfHeight = -MulDiv(11, dpi, 72);
    lf.lfWeight = FW_SEMIBOLD;
    w.bold = CreateFontIndirectW(&lf);

    for (HICON icon : {w.smallIcon, w.bigIcon}) {
        if (icon) {
            DestroyIcon(icon);
        }
    }
    w.smallIcon = MakeGridIcon(GetSystemMetricsForDpi(SM_CXSMICON, dpi));
    w.bigIcon = MakeGridIcon(GetSystemMetricsForDpi(SM_CXICON, dpi));
    SendMessageW(w.hwnd, WM_SETICON, ICON_SMALL, (LPARAM)w.smallIcon);
    SendMessageW(w.hwnd, WM_SETICON, ICON_BIG, (LPARAM)w.bigIcon);

    const int margin = px(20), labelWidth = px(190), controlWidth = px(290);
    const int controlX = margin + labelWidth + px(10);
    int y = px(8);
    for (auto& f : w.fields) {
        if (f.kind == SettingField::Header) {
            y += px(12);
            SetWindowPos(f.labelWnd, nullptr, margin, y,
                         labelWidth + controlWidth, px(24), SWP_NOZORDER);
            SendMessageW(f.labelWnd, WM_SETFONT, (WPARAM)w.bold, TRUE);
            y += px(30);
            continue;
        }
        SetWindowPos(f.labelWnd, nullptr, margin, y + px(4), labelWidth,
                     px(20), SWP_NOZORDER);
        SendMessageW(f.labelWnd, WM_SETFONT, (WPARAM)w.font, TRUE);
        int width = f.kind == SettingField::Number  ? px(80)
                    : f.kind == SettingField::Color ? px(110)
                    : f.kind == SettingField::Check ? px(24)
                                                    : controlWidth;
        int height = f.kind == SettingField::Choice ? px(200) : px(26);
        SetWindowPos(f.control, nullptr, controlX, y, width, height,
                     SWP_NOZORDER);
        SendMessageW(f.control, WM_SETFONT, (WPARAM)w.font, TRUE);
        if (f.swatch) {
            SetWindowPos(f.swatch, nullptr, controlX + width + px(8), y,
                         px(40), px(26), SWP_NOZORDER);
        }
        y += px(34);
    }
    y += px(12);
    const int buttonWidth = px(90), buttonHeight = px(30);
    const int clientWidth = controlX + controlWidth + margin;
    SetWindowPos(w.close, nullptr, clientWidth - margin - buttonWidth, y,
                 buttonWidth, buttonHeight, SWP_NOZORDER);
    SetWindowPos(w.save, nullptr,
                 clientWidth - margin - buttonWidth * 2 - px(8), y, buttonWidth,
                 buttonHeight, SWP_NOZORDER);
    SetWindowPos(w.status, nullptr, margin, y + px(6),
                 clientWidth - margin * 3 - buttonWidth * 2, px(20),
                 SWP_NOZORDER);
    for (HWND h : {w.status, w.save, w.close}) {
        SendMessageW(h, WM_SETFONT, (WPARAM)w.font, TRUE);
    }

    RECT r{0, 0, clientWidth, y + buttonHeight + margin};
    AdjustWindowRectExForDpi(&r, GetWindowLongW(w.hwnd, GWL_STYLE), FALSE,
                             GetWindowLongW(w.hwnd, GWL_EXSTYLE), dpi);
    SetWindowPos(w.hwnd, nullptr, 0, 0, r.right - r.left, r.bottom - r.top,
                 SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void ThemeSettingsWindow(SettingsWindow& w) {
    w.dark = IsDarkMode();
    if (w.background) {
        DeleteObject(w.background);
        DeleteObject(w.input);
    }
    // In dark mode the title bar and body are one acrylic sheet, tinted with
    // the grid's background color: an empty blur region makes DWM use the
    // window's alpha, and black GDI paint has alpha 0, so the body shows the
    // blur.
    w.background = CreateSolidBrush(w.dark ? RGB(0, 0, 0)
                                           : GetSysColor(COLOR_BTNFACE));
    w.input =
        CreateSolidBrush(w.dark ? RGB(43, 43, 43) : GetSysColor(COLOR_WINDOW));
    BOOL dark = w.dark;
    DwmSetWindowAttribute(w.hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark,
                          sizeof(dark));
    DWM_BLURBEHIND blur{};
    blur.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    blur.fEnable = w.dark;
    blur.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
    DwmEnableBlurBehindWindow(w.hwnd, &blur);
    DeleteObject(blur.hRgnBlur);
    DWORD noBackdrop = 1;  // DWMSBT_NONE, so the accent below is what shows.
    DwmSetWindowAttribute(w.hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */,
                          &noBackdrop, sizeof(noBackdrop));
    COLORREF tint = ParseColorRef(GetStringSetting(L"tintColor"), RGB(30, 30, 46));
    SetAccent(w.hwnd, w.dark ? ACCENT_ENABLE_ACRYLICBLURBEHIND : ACCENT_DISABLED,
              w.dark ? 0xAA000000 | tint : 0);
    EnumChildWindows(
        w.hwnd,
        [](HWND child, LPARAM param) -> BOOL {
            WCHAR className[32] = {};
            GetClassNameW(child, className, ARRAYSIZE(className));
            PCWSTR theme = param ? L"DarkMode_Explorer" : L"Explorer";
            if (param && _wcsicmp(className, L"ComboBox") == 0) {
                theme = L"DarkMode_CFD";
            }
            SetWindowTheme(child, theme, nullptr);
            return TRUE;
        },
        w.dark);
    InvalidateRect(w.hwnd, nullptr, TRUE);
}

LRESULT CALLBACK SettingsWndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                 LPARAM lParam) {
    auto* w = (SettingsWindow*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
    if (msg == WM_NCCREATE) {
        w = (SettingsWindow*)((CREATESTRUCTW*)lParam)->lpCreateParams;
        w->hwnd = hwnd;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)w);
    }
    if (!w) {
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    switch (msg) {
        case WM_ERASEBKGND: {
            RECT r;
            GetClientRect(hwnd, &r);
            FillRect((HDC)wParam, &r, w->background);
            return 1;
        }
        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLORBTN:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORLISTBOX: {
            bool field = msg == WM_CTLCOLOREDIT || msg == WM_CTLCOLORLISTBOX;
            HDC dc = (HDC)wParam;
            if ((HWND)lParam == w->status) {
                SetTextColor(dc, w->dark ? RGB(170, 170, 170)
                                         : GetSysColor(COLOR_GRAYTEXT));
            } else {
                SetTextColor(dc, w->dark ? RGB(255, 255, 255)
                                         : GetSysColor(COLOR_WINDOWTEXT));
            }
            SetBkColor(dc, field ? (w->dark ? RGB(43, 43, 43)
                                            : GetSysColor(COLOR_WINDOW))
                                 : (w->dark ? RGB(0, 0, 0)
                                            : GetSysColor(COLOR_BTNFACE)));
            if (!field) {
                SetBkMode(dc, TRANSPARENT);
            }
            return (LRESULT)(field ? w->input : w->background);
        }
        case WM_DRAWITEM: {
            auto* item = (DRAWITEMSTRUCT*)lParam;
            for (auto& f : w->fields) {
                if (f.swatch == item->hwndItem) {
                    HBRUSH brush = CreateSolidBrush(
                        ParseColorRef(WindowString(f.control), RGB(0, 0, 0)));
                    FillRect(item->hDC, &item->rcItem, brush);
                    DeleteObject(brush);
                    HBRUSH frame = CreateSolidBrush(RGB(128, 128, 128));
                    FrameRect(item->hDC, &item->rcItem, frame);
                    DeleteObject(frame);
                    return TRUE;
                }
            }
            break;
        }
        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (id == kSaveButton) {
                if (!w->saving) {
                    SaveSettingFields(*w);
                }
                return 0;
            }
            if (id == kCloseButton) {
                DestroyWindow(hwnd);
                return 0;
            }
            for (auto& f : w->fields) {
                if (f.kind != SettingField::Color) {
                    continue;
                }
                if ((HWND)lParam == f.control && HIWORD(wParam) == EN_CHANGE) {
                    InvalidateRect(f.swatch, nullptr, TRUE);
                } else if ((HWND)lParam == f.swatch) {
                    CHOOSECOLORW cc{sizeof(cc)};
                    cc.hwndOwner = hwnd;
                    cc.rgbResult =
                        ParseColorRef(WindowString(f.control), RGB(0, 0, 0));
                    cc.lpCustColors = w->customColors;
                    cc.Flags = CC_RGBINIT | CC_FULLOPEN;
                    if (ChooseColorW(&cc)) {
                        WCHAR text[8];
                        swprintf_s(text, L"#%02X%02X%02X",
                                   GetRValue(cc.rgbResult),
                                   GetGValue(cc.rgbResult),
                                   GetBValue(cc.rgbResult));
                        SetWindowTextW(f.control, text);
                    }
                }
            }
            break;
        }
        case WM_APP_SETTINGS_RELOAD:
            if (!w->saving) {
                LoadSettingFields(*w);
            }
            return 0;
        case WM_APP_SETTINGS_ACTIVATE:
            if (IsIconic(hwnd)) {
                ShowWindow(hwnd, SW_RESTORE);
            }
            ForceForeground(hwnd);
            return 0;
        case WM_SETTINGCHANGE:
            if (lParam && wcscmp((PCWSTR)lParam, L"ImmersiveColorSet") == 0) {
                ThemeSettingsWindow(*w);
            }
            break;
        case WM_DPICHANGED: {
            auto* r = (RECT*)lParam;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left,
                         r->bottom - r->top, SWP_NOZORDER | SWP_NOACTIVATE);
            LayoutSettingsWindow(*w, HIWORD(wParam));
            return 0;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            g_settingsWnd = nullptr;
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

DWORD WINAPI SettingsThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HINSTANCE instance = GetModuleHandleW(nullptr);
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = SettingsWndProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kSettingsClass;
    RegisterClassExW(&wc);

    SettingsWindow w;
    HWND hwnd = CreateWindowExW(
        0, kSettingsClass, L"Fullscreen Start Plus settings",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,
        CW_USEDEFAULT, 100, 100, nullptr, nullptr, instance, &w);
    if (!hwnd) {
        UnregisterClassW(kSettingsClass, instance);
        return 0;
    }
    auto child = [&](PCWSTR cls, PCWSTR text, DWORD style, int id,
                     DWORD exStyle = 0) {
        return CreateWindowExW(exStyle, cls, text, WS_CHILD | WS_VISIBLE | style,
                               0, 0, 0, 0, hwnd, (HMENU)(INT_PTR)id, instance,
                               nullptr);
    };
    int id = kFirstControl;
    for (auto& f : w.fields) {
        f.labelWnd = child(L"STATIC", f.label, SS_LEFT | SS_NOPREFIX, 0);
        switch (f.kind) {
            case SettingField::Header:
                continue;
            case SettingField::Choice:
                f.control = child(L"COMBOBOX", L"",
                                  CBS_DROPDOWNLIST | WS_TABSTOP | WS_VSCROLL,
                                  id++);
                for (auto& option : f.options) {
                    SendMessageW(f.control, CB_ADDSTRING, 0,
                                 (LPARAM)option.second);
                }
                break;
            case SettingField::Check:
                f.control = child(L"BUTTON", L"", BS_AUTOCHECKBOX | WS_TABSTOP,
                                  id++);
                break;
            case SettingField::Number:
                f.control =
                    child(L"EDIT", L"", ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP,
                          id++, WS_EX_CLIENTEDGE);
                break;
            default:
                f.control = child(L"EDIT", L"", ES_AUTOHSCROLL | WS_TABSTOP,
                                  id++, WS_EX_CLIENTEDGE);
        }
        if (f.kind == SettingField::Color) {
            f.swatch = child(L"BUTTON", L"", BS_OWNERDRAW | WS_TABSTOP, id++);
        }
    }
    w.status = child(L"STATIC", L"", SS_LEFT | SS_NOPREFIX, 0);
    w.save =
        child(L"BUTTON", L"Save", BS_DEFPUSHBUTTON | WS_TABSTOP, kSaveButton);
    w.close =
        child(L"BUTTON", L"Close", BS_PUSHBUTTON | WS_TABSTOP, kCloseButton);

    // Centered on the monitor the grid was on.
    POINT cursor;
    GetCursorPos(&cursor);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST), &mi);
    SetWindowPos(hwnd, nullptr, mi.rcWork.left, mi.rcWork.top, 0, 0,
                 SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    LayoutSettingsWindow(w, GetDpiForWindow(hwnd));
    RECT r;
    GetWindowRect(hwnd, &r);
    SetWindowPos(hwnd, nullptr,
                 (mi.rcWork.left + mi.rcWork.right - (r.right - r.left)) / 2,
                 (mi.rcWork.top + mi.rcWork.bottom - (r.bottom - r.top)) / 2, 0,
                 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    ThemeSettingsWindow(w);
    LoadSettingFields(w);
    g_settingsWnd = hwnd;
    if (g_settingsStop) {
        DestroyWindow(hwnd);
    } else {
        ShowWindow(hwnd, SW_SHOW);
        ForceForeground(hwnd);
    }

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (!IsDialogMessageW(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    DeleteObject(w.font);
    DeleteObject(w.bold);
    DestroyIcon(w.smallIcon);
    DestroyIcon(w.bigIcon);
    DeleteObject(w.background);
    DeleteObject(w.input);
    UnregisterClassW(kSettingsClass, instance);
    return 0;
}

void OpenSettingsWindow() {
    if (HWND hwnd = g_settingsWnd) {
        PostMessageW(hwnd, WM_APP_SETTINGS_ACTIVATE, 0, 0);
        return;
    }
    if (g_settingsThread) {
        if (WaitForSingleObject(g_settingsThread, 0) == WAIT_TIMEOUT) {
            return;
        }
        CloseHandle(g_settingsThread);
    }
    g_settingsStop = false;
    g_settingsThread =
        CreateThread(nullptr, 0, SettingsThread, nullptr, 0, nullptr);
}

void CloseSettingsWindow() {
    if (!g_settingsThread) {
        return;
    }
    g_settingsStop = true;
    while (WaitForSingleObject(g_settingsThread, 100) == WAIT_TIMEOUT) {
        if (HWND hwnd = g_settingsWnd) {
            PostMessageW(hwnd, WM_CLOSE, 0, 0);
        }
    }
    CloseHandle(g_settingsThread);
    g_settingsThread = nullptr;
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
    g_openFolder = std::move(folder);
    g_folderRow = 0;
    g_hover = g_selected = g_pressed = -1;
    Render();
}

void CloseFolder() {
    if (!g_openFolder) {
        return;
    }
    g_openFolder = nullptr;
    g_hover = g_selected = g_pressed = -1;
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
                        : InRect(g_layout.search, (float)x, (float)y);
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
        if (paths.folder.empty() && EndsWith(ToLower(paths.file), L".exe")) {
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
        AppendMenuW(menu, MF_STRING, kChangeIcon, L"Change icon…");
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
            LaunchTarget(linkOrFile, L"runas");
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
            InsertAtCaret(line);
        }
    }
    CloseClipboard();
    EditChanged();
}

void OnChar(WCHAR ch) {
    if (g_drag.active || g_drag.pending) {
        return;
    }
    switch (ch) {
        case 8: {  // Backspace: the selection, or a code point before the caret.
            if (DeleteSelection()) {
                EditChanged();
            } else if (g_caret > 0) {
                size_t prev = CaretStep(g_caret, -1);
                EditText().erase(prev, g_caret - prev);
                g_caret = g_anchor = prev;
                EditChanged();
            }
            TouchCaret();
            return;
        }
        case 0x7F: {  // Ctrl+Backspace: the word before the caret.
            if (DeleteSelection()) {
                EditChanged();
            } else if (g_caret > 0) {
                size_t start = WordStart(g_caret);
                EditText().erase(start, g_caret - start);
                g_caret = g_anchor = start;
                EditChanged();
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
    }
    if (ch >= 32 && EditText().size() < MaxEditChars()) {
        InsertAtCaret(std::wstring(1, ch));
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
    if (g_drag.active && key != VK_ESCAPE) {
        return;
    }
    switch (key) {
        case VK_ESCAPE:
            if (g_drag.active) {
                EndDrag(false);
                ReleaseCapture();
            } else if (g_openFolder) {
                CloseFolder();
            } else if (!g_query.empty()) {
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
                SetCaret(g_query.size(), GetKeyState(VK_SHIFT) < 0);
                Render();
            }
            break;
        case VK_DELETE:
            if (!EditText().empty()) {
                if (DeleteSelection()) {
                    QueryChanged();
                } else {
                    size_t next = CaretStep(g_caret, 1);
                    if (next != g_caret) {
                        g_query.erase(g_caret, next - g_caret);
                        QueryChanged();
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
// (helper/fsp-keys.cpp) runs as administrator with the same hook. While its
// window exists, this hook leaves the key to it, and the helper sends
// WM_APP_SHIFT_WIN with wParam 1, then presses Ctrl+Esc itself if the answer
// is 1.
constexpr WCHAR kHelperClass[] = L"FullscreenStartPlusKeys";

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
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
                case kTimerCaret:
                    // The search caret blinks by plain redraws.
                    if (g_shown) {
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
            float slop = 6 * g_layout.scale;
            if (g_drag.pending && !g_drag.active &&
                (std::abs(x - g_drag.start.x) > slop ||
                 std::abs(y - g_drag.start.y) > slop)) {
                StartDrag();
            }
            if (g_drag.active) {
                DragMove(x, y);
                return 0;
            }
            int hover = ItemAt(x, y);
            bool menuHover = !g_openFolder &&
                             InRect(g_layout.menuButton, (float)x, (float)y);
            if (hover != g_hover || menuHover != g_menuHover) {
                g_hover = hover;
                g_menuHover = menuHover;
                Render();
            }
            return 0;
        }

        case WM_MOUSELEAVE:
            g_trackingMouse = false;
            if (g_hover >= 0 || g_menuHover) {
                g_hover = -1;
                g_menuHover = false;
                Render();
            }
            return 0;

        case WM_LBUTTONDOWN: {
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            if (!g_openFolder) {
                if (InRect(g_layout.menuButton, (float)x, (float)y)) {
                    POINT pt{(LONG)g_layout.menuButton.right,
                             (LONG)g_layout.menuButton.bottom + 4};
                    ClientToScreen(hwnd, &pt);
                    ShowOptionsMenu(hwnd, pt, true);
                    return 0;
                }
                int dot = PageDotAt(x, y);
                if (dot >= 0) {
                    g_scrollTarget = dot * (float)g_layout.width;
                    StartFrames();
                    return 0;
                }
                if (InRect(g_layout.search, (float)x, (float)y)) {
                    // A click in the search field places the caret; holding
                    // the button and moving selects text. A second click on
                    // the same spot selects the word under it.
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
            }
            if (g_anchor != g_caret) {
                g_anchor = g_caret;  // A click elsewhere drops the selection.
            }
            SetCapture(hwnd);
            g_pressed = ItemAt(x, y);
            g_pressedEmpty = g_pressed < 0 && !ClickKeepsOpen(x, y);
            g_drag.pending = g_pressed >= 0 && g_query.empty();
            g_drag.start = {x, y};
            Render();
            return 0;
        }

        case WM_LBUTTONUP: {
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            g_searchDrag = false;
            bool dragged = g_drag.active;
            EndDrag(true);  // Before the capture goes, which would undo it.
            if (GetCapture() == hwnd) {
                ReleaseCapture();
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
    FreeSurface(g_surface);
    g_labelFormat.Reset();
    g_searchFormat.Reset();
    g_messageFormat.Reset();
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

    CloseSettingsWindow();
    if (!g_thread) {
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
