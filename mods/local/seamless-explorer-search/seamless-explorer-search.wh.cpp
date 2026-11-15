// ==WindhawkMod==
// @id              seamless-explorer-search
// @name            Seamless Explorer Search
// @description     Start typing in any File Explorer window to search it, and every drive, with Everything
// @version         2.0.9
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         windhawk-mod.exe
// @architecture    x86-64
// @compilerOptions -ld2d1 -ldwrite -lwindowscodecs -lole32 -loleaut32 -luuid -lgdi32 -luser32 -lshell32 -lshlwapi -ladvapi32 -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -lshcore
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Explorer Search

Windows' own search box in File Explorer is slow and its index misses things.
This mod replaces it. Click into any folder and just start typing: a search box
drops into the top of that window and fills with matches as you type, straight
from Everything's index. Files in the folder you are in come first, then
everything else on your drives.

## What it does

- Type in a folder's file list and the search box opens with your letters in it.
  Ctrl+F, Ctrl+E and F3 open it too, in place of the Windows search box.
- Matches from this folder and the folders below it sit on top; matches from
  everywhere else follow, newest first.
- Names that start with what you typed rank above names that only contain it,
  and initials work, so "ar" finds "Annual Report.docx".
- Enter opens a folder right in the same window, or a file in its app.
  Ctrl+Enter shows the item in its folder, selected. Tab opens a small menu:
  open, show in folder, open in a new window, copy the path or copy the file.
- Esc closes the box and hands the keyboard back to the folder.
- The address bar, the search box and renaming a file are never touched.
- Files open as you, without admin rights, even though Windhawk runs elevated.
- Catppuccin Mocha look with frosted glass and a blue to mauve gradient on the
  selected row. Every option is in the settings window: click the tray icon.

## What it needs

Everything (voidtools) must be running. Without it, the search box says so
instead of showing results.

## Credits

Inspired by Listary by Bopsoft (https://www.listary.com). No Listary code is
used: search runs on Everything by voidtools (https://www.voidtools.com).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- typeToSearch: true
  $name: "Type to search"
  $description: "Start typing in a folder's file list and the search box opens with what you typed."
- searchKeys: true
  $name: "Take over Ctrl+F, Ctrl+E and F3"
  $description: "These keys open this search box instead of the Windows search box."
- sameWindow: true
  $name: "Open folders in the same window"
  $description: "Enter on a folder goes there in the window you searched from. Off, it opens a new window."
- position: "top"
  $name: "Search box position"
  $description: "Where the box sits inside the folder window."
  $options:
  - top: "Top of the folder"
  - bottom: "Bottom of the folder"
- hideOnFocusLost: true
  $name: "Hide when focus is lost"
  $description: "The search box closes when you click somewhere else."
- searchAsYouType: true
  $name: "Search as you type"
  $description: "Results update on every keystroke. Off, press Enter to search."
- resultLimit: 60
  $name: "Result limit"
  $description: "10 to 200 results kept (Suggested: 60)."
- queryTimeoutMs: 200
  $name: "Query timeout (ms)"
  $description: "50 to 1000 (Suggested: 200). A stuck query is dropped after this, so Explorer never waits on it."
- matchPath: false
  $name: "Search in paths too"
  $description: "Match folder names in the full path, not just the file name."
- thisFolderFirst: true
  $name: "This folder first"
  $description: "Matches inside the folder you are in, and the folders below it, sit above the rest."
- fuzzyRanking: true
  $name: "Smart ranking"
  $description: "Start-of-name and word matches beat matches in the middle."
- accentColor: "#89B4FA"
  $name: "Accent color"
  $description: "Tints the selection, the sliders and the hover gradient start."
- popupOpacity: 85
  $name: "Search box opacity"
  $description: "How solid the glass is, 50 to 100 percent. 85 matches File Explorer (Suggested: 85)."
- animations: true
  $name: "Animations"
  $description: "Off, everything appears and closes with no movement."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it for settings, right-click it for the menu."
*/
// ==/WindhawkModSettings==

// The tool-mod host: this mod never injects into Explorer, it runs in its
// own windhawk-mod.exe process (WhTool_ModInit below).
#include <windhawk_tool_mod.h>

// Seamless Explorer Search core: a Windhawk tool mod (its own windhawk-mod.exe process, never
// injected into Explorer). Start typing in a File Explorer window and a search box drops into
// that window: results come from Everything, this folder first, then everywhere. Enter opens a
// folder in the same window or a file in its app; Ctrl+Enter shows the item in its folder.
// The settings window is the appended block (namespace slset).

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <shldisp.h>
#include <exdisp.h>
#include <shlguid.h>
#include <servprov.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <imm.h>
#include <tlhelp32.h>
#include <shellscalingapi.h>

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
#include <unordered_map>
#include <vector>

#include <windhawk_tool_mod.h>

namespace slset {
void OpenSettingsWindow();
void CloseSettingsWindow();
extern std::atomic<HWND> g_settingsWnd;
}  // namespace slset

void WhTool_ModUninit();

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------

template <class T>
struct Com {
    T* p = nullptr;
    Com() = default;
    Com(const Com&) = delete;
    Com& operator=(const Com&) = delete;
    Com(Com&& o) : p(o.p) { o.p = nullptr; }
    Com& operator=(Com&& o) {
        if (this != &o) {
            Reset();
            p = o.p;
            o.p = nullptr;
        }
        return *this;
    }
    ~Com() { Reset(); }
    void Reset() {
        if (p) p->Release();
        p = nullptr;
    }
    T** put() {
        Reset();
        return &p;
    }
    T* get() const { return p; }
    T* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

static std::wstring ReadStr(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}

static std::wstring Trim(const std::wstring& s) {
    size_t a = 0, b = s.size();
    while (a < b && iswspace(s[a])) a++;
    while (b > a && iswspace(s[b - 1])) b--;
    return s.substr(a, b - a);
}

static std::wstring Lower(std::wstring s) {
    for (auto& c : s) c = (wchar_t)towlower(c);
    return s;
}

static bool EndsWithI(const std::wstring& s, PCWSTR tail) {
    size_t n = wcslen(tail);
    return s.size() >= n && _wcsicmp(s.c_str() + s.size() - n, tail) == 0;
}

static int Clamp(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

static D2D1_COLOR_F Rgb(UINT32 rgb, float a = 1.0f) {
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.0f, ((rgb >> 8) & 0xFF) / 255.0f, (rgb & 0xFF) / 255.0f, a);
}

static UINT32 ParseColor(const std::wstring& s, UINT32 def) {
    std::wstring t = Trim(s);
    if (!t.empty() && t[0] == L'#') t.erase(0, 1);
    if (t.size() != 6) return def;
    wchar_t* end = nullptr;
    unsigned long v = wcstoul(t.c_str(), &end, 16);
    return (end && *end == 0) ? (UINT32)v : def;
}

static std::wstring NoTrailingSlash(std::wstring s) {
    while (s.size() > 1 && s.back() == L'\\') s.pop_back();
    return s;
}

static bool SamePath(const std::wstring& a, const std::wstring& b) {
    return !a.empty() && _wcsicmp(NoTrailingSlash(a).c_str(), NoTrailingSlash(b).c_str()) == 0;
}

// A drive path (C:\...) or a share (\\server\share). Libraries, This PC and Home are not.
static bool IsFileSystemPath(const std::wstring& p) {
    if (p.size() >= 3 && iswalpha(p[0]) && p[1] == L':' && p[2] == L'\\') return true;
    return p.size() > 2 && p[0] == L'\\' && p[1] == L'\\' && p[2] != L'?' && p[2] != L'.';
}

static bool ClassIs(HWND h, PCWSTR cls) {
    WCHAR b[64];
    return h && GetClassNameW(h, b, 64) && wcscmp(b, cls) == 0;
}

// `h` itself or its nearest parent of class `cls`, not above `top`.
static HWND SelfOrAncestor(HWND h, PCWSTR cls, HWND top) {
    for (int i = 0; h && i < 32; i++) {
        if (ClassIs(h, cls)) return h;
        if (h == top) break;
        h = GetAncestor(h, GA_PARENT);
    }
    return nullptr;
}

// Explorer's style bits say nothing about what shows: the CtrlNotifySink above SHELLDLL_DefView
// has no WS_VISIBLE while the files show, and after a folder change the new view has none either
// (probes, 2026-11-13). So a view counts as shown while it exists and sits in the tab that shows.
static bool ViewShown(HWND view, HWND tab) {
    return IsWindow(view) && (!tab || (IsWindowVisible(tab) && IsChild(tab, view)));
}

// The SHELLDLL_DefView under `parent` whose tab is the one showing (see ViewShown).
static HWND FindShownView(HWND parent) {
    struct Find {
        HWND parent, found;
    } f{parent, nullptr};
    EnumChildWindows(
        parent,
        [](HWND h, LPARAM lp) -> BOOL {
            auto* f = (Find*)lp;
            if (!ClassIs(h, L"SHELLDLL_DefView")) return TRUE;
            HWND tab = SelfOrAncestor(h, L"ShellTabWindowClass", f->parent);
            if (tab && !IsWindowVisible(tab)) return TRUE;
            f->found = h;
            return FALSE;
        },
        (LPARAM)&f);
    return f.found;
}

// The file list itself: DirectUIHWND, or SysListView32 in the classic view, right under the view.
static HWND ListOf(HWND view) {
    if (!view) return nullptr;
    HWND list = FindWindowExW(view, nullptr, L"DirectUIHWND", nullptr);
    return list ? list : FindWindowExW(view, nullptr, L"SysListView32", nullptr);
}

// ---------------------------------------------------------------------------
// Settings
// ---------------------------------------------------------------------------

struct Settings {
    bool typeToSearch = true;
    bool searchKeys = true;
    bool sameWindow = true;
    int position = 0;  // 0 = top of the folder, 1 = bottom
    bool hideOnFocusLost = true;
    bool searchAsYouType = true;
    int resultLimit = 60;
    int queryTimeoutMs = 200;
    bool matchPath = false;
    bool thisFolderFirst = true;
    bool fuzzyRanking = true;
    UINT32 accent = 0x89B4FA;
    int popupOpacity = 85;
    bool animations = true;  // Also read by the settings window block.
    bool settingsTrayIcon = true;
};

// Written on the UI thread (and once before it starts). The settings window reads
// `animations` from its own thread; a stale bool there only changes one transition.
static Settings g_settings;

static void LoadSettings() {
    Settings s;
    s.typeToSearch = Wh_GetIntSetting(L"typeToSearch") != 0;
    s.searchKeys = Wh_GetIntSetting(L"searchKeys") != 0;
    s.sameWindow = Wh_GetIntSetting(L"sameWindow") != 0;
    s.position = _wcsicmp(ReadStr(L"position").c_str(), L"bottom") == 0 ? 1 : 0;
    s.hideOnFocusLost = Wh_GetIntSetting(L"hideOnFocusLost") != 0;
    s.searchAsYouType = Wh_GetIntSetting(L"searchAsYouType") != 0;
    s.resultLimit = Clamp(Wh_GetIntSetting(L"resultLimit"), 10, 200);
    s.queryTimeoutMs = Clamp(Wh_GetIntSetting(L"queryTimeoutMs"), 50, 1000);
    s.matchPath = Wh_GetIntSetting(L"matchPath") != 0;
    s.thisFolderFirst = Wh_GetIntSetting(L"thisFolderFirst") != 0;
    s.fuzzyRanking = Wh_GetIntSetting(L"fuzzyRanking") != 0;
    s.accent = ParseColor(ReadStr(L"accentColor"), 0x89B4FA);
    s.popupOpacity = Clamp(Wh_GetIntSetting(L"popupOpacity"), 50, 100);
    s.animations = Wh_GetIntSetting(L"animations") != 0;
    s.settingsTrayIcon = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    g_settings = s;
}

static bool ListaryRunning() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);
    bool found = false;
    for (BOOL ok = Process32FirstW(snap, &pe); ok && !found; ok = Process32NextW(snap, &pe))
        found = _wcsicmp(pe.szExeFile, L"Listary.exe") == 0;
    CloseHandle(snap);
    return found;
}

// Set by WhTool_ModUninit before anything stops. Worker threads check it before they log
// or post, since they can outlive the mod.
static std::atomic<bool> g_stopping{false};

// ---------------------------------------------------------------------------
// Everything client: WM_COPYDATA QUERY2W, pinned against the live service in phase 0
// (probe\PROTOCOL.md). One thread owns the receiver window. The UI posts a request and
// gets the merged reply posted back; it never waits.
// ---------------------------------------------------------------------------

constexpr UINT WM_LS_RESULTS = WM_APP + 20;  // To the popup. lParam = EvReply*.
constexpr UINT WM_EV_KICK = WM_APP + 21;     // To the Everything thread's window.

enum EvStatus { kEvOk = 0, kEvNoEverything, kEvTimeout, kEvError };

struct EvItem {
    std::wstring name, dir;
    bool folder = false;
    bool local = false;  // Inside the folder the search started from.
};

struct EvRequest {
    DWORD gen = 0;
    HWND replyWnd = nullptr;
    std::wstring query;
    std::wstring folder;  // Empty: everywhere only.
    int limit = 60;
    int timeoutMs = 200;
    bool matchPath = false;
};

struct EvReply {
    DWORD gen = 0;
    int status = kEvOk;
    std::vector<EvItem> items;
};

#pragma pack(push, 1)
struct EvQuery2 {
    DWORD replyHwnd, replyId, searchFlags, offset, maxResults, requestFlags, sortType;
};
struct EvList2 {
    DWORD totItems, numItems, offset, requestFlags, sortType;
};
struct EvItem2 {
    DWORD flags, dataOffset;
};
#pragma pack(pop)

constexpr DWORD kEvCopyQuery2W = 18;
constexpr DWORD kEvSearchMatchPath = 4;
constexpr DWORD kEvRequestPathAndName = 3;
constexpr DWORD kEvSortDateModifiedDesc = 14;
constexpr DWORD kEvLocalMax = 30;

static HANDLE g_evThread;
static DWORD g_evTid;
static std::atomic<HWND> g_evWnd{nullptr};
static std::atomic<bool> g_evStop{false};
static std::atomic<EvRequest*> g_evPending{nullptr};
// Everything thread only.
static DWORD g_evExpectId;
static bool g_evGot;
static std::vector<BYTE> g_evData;

static HWND FindEverything() {
    HWND h = FindWindowW(L"EVERYTHING_TASKBAR_NOTIFICATION_(1.5a)", nullptr);
    if (!h) h = FindWindowW(L"EVERYTHING_TASKBAR_NOTIFICATION", nullptr);
    return h;
}

static void ParseReply(const BYTE* data, size_t size, bool local, std::vector<EvItem>& out) {
    if (size < sizeof(EvList2)) return;
    EvList2 list;
    memcpy(&list, data, sizeof(list));
    size_t count = std::min<size_t>(list.numItems, 1000);
    if (sizeof(EvList2) + count * sizeof(EvItem2) > size) count = (size - sizeof(EvList2)) / sizeof(EvItem2);
    auto readStr = [&](size_t& at, std::wstring& s) -> bool {
        if (at + 4 > size) return false;
        DWORD len;
        memcpy(&len, data + at, 4);
        at += 4;
        if (len > 32768 || at + (size_t)len * 2 + 2 > size) return false;
        s.assign((const wchar_t*)(data + at), len);
        at += (size_t)len * 2 + 2;
        return true;
    };
    for (size_t i = 0; i < count; i++) {
        EvItem2 it;
        memcpy(&it, data + sizeof(EvList2) + i * sizeof(EvItem2), sizeof(it));
        size_t at = it.dataOffset;
        EvItem r;
        if (!readStr(at, r.name) || !readStr(at, r.dir)) break;
        if (r.name.empty() || r.name == L"." || r.name == L"..") continue;
        r.folder = (it.flags & 1) != 0;
        r.local = local;
        out.push_back(std::move(r));
    }
}

// One query, answered before `deadline` (tick count). Runs on the Everything thread.
static int EvQuery(HWND ev, const std::wstring& search, DWORD searchFlags, DWORD max, DWORD sort, ULONGLONG deadline,
                   bool local, std::vector<EvItem>& out) {
    static DWORD s_id = 0x45530000;  // "ES"
    DWORD id = ++s_id;
    std::vector<BYTE> buf(sizeof(EvQuery2) + (search.size() + 1) * sizeof(wchar_t));
    EvQuery2 q{(DWORD)(UINT_PTR)g_evWnd.load(), id, searchFlags, 0, max, kEvRequestPathAndName, sort};
    memcpy(buf.data(), &q, sizeof(q));
    memcpy(buf.data() + sizeof(q), search.c_str(), (search.size() + 1) * sizeof(wchar_t));
    COPYDATASTRUCT cds{kEvCopyQuery2W, (DWORD)buf.size(), buf.data()};
    g_evExpectId = id;
    g_evGot = false;
    g_evData.clear();
    ULONGLONG now = GetTickCount64();
    if (now >= deadline) return kEvTimeout;
    DWORD_PTR res = 0;
    // ABORTIFHUNG, not BLOCK: Everything may send its answer while this call still waits.
    if (!SendMessageTimeoutW(ev, WM_COPYDATA, (WPARAM)g_evWnd.load(), (LPARAM)&cds, SMTO_ABORTIFHUNG,
                             (UINT)(deadline - now), &res))
        return GetLastError() == ERROR_TIMEOUT ? kEvTimeout : kEvNoEverything;
    if (!res && !g_evGot) return kEvError;
    MSG m;
    while (!g_evGot && !g_evStop) {
        now = GetTickCount64();
        if (now >= deadline) break;
        // Only sent messages (the reply) run here; a posted kick waits its turn.
        MsgWaitForMultipleObjects(0, nullptr, FALSE, (DWORD)(deadline - now), QS_SENDMESSAGE);
        PeekMessageW(&m, nullptr, 0, 0, PM_NOREMOVE | PM_QS_SENDMESSAGE);
    }
    g_evExpectId = 0;
    if (!g_evGot) return kEvTimeout;
    ParseReply(g_evData.data(), g_evData.size(), local, out);
    return kEvOk;
}

static void EvRun(const EvRequest& req) {
    auto* reply = new EvReply;
    reply->gen = req.gen;
    HWND ev = FindEverything();
    if (!ev) {
        reply->status = kEvNoEverything;
    } else {
        // One budget for both queries of a keystroke.
        ULONGLONG deadline = GetTickCount64() + (ULONGLONG)req.timeoutMs * 2;
        DWORD flags = req.matchPath ? kEvSearchMatchPath : 0;
        int st = kEvOk;
        if (!req.folder.empty()) {
            // A quoted term with a backslash matches the full path, so "C:\x\" keeps the
            // search inside that folder and every folder below it.
            std::wstring f = req.folder;
            if (f.back() != L'\\') f += L'\\';
            st = EvQuery(ev, L"\"" + f + L"\" " + req.query, flags, kEvLocalMax, kEvSortDateModifiedDesc, deadline, true,
                         reply->items);
        }
        if (st == kEvOk && !g_evStop)
            st = EvQuery(ev, req.query, flags, (DWORD)req.limit, kEvSortDateModifiedDesc, deadline, false, reply->items);
        // A slow global search still shows what this folder already gave.
        reply->status = (st == kEvTimeout && !reply->items.empty()) ? kEvOk : st;
    }
    // Junction views (L:\ and H:\) are indexed twice, and a local hit comes back again from
    // the global search: fold by full path, keeping the first.
    std::set<std::wstring> seen;
    std::vector<EvItem> unique;
    unique.reserve(reply->items.size());
    for (auto& it : reply->items)
        if (seen.insert(Lower(it.dir + L"\\" + it.name)).second) unique.push_back(std::move(it));
    reply->items.swap(unique);
    if (!PostMessageW(req.replyWnd, WM_LS_RESULTS, 0, (LPARAM)reply)) delete reply;
}

static LRESULT CALLBACK EvWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_COPYDATA) {
        auto* cds = (COPYDATASTRUCT*)lp;
        if (cds && g_evExpectId && cds->dwData == g_evExpectId && !g_evGot) {
            if (cds->lpData && cds->cbData)
                g_evData.assign((const BYTE*)cds->lpData, (const BYTE*)cds->lpData + cds->cbData);
            g_evGot = true;
        }
        return TRUE;
    }
    if (msg == WM_EV_KICK) {
        if (EvRequest* req = g_evPending.exchange(nullptr)) {
            std::unique_ptr<EvRequest> own(req);
            if (!g_evStop) EvRun(*own);
        }
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI EvThread(LPVOID ready) {
    HINSTANCE inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    WNDCLASSW wc{};
    wc.lpfnWndProc = EvWndProc;
    wc.hInstance = inst;
    wc.lpszClassName = L"SeamlessExplorerSearchEverything";
    RegisterClassW(&wc);
    HWND w = CreateWindowExW(0, wc.lpszClassName, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, inst, nullptr);
    // This process runs elevated; Everything does not. Let its answer in.
    if (w) ChangeWindowMessageFilterEx(w, WM_COPYDATA, MSGFLT_ALLOW, nullptr);
    g_evWnd = w;
    SetEvent((HANDLE)ready);
    if (w) {
        MSG m;
        while (GetMessageW(&m, nullptr, 0, 0) > 0) DispatchMessageW(&m);
    }
    g_evWnd = nullptr;
    if (w) DestroyWindow(w);
    UnregisterClassW(wc.lpszClassName, inst);
    delete g_evPending.exchange(nullptr);
    return 0;
}

static bool EvStart() {
    g_evStop = false;
    HANDLE ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_evThread = CreateThread(nullptr, 0, EvThread, ready, 0, &g_evTid);
    if (g_evThread) WaitForSingleObject(ready, 5000);
    CloseHandle(ready);
    return g_evWnd.load() != nullptr;
}

static void EvStop() {
    g_evStop = true;
    if (g_evThread) {
        PostThreadMessageW(g_evTid, WM_QUIT, 0, 0);
        if (WaitForSingleObject(g_evThread, 5000) != WAIT_OBJECT_0) Wh_Log(L"Everything thread did not stop in 5 s");
        CloseHandle(g_evThread);
        g_evThread = nullptr;
    }
}

// The latest request wins: an older one still queued is dropped.
static void EvQueryAsync(DWORD gen, HWND replyWnd, const std::wstring& query, const std::wstring& folder) {
    HWND w = g_evWnd;
    if (!w) return;
    auto* req = new EvRequest{gen,
                              replyWnd,
                              query,
                              folder,
                              g_settings.resultLimit,
                              g_settings.queryTimeoutMs,
                              g_settings.matchPath};
    delete g_evPending.exchange(req);
    PostMessageW(w, WM_EV_KICK, 0, 0);
}

// ---------------------------------------------------------------------------
// Explorer, over COM. Windhawk runs elevated, so a plain ShellExecute would start every
// app as admin; launches go through the desktop's shell view, and folder moves go through
// the Explorer window's own browser object. Every call here is cross-process and runs on
// a worker thread (ExplorerJob below), never on the UI thread.
// ---------------------------------------------------------------------------

static bool ShellExecAsUser(const std::wstring& file, const std::wstring& args, const std::wstring& dir) {
    Com<IShellWindows> windows;
    if (FAILED(CoCreateInstance(CLSID_ShellWindows, nullptr, CLSCTX_LOCAL_SERVER, IID_IShellWindows, (void**)windows.put())))
        return false;
    VARIANT empty;
    VariantInit(&empty);
    long hwnd = 0;
    Com<IDispatch> disp;
    if (windows->FindWindowSW(&empty, &empty, SWC_DESKTOP, &hwnd, SWFO_NEEDDISPATCH, disp.put()) != S_OK || !disp)
        return false;
    Com<IServiceProvider> sp;
    Com<IShellBrowser> browser;
    Com<IShellView> view;
    Com<IDispatch> viewDisp;
    Com<IShellFolderViewDual> folderView;
    Com<IDispatch> appDisp;
    Com<IShellDispatch2> shell;
    if (FAILED(disp->QueryInterface(IID_IServiceProvider, (void**)sp.put())) ||
        FAILED(sp->QueryService(SID_STopLevelBrowser, IID_IShellBrowser, (void**)browser.put())) ||
        FAILED(browser->QueryActiveShellView(view.put())) ||
        FAILED(view->GetItemObject(SVGIO_BACKGROUND, IID_IDispatch, (void**)viewDisp.put())) ||
        FAILED(viewDisp->QueryInterface(IID_IShellFolderViewDual, (void**)folderView.put())) ||
        FAILED(folderView->get_Application(appDisp.put())) ||
        FAILED(appDisp->QueryInterface(IID_IShellDispatch2, (void**)shell.put())))
        return false;
    BSTR bFile = SysAllocString(file.c_str());
    VARIANT vArgs, vDir, vOp, vShow;
    VariantInit(&vArgs);
    VariantInit(&vDir);
    VariantInit(&vOp);
    VariantInit(&vShow);
    vArgs.vt = VT_BSTR;
    vArgs.bstrVal = SysAllocString(args.c_str());
    vDir.vt = VT_BSTR;
    vDir.bstrVal = SysAllocString(dir.c_str());
    vOp.vt = VT_BSTR;
    vOp.bstrVal = SysAllocString(L"open");
    vShow.vt = VT_I4;
    vShow.lVal = SW_SHOWNORMAL;
    HRESULT hr = shell->ShellExecute(bFile, vArgs, vDir, vOp, vShow);
    SysFreeString(bFile);
    VariantClear(&vArgs);
    VariantClear(&vDir);
    VariantClear(&vOp);
    return SUCCEEDED(hr);
}

// Folder2 {F0D2D8EF-3890-11D2-BF8B-00C04FB93661}, spelled out so no import library has to carry it.
static const IID kIID_Folder2 = {0xF0D2D8EF, 0x3890, 0x11D2, {0xBF, 0x8B, 0x00, 0xC0, 0x4F, 0xB9, 0x36, 0x61}};

// The browser object of Explorer window `top`, on tab `tab` when the window has several.
static Com<IWebBrowser2> FindBrowser(HWND top, HWND tab) {
    Com<IWebBrowser2> first;
    Com<IShellWindows> windows;
    if (FAILED(CoCreateInstance(CLSID_ShellWindows, nullptr, CLSCTX_LOCAL_SERVER, IID_IShellWindows, (void**)windows.put())))
        return first;
    long count = 0;
    if (FAILED(windows->get_Count(&count))) return first;
    for (long i = 0; i < count && !g_stopping; i++) {
        VARIANT index;
        VariantInit(&index);
        index.vt = VT_I4;
        index.lVal = i;
        Com<IDispatch> disp;
        if (FAILED(windows->Item(index, disp.put())) || !disp) continue;
        Com<IWebBrowser2> wb;
        if (FAILED(disp->QueryInterface(IID_IWebBrowser2, (void**)wb.put())) || !wb) continue;
        SHANDLE_PTR h = 0;
        if (FAILED(wb->get_HWND(&h)) || (HWND)h != top) continue;
        if (!tab) return wb;
        // Each tab has its own browser; its shell browser's window is the tab window.
        Com<IServiceProvider> sp;
        Com<IShellBrowser> sb;
        HWND w = nullptr;
        if (SUCCEEDED(wb->QueryInterface(IID_IServiceProvider, (void**)sp.put())) &&
            SUCCEEDED(sp->QueryService(SID_STopLevelBrowser, IID_IShellBrowser, (void**)sb.put())) &&
            SUCCEEDED(sb->GetWindow(&w)) && w == tab)
            return wb;
        if (!first) first = std::move(wb);
    }
    return first;
}

// The folder a browser shows, as a path ("" for virtual folders); its view in `viewOut`.
static std::wstring BrowserPath(IWebBrowser2* wb, Com<IShellFolderViewDual>* viewOut = nullptr) {
    Com<IDispatch> doc;
    Com<IShellFolderViewDual> view;
    Com<Folder> folder;
    Com<Folder2> folder2;
    Com<FolderItem> self;
    if (FAILED(wb->get_Document(doc.put())) || !doc ||
        FAILED(doc->QueryInterface(IID_IShellFolderViewDual, (void**)view.put())) || !view ||
        FAILED(view->get_Folder(folder.put())) || !folder ||
        FAILED(folder->QueryInterface(kIID_Folder2, (void**)folder2.put())) || !folder2 ||
        FAILED(folder2->get_Self(self.put())) || !self)
        return L"";
    BSTR b = nullptr;
    std::wstring path;
    if (SUCCEEDED(self->get_Path(&b)) && b) path = b;
    SysFreeString(b);
    if (viewOut) *viewOut = std::move(view);
    return path;
}

static bool NavigateTo(IWebBrowser2* wb, const std::wstring& path) {
    VARIANT url, empty;
    VariantInit(&url);
    VariantInit(&empty);
    url.vt = VT_BSTR;
    url.bstrVal = SysAllocString(path.c_str());
    HRESULT hr = wb->Navigate2(&url, &empty, &empty, &empty, &empty);
    VariantClear(&url);
    return SUCCEEDED(hr);
}

// Shows `dir` in the browser and selects `full` in it.
static bool RevealIn(IWebBrowser2* wb, const std::wstring& full, const std::wstring& dir) {
    std::wstring before = BrowserPath(wb);
    if (!SamePath(before, dir)) {
        if (!NavigateTo(wb, dir)) return false;
        ULONGLONG until = GetTickCount64() + 3000;
        while (GetTickCount64() < until && !g_stopping) {
            Sleep(60);
            VARIANT_BOOL busy = VARIANT_FALSE;
            wb->get_Busy(&busy);
            std::wstring now = BrowserPath(wb);
            if (busy == VARIANT_FALSE && (SamePath(now, dir) || (!now.empty() && !SamePath(now, before)))) break;
        }
    }
    size_t slash = full.find_last_of(L'\\');
    std::wstring name = slash == std::wstring::npos ? full : full.substr(slash + 1);
    for (int attempt = 0; attempt < 5 && !g_stopping; attempt++) {
        if (attempt) Sleep(100);
        Com<IShellFolderViewDual> view;
        BrowserPath(wb, &view);
        Com<Folder> folder;
        if (!view || FAILED(view->get_Folder(folder.put())) || !folder) continue;
        BSTR b = SysAllocString(name.c_str());
        Com<FolderItem> item;
        HRESULT hr = folder->ParseName(b, item.put());
        SysFreeString(b);
        if (FAILED(hr) || !item) continue;
        VARIANT v;
        VariantInit(&v);
        v.vt = VT_DISPATCH;
        v.pdispVal = item.get();  // Borrowed: `item` keeps the reference.
        // SVSI_SELECT | SVSI_DESELECTOTHERS | SVSI_ENSUREVISIBLE | SVSI_FOCUSED
        if (SUCCEEDED(view->SelectItem(&v, 1 | 4 | 8 | 16))) return true;
    }
    return false;
}

constexpr UINT WM_ES_FOLDER = WM_APP + 42;  // To the popup. wParam = open number, lParam = std::wstring*.

enum JobKind { kJobFolder, kJobNavigate, kJobReveal, kJobLaunch, kJobFocus };

struct ExplorerJob {
    int kind;
    HWND top, tab;
    std::wstring path, dir;
    DWORD openGen;
    HWND reply;
    HMODULE self;
    HWND view = nullptr;
};

// After the popup hides, Explorer's frame comes forward but keeps the keyboard on itself, not on
// the file list it had (take 10), so typing then goes nowhere. Put it back in the list, only when
// the frame is in front holding the keyboard itself: focus Explorer placed elsewhere stays put.
// SetFocus into another thread needs its input attached; this runs on a job thread so a hung
// Explorer can only hold this thread.
static void FocusFileList(const ExplorerJob* job) {
    ULONGLONG until = GetTickCount64() + 500;
    while (GetForegroundWindow() != job->top && GetTickCount64() < until && !g_stopping) Sleep(20);
    if (g_stopping || GetForegroundWindow() != job->top) return;
    MSG m;
    PeekMessageW(&m, nullptr, 0, 0, PM_NOREMOVE);  // AttachThreadInput wants a message queue here.
    DWORD me = GetCurrentThreadId();
    // Explorer handles its own activation after the frame is already in front, and that puts the
    // keyboard on the frame, after a SetFocus made too early (take 16). So: let it handle what it
    // has queued, then watch for 600 ms and hand the keyboard to the list each time the frame takes it.
    int held = 0;
    for (ULONGLONG end = GetTickCount64() + 600; GetTickCount64() < end && held < 3 && !g_stopping; Sleep(50)) {
        DWORD_PTR r;
        if (!SendMessageTimeoutW(job->top, WM_NULL, 0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 200, &r)) return;
        if (GetForegroundWindow() != job->top) return;
        HWND view = IsWindow(job->view) ? job->view : FindShownView(job->tab && IsWindow(job->tab) ? job->tab : job->top);
        HWND list = ListOf(view);
        if (!list || GetAncestor(list, GA_ROOT) != job->top) return;
        DWORD tid = GetWindowThreadProcessId(list, nullptr);
        GUITHREADINFO gti{};
        gti.cbSize = sizeof(gti);
        if (!GetGUIThreadInfo(tid, &gti)) return;
        if (gti.hwndFocus == list) {
            held++;
            continue;
        }
        if (gti.hwndFocus && gti.hwndFocus != job->top) return;  // Explorer put it somewhere on purpose.
        held = 0;
        if (!AttachThreadInput(me, tid, TRUE)) return;
        SetFocus(list);
        AttachThreadInput(me, tid, FALSE);
    }
}

static std::atomic<int> g_jobs{0};

// Each job runs on its own thread: a cross-process call on the UI thread once parked the
// popup in COM's modal loop, where posted search results were never read (1.2.0, 3:19 pm).
// The thread holds its own reference to this module, so a slow Explorer can outlive an unload.
static DWORD WINAPI ExplorerJobThread(LPVOID param) {
    auto* job = (ExplorerJob*)param;
    HMODULE self = job->self;
    HRESULT co = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    bool ok = true;
    switch (job->kind) {
        case kJobFolder: {
            std::wstring path;
            {
                Com<IWebBrowser2> wb = FindBrowser(job->top, job->tab);
                if (wb) path = BrowserPath(wb.get());
            }
            if (!IsFileSystemPath(path)) path.clear();
            auto* s = new std::wstring(std::move(path));
            if (g_stopping || !PostMessageW(job->reply, WM_ES_FOLDER, job->openGen, (LPARAM)s)) delete s;
            break;
        }
        case kJobNavigate: {
            {
                Com<IWebBrowser2> wb = job->top ? FindBrowser(job->top, job->tab) : Com<IWebBrowser2>();
                ok = wb && NavigateTo(wb.get(), job->path);
            }
            if (!ok) ok = ShellExecAsUser(job->path, L"", L"");
            break;
        }
        case kJobReveal: {
            ok = false;
            if (job->top) {
                Com<IWebBrowser2> wb = FindBrowser(job->top, job->tab);
                ok = wb && RevealIn(wb.get(), job->path, job->dir);
            }
            // Selecting the file can leave the keyboard on Explorer's frame after the hide's own
            // hand-back has already finished (take 22), so hand it to the list again once selected.
            if (ok) FocusFileList(job);
            if (!ok && !g_stopping) ok = ShellExecAsUser(L"explorer.exe", L"/select,\"" + job->path + L"\"", L"");
            break;
        }
        case kJobLaunch:
            ok = ShellExecAsUser(job->path, L"", job->dir);
            break;
        case kJobFocus:
            FocusFileList(job);
            break;
    }
    if (SUCCEEDED(co)) CoUninitialize();
    if (!ok && !g_stopping) Wh_Log(L"Couldn't open %s", job->path.c_str());
    g_jobs--;
    delete job;
    FreeLibraryAndExitThread(self, 0);
}

// ---------------------------------------------------------------------------
// Graphics
// ---------------------------------------------------------------------------

namespace pal {
constexpr UINT32 base = 0x1E1E2E, crust = 0x11111B, surface0 = 0x313244, text = 0xCDD6F4,
                 subtext = 0xA6ADC8, overlay = 0x6C7086, mauve = 0xCBA6F7, red = 0xF38BA8;
}

static Com<ID2D1Factory> g_d2d;
static Com<IDWriteFactory> g_dw;
static Com<IDWriteTextFormat> g_fQuery, g_fName, g_fDir, g_fHint, g_fHintRight, g_fGlyph, g_fGlyphBig;
static Com<IDWriteInlineObject> g_ellName, g_ellDir, g_ellQuery, g_ellHint;
static std::wstring g_family = L"Segoe UI";

static bool FontExists(const std::wstring& family) {
    Com<IDWriteFontCollection> fc;
    if (!g_dw || FAILED(g_dw->GetSystemFontCollection(fc.put(), FALSE))) return false;
    UINT32 i = 0;
    BOOL found = FALSE;
    return SUCCEEDED(fc->FindFamilyName(family.c_str(), &i, &found)) && found;
}

static void MakeFormat(Com<IDWriteTextFormat>& f, Com<IDWriteInlineObject>* ell, const std::wstring& family, float size,
                       DWRITE_FONT_WEIGHT weight) {
    f.Reset();
    if (FAILED(g_dw->CreateTextFormat(family.c_str(), nullptr, weight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
                                      size, L"en-us", f.put())))
        return;
    f->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    f->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if (ell) {
        ell->Reset();
        if (SUCCEEDED(g_dw->CreateEllipsisTrimmingSign(f.get(), ell->put()))) {
            DWRITE_TRIMMING trim{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
            f->SetTrimming(&trim, ell->get());
        }
    }
}

static void MakeFormats() {
    g_family = L"Segoe UI";
    for (PCWSTR f : {L"Segoe UI Variable Text", L"Segoe UI"})
        if (FontExists(f)) {
            g_family = f;
            break;
        }
    std::wstring icons = FontExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    MakeFormat(g_fQuery, &g_ellQuery, g_family, 17, DWRITE_FONT_WEIGHT_NORMAL);
    MakeFormat(g_fName, &g_ellName, g_family, 14, DWRITE_FONT_WEIGHT_SEMI_BOLD);
    MakeFormat(g_fDir, &g_ellDir, g_family, 11.5f, DWRITE_FONT_WEIGHT_NORMAL);
    MakeFormat(g_fHint, &g_ellHint, g_family, 11.5f, DWRITE_FONT_WEIGHT_NORMAL);
    MakeFormat(g_fHintRight, nullptr, g_family, 11.5f, DWRITE_FONT_WEIGHT_NORMAL);
    MakeFormat(g_fGlyph, nullptr, icons, 16, DWRITE_FONT_WEIGHT_NORMAL);
    MakeFormat(g_fGlyphBig, nullptr, icons, 18, DWRITE_FONT_WEIGHT_NORMAL);
    for (auto* f : {&g_fGlyph, &g_fGlyphBig})
        if (*f) (*f)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    if (g_fHintRight) g_fHintRight->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
}

static bool TransparencyOn() {
    DWORD v = 1, cb = sizeof(v);
    RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                 L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &v, &cb);
    return v != 0;
}

// File Explorer's own glass (Seamless Flyouts' explorer.exe rule, AccentBlurBehind D81E1E2E):
// acrylic accent with a Mocha base tint at the search box opacity, 85% being Explorer's 0xD8.
// The tint carries the whole look, so the popup paints no wash of its own on top.
static bool SetGlass(HWND hwnd, bool on, int opacity) {
    struct AccentPolicy {
        int state, flags;
        DWORD abgr;
        int animation;
    };
    struct CompositionData {
        int attribute;
        PVOID data;
        SIZE_T size;
    };
    using Fn = BOOL(WINAPI*)(HWND, CompositionData*);
    static Fn fn = (Fn)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (!fn) return false;
    DWORD alpha = (DWORD)(Clamp(opacity, 1, 100) * 255 / 100);
    AccentPolicy ap{on ? 4 : 0, 2, (alpha << 24) | 0x2E1E1E, 0};
    CompositionData d{19, &ap, sizeof(ap)};
    return fn(hwnd, &d) != FALSE;
}

// DWM rounds the popup with the system window radius, which the Custom Window Corner Radius
// mod sets (16 on this machine, not Windows' 8), scaled by DPI like every window. The edge is
// drawn on that same curve: drawn on a tighter one, DWM's clip shaves it thin at the corners.
static float WindowCornerRadiusDip() {
    float r = 8;
    HKEY k;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0, KEY_READ, &k) !=
        ERROR_SUCCESS)
        return r;
    DWORD v = 0, cb = sizeof(v);
    bool on = RegGetValueW(k, nullptr, L"Disabled", RRF_RT_REG_DWORD, nullptr, &v, &cb) != ERROR_SUCCESS || v == 0;
    v = 0;
    cb = sizeof(v);
    if (on && RegGetValueW(k, L"Settings", L"radius", RRF_RT_REG_DWORD, nullptr, &v, &cb) == ERROR_SUCCESS && v <= 64)
        r = (float)v;
    RegCloseKey(k);
    return r;
}

// ---------------------------------------------------------------------------
// Search popup
// ---------------------------------------------------------------------------

constexpr WCHAR kPopupClass[] = L"SeamlessExplorerSearchPopup", kMsgClass[] = L"SeamlessExplorerSearchMsg";
constexpr UINT WM_LS_TRAY = WM_APP + 30, WM_LS_SETTINGS = WM_APP + 32;
constexpr UINT WM_ES_TYPE = WM_APP + 40;  // To the msg window. wParam = character (0: none), lParam = focused HWND.
constexpr UINT WM_ES_KEY = WM_APP + 41;   // To the msg window. wParam = virtual key for the popup.
constexpr UINT_PTR kTimerCaret = 1, kTimerFolder = 2, kTimerWatch = 3, kTimerBeat = 4, kTimerLost = 5;
constexpr UINT kFolderWaitMs = 250, kWatchMs = 250;
// Focus lost: the box waits kLostCheckMs before it hides. Within kRegrabMs of opening, a bounce
// straight back to its own Explorer window (not a click) takes the keyboard back, at most twice.
constexpr UINT kLostCheckMs = 60, kRegrabMs = 1000;
constexpr UINT WM_ES_DIAG = WM_APP + 43;  // To the msg window. wParam = pass reason, lParam = focused HWND.
constexpr UINT kTrayId = 1;
// Layout in DIPs.
constexpr float kPopW = 640, kPopMinW = 420, kMargin = 12, kPad = 12, kQueryTop = 10, kQueryH = 40, kListTop = 62,
                kRowH = 46, kFootH = 34;
constexpr int kMaxRows = 8, kMinRows = 3;

// The Explorer window, tab and file view the popup was opened from.
struct Target {
    HWND top = nullptr, tab = nullptr, view = nullptr;
    std::wstring folder;  // Its folder path, once the lookup answers. Empty: not a real folder.
};

struct Row {
    EvItem item;
    std::wstring full;
    std::wstring where;  // The second line: the folder, relative to this one when inside it.
};

struct Popup {
    HWND hwnd = nullptr;
    Com<ID2D1HwndRenderTarget> rt;
    bool glass = false;
    float radius = 8;  // DWM's corner radius in DIPs, read at each show.
    bool visible = false;
    UINT dpi = 96;
    Target target;
    HMONITOR freeMon = nullptr;  // Opened with no Explorer window (automation): this monitor.
    std::wstring query;
    DWORD gen = 0;      // Search number.
    DWORD openGen = 0;  // Open number, for the folder lookup.
    bool folderPending = false;
    bool waiting = false;
    bool dirty = false;  // Query changed and not searched yet (search as you type off).
    int status = kEvOk;
    std::vector<Row> rows;
    int sel = 0, scroll = 0, hover = -1;
    int maxRows = kMaxRows;
    bool caretOn = true;
    bool tracking = false;
    ULONGLONG shownAt = 0;
    int regrabs = 0;
    bool lostByClick = false;
};

static Popup g_pop;
static HWND g_msgWnd;
static HINSTANCE g_inst;
static bool g_paused;

// Read by the keyboard hook thread.
static std::atomic<HWND> g_hookMsg{nullptr};
static std::atomic<HWND> g_popupFor{nullptr};  // The Explorer window the visible popup belongs to.
static std::atomic<bool> g_hookType{true}, g_hookKeys{true}, g_hookForward{true}, g_listaryUp{false};
static std::atomic<ULONGLONG> g_uiBeat{0};
static std::atomic<ULONGLONG> g_shownAt{0};  // When the box last opened: the hook reports passed keys for 3 s.

// The last few reasons the box closed or a key went past it, for Windhawk's log and for the
// live test (stored as the mod value "diag"). UI thread only.
static std::wstring g_diag;

static std::wstring ProcessOf(HWND h) {
    DWORD pid = 0;
    if (h) GetWindowThreadProcessId(h, &pid);
    std::wstring name = L"?";
    if (HANDLE proc = pid ? OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid) : nullptr) {
        wchar_t buf[MAX_PATH];
        DWORD n = MAX_PATH;
        if (QueryFullProcessImageNameW(proc, 0, buf, &n)) {
            const wchar_t* slash = wcsrchr(buf, L'\\');
            name = slash ? slash + 1 : buf;
        }
        CloseHandle(proc);
    }
    return name;
}

static void Diag(const wchar_t* what, HWND h) {
    wchar_t cls[64] = L"";
    if (h) GetClassNameW(h, cls, 64);
    wchar_t line[256];
    swprintf_s(line, L"%llu %s: %s %s", GetTickCount64(), what, cls, h ? ProcessOf(h).c_str() : L"");
    Wh_Log(L"%s", line);
    g_diag += line;
    g_diag += L"\n";
    if (g_diag.size() > 3000) g_diag.erase(0, g_diag.size() - 3000);
    Wh_SetStringValue(L"diag", g_diag.c_str());
}

static bool StartJob(int kind, const Target& t, const std::wstring& path, const std::wstring& dir) {
    if (g_jobs.load() >= 6) {
        Wh_Log(L"Explorer is not answering; %s skipped", path.empty() ? L"folder lookup" : path.c_str());
        return false;
    }
    HMODULE self = nullptr;
    if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)&ExplorerJobThread, &self)) return false;
    auto* job = new ExplorerJob{kind, t.top, t.tab, path, dir, g_pop.openGen, g_pop.hwnd, self, t.view};
    g_jobs++;
    HANDLE th = CreateThread(nullptr, 0, ExplorerJobThread, job, 0, nullptr);
    if (th) {
        CloseHandle(th);
        return true;
    }
    g_jobs--;
    delete job;
    FreeLibrary(self);
    return false;
}

// 0 starts with, 1 word start or initials, 2 contains, 3 no name match.
static int MatchScore(const std::wstring& nameLower, const std::wstring& q) {
    if (q.empty()) return 3;
    size_t pos = nameLower.find(q);
    if (pos == 0) return 0;
    for (size_t i = 1; i < nameLower.size(); i++) {
        wchar_t p = nameLower[i - 1];
        bool boundary = p == L' ' || p == L'.' || p == L'-' || p == L'_' || p == L'(' || p == L'[';
        if (boundary && nameLower.compare(i, q.size(), q) == 0) return 1;
    }
    if (pos != std::wstring::npos) return 2;
    // Initials: "vsc" for "Visual Studio Code".
    size_t qi = 0;
    for (size_t i = 0; i < nameLower.size() && qi < q.size(); i++) {
        bool start = i == 0 || nameLower[i - 1] == L' ' || nameLower[i - 1] == L'-' || nameLower[i - 1] == L'_';
        if (start && nameLower[i] == q[qi]) qi++;
    }
    return qi == q.size() ? 1 : 3;
}

static std::wstring WhereText(const EvItem& it, const std::wstring& folder) {
    if (it.local && !folder.empty()) {
        std::wstring f = NoTrailingSlash(folder);
        if (_wcsicmp(it.dir.c_str(), f.c_str()) == 0) return L"This folder";
        if (it.dir.size() > f.size() && _wcsnicmp(it.dir.c_str(), f.c_str(), f.size()) == 0 &&
            (it.dir[f.size()] == L'\\' || f.back() == L'\\'))
            return L"This folder \\ " + it.dir.substr(f.size() + (it.dir[f.size()] == L'\\' ? 1 : 0));
    }
    return it.dir;
}

static void SetResults(std::vector<EvItem>&& items) {
    const Settings& s = g_settings;
    std::wstring q = Lower(Trim(g_pop.query));
    // The first word decides the name score; the rest is left to Everything's filter.
    size_t sp = q.find(L' ');
    std::wstring first = sp == std::wstring::npos ? q : q.substr(0, sp);
    struct Scored {
        Row row;
        int score;
    };
    std::vector<Scored> list;
    list.reserve(items.size());
    for (auto& it : items) {
        Row r;
        r.full = it.dir.empty() ? it.name : it.dir + (it.dir.back() == L'\\' ? L"" : L"\\") + it.name;
        r.where = WhereText(it, g_pop.target.folder);
        int score = 0;
        if (s.fuzzyRanking) score = MatchScore(Lower(it.name), first) * 100;
        if (s.thisFolderFirst && it.local) score -= 1000;
        r.item = std::move(it);
        list.push_back({std::move(r), score});
    }
    bool byLength = s.fuzzyRanking;
    std::stable_sort(list.begin(), list.end(), [byLength](const Scored& a, const Scored& b) {
        if (a.score != b.score) return a.score < b.score;
        return byLength && a.row.item.name.size() < b.row.item.name.size();
    });
    g_pop.rows.clear();
    for (auto& sc : list) g_pop.rows.push_back(std::move(sc.row));
    g_pop.sel = 0;
    g_pop.scroll = 0;
    g_pop.hover = -1;
}

static int VisibleRows() {
    int n = std::min((int)g_pop.rows.size(), g_pop.maxRows);
    bool message = g_pop.rows.empty() && !Trim(g_pop.query).empty();
    return std::max(n, message ? 1 : 0);
}

static float PopupHeightDip() {
    int rows = VisibleRows();
    return kListTop + (rows ? rows * kRowH + 6 : 0) + kFootH;
}

// Real file icons, cached by path; the D2D copies are cached per render target.
static std::unordered_map<std::wstring, HICON> g_icons;
static std::unordered_map<std::wstring, Com<ID2D1Bitmap>> g_bmps;
static void* g_bmpRt;
static Com<IWICImagingFactory> g_wic;

static HICON RowIcon(const Row& r) {
    std::wstring key = Lower(r.full);
    auto it = g_icons.find(key);
    if (it != g_icons.end()) return it->second;
    SHFILEINFOW sfi{};
    // Attributes let a path that has vanished still get its type icon.
    DWORD attrs = r.item.folder ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
    HICON h = (HICON)SHGetFileInfoW(r.full.c_str(), attrs, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON);
    if (g_icons.size() > 400) {
        for (auto& [k, ic] : g_icons) {
            if (ic) DestroyIcon(ic);
        }
        g_icons.clear();
    }
    g_icons.emplace(std::move(key), h);
    return h;
}

static Com<ID2D1Bitmap>* RowBitmap(ID2D1HwndRenderTarget* rt, const Row& r) {
    if (!g_wic) return nullptr;
    if (g_bmpRt != rt) {
        g_bmps.clear();
        g_bmpRt = rt;
    }
    std::wstring key = Lower(r.full);
    auto it = g_bmps.find(key);
    if (it == g_bmps.end()) {
        HICON h = RowIcon(r);
        if (!h) return nullptr;
        Com<IWICBitmap> wic;
        Com<ID2D1Bitmap> bmp;
        if (FAILED(g_wic->CreateBitmapFromHICON(h, wic.put())) ||
            FAILED(rt->CreateBitmapFromWicBitmap(wic.get(), bmp.put())))
            return nullptr;
        it = g_bmps.emplace(std::move(key), std::move(bmp)).first;
    }
    return &it->second;
}

static void DrawPopup() {
    Popup& p = g_pop;
    if (!p.hwnd || !p.visible) return;
    if (!p.rt) {
        RECT rc;
        GetClientRect(p.hwnd, &rc);
        auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                                  D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
        if (FAILED(g_d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(p.hwnd, D2D1::SizeU(rc.right, rc.bottom)),
                                                 p.rt.put())))
            return;
    }
    ID2D1HwndRenderTarget* rt = p.rt.get();
    rt->SetDpi((float)p.dpi, (float)p.dpi);
    D2D1_SIZE_F sz = rt->GetSize();
    float W = sz.width, H = sz.height;
    const Settings& s = g_settings;

    rt->BeginDraw();
    rt->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    rt->Clear(p.glass ? D2D1::ColorF(0, 0, 0, 0) : Rgb(pal::base));
    Com<ID2D1SolidColorBrush> b;
    rt->CreateSolidColorBrush(Rgb(pal::crust, 0), b.put());
    D2D1_GRADIENT_STOP stops[2] = {{0, Rgb(s.accent)}, {1, Rgb(pal::mauve)}};
    Com<ID2D1GradientStopCollection> sc;
    Com<ID2D1LinearGradientBrush> grad;
    rt->CreateGradientStopCollection(stops, 2, sc.put());
    if (sc) rt->CreateLinearGradientBrush({{0, 0}, {W, 0}}, D2D1::BrushProperties(), sc.get(), grad.put());
    if (!b || !grad) {
        rt->EndDraw();
        return;
    }
    // Edge: the window borders' look (Seamless Borders: 2 px, accent to mauve at 45 degrees),
    // on DWM's own corner curve so no corner gets shaved.
    {
        const float ew = 2, er = std::max(p.radius - ew / 2, 0.0f), t = (W + H) / 2;
        Com<ID2D1LinearGradientBrush> edge;
        if (sc) rt->CreateLinearGradientBrush({{0, 0}, {t, t}}, D2D1::BrushProperties(), sc.get(), edge.put());
        if (edge)
            rt->DrawRoundedRectangle(D2D1::RoundedRect({ew / 2, ew / 2, W - ew / 2, H - ew / 2}, er, er), edge.get(), ew);
    }

    // Query row.
    float gx = kPad + 4;
    D2D1_RECT_F qr{gx, kQueryTop, W - kPad, kQueryTop + kQueryH};
    grad->SetStartPoint({gx, 0});
    grad->SetEndPoint({gx + 26, 0});
    if (g_fGlyphBig) rt->DrawText(L"\xE721", 1, g_fGlyphBig.get(), {gx, qr.top, gx + 26, qr.bottom}, grad.get());
    grad->SetStartPoint({0, 0});
    grad->SetEndPoint({W, 0});
    float tx = gx + 38;
    if (g_fQuery) {
        if (p.query.empty()) {
            b->SetColor(Rgb(pal::overlay));
            PCWSTR ph = L"Search files and folders";
            rt->DrawText(ph, (UINT32)wcslen(ph), g_fQuery.get(), {tx, qr.top, qr.right, qr.bottom}, b.get());
        } else {
            b->SetColor(Rgb(pal::text));
            rt->DrawText(p.query.c_str(), (UINT32)p.query.size(), g_fQuery.get(), {tx, qr.top, qr.right, qr.bottom}, b.get());
        }
        if (p.caretOn) {
            float cw = 0;
            Com<IDWriteTextLayout> lay;
            if (!p.query.empty() &&
                SUCCEEDED(g_dw->CreateTextLayout(p.query.c_str(), (UINT32)p.query.size(), g_fQuery.get(), 4000, kQueryH, lay.put()))) {
                DWRITE_TEXT_METRICS m{};
                lay->GetMetrics(&m);
                cw = m.widthIncludingTrailingWhitespace;
            }
            float cx = std::min(tx + cw + 1, qr.right - 2);
            b->SetColor(Rgb(pal::text));
            rt->FillRectangle({cx, qr.top + 10, cx + 1.5f, qr.bottom - 10}, b.get());
        }
    }
    if (p.waiting && g_fHint) {
        b->SetColor(Rgb(pal::overlay));
        rt->DrawText(L"\x2026", 1, g_fHint.get(), {W - kPad - 24, qr.top, W - kPad, qr.bottom}, b.get());
    }
    // Hairline under the query, in the gradient.
    grad->SetOpacity(0.45f);
    rt->FillRectangle({kPad, kListTop - 9, W - kPad, kListTop - 8}, grad.get());
    grad->SetOpacity(1);

    // Rows.
    float y = kListTop;
    int shown = 0;
    if (p.rows.empty() && !Trim(p.query).empty() && g_fHint) {
        PCWSTR msg = p.waiting  ? L"Searching"
                     : p.dirty ? L"Press Enter to search"
                     : p.status == kEvNoEverything ? L"Everything isn't running, so there is nothing to search. Start Everything."
                     : p.status == kEvTimeout ? L"Everything took too long to answer. Try again."
                     : p.status == kEvError   ? L"Everything turned the search down."
                                              : L"No results";
        bool bad = !p.waiting && !p.dirty && p.status != kEvOk;
        b->SetColor(Rgb(bad ? pal::red : pal::overlay));
        rt->DrawText(msg, (UINT32)wcslen(msg), g_fHint.get(), {kPad + 14, y, W - kPad, y + kRowH}, b.get());
    }
    for (int i = p.scroll; i < (int)p.rows.size() && shown < p.maxRows; i++, shown++, y += kRowH) {
        const Row& r = p.rows[i];
        bool sel = i == p.sel, hov = i == p.hover && !sel;
        D2D1_ROUNDED_RECT rr = D2D1::RoundedRect({kPad, y + 2, W - kPad, y + kRowH - 2}, 7, 7);
        if (sel) {
            grad->SetOpacity(0.16f);
            rt->FillRoundedRectangle(rr, grad.get());
            grad->SetOpacity(1);
            D2D1_ROUNDED_RECT ring = D2D1::RoundedRect({kPad + 0.75f, y + 2.75f, W - kPad - 0.75f, y + kRowH - 2.75f}, 6.5f, 6.5f);
            rt->DrawRoundedRectangle(ring, grad.get(), 1.5f);
        } else if (hov) {
            b->SetColor(Rgb(pal::surface0, 0.55f));
            rt->FillRoundedRectangle(rr, b.get());
        }
        WCHAR glyph = r.item.folder ? 0xE8B7 : EndsWithI(r.item.name, L".exe") ? 0xECAA : 0xE8A5;
        float ix = kPad + 10;
        Com<ID2D1Bitmap>* icon = RowBitmap(rt, r);
        if (icon) {
            rt->DrawBitmap(icon->get(), {ix, y + 11, ix + 24, y + 35});
        } else if (g_fGlyph) {
            if (sel) {
                grad->SetStartPoint({ix, 0});
                grad->SetEndPoint({ix + 24, 0});
                rt->DrawText(&glyph, 1, g_fGlyph.get(), {ix, y, ix + 24, y + kRowH}, grad.get());
                grad->SetStartPoint({0, 0});
                grad->SetEndPoint({W, 0});
            } else {
                b->SetColor(Rgb(pal::subtext));
                rt->DrawText(&glyph, 1, g_fGlyph.get(), {ix, y, ix + 24, y + kRowH}, b.get());
            }
        }
        float nx = ix + 36, right = W - kPad - 12;
        if (g_fName) {
            b->SetColor(Rgb(pal::text));
            rt->DrawText(r.item.name.c_str(), (UINT32)r.item.name.size(), g_fName.get(), {nx, y + 5, right, y + 25}, b.get());
        }
        if (g_fDir) {
            b->SetColor(Rgb(sel ? pal::subtext : pal::overlay));
            rt->DrawText(r.where.c_str(), (UINT32)r.where.size(), g_fDir.get(), {nx, y + 24, right, y + 41}, b.get());
        }
    }

    // Footer: key hints on the left, the result count on the right.
    if (g_fHint && g_fHintRight) {
        b->SetColor(Rgb(pal::overlay));
        float countW = 0;
        if (!p.rows.empty()) {
            std::wstring count = std::to_wstring(p.rows.size()) + (p.rows.size() == 1 ? L" result" : L" results");
            countW = 96;
            rt->DrawText(count.c_str(), (UINT32)count.size(), g_fHintRight.get(), {W - kPad - 14 - countW, H - kFootH, W - kPad - 14, H - 4},
                         b.get());
        }
        PCWSTR hint = L"Enter  open   \x00B7   Ctrl+Enter  show in folder   \x00B7   Tab  more   \x00B7   Esc  close";
        rt->DrawText(hint, (UINT32)wcslen(hint), g_fHint.get(), {kPad + 14, H - kFootH, W - kPad - 14 - countW - 8, H - 4},
                     b.get(), D2D1_DRAW_TEXT_OPTIONS_CLIP);
    }
    if (rt->EndDraw() == D2DERR_RECREATE_TARGET) p.rt.Reset();
}

static void InvalidatePopup() {
    if (g_pop.hwnd) InvalidateRect(g_pop.hwnd, nullptr, FALSE);
}

// Inside the Explorer window's file list, at its top or bottom, centred. Read again on every
// call, so the popup follows the window when it moves or resizes.
static void PlacePopup() {
    Popup& p = g_pop;
    RECT anchor{};
    bool anchored = p.target.view && IsWindow(p.target.view) && GetWindowRect(p.target.view, &anchor) &&
                    anchor.right - anchor.left > 50 && anchor.bottom - anchor.top > 50;
    HMONITOR mon = anchored ? MonitorFromRect(&anchor, MONITOR_DEFAULTTONEAREST)
                            : (p.freeMon ? p.freeMon : MonitorFromWindow(p.hwnd, MONITOR_DEFAULTTONEAREST));
    UINT dx = 96, dy = 96;
    GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &dx, &dy);
    if (p.dpi != dx) {
        p.dpi = dx;
        p.rt.Reset();
        InvalidatePopup();
    }
    MONITORINFO mi{};
    mi.cbSize = sizeof(mi);
    GetMonitorInfoW(mon, &mi);
    const RECT& wa = mi.rcWork;
    float sc = p.dpi / 96.0f;
    int margin = (int)std::lround(kMargin * sc);
    // As many rows as fit in the file list (or the screen), between 3 and 8.
    float roomDip = (anchored ? (anchor.bottom - anchor.top - 2 * margin) : (wa.bottom - wa.top) / 2) / sc;
    p.maxRows = Clamp((int)((roomDip - kListTop - kFootH - 6) / kRowH), kMinRows, kMaxRows);
    if (p.scroll > std::max(0, (int)p.rows.size() - p.maxRows)) p.scroll = std::max(0, (int)p.rows.size() - p.maxRows);
    int h = (int)std::lround(PopupHeightDip() * sc);
    int w, x, y;
    if (anchored) {
        int room = anchor.right - anchor.left - 2 * margin;
        w = std::max(std::min((int)std::lround(kPopW * sc), room), (int)std::lround(kPopMinW * sc));
        x = anchor.left + (anchor.right - anchor.left - w) / 2;
        y = g_settings.position == 1 ? anchor.bottom - margin - h : anchor.top + margin;
        // A file list narrower than the box (a narrow window with the folder tree open): the box
        // may cover the tree, but never hangs past the window's own edge (take 11).
        RECT frame{};
        if (p.target.top && (SUCCEEDED(DwmGetWindowAttribute(p.target.top, DWMWA_EXTENDED_FRAME_BOUNDS, &frame,
                                                             sizeof(frame))) ||
                             GetWindowRect(p.target.top, &frame))) {
            int frameRoom = frame.right - frame.left - 2 * margin;
            if (frameRoom > 0) w = std::min(w, std::max(frameRoom, (int)std::lround(200 * sc)));
            x = Clamp(x, (int)frame.left + margin, std::max((int)frame.left + margin, (int)frame.right - margin - w));
        }
    } else {
        w = (int)std::lround(kPopW * sc);
        x = wa.left + (wa.right - wa.left - w) / 2;
        y = wa.top + (wa.bottom - wa.top) / 4;
    }
    x = Clamp(x, (int)wa.left, std::max((int)wa.left, (int)wa.right - w));
    y = Clamp(y, (int)wa.top, std::max((int)wa.top, (int)wa.bottom - h));
    RECT cur;
    GetWindowRect(p.hwnd, &cur);
    if (cur.right - cur.left != w || cur.bottom - cur.top != h || cur.left != x || cur.top != y) {
        SetWindowPos(p.hwnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE);
        if (p.rt) p.rt->Resize(D2D1::SizeU(w, h));
    }
}

static void RunSearch() {
    Popup& p = g_pop;
    p.gen++;
    p.dirty = false;
    std::wstring q = Trim(p.query);
    if (q.empty()) {
        p.rows.clear();
        p.waiting = false;
        p.status = kEvOk;
        p.sel = p.scroll = 0;
        p.hover = -1;
    } else {
        p.waiting = true;
        EvQueryAsync(p.gen, p.hwnd, q, g_settings.thisFolderFirst ? p.target.folder : std::wstring());
    }
    PlacePopup();
    InvalidatePopup();
}

static void ResetCaret() {
    g_pop.caretOn = true;
    UINT blink = GetCaretBlinkTime();
    if (g_pop.hwnd) SetTimer(g_pop.hwnd, kTimerCaret, blink == INFINITE || blink == 0 ? 100000 : blink, nullptr);
}

static void BringForward(HWND hwnd) {
    // An empty SendInput makes this process the last input source, which SetForegroundWindow
    // asks for (the keyboard hook ate the key that opened the popup).
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
}

static void BringPopupForward() {
    HWND hwnd = g_pop.hwnd;
    BringForward(hwnd);
    SetActiveWindow(hwnd);
    SetFocus(hwnd);
}

// restoreFocus: hand the keyboard back to the Explorer window it came from.
static void HidePopup(bool restoreFocus) {
    Popup& p = g_pop;
    if (!p.hwnd || !p.visible) return;
    p.visible = false;  // First: hiding deactivates, and WM_ACTIVATE comes back here.
    g_popupFor = nullptr;
    p.gen++;
    p.folderPending = false;
    KillTimer(p.hwnd, kTimerCaret);
    KillTimer(p.hwnd, kTimerFolder);
    KillTimer(p.hwnd, kTimerWatch);
    KillTimer(p.hwnd, kTimerLost);
    // Hidden while it had the keyboard: Windows would activate the Explorer frame with no focused
    // child, and typing then went nowhere (take 8). Hand it back the way Esc does.
    if (GetForegroundWindow() == p.hwnd) restoreFocus = true;
    ShowWindow(p.hwnd, SW_HIDE);
    p.hover = -1;
    if (restoreFocus && p.target.top && IsWindow(p.target.top) && !IsIconic(p.target.top)) {
        BringForward(p.target.top);
        StartJob(kJobFocus, p.target, L"", L"");
    }
}

static void StartFirstSearch() {
    Popup& p = g_pop;
    if (Trim(p.query).empty()) return;
    if (p.folderPending) {
        p.waiting = true;
    } else if (g_settings.searchAsYouType) {
        RunSearch();
    } else {
        p.dirty = true;
    }
}

// Opens the popup for Explorer window `t` with `ch` typed (0: empty), or for no window.
static void ShowFor(const Target& t, wchar_t ch) {
    Popup& p = g_pop;
    if (!p.hwnd) return;
    p.target = t;
    p.query = ch ? std::wstring(1, ch) : std::wstring();
    p.rows.clear();
    p.status = kEvOk;
    p.waiting = false;
    p.dirty = false;
    p.sel = p.scroll = 0;
    p.hover = -1;
    p.gen++;
    p.openGen++;
    p.folderPending = false;
    p.regrabs = 0;
    p.lostByClick = false;
    p.shownAt = GetTickCount64();
    g_shownAt = p.shownAt;
    KillTimer(p.hwnd, kTimerFolder);
    KillTimer(p.hwnd, kTimerLost);
    if (!t.top) {
        POINT pt;
        GetCursorPos(&pt);
        p.freeMon = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    }
    // This folder first: the first search waits for the folder, at most kFolderWaitMs.
    if (g_settings.thisFolderFirst && t.top && StartJob(kJobFolder, t, L"", L"")) {
        p.folderPending = true;
        SetTimer(p.hwnd, kTimerFolder, kFolderWaitMs, nullptr);
    }
    p.glass = TransparencyOn() && SetGlass(p.hwnd, true, g_settings.popupOpacity);
    if (!p.glass) SetGlass(p.hwnd, false, 0);
    p.radius = WindowCornerRadiusDip();
    PlacePopup();
    p.visible = true;
    g_popupFor = t.top;
    ShowWindow(p.hwnd, SW_SHOW);
    BringPopupForward();
    ResetCaret();
    SetTimer(p.hwnd, kTimerWatch, kWatchMs, nullptr);
    StartFirstSearch();
    PlacePopup();
    DrawPopup();
}

// The hook saw a key in an Explorer file view (or Ctrl+F there): `focus` is the focused window.
static void OnExplorerType(HWND focus, wchar_t ch) {
    if (!focus || !IsWindow(focus)) return;
    HWND top = GetAncestor(focus, GA_ROOT);
    if (!ClassIs(top, L"CabinetWClass")) return;
    Popup& p = g_pop;
    if (p.visible && p.target.top == top) {
        if (ch && p.query.size() < 512) {
            p.query += ch;
            ResetCaret();
            if (p.folderPending) {
                p.waiting = true;
                PlacePopup();
                InvalidatePopup();
            } else if (g_settings.searchAsYouType) {
                RunSearch();
            } else {
                p.dirty = true;
                PlacePopup();
                InvalidatePopup();
            }
        }
        BringPopupForward();
        return;
    }
    Target t;
    t.top = top;
    t.tab = SelfOrAncestor(focus, L"ShellTabWindowClass", top);
    t.view = SelfOrAncestor(focus, L"SHELLDLL_DefView", top);
    if (!t.view) t.view = FindShownView(t.tab ? t.tab : top);
    if (!t.view) return;
    ShowFor(t, ch);
}

static void EnsureVisible() {
    Popup& p = g_pop;
    if (p.sel < p.scroll) p.scroll = p.sel;
    if (p.sel >= p.scroll + p.maxRows) p.scroll = p.sel - p.maxRows + 1;
    p.scroll = Clamp(p.scroll, 0, std::max(0, (int)p.rows.size() - p.maxRows));
}

enum OpenHow { kOpenDefault, kOpenReveal, kOpenNewWindow };

static void OpenRow(int i, int how) {
    Popup& p = g_pop;
    if (i < 0 || i >= (int)p.rows.size()) return;
    Row r = p.rows[i];
    Target t = p.target;
    HidePopup(true);
    bool inPlace = g_settings.sameWindow && t.top && IsWindow(t.top);
    if (!inPlace) t = Target{};
    if (how == kOpenReveal) {
        StartJob(kJobReveal, t, r.full, r.item.dir);
    } else if (r.item.folder) {
        StartJob(how == kOpenDefault && inPlace ? kJobNavigate : kJobLaunch, t, r.full, L"");
    } else {
        StartJob(kJobLaunch, t, r.full, r.item.dir);
    }
}

// ---------------------------------------------------------------------------
// Row actions: Tab opens a small menu for the selected row.
// ---------------------------------------------------------------------------

static void CopyTextToClipboard(HWND hwnd, const std::wstring& text) {
    if (!OpenClipboard(hwnd)) return;
    EmptyClipboard();
    size_t bytes = (text.size() + 1) * sizeof(wchar_t);
    HGLOBAL g = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (g) {
        void* p = GlobalLock(g);
        if (p) {
            memcpy(p, text.c_str(), bytes);
            GlobalUnlock(g);
            if (!SetClipboardData(CF_UNICODETEXT, g)) GlobalFree(g);
        } else {
            GlobalFree(g);
        }
    }
    CloseClipboard();
}

static void CopyFileToClipboard(HWND hwnd, const std::wstring& path) {
    if (!OpenClipboard(hwnd)) return;
    EmptyClipboard();
    size_t bytes = sizeof(DROPFILES) + (path.size() + 2) * sizeof(wchar_t);
    HGLOBAL g = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (g) {
        void* p = GlobalLock(g);
        if (p) {
            auto* df = (DROPFILES*)p;
            df->pFiles = sizeof(DROPFILES);
            df->fWide = TRUE;
            wchar_t* names = (wchar_t*)((BYTE*)p + sizeof(DROPFILES));
            memcpy(names, path.c_str(), (path.size() + 1) * sizeof(wchar_t));
            names[path.size() + 1] = 0;
            GlobalUnlock(g);
            if (!SetClipboardData(CF_HDROP, g)) GlobalFree(g);
        } else {
            GlobalFree(g);
        }
    }
    CloseClipboard();
}

enum { kActOpen = 1, kActReveal, kActNewWindow, kActCopyPath, kActCopyFile };

static void ShowActionsMenu() {
    Popup& p = g_pop;
    if (!p.hwnd || p.sel >= (int)p.rows.size()) return;
    int sel = p.sel;
    Row r = p.rows[sel];
    HMENU menu = CreatePopupMenu();
    if (!menu) return;
    AppendMenuW(menu, MF_STRING, kActOpen, L"Open");
    AppendMenuW(menu, MF_STRING, kActReveal, L"Show in folder");
    if (r.item.folder) AppendMenuW(menu, MF_STRING, kActNewWindow, L"Open in new window");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, kActCopyPath, L"Copy path");
    if (!r.item.folder) AppendMenuW(menu, MF_STRING, kActCopyFile, L"Copy file");
    // Drop the menu at the selected row's left edge, below the row.
    float rowTop = kListTop + (sel - p.scroll) * kRowH;
    POINT pt{(int)((kPad + 6) * p.dpi / 96.0f), (int)((rowTop + kRowH + 2) * p.dpi / 96.0f)};
    ClientToScreen(p.hwnd, &pt);
    SetForegroundWindow(p.hwnd);
    UINT cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON, pt.x, pt.y, p.hwnd, nullptr);
    PostMessageW(p.hwnd, WM_NULL, 0, 0);
    DestroyMenu(menu);
    // The popup may have closed while the menu was open.
    if (!p.visible || sel >= (int)p.rows.size()) return;
    switch (cmd) {
        case kActOpen: OpenRow(sel, kOpenDefault); break;
        case kActReveal: OpenRow(sel, kOpenReveal); break;
        case kActNewWindow: OpenRow(sel, kOpenNewWindow); break;
        case kActCopyPath: CopyTextToClipboard(p.hwnd, r.full); break;
        case kActCopyFile: CopyFileToClipboard(p.hwnd, r.full); break;
    }
}

static int RowAt(int ypx) {
    float y = ypx * 96.0f / g_pop.dpi;
    if (y < kListTop) return -1;
    int i = (int)((y - kListTop) / kRowH);
    if (i >= g_pop.maxRows) return -1;
    i += g_pop.scroll;
    return i < (int)g_pop.rows.size() ? i : -1;
}

static void EditQuery(const std::wstring& q) {
    Popup& p = g_pop;
    if (q == p.query) return;
    p.query = q;
    ResetCaret();
    if (p.folderPending) {
        p.waiting = !Trim(q).empty();
        PlacePopup();
        InvalidatePopup();
    } else if (g_settings.searchAsYouType || Trim(q).empty()) {
        RunSearch();
    } else {
        p.dirty = true;
        PlacePopup();
        InvalidatePopup();
    }
}

static void PasteQuery() {
    if (!OpenClipboard(g_pop.hwnd)) return;
    std::wstring text;
    if (HANDLE h = GetClipboardData(CF_UNICODETEXT)) {
        if (auto* s = (const wchar_t*)GlobalLock(h)) {
            text = s;
            GlobalUnlock(h);
        }
    }
    CloseClipboard();
    for (auto& c : text)
        if (c == L'\r' || c == L'\n' || c == L'\t') c = L' ';
    if (!text.empty()) EditQuery((g_pop.query + text).substr(0, 512));
}

static LRESULT CALLBACK PopupProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    Popup& p = g_pop;
    switch (msg) {
        case WM_LS_RESULTS: {
            std::unique_ptr<EvReply> r((EvReply*)lp);
            if (r->gen != p.gen || !p.visible) return 0;  // An older search.
            p.waiting = false;
            p.status = r->status;
            SetResults(std::move(r->items));
            PlacePopup();
            InvalidatePopup();
            return 0;
        }
        case WM_ES_FOLDER: {
            std::unique_ptr<std::wstring> folder((std::wstring*)lp);
            if ((DWORD)wp != p.openGen || !p.visible) return 0;
            p.target.folder = *folder;
            bool held = p.folderPending;
            p.folderPending = false;
            KillTimer(hwnd, kTimerFolder);
            // The held first search runs now; one that already ran everywhere runs again
            // with this folder first.
            if (!Trim(p.query).empty() && (held || !p.target.folder.empty())) {
                if (g_settings.searchAsYouType) {
                    RunSearch();
                } else if (held) {
                    p.waiting = false;
                    p.dirty = true;
                    InvalidatePopup();
                }
            }
            return 0;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            DrawPopup();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_ERASEBKGND:
            return 1;
        case WM_SIZE:
            if (p.rt) p.rt->Resize(D2D1::SizeU(LOWORD(lp), HIWORD(lp)));
            return 0;
        case WM_DPICHANGED:
            p.dpi = HIWORD(wp);
            p.rt.Reset();
            PlacePopup();
            return 0;
        case WM_ACTIVATE:
            if (LOWORD(wp) == WA_INACTIVE) {
                // Hiding waits a moment: right after the box opened, the keyboard was seen going
                // straight back to the Explorer window (live test, 2026-11-13).
                if (p.visible && g_settings.hideOnFocusLost) {
                    p.lostByClick = GetAsyncKeyState(VK_LBUTTON) < 0 || GetAsyncKeyState(VK_RBUTTON) < 0 ||
                                    GetAsyncKeyState(VK_MBUTTON) < 0;
                    SetTimer(hwnd, kTimerLost, kLostCheckMs, nullptr);
                }
            } else {
                KillTimer(hwnd, kTimerLost);
            }
            return 0;
        case WM_TIMER:
            if (wp == kTimerCaret) {
                p.caretOn = !p.caretOn;
                InvalidatePopup();
            } else if (wp == kTimerFolder) {
                // The folder lookup is slow: search everywhere now; a late folder searches again.
                KillTimer(hwnd, kTimerFolder);
                if (p.folderPending) {
                    p.folderPending = false;
                    p.waiting = false;
                    StartFirstSearch();
                    PlacePopup();
                    InvalidatePopup();
                }
            } else if (wp == kTimerLost) {
                KillTimer(hwnd, kTimerLost);
                HWND fg = GetForegroundWindow();
                if (!p.visible || fg == hwnd) return 0;
                if (!p.lostByClick && p.target.top && fg == p.target.top && p.regrabs < 2 &&
                    GetTickCount64() - p.shownAt < kRegrabMs) {
                    p.regrabs++;
                    Diag(L"focus bounced back, taken again", fg);
                    BringPopupForward();
                    return 0;
                }
                Diag(p.lostByClick ? L"closed, clicked away to" : L"closed, focus moved to", fg);
                HidePopup(false);
            } else if (wp == kTimerWatch && p.visible) {
                if (p.target.top) {
                    HWND top = p.target.top, view = p.target.view;
                    // Closed, minimised, or another tab or folder showing: the popup goes.
                    if (!IsWindow(top) || IsIconic(top) || !IsWindowVisible(top) || !ViewShown(view, p.target.tab)) {
                        Diag(!IsWindow(top)            ? L"closed, window gone"
                             : IsIconic(top)           ? L"closed, window minimised"
                             : !IsWindowVisible(top)   ? L"closed, window hidden"
                                                       : L"closed, folder view changed",
                             IsWindow(view) ? view : nullptr);
                        HidePopup(false);
                        return 0;
                    }
                    PlacePopup();
                }
                if (!g_settings.hideOnFocusLost) {
                    HWND fg = GetForegroundWindow();
                    DWORD pid = 0;
                    if (fg) GetWindowThreadProcessId(fg, &pid);
                    if (fg && fg != hwnd && GetAncestor(fg, GA_ROOT) != p.target.top && pid != GetCurrentProcessId()) {
                        Diag(L"closed, another app in front", fg);
                        HidePopup(false);
                    }
                }
            }
            return 0;
        case WM_KEYDOWN: {
            bool ctrl = GetKeyState(VK_CONTROL) < 0;
            int n = (int)p.rows.size();
            switch (wp) {
                case VK_ESCAPE:
                    HidePopup(true);
                    return 0;
                case VK_RETURN:
                    if (p.dirty || p.folderPending) {
                        if (p.folderPending) {
                            p.folderPending = false;
                            KillTimer(hwnd, kTimerFolder);
                        }
                        RunSearch();
                    } else {
                        OpenRow(p.sel, ctrl ? kOpenReveal : kOpenDefault);
                    }
                    return 0;
                case VK_DOWN:
                case VK_UP:
                    if (n) {
                        p.sel = (p.sel + (wp == VK_DOWN ? 1 : n - 1)) % n;
                        EnsureVisible();
                        InvalidatePopup();
                    }
                    return 0;
                case VK_NEXT:
                case VK_PRIOR:
                    if (n) {
                        p.sel = Clamp(p.sel + (wp == VK_NEXT ? p.maxRows : -p.maxRows), 0, n - 1);
                        EnsureVisible();
                        InvalidatePopup();
                    }
                    return 0;
                case VK_TAB:
                case VK_RIGHT:
                    if (n) ShowActionsMenu();
                    return 0;
            }
            break;
        }
        case WM_CHAR: {
            wchar_t c = (wchar_t)wp;
            if (c == 0x08) {  // Backspace; on an empty box it closes, like Esc.
                if (!p.query.empty()) EditQuery(p.query.substr(0, p.query.size() - 1));
                else HidePopup(true);
            } else if (c == 0x7F) {  // Ctrl+Backspace: the last word
                std::wstring q = p.query;
                while (!q.empty() && q.back() == L' ') q.pop_back();
                while (!q.empty() && q.back() != L' ') q.pop_back();
                EditQuery(q);
            } else if (c == 0x16) {  // Ctrl+V
                PasteQuery();
            } else if (c == 0x01) {  // Ctrl+A: start over
                EditQuery(L"");
            } else if (c >= 0x20 && p.query.size() < 512) {
                EditQuery(p.query + c);
            }
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (!p.tracking) {
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                p.tracking = TrackMouseEvent(&t) != FALSE;
            }
            int i = RowAt(GET_Y_LPARAM(lp));
            if (i != p.hover) {
                p.hover = i;
                InvalidatePopup();
            }
            return 0;
        }
        case WM_MOUSELEAVE:
            p.tracking = false;
            if (p.hover != -1) {
                p.hover = -1;
                InvalidatePopup();
            }
            return 0;
        case WM_LBUTTONUP: {
            int i = RowAt(GET_Y_LPARAM(lp));
            if (i >= 0) {
                p.sel = i;
                OpenRow(i, GetKeyState(VK_CONTROL) < 0 ? kOpenReveal : kOpenDefault);
            }
            return 0;
        }
        case WM_MOUSEWHEEL: {
            int delta = GET_WHEEL_DELTA_WPARAM(wp);
            int steps = -delta / WHEEL_DELTA;
            if (!steps) steps = delta < 0 ? 1 : -1;
            int maxScroll = std::max(0, (int)p.rows.size() - p.maxRows);
            int s = Clamp(p.scroll + steps, 0, maxScroll);
            if (s != p.scroll) {
                p.scroll = s;
                POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
                ScreenToClient(hwnd, &pt);
                p.hover = RowAt(pt.y);
                InvalidatePopup();
            }
            return 0;
        }
        case WM_MOUSEACTIVATE:
            return MA_ACTIVATE;
        case WM_CLOSE:
            HidePopup(false);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// ---------------------------------------------------------------------------
// Typing in Explorer: a low-level keyboard hook on its own thread. It eats a key only when
// a File Explorer window is in front with its file list focused (not the address bar, the
// search box or a name being edited), and only keys that type a character, or Explorer's
// own search keys. Everything else, and every key elsewhere, passes untouched.
// ---------------------------------------------------------------------------

static HANDLE g_hookThread;
static DWORD g_hookTid;
static HHOOK g_hook;
static bool g_eaten[256];  // Hook thread only: keys whose key-up is eaten too.

static bool IsModifierKey(DWORD vk) {
    switch (vk) {
        case VK_SHIFT: case VK_LSHIFT: case VK_RSHIFT: case VK_CONTROL: case VK_LCONTROL: case VK_RCONTROL:
        case VK_MENU: case VK_LMENU: case VK_RMENU: case VK_LWIN: case VK_RWIN: case VK_CAPITAL:
        case VK_NUMLOCK: case VK_SCROLL: case VK_APPS:
            return true;
    }
    return false;
}

static LRESULT CALLBACK ExplorerKeyProc(int code, WPARAM wp, LPARAM lp) {
    if (code != HC_ACTION) return CallNextHookEx(nullptr, code, wp, lp);
    auto* k = (KBDLLHOOKSTRUCT*)lp;
    DWORD vk = k->vkCode & 0xFF;
    if (wp == WM_KEYUP || wp == WM_SYSKEYUP) {
        if (g_eaten[vk]) {
            g_eaten[vk] = false;
            return 1;
        }
        return CallNextHookEx(nullptr, code, wp, lp);
    }
    if (wp != WM_KEYDOWN || IsModifierKey(vk)) return CallNextHookEx(nullptr, code, wp, lp);
    HWND msgWnd = g_hookMsg;
    // A UI thread that stopped answering never gets keys it can't show.
    if (!msgWnd || g_listaryUp || GetTickCount64() - g_uiBeat.load() > 3000) {
        if (msgWnd && GetTickCount64() - g_shownAt.load() < 3000) PostMessageW(msgWnd, WM_ES_DIAG, g_listaryUp ? 1 : 2, 0);
        return CallNextHookEx(nullptr, code, wp, lp);
    }
    HWND fg = GetForegroundWindow();
    if (!ClassIs(fg, L"CabinetWClass")) return CallNextHookEx(nullptr, code, wp, lp);
    DWORD tid = GetWindowThreadProcessId(fg, nullptr);
    GUITHREADINFO gti{};
    gti.cbSize = sizeof(gti);
    if (!GetGUIThreadInfo(tid, &gti) || !gti.hwndFocus ||
        (gti.flags & (GUI_INMENUMODE | GUI_POPUPMENUMODE | GUI_SYSTEMMENUMODE | GUI_INMOVESIZE)))
        return CallNextHookEx(nullptr, code, wp, lp);
    HWND focus = gti.hwndFocus;
    // The file list: DirectUIHWND (or SysListView32 in the classic view) right under the view.
    bool inView = (ClassIs(focus, L"DirectUIHWND") || ClassIs(focus, L"SysListView32")) &&
                  ClassIs(GetAncestor(focus, GA_PARENT), L"SHELLDLL_DefView");
    bool ctrl = GetAsyncKeyState(VK_CONTROL) < 0, alt = GetAsyncKeyState(VK_MENU) < 0,
         win = GetAsyncKeyState(VK_LWIN) < 0 || GetAsyncKeyState(VK_RWIN) < 0, shift = GetAsyncKeyState(VK_SHIFT) < 0;
    if (alt || win) return CallNextHookEx(nullptr, code, wp, lp);

    // Explorer's search keys: Ctrl+F, Ctrl+E and F3, from the file list or the folder tree.
    if (g_hookKeys && !shift && ((ctrl && (vk == 'F' || vk == 'E')) || (!ctrl && vk == VK_F3))) {
        bool inTree = ClassIs(focus, L"SysTreeView32") && SelfOrAncestor(focus, L"ShellTabWindowClass", fg);
        if (inView || inTree) {
            g_eaten[vk] = true;
            PostMessageW(msgWnd, WM_ES_TYPE, 0, (LPARAM)focus);
            return 1;
        }
    }
    if (!g_hookType || !inView || ctrl) {
        if (!inView && !ctrl && GetTickCount64() - g_shownAt.load() < 3000) PostMessageW(msgWnd, WM_ES_DIAG, 3, (LPARAM)focus);
        return CallNextHookEx(nullptr, code, wp, lp);
    }

    // The popup is open for this window but didn't get the keyboard: its keys go to it.
    if (g_hookForward && g_popupFor.load() == fg && !shift &&
        (vk == VK_UP || vk == VK_DOWN || vk == VK_PRIOR || vk == VK_NEXT || vk == VK_RETURN || vk == VK_ESCAPE ||
         vk == VK_BACK || vk == VK_TAB)) {
        g_eaten[vk] = true;
        PostMessageW(msgWnd, WM_ES_KEY, vk, 0);
        return 1;
    }

    // Only a key that types one visible character opens the search. Flag 4 keeps a
    // pending accent key in Explorer's layout state untouched.
    BYTE ks[256] = {};
    if (shift) ks[VK_SHIFT] = 0x80;
    GetKeyState(0);  // Syncs this thread's key state, so Caps Lock reads right.
    if (GetKeyState(VK_CAPITAL) & 1) ks[VK_CAPITAL] = 0x01;
    WCHAR buf[8] = {};
    int n = ToUnicodeEx(vk, k->scanCode, ks, buf, 8, 0x4, GetKeyboardLayout(tid));
    if (n != 1 || buf[0] < 0x21 || buf[0] == 0x7F) return CallNextHookEx(nullptr, code, wp, lp);
    g_eaten[vk] = true;
    PostMessageW(msgWnd, WM_ES_TYPE, buf[0], (LPARAM)focus);
    return 1;
}

static DWORD WINAPI HookThread(LPVOID ready) {
    MSG m;
    PeekMessageW(&m, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    memset(g_eaten, 0, sizeof(g_eaten));
    g_hook = SetWindowsHookExW(WH_KEYBOARD_LL, ExplorerKeyProc, (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle(), 0);
    SetEvent((HANDLE)ready);
    if (g_hook) {
        while (GetMessageW(&m, nullptr, 0, 0) > 0) DispatchMessageW(&m);
        UnhookWindowsHookEx(g_hook);
        g_hook = nullptr;
    }
    return 0;
}

static void StopHook() {
    if (!g_hookThread) return;
    PostThreadMessageW(g_hookTid, WM_QUIT, 0, 0);
    if (WaitForSingleObject(g_hookThread, 5000) != WAIT_OBJECT_0) Wh_Log(L"Keyboard thread did not stop in 5 s");
    CloseHandle(g_hookThread);
    g_hookThread = nullptr;
}

static void StartHook() {
    if (g_hookThread) return;
    HANDLE ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_hookThread = CreateThread(nullptr, 0, HookThread, ready, 0, &g_hookTid);
    if (g_hookThread) WaitForSingleObject(ready, 5000);
    CloseHandle(ready);
    if (g_hookThread && !g_hook) {
        Wh_Log(L"Couldn't watch the keyboard");
        StopHook();
    }
}

static void ApplyHook() {
    const Settings& s = g_settings;
    g_hookType = s.typeToSearch;
    g_hookKeys = s.searchKeys;
    g_hookForward = s.hideOnFocusLost;
    if (!g_paused && (s.typeToSearch || s.searchKeys)) StartHook();
    else StopHook();
}

// ---------------------------------------------------------------------------
// Tray
// ---------------------------------------------------------------------------

static UINT g_taskbarCreated;
static bool g_trayAdded;
static HICON g_trayIcon;

static void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)(void*)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)(void*)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// A rounded square in the blue to mauve gradient with the search glyph, drawn with GDI.
static HICON MakeTrayIcon(bool paused) {
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
    HFONT font = CreateFontW(-(int)(size * 0.62f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0,
                             L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    WCHAR face[64]{};
    GetTextFaceW(dc, 64, face);
    if (_wcsicmp(face, L"Segoe Fluent Icons") != 0) {
        SelectObject(dc, oldFont);
        DeleteObject(font);
        font = CreateFontW(-(int)(size * 0.62f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0,
                           L"Segoe MDL2 Assets");
        oldFont = SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)(paused ? 0xE769 : 0xE721), 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {paused ? 0x6C / 255.f : 0x89 / 255.f, paused ? 0x70 / 255.f : 0xB4 / 255.f,
                         paused ? 0x86 / 255.f : 0xFA / 255.f};
    const float c1[3] = {paused ? 0x58 / 255.f : 0xCB / 255.f, paused ? 0x5B / 255.f : 0xA6 / 255.f,
                         paused ? 0x70 / 255.f : 0xF7 / 255.f};
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

static void UpdateTray(bool add) {
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    if (!g_settings.settingsTrayIcon) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
        return;
    }
    bool resting = g_paused || g_listaryUp;
    HICON icon = MakeTrayIcon(resting);
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_LS_TRAY;
    nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    PCWSTR tip = g_paused      ? L"Seamless Explorer Search: paused"
                 : g_listaryUp ? L"Seamless Explorer Search: resting while Listary runs"
                               : L"Seamless Explorer Search: type in a folder to search";
    wcsncpy_s(nid.szTip, tip, _TRUNCATE);
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

static void ShowTrayMenu(POINT pt) {
    enum { IDM_SETTINGS = 1, IDM_PAUSE };
    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, IDM_SETTINGS, L"Settings");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING | (g_paused ? MF_CHECKED : 0), IDM_PAUSE, L"Pause typing to search");
    SetForegroundWindow(g_msgWnd);
    UINT cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON |
                                          (GetSystemMetrics(SM_MENUDROPALIGNMENT) ? TPM_RIGHTALIGN : TPM_LEFTALIGN),
                                pt.x, pt.y, g_msgWnd, nullptr);
    PostMessageW(g_msgWnd, WM_NULL, 0, 0);
    DestroyMenu(menu);
    if (cmd == IDM_SETTINGS) slset::OpenSettingsWindow();
    else if (cmd == IDM_PAUSE) {
        g_paused = !g_paused;
        Wh_SetIntValue(L"paused", g_paused ? 1 : 0);
        if (g_paused) HidePopup(false);
        ApplyHook();
        UpdateTray(false);
    }
}

// ---------------------------------------------------------------------------
// UI thread
// ---------------------------------------------------------------------------

static LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        g_trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    switch (msg) {
        case WM_COPYDATA: {
            // Automation channel for probes and scripts: 'SLQ' opens the popup (for no
            // Explorer window) with a query, 'SLK' presses a key on it, 'SLX' closes it.
            // UiThread lets it through the integrity filter.
            auto* cds = (COPYDATASTRUCT*)lp;
            if (!cds || !cds->lpData || cds->cbData < sizeof(wchar_t)) return FALSE;
            const wchar_t* d = (const wchar_t*)cds->lpData;
            int chars = (int)(cds->cbData / sizeof(wchar_t));
            if (cds->dwData == 0x00514C53) {  // 'SLQ'
                std::wstring q(d, chars);
                size_t z = q.find(L'\0');
                if (z != std::wstring::npos) q.resize(z);
                ShowFor(Target{}, 0);
                EditQuery(q);
                return TRUE;
            }
            if (cds->dwData == 0x004B4C53 && chars >= 1 && g_pop.hwnd) {  // 'SLK'
                PostMessageW(g_pop.hwnd, WM_KEYDOWN, (WPARAM)(wchar_t)d[0], 0);
                PostMessageW(g_pop.hwnd, WM_KEYUP, (WPARAM)(wchar_t)d[0], 0);
                return TRUE;
            }
            if (cds->dwData == 0x00584C53) {  // 'SLX'
                HidePopup(false);
                return TRUE;
            }
            return FALSE;
        }
        case WM_ES_TYPE:
            if (!g_paused) OnExplorerType((HWND)lp, (wchar_t)wp);
            return 0;
        case WM_ES_DIAG:
            Diag(wp == 1   ? L"key passed, Listary running"
                 : wp == 2 ? L"key passed, UI thread slow"
                           : L"key passed, focus not on the file list",
                 IsWindow((HWND)lp) ? (HWND)lp : nullptr);
            return 0;
        case WM_ES_KEY:
            if (g_pop.visible) {
                BringPopupForward();
                if (wp == VK_BACK) SendMessageW(g_pop.hwnd, WM_CHAR, 0x08, 0);
                else SendMessageW(g_pop.hwnd, WM_KEYDOWN, wp, 0);
            }
            return 0;
        case WM_TIMER:
            if (wp == kTimerBeat) {
                // The hook's sign of life, and every 10 s, whether Listary still runs: while it
                // does, it keeps typing in Explorer to itself.
                static int s_ticks;
                g_uiBeat = GetTickCount64();
                if (++s_ticks % 10 == 0) {
                    bool up = ListaryRunning();
                    if (up != g_listaryUp.load()) {
                        g_listaryUp = up;
                        if (up) Wh_Log(L"Listary.exe is running: typing in Explorer is left to it");
                        else Wh_Log(L"Listary.exe stopped: typing in Explorer searches again");
                        UpdateTray(false);
                    }
                }
            }
            return 0;
        case WM_LS_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    slset::OpenSettingsWindow();
                    break;
                case WM_CONTEXTMENU:
                    ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)});
                    break;
            }
            return 0;
        case WM_LS_SETTINGS:
            LoadSettings();
            ApplyHook();
            UpdateTray(false);
            if (g_pop.visible) RunSearch();
            if (HWND s = slset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* settings reload */, 0, 0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static HANDLE g_uiThread, g_uiReady;
static DWORD g_uiTid;

static DWORD WINAPI UiThread(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    EnableDarkMenus();
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), nullptr, (void**)g_d2d.put());
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)g_dw.put());
    CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void**)g_wic.put());
    g_inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    WNDCLASSW wc{};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = g_inst;
    wc.lpszClassName = kMsgClass;
    RegisterClassW(&wc);
    WNDCLASSW pc{};
    pc.lpfnWndProc = PopupProc;
    pc.hInstance = g_inst;
    pc.lpszClassName = kPopupClass;
    pc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassW(&pc);
    if (g_d2d && g_dw) {
        g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, kMsgClass, L"Seamless Explorer Search", WS_POPUP, 0, 0, 0, 0, nullptr,
                                   nullptr, g_inst, nullptr);
        g_pop.hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, kPopupClass, L"Seamless Explorer Search", WS_POPUP,
                                     -32000, -32000, 10, 10, nullptr, nullptr, g_inst, nullptr);
    }
    if (g_msgWnd && g_pop.hwnd) {
        // Probes and scripts run at a lower integrity than this service child; let their
        // WM_COPYDATA through (the automation channel in MsgWndProc).
        ChangeWindowMessageFilterEx(g_msgWnd, WM_COPYDATA, MSGFLT_ALLOW, nullptr);
        int corner = 2;  // Round.
        DwmSetWindowAttribute(g_pop.hwnd, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner, sizeof(corner));
        COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: the popup draws its own edge.
        DwmSetWindowAttribute(g_pop.hwnd, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));
        BOOL dark = TRUE;
        DwmSetWindowAttribute(g_pop.hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
        ImmAssociateContextEx(g_pop.hwnd, nullptr, 0);  // Plain keys: the hook hands over characters, not IME input.
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_msgWnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        MakeFormats();
        UpdateTray(true);
        g_uiBeat = GetTickCount64();
        SetTimer(g_msgWnd, kTimerBeat, 1000, nullptr);
        g_hookMsg = g_msgWnd;
        ApplyHook();
    }
    SetEvent(g_uiReady);
    if (g_msgWnd && g_pop.hwnd) {
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    g_hookMsg = nullptr;
    StopHook();
    if (g_msgWnd) KillTimer(g_msgWnd, kTimerBeat);
    if (g_pop.hwnd) {
        while (PeekMessageW(&msg, g_pop.hwnd, WM_LS_RESULTS, WM_LS_RESULTS, PM_REMOVE)) delete (EvReply*)msg.lParam;
        while (PeekMessageW(&msg, g_pop.hwnd, WM_ES_FOLDER, WM_ES_FOLDER, PM_REMOVE)) delete (std::wstring*)msg.lParam;
    }
    if (g_trayAdded) {
        NOTIFYICONDATAW nid{};
        nid.cbSize = sizeof(nid);
        nid.hWnd = g_msgWnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    g_pop.rt.Reset();
    g_pop.visible = false;
    g_popupFor = nullptr;
    if (g_pop.hwnd) DestroyWindow(g_pop.hwnd);
    g_pop.hwnd = nullptr;
    HWND w = g_msgWnd;
    g_msgWnd = nullptr;
    if (w) DestroyWindow(w);
    UnregisterClassW(kPopupClass, g_inst);
    UnregisterClassW(kMsgClass, g_inst);
    for (auto* f : {&g_fQuery, &g_fName, &g_fDir, &g_fHint, &g_fHintRight, &g_fGlyph, &g_fGlyphBig}) f->Reset();
    for (auto* e : {&g_ellName, &g_ellDir, &g_ellQuery, &g_ellHint}) e->Reset();
    // Every COM object goes before CoUninitialize: the WIC factory left for the static
    // destructors called into an unloaded windowscodecs.dll (crash on 1.1.0 unload, 8:30 am).
    g_bmps.clear();
    g_wic.Reset();
    g_dw.Reset();
    g_d2d.Reset();
    CoUninitialize();
    return 0;
}

// ---------------------------------------------------------------------------
// Start and stop
// ---------------------------------------------------------------------------

static HANDLE g_singleInstance;

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
constexpr INT kRowMargin = 8;                  // row top and bottom margin of the menu look
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

// Picks the largest row margin (8 down to 2) at which the whole menu fits its monitor.
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
        INT cut = px(2 * (kRowMargin - pick));   // rows measure 33 px and separators 21 px at margin 8
        if (rows * (px(33) - cut) + seps * (px(21) - cut) + px(10) <= avail) break;
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
    g_stopping = false;
    g_singleInstance = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessExplorerSearchRunning");
    if (!g_singleInstance || GetLastError() == ERROR_ALREADY_EXISTS) {
        if (g_singleInstance) CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
        SeamlessMenuSkin::Uninit();
        Wh_Log(L"Already running");
        return FALSE;
    }
    g_paused = Wh_GetIntValue(L"paused", 0) != 0;
    g_listaryUp = ListaryRunning();
    if (g_listaryUp) Wh_Log(L"Listary.exe is running: typing in Explorer is left to it");
    LoadSettings();
    if (!EvStart()) Wh_Log(L"Couldn't start the Everything client");
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThread, nullptr, 0, &g_uiTid);
    if (g_uiThread) WaitForSingleObject(g_uiReady, 10000);
    CloseHandle(g_uiReady);
    g_uiReady = nullptr;
    if (!g_uiThread || !g_msgWnd) {
        Wh_Log(L"Couldn't start");
        WhTool_ModUninit();
        return FALSE;
    }
    Wh_Log(L"Started%s", g_paused ? L" (typing paused)" : L"");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (HWND w = g_msgWnd) PostMessageW(w, WM_LS_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    g_stopping = true;
    SeamlessMenuSkin::Uninit();
    slset::CloseSettingsWindow();
    EvStop();
    if (g_uiThread) {
        PostThreadMessageW(g_uiTid, WM_QUIT, 0, 0);
        if (WaitForSingleObject(g_uiThread, 15000) != WAIT_OBJECT_0) Wh_Log(L"UI thread did not stop in 15 s");
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }
    if (g_singleInstance) {
        CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
    }
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-12-listary-port\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace slset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessExplorerSearchSettings";
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
    float fitW = 0;      // Box width that fits the text (Set_FitBoxes); 0 until measured.
    float fitText = -1;  // Measured text width behind fitW.
    std::wstring fitFor; // The text that was measured.
};

// Names, descriptions and option labels match the ==WindhawkModSettings== block word for word.
// Generated by work\2026-11-12-listary-port\build2.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Check, L"typeToSearch", L"Type to search", L"Start typing in a folder's file list and the search box opens with what you typed.", L"1", {}, 0, 100, 0, L"In Explorer windows"},
{K::Check, L"searchKeys", L"Take over Ctrl+F, Ctrl+E and F3", L"These keys open this search box instead of the Windows search box.", L"1", {}, 0, 100, 0, L"In Explorer windows"},
{K::Check, L"sameWindow", L"Open folders in the same window", L"Enter on a folder goes there in the window you searched from. Off, it opens a new window.", L"1", {}, 0, 100, 0, L"In Explorer windows"},
{K::Choice, L"position", L"Search box position", L"Where the box sits inside the folder window.", L"top", {{L"top", L"Top of the folder"}, {L"bottom", L"Bottom of the folder"}}, 0, 100, 0, L"In Explorer windows"},
{K::Check, L"hideOnFocusLost", L"Hide when focus is lost", L"The search box closes when you click somewhere else.", L"1", {}, 0, 100, 0, L"Behaviour"},
{K::Check, L"searchAsYouType", L"Search as you type", L"Results update on every keystroke. Off, press Enter to search.", L"1", {}, 0, 100, 0, L"Behaviour"},
{K::Number, L"resultLimit", L"Result limit", L"10 to 200 results kept (Suggested: 60).", L"60", {}, 10, 200, 1, L"Everything"},
{K::Number, L"queryTimeoutMs", L"Query timeout (ms)", L"50 to 1000 (Suggested: 200). A stuck query is dropped after this, so Explorer never waits on it.", L"200", {}, 50, 1000, 1, L"Everything"},
{K::Check, L"matchPath", L"Search in paths too", L"Match folder names in the full path, not just the file name.", L"0", {}, 0, 100, 1, L"Everything"},
{K::Check, L"thisFolderFirst", L"This folder first", L"Matches inside the folder you are in, and the folders below it, sit above the rest.", L"1", {}, 0, 100, 1, L"Ranking"},
{K::Check, L"fuzzyRanking", L"Smart ranking", L"Start-of-name and word matches beat matches in the middle.", L"1", {}, 0, 100, 1, L"Ranking"},
{K::Color, L"accentColor", L"Accent color", L"Tints the selection, the sliders and the hover gradient start.", L"#89B4FA", {}, 0, 100, 2, L"Search box"},
{K::Number, L"popupOpacity", L"Search box opacity", L"How solid the glass is, 50 to 100 percent. 85 matches File Explorer (Suggested: 85).", L"85", {}, 50, 100, 2, L"Search box"},
{K::Check, L"animations", L"Animations", L"Off, everything appears and closes with no movement.", L"1", {}, 0, 100, 2, L"Search box"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 2, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 2, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it for settings, right-click it for the menu.", L"1", {}, 0, 100, 2, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"General", L"How the search box opens inside File Explorer and how it behaves.", 0xE713},
{L"Search", L"Everything does the indexing; the mod shapes the results.", 0xE721},
{L"Appearance", L"The search box look and this settings window.", 0xE790},
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
// "Explorer Search" is longer than the template's name: the open sidebar never gets narrower than
// the name needs at full size (15 cells of Fira Code at 18 DIP is 162, plus the 100 beside it).
constexpr float kSearchRailMin = 264;
// A row whose control leaves the label less than this stacks: label on top, control below it.
constexpr float kSearchStackText = 150;
static bool SearchRowStacked(float rowW, float controlW) { return rowW - 2 * kSetRowPad - controlW - 24 < kSearchStackText; }
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
constexpr PCWSTR kSetDittoUrl = L"https://www.listary.com";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Explorer%20Search%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Explorer Search";
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
    int dropHover = -1, dropTop = 0;  // dropTop: first option shown when the dropdown scrolls.
    bool frameApplied = false;        // Set_ApplyFrame has run once.
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
    const float railW = kSearchRailMin - 90 - 10;
    for (float size = 18; size >= 15.5f; size -= 0.5f) {
        w.fRailName = Set_Fmt(w.family, size, bold, false, L_, true);
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Explorer Search") <= railW) break;
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
    return !w.render && g_settings.animations && on;
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
    if (SearchRowStacked(row.right - row.left, Set_ControlW(f))) mid = row.bottom - 14 - h;  // Below the label.
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

// The About page cards grow with their text, so nothing clips at any width.
constexpr PCWSTR kSearchAboutTitle = L"Seamless Explorer Search";
constexpr PCWSTR kSearchAboutDesc = L"Fast search for every File Explorer window, on the Everything index.";
constexpr PCWSTR kSearchAboutMade = L"Made by DavidHiFi. Inspired by Listary by Bopsoft, runs on the Everything index.";

static std::wstring SearchAboutVersion() {
#ifdef WH_MOD_VERSION
    return std::wstring(L"Version ") + WH_MOD_VERSION + L"  ·  MIT license  ·  A Windhawk mod";
#else
    return L"MIT license  ·  A Windhawk mod";
#endif
}

struct SearchAboutGeo {
    float textW = 0, titleH = 0, verH = 0, descH = 0, madeH = 0, h = 0;
    bool splitTitle = false;  // "Seamless" over "Explorer Search" when the one line does not fit.
};

static SearchAboutGeo SearchAboutLayout(const SetWindow& w) {
    SearchAboutGeo g;
    g.textW = w.contentW - 20 - 72 - 20 - 16;
    g.splitTitle = Set_TextW(w.fBig.get(), kSearchAboutTitle) > g.textW;
    g.titleH = g.splitTitle ? 54 : 28;
    g.verH = Set_TextH(w.fHint.get(), SearchAboutVersion(), g.textW);
    g.descH = Set_TextH(w.fHint.get(), kSearchAboutDesc, g.textW);
    g.madeH = Set_TextH(w.fHint.get(), kSearchAboutMade, g.textW);
    g.h = std::max(112.0f, 18 + g.titleH + 2 + g.verH + 6 + g.descH + 4 + g.madeH + 16);
    return g;
}

// The Ko-fi card's text column (the button takes the right 180).
static float SearchSupportTextW(const SetWindow& w) { return w.contentW - kSetRowPad - 180; }

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
        bool stacked = SearchRowStacked(w.contentW, Set_ControlW(f));
        float textW = w.contentW - 2 * kSetRowPad - (stacked ? 0 : Set_ControlW(f) + 24);
        float lh = Set_TextH(w.fLabel.get(), f.label, textW);
        float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = stacked ? 28 + lh + dh + 12 + kSetBoxH : std::max(kSetRowMin, 28 + lh + dh);
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
        // Link rows: label on top (one line), the hint wraps below it and the row grows to fit.
        auto link = [&](PCWSTR text, PCWSTR sub, PCWSTR url) {
            float hh = Set_TextH(w.fHint.get(), sub, w.contentW - kSetRowPad - 50);
            add(SetItem::Link, std::max(56.0f, 30 + hh + 10), text, sub, url);
        };
        add(SetItem::About, SearchAboutLayout(w).h, L"", L"", L"");
        {
            PCWSTR text = L"Like it? Help the mod keep going.", sub = L"Free and open source. A tip on Ko-fi keeps it moving.";
            float tw = SearchSupportTextW(w);
            float lh = Set_TextH(w.fLabel.get(), text, tw), dh = Set_TextH(w.fHint.get(), sub, tw);
            add(SetItem::Support, std::max(84.0f, 14 + lh + 4 + dh + 14), text, sub, kSetKofiUrl);
        }
        group(L"Author");
        link(L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        link(L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        link(L"Inspired by Listary by Bopsoft", L"The app that set the bar for this one", kSetDittoUrl);
        group(L"Project");
        link(L"Project page on GitHub", L"github.com/DavidHiFi/davids-windhawk-mods", kSetRepoUrl);
        link(L"Report a problem", L"Opens a new issue on GitHub, with the mod's name filled in", kSetBugUrl);
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
constexpr UINT32 kSetBoxFill = 0x232434;

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

static void Set_DrawBox(SetPaint& p, SetWindow& w, int k, const D2D1_RECT_F& box, bool active) {
    p.Round(box, 8, mocha::crust);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.GradRing(box, 8, g);
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

    bool stacked = SearchRowStacked(row.right - row.left, Set_ControlW(f));
    float textW = w.contentW - 2 * kSetRowPad - (stacked ? 0 : Set_ControlW(f) + 24);
    float lh = Set_TextH(w.fLabel.get(), f.label, textW);
    float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = stacked ? row.top + 14 : row.top + (it.h - lh - dh) / 2;
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
    Set_DrawCard(p, row, 0);
    float tw = SearchSupportTextW(w);
    float lh = Set_TextH(w.fLabel.get(), it.text, tw), dh = Set_TextH(w.fHint.get(), it.sub, tw);
    float top = row.top + (row.bottom - row.top - lh - 4 - dh) / 2;
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, top, row.right - 180, top + lh + 2}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, top + lh + 4, row.right - 180, top + lh + 4 + dh + 2},
           mocha::subtext0);
    D2D1_RECT_F b = Set_SupportButton(w, it);
    float hov = Set_GlowOf(w, 3500 + idx);
    p.GradFill(b, 8, 0.85f + 0.15f * hov);
    p.GradRing(b, 8, hov, 2);
    p.Text(w.fButton.get(), L"Open Ko-fi", b, mocha::crust);
}

static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    Set_DrawCard(p, row, 0);
    D2D1_RECT_F mark{row.left + 20, row.top + 20, row.left + 92, row.top + 92};
    p.GradFill(mark, 18, 1);
    p.Glyph(w.fIconL.get(), 0xE721, mark, mocha::crust);
    float x = mark.right + 20, r = row.right - 16, y = row.top + 18;
    SearchAboutGeo g = SearchAboutLayout(w);
    if (g.splitTitle) {
        p.Text(w.fBig.get(), L"Seamless", {x, y, r, y + 27}, mocha::text);
        p.Text(w.fBig.get(), L"Explorer Search", {x, y + 27, r, y + 54}, mocha::text);
    } else {
        p.Text(w.fBig.get(), kSearchAboutTitle, {x, y, r, y + 28}, mocha::text);
    }
    y += g.titleH + 2;
    p.Text(w.fHint.get(), SearchAboutVersion(), {x, y, r, y + g.verH + 2}, mocha::subtext0);
    y += g.verH + 6;
    p.Text(w.fHint.get(), kSearchAboutDesc, {x, y, r, y + g.descH + 2}, mocha::subtext1);
    y += g.descH + 4;
    p.Text(w.fHint.get(), kSearchAboutMade, {x, y, r, y + g.madeH + 2}, mocha::overlay2);
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
    Set_DrawDock(p, w, d, 14, w.glass ? 0.58f : 1.0f, std::max(w.railGlow, w.dragRail ? 1.0f : 0.0f) * 0.85f);

    // Drag handle: a thin gradient line on the dock's right edge while it is grabbed or pointed at.
    float edge = std::max(Set_GlowOf(w, 41), w.dragRail ? 1.0f : 0.0f);
    if (edge > 0.003f) p.GradFill({d.right - 1.5f, d.top + 18, d.right + 1.5f, d.bottom - 18}, 1.5f, edge);

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
    p.Text(w.fRailName.get(), L"Explorer Search", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    Set_DrawDock(p, w, d, rad, w.glass ? 0.9f : 1.0f, w.footGlow);
    UINT32 sc;
    std::wstring status = Set_FooterStatus(w, &sc);
    float sw = Set_FooterStatusW(w);
    if (sw > 0) p.Text(w.fStatusLine.get(), status, {d.left + 18, d.top, d.left + 18 + sw, d.bottom}, sc);
    static const PCWSTR names[3] = {L"Reset to suggested", L"Cancel", L"Save"};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_FooterButton(w, i);
        float hov = Set_GlowOf(w, 10 + i);
        if (i == 2) {
            p.GradFill(b, brad, 0.88f + 0.12f * hov);
            p.GradRing(b, brad, hov, 2);
            p.Text(w.fButton.get(), names[i], b, mocha::crust, w.saving ? 0.5f : 1.0f);
        } else {
            p.Round(b, brad, mocha::surface0, 0.6f);
            p.GradFill(b, brad, 0.12f * hov);
            p.GradRing(b, brad, 0.85f * hov);
            p.Text(w.fButton.get(), names[i], b, mocha::text);
        }
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
    p.Glyph(glyph, 0xE721, r, mocha::crust);
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

    rt->PushAxisAlignedClip(D2D1::RectF(Set_RailSpace(w) + 4, 0, w.cw, viewH), D2D1_ANTIALIAS_MODE_ALIASED);
    auto place = [&](int index, float& rise) {
        float t = w.pageT >= 1 ? 1.0f : Set_Ease(w.pageT * 1.7f - std::min(index, 9) * 0.07f);
        p.fade = t;
        rise = (1 - t) * 10;
        rt->SetTransform(D2D1::Matrix3x2F::Translation(0, -w.scrollY + rise) * base);
    };
    float rise = 0;
    place(0, rise);
    p.Text(w.fTitle.get(), kSetPages[w.page].name, {w.contentX, 36, w.contentX + w.contentW, 72}, mocha::text);
    place(1, rise);
    p.Text(w.fIntro.get(), kSetPages[w.page].intro, {w.contentX, 76, w.contentX + w.contentW, 76 + 40}, mocha::subtext0);
    for (size_t i = 0; i < w.items.size(); i++) {
        const SetItem& it = w.items[i];
        if (it.y + it.h < w.scrollY - 20 || it.y > w.scrollY + viewH + 20) continue;
        place((int)i + 2, rise);
        switch (it.type) {
            case SetItem::Group: Set_DrawGroup(p, w, it); break;
            case SetItem::Row: Set_DrawRow(p, w, it); break;
            case SetItem::Banner: Set_DrawBanner(p, w, it); break;
            case SetItem::About: Set_DrawAbout(p, w, it); break;
            case SetItem::Link: Set_DrawLinkRow(p, w, it, (int)i); break;
            case SetItem::Support: Set_DrawSupport(p, w, it, (int)i); break;
        }
    }
    p.fade = 1;
    rt->SetTransform(base);
    rt->PopAxisAlignedClip();

    D2D1_RECT_F th = Set_ScrollThumb(w);
    Set_ThumbFill(p, th, w.dragScroll || w.hover.kind == SetHit::Scroll ? 1.0f : 0.7f);

    Set_DrawFooter(p, w);
    Set_DrawRail(p, w);
    Set_DrawPopup(p, w);
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (false) p.GradRing({0, 0, w.cw, w.ch + kSetCapH}, SystemCornerRadius(false), 1, 1);
    HRESULT hr = rt->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) w.rt.reset();
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
            if (Set_In(Set_SupportButton(w, it), x, cy)) {
                h.kind = SetHit::Link;
                h.a = (int)i;
                h.id = 3500 + (int)i;
            }
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
        w.railW = std::clamp(width, kSearchRailMin, kSetRailMax);
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
    std::wstring text;
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
    w->editBrush = CreateSolidBrush(RefFromRgb(mocha::crust));
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Explorer Search settings", style,
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
        w->railW = std::clamp((float)GetState(StateKey(L"Settings", L"RailW").c_str(), (int)kSetRailDef), kSearchRailMin, kSetRailMax);
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
}  // namespace slset
