// ==WindhawkMod==
// @id              seamless-download-manager
// @name            Seamless Download Manager
// @description     A fast tray download manager: downloads in parts, resumes where it stopped, takes browser links
// @version         1.0.10
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/seamless-download-manager
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
# Seamless Download Manager

The Windhawk version of [Seamless Download Manager](https://github.com/DavidHiFi/seamless-download-manager),
a fast download manager for Windows written in Rust. Downloads split into
parts, pick up where they stopped, and come straight from your browser. This
mod runs the same download engine as the standalone app, inside Windhawk, so
there is no extra program to start with Windows.

![Seamless Download Manager](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-download-manager.png)

## How to use

- Click the tray icon to open the download list. Close the window and it
  goes back to the tray; downloads keep running.
- Add a link with **Add link**, or many at once with **Add many**. Links you
  copy are filled in for you.
- The browser extension sends downloads here by itself.
- Right-click the tray icon to add a link, pause or resume everything, open
  the settings, or stop the download engine.

## The download engine

The engine is a small file Seamless Workshop sets up for you (Extras, or by
itself when this mod is installed). If it is missing, the download window
offers to get it from the app's GitHub release, checked against its
published checksum.

The mod and the standalone app share one download list. Only one of them can
run the engine at a time, so close the app from its tray icon before you use
the mod. The first time the mod starts, it stops the app from starting with
Windows.

## Settings

Everything the app can set is in the mod's own settings window: where files
go, connections, speed limit, the browser link, name lookup, sounds, site
rules and queues. This page only holds how the windows look.

## What's new in 1.0.10

- Moves to engine 0.1.3, which no longer carries the AB Download Manager import.
  Your downloads, queues and settings stay as they are.
- Title bar menus get the same blurred Mocha body as every other menu again. They
  showed pitch black because the part that spots new menus stopped right after start.

## Credits

Built on the ideas of [AB Download Manager](https://github.com/amir1376/ab-download-manager)
by Amir Ali Ghaffari, shared under the Apache 2.0 licence. Every line here is
new, but the features and the care come from that project. Colors from
Catppuccin Mocha (https://github.com/catppuccin/catppuccin). Made by
DavidHiFi, released under GPL-3.0.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- settingsGlass: true
  $name: "Blurred windows"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it to open your downloads. Right-click it for more. When off, closing the window keeps downloads running and your browser can still open it."
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

#include <commdlg.h>
#include <shobjidl.h>
#include <urlmon.h>
#include <wincrypt.h>

#include <deque>
#include <functional>
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
int ShowTrayMenu(HWND owner, const POINT* at, bool on, PCWSTR hotkey);
extern std::atomic<HWND> g_settingsWnd;
}  // namespace acset

namespace sdm {
constexpr WCHAR kEngineVersion[] = L"0.1.3";
constexpr PCWSTR kAppRepo = L"https://github.com/DavidHiFi/seamless-download-manager";
constexpr PCWSTR kAbRepo = L"https://github.com/amir1376/ab-download-manager";
struct PageLink {
    int page;
    PCWSTR after;  // Shown after this field. nullptr: before the fields. L"": after them all.
    PCWSTR group;
    PCWSTR url;
};
std::vector<const PageLink*> LinksFor(int page, PCWSTR after);
// The settings window's link to the download engine (sdm_app.inc).
std::wstring LinkText(PCWSTR url, bool sub);
void LinkAction(PCWSTR url);
std::vector<std::pair<std::wstring, std::wstring>> LoadSettings();
bool SaveSettings(const std::vector<std::pair<std::wstring, std::wstring>>& vals, const std::vector<std::wstring>& changed,
                  std::wstring& err);
std::wstring BannerText();
int TakeStartPage();
}  // namespace sdm

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

// ---------------------------------------------------------------------------------------------
// A small JSON reader and writer for the engine's replies. UTF-8 text in, UTF-8 text out.
// ---------------------------------------------------------------------------------------------
namespace sj {

struct Val {
    enum Type { Null, Bool, Num, Str, Arr, Obj } t = Null;
    bool b = false;
    double n = 0;
    bool isInt = false;
    int64_t i = 0;
    std::string s;
    std::vector<Val> a;
    std::vector<std::pair<std::string, Val>> o;

    static const Val& None() {
        static const Val none;
        return none;
    }
    bool null() const { return t == Null; }
    const Val& operator[](const char* key) const {
        if (t == Obj)
            for (auto& kv : o)
                if (kv.first == key) return kv.second;
        return None();
    }
    const Val& operator[](size_t k) const { return t == Arr && k < a.size() ? a[k] : None(); }
    bool has(const char* key) const {
        if (t == Obj)
            for (auto& kv : o)
                if (kv.first == key) return true;
        return false;
    }
    size_t size() const { return t == Arr ? a.size() : t == Obj ? o.size() : 0; }
    int64_t num(int64_t def = 0) const {
        if (t == Num) return isInt ? i : (int64_t)n;
        if (t == Bool) return b ? 1 : 0;
        return def;
    }
    double dbl(double def = 0) const { return t == Num ? (isInt ? (double)i : n) : def; }
    bool truthy(bool def = false) const { return t == Bool ? b : t == Num ? num() != 0 : def; }
    const std::string& str() const {
        static const std::string empty;
        return t == Str ? s : empty;
    }
    Val& set(const char* key, Val v) {
        if (t != Obj) {
            t = Obj;
            o.clear();
        }
        for (auto& kv : o)
            if (kv.first == key) {
                kv.second = std::move(v);
                return kv.second;
            }
        o.emplace_back(key, std::move(v));
        return o.back().second;
    }
    void push(Val v) {
        if (t != Arr) {
            t = Arr;
            a.clear();
        }
        a.push_back(std::move(v));
    }
};

inline Val Int(int64_t v) {
    Val x;
    x.t = Val::Num;
    x.isInt = true;
    x.i = v;
    x.n = (double)v;
    return x;
}
inline Val Dbl(double v) {
    Val x;
    x.t = Val::Num;
    x.n = v;
    return x;
}
inline Val Bool(bool v) {
    Val x;
    x.t = Val::Bool;
    x.b = v;
    return x;
}
inline Val Str(std::string v) {
    Val x;
    x.t = Val::Str;
    x.s = std::move(v);
    return x;
}
inline Val Arr() {
    Val x;
    x.t = Val::Arr;
    return x;
}
inline Val Obj() {
    Val x;
    x.t = Val::Obj;
    return x;
}

struct Reader {
    const char* p;
    const char* end;
    int depth = 0;
    void ws() {
        while (p < end && (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')) p++;
    }
    bool lit(const char* w) {
        size_t n = strlen(w);
        if ((size_t)(end - p) < n || memcmp(p, w, n) != 0) return false;
        p += n;
        return true;
    }
    static void put(std::string& out, uint32_t cp) {
        if (cp < 0x80) {
            out += (char)cp;
        } else if (cp < 0x800) {
            out += (char)(0xC0 | (cp >> 6));
            out += (char)(0x80 | (cp & 0x3F));
        } else if (cp < 0x10000) {
            out += (char)(0xE0 | (cp >> 12));
            out += (char)(0x80 | ((cp >> 6) & 0x3F));
            out += (char)(0x80 | (cp & 0x3F));
        } else {
            out += (char)(0xF0 | (cp >> 18));
            out += (char)(0x80 | ((cp >> 12) & 0x3F));
            out += (char)(0x80 | ((cp >> 6) & 0x3F));
            out += (char)(0x80 | (cp & 0x3F));
        }
    }
    bool hex4(uint32_t& v) {
        if (end - p < 4) return false;
        v = 0;
        for (int k = 0; k < 4; k++) {
            char c = *p++;
            v <<= 4;
            if (c >= '0' && c <= '9') v |= c - '0';
            else if (c >= 'a' && c <= 'f') v |= c - 'a' + 10;
            else if (c >= 'A' && c <= 'F') v |= c - 'A' + 10;
            else return false;
        }
        return true;
    }
    bool string(std::string& out) {
        if (p >= end || *p != '"') return false;
        p++;
        while (p < end && *p != '"') {
            char c = *p++;
            if (c != '\\') {
                out += c;
                continue;
            }
            if (p >= end) return false;
            char e = *p++;
            switch (e) {
                case '"': out += '"'; break;
                case '\\': out += '\\'; break;
                case '/': out += '/'; break;
                case 'b': out += '\b'; break;
                case 'f': out += '\f'; break;
                case 'n': out += '\n'; break;
                case 'r': out += '\r'; break;
                case 't': out += '\t'; break;
                case 'u': {
                    uint32_t cp;
                    if (!hex4(cp)) return false;
                    if (cp >= 0xD800 && cp < 0xDC00 && end - p >= 6 && p[0] == '\\' && p[1] == 'u') {
                        p += 2;
                        uint32_t lo;
                        if (!hex4(lo)) return false;
                        cp = 0x10000 + ((cp - 0xD800) << 10) + (lo - 0xDC00);
                    }
                    put(out, cp);
                    break;
                }
                default: return false;
            }
        }
        if (p >= end) return false;
        p++;
        return true;
    }
    bool value(Val& v) {
        if (++depth > 64) return false;
        ws();
        if (p >= end) return false;
        bool ok = true;
        if (*p == '{') {
            p++;
            v.t = Val::Obj;
            ws();
            if (p < end && *p == '}') {
                p++;
            } else {
                for (;;) {
                    ws();
                    std::string key;
                    if (!string(key)) return false;
                    ws();
                    if (p >= end || *p != ':') return false;
                    p++;
                    Val child;
                    if (!value(child)) return false;
                    v.o.emplace_back(std::move(key), std::move(child));
                    ws();
                    if (p < end && *p == ',') {
                        p++;
                        continue;
                    }
                    if (p < end && *p == '}') {
                        p++;
                        break;
                    }
                    return false;
                }
            }
        } else if (*p == '[') {
            p++;
            v.t = Val::Arr;
            ws();
            if (p < end && *p == ']') {
                p++;
            } else {
                for (;;) {
                    Val child;
                    if (!value(child)) return false;
                    v.a.push_back(std::move(child));
                    ws();
                    if (p < end && *p == ',') {
                        p++;
                        continue;
                    }
                    if (p < end && *p == ']') {
                        p++;
                        break;
                    }
                    return false;
                }
            }
        } else if (*p == '"') {
            v.t = Val::Str;
            ok = string(v.s);
        } else if (lit("true")) {
            v.t = Val::Bool;
            v.b = true;
        } else if (lit("false")) {
            v.t = Val::Bool;
        } else if (lit("null")) {
            v.t = Val::Null;
        } else {
            const char* start = p;
            bool frac = false;
            if (p < end && (*p == '-' || *p == '+')) p++;
            while (p < end && ((*p >= '0' && *p <= '9') || *p == '.' || *p == 'e' || *p == 'E' || *p == '-' || *p == '+')) {
                if (*p == '.' || *p == 'e' || *p == 'E') frac = true;
                p++;
            }
            if (p == start) return false;
            std::string text(start, p);
            v.t = Val::Num;
            v.n = strtod(text.c_str(), nullptr);
            if (!frac) {
                v.isInt = true;
                v.i = _strtoi64(text.c_str(), nullptr, 10);
            }
        }
        depth--;
        return ok;
    }
};

inline Val Parse(const char* text) {
    Val v;
    if (!text) return v;
    Reader r{text, text + strlen(text)};
    if (!r.value(v)) return Val();
    return v;
}

inline void DumpStr(std::string& out, const std::string& s) {
    out += '"';
    for (unsigned char c : s) {
        switch (c) {
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (c < 0x20) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "\\u%04x", c);
                    out += buf;
                } else {
                    out += (char)c;
                }
        }
    }
    out += '"';
}

inline void Dump(std::string& out, const Val& v) {
    switch (v.t) {
        case Val::Null: out += "null"; break;
        case Val::Bool: out += v.b ? "true" : "false"; break;
        case Val::Num: {
            char buf[40];
            if (v.isInt) snprintf(buf, sizeof(buf), "%lld", (long long)v.i);
            else snprintf(buf, sizeof(buf), "%.17g", v.n);
            out += buf;
            break;
        }
        case Val::Str: DumpStr(out, v.s); break;
        case Val::Arr:
            out += '[';
            for (size_t k = 0; k < v.a.size(); k++) {
                if (k) out += ',';
                Dump(out, v.a[k]);
            }
            out += ']';
            break;
        case Val::Obj:
            out += '{';
            for (size_t k = 0; k < v.o.size(); k++) {
                if (k) out += ',';
                DumpStr(out, v.o[k].first);
                out += ':';
                Dump(out, v.o[k].second);
            }
            out += '}';
            break;
    }
}

inline std::string Dump(const Val& v) {
    std::string out;
    Dump(out, v);
    return out;
}

inline std::string U8(const std::wstring& w) {
    if (w.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), s.data(), n, nullptr, nullptr);
    return s;
}

inline std::wstring W(const std::string& s) {
    if (s.empty()) return {};
    int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring w(n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), w.data(), n);
    return w;
}

inline Val WStr(const std::wstring& w) { return Str(U8(w)); }

}  // namespace sj

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

static HMODULE g_hookSelf = nullptr;
static HANDLE g_hookThread = nullptr, g_hookReady = nullptr;
static DWORD g_hookThreadId = 0;
static DWORD WINAPI HookThreadProc(LPVOID)
{
    MSG m;
    PeekMessageW(&m, nullptr, 0, 0, PM_NOREMOVE);  // a queue, so WM_QUIT can reach this thread
    DWORD pid = GetCurrentProcessId();
    g_createHook = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_CREATE, g_hookSelf, OnEvent, pid, 0, WINEVENT_INCONTEXT);
    g_menuHook = SetWinEventHook(EVENT_SYSTEM_MENUSTART, EVENT_SYSTEM_MENUEND, g_hookSelf, OnEvent, pid, 0, WINEVENT_INCONTEXT);
    if (g_hookReady) SetEvent(g_hookReady);
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {}
    for (HWINEVENTHOOK* hk : {&g_createHook, &g_menuHook})
        if (*hk) { UnhookWinEvent(*hk); *hk = nullptr; }
    return 0;
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
    g_hookSelf = self;
    // Tool mods run init on the main thread, which exits right after, and Windows drops a
    // thread's event hooks when it ends. Keep them on a small thread that lives with the mod.
    if (!g_hookReady) g_hookReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_hookThread = CreateThread(nullptr, 0, HookThreadProc, nullptr, 0, &g_hookThreadId);
    if (g_hookThread && g_hookReady) WaitForSingleObject(g_hookReady, 5000);
}

static VOID Uninit()
{
    if (g_hookThread) {  // the hook thread removes its own hooks on the way out
        PostThreadMessageW(g_hookThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g_hookThread, 2000);
        CloseHandle(g_hookThread);
        g_hookThread = nullptr;
    }
    if (g_hookReady) { CloseHandle(g_hookReady); g_hookReady = nullptr; }
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
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-23-seamless-download-manager\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace acset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessDownloadManagerSettings";
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
// Generated by work\2026-11-23-seamless-download-manager\gen.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Number, L"sdm.threads", L"Connections per download", L"More connections can be faster. 8 suits most sites.", L"8", {}, 1, 32, 0, L"Connections"},
{K::Number, L"sdm.concurrent", L"Downloads at the same time", L"0 means no limit.", L"3", {}, 0, 50, 0, L"Connections"},
{K::Number, L"sdm.retries", L"Tries before giving up", L"Each try waits longer than the last.", L"3", {}, 0, 50, 0, L"Connections"},
{K::Check, L"sdm.split", L"Split big parts while downloading", L"Keeps every connection busy near the end.", L"1", {}, 0, 100, 0, L"Connections"},
{K::Text, L"sdm.folder", L"Save files to", L"Where new downloads go unless a file type has its own folder.", L"", {}, 0, 100, 0, L"Where files go"},
{K::Check, L"sdm.sortcat", L"Sort into folders by file type", L"Uses the folder set for each file type.", L"1", {}, 0, 100, 0, L"Where files go"},
{K::Check, L"sdm.limitOn", L"Limit total speed", L"Leaves room for games and calls.", L"0", {}, 0, 100, 1, L"Speed"},
{K::Number, L"sdm.limitKb", L"Speed limit in KB per second", L"Used while the limit is on.", L"256", {}, 1, 10000000, 1, L"Speed"},
{K::Check, L"sdm.decimal", L"Show sizes in thousands (KB, MB)", L"Off shows 1024-based units.", L"0", {}, 0, 100, 1, L"Speed"},
{K::Check, L"sdm.markPart", L"Mark unfinished files", L"Unfinished files end in .sdm-part until they are done.", L"1", {}, 0, 100, 1, L"Files"},
{K::Check, L"sdm.sparse", L"Reserve space quickly", L"Big files start at once instead of filling the disk first.", L"1", {}, 0, 100, 1, L"Files"},
{K::Check, L"sdm.serverDate", L"Keep the server's file date", L"A finished file gets the date the site gives it.", L"0", {}, 0, 100, 1, L"Files"},
{K::Check, L"sdm.deletePart", L"Delete unfinished files on remove", L"Removing a download that never finished also deletes what it got so far.", L"1", {}, 0, 100, 1, L"Files"},
{K::Number, L"sdm.port", L"Port", L"The extension finds it by itself.", L"15161", {}, 1024, 65535, 2, L"Browser link"},
{K::Text, L"sdm.key", L"Browser key", L"The extension gets it by itself. Copy it only to set it up by hand.", L"", {}, 0, 100, 2, L"Browser link"},
{K::Choice, L"sdm.dns", L"Find sites with", L"How the engine looks up a site's address.", L"win", {{L"win", L"Windows"}, {L"cloudflare", L"Cloudflare"}, {L"google", L"Google"}, {L"quad9", L"Quad9"}, {L"custom", L"Custom address"}}, 0, 100, 2, L"Name lookup"},
{K::Text, L"sdm.dnsUrl", L"Custom address", L"Only for Custom address. It must start with https://", L"", {}, 0, 100, 2, L"Name lookup"},
{K::Check, L"sdm.sound", L"Play a sound when a download ends", L"One sound every two seconds at most, so big batches stay quiet.", L"1", {}, 0, 100, 3, L"Sounds"},
{K::Text, L"sdm.soundDone", L"When it finishes", L"A .wav file. Empty plays the Windows sound.", L"", {}, 0, 100, 3, L"Sounds"},
{K::Text, L"sdm.soundFail", L"When it fails", L"A .wav file. Empty plays the Windows sound.", L"", {}, 0, 100, 3, L"Sounds"},
{K::Check, L"settingsGlass", L"Blurred windows", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 4, L"Windows"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 4, L"Windows"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to open your downloads. Right-click it for more. When off, closing the window keeps downloads running and your browser can still open it.", L"1", {}, 0, 100, 4, L"Windows"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Downloads", L"Where files go, how many connections each download uses and how many run at once.", 0xE896},
{L"Speed and files", L"A speed limit, how sizes show and what happens to unfinished files.", 0xEC4A},
{L"Browser and lookup", L"How your browser sends downloads here, and how site names are looked up.", 0xE774},
{L"Sounds and sites", L"Sounds when downloads end, and rules for single sites.", 0xE767},
{L"Look", L"How the download window, its small windows and this settings window look.", 0xE790},
{L"About", L"Version, updates, credits, support and links.", 0xE946},
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
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Download%20Manager%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Download Manager";
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
    return sdm::BannerText();
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Downloads") <= railW) break;
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
    auto engine = sdm::LoadSettings();
    for (auto& f : w.fields) {
        if (wcsncmp(f.key, L"sdm.", 4) == 0) {
            std::wstring v = f.def;
            for (auto& [k, val] : engine)
                if (k == f.key) v = val;
            Set_PutValue(f, v);
            f.value = Set_FieldValue(f);
            continue;
        }
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
    int startPage = sdm::TakeStartPage();
    if (startPage >= 0 && startPage < kSetPageCount && startPage != w.page) {
        w.page = startPage;
        w.scrollY = w.scrollTarget = 0;
    }
    w.items.clear();
    const float space = Set_RailSpace(w), avail = w.cw - space;
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, kSetMaxW);
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), kSetPages[w.page].intro, w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
    if (w.page != kSetAboutPage) {
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
    // Engine links (sdm_app.inc): before the fields, after a field, or at the end of the page.
    auto sdmLinks = [&](PCWSTR after, PCWSTR& lastGroup) {
        for (auto* l : sdm::LinksFor(w.page, after)) {
            if (!lastGroup || wcscmp(lastGroup, l->group) != 0) {
                SetItem g;
                g.type = SetItem::Group;
                g.text = l->group;
                y += lastGroup ? 14 : 0;
                g.y = y;
                g.h = 22;
                y += g.h + 6;
                w.items.push_back(g);
                lastGroup = l->group;
            }
            SetItem it;
            it.type = SetItem::Link;
            it.text = sdm::LinkText(l->url, false);
            it.sub = sdm::LinkText(l->url, true);
            it.url = l->url;
            it.y = y;
            it.h = std::max(56.0f, Set_TextH(w.fHint.get(), it.sub, w.contentW - kSetRowPad - 50) + 38);
            y += it.h + kSetRowGap;
            w.items.push_back(it);
        }
    };
    sdmLinks(nullptr, lastGroup);
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
        sdmLinks(f.key, lastGroup);
    }
    sdmLinks(L"", lastGroup);
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
        {
            std::wstring t = sdm::LinkText(L"sdm:update", false), s = sdm::LinkText(L"sdm:update", true);
            add(SetItem::Link, 56, t.c_str(), s.c_str(), L"sdm:update");
        }
        add(SetItem::Support, 84, L"Like it? Help it keep going.",
            L"If this saves you time, a tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        {
            PCWSTR thanks = L"Built on the ideas of AB Download Manager by Amir Ali Ghaffari, shared under the Apache 2.0 "
                            L"licence. Every line here is new, but the features and the care come from that project.";
            add(SetItem::Link, std::max(56.0f, Set_TextH(w.fHint.get(), thanks, w.contentW - kSetRowPad - 50) + 38),
                L"AB Download Manager", thanks, sdm::kAbRepo);
        }
        add(SetItem::Link, 56, L"Colors from Catppuccin Mocha", L"By the Catppuccin team, MIT", kSetPaletteUrl);
        group(L"Project");
        add(SetItem::Link, 56, L"The standalone app on GitHub", L"github.com/DavidHiFi/seamless-download-manager", sdm::kAppRepo);
        add(SetItem::Link, 56, L"This mod on GitHub", L"github.com/DavidHiFi/davids-windhawk-mods", kSetRepoUrl);
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

// Text that should not sit in plain view (the browser key): it shows frosted, and the
// pointer on its row eases it clear.
static bool Set_IsSecret(const SetField& f) { return wcscmp(f.key, L"sdm.key") == 0; }

static void Set_DrawSecret(SetPaint& p, SetWindow& w, const std::wstring& s, const D2D1_RECT_F& r, const D2D1_RECT_F& box,
                           float reveal) {
    if (s.empty()) return;
    reveal = std::clamp(reveal, 0.0f, 1.0f);
    if (reveal > 0.003f) p.Text(w.fValue.get(), s, r, mocha::text, reveal);
    float a = 1 - reveal;
    if (a <= 0.003f) return;
    const float pad = 10;
    D2D1_SIZE_F sz = D2D1::SizeF(r.right - r.left + 2 * pad, r.bottom - r.top);
    SetCom<ID2D1DeviceContext> dc;
    SetCom<ID2D1BitmapRenderTarget> tmp;
    SetCom<ID2D1Effect> blur;
    SetCom<ID2D1SolidColorBrush> br;
    SetCom<ID2D1Bitmap> bmp;
    if (sz.width > 1 && SUCCEEDED(p.rt->QueryInterface(__uuidof(ID2D1DeviceContext), (void**)dc.put())) &&
        SUCCEEDED(dc->CreateEffect(CLSID_D2D1GaussianBlur, blur.put())) &&
        SUCCEEDED(p.rt->CreateCompatibleRenderTarget(sz, tmp.put())) &&
        SUCCEEDED(tmp->CreateSolidColorBrush(D2DColor(mocha::text, a * p.fade), br.put()))) {
        tmp->BeginDraw();
        tmp->Clear(D2D1::ColorF(0, 0));
        tmp->DrawText(s.c_str(), (UINT32)s.size(), w.fValue.get(), D2D1::RectF(pad, 0, sz.width - pad, sz.height), br.get(),
                      D2D1_DRAW_TEXT_OPTIONS_CLIP);
        if (SUCCEEDED(tmp->EndDraw()) && SUCCEEDED(tmp->GetBitmap(bmp.put()))) {
            blur->SetInput(0, bmp.get());
            blur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 3.5f);
            blur->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_SOFT);
            p.rt->PushAxisAlignedClip({box.left + 2, box.top + 2, box.right - 2, box.bottom - 2}, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
            dc->DrawImage(blur.get(), D2D1::Point2F(r.left - pad, r.top));
            p.rt->PopAxisAlignedClip();
            return;
        }
    }
    // No blur on this target: dots in place of the key.
    p.Text(w.fValue.get(), std::wstring(std::min<size_t>(s.size(), 24), L'\x2022'), r, mocha::overlay1, a);
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
            D2D1_RECT_F tr{b.left + 12, b.top, b.right - 10, b.bottom};
            if (ed) break;
            if (Set_IsSecret(f)) Set_DrawSecret(p, w, f.cur, tr, b, std::max(Set_GlowOf(w, 1000 + k), Set_GlowOf(w, 6000 + k)));
            else p.Text(w.fValue.get(), f.cur, tr, mocha::text);
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
        const WCHAR glyph = 0xE896;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Download Manager", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  engine " + sdm::kEngineVersion +
                      L"  \u00B7  GPL-3.0  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"GPL-3.0  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"A fast download manager for Windows, written in Rust. Downloads split into parts, pick up where they "
           L"stopped, and come straight from your browser.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi. The Windhawk version of the standalone app.",
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
    p.Text(w.fRailName.get(), L"Downloads", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    const WCHAR mark = 0xE896;
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
    if (wcsncmp(url, L"sdm:", 4) == 0) {
        sdm::LinkAction(url);
        return;
    }
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
        if (wcsncmp(f.key, L"sdm.", 4) == 0) continue;  // Saved to the engine instead.
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
    // Download settings go straight to the engine; only the look goes through Windhawk.
    std::vector<std::pair<std::wstring, std::wstring>> sdmVals;
    std::vector<std::wstring> sdmChanged;
    for (auto& f : w.fields) {
        if (wcsncmp(f.key, L"sdm.", 4) != 0) continue;
        std::wstring value = Set_FieldValue(f);
        sdmVals.push_back({f.key, value});
        if (value != f.value) sdmChanged.push_back(f.key);
    }
    if (!changed && sdmChanged.empty()) {
        Set_SetStatus(w, L"Nothing changed");
        return;
    }
    if (!sdmChanged.empty()) {
        std::wstring err;
        if (!sdm::SaveSettings(sdmVals, sdmChanged, err)) {
            Set_SetStatus(w, err.c_str(), true);
            return;
        }
        for (auto& f : w.fields)
            if (wcsncmp(f.key, L"sdm.", 4) == 0) f.value = Set_FieldValue(f);
        if (!changed) {
            Set_SetStatus(w, L"Saved");
            return;
        }
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Download Manager settings", style,
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
int ShowTrayMenu(HWND owner, const POINT* at, bool on, PCWSTR) {
    return Set_TrayMenu(owner, {Set_MenuRow(100, L"", L"Open Seamless Download Manager"),
                                Set_MenuRow(101, L"", L"Add a link", false, !on),
                                Set_MenuSep(),
                                Set_MenuRow(102, L"", L"Pause all", false, !on),
                                Set_MenuRow(103, L"", L"Resume all", false, !on),
                                Set_MenuSep(),
                                Set_MenuRow(104, L"", L"Settings"),
                                Set_MenuRow(105, L"", on ? L"Exit" : L"Start the download engine")}, at);
}
}  // namespace acset

// ===========================================================================
// Seamless Download Manager: the engine link, the data model and the words.
// The engine is the same Rust library the standalone app uses, so both share
// one data folder and one download list.
// ===========================================================================
namespace sdm {
using sj::Val;
using acset::SetCom;
namespace mocha = acset::mocha;
using acset::D2DColor;

constexpr PCWSTR kAppTitle = L"Seamless Download Manager";
constexpr PCWSTR kKofi = L"https://ko-fi.com/DavidHiFi";

// Window messages from the engine thread to the UI thread.
constexpr UINT WM_SDM_TRAY = WM_APP + 45, WM_SDM_SETTINGS = WM_APP + 46, WM_SDM_POLL = WM_APP + 60,
               WM_SDM_STATE = WM_APP + 61, WM_SDM_SHOW = WM_APP + 62, WM_SDM_OPEN = WM_APP + 63,
               WM_SDM_NOTICE = WM_APP + 64, WM_SDM_POWER = WM_APP + 65, WM_SDM_ADDREQ = WM_APP + 66,
               WM_SDM_SETTINGS_SAVED = WM_APP + 67, WM_SDM_TEST = WM_APP + 70;

enum class State { Starting, Missing, Busy, Failed, Running, Stopped };

using StartFn = int32_t (*)(const uint16_t*);
using CallFn = char* (*)(const char*);
using FreeFn = void (*)(char*);
using StopFn = void (*)();
using ErrFn = char* (*)();

struct Engine {
    HMODULE dll = nullptr;
    StartFn start = nullptr;
    CallFn call = nullptr;
    FreeFn free = nullptr;
    StopFn stop = nullptr;
    ErrFn lastError = nullptr;
};

Engine g_eng;
std::mutex g_callLock;
std::atomic<State> g_state{State::Starting};
std::atomic<bool> g_quit{false}, g_shown{false}, g_refresh{false}, g_restart{false};
HANDLE g_engineThread = nullptr, g_wake = nullptr;
HWND g_msgWnd = nullptr;  // The tray window, on the UI thread.
DWORD g_uiThreadId = 0;
std::mutex g_textLock;
std::wstring g_failText;  // Why the engine did not start, for the notice.
std::atomic<bool> g_fetching{false};  // A Workshop download of the engine is under way.

std::wstring LocalAppData() {
    WCHAR buf[MAX_PATH];
    DWORD n = GetEnvironmentVariableW(L"LOCALAPPDATA", buf, MAX_PATH);
    return n && n < MAX_PATH ? std::wstring(buf, n) : std::wstring();
}

std::wstring DataDir() { return LocalAppData() + L"\\SeamlessDownloadManager"; }

std::wstring EnginePath() {
    return DataDir() + L"\\engine\\seamless_download_core-" + kEngineVersion + L".dll";
}

bool FileExists(const std::wstring& path) {
    DWORD a = GetFileAttributesW(path.c_str());
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

bool DirExists(const std::wstring& path) {
    DWORD a = GetFileAttributesW(path.c_str());
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
}

// One engine call. The engine answers {"error": "..."} on any failure; so does this when it is not running.
Val Call(const Val& req) {
    std::string text = sj::Dump(req);
    std::lock_guard<std::mutex> lock(g_callLock);
    if (g_state.load() != State::Running || !g_eng.call) {
        Val v = sj::Obj();
        v.set("error", sj::Str("The download engine is not running"));
        return v;
    }
    char* out = g_eng.call(text.c_str());
    Val v = sj::Parse(out);
    if (out) g_eng.free(out);
    if (v.null()) {
        v = sj::Obj();
        v.set("error", sj::Str("The engine gave an answer that could not be read"));
    }
    return v;
}

Val Cmd(const char* cmd) {
    Val r = sj::Obj();
    r.set("cmd", sj::Str(cmd));
    return r;
}

std::wstring ErrorOf(const Val& v) {
    const Val& e = v["error"];
    if (e.t == Val::Str) return sj::W(e.s);
    return {};
}

Val IdsVal(const std::vector<int64_t>& ids) {
    Val a = sj::Arr();
    for (int64_t id : ids) a.push(sj::Int(id));
    return a;
}

// ---- The data the window shows ---------------------------------------------------------

struct Dl {
    int64_t id = 0;
    std::wstring name, folder, url, error;
    int64_t size = -1, downloaded = 0, speed = 0, eta = -1, added = 0, finished = 0, queue = -1, category = -1;
    int64_t connections = 0, speedLimit = 0;
    std::string status;
    std::wstring lname, lurl;  // Lowercase, for search.
    bool running() const { return status == "downloading" || status == "retrying"; }
    bool waiting() const { return status == "queued"; }
    bool done() const { return status == "completed"; }
    std::wstring path() const {
        if (folder.empty()) return name;
        std::wstring p = folder;
        if (p.back() != L'\\' && p.back() != L'/') p += L'\\';
        return p + name;
    }
};

struct QueueInfo {
    int64_t id = 0;
    std::wstring name;
    std::vector<int64_t> items;
    bool active = false;
    Val raw;
};

struct CatInfo {
    int64_t id = 0;
    std::wstring name;
    std::string icon;
};

std::wstring Lower(std::wstring s) {
    CharLowerBuffW(s.data(), (DWORD)s.size());
    return s;
}

Dl ParseDl(const Val& v) {
    Dl d;
    d.id = v["id"].num();
    d.name = sj::W(v["name"].str());
    d.folder = sj::W(v["folder"].str());
    d.url = sj::W(v["url"].str());
    d.error = sj::W(v["error"].str());
    d.size = v["size"].null() ? -1 : v["size"].num();
    d.downloaded = v["downloaded"].num();
    d.speed = v["speed"].num();
    d.eta = v["eta_secs"].null() ? -1 : v["eta_secs"].num();
    d.added = v["date_added"].num();
    d.finished = v["date_finished"].null() ? 0 : v["date_finished"].num();
    d.queue = v["queue_id"].null() ? -1 : v["queue_id"].num();
    d.category = v["category_id"].null() ? -1 : v["category_id"].num();
    d.connections = v["connections"].num();
    d.speedLimit = v["speed_limit"].num();
    d.status = v["status"].str();
    d.lname = Lower(d.name);
    d.lurl = Lower(d.url);
    return d;
}

// What one poll brought, handed from the engine thread to the window.
struct PollResult {
    bool hasDownloads = false;
    std::vector<Dl> downloads;
    bool hasQueues = false;
    std::vector<QueueInfo> queues;
    bool hasCats = false;
    std::vector<CatInfo> cats;
    bool hasSettings = false;
    Val settings;
    bool hasStatus = false;
    Val status;
};

struct PowerAsk {
    std::wstring queue;
    std::string action;
};

// ---- Words and numbers, as the app writes them -------------------------------------------

std::wstring Fmt1(double v) {
    WCHAR b[32];
    swprintf_s(b, L"%.1f", v);
    return b;
}

std::wstring SizeText(int64_t bytes, bool decimal) {
    if (bytes < 0) bytes = 0;
    static const PCWSTR dec[] = {L"B", L"KB", L"MB", L"GB", L"TB"};
    static const PCWSTR bin[] = {L"B", L"KiB", L"MiB", L"GiB", L"TiB"};
    double step = decimal ? 1000.0 : 1024.0, value = (double)bytes;
    int unit = 0;
    while (value >= step && unit < 4) {
        value /= step;
        unit++;
    }
    WCHAR b[48];
    if (unit == 0) swprintf_s(b, L"%lld B", (long long)bytes);
    else if (value >= 100.0) swprintf_s(b, L"%.0f %s", value, decimal ? dec[unit] : bin[unit]);
    else swprintf_s(b, L"%.1f %s", value, decimal ? dec[unit] : bin[unit]);
    return b;
}

std::wstring SpeedText(int64_t bps, bool decimal) { return SizeText(bps, decimal) + L"/s"; }

std::wstring EtaText(int64_t s) {
    WCHAR b[32];
    if (s < 60) swprintf_s(b, L"%llds", (long long)s);
    else if (s < 3600) swprintf_s(b, L"%lldm %02llds", (long long)(s / 60), (long long)(s % 60));
    else if (s < 86400) swprintf_s(b, L"%lldh %02lldm", (long long)(s / 3600), (long long)((s % 3600) / 60));
    else swprintf_s(b, L"%lldd %lldh", (long long)(s / 86400), (long long)((s % 86400) / 3600));
    return b;
}

SYSTEMTIME LocalFromMs(int64_t ms) {
    ULARGE_INTEGER u;
    u.QuadPart = (ULONGLONG)(ms + 11644473600000LL) * 10000ULL;
    FILETIME ft{u.LowPart, u.HighPart}, lf;
    SYSTEMTIME st{};
    FileTimeToLocalFileTime(&ft, &lf);
    FileTimeToSystemTime(&lf, &st);
    return st;
}

std::wstring WhenText(int64_t ms) {
    if (ms <= 0) return {};
    static const PCWSTR months[] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun",
                                    L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};
    SYSTEMTIME at = LocalFromMs(ms), now;
    GetLocalTime(&now);
    auto dayNumber = [](const SYSTEMTIME& t) {
        FILETIME f;
        SYSTEMTIME d = t;
        d.wHour = d.wMinute = d.wSecond = d.wMilliseconds = 0;
        SystemTimeToFileTime(&d, &f);
        return (int64_t)(((ULONGLONG)f.dwHighDateTime << 32 | f.dwLowDateTime) / 864000000000ULL);
    };
    int64_t days = dayNumber(now) - dayNumber(at);
    WCHAR b[48];
    if (days == 0) {
        int h = at.wHour % 12;
        if (!h) h = 12;
        swprintf_s(b, L"Today %d:%02d %s", h, at.wMinute, at.wHour < 12 ? L"am" : L"pm");
    } else if (days == 1) {
        return L"Yesterday";
    } else if (at.wYear == now.wYear) {
        swprintf_s(b, L"%d %s", at.wDay, months[(at.wMonth + 11) % 12]);
    } else {
        swprintf_s(b, L"%d %s %d", at.wDay, months[(at.wMonth + 11) % 12], at.wYear);
    }
    return b;
}

int Percent(const Dl& d) {
    return d.size > 0 ? (int)std::min<int64_t>(100, d.downloaded * 100 / d.size) : 0;
}

// The status words and their tone: 0 plain, 1 green, 2 blue, 3 peach, 4 red, 5 quiet.
std::wstring StatusText(const Dl& d, int& tone) {
    WCHAR b[48];
    if (d.status == "completed") {
        tone = 1;
        return L"Done";
    }
    if (d.status == "downloading") {
        tone = 2;
        swprintf_s(b, L"Downloading %d%%", Percent(d));
        return b;
    }
    if (d.status == "retrying") {
        tone = 5;
        return L"Trying again";
    }
    if (d.status == "paused") {
        tone = 3;
        swprintf_s(b, L"Paused at %d%%", Percent(d));
        return b;
    }
    if (d.status == "queued") {
        tone = 5;
        return L"Waiting in queue";
    }
    if (d.status == "failed") {
        tone = 4;
        return L"Failed";
    }
    tone = 0;
    return L"Not started";
}

UINT32 ToneColor(int tone) {
    switch (tone) {
        case 1: return mocha::green;
        case 2: return mocha::blue;
        case 3: return mocha::peach;
        case 4: return mocha::red;
        case 5: return mocha::subtext0;
        default: return mocha::subtext1;
    }
}

std::wstring PowerWhat(const std::string& a) {
    if (a == "sleep") return L"go to sleep";
    if (a == "hibernate") return L"hibernate";
    if (a == "shutdown") return L"shut down";
    if (a == "restart") return L"restart";
    return L"";
}

std::wstring PowerButton(const std::string& a) {
    if (a == "sleep") return L"Sleep now";
    if (a == "hibernate") return L"Hibernate now";
    if (a == "shutdown") return L"Shut down now";
    if (a == "restart") return L"Restart now";
    return L"Now";
}

// ---- The engine thread --------------------------------------------------------------------

void PostUi(UINT msg, WPARAM w = 0, LPARAM l = 0) {
    if (HWND h = g_msgWnd) PostMessageW(h, msg, w, l);
}

void SetFail(const std::wstring& text) {
    std::lock_guard<std::mutex> lock(g_textLock);
    g_failText = text;
}

std::wstring FailText() {
    std::lock_guard<std::mutex> lock(g_textLock);
    return g_failText;
}

void SetState(State s) {
    if (g_state.exchange(s) != s) PostUi(WM_SDM_STATE);
}

bool LoadEngine() {
    if (g_eng.dll) return true;
    std::wstring path = EnginePath();
    if (!FileExists(path)) return false;
    HMODULE dll = LoadLibraryExW(path.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!dll) {
        WCHAR b[160];
        swprintf_s(b, L"Windows could not load the engine file (error %lu).", GetLastError());
        SetFail(b);
        return false;
    }
    Engine e;
    e.dll = dll;
    e.start = (StartFn)(void*)GetProcAddress(dll, "sdm_start");
    e.call = (CallFn)(void*)GetProcAddress(dll, "sdm_call");
    e.free = (FreeFn)(void*)GetProcAddress(dll, "sdm_free");
    e.stop = (StopFn)(void*)GetProcAddress(dll, "sdm_stop");
    e.lastError = (ErrFn)(void*)GetProcAddress(dll, "sdm_last_error");
    if (!e.start || !e.call || !e.free || !e.stop) {
        SetFail(L"The engine file is missing parts this version needs.");
        Wh_Log(L"engine dll lacks exports");
        // Never FreeLibrary: the engine may have started threads of its own.
        return false;
    }
    g_eng = e;
    return true;
}

// The standalone app used to start with Windows. The mod runs the engine now, so the app's
// start-up entry goes.
bool DropRunValue() {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE | KEY_QUERY_VALUE,
                      &key) != ERROR_SUCCESS)
        return false;
    bool had = RegQueryValueExW(key, L"SeamlessDownloadManager", nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS;
    bool gone = had && RegDeleteValueW(key, L"SeamlessDownloadManager") == ERROR_SUCCESS;
    RegCloseKey(key);
    return gone;
}

bool Wait(DWORD ms) {
    if (g_quit.load()) return false;
    WaitForSingleObject(g_wake, ms);
    return !g_quit.load();
}

void FetchLists(PollResult& r, bool queues, bool settings) {
    if (queues) {
        Val q = Call(Cmd("queues"));
        if (q.has("queues")) {
            r.hasQueues = true;
            std::set<int64_t> active;
            for (auto& a : q["active"].a) active.insert(a.num());
            for (auto& one : q["queues"].a) {
                QueueInfo qi;
                qi.id = one["id"].num();
                qi.name = sj::W(one["name"].str());
                for (auto& it : one["items"].a) qi.items.push_back(it.num());
                qi.active = active.count(qi.id) != 0;
                qi.raw = one;
                r.queues.push_back(std::move(qi));
            }
        }
        Val c = Call(Cmd("categories"));
        if (c.t == Val::Arr) {
            r.hasCats = true;
            for (auto& one : c.a) {
                CatInfo ci;
                ci.id = one["id"].num();
                ci.name = sj::W(one["name"].str());
                ci.icon = one["icon"].str();
                r.cats.push_back(std::move(ci));
            }
        }
    }
    if (settings) {
        Val s = Call(Cmd("settings"));
        if (!s.has("error")) {
            r.hasSettings = true;
            r.settings = std::move(s);
        }
        Val st = Call(Cmd("status"));
        if (!st.has("error")) {
            r.hasStatus = true;
            r.status = std::move(st);
        }
    }
}

void PollLoop() {
    int64_t rev = -1, queuesRev = -1, settingsRev = -1;
    ULONGLONG lastStatus = 0;
    while (!g_quit.load() && g_state.load() == State::Running) {
        if (g_refresh.exchange(false)) rev = queuesRev = settingsRev = -1;
        Val req = Cmd("poll");
        if (rev >= 0) req.set("rev", sj::Int(rev));
        Val v = Call(req);
        if (v.has("error")) {
            Wh_Log(L"poll failed: %s", ErrorOf(v).c_str());
            if (!Wait(1000)) break;
            continue;
        }
        auto* r = new PollResult();
        rev = v["rev"].num();
        if (v["downloads"].t == Val::Arr) {
            r->hasDownloads = true;
            r->downloads.reserve(v["downloads"].a.size());
            for (auto& d : v["downloads"].a) r->downloads.push_back(ParseDl(d));
        }
        int64_t qr = v["queues_rev"].num(), sr = v["settings_rev"].num();
        ULONGLONG now = GetTickCount64();
        bool wantQueues = qr != queuesRev, wantSettings = sr != settingsRev || now - lastStatus > 5000;
        queuesRev = qr;
        settingsRev = sr;
        if (wantSettings) lastStatus = now;
        FetchLists(*r, wantQueues, wantSettings);
        if (r->hasDownloads || r->hasQueues || r->hasSettings || r->hasStatus) {
            if (!g_msgWnd || !PostMessageW(g_msgWnd, WM_SDM_POLL, 0, (LPARAM)r)) delete r;
        } else {
            delete r;
        }
        if (v["show"].truthy()) PostUi(WM_SDM_SHOW);
        for (auto& add : v["add_requests"].a) {
            auto* copy = new Val(add);
            if (!g_msgWnd || !PostMessageW(g_msgWnd, WM_SDM_ADDREQ, 0, (LPARAM)copy)) delete copy;
        }
        if (!v["power"].null() && v["power"].t == Val::Obj) {
            auto* ask = new PowerAsk{sj::W(v["power"]["queue"].str()), v["power"]["action"].str()};
            if (!g_msgWnd || !PostMessageW(g_msgWnd, WM_SDM_POWER, 0, (LPARAM)ask)) delete ask;
        }
        if (v["exit"].truthy()) {
            // Another copy asked this one to step aside (an app update, for one).
            {
                std::lock_guard<std::mutex> lock(g_callLock);
                g_eng.stop();
            }
            SetFail(L"The download engine was asked to stop. Press Start to run it again.");
            SetState(State::Stopped);
            break;
        }
        if (!Wait(g_shown.load() ? 250 : 1000)) break;
    }
}

DWORD WINAPI EngineThread(void*) {
    bool noticed = false;
    while (!g_quit.load()) {
        if (!LoadEngine()) {
            if (FailText().empty() || !g_eng.dll) {
                if (!FileExists(EnginePath())) SetFail(L"");
            }
            SetState(State::Missing);
            if (!Wait(10000)) break;
            continue;
        }
        if (g_state.load() == State::Stopped && !g_restart.exchange(false)) {
            if (!Wait(1000)) break;
            continue;
        }
        g_restart = false;
        SetState(State::Starting);
        int32_t r = g_eng.start(nullptr);
        if (r == 0) {
            SetFail(L"");
            g_refresh = true;
            SetState(State::Running);
            if (!noticed) {
                noticed = true;
                if (DropRunValue()) PostUi(WM_SDM_NOTICE, 1);
            }
            PollLoop();
            continue;
        }
        if (r == 1) {
            SetFail(L"The Seamless Download Manager app is still open and would not let go. Close it from its tray icon.");
            SetState(State::Busy);
            if (!Wait(5000)) break;
            continue;
        }
        std::wstring why = L"The download engine did not start.";
        if (g_eng.lastError) {
            if (char* e = g_eng.lastError()) {
                std::wstring said = ErrorOf(sj::Parse(e));
                if (!said.empty()) why += L" " + said;
                g_eng.free(e);
            }
        }
        Wh_Log(L"%s", why.c_str());
        SetFail(why);
        SetState(State::Failed);
        if (!Wait(30000)) break;
    }
    if (g_eng.stop) {
        std::lock_guard<std::mutex> lock(g_callLock);
        g_eng.stop();  // Safe to call twice.
    }
    g_state = State::Stopped;
    return 0;
}

void Wake() {
    if (g_wake) SetEvent(g_wake);
}

void Refresh() {
    g_refresh = true;
    Wake();
}

}  // namespace sdm

// ===========================================================================
// The main window: sidebar, toolbar, the download list and the status line.
// Everything runs on the UI thread, drawn with Direct2D in the Mocha look and the
// same glass as the settings window.
// ===========================================================================
namespace sdm {

using acset::RefFromRgb;

// ---- Shared drawing core (UI thread only) --------------------------------------------------

struct Gfx {
    SetCom<ID2D1Factory> d2d;
    SetCom<IDWriteFactory> dw;
    std::wstring family, icons;
    std::map<uint64_t, SetCom<IDWriteTextFormat>> fmts;
};
Gfx g_gfx;
bool g_glass = true;

enum FmtFlags { kWrap = 1, kCenter = 2, kRight = 4, kMiddle = 8, kIcon = 16 };

bool Gfx_Family(const std::wstring& name) {
    SetCom<IDWriteFontCollection> sys;
    if (FAILED(g_gfx.dw->GetSystemFontCollection(sys.put(), FALSE))) return false;
    UINT32 index = 0;
    BOOL exists = FALSE;
    return SUCCEEDED(sys->FindFamilyName(name.c_str(), &index, &exists)) && exists;
}

bool Gfx_Init() {
    if (!g_gfx.d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), nullptr,
                                               (void**)g_gfx.d2d.put())))
        return false;
    if (!g_gfx.dw) {
        if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)g_gfx.dw.put())))
            return false;
        g_gfx.family = L"Segoe UI";
        for (PCWSTR face : {L"FiraCode Nerd Font", L"FiraCodeNerdFont", L"FiraCode Nerd Font Mono"})
            if (Gfx_Family(face)) {
                g_gfx.family = face;
                break;
            }
        g_gfx.icons = Gfx_Family(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    }
    return true;
}

void Gfx_Release() {
    g_gfx.fmts.clear();
    g_gfx.dw.reset();
    g_gfx.d2d.reset();
}

IDWriteTextFormat* Fmt(float size, int weight, int flags) {
    uint64_t key = ((uint64_t)(size * 10) << 32) | ((uint64_t)weight << 8) | (uint64_t)flags;
    auto it = g_gfx.fmts.find(key);
    if (it != g_gfx.fmts.end()) return it->second.get();
    SetCom<IDWriteTextFormat> f;
    const std::wstring& face = (flags & kIcon) ? g_gfx.icons : g_gfx.family;
    if (FAILED(g_gfx.dw->CreateTextFormat(face.c_str(), nullptr, (DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STYLE_NORMAL,
                                          DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", f.put())))
        return nullptr;
    f->SetWordWrapping((flags & kWrap) ? DWRITE_WORD_WRAPPING_WRAP : DWRITE_WORD_WRAPPING_NO_WRAP);
    f->SetTextAlignment((flags & kCenter)  ? DWRITE_TEXT_ALIGNMENT_CENTER
                        : (flags & kRight) ? DWRITE_TEXT_ALIGNMENT_TRAILING
                                           : DWRITE_TEXT_ALIGNMENT_LEADING);
    f->SetParagraphAlignment((flags & kMiddle) ? DWRITE_PARAGRAPH_ALIGNMENT_CENTER : DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    if (!(flags & kWrap)) {
        SetCom<IDWriteInlineObject> sign;
        g_gfx.dw->CreateEllipsisTrimmingSign(f.get(), sign.put());
        DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        f->SetTrimming(&t, sign.get());
    }
    IDWriteTextFormat* raw = f.get();
    g_gfx.fmts[key] = f;
    return raw;
}

float TextW(IDWriteTextFormat* f, const std::wstring& s) {
    SetCom<IDWriteTextLayout> layout;
    DWRITE_TEXT_METRICS m{};
    if (!f || s.empty() || FAILED(g_gfx.dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, 10000, 1000, layout.put())) ||
        FAILED(layout->GetMetrics(&m)))
        return 0;
    return m.widthIncludingTrailingWhitespace;
}

float TextH(IDWriteTextFormat* f, const std::wstring& s, float width) {
    SetCom<IDWriteTextLayout> layout;
    DWRITE_TEXT_METRICS m{};
    if (!f || s.empty() || FAILED(g_gfx.dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, std::max(1.0f, width), 10000, layout.put())) ||
        FAILED(layout->GetMetrics(&m)))
        return 0;
    return m.height;
}

// The live corner radius (the corner mod's setting), in DIPs.
float g_radius = 8;
float Radius() { return g_radius; }
float CtlRadius() { return std::min(g_radius, 8.0f); }

struct Pt {
    ID2D1RenderTarget* rt;
    SetCom<ID2D1SolidColorBrush> sb;
    explicit Pt(ID2D1RenderTarget* r) : rt(r) { rt->CreateSolidColorBrush(D2DColor(0), sb.put()); }
    ID2D1SolidColorBrush* B(UINT32 c, float a = 1) {
        sb->SetColor(D2DColor(c, a));
        return sb.get();
    }
    SetCom<ID2D1LinearGradientBrush> G(const D2D1_RECT_F& r, float a) {
        SetCom<ID2D1LinearGradientBrush> out;
        D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a)}, {1, D2DColor(mocha::mauve, a)}};
        SetCom<ID2D1GradientStopCollection> coll;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())))
            rt->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, (r.top + r.bottom) / 2),
                                                    D2D1::Point2F(std::max(r.right, r.left + 1), (r.top + r.bottom) / 2)),
                coll.get(), out.put());
        return out;
    }
    void Fill(const D2D1_RECT_F& r, UINT32 c, float a = 1) {
        if (a > 0.003f) rt->FillRectangle(r, B(c, a));
    }
    void Round(const D2D1_RECT_F& r, float rad, UINT32 c, float a = 1) {
        if (a > 0.003f) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), B(c, a));
    }
    // A stroke of width w sits at inset w/2 on radius R - w/2, so the curve matches the straight sides.
    void Edge(const D2D1_RECT_F& r, float rad, UINT32 c, float a, float w = 2) {
        if (a <= 0.003f) return;
        float h = w / 2;
        rt->DrawRoundedRectangle(D2D1::RoundedRect({r.left + h, r.top + h, r.right - h, r.bottom - h}, std::max(0.0f, rad - h),
                                                   std::max(0.0f, rad - h)),
                                 B(c, a), w);
    }
    void GradFill(const D2D1_RECT_F& r, float rad, float a) {
        if (a <= 0.003f) return;
        if (auto g = G(r, a)) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), g.get());
    }
    void GradEdge(const D2D1_RECT_F& r, float rad, float a, float w = 2) {
        if (a <= 0.003f) return;
        float h = w / 2;
        if (auto g = G(r, a))
            rt->DrawRoundedRectangle(D2D1::RoundedRect({r.left + h, r.top + h, r.right - h, r.bottom - h}, std::max(0.0f, rad - h),
                                                       std::max(0.0f, rad - h)),
                                     g.get(), w);
    }
    // The resting edge fades out as the hover edge fades in, both 2px, so nothing jumps.
    void HoverEdge(const D2D1_RECT_F& r, float rad, float glow, float rest = 1) {
        Edge(r, rad, mocha::surface2, rest * (1 - glow));
        GradEdge(r, rad, glow);
    }
    void Text(IDWriteTextFormat* f, const std::wstring& s, const D2D1_RECT_F& r, UINT32 c, float a = 1) {
        if (!f || s.empty() || a <= 0.003f) return;
        rt->DrawText(s.c_str(), (UINT32)s.size(), f, r, B(c, a), D2D1_DRAW_TEXT_OPTIONS_CLIP);
    }
    void Glyph(IDWriteTextFormat* f, WCHAR g, const D2D1_RECT_F& r, UINT32 c, float a = 1) { Text(f, std::wstring(1, g), r, c, a); }
    void Line(float x0, float y0, float x1, float y1, UINT32 c, float a, float w = 1) {
        if (a > 0.003f) rt->DrawLine({x0, y0}, {x1, y1}, B(c, a), w);
    }
};

bool In(const D2D1_RECT_F& r, float x, float y) { return x >= r.left && x < r.right && y >= r.top && y < r.bottom; }

// Hover easing shared by every window: 150 ms in and out.
struct Glow {
    std::map<int, float> v;
    ULONGLONG last = 0;
    float Of(int id) const {
        auto it = v.find(id);
        return it == v.end() ? 0.0f : it->second;
    }
    // Returns true while something still moves.
    bool Step(int hover, int pressed) {
        ULONGLONG now = GetTickCount64();
        float dt = last ? (float)std::min<ULONGLONG>(now - last, 100) : 16;
        last = now;
        float step = dt / 150.0f;
        bool moving = false;
        if (hover >= 0 && !v.count(hover)) v[hover] = 0;
        for (auto it = v.begin(); it != v.end();) {
            float target = it->first == hover || it->first == pressed ? 1.0f : 0.0f;
            float& g = it->second;
            if (g < target) g = std::min(target, g + step);
            else if (g > target) g = std::max(target, g - step);
            if (g != target) moving = true;
            if (g <= 0 && target <= 0) it = v.erase(it);
            else ++it;
        }
        return moving;
    }
};

struct Hit {
    int id;
    D2D1_RECT_F r;
    bool enabled = true;
};

int HitAt(const std::vector<Hit>& hits, float x, float y) {
    for (size_t i = hits.size(); i-- > 0;)
        if (In(hits[i].r, x, y)) return hits[i].enabled ? hits[i].id : -2;
    return -1;
}

// The glass under every window of the mod: the settings window's recipe (accent acrylic with a
// faint Mocha base, frame extended over the whole client), with the Windows title bar on top.
void Sdm_ApplyGlass(HWND hwnd) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    COLORREF captionText = RefFromRgb(mocha::text);
    DwmSetWindowAttribute(hwnd, 36 /* DWMWA_TEXT_COLOR */, &captionText, sizeof(captionText));
    if (!g_glass) {
        COLORREF caption = RefFromRgb(mocha::crust);
        DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
        return;
    }
    struct AccentPolicy {
        int state, flags, abgr, animation;
    };
    struct CompositionData {
        DWORD attribute;
        void* data;
        SIZE_T size;
    };
    using Composition_t = BOOL(WINAPI*)(HWND, CompositionData*);
    auto setComposition = (Composition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    int backdrop = 1;  // DWMSBT_NONE
    DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
    DWM_BLURBEHIND bb{};
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.fEnable = TRUE;
    bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
    DwmEnableBlurBehindWindow(hwnd, &bb);
    if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
    if (setComposition) {
        AccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};
        CompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
        setComposition(hwnd, &data);
    }
    MARGINS margins{-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
}

// The window body: the glass tint, or solid crust when glass is off.
void PaintBody(Pt& p, float w, float h, float tint) {
    if (g_glass) {
        p.rt->Clear(D2D1::ColorF(0, 0));
        p.Fill({0, 0, w, h}, mocha::crust, tint);
    } else {
        p.rt->Clear(D2DColor(mocha::crust));
    }
}

// A button: plain, primary (the gradient) or danger (red).
enum BtnStyle { kPlain, kPrimary, kDanger, kGhost };
void DrawButton(Pt& p, const D2D1_RECT_F& r, const std::wstring& label, WCHAR icon, int style, float glow, bool enabled,
                float fontSize = 13.5f) {
    float a = enabled ? 1.0f : 0.4f, rad = CtlRadius();
    UINT32 ink = mocha::text;
    if (style == kPrimary) {
        p.GradFill(r, rad, (0.85f + 0.15f * glow) * a);
        p.GradEdge(r, rad, glow * a);
        ink = mocha::crust;
    } else if (style == kDanger) {
        p.Round(r, rad, mocha::red, (0.85f + 0.15f * glow) * a);
        p.Edge(r, rad, mocha::maroon, glow * a);
        ink = mocha::crust;
    } else if (style == kGhost) {
        p.Round(r, rad, mocha::surface0, 0.55f * glow * a);
        p.GradEdge(r, rad, glow * a);
    } else {
        p.Round(r, rad, mocha::surface0, (0.55f + 0.2f * glow) * a);
        p.HoverEdge(r, rad, glow * (enabled ? 1 : 0), a);
    }
    IDWriteTextFormat* tf = Fmt(fontSize, 600, kCenter | kMiddle);
    if (icon && label.empty()) {
        p.Glyph(Fmt(16, 400, kIcon | kCenter | kMiddle), icon, r, ink, a);
        return;
    }
    if (icon) {
        float tw = TextW(tf, label), total = 16 + 8 + tw, x = (r.left + r.right - total) / 2;
        p.Glyph(Fmt(16, 400, kIcon | kCenter | kMiddle), icon, {x, r.top, x + 16, r.bottom}, ink, a);
        p.Text(Fmt(fontSize, 600, kMiddle), label, {x + 24, r.top, r.right, r.bottom}, ink, a);
        return;
    }
    p.Text(tf, label, r, ink, a);
}

// A switch: the knob slides, the track takes the gradient when on.
void DrawSwitch(Pt& p, const D2D1_RECT_F& r, bool on, float glow, bool enabled = true) {
    float a = enabled ? 1.0f : 0.4f, h = r.bottom - r.top;
    if (on) p.GradFill(r, h / 2, a);
    else p.Round(r, h / 2, mocha::surface0, a);
    if (!on) p.HoverEdge(r, h / 2, glow, a);
    else p.GradEdge(r, h / 2, glow * a);
    float k = h - 8, x = on ? r.right - 4 - k : r.left + 4;
    p.rt->FillEllipse(D2D1::Ellipse({x + k / 2, r.top + h / 2}, k / 2, k / 2), p.B(on ? mocha::crust : mocha::overlay2, a));
}

// ---- Forward declarations (forms.inc, queues.inc, app.inc) -----------------------------------

void Toast(const std::wstring& text, bool bad = false);
void OpenAddDialog(const Val* request, const std::wstring& link);
void OpenAddMany();
void OpenRemoveDialog(const std::vector<int64_t>& ids);
void OpenSpeedDialog(int64_t id);
void OpenCheckDialog(int64_t id);
void OpenQueuesPage(int64_t select);
void Queues_Changed();
void OpenAboutPage();
void OpenSettings();
void FetchEngine();
bool OpenWorkshop();

// ---- The main window ------------------------------------------------------------------

constexpr WCHAR kMainClass[] = L"SeamlessDownloadManagerWindow";
constexpr float kSideW = 220, kSideMini = 60, kToolH = 48, kHeadH = 34, kRowH = 44, kStatusH = 30, kGap = 10;
constexpr float kMainTint = 0x38 / 255.0f;
constexpr UINT_PTR kMainTimer = 1, kToastMs = 2600;

enum Ids {
    kIdAdd = 1, kIdAddMany, kIdResume, kIdPause, kIdRemove, kIdQueue, kIdPauseAll, kIdSearch, kIdNoticeA, kIdNoticeB,
    kIdThumb, kIdTrack,
    kIdCol = 200,
    kIdSide = 1000, kIdCat = 1100, kIdQueueRow = 1300, kIdManage = 1900, kIdSettings, kIdAbout,
    kIdRow = 100000,
};

struct Col {
    int key;
    PCWSTR name;
    float w;
};
const Col kCols[] = {{0, L"Name", 0}, {1, L"Size", 92}, {2, L"Status", 156}, {3, L"Speed", 100}, {4, L"Time left", 92}, {5, L"Added", 124}};

struct MainWin {
    HWND hwnd = nullptr, search = nullptr;
    HFONT searchFont = nullptr;
    HBRUSH boxBrush = nullptr;
    SetCom<ID2D1HwndRenderTarget> rt;
    UINT dpi = 96;
    float cw = 1000, ch = 640;
    std::vector<Dl> all;
    std::vector<int> view;
    std::vector<QueueInfo> queues;
    std::vector<CatInfo> cats;
    Val settings, status;
    bool haveData = false, decimal = false, apiUp = false;
    std::string filter = "all";
    std::wstring query;
    int sortCol = 5;
    bool sortDesc = true;
    std::set<int64_t> sel;
    int64_t anchor = -1, focusId = -1;
    float scroll = 0, dragOff = 0;
    bool dragThumb = false, tracking = false, timer = false;
    std::vector<Hit> hits;
    int hover = -1, pressed = -1;
    float mx = -1, my = -1;
    Glow glow;
    std::wstring toast;
    bool toastBad = false;
    ULONGLONG toastAt = 0;
    ULONGLONG lastClick = 0;
    int64_t lastClickId = -1;
    D2D1_RECT_F listRect{}, searchRect{};
    float thumbTop = 0, thumbH = 0, trackTop = 0, trackH = 0;
    std::vector<int> cols;  // Column keys shown at this width.
};

MainWin g_main;

float Px(float dip) { return dip * g_main.dpi / 96.0f; }

const Dl* FindDl(int64_t id) {
    for (auto& d : g_main.all)
        if (d.id == id) return &d;
    return nullptr;
}

const QueueInfo* FindQueue(int64_t id) {
    for (auto& q : g_main.queues)
        if (q.id == id) return &q;
    return nullptr;
}

std::wstring QueueName(int64_t id) {
    const QueueInfo* q = FindQueue(id);
    return q ? q->name : L"Main queue";
}

int64_t FilterQueue() { return g_main.filter.rfind("queue:", 0) == 0 ? _atoi64(g_main.filter.c_str() + 6) : -1; }
int64_t FilterCat() { return g_main.filter.rfind("cat:", 0) == 0 ? _atoi64(g_main.filter.c_str() + 4) : -1; }

bool Matches(const Dl& d) {
    const std::string& f = g_main.filter;
    if (f == "running" && !(d.running() || d.waiting())) return false;
    if (f == "done" && !d.done()) return false;
    if (f == "unfinished" && d.done()) return false;
    if (int64_t c = FilterCat(); c >= 0 && d.category != c) return false;
    if (int64_t q = FilterQueue(); q >= 0) {
        const QueueInfo* qi = FindQueue(q);
        if (!qi || std::find(qi->items.begin(), qi->items.end(), d.id) == qi->items.end()) return false;
    }
    if (!g_main.query.empty() && d.lname.find(g_main.query) == std::wstring::npos && d.lurl.find(g_main.query) == std::wstring::npos)
        return false;
    return true;
}

int StatusRank(const Dl& d) {
    static const char* order[] = {"downloading", "retrying", "queued", "paused", "added", "failed", "completed"};
    for (int i = 0; i < 7; i++)
        if (d.status == order[i]) return i;
    return 4;
}

void RebuildView() {
    MainWin& m = g_main;
    m.view.clear();
    for (int i = 0; i < (int)m.all.size(); i++)
        if (Matches(m.all[i])) m.view.push_back(i);
    int64_t q = FilterQueue();
    if (q >= 0 && m.sortCol == 5 && m.sortDesc) {
        // A queue lists in its own order, the order it downloads in.
        if (const QueueInfo* qi = FindQueue(q)) {
            std::map<int64_t, size_t> pos;
            for (size_t i = 0; i < qi->items.size(); i++) pos[qi->items[i]] = i;
            std::stable_sort(m.view.begin(), m.view.end(), [&](int a, int b) { return pos[m.all[a].id] < pos[m.all[b].id]; });
        }
    } else {
        auto key = [&](const Dl& d) -> double {
            switch (m.sortCol) {
                case 1: return (double)d.size;
                case 2: return (double)StatusRank(d);
                case 3: return (double)d.speed;
                case 4: return d.eta < 0 ? 1e18 : (double)d.eta;
                default: return (double)d.added;
            }
        };
        std::stable_sort(m.view.begin(), m.view.end(), [&](int ia, int ib) {
            const Dl &a = m.all[ia], &b = m.all[ib];
            if (m.sortCol == 0) {
                int c = a.lname.compare(b.lname);
                if (c != 0) return m.sortDesc ? c > 0 : c < 0;
            } else {
                double ka = key(a), kb = key(b);
                if (ka != kb) return m.sortDesc ? ka > kb : ka < kb;
            }
            return a.id > b.id;
        });
    }
    std::set<int64_t> keep;
    for (int i : m.view)
        if (m.sel.count(m.all[i].id)) keep.insert(m.all[i].id);
    m.sel.swap(keep);
}

std::vector<int64_t> Selected() {
    std::vector<int64_t> out;
    for (int i : g_main.view)
        if (g_main.sel.count(g_main.all[i].id)) out.push_back(g_main.all[i].id);
    return out;
}

void Main_Invalidate() {
    if (g_main.hwnd) InvalidateRect(g_main.hwnd, nullptr, FALSE);
}

void Main_StartTimer() {
    if (g_main.hwnd && !g_main.timer) g_main.timer = SetTimer(g_main.hwnd, kMainTimer, 15, nullptr) != 0;
}

void Toast(const std::wstring& text, bool bad) {
    g_main.toast = text;
    g_main.toastBad = bad;
    g_main.toastAt = GetTickCount64();
    Main_StartTimer();
    Main_Invalidate();
}

bool Running() { return g_state.load() == State::Running; }

// ---- Actions -----------------------------------------------------------------------

bool CallIds(const char* cmd, const std::vector<int64_t>& ids, std::wstring* err = nullptr) {
    Val r = Cmd(cmd);
    r.set("ids", IdsVal(ids));
    Val v = Call(r);
    Wake();
    if (v.has("error")) {
        if (err) *err = ErrorOf(v);
        return false;
    }
    return true;
}

void DoResume(const std::vector<int64_t>& ids) {
    std::wstring err;
    if (!ids.empty() && !CallIds("resume", ids, &err)) Toast(L"Could not resume: " + err, true);
}

void DoPause(const std::vector<int64_t>& ids) {
    std::wstring err;
    if (!ids.empty() && !CallIds("pause", ids, &err)) Toast(L"Could not pause: " + err, true);
}

void DoSimple(const char* cmd) {
    Val v = Call(Cmd(cmd));
    Wake();
    if (v.has("error")) Toast(ErrorOf(v), true);
}

void OpenFile(const Dl& d) {
    std::wstring path = d.path();
    if (!FileExists(path)) {
        Toast(L"That file is no longer on the disk", true);
        return;
    }
    ShellExecuteW(g_main.hwnd, L"open", path.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

void ShowInFolder(const Dl& d) {
    std::wstring path = d.path();
    if (FileExists(path)) {
        if (PIDLIST_ABSOLUTE pidl = ILCreateFromPathW(path.c_str())) {
            SHOpenFolderAndSelectItems(pidl, 0, nullptr, 0);
            ILFree(pidl);
            return;
        }
    }
    if (DirExists(d.folder)) {
        ShellExecuteW(g_main.hwnd, L"open", L"explorer.exe", acset::Set_QuoteArg(d.folder).c_str(), nullptr, SW_SHOWNORMAL);
        return;
    }
    Toast(L"That file is no longer on the disk", true);
}

bool SetClipboardText(const std::wstring& text) {
    if (!OpenClipboard(g_main.hwnd)) return false;
    EmptyClipboard();
    bool ok = false;
    if (HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(WCHAR))) {
        memcpy(GlobalLock(mem), text.c_str(), (text.size() + 1) * sizeof(WCHAR));
        GlobalUnlock(mem);
        ok = SetClipboardData(CF_UNICODETEXT, mem) != nullptr;
        if (!ok) GlobalFree(mem);
    }
    CloseClipboard();
    return ok;
}

std::wstring ClipboardText() {
    std::wstring out;
    if (!OpenClipboard(g_main.hwnd)) return out;
    if (HANDLE h = GetClipboardData(CF_UNICODETEXT)) {
        if (auto* p = (const WCHAR*)GlobalLock(h)) {
            out = p;
            GlobalUnlock(h);
        }
    }
    CloseClipboard();
    return out;
}

// A clipboard link counts when it is one http(s) address with no spaces.
std::wstring ClipboardLink() {
    std::wstring t = ClipboardText();
    while (!t.empty() && iswspace(t.back())) t.pop_back();
    size_t s = 0;
    while (s < t.size() && iswspace(t[s])) s++;
    t = t.substr(s);
    std::wstring low = Lower(t);
    if ((low.rfind(L"http://", 0) == 0 || low.rfind(L"https://", 0) == 0) && t.find_first_of(L" \t\r\n") == std::wstring::npos)
        return t;
    return {};
}

void CopyLinks(const std::vector<int64_t>& ids) {
    std::wstring text;
    int n = 0;
    for (int64_t id : ids)
        if (const Dl* d = FindDl(id)) {
            if (n++) text += L"\r\n";
            text += d->url;
        }
    if (!n || !SetClipboardText(text)) return;
    Toast(n == 1 ? std::wstring(L"Link copied") : std::to_wstring(n) + L" links copied");
}

void MoveInQueue(int64_t id, int dir) {
    const QueueInfo* q = FindQueue(FilterQueue());
    if (!q) return;
    std::vector<int64_t> items = q->items;
    auto it = std::find(items.begin(), items.end(), id);
    if (it == items.end()) return;
    size_t i = it - items.begin(), j = i + dir;
    if (dir < 0 && i == 0) return;
    if (j >= items.size()) return;
    std::swap(items[i], items[j]);
    Val raw = q->raw;
    raw.set("items", IdsVal(items));
    Val r = Cmd("save_queue");
    r.set("queue", raw);
    Val v = Call(r);
    Refresh();
    if (v.has("error")) Toast(L"Could not move it: " + ErrorOf(v), true);
}

void MoveToQueue(const std::vector<int64_t>& ids, int64_t queue) {
    Val r = Cmd("move_to_queue");
    r.set("ids", IdsVal(ids));
    r.set("queue", sj::Int(queue));
    Val v = Call(r);
    Refresh();
    if (v.has("error")) Toast(L"Could not move them: " + ErrorOf(v), true);
    else Toast(L"Moved to the queue");
}

void DefaultAction(const Dl& d) {
    if (d.done()) OpenFile(d);
    else if (!d.running()) DoResume({d.id});
}

bool QueueActive(int64_t id) {
    const QueueInfo* q = FindQueue(id);
    return q && q->active;
}

void ToggleQueue(int64_t id) {
    Val r = Cmd(QueueActive(id) ? "stop_queue" : "start_queue");
    r.set("id", sj::Int(id));
    Val v = Call(r);
    Refresh();
    if (v.has("error")) Toast(ErrorOf(v), true);
}

void RowMenu(POINT at) {
    std::vector<int64_t> ids = Selected();
    if (ids.empty()) return;
    const Dl* first = FindDl(ids[0]);
    if (!first) return;
    bool one = ids.size() == 1, anyRun = false, anyIdle = false;
    for (int64_t id : ids)
        if (const Dl* d = FindDl(id)) {
            if (d->running() || d->waiting()) anyRun = true;
            else if (!d->done()) anyIdle = true;
        }
    using acset::Set_MenuRow;
    using acset::Set_MenuSep;
    using acset::Set_MenuSub;
    std::vector<acset::SetMenuItem> items;
    items.push_back(Set_MenuRow(1, L"", L"Open", false, !(one && first->done())));
    items.push_back(Set_MenuRow(2, L"", L"Show in folder", false, !one));
    items.push_back(Set_MenuRow(3, L"", L"Check file", false, !(one && first->done())));
    items.push_back(Set_MenuSep());
    items.push_back(Set_MenuRow(4, L"", L"Resume", false, !anyIdle));
    items.push_back(Set_MenuRow(5, L"", L"Pause", false, !anyRun));
    items.push_back(Set_MenuRow(6, L"", ids.size() > 1 ? L"Copy links" : L"Copy link"));
    items.push_back(Set_MenuRow(7, L"", L"Speed limit", false, !one || first->done()));
    items.push_back(Set_MenuSep());
    if (FilterQueue() >= 0) {
        items.push_back(Set_MenuRow(8, L"", L"Move up in the queue", false, !one));
        items.push_back(Set_MenuRow(9, L"", L"Move down in the queue", false, !one));
    }
    std::vector<acset::SetMenuItem> sub;
    for (size_t i = 0; i < g_main.queues.size(); i++)
        sub.push_back(Set_MenuRow(100 + (int)i, L"", g_main.queues[i].name.c_str(), one && first->queue == g_main.queues[i].id));
    items.push_back(Set_MenuSub(L"", L"Add to queue", sub, sub.empty()));
    items.push_back(Set_MenuSep());
    items.push_back(Set_MenuRow(10, L"", ids.size() > 1 ? L"Remove these" : L"Remove"));
    int pick = acset::Set_TrayMenu(g_main.hwnd, items, &at);
    switch (pick) {
        case 1: OpenFile(*first); break;
        case 2: ShowInFolder(*first); break;
        case 3: OpenCheckDialog(first->id); break;
        case 4: DoResume(ids); break;
        case 5: DoPause(ids); break;
        case 6: CopyLinks(ids); break;
        case 7: OpenSpeedDialog(first->id); break;
        case 8: MoveInQueue(first->id, -1); break;
        case 9: MoveInQueue(first->id, 1); break;
        case 10: OpenRemoveDialog(ids); break;
        default:
            if (pick >= 100 && pick < 100 + (int)g_main.queues.size()) MoveToQueue(ids, g_main.queues[pick - 100].id);
    }
}

// ---- Layout and painting --------------------------------------------------------------

float SideW() { return g_main.cw < 760 ? kSideMini : kSideW; }

WCHAR CatGlyph(const CatInfo& c) {
    std::wstring n = Lower(c.name);
    std::wstring icon = Lower(sj::W(c.icon));
    auto has = [&](PCWSTR w) { return n.find(w) != std::wstring::npos || icon.find(w) != std::wstring::npos; };
    if (has(L"video") || has(L"movie")) return 0xE714;
    if (has(L"music") || has(L"audio")) return 0xE8D6;
    if (has(L"compress") || has(L"archive") || has(L"zip")) return 0xF012;
    if (has(L"program") || has(L"app")) return 0xECAA;
    if (has(L"doc")) return 0xE8A5;
    if (has(L"image") || has(L"picture") || has(L"photo")) return 0xEB9F;
    return 0xE7C3;
}

struct SideRow {
    int id;
    std::string filter;
    std::wstring name;
    WCHAR glyph;
    int count;
    bool dot;
};

std::vector<std::pair<std::wstring, std::vector<SideRow>>> SideRows() {
    MainWin& m = g_main;
    int all = (int)m.all.size(), run = 0, done = 0;
    for (auto& d : m.all) {
        if (d.running() || d.waiting()) run++;
        if (d.done()) done++;
    }
    std::vector<std::pair<std::wstring, std::vector<SideRow>>> out;
    out.push_back({L"DOWNLOADS",
                   {{kIdSide, "all", L"All downloads", 0xE8FD, all, false},
                    {kIdSide + 1, "running", L"Downloading", 0xE896, run, false},
                    {kIdSide + 2, "done", L"Finished", 0xE73E, done, false},
                    {kIdSide + 3, "unfinished", L"Unfinished", 0xE769, all - done, false}}});
    std::vector<SideRow> cats;
    for (size_t i = 0; i < m.cats.size(); i++) {
        int n = 0;
        for (auto& d : m.all)
            if (d.category == m.cats[i].id) n++;
        cats.push_back({kIdCat + (int)i, "cat:" + std::to_string(m.cats[i].id), m.cats[i].name, CatGlyph(m.cats[i]), n, false});
    }
    if (!cats.empty()) out.push_back({L"FILE TYPES", cats});
    std::vector<SideRow> qs;
    for (size_t i = 0; i < m.queues.size(); i++) {
        int n = 0;
        for (int64_t id : m.queues[i].items)
            if (FindDl(id)) n++;
        qs.push_back({kIdQueueRow + (int)i, "queue:" + std::to_string(m.queues[i].id), m.queues[i].name, 0xE8CB, n, m.queues[i].active});
    }
    if (!qs.empty()) out.push_back({L"QUEUES", qs});
    return out;
}

void DrawSidebar(Pt& p, float top, float bottom) {
    MainWin& m = g_main;
    float w = SideW();
    bool mini = w < kSideW;
    D2D1_RECT_F dock{kGap, top, kGap + w, bottom};
    float rad = Radius();
    p.Round(dock, rad, mocha::mantle, 0.18f);
    p.Edge(dock, rad, mocha::surface2, 1);
    p.rt->PushAxisAlignedClip({dock.left + 2, dock.top + 2, dock.right - 2, dock.bottom - 2}, D2D1_ANTIALIAS_MODE_ALIASED);
    float y = dock.top + 10;
    const float bottomRows = 3 * 38 + 14;
    // A short window squeezes the rows a little so every type still shows.
    auto sections = SideRows();
    float need = 0;
    for (auto& section : sections) need += (mini ? 6 : 26) + 38 * section.second.size() + 8;
    float room = dock.bottom - bottomRows - 30 - y;
    float squeeze = need > room && need > 0 ? std::max(0.78f, room / need) : 1.0f;
    float step = 38 * squeeze, rowH = step - 4, headH = (mini ? 6 : 26) * squeeze;
    auto row = [&](int id, const std::wstring& name, WCHAR glyph, int count, bool active, bool dot, float at, float h = 34) {
        D2D1_RECT_F r{dock.left + 8, at, dock.right - 8, at + h};
        float g = m.glow.Of(id);
        if (active) {
            p.GradFill(r, CtlRadius(), 0.2f);
            p.GradEdge(r, CtlRadius(), 0.6f + 0.4f * g);
        } else {
            p.Round(r, CtlRadius(), mocha::surface0, 0.6f * g);
            p.GradEdge(r, CtlRadius(), g);
        }
        UINT32 ink = active ? mocha::text : mocha::subtext1;
        if (mini) {
            p.Glyph(Fmt(16, 400, kIcon | kCenter | kMiddle), glyph, r, active ? mocha::blue : ink);
        } else {
            p.Glyph(Fmt(16, 400, kIcon | kCenter | kMiddle), glyph, {r.left + 6, r.top, r.left + 32, r.bottom}, active ? mocha::blue : ink);
            std::wstring c = count >= 0 ? std::to_wstring(count) : L"";
            float cwid = c.empty() ? 0 : TextW(Fmt(12, 500, kMiddle), c) + 4;
            p.Text(Fmt(13.5f, active ? 600 : 500, kMiddle), name, {r.left + 38, r.top, r.right - 10 - cwid - (dot ? 14 : 0), r.bottom}, ink);
            if (dot)
                p.rt->FillEllipse(D2D1::Ellipse({r.right - 14 - cwid - 4, (r.top + r.bottom) / 2}, 3.5f, 3.5f), p.B(mocha::green));
            p.Text(Fmt(12, 500, kMiddle | kRight), c, {r.right - 10 - cwid, r.top, r.right - 10, r.bottom}, mocha::overlay2);
        }
        m.hits.push_back({id, r});
    };
    for (auto& section : sections) {
        if (y > dock.bottom - bottomRows - 30) break;
        if (!mini) p.Text(Fmt(10.5f, 700, kMiddle), section.first, {dock.left + 20, y, dock.right - 12, y + headH - 2}, mocha::overlay1);
        y += headH;
        for (auto& r : section.second) {
            if (y + rowH > dock.bottom - bottomRows - 2) break;
            row(r.id, r.name, r.glyph, r.count, m.filter == r.filter, r.dot, y, rowH);
            y += step;
        }
        y += 8 * squeeze;
    }
    float by = dock.bottom - bottomRows + 6;
    p.Line(dock.left + 16, by - 8, dock.right - 16, by - 8, mocha::surface1, 0.8f);
    row(kIdManage, L"Manage queues", 0xE70F, -1, false, false, by);
    row(kIdSettings, L"Settings", 0xE713, -1, false, false, by + 38);
    row(kIdAbout, L"About", 0xE946, -1, false, false, by + 76);
    p.rt->PopAxisAlignedClip();
}

struct ToolBtn {
    int id;
    PCWSTR label;
    WCHAR glyph;
    bool enabled;
    int style;
};

void DrawToolbar(Pt& p, float left, float right, float top) {
    MainWin& m = g_main;
    bool run = Running();
    std::vector<int64_t> ids = Selected();
    bool canResume = false, canPause = false;
    for (int64_t id : ids)
        if (const Dl* d = FindDl(id)) {
            if (d->running() || d->waiting()) canPause = true;
            else if (!d->done()) canResume = true;
        }
    std::vector<ToolBtn> btns = {{kIdAdd, L"Add link", 0xE710, run, kPrimary},
                                 {kIdAddMany, L"Add many", 0xE8F4, run, kPlain},
                                 {kIdResume, L"Resume", 0xE768, run && canResume, kPlain},
                                 {kIdPause, L"Pause", 0xE769, run && canPause, kPlain},
                                 {kIdRemove, L"Remove", 0xE74D, run && !ids.empty(), kPlain}};
    int64_t q = FilterQueue();
    if (q >= 0) {
        bool act = QueueActive(q);
        btns.push_back({kIdQueue, act ? L"Stop queue" : L"Start queue", (WCHAR)(act ? 0xE71A : 0xE768), run, kPlain});
    }
    btns.push_back({kIdPauseAll, L"Pause all", 0xE769, run, kPlain});
    float searchW = std::clamp((right - left) * 0.28f, 150.0f, 280.0f);
    float avail = right - left - searchW - 12;
    IDWriteTextFormat* tf = Fmt(13.5f, 600, kMiddle);
    float full = 0;
    for (auto& b : btns) full += 16 + 8 + TextW(tf, b.label) + 28 + 8;
    bool labels = full <= avail;
    float x = left, h = 36, y = top + (kToolH - h) / 2;
    for (auto& b : btns) {
        float bw = labels ? 16 + 8 + TextW(tf, b.label) + 28 : 40;
        if (x + bw > left + avail) break;
        D2D1_RECT_F r{x, y, x + bw, y + h};
        DrawButton(p, r, labels ? b.label : L"", b.glyph, b.style, m.glow.Of(b.id), b.enabled);
        m.hits.push_back({b.id, r, b.enabled});
        x += bw + 8;
    }
    m.searchRect = {right - searchW, y, right, y + h};
    float g = m.glow.Of(kIdSearch);
    bool focused = m.search && GetFocus() == m.search;
    p.Round(m.searchRect, CtlRadius(), acset::kSetBoxFill);
    p.HoverEdge(m.searchRect, CtlRadius(), focused ? 1.0f : g);
    p.Glyph(Fmt(14, 400, kIcon | kCenter | kMiddle), 0xE721, {m.searchRect.left + 6, y, m.searchRect.left + 32, y + h}, mocha::overlay2);
    m.hits.push_back({kIdSearch, m.searchRect});
}

std::vector<int> ShownCols(float width) {
    std::vector<int> keys = {0, 1, 2, 3, 4, 5};
    for (int drop : {5, 4, 3}) {
        float fixed = 0;
        for (int k : keys) fixed += kCols[k].w;
        if (width - fixed >= 200) break;
        keys.erase(std::remove(keys.begin(), keys.end(), drop), keys.end());
    }
    return keys;
}

void ColumnSpans(float left, float right, std::vector<std::pair<int, std::pair<float, float>>>& out) {
    float fixed = 0;
    for (int k : g_main.cols) fixed += kCols[k].w;
    float x = left;
    for (int k : g_main.cols) {
        float w = k == 0 ? std::max(120.0f, right - left - fixed) : kCols[k].w;
        out.push_back({k, {x, x + w}});
        x += w;
    }
}

void DrawNotice(Pt& p, const D2D1_RECT_F& area) {
    MainWin& m = g_main;
    std::wstring title, body, a, b;
    State s = g_state.load();
    if (g_fetching.load()) {
        title = L"Getting the download engine";
        body = L"This takes a few seconds.";
    } else if (s == State::Missing) {
        title = L"The download engine is not here yet";
        body = FailText().empty() ? L"Seamless Workshop sets it up by itself. You can also get it now." : FailText();
        a = L"Get it now";
        b = L"Open Seamless Workshop";
    } else if (s == State::Busy) {
        title = L"The app is still running";
        body = FailText();
        a = L"Try again";
    } else if (s == State::Failed) {
        title = L"The download engine did not start";
        body = FailText();
        a = L"Try again";
    } else if (s == State::Stopped) {
        title = L"The download engine is stopped";
        body = FailText().empty() ? L"Press Start to run it again." : FailText();
        a = L"Start again";
    } else {
        title = L"Starting the download engine";
        body = L"Your downloads show up in a moment.";
    }
    float w = std::min(area.right - area.left - 48, 460.0f), x = (area.left + area.right - w) / 2;
    float bh = TextH(Fmt(13.5f, 500, kWrap | kCenter), body, w);
    float total = 30 + 10 + bh + (a.empty() ? 0 : 24 + 38), y = (area.top + area.bottom - total) / 2;
    p.Text(Fmt(20, 700, kCenter), title, {x, y, x + w, y + 30}, mocha::text);
    p.Text(Fmt(13.5f, 500, kWrap | kCenter), body, {x, y + 40, x + w, y + 40 + bh + 4}, mocha::subtext0);
    if (a.empty()) return;
    IDWriteTextFormat* tf = Fmt(13.5f, 600, kMiddle);
    float aw = TextW(tf, a) + 40, bw = b.empty() ? 0 : TextW(tf, b) + 40, gap = b.empty() ? 0 : 10;
    float bx = (area.left + area.right - aw - bw - gap) / 2, by = y + 40 + bh + 24;
    D2D1_RECT_F ra{bx, by, bx + aw, by + 38};
    DrawButton(p, ra, a, 0, kPrimary, m.glow.Of(kIdNoticeA), true);
    m.hits.push_back({kIdNoticeA, ra});
    if (!b.empty()) {
        D2D1_RECT_F rb{ra.right + gap, by, ra.right + gap + bw, by + 38};
        DrawButton(p, rb, b, 0, kPlain, m.glow.Of(kIdNoticeB), true);
        m.hits.push_back({kIdNoticeB, rb});
    }
}

void DrawEmpty(Pt& p, const D2D1_RECT_F& area) {
    std::wstring title, body;
    if (g_main.all.empty()) {
        title = L"No downloads yet";
        body = L"Copy a link and press Ctrl+V, or click Add link. Downloads from your browser land here too.";
    } else if (!g_main.query.empty()) {
        title = L"Nothing matches that search";
        body = L"Try fewer words, or clear the search box.";
    } else {
        title = L"Nothing here right now";
        body = L"Downloads show up here when they fit this view.";
    }
    float w = std::min(area.right - area.left - 48, 440.0f), x = (area.left + area.right - w) / 2;
    float bh = TextH(Fmt(13.5f, 500, kWrap | kCenter), body, w), y = (area.top + area.bottom - 40 - bh) / 2;
    p.Glyph(Fmt(34, 400, kIcon | kCenter | kMiddle), 0xE896, {x, y - 56, x + w, y - 10}, mocha::overlay1);
    p.Text(Fmt(18, 700, kCenter), title, {x, y, x + w, y + 28}, mocha::text);
    p.Text(Fmt(13.5f, 500, kWrap | kCenter), body, {x, y + 36, x + w, y + 40 + bh}, mocha::subtext0);
}

float MaxScroll() {
    float rows = g_main.listRect.bottom - g_main.listRect.top - kHeadH - 8;
    return std::max(0.0f, g_main.view.size() * kRowH - rows);
}

void DrawList(Pt& p, const D2D1_RECT_F& dock) {
    MainWin& m = g_main;
    float rad = Radius();
    p.Round(dock, rad, mocha::mantle, 0.18f);
    p.Edge(dock, rad, mocha::surface2, 1);
    D2D1_RECT_F inner{dock.left + 2, dock.top + 2, dock.right - 2, dock.bottom - 2};
    if (!Running() || g_fetching.load()) {
        DrawNotice(p, inner);
        return;
    }
    m.cols = ShownCols(inner.right - inner.left - 32);
    std::vector<std::pair<int, std::pair<float, float>>> spans;
    ColumnSpans(inner.left + 12, inner.right - 20, spans);
    float hy = inner.top;
    for (auto& s : spans) {
        int k = s.first;
        D2D1_RECT_F r{s.second.first, hy + 4, s.second.second - 4, hy + kHeadH - 2};
        int id = kIdCol + k;
        float g = m.glow.Of(id);
        p.Round(r, CtlRadius(), mocha::surface0, 0.5f * g);
        bool on = m.sortCol == k;
        p.Text(Fmt(12, on ? 700 : 600, kMiddle), kCols[k].name, {r.left + 10, r.top, r.right - 22, r.bottom}, on ? mocha::text : mocha::subtext0);
        if (on) p.Glyph(Fmt(10, 400, kIcon | kCenter | kMiddle), (WCHAR)(m.sortDesc ? 0xE70D : 0xE70E), {r.right - 22, r.top, r.right - 6, r.bottom}, mocha::blue);
        m.hits.push_back({id, r});
    }
    p.Line(inner.left + 12, hy + kHeadH + 1, inner.right - 12, hy + kHeadH + 1, mocha::surface1, 0.9f);
    D2D1_RECT_F rows{inner.left, hy + kHeadH + 4, inner.right, inner.bottom - 4};
    if (m.view.empty()) {
        DrawEmpty(p, rows);
        return;
    }
    m.scroll = std::clamp(m.scroll, 0.0f, MaxScroll());
    p.rt->PushAxisAlignedClip(rows, D2D1_ANTIALIAS_MODE_ALIASED);
    int first = std::max(0, (int)(m.scroll / kRowH));
    for (int i = first; i < (int)m.view.size(); i++) {
        float y = rows.top + i * kRowH - m.scroll;
        if (y > rows.bottom) break;
        const Dl& d = m.all[m.view[i]];
        D2D1_RECT_F r{inner.left + 6, y + 2, inner.right - 14, y + kRowH - 2};
        int id = kIdRow + i;
        float g = m.glow.Of(id);
        bool selected = m.sel.count(d.id) != 0;
        if (selected) {
            p.GradFill(r, CtlRadius(), 0.16f + 0.06f * g);
            p.GradEdge(r, CtlRadius(), 0.55f + 0.45f * g);
        } else {
            p.Round(r, CtlRadius(), mocha::surface0, 0.45f * g);
            p.GradEdge(r, CtlRadius(), g * 0.8f);
        }
        if (d.id == m.focusId && GetFocus() == m.hwnd && !selected) p.Edge(r, CtlRadius(), mocha::overlay0, 0.6f);
        bool decimal = m.decimal;
        for (auto& s : spans) {
            D2D1_RECT_F c{s.second.first + 10, r.top, s.second.second - 8, r.bottom};
            switch (s.first) {
                case 0:
                    p.Text(Fmt(13.5f, 500, kMiddle), d.name.empty() ? d.url : d.name, c, mocha::text);
                    break;
                case 1:
                    p.Text(Fmt(12.5f, 500, kMiddle), d.size >= 0 ? SizeText(d.size, decimal) : std::wstring(L"Not known"), c,
                           d.size >= 0 ? mocha::subtext1 : mocha::overlay1);
                    break;
                case 2: {
                    int tone = 0;
                    std::wstring st = StatusText(d, tone);
                    bool bar = !d.done() && d.size > 0 && (d.downloaded > 0 || d.running());
                    D2D1_RECT_F t = c;
                    if (bar) t.bottom -= 8;
                    p.Text(Fmt(12.5f, 600, kMiddle), st, t, ToneColor(tone));
                    if (bar) {
                        D2D1_RECT_F track{c.left, c.bottom - 13, c.right - 8, c.bottom - 9};
                        p.Round(track, 2, mocha::surface1, 0.9f);
                        float f = std::clamp((float)d.downloaded / (float)d.size, 0.0f, 1.0f);
                        if (f > 0) p.GradFill({track.left, track.top, track.left + (track.right - track.left) * f, track.bottom}, 2, 1);
                    }
                    break;
                }
                case 3:
                    if (d.running()) p.Text(Fmt(12.5f, 500, kMiddle), SpeedText(d.speed, decimal), c, mocha::subtext1);
                    break;
                case 4:
                    if (d.running() && d.eta >= 0) p.Text(Fmt(12.5f, 500, kMiddle), EtaText(d.eta), c, mocha::subtext1);
                    break;
                case 5:
                    p.Text(Fmt(12.5f, 500, kMiddle), WhenText(d.added), c, mocha::subtext0);
                    break;
            }
        }
        m.hits.push_back({id, {r.left, std::max(r.top, rows.top), r.right, std::min(r.bottom, rows.bottom)}});
    }
    p.rt->PopAxisAlignedClip();
    float max = MaxScroll();
    if (max > 0) {
        float trackH = rows.bottom - rows.top - 8, thumbH = std::max(36.0f, trackH * trackH / (trackH + max));
        float t = rows.top + 4 + (trackH - thumbH) * (m.scroll / max);
        m.trackTop = rows.top + 4;
        m.trackH = trackH;
        m.thumbH = thumbH;
        D2D1_RECT_F track{inner.right - 12, rows.top + 4, inner.right - 4, rows.bottom - 4};
        D2D1_RECT_F thumb{inner.right - 11, t, inner.right - 5, t + thumbH};
        float g = std::max(m.glow.Of(kIdThumb), m.dragThumb ? 1.0f : 0.0f);
        p.Round(thumb, 3, mocha::surface2, 0.8f * (1 - g));
        p.GradFill(thumb, 3, g);
        m.hits.push_back({kIdTrack, track});
        m.hits.push_back({kIdThumb, {thumb.left - 3, thumb.top, thumb.right + 3, thumb.bottom}});
    }
}

void DrawStatus(Pt& p, float top) {
    MainWin& m = g_main;
    int r = 0, w = 0;
    int64_t speed = 0;
    for (auto& d : m.all) {
        if (d.running()) {
            r++;
            speed += d.speed;
        }
        if (d.waiting()) w++;
    }
    std::wstring text;
    if (!Running()) text = L"Download engine not running";
    else if (!r && !w) text = L"Nothing downloading";
    else if (r && w) text = std::to_wstring(r) + L" downloading, " + std::to_wstring(w) + L" waiting";
    else if (r) text = std::to_wstring(r) + L" downloading";
    else text = std::to_wstring(w) + L" waiting";
    if (r) text += L"  ·  " + SpeedText(speed, m.decimal);
    float h = kStatusH;
    p.Text(Fmt(12.5f, 500, kMiddle), text, {kGap + 12, top, m.cw * 0.6f, top + h}, mocha::subtext0);
    bool on = Running() && m.apiUp;
    std::wstring link = on ? L"Browser link on" : L"Browser link off";
    float lw = TextW(Fmt(12.5f, 500, kMiddle), link);
    float x = m.cw - kGap - 12 - lw;
    p.rt->FillEllipse(D2D1::Ellipse({x - 12, top + h / 2}, 4, 4), p.B(on ? mocha::green : mocha::overlay0));
    p.Text(Fmt(12.5f, 500, kMiddle), link, {x, top, m.cw - kGap - 6, top + h}, on ? mocha::subtext1 : mocha::overlay1);
}

void DrawToast(Pt& p) {
    MainWin& m = g_main;
    if (m.toast.empty()) return;
    ULONGLONG age = GetTickCount64() - m.toastAt;
    if (age > kToastMs) {
        m.toast.clear();
        return;
    }
    float a = std::min({1.0f, age / 150.0f, (kToastMs - age) / 250.0f});
    IDWriteTextFormat* tf = Fmt(13.5f, 600, kMiddle | kCenter);
    float w = std::min(TextW(tf, m.toast) + 48, m.cw - 40), h = 40;
    float x = (m.cw - w) / 2, y = m.ch - kStatusH - h - 18 + (1 - a) * 8;
    D2D1_RECT_F r{x, y, x + w, y + h};
    // A floating pill over the list: solid, never see-through.
    p.Round(r, h / 2, mocha::base, a);
    if (m.toastBad) p.Edge(r, h / 2, mocha::red, a);
    else p.GradEdge(r, h / 2, a);
    p.Text(tf, m.toast, r, m.toastBad ? mocha::red : mocha::text, a);
}

void Main_Paint() {
    MainWin& m = g_main;
    if (!m.hwnd) return;
    if (!m.rt) {
        RECT rc;
        GetClientRect(m.hwnd, &rc);
        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
            (float)m.dpi, (float)m.dpi);
        if (FAILED(g_gfx.d2d->CreateHwndRenderTarget(
                props, D2D1::HwndRenderTargetProperties(m.hwnd, D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom))),
                m.rt.put())))
            return;
    }
    m.hits.clear();
    Pt p(m.rt.get());
    m.rt->BeginDraw();
    m.rt->SetTransform(D2D1::Matrix3x2F::Identity());
    PaintBody(p, m.cw, m.ch, kMainTint);
    float side = SideW(), left = kGap + side + kGap, right = m.cw - kGap;
    float bottom = m.ch - kStatusH;
    DrawSidebar(p, kGap, bottom);
    DrawToolbar(p, left, right, kGap - 4);
    m.listRect = {left, kGap + kToolH, right, bottom};
    DrawList(p, m.listRect);
    DrawStatus(p, bottom);
    DrawToast(p);
    if (m.rt->EndDraw() == D2DERR_RECREATE_TARGET) m.rt.reset();
    // The search box follows the drawn box.
    if (m.search) {
        D2D1_RECT_F s = m.searchRect;
        int x = (int)Px(s.left + 32), y = (int)Px(s.top + 8), w = (int)Px(s.right - s.left - 40), h = (int)Px(s.bottom - s.top - 16);
        RECT cur;
        GetWindowRect(m.search, &cur);
        MapWindowPoints(nullptr, m.hwnd, (POINT*)&cur, 2);
        if (cur.left != x || cur.top != y || cur.right - cur.left != w || cur.bottom - cur.top != h)
            SetWindowPos(m.search, nullptr, x, y, std::max(10, w), std::max(10, h), SWP_NOZORDER | SWP_NOACTIVATE);
        if (!IsWindowVisible(m.search)) ShowWindow(m.search, SW_SHOWNA);
    }
}

// ---- Input ---------------------------------------------------------------------------

void SetFilter(const std::string& f) {
    g_main.filter = f;
    g_main.scroll = 0;
    g_main.sel.clear();
    RebuildView();
    Main_Invalidate();
}

int RowAt(float y) {
    float top = g_main.listRect.top + 2 + kHeadH + 4;
    int i = (int)((y - top + g_main.scroll) / kRowH);
    return i >= 0 && i < (int)g_main.view.size() ? i : -1;
}

void EnsureRowVisible(int i) {
    float rows = g_main.listRect.bottom - g_main.listRect.top - kHeadH - 8;
    float top = i * kRowH;
    if (top < g_main.scroll) g_main.scroll = top;
    else if (top + kRowH > g_main.scroll + rows) g_main.scroll = top + kRowH - rows;
    g_main.scroll = std::clamp(g_main.scroll, 0.0f, MaxScroll());
}

void ClickRow(int i, bool ctrl, bool shift) {
    MainWin& m = g_main;
    int64_t id = m.all[m.view[i]].id;
    if (shift && m.anchor >= 0) {
        int a = -1;
        for (int k = 0; k < (int)m.view.size(); k++)
            if (m.all[m.view[k]].id == m.anchor) a = k;
        if (a >= 0) {
            if (!ctrl) m.sel.clear();
            for (int k = std::min(a, i); k <= std::max(a, i); k++) m.sel.insert(m.all[m.view[k]].id);
        }
    } else if (ctrl) {
        if (!m.sel.erase(id)) m.sel.insert(id);
        m.anchor = id;
    } else {
        m.sel = {id};
        m.anchor = id;
    }
    m.focusId = id;
}

void Main_Action(int id) {
    MainWin& m = g_main;
    switch (id) {
        case kIdAdd: OpenAddDialog(nullptr, ClipboardLink()); break;
        case kIdAddMany: OpenAddMany(); break;
        case kIdResume: DoResume(Selected()); break;
        case kIdPause: DoPause(Selected()); break;
        case kIdRemove:
            if (!Selected().empty()) OpenRemoveDialog(Selected());
            break;
        case kIdQueue:
            if (FilterQueue() >= 0) ToggleQueue(FilterQueue());
            break;
        case kIdPauseAll: DoSimple("pause_all"); break;
        case kIdNoticeA:
            if (g_state.load() == State::Missing) FetchEngine();
            else {
                g_restart = true;
                Wake();
            }
            break;
        case kIdNoticeB:
            if (!OpenWorkshop()) Toast(L"Seamless Workshop is not open. Turn it on in Windhawk.", true);
            break;
        case kIdManage: OpenQueuesPage(FilterQueue()); break;
        case kIdSettings: OpenSettings(); break;
        case kIdAbout: OpenAboutPage(); break;
        default:
            if (id >= kIdCol && id < kIdCol + 6) {
                int k = id - kIdCol;
                if (m.sortCol == k) m.sortDesc = !m.sortDesc;
                else {
                    m.sortCol = k;
                    m.sortDesc = k == 5 || k == 1 || k == 3;
                }
                RebuildView();
            } else if (id >= kIdSide && id < kIdSide + 4) {
                static const char* f[] = {"all", "running", "done", "unfinished"};
                SetFilter(f[id - kIdSide]);
            } else if (id >= kIdCat && id < kIdCat + (int)m.cats.size()) {
                SetFilter("cat:" + std::to_string(m.cats[id - kIdCat].id));
            } else if (id >= kIdQueueRow && id < kIdQueueRow + (int)m.queues.size()) {
                SetFilter("queue:" + std::to_string(m.queues[id - kIdQueueRow].id));
            }
    }
    Main_Invalidate();
}

void Main_UpdateHover() {
    MainWin& m = g_main;
    int h = m.mx < 0 ? -1 : HitAt(m.hits, m.mx, m.my);
    if (h != m.hover) {
        m.hover = h;
        Main_StartTimer();
        Main_Invalidate();
    }
}

bool Main_Key(UINT vk) {
    MainWin& m = g_main;
    bool ctrl = GetKeyState(VK_CONTROL) < 0, shift = GetKeyState(VK_SHIFT) < 0;
    if (ctrl && vk == 'V' && Running()) {
        OpenAddDialog(nullptr, ClipboardLink());
        return true;
    }
    if (ctrl && vk == 'F' && m.search) {
        SetFocus(m.search);
        return true;
    }
    if (m.view.empty() || !Running()) return false;
    int cur = -1;
    for (int k = 0; k < (int)m.view.size(); k++)
        if (m.all[m.view[k]].id == m.focusId) cur = k;
    switch (vk) {
        case 'A':
            if (!ctrl) return false;
            for (int i : m.view) m.sel.insert(m.all[i].id);
            break;
        case VK_UP:
        case VK_DOWN:
        case VK_HOME:
        case VK_END:
        case VK_PRIOR:
        case VK_NEXT: {
            int page = std::max(1, (int)((m.listRect.bottom - m.listRect.top - kHeadH) / kRowH) - 1);
            int n = (int)m.view.size();
            int next = vk == VK_UP ? cur - 1 : vk == VK_DOWN ? cur + 1 : vk == VK_HOME ? 0 : vk == VK_END ? n - 1
                     : vk == VK_PRIOR ? cur - page : cur + page;
            if (cur < 0) next = 0;
            next = std::clamp(next, 0, n - 1);
            ClickRow(next, false, shift);
            EnsureRowVisible(next);
            break;
        }
        case VK_RETURN:
            if (const Dl* d = FindDl(m.focusId)) DefaultAction(*d);
            break;
        case VK_DELETE:
            if (!Selected().empty()) OpenRemoveDialog(Selected());
            break;
        case VK_APPS: {
            if (cur < 0) return false;
            POINT pt{(LONG)Px(m.listRect.left + 60), (LONG)Px(m.listRect.top + kHeadH + (cur + 1) * kRowH - m.scroll)};
            ClientToScreen(m.hwnd, &pt);
            RowMenu(pt);
            break;
        }
        default: return false;
    }
    Main_Invalidate();
    return true;
}

LRESULT CALLBACK SearchProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    if (msg == WM_KEYDOWN && (wp == VK_ESCAPE || wp == VK_DOWN || wp == VK_RETURN)) {
        if (wp == VK_ESCAPE) SetWindowTextW(hwnd, L"");
        SetFocus(GetParent(hwnd));
        return 0;
    }
    if (msg == WM_CHAR && (wp == VK_ESCAPE || wp == VK_RETURN)) return 0;
    if (msg == WM_SETFOCUS || msg == WM_KILLFOCUS) Main_Invalidate();
    return DefSubclassProc(hwnd, msg, wp, lp);
}

void Main_MakeSearch() {
    MainWin& m = g_main;
    if (m.search) DestroyWindow(m.search);
    if (m.searchFont) DeleteObject(m.searchFont);
    m.search = CreateWindowExW(g_glass ? WS_EX_LAYERED : 0, L"EDIT", L"", WS_CHILD | ES_AUTOHSCROLL, 0, 0, 10, 10, m.hwnd, (HMENU)(INT_PTR)kIdSearch,
                               (HINSTANCE)&__ImageBase, nullptr);
    if (!m.search) return;
    if (g_glass) SetLayeredWindowAttributes(m.search, 0, 255, LWA_ALPHA);
    m.searchFont = CreateFontW(-MulDiv(13, m.dpi, 96), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                               CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, g_gfx.family.c_str());
    SendMessageW(m.search, WM_SETFONT, (WPARAM)m.searchFont, TRUE);
    SendMessageW(m.search, EM_SETCUEBANNER, TRUE, (LPARAM)L"Search");
    SetWindowTheme(m.search, L"DarkMode_Explorer", nullptr);
    SetWindowSubclass(m.search, SearchProc, 1, 0);
    SetWindowTextW(m.search, m.query.c_str());
}

void Main_SaveRect() {
    MainWin& m = g_main;
    if (!m.hwnd || IsIconic(m.hwnd) || IsZoomed(m.hwnd) || !IsWindowVisible(m.hwnd)) return;
    RECT r;
    GetWindowRect(m.hwnd, &r);
    Wh_SetIntValue(L"MainX", r.left);
    Wh_SetIntValue(L"MainY", r.top);
    Wh_SetIntValue(L"MainCX", r.right - r.left);
    Wh_SetIntValue(L"MainCY", r.bottom - r.top);
}

LRESULT CALLBACK MainProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    MainWin& m = g_main;
    switch (msg) {
        case WM_ERASEBKGND: return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            Main_Paint();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_SIZE:
            if (wp != SIZE_MINIMIZED) {
                RECT rc;
                GetClientRect(hwnd, &rc);
                m.cw = rc.right * 96.0f / m.dpi;
                m.ch = rc.bottom * 96.0f / m.dpi;
                if (!IsWindowVisible(hwnd)) m.rt.reset();
                else if (m.rt) m.rt->Resize(D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom)));
                Main_Invalidate();
            }
            return 0;
        case WM_GETMINMAXINFO: {
            auto* mm = (MINMAXINFO*)lp;
            mm->ptMinTrackSize = {(LONG)Px(420), (LONG)Px(360)};
            return 0;
        }
        case WM_DPICHANGED: {
            m.dpi = HIWORD(wp);
            if (m.rt) m.rt->SetDpi((float)m.dpi, (float)m.dpi);
            Main_MakeSearch();
            const RECT* r = (const RECT*)lp;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top, SWP_NOZORDER | SWP_NOACTIVATE);
            return 0;
        }
        case WM_CTLCOLOREDIT: {
            HDC dc = (HDC)wp;
            SetTextColor(dc, RefFromRgb(mocha::text));
            SetBkColor(dc, RefFromRgb(acset::kSetBoxFill));
            return (LRESULT)m.boxBrush;
        }
        case WM_COMMAND:
            if (LOWORD(wp) == kIdSearch && HIWORD(wp) == EN_CHANGE) {
                std::wstring t(GetWindowTextLengthW(m.search) + 1, L'\0');
                t.resize(GetWindowTextW(m.search, t.data(), (int)t.size()));
                m.query = Lower(t);
                m.scroll = 0;
                RebuildView();
                Main_Invalidate();
            }
            return 0;
        case WM_MOUSEMOVE: {
            m.mx = GET_X_LPARAM(lp) * 96.0f / m.dpi;
            m.my = GET_Y_LPARAM(lp) * 96.0f / m.dpi;
            if (!m.tracking) {
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                m.tracking = TrackMouseEvent(&t);
            }
            if (m.dragThumb) {
                float max = MaxScroll(), span = std::max(1.0f, m.trackH - m.thumbH);
                m.scroll = std::clamp((m.my - m.dragOff - m.trackTop) / span * max, 0.0f, max);
                Main_Invalidate();
            }
            Main_UpdateHover();
            return 0;
        }
        case WM_MOUSELEAVE:
            m.tracking = false;
            m.mx = m.my = -1;
            Main_UpdateHover();
            return 0;
        case WM_MOUSEWHEEL: {
            m.scroll = std::clamp(m.scroll - GET_WHEEL_DELTA_WPARAM(wp) / 120.0f * kRowH * 3, 0.0f, MaxScroll());
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            ScreenToClient(hwnd, &pt);
            m.mx = pt.x * 96.0f / m.dpi;
            m.my = pt.y * 96.0f / m.dpi;
            Main_Invalidate();
            UpdateWindow(hwnd);
            Main_UpdateHover();
            return 0;
        }
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK: {
            SetFocus(hwnd);
            float x = GET_X_LPARAM(lp) * 96.0f / m.dpi, y = GET_Y_LPARAM(lp) * 96.0f / m.dpi;
            int id = HitAt(m.hits, x, y);
            if (id == kIdSearch) {
                if (m.search) SetFocus(m.search);
                return 0;
            }
            if (id == kIdThumb) {
                m.dragThumb = true;
                float max = MaxScroll();
                m.dragOff = y - (m.trackTop + (m.trackH - m.thumbH) * (max > 0 ? m.scroll / max : 0));
                SetCapture(hwnd);
                return 0;
            }
            if (id == kIdTrack) {
                float rows = m.listRect.bottom - m.listRect.top - kHeadH;
                float thumbY = m.trackTop + (m.trackH - m.thumbH) * (MaxScroll() > 0 ? m.scroll / MaxScroll() : 0);
                m.scroll = std::clamp(m.scroll + (y < thumbY ? -rows : rows), 0.0f, MaxScroll());
                Main_Invalidate();
                return 0;
            }
            if (id >= kIdRow) {
                int i = id - kIdRow;
                if (i >= (int)m.view.size()) return 0;
                int64_t did = m.all[m.view[i]].id;
                ULONGLONG now = GetTickCount64();
                bool dbl = msg == WM_LBUTTONDBLCLK || (did == m.lastClickId && now - m.lastClick < GetDoubleClickTime());
                ClickRow(i, (wp & MK_CONTROL) != 0, (wp & MK_SHIFT) != 0);
                m.lastClick = dbl ? 0 : now;
                m.lastClickId = did;
                if (dbl && !(wp & (MK_CONTROL | MK_SHIFT)))
                    if (const Dl* d = FindDl(did)) DefaultAction(*d);
                Main_Invalidate();
                return 0;
            }
            if (id < 0 && In(m.listRect, x, y)) {
                m.sel.clear();
                Main_Invalidate();
                return 0;
            }
            m.pressed = id;
            if (id >= 0) SetCapture(hwnd);
            Main_StartTimer();
            Main_Invalidate();
            return 0;
        }
        case WM_LBUTTONUP: {
            if (GetCapture() == hwnd) ReleaseCapture();
            if (m.dragThumb) {
                m.dragThumb = false;
                Main_Invalidate();
                return 0;
            }
            float x = GET_X_LPARAM(lp) * 96.0f / m.dpi, y = GET_Y_LPARAM(lp) * 96.0f / m.dpi;
            int id = HitAt(m.hits, x, y), was = m.pressed;
            m.pressed = -1;
            if (was >= 0 && id == was) Main_Action(id);
            Main_Invalidate();
            return 0;
        }
        case WM_RBUTTONUP: {
            float x = GET_X_LPARAM(lp) * 96.0f / m.dpi, y = GET_Y_LPARAM(lp) * 96.0f / m.dpi;
            int id = HitAt(m.hits, x, y);
            if (id >= kIdRow && id - kIdRow < (int)m.view.size()) {
                int i = id - kIdRow;
                int64_t did = m.all[m.view[i]].id;
                if (!m.sel.count(did)) ClickRow(i, false, false);
                m.focusId = did;
                Main_Invalidate();
                UpdateWindow(hwnd);
                POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
                ClientToScreen(hwnd, &pt);
                RowMenu(pt);
                Main_Invalidate();
            }
            return 0;
        }
        case WM_CAPTURECHANGED:
            if (m.dragThumb && (HWND)lp != hwnd) m.dragThumb = false;
            return 0;
        case WM_KEYDOWN:
            if (Main_Key((UINT)wp)) return 0;
            break;
        case WM_SETFOCUS:
        case WM_KILLFOCUS:
            Main_Invalidate();
            break;
        case WM_TIMER:
            if (wp == kMainTimer) {
                bool moving = m.glow.Step(m.hover, m.pressed);
                if (!m.toast.empty()) moving = true;
                Main_Invalidate();
                if (!moving) {
                    KillTimer(hwnd, kMainTimer);
                    m.timer = false;
                }
            }
            return 0;
        case WM_ACTIVATE:
            Main_Invalidate();
            break;
        case WM_CLOSE:
            // Closing hides the window to the tray; downloads keep going.
            Main_SaveRect();
            ShowWindow(hwnd, SW_HIDE);
            g_shown = false;
            return 0;
        case WM_SHOWWINDOW:
            g_shown = wp != 0;
            if (wp) {
                Refresh();
                Main_Invalidate();
            }
            break;
        case WM_EXITSIZEMOVE:
            Main_SaveRect();
            break;
        case WM_DESTROY:
            m.rt.reset();
            m.search = nullptr;
            m.hwnd = nullptr;
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

HICON g_iconSmall = nullptr, g_iconBig = nullptr;

bool Main_Create() {
    MainWin& m = g_main;
    if (m.hwnd) return true;
    if (!Gfx_Init()) return false;
    g_radius = acset::Set_MenuCornerRadius();
    g_glass = Wh_GetIntSetting(L"settingsGlass") != 0;
    WNDCLASSEXW wc{sizeof(wc)};
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = MainProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kMainClass;
    wc.hIcon = g_iconBig;
    wc.hIconSm = g_iconSmall;
    RegisterClassExW(&wc);
    if (!m.boxBrush) m.boxBrush = CreateSolidBrush(RefFromRgb(acset::kSetBoxFill));
    HWND hwnd = CreateWindowExW(0, kMainClass, kAppTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, 1100, 700,
                                nullptr, nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (!hwnd) return false;
    m.hwnd = hwnd;
    m.dpi = GetDpiForWindow(hwnd);
    if (g_iconSmall) SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)g_iconSmall);
    if (g_iconBig) SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)g_iconBig);
    Sdm_ApplyGlass(hwnd);
    Main_MakeSearch();
    // Where it was last time, when that is still on a screen; otherwise centred on the main screen.
    RECT r{Wh_GetIntValue(L"MainX", 0), Wh_GetIntValue(L"MainY", 0), 0, 0};
    int cx = Wh_GetIntValue(L"MainCX", 0), cy = Wh_GetIntValue(L"MainCY", 0);
    r.right = r.left + cx;
    r.bottom = r.top + cy;
    if (cx <= 0 || cy <= 0 || !MonitorFromRect(&r, MONITOR_DEFAULTTONULL)) {
        MONITORINFO mi{sizeof(mi)};
        GetMonitorInfoW(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY), &mi);
        int w = std::min((int)Px(1120), (int)(mi.rcWork.right - mi.rcWork.left) * 9 / 10);
        int h = std::min((int)Px(720), (int)(mi.rcWork.bottom - mi.rcWork.top) * 9 / 10);
        r = {(mi.rcWork.left + mi.rcWork.right - w) / 2, (mi.rcWork.top + mi.rcWork.bottom - h) / 2, 0, 0};
        r.right = r.left + w;
        r.bottom = r.top + h;
    }
    SetWindowPos(hwnd, nullptr, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_NOZORDER | SWP_NOACTIVATE);
    m.dpi = GetDpiForWindow(hwnd);
    return true;
}

// Shows the window. activate: the owner asked for it (tray, a link), so it may come to the front.
void Main_Show(bool activate) {
    if (!Main_Create()) return;
    HWND hwnd = g_main.hwnd;
    if (activate) {
        if (IsIconic(hwnd)) ShowWindow(hwnd, SW_RESTORE);
        else ShowWindow(hwnd, SW_SHOW);
        SetForegroundWindow(hwnd);
    } else if (!IsWindowVisible(hwnd)) {
        ShowWindow(hwnd, SW_SHOWNOACTIVATE);
    }
    RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
    g_shown = true;
    Wake();
}

void Main_Destroy() {
    MainWin& m = g_main;
    if (m.hwnd) {
        Main_SaveRect();
        DestroyWindow(m.hwnd);
    }
    if (m.searchFont) DeleteObject(m.searchFont);
    m.searchFont = nullptr;
    if (m.boxBrush) DeleteObject(m.boxBrush);
    m.boxBrush = nullptr;
    UnregisterClassW(kMainClass, (HINSTANCE)&__ImageBase);
}

// A poll result from the engine thread.
void Main_Apply(PollResult& r) {
    MainWin& m = g_main;
    bool rebuild = false;
    if (r.hasDownloads) {
        m.all = std::move(r.downloads);
        m.haveData = true;
        rebuild = true;
    }
    if (r.hasQueues) {
        m.queues = std::move(r.queues);
        rebuild = true;
        if (FilterQueue() >= 0 && !FindQueue(FilterQueue())) m.filter = "all";
    }
    if (r.hasCats) {
        m.cats = std::move(r.cats);
        bool found = FilterCat() < 0;
        for (auto& c : m.cats)
            if (c.id == FilterCat()) found = true;
        if (!found) m.filter = "all";
        rebuild = true;
    }
    if (r.hasSettings) {
        m.settings = std::move(r.settings);
        const std::string& u = m.settings["size_unit"].str();
        m.decimal = u.find("Decimal") != std::string::npos;
    }
    if (r.hasStatus) {
        m.status = std::move(r.status);
        m.apiUp = m.status["api_up"].truthy();
    }
    if (rebuild) RebuildView();
    Main_Invalidate();
    if (r.hasQueues || r.hasDownloads) Queues_Changed();
}

}  // namespace sdm

// ===========================================================================
// The small windows: add a link, add many, remove, speed limit, check file, the
// power countdown and the site rules. One drawn form engine, the Mocha look and the
// same glass as the main window. Everything runs on the UI thread.
// ===========================================================================
namespace sdm {

// ---- Engine jobs: started here, checked four times a second ---------------------------

using JobDone = std::function<void(bool ok, const Val& result, const std::wstring& err)>;
struct JobWait {
    int64_t job;
    JobDone done;
};
std::vector<JobWait> g_jobs;
UINT_PTR g_jobTimer = 0;

void CALLBACK JobTick(HWND, UINT, UINT_PTR, DWORD) {
    std::vector<JobWait> keep;
    std::vector<std::pair<JobWait, Val>> finished;
    for (auto& j : g_jobs) {
        Val req = Cmd("job");
        req.set("job", sj::Int(j.job));
        Val v = Call(req);
        if (!v.has("error") && !v["done"].truthy()) keep.push_back(std::move(j));
        else finished.emplace_back(std::move(j), std::move(v));
    }
    g_jobs = std::move(keep);
    if (g_jobs.empty() && g_jobTimer) {
        KillTimer(nullptr, g_jobTimer);
        g_jobTimer = 0;
    }
    for (auto& [j, v] : finished) {
        if (v.has("error")) j.done(false, Val::None(), ErrorOf(v));
        else if (v["ok"].truthy()) j.done(true, v["result"], L"");
        else j.done(false, Val::None(), sj::W(v["error"].str()));
    }
}

// Starts a slow engine command (a link check, a file check, an update check). done runs later, here.
void StartJob(const Val& req, JobDone done) {
    Val v = Call(req);
    if (v.has("error") || !v.has("job")) {
        std::wstring e = ErrorOf(v);
        done(false, Val::None(), e.empty() ? L"The engine did not take the job" : e);
        return;
    }
    g_jobs.push_back({v["job"].num(), std::move(done)});
    if (!g_jobTimer) g_jobTimer = SetTimer(nullptr, 0, 250, JobTick);
}

void Jobs_Stop() {
    if (g_jobTimer) KillTimer(nullptr, g_jobTimer);
    g_jobTimer = 0;
    g_jobs.clear();
}

// ---- The form engine -------------------------------------------------------------------

enum CtlKind { cHead, cText, cEdit, cSwitch, cChoice, cButtons, cNote, cChips, cLine, cBar };

struct FBtn {
    int id;
    std::wstring label;
    int style = kPlain;
    WCHAR icon = 0;
    bool enabled = true;
};

struct FCtl {
    int kind = cText, id = 0;
    std::wstring label, hint, text, placeholder;
    bool on = false, enabled = true, visible = true, password = false, half = false, readOnly = false;
    int choice = 0, lines = 1;
    float boxW = 0;  // A fixed box width; 0 fills the line.
    std::vector<std::wstring> options;
    std::vector<FBtn> buttons;  // cButtons; on cEdit, buttons[0] is the side button.
    uint32_t mask = 0;          // cChips: one bit per chip.
    UINT32 tone = mocha::subtext0;
    float progress = 0;
    HWND edit = nullptr;
    D2D1_RECT_F r{}, box{}, side{};
};

constexpr float kFormW = 520, kFormPad = 22, kFormGap = 14, kBoxH = 36, kBtnH = 38;
constexpr UINT_PTR kFormAnim = 1, kFormTick = 2;
constexpr WCHAR kFormClass[] = L"SeamlessDownloadManagerForm";

struct Form {
    std::string key;
    uint64_t serial = 0;
    HWND hwnd = nullptr;
    bool dead = false, tracking = false, animating = false, muted = false;
    SetCom<ID2D1HwndRenderTarget> rt;
    UINT dpi = 96;
    float cw = kFormW, ch = 300, scroll = 0, contentH = 0;
    std::wstring title;
    std::vector<FCtl> ctls;
    std::vector<Hit> hits;
    Glow glow;
    int hover = -1, pressed = -1;
    float mx = -1, my = -1;
    HFONT font = nullptr;
    HBRUSH box = nullptr;
    HWND lastFocus = nullptr;
    int defaultBtn = 0, cancelBtn = 0;
    UINT tickMs = 0;
    std::function<void(Form&, int)> onButton, onChange;
    std::function<void(Form&)> onTick, onClose;
    int64_t tag = 0;
    Val data;
};

std::vector<std::unique_ptr<Form>> g_forms;
uint64_t g_formSerial = 0;
int g_formDepth = 0;  // Inside a form callback: dead forms wait to be dropped.

struct FormCall {
    FormCall() { g_formDepth++; }
    ~FormCall() { g_formDepth--; }
};

void Form_Sweep() {
    if (g_formDepth) return;
    g_forms.erase(std::remove_if(g_forms.begin(), g_forms.end(), [](auto& f) { return f->dead; }), g_forms.end());
}

Form* Form_Find(const std::string& key) {
    for (auto& f : g_forms)
        if (!f->dead && f->key == key) return f.get();
    return nullptr;
}

Form* Form_BySerial(uint64_t serial) {
    for (auto& f : g_forms)
        if (!f->dead && f->serial == serial) return f.get();
    return nullptr;
}

float FPx(Form& f, float dip) { return dip * f.dpi / 96.0f; }

FCtl* Form_Ctl(Form& f, int id) {
    for (auto& c : f.ctls)
        if (c.id == id) return &c;
    return nullptr;
}

std::wstring Form_Text(Form& f, int id) {
    FCtl* c = Form_Ctl(f, id);
    if (!c) return {};
    if (c->edit) {
        std::wstring t(GetWindowTextLengthW(c->edit) + 1, L'\0');
        t.resize(GetWindowTextW(c->edit, t.data(), (int)t.size()));
        c->text = t;
    }
    return c->text;
}

std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n"), b = s.find_last_not_of(L" \t\r\n");
    return a == std::wstring::npos ? std::wstring() : s.substr(a, b - a + 1);
}

void Form_Invalidate(Form& f) {
    if (f.hwnd) InvalidateRect(f.hwnd, nullptr, FALSE);
}

void Form_SetText(Form& f, int id, const std::wstring& text) {
    FCtl* c = Form_Ctl(f, id);
    if (!c) return;
    c->text = text;
    if (c->edit) {
        f.muted = true;
        SetWindowTextW(c->edit, text.c_str());
        f.muted = false;
    }
    Form_Invalidate(f);
}

void Form_Note(Form& f, int id, const std::wstring& text, UINT32 tone);
void Form_Relayout(Form& f);

void Form_Note(Form& f, int id, const std::wstring& text, UINT32 tone) {
    FCtl* c = Form_Ctl(f, id);
    if (!c) return;
    c->text = text;
    c->tone = tone;
    Form_Relayout(f);
}

void Form_Enable(Form& f, int id, bool on) {
    FCtl* c = Form_Ctl(f, id);
    if (!c) return;
    c->enabled = on;
    if (c->edit) EnableWindow(c->edit, on);
    Form_Invalidate(f);
}

void Form_Show(Form& f, int id, bool on) {
    FCtl* c = Form_Ctl(f, id);
    if (!c || c->visible == on) return;
    c->visible = on;
    Form_Relayout(f);
}

FBtn* Form_Button(Form& f, int id) {
    for (auto& c : f.ctls)
        for (auto& b : c.buttons)
            if (b.id == id) return &b;
    return nullptr;
}

void Form_EnableButton(Form& f, int id, bool on) {
    if (FBtn* b = Form_Button(f, id)) b->enabled = on;
    Form_Invalidate(f);
}

// Builders, so each dialog reads like the app's layout.
FCtl Head(const std::wstring& t) {
    FCtl c;
    c.kind = cHead;
    c.text = t;
    return c;
}
FCtl Para(const std::wstring& t, UINT32 tone = mocha::subtext1) {
    FCtl c;
    c.kind = cText;
    c.text = t;
    c.tone = tone;
    return c;
}
FCtl Note(int id) {
    FCtl c;
    c.kind = cNote;
    c.id = id;
    return c;
}
FCtl EditBox(int id, const std::wstring& label, const std::wstring& text, const std::wstring& placeholder = L"") {
    FCtl c;
    c.kind = cEdit;
    c.id = id;
    c.label = label;
    c.text = text;
    c.placeholder = placeholder;
    return c;
}
FCtl Switch(int id, const std::wstring& label, const std::wstring& hint, bool on) {
    FCtl c;
    c.kind = cSwitch;
    c.id = id;
    c.label = label;
    c.hint = hint;
    c.on = on;
    return c;
}
FCtl Choice(int id, const std::wstring& label, std::vector<std::wstring> options, int choice) {
    FCtl c;
    c.kind = cChoice;
    c.id = id;
    c.label = label;
    c.options = std::move(options);
    c.choice = std::clamp(choice, 0, std::max(0, (int)c.options.size() - 1));
    return c;
}
FCtl Buttons(std::vector<FBtn> b) {
    FCtl c;
    c.kind = cButtons;
    c.buttons = std::move(b);
    return c;
}
FCtl Bar() {
    FCtl c;
    c.kind = cBar;
    return c;
}

// ---- Layout --------------------------------------------------------------------------

float BtnWidth(const FBtn& b) {
    return TextW(Fmt(13.5f, 600, kMiddle), b.label) + 36 + (b.icon ? 24 : 0);
}

float Form_Place(Form& f, FCtl& c, float x, float y, float w) {
    c.r = {x, y, x + w, y};
    c.box = c.side = {};
    float h = 0;
    switch (c.kind) {
        case cHead: h = TextH(Fmt(18, 700, kWrap), c.text, w) + 2; break;
        case cText: h = c.text.empty() ? 0 : TextH(Fmt(13.5f, 500, kWrap), c.text, w); break;
        case cNote: h = c.text.empty() ? 0 : TextH(Fmt(13, 600, kWrap), c.text, w); break;
        case cEdit:
        case cChoice: {
            float lh = c.label.empty() ? 0 : 22, bh = kBoxH + (c.lines - 1) * 18.0f;
            float sideW = c.kind == cEdit && !c.buttons.empty() ? BtnWidth(c.buttons[0]) : 0;
            float bw = c.boxW > 0 ? std::min(c.boxW, w) : w - (sideW > 0 ? sideW + 8 : 0);
            c.box = {x, y + lh, x + bw, y + lh + bh};
            if (sideW > 0) c.side = {c.box.right + 8, c.box.bottom - kBoxH, c.box.right + 8 + sideW, c.box.bottom};
            h = lh + bh;
            if (!c.hint.empty()) h += 6 + TextH(Fmt(12, 500, kWrap), c.hint, w);
            break;
        }
        case cSwitch: {
            float tw = w - 60;
            float lh = TextH(Fmt(13.5f, 600, kWrap), c.label, tw);
            float hh = c.hint.empty() ? 0 : 2 + TextH(Fmt(12.5f, 500, kWrap), c.hint, tw);
            h = std::max(26.0f, lh + hh);
            float sy = y + std::max(0.0f, (std::min(h, lh + 6) - 24) / 2);
            if (hh > 0) sy = y + (h - 24) / 2;
            c.box = {x + w - 44, sy, x + w, sy + 24};
            break;
        }
        case cButtons: h = kBtnH; break;
        case cChips: h = (c.label.empty() ? 0 : 22) + 30; break;
        case cLine: h = 1; break;
        case cBar: h = 6; break;
    }
    c.r.bottom = y + h;
    return h;
}

void Form_PlaceEdits(Form& f);

void Form_Layout(Form& f) {
    float W = f.cw - 2 * kFormPad, y = kFormPad;
    bool any = false;
    for (size_t i = 0; i < f.ctls.size();) {
        FCtl& c = f.ctls[i];
        if (!c.visible) {
            c.r = c.box = c.side = {};
            i++;
            continue;
        }
        if (c.half) {
            size_t j = i + 1;
            while (j < f.ctls.size() && !f.ctls[j].visible) j++;
            if (j < f.ctls.size() && f.ctls[j].half) {
                float hw = (W - 12) / 2;
                float h1 = Form_Place(f, c, kFormPad, y, hw), h2 = Form_Place(f, f.ctls[j], kFormPad + hw + 12, y, hw);
                y += std::max(h1, h2) + kFormGap;
                any = true;
                i = j + 1;
                continue;
            }
        }
        float h = Form_Place(f, c, kFormPad, y, W);
        if (h > 0) {
            y += h + kFormGap;
            any = true;
        }
        i++;
    }
    f.contentH = (any ? y - kFormGap : y) + kFormPad;
}

// Height fits the content, up to 85% of the screen; the rest scrolls.
void Form_FitWindow(Form& f, bool center) {
    if (!f.hwnd) return;
    HMONITOR mon = g_main.hwnd && IsWindowVisible(g_main.hwnd) ? MonitorFromWindow(g_main.hwnd, MONITOR_DEFAULTTONEAREST)
                                                               : MonitorFromWindow(f.hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    DWORD style = (DWORD)GetWindowLongPtrW(f.hwnd, GWL_STYLE), ex = (DWORD)GetWindowLongPtrW(f.hwnd, GWL_EXSTYLE);
    RECT want{0, 0, (LONG)FPx(f, kFormW), (LONG)FPx(f, f.contentH)};
    AdjustWindowRectExForDpi(&want, style, FALSE, ex, f.dpi);
    int w = want.right - want.left, h = want.bottom - want.top;
    int maxH = (mi.rcWork.bottom - mi.rcWork.top) * 85 / 100;
    h = std::min(h, maxH);
    RECT cur;
    GetWindowRect(f.hwnd, &cur);
    int x = cur.left, y = cur.top;
    if (center) {
        RECT over = mi.rcWork;
        if (g_main.hwnd && IsWindowVisible(g_main.hwnd) && !IsIconic(g_main.hwnd)) GetWindowRect(g_main.hwnd, &over);
        x = (over.left + over.right - w) / 2;
        y = (over.top + over.bottom - h) / 2;
    }
    x = std::clamp(x, (int)mi.rcWork.left, std::max((int)mi.rcWork.left, (int)mi.rcWork.right - w));
    y = std::clamp(y, (int)mi.rcWork.top, std::max((int)mi.rcWork.top, (int)mi.rcWork.bottom - h));
    if (!center && cur.right - cur.left == w && cur.bottom - cur.top == h && cur.left == x && cur.top == y) return;
    SetWindowPos(f.hwnd, nullptr, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE);
}

float Form_MaxScroll(Form& f) { return std::max(0.0f, f.contentH - f.ch); }

void Form_Relayout(Form& f) {
    Form_Layout(f);
    Form_FitWindow(f, false);
    f.scroll = std::clamp(f.scroll, 0.0f, Form_MaxScroll(f));
    Form_PlaceEdits(f);
    Form_Invalidate(f);
}

// The native text boxes follow their drawn boxes; one not fully in view hides.
void Form_PlaceEdits(Form& f) {
    for (auto& c : f.ctls) {
        if (!c.edit) continue;
        bool show = c.visible && c.box.bottom > c.box.top;
        float top = c.box.top - f.scroll, bottom = c.box.bottom - f.scroll;
        if (top < 0 || bottom > f.ch) show = false;
        if (!show) {
            if (IsWindowVisible(c.edit)) ShowWindow(c.edit, SW_HIDE);
            continue;
        }
        int x = (int)FPx(f, c.box.left + 12), w = (int)FPx(f, c.box.right - c.box.left - 24);
        int lineH = (int)FPx(f, 20), h = c.lines > 1 ? (int)FPx(f, c.box.bottom - c.box.top - 16) : lineH;
        int y = c.lines > 1 ? (int)FPx(f, top + 8) : (int)FPx(f, (top + bottom) / 2) - lineH / 2;
        SetWindowPos(c.edit, nullptr, x, y, std::max(10, w), std::max(10, h), SWP_NOZORDER | SWP_NOACTIVATE);
        if (!IsWindowVisible(c.edit)) ShowWindow(c.edit, SW_SHOWNA);
    }
}

// ---- Drawing -------------------------------------------------------------------------

constexpr int kPart = 16;

void Form_Paint(Form& f) {
    if (!f.hwnd) return;
    if (!f.rt) {
        RECT rc;
        GetClientRect(f.hwnd, &rc);
        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
            (float)f.dpi, (float)f.dpi);
        if (FAILED(g_gfx.d2d->CreateHwndRenderTarget(
                props, D2D1::HwndRenderTargetProperties(f.hwnd, D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom))),
                f.rt.put())))
            return;
    }
    f.hits.clear();
    Pt p(f.rt.get());
    f.rt->BeginDraw();
    f.rt->SetTransform(D2D1::Matrix3x2F::Identity());
    PaintBody(p, f.cw, f.ch, kMainTint);
    f.rt->SetTransform(D2D1::Matrix3x2F::Translation(0, -f.scroll));
    HWND focus = GetFocus();
    float rad = CtlRadius();
    for (size_t i = 0; i < f.ctls.size(); i++) {
        FCtl& c = f.ctls[i];
        if (!c.visible || c.r.bottom <= c.r.top) continue;
        int base = (int)i * kPart;
        float a = c.enabled ? 1.0f : 0.4f;
        switch (c.kind) {
            case cHead: p.Text(Fmt(18, 700, kWrap), c.text, {c.r.left, c.r.top, c.r.right, c.r.bottom + 4}, mocha::text); break;
            case cText: p.Text(Fmt(13.5f, 500, kWrap), c.text, {c.r.left, c.r.top, c.r.right, c.r.bottom + 4}, c.tone); break;
            case cNote: p.Text(Fmt(13, 600, kWrap), c.text, {c.r.left, c.r.top, c.r.right, c.r.bottom + 4}, c.tone); break;
            case cEdit:
            case cChoice: {
                if (!c.label.empty()) p.Text(Fmt(12.5f, 600, 0), c.label, {c.r.left, c.r.top, c.r.right, c.r.top + 20}, mocha::subtext0, a);
                float g = f.glow.Of(base);
                bool focused = c.edit && focus == c.edit;
                p.Round(c.box, rad, acset::kSetBoxFill, a);
                if (focused) p.GradEdge(c.box, rad, a);
                else p.HoverEdge(c.box, rad, c.enabled ? g : 0, a);
                if (c.kind == cChoice) {
                    std::wstring t = c.choice < (int)c.options.size() ? c.options[c.choice] : L"";
                    p.Text(Fmt(13.5f, 500, kMiddle), t, {c.box.left + 12, c.box.top, c.box.right - 36, c.box.bottom}, mocha::text, a);
                    p.Glyph(Fmt(12, 400, kIcon | kCenter | kMiddle), 0xE70D, {c.box.right - 34, c.box.top, c.box.right - 8, c.box.bottom},
                            mocha::subtext0, a);
                }
                f.hits.push_back({base, c.box, c.enabled});
                if (!c.buttons.empty() && c.side.right > c.side.left) {
                    FBtn& b = c.buttons[0];
                    DrawButton(p, c.side, b.label, b.icon, b.style, f.glow.Of(base + 1), b.enabled && c.enabled);
                    f.hits.push_back({base + 1, c.side, b.enabled && c.enabled});
                }
                if (!c.hint.empty())
                    p.Text(Fmt(12, 500, kWrap), c.hint, {c.r.left, c.box.bottom + 6, c.r.right, c.r.bottom + 4}, mocha::overlay2, a);
                break;
            }
            case cSwitch: {
                float tw = c.r.right - c.r.left - 60;
                float lh = TextH(Fmt(13.5f, 600, kWrap), c.label, tw);
                p.Text(Fmt(13.5f, 600, kWrap), c.label, {c.r.left, c.r.top, c.r.left + tw, c.r.top + lh + 4}, mocha::text, a);
                if (!c.hint.empty())
                    p.Text(Fmt(12.5f, 500, kWrap), c.hint, {c.r.left, c.r.top + lh + 2, c.r.left + tw, c.r.bottom + 4}, mocha::subtext0, a);
                DrawSwitch(p, c.box, c.on, f.glow.Of(base), c.enabled);
                f.hits.push_back({base, c.r, c.enabled});
                break;
            }
            case cButtons: {
                float x = c.r.right;
                for (size_t k = c.buttons.size(); k-- > 0;) {
                    FBtn& b = c.buttons[k];
                    float bw = BtnWidth(b);
                    D2D1_RECT_F br{x - bw, c.r.top, x, c.r.top + kBtnH};
                    bool en = b.enabled && c.enabled;
                    DrawButton(p, br, b.label, b.icon, b.style, f.glow.Of(base + 1 + (int)k), en);
                    f.hits.push_back({base + 1 + (int)k, br, en});
                    x -= bw + 8;
                }
                break;
            }
            case cChips: {
                float top = c.r.top;
                if (!c.label.empty()) {
                    p.Text(Fmt(12.5f, 600, 0), c.label, {c.r.left, top, c.r.right, top + 20}, mocha::subtext0, a);
                    top += 22;
                }
                float x = c.r.left;
                for (size_t k = 0; k < c.options.size(); k++) {
                    D2D1_RECT_F cr{x, top, x + 46, top + 30};
                    bool on = (c.mask >> k) & 1;
                    float g = f.glow.Of(base + 1 + (int)k);
                    if (on) {
                        p.Round(cr, 15, mocha::blue, 0.18f * a);
                        p.Edge(cr, 15, mocha::blue, 0.6f * a * (1 - g));
                        p.GradEdge(cr, 15, g * a);
                    } else {
                        p.Round(cr, 15, mocha::surface0, 0.5f * g * a);
                        p.HoverEdge(cr, 15, g, a);
                    }
                    p.Text(Fmt(12.5f, 600, kCenter | kMiddle), c.options[k], cr, on ? mocha::text : mocha::subtext0, a);
                    f.hits.push_back({base + 1 + (int)k, cr, c.enabled});
                    x += 52;
                }
                break;
            }
            case cLine: p.Line(c.r.left, c.r.top + 0.5f, c.r.right, c.r.top + 0.5f, mocha::surface1, 0.8f); break;
            case cBar: {
                p.Round(c.r, 3, mocha::surface0);
                float w = (c.r.right - c.r.left) * std::clamp(c.progress, 0.0f, 1.0f);
                if (w > 0.5f) p.GradFill({c.r.left, c.r.top, c.r.left + std::max(6.0f, w), c.r.bottom}, 3, 1);
                break;
            }
        }
    }
    // The scroll thumb, when the content is taller than the window.
    float max = Form_MaxScroll(f);
    if (max > 0) {
        f.rt->SetTransform(D2D1::Matrix3x2F::Identity());
        float track = f.ch - 16, th = std::max(36.0f, track * f.ch / f.contentH);
        float ty = 8 + (track - th) * (f.scroll / max);
        p.Round({f.cw - 8, ty, f.cw - 4, ty + th}, 2, mocha::overlay0, 0.7f);
    }
    if (f.rt->EndDraw() == D2DERR_RECREATE_TARGET) f.rt.reset();
}

// ---- Input ---------------------------------------------------------------------------

void Form_StartAnim(Form& f) {
    if (!f.animating && f.hwnd) {
        SetTimer(f.hwnd, kFormAnim, 16, nullptr);
        f.animating = true;
    }
}

void Form_UpdateHover(Form& f) {
    int h = f.mx < 0 ? -1 : HitAt(f.hits, f.mx, f.my + f.scroll);
    if (h < 0) h = -1;
    if (h != f.hover) {
        f.hover = h;
        Form_StartAnim(f);
    }
    bool hand = h >= 0;
    SetCursor(LoadCursorW(nullptr, hand ? IDC_HAND : IDC_ARROW));
}

void Form_Close(Form& f) {
    if (f.hwnd) DestroyWindow(f.hwnd);
}

void Form_Press(Form& f, int btnId) {
    if (!btnId) return;
    FBtn* b = Form_Button(f, btnId);
    if (b && !b->enabled) return;
    FormCall guard;
    if (f.onButton) f.onButton(f, btnId);
}

void Form_Changed(Form& f, int id) {
    FormCall guard;
    if (f.onChange) f.onChange(f, id);
}

void Form_Click(Form& f, int hit) {
    int idx = hit / kPart, part = hit % kPart;
    if (idx < 0 || idx >= (int)f.ctls.size()) return;
    FCtl& c = f.ctls[idx];
    if (!c.enabled) return;
    switch (c.kind) {
        case cEdit:
            if (part == 0 && c.edit) SetFocus(c.edit);
            else if (part == 1 && !c.buttons.empty()) Form_Press(f, c.buttons[0].id);
            break;
        case cSwitch:
            c.on = !c.on;
            Form_StartAnim(f);
            Form_Changed(f, c.id);
            break;
        case cChoice: {
            std::vector<acset::SetMenuItem> items;
            for (size_t k = 0; k < c.options.size(); k++)
                items.push_back(acset::Set_MenuRow((int)k + 1, L"", c.options[k].c_str(), (int)k == c.choice));
            POINT pt{(LONG)FPx(f, c.box.left), (LONG)FPx(f, c.box.bottom - f.scroll + 4)};
            ClientToScreen(f.hwnd, &pt);
            int id = c.id;
            int picked = acset::Set_TrayMenu(f.hwnd, items, &pt);
            if (f.dead) return;
            FCtl* again = Form_Ctl(f, id);
            if (again && picked > 0 && picked - 1 != again->choice) {
                again->choice = picked - 1;
                Form_Changed(f, id);
            }
            Form_Invalidate(f);
            break;
        }
        case cButtons:
            if (part >= 1 && part - 1 < (int)c.buttons.size()) Form_Press(f, c.buttons[part - 1].id);
            break;
        case cChips:
            if (part >= 1) {
                c.mask ^= 1u << (part - 1);
                Form_Changed(f, c.id);
                Form_Invalidate(f);
            }
            break;
    }
}

// Tab walks the text boxes; Enter presses the main button; Escape closes.
void Form_FocusNext(Form& f, HWND from, bool back) {
    std::vector<HWND> edits;
    for (auto& c : f.ctls)
        if (c.edit && c.visible && c.enabled && IsWindowVisible(c.edit)) edits.push_back(c.edit);
    if (edits.empty()) return;
    auto it = std::find(edits.begin(), edits.end(), from);
    size_t k = it == edits.end() ? 0 : (size_t)(it - edits.begin());
    k = it == edits.end() ? 0 : back ? (k + edits.size() - 1) % edits.size() : (k + 1) % edits.size();
    SetFocus(edits[k]);
    SendMessageW(edits[k], EM_SETSEL, 0, -1);
}

Form* Form_Of(HWND hwnd) { return (Form*)GetWindowLongPtrW(hwnd, GWLP_USERDATA); }

bool Form_Key(Form& f, UINT vk, HWND from) {
    if (vk == VK_ESCAPE) {
        if (f.cancelBtn) Form_Press(f, f.cancelBtn);
        else Form_Close(f);
        return true;
    }
    if (vk == VK_RETURN) {
        Form_Press(f, f.defaultBtn);
        return true;
    }
    if (vk == VK_TAB) {
        Form_FocusNext(f, from, GetKeyState(VK_SHIFT) < 0);
        return true;
    }
    return false;
}

LRESULT CALLBACK FormEditProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    Form* f = Form_Of(GetParent(hwnd));
    if (f && msg == WM_KEYDOWN && (wp == VK_ESCAPE || wp == VK_TAB || (wp == VK_RETURN && !(GetWindowLongPtrW(hwnd, GWL_STYLE) & ES_MULTILINE)))) {
        Form_Key(*f, (UINT)wp, hwnd);
        return 0;
    }
    if (msg == WM_KEYDOWN && wp == 'A' && GetKeyState(VK_CONTROL) < 0) {
        SendMessageW(hwnd, EM_SETSEL, 0, -1);
        return 0;
    }
    if (msg == WM_CHAR && (wp == VK_ESCAPE || wp == VK_RETURN || wp == VK_TAB || wp == 1 /* Ctrl+A */)) return 0;
    if (f && (msg == WM_SETFOCUS || msg == WM_KILLFOCUS)) {
        if (msg == WM_SETFOCUS) f->lastFocus = hwnd;
        Form_Invalidate(*f);
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

void Form_MakeEdits(Form& f) {
    if (f.font) DeleteObject(f.font);
    f.font = CreateFontW(-MulDiv(13, f.dpi, 96), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                         CLEARTYPE_QUALITY, DEFAULT_PITCH, g_gfx.family.c_str());
    for (size_t i = 0; i < f.ctls.size(); i++) {
        FCtl& c = f.ctls[i];
        if (c.kind != cEdit) continue;
        if (c.edit) {
            c.text = Form_Text(f, c.id);
            DestroyWindow(c.edit);
        }
        DWORD style = WS_CHILD | WS_TABSTOP;
        style |= c.lines > 1 ? (ES_MULTILINE | WS_VSCROLL * 0) : ES_AUTOHSCROLL;
        if (c.password) style |= ES_PASSWORD;
        if (c.readOnly) style |= ES_READONLY;
        c.edit = CreateWindowExW(g_glass ? WS_EX_LAYERED : 0, L"EDIT", L"", style, 0, 0, 10, 10, f.hwnd, (HMENU)(INT_PTR)(100 + i),
                                 (HINSTANCE)&__ImageBase, nullptr);
        if (!c.edit) continue;
        if (g_glass) SetLayeredWindowAttributes(c.edit, 0, 255, LWA_ALPHA);
        SendMessageW(c.edit, WM_SETFONT, (WPARAM)f.font, TRUE);
        if (!c.placeholder.empty()) SendMessageW(c.edit, EM_SETCUEBANNER, TRUE, (LPARAM)c.placeholder.c_str());
        SetWindowTheme(c.edit, L"DarkMode_Explorer", nullptr);
        SetWindowSubclass(c.edit, FormEditProc, 1, 0);
        f.muted = true;
        SetWindowTextW(c.edit, c.text.c_str());
        f.muted = false;
        EnableWindow(c.edit, c.enabled);
    }
}

LRESULT CALLBACK FormProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NCCREATE) SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCTW*)lp)->lpCreateParams);
    Form* fp = Form_Of(hwnd);
    if (!fp) return DefWindowProcW(hwnd, msg, wp, lp);
    Form& f = *fp;
    switch (msg) {
        case WM_ERASEBKGND: return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            Form_Paint(f);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_SIZE: {
            RECT rc;
            GetClientRect(hwnd, &rc);
            f.ch = rc.bottom * 96.0f / f.dpi;
            if (f.rt) f.rt->Resize(D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom)));
            f.scroll = std::clamp(f.scroll, 0.0f, Form_MaxScroll(f));
            Form_PlaceEdits(f);
            Form_Invalidate(f);
            return 0;
        }
        case WM_DPICHANGED: {
            f.dpi = HIWORD(wp);
            if (f.rt) f.rt->SetDpi((float)f.dpi, (float)f.dpi);
            Form_MakeEdits(f);
            const RECT* r = (const RECT*)lp;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top, SWP_NOZORDER | SWP_NOACTIVATE);
            Form_Relayout(f);
            return 0;
        }
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORSTATIC: {
            HDC dc = (HDC)wp;
            SetTextColor(dc, RefFromRgb(mocha::text));
            SetBkColor(dc, RefFromRgb(acset::kSetBoxFill));
            return (LRESULT)f.box;
        }
        case WM_COMMAND:
            if (HIWORD(wp) == EN_CHANGE && !f.muted) {
                int i = LOWORD(wp) - 100;
                if (i >= 0 && i < (int)f.ctls.size()) {
                    Form_Text(f, f.ctls[i].id);
                    Form_Changed(f, f.ctls[i].id);
                }
            }
            return 0;
        case WM_SETCURSOR:
            if (LOWORD(lp) == HTCLIENT) {
                Form_UpdateHover(f);
                return TRUE;
            }
            break;
        case WM_MOUSEMOVE:
            f.mx = GET_X_LPARAM(lp) * 96.0f / f.dpi;
            f.my = GET_Y_LPARAM(lp) * 96.0f / f.dpi;
            if (!f.tracking) {
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                f.tracking = TrackMouseEvent(&t);
            }
            Form_UpdateHover(f);
            return 0;
        case WM_MOUSELEAVE:
            f.tracking = false;
            f.mx = f.my = -1;
            f.hover = -1;
            Form_StartAnim(f);
            return 0;
        case WM_MOUSEWHEEL: {
            float max = Form_MaxScroll(f);
            if (max <= 0) return 0;
            f.scroll = std::clamp(f.scroll - GET_WHEEL_DELTA_WPARAM(wp) / 120.0f * 60, 0.0f, max);
            Form_PlaceEdits(f);
            Form_Invalidate(f);
            return 0;
        }
        case WM_LBUTTONDOWN: {
            float x = GET_X_LPARAM(lp) * 96.0f / f.dpi, y = GET_Y_LPARAM(lp) * 96.0f / f.dpi + f.scroll;
            int id = HitAt(f.hits, x, y);
            f.pressed = id >= 0 ? id : -1;
            if (id >= 0) SetCapture(hwnd);
            else SetFocus(hwnd);
            Form_StartAnim(f);
            return 0;
        }
        case WM_LBUTTONUP: {
            if (GetCapture() == hwnd) ReleaseCapture();
            float x = GET_X_LPARAM(lp) * 96.0f / f.dpi, y = GET_Y_LPARAM(lp) * 96.0f / f.dpi + f.scroll;
            int id = HitAt(f.hits, x, y), was = f.pressed;
            f.pressed = -1;
            Form_StartAnim(f);
            if (was >= 0 && id == was) Form_Click(f, id);
            return 0;
        }
        case WM_KEYDOWN:
            if (Form_Key(f, (UINT)wp, nullptr)) return 0;
            break;
        case WM_ACTIVATE:
            if (LOWORD(wp) != WA_INACTIVE) {
                HWND to = f.lastFocus && IsWindow(f.lastFocus) && IsWindowVisible(f.lastFocus) ? f.lastFocus : nullptr;
                if (!to)
                    for (auto& c : f.ctls)
                        if (c.edit && c.enabled && !c.readOnly && IsWindowVisible(c.edit)) {
                            to = c.edit;
                            break;
                        }
                if (to) {
                    SetFocus(to);
                    return 0;
                }
            }
            Form_Invalidate(f);
            break;
        case WM_TIMER:
            if (wp == kFormAnim) {
                bool moving = f.glow.Step(f.hover, f.pressed);
                Form_Invalidate(f);
                if (!moving) {
                    KillTimer(hwnd, kFormAnim);
                    f.animating = false;
                }
            } else if (wp == kFormTick && f.onTick) {
                FormCall guard;
                f.onTick(f);
            }
            return 0;
        case WM_CLOSE:
            if (f.cancelBtn) Form_Press(f, f.cancelBtn);
            else Form_Close(f);
            return 0;
        case WM_DESTROY: {
            FormCall guard;
            if (f.onClose) {
                auto done = std::move(f.onClose);
                f.onClose = nullptr;
                done(f);
            }
            return 0;
        }
        case WM_NCDESTROY:
            f.rt.reset();
            for (auto& c : f.ctls) c.edit = nullptr;
            if (f.font) DeleteObject(f.font);
            if (f.box) DeleteObject(f.box);
            f.font = nullptr;
            f.box = nullptr;
            f.hwnd = nullptr;
            f.dead = true;
            SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// A new form, not yet on screen. Fill ctls and callbacks, then Form_Open.
Form& Form_New(const std::string& key, const std::wstring& title) {
    Form_Sweep();
    auto f = std::make_unique<Form>();
    f->key = key;
    f->serial = ++g_formSerial;
    f->title = title;
    g_forms.push_back(std::move(f));
    return *g_forms.back();
}

// quiet: opened for the browser or a timer, so it never takes focus from what the owner is doing.
bool Form_Open(Form& f, bool quiet) {
    if (!Gfx_Init()) return false;
    // Asked each time: Forms_CloseAll unregisters the class, so a remembered flag goes stale.
    WNDCLASSEXW have{sizeof(have)};
    if (!GetClassInfoExW((HINSTANCE)&__ImageBase, kFormClass, &have)) {
        WNDCLASSEXW wc{sizeof(wc)};
        wc.lpfnWndProc = FormProc;
        wc.hInstance = (HINSTANCE)&__ImageBase;
        wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wc.lpszClassName = kFormClass;
        wc.hIcon = g_iconBig;
        wc.hIconSm = g_iconSmall;
        RegisterClassExW(&wc);
    }
    g_radius = acset::Set_MenuCornerRadius();
    g_glass = Wh_GetIntSetting(L"settingsGlass") != 0;
    std::wstring caption = f.title.empty() ? std::wstring(kAppTitle) : f.title;
    HWND hwnd = CreateWindowExW(0, kFormClass, caption.c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN, CW_USEDEFAULT,
                                CW_USEDEFAULT, 520, 300, nullptr, nullptr, (HINSTANCE)&__ImageBase, &f);
    if (!hwnd) return false;
    f.hwnd = hwnd;
    f.dpi = GetDpiForWindow(hwnd);
    f.box = CreateSolidBrush(RefFromRgb(acset::kSetBoxFill));
    if (g_iconSmall) SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)g_iconSmall);
    if (g_iconBig) SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)g_iconBig);
    Sdm_ApplyGlass(hwnd);
    Form_MakeEdits(f);
    Form_Layout(f);
    Form_FitWindow(f, true);
    RECT rc;
    GetClientRect(hwnd, &rc);
    f.ch = rc.bottom * 96.0f / f.dpi;
    Form_PlaceEdits(f);
    if (f.tickMs) SetTimer(hwnd, kFormTick, f.tickMs, nullptr);
    if (quiet) {
        ShowWindow(hwnd, SW_SHOWNOACTIVATE);
        SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    } else {
        ShowWindow(hwnd, SW_SHOW);
        SetForegroundWindow(hwnd);
    }
    return true;
}

// Brings an open form forward (the owner asked for it again).
bool Form_Raise(const std::string& key) {
    Form* f = Form_Find(key);
    if (!f || !f->hwnd) return false;
    if (IsIconic(f->hwnd)) ShowWindow(f->hwnd, SW_RESTORE);
    SetForegroundWindow(f->hwnd);
    return true;
}

void Forms_CloseAll() {
    std::vector<HWND> wins;
    for (auto& f : g_forms)
        if (f->hwnd) wins.push_back(f->hwnd);
    for (HWND h : wins) DestroyWindow(h);
    Form_Sweep();
    UnregisterClassW(kFormClass, (HINSTANCE)&__ImageBase);
}

// ---- Shared bits -------------------------------------------------------------------------

std::vector<std::wstring> QueueNames() {
    std::vector<std::wstring> out;
    for (auto& q : g_main.queues) out.push_back(q.name.empty() ? L"Main queue" : q.name);
    if (out.empty()) out.push_back(L"Main queue");
    return out;
}

int64_t QueueAt(int index) {
    if (index >= 0 && index < (int)g_main.queues.size()) return g_main.queues[index].id;
    return 0;
}

std::wstring DefaultFolder() { return sj::W(g_main.settings["default_download_folder"].str()); }

bool PickFolder(HWND owner, std::wstring& folder) {
    SetCom<IFileOpenDialog> dlg;
    if (FAILED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(dlg.put())))) return false;
    DWORD opts = 0;
    dlg->GetOptions(&opts);
    dlg->SetOptions(opts | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST);
    dlg->SetTitle(L"Save downloads to");
    if (!folder.empty()) {
        SetCom<IShellItem> start;
        if (SUCCEEDED(SHCreateItemFromParsingName(folder.c_str(), nullptr, IID_PPV_ARGS(start.put())))) dlg->SetFolder(start.get());
    }
    if (dlg->Show(owner) != S_OK) return false;
    SetCom<IShellItem> item;
    if (FAILED(dlg->GetResult(item.put()))) return false;
    PWSTR path = nullptr;
    if (FAILED(item->GetDisplayName(SIGDN_FILESYSPATH, &path)) || !path) return false;
    folder = path;
    CoTaskMemFree(path);
    return true;
}

std::wstring Plural(int64_t n, PCWSTR one, PCWSTR many) {
    return std::to_wstring(n) + L" " + (n == 1 ? one : many);
}

// "Speed limit must be a number from 1 to 10000000", as the app says it.
bool ParseNum(const std::wstring& text, PCWSTR what, int64_t lo, int64_t hi, int64_t& out, std::wstring& err) {
    std::wstring t = Trim(text);
    bool ok = !t.empty() && t.size() < 19 && std::all_of(t.begin(), t.end(), [](wchar_t c) { return c >= L'0' && c <= L'9'; });
    if (ok) {
        out = _wtoi64(t.c_str());
        ok = out >= lo && out <= hi;
    }
    if (!ok) err = std::wstring(what) + L" must be a number from " + std::to_wstring(lo) + L" to " + std::to_wstring(hi);
    return ok;
}

// ---- Add a download ------------------------------------------------------------------------

enum { kAddLink = 1, kAddInfo, kAddName, kAddFolder, kAddQueue, kAddAuth, kAddUser, kAddPass, kAddCancel = 90, kAddQueueBtn, kAddNow, kAddChoose };

std::deque<Val> g_pendingAdds;  // Browser links that came in while the add window was busy.

void Add_Probe(Form& f) {
    std::wstring url = Trim(Form_Text(f, kAddLink));
    f.data.set("probeAt", sj::Int(0));
    if (url.empty()) {
        Form_Note(f, kAddInfo, L"", mocha::subtext0);
        return;
    }
    if (f.data["probing"].truthy()) {
        f.data.set("again", sj::Bool(true));
        return;
    }
    f.data.set("probing", sj::Bool(true));
    f.data.set("probed", sj::WStr(url));
    Form_Note(f, kAddInfo, L"Checking the link", mocha::overlay2);
    Val req = Cmd("probe");
    req.set("url", sj::WStr(url));
    const Val& pending = f.data["request"];
    if (pending.t == Val::Obj && sj::W(pending["url"].str()) == url && pending["headers"].t == Val::Arr) req.set("headers", pending["headers"]);
    uint64_t serial = f.serial;
    StartJob(req, [serial, url](bool ok, const Val& info, const std::wstring& err) {
        Form* f = Form_BySerial(serial);
        if (!f) return;
        f->data.set("probing", sj::Bool(false));
        if (f->data["again"].truthy() || Trim(Form_Text(*f, kAddLink)) != url) {
            f->data.set("again", sj::Bool(false));
            Add_Probe(*f);
            return;
        }
        if (!ok) {
            Form_Note(*f, kAddInfo, L"Could not reach that link: " + err, mocha::red);
            return;
        }
        if (info["is_web_page"].truthy()) {
            Form_Note(*f, kAddInfo, L"This link opens a web page, not a file. You can still add it.", mocha::red);
            return;
        }
        if (info["needs_auth"].truthy()) {
            Form_Note(*f, kAddInfo, L"The site wants you signed in. Try the download from your browser instead.", mocha::red);
            return;
        }
        std::wstring size = info["total"].null() ? L"Size not known" : SizeText(info["total"].num(), g_main.decimal);
        Form_Note(*f, kAddInfo, size + (info["resumable"].truthy() ? L", can pause and resume." : L", cannot resume if it stops."), mocha::green);
        if (Trim(Form_Text(*f, kAddName)).empty() && !info["file_name"].str().empty())
            Form_SetText(*f, kAddName, sj::W(info["file_name"].str()));
    });
}

void Add_Submit(Form& f, bool now) {
    std::wstring url = Trim(Form_Text(f, kAddLink));
    if (url.empty()) {
        Form_Note(f, kAddInfo, L"Paste a link first.", mocha::red);
        return;
    }
    const Val& pending = f.data["request"];
    Val req = pending.t == Val::Obj && sj::W(pending["url"].str()) == url ? pending : sj::Obj();
    req.set("url", sj::WStr(url));
    std::wstring name = Trim(Form_Text(f, kAddName)), folder = Trim(Form_Text(f, kAddFolder));
    req.set("name", name.empty() ? Val() : sj::WStr(name));
    req.set("folder", folder.empty() ? Val() : sj::WStr(folder));
    req.set("start", sj::Bool(now));
    FCtl* q = Form_Ctl(f, kAddQueue);
    req.set("queue_id", now ? Val() : sj::Int(QueueAt(q ? q->choice : 0)));
    FCtl* auth = Form_Ctl(f, kAddAuth);
    std::wstring user = Trim(Form_Text(f, kAddUser));
    if (auth && auth->on && !user.empty()) {
        Val pair = sj::Arr();
        pair.push(sj::WStr(user));
        pair.push(sj::WStr(Form_Text(f, kAddPass)));
        req.set("basic_auth", pair);
    } else {
        req.set("basic_auth", Val());
    }
    Val call = Cmd("add");
    call.set("request", req);
    Val v = Call(call);
    if (v.has("error")) {
        Form_Note(f, kAddInfo, L"Could not add it: " + ErrorOf(v), mocha::red);
        return;
    }
    Toast(now ? L"Downloading" : L"Added to the queue");
    Refresh();
    Form_Close(f);
}

void OpenAddDialog(const Val* request, const std::wstring& link) {
    if (Form_Find("add")) {
        if (request) g_pendingAdds.push_back(*request);
        else Form_Raise("add");
        return;
    }
    bool quiet = request != nullptr;
    std::wstring url = request ? sj::W((*request)["url"].str()) : link;
    std::wstring name, folder;
    if (request) {
        name = sj::W((*request)["name"].str());
        if (name.empty()) name = sj::W((*request)["suggested_name"].str());
        folder = sj::W((*request)["folder"].str());
    }
    if (folder.empty()) folder = DefaultFolder();
    Form& f = Form_New("add", L"Add a download");
    if (request) f.data.set("request", *request);
    f.ctls.push_back(EditBox(kAddLink, L"Link", url, L"Paste a link"));
    f.ctls.push_back(Note(kAddInfo));
    f.ctls.push_back(EditBox(kAddName, L"File name", name, L"Picked from the link"));
    FCtl folderBox = EditBox(kAddFolder, L"Save to", folder);
    folderBox.buttons.push_back({kAddChoose, L"Choose", kPlain, 0xE838});
    f.ctls.push_back(folderBox);
    f.ctls.push_back(Choice(kAddQueue, L"Queue", QueueNames(), 0));
    bool hasAuth = request && (*request)["basic_auth"].t == Val::Arr;
    f.ctls.push_back(Switch(kAddAuth, L"Site needs a sign-in", L"", hasAuth));
    FCtl user = EditBox(kAddUser, L"", hasAuth ? sj::W((*request)["basic_auth"][size_t(0)].str()) : L"", L"Name");
    FCtl pass = EditBox(kAddPass, L"", hasAuth ? sj::W((*request)["basic_auth"][size_t(1)].str()) : L"", L"Password");
    user.half = pass.half = true;
    pass.password = true;
    user.visible = pass.visible = hasAuth;
    f.ctls.push_back(user);
    f.ctls.push_back(pass);
    f.ctls.push_back(Buttons({{kAddCancel, L"Cancel"}, {kAddQueueBtn, L"Add to queue", kPlain, 0xE8FD}, {kAddNow, L"Download now", kPrimary, 0xE896}}));
    f.defaultBtn = kAddNow;
    f.cancelBtn = kAddCancel;
    f.tickMs = 100;
    f.onTick = [](Form& f) {
        int64_t at = f.data["probeAt"].num();
        if (at && (int64_t)GetTickCount64() >= at) Add_Probe(f);
    };
    f.onChange = [](Form& f, int id) {
        if (id == kAddLink) f.data.set("probeAt", sj::Int((int64_t)GetTickCount64() + 450));
        if (id == kAddAuth) {
            bool on = Form_Ctl(f, kAddAuth)->on;
            Form_Ctl(f, kAddUser)->visible = on;
            Form_Ctl(f, kAddPass)->visible = on;
            Form_Relayout(f);
            if (on && Form_Ctl(f, kAddUser)->edit) SetFocus(Form_Ctl(f, kAddUser)->edit);
        }
    };
    f.onButton = [](Form& f, int id) {
        if (id == kAddCancel) Form_Close(f);
        else if (id == kAddQueueBtn) Add_Submit(f, false);
        else if (id == kAddNow) Add_Submit(f, true);
        else if (id == kAddChoose) {
            std::wstring folder = Trim(Form_Text(f, kAddFolder));
            if (PickFolder(f.hwnd, folder)) Form_SetText(f, kAddFolder, folder);
        }
    };
    f.onClose = [](Form&) {
        if (g_pendingAdds.empty()) return;
        Val next = std::move(g_pendingAdds.front());
        g_pendingAdds.pop_front();
        // Opened on the next turn, after this window is fully gone.
        auto* copy = new Val(std::move(next));
        if (!g_msgWnd || !PostMessageW(g_msgWnd, WM_SDM_ADDREQ, 0, (LPARAM)copy)) delete copy;
    };
    if (!Form_Open(f, quiet)) return;
    if (!url.empty()) Add_Probe(f);
}

// ---- Add many links ------------------------------------------------------------------------

enum { kManyLink = 1, kManyFrom, kManyTo, kManyZeros, kManyWidth, kManyPreview, kManyFolder, kManyQueue, kManyCancel = 90, kManyQueueBtn, kManyStart, kManyChoose };

bool Many_Request(Form& f, Val& out, std::wstring& err) {
    std::wstring pattern = Trim(Form_Text(f, kManyLink));
    if (pattern.empty() || pattern.find(L'*') == std::wstring::npos) {
        err = L"Put a * where the number goes.";
        return false;
    }
    int64_t from = 0, to = 0;
    if (!ParseNum(Form_Text(f, kManyFrom), L"From", 0, 999999999, from, err)) return false;
    if (!ParseNum(Form_Text(f, kManyTo), L"To", 0, 999999999, to, err)) return false;
    out.set("pattern", sj::WStr(pattern));
    out.set("start", sj::Int(from));
    out.set("end", sj::Int(to));
    int zeros = Form_Ctl(f, kManyZeros)->choice;
    if (zeros == 1) {
        out.set("padding", sj::Str("none"));
    } else if (zeros == 2) {
        int64_t width = 0;
        if (!ParseNum(Form_Text(f, kManyWidth), L"Width", 1, 20, width, err)) return false;
        out.set("padding", sj::Int(width));
    }
    return true;
}

void Many_Preview(Form& f) {
    Val req = Cmd("batch_preview");
    std::wstring err;
    bool ok = Many_Request(f, req, err);
    if (ok) {
        Val v = Call(req);
        if (v.has("error")) {
            err = ErrorOf(v);
            ok = false;
        } else {
            int64_t n = v["count"].num();
            f.data.set("count", sj::Int(n));
            std::wstring text = Plural(n, L"link", L"links");
            if (n > 0) text += L"\n" + sj::W(v["first"].str());
            if (n > 1) text += L"\nto " + sj::W(v["last"].str());
            Form_Note(f, kManyPreview, text, mocha::subtext1);
        }
    }
    if (!ok) {
        f.data.set("count", sj::Int(0));
        Form_Note(f, kManyPreview, err, Trim(Form_Text(f, kManyLink)).empty() ? mocha::overlay2 : mocha::red);
    }
    Form_EnableButton(f, kManyQueueBtn, ok);
    Form_EnableButton(f, kManyStart, ok);
}

void Many_Submit(Form& f, bool start) {
    Val req = Cmd("add_many");
    std::wstring err;
    if (!Many_Request(f, req, err)) {
        Form_Note(f, kManyPreview, err, mocha::red);
        return;
    }
    Val tmpl = sj::Obj();
    std::wstring folder = Trim(Form_Text(f, kManyFolder));
    if (!folder.empty()) tmpl.set("folder", sj::WStr(folder));
    int64_t queue = QueueAt(Form_Ctl(f, kManyQueue)->choice);
    tmpl.set("queue_id", sj::Int(queue));
    tmpl.set("start", sj::Bool(false));
    req.set("request", tmpl);
    req.set("start_queue", sj::Bool(start));
    Val v = Call(req);
    Refresh();
    if (v.has("error")) {
        Form_Note(f, kManyPreview, L"Could not add them: " + ErrorOf(v), mocha::red);
        return;
    }
    std::wstring n = Plural((int64_t)v["ids"].size(), L"link", L"links");
    Toast(start ? L"Added " + n + L" and started the queue" : L"Added " + n + L" to the queue");
    Form_Close(f);
}

void OpenAddMany() {
    if (Form_Raise("many")) return;
    std::wstring clip = ClipboardText(), link;
    std::wstring low = Lower(Trim(clip));
    if ((low.rfind(L"http://", 0) == 0 || low.rfind(L"https://", 0) == 0) && low.find(L'*') != std::wstring::npos &&
        low.find_first_of(L" \r\n\t") == std::wstring::npos)
        link = Trim(clip);
    Form& f = Form_New("many", L"Add many links");
    f.ctls.push_back(Para(L"Put a * where the number goes, like https://site.com/part-*.zip"));
    f.ctls.push_back(EditBox(kManyLink, L"Link", link, L"Link with a *"));
    FCtl from = EditBox(kManyFrom, L"From", L"1"), to = EditBox(kManyTo, L"To", L"10");
    from.half = to.half = true;
    f.ctls.push_back(from);
    f.ctls.push_back(to);
    FCtl zeros = Choice(kManyZeros, L"Leading zeros", {L"Match the last", L"None", L"Fixed width"}, 0);
    FCtl width = EditBox(kManyWidth, L"Width", L"3");
    zeros.half = width.half = true;
    width.enabled = false;
    f.ctls.push_back(zeros);
    f.ctls.push_back(width);
    f.ctls.push_back(Note(kManyPreview));
    FCtl folder = EditBox(kManyFolder, L"Save to", DefaultFolder());
    folder.buttons.push_back({kManyChoose, L"Choose", kPlain, 0xE838});
    f.ctls.push_back(folder);
    f.ctls.push_back(Choice(kManyQueue, L"Queue", QueueNames(), 0));
    f.ctls.push_back(Buttons({{kManyCancel, L"Cancel"}, {kManyQueueBtn, L"Add to queue", kPlain, 0xE8FD}, {kManyStart, L"Add and start", kPrimary, 0xE768}}));
    f.defaultBtn = kManyStart;
    f.cancelBtn = kManyCancel;
    f.onChange = [](Form& f, int id) {
        if (id == kManyZeros) Form_Enable(f, kManyWidth, Form_Ctl(f, kManyZeros)->choice == 2);
        if (id == kManyLink || id == kManyFrom || id == kManyTo || id == kManyZeros || id == kManyWidth) Many_Preview(f);
    };
    f.onButton = [](Form& f, int id) {
        if (id == kManyCancel) Form_Close(f);
        else if (id == kManyQueueBtn) Many_Submit(f, false);
        else if (id == kManyStart) Many_Submit(f, true);
        else if (id == kManyChoose) {
            std::wstring folder = Trim(Form_Text(f, kManyFolder));
            if (PickFolder(f.hwnd, folder)) Form_SetText(f, kManyFolder, folder);
        }
    };
    Many_Preview(f);
    Form_Open(f, false);
}

// ---- Remove --------------------------------------------------------------------------------

enum { kRmFiles = 1, kRmCancel = 90, kRmGo };

void OpenRemoveDialog(const std::vector<int64_t>& ids) {
    if (ids.empty()) return;
    if (Form* old = Form_Find("remove")) Form_Close(*old);
    Form& f = Form_New("remove", L"Remove");
    const Dl* first = FindDl(ids[0]);
    std::wstring title = ids.size() == 1 ? L"Remove " + (first ? first->name : std::wstring(L"this download")) + L"?"
                                         : L"Remove " + std::to_wstring(ids.size()) + L" downloads?";
    Val list = sj::Arr();
    for (int64_t id : ids) list.push(sj::Int(id));
    f.data.set("ids", list);
    f.ctls.push_back(Head(title));
    f.ctls.push_back(Para(L"They leave the list. Files already on the disk stay there unless you turn on the switch below."));
    f.ctls.push_back(Switch(kRmFiles, L"Also delete the files from the disk", L"This cannot be undone.", false));
    f.ctls.push_back(Buttons({{kRmCancel, L"Cancel"}, {kRmGo, L"Remove", kDanger, 0xE74D}}));
    f.defaultBtn = kRmGo;
    f.cancelBtn = kRmCancel;
    f.onChange = [](Form& f, int) { Form_Invalidate(f); };
    f.onButton = [](Form& f, int id) {
        if (id == kRmCancel) {
            Form_Close(f);
            return;
        }
        bool files = Form_Ctl(f, kRmFiles)->on;
        int failed = 0, total = (int)f.data["ids"].size();
        for (auto& one : f.data["ids"].a) {
            Val req = Cmd("remove");
            Val ids = sj::Arr();
            ids.push(sj::Int(one.num()));
            req.set("ids", ids);
            req.set("delete_file", sj::Bool(files));
            if (Call(req).has("error")) failed++;
        }
        g_main.sel.clear();
        Refresh();
        if (failed > 0) Toast(std::to_wstring(failed) + L" could not be removed", true);
        else Toast(total == 1 ? L"Removed" : L"Removed " + std::to_wstring(total));
        Form_Close(f);
    };
    Form_Open(f, false);
}

// ---- Speed limit for one download ------------------------------------------------------------

enum { kSpOn = 1, kSpKb, kSpErr, kSpCancel = 90, kSpSave };

void OpenSpeedDialog(int64_t id) {
    const Dl* d = FindDl(id);
    if (!d) return;
    std::string key = "speed:" + std::to_string(id);
    if (Form_Raise(key)) return;
    Form& f = Form_New(key, L"Speed limit");
    f.tag = id;
    f.ctls.push_back(Head(L"Speed limit for this download"));
    f.ctls.push_back(Para(d->name));
    f.ctls.push_back(Switch(kSpOn, L"Limit this download", L"The total speed limit in Settings still applies on top.", d->speedLimit > 0));
    FCtl kb = EditBox(kSpKb, L"Speed limit in KB per second", d->speedLimit > 0 ? std::to_wstring(std::max<int64_t>(1, d->speedLimit / 1024)) : L"");
    kb.boxW = 160;
    kb.enabled = d->speedLimit > 0;
    f.ctls.push_back(kb);
    f.ctls.push_back(Note(kSpErr));
    f.ctls.push_back(Buttons({{kSpCancel, L"Cancel"}, {kSpSave, L"Save", kPrimary, 0xE73E}}));
    f.defaultBtn = kSpSave;
    f.cancelBtn = kSpCancel;
    f.onChange = [](Form& f, int id) {
        if (id == kSpOn) {
            bool on = Form_Ctl(f, kSpOn)->on;
            Form_Enable(f, kSpKb, on);
            if (on && Form_Ctl(f, kSpKb)->edit) SetFocus(Form_Ctl(f, kSpKb)->edit);
        }
    };
    f.onButton = [](Form& f, int id) {
        if (id == kSpCancel) {
            Form_Close(f);
            return;
        }
        int64_t rate = 0;
        if (Form_Ctl(f, kSpOn)->on) {
            int64_t kb = 0;
            std::wstring err;
            if (!ParseNum(Form_Text(f, kSpKb), L"The speed limit", 1, 10000000, kb, err)) {
                Form_Note(f, kSpErr, err, mocha::red);
                return;
            }
            rate = kb * 1024;
        }
        Val req = Cmd("set_speed_limit");
        req.set("id", sj::Int(f.tag));
        req.set("rate", sj::Int(rate));
        Val v = Call(req);
        if (v.has("error")) {
            Form_Note(f, kSpErr, ErrorOf(v), mocha::red);
            return;
        }
        Refresh();
        Toast(rate == 0 ? L"Speed limit removed" : L"Limited to " + std::to_wstring(rate / 1024) + L" KB per second");
        Form_Close(f);
    };
    Form_Open(f, false);
}

// ---- Check file ------------------------------------------------------------------------------

enum { kCkKind = 1, kCkSum, kCkExpected, kCkVerdict, kCkCopy = 80, kCkClose = 90 };
const PCWSTR kHashKinds[] = {L"MD5", L"SHA-1", L"SHA-256", L"SHA-512"};

std::wstring HashNorm(const std::wstring& s) {
    std::wstring out;
    for (wchar_t c : s)
        if (!iswspace(c)) out += (wchar_t)towlower(c);
    return out;
}

void Check_Verdict(Form& f) {
    std::wstring sum = HashNorm(f.data["sum"].t == Val::Str ? sj::W(f.data["sum"].str()) : L"");
    if (f.data["failed"].truthy()) return;
    if (sum.empty()) {
        Form_Note(f, kCkVerdict, L"", mocha::subtext0);
        return;
    }
    std::wstring want = HashNorm(Form_Text(f, kCkExpected));
    if (want.empty()) Form_Note(f, kCkVerdict, L"Paste the value from the download page to compare.", mocha::subtext0);
    else if (want == sum) Form_Note(f, kCkVerdict, L"Matches. The file is exactly what the site sent.", mocha::green);
    else Form_Note(f, kCkVerdict, L"Does not match. The file may be damaged or changed.", mocha::red);
}

void Check_Run(Form& f) {
    int kind = Form_Ctl(f, kCkKind)->choice;
    f.data.set("sum", Val());
    f.data.set("failed", sj::Bool(false));
    f.data.set("run", sj::Int(f.data["run"].num() + 1));
    int64_t run = f.data["run"].num();
    Form_SetText(f, kCkSum, L"Reading the file");
    Form_EnableButton(f, kCkCopy, false);
    Form_Note(f, kCkVerdict, L"", mocha::subtext0);
    Val req = Cmd("checksum");
    req.set("id", sj::Int(f.tag));
    req.set("kind", sj::WStr(kHashKinds[std::clamp(kind, 0, 3)]));
    uint64_t serial = f.serial;
    StartJob(req, [serial, run](bool ok, const Val& r, const std::wstring& err) {
        Form* f = Form_BySerial(serial);
        if (!f || f->data["run"].num() != run) return;
        if (!ok) {
            f->data.set("failed", sj::Bool(true));
            Form_SetText(*f, kCkSum, L"");
            Form_Note(*f, kCkVerdict, L"Could not read the file: " + err, mocha::red);
            return;
        }
        f->data.set("sum", r["sum"]);
        Form_SetText(*f, kCkSum, sj::W(r["sum"].str()));
        Form_EnableButton(*f, kCkCopy, true);
        Check_Verdict(*f);
    });
}

void OpenCheckDialog(int64_t id) {
    const Dl* d = FindDl(id);
    if (!d) return;
    std::string key = "check:" + std::to_string(id);
    if (Form_Raise(key)) return;
    Form& f = Form_New(key, L"Check file");
    f.tag = id;
    f.ctls.push_back(Para(d->name));
    FCtl kind = Choice(kCkKind, L"Kind of check", {L"MD5", L"SHA-1", L"SHA-256", L"SHA-512"}, 2);
    kind.boxW = 200;
    f.ctls.push_back(kind);
    FCtl sum = EditBox(kCkSum, L"", L"Reading the file");
    sum.readOnly = true;
    sum.lines = 3;
    sum.buttons.push_back({kCkCopy, L"Copy", kPlain, 0xE8C8, false});
    f.ctls.push_back(sum);
    f.ctls.push_back(EditBox(kCkExpected, L"Value from the download page", L"", L"Paste it here to compare"));
    f.ctls.push_back(Note(kCkVerdict));
    f.ctls.push_back(Buttons({{kCkClose, L"Close", kPrimary}}));
    f.defaultBtn = kCkClose;
    f.cancelBtn = kCkClose;
    f.onChange = [](Form& f, int id) {
        if (id == kCkKind) Check_Run(f);
        else if (id == kCkExpected) Check_Verdict(f);
    };
    f.onButton = [](Form& f, int id) {
        if (id == kCkClose) Form_Close(f);
        else if (id == kCkCopy && f.data["sum"].t == Val::Str && SetClipboardText(sj::W(f.data["sum"].str()))) Toast(L"Copied");
    };
    if (!Form_Open(f, false)) return;
    Check_Run(f);
}

// ---- The power countdown when a queue finishes ---------------------------------------------

enum { kPwText = 1, kPwCancel = 90, kPwNow };
constexpr int kPowerSeconds = 60;

void Power_Text(Form& f) {
    int left = (int)f.data["left"].num();
    std::wstring what = PowerWhat(f.data["action"].str());
    for (auto& c : f.ctls) {
        if (c.id == kPwText) c.text = L"The computer will " + what + L" in " + std::to_wstring(left) + (left == 1 ? L" second." : L" seconds.");
        if (c.kind == cBar) c.progress = left / (float)kPowerSeconds;
    }
    Form_Invalidate(f);
}

void Power_Run(Form& f) {
    std::string action = f.data["action"].str();
    f.data.set("done", sj::Bool(true));
    Form_Close(f);
    Val req = Cmd("power");
    req.set("action", sj::Str(action));
    Val v = Call(req);
    if (v.has("error")) {
        Main_Show(false);
        Toast(L"Could not " + PowerWhat(action) + L": " + ErrorOf(v), true);
    }
}

void OpenPowerCountdown(const PowerAsk& ask) {
    if (PowerWhat(ask.action).empty()) return;
    if (Form* old = Form_Find("power")) {
        old->data.set("done", sj::Bool(true));
        Form_Close(*old);
    }
    Form& f = Form_New("power", ask.queue + L" is done");
    f.data.set("action", sj::Str(ask.action));
    f.data.set("left", sj::Int(kPowerSeconds));
    f.ctls.push_back(Head((ask.queue.empty() ? std::wstring(L"The queue") : ask.queue) + L" is done"));
    FCtl text = Para(L"");
    text.id = kPwText;
    f.ctls.push_back(text);
    f.ctls.push_back(Bar());
    f.ctls.push_back(Buttons({{kPwNow, PowerButton(ask.action), kDanger, 0xE7E8}, {kPwCancel, L"Cancel", kPrimary, 0xE711}}));
    f.defaultBtn = kPwCancel;
    f.cancelBtn = kPwCancel;
    f.tickMs = 1000;
    f.onTick = [](Form& f) {
        int left = (int)f.data["left"].num() - 1;
        f.data.set("left", sj::Int(std::max(0, left)));
        Power_Text(f);
        if (left <= 0) Power_Run(f);
    };
    f.onButton = [](Form& f, int id) {
        if (id == kPwNow) Power_Run(f);
        else Form_Close(f);
    };
    f.onClose = [](Form& f) {
        if (!f.data["done"].truthy()) Toast(L"Cancelled. The computer stays on.");
    };
    Power_Text(f);
    Form_Open(f, true);
}

// ---- Site rules ---------------------------------------------------------------------------

enum { kSiPick = 1, kSiSummary, kSiHost, kSiUser, kSiPass, kSiAgent, kSiThreads, kSiKb, kSiErr, kSiDelete = 89, kSiCancel = 90, kSiSave };

std::wstring SiteSummary(const Val& r) {
    std::vector<std::wstring> parts;
    if (!r["username"].str().empty()) parts.push_back(L"Signs in");
    if (!Trim(sj::W(r["user_agent"].str())).empty()) parts.push_back(L"Own browser name");
    int64_t t = r["threads"].num();
    if (t > 0) parts.push_back(Plural(t, L"connection", L"connections"));
    int64_t s = r["speed_limit"].num();
    if (s > 0) parts.push_back(std::to_wstring(std::max<int64_t>(1, s / 1024)) + L" KB/s");
    if (parts.empty()) return L"Uses the normal settings";
    std::wstring out;
    for (size_t k = 0; k < parts.size(); k++) out += (k ? L", " : L"") + parts[k];
    return out;
}

bool CleanHost(const std::wstring& text, std::wstring& host) {
    std::wstring t = Trim(text);
    std::wstring low = Lower(t);
    if (low.rfind(L"https://", 0) == 0) t = t.substr(8);
    else if (low.rfind(L"http://", 0) == 0) t = t.substr(7);
    size_t cut = t.find_first_of(L"/?#");
    host = Lower(cut == std::wstring::npos ? t : t.substr(0, cut));
    bool ok = !host.empty() && host.find_first_of(L" \t") == std::wstring::npos;
    for (size_t k = 0; ok && k < host.size(); k++) {
        wchar_t c = host[k];
        ok = iswalnum(c) || c == L'.' || c == L'-' || c == L'*' || c == L':' || c == L'_';
    }
    return ok;
}

void Site_Fill(Form& f) {
    const Val& rules = g_main.settings["per_host"];
    int pick = Form_Ctl(f, kSiPick)->choice;
    bool isNew = pick >= (int)rules.size();
    Val empty = sj::Obj();
    const Val& r = isNew ? empty : rules[(size_t)pick];
    Form_Note(f, kSiSummary, isNew ? L"A new rule for one site." : SiteSummary(r), mocha::subtext0);
    Form_SetText(f, kSiHost, sj::W(r["host"].str()));
    Form_SetText(f, kSiUser, sj::W(r["username"].str()));
    Form_SetText(f, kSiPass, sj::W(r["password"].str()));
    Form_SetText(f, kSiAgent, sj::W(r["user_agent"].str()));
    Form_SetText(f, kSiThreads, r["threads"].num() > 0 ? std::to_wstring(r["threads"].num()) : L"");
    Form_SetText(f, kSiKb, r["speed_limit"].num() > 0 ? std::to_wstring(std::max<int64_t>(1, r["speed_limit"].num() / 1024)) : L"");
    Form_Note(f, kSiErr, L"", mocha::red);
    if (FCtl* c = Form_Ctl(f, kSiDelete)) c->visible = !isNew;
    for (auto& c : f.ctls)
        if (c.kind == cButtons)
            for (auto& b : c.buttons)
                if (b.id == kSiDelete) b.enabled = !isNew;
    Form_Invalidate(f);
}

std::vector<std::wstring> SiteNames() {
    std::vector<std::wstring> out;
    for (auto& r : g_main.settings["per_host"].a) out.push_back(sj::W(r["host"].str()));
    out.push_back(L"New rule");
    return out;
}

bool Site_Store(Val rules, std::wstring& err) {
    Val partial = sj::Obj();
    partial.set("per_host", std::move(rules));
    Val req = Cmd("set_settings");
    req.set("settings", partial);
    Val v = Call(req);
    if (v.has("error")) {
        err = ErrorOf(v);
        return false;
    }
    Val s = Call(Cmd("settings"));
    if (!s.has("error")) g_main.settings = std::move(s);
    Refresh();
    return true;
}

void OpenSitesDialog() {
    if (Form_Raise("sites")) return;
    if (g_state.load() != State::Running) {
        Toast(L"The download engine is not running", true);
        return;
    }
    Form& f = Form_New("sites", L"Site rules");
    f.ctls.push_back(Para(L"Sign-ins, a browser name, connections or a speed limit for one site. *.example.com covers every part of a site."));
    f.ctls.push_back(Choice(kSiPick, L"Rule", SiteNames(), 0));
    f.ctls.push_back(Note(kSiSummary));
    f.ctls.push_back(EditBox(kSiHost, L"Site", L"", L"files.example.com"));
    FCtl user = EditBox(kSiUser, L"Sign-in name", L""), pass = EditBox(kSiPass, L"Password", L"");
    user.half = pass.half = true;
    pass.password = true;
    f.ctls.push_back(user);
    f.ctls.push_back(pass);
    f.ctls.push_back(EditBox(kSiAgent, L"Browser name", L"", L"Leave empty for the normal one"));
    FCtl threads = EditBox(kSiThreads, L"Connections", L"", L"Normal"), kb = EditBox(kSiKb, L"Speed limit in KB/s", L"", L"None");
    threads.half = kb.half = true;
    f.ctls.push_back(threads);
    f.ctls.push_back(kb);
    f.ctls.push_back(Note(kSiErr));
    f.ctls.push_back(Buttons({{kSiDelete, L"Delete rule", kDanger, 0xE74D}, {kSiCancel, L"Close"}, {kSiSave, L"Save", kPrimary, 0xE73E}}));
    f.defaultBtn = kSiSave;
    f.cancelBtn = kSiCancel;
    f.onChange = [](Form& f, int id) {
        if (id == kSiPick) Site_Fill(f);
    };
    f.onButton = [](Form& f, int id) {
        if (id == kSiCancel) {
            Form_Close(f);
            return;
        }
        Val rules = g_main.settings["per_host"].t == Val::Arr ? g_main.settings["per_host"] : sj::Arr();
        int pick = Form_Ctl(f, kSiPick)->choice;
        bool isNew = pick >= (int)rules.a.size();
        std::wstring err;
        if (id == kSiDelete) {
            if (isNew) return;
            std::wstring host = sj::W(rules.a[pick]["host"].str());
            rules.a.erase(rules.a.begin() + pick);
            if (!Site_Store(rules, err)) {
                Form_Note(f, kSiErr, L"Could not save: " + err, mocha::red);
                return;
            }
            Toast(L"Removed the rule for " + host);
            FCtl* c = Form_Ctl(f, kSiPick);
            c->options = SiteNames();
            c->choice = std::min(pick, (int)c->options.size() - 1);
            Site_Fill(f);
            return;
        }
        std::wstring host;
        if (!CleanHost(Form_Text(f, kSiHost), host)) {
            Form_Note(f, kSiErr, L"Type the site, like files.example.com or *.example.com.", mocha::red);
            return;
        }
        int64_t threads = 0, kb = 0;
        if (!Trim(Form_Text(f, kSiThreads)).empty() && !ParseNum(Form_Text(f, kSiThreads), L"Connections", 0, 32, threads, err)) {
            Form_Note(f, kSiErr, err, mocha::red);
            return;
        }
        if (!Trim(Form_Text(f, kSiKb)).empty() && !ParseNum(Form_Text(f, kSiKb), L"The speed limit", 0, 10000000, kb, err)) {
            Form_Note(f, kSiErr, err, mocha::red);
            return;
        }
        Val rule = isNew ? sj::Obj() : rules.a[pick];
        rule.set("host", sj::WStr(host));
        rule.set("username", sj::WStr(Trim(Form_Text(f, kSiUser))));
        rule.set("password", sj::WStr(Form_Text(f, kSiPass)));
        rule.set("user_agent", sj::WStr(Trim(Form_Text(f, kSiAgent))));
        rule.set("threads", sj::Int(threads));
        rule.set("speed_limit", sj::Int(kb * 1024));
        if (isNew) rules.push(rule);
        else rules.a[pick] = rule;
        if (!Site_Store(rules, err)) {
            Form_Note(f, kSiErr, L"Could not save: " + err, mocha::red);
            return;
        }
        Toast(L"Saved the rule for " + host);
        FCtl* c = Form_Ctl(f, kSiPick);
        c->options = SiteNames();
        c->choice = isNew ? (int)c->options.size() - 2 : pick;
        Site_Fill(f);
    };
    if (!Form_Open(f, false)) return;
    Site_Fill(f);
}

// ---- Getting the engine file ---------------------------------------------------------------

// Seamless Workshop sets the engine up as a dependency. This is the same download, for the owner
// who presses "Get it now" before the Workshop got to it: the release file, checked against its
// published SHA-256 before it is moved into place.
bool DownloadTo(const std::wstring& url, const std::wstring& path) {
    DeleteFileW(path.c_str());
    HRESULT hr = URLDownloadToFileW(nullptr, url.c_str(), path.c_str(), 0, nullptr);
    return SUCCEEDED(hr) && FileExists(path);
}

std::string FileSha256(const std::wstring& path) {
    std::string out;
    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (file == INVALID_HANDLE_VALUE) return out;
    HCRYPTPROV prov = 0;
    HCRYPTHASH hash = 0;
    if (CryptAcquireContextW(&prov, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT) && CryptCreateHash(prov, CALG_SHA_256, 0, 0, &hash)) {
        std::vector<BYTE> buf(1 << 16);
        DWORD got = 0;
        bool ok = true;
        while (ReadFile(file, buf.data(), (DWORD)buf.size(), &got, nullptr) && got > 0)
            if (!CryptHashData(hash, buf.data(), got, 0)) {
                ok = false;
                break;
            }
        BYTE digest[32];
        DWORD len = sizeof(digest);
        if (ok && CryptGetHashParam(hash, HP_HASHVAL, digest, &len, 0)) {
            static const char* hex = "0123456789abcdef";
            for (DWORD k = 0; k < len; k++) {
                out += hex[digest[k] >> 4];
                out += hex[digest[k] & 15];
            }
        }
    }
    if (hash) CryptDestroyHash(hash);
    if (prov) CryptReleaseContext(prov, 0);
    CloseHandle(file);
    return out;
}

std::string ReadSmallFile(const std::wstring& path) {
    std::string out;
    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (file == INVALID_HANDLE_VALUE) return out;
    char buf[4096];
    DWORD got = 0;
    if (ReadFile(file, buf, sizeof(buf), &got, nullptr)) out.assign(buf, got);
    CloseHandle(file);
    return out;
}

DWORD WINAPI FetchThread(void*) {
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    std::wstring ver = kEngineVersion, dir = DataDir() + L"\\engine";
    std::wstring base = std::wstring(kAppRepo) + L"/releases/download/v" + ver + L"/seamless_download_core-" + ver + L".dll";
    std::wstring tmp = dir + L"\\download-" + ver + L".part", sumFile = dir + L"\\download-" + ver + L".sha256";
    SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
    std::wstring fail;
    if (!DownloadTo(base + L".sha256", sumFile)) {
        fail = L"Could not get the engine from GitHub. Check the internet and try again.";
    } else {
        std::string text = ReadSmallFile(sumFile), want;
        for (char c : text) {
            if (isxdigit((unsigned char)c)) want += (char)tolower((unsigned char)c);
            else if (!want.empty()) break;
        }
        if (want.size() != 64) fail = L"The engine's check value on GitHub could not be read.";
        else if (!DownloadTo(base, tmp)) fail = L"Could not get the engine from GitHub. Check the internet and try again.";
        else if (FileSha256(tmp) != want) fail = L"The downloaded engine did not match its check value, so it was not used.";
        else if (!MoveFileExW(tmp.c_str(), EnginePath().c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
            fail = L"The engine was downloaded but could not be put in place.";
    }
    DeleteFileW(tmp.c_str());
    DeleteFileW(sumFile.c_str());
    g_fetching = false;
    if (fail.empty()) {
        PostUi(WM_SDM_NOTICE, 2);
    } else {
        Wh_Log(L"engine download: %s", fail.c_str());
        PostUi(WM_SDM_NOTICE, 3, (LPARAM) new std::wstring(fail));
    }
    Wake();
    CoUninitialize();
    return 0;
}

void FetchEngine() {
    if (g_fetching.exchange(true)) return;
    Main_Invalidate();
    HANDLE t = CreateThread(nullptr, 0, FetchThread, nullptr, 0, nullptr);
    if (t) CloseHandle(t);
    else g_fetching = false;
}

// Opens Seamless Workshop on its Extras page, where the engine shows as a part to set up.
bool OpenWorkshop() {
    HWND ws = FindWindowW(L"SeamlessWorkshopWindow", nullptr);
    if (!ws) return false;
    return PostMessageW(ws, WM_APP + 2, 0, 0) != 0;
}

}  // namespace sdm

// ---- Queues and schedules ------------------------------------------------------------------
// One window: pick a queue, change it, save. Mirrors the app's queue cards.

namespace sdm {

enum {
    kQuPick = 1, kQuState, kQuName, kQuMax, kQuEmpty, kQuPower, kQuDays, kQuStartOn, kQuEndOn, kQuStart, kQuEnd, kQuErr,
    kQuNew = 80, kQuToggle, kQuDelete = 89, kQuClose = 90, kQuSave,
};

const PCWSTR kDayChips[] = {L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat", L"Sun"};
const char* const kDayNames[] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};
const char* const kPowerKeys[] = {"none", "sleep", "hibernate", "shutdown", "restart"};

int PowerIndex(const std::string& s) {
    for (int i = 0; i < 5; i++)
        if (s == kPowerKeys[i]) return i;
    return 0;
}

int WaitingIn(const QueueInfo& q) {
    int n = 0;
    for (int64_t id : q.items)
        if (const Dl* d = FindDl(id))
            if (!d->done()) n++;
    return n;
}

bool ValidTime(const std::wstring& t) {
    std::wstring s = Trim(t);
    if (s.size() != 5 || s[2] != L':') return false;
    for (int i : {0, 1, 3, 4})
        if (!iswdigit(s[i])) return false;
    int h = (s[0] - L'0') * 10 + (s[1] - L'0'), m = (s[3] - L'0') * 10 + (s[4] - L'0');
    return h < 24 && m < 60;
}

const QueueInfo* Queue_Current(Form& f) {
    FCtl* pick = Form_Ctl(f, kQuPick);
    int i = pick ? pick->choice : 0;
    if (i >= 0 && i < (int)g_main.queues.size()) return &g_main.queues[i];
    return nullptr;
}

// The running note and the Start or Stop button follow the engine, even while editing.
void Queue_State(Form& f) {
    const QueueInfo* q = Queue_Current(f);
    FBtn* b = Form_Button(f, kQuToggle);
    if (!q) {
        Form_Note(f, kQuState, L"No queues yet.", mocha::subtext0);
        if (b) b->enabled = false;
        return;
    }
    int waiting = WaitingIn(*q);
    Form_Note(f, kQuState, q->active ? L"Running" : Plural(waiting, L"download waiting", L"downloads waiting"),
              q->active ? mocha::green : mocha::subtext0);
    if (b) {
        b->label = q->active ? L"Stop" : L"Start";
        b->icon = q->active ? 0xE71A : 0xE768;
        b->style = q->active ? kPlain : kPrimary;
        b->enabled = true;
    }
    Form_EnableButton(f, kQuDelete, q->id != 0);
    Form_Relayout(f);
}

void Queue_Fill(Form& f) {
    const QueueInfo* q = Queue_Current(f);
    f.data.set("dirty", sj::Bool(false));
    Form_Note(f, kQuErr, L"", mocha::subtext0);
    if (!q) return;
    const Val& raw = q->raw;
    const Val& sc = raw["schedule"];
    f.tag = q->id;
    Form_SetText(f, kQuName, q->name);
    Form_SetText(f, kQuMax, std::to_wstring(raw["max_concurrent"].num()));
    Form_Ctl(f, kQuEmpty)->on = raw["stop_on_empty"].truthy();
    FCtl* power = Form_Ctl(f, kQuPower);
    power->choice = PowerIndex(raw["power_action"].str());
    power->hint = power->choice == 0 ? L"" : L"You get a minute to cancel first.";
    uint32_t mask = 0;
    for (auto& d : sc["days"].a)
        for (int i = 0; i < 7; i++)
            if (d.str() == kDayNames[i]) mask |= 1u << i;
    Form_Ctl(f, kQuDays)->mask = mask;
    bool startOn = sc["enabled_start"].truthy(), endOn = sc["enabled_end"].truthy();
    Form_Ctl(f, kQuStartOn)->on = startOn;
    Form_Ctl(f, kQuEndOn)->on = endOn;
    Form_SetText(f, kQuStart, sc["start"].t == Val::Str ? sj::W(sc["start"].str()) : L"");
    Form_SetText(f, kQuEnd, sc["end"].t == Val::Str ? sj::W(sc["end"].str()) : L"");
    Form_Enable(f, kQuStart, startOn);
    Form_Enable(f, kQuEnd, endOn);
    Form_EnableButton(f, kQuSave, false);
    Queue_State(f);
}

void Queue_Pick(Form& f, int64_t id) {
    FCtl* pick = Form_Ctl(f, kQuPick);
    pick->options = QueueNames();
    int at = 0;
    for (size_t i = 0; i < g_main.queues.size(); i++)
        if (g_main.queues[i].id == id) at = (int)i;
    pick->choice = std::clamp(at, 0, std::max(0, (int)pick->options.size() - 1));
    Queue_Fill(f);
}

void Queue_Save(Form& f) {
    const QueueInfo* q = Queue_Current(f);
    if (!q) return;
    std::wstring err;
    int64_t max = 0;
    if (!ParseNum(Form_Text(f, kQuMax), L"Downloads at the same time", 1, 50, max, err)) {
        Form_Note(f, kQuErr, err, mocha::red);
        return;
    }
    bool startOn = Form_Ctl(f, kQuStartOn)->on, endOn = Form_Ctl(f, kQuEndOn)->on;
    std::wstring start = Trim(Form_Text(f, kQuStart)), end = Trim(Form_Text(f, kQuEnd));
    if ((startOn && !ValidTime(start)) || (endOn && !ValidTime(end))) {
        Form_Note(f, kQuErr, L"Times look like 02:30, on a 24 hour clock", mocha::red);
        return;
    }
    std::wstring name = Trim(Form_Text(f, kQuName));
    if (name.empty()) {
        Form_Note(f, kQuErr, L"Give the queue a name", mocha::red);
        return;
    }
    Val queue = q->raw;
    queue.set("name", sj::WStr(name));
    queue.set("max_concurrent", sj::Int(max));
    Val sc = queue["schedule"].t == Val::Obj ? queue["schedule"] : sj::Obj();
    Val days = sj::Arr();
    uint32_t mask = Form_Ctl(f, kQuDays)->mask;
    for (int i = 0; i < 7; i++)
        if ((mask >> i) & 1) days.push(sj::Str(kDayNames[i]));
    sc.set("days", days);
    sc.set("enabled_start", sj::Bool(startOn));
    sc.set("start", start.empty() ? Val() : sj::WStr(start));
    sc.set("enabled_end", sj::Bool(endOn));
    sc.set("end", end.empty() ? Val() : sj::WStr(end));
    queue.set("schedule", sc);
    queue.set("stop_on_empty", sj::Bool(Form_Ctl(f, kQuEmpty)->on));
    queue.set("power_action", sj::Str(kPowerKeys[std::clamp(Form_Ctl(f, kQuPower)->choice, 0, 4)]));
    Val req = Cmd("save_queue");
    req.set("queue", queue);
    Val v = Call(req);
    if (v.has("error")) {
        Form_Note(f, kQuErr, L"Could not save: " + ErrorOf(v), mocha::red);
        return;
    }
    f.data.set("dirty", sj::Bool(false));
    Form_EnableButton(f, kQuSave, false);
    Form_Note(f, kQuErr, L"Queue saved", mocha::green);
    Refresh();
}

void Queue_New(Form& f) {
    Val queue = sj::Obj();
    queue.set("id", sj::Int(-1));
    queue.set("name", sj::WStr(L"Queue " + std::to_wstring(g_main.queues.size())));
    queue.set("max_concurrent", sj::Int(2));
    queue.set("items", sj::Arr());
    Val sc = sj::Obj(), days = sj::Arr();
    for (auto d : kDayNames) days.push(sj::Str(d));
    sc.set("days", days);
    sc.set("start", sj::Str("02:30"));
    sc.set("end", sj::Str("07:30"));
    sc.set("enabled_start", sj::Bool(false));
    sc.set("enabled_end", sj::Bool(false));
    queue.set("schedule", sc);
    queue.set("stop_on_empty", sj::Bool(false));
    queue.set("power_action", sj::Str("none"));
    Val req = Cmd("save_queue");
    req.set("queue", queue);
    Val v = Call(req);
    if (v.has("error")) {
        Form_Note(f, kQuErr, L"Could not add a queue: " + ErrorOf(v), mocha::red);
        return;
    }
    // The list catches up on the next poll; pick the new queue then.
    f.data.set("want", sj::Int(v["id"].num()));
    Refresh();
}

void Queue_Delete(Form& f) {
    const QueueInfo* q = Queue_Current(f);
    if (!q || q->id == 0) return;
    Val req = Cmd("delete_queue");
    req.set("id", sj::Int(q->id));
    Val v = Call(req);
    if (v.has("error")) {
        Form_Note(f, kQuErr, L"Could not delete: " + ErrorOf(v), mocha::red);
        return;
    }
    f.data.set("want", sj::Int(0));
    Toast(L"Queue deleted. Its downloads stay in the list.");
    Refresh();
}

void Queues_Changed() {
    Form* f = Form_Find("queues");
    if (!f || !f->hwnd) return;
    FCtl* pick = Form_Ctl(*f, kQuPick);
    if (f->data.has("want") && f->data["want"].t == Val::Num) {
        int64_t want = f->data["want"].num();
        if (FindQueue(want)) {
            f->data.set("want", Val());
            Queue_Pick(*f, want);
            return;
        }
    }
    // Keep the same queue picked by id; refill only when nothing is being edited.
    int64_t id = f->tag;
    pick->options = QueueNames();
    int at = -1;
    for (size_t i = 0; i < g_main.queues.size(); i++)
        if (g_main.queues[i].id == id) at = (int)i;
    if (at < 0) {
        Queue_Pick(*f, 0);
        return;
    }
    pick->choice = at;
    if (!f->data["dirty"].truthy()) Queue_Fill(*f);
    else Queue_State(*f);
}

void OpenQueuesPage(int64_t select) {
    if (Form* old = Form_Find("queues")) {
        if (select >= 0 && FindQueue(select)) Queue_Pick(*old, select);
        Form_Raise("queues");
        return;
    }
    Form& f = Form_New("queues", L"Queues and schedules");
    f.ctls.push_back(Head(L"Queues and schedules"));
    FCtl pick = Choice(kQuPick, L"Queue", QueueNames(), 0);
    f.ctls.push_back(pick);
    FCtl state = Note(kQuState);
    f.ctls.push_back(state);
    f.ctls.push_back(Buttons({{kQuToggle, L"Start", kPrimary, 0xE768}, {kQuNew, L"New queue", kPlain, 0xE710}}));
    f.ctls.push_back(EditBox(kQuName, L"Name", L"", L"Queue name"));
    FCtl max = EditBox(kQuMax, L"Downloads at the same time", L"");
    max.boxW = 90;
    f.ctls.push_back(max);
    f.ctls.push_back(Switch(kQuEmpty, L"Stop when the queue is empty", L"", false));
    FCtl power = Choice(kQuPower, L"When the queue finishes", {L"Do nothing", L"Sleep", L"Hibernate", L"Shut down", L"Restart"}, 0);
    power.boxW = 220;
    f.ctls.push_back(power);
    FCtl days;
    days.kind = cChips;
    days.id = kQuDays;
    days.label = L"Days";
    for (auto d : kDayChips) days.options.push_back(d);
    f.ctls.push_back(days);
    f.ctls.push_back(Switch(kQuStartOn, L"Start at a set time", L"24 hour clock, like 02:30.", false));
    f.ctls.push_back(Switch(kQuEndOn, L"Stop at a set time", L"", false));
    FCtl start = EditBox(kQuStart, L"Start time", L"", L"02:30");
    start.half = true;
    f.ctls.push_back(start);
    FCtl end = EditBox(kQuEnd, L"Stop time", L"", L"07:30");
    end.half = true;
    f.ctls.push_back(end);
    f.ctls.push_back(Note(kQuErr));
    f.ctls.push_back(Buttons({{kQuDelete, L"Delete queue", kDanger, 0xE74D}, {kQuClose, L"Close"}, {kQuSave, L"Save", kPrimary, 0xE73E, false}}));
    f.defaultBtn = kQuSave;
    f.cancelBtn = kQuClose;
    f.onChange = [](Form& f, int id) {
        if (id == kQuPick) {
            Queue_Fill(f);
            return;
        }
        if (id == kQuStartOn) Form_Enable(f, kQuStart, Form_Ctl(f, kQuStartOn)->on);
        if (id == kQuEndOn) Form_Enable(f, kQuEnd, Form_Ctl(f, kQuEndOn)->on);
        if (id == kQuPower) {
            FCtl* p = Form_Ctl(f, kQuPower);
            p->hint = p->choice == 0 ? L"" : L"You get a minute to cancel first.";
            Form_Relayout(f);
        }
        f.data.set("dirty", sj::Bool(true));
        Form_EnableButton(f, kQuSave, true);
        Form_Note(f, kQuErr, L"", mocha::subtext0);
    };
    f.onButton = [](Form& f, int id) {
        switch (id) {
            case kQuClose: Form_Close(f); break;
            case kQuSave: Queue_Save(f); break;
            case kQuNew: Queue_New(f); break;
            case kQuDelete: Queue_Delete(f); break;
            case kQuToggle:
                if (const QueueInfo* q = Queue_Current(f)) ToggleQueue(q->id);
                break;
        }
    };
    if (!Form_Open(f, false)) return;
    Queue_Pick(f, select >= 0 ? select : 0);
}

}  // namespace sdm

// ===========================================================================
// The glue: the settings window's link to the engine, the tray, the UI thread and
// start-up. Comes after every other part.
// ===========================================================================
namespace sdm {

// ---- Shared between the UI thread and the settings thread ----------------------------------

std::mutex g_linkLock;
Val g_statusCache;                       // The engine's last "status", for the browser line.
std::string g_statusDump;
std::wstring g_updateText, g_updateUrl;  // "Check for updates" state.
bool g_updateBusy = false, g_updateNewer = false;
std::atomic<bool> g_setLoaded{false};    // The settings window holds the engine's values.
std::atomic<int> g_startPage{-1};        // A page the settings window should open on.
std::string g_loadedLimitMode;           // Kept so "when busy" survives a save.

constexpr int kPageAbout = 5;

// Asks the settings window to lay its page out again (new link text, a new page).
void Settings_Refresh() {
    if (HWND s = acset::g_settingsWnd) PostMessageW(s, WM_SIZE, IsZoomed(s) ? SIZE_MAXIMIZED : SIZE_RESTORED, 0);
}

void OpenSettings() { acset::OpenSettingsWindow(); }

void OpenAboutPage() {
    g_startPage = kPageAbout;
    acset::OpenSettingsWindow();
    Settings_Refresh();
}

int TakeStartPage() { return g_startPage.exchange(-1); }

// ---- Settings: engine values <-> settings window fields --------------------------------------

struct DnsChoice {
    PCWSTR key;
    PCWSTR url;
};
const DnsChoice kDns[] = {{L"win", L""},
                          {L"cloudflare", L"https://cloudflare-dns.com/dns-query"},
                          {L"google", L"https://dns.google/dns-query"},
                          {L"quad9", L"https://dns.quad9.net/dns-query"}};

std::wstring B(bool v) { return v ? L"1" : L"0"; }

std::vector<std::pair<std::wstring, std::wstring>> LoadSettings() {
    std::vector<std::pair<std::wstring, std::wstring>> out;
    Val s = Call(Cmd("settings"));
    if (s.has("error") || s.t != Val::Obj) {
        g_setLoaded = false;
        return out;
    }
    auto put = [&](PCWSTR k, const std::wstring& v) { out.push_back({k, v}); };
    put(L"sdm.folder", sj::W(s["default_download_folder"].str()));
    put(L"sdm.threads", std::to_wstring(s["thread_count"].num(8)));
    put(L"sdm.concurrent", std::to_wstring(s["max_concurrent_downloads"].num(3)));
    put(L"sdm.retries", std::to_wstring(s["max_retry_count"].num(3)));
    put(L"sdm.split", B(s["dynamic_part_creation"].truthy()));
    put(L"sdm.sortcat", B(s["use_category_by_default"].truthy()));
    std::string mode = s["speed_limit_mode"].str();
    {
        std::lock_guard<std::mutex> lock(g_linkLock);
        g_loadedLimitMode = mode;
    }
    put(L"sdm.limitOn", B(!mode.empty() && mode != "Disabled"));
    int64_t kb = (s["speed_limit"].num(262144) + 512) / 1024;
    put(L"sdm.limitKb", std::to_wstring(std::clamp<int64_t>(kb, 1, 10000000)));
    put(L"sdm.decimal", B(s["size_unit"].str().find("Decimal") != std::string::npos));
    put(L"sdm.markPart", B(s["append_extension_to_incomplete_downloads"].truthy()));
    put(L"sdm.sparse", B(s["use_sparse_file_allocation"].truthy()));
    put(L"sdm.serverDate", B(s["use_server_last_modified_time"].truthy()));
    put(L"sdm.deletePart", B(s["delete_partial_file_on_cancellation"].truthy()));
    put(L"sdm.port", std::to_wstring(s["api_port"].num(15161)));
    put(L"sdm.key", sj::W(s["api_key"].str()));
    std::wstring dns = sj::W(s["dns_over_https"].str()), choice = L"custom", custom = dns;
    for (auto& d : kDns)
        if (dns == d.url) {
            choice = d.key;
            custom.clear();
        }
    put(L"sdm.dns", choice);
    put(L"sdm.dnsUrl", custom);
    put(L"sdm.sound", B(s["notification_sound"].truthy()));
    put(L"sdm.soundDone", sj::W(s["success_notification_sound"].str()));
    put(L"sdm.soundFail", sj::W(s["error_notification_sound"].str()));
    g_setLoaded = true;
    return out;
}

// vals: every sdm field as the window shows it. changed: the keys the owner touched. Only
// those go to the engine, so a value the window never read is never written back.
bool SaveSettings(const std::vector<std::pair<std::wstring, std::wstring>>& vals, const std::vector<std::wstring>& changed,
                  std::wstring& err) {
    if (!g_setLoaded.load()) {
        if (g_state.load() == State::Running) LoadSettings();
        err = g_state.load() != State::Running ? L"Could not save: the download engine is not running"
                                               : L"The download settings were not read yet. Close this window and open it again.";
        return false;
    }
    auto get = [&](PCWSTR k) -> std::wstring {
        for (auto& [key, v] : vals)
            if (key == k) return v;
        return L"";
    };
    auto touched = [&](PCWSTR k) { return std::find(changed.begin(), changed.end(), k) != changed.end(); };
    auto num = [&](PCWSTR k) { return sj::Int(_wtoi64(get(k).c_str())); };
    auto on = [&](PCWSTR k) { return sj::Bool(get(k) == L"1"); };
    Val s = sj::Obj();
    if (touched(L"sdm.folder")) {
        std::wstring folder = Trim(get(L"sdm.folder"));
        if (folder.empty()) {
            err = L"Save files to needs a folder";
            return false;
        }
        s.set("default_download_folder", sj::Str(sj::U8(folder)));
    }
    if (touched(L"sdm.threads")) s.set("thread_count", num(L"sdm.threads"));
    if (touched(L"sdm.concurrent")) s.set("max_concurrent_downloads", num(L"sdm.concurrent"));
    if (touched(L"sdm.retries")) s.set("max_retry_count", num(L"sdm.retries"));
    if (touched(L"sdm.split")) s.set("dynamic_part_creation", on(L"sdm.split"));
    if (touched(L"sdm.sortcat")) s.set("use_category_by_default", on(L"sdm.sortcat"));
    if (touched(L"sdm.limitOn")) {
        std::string was;
        {
            std::lock_guard<std::mutex> lock(g_linkLock);
            was = g_loadedLimitMode;
        }
        bool want = get(L"sdm.limitOn") == L"1";
        s.set("speed_limit_mode", sj::Str(!want ? "Disabled" : was == "EnabledWhenBusy" ? "EnabledWhenBusy" : "Enabled"));
    }
    if (touched(L"sdm.limitKb")) s.set("speed_limit", sj::Int(_wtoi64(get(L"sdm.limitKb").c_str()) * 1024));
    if (touched(L"sdm.decimal")) {
        const char* unit = get(L"sdm.decimal") == L"1" ? "DecimalBytes" : "BinaryBytes";
        s.set("size_unit", sj::Str(unit));
        s.set("speed_unit", sj::Str(unit));
    }
    if (touched(L"sdm.markPart")) s.set("append_extension_to_incomplete_downloads", on(L"sdm.markPart"));
    if (touched(L"sdm.sparse")) s.set("use_sparse_file_allocation", on(L"sdm.sparse"));
    if (touched(L"sdm.serverDate")) s.set("use_server_last_modified_time", on(L"sdm.serverDate"));
    if (touched(L"sdm.deletePart")) s.set("delete_partial_file_on_cancellation", on(L"sdm.deletePart"));
    if (touched(L"sdm.port")) s.set("api_port", num(L"sdm.port"));
    if (touched(L"sdm.key")) s.set("api_key", sj::Str(sj::U8(Trim(get(L"sdm.key")))));
    if (touched(L"sdm.dns") || touched(L"sdm.dnsUrl")) {
        std::wstring choice = get(L"sdm.dns"), url;
        if (choice == L"custom") {
            url = Trim(get(L"sdm.dnsUrl"));
            if (url.compare(0, 8, L"https://") != 0) {
                err = L"The name lookup address must start with https://";
                return false;
            }
        } else {
            for (auto& d : kDns)
                if (choice == d.key) url = d.url;
        }
        s.set("dns_over_https", sj::Str(sj::U8(url)));
    }
    if (touched(L"sdm.sound")) s.set("notification_sound", on(L"sdm.sound"));
    if (touched(L"sdm.soundDone")) s.set("success_notification_sound", sj::Str(sj::U8(Trim(get(L"sdm.soundDone")))));
    if (touched(L"sdm.soundFail")) s.set("error_notification_sound", sj::Str(sj::U8(Trim(get(L"sdm.soundFail")))));
    if (s.size() == 0) return true;
    Val req = Cmd("set_settings");
    req.set("settings", s);
    Val v = Call(req);
    if (v.has("error")) {
        err = L"Could not save: " + ErrorOf(v);
        return false;
    }
    if (touched(L"sdm.limitOn")) {
        std::lock_guard<std::mutex> lock(g_linkLock);
        g_loadedLimitMode = s["speed_limit_mode"].str();
    }
    Refresh();
    return true;
}

// ---- The page banner and the link rows ---------------------------------------------------

std::wstring BannerText() {
    switch (g_state.load()) {
        case State::Running: return L"";
        case State::Starting: return L"The download engine is starting.";
        case State::Missing:
            return g_fetching.load() ? L"Getting the download engine from GitHub."
                                     : L"The download engine is not set up yet. Open the download window to get it, or set it up "
                                       L"in Seamless Workshop under Extras.";
        default: {
            std::wstring t = FailText();
            return t.empty() ? L"The download engine is not running." : t;
        }
    }
}

const PageLink kLinks[] = {
    {0, L"sdm.folder", L"Where files go", L"sdm:folder"},
    {2, nullptr, L"Browser link", L"sdm:status"},
    {2, L"sdm.key", L"Browser link", L"sdm:copykey"},
    {3, L"sdm.soundDone", L"Sounds", L"sdm:sounddone"},
    {3, L"sdm.soundFail", L"Sounds", L"sdm:soundfail"},
    {3, L"", L"Sites", L"sdm:sites"},
};

std::vector<const PageLink*> LinksFor(int page, PCWSTR after) {
    std::vector<const PageLink*> out;
    for (auto& l : kLinks) {
        if (l.page != page) continue;
        if (!after ? !l.after : (l.after && wcscmp(l.after, after) == 0)) out.push_back(&l);
    }
    return out;
}

std::wstring LinkText(PCWSTR url, bool sub) {
    std::wstring u = url;
    if (u == L"sdm:folder") return sub ? L"Pick the folder in a window instead of typing it" : L"Choose folder";
    if (u == L"sdm:copykey")
        return sub ? L"The extension gets it by itself. Copy it only to set it up by hand." : L"Copy the browser key";
    if (u == L"sdm:sounddone") return sub ? L"A .wav file. Leave the box empty for the Windows sound." : L"Choose the finish sound";
    if (u == L"sdm:soundfail") return sub ? L"A .wav file. Leave the box empty for the Windows sound." : L"Choose the fail sound";
    if (u == L"sdm:sites")
        return sub ? L"A sign-in, browser name, connections or speed limit for one site. A * matches any part, and when two rules "
                     L"fit, the one with fewer * wins. Saved straight away."
                   : L"Site rules";
    if (u == L"sdm:status") {
        if (g_state.load() != State::Running) return sub ? L"The download engine is not running." : L"The browser link is off";
        std::lock_guard<std::mutex> lock(g_linkLock);
        bool up = g_statusCache["api_up"].truthy();
        if (!sub) return up ? L"Browsers can send downloads here" : L"The browser link is off";
        std::wstring t = sj::W(g_statusCache["api_text"].str());
        return t.empty() ? L"Click to check again." : t;
    }
    if (u == L"sdm:update") {
        std::lock_guard<std::mutex> lock(g_linkLock);
        if (!sub) return g_updateNewer ? L"Get the new version" : L"Check for updates";
        if (g_updateBusy) return L"Looking for a new version";
        return g_updateText.empty() ? std::wstring(L"You have version ") + kEngineVersion + L"." : g_updateText;
    }
    return L"";
}

acset::SetField* FieldOf(acset::SetWindow& w, PCWSTR key) {
    for (auto& f : w.fields)
        if (wcscmp(f.key, key) == 0) return &f;
    return nullptr;
}

bool CopyText(HWND owner, const std::wstring& text) {
    if (!OpenClipboard(owner)) return false;
    EmptyClipboard();
    bool ok = false;
    size_t bytes = (text.size() + 1) * sizeof(WCHAR);
    if (HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, bytes)) {
        memcpy(GlobalLock(mem), text.c_str(), bytes);
        GlobalUnlock(mem);
        ok = SetClipboardData(CF_UNICODETEXT, mem) != nullptr;
        if (!ok) GlobalFree(mem);
    }
    CloseClipboard();
    return ok;
}

bool PickSound(HWND owner, std::wstring& path) {
    WCHAR file[MAX_PATH]{};
    wcsncpy_s(file, path.c_str(), _TRUNCATE);
    OPENFILENAMEW ofn{sizeof(ofn)};
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = L"Sounds (*.wav)\0*.wav\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = L"Choose a sound";
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_EXPLORER;
    if (!GetOpenFileNameW(&ofn)) return false;
    path = file;
    return true;
}

// A click on one of the link rows. Runs on the settings thread.
void LinkAction(PCWSTR url) {
    auto keep = acset::g_setWin;
    if (!keep || !keep->hwnd) return;
    acset::SetWindow& w = *keep;
    std::wstring u = url;
    auto fill = [&](PCWSTR key, const std::wstring& value) {
        acset::Set_CommitEdit(w, true);
        if (auto* f = FieldOf(w, key)) f->cur = value;
        acset::Set_BuildAndClamp(w);
    };
    if (u == L"sdm:folder") {
        auto* f = FieldOf(w, L"sdm.folder");
        std::wstring folder = f ? f->cur : L"";
        if (PickFolder(w.hwnd, folder)) fill(L"sdm.folder", folder);
    } else if (u == L"sdm:sounddone" || u == L"sdm:soundfail") {
        PCWSTR key = u == L"sdm:sounddone" ? L"sdm.soundDone" : L"sdm.soundFail";
        auto* f = FieldOf(w, key);
        std::wstring path = f ? f->cur : L"";
        if (PickSound(w.hwnd, path)) fill(key, path);
    } else if (u == L"sdm:copykey") {
        acset::Set_CommitEdit(w, true);
        auto* f = FieldOf(w, L"sdm.key");
        std::wstring key = f ? Trim(f->cur) : L"";
        if (key.empty()) acset::Set_SetStatus(w, L"There is no browser key yet. Start the download engine first.", true);
        else if (CopyText(w.hwnd, key)) acset::Set_SetStatus(w, L"Browser key copied");
        else acset::Set_SetStatus(w, L"Could not copy the browser key", true);
    } else if (u == L"sdm:status") {
        Refresh();
    } else if (u == L"sdm:sites") {
        PostUi(WM_SDM_OPEN, 1);
    } else if (u == L"sdm:update") {
        std::wstring open;
        {
            std::lock_guard<std::mutex> lock(g_linkLock);
            if (g_updateNewer) open = g_updateUrl;
        }
        if (!open.empty()) ShellExecuteW(nullptr, L"open", open.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        else PostUi(WM_SDM_OPEN, 2);
    }
}

// ---- Jobs started from the settings window (UI thread) ------------------------------------

void StartUpdateCheck() {
    {
        std::lock_guard<std::mutex> lock(g_linkLock);
        if (g_updateBusy) return;
        g_updateBusy = true;
    }
    Settings_Refresh();
    Val req = Cmd("check_update");
    req.set("current", sj::Str(sj::U8(kEngineVersion)));
    StartJob(req, [](bool ok, const Val& r, const std::wstring& e) {
        {
            std::lock_guard<std::mutex> lock(g_linkLock);
            g_updateBusy = false;
            g_updateNewer = false;
            g_updateUrl.clear();
            if (!ok) g_updateText = L"Could not check: " + e;
            else if (!r["release"].truthy()) g_updateText = L"No public release yet.";
            else if (r["newer"].truthy()) {
                g_updateText = L"Version " + sj::W(r["tag"].str()) + L" is out.";
                g_updateUrl = sj::W(r["url"].str());
                g_updateNewer = !g_updateUrl.empty();
            } else g_updateText = L"You have the newest version.";
        }
        Settings_Refresh();
    });
}

// ---- The tray ------------------------------------------------------------------------------

// Windows files tray settings (shown or hidden) per program and number, and every mod is
// windhawk-mod.exe, so the number comes from the mod id like the other mods' trays.
constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
UINT g_taskbarCreated = 0;
bool g_trayAdded = false;
bool g_trayIconOn = true;
void RemoveTray();
HICON g_trayIcon = nullptr;
std::wstring g_trayTip;
bool g_trayOn = false;

void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// A rounded square drawn with GDI: the download arrow on the blue to mauve gradient, grey
// while the engine is not running.
HICON MakeBadge(bool on, int size) {
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
    HFONT font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0,
                             L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    WCHAR face[64]{};
    GetTextFaceW(dc, 64, face);
    if (_wcsicmp(face, L"Segoe Fluent Icons") != 0) {
        SelectObject(dc, oldFont);
        DeleteObject(font);
        font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0,
                           L"Segoe MDL2 Assets");
        oldFont = SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xE896, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    // Mocha blue 89B4FA to mauve CBA6F7; overlay0 to surface2 when off. Glyph in crust 11111B.
    const float c0[3] = {on ? 0x89 / 255.f : 0x6C / 255.f, on ? 0xB4 / 255.f : 0x70 / 255.f, on ? 0xFA / 255.f : 0x86 / 255.f};
    const float c1[3] = {on ? 0xCB / 255.f : 0x58 / 255.f, on ? 0xA6 / 255.f : 0x5B / 255.f, on ? 0xF7 / 255.f : 0x70 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = base * cov;  // Premultiplied; clear where there is no glyph.
            }
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

std::wstring TrayTipText() {
    std::wstring tip = kAppTitle;
    if (g_state.load() != State::Running) return tip + L": the download engine is not running";
    int active = 0;
    for (auto& d : g_main.all)
        if (d.running()) active++;
    if (active) tip += L": " + Plural(active, L"download", L"downloads") + L" running";
    return tip;
}

void UpdateTray(bool add) {
    if (!g_trayIconOn) {
        RemoveTray();
        return;
    }
    bool on = g_state.load() == State::Running;
    std::wstring tip = TrayTipText();
    if (!add && g_trayAdded && on == g_trayOn && tip == g_trayTip) return;
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    nid.uFlags = NIF_MESSAGE | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_SDM_TRAY;
    wcsncpy_s(nid.szTip, tip.c_str(), _TRUNCATE);
    HICON icon = nullptr;
    if (add || !g_trayAdded || on != g_trayOn) {
        icon = MakeBadge(on, GetSystemMetricsForDpi(SM_CXSMICON, GetDpiForSystem()));
        nid.uFlags |= NIF_ICON;
        nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    } else {
        nid.uFlags |= NIF_ICON;
        nid.hIcon = g_trayIcon;
    }
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
    if (icon) {
        if (g_trayIcon) DestroyIcon(g_trayIcon);
        g_trayIcon = icon;
    }
    g_trayOn = on;
    g_trayTip = tip;
}

void RemoveTray() {
    if (g_trayAdded) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = g_msgWnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
}

// Exit: stops the engine (downloads pause where they are) and hides the windows. The tray
// stays, so the downloads can start again without Windhawk. Stopping can take a moment, so
// it runs off the UI thread.
DWORD WINAPI StopEngineThread(void*) {
    {
        std::lock_guard<std::mutex> lock(g_callLock);
        if (g_eng.stop && g_state.load() == State::Running) g_eng.stop();
    }
    SetFail(L"The download engine is stopped. Press Start to run it again.");
    SetState(State::Stopped);
    Wake();
    return 0;
}

void ExitEngine() {
    Forms_CloseAll();
    if (g_main.hwnd) ShowWindow(g_main.hwnd, SW_HIDE);
    g_shown = false;
    if (HANDLE t = CreateThread(nullptr, 0, StopEngineThread, nullptr, 0, nullptr)) CloseHandle(t);
}

enum : int { kTrayOpen = 100, kTrayAdd, kTrayPause, kTrayResume, kTraySettings, kTrayExit };

void TrayMenu(POINT pt) {
    bool running = g_state.load() == State::Running;
    int cmd = acset::ShowTrayMenu(g_msgWnd, &pt, running, L"");
    switch (cmd) {
        case kTrayOpen: Main_Show(true); break;
        case kTrayAdd:
            Main_Show(true);
            if (Running()) OpenAddDialog(nullptr, ClipboardLink());
            break;
        case kTrayPause: DoSimple("pause_all"); break;
        case kTrayResume: DoSimple("resume_all"); break;
        case kTraySettings: OpenSettings(); break;
        case kTrayExit:
            if (running) ExitEngine();
            else {
                g_restart = true;
                Wake();
            }
            break;
    }
}

// ---- The UI thread ---------------------------------------------------------------------

HANDLE g_uiThread = nullptr, g_uiReady = nullptr, g_instanceMutex = nullptr;

// Start-up notes for test runs: written only while a file named diag.flag sits in the data
// folder, so a normal install never writes anything.
void DiagNote(const std::wstring& line) {
    static int on = -1;
    if (on < 0) on = GetFileAttributesW((DataDir() + L"\\diag.flag").c_str()) != INVALID_FILE_ATTRIBUTES;
    if (!on) return;
    SYSTEMTIME t;
    GetLocalTime(&t);
    WCHAR stamp[32];
    wsprintfW(stamp, L"%02u:%02u:%02u.%03u ", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    std::wstring w = stamp + line + L"\r\n";
    int n = WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), s.data(), n, nullptr, nullptr);
    HANDLE f = CreateFileW((DataDir() + L"\\mod-diag.txt").c_str(), FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE,
                           nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f == INVALID_HANDLE_VALUE) return;
    DWORD done;
    WriteFile(f, s.data(), (DWORD)s.size(), &done, nullptr);
    CloseHandle(f);
}

std::wstring ObjectName(HANDLE h) {
    WCHAR name[256] = L"?";
    DWORD need = 0;
    if (h) GetUserObjectInformationW(h, UOI_NAME, name, sizeof(name), &need);
    return name;
}

LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        g_trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    switch (msg) {
        case WM_CLOSE:
            // The hidden message window lives as long as the mod; a stray close never ends it.
            DiagNote(L"message window got a close request; ignored");
            return 0;
        case WM_DESTROY:
            if (g_msgWnd == hwnd) DiagNote(L"message window destroyed while the mod runs");
            return 0;
        case WM_SDM_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: Main_Show(true); break;
                case WM_CONTEXTMENU: TrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_SDM_POLL: {
            auto* r = (PollResult*)lp;
            if (r->hasStatus) {
                std::string dump = sj::Dump(r->status);
                bool changed;
                {
                    std::lock_guard<std::mutex> lock(g_linkLock);
                    changed = dump != g_statusDump;
                    g_statusDump = dump;
                    g_statusCache = r->status;
                }
                if (changed) Settings_Refresh();
            }
            Main_Apply(*r);
            delete r;
            UpdateTray(false);
            return 0;
        }
        case WM_SDM_ADDREQ: {
            auto* req = (Val*)lp;
            OpenAddDialog(req, L"");
            delete req;
            return 0;
        }
        case WM_SDM_POWER: {
            auto* ask = (PowerAsk*)lp;
            OpenPowerCountdown(*ask);
            delete ask;
            return 0;
        }
        case WM_SDM_NOTICE:
            if (wp == 1) Toast(L"The app no longer starts with Windows. This mod runs the downloads now.");
            else if (wp == 2) Toast(L"The download engine is set up.");
            else if (wp == 3) {
                auto* text = (std::wstring*)lp;
                Toast(*text, true);
                delete text;
            }
            Main_Invalidate();
            Settings_Refresh();
            return 0;
        case WM_SDM_SHOW: Main_Show(false); return 0;
        // Lets a capture script open each window without clicks or focus: 1 show, 2 a toolbar
        // or sidebar action (lp = its id), 3 settings, 4 about, 5 width (lp = pixels), 6 hide, 7 close every dialog.
        case WM_SDM_TEST:
            switch (wp) {
                case 1: Main_Show(false); break;
                case 2: Main_Show(false); Main_Action((int)lp); break;
                case 3: OpenSettings(); break;
                case 4: OpenAboutPage(); break;
                case 5:
                    if (g_main.hwnd) {
                        RECT r;
                        GetWindowRect(g_main.hwnd, &r);
                        SetWindowPos(g_main.hwnd, nullptr, 0, 0, (int)lp, r.bottom - r.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
                    }
                    break;
                case 6:
                    if (g_main.hwnd) ShowWindow(g_main.hwnd, SW_HIDE);
                    break;
                case 7:
                    Forms_CloseAll();
                    if (HWND s = acset::g_settingsWnd) PostMessageW(s, WM_CLOSE, 0, 0);
                    break;
            }
            return 0;
        case WM_SDM_STATE:
            Main_Invalidate();
            UpdateTray(false);
            if (g_state.load() == State::Running && !g_setLoaded.load()) {
                if (HWND s = acset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* reload */, 0, 0);
            }
            Settings_Refresh();
            return 0;
        case WM_SDM_OPEN:
            if (wp == 1) {
                if (Running()) OpenSitesDialog();
            } else if (wp == 2) {
                StartUpdateCheck();
            }
            return 0;
        case WM_SDM_SETTINGS:
            g_glass = Wh_GetIntSetting(L"settingsGlass") != 0;
            g_trayIconOn = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
            UpdateTray(true);
            if (g_main.hwnd) {
                Sdm_ApplyGlass(g_main.hwnd);
                Main_Invalidate();
            }
            if (HWND s = acset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* reload */, 0, 0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

DWORD WINAPI UiThreadProc(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    EnableDarkMenus();
    g_uiThreadId = GetCurrentThreadId();
    UINT dpi = GetDpiForSystem();
    g_iconSmall = MakeBadge(true, GetSystemMetricsForDpi(SM_CXSMICON, dpi));
    g_iconBig = MakeBadge(true, GetSystemMetricsForDpi(SM_CXICON, dpi));
    WNDCLASSW wc{};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.lpszClassName = L"SeamlessDownloadManagerMsg";
    RegisterClassW(&wc);
    HWND w = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, kAppTitle, WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                             wc.hInstance, nullptr);
    DWORD made = GetLastError();
    g_msgWnd = w;
    if (w) {
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        UpdateTray(true);
    }
    {
        WCHAR user[128] = L"?";
        DWORD un = 128, sess = 0;
        GetUserNameW(user, &un);
        ProcessIdToSessionId(GetCurrentProcessId(), &sess);
        WCHAR line[512];
        wsprintfW(line, L"ui start: pid %u session %u user %s station %s desktop %s window %p (error %u) tray %d",
                  GetCurrentProcessId(), sess, user, ObjectName(GetProcessWindowStation()).c_str(),
                  ObjectName(GetThreadDesktop(GetCurrentThreadId())).c_str(), (void*)w, made, g_trayAdded ? 1 : 0);
        DiagNote(line);
    }
    SetEvent(g_uiReady);
    if (!w) {
        CoUninitialize();
        return 1;
    }
    BOOL got;
    while ((got = GetMessageW(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    {
        WCHAR line[128];
        wsprintfW(line, L"ui loop ended: %d (error %u) quit %d", got, got < 0 ? GetLastError() : 0, g_quit ? 1 : 0);
        DiagNote(line);
    }
    Jobs_Stop();
    Forms_CloseAll();
    Main_Destroy();
    Gfx_Release();
    RemoveTray();
    g_msgWnd = nullptr;
    DestroyWindow(w);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    if (g_iconSmall) DestroyIcon(g_iconSmall);
    if (g_iconBig) DestroyIcon(g_iconBig);
    g_iconSmall = g_iconBig = nullptr;
    CoUninitialize();
    return 0;
}

}  // namespace sdm

// ---- Windhawk entry points -------------------------------------------------------------------

BOOL WhTool_ModInit() {
    SeamlessMenuSkin::Init();
    sdm::g_instanceMutex = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessDownloadManagerMod");
    if (sdm::g_instanceMutex && GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(sdm::g_instanceMutex);
        sdm::g_instanceMutex = nullptr;
        ExitProcess(0);
    }
    sdm::g_glass = Wh_GetIntSetting(L"settingsGlass") != 0;
    sdm::g_trayIconOn = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    sdm::g_wake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    sdm::g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    DWORD tid = 0;
    sdm::g_uiThread = CreateThread(nullptr, 0, sdm::UiThreadProc, nullptr, 0, &tid);
    if (sdm::g_uiThread && sdm::g_uiReady) WaitForSingleObject(sdm::g_uiReady, 10000);
    if (sdm::g_uiReady) CloseHandle(sdm::g_uiReady);
    sdm::g_uiReady = nullptr;
    if (!sdm::g_uiThread || !sdm::g_msgWnd || !sdm::g_wake) {
        Wh_Log(L"Couldn't start: %u", GetLastError());
        WhTool_ModUninit();
        return FALSE;
    }
    // The engine starts on its own thread, so a slow disk or a busy port never holds up Windhawk.
    sdm::g_engineThread = CreateThread(nullptr, 0, sdm::EngineThread, nullptr, 0, nullptr);
    if (!sdm::g_engineThread) {
        Wh_Log(L"Couldn't start the engine thread: %u", GetLastError());
        WhTool_ModUninit();
        return FALSE;
    }
    Wh_Log(L"Started");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (HWND w = sdm::g_msgWnd) PostMessageW(w, sdm::WM_SDM_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    SeamlessMenuSkin::Uninit();
    sdm::g_quit = true;
    sdm::Wake();
    acset::CloseSettingsWindow();
    if (sdm::g_uiThread) {
        if (sdm::g_uiThreadId) PostThreadMessageW(sdm::g_uiThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(sdm::g_uiThread, 10000);
        CloseHandle(sdm::g_uiThread);
        sdm::g_uiThread = nullptr;
    }
    // The engine thread calls sdm_stop on its way out. The engine library stays loaded: it
    // may still have threads of its own winding down.
    if (sdm::g_engineThread) {
        WaitForSingleObject(sdm::g_engineThread, 20000);
        CloseHandle(sdm::g_engineThread);
        sdm::g_engineThread = nullptr;
    }
    if (sdm::g_wake) {
        CloseHandle(sdm::g_wake);
        sdm::g_wake = nullptr;
    }
    if (sdm::g_instanceMutex) {
        CloseHandle(sdm::g_instanceMutex);
        sdm::g_instanceMutex = nullptr;
    }
}
