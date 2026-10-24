// ==WindhawkMod==
// @id              fullscreen-start-plus
// @name            Fullscreen Start Plus
// @description     A fullscreen grid of all your apps in place of Start, with instant search and adjustable blur
// @version         1.4.0
// @author          DavidHiFi, Rafael Mendes
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -lshell32 -lshcore -ldwmapi -ld2d1 -ldwrite -lole32 -luuid -lcomdlg32 -luxtheme
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
  both together, or only the apps you pinned to Start.
- **Scroll or pages.** One list that scrolls, or pages that flip left and
  right with dots below, like Launchpad.
- **Instant search.** Just type. Case and accents don't matter, and names that
  start with your text come first.
- **Adjustable blur.** Pick the blur type, strength, opacity and color of the
  background.
- **Opens like Start.** The Windows key, Ctrl+Esc and the Start button of the
  taskbar or the Standalone Dock all open it.
- **Your own Windows key.** The Windows key, Shift + Windows key and the Start
  button can each open this grid, the original Start, or a program of your
  choice, such as a launcher. The program starts even when it isn't running,
  so this replaces the same feature of Open-Shell.

## Keyboard and mouse
| Key | Action |
| --- | --- |
| Type | Search |
| Backspace, Ctrl+Backspace | Delete a letter, or the last word |
| Ctrl+V | Paste |
| Arrows, Enter | Pick an app and open it. While searching, the first result is already picked |
| Esc | Clear the search, or close when the search is empty |
| Mouse wheel, Page Up, Page Down | Scroll, or flip pages |
| Sideways scroll, page dots | Flip pages |
| The ... button, top right | Open this mod's own settings window (it saves to the same settings as Windhawk's page) |

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
  $description: Pinned apps keep the order they have in Start
  $options:
  - allApps: Start menu apps (the All apps list)
  - desktop: Desktop icons
  - both: Start menu apps and desktop icons
  - pinned: Apps pinned to Start
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
// Otherwise the Win32 macro renames ID2D1RenderTarget::DrawText.
#undef DrawText
#include <d2d1_1.h>
#include <dwrite.h>
#include <wrl/client.h>
#include <windhawk_utils.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <memory>
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
bool g_appsFailed;  // The pins couldn't be read.
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

void LoadAppIcon(IShellItem* item, int size, App& app) {
    ComPtr<IShellItemImageFactory> factory;
    HBITMAP bitmap = nullptr;
    if (FAILED(item->QueryInterface(IID_PPV_ARGS(&factory))) ||
        FAILED(factory->GetImage(SIZE{size, size},
                                 SIIGBF_ICONONLY | SIIGBF_BIGGERSIZEOK,
                                 &bitmap))) {
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

AppList* EnumerateApps(int iconPixels, AppSource source) {
    auto list = std::make_unique<AppList>();
    if (source == AppSource::Pinned) {
        // Keeps Start's order. nullptr: the pins couldn't be read.
        return AddStartPins(iconPixels, *list) ? list.release() : nullptr;
    }
    if (source != AppSource::Desktop) {
        AddStartApps(iconPixels, *list);
    }
    if (source != AppSource::AllApps) {
        AddDesktopItems(iconPixels, *list);
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
// Search

std::wstring g_query;
std::vector<int> g_visible;  // Indices in g_apps that pass the search.

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
        int rank = 0;
        for (size_t w = 0; w < words.size() && rank >= 0; w++) {
            int r = MatchRank(g_apps[i]->name, words[w]);
            rank = r < 0 ? -1 : (w == 0 ? r : rank);
        }
        if (rank >= 0) {
            ranked.emplace_back(rank, i);
        }
    }
    std::stable_sort(ranked.begin(), ranked.end(),
                     [](const auto& a, const auto& b) {
                         return a.first < b.first;
                     });
    g_visible.clear();
    for (const auto& r : ranked) {
        g_visible.push_back(r.second);
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

bool InRect(const D2D1_RECT_F& r, float x, float y) {
    return x >= r.left && x < r.right && y >= r.top && y < r.bottom;
}

// Position in the visible list under the point (window coordinates), or -1.
int ItemAt(int px, int py) {
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
    int index = page * L.perPage + row * L.columns + col;
    if (row < 0 || index < 0 || index >= (int)g_visible.size() ||
        !InRect(CellAt(index).highlight, x, y)) {
        return -1;
    }
    return index;
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

    // The typed text, with its end always visible, and the caret after it.
    ComPtr<IDWriteTextLayout> layout;
    g_dwrite->CreateTextLayout(g_query.c_str(), (UINT32)g_query.size(),
                               g_searchFormat.Get(), 10000,
                               text.bottom - text.top, &layout);
    if (!layout) {
        return;
    }
    layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    DWRITE_TEXT_METRICS metrics{};
    layout->GetMetrics(&metrics);
    float textWidth = metrics.widthIncludingTrailingWhitespace;
    float room = text.right - text.left - 3 * s;
    float shift = std::max(0.0f, textWidth - room);
    g_target->PushAxisAlignedClip(text, D2D1_ANTIALIAS_MODE_ALIASED);
    g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.95f));
    g_target->DrawTextLayout(D2D1::Point2F(text.left - shift, text.top),
                             layout.Get(), g_brush.Get());
    float caretX = std::round(text.left + textWidth - shift) + 1;
    float caretH = 18 * s;
    float mid = (text.top + text.bottom) / 2;
    Fill(D2D1::RectF(caretX, mid - caretH / 2, caretX + std::max(1.0f, s),
                     mid + caretH / 2),
         D2D1::ColorF(1, 1, 1, 0.9f));
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

void DrawGrid() {
    const Layout& L = g_layout;
    float s = L.scale;
    if (!g_appsLoaded && g_apps.empty()) {
        DrawMessage(L"Loading apps…");
        return;
    }
    if (g_visible.empty()) {
        DrawMessage(!g_query.empty() ? L"No apps found"
                    : g_appsFailed ? L"Couldn't read the apps pinned to Start"
                    : (g_appsKey >> 16) == (int)AppSource::Pinned
                        ? L"No apps are pinned to Start"
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
        App& app = *g_apps[g_visible[i]];
        Cell c = CellAt(i);
        if (i == g_selected || i == g_hover) {
            Fill(c.highlight,
                 D2D1::ColorF(1, 1, 1, i == g_selected ? 0.18f : 0.10f),
                 12 * s);
        }
        float opacity = i == g_pressed ? 0.6f : 1.0f;
        if (ID2D1Bitmap* bitmap = GetBitmap(app)) {
            g_target->DrawBitmap(bitmap, c.icon, opacity,
                                 D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
        } else {
            Fill(c.icon, D2D1::ColorF(1, 1, 1, 0.12f * opacity), 14 * s);
        }
        if (g_labelFormat) {
            // Light shadow so the name reads well over any background.
            D2D1_RECT_F shadow = c.label;
            shadow.top += 1 * s;
            shadow.bottom += 1 * s;
            g_brush->SetColor(D2D1::ColorF(0, 0, 0, 0.45f));
            g_target->DrawText(app.name.c_str(), (UINT32)app.name.size(),
                               g_labelFormat.Get(), shadow, g_brush.Get());
            g_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.95f));
            g_target->DrawText(app.name.c_str(), (UINT32)app.name.size(),
                               g_labelFormat.Get(), c.label, g_brush.Get());
        }
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
    g_hover = g_selected = g_pressed = -1;
    g_scroll = g_scrollTarget = 0;
    g_wheelDelta = 0;
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

void LaunchApp(int index) {
    if (index < 0 || index >= (int)g_visible.size()) {
        return;
    }
    const App& app = *g_apps[g_visible[index]];
    SHELLEXECUTEINFOW sei{sizeof(sei)};
    sei.fMask = SEE_MASK_ASYNCOK;
    sei.lpFile = app.target.c_str();
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
          {L"pinned", L"Apps pinned to Start"}}},
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

// The "..." menu.
void ShowOptionsMenu(HWND hwnd) {
    enum { kOpenSettings = 1 };
    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, kOpenSettings, L"Open settings");
    const RECT& a = g_layout.area;
    const D2D1_RECT_F& r = g_layout.menuButton;
    int command = TrackPopupMenuEx(
        menu, TPM_RETURNCMD | TPM_RIGHTALIGN | TPM_TOPALIGN | TPM_NONOTIFY,
        a.left + (int)r.right, a.top + (int)r.bottom + 4, hwnd, nullptr);
    DestroyMenu(menu);
    if (command == kOpenSettings) {
        HideNow();
        OpenSettingsWindow();
    }
}

void EnsureVisible(int index) {
    if (index < 0) {
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
            g_query += line.substr(0, 200);
        }
    }
    CloseClipboard();
    QueryChanged();
}

void OnChar(WCHAR ch) {
    switch (ch) {
        case 8:  // Backspace
            if (!g_query.empty()) {
                g_query.pop_back();
                if (!g_query.empty() && IS_HIGH_SURROGATE(g_query.back())) {
                    g_query.pop_back();
                }
                QueryChanged();
            }
            return;
        case 0x7F: {  // Ctrl+Backspace: the last word.
            size_t end = g_query.find_last_not_of(L' ');
            if (end == std::wstring::npos) {
                g_query.clear();
            } else {
                size_t space = g_query.find_last_of(L' ', end);
                g_query.resize(space == std::wstring::npos ? 0 : space + 1);
            }
            QueryChanged();
            return;
        }
        case 0x16:  // Ctrl+V
            PasteText();
            return;
    }
    if (ch >= 32 && g_query.size() < 200) {
        g_query += ch;
        QueryChanged();
    }
}

void MoveSelection(int delta) {
    if (g_visible.empty()) {
        return;
    }
    int count = (int)g_visible.size();
    if (g_selected < 0) {
        g_selected = 0;
    } else {
        int next = g_selected + delta;
        if (next >= 0 && next < count) {
            g_selected = next;
        } else if (delta > 0 && delta == g_layout.columns) {
            g_selected = count - 1;  // Down on the last incomplete row.
        }
    }
    EnsureVisible(g_selected);
    Render();
    StartFrames();
}

void OnKeyDown(WPARAM key) {
    switch (key) {
        case VK_ESCAPE:
            if (!g_query.empty()) {
                g_query.clear();
                QueryChanged();
            } else {
                Close();
            }
            break;
        case VK_RETURN:
            if (g_selected >= 0) {
                LaunchApp(g_selected);
            } else if (!g_query.empty() && !g_visible.empty()) {
                LaunchApp(0);
            }
            break;
        case VK_LEFT:
            MoveSelection(-1);
            break;
        case VK_RIGHT:
            MoveSelection(1);
            break;
        case VK_UP:
            MoveSelection(-g_layout.columns);
            break;
        case VK_DOWN:
            MoveSelection(g_layout.columns);
            break;
        case VK_PRIOR:
            ScrollRows(-g_layout.visibleRows);
            break;
        case VK_NEXT:
            ScrollRows(g_layout.visibleRows);
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
                if (!otherKey && withShift && wnd) {
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
    g_appsFailed = !list;
    g_apps = list ? std::move(*list) : AppList{};
    delete list;
    g_appsLoaded = true;
    g_appsKey = key;
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
            if (LOWORD(wParam) == WA_INACTIVE && g_shown && !g_closing) {
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
            int hover = ItemAt(x, y);
            bool menuHover = InRect(g_layout.menuButton, (float)x, (float)y);
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
            if (InRect(g_layout.menuButton, (float)x, (float)y)) {
                ShowOptionsMenu(hwnd);
                return 0;
            }
            int dot = PageDotAt(x, y);
            if (dot >= 0) {
                g_scrollTarget = dot * (float)g_layout.width;
                StartFrames();
                return 0;
            }
            SetCapture(hwnd);
            g_pressed = ItemAt(x, y);
            g_pressedEmpty = g_pressed < 0 &&
                             !InRect(g_layout.search, (float)x, (float)y);
            Render();
            return 0;
        }

        case WM_LBUTTONUP: {
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            if (GetCapture() == hwnd) {
                ReleaseCapture();
            }
            int item = ItemAt(x, y);
            int pressed = g_pressed;
            g_pressed = -1;
            if (pressed >= 0 && item == pressed) {
                LaunchApp(item);
            } else if (g_pressedEmpty && item < 0 &&
                       !InRect(g_layout.search, (float)x, (float)y)) {
                Close();  // Clicking on empty space closes, like in Launchpad.
            } else {
                Render();
            }
            g_pressedEmpty = false;
            return 0;
        }

        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
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
