// ==WindhawkMod==
// @id              seamless-autoclicker
// @name            Seamless AutoClicker
// @description     Hold forward + left mouse button and the left button keeps clicking
// @version         1.1.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         GPL-3.0
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -luser32 -ladvapi32 -lshell32
// ==/WindhawkMod==

// Source code is published under The GNU General Public License v3.0.
//
// For bug reports and feature requests, please open an issue here:
// https://github.com/DavidHiFi/davids-windhawk-mods/issues

// ==WindhawkModReadme==
/*
# Seamless AutoClicker

Hold the forward mouse button and the left button together. The left button
keeps clicking until you let one of them go. Made for mice whose forward
button has no use, like the PRO X2 SUPERSTRIKE.

## How to use

1. Hold the forward button.
2. Hold the left button. Left clicks repeat at the rate set in the mod
   settings.
3. Let go of either button to stop.

Each click is a real press and release, so games that skip zero-length
clicks still count it. The mod runs as administrator, so it also works
over windows opened as administrator.

The forward button is swallowed while the mod is running, the same thing
G Hub did with its G-Shift macro. To get the normal forward button back,
turn the mod off in Windhawk.

## Settings

- **Clicks per second**: how fast the clicks repeat while both buttons are
  held. 1 to 60, suggested 30.

## Credits

Original work, released under GPL-3.0.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- clicksPerSecond: 30
  $name: Clicks per second
  $description: >-
    How fast the clicks repeat while forward and left are held.
    1 to 60 (Suggested: 30).
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <time.h>
#include <atomic>

namespace {

// Tagged onto synthetic clicks so the hook can ignore its own output.
constexpr ULONG_PTR kSyntheticTag = 0xA17CA17C;

std::atomic<bool> g_stop = false;
std::atomic<int> g_halfMs = 17;
std::atomic<bool> g_forwardDown = false;
std::atomic<bool> g_leftDown = false;

HMODULE g_module = nullptr;
DWORD g_hookThreadId = 0;
DWORD g_clickThreadId = 0;
HANDLE g_hookThread = nullptr;
HANDLE g_clickThread = nullptr;
HANDLE g_readyEvent = nullptr;
HANDLE g_instanceMutex = nullptr;

bool LeftPhysicallyDown() {
    return g_leftDown.load(std::memory_order_relaxed);
}

bool ForwardPhysicallyDown() {
    if (g_forwardDown.load(std::memory_order_relaxed)) {
        return true;
    }
    // Fallback for the activator in case the hook missed a press (for
    // example after a settings change mid-hold). Never used for the left
    // button, which our own synthetic clicks would fake.
    return (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) != 0;
}

void SendLeft(DWORD flags) {
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = flags;
    input.mi.dwExtraInfo = kSyntheticTag;
    SendInput(1, &input, sizeof(INPUT));
}

bool IsElevated() {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
        return false;
    }
    TOKEN_ELEVATION elevation{};
    DWORD bytes = 0;
    bool ok = GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &bytes);
    CloseHandle(token);
    return ok && elevation.TokenIsElevated;
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && lParam) {
        auto* data = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
        bool synthetic = data->dwExtraInfo == kSyntheticTag;

        if (!synthetic) {
            switch (wParam) {
            case WM_LBUTTONDOWN:
                g_leftDown.store(true, std::memory_order_relaxed);
                break;
            case WM_LBUTTONUP:
                g_leftDown.store(false, std::memory_order_relaxed);
                break;
            case WM_XBUTTONDOWN:
                if (HIWORD(data->mouseData) == XBUTTON2) {
                    g_forwardDown.store(true, std::memory_order_relaxed);
                }
                break;
            case WM_XBUTTONUP:
                if (HIWORD(data->mouseData) == XBUTTON2) {
                    g_forwardDown.store(false, std::memory_order_relaxed);
                }
                break;
            }
        }

        // Swallow the forward button so apps never see it, G Hub style.
        if (wParam == WM_XBUTTONDOWN || wParam == WM_XBUTTONUP) {
            if (HIWORD(data->mouseData) == XBUTTON2) {
                return 1;
            }
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

DWORD WINAPI HookThreadProc(LPVOID) {
    HHOOK hook = SetWindowsHookExW(WH_MOUSE_LL, LowLevelMouseProc, g_module, 0);
    if (!hook) {
        Wh_Log(L"SetWindowsHookEx(WH_MOUSE_LL) failed: %u", GetLastError());
        SetEvent(g_readyEvent);
        return 0;
    }

    // Touch the message queue before signalling ready so WM_QUIT can't race it.
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    SetEvent(g_readyEvent);

    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnhookWindowsHookEx(hook);
    return 0;
}

DWORD WINAPI ClickThreadProc(LPVOID) {
    while (!g_stop.load(std::memory_order_relaxed)) {
        if (LeftPhysicallyDown() && ForwardPhysicallyDown()) {
            // Up first: the real press is already down when the burst starts.
            int half = g_halfMs.load(std::memory_order_relaxed);
            if (half < 1) {
                half = 1;
            }
            SendLeft(MOUSEEVENTF_LEFTUP);
            Sleep(static_cast<DWORD>(half));
            if (g_stop.load(std::memory_order_relaxed)) {
                break;
            }
            SendLeft(MOUSEEVENTF_LEFTDOWN);
            Sleep(static_cast<DWORD>(half));
        } else {
            Sleep(8);
        }
    }
    return 0;
}

void ReadClicksPerSecond() {
    int cps = Wh_GetIntSetting(L"clicksPerSecond");
    if (cps < 1) cps = 1;
    if (cps > 60) cps = 60;
    int half = 500 / cps;
    if (half < 1) half = 1;
    g_halfMs.store(half, std::memory_order_relaxed);
}

void ResetState() {
    g_forwardDown.store(false, std::memory_order_relaxed);
    g_leftDown.store(false, std::memory_order_relaxed);
}

}  // namespace

BOOL WhTool_ModInit() {
    // Unelevated hooks miss clicks over admin windows. UAC prompts are off on
    // this PC, so relaunch elevated and let this copy exit.
    if (!IsElevated()) {
        WCHAR self[MAX_PATH];
        if (GetModuleFileNameW(nullptr, self, MAX_PATH)) {
            SHELLEXECUTEINFOW launch{sizeof(launch)};
            launch.fMask = SEE_MASK_FLAG_NO_UI;
            launch.lpVerb = L"runas";
            launch.lpFile = self;
            launch.lpParameters = L"-windhawk-tool-mod \"" WH_MOD_ID L"\"";
            launch.nShow = SW_HIDE;
            if (ShellExecuteExW(&launch)) {
                return FALSE;
            }
        }
        Wh_Log(L"Elevated relaunch failed, running unelevated");
    }

    g_instanceMutex = CreateMutexW(nullptr, FALSE, L"Global\\SeamlessAutoClicker");
    if (g_instanceMutex && GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(g_instanceMutex);
        g_instanceMutex = nullptr;
        return FALSE;
    }

    g_module = GetModuleHandleW(nullptr);
    g_readyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_readyEvent) {
        Wh_Log(L"CreateEvent failed: %u", GetLastError());
        return FALSE;
    }
    ResetState();
    ReadClicksPerSecond();

    g_hookThread = CreateThread(nullptr, 0, HookThreadProc, nullptr, 0, &g_hookThreadId);
    if (!g_hookThread) {
        Wh_Log(L"CreateThread(hook) failed: %u", GetLastError());
        CloseHandle(g_readyEvent);
        g_readyEvent = nullptr;
        return FALSE;
    }
    WaitForSingleObject(g_readyEvent, 5000);
    CloseHandle(g_readyEvent);
    g_readyEvent = nullptr;

    g_clickThread = CreateThread(nullptr, 0, ClickThreadProc, nullptr, 0, &g_clickThreadId);
    if (!g_clickThread) {
        Wh_Log(L"CreateThread(click) failed: %u", GetLastError());
        g_stop.store(true, std::memory_order_relaxed);
        PostThreadMessageW(g_hookThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g_hookThread, 3000);
        CloseHandle(g_hookThread);
        g_hookThread = nullptr;
        return FALSE;
    }
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    ReadClicksPerSecond();
    ResetState();
}

void WhTool_ModUninit() {
    g_stop.store(true, std::memory_order_relaxed);
    if (g_hookThreadId) {
        PostThreadMessageW(g_hookThreadId, WM_QUIT, 0, 0);
    }
    if (g_clickThread) {
        WaitForSingleObject(g_clickThread, 3000);
        CloseHandle(g_clickThread);
        g_clickThread = nullptr;
    }
    if (g_hookThread) {
        WaitForSingleObject(g_hookThread, 3000);
        CloseHandle(g_hookThread);
        g_hookThread = nullptr;
    }
    ResetState();
    if (g_instanceMutex) {
        CloseHandle(g_instanceMutex);
        g_instanceMutex = nullptr;
    }
}

#include <windhawk_tool_mod.h>
