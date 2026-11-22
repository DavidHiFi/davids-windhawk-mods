// ==WindhawkMod==
// @id              mocha-steam-icons
// @name            Mocha Steam Icons
// @description     Gives Steam a blue to mauve icon in the tray, on its windows and on its shortcuts
// @version         1.0.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         steam.exe
// @include         steamwebhelper.exe
// @architecture    x86-64
// @compilerOptions -DWIN32_LEAN_AND_MEAN -luser32 -lshell32 -lole32 -luuid -lcrypt32 -ladvapi32 -lcomctl32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Mocha Steam Icons

Swaps Steam's icon for a Catppuccin Mocha one, the Steam logo on a blue to mauve tile, everywhere Windows shows it. It goes well with the MochaSteam theme for Millennium and works without it too.

![Mocha Steam Icons preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/mocha-steam-icons.png)

## What's new in 1.0.0

- First release. The tray icon, every Steam window, its taskbar button and the Steam shortcuts get the blue and mauve icon.

## Features

- **Tray icon.** The Steam icon by the clock turns blue and mauve, and stays that way when Steam updates it or Explorer restarts.
- **Windows and taskbar.** The main window, Big Picture, chats, pop-outs and the Alt+Tab list all show the new icon.
- **Shortcuts.** The Steam shortcuts in the Start menu, on the desktop and pinned to the taskbar use it too.
- **Easy to undo.** Each switch puts Steam's own icon back when you turn it off, and turning the mod off puts everything back.

## Notes

- The mod changes no Steam files. It keeps the icon and copies of your original shortcuts in `%LOCALAPPDATA%\Mocha Steam`.
- Shortcuts shared by every user on the PC need admin rights, so Windows may ask once. If you say no, the mod leaves those shortcuts alone.
- To get the stock shortcut icons back, turn the mod off while Steam is open.

## Credits

Steam and the Steam logo are trademarks of Valve Corporation. This mod is not made by or linked to Valve.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- trayIcon: true
  $name: Tray icon
  $description: "Use the blue and mauve icon in the tray. When off, Steam's own tray icon comes back"
- windowIcons: true
  $name: Window icons
  $description: "Use it on every Steam window, its taskbar button and in Alt+Tab. When off, Steam's own icon comes back"
- shortcutIcons: true
  $name: Shortcut icons
  $description: "Use it on the Steam shortcuts in the Start menu, on the desktop and pinned to the taskbar. When off, the stock icons come back"
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

static std::atomic_bool g_trayOn{true};
static std::atomic_bool g_windowsOn{true};
static std::atomic_bool g_shortcutsOn{true};
static bool g_isSteam = false;  // steam.exe owns the tray icon and the shortcuts

static HANDLE g_stopEvent;
static HANDLE g_settingsEvent;
static HANDLE g_worker;
static UINT g_applyMsg;

static void ReadSettings() {
    g_trayOn = Wh_GetIntSetting(L"trayIcon") != 0;
    g_windowsOn = Wh_GetIntSetting(L"windowIcons") != 0;
    g_shortcutsOn = Wh_GetIntSetting(L"shortcutIcons") != 0;
}

// ---------------------------------------------------------------- the icon

static std::wstring IconFile() {
    wchar_t folder[MAX_PATH];
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, folder))) return {};
    return std::wstring(folder) + L"\\Mocha Steam\\Steam-Mocha.ico";
}

static bool WriteIcon(const std::wstring& path) {
    static constexpr char data[] =
        "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"
    ;
    DWORD size = 0;
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, nullptr, &size, nullptr, nullptr)) return false;
    std::vector<BYTE> bytes(size);
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, bytes.data(), &size, nullptr, nullptr)) return false;
    WIN32_FILE_ATTRIBUTE_DATA info;
    if (GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &info) && !info.nFileSizeHigh &&
        info.nFileSizeLow == size) {
        return true;
    }
    std::wstring dir = path.substr(0, path.rfind(L'\\'));
    CreateDirectoryW(dir.c_str(), nullptr);
    wchar_t temp[MAX_PATH];
    if (!GetTempFileNameW(dir.c_str(), L"msi", 0, temp)) return false;
    HANDLE file = CreateFileW(temp, GENERIC_WRITE, 0, nullptr, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    bool ok = file != INVALID_HANDLE_VALUE && WriteFile(file, bytes.data(), size, &written, nullptr) && written == size;
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    // steam.exe and the web helper start together; whoever loses the race
    // finds the file already in place.
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
// Each Steam window is subclassed. Its icons are swapped for the Mocha ones,
// and any icon Steam sets later is remembered and swapped too, so turning
// the switch off can hand back exactly what Steam last asked for.

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
    Wh_Log(L"window %p: %s", hwnd, on ? L"Mocha icon" : L"Steam icon");
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
                // Steam may free what it gets back, so it gets its own icon,
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
static HICON g_stockTray;              // copy of the last icon Steam itself set
static std::atomic_int g_trayThemed{-1};  // -1 untouched, 0 Steam's icon, 1 ours

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
            Wh_Log(L"tray: Steam set its icon, swapped for Mocha (%d)", ok);
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
            Wh_Log(L"tray: found Steam's icon on %p, id %u", hwnd, id);
            return;
        }
    }
}

static BOOL CALLBACK ProbeTopLevel(HWND hwnd, LPARAM) {
    if (OwnWindow(hwnd)) ProbeWindow(hwnd);
    return !g_tray.known;
}

// The mod loaded into a Steam that already shows its tray icon: find it.
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

static HICON SteamExeIcon(int size) {
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
        if (!stock) stock = SteamExeIcon(TrayIconSize());
        data.hIcon = stock;
    }
    BOOL done = data.hIcon && CallNotify(NIM_MODIFY, &data);
    if (done) g_trayThemed = on ? 1 : 0;
    Wh_Log(L"tray: %s icon -> %d", on ? L"Mocha" : L"Steam", done);
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

static void UpdateShortcutIcon(IShellLinkW* link, IPersistFile* file, const std::wstring& path,
                               const std::wstring& icon, const std::wstring& backup, bool enabled,
                               std::vector<ShortcutCopy>& pending) {
    if (GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES) return;
    if (FAILED(file->Load(path.c_str(), STGM_READ))) return;
    wchar_t target[MAX_PATH], image[MAX_PATH], args[1024];
    int index = 0;
    if (FAILED(link->GetPath(target, ARRAYSIZE(target), nullptr, SLGP_RAWPATH)) ||
        FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &index))) return;
    if (FAILED(link->GetArguments(args, ARRAYSIZE(args)))) args[0] = 0;
    // A game shortcut also points at steam.exe; it carries a launch argument.
    if (wcsstr(args, L"-applaunch") || wcsstr(args, L"steam://") || wcsstr(args, L"-rungameid")) return;
    wchar_t expanded[MAX_PATH], installed[MAX_PATH];
    DWORD count = ExpandEnvironmentStringsW(target, expanded, ARRAYSIZE(expanded));
    if (!count || count > ARRAYSIZE(expanded) ||
        !GetModuleFileNameW(nullptr, installed, ARRAYSIZE(installed)) ||
        _wcsicmp(expanded, installed) != 0) return;

    bool themed = _wcsicmp(image, icon.c_str()) == 0;
    if (enabled == themed) return;
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
        Wh_Log(L"shortcut %s: %s", enabled ? L"Mocha" : L"restored", path.c_str());
        if (!enabled) DeleteFileW(backup.c_str());
        return;
    }
    std::wstring staged = backup + L".new.lnk";
    if (SUCCEEDED(file->Save(staged.c_str(), FALSE))) pending.push_back({staged, path});
}

// The admin prompt runs in a hidden helper, so Steam never sits waiting on
// it: the mod waits on the helper and gives up when Steam or the mod stops.
static void CopySharedShortcuts(const std::vector<ShortcutCopy>& pending, bool enabled, HANDLE stop) {
    if (pending.empty()) return;
    // A "no" to the admin prompt is remembered, so Steam does not ask on
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

static void UpdateShortcutIcons(bool enabled, HANDLE stop) {
    auto icon = IconFile();
    if (icon.empty() || (enabled && !WriteIcon(icon))) return;
    std::wstring base = icon.substr(0, icon.rfind(L'\\')) + L"\\Steam";
    HRESULT init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(init)) return;
    IShellLinkW* link = nullptr;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW,
                                   reinterpret_cast<void**>(&link)))) {
        IPersistFile* file = nullptr;
        if (SUCCEEDED(link->QueryInterface(IID_IPersistFile, reinterpret_cast<void**>(&file)))) {
            static constexpr struct {
                int folder;
                PCWSTR suffix;
                PCWSTR backupSuffix;
            } shortcuts[] = {
                {CSIDL_COMMON_PROGRAMS, L"\\Steam\\Steam.lnk", L".common-programs.lnk"},
                {CSIDL_PROGRAMS, L"\\Steam\\Steam.lnk", L".programs.lnk"},
                {CSIDL_COMMON_PROGRAMS, L"\\Steam.lnk", L".common-programs-top.lnk"},
                {CSIDL_PROGRAMS, L"\\Steam.lnk", L".programs-top.lnk"},
                {CSIDL_COMMON_DESKTOPDIRECTORY, L"\\Steam.lnk", L".common-desktop.lnk"},
                {CSIDL_DESKTOPDIRECTORY, L"\\Steam.lnk", L".desktop.lnk"},
                {CSIDL_APPDATA, L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar\\Steam.lnk", L".taskbar.lnk"},
            };
            std::vector<ShortcutCopy> pending;
            for (const auto& shortcut : shortcuts) {
                wchar_t folder[MAX_PATH];
                if (SUCCEEDED(SHGetFolderPathW(nullptr, shortcut.folder, nullptr, SHGFP_TYPE_CURRENT, folder))) {
                    UpdateShortcutIcon(link, file, std::wstring(folder) + shortcut.suffix, icon,
                                       base + shortcut.backupSuffix, enabled, pending);
                }
            }
            file->Release();
            CopySharedShortcuts(pending, enabled, stop);
        }
        link->Release();
    }
    CoUninitialize();
}

// The mod was turned off or removed, not just reloaded or Steam closing.
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
    if (g_isSteam) {
        RefreshTray(g_trayOn);
        UpdateShortcutIcons(g_shortcutsOn, g_stopEvent);
    }
}

static DWORD WINAPI Worker(LPVOID) {
    HWINEVENTHOOK hook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, ShowEvent,
                                         GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT);
    EnumWindows(AttachExisting, 0);
    if (g_isSteam) {
        RefreshTray(g_trayOn);
        UpdateShortcutIcons(g_shortcutsOn, g_stopEvent);
    }
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
    g_isSteam = _wcsicmp(name, L"steam.exe") == 0;
    // The web helper starts many copies of itself; only the main one, with
    // no --type, owns the Steam windows.
    if (!g_isSteam && wcsstr(GetCommandLineW(), L"--type=")) return FALSE;

    ReadSettings();
    g_applyMsg = RegisterWindowMessageW(L"MochaSteamIcons.Apply");
    if (g_isSteam) Wh_SetFunctionHook((void*)Shell_NotifyIconW, (void*)NotifyIconHook, (void**)&g_notifyIcon);

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
    if (g_isSteam) {
        RefreshTray(false);
        if (ModTurnedOff()) UpdateShortcutIcons(false, nullptr);
    }
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
