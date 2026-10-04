// ==WindhawkMod==
// @id              windhawk-styler
// @name            Windhawk Styler
// @description     Change Windhawk's background color, font, transparency and acrylic blur
// @version         1.0.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         MIT
// @include         windhawk.exe
// @compilerOptions -luser32 -lshell32 -ldwmapi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Windhawk Styler

Give Windhawk a background color and font of your choice, with optional
transparency and acrylic blur.

![Windhawk Styler preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/windhawk-styler.png)

## Features

- Choose a background color with a hex color such as `#1e1e2e`.
- Choose an installed font for the interface. Icons keep their own font.
- Adjust window opacity between 40 and 100 percent.
- Turn acrylic blur on or off.
- Disabling the mod removes its styles and restores the window opacity.

## Setup

Compile and enable the mod, then close and reopen the Windhawk window once.
Save changes in the mod's Settings tab. Background and font changes refresh
the main page after saving. The code editor keeps its own font setting.

## Notes

Supports Windhawk's bundled VSCodium interface. The mod adds marked styles
to its interface files, keeping a backup beside each file. A Windhawk update
may require closing and reopening Windhawk to apply the styles again.
Transparency affects text as well as the background. Acrylic uses Windows'
fixed blur strength. Keep opacity high enough to read the text.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- backgroundColor: "#1e1e2e"
  $name: Background color
  $description: Hex color in #RRGGBB format
- fontFamily: "Segoe UI"
  $name: Font family
  $description: An installed font name. Leave blank to use Windhawk's font.
- opacity: 92
  $name: Window opacity
  $description: 40 to 100 percent. Transparency also affects text.
- acrylic: true
  $name: Acrylic blur
  $description: Blur behind the window. Windows controls the blur strength.
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <shellapi.h>
#include <dwmapi.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <mutex>
#include <map>
#include <algorithm>

namespace fs = std::filesystem;
static bool g_tool;
static HANDLE g_stop, g_thread, g_mutex;
static fs::path g_root;
static std::mutex g_guard;
static int g_opacity = 100;
static bool g_acrylic;
static DWORD g_color;
static std::map<HWND, LONG_PTR> g_windows;
static std::map<HWND, HWND> g_backdrops;
static const std::string kBegin = "/* windhawk-styler begin */";
static const std::string kEnd = "/* windhawk-styler end */";

static std::string Read(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot read interface file");
    return {std::istreambuf_iterator<char>(f), {}};
}
static void Write(const fs::path& p, const std::string& s) {
    std::ofstream f(p, std::ios::binary | std::ios::trunc);
    if (!f || !f.write(s.data(), s.size())) throw std::runtime_error("Cannot write interface file");
}
static std::string Strip(std::string s) {
    auto a = s.find(kBegin);
    if (a == std::string::npos) return s;
    auto b = s.find(kEnd, a);
    if (b == std::string::npos || s.find(kBegin, a + kBegin.size()) != std::string::npos)
        throw std::runtime_error("Ambiguous style markers");
    auto end = b + kEnd.size();
    if (a >= 4 && s.substr(a - 4, 4) == "<!--" && s.substr(end, 3) == "-->") {
        a -= 4; end += 3;
    }
    s.erase(a, end - a);
    return s;
}
static void Patch(const fs::path& p, const std::string& block) {
    auto old = Read(p), clean = Strip(old);
    if (!fs::exists(p.wstring() + L".windhawk-styler.bak"))
        fs::copy_file(p, p.wstring() + L".windhawk-styler.bak");
    auto next = clean + block;
    if (next != old) Write(p, next);
}
static std::string Utf8(const std::wstring& s) {
    int n = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), s.size(), nullptr, 0, nullptr, nullptr);
    std::string r(n, 0);
    WideCharToMultiByte(CP_UTF8, 0, s.c_str(), s.size(), r.data(), n, nullptr, nullptr);
    return r;
}
static std::wstring Setting(PCWSTR name) {
    auto p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    Wh_FreeStringSetting(p);
    return s;
}
static void ApplyFiles(bool remove = false) {
    auto app = g_root / L"UI/resources/app";
    auto html = app / L"extensions/windhawk/webview/index.html";
    auto ext = app / L"extensions/windhawk/dist/extension.js";
    if (remove) {
        Patch(html, ""); Patch(ext, "");
        return;
    }
    auto color = Setting(L"backgroundColor"), font = Setting(L"fontFamily");
    if (color.size() != 7 || color[0] != L'#' ||
        !std::all_of(color.begin() + 1, color.end(), [](wchar_t c) { return iswxdigit(c); }))
        color = L"#1e1e2e";
    g_color = std::stoul(color.substr(1), nullptr, 16);
    g_opacity = std::clamp(Wh_GetIntSetting(L"opacity"), 40, 100);
    g_acrylic = Wh_GetIntSetting(L"acrylic") != 0;
    // Encode every font character as a CSS escape so settings cannot add CSS or HTML.
    std::string escaped;
    for (wchar_t c : font) { char b[20]; sprintf_s(b, "\\%x ", unsigned(c)); escaped += b; }
    std::string fontCss = font.empty() ? "" :
        "body,button,input,textarea,select,.ant-typography,.ant-btn,.ant-input{font-family:\"" + escaped + "\",sans-serif!important;}";
    auto css = "body{--app-background-color:" + Utf8(color) + "!important;}" + fontCss;
    // A style element after the HTML remains valid in Chromium and avoids replacing stock tags.
    Patch(html, "<!--" + kBegin + "--><style>" + css + "</style><!--" + kEnd + "-->");
    // Refresh the Windhawk page only when this mod changes its HTML. Never interrupt editor mode.
    const std::string watcher = R"JS(
;(()=>{const fs=require('fs'),path=require('path'),v=require('vscode');
const file=path.join(__dirname,'../webview/index.html');let timer;
fs.watchFile(file,{interval:750,persistent:false},(a,b)=>{
if(a.mtimeMs===b.mtimeMs)return;clearTimeout(timer);timer=setTimeout(()=>{
if(!v.workspace.getConfiguration('windhawk').get('editedModId'))
v.commands.executeCommand('windhawk.start');},1000);});})();
)JS";
    Patch(ext, kBegin + watcher + kEnd);
}
struct Accent { int state, flags; DWORD color; int animation; };
struct Composition { int attribute; void* data; SIZE_T size; };
static void Effect(HWND h, bool reset) {
    auto proc = reinterpret_cast<BOOL(WINAPI*)(HWND, Composition*)>(
        GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute"));
    DWORD tint = ((g_color & 255) << 16) | (g_color & 0xff00) | (g_color >> 16) | 0xA0000000;
    Accent accent{!reset && g_acrylic ? 4 : 0, 2, tint, 0};
    Composition data{19, &accent, sizeof(accent)};
    auto original = g_windows.at(h);
    if (reset || g_opacity == 100) {
        SetLayeredWindowAttributes(h, 0, 255, LWA_ALPHA);
        SetWindowLongPtrW(h, GWL_EXSTYLE, original);
    } else {
        SetWindowLongPtrW(h, GWL_EXSTYLE, original | WS_EX_LAYERED);
        SetLayeredWindowAttributes(h, 0, BYTE(g_opacity * 255 / 100), LWA_ALPHA);
    }
    if (proc && !proc(h, &data)) Wh_Log(L"Backdrop update failed: %u", GetLastError());
}
static BOOL CALLBACK Window(HWND h, LPARAM) {
    WCHAR cls[64]; GetClassNameW(h, cls, 64);
    if (wcscmp(cls, L"Chrome_WidgetWin_1") || !IsWindowVisible(h)) return TRUE;
    DWORD pid; GetWindowThreadProcessId(h, &pid);
    HANDLE p = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    WCHAR path[32768]; DWORD n = ARRAYSIZE(path);
    bool ours = p && QueryFullProcessImageNameW(p, 0, path, &n) &&
        _wcsicmp(path, (g_root / L"UI" / L"VSCodium.exe").c_str()) == 0;
    if (p) CloseHandle(p);
    if (ours && !g_windows.contains(h)) {
        g_windows[h] = GetWindowLongPtrW(h, GWL_EXSTYLE); Effect(h, false);
    }
    return TRUE;
}
static LRESULT CALLBACK BackdropProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_ERASEBKGND) return 1;
    if (m == WM_PAINT) { PAINTSTRUCT p; BeginPaint(h, &p); EndPaint(h, &p); return 0; }
    return DefWindowProcW(h, m, w, l);
}
static void Backdrops() {
    static std::map<HWND, DWORD> colors;
    for (auto it = g_backdrops.begin(); it != g_backdrops.end();) {
        if (!g_windows.contains(it->first) || !g_acrylic) {
            colors.erase(it->second); DestroyWindow(it->second); it = g_backdrops.erase(it);
        } else ++it;
    }
    for (auto& [target, style] : g_windows) {
        if (!g_acrylic) continue;
        HWND& backdrop = g_backdrops[target];
        if (!backdrop) {
            backdrop = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_TRANSPARENT,
                L"WindhawkStylerBackdrop", L"", WS_POPUP | WS_DISABLED,
                0, 0, 0, 0, nullptr, nullptr, GetModuleHandleW(nullptr), nullptr);
            MARGINS margins{-1, -1, -1, -1}; DwmExtendFrameIntoClientArea(backdrop, &margins);
        }
        if (!IsWindowVisible(target) || IsIconic(target)) { ShowWindow(backdrop, SW_HIDE); continue; }
        RECT r; GetWindowRect(target, &r);
        auto proc = reinterpret_cast<BOOL(WINAPI*)(HWND, Composition*)>(
            GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute"));
        DWORD tint = ((g_color & 255) << 16) | (g_color & 0xff00) | (g_color >> 16) | 0x80000000;
        Accent a{4, 0, tint, 0}; Composition d{19, &a, sizeof(a)};
        if (!colors.contains(backdrop) || colors[backdrop] != tint) {
            if (proc) proc(backdrop, &d);
            colors[backdrop] = tint;
        }
        RECT old{}; GetWindowRect(backdrop, &old);
        if (!EqualRect(&old, &r) || !IsWindowVisible(backdrop) || GetWindow(backdrop, GW_HWNDPREV) != target)
            SetWindowPos(backdrop, target, r.left, r.top, r.right-r.left, r.bottom-r.top,
                SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }
}
static void CALLBACK WindowEvent(HWINEVENTHOOK, DWORD event, HWND h, LONG object, LONG child, DWORD, DWORD) {
    if (event != EVENT_SYSTEM_FOREGROUND && (object != OBJID_WINDOW || child != 0)) return;
    std::lock_guard lock(g_guard);
    if (event == EVENT_SYSTEM_FOREGROUND || g_windows.contains(h)) Backdrops();
}
static DWORD WINAPI Worker(void*) {
    WNDCLASSW wc{}; wc.lpfnWndProc = BackdropProc; wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = L"WindhawkStylerBackdrop"; RegisterClassW(&wc);
    auto locationHook = SetWinEventHook(EVENT_OBJECT_LOCATIONCHANGE, EVENT_OBJECT_LOCATIONCHANGE,
        nullptr, WindowEvent, 0, 0, WINEVENT_OUTOFCONTEXT);
    auto foregroundHook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND,
        nullptr, WindowEvent, 0, 0, WINEVENT_OUTOFCONTEXT);
    while (MsgWaitForMultipleObjects(1, &g_stop, FALSE, 100, QS_ALLINPUT) != WAIT_OBJECT_0) {
        MSG msg; while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg); DispatchMessageW(&msg);
        }
        std::lock_guard lock(g_guard);
        for (auto it = g_windows.begin(); it != g_windows.end();)
            if (!IsWindow(it->first)) it = g_windows.erase(it); else ++it;
        EnumWindows(Window, 0);
        for (auto& [h, style] : g_windows) {
            BYTE alpha = 255; DWORD flags = 0; COLORREF key = 0;
            bool layered = GetLayeredWindowAttributes(h, &key, &alpha, &flags) != FALSE;
            if (g_opacity < 100 && (!layered || !(flags & LWA_ALPHA) || alpha != BYTE(g_opacity * 255 / 100)))
                Effect(h, false);
        }
        Backdrops();
    }
    if (locationHook) UnhookWinEvent(locationHook);
    if (foregroundHook) UnhookWinEvent(foregroundHook);
    for (auto& [h, backdrop] : g_backdrops) DestroyWindow(backdrop);
    g_backdrops.clear(); UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}
static void WINAPI Entry() { ExitThread(0); }
BOOL Wh_ModInit() {
    DWORD session; if (!ProcessIdToSessionId(GetCurrentProcessId(), &session) || session == 0) return FALSE;
    int argc; auto argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv) return FALSE;
    bool excluded = false;
    for (int i = 1; i < argc; ++i) {
        if (!wcscmp(argv[i], L"-service")) excluded = true;
        if (!wcscmp(argv[i], L"-tool-mod")) {
            g_tool = i + 1 < argc && !wcscmp(argv[i + 1], WH_MOD_ID);
            if (!g_tool) excluded = true;
        }
    }
    LocalFree(argv); if (excluded) return FALSE;
    WCHAR exe[MAX_PATH]; GetModuleFileNameW(nullptr, exe, MAX_PATH); g_root = fs::path(exe).parent_path();
    if (!g_tool) return TRUE;
    g_mutex = CreateMutexW(nullptr, FALSE, L"windhawk-tool-mod_" WH_MOD_ID);
    if (!g_mutex || GetLastError() == ERROR_ALREADY_EXISTS) return FALSE;
    try { ApplyFiles(); } catch (const std::exception& e) { Wh_Log(L"Style setup failed: %S", e.what()); return FALSE; }
    g_stop = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
    if (!g_stop || !g_thread) return FALSE;
    auto base = reinterpret_cast<BYTE*>(GetModuleHandleW(nullptr));
    auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
    return Wh_SetFunctionHook(base + nt->OptionalHeader.AddressOfEntryPoint, reinterpret_cast<void*>(Entry), nullptr);
}
void Wh_ModAfterInit() {
    if (g_tool) return;
    auto exe = g_root / L"windhawk.exe";
    SHELLEXECUTEINFOW s{sizeof(s)}; s.fMask = SEE_MASK_FLAG_NO_UI;
    s.lpVerb = L"runas"; s.lpFile = exe.c_str(); s.lpParameters = L"-tool-mod \"" WH_MOD_ID L"\""; s.nShow = SW_HIDE;
    if (!ShellExecuteExW(&s)) Wh_Log(L"Tool launch failed: %u", GetLastError());
}
void Wh_ModSettingsChanged() {
    if (!g_tool) return;
    std::lock_guard lock(g_guard);
    try { ApplyFiles(); } catch (const std::exception& e) { Wh_Log(L"Style update failed: %S", e.what()); }
    for (auto& [h, style] : g_windows) if (IsWindow(h)) Effect(h, false);
}
void Wh_ModUninit() {
    if (!g_tool) return;
    SetEvent(g_stop); WaitForSingleObject(g_thread, INFINITE);
    for (auto& [h, style] : g_windows) if (IsWindow(h)) Effect(h, true);
    try { ApplyFiles(true); } catch (const std::exception& e) { Wh_Log(L"Style cleanup failed: %S", e.what()); }
    CloseHandle(g_thread); CloseHandle(g_stop); CloseHandle(g_mutex);
    ExitProcess(0);
}
