// ==WindhawkMod==
// @id startup-control
// @name Startup Control
// @description Manage startup apps, scheduled tasks and Windows startup locations.
// @version 0.1.8
// @author DavidHiFi
// @github https://github.com/DavidHiFi
// @homepage https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl https://ko-fi.com/DavidHiFi
// @include windhawk.exe
// @include windhawk-mod.exe
// @include windhawk-mod-elevated.exe
// @compilerOptions -ld2d1 -ldwrite -ldwmapi -lwindowscodecs -lole32 -loleaut32 -luuid -ltaskschd -lwevtapi -lsetupapi -lcfgmgr32 -ladvapi32 -lshell32 -lshlwapi -lcomdlg32 -lcomctl32 -luxtheme -lgdi32 -lwbemuuid -lversion -lwintrust
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Startup Control

![Startup Control](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/startup-control.png)

See and switch off everything that starts with Windows, in one calm window.

- Startup apps and shortcuts, scheduled tasks, services, drivers, devices,
  Explorer add-ons and the deeper places programs hide in.
- Every entry has an on and off switch. Turning one off keeps a copy, so the
  Changes page can put it back.
- Its own Tasks tab replaces Task Scheduler: details, run history, run and
  end, edit the task file, make a new task, delete one.
- Things Windows protects show as view-only, so nothing important gets broken.
- Each scan type and safety prompt can be switched off in the settings.

## What's new in 0.1.8

- The window shows its own icon on the taskbar instead of a blank one.
- Right-clicking the tray icon opens its menu and the menu stays open.
- You can open the window from this settings page: flip "Open the settings
  window" and press Save.

This is a first release. Keep Autoruns around until you have checked the
entries you care about.

Startup Control was written from scratch from how Windows documents these
places. Autoruns is not open source, and none of its code or files are used.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- openSettingsWindow: false
  $name: "Open the settings window"
  $description: "Flip this switch either way and press Save to open the Startup Control window."
- scanRegistry: true
  $name: "Scan registry locations"
  $description: "Include logon entries and advanced integrations."
- scanTasks: true
  $name: "Scan scheduled tasks"
  $description: "Include hidden tasks and task subfolders."
- scanServices: true
  $name: "Scan services and drivers"
  $description: "Read startup modes and dependencies."
- scanDevices: true
  $name: "Scan devices"
  $description: "Include disconnected devices."
- scanWmi: true
  $name: "Scan WMI subscriptions"
  $description: "Read event filters, consumers and their bindings."
- showViewOnly: true
  $name: "Show entries you cannot change"
  $description: "Lists protected entries too, with a lock instead of a switch."
- groupByLocation: true
  $name: "Group Everything by location"
  $description: "Splits the Everything page into one section per location."
- confirmDevices: true
  $name: "Ask before turning off a device"
  $description: "Turning off a device needs a second click."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Show Startup Control in the notification area."
*/
// ==/WindhawkModSettings==

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <commdlg.h>
#include <commctrl.h>
#include <uxtheme.h>
#include <dwmapi.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <wrl/client.h>
#include <taskschd.h>
#include <winevt.h>
#include <winsvc.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <cfg.h>
#include <wintrust.h>
#include <mscat.h>
#include <softpub.h>
#include <wincrypt.h>
#include <sddl.h>
#include <wbemidl.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <memory>
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <thread>
#include <functional>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <cwctype>
#include <windhawk_api.h>
using Microsoft::WRL::ComPtr;
namespace sc {
inline std::wstring Error(DWORD code) {
    wchar_t* raw = nullptr;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr, code, 0, reinterpret_cast<LPWSTR>(&raw), 0, nullptr);
    std::wstring s = raw ? raw : L"Windows error " + std::to_wstring(code);
    if (raw) LocalFree(raw);
    while (!s.empty() && iswspace(s.back())) s.pop_back();
    return s;
}
inline std::wstring Hex(unsigned long value) {
    std::wostringstream s;
    s << L"0x" << std::hex << std::uppercase << value;
    return s.str();
}
inline std::wstring Lower(std::wstring s) {
    std::transform(s.begin(), s.end(), s.begin(), [](wchar_t c) { return towlower(c); });
    return s;
}
inline std::wstring Expand(const std::wstring& s) {
    DWORD n = ExpandEnvironmentStringsW(s.c_str(), nullptr, 0);
    if (!n || n > 32768) return s;
    std::wstring out(n, 0);
    ExpandEnvironmentStringsW(s.c_str(), out.data(), n);
    out.resize(n - 1);
    return out;
}
inline std::wstring Bstr(BSTR s) { return s ? std::wstring(s, SysStringLen(s)) : L""; }
struct BString {
    BSTR p = nullptr;
    explicit BString(const std::wstring& s) : p(SysAllocStringLen(s.data(), static_cast<UINT>(s.size()))) {}
    BString(const BString&) = delete;
    BString& operator=(const BString&) = delete;
    ~BString() { SysFreeString(p); }
    operator BSTR() const { return p; }
};
struct Apartment {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    ~Apartment() { if (SUCCEEDED(hr)) CoUninitialize(); }
};
struct RegKey {
    HKEY h = nullptr;
    RegKey() = default;
    RegKey(const RegKey&) = delete;
    ~RegKey() { if (h) RegCloseKey(h); }
};
struct ServiceHandle {
    SC_HANDLE h = nullptr;
    explicit ServiceHandle(SC_HANDLE value = nullptr) : h(value) {}
    ServiceHandle(const ServiceHandle&) = delete;
    ServiceHandle& operator=(const ServiceHandle&) = delete;
    ~ServiceHandle() { if (h) CloseServiceHandle(h); }
    operator SC_HANDLE() const { return h; }
};
inline std::wstring TextValue(HKEY key, const wchar_t* name) {
    DWORD type = 0, bytes = 0;
    if (RegQueryValueExW(key, name, nullptr, &type, nullptr, &bytes) != ERROR_SUCCESS || bytes > 1024 * 1024) return L"";
    if (type != REG_SZ && type != REG_EXPAND_SZ && type != REG_MULTI_SZ) return L"";
    std::vector<wchar_t> b(bytes / 2 + 2);
    if (RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(b.data()), &bytes) != ERROR_SUCCESS) return L"";
    if (type == REG_MULTI_SZ) {
        std::wstring result;
        for (size_t p = 0; p < bytes / 2 && b[p];) {
            std::wstring part(&b[p]);
            if (!result.empty()) result += L"; ";
            result += part;
            p += part.size() + 1;
        }
        return result;
    }
    return b.data();
}
inline std::wstring DataRoot() {
    wchar_t p[MAX_PATH]{};
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, p))) return L"";
    std::wstring root = std::wstring(p) + L"\\StartupControl";
    CreateDirectoryW(root.c_str(), nullptr);
    return root;
}
inline bool Elevated() {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return false;
    TOKEN_ELEVATION e{};
    DWORD n;
    bool ok = GetTokenInformation(token, TokenElevation, &e, sizeof(e), &n) && e.TokenIsElevated;
    CloseHandle(token);
    return ok;
}
inline std::wstring XmlEscape(const std::wstring& s) {
    std::wstring out;
    for (wchar_t c : s) {
        switch (c) {
            case L'&': out += L"&amp;"; break;
            case L'<': out += L"&lt;"; break;
            case L'>': out += L"&gt;"; break;
            case L'\"': out += L"&quot;"; break;
            case L'\'': out += L"&apos;"; break;
            default: out += c;
        }
    }
    return out;
}
inline std::wstring Target(const std::wstring& command) {
    auto s = Expand(command);
    if (s.rfind(L"\\SystemRoot\\", 0) == 0) s = Expand(L"%SystemRoot%\\") + s.substr(12);
    if (s.rfind(L"\\??\\", 0) == 0) s = s.substr(4);
    if (Lower(s).rfind(L"system32\\", 0) == 0) s = Expand(L"%SystemRoot%\\") + s;
    if (s.empty()) return s;
    if (s.front() == L'\"') {
        auto end = s.find(L'\"', 1);
        return end == s.npos ? s : s.substr(1, end - 1);
    }
    auto exe = Lower(s).find(L".exe");
    if (exe != s.npos) return s.substr(0, exe + 4);
    return s.substr(0, s.find_first_of(L" \t,"));
}
}

namespace sc {
enum class Kind { Registry, Shortcut, Task, Service, Driver, Device, Wmi, Notice };
struct Entry {
    Kind kind = Kind::Notice;
    std::wstring id, name, category, source, command, target, detail;
    std::wstring key, value, user;
    DWORD view = KEY_WOW64_64KEY, type = 0;
    bool machine = false, enabled = true, writable = false, missing = false;
    bool disabledStore = false;
    bool windows = false;  // shipped by Microsoft as part of Windows
    std::vector<BYTE> raw;
    DWORD startMode = 0;
};
struct Inventory {
    std::vector<Entry> entries;
    std::vector<std::wstring> errors;
    ULONGLONG revision = 0;
};
std::mutex g_dataMutex;
Inventory g_inventory;
std::atomic<bool> g_cancel{false}, g_scanning{false};
std::thread g_scanThread;
std::atomic<HWND> g_notify{};
constexpr UINT WM_SC_DATA = WM_APP + 60;
inline std::wstring Identity(const Entry& e) {
    return std::to_wstring(static_cast<int>(e.kind)) + L"|" + (e.machine ? L"M|" : L"U|") +
           std::to_wstring(e.view) + L"|" + e.source + L"|" + e.value;
}
// Part of Windows: a Microsoft file inside the Windows folder, or a task in Microsoft's own
// task folder. Third-party drivers in the driver store stay with the apps.
inline bool MicrosoftFile(const std::wstring& path) {
    static std::mutex lock;
    static std::map<std::wstring, bool> cache;
    std::wstring key = Lower(path);
    {
        std::lock_guard<std::mutex> g(lock);
        auto it = cache.find(key);
        if (it != cache.end()) return it->second;
    }
    bool ms = false;
    DWORD handle = 0, size = GetFileVersionInfoSizeW(path.c_str(), &handle);
    if (size && size < 4 * 1024 * 1024) {
        std::vector<BYTE> data(size);
        struct Lang { WORD lang, page; }* langs = nullptr;
        UINT len = 0;
        if (GetFileVersionInfoW(path.c_str(), 0, size, data.data()) &&
            VerQueryValueW(data.data(), L"\\VarFileInfo\\Translation", reinterpret_cast<void**>(&langs), &len) && len >= sizeof(Lang)) {
            wchar_t query[64];
            swprintf(query, 64, L"\\StringFileInfo\\%04x%04x\\CompanyName", langs->lang, langs->page);
            wchar_t* company = nullptr;
            UINT clen = 0;
            if (VerQueryValueW(data.data(), query, reinterpret_cast<void**>(&company), &clen) && clen && company)
                ms = wcsstr(company, L"Microsoft") != nullptr;
        }
    }
    std::lock_guard<std::mutex> g(lock);
    cache[key] = ms;
    return ms;
}
inline bool WindowsCatalog(const std::wstring& path) {
    static std::mutex lock;
    static std::map<std::wstring, bool> cache;
    static HCATADMIN admin = [] {
        HCATADMIN a = nullptr;
        if (!CryptCATAdminAcquireContext2(&a, nullptr, L"SHA256", nullptr, 0)) a = nullptr;
        return a;
    }();
    std::wstring key = Lower(path);
    std::lock_guard<std::mutex> g(lock);
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;
    bool windows = false;
    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                              nullptr, OPEN_EXISTING, 0, nullptr);
    if (admin && file != INVALID_HANDLE_VALUE) {
        DWORD size = 0;
        CryptCATAdminCalcHashFromFileHandle2(admin, file, &size, nullptr, 0);
        std::vector<BYTE> hash(size);
        if (size && CryptCATAdminCalcHashFromFileHandle2(admin, file, &size, hash.data(), 0)) {
            HCATINFO info = CryptCATAdminEnumCatalogFromHash(admin, hash.data(), size, 0, nullptr);
            if (info) {
                CATALOG_INFO ci{sizeof(ci)};
                if (CryptCATCatalogInfoFromContext(info, &ci, 0)) {
                    const wchar_t* name = wcsrchr(ci.wszCatalogFile, L'\\');
                    name = name ? name + 1 : ci.wszCatalogFile;
                    windows = _wcsnicmp(name, L"oem", 3) != 0;
                }
                CryptCATAdminReleaseCatalogContext(admin, info, 0);
            }
        }
    }
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    cache[key] = windows;
    return windows;
}
inline bool PartOfWindows(const Entry& e) {
    if (e.kind == Kind::Device) return false;
    if (e.kind == Kind::Task && Lower(e.source).rfind(L"\\microsoft\\", 0) == 0) return true;
    if (e.target.empty() || e.missing) return false;
    static const std::wstring windir = [] {
        wchar_t buf[MAX_PATH]{};
        GetWindowsDirectoryW(buf, MAX_PATH);
        return Lower(std::wstring(buf) + L"\\");
    }();
    std::wstring t = Lower(e.target);
    if (t.rfind(windir, 0) != 0) return false;
    if (t.find(L"\\driverstore\\") == t.npos && MicrosoftFile(e.target)) return true;
    return WindowsCatalog(e.target);
}
inline void Add(Inventory& inv, Entry e) {
    if (e.id.empty()) e.id = Identity(e);
    if (e.name.size() > 1 && e.name[0] == L'@') {
        wchar_t text[512]{};
        std::wstring ref = e.name, fallback;
        auto semi = ref.find(L';');
        if (semi != ref.npos) { fallback = ref.substr(semi + 1); ref = ref.substr(0, semi); }
        if (SUCCEEDED(SHLoadIndirectString(Expand(ref).c_str(), text, ARRAYSIZE(text), nullptr)) && *text) e.name = text;
        else e.name = !fallback.empty() ? fallback : (!e.value.empty() ? e.value : e.name);
    }
    // A task's command field holds its XML definition, never a file path.
    if (e.target.empty() && !e.command.empty() && e.kind != Kind::Task) e.target = Target(e.command);
    if (e.target.empty() && e.command.empty() && e.kind == Kind::Driver && !e.value.empty())
        e.target = Expand(L"%SystemRoot%\\System32\\drivers\\" + e.value + L".sys");
    if (e.target.size() > 1 && e.target.front() == L'"' && e.target.back() == L'"') e.target = e.target.substr(1, e.target.size() - 2);
    if (!e.target.empty() && e.target.find(L":\\") != e.target.npos)
        e.missing = GetFileAttributesW(e.target.c_str()) == INVALID_FILE_ATTRIBUTES;
    e.windows = PartOfWindows(e);
    inv.entries.push_back(std::move(e));
}
inline std::wstring State(const Entry& e) {
    std::wstring s = e.enabled ? L"On" : L"Off";
    if (e.missing) s += L" · File missing";
    if (!e.writable) s += L" · View only";
    return s;
}
}

namespace sc {
struct Location { const wchar_t* category; const wchar_t* key; bool recursive; };
const Location kLocations[] = {
    {L"Startup apps", L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", false},
    {L"Startup apps", L"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce", false},
    {L"Startup apps", L"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx", true},
    {L"Startup apps", L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run", false},
    {L"Startup apps", L"Software\\Microsoft\\Active Setup\\Installed Components", true},
    {L"Startup apps", L"Environment", false},
    {L"Explorer add-ons", L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ShellIconOverlayIdentifiers", true},
    {L"Explorer add-ons", L"Software\\Microsoft\\Windows\\CurrentVersion\\ShellServiceObjectDelayLoad", false},
    {L"Explorer add-ons", L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ShellExecuteHooks", false},
    {L"Explorer add-ons", L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\SharedTaskScheduler", false},
    {L"Explorer add-ons", L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ShellServiceObjects", true},
    {L"Explorer add-ons", L"Software\\Classes\\*\\shellex", true},
    {L"Explorer add-ons", L"Software\\Classes\\AllFileSystemObjects\\shellex", true},
    {L"Explorer add-ons", L"Software\\Classes\\Directory\\shellex", true},
    {L"Explorer add-ons", L"Software\\Classes\\Folder\\shellex", true},
    {L"Explorer add-ons", L"Software\\Classes\\Drive\\shellex", true},
    {L"Explorer add-ons", L"Software\\Classes\\Protocols\\Handler", true},
    {L"Explorer add-ons", L"Software\\Classes\\Protocols\\Filter", true},
    {L"Internet Explorer", L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Browser Helper Objects", true},
    {L"Internet Explorer", L"Software\\Microsoft\\Internet Explorer\\Toolbar", false},
    {L"Internet Explorer", L"Software\\Microsoft\\Internet Explorer\\Extensions", true},
    {L"Image hooks", L"Software\\Microsoft\\Command Processor", false},
    {L"Image hooks", L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options", true},
    {L"AppInit", L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows", false},
    {L"Sign-in security", L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", true},
    {L"Sign-in security", L"Software\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Providers", true},
    {L"Sign-in security", L"Software\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Provider Filters", true},
    {L"Sign-in security", L"Control Panel\\Desktop", false},
    {L"Codecs", L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Drivers32", false},
    {L"Codecs", L"Software\\Classes\\Filter", true},
    {L"Office", L"Software\\Microsoft\\Office\\Word\\Addins", true},
    {L"Office", L"Software\\Microsoft\\Office\\Excel\\Addins", true},
    {L"Office", L"Software\\Microsoft\\Office\\Outlook\\Addins", true},
    {L"Office", L"Software\\Microsoft\\Office\\PowerPoint\\Addins", true},
    {L"Office", L"Software\\Microsoft\\Office\\Access\\Addins", true},
    {L"Office", L"Software\\Microsoft\\Office\\OneNote\\Addins", true},
    {L"AMSI", L"Software\\Microsoft\\AMSI\\Providers", true},
    {L"Boot hooks", L"SYSTEM\\CurrentControlSet\\Control\\Session Manager", false},
    {L"Known DLLs", L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\KnownDLLs", false},
    {L"AppInit", L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\AppCertDlls", false},
    {L"Print providers", L"SYSTEM\\CurrentControlSet\\Control\\Print\\Monitors", true},
    {L"Print providers", L"SYSTEM\\CurrentControlSet\\Control\\Print\\Providers", true},
    {L"Security providers", L"SYSTEM\\CurrentControlSet\\Control\\Lsa", false},
    {L"Security providers", L"SYSTEM\\CurrentControlSet\\Control\\SecurityProviders", false},
    {L"Network providers", L"SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order", false},
};
inline bool Relevant(const std::wstring& key, const std::wstring& name) {
    auto k = Lower(key), n = Lower(name);
    if (k == L"environment") return n == L"userinitmprlogonscript";
    if (k.find(L"active setup\\installed components\\") != k.npos) return n == L"stubpath";
    if (k.ends_with(L"command processor")) return n == L"autorun";
    if (k.ends_with(L"currentversion\\windows")) return n == L"appinit_dlls" || n == L"loadappinit_dlls" || n == L"load" || n == L"run";
    if (k.ends_with(L"session manager")) return n == L"bootexecute" || n == L"execute" || n == L"s0initialcommand" || n == L"setupexecute";
    if (k.ends_with(L"control panel\\desktop")) return n == L"scrnsave.exe";
    if (k.find(L"image file execution options") != k.npos) return n == L"debugger" || n == L"globalflag";
    if (k.ends_with(L"control\\lsa")) return n == L"authentication packages" || n == L"notification packages" || n == L"security packages";
    return true;
}
void RegistryLocation(Inventory& inv, HKEY root, const std::wstring& key, const std::wstring& category,
                      DWORD view, int depth, bool disabled = false) {
    if (g_cancel || depth > 12) return;
    RegKey h;
    LONG status = RegOpenKeyExW(root, key.c_str(), 0, KEY_READ | view, &h.h);
    if (status != ERROR_SUCCESS) {
        if (status == ERROR_ACCESS_DENIED) inv.errors.push_back(L"Cannot read " + key + L": " + Error(status));
        return;
    }
    DWORD maxName = 0, maxBytes = 0, maxSub = 0;
    RegQueryInfoKeyW(h.h, nullptr, nullptr, nullptr, nullptr, &maxSub, nullptr, nullptr, &maxName, &maxBytes, nullptr, nullptr);
    if (maxBytes > 1024 * 1024 || maxName > 32768) { inv.errors.push_back(L"Registry value too large: " + key); return; }
    std::vector<wchar_t> name(maxName + 2);
    std::vector<BYTE> data(maxBytes + 4);
    for (DWORD i = 0; !g_cancel; ++i) {
        DWORD nc = static_cast<DWORD>(name.size()), bytes = static_cast<DWORD>(data.size()), type = 0;
        status = RegEnumValueW(h.h, i, name.data(), &nc, nullptr, &type, data.data(), &bytes);
        if (status == ERROR_NO_MORE_ITEMS) break;
        if (status != ERROR_SUCCESS) { inv.errors.push_back(L"Cannot enumerate " + key + L": " + Error(status)); break; }
        if (!Relevant(key, std::wstring(name.data(), nc))) continue;
        if (type != REG_SZ && type != REG_EXPAND_SZ && type != REG_MULTI_SZ && type != REG_DWORD) continue;
        Entry e;
        e.kind = Kind::Registry;
        e.machine = root == HKEY_LOCAL_MACHINE;
        e.key = key; e.value.assign(name.data(), nc); e.view = view; e.type = type;
        e.name = e.value.empty() ? std::filesystem::path(key).filename().wstring() + L" (default)" : e.value;
        if (Lower(e.value) == L"stubpath") {
            std::wstring title = TextValue(h.h, L"");
            e.name = title.empty() ? std::filesystem::path(key).filename().wstring() : title;
        }
        e.category = category;
        e.source = (e.machine ? L"HKLM\\" : L"HKCU\\") + key;
        e.raw.assign(data.begin(), data.begin() + bytes);
        e.command = TextValue(h.h, e.value.c_str());
        if (type == REG_DWORD && bytes == 4) e.detail = L"Value: " + std::to_wstring(*reinterpret_cast<DWORD*>(data.data()));
        e.disabledStore = disabled; e.enabled = !disabled;
        e.writable = category == L"Startup apps" && (Lower(key).ends_with(L"\\run") || Lower(key).ends_with(L"\\runonce") || disabled);
        if (e.writable && !disabled) {
            std::wstring approved = L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\";
            approved += view == KEY_WOW64_32KEY ? L"Run32" : L"Run";
            RegKey a;
            if (RegOpenKeyExW(root, approved.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &a.h) == ERROR_SUCCESS) {
                BYTE state[64]{}; DWORD st = 0, sz = sizeof(state);
                if (RegQueryValueExW(a.h, e.value.c_str(), nullptr, &st, state, &sz) == ERROR_SUCCESS && st == REG_BINARY && sz) {
                    if (state[0] == 3 || state[0] == 7) e.enabled = false;
                    else if (state[0] != 2 && state[0] != 6) { e.writable = false; e.detail += L" Unknown Windows approval state " + std::to_wstring(state[0]); }
                }
            }
        }
        Add(inv, std::move(e));
    }
    if (depth >= 0) {
        std::vector<wchar_t> sub(maxSub + 2);
        for (DWORD i = 0; !g_cancel; ++i) {
            DWORD n = static_cast<DWORD>(sub.size());
            status = RegEnumKeyExW(h.h, i, sub.data(), &n, nullptr, nullptr, nullptr, nullptr);
            if (status == ERROR_NO_MORE_ITEMS) break;
            if (status != ERROR_SUCCESS) break;
            std::wstring child(sub.data(), n);
            if (!disabled && child == L"AutorunsDisabled" && depth < 12) RegistryLocation(inv, root, key + L"\\" + child, category, view, 12, true);
            else if (depth < 12) RegistryLocation(inv, root, key + L"\\" + child, category, view, depth + 1, disabled);
        }
    }
}
void ScanRegistry(Inventory& inv) {
    for (auto& l : kLocations) for (HKEY root : {HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE}) {
        if (root == HKEY_CURRENT_USER && std::wstring(l.key).rfind(L"SYSTEM", 0) == 0) continue;
        for (DWORD view : {KEY_WOW64_64KEY, KEY_WOW64_32KEY}) {
            if (view == KEY_WOW64_32KEY && std::wstring(l.key).rfind(L"SYSTEM", 0) == 0) continue;
            if (g_cancel) return;
            RegistryLocation(inv, root, l.key, l.category, view, l.recursive ? 0 : 12);
            if (!l.recursive) RegistryLocation(inv, root, std::wstring(l.key) + L"\\AutorunsDisabled", l.category, view, 12, true);
        }
    }
}
}

namespace sc {
void ScanStartupFolder(Inventory& inv, const std::wstring& folder, bool machine, bool disabled = false) {
    WIN32_FIND_DATAW data{};
    HANDLE find = FindFirstFileW((folder + L"\\*").c_str(), &data);
    if (find == INVALID_HANDLE_VALUE) return;
    do {
        if (g_cancel) break;
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        if (_wcsicmp(data.cFileName, L"desktop.ini") == 0) continue;
        Entry e; e.kind = Kind::Shortcut; e.category = L"Startup apps"; e.machine = machine;
        e.name = data.cFileName; e.value = e.name; e.key = folder + L"\\" + e.name;
        e.source = e.key; e.target = e.key; e.writable = true; e.enabled = !disabled; e.disabledStore = disabled;
        if (Lower(e.name).ends_with(L".lnk")) {
            ComPtr<IShellLinkW> link; ComPtr<IPersistFile> file;
            if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&link))) &&
                SUCCEEDED(link.As(&file)) && SUCCEEDED(file->Load(e.key.c_str(), STGM_READ))) {
                wchar_t target[32768]{}, args[32768]{}, cwd[32768]{};
                link->GetPath(target, ARRAYSIZE(target), nullptr, SLGP_RAWPATH);
                link->GetArguments(args, ARRAYSIZE(args)); link->GetWorkingDirectory(cwd, ARRAYSIZE(cwd));
                e.target = Expand(target); e.command = L"\"" + e.target + L"\" " + args; e.detail = L"Working folder: " + std::wstring(cwd);
            }
        }
        if (!disabled) {
            RegKey approval;
            if (RegOpenKeyExW(machine ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER,
                L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\StartupFolder", 0, KEY_READ | KEY_WOW64_64KEY, &approval.h) == ERROR_SUCCESS) {
                BYTE state[64]{}; DWORD type = 0, bytes = sizeof(state);
                LONG status = RegQueryValueExW(approval.h, e.value.c_str(), nullptr, &type, state, &bytes);
                if (status == ERROR_SUCCESS && type == REG_BINARY && bytes >= 1) {
                    if (state[0] == 3 || state[0] == 7) e.enabled = false;
                    else if (state[0] != 2 && state[0] != 6) { e.writable = false; e.detail += L" Unknown approval state"; }
                }
            }
        }
        Add(inv, std::move(e));
    } while (FindNextFileW(find, &data));
    FindClose(find);
    if (!disabled) ScanStartupFolder(inv, folder + L"\\AutorunsDisabled", machine, true);
}
void ScanLogon(Inventory& inv) {
    for (auto id : {CSIDL_STARTUP, CSIDL_COMMON_STARTUP}) {
        wchar_t folder[MAX_PATH]{};
        if (SUCCEEDED(SHGetFolderPathW(nullptr, id, nullptr, SHGFP_TYPE_CURRENT, folder))) ScanStartupFolder(inv, folder, id == CSIDL_COMMON_STARTUP);
    }
}
HRESULT CreateStartupShortcut(const std::wstring& name, const std::wstring& target,
                              const std::wstring& arguments, const std::wstring& directory) {
    if (name.empty() || name.find_first_of(L"\\/:*?\"<>|") != name.npos) return E_INVALIDARG;
    wchar_t folder[MAX_PATH]{};
    HRESULT hr = SHGetFolderPathW(nullptr, CSIDL_STARTUP, nullptr, SHGFP_TYPE_CURRENT, folder);
    if (FAILED(hr)) return hr;
    std::wstring path = std::wstring(folder) + L"\\" + name + L".lnk";
    if (GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES) return HRESULT_FROM_WIN32(ERROR_FILE_EXISTS);
    ComPtr<IShellLinkW> link; ComPtr<IPersistFile> persist;
    hr = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&link));
    if (SUCCEEDED(hr)) hr = link->SetPath(target.c_str());
    if (SUCCEEDED(hr)) hr = link->SetArguments(arguments.c_str());
    if (SUCCEEDED(hr)) hr = link->SetWorkingDirectory(directory.c_str());
    if (SUCCEEDED(hr)) hr = link.As(&persist);
    if (SUCCEEDED(hr)) hr = persist->Save(path.c_str(), TRUE);
    return hr;
}
}

namespace sc {
struct TaskConnection {
    ComPtr<ITaskService> service;
    HRESULT status = E_FAIL;
    explicit TaskConnection(const std::wstring& server = L"") {
        status = CoCreateInstance(CLSID_TaskScheduler, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&service));
        if (FAILED(status)) return;
        VARIANT host{}, empty{};
        if (!server.empty()) { host.vt = VT_BSTR; host.bstrVal = SysAllocString(server.c_str()); }
        status = service->Connect(host, empty, empty, empty);
        VariantClear(&host);
    }
    ComPtr<ITaskFolder> Folder(const std::wstring& path) {
        ComPtr<ITaskFolder> f;
        if (SUCCEEDED(status)) service->GetFolder(BString(path), &f);
        return f;
    }
    ComPtr<IRegisteredTask> Task(const std::wstring& path) {
        auto pos = path.find_last_of(L'\\');
        auto f = Folder(pos == 0 || pos == path.npos ? L"\\" : path.substr(0, pos));
        ComPtr<IRegisteredTask> task;
        if (f) f->GetTask(BString(path.substr(pos == path.npos ? 0 : pos + 1)), &task);
        return task;
    }
};
inline std::wstring TaskXml(IRegisteredTask* task) {
    BSTR value = nullptr;
    HRESULT hr = task->get_Xml(&value);
    std::wstring xml = SUCCEEDED(hr) ? Bstr(value) : L"";
    SysFreeString(value);
    return xml;
}
inline std::wstring TaskSecurity(IRegisteredTask* task) {
    BSTR value = nullptr;
    HRESULT hr = task->GetSecurityDescriptor(OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, &value);
    auto result = SUCCEEDED(hr) ? Bstr(value) : L"";
    SysFreeString(value);
    return result;
}
inline std::wstring DateText(DATE value) {
    if (value <= 0) return L"Never";
    SYSTEMTIME st{};
    if (!VariantTimeToSystemTime(value, &st)) return L"Unknown";
    wchar_t b[64];
    swprintf_s(b, L"%04u-%02u-%02u %02u:%02u", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
    return b;
}
void TaskFolderScan(Inventory& inv, ITaskFolder* folder, unsigned depth = 0) {
    if (g_cancel || depth > 64) return;
    ComPtr<IRegisteredTaskCollection> tasks;
    HRESULT hr = folder->GetTasks(TASK_ENUM_HIDDEN, &tasks);
    if (FAILED(hr)) inv.errors.push_back(L"Task enumeration: " + Error(hr));
    LONG count = 0;
    if (tasks) tasks->get_Count(&count);
    for (LONG i = 1; i <= count && !g_cancel; ++i) {
        VARIANT index{}; index.vt = VT_I4; index.lVal = i;
        ComPtr<IRegisteredTask> task;
        if (FAILED(tasks->get_Item(index, &task))) continue;
        Entry e; e.kind = Kind::Task; e.category = L"Scheduled tasks"; e.writable = true;
        BSTR name = nullptr, path = nullptr;
        task->get_Name(&name); task->get_Path(&path);
        e.name = Bstr(name); e.source = Bstr(path); e.key = e.source;
        SysFreeString(name); SysFreeString(path);
        VARIANT_BOOL on = VARIANT_FALSE;
        task->get_Enabled(&on); e.enabled = on != VARIANT_FALSE;
        TASK_STATE state{}; DATE last = 0, next = 0; LONG result = 0, missed = 0;
        task->get_State(&state); task->get_LastRunTime(&last); task->get_NextRunTime(&next);
        task->get_LastTaskResult(&result); task->get_NumberOfMissedRuns(&missed);
        e.startMode = state;
        e.command = TaskXml(task.Get());
        e.detail = L"Last: " + DateText(last) + L"  Next: " + DateText(next) + L"  Result: " + Hex(result) +
                   L"  Missed: " + std::to_wstring(missed) + (state == TASK_STATE_RUNNING ? L"  Running" : L"");
        ComPtr<ITaskDefinition> definition;
        if (SUCCEEDED(task->get_Definition(&definition))) {
            ComPtr<IPrincipal> principal;
            if (SUCCEEDED(definition->get_Principal(&principal))) {
                BSTR user = nullptr; principal->get_UserId(&user); e.user = Bstr(user); SysFreeString(user);
            }
            ComPtr<IActionCollection> actions;
            if (SUCCEEDED(definition->get_Actions(&actions))) {
                LONG ac = 0; actions->get_Count(&ac);
                for (LONG a = 1; a <= ac; ++a) {
                    ComPtr<IAction> action; ComPtr<IExecAction> exec;
                    if (SUCCEEDED(actions->get_Item(a, &action)) && SUCCEEDED(action.As(&exec))) {
                        BSTR p = nullptr; exec->get_Path(&p);
                        if (e.target.empty()) e.target = Target(Expand(Bstr(p)));
                        SysFreeString(p);
                    }
                }
            }
        }
        Add(inv, std::move(e));
    }
    ComPtr<ITaskFolderCollection> children;
    hr = folder->GetFolders(0, &children);
    if (FAILED(hr)) { inv.errors.push_back(L"Task folders: " + Error(hr)); return; }
    count = 0; children->get_Count(&count);
    for (LONG i = 1; i <= count && !g_cancel; ++i) {
        VARIANT index{}; index.vt = VT_I4; index.lVal = i;
        ComPtr<ITaskFolder> child;
        if (SUCCEEDED(children->get_Item(index, &child))) TaskFolderScan(inv, child.Get(), depth + 1);
    }
}
void ScanTasks(Inventory& inv) {
    TaskConnection c;
    auto root = c.Folder(L"\\");
    if (!root) { inv.errors.push_back(L"Task Scheduler: " + Error(c.status)); return; }
    TaskFolderScan(inv, root.Get());
}
HRESULT RegisterXml(const std::wstring& path, const std::wstring& xml, bool validate,
                    bool update, const std::wstring& security = L"") {
    TaskConnection connection;
    if (FAILED(connection.status)) return connection.status;
    ComPtr<ITaskDefinition> definition;
    HRESULT hr = connection.service->NewTask(0, &definition);
    if (FAILED(hr)) return hr;
    hr = definition->put_XmlText(BString(xml));
    if (FAILED(hr)) return hr;
    ComPtr<IPrincipal> principal;
    hr = definition->get_Principal(&principal);
    if (FAILED(hr)) return hr;
    TASK_LOGON_TYPE logon{};
    hr = principal->get_LogonType(&logon);
    if (FAILED(hr)) return hr;
    // Windows cannot export the password needed to update these definitions.
    if (logon == TASK_LOGON_PASSWORD || logon == TASK_LOGON_INTERACTIVE_TOKEN_OR_PASSWORD) return HRESULT_FROM_WIN32(ERROR_LOGON_FAILURE);
    auto pos = path.find_last_of(L'\\');
    auto folder = connection.Folder(pos == 0 || pos == path.npos ? L"\\" : path.substr(0, pos));
    if (!folder) return HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND);
    VARIANT user{}, password{}, sddl{};
    BSTR account = nullptr;
    hr = logon == TASK_LOGON_GROUP ? principal->get_GroupId(&account) : principal->get_UserId(&account);
    if (FAILED(hr)) return hr;
    if (account && SysStringLen(account)) { user.vt = VT_BSTR; user.bstrVal = account; }
    else SysFreeString(account);
    if (!security.empty()) { sddl.vt = VT_BSTR; sddl.bstrVal = SysAllocString(security.c_str()); }
    ComPtr<IRegisteredTask> registered;
    LONG flags = validate ? TASK_VALIDATE_ONLY : (update ? TASK_UPDATE : TASK_CREATE) | TASK_IGNORE_REGISTRATION_TRIGGERS;
    hr = folder->RegisterTaskDefinition(BString(path.substr(pos == path.npos ? 0 : pos + 1)), definition.Get(), flags,
                                        user, password, logon, sddl, &registered);
    VariantClear(&user); VariantClear(&sddl);
    return hr;
}
inline std::wstring BasicTaskXml(const std::wstring& executable, const std::wstring& arguments,
                                 const std::wstring& directory, bool boot) {
    return L"<?xml version=\"1.0\" encoding=\"UTF-16\"?>"
           L"<Task version=\"1.2\" xmlns=\"http://schemas.microsoft.com/windows/2004/02/mit/task\">"
           L"<RegistrationInfo><Description>Created in Startup Control</Description></RegistrationInfo>"
           L"<Triggers>" + std::wstring(boot ? L"<BootTrigger><Enabled>true</Enabled></BootTrigger>" :
           L"<LogonTrigger><Enabled>true</Enabled></LogonTrigger>") + L"</Triggers>"
           L"<Principals><Principal id=\"Owner\"><LogonType>InteractiveToken</LogonType><RunLevel>LeastPrivilege</RunLevel></Principal></Principals>"
           L"<Settings><MultipleInstancesPolicy>IgnoreNew</MultipleInstancesPolicy><DisallowStartIfOnBatteries>false</DisallowStartIfOnBatteries>"
           L"<StopIfGoingOnBatteries>false</StopIfGoingOnBatteries><ExecutionTimeLimit>PT0S</ExecutionTimeLimit></Settings>"
           L"<Actions Context=\"Owner\"><Exec><Command>" + XmlEscape(executable) + L"</Command><Arguments>" + XmlEscape(arguments) +
           L"</Arguments><WorkingDirectory>" + XmlEscape(directory) + L"</WorkingDirectory></Exec></Actions></Task>";
}
std::wstring TaskHistory(const std::wstring& path) {
    // Filter TaskName in code so a task name cannot inject XPath syntax.
    EVT_HANDLE query = EvtQuery(nullptr, L"Microsoft-Windows-TaskScheduler/Operational", L"*", EvtQueryChannelPath | EvtQueryReverseDirection);
    if (!query) return L"History unavailable: " + Error(GetLastError());
    std::wstring out; unsigned examined = 0, matched = 0;
    while (examined < 1000 && matched < 50 && !g_cancel) {
        EVT_HANDLE event = nullptr; DWORD returned = 0;
        if (!EvtNext(query, 1, &event, 200, 0, &returned)) break;
        ++examined; DWORD bytes = 0, count = 0;
        EvtRender(nullptr, event, EvtRenderEventXml, 0, nullptr, &bytes, &count);
        if (bytes && bytes <= 1024 * 1024) {
            std::vector<wchar_t> b(bytes / 2 + 1);
            if (EvtRender(nullptr, event, EvtRenderEventXml, bytes, b.data(), &bytes, &count)) {
                std::wstring xml = b.data();
                if (xml.find(L">" + XmlEscape(path) + L"</Data>") != xml.npos) { out += xml + L"\r\n\r\n"; ++matched; }
            }
        }
        EvtClose(event);
    }
    EvtClose(query);
    return out.empty() ? L"No matching events among the newest 1,000 records. History may have been cleared or disabled." : out;
}
}

namespace sc {
void ScanServices(Inventory& inv) {
    ServiceHandle manager(OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ENUMERATE_SERVICE));
    if (!manager.h) { inv.errors.push_back(L"Services: " + Error(GetLastError())); return; }
    DWORD needed = 0, count = 0, resume = 0;
    EnumServicesStatusExW(manager, SC_ENUM_PROCESS_INFO, SERVICE_WIN32 | SERVICE_DRIVER, SERVICE_STATE_ALL, nullptr, 0, &needed, &count, &resume, nullptr);
    if (needed > 16 * 1024 * 1024) { inv.errors.push_back(L"Service inventory exceeds the safety limit."); return; }
    std::vector<BYTE> buffer(needed + 65536);
    resume = 0;
    if (!EnumServicesStatusExW(manager, SC_ENUM_PROCESS_INFO, SERVICE_WIN32 | SERVICE_DRIVER, SERVICE_STATE_ALL,
                               buffer.data(), static_cast<DWORD>(buffer.size()), &needed, &count, &resume, nullptr)) {
        inv.errors.push_back(L"Service inventory: " + Error(GetLastError())); return;
    }
    auto records = reinterpret_cast<ENUM_SERVICE_STATUS_PROCESSW*>(buffer.data());
    for (DWORD i = 0; i < count && !g_cancel; ++i) {
        auto& record = records[i];
        ServiceHandle service(OpenServiceW(manager, record.lpServiceName, SERVICE_QUERY_CONFIG));
        if (!service.h) {
            DWORD error = GetLastError();
            // Protected services refuse a config query; their registry key still says how they start.
            if (error != ERROR_ACCESS_DENIED) { inv.errors.push_back(std::wstring(record.lpServiceName) + L": " + Error(error)); continue; }
            RegKey key;
            bool readable = RegOpenKeyExW(HKEY_LOCAL_MACHINE, (L"SYSTEM\\CurrentControlSet\\Services\\" + std::wstring(record.lpServiceName)).c_str(),
                                          0, KEY_QUERY_VALUE, &key.h) == ERROR_SUCCESS;
            DWORD start = readable ? 3 : 99, type = record.ServiceStatusProcess.dwServiceType, size = sizeof(DWORD);
            if (readable) RegQueryValueExW(key.h, L"Start", nullptr, nullptr, reinterpret_cast<BYTE*>(&start), &size); size = sizeof(DWORD);
            if (readable) RegQueryValueExW(key.h, L"Type", nullptr, nullptr, reinterpret_cast<BYTE*>(&type), &size);
            Entry e; bool driver = (type & SERVICE_DRIVER) != 0;
            e.kind = driver ? Kind::Driver : Kind::Service; e.category = driver ? L"Drivers" : L"Services";
            e.machine = true; e.name = record.lpDisplayName; e.value = record.lpServiceName;
            e.source = L"Service\\" + e.value; e.key = e.value;
            if (readable) { e.command = TextValue(key.h, L"ImagePath"); e.user = TextValue(key.h, L"ObjectName"); }
            e.startMode = start; e.enabled = start != SERVICE_DISABLED; e.writable = false;
            e.detail = std::wstring(record.ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING ? L"Running" : L"Stopped") + L". Windows protects this service.";
            Add(inv, std::move(e)); continue;
        }
        DWORD bytes = 0;
        QueryServiceConfigW(service, nullptr, 0, &bytes);
        if (!bytes || bytes > 1024 * 1024) continue;
        std::vector<BYTE> config(bytes);
        if (!QueryServiceConfigW(service, reinterpret_cast<QUERY_SERVICE_CONFIGW*>(config.data()), bytes, &bytes)) continue;
        auto c = reinterpret_cast<QUERY_SERVICE_CONFIGW*>(config.data());
        Entry e; bool driver = (c->dwServiceType & SERVICE_DRIVER) != 0;
        e.kind = driver ? Kind::Driver : Kind::Service; e.category = driver ? L"Drivers" : L"Services";
        e.machine = true; e.name = record.lpDisplayName; e.value = record.lpServiceName;
        e.source = L"Service\\" + e.value; e.key = e.value;
        e.command = c->lpBinaryPathName ? c->lpBinaryPathName : L"";
        e.startMode = c->dwStartType; e.enabled = c->dwStartType != SERVICE_DISABLED;
        e.writable = true; e.user = c->lpServiceStartName ? c->lpServiceStartName : L"";
        e.detail = record.ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING ? L"Running" : L"Stopped";
        SERVICE_DELAYED_AUTO_START_INFO delayed{};
        if (QueryServiceConfig2W(service, SERVICE_CONFIG_DELAYED_AUTO_START_INFO, reinterpret_cast<BYTE*>(&delayed), sizeof(delayed), &bytes) && delayed.fDelayedAutostart)
            e.detail += L", starts a little after sign-in";
        if (c->lpDependencies) for (auto p = c->lpDependencies; *p; p += wcslen(p) + 1) e.detail += L"\nNeeds: " + std::wstring(p);
        if (!driver && Lower(e.command).find(L"svchost") != e.command.npos) {
            RegKey params;
            if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, (L"SYSTEM\\CurrentControlSet\\Services\\" + e.value + L"\\Parameters").c_str(), 0, KEY_READ, &params.h) == ERROR_SUCCESS)
                e.target = Expand(TextValue(params.h, L"ServiceDll"));
        }
        Add(inv, std::move(e));
    }
}
void ScanDevices(Inventory& inv) {
    HDEVINFO devices = SetupDiGetClassDevsW(nullptr, nullptr, nullptr, DIGCF_ALLCLASSES);
    if (devices == INVALID_HANDLE_VALUE) { inv.errors.push_back(L"Devices: " + Error(GetLastError())); return; }
    for (DWORD i = 0; !g_cancel; ++i) {
        SP_DEVINFO_DATA data{sizeof(data)};
        if (!SetupDiEnumDeviceInfo(devices, i, &data)) break;
        wchar_t id[4096]{}, name[4096]{}; DWORD type = 0;
        if (!SetupDiGetDeviceInstanceIdW(devices, &data, id, ARRAYSIZE(id), nullptr)) continue;
        if (!SetupDiGetDeviceRegistryPropertyW(devices, &data, SPDRP_FRIENDLYNAME, &type, reinterpret_cast<BYTE*>(name), sizeof(name), nullptr))
            SetupDiGetDeviceRegistryPropertyW(devices, &data, SPDRP_DEVICEDESC, &type, reinterpret_cast<BYTE*>(name), sizeof(name), nullptr);
        ULONG status = 0, problem = 0;
        CONFIGRET result = CM_Get_DevNode_Status(&status, &problem, data.DevInst, 0);
        Entry e; e.kind = Kind::Device; e.category = L"Devices"; e.machine = true;
        e.value = id; e.key = id; e.name = *name ? name : id; e.source = L"Device\\" + e.value;
        e.enabled = problem != CM_PROB_DISABLED; e.writable = result == CR_SUCCESS;
        e.detail = result == CR_SUCCESS ? (L"Problem code: " + std::to_wstring(problem)) : L"Disconnected or status unavailable";
        Add(inv, std::move(e));
    }
    SetupDiDestroyDeviceInfoList(devices);
}
}

namespace sc {
inline std::wstring WmiText(IWbemClassObject* object, PCWSTR property) {
    VARIANT value{};
    HRESULT hr = object->Get(property, 0, &value, nullptr, nullptr);
    std::wstring result = SUCCEEDED(hr) && value.vt == VT_BSTR ? Bstr(value.bstrVal) : L"";
    VariantClear(&value); return result;
}
void ScanWmi(Inventory& inventory) {
    ComPtr<IWbemLocator> locator;
    HRESULT hr = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&locator));
    ComPtr<IWbemServices> services;
    if (SUCCEEDED(hr)) hr = locator->ConnectServer(BString(L"ROOT\\subscription"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &services);
    if (SUCCEEDED(hr)) hr = CoSetProxyBlanket(services.Get(), RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
                                             RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
    if (FAILED(hr)) { inventory.errors.push_back(L"WMI subscriptions: " + Error(hr)); return; }
    for (PCWSTR className : {L"__EventFilter", L"CommandLineEventConsumer", L"ActiveScriptEventConsumer", L"__FilterToConsumerBinding"}) {
        ComPtr<IEnumWbemClassObject> enumeration;
        hr = services->CreateInstanceEnum(BString(className), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &enumeration);
        if (FAILED(hr)) { inventory.errors.push_back(std::wstring(L"WMI ") + className + L": " + Error(hr)); continue; }
        unsigned count = 0;
        while (!g_cancel && count < 10000) {
            ComPtr<IWbemClassObject> object; ULONG returned = 0;
            hr = enumeration->Next(500, 1, &object, &returned);
            if (hr == WBEM_S_TIMEDOUT) { inventory.errors.push_back(L"WMI enumeration timed out; results are partial."); break; }
            if (FAILED(hr)) { inventory.errors.push_back(L"WMI enumeration: " + Error(hr)); break; }
            if (!returned) break;
            ++count;
            Entry e; e.kind = Kind::Wmi; e.machine = true; e.category = L"WMI subscriptions";
            e.name = WmiText(object.Get(), L"Name"); e.source = WmiText(object.Get(), L"__RELPATH");
            if (e.name.empty()) e.name = e.source;
            e.key = e.source; e.command = WmiText(object.Get(), L"CommandLineTemplate");
            e.target = WmiText(object.Get(), L"ExecutablePath");
            e.detail = std::wstring(className) + L"\r\n" + WmiText(object.Get(), L"Query") + L"\r\n" +
                       WmiText(object.Get(), L"ScriptText") + L"\r\nFilter: " + WmiText(object.Get(), L"Filter") +
                       L"\r\nConsumer: " + WmiText(object.Get(), L"Consumer");
            e.writable = false;
            Add(inventory, std::move(e));
        }
        if (count == 10000) inventory.errors.push_back(L"WMI inventory reached its limit; results are partial.");
    }
}
}

namespace sc {
struct FileHandle {
    HANDLE h = INVALID_HANDLE_VALUE;
    explicit FileHandle(HANDLE value) : h(value) {}
    FileHandle(const FileHandle&) = delete;
    ~FileHandle() { if (h != INVALID_HANDLE_VALUE) CloseHandle(h); }
};
struct Archive {
    std::vector<BYTE> bytes;
    size_t offset = 0;
    bool valid = true;
    void Put(DWORD n) {
        for (unsigned i = 0; i != 4; ++i) bytes.push_back(static_cast<BYTE>(n >> (i * 8)));
    }
    DWORD Get() {
        if (offset > bytes.size() || bytes.size() - offset < 4) { valid = false; return 0; }
        DWORD n = 0;
        for (unsigned i = 0; i != 4; ++i) n |= DWORD(bytes[offset++]) << (i * 8);
        return n;
    }
    void Blob(const std::vector<BYTE>& v) {
        if (v.size() > 16 * 1024 * 1024) { valid = false; return; }
        Put(static_cast<DWORD>(v.size())); bytes.insert(bytes.end(), v.begin(), v.end());
    }
    std::vector<BYTE> Blob() {
        DWORD n = Get();
        if (!valid || n > 16 * 1024 * 1024 || offset > bytes.size() || n > bytes.size() - offset) { valid = false; return {}; }
        std::vector<BYTE> v(bytes.begin() + offset, bytes.begin() + offset + n); offset += n; return v;
    }
    void Text(const std::wstring& s) {
        auto p = reinterpret_cast<const BYTE*>(s.data());
        Blob(std::vector<BYTE>(p, p + s.size() * sizeof(wchar_t)));
    }
    std::wstring Text() {
        auto v = Blob();
        if (v.size() % sizeof(wchar_t)) { valid = false; return {}; }
        std::wstring s(v.size() / sizeof(wchar_t), 0);
        if (!v.empty()) memcpy(s.data(), v.data(), v.size());
        return s;
    }
};
HRESULT AtomicFile(const std::wstring& path, const std::vector<BYTE>& bytes, bool replace = true) {
    GUID id{};
    HRESULT hr = CoCreateGuid(&id);
    if (FAILED(hr)) return hr;
    wchar_t guid[40]{}; StringFromGUID2(id, guid, ARRAYSIZE(guid));
    auto temp = path + L"." + guid + L".tmp";
    DWORD failure = ERROR_SUCCESS;
    {
        FileHandle f(CreateFileW(temp.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr));
        if (f.h == INVALID_HANDLE_VALUE) return HRESULT_FROM_WIN32(GetLastError());
        DWORD written = 0;
        if (bytes.size() > MAXDWORD) failure = ERROR_FILE_TOO_LARGE;
        else if (!WriteFile(f.h, bytes.data(), static_cast<DWORD>(bytes.size()), &written, nullptr) || written != bytes.size()) failure = GetLastError() ? GetLastError() : ERROR_WRITE_FAULT;
        else if (!FlushFileBuffers(f.h)) failure = GetLastError();
    }
    if (failure == ERROR_SUCCESS && !MoveFileExW(temp.c_str(), path.c_str(), MOVEFILE_WRITE_THROUGH | (replace ? MOVEFILE_REPLACE_EXISTING : 0))) failure = GetLastError();
    if (failure != ERROR_SUCCESS) DeleteFileW(temp.c_str());
    return HRESULT_FROM_WIN32(failure);
}
HRESULT ReadFileBytes(const std::wstring& path, std::vector<BYTE>& bytes) {
    FileHandle f(CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));
    if (f.h == INVALID_HANDLE_VALUE) return HRESULT_FROM_WIN32(GetLastError());
    LARGE_INTEGER size{};
    if (!GetFileSizeEx(f.h, &size)) return HRESULT_FROM_WIN32(GetLastError());
    if (size.QuadPart < 0 || size.QuadPart > 64 * 1024 * 1024) return HRESULT_FROM_WIN32(ERROR_FILE_TOO_LARGE);
    bytes.resize(static_cast<size_t>(size.QuadPart)); DWORD read = 0;
    if (!ReadFile(f.h, bytes.data(), static_cast<DWORD>(bytes.size()), &read, nullptr)) return HRESULT_FROM_WIN32(GetLastError());
    return read == bytes.size() ? S_OK : HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
}
struct Change {
    std::wstring path, operation, subject, location, value;
    bool machine = false;
    DWORD view = 0, beforeType = 0, afterType = 0;
    bool beforeExists = false, afterExists = false;
    std::vector<BYTE> before, after;
    // A prepared record survives failure between the native write and its receipt.
    DWORD phase = 0;
};
Archive EncodeChange(const Change& c) {
    Archive a; a.Put(0x53434348); a.Put(1); a.Put(c.phase);
    a.Text(c.operation); a.Text(c.subject); a.Text(c.location); a.Text(c.value);
    a.Put(c.machine); a.Put(c.view); a.Put(c.beforeType); a.Put(c.afterType);
    a.Put(c.beforeExists); a.Put(c.afterExists); a.Blob(c.before); a.Blob(c.after); return a;
}
HRESULT StoreChange(Change& c) {
    if (c.path.empty()) {
        auto root = DataRoot();
        if (root.empty()) return E_FAIL;
        root += L"\\Changes";
        if (!CreateDirectoryW(root.c_str(), nullptr) && GetLastError() != ERROR_ALREADY_EXISTS) return HRESULT_FROM_WIN32(GetLastError());
        GUID id{}; HRESULT hr = CoCreateGuid(&id); if (FAILED(hr)) return hr;
        wchar_t guid[40]{}; StringFromGUID2(id, guid, ARRAYSIZE(guid));
        c.path = root + L"\\" + guid + L".scchange";
    }
    auto a = EncodeChange(c);
    return a.valid ? AtomicFile(c.path, a.bytes) : E_INVALIDARG;
}
HRESULT LoadChange(const std::wstring& path, Change& c) {
    Archive a; HRESULT hr = ReadFileBytes(path, a.bytes); if (FAILED(hr)) return hr;
    if (a.Get() != 0x53434348 || a.Get() != 1) return E_INVALIDARG;
    c.path = path; c.phase = a.Get(); c.operation = a.Text(); c.subject = a.Text();
    c.location = a.Text(); c.value = a.Text(); c.machine = a.Get() != 0;
    c.view = a.Get(); c.beforeType = a.Get(); c.afterType = a.Get();
    c.beforeExists = a.Get() != 0; c.afterExists = a.Get() != 0; c.before = a.Blob(); c.after = a.Blob();
    return a.valid && a.offset == a.bytes.size() && c.phase <= 2 ? S_OK : E_INVALIDARG;
}
struct RegValue {
    bool exists = false;
    DWORD type = 0;
    std::vector<BYTE> bytes;
    bool operator==(const RegValue& other) const { return exists == other.exists && (!exists || (type == other.type && bytes == other.bytes)); }
};
HRESULT ReadValue(bool machine, const std::wstring& key, const std::wstring& name, DWORD view, RegValue& value) {
    value = {}; RegKey h;
    LONG status = RegOpenKeyExW(machine ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER, key.c_str(), 0, KEY_QUERY_VALUE | view, &h.h);
    if (status == ERROR_FILE_NOT_FOUND) return S_OK;
    if (status != ERROR_SUCCESS) return HRESULT_FROM_WIN32(status);
    DWORD size = 0;
    status = RegQueryValueExW(h.h, name.c_str(), nullptr, &value.type, nullptr, &size);
    if (status == ERROR_FILE_NOT_FOUND) return S_OK;
    if (status != ERROR_SUCCESS) return HRESULT_FROM_WIN32(status);
    if (size > 16 * 1024 * 1024) return HRESULT_FROM_WIN32(ERROR_FILE_TOO_LARGE);
    value.bytes.resize(size);
    status = RegQueryValueExW(h.h, name.c_str(), nullptr, &value.type, value.bytes.data(), &size);
    if (status != ERROR_SUCCESS) return HRESULT_FROM_WIN32(status);
    value.bytes.resize(size); value.exists = true; return S_OK;
}
HRESULT WriteValue(bool machine, const std::wstring& key, const std::wstring& name, DWORD view, const RegValue& value) {
    RegKey h;
    LONG status = RegCreateKeyExW(machine ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER, key.c_str(), 0, nullptr, 0, KEY_SET_VALUE | view, nullptr, &h.h, nullptr);
    if (status != ERROR_SUCCESS) return HRESULT_FROM_WIN32(status);
    if (value.exists) status = RegSetValueExW(h.h, name.c_str(), 0, value.type, value.bytes.data(), static_cast<DWORD>(value.bytes.size()));
    else { status = RegDeleteValueW(h.h, name.c_str()); if (status == ERROR_FILE_NOT_FOUND) status = ERROR_SUCCESS; }
    if (status == ERROR_SUCCESS) status = RegFlushKey(h.h);
    return HRESULT_FROM_WIN32(status);
}
HRESULT ChangeValue(const std::wstring& subject, bool machine, const std::wstring& key, const std::wstring& name,
                    DWORD view, const RegValue& expected, const RegValue& desired, std::wstring& receipt) {
    RegValue current;
    HRESULT hr = ReadValue(machine, key, name, view, current);
    if (FAILED(hr)) return hr;
    if (!(current == expected)) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    if (current == desired) return S_FALSE;
    Change c; c.operation = L"Registry value"; c.subject = subject; c.machine = machine;
    c.location = key; c.value = name; c.view = view;
    c.beforeExists = current.exists; c.beforeType = current.type; c.before = current.bytes;
    c.afterExists = desired.exists; c.afterType = desired.type; c.after = desired.bytes;
    hr = StoreChange(c); if (FAILED(hr)) return hr;
    receipt = c.path;
    hr = WriteValue(machine, key, name, view, desired); if (FAILED(hr)) return hr;
    RegValue actual; hr = ReadValue(machine, key, name, view, actual);
    if (FAILED(hr)) return hr;
    if (!(actual == desired)) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    c.phase = 1; return StoreChange(c);
}
HRESULT UndoValue(const std::wstring& receipt) {
    Change c; HRESULT hr = LoadChange(receipt, c); if (FAILED(hr)) return hr;
    if (c.operation != L"Registry value" || c.phase == 2) return E_INVALIDARG;
    RegValue before{c.beforeExists, c.beforeType, c.before}, after{c.afterExists, c.afterType, c.after}, current;
    hr = ReadValue(c.machine, c.location, c.value, c.view, current); if (FAILED(hr)) return hr;
    if (current == before && c.phase == 0) { c.phase = 2; return StoreChange(c); }
    if (!(current == after)) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    hr = WriteValue(c.machine, c.location, c.value, c.view, before); if (FAILED(hr)) return hr;
    hr = ReadValue(c.machine, c.location, c.value, c.view, current); if (FAILED(hr)) return hr;
    if (!(current == before)) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    c.phase = 2; return StoreChange(c);
}
}

namespace sc {
void EncodeEntry(Archive& a, const Entry& e) {
    a.Put(static_cast<DWORD>(e.kind));
    for (const auto* text : {&e.id, &e.name, &e.category, &e.source, &e.command, &e.target, &e.detail, &e.key, &e.value, &e.user}) a.Text(*text);
    a.Put(e.view); a.Put(e.type); a.Put(e.machine); a.Put(e.enabled); a.Put(e.writable);
    a.Put(e.missing); a.Put(e.disabledStore); a.Put(e.startMode); a.Blob(e.raw);
}
Entry DecodeEntry(Archive& a) {
    Entry e; DWORD kind = a.Get();
    if (kind > static_cast<DWORD>(Kind::Notice)) a.valid = false;
    e.kind = static_cast<Kind>(kind);
    for (auto* text : {&e.id, &e.name, &e.category, &e.source, &e.command, &e.target, &e.detail, &e.key, &e.value, &e.user}) *text = a.Text();
    e.view = a.Get(); e.type = a.Get(); e.machine = a.Get() != 0; e.enabled = a.Get() != 0;
    e.writable = a.Get() != 0; e.missing = a.Get() != 0; e.disabledStore = a.Get() != 0;
    e.startMode = a.Get(); e.raw = a.Blob(); return e;
}
HRESULT SaveSnapshot(const std::wstring& path, const Inventory& inventory) {
    if (inventory.entries.size() > 100000 || inventory.errors.size() > 100000) return E_INVALIDARG;
    Archive a; a.Put(0x5343534E); a.Put(1);
    a.Put(static_cast<DWORD>(inventory.entries.size()));
    for (const auto& entry : inventory.entries) EncodeEntry(a, entry);
    a.Put(static_cast<DWORD>(inventory.errors.size()));
    for (const auto& error : inventory.errors) a.Text(error);
    if (!a.valid || a.bytes.size() > 64 * 1024 * 1024) return HRESULT_FROM_WIN32(ERROR_FILE_TOO_LARGE);
    return AtomicFile(path, a.bytes);
}
HRESULT LoadSnapshot(const std::wstring& path, Inventory& inventory) {
    Archive a; HRESULT hr = ReadFileBytes(path, a.bytes); if (FAILED(hr)) return hr;
    if (a.Get() != 0x5343534E || a.Get() != 1) return E_INVALIDARG;
    Inventory loaded;
    DWORD count = a.Get(); if (count > 100000) return E_INVALIDARG;
    for (DWORD i = 0; i < count && a.valid; ++i) loaded.entries.push_back(DecodeEntry(a));
    count = a.Get(); if (count > 100000) return E_INVALIDARG;
    for (DWORD i = 0; i < count && a.valid; ++i) loaded.errors.push_back(a.Text());
    if (!a.valid || a.offset != a.bytes.size()) return E_INVALIDARG;
    inventory = std::move(loaded); return S_OK;
}
struct Difference { std::wstring state; Entry before, after; };
std::vector<Difference> CompareSnapshots(const Inventory& before, const Inventory& after) {
    std::map<std::wstring, Entry> previous, current;
    for (const auto& e : before.entries) previous[e.id] = e;
    for (const auto& e : after.entries) current[e.id] = e;
    std::vector<Difference> result;
    for (const auto& [id, e] : previous) {
        auto it = current.find(id);
        if (it == current.end()) result.push_back({L"Removed", e, {}});
        else {
            const auto& now = it->second;
            if (e.enabled != now.enabled || e.command != now.command || e.raw != now.raw || e.startMode != now.startMode || e.target != now.target || e.type != now.type)
                result.push_back({L"Changed", e, now});
        }
    }
    for (const auto& [id, e] : current) if (!previous.contains(id)) result.push_back({L"Added", {}, e});
    return result;
}
}

namespace sc {
// Runs a built-in Windows tool with admin rights, hidden, and waits for it. Used only when a
// direct call was refused for lack of rights; every caller reads the result back afterwards.
HRESULT RunElevated(const std::wstring& exe, const std::wstring& params, DWORD timeout = 60000) {
    SHELLEXECUTEINFOW info{sizeof(info)};
    info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI | SEE_MASK_NOASYNC;
    info.lpVerb = Elevated() ? L"open" : L"runas";
    info.lpFile = exe.c_str();
    info.lpParameters = params.c_str();
    info.nShow = SW_HIDE;
    if (!ShellExecuteExW(&info)) return HRESULT_FROM_WIN32(GetLastError());
    if (!info.hProcess) return E_FAIL;
    DWORD wait = WaitForSingleObject(info.hProcess, timeout), code = 0;
    if (wait != WAIT_OBJECT_0) { CloseHandle(info.hProcess); return HRESULT_FROM_WIN32(ERROR_TIMEOUT); }
    GetExitCodeProcess(info.hProcess, &code);
    CloseHandle(info.hProcess);
    return code == 0 || code == 3010 ? S_OK : HRESULT_FROM_WIN32(code);
}
inline std::wstring SystemTool(PCWSTR name) { return Expand(L"%SystemRoot%\\System32\\") + name; }
HRESULT BrokerServiceMode(const std::wstring& name, DWORD mode) {
    static const PCWSTR modes[] = {L"boot", L"system", L"auto", L"demand", L"disabled"};
    if (mode > 4 || name.find(L'"') != name.npos) return E_INVALIDARG;
    return RunElevated(SystemTool(L"sc.exe"), L"config \"" + name + L"\" start= " + modes[mode]);
}
HRESULT BrokerDeviceState(const std::wstring& id, bool enabled) {
    if (id.find(L'"') != id.npos) return E_INVALIDARG;
    return RunElevated(SystemTool(L"pnputil.exe"), std::wstring(enabled ? L"/enable-device" : L"/disable-device") + L" \"" + id + L"\"");
}
inline bool Denied(HRESULT hr) { return hr == E_ACCESSDENIED || hr == HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED); }
}

namespace sc {
std::mutex g_changeMutex;
inline std::vector<BYTE> TextBytes(const std::wstring& text) {
    auto first = reinterpret_cast<const BYTE*>(text.data());
    return {first, first + text.size() * sizeof(wchar_t)};
}
inline std::wstring BytesText(const std::vector<BYTE>& bytes) {
    if (bytes.size() % sizeof(wchar_t)) return {};
    std::wstring text(bytes.size() / sizeof(wchar_t), 0);
    if (!bytes.empty()) memcpy(text.data(), bytes.data(), bytes.size());
    return text;
}
HRESULT ApprovalToggle(const Entry& e, bool enabled, std::wstring& receipt) {
    if (!e.writable || e.disabledStore || (e.kind != Kind::Registry && e.kind != Kind::Shortcut)) return E_ACCESSDENIED;
    std::wstring suffix;
    if (e.kind == Kind::Shortcut) suffix = L"StartupFolder";
    else if (Lower(e.key).ends_with(L"\\run")) suffix = e.view == KEY_WOW64_32KEY ? L"Run32" : L"Run";
    else return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
    const std::wstring location = L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\" + suffix;
    RegValue current;
    HRESULT hr = ReadValue(e.machine, location, e.value, KEY_WOW64_64KEY, current);
    if (FAILED(hr)) return hr;
    bool now = true;
    if (current.exists) {
        if (current.type != REG_BINARY || current.bytes.size() != 12 || current.bytes[1] || current.bytes[2] || current.bytes[3]) return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
        BYTE state = current.bytes[0];
        if (state != 2 && state != 3 && state != 6 && state != 7) return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
        now = state == 2 || state == 6;
    }
    if (now != e.enabled) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    if (now == enabled) return S_FALSE;
    // Check that the item still exists and its command has not changed since scanning.
    if (e.kind == Kind::Registry) {
        RegValue command;
        hr = ReadValue(e.machine, e.key, e.value, e.view, command);
        if (FAILED(hr)) return hr;
        if (!(command == RegValue{true, e.type, e.raw})) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    } else if (GetFileAttributesW(e.key.c_str()) == INVALID_FILE_ATTRIBUTES) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    RegValue desired{true, REG_BINARY, current.exists ? current.bytes : std::vector<BYTE>(12)};
    desired.bytes[0] = enabled ? (current.exists && current.bytes[0] >= 6 ? 6 : 2) : (current.exists && current.bytes[0] >= 6 ? 7 : 3);
    FILETIME time{};
    if (!enabled) GetSystemTimeAsFileTime(&time);
    memcpy(desired.bytes.data() + 4, &time, sizeof(time));
    return ChangeValue(e.name, e.machine, location, e.value, KEY_WOW64_64KEY, current, desired, receipt);
}
HRESULT SetTaskEnabled(const Entry& e, bool enabled, std::wstring& receipt) {
    TaskConnection connection; if (FAILED(connection.status)) return connection.status;
    auto task = connection.Task(e.key); if (!task) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    auto xml = TaskXml(task.Get());
    VARIANT_BOOL current = VARIANT_FALSE;
    HRESULT hr = task->get_Enabled(&current); if (FAILED(hr)) return hr;
    if (xml.empty() || xml != e.command || (current != VARIANT_FALSE) != e.enabled) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    if ((current != VARIANT_FALSE) == enabled) return S_FALSE;
    Change c; c.operation = L"Task enabled"; c.subject = e.name; c.location = e.key;
    c.beforeType = current != VARIANT_FALSE; c.afterType = enabled;
    c.before = TextBytes(xml);
    hr = StoreChange(c); if (FAILED(hr)) return hr; receipt = c.path;
    hr = task->put_Enabled(enabled ? VARIANT_TRUE : VARIANT_FALSE); if (FAILED(hr)) return hr;
    hr = task->get_Enabled(&current); if (FAILED(hr)) return hr;
    if ((current != VARIANT_FALSE) != enabled) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    c.after = TextBytes(TaskXml(task.Get())); c.phase = 1;
    return c.after.empty() ? E_FAIL : StoreChange(c);
}
HRESULT ReadServiceMode(const std::wstring& name, DWORD& mode) {
    ServiceHandle manager(OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CONNECT));
    if (!manager.h) return HRESULT_FROM_WIN32(GetLastError());
    ServiceHandle service(OpenServiceW(manager, name.c_str(), SERVICE_QUERY_CONFIG));
    if (!service.h) return HRESULT_FROM_WIN32(GetLastError());
    DWORD needed = 0; QueryServiceConfigW(service, nullptr, 0, &needed);
    if (!needed || needed > 1024 * 1024) return E_FAIL;
    std::vector<BYTE> bytes(needed);
    auto config = reinterpret_cast<QUERY_SERVICE_CONFIGW*>(bytes.data());
    if (!QueryServiceConfigW(service, config, needed, &needed)) return HRESULT_FROM_WIN32(GetLastError());
    mode = config->dwStartType; return S_OK;
}
HRESULT WriteServiceMode(const std::wstring& name, DWORD mode) {
    if (mode > SERVICE_DISABLED) return E_INVALIDARG;
    ServiceHandle manager(OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CONNECT));
    if (!manager.h) return HRESULT_FROM_WIN32(GetLastError());
    ServiceHandle service(OpenServiceW(manager, name.c_str(), SERVICE_CHANGE_CONFIG));
    HRESULT hr = service.h ? S_OK : HRESULT_FROM_WIN32(GetLastError());
    if (SUCCEEDED(hr) && !ChangeServiceConfigW(service, SERVICE_NO_CHANGE, mode, SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return Denied(hr) ? BrokerServiceMode(name, mode) : hr;
}
HRESULT UpdateTask(const std::wstring& path, const std::wstring& expectedXml,
                   const std::wstring& desiredXml, std::wstring& receipt) {
    std::lock_guard<std::mutex> guard(g_changeMutex);
    TaskConnection connection; if (FAILED(connection.status)) return connection.status;
    auto task = connection.Task(path); if (!task) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    auto before = TaskXml(task.Get());
    if (before.empty() || before != expectedXml) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    if (before == desiredXml) return S_FALSE;
    auto security = TaskSecurity(task.Get());
    if (security.empty()) return E_ACCESSDENIED;
    HRESULT hr = RegisterXml(path, desiredXml, true, true, security);
    if (FAILED(hr)) return hr;
    Change c; c.operation = L"Task definition"; c.subject = path; c.location = path;
    c.value = security; c.before = TextBytes(before); c.after = TextBytes(desiredXml);
    hr = StoreChange(c); if (FAILED(hr)) return hr; receipt = c.path;
    // Recheck after validation and receipt I/O, which may have allowed another editor to save.
    if (TaskXml(task.Get()) != before) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    hr = RegisterXml(path, desiredXml, false, true, security); if (FAILED(hr)) return hr;
    task = connection.Task(path); if (!task) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    auto after = TaskXml(task.Get()); if (after.empty()) return E_FAIL;
    c.after = TextBytes(after); c.phase = 1; return StoreChange(c);
}
HRESULT SetServiceMode(const Entry& e, DWORD mode, std::wstring& receipt) {
    if ((e.kind != Kind::Service && e.kind != Kind::Driver) || mode > SERVICE_DISABLED) return E_INVALIDARG;
    if (e.kind == Kind::Service && mode < SERVICE_AUTO_START) return E_INVALIDARG;
    DWORD current = 0; HRESULT hr = ReadServiceMode(e.key, current); if (FAILED(hr)) return hr;
    if (current != e.startMode) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    if (current == mode) return S_FALSE;
    Change c; c.operation = L"Service startup"; c.subject = e.name; c.location = e.key;
    c.beforeType = current; c.afterType = mode;
    hr = StoreChange(c); if (FAILED(hr)) return hr; receipt = c.path;
    hr = WriteServiceMode(e.key, mode); if (FAILED(hr)) return hr;
    hr = ReadServiceMode(e.key, current); if (FAILED(hr)) return hr;
    if (current != mode) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    c.phase = 1; return StoreChange(c);
}
HRESULT UndoChange(const std::wstring& receipt) {
    std::lock_guard<std::mutex> guard(g_changeMutex);
    Change c; HRESULT hr = LoadChange(receipt, c); if (FAILED(hr)) return hr;
    if (c.operation == L"Registry value") return UndoValue(receipt);
    if (c.phase == 2) return E_INVALIDARG;
    if (c.operation == L"Service startup") {
        DWORD current = 0; hr = ReadServiceMode(c.location, current); if (FAILED(hr)) return hr;
        if (current == c.beforeType && c.phase == 0) { c.phase = 2; return StoreChange(c); }
        if (current != c.afterType) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
        hr = WriteServiceMode(c.location, c.beforeType); if (FAILED(hr)) return hr;
        hr = ReadServiceMode(c.location, current); if (FAILED(hr)) return hr;
        if (current != c.beforeType) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    } else if (c.operation == L"Task definition") {
        TaskConnection connection; if (FAILED(connection.status)) return connection.status;
        auto task = connection.Task(c.location); if (!task) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
        auto xml = TextBytes(TaskXml(task.Get()));
        if (xml == c.before && c.phase == 0) { c.phase = 2; return StoreChange(c); }
        if (c.phase != 1 || xml != c.after) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
        hr = RegisterXml(c.location, BytesText(c.before), true, true, c.value); if (FAILED(hr)) return hr;
        hr = RegisterXml(c.location, BytesText(c.before), false, true, c.value); if (FAILED(hr)) return hr;
        task = connection.Task(c.location); if (!task) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
        if (TextBytes(TaskXml(task.Get())) != c.before) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    } else if (c.operation == L"Task enabled") {
        TaskConnection connection; if (FAILED(connection.status)) return connection.status;
        auto task = connection.Task(c.location); if (!task) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
        auto xml = TextBytes(TaskXml(task.Get()));
        if (xml == c.before && c.phase == 0) { c.phase = 2; return StoreChange(c); }
        // An incomplete post-write receipt requires manual review of the saved original XML.
        if (c.phase != 1 || xml != c.after) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
        hr = task->put_Enabled(c.beforeType ? VARIANT_TRUE : VARIANT_FALSE); if (FAILED(hr)) return hr;
        VARIANT_BOOL enabled = VARIANT_FALSE; hr = task->get_Enabled(&enabled); if (FAILED(hr)) return hr;
        if ((enabled != VARIANT_FALSE) != (c.beforeType != 0)) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    } else return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
    c.phase = 2; return StoreChange(c);
}
HRESULT ToggleEntry(const Entry& e, bool enabled, std::wstring& receipt) {
    std::lock_guard<std::mutex> guard(g_changeMutex);
    if (!e.writable) return E_ACCESSDENIED;
    if (e.kind == Kind::Registry || e.kind == Kind::Shortcut) return ApprovalToggle(e, enabled, receipt);
    if (e.kind == Kind::Task) return SetTaskEnabled(e, enabled, receipt);
    // Restoring a service needs an explicit startup mode, rather than guessing one.
    if ((e.kind == Kind::Service || e.kind == Kind::Driver) && !enabled) return SetServiceMode(e, SERVICE_DISABLED, receipt);
    return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
}
HRESULT TaskRun(const std::wstring& path, bool stop) {
    TaskConnection connection; if (FAILED(connection.status)) return connection.status;
    auto task = connection.Task(path); if (!task) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    if (stop) return task->Stop(0);
    VARIANT arguments{}; ComPtr<IRunningTask> instance;
    return task->Run(arguments, &instance);
}
}

namespace sc {
// ---- Devices -------------------------------------------------------------------------------
HRESULT ReadDeviceState(const std::wstring& id, bool& enabled) {
    DEVINST inst = 0;
    CONFIGRET cr = CM_Locate_DevNodeW(&inst, const_cast<DEVINSTID_W>(id.c_str()), CM_LOCATE_DEVNODE_NORMAL);
    if (cr != CR_SUCCESS) return HRESULT_FROM_WIN32(ERROR_DEVICE_NOT_CONNECTED);
    ULONG status = 0, problem = 0;
    cr = CM_Get_DevNode_Status(&status, &problem, inst, 0);
    if (cr != CR_SUCCESS) return HRESULT_FROM_WIN32(CM_MapCrToWin32Err(cr, ERROR_GEN_FAILURE));
    enabled = !((status & DN_HAS_PROBLEM) && problem == CM_PROB_DISABLED);
    return S_OK;
}
HRESULT WriteDeviceState(const std::wstring& id, bool enabled) {
    DEVINST inst = 0;
    CONFIGRET cr = CM_Locate_DevNodeW(&inst, const_cast<DEVINSTID_W>(id.c_str()), CM_LOCATE_DEVNODE_NORMAL);
    if (cr != CR_SUCCESS) return HRESULT_FROM_WIN32(ERROR_DEVICE_NOT_CONNECTED);
    cr = enabled ? CM_Enable_DevNode(inst, 0) : CM_Disable_DevNode(inst, CM_DISABLE_UI_NOT_OK);
    if (cr == CR_SUCCESS) return S_OK;
    if (cr == CR_ACCESS_DENIED) return BrokerDeviceState(id, enabled);
    return HRESULT_FROM_WIN32(CM_MapCrToWin32Err(cr, ERROR_GEN_FAILURE));
}
HRESULT DeviceSetEnabled(const Entry& e, bool enabled, std::wstring& receipt) {
    std::lock_guard<std::mutex> guard(g_changeMutex);
    if (e.kind != Kind::Device) return E_INVALIDARG;
    bool now = true;
    HRESULT hr = ReadDeviceState(e.key, now); if (FAILED(hr)) return hr;
    if (now != e.enabled) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
    if (now == enabled) return S_FALSE;
    Change c; c.operation = L"Device state"; c.subject = e.name; c.location = e.key;
    c.beforeType = now; c.afterType = enabled;
    hr = StoreChange(c); if (FAILED(hr)) return hr; receipt = c.path;
    hr = WriteDeviceState(e.key, enabled); if (FAILED(hr)) return hr;
    hr = ReadDeviceState(e.key, now); if (FAILED(hr)) return hr;
    if (now != enabled) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    c.phase = 1; return StoreChange(c);
}

// ---- New and deleted tasks -----------------------------------------------------------------
inline std::wstring CurrentAccount() {
    wchar_t domain[256]{}, user[256]{};
    GetEnvironmentVariableW(L"USERDOMAIN", domain, ARRAYSIZE(domain));
    GetEnvironmentVariableW(L"USERNAME", user, ARRAYSIZE(user));
    return *domain ? std::wstring(domain) + L"\\" + user : std::wstring(user);
}
// trigger: 0 at sign-in, 1 at startup, 2 daily, 3 once.
std::wstring TaskXmlFor(const std::wstring& exe, const std::wstring& args, const std::wstring& dir,
                        int trigger, int hour, int minute) {
    SYSTEMTIME now{}; GetLocalTime(&now);
    FILETIME ft{}; SystemTimeToFileTime(&now, &ft);
    if (trigger >= 2 && (now.wHour > hour || (now.wHour == hour && now.wMinute >= minute))) {
        ULARGE_INTEGER u{ft.dwLowDateTime, ft.dwHighDateTime};
        u.QuadPart += 24ULL * 3600 * 10000000;
        ft.dwLowDateTime = u.LowPart; ft.dwHighDateTime = u.HighPart;
        FileTimeToSystemTime(&ft, &now);
    }
    wchar_t start[40];
    swprintf_s(start, L"%04u-%02u-%02uT%02d:%02d:00", now.wYear, now.wMonth, now.wDay, hour, minute);
    const std::wstring account = XmlEscape(CurrentAccount());
    std::wstring t;
    switch (trigger) {
        case 1: t = L"<BootTrigger><Enabled>true</Enabled></BootTrigger>"; break;
        case 2: t = L"<CalendarTrigger><StartBoundary>" + std::wstring(start) + L"</StartBoundary><Enabled>true</Enabled><ScheduleByDay><DaysInterval>1</DaysInterval></ScheduleByDay></CalendarTrigger>"; break;
        case 3: t = L"<TimeTrigger><StartBoundary>" + std::wstring(start) + L"</StartBoundary><Enabled>true</Enabled></TimeTrigger>"; break;
        default: t = L"<LogonTrigger><Enabled>true</Enabled><UserId>" + account + L"</UserId></LogonTrigger>"; break;
    }
    // A startup trigger runs before anyone signs in, so it needs the system account.
    const std::wstring principal = trigger == 1
        ? L"<Principal id=\"Author\"><UserId>S-1-5-18</UserId><RunLevel>HighestAvailable</RunLevel></Principal>"
        : L"<Principal id=\"Author\"><UserId>" + account + L"</UserId><LogonType>InteractiveToken</LogonType><RunLevel>LeastPrivilege</RunLevel></Principal>";
    return L"<?xml version=\"1.0\" encoding=\"UTF-16\"?>"
           L"<Task version=\"1.2\" xmlns=\"http://schemas.microsoft.com/windows/2004/02/mit/task\">"
           L"<RegistrationInfo><Author>" + account + L"</Author><Description>Created in Startup Control</Description></RegistrationInfo>"
           L"<Triggers>" + t + L"</Triggers><Principals>" + principal + L"</Principals>"
           L"<Settings><MultipleInstancesPolicy>IgnoreNew</MultipleInstancesPolicy><DisallowStartIfOnBatteries>false</DisallowStartIfOnBatteries>"
           L"<StopIfGoingOnBatteries>false</StopIfGoingOnBatteries><StartWhenAvailable>true</StartWhenAvailable><ExecutionTimeLimit>PT0S</ExecutionTimeLimit><Enabled>true</Enabled></Settings>"
           L"<Actions Context=\"Author\"><Exec><Command>" + XmlEscape(exe) + L"</Command>" +
           (args.empty() ? L"" : L"<Arguments>" + XmlEscape(args) + L"</Arguments>") +
           (dir.empty() ? L"" : L"<WorkingDirectory>" + XmlEscape(dir) + L"</WorkingDirectory>") +
           L"</Exec></Actions></Task>";
}
HRESULT CreateTask(const std::wstring& path, const std::wstring& xml, std::wstring& receipt) {
    std::lock_guard<std::mutex> guard(g_changeMutex);
    TaskConnection connection; if (FAILED(connection.status)) return connection.status;
    if (connection.Task(path)) return HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS);
    HRESULT hr = RegisterXml(path, xml, true, false); if (FAILED(hr)) return hr;
    Change c; c.operation = L"Task created"; c.subject = path; c.location = path; c.after = TextBytes(xml);
    hr = StoreChange(c); if (FAILED(hr)) return hr; receipt = c.path;
    hr = RegisterXml(path, xml, false, false); if (FAILED(hr)) return hr;
    auto task = connection.Task(path); if (!task) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
    c.after = TextBytes(TaskXml(task.Get())); c.phase = 1; return StoreChange(c);
}
HRESULT RemoveTask(TaskConnection& connection, const std::wstring& path) {
    auto pos = path.find_last_of(L'\\');
    auto folder = connection.Folder(pos == 0 || pos == path.npos ? L"\\" : path.substr(0, pos));
    if (!folder) return HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND);
    HRESULT hr = folder->DeleteTask(BString(path.substr(pos == path.npos ? 0 : pos + 1)), 0);
    if (FAILED(hr)) return hr;
    return connection.Task(path) ? HRESULT_FROM_WIN32(ERROR_WRITE_FAULT) : S_OK;
}
HRESULT DeleteTask(const std::wstring& path, std::wstring& receipt) {
    std::lock_guard<std::mutex> guard(g_changeMutex);
    TaskConnection connection; if (FAILED(connection.status)) return connection.status;
    auto task = connection.Task(path); if (!task) return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    auto xml = TaskXml(task.Get()); if (xml.empty()) return E_FAIL;
    Change c; c.operation = L"Task deleted"; c.subject = path; c.location = path;
    c.value = TaskSecurity(task.Get()); c.before = TextBytes(xml);
    HRESULT hr = StoreChange(c); if (FAILED(hr)) return hr; receipt = c.path;
    task.Reset();
    hr = RemoveTask(connection, path); if (FAILED(hr)) return hr;
    c.phase = 1; return StoreChange(c);
}
HRESULT UndoAny(const std::wstring& receipt) {
    Change c;
    {
        std::lock_guard<std::mutex> guard(g_changeMutex);
        HRESULT hr = LoadChange(receipt, c); if (FAILED(hr)) return hr;
        if (c.operation == L"Device state") {
            if (c.phase == 2) return E_INVALIDARG;
            bool now = true; hr = ReadDeviceState(c.location, now); if (FAILED(hr)) return hr;
            if (now == (c.beforeType != 0)) { c.phase = 2; return StoreChange(c); }
            hr = WriteDeviceState(c.location, c.beforeType != 0); if (FAILED(hr)) return hr;
            hr = ReadDeviceState(c.location, now); if (FAILED(hr)) return hr;
            if (now != (c.beforeType != 0)) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
            c.phase = 2; return StoreChange(c);
        }
        if (c.operation == L"Task created") {
            if (c.phase == 2) return E_INVALIDARG;
            TaskConnection connection; if (FAILED(connection.status)) return connection.status;
            auto task = connection.Task(c.location);
            if (!task) { c.phase = 2; return StoreChange(c); }
            if (TextBytes(TaskXml(task.Get())) != c.after) return HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH);
            task.Reset();
            hr = RemoveTask(connection, c.location); if (FAILED(hr)) return hr;
            c.phase = 2; return StoreChange(c);
        }
        if (c.operation == L"Task deleted") {
            if (c.phase == 2) return E_INVALIDARG;
            TaskConnection connection; if (FAILED(connection.status)) return connection.status;
            if (connection.Task(c.location)) return HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS);
            hr = RegisterXml(c.location, BytesText(c.before), false, false, c.value); if (FAILED(hr)) return hr;
            if (!connection.Task(c.location)) return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
            c.phase = 2; return StoreChange(c);
        }
    }
    return UndoChange(receipt);
}
std::vector<Change> ListChanges() {
    std::vector<std::pair<FILETIME, std::wstring>> files;
    auto root = DataRoot();
    if (root.empty()) return {};
    WIN32_FIND_DATAW fd{};
    HANDLE find = FindFirstFileW((root + L"\\Changes\\*.scchange").c_str(), &fd);
    if (find != INVALID_HANDLE_VALUE) {
        do files.push_back({fd.ftLastWriteTime, root + L"\\Changes\\" + fd.cFileName});
        while (FindNextFileW(find, &fd));
        FindClose(find);
    }
    std::sort(files.begin(), files.end(), [](auto& a, auto& b) { return CompareFileTime(&a.first, &b.first) > 0; });
    std::vector<Change> out;
    for (auto& f : files) {
        if (out.size() >= 200) break;
        Change c;
        if (SUCCEEDED(LoadChange(f.second, c))) { c.before.clear(); c.after.clear(); out.push_back(std::move(c)); }
    }
    return out;
}
inline std::wstring FileTimeText(const std::wstring& path) {
    WIN32_FILE_ATTRIBUTE_DATA a{};
    if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &a)) return L"";
    FILETIME local{}; SYSTEMTIME st{};
    FileTimeToLocalFileTime(&a.ftLastWriteTime, &local); FileTimeToSystemTime(&local, &st);
    wchar_t b[40]; swprintf_s(b, L"%04u-%02u-%02u %02u:%02u", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
    return b;
}

// ---- Task details --------------------------------------------------------------------------
struct Section { std::wstring title; std::vector<std::pair<std::wstring, std::wstring>> rows; };
inline std::wstring Prop(BSTR s) { std::wstring v = Bstr(s); SysFreeString(s); return v; }
inline std::wstring Boundary(const std::wstring& s) {
    if (s.size() < 16) return s;
    auto t = s.substr(0, 16); t[10] = L' '; return t;
}
std::vector<Section> TaskSummary(const std::wstring& path) {
    std::vector<Section> out;
    TaskConnection connection; if (FAILED(connection.status)) return out;
    auto task = connection.Task(path); if (!task) return out;
    ComPtr<ITaskDefinition> d; if (FAILED(task->get_Definition(&d))) return out;
    Section general{L"General"};
    ComPtr<IRegistrationInfo> info;
    if (SUCCEEDED(d->get_RegistrationInfo(&info))) {
        BSTR s = nullptr;
        info->get_Description(&s); auto desc = Prop(s);
        if (!desc.empty()) general.rows.push_back({L"Description", desc});
        s = nullptr; info->get_Author(&s); auto author = Prop(s);
        if (!author.empty()) general.rows.push_back({L"Author", author});
    }
    ComPtr<IPrincipal> principal;
    if (SUCCEEDED(d->get_Principal(&principal))) {
        BSTR s = nullptr; principal->get_UserId(&s); auto user = Prop(s);
        if (user.empty()) { s = nullptr; principal->get_GroupId(&s); user = Prop(s); }
        if (user == L"S-1-5-18" || Lower(user) == L"system") user = L"System";
        general.rows.push_back({L"Runs as", user.empty() ? L"Not set" : user});
        TASK_RUNLEVEL_TYPE level{}; principal->get_RunLevel(&level);
        general.rows.push_back({L"Admin rights", level == TASK_RUNLEVEL_HIGHEST ? L"Yes" : L"No"});
    }
    DATE last = 0, next = 0; LONG result = 0;
    task->get_LastRunTime(&last); task->get_NextRunTime(&next); task->get_LastTaskResult(&result);
    general.rows.push_back({L"Last run", DateText(last)});
    general.rows.push_back({L"Next run", DateText(next)});
    general.rows.push_back({L"Last result", result == 0 ? L"Finished fine" : result == 0x41303 ? L"Not run yet" :
                            result == 0x41301 ? L"Running now" : Hex(result)});
    out.push_back(general);
    Section triggers{L"Triggers"};
    ComPtr<ITriggerCollection> tc;
    if (SUCCEEDED(d->get_Triggers(&tc))) {
        LONG n = 0; tc->get_Count(&n);
        for (LONG i = 1; i <= n; ++i) {
            ComPtr<ITrigger> t; if (FAILED(tc->get_Item(i, &t))) continue;
            TASK_TRIGGER_TYPE2 type{}; t->get_Type(&type);
            PCWSTR name = L"Other";
            switch (type) {
                case TASK_TRIGGER_EVENT: name = L"When an event is logged"; break;
                case TASK_TRIGGER_TIME: name = L"Once"; break;
                case TASK_TRIGGER_DAILY: name = L"Daily"; break;
                case TASK_TRIGGER_WEEKLY: name = L"Weekly"; break;
                case TASK_TRIGGER_MONTHLY: case TASK_TRIGGER_MONTHLYDOW: name = L"Monthly"; break;
                case TASK_TRIGGER_IDLE: name = L"When the PC is idle"; break;
                case TASK_TRIGGER_REGISTRATION: name = L"When the task is saved"; break;
                case TASK_TRIGGER_BOOT: name = L"At startup"; break;
                case TASK_TRIGGER_LOGON: name = L"At sign-in"; break;
                case TASK_TRIGGER_SESSION_STATE_CHANGE: name = L"On a session change"; break;
                default: break;
            }
            BSTR s = nullptr; t->get_StartBoundary(&s); auto start = Boundary(Prop(s));
            VARIANT_BOOL on = VARIANT_TRUE; t->get_Enabled(&on);
            std::wstring v = start.empty() ? L"" : L"From " + start;
            if (on == VARIANT_FALSE) v += v.empty() ? L"Off" : L"  ·  Off";
            triggers.rows.push_back({name, v.empty() ? L"On" : v});
        }
    }
    if (triggers.rows.empty()) triggers.rows.push_back({L"None", L"Runs only when started by hand"});
    out.push_back(triggers);
    Section actions{L"Actions"};
    ComPtr<IActionCollection> ac;
    if (SUCCEEDED(d->get_Actions(&ac))) {
        LONG n = 0; ac->get_Count(&n);
        for (LONG i = 1; i <= n; ++i) {
            ComPtr<IAction> a; if (FAILED(ac->get_Item(i, &a))) continue;
            ComPtr<IExecAction> exec;
            if (SUCCEEDED(a.As(&exec))) {
                BSTR p = nullptr, g = nullptr; exec->get_Path(&p); exec->get_Arguments(&g);
                auto prog = Prop(p), args = Prop(g);
                actions.rows.push_back({L"Start a program", prog + (args.empty() ? L"" : L" " + args)});
            } else actions.rows.push_back({L"Built-in handler", L"Runs a Windows component"});
        }
    }
    out.push_back(actions);
    Section settings{L"Conditions and settings"};
    ComPtr<ITaskSettings> ts;
    if (SUCCEEDED(d->get_Settings(&ts))) {
        VARIANT_BOOL b = VARIANT_FALSE;
        ts->get_DisallowStartIfOnBatteries(&b);
        settings.rows.push_back({L"On battery", b != VARIANT_FALSE ? L"Waits for power" : L"Runs anyway"});
        b = VARIANT_FALSE; ts->get_RunOnlyIfIdle(&b);
        settings.rows.push_back({L"Only when idle", b != VARIANT_FALSE ? L"Yes" : L"No"});
        b = VARIANT_FALSE; ts->get_StartWhenAvailable(&b);
        settings.rows.push_back({L"Catch up missed runs", b != VARIANT_FALSE ? L"Yes" : L"No"});
        b = VARIANT_FALSE; ts->get_Hidden(&b);
        settings.rows.push_back({L"Hidden", b != VARIANT_FALSE ? L"Yes" : L"No"});
        BSTR s = nullptr; ts->get_ExecutionTimeLimit(&s); auto limit = Prop(s);
        settings.rows.push_back({L"Time limit", limit.empty() || limit == L"PT0S" ? L"None" : limit});
    }
    out.push_back(settings);
    return out;
}
struct HistoryEvent { std::wstring when, what, result; };
inline std::wstring Between(const std::wstring& s, const std::wstring& a, const std::wstring& b, size_t from = 0) {
    auto p = s.find(a, from); if (p == s.npos) return L"";
    p += a.size(); auto q = s.find(b, p); if (q == s.npos) return L"";
    return s.substr(p, q - p);
}
std::vector<HistoryEvent> ParseHistory(const std::wstring& raw) {
    std::vector<HistoryEvent> out;
    for (size_t at = 0; (at = raw.find(L"<Event ", at)) != raw.npos;) {
        auto end = raw.find(L"</Event>", at); if (end == raw.npos) break;
        auto ev = raw.substr(at, end - at); at = end;
        auto tag = ev.find(L"<EventID"), close = tag == ev.npos ? ev.npos : ev.find(L'>', tag);
        int id = close == ev.npos ? 0 : _wtoi(ev.c_str() + close + 1);
        PCWSTR what = nullptr;
        switch (id) {
            case 100: what = L"Started"; break; case 101: what = L"Failed to start"; break;
            case 102: what = L"Finished"; break; case 103: what = L"Action failed"; break;
            case 106: what = L"Registered"; break; case 107: what = L"Triggered by schedule"; break;
            case 110: what = L"Run by user"; break; case 129: what = L"Program started"; break;
            case 140: what = L"Updated"; break; case 141: what = L"Deleted"; break;
            case 200: what = L"Action started"; break; case 201: what = L"Action finished"; break;
            default: break;
        }
        HistoryEvent h; h.what = what ? what : L"Event " + std::to_wstring(id);
        auto t = Between(ev, L"SystemTime='", L"'"); if (t.empty()) t = Between(ev, L"SystemTime=\"", L"\"");
        SYSTEMTIME st{};
        if (t.size() >= 19 && swscanf_s(t.c_str(), L"%hu-%hu-%huT%hu:%hu:%hu", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond) == 6) {
            SYSTEMTIME local{};
            if (SystemTimeToTzSpecificLocalTime(nullptr, &st, &local)) st = local;
            wchar_t b[40]; swprintf_s(b, L"%04u-%02u-%02u %02u:%02u:%02u", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
            h.when = b;
        }
        auto code = Between(ev, L"Name='ResultCode'>", L"<"); if (code.empty()) code = Between(ev, L"Name=\"ResultCode\">", L"<");
        if (!code.empty()) h.result = code == L"0" ? L"Result fine" : L"Result " + code;
        out.push_back(std::move(h));
    }
    return out;
}
}

namespace sc {
struct ScanOptions {
    bool registry = true, tasks = true, services = true, devices = true, wmi = true;
};
bool StartScan(HWND notify, ScanOptions options = {}) {
    if (g_scanning.exchange(true)) return false;
    if (g_scanThread.joinable()) g_scanThread.join();
    g_cancel = false; g_notify = notify;
    g_scanThread = std::thread([options] {
        SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
        Apartment apartment;
        Inventory inv;
        if (FAILED(apartment.hr)) inv.errors.push_back(L"Cannot start Windows management: " + Error(apartment.hr));
        else {
            ScanLogon(inv);
            if (options.registry && !g_cancel) ScanRegistry(inv);
            if (options.tasks && !g_cancel) ScanTasks(inv);
            if (options.services && !g_cancel) ScanServices(inv);
            if (options.devices && !g_cancel) ScanDevices(inv);
            if (options.wmi && !g_cancel) ScanWmi(inv);
        }
        if (!g_cancel) {
            std::lock_guard<std::mutex> guard(g_dataMutex);
            inv.revision = g_inventory.revision + 1;
            g_inventory = std::move(inv);
        }
        g_scanning = false;
        if (HWND hwnd = g_notify.load()) PostMessageW(hwnd, WM_SC_DATA, 0, 0);
    });
    return true;
}
void StopScan() {
    g_notify = nullptr; g_cancel = true;
    if (g_scanThread.joinable()) g_scanThread.join();
}
}

extern "C" IMAGE_DOS_HEADER __ImageBase;
static std::wstring GetStringSetting(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring value = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return value;
}
static void ForceForeground(HWND hwnd) { SetForegroundWindow(hwnd); SetFocus(hwnd); }
namespace scui {
// The settings window, from the "..." menu. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkStartupControl";
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1, WM_APP_SETTINGS_ACTIVATE = WM_APP + 2;
HANDLE g_settingsThread = nullptr;
std::atomic<HWND> g_settingsWnd;
std::atomic<bool> g_settingsStop;
void Settings_Close();
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
// Generated by test-settings\gen_table.py from src\00-header.cpp.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Check, L"scanRegistry", L"Scan registry locations", L"Include logon entries and advanced integrations.", L"1", {}, 0, 100, 9, L"Scanning"},
{K::Check, L"scanTasks", L"Scan scheduled tasks", L"Include hidden tasks and task subfolders.", L"1", {}, 0, 100, 9, L"Scanning"},
{K::Check, L"scanServices", L"Scan services and drivers", L"Read startup modes and dependencies.", L"1", {}, 0, 100, 9, L"Scanning"},
{K::Check, L"scanDevices", L"Scan devices", L"Include disconnected devices.", L"1", {}, 0, 100, 9, L"Scanning"},
{K::Check, L"scanWmi", L"Scan WMI subscriptions", L"Read event filters, consumers and their bindings.", L"1", {}, 0, 100, 9, L"Scanning"},
{K::Check, L"showViewOnly", L"Show entries you cannot change", L"Lists protected entries too, with a lock instead of a switch.", L"1", {}, 0, 100, 9, L"List"},
{K::Check, L"groupByLocation", L"Group Everything by location", L"Splits the Everything page into one section per location.", L"1", {}, 0, 100, 9, L"List"},
{K::Check, L"confirmDevices", L"Ask before turning off a device", L"Turning off a device needs a second click.", L"1", {}, 0, 100, 9, L"Safety"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 9, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 9, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Show Startup Control in the notification area.", L"1", {}, 0, 100, 9, L"Settings window"},
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Everything", L"Search startup entries from every scanned location.", 0xE8A9},
{L"Startup apps", L"Apps and shortcuts that run when you sign in.", 0xE7F4},
{L"Scheduled tasks", L"Task folders, definitions, actions and history.", 0xE787},
{L"Services", L"Service startup settings and current state.", 0xE90F},
{L"Drivers", L"Driver startup settings. Some changes need a restart.", 0xE950},
{L"Devices", L"Connected and remembered devices.", 0xE772},
{L"Explorer add-ons", L"Extensions and handlers registered with Windows.", 0xE8B7},
{L"Advanced locations", L"Other startup and system integration locations.", 0xE81E},
{L"Changes", L"Saved originals and receipts for changes made here.", 0xE81C},
{L"Settings", L"Scanning, display and this window.", 0xE713},
{L"About", L"Startup Control, credits and support.", 0xE946},
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
constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/fullscreen-start";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Launchpad%5D%20";
constexpr PCWSTR kSetTitle = L"Startup Control";
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
// ---- Tray menu (since Launchpad 2.6.0) --------------------------------------------------------
// Every mod's tray menu: Clipboard's Direct2D menu, one acrylic popup per level, a glyph column,
// measured labels, submenus, keyboard and click-away. Build a std::vector<SetMenuItem> and call
// Set_TrayMenu(owner, items); it returns the picked id, or 0.

// The live window corner radius: the custom-corner-radius mod's value, 8 when it is off.
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

// Row heights and a width that fits the longest label and hint, so nothing is cut off.
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

// The next enabled row from `from` in direction dir (+1 or -1), wrapping. -1 when there is none.
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

// Closes every level from n down; n == 0 closes the whole menu.
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

// Clipboard's popup material: dark, round corners, no system border, the accent acrylic blur.
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

// Makes the popup at `at`, reads its monitor's scale, then sizes it to the rows. A root menu flips
// to the left of or above the point near a monitor edge; a submenu sits beside its parent row.
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

// Arrows move, Right or Enter opens a submenu, Left or Esc closes one level, Enter or Space picks.
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

// Shows a tray menu at `at` (the pointer when null) and returns the picked id, or 0. Runs its own
// message loop on the calling thread, like TrackPopupMenu with TPM_RETURNCMD.
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Control") <= railW) break;
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
static float SC_BuildPage(SetWindow& w, float y);
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
        add(SetItem::Link, 56, L"Windows Task Scheduler", L"Microsoft documentation", L"https://learn.microsoft.com/windows/win32/taskschd/task-scheduler-start-page");
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/davids-windhawk-mods", kSetRepoUrl);
        add(SetItem::Link, 56, L"Report a problem", L"Opens a new issue on GitHub, with the mod's name filled in", kSetBugUrl);
    }
    y = SC_BuildPage(w, y);
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
    p.Glyph(w.fIconL.get(), 0xE7F4, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Startup Control", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Manage startup apps, scheduled tasks and Windows startup locations.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi using the Windows management interfaces.",
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
    p.Text(w.fRailName.get(), L"Startup", {d.left + 90, d.top + 9, d.left + w.railW - 10, d.top + 33}, mocha::text, textA);
    p.Text(w.fRailName.get(), L"Control", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    p.Glyph(glyph, 0xE7F4, r, mocha::crust);
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

static void SC_Layout(SetWindow& w);
static void SC_DrawPage(SetPaint& p, SetWindow& w, float viewH, const D2D1_MATRIX_3X2_F& base);
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
        SC_DrawPage(cp, w, viewH, base);
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
    SC_Layout(w);
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (false) p.GradRing({0, 0, w.cw, w.ch + kSetCapH}, SystemCornerRadius(false), 1, 1);
    HRESULT hr = rt->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) w.rt.reset(), w.layer.reset();
}

// ---- Hit testing --------------------------------------------------------------

static bool SC_Hit(SetWindow& w, float x, float cy, SetHit& h);
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
    if (SC_Hit(w, x, cy, h)) return h;
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

static std::wstring Set_FormatHotkey(UINT mods, UINT vk) {
    std::wstring text = std::to_wstring(vk);
    if (!text.empty()) return text;
    // Fallback while the capture part is a stub.
    if (mods & MOD_CONTROL) text += L"Ctrl+";
    if (mods & MOD_ALT) text += L"Alt+";
    if (mods & MOD_SHIFT) text += L"Shift+";
    if (mods & MOD_WIN) text += L"Win+";
    WCHAR name[64] = {};
    LONG scan = (LONG)MapVirtualKeyW(vk, MAPVK_VK_TO_VSC) << 16;
    if (GetKeyNameTextW(scan, name, ARRAYSIZE(name)) > 0) {
        text += name;
    } else {
        text += std::to_wstring(vk);
    }
    return text;
}

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

// A switch's stored value, found by the end of its key so a "SettingsWindow." prefix still matches.
static bool Set_FieldOn(const SetWindow& w, PCWSTR key, bool def) {
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

static bool SC_Message(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, LRESULT& result);
static LRESULT CALLBACK Set_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w) return DefWindowProcW(hwnd, msg, wParam, lParam);
    LRESULT scResult = 0;
    if (SC_Message(hwnd, msg, wParam, lParam, scResult)) return scResult;
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Startup Control", style,
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

// ---- Startup Control screens: lists, details, task definition, new task, changes ----------
// Pages 0 to 8 are drawn here inside the shared settings window. Settings and About stay the
// template's own pages.
constexpr int SC_REFRESH = 4102;
constexpr int SC_ID_EDIT = 4110;
constexpr UINT SC_WM_DONE = WM_APP + 61;
constexpr int SC_HitBase = 200000;
constexpr int SC_Pages = 9, SC_ChangesPage = 8;
std::atomic<int> g_scJobs{0};

enum SC_Edit { SE_Search, SE_Xml, SE_Name, SE_Prog, SE_Args, SE_Time, SE_Count };
enum SC_Act {
    A_None, A_Row, A_Switch, A_Head, A_Show, A_Sort, A_Refresh, A_NewTask, A_Back, A_Mode, A_Run, A_End,
    A_EditXml, A_History, A_Copy, A_Reveal, A_Delete, A_Trigger, A_Browse, A_Create, A_Check, A_Save, A_Undo, A_Box
};
enum SC_Kind { R_Toggle, R_Mode, R_Run, R_Summary, R_History, R_Xml, R_Check, R_Save, R_Delete, R_Create, R_Undo };

struct SC_Item {
    enum Type { Box, Chip, Pill, Icon, Head, Row, Note, Hero, Card, Change, Label, Switch } type = Note;
    D2D1_RECT_F r{};
    int act = A_None, arg = 0, edit = -1, entry = -1, tone = 0;
    bool on = false;
    WCHAR glyph = 0;
    std::wstring text, sub;
    std::vector<std::pair<std::wstring, std::wstring>> rows;
};

struct SC_Result {
    int kind = 0;
    HRESULT hr = S_OK;
    std::wstring id, text;
    DWORD value = 0;
    bool on = false;
    std::vector<sc::Section> summary;
    std::vector<sc::HistoryEvent> history;
};

struct SC_State {
    HWND hwnd = nullptr;
    UINT dpi = 0;
    bool glass = false, loaded = false, scanning = false, kbd = false;
    std::vector<sc::Entry> entries;
    std::map<std::wstring, int> byId;
    std::vector<std::wstring> errors;
    std::vector<int> order;
    std::wstring filter, selId, cursorId, confirmId, xmlOriginal;
    int show = 0, sort = 0, mode = 0, lastPage = -1, trigger = 0;
    std::vector<sc::Section> summary;
    std::vector<sc::HistoryEvent> history;
    bool summaryLoading = false, historyShown = false, historyLoading = false, confirmDelete = false;
    std::vector<sc::Change> changes;
    std::map<std::wstring, bool> collapsed, want;
    std::map<std::wstring, float> knob;
    std::vector<SC_Item> items;
    HWND edits[SE_Count]{};
    HFONT font = nullptr, mono = nullptr;
    D2D1_RECT_F editRect[SE_Count]{};
    bool editWant[SE_Count]{}, editForce[SE_Count]{};
    RECT editPx[SE_Count]{};
    bool editShown[SE_Count]{};
    SetCom<IDWriteTextFormat> fName, fSub, fChip, fHead;
};
static SC_State g_sc;

// ---- Small helpers -------------------------------------------------------------------------
static SetCom<IDWriteTextFormat> SC_Fmt(SetWindow& w, float size, int weight,
                                       DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING) {
    auto f = Set_Fmt(w.family, size, weight, false, align, true);
    if (f) {
        DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        SetCom<IDWriteInlineObject> sign;
        if (SUCCEEDED(g_setDw->CreateEllipsisTrimmingSign(f.get(), sign.put()))) f->SetTrimming(&t, sign.get());
    }
    return f;
}
static void SC_EnsureFormats(SetWindow& w) {
    if (g_sc.fName) return;
    g_sc.fName = SC_Fmt(w, 13.5f, 600);
    g_sc.fSub = SC_Fmt(w, 12, 400);
    g_sc.fChip = SC_Fmt(w, 12.5f, 600, DWRITE_TEXT_ALIGNMENT_CENTER);
    g_sc.fHead = SC_Fmt(w, 10.5f, 700);
}
static std::wstring SC_Text(HWND hwnd) {
    if (!hwnd) return {};
    int n = GetWindowTextLengthW(hwnd);
    if (n <= 0) return {};
    std::wstring s(n + 1, 0);
    s.resize(GetWindowTextW(hwnd, s.data(), n + 1));
    return s;
}
static std::wstring SC_Upper(std::wstring s) {
    for (auto& c : s) c = (wchar_t)towupper(c);
    return s;
}
static bool SC_InPage(const sc::Entry& e, int page) {
    switch (page) {
        case 0: return true;
        case 1: return e.category == L"Startup apps";
        case 2: return e.kind == sc::Kind::Task;
        case 3: return e.kind == sc::Kind::Service;
        case 4: return e.kind == sc::Kind::Driver;
        case 5: return e.kind == sc::Kind::Device;
        case 6: return e.category == L"Explorer add-ons";
        case 7:
            return (e.kind == sc::Kind::Registry || e.kind == sc::Kind::Wmi) && e.category != L"Startup apps" &&
                   e.category != L"Explorer add-ons";
        default: return false;
    }
}
static WCHAR SC_Glyph(const sc::Entry& e) {
    switch (e.kind) {
        case sc::Kind::Task: return 0xE787;
        case sc::Kind::Service: return 0xE90F;
        case sc::Kind::Driver: return 0xE950;
        case sc::Kind::Device: return 0xE772;
        case sc::Kind::Wmi: return 0xE945;
        case sc::Kind::Shortcut: return 0xE71B;
        default: break;
    }
    if (e.category == L"Startup apps") return 0xE7F4;
    if (e.category == L"Explorer add-ons") return 0xE8B7;
    return 0xE81E;
}
static bool SC_Toggleable(const sc::Entry& e) {
    if (!e.writable) return false;
    return e.kind == sc::Kind::Registry || e.kind == sc::Kind::Shortcut || e.kind == sc::Kind::Task ||
           e.kind == sc::Kind::Service || e.kind == sc::Kind::Driver || e.kind == sc::Kind::Device;
}
static PCWSTR SC_ModeName(DWORD mode);
static std::wstring SC_WhereRaw(const sc::Entry& e) {
    if (e.kind == sc::Kind::Task) return e.target.empty() ? e.source : e.target;
    if (e.kind == sc::Kind::Service || e.kind == sc::Kind::Driver) {
        std::wstring file = e.target.empty() ? e.command : e.target;
        return file.empty() ? std::wstring(SC_ModeName(e.startMode)) : std::wstring(SC_ModeName(e.startMode)) + L" · " + file;
    }
    if (!e.command.empty()) return e.command;
    if (!e.target.empty()) return e.target;
    return e.source;
}
// The 32-bit registry copy reads like a duplicate unless it says which one it is.
static std::wstring SC_Where(const sc::Entry& e) {
    return e.view == KEY_WOW64_32KEY ? L"32-bit · " + SC_WhereRaw(e) : SC_WhereRaw(e);
}
static PCWSTR SC_ModeName(DWORD mode) {
    static const PCWSTR names[] = {L"At boot", L"With Windows", L"Automatic", L"When needed", L"Disabled"};
    return mode <= 4 ? names[mode] : L"Unknown";
}
static const sc::Entry* SC_Sel() {
    auto it = g_sc.byId.find(g_sc.selId);
    return it == g_sc.byId.end() ? nullptr : &g_sc.entries[it->second];
}
static int SC_IndexOf(const std::wstring& id) {
    auto it = g_sc.byId.find(id);
    return it == g_sc.byId.end() ? -1 : it->second;
}
static void SC_Reindex() {
    g_sc.byId.clear();
    for (int i = 0; i < (int)g_sc.entries.size(); i++) g_sc.byId[g_sc.entries[i].id] = i;
}
static std::wstring SC_ErrorText(HRESULT hr) {
    if (hr == HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH)) return L"This entry changed somewhere else. Refresh and try again.";
    if (hr == HRESULT_FROM_WIN32(ERROR_LOGON_FAILURE)) return L"This task needs its account password. Nothing was changed.";
    if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED)) return L"The admin prompt was cancelled. Nothing was changed.";
    if (hr == HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS)) return L"A task with that name already exists.";
    if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) return L"Windows can no longer find it. Refresh the list.";
    if (sc::Denied(hr)) return L"Windows refused the change. It needs admin rights.";
    return sc::Error(hr);
}
static void SC_Status(SetWindow& w, const std::wstring& text, bool error = false) { Set_SetStatus(w, text.c_str(), error); }

template <class F>
static void SC_RunAsync(HWND hwnd, F fn) {
    ++g_scJobs;
    std::thread([hwnd, fn]() mutable {
        auto* r = new SC_Result;
        {
            sc::Apartment apartment;
            if (SUCCEEDED(apartment.hr)) fn(*r);
            else r->hr = apartment.hr;
        }
        if (!PostMessageW(hwnd, SC_WM_DONE, 0, (LPARAM)r)) delete r;
        --g_scJobs;
    }).detach();
}

// ---- List order ----------------------------------------------------------------------------
static bool SC_Grouped(const SetWindow& w) { return w.page == 0 && Wh_GetIntSetting(L"groupByLocation") != 0; }
// Every list except Devices splits into what apps added and what Windows ships.
static bool SC_Split(const SetWindow& w) { return !SC_Grouped(w) && w.page != 5; }
static std::wstring SC_Group(const SetWindow& w, const sc::Entry& e) {
    if (SC_Grouped(w)) return e.category;
    return e.windows ? L"Part of Windows" : L"Added by apps";
}
static void SC_Filter(SetWindow& w) {
    g_sc.order.clear();
    std::wstring q = sc::Lower(g_sc.filter);
    bool viewOnly = Wh_GetIntSetting(L"showViewOnly") != 0;
    for (int i = 0; i < (int)g_sc.entries.size(); i++) {
        const auto& e = g_sc.entries[i];
        if (e.kind == sc::Kind::Notice || !SC_InPage(e, w.page)) continue;
        if (!viewOnly && !e.writable) continue;
        if (g_sc.show == 1 && !e.enabled) continue;
        if (g_sc.show == 2 && e.enabled) continue;
        if (!q.empty() && sc::Lower(e.name + L" " + e.source + L" " + SC_Where(e) + L" " + e.command + L" " + e.category + L" " + e.user).find(q) ==
                              std::wstring::npos)
            continue;
        g_sc.order.push_back(i);
    }
    bool grouped = SC_Grouped(w), split = SC_Split(w);
    int sort = g_sc.sort;
    std::stable_sort(g_sc.order.begin(), g_sc.order.end(), [&](int a, int b) {
        const auto &x = g_sc.entries[a], &y = g_sc.entries[b];
        if (split && x.windows != y.windows) return !x.windows;
        if (grouped) {
            int c = _wcsicmp(x.category.c_str(), y.category.c_str());
            if (c) return c < 0;
        }
        if (sort == 1 && x.enabled != y.enabled) return x.enabled;
        if (sort == 2) {
            int c = _wcsicmp(x.source.c_str(), y.source.c_str());
            if (c) return c < 0;
        }
        return _wcsicmp(x.name.c_str(), y.name.c_str()) < 0;
    });
}
static void SC_Refresh(SetWindow& w) {
    sc::ScanOptions o;
    o.registry = Wh_GetIntSetting(L"scanRegistry") != 0;
    o.tasks = Wh_GetIntSetting(L"scanTasks") != 0;
    o.services = Wh_GetIntSetting(L"scanServices") != 0;
    o.devices = Wh_GetIntSetting(L"scanDevices") != 0;
    o.wmi = Wh_GetIntSetting(L"scanWmi") != 0;
    if (sc::StartScan(w.hwnd, o)) {
        g_sc.scanning = true;
        SC_Status(w, L"Reading startup locations...");
    }
}

// ---- Page build ----------------------------------------------------------------------------
static SC_Item& SC_Add(SC_Item::Type t, D2D1_RECT_F r, int act = A_None, int arg = 0) {
    SC_Item it;
    it.type = t;
    it.r = r;
    it.act = act;
    it.arg = arg;
    g_sc.items.push_back(std::move(it));
    return g_sc.items.back();
}
static float SC_PillW(const std::wstring& text, WCHAR glyph) {
    return Set_TextW(g_sc.fChip.get(), text) + (glyph ? 50.0f : 30.0f);
}
static SC_Item& SC_AddPill(float& x, float y, float h, const std::wstring& text, WCHAR glyph, int act, int arg = 0, int tone = 0,
                           SC_Item::Type t = SC_Item::Pill) {
    float wdt = SC_PillW(text, glyph);
    auto& it = SC_Add(t, {x, y, x + wdt, y + h}, act, arg);
    it.text = text;
    it.glyph = glyph;
    it.tone = tone;
    x += wdt + 8;
    return it;
}
static void SC_AddBox(int edit, D2D1_RECT_F r, const std::wstring& hint, WCHAR glyph = 0) {
    auto& it = SC_Add(SC_Item::Box, r, A_Box, edit);
    it.edit = edit;
    it.text = hint;
    it.glyph = glyph;
    g_sc.editWant[edit] = true;
    g_sc.editRect[edit] = r;
}
static float SC_AddNote(SetWindow& w, float y, const std::wstring& text) {
    float h = Set_TextH(w.fHint.get(), text, w.contentW - 8) + 8;
    auto& it = SC_Add(SC_Item::Note, {w.contentX, y, w.contentX + w.contentW, y + h});
    it.text = text;
    return y + h + 10;
}
static float SC_AddLabel(SetWindow& w, float y, const std::wstring& text) {
    auto& it = SC_Add(SC_Item::Label, {w.contentX, y, w.contentX + w.contentW, y + 20});
    it.text = text;
    return y + 26;
}
constexpr float kScLabelW = 132;
static float SC_CardH(SetWindow& w, const SC_Item& it) {
    float vw = it.r.right - it.r.left - kScLabelW - 40, h = it.text.empty() ? 12.0f : 42.0f;
    for (auto& row : it.rows) h += std::max(Set_TextH(w.fHint.get(), row.second, vw), 18.0f) + 10;
    return h + 8;
}
static float SC_AddCard(SetWindow& w, float y, const std::wstring& title, std::vector<std::pair<std::wstring, std::wstring>> rows) {
    if (rows.empty()) return y;
    auto& it = SC_Add(SC_Item::Card, {w.contentX, y, w.contentX + w.contentW, y});
    it.text = title;
    it.rows = std::move(rows);
    it.r.bottom = y + SC_CardH(w, it);
    return it.r.bottom + 12;
}

static float SC_BuildList(SetWindow& w, float y) {
    float L = w.contentX, R = w.contentX + w.contentW;
    bool tasks = w.page == 2;
    float boxR = R - 46 - (tasks ? 124 : 0);
    SC_AddBox(SE_Search, {L, y, boxR, y + 38}, L"Search by name, file or location", 0xE721);
    if (tasks) {
        float x = R - 46 - 116;
        SC_AddPill(x, y, 38, L"New task", 0xE710, A_NewTask, 0, 1);
    }
    auto& refresh = SC_Add(SC_Item::Icon, {R - 38, y, R, y + 38}, A_Refresh);
    refresh.glyph = 0xE72C;
    refresh.on = g_sc.scanning;
    y += 50;
    float x = L;
    static const PCWSTR shows[] = {L"All", L"On", L"Off"};
    for (int i = 0; i < 3; i++) SC_AddPill(x, y, 30, shows[i], 0, A_Show, i, 0, SC_Item::Chip).on = g_sc.show == i;
    static const PCWSTR sorts[] = {L"Name", L"State", L"Location"};
    float sx = R;
    for (int i = 2; i >= 0; i--) sx -= SC_PillW(sorts[i], 0) + 8;
    if (sx - 54 >= x + 8) {
        auto& sortLabel = SC_Add(SC_Item::Label, {sx - 54, y, sx - 6, y + 30});
        sortLabel.text = L"Sort";
        sortLabel.tone = 1;
    }
    for (int i = 0; i < 3; i++) SC_AddPill(sx, y, 30, sorts[i], 0, A_Sort, i, 0, SC_Item::Chip).on = g_sc.sort == i;
    y += 44;
    if (!g_sc.loaded) return SC_AddNote(w, y, L"Reading startup locations. This takes a few seconds the first time.");
    size_t total = 0;
    for (auto& e : g_sc.entries)
        if (e.kind != sc::Kind::Notice && SC_InPage(e, w.page)) total++;
    std::wstring count = std::to_wstring(g_sc.order.size()) + (g_sc.order.size() == total ? L"" : L" of " + std::to_wstring(total)) +
                         (total == 1 ? L" entry" : L" entries");
    if (!g_sc.errors.empty()) count += L". Some locations could not be read.";
    y = SC_AddNote(w, y, count);
    if (g_sc.order.empty())
        return SC_AddNote(w, y, g_sc.filter.empty() && !g_sc.show ? L"Nothing here." : L"Nothing matches. Clear the search or pick All.");
    bool grouped = SC_Grouped(w) || SC_Split(w);
    std::map<std::wstring, int> counts;
    if (grouped)
        for (int i : g_sc.order) counts[SC_Group(w, g_sc.entries[i])]++;
    std::wstring group;
    bool hidden = false;
    for (int i : g_sc.order) {
        const auto& e = g_sc.entries[i];
        std::wstring name = grouped ? SC_Group(w, e) : std::wstring();
        if (grouped && (group != name || g_sc.items.back().type == SC_Item::Note)) {
            if (group != name) {
                group = name;
                // Windows' own items start folded; a search always shows what it found.
                auto c = g_sc.collapsed.find(group);
                bool folded = c != g_sc.collapsed.end() ? c->second : group == L"Part of Windows";
                hidden = folded && g_sc.filter.empty();
                auto& head = SC_Add(SC_Item::Head, {L, y + 4, R, y + 36}, A_Head);
                head.text = group;
                head.sub = std::to_wstring(counts[group]);
                head.on = !hidden;
                y += 42;
            }
        }
        if (hidden) continue;
        auto& row = SC_Add(SC_Item::Row, {L, y, R, y + 52}, A_Row);
        row.entry = i;
        y += 58;
    }
    return y + 8;
}

static float SC_BuildDetails(SetWindow& w, float y) {
    const sc::Entry* e = SC_Sel();
    if (!e) {
        g_sc.mode = 0;
        return SC_BuildList(w, y);
    }
    float L = w.contentX, R = w.contentX + w.contentW, x = L;
    SC_AddPill(x, y, 34, L"Back", 0xE72B, A_Back);
    y += 48;
    auto& hero = SC_Add(SC_Item::Hero, {L, y, R, y + 92});
    hero.entry = SC_IndexOf(e->id);
    if (SC_Toggleable(*e)) {
        auto& sw = SC_Add(SC_Item::Switch, {R - 76, y + 30, R - 16, y + 62}, A_Switch, hero.entry);
        sw.entry = hero.entry;
    }
    y += 104;
    if ((e->kind == sc::Kind::Service || e->kind == sc::Kind::Driver) && e->writable) {
        auto& label = SC_Add(SC_Item::Label, {L, y, L + 64, y + 32});
        label.text = L"Starts";
        label.tone = 1;
        x = L + 64;
        DWORD first = e->kind == sc::Kind::Driver ? 0 : 2;
        for (DWORD m = first; m <= 4; m++) {
            if (x + SC_PillW(SC_ModeName(m), 0) > R) { x = L + 64; y += 40; }
            SC_AddPill(x, y, 32, SC_ModeName(m), 0, A_Mode, (int)m, 0, SC_Item::Chip).on = e->startMode == m;
        }
        y += 46;
    }
    struct P { PCWSTR text; WCHAR glyph; int act; int tone; };
    std::vector<P> pills;
    if (e->kind == sc::Kind::Task) {
        pills.push_back({L"Run now", 0xE768, A_Run, 1});
        pills.push_back({L"End", 0xE71A, A_End, 0});
        pills.push_back({L"Edit definition", 0xE70F, A_EditXml, 0});
        pills.push_back({g_sc.historyShown ? L"Hide history" : L"History", 0xE81C, A_History, 0});
    }
    if (!SC_Where(*e).empty() && e->kind != sc::Kind::Task) pills.push_back({L"Copy command", 0xE8C8, A_Copy, 0});
    if (!e->target.empty() && !e->missing && e->target.find(L":\\") != std::wstring::npos)
        pills.push_back({L"Show file", 0xE8B7, A_Reveal, 0});
    if (e->kind == sc::Kind::Task)
        pills.push_back({g_sc.confirmDelete ? L"Delete for good" : L"Delete", 0xE74D, A_Delete, g_sc.confirmDelete ? 2 : 0});
    x = L;
    for (auto& pl : pills) {
        if (x + SC_PillW(pl.text, pl.glyph) > R) { x = L; y += 44; }
        SC_AddPill(x, y, 36, pl.text, pl.glyph, pl.act, 0, pl.tone);
    }
    if (!pills.empty()) y += 52;
    std::vector<std::pair<std::wstring, std::wstring>> facts;
    auto fact = [&](PCWSTR k, const std::wstring& v) { if (!v.empty()) facts.push_back({k, v}); };
    fact(L"Kind", e->category);
    fact(L"Location", e->source);
    if (e->kind != sc::Kind::Task) fact(L"Command", e->command);
    fact(L"File", e->target + (e->missing ? L"  (missing)" : L""));
    fact(L"Runs as", e->user);
    if (e->kind == sc::Kind::Service || e->kind == sc::Kind::Driver) fact(L"Starts", SC_ModeName(e->startMode));
    fact(L"Details", e->detail);
    if (!e->target.empty() && !e->missing) fact(L"File date", sc::FileTimeText(e->target));
    y = SC_AddCard(w, y, L"About this entry", facts);
    if (e->kind == sc::Kind::Task) {
        if (g_sc.summaryLoading) y = SC_AddNote(w, y, L"Reading the task...");
        for (auto& s : g_sc.summary) y = SC_AddCard(w, y, s.title, s.rows);
        if (g_sc.historyShown) {
            if (g_sc.historyLoading) y = SC_AddNote(w, y, L"Reading the task history...");
            else if (g_sc.history.empty()) y = SC_AddNote(w, y, L"No history for this task. Windows may have task history turned off.");
            else {
                std::vector<std::pair<std::wstring, std::wstring>> rows;
                for (auto& h : g_sc.history) rows.push_back({h.when, h.what + (h.result.empty() ? L"" : L"  " + h.result)});
                y = SC_AddCard(w, y, L"History", rows);
            }
        }
    }
    return y + 8;
}

static float SC_BuildXml(SetWindow& w, float y) {
    const sc::Entry* e = SC_Sel();
    float L = w.contentX, R = w.contentX + w.contentW, x = L;
    SC_AddPill(x, y, 34, L"Cancel", 0xE72B, A_Back);
    SC_AddPill(x, y, 34, L"Check", 0xE73E, A_Check);
    SC_AddPill(x, y, 34, L"Save", 0xE74E, A_Save, 0, 1);
    y += 48;
    y = SC_AddNote(w, y, L"The task definition for " + (e ? e->name : std::wstring(L"this task")) +
                             L". Check tests it without saving. The original is kept in Changes.");
    float h = std::max(260.0f, w.ch - (y - w.scrollY) - Set_FootClear());
    SC_AddBox(SE_Xml, {L, y, R, y + h}, L"");
    return y + h + 12;
}

static float SC_BuildForm(SetWindow& w, float y) {
    float L = w.contentX, R = w.contentX + w.contentW, x = L;
    SC_AddPill(x, y, 34, L"Back", 0xE72B, A_Back);
    y += 50;
    y = SC_AddLabel(w, y, L"Name");
    SC_AddBox(SE_Name, {L, y, R, y + 38}, L"What to call the task");
    y += 50;
    y = SC_AddLabel(w, y, L"Program");
    x = R - SC_PillW(L"Browse", 0xE8E5);
    SC_AddBox(SE_Prog, {L, y, x - 8, y + 38}, L"The app or script to run");
    SC_AddPill(x, y, 38, L"Browse", 0xE8E5, A_Browse);
    y += 50;
    y = SC_AddLabel(w, y, L"Arguments (optional)");
    SC_AddBox(SE_Args, {L, y, R, y + 38}, L"Extra words passed to the program");
    y += 50;
    y = SC_AddLabel(w, y, L"When it runs");
    static const PCWSTR triggers[] = {L"When I sign in", L"When Windows starts", L"Every day", L"Once"};
    x = L;
    for (int i = 0; i < 4; i++) SC_AddPill(x, y, 32, triggers[i], 0, A_Trigger, i, 0, SC_Item::Chip).on = g_sc.trigger == i;
    y += 46;
    if (g_sc.trigger >= 2) {
        y = SC_AddLabel(w, y, L"Time (24 hour, like 09:30)");
        SC_AddBox(SE_Time, {L, y, L + 140, y + 38}, L"09:00");
        y += 50;
    }
    x = L;
    SC_AddPill(x, y, 38, L"Create task", 0xE710, A_Create, 0, 1);
    y += 52;
    return SC_AddNote(w, y, L"The task runs as you. Every new task is listed in Changes, so you can remove it from there.");
}

static float SC_BuildChanges(SetWindow& w, float y) {
    float L = w.contentX, R = w.contentX + w.contentW;
    if (g_sc.changes.empty())
        return SC_AddNote(w, y, L"Nothing changed yet. Each change made here keeps its original, so you can undo it from this page.");
    y = SC_AddNote(w, y, L"Newest first. Undo puts back the saved original.");
    for (int i = 0; i < (int)g_sc.changes.size(); i++) {
        const auto& c = g_sc.changes[i];
        auto& card = SC_Add(SC_Item::Change, {L, y, R, y + 76});
        card.arg = i;
        if (c.phase < 2) {
            float x = R - 14 - SC_PillW(L"Undo", 0xE7A7);
            SC_AddPill(x, y + 20, 36, L"Undo", 0xE7A7, A_Undo, i);
        }
        y += 84;
    }
    return y + 8;
}

static float SC_BuildPage(SetWindow& w, float y) {
    g_sc.items.clear();
    for (int k = 0; k < SE_Count; k++) g_sc.editWant[k] = false;
    if (w.page < 0 || w.page >= SC_Pages) return y;
    SC_EnsureFormats(w);
    if (g_sc.lastPage != w.page) {
        bool first = g_sc.lastPage < 0;
        g_sc.lastPage = w.page;
        g_sc.mode = 0;
        g_sc.show = 0;
        g_sc.confirmDelete = false;
        g_sc.cursorId.clear();
        if (!first && g_sc.edits[SE_Search]) SetWindowTextW(g_sc.edits[SE_Search], L"");
        g_sc.filter.clear();
        if (w.page == SC_ChangesPage) g_sc.changes = sc::ListChanges();
        SC_Filter(w);
    }
    if (w.page == SC_ChangesPage) return SC_BuildChanges(w, y);
    switch (g_sc.mode) {
        case 1: return SC_BuildDetails(w, y);
        case 2: return SC_BuildXml(w, y);
        case 3: return SC_BuildForm(w, y);
        default: return SC_BuildList(w, y);
    }
}

// ---- Drawing -------------------------------------------------------------------------------
static float SC_Glow(SetWindow& w, int i) { return Set_GlowOf(w, SC_HitBase + i); }
static float SC_KnobOf(const sc::Entry& e) {
    auto it = g_sc.knob.find(e.id);
    if (it != g_sc.knob.end()) return it->second;
    auto want = g_sc.want.find(e.id);
    return (want != g_sc.want.end() ? want->second : e.enabled) ? 1.0f : 0.0f;
}
static void SC_DrawSwitch(SetPaint& p, D2D1_RECT_F tr, float kn, float hov, bool busy) {
    p.Round(tr, 11, mocha::surface1, busy ? 0.6f : 1.0f);
    p.GradFill(tr, 11, kn * (busy ? 0.6f : 1.0f));
    p.GradRing(tr, 11, hov * 0.8f, 1.25f);
    float cx = tr.left + 11 + kn * (tr.right - tr.left - 22), cy = (tr.top + tr.bottom) / 2;
    p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8, 8), p.B(kn > 0.5f ? mocha::crust : mocha::text));
}
static void SC_DrawPill(SetPaint& p, SetWindow& w, const SC_Item& it, float hov) {
    D2D1_RECT_F r = it.r;
    float rad = (r.bottom - r.top) / 2;
    bool accent = it.tone == 1 || (it.type == SC_Item::Chip && it.on);
    UINT32 fg = mocha::text;
    if (accent) {
        p.Round(r, rad, mocha::surface0, 0.5f);
        p.GradFill(r, rad, it.type == SC_Item::Chip ? 0.9f : 0.85f + 0.15f * hov);
        fg = mocha::crust;
    } else if (it.tone == 2) {
        p.Round(r, rad, mocha::red, 0.22f + 0.12f * hov);
        p.Edge(r, rad, mocha::red, 0.8f, 1.25f);
        fg = mocha::red;
    } else {
        p.Round(r, rad, mocha::surface0, 0.55f);
        p.Edge(r, rad, mocha::surface2, 0.6f * (1 - hov));
        p.GradFill(r, rad, 0.12f * hov);
    }
    if (it.tone != 2) p.GradRing(r, rad, hov, 1.5f);
    float tw = Set_TextW(g_sc.fChip.get(), it.text), gw = it.glyph ? 22.0f : 0.0f;
    float left = (r.left + r.right) / 2 - (tw + gw) / 2;
    if (it.glyph) p.Glyph(w.fIconS.get(), it.glyph, {left, r.top, left + 16, r.bottom}, fg);
    p.Text(g_sc.fChip.get(), it.text, {left + gw - 2, r.top, left + gw + tw + 2, r.bottom}, fg);
}
static void SC_DrawBox(SetPaint& p, SetWindow& w, const SC_Item& it, float hov) {
    HWND edit = g_sc.edits[it.edit];
    bool focused = edit && GetFocus() == edit;
    p.Round(it.r, 8, kSetBoxFill);
    float g = std::max(hov, focused ? 1.0f : 0.0f);
    p.Edge(it.r, 8, mocha::overlay0, 0.7f * (1 - g), 1.25f);
    p.GradRing(it.r, 8, g, 1.75f);
    float left = it.r.left + 12;
    if (it.glyph) {
        p.Glyph(w.fIconS.get(), it.glyph, {left, it.r.top, left + 16, it.r.bottom}, mocha::overlay1);
        left += 24;
    }
    if (!g_sc.editShown[it.edit] && !it.text.empty())
        p.Text(w.fValue.get(), it.text, {left, it.r.top, it.r.right - 10, it.r.bottom}, mocha::overlay1);
}
static void SC_DrawRow(SetPaint& p, SetWindow& w, const SC_Item& it, float hov) {
    const sc::Entry& e = g_sc.entries[it.entry];
    D2D1_RECT_F r = it.r;
    Set_DrawCard(p, r, hov);
    p.GradFill(r, 10, 0.13f * hov);
    p.GradRing(r, 10, hov, 1.5f);
    if (g_sc.kbd && e.id == g_sc.cursorId) p.GradRing(r, 10, 1, 2);
    float mid = (r.top + r.bottom) / 2;
    D2D1_RECT_F icon{r.left + 12, mid - 16, r.left + 44, mid + 16};
    p.Round(icon, 9, mocha::surface0, 0.8f);
    p.Glyph(w.fIcon.get(), SC_Glyph(e), {icon.left, icon.top + 1, icon.right, icon.bottom}, e.enabled ? mocha::blue : mocha::overlay1);
    float right = r.right - (SC_Toggleable(e) ? 84 : 112);
    if (e.missing) {
        D2D1_RECT_F badge{right - 112, mid - 11, right - 8, mid + 11};
        p.Round(badge, 11, mocha::peach, 0.16f);
        p.Text(g_sc.fChip.get(), L"File missing", badge, mocha::peach);
        right = badge.left;
    }
    p.Text(g_sc.fName.get(), e.name.empty() ? e.value : e.name, {r.left + 56, r.top + 7, right - 8, r.top + 28},
           e.enabled ? mocha::text : mocha::subtext0);
    p.Text(g_sc.fSub.get(), SC_Where(e), {r.left + 56, r.top + 28, right - 8, r.bottom - 6}, mocha::overlay2);
    if (SC_Toggleable(e)) {
        SC_DrawSwitch(p, {r.right - 56, mid - 11, r.right - 16, mid + 11}, SC_KnobOf(e), hov, g_sc.want.count(e.id) > 0);
    } else {
        p.Glyph(w.fIconS.get(), 0xE72E, {r.right - 104, r.top, r.right - 88, r.bottom}, mocha::overlay1);
        p.Text(g_sc.fSub.get(), L"View only", {r.right - 84, r.top, r.right - 12, r.bottom}, mocha::overlay1);
    }
}
static void SC_DrawCardItem(SetPaint& p, SetWindow& w, const SC_Item& it) {
    Set_DrawCard(p, it.r, 0);
    float y = it.r.top + 12, vw = it.r.right - it.r.left - kScLabelW - 40;
    if (!it.text.empty()) {
        p.Text(g_sc.fHead.get(), SC_Upper(it.text), {it.r.left + 18, y, it.r.right - 18, y + 20}, mocha::overlay2);
        y += 30;
    }
    for (auto& row : it.rows) {
        float h = std::max(Set_TextH(w.fHint.get(), row.second, vw), 18.0f);
        p.Text(w.fHint.get(), row.first, {it.r.left + 18, y, it.r.left + 18 + kScLabelW - 8, y + h}, mocha::subtext0);
        p.Text(w.fHint.get(), row.second, {it.r.left + 18 + kScLabelW, y, it.r.right - 22, y + h + 2}, mocha::text);
        y += h + 10;
    }
}
static void SC_DrawItem(SetPaint& p, SetWindow& w, const SC_Item& it, int i) {
    float hov = it.act != A_None ? SC_Glow(w, i) : 0;
    switch (it.type) {
        case SC_Item::Box: SC_DrawBox(p, w, it, hov); break;
        case SC_Item::Chip:
        case SC_Item::Pill: SC_DrawPill(p, w, it, hov); break;
        case SC_Item::Icon: {
            p.Round(it.r, 10, mocha::surface0, 0.55f);
            p.Edge(it.r, 10, mocha::surface2, 0.6f * (1 - hov));
            p.GradFill(it.r, 10, 0.12f * hov);
            p.GradRing(it.r, 10, hov, 1.5f);
            p.Glyph(w.fIcon.get(), it.glyph, {it.r.left, it.r.top + 1, it.r.right, it.r.bottom}, it.on ? mocha::blue : mocha::text);
            break;
        }
        case SC_Item::Head: {
            UINT32 c = hov > 0.5f ? mocha::text : mocha::overlay2;
            p.Glyph(w.fIconS.get(), it.on ? 0xE70D : 0xE76C, {it.r.left, it.r.top, it.r.left + 16, it.r.bottom}, c);
            std::wstring t = SC_Upper(it.text);
            float tw = Set_TextW(g_sc.fHead.get(), t);
            p.Text(g_sc.fHead.get(), t, {it.r.left + 22, it.r.top, it.r.left + 22 + tw + 4, it.r.bottom}, c);
            p.Text(g_sc.fSub.get(), it.sub, {it.r.left + 34 + tw, it.r.top, it.r.right, it.r.bottom}, mocha::overlay1);
            break;
        }
        case SC_Item::Row: SC_DrawRow(p, w, it, hov); break;
        case SC_Item::Note: p.Text(w.fHint.get(), it.text, it.r, mocha::subtext0); break;
        case SC_Item::Label:
            if (it.tone == 1) p.Text(g_sc.fSub.get(), it.text, it.r, mocha::subtext0);
            else p.Text(w.fHint.get(), it.text, it.r, mocha::subtext1);
            break;
        case SC_Item::Hero: {
            if (it.entry < 0) break;
            const sc::Entry& e = g_sc.entries[it.entry];
            Set_DrawCard(p, it.r, 0);
            D2D1_RECT_F icon{it.r.left + 18, it.r.top + 20, it.r.left + 70, it.r.top + 72};
            p.GradFill(icon, 14, e.enabled ? 0.9f : 0.25f);
            p.Glyph(w.fIcon.get(), SC_Glyph(e), {icon.left, icon.top + 1, icon.right, icon.bottom}, e.enabled ? mocha::crust : mocha::text);
            float right = it.r.right - (SC_Toggleable(e) ? 96 : 18);
            p.Text(w.fBig.get(), e.name.empty() ? e.value : e.name, {it.r.left + 86, it.r.top + 18, right, it.r.top + 48}, mocha::text);
            std::wstring state = sc::State(e);
            if (e.kind == sc::Kind::Service || e.kind == sc::Kind::Driver) state += std::wstring(L" · Starts: ") + SC_ModeName(e.startMode);
            if (g_sc.want.count(e.id)) state += L" · Working...";
            p.Text(g_sc.fSub.get(), state, {it.r.left + 86, it.r.top + 52, right, it.r.top + 72}, e.missing ? mocha::peach : mocha::subtext0);
            break;
        }
        case SC_Item::Switch: {
            if (it.entry < 0) break;
            const sc::Entry& e = g_sc.entries[it.entry];
            float mid = (it.r.top + it.r.bottom) / 2;
            SC_DrawSwitch(p, {it.r.right - 44, mid - 11, it.r.right - 4, mid + 11}, SC_KnobOf(e), hov, g_sc.want.count(e.id) > 0);
            break;
        }
        case SC_Item::Card: SC_DrawCardItem(p, w, it); break;
        case SC_Item::Change: {
            if (it.arg < 0 || it.arg >= (int)g_sc.changes.size()) break;
            const auto& c = g_sc.changes[it.arg];
            Set_DrawCard(p, it.r, 0);
            float right = it.r.right - 120;
            static const PCWSTR phases[] = {L"Not finished", L"Done", L"Undone"};
            p.Text(g_sc.fName.get(), c.subject, {it.r.left + 18, it.r.top + 9, right, it.r.top + 30}, c.phase == 2 ? mocha::subtext0 : mocha::text);
            p.Text(g_sc.fSub.get(), c.operation + L" · " + c.location, {it.r.left + 18, it.r.top + 31, right, it.r.top + 50}, mocha::overlay2);
            std::wstring when = sc::FileTimeText(c.path);
            p.Text(g_sc.fSub.get(), when + (when.empty() ? L"" : L" · ") + phases[std::min<DWORD>(c.phase, 2)],
                   {it.r.left + 18, it.r.top + 51, right, it.r.top + 70}, c.phase == 0 ? mocha::peach : mocha::overlay1);
            break;
        }
    }
}
static void SC_DrawPage(SetPaint& p, SetWindow& w, float viewH, const D2D1_MATRIX_3X2_F& base) {
    if (w.page < 0 || w.page >= SC_Pages) return;
    SC_EnsureFormats(w);
    for (size_t i = 0; i < g_sc.items.size(); i++) {
        const SC_Item& it = g_sc.items[i];
        if (it.r.bottom < w.scrollY - 20 || it.r.top > w.scrollY + viewH + 20) continue;
        float t = w.pageT >= 1 ? 1.0f : Set_Ease(w.pageT * 1.7f - std::min((int)i + 2, 9) * 0.07f);
        p.fade = t;
        p.rt->SetTransform(D2D1::Matrix3x2F::Translation(0, -w.scrollY + (1 - t) * 10) * *D2D1::Matrix3x2F::ReinterpretBaseType(&base));
        SC_DrawItem(p, w, it, (int)i);
    }
    p.fade = 1;
}

// ---- Hit testing ---------------------------------------------------------------------------
static bool SC_Hit(SetWindow& w, float x, float cy, SetHit& h) {
    if (w.page < 0 || w.page >= SC_Pages) return false;
    for (int i = (int)g_sc.items.size() - 1; i >= 0; i--) {
        const SC_Item& it = g_sc.items[i];
        if (it.act == A_None || !Set_In(it.r, x, cy)) continue;
        h.kind = SetHit::Link;
        h.a = i;
        h.id = SC_HitBase + i;
        return true;
    }
    return false;
}

// ---- Edits ---------------------------------------------------------------------------------
static void SC_Rebuild(SetWindow& w) { Set_BuildAndClamp(w); }
static void SC_GoMode(SetWindow& w, int mode) {
    g_sc.mode = mode;
    g_sc.confirmDelete = false;
    w.scrollY = w.scrollTarget = 0;
    if (w.hwnd && GetFocus() != w.hwnd) {
        HWND f = GetFocus();
        for (HWND e : g_sc.edits)
            if (e && e == f) SetFocus(w.hwnd);
    }
    SC_Rebuild(w);
}
static void SC_Back(SetWindow& w) {
    if (g_sc.mode == 2) SC_GoMode(w, 1);
    else if (g_sc.mode != 0) SC_GoMode(w, 0);
}
static void SC_PlaceEdits(SetWindow& w);
static void SC_FocusEdit(SetWindow& w, int k) {
    if (!g_sc.edits[k] || !g_sc.editWant[k]) return;
    g_sc.editForce[k] = true;
    const D2D1_RECT_F& r = g_sc.editRect[k];
    Set_EnsureVisible(w, r.top - 8, r.bottom + 8);
    w.scrollY = w.scrollTarget;
    SC_PlaceEdits(w);
    SetFocus(g_sc.edits[k]);
    SendMessageW(g_sc.edits[k], EM_SETSEL, 0, -1);
    Set_Invalidate(w);
}
static void SC_Create(SetWindow& w);
static void SC_MoveCursor(SetWindow& w, int delta);
static LRESULT CALLBACK SC_EditProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR ref) {
    int k = (int)ref;
    SetWindow* w = g_setWin.get();
    if (w) {
        bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0, shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
        switch (msg) {
            case WM_KEYDOWN:
                if (wp == 'A' && ctrl) { SendMessageW(hwnd, EM_SETSEL, 0, -1); return 0; }
                if (wp == VK_ESCAPE) {
                    if (k == SE_Search && GetWindowTextLengthW(hwnd) > 0) { SetWindowTextW(hwnd, L""); return 0; }
                    SetFocus(w->hwnd);
                    if (k != SE_Search) SC_Back(*w);
                    Set_Invalidate(*w);
                    return 0;
                }
                if (k == SE_Search && (wp == VK_RETURN || wp == VK_DOWN)) {
                    SetFocus(w->hwnd);
                    g_sc.kbd = true;
                    g_sc.cursorId.clear();
                    SC_MoveCursor(*w, 1);
                    return 0;
                }
                if (k >= SE_Name && wp == VK_RETURN) { SC_Create(*w); return 0; }
                if (wp == VK_TAB) {
                    if (k == SE_Xml) { SendMessageW(hwnd, EM_REPLACESEL, TRUE, (LPARAM)L"  "); return 0; }
                    if (k >= SE_Name) {
                        int order[] = {SE_Name, SE_Prog, SE_Args, SE_Time}, n = g_sc.trigger >= 2 ? 4 : 3, at = 0;
                        for (int i = 0; i < n; i++) if (order[i] == k) at = i;
                        SC_FocusEdit(*w, order[(at + (shift ? n - 1 : 1)) % n]);
                        return 0;
                    }
                }
                break;
            case WM_CHAR:
                if (wp == 1 && ctrl) return 0;  // Ctrl+A, handled above, would beep.
                if (wp == VK_ESCAPE || wp == VK_TAB) return 0;
                if (wp == VK_RETURN && k != SE_Xml) return 0;
                break;
            case WM_MBUTTONDOWN:
            case WM_MOUSEWHEEL:
                if (k != SE_Xml || msg == WM_MBUTTONDOWN) {
                    if (msg == WM_MBUTTONDOWN) {
                        POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
                        MapWindowPoints(hwnd, w->hwnd, &pt, 1);
                        SetFocus(w->hwnd);
                        return SendMessageW(w->hwnd, msg, wp, MAKELPARAM(pt.x, pt.y));
                    }
                    return SendMessageW(w->hwnd, msg, wp, lp);
                }
                break;
            case WM_NCDESTROY: RemoveWindowSubclass(hwnd, SC_EditProc, 77); break;
        }
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}
static void SC_MakeEdits(SetWindow& w) {
    std::wstring keep[SE_Count];
    for (int k = 0; k < SE_Count; k++) {
        keep[k] = SC_Text(g_sc.edits[k]);
        if (g_sc.edits[k]) DestroyWindow(g_sc.edits[k]);
        g_sc.edits[k] = nullptr;
        g_sc.editShown[k] = false;
        g_sc.editPx[k] = {};
    }
    if (g_sc.font) DeleteObject(g_sc.font);
    if (g_sc.mono) DeleteObject(g_sc.mono);
    g_sc.font = CreateFontW(-MulDiv(13, w.dpi, 96), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, w.family.c_str());
    g_sc.mono = CreateFontW(-MulDiv(12, w.dpi, 96), 0, 0, 0, 400, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FIXED_PITCH, L"FiraCode Nerd Font");
    if (keep[SE_Time].empty()) keep[SE_Time] = L"09:00";
    for (int k = 0; k < SE_Count; k++) {
        DWORD style = WS_CHILD | (k == SE_Xml ? ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN | WS_VSCROLL | ES_NOHIDESEL : ES_AUTOHSCROLL);
        HWND e = CreateWindowExW(w.glass ? WS_EX_LAYERED : 0, L"EDIT", L"", style, 0, 0, 10, 10, w.hwnd,
                                 (HMENU)(INT_PTR)(SC_ID_EDIT + k), GetModuleHandleW(nullptr), nullptr);
        if (!e) continue;
        if (w.glass) SetLayeredWindowAttributes(e, 0, 255, LWA_ALPHA);
        if (k == SE_Xml) SetWindowTheme(e, L"DarkMode_Explorer", nullptr);
        SendMessageW(e, WM_SETFONT, (WPARAM)(k == SE_Xml ? g_sc.mono : g_sc.font), FALSE);
        SendMessageW(e, EM_SETLIMITTEXT, k == SE_Xml ? 4 * 1024 * 1024 : (k == SE_Time ? 5 : 1024), 0);
        SetWindowTextW(e, keep[k].c_str());
        SetWindowSubclass(e, SC_EditProc, 77, (DWORD_PTR)k);
        g_sc.edits[k] = e;
    }
}
static void SC_PlaceEdits(SetWindow& w) {
    float s = w.dpi / 96.0f, viewH = Set_ViewH(w), limit = viewH - kSetFootH - kSetFootGap;
    HWND focus = GetFocus();
    for (int k = 0; k < SE_Count; k++) {
        HWND e = g_sc.edits[k];
        if (!e) continue;
        const D2D1_RECT_F& r = g_sc.editRect[k];
        float top = r.top - w.scrollY, bottom = r.bottom - w.scrollY;
        bool active = focus == e || g_sc.editForce[k] || k == SE_Xml || GetWindowTextLengthW(e) > 0;
        bool show = g_sc.editWant[k] && active && w.page < SC_Pages && w.pageT >= 1 && w.openSel < 0 && !w.saving &&
                    top >= 0 && bottom <= limit;
        g_sc.editForce[k] = false;
        if (!show) {
            if (g_sc.editShown[k]) {
                if (focus == e) SetFocus(w.hwnd);
                ShowWindow(e, SW_HIDE);
                g_sc.editShown[k] = false;
                Set_Invalidate(w);
            }
            continue;
        }
        float left = r.left + (k == SE_Search ? 36 : 12), right = r.right - 10, y0, y1;
        if (k == SE_Xml) { y0 = top + 8; y1 = bottom - 8; left = r.left + 10; right = r.right - 4; }
        else { float mid = (top + bottom) / 2; y0 = mid - 10; y1 = mid + 10; }
        RECT px{(int)(left * s), (int)((y0 + kSetCapH) * s), (int)(right * s), (int)((y1 + kSetCapH) * s)};
        if (!g_sc.editShown[k] || memcmp(&px, &g_sc.editPx[k], sizeof(px)) != 0) {
            SetWindowPos(e, HWND_TOP, px.left, px.top, px.right - px.left, px.bottom - px.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
            g_sc.editPx[k] = px;
            if (!g_sc.editShown[k]) Set_Invalidate(w);
            g_sc.editShown[k] = true;
        }
    }
}
static void SC_Layout(SetWindow& w) {
    if (w.render || !w.hwnd) return;
    if (g_sc.hwnd != w.hwnd) {
        g_sc.hwnd = w.hwnd;
        g_sc.dpi = w.dpi;
        g_sc.glass = w.glass;
        SC_MakeEdits(w);
        SC_Refresh(w);
    } else if (g_sc.dpi != w.dpi || g_sc.glass != w.glass) {
        g_sc.dpi = w.dpi;
        g_sc.glass = w.glass;
        SC_MakeEdits(w);
    }
    SC_PlaceEdits(w);
}

// ---- Actions -------------------------------------------------------------------------------
static void SC_OpenDetails(SetWindow& w, int idx) {
    if (idx < 0 || idx >= (int)g_sc.entries.size()) return;
    const sc::Entry e = g_sc.entries[idx];
    g_sc.selId = e.id;
    g_sc.cursorId = e.id;
    g_sc.summary.clear();
    g_sc.history.clear();
    g_sc.historyShown = g_sc.historyLoading = false;
    g_sc.summaryLoading = e.kind == sc::Kind::Task;
    SC_GoMode(w, 1);
    if (e.kind == sc::Kind::Task)
        SC_RunAsync(w.hwnd, [path = e.key, id = e.id](SC_Result& r) {
            r.kind = R_Summary;
            r.id = id;
            r.summary = sc::TaskSummary(path);
        });
}
static void SC_Toggle(SetWindow& w, int idx) {
    if (idx < 0 || idx >= (int)g_sc.entries.size()) return;
    const sc::Entry e = g_sc.entries[idx];
    if (!SC_Toggleable(e)) { SC_Status(w, L"This entry is view only."); return; }
    if (g_sc.want.count(e.id)) return;
    bool to = !e.enabled;
    if ((e.kind == sc::Kind::Service || e.kind == sc::Kind::Driver) && to) {
        if (g_sc.mode != 1) SC_OpenDetails(w, idx);
        SC_Status(w, L"Pick how it should start. That turns it back on.");
        return;
    }
    if (e.kind == sc::Kind::Device && !to && Wh_GetIntSetting(L"confirmDevices") != 0 && g_sc.confirmId != e.id) {
        g_sc.confirmId = e.id;
        SC_Status(w, L"Turning off a device can stop it working until you turn it back on. Click again to turn it off.");
        return;
    }
    g_sc.confirmId.clear();
    g_sc.want[e.id] = to;
    if (!g_sc.knob.count(e.id)) g_sc.knob[e.id] = e.enabled ? 1.0f : 0.0f;
    SC_Status(w, to ? L"Turning on..." : L"Turning off...");
    SC_RunAsync(w.hwnd, [e, to](SC_Result& r) {
        r.kind = R_Toggle;
        r.id = e.id;
        r.on = to;
        std::wstring receipt;
        r.hr = e.kind == sc::Kind::Device ? sc::DeviceSetEnabled(e, to, receipt) : sc::ToggleEntry(e, to, receipt);
    });
}
static void SC_SetMode(SetWindow& w, DWORD mode) {
    const sc::Entry* sel = SC_Sel();
    if (!sel || g_sc.want.count(sel->id)) return;
    const sc::Entry e = *sel;
    if (e.startMode == mode) return;
    g_sc.want[e.id] = mode != SERVICE_DISABLED;
    if (!g_sc.knob.count(e.id)) g_sc.knob[e.id] = e.enabled ? 1.0f : 0.0f;
    SC_Status(w, L"Changing how it starts...");
    SC_RunAsync(w.hwnd, [e, mode](SC_Result& r) {
        r.kind = R_Mode;
        r.id = e.id;
        r.value = mode;
        std::wstring receipt;
        r.hr = sc::SetServiceMode(e, mode, receipt);
    });
}
static bool SC_CopyText(HWND hwnd, const std::wstring& s) {
    if (!OpenClipboard(hwnd)) return false;
    EmptyClipboard();
    bool ok = false;
    if (HGLOBAL g = GlobalAlloc(GMEM_MOVEABLE, (s.size() + 1) * sizeof(wchar_t))) {
        if (void* p = GlobalLock(g)) {
            memcpy(p, s.c_str(), (s.size() + 1) * sizeof(wchar_t));
            GlobalUnlock(g);
            ok = SetClipboardData(CF_UNICODETEXT, g) != nullptr;
        }
        if (!ok) GlobalFree(g);
    }
    CloseClipboard();
    return ok;
}
static std::wstring SC_Crlf(const std::wstring& s) {
    std::wstring out;
    out.reserve(s.size() + s.size() / 20);
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == L'\n' && (i == 0 || s[i - 1] != L'\r')) out += L'\r';
        out += s[i];
    }
    return out;
}
static void SC_Browse(SetWindow& w) {
    wchar_t file[MAX_PATH]{};
    std::wstring cur = SC_Text(g_sc.edits[SE_Prog]);
    wcsncpy_s(file, cur.c_str(), _TRUNCATE);
    OPENFILENAMEW o{sizeof(o)};
    o.hwndOwner = w.hwnd;
    o.lpstrFilter = L"Programs and scripts\0*.exe;*.cmd;*.bat;*.ps1;*.vbs\0All files\0*.*\0";
    o.lpstrFile = file;
    o.nMaxFile = MAX_PATH;
    o.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
    if (GetOpenFileNameW(&o)) {
        SetWindowTextW(g_sc.edits[SE_Prog], file);
        if (SC_Text(g_sc.edits[SE_Name]).empty()) {
            std::wstring name = PathFindFileNameW(file);
            auto dot = name.find_last_of(L'.');
            SetWindowTextW(g_sc.edits[SE_Name], name.substr(0, dot).c_str());
        }
        Set_Invalidate(w);
    }
}
static void SC_Create(SetWindow& w) {
    std::wstring name = SC_Text(g_sc.edits[SE_Name]), prog = SC_Text(g_sc.edits[SE_Prog]), args = SC_Text(g_sc.edits[SE_Args]);
    std::wstring time = SC_Text(g_sc.edits[SE_Time]);
    while (!prog.empty() && (prog.front() == L'"' || prog.front() == L' ')) prog.erase(prog.begin());
    while (!prog.empty() && (prog.back() == L'"' || prog.back() == L' ')) prog.pop_back();
    if (name.empty()) { SC_Status(w, L"Give the task a name.", true); SC_FocusEdit(w, SE_Name); return; }
    if (name.find_first_of(L"\\/:*?\"<>|") != std::wstring::npos) {
        SC_Status(w, L"A task name cannot use \\ / : * ? \" < > or |.", true);
        SC_FocusEdit(w, SE_Name);
        return;
    }
    if (prog.empty()) { SC_Status(w, L"Pick the program it should run.", true); SC_FocusEdit(w, SE_Prog); return; }
    int hour = 9, minute = 0;
    if (g_sc.trigger >= 2 && (swscanf_s(time.c_str(), L"%d:%d", &hour, &minute) != 2 || hour < 0 || hour > 23 || minute < 0 || minute > 59)) {
        SC_Status(w, L"Type the time like 09:30.", true);
        SC_FocusEdit(w, SE_Time);
        return;
    }
    std::wstring dir = prog;
    auto slash = dir.find_last_of(L'\\');
    dir = slash == std::wstring::npos ? L"" : dir.substr(0, slash);
    std::wstring xml = sc::TaskXmlFor(prog, args, dir, g_sc.trigger, hour, minute);
    SC_Status(w, L"Creating the task...");
    SC_RunAsync(w.hwnd, [path = L"\\" + name, xml](SC_Result& r) {
        r.kind = R_Create;
        r.text = path;
        std::wstring receipt;
        r.hr = sc::CreateTask(path, xml, receipt);
    });
}
static void SC_Do(SetWindow& w, int i, float x) {
    if (i < 0 || i >= (int)g_sc.items.size()) return;
    const SC_Item it = g_sc.items[i];
    const sc::Entry* sel = SC_Sel();
    if (it.act != A_Delete) g_sc.confirmDelete = false;
    switch (it.act) {
        case A_Row:
            g_sc.cursorId = g_sc.entries[it.entry].id;
            if (x >= it.r.right - 72 && SC_Toggleable(g_sc.entries[it.entry])) SC_Toggle(w, it.entry);
            else SC_OpenDetails(w, it.entry);
            Set_Invalidate(w);
            break;
        case A_Switch: SC_Toggle(w, it.entry); Set_Invalidate(w); break;
        case A_Head: g_sc.collapsed[it.text] = it.on; SC_Rebuild(w); break;
        case A_Show: g_sc.show = it.arg; SC_Filter(w); SC_Rebuild(w); break;
        case A_Sort: g_sc.sort = it.arg; SC_Filter(w); SC_Rebuild(w); break;
        case A_Refresh: SC_Refresh(w); SC_Rebuild(w); break;
        case A_NewTask: SC_GoMode(w, 3); SC_FocusEdit(w, SE_Name); break;
        case A_Back: SC_Back(w); break;
        case A_Box: SC_FocusEdit(w, it.edit); break;
        case A_Mode: SC_SetMode(w, (DWORD)it.arg); break;
        case A_Run:
        case A_End:
            if (!sel) break;
            SC_Status(w, it.act == A_Run ? L"Starting the task..." : L"Ending the task...");
            SC_RunAsync(w.hwnd, [path = sel->key, stop = it.act == A_End](SC_Result& r) {
                r.kind = R_Run;
                r.on = stop;
                r.hr = sc::TaskRun(path, stop);
            });
            break;
        case A_EditXml:
            if (!sel) break;
            SC_Status(w, L"Reading the task definition...");
            SC_RunAsync(w.hwnd, [path = sel->key, id = sel->id](SC_Result& r) {
                r.kind = R_Xml;
                r.id = id;
                sc::TaskConnection c;
                if (FAILED(c.status)) { r.hr = c.status; return; }
                auto task = c.Task(path);
                if (!task) { r.hr = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND); return; }
                r.text = sc::TaskXml(task.Get());
                if (r.text.empty()) r.hr = E_FAIL;
            });
            break;
        case A_History:
            if (!sel) break;
            g_sc.historyShown = !g_sc.historyShown;
            if (g_sc.historyShown) {
                g_sc.historyLoading = true;
                SC_RunAsync(w.hwnd, [path = sel->key, id = sel->id](SC_Result& r) {
                    r.kind = R_History;
                    r.id = id;
                    r.history = sc::ParseHistory(sc::TaskHistory(path));
                });
            }
            SC_Rebuild(w);
            break;
        case A_Copy:
            if (sel) SC_Status(w, SC_CopyText(w.hwnd, sel->command.empty() ? SC_WhereRaw(*sel) : sel->command) ? L"Copied." : L"Could not reach the clipboard.");
            break;
        case A_Reveal:
            if (sel) ShellExecuteW(nullptr, L"open", L"explorer.exe", (L"/select,\"" + sel->target + L"\"").c_str(), nullptr, SW_SHOWNORMAL);
            break;
        case A_Delete:
            if (!sel) break;
            if (!g_sc.confirmDelete) {
                g_sc.confirmDelete = true;
                SC_Status(w, L"Click Delete for good to remove this task. Its definition stays in Changes.");
                SC_Rebuild(w);
                break;
            }
            g_sc.confirmDelete = false;
            SC_Status(w, L"Deleting the task...");
            SC_RunAsync(w.hwnd, [path = sel->key, id = sel->id](SC_Result& r) {
                r.kind = R_Delete;
                r.id = id;
                std::wstring receipt;
                r.hr = sc::DeleteTask(path, receipt);
            });
            SC_Rebuild(w);
            break;
        case A_Trigger: g_sc.trigger = it.arg; SC_Rebuild(w); break;
        case A_Browse: SC_Browse(w); break;
        case A_Create: SC_Create(w); break;
        case A_Check:
        case A_Save: {
            if (!sel) break;
            std::wstring xml = SC_Text(g_sc.edits[SE_Xml]);
            SC_Status(w, it.act == A_Check ? L"Checking..." : L"Saving...");
            SC_RunAsync(w.hwnd, [path = sel->key, xml, original = g_sc.xmlOriginal, save = it.act == A_Save](SC_Result& r) {
                r.kind = save ? R_Save : R_Check;
                std::wstring receipt;
                r.hr = save ? sc::UpdateTask(path, original, xml, receipt) : sc::RegisterXml(path, xml, true, true);
            });
            break;
        }
        case A_Undo:
            if (it.arg < 0 || it.arg >= (int)g_sc.changes.size()) break;
            SC_Status(w, L"Undoing...");
            SC_RunAsync(w.hwnd, [path = g_sc.changes[it.arg].path](SC_Result& r) {
                r.kind = R_Undo;
                r.hr = sc::UndoAny(path);
            });
            break;
    }
}
static void SC_OnDone(SetWindow& w, SC_Result& r) {
    int idx = SC_IndexOf(r.id);
    switch (r.kind) {
        case R_Toggle:
        case R_Mode: {
            g_sc.want.erase(r.id);
            if (SUCCEEDED(r.hr) && idx >= 0) {
                auto& e = g_sc.entries[idx];
                if (r.kind == R_Mode) {
                    e.startMode = r.value;
                    e.enabled = r.value != SERVICE_DISABLED;
                    SC_Status(w, (e.name + L" now starts: " + SC_ModeName(r.value) + L".").c_str());
                } else {
                    e.enabled = r.on;
                    if ((e.kind == sc::Kind::Service || e.kind == sc::Kind::Driver) && !r.on) e.startMode = SERVICE_DISABLED;
                    SC_Status(w, (std::wstring(r.on ? L"Turned on " : L"Turned off ") + e.name + L".").c_str());
                }
                SC_Filter(w);
            } else if (FAILED(r.hr)) SC_Status(w, SC_ErrorText(r.hr), true);
            SC_Rebuild(w);
            break;
        }
        case R_Run:
            if (SUCCEEDED(r.hr)) SC_Status(w, r.on ? L"Asked the task to end." : L"The task is starting.");
            else SC_Status(w, SC_ErrorText(r.hr), true);
            break;
        case R_Summary:
            if (r.id != g_sc.selId) break;
            g_sc.summary = std::move(r.summary);
            g_sc.summaryLoading = false;
            SC_Rebuild(w);
            break;
        case R_History:
            if (r.id != g_sc.selId) break;
            g_sc.history = std::move(r.history);
            g_sc.historyLoading = false;
            SC_Rebuild(w);
            break;
        case R_Xml:
            if (r.id != g_sc.selId || g_sc.mode != 1) break;
            if (FAILED(r.hr)) { SC_Status(w, SC_ErrorText(r.hr), true); break; }
            g_sc.xmlOriginal = r.text;
            if (g_sc.edits[SE_Xml]) SetWindowTextW(g_sc.edits[SE_Xml], SC_Crlf(r.text).c_str());
            SC_Status(w, L"");
            SC_GoMode(w, 2);
            break;
        case R_Check:
            if (SUCCEEDED(r.hr)) SC_Status(w, L"The definition is valid. Nothing was saved.");
            else SC_Status(w, L"Windows does not accept it: " + SC_ErrorText(r.hr), true);
            break;
        case R_Save:
            if (FAILED(r.hr)) { SC_Status(w, L"Not saved: " + SC_ErrorText(r.hr), true); break; }
            SC_Status(w, L"Saved. The original is in Changes.");
            if (g_sc.mode == 2) {
                const sc::Entry* sel = SC_Sel();
                if (sel) SC_OpenDetails(w, SC_IndexOf(sel->id));
            }
            SC_Refresh(w);
            break;
        case R_Delete:
            if (FAILED(r.hr)) { SC_Status(w, SC_ErrorText(r.hr), true); break; }
            if (idx >= 0) {
                g_sc.entries.erase(g_sc.entries.begin() + idx);
                SC_Reindex();
                SC_Filter(w);
            }
            SC_Status(w, L"Task deleted. You can bring it back from Changes.");
            if (r.id == g_sc.selId) SC_GoMode(w, 0);
            else SC_Rebuild(w);
            break;
        case R_Create:
            if (FAILED(r.hr)) { SC_Status(w, L"Not created: " + SC_ErrorText(r.hr), true); break; }
            SC_Status(w, L"Created " + r.text.substr(1) + L".");
            for (int k : {SE_Name, SE_Prog, SE_Args})
                if (g_sc.edits[k]) SetWindowTextW(g_sc.edits[k], L"");
            SC_GoMode(w, 0);
            SC_Refresh(w);
            break;
        case R_Undo:
            if (FAILED(r.hr)) SC_Status(w, L"Could not undo: " + SC_ErrorText(r.hr), true);
            else SC_Status(w, L"Put back the original.");
            g_sc.changes = sc::ListChanges();
            SC_Rebuild(w);
            if (SUCCEEDED(r.hr)) SC_Refresh(w);
            break;
    }
}

// ---- Keyboard ------------------------------------------------------------------------------
static void SC_MoveCursor(SetWindow& w, int delta) {
    std::vector<int> rows;
    int at = -1;
    for (int i = 0; i < (int)g_sc.items.size(); i++) {
        if (g_sc.items[i].type != SC_Item::Row) continue;
        if (g_sc.entries[g_sc.items[i].entry].id == g_sc.cursorId) at = (int)rows.size();
        rows.push_back(i);
    }
    if (rows.empty()) return;
    int next = at < 0 ? (delta > 0 ? 0 : (int)rows.size() - 1) : std::clamp(at + delta, 0, (int)rows.size() - 1);
    const SC_Item& it = g_sc.items[rows[next]];
    g_sc.cursorId = g_sc.entries[it.entry].id;
    Set_EnsureVisible(w, it.r.top - 8, it.r.bottom + 8);
    Set_Invalidate(w);
}
static int SC_CursorEntry() {
    for (auto& it : g_sc.items)
        if (it.type == SC_Item::Row && g_sc.entries[it.entry].id == g_sc.cursorId) return it.entry;
    return -1;
}
static bool SC_Key(SetWindow& w, UINT vk) {
    bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
    if (vk == VK_F5) { SC_Refresh(w); SC_Rebuild(w); return true; }
    if (w.page == SC_ChangesPage) return false;
    if (g_sc.mode != 0) {
        if (vk == VK_ESCAPE || vk == VK_BACK) { SC_Back(w); return true; }
        if (g_sc.mode == 1 && vk == VK_SPACE) {
            const sc::Entry* sel = SC_Sel();
            if (sel) SC_Toggle(w, SC_IndexOf(sel->id));
            return true;
        }
        return false;
    }
    if ((vk == 'F' && ctrl) || vk == VK_OEM_2) { SC_FocusEdit(w, SE_Search); return true; }
    float viewH = Set_ViewH(w), maxScroll = std::max(0.0f, w.contentH - viewH);
    switch (vk) {
        case VK_DOWN: g_sc.kbd = true; SC_MoveCursor(w, 1); return true;
        case VK_UP: g_sc.kbd = true; SC_MoveCursor(w, -1); return true;
        case VK_NEXT: g_sc.kbd = true; SC_MoveCursor(w, std::max(1, (int)(viewH / 58))); return true;
        case VK_PRIOR: g_sc.kbd = true; SC_MoveCursor(w, -std::max(1, (int)(viewH / 58))); return true;
        case VK_HOME: g_sc.kbd = true; g_sc.cursorId.clear(); SC_MoveCursor(w, 1); w.scrollTarget = 0; return true;
        case VK_END: g_sc.kbd = true; g_sc.cursorId.clear(); SC_MoveCursor(w, -1); w.scrollTarget = maxScroll; return true;
        case VK_RETURN: if (SC_CursorEntry() >= 0) { SC_OpenDetails(w, SC_CursorEntry()); return true; } return false;
        case VK_SPACE: if (SC_CursorEntry() >= 0) { SC_Toggle(w, SC_CursorEntry()); Set_Invalidate(w); return true; } return false;
        case VK_ESCAPE:
            if (!g_sc.filter.empty()) { SetWindowTextW(g_sc.edits[SE_Search], L""); return true; }
            return false;
    }
    return false;
}

// ---- Window messages -----------------------------------------------------------------------
static bool SC_Message(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, LRESULT& result) {
    // The window runs elevated, so the taskbar cannot ask it for its icon and falls back to
    // the class icon. Mirror every icon the window gets onto its class so the taskbar sees it.
    if (msg == WM_SETICON && (wp == ICON_BIG || wp == ICON_SMALL)) {
        result = DefWindowProcW(hwnd, msg, wp, lp);
        SetClassLongPtrW(hwnd, wp == ICON_BIG ? GCLP_HICON : GCLP_HICONSM, lp);
        return true;
    }
    if (msg == WM_NCDESTROY) {
        SetClassLongPtrW(hwnd, GCLP_HICON, 0);
        SetClassLongPtrW(hwnd, GCLP_HICONSM, 0);
    }
    SetWindow* pw = g_setWin.get();
    if (!pw || pw->hwnd != hwnd) return false;
    SetWindow& w = *pw;
    switch (msg) {
        case sc::WM_SC_DATA: {
            {
                std::lock_guard<std::mutex> guard(sc::g_dataMutex);
                g_sc.entries = sc::g_inventory.entries;
                g_sc.errors = sc::g_inventory.errors;
            }
            g_sc.loaded = true;
            g_sc.scanning = false;
            g_sc.knob.clear();
            SC_Reindex();
            SC_Filter(w);
            size_t n = 0;
            for (auto& e : g_sc.entries) if (e.kind != sc::Kind::Notice) n++;
            (void)n;
            SC_Status(w, L"");
            if (g_sc.mode != 0 && !SC_Sel()) g_sc.mode = 0;
            SC_Rebuild(w);
            result = 0;
            return true;
        }
        case SC_WM_DONE: {
            std::unique_ptr<SC_Result> r((SC_Result*)lp);
            if (r) SC_OnDone(w, *r);
            result = 0;
            return true;
        }
        case WM_APP_SETTINGS_RELOAD:
            SC_Filter(w);
            return false;  // The template reloads its fields and rebuilds.
        case WM_TIMER:
            if (wp == kSetTimerId && !g_sc.knob.empty()) {
                bool moved = false;
                for (auto it = g_sc.knob.begin(); it != g_sc.knob.end();) {
                    int idx = SC_IndexOf(it->first);
                    float target = 0;
                    if (idx >= 0) {
                        auto want = g_sc.want.find(it->first);
                        target = (want != g_sc.want.end() ? want->second : g_sc.entries[idx].enabled) ? 1.0f : 0.0f;
                    }
                    float d = target - it->second;
                    if (idx < 0 || fabsf(d) < 0.02f) {
                        moved = true;
                        bool busy = g_sc.want.count(it->first) > 0;
                        if (!busy || idx < 0) { it = g_sc.knob.erase(it); continue; }
                        it->second = target;
                    } else {
                        it->second += d * 0.3f;
                        moved = true;
                    }
                    ++it;
                }
                if (moved) Set_Invalidate(w);
            }
            return false;
        case WM_COMMAND: {
            if (LOWORD(wp) == SC_REFRESH && !lp) { SC_Refresh(w); SC_Rebuild(w); result = 0; return true; }
            int k = (int)LOWORD(wp) - SC_ID_EDIT;
            if (k < 0 || k >= SE_Count || (HWND)lp != g_sc.edits[k]) return false;
            if (HIWORD(wp) == EN_CHANGE && k == SE_Search) {
                g_sc.filter = SC_Text(g_sc.edits[SE_Search]);
                SC_Filter(w);
                w.scrollY = w.scrollTarget = 0;
                SC_Rebuild(w);
            } else if (HIWORD(wp) == EN_SETFOCUS || HIWORD(wp) == EN_KILLFOCUS) {
                Set_Invalidate(w);
            }
            result = 0;
            return true;
        }
        case WM_LBUTTONDOWN: {
            if (w.autoScroll || w.saving || w.page >= SC_Pages) return false;
            float s = w.dpi / 96.0f, x = GET_X_LPARAM(lp) / s, y = GET_Y_LPARAM(lp) / s - kSetCapH;
            SetHit h = Set_Hit(w, x, y);
            if (h.id < SC_HitBase) return false;
            SetFocus(hwnd);
            w.kbd = false;
            g_sc.kbd = false;
            SC_Do(w, h.a, x);
            if (g_setWin.get() == pw) {
                w.hover = Set_Hit(w, x, y);
                Set_Invalidate(w);
            }
            result = 0;
            return true;
        }
        case WM_KEYDOWN:
            if (w.page >= SC_Pages || w.autoScroll || w.saving || w.openSel >= 0) return false;
            if (SC_Key(w, (UINT)wp)) { result = 0; return true; }
            return false;
        case WM_CHAR:
            if (w.page >= SC_Pages || g_sc.mode != 0 || w.page == SC_ChangesPage || w.autoScroll) return false;
            if (wp > 32 && wp != L'/' && !(GetKeyState(VK_CONTROL) & 0x8000) && g_sc.edits[SE_Search]) {
                SC_FocusEdit(w, SE_Search);
                SendMessageW(g_sc.edits[SE_Search], EM_SETSEL, -1, -1);
                SendMessageW(g_sc.edits[SE_Search], WM_CHAR, wp, lp);
                result = 0;
                return true;
            }
            if (wp == L' ' || wp == L'/' || wp == VK_RETURN) { result = 0; return true; }  // Handled on key down.
            return false;
        case WM_DESTROY:
            sc::g_notify = nullptr;
            for (HWND& e : g_sc.edits) e = nullptr;  // Children go with the window.
            if (g_sc.font) DeleteObject(g_sc.font);
            if (g_sc.mono) DeleteObject(g_sc.mono);
            g_sc = SC_State{};
            return false;
    }
    return false;
}

}  // namespace scui
namespace {
constexpr UINT kTrayMessage = WM_APP + 108;
constexpr UINT kReloadMessage = WM_APP + 109;
HWND g_toolWindow = nullptr;
DWORD g_toolThread = 0;
HICON g_trayIcon = nullptr;
bool g_trayShown = false;
// The shared tray badge, copied from Seamless Crosshair.
static HICON MakeTrayIcon(bool off) {
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
    HDC dc = CreateCompatibleDC(nullptr);
    HGDIOBJ old = SelectObject(dc, glyph);
    memset(glyphBits, 0, (size_t)size * size * 4);
    HFONT font = CreateFontW(-(int)(size * 0.66f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xE7F4, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {off ? 0x6C / 255.f : 0x89 / 255.f, off ? 0x70 / 255.f : 0xB4 / 255.f, off ? 0x86 / 255.f : 0xFA / 255.f};
    const float c1[3] = {off ? 0x58 / 255.f : 0xCB / 255.f, off ? 0x5B / 255.f : 0xA6 / 255.f, off ? 0x70 / 255.f : 0xF7 / 255.f};
    const float ink[3] = {0x11 / 255.f, 0x11 / 255.f, 0x1B / 255.f};
    float radius = size * 0.26f, half = size / 2.0f;
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float qx = std::fabs(x + 0.5f - half) - (half - radius), qy = std::fabs(y + 0.5f - half) - (half - radius);
            float ox = std::max(qx, 0.0f), oy = std::max(qy, 0.0f);
            float d = std::sqrt(ox * ox + oy * oy) + std::min(std::max(qx, qy), 0.0f) - radius;
            float a = std::clamp(0.5f - d, 0.0f, 1.0f);
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
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
    DeleteObject(glyph);
    return icon;
}
UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
void UpdateTray() {
    if (!g_toolWindow) return;
    NOTIFYICONDATAW data{sizeof(data)};
    data.hWnd = g_toolWindow; data.uID = TrayIconId();
    data.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    data.uCallbackMessage = kTrayMessage;
    data.hIcon = g_trayIcon;
    wcscpy_s(data.szTip, L"Startup Control");
    bool wanted = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    if (wanted) {
        g_trayShown = Shell_NotifyIconW(g_trayShown ? NIM_MODIFY : NIM_ADD, &data) != FALSE;
        data.uVersion = NOTIFYICON_VERSION_4; Shell_NotifyIconW(NIM_SETVERSION, &data);
    } else if (g_trayShown) { Shell_NotifyIconW(NIM_DELETE, &data); g_trayShown = false; }
}
// The "Open the settings window" switch on Windhawk's page: any flip since the last look counts
// as a press. The first look only records the value.
static bool OpenRequestChanged() {
    int now = Wh_GetIntSetting(L"openSettingsWindow") ? 1 : 0;
    int seen = Wh_GetIntValue(L"openSettingsWindowSeen", -1);
    if (now == seen) return false;
    Wh_SetIntValue(L"openSettingsWindowSeen", now);
    return seen != -1;
}
LRESULT CALLBACK ToolWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == kTrayMessage) {
        // Version 4 tray messages: a left click arrives as WM_LBUTTONUP then NIN_SELECT, a right
        // click as WM_RBUTTONUP then WM_CONTEXTMENU. Act on one of each, or the second message
        // closes the menu the first one opened.
        if (LOWORD(lp) == NIN_SELECT || LOWORD(lp) == NIN_KEYSELECT) scui::OpenSettingsWindow();
        if (LOWORD(lp) == WM_CONTEXTMENU) {
            std::vector<scui::SetMenuItem> menu = {
                {1, L"\uE7F4", L"Open Startup Control"},
                {2, L"\uE72C", L"Refresh entries"},
            };
            POINT at{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)};
            int result = scui::Set_TrayMenu(hwnd, menu, &at);
            if (result == 1) scui::OpenSettingsWindow();
            if (result == 2) {
                scui::OpenSettingsWindow();
                if (HWND window = scui::g_settingsWnd.load()) PostMessageW(window, WM_COMMAND, scui::SC_REFRESH, 0);
            }
        }
        return 0;
    }
    if (msg == kReloadMessage) {
        if (OpenRequestChanged()) scui::OpenSettingsWindow();
        UpdateTray();
        if (HWND window = scui::g_settingsWnd.load()) PostMessageW(window, scui::WM_APP_SETTINGS_RELOAD, 0, 0);
        return 0;
    }
    static UINT taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    if (msg == taskbarCreated) { g_trayShown = false; UpdateTray(); return 0; }
    return DefWindowProcW(hwnd, msg, wp, lp);
}
}
BOOL WhTool_ModInit() {
    g_toolThread = GetCurrentThreadId();
    INITCOMMONCONTROLSEX controls{sizeof(controls), ICC_STANDARD_CLASSES};
    InitCommonControlsEx(&controls);
    WNDCLASSW cls{}; cls.hInstance = (HINSTANCE)&__ImageBase;
    cls.lpfnWndProc = ToolWindowProc; cls.lpszClassName = L"WindhawkStartupControlTool";
    if (!RegisterClassW(&cls) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) return FALSE;
    g_toolWindow = CreateWindowExW(WS_EX_TOOLWINDOW, cls.lpszClassName, L"Startup Control", 0,
                                  0, 0, 0, 0, nullptr, nullptr, cls.hInstance, nullptr);
    if (!g_toolWindow) return FALSE;
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    g_trayIcon = MakeTrayIcon(false);
    UpdateTray();
    if (OpenRequestChanged() || !g_trayShown) scui::OpenSettingsWindow();
    return TRUE;
}
void WhTool_ModEntryPoint() {
    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) { TranslateMessage(&msg); DispatchMessageW(&msg); }
}
void WhTool_ModSettingsChanged() {
    if (g_toolWindow) PostMessageW(g_toolWindow, kReloadMessage, 0, 0);
}
void WhTool_ModUninit() {
    scui::CloseSettingsWindow();
    sc::StopScan();
    for (int i = 0; i < 200 && scui::g_scJobs.load() > 0; ++i) Sleep(50);
    Sleep(50);
    if (g_trayShown) {
        NOTIFYICONDATAW data{sizeof(data)}; data.hWnd = g_toolWindow; data.uID = TrayIconId();
        Shell_NotifyIconW(NIM_DELETE, &data); g_trayShown = false;
    }
    if (g_trayIcon) { DestroyIcon(g_trayIcon); g_trayIcon = nullptr; }
    if (g_toolWindow) { DestroyWindow(g_toolWindow); g_toolWindow = nullptr; }
    UnregisterClassW(L"WindhawkStartupControlTool", (HINSTANCE)&__ImageBase);
    CoUninitialize();
    if (g_toolThread) PostThreadMessageW(g_toolThread, WM_QUIT, 0, 0);
}
#if __has_include(<windhawk_tool_mod.h>)
#include <windhawk_tool_mod.h>
#endif
