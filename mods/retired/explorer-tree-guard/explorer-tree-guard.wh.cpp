// ==WindhawkMod==
// @id              explorer-tree-guard
// @name            Explorer Tree Guard
// @description     Stops File Explorer windows crashing when the folder tree gets a request from a thread that already gave up
// @version         1.0.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         explorer.exe
// @compilerOptions -luser32 -lcomctl32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Explorer Tree Guard

A File Explorer window can close by itself with a crash in the folder tree on the
left (COMCTL32, the tree's own window code).

It happens like this. Some code in Explorer asks the folder tree for an item's
position and hands it a spot in its own memory to write the answer. If that code
stops waiting before the tree gets to the request, its memory is gone by the time
the tree answers, and the tree crashes writing to it.

This mod checks each such request that comes from another thread. If the answer
spot is no longer valid memory, the tree skips that one request instead of
crashing. Nothing else about the tree changes.

It also notes in the Windhawk log which code gave up on a tree request, so the
real sender can be found and fixed.
*/
// ==/WindhawkModReadme==

#include <windows.h>
#include <commctrl.h>
#include <windhawk_utils.h>

#include <atomic>
#include <mutex>
#include <unordered_set>

namespace {

std::mutex g_treesMutex;
std::unordered_set<HWND> g_trees;
std::atomic<bool> g_unloading{false};
std::atomic<LONG> g_blocked{0};

bool IsTreeWindow(HWND hwnd) {
    wchar_t cls[32];
    return GetClassNameW(hwnd, cls, ARRAYSIZE(cls)) && !_wcsicmp(cls, WC_TREEVIEWW);
}

// True when [p, p + size) is committed, writable and not a guard page.
bool IsWritableRange(const void* p, SIZE_T size) {
    if (!p) return false;
    MEMORY_BASIC_INFORMATION mbi;
    if (!VirtualQuery(p, &mbi, sizeof(mbi))) return false;
    if (mbi.State != MEM_COMMIT) return false;
    if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) return false;
    const DWORD writable = PAGE_READWRITE | PAGE_WRITECOPY |
                           PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
    if (!(mbi.Protect & writable)) return false;
    auto start = reinterpret_cast<ULONG_PTR>(p);
    auto regionEnd = reinterpret_cast<ULONG_PTR>(mbi.BaseAddress) + mbi.RegionSize;
    return start + size <= regionEnd;
}

// Messages where the tree reads or writes through lParam.
SIZE_T PointerSize(UINT msg) {
    switch (msg) {
        case TVM_GETITEMRECT: return sizeof(RECT);
        case TVM_GETITEMW: return sizeof(TVITEMW);
        case TVM_GETITEMA: return sizeof(TVITEMA);
        case TVM_HITTEST: return sizeof(TVHITTESTINFO);
        default: return 0;
    }
}

LRESULT CALLBACK TreeSubclassProc(HWND hwnd, UINT msg, WPARAM wParam,
                                  LPARAM lParam, DWORD_PTR) {
    if (msg == WM_NCDESTROY) {
        std::lock_guard<std::mutex> lock(g_treesMutex);
        g_trees.erase(hwnd);
    } else if (SIZE_T size = PointerSize(msg)) {
        // Only requests sent from another thread can outlive their sender.
        if ((InSendMessageEx(nullptr) & (ISMEX_SEND | ISMEX_REPLIED)) == ISMEX_SEND &&
            !IsWritableRange(reinterpret_cast<void*>(lParam), size)) {
            LONG n = ++g_blocked;
            Wh_Log(L"Skipped tree message 0x%X with dead pointer %p (count %ld)",
                   msg, reinterpret_cast<void*>(lParam), n);
            return 0;
        }
    }
    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

void AttachTree(HWND hwnd) {
    if (g_unloading || !IsTreeWindow(hwnd)) return;
    {
        std::lock_guard<std::mutex> lock(g_treesMutex);
        if (!g_trees.insert(hwnd).second) return;
    }
    if (!WindhawkUtils::SetWindowSubclassFromAnyThread(hwnd, TreeSubclassProc, 0)) {
        std::lock_guard<std::mutex> lock(g_treesMutex);
        g_trees.erase(hwnd);
    }
}

BOOL CALLBACK AttachChild(HWND hwnd, LPARAM) {
    AttachTree(hwnd);
    return TRUE;
}

BOOL CALLBACK AttachTop(HWND hwnd, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid == GetCurrentProcessId()) EnumChildWindows(hwnd, AttachChild, 0);
    return TRUE;
}

using CreateWindowExW_t = decltype(&CreateWindowExW);
CreateWindowExW_t CreateWindowExW_Original;

HWND WINAPI CreateWindowExW_Hook(DWORD exStyle, LPCWSTR className, LPCWSTR name,
                                 DWORD style, int x, int y, int w, int h,
                                 HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) {
    HWND hwnd = CreateWindowExW_Original(exStyle, className, name, style, x, y, w,
                                         h, parent, menu, inst, param);
    if (hwnd && parent) AttachTree(hwnd);
    return hwnd;
}

// Logs who gives up on a tree request: that caller is the real cause.
using SendMessageTimeoutW_t = decltype(&SendMessageTimeoutW);
SendMessageTimeoutW_t SendMessageTimeoutW_Original;

LRESULT WINAPI SendMessageTimeoutW_Hook(HWND hwnd, UINT msg, WPARAM wParam,
                                        LPARAM lParam, UINT flags, UINT timeout,
                                        PDWORD_PTR result) {
    void* caller = __builtin_return_address(0);
    LRESULT ok = SendMessageTimeoutW_Original(hwnd, msg, wParam, lParam, flags,
                                              timeout, result);
    if (!ok && PointerSize(msg) && IsTreeWindow(hwnd)) {
        HMODULE module = nullptr;
        wchar_t path[MAX_PATH] = L"?";
        if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                   GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                               static_cast<LPCWSTR>(caller), &module))
            GetModuleFileNameW(module, path, MAX_PATH);
        Wh_Log(L"Tree message 0x%X timed out after %u ms, sender %s+0x%IX thread %lu",
               msg, timeout, path,
               reinterpret_cast<ULONG_PTR>(caller) - reinterpret_cast<ULONG_PTR>(module),
               GetCurrentThreadId());
    }
    return ok;
}

}  // namespace

BOOL Wh_ModInit() {
    Wh_SetFunctionHook(reinterpret_cast<void*>(CreateWindowExW),
                       reinterpret_cast<void*>(CreateWindowExW_Hook),
                       reinterpret_cast<void**>(&CreateWindowExW_Original));
    Wh_SetFunctionHook(reinterpret_cast<void*>(SendMessageTimeoutW),
                       reinterpret_cast<void*>(SendMessageTimeoutW_Hook),
                       reinterpret_cast<void**>(&SendMessageTimeoutW_Original));
    return TRUE;
}

void Wh_ModAfterInit() {
    EnumWindows(AttachTop, 0);
}

void Wh_ModBeforeUninit() {
    g_unloading = true;
    std::unordered_set<HWND> trees;
    {
        std::lock_guard<std::mutex> lock(g_treesMutex);
        trees.swap(g_trees);
    }
    for (HWND hwnd : trees)
        if (IsWindow(hwnd))
            WindhawkUtils::RemoveWindowSubclassFromAnyThread(hwnd, TreeSubclassProc);
}

void Wh_ModUninit() {}
