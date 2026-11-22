// ==WindhawkMod==
// @id              dsx-tray-icon-fix
// @name            DSX Tray Icon Fix
// @description     Keeps DSX to one tray icon that always shows its picture, even after DSX runs out of drawing memory
// @version         1.0.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         DSX.exe
// @architecture    x86-64
// @compilerOptions -lshell32 -luser32 -lgdi32
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# DSX Tray Icon Fix

DSX puts its tray icon back every few seconds. Each time it makes a new hidden
window and a new copy of the picture, and it never frees either. After an hour or
two it runs out of drawing memory. From then on every new tray icon comes up
blank, and the old ones can stay behind, so the tray fills with empty DSX tiles.

This mod keeps it to one tile with the real picture:

- When DSX adds its icon, any older DSX tray icon is removed first, so there is
  only ever one.
- The first good picture DSX shows is kept. When DSX later sends no picture, or
  one it could not finish drawing, the kept picture is used instead.

It only changes what DSX sends to the tray. DSX itself, its controller work and
its settings are left alone.

## What's new in 1.0.0

- First release.
*/
// ==/WindhawkModReadme==

#include <windows.h>
#include <shellapi.h>

#include <algorithm>
#include <mutex>
#include <vector>

namespace {

struct Entry {
    HWND hwnd;
    UINT uid;
};

using ShellNotifyIconW_t = BOOL(WINAPI*)(DWORD, PNOTIFYICONDATAW);
ShellNotifyIconW_t g_original;
std::mutex g_lock;
std::vector<Entry> g_live;      // entries this process has in the tray
HICON g_goodIcon;

bool IsWpfUiTrayWindow(HWND hwnd) {
    if (!hwnd)
        return false;
    wchar_t title[64]{};
    // InternalGetWindowText reads the title without sending a message, so it
    // cannot wait on a busy UI thread.
    InternalGetWindowText(hwnd, title, ARRAYSIZE(title));
    return wcsncmp(title, L"wpfui_th_", 9) == 0;
}

bool IconIsUsable(HICON icon) {
    if (!icon)
        return false;
    ICONINFO info{};
    // Out of drawing memory, this fails even for a good icon. The kept copy is
    // the same picture, so using it then is harmless.
    if (!GetIconInfo(icon, &info))
        return false;
    if (info.hbmColor)
        DeleteObject(info.hbmColor);
    if (info.hbmMask)
        DeleteObject(info.hbmMask);
    return info.hbmMask != nullptr;
}

BOOL DeleteEntry(Entry const& e) {
    NOTIFYICONDATAW data{};
    data.cbSize = sizeof(data);
    data.hWnd = e.hwnd;
    data.uID = e.uid;
    return g_original(NIM_DELETE, &data);
}

void Forget(std::vector<Entry>& list, HWND hwnd, UINT uid) {
    list.erase(std::remove_if(list.begin(), list.end(),
                              [&](Entry const& e) { return e.hwnd == hwnd && e.uid == uid; }),
               list.end());
}

// Icons DSX added before the mod loaded are not in g_live. Its tray windows are
// titled wpfui_th_<parent>_<id> and each added its icon with uID = <id>, so the
// first add after loading removes all of those once. Caller holds g_lock.
bool g_swept;

BOOL CALLBACK SweepWindow(HWND hwnd, LPARAM keep) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != GetCurrentProcessId() || hwnd == reinterpret_cast<HWND>(keep))
        return TRUE;
    wchar_t title[64]{};
    InternalGetWindowText(hwnd, title, ARRAYSIZE(title));
    if (wcsncmp(title, L"wpfui_th_", 9) != 0)
        return TRUE;
    wchar_t const* id = wcsrchr(title, L'_');
    if (id && id[1])
        DeleteEntry({hwnd, static_cast<UINT>(wcstoul(id + 1, nullptr, 10))});
    return TRUE;
}

// Caller holds g_lock.
void FixIcon(NOTIFYICONDATAW& data, bool adding) {
    bool hasIcon = (data.uFlags & NIF_ICON) != 0;
    if (hasIcon && IconIsUsable(data.hIcon)) {
        if (!g_goodIcon) {
            g_goodIcon = CopyIcon(data.hIcon);
            Wh_Log(L"Kept DSX's tray picture: %d", g_goodIcon != nullptr);
        }
        return;
    }
    if (!g_goodIcon || (!hasIcon && !adding))
        return;  // a change that does not touch the picture
    data.uFlags |= NIF_ICON;
    data.hIcon = g_goodIcon;
    Wh_Log(L"DSX sent no usable picture; used the kept one");
}

BOOL WINAPI ShellNotifyIconW_Hook(DWORD message, PNOTIFYICONDATAW in) {
    if (!in || in->cbSize < NOTIFYICONDATAW_V2_SIZE || (in->uFlags & NIF_GUID) ||
        !IsWpfUiTrayWindow(in->hWnd))
        return g_original(message, in);

    std::lock_guard<std::mutex> guard(g_lock);
    NOTIFYICONDATAW data{};
    DWORD size = std::min<DWORD>(in->cbSize, sizeof(data));
    memcpy(&data, in, size);
    data.cbSize = size;

    switch (message) {
        case NIM_ADD: {
            FixIcon(data, true);
            BOOL ok = g_original(NIM_ADD, &data);
            if (ok) {
                // The new icon is up: remove every older one.
                size_t removed = 0;
                for (auto const& e : g_live) {
                    if (e.hwnd == data.hWnd && e.uid == data.uID)
                        continue;
                    DeleteEntry(e);
                    ++removed;
                }
                g_live.clear();
                g_live.push_back({data.hWnd, data.uID});
                if (!g_swept) {
                    g_swept = true;
                    EnumWindows(SweepWindow, reinterpret_cast<LPARAM>(data.hWnd));
                    Wh_Log(L"Cleared DSX tray icons left from before the mod loaded");
                }
                if (removed)
                    Wh_Log(L"Removed %zu older DSX tray icon(s)", removed);
            }
            return ok;
        }
        case NIM_MODIFY:
            FixIcon(data, false);
            return g_original(NIM_MODIFY, &data);
        case NIM_DELETE:
            Forget(g_live, data.hWnd, data.uID);
            return g_original(NIM_DELETE, &data);
        default:
            return g_original(message, &data);
    }
}

}  // namespace

BOOL Wh_ModInit() {
    HMODULE shell = LoadLibraryExW(L"shell32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    auto target = shell ? reinterpret_cast<ShellNotifyIconW_t>(GetProcAddress(shell, "Shell_NotifyIconW"))
                        : nullptr;
    if (!target) {
        Wh_Log(L"Shell_NotifyIconW not found");
        return FALSE;
    }
    if (!Wh_SetFunctionHook(reinterpret_cast<void*>(target),
                            reinterpret_cast<void*>(ShellNotifyIconW_Hook),
                            reinterpret_cast<void**>(&g_original)))
        return FALSE;
    Wh_Log(L"DSX Tray Icon Fix loaded");
    return TRUE;
}

void Wh_ModUninit() {
    // g_goodIcon stays alive: a DSX call already in flight may still pass it.
    // It is one icon and goes away with the process.
}
