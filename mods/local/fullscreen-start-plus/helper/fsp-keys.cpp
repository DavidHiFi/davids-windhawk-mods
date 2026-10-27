// Fullscreen Start Plus keys helper
//
// Windows keeps keys typed in a window that runs as administrator away from
// programs that don't, Explorer included, so the mod can't see Shift + Windows
// key there, and the Ctrl+Esc it presses to open the grid is dropped. This
// helper runs as administrator (a scheduled task, see README.md), watches for
// Shift + Windows key with the same rules as the mod, asks the mod's window
// what to do, and presses Ctrl+Esc for it. While this helper runs, the mod's
// own hook leaves the key alone (it looks for this helper's window).
//
// Build: clang++ -std=c++23 -O2 -municode -mwindows -static fsp-keys.cpp -o fsp-keys.exe

#include <windows.h>

constexpr WCHAR kClass[] = L"FullscreenStartPlusKeys";
constexpr WCHAR kGridClass[] = L"WindhawkFullscreenStartPlus";
constexpr UINT WM_APP_SHIFT_WIN = WM_APP + 6;  // Same as the mod.
constexpr UINT WM_APP_PRESSED = WM_APP + 1;
constexpr UINT_PTR kTimerKeysUp = 1;
constexpr UINT_PTR kTimerFront = 2;

HWND g_wnd;
HWND g_grid;
int g_waited;

// The mod's window in the Explorer that owns the taskbar.
HWND FindGrid() {
    DWORD tray = 0;
    GetWindowThreadProcessId(FindWindowW(L"Shell_TrayWnd", nullptr), &tray);
    for (HWND h = nullptr;
         (h = FindWindowExW(nullptr, h, kGridClass, nullptr));) {
        DWORD pid = 0;
        GetWindowThreadProcessId(h, &pid);
        if (pid == tray) {
            return h;
        }
    }
    return nullptr;
}

// Shift counts if it was down at any point while Win was (macro keys let go
// of Shift first), and any other key in between makes it a Windows shortcut.
LRESULT CALLBACK KeyboardHook(int code, WPARAM wParam, LPARAM lParam) {
    static bool winDown, otherKey, withShift;
    if (code == HC_ACTION) {
        DWORD vk = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
        bool up = wParam == WM_KEYUP || wParam == WM_SYSKEYUP;
        bool shift = vk == VK_SHIFT || vk == VK_LSHIFT || vk == VK_RSHIFT;
        if (vk == VK_LWIN || vk == VK_RWIN) {
            if (!up && !winDown) {
                winDown = true;
                otherKey = false;
                withShift = GetAsyncKeyState(VK_SHIFT) < 0;
            } else if (up && winDown) {
                winDown = false;
                if (!otherKey && withShift) {
                    PostMessageW(g_wnd, WM_APP_PRESSED, 0, 0);
                }
            }
        } else if (shift && !up && winDown) {
            withShift = true;
        } else if (!up && !shift && winDown) {
            otherKey = true;
        }
    }
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

bool KeysUp() {
    return GetAsyncKeyState(VK_SHIFT) >= 0 && GetAsyncKeyState(VK_LWIN) >= 0 &&
           GetAsyncKeyState(VK_RWIN) >= 0;
}

void PressCtrlEsc() {
    INPUT keys[4] = {};
    WORD vks[4] = {VK_CONTROL, VK_ESCAPE, VK_ESCAPE, VK_CONTROL};
    for (int i = 0; i < 4; i++) {
        keys[i].type = INPUT_KEYBOARD;
        keys[i].ki.wVk = vks[i];
        keys[i].ki.dwFlags = i < 2 ? 0 : KEYEVENTF_KEYUP;
    }
    SendInput(4, keys, sizeof(INPUT));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_APP_PRESSED: {
            g_grid = FindGrid();
            DWORD_PTR answer = 0;
            if (g_grid &&
                SendMessageTimeoutW(g_grid, WM_APP_SHIFT_WIN, 1, 0,
                                    SMTO_ABORTIFHUNG, 1000, &answer) &&
                answer == 1) {
                g_waited = 0;
                SetTimer(hwnd, kTimerKeysUp, 20, nullptr);
            }
            return 0;
        }
        case WM_TIMER:
            if (wParam == kTimerKeysUp) {
                // With Shift still down, Ctrl+Esc would be Task Manager.
                if (KeysUp() || ++g_waited > 150) {
                    KillTimer(hwnd, kTimerKeysUp);
                    PressCtrlEsc();
                    g_waited = 0;
                    SetTimer(hwnd, kTimerFront, 50, nullptr);
                }
            } else if (wParam == kTimerFront) {
                // Explorer may not get the foreground from an administrator
                // window. This process pressed the last key, so it can give it.
                if (IsWindowVisible(g_grid)) {
                    KillTimer(hwnd, kTimerFront);
                    if (GetForegroundWindow() != g_grid) {
                        SetForegroundWindow(g_grid);
                    }
                } else if (++g_waited > 20) {
                    KillTimer(hwnd, kTimerFront);
                }
            }
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int) {
    if (FindWindowW(kClass, nullptr)) {
        return 0;  // Already running.
    }
    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = instance;
    wc.lpszClassName = kClass;
    RegisterClassW(&wc);
    // A hidden top-level window (not message-only), so FindWindow finds it.
    g_wnd = CreateWindowExW(WS_EX_TOOLWINDOW, kClass, kClass, WS_POPUP, 0, 0,
                            0, 0, nullptr, nullptr, instance, nullptr);
    HHOOK hook =
        SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardHook, instance, 0);
    if (!g_wnd || !hook) {
        return 1;
    }
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        DispatchMessageW(&msg);
    }
    UnhookWindowsHookEx(hook);
    return 0;
}
