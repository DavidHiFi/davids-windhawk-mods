// ==WindhawkMod==
// @id              seamless-task-manager
// @name            Seamless Task Manager
// @description     Every Task Manager tweak in one mod, with the Catppuccin Mocha look on its menus, flyouts and accents
// @version         1.0.0
// @author          DavidHiFi, GF-Huang, Luiz Bizzio, sb4ssman, chenxustu1, Joe Ye, Nehoray-Bitan, Abdullah Masood, m417z
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         Taskmgr.exe
// @include         windhawk.exe
// @architecture    x86-64
// @license         GPL-3.0
// @donateUrl       https://ko-fi.com/DavidHiFi
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshlwapi -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -ladvapi32 -lurlmon -lwininet -loleacc -lversion -lmsimg32 -lruntimeobject
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Task Manager

Every Task Manager tweak in one mod, each one a switch in the settings, plus the
Catppuccin Mocha look on Task Manager's menus, flyouts, tooltips, dialogs and
accent colours.

## What's new in 1.0.0

- Nine Task Manager mods merged into one, with every setting carried over.
- The Mocha look: frosted menus and flyouts with a grey edge, blue to mauve accents.
- Its own settings window and tray icon. Click the tray icon to turn the look on or off.

## What it does

| Switch | What you get | Based on |
|---|---|---|
| Hide the navigation border | No focus border around the side menu | [Disable Task Manager Navigation Border](https://windhawk.net/mods/disable-taskmgr-navigation-border) by [GF-Huang](https://github.com/GF-Huang) |
| Normal size icons on Details | Details and Services icons at a normal size | [Fix Task Manager Details Icon Size](https://windhawk.net/mods/fix-taskmgr-details-icon-size) by [GF-Huang](https://github.com/GF-Huang) |
| Pause button | Pause and resume the selected app | [Task Manager Pause Button](https://windhawk.net/mods/task-manager-pause-button) by [Luiz Bizzio](https://github.com/luizbizzio) |
| Esc closes Task Manager | Esc closes the window | [Press Esc to exit Task Manager](https://windhawk.net/mods/taskmgr-esc) by [chenxustu1](https://github.com/chenxustu1) |
| Show link speed | Live link speed per network adapter | [Task Manager Show Link Speed](https://windhawk.net/mods/taskmgr-link-speed) by [Joe Ye](https://github.com/JoeYe-233) |
| Network speed in bytes | KB/s, MB/s and GB/s instead of bits | [Task Manager Network Speed in Bytes](https://windhawk.net/mods/taskmgr-network-bytes) by [Nehoray-Bitan](https://github.com/Nehoray-Bitan) |
| Animate switching pages | A crossfade or slide between pages | [Task Manager Tab Slide Animation](https://windhawk.net/mods/taskmgr-tab-slide-animation) by [Abdullah Masood](https://github.com/Abdullah-Masood-05) |
| Taller tabs (Windows 10) | Bigger tab labels on the old Task Manager | [Make Task Manager Tabs Taller](https://windhawk.net/mods/taskmgr-taller-tab) by [Joe Ye](https://github.com/JoeYe-233) |
| Keep Task Manager last on the taskbar | Its button stays at the end | [Task Manager Tail](https://windhawk.net/mods/task-manager-tail) by [sb4ssman](https://github.com/sb4ssman) |

The look is drawn with the styling engine of
[Windows Settings Styler](https://windhawk.net/mods/windows-settings-styler) by
[m417z](https://github.com/m417z). Colours from
[Catppuccin Mocha](https://github.com/catppuccin/catppuccin).

## Notes

- The process lists themselves are drawn by an older part of Windows that the
  look can't reach. Menus, flyouts, tooltips, dialogs and accents get the look.
- Window edges and the title bar come from Seamless Title Bars and the window
  border mods, and Win32 menus from Seamless Flyouts, so nothing is drawn twice.
- Turn off the original nine mods while this one is on.

Made by [DavidHiFi](https://github.com/DavidHiFi). Like it?
[Support on Ko-fi](https://ko-fi.com/DavidHiFi).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- featureNavBorder: true
  $name: Hide the navigation border
  $description: Removes the focus border Task Manager draws around the side menu and other controls. From Disable Task Manager Navigation Border by GF-Huang.
- featureDetailsIcon: true
  $name: Normal size icons on Details
  $description: Gives the Details and Services lists normal size icons. From Fix Task Manager Details Icon Size by GF-Huang.
- cellSize: 32
  $name: Cell size
  $name:zh-CN: 单元格大小
  $description: The size of the cell occupied by the icon (in pixels, ranging from 24 to 256) is used as the margin around the icon.
  $description:zh-CN: 图标所占单元格的大小（像素，24-256），用作图标四周的留空。
  #! $min: 24
  #! $max: 256
- iconSize: 24
  $name: Icon size
  $name:zh-CN: 图标大小
  $description: Icon size in pixels; cannot exceed cell size (16-256)
  $description:zh-CN: 图标大小（像素，16-256），不能超过单元格大小
  #! $min: 16
  #! $max: 256
- featurePauseButton: true
  $name: Pause button
  $description: Adds a Pause and Resume button to Processes and Details, for the selected app. From Task Manager Pause Button by Luiz Bizzio.
- featureEsc: true
  $name: Esc closes Task Manager
  $description: Press Esc to close Task Manager. From Press Esc to exit Task Manager by chenxustu1.
- featureLinkSpeed: true
  $name: Show link speed
  $description: Shows each network adapter's live link speed on the Performance page. From Task Manager Show Link Speed by Joe Ye.
- CustomLabelOverrideEnabled: false
  $name: Enable custom label text
  $name:zh-CN: 启用自定义标签文本
  $description: Default = False, which means using the system's built-in multilingual "Link speed" as the label text in Task Manager. Enable this option to use custom text.
  $description:zh-CN: 图表页面默认使用系统自带的多语言“链接速度”作为项目名称，如需自定义文本可启用该选项
- CustomLabelOverrideText: ""
  $name: Custom label text
  $name:zh-CN: 自定义标签文本
  $description: "Custom label text for Task Manager (example: Link speed)"
  $description:zh-CN: "任务管理器中显示的自定义标签文本（例如: 链路速度）"
- featureNetworkBytes: true
  $name: Network speed in bytes
  $description: Shows network speed as KB/s, MB/s and GB/s instead of bits. From Task Manager Network Speed in Bytes by Nehoray-Bitan.
- unitNames: english
  $name: Unit names
  $description: >-
    English always shows KB/s, MB/s and GB/s. Task Manager's language uses the
    translated unit names Task Manager shows for disk rates. Graph labels
    update after Task Manager is restarted.
  $options:
  - english: English (KB/s, MB/s, GB/s)
  - localized: Task Manager's display language
- featureTabSlide: true
  $name: Animate switching pages
  $description: A crossfade or slide when you switch pages. From Task Manager Tab Slide Animation by Abdullah Masood.
- animation_type: fade
  $name: Animation type
  $description: How the new tab appears.
  $options:
  - fade: Crossfade (no visual jump)
  - slide: Slide
- duration_ms: 250
  $name: Animation duration (ms)
  $description: How long the transition lasts. Clamped to 60-1500.
- top_inset: 48
  $name: Top inset (px)
  $description: Height of the top command bar to exclude from the animation, at 100% display scaling. It's scaled automatically for other scaling levels.
- capture_delay_ms: 140
  $name: Capture delay (ms)
  $description: Delay after the click before capturing the new view. Raise if it grabs the old view.
- change_threshold: 2
  $name: Change threshold (%)
  $description: Minimum percent of the region that must change for the animation to play. Raise to reduce spurious animations.
- slide_vertical: false
  $name: Slide vertically (slide mode only)
  $description: Slide up/down instead of left/right. Only affects the Slide animation.
- featureTallerTab: true
  $name: Taller tabs (Windows 10)
  $description: Makes the old Windows 10 tab labels taller so they are easier to click. From Make Task Manager Tabs Taller by Joe Ye.
- featureTail: true
  $name: Keep Task Manager last on the taskbar
  $description: Moves Task Manager's taskbar button to the end of the taskbar. From Task Manager Tail by sb4ssman.
- targetName: Task Manager
  $name: Target Button Name
  $description: The text on the taskbar button (partial match). Change this for other languages (e.g., "Gestionnaire").
- targetClass: TaskManagerWindow
  $name: Target Window Class
  $description: The internal class name of the window. Use "Notepad" to tail Notepad, etc.
- moveDelay: 100
  $name: Move Delay (ms)
  $description: How long to wait before moving the button after a check confirms it is out of place.
- debounceTime: 300
  $name: Event Debounce Time (ms)
  $description: How long to wait after window events stop occurring before checking the taskbar.
- theme: Mocha
  $name: Look
  $description: Catppuccin Mocha on Task Manager's menus, flyouts, tooltips, dialogs and accent colours. None keeps Task Manager's own look.
  $options:
  - Mocha: Catppuccin Mocha
  - "": None
- toggleHotkey: ""
  $name: Turn the Mocha look on or off
  $description: Press the keys in the box. Backspace clears it. The tray icon does the same.
- settingsGlass: true
  $name: Blurred settings window
  $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.
- nativeSettingsTitleBar: false
  $name: Native Windows title bar
  $description: Use the Windows title bar and window buttons for this settings window. Applies when you save.
- settingsTrayIcon: true
  $name: Tray icon
  $description: Click it to turn the Mocha look on or off. Right-click it for these settings. When off, change settings in Windhawk.
- styleConstants: [""]
  $name: Style constants
  $description: >-
    Some themes support style constants for customization, such as colors. Refer
    to the theme page for available constants. For technical details, refer to
    the mod description.
- controlStyles:
  - - target: ""
      $name: Target
    - styles: [""]
      $name: Styles
  $name: Control styles
- themeResourceVariables: [""]
  $name: Resource variables
  $description: >-
    Use "Key=Value" to override an existing resource with a new value.

    Use "Key@Dark=Value" or "Key@Light=Value" to define theme-aware resources
    that can be referenced with {ThemeResource Key} in styles.

    The ":=" syntax can be used to set a XAML value. For details, refer to the
    mod description.
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <Windows.h>
#include <commctrl.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d2d1helper.h>
#include <dwmapi.h>
#include <dwrite.h>
#include <inspectable.h>
#include <objbase.h>
#include <psapi.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <shobjidl.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <strsafe.h>
#include <uiautomation.h>
#include <uxtheme.h>
#include <wchar.h>
#include <wincodec.h>
#include <windowsx.h>
#include <windhawk_utils.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <map>
#include <memory>
#include <mutex>
#include <regex>
#include <set>
#include <string>
#include <string_view>
#include <vector>

#undef GetCurrentTime

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Navigation.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/base.h>
#include <winrt/Windows.UI.Xaml.h>

#include <xamlom.h>

void WhTool_ModUninit();
namespace stmset {
void OpenSettingsWindow();
void CloseSettingsWindow();
int ShowTrayMenu(HWND owner, const POINT* at, bool on, PCWSTR hotkey);
extern std::atomic<HWND> g_settingsWnd;
}  // namespace stmset

void WhTool_ModUninit();

namespace f_tail {
bool ToolInit();
void ToolUninit();
void ToolSettingsChanged();
}  // namespace f_tail


// ---------------------------------------------------------------------------
// Shortcuts: "Ctrl+Alt+K" text, the same the settings window's key box writes.
// ---------------------------------------------------------------------------

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return {};
    return s.substr(a, s.find_last_not_of(L" \t\r\n") - a + 1);
}

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

namespace {

std::atomic<bool> g_stop = false;
std::atomic<bool> g_enabled = true;
bool g_trayIconOn = true;
std::wstring g_hotkeyText;
HMODULE g_module = nullptr;
DWORD g_uiThreadId = 0;
HANDLE g_uiThread = nullptr;
HANDLE g_uiReady = nullptr;
HANDLE g_instanceMutex = nullptr;
HWND g_msgWnd = nullptr;
bool g_tailStarted = false;

HMODULE StmModuleHandle() {
    HMODULE module = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)&StmModuleHandle, &module);
    return module;
}

std::wstring ReadString(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) {
        Wh_FreeStringSetting(p);
    }
    return s;
}

void ReadSettings() {
    g_trayIconOn = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    g_hotkeyText = Trim(ReadString(L"toggleHotkey"));

    // With no tray icon and no shortcut nothing could turn it back on.
    if (!g_trayIconOn && g_hotkeyText.empty() && !g_enabled.load()) {
        g_enabled.store(true);
        Wh_SetIntValue(L"enabled", 1);
    }
    Wh_Log(L"Settings: tray %d, shortcut \"%s\"", (int)g_trayIconOn, g_hotkeyText.c_str());
}

// After the elevated relaunch, Windhawk can load this mod a moment late when
// the PC is busy. windhawk-mod.exe then shows a false "Running the tool mod
// failed" box even though the mod loads and works. Close that box, only in
// this process, during the first seconds.
BOOL CALLBACK CloseFalseFailureBox(HWND hwnd, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != GetCurrentProcessId()) {
        return TRUE;
    }
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

DWORD WINAPI FalseFailureBoxThreadProc(LPVOID) {
    for (int i = 0; i < 60 && !g_stop.load(std::memory_order_relaxed); i++) {
        EnumWindows(CloseFalseFailureBox, 0);
        Sleep(250);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// UI thread: tray icon, menu, shortcut.
// ---------------------------------------------------------------------------

constexpr UINT WM_AC_TRAY = WM_APP + 45;
constexpr UINT WM_AC_SETTINGS = WM_APP + 46;
constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
constexpr int kHotkeyId = 1;
UINT g_taskbarCreated = 0;
bool g_trayAdded = false;
HICON g_trayIcon = nullptr;
bool g_hotkeyOn = false;

void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// A rounded square drawn with GDI, so the tray never shares the settings
// window's Direct2D factories. On: a pointer on the blue to mauve gradient.
// Off: a pause sign on grey.
HICON MakeTrayIcon(bool on) {
    int size = GetSystemMetricsForDpi(SM_CXSMICON, GetDpiForSystem());
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
    // Glyph coverage: white text on black, read back from one channel.
    HDC dc = CreateCompatibleDC(nullptr);
    HGDIOBJ old = SelectObject(dc, glyph);
    memset(glyphBits, 0, (size_t)size * size * 4);
    HFONT font = CreateFontW(-(int)(size * 0.62f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    WCHAR face[64]{};
    GetTextFaceW(dc, 64, face);
    if (_wcsicmp(face, L"Segoe Fluent Icons") != 0) {
        SelectObject(dc, oldFont);
        DeleteObject(font);
        font = CreateFontW(-(int)(size * 0.62f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                           ANTIALIASED_QUALITY, 0, L"Segoe MDL2 Assets");
        oldFont = SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)(on ? 0xE9D9 : 0xE769), 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    // Mocha blue 89B4FA to mauve CBA6F7; grey overlay0 to surface2 when off. Glyph in crust 11111B.
    const float c0[3] = {on ? 0x89 / 255.f : 0x6C / 255.f, on ? 0xB4 / 255.f : 0x70 / 255.f, on ? 0xFA / 255.f : 0x86 / 255.f};
    const float c1[3] = {on ? 0xCB / 255.f : 0x58 / 255.f, on ? 0xA6 / 255.f : 0x5B / 255.f, on ? 0xF7 / 255.f : 0x70 / 255.f};
    const float ink[3] = {0x11 / 255.f, 0x11 / 255.f, 0x1B / 255.f};
    float radius = size * 0.26f, half = size / 2.0f;
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            // Signed distance to the rounded square, for a soft edge.
            float qx = std::fabs(x + 0.5f - half) - (half - radius), qy = std::fabs(y + 0.5f - half) - (half - radius);
            float ox = std::max(qx, 0.0f), oy = std::max(qy, 0.0f);
            float d = std::sqrt(ox * ox + oy * oy) + std::min(std::max(qx, qy), 0.0f) - radius;
            float a = std::clamp(0.5f - d, 0.0f, 1.0f);
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = (base + (ink[i] - base) * cov) * a;  // Premultiplied.
            }
            px[y * size + x] = ((uint32_t)(a * 255 + 0.5f) << 24) | ((uint32_t)(rgb[0] * 255 + 0.5f) << 16) |
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

void TrayTip(NOTIFYICONDATAW& nid) {
    PCWSTR tip = g_enabled.load() ? L"Seamless Task Manager: Mocha look on."
                                  : L"Seamless Task Manager: off. Click to turn it on.";
    wcsncpy_s(nid.szTip, tip, _TRUNCATE);
}

void UpdateTray(bool add) {
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    if (!g_trayIconOn) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
        return;
    }
    HICON icon = MakeTrayIcon(g_enabled.load());
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_AC_TRAY;
    nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    TrayTip(nid);
    if (!g_trayAdded || add) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
        if (g_trayAdded) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = icon;
}

void RegisterToggleHotkey() {
    if (g_hotkeyOn) UnregisterHotKey(g_msgWnd, kHotkeyId);
    g_hotkeyOn = false;
    UINT mods, vk;
    if (g_hotkeyText.empty()) return;
    if (!Hotkey_Parse(g_hotkeyText, mods, vk)) {
        Wh_Log(L"Shortcut \"%s\" isn't one the mod understands", g_hotkeyText.c_str());
        return;
    }
    g_hotkeyOn = RegisterHotKey(g_msgWnd, kHotkeyId, mods | MOD_NOREPEAT, vk) != FALSE;
    if (!g_hotkeyOn) Wh_Log(L"Shortcut %s is taken by another app (error %lu)", g_hotkeyText.c_str(), GetLastError());
}

void SetEnabled(bool on, PCWSTR why) {
    g_enabled.store(on);
    Wh_SetIntValue(L"enabled", on ? 1 : 0);
    Wh_Log(L"Mocha look %s (%s)", on ? L"on" : L"off", why);
    UpdateTray(false);
}

enum : UINT { IDM_TOGGLE = 100, IDM_SETTINGS };

void ShowTrayMenu(POINT pt) {
    int cmd = stmset::ShowTrayMenu(g_msgWnd, &pt, g_enabled.load(), g_hotkeyOn ? g_hotkeyText.c_str() : L"");
    if (cmd == IDM_TOGGLE) SetEnabled(!g_enabled.load(), L"tray menu");
    else if (cmd == IDM_SETTINGS) stmset::OpenSettingsWindow();
}

LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == g_taskbarCreated && g_taskbarCreated) {
        g_trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    switch (msg) {
        case WM_HOTKEY:
            if (wp == kHotkeyId) SetEnabled(!g_enabled.load(), L"shortcut");
            return 0;
        case WM_AC_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: SetEnabled(!g_enabled.load(), L"tray icon"); break;
                case WM_CONTEXTMENU: ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_AC_SETTINGS:
            ReadSettings();
            RegisterToggleHotkey();
            UpdateTray(false);
            if (HWND s = stmset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

DWORD WINAPI UiThreadProc(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    EnableDarkMenus();
    WNDCLASSW wc{};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = (HINSTANCE)StmModuleHandle();
    wc.lpszClassName = L"SeamlessTaskManagerMsg";
    RegisterClassW(&wc);
    g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless Task Manager", WS_POPUP, 0, 0, 0, 0,
                               nullptr, nullptr, wc.hInstance, nullptr);
    if (g_msgWnd) {
        // This copy runs as administrator; let Explorer's tray messages through.
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_msgWnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        ChangeWindowMessageFilterEx(g_msgWnd, WM_AC_TRAY, MSGFLT_ALLOW, nullptr);
        RegisterToggleHotkey();
        UpdateTray(true);
    }
    SetEvent(g_uiReady);
    if (!g_msgWnd) return 1;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    if (g_hotkeyOn) UnregisterHotKey(g_msgWnd, kHotkeyId);
    g_hotkeyOn = false;
    if (g_trayAdded) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = g_msgWnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    DestroyWindow(g_msgWnd);
    g_msgWnd = nullptr;
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}

void StopThread(HANDLE& t, DWORD tid) {
    if (!t) return;
    if (tid) PostThreadMessageW(tid, WM_QUIT, 0, 0);
    WaitForSingleObject(t, 5000);
    CloseHandle(t);
    t = nullptr;
}

}  // namespace

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

// ===========================================================================
// disable-taskmgr-navigation-border
// ===========================================================================
namespace f_navborder {
namespace {

// x64 non-static member functions receive the AtmView* in RCX.
using SetBorder_t = void(__cdecl *)(void *view);

SetBorder_t SetBorderUponNavigationForColumnHeader_Original;
SetBorder_t SetBorderUponNavigationForListRow_Original;
SetBorder_t SetBorderUponNavigationForListRowWithColumnTraversal_Original;
SetBorder_t SetBorderUponNavigatingIntoElement_Original;

// Intentionally do nothing and never call the original functions.
void __cdecl SetBorderUponNavigationForColumnHeader_Hook(void * /*view*/) {}
void __cdecl SetBorderUponNavigationForListRow_Hook(void * /*view*/) {}
void __cdecl SetBorderUponNavigationForListRowWithColumnTraversal_Hook(void * /*view*/) {}
void __cdecl SetBorderUponNavigatingIntoElement_Hook(void * /*element*/) {}

} // namespace

BOOL ModInit() {
    HMODULE taskmgr = GetModuleHandleW(nullptr);
    if (!taskmgr) {
        Wh_Log(L"Failed to get the Taskmgr.exe module");
        return FALSE;
    }

     // taskmgr.exe
    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {
            { L"private: void __cdecl AtmView::SetBorderUponNavigationForColumnHeader(void)" },
            &SetBorderUponNavigationForColumnHeader_Original,
            SetBorderUponNavigationForColumnHeader_Hook,
        },
        {
            { L"private: void __cdecl AtmView::SetBorderUponNavigationForListRow(void)" },
            &SetBorderUponNavigationForListRow_Original,
            SetBorderUponNavigationForListRow_Hook,
        },
        {
            { L"private: void __cdecl AtmView::SetBorderUponNavigationForListRowWithColumnTraversal(void)" },
            &SetBorderUponNavigationForListRowWithColumnTraversal_Original,
            SetBorderUponNavigationForListRowWithColumnTraversal_Hook,
        },
        {
            { L"void __cdecl SetBorderUponNavigatingIntoElement(class DirectUI::Element *)" },
            &SetBorderUponNavigatingIntoElement_Original,
            SetBorderUponNavigatingIntoElement_Hook,
        },
    };

    if (!WindhawkUtils::HookSymbols(taskmgr, hooks, ARRAYSIZE(hooks))) {
        Wh_Log(L"Failed to resolve/hook the required Task Manager border methods");
        return FALSE;
    }

    Wh_Log(L"Hooks installed");
    return TRUE;
}
}  // namespace f_navborder


// ===========================================================================
// fix-taskmgr-details-icon-size
// ===========================================================================
namespace f_detailsicon {
namespace {

constexpr int kOldCellSize = 24;
int g_cellSize = 32;
constexpr int kOldIconSize = 16;
int g_iconSize = 24;

int GetIconOffset() {
    return (g_cellSize - g_iconSize) / 2;
}

thread_local unsigned g_wdcImageListCreationDepth;
thread_local unsigned g_wdcIconResizeDepth;

class ScopedCounter {
public:
    explicit ScopedCounter(unsigned& counter) : m_counter(counter) {
        ++m_counter;
    }

    ~ScopedCounter() {
        --m_counter;
    }

    ScopedCounter(const ScopedCounter&) = delete;
    ScopedCounter& operator=(const ScopedCounter&) = delete;

private:
    unsigned& m_counter;
};

using WdcCreateImageList_t = HRESULT(__fastcall*)(void* monitor);
using WdcAddResizedIcon_t = HRESULT(__fastcall*)(void* monitor, HICON icon,
                                                  int* imageIndex);
using ImageListCreate_t = HIMAGELIST(WINAPI*)(int, int, UINT, int, int);
using CreateCompatibleBitmap_t = HBITMAP(WINAPI*)(HDC, int, int);
using FillRect_t = int(WINAPI*)(HDC, const RECT*, HBRUSH);
using CreateBitmap_t = HBITMAP(WINAPI*)(int, int, UINT, UINT, const void*);
using PatBlt_t = BOOL(WINAPI*)(HDC, int, int, int, int, DWORD);
using DrawIconEx_t = BOOL(WINAPI*)(HDC, int, int, HICON, int, int, UINT,
                                   HBRUSH, UINT);

WdcCreateImageList_t WdcCreateImageList_Original;
WdcAddResizedIcon_t WdcAddResizedIcon_Original;
ImageListCreate_t ImageListCreate_Original;
CreateCompatibleBitmap_t CreateCompatibleBitmap_Original;
FillRect_t FillRect_Original;
CreateBitmap_t CreateBitmap_Original;
PatBlt_t PatBlt_Original;
DrawIconEx_t DrawIconEx_Original;

HRESULT __fastcall WdcCreateImageList_Hook(void* monitor) {
    ScopedCounter scope(g_wdcImageListCreationDepth);
    return WdcCreateImageList_Original(monitor);
}

HRESULT __fastcall WdcAddResizedIcon_Hook(void* monitor, HICON icon,
                                           int* imageIndex) {
    ScopedCounter scope(g_wdcIconResizeDepth);
    return WdcAddResizedIcon_Original(monitor, icon, imageIndex);
}

HIMAGELIST WINAPI ImageListCreate_Hook(int cx, int cy, UINT flags,
                                      int initialCount, int growCount) {
    if (g_wdcImageListCreationDepth && cx == kOldCellSize &&
        cy == kOldCellSize) {
        cx = g_cellSize;
        cy = g_cellSize;
    }

    return ImageListCreate_Original(cx, cy, flags, initialCount, growCount);
}

HBITMAP WINAPI CreateCompatibleBitmap_Hook(HDC hdc, int cx, int cy) {
    if (g_wdcIconResizeDepth && cx == kOldCellSize &&
        cy == kOldCellSize) {
        cx = g_cellSize;
        cy = g_cellSize;
    }

    return CreateCompatibleBitmap_Original(hdc, cx, cy);
}

int WINAPI FillRect_Hook(HDC hdc, const RECT* rect, HBRUSH brush) {
    if (g_wdcIconResizeDepth && rect && rect->right == kOldCellSize &&
        rect->bottom == kOldCellSize) {
        RECT adjusted = *rect;
        adjusted.right = g_cellSize;
        adjusted.bottom = g_cellSize;
        return FillRect_Original(hdc, &adjusted, brush);
    }

    return FillRect_Original(hdc, rect, brush);
}

HBITMAP WINAPI CreateBitmap_Hook(int width, int height, UINT planes,
                                 UINT bitCount, const void* bits) {
    if (g_wdcIconResizeDepth && width == kOldCellSize &&
        height == kOldCellSize) {
        width = g_cellSize;
        height = g_cellSize;
    }

    return CreateBitmap_Original(width, height, planes, bitCount, bits);
}

BOOL WINAPI PatBlt_Hook(HDC hdc, int x, int y, int width, int height,
                        DWORD rop) {
    if (g_wdcIconResizeDepth && width == kOldCellSize &&
        height == kOldCellSize) {
        width = g_cellSize;
        height = g_cellSize;
    }

    return PatBlt_Original(hdc, x, y, width, height, rop);
}

BOOL WINAPI DrawIconEx_Hook(HDC hdc, int x, int y, HICON icon, int cx, int cy,
                            UINT step, HBRUSH flickerFree, UINT flags) {
    if (g_wdcIconResizeDepth && x == 4 && y == 4 &&
        cx == kOldIconSize && cy == kOldIconSize) {
        x = GetIconOffset();
        y = GetIconOffset();
        cx = g_iconSize;
        cy = g_iconSize;
    }

    return DrawIconEx_Original(hdc, x, y, icon, cx, cy, step, flickerFree,
                               flags);
}

bool InstallApiHook(HMODULE module, const char* name, void* hook,
                    void** original) {
    if (!module) {
        Wh_Log(L"A required API module isn't loaded");
        return false;
    }

    FARPROC target = GetProcAddress(module, name);
    if (!target) {
        Wh_Log(L"Couldn't resolve a required API");
        return false;
    }

    if (!Wh_SetFunctionHook(reinterpret_cast<void*>(target), hook, original)) {
        Wh_Log(L"Couldn't install a required API hook");
        return false;
    }

    return true;
}

} // namespace

BOOL ModInit() {
    g_cellSize = std::clamp(Wh_GetIntSetting(L"cellSize"), 24, 256);
    g_iconSize = std::clamp(Wh_GetIntSetting(L"iconSize"), 16, g_cellSize);
    HMODULE taskmgr = GetModuleHandleW(nullptr);
    if (!taskmgr) {
        Wh_Log(L"Couldn't get the Taskmgr.exe module handle");
        return FALSE;
    }

    // taskmgr.exe
    const WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {
            { L"public: long __cdecl WdcDataMonitor::CreateImageListWithResizedImage(void)" },
            &WdcCreateImageList_Original,
            WdcCreateImageList_Hook,
        },
        {
            { L"public: long __cdecl WdcDataMonitor::AddResizedIconToImageList(struct HICON__ *,int *)" },
            &WdcAddResizedIcon_Original,
            WdcAddResizedIcon_Hook,
        },
    };
    if (!WindhawkUtils::HookSymbols(taskmgr, hooks, ARRAYSIZE(hooks))) {
        Wh_Log(L"Could not resolve WDC helpers; check the Taskmgr PDB symbols");
        return FALSE;
    }
    HMODULE comctl32 = GetModuleHandleW(L"comctl32.dll");
    HMODULE gdi32 = GetModuleHandleW(L"gdi32.dll");
    HMODULE user32 = GetModuleHandleW(L"user32.dll");

    bool ok = true;
    ok &= InstallApiHook(comctl32, "ImageList_Create",
                         reinterpret_cast<void*>(ImageListCreate_Hook),
                         reinterpret_cast<void**>(&ImageListCreate_Original));
    ok &= InstallApiHook(gdi32, "CreateCompatibleBitmap",
                         reinterpret_cast<void*>(CreateCompatibleBitmap_Hook),
                         reinterpret_cast<void**>(
                             &CreateCompatibleBitmap_Original));
    ok &= InstallApiHook(user32, "FillRect",
                         reinterpret_cast<void*>(FillRect_Hook),
                         reinterpret_cast<void**>(&FillRect_Original));
    ok &= InstallApiHook(gdi32, "CreateBitmap",
                         reinterpret_cast<void*>(CreateBitmap_Hook),
                         reinterpret_cast<void**>(&CreateBitmap_Original));
    ok &= InstallApiHook(gdi32, "PatBlt",
                         reinterpret_cast<void*>(PatBlt_Hook),
                         reinterpret_cast<void**>(&PatBlt_Original));
    ok &= InstallApiHook(user32, "DrawIconEx",
                         reinterpret_cast<void*>(DrawIconEx_Hook),
                         reinterpret_cast<void**>(&DrawIconEx_Original));

    if (!ok) {
        Wh_Log(L"One or more WDC image-size API hooks failed");
        return FALSE;
    }

    Wh_Log(L"PDB-symbol WDC hooks installed: %dpx cells, %dpx icons",
           g_cellSize, g_iconSize);
    return TRUE;
}
}  // namespace f_detailsicon


// ===========================================================================
// task-manager-pause-button
// ===========================================================================
namespace f_pause {
// SPDX-License-Identifier: Apache-2.0
// Copyright 2026 Luiz Bizzio


namespace mux = winrt::Windows::UI::Xaml;
namespace muxc = winrt::Windows::UI::Xaml::Controls;
namespace muxm = winrt::Windows::UI::Xaml::Media;
namespace muxa = winrt::Windows::UI::Xaml::Automation;
namespace wf = winrt::Windows::Foundation;

namespace {
constexpr wchar_t kButtonName[] = L"WindhawkTaskManagerPauseButton";

std::atomic<bool> g_stopping{false};
std::atomic<bool> g_paused{false};
std::atomic<unsigned> g_insertions{0};

uintptr_t g_taskBegin{};
uintptr_t g_taskEnd{};

using GetKeyState_t = decltype(&GetKeyState);
GetKeyState_t g_getKeyOriginal{};

bool IsCtrl(int vk) noexcept {
    return vk == VK_CONTROL || vk == VK_LCONTROL || vk == VK_RCONTROL;
}

bool CalledByTaskManager(uintptr_t returnAddress) noexcept {
    return returnAddress >= g_taskBegin && returnAddress < g_taskEnd;
}

SHORT WINAPI GetKeyState_Hook(int vk) {
    SHORT value = g_getKeyOriginal(vk);
    if (g_paused.load(std::memory_order_relaxed) &&
        !g_stopping.load(std::memory_order_relaxed) && IsCtrl(vk) &&
        CalledByTaskManager(reinterpret_cast<uintptr_t>(__builtin_return_address(0)))) {
        value = static_cast<SHORT>(value | 0x8000);
    }
    return value;
}

struct BarEntry {
    winrt::weak_ref<muxc::CommandBar> bar;
    winrt::weak_ref<muxc::AppBarButton> button;
    DWORD ownerThread{};
    winrt::event_token clickToken{};
    uint64_t entryId{};
    bool clickAttached{};
    // Only true after the complete insertion sequence succeeds. A callback
    // retained after a failed rollback is tracked but is not a usable button.
    bool usable{};
};

std::mutex g_barsMutex;
std::vector<BarEntry> g_bars;
std::atomic<uint64_t> g_nextEntryId{1};
thread_local bool g_addingButton = false;

// Close admission to new insertions before taking a cleanup snapshot. Unlike
// dispatching only to the main HWND, this also covers a separate XAML thread.
std::mutex g_insertionMutex;
std::condition_variable g_insertionDone;
bool g_acceptingInsertions = true;
unsigned g_insertionCount = 0;

struct InsertionGuard {
    bool active{};
    InsertionGuard() {
        std::lock_guard<std::mutex> lock(g_insertionMutex);
        if (!g_acceptingInsertions || g_stopping.load(std::memory_order_acquire))
            return;
        ++g_insertionCount;
        active = true;
    }
    ~InsertionGuard() {
        if (!active) return;
        std::lock_guard<std::mutex> lock(g_insertionMutex);
        if (--g_insertionCount == 0) g_insertionDone.notify_all();
    }
};

void StopNewInsertions() {
    std::lock_guard<std::mutex> lock(g_insertionMutex);
    g_acceptingInsertions = false;
    g_stopping.store(true, std::memory_order_release);
    g_paused.store(false, std::memory_order_release);
}

HWND FindTaskManagerWindow();
void SyncButtons();
std::vector<DWORD> NavigationThreads();
bool RemoveThreadNavigationHooks(DWORD threadId);
void ForgetNavigationThread(DWORD threadId);
void TryAttachFrameNavigation(mux::DependencyObject object);
bool NeedsFrameNavigationScan(winrt::hstring const& pageType,
                              mux::FrameworkElement const& page);
void ForgetHookScanThread(DWORD threadId);

void UpdateButton(muxc::AppBarButton const& button) {
    const bool paused = g_paused.load(std::memory_order_relaxed);
    const wchar_t* caption = paused ? L"Resume" : L"Pause";
    if (button.Label() == caption) return;

    // The label and Click handler must remain usable even if creating or
    // assigning the native SymbolIcon fails on this Task Manager build.
    button.Label(caption);
    try {
        button.Icon(muxc::SymbolIcon(paused ? muxc::Symbol::Play : muxc::Symbol::Pause));
    } catch (...) {
        const HRESULT iconError = winrt::to_hresult();
        // Avoid showing a stale Play/Pause icon from an earlier state.
        try {
            button.Icon(nullptr);
        } catch (...) {
            // The text label remains correct if clearing the icon also fails.
        }
        Wh_Log(L"Pause/Resume icon unavailable (HRESULT=0x%08X); text label kept",
               static_cast<unsigned int>(iconError));
    }
}

void TogglePause() {
    bool was = g_paused.load(std::memory_order_relaxed);
    while (!g_paused.compare_exchange_weak(was, !was, std::memory_order_relaxed)) {}
    SyncButtons();
}

// Identifiers are checked only for their semantic role, not an assumed
// Windows-specific AutomationId spelling. Both anchors must be found.
std::wstring NormalizeIdentifier(winrt::hstring const& value) {
    std::wstring normalized;
    for (wchar_t c : value) {
        if (std::iswalnum(c))
            normalized.push_back(static_cast<wchar_t>(std::towlower(c)));
    }
    return normalized;
}

bool MatchesRole(muxc::AppBarButton const& item, bool runNewTask) {
    const auto label = item.Label();
    if (runNewTask) {
        if (label == L"Run new task" || label == L"Executar nova tarefa")
            return true;
    } else if (label == L"End task" || label == L"Finalizar tarefa") {
        return true;
    }

    const auto matchesId = [runNewTask](winrt::hstring const& identifier) {
        const auto normalized = NormalizeIdentifier(identifier);
        return runNewTask
            ? normalized.find(L"runnewtask") != std::wstring::npos ||
                  normalized.find(L"createnewtask") != std::wstring::npos
            : normalized.find(L"endtask") != std::wstring::npos;
    };
    if (matchesId(item.Name())) return true;
    try {
        return matchesId(muxa::AutomationProperties::GetAutomationId(item));
    } catch (...) {
        // Some builds may not expose a usable AutomationId on this control.
        return false;
    }
}

struct BarCandidate {
    muxc::CommandBar bar{nullptr};
    uint32_t place{};
};

// Resolve native commands by labels/IDs when available. Do not check
// ancestor Visibility here: OnNavigatedTo can fire before page display.
bool InspectBar(muxc::CommandBar const& bar, BarCandidate& candidate) {
    if (!bar) return false;
    auto commands = bar.PrimaryCommands();
    if (!commands) return false;

    bool hasRun = false;
    bool hasEnd = false;
    uint32_t afterRun{};
    for (uint32_t i = 0; i < commands.Size(); ++i) {
        auto item = commands.GetAt(i).try_as<muxc::AppBarButton>();
        if (!item || item.Name() == kButtonName) continue;
        if (MatchesRole(item, true)) {
            hasRun = true;
            afterRun = i + 1;
        }
        if (MatchesRole(item, false)) hasEnd = true;
    }
    if (!hasRun || !hasEnd) return false;
    candidate.bar = bar;
    candidate.place = afterRun;
    return true;
}

// On the tested Task Manager layout, page navigation exposes one CommandBar
// with four native AppBarButtons and Run new task as its first native command.
//
// This is a conservative, language-independent fallback for that layout,
// not a universal identification of the semantic role of each button.
// In particular, don't infer a position from an arbitrary group of 2+ buttons.
// Other layouts can still use the semantic label/identifier matcher.
bool InspectSinglePageBarByStructure(muxc::CommandBar const& bar,
                                     BarCandidate& candidate) {
    if (!bar) return false;
    auto commands = bar.PrimaryCommands();
    if (!commands) return false;

    uint32_t nativeCount = 0;
    uint32_t otherCommands = 0;
    uint32_t ownButtons = 0;
    uint32_t firstNativeIndex = UINT32_MAX;
    for (uint32_t i = 0; i < commands.Size(); ++i) {
        auto button = commands.GetAt(i).try_as<muxc::AppBarButton>();
        if (!button) {
            // A separator can exist in some builds, but do not match bars
            // with an otherwise different collection of commands.
            if (++otherCommands > 1) return false;
            continue;
        }
        if (button.Name() == kButtonName) {
            if (++ownButtons > 1) return false;
            continue;
        }
        if (firstNativeIndex == UINT32_MAX) firstNativeIndex = i;
        if (++nativeCount > 4) return false;
    }

    if (nativeCount != 4 || firstNativeIndex != 0) return false;
    candidate.bar = bar;
    candidate.place = firstNativeIndex + 1;
    return true;
}

// Prefer a verified structural layout when unique to this page-navigation
// scan. If the bar's known labels/IDs contradict the proposed position,
// trust the explicit semantic match instead of moving the native action.
bool InspectProductionBar(muxc::CommandBar const& bar,
                          bool uniquePageBar,
                          BarCandidate& candidate) {
    BarCandidate identified;
    const bool hasIdentifiedRoles = InspectBar(bar, identified);
    if (uniquePageBar) {
        BarCandidate structural;
        if (InspectSinglePageBarByStructure(bar, structural)) {
            if (hasIdentifiedRoles && structural.place != identified.place) {
                Wh_Log(L"Structural placement differs from identified Run new task; using verified label/ID");
                candidate = identified;
            } else {
                candidate = structural;
            }
            return true;
        }
    }
    if (hasIdentifiedRoles) {
        candidate = identified;
        return true;
    }
    return false;
}

// Distinguish a usable button from an incomplete insertion whose Click
// callback could not be revoked. The latter must remain tracked for safe
// unloading, but must NOT count as successful insertion.
enum class InsertStatus { Failed, Ready, RetainedCallback };

InsertStatus TryInsertButton(muxc::CommandBar const& bar, uint32_t place) {
    if (!bar || g_addingButton) return InsertStatus::Failed;
    InsertionGuard insertion;
    if (!insertion.active) return InsertStatus::Failed;
    struct Guard {
        Guard() { g_addingButton = true; }
        ~Guard() { g_addingButton = false; }
    } guard;

    muxc::AppBarButton button{nullptr};
    winrt::event_token clickToken{};
    bool clickAttached = false;
    bool inserted = false;
    bool tracked = false;
    uint64_t entryId{};
    try {
        auto commands = bar.PrimaryCommands();
        if (!commands || place > commands.Size()) return InsertStatus::Failed;

        // Before examining visible commands, avoid inserting another button
        // if a previous rollback left a live Click callback on this bar.
        // Such an entry must be released by the unload path, not overwritten.
        std::vector<BarEntry> trackedEntries;
        {
            std::lock_guard<std::mutex> lock(g_barsMutex);
            for (const auto& entry : g_bars) {
                if (entry.ownerThread == GetCurrentThreadId() &&
                    entry.clickAttached)
                    trackedEntries.push_back(entry);
            }
        }
        for (const auto& entry : trackedEntries) {
            if (!entry.usable && entry.bar.get() == bar && entry.button.get()) {
                Wh_Log(L"Previous insertion has a retained Click callback; waiting for safe cleanup");
                return InsertStatus::RetainedCallback;
            }
        }

        // On a previous unload a button can remain visible after its Click
        // handler was successfully detached but XAML RemoveAt failed.
        // Remove that inert control before adding the new instance.
        for (uint32_t i = commands.Size(); i > 0; --i) {
            auto item = commands.GetAt(i - 1).try_as<muxc::AppBarButton>();
            if (!item || item.Name() != kButtonName) continue;
            for (const auto& entry : trackedEntries) {
                if (entry.button.get() == item)
                    return entry.usable ? InsertStatus::Ready :
                                          InsertStatus::RetainedCallback;
            }
            commands.RemoveAt(i - 1);
            if (i - 1 < place) --place;
            Wh_Log(L"Removed detached button left by an earlier unload");
        }

        button = muxc::AppBarButton();
        button.Name(kButtonName);
        // Keep the default native AppBarButton style. In particular, do not
        // set RequestedTheme, Foreground, Background, or a fixed Style: the
        // XAML tree inherits Task Manager's own Light/Dark/contrast resources.
        // The SymbolIcon inherits its brush from this native button as well.
        UpdateButton(button);
        commands.InsertAt(place, button);
        inserted = true;

        // Allocate bookkeeping BEFORE subscribing to Click. If allocation
        // fails, we can roll back a button that never had a mod callback.
        BarEntry entry;
        entry.bar = winrt::make_weak(bar);
        entry.button = winrt::make_weak(button);
        entry.ownerThread = GetCurrentThreadId();
        entry.entryId = g_nextEntryId.fetch_add(1, std::memory_order_relaxed);
        entryId = entry.entryId;
        {
            std::lock_guard<std::mutex> lock(g_barsMutex);
            g_bars.push_back(std::move(entry));
        }
        tracked = true;

        clickToken = button.Click([](auto const&, auto const&) {
            if (!g_stopping.load(std::memory_order_acquire)) TogglePause();
        });
        clickAttached = true;
        {
            std::lock_guard<std::mutex> lock(g_barsMutex);
            for (auto& saved : g_bars) {
                if (saved.entryId == entryId) {
                    saved.clickToken = clickToken;
                    saved.clickAttached = true;
                    saved.usable = true;
                    break;
                }
            }
        }

        const auto count = g_insertions.fetch_add(1) + 1;
        // Diagnostics must not turn a completed Click subscription into a
        // failed insertion. ActualTheme is optional and may throw.
        if (count <= 8) {
            try {
                const auto theme = button.ActualTheme();
                Wh_Log(L"Native Pause button inserted (%u, theme=%s)", count,
                       theme == mux::ElementTheme::Light ? L"light" :
                       theme == mux::ElementTheme::Dark ? L"dark" : L"default");
            } catch (...) {
                Wh_Log(L"Native Pause button inserted (%u, theme unavailable)", count);
            }
        }
        return InsertStatus::Ready;
    } catch (...) {
        HRESULT error = winrt::to_hresult();
        bool safeToForget = !clickAttached;
        if (button && clickAttached) {
            try {
                button.Click(clickToken);
                safeToForget = true;
            } catch (...) {
                Wh_Log(L"WARNING: event rollback failed; keeping entry for unload retry");
            }
        }
        if (safeToForget) {
            if (tracked) {
                std::lock_guard<std::mutex> lock(g_barsMutex);
                g_bars.erase(std::remove_if(g_bars.begin(), g_bars.end(),
                    [entryId](BarEntry const& e) { return e.entryId == entryId; }),
                    g_bars.end());
            }
            if (inserted) {
                try {
                    auto commands = bar.PrimaryCommands();
                    if (commands) {
                        for (uint32_t i = commands.Size(); i > 0; --i) {
                            if (auto item = commands.GetAt(i - 1).try_as<muxc::AppBarButton>()) {
                                if (item == button) {
                                    commands.RemoveAt(i - 1);
                                    break;
                                }
                            }
                        }
                    }
                } catch (...) {
                    Wh_Log(L"Could not remove detached button during rollback");
                }
            }
        }
        // If Click revocation failed, its callback may remain live. Keep a
        // non-usable entry with its revocation token for safe unload. Never
        // present this exceptional state as a successful button insertion.
        if (!safeToForget && clickAttached && inserted && tracked) {
            try {
                std::lock_guard<std::mutex> lock(g_barsMutex);
                for (auto& entry : g_bars) {
                    if (entry.entryId == entryId) {
                        entry.clickToken = clickToken;
                        entry.clickAttached = true;
                        entry.usable = false;
                        break;
                    }
                }
            } catch (...) {
                Wh_Log(L"WARNING: could not refresh retained callback state");
            }
            Wh_Log(L"Button insertion incomplete: 0x%08X; Click callback retained",
                   error);
            return InsertStatus::RetainedCallback;
        }
        Wh_Log(L"Button insertion failed: 0x%08X", error);
        return InsertStatus::Failed;
    }
}

// Synchronous UI dispatch, following Windhawk's RunFromWindowThread pattern.
// Keep a short-lived request registry to reject unrelated registered messages.
// Never hold the registry mutex while sending a message or invoking a callback.
UINT g_dispatchMsg{};

struct UiRequest {
    HWND hwnd{};
    DWORD threadId{};
    bool (*callback)(DWORD){};
    std::atomic<bool> invoked{false};
    std::atomic<bool> succeeded{false};
    UiRequest* next{};
};

std::mutex g_dispatchMutex;
UiRequest* g_activeRequests{}; // Protected by g_dispatchMutex.

bool UiThreadTerminated(DWORD threadId) {
    HANDLE thread = OpenThread(SYNCHRONIZE, FALSE, threadId);
    if (!thread) return GetLastError() == ERROR_INVALID_PARAMETER;
    const DWORD result = WaitForSingleObject(thread, 0);
    CloseHandle(thread);
    return result == WAIT_OBJECT_0;
}

HWND FindTaskManagerWindow() {
    HWND result = nullptr;
    EnumWindows([](HWND hwnd, LPARAM param) -> BOOL {
        DWORD pid{};
        wchar_t className[64]{};
        if (GetWindowThreadProcessId(hwnd, &pid) &&
            pid == GetCurrentProcessId() &&
            GetClassNameW(hwnd, className, ARRAYSIZE(className)) &&
            wcscmp(className, L"TaskManagerWindow") == 0) {
            *reinterpret_cast<HWND*>(param) = hwnd;
            return FALSE;
        }
        return TRUE;
    }, reinterpret_cast<LPARAM>(&result));
    return result;
}

LRESULT CALLBACK DispatchHook(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && g_dispatchMsg) {
        auto* msg = reinterpret_cast<const CWPSTRUCT*>(lp);
        if (msg && msg->message == g_dispatchMsg) {
            // Do not dereference an arbitrary lParam before verifying it is
            // one of our live requests. Multiple UI threads may dispatch at once.
            auto* candidate = reinterpret_cast<UiRequest*>(msg->lParam);
            bool run = false;
            {
                std::lock_guard<std::mutex> lock(g_dispatchMutex);
                for (auto* request = g_activeRequests; request; request = request->next) {
                    if (request == candidate && request->hwnd == msg->hwnd &&
                        request->threadId == GetCurrentThreadId() &&
                        !request->invoked.exchange(true, std::memory_order_acq_rel)) {
                        run = true;
                        break;
                    }
                }
            }
            if (run) {
                try {
                    candidate->succeeded.store(candidate->callback(candidate->threadId),
                                               std::memory_order_release);
                } catch (...) {
                    Wh_Log(L"UI dispatch callback exception");
                }
            }
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

void UnhookDispatchSafely(HHOOK hook, DWORD threadId) {
    if (!hook) return;
    unsigned attempts = 0;
    while (!UnhookWindowsHookEx(hook)) {
        DWORD error = GetLastError();
        if (error == ERROR_INVALID_HOOK_HANDLE || UiThreadTerminated(threadId))
            return;
        if (++attempts % 50 == 0)
            Wh_Log(L"Waiting to remove UI hook: thread=%lu error=%lu", threadId, error);
        Sleep(100);
    }
}

// Use Task Manager's main window when possible, otherwise one of its XAML
// host descendants belonging to the requested thread. Do not send a hook
// message to an arbitrary IME or unrelated thread window.
HWND FindUiWindowForThread(DWORD threadId) {
    HWND mainWindow = FindTaskManagerWindow();
    if (mainWindow && GetWindowThreadProcessId(mainWindow, nullptr) == threadId)
        return mainWindow;

    struct FindWindowContext {
        DWORD threadId;
        HWND result;
    } context{threadId, nullptr};
    if (mainWindow) {
        EnumChildWindows(mainWindow, [](HWND hwnd, LPARAM param) -> BOOL {
            auto* search = reinterpret_cast<FindWindowContext*>(param);
            DWORD pid{};
            DWORD owner = GetWindowThreadProcessId(hwnd, &pid);
            if (pid == GetCurrentProcessId() && owner == search->threadId) {
                search->result = hwnd;
                return FALSE;
            }
            return TRUE;
        }, reinterpret_cast<LPARAM>(&context));
        if (context.result) return context.result;
    }

    // After a main window closes, an owned top-level XAML host may still
    // exist while its UI thread drains. Prefer it over an infinite wait with
    // no dispatch target. Exclude common IME helper windows.
    EnumThreadWindows(threadId, [](HWND hwnd, LPARAM param) -> BOOL {
        auto* search = reinterpret_cast<FindWindowContext*>(param);
        DWORD pid{};
        if (GetWindowThreadProcessId(hwnd, &pid) != search->threadId ||
            pid != GetCurrentProcessId()) return TRUE;
        wchar_t cls[64]{};
        if (!GetClassNameW(hwnd, cls, ARRAYSIZE(cls))) return TRUE;
        if (wcscmp(cls, L"Default IME") == 0 ||
            wcscmp(cls, L"MSCTFIME UI") == 0 ||
            wcscmp(cls, L"IME") == 0) return TRUE;
        search->result = hwnd;
        return FALSE;
    }, reinterpret_cast<LPARAM>(&context));
    return context.result;
}

bool RunOnUiThread(DWORD threadId, bool (*callback)(DWORD)) {
    if (threadId == GetCurrentThreadId()) {
        try {
            return callback(threadId);
        } catch (...) {
            Wh_Log(L"Same-thread UI callback exception");
            return false;
        }
    }
    HWND hwnd = FindUiWindowForThread(threadId);
    if (!hwnd) return false;

    HHOOK hook = SetWindowsHookExW(WH_CALLWNDPROC, DispatchHook, nullptr, threadId);
    if (!hook) return false;

    UiRequest request;
    request.hwnd = hwnd;
    request.threadId = threadId;
    request.callback = callback;
    {
        std::lock_guard<std::mutex> lock(g_dispatchMutex);
        request.next = g_activeRequests;
        g_activeRequests = &request;
    }
    // SendMessageW waits for the target UI callback and the hook chain.
    // Do not substitute a naive SendMessageTimeoutW here: the stack-backed
    // UiRequest and module callback could remain in flight after timeout,
    // allowing use-after-free or unload-while-running. Safe cancellation needs
    // a separate lifetime protocol. Other dispatches can proceed meanwhile.
    SendMessageW(hwnd, g_dispatchMsg, 0, reinterpret_cast<LPARAM>(&request));
    {
        std::lock_guard<std::mutex> lock(g_dispatchMutex);
        auto** link = &g_activeRequests;
        while (*link && *link != &request) link = &(*link)->next;
        if (*link) *link = request.next;
    }
    UnhookDispatchSafely(hook, threadId);
    return request.invoked.load(std::memory_order_acquire) &&
           request.succeeded.load(std::memory_order_acquire);
}

void PruneExpiredEntriesOnCurrentThread() {
    DWORD threadId = GetCurrentThreadId();
    std::vector<BarEntry> entries;
    {
        std::lock_guard<std::mutex> lock(g_barsMutex);
        for (auto const& entry : g_bars)
            if (entry.ownerThread == threadId) entries.push_back(entry);
    }
    std::vector<uint64_t> expired;
    for (auto const& entry : entries) {
        try {
            if (!entry.button.get()) expired.push_back(entry.entryId);
        } catch (...) {
            // If the reference cannot be resolved, preserve the event record.
        }
    }
    if (expired.empty()) return;
    std::lock_guard<std::mutex> lock(g_barsMutex);
    g_bars.erase(std::remove_if(g_bars.begin(), g_bars.end(),
        [&expired](BarEntry const& entry) {
            return std::find(expired.begin(), expired.end(), entry.entryId) !=
                expired.end();
        }), g_bars.end());
}

std::vector<DWORD> KnownThreads() {
    std::vector<DWORD> result;
    {
        std::lock_guard<std::mutex> lock(g_barsMutex);
        for (const auto& entry : g_bars) {
            if (std::find(result.begin(), result.end(), entry.ownerThread) == result.end())
                result.push_back(entry.ownerThread);
        }
    }
    for (DWORD id : NavigationThreads()) {
        if (std::find(result.begin(), result.end(), id) == result.end())
            result.push_back(id);
    }
    return result;
}

bool SyncThreadButtons(DWORD threadId) {
    std::vector<BarEntry> entries;
    {
        std::lock_guard<std::mutex> lock(g_barsMutex);
        for (auto const& e : g_bars)
            if (e.ownerThread == threadId) entries.push_back(e);
    }
    bool success = true;
    for (auto const& entry : entries) {
        try {
            if (auto button = entry.button.get()) UpdateButton(button);
        } catch (...) {
            success = false;
        }
    }
    return success;
}

void SyncButtons() {
    for (auto threadId : KnownThreads()) {
        if (g_stopping.load(std::memory_order_acquire)) return;
        if (!RunOnUiThread(threadId, SyncThreadButtons))
            Wh_Log(L"Could not sync thread %lu", threadId);
    }
}

std::atomic<unsigned> g_cleanupFailures{0};

// Called only on the owner XAML thread. A detached Click handler is sufficient
// for safe unload. Visual removal is best-effort and never keeps code alive.
bool RemoveThreadButtonsAndEvents(DWORD threadId) {
    std::vector<BarEntry> entries;
    {
        std::lock_guard<std::mutex> lock(g_barsMutex);
        for (auto const& entry : g_bars)
            if (entry.ownerThread == threadId) entries.push_back(entry);
    }

    bool allDetached = true;
    for (auto const& entry : entries) {
        bool detached = false;
        muxc::AppBarButton button{nullptr};
        try {
            button = entry.button.get();
            if (!button) {
                detached = true; // A destroyed event source cannot invoke us.
            } else if (!entry.clickAttached) {
                detached = true;
            } else {
                button.Click(entry.clickToken);
                detached = true;
            }
        } catch (...) {
            ++g_cleanupFailures;
            Wh_Log(L"Click handler detach failed: 0x%08X", winrt::to_hresult());
        }
        if (!detached) {
            allDetached = false;
            continue; // Never unload while a live handler remains.
        }

        if (button) {
            try {
                if (auto bar = entry.bar.get()) {
                    if (auto commands = bar.PrimaryCommands()) {
                        for (uint32_t i = commands.Size(); i > 0; --i) {
                            auto item = commands.GetAt(i - 1).try_as<muxc::AppBarButton>();
                            if (item && item == button) {
                                commands.RemoveAt(i - 1);
                                break;
                            }
                        }
                    }
                }
            } catch (...) {
                ++g_cleanupFailures;
                Wh_Log(L"Button removal failed (event already detached): 0x%08X",
                       winrt::to_hresult());
            }
        }
        std::lock_guard<std::mutex> lock(g_barsMutex);
        auto it = std::find_if(g_bars.begin(), g_bars.end(),
            [&entry](BarEntry const& value) { return value.entryId == entry.entryId; });
        if (it != g_bars.end()) g_bars.erase(it);
    }
    // The navigation listener is also a callback into this mod. Detach it
    // on its owning XAML thread before the DLL is unloaded.
    const bool navigationDetached = RemoveThreadNavigationHooks(threadId);
    if (navigationDetached && allDetached) ForgetHookScanThread(threadId);
    return navigationDetached && allDetached;
}

void ForgetTerminatedThread(DWORD threadId) {
    {
        std::lock_guard<std::mutex> lock(g_barsMutex);
        g_bars.erase(std::remove_if(g_bars.begin(), g_bars.end(),
            [threadId](BarEntry const& entry) { return entry.ownerThread == threadId; }),
            g_bars.end());
    }
    ForgetNavigationThread(threadId);
    ForgetHookScanThread(threadId);
}

bool FindTaskManagerRange() {
    auto* start = reinterpret_cast<BYTE*>(GetModuleHandleW(nullptr));
    if (!start) return false;
    auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(start);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return false;
    auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(start + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) return false;
    g_taskBegin = reinterpret_cast<uintptr_t>(start);
    g_taskEnd = g_taskBegin + nt->OptionalHeader.SizeOfImage;
    return g_taskBegin < g_taskEnd;
}


// Called on the XAML thread during Processes/Details page navigation.
// Returns true only after all matched bars have usable Pause buttons.
// Frame.Navigated may retry when the entry hook ran before the toolbar was
// created, or when the first insertion attempt failed.
bool FindCommandBars(mux::FrameworkElement const& page) {
    if (g_stopping.load(std::memory_order_acquire) || !page) return false;
    try {
        // Public XAML event, subscribed only on a page/navigation frame
        // obtained through the normal Task Manager symbol hook.
        TryAttachFrameNavigation(page);
        mux::DependencyObject root = page;
        std::vector<mux::DependencyObject> pagePath{root};
        for (unsigned i = 0; i < 48; ++i) {
            auto parent = muxm::VisualTreeHelper::GetParent(root);
            if (!parent) break;
            root = parent;
            pagePath.push_back(root);
        }
        std::vector<mux::DependencyObject> stack{root};
        unsigned scanned = 0;
        unsigned barsFound = 0;
        unsigned matchingBars = 0;
        unsigned buttonsReady = 0;
        unsigned retainedCallbacks = 0;
        unsigned skippedOtherPages = 0;
        std::vector<muxc::CommandBar> pageBars;
        while (!stack.empty() && scanned < 5000 &&
               !g_stopping.load(std::memory_order_acquire)) {
            auto element = stack.back();
            stack.pop_back();
            ++scanned;
            // A shell-level command bar can be a sibling of the active page,
            // so we must search the common root. Exclude *other* Page subtrees
            // (including cached/navigated-away pages) to avoid matching their
            // command bars. Preserve all ancestors of the active page.
            if (element.try_as<muxc::Page>() &&
                std::find(pagePath.begin(), pagePath.end(), element) == pagePath.end()) {
                ++skippedOtherPages;
                continue;
            }
            if (auto bar = element.try_as<muxc::CommandBar>()) {
                ++barsFound;
                pageBars.push_back(bar);
            }
            int children = muxm::VisualTreeHelper::GetChildrenCount(element);
            for (int i = children - 1; i >= 0; --i)
                stack.push_back(muxm::VisualTreeHelper::GetChild(element, i));
        }

        // A complete scan is essential for the structural fallback. If the
        // traversal was cut short, only the semantic matcher may be trusted.
        const bool uniquePageBar = stack.empty() && pageBars.size() == 1;
        for (auto const& bar : pageBars) {
            if (g_stopping.load(std::memory_order_acquire)) break;
            try {
                TryAttachFrameNavigation(bar);
                BarCandidate candidate;
                if (InspectProductionBar(bar, uniquePageBar, candidate)) {
                    ++matchingBars;
                    const auto result = TryInsertButton(candidate.bar,
                                                        candidate.place);
                    if (result == InsertStatus::Ready)
                        ++buttonsReady;
                    else if (result == InsertStatus::RetainedCallback)
                        ++retainedCallbacks;
                }
            } catch (...) {
                Wh_Log(L"Could not inspect command bar: 0x%08X",
                       winrt::to_hresult());
            }
        }
        // Bounded diagnostics for distinguishing missing hooks, missing
        // toolbar anchors, and insertion errors without spamming the log.
        static std::atomic<unsigned> searchesLogged{0};
        if (searchesLogged.fetch_add(1, std::memory_order_relaxed) < 6) {
            Wh_Log(L"Command bar scan: elements=%u bars=%u matches=%u ready=%u retained=%u otherPages=%u",
                   scanned, barsFound, matchingBars, buttonsReady,
                   retainedCallbacks, skippedOtherPages);
        }
        return matchingBars != 0 && buttonsReady == matchingBars;
    } catch (...) {
        Wh_Log(L"Visual tree search failed: 0x%08X", winrt::to_hresult());
        return false;
    }
}

// Frame.Navigated is a public XAML event. We acquire the Frame through the
// Processes navigation hook, not through XAML Diagnostics.
// Unknown page types do not cause an automatic Resume.
enum class ActivePage { Unknown, Supported, Other };

bool EndsWith(std::wstring_view value, std::wstring_view suffix) {
    return value.size() >= suffix.size() &&
           value.substr(value.size() - suffix.size()) == suffix;
}

ActivePage ClassifyPageType(winrt::hstring const& fullName) {
    const std::wstring_view name{fullName.c_str(), fullName.size()};
    if (EndsWith(name, L"ProcessesPage") || EndsWith(name, L"DetailsPage"))
        return ActivePage::Supported;

    // Limit automatic Resume to positively identified Task Manager pages.
    // Avoid treating arbitrary XAML container navigation as leaving Task Manager.
    if (name.find(L"TaskManagerApp.") != std::wstring_view::npos &&
        EndsWith(name, L"Page"))
        return ActivePage::Other;
    return ActivePage::Unknown;
}

struct NavigationEntry {
    winrt::weak_ref<muxc::Frame> frame;
    DWORD ownerThread{};
    winrt::event_token token{};
    uint64_t id{};
    bool attached{};
};

std::mutex g_navigationMutex;
std::vector<NavigationEntry> g_navigationEntries; // Weak references only.
std::atomic<uint64_t> g_nextNavigationId{1};
std::atomic<unsigned> g_navigationEvents{0};

void ResumeOnUnsupportedPage() {
    if (g_stopping.load(std::memory_order_acquire)) return;
    if (g_paused.exchange(false, std::memory_order_acq_rel)) {
        Wh_Log(L"Pause cleared after navigating to another Task Manager page");
        SyncButtons();
    }
}

std::vector<DWORD> NavigationThreads() {
    std::vector<DWORD> result;
    std::lock_guard<std::mutex> lock(g_navigationMutex);
    for (const auto& entry : g_navigationEntries)
        if (std::find(result.begin(), result.end(), entry.ownerThread) == result.end())
            result.push_back(entry.ownerThread);
    return result;
}

void ForgetNavigationThread(DWORD threadId) {
    std::lock_guard<std::mutex> lock(g_navigationMutex);
    g_navigationEntries.erase(std::remove_if(g_navigationEntries.begin(),
        g_navigationEntries.end(), [threadId](const NavigationEntry& entry) {
            return entry.ownerThread == threadId;
        }), g_navigationEntries.end());
}

bool RemoveThreadNavigationHooks(DWORD threadId) {
    std::vector<NavigationEntry> entries;
    {
        std::lock_guard<std::mutex> lock(g_navigationMutex);
        for (const auto& entry : g_navigationEntries)
            if (entry.ownerThread == threadId) entries.push_back(entry);
    }
    bool allDetached = true;
    for (const auto& entry : entries) {
        bool detached = false;
        try {
            auto frame = entry.frame.get();
            if (!frame || !entry.attached) {
                detached = true;
            } else {
                frame.Navigated(entry.token);
                detached = true;
            }
        } catch (...) {
            ++g_cleanupFailures;
            Wh_Log(L"Frame.Navigated detach failed: 0x%08X", winrt::to_hresult());
        }
        if (!detached) {
            allDetached = false;
            continue; // Never unload with a live callback still attached.
        }
        std::lock_guard<std::mutex> lock(g_navigationMutex);
        g_navigationEntries.erase(std::remove_if(g_navigationEntries.begin(),
            g_navigationEntries.end(), [&entry](const NavigationEntry& value) {
                return value.id == entry.id;
            }), g_navigationEntries.end());
    }
    return allDetached;
}

void TryAttachFrameNavigation(mux::DependencyObject object) {
    if (!object || g_stopping.load(std::memory_order_acquire)) return;
    InsertionGuard guard; // Wait for event subscriptions during unload.
    if (!guard.active) return;
    try {
        for (unsigned depth = 0; object && depth < 64; ++depth) {
            if (auto frame = object.try_as<muxc::Frame>()) {
                const DWORD owner = GetCurrentThreadId();
                {
                    std::lock_guard<std::mutex> lock(g_navigationMutex);
                    for (const auto& entry : g_navigationEntries)
                        if (entry.ownerThread == owner && entry.frame.get() == frame)
                            return;
                }

                NavigationEntry entry;
                entry.frame = winrt::make_weak(frame);
                entry.ownerThread = owner;
                entry.id = g_nextNavigationId.fetch_add(1);
                const uint64_t id = entry.id;
                winrt::event_token token{};
                bool attached = false;
                bool tracked = false;
                try {
                    {
                        std::lock_guard<std::mutex> lock(g_navigationMutex);
                        g_navigationEntries.push_back(entry);
                    }
                    tracked = true;
                    token = frame.Navigated([](auto const&,
                        mux::Navigation::NavigationEventArgs const& args) {
                        if (g_stopping.load(std::memory_order_acquire)) return;
                        try {
                            const auto pageType = args.SourcePageType().Name;
                            const ActivePage active = ClassifyPageType(pageType);
                            if (g_navigationEvents.fetch_add(1) < 12)
                                Wh_Log(L"Frame.Navigated: page=%d",
                                       static_cast<int>(active));
                            if (active == ActivePage::Other) {
                                ResumeOnUnsupportedPage();
                            } else if (active == ActivePage::Supported) {
                                auto page = args.Content().try_as<mux::FrameworkElement>();
                                if (page && NeedsFrameNavigationScan(pageType, page)) {
                                    // If there is no entry hook, the toolbar
                                    // was not ready, or insertion failed,
                                    // retry after navigation completes.
                                    PruneExpiredEntriesOnCurrentThread();
                                    FindCommandBars(page);
                                }
                            }
                        } catch (...) {
                            Wh_Log(L"Frame navigation callback failed: 0x%08X",
                                   winrt::to_hresult());
                        }
                    });
                    attached = true;
                    {
                        std::lock_guard<std::mutex> lock(g_navigationMutex);
                        for (auto& saved : g_navigationEntries)
                            if (saved.id == id) {
                                saved.token = token;
                                saved.attached = true;
                                break;
                            }
                    }
                    Wh_Log(L"Frame.Navigated attached on thread %lu", owner);
                } catch (...) {
                    const HRESULT error = winrt::to_hresult();
                    bool safe = !attached;
                    if (attached) {
                        try { frame.Navigated(token); safe = true; } catch (...) {}
                    }
                    if (tracked && safe) {
                        std::lock_guard<std::mutex> lock(g_navigationMutex);
                        g_navigationEntries.erase(std::remove_if(
                            g_navigationEntries.begin(), g_navigationEntries.end(),
                            [id](const NavigationEntry& e) { return e.id == id; }),
                            g_navigationEntries.end());
                    }
                    Wh_Log(L"Frame.Navigated attachment failed: 0x%08X", error);
                }
                return;
            }
            object = muxm::VisualTreeHelper::GetParent(object);
        }
    } catch (...) {
        static std::atomic<unsigned> logged{0};
        if (logged.fetch_add(1) < 4)
            Wh_Log(L"Frame navigation discovery unavailable: 0x%08X",
                   winrt::to_hresult());
    }
}

// IPageOverrides::OnNavigatedTo belongs to a C++/WinRT produce interface.
// The supplied self pointer is an inspectable ABI interface pointer.
using PageNavigation_t = HRESULT(__cdecl*)(void*, void*);
PageNavigation_t g_processesToOriginal{};
PageNavigation_t g_detailsToOriginal{};
PageNavigation_t g_processesFromOriginal{};
PageNavigation_t g_detailsFromOriginal{};
// The compiler can fold identical Processes/Details navigation functions.
// In that case the Processes hook covers both page types.
bool g_detailsToUsesProcessesHook = false;

// Track whether the entry hook inserted or found a usable button on the
// specific page instance. The frame event retries failed/missing insertions,
// but avoids a duplicate scan if the button is already usable.
struct HookScanRecord {
    winrt::weak_ref<mux::FrameworkElement> page;
    DWORD ownerThread{};
    bool buttonReady{};
};
std::mutex g_hookScansMutex;
std::vector<HookScanRecord> g_hookScans;

void RememberHookScan(mux::FrameworkElement const& page, bool buttonReady) {
    const DWORD owner = GetCurrentThreadId();
    std::lock_guard<std::mutex> lock(g_hookScansMutex);
    auto it = std::find_if(g_hookScans.begin(), g_hookScans.end(),
        [owner](HookScanRecord const& item) { return item.ownerThread == owner; });
    HookScanRecord record{winrt::make_weak(page), owner, buttonReady};
    if (it != g_hookScans.end()) *it = std::move(record);
    else g_hookScans.push_back(std::move(record));
}

void ForgetHookScanThread(DWORD threadId) {
    std::lock_guard<std::mutex> lock(g_hookScansMutex);
    g_hookScans.erase(std::remove_if(g_hookScans.begin(), g_hookScans.end(),
        [threadId](HookScanRecord const& record) {
            return record.ownerThread == threadId;
        }), g_hookScans.end());
}

bool NeedsFrameNavigationScan(winrt::hstring const& pageType,
                              mux::FrameworkElement const& page) {
    const std::wstring_view name{pageType.c_str(), pageType.size()};
    bool hasEntryHook = false;
    if (EndsWith(name, L"ProcessesPage"))
        hasEntryHook = g_processesToOriginal != nullptr;
    else if (EndsWith(name, L"DetailsPage"))
        hasEntryHook = g_detailsToOriginal != nullptr ||
                       g_detailsToUsesProcessesHook;
    else
        return false;
    if (!hasEntryHook) return true;
    const DWORD owner = GetCurrentThreadId();
    std::lock_guard<std::mutex> lock(g_hookScansMutex);
    for (const auto& record : g_hookScans) {
        if (record.ownerThread == owner && record.page.get() == page)
            return !record.buttonReady;
    }
    return true; // A hook exists, but has not yet captured this page instance.
}

void CapturePageFromInterface(void* self) {
    if (!self || g_stopping.load(std::memory_order_acquire)) return;
    try {
        winrt::com_ptr<::IInspectable> object;
        HRESULT hr = reinterpret_cast<::IUnknown*>(self)->QueryInterface(
            __uuidof(::IInspectable), object.put_void());
        if (FAILED(hr) || !object) {
            Wh_Log(L"Page capture: IInspectable unavailable, hr=0x%08X", hr);
            return;
        }
        wf::IInspectable inspectable{nullptr};
        winrt::copy_from_abi(inspectable, object.get());
        auto page = inspectable.try_as<mux::FrameworkElement>();
        if (!page) {
            Wh_Log(L"Page capture: FrameworkElement unavailable");
            return;
        }
        // A shared navigation function can also be used by unrelated pages.
        // Never apply the structural command-bar fallback outside these two.
        if (ClassifyPageType(winrt::get_class_name(page)) !=
            ActivePage::Supported) return;
        PruneExpiredEntriesOnCurrentThread();
        const bool buttonReady = FindCommandBars(page);
        RememberHookScan(page, buttonReady);
    } catch (...) {
        Wh_Log(L"Page capture failed: 0x%08X", winrt::to_hresult());
    }
}

HRESULT __cdecl ProcessesNavigatedTo_Hook(void* self, void* args) {
    HRESULT result = g_processesToOriginal(self, args);
    if (SUCCEEDED(result) && !g_stopping.load(std::memory_order_acquire))
        CapturePageFromInterface(self);
    return result;
}

HRESULT __cdecl DetailsNavigatedTo_Hook(void* self, void* args) {
    HRESULT result = g_detailsToOriginal(self, args);
    if (SUCCEEDED(result) && !g_stopping.load(std::memory_order_acquire))
        CapturePageFromInterface(self);
    return result;
}

// SourcePageType identifies the navigation destination. Preserve Pause when
// switching Processes <-> Details. An unknown event/argument is not evidence
// of a real departure (OnNavigatedFrom can also run for GetNavigationState).
bool IsSupportedDestination(void* args, bool& known) {
    known = false;
    if (!args) return false;
    try {
        mux::Navigation::NavigationEventArgs navigation{nullptr};
        winrt::copy_from_abi(navigation, args);
        const auto name = navigation.SourcePageType().Name;
        if (name.empty()) return false;
        known = true;
        const std::wstring_view value{name.c_str(), name.size()};
        const auto endsWith = [value](std::wstring_view suffix) {
            return value.size() >= suffix.size() &&
                value.substr(value.size() - suffix.size()) == suffix;
        };
        return value == L"ProcessesPage" || value == L"DetailsPage" ||
               endsWith(L".ProcessesPage") || endsWith(L".DetailsPage");
    } catch (...) {
        Wh_Log(L"Could not inspect navigation destination; preserving pause state");
        return false;
    }
}

void OnLeavingSupportedPage(void* args) {
    if (g_stopping.load(std::memory_order_acquire)) return;
    bool known = false;
    const bool supported = IsSupportedDestination(args, known);
    if (!known || supported) return;
    if (g_paused.exchange(false, std::memory_order_acq_rel))
        SyncButtons();
}

HRESULT __cdecl ProcessesNavigatedFrom_Hook(void* self, void* args) {
    HRESULT result = g_processesFromOriginal(self, args);
    if (SUCCEEDED(result)) OnLeavingSupportedPage(args);
    return result;
}

HRESULT __cdecl DetailsNavigatedFrom_Hook(void* self, void* args) {
    HRESULT result = g_detailsFromOriginal(self, args);
    if (SUCCEEDED(result)) OnLeavingSupportedPage(args);
    return result;
}


} // namespace

BOOL ModInit() {
    {
        std::lock_guard<std::mutex> lock(g_insertionMutex);
        g_acceptingInsertions = true;
        g_insertionCount = 0;
    }
    g_stopping = false;
    g_paused = false;
    g_insertions = 0;
    g_cleanupFailures = 0;
    g_navigationEvents = 0;
    g_dispatchMsg = RegisterWindowMessageW(
        L"Windhawk.TaskManagerPauseButton.SynchronousUI");
    if (!g_dispatchMsg || !FindTaskManagerRange()) return FALSE;

    HMODULE host = GetModuleHandleW(nullptr);
    if (!host) return FALSE;

    // Resolve all four navigation symbols, but do not hook until we can
    // compare addresses. Identical C++/WinRT produce<> bodies may be folded
    // into one function by the linker; hook that function only once.
    PageNavigation_t processesTo{};
    PageNavigation_t detailsTo{};
    PageNavigation_t processesFrom{};
    PageNavigation_t detailsFrom{};
    WindhawkUtils::SYMBOL_HOOK taskmgrExeHooks[] = {
        {{L"public: virtual int __cdecl winrt::impl::produce<struct winrt::TaskManagerApp::implementation::ProcessesPage,struct winrt::Windows::UI::Xaml::Controls::IPageOverrides>::OnNavigatedTo(void *)"},
         &processesTo},
        {{L"public: virtual int __cdecl winrt::impl::produce<struct winrt::TaskManagerApp::implementation::DetailsPage,struct winrt::Windows::UI::Xaml::Controls::IPageOverrides>::OnNavigatedTo(void *)"},
         &detailsTo, nullptr, true},
        {{L"public: virtual int __cdecl winrt::impl::produce<struct winrt::TaskManagerApp::implementation::ProcessesPage,struct winrt::Windows::UI::Xaml::Controls::IPageOverrides>::OnNavigatedFrom(void *)"},
         &processesFrom, nullptr, true},
        {{L"public: virtual int __cdecl winrt::impl::produce<struct winrt::TaskManagerApp::implementation::DetailsPage,struct winrt::Windows::UI::Xaml::Controls::IPageOverrides>::OnNavigatedFrom(void *)"},
         &detailsFrom, nullptr, true},
    };
    if (!WindhawkUtils::HookSymbols(host, taskmgrExeHooks,
                                    ARRAYSIZE(taskmgrExeHooks))) {
        Wh_Log(L"Navigation symbol resolution failed (cache or PDB unavailable)");
        return FALSE;
    }
    if (!processesTo ||
        !WindhawkUtils::SetFunctionHook(processesTo, ProcessesNavigatedTo_Hook,
                                       &g_processesToOriginal)) {
        Wh_Log(L"Required ProcessesPage::OnNavigatedTo hook unavailable");
        return FALSE;
    }
    Wh_Log(L"Required ProcessesPage::OnNavigatedTo hook installed via Windhawk symbols");

    g_detailsToUsesProcessesHook = detailsTo && detailsTo == processesTo;
    const bool detailsToFound = detailsTo != nullptr;
    const bool detailsToHooked = g_detailsToUsesProcessesHook ||
        (detailsToFound && WindhawkUtils::SetFunctionHook(
            detailsTo, DetailsNavigatedTo_Hook, &g_detailsToOriginal));
    if (!detailsToHooked) g_detailsToOriginal = nullptr;
    Wh_Log(L"Optional DetailsPage::OnNavigatedTo: symbol=%s hook=%s",
           detailsToFound ? L"found" : L"missing",
           g_detailsToUsesProcessesHook ? L"shared" :
           detailsToHooked ? L"ok" : L"unavailable");

    // Optional exit hooks. One hook handles both page types when the linker
    // gave Processes and Details the same OnNavigatedFrom address.
    const bool processesExitFound = processesFrom != nullptr;
    const bool processesExitHooked = processesExitFound &&
        WindhawkUtils::SetFunctionHook(processesFrom,
                                      ProcessesNavigatedFrom_Hook,
                                      &g_processesFromOriginal);
    if (!processesExitHooked) g_processesFromOriginal = nullptr;
    Wh_Log(L"Optional ProcessesPage::OnNavigatedFrom: symbol=%s hook=%s",
           processesExitFound ? L"found" : L"missing",
           processesExitHooked ? L"ok" : L"unavailable");

    const bool detailsExitFound = detailsFrom != nullptr;
    const bool sharedExit = processesExitHooked &&
                            detailsFrom && detailsFrom == processesFrom;
    const bool detailsExitHooked = sharedExit ||
        (detailsExitFound && detailsFrom != processesFrom &&
         WindhawkUtils::SetFunctionHook(detailsFrom,
                                       DetailsNavigatedFrom_Hook,
                                       &g_detailsFromOriginal));
    if (!detailsExitHooked) g_detailsFromOriginal = nullptr;
    Wh_Log(L"Optional DetailsPage::OnNavigatedFrom: symbol=%s hook=%s",
           detailsExitFound ? L"found" : L"missing",
           sharedExit ? L"shared" :
           detailsExitHooked ? L"ok" : L"unavailable");

    // Intentionally unchanged: preserve the tested GetKeyState-based refresh
    // hold, including its Taskmgr.exe return-address restriction.
    if (!WindhawkUtils::SetFunctionHook(
            GetKeyState, GetKeyState_Hook, &g_getKeyOriginal)) return FALSE;

    Wh_Log(L"Ready: Processes hook, Details hook=%s, Frame.Navigated fallback",
           g_detailsToUsesProcessesHook ? L"shared" :
           g_detailsToOriginal ? L"separate" : L"unavailable");
    return TRUE;
}

void ModBeforeUninit() {
    StopNewInsertions();
}


void ModUninit() {
    StopNewInsertions();
    {
        std::unique_lock<std::mutex> lock(g_insertionMutex);
        g_insertionDone.wait(lock, [] { return g_insertionCount == 0; });
    }

    // Admission is closed and every started insertion has finished, so
    // KnownThreads can no longer miss a late first Click subscription.
    unsigned terminatedThreads = 0;
    unsigned attempts = 0;
    for (;;) {
        const auto threads = KnownThreads();
        if (threads.empty()) break;
        for (DWORD threadId : threads) {
            if (UiThreadTerminated(threadId)) {
                ForgetTerminatedThread(threadId);
                ++terminatedThreads;
                continue;
            }
            if (!RunOnUiThread(threadId, RemoveThreadButtonsAndEvents)) {
                if (++attempts % 4 == 0) {
                    Wh_Log(L"Awaiting safe UI cleanup: thread=%lu attempts=%u; close a hung Task Manager",
                           threadId, attempts);
                }
            }
        }
        if (KnownThreads().empty()) break;
        // Never unload a module while a live XAML button still has a Click
        // handler pointing into it. A dead or inaccessible UI thread may
        // require the user to close Task Manager; a simple timeout would be
        // unsafe without first revoking all callbacks.
        Sleep(250);
    }
    Wh_Log(L"Uninit finished: inserted=%u terminatedThreads=%u cleanupErrors=%u",
           g_insertions.load(), terminatedThreads, g_cleanupFailures.load());
}
}  // namespace f_pause


// ===========================================================================
// taskmgr-esc
// ===========================================================================
namespace f_esc {
static HHOOK g_keyboardHook = nullptr;
static HANDLE g_thread = nullptr;
static DWORD g_threadId = 0;

HWND GetTaskManagerForegroundWindow() {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd)
        return nullptr;

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);

    if (pid != GetCurrentProcessId())
        return nullptr;

    return hwnd;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        auto* kb = (KBDLLHOOKSTRUCT*)lParam;

        if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) &&
            kb->vkCode == VK_ESCAPE) {
            Wh_Log(L"[ESC] pressed");

            HWND hwnd = GetTaskManagerForegroundWindow();
            if (hwnd) {
                Wh_Log(L"[ESC] closing task manager");
                PostMessageW(hwnd, WM_CLOSE, 0, 0);
                return 1;
            }
        }
    }

    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

DWORD WINAPI KeyboardThread(LPVOID) {
    Wh_Log(L"Keyboard hook thread started");

    g_keyboardHook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc,
                                       GetModuleHandleW(nullptr), 0);

    if (!g_keyboardHook) {
        Wh_Log(L"Failed to install keyboard hook");
        return 0;
    }

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}

BOOL ModInit() {
    Wh_Log(L"Mod init");

    g_thread =
        CreateThread(nullptr, 0, KeyboardThread, nullptr, 0, &g_threadId);

    return g_thread != nullptr;
}

void ModUninit() {
    Wh_Log(L"Mod uninit");

    if (g_threadId) {
        PostThreadMessageW(g_threadId, WM_QUIT, 0, 0);
    }

    if (g_keyboardHook) {
        UnhookWindowsHookEx(g_keyboardHook);
        g_keyboardHook = nullptr;
    }

    if (g_thread) {
        CloseHandle(g_thread);
        g_thread = nullptr;
    }
}
}  // namespace f_esc


// ===========================================================================
// taskmgr-link-speed
// ===========================================================================
namespace f_linkspeed {
// Following the exact order of includes is crucial to prevent conflicts with network data types

// ------------------------------------------------
// Global variables and function pointers
// ------------------------------------------------
typedef __int64 (__fastcall *CAdapter_Update_t)(void* pThis, bool* pbRefresh, unsigned long historyIndex);
CAdapter_Update_t Original_CAdapter_Update = nullptr;

// Official GetAdapterStat function
typedef unsigned __int64 (__fastcall *GetAdapterStat_t)(void* pThis, unsigned long arg1, int arg2, int arg3);
GetAdapterStat_t pGetAdapterStat = nullptr;

// UpdateDNSName (used to obtain address for assembly analysis)
typedef void (__fastcall *UpdateDNSName_t)(void* pThis, const unsigned __int16* a2, void* a3);
UpdateDNSName_t Original_CAdapter_UpdateDNSName = nullptr;

// UIProps offset (default 0x1F90)
size_t g_UIPropsOffset = 0x1F90; 

// ------------------------------------------------
// Utility function: use Windhawk Wh_Disasm regex to extract offset
// ------------------------------------------------
size_t OffsetFromAssemblyRegex(void* func, size_t defValue, std::regex regex, int limit = 100) {
    if (!func) return defValue;
    
    BYTE* p = (BYTE*)func;
    for (int i = 0; i < limit; i++) {
        WH_DISASM_RESULT result;
        if (!Wh_Disasm(p, &result)) {
            break;
        }

        p += result.length;

        std::string_view s = result.text;
        if (s == "ret" || s == "retn") {
            break; // Function ends, exit early
        }

        std::match_results<std::string_view::const_iterator> match;
        if (std::regex_search(s.begin(), s.end(), match, regex)) {
            // Parse the first captured group (hex string)
            return std::stoull(match[1], nullptr, 16);
        }
    }

    Wh_Log(L"Regex offset extraction failed for %p. Using default.", func);
    return defValue;
}

// ------------------------------------------------
// Memory safety check helper functions
// ------------------------------------------------
bool IsMemoryAccessible(const void* ptr, size_t size, bool requireWritable) {
    if (!ptr || size == 0) return false;

    static thread_local const void* g_lastCheckedPtr = nullptr;
    static thread_local size_t g_lastCheckedSize = 0;
    static thread_local bool g_lastRequireWritable = false;
    static thread_local bool g_lastCheckResult = false;

    if (ptr == g_lastCheckedPtr &&
        size == g_lastCheckedSize &&
        requireWritable == g_lastRequireWritable) {
        return g_lastCheckResult;
    }

    bool isAccessible = true;

    uintptr_t start = (uintptr_t)ptr;
    uintptr_t end = start + size;
    uintptr_t current = start;
    if (end < start) {
        isAccessible = false;
        goto CACHE_AND_RETURN;
    }

    while (current < end) {
        MEMORY_BASIC_INFORMATION mbi;
        if (!VirtualQuery((LPCVOID)current, &mbi, sizeof(mbi))) {
            isAccessible = false;
            break;
        }

        if (mbi.State != MEM_COMMIT) {
            isAccessible = false;
            break;
        }

        DWORD protect = mbi.Protect;
        if (protect & (PAGE_GUARD | PAGE_NOACCESS)) {
            isAccessible = false;
            break;
        }

        bool hasAccess = false;
        if (requireWritable) {
            hasAccess = (protect & (PAGE_READWRITE | PAGE_WRITECOPY |
                                    PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
        } else {
            hasAccess = (protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY |
                                    PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE |
                                    PAGE_EXECUTE_WRITECOPY)) != 0;
        }

        if (!hasAccess) {
            isAccessible = false;
            break;
        }

        uintptr_t regionEnd = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
        if (regionEnd <= current) {
            isAccessible = false;
            break;
        }

        current = (regionEnd < end) ? regionEnd : end;
    }

CACHE_AND_RETURN:
    g_lastCheckedPtr = ptr;
    g_lastCheckedSize = size;
    g_lastRequireWritable = requireWritable;
    g_lastCheckResult = isAccessible;
    return isAccessible;
}

bool IsMemoryReadable(const void* ptr, size_t size) {
    return IsMemoryAccessible(ptr, size, false);
}

bool IsMemoryWritable(void* ptr, size_t size) {
    return IsMemoryAccessible(ptr, size, true);
}

// ==========================================
// Additional module: Intercept LoadStringW at the lowest level (perfect internationalization solution)
// ==========================================

typedef int (WINAPI *LoadStringW_t)(HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax);
LoadStringW_t Original_LoadStringW_User32 = nullptr;
LoadStringW_t Original_LoadStringW_KernelBase = nullptr;

bool g_CustomLabelEnabled = false;
wchar_t g_CustomLabelText[128] = {0};

void LoadUserSettings() {
    g_CustomLabelEnabled = (Wh_GetIntSetting(L"CustomLabelOverrideEnabled") != 0);
    g_CustomLabelText[0] = L'\0';

    PCWSTR customText = Wh_GetStringSetting(L"CustomLabelOverrideText");
    if (customText) {
        wcsncpy_s(g_CustomLabelText, _countof(g_CustomLabelText), customText, _TRUNCATE);
        Wh_FreeStringSetting(customText);
    }
}

int BuildLabelText(HINSTANCE hInstance, wchar_t* outBuf, size_t outBufCount, LoadStringW_t OriginalFunc) {
    if (g_CustomLabelEnabled && g_CustomLabelText[0] != L'\0') {
        wcsncpy_s(outBuf, outBufCount, g_CustomLabelText, _TRUNCATE);
        return (int)wcslen(outBuf);
    }

    return OriginalFunc(hInstance, 34669, outBuf, (int)outBufCount);
}

// Core replacement logic: extracted into a shared function for both hooks
int ProcessLoadStringHook(HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax, LoadStringW_t OriginalFunc) {
    // Target resource ID: 34554 (DNS name)
    if (uID == 34554) {
        wchar_t labelText[128] = {0};
        int labelLen = BuildLabelText(hInstance, labelText, _countof(labelText), OriginalFunc);
        if (labelLen <= 0) {
            return OriginalFunc(hInstance, uID, lpBuffer, cchBufferMax);
        }

        if (cchBufferMax == 0) {
            // [DirectUI zero-copy mode]
            // When cchBufferMax is 0, the API expects a read-only string pointer,
            // and the preceding 16-bit value must store the string length.
            static wchar_t fakeRes[256] = {0};

            size_t maxCopy = _countof(fakeRes) - 3; // Prefix + colon + terminator
            size_t copyLen = (size_t)labelLen;
            if (copyLen > maxCopy) {
                copyLen = maxCopy;
            }

            fakeRes[0] = (wchar_t)(copyLen + 1); // Length prefix: text length + colon
            wcsncpy_s(&fakeRes[1], _countof(fakeRes) - 1, labelText, copyLen);
            fakeRes[copyLen + 1] = L':';
            fakeRes[copyLen + 2] = L'\0';

            // Per API contract, cast and write the pointer into lpBuffer
            *(PWSTR*)lpBuffer = &fakeRes[1];
            return (int)fakeRes[0];
        } else {
            // [Standard copy mode]
            wcsncpy_s(lpBuffer, cchBufferMax, labelText, _TRUNCATE);
            int len = (int)wcslen(lpBuffer);
            if (len > 0 && len + 1 < cchBufferMax) {
                lpBuffer[len] = L':';
                lpBuffer[len + 1] = L'\0';
                return len + 1;
            }
            return len;
        }
    }
    // Pass through all other string resources
    return OriginalFunc(hInstance, uID, lpBuffer, cchBufferMax);
}

// User32 hook
int WINAPI Hooked_LoadStringW_User32(HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax) {
    return ProcessLoadStringHook(hInstance, uID, lpBuffer, cchBufferMax, Original_LoadStringW_User32);
}

// KernelBase hook (many Win10/11 internal calls are forwarded here)
int WINAPI Hooked_LoadStringW_KernelBase(HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax) {
    return ProcessLoadStringHook(hInstance, uID, lpBuffer, cchBufferMax, Original_LoadStringW_KernelBase);
}

// ------------------------------------------------
// Core logic: Update hook and speed retrieval
// ------------------------------------------------
__int64 __fastcall Hooked_CAdapter_Update(void* pThis, bool* pbRefresh, unsigned long historyIndex) {
    __int64 result = Original_CAdapter_Update(pThis, pbRefresh, historyIndex);
    if (!pThis) return result;

    unsigned int adapterCount = *(unsigned int*)((char*)pThis + 0x10);
    void** pAdapterArray = *(void***)((char*)pThis + 0x8); 

    if (!pAdapterArray || adapterCount == 0 || adapterCount > 100 || !pGetAdapterStat) return result;

    for (unsigned int i = 0; i < adapterCount; i++) {
        char* pAdapterInfoEx = (char*)pAdapterArray[i];
        if (!pAdapterInfoEx) continue;

        // 1. Call the official getter to obtain LinkSpeedBps (cmd = 4)
        ULONG64 linkSpeedBps = pGetAdapterStat(pThis, i, 4, 0);

        if (linkSpeedBps == 0 || linkSpeedBps == (ULONG64)-1) continue;

        wchar_t speedStr[261] = {0};
        double speedGbps = (double)linkSpeedBps / 1000000000.0;
        double speedMbps = (double)linkSpeedBps / 1000000.0;
        
        if (speedGbps >= 1.0) {
            swprintf(speedStr, 261, L"%.1f Gbps", speedGbps);
        } else {
            swprintf(speedStr, 261, L"%.0f Mbps", speedMbps);
        }

        // 2. Write into the UIProps buffer using the dynamic offset
        char** ppUIProps = (char**)(pAdapterInfoEx + g_UIPropsOffset);
        if (!IsMemoryReadable(ppUIProps, sizeof(void*))) continue;
        
        char* pUIProps = *ppUIProps;
        if (!pUIProps) continue;

        wchar_t* pDnsBuffer = (wchar_t*)(pUIProps + 0x30); // Internal string offset 0x30 is highly stable

        if (IsMemoryWritable(pDnsBuffer, 261 * sizeof(wchar_t))) {
            wcscpy_s(pDnsBuffer, 261, speedStr);
        }
    }

    return result;
}

BOOL ModInit(void) {
    Wh_Log(L">>> Taskmgr Real Link Speed Mod Initializing...");
    LoadUserSettings();
    HMODULE hTaskmgr = GetModuleHandleW(NULL);
    if (!hTaskmgr) return FALSE;

    // Register core hooks and resolve target function symbols
    WindhawkUtils::SYMBOL_HOOK taskmgrExeHooks[] = {
        {
            { L"public: long __cdecl CAdapter::Update(bool *,unsigned long)" },
            (void**)&Original_CAdapter_Update,
            (void*)Hooked_CAdapter_Update,
            false
        },
        {
            { L"public: unsigned __int64 __cdecl CAdapter::GetAdapterStat(unsigned long,enum NETCOLUMNID,int)" },
            (void**)&pGetAdapterStat,
            nullptr,
            false
        },
        {
            // Use a dummy hook to obtain the exact UpdateDNSName pointer
            { L"private: void __cdecl CAdapter::UpdateDNSName(unsigned short const *,struct ADAPTER_INFOEX *)" },
            (void**)&Original_CAdapter_UpdateDNSName,
            nullptr,
            true // Optional; base loading is not affected even if not found
        }
    };

    if (!WindhawkUtils::HookSymbols(hTaskmgr, taskmgrExeHooks, ARRAYSIZE(taskmgrExeHooks))) {
        Wh_Log(L"ERROR: Failed to hook main CAdapter symbols.");
        return FALSE;
    }

    // ------------------------------------------------
    // [ASM pattern extraction] extract 0x1F90
    // ------------------------------------------------
    if (Original_CAdapter_UpdateDNSName) {
        // Match pattern: mov rcx, [rdi + 0x1f90] or similar instructions
        // Require at least 3 hex digits to avoid matching short local offsets like +0x30
        std::regex rx(R"(mov\s+r\w+,\s*(?:qword ptr\s*)?\[r\w+\s*\+\s*0x([1-9a-fA-F][0-9a-fA-F]{2,})\])", std::regex_constants::icase);
        
        // Scan the first 100 instructions (Limit = 100)
        size_t extracted = OffsetFromAssemblyRegex((void*)Original_CAdapter_UpdateDNSName, 0x1F90, rx, 100);
        if (extracted != 0x1F90) {
            g_UIPropsOffset = extracted;
            Wh_Log(L"Dynamically extracted UIProps offset from ASM: 0x%zX", g_UIPropsOffset);
        } else {
            Wh_Log(L"Regex extraction resulted in default: 0x%zX", g_UIPropsOffset);
        }
    }

    // ------------------------------------------------
    // LoadStringW internationalization hook
    // ------------------------------------------------
    HMODULE hUser32 = GetModuleHandleW(L"user32.dll");
    if (hUser32) {
        void* pLoadStringW = (void*)GetProcAddress(hUser32, "LoadStringW");
        Wh_SetFunctionHook(pLoadStringW, (void*)Hooked_LoadStringW_User32, (void**)&Original_LoadStringW_User32);
    }

    HMODULE hKernelBase = GetModuleHandleW(L"KernelBase.dll");
    if (hKernelBase) {
        void* pLoadStringW = (void*)GetProcAddress(hKernelBase, "LoadStringW");
        Wh_SetFunctionHook(pLoadStringW, (void*)Hooked_LoadStringW_KernelBase, (void**)&Original_LoadStringW_KernelBase);
    }

    Wh_Log(L"Hook applied successfully! Real speed active.");
    return TRUE;
}

void ModUninit() {
    Wh_Log(L"<<< Taskmgr Link Speed Mod Uninitialized");
}

void ModSettingsChanged(void) {
    LoadUserSettings();
    Wh_Log(L"Settings reloaded: Custom label override updated.");
}
}  // namespace f_linkspeed


// ===========================================================================
// taskmgr-network-bytes
// ===========================================================================
namespace f_netbytes {
namespace {

// Task Manager string resource IDs (Taskmgr.exe.mui).
constexpr DWORD kIdBps = 32875;   // "bps"
constexpr DWORD kIdKbps = 32876;  // "Kbps"
constexpr DWORD kIdMbps = 32877;  // "Mbps"
constexpr DWORD kIdGbps = 32878;  // "Gbps"
constexpr DWORD kIdBytesPerSec = 32879;      // "B/sec"
constexpr DWORD kIdKBytesPerSec = 32880;     // "KB/s"
constexpr DWORD kIdMBytesPerSec = 32881;     // "MB/s"
constexpr DWORD kIdGBytesPerSec = 32882;     // "GB/s"
constexpr DWORD kIdValueUnitPattern = 34563;  // "%1!s! %2!s!"
constexpr DWORD kIdNetworkColumnMbps = 37034;  // "%s Mbps"

constexpr PCWSTR kEnglishByteUnits[] = {L"B/s", L"KB/s", L"MB/s", L"GB/s"};
constexpr PCWSTR kDefaultValueUnitPattern = L"%1!s! %2!s!";

// WDC column type of the Processes/Users "Network" column.
constexpr BYTE kNetworkColumnType = 0x0A;

// GetColumnText raises any non-zero network value below this to this.
constexpr double kNetworkColumnMinMbps = static_cast<double>(0.1f);

// Fixed output size used by the link speed overload of GetBestFitUnit.
constexpr size_t kLinkSpeedBufferChars = 0x80;

// Byte patterns for the hook targets, used when Microsoft's symbol server
// doesn't have a PDB for the installed Task Manager build yet. '??' marks
// bytes that can change without the function itself changing: relocated
// addresses, stack frame sizes and local variable offsets. Matching is exact
// otherwise, and only function starts from the executable's function table
// are considered, so moved code still matches but a lookalike function does
// not.
constexpr PCSTR kPatternGetBestFitUnit =
    "48 8B C4 48 89 58 08 55 56 57 41 56 41 57 "
    "48 81 EC ?? ?? ?? ?? 0F 29 70 C8 48 8B 05 "
    "?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? "
    "?? 48 8B BC 24 ?? ?? ?? ?? 4C 8B F2 F2 0F "
    "10 B4 24 ?? ?? ?? ?? 45 33 FF 0F 28 DE 4C "
    "89 7C 24 ?? 48 8B D7 4C 89 7C 24 ?? 49 8B "
    "F0 E8 ?? ?? ?? ?? 48 98 4C 8D 44 24 ?? 66 "
    "44 89 3E 48 8D 2C 40 8B 54 EF 10 E8 ?? ?? "
    "?? ?? 8B D8 85 C0";
constexpr PCSTR kPatternGetBestFitUnitPair =
    "48 8B C4 48 89 58 08 55 56 57 41 54 41 55 "
    "41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC "
    "?? ?? ?? ?? 0F 29 70 B8 0F 29 78 A8 44 0F "
    "29 40 98 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 "
    "89 45 60 48 8B BD ?? ?? ?? ?? 33 C9 4C 8B "
    "E2 F2 0F 10 B5 ?? ?? ?? ?? 4D 8B E8 66 41 "
    "89 08 44 8B F9 66 41 89 09 48 8B D7 4C 89 "
    "4C 24 ?? 0F 28 DE 48 89 4C 24 ?? 48 89 4C "
    "24 ?? 48 89 4C 24 ?? 48 89 4C 24 ?? 38 8D "
    "?? ?? ?? ?? 0F 85 ?? ?? ?? ?? E8 ?? ?? ?? "
    "?? F2 0F 10 BD ?? ?? ?? ??";
constexpr PCSTR kPatternGetBestFitUnitLinkSpeed =
    "48 89 5C 24 08 48 89 6C 24 18 56 57 41 56 "
    "48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? "
    "48 33 C4 48 89 84 24 ?? ?? ?? ?? 48 8B 9C "
    "24 ?? ?? ?? ?? 4C 8D 1D ?? ?? ?? ?? 33 ED "
    "4C 8B F2 48 89 6C 24 ?? 44 8B CD 48 89 6C "
    "24 ?? 66 89 2A 48 85 DB 74 ?? 44 8B C5 4C "
    "8D 15 ?? ?? ?? ?? 49 8B D3 49 3B D2 7D ?? "
    "0F 57 C9 48 85 DB 78 ?? F2 48 0F 2A CB EB "
    "?? 48 8B C3 48 8B CB 48 D1 E9 83 E0 01 48 "
    "0B C8 F2 48 0F 2A C9 F2 0F 58 C9 F2 0F 10 "
    "02 66 0F 2F C1 73 ?? 41 FF C0 48 83 C2 18 "
    "EB ??";
constexpr PCSTR kPatternTmPrintOrFormatBuffer =
    "40 53 55 56 57 41 54 41 55 41 56 41 57 48 "
    "81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 "
    "33 C4 48 89 84 24 ?? ?? ?? ?? 41 69 D9 6D "
    "4E C6 41 4C 8B FA 41 69 C1 CD 0D 01 00 4D "
    "8B E0 41 B8 01 00 00 00 41 8B E9 41 B9 AB "
    "AA AA AA 4C 8B F1 81 C3 39 30 00 00 41 03 "
    "C0 C1 EB 10 25 00 00 FF FF 0B D8 41 8B C1 "
    "F7 E3 C1 EA 09 8D 04 52 C1 E0 08 2B D8 45 "
    "33 ED 41 0F B7 FD B8 00 03 00 00 48 8D 0D "
    "?? ?? ?? ?? 66 3B F8 0F 83 ?? ?? ?? ?? 0F "
    "B7 C3 48 03 C0 83 7C C1 ?? FF 0F 84 ?? ?? "
    "?? ?? 3B 6C C1 ?? 0F 85 ?? ?? ?? ?? 48 8B "
    "7C C1 ??";
constexpr PCSTR kPatternGetColumnText =
    "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 "
    "18 57 41 56 41 57 48 83 EC ?? 41 0F B6 18 "
    "49 8B F9 48 83 22 00 49 8B E8 0F 29 70 D8 "
    "48 8B F2 4C 8B F1 48 8D 0D ?? ?? ?? ?? E8 "
    "?? ?? ?? ?? 44 8D 53 F9 41 83 FA 04 76 6B "
    "83 FB 0E 74 66 84 C0 74 05 83 FB 20 74 5D "
    "83 FB 0F 0F 84 ?? ?? ?? ?? 8B 84 24 ?? ?? "
    "?? ?? 4C 8B CF 89 44 24 ?? 4C 8B C5 48 8B "
    "84 24 ?? ?? ?? ?? 48 8B D6 49 8B CE 48 89 "
    "44 24 ?? E8 ?? ?? ?? ?? 8B D8 85 C0 0F 88 "
    "?? ?? ?? ?? 48 8B 6C 24 ?? 8B C3 48 8B 5C "
    "24 ?? 48 8B 74 24 ?? 0F 28 74 24 30 48 83 "
    "C4 40 41 5F 41 5E 5F C3";
constexpr PCSTR kPatternWdcStringMapLoadStringW =
    "48 8B C4 48 89 58 10 48 89 68 18 48 89 70 "
    "20 48 89 48 08 57 41 54 41 55 41 56 41 57 "
    "48 83 EC ?? 69 F2 6D 4E C6 41 4C 8D 25 ?? "
    "?? ?? ?? 69 C2 CD 0D 01 00 4D 8B F8 44 8B "
    "F2 41 B8 01 00 00 00 41 B9 AB AA AA AA 81 "
    "C6 39 30 00 00 41 03 C0 C1 EE 10 25 00 00 "
    "FF FF 0B F0 41 8B C1 F7 E6 C1 EA 09 8D 04 "
    "52 C1 E0 08 2B F0 33 FF 0F B7 EF 49 89 3F "
    "B8 00 03 00 00 66 3B E8 73 ?? 0F B7 CE 8B "
    "C1 48 03 C0 41 83 7C C4 ?? FF 74 ?? 45 3B "
    "74 C4 ?? 75 ?? 48 03 C9 49 8B 44 CC ?? 49 "
    "89 07 33 C0 48 8B 5C 24 ?? 48 8B 6C 24 ?? "
    "48 8B 74 24 ?? 48 83 C4 30 41 5F 41 5E 41 "
    "5D 41 5C 5F C3";
constexpr PCSTR kPatternWdcLoadString =
    "48 89 5C 24 08 57 48 83 EC ?? 49 81 F8 FF "
    "FF FF 7F 77 ?? 49 63 C0 49 3B C0 0F 87 ?? "
    "?? ?? ?? 45 8B C8 4C 8B C2 8B D1 48 8B 0D "
    "?? ?? ?? ?? 48 FF 15 ?? ?? ?? ?? 0F 1F 44 "
    "00 00 85 C0 7E ?? 33 DB 8B C3 48 8B 5C 24 "
    "?? 48 83 C4 30 5F C3 CC BB 16 02 07 80 48 "
    "FF 15 ?? ?? ?? ?? 0F 1F 44 00 00 41 B8 27 "
    "00 00 00 89 5C 24 ?? 4C 8D 0D ?? ?? ?? ?? "
    "89 44 24 ?? 48 8D 15 ?? ?? ?? ?? 48 8D 0D "
    "?? ?? ?? ?? E8 ?? ?? ?? ?? EB ?? 48 FF 15 "
    "?? ?? ?? ?? 0F 1F 44 00 00 8B D8 85 C0 74 "
    "?? 7E ?? 0F B7 D8 81 CB 00 00 07 80 8B FB "
    "85 DB 79 ??";

struct ATM_INSTANT_VALUE_SCALE {
    double threshold;
    double multiplier;
    DWORD stringId;
    DWORD padding;
};
static_assert(sizeof(ATM_INSTANT_VALUE_SCALE) == 0x18);

// Same shape as Task Manager's network table (Kbps, Mbps, Gbps), with byte
// units. Values are divided by 8 before they reach it. Each unit switches to
// the next one where it would round up to "1,000" (999.5 and above).
//
// Task Manager reads exactly 3 rows: its scaleCount argument is unused, and
// the callers never set it. The 4th row is spare, so a later build that reads
// one more row still stays within this table.
constexpr ATM_INSTANT_VALUE_SCALE kByteScale[] = {
    {999499.999, 1e-3, kIdKBytesPerSec, 0},
    {999499999.999, 1e-6, kIdMBytesPerSec, 0},
    {999999999999.0, 1e-9, kIdGBytesPerSec, 0},
    {1e300, 1e-9, kIdGBytesPerSec, 0},
};

// Settings.
bool g_englishUnits = true;

// Identified by the unit string IDs. scaleCount can't be used: see kByteScale.
bool IsNetworkScale(const ATM_INSTANT_VALUE_SCALE* scale) {
    return scale && scale[0].stringId == kIdKbps &&
           scale[1].stringId == kIdMbps && scale[2].stringId == kIdGbps;
}

// Network graph scale labels: string ID and the bits/s value it names.
struct NetworkLabel {
    DWORD id;
    double bitsPerSec;
};

constexpr NetworkLabel kNetworkLabels[] = {
    {32808, 1},     {32809, 1e4},   {32810, 1e6},   {32811, 1e7},
    {32812, 1e8},   {32813, 1e9},   {32814, 1e10},  {32815, 1e11},
    {32816, 1e5},   {32820, 1e5},   {32821, 5e5},   {32822, 1e6},
    {32823, 11e6},  {32824, 54e6},  {32825, 1e8},   {32826, 5e8},
    {32827, 1e9},   {32828, 1e10},  {32829, 1e11},  {32830, 45e4},
    {32831, 8e5},   {32832, 77e5},  {32833, 32e6},  {32834, 5e7},
    {32835, 2e8},   {32836, 3e8},   {32837, 2e9},   {32838, 1e10},
    {32884, 5e6},   {32885, 26e6},  {32886, 25e7},  {32887, 36e5},
    {32888, 17e6},  {32889, 113e6},
};

// Built once, never freed: Task Manager may hold these pointers after the mod
// unloads. nullptr means "leave this ID alone".
PCWSTR g_networkLabelText[ARRAYSIZE(kNetworkLabels)];
INIT_ONCE g_initOnce = INIT_ONCE_STATIC_INIT;

WCHAR g_decimalSep[8] = L".";
WCHAR g_thousandSep[8] = L",";
NUMBERFMTW g_localeNumberFormat = {0, 1, 3, g_decimalSep, g_thousandSep, 1};

// Strings loaded once. g_byteUnits are English or localized per the
// "unitNames" setting; g_byteUnitText holds never-freed copies for the hooks.
std::wstring g_valueUnitPattern = kDefaultValueUnitPattern;
std::wstring g_byteUnits[4];  // B/s, KB/s, MB/s, GB/s
PCWSTR g_byteUnitText[4];
std::wstring g_networkColumnPrefix;
// Whether string 37034 is still the "%s Mbps" network column format.
bool g_networkColumnFormatValid;

thread_local bool t_hasRawNetworkMbps;
thread_local double t_rawNetworkMbps;

// Set while a network GetBestFitUnit call runs, so the string hook can answer
// its byte unit IDs with the English names without affecting other callers.
thread_local bool t_inNetworkBestFitUnit;

bool IsBidiMark(WCHAR c) {
    return c == 0x200E || c == 0x200F || c == 0x061C ||
           (c >= 0x202A && c <= 0x202E) || (c >= 0x2066 && c <= 0x2069);
}

std::wstring LoadTmString(DWORD id) {
    WCHAR buffer[256];
    int len = LoadStringW(GetModuleHandleW(nullptr), id, buffer,
                          ARRAYSIZE(buffer));
    return len > 0 ? std::wstring(buffer, len) : std::wstring();
}

std::wstring LeadingBidiMarks(const std::wstring& s) {
    size_t i = 0;
    while (i < s.size() && IsBidiMark(s[i])) {
        i++;
    }
    return s.substr(0, i);
}

std::wstring StripBidiMarks(const std::wstring& s) {
    std::wstring result;
    for (WCHAR c : s) {
        if (!IsBidiMark(c)) {
            result += c;
        }
    }
    return result;
}

PCWSTR CopyToProcessHeap(const std::wstring& s) {
    size_t bytes = (s.size() + 1) * sizeof(WCHAR);
    auto* copy = static_cast<PWSTR>(HeapAlloc(GetProcessHeap(), 0, bytes));
    if (copy) {
        memcpy(copy, s.c_str(), bytes);
    }
    return copy;
}

// Whether `pattern` is safe for FormatMessageW with the two string arguments of
// ComposeValueUnit: it uses inserts %1 and %2, both as strings, and no other.
bool IsValidValueUnitPattern(const std::wstring& pattern) {
    bool has1 = false;
    bool has2 = false;
    for (size_t i = 0; i < pattern.size(); i++) {
        if (pattern[i] != L'%' || i + 1 >= pattern.size()) {
            continue;
        }
        WCHAR next = pattern[i + 1];
        if (next < L'1' || next > L'9') {
            i++;  // An escape like %% or %n, not an insert.
            continue;
        }

        size_t end = i + 1;
        int insert = 0;
        // FormatMessageW only reads ASCII digits as an insert number.
        while (end < pattern.size() && pattern[end] >= L'0' &&
               pattern[end] <= L'9') {
            insert = insert * 10 + (pattern[end] - L'0');
            end++;
        }
        if (insert != 1 && insert != 2) {
            return false;
        }
        if (end < pattern.size() && pattern[end] == L'!' &&
            pattern.compare(end, 3, L"!s!") != 0) {
            return false;
        }
        (insert == 1 ? has1 : has2) = true;
        i = end - 1;
    }
    return has1 && has2;
}

void LoadStrings() {
    std::wstring pattern = LoadTmString(kIdValueUnitPattern);
    if (IsValidValueUnitPattern(pattern)) {
        g_valueUnitPattern = pattern;
    } else {
        Wh_Log(L"Using the default value/unit pattern instead of \"%s\"",
               pattern.c_str());
    }

    for (int i = 0; i < 4; i++) {
        if (!g_englishUnits) {
            g_byteUnits[i] = LoadTmString(kIdBytesPerSec + i);
        }
        if (g_byteUnits[i].empty()) {
            g_byteUnits[i] = kEnglishByteUnits[i];
        }
        g_byteUnitText[i] = CopyToProcessHeap(g_byteUnits[i]);
    }

    std::wstring columnFormat = LoadTmString(kIdNetworkColumnMbps);
    std::wstring mbps = StripBidiMarks(LoadTmString(kIdMbps));
    g_networkColumnFormatValid =
        !mbps.empty() && columnFormat.find(L"%s") != std::wstring::npos &&
        StripBidiMarks(columnFormat).find(mbps) != std::wstring::npos;
    if (!g_networkColumnFormatValid) {
        Wh_Log(L"Not converting the Network column: string %u is \"%s\"",
               kIdNetworkColumnMbps, columnFormat.c_str());
    }
    g_networkColumnPrefix = LeadingBidiMarks(columnFormat);
}

// "%1!s! %2!s!" with a value and a byte unit (kIdBytesPerSec..kIdGBytesPerSec).
std::wstring ComposeValueUnit(const std::wstring& value, DWORD unitId) {
    const std::wstring& unit = g_byteUnits[unitId - kIdBytesPerSec];

    DWORD_PTR args[] = {reinterpret_cast<DWORD_PTR>(value.c_str()),
                        reinterpret_cast<DWORD_PTR>(unit.c_str())};
    WCHAR buffer[256];
    DWORD len = FormatMessageW(
        FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
        g_valueUnitPattern.c_str(), 0, 0, buffer, ARRAYSIZE(buffer),
        reinterpret_cast<va_list*>(args));
    if (len == 0) {
        return value + L" " + unit;
    }
    return std::wstring(buffer, len);
}

// Formats `value` with `digits` decimals. With `format`, uses that number
// format (locale separators); otherwise plain "%.*f".
std::wstring FormatNumber(double value, int digits, const NUMBERFMTW* format) {
    WCHAR raw[64];
    swprintf_s(raw, ARRAYSIZE(raw), L"%.*f", digits, value);
    if (!format) {
        return raw;
    }

    NUMBERFMTW fmt = *format;
    fmt.NumDigits = digits;
    WCHAR formatted[64];
    if (!GetNumberFormatEx(LOCALE_NAME_USER_DEFAULT, 0, raw, &fmt, formatted,
                           ARRAYSIZE(formatted))) {
        return raw;
    }
    return formatted;
}

// Up to 2 decimals below 10, 1 below 100, none above, trailing zeros dropped:
// 1.25, 6.75, 12.5, 62.5, 125, 963.
std::wstring FormatSmart(double value) {
    int maxDigits = value >= 100 ? 0 : value >= 10 ? 1 : 2;
    double maxScale = std::pow(10.0, maxDigits);
    double rounded = std::round(value * maxScale) / maxScale;

    int digits = 0;
    while (digits < maxDigits) {
        double scale = std::pow(10.0, digits);
        if (std::fabs(std::round(rounded * scale) / scale - rounded) < 1e-9) {
            break;
        }
        digits++;
    }
    return FormatNumber(rounded, digits, &g_localeNumberFormat);
}

// e.g. 125000000 -> "125 MB/s".
std::wstring FormatBytesPerSec(double bytesPerSec) {
    DWORD unitId;
    double scaled;
    if (bytesPerSec > 0 && bytesPerSec < 1e3) {
        unitId = kIdBytesPerSec;
        scaled = bytesPerSec;
    } else if (bytesPerSec < 1e6) {
        unitId = kIdKBytesPerSec;
        scaled = bytesPerSec / 1e3;
    } else if (bytesPerSec < 1e9) {
        unitId = kIdMBytesPerSec;
        scaled = bytesPerSec / 1e6;
    } else {
        unitId = kIdGBytesPerSec;
        scaled = bytesPerSec / 1e9;
    }
    return ComposeValueUnit(FormatSmart(scaled), unitId);
}

UINT ParseGrouping(PCWSTR grouping) {
    UINT result = 0;
    for (PCWSTR p = grouping; *p; p++) {
        if (*p >= L'0' && *p <= L'9') {
            result = result * 10 + (*p - L'0');
        }
    }
    size_t len = wcslen(grouping);
    if (len >= 2 && wcscmp(grouping + len - 2, L";0") == 0) {
        return result / 10;  // "3;0" -> 3, "3;2;0" -> 32
    }
    return result * 10;  // "3" -> 30
}

void InitLocaleNumberFormat() {
    GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SDECIMAL, g_decimalSep,
                    ARRAYSIZE(g_decimalSep));
    GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_STHOUSAND, g_thousandSep,
                    ARRAYSIZE(g_thousandSep));

    DWORD value;
    if (GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT,
                        LOCALE_ILZERO | LOCALE_RETURN_NUMBER,
                        reinterpret_cast<LPWSTR>(&value),
                        sizeof(value) / sizeof(WCHAR))) {
        g_localeNumberFormat.LeadingZero = value;
    }
    if (GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT,
                        LOCALE_INEGNUMBER | LOCALE_RETURN_NUMBER,
                        reinterpret_cast<LPWSTR>(&value),
                        sizeof(value) / sizeof(WCHAR))) {
        g_localeNumberFormat.NegativeOrder = value;
    }
    WCHAR grouping[16];
    if (GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SGROUPING, grouping,
                        ARRAYSIZE(grouping))) {
        g_localeNumberFormat.Grouping = ParseGrouping(grouping);
    }
}

// The bit unit string ID a label for `bitsPerSec` is expected to contain.
DWORD ExpectedBitUnitId(double bitsPerSec) {
    return bitsPerSec < 1e3   ? kIdBps
           : bitsPerSec < 1e6 ? kIdKbps
           : bitsPerSec < 1e9 ? kIdMbps
                              : kIdGbps;
}

// The bit unit a localized label uses, or 0 if none matches.
DWORD DetectBitUnitId(const std::wstring& label,
                      const std::wstring (&units)[4]) {
    // Prefixed units first: "Kbps" contains "bps".
    constexpr DWORD ids[] = {kIdKbps, kIdMbps, kIdGbps, kIdBps};
    constexpr int indexes[] = {1, 2, 3, 0};
    for (int i = 0; i < 4; i++) {
        const std::wstring& unit = units[indexes[i]];
        if (!unit.empty() && label.find(unit) != std::wstring::npos) {
            return ids[i];
        }
    }
    return 0;
}

void BuildNetworkLabels() {
    std::wstring bitUnits[4] = {
        StripBidiMarks(LoadTmString(kIdBps)),
        StripBidiMarks(LoadTmString(kIdKbps)),
        StripBidiMarks(LoadTmString(kIdMbps)),
        StripBidiMarks(LoadTmString(kIdGbps)),
    };

    for (size_t i = 0; i < ARRAYSIZE(kNetworkLabels); i++) {
        const NetworkLabel& label = kNetworkLabels[i];
        std::wstring original = LoadTmString(label.id);
        DWORD expected = ExpectedBitUnitId(label.bitsPerSec);
        DWORD detected = DetectBitUnitId(StripBidiMarks(original), bitUnits);
        if (detected != expected) {
            Wh_Log(L"Not remapping label %u (\"%s\"): unexpected unit",
                   label.id, original.c_str());
            continue;
        }

        g_networkLabelText[i] =
            CopyToProcessHeap(LeadingBidiMarks(original) +
                              FormatBytesPerSec(label.bitsPerSec / 8));
    }
}

BOOL CALLBACK InitOnceCallback(PINIT_ONCE, PVOID, PVOID*) {
    InitLocaleNumberFormat();
    LoadStrings();
    BuildNetworkLabels();
    return TRUE;
}

void EnsureInitialized() {
    InitOnceExecuteOnce(&g_initOnce, InitOnceCallback, nullptr, nullptr);
}

// In English mode, the English name for a byte unit ID that a network
// GetBestFitUnit call loads, or nullptr. Other callers of the same IDs, such as
// the disk view, keep Task Manager's names.
PCWSTR GetNetworkUnitText(DWORD id) {
    if (!t_inNetworkBestFitUnit || !g_englishUnits || id < kIdKBytesPerSec ||
        id > kIdGBytesPerSec) {
        return nullptr;
    }
    EnsureInitialized();
    return g_byteUnitText[id - kIdBytesPerSec];
}

// The replacement for a network graph label ID, or nullptr.
PCWSTR GetNetworkLabelText(DWORD id) {
    if (id < kNetworkLabels[0].id ||
        id > kNetworkLabels[ARRAYSIZE(kNetworkLabels) - 1].id) {
        return nullptr;
    }
    for (size_t i = 0; i < ARRAYSIZE(kNetworkLabels); i++) {
        if (kNetworkLabels[i].id == id) {
            EnsureInitialized();
            return g_networkLabelText[i];
        }
    }
    return nullptr;
}

// Performance page Send / Receive values.
using GetBestFitUnit_t = HRESULT(WINAPI*)(void* pThis,
                                          NUMBERFMTW* numberFormat,
                                          PWSTR output,
                                          DWORD outputChars,
                                          const ATM_INSTANT_VALUE_SCALE* scale,
                                          int scaleCount,
                                          double value,
                                          int flags);
GetBestFitUnit_t GetBestFitUnit_Original;
HRESULT WINAPI GetBestFitUnit_Hook(void* pThis,
                                   NUMBERFMTW* numberFormat,
                                   PWSTR output,
                                   DWORD outputChars,
                                   const ATM_INSTANT_VALUE_SCALE* scale,
                                   int scaleCount,
                                   double value,
                                   int flags) {
    if (!IsNetworkScale(scale)) {
        return GetBestFitUnit_Original(pThis, numberFormat, output,
                                       outputChars, scale, scaleCount, value,
                                       flags);
    }

    bool wasInNetworkBestFitUnit = t_inNetworkBestFitUnit;
    t_inNetworkBestFitUnit = true;
    HRESULT hr = GetBestFitUnit_Original(pThis, numberFormat, output,
                                         outputChars, kByteScale, scaleCount,
                                         value / 8, flags);
    t_inNetworkBestFitUnit = wasInNetworkBestFitUnit;
    return hr;
}

// Performance sidebar "S: ... R: ..." pair.
using GetBestFitUnitPair_t =
    HRESULT(WINAPI*)(void* pThis,
                     NUMBERFMTW* numberFormat,
                     PWSTR output1,
                     PWSTR output2,
                     DWORD outputChars,
                     const ATM_INSTANT_VALUE_SCALE* scale,
                     int scaleCount,
                     double value1,
                     double value2,
                     int formatId1,
                     int formatId2,
                     bool sharedUnit);
GetBestFitUnitPair_t GetBestFitUnitPair_Original;
HRESULT WINAPI GetBestFitUnitPair_Hook(void* pThis,
                                       NUMBERFMTW* numberFormat,
                                       PWSTR output1,
                                       PWSTR output2,
                                       DWORD outputChars,
                                       const ATM_INSTANT_VALUE_SCALE* scale,
                                       int scaleCount,
                                       double value1,
                                       double value2,
                                       int formatId1,
                                       int formatId2,
                                       bool sharedUnit) {
    if (!IsNetworkScale(scale)) {
        return GetBestFitUnitPair_Original(
            pThis, numberFormat, output1, output2, outputChars, scale,
            scaleCount, value1, value2, formatId1, formatId2, sharedUnit);
    }

    bool wasInNetworkBestFitUnit = t_inNetworkBestFitUnit;
    t_inNetworkBestFitUnit = true;
    HRESULT hr = GetBestFitUnitPair_Original(
        pThis, numberFormat, output1, output2, outputChars, kByteScale,
        scaleCount, value1 / 8, value2 / 8, formatId1, formatId2, sharedUnit);
    t_inNetworkBestFitUnit = wasInNetworkBestFitUnit;
    return hr;
}

// "View network details" link speed. This overload is only used for network
// values: it ignores `scale` and always uses the network table. `outputChars`
// is garbage at the call site; the original writes at most 0x80 characters.
using GetBestFitUnitLinkSpeed_t =
    HRESULT(WINAPI*)(void* pThis,
                     PWSTR output,
                     DWORD outputChars,
                     const ATM_INSTANT_VALUE_SCALE* scale,
                     int scaleCount,
                     ULONGLONG bitsPerSec,
                     int flags);
GetBestFitUnitLinkSpeed_t GetBestFitUnitLinkSpeed_Original;
HRESULT WINAPI
GetBestFitUnitLinkSpeed_Hook(void* /*pThis*/,
                             PWSTR output,
                             DWORD /*outputChars*/,
                             const ATM_INSTANT_VALUE_SCALE* /*scale*/,
                             int /*scaleCount*/,
                             ULONGLONG bitsPerSec,
                             int /*flags*/) {
    EnsureInitialized();
    std::wstring text =
        FormatBytesPerSec(static_cast<double>(bitsPerSec) / 8);
    return StringCchCopyW(output, kLinkSpeedBufferChars, text.c_str());
}

// Processes / Users tabs: remembers the network value before Task Manager
// raises small values to 0.1 Mbps, for TmPrintOrFormatBuffer_Hook.
using GetColumnText_t = HRESULT(WINAPI*)(void* pThis,
                                         PWSTR* outputText,
                                         const BYTE* column,
                                         PWSTR buffer,
                                         ULONGLONG bufferChars,
                                         int flags);
GetColumnText_t GetColumnText_Original;
HRESULT WINAPI GetColumnText_Hook(void* pThis,
                                  PWSTR* outputText,
                                  const BYTE* column,
                                  PWSTR buffer,
                                  ULONGLONG bufferChars,
                                  int flags) {
    bool isNetwork = column && column[0] == kNetworkColumnType;
    if (isNetwork) {
        t_rawNetworkMbps = *reinterpret_cast<const double*>(column + 0x10);
        t_hasRawNetworkMbps = true;
    }
    HRESULT hr = GetColumnText_Original(pThis, outputText, column, buffer,
                                        bufferChars, flags);
    if (isNetwork) {
        t_hasRawNetworkMbps = false;
    }
    return hr;
}

// The Network column value as Task Manager computed it, before rounding up.
double GetNetworkColumnMbps(double passedMbps) {
    if (!t_hasRawNetworkMbps) {
        return passedMbps;
    }
    double raw = t_rawNetworkMbps;
    if (raw == passedMbps ||
        (raw > 0 && raw < kNetworkColumnMinMbps &&
         passedMbps == kNetworkColumnMinMbps)) {
        return raw;
    }
    return passedMbps;
}

// Processes / Users tabs "Network" column: "%s Mbps" -> "x KB/s" / "x MB/s".
using TmPrintOrFormatBuffer_t = HRESULT(WINAPI*)(PWSTR buffer,
                                                 SIZE_T bufferChars,
                                                 NUMBERFMTW* numberFormat,
                                                 DWORD formatId,
                                                 double value,
                                                 int useNumberFormat);
TmPrintOrFormatBuffer_t TmPrintOrFormatBuffer_Original;
HRESULT WINAPI TmPrintOrFormatBuffer_Hook(PWSTR buffer,
                                          SIZE_T bufferChars,
                                          NUMBERFMTW* numberFormat,
                                          DWORD formatId,
                                          double value,
                                          int useNumberFormat) {
    if (formatId != kIdNetworkColumnMbps) {
        return TmPrintOrFormatBuffer_Original(buffer, bufferChars,
                                              numberFormat, formatId, value,
                                              useNumberFormat);
    }

    EnsureInitialized();
    if (!g_networkColumnFormatValid) {
        return TmPrintOrFormatBuffer_Original(buffer, bufferChars,
                                              numberFormat, formatId, value,
                                              useNumberFormat);
    }

    double kbps = GetNetworkColumnMbps(value) * 125;  // 1 Mbps = 125 KB/s
    if (kbps < 0) {
        kbps = 0;
    } else if (kbps > 0 && kbps < 0.1) {
        kbps = 0.1;
    }

    DWORD unitId;
    double scaled;
    int digits;
    if (kbps >= 999.95) {
        unitId = kIdMBytesPerSec;
        scaled = kbps / 1000;
        digits = 1;
    } else {
        unitId = kIdKBytesPerSec;
        scaled = kbps;
        digits = kbps == 0 ? 0 : kbps >= 99.95 ? 0 : 1;
    }

    const NUMBERFMTW* format =
        useNumberFormat && numberFormat ? numberFormat : nullptr;
    std::wstring text =
        g_networkColumnPrefix +
        ComposeValueUnit(FormatNumber(scaled, digits, format), unitId);
    return StringCchCopyW(buffer, bufferChars, text.c_str());
}

// Graph scale labels and English unit names, through Task Manager's string
// cache. Replacements are returned without entering the cache.
using WdcStringMap_LoadStringW_t = HRESULT(WINAPI*)(void* pThis,
                                                    DWORD id,
                                                    PWSTR* string);
WdcStringMap_LoadStringW_t WdcStringMap_LoadStringW_Original;
HRESULT WINAPI WdcStringMap_LoadStringW_Hook(void* pThis,
                                             DWORD id,
                                             PWSTR* string) {
    PCWSTR text = GetNetworkUnitText(id);
    if (!text) {
        text = GetNetworkLabelText(id);
    }
    if (text) {
        *string = const_cast<PWSTR>(text);
        return S_OK;
    }
    return WdcStringMap_LoadStringW_Original(pThis, id, string);
}

// Graph scale labels, uncached loads. Unit names are not replaced here: when
// the cache calls this, the result is cached and shared with the disk view.
using WdcLoadString_t = HRESULT(WINAPI*)(DWORD id,
                                         PWSTR buffer,
                                         ULONGLONG bufferChars);
WdcLoadString_t WdcLoadString_Original;
HRESULT WINAPI WdcLoadString_Hook(DWORD id,
                                  PWSTR buffer,
                                  ULONGLONG bufferChars) {
    if (PCWSTR label = GetNetworkLabelText(id)) {
        return StringCchCopyW(buffer, bufferChars, label);
    }
    return WdcLoadString_Original(id, buffer, bufferChars);
}

struct PatternByte {
    BYTE value;
    bool exact;
};

struct Pattern {
    PatternByte bytes[256];
    size_t count;
};

int HexDigit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;
}

// Parses a space-separated byte pattern. '??' matches any byte.
bool ParsePattern(PCSTR text, Pattern* pattern) {
    pattern->count = 0;
    for (PCSTR p = text; *p;) {
        if (*p == ' ' || *p == '\t') {
            p++;
            continue;
        }
        if (pattern->count == ARRAYSIZE(pattern->bytes)) {
            return false;
        }
        if (p[0] == '?' && p[1] == '?') {
            pattern->bytes[pattern->count++] = {0, false};
            p += 2;
            continue;
        }
        int high = HexDigit(p[0]);
        int low = HexDigit(p[1]);
        if (high < 0 || low < 0) {
            return false;
        }
        pattern->bytes[pattern->count++] = {
            static_cast<BYTE>((high << 4) | low), true};
        p += 2;
    }
    return pattern->count != 0;
}

bool MatchesPattern(const BYTE* address, const Pattern& pattern) {
    for (size_t i = 0; i < pattern.count; i++) {
        if (pattern.bytes[i].exact && address[i] != pattern.bytes[i].value) {
            return false;
        }
    }
    return true;
}

const IMAGE_SECTION_HEADER* FindTextSection(const IMAGE_NT_HEADERS* nt) {
    const IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(nt);
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; i++, section++) {
        if (memcmp(section->Name, ".text", 5) == 0) {
            return section;
        }
    }
    return nullptr;
}

bool GetTextRange(HMODULE module,
                  const IMAGE_NT_HEADERS* nt,
                  const BYTE** start,
                  const BYTE** end) {
    const IMAGE_SECTION_HEADER* section = FindTextSection(nt);
    if (!section) {
        return false;
    }
    size_t imageSize = nt->OptionalHeader.SizeOfImage;
    size_t sectionSize = section->Misc.VirtualSize
                             ? section->Misc.VirtualSize
                             : section->SizeOfRawData;
    if (section->VirtualAddress > imageSize ||
        sectionSize > imageSize - section->VirtualAddress) {
        return false;
    }
    *start = reinterpret_cast<const BYTE*>(module) + section->VirtualAddress;
    *end = *start + sectionSize;
    return true;
}

// A RUNTIME_FUNCTION entry from the exception directory (.pdata).
struct PdataEntry {
    DWORD beginAddress;
    DWORD endAddress;
    DWORD unwindInfo;
};
static_assert(sizeof(PdataEntry) == 0xC);

// Matches `pattern` at the start of a function from the exception directory
// (.pdata). Moving a function to a different address doesn't matter because
// the function table supplies the candidates. The match must be unique; a
// pattern that fits more than one function is refused.
const BYTE* FindPatternInFunctions(HMODULE module,
                                   const IMAGE_NT_HEADERS* nt,
                                   const Pattern& pattern) {
    const BYTE* textStart;
    const BYTE* textEnd;
    if (!GetTextRange(module, nt, &textStart, &textEnd)) {
        return nullptr;
    }

    const IMAGE_DATA_DIRECTORY& directory =
        nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
    size_t imageSize = nt->OptionalHeader.SizeOfImage;
    if (directory.VirtualAddress == 0 ||
        directory.Size < sizeof(PdataEntry) ||
        directory.Size % sizeof(PdataEntry) != 0 ||
        directory.VirtualAddress > imageSize ||
        directory.Size > imageSize - directory.VirtualAddress) {
        return nullptr;
    }

    const BYTE* base = reinterpret_cast<const BYTE*>(module);
    size_t textStartOffset = static_cast<size_t>(textStart - base);
    size_t textEndOffset = static_cast<size_t>(textEnd - base);
    const auto* functions = reinterpret_cast<const PdataEntry*>(
        base + directory.VirtualAddress);
    size_t functionCount = directory.Size / sizeof(PdataEntry);

    const BYTE* match = nullptr;

    for (size_t i = 0; i < functionCount; i++) {
        size_t offset = functions[i].beginAddress;
        if (offset < textStartOffset || offset > textEndOffset ||
            pattern.count > textEndOffset - offset) {
            continue;
        }

        const BYTE* start = base + offset;
        if (start == match || !MatchesPattern(start, pattern)) {
            continue;
        }
        if (match) {
            Wh_Log(L"Byte pattern matches more than one function");
            return nullptr;
        }
        match = start;
    }

    return match;
}

// Finds `pattern` at a function start. Returns nullptr unless it matches
// exactly one function.
const BYTE* FindPattern(HMODULE module, PCSTR patternText) {
    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(module);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) {
        return nullptr;
    }
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(
        reinterpret_cast<const BYTE*>(module) + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) {
        return nullptr;
    }

    Pattern pattern;
    if (!ParsePattern(patternText, &pattern)) {
        return nullptr;
    }

    return FindPatternInFunctions(module, nt, pattern);
}

// Hooks `pattern` if it can be found unambiguously. Used only for functions
// that HookSymbols couldn't resolve.
template <typename Prototype>
bool HookByPattern(PCSTR pattern,
                   Prototype* hookFunction,
                   Prototype** originalFunction,
                   PCWSTR name) {
    const BYTE* target = FindPattern(GetModuleHandleW(nullptr), pattern);
    if (!target) {
        Wh_Log(L"%s: byte pattern not found or ambiguous", name);
        return false;
    }
    if (!Wh_SetFunctionHook(
            const_cast<BYTE*>(target), reinterpret_cast<void*>(hookFunction),
            reinterpret_cast<void**>(originalFunction))) {
        Wh_Log(L"%s: Wh_SetFunctionHook failed", name);
        return false;
    }
    Wh_Log(L"%s: hooked at %p (byte pattern)", name, target);
    return true;
}

void LoadSettings() {
    auto unitNames = WindhawkUtils::StringSetting::make(L"unitNames");
    g_englishUnits = wcscmp(unitNames, L"localized") != 0;
}

}  // namespace

BOOL ModInit() {
    Wh_Log(L">");

    LoadSettings();

    WindhawkUtils::SYMBOL_HOOK taskmgrExeHooks[] = {
        {
            {LR"(protected: long __cdecl AtmBaseView::GetBestFitUnit(struct _numberfmtW *,unsigned short *,unsigned long,struct ATM_INSTANT_VALUE_SCALE const *,int,double,int))"},
            &GetBestFitUnit_Original,
            GetBestFitUnit_Hook,
            true,
        },
        {
            {LR"(protected: long __cdecl AtmBaseView::GetBestFitUnit(struct _numberfmtW *,unsigned short *,unsigned short *,unsigned long,struct ATM_INSTANT_VALUE_SCALE const *,int,double,double,int,int,bool))"},
            &GetBestFitUnitPair_Original,
            GetBestFitUnitPair_Hook,
            true,
        },
        {
            {LR"(protected: long __cdecl AtmBaseView::GetBestFitUnit(unsigned short *,unsigned long,struct ATM_INSTANT_VALUE_SCALE const *,int,unsigned __int64,int))"},
            &GetBestFitUnitLinkSpeed_Original,
            GetBestFitUnitLinkSpeed_Hook,
            true,
        },
        {
            {LR"(long __cdecl TmPrintOrFormatBuffer(unsigned short *,unsigned __int64,struct _numberfmtW *,unsigned long,double,int))"},
            &TmPrintOrFormatBuffer_Original,
            TmPrintOrFormatBuffer_Hook,
            true,
        },
        {
            {LR"(public: virtual long __cdecl WdcApplicationsMonitor::GetColumnText(unsigned short * *,struct _WDC_DATA_COLUMN const *,unsigned short *,unsigned __int64,int))"},
            &GetColumnText_Original,
            GetColumnText_Hook,
            true,
        },
        {
            {LR"(public: long __cdecl WdcStringMap::LoadStringW(unsigned long,unsigned short * *))"},
            &WdcStringMap_LoadStringW_Original,
            WdcStringMap_LoadStringW_Hook,
            true,
        },
        {
            {LR"(long __cdecl WdcLoadString(unsigned long,unsigned short *,unsigned __int64))"},
            &WdcLoadString_Original,
            WdcLoadString_Hook,
            true,
        },
    };

    if (!WindhawkUtils::HookSymbols(GetModuleHandleW(nullptr), taskmgrExeHooks,
                                    ARRAYSIZE(taskmgrExeHooks))) {
        Wh_Log(L"Task Manager symbols are unavailable; trying byte patterns");
    }

    // Microsoft's symbol server can lag behind a Windows update. The patterns
    // are only used for functions the symbol lookup didn't resolve, so normal
    // symbol-based hooking stays in charge whenever a PDB is available.
    if (!GetBestFitUnit_Original) {
        HookByPattern(kPatternGetBestFitUnit, GetBestFitUnit_Hook,
                      &GetBestFitUnit_Original,
                      L"GetBestFitUnit (Send/Receive)");
    }
    if (!GetBestFitUnitPair_Original) {
        HookByPattern(kPatternGetBestFitUnitPair, GetBestFitUnitPair_Hook,
                      &GetBestFitUnitPair_Original,
                      L"GetBestFitUnit (sidebar)");
    }
    if (!GetBestFitUnitLinkSpeed_Original) {
        HookByPattern(kPatternGetBestFitUnitLinkSpeed,
                      GetBestFitUnitLinkSpeed_Hook,
                      &GetBestFitUnitLinkSpeed_Original,
                      L"GetBestFitUnit (link speed)");
    }
    if (!TmPrintOrFormatBuffer_Original) {
        HookByPattern(kPatternTmPrintOrFormatBuffer,
                      TmPrintOrFormatBuffer_Hook,
                      &TmPrintOrFormatBuffer_Original,
                      L"TmPrintOrFormatBuffer");
    }
    if (!GetColumnText_Original) {
        HookByPattern(kPatternGetColumnText, GetColumnText_Hook,
                      &GetColumnText_Original,
                      L"WdcApplicationsMonitor::GetColumnText");
    }
    if (!WdcStringMap_LoadStringW_Original) {
        HookByPattern(kPatternWdcStringMapLoadStringW,
                      WdcStringMap_LoadStringW_Hook,
                      &WdcStringMap_LoadStringW_Original,
                      L"WdcStringMap::LoadStringW");
    }
    if (!WdcLoadString_Original) {
        HookByPattern(kPatternWdcLoadString, WdcLoadString_Hook,
                      &WdcLoadString_Original, L"WdcLoadString");
    }

    struct {
        PCWSTR name;
        bool found;
    } const results[] = {
        {L"GetBestFitUnit (Send/Receive)", GetBestFitUnit_Original != nullptr},
        {L"GetBestFitUnit (sidebar)", GetBestFitUnitPair_Original != nullptr},
        {L"GetBestFitUnit (link speed)",
         GetBestFitUnitLinkSpeed_Original != nullptr},
        {L"TmPrintOrFormatBuffer", TmPrintOrFormatBuffer_Original != nullptr},
        {L"WdcApplicationsMonitor::GetColumnText",
         GetColumnText_Original != nullptr},
        {L"WdcStringMap::LoadStringW",
         WdcStringMap_LoadStringW_Original != nullptr},
        {L"WdcLoadString", WdcLoadString_Original != nullptr},
    };

    bool anyFound = false;
    for (const auto& result : results) {
        Wh_Log(L"%s: %s", result.name, result.found ? L"hooked" : L"NOT FOUND");
        anyFound |= result.found;
    }

    if (g_englishUnits && !WdcStringMap_LoadStringW_Original) {
        Wh_Log(L"The Performance page keeps Task Manager's unit names: "
               L"WdcStringMap::LoadStringW is not hooked");
    }

    return anyFound;
}

void ModUninit() {
    Wh_Log(L">");
}

BOOL ModSettingsChanged(BOOL* bReload) {
    Wh_Log(L">");

    // Strings and labels are built once per load; reload to rebuild them.
    *bReload = TRUE;
    return TRUE;
}
}  // namespace f_netbytes


// ===========================================================================
// taskmgr-tab-slide-animation
// ===========================================================================
namespace f_tabslide {
// Custom message posted from the worker thread to the hook thread asking it to
// destroy the overlay window (a window must be destroyed on its creating thread).
#define WM_FADE_DESTROY_WND (WM_APP + 1)

// Render the window's own DirectComposition/WinUI content (added in Win 8.1). Lets
// us capture the new view even though our topmost overlay covers it on screen.
#ifndef PW_RENDERFULLCONTENT
#define PW_RENDERFULLCONTENT 0x00000002
#endif

// CLSID_CUIAutomation / IID_IUIAutomation defined inline so we don't depend on the
// uuid import library being linked.
static const CLSID kCLSID_CUIAutomation =
    { 0xff48dba4, 0x60ef, 0x4201, { 0xaa, 0x87, 0x54, 0x10, 0x3e, 0xef, 0x59, 0x4e } };
static const IID kIID_IUIAutomation =
    { 0x30cbe57d, 0xd9d0, 0x452a, { 0xab, 0x13, 0x7a, 0xc5, 0xac, 0x48, 0x25, 0xee } };

// Animation styles.
enum { ANIM_FADE = 0, ANIM_SLIDE = 1 };

// -------------------------------------------------------------------------
// State
// -------------------------------------------------------------------------

// Data handed to the worker thread. The captured old frame lives on the overlay
// (g_overlay.frozenBmp), so the worker only needs the click point, overlay rect,
// the window (for PrintWindow capture) and which style to play.
struct TabAnimData {
    HWND  root;      // the Task Manager window (for PrintWindow capture)
    POINT clickPt;   // screen point of the nav click (for UI Automation)
    RECT  fullRect;  // screen rect the overlay covers
    RECT  winRect;   // window rect at mouse-down (to detect a move/resize mid-cycle)
    int   mode;      // ANIM_FADE or ANIM_SLIDE
};

// The single live overlay. Created on the hook thread at mouse-down, read by the
// worker during the animation, destroyed on the hook thread afterwards.
struct OverlayState {
    HWND    hwnd;       // topmost, click-through, layered window
    HBITMAP frozenBmp;  // the full old frame captured at mouse-down (overlay owns it)
    RECT    rect;       // screen rect of the overlay
    HWND    srcWnd;     // source window (to detect a move while the overlay is live)
    RECT    srcRect;    // source window rect when the overlay was created
};

std::atomic<int>  g_animType{ANIM_FADE};
std::atomic<int>  g_durationMs{250};
std::atomic<int>  g_topInset{48};
std::atomic<int>  g_captureDelay{140};
std::atomic<int>  g_changeThreshold{2};
std::atomic<bool> g_slideVertical{false};

std::atomic<bool> g_inProgress{false}; // an animation cycle (overlay live) is in flight

// Pairing state between mouse-down (create overlay) and mouse-up (start worker). The
// active style is captured into g_pendingMode at mouse-down so a mid-gesture settings
// change can't split a cycle across both code paths.
std::mutex g_mutex;
int        g_pendingMode  = ANIM_FADE;
HWND       g_pendingRoot  = NULL;
POINT      g_pendingClick = {0, 0};
RECT       g_pendingRect  = {0, 0, 0, 0};
RECT       g_pendingWin   = {0, 0, 0, 0};
bool       g_armed        = false;

// Overlay state, guarded by its own mutex (touched by hook + worker threads).
std::mutex   g_overlayMutex;
OverlayState g_overlay = { NULL, NULL, {0, 0, 0, 0}, NULL, {0, 0, 0, 0} };

// Mouse-hook thread.
HHOOK  g_mouseHook    = NULL;
HANDLE g_hookThread   = NULL;
DWORD  g_hookThreadId = 0;

void TmLoadSettings() {
    PCWSTR type = Wh_GetStringSetting(L"animation_type");
    int mode = ANIM_FADE;
    if (type) {
        if (wcscmp(type, L"slide") == 0) mode = ANIM_SLIDE;
        Wh_FreeStringSetting(type);
    }
    g_animType.store(mode, std::memory_order_relaxed);

    int ms = Wh_GetIntSetting(L"duration_ms");
    if (ms < 60)   ms = 60;
    if (ms > 1500) ms = 1500;
    g_durationMs.store(ms, std::memory_order_relaxed);

    int top = Wh_GetIntSetting(L"top_inset");
    if (top < 0) top = 0;
    g_topInset.store(top, std::memory_order_relaxed);

    int delay = Wh_GetIntSetting(L"capture_delay_ms");
    if (delay < 0)    delay = 0;
    if (delay > 1000) delay = 1000;
    g_captureDelay.store(delay, std::memory_order_relaxed);

    int thr = Wh_GetIntSetting(L"change_threshold");
    if (thr < 1)   thr = 1;
    if (thr > 100) thr = 100;
    g_changeThreshold.store(thr, std::memory_order_relaxed);

    g_slideVertical.store(Wh_GetIntSetting(L"slide_vertical") != 0, std::memory_order_relaxed);
}

// -------------------------------------------------------------------------
// Capture / geometry helpers
// -------------------------------------------------------------------------

// Grab a screen rectangle into a new DDB (caller owns / deletes it).
HBITMAP TmCaptureRect(const RECT& r) {
    int w = r.right - r.left;
    int h = r.bottom - r.top;
    if (w <= 0 || h <= 0) return NULL;

    HDC screen = GetDC(NULL);
    HDC mem = CreateCompatibleDC(screen);
    HBITMAP bmp = CreateCompatibleBitmap(screen, w, h);
    HBITMAP oldSel = (HBITMAP)SelectObject(mem, bmp);
    BitBlt(mem, 0, 0, w, h, screen, r.left, r.top, SRCCOPY);
    SelectObject(mem, oldSel);
    DeleteDC(mem);
    ReleaseDC(NULL, screen);
    return bmp;
}

// Capture a screen-space region of `root` by asking the window to render itself
// (PrintWindow + PW_RENDERFULLCONTENT). Unlike a screen BitBlt this is NOT blocked
// by our topmost overlay, so the worker can grab the freshly-switched view even
// while the overlay still covers that area on screen. Caller owns the result.
HBITMAP TmCaptureWindowRegion(HWND root, const RECT& screenRegion) {
    if (!root) return NULL;
    RECT wr;
    if (!GetWindowRect(root, &wr)) return NULL;
    int ww = wr.right - wr.left;
    int wh = wr.bottom - wr.top;
    int rw = screenRegion.right - screenRegion.left;
    int rh = screenRegion.bottom - screenRegion.top;
    if (ww <= 0 || wh <= 0 || rw <= 0 || rh <= 0) return NULL;

    HDC screen = GetDC(NULL);
    HDC winDC  = CreateCompatibleDC(screen);
    HBITMAP winBmp = CreateCompatibleBitmap(screen, ww, wh);
    HBITMAP oldWin = (HBITMAP)SelectObject(winDC, winBmp);

    // Render the whole window (incl. DirectComposition content) into winDC.
    BOOL ok = PrintWindow(root, winDC, PW_RENDERFULLCONTENT);

    HBITMAP dst = NULL;
    if (ok) {
        int rx = screenRegion.left - wr.left;   // region offset within the window
        int ry = screenRegion.top  - wr.top;
        HDC ddc = CreateCompatibleDC(screen);
        dst = CreateCompatibleBitmap(screen, rw, rh);
        HBITMAP oldDst = (HBITMAP)SelectObject(ddc, dst);
        BitBlt(ddc, 0, 0, rw, rh, winDC, rx, ry, SRCCOPY);
        SelectObject(ddc, oldDst);
        DeleteDC(ddc);
    }

    SelectObject(winDC, oldWin);
    DeleteObject(winBmp);
    DeleteDC(winDC);
    ReleaseDC(NULL, screen);
    return dst;
}

// True if a bitmap is essentially blank (almost entirely near-black) - the typical
// signature of PrintWindow failing on hardware-composited content. Used to fall
// back to a plain screen grab so the overlay never flashes a black box.
bool TmLooksBlank(HBITMAP bmp, int w, int h) {
    if (!bmp || w <= 0 || h <= 0) return true;

    BITMAPINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth       = w;
    bi.bmiHeader.biHeight      = -h;
    bi.bmiHeader.biPlanes      = 1;
    bi.bmiHeader.biBitCount    = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    size_t n = (size_t)w * h * 4;
    BYTE* p = (BYTE*)HeapAlloc(GetProcessHeap(), 0, n);
    if (!p) return false;   // can't tell - assume usable

    bool blank = false;
    HDC dc = GetDC(NULL);
    int r = GetDIBits(dc, bmp, 0, h, p, &bi, DIB_RGB_COLORS);
    ReleaseDC(NULL, dc);
    if (r) {
        long sampled = 0, nonblack = 0;
        const int step = 8;
        for (int y = 0; y < h; y += step) {
            BYTE* row = p + (size_t)y * w * 4;
            for (int x = 0; x < w; x += step) {
                BYTE* c = row + (size_t)x * 4;
                if (c[0] > 16 || c[1] > 16 || c[2] > 16) nonblack++;
                sampled++;
            }
        }
        if (sampled > 0) blank = (nonblack * 100 / sampled) < 2;
    }
    HeapFree(GetProcessHeap(), 0, p);
    return blank;
}

// Copy a sub-region of a bitmap into a new bitmap.
HBITMAP TmCrop(HBITMAP src, int x, int y, int w, int h) {
    if (!src || w <= 0 || h <= 0) return NULL;
    HDC screen = GetDC(NULL);
    HDC sdc = CreateCompatibleDC(screen);
    HDC ddc = CreateCompatibleDC(screen);
    HBITMAP dst = CreateCompatibleBitmap(screen, w, h);
    HBITMAP os = (HBITMAP)SelectObject(sdc, src);
    HBITMAP od = (HBITMAP)SelectObject(ddc, dst);
    BitBlt(ddc, 0, 0, w, h, sdc, x, y, SRCCOPY);
    SelectObject(sdc, os);
    SelectObject(ddc, od);
    DeleteDC(sdc);
    DeleteDC(ddc);
    ReleaseDC(NULL, screen);
    return dst;
}

// Screen-space origin and size of the window's client area.
bool TmClientInfo(HWND root, POINT* originScreen, int* clientW, int* clientH) {
    if (!root) return false;
    RECT cr;
    if (!GetClientRect(root, &cr)) return false;
    POINT o = { cr.left, cr.top };
    ClientToScreen(root, &o);
    *originScreen = o;
    *clientW = cr.right - cr.left;
    *clientH = cr.bottom - cr.top;
    return true;
}

// Fraction (0..1) of sampled pixels that differ noticeably between two same-size
// bitmaps. Used to tell a real view change (high) from a selection highlight or a
// live graph tick (low). Returns 1.0 (treat as changed) if it can't read the bits.
double TmChangedFraction(HBITMAP a, HBITMAP b, int w, int h) {
    if (!a || !b || w <= 0 || h <= 0) return 1.0;

    BITMAPINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth       = w;
    bi.bmiHeader.biHeight      = -h;   // top-down
    bi.bmiHeader.biPlanes      = 1;
    bi.bmiHeader.biBitCount    = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    size_t n = (size_t)w * h * 4;
    BYTE* pa = (BYTE*)HeapAlloc(GetProcessHeap(), 0, n);
    BYTE* pb = (BYTE*)HeapAlloc(GetProcessHeap(), 0, n);
    double frac = 1.0;
    if (pa && pb) {
        HDC dc = GetDC(NULL);
        int ra = GetDIBits(dc, a, 0, h, pa, &bi, DIB_RGB_COLORS);
        int rb = GetDIBits(dc, b, 0, h, pb, &bi, DIB_RGB_COLORS);
        ReleaseDC(NULL, dc);
        if (ra && rb) {
            long sampled = 0, diff = 0;
            const int step = 4;
            for (int y = 0; y < h; y += step) {
                BYTE* rowa = pa + (size_t)y * w * 4;
                BYTE* rowb = pb + (size_t)y * w * 4;
                for (int x = 0; x < w; x += step) {
                    BYTE* ca = rowa + (size_t)x * 4;
                    BYTE* cb = rowb + (size_t)x * 4;
                    int d0 = ca[0] - cb[0]; if (d0 < 0) d0 = -d0;
                    int d1 = ca[1] - cb[1]; if (d1 < 0) d1 = -d1;
                    int d2 = ca[2] - cb[2]; if (d2 < 0) d2 = -d2;
                    if (d0 > 24 || d1 > 24 || d2 > 24) diff++;
                    sampled++;
                }
            }
            if (sampled > 0) frac = (double)diff / (double)sampled;
        }
    }
    if (pa) HeapFree(GetProcessHeap(), 0, pa);
    if (pb) HeapFree(GetProcessHeap(), 0, pb);
    return frac;
}

// Using UI Automation, find the clicked navigation item and return the screen X of
// its right edge - i.e. where the content next to it begins. Walks a few ancestors
// so we land on the whole item/list, not an inner icon/label.
bool TmNavItemRight(IUIAutomation* uia, POINT pt, int clientLeft, int clientW,
                    UINT dpi, int* contentLeftScreen) {
    if (!uia) return false;

    IUIAutomationElement* el = NULL;
    if (FAILED(uia->ElementFromPoint(pt, &el)) || !el) return false;

    IUIAutomationTreeWalker* walker = NULL;
    uia->get_ControlViewWalker(&walker);

    const int leftMax  = (int)(clientW * 0.55);
    const int rightMax = (int)(clientW * 0.70);
    // UIA rects are in physical pixels; the limits below are tuned at 96 DPI.
    const int px8   = MulDiv(8,   dpi, 96);
    const int px24  = MulDiv(24,  dpi, 96);
    const int px360 = MulDiv(360, dpi, 96);

    int best = -1;
    IUIAutomationElement* cur = el;
    for (int i = 0; i < 6 && cur; ++i) {
        RECT r;
        if (SUCCEEDED(cur->get_CurrentBoundingRectangle(&r))) {
            int leftRel  = r.left  - clientLeft;
            int rightRel = r.right - clientLeft;
            int width    = rightRel - leftRel;
            if (leftRel >= -px8 && leftRel <= leftMax &&
                width >= px24 && width <= px360 &&
                rightRel >= px24 && rightRel <= rightMax &&
                rightRel > best) {
                best = rightRel;
            }
        }
        IUIAutomationElement* parent = NULL;
        if (walker) walker->GetParentElement(cur, &parent);
        cur->Release();
        cur = parent;
    }
    if (cur)    cur->Release();
    if (walker) walker->Release();

    if (best < 0) return false;
    *contentLeftScreen = clientLeft + best;
    return true;
}

// True if the window has moved or resized away from `orig` (or vanished). Our overlay
// is pinned to fixed screen coordinates, so once the window moves the overlay would
// become a detached ghost - the animation aborts the moment this returns true.
static bool TmWindowMoved(HWND root, const RECT& orig) {
    RECT cur;
    if (!root || !GetWindowRect(root, &cur)) return true;
    return cur.left   != orig.left  || cur.top    != orig.top ||
           cur.right  != orig.right || cur.bottom != orig.bottom;
}

// -------------------------------------------------------------------------
// Overlay management
//   Create  / Destroy  -> hook thread only (owns the window)
//   Animate            -> worker thread (UpdateLayeredWindow is thread-agnostic)
// -------------------------------------------------------------------------

// Destroy the live overlay and free its bitmap. MUST run on the hook thread.
void TmDestroyOverlay() {
    std::lock_guard<std::mutex> lock(g_overlayMutex);
    if (g_overlay.hwnd) {
        DestroyWindow(g_overlay.hwnd);
        g_overlay.hwnd = NULL;
    }
    if (g_overlay.frozenBmp) {
        DeleteObject(g_overlay.frozenBmp);
        g_overlay.frozenBmp = NULL;
    }
    g_overlay.rect    = RECT{0, 0, 0, 0};
    g_overlay.srcWnd  = NULL;
    g_overlay.srcRect = RECT{0, 0, 0, 0};
}

// Create the overlay showing the frozen old frame. Takes ownership of `frozen`.
// MUST run on the hook thread. Returns true on success.
bool TmCreateOverlay(HBITMAP frozen, const RECT& full, HWND srcWnd, const RECT& srcRect) {
    int W = full.right - full.left;
    int H = full.bottom - full.top;
    if (!frozen || W <= 0 || H <= 0) return false;

    // Clear any stale overlay first (shouldn't normally exist).
    TmDestroyOverlay();

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_TRANSPARENT,
        L"STATIC", NULL, WS_POPUP,
        full.left, full.top, W, H,
        NULL, NULL, NULL, NULL);
    if (!hwnd) return false;

    // Paint the frozen frame onto the layered window.
    HDC screen = GetDC(NULL);
    HDC src = CreateCompatibleDC(screen);
    HBITMAP os = (HBITMAP)SelectObject(src, frozen);

    POINT ptDst = { full.left, full.top };
    SIZE  sz    = { W, H };
    POINT ptSrc = { 0, 0 };
    BLENDFUNCTION bf;
    bf.BlendOp             = AC_SRC_OVER;
    bf.BlendFlags          = 0;
    bf.SourceConstantAlpha = 255;
    bf.AlphaFormat         = 0;
    UpdateLayeredWindow(hwnd, screen, &ptDst, &sz, src, &ptSrc, 0, &bf, ULW_ALPHA);

    SelectObject(src, os);
    DeleteDC(src);
    ReleaseDC(NULL, screen);

    ShowWindow(hwnd, SW_SHOWNOACTIVATE);

    std::lock_guard<std::mutex> lock(g_overlayMutex);
    g_overlay.hwnd      = hwnd;
    g_overlay.frozenBmp = frozen;
    g_overlay.rect      = full;
    g_overlay.srcWnd    = srcWnd;
    g_overlay.srcRect   = srcRect;
    return true;
}

// Hide the overlay if its source window has moved/resized. Runs on the hook thread
// (called for every mouse event). The animation worker can be blocked inside a
// cross-process UI Automation call while the user drags the window - Task Manager's
// UI thread is busy in its modal move loop and can't answer - so the worker can't
// tear the overlay down itself until the drag ends. Hiding it here kills the ghost
// immediately, regardless of the worker. We only hide (not destroy) so we never free
// the frozen bitmap out from under a worker that might still be animating.
void TmHideOverlayIfMoved() {
    std::lock_guard<std::mutex> lock(g_overlayMutex);
    if (!g_overlay.hwnd) return;
    if (TmWindowMoved(g_overlay.srcWnd, g_overlay.srcRect)) {
        ShowWindow(g_overlay.hwnd, SW_HIDE);
    }
}

// Ask the hook thread to destroy the overlay once the worker is finished.
void TmAnimationDone() {
    if (g_hookThreadId) {
        PostThreadMessageW(g_hookThreadId, WM_FADE_DESTROY_WND, 0, 0);
    }
}

// Crossfade the EXISTING overlay: the frozen full frame stays as the base, and the
// new content (offsetX..offsetX+cw, 0..ch within the overlay) is blended in from
// alpha 0 -> 255 over the animation duration. Runs on the worker thread.
void TmFadeAnimate(HBITMAP newBmp, int offsetX, int cw, int ch, HWND root, const RECT& winRect) {
    HWND    hwnd;
    HBITMAP frozen;
    RECT    rect;
    {
        std::lock_guard<std::mutex> lock(g_overlayMutex);
        hwnd   = g_overlay.hwnd;
        frozen = g_overlay.frozenBmp;
        rect   = g_overlay.rect;
    }
    if (!hwnd || !frozen || !newBmp) return;

    int W = rect.right - rect.left;
    int H = rect.bottom - rect.top;
    if (W <= 0 || H <= 0) return;

    HDC screen   = GetDC(NULL);
    HDC frozenDC = CreateCompatibleDC(screen);
    HDC newDC    = CreateCompatibleDC(screen);
    HDC canvasDC = CreateCompatibleDC(screen);
    HBITMAP canvas  = CreateCompatibleBitmap(screen, W, H);
    HBITMAP oldSelF = (HBITMAP)SelectObject(frozenDC, frozen);
    HBITMAP oldSelN = (HBITMAP)SelectObject(newDC,    newBmp);
    HBITMAP oldSelC = (HBITMAP)SelectObject(canvasDC, canvas);

    const double total = (double)g_durationMs.load(std::memory_order_relaxed);

    LARGE_INTEGER freq, start, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for (;;) {
        QueryPerformanceCounter(&now);
        double elapsed = (now.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
        BOOL last = (elapsed >= total);
        float p = last ? 1.0f : (float)(elapsed / total);
        float e = p * p * (3.0f - 2.0f * p);   // smoothstep ease in/out

        // Bail if the user moved/resized the window - a fixed-position overlay would
        // otherwise linger as a detached ghost during the move.
        if (TmWindowMoved(root, winRect)) break;

        // Base = frozen full frame. Then blend the new content region on top with
        // alpha tied to eased progress, so the nav stays frozen and only the
        // content crossfades.
        BitBlt(canvasDC, 0, 0, W, H, frozenDC, 0, 0, SRCCOPY);

        BLENDFUNCTION bfBlend;
        bfBlend.BlendOp             = AC_SRC_OVER;
        bfBlend.BlendFlags          = 0;
        bfBlend.SourceConstantAlpha = (BYTE)(e * 255.0f);
        bfBlend.AlphaFormat         = 0;
        AlphaBlend(canvasDC, offsetX, 0, cw, ch, newDC, 0, 0, cw, ch, bfBlend);

        POINT ptDst = { rect.left, rect.top };
        SIZE  sz    = { W, H };
        POINT ptSrc = { 0, 0 };
        BLENDFUNCTION bf;
        bf.BlendOp             = AC_SRC_OVER;
        bf.BlendFlags          = 0;
        bf.SourceConstantAlpha = 255;
        bf.AlphaFormat         = 0;
        UpdateLayeredWindow(hwnd, screen, &ptDst, &sz, canvasDC, &ptSrc, 0, &bf, ULW_ALPHA);

        if (last) break;
        DwmFlush();
    }

    SelectObject(canvasDC, oldSelC);
    SelectObject(newDC,    oldSelN);
    SelectObject(frozenDC, oldSelF);
    DeleteObject(canvas);
    DeleteDC(canvasDC);
    DeleteDC(newDC);
    DeleteDC(frozenDC);
    ReleaseDC(NULL, screen);
}

// Slide the content region of the EXISTING overlay: the frozen full frame is the
// base (keeps the left nav frozen), and within the content sub-rect the old content
// slides out while the new content slides in. Drawing is clipped to the content rect
// so the sliding bitmaps never spill over the nav. Runs on the worker thread.
void TmSlideAnimate(HBITMAP newContent, HBITMAP oldContent, int offsetX, int cw, int ch, HWND root, const RECT& winRect) {
    HWND    hwnd;
    HBITMAP frozen;
    RECT    rect;
    {
        std::lock_guard<std::mutex> lock(g_overlayMutex);
        hwnd   = g_overlay.hwnd;
        frozen = g_overlay.frozenBmp;
        rect   = g_overlay.rect;
    }
    if (!hwnd || !frozen || !newContent || !oldContent) return;

    int W = rect.right - rect.left;
    int H = rect.bottom - rect.top;
    if (W <= 0 || H <= 0) return;

    const bool vertical = g_slideVertical.load(std::memory_order_relaxed);
    const int  span     = vertical ? ch : cw;

    HDC screen   = GetDC(NULL);
    HDC frozenDC = CreateCompatibleDC(screen);
    HDC oldDC    = CreateCompatibleDC(screen);
    HDC newDC    = CreateCompatibleDC(screen);
    HDC canvasDC = CreateCompatibleDC(screen);
    HBITMAP canvas  = CreateCompatibleBitmap(screen, W, H);
    HBITMAP oldSelF = (HBITMAP)SelectObject(frozenDC, frozen);
    HBITMAP oldSelO = (HBITMAP)SelectObject(oldDC,    oldContent);
    HBITMAP oldSelN = (HBITMAP)SelectObject(newDC,    newContent);
    HBITMAP oldSelC = (HBITMAP)SelectObject(canvasDC, canvas);

    const double total = (double)g_durationMs.load(std::memory_order_relaxed);

    LARGE_INTEGER freq, start, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for (;;) {
        QueryPerformanceCounter(&now);
        double elapsed = (now.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
        BOOL last = (elapsed >= total);
        float p = last ? 1.0f : (float)(elapsed / total);
        float e = p * p * (3.0f - 2.0f * p);   // smoothstep ease in/out

        // Bail if the user moved/resized the window (see TmFadeAnimate).
        if (TmWindowMoved(root, winRect)) break;

        int oldOff = (int)(-e * span);
        int newOff = (int)((1.0f - e) * span);
        int ox = vertical ? 0 : oldOff;
        int oy = vertical ? oldOff : 0;
        int nx = vertical ? 0 : newOff;
        int ny = vertical ? newOff : 0;

        // Base = frozen full frame (keeps the nav frozen). Then draw the sliding old
        // and new content, clipped to the content rect so nothing paints the nav.
        BitBlt(canvasDC, 0, 0, W, H, frozenDC, 0, 0, SRCCOPY);

        HRGN clip = CreateRectRgn(offsetX, 0, offsetX + cw, ch);
        SelectClipRgn(canvasDC, clip);
        BitBlt(canvasDC, offsetX + ox, oy, cw, ch, oldDC, 0, 0, SRCCOPY);
        BitBlt(canvasDC, offsetX + nx, ny, cw, ch, newDC, 0, 0, SRCCOPY);
        SelectClipRgn(canvasDC, NULL);
        DeleteObject(clip);

        POINT ptDst = { rect.left, rect.top };
        SIZE  sz    = { W, H };
        POINT ptSrc = { 0, 0 };
        BLENDFUNCTION bf;
        bf.BlendOp             = AC_SRC_OVER;
        bf.BlendFlags          = 0;
        bf.SourceConstantAlpha = 255;
        bf.AlphaFormat         = 0;
        UpdateLayeredWindow(hwnd, screen, &ptDst, &sz, canvasDC, &ptSrc, 0, &bf, ULW_ALPHA);

        if (last) break;
        DwmFlush();
    }

    SelectObject(canvasDC, oldSelC);
    SelectObject(newDC,    oldSelN);
    SelectObject(oldDC,    oldSelO);
    SelectObject(frozenDC, oldSelF);
    DeleteObject(canvas);
    DeleteDC(canvasDC);
    DeleteDC(newDC);
    DeleteDC(oldDC);
    DeleteDC(frozenDC);
    ReleaseDC(NULL, screen);
}

// -------------------------------------------------------------------------
// Worker: wait for the new view to render, locate the content edge via UI
// Automation, capture the new view, play the chosen animation on the existing
// overlay (only if the content actually changed), then ask the hook thread to
// destroy the overlay.
// -------------------------------------------------------------------------
DWORD WINAPI TmWorkerThread(LPVOID lpParam) {
    TabAnimData* d = (TabAnimData*)lpParam;

    Sleep(g_captureDelay.load(std::memory_order_relaxed));

    // If the user started moving/resizing the window during the capture delay, our
    // fixed-position overlay would show as a detached ghost - abort and destroy it.
    if (TmWindowMoved(d->root, d->winRect)) {
        TmAnimationDone();
        delete d;
        g_inProgress.store(false, std::memory_order_relaxed);
        return 0;
    }

    int clientW     = d->fullRect.right - d->fullRect.left;
    int contentLeft = d->fullRect.left;
    bool located    = false;

    HRESULT hrCo = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    IUIAutomation* uia = NULL;
    if (SUCCEEDED(CoCreateInstance(kCLSID_CUIAutomation, NULL, CLSCTX_INPROC_SERVER,
                                   kIID_IUIAutomation, (void**)&uia)) && uia) {
        UINT dpi = GetDpiForWindow(d->root);
        if (!dpi) dpi = 96;
        located = TmNavItemRight(uia, d->clickPt, d->fullRect.left, clientW, dpi, &contentLeft);
        uia->Release();
    }
    if (SUCCEEDED(hrCo)) CoUninitialize();

    if (located) {
        int offsetX = contentLeft - d->fullRect.left;
        RECT content = { contentLeft, d->fullRect.top, d->fullRect.right, d->fullRect.bottom };
        int cw = content.right  - content.left;
        int ch = content.bottom - content.top;

        if (offsetX >= 0 && cw >= 80 && ch >= 80) {
            // Crop the OLD content out of the overlay's frozen full frame.
            HBITMAP oldCrop = NULL;
            {
                std::lock_guard<std::mutex> lock(g_overlayMutex);
                if (g_overlay.frozenBmp) {
                    oldCrop = TmCrop(g_overlay.frozenBmp, offsetX, 0, cw, ch);
                }
            }

            if (oldCrop) {
                // Re-capture the new view until it has actually rendered. Some tabs
                // (Disk / Network / GPU) draw their first frame noticeably later than
                // CPU / Memory, so a single fixed delay can miss them. Poll until the
                // content visibly changes (or give up).
                const double readyFrac = 0.06;
                const double userThr   = g_changeThreshold.load(std::memory_order_relaxed) / 100.0;
                HBITMAP newBmp = NULL;
                double  frac   = 0.0;
                for (int attempt = 0; attempt < 6; ++attempt) {
                    // Capture from the window itself, not the screen - the overlay
                    // sits on top of `content`, so a screen BitBlt would just read
                    // back our own frozen old frame and the animation would never play.
                    HBITMAP cap = TmCaptureWindowRegion(d->root, content);
                    if (!cap) break;
                    if (newBmp) DeleteObject(newBmp);
                    newBmp = cap;
                    frac = TmChangedFraction(oldCrop, newBmp, cw, ch);
                    if (frac >= readyFrac) break;  // new view has rendered
                    Sleep(35);
                }

                if (newBmp && frac >= userThr && !TmWindowMoved(d->root, d->winRect)) {
                    if (d->mode == ANIM_SLIDE) {
                        TmSlideAnimate(newBmp, oldCrop, offsetX, cw, ch, d->root, d->winRect);
                    } else {
                        TmFadeAnimate(newBmp, offsetX, cw, ch, d->root, d->winRect);
                    }
                }
                if (newBmp) DeleteObject(newBmp);
                DeleteObject(oldCrop);
            }
        }
    }

    // Hand the overlay back to the hook thread for destruction.
    TmAnimationDone();

    delete d;
    g_inProgress.store(false, std::memory_order_relaxed);
    return 0;
}

// -------------------------------------------------------------------------
// Click detection (low-level mouse hook)
//   mouse-down -> capture old frame + create overlay immediately
//   mouse-up   -> launch the worker that animates and destroys it
// -------------------------------------------------------------------------
void TmOnClick(WPARAM msg, POINT pt) {
    // ------------------------------------------------------------------
    // FINISH: launch the worker.
    // ------------------------------------------------------------------
    if (msg == WM_LBUTTONUP) {
        int   mode;
        HWND  root;
        POINT click;
        RECT  full;
        RECT  win;
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            if (!g_armed) return;
            g_armed = false;
            mode  = g_pendingMode;
            root  = g_pendingRoot;
            click = g_pendingClick;
            full  = g_pendingRect;
            win   = g_pendingWin;
        }

        // An overlay was created at mouse-down. If a previous cycle is somehow still
        // running, tear this overlay down and bail.
        if (g_inProgress.load(std::memory_order_relaxed)) {
            TmDestroyOverlay();
            return;
        }

        g_inProgress.store(true, std::memory_order_relaxed);

        TabAnimData* d = new TabAnimData();
        d->root     = root;
        d->clickPt  = click;
        d->fullRect = full;
        d->winRect  = win;
        d->mode     = mode;

        HANDLE h = CreateThread(NULL, 0, TmWorkerThread, d, 0, NULL);
        if (h) {
            CloseHandle(h);
        } else {
            delete d;
            TmDestroyOverlay();   // we're on the hook thread - safe
            g_inProgress.store(false, std::memory_order_relaxed);
        }
        return;
    }

    // ------------------------------------------------------------------
    // START: capture the current view and show the overlay immediately, before the
    // click changes the tab, if the click is plausibly in a left nav column.
    // ------------------------------------------------------------------
    if (msg != WM_LBUTTONDOWN) return;
    if (g_inProgress.load(std::memory_order_relaxed)) return;

    HWND under = WindowFromPoint(pt);
    HWND root  = under ? GetAncestor(under, GA_ROOT) : NULL;
    if (!root) return;

    DWORD pid = 0;
    GetWindowThreadProcessId(root, &pid);
    if (pid != GetCurrentProcessId()) return;

    POINT origin;
    int cw, ch;
    if (!TmClientInfo(root, &origin, &cw, &ch)) return;
    int relX = pt.x - origin.x;
    int relY = pt.y - origin.y;

    // The inset setting is at 100% scaling; hook coordinates are physical pixels.
    UINT dpi = GetDpiForWindow(root);
    if (!dpi) dpi = 96;
    int topI = MulDiv(g_topInset.load(std::memory_order_relaxed), dpi, 96);
    // Below the command bar, and in the left portion where the nav / sub-nav can be.
    if (relX < 0 || relY < topI || relX > (cw * 3) / 5 || relY >= ch) return;

    RECT full;
    full.left   = origin.x;
    full.top    = origin.y + topI;
    full.right  = origin.x + cw;
    full.bottom = origin.y + ch;
    if ((full.right - full.left) < 80 || (full.bottom - full.top) < 80) return;

    // Capture the old frame the same way the worker captures the new one
    // (PrintWindow), so the change-detection comparison is apples-to-apples. If
    // PrintWindow isn't usable here (null or a blank/black frame), fall back to a
    // plain screen grab for the displayed frame - the animation then simply no-ops
    // instead of showing a black overlay.
    int fullW = full.right - full.left;
    int fullH = full.bottom - full.top;
    HBITMAP oldBmp = TmCaptureWindowRegion(root, full);
    if (!oldBmp || TmLooksBlank(oldBmp, fullW, fullH)) {
        if (oldBmp) DeleteObject(oldBmp);
        oldBmp = TmCaptureRect(full);
    }
    if (!oldBmp) return;

    RECT winRect = {0, 0, 0, 0};
    GetWindowRect(root, &winRect);

    // Show the frozen old frame immediately so the tab switches invisibly. The
    // overlay takes ownership of oldBmp (freed in TmDestroyOverlay).
    if (!TmCreateOverlay(oldBmp, full, root, winRect)) {
        DeleteObject(oldBmp);
        return;
    }

    std::lock_guard<std::mutex> lock(g_mutex);
    g_pendingMode  = g_animType.load(std::memory_order_relaxed);
    g_pendingRoot  = root;
    g_pendingClick = pt;
    g_pendingRect  = full;
    g_pendingWin   = winRect;
    g_armed        = true;
}

LRESULT CALLBACK TmMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        // Every mouse event (incl. moves during a title-bar drag): if a live overlay's
        // window has moved, hide it now so it doesn't linger as a detached ghost.
        TmHideOverlayIfMoved();

        if (wParam == WM_LBUTTONDOWN || wParam == WM_LBUTTONUP) {
            MSLLHOOKSTRUCT* ms = (MSLLHOOKSTRUCT*)lParam;
            TmOnClick(wParam, ms->pt);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Dedicated thread owning the hook and pumping messages (required for LL hooks).
// It also owns the overlay window, so it is the only place the overlay is destroyed.
DWORD WINAPI TmHookThread(LPVOID lpParam) {
    g_mouseHook = SetWindowsHookExW(WH_MOUSE_LL, TmMouseProc, GetModuleHandleW(NULL), 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_FADE_DESTROY_WND) {
            TmDestroyOverlay();
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Destroy any surviving overlay on its creating thread before we exit.
    TmDestroyOverlay();

    if (g_mouseHook) {
        UnhookWindowsHookEx(g_mouseHook);
        g_mouseHook = NULL;
    }
    return 0;
}

// -------------------------------------------------------------------------
// Windhawk entry points
// -------------------------------------------------------------------------
BOOL ModInit() {
    TmLoadSettings();
    g_hookThread = CreateThread(NULL, 0, TmHookThread, NULL, 0, &g_hookThreadId);
    return TRUE;
}

void ModSettingsChanged() {
    TmLoadSettings();
}

void ModUninit() {
    if (g_hookThread) {
        if (g_hookThreadId) {
            PostThreadMessageW(g_hookThreadId, WM_QUIT, 0, 0);
        }
        WaitForSingleObject(g_hookThread, 2000);
        CloseHandle(g_hookThread);
        g_hookThread   = NULL;
        g_hookThreadId = 0;
    }

    // The hook thread destroys the overlay on exit; this frees anything left.
    TmDestroyOverlay();
}
}  // namespace f_tabslide


// ===========================================================================
// taskmgr-taller-tab
// ===========================================================================
namespace f_tallertab {
using CreateWindowExW_t = decltype(&CreateWindowExW);
CreateWindowExW_t CreateWindowExW_Original;
HWND WINAPI CreateWindowExW_Hook(
    DWORD dwExStyle,
    LPCWSTR lpClassName,
    LPCWSTR lpWindowName,
    DWORD dwStyle,
    int x, int y,
    int nWidth, int nHeight,
    HWND hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam
)
{
    HWND hWnd = CreateWindowExW_Original(
        dwExStyle, lpClassName, lpWindowName, dwStyle,
        x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam
    );

    BOOL bTextualClassName = ((ULONG_PTR)lpClassName & ~(ULONG_PTR)0xffff) != 0;
    //Ref: windhawk-mods/mods/explorer-name-windows.wh.cpp

    if (bTextualClassName && _wcsicmp(lpClassName, L"SysTabControl32") == 0) {
        //ensuring target control is a tab control "SysTabControl32"
        TabCtrl_SetItemSize(hWnd, 100, 37); // width= 100，height= 37
    }

    return hWnd;
}

template<typename ProtoType>
BOOL Wh_SetFunctionHookT(ProtoType targetFunction, ProtoType hookFunction, ProtoType* originalFunction)
{
    return Wh_SetFunctionHook((void*)targetFunction, (void*)hookFunction, (void**)originalFunction);
}

BOOL ModInit()
{
    // Wh_Log(L"Init " WH_MOD_ID L" version " WH_MOD_VERSION);

    Wh_SetFunctionHookT(CreateWindowExW, CreateWindowExW_Hook, &CreateWindowExW_Original);

    return TRUE;
}
}  // namespace f_tallertab


// ===========================================================================
// task-manager-tail
// ===========================================================================
namespace f_tail {
// Custom Message to wake up the thread
#define WM_TRIGGER_CHECK (WM_USER + 1)

// Windows version enumeration
enum class WinVersion {
    Win10,
    Win11,
    Win11_24H2
};

struct UIAItem {
    IUIAutomationElement* element;
    BSTR name;
};

struct Settings {
    std::wstring targetName;
    std::wstring targetClass;
    int moveDelay;
    int debounceTime;
} g_settings;

// Global thread control
HANDLE g_hThread = NULL;
DWORD g_dwThreadId = 0;
volatile bool g_stopThread = false;
DWORD g_lastAttemptTime = 0;
WinVersion g_winVersion = WinVersion::Win11;

// Forward declarations
void CheckAndMoveWin10(IUIAutomation* pAutomation);

//////////////////////////////////////////////////////////////////////////////
// Windows 10: UIA Structure Changed Event Handler
// This class receives events ONLY when the taskbar structure changes
//////////////////////////////////////////////////////////////////////////////

class TaskbarStructureChangedHandler : public IUIAutomationStructureChangedEventHandler {
private:
    LONG m_refCount;
    IUIAutomation* m_pAutomation;

public:
    TaskbarStructureChangedHandler(IUIAutomation* pAutomation)
        : m_refCount(1), m_pAutomation(pAutomation) {
        if (m_pAutomation) m_pAutomation->AddRef();
    }

    ~TaskbarStructureChangedHandler() {
        if (m_pAutomation) m_pAutomation->Release();
    }

    // IUnknown methods
    ULONG STDMETHODCALLTYPE AddRef() override {
        return InterlockedIncrement(&m_refCount);
    }

    ULONG STDMETHODCALLTYPE Release() override {
        LONG count = InterlockedDecrement(&m_refCount);
        if (count == 0) {
            delete this;
        }
        return count;
    }

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) override {
        if (riid == IID_IUnknown || riid == IID_IUIAutomationStructureChangedEventHandler) {
            *ppv = static_cast<IUIAutomationStructureChangedEventHandler*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    // IUIAutomationStructureChangedEventHandler method
    HRESULT STDMETHODCALLTYPE HandleStructureChangedEvent(
        IUIAutomationElement* pSender,
        StructureChangeType changeType,
        SAFEARRAY* pRuntimeId) override {

        // Only care about children added/removed (new buttons appearing/disappearing)
        if (changeType == StructureChangeType_ChildAdded ||
            changeType == StructureChangeType_ChildRemoved ||
            changeType == StructureChangeType_ChildrenReordered) {

            Wh_Log(L"Win10: Taskbar structure changed (type=%d), triggering check", changeType);

            // Post to our thread to do the actual check (avoid blocking the event)
            if (g_dwThreadId != 0) {
                PostThreadMessage(g_dwThreadId, WM_TRIGGER_CHECK, 0, 0);
            }
        }
        return S_OK;
    }
};

// Global handler reference for cleanup
TaskbarStructureChangedHandler* g_pWin10Handler = NULL;
IUIAutomationElement* g_pWin10TaskListElement = NULL;

// Detect Windows version by checking explorer.exe file version
WinVersion DetectWindowsVersion() {
    WCHAR sysDir[MAX_PATH];
    if (!GetSystemDirectoryW(sysDir, MAX_PATH)) {
        Wh_Log(L"GetSystemDirectory failed, assuming Win11");
        return WinVersion::Win11;
    }

    WCHAR explorerPath[MAX_PATH];
    swprintf_s(explorerPath, L"%s\\..\\explorer.exe", sysDir);

    DWORD dummy;
    DWORD size = GetFileVersionInfoSizeW(explorerPath, &dummy);
    if (!size) {
        Wh_Log(L"GetFileVersionInfoSize failed, assuming Win11");
        return WinVersion::Win11;
    }

    std::vector<BYTE> data(size);
    if (!GetFileVersionInfoW(explorerPath, 0, size, data.data())) {
        Wh_Log(L"GetFileVersionInfo failed, assuming Win11");
        return WinVersion::Win11;
    }

    VS_FIXEDFILEINFO* info = NULL;
    UINT len = 0;
    if (!VerQueryValueW(data.data(), L"\\", (void**)&info, &len) || !info) {
        Wh_Log(L"VerQueryValue failed, assuming Win11");
        return WinVersion::Win11;
    }

    WORD major = HIWORD(info->dwFileVersionMS);
    WORD minor = LOWORD(info->dwFileVersionMS);
    WORD build = HIWORD(info->dwFileVersionLS);

    Wh_Log(L"Detected Windows version: %d.%d.%d", major, minor, build);

    if (build < 22000) {
        Wh_Log(L"Running on Windows 10");
        return WinVersion::Win10;
    } else if (build < 26100) {
        Wh_Log(L"Running on Windows 11");
        return WinVersion::Win11;
    } else {
        Wh_Log(L"Running on Windows 11 24H2+");
        return WinVersion::Win11_24H2;
    }
}

void LoadSettings() {
    PCWSTR target = Wh_GetStringSetting(L"targetName");
    g_settings.targetName = target ? target : L"Task Manager";
    Wh_FreeStringSetting(target);

    PCWSTR cls = Wh_GetStringSetting(L"targetClass");
    g_settings.targetClass = cls ? cls : L"TaskManagerWindow";
    Wh_FreeStringSetting(cls);

    g_settings.moveDelay = Wh_GetIntSetting(L"moveDelay");
    if (g_settings.moveDelay < 0) g_settings.moveDelay = 0;

    g_settings.debounceTime = Wh_GetIntSetting(L"debounceTime");
    if (g_settings.debounceTime < 50) g_settings.debounceTime = 50;
}

// --- WinEvent Hook Callback (used for Win11) ---
void CALLBACK WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd,
                           LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
    if (idObject == OBJID_WINDOW && idChild == CHILDID_SELF && g_dwThreadId != 0) {
        PostThreadMessage(g_dwThreadId, WM_TRIGGER_CHECK, 0, 0);
    }
}

void CycleTaskbarTab(HWND hwnd) {
    Wh_Log(L"Cycling Taskbar Tab for HWND %p via ITaskbarList", hwnd);

    ITaskbarList* pTaskbarList = NULL;
    HRESULT hr = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList, (void**)&pTaskbarList);

    if (SUCCEEDED(hr) && pTaskbarList) {
        hr = pTaskbarList->HrInit();
        if (SUCCEEDED(hr)) {
            pTaskbarList->DeleteTab(hwnd);
            Sleep(200);
            pTaskbarList->AddTab(hwnd);
            Sleep(50);
            pTaskbarList->ActivateTab(hwnd);
        }
        pTaskbarList->Release();
    }
}

// Find the MSTaskListWClass element for Windows 10
IUIAutomationElement* FindWin10TaskListElement(IUIAutomation* pAutomation) {
    HWND hTray = FindWindowW(L"Shell_TrayWnd", NULL);
    if (!hTray) return NULL;

    HWND hRebar = FindWindowExW(hTray, NULL, L"ReBarWindow32", NULL);
    if (!hRebar) return NULL;

    HWND hTaskSw = FindWindowExW(hRebar, NULL, L"MSTaskSwWClass", NULL);
    if (!hTaskSw) return NULL;

    HWND hTaskList = FindWindowExW(hTaskSw, NULL, L"MSTaskListWClass", NULL);
    if (!hTaskList) return NULL;

    IUIAutomationElement* pElement = NULL;
    pAutomation->ElementFromHandle(hTaskList, &pElement);
    return pElement;
}

// Windows 10 specific taskbar check
void CheckAndMoveWin10(IUIAutomation* pAutomation) {
    HWND hTargetWnd = FindWindowW(g_settings.targetClass.c_str(), NULL);
    if (!hTargetWnd) return;

    HWND hTray = FindWindowW(L"Shell_TrayWnd", NULL);
    if (!hTray) return;

    HWND hRebar = FindWindowExW(hTray, NULL, L"ReBarWindow32", NULL);
    if (!hRebar) return;

    HWND hTaskSw = FindWindowExW(hRebar, NULL, L"MSTaskSwWClass", NULL);
    if (!hTaskSw) return;

    HWND hTaskList = FindWindowExW(hTaskSw, NULL, L"MSTaskListWClass", NULL);
    if (!hTaskList) return;

    IUIAutomationElement* pRoot = NULL;
    HRESULT hr = pAutomation->ElementFromHandle(hTaskList, &pRoot);
    if (FAILED(hr) || !pRoot) return;

    IUIAutomationCondition* pTrueCondition = NULL;
    pAutomation->CreateTrueCondition(&pTrueCondition);

    IUIAutomationElementArray* pChildren = NULL;
    pRoot->FindAll(TreeScope_Children, pTrueCondition, &pChildren);

    if (pChildren) {
        int count = 0;
        pChildren->get_Length(&count);

        std::vector<UIAItem> buttons;
        int targetIndex = -1;

        for (int i = 0; i < count; i++) {
            IUIAutomationElement* pChild = NULL;
            pChildren->GetElement(i, &pChild);
            if (pChild) {
                CONTROLTYPEID controlType;
                pChild->get_CurrentControlType(&controlType);

                if (controlType == UIA_ButtonControlTypeId) {
                    UIAItem item;
                    item.element = pChild;
                    pChild->AddRef();
                    pChild->get_CurrentName(&item.name);

                    buttons.push_back(item);

                    if (item.name && wcsstr(item.name, g_settings.targetName.c_str())) {
                        targetIndex = (int)buttons.size() - 1;
                    }
                }
                pChild->Release();
            }
        }

        // Only act if found and NOT already at the end
        if (targetIndex != -1 && static_cast<size_t>(targetIndex) < buttons.size() - 1) {
            if (GetTickCount() - g_lastAttemptTime > 1000) {
                Wh_Log(L"Win10: Target at index %d (of %d). Moving to end...", targetIndex, (int)buttons.size());
                if (hTargetWnd && IsWindow(hTargetWnd)) {
                    if (g_settings.moveDelay > 0) Sleep(g_settings.moveDelay);
                    CycleTaskbarTab(hTargetWnd);
                    g_lastAttemptTime = GetTickCount();
                }
            }
        }

        for (auto& b : buttons) {
            if (b.name) SysFreeString(b.name);
            if (b.element) b.element->Release();
        }
        pChildren->Release();
    }

    if (pTrueCondition) pTrueCondition->Release();
    pRoot->Release();
}

// Windows 11 specific taskbar check (original implementation)
void CheckAndMoveWin11(IUIAutomation* pAutomation) {
    HWND hTargetWnd = FindWindowW(g_settings.targetClass.c_str(), NULL);
    if (!hTargetWnd) return;

    HWND hTray = FindWindowW(L"Shell_TrayWnd", NULL);
    if (!hTray) return;

    HWND hChild = GetWindow(hTray, GW_CHILD);
    while (hChild) {
        wchar_t text[256] = {0};
        GetWindowTextW(hChild, text, 255);

        if (wcsstr(text, L"DesktopWindowXamlSource")) {
            IUIAutomationElement* pRoot = NULL;
            HRESULT hr = pAutomation->ElementFromHandle(hChild, &pRoot);
            if (SUCCEEDED(hr) && pRoot) {
                IUIAutomationCondition* pTrueCondition = NULL;
                pAutomation->CreateTrueCondition(&pTrueCondition);

                IUIAutomationElementArray* pChildren = NULL;
                pRoot->FindAll(TreeScope_Descendants, pTrueCondition, &pChildren);

                if (pChildren) {
                    int count = 0;
                    pChildren->get_Length(&count);

                    std::vector<UIAItem> buttons;
                    int targetIndex = -1;

                    for (int i = 0; i < count; i++) {
                        IUIAutomationElement* pChild = NULL;
                        pChildren->GetElement(i, &pChild);
                        if (pChild) {
                            BSTR cls = NULL;
                            pChild->get_CurrentClassName(&cls);

                            if (cls && wcsstr(cls, L"TaskListButtonAutomationPeer")) {
                                UIAItem item;
                                item.element = pChild;
                                pChild->AddRef();
                                pChild->get_CurrentName(&item.name);

                                buttons.push_back(item);

                                if (item.name && wcsstr(item.name, g_settings.targetName.c_str())) {
                                    targetIndex = (int)buttons.size() - 1;
                                }
                            }
                            if (cls) SysFreeString(cls);
                            pChild->Release();
                        }
                    }

                    if (targetIndex != -1 && static_cast<size_t>(targetIndex) < buttons.size() - 1) {
                        if (GetTickCount() - g_lastAttemptTime > 1000) {
                            Wh_Log(L"Target found at index %d (of %d). Moving...", targetIndex, (int)buttons.size());
                            if (hTargetWnd && IsWindow(hTargetWnd)) {
                                if (g_settings.moveDelay > 0) Sleep(g_settings.moveDelay);
                                CycleTaskbarTab(hTargetWnd);
                                g_lastAttemptTime = GetTickCount();
                            }
                        }
                    }

                    for (auto& b : buttons) {
                        if (b.name) SysFreeString(b.name);
                        if (b.element) b.element->Release();
                    }
                    pChildren->Release();
                }
                pTrueCondition->Release();
                pRoot->Release();
            }
        }
        hChild = GetWindow(hChild, GW_HWNDNEXT);
    }
}

void CheckAndMove(IUIAutomation* pAutomation) {
    if (g_winVersion == WinVersion::Win10) {
        CheckAndMoveWin10(pAutomation);
    } else {
        CheckAndMoveWin11(pAutomation);
    }
}

//////////////////////////////////////////////////////////////////////////////
// Background Thread - Different event sources for Win10 vs Win11
//////////////////////////////////////////////////////////////////////////////

DWORD WINAPI BackgroundThread(LPVOID) {
    Wh_Log(L"Task Manager Tail Thread Started");
    g_dwThreadId = GetCurrentThreadId();

    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) return 1;

    IUIAutomation* pAutomation = NULL;
    hr = CoCreateInstance(CLSID_CUIAutomation, NULL, CLSCTX_INPROC_SERVER, IID_IUIAutomation, (void**)&pAutomation);

    if (FAILED(hr) || !pAutomation) {
        Wh_Log(L"Failed to create UI Automation instance");
        CoUninitialize();
        return 1;
    }

    HWINEVENTHOOK hWinEventHook = NULL;

    if (g_winVersion == WinVersion::Win10) {
        // Windows 10: Use UIA StructureChangedEventHandler on the taskbar
        Wh_Log(L"Win10: Setting up UIA StructureChangedEventHandler...");

        g_pWin10TaskListElement = FindWin10TaskListElement(pAutomation);
        if (g_pWin10TaskListElement) {
            g_pWin10Handler = new TaskbarStructureChangedHandler(pAutomation);

            hr = pAutomation->AddStructureChangedEventHandler(
                g_pWin10TaskListElement,
                TreeScope_Subtree,
                NULL,  // No cache request
                g_pWin10Handler
            );

            if (SUCCEEDED(hr)) {
                Wh_Log(L"Win10: UIA StructureChangedEventHandler registered successfully!");
            } else {
                Wh_Log(L"Win10: Failed to register UIA handler (hr=0x%08X), falling back to WinEventHook", hr);
                // Fall back to WinEventHook
                g_pWin10Handler->Release();
                g_pWin10Handler = NULL;
                g_pWin10TaskListElement->Release();
                g_pWin10TaskListElement = NULL;

                hWinEventHook = SetWinEventHook(
                    EVENT_OBJECT_CREATE, EVENT_OBJECT_HIDE,
                    NULL, WinEventProc, 0, 0,
                    WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
                );
            }
        } else {
            Wh_Log(L"Win10: Could not find taskbar element, falling back to WinEventHook");
            hWinEventHook = SetWinEventHook(
                EVENT_OBJECT_CREATE, EVENT_OBJECT_HIDE,
                NULL, WinEventProc, 0, 0,
                WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
            );
        }
    } else {
        // Windows 11: Use WinEventHook (works well there)
        hWinEventHook = SetWinEventHook(
            EVENT_OBJECT_CREATE, EVENT_OBJECT_HIDE,
            NULL, WinEventProc, 0, 0,
            WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
        );

        if (hWinEventHook) {
            Wh_Log(L"Win11: WinEventHook Registered. Waiting for events...");
        }
    }

    // Message loop with debouncing
    MSG msg;
    UINT_PTR debounceTimer = 0;

    // Do an initial check
    CheckAndMove(pAutomation);

    while (!g_stopThread && GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_TRIGGER_CHECK) {
            if (debounceTimer) KillTimer(NULL, debounceTimer);
            debounceTimer = SetTimer(NULL, 0, g_settings.debounceTime, NULL);
        }
        else if (msg.message == WM_TIMER && msg.wParam == debounceTimer) {
            KillTimer(NULL, debounceTimer);
            debounceTimer = 0;
            CheckAndMove(pAutomation);
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup
    if (hWinEventHook) {
        UnhookWinEvent(hWinEventHook);
    }

    if (g_pWin10Handler) {
        pAutomation->RemoveStructureChangedEventHandler(g_pWin10TaskListElement, g_pWin10Handler);
        g_pWin10Handler->Release();
        g_pWin10Handler = NULL;
    }

    if (g_pWin10TaskListElement) {
        g_pWin10TaskListElement->Release();
        g_pWin10TaskListElement = NULL;
    }

    pAutomation->Release();
    CoUninitialize();
    return 0;
}

bool ToolInit() {
    g_winVersion = DetectWindowsVersion();
    LoadSettings();
    g_stopThread = false;
    g_hThread = CreateThread(NULL, 0, BackgroundThread, NULL, 0, NULL);
    return g_hThread != NULL;
}

void ToolUninit() {
    g_stopThread = true;
    if (g_dwThreadId) PostThreadMessage(g_dwThreadId, WM_QUIT, 0, 0);
    if (g_hThread) {
        WaitForSingleObject(g_hThread, 3000);
        CloseHandle(g_hThread);
    }
}

void ToolSettingsChanged() {
    LoadSettings();
}
}  // namespace f_tail


// ---------------------------------------------------------------------------
// Tool side: runs in Windhawk's own helper process. Tray icon, shortcut,
// settings window and the taskbar button keeper. The Task Manager changes run
// inside Task Manager (see the end of this file).
// ---------------------------------------------------------------------------

BOOL WhTool_ModInit() {
    SeamlessMenuSkin::Init();
    g_instanceMutex = CreateMutexW(nullptr, FALSE, L"Global\\SeamlessTaskManager");
    if (g_instanceMutex && GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(g_instanceMutex);
        g_instanceMutex = nullptr;
        ExitProcess(0);
    }

    if (HANDLE boxThread = CreateThread(nullptr, 0, FalseFailureBoxThreadProc, nullptr, 0, nullptr)) {
        CloseHandle(boxThread);
    }

    g_module = GetModuleHandleW(nullptr);
    g_enabled.store(Wh_GetIntValue(L"enabled", 1) != 0);
    ReadSettings();

    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, &g_uiThreadId);
    if (g_uiThread && g_uiReady) WaitForSingleObject(g_uiReady, 10000);
    if (g_uiReady) CloseHandle(g_uiReady);
    g_uiReady = nullptr;
    if (!g_uiThread) {
        Wh_Log(L"Couldn't start: %u", GetLastError());
        WhTool_ModUninit();
        return FALSE;
    }

    if (Wh_GetIntSetting(L"featureTail")) {
        g_tailStarted = f_tail::ToolInit();
        if (!g_tailStarted) Wh_Log(L"Taskbar button keeper failed to start");
    }
    Wh_Log(L"Started, Mocha look %s", g_enabled.load() ? L"on" : L"off");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_msgWnd) {
        PostMessageW(g_msgWnd, WM_AC_SETTINGS, 0, 0);
    } else {
        ReadSettings();
    }
    bool wantTail = Wh_GetIntSetting(L"featureTail") != 0;
    if (wantTail && !g_tailStarted) {
        g_tailStarted = f_tail::ToolInit();
    } else if (!wantTail && g_tailStarted) {
        f_tail::ToolUninit();
        g_tailStarted = false;
    } else if (g_tailStarted) {
        f_tail::ToolSettingsChanged();
    }
}

void WhTool_ModUninit() {
    SeamlessMenuSkin::Uninit();
    g_stop.store(true, std::memory_order_relaxed);
    stmset::CloseSettingsWindow();
    StopThread(g_uiThread, g_uiThreadId);
    if (g_tailStarted) {
        f_tail::ToolUninit();
        g_tailStarted = false;
    }
    if (g_instanceMutex) {
        CloseHandle(g_instanceMutex);
        g_instanceMutex = nullptr;
    }
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-12-seamless-autoclicker\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace stmset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessTaskManagerSettings";
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
// Generated by work\2026-11-12-seamless-autoclicker\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Check, L"featureNavBorder", L"Hide the navigation border", L"Removes the focus border Task Manager draws around the side menu and other controls. From Disable Task Manager Navigation Border by GF-Huang.", L"1", {}, 0, 100, 0, L"Features"},
{K::Check, L"featureDetailsIcon", L"Normal size icons on Details", L"Gives the Details and Services lists normal size icons. From Fix Task Manager Details Icon Size by GF-Huang.", L"1", {}, 0, 100, 0, L"Features"},
{K::Number, L"cellSize", L"Cell size", L"The size of the cell occupied by the icon (in pixels, ranging from 24 to 256) is used as the margin around the icon.", L"32", {}, 24, 256, 0, L"Details icons"},
{K::Number, L"iconSize", L"Icon size", L"Icon size in pixels; cannot exceed cell size (16-256)", L"24", {}, 16, 256, 0, L"Details icons"},
{K::Check, L"featurePauseButton", L"Pause button", L"Adds a Pause and Resume button to Processes and Details, for the selected app. From Task Manager Pause Button by Luiz Bizzio.", L"1", {}, 0, 100, 0, L"Features"},
{K::Check, L"featureEsc", L"Esc closes Task Manager", L"Press Esc to close Task Manager. From Press Esc to exit Task Manager by chenxustu1.", L"1", {}, 0, 100, 0, L"Features"},
{K::Check, L"featureLinkSpeed", L"Show link speed", L"Shows each network adapter's live link speed on the Performance page. From Task Manager Show Link Speed by Joe Ye.", L"1", {}, 0, 100, 1, L"Features"},
{K::Check, L"CustomLabelOverrideEnabled", L"Enable custom label text", L"Default = False, which means using the system's built-in multilingual \"Link speed\" as the label text in Task Manager. Enable this option to use custom text.", L"0", {}, 0, 100, 1, L"Link speed"},
{K::Text, L"CustomLabelOverrideText", L"Custom label text", L"Custom label text for Task Manager (example: Link speed)", L"", {}, 0, 100, 1, L"Link speed"},
{K::Check, L"featureNetworkBytes", L"Network speed in bytes", L"Shows network speed as KB/s, MB/s and GB/s instead of bits. From Task Manager Network Speed in Bytes by Nehoray-Bitan.", L"1", {}, 0, 100, 1, L"Features"},
{K::Choice, L"unitNames", L"Unit names", L"English always shows KB/s, MB/s and GB/s. Task Manager's language uses the translated unit names Task Manager shows for disk rates. Graph labels update after Task Manager is restarted.", L"english", {{L"english", L"English (KB/s, MB/s, GB/s)"}, {L"localized", L"Task Manager's display language"}}, 0, 100, 1, L"Network speed"},
{K::Check, L"featureTabSlide", L"Animate switching pages", L"A crossfade or slide when you switch pages. From Task Manager Tab Slide Animation by Abdullah Masood.", L"1", {}, 0, 100, 2, L"Features"},
{K::Choice, L"animation_type", L"Animation type", L"How the new tab appears.", L"fade", {{L"fade", L"Crossfade (no visual jump)"}, {L"slide", L"Slide"}}, 0, 100, 2, L"Page animation"},
{K::Number, L"duration_ms", L"Animation duration (ms)", L"How long the transition lasts. Clamped to 60-1500.", L"250", {}, 60, 1500, 2, L"Page animation"},
{K::Number, L"top_inset", L"Top inset (px)", L"Height of the top command bar to exclude from the animation, at 100% display scaling. It's scaled automatically for other scaling levels.", L"48", {}, 0, 200, 2, L"Page animation"},
{K::Number, L"capture_delay_ms", L"Capture delay (ms)", L"Delay after the click before capturing the new view. Raise if it grabs the old view.", L"140", {}, 0, 1000, 2, L"Page animation"},
{K::Number, L"change_threshold", L"Change threshold (%)", L"Minimum percent of the region that must change for the animation to play. Raise to reduce spurious animations.", L"2", {}, 0, 100, 2, L"Page animation"},
{K::Check, L"slide_vertical", L"Slide vertically (slide mode only)", L"Slide up/down instead of left/right. Only affects the Slide animation.", L"0", {}, 0, 100, 2, L"Page animation"},
{K::Check, L"featureTallerTab", L"Taller tabs (Windows 10)", L"Makes the old Windows 10 tab labels taller so they are easier to click. From Make Task Manager Tabs Taller by Joe Ye.", L"1", {}, 0, 100, 2, L"Features"},
{K::Check, L"featureTail", L"Keep Task Manager last on the taskbar", L"Moves Task Manager's taskbar button to the end of the taskbar. From Task Manager Tail by sb4ssman.", L"1", {}, 0, 100, 3, L"Features"},
{K::Text, L"targetName", L"Target Button Name", L"The text on the taskbar button (partial match). Change this for other languages (e.g., \"Gestionnaire\").", L"Task Manager", {}, 0, 100, 3, L"Taskbar button"},
{K::Text, L"targetClass", L"Target Window Class", L"The internal class name of the window. Use \"Notepad\" to tail Notepad, etc.", L"TaskManagerWindow", {}, 0, 100, 3, L"Taskbar button"},
{K::Number, L"moveDelay", L"Move Delay (ms)", L"How long to wait before moving the button after a check confirms it is out of place.", L"100", {}, 0, 5000, 3, L"Taskbar button"},
{K::Number, L"debounceTime", L"Event Debounce Time (ms)", L"How long to wait after window events stop occurring before checking the taskbar.", L"300", {}, 0, 5000, 3, L"Taskbar button"},
{K::Choice, L"theme", L"Look", L"Catppuccin Mocha on Task Manager's menus, flyouts, tooltips, dialogs and accent colours. None keeps Task Manager's own look.", L"Mocha", {{L"Mocha", L"Catppuccin Mocha"}, {L"", L"None"}}, 0, 100, 4, L"Look"},
{K::Hotkey, L"toggleHotkey", L"Turn the Mocha look on or off", L"Press the keys in the box. Backspace clears it. The tray icon does the same.", L"", {}, 0, 100, 4, L"Shortcut"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 4, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 4, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to turn the Mocha look on or off. Right-click it for these settings. When off, change settings in Windhawk.", L"1", {}, 0, 100, 4, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Processes and details", L"The border, Details icons, the Pause button and Esc to close.", 0xE9D9},
{L"Network", L"Link speed and network speed in bytes.", 0xE968},
{L"Tabs and animation", L"The page switch animation and taller Windows 10 tabs.", 0xE8A9},
{L"Taskbar button", L"Keep Task Manager's button at the end of the taskbar.", 0xE90E},
{L"Look", L"The Mocha look, its shortcut, the tray icon and this window.", 0xE790},
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
constexpr PCWSTR kSetPaletteUrl = L"https://github.com/catppuccin/catppuccin";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Task%20Manager%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Task Manager";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Task Manager") <= railW) break;
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
        add(SetItem::Link, 56, L"Colours from Catppuccin Mocha", L"By the Catppuccin team, MIT", kSetPaletteUrl);
        add(SetItem::Link, 56, L"GF-Huang", L"Navigation border and Details icons", L"https://github.com/GF-Huang");
        add(SetItem::Link, 56, L"Luiz Bizzio", L"Pause button", L"https://github.com/luizbizzio");
        add(SetItem::Link, 56, L"sb4ssman", L"Taskbar button keeper", L"https://github.com/sb4ssman");
        add(SetItem::Link, 56, L"chenxustu1", L"Esc closes Task Manager", L"https://github.com/chenxustu1");
        add(SetItem::Link, 56, L"Joe Ye", L"Link speed and taller tabs", L"https://github.com/JoeYe-233");
        add(SetItem::Link, 56, L"Nehoray-Bitan", L"Network speed in bytes", L"https://github.com/Nehoray-Bitan");
        add(SetItem::Link, 56, L"Abdullah Masood", L"Page animation", L"https://github.com/Abdullah-Masood-05");
        add(SetItem::Link, 56, L"m417z", L"Styling engine (Windows Settings Styler)", L"https://github.com/m417z");
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
    p.Glyph(w.fIconL.get(), 0xE9D9, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Task Manager", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  GPL-3.0  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"GPL-3.0  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Every Task Manager tweak in one mod, with the Catppuccin Mocha look on its menus, flyouts and accents.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi. Built on mods by GF-Huang, Luiz Bizzio, sb4ssman, chenxustu1, Joe Ye, Nehoray-Bitan, Abdullah Masood and m417z.",
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
    p.Text(w.fRailName.get(), L"Task Manager", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Task Manager settings", style,
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
int ShowTrayMenu(HWND owner, const POINT* at, bool on, PCWSTR hotkey) {
    return Set_TrayMenu(owner, {Set_MenuRow(100, L"", L"Mocha look on", on, false, hotkey),
                                Set_MenuSep(),
                                Set_MenuRow(101, L"", L"Settings")}, at);
}
}  // namespace stmset

#include <xamlom.h>

#include <atomic>
#include <vector>

#undef GetCurrentTime

#include <winrt/Windows.UI.Xaml.h>

struct ThemeTargetStyles {
    PCWSTR target;
    std::vector<PCWSTR> styles;
};

struct Theme {
    std::vector<ThemeTargetStyles> targetStyles;
    std::vector<PCWSTR> styleConstants;
    std::vector<PCWSTR> themeResourceVariables;
};

// clang-format off


// Catppuccin Mocha: frosted menus and flyouts with a grey 2 px edge, blue to mauve accents.
const Theme g_themeMocha = {{
    ThemeTargetStyles{L"MenuFlyoutPresenter", {
        L"Background:=<AcrylicBrush BackgroundSource=\"HostBackdrop\" TintColor=\"#1E1E2E\" TintOpacity=\"0.6\" FallbackColor=\"#1E1E2E\"/>",
        L"BorderBrush=#585B70",
        L"BorderThickness=2",
        L"CornerRadius=8"}},
    ThemeTargetStyles{L"FlyoutPresenter", {
        L"Background:=<AcrylicBrush BackgroundSource=\"HostBackdrop\" TintColor=\"#1E1E2E\" TintOpacity=\"0.6\" FallbackColor=\"#1E1E2E\"/>",
        L"BorderBrush=#585B70",
        L"BorderThickness=2",
        L"CornerRadius=8"}},
    ThemeTargetStyles{L"CommandBarOverflowPresenter", {
        L"Background:=<AcrylicBrush BackgroundSource=\"HostBackdrop\" TintColor=\"#1E1E2E\" TintOpacity=\"0.6\" FallbackColor=\"#1E1E2E\"/>",
        L"BorderBrush=#585B70",
        L"BorderThickness=2",
        L"CornerRadius=8"}},
    ThemeTargetStyles{L"ToolTip", {
        L"Background:=<AcrylicBrush BackgroundSource=\"HostBackdrop\" TintColor=\"#1E1E2E\" TintOpacity=\"0.6\" FallbackColor=\"#1E1E2E\"/>",
        L"Foreground=#CDD6F4",
        L"BorderBrush=#585B70",
        L"BorderThickness=2",
        L"CornerRadius=8"}},
    ThemeTargetStyles{L"ContentDialog", {
        L"Background=#1E1E2E",
        L"BorderBrush=#585B70",
        L"BorderThickness=2",
        L"CornerRadius=8"}},
    ThemeTargetStyles{L"MenuFlyoutItem", {
        L"Foreground=#CDD6F4"}},
}, {}, {
    L"SystemAccentColor=#89B4FA",
    L"SystemAccentColorLight1=#89B4FA",
    L"SystemAccentColorLight2=#B4BEFE",
    L"SystemAccentColorLight3=#CBA6F7",
    L"AccentFillColorDefaultBrush=#89B4FA",
    L"AccentFillColorSecondaryBrush=#B4BEFE",
    L"AccentFillColorTertiaryBrush=#CBA6F7",
    L"TextOnAccentFillColorPrimaryBrush=#11111B",
    L"NavigationViewSelectionIndicatorForeground=#89B4FA",
    L"AccentTextFillColorPrimaryBrush=#89B4FA",
    L"TextFillColorPrimaryBrush=#CDD6F4",
    L"TextFillColorSecondaryBrush=#BAC2DE",
    L"TextFillColorTertiaryBrush=#A6ADC8"
}};

// clang-format on

std::atomic<DWORD> g_targetThreadId = 0;

void ApplyCustomizations(InstanceHandle handle,
                         winrt::Windows::UI::Xaml::FrameworkElement element,
                         PCWSTR fallbackClassName);
void CleanupCustomizations(InstanceHandle handle);
void TrackSplitView(winrt::Windows::UI::Xaml::FrameworkElement element);
void ReleaseDiscardedSplitViewChild(
    winrt::Windows::Foundation::IInspectable removedElement);

HMODULE GetCurrentModuleHandle() {
    HMODULE module;
    if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                               GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           L"", &module)) {
        return nullptr;
    }

    return module;
}

////////////////////////////////////////////////////////////////////////////////
// clang-format off

#pragma region winrt_hpp

#include <Unknwn.h>
#include <winrt/base.h>

// forward declare namespaces we alias
namespace winrt {
    namespace Windows {
        namespace Foundation {}
        namespace UI::Xaml {}
    }
}

// alias some long namespaces for convenience
namespace wf = winrt::Windows::Foundation;
namespace wux = winrt::Windows::UI::Xaml;

#pragma endregion  // winrt_hpp

#pragma region visualtreewatcher_hpp

#include <winrt/Windows.UI.Xaml.h>

class VisualTreeWatcher : public winrt::implements<VisualTreeWatcher, IVisualTreeServiceCallback2, winrt::non_agile>
{
public:
    VisualTreeWatcher(winrt::com_ptr<IUnknown> site);

    VisualTreeWatcher(const VisualTreeWatcher&) = delete;
    VisualTreeWatcher& operator=(const VisualTreeWatcher&) = delete;

    VisualTreeWatcher(VisualTreeWatcher&&) = delete;
    VisualTreeWatcher& operator=(VisualTreeWatcher&&) = delete;

    ~VisualTreeWatcher();

    void UnadviseVisualTreeChange();

private:
    HRESULT STDMETHODCALLTYPE OnVisualTreeChange(ParentChildRelation relation, VisualElement element, VisualMutationType mutationType) override;
    HRESULT STDMETHODCALLTYPE OnElementStateChanged(InstanceHandle element, VisualElementState elementState, LPCWSTR context) noexcept override;

    wf::IInspectable FromHandle(InstanceHandle handle)
    {
        wf::IInspectable obj;
        winrt::check_hresult(m_XamlDiagnostics->GetIInspectableFromHandle(handle, reinterpret_cast<::IInspectable**>(winrt::put_abi(obj))));
        return obj;
    }

    winrt::com_ptr<IXamlDiagnostics> m_XamlDiagnostics = nullptr;
};

#pragma endregion  // visualtreewatcher_hpp

#pragma region visualtreewatcher_cpp

VisualTreeWatcher::VisualTreeWatcher(winrt::com_ptr<IUnknown> site) :
    m_XamlDiagnostics(site.as<IXamlDiagnostics>())
{
    Wh_Log(L"Constructing VisualTreeWatcher");
    // winrt::check_hresult(m_XamlDiagnostics.as<IVisualTreeService3>()->AdviseVisualTreeChange(this));

    // Calling AdviseVisualTreeChange from the current thread causes the app to
    // hang in Advising::RunOnUIThread sometimes. Creating a new thread and
    // calling it from there fixes it.
    HANDLE thread = CreateThread(
        nullptr, 0,
        [](LPVOID lpParam) -> DWORD {
            auto watcher = reinterpret_cast<VisualTreeWatcher*>(lpParam);
            HRESULT hr = watcher->m_XamlDiagnostics.as<IVisualTreeService3>()->AdviseVisualTreeChange(watcher);
            watcher->Release();
            if (FAILED(hr)) {
                Wh_Log(L"Error %08X", hr);
            }
            return 0;
        },
        this, 0, nullptr);
    if (thread) {
        AddRef();
        CloseHandle(thread);
    }
}

VisualTreeWatcher::~VisualTreeWatcher()
{
    Wh_Log(L"Destructing VisualTreeWatcher");
}

void VisualTreeWatcher::UnadviseVisualTreeChange()
{
    Wh_Log(L"UnadviseVisualTreeChange VisualTreeWatcher");
    HRESULT hr = m_XamlDiagnostics.as<IVisualTreeService3>()->UnadviseVisualTreeChange(this);
    if (FAILED(hr)) {
        Wh_Log(L"UnadviseVisualTreeChange failed with error %08X", hr);
    }
}

HRESULT VisualTreeWatcher::OnVisualTreeChange(ParentChildRelation, VisualElement element, VisualMutationType mutationType) try
{
    if (GetCurrentThreadId() != g_targetThreadId)
    {
        Wh_Log(L"Not initialized for thread %u", GetCurrentThreadId());
        return S_OK;
    }

    Wh_Log(L"========================================");

    switch (mutationType)
    {
    case Add:
        Wh_Log(L"Mutation type: Add %llu", element.Handle);
        break;

    case Remove:
        Wh_Log(L"Mutation type: Remove %llu", element.Handle);
        break;

    default:
        Wh_Log(L"Mutation type: %d %llu", static_cast<int>(mutationType), element.Handle);
        break;
    }

    Wh_Log(L"Element type: %s", element.Type);

    if (mutationType == Add)
    {
        const auto inspectable = FromHandle(element.Handle);
        auto frameworkElement = inspectable.try_as<wux::FrameworkElement>();
        if (frameworkElement)
        {
            Wh_Log(L"FrameworkElement name: %s", frameworkElement.Name().c_str());
            TrackSplitView(frameworkElement);
            ApplyCustomizations(element.Handle, frameworkElement, element.Type);
        }
        else
        {
            Wh_Log(L"Skipping non-FrameworkElement");
        }
    }
    else if (mutationType == Remove)
    {
        CleanupCustomizations(element.Handle);
        ReleaseDiscardedSplitViewChild(FromHandle(element.Handle));
    }

    return S_OK;
}
catch (...)
{
    HRESULT hr = winrt::to_hresult();
    Wh_Log(L"Error %08X", hr);

    // Returning an error prevents (some?) further messages, always return
    // success.
    // return hr;
    return S_OK;
}

HRESULT VisualTreeWatcher::OnElementStateChanged(InstanceHandle, VisualElementState, LPCWSTR) noexcept
{
    return S_OK;
}

#pragma endregion  // visualtreewatcher_cpp

#pragma region tap_hpp

#include <ocidl.h>

winrt::com_ptr<VisualTreeWatcher> g_visualTreeWatcher;

// {C85D8CC7-5463-40E8-A432-F5916B6427E5}
static constexpr CLSID CLSID_WindhawkTAP = { 0xc85d8cc7, 0x5463, 0x40e8, { 0xa4, 0x32, 0xf5, 0x91, 0x6b, 0x64, 0x27, 0xe5 } };

class WindhawkTAP : public winrt::implements<WindhawkTAP, IObjectWithSite, winrt::non_agile>
{
public:
    HRESULT STDMETHODCALLTYPE SetSite(IUnknown *pUnkSite) override;
    HRESULT STDMETHODCALLTYPE GetSite(REFIID riid, void **ppvSite) noexcept override;

private:
    winrt::com_ptr<IUnknown> site;
};

#pragma endregion  // tap_hpp

#pragma region tap_cpp

HRESULT WindhawkTAP::SetSite(IUnknown *pUnkSite) try
{
    // Only ever 1 VTW at once.
    if (g_visualTreeWatcher)
    {
        g_visualTreeWatcher->UnadviseVisualTreeChange();
        g_visualTreeWatcher = nullptr;
    }

    site.copy_from(pUnkSite);

    if (site)
    {
        // Decrease refcount increased by InitializeXamlDiagnosticsEx.
        FreeLibrary(GetCurrentModuleHandle());

        g_visualTreeWatcher = winrt::make_self<VisualTreeWatcher>(site);
    }

    return S_OK;
}
catch (...)
{
    HRESULT hr = winrt::to_hresult();
    Wh_Log(L"Error %08X", hr);
    return hr;
}

HRESULT WindhawkTAP::GetSite(REFIID riid, void **ppvSite) noexcept
{
    return site.as(riid, ppvSite);
}

#pragma endregion  // tap_cpp

#pragma region simplefactory_hpp

#include <Unknwn.h>

template<class T>
struct SimpleFactory : winrt::implements<SimpleFactory<T>, IClassFactory, winrt::non_agile>
{
    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override try
    {
        if (!pUnkOuter)
        {
            *ppvObject = nullptr;
            return winrt::make<T>().as(riid, ppvObject);
        }
        else
        {
            return CLASS_E_NOAGGREGATION;
        }
    }
    catch (...)
    {
        HRESULT hr = winrt::to_hresult();
        Wh_Log(L"Error %08X", hr);
        return hr;
    }

    HRESULT STDMETHODCALLTYPE LockServer(BOOL) noexcept override
    {
        return S_OK;
    }
};

#pragma endregion  // simplefactory_hpp

#pragma region module_cpp

#include <combaseapi.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdll-attribute-on-redeclaration"

__declspec(dllexport)
_Use_decl_annotations_ STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) try
{
    if (rclsid == CLSID_WindhawkTAP)
    {
        *ppv = nullptr;
        return winrt::make<SimpleFactory<WindhawkTAP>>().as(riid, ppv);
    }
    else
    {
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}
catch (...)
{
    HRESULT hr = winrt::to_hresult();
    Wh_Log(L"Error %08X", hr);
    return hr;
}

__declspec(dllexport)
_Use_decl_annotations_ STDAPI DllCanUnloadNow()
{
    if (winrt::get_module_lock())
    {
        return S_FALSE;
    }
    else
    {
        return S_OK;
    }
}

#pragma clang diagnostic pop

#pragma endregion  // module_cpp

#pragma region api_cpp

using PFN_INITIALIZE_XAML_DIAGNOSTICS_EX = decltype(&InitializeXamlDiagnosticsEx);

HRESULT InjectWindhawkTAP() noexcept
{
    HMODULE module = GetCurrentModuleHandle();
    if (!module)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    WCHAR location[MAX_PATH];
    switch (GetModuleFileName(module, location, ARRAYSIZE(location)))
    {
    case 0:
    case ARRAYSIZE(location):
        return HRESULT_FROM_WIN32(GetLastError());
    }

    const HMODULE wux(LoadLibraryEx(L"Windows.UI.Xaml.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32));
    if (!wux) [[unlikely]]
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    const auto ixde = reinterpret_cast<PFN_INITIALIZE_XAML_DIAGNOSTICS_EX>(GetProcAddress(wux, "InitializeXamlDiagnosticsEx"));
    if (!ixde) [[unlikely]]
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    // I didn't find a better way than trying many connections until one works.
    // Reference:
    // https://github.com/microsoft/microsoft-ui-xaml/blob/d74a0332cf0d5e58f12eddce1070fa7a79b4c2db/src/dxaml/xcp/dxaml/lib/DXamlCore.cpp#L2782
    HRESULT hr;
    for (int i = 0; i < 10000; i++)
    {
        WCHAR connectionName[256];
        wsprintf(connectionName, L"VisualDiagConnection%d", i + 1);

        hr = ixde(connectionName, GetCurrentProcessId(), L"", location, CLSID_WindhawkTAP, nullptr);
        if (hr != HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
        {
            break;
        }
    }

    return hr;
}

#pragma endregion  // api_cpp

// clang-format on
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <charconv>
#include <chrono>
#include <cmath>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::string_view_literals;

#include <initguid.h>

#include <commctrl.h>
#include <d2d1_1.h>
#include <roapi.h>
#include <windows.graphics.effects.h>
#include <winstring.h>

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.Networking.Connectivity.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.System.Power.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.h>

using namespace winrt::Windows::UI::Xaml;

// Task Manager hosts XAML in islands; read the app resources without throwing.
ResourceDictionary StmAppResources() {
    try {
        if (auto app = Application::Current()) {
            return app.Resources();
        }
    } catch (...) {
    }
    return nullptr;
}

namespace wge = winrt::Windows::Graphics::Effects;
namespace wuc = winrt::Windows::UI::Composition;
namespace wuxh = wux::Hosting;
namespace awge = ABI::Windows::Graphics::Effects;

// https://stackoverflow.com/a/51274008
template <auto fn>
struct deleter_from_fn {
    template <typename T>
    constexpr void operator()(T* arg) const {
        fn(arg);
    }
};
using string_setting_unique_ptr =
    std::unique_ptr<const WCHAR[], deleter_from_fn<Wh_FreeStringSetting>>;

using PropertyKeyValue =
    std::pair<DependencyProperty, winrt::Windows::Foundation::IInspectable>;

using PropertyValuesUnresolved =
    std::vector<std::pair<std::wstring, std::wstring>>;
using PropertyValues = std::vector<PropertyKeyValue>;
using PropertyValuesMaybeUnresolved =
    std::variant<PropertyValuesUnresolved, PropertyValues>;

struct ElementMatcher {
    enum class Kind {
        Element,   // Normal element matcher.
        Wildcard,  // '*': matches zero or more intermediate ancestors.
        Root,      // ':root': asserts the next element has no parent.
    };
    Kind kind = Kind::Element;
    std::wstring type;
    std::wstring name;
    std::optional<std::wstring> visualStateGroupName;
    int oneBasedIndex = 0;
    PropertyValuesMaybeUnresolved propertyValues;
};

// A `Property[@VisualState][:]=value` rule that sets a control property.
// `value` may contain `{{...}}` placeholders, in which case `isDynamic()`
// returns true and the rule is re-resolved on every apply.
struct ValueRule {
    std::wstring propertyName;
    std::wstring visualState;
    std::wstring value;
    bool isXamlValue = false;

    bool isDynamic() const { return value.find(L"{{") != std::wstring::npos; }
};

// A `Property=>VarName` rule that observes a control property and writes its
// current value into the named mod-global style variable.
struct CaptureRule {
    std::wstring propertyName;
    std::wstring varName;
};

// Parsed-but-not-yet-resolved rules for one target. Captures and value-rules
// are intentionally split: they live in different fields of `ResolvedRules`
// post-resolution, and the parser already validates that captures cannot carry
// `:=` or `@VisualState`.
struct UnresolvedRules {
    std::vector<ValueRule> valueRules;
    std::vector<CaptureRule> captureRules;
};

struct XamlBlurBrushParams {
    float blurAmount;
    winrt::Windows::UI::Color tint;
    std::optional<uint8_t> tintOpacity;
    std::wstring tintThemeResourceKey;  // Empty if not from ThemeResource
    std::optional<float> tintLuminosityOpacity;
    std::optional<float> tintSaturation;
    std::optional<float> noiseOpacity;
    std::optional<float> noiseDensity;
    std::optional<winrt::Windows::UI::Color> fallbackColor;
    std::wstring fallbackThemeResourceKey;  // Empty if not from ThemeResource
};

// Holds the raw rule body for a style whose value depends on `{{...}}`
// substitutions. Re-resolved on every apply and on every variable change.
// `propertyName` is kept alongside the value because Windows.UI.Xaml's
// DependencyProperty does not expose its name, and the re-resolution path needs
// to feed the name back to the XAML parser.
struct DynamicStyleTemplate {
    std::wstring propertyName;
    std::wstring rawValue;
    bool isXamlValue = false;
};

// Tagged value for one (property, visualState) cell of PropertyOverrides.
// Possible states:
// - IInspectable        : fully resolved WinRT value (literal or static XAML).
//                         Apply directly via SetValue.
// - XamlBlurBrushParams : parsed `<WindhawkBlur .../>` parameters. The brush
//                         instance is constructed at apply time (needs the live
//                         UIElement).
// - DynamicStyleTemplate: rule body contains `{{...}}` substitutions.
//                         Re-resolved on every apply and on every variable
//                         change. This arm appears only inside
//                         PropertyOverrides cells; it is never stored in
//                         ElementPropertyCustomizationState::customValue (see
//                         notes there).
using PropertyOverrideValue =
    std::variant<winrt::Windows::Foundation::IInspectable,
                 XamlBlurBrushParams,
                 DynamicStyleTemplate>;

// Property -> visual state -> value.
using PropertyOverrides =
    std::unordered_map<DependencyProperty,
                       std::unordered_map<std::wstring, PropertyOverrideValue>>;

// Resolved counterpart to CaptureRule: the property name string has been turned
// into an actual DependencyProperty by the XAML parser, so the apply path can
// call RegisterPropertyChangedCallback / GetValue directly without re-resolving
// on every use.
struct CaptureSpec {
    DependencyProperty property{nullptr};
    std::wstring varName;
};

struct ResolvedRules {
    PropertyOverrides propertyOverrides;
    std::vector<CaptureSpec> captures;
    // Whether this target consumes style variables. Lets ApplyCustomizations
    // skip the visual-tree bookkeeping that only variable users need.
    bool hasDynamicValues = false;
};

using PropertyOverridesMaybeUnresolved =
    std::variant<UnresolvedRules, ResolvedRules>;

// A `{{Var}}` reference resolved for one consuming property. The owner lets a
// value change on some other capture of the same name be skipped.
struct StyleVariableDependency {
    std::wstring name;
    InstanceHandle owner = 0;  // 0 when the variable was undefined
};

// Interned node of an element's visual-tree spine. Nodes are shared by every
// tracked element under the same ancestor, so the pool holds one node per
// distinct ancestor rather than a full path per element. Once a node exists its
// `parent` and `depth` are final; an element that is later reparented keeps the
// spine it was first seen with, and only a node interned as a root before its
// object was attached (see GetOrCreateElementTreeNode) is ever replaced.
struct ElementTreeNode {
    // A node can outlive the object it describes -- descendant nodes and
    // not-yet-cleaned-up ElementCustomizationState entries keep it alive -- so
    // this is what proves a pool hit isn't a recycled address.
    winrt::weak_ref<DependencyObject> ref;
    std::shared_ptr<ElementTreeNode> parent;
    uint32_t depth = 0;
};

// Keyed by the object's IUnknown pointer: COM only guarantees a stable pointer
// for that interface, and the same element is reached both as a
// FrameworkElement and as a VisualTreeHelper::GetParent result.
std::unordered_map<void*, std::weak_ptr<ElementTreeNode>> g_elementTreeNodes;

// Expired pool entries are reaped once the map grows past this, which is then
// set to twice the surviving size, making the sweep amortized O(1).
size_t g_elementTreeNodesReapThreshold = 64;

void* ElementIdentityKey(DependencyObject const& object) {
    return winrt::get_abi(object.as<winrt::Windows::Foundation::IUnknown>());
}

// Fetch (or build) the spine node for `object`. Uses
// VisualTreeHelper::GetParent rather than Parent(), same reason as in
// FindElementPropertyOverrides. Returns nullptr if a node can't be built,
// leaving callers with no proximity information rather than a wrong answer.
std::shared_ptr<ElementTreeNode> GetOrCreateElementTreeNode(
    DependencyObject object) {
    if (!object) {
        return nullptr;
    }

    std::shared_ptr<ElementTreeNode> node;

    // Ancestors still lacking a node, innermost first. The walk stops at the
    // first ancestor that is already interned, so a new sibling of an
    // already-seen element costs one GetParent call.
    std::vector<DependencyObject> missing;

    try {
        for (auto iter = object; iter;
             iter = Media::VisualTreeHelper::GetParent(iter)) {
            auto key = ElementIdentityKey(iter);

            if (auto it = g_elementTreeNodes.find(key);
                it != g_elementTreeNodes.end()) {
                auto existing = it->second.lock();
                // A weak_ref never resolves to an object other than its own, so
                // a live ref proves this address hasn't been recycled since.
                if (!existing || !existing->ref.get()) {
                    Wh_Log(L"Replacing stale tree node for a reused address");
                    g_elementTreeNodes.erase(it);
                } else if (existing->depth > 0 ||
                           !Media::VisualTreeHelper::GetParent(iter)) {
                    node = std::move(existing);
                    break;
                } else {
                    // A depth-0 node was interned as a root. Having a parent
                    // now means the object was only partly attached back then
                    // and the node stops short of the real root, so drop it and
                    // let the walk rebuild the full spine. Elements interned
                    // through the old node keep it and stay unrankable against
                    // the rest of the tree, which is the same answer they got
                    // before the repair.
                    Wh_Log(L"Rebuilding tree node interned before attachment");
                    g_elementTreeNodes.erase(it);
                }
            }

            missing.push_back(iter);
        }

        for (auto it = missing.rbegin(); it != missing.rend(); ++it) {
            auto fresh = std::make_shared<ElementTreeNode>();
            fresh->ref = *it;
            fresh->depth = node ? node->depth + 1 : 0;
            fresh->parent = std::move(node);
            g_elementTreeNodes[ElementIdentityKey(*it)] = fresh;
            node = std::move(fresh);
        }
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        return nullptr;
    }

    return node;
}

void ReapElementTreeNodesIfNeeded() {
    if (g_elementTreeNodes.size() < g_elementTreeNodesReapThreshold) {
        return;
    }

    std::erase_if(g_elementTreeNodes,
                  [](const auto& item) { return item.second.expired(); });
    g_elementTreeNodesReapThreshold =
        std::max<size_t>(64, g_elementTreeNodes.size() * 2);
}

// Depth of the lowest common ancestor of two spine nodes, or -1 when they have
// none (separate visual trees, or a node that couldn't be built). A node counts
// as its own ancestor, so an element on the other's parent chain scores its own
// depth -- the deepest score that element can reach.
int ElementTreeLcaDepth(ElementTreeNode const* a, ElementTreeNode const* b) {
    if (!a || !b) {
        return -1;
    }

    while (a->depth > b->depth) {
        a = a->parent.get();
    }
    while (b->depth > a->depth) {
        b = b->parent.get();
    }

    while (a != b) {
        a = a->parent.get();
        b = b->parent.get();
        if (!a || !b) {
            return -1;
        }
    }

    return static_cast<int>(a->depth);
}

struct ElementCustomizationRules {
    ElementMatcher elementMatcher;
    std::vector<ElementMatcher> parentElementMatchers;
    PropertyOverridesMaybeUnresolved propertyOverrides;
};

std::vector<ElementCustomizationRules> g_elementsCustomizationRules;

struct ElementPropertyCustomizationState {
    std::optional<winrt::Windows::Foundation::IInspectable> originalValue;
    // The most recently applied value, re-pushed by the per-DP property-
    // changed callback when something external (animation, system Setter)
    // overrides it. Although PropertyOverrideValue's variant declares a
    // DynamicStyleTemplate arm, customValue here is always either IInspectable
    // or XamlBlurBrushParams in practice -- dynamic styles get resolved into
    // one of those before being stored, and the source template lives
    // separately in `dynamicTemplate` below.
    std::optional<PropertyOverrideValue> customValue;
    winrt::Windows::Foundation::IInspectable lastAppliedValue{nullptr};
    int64_t propertyChangedToken = 0;
    // Source template for dynamic styles whose value contains `{{...}}`
    // substitutions; re-evaluated whenever a referenced variable changes, with
    // the resolved result written back into `customValue`. Empty for static
    // styles.
    std::optional<DynamicStyleTemplate> dynamicTemplate;
    // Style variables this property's value depends on, each with the capture
    // that supplied it. Populated alongside `dynamicTemplate`; empty for static
    // styles.
    std::vector<StyleVariableDependency> variableDependencies;
    // Makes this property re-resolve on any change to any of its variables:
    // expansion aborts at the first failure, so the names past that point have
    // no recorded owner and a targeted propagation would never reach them.
    bool lastResolveFailed = false;
};

struct CapturePropertyCustomizationState {
    std::wstring varName;
    int64_t propertyChangedToken = 0;
};

struct ElementCustomizationStateForVisualStateGroup {
    std::unordered_map<DependencyProperty, ElementPropertyCustomizationState>
        propertyCustomizationStates;
    winrt::event_token visualStateGroupCurrentStateChangedToken;
};

struct ElementCustomizationState {
    winrt::weak_ref<FrameworkElement> element;

    // Scores how close each capture of a style variable is to this element.
    // Only built for elements that capture or consume a variable.
    std::shared_ptr<ElementTreeNode> treeNode;

    // Capture state lives at the element level: capture rules (`Prop=>Var`) are
    // intentionally not visual-state-aware (the parser rejects `@VisualState`
    // on them), and a single element observed by multiple targets with
    // different VSGs should still only register one
    // RegisterPropertyChangedCallback per DP and one SizeChanged subscription.
    std::unordered_map<DependencyProperty, CapturePropertyCustomizationState>
        captureCustomizationStates;

    // ActualWidth/ActualHeight (and other layout-driven DPs) do not fire
    // RegisterPropertyChangedCallback on UWP, so any element with capture rules
    // also subscribes to `FrameworkElement.SizeChanged` to pick up size
    // changes.
    winrt::event_token captureSizeChangedToken;

    // Use list to avoid reallocations on insertion, as pointers to items are
    // captured in callbacks and stored.
    std::list<std::pair<std::optional<winrt::weak_ref<VisualStateGroup>>,
                        ElementCustomizationStateForVisualStateGroup>>
        perVisualStateGroup;
};

std::unordered_map<InstanceHandle, ElementCustomizationState>
    g_elementsCustomizationState;

// The element's spine node, built on first use if the eager attempt in
// ApplyCustomizations came up empty. An element can be matched before it is
// attached, and a spine built then would stop short of the real root; retrying
// on use picks up the real one once the element is in the tree.
ElementTreeNode* EnsureElementTreeNode(
    ElementCustomizationState& elementCustomizationState) {
    if (!elementCustomizationState.treeNode) {
        if (auto element = elementCustomizationState.element.get()) {
            elementCustomizationState.treeNode =
                GetOrCreateElementTreeNode(element);
        }
    }

    return elementCustomizationState.treeNode.get();
}

// Mod-global style variable registry. Populated by `Property=>VarName` capture
// rules and consumed by `{{VarName}}` substitutions in other styles. Every
// capturing element gets its own entry, so a name stays defined until its last
// capture goes away, and a consumer reading the name resolves to whichever
// capture is closest to it in the visual tree.
struct StyleVariableValue {
    std::wstring stringForm;        // invariant-formatted text representation
    std::optional<double> numeric;  // only present when source was numeric
    // True for primitive captures whose `stringForm` is meaningful to insert
    // verbatim into a XAML attribute (numeric, boolean, string). False for
    // opaque types -- their stringForm is the captured class name, kept only
    // for diagnostics; bare-identifier substitution skips such variables.
    bool substitutable = false;
};

// One element's capture of a variable. FindElementPropertyOverrides dedupes
// captures by name, so (name, elementHandle) identifies an entry.
struct StyleVariableCapture {
    InstanceHandle elementHandle;
    StyleVariableValue value;
};

struct StyleVariableConsumer {
    InstanceHandle elementHandle;
    DependencyProperty property{nullptr};
    // Each consumer remembers its own fallbackClassName so that propagation can
    // re-resolve dynamic styles using the consumer's match-site context, not
    // the (potentially different) capturer's.
    std::wstring fallbackClassName;
};

// Mod-global style variable registry. The struct mirrors the per-XamlRoot state
// used by the taskbar styler so the variable-resolution call paths stay aligned
// across the styler mods, but here all elements share one registry.
struct StyleVariableState {
    std::unordered_map<std::wstring, std::vector<StyleVariableCapture>>
        variables;
    std::unordered_map<std::wstring, std::vector<StyleVariableConsumer>>
        consumers;
};

StyleVariableState g_styleVariableState;

// Non-zero while PropagateStyleVariableChange is running, so nested calls queue
// instead of recursing.
int g_styleVariablePropagationDepth;

struct PendingStyleVariablePropagation {
    StyleVariableState* state;
    std::wstring varName;
    std::optional<InstanceHandle> changedOwner;

    bool operator==(const PendingStyleVariablePropagation&) const = default;
};

// Propagations queued while another one is running, drained by the outermost
// PropagateStyleVariableChange frame.
std::vector<PendingStyleVariablePropagation> g_pendingStyleVariablePropagations;

StyleVariableState* GetStyleVariableState() {
    return &g_styleVariableState;
}

bool g_elementPropertyModifying;

// An ImageBrush with a remote source fails to load when the process starts
// before the network is up. Such brushes are tracked so that the load can be
// retried once there's internet access. Only a brush which has no image is
// retried, so replacing its source has nothing to hide, and the source is never
// cleared, so an image that's currently displayed can't be blanked out.
struct TrackedImageBrush {
    winrt::weak_ref<Media::ImageBrush> brush;
    winrt::Windows::Foundation::Uri uri{nullptr};

    // Decode properties of the BitmapImage the style declared, reapplied to the
    // BitmapImage a retry creates.
    int32_t decodePixelWidth = 0;
    int32_t decodePixelHeight = 0;
    Media::Imaging::DecodePixelType decodePixelType =
        Media::Imaging::DecodePixelType::Physical;
    Media::Imaging::BitmapCreateOptions createOptions =
        Media::Imaging::BitmapCreateOptions::None;
    bool autoPlay = true;

    Media::ImageBrush::ImageFailed_revoker imageFailedRevoker;
    Media::ImageBrush::ImageOpened_revoker imageOpenedRevoker;

    // Whether the brush has an image. Retries target the brushes which don't.
    bool loaded = false;

    ULONGLONG lastRetryTick = 0;
    int retryCount = 0;
};

struct TrackedImageBrushesForThread {
    // Entries are held by shared_ptr so that event handlers can reference them
    // via a weak_ptr and do nothing once an entry is gone.
    std::list<std::shared_ptr<TrackedImageBrush>> brushes;
    winrt::Windows::System::DispatcherQueue dispatcher{nullptr};
    winrt::Windows::System::DispatcherQueueTimer retryDebounceTimer{nullptr};
    winrt::Windows::System::DispatcherQueueTimer::Tick_revoker
        retryDebounceTimerTickRevoker;
};

thread_local TrackedImageBrushesForThread g_trackedImageBrushesForThread;

// A single connectivity transition raises several network status events, and
// the state right after the first one isn't final yet.
constexpr DWORD kNetworkChangeDebounceMs = 2000;

// Minimum delay between the retries of a brush, doubling with each attempt up
// to about five minutes. Also keeps a retry from being started while the
// previous one is still loading.
constexpr ULONGLONG kImageRetryBaseDelayMs = 5000;
constexpr int kImageRetryMaxBackoffShift = 6;
constexpr ULONGLONG kImageRetryMaxDelayMs = kImageRetryBaseDelayMs
                                            << kImageRetryMaxBackoffShift;

// Caps the attempts of a brush so that an event storm doesn't retry it
// endlessly. The count starts over once the brush has been idle for the maximum
// delay, so connectivity which returns much later can still recover the image.
constexpr int kImageRetryMaxCount = 20;

// Guards the globals below it. The network status handler acquires it, so it
// must never be held while adding or removing that handler: the event source
// can wait for an invocation which is already in flight, and registering from a
// UI thread pumps messages, which can re-enter this code on the same thread.
std::mutex g_imageRetryMutex;
bool g_imageRetryActive;
// The dispatcher of each UI thread which has tracked brushes, used to run a
// retry on the thread that owns the brush.
std::vector<winrt::weak_ref<winrt::Windows::System::DispatcherQueue>>
    g_imageRetryDispatchers;
winrt::event_token g_networkStatusChangedToken;
// Set while a thread is registering the handler outside the mutex, so that a
// concurrent or re-entrant call doesn't register a second one.
bool g_networkStatusChangedRegistering;

enum class ResourceVariableTheme {
    None,
    Dark,
    Light,
};

enum class ResourceVariableType {
    String,
    Xaml,
    ThemeResourceReference,
};

struct ResourceVariableEntry {
    std::wstring key;
    std::wstring value;
    ResourceVariableTheme theme;
    ResourceVariableType type;
};

std::vector<ResourceVariableEntry> g_resourceVariables;

// Track original resource values for restoration (per-thread since
// Application::Current().Resources() is per-thread).
std::unordered_map<std::wstring, winrt::Windows::Foundation::IInspectable>
    g_originalResourceValues;

// Track our merged theme dictionary for cleanup (per-thread).
ResourceDictionary g_resourceVariablesThemeDict{nullptr};

// For listening to theme color changes (per-thread).
winrt::Windows::UI::ViewManagement::UISettings g_uiSettings{nullptr};
thread_local winrt::event_token g_colorValuesChangedToken;

winrt::Windows::Foundation::IInspectable ReadLocalValueWithWorkaround(
    DependencyObject elementDo,
    DependencyProperty property) {
    auto value = elementDo.ReadLocalValue(property);

    // Workaround for RowDefinitions/ColumnDefinitions.
    if (value == DependencyProperty::UnsetValue()) {
        if (auto grid = elementDo.try_as<Controls::Grid>()) {
            if (auto value2 = elementDo.GetValue(property)) {
                auto className = winrt::get_class_name(value2);
                if (className ==
                        L"Windows.UI.Xaml.Controls."
                        L"ColumnDefinitionCollection" ||
                    className ==
                        L"Windows.UI.Xaml.Controls.RowDefinitionCollection") {
                    Wh_Log(L"Using GetValue workaround for %s",
                           className.c_str());
                    value = std::move(value2);
                }
            }
        }
    }

    if (value) {
        auto className = winrt::get_class_name(value);
        if (className == L"Windows.UI.Xaml.Data.BindingExpressionBase" ||
            className == L"Windows.UI.Xaml.Data.BindingExpression") {
            // BindingExpressionBase was observed to be returned for XAML
            // properties that were declared as following:
            //
            // <Border ... CornerRadius="{TemplateBinding CornerRadius}" />
            //
            // Calling SetValue with it fails with an error, so we won't be able
            // to use it to restore the value. As a workaround, we use
            // GetAnimationBaseValue to get the value.
            Wh_Log(L"ReadLocalValue returned %s, using GetAnimationBaseValue",
                   className.c_str());
            value = elementDo.GetAnimationBaseValue(property);
        }
    }

    Wh_Log(L"Read property value %s",
           value ? (value == DependencyProperty::UnsetValue()
                        ? L"(unset)"
                        : winrt::get_class_name(value).c_str())
                 : L"(null)");

    return value;
}

////////////////////////////////////////////////////////////////////////////////
// Noise generation
//
// Generates a tileable noise BMP in memory. Density controls the brightness
// distribution curve via a power function (lower density = sparser bright
// pixels). Opacity is handled downstream by the composition effect graph.
winrt::Windows::Storage::Streams::IRandomAccessStream CreateNoiseStream(
    float density) {
    // Cache the last stream to avoid regenerating when density hasn't changed.
    // The cached stream is never read directly; callers get independent clones
    // via CloneStream() so they don't share a seek cursor.
    thread_local float cachedDensity = std::numeric_limits<float>::quiet_NaN();
    thread_local winrt::Windows::Storage::Streams::InMemoryRandomAccessStream
        cachedStream{nullptr};

    if (density == cachedDensity && cachedStream) {
        return cachedStream.CloneStream();
    }

    // Use 256x256 to minimize visible tiling seams.
    constexpr int kSize = 256;
    constexpr DWORD kBpp = 32;
    constexpr DWORD rowSize = kSize * (kBpp / 8);
    constexpr DWORD dataSize = rowSize * kSize;

    BITMAPFILEHEADER fileHeader{
        .bfType = 0x4D42,  // "BM"
        .bfSize =
            sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dataSize,
        .bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER),
    };

    BITMAPINFOHEADER infoHeader{
        .biSize = sizeof(BITMAPINFOHEADER),
        .biWidth = kSize,
        .biHeight = kSize,
        .biPlanes = 1,
        .biBitCount = kBpp,
        .biSizeImage = dataSize,
    };

    std::vector<uint8_t> pixels(dataSize);

    // Precompute the density power curve as a lookup table so that
    // std::pow is called 256 times instead of once per pixel (65536).
    float safeDensity = std::clamp(density, 0.001f, 1.0f);
    float exponent = 1.0f / safeDensity;

    uint8_t lut[256];
    for (int i = 0; i < 256; i++) {
        lut[i] = static_cast<uint8_t>(std::pow(i / 255.0f, exponent) * 255.0f);
    }

    std::mt19937 rng(0);
    std::uniform_int_distribution<int> dist(0, 255);

    for (size_t i = 0; i < pixels.size(); i += 4) {
        uint8_t gray = lut[dist(rng)];

        // Fully opaque; opacity is applied downstream by ColorMatrixEffect.
        pixels[i] = gray;
        pixels[i + 1] = gray;
        pixels[i + 2] = gray;
        pixels[i + 3] = 255;
    }

    winrt::Windows::Storage::Streams::InMemoryRandomAccessStream stream;
    winrt::Windows::Storage::Streams::DataWriter writer(stream);
    writer.WriteBytes(winrt::array_view<const uint8_t>(
        reinterpret_cast<const uint8_t*>(&fileHeader), sizeof(fileHeader)));
    writer.WriteBytes(winrt::array_view<const uint8_t>(
        reinterpret_cast<const uint8_t*>(&infoHeader), sizeof(infoHeader)));
    writer.WriteBytes(pixels);
    writer.StoreAsync().get();
    writer.DetachStream();

    cachedStream = std::move(stream);
    cachedDensity = density;

    return cachedStream.CloneStream();
}

// Blur background implementation, copied from TranslucentTB.
////////////////////////////////////////////////////////////////////////////////
// clang-format off
template <> inline constexpr winrt::guid winrt::impl::guid_v<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>{
    winrt::impl::guid_v<winrt::Windows::Foundation::IPropertyValue>
};

typedef enum MY_D2D1_GAUSSIANBLUR_OPTIMIZATION
{
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_SPEED = 0,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED = 1,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY = 2,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_FORCE_DWORD = 0xffffffff

} MY_D2D1_GAUSSIANBLUR_OPTIMIZATION;

////////////////////////////////////////////////////////////////////////////////
// XamlBlurBrush.h
class XamlBlurBrush : public Media::XamlCompositionBrushBaseT<XamlBlurBrush>
{
public:
    XamlBlurBrush(UIElement element,
                  float blurAmount,
                  winrt::Windows::UI::Color tint,
                  std::optional<uint8_t> tintOpacity,
                  winrt::hstring tintThemeResourceKey,
                  std::optional<float> tintLuminosityOpacity,
                  std::optional<float> tintSaturation,
                  std::optional<float> noiseOpacity,
                  std::optional<float> noiseDensity,
                  std::optional<winrt::Windows::UI::Color> fallbackColor,
                  winrt::hstring fallbackThemeResourceKey);
    ~XamlBlurBrush();

    void OnConnected();
    void OnDisconnected();

private:
    void RefreshThemeTint();
    void RefreshFallbackColor();
    bool ShouldUseFallback() const;
    void RefreshBrush();
    wuc::CompositionBrush CreateEffectBrush();
    wuc::CompositionBrush CreateFallbackBrush();

    wuc::Compositor m_compositor;
    float m_blurAmount;
    winrt::Windows::UI::Color m_tint;
    std::optional<uint8_t> m_tintOpacity;
    winrt::hstring m_tintThemeResourceKey;
    std::optional<float> m_tintLuminosityOpacity;
    std::optional<float> m_tintSaturation;
    std::optional<float> m_noiseOpacity;
    std::optional<float> m_noiseDensity;
    std::optional<winrt::Windows::UI::Color> m_fallbackColor;
    winrt::hstring m_fallbackThemeResourceKey;
    Media::SolidColorBrush m_proxyBrush{nullptr};
    Media::SolidColorBrush m_fallbackProxyBrush{nullptr};
    winrt::weak_ref<FrameworkElement> m_weakProxyElement;
    winrt::hstring m_proxyKey;
    winrt::hstring m_fallbackProxyKey;
    winrt::Windows::UI::ViewManagement::UISettings m_uiSettings{nullptr};
    winrt::event_token m_advancedEffectsEnabledChangedToken{};
    winrt::event_token m_energySaverStatusChangedToken{};
    winrt::Windows::System::DispatcherQueue m_dispatcher{nullptr};
    HKEY m_powerKey{nullptr};
    HANDLE m_regNotifyEvent{nullptr};
    HANDLE m_regWaitHandle{nullptr};

    static void CALLBACK OnEnergySaverRegistryChanged(PVOID context,
                                                      BOOLEAN timerOrWaitFired);
};

////////////////////////////////////////////////////////////////////////////////
// windows.graphics.effects.interop.h
#ifndef BUILD_WINDOWS
namespace ABI {
#endif
namespace Windows {
namespace Graphics {
namespace Effects {

typedef interface IGraphicsEffectSource                         IGraphicsEffectSource;
typedef interface IGraphicsEffectD2D1Interop                    IGraphicsEffectD2D1Interop;


typedef enum GRAPHICS_EFFECT_PROPERTY_MAPPING
{
    GRAPHICS_EFFECT_PROPERTY_MAPPING_UNKNOWN,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORX,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORY,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORZ,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORW,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_RECT_TO_VECTOR4,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_RADIANS_TO_DEGREES,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLORMATRIX_ALPHA_MODE,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLOR_TO_VECTOR3,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLOR_TO_VECTOR4
} GRAPHICS_EFFECT_PROPERTY_MAPPING;

//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGraphicsEffectD2D1Interop
//
//  Synopsis:
//      An interface providing a Interop counterpart to IGraphicsEffect
//      and allowing for metadata queries.
//
//------------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE IGraphicsEffectD2D1Interop
DECLARE_INTERFACE_IID_(IGraphicsEffectD2D1Interop, IUnknown, "2FC57384-A068-44D7-A331-30982FCF7177")
{
    STDMETHOD(GetEffectId)(
        _Out_ GUID * id
        ) PURE;

    STDMETHOD(GetNamedPropertyMapping)(
        LPCWSTR name,
        _Out_ UINT * index,
        _Out_ GRAPHICS_EFFECT_PROPERTY_MAPPING * mapping
        ) PURE;

    STDMETHOD(GetPropertyCount)(
        _Out_ UINT * count
        ) PURE;

    STDMETHOD(GetProperty)(
        UINT index,
        _Outptr_ winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue> ** value
        ) PURE;

    STDMETHOD(GetSource)(
        UINT index,
        _Outptr_ IGraphicsEffectSource ** source
        ) PURE;

    STDMETHOD(GetSourceCount)(
        _Out_ UINT * count
        ) PURE;
};


} // namespace Effects
} // namespace Graphics
} // namespace Windows
#ifndef BUILD_WINDOWS
} // namespace ABI
#endif

template <> inline constexpr winrt::guid winrt::impl::guid_v<ABI::Windows::Graphics::Effects::IGraphicsEffectD2D1Interop>{
    0x2FC57384, 0xA068, 0x44D7, { 0xA3, 0x31, 0x30, 0x98, 0x2F, 0xCF, 0x71, 0x77 }
};


////////////////////////////////////////////////////////////////////////////////
// CompositeEffect.h
struct CompositeEffect : winrt::implements<CompositeEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop>
{
public:
    // IGraphicsEffectD2D1Interop
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override;
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override;
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override;
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override;

    // IGraphicsEffect
    winrt::hstring Name();
    void Name(winrt::hstring name);

    std::vector<wge::IGraphicsEffectSource> Sources;
    D2D1_COMPOSITE_MODE Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;
private:
    winrt::hstring m_name = L"CompositeEffect";
};

////////////////////////////////////////////////////////////////////////////////
// CompositeEffect.cpp
HRESULT CompositeEffect::GetEffectId(GUID* id) noexcept
{
    if (id == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *id = CLSID_D2D1Composite;
    return S_OK;
}

HRESULT CompositeEffect::GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept
{
    if (index == nullptr || mapping == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    const std::wstring_view nameView(name);
    if (nameView == L"Mode")
    {
        *index = D2D1_COMPOSITE_PROP_MODE;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }

    return E_INVALIDARG;
}

HRESULT CompositeEffect::GetPropertyCount(UINT* count) noexcept
{
    if (count == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *count = 1;
    return S_OK;
}

HRESULT CompositeEffect::GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept try
{
    if (value == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    switch (index)
    {
        case D2D1_COMPOSITE_PROP_MODE:
            *value = wf::PropertyValue::CreateUInt32((UINT32)Mode).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        default:
            return E_BOUNDS;
    }

    return S_OK;
}
catch (...)
{
    return winrt::to_hresult();
}

HRESULT CompositeEffect::GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept try
{
    if (source == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    winrt::copy_to_abi(Sources.at(index), *reinterpret_cast<void**>(source));
    return S_OK;
}
catch (...)
{
    return winrt::to_hresult();
}

HRESULT CompositeEffect::GetSourceCount(UINT* count) noexcept
{
    if (count == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *count = static_cast<UINT>(Sources.size());
    return S_OK;
}

winrt::hstring CompositeEffect::Name()
{
    return m_name;
}

void CompositeEffect::Name(winrt::hstring name)
{
    m_name = name;
}

////////////////////////////////////////////////////////////////////////////////
// FloodEffect.h
struct FloodEffect : winrt::implements<FloodEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop>
{
public:
    // IGraphicsEffectD2D1Interop
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override;
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override;
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override;
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override;

    // IGraphicsEffect
    winrt::hstring Name();
    void Name(winrt::hstring name);

    winrt::Windows::UI::Color Color{};
private:
    winrt::hstring m_name = L"FloodEffect";
};

////////////////////////////////////////////////////////////////////////////////
// FloodEffect.cpp
HRESULT FloodEffect::GetEffectId(GUID* id) noexcept
{
    if (id == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *id = CLSID_D2D1Flood;
    return S_OK;
}

HRESULT FloodEffect::GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept
{
    if (index == nullptr || mapping == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    const std::wstring_view nameView(name);
    if (nameView == L"Color")
    {
        *index = D2D1_FLOOD_PROP_COLOR;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }

    return E_INVALIDARG;
}

HRESULT FloodEffect::GetPropertyCount(UINT* count) noexcept
{
    if (count == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *count = 1;
    return S_OK;
}

HRESULT FloodEffect::GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept try
{
    if (value == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    switch (index)
    {
        case D2D1_FLOOD_PROP_COLOR:
            *value = wf::PropertyValue::CreateSingleArray({
                Color.R / 255.0f,
                Color.G / 255.0f,
                Color.B / 255.0f,
                Color.A / 255.0f,
            }).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        default:
            return E_BOUNDS;
    }

    return S_OK;
}
catch (...)
{
    return winrt::to_hresult();
}

HRESULT FloodEffect::GetSource(UINT, awge::IGraphicsEffectSource** source) noexcept
{
    if (source == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    return E_BOUNDS;
}

HRESULT FloodEffect::GetSourceCount(UINT* count) noexcept
{
    if (count == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *count = 0;
    return S_OK;
}

winrt::hstring FloodEffect::Name()
{
    return m_name;
}

void FloodEffect::Name(winrt::hstring name)
{
    m_name = name;
}

////////////////////////////////////////////////////////////////////////////////
// BorderEffect.h
struct BorderEffect : winrt::implements<BorderEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop>
{
public:
    // IGraphicsEffectD2D1Interop
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override;
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override;
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override;
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override;

    // IGraphicsEffect
    winrt::hstring Name();
    void Name(winrt::hstring name);

    wge::IGraphicsEffectSource Source{nullptr};
    D2D1_BORDER_EDGE_MODE ExtendX = D2D1_BORDER_EDGE_MODE_WRAP;
    D2D1_BORDER_EDGE_MODE ExtendY = D2D1_BORDER_EDGE_MODE_WRAP;
private:
    winrt::hstring m_name = L"BorderEffect";
};

////////////////////////////////////////////////////////////////////////////////
// BorderEffect.cpp
HRESULT BorderEffect::GetEffectId(GUID* id) noexcept
{
    if (!id)
    {
        return E_INVALIDARG;
    }

    *id = CLSID_D2D1Border;
    return S_OK;
}

HRESULT BorderEffect::GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept
{
    if (!index || !mapping)
    {
        return E_INVALIDARG;
    }

    const std::wstring_view nameView(name);
    if (nameView == L"ExtendX")
    {
        *index = D2D1_BORDER_PROP_EDGE_MODE_X;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }

    if (nameView == L"ExtendY")
    {
        *index = D2D1_BORDER_PROP_EDGE_MODE_Y;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }

    return E_INVALIDARG;
}

HRESULT BorderEffect::GetPropertyCount(UINT* count) noexcept
{
    if (!count)
    {
        return E_INVALIDARG;
    }

    *count = 2;
    return S_OK;
}

HRESULT BorderEffect::GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept try
{
    if (!value)
    {
        return E_INVALIDARG;
    }

    switch (index)
    {
        case D2D1_BORDER_PROP_EDGE_MODE_X:
            *value = wf::PropertyValue::CreateUInt32((UINT32)ExtendX).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        case D2D1_BORDER_PROP_EDGE_MODE_Y:
            *value = wf::PropertyValue::CreateUInt32((UINT32)ExtendY).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        default:
            return E_BOUNDS;
    }

    return S_OK;
}
catch (...)
{
    return winrt::to_hresult();
}

HRESULT BorderEffect::GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept
{
    if (!source)
    {
        return E_INVALIDARG;
    }

    if (index == 0 && Source)
    {
        winrt::copy_to_abi(Source, *reinterpret_cast<void**>(source));
        return S_OK;
    }

    return E_BOUNDS;
}

HRESULT BorderEffect::GetSourceCount(UINT* count) noexcept
{
    if (!count)
    {
        return E_INVALIDARG;
    }

    *count = 1;
    return S_OK;
}

winrt::hstring BorderEffect::Name()
{
    return m_name;
}

void BorderEffect::Name(winrt::hstring name)
{
    m_name = name;
}

////////////////////////////////////////////////////////////////////////////////
// GaussianBlurEffect.h
struct GaussianBlurEffect : winrt::implements<GaussianBlurEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop>
{
public:
    // IGraphicsEffectD2D1Interop
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override;
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override;
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override;
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override;

    // IGraphicsEffect
    winrt::hstring Name();
    void Name(winrt::hstring name);

    wge::IGraphicsEffectSource Source;

    float BlurAmount = 3.0f;
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION Optimization = MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED;
    D2D1_BORDER_MODE BorderMode = D2D1_BORDER_MODE_SOFT;
private:
    winrt::hstring m_name = L"GaussianBlurEffect";
};

////////////////////////////////////////////////////////////////////////////////
// GaussianBlurEffect.cpp
HRESULT GaussianBlurEffect::GetEffectId(GUID* id) noexcept
{
    if (id == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *id = CLSID_D2D1GaussianBlur;
    return S_OK;
}

HRESULT GaussianBlurEffect::GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept
{
    if (index == nullptr || mapping == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    const std::wstring_view nameView(name);
    if (nameView == L"BlurAmount")
    {
        *index = D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }
    else if (nameView == L"Optimization")
    {
        *index = D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }
    else if (nameView == L"BorderMode")
    {
        *index = D2D1_GAUSSIANBLUR_PROP_BORDER_MODE;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }

    return E_INVALIDARG;
}

HRESULT GaussianBlurEffect::GetPropertyCount(UINT* count) noexcept
{
    if (count == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *count = 3;
    return S_OK;
}

HRESULT GaussianBlurEffect::GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept try
{
    if (value == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    switch (index)
    {
        case D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION:
            *value = wf::PropertyValue::CreateSingle(BlurAmount).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        case D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION:
            *value = wf::PropertyValue::CreateUInt32((UINT32)Optimization).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        case D2D1_GAUSSIANBLUR_PROP_BORDER_MODE:
            *value = wf::PropertyValue::CreateUInt32((UINT32)BorderMode).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        default:
            return E_BOUNDS;
    }

    return S_OK;
}
catch (...)
{
    return winrt::to_hresult();
}

HRESULT GaussianBlurEffect::GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept
{
    if (source == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    if (index == 0)
    {
        winrt::copy_to_abi(Source, *reinterpret_cast<void**>(source));
        return S_OK;
    }
    else
    {
        return E_BOUNDS;
    }
}

HRESULT GaussianBlurEffect::GetSourceCount(UINT* count) noexcept
{
    if (count == nullptr) [[unlikely]]
    {
        return E_INVALIDARG;
    }

    *count = 1;
    return S_OK;
}

winrt::hstring GaussianBlurEffect::Name()
{
    return m_name;
}

void GaussianBlurEffect::Name(winrt::hstring name)
{
    m_name = name;
}

////////////////////////////////////////////////////////////////////////////////
// ColorMatrixEffect.h
struct ColorMatrixEffect : winrt::implements<ColorMatrixEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop>
{
public:
    // IGraphicsEffectD2D1Interop
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override;
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override;
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override;
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override;
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override;

    // IGraphicsEffect
    winrt::hstring Name();
    void Name(winrt::hstring name);

    wge::IGraphicsEffectSource Source{nullptr};

    // D2D1_MATRIX_5X4_F: 5 rows x 4 columns (20 floats), initialized to identity.
    float Matrix[20] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
        0, 0, 0, 0,
    };

    uint32_t AlphaMode = D2D1_COLORMATRIX_ALPHA_MODE_PREMULTIPLIED;
    bool ClampOutput = false;
private:
    winrt::hstring m_name = L"ColorMatrixEffect";
};

////////////////////////////////////////////////////////////////////////////////
// ColorMatrixEffect.cpp
HRESULT ColorMatrixEffect::GetEffectId(GUID* id) noexcept
{
    if (!id)
    {
        return E_INVALIDARG;
    }

    *id = CLSID_D2D1ColorMatrix;
    return S_OK;
}

HRESULT ColorMatrixEffect::GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept
{
    if (!index || !mapping)
    {
        return E_INVALIDARG;
    }

    const std::wstring_view nameView(name);
    if (nameView == L"ColorMatrix")
    {
        *index = D2D1_COLORMATRIX_PROP_COLOR_MATRIX;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }

    if (nameView == L"AlphaMode")
    {
        *index = D2D1_COLORMATRIX_PROP_ALPHA_MODE;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }

    if (nameView == L"ClampOutput")
    {
        *index = D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;

        return S_OK;
    }

    return E_INVALIDARG;
}

HRESULT ColorMatrixEffect::GetPropertyCount(UINT* count) noexcept
{
    if (!count)
    {
        return E_INVALIDARG;
    }

    *count = 3;
    return S_OK;
}

HRESULT ColorMatrixEffect::GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept try
{
    if (!value)
    {
        return E_INVALIDARG;
    }

    switch (index)
    {
        case D2D1_COLORMATRIX_PROP_COLOR_MATRIX:
            *value = wf::PropertyValue::CreateSingleArray(
                winrt::array_view<const float>(Matrix, Matrix + 20)
            ).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        case D2D1_COLORMATRIX_PROP_ALPHA_MODE:
            *value = wf::PropertyValue::CreateUInt32(AlphaMode).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        case D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT:
            *value = wf::PropertyValue::CreateBoolean(ClampOutput).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            break;

        default:
            return E_BOUNDS;
    }

    return S_OK;
}
catch (...)
{
    return winrt::to_hresult();
}

HRESULT ColorMatrixEffect::GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept
{
    if (!source)
    {
        return E_INVALIDARG;
    }

    if (index == 0 && Source)
    {
        winrt::copy_to_abi(Source, *reinterpret_cast<void**>(source));
        return S_OK;
    }

    return E_BOUNDS;
}

HRESULT ColorMatrixEffect::GetSourceCount(UINT* count) noexcept
{
    if (!count)
    {
        return E_INVALIDARG;
    }

    *count = 1;
    return S_OK;
}

winrt::hstring ColorMatrixEffect::Name()
{
    return m_name;
}

void ColorMatrixEffect::Name(winrt::hstring name)
{
    m_name = name;
}

////////////////////////////////////////////////////////////////////////////////
// XamlBlurBrush.cpp
XamlBlurBrush::XamlBlurBrush(UIElement element,
                             float blurAmount,
                             winrt::Windows::UI::Color tint,
                             std::optional<uint8_t> tintOpacity,
                             winrt::hstring tintThemeResourceKey,
                             std::optional<float> tintLuminosityOpacity,
                             std::optional<float> tintSaturation,
                             std::optional<float> noiseOpacity,
                             std::optional<float> noiseDensity,
                             std::optional<winrt::Windows::UI::Color> fallbackColor,
                             winrt::hstring fallbackThemeResourceKey) :
    m_compositor(wuxh::ElementCompositionPreview::GetElementVisual(element)
                     .Compositor()),
    m_blurAmount(blurAmount),
    m_tint(tint),
    m_tintOpacity(tintOpacity),
    m_tintThemeResourceKey(std::move(tintThemeResourceKey)),
    m_tintLuminosityOpacity(tintLuminosityOpacity),
    m_tintSaturation(tintSaturation),
    m_noiseOpacity(noiseOpacity),
    m_noiseDensity(noiseDensity),
    m_fallbackColor(fallbackColor),
    m_fallbackThemeResourceKey(std::move(fallbackThemeResourceKey))
{
    auto fe = element.try_as<FrameworkElement>();

    auto createProxy = [&](winrt::hstring const& themeResourceKey)
        -> Media::SolidColorBrush
    {
        if (!fe)
        {
            return nullptr;
        }
        std::wstring xaml =
            L"<SolidColorBrush"
            L" xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/"
            L"presentation\""
            L" Color=\"{ThemeResource " +
            std::wstring(themeResourceKey) + L"}\"/>";
        try
        {
            return Markup::XamlReader::Load(winrt::hstring(xaml))
                .try_as<Media::SolidColorBrush>();
        }
        catch (winrt::hresult_error const& ex)
        {
            Wh_Log(L"Failed to create proxy brush: %08X", ex.code());
            return nullptr;
        }
    };

    static std::atomic<uint64_t> s_proxyCounter{0};

    if (!m_tintThemeResourceKey.empty())
    {
        if (auto proxyBrush = createProxy(m_tintThemeResourceKey))
        {
            auto proxyKey = winrt::hstring(
                L"__WhBlurProxy_" +
                std::to_wstring(++s_proxyCounter));
            fe.Resources().Insert(
                winrt::box_value(proxyKey), proxyBrush);
            m_proxyBrush = proxyBrush;
            m_weakProxyElement = winrt::make_weak(fe);
            m_proxyKey = proxyKey;
            Wh_Log(L"Tint proxy brush for %s inserted with key %s",
                   m_tintThemeResourceKey.c_str(),
                   proxyKey.c_str());
        }

        if (m_proxyBrush)
        {
            m_proxyBrush.RegisterPropertyChangedCallback(
                Media::SolidColorBrush::ColorProperty(),
                [weakThis = get_weak()](auto&&, auto&&)
                {
                    if (auto self = weakThis.get())
                    {
                        Wh_Log(L"Tint theme color changed");
                        self->RefreshBrush();
                    }
                });
        }
    }

    if (!m_fallbackThemeResourceKey.empty())
    {
        if (auto proxyBrush = createProxy(m_fallbackThemeResourceKey))
        {
            auto proxyKey = winrt::hstring(
                L"__WhBlurFallbackProxy_" +
                std::to_wstring(++s_proxyCounter));
            fe.Resources().Insert(
                winrt::box_value(proxyKey), proxyBrush);
            m_fallbackProxyBrush = proxyBrush;
            if (!m_weakProxyElement.get())
            {
                m_weakProxyElement = winrt::make_weak(fe);
            }
            m_fallbackProxyKey = proxyKey;
            Wh_Log(L"Fallback proxy brush for %s inserted with key %s",
                   m_fallbackThemeResourceKey.c_str(),
                   proxyKey.c_str());
        }

        if (m_fallbackProxyBrush)
        {
            m_fallbackProxyBrush.RegisterPropertyChangedCallback(
                Media::SolidColorBrush::ColorProperty(),
                [weakThis = get_weak()](auto&&, auto&&)
                {
                    if (auto self = weakThis.get())
                    {
                        Wh_Log(L"Fallback theme color changed");
                        self->RefreshBrush();
                    }
                });
        }
    }

    if (m_fallbackColor || !m_fallbackThemeResourceKey.empty())
    {
        m_dispatcher =
            winrt::Windows::System::DispatcherQueue::GetForCurrentThread();

        try
        {
            m_uiSettings = winrt::Windows::UI::ViewManagement::UISettings();
            auto dispatcher = m_dispatcher;
            m_advancedEffectsEnabledChangedToken =
                m_uiSettings.AdvancedEffectsEnabledChanged(
                    [weakThis = get_weak(), dispatcher](auto&&, auto&&)
                    {
                        dispatcher.TryEnqueue([weakThis]
                        {
                            if (auto self = weakThis.get())
                            {
                                Wh_Log(L"AdvancedEffectsEnabled changed");
                                self->RefreshBrush();
                            }
                        });
                    });
            m_energySaverStatusChangedToken =
                winrt::Windows::System::Power::PowerManager::
                    EnergySaverStatusChanged(
                        [weakThis = get_weak(), dispatcher](auto&&, auto&&)
                        {
                            dispatcher.TryEnqueue([weakThis]
                            {
                                if (auto self = weakThis.get())
                                {
                                    Wh_Log(L"EnergySaverStatus changed");
                                    self->RefreshBrush();
                                }
                            });
                        });
        }
        catch (winrt::hresult_error const& ex)
        {
            Wh_Log(L"Failed to register fallback state listeners: %08X",
                   ex.code());
        }

        // Watch HKLM\SYSTEM\CurrentControlSet\Control\Power for changes to
        // EnergySaverState. On Windows 11 24H2+ neither the WinRT
        // PowerManager.EnergySaverStatus property nor the Win32
        // GetSystemPowerStatus.SystemStatusFlag flag reliably reflects the
        // "Always use energy saver" setting; the registry value is the only
        // signal that updates in that case. The wait callback re-arms the
        // notification and posts a brush refresh on the UI thread.
        LONG regStatus = RegOpenKeyExW(
            HKEY_LOCAL_MACHINE,
            L"SYSTEM\\CurrentControlSet\\Control\\Power", 0, KEY_NOTIFY,
            &m_powerKey);
        if (regStatus == ERROR_SUCCESS)
        {
            m_regNotifyEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
            if (m_regNotifyEvent)
            {
                regStatus = RegNotifyChangeKeyValue(m_powerKey, FALSE,
                                                   REG_NOTIFY_CHANGE_LAST_SET,
                                                   m_regNotifyEvent, TRUE);
                if (regStatus == ERROR_SUCCESS)
                {
                    if (!RegisterWaitForSingleObject(
                            &m_regWaitHandle, m_regNotifyEvent,
                            OnEnergySaverRegistryChanged, this, INFINITE,
                            WT_EXECUTEINWAITTHREAD))
                    {
                        Wh_Log(L"RegisterWaitForSingleObject failed: %lu",
                               GetLastError());
                        m_regWaitHandle = nullptr;
                    }
                }
                else
                {
                    Wh_Log(L"RegNotifyChangeKeyValue failed: %ld", regStatus);
                    CloseHandle(m_regNotifyEvent);
                    m_regNotifyEvent = nullptr;
                    RegCloseKey(m_powerKey);
                    m_powerKey = nullptr;
                }
            }
            else
            {
                Wh_Log(L"CreateEvent failed: %lu", GetLastError());
                RegCloseKey(m_powerKey);
                m_powerKey = nullptr;
            }
        }
        else
        {
            Wh_Log(L"RegOpenKeyEx for Power key failed: %ld", regStatus);
        }
    }
}

void CALLBACK XamlBlurBrush::OnEnergySaverRegistryChanged(PVOID context,
                                                          BOOLEAN)
{
    auto* self = static_cast<XamlBlurBrush*>(context);

    // Re-arm before dispatching so a rapid second change isn't dropped.
    if (self->m_powerKey && self->m_regNotifyEvent)
    {
        RegNotifyChangeKeyValue(self->m_powerKey, FALSE,
                                REG_NOTIFY_CHANGE_LAST_SET,
                                self->m_regNotifyEvent, TRUE);
    }

    if (self->m_dispatcher)
    {
        auto weakThis = self->get_weak();
        self->m_dispatcher.TryEnqueue([weakThis]
        {
            if (auto strongThis = weakThis.get())
            {
                Wh_Log(L"Power registry key changed, refreshing brush");
                strongThis->RefreshBrush();
            }
        });
    }
}

XamlBlurBrush::~XamlBlurBrush()
{
    // Tear down the registry watch first so no more callbacks can fire while
    // we close the underlying handles.
    if (m_regWaitHandle)
    {
        UnregisterWaitEx(m_regWaitHandle, INVALID_HANDLE_VALUE);
        m_regWaitHandle = nullptr;
    }
    if (m_regNotifyEvent)
    {
        CloseHandle(m_regNotifyEvent);
        m_regNotifyEvent = nullptr;
    }
    if (m_powerKey)
    {
        RegCloseKey(m_powerKey);
        m_powerKey = nullptr;
    }

    if (m_uiSettings && m_advancedEffectsEnabledChangedToken.value)
    {
        try
        {
            m_uiSettings.AdvancedEffectsEnabledChanged(
                m_advancedEffectsEnabledChangedToken);
        }
        catch (...)
        {
            Wh_Log(L"Error %08X", winrt::to_hresult());
        }
    }

    if (m_energySaverStatusChangedToken.value)
    {
        try
        {
            winrt::Windows::System::Power::PowerManager::
                EnergySaverStatusChanged(m_energySaverStatusChangedToken);
        }
        catch (...)
        {
            Wh_Log(L"Error %08X", winrt::to_hresult());
        }
    }

    if (auto element = m_weakProxyElement.get())
    {
        try
        {
            if (!m_proxyKey.empty())
            {
                element.Resources().Remove(winrt::box_value(m_proxyKey));
            }
            if (!m_fallbackProxyKey.empty())
            {
                element.Resources().Remove(
                    winrt::box_value(m_fallbackProxyKey));
            }
        }
        catch (...)
        {
            HRESULT hr = winrt::to_hresult();
            Wh_Log(L"Error %08X", hr);
        }
    }
}

void XamlBlurBrush::OnConnected()
{
    if (!CompositionBrush())
    {
        RefreshThemeTint();
        RefreshFallbackColor();

        CompositionBrush(ShouldUseFallback() ? CreateFallbackBrush()
                                             : CreateEffectBrush());
    }
}

wuc::CompositionBrush XamlBlurBrush::CreateFallbackBrush()
{
    return m_compositor.CreateColorBrush(m_fallbackColor.value_or(m_tint));
}

wuc::CompositionBrush XamlBlurBrush::CreateEffectBrush()
{
    auto backdropBrush = m_compositor.CreateBackdropBrush();

    // Rec. 709 luma coefficients, used for saturation and luminosity.
    constexpr float kLumaR = 0.2126f;
    constexpr float kLumaG = 0.7152f;
    constexpr float kLumaB = 0.0722f;

    // 1. Blur
    auto blurEffect = winrt::make_self<GaussianBlurEffect>();
    blurEffect->Source = wuc::CompositionEffectSourceParameter(L"backdrop");
    blurEffect->BlurAmount = m_blurAmount;
    blurEffect->Name(L"BlurEffect");

    wge::IGraphicsEffectSource topOfStack = *blurEffect;

    // 2. Saturation (optional)
    if (m_tintSaturation && *m_tintSaturation != 1.0f)
    {
        float s = std::max(*m_tintSaturation, 0.0f);
        float invS = 1.0f - s;

        auto satMatrix = winrt::make_self<ColorMatrixEffect>();
        satMatrix->Source = topOfStack;

        // Standard saturation matrix: lerp between luminance and identity.
        auto& m = satMatrix->Matrix;
        m[0]  = invS * kLumaR + s; m[1]  = invS * kLumaR;     m[2]  = invS * kLumaR;     m[3]  = 0.0f;
        m[4]  = invS * kLumaG;     m[5]  = invS * kLumaG + s; m[6]  = invS * kLumaG;     m[7]  = 0.0f;
        m[8]  = invS * kLumaB;     m[9]  = invS * kLumaB;     m[10] = invS * kLumaB + s; m[11] = 0.0f;
        m[12] = 0.0f;              m[13] = 0.0f;              m[14] = 0.0f;              m[15] = 1.0f;

        satMatrix->Name(L"SaturationEffect");
        topOfStack = *satMatrix;
    }

    // 3. Luminosity (optional) - shifts pixel luminance towards the tint's
    // luminance, blended by the opacity factor.
    if (m_tintLuminosityOpacity && *m_tintLuminosityOpacity > 0.0f)
    {
        float op = std::clamp(*m_tintLuminosityOpacity, 0.0f, 1.0f);

        float tintLum = (m_tint.R / 255.0f) * kLumaR +
                        (m_tint.G / 255.0f) * kLumaG +
                        (m_tint.B / 255.0f) * kLumaB;

        auto lumMatrix = winrt::make_self<ColorMatrixEffect>();
        lumMatrix->Source = topOfStack;

        auto& m = lumMatrix->Matrix;
        m[0]  = 1.0f - (kLumaR * op); m[1]  = -(kLumaR * op);       m[2]  = -(kLumaR * op);       m[3]  = 0.0f;
        m[4]  = -(kLumaG * op);       m[5]  = 1.0f - (kLumaG * op); m[6]  = -(kLumaG * op);       m[7]  = 0.0f;
        m[8]  = -(kLumaB * op);       m[9]  = -(kLumaB * op);       m[10] = 1.0f - (kLumaB * op); m[11] = 0.0f;
        m[12] = 0.0f;                 m[13] = 0.0f;                 m[14] = 0.0f;                 m[15] = 1.0f;
        m[16] = tintLum * op;         m[17] = tintLum * op;         m[18] = tintLum * op;         m[19] = 0.0f;

        lumMatrix->Name(L"LuminosityBlend");
        topOfStack = *lumMatrix;
    }

    // 4. Noise overlay (optional) - procedural tiled noise with adjustable
    // density and opacity.
    wuc::CompositionSurfaceBrush noiseBrush{nullptr};
    if (m_noiseOpacity && *m_noiseOpacity > 0.0f)
    {
        float density = m_noiseDensity.value_or(1.0f);

        auto stream = CreateNoiseStream(density);
        auto surface =
            Media::LoadedImageSurface::StartLoadFromStream(stream);
        noiseBrush = m_compositor.CreateSurfaceBrush(surface);
        noiseBrush.Stretch(wuc::CompositionStretch::None);

        // Tile via border effect (wrap mode).
        auto borderEffect = winrt::make_self<BorderEffect>();
        borderEffect->Source =
            wuc::CompositionEffectSourceParameter(L"NoiseSource");

        // Scale all channels by opacity for premultiplied blending.
        float nOp = std::clamp(*m_noiseOpacity, 0.0f, 1.0f);

        auto opacityEffect = winrt::make_self<ColorMatrixEffect>();
        opacityEffect->Source = *borderEffect;
        // Matrix: Scale all channels by opacity (for premultiplied blending).
        opacityEffect->Matrix[0] = nOp;
        opacityEffect->Matrix[5] = nOp;
        opacityEffect->Matrix[10] = nOp;
        opacityEffect->Matrix[15] = nOp;
        opacityEffect->Name(L"NoiseOpacityEffect");

        // Composite noise over the current stack.
        auto noiseComposite = winrt::make_self<CompositeEffect>();
        noiseComposite->Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;
        noiseComposite->Sources.push_back(topOfStack);
        noiseComposite->Sources.push_back(*opacityEffect);
        noiseComposite->Name(L"NoiseComposite");
        topOfStack = *noiseComposite;
    }

    // 5. Tint (flood color composited over the stack).
    auto floodEffect = winrt::make_self<FloodEffect>();
    floodEffect->Color = m_tint;
    floodEffect->Name(L"FloodEffect");

    auto compositeEffect = winrt::make_self<CompositeEffect>();
    compositeEffect->Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;
    compositeEffect->Sources.push_back(topOfStack);
    compositeEffect->Sources.push_back(*floodEffect);

    auto factory = m_compositor.CreateEffectFactory(*compositeEffect);
    auto brush = factory.CreateBrush();

    brush.SetSourceParameter(L"backdrop", backdropBrush);

    // Bind the noise brush if we created one.
    if (noiseBrush)
    {
        brush.SetSourceParameter(L"NoiseSource", noiseBrush);
    }

    return brush;
}

void XamlBlurBrush::OnDisconnected()
{
    if (const auto brush = CompositionBrush())
    {
        brush.Close();
        CompositionBrush(nullptr);
    }
}

void XamlBlurBrush::RefreshThemeTint()
{
    if (!m_proxyBrush)
    {
        return;
    }

    m_tint = m_proxyBrush.Color();
    if (m_tintOpacity)
    {
        m_tint.A = *m_tintOpacity;
    }
}

void XamlBlurBrush::RefreshFallbackColor()
{
    if (!m_fallbackProxyBrush)
    {
        return;
    }

    m_fallbackColor = m_fallbackProxyBrush.Color();
}

bool XamlBlurBrush::ShouldUseFallback() const
{
    if (!m_fallbackColor && m_fallbackThemeResourceKey.empty())
    {
        return false;
    }

    // The HKLM\SYSTEM\CurrentControlSet\Control\Power\EnergySaverState value
    // is the only signal that consistently reflects "Always use energy saver"
    // on Windows 11 24H2+; the WinRT and Win32 power-status APIs can stay
    // stuck in the off state on those builds. 1 = enabled, 2 = disabled.
    bool energySaverActive = false;
    HKEY key{};
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                      L"SYSTEM\\CurrentControlSet\\Control\\Power", 0,
                      KEY_QUERY_VALUE, &key) == ERROR_SUCCESS)
    {
        DWORD value = 0;
        DWORD type = 0;
        DWORD size = sizeof(value);
        if (RegQueryValueExW(key, L"EnergySaverState", nullptr, &type,
                             reinterpret_cast<LPBYTE>(&value),
                             &size) == ERROR_SUCCESS &&
            type == REG_DWORD)
        {
            energySaverActive = (value == 1);
        }
        RegCloseKey(key);
    }

    // Backup for older Windows where the registry value above isn't populated.
    if (!energySaverActive)
    {
        SYSTEM_POWER_STATUS powerStatus{};
        if (GetSystemPowerStatus(&powerStatus) &&
            powerStatus.SystemStatusFlag != 0)
        {
            energySaverActive = true;
        }
    }

    bool advancedEffectsOff = false;
    if (m_uiSettings)
    {
        try
        {
            advancedEffectsOff = !m_uiSettings.AdvancedEffectsEnabled();
        }
        catch (...)
        {
            Wh_Log(L"AdvancedEffectsEnabled query failed: %08X",
                   winrt::to_hresult());
        }
    }

    return energySaverActive || advancedEffectsOff;
}

void XamlBlurBrush::RefreshBrush()
{
    if (const auto brush = CompositionBrush())
    {
        brush.Close();
        CompositionBrush(nullptr);
        OnConnected();
    }
}

// clang-format on
////////////////////////////////////////////////////////////////////////////////

// Helper functions for tracking and retrying failed ImageBrush loads.

// Reports true if the query itself fails, as a retry which turns out to be
// pointless is harmless, while skipping a necessary one leaves images missing.
bool HasInternetAccess() {
    try {
        auto profile = winrt::Windows::Networking::Connectivity::
            NetworkInformation::GetInternetConnectionProfile();
        return profile && profile.GetNetworkConnectivityLevel() ==
                              winrt::Windows::Networking::Connectivity::
                                  NetworkConnectivityLevel::InternetAccess;
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        return true;
    }
}

void StartImageBrushRetry(const std::shared_ptr<TrackedImageBrush>& tracked) {
    auto brush = tracked->brush.get();
    if (!brush) {
        return;
    }

    Wh_Log(L"Retrying image load for: %s", tracked->uri.RawUri().c_str());

    tracked->lastRetryTick = GetTickCount64();
    tracked->retryCount++;

    try {
        Media::Imaging::BitmapImage retryImage;
        // Bypass the XAML image cache: a retry is only needed when what the
        // cache holds for the URI is a failed or missing image.
        retryImage.CreateOptions(
            tracked->createOptions |
            Media::Imaging::BitmapCreateOptions::IgnoreImageCache);
        retryImage.DecodePixelType(tracked->decodePixelType);
        retryImage.DecodePixelWidth(tracked->decodePixelWidth);
        retryImage.DecodePixelHeight(tracked->decodePixelHeight);
        retryImage.AutoPlay(tracked->autoPlay);
        retryImage.UriSource(tracked->uri);

        // A BitmapImage is loaded by the framework as part of the tree it's
        // used in, so it has to be assigned to the brush for anything to
        // happen. A new object rather than the failed one, since reassigning
        // the same URI to a BitmapImage doesn't reload it. The brush's own
        // ImageOpened and ImageFailed report how this attempt went.
        brush.ImageSource(retryImage);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }
}

void RetryFailedImageLoadsOnCurrentThread() {
    if (GetCurrentThreadId() != g_targetThreadId) {
        return;
    }

    Wh_Log(L"Retrying failed image loads on current thread");

    auto& brushes = g_trackedImageBrushesForThread.brushes;

    std::erase_if(brushes,
                  [](const auto& tracked) { return !tracked->brush.get(); });

    // Copy the entries before iterating: a retry can raise ImageBrush events,
    // and their handlers modify the entries.
    std::vector<std::shared_ptr<TrackedImageBrush>> snapshot(brushes.begin(),
                                                             brushes.end());

    ULONGLONG tick = GetTickCount64();

    for (const auto& tracked : snapshot) {
        if (tracked->loaded) {
            continue;
        }

        if (tracked->lastRetryTick) {
            ULONGLONG sinceLastRetry = tick - tracked->lastRetryTick;
            if (sinceLastRetry >= kImageRetryMaxDelayMs) {
                tracked->retryCount = 0;
            } else {
                ULONGLONG delay = kImageRetryBaseDelayMs
                                  << std::clamp(tracked->retryCount - 1, 0,
                                                kImageRetryMaxBackoffShift);
                if (sinceLastRetry < delay) {
                    continue;
                }
            }
        }

        if (tracked->retryCount >= kImageRetryMaxCount) {
            continue;
        }

        StartImageBrushRetry(tracked);
    }
}

// Retries once the network status events stop coming, since the connectivity a
// single transition ends up at isn't there yet when the first of them arrives.
void ScheduleImageLoadRetryOnCurrentThread() {
    if (GetCurrentThreadId() != g_targetThreadId) {
        return;
    }

    auto& timer = g_trackedImageBrushesForThread.retryDebounceTimer;

    try {
        if (!timer) {
            auto dispatcher = g_trackedImageBrushesForThread.dispatcher;
            if (!dispatcher) {
                return;
            }

            timer = dispatcher.CreateTimer();
            timer.Interval(std::chrono::milliseconds{kNetworkChangeDebounceMs});
            timer.IsRepeating(false);
            g_trackedImageBrushesForThread.retryDebounceTimerTickRevoker =
                timer.Tick(
                    winrt::auto_revoke,
                    [](winrt::Windows::System::DispatcherQueueTimer const&,
                       winrt::Windows::Foundation::IInspectable const&) {
                        RetryFailedImageLoadsOnCurrentThread();
                    });
        }

        timer.Stop();
        timer.Start();
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }
}

void ScheduleImageLoadRetryOnAllUiThreads() {
    // Losing connectivity raises a network status event just like gaining it
    // does, and there's nothing to retry with no internet access.
    if (!HasInternetAccess()) {
        Wh_Log(L"No internet access, not retrying image loads");
        return;
    }

    std::vector<winrt::Windows::System::DispatcherQueue> dispatchers;
    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);

        if (!g_imageRetryActive) {
            return;
        }

        for (auto& weakDispatcher : g_imageRetryDispatchers) {
            if (auto dispatcher = weakDispatcher.get()) {
                dispatchers.push_back(dispatcher);
            }
        }

        std::erase_if(g_imageRetryDispatchers, [](const auto& weakDispatcher) {
            return !weakDispatcher.get();
        });
    }

    for (auto& dispatcher : dispatchers) {
        try {
            dispatcher.TryEnqueue(
                []() { ScheduleImageLoadRetryOnCurrentThread(); });
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error dispatching retry to UI thread %08X: %s", ex.code(),
                   ex.message().c_str());
        }
    }
}

void OnNetworkStatusChanged(
    winrt::Windows::Foundation::IInspectable const& sender) {
    Wh_Log(L">");

    // Runs on a Windows Runtime thread pool thread, where the connectivity
    // query is allowed and doesn't hold up a UI thread.
    ScheduleImageLoadRetryOnAllUiThreads();
}

// Must not be called with g_imageRetryMutex held.
winrt::event_token RegisterNetworkStatusChangedHandler() {
    try {
        auto token = winrt::Windows::Networking::Connectivity::
            NetworkInformation::NetworkStatusChanged(OnNetworkStatusChanged);
        Wh_Log(L"Registered global network status change handler");
        return token;
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error registering network status handler %08X: %s", ex.code(),
               ex.message().c_str());
        return {};
    }
}

// Must not be called with g_imageRetryMutex held.
void UnregisterNetworkStatusChangedHandler(winrt::event_token token) {
    try {
        winrt::Windows::Networking::Connectivity::NetworkInformation::
            NetworkStatusChanged(token);
        Wh_Log(L"Unregistered global network status change handler");
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error unregistering network status handler %08X: %s",
               ex.code(), ex.message().c_str());
    }
}

void StopImageLoadRetries() {
    winrt::event_token token;

    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);

        // Makes any handler which acquires the mutex from here on return
        // early, which is what stops the retries. Removing the handler only
        // stops further invocations.
        g_imageRetryActive = false;

        token = g_networkStatusChangedToken;
        g_networkStatusChangedToken = {};

        g_imageRetryDispatchers.clear();
    }

    if (token) {
        UnregisterNetworkStatusChangedHandler(token);
    }
}

// Drops the calling thread from the dispatcher registry, and stops the retries
// altogether once the last thread is out of it.
void StopImageLoadRetriesForCurrentThread() {
    auto dispatcher = g_trackedImageBrushesForThread.dispatcher;
    if (!dispatcher) {
        return;
    }

    g_trackedImageBrushesForThread.dispatcher = nullptr;

    winrt::event_token token;

    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);

        std::erase_if(g_imageRetryDispatchers, [&dispatcher](
                                                   const auto& weakDispatcher) {
            auto registeredDispatcher = weakDispatcher.get();
            return !registeredDispatcher || registeredDispatcher == dispatcher;
        });

        if (!g_imageRetryDispatchers.empty()) {
            return;
        }

        // What StopImageLoadRetries does, kept under the lock which found the
        // registry empty so that a thread which registers in between isn't
        // stopped as well.
        g_imageRetryActive = false;

        token = g_networkStatusChangedToken;
        g_networkStatusChangedToken = {};
    }

    if (token) {
        UnregisterNetworkStatusChangedHandler(token);
    }
}

void SetupImageBrushTracking(Media::ImageBrush const& brush,
                             Media::Imaging::BitmapImage const& bitmapImage,
                             winrt::Windows::Foundation::Uri const& uri) {
    auto& brushes = g_trackedImageBrushesForThread.brushes;

    std::erase_if(brushes,
                  [](const auto& tracked) { return !tracked->brush.get(); });

    auto it = std::find_if(brushes.begin(), brushes.end(),
                           [&brush](const auto& tracked) {
                               if (auto trackedBrush = tracked->brush.get()) {
                                   return trackedBrush == brush;
                               }
                               return false;
                           });

    if (it != brushes.end()) {
        // Resolved style values are cached, so the same brush object is applied
        // to many elements and reapplied on every visual state change. Keep the
        // load state which was collected so far unless the source changed.
        if ((*it)->uri.Equals(uri)) {
            return;
        }

        brushes.erase(it);
    }

    Wh_Log(L"Tracking ImageBrush with remote source: %s", uri.RawUri().c_str());

    auto tracked = std::make_shared<TrackedImageBrush>();
    tracked->brush = winrt::make_weak(brush);
    tracked->uri = uri;

    try {
        tracked->decodePixelWidth = bitmapImage.DecodePixelWidth();
        tracked->decodePixelHeight = bitmapImage.DecodePixelHeight();
        tracked->decodePixelType = bitmapImage.DecodePixelType();
        tracked->createOptions = bitmapImage.CreateOptions();
        tracked->autoPlay = bitmapImage.AutoPlay();
        // A load which completed before tracking started raises no further
        // event, so the decoded size is what tells an image that's there from
        // one that isn't. An image which is still loading counts as missing,
        // which at worst costs a redundant download.
        tracked->loaded = bitmapImage.PixelWidth() != 0;
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }

    std::weak_ptr<TrackedImageBrush> trackedWeak = tracked;

    tracked->imageFailedRevoker = brush.ImageFailed(
        winrt::auto_revoke,
        [trackedWeak](winrt::Windows::Foundation::IInspectable const&,
                      ExceptionRoutedEventArgs const& e) {
            auto tracked = trackedWeak.lock();
            if (!tracked) {
                return;
            }

            Wh_Log(L"ImageBrush load failed for: %s, error: %s",
                   tracked->uri.RawUri().c_str(), e.ErrorMessage().c_str());

            tracked->loaded = false;
        });

    tracked->imageOpenedRevoker = brush.ImageOpened(
        winrt::auto_revoke,
        [trackedWeak](winrt::Windows::Foundation::IInspectable const&,
                      RoutedEventArgs const&) {
            auto tracked = trackedWeak.lock();
            if (!tracked) {
                return;
            }

            Wh_Log(L"ImageBrush loaded for: %s", tracked->uri.RawUri().c_str());

            tracked->loaded = true;
            tracked->retryCount = 0;
            tracked->lastRetryTick = 0;
        });

    brushes.push_back(std::move(tracked));

    bool registerHandler = false;

    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);

        g_imageRetryActive = true;

        if (!g_trackedImageBrushesForThread.dispatcher) {
            try {
                auto dispatcher = winrt::Windows::System::DispatcherQueue::
                    GetForCurrentThread();
                if (dispatcher) {
                    g_trackedImageBrushesForThread.dispatcher = dispatcher;
                    g_imageRetryDispatchers.push_back(
                        winrt::make_weak(dispatcher));
                    Wh_Log(
                        L"Registered UI thread dispatcher for network retry");
                }
            } catch (winrt::hresult_error const& ex) {
                Wh_Log(L"Error getting dispatcher for current thread %08X: %s",
                       ex.code(), ex.message().c_str());
            }
        }

        if (!g_networkStatusChangedToken &&
            !g_networkStatusChangedRegistering) {
            g_networkStatusChangedRegistering = true;
            registerHandler = true;
        }
    }

    if (!registerHandler) {
        return;
    }

    winrt::event_token token = RegisterNetworkStatusChangedHandler();

    bool stopped;

    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);

        g_networkStatusChangedRegistering = false;

        stopped = !g_imageRetryActive;
        if (!stopped) {
            g_networkStatusChangedToken = token;
        }
    }

    // StopImageLoadRetries ran while the handler was being registered, so it
    // found no token to remove.
    if (stopped && token) {
        UnregisterNetworkStatusChangedHandler(token);
    }
}

// Tracks the brush if the image source is a remote URL, which can fail to load
// and be worth retrying.
void TrackImageBrushIfRemoteSource(
    Media::ImageBrush const& brush,
    winrt::Windows::Foundation::IInspectable const& imageSource) {
    auto bitmapImage = imageSource.try_as<Media::Imaging::BitmapImage>();
    if (!bitmapImage) {
        return;
    }

    auto uri = bitmapImage.UriSource();
    if (!uri) {
        return;
    }

    auto scheme = uri.SchemeName();
    if (scheme != L"http" && scheme != L"https") {
        return;
    }

    SetupImageBrushTracking(brush, bitmapImage, uri);
}

void SetOrClearValue(DependencyObject elementDo,
                     DependencyProperty property,
                     const PropertyOverrideValue& overrideValue,
                     bool initialApply = false) {
    winrt::Windows::Foundation::IInspectable value;
    if (auto* inspectable =
            std::get_if<winrt::Windows::Foundation::IInspectable>(
                &overrideValue)) {
        value = *inspectable;
    } else if (auto* blurBrushParams =
                   std::get_if<XamlBlurBrushParams>(&overrideValue)) {
        if (auto uiElement = elementDo.try_as<UIElement>()) {
            value = winrt::make<XamlBlurBrush>(
                uiElement, blurBrushParams->blurAmount, blurBrushParams->tint,
                blurBrushParams->tintOpacity,
                winrt::hstring(blurBrushParams->tintThemeResourceKey),
                blurBrushParams->tintLuminosityOpacity,
                blurBrushParams->tintSaturation, blurBrushParams->noiseOpacity,
                blurBrushParams->noiseDensity, blurBrushParams->fallbackColor,
                winrt::hstring(blurBrushParams->fallbackThemeResourceKey));
        } else {
            Wh_Log(L"Can't get UIElement for blur brush");
            return;
        }
    } else {
        Wh_Log(L"Unsupported override value");
        return;
    }

    if (value == DependencyProperty::UnsetValue()) {
        Wh_Log(L"Clearing property value");
        try {
            elementDo.ClearValue(property);
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        }
        return;
    }

    Wh_Log(L"Setting property value %s",
           value ? winrt::get_class_name(value).c_str() : L"(null)");

    // Track ImageBrush with remote ImageSource for retry on network
    // reconnection. This handles cases where an ImageBrush is set as a property
    // value (e.g., Background).
    if (auto imageBrush = value.try_as<Media::ImageBrush>()) {
        TrackImageBrushIfRemoteSource(imageBrush, imageBrush.ImageSource());
    }
    // Also handle direct ImageSource property being set on an ImageBrush.
    else if (auto imageBrush = elementDo.try_as<Media::ImageBrush>()) {
        if (property == Media::ImageBrush::ImageSourceProperty()) {
            TrackImageBrushIfRemoteSource(imageBrush, value);
        }
    }

    // This might fail. See `ReadLocalValueWithWorkaround` for an example (which
    // we now handle but there might be other cases).
    try {
        // `setter.Value()` returns font weight as an int. Using it with
        // `SetValue` results in the following error: 0x80004002 (No such
        // interface supported). Box it as `Windows.UI.Text.FontWeight` as a
        // workaround.
        if (property == Controls::TextBlock::FontWeightProperty() ||
            property == Controls::Control::FontWeightProperty() ||
            property == Controls::RichTextBlock::FontWeightProperty() ||
            property == Controls::FontIcon::FontWeightProperty() ||
            property == Controls::FontIconSource::FontWeightProperty() ||
            property == Controls::ContentPresenter::FontWeightProperty()) {
            auto valueInt = value.try_as<int>();
            if (valueInt && *valueInt >= std::numeric_limits<uint16_t>::min() &&
                *valueInt <= std::numeric_limits<uint16_t>::max()) {
                value = winrt::box_value(winrt::Windows::UI::Text::FontWeight{
                    static_cast<uint16_t>(*valueInt)});
            }
        }

        // Grid ColumnDefinitions/RowDefinitions hold DependencyObjects
        // (ColumnDefinition/RowDefinition) that the layout engine writes
        // ActualWidth/ActualHeight back into. The resolved value is parsed once
        // and cached, so applying it to more than one grid - e.g. a taskbar per
        // monitor, all sharing one UI thread - would set the same collection on
        // each, and one monitor's column sizes would then leak onto another's.
        // Give each element a private copy. The scratch Grid owns the fresh
        // collection until SetValue reassigns ownership to the target, so it's
        // kept alive through the SetValue call below.
        Controls::Grid definitionsCloneOwner{nullptr};
        if (auto sourceColumns =
                value.try_as<Controls::ColumnDefinitionCollection>()) {
            definitionsCloneOwner = Controls::Grid{};
            auto clonedColumns = definitionsCloneOwner.ColumnDefinitions();
            for (auto const& column : sourceColumns) {
                Controls::ColumnDefinition clonedColumn;
                clonedColumn.Width(column.Width());
                clonedColumn.MinWidth(column.MinWidth());
                clonedColumn.MaxWidth(column.MaxWidth());
                clonedColumns.Append(clonedColumn);
            }
            value = clonedColumns;
        } else if (auto sourceRows =
                       value.try_as<Controls::RowDefinitionCollection>()) {
            definitionsCloneOwner = Controls::Grid{};
            auto clonedRows = definitionsCloneOwner.RowDefinitions();
            for (auto const& row : sourceRows) {
                Controls::RowDefinition clonedRow;
                clonedRow.Height(row.Height());
                clonedRow.MinHeight(row.MinHeight());
                clonedRow.MaxHeight(row.MaxHeight());
                clonedRows.Append(clonedRow);
            }
            value = clonedRows;
        }

        elementDo.SetValue(property, value);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }
}

// https://stackoverflow.com/a/5665377
std::wstring EscapeXmlAttribute(std::wstring_view data) {
    std::wstring buffer;
    buffer.reserve(data.size());
    for (const auto c : data) {
        switch (c) {
            case '&':
                buffer.append(L"&amp;");
                break;
            case '\"':
                buffer.append(L"&quot;");
                break;
            // case '\'':
            //     buffer.append(L"&apos;");
            //     break;
            case '<':
                buffer.append(L"&lt;");
                break;
            case '>':
                buffer.append(L"&gt;");
                break;
            default:
                buffer.push_back(c);
                break;
        }
    }

    return buffer;
}

// https://stackoverflow.com/a/54364173
std::wstring_view TrimStringView(std::wstring_view s) {
    s.remove_prefix(std::min(s.find_first_not_of(L" \t\r\v\n"), s.size()));
    s.remove_suffix(
        std::min(s.size() - s.find_last_not_of(L" \t\r\v\n") - 1, s.size()));
    return s;
}

// https://stackoverflow.com/a/46931770
std::vector<std::wstring_view> SplitStringView(std::wstring_view s,
                                               std::wstring_view delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::wstring_view token;
    std::vector<std::wstring_view> res;

    while ((pos_end = s.find(delimiter, pos_start)) !=
           std::wstring_view::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

std::optional<PropertyOverrideValue> ParseNonXamlPropertyOverrideValue(
    std::wstring_view stringValue) {
    // Example:
    // <WindhawkBlur BlurAmount="10" TintColor="#FFFF0000"/>

    auto substr = TrimStringView(stringValue);

    constexpr auto kWindhawkBlurPrefix = L"<WindhawkBlur "sv;
    if (!substr.starts_with(kWindhawkBlurPrefix)) {
        return std::nullopt;
    }
    Wh_Log(L"%.*s", static_cast<int>(substr.length()), substr.data());
    substr = substr.substr(std::size(kWindhawkBlurPrefix));

    constexpr auto kWindhawkBlurSuffix = L"/>"sv;
    if (!substr.ends_with(kWindhawkBlurSuffix)) {
        throw std::runtime_error("WindhawkBlur: Bad suffix");
    }
    substr = substr.substr(0, substr.size() - std::size(kWindhawkBlurSuffix));

    bool pendingTintColorThemeResource = false;
    bool pendingFallbackColorThemeResource = false;
    std::wstring tintThemeResourceKey;
    std::wstring fallbackThemeResourceKey;
    winrt::Windows::UI::Color tint{};
    std::optional<winrt::Windows::UI::Color> fallbackColor;
    float tintOpacity = std::numeric_limits<float>::quiet_NaN();
    float tintLuminosityOpacity = std::numeric_limits<float>::quiet_NaN();
    float tintSaturation = std::numeric_limits<float>::quiet_NaN();
    float noiseOpacity = std::numeric_limits<float>::quiet_NaN();
    float noiseDensity = std::numeric_limits<float>::quiet_NaN();
    float blurAmount = 0;

    constexpr auto kTintColorThemeResourcePrefix =
        L"TintColor=\"{ThemeResource"sv;
    constexpr auto kTintColorThemeResourceSuffix = L"}\""sv;
    constexpr auto kTintColorPrefix = L"TintColor=\"#"sv;
    constexpr auto kTintOpacityPrefix = L"TintOpacity=\""sv;
    constexpr auto kTintLuminosityOpacityPrefix = L"TintLuminosityOpacity=\""sv;
    constexpr auto kTintSaturationPrefix = L"TintSaturation=\""sv;
    constexpr auto kNoiseOpacityPrefix = L"NoiseOpacity=\""sv;
    constexpr auto kNoiseDensityPrefix = L"NoiseDensity=\""sv;
    constexpr auto kBlurAmountPrefix = L"BlurAmount=\""sv;
    constexpr auto kFallbackColorThemeResourcePrefix =
        L"FallbackColor=\"{ThemeResource"sv;
    constexpr auto kFallbackColorThemeResourceSuffix = L"}\""sv;
    constexpr auto kFallbackColorPrefix = L"FallbackColor=\"#"sv;
    for (const auto prop : SplitStringView(substr, L" ")) {
        const auto propSubstr = TrimStringView(prop);
        if (propSubstr.empty()) {
            continue;
        }

        Wh_Log(L"  %.*s", static_cast<int>(propSubstr.length()),
               propSubstr.data());

        if (pendingTintColorThemeResource) {
            if (!propSubstr.ends_with(kTintColorThemeResourceSuffix)) {
                throw std::runtime_error(
                    "WindhawkBlur: Invalid TintColor theme resource syntax");
            }

            pendingTintColorThemeResource = false;

            tintThemeResourceKey = propSubstr.substr(
                0,
                propSubstr.size() - std::size(kTintColorThemeResourceSuffix));

            continue;
        }

        if (pendingFallbackColorThemeResource) {
            if (!propSubstr.ends_with(kFallbackColorThemeResourceSuffix)) {
                throw std::runtime_error(
                    "WindhawkBlur: Invalid FallbackColor theme resource "
                    "syntax");
            }

            pendingFallbackColorThemeResource = false;

            fallbackThemeResourceKey = propSubstr.substr(
                0, propSubstr.size() -
                       std::size(kFallbackColorThemeResourceSuffix));

            continue;
        }

        if (propSubstr == kTintColorThemeResourcePrefix) {
            pendingTintColorThemeResource = true;
            continue;
        }

        if (propSubstr == kFallbackColorThemeResourcePrefix) {
            pendingFallbackColorThemeResource = true;
            continue;
        }

        if (propSubstr.starts_with(kTintColorPrefix) &&
            propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(
                std::size(kTintColorPrefix),
                propSubstr.size() - std::size(kTintColorPrefix) - 1);

            bool hasAlpha;
            switch (valStr.size()) {
                case 6:
                    hasAlpha = false;
                    break;
                case 8:
                    hasAlpha = true;
                    break;
                default:
                    throw std::runtime_error(
                        "WindhawkBlur: Unsupported TintColor value");
            }

            auto valNum = std::stoul(std::wstring(valStr), nullptr, 16);
            uint8_t a = hasAlpha ? HIBYTE(HIWORD(valNum)) : 255;
            uint8_t r = LOBYTE(HIWORD(valNum));
            uint8_t g = HIBYTE(LOWORD(valNum));
            uint8_t b = LOBYTE(LOWORD(valNum));
            tint = {a, r, g, b};
            continue;
        }

        if (propSubstr.starts_with(kFallbackColorPrefix) &&
            propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(
                std::size(kFallbackColorPrefix),
                propSubstr.size() - std::size(kFallbackColorPrefix) - 1);

            bool hasAlpha;
            switch (valStr.size()) {
                case 6:
                    hasAlpha = false;
                    break;
                case 8:
                    hasAlpha = true;
                    break;
                default:
                    throw std::runtime_error(
                        "WindhawkBlur: Unsupported FallbackColor value");
            }

            auto valNum = std::stoul(std::wstring(valStr), nullptr, 16);
            uint8_t a = hasAlpha ? HIBYTE(HIWORD(valNum)) : 255;
            uint8_t r = LOBYTE(HIWORD(valNum));
            uint8_t g = HIBYTE(LOWORD(valNum));
            uint8_t b = LOBYTE(LOWORD(valNum));
            fallbackColor = winrt::Windows::UI::Color{a, r, g, b};
            continue;
        }

        if (propSubstr.starts_with(kTintOpacityPrefix) &&
            propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(
                std::size(kTintOpacityPrefix),
                propSubstr.size() - std::size(kTintOpacityPrefix) - 1);
            tintOpacity = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kTintLuminosityOpacityPrefix) &&
            propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(
                std::size(kTintLuminosityOpacityPrefix),
                propSubstr.size() - std::size(kTintLuminosityOpacityPrefix) -
                    1);
            tintLuminosityOpacity = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kTintSaturationPrefix) &&
            propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(
                std::size(kTintSaturationPrefix),
                propSubstr.size() - std::size(kTintSaturationPrefix) - 1);
            tintSaturation = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kNoiseOpacityPrefix) &&
            propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(
                std::size(kNoiseOpacityPrefix),
                propSubstr.size() - std::size(kNoiseOpacityPrefix) - 1);
            noiseOpacity = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kNoiseDensityPrefix) &&
            propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(
                std::size(kNoiseDensityPrefix),
                propSubstr.size() - std::size(kNoiseDensityPrefix) - 1);
            noiseDensity = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kBlurAmountPrefix) &&
            propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(
                std::size(kBlurAmountPrefix),
                propSubstr.size() - std::size(kBlurAmountPrefix) - 1);
            blurAmount = std::stof(std::wstring(valStr));
            continue;
        }

        throw std::runtime_error("WindhawkBlur: Bad property");
    }

    if (pendingTintColorThemeResource) {
        throw std::runtime_error(
            "WindhawkBlur: Unterminated TintColor theme resource");
    }

    if (pendingFallbackColorThemeResource) {
        throw std::runtime_error(
            "WindhawkBlur: Unterminated FallbackColor theme resource");
    }

    if (!std::isnan(tintOpacity)) {
        if (tintOpacity < 0.0f) {
            tintOpacity = 0.0f;
        } else if (tintOpacity > 1.0f) {
            tintOpacity = 1.0f;
        }

        tint.A = static_cast<uint8_t>(tintOpacity * 255.0f);
    }

    return XamlBlurBrushParams{
        .blurAmount = blurAmount,
        .tint = tint,
        .tintOpacity =
            !std::isnan(tintOpacity) ? std::optional(tint.A) : std::nullopt,
        .tintThemeResourceKey = std::move(tintThemeResourceKey),
        .tintLuminosityOpacity = !std::isnan(tintLuminosityOpacity)
                                     ? std::optional(tintLuminosityOpacity)
                                     : std::nullopt,
        .tintSaturation = !std::isnan(tintSaturation)
                              ? std::optional(tintSaturation)
                              : std::nullopt,
        .noiseOpacity = !std::isnan(noiseOpacity) ? std::optional(noiseOpacity)
                                                  : std::nullopt,
        .noiseDensity = !std::isnan(noiseDensity) ? std::optional(noiseDensity)
                                                  : std::nullopt,
        .fallbackColor = fallbackColor,
        .fallbackThemeResourceKey = std::move(fallbackThemeResourceKey),
    };
}

Style GetStyleFromXamlSetters(const std::wstring_view type,
                              const std::wstring_view xamlStyleSetters) {
    std::wstring xaml =
        LR"(<ResourceDictionary
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
    xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
    xmlns:muxc="using:Microsoft.UI.Xaml.Controls")";

    if (auto pos = type.rfind('.'); pos != type.npos) {
        auto typeNamespace = std::wstring_view(type).substr(0, pos);
        auto typeName = std::wstring_view(type).substr(pos + 1);

        xaml += L"\n    xmlns:windhawkstyler=\"using:";
        xaml += EscapeXmlAttribute(typeNamespace);
        xaml +=
            L"\">\n"
            L"    <Style TargetType=\"windhawkstyler:";
        xaml += EscapeXmlAttribute(typeName);
        xaml += L"\">\n";
    } else {
        xaml +=
            L">\n"
            L"    <Style TargetType=\"";
        xaml += EscapeXmlAttribute(type);
        xaml += L"\">\n";
    }

    xaml += xamlStyleSetters;

    xaml +=
        L"    </Style>\n"
        L"</ResourceDictionary>";

    Wh_Log(L"======================================== XAML:");
    std::wstringstream ss(xaml);
    std::wstring line;
    while (std::getline(ss, line, L'\n')) {
        Wh_Log(L"%s", line.c_str());
    }
    Wh_Log(L"========================================");

    auto resourceDictionary =
        Markup::XamlReader::Load(xaml).as<ResourceDictionary>();

    auto [styleKey, styleInspectable] = resourceDictionary.First().Current();
    return styleInspectable.as<Style>();
}

Style GetStyleFromXamlSettersWithFallbackType(
    const std::wstring_view type,
    const std::wstring_view fallbackType,
    const std::wstring_view xamlStyleSetters) {
    try {
        return GetStyleFromXamlSetters(type, xamlStyleSetters);
    } catch (winrt::hresult_error const& ex) {
        constexpr HRESULT kStowedException = 0x802B000A;
        if (ex.code() != kStowedException || fallbackType.empty() ||
            fallbackType == type) {
            throw;
        }

        // For some types such as JumpViewUI.JumpListListViewItem, the following
        // error is returned:
        //
        // Error 802B000A: Failed to create a 'System.Type' from the text
        // 'windhawkstyler:JumpListListViewItem'. [Line: 8 Position: 12]
        //
        // Retry with a fallback type, which will allow to at least use the
        // basic properties.
        Wh_Log(L"Retrying with fallback type type due to error %08X: %s",
               ex.code(), ex.message().c_str());
        return GetStyleFromXamlSetters(fallbackType, xamlStyleSetters);
    }
}

const ResolvedRules& GetResolvedPropertyOverrides(
    const std::wstring_view type,
    const std::wstring_view fallbackType,
    PropertyOverridesMaybeUnresolved* propertyOverridesMaybeUnresolved) {
    if (const auto* resolved =
            std::get_if<ResolvedRules>(propertyOverridesMaybeUnresolved)) {
        return *resolved;
    }

    ResolvedRules resolved;

    try {
        const auto& unresolved =
            std::get<UnresolvedRules>(*propertyOverridesMaybeUnresolved);
        const auto& valueRules = unresolved.valueRules;
        const auto& captureRules = unresolved.captureRules;

        if (!valueRules.empty() || !captureRules.empty()) {
            // Build a single XAML <Style> with one <Setter> per rule. Setters
            // for value rules come first, followed by one per capture rule.
            // Dynamic / capture rules emit a placeholder `{x:Null}` value -- we
            // only need the resolved DependencyProperty from those setters; the
            // value is computed elsewhere (per apply for dynamic, never for
            // captures).
            std::wstring xaml;

            std::vector<std::optional<PropertyOverrideValue>>
                propertyOverrideValues;
            propertyOverrideValues.reserve(valueRules.size());

            for (const auto& rule : valueRules) {
                const bool isDynamic = rule.isDynamic();

                propertyOverrideValues.push_back(
                    !isDynamic && rule.isXamlValue
                        ? ParseNonXamlPropertyOverrideValue(rule.value)
                        : std::nullopt);

                xaml += L"        <Setter Property=\"";
                xaml += EscapeXmlAttribute(rule.propertyName);
                xaml += L"\"";
                if (isDynamic || propertyOverrideValues.back() ||
                    (rule.isXamlValue && rule.value.empty())) {
                    xaml += L" Value=\"{x:Null}\" />\n";
                } else if (!rule.isXamlValue) {
                    xaml += L" Value=\"";
                    xaml += EscapeXmlAttribute(rule.value);
                    xaml += L"\" />\n";
                } else {
                    xaml +=
                        L">\n"
                        L"            <Setter.Value>\n";
                    xaml += rule.value;
                    xaml +=
                        L"\n"
                        L"            </Setter.Value>\n"
                        L"        </Setter>\n";
                }
            }

            for (const auto& rule : captureRules) {
                xaml += L"        <Setter Property=\"";
                xaml += EscapeXmlAttribute(rule.propertyName);
                xaml += L"\" Value=\"{x:Null}\" />\n";
            }

            auto style = GetStyleFromXamlSettersWithFallbackType(
                type, fallbackType, xaml);

            uint32_t setterIndex = 0;
            for (size_t i = 0; i < valueRules.size(); i++, setterIndex++) {
                const auto& rule = valueRules[i];
                const auto setter =
                    style.Setters().GetAt(setterIndex).as<Setter>();
                auto property = setter.Property();
                if (rule.isDynamic()) {
                    resolved.propertyOverrides[property][rule.visualState] =
                        DynamicStyleTemplate{rule.propertyName, rule.value,
                                             rule.isXamlValue};
                    resolved.hasDynamicValues = true;
                } else {
                    resolved.propertyOverrides[property][rule.visualState] =
                        propertyOverrideValues[i].value_or(
                            rule.isXamlValue && rule.value.empty()
                                ? DependencyProperty::UnsetValue()
                                : setter.Value());
                }
            }

            for (const auto& rule : captureRules) {
                const auto setter =
                    style.Setters().GetAt(setterIndex++).as<Setter>();
                resolved.captures.push_back({setter.Property(), rule.varName});
            }
        }

        Wh_Log(L"%.*s: %zu override styles, %zu captures",
               static_cast<int>(type.length()), type.data(),
               resolved.propertyOverrides.size(), resolved.captures.size());
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    } catch (std::exception const& ex) {
        Wh_Log(L"Error: %S", ex.what());
    }

    *propertyOverridesMaybeUnresolved = std::move(resolved);
    return std::get<ResolvedRules>(*propertyOverridesMaybeUnresolved);
}

// Resolve a single style rule's expanded textual value into a usable
// PropertyOverrideValue. Built for re-resolving dynamic `{{...}}` styles on
// every variable change; falls back to the same XAML-Setter parse trick used by
// the bulk resolver above. propertyName is the property whose XAML name should
// appear on the synthetic Setter (already known at apply time).
std::optional<PropertyOverrideValue> ResolveExpandedSinglePropertyValue(
    std::wstring_view type,
    std::wstring_view fallbackType,
    std::wstring_view propertyName,
    std::wstring_view expandedValue,
    bool isXamlValue) {
    if (isXamlValue) {
        if (auto blur = ParseNonXamlPropertyOverrideValue(expandedValue)) {
            return *blur;
        }

        if (TrimStringView(expandedValue).empty()) {
            return PropertyOverrideValue{DependencyProperty::UnsetValue()};
        }
    }

    std::wstring xaml = L"        <Setter Property=\"";
    xaml += EscapeXmlAttribute(propertyName);
    xaml += L"\"";
    if (!isXamlValue) {
        xaml += L" Value=\"";
        xaml += EscapeXmlAttribute(expandedValue);
        xaml += L"\" />\n";
    } else {
        xaml +=
            L">\n"
            L"            <Setter.Value>\n";
        xaml += expandedValue;
        xaml +=
            L"\n"
            L"            </Setter.Value>\n"
            L"        </Setter>\n";
    }

    try {
        auto style =
            GetStyleFromXamlSettersWithFallbackType(type, fallbackType, xaml);
        const auto setter = style.Setters().GetAt(0).as<Setter>();
        return PropertyOverrideValue{setter.Value()};
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    } catch (std::exception const& ex) {
        Wh_Log(L"Error: %S", ex.what());
    }

    return std::nullopt;
}

const PropertyValues& GetResolvedPropertyValues(
    const std::wstring_view type,
    const std::wstring_view fallbackType,
    PropertyValuesMaybeUnresolved* propertyValuesMaybeUnresolved) {
    if (const auto* resolved =
            std::get_if<PropertyValues>(propertyValuesMaybeUnresolved)) {
        return *resolved;
    }

    PropertyValues propertyValues;

    try {
        const auto& propertyValuesStr =
            std::get<PropertyValuesUnresolved>(*propertyValuesMaybeUnresolved);
        if (!propertyValuesStr.empty()) {
            std::wstring xaml;

            for (const auto& [property, value] : propertyValuesStr) {
                xaml += L"        <Setter Property=\"";
                xaml += EscapeXmlAttribute(property);
                xaml += L"\" Value=\"";
                xaml += EscapeXmlAttribute(value);
                xaml += L"\" />\n";
            }

            auto style = GetStyleFromXamlSettersWithFallbackType(
                type, fallbackType, xaml);

            for (size_t i = 0; i < propertyValuesStr.size(); i++) {
                const auto setter = style.Setters().GetAt(i).as<Setter>();
                propertyValues.push_back({
                    setter.Property(),
                    setter.Value(),
                });
            }
        }

        Wh_Log(L"%.*s: %zu matcher styles", static_cast<int>(type.length()),
               type.data(), propertyValues.size());
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    } catch (std::exception const& ex) {
        Wh_Log(L"Error: %S", ex.what());
    }

    *propertyValuesMaybeUnresolved = std::move(propertyValues);
    return std::get<PropertyValues>(*propertyValuesMaybeUnresolved);
}

// https://stackoverflow.com/a/12835139
VisualStateGroup GetVisualStateGroup(FrameworkElement element,
                                     std::wstring_view visualStateGroupName) {
    auto list = VisualStateManager::GetVisualStateGroups(element);

    for (const auto& v : list) {
        if (v.Name() == visualStateGroupName) {
            return v;
        }
    }

    return nullptr;
}

// Locale-independent double formatter. Uses `std::to_chars` shortest round-trip
// representation so XAML always sees `.` as the decimal separator.
std::wstring FormatDoubleInvariant(double d) {
    char buf[64];
    auto [end, ec] = std::to_chars(buf, buf + std::size(buf), d);
    if (ec != std::errc{}) {
        return L"0";
    }
    return std::wstring(buf, end);
}

// Locale-independent double parser. Accepts an optional leading sign followed
// by a decimal fraction or exponent. Returns std::nullopt on partial / bad
// input.
std::optional<double> ParseDoubleInvariant(std::wstring_view sv) {
    std::string narrow;
    narrow.reserve(sv.size());
    for (auto c : sv) {
        if (c > 127) {
            return std::nullopt;
        }
        narrow.push_back(static_cast<char>(c));
    }
    double result = 0;
    auto* first = narrow.data();
    auto* last = first + narrow.size();
    auto [ptr, ec] = std::from_chars(first, last, result);
    if (ec != std::errc{} || ptr != last) {
        return std::nullopt;
    }
    return result;
}

using UnboxedPropertyValue = std::variant<std::wstring,
                                          bool,
                                          char16_t,
                                          uint8_t,
                                          int16_t,
                                          uint16_t,
                                          int32_t,
                                          uint32_t,
                                          int64_t,
                                          uint64_t,
                                          float,
                                          double>;

// Unwraps a boxed primitive into a typed primitive variant. Dispatches on
// IPropertyValue::Type(). Returns std::nullopt for non-primitive (opaque)
// values such as brushes or thicknesses.
std::optional<UnboxedPropertyValue> TryUnboxPropertyValue(
    winrt::Windows::Foundation::IInspectable const& value) {
    using winrt::Windows::Foundation::IPropertyValue;
    using winrt::Windows::Foundation::PropertyType;

    auto pv = value.try_as<IPropertyValue>();
    if (!pv) {
        return std::nullopt;
    }

    switch (pv.Type()) {
        case PropertyType::String:
            return UnboxedPropertyValue{std::wstring(pv.GetString())};
        case PropertyType::Boolean:
            return UnboxedPropertyValue{pv.GetBoolean()};
        case PropertyType::Char16:
            return UnboxedPropertyValue{pv.GetChar16()};
        case PropertyType::Double:
            return UnboxedPropertyValue{pv.GetDouble()};
        case PropertyType::Single:
            return UnboxedPropertyValue{pv.GetSingle()};
        case PropertyType::UInt8:
            return UnboxedPropertyValue{pv.GetUInt8()};
        case PropertyType::Int16:
            return UnboxedPropertyValue{pv.GetInt16()};
        case PropertyType::UInt16:
            return UnboxedPropertyValue{pv.GetUInt16()};
        case PropertyType::Int32:
            return UnboxedPropertyValue{pv.GetInt32()};
        case PropertyType::UInt32:
            return UnboxedPropertyValue{pv.GetUInt32()};
        case PropertyType::Int64:
            return UnboxedPropertyValue{pv.GetInt64()};
        case PropertyType::UInt64:
            return UnboxedPropertyValue{pv.GetUInt64()};
        case PropertyType::OtherType: {
            // Common for enums.
            if (auto intVal = value.try_as<int32_t>()) {
                return UnboxedPropertyValue{*intVal};
            }
            return std::nullopt;
        }
        default: {
            return std::nullopt;
        }
    }
}

// Invariant-formatted text form, suitable for XAML attribute use or diagnostic
// logs.
std::wstring FormatUnboxedPropertyValue(UnboxedPropertyValue const& v) {
    return std::visit(
        [](auto const& x) -> std::wstring {
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, std::wstring>) {
                return x;
            } else if constexpr (std::is_same_v<T, bool>) {
                return x ? L"True" : L"False";
            } else if constexpr (std::is_same_v<T, char16_t>) {
                // Single-character text form so substitution emits the
                // character itself.
                return std::wstring(1, static_cast<wchar_t>(x));
            } else if constexpr (std::is_floating_point_v<T>) {
                return FormatDoubleInvariant(static_cast<double>(x));
            } else {
                return std::to_wstring(x);
            }
        },
        v);
}

// Numeric-as-double form, or std::nullopt if the value isn't numeric (i.e.
// holds a string).
std::optional<double> UnboxedPropertyValueAsNumeric(
    UnboxedPropertyValue const& v) {
    return std::visit(
        [](auto const& x) -> std::optional<double> {
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, std::wstring>) {
                return std::nullopt;
            } else {
                return static_cast<double>(x);
            }
        },
        v);
}

bool TestElementMatcher(FrameworkElement element,
                        ElementMatcher& matcher,
                        VisualStateGroup* visualStateGroup,
                        PCWSTR fallbackClassName) {
    if (!matcher.type.empty() &&
        matcher.type != winrt::get_class_name(element) &&
        (!fallbackClassName || matcher.type != fallbackClassName)) {
        return false;
    }

    if (!matcher.name.empty() && matcher.name != element.Name()) {
        return false;
    }

    if (matcher.oneBasedIndex) {
        auto parent = Media::VisualTreeHelper::GetParent(element);
        if (!parent) {
            return false;
        }

        int index = matcher.oneBasedIndex - 1;
        if (index < 0 ||
            index >= Media::VisualTreeHelper::GetChildrenCount(parent) ||
            Media::VisualTreeHelper::GetChild(parent, index) != element) {
            return false;
        }
    }

    auto elementDo = element.as<DependencyObject>();

    for (const auto& propertyValue : GetResolvedPropertyValues(
             matcher.type,
             fallbackClassName ? fallbackClassName
                               : winrt::name_of<FrameworkElement>(),
             &matcher.propertyValues)) {
        const auto value =
            ReadLocalValueWithWorkaround(elementDo, propertyValue.first);
        if (!value) {
            Wh_Log(L"Null property value");
            return false;
        } else if (value == DependencyProperty::UnsetValue()) {
            return false;
        }

        auto expectedUnboxed = TryUnboxPropertyValue(propertyValue.second);
        auto valueUnboxed = TryUnboxPropertyValue(value);
        if (!expectedUnboxed || !valueUnboxed) {
            Wh_Log(L"Unsupported property class: %s",
                   winrt::get_class_name(value).c_str());
            return false;
        }

        if (*expectedUnboxed != *valueUnboxed) {
            return false;
        }
    }

    if (matcher.visualStateGroupName && visualStateGroup) {
        *visualStateGroup =
            GetVisualStateGroup(element, *matcher.visualStateGroupName);
    }

    return true;
}

// Aggregated resolved rules for an element. Value-rules are still bucketed by
// visual-state-group (each target's rules live under that target's @VSGName);
// captures are intentionally NOT per-VSG -- they are wired up once at element
// level (see SetUpCapturesForElement).
struct ElementResolvedRules {
    std::unordered_map<VisualStateGroup, PropertyOverrides> overridesPerVSG;
    std::vector<CaptureSpec> captures;
    bool hasDynamicValues = false;
};

ElementResolvedRules FindElementPropertyOverrides(FrameworkElement element,
                                                  PCWSTR fallbackClassName) {
    ElementResolvedRules result;
    std::unordered_set<DependencyProperty> propertiesAdded;
    std::unordered_set<std::wstring> capturesAdded;

    for (auto it = g_elementsCustomizationRules.rbegin();
         it != g_elementsCustomizationRules.rend(); ++it) {
        auto& override = *it;

        VisualStateGroup visualStateGroup = nullptr;

        if (!TestElementMatcher(element, override.elementMatcher,
                                &visualStateGroup, fallbackClassName)) {
            continue;
        }

        // Using iter.Parent() was sometimes returning null, so use
        // VisualTreeHelper::GetParent below instead.
        //
        // Recursive lambda so that '*' can backtrack: when a candidate match
        // for the wildcard's next matcher leads to a failure further up the
        // chain, retry with a farther ancestor.
        auto& parentMatchers = override.parentElementMatchers;
        auto matchParents = [&](auto& self, FrameworkElement iter,
                                size_t mi) -> bool {
            if (mi >= parentMatchers.size()) {
                return true;
            }

            auto& matcher = parentMatchers[mi];

            if (matcher.kind == ElementMatcher::Kind::Root) {
                if (Media::VisualTreeHelper::GetParent(iter)) {
                    return false;
                }

                return self(self, iter, mi + 1);
            }

            if (matcher.kind == ElementMatcher::Kind::Wildcard) {
                // '*' is always followed by an Element matcher (validated at
                // parse time). Walk up parents and try recursing for each
                // ancestor that matches the next matcher.
                auto& nextMatcher = parentMatchers[mi + 1];
                auto cur = iter;
                while (true) {
                    auto parent = Media::VisualTreeHelper::GetParent(cur)
                                      .try_as<FrameworkElement>();
                    if (!parent) {
                        return false;
                    }

                    cur = parent;
                    if (TestElementMatcher(cur, nextMatcher, &visualStateGroup,
                                           nullptr) &&
                        self(self, cur, mi + 2)) {
                        return true;
                    }
                }
            }

            auto parent = Media::VisualTreeHelper::GetParent(iter)
                              .try_as<FrameworkElement>();
            if (!parent) {
                return false;
            }

            if (!TestElementMatcher(parent, matcher, &visualStateGroup,
                                    nullptr)) {
                return false;
            }

            return self(self, parent, mi + 1);
        };

        if (!matchParents(matchParents, element, 0)) {
            continue;
        }

        const auto& resolvedRules = GetResolvedPropertyOverrides(
            override.elementMatcher.type,
            fallbackClassName ? fallbackClassName
                              : winrt::name_of<FrameworkElement>(),
            &override.propertyOverrides);

        result.hasDynamicValues |= resolvedRules.hasDynamicValues;

        auto& propertyOverridesForVSG =
            result.overridesPerVSG[visualStateGroup];
        for (const auto& [property, valuesPerVisualState] :
             resolvedRules.propertyOverrides) {
            bool propertyInserted = propertiesAdded.insert(property).second;
            if (!propertyInserted) {
                continue;
            }

            auto& propertyOverrides = propertyOverridesForVSG[property];
            for (const auto& [visualState, value] : valuesPerVisualState) {
                propertyOverrides.insert({visualState, value});
            }
        }

        for (const auto& capture : resolvedRules.captures) {
            if (!capturesAdded.insert(capture.varName).second) {
                continue;
            }

            result.captures.push_back(capture);
        }
    }

    std::erase_if(result.overridesPerVSG,
                  [](const auto& item) { return item.second.empty(); });

    return result;
}

struct StyleVariableResolution {
    // Points into state->variables; only valid until that map is next touched,
    // so read it out before doing anything that could apply a style.
    const StyleVariableValue* value = nullptr;
    InstanceHandle owner = 0;
};

// How well a capture serves a consumer, as a sort key -- smaller is better.
// Captures are ranked by, in order:
//
//  1. Deepest common ancestor with the consumer.
//  2. Shallowest capture element. On a tie the capture that lies on the
//     consumer's own parent chain *is* the common ancestor, so this is what
//     makes a capture on an ancestor beat one on a cousin below it.
//  3. Registration order, applied by the callers below keeping the first of
//     equal keys. Only a last resort: it follows the order XamlDiagnostics
//     reports elements in, which is not stable across boots or across taskbar
//     item recycling.
//
// The closest capture wins even when its value is opaque, in which case the
// consuming style is skipped rather than falling through to a farther capture
// that happens to be usable.
std::pair<int, int> StyleVariableCaptureRank(
    ElementTreeNode const* consumerNode,
    ElementTreeNode const* captureNode) {
    int lcaDepth = ElementTreeLcaDepth(consumerNode, captureNode);
    int captureDepth = captureNode ? static_cast<int>(captureNode->depth)
                                   : std::numeric_limits<int>::max();
    return {-lcaDepth, captureDepth};
}

// Pick the capture of `varName` that `consumerNode` should read.
StyleVariableResolution FindWinningCapture(
    StyleVariableState* state,
    const std::wstring& varName,
    ElementTreeNode const* consumerNode) {
    StyleVariableResolution result;

    auto it = state->variables.find(varName);
    if (it == state->variables.end() || it->second.empty()) {
        return result;
    }

    const auto& captures = it->second;
    if (captures.size() == 1) {
        // The common case by far: nothing to rank, and the owner's spine node
        // never has to be resolved.
        return {&captures.front().value, captures.front().elementHandle};
    }

    std::pair<int, int> bestRank;
    for (const auto& capture : captures) {
        ElementTreeNode const* captureNode = nullptr;
        if (auto elementIt =
                g_elementsCustomizationState.find(capture.elementHandle);
            elementIt != g_elementsCustomizationState.end()) {
            captureNode = EnsureElementTreeNode(elementIt->second);
        }

        auto rank = StyleVariableCaptureRank(consumerNode, captureNode);
        if (!result.value || rank < bestRank) {
            bestRank = rank;
            result = {&capture.value, capture.elementHandle};
        }
    }

    return result;
}

// A capture reduced to what ranking needs. The node is held by strong ref so a
// snapshot stays usable even after re-entrant work tears the owning element
// down.
struct StyleVariableCandidate {
    InstanceHandle owner = 0;
    std::shared_ptr<ElementTreeNode> node;
};

// Resolve every capture's spine node once. A pass that ranks one variable
// against many consumers would otherwise repeat the same lookups per consumer,
// and only the ranking actually varies between them.
std::vector<StyleVariableCandidate> SnapshotStyleVariableCaptures(
    const std::vector<StyleVariableCapture>& captures) {
    std::vector<StyleVariableCandidate> candidates;
    candidates.reserve(captures.size());

    for (const auto& capture : captures) {
        StyleVariableCandidate candidate;
        candidate.owner = capture.elementHandle;
        if (auto elementIt =
                g_elementsCustomizationState.find(capture.elementHandle);
            elementIt != g_elementsCustomizationState.end()) {
            auto& elementCustomizationState = elementIt->second;
            EnsureElementTreeNode(elementCustomizationState);
            candidate.node = elementCustomizationState.treeNode;
        }

        candidates.push_back(std::move(candidate));
    }

    return candidates;
}

// The owner FindWinningCapture would pick, ranked from a snapshot. A snapshot
// taken before a re-entrant capture change can go stale, which at worst skips a
// consumer that needed redoing -- the change that invalidated it queues its own
// propagation, and that pass re-snapshots and picks the consumer up.
InstanceHandle PickWinningCaptureOwner(
    const std::vector<StyleVariableCandidate>& candidates,
    ElementTreeNode const* consumerNode) {
    InstanceHandle owner = 0;
    bool haveBest = false;
    std::pair<int, int> bestRank;

    for (const auto& candidate : candidates) {
        auto rank =
            StyleVariableCaptureRank(consumerNode, candidate.node.get());
        if (!haveBest || rank < bestRank) {
            haveBest = true;
            bestRank = rank;
            owner = candidate.owner;
        }
    }

    return owner;
}

// What a `{{...}}` expansion needs. `consumerNode` is the consuming element's
// position in the tree, used to pick the closest capture of each name.
struct StyleVariableLookupContext {
    StyleVariableState* state;
    ElementTreeNode const* consumerNode;
    std::vector<StyleVariableDependency>* outDeps;
};

bool IsValidStyleVariableIdentifier(std::wstring_view sv) {
    if (sv.empty()) {
        return false;
    }
    auto isStart = [](wchar_t c) {
        return (c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z') ||
               c == L'_';
    };
    auto isCont = [&](wchar_t c) {
        return isStart(c) || (c >= L'0' && c <= L'9');
    };
    if (!isStart(sv[0])) {
        return false;
    }
    for (size_t i = 1; i < sv.size(); i++) {
        if (!isCont(sv[i])) {
            return false;
        }
    }
    return true;
}

// Value produced while evaluating a `{{ ... }}` expression: either a number or
// a string. Number literals and numeric variables produce numbers; backtick-
// delimited string literals and string-typed variables produce strings.
struct StyleExpressionValue {
    // Engaged => numeric value; otherwise `text` holds the string value.
    std::optional<double> number;
    std::wstring text;

    static StyleExpressionValue Number(double d) { return {d, std::wstring()}; }
    static StyleExpressionValue String(std::wstring s) {
        return {std::nullopt, std::move(s)};
    }

    bool IsNumber() const { return number.has_value(); }
};

// Recursive-descent evaluator for `{{ ... }}` expressions. Operands: number
// literals, backtick-delimited string literals, style variable references, and
// parenthesized subexpressions. Operators: binary + - * /, unary - / +, the
// comparisons < <= == >= > !=, the conditional operator cond ? a : b, and the
// two-arg functions min(a, b) and max(a, b). Standard math precedence.
// Arithmetic, relational, unary-sign, and min/max operators require numeric
// operands; == and != compare two numbers or two strings; the conditional
// selects one of its (possibly string) branches. Evaluate() formats the result
// to text.
//
// Variable references pushed into outDeps so the dependent style can be
// re-evaluated when those variables change.
class StyleVariableExpressionEvaluator {
   public:
    StyleVariableExpressionEvaluator(std::wstring_view text,
                                     const StyleVariableLookupContext* context)
        : m_text(text), m_context(context) {}

    // Returns the text form of the result: numeric results are formatted with
    // FormatDoubleInvariant, string results are returned verbatim. Throws
    // std::runtime_error on parse / evaluation failure (including when a value
    // is used where the grammar requires a number, or when a numeric result is
    // non-finite -- NaN/Inf can't be formatted into XAML attributes
    // meaningfully and would also break the consumer-equality check in
    // SetStyleVariableIfChangedAndPropagate, since NaN != NaN).
    std::wstring Evaluate() {
        m_pos = 0;
        SkipWhitespace();
        StyleExpressionValue v = ParseExpression();
        SkipWhitespace();
        if (m_pos != m_text.size()) {
            throw std::runtime_error(
                "Unexpected trailing characters in style variable expression");
        }
        if (v.IsNumber()) {
            if (!std::isfinite(*v.number)) {
                throw std::runtime_error(
                    "Style variable expression produced a non-finite result");
            }
            return FormatDoubleInvariant(*v.number);
        }
        return v.text;
    }

   private:
    void SkipWhitespace() {
        while (m_pos < m_text.size() &&
               (m_text[m_pos] == L' ' || m_text[m_pos] == L'\t' ||
                m_text[m_pos] == L'\r' || m_text[m_pos] == L'\n')) {
            m_pos++;
        }
    }

    bool ConsumeChar(wchar_t c) {
        SkipWhitespace();
        if (m_pos < m_text.size() && m_text[m_pos] == c) {
            m_pos++;
            return true;
        }
        return false;
    }

    // Tries to consume the multi-char operator `op` at the current position
    // (after skipping leading whitespace). The operator must match exactly with
    // no embedded whitespace; advances past it and returns true on success.
    bool ConsumeOperator(std::wstring_view op) {
        SkipWhitespace();
        if (m_text.size() - m_pos >= op.size() &&
            m_text.compare(m_pos, op.size(), op) == 0) {
            m_pos += op.size();
            return true;
        }
        return false;
    }

    // Unwraps a numeric operand. In a dead ternary branch (m_live == false) the
    // value is discarded, so a string operand is tolerated (reported as 0)
    // rather than aborting the whole expression.
    double RequireNumber(const StyleExpressionValue& v) {
        if (v.IsNumber()) {
            return *v.number;
        }
        if (m_live) {
            throw std::runtime_error(
                "Non-numeric value used where a number is required in style "
                "variable expression");
        }
        return 0.0;
    }

    // Equality test for == / !=. Two numbers compare numerically, two strings
    // compare by content. A number/string mismatch is always unequal rather
    // than an error, so `{{var == `` ? default : var}}` can supply a fallback
    // for an undefined variable (which reads as the empty string) without
    // failing when the variable is instead a captured number.
    bool ValuesEqual(const StyleExpressionValue& a,
                     const StyleExpressionValue& b) {
        if (a.IsNumber() && b.IsNumber()) {
            return *a.number == *b.number;
        }
        if (!a.IsNumber() && !b.IsNumber()) {
            return a.text == b.text;
        }
        return false;
    }

    StyleExpressionValue ParseExpression() { return ParseTernary(); }

    // Conditional operator `cond ? thenVal : elseVal`, right-associative.
    // Short-circuit: only the taken branch is evaluated. The untaken branch is
    // still parsed (to advance the position and enforce syntax) with m_live
    // cleared, which suppresses value-level errors (division by zero, a
    // non-numeric / undefined variable, an unknown function) and dependency
    // capture for that branch.
    StyleExpressionValue ParseTernary() {
        StyleExpressionValue cond = ParseEquality();
        if (!ConsumeChar(L'?')) {
            return cond;
        }
        bool condTrue = RequireNumber(cond) != 0.0;
        bool prevLive = m_live;

        m_live = prevLive && condTrue;
        StyleExpressionValue thenVal = ParseExpression();
        m_live = prevLive;

        if (!ConsumeChar(L':')) {
            throw std::runtime_error(
                "Missing ':' for '?' in style variable expression");
        }

        m_live = prevLive && !condTrue;
        StyleExpressionValue elseVal = ParseTernary();
        m_live = prevLive;

        return condTrue ? thenVal : elseVal;
    }

    StyleExpressionValue ParseEquality() {
        StyleExpressionValue v = ParseRelational();
        while (true) {
            if (ConsumeOperator(L"==")) {
                v = StyleExpressionValue::Number(
                    ValuesEqual(v, ParseRelational()) ? 1.0 : 0.0);
            } else if (ConsumeOperator(L"!=")) {
                v = StyleExpressionValue::Number(
                    ValuesEqual(v, ParseRelational()) ? 0.0 : 1.0);
            } else {
                break;
            }
        }
        return v;
    }

    StyleExpressionValue ParseRelational() {
        StyleExpressionValue v = ParseAdditive();
        while (true) {
            // Match the two-char operators before their single-char prefixes.
            if (ConsumeOperator(L"<=")) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(
                    lhs <= RequireNumber(ParseAdditive()) ? 1.0 : 0.0);
            } else if (ConsumeOperator(L">=")) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(
                    lhs >= RequireNumber(ParseAdditive()) ? 1.0 : 0.0);
            } else if (ConsumeOperator(L"<")) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(
                    lhs < RequireNumber(ParseAdditive()) ? 1.0 : 0.0);
            } else if (ConsumeOperator(L">")) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(
                    lhs > RequireNumber(ParseAdditive()) ? 1.0 : 0.0);
            } else {
                break;
            }
        }
        return v;
    }

    StyleExpressionValue ParseAdditive() {
        StyleExpressionValue v = ParseTerm();
        while (true) {
            SkipWhitespace();
            if (ConsumeChar(L'+')) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs +
                                                 RequireNumber(ParseTerm()));
            } else if (ConsumeChar(L'-')) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs -
                                                 RequireNumber(ParseTerm()));
            } else {
                break;
            }
        }
        return v;
    }

    StyleExpressionValue ParseTerm() {
        StyleExpressionValue v = ParseFactor();
        while (true) {
            SkipWhitespace();
            if (ConsumeChar(L'*')) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs *
                                                 RequireNumber(ParseFactor()));
            } else if (ConsumeChar(L'/')) {
                double lhs = RequireNumber(v);
                double rhs = RequireNumber(ParseFactor());
                if (rhs == 0.0) {
                    if (m_live) {
                        throw std::runtime_error(
                            "Division by zero in style variable expression");
                    }
                    // Dead ternary branch: the result is discarded, so skip the
                    // divide instead of throwing or producing inf/nan.
                    v = StyleExpressionValue::Number(lhs);
                } else {
                    v = StyleExpressionValue::Number(lhs / rhs);
                }
            } else {
                break;
            }
        }
        return v;
    }

    StyleExpressionValue ParseFactor() {
        SkipWhitespace();
        if (ConsumeChar(L'+')) {
            return StyleExpressionValue::Number(RequireNumber(ParseFactor()));
        }
        if (ConsumeChar(L'-')) {
            return StyleExpressionValue::Number(-RequireNumber(ParseFactor()));
        }
        return ParsePrimary();
    }

    StyleExpressionValue ParsePrimary() {
        SkipWhitespace();
        if (m_pos >= m_text.size()) {
            throw std::runtime_error(
                "Unexpected end of style variable expression");
        }

        wchar_t c = m_text[m_pos];
        if (c == L'(') {
            m_pos++;
            StyleExpressionValue v = ParseExpression();
            SkipWhitespace();
            if (!ConsumeChar(L')')) {
                throw std::runtime_error(
                    "Missing ')' in style variable expression");
            }
            return v;
        }

        if (c == L'`') {
            return ParseStringLiteral();
        }

        if ((c >= L'0' && c <= L'9') || c == L'.') {
            return StyleExpressionValue::Number(ParseNumberLiteral());
        }

        if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z') || c == L'_') {
            return ParseIdentifierOrCall();
        }

        throw std::runtime_error(
            "Unexpected character in style variable expression");
    }

    // Backtick-delimited string literal. A doubled backtick encodes one literal
    // backtick character; every other character is taken verbatim. Backtick is
    // used (rather than a quote) so that literals don't clash with the string
    // quoting of YAML settings or with the double quotes of XAML attributes,
    // inside which these expressions often appear. The literal must be closed
    // before the end of the expression.
    StyleExpressionValue ParseStringLiteral() {
        m_pos++;  // Skip the opening backtick.
        std::wstring out;
        while (m_pos < m_text.size()) {
            wchar_t c = m_text[m_pos];
            if (c == L'`') {
                if (m_pos + 1 < m_text.size() && m_text[m_pos + 1] == L'`') {
                    out.push_back(L'`');
                    m_pos += 2;
                    continue;
                }
                m_pos++;
                return StyleExpressionValue::String(std::move(out));
            }
            out.push_back(c);
            m_pos++;
        }
        throw std::runtime_error(
            "Unterminated string literal in style variable expression");
    }

    double ParseNumberLiteral() {
        size_t start = m_pos;
        bool sawDigit = false;
        bool sawDot = false;
        while (m_pos < m_text.size()) {
            wchar_t c = m_text[m_pos];
            if (c >= L'0' && c <= L'9') {
                sawDigit = true;
                m_pos++;
            } else if (c == L'.' && !sawDot) {
                sawDot = true;
                m_pos++;
            } else {
                break;
            }
        }
        if (m_pos < m_text.size() &&
            (m_text[m_pos] == L'e' || m_text[m_pos] == L'E')) {
            m_pos++;
            if (m_pos < m_text.size() &&
                (m_text[m_pos] == L'+' || m_text[m_pos] == L'-')) {
                m_pos++;
            }
            while (m_pos < m_text.size() && m_text[m_pos] >= L'0' &&
                   m_text[m_pos] <= L'9') {
                m_pos++;
            }
        }
        if (!sawDigit) {
            throw std::runtime_error(
                "Bad number literal in style variable expression");
        }
        auto parsed = ParseDoubleInvariant(m_text.substr(start, m_pos - start));
        if (!parsed) {
            throw std::runtime_error(
                "Bad number literal in style variable expression");
        }
        return *parsed;
    }

    StyleExpressionValue ParseIdentifierOrCall() {
        size_t start = m_pos;
        while (m_pos < m_text.size()) {
            wchar_t c = m_text[m_pos];
            if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z') ||
                (c >= L'0' && c <= L'9') || c == L'_') {
                m_pos++;
            } else {
                break;
            }
        }
        std::wstring_view ident = m_text.substr(start, m_pos - start);
        SkipWhitespace();
        if (m_pos < m_text.size() && m_text[m_pos] == L'(') {
            m_pos++;
            double a = RequireNumber(ParseExpression());
            if (!ConsumeChar(L',')) {
                throw std::runtime_error(
                    "Expected ',' in min/max style variable call");
            }
            double b = RequireNumber(ParseExpression());
            if (!ConsumeChar(L')')) {
                throw std::runtime_error(
                    "Missing ')' after min/max style variable call");
            }
            if (ident == L"min") {
                return StyleExpressionValue::Number((a < b) ? a : b);
            }
            if (ident == L"max") {
                return StyleExpressionValue::Number((a > b) ? a : b);
            }
            if (m_live) {
                throw std::runtime_error(
                    "Unknown function in style variable expression");
            }
            // Dead ternary branch: value discarded, don't fail on the name.
            return StyleExpressionValue::Number(0.0);
        }
        return LookupVariable(std::wstring(ident));
    }

    StyleExpressionValue LookupVariable(const std::wstring& name) {
        // In a dead ternary branch (m_live == false) the value is discarded, so
        // skip the lookup along with dependency capture and the value-level
        // errors below; the branch must not abort the whole expression, and
        // every operator tolerates a string operand while not live.
        if (!m_live) {
            return StyleExpressionValue::String(L"");
        }

        auto resolution =
            FindWinningCapture(m_context->state, name, m_context->consumerNode);

        if (m_context->outDeps) {
            m_context->outDeps->push_back({name, resolution.owner});
        }
        if (!resolution.value) {
            Wh_Log(L"Style variable '%s' not defined; treating as empty string",
                   name.c_str());
            // Undefined reads as the empty string sentinel, so `{{var == `` ?
            // default : var}}` can detect the undefined state and substitute a
            // fallback. Arithmetic on an undefined variable then fails
            // RequireNumber and skips the style, rather than silently using 0.
            return StyleExpressionValue::String(L"");
        }
        if (resolution.value->numeric) {
            return StyleExpressionValue::Number(*resolution.value->numeric);
        }
        // Non-numeric primitive (e.g. a captured string property): usable as a
        // string operand.
        if (resolution.value->substitutable) {
            return StyleExpressionValue::String(resolution.value->stringForm);
        }
        // Opaque capture (brush, thickness, etc.): no value form usable in an
        // expression.
        throw std::runtime_error(
            "Style variable used in expression is not a primitive value");
    }

    std::wstring_view m_text;
    const StyleVariableLookupContext* m_context;
    size_t m_pos = 0;
    // When false, we're parsing (but discarding) the untaken branch of a
    // ternary; value-level errors and dependency capture are suppressed.
    bool m_live = true;
};

// Evaluate a single expression body (the text between `{{` and `}}`). If the
// body is a bare identifier, returns the variable's `stringForm` directly --
// but only when the captured value is a primitive type flagged `substitutable`
// (numeric, boolean, or string). Missing variables and opaque-type captures
// both cause this function to return std::nullopt, at which point
// ExpandStyleVariables aborts the whole expansion and the consuming style is
// skipped. This matches the arithmetic path's behaviour of failing closed
// rather than substituting a value that won't parse.
std::optional<std::wstring> EvaluateStyleVariableExpression(
    std::wstring_view exprText,
    const StyleVariableLookupContext* context) {
    auto trimmed = TrimStringView(exprText);
    if (trimmed.empty()) {
        Wh_Log(L"Empty style variable expression");
        return std::nullopt;
    }

    if (IsValidStyleVariableIdentifier(trimmed)) {
        std::wstring name(trimmed);
        auto resolution =
            FindWinningCapture(context->state, name, context->consumerNode);
        if (context->outDeps) {
            context->outDeps->push_back({name, resolution.owner});
        }
        if (!resolution.value) {
            Wh_Log(L"Style variable '%s' not yet defined; skipping style",
                   name.c_str());
            return std::nullopt;
        }
        if (!resolution.value->substitutable) {
            Wh_Log(
                L"Style variable '%s' is not substitutable (captured type "
                L"'%s'); skipping style",
                name.c_str(), resolution.value->stringForm.c_str());
            return std::nullopt;
        }
        return resolution.value->stringForm;
    }

    try {
        StyleVariableExpressionEvaluator eval(trimmed, context);
        return eval.Evaluate();
    } catch (std::exception const& ex) {
        Wh_Log(L"Style variable expression failed: %S (in '%.*s')", ex.what(),
               static_cast<int>(trimmed.size()), trimmed.data());
        return std::nullopt;
    }
}

// Walks the input text, repeatedly expanding the innermost `{{ ... }}`
// substitution. Returns std::nullopt on parse failure (and logs a warning).
//
// Inner-matching rule: the first `}}` is paired with the *rightmost* `{{` that
// precedes it. So `{{{x}}}` -> `{` + value-of-x + `}` (literal outer braces).
//
// Substituted text is treated as literal (no further `{{...}}` expansion of the
// substituted output) to keep behavior predictable.
std::optional<std::wstring> ExpandStyleVariables(
    std::wstring_view input,
    const StyleVariableLookupContext* context) {
    std::wstring result(input);
    size_t scanFrom = 0;

    while (true) {
        size_t closePos = std::wstring::npos;
        for (size_t i = scanFrom; i + 1 < result.size(); i++) {
            if (result[i] == L'}' && result[i + 1] == L'}') {
                closePos = i;
                break;
            }
        }
        if (closePos == std::wstring::npos) {
            break;
        }

        // Find rightmost `{{` strictly before closePos. Search from closePos -
        // 1 downward; the pair occupies indices (j-1, j).
        size_t openPos = std::wstring::npos;
        if (closePos >= 2) {
            for (size_t j = closePos - 1; j >= 1; j--) {
                if (result[j - 1] == L'{' && result[j] == L'{') {
                    openPos = j - 1;
                    break;
                }
                if (j == 1) {
                    break;
                }
            }
        }

        if (openPos == std::wstring::npos) {
            Wh_Log(L"Unmatched '}}' in style value at offset %zu", closePos);
            return std::nullopt;
        }

        std::wstring_view exprText(result.data() + openPos + 2,
                                   closePos - openPos - 2);
        auto expanded = EvaluateStyleVariableExpression(exprText, context);
        if (!expanded) {
            return std::nullopt;
        }

        size_t spanLen = closePos + 2 - openPos;
        result.replace(openPos, spanLen, *expanded);
        scanFrom = openPos + expanded->size();
    }

    return result;
}

// Read a property's current effective value and convert it to a
// StyleVariableValue suitable for `{{Var}}` substitution. Numeric primitives
// produce both string + numeric forms and are flagged substitutable; boolean
// and string primitives are flagged substitutable but have no numeric form.
// Opaque types (brushes, thicknesses, etc.) record only the captured class name
// as a diagnostic and are NOT flagged substitutable -- the bare- identifier
// substitution path skips them rather than emitting a class name into the XAML
// output.
StyleVariableValue ReadCapturedStyleVariableValue(FrameworkElement element,
                                                  DependencyProperty property) {
    StyleVariableValue out;

    auto elementDo = element.as<DependencyObject>();
    winrt::Windows::Foundation::IInspectable value{nullptr};
    // Get effective value so layout-driven properties like ActualWidth (which
    // never have a local value) still capture.
    try {
        value = elementDo.GetValue(property);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }
    if (!value || value == DependencyProperty::UnsetValue()) {
        out.stringForm = L"";
        return out;
    }

    try {
        if (auto unboxed = TryUnboxPropertyValue(value)) {
            out.stringForm = FormatUnboxedPropertyValue(*unboxed);
            out.numeric = UnboxedPropertyValueAsNumeric(*unboxed);
            out.substitutable = true;
            return out;
        }

        // Opaque value (brush, thickness, etc.). Stored as a diagnostic only;
        // not flagged substitutable, so bare `{{Var}}` skips the consuming
        // style with a clear log message rather than emitting `className` into
        // the XAML.
        out.stringForm = std::wstring(winrt::get_class_name(value));
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        out.stringForm = L"";
    }
    return out;
}

// Remove this (handle, property) entry from the consumer lists of every
// variable named in oldDeps, then add it for every variable named in newDeps.
// `fallbackClassName` is stored on each newly-added consumer entry so the
// per-consumer context is preserved across propagations; it is irrelevant when
// newDeps is empty (pure-removal calls from the cleanup paths).
void UpdateStyleVariableConsumers(
    StyleVariableState* state,
    InstanceHandle handle,
    DependencyProperty property,
    PCWSTR fallbackClassName,
    const std::vector<StyleVariableDependency>& oldDeps,
    const std::vector<StyleVariableDependency>& newDeps) {
    if (!state) {
        // The element's XamlRoot has already been destroyed (or was never
        // available); the StyleVariableState entry has been or will be reaped,
        // and there is nothing to clean up. New registrations (newDeps) are
        // also dropped on the floor: without a state we cannot route
        // propagations anyway.
        return;
    }

    for (const auto& dep : oldDeps) {
        auto it = state->consumers.find(dep.name);
        if (it == state->consumers.end()) {
            continue;
        }
        auto& consumers = it->second;
        std::erase_if(consumers, [&](const StyleVariableConsumer& c) {
            return c.elementHandle == handle && c.property == property;
        });
        if (consumers.empty()) {
            state->consumers.erase(it);
        }
    }

    std::wstring fallbackClassNameStr =
        fallbackClassName ? fallbackClassName : L"";
    for (const auto& dep : newDeps) {
        auto& consumers = state->consumers[dep.name];
        bool already = std::any_of(consumers.begin(), consumers.end(),
                                   [&](const StyleVariableConsumer& c) {
                                       return c.elementHandle == handle &&
                                              c.property == property;
                                   });
        if (!already) {
            consumers.push_back({handle, property, fallbackClassNameStr});
        }
    }
}

// Re-evaluate the dynamic template stored on `propertyCustomizationState` and
// return the resolved IInspectable / XamlBlurBrushParams ready to be applied.
// Updates the (handle, property) -> state->consumers registry to match the
// freshly computed dependency set so future variable changes route to this
// property. The dependency registry is committed *before* the final XAML
// resolution attempt: ExpandStyleVariables records every variable name it scans
// into newDeps even on partial parse failure, which lets a future change to any
// of those variables re-enter this function and retry. The trade-off is that on
// resolution failure the caller's last-good `customValue` is preserved (we
// return std::nullopt and the caller leaves the property as-is); this
// self-heals on the next variable change.
//
// `fallbackClassName` is the consumer-element's own fallback class name (the
// one that was used when matching the consumer's target rule), which is
// generally NOT the same as the capturer's. It is what
// ResolveExpandedSinglePropertyValue feeds to the synthetic <Style> used to
// re-parse the rule body, and it is also stored on each new
// StyleVariableConsumer entry so subsequent propagations route through this
// same context.
//
// `elementCustomizationState` is the consumer's own entry when the caller
// already has it, saving the lookup needed to rank captures by proximity; pass
// nullptr to have it looked up from `handle`.
//
// Returns std::nullopt if the state has no template, expansion failed, or XAML
// resolution failed.
std::optional<PropertyOverrideValue> ResolveDynamicStyleValue(
    StyleVariableState* state,
    InstanceHandle handle,
    FrameworkElement element,
    DependencyProperty property,
    PCWSTR fallbackClassName,
    ElementPropertyCustomizationState* propertyCustomizationState,
    ElementCustomizationState* elementCustomizationState) {
    if (!propertyCustomizationState->dynamicTemplate) {
        return std::nullopt;
    }

    const auto& tmpl = *propertyCustomizationState->dynamicTemplate;

    if (!elementCustomizationState) {
        if (auto it = g_elementsCustomizationState.find(handle);
            it != g_elementsCustomizationState.end()) {
            elementCustomizationState = &it->second;
        }
    }

    ElementTreeNode const* consumerNode =
        elementCustomizationState
            ? EnsureElementTreeNode(*elementCustomizationState)
            : nullptr;

    std::vector<StyleVariableDependency> newDeps;
    StyleVariableLookupContext context{state, consumerNode, &newDeps};
    auto expanded = ExpandStyleVariables(tmpl.rawValue, &context);

    UpdateStyleVariableConsumers(
        state, handle, property, fallbackClassName,
        propertyCustomizationState->variableDependencies, newDeps);
    propertyCustomizationState->variableDependencies = std::move(newDeps);

    if (!expanded) {
        propertyCustomizationState->lastResolveFailed = true;
        return std::nullopt;
    }

    auto typeName = winrt::get_class_name(element);
    auto resolved = ResolveExpandedSinglePropertyValue(
        std::wstring_view(typeName),
        fallbackClassName ? std::wstring_view(fallbackClassName)
                          : winrt::name_of<FrameworkElement>(),
        tmpl.propertyName, *expanded, tmpl.isXamlValue);
    if (!resolved) {
        Wh_Log(
            L"Dynamic style resolution failed for '%s' on %s; keeping "
            L"previously applied value",
            tmpl.propertyName.c_str(), typeName.c_str());
    }
    propertyCustomizationState->lastResolveFailed = !resolved;
    return resolved;
}

// Whether a change to `varName` can alter this property's resolved value.
// `changedOwner` is set when one capture's value changed: only consumers that
// read from that capture are affected. It is empty when the set of captures
// changed instead, in which case `winningOwner` is the capture the consumer
// would read now, and only a consumer whose recorded owner differs needs
// redoing.
bool StyleVariableChangeAffectsConsumer(
    const ElementPropertyCustomizationState& propertyCustomizationState,
    const std::wstring& varName,
    std::optional<InstanceHandle> changedOwner,
    InstanceHandle winningOwner) {
    if (propertyCustomizationState.lastResolveFailed) {
        return true;
    }

    for (const auto& dep : propertyCustomizationState.variableDependencies) {
        if (dep.name != varName) {
            continue;
        }

        return changedOwner ? dep.owner == *changedOwner
                            : dep.owner != winningOwner;
    }

    return false;
}

// Re-evaluate the dependent styles a change to `varName` can actually reach.
// Each consumer carries its own fallbackClassName (recorded when the consumer
// was registered), so propagation uses the consumer's own match-site context to
// re-parse the rule body, even when the capturer was matched against a
// different type/fallback class.
void PropagateStyleVariableChangeCore(
    StyleVariableState* state,
    const std::wstring& varName,
    std::optional<InstanceHandle> changedOwner) {
    auto consumersIt = state->consumers.find(varName);
    if (consumersIt == state->consumers.end()) {
        return;
    }

    // Only the ranking varies per consumer, so the captures' spine nodes are
    // resolved once for the whole pass. Needed only when the set of captures
    // changed; a value change routes by the recorded owner instead.
    std::vector<StyleVariableCandidate> candidates;
    if (!changedOwner) {
        if (auto varIt = state->variables.find(varName);
            varIt != state->variables.end()) {
            candidates = SnapshotStyleVariableCaptures(varIt->second);
        }
    }

    auto consumersCopy = consumersIt->second;
    for (const auto& consumer : consumersCopy) {
        auto stateIt =
            g_elementsCustomizationState.find(consumer.elementHandle);
        if (stateIt == g_elementsCustomizationState.end()) {
            continue;
        }
        // A reference rather than the iterator: applying a style below can
        // realize children, which re-enters ApplyCustomizations and may rehash
        // g_elementsCustomizationState. Rehashing invalidates iterators but not
        // references to the mapped values.
        auto& elementState = stateIt->second;

        auto element = elementState.element.get();
        if (!element) {
            continue;
        }

        // A handful of pointer comparisons against the snapshot above, far
        // cheaper than the re-parse it avoids.
        InstanceHandle winningOwner =
            changedOwner ? 0
                         : PickWinningCaptureOwner(
                               candidates, EnsureElementTreeNode(elementState));

        PCWSTR consumerFallbackClassName =
            consumer.fallbackClassName.empty()
                ? nullptr
                : consumer.fallbackClassName.c_str();

        for (auto& [vsgWeak, vsgState] : elementState.perVisualStateGroup) {
            auto propIt =
                vsgState.propertyCustomizationStates.find(consumer.property);
            if (propIt == vsgState.propertyCustomizationStates.end()) {
                continue;
            }
            auto& propState = propIt->second;
            if (!propState.dynamicTemplate) {
                continue;
            }

            if (!StyleVariableChangeAffectsConsumer(
                    propState, varName, changedOwner, winningOwner)) {
                continue;
            }

            auto resolved = ResolveDynamicStyleValue(
                state, consumer.elementHandle, element, consumer.property,
                consumerFallbackClassName, &propState, &elementState);
            if (!resolved) {
                continue;
            }
            if (!propState.originalValue) {
                propState.originalValue =
                    ReadLocalValueWithWorkaround(element, consumer.property);
            }
            propState.customValue = *resolved;

            bool wasModifying = g_elementPropertyModifying;
            g_elementPropertyModifying = true;
            SetOrClearValue(element, consumer.property, *resolved);
            propState.lastAppliedValue =
                ReadLocalValueWithWorkaround(element, consumer.property);
            g_elementPropertyModifying = wasModifying;
        }
    }
}

// Notify the styles that depend on `varName`. `changedOwner` names the capture
// whose value changed, or is empty when captures were added or removed.
//
// Applying a style can realize children (running ApplyCustomizations, which
// adds captures) or write a captured property (running a capture callback,
// which g_elementPropertyModifying deliberately does not suppress), so this
// re-enters. Nested calls queue instead of running, and the outermost frame
// drains the queue, which also coalesces a burst into one pass.
void PropagateStyleVariableChange(StyleVariableState* state,
                                  const std::wstring& varName,
                                  std::optional<InstanceHandle> changedOwner) {
    PendingStyleVariablePropagation propagation{state, varName, changedOwner};

    if (g_styleVariablePropagationDepth > 0) {
        auto& pending = g_pendingStyleVariablePropagations;
        if (std::find(pending.begin(), pending.end(), propagation) ==
            pending.end()) {
            pending.push_back(std::move(propagation));
        }
        return;
    }

    struct DepthScope {
        DepthScope() { g_styleVariablePropagationDepth++; }
        ~DepthScope() { g_styleVariablePropagationDepth--; }
    } depthScope;

    PropagateStyleVariableChangeCore(state, varName, changedOwner);

    // A style that writes a property some rule captures keeps refilling the
    // queue. The unchanged-value fast path settles most such loops within a
    // round or two; a value that oscillates never settles, so give up loudly
    // instead of hanging the UI thread.
    constexpr int kMaxDrainRounds = 32;

    for (int round = 0; !g_pendingStyleVariablePropagations.empty(); round++) {
        if (round >= kMaxDrainRounds) {
            Wh_Log(
                L"Style variables did not settle after %d rounds; dropping %zu "
                L"queued update(s)",
                kMaxDrainRounds, g_pendingStyleVariablePropagations.size());
            g_pendingStyleVariablePropagations.clear();
            break;
        }

        auto pending = std::move(g_pendingStyleVariablePropagations);
        g_pendingStyleVariablePropagations.clear();
        for (const auto& pendingPropagation : pending) {
            PropagateStyleVariableChangeCore(pendingPropagation.state,
                                             pendingPropagation.varName,
                                             pendingPropagation.changedOwner);
        }
    }
}

// Store a capture's freshly read value and notify dependents if it changed.
// The comparison is against this capture's own previous value: comparing
// against whichever capture currently wins would silently drop a second
// capturer's change whenever it happened to match. Used by every path that
// publishes a captured value -- the per-property capture callback and the
// SizeChanged catch-all -- so the no-op fast path applies uniformly.
void SetStyleVariableIfChangedAndPropagate(StyleVariableState* state,
                                           const std::wstring& varName,
                                           InstanceHandle owner,
                                           StyleVariableValue value) {
    auto varIt = state->variables.find(varName);
    if (varIt == state->variables.end()) {
        return;
    }

    auto& captures = varIt->second;
    auto it = std::find_if(captures.begin(), captures.end(),
                           [owner](const StyleVariableCapture& capture) {
                               return capture.elementHandle == owner;
                           });
    if (it == captures.end()) {
        // The capture was torn down between the notification and here.
        return;
    }

    if (it->value.stringForm == value.stringForm &&
        it->value.numeric == value.numeric &&
        it->value.substitutable == value.substitutable) {
        Wh_Log(L"Style variable '%s' unchanged at '%s'", varName.c_str(),
               value.stringForm.c_str());
        return;
    }

    Wh_Log(L"Style variable '%s' changed: '%s' -> '%s'", varName.c_str(),
           it->value.stringForm.c_str(), value.stringForm.c_str());
    it->value = std::move(value);
    PropagateStyleVariableChange(state, varName, owner);
}

// True for layout-driven DPs whose updates do not fire
// RegisterPropertyChangedCallback on UWP, so capture rules on those DPs need
// `FrameworkElement.SizeChanged` as their notification source instead.
bool IsLayoutDrivenSizeProperty(DependencyProperty property) {
    return property == FrameworkElement::ActualWidthProperty() ||
           property == FrameworkElement::ActualHeightProperty();
}

// Wire up `Property=>VarName` capture rules for an element. Called once per
// matched element (captures are not visual-state-aware). Seeds the variables
// from the current property values, registers per-DP property-changed
// callbacks, and -- because UWP's ActualWidth/ActualHeight don't fire those
// callbacks on layout -- subscribes to FrameworkElement.SizeChanged as a
// catch-all that re-reads every active capture on resize.
//
// Seeding writes the captured values into state->variables in a single batch
// (to avoid intermediate inconsistent states for consumers that depend on
// multiple variables from this element) and only then propagates. Every seeded
// name propagates, even one whose value matches an existing capture's: adding a
// capture changes which captures a consumer chooses between, so the consumers
// have to be re-scored regardless of the value. The function does not need the
// capturer's fallbackClassName: each StyleVariableConsumer entry already
// carries its own consumer-side fallback, so propagation routes through the
// right context per consumer.
void SetUpCapturesForElement(StyleVariableState* state,
                             InstanceHandle handle,
                             FrameworkElement element,
                             const std::vector<CaptureSpec>& captures,
                             ElementCustomizationState* elementState) {
    if (captures.empty()) {
        return;
    }

    auto elementDo = element.as<DependencyObject>();
    winrt::weak_ref<FrameworkElement> elementWeakRef = element;

    // Names seeded below, propagated once the whole batch is in place.
    std::vector<std::wstring> seededVarNames;
    seededVarNames.reserve(captures.size());

    // Captures whose source DP is layout-driven (ActualWidth/ActualHeight) need
    // a SizeChanged subscription as their notification source. Collect them so
    // we only subscribe once and only when needed.
    std::vector<std::pair<DependencyProperty, std::wstring>>
        sizeChangedCaptures;

    for (const auto& capture : captures) {
        const auto [it, inserted] =
            elementState->captureCustomizationStates.insert(
                {capture.property, {}});
        if (!inserted) {
            // Same DP captured twice on this element (different rules with the
            // same property); keep the first and warn so the dropped second is
            // not a silent footgun for users who later try to reference the
            // dropped variable in a `{{...}}` substitution.
            Wh_Log(
                L"Capture for property already registered on %s; "
                L"dropping duplicate variable '%s' (kept: '%s')",
                winrt::get_class_name(element).c_str(), capture.varName.c_str(),
                it->second.varName.c_str());
            continue;
        }
        auto& captureState = it->second;
        captureState.varName = capture.varName;

        auto value = ReadCapturedStyleVariableValue(element, capture.property);

        // No entry for this element can exist yet: the insert above rejects a
        // second capture of the same DP, and FindElementPropertyOverrides
        // rejects a second capture of the same name.
        auto& capturesForVar = state->variables[capture.varName];
        Wh_Log(
            L"Seeding capture variable '%s' from %s with value '%s' "
            L"(%zu other capture(s))",
            capture.varName.c_str(), winrt::get_class_name(element).c_str(),
            value.stringForm.c_str(), capturesForVar.size());
        capturesForVar.push_back({handle, std::move(value)});

        seededVarNames.push_back(capture.varName);

        if (IsLayoutDrivenSizeProperty(capture.property)) {
            sizeChangedCaptures.push_back({capture.property, capture.varName});
            // No property-changed callback: the DP doesn't fire one for layout
            // updates anyway, and SizeChanged below covers it.
            continue;
        }

        std::wstring varName = capture.varName;
        captureState.propertyChangedToken =
            elementDo.RegisterPropertyChangedCallback(
                capture.property,
                [state, varName, handle, elementWeakRef](
                    DependencyObject sender, DependencyProperty property) {
                    auto element = elementWeakRef.get();
                    if (!element) {
                        return;
                    }
                    auto value =
                        ReadCapturedStyleVariableValue(element, property);
                    SetStyleVariableIfChangedAndPropagate(
                        state, varName, handle, std::move(value));
                });
    }

    if (!sizeChangedCaptures.empty()) {
        elementState->captureSizeChangedToken = element.SizeChanged(
            [state, handle, elementWeakRef,
             sizeChangedCaptures = std::move(sizeChangedCaptures)](
                winrt::Windows::Foundation::IInspectable const& sender,
                SizeChangedEventArgs const& e) {
                auto element = elementWeakRef.get();
                if (!element) {
                    return;
                }
                Wh_Log(L"SizeChanged on %s: %.3fx%.3f",
                       winrt::get_class_name(element).c_str(),
                       e.NewSize().Width, e.NewSize().Height);
                for (const auto& [property, varName] : sizeChangedCaptures) {
                    auto value =
                        ReadCapturedStyleVariableValue(element, property);
                    SetStyleVariableIfChangedAndPropagate(
                        state, varName, handle, std::move(value));
                }
            });
    }

    // The new captures may be closer to consumers registered before this
    // element was matched than whatever they were reading.
    for (const auto& varName : seededVarNames) {
        PropagateStyleVariableChange(state, varName, std::nullopt);
    }
}

// Tear down capture subscriptions for an element. Called from
// CleanupCustomizations and UninitializeSettingsAndTap before the
// ElementCustomizationState entry is erased.
void RestoreCapturesForElement(FrameworkElement element,
                               const ElementCustomizationState& elementState) {
    if (!element) {
        return;
    }

    for (const auto& [property, captureState] :
         elementState.captureCustomizationStates) {
        if (!captureState.propertyChangedToken) {
            continue;
        }
        try {
            element.UnregisterPropertyChangedCallback(
                property, captureState.propertyChangedToken);
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        }
    }

    if (elementState.captureSizeChangedToken) {
        try {
            element.SizeChanged(elementState.captureSizeChangedToken);
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        }
    }
}

void ApplyCustomizationsForVisualStateGroup(
    StyleVariableState* state,
    InstanceHandle handle,
    FrameworkElement element,
    VisualStateGroup visualStateGroup,
    PCWSTR fallbackClassName,
    PropertyOverrides propertyOverrides,
    ElementCustomizationStateForVisualStateGroup*
        elementCustomizationStateForVisualStateGroup) {
    auto elementDo = element.as<DependencyObject>();

    VisualState currentVisualState(
        visualStateGroup ? visualStateGroup.CurrentState() : nullptr);

    std::wstring currentVisualStateName(
        currentVisualState ? currentVisualState.Name() : L"");

    for (const auto& [property, valuesPerVisualState] : propertyOverrides) {
        const auto [propertyCustomizationStatesIt, inserted] =
            elementCustomizationStateForVisualStateGroup
                ->propertyCustomizationStates.insert({property, {}});
        if (!inserted) {
            continue;
        }

        auto& propertyCustomizationState =
            propertyCustomizationStatesIt->second;

        auto it = valuesPerVisualState.find(currentVisualStateName);
        if (it == valuesPerVisualState.end() &&
            !currentVisualStateName.empty()) {
            it = valuesPerVisualState.find(L"");
        }

        if (it != valuesPerVisualState.end()) {
            std::optional<PropertyOverrideValue> resolved;
            if (auto* tmpl = std::get_if<DynamicStyleTemplate>(&it->second)) {
                propertyCustomizationState.dynamicTemplate = *tmpl;
                resolved = ResolveDynamicStyleValue(
                    state, handle, element, property, fallbackClassName,
                    &propertyCustomizationState,
                    /*elementCustomizationState=*/nullptr);
            } else {
                resolved = it->second;
            }

            if (resolved) {
                propertyCustomizationState.originalValue =
                    ReadLocalValueWithWorkaround(element, property);
                propertyCustomizationState.customValue = *resolved;
                SetOrClearValue(element, property, *resolved,
                                /*initialApply=*/true);
                propertyCustomizationState.lastAppliedValue =
                    ReadLocalValueWithWorkaround(element, property);
            }
        }

        propertyCustomizationState.propertyChangedToken =
            elementDo.RegisterPropertyChangedCallback(
                property,
                [&propertyCustomizationState](DependencyObject sender,
                                              DependencyProperty property) {
                    if (g_elementPropertyModifying) {
                        return;
                    }

                    auto element = sender.try_as<FrameworkElement>();
                    if (!element) {
                        return;
                    }

                    if (!propertyCustomizationState.customValue) {
                        return;
                    }

                    auto localValue =
                        ReadLocalValueWithWorkaround(element, property);

                    // Only update originalValue if the local value was changed
                    // externally (e.g. by a Setter). When an animation changes
                    // only the effective value, the local value still matches
                    // what we set, so updating originalValue would corrupt it
                    // with our own brush - causing the brush to survive cleanup
                    // and crash when the mod's DLL is unloaded.
                    if (localValue !=
                        propertyCustomizationState.lastAppliedValue) {
                        propertyCustomizationState.originalValue = localValue;
                    }

                    Wh_Log(L"Re-applying style for %s",
                           winrt::get_class_name(element).c_str());

                    g_elementPropertyModifying = true;
                    SetOrClearValue(element, property,
                                    *propertyCustomizationState.customValue);
                    propertyCustomizationState.lastAppliedValue =
                        ReadLocalValueWithWorkaround(element, property);
                    g_elementPropertyModifying = false;
                });
    }

    if (visualStateGroup) {
        winrt::weak_ref<FrameworkElement> elementWeakRef = element;
        std::wstring fallbackClassNameStr =
            fallbackClassName ? fallbackClassName : L"";
        elementCustomizationStateForVisualStateGroup
            ->visualStateGroupCurrentStateChangedToken =
            visualStateGroup.CurrentStateChanged(
                [state, elementWeakRef, propertyOverrides, handle,
                 fallbackClassNameStr,
                 elementCustomizationStateForVisualStateGroup](
                    winrt::Windows::Foundation::IInspectable const& sender,
                    VisualStateChangedEventArgs const& e) {
                    auto element = elementWeakRef.get();
                    if (!element) {
                        return;
                    }

                    Wh_Log(L"Re-applying all styles for %s",
                           winrt::get_class_name(element).c_str());

                    g_elementPropertyModifying = true;

                    auto& propertyCustomizationStates =
                        elementCustomizationStateForVisualStateGroup
                            ->propertyCustomizationStates;

                    PCWSTR fallbackClassNamePtr =
                        fallbackClassNameStr.empty()
                            ? nullptr
                            : fallbackClassNameStr.c_str();

                    for (const auto& [property, valuesPerVisualState] :
                         propertyOverrides) {
                        auto& propertyCustomizationState =
                            propertyCustomizationStates.at(property);

                        auto newState = e.NewState();
                        auto newStateName =
                            std::wstring{newState ? newState.Name() : L""};
                        auto it = valuesPerVisualState.find(newStateName);
                        if (it == valuesPerVisualState.end()) {
                            it = valuesPerVisualState.find(L"");
                            if (it != valuesPerVisualState.end()) {
                                auto oldState = e.OldState();
                                auto oldStateName = std::wstring{
                                    oldState ? oldState.Name() : L""};
                                if (!valuesPerVisualState.contains(
                                        oldStateName)) {
                                    continue;
                                }
                            }
                        }

                        if (it != valuesPerVisualState.end()) {
                            std::optional<PropertyOverrideValue> resolved;
                            if (auto* tmpl = std::get_if<DynamicStyleTemplate>(
                                    &it->second)) {
                                propertyCustomizationState.dynamicTemplate =
                                    *tmpl;
                                resolved = ResolveDynamicStyleValue(
                                    state, handle, element, property,
                                    fallbackClassNamePtr,
                                    &propertyCustomizationState,
                                    /*elementCustomizationState=*/nullptr);
                            } else {
                                // Transitioning from dynamic to static for this
                                // visual state: clear template metadata and
                                // unregister consumer entries.
                                if (propertyCustomizationState
                                        .dynamicTemplate) {
                                    UpdateStyleVariableConsumers(
                                        state, handle, property,
                                        /*fallbackClassName=*/nullptr,
                                        propertyCustomizationState
                                            .variableDependencies,
                                        {});
                                    propertyCustomizationState
                                        .variableDependencies.clear();
                                    propertyCustomizationState.dynamicTemplate
                                        .reset();
                                }

                                resolved = it->second;
                            }

                            if (resolved) {
                                if (!propertyCustomizationState.originalValue) {
                                    propertyCustomizationState.originalValue =
                                        ReadLocalValueWithWorkaround(element,
                                                                     property);
                                }

                                propertyCustomizationState.customValue =
                                    *resolved;
                                SetOrClearValue(element, property, *resolved);
                                propertyCustomizationState.lastAppliedValue =
                                    ReadLocalValueWithWorkaround(element,
                                                                 property);
                            }
                        } else {
                            if (propertyCustomizationState.dynamicTemplate) {
                                UpdateStyleVariableConsumers(
                                    state, handle, property,
                                    /*fallbackClassName=*/nullptr,
                                    propertyCustomizationState
                                        .variableDependencies,
                                    {});
                                propertyCustomizationState.variableDependencies
                                    .clear();
                                propertyCustomizationState.dynamicTemplate
                                    .reset();
                            }
                            if (propertyCustomizationState.originalValue) {
                                SetOrClearValue(
                                    element, property,
                                    *propertyCustomizationState.originalValue);
                                propertyCustomizationState.originalValue
                                    .reset();
                            }
                            propertyCustomizationState.lastAppliedValue =
                                nullptr;

                            propertyCustomizationState.customValue.reset();
                        }
                    }

                    g_elementPropertyModifying = false;
                });
    }
}

void RestoreCustomizationsForVisualStateGroup(
    StyleVariableState* state,
    InstanceHandle handle,
    FrameworkElement element,
    std::optional<winrt::weak_ref<VisualStateGroup>>
        visualStateGroupOptionalWeakPtr,
    const ElementCustomizationStateForVisualStateGroup&
        elementCustomizationStateForVisualStateGroup) {
    if (element) {
        for (const auto& [property, propState] :
             elementCustomizationStateForVisualStateGroup
                 .propertyCustomizationStates) {
            try {
                element.UnregisterPropertyChangedCallback(
                    property, propState.propertyChangedToken);
            } catch (winrt::hresult_error const& ex) {
                Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
            }

            if (!propState.variableDependencies.empty()) {
                UpdateStyleVariableConsumers(state, handle, property,
                                             /*fallbackClassName=*/nullptr,
                                             propState.variableDependencies,
                                             {});
            }

            if (propState.originalValue) {
                SetOrClearValue(element, property, *propState.originalValue);
            }
        }
    } else {
        // Element is gone; still clear consumer entries so a stale (handle,
        // property) pair isn't visited during PropagateStyleVariableChange.
        for (const auto& [property, propState] :
             elementCustomizationStateForVisualStateGroup
                 .propertyCustomizationStates) {
            if (!propState.variableDependencies.empty()) {
                UpdateStyleVariableConsumers(state, handle, property,
                                             /*fallbackClassName=*/nullptr,
                                             propState.variableDependencies,
                                             {});
            }
        }
    }

    auto visualStateGroupIter = visualStateGroupOptionalWeakPtr
                                    ? visualStateGroupOptionalWeakPtr->get()
                                    : nullptr;
    if (visualStateGroupIter && elementCustomizationStateForVisualStateGroup
                                    .visualStateGroupCurrentStateChangedToken) {
        try {
            visualStateGroupIter.CurrentStateChanged(
                elementCustomizationStateForVisualStateGroup
                    .visualStateGroupCurrentStateChangedToken);
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        }
    }
}

void MergeResourceVariables();

void ApplyCustomizations(InstanceHandle handle,
                         FrameworkElement element,
                         PCWSTR fallbackClassName) {
    // Merge resource dictionary on first element add. Merging it earlier on
    // window creation doesn't work, perhaps merged dictionaries are reset
    // during initialization.
    if (!g_resourceVariablesThemeDict) {
        MergeResourceVariables();
    }

    auto* state = GetStyleVariableState();
    if (!state) {
        Wh_Log(L"No XamlRoot for %s, skipping",
               winrt::get_class_name(element).c_str());
        return;
    }

    auto resolved = FindElementPropertyOverrides(element, fallbackClassName);
    if (resolved.overridesPerVSG.empty() && resolved.captures.empty()) {
        return;
    }

    Wh_Log(L"Applying styles to %s", winrt::get_class_name(element).c_str());

    auto& elementCustomizationState = g_elementsCustomizationState[handle];

    for (const auto& [visualStateGroupOptionalWeakPtrIter, stateIter] :
         elementCustomizationState.perVisualStateGroup) {
        RestoreCustomizationsForVisualStateGroup(
            state, handle, element, visualStateGroupOptionalWeakPtrIter,
            stateIter);
    }

    elementCustomizationState.element = element;
    elementCustomizationState.perVisualStateGroup.clear();

    // Elements that neither capture nor consume a variable pay nothing. The
    // rest get their spine now that the element has been matched; if it isn't
    // attached yet the walk yields nothing and EnsureElementTreeNode retries on
    // first use. Cleared unconditionally so a re-apply that drops all variable
    // use cannot leave a stale node behind.
    elementCustomizationState.treeNode = nullptr;
    if (!resolved.captures.empty() || resolved.hasDynamicValues) {
        elementCustomizationState.treeNode =
            GetOrCreateElementTreeNode(element);
    }

    // Wire up captures first so any variables they define are visible to
    // dynamic value-rules applied below. Note: SetUpCapturesForElement does not
    // need this element's fallbackClassName -- propagation routes through each
    // consumer's own stored fallback.
    SetUpCapturesForElement(state, handle, element, resolved.captures,
                            &elementCustomizationState);

    for (auto& [visualStateGroup, overridesForVisualStateGroup] :
         resolved.overridesPerVSG) {
        std::optional<winrt::weak_ref<VisualStateGroup>>
            visualStateGroupOptionalWeakPtr;
        if (visualStateGroup) {
            visualStateGroupOptionalWeakPtr = visualStateGroup;
        }

        elementCustomizationState.perVisualStateGroup.push_back(
            {visualStateGroupOptionalWeakPtr, {}});
        auto* elementCustomizationStateForVisualStateGroup =
            &elementCustomizationState.perVisualStateGroup.back().second;

        ApplyCustomizationsForVisualStateGroup(
            state, handle, element, visualStateGroup, fallbackClassName,
            std::move(overridesForVisualStateGroup),
            elementCustomizationStateForVisualStateGroup);
    }
}

// XAML diagnostics, which the mod relies on to observe the visual tree, holds a
// strong reference to every element it reports. Template content that a control
// discarded therefore stays alive, still owning the children the control handed
// to it. When the control instantiates its template again, taking those
// children back fails the association check with E_INVALIDARG, and XAML turns
// that into an unhandled error which terminates the app. The Settings app hits
// this with the SplitView inside its NavigationView: `PaneRoot` binds
// `Border.Child` to `SplitView.Pane`. Hand the children back while the content
// holding them is torn down, which happens before the replacement is built.
//
// The owner is found from the Border rather than from the child: once content
// leaves the tree, neither VisualTreeHelper::GetParent nor
// FrameworkElement.Parent reports an owner for the child anymore, while
// Border.Child keeps reading fine.
std::vector<winrt::weak_ref<Controls::SplitView>> g_trackedSplitViews;

void TrackSplitView(FrameworkElement element) {
    auto splitView = element.try_as<Controls::SplitView>();
    if (!splitView) {
        return;
    }

    // An element is reported again every time it re-enters the tree, so without
    // this the same SplitView piles up.
    std::erase_if(g_trackedSplitViews,
                  [&splitView](const auto& trackedWeakPtr) {
                      auto tracked = trackedWeakPtr.get();
                      return !tracked || tracked == splitView;
                  });

    g_trackedSplitViews.push_back(winrt::make_weak(splitView));
}

void ReleaseDiscardedSplitViewChild(
    winrt::Windows::Foundation::IInspectable removedElement) {
    auto border = removedElement.try_as<Controls::Border>();
    if (!border) {
        return;
    }

    auto child = border.Child();
    if (!child) {
        return;
    }

    bool discarded = false;
    std::erase_if(g_trackedSplitViews, [&](const auto& splitViewWeakPtr) {
        auto splitView = splitViewWeakPtr.get();
        if (!splitView) {
            return true;
        }

        // A SplitView on its way out of the tree takes its content with it and
        // keeps using it once it's back, so only a SplitView that stays needs
        // its children handed back.
        if (!Media::VisualTreeHelper::GetParent(splitView)) {
            return false;
        }

        if (child == splitView.Pane() || child == splitView.Content()) {
            discarded = true;
        }

        return false;
    });

    if (!discarded) {
        return;
    }

    Wh_Log(L"Detaching %s from discarded SplitView template content",
           winrt::get_class_name(child).c_str());

    // Detaching reports the child as removed, which re-enters this function, so
    // it has to happen once the tracked SplitViews are no longer being walked.
    border.Child(nullptr);
}

void CleanupCustomizations(InstanceHandle handle) {
    auto it = g_elementsCustomizationState.find(handle);
    if (it == g_elementsCustomizationState.end()) {
        return;
    }

    // A reference rather than the iterator: restoring a style below runs
    // arbitrary XAML work that can re-enter ApplyCustomizations and rehash
    // g_elementsCustomizationState, which invalidates iterators but not
    // references to the mapped values.
    auto& elementCustomizationState = it->second;

    auto element = elementCustomizationState.element.get();
    auto* state = GetStyleVariableState();

    RestoreCapturesForElement(element, elementCustomizationState);

    // Drop this element's captures from the registry. Other elements may still
    // capture the same names, so a name only becomes undefined once its last
    // capture is gone. Runs after RestoreCapturesForElement so the
    // just-unregistered capture callbacks can't re-seed a variable
    // mid-teardown.
    std::vector<std::wstring> removedVarNames;
    if (state) {
        for (const auto& [property, captureState] :
             elementCustomizationState.captureCustomizationStates) {
            if (captureState.varName.empty()) {
                continue;
            }

            auto varIt = state->variables.find(captureState.varName);
            if (varIt == state->variables.end()) {
                continue;
            }

            if (!std::erase_if(varIt->second,
                               [handle](const StyleVariableCapture& capture) {
                                   return capture.elementHandle == handle;
                               })) {
                continue;
            }

            removedVarNames.push_back(captureState.varName);
            if (varIt->second.empty()) {
                state->variables.erase(varIt);
            }
        }
    }

    for (const auto& [visualStateGroupOptionalWeakPtrIter, stateIter] :
         elementCustomizationState.perVisualStateGroup) {
        RestoreCustomizationsForVisualStateGroup(
            state, handle, element, visualStateGroupOptionalWeakPtrIter,
            stateIter);
    }

    // By handle, not by `it`: a re-entrant apply above may have rehashed the
    // map since the lookup.
    g_elementsCustomizationState.erase(handle);

    ReapElementTreeNodesIfNeeded();

    // Deferred until this element is out of g_elementsCustomizationState, both
    // so it can't be scored as a winning capture while being torn down and so
    // the loops above don't walk state that re-entrant style applies could
    // invalidate. Every removal propagates, not just the one that left a name
    // undefined: dropping one of several captures still changes which one wins
    // for the consumers that were closest to it.
    for (const auto& varName : removedVarNames) {
        PropagateStyleVariableChange(state, varName, std::nullopt);
    }
}

using StyleConstant = std::pair<std::wstring, std::wstring>;
using StyleConstants = std::vector<StyleConstant>;

std::wstring ApplyStyleConstants(std::wstring_view style,
                                 const StyleConstants& styleConstants) {
    std::wstring result;

    size_t lastPos = 0;
    size_t findPos;

    while ((findPos = style.find('$', lastPos)) != style.npos) {
        result.append(style, lastPos, findPos - lastPos);

        const StyleConstant* constant = nullptr;
        for (const auto& s : styleConstants) {
            if (s.first == style.substr(findPos + 1, s.first.size())) {
                constant = &s;
                break;
            }
        }

        if (constant) {
            result += constant->second;
            lastPos = findPos + 1 + constant->first.size();
        } else {
            result += '$';
            lastPos = findPos + 1;
        }
    }

    // Care for the rest after last occurrence.
    result += style.substr(lastPos);

    return result;
}

std::optional<StyleConstant> ParseStyleConstant(
    std::wstring_view constant,
    const StyleConstants& styleConstants) {
    // Skip if commented.
    if (constant.starts_with(L"//")) {
        return std::nullopt;
    }

    auto eqPos = constant.find(L'=');
    if (eqPos == constant.npos) {
        Wh_Log(L"Skipping entry with no '=': %.*s",
               static_cast<int>(constant.length()), constant.data());
        return std::nullopt;
    }

    auto key = TrimStringView(constant.substr(0, eqPos));
    auto valueRaw = TrimStringView(constant.substr(eqPos + 1));
    auto value = ApplyStyleConstants(valueRaw, styleConstants);

    return StyleConstant{std::wstring(key), std::move(value)};
}

StyleConstants LoadStyleConstants(
    const std::vector<PCWSTR>& themeStyleConstants) {
    StyleConstants result;

    auto addToResult = [&result](StyleConstant sc) {
        // Keep sorted by name length to replace long names first. Reverse the
        // order to allow overriding definitions with the same name.
        auto insertIndex = std::lower_bound(
            result.begin(), result.end(), sc,
            [](const StyleConstant& a, const StyleConstant& b) {
                return a.first.size() > b.first.size();
            });

        result.insert(insertIndex, std::move(sc));
    };

    for (const auto themeStyleConstant : themeStyleConstants) {
        if (auto parsed = ParseStyleConstant(themeStyleConstant, result)) {
            addToResult(std::move(*parsed));
        }
    }

    for (int i = 0;; i++) {
        string_setting_unique_ptr constantSetting(
            Wh_GetStringSetting(L"styleConstants[%d]", i));
        if (!*constantSetting.get()) {
            break;
        }

        if (auto parsed = ParseStyleConstant(constantSetting.get(), result)) {
            addToResult(std::move(*parsed));
        }
    }

    return result;
}

ElementMatcher ElementMatcherFromString(std::wstring_view str) {
    ElementMatcher result;
    PropertyValuesUnresolved propertyValuesUnresolved;

    auto trimmed = TrimStringView(str);
    if (trimmed == L"*") {
        result.kind = ElementMatcher::Kind::Wildcard;
        return result;
    }
    if (trimmed == L":root") {
        result.kind = ElementMatcher::Kind::Root;
        return result;
    }

    auto i = str.find_first_of(L"#@[");
    result.type = TrimStringView(str.substr(0, i));
    if (result.type.empty()) {
        throw std::runtime_error("Bad target syntax, empty type");
    }

    while (i != str.npos) {
        auto iNext = str.find_first_of(L"#@[", i + 1);
        auto nextPart =
            str.substr(i + 1, iNext == str.npos ? str.npos : iNext - (i + 1));

        switch (str[i]) {
            case L'#':
                if (!result.name.empty()) {
                    throw std::runtime_error(
                        "Bad target syntax, more than one name");
                }

                result.name = TrimStringView(nextPart);
                if (result.name.empty()) {
                    throw std::runtime_error("Bad target syntax, empty name");
                }
                break;

            case L'@':
                if (result.visualStateGroupName) {
                    throw std::runtime_error(
                        "Bad target syntax, more than one visual state group");
                }

                result.visualStateGroupName = TrimStringView(nextPart);
                break;

            case L'[': {
                auto rule = TrimStringView(nextPart);
                if (rule.length() == 0 || rule.back() != L']') {
                    throw std::runtime_error("Bad target syntax, missing ']'");
                }

                rule = TrimStringView(rule.substr(0, rule.length() - 1));
                if (rule.length() == 0) {
                    throw std::runtime_error(
                        "Bad target syntax, empty property");
                }

                if (rule.find_first_not_of(L"0123456789") == rule.npos) {
                    result.oneBasedIndex = std::stoi(std::wstring(rule));
                    break;
                }

                auto ruleEqPos = rule.find(L'=');
                if (ruleEqPos == rule.npos) {
                    throw std::runtime_error(
                        "Bad target syntax, missing '=' in property");
                }

                auto ruleKey = TrimStringView(rule.substr(0, ruleEqPos));
                auto ruleVal = TrimStringView(rule.substr(ruleEqPos + 1));

                if (ruleKey.length() == 0) {
                    throw std::runtime_error(
                        "Bad target syntax, empty property name");
                }

                propertyValuesUnresolved.push_back(
                    {std::wstring(ruleKey), std::wstring(ruleVal)});
                break;
            }

            default:
                throw std::runtime_error("Bad target syntax");
        }

        i = iNext;
    }

    result.propertyValues = std::move(propertyValuesUnresolved);

    return result;
}

// Parses a single `controlStyles[*].styles[*]` entry into either a ValueRule
// (`Property[@VisualState][:]=value`) or a CaptureRule (`Property=>VarName`).
// Throws std::runtime_error on malformed input or disallowed combinations such
// as `:=>` or `@VisualState=>`.
std::variant<ValueRule, CaptureRule> ParseRule(std::wstring_view str) {
    auto eqPos = str.find(L'=');
    if (eqPos == str.npos) {
        throw std::runtime_error("Bad style syntax, '=' is missing");
    }

    auto name = str.substr(0, eqPos);
    auto value = str.substr(eqPos + 1);

    if (!value.empty() && value.front() == L'>') {
        // Capture rule: `Property=>VarName`. The right-hand side (after the
        // leading `>` marker) is the name of a mod-global style variable into
        // which the property's current value is captured.
        value = value.substr(1);

        if (!name.empty() && name.back() == L':') {
            throw std::runtime_error(
                "Bad style syntax, ':=>' is not valid (':=' XAML value "
                "cannot be combined with '=>' capture)");
        }

        if (name.find(L'@') != name.npos) {
            throw std::runtime_error(
                "Bad style syntax, '@VisualState' not allowed on a capture "
                "rule");
        }

        auto trimmedPropertyName = TrimStringView(name);
        if (trimmedPropertyName.empty()) {
            throw std::runtime_error("Bad style syntax, empty name");
        }

        auto trimmedVarName = TrimStringView(value);
        if (trimmedVarName.empty()) {
            throw std::runtime_error(
                "Bad style syntax, empty capture variable name");
        }
        if (!IsValidStyleVariableIdentifier(trimmedVarName)) {
            throw std::runtime_error(
                "Bad style syntax, invalid capture variable name");
        }

        return CaptureRule{std::wstring(trimmedPropertyName),
                           std::wstring(trimmedVarName)};
    }

    ValueRule result;
    result.value = TrimStringView(value);

    if (!name.empty() && name.back() == L':') {
        result.isXamlValue = true;
        name = name.substr(0, name.size() - 1);
    }

    auto atPos = name.find(L'@');
    if (atPos != name.npos) {
        result.visualState = TrimStringView(name.substr(atPos + 1));
        name = name.substr(0, atPos);
    }

    result.propertyName = TrimStringView(name);
    if (result.propertyName.empty()) {
        throw std::runtime_error("Bad style syntax, empty name");
    }

    return result;
}

std::wstring AdjustTypeName(std::wstring_view type) {
    if (type.find_first_of(L".:") == type.npos) {
        if (type == L"Rectangle") {
            return L"Windows.UI.Xaml.Shapes.Rectangle";
        }

        return L"Windows.UI.Xaml.Controls." + std::wstring{type};
    }

    return std::wstring{type};
}

// Splits a target string on the commas which separate targets, ignoring commas
// which are part of a `[Property=Value]` clause.
std::vector<std::wstring_view> SplitTargetString(std::wstring_view target) {
    std::vector<std::wstring_view> result;

    size_t partBegin = 0;
    bool inProperty = false;
    for (size_t i = 0; i < target.size(); i++) {
        switch (target[i]) {
            case L'[':
                inProperty = true;
                break;

            case L']':
                inProperty = false;
                break;

            case L',':
                if (!inProperty) {
                    result.push_back(target.substr(partBegin, i - partBegin));
                    partBegin = i + 1;
                }
                break;
        }
    }

    result.push_back(target.substr(partBegin));

    return result;
}

void AddElementCustomizationRulesForSingleTarget(
    std::wstring_view target,
    const std::vector<std::wstring>& styles) {
    ElementCustomizationRules elementCustomizationRules;

    auto targetParts = SplitStringView(target, L" > ");

    bool first = true;
    bool hasVisualStateGroup = false;
    for (auto i = targetParts.rbegin(); i != targetParts.rend(); ++i) {
        const auto& targetPart = *i;
        const bool isLeftmost = (i + 1 == targetParts.rend());

        auto matcher = ElementMatcherFromString(targetPart);

        const auto& prevParents =
            elementCustomizationRules.parentElementMatchers;
        const bool prevIsWildcard =
            !prevParents.empty() &&
            prevParents.back().kind == ElementMatcher::Kind::Wildcard;

        switch (matcher.kind) {
            case ElementMatcher::Kind::Element:
                matcher.type = AdjustTypeName(matcher.type);
                break;

            case ElementMatcher::Kind::Wildcard:
                if (first) {
                    throw std::runtime_error(
                        "Bad target syntax, '*' can't be the matched element");
                }
                if (isLeftmost) {
                    throw std::runtime_error(
                        "Bad target syntax, '*' can't be the leftmost target "
                        "part");
                }
                if (prevIsWildcard) {
                    throw std::runtime_error(
                        "Bad target syntax, '*' can't be adjacent to another "
                        "'*'");
                }
                break;

            case ElementMatcher::Kind::Root:
                if (first) {
                    throw std::runtime_error(
                        "Bad target syntax, ':root' can't be the matched "
                        "element");
                }
                if (!isLeftmost) {
                    throw std::runtime_error(
                        "Bad target syntax, ':root' must be the leftmost "
                        "target part");
                }
                if (prevIsWildcard) {
                    throw std::runtime_error(
                        "Bad target syntax, ':root' must be followed by a "
                        "non-wildcard target part");
                }
                break;
        }

        if (matcher.visualStateGroupName) {
            if (hasVisualStateGroup) {
                throw std::runtime_error(
                    "Element type can't have more than one visual state group");
            }

            hasVisualStateGroup = true;
        }

        if (first) {
            UnresolvedRules unresolvedRules;
            for (const auto& style : styles) {
                auto parsed = ParseRule(style);
                if (auto* valueRule = std::get_if<ValueRule>(&parsed)) {
                    unresolvedRules.valueRules.push_back(std::move(*valueRule));
                } else {
                    unresolvedRules.captureRules.push_back(
                        std::move(std::get<CaptureRule>(parsed)));
                }
            }

            elementCustomizationRules.elementMatcher = std::move(matcher);
            elementCustomizationRules.propertyOverrides =
                std::move(unresolvedRules);
        } else {
            elementCustomizationRules.parentElementMatchers.push_back(
                std::move(matcher));
        }

        first = false;
    }

    g_elementsCustomizationRules.push_back(
        std::move(elementCustomizationRules));
}

void AddElementCustomizationRules(std::wstring_view target,
                                  const std::vector<std::wstring>& styles) {
    auto targets = SplitTargetString(target);

    for (const auto& singleTarget : targets) {
        try {
            AddElementCustomizationRulesForSingleTarget(singleTarget, styles);
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error %08X for target %.*s", ex.code(),
                   static_cast<int>(singleTarget.length()),
                   singleTarget.data());
        } catch (std::exception const& ex) {
            Wh_Log(L"Error for target %.*s: %S",
                   static_cast<int>(singleTarget.length()), singleTarget.data(),
                   ex.what());
        }
    }
}

bool ProcessSingleTargetStylesFromSettings(
    int index,
    const StyleConstants& styleConstants) {
    string_setting_unique_ptr targetStringSetting(
        Wh_GetStringSetting(L"controlStyles[%d].target", index));
    if (!*targetStringSetting.get()) {
        return false;
    }

    // Skip if commented.
    if (targetStringSetting[0] == L'/' && targetStringSetting[1] == L'/') {
        return true;
    }

    Wh_Log(L"Processing styles for %s", targetStringSetting.get());

    std::vector<std::wstring> styles;

    for (int styleIndex = 0;; styleIndex++) {
        string_setting_unique_ptr styleSetting(Wh_GetStringSetting(
            L"controlStyles[%d].styles[%d]", index, styleIndex));
        if (!*styleSetting.get()) {
            break;
        }

        // Skip if commented.
        if (styleSetting[0] == L'/' && styleSetting[1] == L'/') {
            continue;
        }

        styles.push_back(
            ApplyStyleConstants(styleSetting.get(), styleConstants));
    }

    if (styles.size() > 0) {
        AddElementCustomizationRules(targetStringSetting.get(), styles);
    }

    return true;
}

std::optional<ResourceVariableEntry> ParseResourceVariable(
    std::wstring_view entry,
    const StyleConstants& styleConstants) {
    // Skip if commented.
    if (entry.starts_with(L"//")) {
        return std::nullopt;
    }

    // Find the first '=' to split key and value.
    auto eqPos = entry.find(L'=');
    if (eqPos == entry.npos) {
        Wh_Log(L"Skipping entry with no '=': %.*s",
               static_cast<int>(entry.length()), entry.data());
        return std::nullopt;
    }

    auto keyPart = TrimStringView(entry.substr(0, eqPos));
    auto valueRaw = TrimStringView(entry.substr(eqPos + 1));
    auto value = ApplyStyleConstants(valueRaw, styleConstants);

    constexpr std::wstring_view kThemeResourcePrefix = L"{ThemeResource ";

    ResourceVariableType type = ResourceVariableType::String;
    if (keyPart.size() > 0 && keyPart.back() == L':') {
        type = ResourceVariableType::Xaml;
        keyPart = keyPart.substr(0, keyPart.size() - 1);
        keyPart = TrimStringView(keyPart);
    } else if (value.starts_with(kThemeResourcePrefix) &&
               value.ends_with(L"}")) {
        type = ResourceVariableType::ThemeResourceReference;
        value = TrimStringView(
            value.substr(kThemeResourcePrefix.size(),
                         value.size() - kThemeResourcePrefix.size() - 1));
    }

    ResourceVariableTheme theme = ResourceVariableTheme::None;
    std::wstring key;

    // Check for @theme suffix in key part.
    auto atPos = keyPart.find(L'@');
    if (atPos != keyPart.npos) {
        key = TrimStringView(keyPart.substr(0, atPos));
        auto themePart = TrimStringView(keyPart.substr(atPos + 1));
        if (themePart == L"Dark") {
            theme = ResourceVariableTheme::Dark;
        } else if (themePart == L"Light") {
            theme = ResourceVariableTheme::Light;
        } else {
            Wh_Log(L"Unknown theme '%.*s', expected 'Dark' or 'Light'",
                   static_cast<int>(themePart.size()), themePart.data());
            return std::nullopt;
        }
    } else {
        key = std::wstring(keyPart);
    }

    return ResourceVariableEntry{std::move(key), std::move(value), theme, type};
}

winrt::Windows::Foundation::IInspectable ParseXamlValue(
    std::wstring_view xamlValue) {
    std::wstring xaml;
    xaml += L"        <Setter Property=\"Tag\">\n";
    xaml += L"            <Setter.Value>\n";
    xaml += xamlValue;
    xaml += L"\n";
    xaml += L"            </Setter.Value>\n";
    xaml += L"        </Setter>\n";

    auto style = GetStyleFromXamlSetters(L"FrameworkElement", xaml);
    return style.Setters().GetAt(0).as<Setter>().Value();
}

bool ProcessResourceVariable(ResourceDictionary resources,
                             ResourceDictionary darkDict,
                             ResourceDictionary lightDict,
                             const ResourceVariableEntry& entry) {
    auto boxedKey = winrt::box_value(entry.key);

    if (entry.theme != ResourceVariableTheme::None) {
        ResourceDictionary& targetDict =
            entry.theme == ResourceVariableTheme::Dark ? darkDict : lightDict;

        if (targetDict.HasKey(boxedKey)) {
            Wh_Log(
                L"Resource variable key '%s' already exists in theme '%s', "
                L"skipping",
                entry.key.c_str(),
                entry.theme == ResourceVariableTheme::Dark ? L"Dark"
                                                           : L"Light");
            return false;
        }

        winrt::Windows::Foundation::IInspectable value;
        switch (entry.type) {
            case ResourceVariableType::String:
                value = winrt::box_value(entry.value);
                break;
            case ResourceVariableType::Xaml:
                value =
                    entry.value.empty() ? nullptr : ParseXamlValue(entry.value);
                break;
            case ResourceVariableType::ThemeResourceReference:
                value = resources.Lookup(winrt::box_value(entry.value));
                break;
        }

        targetDict.Insert(boxedKey, value);

        return true;
    }

    // key= - convert using existing resource type.
    auto existingResource = resources.TryLookup(boxedKey);
    if (!existingResource) {
        Wh_Log(L"Resource variable key '%s' not found, skipping",
               entry.key.c_str());
        return false;
    }

    auto [it, inserted] =
        g_originalResourceValues.try_emplace(entry.key, existingResource);
    if (!inserted) {
        Wh_Log(L"Resource variable key '%s' already modified, skipping",
               entry.key.c_str());
        return false;
    }

    winrt::Windows::Foundation::IInspectable value;
    switch (entry.type) {
        case ResourceVariableType::String: {
            auto resourceClassName = winrt::get_class_name(existingResource);

            // Unwrap IReference<T> to get inner type name.
            if (resourceClassName.starts_with(
                    L"Windows.Foundation.IReference`1<") &&
                resourceClassName.ends_with(L'>')) {
                size_t prefixSize =
                    sizeof("Windows.Foundation.IReference`1<") - 1;
                resourceClassName =
                    winrt::hstring(resourceClassName.data() + prefixSize,
                                   resourceClassName.size() - prefixSize - 1);
            }

            value = Markup::XamlBindingHelper::ConvertValue(
                Interop::TypeName{resourceClassName},
                winrt::box_value(entry.value));
            break;
        }

        case ResourceVariableType::Xaml:
            value = entry.value.empty() ? nullptr : ParseXamlValue(entry.value);
            break;

        case ResourceVariableType::ThemeResourceReference:
            value = resources.Lookup(winrt::box_value(entry.value));
            break;
    }

    resources.Insert(boxedKey, value);

    return true;
}

void RefreshThemeResourceEntries() {
    if (g_resourceVariables.empty()) {
        return;
    }

    Wh_Log(L"Refreshing theme resource entries");

    auto resources = StmAppResources();
    if (!resources) {
        return;
    }

    auto darkDict = g_resourceVariablesThemeDict.ThemeDictionaries()
                        .TryLookup(winrt::box_value(L"Dark"))
                        .try_as<ResourceDictionary>();
    auto lightDict = g_resourceVariablesThemeDict.ThemeDictionaries()
                         .TryLookup(winrt::box_value(L"Light"))
                         .try_as<ResourceDictionary>();

    for (const auto& entry : g_resourceVariables) {
        if (entry.type != ResourceVariableType::ThemeResourceReference) {
            continue;
        }

        try {
            auto boxedKey = winrt::box_value(entry.key);
            auto value = resources.Lookup(winrt::box_value(entry.value));

            if (entry.theme == ResourceVariableTheme::Dark && darkDict) {
                darkDict.Insert(boxedKey, value);
            } else if (entry.theme == ResourceVariableTheme::Light &&
                       lightDict) {
                lightDict.Insert(boxedKey, value);
            } else {
                resources.Insert(boxedKey, value);
            }
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error refreshing '%s': %08X", entry.key.c_str(),
                   ex.code());
        }
    }
}

std::vector<ResourceVariableEntry> ProcessResourceVariablesFromSettings(
    const StyleConstants& styleConstants,
    const std::vector<PCWSTR>& themeResourceVariables) {
    std::vector<ResourceVariableEntry> resourceVariables;

    for (const auto& themeResourceVariable : themeResourceVariables) {
        Wh_Log(L"Processing theme resource variable %s", themeResourceVariable);

        auto parsed =
            ParseResourceVariable(themeResourceVariable, styleConstants);
        if (parsed) {
            resourceVariables.push_back(std::move(*parsed));
        }
    }

    for (int i = 0;; i++) {
        string_setting_unique_ptr setting(
            Wh_GetStringSetting(L"themeResourceVariables[%d]", i));
        if (!*setting.get()) {
            break;
        }

        Wh_Log(L"Processing resource variable %s", setting.get());

        auto parsed = ParseResourceVariable(setting.get(), styleConstants);
        if (parsed) {
            resourceVariables.push_back(std::move(*parsed));
        }
    }

    return resourceVariables;
}

void MergeResourceVariables() {
    auto resources = StmAppResources();
    if (!resources) {
        return;
    }

    // Create theme dictionaries for @Dark/@Light resources.
    g_resourceVariablesThemeDict = ResourceDictionary();
    ResourceDictionary darkDict;
    ResourceDictionary lightDict;
    bool hasThemeResources = false;
    bool hasThemeResourceReferences = false;

    for (auto it = g_resourceVariables.rbegin();
         it != g_resourceVariables.rend(); ++it) {
        Wh_Log(L"Processing resource variable %s", it->key.c_str());

        try {
            if (ProcessResourceVariable(resources, darkDict, lightDict, *it)) {
                if (it->theme != ResourceVariableTheme::None) {
                    hasThemeResources = true;
                }

                if (it->type == ResourceVariableType::ThemeResourceReference) {
                    hasThemeResourceReferences = true;
                }
            }
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        } catch (std::exception const& ex) {
            Wh_Log(L"Error: %S", ex.what());
        }
    }

    if (hasThemeResources) {
        g_resourceVariablesThemeDict.ThemeDictionaries().Insert(
            winrt::box_value(L"Dark"), darkDict);
        g_resourceVariablesThemeDict.ThemeDictionaries().Insert(
            winrt::box_value(L"Light"), lightDict);

        resources.MergedDictionaries().Append(g_resourceVariablesThemeDict);
    }

    // Register for color changes to refresh theme resource references.
    if (hasThemeResourceReferences) {
        g_uiSettings = winrt::Windows::UI::ViewManagement::UISettings();
        auto dispatcherQueue =
            winrt::Windows::System::DispatcherQueue::GetForCurrentThread();
        g_colorValuesChangedToken =
            g_uiSettings.ColorValuesChanged([dispatcherQueue](auto&&, auto&&) {
                dispatcherQueue.TryEnqueue(RefreshThemeResourceEntries);
            });
    }
}

void ProcessAllStylesFromSettings() {
    PCWSTR themeName = Wh_GetStringSetting(L"theme");
    const Theme* theme = nullptr;
    if (wcscmp(themeName, L"Mocha") == 0) {
        theme = &g_themeMocha;
    }
    Wh_FreeStringSetting(themeName);

    StyleConstants styleConstants = LoadStyleConstants(
        theme ? theme->styleConstants : std::vector<PCWSTR>{});

    if (theme) {
        for (const auto& themeTargetStyle : theme->targetStyles) {
            try {
                std::vector<std::wstring> styles;
                styles.reserve(themeTargetStyle.styles.size());
                for (const auto& s : themeTargetStyle.styles) {
                    styles.push_back(ApplyStyleConstants(s, styleConstants));
                }

                AddElementCustomizationRules(themeTargetStyle.target, styles);
            } catch (winrt::hresult_error const& ex) {
                Wh_Log(L"Error %08X", ex.code());
            } catch (std::exception const& ex) {
                Wh_Log(L"Error: %S", ex.what());
            }
        }
    }

    for (int i = 0;; i++) {
        try {
            if (!ProcessSingleTargetStylesFromSettings(i, styleConstants)) {
                break;
            }
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        } catch (std::exception const& ex) {
            Wh_Log(L"Error: %S", ex.what());
        }
    }

    g_resourceVariables = ProcessResourceVariablesFromSettings(
        styleConstants,
        theme ? theme->themeResourceVariables : std::vector<PCWSTR>{});
}

void UninitializeResourceVariables() {
    // Unregister color change handler.
    if (g_colorValuesChangedToken) {
        g_uiSettings.ColorValuesChanged(g_colorValuesChangedToken);
        g_colorValuesChangedToken = {};
    }
    g_uiSettings = nullptr;
    g_resourceVariables.clear();

    // Restore original resource values.
    auto resources = StmAppResources();
    if (!resources) {
        return;
    }
    for (const auto& [key, originalValue] : g_originalResourceValues) {
        try {
            resources.Insert(winrt::box_value(key), originalValue);
        } catch (...) {
            HRESULT hr = winrt::to_hresult();
            Wh_Log(L"Error %08X", hr);
        }
    }
    g_originalResourceValues.clear();

    // Remove our merged theme dictionary.
    if (g_resourceVariablesThemeDict) {
        auto merged = resources.MergedDictionaries();
        uint32_t index;
        if (merged.IndexOf(g_resourceVariablesThemeDict, index)) {
            merged.RemoveAt(index);
        }
        g_resourceVariablesThemeDict = nullptr;
    }
}

void UninitializeSettingsAndTap() {
    // Clear tracked image brushes for this thread (revokers will automatically
    // unregister).
    if (auto& timer = g_trackedImageBrushesForThread.retryDebounceTimer) {
        try {
            timer.Stop();
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        }
    }
    g_trackedImageBrushesForThread.retryDebounceTimerTickRevoker.revoke();
    g_trackedImageBrushesForThread.retryDebounceTimer = nullptr;
    g_trackedImageBrushesForThread.brushes.clear();
    StopImageLoadRetriesForCurrentThread();

    for (const auto& [handle, elementCustomizationState] :
         g_elementsCustomizationState) {
        auto element = elementCustomizationState.element.get();
        auto* state = GetStyleVariableState();

        RestoreCapturesForElement(element, elementCustomizationState);

        for (const auto& [visualStateGroupOptionalWeakPtrIter, stateIter] :
             elementCustomizationState.perVisualStateGroup) {
            RestoreCustomizationsForVisualStateGroup(
                state, handle, element, visualStateGroupOptionalWeakPtrIter,
                stateIter);
        }
    }

    // Before g_elementTreeNodes, since the states hold the last strong refs to
    // the spine nodes.
    g_elementsCustomizationState.clear();
    g_elementTreeNodes.clear();
    g_elementTreeNodesReapThreshold = 64;
    g_pendingStyleVariablePropagations.clear();
    g_styleVariableState = {};

    g_elementsCustomizationRules.clear();
    g_trackedSplitViews.clear();

    UninitializeResourceVariables();

    g_targetThreadId = 0;
}

void InitializeSettingsAndTap() {
    DWORD kNoThreadId = 0;
    if (!g_targetThreadId.compare_exchange_strong(kNoThreadId,
                                                  GetCurrentThreadId())) {
        return;
    }

    ProcessAllStylesFromSettings();

    HRESULT hr = InjectWindhawkTAP();
    if (FAILED(hr)) {
        Wh_Log(L"Error %08X", hr);
    }
}

using RunFromWindowThreadProc_t = void(WINAPI*)(PVOID parameter);

bool RunFromWindowThread(HWND hWnd,
                         RunFromWindowThreadProc_t proc,
                         PVOID procParam) {
    static const UINT runFromWindowThreadRegisteredMsg =
        RegisterWindowMessage(L"Windhawk_RunFromWindowThread_" WH_MOD_ID);

    struct RUN_FROM_WINDOW_THREAD_PARAM {
        RunFromWindowThreadProc_t proc;
        PVOID procParam;
    };

    DWORD dwThreadId = GetWindowThreadProcessId(hWnd, nullptr);
    if (dwThreadId == 0) {
        return false;
    }

    if (dwThreadId == GetCurrentThreadId()) {
        proc(procParam);
        return true;
    }

    HHOOK hook = SetWindowsHookEx(
        WH_CALLWNDPROC,
        [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT {
            if (nCode == HC_ACTION) {
                const CWPSTRUCT* cwp = (const CWPSTRUCT*)lParam;
                if (cwp->message == runFromWindowThreadRegisteredMsg) {
                    RUN_FROM_WINDOW_THREAD_PARAM* param =
                        (RUN_FROM_WINDOW_THREAD_PARAM*)cwp->lParam;
                    param->proc(param->procParam);
                }
            }

            return CallNextHookEx(nullptr, nCode, wParam, lParam);
        },
        nullptr, dwThreadId);
    if (!hook) {
        return false;
    }

    RUN_FROM_WINDOW_THREAD_PARAM param;
    param.proc = proc;
    param.procParam = procParam;
    SendMessage(hWnd, runFromWindowThreadRegisteredMsg, 0, (LPARAM)&param);

    UnhookWindowsHookEx(hook);

    return true;
}

bool RunFromWindowThreadViaPostMessage(HWND hWnd,
                                       RunFromWindowThreadProc_t proc,
                                       PVOID procParam) {
    static const UINT runFromWindowThreadRegisteredMsgViaPostMessage =
        RegisterWindowMessage(
            L"Windhawk_RunFromWindowThreadViaPostMessage_" WH_MOD_ID);

    struct RUN_FROM_WINDOW_THREAD_PARAM {
        RunFromWindowThreadProc_t proc;
        PVOID procParam;
        HHOOK hook;
    };

    DWORD dwThreadId = GetWindowThreadProcessId(hWnd, nullptr);
    if (dwThreadId == 0) {
        return false;
    }

    HHOOK hook = SetWindowsHookEx(
        WH_GETMESSAGE,
        [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT {
            if (nCode == HC_ACTION && wParam == PM_REMOVE) {
                MSG* msg = (MSG*)lParam;
                if (msg->message ==
                    runFromWindowThreadRegisteredMsgViaPostMessage) {
                    auto* param = (RUN_FROM_WINDOW_THREAD_PARAM*)msg->lParam;
                    if (param) {
                        param->proc(param->procParam);
                        UnhookWindowsHookEx(param->hook);
                        delete param;
                        msg->lParam = 0;
                    }
                }
            }

            return CallNextHookEx(nullptr, nCode, wParam, lParam);
        },
        nullptr, dwThreadId);
    if (!hook) {
        return false;
    }

    auto* param = new RUN_FROM_WINDOW_THREAD_PARAM{
        .proc = proc,
        .procParam = procParam,
        .hook = hook,
    };
    if (!PostMessage(hWnd, runFromWindowThreadRegisteredMsgViaPostMessage, 0,
                     (LPARAM)param)) {
        UnhookWindowsHookEx(hook);
        delete param;
        return false;
    }

    return true;
}


// ---------------------------------------------------------------------------
// Task Manager side: every tweak hooks in here, and the Mocha look is applied
// to Task Manager's XAML from its own window thread.
// ---------------------------------------------------------------------------
namespace stm_app {

bool g_on_navborder = false;
bool g_on_detailsicon = false;
bool g_on_pause = false;
bool g_on_esc = false;
bool g_on_linkspeed = false;
bool g_on_netbytes = false;
bool g_on_tabslide = false;
bool g_on_tallertab = false;
std::atomic<bool> g_pollStop = false;
HANDLE g_pollThread = nullptr;
HWND g_styledWnd = nullptr;

BOOL CALLBACK FindTaskMgrProc(HWND hwnd, LPARAM lp) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != GetCurrentProcessId()) return TRUE;
    WCHAR cls[64]{};
    GetClassNameW(hwnd, cls, ARRAYSIZE(cls));
    if (wcscmp(cls, L"TaskManagerWindow") == 0) {
        *(HWND*)lp = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND FindTaskMgrWindow() {
    HWND found = nullptr;
    EnumWindows(FindTaskMgrProc, (LPARAM)&found);
    return found;
}

bool LookWanted() {
    if (Wh_GetIntValue(L"enabled", 1) == 0) return false;
    PCWSTR theme = Wh_GetStringSetting(L"theme");
    bool want = theme && *theme;
    Wh_FreeStringSetting(theme);
    return want;
}

void WINAPI InitProc(PVOID) {
    InitializeSettingsAndTap();
}

void WINAPI UninitProc(PVOID) {
    UninitializeSettingsAndTap();
}

void StopLook() {
    if (!g_styledWnd) return;
    StopImageLoadRetries();
    if (g_visualTreeWatcher) {
        g_visualTreeWatcher->UnadviseVisualTreeChange();
        g_visualTreeWatcher = nullptr;
    }
    if (IsWindow(g_styledWnd)) RunFromWindowThread(g_styledWnd, UninitProc, nullptr);
    g_styledWnd = nullptr;
    Wh_Log(L"Mocha look off");
}

DWORD WINAPI PollThreadProc(LPVOID) {
    int seen = 0;
    int tick = 0;
    bool want = LookWanted();
    while (!g_pollStop.load()) {
        if (++tick >= 20) {
            tick = 0;
            want = LookWanted();
        }
        if (want && !g_styledWnd) {
            HWND hwnd = FindTaskMgrWindow();
            if (hwnd && GetModuleHandleW(L"Windows.UI.Xaml.dll")) {
                // Give the window half a second to build its XAML first.
                if (++seen >= 10) {
                    if (RunFromWindowThread(hwnd, InitProc, nullptr)) {
                        g_styledWnd = hwnd;
                        Wh_Log(L"Mocha look on");
                    }
                    seen = 0;
                }
            } else {
                seen = 0;
            }
        } else if (!want && g_styledWnd) {
            StopLook();
        } else if (g_styledWnd && !IsWindow(g_styledWnd)) {
            g_styledWnd = nullptr;
        }
        Sleep(50);
    }
    return 0;
}

bool Init() {
    if (Wh_GetIntSetting(L"featureNavBorder")) {
        g_on_navborder = f_navborder::ModInit() != FALSE;
        Wh_Log(L"disable-taskmgr-navigation-border: %s", g_on_navborder ? L"started" : L"failed to start");
    }
    if (Wh_GetIntSetting(L"featureDetailsIcon")) {
        g_on_detailsicon = f_detailsicon::ModInit() != FALSE;
        Wh_Log(L"fix-taskmgr-details-icon-size: %s", g_on_detailsicon ? L"started" : L"failed to start");
    }
    if (Wh_GetIntSetting(L"featurePauseButton")) {
        g_on_pause = f_pause::ModInit() != FALSE;
        Wh_Log(L"task-manager-pause-button: %s", g_on_pause ? L"started" : L"failed to start");
    }
    if (Wh_GetIntSetting(L"featureEsc")) {
        g_on_esc = f_esc::ModInit() != FALSE;
        Wh_Log(L"taskmgr-esc: %s", g_on_esc ? L"started" : L"failed to start");
    }
    if (Wh_GetIntSetting(L"featureLinkSpeed")) {
        g_on_linkspeed = f_linkspeed::ModInit() != FALSE;
        Wh_Log(L"taskmgr-link-speed: %s", g_on_linkspeed ? L"started" : L"failed to start");
    }
    if (Wh_GetIntSetting(L"featureNetworkBytes")) {
        g_on_netbytes = f_netbytes::ModInit() != FALSE;
        Wh_Log(L"taskmgr-network-bytes: %s", g_on_netbytes ? L"started" : L"failed to start");
    }
    if (Wh_GetIntSetting(L"featureTabSlide")) {
        g_on_tabslide = f_tabslide::ModInit() != FALSE;
        Wh_Log(L"taskmgr-tab-slide-animation: %s", g_on_tabslide ? L"started" : L"failed to start");
    }
    if (Wh_GetIntSetting(L"featureTallerTab")) {
        g_on_tallertab = f_tallertab::ModInit() != FALSE;
        Wh_Log(L"taskmgr-taller-tab: %s", g_on_tallertab ? L"started" : L"failed to start");
    }
    g_pollStop = false;
    g_pollThread = CreateThread(nullptr, 0, PollThreadProc, nullptr, 0, nullptr);
    return true;
}

void BeforeUninit() {
    if (g_on_pause) f_pause::ModBeforeUninit();
}

void Uninit() {
    g_pollStop = true;
    if (g_pollThread) {
        WaitForSingleObject(g_pollThread, 3000);
        CloseHandle(g_pollThread);
        g_pollThread = nullptr;
    }
    StopLook();
    if (g_on_pause) f_pause::ModUninit();
    if (g_on_esc) f_esc::ModUninit();
    if (g_on_linkspeed) f_linkspeed::ModUninit();
    if (g_on_netbytes) f_netbytes::ModUninit();
    if (g_on_tabslide) f_tabslide::ModUninit();
}

}  // namespace stm_app

// ---------------------------------------------------------------------------
// Which side runs where: Windhawk starts the tool side in its own helper, and
// Task Manager gets the tweaks and the look.
// ---------------------------------------------------------------------------
static bool g_inApp = false;

static bool IsWindhawkHost() {
    wchar_t path[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, path, MAX_PATH)) return false;
    const wchar_t* name = wcsrchr(path, L'\\');
    name = name ? name + 1 : path;
    return _wcsicmp(name, L"windhawk.exe") == 0 ||
           _wcsicmp(name, L"windhawk-mod.exe") == 0 ||
           _wcsicmp(name, L"windhawk-mod-elevated.exe") == 0;
}

BOOL WhToolLauncher_ModInit(BOOL* launch) {
    if (IsWindhawkHost()) {
        *launch = TRUE;
        return TRUE;
    }
    *launch = FALSE;
    if (!stm_app::Init()) return FALSE;
    g_inApp = true;
    return TRUE;
}

void WhToolLauncher_ModAfterInit() {
}

void WhToolLauncher_ModSettingsChanged(BOOL* reload) {
    // A full reload starts every tweak again with the new settings.
    *reload = TRUE;
}

void WhToolLauncher_ModBeforeUninit() {
    if (g_inApp) stm_app::BeforeUninit();
}

void WhToolLauncher_ModUninit() {
    if (g_inApp) stm_app::Uninit();
}

#if __has_include(<windhawk_tool_mod.h>)
#include <windhawk_tool_mod.h>
#else

////////////////////////////////////////////////////////////////////////////////
// Windhawk 1.x: the same split as windhawk_tool_mod.h. The helper runs in a
// dedicated windhawk.exe process; every other included process gets the
// launcher callbacks above.
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process

bool g_isToolModProcessLauncher;
bool g_launchToolModProcess;
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

    BOOL launch = TRUE;
    if (!WhToolLauncher_ModInit(&launch)) {
        return FALSE;
    }
    g_isToolModProcessLauncher = true;
    g_launchToolModProcess = launch;
    return TRUE;
}

static void LaunchToolModProcess() {
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

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }
    if (g_launchToolModProcess) {
        LaunchToolModProcess();
    }
    WhToolLauncher_ModAfterInit();
}

void Wh_ModBeforeUninit() {
    if (g_isToolModProcessLauncher) {
        WhToolLauncher_ModBeforeUninit();
    }
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        BOOL reload = FALSE;
        WhToolLauncher_ModSettingsChanged(&reload);
        // 1.x has no reload request here; start the helper if it is gone.
        if (reload && g_launchToolModProcess) {
            HANDLE m = OpenMutexW(SYNCHRONIZE, FALSE, L"windhawk-tool-mod_" WH_MOD_ID);
            if (m) CloseHandle(m);
            else if (GetLastError() == ERROR_FILE_NOT_FOUND) LaunchToolModProcess();
        }
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        WhToolLauncher_ModUninit();
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}

#endif
