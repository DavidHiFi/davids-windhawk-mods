// ==WindhawkMod==
// @id              seamless-file-unlocker
// @name            Seamless File Unlocker
// @description     Find out what is holding a file or folder, then let go of it, move it or delete it
// @version         1.0.3
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/seamless-workshop
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @include         explorer.exe
// @compilerOptions -ld2d1 -ldwrite -lwindowscodecs -lole32 -loleaut32 -luuid -lgdi32 -lgdiplus -luser32 -lshell32 -lshlwapi -ladvapi32 -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -lversion -lntdll -lpropsys -lbcrypt -lrstrtmgr -lpsapi -Wl,--delayload=d2d1.dll -Wl,--delayload=dwrite.dll -Wl,--delayload=windowscodecs.dll -Wl,--delayload=comdlg32.dll -Wl,--delayload=imm32.dll -Wl,--delayload=gdiplus.dll -Wl,--delayload=propsys.dll -Wl,--delayload=bcrypt.dll -Wl,--delayload=rstrtmgr.dll -ldelayimp
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless File Unlocker

"This file is in use." "The folder can't be deleted." This mod answers the question
behind those messages: what is holding it? It lists every program that has the file
open, or anything inside a folder, and lets you free it in one click.

![Seamless File Unlocker](https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/media/previews/seamless-file-unlocker.png)

## How to open it

- Right-click a file, folder or drive in Explorer or on the desktop, pick Show more options, then **What's locking this?**
- Or select something in Explorer and press Ctrl+Shift+U.
- Or click the tray icon.

## What it shows

- The program's icon and name, its number, where it runs from, which file it holds and how.
- How: an open file, a loaded DLL, a running program or a mapped file.
- If nothing is holding it: "Nothing is holding this. You can delete, move or rename it now."

## What you can do

- **Unlock** lets go of the file without closing the program. A loaded DLL is unloaded, after a warning.
- **Delete** unlocks, then sends it to the Recycle Bin. If it still won't go, it is removed at the next restart.
- Unlock and rename, copy or move it.
- Delete at the next restart.
- Close the program that holds it: politely first, then for good after you confirm.
- Open the program's folder, or copy the details.
- Every step that could lose work asks first, in plain words.

## Good to know

- The system's own programs are never touched. Explorer gets a warning first.
- Programs run with more rights than this tool can't always be seen or freed. The window says when some were out of reach.
- Nothing is held back from you: the window never freezes while it looks.

## Credits

- Inspired by LockHunter by Crystal Rich. No code from it is used.

Made by [DavidHiFi](https://github.com/DavidHiFi). Like it? [Buy me a coffee on Ko-fi](https://ko-fi.com/DavidHiFi).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- unlockHotkey: Ctrl+Shift+U
  $name: Shortcut
  $description: "Press it in Explorer or on the desktop to see what is holding the selected items, or the folder when nothing is selected."
- menuEntry: true
  $name: Right-click menu entry
  $description: "Adds What's locking this? above Properties. It shows under Show more options."
- askBeforeClosing: true
  $name: Ask before closing programs
  $description: "Ask first before a program is closed or a loaded DLL is unloaded."
- recycleBin: true
  $name: Delete to the Recycle Bin
  $description: "On, Delete sends items to the Recycle Bin. Off, they are deleted for good."
- showSystem: false
  $name: Show system programs
  $description: "Also list the programs Windows runs for itself. They can be seen but never closed."
- settingsAnimation: true
  $name: Open and close animation
  $description: "The window fades in with a short slide. Stays still when Windows animations are off."
- settingsGlass: true
  $name: Blurred settings window
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: Native Windows title bar
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: Tray icon
  $description: "An icon in the tray. Click it to open the window. Right-click for settings."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <dwmapi.h>
#include <gdiplus.h>
#include <objbase.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <windhawk_utils.h>
#include <psapi.h>
#include <restartmanager.h>
#include <tlhelp32.h>
#include <bcrypt.h>
#include <propvarutil.h>
#include <propsys.h>
#include <shlguid.h>
#include <exdisp.h>
#include <shobjidl.h>
#include <cstring>
#include <random>
#include <map>
#include <imm.h>
#include <d2d1helper.h>
#include <d2d1_1.h>
#include <shlobj.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <cwctype>
#include <functional>
#include <memory>
#include <mutex>
#include <regex>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

extern "C" IMAGE_DOS_HEADER __ImageBase;

// ---- Keys ---------------------------------------------------------------------------------------------------------

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
    {VK_CAPITAL, L"CapsLock"}, {VK_ADD, L"NumpadPlus"}, {VK_SUBTRACT, L"NumpadMinus"},
    {VK_MULTIPLY, L"NumpadStar"}, {VK_DIVIDE, L"NumpadSlash"}, {VK_DECIMAL, L"NumpadDot"},
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

static std::wstring SettingString(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}

// The class of the tool process's hidden tray window. Explorer sends it the selected paths.
constexpr WCHAR kFuTrayClass[] = L"SeamlessFileUnlockerTray";
constexpr ULONG_PTR kFuCopyPaths = 0x53465531;  // "SFU1": the paths to check, joined by NULs.


// ---- Finding and freeing locks ---------------------------------------------------------------------------------------
// Nothing in this part calls Windhawk. It all runs on worker threads, so the window never waits on it, and it could run
// in a helper process as it is.

static bool g_fuAnim = true;

namespace fu {

struct NtString {  // the system's UNICODE_STRING, which the Windhawk headers do not declare
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
};

enum Kind { kOpen = 0, kDll = 1, kExe = 2, kMapped = 3 };

static PCWSTR KindText(int k) {
    static const PCWSTR t[] = {L"Open file", L"Loaded DLL", L"Running program", L"Mapped file"};
    return t[k & 3];
}

struct Lock {
    DWORD pid = 0;
    std::wstring name, exe, path;  // program name, where it runs from, what it holds
    int kind = kOpen;
    ULONG_PTR handle = 0;  // the handle's number inside that program; 0 when only the program is known
    int safety = 0;        // 0 normal, 1 warn first (Explorer), 2 never touch
};

struct Found {
    std::vector<Lock> rows;
    int denied = 0;   // programs that could not be looked into
    int hidden = 0;   // Windows' own programs left out of the list
    bool partial = false, missing = false, failed = false;
    std::wstring error;
};

static std::wstring Lower(std::wstring s) {
    if (!s.empty()) CharLowerBuffW(s.data(), (DWORD)s.size());
    return s;
}

// A path in one shape for comparing: full, long names, no \\?\, no closing slash, lower case.
static std::wstring Norm(const std::wstring& in) {
    std::wstring p = in;
    if (p.rfind(L"\\\\?\\UNC\\", 0) == 0) p = L"\\\\" + p.substr(8);
    else if (p.rfind(L"\\\\?\\", 0) == 0) p = p.substr(4);
    std::vector<WCHAR> buf(32768);
    DWORD n = GetFullPathNameW(p.c_str(), (DWORD)buf.size(), buf.data(), nullptr);
    if (n && n < buf.size()) p.assign(buf.data(), n);
    n = GetLongPathNameW(p.c_str(), buf.data(), (DWORD)buf.size());
    if (n && n < buf.size()) p.assign(buf.data(), n);
    while (p.size() > 3 && p.back() == L'\\') p.pop_back();
    if (p.size() == 3 && p[1] == L':' && p[2] == L'\\') p.pop_back();
    return Lower(p);
}

static bool Under(const std::wstring& lowerPath, const std::vector<std::wstring>& keys) {
    for (const auto& t : keys) {
        if (lowerPath.size() < t.size() || lowerPath.compare(0, t.size(), t) != 0) continue;
        if (lowerPath.size() == t.size() || lowerPath[t.size()] == L'\\') return true;
    }
    return false;
}

static std::wstring ErrText(DWORD e) {
    switch (e) {
        case ERROR_ACCESS_DENIED: return L"Windows said no. This needs more rights";
        case ERROR_SHARING_VIOLATION:
        case ERROR_LOCK_VIOLATION: return L"Another program still has it open";
        case ERROR_FILE_NOT_FOUND:
        case ERROR_PATH_NOT_FOUND: return L"It isn't there any more";
        case ERROR_ALREADY_EXISTS:
        case ERROR_FILE_EXISTS: return L"Something with that name is already there";
        case ERROR_DIR_NOT_EMPTY: return L"The folder isn't empty";
        case ERROR_NOT_SAME_DEVICE: return L"It can't move between those drives like that";
        default: return L"Windows error " + std::to_wstring(e);
    }
}

// ---- The system calls we use without a header -------------------------------------------------------------------------

struct Nt {
    LONG(NTAPI* QuerySystem)(ULONG, PVOID, ULONG, PULONG);
    LONG(NTAPI* QueryObject)(HANDLE, ULONG, PVOID, ULONG, PULONG);
    LONG(NTAPI* QueryProcess)(HANDLE, ULONG, PVOID, ULONG, PULONG);
    bool ok;
};

static const Nt& GetNt() {
    static Nt n = [] {
        Nt x{};
        HMODULE m = GetModuleHandleW(L"ntdll.dll");
        if (m) {
            x.QuerySystem = (decltype(x.QuerySystem))GetProcAddress(m, "NtQuerySystemInformation");
            x.QueryObject = (decltype(x.QueryObject))GetProcAddress(m, "NtQueryObject");
            x.QueryProcess = (decltype(x.QueryProcess))GetProcAddress(m, "NtQueryInformationProcess");
        }
        x.ok = x.QuerySystem && x.QueryObject && x.QueryProcess;
        return x;
    }();
    return n;
}

struct HandleEntry {  // SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX
    PVOID Object;
    ULONG_PTR Pid, Handle;
    ULONG Access;
    USHORT CreatorBackTrace, TypeIndex;
    ULONG Attributes, Reserved;
};
static_assert(sizeof(HandleEntry) == 3 * sizeof(void*) + 16, "handle entry size");  // 40 on x64, 28 on x86

static bool g_elevated = false, g_debugRights = false;

static void InitRights() {
    HANDLE tok = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &tok)) return;
    TOKEN_ELEVATION e{};
    DWORD n = 0;
    if (GetTokenInformation(tok, TokenElevation, &e, sizeof(e), &n)) g_elevated = e.TokenIsElevated != 0;
    TOKEN_PRIVILEGES tp{};
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if (LookupPrivilegeValueW(nullptr, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
        AdjustTokenPrivileges(tok, FALSE, &tp, sizeof(tp), nullptr, nullptr);
        g_debugRights = GetLastError() == ERROR_SUCCESS;
    }
    CloseHandle(tok);
}

// ---- Reading a handle's name without ever hanging ---------------------------------------------------------------------
// Asking a pipe for its name can wait forever. The question goes to a helper thread; when it doesn't answer in time the
// thread is stopped and a fresh one takes over.

struct QShared {
    HANDLE req = CreateEventW(nullptr, FALSE, FALSE, nullptr), done = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    HANDLE h = nullptr;
    bool disk = false, ok = false;
    volatile LONG quit = 0;
    BYTE buf[66000];
};

static DWORD WINAPI QueryThread(void* p) {
    auto* s = (QShared*)p;
    const Nt& nt = GetNt();
    for (;;) {
        WaitForSingleObject(s->req, INFINITE);
        if (s->quit) break;
        s->ok = s->disk = false;
        if (GetFileType(s->h) == FILE_TYPE_DISK) {
            s->disk = true;
            ULONG ret = 0;
            if (nt.QueryObject(s->h, 1, s->buf, sizeof(s->buf), &ret) >= 0) s->ok = true;
        }
        SetEvent(s->done);
    }
    return 0;
}

static DWORD WINAPI CloseThread(void* h) {
    CloseHandle((HANDLE)h);
    return 0;
}

// A handle whose name question hung is closed from a thread of its own, in case closing waits as well.
static void CloseLater(HANDLE h) {
    HANDLE t = CreateThread(nullptr, 0, CloseThread, h, 0, nullptr);
    if (t) CloseHandle(t);
}

class Reader {
    QShared* s = nullptr;
    HANDLE th = nullptr;
    void Start() {
        s = new QShared;
        th = CreateThread(nullptr, 0, QueryThread, s, 0, nullptr);
    }

public:
    int timeouts = 0;
    ~Reader() {
        if (!s) return;
        InterlockedExchange(&s->quit, 1);
        SetEvent(s->req);
        if (th) {
            if (WaitForSingleObject(th, 2000) == WAIT_TIMEOUT) TerminateThread(th, 0);
            CloseHandle(th);
        }
        CloseHandle(s->req);
        CloseHandle(s->done);
        delete s;
    }
    // ok: the name was read. disk: it is a file or folder. timedOut: the handle never answered.
    bool Read(HANDLE h, std::wstring& name, bool& disk, bool& timedOut, DWORD ms = 150) {
        timedOut = false;
        disk = false;
        if (!s) Start();
        if (!s || !th) return false;
        s->h = h;
        ResetEvent(s->done);
        SetEvent(s->req);
        if (WaitForSingleObject(s->done, ms) != WAIT_OBJECT_0) {
            timedOut = true;
            timeouts++;
            TerminateThread(th, 0);
            CloseHandle(th);
            th = nullptr;
            s = nullptr;  // the old state is left behind on purpose: the stopped thread may still touch it
            return false;
        }
        disk = s->disk;
        if (!s->ok) return false;
        auto* u = (NtString*)s->buf;
        if (!u->Buffer || !u->Length) return false;
        name.assign(u->Buffer, u->Length / sizeof(WCHAR));
        return true;
    }
};

// ---- Paths ---------------------------------------------------------------------------------------------------------------

struct DevMap {
    std::vector<std::pair<std::wstring, std::wstring>> v;  // "\Device\HarddiskVolume3" -> "C:"
    DevMap() {
        for (WCHAR d = L'A'; d <= L'Z'; d++) {
            WCHAR nm[3] = {d, L':', 0};
            WCHAR tgt[1024];
            if (QueryDosDeviceW(nm, tgt, ARRAYSIZE(tgt))) v.push_back({tgt, nm});
        }
    }
    std::wstring ToDos(const std::wstring& dev) const {
        for (const auto& [prefix, letter] : v) {
            if (dev.size() < prefix.size() || _wcsnicmp(dev.c_str(), prefix.c_str(), prefix.size()) != 0) continue;
            if (dev.size() == prefix.size()) return letter + L"\\";
            if (dev[prefix.size()] == L'\\') return letter + dev.substr(prefix.size());
        }
        if (_wcsnicmp(dev.c_str(), L"\\Device\\Mup\\", 12) == 0) return L"\\\\" + dev.substr(12);
        return {};
    }
};

// ---- Programs ------------------------------------------------------------------------------------------------------------

static bool IsNever(const std::wstring& lowerName) {
    static const PCWSTR n[] = {L"csrss.exe", L"wininit.exe", L"smss.exe", L"lsass.exe", L"services.exe", L"winlogon.exe",
                               L"system", L"registry", L"memory compression", L"secure system", L"dwm.exe",
                               L"windhawk.exe", L"system idle process"};
    for (PCWSTR s : n)
        if (lowerName == s) return true;
    return false;
}

struct ProcNames {
    std::map<DWORD, std::wstring> v;
    ProcNames() {
        HANDLE s = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (s == INVALID_HANDLE_VALUE) return;
        PROCESSENTRY32W e{sizeof(e)};
        for (BOOL ok = Process32FirstW(s, &e); ok; ok = Process32NextW(s, &e)) v[e.th32ProcessID] = e.szExeFile;
        CloseHandle(s);
    }
};

static void FillProc(Lock& L, const ProcNames& names) {
    L.safety = 0;
    auto it = names.v.find(L.pid);
    if (L.pid == 4) {
        L.name = L"System";
        L.exe = L"System";
    } else {
        HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, L.pid);
        if (h) {
            WCHAR buf[2048];
            DWORD n = ARRAYSIZE(buf);
            if (QueryFullProcessImageNameW(h, 0, buf, &n)) L.exe = buf;
            ULONG brk = 0;
            if (GetNt().QueryProcess(h, 29, &brk, sizeof(brk), nullptr) >= 0 && brk) L.safety = 2;  // BreakOnTermination
            CloseHandle(h);
        }
        L.name = it != names.v.end() ? it->second : (L.exe.empty() ? L"(unknown)" : PathFindFileNameW(L.exe.c_str()));
    }
    std::wstring low = Lower(L.name);
    if (L.pid == GetCurrentProcessId() || L.pid == 0 || IsNever(low)) L.safety = 2;
    else if (low == L"explorer.exe" && L.safety < 1) L.safety = 1;
}

// ---- Looking for locks -----------------------------------------------------------------------------------------------

struct Progress {
    std::atomic<int> done{0}, total{0};
};
static Progress g_prog;

static int FileTypeIndex(std::vector<BYTE>& snap, const Nt& nt) {
    ULONG size = 24u << 20;
    for (int i = 0; i < 12; i++) {
        WCHAR me[MAX_PATH]{};
        GetModuleFileNameW(nullptr, me, ARRAYSIZE(me));
        HANDLE self = CreateFileW(me, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                                  OPEN_EXISTING, 0, nullptr);
        if (self == INVALID_HANDLE_VALUE) return -1;
        snap.resize(size);
        ULONG need = 0;
        LONG st = nt.QuerySystem(64, snap.data(), size, &need);
        int idx = -1;
        if (st >= 0) {
            auto* hdr = (const ULONG_PTR*)snap.data();
            auto* e = (const HandleEntry*)(snap.data() + 2 * sizeof(ULONG_PTR));
            for (ULONG_PTR k = 0; k < hdr[0]; k++)
                if (e[k].Pid == GetCurrentProcessId() && e[k].Handle == (ULONG_PTR)self) {
                    idx = e[k].TypeIndex;
                    break;
                }
        }
        CloseHandle(self);
        if (st >= 0) return idx;
        if (st != (LONG)0xC0000004) return -1;  // not "buffer too small"
        size = std::max<ULONG>(size * 2, need + (4u << 20));
    }
    return -1;
}

static bool IsDir(const std::wstring& p) {
    DWORD a = GetFileAttributesW(p.c_str());
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
}

static bool Exists(const std::wstring& p) { return GetFileAttributesW(p.c_str()) != INVALID_FILE_ATTRIBUTES; }

// Programs with a file or folder open, found by looking at every open handle on the machine.
// A short trail of what the last scans did, written into the test state file.
static std::mutex g_dbgMu;
static std::wstring g_dbgText;
static void DbgAdd(const std::wstring& s) {
    std::lock_guard<std::mutex> g(g_dbgMu);
    g_dbgText += s + L"\n";
    if (g_dbgText.size() > 6000) g_dbgText.erase(0, g_dbgText.size() - 6000);
}
static std::wstring DbgGet() {
    std::lock_guard<std::mutex> g(g_dbgMu);
    return g_dbgText;
}

static void HandlePass(const std::vector<std::wstring>& keys, const DevMap& dm, Reader& rd, const std::atomic<bool>& cancel,
                       Found& out, ULONGLONG deadline, int cap, const std::set<DWORD>* only = nullptr, DWORD readMs = 150) {
    const Nt& nt = GetNt();
    ULONGLONG t0 = GetTickCount64();
    int nDupFail = 0, nReadFail = 0, nNotDisk = 0, nTimeout = 0, nNoMap = 0, nHandles = 0, nPids = 0, nDenied = 0;
    std::wstring why = L"done";
    std::wstring sample;
    std::vector<BYTE> snap;
    int fileType = FileTypeIndex(snap, nt);
    if (fileType < 0) {
        out.failed = true;
        out.error = L"Couldn't read the list of open files from Windows.";
        DbgAdd(L"pass " + std::wstring(only ? L"targeted" : L"full") + L": no file type index");
        return;
    }
    auto* hdr = (const ULONG_PTR*)snap.data();
    auto* ent = (const HandleEntry*)(snap.data() + 2 * sizeof(ULONG_PTR));
    DWORD self = GetCurrentProcessId();
    std::map<ULONG_PTR, std::vector<const HandleEntry*>> byPid;
    for (ULONG_PTR i = 0; i < hdr[0]; i++)
        if (ent[i].TypeIndex == fileType && ent[i].Pid && ent[i].Pid != self) byPid[ent[i].Pid].push_back(&ent[i]);
    if (!only) {
        g_prog.total = (int)byPid.size();
        g_prog.done = 0;
    }
    std::unordered_map<PVOID, int> cache;
    std::vector<std::wstring> matched;
    ProcNames names;
    auto report = [&] {
        std::wstring s = std::wstring(L"pass ") + (only ? L"targeted" : L"full") + L" " + why + L": " +
                         std::to_wstring(GetTickCount64() - t0) + L" ms, pids " + std::to_wstring(nPids) + L"/" +
                         std::to_wstring(byPid.size()) + L", handles " + std::to_wstring(nHandles) + L", denied " +
                         std::to_wstring(nDenied) + L", dupFail " + std::to_wstring(nDupFail) + L", timeouts " +
                         std::to_wstring(nTimeout) + L", readFail " + std::to_wstring(nReadFail) + L", notDisk " +
                         std::to_wstring(nNotDisk) + L", noMap " + std::to_wstring(nNoMap) + L", rows " +
                         std::to_wstring(out.rows.size()) + L", type " + std::to_wstring(fileType) + L", key " +
                         (keys.empty() ? L"" : keys[0]);
        if (only) s += L" | " + sample;
        DbgAdd(s);
    };
    for (auto& [pid, list] : byPid) {
        if (only && !only->count((DWORD)pid)) continue;
        g_prog.done++;
        if (cancel) {
            why = L"cancelled";
            report();
            return;
        }
        if (GetTickCount64() > deadline || (int)out.rows.size() >= cap || rd.timeouts > 300) {
            out.partial = true;
            why = GetTickCount64() > deadline ? L"out of time" : (rd.timeouts > 300 ? L"too many timeouts" : L"row cap");
            report();
            return;
        }
        HANDLE hp = OpenProcess(PROCESS_DUP_HANDLE, FALSE, (DWORD)pid);
        if (!hp) {
            nDenied++;
            Lock probe;
            probe.pid = (DWORD)pid;
            FillProc(probe, names);
            if (probe.safety < 2 && !only) out.denied++;
            continue;
        }
        nPids++;
        for (const HandleEntry* e : list) {
            int m = -1;
            nHandles++;
            // Without special rights Windows hides every object address (all zero), so there is nothing to remember by.
            auto c = e->Object ? cache.find(e->Object) : cache.end();
            if (c != cache.end()) {
                m = c->second;
            } else {
                HANDLE dup = nullptr;
                if (!DuplicateHandle(hp, (HANDLE)e->Handle, GetCurrentProcess(), &dup, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
                    nDupFail++;
                    continue;
                }
                std::wstring dev;
                bool disk = false, timedOut = false;
                bool ok = rd.Read(dup, dev, disk, timedOut, readMs);
                if (timedOut) CloseLater(dup);
                else CloseHandle(dup);
                if (timedOut) nTimeout++;
                else if (!disk) nNotDisk++;
                else if (!ok) nReadFail++;
                if (only && ok && sample.size() < 400) sample += dev.substr(dev.size() > 60 ? dev.size() - 60 : 0) + L" ; ";
                if (ok && disk) {
                    std::wstring dos = dm.ToDos(dev);
                    if (dos.empty()) nNoMap++;
                    if (!dos.empty() && Under(Lower(dos), keys)) {
                        m = (int)matched.size();
                        matched.push_back(dos);
                    }
                }
                if (!timedOut && e->Object) cache[e->Object] = m;  // a handle that never answered is asked again, not remembered as "no"
            }
            if (m >= 0) {
                Lock L;
                L.pid = (DWORD)pid;
                L.handle = e->Handle;
                L.path = matched[m];
                L.kind = kOpen;
                out.rows.push_back(L);
            }
        }
        CloseHandle(hp);
    }
    report();
}

// Programs that run from, or have loaded or mapped, the item.
static void ModulePass(const std::vector<std::wstring>& keys, const DevMap& dm, const std::atomic<bool>& cancel, Found& out,
                       ULONGLONG deadline) {
    ProcNames names;
    DWORD self = GetCurrentProcessId();
    std::set<std::wstring> seen;
    for (const auto& [pid, nm] : names.v) {
        if (cancel) return;
        if (pid <= 4 || pid == self) continue;
        if (GetTickCount64() > deadline) {
            out.partial = true;
            return;
        }
        HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
        if (!h) continue;
        MEMORY_BASIC_INFORMATION mbi;
        BYTE* addr = nullptr;
        while (VirtualQueryEx(h, addr, &mbi, sizeof(mbi)) == sizeof(mbi)) {
            BYTE* next = (BYTE*)mbi.BaseAddress + mbi.RegionSize;
            if ((mbi.Type == MEM_IMAGE || mbi.Type == MEM_MAPPED) && mbi.BaseAddress == mbi.AllocationBase) {
                WCHAR buf[2048];
                DWORD n = GetMappedFileNameW(h, mbi.BaseAddress, buf, ARRAYSIZE(buf));
                if (n && n < ARRAYSIZE(buf)) {
                    std::wstring dos = dm.ToDos(std::wstring(buf, n));
                    std::wstring low = Lower(dos);
                    if (!dos.empty() && Under(low, keys)) {
                        int kind = kMapped;
                        if (mbi.Type == MEM_IMAGE) {
                            kind = low.size() > 4 && low.compare(low.size() - 4, 4, L".exe") == 0 ? kExe : kDll;
                        }
                        std::wstring key = std::to_wstring(pid) + L"|" + std::to_wstring(kind) + L"|" + low;
                        if (seen.insert(key).second) {
                            Lock L;
                            L.pid = pid;
                            L.path = dos;
                            L.kind = kind;
                            out.rows.push_back(L);
                        }
                    }
                }
            }
            if (next <= addr) break;
            addr = next;
#ifdef _WIN64
            if ((ULONG_PTR)addr >= 0x7FFFFFFF0000ull) break;
#endif
        }
        CloseHandle(h);
    }
}

// Restart Manager knows programs that hold a file in ways the handle list doesn't show.
static void RestartPass(const std::vector<std::wstring>& targets, Found& out) {
    std::vector<LPCWSTR> files;
    for (const auto& t : targets)
        if (!IsDir(t) && Exists(t) && files.size() < 200) files.push_back(t.c_str());
    if (files.empty()) return;
    DWORD session = 0;
    WCHAR key[CCH_RM_SESSION_KEY + 1] = {};
    if (RmStartSession(&session, 0, key) != ERROR_SUCCESS) return;
    if (RmRegisterResources(session, (UINT)files.size(), files.data(), 0, nullptr, 0, nullptr) == ERROR_SUCCESS) {
        UINT need = 0, cnt = 0;
        DWORD reasons = 0;
        DWORD r = RmGetList(session, &need, &cnt, nullptr, &reasons);
        if (r == ERROR_MORE_DATA && need) {
            std::vector<RM_PROCESS_INFO> info(need + 4);
            cnt = (UINT)info.size();
            if (RmGetList(session, &need, &cnt, info.data(), &reasons) == ERROR_SUCCESS) {
                for (UINT i = 0; i < cnt; i++) {
                    DWORD pid = info[i].Process.dwProcessId;
                    bool have = false;
                    for (const Lock& L : out.rows)
                        if (L.pid == pid) have = true;
                    if (have) continue;
                    Lock L;
                    L.pid = pid;
                    L.path = files.size() == 1 ? files[0] : L"";
                    L.kind = kOpen;
                    out.rows.push_back(L);
                }
            }
        }
    }
    RmEndSession(session);
}

static Found Find(const std::vector<std::wstring>& targets, bool showSystem, const std::atomic<bool>& cancel) {
    Found out;
    const Nt& nt = GetNt();
    if (!nt.ok) {
        out.failed = true;
        out.error = L"This version of Windows doesn't allow the check.";
        return out;
    }
    std::vector<std::wstring> keys;
    bool any = false;
    for (const auto& t : targets) {
        keys.push_back(Norm(t));
        if (Exists(t)) any = true;
    }
    if (!any) {
        out.missing = true;
        return out;
    }
    DevMap dm;
    Reader rd;
    ULONGLONG deadline = GetTickCount64() + 25000;
    HandlePass(keys, dm, rd, cancel, out, deadline, 2000);
    if (out.failed || cancel) return out;
    ModulePass(keys, dm, cancel, out, deadline);
    if (cancel) return out;
    RestartPass(targets, out);
    {
        // The fallback named programs the long scan never reached (it can run out of time on a busy PC).
        // Look at just those programs, so the handle itself is known and can be closed.
        std::set<DWORD> bare;
        for (const Lock& L : out.rows)
            if (L.kind == kOpen && !L.handle) bare.insert(L.pid);
        if (!bare.empty() && !cancel) {
            Found more;
            Reader rd2;
            HandlePass(keys, dm, rd2, cancel, more, GetTickCount64() + 15000, 2000, &bare, 1500);
            if (!more.failed && !more.rows.empty()) {
                std::set<DWORD> got;
                for (const Lock& L : more.rows) got.insert(L.pid);
                std::vector<Lock> merged;
                for (Lock& L : out.rows)
                    if (!(L.kind == kOpen && !L.handle && got.count(L.pid))) merged.push_back(std::move(L));
                for (Lock& L : more.rows) merged.push_back(std::move(L));
                out.rows = std::move(merged);
            }
        }
    }
    ProcNames names;
    for (Lock& L : out.rows) FillProc(L, names);
    // Lock rows that name the same program, kind and thing are one row.
    std::set<std::wstring> seen;
    std::vector<Lock> kept;
    for (Lock& L : out.rows) {
        if (L.safety == 2 && !showSystem) {
            out.hidden++;
            continue;
        }
        std::wstring k = std::to_wstring(L.pid) + L"|" + std::to_wstring(L.kind) + L"|" + std::to_wstring(L.handle) + L"|" +
                         Lower(L.path);
        if (seen.insert(k).second) kept.push_back(std::move(L));
    }
    std::stable_sort(kept.begin(), kept.end(), [](const Lock& a, const Lock& b) {
        int c = _wcsicmp(a.name.c_str(), b.name.c_str());
        if (c) return c < 0;
        if (a.pid != b.pid) return a.pid < b.pid;
        return a.kind < b.kind;
    });
    out.rows = std::move(kept);
    return out;
}

// ---- Letting go ---------------------------------------------------------------------------------------------------------

struct Ctx {
    DevMap dm;
    Reader rd;
};

// Closes one open handle inside another program, after checking it still points at the same thing.
static std::wstring CloseHandleIn(const Lock& L, Ctx& cx) {
    HANDLE hp = OpenProcess(PROCESS_DUP_HANDLE, FALSE, L.pid);
    if (!hp) return L"Couldn't reach that program. " + ErrText(GetLastError());
    std::wstring err;
    HANDLE dup = nullptr;
    if (!DuplicateHandle(hp, (HANDLE)L.handle, GetCurrentProcess(), &dup, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
        CloseHandle(hp);
        return L"";  // gone already
    }
    std::wstring dev;
    bool disk = false, timedOut = false;
    bool ok = cx.rd.Read(dup, dev, disk, timedOut, 400);
    if (timedOut) CloseLater(dup);
    else CloseHandle(dup);
    if (!ok) {
        err = L"That handle didn't answer, so it was left alone.";
    } else if (Norm(cx.dm.ToDos(dev)) != Norm(L.path)) {
        err = L"";  // the program closed it, or reused the number: the lock is already gone
    } else if (!DuplicateHandle(hp, (HANDLE)L.handle, nullptr, nullptr, 0, FALSE, DUPLICATE_CLOSE_SOURCE)) {
        err = L"Couldn't close it. " + ErrText(GetLastError());
    }
    CloseHandle(hp);
    return err;
}

// Unloads a DLL from another program by asking it to run FreeLibrary until the DLL is gone.
static std::wstring FreeDll(const Lock& L, Ctx&) {
    HANDLE hp = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE |
                                PROCESS_VM_READ,
                            FALSE, L.pid);
    if (!hp) return L"Couldn't reach that program. " + ErrText(GetLastError());
    std::wstring err;
    BOOL wow = FALSE;
    IsWow64Process(hp, &wow);
    if (wow) {
        CloseHandle(hp);
        return L"That program is 32-bit. Close the program to free this DLL.";
    }
    std::wstring want = Norm(L.path);
    auto* freeLib = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "FreeLibrary");
    bool gone = false;
    for (int round = 0; round < 64 && !gone && err.empty(); round++) {
        HMODULE mods[2048];
        DWORD bytes = 0;
        HMODULE found = nullptr;
        if (EnumProcessModulesEx(hp, mods, sizeof(mods), &bytes, LIST_MODULES_ALL)) {
            for (DWORD i = 0; i < bytes / sizeof(HMODULE) && i < ARRAYSIZE(mods); i++) {
                WCHAR buf[2048];
                DWORD n = GetModuleFileNameExW(hp, mods[i], buf, ARRAYSIZE(buf));
                if (n && Norm(buf) == want) {
                    found = mods[i];
                    break;
                }
            }
        }
        if (!found) {
            gone = true;
            break;
        }
        HANDLE t = CreateRemoteThread(hp, nullptr, 0, freeLib, found, 0, nullptr);
        if (!t) {
            err = L"Couldn't unload it. " + ErrText(GetLastError());
            break;
        }
        if (WaitForSingleObject(t, 5000) != WAIT_OBJECT_0) err = L"The program didn't answer. Close it to free the DLL.";
        else {
            DWORD ok = 0;
            GetExitCodeThread(t, &ok);
            if (!ok) err = L"The program still needs this DLL. Close the program to free it.";
        }
        CloseHandle(t);
    }
    if (!gone && err.empty()) err = L"The program keeps loading it again. Close the program to free it.";
    CloseHandle(hp);
    return err;
}

static std::wstring UnlockOne(const Lock& L, Ctx& cx) {
    if (L.safety >= 2) return L"Windows needs this one. It is never touched.";
    if (L.kind == kOpen && !L.handle && !L.path.empty()) {
        // The list only knew the program. Look inside just that program again, patiently, and let go of what is found.
        Found f;
        std::set<DWORD> only{L.pid};
        std::atomic<bool> never{false};
        HandlePass({Norm(L.path)}, cx.dm, cx.rd, never, f, GetTickCount64() + 20000, 2000, &only, 1500);
        std::wstring err;
        int n = 0;
        for (const Lock& h : f.rows) {
            if (!h.handle) continue;
            n++;
            std::wstring e = CloseHandleIn(h, cx);
            if (!e.empty() && err.empty()) err = e;
        }
        if (n) return err;
    }
    if (L.kind == kOpen && L.handle) return CloseHandleIn(L, cx);
    if (L.kind == kDll) return FreeDll(L, cx);
    if (L.kind == kExe) return L"This is the program itself. Close the program to free it.";
    if (L.kind == kMapped) return L"The program has it in memory. Close the program to free it.";
    return L"Couldn't reach this program to let go. Close it to free the file.";
}

struct Unlocked {
    int freed = 0, failed = 0;
    std::wstring firstError;
};

static Unlocked UnlockAll(const std::vector<Lock>& rows, Ctx& cx) {
    Unlocked u;
    for (const Lock& L : rows) {
        std::wstring e = UnlockOne(L, cx);
        if (e.empty()) u.freed++;
        else {
            u.failed++;
            if (u.firstError.empty()) u.firstError = e;
        }
    }
    return u;
}

// ---- Close and end programs ---------------------------------------------------------------------------------------------

static BOOL CALLBACK PostClose(HWND h, LPARAM lp) {
    DWORD p = 0;
    GetWindowThreadProcessId(h, &p);
    if (p == (DWORD)lp) PostMessageW(h, WM_CLOSE, 0, 0);
    return TRUE;
}

// Asks the program's windows to close and waits a moment. True when it is gone.
static bool CloseProgramPolitely(DWORD pid) {
    HANDLE ph = OpenProcess(SYNCHRONIZE, FALSE, pid);
    if (!ph) return true;
    EnumWindows(PostClose, (LPARAM)pid);
    bool gone = WaitForSingleObject(ph, 3000) == WAIT_OBJECT_0;
    CloseHandle(ph);
    return gone;
}

static bool EndProgram(DWORD pid) {
    HANDLE ph = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, FALSE, pid);
    if (!ph) return false;
    bool ok = TerminateProcess(ph, 1) && WaitForSingleObject(ph, 3000) == WAIT_OBJECT_0;
    CloseHandle(ph);
    return ok;
}

// ---- Delete, move, copy, rename -------------------------------------------------------------------------------------------

static bool ScheduleDelete(const std::wstring& p, int depth = 0) {
    DWORD a = GetFileAttributesW(p.c_str());
    if (a == INVALID_FILE_ATTRIBUTES) return true;
    bool ok = true;
    if ((a & FILE_ATTRIBUTE_DIRECTORY) && !(a & FILE_ATTRIBUTE_REPARSE_POINT) && depth < 64) {
        WIN32_FIND_DATAW fd;
        HANDLE h = FindFirstFileW((p + L"\\*").c_str(), &fd);
        if (h != INVALID_HANDLE_VALUE) {
            do {
                if (!wcscmp(fd.cFileName, L".") || !wcscmp(fd.cFileName, L"..")) continue;
                ok = ScheduleDelete(p + L"\\" + fd.cFileName, depth + 1) && ok;
            } while (FindNextFileW(h, &fd));
            FindClose(h);
        }
    }
    return MoveFileExW(p.c_str(), nullptr, MOVEFILE_DELAY_UNTIL_REBOOT) && ok;
}

// True when every item is on a drive that has a Recycle Bin.
static bool BinPossible(const std::vector<std::wstring>& targets) {
    for (const auto& t : targets) {
        if (t.size() < 3 || t[1] != L':') return false;
        WCHAR root[4] = {t[0], L':', L'\\', 0};
        if (GetDriveTypeW(root) != DRIVE_FIXED) return false;
    }
    return true;
}

static HRESULT ShellDelete(const std::vector<std::wstring>& targets, bool toBin) {
    IFileOperation* fo = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileOperation, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&fo));
    if (FAILED(hr) || !fo) return hr;
    fo->SetOperationFlags(FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT | (toBin ? FOF_ALLOWUNDO : 0));
    for (const auto& t : targets) {
        IShellItem* si = nullptr;
        if (SUCCEEDED(SHCreateItemFromParsingName(t.c_str(), nullptr, IID_PPV_ARGS(&si))) && si) {
            fo->DeleteItem(si, nullptr);
            si->Release();
        }
    }
    hr = fo->PerformOperations();
    fo->Release();
    return hr;
}

static HRESULT ShellPlace(const std::vector<std::wstring>& targets, const std::wstring& folder, bool move) {
    IFileOperation* fo = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileOperation, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&fo));
    if (FAILED(hr) || !fo) return hr;
    fo->SetOperationFlags(FOF_NOERRORUI | FOF_SILENT | FOFX_NOCOPYHOOKS | FOF_RENAMEONCOLLISION);
    IShellItem* dest = nullptr;
    hr = SHCreateItemFromParsingName(folder.c_str(), nullptr, IID_PPV_ARGS(&dest));
    if (SUCCEEDED(hr) && dest) {
        for (const auto& t : targets) {
            IShellItem* si = nullptr;
            if (SUCCEEDED(SHCreateItemFromParsingName(t.c_str(), nullptr, IID_PPV_ARGS(&si))) && si) {
                if (move) fo->MoveItem(si, dest, nullptr, nullptr);
                else fo->CopyItem(si, dest, nullptr, nullptr);
                si->Release();
            }
        }
        hr = fo->PerformOperations();
        dest->Release();
    }
    fo->Release();
    return hr;
}

// ---- Jobs ---------------------------------------------------------------------------------------------------------------------

enum JobType { J_SCAN, J_UNLOCK, J_DELETE, J_RENAME, J_COPY, J_MOVE, J_REBOOT, J_CLOSE, J_END };

struct Job {
    int type = J_SCAN;
    std::vector<std::wstring> targets;
    std::vector<Lock> rows;
    std::wstring arg;  // a new name, or the folder to copy or move into
    bool toBin = true, showSystem = false;
    std::atomic<bool>* cancel = nullptr;
};

struct Result {
    int type = J_SCAN;
    bool ok = true;
    bool rescan = false;
    std::wstring text;
    Found found;
    std::vector<DWORD> stillRunning;  // programs that did not close when asked
};

static std::wstring Plural(int n, PCWSTR one, PCWSTR many) { return std::to_wstring(n) + L" " + (n == 1 ? one : many); }

static std::wstring UnlockSummary(const Unlocked& u) {
    if (!u.failed) return u.freed ? L"Let go of " + Plural(u.freed, L"lock", L"locks") + L"." : L"Nothing needed unlocking.";
    return L"Let go of " + std::to_wstring(u.freed) + L", " + std::to_wstring(u.failed) + L" held on: " + u.firstError;
}

static Result* Run(Job& job) {
    auto* r = new Result;
    r->type = job.type;
    static std::atomic<bool> never{false};
    switch (job.type) {
        case J_SCAN:
            r->found = Find(job.targets, job.showSystem, job.cancel ? *job.cancel : never);
            break;
        case J_UNLOCK: {
            Ctx cx;
            Unlocked u = UnlockAll(job.rows, cx);
            r->ok = !u.failed;
            r->text = UnlockSummary(u);
            r->rescan = true;
            break;
        }
        case J_DELETE: {
            Ctx cx;
            Unlocked u = UnlockAll(job.rows, cx);
            bool bin = job.toBin && BinPossible(job.targets);
            ShellDelete(job.targets, bin);
            std::vector<std::wstring> left;
            for (const auto& t : job.targets)
                if (Exists(t)) left.push_back(t);
            if (left.empty()) {
                r->text = bin ? L"Sent to the Recycle Bin." : L"Deleted.";
            } else {
                bool all = true;
                for (const auto& t : left) all = ScheduleDelete(t) && all;
                r->ok = all;
                r->text = all ? L"Still in use, so it will be deleted when Windows restarts."
                              : L"Couldn't delete it, even at the next restart." +
                                    std::wstring(u.failed ? L" " + u.firstError : L"");
            }
            r->rescan = true;
            break;
        }
        case J_RENAME: {
            Ctx cx;
            Unlocked u = UnlockAll(job.rows, cx);
            if (job.targets.size() != 1 || job.arg.empty()) {
                r->ok = false;
                r->text = L"Pick one item and a new name.";
            } else if (MoveFileExW(job.targets[0].c_str(), job.arg.c_str(), MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH)) {
                r->text = L"Renamed.";
                r->rescan = false;
            } else {
                r->ok = false;
                r->text = L"Couldn't rename it. " + ErrText(GetLastError()) + L".";
                if (u.failed) r->text += L" " + u.firstError;
            }
            break;
        }
        case J_COPY:
        case J_MOVE: {
            Ctx cx;
            Unlocked u = UnlockAll(job.rows, cx);
            bool move = job.type == J_MOVE;
            HRESULT hr = ShellPlace(job.targets, job.arg, move);
            bool done = SUCCEEDED(hr);
            if (move) {
                for (const auto& t : job.targets)
                    if (Exists(t)) done = false;
            }
            r->ok = done;
            r->text = done ? (move ? L"Moved." : L"Copied.")
                           : std::wstring(move ? L"Couldn't move everything." : L"Couldn't copy everything.") +
                                 (u.failed ? L" " + u.firstError : L"");
            r->rescan = true;
            break;
        }
        case J_REBOOT: {
            bool all = true;
            for (const auto& t : job.targets) all = ScheduleDelete(t) && all;
            r->ok = all;
            r->text = all ? L"It will be deleted when Windows restarts."
                          : L"Couldn't schedule that. It needs the tool to run with full rights.";
            break;
        }
        case J_CLOSE: {
            std::set<DWORD> pids;
            for (const Lock& L : job.rows)
                if (L.safety < 2) pids.insert(L.pid);
            int closed = 0;
            for (DWORD pid : pids) {
                if (CloseProgramPolitely(pid)) closed++;
                else r->stillRunning.push_back(pid);
            }
            r->ok = r->stillRunning.empty();
            r->text = r->ok ? (closed ? L"Closed " + Plural(closed, L"program", L"programs") + L"." : L"Nothing to close.")
                            : Plural((int)r->stillRunning.size(), L"program", L"programs") + L" didn't close.";
            r->rescan = true;
            break;
        }
        case J_END: {
            int ended = 0, failed = 0;
            for (const Lock& L : job.rows) {
                if (L.safety >= 2) continue;
                if (EndProgram(L.pid)) ended++;
                else failed++;
            }
            r->ok = !failed;
            r->text = failed ? L"Couldn't end " + Plural(failed, L"program", L"programs") + L"."
                             : L"Ended " + Plural(ended, L"program", L"programs") + L".";
            r->rescan = true;
            break;
        }
    }
    return r;
}

}  // namespace fu

// ---- Explorer: the right-click entry and the shortcut ---------------------------------------------------------------
// Runs only inside explorer.exe. Both read what is selected in the folder window (or on the desktop) and send the
// paths to the tool process, which owns the unlocker window. Nothing here unlocks anything.

namespace fuex {

static std::atomic<bool> g_menuOn{true};
static HANDLE g_hotThread;
static std::atomic<DWORD> g_hotThreadId;
constexpr UINT WM_APP_HOTKEY_RELOAD = WM_APP + 1;

static bool ClassIs(HWND h, PCWSTR cls) {
    WCHAR buf[64];
    return h && GetClassNameW(h, buf, 64) && !wcscmp(buf, cls);
}

static bool IsShellRoot(HWND root) {
    return ClassIs(root, L"CabinetWClass") || ClassIs(root, L"Progman") || ClassIs(root, L"WorkerW");
}

// What the view has selected, or the folder itself when nothing is. Returns 'S' or 'F', or 0 for nothing usable.
static wchar_t ReadView(IShellBrowser* sb, std::vector<std::wstring>& out) {
    if (!sb) return 0;
    wchar_t kind = 0;
    IShellView* sv = nullptr;
    if (FAILED(sb->QueryActiveShellView(&sv)) || !sv) return 0;
    IFolderView2* fv = nullptr;
    if (SUCCEEDED(sv->QueryInterface(IID_PPV_ARGS(&fv))) && fv) {
        IShellItemArray* sel = nullptr;
        DWORD count = 0;
        if (SUCCEEDED(fv->GetSelection(FALSE, &sel)) && sel && SUCCEEDED(sel->GetCount(&count))) {
            for (DWORD i = 0; i < count; i++) {
                IShellItem* si = nullptr;
                if (FAILED(sel->GetItemAt(i, &si)) || !si) continue;
                PWSTR p = nullptr;
                if (SUCCEEDED(si->GetDisplayName(SIGDN_FILESYSPATH, &p)) && p) {
                    out.push_back(p);
                    CoTaskMemFree(p);
                }
                si->Release();
            }
        }
        if (sel) sel->Release();
        if (!out.empty()) {
            kind = L'S';
        } else {
            IPersistFolder2* pf = nullptr;
            if (SUCCEEDED(fv->GetFolder(IID_PPV_ARGS(&pf))) && pf) {
                PIDLIST_ABSOLUTE pidl = nullptr;
                if (SUCCEEDED(pf->GetCurFolder(&pidl)) && pidl) {
                    WCHAR path[MAX_PATH * 4] = {};
                    if (SHGetPathFromIDListEx(pidl, path, ARRAYSIZE(path), GPFIDL_DEFAULT) && *path) {
                        out.push_back(path);
                        kind = L'F';
                    }
                    CoTaskMemFree(pidl);
                }
                pf->Release();
            }
        }
        fv->Release();
    }
    sv->Release();
    return kind;
}

struct SendJob {
    wchar_t kind;
    std::vector<std::wstring> paths;
};

static DWORD WINAPI SendThread(void* p) {
    std::unique_ptr<SendJob> job((SendJob*)p);
    HWND tray = FindWindowW(kFuTrayClass, nullptr);
    if (!tray) {
        Wh_Log(L"The unlocker window isn't running yet");
        return 0;
    }
    std::wstring blob(1, job->kind);
    for (const auto& s : job->paths) {
        blob += s;
        blob += L'\0';
    }
    DWORD pid = 0;
    GetWindowThreadProcessId(tray, &pid);
    if (pid) AllowSetForegroundWindow(pid);
    COPYDATASTRUCT cd{kFuCopyPaths, (DWORD)(blob.size() * sizeof(WCHAR)), (void*)blob.data()};
    DWORD_PTR r = 0;
    SendMessageTimeoutW(tray, WM_COPYDATA, 0, (LPARAM)&cd, SMTO_ABORTIFHUNG, 2000, &r);
    return 0;
}

// Hands the paths to a short-lived thread so Explorer's own window never waits on the tool process.
static void Send(wchar_t kind, std::vector<std::wstring>&& paths) {
    if (!kind || paths.empty()) return;
    auto* job = new SendJob{kind, std::move(paths)};
    HANDLE t = CreateThread(nullptr, 0, SendThread, job, 0, nullptr);
    if (t) CloseHandle(t);
    else delete job;
}

// ---- The right-click entry ------------------------------------------------------------------------------------------

using TrackPopupMenu_t = BOOL(WINAPI*)(HMENU, UINT, int, int, int, HWND, const RECT*);
using TrackPopupMenuEx_t = BOOL(WINAPI*)(HMENU, UINT, int, int, HWND, LPTPMPARAMS);
static TrackPopupMenu_t TrackPopupMenu_Orig;
static TrackPopupMenuEx_t TrackPopupMenuEx_Orig;
static thread_local bool t_inMenu;

static std::wstring PlainText(HMENU m, UINT pos) {
    WCHAR buf[128] = {};
    MENUITEMINFOW mi{sizeof(mi)};
    mi.fMask = MIIM_STRING | MIIM_FTYPE;
    mi.dwTypeData = buf;
    mi.cch = ARRAYSIZE(buf) - 1;
    if (!GetMenuItemInfoW(m, pos, TRUE, &mi) || (mi.fType & MFT_SEPARATOR)) return {};
    std::wstring s;
    for (PCWSTR p = buf; *p && *p != L'\t'; p++)
        if (*p != L'&') s += *p;
    return s;
}

static bool IdUsed(HMENU m, UINT id, int depth = 0) {
    if (depth > 6) return false;
    int n = GetMenuItemCount(m);
    for (int i = 0; i < n; i++) {
        if (GetMenuItemID(m, i) == id) return true;
        if (HMENU sub = GetSubMenu(m, i))
            if (IdUsed(sub, id, depth + 1)) return true;
    }
    return false;
}

// Returns where Properties sits when this is a file or folder menu in a folder window or on the desktop, else -1.
static int PropsPos(HMENU m, HWND owner) {
    if (!g_menuOn || !m || !IsShellRoot(GetAncestor(owner, GA_ROOT))) return -1;
    int n = GetMenuItemCount(m), props = -1;
    for (int i = 0; i < n; i++)
        if (PlainText(m, (UINT)i) == L"Properties") props = i;
    return n >= 4 ? props : -1;
}

static IShellBrowser* BrowserOf(HWND h) {
    for (HWND w = h; w; w = GetParent(w)) {
        DWORD_PTR r = 0;
        if (SendMessageTimeoutW(w, WM_USER + 7, 0, 0, SMTO_ABORTIFHUNG, 500, &r) && r) return (IShellBrowser*)r;
        if (GetWindowLongPtrW(w, GWL_STYLE) & WS_CHILD) continue;
        break;
    }
    return nullptr;
}

static std::wstring_view kEntry = L"What's locking this?";

template <class F>
static BOOL Around(HMENU m, UINT flags, HWND owner, F call) {
    int pos = t_inMenu ? -1 : PropsPos(m, owner);
    if (pos < 0) return call(flags);
    UINT id = 0x7FF0;
    while (id > 0x7000 && IdUsed(m, id)) id--;
    if (!InsertMenuW(m, (UINT)pos, MF_BYPOSITION | MF_STRING, id, kEntry.data())) return call(flags);
    t_inMenu = true;
    BOOL r = call(flags | TPM_RETURNCMD);
    t_inMenu = false;
    DeleteMenu(m, id, MF_BYCOMMAND);
    if ((UINT)r == id) {
        std::vector<std::wstring> paths;
        wchar_t kind = ReadView(BrowserOf(owner), paths);
        Send(kind, std::move(paths));
        return (flags & TPM_RETURNCMD) ? 0 : TRUE;
    }
    if (flags & TPM_RETURNCMD) return r;
    if (r && !(flags & TPM_NONOTIFY)) PostMessageW(owner, WM_COMMAND, MAKEWPARAM((UINT)r, 0), 0);
    return r ? TRUE : FALSE;
}

static BOOL WINAPI TrackPopupMenu_Hook(HMENU m, UINT flags, int x, int y, int res, HWND owner, const RECT* rc) {
    return Around(m, flags, owner, [&](UINT f) { return TrackPopupMenu_Orig(m, f, x, y, res, owner, rc); });
}

static BOOL WINAPI TrackPopupMenuEx_Hook(HMENU m, UINT flags, int x, int y, HWND owner, LPTPMPARAMS tpm) {
    return Around(m, flags, owner, [&](UINT f) { return TrackPopupMenuEx_Orig(m, f, x, y, owner, tpm); });
}

static bool HookMenus() {
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    void* a = user32 ? (void*)GetProcAddress(user32, "TrackPopupMenu") : nullptr;
    void* b = user32 ? (void*)GetProcAddress(user32, "TrackPopupMenuEx") : nullptr;
    bool ok = a && b && Wh_SetFunctionHook(a, (void*)TrackPopupMenu_Hook, (void**)&TrackPopupMenu_Orig) &&
              Wh_SetFunctionHook(b, (void*)TrackPopupMenuEx_Hook, (void**)&TrackPopupMenuEx_Orig);
    if (!ok) Wh_Log(L"Couldn't hook the right-click menu");
    return ok;
}

// ---- The shortcut ---------------------------------------------------------------------------------------------------
// Registered only while one of this Explorer's own windows is in front, so the keys stay free in every other app.

static UINT g_hotMods, g_hotVk;
static bool g_hotOn;

static bool OwnShellWindow(HWND fg) {
    if (!fg || !IsShellRoot(fg)) return false;
    DWORD pid = 0;
    GetWindowThreadProcessId(fg, &pid);
    return pid == GetCurrentProcessId();
}

static void ReadHotkey() {
    if (!Hotkey_Parse(SettingString(L"unlockHotkey"), g_hotMods, g_hotVk)) g_hotMods = g_hotVk = 0;
}

static void SyncHotkey(HWND fg) {
    bool want = g_hotVk && OwnShellWindow(fg);
    if (want == g_hotOn) return;
    if (want) {
        g_hotOn = RegisterHotKey(nullptr, 1, g_hotMods | MOD_NOREPEAT, g_hotVk) != FALSE;
        if (!g_hotOn) Wh_Log(L"Another app already uses the shortcut");
    } else {
        UnregisterHotKey(nullptr, 1);
        g_hotOn = false;
    }
}

static void CALLBACK OnForeground(HWINEVENTHOOK, DWORD, HWND hwnd, LONG idObject, LONG, DWORD, DWORD) {
    if (idObject == OBJID_WINDOW) SyncHotkey(hwnd);
}

// The active tab of a folder window, or the desktop.
static IShellBrowser* ForegroundBrowser(HWND fg, IShellWindows* sw) {
    if (!sw) return nullptr;
    if (ClassIs(fg, L"Progman") || ClassIs(fg, L"WorkerW")) {
        VARIANT empty{};
        long h = 0;
        IDispatch* disp = nullptr;
        if (FAILED(sw->FindWindowSW(&empty, &empty, SWC_DESKTOP, &h, SWFO_NEEDDISPATCH, &disp)) || !disp)
            return nullptr;
        IShellBrowser* sb = nullptr;
        IServiceProvider* sp = nullptr;
        if (SUCCEEDED(disp->QueryInterface(IID_PPV_ARGS(&sp))) && sp) {
            sp->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&sb));
            sp->Release();
        }
        disp->Release();
        return sb;
    }
    HWND activeTab = FindWindowExW(fg, nullptr, L"ShellTabWindowClass", nullptr);
    long count = 0;
    sw->get_Count(&count);
    IShellBrowser* pick = nullptr;
    for (long i = 0; i < count && !pick; i++) {
        VARIANT v{};
        v.vt = VT_I4;
        v.lVal = i;
        IDispatch* disp = nullptr;
        if (FAILED(sw->Item(v, &disp)) || !disp) continue;
        IWebBrowserApp* app = nullptr;
        SHANDLE_PTR h = 0;
        if (SUCCEEDED(disp->QueryInterface(IID_PPV_ARGS(&app))) && app) {
            app->get_HWND(&h);
            app->Release();
        }
        if ((HWND)h == fg) {
            IServiceProvider* sp = nullptr;
            IShellBrowser* sb = nullptr;
            if (SUCCEEDED(disp->QueryInterface(IID_PPV_ARGS(&sp))) && sp) {
                sp->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&sb));
                sp->Release();
            }
            if (sb) {
                HWND tab = nullptr;
                if (!activeTab || (SUCCEEDED(sb->GetWindow(&tab)) && tab == activeTab)) pick = sb;
                else sb->Release();
            }
        }
        disp->Release();
    }
    return pick;
}

static void OnHotkey() {
    HWND fg = GetForegroundWindow();
    if (!OwnShellWindow(fg)) return;
    IShellWindows* sw = nullptr;
    if (FAILED(CoCreateInstance(CLSID_ShellWindows, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&sw))) || !sw) return;
    IShellBrowser* sb = ForegroundBrowser(fg, sw);
    std::vector<std::wstring> paths;
    wchar_t kind = ReadView(sb, paths);
    if (sb) sb->Release();
    sw->Release();
    Send(kind, std::move(paths));
}

static DWORD WINAPI HotkeyThread(void*) {
    HRESULT co = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    MSG m;
    PeekMessageW(&m, nullptr, WM_USER, WM_USER, PM_NOREMOVE);  // the queue exists before anyone posts to it
    ReadHotkey();
    HWINEVENTHOOK hook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, OnForeground, 0, 0,
                                         WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNTHREAD);
    SyncHotkey(GetForegroundWindow());
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {
        if (!m.hwnd && m.message == WM_HOTKEY) {
            OnHotkey();
            continue;
        }
        if (!m.hwnd && m.message == WM_APP_HOTKEY_RELOAD) {
            if (g_hotOn) UnregisterHotKey(nullptr, 1);
            g_hotOn = false;
            ReadHotkey();
            SyncHotkey(GetForegroundWindow());
            continue;
        }
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    if (g_hotOn) UnregisterHotKey(nullptr, 1);
    g_hotOn = false;
    if (hook) UnhookWinEvent(hook);
    if (SUCCEEDED(co)) CoUninitialize();
    return 0;
}

static void StartHotkeyThread() {
    DWORD id = 0;
    g_hotThread = CreateThread(nullptr, 0, HotkeyThread, nullptr, 0, &id);
    g_hotThreadId = id;
}

static void ReloadHotkey() {
    if (DWORD id = g_hotThreadId) PostThreadMessageW(id, WM_APP_HOTKEY_RELOAD, 0, 0);
}

static void StopHotkeyThread() {
    if (!g_hotThread) return;
    if (DWORD id = g_hotThreadId) PostThreadMessageW(id, WM_QUIT, 0, 0);
    if (WaitForSingleObject(g_hotThread, 5000) == WAIT_TIMEOUT) Wh_Log(L"The shortcut thread did not stop");
    CloseHandle(g_hotThread);
    g_hotThread = nullptr;
    g_hotThreadId = 0;
}

}  // namespace fuex

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-26-seamless-file-unlocker\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace fuset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessFileUnlockerSettings";
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
// Generated by work\2026-11-26-seamless-file-unlocker\gen.py from the settings block.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Hotkey, L"unlockHotkey", L"Shortcut", L"Press it in Explorer or on the desktop to see what is holding the selected items, or the folder when nothing is selected.", L"Ctrl+Shift+U", {}, 0, 100, 0, L"Behaviour"},
{K::Check, L"menuEntry", L"Right-click menu entry", L"Adds What's locking this? above Properties. It shows under Show more options.", L"1", {}, 0, 100, 0, L"Behaviour"},
{K::Check, L"askBeforeClosing", L"Ask before closing programs", L"Ask first before a program is closed or a loaded DLL is unloaded.", L"1", {}, 0, 100, 0, L"Behaviour"},
{K::Check, L"recycleBin", L"Delete to the Recycle Bin", L"On, Delete sends items to the Recycle Bin. Off, they are deleted for good.", L"1", {}, 0, 100, 0, L"Behaviour"},
{K::Check, L"showSystem", L"Show system programs", L"Also list the programs Windows runs for itself. They can be seen but never closed.", L"0", {}, 0, 100, 0, L"Behaviour"},
{K::Check, L"settingsAnimation", L"Open and close animation", L"The window fades in with a short slide. Stays still when Windows animations are off.", L"1", {}, 0, 100, 1, L"Settings window"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 1, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 1, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"An icon in the tray. Click it to open the window. Right-click for settings.", L"1", {}, 0, 100, 1, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Behaviour", L"The shortcut, the right-click entry and what happens when you let go of a lock.", 0xE713},
{L"Look", L"Choose how this window looks and whether its tray icon is shown.", 0xE771},
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
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetCreditLockHunter = L"https://lockhunter.com";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/seamless-workshop";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/seamless-workshop/issues/new?title=%5BSeamless%20File%20Unlocker%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless File Unlocker";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"File Unlocker") <= railW) break;
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
    return !w.render && g_fuAnim && on;
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

// A colour row needs 362 DIP for its hex box and chips; when that leaves the label under 200 DIP,
// the chips drop to a line of their own under the text.
constexpr float kSgcColorFullW = 362, kSgcLabelMinW = 200, kSgcChipLine = 30;
static bool ColorRowStacked(const SetField& f, float rowW) {
    return f.kind == SetField::Color && rowW - 2 * kSetRowPad - kSgcColorFullW - 24 < kSgcLabelMinW;
}
static float RowControlW(const SetField& f, float rowW) { return ColorRowStacked(f, rowW) ? 96 : Set_ControlW(f); }

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

struct SetPaint;
static float Fu_PaneW(const SetWindow&);
static float Fu_ThumbX(const SetWindow&);
static LONG Fu_MinSide(HWND, int, UINT, bool);
static void Fu_DrawPane(SetPaint&, SetWindow&);
static void Fu_Attach();

// A window too narrow for the open sidebar, the page and the locks list folds the sidebar to its icons by itself,
// and opens it again once there is room. Opening it by hand while narrow is respected until the window widens.
static bool g_fuRailAuto = false, g_fuRailKeep = false;
static void Fu_FitRail(SetWindow& w) {
    const bool narrow = w.cw < kSetDockGap + w.railW + 14 + 500 + 380;
    if (!narrow) {
        g_fuRailKeep = false;
        if (g_fuRailAuto) { g_fuRailAuto = false; w.railCollapsed = false; }
        return;
    }
    if (g_fuRailAuto && !w.railCollapsed) { g_fuRailAuto = false; g_fuRailKeep = true; }
    if (!w.railCollapsed && !g_fuRailKeep) { w.railCollapsed = true; g_fuRailAuto = true; }
}

// Lays out the current page's items for the current width. The locks list takes the right side of the window, so
// the page is centred in what is left of it.
static void Set_BuildPage(SetWindow& w) {
    w.items.clear();
    Fu_FitRail(w);
    const float space = Set_RailSpace(w), paneW = Fu_PaneW(w);
    const float avail = w.cw - space - paneW - (paneW > 0 ? 14 : 0);
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, kSetMaxW);
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), kSetPages[w.page].intro, w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
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
        float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh);
        y += it.h + kSetRowGap;
        w.items.push_back(it);
    }
    auto add = [&](SetItem::Type t, float h, const std::wstring& text, const std::wstring& sub, const std::wstring& url) {
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
    if (w.page == kSetAboutPage) {
        add(SetItem::About, 146, L"", L"", L"");
        add(SetItem::Support, 84, L"Like it? Help the mod keep going.",
            L"Free and open source. A tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        add(SetItem::Link, 56, L"Inspired by LockHunter", L"By Crystal Rich. No code from it is used",
            kSetCreditLockHunter);
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/seamless-workshop", kSetRepoUrl);
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
    return {Fu_ThumbX(w) - 18, top + 4, Fu_ThumbX(w) - 12, top + th - 4};
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
    {  // The glyph alone in the gradient, no plate (owner, 2026-11-24).
        D2D1_MATRIX_3X2_F old;
        p.rt->GetTransform(&old);
        const D2D1_POINT_2F mc{(mark.left + mark.right) / 2, (mark.top + mark.bottom) / 2};
        p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.75f, 1.75f, mc) * old);
        const WCHAR glyph = 0xE785;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless File Unlocker", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"See what is holding a file or folder, then let go of it, move it or delete it.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, inspired by LockHunter.",
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
    p.Edge(d, rad, mocha::surface1, 0.9f * (1 - glow), 2);
    p.GradRing(d, rad - 1, glow, 2);
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
    if (edge > 0.003f) p.GradRing(d, 12.5f, edge, 3);

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
    p.Text(w.fRailName.get(), L"File Unlocker", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    // The mod's glyph alone in the blue to mauve gradient on a clear background, no plate
    // (owner, 2026-11-24), scaled up about its centre to fill the room the plate had.
    const float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    const float ix = (r.right - r.left) * 0.31f, iy = (r.bottom - r.top) * 0.31f;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (FAILED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) ||
        FAILED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(cx - ix, cy - iy), D2D1::Point2F(cx + ix, cy + iy)),
            coll.get(), g.put())))
        return;
    D2D1_MATRIX_3X2_F old;
    p.rt->GetTransform(&old);
    p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.4f, 1.4f, D2D1::Point2F(cx, cy)) * old);
    const WCHAR mark = 0xE785;
    p.rt->DrawText(&mark, 1, glyph, r, g.get());
    p.rt->SetTransform(old);
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

    Fu_DrawPane(p, w);
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
    if (th.bottom > th.top && x >= Fu_ThumbX(w) - 16 && y >= th.top && y <= th.bottom) {
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
            RECT r{0, 0, Fu_MinSide(hwnd, 1180, w->dpi, false), Fu_MinSide(hwnd, 640, w->dpi, true)};
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
                SetState(StateKey(L"Settings", L"RailCollapsed").c_str(), (w->railCollapsed && !g_fuRailAuto) ? 1 : 0);
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless File Unlocker settings", style,
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
    outer(1320, 780, size);
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
 if (g_settingsStop && g_settingsWnd) PostMessageW(g_settingsWnd,WM_CLOSE,0,0);  // closed while opening
 if (g_setWin) Fu_Attach();
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
// ---- The locks list -------------------------------------------------------------------------------------------------
// A dock on the right of the settings window: what is holding the picked items, and the buttons to let go of it.
// The pages on the left are the settings. Every job runs on a worker thread and the window only ever paints.

static constexpr UINT WM_APP_FU_TAKE = WM_APP + 60, WM_APP_FU_DONE = WM_APP + 62, WM_APP_FU_CMD = WM_APP + 70,
                      WM_APP_FU_STATE = WM_APP + 71;
static constexpr UINT_PTR kFuTimer = 0xB0, kFuSubclass = 0xB1;
static constexpr float kFuRowH = 64;

struct FuPane {
    std::vector<std::wstring> targets;
    std::vector<fu::Lock> rows;
    std::set<size_t> sel;
    bool scanning = false, busy = false, scanned = false, partial = false, missing = false, failed = false;
    int denied = 0, hidden = 0;
    std::wstring failText;
    float scroll = 0, scrollTarget = 0, dragOff = 0;
    bool dragThumb = false, tracking = false, timer = false;
    std::map<int, float> glow;
    int hover = -1;
    std::wstring status;
    bool statusError = false;
    // The question card in front of a risky action.
    bool asking = false;
    std::wstring askTitle, askBody, askYes;
    std::function<void(SetWindow&)> onYes;
    float askShow = 0;
    float paneGlow = 0;  // The locks dock's edge lights blue to mauve while the pointer is over it.
    bool inPane = false;
    SetCom<IDWriteTextFormat> fCenter, fWrap, fChip;
    std::map<std::wstring, IWICBitmapSource*> iconsWic;
    std::map<std::wstring, ID2D1Bitmap*> iconsD2d;
    ID2D1RenderTarget* iconRt = nullptr;
    int iconBudget = 0;
    ~FuPane() {
        for (auto& [k, v] : iconsWic)
            if (v) v->Release();
        for (auto& [k, v] : iconsD2d)
            if (v) v->Release();
    }
};
static FuPane* g_pane = nullptr;
static HANDLE g_fuWorker = nullptr;
static std::atomic<bool> g_fuCancel{false};
[[clang::no_destroy]] static std::mutex g_fuQueueLock;
[[clang::no_destroy]] static std::vector<std::pair<std::vector<std::wstring>, bool>> g_fuQueue;

static const WCHAR kFuPillGlyph[4] = {0xE72C, 0xE785, 0xE74D, 0xE712};
static const PCWSTR kFuPillText[4] = {L"Refresh", L"Unlock", L"Delete", L"More"};

// What a setting says right now in the window.
static std::wstring Fu_Get(const SetWindow& w, PCWSTR key) {
    for (const SetField& f : w.fields)
        if (wcscmp(f.key, key) == 0) return Set_FieldValue(f);
    return SettingString(key);
}

static bool Fu_On(const SetWindow& w, PCWSTR key) {
    std::wstring v = Fu_Get(w, key);
    return v == L"1" || v == L"true";
}

static std::wstring Fu_Count(int n, PCWSTR one, PCWSTR many) { return std::to_wstring(n) + L" " + (n == 1 ? one : many); }

// ---- Layout ---------------------------------------------------------------------------------------------------------

static float Fu_PaneW(const SetWindow& w) {
    return std::clamp(w.cw - Set_RailSpace(w) - 14 - 520, 380.0f, 760.0f);
}

static float Fu_ThumbX(const SetWindow& w) { return w.cw - Fu_PaneW(w) - 24; }

static LONG Fu_MinSide(HWND hwnd, int want, UINT dpi, bool tall) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST), &mi);
    LONG room = tall ? mi.rcWork.bottom - mi.rcWork.top : mi.rcWork.right - mi.rcWork.left;
    return std::min<LONG>(MulDiv(want, dpi, 96), room * 9 / 10);
}

static D2D1_RECT_F Fu_Pane(const SetWindow& w) {
    float pw = Fu_PaneW(w);
    return {w.cw - pw - 10, 10, w.cw - 10, w.ch - 10};
}

static D2D1_RECT_F Fu_ListRect(const SetWindow& w) {
    D2D1_RECT_F P = Fu_Pane(w);
    return {P.left + 8, P.top + 146, P.right - 8, P.bottom - 56};
}

struct FuPills {
    D2D1_RECT_F r[4];
    bool label[4];
};

static FuPills Fu_Pills(const SetWindow& w) {
    D2D1_RECT_F P = Fu_Pane(w);
    FuPills b{};
    float left = P.left + 20, avail = P.right - 20 - left, gap = 8, tw[4];
    for (int i = 0; i < 4; i++) {
        b.label[i] = true;
        tw[i] = (w.fSmall ? Set_TextW(w.fSmall.get(), kFuPillText[i]) : 60) + 12 + 16 + 8 + 14;
    }
    auto total = [&] {
        float s = gap * 3;
        for (int i = 0; i < 4; i++) s += b.label[i] ? tw[i] : 32;
        return s;
    };
    if (total() > avail) b.label[0] = b.label[3] = false;
    if (total() > avail) b.label[1] = b.label[2] = false;
    float x = left;
    for (int i = 0; i < 4; i++) {
        float wd = b.label[i] ? tw[i] : 32;
        b.r[i] = {x, P.top + 76, x + wd, P.top + 108};
        x += wd + gap;
    }
    return b;
}

static float Fu_MaxScroll(const SetWindow& w) {
    if (!g_pane) return 0;
    D2D1_RECT_F L = Fu_ListRect(w);
    return std::max(0.0f, g_pane->rows.size() * kFuRowH - (L.bottom - L.top));
}

static D2D1_RECT_F Fu_Thumb(const SetWindow& w) {
    D2D1_RECT_F L = Fu_ListRect(w);
    float view = L.bottom - L.top, content = g_pane ? g_pane->rows.size() * kFuRowH : 0;
    if (content <= view || view <= 0) return {};
    float th = std::max(30.0f, view * view / content), range = content - view;
    float top = L.top + (g_pane->scroll / range) * (view - th);
    return {L.right - 8, top + 2, L.right - 4, top + th - 2};
}

// The question card, centred in the pane, and its two buttons.
static D2D1_RECT_F Fu_Card(const SetWindow& w) {
    D2D1_RECT_F P = Fu_Pane(w);
    float cw = std::min(400.0f, P.right - P.left - 40), cx = (P.left + P.right) / 2, cy = (P.top + P.bottom) / 2;
    return {cx - cw / 2, cy - 110, cx + cw / 2, cy + 110};
}

static D2D1_RECT_F Fu_AskBtn(const SetWindow& w, bool yes) {
    D2D1_RECT_F c = Fu_Card(w);
    float mid = (c.left + c.right) / 2;
    return yes ? D2D1_RECT_F{mid + 6, c.bottom - 56, c.right - 20, c.bottom - 18}
               : D2D1_RECT_F{c.left + 20, c.bottom - 56, mid - 6, c.bottom - 18};
}

// 0 inside the pane on nothing, -1 outside it. 1-4 the pills, 6 the scroll thumb, 20 Yes, 21 No, 100+ a row.
static int Fu_HitAt(const SetWindow& w, float x, float y) {
    if (!g_pane) return -1;
    D2D1_RECT_F P = Fu_Pane(w);
    if (!Set_In(P, x, y)) return -1;
    if (g_pane->asking) {
        if (Set_In(Fu_AskBtn(w, true), x, y)) return 20;
        if (Set_In(Fu_AskBtn(w, false), x, y)) return 21;
        return 0;
    }
    FuPills b = Fu_Pills(w);
    for (int i = 0; i < 4; i++)
        if (Set_In(b.r[i], x, y)) return 1 + i;
    D2D1_RECT_F L = Fu_ListRect(w);
    if (!Set_In(L, x, y)) return 0;
    D2D1_RECT_F th = Fu_Thumb(w);
    if (th.bottom > th.top && x >= L.right - 14) return 6;
    int i = (int)((y - L.top + g_pane->scroll) / kFuRowH);
    if (i >= 0 && i < (int)g_pane->rows.size()) return 100 + i;
    return 0;
}

static bool Fu_Clickable(int id) {
    if (!g_pane || id <= 0) return false;
    FuPane& pn = *g_pane;
    if (pn.asking) return id == 20 || id == 21;
    if (id >= 100 || id == 6) return true;
    if (pn.busy || pn.scanning) return false;
    if (id == 1 || id == 3 || id == 4) return !pn.targets.empty();
    if (id == 2) return !pn.rows.empty();
    return false;
}

// ---- Programs' icons ------------------------------------------------------------------------------------------------

static ID2D1Bitmap* Fu_Icon(FuPane& pn, ID2D1RenderTarget* rt, const std::wstring& exe) {
    if (pn.iconRt != rt) {
        for (auto& [k, v] : pn.iconsD2d)
            if (v) v->Release();
        pn.iconsD2d.clear();
        pn.iconRt = rt;
    }
    std::wstring key = fu::Lower(exe);
    auto d = pn.iconsD2d.find(key);
    if (d != pn.iconsD2d.end()) return d->second;
    IWICBitmapSource* src = nullptr;
    auto wi = pn.iconsWic.find(key);
    if (wi != pn.iconsWic.end()) {
        src = wi->second;
    } else {
        if (pn.iconBudget <= 0) return nullptr;  // a few new icons per frame, so a long list never stalls
        pn.iconBudget--;
        SHFILEINFOW sfi{};
        UINT flags = SHGFI_ICON | SHGFI_LARGEICON;
        PCWSTR name = exe.c_str();
        DWORD attr = 0;
        if (exe.empty() || GetFileAttributesW(exe.c_str()) == INVALID_FILE_ATTRIBUTES) {
            name = L".exe";
            flags |= SHGFI_USEFILEATTRIBUTES;
            attr = FILE_ATTRIBUTE_NORMAL;
        }
        if (SHGetFileInfoW(name, attr, &sfi, sizeof(sfi), flags) && sfi.hIcon && g_setWic) {
            IWICBitmap* bmp = nullptr;
            if (SUCCEEDED(g_setWic->CreateBitmapFromHICON(sfi.hIcon, &bmp)) && bmp) {
                IWICFormatConverter* conv = nullptr;
                if (SUCCEEDED(g_setWic->CreateFormatConverter(&conv)) && conv) {
                    if (SUCCEEDED(conv->Initialize(bmp, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0,
                                                   WICBitmapPaletteTypeCustom)))
                        src = conv;
                    else
                        conv->Release();
                }
                bmp->Release();
            }
        }
        if (sfi.hIcon) DestroyIcon(sfi.hIcon);
        pn.iconsWic[key] = src;
    }
    ID2D1Bitmap* out = nullptr;
    if (src) rt->CreateBitmapFromWicBitmap(src, nullptr, &out);
    pn.iconsD2d[key] = out;
    return out;
}

// ---- Jobs -----------------------------------------------------------------------------------------------------------

static void Fu_Status(PCWSTR text, bool error = false) {
    if (!g_pane) return;
    g_pane->status = text;
    g_pane->statusError = error;
}

static void Fu_Kick(SetWindow& w) {
    if (!g_pane || g_pane->timer || !w.hwnd) return;
    g_pane->timer = SetTimer(w.hwnd, kFuTimer, 15, nullptr) != 0;
}

struct FuWork {
    fu::Job* job;
    HWND hwnd;
};

static DWORD WINAPI Fu_Worker(void* arg) {
    auto* work = (FuWork*)arg;
    HRESULT co = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    fu::Result* r = nullptr;
    try {
        r = fu::Run(*work->job);
    } catch (...) {
        r = new fu::Result;
        r->type = work->job->type;
        r->ok = false;
        r->found.failed = work->job->type == fu::J_SCAN;
        r->found.error = L"Something went wrong while looking.";
        r->text = L"Something went wrong partway.";
    }
    HWND hwnd = work->hwnd;
    delete work->job;
    delete work;
    if (!PostMessageW(hwnd, WM_APP_FU_DONE, 0, (LPARAM)r)) delete r;
    if (SUCCEEDED(co)) CoUninitialize();
    return 0;
}

static bool Fu_Start(SetWindow& w, fu::Job* job) {
    if (g_fuWorker) {
        if (WaitForSingleObject(g_fuWorker, 0) == WAIT_TIMEOUT) {
            delete job;
            return false;
        }
        CloseHandle(g_fuWorker);
        g_fuWorker = nullptr;
    }
    job->cancel = &g_fuCancel;
    g_fuCancel = false;
    auto* work = new FuWork{job, w.hwnd};
    g_fuWorker = CreateThread(nullptr, 0, Fu_Worker, work, 0, nullptr);
    if (!g_fuWorker) {
        delete job;
        delete work;
        return false;
    }
    if (job->type == fu::J_SCAN) g_pane->scanning = true;
    else g_pane->busy = true;
    Fu_Kick(w);
    Set_Invalidate(w);
    return true;
}

static void Fu_Scan(SetWindow& w) {
    if (!g_pane) return;
    FuPane& pn = *g_pane;
    if (pn.targets.empty()) {
        pn.rows.clear();
        pn.scanned = false;
        Set_Invalidate(w);
        return;
    }
    auto* job = new fu::Job;
    job->type = fu::J_SCAN;
    job->targets = pn.targets;
    job->showSystem = Fu_On(w, L"showSystem");
    fu::g_prog.done = fu::g_prog.total = 0;
    if (!Fu_Start(w, job)) Fu_Status(L"Still busy. Try again in a moment.");
}

static void Fu_SetTargets(SetWindow& w, std::vector<std::wstring> paths) {
    if (!g_pane || paths.empty()) return;
    FuPane& pn = *g_pane;
    pn.targets = std::move(paths);
    pn.rows.clear();
    pn.sel.clear();
    pn.scroll = pn.scrollTarget = 0;
    pn.scanned = pn.missing = pn.failed = pn.partial = false;
    pn.denied = pn.hidden = 0;
    Fu_Status(L"");
    if (g_fuWorker && WaitForSingleObject(g_fuWorker, 0) == WAIT_TIMEOUT) {
        Fu_Status(L"Finishing the last job first...");
        Set_Invalidate(w);
        return;
    }
    Fu_Scan(w);
}

// The rows an action works on: the ticked ones, or all of them when none is ticked.
static std::vector<fu::Lock> Fu_ActRows(const FuPane& pn) {
    std::vector<fu::Lock> v;
    for (size_t i = 0; i < pn.rows.size(); i++)
        if (pn.sel.empty() || pn.sel.count(i)) v.push_back(pn.rows[i]);
    return v;
}

static std::wstring Fu_Names(const std::vector<fu::Lock>& rows) {
    std::vector<std::wstring> names;
    for (const auto& r : rows)
        if (std::find(names.begin(), names.end(), r.name) == names.end()) names.push_back(r.name);
    std::wstring s;
    for (size_t i = 0; i < names.size() && i < 3; i++) s += (i ? L", " : L"") + names[i];
    if (names.size() > 3) s += L" and " + std::to_wstring(names.size() - 3) + L" more";
    return s;
}

static std::wstring Fu_TargetName(const FuPane& pn) {
    if (pn.targets.empty()) return L"Nothing picked yet";
    if (pn.targets.size() == 1) {
        PCWSTR n = PathFindFileNameW(pn.targets[0].c_str());
        return *n ? n : pn.targets[0];
    }
    return std::to_wstring(pn.targets.size()) + L" items";
}

static void Fu_Ask(SetWindow& w, std::wstring title, std::wstring body, std::wstring yes,
                   std::function<void(SetWindow&)> onYes) {
    FuPane& pn = *g_pane;
    pn.asking = true;
    pn.askTitle = std::move(title);
    pn.askBody = std::move(body);
    pn.askYes = std::move(yes);
    pn.onYes = std::move(onYes);
    pn.askShow = Set_Anim(w) ? 0.0f : 1.0f;
    Fu_Kick(w);
    Set_Invalidate(w);
}

static void Fu_AnswerAsk(SetWindow& w, bool yes) {
    if (!g_pane || !g_pane->asking) return;
    auto go = std::move(g_pane->onYes);
    g_pane->asking = false;
    g_pane->onYes = nullptr;
    Set_Invalidate(w);
    if (yes && go) go(w);
}

static void Fu_Run(SetWindow& w, int type, std::vector<fu::Lock> rows, std::wstring arg = L"") {
    if (!g_pane) return;
    auto* job = new fu::Job;
    job->type = type;
    job->targets = g_pane->targets;
    job->rows = std::move(rows);
    job->arg = std::move(arg);
    job->toBin = Fu_On(w, L"recycleBin");
    job->showSystem = Fu_On(w, L"showSystem");
    Fu_Status(L"");
    if (!Fu_Start(w, job)) {
        Fu_Status(L"Still busy. Try again in a moment.");
        Set_Invalidate(w);
    }
}

// A line about what is risky in these rows, or nothing.
static std::wstring Fu_Risks(const std::vector<fu::Lock>& rows) {
    std::wstring s;
    bool dll = false, expl = false, sys = false;
    for (const auto& r : rows) {
        if (r.kind == fu::kDll) dll = true;
        if (r.safety == 1) expl = true;
        if (r.safety == 2) sys = true;
    }
    if (dll) s += L" A loaded DLL is taken out of the program, which can make it crash.";
    if (expl) s += L" One of them is Windows Explorer, so your desktop and taskbar may flash.";
    if (sys) s += L" Windows' own programs are left alone.";
    return s;
}

static bool Fu_Risky(const std::vector<fu::Lock>& rows) {
    for (const auto& r : rows)
        if (r.safety == 1) return true;
    return false;
}

// ---- The actions ----------------------------------------------------------------------------------------------------

static void Fu_DoUnlock(SetWindow& w, bool force) {
    if (!g_pane || g_pane->busy || g_pane->scanning) return;
    std::vector<fu::Lock> rows = Fu_ActRows(*g_pane);
    if (rows.empty()) return;
    bool ask = !force && (Fu_On(w, L"askBeforeClosing") || Fu_Risky(rows));
    if (!ask) {
        Fu_Run(w, fu::J_UNLOCK, rows);
        return;
    }
    std::wstring body = L"This lets go of " + Fu_Count((int)rows.size(), L"lock", L"locks") + L" held by " + Fu_Names(rows) +
                        L". The programs keep running, but can lose what they were doing with the file. Save your work "
                        L"in them first." +
                        Fu_Risks(rows);
    Fu_Ask(w, L"Let go of it?", body, L"Unlock", [rows](SetWindow& ww) { Fu_Run(ww, fu::J_UNLOCK, rows); });
}

static void Fu_DoDelete(SetWindow& w, bool force) {
    if (!g_pane || g_pane->busy || g_pane->scanning || g_pane->targets.empty()) return;
    std::vector<fu::Lock> rows = g_pane->rows;
    bool bin = Fu_On(w, L"recycleBin") && fu::BinPossible(g_pane->targets);
    if (force) {
        Fu_Run(w, fu::J_DELETE, rows);
        return;
    }
    std::wstring what = g_pane->targets.size() == 1 ? L"\"" + Fu_TargetName(*g_pane) + L"\"" : Fu_TargetName(*g_pane);
    std::wstring body = L"Delete " + what + L"? " +
                        (bin ? L"It goes to the Recycle Bin, so you can get it back."
                             : L"It is deleted for good. It does not go to the Recycle Bin.") +
                        L" Programs holding it are let go first." + Fu_Risks(rows);
    Fu_Ask(w, L"Delete it?", body, L"Delete", [rows](SetWindow& ww) { Fu_Run(ww, fu::J_DELETE, rows); });
}

static void Fu_DoReboot(SetWindow& w, bool force) {
    if (!g_pane || g_pane->busy || g_pane->scanning || g_pane->targets.empty()) return;
    if (force) {
        Fu_Run(w, fu::J_REBOOT, {});
        return;
    }
    Fu_Ask(w, L"Delete at the next restart?",
           L"Windows deletes " + Fu_TargetName(*g_pane) +
               L" the next time it starts, before any program can open it. Nothing happens until then.",
           L"Schedule it", [](SetWindow& ww) { Fu_Run(ww, fu::J_REBOOT, {}); });
}

static void Fu_DoClose(SetWindow& w, bool force) {
    if (!g_pane || g_pane->busy || g_pane->scanning) return;
    std::vector<fu::Lock> rows = Fu_ActRows(*g_pane);
    if (rows.empty()) return;
    bool ask = !force && (Fu_On(w, L"askBeforeClosing") || Fu_Risky(rows));
    if (!ask) {
        Fu_Run(w, fu::J_CLOSE, rows);
        return;
    }
    Fu_Ask(w, L"Close these programs?",
           L"Asks " + Fu_Names(rows) +
               L" to close. They get the chance to ask you to save first. Any that refuse can be ended after that." +
               Fu_Risks(rows),
           L"Close them", [rows](SetWindow& ww) { Fu_Run(ww, fu::J_CLOSE, rows); });
}

static void Fu_DoEnd(SetWindow& w) {
    if (!g_pane || g_pane->busy || g_pane->scanning) return;
    std::vector<fu::Lock> rows = Fu_ActRows(*g_pane);
    if (rows.empty()) return;
    Fu_Ask(w, L"End these programs?",
           Fu_Names(rows) + L" will stop at once. Anything they had not saved is lost." + Fu_Risks(rows), L"End them",
           [rows](SetWindow& ww) { Fu_Run(ww, fu::J_END, rows); });
}

static std::wstring Fu_PickFolder(SetWindow& w) {
    std::wstring out;
    IFileOpenDialog* d = nullptr;
    if (FAILED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&d)))) return out;
    DWORD o = 0;
    d->GetOptions(&o);
    d->SetOptions(o | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM);
    d->SetTitle(L"Pick the folder to put it in");
    if (SUCCEEDED(d->Show(w.hwnd))) {
        IShellItem* it = nullptr;
        if (SUCCEEDED(d->GetResult(&it)) && it) {
            PWSTR p = nullptr;
            if (SUCCEEDED(it->GetDisplayName(SIGDN_FILESYSPATH, &p)) && p) {
                out = p;
                CoTaskMemFree(p);
            }
            it->Release();
        }
    }
    d->Release();
    return out;
}

static std::wstring Fu_PickName(SetWindow& w, const std::wstring& from) {
    std::wstring out;
    IFileSaveDialog* d = nullptr;
    if (FAILED(CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&d)))) return out;
    DWORD o = 0;
    d->GetOptions(&o);
    d->SetOptions(o | FOS_FORCEFILESYSTEM | FOS_OVERWRITEPROMPT | FOS_NOREADONLYRETURN);
    d->SetTitle(L"Rename it");
    d->SetFileName(PathFindFileNameW(from.c_str()));
    std::wstring dir = from;
    PathRemoveFileSpecW(dir.data());
    dir.resize(wcslen(dir.c_str()));
    IShellItem* folder = nullptr;
    if (SUCCEEDED(SHCreateItemFromParsingName(dir.c_str(), nullptr, IID_PPV_ARGS(&folder))) && folder) {
        d->SetFolder(folder);
        folder->Release();
    }
    if (SUCCEEDED(d->Show(w.hwnd))) {
        IShellItem* it = nullptr;
        if (SUCCEEDED(d->GetResult(&it)) && it) {
            PWSTR p = nullptr;
            if (SUCCEEDED(it->GetDisplayName(SIGDN_FILESYSPATH, &p)) && p) {
                out = p;
                CoTaskMemFree(p);
            }
            it->Release();
        }
    }
    d->Release();
    return out;
}

static void Fu_DoPlace(SetWindow& w, int type) {  // copy or move
    if (!g_pane || g_pane->busy || g_pane->scanning || g_pane->targets.empty()) return;
    std::wstring dest = Fu_PickFolder(w);
    if (!g_setWin || g_setWin.get() != &w || !g_pane || dest.empty()) return;
    Fu_Run(w, type, g_pane->rows, dest);
}

static void Fu_DoRename(SetWindow& w) {
    if (!g_pane || g_pane->busy || g_pane->scanning || g_pane->targets.size() != 1) return;
    std::wstring to = Fu_PickName(w, g_pane->targets[0]);
    if (!g_setWin || g_setWin.get() != &w || !g_pane || to.empty()) return;
    if (fu::Norm(to) == fu::Norm(g_pane->targets[0])) return;
    Fu_Run(w, fu::J_RENAME, g_pane->rows, to);
}

static void Fu_CopyDetails(SetWindow& w) {
    if (!g_pane) return;
    std::wstring t;
    for (const auto& r : Fu_ActRows(*g_pane)) {
        t += r.name + L" (number " + std::to_wstring(r.pid) + L")\r\n";
        t += L"  Runs from: " + r.exe + L"\r\n";
        t += L"  Holds: " + (r.path.empty() ? g_pane->targets[0] : r.path) + L"\r\n";
        t += L"  How: " + std::wstring(fu::KindText(r.kind)) + L"\r\n";
    }
    if (t.empty()) {
        Fu_Status(L"Nothing to copy.");
        Set_Invalidate(w);
        return;
    }
    if (OpenClipboard(w.hwnd)) {
        EmptyClipboard();
        HGLOBAL g = GlobalAlloc(GMEM_MOVEABLE, (t.size() + 1) * sizeof(WCHAR));
        if (g) {
            if (void* p = GlobalLock(g)) {
                memcpy(p, t.c_str(), (t.size() + 1) * sizeof(WCHAR));
                GlobalUnlock(g);
                if (!SetClipboardData(CF_UNICODETEXT, g)) GlobalFree(g);
            } else {
                GlobalFree(g);
            }
        }
        CloseClipboard();
        Fu_Status(L"Copied the details.");
    } else {
        Fu_Status(L"Couldn't reach the clipboard.", true);
    }
    Set_Invalidate(w);
}

static void Fu_OpenFolder(SetWindow& w) {
    if (!g_pane) return;
    for (const auto& r : Fu_ActRows(*g_pane)) {
        if (r.exe.empty() || !fu::Exists(r.exe)) continue;
        std::wstring arg = L"/select,\"" + r.exe + L"\"";
        ShellExecuteW(nullptr, L"open", L"explorer.exe", arg.c_str(), nullptr, SW_SHOWNORMAL);
        return;
    }
    Fu_Status(L"That program's folder isn't known.");
    Set_Invalidate(w);
}

static void Fu_Done(SetWindow& w, fu::Result* r) {
    if (!g_pane) {
        delete r;
        return;
    }
    FuPane& pn = *g_pane;
    pn.busy = false;
    if (r->type == fu::J_SCAN) {
        pn.scanning = false;
        pn.scanned = true;
        pn.rows = std::move(r->found.rows);
        pn.sel.clear();
        pn.denied = r->found.denied;
        pn.hidden = r->found.hidden;
        pn.partial = r->found.partial;
        pn.missing = r->found.missing;
        pn.failed = r->found.failed;
        pn.failText = r->found.error;
        pn.scroll = pn.scrollTarget = std::min(pn.scrollTarget, Fu_MaxScroll(w));
    } else {
        Fu_Status(r->text.c_str(), !r->ok);
        if (r->type == fu::J_CLOSE && !r->stillRunning.empty()) {
            std::vector<fu::Lock> left;
            for (const auto& L : pn.rows)
                if (std::find(r->stillRunning.begin(), r->stillRunning.end(), L.pid) != r->stillRunning.end()) left.push_back(L);
            if (!left.empty())
                Fu_Ask(w, L"They didn't close",
                       Fu_Names(left) + L" didn't close on request. End " + (left.size() == 1 ? L"it" : L"them") +
                           L" now? Anything not saved is lost.",
                       L"End them", [left](SetWindow& ww) { Fu_Run(ww, fu::J_END, left); });
        }
    }
    bool again = r->type != fu::J_SCAN && r->rescan;
    delete r;
    if (again) Fu_Scan(w);
    Set_Invalidate(w);
}

// ---- Painting -------------------------------------------------------------------------------------------------------

static float Fu_Glow(int id) {
    if (!g_pane) return 0;
    auto it = g_pane->glow.find(id);
    return it == g_pane->glow.end() ? 0 : it->second;
}

static void Fu_DrawPill(SetPaint& p, SetWindow& w, const D2D1_RECT_F& r, int i, bool label, bool off) {
    float g = off ? 0 : Fu_Glow(1 + i), rad = (r.bottom - r.top) / 2;
    p.Round(r, rad, mocha::surface0, w.glass ? 0.7f : 1);
    p.Edge(r, rad, mocha::surface1, 0.8f * (1 - g), 1);
    p.GradRing(r, rad, g, 1.5f);
    UINT32 c = off ? mocha::overlay0 : mocha::text;
    if (label) {
        p.Glyph(w.fIconS.get(), kFuPillGlyph[i], {r.left + 12, r.top, r.left + 28, r.bottom}, c);
        p.Text(w.fSmall.get(), kFuPillText[i], {r.left + 36, r.top, r.right - 10, r.bottom}, c);
    } else {
        p.Glyph(w.fIconS.get(), kFuPillGlyph[i], r, c);
    }
}

static UINT32 Fu_KindColour(int k) {
    switch (k) {
        case fu::kDll: return mocha::mauve;
        case fu::kExe: return mocha::peach;
        case fu::kMapped: return mocha::teal;
        default: return mocha::blue;
    }
}

static void Fu_DrawRow(SetPaint& p, SetWindow& w, FuPane& pn, const D2D1_RECT_F& L, int i, float y) {
    const fu::Lock& k = pn.rows[i];
    D2D1_RECT_F row{L.left, y + 2, L.right - 12, y + kFuRowH - 2};
    float g = Fu_Glow(100 + i);
    bool sel = pn.sel.count(i) != 0;
    if (sel) {
        p.Round(row, 10, mocha::surface1, 0.55f);
        p.GradRing(row, 10, 0.9f, 1.2f);
    } else if (g > 0) {
        p.Round(row, 10, mocha::surface0, 0.55f * g);
        p.GradRing(row, 10, 0.6f * g, 1);
    }
    float x0 = row.left + 52, right = row.right - 12;
    if (ID2D1Bitmap* bmp = Fu_Icon(pn, p.rt, k.exe)) {
        D2D1_RECT_F ir{row.left + 14, y + 14, row.left + 42, y + 42};
        p.rt->DrawBitmap(bmp, ir, p.fade, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    }
    // The chip with how it is held.
    PCWSTR kind = fu::KindText(k.kind);
    if (!pn.fChip) pn.fChip = Set_Fmt(w.family, 11, 500, false, DWRITE_TEXT_ALIGNMENT_CENTER, true);
    float cw = (pn.fChip ? Set_TextW(pn.fChip.get(), kind) : 70) + 18;
    D2D1_RECT_F chip{right - cw, y + 11, right, y + 29};
    UINT32 kc = Fu_KindColour(k.kind);
    p.Edge(chip, 9, kc, 0.85f, 1);
    p.Text(pn.fChip.get(), kind, chip, kc);
    float nameW = std::min(Set_TextW(w.fValue.get(), k.name), (chip.left - x0) * 0.55f);
    p.Text(w.fValue.get(), k.name, {x0, y + 8, x0 + nameW + 4, y + 30}, mocha::text);
    p.Text(w.fSmall.get(), L"number " + std::to_wstring(k.pid), {x0 + nameW + 12, y + 9, chip.left - 8, y + 29},
           mocha::overlay1);
    std::wstring held = k.path.empty() ? (pn.targets.empty() ? L"" : pn.targets[0]) : k.path;
    p.Text(w.fSmall.get(), L"Holds  " + held, {x0, y + 29, right, y + 46}, mocha::subtext1);
    std::wstring run = k.safety == 2 ? L"Windows needs this one, so it is never closed."
                       : k.safety == 1 ? L"Windows Explorer: closing it restarts your desktop."
                                       : L"Runs from  " + (k.exe.empty() ? std::wstring(L"(unknown)") : k.exe);
    p.Text(w.fSmall.get(), run, {x0, y + 45, right, y + 62}, k.safety ? mocha::peach : mocha::overlay1);
}

static void Fu_DrawAsk(SetPaint& p, SetWindow& w, FuPane& pn) {
    D2D1_RECT_F P = Fu_Pane(w);
    float a = pn.askShow;
    p.Round(P, 14, mocha::crust, 0.62f * a);
    D2D1_RECT_F c = Fu_Card(w);
    float lift = (1 - a) * 8;
    c.top += lift;
    c.bottom += lift;
    float keep = p.fade;
    p.fade = keep * a;
    p.Round({c.left, c.top + 3, c.right, c.bottom + 5}, 16, mocha::crust, 0.5f);
    p.Round(c, 14, mocha::base, 1);
    p.Edge(c, 14, mocha::surface1, 0.9f, 1);
    p.Text(w.fBig.get(), pn.askTitle, {c.left + 20, c.top + 16, c.right - 20, c.top + 46}, mocha::text);
    if (!pn.fWrap) pn.fWrap = Set_Fmt(w.family, 13, 400, true);
    p.Text(pn.fWrap.get(), pn.askBody, {c.left + 20, c.top + 52, c.right - 20, c.bottom - 62}, mocha::subtext1);
    D2D1_RECT_F no = Fu_AskBtn(w, false), yes = Fu_AskBtn(w, true);
    no.top += lift, no.bottom += lift, yes.top += lift, yes.bottom += lift;
    float gn = Fu_Glow(21), gy = Fu_Glow(20);
    p.Round(no, 12, mocha::surface0, 1);
    p.Edge(no, 12, mocha::surface1, 0.9f * (1 - gn), 1);
    p.GradRing(no, 12, gn, 1.5f);
    p.Text(w.fButton.get(), L"Cancel", no, mocha::text);
    p.GradFill(yes, 12, 0.86f + 0.14f * gy);
    p.Text(w.fButton.get(), pn.askYes, yes, mocha::crust);
    p.fade = keep;
}

static void Fu_DrawPane(SetPaint& p, SetWindow& w) {
    if (!g_pane || w.render) return;
    FuPane& pn = *g_pane;
    pn.iconBudget = 6;
    if (!pn.fCenter) pn.fCenter = Set_Fmt(w.family, 13, 500, true, DWRITE_TEXT_ALIGNMENT_CENTER);
    D2D1_RECT_F P = Fu_Pane(w);
    Set_DrawDock(p, w, P, 14, w.glass ? 0.58f : 1, pn.paneGlow * 0.85f);
    float l = P.left + 20, r = P.right - 20, t = P.top;
    p.Text(w.fBig.get(), L"Locks", {l, t + 16, r, t + 44}, mocha::text);
    std::wstring sub = Fu_TargetName(pn);
    if (pn.scanned && !pn.missing && !pn.failed) {
        std::set<DWORD> pids;
        for (const auto& k : pn.rows) pids.insert(k.pid);
        sub += L"  ·  " + (pn.rows.empty() ? std::wstring(L"nothing holding it") : Fu_Count((int)pids.size(), L"program", L"programs"));
    }
    p.Text(w.fSmall.get(), sub, {l, t + 46, r, t + 64}, mocha::subtext0);

    FuPills b = Fu_Pills(w);
    for (int i = 0; i < 4; i++) Fu_DrawPill(p, w, b.r[i], i, b.label[i], !Fu_Clickable(1 + i));

    D2D1_RECT_F L = Fu_ListRect(w);
    p.Text(w.fSection.get(), L"PROGRAM", {L.left + 52, t + 124, L.right - 16, t + 140}, mocha::subtext0);
    p.rt->DrawLine({L.left + 10, L.top - 2}, {L.right - 10, L.top - 2}, p.B(mocha::surface1, 0.6f), 1);

    float cy = (L.top + L.bottom) / 2;
    auto empty = [&](WCHAR glyph, const std::wstring& text, UINT32 c = mocha::subtext0) {
        p.Glyph(w.fIconL.get(), glyph, {L.left, cy - 64, L.right, cy - 16}, mocha::overlay1);
        p.Text(pn.fCenter.get(), text, {L.left + 30, cy - 4, L.right - 30, cy + 70}, c);
    };
    if (pn.targets.empty()) {
        std::wstring hk = Trim(Fu_Get(w, L"unlockHotkey"));
        empty(0xE785, hk.empty() ? L"Right-click a file or folder in Explorer and pick What's locking this?"
                                 : L"Right-click a file or folder in Explorer and pick What's locking this?, or select it and press " + hk + L".");
    } else if (pn.scanning) {
        int total = fu::g_prog.total, done = fu::g_prog.done;
        empty(0xE721, total ? L"Looking... checked " + std::to_wstring(std::min(done, total)) + L" of " +
                                  Fu_Count(total, L"program", L"programs") + L" with files open."
                            : L"Looking...");
    } else if (pn.missing) {
        empty(0xE783, L"That item isn't there any more.");
    } else if (pn.failed) {
        empty(0xE783, pn.failText.empty() ? L"The check couldn't run." : pn.failText, mocha::red);
    } else if (pn.rows.empty()) {
        empty(0xE73E, L"Nothing is holding this. You can delete, move or rename it now.");
    } else {
        p.rt->PushAxisAlignedClip(L, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
        int n = (int)pn.rows.size();
        int first = std::max(0, (int)(pn.scroll / kFuRowH));
        int last = std::min(n - 1, (int)((pn.scroll + (L.bottom - L.top)) / kFuRowH) + 1);
        for (int i = first; i <= last; i++) Fu_DrawRow(p, w, pn, L, i, L.top + i * kFuRowH - pn.scroll);
        p.rt->PopAxisAlignedClip();
        D2D1_RECT_F th = Fu_Thumb(w);
        if (th.bottom > th.top) Set_ThumbFill(p, th, 0.45f + 0.55f * std::max(Fu_Glow(6), pn.dragThumb ? 1.0f : 0.0f));
    }

    std::wstring line = pn.status;
    bool err = pn.statusError;
    if (line.empty() && (pn.busy)) line = L"Working...";
    if (line.empty() && pn.scanned && !pn.failed && !pn.missing) {
        if (pn.denied) line = L"Couldn't check " + Fu_Count(pn.denied, L"program", L"programs") +
                              (fu::g_elevated ? L"." : L". The tool runs without full rights, so it can't see them.");
        else if (pn.partial) line = L"The list may be missing a few: the check took too long.";
        else if (pn.hidden) line = Fu_Count(pn.hidden, L"Windows program", L"Windows programs") + L" left out of the list.";
        else if (!pn.rows.empty()) line = L"Click a row to pick it. Right-click for more.";
    }
    p.Text(w.fStatusLine.get(), line, {l, P.bottom - 44, r, P.bottom - 18}, err ? mocha::red : mocha::overlay1);
    if (pn.asking) Fu_DrawAsk(p, w, pn);
}

// ---- Input ----------------------------------------------------------------------------------------------------------

static bool Fu_Tick(SetWindow& w) {
    if (!g_pane) return false;
    FuPane& pn = *g_pane;
    bool anim = Set_Anim(w), moving = pn.scanning || pn.busy;
    if (pn.hover > 0 && !pn.glow.count(pn.hover)) pn.glow[pn.hover] = 0;
    for (auto it = pn.glow.begin(); it != pn.glow.end();) {
        float target = it->first == pn.hover && Fu_Clickable(it->first) ? 1.0f : 0.0f;
        float d = target - it->second;
        if (!anim || fabsf(d) < 0.02f) it->second = target;
        else it->second += d * 0.3f, moving = true;
        if (it->second == 0 && target == 0) it = pn.glow.erase(it);
        else ++it;
    }
    float d = pn.scrollTarget - pn.scroll;
    if (!anim || fabsf(d) < 0.5f) pn.scroll = pn.scrollTarget;
    else pn.scroll += d * 0.25f, moving = true;
    float want = pn.asking ? 1.0f : 0.0f, da = want - pn.askShow;
    if (!anim || fabsf(da) < 0.02f) pn.askShow = want;
    else pn.askShow += da * 0.3f, moving = true;
    float dg = (pn.inPane ? 1.0f : 0.0f) - pn.paneGlow;
    if (!anim || fabsf(dg) < 0.02f) pn.paneGlow = pn.inPane ? 1.0f : 0.0f;
    else pn.paneGlow += dg * 0.25f, moving = true;
    return moving;
}

static void Fu_SetHover(SetWindow& w, int id) {
    if (!g_pane || g_pane->hover == id) return;
    g_pane->hover = id;
    Fu_Kick(w);
    Set_Invalidate(w);
}

static void Fu_ThumbTo(SetWindow& w, float y) {
    D2D1_RECT_F L = Fu_ListRect(w), th = Fu_Thumb(w);
    float thh = th.bottom - th.top + 4, range = (L.bottom - L.top) - thh;
    float f = range > 0 ? std::clamp((y - g_pane->dragOff - L.top) / range, 0.0f, 1.0f) : 0;
    g_pane->scroll = g_pane->scrollTarget = f * Fu_MaxScroll(w);
    Set_Invalidate(w);
}

static void Fu_MoreMenu(SetWindow& w, POINT screen) {
    FuPane& pn = *g_pane;
    bool one = pn.targets.size() == 1, rows = !pn.rows.empty();
    std::vector<SetMenuItem> m;
    m.push_back(Set_MenuRow(11, L"\xF044", L"Unlock and rename", false, !one));
    m.push_back(Set_MenuRow(12, L"\xF0C5", L"Unlock and copy"));
    m.push_back(Set_MenuRow(13, L"\xF07B", L"Unlock and move"));
    m.push_back(Set_MenuRow(14, L"\xF017", L"Delete at the next restart"));
    m.push_back(Set_MenuSep());
    m.push_back(Set_MenuRow(15, L"\xF00D", L"Close the locking programs", false, !rows));
    m.push_back(Set_MenuRow(16, L"\xF05E", L"End the locking programs", false, !rows));
    m.push_back(Set_MenuSep());
    m.push_back(Set_MenuRow(17, L"\xF07C", L"Open the program's folder", false, !rows));
    m.push_back(Set_MenuRow(18, L"\xF0C5", L"Copy the details", false, !rows));
    int cmd = Set_TrayMenu(w.hwnd, m, &screen);
    if (!g_pane || g_pane != &pn) return;
    switch (cmd) {
        case 11: Fu_DoRename(w); break;
        case 12: Fu_DoPlace(w, fu::J_COPY); break;
        case 13: Fu_DoPlace(w, fu::J_MOVE); break;
        case 14: Fu_DoReboot(w, false); break;
        case 15: Fu_DoClose(w, false); break;
        case 16: Fu_DoEnd(w); break;
        case 17: Fu_OpenFolder(w); break;
        case 18: Fu_CopyDetails(w); break;
    }
}

static void Fu_RowMenu(SetWindow& w, int id, POINT screen) {
    FuPane& pn = *g_pane;
    size_t i = (size_t)(id - 100);
    if (i >= pn.rows.size()) return;
    if (!pn.sel.count(i)) {
        pn.sel.clear();
        pn.sel.insert(i);
        Set_Invalidate(w);
    }
    std::vector<SetMenuItem> m;
    m.push_back(Set_MenuRow(1, L"\xF09C", L"Unlock this"));
    m.push_back(Set_MenuRow(2, L"\xF00D", L"Close this program"));
    m.push_back(Set_MenuRow(3, L"\xF07C", L"Open the program's folder"));
    m.push_back(Set_MenuRow(4, L"\xF0C5", L"Copy the details"));
    int cmd = Set_TrayMenu(w.hwnd, m, &screen);
    if (!g_pane || g_pane != &pn) return;
    switch (cmd) {
        case 1: Fu_DoUnlock(w, false); break;
        case 2: Fu_DoClose(w, false); break;
        case 3: Fu_OpenFolder(w); break;
        case 4: Fu_CopyDetails(w); break;
    }
}

static void Fu_Click(SetWindow& w, int id, float x, float y) {
    FuPane& pn = *g_pane;
    if (id == 6) {
        D2D1_RECT_F th = Fu_Thumb(w);
        pn.dragThumb = true;
        pn.dragOff = Set_In({th.left - 10, th.top, th.right + 10, th.bottom}, th.left, y) ? y - th.top + 2
                                                                                           : (th.bottom - th.top) / 2;
        SetCapture(w.hwnd);
        Fu_ThumbTo(w, y);
        return;
    }
    if (!Fu_Clickable(id)) return;
    if (id == 20 || id == 21) {
        Fu_AnswerAsk(w, id == 20);
        return;
    }
    if (id >= 100) {
        size_t i = (size_t)(id - 100);
        if (i >= pn.rows.size()) return;
        if (GetKeyState(VK_CONTROL) < 0) {
            if (!pn.sel.erase(i)) pn.sel.insert(i);
        } else if (pn.sel.size() == 1 && pn.sel.count(i)) {
            pn.sel.clear();
        } else {
            pn.sel.clear();
            pn.sel.insert(i);
        }
        Set_Invalidate(w);
        return;
    }
    switch (id) {
        case 1: Fu_Scan(w); break;
        case 2: Fu_DoUnlock(w, false); break;
        case 3: Fu_DoDelete(w, false); break;
        case 4: {
            D2D1_RECT_F r = Fu_Pills(w).r[3];
            POINT pt{(LONG)(r.left * w.dpi / 96.0f), (LONG)((r.bottom + kSetCapH + 4) * w.dpi / 96.0f)};
            ClientToScreen(w.hwnd, &pt);
            Fu_MoreMenu(w, pt);
            break;
        }
    }
    (void)x;
}

// Test hook, for the test PC: posted by a program at the same rights as this one.
static void Fu_Command(SetWindow& w, WPARAM what, LPARAM arg) {
    if (!g_pane) return;
    switch (what) {
        case 1: Fu_Scan(w); break;
        case 2: Fu_DoUnlock(w, true); break;
        case 3: Fu_DoDelete(w, true); break;
        case 4:
            g_pane->sel.clear();
            if (arg >= 0 && (size_t)arg < g_pane->rows.size()) g_pane->sel.insert((size_t)arg);
            Set_Invalidate(w);
            break;
        case 5: Fu_DoClose(w, true); break;
        case 6: Fu_DoReboot(w, true); break;
        case 7: Fu_AnswerAsk(w, arg != 0); break;
    }
}

static void Fu_WriteState(SetWindow&) {
    if (!g_pane) return;
    WCHAR tmp[MAX_PATH];
    GetTempPathW(MAX_PATH, tmp);
    std::wstring path = std::wstring(tmp) + L"seamless-file-unlocker-state.txt";
    std::wstring t = std::wstring(L"state=") + (g_pane->scanning ? L"scanning" : g_pane->busy ? L"busy" : L"idle") +
                     L"\nrows=" + std::to_wstring(g_pane->rows.size()) + L"\ndenied=" + std::to_wstring(g_pane->denied) +
                     L"\nelevated=" + (fu::g_elevated ? L"1" : L"0") + L"\nasking=" + (g_pane->asking ? L"1" : L"0") +
                     L"\nstatus=" + g_pane->status + L"\n";
    {
        std::wstring d = fu::DbgGet();
        for (size_t p = 0; p < d.size();) {
            size_t q = d.find(L'\n', p);
            if (q == std::wstring::npos) q = d.size();
            if (q > p) t += L"dbg=" + d.substr(p, q - p) + L"\n";
            p = q + 1;
        }
    }
    for (const auto& k : g_pane->rows)
        t += std::to_wstring(k.pid) + L"|" + std::to_wstring(k.kind) + L"|" + k.name + L"|" + k.path + L"\n";
    HANDLE h = CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return;
    int n = WideCharToMultiByte(CP_UTF8, 0, t.c_str(), (int)t.size(), nullptr, 0, nullptr, nullptr);
    std::string u(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, t.c_str(), (int)t.size(), u.data(), n, nullptr, nullptr);
    DWORD wr = 0;
    WriteFile(h, u.data(), (DWORD)u.size(), &wr, nullptr);
    CloseHandle(h);
}

static LRESULT CALLBACK Fu_Subclass(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w || !g_pane) {
        if (msg == WM_NCDESTROY) RemoveWindowSubclass(hwnd, Fu_Subclass, kFuSubclass);
        if (msg == WM_APP_FU_DONE) delete (fu::Result*)lp;
        return DefSubclassProc(hwnd, msg, wp, lp);
    }
    FuPane& pn = *g_pane;
    auto dipX = [&](int x) { return x * 96.0f / w->dpi; };
    auto dipY = [&](int y) { return y * 96.0f / w->dpi - kSetCapH; };
    switch (msg) {
        case WM_APP_FU_TAKE: {
            std::vector<std::pair<std::vector<std::wstring>, bool>> batch;
            {
                std::lock_guard<std::mutex> lock(g_fuQueueLock);
                batch.swap(g_fuQueue);
            }
            if (batch.empty()) return 0;
            Fu_SetTargets(*w, std::move(batch.back().first));  // The newest pick wins.
            return 0;
        }
        case WM_APP_FU_DONE:
            Fu_Done(*w, (fu::Result*)lp);
            return 0;
        case WM_APP_FU_CMD:
            Fu_Command(*w, wp, lp);
            return 0;
        case WM_APP_FU_STATE:
            Fu_WriteState(*w);
            return 0;
        case WM_TIMER:
            if (wp == kFuTimer) {
                if (!Fu_Tick(*w)) {
                    KillTimer(hwnd, kFuTimer);
                    pn.timer = false;
                }
                Set_Invalidate(*w);
                return 0;
            }
            break;
        case WM_DROPFILES: {
            HDROP drop = (HDROP)wp;
            UINT n = DragQueryFileW(drop, 0xFFFFFFFF, nullptr, 0);
            std::vector<std::wstring> paths;
            for (UINT i = 0; i < n; i++) {
                UINT len = DragQueryFileW(drop, i, nullptr, 0);
                std::wstring p(len + 1, L'\0');
                DragQueryFileW(drop, i, p.data(), len + 1);
                p.resize(len);
                paths.push_back(p);
            }
            DragFinish(drop);
            Fu_SetTargets(*w, std::move(paths));
            return 0;
        }
        case WM_MOUSEMOVE: {
            float x = dipX(GET_X_LPARAM(lp)), y = dipY(GET_Y_LPARAM(lp));
            bool inPane = Set_In(Fu_Pane(*w), x, y);
            if (inPane != pn.inPane) {
                pn.inPane = inPane;
                Fu_Kick(*w);
            }
            if (pn.dragThumb) {
                Fu_ThumbTo(*w, y);
                return 0;
            }
            if (w->openSel < 0) Fu_SetHover(*w, Fu_HitAt(*w, x, y));
            if (!pn.tracking) {
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                pn.tracking = TrackMouseEvent(&t) != FALSE;
            }
            break;
        }
        case WM_MOUSELEAVE:
            pn.tracking = false;
            pn.inPane = false;
            Fu_Kick(*w);
            Fu_SetHover(*w, -1);
            break;
        case WM_LBUTTONDOWN: {
            if (w->openSel >= 0 || pn.dragThumb) break;
            float x = dipX(GET_X_LPARAM(lp)), y = dipY(GET_Y_LPARAM(lp));
            int id = Fu_HitAt(*w, x, y);
            if (id < 0) break;
            Set_CommitEdit(*w, true);
            SetFocus(hwnd);
            Fu_Click(*w, id, x, y);
            return 0;
        }
        case WM_LBUTTONDBLCLK: {
            float x = dipX(GET_X_LPARAM(lp)), y = dipY(GET_Y_LPARAM(lp));
            if (w->openSel < 0 && Fu_HitAt(*w, x, y) >= 0) return 0;
            break;
        }
        case WM_LBUTTONUP:
            if (pn.dragThumb) {
                pn.dragThumb = false;
                if (GetCapture() == hwnd) ReleaseCapture();
                Set_Invalidate(*w);
                return 0;
            }
            break;
        case WM_CAPTURECHANGED:
            if (pn.dragThumb && (HWND)lp != hwnd) {
                pn.dragThumb = false;
                Set_Invalidate(*w);
            }
            break;
        case WM_RBUTTONUP: {
            if (w->openSel >= 0) break;
            float x = dipX(GET_X_LPARAM(lp)), y = dipY(GET_Y_LPARAM(lp));
            int id = Fu_HitAt(*w, x, y);
            if (id < 0) break;
            if (id >= 100 && !pn.busy && !pn.asking) {
                POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
                ClientToScreen(hwnd, &pt);
                Fu_RowMenu(*w, id, pt);
            }
            return 0;
        }
        case WM_MOUSEWHEEL: {
            if (w->openSel >= 0) break;
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            ScreenToClient(hwnd, &pt);
            if (!Set_In(Fu_ListRect(*w), dipX(pt.x), dipY(pt.y))) {
                if (Fu_HitAt(*w, dipX(pt.x), dipY(pt.y)) >= 0) return 0;
                break;
            }
            float delta = (float)GET_WHEEL_DELTA_WPARAM(wp) / WHEEL_DELTA;
            pn.scrollTarget = std::clamp(pn.scrollTarget - delta * kFuRowH * 1.5f, 0.0f, Fu_MaxScroll(*w));
            if (!Set_Anim(*w)) pn.scroll = pn.scrollTarget;
            Fu_Kick(*w);
            Set_Invalidate(*w);
            return 0;
        }
        case WM_SETCURSOR:
            if (LOWORD(lp) == HTCLIENT && pn.hover >= 0 && w->openSel < 0) {
                SetCursor(LoadCursorW(nullptr, Fu_Clickable(pn.hover) ? IDC_HAND : IDC_ARROW));
                return TRUE;
            }
            break;
        case WM_KEYDOWN:
            if (pn.asking && GetFocus() == hwnd) {
                if (wp == VK_ESCAPE) {
                    Fu_AnswerAsk(*w, false);
                    return 0;
                }
                if (wp == VK_RETURN) {
                    Fu_AnswerAsk(*w, true);
                    return 0;
                }
            } else if (GetFocus() == hwnd && w->recording < 0) {
                if (wp == VK_F5) {
                    Fu_Scan(*w);
                    return 0;
                }
                if (wp == 'A' && GetKeyState(VK_CONTROL) < 0) {
                    pn.sel.clear();
                    for (size_t i = 0; i < pn.rows.size(); i++) pn.sel.insert(i);
                    Set_Invalidate(*w);
                    return 0;
                }
            }
            break;
        case WM_NCDESTROY: {
            g_fuCancel = true;
            if (pn.timer) KillTimer(hwnd, kFuTimer);
            RemoveWindowSubclass(hwnd, Fu_Subclass, kFuSubclass);
            delete g_pane;
            g_pane = nullptr;
            break;
        }
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

// Called on the window's own thread once it is open.
static void Fu_Attach() {
    SetWindow* w = g_setWin.get();
    if (!w || !w->hwnd || w->render) return;
    delete g_pane;
    g_pane = new FuPane;
    DragAcceptFiles(w->hwnd, TRUE);
    // Explorer may run with fewer rights than this window: let its drops and paths through.
    ChangeWindowMessageFilterEx(w->hwnd, WM_DROPFILES, MSGFLT_ALLOW, nullptr);
    ChangeWindowMessageFilterEx(w->hwnd, WM_COPYDATA, MSGFLT_ALLOW, nullptr);
    ChangeWindowMessageFilterEx(w->hwnd, 0x0049 /* WM_COPYGLOBALDATA */, MSGFLT_ALLOW, nullptr);
    SetWindowSubclass(w->hwnd, Fu_Subclass, kFuSubclass, 0);
    PostMessageW(w->hwnd, WM_APP_FU_TAKE, 0, 0);
}

// From the tray thread: paths Explorer sent. The window takes them when it gets WM_APP_FU_TAKE.
void Fu_QueuePaths(std::vector<std::wstring> paths, bool folder) {
    std::lock_guard<std::mutex> lock(g_fuQueueLock);
    g_fuQueue.push_back({std::move(paths), folder});
}

// At unload: a job still running finishes (or is told to stop) before the code it runs goes away.
void Fu_WaitWorkers() {
    g_fuCancel = true;
    if (!g_fuWorker) return;
    WaitForSingleObject(g_fuWorker, 60000);
    CloseHandle(g_fuWorker);
    g_fuWorker = nullptr;
}

// The tray icon's right-click menu. Returns 1 to open, 3 for settings, 0 for nothing.
int ShowTrayMenu(HWND owner, POINT pt) {
    std::vector<SetMenuItem> rows;
    rows.push_back(Set_MenuRow(1, L"\uE785", L"Open File Unlocker"));
    rows.push_back(Set_MenuSep());
    rows.push_back(Set_MenuRow(3, L"\uEB51", L"Settings"));
    return Set_TrayMenu(owner, rows, &pt);
}
}  // namespace fuset

// ---- Tray icon (tool process only) -------------------------------------------------------------------------------
// Click opens the window; right-click shows Open and Settings. Explorer sends the selected paths here.

constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
static constexpr UINT WM_APP_TRAY = WM_APP + 20, WM_APP_TRAY_REFRESH = WM_APP + 21;
static HANDLE g_trayThread;
static std::atomic<HWND> g_trayWnd;
static UINT g_taskbarCreated;
static bool g_trayShown;
static HICON g_trayIcon;

static HICON Crisp_ShrinkIcon(HICON big, int factor) {
    if (!big || factor <= 1) return big;
    ICONINFO ii{};
    if (!GetIconInfo(big, &ii)) return big;
    HICON out = nullptr;
    BITMAP bm{};
    if (ii.hbmColor && GetObjectW(ii.hbmColor, sizeof(bm), &bm) && bm.bmWidth == bm.bmHeight &&
        bm.bmWidth >= factor && bm.bmWidth % factor == 0) {
        const int src = bm.bmWidth, n = src / factor;
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = src;
        bi.bmiHeader.biHeight = -src;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        unsigned int* in = new unsigned int[(size_t)src * src];
        HDC screen = GetDC(nullptr);
        if (GetDIBits(screen, ii.hbmColor, 0, src, in, &bi, DIB_RGB_COLORS) == src) {
            bool premul = true, anyAlpha = false;
            for (size_t i = 0; i < (size_t)src * src; i++) {
                unsigned int p = in[i], a = p >> 24;
                if (a) anyAlpha = true;
                if (((p >> 16) & 0xFF) > a || ((p >> 8) & 0xFF) > a || (p & 0xFF) > a) premul = false;
            }
            void* bits = nullptr;
            bi.bmiHeader.biWidth = n;
            bi.bmiHeader.biHeight = -n;
            HBITMAP color = anyAlpha ? CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0) : nullptr;
            if (color && bits) {
                unsigned int* px = (unsigned int*)bits;
                const unsigned int cnt = (unsigned int)(factor * factor);
                for (int y = 0; y < n; y++)
                    for (int x = 0; x < n; x++) {
                        unsigned int sa = 0, sr = 0, sg = 0, sb = 0;
                        for (int dy = 0; dy < factor; dy++)
                            for (int dx = 0; dx < factor; dx++) {
                                unsigned int p = in[(size_t)(y * factor + dy) * src + x * factor + dx], a = p >> 24;
                                unsigned int r = (p >> 16) & 0xFF, g = (p >> 8) & 0xFF, b = p & 0xFF;
                                if (!premul) {
                                    r = (r * a + 127) / 255;
                                    g = (g * a + 127) / 255;
                                    b = (b * a + 127) / 255;
                                }
                                sa += a; sr += r; sg += g; sb += b;
                            }
                        unsigned int a = (sa + cnt / 2) / cnt, r = 0, g = 0, b = 0;
                        if (a && sa) {
                            r = (sr * 255 + sa / 2) / sa; if (r > 255) r = 255;
                            g = (sg * 255 + sa / 2) / sa; if (g > 255) g = 255;
                            b = (sb * 255 + sa / 2) / sa; if (b > 255) b = 255;
                        }
                        px[(size_t)y * n + x] = a ? ((a << 24) | (r << 16) | (g << 8) | b) : 0;
                    }
                // A zero mask: with 32-bit colour Windows draws from the alpha channel.
                unsigned char* maskBits = new unsigned char[(size_t)((n + 15) / 16) * 2 * n]();
                HBITMAP mask = CreateBitmap(n, n, 1, 1, maskBits);
                delete[] maskBits;
                if (mask) {
                    ICONINFO o{TRUE, 0, 0, mask, color};
                    out = CreateIconIndirect(&o);
                    DeleteObject(mask);
                }
            }
            if (color) DeleteObject(color);
        }
        ReleaseDC(nullptr, screen);
        delete[] in;
    }
    if (ii.hbmColor) DeleteObject(ii.hbmColor);
    if (ii.hbmMask) DeleteObject(ii.hbmMask);
    if (!out) return big;
    DestroyIcon(big);
    return out;
}

static HICON MakeTrayIcon_Big() {
    int size = GetSystemMetricsForDpi(SM_CXICON, GetDpiForSystem()) * 4;
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
    HFONT font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xE785, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) rgb[i] = (c0[i] + (c1[i] - c0[i]) * t) * cov;
            px[y * size + x] = ((uint32_t)(cov * 255 + 0.5f) << 24) | ((uint32_t)(rgb[0] * 255 + 0.5f) << 16) |
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

// Drawn at 4x and shrunk, so the icon is smooth at the size it is shown.
static HICON MakeTrayIcon() { return Crisp_ShrinkIcon(MakeTrayIcon_Big(), 4); }

static void UpdateTray(HWND hwnd, bool recreate) {
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = kTrayId;
    if (!Wh_GetIntSetting(L"settingsTrayIcon")) {
        if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayShown = false;
        return;
    }
    HICON icon = g_trayIcon && !recreate ? g_trayIcon : MakeTrayIcon();
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_APP_TRAY;
    nid.hIcon = icon;
    wcscpy_s(nid.szTip, L"Seamless File Unlocker");
    if (recreate) g_trayShown = false;
    if (!g_trayShown) {
        Shell_NotifyIconW(NIM_DELETE, &nid);
        if (Shell_NotifyIconW(NIM_ADD, &nid)) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
            g_trayShown = true;
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    if (g_trayIcon && g_trayIcon != icon) DestroyIcon(g_trayIcon);
    g_trayIcon = icon;
}

// Paths from Explorer: 'S' (the selection) or 'F' (a folder to open up), then the paths, each ending in a NUL.
static void TakePaths(const COPYDATASTRUCT* cd) {
    if (!cd || cd->dwData != kFuCopyPaths || cd->cbData < 2 * sizeof(WCHAR) || cd->cbData % sizeof(WCHAR)) return;
    const WCHAR* p = (const WCHAR*)cd->lpData;
    size_t n = cd->cbData / sizeof(WCHAR);
    bool folder = p[0] == L'F';
    std::vector<std::wstring> paths;
    std::wstring cur;
    for (size_t i = 1; i < n; i++) {
        if (p[i]) {
            cur += p[i];
            continue;
        }
        if (!cur.empty()) paths.push_back(cur);
        cur.clear();
    }
    if (!cur.empty()) paths.push_back(cur);
    if (paths.empty()) return;
    fuset::Fu_QueuePaths(std::move(paths), folder);
    fuset::OpenSettingsWindow();
    if (HWND w = fuset::g_settingsWnd) PostMessageW(w, WM_APP + 60, 0, 0);
}

static LRESULT CALLBACK TrayProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        UpdateTray(hwnd, true);
        return 0;
    }
    switch (msg) {
        case WM_COPYDATA:
            TakePaths((const COPYDATASTRUCT*)lp);
            return TRUE;
        case WM_APP_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    fuset::OpenSettingsWindow();
                    break;
                case WM_CONTEXTMENU: {
                    POINT pt{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)};
                    SetForegroundWindow(hwnd);
                    int cmd = fuset::ShowTrayMenu(hwnd, pt);
                    if (cmd == 1 || cmd == 3) fuset::OpenSettingsWindow();
                    break;
                }
            }
            return 0;
        case WM_APP_TRAY_REFRESH:
            UpdateTray(hwnd, false);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY: {
            NOTIFYICONDATAW nid{};
            nid.cbSize = sizeof(nid);
            nid.hWnd = hwnd;
            nid.uID = kTrayId;
            if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
            g_trayShown = false;
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI TrayThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HRESULT co = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    HINSTANCE inst = (HINSTANCE)&__ImageBase;
    WNDCLASSW wc{};
    wc.lpfnWndProc = TrayProc;
    wc.hInstance = inst;
    wc.lpszClassName = kFuTrayClass;
    RegisterClassW(&wc);
    // A hidden top-level window, not a message-only one: only top-level windows hear TaskbarCreated, and Explorer
    // finds it by class to send the selection.
    HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless File Unlocker", WS_POPUP, 0, 0, 0, 0,
                                nullptr, nullptr, inst, nullptr);
    if (!hwnd) {
        UnregisterClassW(wc.lpszClassName, inst);
        if (SUCCEEDED(co)) CoUninitialize();
        return 0;
    }
    g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(hwnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
    ChangeWindowMessageFilterEx(hwnd, WM_COPYDATA, MSGFLT_ALLOW, nullptr);  // Explorer runs with fewer rights.
    g_trayWnd = hwnd;
    UpdateTray(hwnd, true);
    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    g_trayWnd = nullptr;
    if (IsWindow(hwnd)) DestroyWindow(hwnd);
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    UnregisterClassW(wc.lpszClassName, inst);
    if (SUCCEEDED(co)) CoUninitialize();
    return 0;
}

static void StopTrayThread() {
    if (!g_trayThread) return;
    if (HWND hwnd = g_trayWnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
    if (WaitForSingleObject(g_trayThread, 5000) == WAIT_TIMEOUT) Wh_Log(L"The tray thread did not stop");
    CloseHandle(g_trayThread);
    g_trayThread = nullptr;
}


// ---- Start and stop -------------------------------------------------------------------------------------------------
// The tool process owns the tray icon and the unlocker window. Inside Explorer the mod only adds the right-click entry
// and the shortcut, and sends the selected paths across.

#include <windhawk_tool_mod.h>

static bool g_inExplorer;

static void Fu_ReadToolSettings() { g_fuAnim = Wh_GetIntSetting(L"settingsAnimation") != 0; }

BOOL WhTool_ModInit() {
    Fu_ReadToolSettings();
    fu::InitRights();
    g_trayThread =CreateThread(nullptr, 0, TrayThread, nullptr, 0, nullptr);
    if (!g_trayThread) Wh_Log(L"Couldn't start the tray thread");
    return g_trayThread != nullptr;
}

void WhTool_ModSettingsChanged() {
    Fu_ReadToolSettings();
    if (HWND hwnd = g_trayWnd) PostMessageW(hwnd, WM_APP_TRAY_REFRESH, 0, 0);
    if (HWND wnd = fuset::g_settingsWnd) PostMessageW(wnd, fuset::WM_APP_SETTINGS_RELOAD, 0, 0);
}

void WhTool_ModUninit() {
    fuset::CloseSettingsWindow();
    fuset::Fu_WaitWorkers();
    StopTrayThread();
}

BOOL WhToolLauncher_ModInit(BOOL* launch) {
    WCHAR path[MAX_PATH]{};
    GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    PCWSTR exe = PathFindFileNameW(path);
    if (_wcsicmp(exe, L"windhawk.exe") == 0) {
        *launch = TRUE;
        return TRUE;
    }
    *launch = FALSE;
    if (_wcsicmp(exe, L"explorer.exe") != 0) return FALSE;
    g_inExplorer = true;
    fuex::g_menuOn = Wh_GetIntSetting(L"menuEntry") != 0;
    fuex::HookMenus();
    fuex::StartHotkeyThread();
    return TRUE;
}

void WhToolLauncher_ModUninit() {
    if (g_inExplorer) fuex::StopHotkeyThread();
}

void WhToolLauncher_ModSettingsChanged(BOOL* reload) {
    if (!g_inExplorer) return;
    fuex::g_menuOn = Wh_GetIntSetting(L"menuEntry") != 0;
    fuex::ReloadHotkey();
}
