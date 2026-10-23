// ==WindhawkMod==
// @id              theme-tool-plus
// @name            Theme Tool Plus
// @description     Apply and switch custom Windows themes from the settings tab. No separate theme tool needed
// @version         1.1.0
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

Apply and switch custom Windows themes from the mod's settings tab. The theme
signature patch from UXTheme hook is built in, so unsigned themes load without
changing system files or running a separate theme tool.

![Theme Tool Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/theme-tool-plus.png)

## Features
- **Settings-driven.** Pick an installed theme from a dropdown in the settings
  tab and apply it by saving. Nothing to memorize, and no hotkey needed.
- **Unsigned theme support.** Custom .msstyles files load as they are. No
  system file is touched, so Secure Boot is not affected.
- **ThemeToolSharp options.** Keep your wallpaper, cursor, desktop icons,
  colors, sounds or screensaver as they are. Hide the busy cursor while a theme
  applies. The undocumented apply, theme pack and start-up flags from the
  original theme tool are included.
- **Survives restarts.** Sign-in and lock screen colors stay in sync, so the
  theme survives a reboot.
- **No extra app.** Everything runs inside the mod. You can uninstall
  ThemeToolSharp, along with its process entry in Windhawk.
- **Settings blocker.** Stops the Settings app from opening after each theme
  apply, if you turn that on.

## How to use

Open the mod's settings tab.

1. Pick a theme from **Theme to apply**.
2. Turn on **Apply theme when settings save**.
3. Save. The theme applies right away.

The **What happens when settings save** option can refresh the theme list
after you install a new theme, re-initialize the theme manager if themes act
up, or open the theme picker once. The other settings control what an apply
keeps or changes.

## Notes
- Use themes made for your Windows version. The dropdown and the picker both
  list the themes in `C:\Windows\Resources\Themes`. New themes appear after you
  refresh the list.
- Before you remove the mod, switch back to a stock theme. Otherwise the next
  sign-in checks theme signatures again, and a custom theme may fail to load.
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
- themeName: ""
  $name: Theme to apply
  $description: Themes installed on this computer. Pick one, turn on Apply theme when settings save (or choose another action), then save. The list updates when the mod source is updated.
  $options:
  - "": No theme
  - Captured Motion: Captured Motion
  - catppuccin Latte: catppuccin Latte
  - catppuccin Latte Win: catppuccin Latte Win
  - catppuccin Mocha: catppuccin Mocha
  - catppuccin Mocha Night: catppuccin Mocha Night
  - catppuccin Mocha Night Win: catppuccin Mocha Night Win
  - catppuccin Mocha Win: catppuccin Mocha Win
  - Flow: Flow
  - Glow: Glow
  - Main 01: Main 01
  - Sunrise: Sunrise
  - Windows (dark): Windows (dark)
  - Windows (light): Windows (light)
  - Windows spotlight: Windows spotlight
- applyOnSettingsChange: false
  $name: Apply theme when settings save
  $description: Applies the theme picked above as soon as you save.
- action: none
  $name: What happens when settings save
  $description: An extra step to run after saving. Refresh the theme list after installing a new theme, re-initialize the theme manager if themes act up, or open the theme picker once.
  $options:
  - none: Nothing extra
  - refresh: Refresh the theme list
  - reinitialize: Re-initialize the theme manager
  - picker: Open the theme picker
- updateLogonUI: true
  $name: Keep sign-in screens in sync
  $description: Matches the colors of the sign-in and lock screens to the applied theme.
- preventSettings: false
  $name: Keep the Settings app closed after applying
  $description: Windows sometimes opens Settings right after a theme is applied. Turn this on to stop it.
- ignoreBackground: false
  $name: Keep current wallpaper
  $description: Leaves the wallpaper alone when applying a theme.
- ignoreCursor: false
  $name: Keep current cursor
  $description: Leaves the mouse pointer scheme alone when applying a theme.
- ignoreDesktopIcons: false
  $name: Keep current desktop icons
  $description: Leaves desktop icon positions alone when applying a theme.
- ignoreColor: false
  $name: Keep current colors
  $description: Leaves accent and window colors alone when applying a theme.
- ignoreSound: false
  $name: Keep current sounds
  $description: Leaves the sound scheme alone when applying a theme.
- ignoreScreensaver: false
  $name: Keep current screensaver
  $description: Leaves the screensaver alone when applying a theme.
- noHourglass: true
  $name: Hide the busy cursor while applying
  $description: Skips the hourglass flash Windows shows while a theme applies.
- unknownFlag1: false
  $name: Extra apply option 1 (advanced)
  $description: An undocumented option Windows accepts when applying a theme. It relates to window metrics, and the original theme tool exposes it too. Leave it off unless you need it.
- unknownFlag2: false
  $name: Extra apply option 2 (advanced)
  $description: A second undocumented apply option. The original theme tool exposes it too. Leave it off unless you need it.
- themePackUnknown1: false
  $name: Extra theme pack option 1 (advanced)
  $description: The first undocumented theme pack option. Upstream notes suggest it also hides the busy cursor. Leave it off unless you need it.
- themePackUnknown2: false
  $name: Extra theme pack option 2 (advanced)
  $description: The second undocumented theme pack option. Upstream notes suggest it also hides the busy cursor. Leave it off unless you need it.
- themePackSilent: false
  $name: Apply packs quietly
  $description: Hides every dialog a theme pack would show and stops its sounds.
- themePackRoamed: false
  $name: Roam theme packs
  $description: Lets the applied theme pack roam with your account settings.
- initUnknownFlag1: false
  $name: Extra start-up option 1 (advanced)
  $description: An undocumented option the theme manager gets when it starts or re-initializes. Leave it off unless you need it.
- initUnknownFlag2: false
  $name: Extra start-up option 2 (advanced)
  $description: A second undocumented start-up option. It relates to immersive colors. Leave it off unless you need it.
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

// Bits confirmed from ThemeToolSharp's IThemeManager2.cs. Upstream comments:
// both Unknown flags seem to suppress the hourglass, Silent hides dialogs and
// stops sounds, Roamed roams the pack with account settings.
enum : DWORD {
    ThemePack_Unknown1 = 1 << 0,
    ThemePack_Unknown2 = 1 << 1,
    ThemePack_Silent = 1 << 2,
    ThemePack_Roamed = 1 << 3,
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
    bool noHourglass;
    bool themePackUnknown1;
    bool themePackUnknown2;
    bool themePackSilent;
    bool themePackRoamed;
    wchar_t themeName[256];
    int action;  // 0 none, 1 refresh, 2 reinitialize, 3 open picker
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
    g_settings.noHourglass = Wh_GetIntSetting(L"noHourglass");
    g_settings.themePackUnknown1 = Wh_GetIntSetting(L"themePackUnknown1");
    g_settings.themePackUnknown2 = Wh_GetIntSetting(L"themePackUnknown2");
    g_settings.themePackSilent = Wh_GetIntSetting(L"themePackSilent");
    g_settings.themePackRoamed = Wh_GetIntSetting(L"themePackRoamed");
    CopyStringSetting(g_settings.themeName, ARRAYSIZE(g_settings.themeName), L"themeName");
    g_settings.action = Wh_GetIntSetting(L"action");
}

static DWORD ApplyFlagsFromSettings() {
    DWORD flags = 0;
    if (g_settings.noHourglass) flags |= ThemeApply_NoHourglass;
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

static DWORD PackFlagsFromSettings() {
    DWORD flags = 0;
    if (g_settings.themePackUnknown1) flags |= ThemePack_Unknown1;
    if (g_settings.themePackUnknown2) flags |= ThemePack_Unknown2;
    if (g_settings.themePackSilent) flags |= ThemePack_Silent;
    if (g_settings.themePackRoamed) flags |= ThemePack_Roamed;
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
    HRESULT hr = g_manager->SetCurrentTheme(g_popup ? g_popup : g_msgWnd, index, 1, ApplyFlagsFromSettings(), PackFlagsFromSettings());
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
                HRESULT hr = manager->SetCurrentTheme(g_msgWnd, i, 1, ApplyFlagsFromSettings(), PackFlagsFromSettings());
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

static void ShowPicker();  // defined below; the picker-on-save action needs it

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
        case 3:  // open the picker
            ShowPicker();
            break;
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
        case WM_APP_APPLY_NAME:
            ApplyThemeByName();
            return 0;
        case WM_APP_ACTION:
            RunPendingAction();
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
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

        // The picker opens from the settings tab (the "Open the theme
        // picker" action); no hotkey is registered anymore.
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
