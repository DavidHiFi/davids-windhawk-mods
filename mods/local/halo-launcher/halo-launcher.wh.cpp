// ==WindhawkMod==
// @id              halo-launcher
// @name            Halo Launcher
// @description     Press a key, type a few letters, press Enter: apps, files, sums, web searches and every module
// @version         0.6.6
// @author          DavidHiFi, David Ravelo
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         windhawk-mod.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshlwapi -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -ladvapi32 -lwinmm
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Halo Launcher

Press a key, type a few letters, press Enter. Halo finds apps, files, settings,
bookmarks and web searches, does sums, and runs modules for everything else.

![Halo Launcher settings](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/halo-launcher.png)

Halo draws its own window on dark Mocha glass with a blue to mauve edge, and has
its own settings window: open it from the tray icon or with Ctrl+I in Halo.

## What it does

- Opens on a tap of the Windows key, or any key you pick in the settings. The
  tap replaces the Windows Start menu: Start never opens for it. With Seamless
  Launchpad, Shift + Windows key and the Start button open its app grid.
- Shortcut keys for searches you use a lot, like Win+R for the command line.
- Modules: turn each one on or off, change the words that call it, and change
  a module's own settings right in its card when you open it.
- History, a preview of the selected file (F1), and Space to open it in the Peek
  mod once you have moved through the results.
- A tray icon: click it for settings, right-click it to open Halo or restart its
  search engine.

## Keys in the window

| Key | What it does |
|---|---|
| Enter | Open the selected result |
| Shift+Enter, Right | More actions for the result |
| Up, Down, Tab, Shift+Tab | Move through the results |
| Page Up, Page Down | Move a page |
| Alt+1 to Alt+0 | Open result 1 to 10 |
| Ctrl+H | History |
| Ctrl+I | Settings |
| F1 | Preview the selected file |
| Esc | Back, then close |

Every key in that list can be changed on the Keys page of the settings.

## What's new in 0.6.6

- A module's own settings no longer leave copies of the Save bar behind
  while you scroll the page.

## Credits

- The window started from [Spotlight Launcher](https://windhawk.net/mods/spotlight-launcher) by David Ravelo (MIT).
- The search runs on [Flow Launcher](https://github.com/Flow-Launcher/Flow.Launcher)'s plugin code (MIT), which grew out of [Wox](https://github.com/Wox-launcher/Wox) (MIT).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- openKey: ""
  $name: "Second open key"
  $description: "Another key that opens and closes Halo, kept even when the keys below are off. Leave it empty for none."
- useFlowKeys: true
  $name: "Use the open key and shortcut keys"
  $description: "Halo answers the open key above and the query shortcut keys, like Win+R for the command line. Off, only the second open key works."
- peekOnSpace: true
  $name: "Space previews the file"
  $description: "After moving through the results with the arrows or Tab, Space opens the selected file in the Peek mod. Typing a space still works before that."
- backgroundOpacity: 55
  $name: "Glass darkness"
  $description: "0 to 100 (Suggested: 55). How much Mocha covers the blur. 55 is the same glass as the settings windows."
- blur: true
  $name: "Blur behind the window"
  $description: "Off, the window is solid Mocha."
- fontFamily: "FiraCode Nerd Font"
  $name: "Font"
  $description: "The font for all of Halo's words: the search box, results, clock, hints and preview. If it is not installed, Segoe UI is used at the same size."
- fontWeight: "Medium"
  $name: "Font weight"
  $description: "How thick the letters are."
  $options:
  - Light: "Light"
  - Normal: "Regular"
  - Medium: "Medium"
  - SemiBold: "Semi-bold"
  - Bold: "Bold"
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it to open these settings. Right-click it to open Halo or restart its search engine. When off, Ctrl + I in Halo still opens this window."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <imm.h>
#include <mmsystem.h>
#include <wincodec.h>
#include <wrl/client.h>

#include <algorithm>
#include <atomic>
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include <windhawk_tool_mod.h>

using Microsoft::WRL::ComPtr;

// The settings window (namespace haloset, at the end of the file) runs on its own thread. It reads
// the search engine's settings and plugins from this bridge and saves them with a line to it.
// One row of a Halo menu, drawn by the settings engine's styled menu (haloset::ShowMenu).
struct HaloMenuItem {
    int id = 0;
    std::wstring glyph, label, hint;
    bool checked = false, disabled = false, separator = false;
    std::vector<HaloMenuItem> sub;
};
namespace haloset {
void OpenSettingsWindow(int page = -1);
void CloseSettingsWindow();
int ShowTrayMenu(HWND owner, const POINT* at);
int ShowMenu(HWND owner, const std::vector<HaloMenuItem>& items, const POINT* at);
extern std::atomic<HWND> g_settingsWnd;
}  // namespace haloset

struct HaloBridgePlugin {
    std::wstring id, name, desc, keywords, defaultKeywords, version, author;
    bool disabled = false, hasSettings = false;
};
// A module's own settings panel, made by the engine as a child window inside a holder the
// settings window owns. px: its height in pixels.
struct HaloBridgePanel {
    HWND child = nullptr;
    int px = 0;
    bool failed = false;
};
namespace halobridge {
bool Panel(const std::wstring& id, HaloBridgePanel* out);
void DropPanel(const std::wstring& id);
bool Ready();
std::wstring Setting(const std::wstring& name, bool* found);
std::vector<HaloBridgePlugin> Plugins();
std::wstring TakeError();
bool SendLine(std::initializer_list<std::wstring> fields);
}  // namespace halobridge
std::wstring Hotkey_Format(UINT mods, UINT vk);
void HaloGlyph(ID2D1RenderTarget* rt, D2D1_RECT_F r, float alpha);
void HaloRecording(bool on);

namespace {

constexpr UINT WM_APP_LINES = WM_APP + 1;     // lParam: std::vector<std::string>*
constexpr UINT WM_APP_ENGINEDONE = WM_APP + 2;  // the engine said bye or its thread ended
constexpr UINT WM_APP_SETTINGS = WM_APP + 3;
constexpr UINT WM_APP_TRAY = WM_APP + 5;      // the tray icon's callback
constexpr UINT WM_APP_RECORD = WM_APP + 6;    // wParam 1: a key box in the settings listens
constexpr UINT WM_APP_APPMENU = WM_APP + 7;   // the engine answered a row's right-click menu
constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
constexpr UINT WM_APP_HOOKKEY = WM_APP + 4;   // wParam: hotkey slot
constexpr UINT_PTR kTimerFrame = 1;
constexpr UINT_PTR kTimerCaret = 2;
constexpr UINT_PTR kTimerHide = 3;
constexpr UINT kHideDelay = 100;
constexpr wchar_t kMsgClass[] = L"HaloLauncherMsg";
constexpr wchar_t kWndClass[] = L"HaloLauncher";

HANDLE g_thread = nullptr;
HANDLE g_ready = nullptr;
DWORD g_threadId = 0;

// ---------------------------------------------------------------- text helpers

std::wstring Wide(const std::string& s) {
    if (s.empty()) return {};
    int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring w(n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), w.data(), n);
    return w;
}

std::string Utf8(const std::wstring& w) {
    if (w.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), s.data(), n, nullptr, nullptr);
    return s;
}

std::string Escape(const std::string& s) {
    std::string o;
    o.reserve(s.size());
    for (char c : s) {
        if (c == '\\') o += "\\\\";
        else if (c == '\t') o += "\\t";
        else if (c == '\n') o += "\\n";
        else if (c != '\r') o += c;
    }
    return o;
}

std::vector<std::wstring> SplitLine(const std::string& line) {
    std::vector<std::wstring> out;
    std::string cur;
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '\t') {
            out.push_back(Wide(cur));
            cur.clear();
        } else if (c == '\\' && i + 1 < line.size()) {
            char n = line[++i];
            cur += n == 't' ? '\t' : n == 'n' ? '\n' : n;
        } else {
            cur += c;
        }
    }
    out.push_back(Wide(cur));
    return out;
}

std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t"), b = s.find_last_not_of(L" \t");
    return a == std::wstring::npos ? L"" : s.substr(a, b - a + 1);
}

bool EqualsNoCase(const std::wstring& a, const wchar_t* b) { return _wcsicmp(a.c_str(), b) == 0; }

// A short trace beside the engine's log: who opened, closed or took focus from the window.
void Trace(const wchar_t* fmt, ...) {
    static std::wstring path;
    if (path.empty()) {
        wchar_t base[MAX_PATH] = L"";
        GetEnvironmentVariableW(L"LOCALAPPDATA", base, MAX_PATH);
        path = std::wstring(base) + L"\\HaloLauncher\\mod.log";
        WIN32_FILE_ATTRIBUTE_DATA fa{};
        if (GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &fa) && fa.nFileSizeLow > 512 * 1024)
            DeleteFileW(path.c_str());
    }
    wchar_t msg[600];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf_s(msg, _TRUNCATE, fmt, args);
    va_end(args);
    SYSTEMTIME st;
    GetLocalTime(&st);
    wchar_t line[700];
    swprintf_s(line, L"%02d:%02d:%02d.%03d %s\r\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, msg);
    std::string out = Utf8(line);
    HANDLE f = CreateFileW(path.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f != INVALID_HANDLE_VALUE) {
        DWORD done;
        WriteFile(f, out.data(), (DWORD)out.size(), &done, nullptr);
        CloseHandle(f);
    }
}

// ---------------------------------------------------------------- hotkeys

constexpr UINT kCtrl = 1, kShift = 2, kAlt = 4, kWin = 8;

struct Hotkey {
    UINT mods = 0;
    UINT vk = 0;
    bool valid() const { return vk != 0; }
};

UINT KeyNameToVk(const std::wstring& n) {
    static const struct { const wchar_t* name; UINT vk; } table[] = {
        {L"Space", VK_SPACE}, {L"Tab", VK_TAB}, {L"Enter", VK_RETURN}, {L"Return", VK_RETURN},
        {L"Escape", VK_ESCAPE}, {L"Esc", VK_ESCAPE}, {L"Back", VK_BACK}, {L"Backspace", VK_BACK},
        {L"Delete", VK_DELETE}, {L"Insert", VK_INSERT}, {L"Home", VK_HOME}, {L"End", VK_END},
        {L"PageUp", VK_PRIOR}, {L"Prior", VK_PRIOR}, {L"PageDown", VK_NEXT}, {L"Next", VK_NEXT},
        {L"Up", VK_UP}, {L"Down", VK_DOWN}, {L"Left", VK_LEFT}, {L"Right", VK_RIGHT},
        {L"OemTilde", VK_OEM_3}, {L"Oem3", VK_OEM_3}, {L"OemPlus", VK_OEM_PLUS},
        {L"OemMinus", VK_OEM_MINUS}, {L"OemComma", VK_OEM_COMMA}, {L"OemPeriod", VK_OEM_PERIOD},
        {L"OemQuestion", VK_OEM_2}, {L"Oem2", VK_OEM_2}, {L"OemSemicolon", VK_OEM_1},
        {L"Oem1", VK_OEM_1}, {L"OemOpenBrackets", VK_OEM_4}, {L"Oem4", VK_OEM_4},
        {L"OemPipe", VK_OEM_5}, {L"Oem5", VK_OEM_5}, {L"OemCloseBrackets", VK_OEM_6},
        {L"Oem6", VK_OEM_6}, {L"OemQuotes", VK_OEM_7}, {L"Oem7", VK_OEM_7},
        {L"OemBackslash", VK_OEM_102}, {L"Oem102", VK_OEM_102}, {L"CapsLock", VK_CAPITAL},
        {L"Capital", VK_CAPITAL}, {L"PrintScreen", VK_SNAPSHOT}, {L"Snapshot", VK_SNAPSHOT},
        {L"Pause", VK_PAUSE}, {L"Apps", VK_APPS}, {L"Multiply", VK_MULTIPLY}, {L"Add", VK_ADD},
        {L"Subtract", VK_SUBTRACT}, {L"Divide", VK_DIVIDE}, {L"Decimal", VK_DECIMAL},
        {L"LWin", VK_LWIN}, {L"RWin", VK_RWIN},
    };
    for (auto& e : table)
        if (EqualsNoCase(n, e.name)) return e.vk;
    if (n.size() == 1) {
        wchar_t c = towupper(n[0]);
        if ((c >= L'A' && c <= L'Z') || (c >= L'0' && c <= L'9')) return c;
        SHORT s = VkKeyScanW(n[0]);
        if (s != -1) return LOBYTE(s);
    }
    if (n.size() == 2 && towupper(n[0]) == L'D' && n[1] >= L'0' && n[1] <= L'9') return n[1];
    if (n.size() >= 2 && towupper(n[0]) == L'F') {
        int f = _wtoi(n.c_str() + 1);
        if (f >= 1 && f <= 24) return VK_F1 + f - 1;
    }
    if (n.size() == 7 && _wcsnicmp(n.c_str(), L"NumPad", 6) == 0 && n[6] >= L'0' && n[6] <= L'9')
        return VK_NUMPAD0 + (n[6] - L'0');
    return 0;
}

Hotkey ParseHotkey(const std::wstring& text) {
    Hotkey hk;
    size_t pos = 0;
    while (pos <= text.size()) {
        size_t plus = text.find(L'+', pos);
        // "Ctrl + +" style: a trailing plus is the key itself.
        std::wstring tok = Trim(text.substr(pos, plus == std::wstring::npos ? std::wstring::npos : plus - pos));
        if (!tok.empty()) {
            if (EqualsNoCase(tok, L"Ctrl") || EqualsNoCase(tok, L"Control")) hk.mods |= kCtrl;
            else if (EqualsNoCase(tok, L"Shift")) hk.mods |= kShift;
            else if (EqualsNoCase(tok, L"Alt")) hk.mods |= kAlt;
            else if (EqualsNoCase(tok, L"Win") || EqualsNoCase(tok, L"Windows")) hk.mods |= kWin;
            else hk.vk = KeyNameToVk(tok);
        }
        if (plus == std::wstring::npos) break;
        pos = plus + 1;
    }
    return hk;
}

UINT CurrentMods() {
    UINT m = 0;
    if (GetAsyncKeyState(VK_CONTROL) < 0) m |= kCtrl;
    if (GetAsyncKeyState(VK_SHIFT) < 0) m |= kShift;
    if (GetAsyncKeyState(VK_MENU) < 0) m |= kAlt;
    if (GetAsyncKeyState(VK_LWIN) < 0 || GetAsyncKeyState(VK_RWIN) < 0) m |= kWin;
    return m;
}

// ---------------------------------------------------------------- state

struct Item {
    int index = 0;
    std::wstring title, sub, icon, glyph, glyphFont, badge, suggestion, path;
    bool round = false;
};

struct ResultBlock {
    std::wstring view = L"results";
    int total = 0, top = 0, sel = -1;
    std::vector<Item> items;
};

// One row's right-click menu as the engine sent it: the plugin's own actions, and the app id
// or path the Windows menu is built from.
struct AppMenuAction {
    std::wstring title, sub;
};
struct AppMenuData {
    int row = -1;
    std::wstring aumid, path;
    std::vector<AppMenuAction> flow;
};

struct GlobalKey {
    Hotkey hk;
    std::wstring keyword;   // empty: toggle the window
    bool registered = false;  // through RegisterHotKey; otherwise the keyboard hook serves it
};

struct Layout {
    float s = 1;            // pixels per DIP
    float W = 780, H = 58;  // DIPs
    float topH = 56, listY = 0, listH = 0, listW = 0, rowH = 58;
    int rows = 0;
    bool preview = false;
    int pxX = 0, pxY = 0, pxW = 0, pxH = 0;
};

struct Surface {
    HDC dc = nullptr;
    HBITMAP bitmap = nullptr;
    HGDIOBJ old = nullptr;
    void* bits = nullptr;
    int width = 0, height = 0;
};

struct State {
    HWND msgWnd = nullptr, wnd = nullptr;
    // A quiet show draws the window without taking the keyboard (used by the test driver).
    bool quiet = false, quietNext = false;

    // Windhawk settings
    std::wstring openKey;
    bool useFlowKeys = false;
    int backgroundOpacity = 55;
    bool blur = true;
    bool peekOnSpace = true;
    bool trayIcon = true;
    std::wstring fontFamily = L"FiraCode Nerd Font";  // every word Halo draws; sizes stay per place
    std::wstring fontWeight = L"Medium";
    bool trayAdded = false;
    bool menuOpen = false;   // one of Halo's styled menus has the focus; the launcher stays
    AppMenuData appMenu, appMenuPending;
    bool inAppMenu = false;
    int appMenuWant = -1;        // the row whose menu was asked for, -1 when none is wanted
    DWORD appMenuAsked = 0;
    POINT appMenuAt{};
    bool recording = false;  // a key box in the settings window listens, so Halo's keys stand down
    std::vector<HaloBridgePlugin> plugPending;

    // Engine
    bool engineReady = false;
    bool pendingShow = false;
    bool pendingKey = false;        // a keyword hotkey pressed while the engine was away
    bool keyShow = false;           // the next show comes from a shortcut: its words are not selected
    std::wstring pendingKeyword;
    DWORD pendingTick = 0;
    std::map<std::wstring, std::wstring> set, setPending;
    std::vector<std::pair<std::wstring, std::wstring>> hk, hkPending;
    bool inSet = false;
    ResultBlock res, resPending;
    bool inRes = false;
    std::wstring clock, date, pluginIcon;
    bool busy = false;
    DWORD busySince = 0;

    // Window
    bool visible = false;
    Layout lay;
    HMONITOR monitor = nullptr;
    DWORD shownAt = 0;
    bool animating = false;
    bool previewOn = false;
    bool movedByKeys = false;  // arrows or Tab moved the selection since the last edit
    bool caretOn = true;
    int hoverRow = -1;
    POINT lastMouse{-1, -1};
    bool selecting = false;

    // Query box
    std::wstring text;
    int caret = 0, anchor = 0;
    float scrollX = 0;
    std::vector<std::wstring> undo;

    // Hotkeys
    std::vector<GlobalKey> keys;
    HANDLE hookThread = nullptr;
    DWORD hookThreadId = 0;

    // Drawing
    ComPtr<ID2D1Factory> d2d;
    ComPtr<IDWriteFactory> dwrite;
    ComPtr<IWICImagingFactory> wic;
    ComPtr<ID2D1DCRenderTarget> rt;
    ComPtr<ID2D1SolidColorBrush> brush;
    ComPtr<ID2D1Layer> fadeLayer;
    ComPtr<IDWriteTextFormat> fQuery, fTitle, fSub, fClock, fHint, fPrevTitle, fPrevSub;
    ComPtr<IDWriteTextLayout> queryLayout;
    std::map<std::wstring, ComPtr<ID2D1Bitmap>> bitmaps;
    std::map<std::wstring, ComPtr<IDWriteTextFormat>> glyphFormats;
    Surface surface, faded;
};

[[clang::no_destroy]] State g;

std::wstring SetStr(const wchar_t* key, const wchar_t* def = L"") {
    auto it = g.set.find(key);
    return it == g.set.end() ? def : it->second;
}
int SetInt(const wchar_t* key, int def) {
    auto it = g.set.find(key);
    if (it == g.set.end() || it->second.empty()) return def;
    return (int)std::lround(_wtof(it->second.c_str()));
}
bool SetBool(const wchar_t* key, bool def) {
    auto it = g.set.find(key);
    if (it == g.set.end()) return def;
    return EqualsNoCase(it->second, L"True") || it->second == L"1";
}

// ---------------------------------------------------------------- the engine, inside this process
//
// The engine (Flow Launcher's own code plus Halo.Engine.dll) runs on its own thread here,
// started through hostfxr, the same loader Flow's exe uses. Lines go both ways through two
// function pointers: the mod fills toMod, the engine fills toEngine when it starts.
// The .NET runtime cannot be started twice in one process, so "restart the engine" means:
// this process ends with kExitRestart and the launcher in windhawk.exe starts a fresh one.

constexpr int kExitRestart = 75;      // the launcher starts the process again at once
constexpr int kExitEngineDied = 76;   // the launcher starts it again, with a pause, a few times at most
constexpr int kEngineRunning = INT_MIN;

struct EngineAbi {
    void(__cdecl* toMod)(const char*, int);
    void(__cdecl* toEngine)(const char*, int);
};

struct EngineHost {
    EngineAbi abi{};
    SRWLOCK callLock = SRWLOCK_INIT;  // shared while calling into the engine, exclusive to cut the link
    std::mutex inLock;
    std::string pending;
    HANDLE thread = nullptr;
    HANDLE bye = nullptr;  // set when the engine says its last word
    std::atomic<bool> closing{false};
    std::atomic<int> exitCode{0};
    std::atomic<int> result{kEngineRunning};
    DWORD startTick = 0;
};
[[clang::no_destroy]] EngineHost g_engine;
std::atomic<bool> g_unloading{false};  // Windhawk is unloading the mod: no restart

void CutEngineLink() {
    AcquireSRWLockExclusive(&g_engine.callLock);
    __atomic_store_n(&g_engine.abi.toEngine, nullptr, __ATOMIC_RELEASE);
    ReleaseSRWLockExclusive(&g_engine.callLock);
}

// Called by the engine, on any of its threads.
void __cdecl EngineToMod(const char* data, int length) {
    auto lines = std::make_unique<std::vector<std::string>>();
    bool bye = false;
    {
        std::lock_guard<std::mutex> guard(g_engine.inLock);
        g_engine.pending.append(data, length);
        size_t start = 0, nl;
        while ((nl = g_engine.pending.find('\n', start)) != std::string::npos) {
            std::string line = g_engine.pending.substr(start, nl - start);
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line == "restart") g_engine.exitCode = kExitRestart;
            else if (line == "bye") bye = true;
            lines->push_back(std::move(line));
            start = nl + 1;
        }
        g_engine.pending.erase(0, start);
    }
    if (!lines->empty() && g.msgWnd) {
        auto* raw = lines.release();
        if (!PostMessageW(g.msgWnd, WM_APP_LINES, 0, (LPARAM)raw)) delete raw;
    }
    if (bye) {
        // After "bye" the engine is shutting its runtime down, so nothing may call into it.
        // Its thread may never end (a plugin can leave a thread running), so "bye" is the end.
        CutEngineLink();
        SetEvent(g_engine.bye);
        if (g.msgWnd) PostMessageW(g.msgWnd, WM_APP_ENGINEDONE, 0, 0);
    }
}

bool PipeSendRaw(const std::string& line) {
    AcquireSRWLockShared(&g_engine.callLock);
    auto fn = __atomic_load_n(&g_engine.abi.toEngine, __ATOMIC_ACQUIRE);
    if (fn) {
        std::string data = line + "\n";
        fn(data.data(), (int)data.size());
    }
    ReleaseSRWLockShared(&g_engine.callLock);
    return fn != nullptr;
}

bool Send(std::initializer_list<std::wstring> fields) {
    std::string line;
    bool first = true;
    for (auto& f : fields) {
        if (!first) line += '\t';
        first = false;
        line += Escape(Utf8(f));
    }
    return PipeSendRaw(line);
}

bool Cmd(const wchar_t* name) { return Send({L"cmd", name}); }

std::wstring EngineDir() {
    PWSTR p = nullptr;
    std::wstring dir;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &p))) dir = p;
    CoTaskMemFree(p);
    return dir + L"\\HaloLauncher\\engine";
}

using HostfxrInit = int(__cdecl*)(int, const wchar_t**, const void*, void**);
using HostfxrRun = int(__cdecl*)(void*);
using HostfxrClose = int(__cdecl*)(void*);
using HostfxrErrorWriter = void(__cdecl*)(const wchar_t*);
using HostfxrSetErrorWriter = HostfxrErrorWriter(__cdecl*)(HostfxrErrorWriter);
struct HostfxrParams {
    size_t size;
    const wchar_t* hostPath;
    const wchar_t* dotnetRoot;
};

void __cdecl HostfxrError(const wchar_t* message) { Wh_Log(L"engine loader: %s", message); }

DWORD WINAPI EngineThreadProc(void*) {
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    std::wstring dir = EngineDir();
    std::wstring app = dir + L"\\Halo.Engine.dll";
    int rc = -1;
    HMODULE fx = nullptr;
    if (GetFileAttributesW(app.c_str()) == INVALID_FILE_ATTRIBUTES) {
        Wh_Log(L"Engine not found: %s", app.c_str());
        Trace(L"engine not found: %s", app.c_str());
    } else {
        fx = LoadLibraryExW((dir + L"\\hostfxr.dll").c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    }
    if (fx) {
        auto setWriter = (HostfxrSetErrorWriter)GetProcAddress(fx, "hostfxr_set_error_writer");
        auto init = (HostfxrInit)GetProcAddress(fx, "hostfxr_initialize_for_dotnet_command_line");
        auto run = (HostfxrRun)GetProcAddress(fx, "hostfxr_run_app");
        auto close = (HostfxrClose)GetProcAddress(fx, "hostfxr_close");
        if (setWriter) setWriter(HostfxrError);
        if (init && run && close) {
            std::wstring host = dir + L"\\Halo.Engine.exe";  // never run: names the app's folder for the loader
            wchar_t addr[32];
            swprintf(addr, 32, L"%llx", (unsigned long long)(uintptr_t)&g_engine.abi);
            const wchar_t* argv[] = {app.c_str(), L"--bridge", addr};
            HostfxrParams params{sizeof(params), host.c_str(), dir.c_str()};
            void* ctx = nullptr;
            rc = init(3, argv, &params, &ctx);
            if (rc >= 0 && ctx) {
                Wh_Log(L"Engine loaded in %u ms", GetTickCount() - g_engine.startTick);
                Trace(L"Engine loaded in %u ms", GetTickCount() - g_engine.startTick);
                rc = run(ctx);
                close(ctx);
            } else {
                Wh_Log(L"Engine loader refused: 0x%08X", (unsigned)rc);
                Trace(L"engine loader refused: 0x%08X", (unsigned)rc);
                if (ctx) close(ctx);
            }
        } else {
            Wh_Log(L"hostfxr.dll is missing its entry points");
        }
    } else if (GetFileAttributesW(app.c_str()) != INVALID_FILE_ATTRIBUTES) {
        Wh_Log(L"hostfxr.dll load failed: %u", GetLastError());
    }
    CutEngineLink();
    g_engine.result = rc;
    Wh_Log(L"Engine ended: %d", rc);
    Trace(L"engine exit %d", rc);
    if (g.msgWnd) PostMessageW(g.msgWnd, WM_APP_ENGINEDONE, 0, 0);
    CoUninitialize();
    return 0;
}

void StartEngine() {
    if (g_engine.thread) return;
    g_engine.bye = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_engine.abi.toMod = EngineToMod;
    g_engine.startTick = GetTickCount();
    // WPF's dispatcher and the plugins expect a main-thread sized stack.
    g_engine.thread = CreateThread(nullptr, 8u << 20, EngineThreadProc, nullptr, STACK_SIZE_PARAM_IS_A_RESERVATION,
                                   nullptr);
    if (!g_engine.thread) Wh_Log(L"Engine thread failed: %u", GetLastError());
}

// Asks the engine to save and leave, then waits a bounded time. Returns once it is gone or
// the time is up; the process exit after this stops whatever is left.
void StopEngine() {
    g_engine.closing = true;
    if (!g_engine.thread) return;
    DWORD t = GetTickCount();
    if (PipeSendRaw("exit") && WaitForSingleObject(g_engine.bye, 7000) != WAIT_OBJECT_0)
        Wh_Log(L"Engine did not say bye in 7 s");
    CutEngineLink();
    if (WaitForSingleObject(g_engine.thread, 3000) != WAIT_OBJECT_0) Wh_Log(L"Engine thread still running, leaving it");
    Wh_Log(L"Engine stopped in %u ms", GetTickCount() - t);
    Trace(L"engine stopped in %u ms", GetTickCount() - t);
}

// Ends this process so the launcher starts a fresh one: the only way to restart .NET.
void RestartProcess(int code) {
    if (!g_engine.exitCode) g_engine.exitCode = code;
    if (g.msgWnd) PostMessageW(g.msgWnd, WM_CLOSE, 0, 0);
}

// ---------------------------------------------------------------- colours and fonts

D2D1_COLOR_F Rgb(UINT rgb, float a = 1.0f) {
    return D2D1::ColorF(((rgb >> 16) & 255) / 255.0f, ((rgb >> 8) & 255) / 255.0f, (rgb & 255) / 255.0f, a);
}

// Catppuccin Mocha, as the owner's Flow theme sets it.
constexpr UINT cBase = 0x181825, cBorder = 0x313244, cAccent = 0x89b4fa, cGlyph = 0xa6adc8,
               cText = 0xcdd6f4, cSelection = 0x7496d1, cTitle = 0xbac2de, cSub = 0xa6adc8,
               cSeparator = 0x585b70, cRow = 0x313244, cSearch = 0x9399b2, cHint = 0x6c7086,
               cPreviewSub = 0x45475a, cCrust = 0x11111b, cMochaBase = 0x1e1e2e;

// Flow keeps a thin square edge in the border colour under the corners Windows rounds.
constexpr float kEdge = 1;

DWRITE_FONT_WEIGHT WeightOf(const std::wstring& w) {
    static const struct { const wchar_t* n; int v; } t[] = {
        {L"Thin", 100}, {L"ExtraLight", 200}, {L"UltraLight", 200}, {L"Light", 300},
        {L"Normal", 400}, {L"Regular", 400}, {L"Medium", 500}, {L"SemiBold", 600},
        {L"DemiBold", 600}, {L"Bold", 700}, {L"ExtraBold", 800}, {L"UltraBold", 800},
        {L"Black", 900}, {L"Heavy", 900}, {L"ExtraBlack", 950},
    };
    for (auto& e : t)
        if (EqualsNoCase(w, e.n)) return (DWRITE_FONT_WEIGHT)e.v;
    int n = _wtoi(w.c_str());
    return n >= 1 && n <= 999 ? (DWRITE_FONT_WEIGHT)n : DWRITE_FONT_WEIGHT_NORMAL;
}

DWRITE_FONT_STYLE StyleOf(const std::wstring& s) {
    if (EqualsNoCase(s, L"Italic")) return DWRITE_FONT_STYLE_ITALIC;
    if (EqualsNoCase(s, L"Oblique")) return DWRITE_FONT_STYLE_OBLIQUE;
    return DWRITE_FONT_STYLE_NORMAL;
}

ComPtr<IDWriteTextFormat> MakeFormat(const std::wstring& family, const std::wstring& weight,
                                     const std::wstring& style, float size, bool trim) {
    ComPtr<IDWriteTextFormat> f;
    const wchar_t* fam = family.empty() ? L"Segoe UI" : family.c_str();
    if (FAILED(g.dwrite->CreateTextFormat(fam, nullptr, WeightOf(weight), StyleOf(style),
                                          DWRITE_FONT_STRETCH_NORMAL, size, L"", &f)))
        g.dwrite->CreateTextFormat(L"Segoe UI", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
                                   DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &f);
    if (f) {
        f->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        if (trim) {
            DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
            ComPtr<IDWriteInlineObject> sign;
            g.dwrite->CreateEllipsisTrimmingSign(f.Get(), &sign);
            f->SetTrimming(&t, sign.Get());
        }
    }
    return f;
}

void ResetFormats() {
    g.fQuery.Reset();
    g.fTitle.Reset();
    g.fSub.Reset();
    g.fClock.Reset();
    g.fHint.Reset();
    g.fPrevTitle.Reset();
    g.fPrevSub.Reset();
    g.glyphFormats.clear();
    g.queryLayout.Reset();
}

// True when Windows has the family installed. DirectWrite would quietly swap in another font.
bool FontInstalled(const std::wstring& family) {
    ComPtr<IDWriteFontCollection> fonts;
    UINT32 index = 0;
    BOOL found = FALSE;
    if (family.empty() || FAILED(g.dwrite->GetSystemFontCollection(&fonts, TRUE))) return false;
    return SUCCEEDED(fonts->FindFamilyName(family.c_str(), &index, &found)) && found;
}

void EnsureFormats() {
    if (g.fQuery) return;
    // One font for all of Halo's text (its own setting, default FiraCode Nerd Font Medium). A
    // missing family falls back to Segoe UI at the same size, never a smaller one.
    std::wstring fam = FontInstalled(g.fontFamily) ? g.fontFamily : L"Segoe UI";
    const std::wstring& wt = g.fontWeight;
    g.fQuery = MakeFormat(fam, wt, SetStr(L"QueryBoxFontStyle", L"Normal"), (float)SetInt(L"QueryBoxFontSize", 16), false);
    g.fTitle = MakeFormat(fam, wt, SetStr(L"ResultFontStyle", L"Normal"), (float)SetInt(L"ResultItemFontSize", 16), true);
    g.fSub = MakeFormat(fam, wt, SetStr(L"ResultSubFontStyle", L"Normal"), (float)SetInt(L"ResultSubItemFontSize", 13), true);
    g.fClock = MakeFormat(fam, wt, L"Normal", 14, false);
    g.fClock->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
    // The Alt+number hint measures 14 on Flow's real window.
    g.fHint = MakeFormat(fam, wt, L"Normal", 14, false);
    g.fHint->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    g.fHint->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    g.fPrevTitle = MakeFormat(fam, wt, L"Normal", 15, false);
    g.fPrevTitle->SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP);
    g.fPrevTitle->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    g.fPrevSub = MakeFormat(fam, wt, L"Normal", 12, false);
    g.fPrevSub->SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP);
    g.fPrevSub->SetLineSpacing(DWRITE_LINE_SPACING_METHOD_UNIFORM, 18, 14);
}

IDWriteTextFormat* GlyphFormat(const std::wstring& fontSpec, float size) {
    // WPF font specs look like "file:///C:/x/#Family Name" or "/Resources/#Segoe Fluent Icons".
    std::wstring family = fontSpec;
    size_t hash = family.rfind(L'#');
    if (hash != std::wstring::npos) family = family.substr(hash + 1);
    if (family.empty()) family = L"Segoe Fluent Icons";
    std::wstring key = family + L"|" + std::to_wstring((int)size);
    auto it = g.glyphFormats.find(key);
    if (it != g.glyphFormats.end()) return it->second.Get();
    auto f = MakeFormat(family, L"Normal", L"Normal", size, false);
    if (f) {
        f->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        f->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }
    g.glyphFormats[key] = f;
    return f.Get();
}

// ---------------------------------------------------------------- surface and bitmaps

void FreeSurface(Surface& s) {
    if (s.dc) {
        SelectObject(s.dc, s.old);
        DeleteObject(s.bitmap);
        DeleteDC(s.dc);
    }
    s = {};
}

bool EnsureSurface(Surface& s, int width, int height) {
    if (s.dc && s.width == width && s.height == height) return true;
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
    s.bits = bits;
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

void ResetTarget() {
    g.bitmaps.clear();
    g.brush.Reset();
    g.fadeLayer.Reset();
    g.rt.Reset();
}

bool EnsureTarget() {
    if (g.rt) return true;
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
    if (FAILED(g.d2d->CreateDCRenderTarget(&props, &g.rt))) return false;
    g.rt->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &g.brush);
    g.rt->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    return true;
}

ID2D1Bitmap* LoadBitmap(const std::wstring& path) {
    if (path.empty() || !g.rt) return nullptr;
    auto it = g.bitmaps.find(path);
    if (it != g.bitmaps.end()) return it->second.Get();
    if (g.bitmaps.size() > 400) g.bitmaps.clear();
    ComPtr<ID2D1Bitmap> bmp;
    ComPtr<IWICBitmapDecoder> dec;
    if (SUCCEEDED(g.wic->CreateDecoderFromFilename(path.c_str(), nullptr, GENERIC_READ,
                                                   WICDecodeMetadataCacheOnDemand, &dec))) {
        ComPtr<IWICBitmapFrameDecode> frame;
        ComPtr<IWICFormatConverter> conv;
        if (SUCCEEDED(dec->GetFrame(0, &frame)) && SUCCEEDED(g.wic->CreateFormatConverter(&conv)) &&
            SUCCEEDED(conv->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
                                       nullptr, 0, WICBitmapPaletteTypeMedianCut)))
            g.rt->CreateBitmapFromWicBitmap(conv.Get(), nullptr, &bmp);
    }
    g.bitmaps[path] = bmp;  // a failed load is remembered too, so it is not retried every frame
    return bmp.Get();
}

// ---------------------------------------------------------------- glass

// The launcher grid's own material, the same as every Seamless settings window: accent
// acrylic with an almost clear tint (state 4, flags 2, 0x012E1E1E) so only the blur shows,
// blur-behind over the whole window and the frame extended. The page paints Mocha crust
// over it. The system backdrop (DWMSBT_TRANSIENTWINDOW) read as a light grey slab and went
// flat when the window lost focus; this one stays dark and the same either way. Windows
// rounds the window and draws its shadow, so nothing of ours sticks out past the corners.
struct HaloAccentPolicy { int state, flags, abgr, animation; };
struct HaloCompositionData { DWORD attribute; void* data; SIZE_T size; };

void ApplyBackdrop() {
    if (!g.wnd) return;
    BOOL on = TRUE;
    DwmSetWindowAttribute(g.wnd, 20, &on, sizeof(on));  // dark
    DwmSetWindowAttribute(g.wnd, 3, &on, sizeof(on));   // no open and close zoom, Halo fades itself
    UINT corner = 2;                                    // round
    DwmSetWindowAttribute(g.wnd, 33, &corner, sizeof(corner));
    int backdrop = 1;  // DWMSBT_NONE: never the system's light acrylic
    DwmSetWindowAttribute(g.wnd, 38, &backdrop, sizeof(backdrop));
    using SetComposition_t = BOOL(WINAPI*)(HWND, HaloCompositionData*);
    static auto setComposition =
        (SetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    DWM_BLURBEHIND bb{};
    if (g.blur) {
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        bb.fEnable = TRUE;
        bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
        DwmEnableBlurBehindWindow(g.wnd, &bb);
        if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
        if (setComposition) {
            HaloAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};  // as the launcher grid
            HaloCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(g.wnd, &data);
        }
    } else {
        if (setComposition) {
            HaloAccentPolicy policy{0, 0, 0, 0};
            HaloCompositionData data{19, &policy, sizeof(policy)};
            setComposition(g.wnd, &data);
        }
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = FALSE;
        DwmEnableBlurBehindWindow(g.wnd, &bb);
    }
    MARGINS sheet{-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(g.wnd, &sheet);
}

// ---------------------------------------------------------------- layout

float AnimLength() {
    if (!SetBool(L"UseAnimation", true)) return 0;
    std::wstring speed = SetStr(L"AnimationSpeed", L"Medium");
    if (EqualsNoCase(speed, L"Slow")) return 560;
    if (EqualsNoCase(speed, L"Fast")) return 160;
    if (EqualsNoCase(speed, L"Custom")) return (float)SetInt(L"CustomAnimationLength", 360);
    return 360;
}

float EaseCircle(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    if (t < 0.5f) return (1 - std::sqrt(1 - 4 * t * t)) / 2;
    float u = -2 * t + 2;
    return (std::sqrt(1 - u * u) + 1) / 2;
}

HMONITOR PickMonitor() {
    std::wstring screen = SetStr(L"SearchWindowScreen", L"Primary");
    if (EqualsNoCase(screen, L"Cursor")) {
        POINT p;
        GetCursorPos(&p);
        return MonitorFromPoint(p, MONITOR_DEFAULTTOPRIMARY);
    }
    if (EqualsNoCase(screen, L"Focus")) {
        HWND fg = GetForegroundWindow();
        if (fg) return MonitorFromWindow(fg, MONITOR_DEFAULTTOPRIMARY);
    }
    POINT zero{0, 0};
    return MonitorFromPoint(zero, MONITOR_DEFAULTTOPRIMARY);
}

float MonitorScale(HMONITOR mon) {
    using Fn = HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*);
    static auto fn = (Fn)GetProcAddress(LoadLibraryW(L"shcore.dll"), "GetDpiForMonitor");
    UINT dx = 96, dy = 96;
    if (fn) fn(mon, 0, &dx, &dy);
    return dx / 96.0f;
}

void ComputeLayout() {
    Layout& L = g.lay;
    if (!g.monitor) g.monitor = PickMonitor();
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(g.monitor, &mi);
    L.s = MonitorScale(g.monitor);
    // Layout numbers are the content inside the thin edge, as in Flow: its window is
    // WindowSize wide and the edge takes one unit from every side.
    float outerW = (float)std::max(300, SetInt(L"WindowSize", 780));
    L.W = outerW - 2 * kEdge;
    float qh = (float)SetInt(L"WindowHeightSize", 42);
    L.topH = 7 + qh + 7;
    L.rowH = (float)SetInt(L"ItemHeightSize", 58);
    int maxRows = std::max(1, SetInt(L"MaxResultsToShow", 5));
    int n = (int)g.res.items.size();
    // Flow's "KeepMaxResults" only locks resizing by dragging; the list still shrinks to its rows.
    L.rows = std::min(n, maxRows);
    L.preview = g.previewOn && n > 0;
    L.listY = L.topH + 1;
    L.listH = L.rows ? 10 + L.rows * L.rowH + 10 : 0;
    if (L.preview) L.listH = std::max(L.listH, 380.0f);
    // With the preview open the list and the preview share the width 1 : 0.85, with a
    // 20 wide divider strip between them and at least 244 for the preview.
    L.listW = L.W;
    if (L.preview) L.listW = std::max(80.0f, std::min(std::floor((L.W - 20) / 1.85f), L.W - 20 - 244));
    L.H = L.topH + (L.rows ? 1 + L.listH : 0);

    float waW = (mi.rcWork.right - mi.rcWork.left) / L.s, waH = (mi.rcWork.bottom - mi.rcWork.top) / L.s;
    float left = (waW - outerW) / 2, top = (waH - qh) / 4;
    std::wstring align = SetStr(L"SearchWindowAlign", L"Center");
    if (EqualsNoCase(align, L"CenterTop")) top = 10;
    else if (EqualsNoCase(align, L"LeftTop")) { left = 10; top = 10; }
    else if (EqualsNoCase(align, L"RightTop")) { left = waW - outerW - 10; top = 10; }
    else if (EqualsNoCase(align, L"Custom")) {
        left += SetInt(L"CustomWindowLeft", 0);
        top += SetInt(L"CustomWindowTop", 0);
    }
    L.pxW = (int)std::lround(outerW * L.s);
    L.pxH = (int)std::lround((L.H + 2 * kEdge) * L.s);
    L.pxX = mi.rcWork.left + (int)std::lround(left * L.s);
    L.pxY = mi.rcWork.top + (int)std::lround(top * L.s);
}

// ---------------------------------------------------------------- query box

float QueryLeft() { return 18; }
float QueryRight() { return g.lay.W - 50; }

void BuildQueryLayout() {
    EnsureFormats();
    g.queryLayout.Reset();
    g.dwrite->CreateTextLayout(g.text.c_str(), (UINT32)g.text.size(), g.fQuery.Get(), 100000,
                               g.lay.topH, &g.queryLayout);
}

float CaretX(int pos) {
    if (!g.queryLayout) BuildQueryLayout();
    if (!g.queryLayout) return 0;
    FLOAT x = 0, y = 0;
    DWRITE_HIT_TEST_METRICS m{};
    g.queryLayout->HitTestTextPosition((UINT32)std::clamp(pos, 0, (int)g.text.size()), FALSE, &x, &y, &m);
    return x;
}

void KeepCaretVisible() {
    float width = QueryRight() - QueryLeft();
    float x = CaretX(g.caret);
    if (x - g.scrollX > width - 2) g.scrollX = x - width + 2;
    if (x - g.scrollX < 0) g.scrollX = x;
    if (g.scrollX < 0) g.scrollX = 0;
}

int HitQuery(float dipX) {
    if (!g.queryLayout) BuildQueryLayout();
    if (!g.queryLayout) return 0;
    BOOL trailing = FALSE, inside = FALSE;
    DWRITE_HIT_TEST_METRICS m{};
    g.queryLayout->HitTestPoint(dipX - QueryLeft() + g.scrollX, 5, &trailing, &inside, &m);
    return std::clamp((int)m.textPosition + (trailing ? 1 : 0), 0, (int)g.text.size());
}

void Render();

// The first open used to pay for every lazy thing the draw needs: the text formats, the
// render target, the drawing surface. On a cold start that ran to seconds between the key
// press and the window (0.5.5's first open sat 10 s in there, and a second press in the
// meantime made it flash open and closed). The draw tools are built here instead, while
// the engine starts, so the first open draws like every later one.
void WarmRender() {
    if (!g.wnd || g.visible) return;
    EnsureFormats();
    ComputeLayout();
    Layout& L = g.lay;
    EnsureSurface(g.surface, L.pxW, L.pxH);
    EnsureTarget();
    Trace(L"draw tools warmed");
}

void TextChanged(bool notify) {
    g.queryLayout.Reset();
    g.caret = std::clamp(g.caret, 0, (int)g.text.size());
    g.anchor = std::clamp(g.anchor, 0, (int)g.text.size());
    KeepCaretVisible();
    g.movedByKeys = false;
    if (notify) Send({L"q", g.text});
    g.caretOn = true;
    if (g.visible) {
        SetTimer(g.wnd, kTimerCaret, GetCaretBlinkTime() == INFINITE ? 530 : GetCaretBlinkTime(), nullptr);
        Render();
    }
}

void PushUndo() {
    if (g.undo.empty() || g.undo.back() != g.text) {
        g.undo.push_back(g.text);
        if (g.undo.size() > 60) g.undo.erase(g.undo.begin());
    }
}

bool HasSelection() { return g.caret != g.anchor; }

void DeleteSelection() {
    int a = std::min(g.caret, g.anchor), b = std::max(g.caret, g.anchor);
    g.text.erase(a, b - a);
    g.caret = g.anchor = a;
}

void InsertText(const std::wstring& s) {
    PushUndo();
    if (HasSelection()) DeleteSelection();
    std::wstring clean;
    for (wchar_t c : s)
        if (c >= 32 && c != 127) clean += c;
        else if (c == L'\t' || c == L'\n') clean += L' ';
    g.text.insert(g.caret, clean);
    g.caret += (int)clean.size();
    g.anchor = g.caret;
    TextChanged(true);
}

int WordLeft(int p) {
    while (p > 0 && iswspace(g.text[p - 1])) p--;
    while (p > 0 && !iswspace(g.text[p - 1])) p--;
    return p;
}
int WordRight(int p) {
    int n = (int)g.text.size();
    while (p < n && !iswspace(g.text[p])) p++;
    while (p < n && iswspace(g.text[p])) p++;
    return p;
}

void MoveCaret(int pos, bool extend) {
    g.caret = std::clamp(pos, 0, (int)g.text.size());
    if (!extend) g.anchor = g.caret;
    KeepCaretVisible();
    g.caretOn = true;
    Render();
}

void CopySelection(bool cut) {
    if (!HasSelection()) return;
    int a = std::min(g.caret, g.anchor), b = std::max(g.caret, g.anchor);
    std::wstring s = g.text.substr(a, b - a);
    if (OpenClipboard(g.wnd)) {
        EmptyClipboard();
        HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, (s.size() + 1) * sizeof(wchar_t));
        if (h) {
            memcpy(GlobalLock(h), s.c_str(), (s.size() + 1) * sizeof(wchar_t));
            GlobalUnlock(h);
            if (!SetClipboardData(CF_UNICODETEXT, h)) GlobalFree(h);
        }
        CloseClipboard();
    }
    if (cut) {
        PushUndo();
        DeleteSelection();
        TextChanged(true);
    }
}

void Paste() {
    if (!OpenClipboard(g.wnd)) return;
    std::wstring s;
    if (HANDLE h = GetClipboardData(CF_UNICODETEXT)) {
        if (auto* p = (const wchar_t*)GlobalLock(h)) {
            s = p;
            GlobalUnlock(h);
        }
    }
    CloseClipboard();
    if (!s.empty()) InsertText(s);
}

// ---------------------------------------------------------------- drawing

void FillRound(D2D1_RECT_F r, float radius, D2D1_COLOR_F c) {
    g.brush->SetColor(c);
    g.rt->FillRoundedRectangle(D2D1::RoundedRect(r, radius, radius), g.brush.Get());
}

// Our hover and focus colours: blue #89B4FA to mauve #CBA6F7, left to right (or top to
// bottom), at the given strength.
ComPtr<ID2D1LinearGradientBrush> MochaGradient(D2D1_RECT_F r, float alpha, bool vertical = false) {
    ComPtr<ID2D1GradientStopCollection> stops;
    D2D1_GRADIENT_STOP s[2] = {{0, Rgb(0x89b4fa, alpha)}, {1, Rgb(0xcba6f7, alpha)}};
    g.rt->CreateGradientStopCollection(s, 2, &stops);
    ComPtr<ID2D1LinearGradientBrush> b;
    if (stops)
        g.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, r.top),
                                                vertical ? D2D1::Point2F(r.left, r.bottom) : D2D1::Point2F(r.right, r.top)),
            stops.Get(), &b);
    return b;
}

// The selected row, as the hover of every Seamless card: a surface0 card with a faint
// blue to mauve wash and a gradient ring.
void FillSelection(D2D1_RECT_F r, float radius) {
    FillRound(r, radius, Rgb(cRow, 0.55f));
    D2D1_ROUNDED_RECT rr = D2D1::RoundedRect(r, radius, radius);
    if (auto wash = MochaGradient(r, 0.10f)) g.rt->FillRoundedRectangle(rr, wash.Get());
    float px = 1 / g.lay.s;
    D2D1_RECT_F in = D2D1::RectF(r.left + px / 2, r.top + px / 2, r.right - px / 2, r.bottom - px / 2);
    if (auto ring = MochaGradient(r, 0.75f))
        g.rt->DrawRoundedRectangle(D2D1::RoundedRect(in, radius - px / 2, radius - px / 2), ring.Get(), px);
}

void DrawStr(const std::wstring& s, IDWriteTextFormat* f, D2D1_RECT_F r, D2D1_COLOR_F c) {
    if (s.empty() || !f) return;
    g.brush->SetColor(c);
    g.rt->DrawText(s.c_str(), (UINT32)s.size(), f, r, g.brush.Get(), D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

float LineHeight(IDWriteTextFormat* f) {
    ComPtr<IDWriteTextLayout> l;
    DWRITE_TEXT_METRICS m{};
    if (f && SUCCEEDED(g.dwrite->CreateTextLayout(L"Ag", 2, f, 1000, 1000, &l))) l->GetMetrics(&m);
    return m.height;
}

const Item* SelectedItem() {
    for (auto& it : g.res.items)
        if (it.index == g.res.sel) return &it;
    return nullptr;
}

float TextHeight(const std::wstring& s, IDWriteTextFormat* f, float width) {
    ComPtr<IDWriteTextLayout> l;
    DWRITE_TEXT_METRICS m{};
    if (!s.empty() && f && SUCCEEDED(g.dwrite->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, width, 10000, &l)))
        l->GetMetrics(&m);
    return m.height;
}

// Flow's own magnifier (its shape is a ring with a round-ended handle in a 24 unit box).
void DrawSearchIcon(float x, float y, D2D1_COLOR_F c) {
    g.brush->SetColor(c);
    g.rt->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x + 8.94f, y + 8.92f), 6.05f, 6.05f), g.brush.Get(), 1.66f);
    g.rt->DrawLine(D2D1::Point2F(x + 13.3f, y + 13.3f), D2D1::Point2F(x + 21.0f, y + 21.0f), g.brush.Get(), 1.93f);
    g.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x + 21.0f, y + 21.0f), 0.96f, 0.96f), g.brush.Get());
}

void DrawIcon(const Item& it, D2D1_RECT_F box, UINT glyphColor, float glyphSize) {
    bool glyphs = SetBool(L"UseGlyphIcons", true);
    if (glyphs && !it.glyph.empty()) {
        DrawStr(it.glyph, GlyphFormat(it.glyphFont, glyphSize), box, Rgb(glyphColor));
        return;
    }
    ID2D1Bitmap* bmp = LoadBitmap(it.icon);
    if (bmp) {
        if (it.round) {
            ComPtr<ID2D1EllipseGeometry> geo;
            float rx = (box.right - box.left) / 2, ry = (box.bottom - box.top) / 2;
            g.d2d->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(box.left + rx, box.top + ry), rx, ry), &geo);
            g.rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), geo.Get()), nullptr);
            g.rt->DrawBitmap(bmp, box, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
            g.rt->PopLayer();
        } else {
            g.rt->DrawBitmap(bmp, box, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
        }
    }
    if (SetBool(L"ShowBadges", false) && !it.badge.empty()) {
        if (ID2D1Bitmap* badge = LoadBitmap(it.badge)) {
            float size = (box.right - box.left) * 0.6f;
            g.rt->DrawBitmap(badge, D2D1::RectF(box.right - size + 4, box.bottom - size + 4, box.right + 4, box.bottom + 4),
                             1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
        }
    }
}

// Copies the drawn frame into the window. The window is glass, so the alpha of every
// pixel is kept and Windows blends it over the blur.
void Present(float alpha) {
    Layout& L = g.lay;
    RECT now{};
    GetWindowRect(g.wnd, &now);
    if (now.left != L.pxX || now.top != L.pxY || now.right - now.left != L.pxW || now.bottom - now.top != L.pxH) {
        // While it is on screen (results arriving grow it, most of all on the first open after
        // a start, when the list begins empty) the old picture is kept and the new one copied
        // in right after a frame was shown, so Windows never shows a blank window between them.
        bool onScreen = IsWindowVisible(g.wnd);
        if (onScreen) DwmFlush();
        SetWindowPos(g.wnd, nullptr, L.pxX, L.pxY, L.pxW, L.pxH,
                     SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW | (onScreen ? 0 : SWP_NOCOPYBITS));
    }
    HDC from = g.surface.dc;
    int a = (int)std::lround(255 * std::clamp(alpha, 0.0f, 1.0f));
    if (a < 255 && EnsureSurface(g.faded, L.pxW, L.pxH)) {
        auto* in = (const BYTE*)g.surface.bits;
        auto* out = (BYTE*)g.faded.bits;
        size_t bytes = (size_t)L.pxW * L.pxH * 4;
        for (size_t i = 0; i < bytes; i++) out[i] = (BYTE)((in[i] * a + 127) / 255);
        from = g.faded.dc;
    }
    GdiFlush();
    if (HDC dc = GetDC(g.wnd)) {
        BitBlt(dc, 0, 0, L.pxW, L.pxH, from, 0, 0, SRCCOPY);
        ReleaseDC(g.wnd, dc);
    }
}

void Render() {
    if (!g.visible || !g.wnd) return;
    ComputeLayout();
    Layout& L = g.lay;
    if (!EnsureSurface(g.surface, L.pxW, L.pxH) || !EnsureTarget()) return;
    EnsureFormats();
    RECT rc{0, 0, L.pxW, L.pxH};
    if (FAILED(g.rt->BindDC(g.surface.dc, &rc))) return;

    float animLen = AnimLength();
    float elapsed = (float)(GetTickCount() - g.shownAt);
    float t = animLen > 0 ? EaseCircle(elapsed / animLen) : 1;
    float fade = animLen > 0 ? EaseCircle(elapsed / (animLen * 2 / 3)) : 1;
    g.animating = animLen > 0 && elapsed < animLen;
    float slide = (1 - t) * 12;

    g.rt->BeginDraw();
    g.rt->SetTransform(D2D1::Matrix3x2F::Scale(L.s, L.s));
    g.rt->Clear(D2D1::ColorF(0, 0, 0, 0));

    // Window: the tint over the glass, then Flow's thin square edge. Windows rounds the
    // window and clips that edge at the corners, and the borders mod draws the ring.
    float px = 1 / L.s;
    // Glass: Mocha crust laid flat over the blur, 55% like every Seamless window. Without
    // blur: solid Mocha base.
    float outerW = L.W + 2 * kEdge, outerH = L.H + 2 * kEdge;
    g.brush->SetColor(g.blur ? Rgb(cCrust, g.backgroundOpacity / 100.0f) : Rgb(cMochaBase));
    g.rt->FillRectangle(D2D1::RectF(0, 0, outerW, outerH), g.brush.Get());
    g.rt->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
    g.brush->SetColor(Rgb(cBorder));
    g.rt->FillRectangle(D2D1::RectF(0, 0, outerW, kEdge), g.brush.Get());
    g.rt->FillRectangle(D2D1::RectF(0, outerH - kEdge, outerW, outerH), g.brush.Get());
    g.rt->FillRectangle(D2D1::RectF(0, kEdge, kEdge, outerH - kEdge), g.brush.Get());
    g.rt->FillRectangle(D2D1::RectF(outerW - kEdge, kEdge, outerW, outerH - kEdge), g.brush.Get());
    g.rt->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    // The glass is whole from the first frame; only what sits on it fades in. Fading the tint
    // too showed the bare blur and a flat brown slab for the first frames of every open.
    bool fadeOn = fade < 1 && (g.fadeLayer || SUCCEEDED(g.rt->CreateLayer(&g.fadeLayer)));
    if (fadeOn)
        g.rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), nullptr, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
                                              D2D1::IdentityMatrix(), fade),
                        g.fadeLayer.Get());
    // Everything below is laid out inside the edge.
    g.rt->SetTransform(D2D1::Matrix3x2F::Translation(kEdge, kEdge) * D2D1::Matrix3x2F::Scale(L.s, L.s));

    // Query box.
    float qTop = 7, qBottom = L.topH - 7;
    if (!g.queryLayout) BuildQueryLayout();
    DWRITE_TEXT_METRICS qm{};
    if (g.queryLayout) g.queryLayout->GetMetrics(&qm);
    float lineH = qm.height > 0 ? qm.height : LineHeight(g.fQuery.Get());
    float textY = qTop + ((qBottom - qTop) - lineH) / 2;
    g.rt->PushAxisAlignedClip(D2D1::RectF(16, qTop, QueryRight(), qBottom), D2D1_ANTIALIAS_MODE_ALIASED);
    const Item* selItem = SelectedItem();
    if (selItem && !g.text.empty() && g.res.view == L"results" && g.scrollX == 0 &&
        selItem->suggestion.size() > g.text.size() &&
        _wcsnicmp(selItem->suggestion.c_str(), g.text.c_str(), g.text.size()) == 0) {
        std::wstring sug = g.text + selItem->suggestion.substr(g.text.size());
        DrawStr(sug, g.fQuery.Get(), D2D1::RectF(QueryLeft(), textY, 100000, textY + lineH + 4), Rgb(cGlyph));
    }
    if (g.text.empty() && SetBool(L"ShowPlaceholder", true)) {
        std::wstring hint = SetStr(L"PlaceholderText");
        if (hint.empty()) hint = L"Type here to search";
        DrawStr(hint, g.fQuery.Get(), D2D1::RectF(QueryLeft(), textY, QueryRight(), textY + lineH + 4), Rgb(cHint));
    }
    if (g.queryLayout) {
        if (HasSelection()) {
            float a = CaretX(std::min(g.caret, g.anchor)), b = CaretX(std::max(g.caret, g.anchor));
            g.brush->SetColor(Rgb(cSelection));
            g.rt->FillRectangle(D2D1::RectF(QueryLeft() + a - g.scrollX, textY, QueryLeft() + b - g.scrollX,
                                            textY + lineH), g.brush.Get());
        }
        g.brush->SetColor(Rgb(cText));
        g.rt->DrawTextLayout(D2D1::Point2F(QueryLeft() - g.scrollX, textY), g.queryLayout.Get(), g.brush.Get());
        if (g.caretOn && GetForegroundWindow() == g.wnd) {
            float cx = std::round((QueryLeft() + CaretX(g.caret) - g.scrollX) * L.s) / L.s;
            g.brush->SetColor(Rgb(cText));
            g.rt->FillRectangle(D2D1::RectF(cx, textY + 1, cx + std::max(px, 1.0f), textY + lineH - 1), g.brush.Get());
        }
    }
    g.rt->PopAxisAlignedClip();

    // Clock and date, only while the box is empty.
    bool useClock = SetBool(L"UseClock", true), useDate = SetBool(L"UseDate", true);
    if (g.text.empty() && (useClock || useDate)) {
        // Stacked, right edge 54 from the side; the lower line carries 3 below it.
        float right = L.W - 54;
        float h = LineHeight(g.fClock.Get());
        float both = (useClock && useDate) ? h * 2 + 3 : h;
        float y = (L.topH - both) / 2 + slide;
        D2D1_COLOR_F c = Rgb(cGlyph, t);
        if (useClock) {
            DrawStr(g.clock, g.fClock.Get(), D2D1::RectF(right - 300, y, right, y + h + 2), c);
            y += h;
        }
        if (useDate) DrawStr(g.date, g.fClock.Get(), D2D1::RectF(right - 300, y, right, y + h + 2), c);
    }

    // The active plugin's icon (32, centred, 18 from the side), or the magnifier (a 24
    // shape in a 32 box that sits 8 from the top and the side).
    if (ID2D1Bitmap* pico = LoadBitmap(g.pluginIcon)) {
        float top = (L.topH - 32) / 2 + slide;
        g.rt->DrawBitmap(pico, D2D1::RectF(L.W - 18 - 32, top, L.W - 18, top + 32), t,
                         D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    } else {
        DrawSearchIcon(L.W - 8 - 32, 8 + (L.topH - 8 - 32) / 2 + slide, Rgb(cSearch, t));
    }

    if (L.rows) {
        g.brush->SetColor(Rgb(cSeparator));
        g.rt->FillRectangle(D2D1::RectF(0, L.topH, L.W, L.topH + 1), g.brush.Get());
    }

    // Busy line.
    if (g.busy) {
        float phase = (float)((GetTickCount() - g.busySince) % 1600) / 1600.0f;
        float x = -100 + phase * (L.W + 100);
        g.rt->PushAxisAlignedClip(D2D1::RectF(12, L.topH - 2, L.W - 12, L.topH + 1), D2D1_ANTIALIAS_MODE_ALIASED);
        g.brush->SetColor(Rgb(cAccent));
        g.rt->FillRectangle(D2D1::RectF(x, L.topH - 2, x + 100, L.topH), g.brush.Get());
        g.rt->PopAxisAlignedClip();
    }

    // Results.
    if (L.rows) {
        float titleH = LineHeight(g.fTitle.Get()), subH = LineHeight(g.fSub.Get());
        bool hints = SetBool(L"ShowOpenResultHotkey", true) && g.res.view == L"results";
        std::wstring hintMod = SetStr(L"OpenResultModifiers", L"Alt");
        float y = L.listY + 10;
        g.rt->PushAxisAlignedClip(D2D1::RectF(0, L.listY, L.listW, L.listY + L.listH), D2D1_ANTIALIAS_MODE_ALIASED);
        int shown = 0;
        for (auto& it : g.res.items) {
            if (shown >= (L.preview ? (int)((L.listH - 20) / L.rowH) : L.rows)) break;
            bool selected = it.index == g.res.sel;
            float left = 10, right = L.listW - 10;
            if (selected) {
                FillSelection(D2D1::RectF(left, y, right, y + L.rowH), 8);
                D2D1_RECT_F bullet = D2D1::RectF(left + 5, y + (L.rowH - 30) / 2, left + 8, y + (L.rowH + 30) / 2);
                if (auto bb = MochaGradient(bullet, 1.0f, true))
                    g.rt->FillRoundedRectangle(D2D1::RoundedRect(bullet, 1.5f, 1.5f), bb.Get());
            }
            // The icon is centred in the 47 left of the 60 wide image area after the 4 wide
            // bullet and a 9 gap, then pulled 2 to the left, which lands on a half unit.
            float iconCx = left + 4 + 9 + (60 - 4 - 9) / 2.0f - 1;
            DrawIcon(it, D2D1::RectF(iconCx - 16, y + (L.rowH - 32) / 2, iconCx + 16, y + (L.rowH + 32) / 2),
                     selected ? cText : cGlyph, 25);
            float textLeft = left + 60 + 6, textRight = right - 10;
            if (hints && it.index < 10) {
                std::wstring label = hintMod + L"+" + std::to_wstring((it.index + 1) % 10);
                ComPtr<IDWriteTextLayout> hl;
                DWRITE_TEXT_METRICS hm{};
                if (SUCCEEDED(g.dwrite->CreateTextLayout(label.c_str(), (UINT32)label.size(), g.fHint.Get(), 200, 30, &hl))) {
                    hl->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
                    hl->GetMetrics(&hm);
                }
                float bw = hm.width + 12, bh = hm.height + 8;
                D2D1_RECT_F badge = D2D1::RectF(right - 10 - 12 - bw, y + (L.rowH - bh) / 2, right - 10 - 12,
                                                y + (L.rowH + bh) / 2);
                FillRound(badge, 4, D2D1::ColorF(0x8A / 255.0f, 0x8A / 255.0f, 0x8A / 255.0f, 0x13 / 255.0f));
                DrawStr(label, g.fHint.Get(), badge, Rgb(selected ? cAccent : cHint));
                textRight = badge.left - 12;
            }
            if (it.sub.empty()) {
                DrawStr(it.title, g.fTitle.Get(), D2D1::RectF(textLeft, y + (L.rowH - titleH) / 2, textRight,
                                                               y + (L.rowH + titleH) / 2 + 2), Rgb(selected ? cText : cTitle));
            } else {
                float pairTop = y + (L.rowH - (titleH + 2 + subH)) / 2;
                DrawStr(it.title, g.fTitle.Get(), D2D1::RectF(textLeft, pairTop, textRight, pairTop + titleH + 1),
                        Rgb(selected ? cText : cTitle));
                DrawStr(it.sub, g.fSub.Get(), D2D1::RectF(textLeft, pairTop + titleH + 2, textRight,
                                                           pairTop + titleH + 2 + subH + 1), Rgb(selected ? cTitle : cSub));
            }
            y += L.rowH;
            shown++;
        }
        g.rt->PopAxisAlignedClip();

        // Scrollbar thumb.
        int page = std::max(1, shown);
        if (g.res.total > page) {
            float track = L.listH - 20, th = std::max(24.0f, track * page / g.res.total);
            float ty = L.listY + 10 + (track - th) * g.res.top / std::max(1, g.res.total - page);
            D2D1_RECT_F thumb = D2D1::RectF(L.listW - 6, ty, L.listW - 2, ty + th);
            if (auto tb = MochaGradient(thumb, 1.0f, true))  // every scrollbar thumb is the blue to mauve gradient
                g.rt->FillRoundedRectangle(D2D1::RoundedRect(thumb, 2, 2), tb.Get());
        }

        // Preview pane, with Flow's spacing: a divider line 5 past the list, then the
        // big icon 16 down, the title 6 below it, a line and the details.
        if (L.preview) {
            float pl = L.listW + 20, pr = L.W - 10, bottom = L.listY + L.listH - 5;
            g.brush->SetColor(Rgb(cBorder));
            g.rt->FillRectangle(D2D1::RectF(L.listW + 5, L.listY, L.listW + 5 + px, L.listY + L.listH), g.brush.Get());
            if (selItem) {
                g.rt->PushAxisAlignedClip(D2D1::RectF(pl, L.listY, pr, bottom), D2D1_ANTIALIAS_MODE_ALIASED);
                float cx = (pl + pr) / 2, py = L.listY + 16;
                DrawIcon(*selItem, D2D1::RectF(cx - 48, py, cx + 48, py + 96), cAccent, 90);
                py += 96 + 6;
                float titleBlock = TextHeight(selItem->title, g.fPrevTitle.Get(), pr - pl);
                DrawStr(selItem->title, g.fPrevTitle.Get(), D2D1::RectF(pl, py, pr, py + titleBlock + 2), Rgb(cAccent));
                py += titleBlock + 16;
                if (!selItem->sub.empty()) {
                    py += 15;
                    g.brush->SetColor(Rgb(cSeparator));
                    g.rt->FillRectangle(D2D1::RectF(pl, py, pr - 5, py + 1), g.brush.Get());
                    py += 1 + 5 + 6;
                    DrawStr(selItem->sub, g.fPrevSub.Get(), D2D1::RectF(pl + 5, py, pr, bottom - 10), Rgb(cSub));
                }
                g.rt->PopAxisAlignedClip();
            }
        }
    }

    if (fadeOn) g.rt->PopLayer();
    g.rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (g.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
        ResetTarget();
        return;
    }
    Present(1);
    bool needFrames = g.animating || g.busy;
    if (needFrames) SetTimer(g.wnd, kTimerFrame, 12, nullptr);
    else KillTimer(g.wnd, kTimerFrame);
}

// ---------------------------------------------------------------- show and hide

void ForceForeground(HWND w) {
    SetForegroundWindow(w);
    if (GetForegroundWindow() == w) return;
    // A tap of an unused key makes this process the last one to get input.
    INPUT in[2]{};
    in[0].type = in[1].type = INPUT_KEYBOARD;
    in[0].ki.wVk = in[1].ki.wVk = 0xE8;
    in[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, in, sizeof(INPUT));
    SetForegroundWindow(w);
    if (GetForegroundWindow() == w) return;
    DWORD other = GetWindowThreadProcessId(GetForegroundWindow(), nullptr), me = GetCurrentThreadId();
    if (other && other != me) {
        AttachThreadInput(me, other, TRUE);
        BringWindowToTop(w);
        SetForegroundWindow(w);
        AttachThreadInput(me, other, FALSE);
    }
}

void PlayOpenSound() {
    if (!SetBool(L"UseSound", false)) return;
    std::wstring file = SetStr(L"SoundFile");
    if (file.empty()) return;
    DWORD v = (DWORD)std::clamp(SetInt(L"SoundVolume", 50), 0, 100) * 0xFFFF / 100;
    waveOutSetVolume(nullptr, v | (v << 16));
    PlaySoundW(file.c_str(), nullptr, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

void ShowLauncher(bool selectAll) {
    if (!g.wnd) return;
    bool was = g.visible;
    g.visible = true;
    if (!was) {
        g.monitor = PickMonitor();
        g.shownAt = GetTickCount();
        g.hoverRow = -1;
        g.previewOn = SetBool(L"AlwaysPreview", false);
        GetCursorPos(&g.lastMouse);
        PlayOpenSound();
    }
    if (selectAll) {
        g.anchor = 0;
        g.caret = (int)g.text.size();
    }
    g.caretOn = true;
    if (!was) {
        g.quiet = g.quietNext;
        g.quietNext = false;
        ApplyBackdrop();
        unsigned long t0 = GetTickCount();
        Render();  // sizes the window before it appears
        unsigned long t1 = GetTickCount();
        // Shown cloaked, drawn, then uncloaked once Windows has composed it: the first frame
        // people see already has the blur and the new contents, never the last open's picture.
        BOOL cloak = TRUE;
        DwmSetWindowAttribute(g.wnd, 13 /* DWMWA_CLOAK */, &cloak, sizeof(cloak));
        SetWindowPos(g.wnd, HWND_TOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
        // The open animation counts from here, so it starts at its first frame on screen
        // instead of jumping in halfway. The draw tools themselves were warmed when the
        // engine became ready; only a settings change rebuilds them here.
        g.shownAt = GetTickCount();
        // Focus is taken while still hidden, so anything activation repaints is never seen.
        if (!g.quiet) {
            ForceForeground(g.wnd);
            SetFocus(g.wnd);
        }
        Render();
        DwmFlush();
        unsigned long t2 = GetTickCount();
        cloak = FALSE;
        DwmSetWindowAttribute(g.wnd, 13, &cloak, sizeof(cloak));
        if (t1 - t0 > 60 || t2 - t1 > 60)
            Trace(L"slow open draw: prep %lu ms, show+draw+flush %lu ms", t1 - t0, t2 - t1);
    }
    if (!g.quiet && (was || GetForegroundWindow() != g.wnd)) {
        ForceForeground(g.wnd);  // already open, or the first try lost the race: one more try
        SetFocus(g.wnd);
    }
    if (!was)
        Trace(L"shown%s, foreground %s", g.quiet ? L" quietly" : L"",
              GetForegroundWindow() == g.wnd ? L"ours" : L"NOT ours");
    SetTimer(g.wnd, kTimerCaret, GetCaretBlinkTime() == INFINITE ? 530 : GetCaretBlinkTime(), nullptr);
    Render();
}

int g_hideNoOwnerChecks = 0;

// Screen capture tools whose window takes focus to let you pick a window or a region.
bool IsCaptureTool(HWND hwnd) {
    if (!hwnd) return false;
    wchar_t cls[64] = L"";
    GetClassNameW(hwnd, cls, 64);
    if (wcsncmp(cls, L"SeamlessSnip", 12) == 0) return true;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    HANDLE proc = pid ? OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid) : nullptr;
    if (!proc) return false;
    wchar_t path[MAX_PATH] = L"";
    DWORD n = MAX_PATH;
    bool found = false;
    if (QueryFullProcessImageNameW(proc, 0, path, &n)) {
        static const wchar_t* tools[] = {L"ShareX.exe",      L"SnippingTool.exe", L"ScreenClippingHost.exe",
                                         L"Greenshot.exe",   L"ScreenToGif.exe",  L"flameshot.exe",
                                         L"Lightshot.exe",   L"PicPick.exe",      L"Snagit32.exe",
                                         L"SnagitCapture.exe"};
        PCWSTR name = PathFindFileNameW(path);
        for (auto t : tools)
            if (_wcsicmp(name, t) == 0) found = true;
    }
    CloseHandle(proc);
    return found;
}

void HideLauncher() {
    if (!g.visible) return;
    g.visible = false;
    KillTimer(g.wnd, kTimerFrame);
    KillTimer(g.wnd, kTimerCaret);
    KillTimer(g.wnd, kTimerHide);
    ShowWindow(g.wnd, SW_HIDE);
    g.selecting = false;
    g.quiet = false;
}

void RequestToggle() {
    Trace(L"toggle asked (engine ready %d, visible %d)", g.engineReady, g.visible);
    g.keyShow = false;
    if (!g.engineReady) {
        g.pendingShow = true;
        g.pendingKey = false;
        g.pendingTick = GetTickCount();
        return;
    }
    Send({L"toggle"});
}

// ---------------------------------------------------------------- Peek link

bool PeekFile(const std::wstring& path) {
    if (path.empty() || GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES) return false;
    HWND peek = FindWindowExW(HWND_MESSAGE, nullptr, L"WindhawkPeekMsg", nullptr);
    if (!peek) return false;
    COPYDATASTRUCT cds{};
    cds.dwData = 0x4F4C4148;  // 'HALO'
    cds.cbData = (DWORD)((path.size() + 1) * sizeof(wchar_t));
    cds.lpData = (PVOID)path.c_str();
    DWORD_PTR result = 0;
    return SendMessageTimeoutW(peek, WM_COPYDATA, (WPARAM)g.wnd, (LPARAM)&cds, SMTO_ABORTIFHUNG, 1500, &result) &&
           result == 1;
}

// ---------------------------------------------------------------- global hotkeys

struct HookKey {
    UINT mods, vk;
};
SRWLOCK g_hookLock = SRWLOCK_INIT;
[[clang::no_destroy]] std::vector<HookKey> g_hookKeys;  // slot = index into g.keys
std::atomic<int> g_winTapSlot{-1};                      // slot served by a lone tap of the Windows key
std::atomic<bool> g_winAlone{false};
std::atomic<DWORD> g_lastWinTap{0};  // when the last Windows-key tap was served, for "open" asks
HHOOK g_hook = nullptr;

UINT AsyncMods() {
    UINT m = 0;
    if (GetAsyncKeyState(VK_CONTROL) < 0) m |= kCtrl;
    if (GetAsyncKeyState(VK_SHIFT) < 0) m |= kShift;
    if (GetAsyncKeyState(VK_MENU) < 0) m |= kAlt;
    if (GetAsyncKeyState(VK_LWIN) < 0 || GetAsyncKeyState(VK_RWIN) < 0) m |= kWin;
    return m;
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wp, LPARAM lp) {
    if (code != HC_ACTION) return CallNextHookEx(nullptr, code, wp, lp);
    auto* k = (KBDLLHOOKSTRUCT*)lp;
    bool down = wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN;
    bool isWin = k->vkCode == VK_LWIN || k->vkCode == VK_RWIN;
    if (k->flags & LLKHF_INJECTED) {
        // Another tool that swallows its own Win chord (Seamless Clipboard on Win+V) sends an
        // unused key while Win is held, so that press was a chord, not a lone tap.
        if (down && !isWin) g_winAlone = false;
        return CallNextHookEx(nullptr, code, wp, lp);
    }
    int tapSlot = g_winTapSlot.load();
    if (isWin && tapSlot >= 0) {
        if (down) {
            // Only a clean tap counts: Shift+Win and friends belong to other tools.
            if (!(GetAsyncKeyState(k->vkCode) < 0)) g_winAlone = (AsyncMods() & ~kWin) == 0;
        } else if (g_winAlone.exchange(false)) {
            // An unused key between Win down and Win up stops the Start menu opening. Input
            // sent from here lands after the key being handled, so the real Win up is held
            // back and sent again after the unused key: Windows sees Win, E8, Win up, never
            // a lone tap, and Start stays shut.
            INPUT in[3]{};
            in[0].type = in[1].type = in[2].type = INPUT_KEYBOARD;
            in[0].ki.wVk = in[1].ki.wVk = 0xE8;
            in[1].ki.dwFlags = KEYEVENTF_KEYUP;
            in[2].ki.wVk = (WORD)k->vkCode;
            in[2].ki.wScan = (WORD)k->scanCode;
            in[2].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_EXTENDEDKEY;
            g_lastWinTap = GetTickCount();
            if (SendInput(3, in, sizeof(INPUT)) == 3) {
                if (g.msgWnd) PostMessageW(g.msgWnd, WM_APP_HOOKKEY, (WPARAM)tapSlot, 0);
                return 1;
            }
            if (g.msgWnd) PostMessageW(g.msgWnd, WM_APP_HOOKKEY, (WPARAM)tapSlot, 0);
        }
        return CallNextHookEx(nullptr, code, wp, lp);
    }
    if (down && !isWin) {
        g_winAlone = false;
        UINT mods = AsyncMods();
        int slot = -1;
        AcquireSRWLockShared(&g_hookLock);
        for (size_t i = 0; i < g_hookKeys.size(); i++)
            if (g_hookKeys[i].vk == k->vkCode && g_hookKeys[i].mods == mods && g_hookKeys[i].vk) slot = (int)i;
        ReleaseSRWLockShared(&g_hookLock);
        if (slot >= 0) {
            if (g.msgWnd) PostMessageW(g.msgWnd, WM_APP_HOOKKEY, (WPARAM)slot, 0);
            return 1;
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

DWORD WINAPI HookThreadProc(void*) {
    g_hook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandleW(nullptr), 0);
    if (!g_hook) Wh_Log(L"Keyboard hook failed: %u", GetLastError());
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) DispatchMessageW(&msg);
    if (g_hook) UnhookWindowsHookEx(g_hook);
    g_hook = nullptr;
    return 0;
}

void StopHook() {
    if (!g.hookThread) return;
    PostThreadMessageW(g.hookThreadId, WM_QUIT, 0, 0);
    WaitForSingleObject(g.hookThread, 3000);
    CloseHandle(g.hookThread);
    g.hookThread = nullptr;
}

void UnregisterKeys() {
    for (size_t i = 0; i < g.keys.size(); i++)
        if (g.keys[i].registered) UnregisterHotKey(g.msgWnd, (int)i + 1);
    g.keys.clear();
    AcquireSRWLockExclusive(&g_hookLock);
    g_hookKeys.clear();
    ReleaseSRWLockExclusive(&g_hookLock);
    g_winTapSlot = -1;
}

void RegisterKeys() {
    UnregisterKeys();
    if (g.recording) return;  // back when the key box stops listening
    auto add = [](const std::wstring& text, const std::wstring& keyword) {
        Hotkey hk = ParseHotkey(text);
        if (!hk.valid()) return;
        for (auto& k : g.keys)
            if (k.hk.vk == hk.vk && k.hk.mods == hk.mods) return;
        g.keys.push_back({hk, keyword, false});
    };
    add(g.openKey, L"");
    if (g.useFlowKeys) {
        add(SetStr(L"Hotkey"), L"");
        for (auto& h : g.hk) add(h.first, h.second);
    }
    std::vector<HookKey> hookKeys(g.keys.size(), HookKey{0, 0});
    bool needHook = false;
    int tap = -1;
    for (size_t i = 0; i < g.keys.size(); i++) {
        GlobalKey& k = g.keys[i];
        bool winAlone = (k.hk.vk == VK_LWIN || k.hk.vk == VK_RWIN) && k.hk.mods == 0;
        if (winAlone) {
            tap = (int)i;
            needHook = true;
            continue;
        }
        UINT mods = MOD_NOREPEAT;
        if (k.hk.mods & kCtrl) mods |= MOD_CONTROL;
        if (k.hk.mods & kShift) mods |= MOD_SHIFT;
        if (k.hk.mods & kAlt) mods |= MOD_ALT;
        if (k.hk.mods & kWin) mods |= MOD_WIN;
        if (k.hk.mods & kWin) {
            // Keys with Win in them are mostly reserved by the shell, so the hook serves those.
            hookKeys[i] = {k.hk.mods, k.hk.vk};
            needHook = true;
        } else if (RegisterHotKey(g.msgWnd, (int)i + 1, mods, k.hk.vk)) {
            k.registered = true;
        } else {
            // Another program holds this key. Flow leaves such a key with its holder, and
            // so does Halo: taking it through the hook would break that program.
            Wh_Log(L"Hotkey %u+%u belongs to another program (%u), left alone", k.hk.mods, k.hk.vk, GetLastError());
            Trace(L"hotkey %u+%u is held by another program, left alone", k.hk.mods, k.hk.vk);
        }
    }
    AcquireSRWLockExclusive(&g_hookLock);
    g_hookKeys = hookKeys;
    ReleaseSRWLockExclusive(&g_hookLock);
    g_winTapSlot = tap;
    int taken = 0, hooked = 0;
    for (size_t i = 0; i < g.keys.size(); i++) {
        if (g.keys[i].registered) taken++;
        else if (hookKeys[i].vk) hooked++;
    }
    Trace(L"keys: %d of %d taken, %d more through the key hook, Windows-key tap %s", taken, (int)g.keys.size(), hooked,
          tap >= 0 ? L"on" : L"off");
    if (needHook && !g.hookThread) {
        g.hookThread = CreateThread(nullptr, 0, HookThreadProc, nullptr, 0, &g.hookThreadId);
    } else if (!needHook) {
        StopHook();
    }
}

void FireKey(size_t slot) {
    if (slot >= g.keys.size()) return;
    const GlobalKey& k = g.keys[slot];
    if (k.keyword.empty()) {
        RequestToggle();
        return;
    }
    Trace(L"key for '%s' (engine ready %d)", k.keyword.c_str(), g.engineReady);
    g.keyShow = true;
    if (g.engineReady) {
        Send({L"hotkey", k.keyword});
        return;
    }
    g.pendingShow = false;
    g.pendingKey = true;
    g.pendingKeyword = k.keyword;
    g.pendingTick = GetTickCount();
}

// ---------------------------------------------------------------- engine messages

void LoadSettings() {
    PCWSTR s = Wh_GetStringSetting(L"openKey");
    g.openKey = s ? s : L"";
    Wh_FreeStringSetting(s);
    g.useFlowKeys = Wh_GetIntSetting(L"useFlowKeys") != 0;
    g.backgroundOpacity = std::clamp(Wh_GetIntSetting(L"backgroundOpacity"), 0, 100);
    g.blur = Wh_GetIntSetting(L"blur") != 0;
    g.peekOnSpace = Wh_GetIntSetting(L"peekOnSpace") != 0;
    g.trayIcon = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    s = Wh_GetStringSetting(L"fontFamily");
    g.fontFamily = s && *s ? s : L"FiraCode Nerd Font";
    Wh_FreeStringSetting(s);
    s = Wh_GetStringSetting(L"fontWeight");
    g.fontWeight = s && *s ? s : L"Medium";
    Wh_FreeStringSetting(s);
}

// What the settings window reads; written on this thread, read on the settings thread.
struct Bridge {
    std::mutex lock;
    bool ready = false;
    std::map<std::wstring, std::wstring> set;
    std::vector<HaloBridgePlugin> plugins;
    std::map<std::wstring, HaloBridgePanel> panels;
    std::wstring error;
};
[[clang::no_destroy]] Bridge g_bridge;
constexpr UINT WM_APP_SETTINGS_PANELS = WM_APP + 9;  // the settings window's "a panel came or went" (wParam 1: ask again)

void ReloadSettingsWindow() {
    if (HWND s = haloset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* its reload message */, 0, 0);
}

void OpenHaloSettings(int page = -1) {
    HideLauncher();
    AllowSetForegroundWindow(ASFW_ANY);
    haloset::OpenSettingsWindow(page);
}

void BeginSettingsBlock() {
    if (g.inSet) return;
    g.inSet = true;
    g.setPending.clear();
    g.hkPending.clear();
    g.plugPending.clear();
}

void OnLine(const std::string& raw) {
    auto f = SplitLine(raw);
    const std::wstring& op = f[0];
    auto field = [&](size_t i) -> const std::wstring& {
        static const std::wstring empty;
        return i < f.size() ? f[i] : empty;
    };
    if (op == L"it") {
        if (!g.inRes) return;
        Item it;
        it.index = _wtoi(field(1).c_str());
        it.title = field(2);
        it.sub = field(3);
        it.icon = field(4);
        it.glyph = field(5);
        it.glyphFont = field(6);
        it.badge = field(7);
        it.round = field(8) == L"1";
        it.suggestion = field(9);
        it.path = field(10);
        g.resPending.items.push_back(std::move(it));
    } else if (op == L"res") {
        g.resPending = {};
        g.resPending.view = field(1);
        g.resPending.total = _wtoi(field(2).c_str());
        g.resPending.top = _wtoi(field(3).c_str());
        g.resPending.sel = _wtoi(field(4).c_str());
        g.inRes = true;
    } else if (op == L"resend") {
        g.inRes = false;
        g.res = std::move(g.resPending);
        g.resPending = {};
        g.hoverRow = -1;
        Render();
    } else if (op == L"set") {
        BeginSettingsBlock();
        g.setPending[field(1)] = field(2);
    } else if (op == L"hk") {
        BeginSettingsBlock();
        g.hkPending.push_back({field(1), field(2)});
    } else if (op == L"plug") {
        // id, name, description, keywords, off, own settings, version, author, default keywords
        BeginSettingsBlock();
        HaloBridgePlugin p;
        p.id = field(1);
        p.name = field(2);
        p.desc = field(3);
        p.keywords = field(4);
        p.disabled = field(5) == L"1";
        p.hasSettings = field(6) == L"1";
        p.version = field(7);
        p.author = field(8);
        p.defaultKeywords = field(9);
        g.plugPending.push_back(std::move(p));
    } else if (op == L"setend") {
        g.inSet = false;
        g.set = std::move(g.setPending);
        g.hk = std::move(g.hkPending);
        g.setPending.clear();
        g.hkPending.clear();
        {
            std::lock_guard<std::mutex> guard(g_bridge.lock);
            g_bridge.ready = true;
            g_bridge.set = g.set;
            if (!g.plugPending.empty()) g_bridge.plugins = std::move(g.plugPending);
        }
        g.plugPending.clear();
        ResetFormats();
        RegisterKeys();
        Render();
        ReloadSettingsWindow();
    } else if (op == L"cm") {
        g.appMenuPending = {};
        g.appMenuPending.row = _wtoi(field(1).c_str());
        g.appMenuPending.aumid = field(3);
        g.appMenuPending.path = field(4);
        g.inAppMenu = true;
    } else if (op == L"ci") {
        if (g.inAppMenu) g.appMenuPending.flow.push_back({field(2), field(3)});
    } else if (op == L"cmend") {
        g.inAppMenu = false;
        g.appMenu = std::move(g.appMenuPending);
        g.appMenuPending = {};
        // A late answer (the engine was busy, the owner moved on) opens nothing.
        if (g.appMenu.row == g.appMenuWant && GetTickCount() - g.appMenuAsked < 2500 && g.visible)
            PostMessageW(g.wnd, WM_APP_APPMENU, 0, 0);
        g.appMenuWant = -1;
    } else if (op == L"panel" || op == L"panelgone") {
        // panel: id, child window, height in pixels, failed. panelgone: id, child window.
        HWND child = (HWND)(ULONG_PTR)wcstoull(field(2).c_str(), nullptr, 10);
        {
            std::lock_guard<std::mutex> guard(g_bridge.lock);
            if (op == L"panel") {
                HaloBridgePanel p;
                p.child = child;
                p.px = _wtoi(field(3).c_str());
                p.failed = field(4) == L"1";
                g_bridge.panels[field(1)] = p;
            } else {
                auto it = g_bridge.panels.find(field(1));
                if (it != g_bridge.panels.end() && (!child || it->second.child == child)) g_bridge.panels.erase(it);
            }
        }
        if (HWND s = haloset::g_settingsWnd) PostMessageW(s, WM_APP_SETTINGS_PANELS, 0, 0);
    } else if (op == L"settings") {
        OpenHaloSettings();
    } else if (op == L"seterr") {
        {
            std::lock_guard<std::mutex> guard(g_bridge.lock);
            g_bridge.error = field(1);
        }
        ReloadSettingsWindow();
    } else if (op == L"front") {
        // A plugin's own settings window: the engine may not take the focus, Halo can while
        // its settings window is in front, so Halo brings it up.
        HWND h = (HWND)(ULONG_PTR)wcstoull(field(1).c_str(), nullptr, 10);
        DWORD pid = 0, fgPid = 0;
        GetWindowThreadProcessId(GetForegroundWindow(), &fgPid);
        if (IsWindow(h) && GetWindowThreadProcessId(h, &pid) && fgPid == GetCurrentProcessId()) {
            if (IsIconic(h)) ShowWindow(h, SW_RESTORE);
            SetForegroundWindow(h);
        }
    } else if (op == L"ready") {
        g.engineReady = true;
        Wh_Log(L"Engine ready: %s plugins in %s ms", field(1).c_str(), field(2).c_str());
        {
            // A new engine: the old one's panels are gone, open cards ask the new one.
            std::lock_guard<std::mutex> guard(g_bridge.lock);
            g_bridge.panels.clear();
        }
        if (HWND s = haloset::g_settingsWnd) PostMessageW(s, WM_APP_SETTINGS_PANELS, 1, 0);
        WarmRender();
        // A key pressed while the engine was starting is answered now, unless it is stale.
        bool fresh = GetTickCount() - g.pendingTick < 25000;
        if (g.pendingKey && fresh) Send({L"hotkey", g.pendingKeyword});
        else if (g.pendingShow && fresh) Send({L"show"});
        g.pendingShow = g.pendingKey = false;
    } else if (op == L"clock") {
        g.clock = field(1);
        g.date = field(2);
        if (g.text.empty()) Render();
    } else if (op == L"text") {
        if (g.text != field(1)) {
            g.text = field(1);
            g.caret = g.anchor = (int)g.text.size();
            g.scrollX = 0;
            TextChanged(false);
        }
    } else if (op == L"caret") {
        // A shortcut's words: caret after them, nothing selected.
        g.caret = g.anchor = (int)g.text.size();
        g.caretOn = true;
        Render();
    } else if (op == L"vis") {
        Trace(L"engine vis %s (text '%s', %d results)", field(1).c_str(), g.text.c_str(), (int)g.res.items.size());
        if (field(1) == L"1") {
            // A shortcut's words are never selected, not even for the first frame.
            ShowLauncher(field(2) == L"1" && !g.keyShow);
            g.keyShow = false;
        } else {
            HideLauncher();
        }
    } else if (op == L"busy") {
        bool on = field(1) == L"1";
        if (on && !g.busy) g.busySince = GetTickCount();
        g.busy = on;
        Render();
    } else if (op == L"pico") {
        g.pluginIcon = field(1);
        Render();
    } else if (op == L"msg") {
        Wh_Log(L"Message: %s | %s", field(1).c_str(), field(2).c_str());
    } else if (op == L"fatal") {
        Wh_Log(L"Engine failed: %s", field(1).c_str());
    }
}

// ---------------------------------------------------------------- keys in the window

bool Matches(const wchar_t* setting, UINT vk, UINT mods) {
    Hotkey hk = ParseHotkey(SetStr(setting));
    return hk.valid() && hk.vk == vk && hk.mods == mods;
}

std::wstring ModsField(UINT mods) {
    std::wstring s = L"0000";
    if (mods & kCtrl) s[0] = L'1';
    if (mods & kShift) s[1] = L'1';
    if (mods & kAlt) s[2] = L'1';
    if (mods & kWin) s[3] = L'1';
    return s;
}

void TogglePreview() {
    const Item* it = SelectedItem();
    if (it && PeekFile(it->path)) return;
    g.previewOn = !g.previewOn;
    Render();
}

void RequestAppMenuForSelection();

bool OnKeyDown(UINT vk, UINT mods) {
    bool atEnd = g.caret == (int)g.text.size() && !HasSelection();
    bool results = g.res.view == L"results";

    // Space previews a file, but only after the arrows or Tab moved the selection.
    if (vk == VK_SPACE && mods == 0 && g.peekOnSpace && g.movedByKeys) {
        const Item* it = SelectedItem();
        if (it && PeekFile(it->path)) return true;
    }

    // Keys Flow handles before its own key table.
    if (mods == 0 || mods == kShift) {
        if (vk == VK_DOWN && mods == 0) { g.movedByKeys = true; Cmd(L"SelectNextItem"); return true; }
        if (vk == VK_UP && mods == 0) { g.movedByKeys = true; Cmd(L"SelectPrevItem"); return true; }
        if (vk == VK_NEXT && mods == 0) { g.movedByKeys = true; Cmd(L"SelectNextPage"); return true; }
        if (vk == VK_PRIOR && mods == 0) { g.movedByKeys = true; Cmd(L"SelectPrevPage"); return true; }
        if (vk == VK_RIGHT && mods == 0 && atEnd && results && !g.res.items.empty()) { Cmd(L"LoadContextMenu"); return true; }
        if (vk == VK_LEFT && mods == 0 && g.caret == 0 && !HasSelection() && !results) { Cmd(L"Esc"); return true; }
    }
    if (vk == VK_BACK && mods == kCtrl && atEnd && results &&
        (g.text.find(L'\\') != std::wstring::npos || g.text.find(L'/') != std::wstring::npos)) {
        Cmd(L"Backspace");
        return true;
    }

    // Keys the owner set in Flow. Later entries win, as in Flow's own table.
    static const struct { const wchar_t* setting; const wchar_t* command; bool moves; } table[] = {
        {L"CycleHistoryDownHotkey", L"ForwardHistory", false},
        {L"CycleHistoryUpHotkey", L"ReverseHistory", false},
        {L"SelectPrevPageHotkey", L"SelectPrevPage", true},
        {L"SelectNextPageHotkey", L"SelectNextPage", true},
        {L"OpenContextMenuHotkey", L"LoadContextMenu", false},
        {L"OpenHistoryHotkey", L"LoadHistory", false},
        {L"SettingWindowHotkey", L"OpenSetting", false},
        {L"SelectPrevItemHotkey2", L"SelectPrevItem", true},
        {L"SelectNextItemHotkey2", L"SelectNextItem", true},
        {L"SelectPrevItemHotkey", L"SelectPrevItem", true},
        {L"SelectNextItemHotkey", L"SelectNextItem", true},
        {L"AutoCompleteHotkey2", L"AutocompleteQuery", false},
        {L"AutoCompleteHotkey", L"AutocompleteQuery", false},
    };
    if (Matches(L"SettingWindowHotkey", vk, mods)) {
        OpenHaloSettings();
        return true;
    }
    // The menu key, Shift+F10 and the context-menu key open the same menu as a right-click.
    if (results && (Matches(L"OpenContextMenuHotkey", vk, mods) || (vk == VK_APPS && mods == 0) ||
                    (vk == VK_F10 && mods == kShift) || (vk == VK_RETURN && mods == kShift))) {
        RequestAppMenuForSelection();
        return true;
    }
    for (auto& e : table) {
        if (Matches(e.setting, vk, mods)) {
            if (e.moves) g.movedByKeys = true;
            Cmd(e.command);
            return true;
        }
    }
    if (Matches(L"PreviewHotkey", vk, mods)) { TogglePreview(); return true; }

    // Flow's fixed keys.
    if (vk == VK_F12 && mods == kCtrl) { Cmd(L"ToggleGameMode"); return true; }
    if (vk == 'C' && mods == (kCtrl | kShift)) { Cmd(L"CopyAlternative"); return true; }
    Hotkey openMod = ParseHotkey(SetStr(L"OpenResultModifiers", L"Alt") + L" + A");
    if (vk >= '0' && vk <= '9' && mods == openMod.mods && mods != 0) {
        int index = vk == '0' ? 9 : (int)(vk - '1');
        Send({L"open", std::to_wstring(index), L"0000"});
        return true;
    }
    if (vk == VK_RETURN) {
        if (mods == kShift) Cmd(L"LoadContextMenu");
        else if (mods == 0 || mods == kCtrl || mods == kAlt || mods == (kCtrl | kShift)) Send({L"open", L"", ModsField(mods)});
        return true;
    }
    if (mods == kCtrl) {
        if (vk == VK_OEM_6) { Cmd(L"IncreaseWidth"); return true; }
        if (vk == VK_OEM_4) { Cmd(L"DecreaseWidth"); return true; }
        if (vk == VK_OEM_PLUS) { Cmd(L"IncreaseMaxResult"); return true; }
        if (vk == VK_OEM_MINUS) { Cmd(L"DecreaseMaxResult"); return true; }
        if (vk == 'R') { Cmd(L"ReQuery"); return true; }
    }
    if (mods == kAlt && vk == VK_HOME) { Cmd(L"SelectFirstResult"); return true; }
    if (mods == kAlt && vk == VK_END) { Cmd(L"SelectLastResult"); return true; }
    if (vk == VK_F5 && mods == 0) { Cmd(L"ReloadPluginData"); return true; }
    if (vk == VK_ESCAPE && mods == 0) { Cmd(L"Esc"); return true; }

    // Text editing.
    bool shift = (mods & kShift) != 0, ctrl = (mods & kCtrl) != 0;
    if (mods & (kAlt | kWin)) return false;
    switch (vk) {
        case VK_LEFT:
            if (!shift && HasSelection() && !ctrl) MoveCaret(std::min(g.caret, g.anchor), false);
            else MoveCaret(ctrl ? WordLeft(g.caret) : g.caret - 1, shift);
            return true;
        case VK_RIGHT:
            if (!shift && HasSelection() && !ctrl) MoveCaret(std::max(g.caret, g.anchor), false);
            else MoveCaret(ctrl ? WordRight(g.caret) : g.caret + 1, shift);
            return true;
        case VK_HOME:
            MoveCaret(0, shift);
            return true;
        case VK_END:
            MoveCaret((int)g.text.size(), shift);
            return true;
        case VK_BACK:
            if (g.text.empty()) return true;
            PushUndo();
            if (HasSelection()) DeleteSelection();
            else if (g.caret > 0) {
                int to = ctrl ? WordLeft(g.caret) : g.caret - 1;
                g.text.erase(to, g.caret - to);
                g.caret = g.anchor = to;
            }
            TextChanged(true);
            return true;
        case VK_DELETE:
            PushUndo();
            if (HasSelection()) DeleteSelection();
            else if (g.caret < (int)g.text.size()) {
                int to = ctrl ? WordRight(g.caret) : g.caret + 1;
                g.text.erase(g.caret, to - g.caret);
            }
            TextChanged(true);
            return true;
    }
    if (ctrl && !shift) {
        switch (vk) {
            case 'A':
                g.anchor = 0;
                MoveCaret((int)g.text.size(), true);
                return true;
            case 'C':
                CopySelection(false);
                return true;
            case 'X':
                CopySelection(true);
                return true;
            case 'V':
                Paste();
                return true;
            case 'Z':
                if (!g.undo.empty()) {
                    g.text = g.undo.back();
                    g.undo.pop_back();
                    g.caret = g.anchor = (int)g.text.size();
                    TextChanged(true);
                }
                return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------- mouse

int RowAt(float dipX, float dipY) {
    Layout& L = g.lay;
    if (!L.rows || dipX < 10 || dipX > L.listW - 10) return -1;
    float y = dipY - (L.listY + 10);
    if (y < 0) return -1;
    int row = (int)(y / L.rowH);
    return row < (int)g.res.items.size() && row < L.rows ? row : -1;
}

// ---------------------------------------------------------------- window procedures

// Runs one of Halo's styled menus over the open launcher. The menu takes the focus, so the
// launcher must not close for it; afterwards a click elsewhere closes Halo, anything else
// hands the keyboard back.
int RunLauncherMenu(const std::vector<HaloMenuItem>& items, POINT at) {
    g.menuOpen = true;
    KillTimer(g.wnd, kTimerHide);
    int id = haloset::ShowMenu(g.wnd, items, &at);
    g.menuOpen = false;
    if (!g.visible) return id;
    if (id == 0) {
        POINT pt;
        GetCursorPos(&pt);
        RECT r;
        GetWindowRect(g.wnd, &r);
        bool pressed = ((GetAsyncKeyState(VK_LBUTTON) | GetAsyncKeyState(VK_RBUTTON) | GetAsyncKeyState(VK_MBUTTON)) & 0x8001) != 0;
        HWND fg = GetForegroundWindow();
        DWORD pid = 0;
        if (fg) GetWindowThreadProcessId(fg, &pid);
        if (pressed && !PtInRect(&r, pt) && fg && pid != GetCurrentProcessId() &&
            SetBool(L"HideWhenDeactivated", true)) {
            HideLauncher();
            Send({L"hide"});
            return 0;
        }
    }
    ForceForeground(g.wnd);
    SetFocus(g.wnd);
    Render();
    return id;
}

// Right-click on the launcher's empty space.
void ShowLauncherMenu(POINT at) {
    enum { kSettings = 1, kPlugins, kRestart, kHide };
    std::vector<HaloMenuItem> items(5);
    items[0] = {kSettings, L"\uEB51", L"Settings", SetStr(L"SettingWindowHotkey", L"Ctrl+I")};
    items[1] = {kPlugins, L"\uEAE6", L"Modules"};
    items[2].separator = true;
    items[3] = {kRestart, L"\uEB37", L"Restart the search engine"};
    items[4] = {kHide, L"\uEAE7", L"Hide Halo", L"Esc"};
    int id = RunLauncherMenu(items, at);
    if (id == kSettings) {
        OpenHaloSettings();
    } else if (id == kPlugins) {
        OpenHaloSettings(4 /* the Plugins page */);
    } else if (id == kRestart) {
        HideLauncher();
        if (!Send({L"restartengine"})) RestartProcess(kExitRestart);
    } else if (id == kHide) {
        HideLauncher();
        Send({L"hide"});
    }
}

// ---------------------------------------------------------------- a row's right-click menu
// Windows' own menu for the app or file (the same entries File Explorer and Start show),
// with fitting icons, then the plugin's actions Windows has no entry for, then pin to taskbar
// through Seamless Taskbar (Windows takes that one from File Explorer's process only).

constexpr UINT kShellFirst = 1, kShellLast = 0x6FFF;   // Windows' entries
constexpr int kFlowFirst = 0x7000;                    // the plugin's actions, by position
constexpr int kPinTaskbar = 0x7F00, kUnpinTaskbar = 0x7F01;

// Icons from FiraCode Nerd Font, picked by the entry's verb first, then by its words.
std::wstring AppMenuGlyph(const std::wstring& verbIn, const std::wstring& labelIn) {
    std::wstring verb = verbIn, label = labelIn;
    for (auto& c : verb) c = (wchar_t)towlower(c);
    for (auto& c : label) c = (wchar_t)towlower(c);
    static const struct { const wchar_t* key; const wchar_t* glyph; } verbs[] = {
        {L"runasuser", L"\uEB99"}, {L"runas", L"\uEB53"}, {L"opencontaining", L"\uEAF7"},
        {L"openfilelocation", L"\uEAF7"}, {L"properties", L"\uEA74"}, {L"delete", L"\uEA81"},
        {L"cut", L"\U000F0190"}, {L"copyaspath", L"\uEAC0"}, {L"copy", L"\uEBCC"}, {L"paste", L"\U000F0192"},
        {L"rename", L"\uEA73"}, {L"link", L"\uEAEE"}, {L"edit", L"\uEA73"}, {L"find", L"\uEA6D"},
        {L"unpin", L"\U000F0404"}, {L"pin", L"\U000F0403"}, {L"uninstall", L"\uEA81"},
        {L"share", L"\U000F0496"}, {L"openas", L"\uEB7F"}, {L"openwith", L"\uEB7F"}, {L"sendto", L"\uEC0F"},
        {L"compress", L"\U000F05C4"}, {L"powershell", L"\uEBC7"}, {L"cmd", L"\uEA85"}, {L"terminal", L"\uEA85"},
        {L"explore", L"\uEA83"}, {L"opennewwindow", L"\uEB7F"}, {L"open", L"\uEB14"},
    };
    if (!verb.empty())
        for (auto& v : verbs)
            if (verb.find(v.key) != std::wstring::npos) return v.glyph;
    static const struct { const wchar_t* key; const wchar_t* glyph; } words[] = {
        {L"administrator", L"\uEB53"}, {L"admin", L"\uEB53"}, {L"different user", L"\uEB99"},
        {L"file location", L"\uEAF7"}, {L"containing folder", L"\uEAF7"}, {L"open folder", L"\uEAF7"},
        {L"properties", L"\uEA74"}, {L"uninstall", L"\uEA81"}, {L"delete", L"\uEA81"}, {L"unpin", L"\U000F0404"},
        {L"pin", L"\U000F0403"}, {L"copy as path", L"\uEAC0"}, {L"copy path", L"\uEAC0"}, {L"copy", L"\uEBCC"},
        {L"cut", L"\U000F0190"}, {L"paste", L"\U000F0192"}, {L"rename", L"\uEA73"}, {L"shortcut", L"\uEAEE"},
        {L"share", L"\U000F0496"}, {L"send to", L"\uEC0F"}, {L"open with", L"\uEB7F"}, {L"zip", L"\U000F05C4"},
        {L"compress", L"\U000F05C4"}, {L"archive", L"\U000F05C4"}, {L"extract", L"\U000F05C4"}, {L"7-zip", L"\U000F05C4"},
        {L"powershell", L"\uEBC7"}, {L"terminal", L"\uEA85"}, {L"command", L"\uEA85"}, {L"visual studio", L"\uEAC4"},
        {L"code", L"\uEAC4"}, {L"notepad", L"\uEA73"}, {L"edit", L"\uEA73"}, {L"scan", L"\uEB53"},
        {L"defender", L"\uEB53"}, {L"security", L"\uEB53"}, {L"hide", L"\uEAE7"}, {L"disable", L"\uEAE7"},
        {L"setting", L"\uEB51"}, {L"option", L"\uEB51"}, {L"search", L"\uEA6D"}, {L"find", L"\uEA6D"},
        {L"history", L"\uEA82"}, {L"top", L"\uEB59"}, {L"favourite", L"\uEB59"}, {L"favorite", L"\uEB59"},
        {L"info", L"\uEA74"}, {L"about", L"\uEA74"}, {L"refresh", L"\uEB37"}, {L"reload", L"\uEB37"},
        {L"web", L"\uEB01"}, {L"browser", L"\uEB01"}, {L"url", L"\uEB01"}, {L"link", L"\uEB15"},
        {L"repair", L"\uEB6D"}, {L"reset", L"\uEB6D"}, {L"new window", L"\uEB7F"}, {L"folder", L"\uEA83"},
        {L"open", L"\uEB14"}, {L"run", L"\uEB2C"}, {L"start", L"\uEB2C"}, {L"file", L"\uEA7B"},
    };
    for (auto& w : words)
        if (label.find(w.key) != std::wstring::npos) return w.glyph;
    return L"\uEAE6";  // an add-on's entry with no better match
}

// "Open &file location\tCtrl+O" -> label "Open file location", hint "Ctrl+O".
void CleanMenuText(const wchar_t* raw, std::wstring& label, std::wstring& hint) {
    std::wstring s = raw;
    size_t tab = s.find(L'\t');
    if (tab != std::wstring::npos) {
        hint = s.substr(tab + 1);
        s.resize(tab);
    }
    label.clear();
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == L'&') {
            if (i + 1 < s.size() && s[i + 1] == L'&') { label += L'&'; i++; }
            continue;
        }
        label += s[i];
    }
    // "(&F)" style keys some apps add after the words.
    if (label.size() > 3 && label.back() == L')' && label[label.size() - 3] == L'(') label.resize(label.size() - 3);
    while (!label.empty() && iswspace(label.back())) label.pop_back();
}

std::wstring MenuKey(std::wstring s) {
    std::wstring k;
    for (wchar_t c : s)
        if (iswalnum(c)) k += (wchar_t)towlower(c);
    if (k == L"openfilelocation") k = L"opencontainingfolder";
    return k;
}

void ShellMenuToItems(IContextMenu* cm, IContextMenu3* cm3, IContextMenu2* cm2, HMENU menu,
                      std::vector<HaloMenuItem>& out, int depth) {
    int count = GetMenuItemCount(menu);
    for (int i = 0; i < count; i++) {
        wchar_t text[260] = {};
        MENUITEMINFOW mi{sizeof(mi)};
        mi.fMask = MIIM_FTYPE | MIIM_ID | MIIM_SUBMENU | MIIM_STATE | MIIM_STRING;
        mi.dwTypeData = text;
        mi.cch = ARRAYSIZE(text) - 1;
        if (!GetMenuItemInfoW(menu, i, TRUE, &mi)) continue;
        if (mi.fType & MFT_SEPARATOR) {
            if (!out.empty() && !out.back().separator) out.push_back(HaloMenuItem{.separator = true});
            continue;
        }
        if (mi.fType & MFT_OWNERDRAW) text[0] = 0;  // the text belongs to the extension's drawing
        HaloMenuItem item;
        CleanMenuText(text, item.label, item.hint);
        if (item.label.empty()) continue;
        std::wstring verb;
        if (!mi.hSubMenu && mi.wID >= kShellFirst && mi.wID <= kShellLast) {
            wchar_t v[128] = {};
            if (SUCCEEDED(cm->GetCommandString(mi.wID - kShellFirst, GCS_VERBW, nullptr, (LPSTR)v, ARRAYSIZE(v)))) verb = v;
            // Windows takes these from File Explorer only; Halo offers them through Seamless Taskbar.
            if (_wcsicmp(verb.c_str(), L"taskbarpin") == 0 || _wcsicmp(verb.c_str(), L"taskbarunpin") == 0) continue;
        }
        item.glyph = AppMenuGlyph(verb, item.label);
        item.disabled = (mi.fState & MFS_DISABLED) != 0;
        item.checked = (mi.fState & MFS_CHECKED) != 0;
        if (mi.hSubMenu) {
            if (depth >= 2) continue;
            // "Send to" and "Open with" fill themselves when they are about to open.
            if (cm3) cm3->HandleMenuMsg2(WM_INITMENUPOPUP, (WPARAM)mi.hSubMenu, i, nullptr);
            else if (cm2) cm2->HandleMenuMsg(WM_INITMENUPOPUP, (WPARAM)mi.hSubMenu, i);
            ShellMenuToItems(cm, cm3, cm2, mi.hSubMenu, item.sub, depth + 1);
            while (!item.sub.empty() && item.sub.back().separator) item.sub.pop_back();
            if (item.sub.empty()) continue;
        } else {
            item.id = (int)mi.wID;
        }
        out.push_back(std::move(item));
    }
}

// Seamless Taskbar answers from inside File Explorer: 2 pinned, 1 not pinned, 0 not possible.
LRESULT AskTaskbarPin(DWORD code, const std::wstring& name) {
    HWND bridge = FindWindowExW(HWND_MESSAGE, nullptr, L"SeamlessTaskbarPinBridge", nullptr);
    if (!bridge || name.empty()) return 0;
    COPYDATASTRUCT cd{code, (DWORD)(name.size() * sizeof(wchar_t)), (void*)name.data()};
    DWORD_PTR result = 0;
    if (!SendMessageTimeoutW(bridge, WM_COPYDATA, (WPARAM)g.wnd, (LPARAM)&cd, SMTO_ABORTIFHUNG | SMTO_BLOCK, 1500, &result))
        return 0;
    return (LRESULT)result;
}
constexpr DWORD kPinQuery = 0x51504E53, kPinDo = 0x50504E53, kPinUndo = 0x55504E53;

void RequestAppMenu(int index, POINT at) {
    g.appMenuWant = index;
    g.appMenuAsked = GetTickCount();
    g.appMenuAt = at;
    Send({L"sel", std::to_wstring(index)});
    if (!Send({L"ctxmenu", std::to_wstring(index)})) g.appMenuWant = -1;
}

// From the keyboard: the menu opens under the selected row.
void RequestAppMenuForSelection() {
    if (g.res.view != L"results" || g.res.items.empty()) return;
    int sel = std::clamp(g.res.sel, g.res.top, g.res.top + (int)g.res.items.size() - 1);
    int vis = sel - g.res.top;
    POINT at{(LONG)((kEdge + 56) * g.lay.s), (LONG)((kEdge + g.lay.listY + 10 + (vis + 1) * g.lay.rowH) * g.lay.s)};
    ClientToScreen(g.wnd, &at);
    RequestAppMenu(g.res.items[vis].index, at);
}

void ShowAppMenu() {
    AppMenuData d = g.appMenu;
    DWORD t0 = GetTickCount();
    std::wstring name = !d.aumid.empty() ? L"shell:AppsFolder\\" + d.aumid : d.path;

    ComPtr<IContextMenu> cm;
    ComPtr<IContextMenu2> cm2;
    ComPtr<IContextMenu3> cm3;
    HMENU menu = nullptr;
    std::vector<HaloMenuItem> items;
    if (!name.empty()) {
        PIDLIST_ABSOLUTE pidl = nullptr;
        if (SUCCEEDED(SHParseDisplayName(name.c_str(), nullptr, &pidl, 0, nullptr)) && pidl) {
            ComPtr<IShellFolder> parent;
            PCUITEMID_CHILD child = nullptr;
            if (SUCCEEDED(SHBindToParent(pidl, IID_PPV_ARGS(&parent), &child)) &&
                SUCCEEDED(parent->GetUIObjectOf(g.wnd, 1, &child, IID_IContextMenu, nullptr, (void**)cm.GetAddressOf()))) {
                cm.As(&cm3);
                cm.As(&cm2);
                menu = CreatePopupMenu();
                if (menu && SUCCEEDED(cm->QueryContextMenu(menu, 0, kShellFirst, kShellLast, CMF_NORMAL)))
                    ShellMenuToItems(cm.Get(), cm3.Get(), cm2.Get(), menu, items, 0);
            }
            CoTaskMemFree(pidl);
        }
    }
    while (!items.empty() && items.back().separator) items.pop_back();

    // Pin to taskbar sits beside Windows' other pin entries, or after the first group.
    bool pinnable = !d.aumid.empty() || (!d.path.empty() && (PathMatchSpecW(d.path.c_str(), L"*.lnk") || PathMatchSpecW(d.path.c_str(), L"*.exe")));
    if (pinnable) {
        LRESULT state = AskTaskbarPin(kPinQuery, name);
        if (state == 1 || state == 2) {
            HaloMenuItem pin;
            pin.id = state == 2 ? kUnpinTaskbar : kPinTaskbar;
            pin.label = state == 2 ? L"Unpin from taskbar" : L"Pin to taskbar";
            pin.glyph = state == 2 ? L"\U000F0404" : L"\U000F0403";
            size_t at = items.size();
            for (size_t i = 0; i < items.size(); i++)
                if (!items[i].separator && MenuKey(items[i].label).find(L"start") != std::wstring::npos &&
                    MenuKey(items[i].label).find(L"pin") != std::wstring::npos) at = i + 1;
            if (at == items.size())
                for (size_t i = 0; i < items.size(); i++)
                    if (items[i].separator) { at = i; break; }
            items.insert(items.begin() + at, pin);
        }
    }

    // The plugin's actions Windows has no entry for.
    std::set<std::wstring> have;
    for (auto& it : items)
        if (!it.separator) have.insert(MenuKey(it.label));
    std::vector<HaloMenuItem> extra;
    for (size_t n = 0; n < d.flow.size(); n++) {
        if (d.flow[n].title.empty() || have.count(MenuKey(d.flow[n].title))) continue;
        HaloMenuItem it;
        it.id = kFlowFirst + (int)n;
        it.label = d.flow[n].title;
        it.glyph = AppMenuGlyph(L"", d.flow[n].title);
        extra.push_back(std::move(it));
    }
    if (!extra.empty()) {
        if (!items.empty()) items.push_back(HaloMenuItem{.separator = true});
        for (auto& e : extra) items.push_back(std::move(e));
    }
    Wh_Log(L"row menu: %d entries in %u ms (Windows menu %s, %d plugin actions)", (int)items.size(),
           GetTickCount() - t0, cm ? L"yes" : L"no", (int)extra.size());
    if (items.empty()) {
        if (menu) DestroyMenu(menu);
        return;
    }

    int id = RunLauncherMenu(items, g.appMenuAt);
    if (id >= (int)kShellFirst && id <= (int)kShellLast && cm) {
        HideLauncher();
        Send({L"hide"});
        AllowSetForegroundWindow(ASFW_ANY);
        CMINVOKECOMMANDINFOEX ici{sizeof(ici)};
        ici.fMask = CMIC_MASK_UNICODE | CMIC_MASK_PTINVOKE;
        ici.hwnd = g.wnd;
        ici.lpVerb = MAKEINTRESOURCEA(id - kShellFirst);
        ici.lpVerbW = MAKEINTRESOURCEW(id - kShellFirst);
        ici.nShow = SW_SHOWNORMAL;
        ici.ptInvoke = g.appMenuAt;
        HRESULT hr = cm->InvokeCommand((CMINVOKECOMMANDINFO*)&ici);
        Wh_Log(L"row menu: Windows entry %d -> 0x%08X", id - (int)kShellFirst, (unsigned)hr);
    } else if (id >= kFlowFirst && id < kFlowFirst + (int)d.flow.size()) {
        Send({L"ctxrun", std::to_wstring(id - kFlowFirst)});
    } else if (id == kPinTaskbar || id == kUnpinTaskbar) {
        LRESULT ok = AskTaskbarPin(id == kPinTaskbar ? kPinDo : kPinUndo, name);
        Wh_Log(L"row menu: taskbar %s -> %d", id == kPinTaskbar ? L"pin" : L"unpin", (int)ok);
    }
    if (menu) DestroyMenu(menu);
}

LRESULT CALLBACK LauncherProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_APP_APPMENU:
            ShowAppMenu();
            return 0;
        case WM_NCCALCSIZE:
            return 0;
        // Windows still thinks this window was born with a caption (every overlapped window is),
        // so the stock handlers paint an old light-blue title strip over the top of the glass
        // when it gains focus or its name changes. The window has no frame to paint.
        case WM_NCACTIVATE:
            return DefWindowProcW(hwnd, msg, wp, -1);  // keep the focus bookkeeping, skip the repaint
        case WM_NCPAINT:
            return 0;
        case WM_SETTEXT:
        case WM_SETICON: {
            LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
            SetWindowLongPtrW(hwnd, GWL_STYLE, style & ~WS_VISIBLE);  // store it, draw nothing
            LRESULT r = DefWindowProcW(hwnd, msg, wp, lp);
            SetWindowLongPtrW(hwnd, GWL_STYLE, style);
            return r;
        }
        case WM_ERASEBKGND:
            return 1;  // every frame is drawn whole, an erase would only flash
        case WM_PAINT:
            ValidateRect(hwnd, nullptr);
            if (g.visible) Render();
            return 0;
        case WM_MOUSEACTIVATE:
            if (g.quiet) return MA_NOACTIVATE;
            break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN: {
            UINT vk = (UINT)wp;
            if (vk == VK_CONTROL || vk == VK_SHIFT || vk == VK_MENU || vk == VK_LWIN || vk == VK_RWIN) break;
            if (OnKeyDown(vk, CurrentMods())) {
                // Swallow the character this key would also produce.
                MSG peek;
                PeekMessageW(&peek, hwnd, WM_CHAR, WM_CHAR, PM_REMOVE);
                PeekMessageW(&peek, hwnd, WM_SYSCHAR, WM_SYSCHAR, PM_REMOVE);
                return 0;
            }
            if (msg == WM_SYSKEYDOWN && vk != VK_F4) return 0;
            break;
        }
        case WM_SYSCHAR:
            return 0;
        case WM_CHAR: {
            wchar_t c = (wchar_t)wp;
            if (c >= 32 && c != 127 && !(GetAsyncKeyState(VK_CONTROL) < 0 && !(GetAsyncKeyState(VK_MENU) < 0)))
                InsertText(std::wstring(1, c));
            else if (c >= 32)
                Trace(L"character dropped, Ctrl is held");
            return 0;
        }
        case WM_TIMER:
            if (wp == kTimerFrame) {
                Render();
            } else if (wp == kTimerCaret) {
                g.caretOn = !g.caretOn;
                if (!g.animating && !g.busy) Render();
            } else if (wp == kTimerHide) {
                HWND fg = GetForegroundWindow();
                if (!g.visible || fg == hwnd || g.menuOpen) {
                    KillTimer(hwnd, kTimerHide);
                } else if (IsCaptureTool(fg) || (!fg && g_hideNoOwnerChecks++ < 12)) {
                    // Look again once the capture closes. With no window in front at all
                    // (Windows between two windows), wait up to 3 s for one to take over.
                    SetTimer(hwnd, kTimerHide, 250, nullptr);
                } else {
                    KillTimer(hwnd, kTimerHide);
                    Trace(L"hidden after losing focus");
                    HideLauncher();
                    Send({L"hide"});
                }
            }
            return 0;
        case WM_ACTIVATE:
            if (LOWORD(wp) == WA_INACTIVE && g.visible) {
                wchar_t cls[64] = L"";
                HWND other = (HWND)lp;
                if (other) GetClassNameW(other, cls, 64);
                bool toPeek = wcsncmp(cls, L"WindhawkPeek", 12) == 0;
                wchar_t fgCls[64] = L"";
                GetClassNameW(GetForegroundWindow(), fgCls, 64);
                Trace(L"lost focus to '%s' (foreground '%s')", cls, fgCls);
                if (!toPeek && !g.menuOpen && SetBool(L"HideWhenDeactivated", true)) {
                    // Hide a moment later, as Flow does (100 ms), and not at all while a screen
                    // capture tool is in front: ShareX and the Snipping Tool list the windows on
                    // screen after their own window opens, and a hidden Halo is not one of them.
                    g_hideNoOwnerChecks = 0;
                    SetTimer(hwnd, kTimerHide, kHideDelay, nullptr);
                }
                Render();
            } else if (g.visible) {
                KillTimer(hwnd, kTimerHide);
                Render();
            }
            return 0;
        case WM_MOUSEMOVE: {
            POINT p{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            POINT screen = p;
            ClientToScreen(hwnd, &screen);
            // The window appearing under a resting pointer must not steal the selection.
            if (screen.x == g.lastMouse.x && screen.y == g.lastMouse.y) return 0;
            g.lastMouse = screen;
            float x = p.x / g.lay.s - kEdge, y = p.y / g.lay.s - kEdge;
            if (g.selecting) {
                MoveCaret(HitQuery(x), true);
                return 0;
            }
            int row = RowAt(x, y);
            if (row >= 0 && row != g.hoverRow && g.res.items[row].index != g.res.sel)
                Send({L"sel", std::to_wstring(g.res.items[row].index)});
            g.hoverRow = row;
            return 0;
        }
        case WM_LBUTTONDOWN: {
            float x = GET_X_LPARAM(lp) / g.lay.s - kEdge, y = GET_Y_LPARAM(lp) / g.lay.s - kEdge;
            if (y < g.lay.topH) {
                g.selecting = true;
                SetCapture(hwnd);
                MoveCaret(HitQuery(x), GetAsyncKeyState(VK_SHIFT) < 0);
            }
            return 0;
        }
        case WM_LBUTTONDBLCLK: {
            float x = GET_X_LPARAM(lp) / g.lay.s - kEdge, y = GET_Y_LPARAM(lp) / g.lay.s - kEdge;
            if (y < g.lay.topH) {
                int p = HitQuery(x);
                g.anchor = WordLeft(p);
                MoveCaret(WordRight(p), true);
            }
            return 0;
        }
        case WM_LBUTTONUP: {
            float x = GET_X_LPARAM(lp) / g.lay.s - kEdge, y = GET_Y_LPARAM(lp) / g.lay.s - kEdge;
            if (g.selecting) {
                g.selecting = false;
                ReleaseCapture();
                return 0;
            }
            int row = RowAt(x, y);
            if (row >= 0) Send({L"open", std::to_wstring(g.res.items[row].index), ModsField(CurrentMods())});
            return 0;
        }
        case WM_RBUTTONUP: {
            int row = RowAt(GET_X_LPARAM(lp) / g.lay.s - kEdge, GET_Y_LPARAM(lp) / g.lay.s - kEdge);
            POINT at{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            ClientToScreen(hwnd, &at);
            if (row >= 0 && g.res.view == L"results") {
                RequestAppMenu(g.res.items[row].index, at);
            } else if (row < 0) {
                ShowLauncherMenu(at);
            }
            return 0;
        }
        case WM_MOUSEWHEEL: {
            int steps = -GET_WHEEL_DELTA_WPARAM(wp) / WHEEL_DELTA;
            if (steps) Send({L"scroll", std::to_wstring(steps * 3)});
            return 0;
        }
        case WM_SETCURSOR:
            if (LOWORD(lp) == HTCLIENT) {
                POINT p;
                GetCursorPos(&p);
                ScreenToClient(hwnd, &p);
                bool inQuery = p.y / g.lay.s - kEdge < g.lay.topH && p.x / g.lay.s - kEdge < QueryRight();
                SetCursor(LoadCursor(nullptr, inQuery ? IDC_IBEAM : IDC_ARROW));
                return TRUE;
            }
            break;
        case WM_DPICHANGED:
        case WM_DISPLAYCHANGE:
            g.monitor = nullptr;
            ResetTarget();
            Render();
            return 0;
        case WM_CLOSE:
            return 0;  // Alt+F4 only hides
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

UINT g_toggleMsg = 0;
UINT g_taskbarCreated = 0;

// ---------------------------------------------------------------- tray icon

void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// Halo's mark in a square of side s at (x, y): a lens ring, a round handle and a dot in the lens.
// The tray icon draws it per pixel; the settings window draws it with Direct2D (HaloGlyph).
struct HaloMark {
    float lx, ly, lr, ring, hx0, hy0, hx1, hy1, hw, dot;
    HaloMark(float x, float y, float s) {
        lx = x + s * 0.43f;
        ly = y + s * 0.43f;
        lr = s * 0.19f;
        ring = s * 0.085f;
        float k = (lr + ring * 0.5f) * 0.7071f;
        hx0 = lx + k;
        hy0 = ly + k;
        hx1 = x + s * 0.74f;
        hy1 = y + s * 0.74f;
        hw = s * 0.1f;
        dot = s * 0.05f;
    }
};

float SegmentDistance(float px, float py, float ax, float ay, float bx, float by) {
    float vx = bx - ax, vy = by - ay, wx = px - ax, wy = py - ay;
    float t = std::clamp((wx * vx + wy * vy) / (vx * vx + vy * vy), 0.0f, 1.0f);
    float dx = wx - vx * t, dy = wy - vy * t;
    return std::sqrt(dx * dx + dy * dy);
}

// The rounded square in the blue to mauve gradient with Halo's mark in crust.
HICON MakeTrayIcon() {
    int size = GetSystemMetricsForDpi(SM_CXSMICON, GetDpiForSystem());
    if (size < 16) size = 16;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color || !bits) {
        if (color) DeleteObject(color);
        return nullptr;
    }
    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
    const float ink[3] = {0x11 / 255.f, 0x11 / 255.f, 0x1B / 255.f};
    float radius = size * 0.26f, half = size / 2.0f;
    HaloMark m(0, 0, (float)size);
    uint32_t* px = (uint32_t*)bits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float fx = x + 0.5f, fy = y + 0.5f;
            float qx = std::fabs(fx - half) - (half - radius), qy = std::fabs(fy - half) - (half - radius);
            float ox = std::max(qx, 0.0f), oy = std::max(qy, 0.0f);
            float d = std::sqrt(ox * ox + oy * oy) + std::min(std::max(qx, qy), 0.0f) - radius;
            float a = std::clamp(0.5f - d, 0.0f, 1.0f);
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float toLens = std::sqrt((fx - m.lx) * (fx - m.lx) + (fy - m.ly) * (fy - m.ly));
            float dRing = std::fabs(toLens - m.lr) - m.ring / 2;
            float dHandle = SegmentDistance(fx, fy, m.hx0, m.hy0, m.hx1, m.hy1) - m.hw / 2;
            float dDot = toLens - m.dot;
            float cov = std::clamp(0.5f - std::min({dRing, dHandle, dDot}), 0.0f, 1.0f);
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = (base + (ink[i] - base) * cov) * a;
            }
            px[y * size + x] = ((uint32_t)(a * 255 + 0.5f) << 24) | ((uint32_t)(rgb[0] * 255 + 0.5f) << 16) |
                               ((uint32_t)(rgb[1] * 255 + 0.5f) << 8) | (uint32_t)(rgb[2] * 255 + 0.5f);
        }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

HICON g_trayIcon = nullptr;

void RemoveTray() {
    if (!g.trayAdded) return;
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g.msgWnd;
    nid.uID = kTrayId;
    Shell_NotifyIconW(NIM_DELETE, &nid);
    g.trayAdded = false;
}

void UpdateTray(bool add) {
    if (!g.msgWnd) return;
    if (!g.trayIcon) {
        RemoveTray();
        return;
    }
    if (!g_trayIcon) g_trayIcon = MakeTrayIcon();
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g.msgWnd;
    nid.uID = kTrayId;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_APP_TRAY;
    nid.hIcon = g_trayIcon ? g_trayIcon : LoadIconW(nullptr, IDI_APPLICATION);
    wcsncpy_s(nid.szTip, L"Halo Launcher", _TRUNCATE);
    if (!g.trayAdded || add) {
        RemoveTray();
        g.trayAdded = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
        if (g.trayAdded) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
}

void ShowTrayMenu(POINT pt) {
    enum { kOpen = 1, kSettings, kRestart };
    int cmd = haloset::ShowTrayMenu(g.msgWnd, &pt);
    if (cmd == kOpen) {
        if (!g.visible) RequestToggle();
    } else if (cmd == kSettings) {
        OpenHaloSettings();
    } else if (cmd == kRestart) {
        // The engine saves, answers "restart" and says bye; this process then ends with
        // kExitRestart and Windhawk's launcher starts a fresh one.
        if (!Send({L"restartengine"})) RestartProcess(kExitRestart);
    }
}

LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        g.trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    if (g_toggleMsg && msg == g_toggleMsg) {
        // 2: open, never close. Seamless Launchpad sends it for a keyboard Start that reached
        // Explorer; a Windows-key tap served here a moment ago already opened Halo.
        if (wp == 2) {
            if (g.visible || g.pendingShow || GetTickCount() - g_lastWinTap.load() < 1500) return 1;
            g.quietNext = false;
            RequestToggle();
            return 1;
        }
        g.quietNext = wp == 1 && !g.visible;  // 1: show without taking the keyboard
        RequestToggle();
        return 1;
    }
    switch (msg) {
        case WM_APP_LINES: {
            std::unique_ptr<std::vector<std::string>> lines((std::vector<std::string>*)lp);
            for (auto& l : *lines) OnLine(l);
            return 0;
        }
        case WM_APP_ENGINEDONE:
            if (!g_engine.closing.exchange(true)) {
                // Not asked to close: the engine left on its own (restart asked, or it failed).
                RestartProcess(g_engine.exitCode ? (int)g_engine.exitCode : kExitEngineDied);
            }
            g.engineReady = false;
            g.inSet = g.inRes = false;
            {
                std::lock_guard<std::mutex> guard(g_bridge.lock);
                g_bridge.ready = false;
            }
            HideLauncher();
            ReloadSettingsWindow();
            return 0;
        case WM_APP_RECORD:
            g.recording = wp != 0;
            RegisterKeys();
            return 0;
        case WM_APP_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    OpenHaloSettings();
                    break;
                case WM_CONTEXTMENU:
                    ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)});
                    break;
            }
            return 0;
        case WM_APP_SETTINGS:
            LoadSettings();
            ResetFormats();
            UpdateTray(false);
            RegisterKeys();
            ApplyBackdrop();
            Render();
            return 0;
        case WM_APP_HOOKKEY:
            FireKey((size_t)wp);
            return 0;
        case WM_HOTKEY:
            if (wp >= 1) FireKey((size_t)wp - 1);
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

// Windhawk starts a tool process once and does not start it again when it ends, and .NET
// cannot start twice in one process. So a restart starts the next copy here, marked with
// "-halo-after <pid>": that copy waits for this one to be gone before Windhawk's tool code
// checks that only one copy runs. "-halo-tries" counts failed starts so a broken engine
// does not loop.
int RelaunchTries() {
    const wchar_t* t = wcsstr(GetCommandLineW(), L" -halo-tries ");
    return t ? _wtoi(t + 13) : 0;
}

void RelaunchSelf(int code) {
    int tries = code == kExitRestart ? 0 : RelaunchTries() + 1;
    if (tries > 3) {
        Wh_Log(L"Engine failed %d times in a row, not starting again", tries - 1);
        return;
    }
    WCHAR exe[MAX_PATH];
    DWORD n = GetModuleFileNameW(nullptr, exe, ARRAYSIZE(exe));
    if (!n || n == ARRAYSIZE(exe)) return;
    wchar_t tail[96];
    swprintf(tail, 96, L" -halo-after %u -halo-tries %d", GetCurrentProcessId(), tries);
    std::wstring cmd = std::wstring(L"\"") + exe + L"\" -windhawk-tool-mod \"" WH_MOD_ID L"\"" + tail;
    STARTUPINFOW si{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_FORCEOFFFEEDBACK;
    PROCESS_INFORMATION pi{};
    if (CreateProcessW(exe, cmd.data(), nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS, nullptr, nullptr, &si, &pi)) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        Wh_Log(L"Started the next copy (pid %u, tries %d)", pi.dwProcessId, tries);
    } else {
        Wh_Log(L"Could not start the next copy: %u", GetLastError());
    }
}

// Runs when the mod loads, before Windhawk's one-copy check: a restarted copy waits here
// (at most 20 s) for the copy that started it to end.
struct WaitForOldCopy {
    WaitForOldCopy() {
        const wchar_t* cmd = GetCommandLineW();
        const wchar_t* a = wcsstr(cmd, L" -halo-after ");
        if (a) {
            DWORD pid = (DWORD)_wtoi(a + 13);
            if (HANDLE h = pid ? OpenProcess(SYNCHRONIZE, FALSE, pid) : nullptr) {
                WaitForSingleObject(h, 20000);
                CloseHandle(h);
            }
            return;
        }
        // Windhawk starts the new copy as soon as an update or a turn on/off unloads the old
        // one, and its tool code gives up after about 300 ms if the old copy still holds the
        // one-copy lock. Halo takes longer than that to stop its search engine, so the new
        // copy ended at once and nothing ran until the next sign-in (0.5.4, 20 Nov). This
        // copy waits (at most 20 s) for the old one's lock to go first.
        if (!wcsstr(cmd, L"-windhawk-tool-mod \"" WH_MOD_ID L"\"")) return;
        for (int i = 0; i < 200; i++) {
            HANDLE m = OpenMutexW(SYNCHRONIZE, FALSE, L"windhawk-tool-mod_" WH_MOD_ID);
            if (!m) return;
            CloseHandle(m);
            Sleep(100);
        }
    }
};
WaitForOldCopy g_waitForOldCopy;

DWORD WINAPI ThreadProc(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, g.d2d.GetAddressOf());
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)g.dwrite.GetAddressOf());
    CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g.wic));

    HINSTANCE inst = GetModuleHandleW(nullptr);
    LoadSettings();
    // Halo's own app identity. This helper process runs only this mod, so its windows and the
    // engine's notifications are named Halo Launcher instead of after Windhawk's helper.
    SetCurrentProcessExplicitAppUserModelID(L"DavidHiFi.HaloLauncher");
    g_toggleMsg = RegisterWindowMessageW(L"HaloLauncher.Toggle");
    g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    EnableDarkMenus();

    WNDCLASSW mc{};
    mc.lpfnWndProc = MsgWndProc;
    mc.hInstance = inst;
    mc.lpszClassName = kMsgClass;
    RegisterClassW(&mc);
    WNDCLASSW wc{};
    wc.lpfnWndProc = LauncherProc;
    wc.hInstance = inst;
    wc.style = CS_DBLCLKS;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = kWndClass;
    RegisterClassW(&wc);

    // A hidden top-level window, so other mods can find Halo by class and ask it to open.
    g.msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, kMsgClass, L"Halo Launcher", WS_POPUP, 0, 0, 0, 0, nullptr,
                               nullptr, inst, nullptr);
    // One plain frameless window, built the way Flow Launcher's is: not a popup, so the
    // borders mod rings it exactly as it ringed Flow, and glass all over, so Windows
    // rounds and shadows it.
    g.wnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, kWndClass, L"Halo Launcher", WS_OVERLAPPED, 0, 0, 400,
                            60, nullptr, nullptr, inst, nullptr);
    SetWindowLongPtrW(g.wnd, GWL_STYLE, WS_CLIPSIBLINGS);
    SetWindowPos(g.wnd, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    ApplyBackdrop();
    RegisterKeys();
    UpdateTray(true);

    StartEngine();
    SetEvent(g_ready);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    HideLauncher();
    RemoveTray();
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    UnregisterKeys();
    StopHook();
    StopEngine();
    // Lines still queued for the window are freed here.
    while (PeekMessageW(&msg, nullptr, WM_APP_LINES, WM_APP_LINES, PM_REMOVE))
        delete (std::vector<std::string>*)msg.lParam;
    if (g.wnd) DestroyWindow(g.wnd);
    g.wnd = g.msgWnd = nullptr;
    ResetFormats();
    ResetTarget();
    FreeSurface(g.surface);
    FreeSurface(g.faded);
    g.wic.Reset();
    g.dwrite.Reset();
    g.d2d.Reset();
    UnregisterClassW(kWndClass, inst);
    UnregisterClassW(kMsgClass, inst);
    CoUninitialize();
    // The engine ended without Windhawk unloading the mod (a restart, or it failed): end the
    // whole process so the launcher in windhawk.exe starts a clean one.
    int code = g_engine.exitCode;
    if (code && !g_unloading) {
        Wh_Log(L"Ending the process with %d so it starts fresh", code);
        RelaunchSelf(code);
        ExitProcess(code);
    }
    return 0;
}

}  // namespace

// ---------------------------------------------------------------- for the settings window

namespace halobridge {
bool Ready() {
    std::lock_guard<std::mutex> guard(g_bridge.lock);
    return g_bridge.ready;
}
std::wstring Setting(const std::wstring& name, bool* found) {
    std::lock_guard<std::mutex> guard(g_bridge.lock);
    auto it = g_bridge.set.find(name);
    *found = it != g_bridge.set.end();
    return *found ? it->second : std::wstring();
}
std::vector<HaloBridgePlugin> Plugins() {
    std::lock_guard<std::mutex> guard(g_bridge.lock);
    return g_bridge.plugins;
}
bool Panel(const std::wstring& id, HaloBridgePanel* out) {
    std::lock_guard<std::mutex> guard(g_bridge.lock);
    auto it = g_bridge.panels.find(id);
    if (it == g_bridge.panels.end()) return false;
    *out = it->second;
    return true;
}
void DropPanel(const std::wstring& id) {
    std::lock_guard<std::mutex> guard(g_bridge.lock);
    g_bridge.panels.erase(id);
}
std::wstring TakeError() {
    std::lock_guard<std::mutex> guard(g_bridge.lock);
    std::wstring e;
    e.swap(g_bridge.error);
    return e;
}
bool SendLine(std::initializer_list<std::wstring> fields) { return Send(fields); }
}  // namespace halobridge

void HaloRecording(bool on) {
    if (g.msgWnd) PostMessageW(g.msgWnd, WM_APP_RECORD, on ? 1 : 0, 0);
}

// Key boxes write keys the way the search engine reads them ("Ctrl + Alt + Space").
// mods are RegisterHotKey's MOD_ flags.
std::wstring Hotkey_Format(UINT mods, UINT vk) {
    std::wstring s;
    auto add = [&](const wchar_t* part) {
        if (!s.empty()) s += L" + ";
        s += part;
    };
    if (mods & MOD_CONTROL) add(L"Ctrl");
    if (mods & MOD_ALT) add(L"Alt");
    if (mods & MOD_SHIFT) add(L"Shift");
    if (mods & MOD_WIN) add(L"Win");
    static const struct { UINT vk; const wchar_t* name; } names[] = {
        {VK_SPACE, L"Space"}, {VK_TAB, L"Tab"}, {VK_RETURN, L"Enter"}, {VK_ESCAPE, L"Escape"},
        {VK_BACK, L"Back"}, {VK_DELETE, L"Delete"}, {VK_INSERT, L"Insert"}, {VK_HOME, L"Home"},
        {VK_END, L"End"}, {VK_PRIOR, L"PageUp"}, {VK_NEXT, L"PageDown"}, {VK_UP, L"Up"},
        {VK_DOWN, L"Down"}, {VK_LEFT, L"Left"}, {VK_RIGHT, L"Right"}, {VK_OEM_3, L"OemTilde"},
        {VK_OEM_PLUS, L"OemPlus"}, {VK_OEM_MINUS, L"OemMinus"}, {VK_OEM_COMMA, L"OemComma"},
        {VK_OEM_PERIOD, L"OemPeriod"}, {VK_OEM_2, L"OemQuestion"}, {VK_OEM_1, L"OemSemicolon"},
        {VK_OEM_4, L"OemOpenBrackets"}, {VK_OEM_5, L"OemPipe"}, {VK_OEM_6, L"OemCloseBrackets"},
        {VK_OEM_7, L"OemQuotes"}, {VK_OEM_102, L"OemBackslash"}, {VK_CAPITAL, L"CapsLock"},
        {VK_SNAPSHOT, L"PrintScreen"}, {VK_PAUSE, L"Pause"}, {VK_APPS, L"Apps"},
        {VK_MULTIPLY, L"Multiply"}, {VK_ADD, L"Add"}, {VK_SUBTRACT, L"Subtract"},
        {VK_DIVIDE, L"Divide"}, {VK_DECIMAL, L"Decimal"}, {VK_LWIN, L"LWin"}, {VK_RWIN, L"RWin"},
    };
    if (!vk) return s;
    wchar_t buf[16] = L"";
    const wchar_t* key = nullptr;
    for (auto& n : names)
        if (n.vk == vk) key = n.name;
    if (!key) {
        if (vk >= 'A' && vk <= 'Z') swprintf_s(buf, L"%c", (wchar_t)vk);
        else if (vk >= '0' && vk <= '9') swprintf_s(buf, L"D%c", (wchar_t)vk);
        else if (vk >= VK_F1 && vk <= VK_F24) swprintf_s(buf, L"F%u", vk - VK_F1 + 1);
        else if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) swprintf_s(buf, L"NumPad%u", vk - VK_NUMPAD0);
        else swprintf_s(buf, L"0x%02X", vk);
        key = buf;
    }
    add(key);
    return s;
}

// Halo's mark in crust: the settings window's rail tile, About card and window icon.
void HaloGlyph(ID2D1RenderTarget* rt, D2D1_RECT_F r, float alpha) {
    if (!rt) return;
    float s = std::min(r.right - r.left, r.bottom - r.top);
    float x = (r.left + r.right - s) / 2, y = (r.top + r.bottom - s) / 2;
    HaloMark m(x, y, s);
    ComPtr<ID2D1SolidColorBrush> ink;
    if (FAILED(rt->CreateSolidColorBrush(D2D1::ColorF(0x11111B, alpha), &ink))) return;
    ComPtr<ID2D1Factory> factory;
    rt->GetFactory(&factory);
    ComPtr<ID2D1StrokeStyle> round;
    if (factory)
        factory->CreateStrokeStyle(D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND,
                                                               D2D1_CAP_STYLE_ROUND),
                                   nullptr, 0, &round);
    rt->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(m.lx, m.ly), m.lr, m.lr), ink.Get(), m.ring);
    rt->DrawLine(D2D1::Point2F(m.hx0, m.hy0), D2D1::Point2F(m.hx1, m.hy1), ink.Get(), m.hw, round.Get());
    rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(m.lx, m.ly), m.dot, m.dot), ink.Get());
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
    Wh_Log(L">");
    // The tray menu gets the same look as every other mod's menus.
    SeamlessMenuSkin::Init();
    g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, ThreadProc, nullptr, 0, &g_threadId);
    if (!g_thread) return FALSE;
    WaitForSingleObject(g_ready, 10000);
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    Wh_Log(L">");
    if (g.msgWnd) PostMessageW(g.msgWnd, WM_APP_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    Wh_Log(L">");
    g_unloading = true;
    haloset::CloseSettingsWindow();
    if (g.msgWnd) PostMessageW(g.msgWnd, WM_CLOSE, 0, 0);
    if (g_thread) {
        WaitForSingleObject(g_thread, 12000);
        CloseHandle(g_thread);
    }
    SeamlessMenuSkin::Uninit();
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-11-halo-launcher\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace haloset {
// The settings window, from the tray icon or Ctrl+I in Halo. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkHaloLauncherSettings";
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1, WM_APP_SETTINGS_ACTIVATE = WM_APP + 2;
HANDLE g_settingsThread = nullptr;
std::atomic<HWND> g_settingsWnd;
std::atomic<bool> g_settingsStop;
void Settings_Close();
constexpr int kHaloPluginsPage = 4;
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
// Plugin names and keys are built at run time; SetField keeps plain pointers, so they live here.
static PCWSTR Pool(const std::wstring& s) {
    [[clang::no_destroy]] static std::deque<std::wstring> pool;
    [[clang::no_destroy]] static std::mutex lock;
    std::lock_guard<std::mutex> guard(lock);
    for (const auto& e : pool)
        if (e == s) return e.c_str();
    pool.push_back(s);
    return pool.back().c_str();
}
static UINT g_recWin = 0;  // A Windows key held while a key box listens; up alone records it.
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
// Generated by work\2026-11-11-halo-launcher\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    std::vector<SetField> fields = {
{K::Hotkey, L"flow:Hotkey", L"Open key", L"Opens and closes Halo. Click the box and press the keys. LWin means a tap of the Windows key on its own.", L"LWin", {}, 0, 100, 0, L"Opening Halo"},
{K::Hotkey, L"openKey", L"Second open key", L"Another key that opens and closes Halo, kept even when the keys below are off. Leave it empty for none.", L"", {}, 0, 100, 0, L"Opening Halo"},
{K::Check, L"useFlowKeys", L"Use the open key and shortcut keys", L"Halo answers the open key above and the query shortcut keys, like Win+R for the command line. Off, only the second open key works.", L"1", {}, 0, 100, 0, L"Opening Halo"},
{K::Check, L"flow:IgnoreHotkeysOnFullscreen", L"Ignore the keys in fullscreen apps", L"The open key does nothing while a game or video fills the screen.", L"0", {}, 0, 100, 0, L"Opening Halo"},
{K::Choice, L"flow:SearchWindowScreen", L"Screen", L"Which screen Halo opens on.", L"Cursor", {{L"Cursor", L"The screen with the mouse"}, {L"Focus", L"The screen of the app in front"}, {L"Primary", L"The main screen"}}, 0, 100, 0, L"Where it shows"},
{K::Choice, L"flow:SearchWindowAlign", L"Position", L"Where on that screen.", L"Center", {{L"Center", L"Middle"}, {L"CenterTop", L"Top middle"}, {L"LeftTop", L"Top left"}, {L"RightTop", L"Top right"}}, 0, 100, 0, L"Where it shows"},
{K::Check, L"flow:HideWhenDeactivated", L"Close when you click away", L"Halo closes when another window takes the focus.", L"1", {}, 0, 100, 0, L"Where it shows"},
{K::Choice, L"flow:LastQueryMode", L"Last search", L"What the search box holds when Halo opens again.", L"Selected", {{L"Selected", L"Keep it, selected"}, {L"Empty", L"Start empty"}, {L"Preserved", L"Keep it"}, {L"ActionKeywordSelected", L"Keep only the module word, selected"}, {L"ActionKeywordPreserved", L"Keep only the module word"}}, 0, 100, 0, L"Where it shows"},
{K::Check, L"flow:ShowHomePage", L"Home page", L"Shows results before you type anything, from the modules that offer them.", L"0", {}, 0, 100, 0, L"Home page"},
{K::Check, L"flow:ShowHistoryResultsForHomePage", L"Recent picks on the home page", L"Adds what you opened lately to the home page.", L"0", {}, 0, 100, 0, L"Home page"},
{K::Number, L"flow:MaxHistoryResultsToShowForHomePage", L"How many recent picks", L"1 to 20 (Suggested: 5).", L"5", {}, 1, 20, 0, L"Home page"},
{K::Choice, L"flow:QuerySearchPrecision", L"Match strictness", L"How closely a result must match what you typed.", L"Regular", {{L"Regular", L"Normal"}, {L"Low", L"Loose, more results"}, {L"None", L"Anything that matches at all"}}, 0, 100, 1, L"Results"},
{K::Number, L"flow:MaxResultsToShow", L"Rows shown", L"2 to 15 (Suggested: 10). Results past this scroll.", L"10", {}, 2, 15, 1, L"Results"},
{K::Check, L"flow:SearchQueryResultsWithDelay", L"Wait for a pause in typing", L"Searches once you stop typing for a moment, so slow modules are asked less often.", L"0", {}, 0, 100, 1, L"Results"},
{K::Number, L"flow:SearchDelayTime", L"Pause length", L"50 to 1000 milliseconds (Suggested: 150).", L"150", {}, 50, 1000, 1, L"Results"},
{K::Check, L"flow:AlwaysPreview", L"Preview panel open", L"Opens with the preview panel showing. The preview key still turns it on or off.", L"0", {}, 0, 100, 1, L"Preview"},
{K::Check, L"peekOnSpace", L"Space previews the file", L"After moving through the results with the arrows or Tab, Space opens the selected file in the Peek mod. Typing a space still works before that.", L"1", {}, 0, 100, 1, L"Preview"},
{K::Hotkey, L"flow:SelectNextItemHotkey", L"Next result", L"", L"Tab", {}, 0, 100, 2, L"Moving"},
{K::Hotkey, L"flow:SelectNextItemHotkey2", L"Next result, second key", L"", L"", {}, 0, 100, 2, L"Moving"},
{K::Hotkey, L"flow:SelectPrevItemHotkey", L"Previous result", L"", L"Shift + Tab", {}, 0, 100, 2, L"Moving"},
{K::Hotkey, L"flow:SelectPrevItemHotkey2", L"Previous result, second key", L"", L"", {}, 0, 100, 2, L"Moving"},
{K::Hotkey, L"flow:SelectNextPageHotkey", L"Next page", L"", L"PageUp", {}, 0, 100, 2, L"Moving"},
{K::Hotkey, L"flow:SelectPrevPageHotkey", L"Previous page", L"", L"PageDown", {}, 0, 100, 2, L"Moving"},
{K::Hotkey, L"flow:AutoCompleteHotkey", L"Complete the text", L"Fills the search box with the selected result.", L"Ctrl + Tab", {}, 0, 100, 2, L"Actions"},
{K::Hotkey, L"flow:AutoCompleteHotkey2", L"Complete the text, second key", L"", L"", {}, 0, 100, 2, L"Actions"},
{K::Hotkey, L"flow:OpenContextMenuHotkey", L"More actions", L"The list of extra actions for the selected result. Shift + Enter does the same.", L"Ctrl+O", {}, 0, 100, 2, L"Actions"},
{K::Hotkey, L"flow:PreviewHotkey", L"Preview", L"Opens the selected file in Peek, or turns the preview panel on or off.", L"F1", {}, 0, 100, 2, L"Actions"},
{K::Hotkey, L"flow:OpenHistoryHotkey", L"History", L"What you opened lately.", L"Ctrl+H", {}, 0, 100, 2, L"Actions"},
{K::Hotkey, L"flow:CycleHistoryUpHotkey", L"Older search", L"Puts your previous search back in the box.", L"Alt + Up", {}, 0, 100, 2, L"Actions"},
{K::Hotkey, L"flow:CycleHistoryDownHotkey", L"Newer search", L"", L"Alt + Down", {}, 0, 100, 2, L"Actions"},
{K::Hotkey, L"flow:SettingWindowHotkey", L"Settings", L"Opens this window.", L"Ctrl+I", {}, 0, 100, 2, L"Actions"},
{K::Choice, L"flow:OpenResultModifiers", L"Open by number with", L"Hold this and press 1 to 0 to open that row.", L"Alt", {{L"Alt", L"Alt"}, {L"Ctrl", L"Ctrl"}, {L"Ctrl+Alt", L"Ctrl + Alt"}}, 0, 100, 2, L"Open by number"},
{K::Check, L"flow:ShowOpenResultHotkey", L"Show the numbers", L"Each row shows the key that opens it.", L"1", {}, 0, 100, 2, L"Open by number"},
{K::Number, L"backgroundOpacity", L"Glass darkness", L"0 to 100 (Suggested: 55). How much Mocha covers the blur. 55 is the same glass as the settings windows.", L"55", {}, 0, 100, 3, L"Window"},
{K::Check, L"blur", L"Blur behind the window", L"Off, the window is solid Mocha.", L"1", {}, 0, 100, 3, L"Window"},
{K::Number, L"flow:WindowSize", L"Width", L"500 to 1600 (Suggested: 780).", L"780", {}, 500, 1600, 3, L"Window"},
{K::Number, L"flow:WindowHeightSize", L"Search box height", L"30 to 80 (Suggested: 42).", L"42", {}, 30, 80, 3, L"Window"},
{K::Number, L"flow:ItemHeightSize", L"Row height", L"40 to 90 (Suggested: 58).", L"58", {}, 40, 90, 3, L"Window"},
{K::Text, L"fontFamily", L"Font", L"The font for all of Halo's words: the search box, results, clock, hints and preview. If it is not installed, Segoe UI is used at the same size.", L"FiraCode Nerd Font", {}, 0, 100, 3, L"Text"},
{K::Choice, L"fontWeight", L"Font weight", L"How thick the letters are.", L"Medium", {{L"Light", L"Light"}, {L"Normal", L"Regular"}, {L"Medium", L"Medium"}, {L"SemiBold", L"Semi-bold"}, {L"Bold", L"Bold"}}, 0, 100, 3, L"Text"},
{K::Number, L"flow:QueryBoxFontSize", L"Search text size", L"12 to 32 (Suggested: 16).", L"16", {}, 12, 32, 3, L"Text"},
{K::Number, L"flow:ResultItemFontSize", L"Result title size", L"10 to 28 (Suggested: 16).", L"16", {}, 10, 28, 3, L"Text"},
{K::Number, L"flow:ResultSubItemFontSize", L"Result detail size", L"8 to 24 (Suggested: 13).", L"13", {}, 8, 24, 3, L"Text"},
{K::Check, L"flow:UseGlyphIcons", L"Line icons", L"Modules that offer a line icon show it instead of a picture.", L"1", {}, 0, 100, 3, L"Results"},
{K::Check, L"flow:ShowBadges", L"Module badges", L"A small module icon on each result, so you can see where it came from.", L"1", {}, 0, 100, 3, L"Results"},
{K::Check, L"flow:ShowBadgesGlobalOnly", L"Badges only without a module word", L"Shows the badges only when you search everything at once.", L"0", {}, 0, 100, 3, L"Results"},
{K::Check, L"flow:UseClock", L"Clock", L"Shows the time in the empty search box.", L"1", {}, 0, 100, 3, L"Clock"},
{K::Choice, L"flow:TimeFormat", L"Time format", L"", L"hh:mm tt", {{L"hh:mm tt", L"03:05 PM"}, {L"h:mm tt", L"3:05 PM"}, {L"HH:mm", L"15:05"}, {L"hh:mm", L"03:05"}, {L"tt hh:mm", L"PM 03:05"}, {L"HH:mm:ss", L"15:05:09"}, {L"hh:mm:ss tt", L"03:05:09 PM"}}, 0, 100, 3, L"Clock"},
{K::Check, L"flow:UseDate", L"Date", L"Shows the date next to the time.", L"1", {}, 0, 100, 3, L"Clock"},
{K::Choice, L"flow:DateFormat", L"Date format", L"", L"MM'/'dd ddd", {{L"MM'/'dd ddd", L"11/14 Sat"}, {L"MM'/'dd dddd", L"11/14 Saturday"}, {L"MM'/'dd", L"11/14"}, {L"dd'/'MM", L"14/11"}, {L"ddd MM'/'dd", L"Sat 11/14"}, {L"ddd dd'/'MM", L"Sat 14/11"}, {L"dddd dd', 'MMMM", L"Saturday 14, November"}, {L"dd', 'MMMM", L"14, November"}, {L"dddd", L"Saturday"}}, 0, 100, 3, L"Clock"},
{K::Check, L"flow:ShowPlaceholder", L"Hint text", L"Grey text in the empty search box.", L"0", {}, 0, 100, 3, L"Hint"},
{K::Text, L"flow:PlaceholderText", L"Hint", L"Leave it empty for \"Type here to search\".", L"", {}, 0, 100, 3, L"Hint"},
{K::Check, L"flow:UseAnimation", L"Open animation", L"", L"1", {}, 0, 100, 3, L"Motion and sound"},
{K::Choice, L"flow:AnimationSpeed", L"Animation speed", L"", L"Medium", {{L"Slow", L"Slow"}, {L"Medium", L"Medium"}, {L"Fast", L"Fast"}, {L"Custom", L"Your own length (below)"}}, 0, 100, 3, L"Motion and sound"},
{K::Number, L"flow:CustomAnimationLength", L"Your own length", L"100 to 1000 milliseconds (Suggested: 360). Used when the speed is \"Your own length\".", L"360", {}, 100, 1000, 3, L"Motion and sound"},
{K::Check, L"flow:UseSound", L"Open sound", L"", L"1", {}, 0, 100, 3, L"Motion and sound"},
{K::Number, L"flow:SoundVolume", L"Sound volume", L"0 to 100 (Suggested: 50).", L"50", {}, 0, 100, 3, L"Motion and sound"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to open these settings. Right-click it to open Halo or restart its search engine. When off, Ctrl + I in Halo still opens this window.", L"1", {}, 0, 100, 3, L"Settings window"}
    };
    // The Modules page: one group per module the engine loaded.
    for (const auto& p : ::halobridge::Plugins()) {
        PCWSTR name = Pool(p.name.empty() ? p.id : p.name);
        std::wstring about = p.desc;
        if (!p.author.empty() || !p.version.empty()) {
            if (!about.empty() && about.back() != L'.') about += L'.';
            if (!about.empty()) about += L' ';
            about += L"Version " + p.version + (p.author.empty() ? L"" : L", by " + p.author) + L".";
        }
        SetField on{K::Check, Pool(L"plugin:" + p.id + L":on"), L"Turned on", Pool(about), L"1", {}, 0, 100,
                    kHaloPluginsPage, name};
        fields.push_back(on);
        SetField kw{K::Text, Pool(L"plugin:" + p.id + L":kw"), L"Words that call it",
                    L"Several words work. * means all.",
                    Pool(p.defaultKeywords.empty() ? p.keywords : p.defaultKeywords), {}, 0, 100, kHaloPluginsPage, name};
        fields.push_back(kw);
    }
    return fields;
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"General", L"The keys that open Halo, where it shows and what it keeps.", 0xE80F},
{L"Search", L"How Halo finds and ranks results.", 0xE721},
{L"Keys", L"Keys inside the open window. Click a box, press the keys. Esc cancels, Backspace clears.", 0xE765},
{L"Look", L"Glass, size, text, the clock, motion and sound.", 0xE790},
{L"Modules", L"Turn modules on or off and change the words that call them.", 0xEA86},
{L"About", L"Version, credits, support and links.", 0xE946},
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
// Middle-click autoscroll: no movement inside kSetAutoDead, then speed grows with distance.
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://github.com/Flow-Launcher/Flow.Launcher";
constexpr PCWSTR kSetWoxUrl = L"https://github.com/Wox-launcher/Wox";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BHalo%20Launcher%5D%20";
constexpr PCWSTR kSetTitle = L"Halo Launcher";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;
constexpr float kSetMenuPad = 6, kSetMenuIconW = 22, kSetMenuSepH = 9, kSetMenuOverlap = 3, kSetMenuMinW = 190, kSetMenuMaxW = 640, kSetMenuBorderW = 2;
constexpr UINT kSetMenuSubDelayMs = 200, kSetMenuFadeMs = 90, kSetMenuTimerSub = 0x5E71, kSetMenuTimerFade = 0x5E72, kSetMenuTimerPoll = 0x5E73;

struct SetItem {
    enum Type { Group, Row, Banner, About, Link, Support, PlugCard, PlugPanel, Seg } type = Row;
    int field = -1;  // Row: index into fields.
    float y = 0, h = 0;
    std::wstring text, sub, url;
    float x = 0, w = 0;   // Halo: an item in a column of the plugin grid (w 0: the full content width).
    float head = 0;       // Halo: a plugin card's clickable top (it folds the card).
    int aux = -1;         // Halo: a card's "turned on" field; a Seg's view (0 grid, 1 list).
    int card = -1;        // Halo: the card a body item belongs to (a Row with a card is drawn bare).
    std::wstring note;    // Halo: a card's version and author line.
    bool open = false;    // Halo: a grid tile whose open card sits under its row.
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
    // Middle-click autoscroll: the anchor in content DIPs; autoA eases the indicator in and out.
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
    if (!::halobridge::Ready())
        return L"Halo's search engine is starting. Its settings and modules show up here in a few seconds.";
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

static bool Set_FamilyExists(const std::wstring& name, IDWriteFactory* dw = nullptr) {
    if (!dw) dw = g_setDw.get();
    SetCom<IDWriteFontCollection> sys;
    if (name.empty() || !dw || FAILED(dw->GetSystemFontCollection(sys.put(), FALSE))) return false;
    UINT32 index = 0;
    BOOL exists = FALSE;
    return SUCCEEDED(sys->FindFamilyName(name.c_str(), &index, &exists)) && exists;
}

// The font setting, or its Nerd Font build ("Fira Code" is installed as
// "FiraCode Nerd Font"), or Segoe UI.
static std::wstring Set_ResolveFamily(IDWriteFactory* dw = nullptr) {
    PCWSTR setting = Wh_GetStringSetting(L"fontFamily");
    std::wstring family = setting && *setting ? setting : L"FiraCode Nerd Font";
    Wh_FreeStringSetting(setting);
    return Set_FamilyExists(family, dw) ? family : L"Segoe UI";
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
    // The menu can open before the settings window ever made the shared factories, so it
    // checks the font with its own (0.6.1 crashed here on the first empty-space right-click).
    std::wstring family = Set_ResolveFamily(s.dw.get());
    auto make = [&](float size, DWRITE_TEXT_ALIGNMENT align, SetCom<IDWriteTextFormat>& out, bool icon = false) {
        if (FAILED(s.dw->CreateTextFormat((icon ? L"FiraCode Nerd Font" : family.c_str()), nullptr, icon ? DWRITE_FONT_WEIGHT_NORMAL : WeightOf(g.fontWeight), DWRITE_FONT_STYLE_NORMAL,
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
           make(15, DWRITE_TEXT_ALIGNMENT_CENTER, s.fGlyph, true) && make(12, DWRITE_TEXT_ALIGNMENT_CENTER, s.fGlyphS, true);
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

// std::wstring(L"FiraCode Nerd Font") at 500; emphasis is one step heavier, never past bold.
static void Set_MakeFormats(SetWindow& w) {
    w.family = Set_ResolveFamily();
    w.iconFamily = Set_FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    int base = (int)WeightOf(g.fontWeight);
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Launcher") <= railW) break;
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

// Owned: values come from Windhawk (mod keys) or from the search engine (keys with ':').
// A field the owner has changed but not saved keeps its value. When the plugin list itself
// changed, the fields are rebuilt, keeping changed values by key.
static void Set_BuildAndClamp(SetWindow& w);
static void Set_SetStatus(SetWindow& w, PCWSTR text, bool error);
// "Ctrl+O" and "Ctrl + O" are the same key to Flow's parser; the window shows the spaced one.
static std::wstring Halo_KeyText(const std::wstring& v) {
    std::wstring out, part;
    auto flush = [&] {
        size_t a = part.find_first_not_of(L' '), b = part.find_last_not_of(L' ');
        if (a == std::wstring::npos) return;
        if (!out.empty()) out += L" + ";
        out += part.substr(a, b - a + 1);
    };
    for (wchar_t c : v) {
        if (c == L'+') {
            flush();
            part.clear();
        } else {
            part += c;
        }
    }
    flush();
    return out;
}

static std::wstring Set_EngineValue(const SetField& f, bool* found) {
    std::wstring key = f.key;
    *found = false;
    if (key.rfind(L"flow:", 0) == 0) {
        std::wstring v = ::halobridge::Setting(key.substr(5), found);
        if (f.kind == SetField::Check) return v == L"True" || v == L"true" || v == L"1" ? L"1" : L"0";
        if (f.kind == SetField::Number) return std::to_wstring((int)std::lround(_wtof(v.c_str())));
        if (f.kind == SetField::Hotkey) return Halo_KeyText(v);
        return v;
    }
    if (key.rfind(L"plugin:", 0) == 0) {
        size_t c = key.rfind(L':');
        std::wstring id = key.substr(7, c - 7), what = key.substr(c + 1);
        for (const auto& p : ::halobridge::Plugins()) {
            if (p.id != id) continue;
            *found = true;
            return what == L"on" ? (p.disabled ? L"0" : L"1") : p.keywords;
        }
    }
    return L"";
}

static std::wstring Set_PluginKey(const std::vector<SetField>& fields) {
    std::wstring s;
    for (const auto& f : fields)
        if (wcsncmp(f.key, L"plugin:", 7) == 0) s += f.key;
    return s;
}

static void Set_LoadFields(SetWindow& w) {
    if (w.editing < 0 && w.recording < 0 && w.openSel < 0) {
        std::vector<SetField> fresh = Set_MakeFields();
        if (Set_PluginKey(fresh) != Set_PluginKey(w.fields)) {
            std::map<std::wstring, std::pair<std::wstring, std::wstring>> kept;
            for (const auto& f : w.fields)
                if (Set_FieldValue(f) != f.value) kept[f.key] = {f.cur, f.value};
            w.fields = std::move(fresh);
            for (auto& f : w.fields) {
                auto it = kept.find(f.key);
                if (it != kept.end()) {
                    f.cur = it->second.first;
                    f.value = it->second.second;
                }
            }
            w.focus = -1;
            if (w.hwnd) Set_BuildAndClamp(w);
        }
    }
    for (auto& f : w.fields) {
        bool touched = !f.value.empty() && Set_FieldValue(f) != f.value;
        if (touched) continue;
        if (wcschr(f.key, L':')) {
            bool found = false;
            std::wstring v = Set_EngineValue(f, &found);
            if (!found) {
                if (f.value.empty()) Set_PutValue(f, f.def);
            } else {
                Set_PutValue(f, v);
            }
        } else {
            bool isInt = f.kind == SetField::Number || f.kind == SetField::Check;
            Set_PutValue(f, isInt ? std::to_wstring(Wh_GetIntSetting(f.key)) : GetStringSetting(f.key));
        }
        f.value = Set_FieldValue(f);  // What the window shows, so an untouched field never saves.
    }
    std::wstring error = ::halobridge::TakeError();
    if (!error.empty() && w.hwnd) Set_SetStatus(w, error.c_str(), true);
    if (w.hwnd) InvalidateRect(w.hwnd, nullptr, FALSE);
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
            if (wcsncmp(f.key, L"plugin:", 7) == 0) {  // Halo: a plugin's words fill its card.
                p.box = {row.left + kSetRowPad, mid - h, r, mid + h};
                break;
            }
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
    if (it.w > 0) return {it.x, it.y, it.x + it.w, it.y + it.h};  // Halo: a column of the plugin grid.
    return {w.contentX, it.y, w.contentX + w.contentW, it.y + it.h};  // Content y (not scrolled).
}

// Lays out the current page's items for the current width.
// Halo's About card and link rows grow with their text (the window can be as narrow as 900).
constexpr PCWSTR kHaloAboutDesc = L"Press a key, type a few letters, press Enter. Apps, files, sums and every module.";
constexpr PCWSTR kHaloAboutMade = L"Made by DavidHiFi. A fast launcher with its own look, built for Windows 11.";
static std::wstring Halo_AboutVer() {
#ifdef WH_MOD_VERSION
    return std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    return L"MIT license  \u00B7  A Windhawk mod";
#endif
}
// Card height. ys gets the tops of the version, description and credit lines, then their end.
static float Halo_AboutLayout(SetWindow& w, float* ys) {
    float tw = std::max(80.0f, w.contentW - 128), y = 48, at[4];
    at[0] = y;
    y += Set_TextH(w.fHint.get(), Halo_AboutVer(), tw) + 6;
    at[1] = y;
    y += Set_TextH(w.fHint.get(), kHaloAboutDesc, tw) + 4;
    at[2] = y;
    y += Set_TextH(w.fHint.get(), kHaloAboutMade, tw);
    at[3] = y;
    if (ys) std::copy(at, at + 4, ys);
    return std::max(146.0f, std::ceil(y + 18));
}
static float Halo_LinkH(SetWindow& w, const std::wstring& sub) {
    return std::max(56.0f, std::ceil(30 + Set_TextH(w.fHint.get(), sub, w.contentW - kSetRowPad - 50) + 10));
}
// ---- Halo: the Plugins page cards ----------------------------------------------
// The grid uses the page's whole width: as many columns as fit, an open card spans its row.
constexpr float kHaloCardMinW = 280, kHaloCardGap = 12, kHaloCardPad = 16, kHaloSegW = 84, kHaloSegH = 30;
constexpr float kHaloPanelMaxW = 920;  // a module's own settings: laid out for about this width
constexpr int kHaloMaxCols = 8;
static int g_haloView = -1;  // 0 grid, 1 list; read once from the mod's stored state.
[[clang::no_destroy]] static std::set<std::wstring> g_haloOpen;  // Plugin ids whose card is open.
static int Halo_View() {
    if (g_haloView < 0) g_haloView = GetState(StateKey(L"Settings", L"PluginView").c_str(), 0) == 1 ? 1 : 0;
    return g_haloView;
}
static float Halo_LineH(IDWriteTextFormat* f) { return Set_TextH(f, L"Ag", 1000); }
static D2D1_RECT_F Halo_CardSwitch(const SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    float mid = r.top + kHaloCardPad + 10;
    return {r.right - kHaloCardPad - 40, mid - 11, r.right - kHaloCardPad, mid + 11};
}
static float Halo_DescW(const SetItem& it) { return it.w - 38 - kHaloCardPad; }
// Where an open card's body lines start, from the card's top. panelH < 0: the module has no
// settings of its own.
struct HaloBody { float note, rule, cap, box, hint, rule2, panel, end; };
static HaloBody Halo_Body(float head, float line, float panelH) {
    HaloBody b;
    b.note = head;
    b.rule = b.note + line + 12;
    b.cap = b.rule + 13;
    b.box = b.cap + line + 4;
    b.hint = b.box + 40 + 2;
    if (panelH >= 0) {
        b.rule2 = b.hint + line + 14;
        b.panel = b.rule2 + 15;
        b.end = b.panel + panelH + kHaloCardPad;
    } else {
        b.rule2 = b.panel = -1;
        b.end = b.hint + line + kHaloCardPad;
    }
    return b;
}
// "12 modules, 9 on", read from the switches as they are now.
static std::wstring Halo_CountText(const SetWindow& w) {
    int on = 0, total = 0;
    for (const auto& f : w.fields)
        if (f.kind == SetField::Check && wcsncmp(f.key, L"plugin:", 7) == 0) total++, on += f.cur == L"1";
    if (!total) return L"No modules yet";
    return std::to_wstring(total) + (total == 1 ? L" module, " : L" modules, ") + std::to_wstring(on) + L" on";
}
static SetItem Halo_CardBase(const SetWindow& w, size_t k, const HaloBridgePlugin* pl, const std::wstring& id) {
    SetItem card;
    card.type = SetItem::PlugCard;
    card.aux = (int)k;
    card.text = w.fields[k].group;
    card.sub = pl ? pl->desc : L"";
    if (card.sub.empty()) card.sub = L"No description.";
    if (pl && (!pl->version.empty() || !pl->author.empty()))
        card.note = (pl->version.empty() ? L"" : L"Version " + pl->version) +
                    (pl->version.empty() || pl->author.empty() ? L"" : L"  \u00B7  ") +
                    (pl->author.empty() ? L"" : L"by " + pl->author);
    card.url = L"halo:fold:" + id;
    return card;
}
// An open card at card.x, card.y, card.w with its body: the words that call it, then the
// module's own settings right in the card. Returns its height.
static float Halo_AddOpenCard(SetWindow& w, SetItem card, size_t k, const HaloBridgePlugin* pl, const std::wstring& id,
                              float nameH, float line) {
    float top = kHaloCardPad + nameH + 4;
    card.head = top + Set_TextH(w.fHint.get(), card.sub, Halo_DescW(card)) + 8;
    bool settings = pl && pl->hasSettings;
    HaloBridgePanel bp;
    bool known = settings && ::halobridge::Panel(id, &bp);
    bool live = known && !bp.failed && bp.px > 0 && bp.child && IsWindow(bp.child);
    float panelH = !settings ? -1.0f : live ? bp.px * 96.0f / (float)w.dpi : line + 12;
    HaloBody b = Halo_Body(card.head, line, panelH);
    card.h = b.end;
    int ci = (int)w.items.size();
    w.items.push_back(card);
    if (k + 1 < w.fields.size()) {
        SetItem words;
        words.type = SetItem::Row;
        words.field = (int)k + 1;  // The "words that call it" field follows its switch.
        words.card = ci;
        words.x = card.x;
        words.w = card.w;
        words.y = card.y + b.box;
        words.h = 40;
        w.items.push_back(words);
    }
    if (settings) {
        SetItem pn;
        pn.type = SetItem::PlugPanel;
        pn.card = ci;
        pn.url = id;
        pn.x = card.x + kHaloCardPad;
        pn.w = std::min(card.w - 2 * kHaloCardPad, kHaloPanelMaxW);
        pn.y = card.y + b.panel;
        pn.h = panelH;
        pn.aux = live ? bp.px : 0;
        pn.sub = live ? L"" : known && bp.failed ? L"Its settings could not load. Close this card and open it again to retry."
                                                 : L"Loading its settings";
        w.items.push_back(pn);
    }
    return card.h;
}
// Lays the cards out from y; returns the y under them.
static float Halo_BuildPlugins(SetWindow& w, float y) {
    const auto& plugins = ::halobridge::Plugins();
    const bool grid = Halo_View() == 0;
    const float nameH = Halo_LineH(w.fLabel.get()), line = Halo_LineH(w.fHint.get());
    // The toolbar: how many there are, then the grid and list switch on the right.
    SetItem g;
    g.type = SetItem::Group;
    g.text = Halo_CountText(w);
    g.url = L"halo:count";
    g.y = y + 6;
    g.h = 22;
    w.items.push_back(g);
    for (int v = 0; v < 2; v++) {
        SetItem s;
        s.type = SetItem::Seg;
        s.aux = v;
        s.text = v ? L"List" : L"Grid";
        s.url = v ? L"halo:view:list" : L"halo:view:grid";
        s.w = kHaloSegW;
        s.x = w.contentX + w.contentW - (2 - v) * kHaloSegW - (1 - v) * 6;
        s.y = y;
        s.h = kHaloSegH;
        w.items.push_back(s);
    }
    y += kHaloSegH + 14;
    struct Entry { size_t k; std::wstring id; const HaloBridgePlugin* pl; };
    std::vector<Entry> list;
    for (size_t k = 0; k < w.fields.size(); k++) {
        const SetField& f = w.fields[k];
        if (f.kind != SetField::Check || wcsncmp(f.key, L"plugin:", 7) != 0) continue;
        std::wstring key = f.key, id = key.substr(7, key.size() - 10);
        const HaloBridgePlugin* pl = nullptr;
        for (const auto& p : plugins)
            if (p.id == id) pl = &p;
        list.push_back({k, id, pl});
    }
    const int cols =
        grid ? std::clamp((int)((w.contentW + kHaloCardGap) / (kHaloCardMinW + kHaloCardGap)), 1, kHaloMaxCols) : 1;
    const float colW = (w.contentW - (cols - 1) * kHaloCardGap) / cols;
    const float closedH = kHaloCardPad + nameH + 4 + 2 * line + 14;  // Every closed card the same height.
    for (size_t r0 = 0; r0 < list.size(); r0 += cols) {
        std::vector<size_t> opened;
        for (int c = 0; c < cols && r0 + c < list.size(); c++) {
            const Entry& e = list[r0 + c];
            SetItem card = Halo_CardBase(w, e.k, e.pl, e.id);
            card.x = w.contentX + c * (colW + kHaloCardGap);
            card.w = colW;
            card.y = y;
            bool open = g_haloOpen.count(e.id) > 0;
            if (open && cols == 1) {  // The list opens a card in place.
                y += Halo_AddOpenCard(w, card, e.k, e.pl, e.id, nameH, line) - closedH;
                continue;
            }
            card.h = card.head = closedH;
            card.open = open;
            w.items.push_back(card);
            if (open) opened.push_back(r0 + c);
        }
        y += closedH + kHaloCardGap;
        // The grid: an open tile's card spans the full width under its row.
        for (size_t i : opened) {
            const Entry& e = list[i];
            SetItem card = Halo_CardBase(w, e.k, e.pl, e.id);
            card.x = w.contentX;
            card.w = w.contentW;
            card.y = y;
            y += Halo_AddOpenCard(w, card, e.k, e.pl, e.id, nameH, line) + kHaloCardGap;
        }
    }
    return y;
}
static void Set_CommitEdit(SetWindow& w, bool apply);
// After a fold or a view change: the page is laid out again where it is.
static void Halo_Relayout() {
    if (!g_setWin) return;
    Set_CommitEdit(*g_setWin, true);
    Set_BuildAndClamp(*g_setWin);
}
static void Set_BuildPage(SetWindow& w) {
    w.items.clear();
    const float space = Set_RailSpace(w), avail = w.cw - space;
    const float maxW = w.page == kHaloPluginsPage && Halo_View() == 0 ? 100000.0f : kSetMaxW;  // the grid fills the page
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, maxW);
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), kSetPages[w.page].intro, w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
    if (w.page != kSetAboutPage) {
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
        if (wcsncmp(f.key, L"plugin:", 7) == 0) continue;  // Cards, laid out below.
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
    if (w.page == kHaloPluginsPage) y = Halo_BuildPlugins(w, y);
    if (w.page == kSetAboutPage) {
        auto add = [&](SetItem::Type t, float h, PCWSTR text, PCWSTR sub, PCWSTR url) {
            SetItem it;
            it.type = t;
            it.y = y;
            it.h = t == SetItem::Link ? Halo_LinkH(w, sub) : h;
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
        add(SetItem::About, Halo_AboutLayout(w, nullptr), L"", L"", L"");
        add(SetItem::Support, 84, L"Like it? Keep it going.",
            L"Free and open source. A tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        add(SetItem::Link, 56, L"Search engine: Flow Launcher", L"Used under the MIT licence", kSetDittoUrl);
        add(SetItem::Link, 56, L"And from Wox", L"Where that code began, MIT licence", kSetWoxUrl);
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
    p.GradFill(mark, 18, 1);
    ::HaloGlyph(p.rt, mark, p.fade);
    float x = mark.right + 20, ys[4];
    Halo_AboutLayout(w, ys);
    p.Text(w.fBig.get(), L"Halo Launcher", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
    p.Text(w.fHint.get(), Halo_AboutVer(), {x, row.top + ys[0], row.right - 16, row.top + ys[1]}, mocha::subtext0);
    p.Text(w.fHint.get(), kHaloAboutDesc, {x, row.top + ys[1], row.right - 16, row.top + ys[2]}, mocha::subtext1);
    p.Text(w.fHint.get(), kHaloAboutMade, {x, row.top + ys[2], row.right - 16, row.top + ys[3] + 2}, mocha::overlay2);
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
    p.Text(w.fRailName.get(), L"Halo", {d.left + 90, d.top + 9, d.left + w.railW - 10, d.top + 33}, mocha::text, textA);
    p.Text(w.fRailName.get(), L"Launcher", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    (void)glyph;
    ::HaloGlyph(p.rt, r, p.fade);
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

// The autoscroll anchor, in Seamless Autoscroll's look: a frosted Mocha disc with the 2px blue to
// mauve ring, an arrow that lights blue the way the page moves, and a mauve centre dot.
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

// ---- Halo: painting the Plugins page cards ---------------------------------------
// Text that wraps but stops at maxH, with "..." where it is cut.
static void Halo_TextClamp(SetPaint& p, IDWriteTextFormat* f, const std::wstring& s, const D2D1_RECT_F& r, UINT32 c) {
    SetCom<IDWriteTextLayout> l;
    if (!f || s.empty() ||
        FAILED(g_setDw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, r.right - r.left, r.bottom - r.top, l.put())))
        return;
    SetCom<IDWriteInlineObject> sign;
    g_setDw->CreateEllipsisTrimmingSign(l.get(), sign.put());
    DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_WORD, 0, 0};
    l->SetTrimming(&t, sign.get());
    p.rt->PushAxisAlignedClip(r, D2D1_ANTIALIAS_MODE_ALIASED);
    p.rt->DrawTextLayout(D2D1::Point2F(r.left, r.top), l.get(), p.B(c));
    p.rt->PopAxisAlignedClip();
}

static float Halo_CardGlow(const SetWindow& w, int idx) {
    float g = Set_GlowOf(w, 3000 + idx);
    for (size_t i = idx + 1; i < w.items.size() && w.items[i].card == idx; i++) {
        const SetItem& b = w.items[i];
        g = std::max(g, b.type == SetItem::Row ? std::max(Set_GlowOf(w, 1000 + b.field), Set_GlowOf(w, 6000 + b.field))
                                               : Set_GlowOf(w, 3000 + (int)i));
    }
    return g;
}

static void Halo_DrawPlugCard(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    float hov = Halo_CardGlow(w, idx);
    const SetItem* panel = nullptr;  // the module's own settings, when the card is open
    for (size_t i = idx + 1; i < w.items.size() && w.items[i].card == idx; i++)
        if (w.items[i].type == SetItem::PlugPanel) panel = &w.items[i];
    // A tile whose card is open under its row keeps its ring lit, so the two read as one.
    float ring = it.open ? std::max(hov, 0.85f) : hov;
    Set_DrawCard(p, r, ring);
    // No hover tint over a card that holds a settings panel: the panel's colour is the card's.
    if (!(panel && panel->aux > 0)) p.GradFill(r, 10, 0.13f * hov);
    p.GradRing(r, 10, ring, 1.5f);
    const SetField* f = it.aux >= 0 && it.aux < (int)w.fields.size() ? &w.fields[it.aux] : nullptr;
    bool on = f && f->cur == L"1", open = it.h > it.head + 1;
    const float nameH = Halo_LineH(w.fLabel.get()), line = Halo_LineH(w.fHint.get());
    float top = r.top + kHaloCardPad;
    p.Glyph(w.fIconS.get(), open || it.open ? 0xE70D : 0xE76C, {r.left + 10, top, r.left + 34, top + nameH},
            hov > 0.5f || it.open ? mocha::text : mocha::overlay2);
    D2D1_RECT_F sw = Halo_CardSwitch(w, it);
    p.Text(w.fLabel.get(), it.text, {r.left + 38, top, sw.left - 12, top + nameH + 2}, on ? mocha::text : mocha::overlay1);
    D2D1_RECT_F desc{r.left + 38, top + nameH + 4, r.left + 38 + Halo_DescW(it), r.top + it.head - (open ? 8 : 14) + 1};
    Halo_TextClamp(p, w.fHint.get(), it.sub, desc, on ? mocha::subtext0 : mocha::overlay0);
    // The switch, drawn as the template draws a Check, so it animates the same.
    if (f) {
        float kn = w.knob.count(it.aux) ? w.knob.at(it.aux) : (on ? 1.0f : 0.0f);
        p.Round(sw, 11, mocha::surface1);
        p.GradFill(sw, 11, kn);
        float cx = sw.left + 11 + kn * 18, cy = (sw.top + sw.bottom) / 2;
        p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8, 8), p.B(on ? mocha::crust : mocha::text));
        if (w.kbd && w.focus == it.aux) p.GradRing({sw.left - 3, sw.top - 3, sw.right + 3, sw.bottom + 3}, 14, 1, 2);
    }
    if (!open) return;
    HaloBody b = Halo_Body(it.head, line, panel ? panel->h : -1.0f);
    float l = r.left + kHaloCardPad, rr = r.right - kHaloCardPad;
    p.Text(w.fHint.get(), it.note.empty() ? std::wstring(L"No version given") : it.note,
           {r.left + 38, r.top + b.note, rr, r.top + b.note + line + 2}, mocha::overlay1);
    p.Fill({l, r.top + b.rule, rr, r.top + b.rule + 1}, mocha::surface1, 0.7f);
    p.Text(w.fHint.get(), L"Words that call it", {l, r.top + b.cap, rr, r.top + b.cap + line + 2}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Several words work. * means every search.", {l, r.top + b.hint, rr, r.top + b.hint + line + 2},
           mocha::overlay1);
    if (panel) p.Fill({l, r.top + b.rule2, rr, r.top + b.rule2 + 1}, mocha::surface1, 0.7f);
}

// The words box of an open card: the template's Text box, with no row card around it.
static void Halo_DrawWordsBox(SetPaint& p, SetWindow& w, const SetItem& it) {
    const SetField& f = w.fields[it.field];
    int k = it.field;
    SetParts pt = Set_Parts(f, Set_RowRect(w, it));
    const D2D1_RECT_F& b = pt.box;
    bool ed = w.editing == k;
    Set_DrawBox(p, w, k, b, ed || (w.kbd && w.focus == k));
    if (!ed)
        p.Text(w.fValue.get(), f.cur.empty() ? std::wstring(L"None, so it never shows") : f.cur,
               {b.left + 12, b.top, b.right - 10, b.bottom}, f.cur.empty() ? mocha::overlay0 : mocha::text);
}

// A module's own settings: the engine's panel window sits here. Until it does (or when it could
// not load), a quiet line says so.
static void Halo_DrawPlugPanel(SetPaint& p, SetWindow& w, const SetItem& it) {
    if (it.aux > 0) return;
    D2D1_RECT_F r = Set_RowRect(w, it);
    p.Text(w.fHint.get(), it.sub, {r.left, r.top, r.right, r.bottom}, mocha::overlay1);
}

static void Halo_DrawSeg(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    bool sel = it.aux == Halo_View();
    float hov = Set_GlowOf(w, 3000 + idx);
    if (sel) {
        p.GradFill(r, 8, 0.9f + 0.1f * hov);
    } else {
        p.Round(r, 8, kSetBoxFill);
        p.Edge(r, 8, mocha::overlay0, 0.7f * (1 - hov), 1.25f);
        p.GradFill(r, 8, 0.13f * hov);
    }
    p.GradRing(r, 8, hov, 1.75f);
    UINT32 c = sel ? mocha::crust : mocha::subtext1;
    p.Glyph(w.fIconS.get(), it.aux ? 0xE8FD : 0xF0E2, {r.left + 8, r.top, r.left + 32, r.bottom}, c);
    p.Text(w.fValue.get(), it.text, {r.left + 34, r.top, r.right - 8, r.bottom}, sel ? mocha::crust : mocha::text);
}

// ---- Halo: a module's own settings, inside its open card ----------------------------
// The engine builds the module's settings panel (the one Flow shows in its own settings) as a
// child window of a holder this window owns. The holder sits where the card's panel item is,
// cut to the visible page (under the title bar, not under the footer dock), so the panel
// scrolls with the page. The engine reports the panel's height; the card grows to fit it.
constexpr wchar_t kHaloPanelClass[] = L"HaloPanelHolder";
struct HaloPanelHost {
    HWND clip = nullptr;
    int askedW = 0;  // the width the engine was last asked for, in pixels
    RECT at{}, vis{}, foot{};
    bool shown = false;
};
[[clang::no_destroy]] static std::map<std::wstring, HaloPanelHost> g_haloPanels;
struct HaloPanelDying {
    HWND clip, child;
    DWORD tick;
};
[[clang::no_destroy]] static std::vector<HaloPanelDying> g_haloPanelsDying;

static LRESULT CALLBACK Halo_PanelProc(HWND h, UINT m, WPARAM wp, LPARAM lp) {
    if (m == WM_ERASEBKGND) return 1;
    if (m == WM_PAINT) {  // Only seen where the panel does not reach: the card's own colour.
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(h, &ps);
        HBRUSH b = CreateSolidBrush(RGB(0x24, 0x24, 0x35));
        FillRect(dc, &ps.rcPaint, b);
        DeleteObject(b);
        EndPaint(h, &ps);
        return 0;
    }
    return DefWindowProcW(h, m, wp, lp);
}

static void Halo_RegisterPanelClass() {
    static bool done = false;
    if (done) return;
    done = true;
    UnregisterClassW(kHaloPanelClass, (HINSTANCE)&__ImageBase);  // a class left by an older build
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = Halo_PanelProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kHaloPanelClass;
    RegisterClassExW(&wc);
}

// Holders whose panel the engine has let go of (or that waited long enough) are destroyed.
static void Halo_ReapPanels(bool all) {
    for (size_t i = 0; i < g_haloPanelsDying.size();) {
        const HaloPanelDying& d = g_haloPanelsDying[i];
        if (all || !d.child || !IsWindow(d.child) || GetTickCount() - d.tick > 3000) {
            if (!all && IsWindow(d.clip)) DestroyWindow(d.clip);
            g_haloPanelsDying.erase(g_haloPanelsDying.begin() + i);
        } else {
            i++;
        }
    }
}

static void Halo_ClosePanel(const std::wstring& id, HaloPanelHost& h) {
    HaloBridgePanel bp;
    HWND child = ::halobridge::Panel(id, &bp) ? bp.child : nullptr;
    ::halobridge::DropPanel(id);
    ::halobridge::SendLine({L"panelclose", id});
    if (h.clip) {
        ShowWindow(h.clip, SW_HIDE);
        g_haloPanelsDying.push_back({h.clip, child, GetTickCount()});
    }
}

// The settings window is going: the engine lets go of every panel (their windows go with ours).
static void Halo_DropAllPanels() {
    for (auto& kv : g_haloPanels) ::halobridge::DropPanel(kv.first);
    if (!g_haloPanels.empty() || !g_haloPanelsDying.empty()) ::halobridge::SendLine({L"panelclose", L"*"});
    g_haloPanels.clear();
    Halo_ReapPanels(true);
}

static void Halo_PlacePanels(SetWindow& w);

// Halo's own messages on the settings window: a panel came, changed height or went (wParam 1: a
// new engine, ask it again), and the window going. Hooked here so the shared window code stays
// the same as every other mod's.
static LRESULT CALLBACK Halo_SetHook(HWND h, UINT m, WPARAM wp, LPARAM lp, UINT_PTR id, DWORD_PTR) {
    if (m == WM_APP_SETTINGS_PANELS) {
        SetWindow* w = g_setWin && g_setWin->hwnd == h ? g_setWin.get() : nullptr;
        if (wp == 1)
            for (auto& kv : g_haloPanels) kv.second.askedW = 0;
        Halo_ReapPanels(false);
        if (w && w->page == kHaloPluginsPage) {
            Set_BuildAndClamp(*w);
            Halo_PlacePanels(*w);
            InvalidateRect(h, nullptr, FALSE);
        }
        return 0;
    }
    if (m == WM_DESTROY) Halo_DropAllPanels();
    if (m == WM_NCDESTROY) RemoveWindowSubclass(h, Halo_SetHook, id);
    return DefSubclassProc(h, m, wp, lp);
}

// Puts every open card's panel where its card is now. Cheap when nothing moved.
static void Halo_PlacePanels(SetWindow& w) {
    if (w.render || !w.hwnd) return;
    Halo_RegisterPanelClass();
    SetWindowSubclass(w.hwnd, Halo_SetHook, 0x4841, 0);  // once per window; a repeat call is a no-op
    const bool onPage = w.page == kHaloPluginsPage;
    std::set<std::wstring> want;
    if (onPage)
        for (const auto& it : w.items)
            if (it.type == SetItem::PlugPanel) want.insert(it.url);
    for (auto i = g_haloPanels.begin(); i != g_haloPanels.end();) {
        if (want.count(i->first)) {
            ++i;
            continue;
        }
        Halo_ClosePanel(i->first, i->second);
        i = g_haloPanels.erase(i);
    }
    Halo_ReapPanels(false);
    if (!onPage) return;
    const float s = (float)w.dpi / 96.0f;
    auto px = [&](float v) { return (int)std::lround(v * s); };
    const float viewH = Set_ViewH(w);
    RECT view{px(Set_RailSpace(w) + 4), px(kSetCapH), px(w.cw), px(kSetCapH + viewH)};
    D2D1_RECT_F fd = Set_FooterDock(w);
    RECT foot{px(fd.left) - 2, px(fd.top + kSetCapH) - 2, px(fd.right) + 2, px(fd.bottom + kSetCapH) + 2};
    for (const auto& it : w.items) {
        if (it.type != SetItem::PlugPanel) continue;
        HaloPanelHost& h = g_haloPanels[it.url];
        if (!h.clip) {
            h.clip = CreateWindowExW(WS_EX_NOPARENTNOTIFY, kHaloPanelClass, L"", WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                                     0, 0, 1, 1, w.hwnd, nullptr, (HINSTANCE)&__ImageBase, nullptr);
            if (!h.clip) continue;
        }
        const int wpx = std::max(1, px(it.w));
        if (h.askedW != wpx) {
            wchar_t hw[24];
            swprintf(hw, 24, L"%llu", (unsigned long long)(ULONG_PTR)h.clip);
            if (::halobridge::SendLine({L"panel", it.url, hw, std::to_wstring(wpx), w.family})) h.askedW = wpx;
        }
        HaloBridgePanel bp;
        bool live = it.aux > 0 && ::halobridge::Panel(it.url, &bp) && !bp.failed && bp.child && IsWindow(bp.child);
        RECT at{px(it.x), px(it.y - w.scrollY + kSetCapH), 0, 0};
        at.right = at.left + wpx;
        at.bottom = at.top + (live ? bp.px : 0);
        RECT vis{};
        if (!live || w.pageT < 1 || !IntersectRect(&vis, &at, &view)) {
            if (h.shown) ShowWindow(h.clip, SW_HIDE);
            h.shown = false;
            continue;
        }
        OffsetRect(&vis, -at.left, -at.top);
        RECT f = foot;
        OffsetRect(&f, -at.left, -at.top);
        // A move or a new cut on a shown holder repaints all of it: bits copied along or newly
        // uncovered would keep stale pixels (the footer pill smeared down the panel on scroll).
        bool dirty = false;
        if (!EqualRect(&vis, &h.vis) || !EqualRect(&f, &h.foot) || !h.shown) {
            dirty = h.shown;
            HRGN rgn = CreateRectRgnIndirect(&vis);
            HRGN pill = CreateRoundRectRgn(f.left, f.top, f.right + 1, f.bottom + 1, f.bottom - f.top, f.bottom - f.top);
            CombineRgn(rgn, rgn, pill, RGN_DIFF);
            DeleteObject(pill);
            SetWindowRgn(h.clip, rgn, FALSE);  // the window owns rgn now
            h.vis = vis;
            h.foot = f;
        }
        if (!EqualRect(&at, &h.at) || !h.shown) {
            SetWindowPos(h.clip, HWND_TOP, at.left, at.top, at.right - at.left, at.bottom - at.top,
                         SWP_NOACTIVATE | SWP_NOCOPYBITS | (h.shown ? 0 : SWP_SHOWWINDOW));
            h.at = at;
            dirty = dirty || h.shown;
        }
        if (dirty) RedrawWindow(h.clip, nullptr, nullptr, RDW_INVALIDATE | RDW_ALLCHILDREN);
        if (!h.shown) {
            ShowWindow(h.clip, SW_SHOWNA);
            h.shown = true;
        }
    }
}

static void Set_Draw(SetWindow& w, ID2D1RenderTarget* rt) {
    if (Set_FitBoxes(w)) {
        Set_BuildPage(w);
        Set_PlaceEdit(w);
    }
    Halo_PlacePanels(w);
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
            place((it.card >= 0 ? it.card : (int)i) + 2, rise);  // A card's body rises with its card.
            switch (it.type) {
                case SetItem::Group:
                    if (it.url == L"halo:count") {
                        SetItem live = it;
                        live.text = Halo_CountText(w);
                        Set_DrawGroup(cp, w, live);
                    } else {
                        Set_DrawGroup(cp, w, it);
                    }
                    break;
                case SetItem::Row:
                    if (it.card >= 0) Halo_DrawWordsBox(cp, w, it);
                    else Set_DrawRow(cp, w, it);
                    break;
                case SetItem::PlugCard: Halo_DrawPlugCard(cp, w, it, (int)i); break;
                case SetItem::PlugPanel: Halo_DrawPlugPanel(cp, w, it); break;
                case SetItem::Seg: Halo_DrawSeg(cp, w, it, (int)i); break;
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
    for (size_t i = w.items.size(); i-- > 0;) {  // Last first: a card's body sits on top of its card.
        const SetItem& it = w.items[i];
        D2D1_RECT_F row = Set_RowRect(w, it);
        if (!Set_In(row, x, cy)) continue;
        if (it.type == SetItem::PlugCard) {
            h.id = 3000 + (int)i;  // The whole card lights; its top folds it, its switch turns it on or off.
            if (it.aux >= 0 && Set_In(Halo_CardSwitch(w, it), x, cy)) {
                h.kind = SetHit::Control;
                h.a = it.aux;
            } else if (cy < it.y + it.head) {
                h.kind = SetHit::Link;
                h.a = (int)i;
            }
        } else if (it.type == SetItem::PlugPanel) {
            h.id = 3000 + it.card;  // Over the settings stand-in the card stays lit; nothing to click.
        } else if (it.type == SetItem::Link || it.type == SetItem::Seg) {
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
    g_recWin = 0;
    ::HaloRecording(false);
    if (w.status.rfind(L"Press the keys", 0) == 0) Set_SetStatus(w, L"");
    
    Set_Invalidate(w);
}

static void Set_StartRecording(SetWindow& w, int k) {
    Set_StopRecording(w);
    w.recording = k;
    ::HaloRecording(true);
    // Our own keys would fire instead of reaching the window while it listens.
    if (!w.render) {
        SetFocus(w.hwnd);
    }
    Set_SetStatus(w, L"Press the keys now");
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
    std::wstring u = url;  // url can point into an item, and the page is laid out again below.
    if (u.rfind(L"halo:fold:", 0) == 0) {
        std::wstring id = u.substr(10);
        if (!g_haloOpen.erase(id)) g_haloOpen.insert(id);
        Halo_Relayout();
        return;
    }
    if (u.rfind(L"halo:view:", 0) == 0) {
        g_haloView = u.substr(10) == L"list" ? 1 : 0;
        SetState(StateKey(L"Settings", L"PluginView").c_str(), g_haloView);
        Halo_Relayout();
        return;
    }
    ShellExecuteW(nullptr, L"open", u.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
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
        if (wcschr(f.key, L':')) continue;  // The engine's own, saved by Set_SaveEngine.
        std::wstring value = Set_FieldValue(f);
        if (value != f.value) {
            params += L" " + Set_QuoteArg(std::wstring(f.key) + L"=" + value);
            changed++;
        }
    }
    return params;
}

// Sends the engine's changed fields. Returns how many were sent, or -1 when it isn't running.
static int Set_SaveEngine(SetWindow& w) {
    int sent = 0;
    bool any = false;
    for (auto& f : w.fields) {
        if (!wcschr(f.key, L':')) continue;
        std::wstring value = Set_FieldValue(f);
        if (value == f.value) continue;
        any = true;
        std::wstring key = f.key;
        bool ok;
        if (key.rfind(L"flow:", 0) == 0) {
            ok = ::halobridge::SendLine({L"flowset", key.substr(5), value});
        } else {
            size_t c = key.rfind(L':');
            ok = ::halobridge::SendLine({L"plugset", key.substr(7, c - 7), key.substr(c + 1), value});
        }
        if (!ok) return -1;
        f.value = value;
        sent++;
    }
    return any ? sent : 0;
}

static void Set_ApplyFrame(SetWindow& w);

static void Set_Save(std::shared_ptr<SetWindow> keep) {
    SetWindow& w = *keep;
    if (w.saving) return;
    Set_StopRecording(w);
    int engine = Set_SaveEngine(w);
    int changed = 0;
    std::wstring params = Set_ChangedParams(w, changed);
    if (!changed) {
        if (engine < 0) Set_SetStatus(w, L"Engine off, not saved", true);
        else Set_SetStatus(w, engine ? L"Saved" : L"Nothing changed");
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
        Set_SetStatus(w, L"Couldn't write the file", true);
        return;
    }
    for (auto& f : w.fields) f.value = Set_FieldValue(f);
    Set_SetStatus(w, L"Saved");
    return;
#else
    if (cli.empty()) {
        Set_SetStatus(w, L"Windhawk tool missing", true);
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
            Set_SetStatus(w, L"Admin prompt refused", true);
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
        Set_SetStatus(w, L"Windhawk didn't answer", true);
    } else if (code == 0) {
        for (auto& f : w.fields)
            if (!wcschr(f.key, L':')) f.value = Set_FieldValue(f);  // Stored now, so a reload reads them.
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

// ---- Middle-click autoscroll (every settings window, 2026-11-16) ----------------------
// Press the middle button and move: the page scrolls, faster the farther the pointer is from
// where it started. Press and release without moving: it keeps going until the next click, a
// key or the wheel. Press, move and release: it stops on release. Browser behaviour.

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

// The pointer moved while autoscrolling: keep the scroll cursor, and note a drag with the button held.
static void Set_AutoScrollMove(SetWindow& w, bool held) {
    if (held && fabsf(w.mouseY - w.autoY) > kSetAutoDead) w.autoMoved = true;
    SetCursor(LoadCursorW(nullptr, IDC_SIZENS));
}

// One timer tick of autoscroll. True when something on screen changed.
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
        else if (it.type == SetItem::PlugCard && !it.open) order.push_back(it.aux);  // Halo: Tab reaches a card's switch.
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
        if (Set_IsModifier(vk)) {
            if ((vk == VK_LWIN || vk == VK_RWIN) && !g_recWin) {
                g_recWin = vk;
                // An unused key while Win is down keeps the Start menu shut when it comes up.
                INPUT in[2]{};
                in[0].type = in[1].type = INPUT_KEYBOARD;
                in[0].ki.wVk = in[1].ki.wVk = 0xE8;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(2, in, sizeof(INPUT));
            } else if (vk != VK_LWIN && vk != VK_RWIN) {
                g_recWin = 0;
            }
            return true;
        }
        g_recWin = 0;
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

static void Set_TakeStartPage();
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
        case WM_APP_SETTINGS_ACTIVATE: ShowWindow(hwnd, SW_RESTORE); Set_TakeStartPage(); ForceForeground(hwnd); return 0;
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
            RECT r{0, 0, MulDiv(900, w->dpi, 96), MulDiv(520, w->dpi, 96)};
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
        case WM_KEYUP:
        case WM_SYSKEYUP:
            if (w->recording >= 0 && g_recWin && wParam == g_recWin) {
                w->fields[w->recording].cur = g_recWin == VK_RWIN ? L"RWin" : L"LWin";
                Set_StopRecording(*w);
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Halo Launcher settings", style,
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


// The page the next open or activation shows (-1: wherever it was).
std::atomic<int> g_settingsStartPage{-1};
static void Set_TakeStartPage() {
    int page = g_settingsStartPage.exchange(-1);
    if (page >= 0 && g_setWin) Set_GoPage(*g_setWin, page);
}
DWORD WINAPI SettingsThread(void*) {
 SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
 CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
 Settings_Open();
 if (g_setWin) g_settingsWnd=g_setWin->hwnd;
 Set_TakeStartPage();
 MSG msg;
 while (g_settingsWnd && GetMessageW(&msg,nullptr,0,0)>0) { TranslateMessage(&msg); DispatchMessageW(&msg); }
 Settings_Close(); UnregisterClassW(kSettingsClass,(HINSTANCE)&__ImageBase); Set_ReleaseFactories(); CoUninitialize(); return 0;
}
void OpenSettingsWindow(int page) {
 g_settingsStartPage=page;
 if (HWND hwnd=g_settingsWnd) { PostMessageW(hwnd,WM_APP_SETTINGS_ACTIVATE,0,0); return; }
 if(g_settingsThread) { if(WaitForSingleObject(g_settingsThread,0)==WAIT_TIMEOUT) return; CloseHandle(g_settingsThread); }
 g_settingsStop=false; g_settingsThread=CreateThread(nullptr,0,SettingsThread,nullptr,0,nullptr);
}
void CloseSettingsWindow() {
 g_settingsStop=true;
 if(HWND hwnd=g_settingsWnd) PostMessageW(hwnd,WM_CLOSE,0,0);
 if(g_settingsThread) { WaitForSingleObject(g_settingsThread,15000); CloseHandle(g_settingsThread); g_settingsThread=nullptr; }
}

// Halo's own menus (empty-area and result right-click) in the engine's look. Core builds
// plain rows; they become the engine's rows here, submenus included.
static SetMenuItem Set_FromHalo(const HaloMenuItem& h) {
    if (h.separator) return Set_MenuSep();
    SetMenuItem m = Set_MenuRow(h.id, h.glyph.c_str(), h.label.c_str(), h.checked, h.disabled, h.hint.c_str());
    for (const auto& s : h.sub) m.sub.push_back(Set_FromHalo(s));
    return m;
}
int ShowMenu(HWND owner, const std::vector<HaloMenuItem>& items, const POINT* at) {
    std::vector<SetMenuItem> rows;
    for (const auto& h : items) rows.push_back(Set_FromHalo(h));
    return Set_TrayMenu(owner, rows, at);
}

// The tray menu: the engine's own menu (Set_TrayMenu). Ids match the tray code's enum.
int ShowTrayMenu(HWND owner, const POINT* at) {
    return Set_TrayMenu(owner, {Set_MenuRow(1, L"\uEB44", L"Open Halo Launcher"),
                                Set_MenuRow(2, L"\uEB51", L"Settings"),
                                Set_MenuSep(),
                                Set_MenuRow(3, L"\uEB37", L"Restart its search engine")}, at);
}
}  // namespace haloset
