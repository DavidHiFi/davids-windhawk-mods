// ==WindhawkMod==
// @id              mocha-app-icons
// @name            Mocha App Icons
// @description     Gives Ableton Live and Yapfast blue to mauve icons on their windows, taskbar buttons and shortcuts
// @version         1.0.1
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         Ableton Live*.exe
// @include         yapfast.exe
// @architecture    x86-64
// @compilerOptions -DWIN32_LEAN_AND_MEAN -luser32 -lshell32 -lole32 -luuid -lcrypt32 -ladvapi32 -lcomctl32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Mocha App Icons

Swaps the icons of Ableton Live and Yapfast for Catppuccin Mocha ones: each app's own mark on a blue to mauve tile, the same tile as Mocha Steam Icons. Windows shows them on the app's windows, its taskbar button, Alt+Tab and its shortcuts.

![Mocha App Icons preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/mocha-app-icons.png)

## What's new in 1.0.1

- Fixed: 1.0.0 never made its icon folder, so no icon showed. The icons now appear as soon as the mod loads.
- A redrawn icon now replaces the old one even when the two files are the same size.

## What's new in 1.0.0

- First release, with Ableton Live (every edition) and Yapfast.

## Features

- **Windows and taskbar.** Every window the app opens, its taskbar button and the Alt+Tab list show the new icon.
- **Shortcuts.** Start menu, desktop and pinned taskbar shortcuts that open the app, or borrow its icon, use the new one too.
- **One switch per app.** Turn an app off and it gets its own icon back.

## Notes

- The mod changes no app files. It keeps the icons and copies of your original shortcuts in `%LOCALAPPDATA%\Mocha App Icons`.
- Shortcuts shared by every user on the PC need admin rights, so Windows may ask once. If you say no, the mod leaves those shortcuts alone.
- To get the stock shortcut icons back, turn the mod off while the app is open.

## Credits

Ableton and Live are trademarks of Ableton AG. Yapfast is free software by its own authors. This mod is not made by or linked to either.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- ableton: true
  $name: Ableton Live
  $description: "Give Ableton Live the blue and mauve icon. When off, its own icon comes back"
- yapfast: true
  $name: Yapfast
  $description: "Give Yapfast the blue and mauve icon. When off, its own icon comes back"
- windowIcons: true
  $name: Window icons
  $description: "Use it on the app's windows, its taskbar button and in Alt+Tab"
- shortcutIcons: true
  $name: Shortcut icons
  $description: "Use it on the app's shortcuts in the Start menu, on the desktop and pinned to the taskbar"
- trayIcon: true
  $name: Tray icon
  $description: "Use it on the app's icon by the clock, if it has one"
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <commctrl.h>
#include <wincrypt.h>
#include <atomic>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <cwchar>

enum App { kNone = -1, kAbleton = 0, kYapfast = 1 };

struct AppInfo {
    PCWSTR setting;  // the app's own switch
    PCWSTR folder;   // its folder under Mocha App Icons
    PCWSTR file;     // the icon file
};

static constexpr AppInfo kApps[] = {
    {L"ableton", L"Ableton", L"Ableton-Mocha.ico"},
    {L"yapfast", L"Yapfast", L"Yapfast-Mocha.ico"},
};

static int g_app = kNone;
static std::atomic_bool g_trayOn{true};
static std::atomic_bool g_windowsOn{true};
static std::atomic_bool g_shortcutsOn{true};

static HANDLE g_stopEvent;
static HANDLE g_settingsEvent;
static HANDLE g_worker;
static UINT g_applyMsg;

static void ReadSettings() {
    bool appOn = Wh_GetIntSetting(kApps[g_app].setting) != 0;
    g_trayOn = appOn && Wh_GetIntSetting(L"trayIcon") != 0;
    g_windowsOn = appOn && Wh_GetIntSetting(L"windowIcons") != 0;
    g_shortcutsOn = appOn && Wh_GetIntSetting(L"shortcutIcons") != 0;
}

// ---------------------------------------------------------------- the icon

static std::wstring IconFile() {
    wchar_t folder[MAX_PATH];
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, folder))) return {};
    return std::wstring(folder) + L"\\Mocha App Icons\\" + kApps[g_app].folder + L"\\" + kApps[g_app].file;
}

static bool WriteIcon(const std::wstring& path) {
    static constexpr char ableton[] =
        "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"
    ;
    static constexpr char yapfast[] =
        "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"
    ;
    const char* data = g_app == kAbleton ? ableton : yapfast;
    DWORD size = 0;
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, nullptr, &size, nullptr, nullptr)) return false;
    std::vector<BYTE> bytes(size);
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, bytes.data(), &size, nullptr, nullptr)) return false;
    HANDLE old = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (old != INVALID_HANDLE_VALUE) {
        std::vector<BYTE> have(size + 1);
        DWORD got = 0;
        BOOL ok = ReadFile(old, have.data(), size + 1, &got, nullptr);
        CloseHandle(old);
        if (ok && got == size && !memcmp(have.data(), bytes.data(), size)) return true;
    }
    std::wstring dir = path.substr(0, path.rfind(L'\\'));
    SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
    wchar_t temp[MAX_PATH];
    if (!GetTempFileNameW(dir.c_str(), L"msi", 0, temp)) return false;
    HANDLE file = CreateFileW(temp, GENERIC_WRITE, 0, nullptr, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    bool ok = file != INVALID_HANDLE_VALUE && WriteFile(file, bytes.data(), size, &written, nullptr) && written == size;
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    // Yapfast starts two copies of itself; whoever loses the race finds the
    // file already in place.
    if (ok) ok = MoveFileExW(temp, path.c_str(), MOVEFILE_REPLACE_EXISTING) ||
                 GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
    DeleteFileW(temp);
    return ok;
}

static std::mutex g_iconMutex;
static std::map<int, HICON> g_icons;

static HICON MochaIcon(int size) {
    if (size <= 0) size = 16;
    std::lock_guard<std::mutex> lock(g_iconMutex);
    if (auto it = g_icons.find(size); it != g_icons.end()) return it->second;
    auto path = IconFile();
    if (path.empty() || !WriteIcon(path)) return nullptr;
    auto icon = (HICON)LoadImageW(nullptr, path.c_str(), IMAGE_ICON, size, size, LR_LOADFROMFILE);
    if (icon) g_icons.emplace(size, icon);
    return icon;
}

static bool OwnWindow(HWND hwnd) {
    DWORD pid = 0;
    return hwnd && GetWindowThreadProcessId(hwnd, &pid) && pid == GetCurrentProcessId();
}

// ---------------------------------------------------------------- windows
//
// Each app window is subclassed. Its icons are swapped for the Mocha ones,
// and any icon the app sets later is remembered and swapped too, so turning
// the switch off can hand back exactly what the app last asked for.

struct WindowIcons {
    HICON big = nullptr;
    HICON small = nullptr;
    bool themed = false;
};

static std::mutex g_windowMutex;
static std::map<HWND, WindowIcons> g_windows;

static HICON WindowIcon(HWND hwnd, bool big) {
    UINT dpi = GetDpiForWindow(hwnd);
    return MochaIcon(GetSystemMetricsForDpi(big ? SM_CXICON : SM_CXSMICON, dpi ? dpi : 96));
}

static void ThemeWindow(HWND hwnd, bool on) {
    WindowIcons state;
    {
        std::lock_guard<std::mutex> lock(g_windowMutex);
        state = g_windows[hwnd];
    }
    if (on == state.themed) return;
    if (on) {
        HICON big = WindowIcon(hwnd, true), small = WindowIcon(hwnd, false);
        if (!big || !small) return;
        state.big = (HICON)DefSubclassProc(hwnd, WM_SETICON, ICON_BIG, (LPARAM)big);
        state.small = (HICON)DefSubclassProc(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)small);
        state.themed = true;
    } else {
        DefSubclassProc(hwnd, WM_SETICON, ICON_BIG, (LPARAM)state.big);
        DefSubclassProc(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)state.small);
        state = {};
    }
    Wh_Log(L"window %p: %s", hwnd, on ? L"Mocha icon" : L"app icon");
    std::lock_guard<std::mutex> lock(g_windowMutex);
    g_windows[hwnd] = state;
}

static LRESULT CALLBACK IconSubclassProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    if (message == g_applyMsg && g_applyMsg) {
        ThemeWindow(hwnd, wParam != 0);
        return 1;
    }
    if (message == WM_SETICON && (wParam == ICON_BIG || wParam == ICON_SMALL)) {
        bool themed;
        {
            std::lock_guard<std::mutex> lock(g_windowMutex);
            auto it = g_windows.find(hwnd);
            themed = it != g_windows.end() && it->second.themed;
        }
        if (themed) {
            if (HICON ours = WindowIcon(hwnd, wParam == ICON_BIG)) {
                HICON previous;
                {
                    std::lock_guard<std::mutex> lock(g_windowMutex);
                    auto& state = g_windows[hwnd];
                    HICON& slot = wParam == ICON_BIG ? state.big : state.small;
                    previous = slot;
                    slot = (HICON)lParam;
                }
                DefSubclassProc(hwnd, WM_SETICON, wParam, (LPARAM)ours);
                // The app may free what it gets back, so it gets its own icon,
                // never ours.
                return (LRESULT)previous;
            }
        }
    }
    if (message == WM_NCDESTROY) {
        std::lock_guard<std::mutex> lock(g_windowMutex);
        g_windows.erase(hwnd);
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}

static std::mutex g_attachedMutex;
static std::set<HWND> g_attached;

static bool WantsIcon(HWND hwnd) {
    if (!IsWindow(hwnd) || !OwnWindow(hwnd)) return false;
    if (GetAncestor(hwnd, GA_PARENT) != GetDesktopWindow()) return false;
    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    LONG_PTR exStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    if (style & WS_CHILD) return false;
    return !(exStyle & WS_EX_TOOLWINDOW) || (exStyle & WS_EX_APPWINDOW);
}

static void Attach(HWND hwnd) {
    {
        std::lock_guard<std::mutex> lock(g_attachedMutex);
        for (auto it = g_attached.begin(); it != g_attached.end();) {
            it = IsWindow(*it) ? std::next(it) : g_attached.erase(it);
        }
        if (g_attached.contains(hwnd)) return;
    }
    if (!WindhawkUtils::SetWindowSubclassFromAnyThread(hwnd, IconSubclassProc, 0)) return;
    {
        std::lock_guard<std::mutex> lock(g_attachedMutex);
        g_attached.insert(hwnd);
    }
    SendMessageTimeoutW(hwnd, g_applyMsg, g_windowsOn ? 1 : 0, 0, SMTO_ABORTIFHUNG, 1000, nullptr);
}

static std::vector<HWND> AttachedWindows() {
    std::lock_guard<std::mutex> lock(g_attachedMutex);
    std::vector<HWND> out;
    for (HWND hwnd : g_attached) {
        if (IsWindow(hwnd)) out.push_back(hwnd);
    }
    return out;
}

// Returns false when a window did not answer, so its icons may still point
// at ours.
static bool ThemeAllWindows(bool on) {
    bool all = true;
    for (HWND hwnd : AttachedWindows()) {
        DWORD_PTR result = 0;
        if (!SendMessageTimeoutW(hwnd, g_applyMsg, on ? 1 : 0, 0, SMTO_ABORTIFHUNG, 2000, &result)) all = false;
    }
    return all;
}

static void CALLBACK ShowEvent(HWINEVENTHOOK, DWORD, HWND hwnd, LONG idObject, LONG idChild, DWORD, DWORD) {
    if (idObject == OBJID_WINDOW && idChild == CHILDID_SELF && WantsIcon(hwnd)) Attach(hwnd);
}

static BOOL CALLBACK AttachExisting(HWND hwnd, LPARAM) {
    if (IsWindowVisible(hwnd) && WantsIcon(hwnd)) Attach(hwnd);
    return TRUE;
}

// ---------------------------------------------------------------- tray

static decltype(&Shell_NotifyIconW) g_notifyIcon;

struct TrayTarget {
    bool known = false;
    HWND hwnd = nullptr;
    UINT id = 0;
    bool byGuid = false;
    GUID guid{};
};

static std::mutex g_trayMutex;
static TrayTarget g_tray;
static HICON g_stockTray;              // copy of the last icon the app itself set
static std::atomic_int g_trayThemed{-1};  // -1 untouched, 0 the app's icon, 1 ours

static BOOL CallNotify(DWORD action, PNOTIFYICONDATAW data) {
    return g_notifyIcon ? g_notifyIcon(action, data) : Shell_NotifyIconW(action, data);
}

static int TrayIconSize() {
    HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
    UINT dpi = taskbar ? GetDpiForWindow(taskbar) : 0;
    return GetSystemMetricsForDpi(SM_CXSMICON, dpi ? dpi : 96);
}

static bool SameTarget(const TrayTarget& t, const NOTIFYICONDATAW* data) {
    if (!t.known) return false;
    if (t.byGuid) return (data->uFlags & NIF_GUID) && IsEqualGUID(t.guid, data->guidItem);
    return t.hwnd == data->hWnd && t.id == data->uID;
}

static BOOL WINAPI NotifyIconHook(DWORD action, PNOTIFYICONDATAW data) {
    constexpr DWORD kMinSize = offsetof(NOTIFYICONDATAW, szTip);
    if (!data || data->cbSize < kMinSize || !OwnWindow(data->hWnd)) return CallNotify(action, data);
    bool hasGuid = data->cbSize >= offsetof(NOTIFYICONDATAW, hBalloonIcon) && (data->uFlags & NIF_GUID);
    if (action == NIM_DELETE) {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        if (SameTarget(g_tray, data)) {
            g_tray = {};
            g_trayThemed = -1;
        }
        return CallNotify(action, data);
    }
    if ((action != NIM_ADD && action != NIM_MODIFY) || !(data->uFlags & NIF_ICON)) return CallNotify(action, data);
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        g_tray.known = true;
        g_tray.hwnd = data->hWnd;
        g_tray.id = data->uID;
        g_tray.byGuid = hasGuid;
        if (hasGuid) g_tray.guid = data->guidItem;
        if (g_stockTray) DestroyIcon(g_stockTray);
        g_stockTray = data->hIcon ? CopyIcon(data->hIcon) : nullptr;
    }
    if (g_trayOn) {
        if (HICON ours = MochaIcon(TrayIconSize())) {
            NOTIFYICONDATAW copy{};
            memcpy(&copy, data, std::min<size_t>(data->cbSize, sizeof(copy)));
            copy.hIcon = ours;
            BOOL ok = CallNotify(action, &copy);
            if (ok) g_trayThemed = 1;
            Wh_Log(L"tray: the app set its icon, swapped for Mocha (%d)", ok);
            return ok;
        }
    }
    BOOL ok = CallNotify(action, data);
    if (ok) g_trayThemed = 0;
    return ok;
}

static void ProbeWindow(HWND hwnd) {
    if (g_tray.known) return;
    for (UINT id = 0; id < 8; ++id) {
        NOTIFYICONDATAW data{};
        data.cbSize = sizeof(data);
        data.hWnd = hwnd;
        data.uID = id;
        // A modify with no flags changes nothing and only says whether
        // this window owns an icon with this number.
        if (CallNotify(NIM_MODIFY, &data)) {
            g_tray.known = true;
            g_tray.hwnd = hwnd;
            g_tray.id = id;
            Wh_Log(L"tray: found the app's icon on %p, id %u", hwnd, id);
            return;
        }
    }
}

static BOOL CALLBACK ProbeTopLevel(HWND hwnd, LPARAM) {
    if (OwnWindow(hwnd)) ProbeWindow(hwnd);
    return !g_tray.known;
}

// The mod loaded into an app that already shows its tray icon: find it.
static void FindTrayIcon() {
    std::lock_guard<std::mutex> lock(g_trayMutex);
    if (g_tray.known) return;
    EnumWindows(ProbeTopLevel, 0);
    HWND hwnd = nullptr;
    while (!g_tray.known && (hwnd = FindWindowExW(HWND_MESSAGE, hwnd, nullptr, nullptr))) {
        if (OwnWindow(hwnd)) ProbeWindow(hwnd);
    }
}

static BOOL CALLBACK FirstIconGroup(HMODULE, LPCWSTR, LPWSTR name, LONG_PTR out) {
    auto* found = reinterpret_cast<std::wstring*>(out);
    *found = IS_INTRESOURCE(name) ? L"#" + std::to_wstring((UINT_PTR)name) : std::wstring(name);
    return FALSE;
}

static HICON AppExeIcon(int size) {
    std::wstring name;
    HMODULE module = GetModuleHandleW(nullptr);
    EnumResourceNamesW(module, RT_GROUP_ICON, FirstIconGroup, (LONG_PTR)&name);
    return name.empty() ? nullptr : (HICON)LoadImageW(module, name.c_str(), IMAGE_ICON, size, size, 0);
}

static void RefreshTray(bool on) {
    if (on) FindTrayIcon();
    TrayTarget target;
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        target = g_tray;
    }
    if (!target.known) return;
    if (on ? g_trayThemed == 1 : g_trayThemed != 1) return;
    NOTIFYICONDATAW data{};
    data.cbSize = sizeof(data);
    data.hWnd = target.hwnd;
    data.uID = target.id;
    data.uFlags = NIF_ICON | (target.byGuid ? NIF_GUID : 0);
    data.guidItem = target.guid;
    HICON stock = nullptr;
    if (on) {
        data.hIcon = MochaIcon(TrayIconSize());
    } else {
        {
            std::lock_guard<std::mutex> lock(g_trayMutex);
            if (g_stockTray) stock = CopyIcon(g_stockTray);
        }
        if (!stock) stock = AppExeIcon(TrayIconSize());
        data.hIcon = stock;
    }
    BOOL done = data.hIcon && CallNotify(NIM_MODIFY, &data);
    if (done) g_trayThemed = on ? 1 : 0;
    Wh_Log(L"tray: %s icon -> %d", on ? L"Mocha" : L"app", done);
    if (stock) DestroyIcon(stock);
}

// ---------------------------------------------------------------- shortcuts
//
// Same method as the Mocha Windhawk icons: the original shortcut is copied
// beside the icon before its icon changes, and that copy is how it goes back.
// Shared shortcuts need admin rights, so their edited copies go in through
// one hidden elevated copy.

struct ShortcutCopy {
    std::wstring from, to;
};

static bool g_shortcutChanged;

// The taskbar and Start keep showing a shortcut's old picture until the shell
// hears that picture changed, so tell it about both the app's and ours.
static void RefreshShellImages(const std::wstring& icon) {
    wchar_t exe[MAX_PATH];
    std::vector<std::wstring> files{icon};
    if (GetModuleFileNameW(nullptr, exe, ARRAYSIZE(exe))) files.push_back(exe);
    for (const auto& path : files) {
        SHFILEINFOW info{};
        if (SHGetFileInfoW(path.c_str(), 0, &info, sizeof(info), SHGFI_SYSICONINDEX) && info.iIcon > 0) {
            SHChangeNotify(SHCNE_UPDATEIMAGE, SHCNF_DWORD, (LPCVOID)(INT_PTR)info.iIcon, nullptr);
        }
    }
    Wh_Log(L"shortcuts: asked the shell to redraw the app's icons");
}

static void UpdateShortcutIcon(IShellLinkW* link, IPersistFile* file, const std::wstring& path,
                               const std::wstring& icon, const std::wstring& backup, bool enabled,
                               std::vector<ShortcutCopy>& pending) {
    if (GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES) return;
    if (FAILED(file->Load(path.c_str(), STGM_READ))) return;
    wchar_t target[MAX_PATH], image[MAX_PATH];
    int index = 0;
    if (FAILED(link->GetPath(target, ARRAYSIZE(target), nullptr, SLGP_RAWPATH)) ||
        FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &index))) return;
    wchar_t installed[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, installed, ARRAYSIZE(installed))) return;
    auto same = [&](PCWSTR raw) {
        wchar_t expanded[MAX_PATH];
        DWORD count = ExpandEnvironmentStringsW(raw, expanded, ARRAYSIZE(expanded));
        return count && count <= ARRAYSIZE(expanded) && _wcsicmp(expanded, installed) == 0;
    };
    bool themedNow = _wcsicmp(image, icon.c_str()) == 0;
    bool opensApp = same(target);
    bool borrowsIcon = index == 0 && same(image);
    // A shortcut we themed earlier is still ours: its backup says so.
    if (!opensApp && !borrowsIcon && !(themedNow && GetFileAttributesW(backup.c_str()) != INVALID_FILE_ATTRIBUTES)) return;

    if (enabled == themedNow) return;
    std::wstring next = icon;
    int nextIndex = 0;
    if (enabled) {
        if (!CopyFileW(path.c_str(), backup.c_str(), FALSE)) return;
    } else {
        if (GetFileAttributesW(backup.c_str()) == INVALID_FILE_ATTRIBUTES ||
            FAILED(file->Load(backup.c_str(), STGM_READ)) ||
            FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &nextIndex)) ||
            FAILED(file->Load(path.c_str(), STGM_READ))) return;
        next = image;
    }
    if (FAILED(link->SetIconLocation(next.c_str(), nextIndex))) return;
    if (SUCCEEDED(file->Save(path.c_str(), TRUE))) {
        SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, path.c_str(), nullptr);
        g_shortcutChanged = true;
        Wh_Log(L"shortcut %s: %s", enabled ? L"Mocha" : L"restored", path.c_str());
        if (!enabled) DeleteFileW(backup.c_str());
        return;
    }
    std::wstring staged = backup + L".new.lnk";
    if (SUCCEEDED(file->Save(staged.c_str(), FALSE))) pending.push_back({staged, path});
}

// The admin prompt runs in a hidden helper, so the app never sits waiting on
// it: the mod waits on the helper and gives up when the app or the mod stops.
static void CopySharedShortcuts(const std::vector<ShortcutCopy>& pending, bool enabled, HANDLE stop) {
    if (pending.empty()) return;
    // A "no" to the admin prompt is remembered, so the app does not ask on
    // every start. Turning the shortcut switch back on asks again.
    bool give = !(enabled && Wh_GetIntValue(L"sharedDeclined", 0));
    std::wstring dir = pending[0].from.substr(0, pending[0].from.rfind(L'\\'));
    std::wstring batch = dir + L"\\copy-shortcuts.cmd";
    std::string text = "@chcp 65001 >nul\r\n";
    for (const auto& item : pending) {
        std::wstring line = L"@copy /y \"" + item.from + L"\" \"" + item.to + L"\" >nul\r\n";
        int size = WideCharToMultiByte(CP_UTF8, 0, line.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string utf8(size > 0 ? size - 1 : 0, '\0');
        if (size > 1) WideCharToMultiByte(CP_UTF8, 0, line.c_str(), -1, utf8.data(), size, nullptr, nullptr);
        text += utf8;
    }
    HANDLE file = give ? CreateFileW(batch.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr)
                       : INVALID_HANDLE_VALUE;
    DWORD written = 0;
    bool ready = file != INVALID_HANDLE_VALUE && WriteFile(file, text.data(), (DWORD)text.size(), &written, nullptr) &&
                 written == text.size();
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);

    wchar_t system[MAX_PATH];
    if (ready && GetSystemDirectoryW(system, ARRAYSIZE(system))) {
        std::wstring quoted;
        for (wchar_t c : batch) quoted += c == L'\'' ? std::wstring(L"''") : std::wstring(1, c);
        std::wstring script = L"try { Start-Process -FilePath $env:ComSpec -ArgumentList '/d /c \"" + quoted +
                              L"\"' -Verb RunAs -WindowStyle Hidden -Wait -ErrorAction Stop; exit 0 } catch { exit 5 }";
        DWORD chars = 0;
        auto bytes = reinterpret_cast<const BYTE*>(script.data());
        DWORD length = (DWORD)(script.size() * sizeof(wchar_t));
        CryptBinaryToStringW(bytes, length, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, nullptr, &chars);
        std::wstring encoded(chars, L'\0');
        if (chars && CryptBinaryToStringW(bytes, length, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, encoded.data(), &chars)) {
            encoded.resize(chars);
            std::wstring command = L"\"" + std::wstring(system) +
                                   L"\\WindowsPowerShell\\v1.0\\powershell.exe\" -NoProfile -NonInteractive "
                                   L"-WindowStyle Hidden -EncodedCommand " + encoded;
            STARTUPINFOW startup{sizeof(startup)};
            startup.dwFlags = STARTF_USESHOWWINDOW;
            startup.wShowWindow = SW_HIDE;
            PROCESS_INFORMATION process{};
            if (CreateProcessW(nullptr, command.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr,
                               &startup, &process)) {
                CloseHandle(process.hThread);
                HANDLE waits[] = {process.hProcess, stop};
                DWORD wait = WaitForMultipleObjects(stop ? 2 : 1, waits, FALSE, stop ? 120000 : 30000);
                DWORD code = STILL_ACTIVE;
                if (wait == WAIT_OBJECT_0) GetExitCodeProcess(process.hProcess, &code);
                CloseHandle(process.hProcess);
                if (code == 0) {
                    for (const auto& item : pending) {
                        SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, item.to.c_str(), nullptr);
                        g_shortcutChanged = true;
                        Wh_Log(L"shortcut %s (shared): %s", enabled ? L"Mocha" : L"restored", item.to.c_str());
                    }
                } else if (code == 5) {
                    Wh_Log(L"shared shortcuts: admin prompt declined");
                    if (enabled) Wh_SetIntValue(L"sharedDeclined", 1);
                }
                // Still waiting on the prompt: leave the helper its files.
                if (code == STILL_ACTIVE) return;
            }
        }
    }
    DeleteFileW(batch.c_str());
    for (const auto& item : pending) DeleteFileW(item.from.c_str());
}

static std::wstring BackupName(const std::wstring& base, const std::wstring& path) {
    // One backup per shortcut, named by a hash of its lower-case path.
    unsigned long long hash = 1469598103934665603ull;
    for (wchar_t c : path) {
        hash ^= (unsigned long long)towlower(c);
        hash *= 1099511628211ull;
    }
    wchar_t name[32];
    swprintf_s(name, L"\\%016llx.lnk", hash);
    return base + name;
}

static void FindShortcuts(const std::wstring& dir, int depth, std::vector<std::wstring>& out) {
    WIN32_FIND_DATAW found;
    HANDLE find = FindFirstFileExW((dir + L"\\*").c_str(), FindExInfoBasic, &found, FindExSearchNameMatch, nullptr, 0);
    if (find == INVALID_HANDLE_VALUE) return;
    do {
        std::wstring name = found.cFileName;
        if (name == L"." || name == L"..") continue;
        if (found.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) continue;
        if (found.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (depth > 0) FindShortcuts(dir + L"\\" + name, depth - 1, out);
        } else if (name.size() > 4 && _wcsicmp(name.c_str() + name.size() - 4, L".lnk") == 0) {
            out.push_back(dir + L"\\" + name);
        }
    } while (FindNextFileW(find, &found));
    FindClose(find);
}

static void UpdateShortcutIcons(bool enabled, HANDLE stop) {
    auto icon = IconFile();
    if (icon.empty() || (enabled && !WriteIcon(icon))) return;
    std::wstring base = icon.substr(0, icon.rfind(L'\\'));
    // Yapfast runs two copies of itself; only one edits shortcuts at a time.
    std::wstring lockName = std::wstring(L"Local\\MochaAppIcons.Shortcuts.") + kApps[g_app].folder;
    HANDLE lock = CreateMutexW(nullptr, FALSE, lockName.c_str());
    if (lock && WaitForSingleObject(lock, 60000) == WAIT_TIMEOUT) {
        CloseHandle(lock);
        return;
    }
    HRESULT init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (SUCCEEDED(init)) {
        IShellLinkW* link = nullptr;
        if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW,
                                       reinterpret_cast<void**>(&link)))) {
            IPersistFile* file = nullptr;
            if (SUCCEEDED(link->QueryInterface(IID_IPersistFile, reinterpret_cast<void**>(&file)))) {
                static constexpr struct {
                    int folder;
                    PCWSTR suffix;
                    int depth;
                } places[] = {
                    {CSIDL_COMMON_PROGRAMS, L"", 2},
                    {CSIDL_PROGRAMS, L"", 2},
                    {CSIDL_COMMON_DESKTOPDIRECTORY, L"", 0},
                    {CSIDL_DESKTOPDIRECTORY, L"", 0},
                    {CSIDL_APPDATA, L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar", 0},
                };
                std::vector<std::wstring> paths;
                for (const auto& place : places) {
                    wchar_t folder[MAX_PATH];
                    if (SUCCEEDED(SHGetFolderPathW(nullptr, place.folder, nullptr, SHGFP_TYPE_CURRENT, folder))) {
                        FindShortcuts(std::wstring(folder) + place.suffix, place.depth, paths);
                    }
                }
                std::vector<ShortcutCopy> pending;
                g_shortcutChanged = false;
                for (const auto& path : paths) {
                    if (stop && WaitForSingleObject(stop, 0) == WAIT_OBJECT_0) break;
                    UpdateShortcutIcon(link, file, path, icon, BackupName(base, path), enabled, pending);
                }
                file->Release();
                CopySharedShortcuts(pending, enabled, stop);
                if (g_shortcutChanged) RefreshShellImages(icon);
            }
            link->Release();
        }
        CoUninitialize();
    }
    if (lock) {
        ReleaseMutex(lock);
        CloseHandle(lock);
    }
}

// The mod was turned off or removed, not just reloaded or the app closing.
static bool ModTurnedOff() {
    std::wstring key = L"SOFTWARE\\Windhawk\\Engine\\Mods\\";
    key += WH_MOD_ID;
    HKEY handle;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ, &handle) != ERROR_SUCCESS) {
        HKEY mods;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods", 0, KEY_READ, &mods) != ERROR_SUCCESS) {
            return false;  // settings live elsewhere (portable Windhawk): never guess
        }
        RegCloseKey(mods);
        return true;
    }
    DWORD disabled = 0, size = sizeof(disabled);
    bool off = RegQueryValueExW(handle, L"Disabled", nullptr, nullptr, (BYTE*)&disabled, &size) == ERROR_SUCCESS &&
               disabled;
    RegCloseKey(handle);
    return off;
}

// ---------------------------------------------------------------- worker

static void ApplyAll() {
    ThemeAllWindows(g_windowsOn);
    RefreshTray(g_trayOn);
    UpdateShortcutIcons(g_shortcutsOn, g_stopEvent);
}

static DWORD WINAPI Worker(LPVOID) {
    HWINEVENTHOOK hook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, ShowEvent,
                                         GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT);
    EnumWindows(AttachExisting, 0);
    RefreshTray(g_trayOn);
    UpdateShortcutIcons(g_shortcutsOn, g_stopEvent);
    HANDLE events[] = {g_stopEvent, g_settingsEvent};
    for (;;) {
        DWORD wait = MsgWaitForMultipleObjects(2, events, FALSE, INFINITE, QS_ALLINPUT);
        if (wait == WAIT_OBJECT_0) break;
        if (wait == WAIT_OBJECT_0 + 1) {
            ApplyAll();
            continue;
        }
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
    }
    if (hook) UnhookWinEvent(hook);
    return 0;
}

// ---------------------------------------------------------------- Windhawk

BOOL Wh_ModInit() {
    wchar_t image[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, image, ARRAYSIZE(image))) return FALSE;
    PCWSTR name = wcsrchr(image, L'\\');
    name = name ? name + 1 : image;
    if (_wcsnicmp(name, L"Ableton Live", 12) == 0) {
        g_app = kAbleton;
    } else if (_wcsicmp(name, L"yapfast.exe") == 0) {
        g_app = kYapfast;
    } else {
        return FALSE;
    }

    ReadSettings();
    g_applyMsg = RegisterWindowMessageW(L"MochaAppIcons.Apply");
    Wh_SetFunctionHook((void*)Shell_NotifyIconW, (void*)NotifyIconHook, (void**)&g_notifyIcon);

    g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_settingsEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (g_stopEvent && g_settingsEvent) g_worker = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
    return TRUE;
}

void Wh_ModUninit() {
    if (g_worker) {
        SetEvent(g_stopEvent);
        WaitForSingleObject(g_worker, 30000);
        CloseHandle(g_worker);
        g_worker = nullptr;
    }
    bool restored = ThemeAllWindows(false);
    WindhawkUtils::RemoveAllWindowSubclasses();
    RefreshTray(false);
    if (ModTurnedOff()) UpdateShortcutIcons(false, nullptr);
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        if (g_stockTray) DestroyIcon(g_stockTray);
        g_stockTray = nullptr;
    }
    // A window that did not answer may still show our icon; keep the icons
    // alive rather than leave it pointing at freed ones.
    if (restored && g_trayThemed != 1) {
        std::lock_guard<std::mutex> lock(g_iconMutex);
        for (const auto& [size, icon] : g_icons) DestroyIcon(icon);
        g_icons.clear();
    }
    if (g_stopEvent) CloseHandle(g_stopEvent);
    if (g_settingsEvent) CloseHandle(g_settingsEvent);
    g_stopEvent = g_settingsEvent = nullptr;
}

void Wh_ModSettingsChanged() {
    bool shortcutsWere = g_shortcutsOn;
    ReadSettings();
    if (g_shortcutsOn && !shortcutsWere) Wh_SetIntValue(L"sharedDeclined", 0);
    if (g_settingsEvent) SetEvent(g_settingsEvent);
}
