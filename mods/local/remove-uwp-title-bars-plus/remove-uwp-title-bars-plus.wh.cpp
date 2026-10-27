// ==WindhawkMod==
// @id              remove-uwp-title-bars-plus
// @name            Remove UWP Title Bars Plus
// @description     Normal Windows title bars, with icon, title and theme buttons, in every UWP app
// @version         2.1.0
// @author          DavidHiFi, Anixx
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         ApplicationFrameHost.exe
// @architecture    x86-64
// @compilerOptions -luser32 -lcomctl32 -ldwmapi -lshell32 -lole32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Remove UWP Title Bars Plus

Gives Store apps (Settings, Calculator, Photos and the rest) the same title bar
desktop apps get. The minimize, maximize and close buttons come from your
Windows theme, including custom themes, and the app's own icon and name sit on
the left.

Windows prepares these app windows before it knows which app will use them, so
the mod waits until the app is known and the window is on screen, then swaps
the title bar. Shell parts that also live in these windows, such as Start and
search, keep their own look.

Applies to app windows opened after you turn the mod on. Turning it off puts
every open window back the way it was.

Based on Remove UWP Title Bars by Anixx.
*/
// ==/WindhawkModReadme==

#include <string>
#include <unordered_map>
#include <vector>

#include <windhawk_utils.h>

#include <dwmapi.h>
#include <propsys.h>
#include <shlobj.h>
#include <windowsx.h>

#ifndef WM_POPUPSYSTEMMENU
#define WM_POPUPSYSTEMMENU 0x0313
#endif

#ifndef WS_EX_NOREDIRECTIONBITMAP
#define WS_EX_NOREDIRECTIONBITMAP 0x00200000L
#endif

namespace frame_host {

constexpr WCHAR kNormalWindowProp[] =
    L"Microsoft.Windows.ShellManagedWindowAsNormalWindow";
constexpr WCHAR kPressedProp[] = L"RemoveUwpTitleBarsPlus_CaptionPressed";
constexpr UINT_PTR kRelayoutTimer = 0x53535031;
constexpr UINT_PTR kResolveTimer = 0x53535032;
constexpr WCHAR kResolveSinceProp[] = L"RemoveUwpTitleBarsPlus_ResolveSince";
// A frame is converted once the shell has shown it. Converting it
// while the shell still holds it cloaked leaves it hidden.
constexpr DWORD kResolveTimeoutMs = 3000;
constexpr UINT kResolveTickMs = 100;

const PROPERTYKEY kAppUserModelId = {
    {0x9F4C2855, 0x9F79, 0x4B39, {0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3}},
    5};

enum class FrameState { Pending, Native, Stock };

struct FrameInfo {
    FrameState state = FrameState::Pending;
    void* titleBar = nullptr;  // CTitleBar whose window creation is held back
    HICON icons[2] = {};       // small, big
    LONG_PTR style = 0, exStyle = 0;  // before MakeFrameNative
    DWORD backdrop = 0;                // DWMWA_SYSTEMBACKDROP_TYPE before it
};

bool g_enabled;
SRWLOCK g_frameLock = SRWLOCK_INIT;
std::unordered_map<HWND, FrameInfo> g_frames;
std::unordered_map<void*, HWND> g_titleBarFrame;
UINT g_frameCheckMsg;
UINT g_frameRestoreMsg;
volatile LONG g_iconJobs;

using CreateTitleBarWindow_t = long(__cdecl*)(void* titleBar);
CreateTitleBarWindow_t CreateTitleBarWindow_Original;
using PaintButton_t =
    long(__cdecl*)(void*, void*, int, int, const RECT*, const RECT*);
PaintButton_t PaintButton_Original;
using DwmSetWindowAttribute_t = HRESULT(WINAPI*)(HWND, DWORD, LPCVOID, DWORD);
DwmSetWindowAttribute_t DwmSetWindowAttribute_Original;

bool IsFrameWindow(HWND hWnd) {
    WCHAR cls[32];
    return GetClassName(hWnd, cls, ARRAYSIZE(cls)) &&
           _wcsicmp(cls, L"ApplicationFrameWindow") == 0;
}

FrameState GetFrameState(HWND hWnd) {
    AcquireSRWLockShared(&g_frameLock);
    auto it = g_frames.find(hWnd);
    FrameState s = it != g_frames.end() ? it->second.state : FrameState::Stock;
    ReleaseSRWLockShared(&g_frameLock);
    return s;
}

// The CTitleBar object keeps its frame's window handle; find it by scanning
// the object for a handle to one of this process's frame windows.
HWND FrameOfTitleBar(void* titleBar) {
    ULONG_PTR buf[0x80] = {};
    SIZE_T got = 0;
    ReadProcessMemory(GetCurrentProcess(), titleBar, buf, sizeof(buf), &got);
    for (size_t i = 0; i < got / sizeof(ULONG_PTR); i++) {
        HWND h = (HWND)buf[i];
        if (!buf[i] || buf[i] > 0xFFFFFFFF || !IsWindow(h)) {
            continue;
        }
        DWORD pid = 0;
        GetWindowThreadProcessId(h, &pid);
        if (pid == GetCurrentProcessId() && IsFrameWindow(h)) {
            return h;
        }
    }
    return nullptr;
}

// Returns true when the frame's app id is known.
bool GetFrameApp(HWND hWnd, std::wstring* aumid) {
    IPropertyStore* store = nullptr;
    if (FAILED(SHGetPropertyStoreForWindow(hWnd, IID_PPV_ARGS(&store)))) {
        return false;
    }
    PROPVARIANT pv;
    PropVariantInit(&pv);
    bool known = false;
    if (SUCCEEDED(store->GetValue(kAppUserModelId, &pv)) &&
        pv.vt == VT_LPWSTR && pv.pwszVal && *pv.pwszVal) {
        known = true;
        *aumid = pv.pwszVal;
    }
    PropVariantClear(&pv);
    store->Release();
    return known;
}

// Gives a native frame the icon the Start menu shows for its app.
DWORD WINAPI IconThread(void* param) {
    auto* job = (std::pair<HWND, std::wstring>*)param;
    HWND hWnd = job->first;
    HICON icons[2] = {};
    HRESULT co = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    PIDLIST_ABSOLUTE pidl = nullptr;
    if (SUCCEEDED(SHParseDisplayName(
            (L"shell:AppsFolder\\" + job->second).c_str(), nullptr, &pidl, 0,
            nullptr))) {
        for (int i = 0; i < 2; i++) {
            SHFILEINFO sfi = {};
            if (SHGetFileInfo((LPCWSTR)pidl, 0, &sfi, sizeof(sfi),
                              SHGFI_PIDL | SHGFI_ICON |
                                  (i ? SHGFI_LARGEICON : SHGFI_SMALLICON))) {
                icons[i] = sfi.hIcon;
            }
        }
        CoTaskMemFree(pidl);
    }
    if (SUCCEEDED(co)) {
        CoUninitialize();
    }
    delete job;

    AcquireSRWLockExclusive(&g_frameLock);
    auto it = g_frames.find(hWnd);
    bool keep = it != g_frames.end() &&
                it->second.state == FrameState::Native &&
                !it->second.icons[0];
    if (keep) {
        it->second.icons[0] = icons[0];
        it->second.icons[1] = icons[1];
    }
    ReleaseSRWLockExclusive(&g_frameLock);
    if (keep) {
        DWORD_PTR r;
        for (int i = 0; i < 2; i++) {
            if (icons[i]) {
                SendMessageTimeout(hWnd, WM_SETICON, i ? ICON_BIG : ICON_SMALL,
                                   (LPARAM)icons[i], SMTO_NORMAL, 2000, &r);
            }
        }
    } else {
        for (HICON i : icons) {
            if (i) {
                DestroyIcon(i);
            }
        }
    }
    InterlockedDecrement(&g_iconJobs);
    return 0;
}

void MakeFrameNative(HWND hWnd, const std::wstring& aumid) {
    // Without this property DWM treats the frame as immersive and hides the
    // minimize and maximize buttons (CTopLevelWindow::GetCurrentStyle).
    SetProp(hWnd, kNormalWindowProp, (HANDLE)1);
    LONG_PTR style = GetWindowLongPtr(hWnd, GWL_STYLE);
    SetWindowLongPtr(hWnd, GWL_STYLE, (style & ~WS_POPUP) | WS_OVERLAPPEDWINDOW);
    LONG_PTR exStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
    SetWindowLongPtr(hWnd, GWL_EXSTYLE, exStyle & ~WS_EX_DLGMODALFRAME);
    DWORD backdrop = 0;
    DwmGetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdrop,
                          sizeof(backdrop));
    AcquireSRWLockExclusive(&g_frameLock);
    g_frames[hWnd].style = style;
    g_frames[hWnd].exStyle = exStyle;
    g_frames[hWnd].backdrop = backdrop;
    ReleaseSRWLockExclusive(&g_frameLock);

    // An acrylic caption, so the title bar matches the blurred page below it.
    DWORD acrylic = DWMSBT_TRANSIENTWINDOW;
    DwmSetWindowAttribute_Original(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &acrylic,
                                   sizeof(acrylic));

    // The shell lookup pumps messages, and doing it here stops the app from
    // attaching to the frame, so it runs on its own thread.
    auto* job = new std::pair<HWND, std::wstring>(hWnd, aumid);
    InterlockedIncrement(&g_iconJobs);
    HANDLE thread = CreateThread(nullptr, 0, IconThread, job, 0, nullptr);
    if (thread) {
        CloseHandle(thread);
    } else {
        InterlockedDecrement(&g_iconJobs);
        delete job;
    }

    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE |
                     SWP_FRAMECHANGED);
    Wh_Log(L"Native title bar for %p", hWnd);
}

// True once the shell shows the frame, or once the wait runs out. Until then the
// frame stays untouched and the timer asks again.
bool ShownOrTimedOut(HWND hWnd) {
    DWORD cloaked = 0;
    DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
    if (!cloaked) {
        RemoveProp(hWnd, kResolveSinceProp);
        return true;
    }
    DWORD now = GetTickCount();
    DWORD since = (DWORD)(ULONG_PTR)GetProp(hWnd, kResolveSinceProp);
    if (!since) {
        since = now;
        SetProp(hWnd, kResolveSinceProp, (HANDLE)(ULONG_PTR)since);
    }
    if (now - since >= kResolveTimeoutMs) {
        RemoveProp(hWnd, kResolveSinceProp);
        return true;
    }
    SetTimer(hWnd, kResolveTimer, kResolveTickMs, nullptr);
    return false;
}

// Shell parts that live in frames and must keep their own look.
bool IsShellSurface(const std::wstring& aumid) {
    static const PCWSTR kPrefixes[] = {
        L"Microsoft.Windows.StartMenuExperienceHost",
        L"Microsoft.Windows.ShellExperienceHost",
        L"MicrosoftWindows.Client.CBS",
        L"MicrosoftWindows.Client.Core",
        L"Microsoft.Windows.Search",
        L"Microsoft.Windows.Cortana",
        L"MicrosoftWindows.LKG",
        L"Microsoft.LockApp",
    };
    for (PCWSTR p : kPrefixes) {
        if (_wcsnicmp(aumid.c_str(), p, wcslen(p)) == 0) {
            return true;
        }
    }
    return false;
}

// Settles a pending frame once its app is known. Runs on the frame's thread.
void ResolveFrame(HWND hWnd) {
    if (GetFrameState(hWnd) != FrameState::Pending) {
        return;
    }
    std::wstring aumid;
    if (!GetFrameApp(hWnd, &aumid)) {
        return;
    }
    bool isSettings = !IsShellSurface(aumid);
    Wh_Log(L"Frame %p app %s: %s", hWnd, aumid.c_str(),
           isSettings ? L"native" : L"stock");
    if (isSettings && !ShownOrTimedOut(hWnd)) {
        return;
    }

    void* titleBar = nullptr;
    AcquireSRWLockExclusive(&g_frameLock);
    FrameInfo& info = g_frames[hWnd];
    info.state = isSettings ? FrameState::Native : FrameState::Stock;
    if (!isSettings) {
        titleBar = info.titleBar;
        info.titleBar = nullptr;  // a native frame keeps it for RestoreFrame
    }
    ReleaseSRWLockExclusive(&g_frameLock);

    if (isSettings) {
        MakeFrameNative(hWnd, aumid);
    } else if (titleBar) {
        CreateTitleBarWindow_Original(titleBar);
    }
}

// Undoes everything for one frame. Runs on the frame's thread; the frame gets
// the title bar window it would have had without the mod.
void RestoreFrame(HWND hWnd) {
    AcquireSRWLockExclusive(&g_frameLock);
    FrameInfo info = g_frames[hWnd];
    g_frames[hWnd].state = FrameState::Stock;
    g_frames[hWnd].titleBar = nullptr;
    ReleaseSRWLockExclusive(&g_frameLock);

    if (info.state == FrameState::Native) {
        RemoveProp(hWnd, kNormalWindowProp);
        RemoveProp(hWnd, kPressedProp);
        KillTimer(hWnd, kRelayoutTimer);
        DwmSetWindowAttribute_Original(hWnd, DWMWA_SYSTEMBACKDROP_TYPE,
                                       &info.backdrop, sizeof(info.backdrop));
        SendMessage(hWnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hWnd, WM_SETICON, ICON_BIG, 0);
        SetWindowLongPtr(hWnd, GWL_STYLE, info.style);
        SetWindowLongPtr(hWnd, GWL_EXSTYLE, info.exStyle);
        SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE |
                         SWP_FRAMECHANGED);
    }
    if (info.titleBar) {
        CreateTitleBarWindow_Original(info.titleBar);
        // The frame host shows its title bar when the caption is activated,
        // then the real state is sent again.
        SendMessage(hWnd, WM_NCACTIVATE, TRUE, 0);
        if (GetForegroundWindow() != hWnd) {
            SendMessage(hWnd, WM_NCACTIVATE, FALSE, 0);
        }
    }
}

LRESULT CaptionHitTest(HWND hWnd, LPARAM lParam) {
    // DWM draws the buttons at its own size, which DefWindowProc doesn't know
    // about, so hit-test against the rects DWM reports.
    TITLEBARINFOEX ti = {sizeof(ti)};
    DefWindowProc(hWnd, WM_GETTITLEBARINFOEX, 0, (LPARAM)&ti);
    POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
    static const int kIndex[] = {2, 3, 5};
    static const LRESULT kHit[] = {HTMINBUTTON, HTMAXBUTTON, HTCLOSE};
    for (int k = 0; k < 3; k++) {
        if (!(ti.rgstate[kIndex[k]] & STATE_SYSTEM_INVISIBLE) &&
            PtInRect(&ti.rgrect[kIndex[k]], pt)) {
            return kHit[k];
        }
    }
    return HTNOWHERE;
}

LRESULT CALLBACK FrameSubclassProc(HWND hWnd,
                                   UINT uMsg,
                                   WPARAM wParam,
                                   LPARAM lParam,
                                   DWORD_PTR) {
    if (uMsg == WM_NCDESTROY || (uMsg == g_frameRestoreMsg && uMsg)) {
        if (uMsg != WM_NCDESTROY) {
            RestoreFrame(hWnd);
        }
        AcquireSRWLockExclusive(&g_frameLock);
        auto it = g_frames.find(hWnd);
        if (it != g_frames.end()) {
            for (HICON i : it->second.icons) {
                if (i) {
                    DestroyIcon(i);
                }
            }
            g_frames.erase(it);
        }
        for (auto t = g_titleBarFrame.begin(); t != g_titleBarFrame.end();) {
            t = t->second == hWnd ? g_titleBarFrame.erase(t) : std::next(t);
        }
        ReleaseSRWLockExclusive(&g_frameLock);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hWnd,
                                                         FrameSubclassProc);
        return uMsg == WM_NCDESTROY
                   ? DefSubclassProc(hWnd, uMsg, wParam, lParam)
                   : 0;
    }

    FrameState state = GetFrameState(hWnd);
    if (state == FrameState::Pending) {
        LRESULT r = DefSubclassProc(hWnd, uMsg, wParam, lParam);
        if (uMsg == WM_TIMER && wParam == kResolveTimer) {
            KillTimer(hWnd, kResolveTimer);
            ResolveFrame(hWnd);
        }
        if (uMsg == g_frameCheckMsg || uMsg == WM_SETTEXT ||
            uMsg == WM_SHOWWINDOW || uMsg == WM_ACTIVATE ||
            uMsg == WM_WINDOWPOSCHANGED) {
            ResolveFrame(hWnd);
        }
        return r;
    }
    if (state != FrameState::Native) {
        return DefSubclassProc(hWnd, uMsg, wParam, lParam);
    }

    switch (uMsg) {
        // The frame host's own handling of these assumes its custom title bar.
        case WM_NCRBUTTONDOWN:
        case WM_NCRBUTTONUP:
        case WM_NCLBUTTONDBLCLK:
        case WM_POPUPSYSTEMMENU:
        case WM_SYSCOMMAND:
        case WM_NCPAINT:
        case WM_NCCALCSIZE:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);

        case WM_NCHITTEST: {
            LRESULT hit = CaptionHitTest(hWnd, lParam);
            return hit != HTNOWHERE
                       ? hit
                       : DefSubclassProc(hWnd, uMsg, wParam, lParam);
        }

        case WM_NCLBUTTONDOWN:
        case WM_NCLBUTTONUP:
            if (wParam == HTMINBUTTON || wParam == HTMAXBUTTON ||
                wParam == HTCLOSE) {
                if (uMsg == WM_NCLBUTTONDOWN) {
                    SetProp(hWnd, kPressedProp, (HANDLE)wParam);
                } else if ((WPARAM)RemoveProp(hWnd, kPressedProp) == wParam) {
                    WPARAM command = wParam == HTCLOSE       ? SC_CLOSE
                                     : wParam == HTMINBUTTON ? SC_MINIMIZE
                                     : IsZoomed(hWnd)        ? SC_RESTORE
                                                             : SC_MAXIMIZE;
                    PostMessage(hWnd, WM_SYSCOMMAND, command, lParam);
                }
                return 0;
            }
            break;

        // DWM lays out the caption once while maximizing or restoring, with
        // the old title bar size. caption-buttons-customizer keeps that
        // layout, which strands the title off-window and moves its button
        // hit areas away from the buttons. A frame change once the size has
        // settled lays the caption out again.
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED) {
                SetTimer(hWnd, kRelayoutTimer, 150, nullptr);
            }
            break;

        case WM_TIMER:
            if (wParam == kRelayoutTimer) {
                KillTimer(hWnd, kRelayoutTimer);
                SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                             SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                                 SWP_NOACTIVATE | SWP_FRAMECHANGED);
                return 0;
            }
            break;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

long __cdecl CreateTitleBarWindow_Hook(void* titleBar) {
    HWND frame = FrameOfTitleBar(titleBar);
    if (frame) {
        AcquireSRWLockExclusive(&g_frameLock);
        auto it = g_frames.find(frame);
        bool hold =
            it != g_frames.end() && it->second.state == FrameState::Pending;
        if (hold) {
            it->second.titleBar = titleBar;
            g_titleBarFrame[titleBar] = frame;
        }
        ReleaseSRWLockExclusive(&g_frameLock);
        if (hold) {
            PostMessage(frame, g_frameCheckMsg, 0, 0);
            return 0;
        }
    }
    return CreateTitleBarWindow_Original(titleBar);
}

long __cdecl PaintButton_Hook(void* titleBar,
                              void* surface,
                              int control,
                              int type,
                              const RECT* a,
                              const RECT* b) {
    AcquireSRWLockShared(&g_frameLock);
    auto it = g_titleBarFrame.find(titleBar);
    HWND frame = it != g_titleBarFrame.end() ? it->second : nullptr;
    ReleaseSRWLockShared(&g_frameLock);
    if (frame && GetFrameState(frame) != FrameState::Stock) {
        return 0;
    }
    return PaintButton_Original(titleBar, surface, control, type, a, b);
}

using CreateWindowInBandEx_t = HWND(WINAPI*)(DWORD,
                                             LPCWSTR,
                                             LPCWSTR,
                                             DWORD,
                                             int,
                                             int,
                                             int,
                                             int,
                                             HWND,
                                             HMENU,
                                             HINSTANCE,
                                             LPVOID,
                                             DWORD,
                                             DWORD);
CreateWindowInBandEx_t CreateWindowInBandEx_Original;
HWND WINAPI CreateWindowInBandEx_Hook(DWORD exStyle,
                                      LPCWSTR className,
                                      LPCWSTR windowName,
                                      DWORD style,
                                      int x,
                                      int y,
                                      int width,
                                      int height,
                                      HWND parent,
                                      HMENU menu,
                                      HINSTANCE instance,
                                      LPVOID param,
                                      DWORD band,
                                      DWORD typeFlags) {
    bool frame = g_enabled && !IS_INTRESOURCE(className) &&
                 _wcsicmp(className, L"ApplicationFrameWindow") == 0;
    if (frame) {
        // A redirection bitmap can only be chosen at creation, and the native
        // caption needs one, so every frame gets it.
        exStyle &= ~WS_EX_NOREDIRECTIONBITMAP;
    }
    HWND hWnd = CreateWindowInBandEx_Original(
        exStyle, className, windowName, style, x, y, width, height, parent,
        menu, instance, param, band, typeFlags);
    if (hWnd && frame) {
        AcquireSRWLockExclusive(&g_frameLock);
        g_frames[hWnd] = FrameInfo{};
        ReleaseSRWLockExclusive(&g_frameLock);
        WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, FrameSubclassProc,
                                                      0);
    }
    return hWnd;
}

using DwmExtendFrameIntoClientArea_t = HRESULT(WINAPI*)(HWND, const MARGINS*);
DwmExtendFrameIntoClientArea_t DwmExtendFrameIntoClientArea_Original;
HRESULT WINAPI DwmExtendFrameIntoClientArea_Hook(HWND hWnd,
                                                 const MARGINS* margins) {
    if (margins) {
        Wh_Log(L"Extend %p state %d margins %d %d %d %d", hWnd,
               (int)GetFrameState(hWnd), margins->cxLeftWidth,
               margins->cxRightWidth, margins->cyTopHeight,
               margins->cyBottomHeight);
    }
    // The frame host extends the frame over its custom title bar, which would
    // hide the native caption.
    if (GetFrameState(hWnd) == FrameState::Native) {
        return 0x80263001;  // DWM_E_COMPOSITIONDISABLED
    }
    return DwmExtendFrameIntoClientArea_Original(hWnd, margins);
}

HRESULT WINAPI DwmSetWindowAttribute_Hook(HWND hWnd,
                                          DWORD attribute,
                                          LPCVOID value,
                                          DWORD size) {
    // Other mods paint a solid caption color; keep the caption see-through
    // and acrylic.
    if ((attribute == DWMWA_CAPTION_COLOR ||
         attribute == DWMWA_SYSTEMBACKDROP_TYPE) &&
        GetFrameState(hWnd) == FrameState::Native) {
        return S_OK;
    }
    return DwmSetWindowAttribute_Original(hWnd, attribute, value, size);
}

void RestoreAllFrames() {
    for (int i = 0; i < 100 && g_iconJobs; i++) {
        Sleep(50);
    }
    std::vector<HWND> frames;
    AcquireSRWLockShared(&g_frameLock);
    for (auto& f : g_frames) {
        frames.push_back(f.first);
    }
    ReleaseSRWLockShared(&g_frameLock);
    for (HWND hWnd : frames) {
        DWORD_PTR r;
        SendMessageTimeout(hWnd, g_frameRestoreMsg, 0, 0, SMTO_NORMAL, 2000,
                           &r);
    }
}

BOOL Init() {
    g_enabled = true;
    g_frameCheckMsg = RegisterWindowMessage(L"RemoveUwpTitleBarsPlus_CheckFrame");
    g_frameRestoreMsg =
        RegisterWindowMessage(L"RemoveUwpTitleBarsPlus_RestoreFrame");

    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {{L"private: long __cdecl CTitleBar::_CreateTitleBarWindow(void)"},
         (void**)&CreateTitleBarWindow_Original,
         (void*)CreateTitleBarWindow_Hook},
        {{L"private: long __cdecl CTitleBar::_PaintButton(struct "
          L"IDCompositionSurface *,enum CTitleBar::TitleBarControl,enum "
          L"TITLE_BAR_BITMAP_TYPE,struct tagRECT const &,struct tagRECT const "
          L"&)"},
         (void**)&PaintButton_Original,
         (void*)PaintButton_Hook},
    };
    HMODULE frameModule = LoadLibraryEx(L"ApplicationFrame.dll", nullptr,
                                        LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!frameModule ||
        !WindhawkUtils::HookSymbols(frameModule, hooks, ARRAYSIZE(hooks))) {
        Wh_Log(L"Failed to hook ApplicationFrame.dll");
        return FALSE;
    }

    HMODULE user32Module =
        LoadLibraryEx(L"user32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    Wh_SetFunctionHook(
        (void*)GetProcAddress(user32Module, "CreateWindowInBandEx"),
        (void*)CreateWindowInBandEx_Hook,
        (void**)&CreateWindowInBandEx_Original);
    Wh_SetFunctionHook((void*)DwmExtendFrameIntoClientArea,
                       (void*)DwmExtendFrameIntoClientArea_Hook,
                       (void**)&DwmExtendFrameIntoClientArea_Original);
    Wh_SetFunctionHook((void*)DwmSetWindowAttribute,
                       (void*)DwmSetWindowAttribute_Hook,
                       (void**)&DwmSetWindowAttribute_Original);
    return TRUE;
}

}  // namespace frame_host

BOOL Wh_ModInit() {
    Wh_Log(L">");
    return frame_host::Init();
}

void Wh_ModBeforeUninit() {
    Wh_Log(L">");
    // While the hooks are still in place, since restoring a frame calls the
    // original title bar function.
    frame_host::RestoreAllFrames();
}
