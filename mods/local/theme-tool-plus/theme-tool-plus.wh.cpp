// ==WindhawkMod==
// @id              theme-tool-plus
// @name            Theme Tool Plus
// @description     Apply and switch custom Windows themes from a hotkey picker, no separate theme tool needed
// @version         1.0.1
// @author          DavidHiFi, rounk-ctrl, namazso
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
// @include         explorer.exe
// @include         windhawk.exe
// @include         winlogon.exe
// @include         systemsettings.exe
// @include         logonui.exe
// @include         rundll32.exe
// @compilerOptions -lole32 -loleaut32 -luser32 -lgdi32 -ldwmapi
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Theme Tool Plus

Apply and switch custom Windows themes from a hotkey picker in Explorer. The
theme signature patch from UXTheme hook is built in, so unsigned themes load
without patching system files or running a separate theme tool.

![Theme Tool Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/theme-tool-plus.png)

## Features
- **Hotkey picker.** Press Ctrl+Alt+Y for a compact theme list; click or
  press Enter to apply. Works even without Explorer running (the picker lives
  in the Windhawk engine process).
- **Unsigned theme support.** Custom .msstyles load as-is; no system file is
  touched and Secure Boot stays happy.
- **Fine-grained apply options.** Ignore background, cursor, desktop icons,
  colors, sounds or the screensaver when applying.
- **Survives restarts.** Logon and lock screen colors are kept in sync so the
  theme survives a reboot.
- **No extra app.** Everything runs inside the mod; ThemeToolSharp and its
  process inclusion entry can go.
- **Settings blocker.** Optionally stop the Settings app from opening on
  every theme apply.

## How to use

| Key | Action |
| --- | --- |
| Ctrl+Alt+Y | Open or close the theme picker |
| Click / Enter | Apply the selected theme |
| Esc / click elsewhere | Close the picker |

To drive the mod without the picker, set **Theme to apply** and turn on
**Apply on settings save**; saving the mod's settings applies that theme.
The **Action on settings save** selector can also refresh the theme list or
re-initialize the theme manager.

## Notes
- Pick themes made for your Windows version. The picker lists the same themes
  Windows shows, from `C:\Windows\Resources\Themes`.
- Before uninstalling the mod, switch to a stock theme; otherwise the next
  logon re-verifies theme signatures and a custom theme may fail to load.
- ARM64 is not supported (Windhawk does not hook ARM64EC).

## Credits
Based on [UXTheme hook](https://windhawk.net/mods/uxtheme-hook) by rounk-ctrl.
Theme engine research from [SecureUxTheme](https://github.com/namazso/SecureUxTheme)
and [ThemeToolSharp](https://github.com/namazso/ThemeToolSharp) by namazso,
LGPL-2.1.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- hotkey: Ctrl+Alt+Y
  $name: Picker hotkey
  $description: Shortcut that opens the theme picker in Explorer. Leave empty to disable. Supports Ctrl, Shift, Alt, Win and a letter, digit or F-key.
- updateLogonUI: true
  $name: Update LogonUI colors on apply
  $description: Keeps logon and lock screen colors in sync with the applied theme.
- preventSettings: false
  $name: Prevent Settings from launching on theme apply
  $description: Stops the Settings app from opening every time a theme is applied.
- ignoreBackground: false
  $name: Ignore background on apply
  $description: Do not change the wallpaper when applying a theme.
- ignoreCursor: false
  $name: Ignore cursor on apply
  $description: Do not change the cursor scheme when applying a theme.
- ignoreDesktopIcons: false
  $name: Ignore desktop icons on apply
  $description: Do not change desktop icon positions when applying a theme.
- ignoreColor: false
  $name: Ignore color on apply
  $description: Do not change the accent color when applying a theme.
- ignoreSound: false
  $name: Ignore sound on apply
  $description: Do not change the sound scheme when applying a theme.
- ignoreScreensaver: false
  $name: Ignore screensaver on apply
  $description: Do not change the screensaver when applying a theme.
- unknownFlag1: false
  $name: Advanced: apply flag 1
  $description: Undocumented theme apply flag related to window metrics. Same option as ThemeToolSharp.
- unknownFlag2: false
  $name: Advanced: apply flag 2
  $description: Undocumented theme apply flag. Same option as ThemeToolSharp.
- initUnknownFlag1: false
  $name: Advanced: initialization flag 1
  $description: Undocumented theme manager initialization flag, passed on picker refresh. Same option as ThemeToolSharp.
- initUnknownFlag2: false
  $name: Advanced: initialization flag 2
  $description: Second undocumented theme manager initialization flag, related to immersive colors. Same option as ThemeToolSharp.
- applyOnSettingsChange: false
  $name: Apply on settings save
  $description: Apply the theme selected below whenever the mod's settings are saved.
- themeName:
  $name: Theme to apply
  $description: Display name of the theme to apply on settings save, exactly as shown in the picker.
- action: none
  $name: Action on settings save
  $description: Extra theme manager action to run when settings are saved.
  $options:
  - none: Do nothing
  - refresh: Refresh the theme list
  - reinitialize: Re-initialize the theme manager
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>
#include <windows.h>
#include <initguid.h>
#include <objidl.h>
#include <dwmapi.h>
#include <cstdarg>
#include <cwchar>

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

#ifdef _WIN64
#define STDCALL __cdecl
#define SSTDCALL L"__cdecl"
#else
#define STDCALL __thiscall
#define SSTDCALL L"__thiscall"
#endif

// ---------------------------------------------------------------------------
// Theme signature bypass (from UXTheme hook, rounk-ctrl)
// ---------------------------------------------------------------------------

typedef HRESULT(STDCALL* CThemeSignature_Verify_t)(PVOID, PVOID);
CThemeSignature_Verify_t CThemeSignature_Verify;
HRESULT STDCALL CThemeSignature_VerifyHook(PVOID, PVOID) {
    return ERROR_SUCCESS;
}

using SetSysColors_t = decltype(&SetSysColors);
SetSysColors_t SetSysColors_orig;
int WINAPI SetSysColors_hook(int cElements, const INT* lpaElements, const COLORREF* lpaRgbValues) {
    DWORD elemCount = 13;
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                      L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\DefaultColors\\Standard",
                      0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegQueryInfoKeyW(hKey, nullptr, nullptr, nullptr, nullptr, nullptr, &elemCount, nullptr, nullptr, nullptr, nullptr, nullptr);
        RegCloseKey(hKey);
    }
    // LogonUI resetting the DefaultColors entries would wash out the theme.
    if (cElements == (int)elemCount) return TRUE;
    return SetSysColors_orig(cElements, lpaElements, lpaRgbValues);
}

// Blocks the ApplicationActivationManager call rundll32 makes for the Settings
// app right after a theme apply. Only installed in rundll32.exe.
DEFINE_GUID(CLSID_ApplicationActivationManager, 0x45ba127d, 0x10a8, 0x46ea, 0x8a, 0xb7, 0x56, 0xea, 0x90, 0x78, 0x94, 0x3c);
DEFINE_GUID(IID_IApplicationActivationManager, 0x2e941141, 0x7f97, 0x4756, 0xba, 0x1d, 0x9d, 0xec, 0xde, 0x89, 0x4a, 0x3d);

using CoCreateInstance_t = decltype(&CoCreateInstance);
CoCreateInstance_t CoCreateInstance_orig;
HRESULT WINAPI CoCreateInstance_hook(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv) {
    if (IsEqualCLSID(rclsid, CLSID_ApplicationActivationManager) && IsEqualIID(riid, IID_IApplicationActivationManager)) {
        return E_NOINTERFACE;
    }
    return CoCreateInstance_orig(rclsid, pUnkOuter, dwClsContext, riid, ppv);
}

// ---------------------------------------------------------------------------
// Theme manager client (researched from ThemeToolSharp, namazso)
// ---------------------------------------------------------------------------

DEFINE_GUID(CLSID_ThemeManager2, 0x9324da94, 0x50ec, 0x4a14, 0xa7, 0x70, 0xe9, 0x0c, 0xa0, 0x3e, 0x7c, 0x8f);
DEFINE_GUID(IID_ThemeManager2, 0xc1e8c83e, 0x845d, 0x4d95, 0x81, 0xdb, 0xe2, 0x83, 0xfd, 0xff, 0xc0, 0x00);

enum : DWORD {
    ThemeInitNoFlags = 0,
    ThemeInitCurrentThemeOnly = 1 << 0,
    ThemeInitFlagUnk1 = 1 << 1,
    ThemeInitFlagUnk2 = 1 << 2,
};

enum : DWORD {
    ThemeApply_IgnoreBackground = 1 << 0,
    ThemeApply_IgnoreCursor = 1 << 1,
    ThemeApply_IgnoreDesktopIcons = 1 << 2,
    ThemeApply_IgnoreColor = 1 << 3,
    ThemeApply_IgnoreSound = 1 << 4,
    ThemeApply_IgnoreScreensaver = 1 << 5,
    ThemeApply_Unknown1 = 1 << 6,
    ThemeApply_Unknown2 = 1 << 7,
    ThemeApply_NoHourglass = 1 << 8,
};

struct IThemeBase : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetDisplayName(BSTR* value) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetDisplayName(BSTR value) = 0;
};

struct IThemeManager2Ex : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE Init(DWORD initFlags) = 0;
    virtual HRESULT STDMETHODCALLTYPE InitAsync(HWND hwnd, int unk1) = 0;
    virtual HRESULT STDMETHODCALLTYPE Refresh() = 0;
    virtual HRESULT STDMETHODCALLTYPE RefreshAsync(HWND hwnd, int unk1) = 0;
    virtual HRESULT STDMETHODCALLTYPE RefreshComplete() = 0;
    virtual HRESULT STDMETHODCALLTYPE GetThemeCount(int* count) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetTheme(int index, IThemeBase** theme) = 0;
    virtual HRESULT STDMETHODCALLTYPE IsThemeDisabled(int index, int* disabled) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetCurrentTheme(int* index) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetCurrentTheme(HWND parent, int themeIndex, int applyNow, DWORD applyFlags, DWORD packFlags) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetCustomTheme(int* index) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetDefaultTheme(int* index) = 0;
    virtual HRESULT STDMETHODCALLTYPE CreateThemePack(HWND hwnd, LPCWSTR unk1, DWORD packFlags) = 0;
    virtual HRESULT STDMETHODCALLTYPE CloneAndSetCurrentTheme(HWND hwnd, LPCWSTR unk1, LPWSTR* unk2) = 0;
    virtual HRESULT STDMETHODCALLTYPE InstallThemePack(HWND hwnd, LPCWSTR unk1, int unk2, DWORD packFlags, LPWSTR* unk3, IThemeBase** unk4) = 0;
    virtual HRESULT STDMETHODCALLTYPE DeleteTheme(LPCWSTR unk1) = 0;
    virtual HRESULT STDMETHODCALLTYPE OpenTheme(HWND hwnd, LPCWSTR path, DWORD packFlags) = 0;
    virtual HRESULT STDMETHODCALLTYPE AddAndSelectTheme(HWND hwnd, LPCWSTR path, DWORD applyFlags, DWORD packFlags) = 0;
    virtual HRESULT STDMETHODCALLTYPE SQMCurrentTheme() = 0;
    virtual HRESULT STDMETHODCALLTYPE ExportRoamingThemeToStream(IStream* stream, int unk1) = 0;
    virtual HRESULT STDMETHODCALLTYPE ImportRoamingThemeFromStream(IStream* stream, int unk1) = 0;
    virtual HRESULT STDMETHODCALLTYPE UpdateColorSettingsForLogonUI() = 0;
    virtual HRESULT STDMETHODCALLTYPE GetDefaultThemeId(GUID* guid) = 0;
};

// ---------------------------------------------------------------------------
// Settings
// ---------------------------------------------------------------------------

struct ModSettings {
    bool preventSettings;
    bool updateLogonUI;
    bool ignoreBackground;
    bool ignoreCursor;
    bool ignoreDesktopIcons;
    bool ignoreColor;
    bool ignoreSound;
    bool ignoreScreensaver;
    bool unknownFlag1;
    bool unknownFlag2;
    bool initUnknownFlag1;
    bool initUnknownFlag2;
    bool applyOnSettingsChange;
    wchar_t themeName[256];
    wchar_t hotkey[64];
    int action;  // 0 none, 1 refresh, 2 reinitialize
} g_settings;

static void CopyStringSetting(wchar_t* dest, size_t size, PCWSTR valueName) {
    PCWSTR value = Wh_GetStringSetting(valueName);
    lstrcpynW(dest, value, (int)size);
    Wh_FreeStringSetting(value);
}

static void LoadSettings() {
    g_settings.preventSettings = Wh_GetIntSetting(L"preventSettings");
    g_settings.updateLogonUI = Wh_GetIntSetting(L"updateLogonUI");
    g_settings.ignoreBackground = Wh_GetIntSetting(L"ignoreBackground");
    g_settings.ignoreCursor = Wh_GetIntSetting(L"ignoreCursor");
    g_settings.ignoreDesktopIcons = Wh_GetIntSetting(L"ignoreDesktopIcons");
    g_settings.ignoreColor = Wh_GetIntSetting(L"ignoreColor");
    g_settings.ignoreSound = Wh_GetIntSetting(L"ignoreSound");
    g_settings.ignoreScreensaver = Wh_GetIntSetting(L"ignoreScreensaver");
    g_settings.unknownFlag1 = Wh_GetIntSetting(L"unknownFlag1");
    g_settings.unknownFlag2 = Wh_GetIntSetting(L"unknownFlag2");
    g_settings.initUnknownFlag1 = Wh_GetIntSetting(L"initUnknownFlag1");
    g_settings.initUnknownFlag2 = Wh_GetIntSetting(L"initUnknownFlag2");
    g_settings.applyOnSettingsChange = Wh_GetIntSetting(L"applyOnSettingsChange");
    CopyStringSetting(g_settings.themeName, ARRAYSIZE(g_settings.themeName), L"themeName");
    CopyStringSetting(g_settings.hotkey, ARRAYSIZE(g_settings.hotkey), L"hotkey");
    g_settings.action = Wh_GetIntSetting(L"action");
}

static DWORD ApplyFlagsFromSettings() {
    DWORD flags = ThemeApply_NoHourglass;
    if (g_settings.ignoreBackground) flags |= ThemeApply_IgnoreBackground;
    if (g_settings.ignoreCursor) flags |= ThemeApply_IgnoreCursor;
    if (g_settings.ignoreDesktopIcons) flags |= ThemeApply_IgnoreDesktopIcons;
    if (g_settings.ignoreColor) flags |= ThemeApply_IgnoreColor;
    if (g_settings.ignoreSound) flags |= ThemeApply_IgnoreSound;
    if (g_settings.ignoreScreensaver) flags |= ThemeApply_IgnoreScreensaver;
    if (g_settings.unknownFlag1) flags |= ThemeApply_Unknown1;
    if (g_settings.unknownFlag2) flags |= ThemeApply_Unknown2;
    return flags;
}

static DWORD InitFlagsFromSettings() {
    DWORD flags = ThemeInitNoFlags;
    if (g_settings.initUnknownFlag1) flags |= ThemeInitFlagUnk1;
    if (g_settings.initUnknownFlag2) flags |= ThemeInitFlagUnk2;
    return flags;
}

// ---------------------------------------------------------------------------
// Picker worker (explorer.exe only)
// ---------------------------------------------------------------------------

static const wchar_t kPopupClassBase[] = L"ThemeToolPlusPicker";
static const wchar_t kMsgClassBase[] = L"ThemeToolPlusMsgWnd";
static wchar_t kPopupClass[64];
static wchar_t kMsgClass[64];
constexpr UINT WM_APP_APPLY_NAME = WM_APP + 1;
constexpr UINT WM_APP_ACTION = WM_APP + 2;
constexpr int IDC_LIST = 200;
constexpr int IDC_APPLY = 201;
constexpr int IDC_REFRESH = 202;
constexpr int kPopupWidth = 340;
constexpr int kPopupListHeight = 360;
constexpr int kPopupButtonHeight = 34;

static HANDLE g_workerThread;
static DWORD g_workerThreadId;
static HINSTANCE g_workerInst;
static HWND g_msgWnd;
static HWND g_popup;
static HWND g_list;
static IThemeManager2Ex* g_manager;
static HBRUSH g_backBrush;
static HFONT g_font;
static bool g_dark;
static bool g_creating;
static bool g_everActive;
static bool g_pendingApplyByName;
static bool g_pendingAction;
static UINT g_hotkeyMods;
static UINT g_hotkeyVk;

// The Windhawk debug log is not reachable headlessly, so diagnostics go to a
// plain temp file while the mod is new.
static void TtpLog(PCWSTR fmt, ...) {
    wchar_t buf[512];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf(buf, ARRAYSIZE(buf) - 1, fmt, args);
    va_end(args);
    buf[ARRAYSIZE(buf) - 1] = L'\0';

    wchar_t path[MAX_PATH];
    if (!GetTempPathW(MAX_PATH, path)) return;
    lstrcatW(path, L"theme-tool-plus-mod.log");
    HANDLE file = CreateFileW(path, FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS, 0, nullptr);
    if (file == INVALID_HANDLE_VALUE) return;
    SYSTEMTIME st;
    GetLocalTime(&st);
    wchar_t line[600];
    _snwprintf(line, ARRAYSIZE(line) - 1, L"[%02u:%02u:%02u.%03u] %s\r\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, buf);
    DWORD written = 0;
    WriteFile(file, line, (DWORD)(lstrlenW(line) * sizeof(wchar_t)), &written, nullptr);
    CloseHandle(file);
}

static bool ProcessIs(PCWSTR name) {
    wchar_t path[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, path, MAX_PATH)) return false;
    PCWSTR base = wcsrchr(path, L'\\');
    base = base ? base + 1 : path;
    return lstrcmpiW(base, name) == 0;
}

static HRESULT CreateThemeManager(IThemeManager2Ex** out) {
    IUnknown* unk = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_ThemeManager2, nullptr, CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER,
                                  IID_ThemeManager2, (void**)&unk);
    if (SUCCEEDED(hr)) {
        *out = reinterpret_cast<IThemeManager2Ex*>(unk);
    }
    return hr;
}

static void ReleaseManager() {
    if (g_manager) {
        g_manager->Release();
        g_manager = nullptr;
    }
}

// Re-initializes the theme manager, same as ThemeToolSharp's re-initialize.
static HRESULT ReinitManager() {
    ReleaseManager();
    HRESULT hr = CreateThemeManager(&g_manager);
    if (FAILED(hr)) {
        g_manager = nullptr;
        return hr;
    }
    hr = g_manager->Init(InitFlagsFromSettings());
    if (FAILED(hr)) {
        ReleaseManager();
    }
    return hr;
}

// The active custom theme is named "Unsaved Theme". Applying it re-saves Custom.theme,
// so the picker and the settings path both skip it.
static constexpr wchar_t kUnsavedCustomTheme[] = L"Unsaved Theme";

static bool ThemeIndexIsUnsavedCustom(int index) {
    IThemeBase* theme = nullptr;
    if (!g_manager || FAILED(g_manager->GetTheme(index, &theme)) || !theme) return false;
    BSTR name = nullptr;
    bool custom = SUCCEEDED(theme->GetDisplayName(&name)) && name && lstrcmpiW(name, kUnsavedCustomTheme) == 0;
    if (name) SysFreeString(name);
    theme->Release();
    return custom;
}

static void ApplyThemeIndex(int index) {
    if (!g_manager || index < 0) return;
    if (ThemeIndexIsUnsavedCustom(index)) {
        Wh_Log(L"Skipped the unsaved custom theme: applying it rewrites Custom.theme");
        return;
    }
    HRESULT hr = g_manager->SetCurrentTheme(g_popup ? g_popup : g_msgWnd, index, 1, ApplyFlagsFromSettings(), 0);
    if (FAILED(hr)) {
        Wh_Log(L"SetCurrentTheme failed 0x%08lX", (unsigned long)hr);
        return;
    }
    if (g_settings.updateLogonUI) {
        g_manager->UpdateColorSettingsForLogonUI();
    }
    int current = -1;
    g_manager->GetCurrentTheme(&current);
    if (current >= 0) {
        SendMessageW(g_list, LB_SETCURSEL, current, 0);
    }
}

static void ApplySelected() {
    if (!g_list) return;
    int sel = (int)SendMessageW(g_list, LB_GETCURSEL, 0, 0);
    ApplyThemeIndex(sel);
}

static void PopulateList() {
    if (!g_list) return;
    SendMessageW(g_list, WM_SETREDRAW, FALSE, 0);
    SendMessageW(g_list, LB_RESETCONTENT, 0, 0);
    int count = 0;
    if (g_manager && SUCCEEDED(g_manager->GetThemeCount(&count))) {
        for (int i = 0; i < count; ++i) {
            IThemeBase* theme = nullptr;
            if (FAILED(g_manager->GetTheme(i, &theme)) || !theme) continue;
            BSTR name = nullptr;
            if (SUCCEEDED(theme->GetDisplayName(&name)) && name) {
                int item = (int)SendMessageW(g_list, LB_ADDSTRING, 0, (LPARAM)name);
                if (item == LB_ERRSPACE) break;
                SysFreeString(name);
            }
            theme->Release();
        }
        int current = -1;
        if (SUCCEEDED(g_manager->GetCurrentTheme(&current)) && current >= 0 && current < count) {
            SendMessageW(g_list, LB_SETCURSEL, current, 0);
        }
    }
    SendMessageW(g_list, WM_SETREDRAW, TRUE, 0);
    InvalidateRect(g_list, nullptr, TRUE);
}

static void ApplyThemeByName() {
    if (!g_settings.themeName[0]) return;
    if (lstrcmpiW(g_settings.themeName, kUnsavedCustomTheme) == 0) {
        Wh_Log(L"Skipped '%s': applying the unsaved custom theme rewrites Custom.theme", g_settings.themeName);
        return;
    }
    IThemeManager2Ex* manager = g_manager;
    bool temporary = false;
    if (!manager) {
        if (FAILED(CreateThemeManager(&manager))) {
            Wh_Log(L"ApplyThemeByName: no theme manager");
            return;
        }
        manager->Init(InitFlagsFromSettings());
        temporary = true;
    }

    int count = 0;
    manager->GetThemeCount(&count);
    bool applied = false;
    for (int i = 0; i < count && !applied; ++i) {
        IThemeBase* theme = nullptr;
        if (FAILED(manager->GetTheme(i, &theme)) || !theme) continue;
        BSTR name = nullptr;
        if (SUCCEEDED(theme->GetDisplayName(&name)) && name) {
            if (lstrcmpiW(name, g_settings.themeName) == 0) {
                HRESULT hr = manager->SetCurrentTheme(g_msgWnd, i, 1, ApplyFlagsFromSettings(), 0);
                if (SUCCEEDED(hr) && g_settings.updateLogonUI) {
                    manager->UpdateColorSettingsForLogonUI();
                }
                Wh_Log(L"Applied theme '%s' by settings (hr=0x%08lX)", g_settings.themeName, (unsigned long)hr);
                applied = true;
            }
            SysFreeString(name);
        }
        theme->Release();
    }
    if (!applied) {
        Wh_Log(L"Theme '%s' not found in the theme list", g_settings.themeName);
    }
    if (temporary) {
        manager->Release();
    }
}

static void RunPendingAction() {
    switch (g_settings.action) {
        case 1: {  // refresh
            IThemeManager2Ex* manager = nullptr;
            if (SUCCEEDED(CreateThemeManager(&manager)) && manager) {
                manager->Refresh();
                manager->Release();
                Wh_Log(L"Refreshed theme list by settings");
            }
            break;
        }
        case 2: {  // reinitialize
            IThemeManager2Ex* manager = nullptr;
            if (SUCCEEDED(CreateThemeManager(&manager)) && manager) {
                manager->Init(InitFlagsFromSettings());
                manager->Release();
                Wh_Log(L"Re-initialized theme manager by settings");
            }
            break;
        }
        default:
            break;
    }
}

static bool IsDarkMode() {
    DWORD light = 1, size = sizeof(light);
    RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                 L"AppsUseLightTheme", RRF_RT_REG_DWORD, nullptr, &light, &size);
    return light == 0;
}

static LRESULT CALLBACK PickerWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            g_dark = IsDarkMode();
            g_backBrush = CreateSolidBrush(g_dark ? RGB(32, 32, 32) : RGB(250, 250, 250));
            g_font = CreateFontW(-16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                 DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

            DWORD style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | LBS_NOTIFY | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT;
            g_list = CreateWindowExW(WS_EX_CLIENTEDGE, WC_LISTBOX, nullptr, style,
                                     10, 10, kPopupWidth - 20, kPopupListHeight, hwnd, (HMENU)(INT_PTR)IDC_LIST,
                                     ((CREATESTRUCTW*)lParam)->hInstance, nullptr);
            DWORD btnStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON;
            CreateWindowExW(0, WC_BUTTON, L"Apply", btnStyle,
                            10, kPopupListHeight + 20, (kPopupWidth - 30) / 2, kPopupButtonHeight, hwnd,
                            (HMENU)(INT_PTR)IDC_APPLY, ((CREATESTRUCTW*)lParam)->hInstance, nullptr);
            CreateWindowExW(0, WC_BUTTON, L"Refresh", btnStyle,
                            20 + (kPopupWidth - 30) / 2, kPopupListHeight + 20, (kPopupWidth - 30) / 2, kPopupButtonHeight, hwnd,
                            (HMENU)(INT_PTR)IDC_REFRESH, ((CREATESTRUCTW*)lParam)->hInstance, nullptr);
            SendMessageW(g_list, WM_SETFONT, (WPARAM)g_font, TRUE);
            SendMessageW(GetDlgItem(hwnd, IDC_APPLY), WM_SETFONT, (WPARAM)g_font, TRUE);
            SendMessageW(GetDlgItem(hwnd, IDC_REFRESH), WM_SETFONT, (WPARAM)g_font, TRUE);
            BOOL dark = g_dark;
            DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
            ReinitManager();
            PopulateList();
            return 0;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case IDC_LIST:
                    if (HIWORD(wParam) == LBN_DBLCLK) ApplySelected();
                    break;
                case IDC_APPLY:
                    ApplySelected();
                    break;
                case IDC_REFRESH:
                    if (g_manager) g_manager->Refresh();
                    PopulateList();
                    break;
            }
            return 0;
        }
        case WM_ACTIVATE:
            if (LOWORD(wParam) != WA_INACTIVE) {
                g_everActive = true;
            } else if (g_everActive) {
                DestroyWindow(hwnd);
            }
            return 0;
        case WM_CTLCOLORLISTBOX:
        case WM_CTLCOLORSTATIC: {
            HDC hdc = (HDC)wParam;
            SetTextColor(hdc, g_dark ? RGB(240, 240, 240) : GetSysColor(COLOR_WINDOWTEXT));
            SetBkColor(hdc, g_dark ? RGB(32, 32, 32) : RGB(250, 250, 250));
            return (LRESULT)g_backBrush;
        }
        case WM_ERASEBKGND: {
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect((HDC)wParam, &rc, g_backBrush);
            return TRUE;
        }
        case WM_NCDESTROY:
            if (g_font) DeleteObject(g_font);
            if (g_backBrush) DeleteObject(g_backBrush);
            g_font = nullptr;
            g_backBrush = nullptr;
            g_popup = nullptr;
            g_list = nullptr;
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static void ShowPicker() {
    if (g_popup) {
        DestroyWindow(g_popup);
        return;
    }

    POINT pt;
    GetCursorPos(&pt);
    HMONITOR monitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = {sizeof(mi)};
    GetMonitorInfoW(monitor, &mi);

    int width = kPopupWidth;
    int height = kPopupListHeight + kPopupButtonHeight + 40;
    int x = pt.x - width / 2;
    int y = pt.y + 16;
    if (x + width > mi.rcWork.right) x = mi.rcWork.right - width;
    if (x < mi.rcWork.left) x = mi.rcWork.left;
    if (y + height > mi.rcWork.bottom) y = pt.y - height - 8;
    if (y < mi.rcWork.top) y = mi.rcWork.top;

    g_creating = true;
    g_everActive = false;
    g_popup = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, kPopupClass, L"Theme Tool Plus",
                              WS_POPUP | WS_BORDER, x, y, width, height, nullptr, nullptr,
                              g_workerInst, nullptr);
    g_creating = false;
    TtpLog(L"ShowPicker: hwnd=%p gle=%lu", g_popup, GetLastError());
    if (!g_popup) return;
    ShowWindow(g_popup, SW_SHOW);
    SetFocus(g_list);
}

static LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_HOTKEY:
            ShowPicker();
            return 0;
        case WM_APP_APPLY_NAME:
            ApplyThemeByName();
            return 0;
        case WM_APP_ACTION:
            RunPendingAction();
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static bool ParseHotkey(const wchar_t* text, UINT* mods, UINT* vk) {
    if (!text || !*text) return false;

    wchar_t buf[64];
    lstrcpynW(buf, text, (int)ARRAYSIZE(buf));

    UINT m = 0;
    wchar_t key[64] = L"";
    wchar_t* context = nullptr;
    for (wchar_t* token = wcstok_s(buf, L"+", &context); token; token = wcstok_s(nullptr, L"+", &context)) {
        if (!lstrcmpiW(token, L"Ctrl") || !lstrcmpiW(token, L"Control")) m |= MOD_CONTROL;
        else if (!lstrcmpiW(token, L"Shift")) m |= MOD_SHIFT;
        else if (!lstrcmpiW(token, L"Alt")) m |= MOD_ALT;
        else if (!lstrcmpiW(token, L"Win") || !lstrcmpiW(token, L"Windows")) m |= MOD_WIN;
        else lstrcpynW(key, token, (int)ARRAYSIZE(key));
    }
    if (!key[0]) return false;

    UINT code = 0;
    if (!key[1] && iswalpha(key[0])) {
        code = towupper(key[0]);
    } else if (!key[1] && iswdigit(key[0])) {
        code = key[0];
    } else if ((key[0] == L'F' || key[0] == L'f') && iswdigit(key[1])) {
        int n = _wtoi(key + 1);
        if (n >= 1 && n <= 24) code = VK_F1 + n - 1;
    } else if (!lstrcmpiW(key, L"Space")) {
        code = VK_SPACE;
    } else {
        SHORT scanned = VkKeyScanW(key[0]);
        if (scanned != -1) code = LOBYTE(scanned);
    }
    if (!code) return false;
    // A bare letter hotkey would swallow that key system-wide; require a
    // modifier unless an F-key is used.
    if (!m && !(code >= VK_F1 && code <= VK_F24)) return false;

    *mods = m;
    *vk = code;
    return true;
}

static DWORD WINAPI PickerThreadProc(LPVOID) {
    TtpLog(L"thread start");
    HRESULT hrCom = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    TtpLog(L"CoInitializeEx hr=0x%08lX", (unsigned long)hrCom);

    HINSTANCE hInst = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)&PickerThreadProc, &hInst);
    g_workerInst = hInst;

    WNDCLASSEXW wc = {sizeof(wc)};
    wc.style = CS_DROPSHADOW;
    wc.lpfnWndProc = PickerWndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kPopupClass;
    ATOM popupAtom = RegisterClassExW(&wc);
    TtpLog(L"RegisterClassExW(popup) atom=%u gle=%lu", popupAtom, GetLastError());

    WNDCLASSEXW mc = {sizeof(mc)};
    mc.lpfnWndProc = MsgWndProc;
    mc.hInstance = hInst;
    mc.lpszClassName = kMsgClass;
    ATOM msgAtom = RegisterClassExW(&mc);
    TtpLog(L"RegisterClassExW(msg) atom=%u gle=%lu", msgAtom, GetLastError());

    g_msgWnd = CreateWindowExW(0, kMsgClass, nullptr, 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, hInst, nullptr);
    TtpLog(L"msgwnd=%p gle=%lu", g_msgWnd, GetLastError());

    if (g_hotkeyVk && !RegisterHotKey(g_msgWnd, 1, g_hotkeyMods, g_hotkeyVk)) {
        TtpLog(L"RegisterHotKey failed gle=%lu", GetLastError());
        Wh_Log(L"RegisterHotKey failed (error %lu); picker stays available via settings", GetLastError());
    } else {
        TtpLog(L"RegisterHotKey ok mods=0x%X vk=0x%X", g_hotkeyMods, g_hotkeyVk);
    }

    if (g_pendingApplyByName) PostMessageW(g_msgWnd, WM_APP_APPLY_NAME, 0, 0);
    if (g_pendingAction) PostMessageW(g_msgWnd, WM_APP_ACTION, 0, 0);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (g_popup && msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE) {
            DestroyWindow(g_popup);
            continue;
        }
        if (g_popup && msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN) {
            ApplySelected();
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (g_popup) DestroyWindow(g_popup);
    ReleaseManager();
    CoUninitialize();
    return 0;
}

// ---------------------------------------------------------------------------
// Mod entry
// ---------------------------------------------------------------------------

BOOL Wh_ModInit() {
    Wh_Log(L"Init");
    static LONG s_loadSeq = 0;
    long seq = InterlockedIncrement(&s_loadSeq);
    // Unique class names per load: classes registered by a previous revision
    // of this mod linger in the process and would fail re-registration.
    _snwprintf(kPopupClass, ARRAYSIZE(kPopupClass) - 1, L"%s_%ld", kPopupClassBase, seq);
    _snwprintf(kMsgClass, ARRAYSIZE(kMsgClass) - 1, L"%s_%ld", kMsgClassBase, seq);

    LoadSettings();
    TtpLog(L"Init seq=%ld", seq);

    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {{L"public: long " SSTDCALL L" CThemeSignature::Verify(void *)"}, &CThemeSignature_Verify,
         CThemeSignature_VerifyHook, false}};

    LPCWSTR files[] = {L"uxtheme.dll", L"uxinit.dll", L"themeui.dll"};
    for (int i = 0; i < int(ARRAYSIZE(files)); ++i) {
        HMODULE hMod = LoadLibraryExW(files[i], nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!hMod || !WindhawkUtils::HookSymbols(hMod, hooks, ARRAYSIZE(hooks))) {
            Wh_Log(L"Failed to hook theme symbols from %s", files[i]);
            return FALSE;
        }
    }

    WindhawkUtils::SetFunctionHook(SetSysColors, SetSysColors_hook, &SetSysColors_orig);

    if (g_settings.preventSettings && ProcessIs(L"rundll32.exe")) {
        WindhawkUtils::SetFunctionHook(CoCreateInstance, CoCreateInstance_hook, &CoCreateInstance_orig);
    }

    if (ProcessIs(L"explorer.exe") || ProcessIs(L"windhawk.exe")) {
        g_pendingApplyByName = g_settings.applyOnSettingsChange && g_settings.themeName[0];
        g_pendingAction = g_settings.action != 0;

        if (ParseHotkey(g_settings.hotkey, &g_hotkeyMods, &g_hotkeyVk)) {
            Wh_Log(L"Picker hotkey: mods=0x%X vk=0x%X", g_hotkeyMods, g_hotkeyVk);
        } else {
            g_hotkeyMods = 0;
            g_hotkeyVk = 0;
        }

        g_workerThread = CreateThread(nullptr, 0, PickerThreadProc, nullptr, 0, &g_workerThreadId);
        TtpLog(L"worker thread=%p tid=%lu", g_workerThread, g_workerThreadId);
        if (!g_workerThread) {
            Wh_Log(L"Failed to start picker thread");
        }
    }

    TtpLog(L"Init done");
    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L"Uninit");
    TtpLog(L"Uninit tid=%lu", g_workerThreadId);
    if (g_workerThread) {
        PostThreadMessageW(g_workerThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g_workerThread, 10000);
        CloseHandle(g_workerThread);
        g_workerThread = nullptr;
    }
}

BOOL Wh_ModSettingsChanged(BOOL* bReload) {
    Wh_Log(L"SettingsChanged");
    LoadSettings();
    *bReload = TRUE;
    return TRUE;
}
