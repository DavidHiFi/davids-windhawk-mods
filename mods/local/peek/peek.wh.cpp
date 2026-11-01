// ==WindhawkMod==
// @id              peek
// @name            Peek
// @description     Select a file in File Explorer and press Space to preview it, like PowerToys Peek
// @version         1.1.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk-mod.exe
// @compilerOptions -ld2d1 -ldwrite -lwindowscodecs -lole32 -loleaut32 -luuid -lgdi32 -luser32 -lshell32 -lshlwapi -ldwmapi -luxtheme -lmfplat -lmfplay
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Peek

Select a file in File Explorer or on the desktop and press Space. A preview
window opens with the picture, text, PDF or document inside. Press Space or
Esc to close it. It works like PowerToys Peek, without PowerToys.

![Peek preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/peek.png)

## What it shows
- **Pictures** (JPG, PNG, GIF, BMP, TIFF, ICO, WebP, HEIC and camera RAW when
  the Windows codec is installed), sized to fit and turned the right way up.
- **Text and code** in a dark, monospaced view. You pick which file types
  count as text.
- **Videos and music** (MP4, MKV, MOV, AVI, WMV, MP3, FLAC, WAV, M4A and
  anything else Windows can play) start playing right away, with a play
  button, a seek bar and the volume at the bottom. Music shows its cover art.
- **PDFs, Office files and anything else** Windows has a preview handler for:
  the same previews the Explorer preview pane shows.
- **Everything else**, folders included: a large icon or thumbnail with the
  name, type, size and date.

## Keys in the preview
| Key | What it does |
|---|---|
| Space or Esc | Close |
| Left, Right | Previous or next file. With several files selected it steps through those, otherwise through the whole folder |
| Enter | Open the file in its normal app and close the preview |

## Keys and mouse for videos and music
| Key or mouse | What it does |
|---|---|
| P, K or the media play key | Play or pause |
| Click the video | Play or pause |
| Ctrl+Left, Ctrl+Right | Back or forward 5 seconds |
| Up, Down, mouse wheel | Volume |
| M, click the volume | Mute |
| Click or drag the bar | Jump to that point |

## Notes
- Space only opens a preview when the file list has the keyboard focus, so
  renaming a file or typing in the address bar works as usual.
- Turn off Peek in PowerToys first if it is still installed. Both would react
  to the same key.
- Animated GIFs show their first frame.

## Credits
Works like [Peek](https://learn.microsoft.com/windows/powertoys/peek) from
Microsoft PowerToys. Written from scratch for Windhawk; it shares no code with
PowerToys.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- hotkey: Space
  $name: Preview key
  $description: The key that opens and closes the preview, for example Space or Ctrl+Space
- onDesktop: true
  $name: Work on the desktop
  $description: Also preview files selected on the desktop
- widthPercent: 60
  $name: Window width (%)
  $description: How wide the preview opens, as a share of the screen
- heightPercent: 75
  $name: Window height (%)
  $description: How tall the preview opens, as a share of the screen
- rememberSize: true
  $name: Remember size and position
  $description: Open where you last moved or resized the preview, until the next sign-in
- alwaysOnTop: false
  $name: Always on top
- closeOnFocusLoss: false
  $name: Close when you click away
- darkMode: true
  $name: Dark window
  $description: Dark title bar and scroll bars
- backgroundColor: "#1e1e2e"
  $name: Background color
  $description: As #RRGGBB
- textColor: "#cdd6f4"
  $name: Text color
  $description: As #RRGGBB
- dimTextColor: "#a6adc8"
  $name: Secondary text color
  $description: Used for file details. As #RRGGBB
- textFont: Cascadia Mono
  $name: Text and code font
- textSize: 11
  $name: Text and code size (pt)
- wordWrap: true
  $name: Wrap long lines
- maxTextSizeKB: 4096
  $name: Largest text shown (KB)
  $description: Bigger files show their first part only
- upscaleImages: false
  $name: Enlarge small pictures
  $description: Stretch pictures smaller than the window to fill it
- usePreviewHandlers: true
  $name: Use Windows preview handlers
  $description: Show PDFs, Office files and more the way the Explorer preview pane does
- playMedia: true
  $name: Play videos and music
  $description: Play them inside the preview. Turn off to show only the cover or a frame
- autoPlay: true
  $name: Start playing right away
- accentColor: "#cba6f7"
  $name: Accent color
  $description: The play button and the seek bar. As #RRGGBB
- textExtensions: txt log ini inf cfg conf config json jsonc xml yml yaml toml md markdown csv tsv ps1 psm1 psd1 bat cmd sh bash zsh py pyw js mjs cjs ts tsx jsx css scss less html htm c cc cpp cxx h hh hpp hxx cs java kt go rs lua rb php pl swift sql reg gsc csc gitignore gitattributes editorconfig env diff patch srt vtt nfo
  $name: Text file types
  $description: Extensions to show as plain text, separated by spaces. Files with other extensions still show as text when they look like text and nothing else can preview them
*/
// ==/WindhawkModSettings==

#include <windhawk_tool_mod.h>

#include <d2d1.h>
#include <dwmapi.h>
#include <dwrite.h>
#include <exdisp.h>
#include <mfapi.h>
#include <mfplay.h>
#include <shlguid.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <shobjidl.h>
#include <uxtheme.h>
#include <wincodec.h>
#include <windowsx.h>
#include <wrl/client.h>

#include <algorithm>
#include <atomic>
#include <memory>
#include <string>
#include <vector>

using Microsoft::WRL::ComPtr;

namespace {

constexpr UINT WM_APP_PEEK = WM_APP + 1;
constexpr UINT WM_APP_KEY = WM_APP + 2;
constexpr UINT WM_APP_SETTINGS = WM_APP + 3;

constexpr UINT_PTR kMediaTimer = 1;
constexpr UINT_PTR kArtTimer = 2;

enum class Key { Close, Prev, Next, Open, PlayPause, SeekBack, SeekFwd, VolUp, VolDown, Mute };

////////////////////////////////////////////////////////////////////////////////
// Settings

struct Settings {
    UINT hotMods = 0, hotVk = VK_SPACE;
    bool onDesktop = true, rememberSize = true, alwaysOnTop = false;
    bool closeOnFocusLoss = false, darkMode = true, wordWrap = true;
    bool upscaleImages = false, usePreviewHandlers = true, playMedia = true, autoPlay = true;
    int widthPercent = 60, heightPercent = 75;
    COLORREF bg = RGB(0x1e, 0x1e, 0x2e), fg = RGB(0xcd, 0xd6, 0xf4),
             dim = RGB(0xa6, 0xad, 0xc8), accent = RGB(0xcb, 0xa6, 0xf7);
    std::wstring textFont = L"Cascadia Mono";
    int textSize = 11;
    size_t maxTextBytes = 4096 * 1024;
    std::vector<std::wstring> textExts;
} g_set;

std::wstring ReadString(PCWSTR name) {
    PCWSTR value = Wh_GetStringSetting(name);
    std::wstring result = value ? value : L"";
    Wh_FreeStringSetting(value);
    return result;
}

std::wstring Lower(std::wstring s) {
    for (auto& c : s) c = (wchar_t)towlower(c);
    return s;
}

std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t");
    if (a == std::wstring::npos) return L"";
    size_t b = s.find_last_not_of(L" \t");
    return s.substr(a, b - a + 1);
}

COLORREF ParseColor(const std::wstring& text, COLORREF fallback) {
    std::wstring s = Trim(text);
    if (!s.empty() && s[0] == L'#') s.erase(0, 1);
    if (s.size() != 6) return fallback;
    wchar_t* end = nullptr;
    unsigned long v = wcstoul(s.c_str(), &end, 16);
    if (*end) return fallback;
    return RGB((v >> 16) & 0xff, (v >> 8) & 0xff, v & 0xff);
}

UINT KeyNameToVk(const std::wstring& name) {
    std::wstring k = Lower(name);
    if (k == L"space") return VK_SPACE;
    if (k == L"enter" || k == L"return") return VK_RETURN;
    if (k == L"tab") return VK_TAB;
    if (k.size() == 1 && ((k[0] >= L'a' && k[0] <= L'z') || (k[0] >= L'0' && k[0] <= L'9')))
        return towupper(k[0]);
    if (k.size() >= 2 && k[0] == L'f') {
        int n = _wtoi(k.c_str() + 1);
        if (n >= 1 && n <= 24) return VK_F1 + n - 1;
    }
    return 0;
}

bool ParseHotkey(const std::wstring& text, UINT* mods, UINT* vk) {
    *mods = 0;
    *vk = 0;
    size_t start = 0;
    std::wstring s = Trim(text);
    while (start <= s.size()) {
        size_t plus = s.find(L'+', start);
        std::wstring part = Trim(
            s.substr(start, plus == std::wstring::npos ? std::wstring::npos : plus - start));
        std::wstring k = Lower(part);
        if (k == L"ctrl" || k == L"control") {
            *mods |= MOD_CONTROL;
        } else if (k == L"alt") {
            *mods |= MOD_ALT;
        } else if (k == L"shift") {
            *mods |= MOD_SHIFT;
        } else if (k == L"win" || k == L"windows") {
            *mods |= MOD_WIN;
        } else if (!part.empty()) {
            *vk = KeyNameToVk(part);
            if (!*vk) return false;
        }
        if (plus == std::wstring::npos) break;
        start = plus + 1;
    }
    return *vk != 0;
}

void LoadSettings() {
    if (!ParseHotkey(ReadString(L"hotkey"), &g_set.hotMods, &g_set.hotVk)) {
        Wh_Log(L"Bad preview key, using Space");
        g_set.hotMods = 0;
        g_set.hotVk = VK_SPACE;
    }
    g_set.onDesktop = Wh_GetIntSetting(L"onDesktop");
    g_set.widthPercent = std::clamp(Wh_GetIntSetting(L"widthPercent"), 20, 100);
    g_set.heightPercent = std::clamp(Wh_GetIntSetting(L"heightPercent"), 20, 100);
    g_set.rememberSize = Wh_GetIntSetting(L"rememberSize");
    g_set.alwaysOnTop = Wh_GetIntSetting(L"alwaysOnTop");
    g_set.closeOnFocusLoss = Wh_GetIntSetting(L"closeOnFocusLoss");
    g_set.darkMode = Wh_GetIntSetting(L"darkMode");
    g_set.bg = ParseColor(ReadString(L"backgroundColor"), RGB(0x1e, 0x1e, 0x2e));
    g_set.fg = ParseColor(ReadString(L"textColor"), RGB(0xcd, 0xd6, 0xf4));
    g_set.dim = ParseColor(ReadString(L"dimTextColor"), RGB(0xa6, 0xad, 0xc8));
    g_set.textFont = ReadString(L"textFont");
    if (g_set.textFont.empty()) g_set.textFont = L"Cascadia Mono";
    g_set.textSize = std::clamp(Wh_GetIntSetting(L"textSize"), 6, 72);
    g_set.wordWrap = Wh_GetIntSetting(L"wordWrap");
    g_set.maxTextBytes = (size_t)std::clamp(Wh_GetIntSetting(L"maxTextSizeKB"), 4, 262144) * 1024;
    g_set.upscaleImages = Wh_GetIntSetting(L"upscaleImages");
    g_set.usePreviewHandlers = Wh_GetIntSetting(L"usePreviewHandlers");
    g_set.playMedia = Wh_GetIntSetting(L"playMedia");
    g_set.autoPlay = Wh_GetIntSetting(L"autoPlay");
    g_set.accent = ParseColor(ReadString(L"accentColor"), RGB(0xcb, 0xa6, 0xf7));
    g_set.textExts.clear();
    std::wstring exts = Lower(ReadString(L"textExtensions")) + L" ";
    std::wstring cur;
    for (wchar_t c : exts) {
        if (c == L' ' || c == L',' || c == L';') {
            if (!cur.empty() && cur[0] == L'.') cur.erase(0, 1);
            if (!cur.empty()) g_set.textExts.push_back(cur);
            cur.clear();
        } else {
            cur += c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// State

struct PidlFree {
    void operator()(ITEMIDLIST* p) const { ILFree(p); }
};
using Pidl = std::unique_ptr<ITEMIDLIST, PidlFree>;

enum class Mode { None, Image, Text, Handler, Info, Media };

struct State {
    HWND msgWnd = nullptr, wnd = nullptr, edit = nullptr, host = nullptr, video = nullptr;
    HICON iconSmall = nullptr, iconBig = nullptr;
    HWND source = nullptr;
    HHOOK hook = nullptr;
    HANDLE hookThread = nullptr;
    DWORD hookThreadId = 0;
    bool swallowUp = false;
    std::vector<Pidl> items;
    size_t index = 0;
    Mode mode = Mode::None;
    std::wstring path, name;
    RECT lastRect{};
    bool haveLastRect = false;
    HFONT textFont = nullptr;
    HBRUSH bgBrush = nullptr;

    ComPtr<ID2D1Factory> d2d;
    ComPtr<IDWriteFactory> dwrite;
    ComPtr<IWICImagingFactory> wic;
    ComPtr<ID2D1HwndRenderTarget> rt;
    ComPtr<IWICBitmapSource> image;  // image or thumbnail, 32bppPBGRA
    ComPtr<ID2D1Bitmap> bitmap;
    std::vector<std::wstring> infoLines;

    ComPtr<IPreviewHandler> handler;

    // Videos and music. MFPlay renders video into the `video` child window and
    // calls back on this thread, so no locking is needed.
    ComPtr<IMFPMediaPlayer> player;
    MFP_MEDIAPLAYER_STATE playerState = MFP_MEDIAPLAYER_STATE_EMPTY;
    bool mediaReady = false, mediaHasVideo = false, mediaEnded = false;
    bool muted = false, dragging = false;
    float volume = 1.0f;  // kept between files until the mod reloads
    LONGLONG duration = 0, dragPos = 0;  // 100 ns units
} g;

// Read by the keyboard hook thread.
std::atomic<bool> g_mediaKeys{false};

HANDLE g_thread = nullptr;
HANDLE g_ready = nullptr;
DWORD g_threadId = 0;

std::wstring ClassOf(HWND hwnd) {
    wchar_t buf[64] = {};
    if (hwnd) GetClassNameW(hwnd, buf, 64);
    return buf;
}

////////////////////////////////////////////////////////////////////////////////
// Keyboard: runs on every key press, so it only reads window classes.

bool ModsMatch(UINT mods) {
    auto down = [](int vk) { return (GetAsyncKeyState(vk) & 0x8000) != 0; };
    UINT now = 0;
    if (down(VK_CONTROL)) now |= MOD_CONTROL;
    if (down(VK_MENU)) now |= MOD_ALT;
    if (down(VK_SHIFT)) now |= MOD_SHIFT;
    if (down(VK_LWIN) || down(VK_RWIN)) now |= MOD_WIN;
    return now == mods;
}

bool IsExplorerFileList(HWND top) {
    std::wstring cls = ClassOf(top);
    bool cabinet = cls == L"CabinetWClass" || cls == L"ExploreWClass";
    bool desktop = cls == L"Progman" || cls == L"WorkerW";
    if (!cabinet && !(desktop && g_set.onDesktop)) return false;
    GUITHREADINFO gti{sizeof(gti)};
    if (!GetGUIThreadInfo(GetWindowThreadProcessId(top, nullptr), &gti)) return false;
    if (!gti.hwndFocus || (gti.flags & GUI_INMENUMODE)) return false;
    // The view control itself must have focus. The rename box is an Edit whose
    // parent is also the DefView, so the parent check alone would eat spaces
    // mid-rename.
    if (ClassOf(gti.hwndFocus) != L"DirectUIHWND") return false;
    return ClassOf(GetParent(gti.hwndFocus)) == L"SHELLDLL_DefView";
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code != HC_ACTION) return CallNextHookEx(nullptr, code, wParam, lParam);
    auto* kb = (KBDLLHOOKSTRUCT*)lParam;
    bool keyDown = wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN;
    if (kb->flags & LLKHF_INJECTED) return CallNextHookEx(nullptr, code, wParam, lParam);

    if (!keyDown) {
        if (g.swallowUp && kb->vkCode == g_set.hotVk) {
            g.swallowUp = false;
            return 1;
        }
        return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    HWND top = GetForegroundWindow();
    bool hot = kb->vkCode == g_set.hotVk && ModsMatch(g_set.hotMods);

    if (g.wnd && top == g.wnd) {
        int key = -1;
        DWORD vk = kb->vkCode;
        if (hot || vk == VK_ESCAPE) key = (int)Key::Close;
        else if (g_mediaKeys && ModsMatch(0) && (vk == 'P' || vk == 'K' || vk == VK_MEDIA_PLAY_PAUSE))
            key = (int)Key::PlayPause;
        else if (g_mediaKeys && vk == VK_LEFT && ModsMatch(MOD_CONTROL)) key = (int)Key::SeekBack;
        else if (g_mediaKeys && vk == VK_RIGHT && ModsMatch(MOD_CONTROL)) key = (int)Key::SeekFwd;
        else if (g_mediaKeys && vk == VK_UP && ModsMatch(0)) key = (int)Key::VolUp;
        else if (g_mediaKeys && vk == VK_DOWN && ModsMatch(0)) key = (int)Key::VolDown;
        else if (g_mediaKeys && vk == 'M' && ModsMatch(0)) key = (int)Key::Mute;
        else if (kb->vkCode == VK_LEFT && ModsMatch(0)) key = (int)Key::Prev;
        else if (kb->vkCode == VK_RIGHT && ModsMatch(0)) key = (int)Key::Next;
        else if (kb->vkCode == VK_RETURN && ModsMatch(0)) key = (int)Key::Open;
        if (key >= 0) {
            if (hot) g.swallowUp = true;
            PostMessageW(g.msgWnd, WM_APP_KEY, key, 0);
            return 1;
        }
    } else if (hot && IsExplorerFileList(top)) {
        g.swallowUp = true;
        PostMessageW(g.msgWnd, WM_APP_PEEK, (WPARAM)top, 0);
        return 1;
    }
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
// Explorer selection

ComPtr<IShellBrowser> BrowserFor(HWND top) {
    ComPtr<IShellWindows> windows;
    if (FAILED(CoCreateInstance(CLSID_ShellWindows, nullptr, CLSCTX_ALL,
                                IID_PPV_ARGS(&windows))))
        return nullptr;

    ComPtr<IDispatch> disp;
    std::wstring cls = ClassOf(top);
    if (cls == L"Progman" || cls == L"WorkerW") {
        VARIANT empty{};
        long hwnd = 0;
        windows->FindWindowSW(&empty, &empty, SWC_DESKTOP, &hwnd, SWFO_NEEDDISPATCH, &disp);
        ComPtr<IServiceProvider> sp;
        ComPtr<IShellBrowser> browser;
        if (disp && SUCCEEDED(disp.As(&sp)))
            sp->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&browser));
        return browser;
    }

    // Each Explorer tab is its own shell window; the visible tab is the active one.
    HWND activeTab = nullptr;
    for (HWND t = nullptr; (t = FindWindowExW(top, t, L"ShellTabWindowClass", nullptr));) {
        if (IsWindowVisible(t)) {
            activeTab = t;
            break;
        }
    }

    long count = 0;
    windows->get_Count(&count);
    for (long i = 0; i < count; i++) {
        VARIANT v{};
        v.vt = VT_I4;
        v.lVal = i;
        disp.Reset();
        if (FAILED(windows->Item(v, &disp)) || !disp) continue;
        ComPtr<IWebBrowserApp> app;
        SHANDLE_PTR hwnd = 0;
        if (FAILED(disp.As(&app)) || FAILED(app->get_HWND(&hwnd)) || (HWND)hwnd != top)
            continue;
        ComPtr<IServiceProvider> sp;
        ComPtr<IShellBrowser> browser;
        if (FAILED(disp.As(&sp)) ||
            FAILED(sp->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&browser))))
            continue;
        HWND tab = nullptr;
        browser->GetWindow(&tab);
        if (activeTab && tab != activeTab) continue;
        return browser;
    }
    return nullptr;
}

// One round trip: the view hands back every item as a shell ID list.
std::vector<Pidl> ItemsFromView(IFolderView* view, UINT which) {
    std::vector<Pidl> out;
    ComPtr<IDataObject> data;
    if (FAILED(view->Items(which | SVGIO_FLAG_VIEWORDER, IID_PPV_ARGS(&data)))) return out;
    FORMATETC fe{(CLIPFORMAT)RegisterClipboardFormatW(CFSTR_SHELLIDLIST), nullptr,
                 DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
    STGMEDIUM sm{};
    if (FAILED(data->GetData(&fe, &sm))) return out;
    if (auto* cida = (CIDA*)GlobalLock(sm.hGlobal)) {
        auto base = (const BYTE*)cida;
        auto parent = (PCIDLIST_ABSOLUTE)(base + cida->aoffset[0]);
        for (UINT i = 1; i <= cida->cidl; i++) {
            auto child = (PCUIDLIST_RELATIVE)(base + cida->aoffset[i]);
            if (auto full = ILCombine(parent, child)) out.emplace_back(full);
        }
        GlobalUnlock(sm.hGlobal);
    }
    ReleaseStgMedium(&sm);
    return out;
}

bool ReadSelection(HWND top) {
    ComPtr<IShellBrowser> browser = BrowserFor(top);
    ComPtr<IShellView> shellView;
    ComPtr<IFolderView> view;
    if (!browser || FAILED(browser->QueryActiveShellView(&shellView)) ||
        FAILED(shellView.As(&view)))
        return false;

    std::vector<Pidl> selected = ItemsFromView(view.Get(), SVGIO_SELECTION);
    if (selected.empty()) return false;
    if (selected.size() > 1) {
        g.items = std::move(selected);
        g.index = 0;
        return true;
    }
    g.items = ItemsFromView(view.Get(), SVGIO_ALLVIEW);
    g.index = 0;
    for (size_t i = 0; i < g.items.size(); i++) {
        if (ILIsEqual(g.items[i].get(), selected[0].get())) {
            g.index = i;
            return true;
        }
    }
    g.items = std::move(selected);
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Loading content

bool HasTextExtension(const std::wstring& path) {
    PCWSTR ext = PathFindExtensionW(path.c_str());
    std::wstring e = Lower(*ext ? ext + 1 : PathFindFileNameW(path.c_str()));
    if (!e.empty() && e[0] == L'.') e.erase(0, 1);
    return std::find(g_set.textExts.begin(), g_set.textExts.end(), e) != g_set.textExts.end();
}

// Returns false for files that don't look like text.
bool LoadText(const std::wstring& path, bool mustLookLikeText, std::wstring* out) {
    HANDLE f = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                           nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (f == INVALID_HANDLE_VALUE) return false;
    LARGE_INTEGER size{};
    GetFileSizeEx(f, &size);
    size_t want = (size_t)std::min<LONGLONG>(size.QuadPart, (LONGLONG)g_set.maxTextBytes);
    std::string bytes(want, '\0');
    DWORD got = 0;
    BOOL ok = want ? ReadFile(f, bytes.data(), (DWORD)want, &got, nullptr) : TRUE;
    CloseHandle(f);
    if (!ok) return false;
    bytes.resize(got);
    bool truncated = (LONGLONG)got < size.QuadPart;

    std::wstring text;
    auto u8 = [](const std::string& b, size_t skip, bool strict, std::wstring* w) {
        int n = MultiByteToWideChar(CP_UTF8, strict ? MB_ERR_INVALID_CHARS : 0, b.data() + skip,
                                    (int)(b.size() - skip), nullptr, 0);
        if (n <= 0) return b.size() == skip;
        w->resize(n);
        MultiByteToWideChar(CP_UTF8, 0, b.data() + skip, (int)(b.size() - skip), w->data(), n);
        return true;
    };
    if (got >= 2 && (BYTE)bytes[0] == 0xFF && (BYTE)bytes[1] == 0xFE) {
        text.assign((const wchar_t*)(bytes.data() + 2), (got - 2) / 2);
    } else if (got >= 2 && (BYTE)bytes[0] == 0xFE && (BYTE)bytes[1] == 0xFF) {
        text.resize((got - 2) / 2);
        for (size_t i = 0; i < text.size(); i++)
            text[i] = (wchar_t)(((BYTE)bytes[2 + i * 2] << 8) | (BYTE)bytes[3 + i * 2]);
    } else if (got >= 3 && (BYTE)bytes[0] == 0xEF && (BYTE)bytes[1] == 0xBB && (BYTE)bytes[2] == 0xBF) {
        u8(bytes, 3, false, &text);
    } else {
        if (mustLookLikeText && bytes.find('\0') != std::string::npos) return false;
        // A cut at the size limit can split a UTF-8 character; drop the partial bytes.
        std::string trimmed = bytes;
        if (truncated) {
            size_t i = trimmed.size(), back = 0;
            while (i > 0 && back < 3 && ((BYTE)trimmed[i - 1] & 0xC0) == 0x80) i--, back++;
            if (i > 0 && (BYTE)trimmed[i - 1] >= 0xC0) trimmed.resize(i - 1);
        }
        if (!u8(trimmed, 0, true, &text)) {
            if (mustLookLikeText) return false;
            int n = MultiByteToWideChar(CP_ACP, 0, bytes.data(), (int)bytes.size(), nullptr, 0);
            text.resize(n);
            MultiByteToWideChar(CP_ACP, 0, bytes.data(), (int)bytes.size(), text.data(), n);
        }
    }

    // The edit control wants CRLF line ends and stops at a NUL.
    out->clear();
    out->reserve(text.size() + text.size() / 32);
    for (size_t i = 0; i < text.size(); i++) {
        wchar_t c = text[i];
        if (c == L'\0') c = L' ';
        if (c == L'\n' && (i == 0 || text[i - 1] != L'\r')) out->push_back(L'\r');
        if (c == L'\r' && (i + 1 >= text.size() || text[i + 1] != L'\n')) {
            out->append(L"\r\n");
            continue;
        }
        out->push_back(c);
    }
    if (truncated) {
        wchar_t note[96];
        swprintf(note, 96, L"\r\n\r\n[Showing the first %zu KB]", g_set.maxTextBytes / 1024);
        out->append(note);
    }
    return true;
}

WICBitmapTransformOptions OrientationOf(IWICBitmapFrameDecode* frame) {
    ComPtr<IWICMetadataQueryReader> reader;
    if (FAILED(frame->GetMetadataQueryReader(&reader))) return WICBitmapTransformRotate0;
    PROPVARIANT pv;
    PropVariantInit(&pv);
    UINT value = 1;
    for (PCWSTR q : {L"/app1/ifd/{ushort=274}", L"/ifd/{ushort=274}"}) {
        if (SUCCEEDED(reader->GetMetadataByName(q, &pv))) {
            if (pv.vt == VT_UI2) value = pv.uiVal;
            PropVariantClear(&pv);
            break;
        }
    }
    switch (value) {
        case 3: return WICBitmapTransformRotate180;
        case 6: return WICBitmapTransformRotate90;
        case 8: return WICBitmapTransformRotate270;
        default: return WICBitmapTransformRotate0;
    }
}

ComPtr<IWICBitmapSource> ToPbgra(IWICBitmapSource* src) {
    ComPtr<IWICFormatConverter> conv;
    if (FAILED(g.wic->CreateFormatConverter(&conv)) ||
        FAILED(conv->Initialize(src, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
                                nullptr, 0, WICBitmapPaletteTypeMedianCut)))
        return nullptr;
    return conv;
}

ComPtr<IWICBitmapSource> LoadImage(const std::wstring& path) {
    ComPtr<IWICBitmapDecoder> dec;
    ComPtr<IWICBitmapFrameDecode> frame;
    if (FAILED(g.wic->CreateDecoderFromFilename(path.c_str(), nullptr, GENERIC_READ,
                                                WICDecodeMetadataCacheOnDemand, &dec)) ||
        FAILED(dec->GetFrame(0, &frame)))
        return nullptr;
    ComPtr<IWICBitmapSource> src = frame;
    WICBitmapTransformOptions turn = OrientationOf(frame.Get());
    if (turn != WICBitmapTransformRotate0) {
        ComPtr<IWICBitmapFlipRotator> rot;
        if (SUCCEEDED(g.wic->CreateBitmapFlipRotator(&rot)) &&
            SUCCEEDED(rot->Initialize(frame.Get(), turn)))
            src = rot;
    }
    // Decode once into memory so painting and resizing stay fast.
    ComPtr<IWICBitmapSource> pbgra = ToPbgra(src.Get());
    ComPtr<IWICBitmap> mem;
    if (!pbgra || FAILED(g.wic->CreateBitmapFromSource(pbgra.Get(), WICBitmapCacheOnLoad, &mem)))
        return nullptr;
    return mem;
}

ComPtr<IWICBitmapSource> LoadThumbnail(IShellItem* item, int size) {
    ComPtr<IShellItemImageFactory> factory;
    HBITMAP hbm = nullptr;
    if (FAILED(item->QueryInterface(IID_PPV_ARGS(&factory))) ||
        FAILED(factory->GetImage({size, size}, SIIGBF_BIGGERSIZEOK, &hbm)))
        return nullptr;
    ComPtr<IWICBitmap> wb;
    g.wic->CreateBitmapFromHBITMAP(hbm, nullptr, WICBitmapUsePremultipliedAlpha, &wb);
    DeleteObject(hbm);
    return wb ? ToPbgra(wb.Get()) : nullptr;
}

std::wstring FormatTime(const FILETIME& ft) {
    FILETIME local;
    SYSTEMTIME st;
    if (!FileTimeToLocalFileTime(&ft, &local) || !FileTimeToSystemTime(&local, &st)) return L"";
    wchar_t d[64] = {}, t[64] = {};
    GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, DATE_LONGDATE, &st, nullptr, d, 64, nullptr);
    GetTimeFormatEx(LOCALE_NAME_USER_DEFAULT, TIME_NOSECONDS, &st, nullptr, t, 64);
    return std::wstring(d) + L", " + t;
}

void BuildInfo(IShellItem* item) {
    g.infoLines.clear();
    g.infoLines.push_back(g.name);
    if (g.path.empty()) return;
    SHFILEINFOW sfi{};
    if (SHGetFileInfoW(g.path.c_str(), 0, &sfi, sizeof(sfi), SHGFI_TYPENAME))
        g.infoLines.push_back(sfi.szTypeName);
    WIN32_FILE_ATTRIBUTE_DATA fa{};
    if (GetFileAttributesExW(g.path.c_str(), GetFileExInfoStandard, &fa)) {
        if (!(fa.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            wchar_t size[64] = {};
            ULONGLONG bytes = ((ULONGLONG)fa.nFileSizeHigh << 32) | fa.nFileSizeLow;
            StrFormatByteSizeEx(bytes, SFBS_FLAGS_ROUND_TO_NEAREST_DISPLAYED_DIGIT, size, 64);
            g.infoLines.push_back(size);
        }
        g.infoLines.push_back(L"Modified " + FormatTime(fa.ftLastWriteTime));
    }
    g.infoLines.push_back(g.path);
}

////////////////////////////////////////////////////////////////////////////////
// Preview handlers: the same previews the Explorer preview pane hosts.

void UnloadHandler() {
    if (g.handler) {
        g.handler->Unload();
        g.handler.Reset();
    }
}

RECT ContentRect() {
    RECT rc{};
    GetClientRect(g.wnd, &rc);
    return rc;
}

bool LoadHandler(const std::wstring& path) {
    PCWSTR ext = PathFindExtensionW(path.c_str());
    if (!*ext) return false;
    wchar_t clsidText[64] = {};
    DWORD len = 64;
    if (FAILED(AssocQueryStringW(ASSOCF_INIT_DEFAULTTOSTAR, ASSOCSTR_SHELLEXTENSION, ext,
                                 L"{8895b1c6-b41f-4c1c-a562-0d564250836f}", clsidText, &len)))
        return false;
    CLSID clsid;
    if (FAILED(CLSIDFromString(clsidText, &clsid))) return false;

    ComPtr<IPreviewHandler> handler;
    if (FAILED(CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&handler))) &&
        FAILED(CoCreateInstance(clsid, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&handler))))
        return false;

    HRESULT hr = E_NOINTERFACE;
    ComPtr<IInitializeWithFile> withFile;
    ComPtr<IInitializeWithStream> withStream;
    ComPtr<IInitializeWithItem> withItem;
    if (SUCCEEDED(handler.As(&withFile))) {
        hr = withFile->Initialize(path.c_str(), STGM_READ);
    } else if (SUCCEEDED(handler.As(&withStream))) {
        ComPtr<IStream> stream;
        hr = SHCreateStreamOnFileEx(path.c_str(), STGM_READ | STGM_SHARE_DENY_NONE, 0, FALSE,
                                    nullptr, &stream);
        if (SUCCEEDED(hr)) hr = withStream->Initialize(stream.Get(), STGM_READ);
    } else if (SUCCEEDED(handler.As(&withItem))) {
        ComPtr<IShellItem> item;
        hr = SHCreateItemFromParsingName(path.c_str(), nullptr, IID_PPV_ARGS(&item));
        if (SUCCEEDED(hr)) hr = withItem->Initialize(item.Get(), STGM_READ);
    }
    if (FAILED(hr)) return false;

    ComPtr<IPreviewHandlerVisuals> visuals;
    if (SUCCEEDED(handler.As(&visuals))) {
        visuals->SetBackgroundColor(g_set.bg);
        visuals->SetTextColor(g_set.fg);
    }
    RECT rc = ContentRect();
    ShowWindow(g.host, SW_SHOW);
    MoveWindow(g.host, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
    RECT hostRc{0, 0, rc.right - rc.left, rc.bottom - rc.top};
    if (FAILED(handler->SetWindow(g.host, &hostRc)) || FAILED(handler->DoPreview())) {
        handler->Unload();
        ShowWindow(g.host, SW_HIDE);
        return false;
    }
    g.handler = handler;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Videos and music. Windows 11 dropped the old media preview handler, so the
// preview plays them itself with Media Foundation (MFPlay).

constexpr UINT WM_APP_MEDIA_FAILED = WM_APP + 4;
const GUID kPos100ns = {};  // MFP_POSITIONTYPE_100NS is the all-zero GUID

void LayoutChildren();

float Scale() {
    return GetDpiForWindow(g.wnd) / 96.0f;
}

int BarHeight() {
    return (int)(56 * Scale());
}

RECT MediaArea() {
    RECT rc = ContentRect();
    rc.bottom = std::max(rc.top, rc.bottom - BarHeight());
    return rc;
}

struct BarRects {
    RECT bar, button, current, track, total, volume;
};

BarRects BarLayout() {
    float s = Scale();
    RECT rc = ContentRect();
    BarRects b;
    b.bar = {rc.left, rc.bottom - BarHeight(), rc.right, rc.bottom};
    int cy = (b.bar.top + b.bar.bottom) / 2, r = (int)(18 * s);
    int x = rc.left + (int)(14 * s);
    b.button = {x, cy - r, x + 2 * r, cy + r};
    int timeW = (int)(60 * s), gap = (int)(10 * s);
    b.volume = {rc.right - (int)(84 * s), b.bar.top, rc.right - (int)(8 * s), b.bar.bottom};
    b.current = {b.button.right + gap, b.bar.top, b.button.right + gap + timeW, b.bar.bottom};
    b.total = {b.volume.left - gap - timeW, b.bar.top, b.volume.left - gap, b.bar.bottom};
    b.track = {b.current.right + gap, b.bar.top, std::max(b.current.right + gap, b.total.left - gap),
               b.bar.bottom};
    return b;
}

LONGLONG MediaPosition() {
    if (g.dragging) return g.dragPos;
    if (!g.player || !g.mediaReady) return 0;
    if (g.mediaEnded) return g.duration;
    PROPVARIANT pv;
    PropVariantInit(&pv);
    LONGLONG t = 0;
    if (SUCCEEDED(g.player->GetPosition(kPos100ns, &pv))) {
        if (pv.vt == VT_I8) t = pv.hVal.QuadPart;
        else if (pv.vt == VT_UI8) t = (LONGLONG)pv.uhVal.QuadPart;
    }
    PropVariantClear(&pv);
    return std::clamp<LONGLONG>(t, 0, std::max<LONGLONG>(g.duration, 0));
}

void ApplyVolume() {
    if (!g.player) return;
    g.player->SetVolume(g.volume);
    g.player->SetMute(g.muted);
}

void SeekTo(LONGLONG t) {
    if (!g.player || !g.mediaReady || g.duration <= 0) return;
    t = std::clamp<LONGLONG>(t, 0, g.duration);
    PROPVARIANT pv;
    PropVariantInit(&pv);
    pv.vt = VT_I8;
    pv.hVal.QuadPart = t;
    if (SUCCEEDED(g.player->SetPosition(kPos100ns, &pv)) && t < g.duration) g.mediaEnded = false;
    InvalidateRect(g.wnd, nullptr, FALSE);
}

void TogglePlay() {
    if (!g.player || !g.mediaReady) return;
    if (g.playerState == MFP_MEDIAPLAYER_STATE_PLAYING) {
        g.player->Pause();
        return;
    }
    if (g.mediaEnded) SeekTo(0);  // from the end, start over
    g.player->Play();
}

void ChangeVolume(float delta) {
    g.volume = std::clamp(g.volume + delta, 0.0f, 1.0f);
    g.muted = false;
    ApplyVolume();
    InvalidateRect(g.wnd, nullptr, FALSE);
}

void StopMedia() {
    g_mediaKeys = false;
    if (g.wnd) {
        KillTimer(g.wnd, kMediaTimer);
        KillTimer(g.wnd, kArtTimer);
    }
    if (g.player) {
        g.player->Shutdown();
        g.player.Reset();
    }
    if (g.video) ShowWindow(g.video, SW_HIDE);
    if (g.dragging && GetCapture() == g.wnd) ReleaseCapture();
    g.mediaReady = g.mediaHasVideo = g.mediaEnded = g.dragging = false;
    g.duration = 0;
    g.playerState = MFP_MEDIAPLAYER_STATE_EMPTY;
}

void OnPlayerEvent(MFP_EVENT_HEADER* e) {
    if (!g.player || e->pMediaPlayer != g.player.Get()) return;  // an old file's player
    g.playerState = e->eState;
    // Shutting the player down from inside its own callback isn't allowed, so
    // failures are handled from the window's message queue.
    if (FAILED(e->hrEvent) && (!g.mediaReady || e->eEventType == MFP_EVENT_TYPE_ERROR)) {
        PostMessageW(g.wnd, WM_APP_MEDIA_FAILED, (WPARAM)e->hrEvent, 0);
        return;
    }
    switch (e->eEventType) {
        case MFP_EVENT_TYPE_MEDIAITEM_CREATED:
            if (auto* c = MFP_GET_MEDIAITEM_CREATED_EVENT(e); c && c->pMediaItem)
                g.player->SetMediaItem(c->pMediaItem);
            break;
        case MFP_EVENT_TYPE_MEDIAITEM_SET: {
            BOOL hasVideo = FALSE, selected = FALSE;
            if (auto* set = MFP_GET_MEDIAITEM_SET_EVENT(e); set && set->pMediaItem)
                set->pMediaItem->HasVideo(&hasVideo, &selected);
            g.mediaHasVideo = hasVideo && selected;
            PROPVARIANT pv;
            PropVariantInit(&pv);
            if (SUCCEEDED(g.player->GetDuration(kPos100ns, &pv))) {
                if (pv.vt == VT_UI8) g.duration = (LONGLONG)pv.uhVal.QuadPart;
                else if (pv.vt == VT_I8) g.duration = pv.hVal.QuadPart;
            }
            PropVariantClear(&pv);
            g.mediaReady = true;
            ApplyVolume();
            if (g.mediaHasVideo) {
                g.player->SetBorderColor(g_set.bg);
                LayoutChildren();
                ShowWindow(g.video, SW_SHOW);
            }
            if (g_set.autoPlay) g.player->Play();
            break;
        }
        case MFP_EVENT_TYPE_PLAY:
            g.mediaEnded = false;
            break;
        case MFP_EVENT_TYPE_PLAYBACK_ENDED:
            g.mediaEnded = true;
            break;
        default:
            break;
    }
    InvalidateRect(g.wnd, nullptr, FALSE);
}

struct PlayerCallback : IMFPMediaPlayerCallback {
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) override {
        if (riid == __uuidof(IUnknown) || riid == __uuidof(IMFPMediaPlayerCallback)) {
            *ppv = static_cast<IMFPMediaPlayerCallback*>(this);
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    // Static object: lives as long as the mod.
    ULONG STDMETHODCALLTYPE AddRef() override { return 2; }
    ULONG STDMETHODCALLTYPE Release() override { return 1; }
    void STDMETHODCALLTYPE OnMediaPlayerEvent(MFP_EVENT_HEADER* e) override { OnPlayerEvent(e); }
} g_playerCallback;

bool IsMediaFile(const std::wstring& path) {
    PCWSTR ext = PathFindExtensionW(path.c_str());
    PERCEIVED type = PERCEIVED_TYPE_UNSPECIFIED;
    PERCEIVEDFLAG flags = 0;
    if (!*ext || FAILED(AssocGetPerceivedType(ext, &type, &flags, nullptr))) return false;
    return type == PERCEIVED_TYPE_AUDIO || type == PERCEIVED_TYPE_VIDEO;
}

// The file opens in the background (MEDIAITEM_CREATED, then SET), and cover
// art loads on a timer after the first paint. Both can take a few hundred
// milliseconds, and the window should appear at once.
bool LoadMedia(const std::wstring& path) {
    g.infoLines = {g.name};
    SHFILEINFOW sfi{};
    if (SHGetFileInfoW(path.c_str(), 0, &sfi, sizeof(sfi), SHGFI_TYPENAME))
        g.infoLines.push_back(sfi.szTypeName);

    RECT m = MediaArea();
    MoveWindow(g.video, m.left, m.top, m.right - m.left, m.bottom - m.top, FALSE);
    if (FAILED(MFPCreateMediaPlayer(nullptr, FALSE, 0, &g_playerCallback, g.video, &g.player)) ||
        FAILED(g.player->CreateMediaItemFromURL(path.c_str(), FALSE, 0, nullptr))) {
        if (g.player) g.player->Shutdown();
        g.player.Reset();
        g.infoLines.clear();
        return false;
    }
    g_mediaKeys = true;
    SetTimer(g.wnd, kMediaTimer, 250, nullptr);
    SetTimer(g.wnd, kArtTimer, 1, nullptr);
    return true;
}

void OnMediaFailed(HRESULT hr) {
    if (g.mode != Mode::Media) return;
    StopMedia();
    g.mode = Mode::Info;
    wchar_t line[96];
    swprintf(line, 96, L"Windows can't play this file (0x%08X)", (unsigned)hr);
    g.infoLines.push_back(line);
    Wh_Log(L"Media failed: 0x%08X", (unsigned)hr);
    InvalidateRect(g.wnd, nullptr, FALSE);
}

LRESULT CALLBACK VideoWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC dc = BeginPaint(hwnd, &ps);
            if (g.player && g.mediaHasVideo) g.player->UpdateVideo();
            else FillRect(dc, &ps.rcPaint, g.bgBrush);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_SIZE:
            if (g.player && g.mediaHasVideo) g.player->UpdateVideo();
            return 0;
        case WM_LBUTTONDOWN:
            TogglePlay();
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

////////////////////////////////////////////////////////////////////////////////
// Window icon: the Peek eye on a mauve tile, drawn at the exact size Windows
// asks for, so it stays sharp at every scale.

HICON MakeIcon(int size) {
    BITMAPINFO bi{};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), size, -size, 1, 32, BI_RGB};
    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    HDC mem = CreateCompatibleDC(screen);
    ReleaseDC(nullptr, screen);
    if (!color || !mem) {
        if (color) DeleteObject(color);
        if (mem) DeleteDC(mem);
        return nullptr;
    }
    HGDIOBJ old = SelectObject(mem, color);

    auto props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
    ComPtr<ID2D1DCRenderTarget> rt;
    ComPtr<ID2D1PathGeometry> eye;
    ComPtr<ID2D1GeometrySink> sink;
    ComPtr<ID2D1StrokeStyle> round;
    ComPtr<ID2D1SolidColorBrush> mauve, dark;
    RECT rc{0, 0, size, size};
    float s = (float)size;
    bool ok = SUCCEEDED(g.d2d->CreateDCRenderTarget(&props, &rt)) && SUCCEEDED(rt->BindDC(mem, &rc)) &&
              SUCCEEDED(g.d2d->CreatePathGeometry(&eye)) && SUCCEEDED(eye->Open(&sink)) &&
              SUCCEEDED(g.d2d->CreateStrokeStyle(
                  D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND,
                                              D2D1_CAP_STYLE_ROUND, D2D1_LINE_JOIN_ROUND),
                  nullptr, 0, &round)) &&
              SUCCEEDED(rt->CreateSolidColorBrush(D2D1::ColorF(0xCBA6F7), &mauve)) &&
              SUCCEEDED(rt->CreateSolidColorBrush(D2D1::ColorF(0x1E1E2E), &dark));
    if (ok) {
        sink->BeginFigure(D2D1::Point2F(0.16f * s, 0.5f * s), D2D1_FIGURE_BEGIN_HOLLOW);
        sink->AddBezier(D2D1::BezierSegment(D2D1::Point2F(0.33f * s, 0.2f * s),
                                            D2D1::Point2F(0.67f * s, 0.2f * s),
                                            D2D1::Point2F(0.84f * s, 0.5f * s)));
        sink->AddBezier(D2D1::BezierSegment(D2D1::Point2F(0.67f * s, 0.8f * s),
                                            D2D1::Point2F(0.33f * s, 0.8f * s),
                                            D2D1::Point2F(0.16f * s, 0.5f * s)));
        sink->EndFigure(D2D1_FIGURE_END_CLOSED);
        ok = SUCCEEDED(sink->Close());
    }
    if (ok) {
        rt->BeginDraw();
        rt->Clear(D2D1::ColorF(0, 0.0f));
        float r = 0.24f * s;
        rt->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(0, 0, s, s), r, r), mauve.Get());
        rt->DrawGeometry(eye.Get(), dark.Get(), std::max(1.0f, 0.085f * s), round.Get());
        rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(0.5f * s, 0.5f * s), 0.125f * s, 0.125f * s),
                        dark.Get());
        ok = SUCCEEDED(rt->EndDraw());
    }
    SelectObject(mem, old);
    DeleteDC(mem);

    HICON icon = nullptr;
    if (ok) {
        // Icons take straight alpha; Direct2D drew premultiplied.
        auto* px = (BYTE*)bits;
        for (int i = 0; i < size * size; i++, px += 4) {
            BYTE a = px[3];
            if (a && a < 255)
                for (int c = 0; c < 3; c++) px[c] = (BYTE)std::min(255, px[c] * 255 / a);
        }
        std::vector<BYTE> zeros((size_t)((size + 15) / 16) * 2 * size);
        HBITMAP mask = CreateBitmap(size, size, 1, 1, zeros.data());
        ICONINFO ii{TRUE, 0, 0, mask, color};
        icon = CreateIconIndirect(&ii);
        DeleteObject(mask);
    }
    DeleteObject(color);
    return icon;
}

void UpdateIcons(HWND hwnd) {
    static UINT iconDpi = 0;
    UINT dpi = GetDpiForWindow(hwnd);
    HICON oldSmall = nullptr, oldBig = nullptr;
    if (dpi != iconDpi || !g.iconSmall || !g.iconBig) {
        HICON small = MakeIcon(GetSystemMetricsForDpi(SM_CXSMICON, dpi));
        HICON big = MakeIcon(GetSystemMetricsForDpi(SM_CXICON, dpi));
        if (!small || !big) {
            if (small) DestroyIcon(small);
            if (big) DestroyIcon(big);
            Wh_Log(L"Icon failed");
            return;
        }
        oldSmall = g.iconSmall;
        oldBig = g.iconBig;
        g.iconSmall = small;
        g.iconBig = big;
        iconDpi = dpi;
    }
    SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)g.iconSmall);
    SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)g.iconBig);
    if (oldSmall) DestroyIcon(oldSmall);
    if (oldBig) DestroyIcon(oldBig);
}

////////////////////////////////////////////////////////////////////////////////
// Window

void ApplyTitle() {
    std::wstring title = g.name;
    if (g.items.size() > 1) {
        wchar_t n[48];
        swprintf(n, 48, L"   (%zu of %zu)", g.index + 1, g.items.size());
        title += n;
    }
    SetWindowTextW(g.wnd, (title + L" - Peek").c_str());
}

void ShowItem() {
    StopMedia();
    UnloadHandler();
    ShowWindow(g.host, SW_HIDE);
    ShowWindow(g.edit, SW_HIDE);
    SetWindowTextW(g.edit, L"");
    g.image.Reset();
    g.bitmap.Reset();
    g.infoLines.clear();
    g.mode = Mode::None;

    ComPtr<IShellItem> item;
    if (g.index >= g.items.size() ||
        FAILED(SHCreateItemFromIDList(g.items[g.index].get(), IID_PPV_ARGS(&item))))
        return;
    PWSTR s = nullptr;
    g.path.clear();
    if (SUCCEEDED(item->GetDisplayName(SIGDN_FILESYSPATH, &s))) {
        g.path = s;
        CoTaskMemFree(s);
    }
    g.name.clear();
    if (SUCCEEDED(item->GetDisplayName(SIGDN_NORMALDISPLAY, &s))) {
        g.name = s;
        CoTaskMemFree(s);
    }
    ApplyTitle();

    SFGAOF attrs = 0;
    item->GetAttributes(SFGAO_FOLDER | SFGAO_STREAM, &attrs);
    bool isFile = !g.path.empty() && !((attrs & SFGAO_FOLDER) && !(attrs & SFGAO_STREAM));

    std::wstring text;
    bool media = isFile && g_set.playMedia && IsMediaFile(g.path);
    if (media && LoadMedia(g.path)) {
        g.mode = Mode::Media;
    } else if (isFile && !media && (g.image = LoadImage(g.path))) {
        g.mode = Mode::Image;
    } else if (isFile && HasTextExtension(g.path) && LoadText(g.path, false, &text)) {
        g.mode = Mode::Text;
    } else if (isFile && g_set.usePreviewHandlers && LoadHandler(g.path)) {
        g.mode = Mode::Handler;
    } else if (isFile && LoadText(g.path, true, &text)) {
        g.mode = Mode::Text;
    } else {
        g.mode = Mode::Info;
        g.image = LoadThumbnail(item.Get(), 256);
        BuildInfo(item.Get());
    }

    if (g.mode == Mode::Text) {
        RECT rc = ContentRect();
        SetWindowTextW(g.edit, text.c_str());
        MoveWindow(g.edit, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
        ShowWindow(g.edit, SW_SHOW);
        SetFocus(g.edit);
    } else {
        SetFocus(g.wnd);
    }
    InvalidateRect(g.wnd, nullptr, TRUE);
}

void ApplyDarkMode(HWND hwnd) {
    BOOL dark = g_set.darkMode;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    COLORREF caption = g_set.bg;
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
}

void CreateTextResources(HWND hwnd) {
    if (g.textFont) DeleteObject(g.textFont);
    if (g.bgBrush) DeleteObject(g.bgBrush);
    int height = -MulDiv(g_set.textSize, GetDpiForWindow(hwnd), 72);
    g.textFont = CreateFontW(height, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                             OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                             FIXED_PITCH | FF_MODERN, g_set.textFont.c_str());
    g.bgBrush = CreateSolidBrush(g_set.bg);
}

D2D1_COLOR_F ToD2D(COLORREF c) {
    return D2D1::ColorF(GetRValue(c) / 255.0f, GetGValue(c) / 255.0f, GetBValue(c) / 255.0f);
}

void DrawBar();
void DrawInfo(float w, float h, float maxIcon, float iconShare, float topShare);

void Paint() {
    PAINTSTRUCT ps;
    BeginPaint(g.wnd, &ps);
    EndPaint(g.wnd, &ps);
    if (g.mode == Mode::Text || g.mode == Mode::Handler) return;

    RECT rc;
    GetClientRect(g.wnd, &rc);
    D2D1_SIZE_U px = D2D1::SizeU(rc.right, rc.bottom);
    if (!g.rt) {
        auto props = D2D1::RenderTargetProperties();
        props.dpiX = props.dpiY = 96.0f;  // draw in pixels
        if (FAILED(g.d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(g.wnd, px),
                                                 &g.rt)))
            return;
    } else {
        g.rt->Resize(px);
    }
    if (g.image && !g.bitmap) g.rt->CreateBitmapFromWicBitmap(g.image.Get(), &g.bitmap);

    float w = (float)rc.right, h = (float)rc.bottom;
    float scale = GetDpiForWindow(g.wnd) / 96.0f;
    g.rt->BeginDraw();
    g.rt->Clear(ToD2D(g_set.bg));

    if (g.mode == Mode::Image && g.bitmap) {
        D2D1_SIZE_F bs = g.bitmap->GetSize();
        float fit = std::min(w / bs.width, h / bs.height);
        if (!g_set.upscaleImages) fit = std::min(fit, 1.0f);
        float dw = bs.width * fit, dh = bs.height * fit;
        D2D1_RECT_F dst = D2D1::RectF((w - dw) / 2, (h - dh) / 2, (w + dw) / 2, (h + dh) / 2);
        g.rt->DrawBitmap(g.bitmap.Get(), dst, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    } else if (g.mode == Mode::Info) {
        DrawInfo(w, h, 256.0f * scale, 0.45f, 0.18f);
    } else if (g.mode == Mode::Media) {
        if (!g.mediaHasVideo) DrawInfo(w, h - BarHeight(), 360.0f * scale, 0.6f, 0.1f);
        DrawBar();
    }
    if (g.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
        g.bitmap.Reset();
        g.rt.Reset();
    }
}

D2D1_COLOR_F Mix(COLORREF a, COLORREF b, float t) {
    D2D1_COLOR_F x = ToD2D(a), y = ToD2D(b);
    return D2D1::ColorF(x.r + (y.r - x.r) * t, x.g + (y.g - x.g) * t, x.b + (y.b - x.b) * t);
}

D2D1_RECT_F ToRectF(const RECT& r) {
    return D2D1::RectF((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
}

void DrawLabel(const std::wstring& text, const D2D1_RECT_F& r, PCWSTR font, float size,
               DWRITE_TEXT_ALIGNMENT align, ID2D1Brush* brush) {
    ComPtr<IDWriteTextFormat> fmt;
    if (FAILED(g.dwrite->CreateTextFormat(font, nullptr, DWRITE_FONT_WEIGHT_NORMAL,
                                          DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size,
                                          L"", &fmt)))
        return;
    fmt->SetTextAlignment(align);
    fmt->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    fmt->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    g.rt->DrawText(text.c_str(), (UINT32)text.size(), fmt.Get(), r, brush);
}

std::wstring FormatDuration(LONGLONG t) {
    LONGLONG secs = std::max<LONGLONG>(t, 0) / 10000000;
    wchar_t buf[32];
    if (secs >= 3600)
        swprintf(buf, 32, L"%lld:%02lld:%02lld", secs / 3600, secs / 60 % 60, secs % 60);
    else
        swprintf(buf, 32, L"%lld:%02lld", secs / 60, secs % 60);
    return buf;
}

void DrawBar() {
    float s = Scale();
    BarRects b = BarLayout();
    ComPtr<ID2D1SolidColorBrush> brush;
    if (FAILED(g.rt->CreateSolidColorBrush(ToD2D(g_set.fg), &brush))) return;
    PCWSTR icons = L"Segoe Fluent Icons";

    brush->SetColor(Mix(g_set.bg, g_set.fg, 0.06f));
    g.rt->FillRectangle(ToRectF(b.bar), brush.Get());

    D2D1_RECT_F btn = ToRectF(b.button);
    float r = (btn.right - btn.left) / 2;
    brush->SetColor(ToD2D(g_set.accent));
    g.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(btn.left + r, btn.top + r), r, r), brush.Get());
    bool playing = g.playerState == MFP_MEDIAPLAYER_STATE_PLAYING;
    brush->SetColor(ToD2D(g_set.bg));
    DrawLabel(playing ? L"\xE769" : L"\xE768", btn, icons, 15 * s, DWRITE_TEXT_ALIGNMENT_CENTER,
              brush.Get());

    LONGLONG pos = MediaPosition();
    brush->SetColor(ToD2D(g_set.dim));
    float textSize = 13 * s;
    DrawLabel(FormatDuration(pos), ToRectF(b.current), L"Segoe UI", textSize,
              DWRITE_TEXT_ALIGNMENT_TRAILING, brush.Get());
    DrawLabel(g.mediaReady ? FormatDuration(g.duration) : L"-:--", ToRectF(b.total), L"Segoe UI",
              textSize, DWRITE_TEXT_ALIGNMENT_LEADING, brush.Get());

    D2D1_RECT_F tr = ToRectF(b.track);
    float cy = (tr.top + tr.bottom) / 2, th = 4 * s;
    if (tr.right > tr.left) {
        brush->SetColor(Mix(g_set.bg, g_set.dim, 0.3f));
        g.rt->FillRoundedRectangle(
            D2D1::RoundedRect(D2D1::RectF(tr.left, cy - th / 2, tr.right, cy + th / 2), th / 2, th / 2),
            brush.Get());
        float frac = g.duration > 0 ? (float)std::clamp((double)pos / g.duration, 0.0, 1.0) : 0.0f;
        float x = tr.left + frac * (tr.right - tr.left);
        brush->SetColor(ToD2D(g_set.accent));
        g.rt->FillRoundedRectangle(
            D2D1::RoundedRect(D2D1::RectF(tr.left, cy - th / 2, x, cy + th / 2), th / 2, th / 2),
            brush.Get());
        g.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, cy), 6 * s, 6 * s), brush.Get());
    }

    D2D1_RECT_F vol = ToRectF(b.volume);
    bool silent = g.muted || g.volume <= 0.0f;
    brush->SetColor(ToD2D(g_set.fg));
    DrawLabel(silent ? L"\xE74F" : L"\xE767", D2D1::RectF(vol.left, vol.top, vol.left + 24 * s, vol.bottom),
              icons, 15 * s, DWRITE_TEXT_ALIGNMENT_CENTER, brush.Get());
    wchar_t pct[16];
    swprintf(pct, 16, L"%d%%", silent ? 0 : (int)(g.volume * 100 + 0.5f));
    brush->SetColor(ToD2D(g_set.dim));
    DrawLabel(pct, D2D1::RectF(vol.left + 28 * s, vol.top, vol.right, vol.bottom), L"Segoe UI",
              textSize, DWRITE_TEXT_ALIGNMENT_LEADING, brush.Get());
}

// The big icon or cover with the name and details under it, in the top
// `h` pixels of the window.
void DrawInfo(float w, float h, float maxIcon, float iconShare, float topShare) {
    float scale = Scale();
    {
        float icon = 0;
        float top = h * topShare;
        if (g.bitmap) {
            D2D1_SIZE_F bs = g.bitmap->GetSize();
            icon = std::min(maxIcon, std::min(w, h) * iconShare);
            float fit = std::min(icon / bs.width, icon / bs.height);
            float dw = bs.width * fit, dh = bs.height * fit;
            g.rt->DrawBitmap(g.bitmap.Get(),
                             D2D1::RectF((w - dw) / 2, top + (icon - dh) / 2, (w + dw) / 2,
                                         top + (icon + dh) / 2),
                             1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
        }
        ComPtr<ID2D1SolidColorBrush> main, dim;
        g.rt->CreateSolidColorBrush(ToD2D(g_set.fg), &main);
        g.rt->CreateSolidColorBrush(ToD2D(g_set.dim), &dim);
        float y = top + icon + 24 * scale;
        for (size_t i = 0; i < g.infoLines.size() && main && dim; i++) {
            ComPtr<IDWriteTextFormat> fmt;
            float size = (i == 0 ? 22.0f : 14.0f) * scale;
            g.dwrite->CreateTextFormat(L"Segoe UI", nullptr,
                                       i == 0 ? DWRITE_FONT_WEIGHT_SEMI_BOLD : DWRITE_FONT_WEIGHT_NORMAL,
                                       DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size,
                                       L"", &fmt);
            if (!fmt) continue;
            fmt->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
            fmt->SetWordWrapping(DWRITE_WORD_WRAPPING_EMERGENCY_BREAK);
            const std::wstring& line = g.infoLines[i];
            ComPtr<IDWriteTextLayout> layout;
            g.dwrite->CreateTextLayout(line.c_str(), (UINT32)line.size(), fmt.Get(),
                                       w - 48 * scale, h, &layout);
            if (!layout) continue;
            DWRITE_TEXT_METRICS m{};
            layout->GetMetrics(&m);
            g.rt->DrawTextLayout(D2D1::Point2F(24 * scale, y), layout.Get(),
                                 i == 0 ? main.Get() : dim.Get());
            y += m.height + (i == 0 ? 12 : 6) * scale;
        }
    }
}

void LayoutChildren() {
    RECT rc = ContentRect();
    int w = rc.right - rc.left, h = rc.bottom - rc.top;
    if (g.mode == Mode::Text) MoveWindow(g.edit, rc.left, rc.top, w, h, TRUE);
    if (g.mode == Mode::Media) {
        RECT m = MediaArea();
        MoveWindow(g.video, m.left, m.top, m.right - m.left, m.bottom - m.top, TRUE);
    }
    if (g.mode == Mode::Handler && g.handler) {
        MoveWindow(g.host, rc.left, rc.top, w, h, TRUE);
        RECT hostRc{0, 0, w, h};
        g.handler->SetRect(&hostRc);
    }
    InvalidateRect(g.wnd, nullptr, FALSE);
}

void ClosePreview() {
    if (!g.wnd) return;
    if (g_set.rememberSize) {
        WINDOWPLACEMENT wp{sizeof(wp)};
        GetWindowPlacement(g.wnd, &wp);
        g.lastRect = wp.rcNormalPosition;
        g.haveLastRect = true;
    }
    StopMedia();
    UnloadHandler();
    HWND back = g.source;
    DestroyWindow(g.wnd);
    if (back && IsWindow(back)) SetForegroundWindow(back);
}

LRESULT CALLBACK PreviewWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            g.wnd = hwnd;
            ApplyDarkMode(hwnd);
            CreateTextResources(hwnd);
            DWORD style = WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_NOHIDESEL;
            if (!g_set.wordWrap) style |= WS_HSCROLL | ES_AUTOHSCROLL;
            g.edit = CreateWindowExW(0, L"EDIT", L"", style, 0, 0, 0, 0, hwnd, nullptr,
                                     GetModuleHandleW(nullptr), nullptr);
            SendMessageW(g.edit, WM_SETFONT, (WPARAM)g.textFont, FALSE);
            SendMessageW(g.edit, EM_SETLIMITTEXT, 0x7FFFFFFE, 0);
            SendMessageW(g.edit, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN,
                         MAKELPARAM(12, 12));
            if (g_set.darkMode) SetWindowTheme(g.edit, L"DarkMode_Explorer", nullptr);
            g.host = CreateWindowExW(0, L"Static", L"", WS_CHILD | WS_CLIPCHILDREN, 0, 0, 0, 0,
                                     hwnd, nullptr, GetModuleHandleW(nullptr), nullptr);
            g.video = CreateWindowExW(0, L"WindhawkPeekVideo", L"", WS_CHILD | WS_CLIPSIBLINGS, 0, 0,
                                      0, 0, hwnd, nullptr, GetModuleHandleW(nullptr), nullptr);
            UpdateIcons(hwnd);
            return 0;
        }
        case WM_TIMER:
            if (wp == kMediaTimer) {
                // A Play() issued from inside the item-set callback is
                // occasionally ignored by the session (state stays stopped).
                // Retry from the message loop, the normal calling context.
                if (g.mode == Mode::Media && g.mediaReady && g_set.autoPlay && !g.mediaEnded &&
                    g.playerState == MFP_MEDIAPLAYER_STATE_STOPPED)
                    g.player->Play();
                RECT bar = BarLayout().bar;
                InvalidateRect(hwnd, &bar, FALSE);
            } else if (wp == kArtTimer) {
                KillTimer(hwnd, kArtTimer);
                // Cover art for music, or a frame until the video starts.
                ComPtr<IShellItem> item;
                if (g.mode == Mode::Media && !g.image && !g.mediaHasVideo && g.index < g.items.size() &&
                    SUCCEEDED(SHCreateItemFromIDList(g.items[g.index].get(), IID_PPV_ARGS(&item)))) {
                    g.image = LoadThumbnail(item.Get(), 512);
                    g.bitmap.Reset();
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
            }
            return 0;
        case WM_APP_MEDIA_FAILED:
            OnMediaFailed((HRESULT)wp);
            return 0;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK: {
            if (g.mode != Mode::Media) break;
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            BarRects b = BarLayout();
            if (PtInRect(&b.button, pt)) {
                TogglePlay();
            } else if (PtInRect(&b.track, pt) && g.mediaReady && g.duration > 0) {
                g.dragging = true;
                SetCapture(hwnd);
                SendMessageW(hwnd, WM_MOUSEMOVE, wp, lp);
            } else if (PtInRect(&b.volume, pt)) {
                g.muted = !g.muted;
                ApplyVolume();
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }
        case WM_MOUSEMOVE:
            if (g.dragging) {
                RECT t = BarLayout().track;
                double frac = t.right > t.left ? (double)(GET_X_LPARAM(lp) - t.left) / (t.right - t.left) : 0;
                g.dragPos = (LONGLONG)(std::clamp(frac, 0.0, 1.0) * g.duration);
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_LBUTTONUP:
            if (g.dragging) {
                g.dragging = false;
                ReleaseCapture();
                SeekTo(g.dragPos);
            }
            return 0;
        case WM_CAPTURECHANGED:
            g.dragging = false;
            return 0;
        case WM_MOUSEWHEEL:
            if (g.mode == Mode::Media) {
                ChangeVolume(GET_WHEEL_DELTA_WPARAM(wp) / (float)WHEEL_DELTA * 0.05f);
                return 0;
            }
            break;
        case WM_ERASEBKGND: {
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect((HDC)wp, &rc, g.bgBrush);
            return 1;
        }
        case WM_PAINT:
            Paint();
            return 0;
        case WM_SIZE:
            LayoutChildren();
            return 0;
        case WM_DPICHANGED: {
            auto* r = (RECT*)lp;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            CreateTextResources(hwnd);
            SendMessageW(g.edit, WM_SETFONT, (WPARAM)g.textFont, TRUE);
            UpdateIcons(hwnd);
            return 0;
        }
        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLOREDIT:
            SetTextColor((HDC)wp, g_set.fg);
            SetBkColor((HDC)wp, g_set.bg);
            return (LRESULT)g.bgBrush;
        case WM_ACTIVATE:
            if (LOWORD(wp) == WA_INACTIVE && g_set.closeOnFocusLoss && !lp)
                PostMessageW(g.msgWnd, WM_APP_KEY, (WPARAM)Key::Close, 0);
            else if (LOWORD(wp) != WA_INACTIVE && g.mode == Mode::Text)
                SetFocus(g.edit);
            return 0;
        case WM_DESTROY:
            StopMedia();
            UnloadHandler();
            g.rt.Reset();
            g.bitmap.Reset();
            g.image.Reset();
            g.items.clear();
            g.wnd = g.edit = g.host = g.video = nullptr;
            g.mode = Mode::None;
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// A hook-only process doesn't own the last input, so Windows would just flash
// the taskbar button. Sharing input state with the window in front lets us take focus.
void TakeForeground(HWND hwnd) {
    HWND front = GetForegroundWindow();
    DWORD frontThread = front ? GetWindowThreadProcessId(front, nullptr) : 0;
    DWORD self = GetCurrentThreadId();
    bool attached = frontThread && frontThread != self && AttachThreadInput(self, frontThread, TRUE);
    SetForegroundWindow(hwnd);
    BringWindowToTop(hwnd);
    if (attached) AttachThreadInput(self, frontThread, FALSE);
}

void OpenPreview(HWND source) {
    g.source = source;
    if (!g.wnd) {
        RECT r;
        if (g_set.rememberSize && g.haveLastRect) {
            r = g.lastRect;
        } else {
            HMONITOR mon = MonitorFromWindow(source, MONITOR_DEFAULTTONEAREST);
            MONITORINFO mi{sizeof(mi)};
            GetMonitorInfoW(mon, &mi);
            RECT wa = mi.rcWork;
            int w = (wa.right - wa.left) * g_set.widthPercent / 100;
            int h = (wa.bottom - wa.top) * g_set.heightPercent / 100;
            r.left = wa.left + (wa.right - wa.left - w) / 2;
            r.top = wa.top + (wa.bottom - wa.top - h) / 2;
            r.right = r.left + w;
            r.bottom = r.top + h;
        }
        DWORD ex = g_set.alwaysOnTop ? WS_EX_TOPMOST : 0;
        CreateWindowExW(ex, L"WindhawkPeek", L"Peek", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                        r.left, r.top, r.right - r.left, r.bottom - r.top, nullptr, nullptr,
                        GetModuleHandleW(nullptr), nullptr);
        if (!g.wnd) return;
        ShowWindow(g.wnd, SW_SHOWNORMAL);
    }
    TakeForeground(g.wnd);
    ShowItem();
}

void OnKey(Key key) {
    if (!g.wnd) return;
    switch (key) {
        case Key::Close:
            ClosePreview();
            break;
        case Key::Prev:
        case Key::Next:
            if (g.items.size() > 1) {
                size_t n = g.items.size();
                g.index = key == Key::Next ? (g.index + 1) % n : (g.index + n - 1) % n;
                ShowItem();
            }
            break;
        case Key::Open:
            if (g.index < g.items.size()) {
                SHELLEXECUTEINFOW sei{sizeof(sei)};
                sei.fMask = SEE_MASK_IDLIST | SEE_MASK_FLAG_NO_UI;
                sei.lpIDList = g.items[g.index].get();
                sei.nShow = SW_SHOWNORMAL;
                HWND back = g.source;
                g.source = nullptr;
                ClosePreview();
                g.source = back;
                ShellExecuteExW(&sei);
            }
            break;
        case Key::PlayPause:
            TogglePlay();
            break;
        case Key::SeekBack:
        case Key::SeekFwd:
            SeekTo(MediaPosition() + (key == Key::SeekFwd ? 1 : -1) * 50000000LL);
            break;
        case Key::VolUp:
        case Key::VolDown:
            ChangeVolume(key == Key::VolUp ? 0.1f : -0.1f);
            break;
        case Key::Mute:
            g.muted = !g.muted;
            ApplyVolume();
            InvalidateRect(g.wnd, nullptr, FALSE);
            break;
    }
}

void OnPeek(HWND top) {
    std::vector<Pidl> old = std::move(g.items);
    size_t oldIndex = g.index;
    if (!ReadSelection(top)) {
        g.items = std::move(old);
        return;
    }
    // Space on the file that is already showing closes it, like Peek.
    if (g.wnd && oldIndex < old.size() && g.index < g.items.size() &&
        ILIsEqual(old[oldIndex].get(), g.items[g.index].get())) {
        ClosePreview();
        return;
    }
    OpenPreview(top);
}

LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_APP_PEEK:
            OnPeek((HWND)wp);
            return 0;
        case WM_APP_KEY:
            OnKey((Key)wp);
            return 0;
        case WM_APP_SETTINGS:
            if (g.wnd) DestroyWindow(g.wnd);
            g.haveLastRect = false;
            LoadSettings();
            return 0;
        case WM_CLOSE:
            if (g.wnd) DestroyWindow(g.wnd);
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

void AllowDarkScrollbars() {
    // uxtheme's unnamed SetPreferredAppMode (ordinal 135): 2 = force dark.
    using SetPreferredAppModeFn = int(WINAPI*)(int);
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    auto fn = ux ? (SetPreferredAppModeFn)GetProcAddress(ux, MAKEINTRESOURCEA(135)) : nullptr;
    if (fn) fn(g_set.darkMode ? 2 : 0);
}

// The keyboard hook gets its own thread. Opening a preview (preview handlers,
// big images) can block the UI thread for seconds, and Windows silently removes
// a low-level hook that misses its timeout, which left Space dead until the
// mod restarted.
DWORD WINAPI HookThreadProc(void*) {
    g.hook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandleW(nullptr), 0);
    if (!g.hook) Wh_Log(L"Keyboard hook failed: %u", GetLastError());
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) DispatchMessageW(&msg);
    if (g.hook) UnhookWindowsHookEx(g.hook);
    g.hook = nullptr;
    return 0;
}

DWORD WINAPI ThreadProc(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    HRESULT mf = MFStartup(MF_VERSION, MFSTARTUP_LITE);
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, g.d2d.GetAddressOf());
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                        (IUnknown**)g.dwrite.GetAddressOf());
    CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g.wic));

    HINSTANCE inst = GetModuleHandleW(nullptr);
    LoadSettings();
    LoadLibraryW(L"uxtheme.dll");
    AllowDarkScrollbars();

    WNDCLASSW mc{};
    mc.lpfnWndProc = MsgWndProc;
    mc.hInstance = inst;
    mc.lpszClassName = L"WindhawkPeekMsg";
    RegisterClassW(&mc);
    WNDCLASSW pc{};
    pc.lpfnWndProc = PreviewWndProc;
    pc.hInstance = inst;
    pc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    pc.lpszClassName = L"WindhawkPeek";
    RegisterClassW(&pc);
    WNDCLASSW vc{};
    vc.lpfnWndProc = VideoWndProc;
    vc.hInstance = inst;
    vc.hCursor = LoadCursor(nullptr, IDC_HAND);
    vc.lpszClassName = L"WindhawkPeekVideo";
    RegisterClassW(&vc);

    g.msgWnd = CreateWindowExW(0, mc.lpszClassName, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr,
                               inst, nullptr);
    g.hookThread = CreateThread(nullptr, 0, HookThreadProc, nullptr, 0, &g.hookThreadId);
    if (!g.hookThread) Wh_Log(L"Hook thread failed: %u", GetLastError());
    SetEvent(g_ready);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (g.hookThread) {
        PostThreadMessageW(g.hookThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g.hookThread, 3000);
        CloseHandle(g.hookThread);
        g.hookThread = nullptr;
    }
    if (g.textFont) DeleteObject(g.textFont);
    if (g.bgBrush) DeleteObject(g.bgBrush);
    g.rt.Reset();
    g.d2d.Reset();
    g.dwrite.Reset();
    g.wic.Reset();
    if (g.iconSmall) DestroyIcon(g.iconSmall);
    if (g.iconBig) DestroyIcon(g.iconBig);
    g.iconSmall = g.iconBig = nullptr;
    UnregisterClassW(vc.lpszClassName, inst);
    UnregisterClassW(pc.lpszClassName, inst);
    UnregisterClassW(mc.lpszClassName, inst);
    if (SUCCEEDED(mf)) MFShutdown();
    CoUninitialize();
    return 0;
}

}  // namespace

BOOL WhTool_ModInit() {
    Wh_Log(L">");
    g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, ThreadProc, nullptr, 0, &g_threadId);
    if (!g_thread) return FALSE;
    WaitForSingleObject(g_ready, 10000);
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    Wh_Log(L">");
    if (g.msgWnd) PostMessageW(g.msgWnd, WM_APP_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    Wh_Log(L">");
    if (g.msgWnd) PostMessageW(g.msgWnd, WM_CLOSE, 0, 0);
    if (g_thread) {
        WaitForSingleObject(g_thread, 5000);
        CloseHandle(g_thread);
    }
}
