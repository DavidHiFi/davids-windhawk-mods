// ==WindhawkMod==
// @id              seamless-autoclicker
// @name            Seamless AutoClicker
// @description     Hold a side mouse button and left click keeps clicking, with a lock, a tray switch and its own settings window
// @version         1.6.4
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshlwapi -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -ladvapi32 -lurlmon -lwininet
// @license         GPL-3.0
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// Source code is published under The GNU General Public License v3.0.
//
// For bug reports and feature requests, please open an issue here:
// https://github.com/DavidHiFi/davids-windhawk-mods/issues

// ==WindhawkModReadme==
/*
# Seamless AutoClicker

Hold a side mouse button and the left button together, and the left button
keeps clicking until you let go. It runs in the background on its own, so it
doesn't touch Explorer or the app you click in.

![Seamless AutoClicker settings](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-autoclicker.png)

## How to use

1. Hold the side button picked in the settings.
2. Hold the left button. Left clicks repeat at the speed you set.
3. Let go to stop.
4. To keep it clicking hands-free, press right click while it clicks. It
   keeps going after you let go. Press right click again, or start a new
   hold, to stop.

Each click is a real press and release, so games that skip zero-length clicks
still count it. The mod runs as administrator, so it also works over windows
opened as administrator.

## Turning it off

- Click the tray icon to turn auto clicking off or on. A blue pointer means
  on, a grey pause sign means off. While off, every mouse button works as
  normal, side buttons included.
- Right-click the tray icon for the same switch and the settings window.
- Set a shortcut in the settings to switch it from the keyboard.

## G-Shift on the mouse itself

If the side button is set to G-Shift in Logitech's Onboard Memory Manager,
Windows never sees that button. The mouse instead sends "forward" for left
click and "back" for right click while G-Shift is held. Pick
**G-Shift (onboard memory)** as the hold button and the mod reads it that way:
G-Shift + left clicks, add right to lock it on. The G-Shift layer's wheel
click (for example a DPI cycle) keeps working.

## Settings

The mod has its own settings window (tray icon, right-click, Settings), and
the same settings are on this page.

- **Hold button**: side button 1, side button 2, or G-Shift (onboard memory).
- **Right click locks clicking on**: while auto clicking, right click keeps it
  clicking with nothing held.
- **Click interval (milliseconds)**: 16 to 1000 ms (Suggested: 33, about 30
  clicks a second). Lower is faster.
- **Turn auto clicking on or off**: an optional keyboard shortcut.
- **Tray icon**, and how the settings window looks.

## Credits

Original work by DavidHiFi, released under GPL-3.0. Colours from Catppuccin
Mocha (https://github.com/catppuccin/catppuccin).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- activatorButton: "back"
  $name: "Hold button"
  $description: "What you hold together with left click to start auto clicking."
  $options:
  - back: "Side button 1 (back)"
  - forward: "Side button 2 (forward)"
  - gshift: "G-Shift (onboard memory, left sends forward, right sends back)"
- toggleWithRightClick: true
  $name: "Right click locks clicking on"
  $description: "While auto clicking, press right click and the clicking keeps going after you let go. Press right click again to stop."
- clickIntervalMs: 33
  $name: "Click interval (milliseconds)"
  $description: "Time between clicks, press and release included. 16 to 1000 (Suggested: 33, about 30 clicks a second). Lower is faster."
- toggleHotkey: ""
  $name: "Turn auto clicking on or off"
  $description: "Press the keys in the box. Backspace clears it. The tray icon does the same."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it to turn auto clicking on or off. Right-click it for these settings. When off, change settings in Windhawk."
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
#include <d2d1effects.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include <windhawk_tool_mod.h>

namespace acset {
void OpenSettingsWindow();
void CloseSettingsWindow();
extern std::atomic<HWND> g_settingsWnd;
}  // namespace acset

void WhTool_ModUninit();

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

// ---------------------------------------------------------------------------
// Clicking: a low-level mouse hook reads the buttons, a second thread clicks.
// ---------------------------------------------------------------------------

// Tagged onto synthetic clicks so the hook can ignore its own output.
constexpr ULONG_PTR kSyntheticTag = 0xA17CA17C;

enum Mode { kModeBack = 0, kModeForward = 1, kModeGShift = 2 };
const PCWSTR kModeNames[] = {L"side button 1", L"side button 2", L"G-Shift"};

std::atomic<bool> g_stop = false;
// Off from the tray icon or the shortcut: every button passes through untouched.
std::atomic<bool> g_enabled = true;
std::atomic<int> g_halfMs = 16;
std::atomic<int> g_mode = kModeBack;
// Side-button mode: the hold button is down (it is swallowed, so only the
// hook knows). G-Shift mode: "forward" is down, which is left under G-Shift.
std::atomic<bool> g_holdDown = false;
std::atomic<bool> g_leftDown = false;
// Right click during a burst keeps it clicking with no buttons held.
std::atomic<bool> g_latched = false;
std::atomic<bool> g_toggleRight = true;
// Hook thread only: swallow the release that matches a swallowed press.
bool g_swallowRightUp = false;
bool g_swallowBackUp = false;

// UI thread only, read from the settings.
bool g_trayIconOn = true;
std::wstring g_hotkeyText;

HMODULE g_module = nullptr;
DWORD g_hookThreadId = 0;
DWORD g_uiThreadId = 0;
HANDLE g_hookThread = nullptr;
HANDLE g_clickThread = nullptr;
HANDLE g_uiThread = nullptr;
HANDLE g_readyEvent = nullptr;
HANDLE g_uiReady = nullptr;
HANDLE g_instanceMutex = nullptr;
HWND g_msgWnd = nullptr;

void SendLeft(DWORD flags) {
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = flags;
    input.mi.dwExtraInfo = kSyntheticTag;
    SendInput(1, &input, sizeof(INPUT));
}

bool IsElevated() {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
        return false;
    }
    TOKEN_ELEVATION elevation{};
    DWORD bytes = 0;
    bool ok = GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &bytes);
    CloseHandle(token);
    return ok && elevation.TokenIsElevated;
}

// The user is holding the clicking gesture right now.
bool Clicking() {
    bool hold = g_holdDown.load(std::memory_order_relaxed);
    if (g_mode.load(std::memory_order_relaxed) == kModeGShift) {
        return hold;
    }
    return hold && g_leftDown.load(std::memory_order_relaxed);
}

bool Active() {
    return g_enabled.load(std::memory_order_relaxed) &&
           (Clicking() || g_latched.load(std::memory_order_relaxed));
}

void SetLatch(bool on, PCWSTR why) {
    g_latched.store(on, std::memory_order_relaxed);
    Wh_Log(L"Lock %s (%s)", on ? L"on" : L"off", why);
}

int HoldButton(int mode) {
    return mode == kModeBack ? XBUTTON1 : XBUTTON2;
}

// Off: pass every button through, except the release of a press that was
// swallowed before the switch, so no app sees a lone "up".
LRESULT DisabledMouseProc(WPARAM wParam, const MSLLHOOKSTRUCT* data) {
    switch (wParam) {
    case WM_LBUTTONDOWN:
        g_leftDown.store(true, std::memory_order_relaxed);
        break;
    case WM_LBUTTONUP:
        g_leftDown.store(false, std::memory_order_relaxed);
        break;
    case WM_RBUTTONUP:
        if (g_swallowRightUp) {
            g_swallowRightUp = false;
            return 1;
        }
        break;
    case WM_XBUTTONUP: {
        int button = HIWORD(data->mouseData);
        if (button == HoldButton(g_mode.load(std::memory_order_relaxed)) &&
            g_holdDown.load(std::memory_order_relaxed)) {
            g_holdDown.store(false, std::memory_order_relaxed);
            return 1;
        }
        if (button == XBUTTON1 && g_swallowBackUp) {
            g_swallowBackUp = false;
            return 1;
        }
        break;
    }
    }
    return 0;
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode != HC_ACTION || !lParam) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }
    auto* data = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
    if (data->dwExtraInfo == kSyntheticTag) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }
    if (!g_enabled.load(std::memory_order_relaxed)) {
        if (DisabledMouseProc(wParam, data)) {
            return 1;
        }
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    int mode = g_mode.load(std::memory_order_relaxed);
    bool toggle = g_toggleRight.load(std::memory_order_relaxed);
    bool latched = g_latched.load(std::memory_order_relaxed);

    switch (wParam) {
    case WM_LBUTTONDOWN:
        g_leftDown.store(true, std::memory_order_relaxed);
        break;
    case WM_LBUTTONUP:
        g_leftDown.store(false, std::memory_order_relaxed);
        break;

    case WM_RBUTTONDOWN:
        // A real right click: G-Shift is not held (or this is a side-button
        // mode). It locks a running burst on, or stops a locked one.
        if (toggle && (latched || Clicking())) {
            SetLatch(!latched, L"right click");
            g_swallowRightUp = true;
            return 1;
        }
        break;
    case WM_RBUTTONUP:
        if (g_swallowRightUp) {
            g_swallowRightUp = false;
            return 1;
        }
        break;

    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP: {
        bool down = wParam == WM_XBUTTONDOWN;
        int button = HIWORD(data->mouseData);

        if (mode == kModeGShift) {
            if (button == XBUTTON2) {
                // Left click under G-Shift. A new hold ends a locked burst;
                // clicking then carries on until it is let go.
                g_holdDown.store(down, std::memory_order_relaxed);
                if (down && latched) {
                    SetLatch(false, L"new hold");
                }
                return 1;
            }
            // XBUTTON1 is right click under G-Shift, but also the real back
            // button. Only while clicking or locked is it taken as right.
            if (down && (g_holdDown.load(std::memory_order_relaxed) || latched)) {
                if (toggle) {
                    SetLatch(!latched, L"G-Shift right");
                }
                g_swallowBackUp = true;
                return 1;
            }
            if (!down && g_swallowBackUp) {
                g_swallowBackUp = false;
                return 1;
            }
            break;
        }

        if (button == HoldButton(mode)) {
            g_holdDown.store(down, std::memory_order_relaxed);
            if (down && latched) {
                SetLatch(false, L"new hold");
            }
            // Swallow the hold button so apps never see it, G Hub style.
            return 1;
        }
        break;
    }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

DWORD WINAPI HookThreadProc(LPVOID) {
    HHOOK hook = SetWindowsHookExW(WH_MOUSE_LL, LowLevelMouseProc, g_module, 0);
    if (!hook) {
        Wh_Log(L"SetWindowsHookEx(WH_MOUSE_LL) failed: %u", GetLastError());
        SetEvent(g_readyEvent);
        return 0;
    }

    // Touch the message queue before signalling ready so WM_QUIT can't race it.
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    SetEvent(g_readyEvent);

    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnhookWindowsHookEx(hook);
    return 0;
}

// Sleep() rounds up to the 15.6 ms system tick, so a 16 ms half-click took
// about 31 ms and 30 CPS came out near 17. A high-resolution waitable timer
// keeps the set rate without changing the global timer resolution.
HANDLE g_clickTimer = nullptr;

void ClickWait(int ms) {
    if (g_clickTimer) {
        LARGE_INTEGER due;
        due.QuadPart = -static_cast<LONGLONG>(ms) * 10000;
        if (SetWaitableTimer(g_clickTimer, &due, 0, nullptr, nullptr, FALSE)) {
            WaitForSingleObject(g_clickTimer, INFINITE);
            return;
        }
    }
    Sleep(static_cast<DWORD>(ms));
}

DWORD WINAPI ClickThreadProc(LPVOID) {
    g_clickTimer = CreateWaitableTimerExW(nullptr, nullptr,
        CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
    bool lastSentDown = false;
    int burstClicks = -1;
    while (!g_stop.load(std::memory_order_relaxed)) {
        if (Active()) {
            if (burstClicks < 0) {
                burstClicks = 0;
            }
            burstClicks++;
            // Up first: in side-button modes the real press is already down.
            int half = std::max(1, g_halfMs.load(std::memory_order_relaxed));
            SendLeft(MOUSEEVENTF_LEFTUP);
            lastSentDown = false;
            ClickWait(half);
            if (g_stop.load(std::memory_order_relaxed)) {
                break;
            }
            // Press again only while still active, so a release always ends
            // the burst with left up.
            if (Active()) {
                SendLeft(MOUSEEVENTF_LEFTDOWN);
                lastSentDown = true;
            }
            ClickWait(half);
        } else {
            // The real release can land between the check and the synthetic
            // press. If Windows still thinks left is down, release it.
            if (lastSentDown && !g_leftDown.load(std::memory_order_relaxed) &&
                (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
                SendLeft(MOUSEEVENTF_LEFTUP);
            }
            lastSentDown = false;
            if (burstClicks >= 0) {
                Wh_Log(L"Burst end, %d clicks", burstClicks);
                burstClicks = -1;
            }
            Sleep(8);
        }
    }
    // Never unload with the synthetic press still held down.
    if (lastSentDown) {
        SendLeft(MOUSEEVENTF_LEFTUP);
    }
    if (g_clickTimer) {
        CloseHandle(g_clickTimer);
        g_clickTimer = nullptr;
    }
    return 0;
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
    int intervalMs = Wh_GetIntSetting(L"clickIntervalMs");
    if (intervalMs <= 0) {
        intervalMs = 33;
    }
    intervalMs = std::clamp(intervalMs, 16, 1000);
    g_halfMs.store(intervalMs / 2, std::memory_order_relaxed);

    std::wstring activator = ReadString(L"activatorButton");
    int mode = activator == L"forward" ? kModeForward : activator == L"gshift" ? kModeGShift : kModeBack;
    g_mode.store(mode, std::memory_order_relaxed);
    g_toggleRight.store(Wh_GetIntSetting(L"toggleWithRightClick") != 0, std::memory_order_relaxed);
    g_trayIconOn = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    g_hotkeyText = Trim(ReadString(L"toggleHotkey"));

    // With no tray icon and no shortcut nothing could turn it back on.
    if (!g_trayIconOn && g_hotkeyText.empty() && !g_enabled.load()) {
        g_enabled.store(true);
        Wh_SetIntValue(L"enabled", 1);
    }
    Wh_Log(L"Settings: hold %s, interval %d ms, right-click lock %d, tray %d, shortcut \"%s\"",
           kModeNames[mode], intervalMs, (int)g_toggleRight.load(), (int)g_trayIconOn, g_hotkeyText.c_str());
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
constexpr UINT kTrayId = 1;
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
    WCHAR g[2] = {(WCHAR)(on ? 0xE8B0 : 0xE769), 0};
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
    std::wstring tip = L"Seamless AutoClicker: ";
    if (g_enabled.load()) {
        tip += L"on. Hold ";
        tip += kModeNames[g_mode.load()];
        tip += L" and left click.";
    } else {
        tip += L"off. Click to turn it on.";
    }
    wcsncpy_s(nid.szTip, tip.c_str(), _TRUNCATE);
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
    // A lock never survives a switch, either way.
    if (g_latched.load()) {
        SetLatch(false, why);
    }
    Wh_SetIntValue(L"enabled", on ? 1 : 0);
    Wh_Log(L"Auto clicking %s (%s)", on ? L"on" : L"off", why);
    UpdateTray(false);
}

enum : UINT { IDM_TOGGLE = 100, IDM_SETTINGS };

void ShowTrayMenu(POINT pt) {
    HMENU menu = CreatePopupMenu();
    std::wstring toggle = L"Auto clicking on";
    if (g_hotkeyOn) toggle += L"\t" + g_hotkeyText;
    AppendMenuW(menu, MF_STRING | (g_enabled.load() ? MF_CHECKED : 0), IDM_TOGGLE, toggle.c_str());
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, IDM_SETTINGS, L"Settings");
    SetForegroundWindow(g_msgWnd);
    UINT cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON |
                                          (GetSystemMetrics(SM_MENUDROPALIGNMENT) ? TPM_RIGHTALIGN : TPM_LEFTALIGN),
                                pt.x, pt.y, g_msgWnd, nullptr);
    PostMessageW(g_msgWnd, WM_NULL, 0, 0);
    DestroyMenu(menu);
    if (cmd == IDM_TOGGLE) SetEnabled(!g_enabled.load(), L"tray menu");
    else if (cmd == IDM_SETTINGS) acset::OpenSettingsWindow();
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
            // A setting change ends a lock, as before.
            if (g_latched.load()) SetLatch(false, L"settings changed");
            RegisterToggleHotkey();
            UpdateTray(false);
            if (HWND s = acset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
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
    wc.hInstance = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    wc.lpszClassName = L"SeamlessAutoClickerMsg";
    RegisterClassW(&wc);
    g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless AutoClicker", WS_POPUP, 0, 0, 0, 0,
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

BOOL WhTool_ModInit() {
    SeamlessMenuSkin::Init();
    // Unelevated hooks miss clicks over admin windows. UAC prompts are off on
    // this PC, so relaunch elevated and let this copy exit.
    if (!IsElevated()) {
        WCHAR self[MAX_PATH];
        if (GetModuleFileNameW(nullptr, self, MAX_PATH)) {
            SHELLEXECUTEINFOW launch{sizeof(launch)};
            launch.fMask = SEE_MASK_FLAG_NO_UI;
            launch.lpVerb = L"runas";
            launch.lpFile = self;
            launch.lpParameters = L"-windhawk-tool-mod \"" WH_MOD_ID L"\"";
            // Not SW_HIDE: Windows applies the launch show state to the first
            // window the process shows, which would be the settings window.
            // The helper has no window of its own to show.
            launch.nShow = SW_SHOWNORMAL;
            if (ShellExecuteExW(&launch)) {
                // Returning FALSE exits with code 1, which Windhawk reports
                // as a failed tool mod. The admin copy takes over, so this
                // copy leaves cleanly.
                ExitProcess(0);
            }
        }
        Wh_Log(L"Elevated relaunch failed, running unelevated");
    }

    g_instanceMutex = CreateMutexW(nullptr, FALSE, L"Global\\SeamlessAutoClicker");
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

    g_readyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_hookThread = CreateThread(nullptr, 0, HookThreadProc, nullptr, 0, &g_hookThreadId);
    if (!g_readyEvent || !g_hookThread) {
        Wh_Log(L"Couldn't start the mouse hook: %u", GetLastError());
        if (g_readyEvent) CloseHandle(g_readyEvent);
        g_readyEvent = nullptr;
        return FALSE;
    }
    WaitForSingleObject(g_readyEvent, 5000);
    CloseHandle(g_readyEvent);
    g_readyEvent = nullptr;

    g_clickThread = CreateThread(nullptr, 0, ClickThreadProc, nullptr, 0, nullptr);
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, &g_uiThreadId);
    if (g_uiThread && g_uiReady) WaitForSingleObject(g_uiReady, 10000);
    if (g_uiReady) CloseHandle(g_uiReady);
    g_uiReady = nullptr;
    if (!g_clickThread || !g_uiThread) {
        Wh_Log(L"Couldn't start: %u", GetLastError());
        WhTool_ModUninit();
        return FALSE;
    }
    Wh_Log(L"Started, auto clicking %s", g_enabled.load() ? L"on" : L"off");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_msgWnd) {
        PostMessageW(g_msgWnd, WM_AC_SETTINGS, 0, 0);
    } else {
        ReadSettings();
    }
}

void WhTool_ModUninit() {
    SeamlessMenuSkin::Uninit();
    g_stop.store(true, std::memory_order_relaxed);
    acset::CloseSettingsWindow();
    StopThread(g_uiThread, g_uiThreadId);
    StopThread(g_hookThread, g_hookThreadId);
    // The click thread releases its own press on the way out.
    StopThread(g_clickThread, 0);
    g_holdDown.store(false);
    g_latched.store(false);
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
namespace acset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessAutoClickerSettings";
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
// Generated by work\2026-11-12-seamless-autoclicker\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Choice, L"activatorButton", L"Hold button", L"What you hold together with left click to start auto clicking.", L"back", {{L"back", L"Side button 1 (back)"}, {L"forward", L"Side button 2 (forward)"}, {L"gshift", L"G-Shift (onboard memory, left sends forward, right sends back)"}}, 0, 100, 0, L"Hold to click"},
{K::Check, L"toggleWithRightClick", L"Right click locks clicking on", L"While auto clicking, press right click and the clicking keeps going after you let go. Press right click again to stop.", L"1", {}, 0, 100, 0, L"Hold to click"},
{K::Number, L"clickIntervalMs", L"Click interval (milliseconds)", L"Time between clicks, press and release included. 16 to 1000 (Suggested: 33, about 30 clicks a second). Lower is faster.", L"33", {}, 16, 1000, 0, L"Speed"},
{K::Hotkey, L"toggleHotkey", L"Turn auto clicking on or off", L"Press the keys in the box. Backspace clears it. The tray icon does the same.", L"", {}, 0, 100, 1, L"Shortcut"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.", L"1", {}, 0, 100, 1, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.", L"0", {}, 0, 100, 1, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to turn auto clicking on or off. Right-click it for these settings. When off, change settings in Windhawk.", L"1", {}, 0, 100, 1, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Clicking", L"The button you hold, how fast it clicks and the right-click lock.", 0xE962},
{L"Shortcut and tray", L"A key that turns auto clicking on or off, the tray icon and this window.", 0xE765},
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
constexpr float kSetGlassTint = 0.55f, kSetNativeFade = 56;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetPaletteUrl = L"https://github.com/catppuccin/catppuccin";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20AutoClicker%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless AutoClicker";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"AutoClicker") <= railW) break;
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
        add(SetItem::Link, 56, L"Colours from Catppuccin Mocha", L"By the Catppuccin team, MIT", kSetPaletteUrl);
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
    p.Glyph(w.fIconL.get(), 0xE8B0, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless AutoClicker", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  GPL-3.0  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"GPL-3.0  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Hold a mouse button and left click keeps clicking. Lock it on, or switch it off from the tray.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi. Original work, free and open source.",
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
    p.Text(w.fRailName.get(), L"AutoClicker", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    p.Glyph(glyph, 0xE8B0, r, mocha::crust);
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
    w->editBrush = CreateSolidBrush(RefFromRgb(kSetBoxFill));
    g_setWin = w;
    if (render) {
        // An owned window gets no taskbar button.
        w->owner = CreateWindowExW(WS_EX_TOOLWINDOW, L"STATIC", L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                                   GetModuleHandleW(nullptr), nullptr);
    }
    const int offX = GetSystemMetrics(SM_XVIRTUALSCREEN) - 6000, offY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    // Off: the window draws its own title bar and buttons. On: Windows draws both.
    w->nativeTitle = !render && Wh_GetIntSetting(L"nativeSettingsTitleBar") != 0;
    w->glass = !render && Wh_GetIntSetting(L"settingsGlass") != 0;
    kSetCapH = w->nativeTitle ? 0.0f : 40.0f;
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless AutoClicker settings", style,
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
            struct SetAccentPolicy { int state, flags, abgr, animation; };
            struct SetCompositionData { DWORD attribute; void* data; SIZE_T size; };
            using SetComposition_t = BOOL(WINAPI*)(HWND, SetCompositionData*);
            if (auto setComposition = (SetComposition_t)(void*)GetProcAddress(
                    GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute")) {
                SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};  // same as the launcher grid
                SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
                setComposition(hwnd, &data);
            }
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
}  // namespace acset
