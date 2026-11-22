// ==WindhawkMod==
// @id              dark-theme-browser-colors-fix-plus
// @name            Dark Theme Browser Colors Fix Plus
// @description     Fixes web pages that show white text on white or black text on dark under the Windows dark theme, and never crashes the browser when it closes
// @version         1.1.0
// @author          DavidHiFi, Roland Pihlakas
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         GPL-3.0
// @donateUrl       https://ko-fi.com/DavidHiFi
// @compilerOptions -lgdi32 -luser32 -lshlwapi -lversion
// @include         brave.exe
// @include         chrome.exe
// @include         chromium.exe
// @include         firefox.exe
// @include         msedge.exe
// @include         msedgewebview*.exe
// @include         opera.exe
// ==/WindhawkMod==

// Source code is published under The GNU General Public License v3.0.
//
// For bug reports and feature requests, please open an issue here:
// https://github.com/levitation-opensource/my-windhawk-mods/issues
//
// For pull requests, development takes place here:
// https://github.com/levitation-opensource/my-windhawk-mods/

// ==WindhawkModReadme==
/*
# Dark Theme Browser Colors Fix Plus

Some web pages pick up Windows' own colors but expect the light theme. Under the dark
theme they end up with white text on a white page or black text on a dark one. This mod
hands those pages the light Windows colors they expect, so they read normally again.
Pages that set their own colors are left alone, and so are the browser's own frame and
the file picker.

Works in Brave, Chrome, Chromium, Edge, Firefox, Opera and Helium, plus the document
viewer inside Teams.

Based on [Fix browser and Teams text colors in dark mode](https://windhawk.net/mods/dark-theme-browser-colors-fix)
by [Roland Pihlakas](https://github.com/levitation).

## What's new in 1.1.0

- The browser no longer crashes when it closes. The old version could touch its own
  brush list after Windows had already torn it down.
- Helium only gets the fix on builds listed in the settings. A new Helium build is
  skipped quietly until you add it, so an update can never take the browser down.

## Good to know

Some pages need a browser restart before they change. Turning the mod off while a
browser is open can upset the tabs that were using the fixed colors; restart the browser
after turning it off.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- applyToAllMsEdgeWebView: false
  $name: Fix every app that uses Edge WebView
  $description: When on, every app built on Edge WebView gets the fix. When off, only the Teams document viewer does. Browsers always get it.
- heliumBuilds: "0.21.1.1"
  $name: Helium builds to fix
  $description: Helium versions the fix runs on, separated by commas (Suggested 0.21.1.1). Any other Helium build is skipped quietly, so a new version can't crash the browser. Leave it empty to skip Helium entirely, or write * to run on every build.
*/
// ==/WindhawkModSettings==


#pragma region Includes

#include <windowsx.h>
#include <winver.h>
#include <intrin.h>
#include <shlwapi.h>

#include <atomic>
#include <mutex>
#include <map>
#include <unordered_set>

#pragma endregion Includes



#pragma region Reusable general helper functions

template <typename T>
BOOL Wh_SetFunctionHookT(
    FARPROC targetFunction,
    T hookFunction,
    T* originalFunction
) {
    return Wh_SetFunctionHook((void*)targetFunction, (void*)hookFunction, (void**)originalFunction);
}

#pragma endregion Reusable general helper functions



#pragma region Global variables

const int nMaxPathLength = (MAX_PATH * 16);
const int nMaxDllPathLength = nMaxPathLength;  //there is no function for retrieving the dll module name length, so need to use custom limit
#define MAX_COLOR_INDEX     COLOR_MENUBAR

const wchar_t* filePickerDlls[] = {
    L"\\Shell32.dll",       //folder tree
    L"\\ComCtl32.dll",      //top folder location bar and save/cancel buttons
    L"\\DUI70.dll",         //file list
    L"\\ExplorerFrame.dll", //file search box (at top right)
    L"\\uxtheme.dll",       //a dropdown opening from the file search box
    L"\\ACLUI.dll",         //file permissions dialog
    L"\\gdi32full.dll",     //file picker selected text
    L"\\comdlg32.dll"       //left panel in classic file picker (in case the Classic File Picker dialog mod is installed)    
};

const COLORREF defaultWindowsColors[] = {   //Default Windows10 colors
    0x00C8C8C8, //0
    0x00FF8000, //1
    0x00D1B499, //2
    0x00DBCDBF, //3

    0x00F0F0F0, //4
    0x00FFFFFF, //5
    0x00646464, //6
    0x00000000, //7

    0x00000000, //8
    0x00000000, //9
    0x00B4B4B4, //10
    0x00FCF7F4, //11

    0x00ABABAB, //12
    0x00D77800, //13
    0x00000000, //14
    0x00F0F0F0, //15

    0x00A0A0A0, //16
    0x006D6D6D, //17
    0x00000000, //18
    0x00000000, //19

    0x00FFFFFF, //20
    0x00696969, //21
    0x00E3E3E3, //22
    0x00000000, //23

    0x00E1FFFF, //24
    0x00000000, //25 - unused in GetSysColor, GetSysColorBrush, and GetThemeSysColor, but used for TMT_BUTTONALTERNATEFACE in GetThemeSysColorBrush
    0x00CC6600, //26
    0x00EAD1B9, //27

    0x00F2E4D7, //28
    0x00D77800, //29
    0x00F0F0F0, //30
};

DWORD g_processId = -1;

std::atomic<size_t> g_hookRefCount;

// 1.1.0: these live on the heap and are never freed. At process exit Windows runs this
// DLL's static destructors before other DLLs (comctl32, for one) finish detaching, and
// those still call DeleteObject and GetSysColorBrush. A destroyed std container there
// is the 1.0 crash (access violation in DeleteObjectHook during RtlDllShutdown).
SRWLOCK g_filePickerDetectionLock = SRWLOCK_INIT;
std::map<void*, bool>* g_filePickerDetectionMap = nullptr;

using RtlDllShutdownInProgress_t = BOOLEAN(NTAPI*)();
RtlDllShutdownInProgress_t pRtlDllShutdownInProgress = nullptr;

HMODULE hGdi32 = NULL;
HMODULE hUser32 = NULL;

HBRUSH g_preallocatedBrushes[MAX_COLOR_INDEX + 1] = {};

bool g_isNonTeamsWebView = false;
bool g_applyToAllWebView = false;

std::atomic<bool> g_unloading{false};
std::atomic<bool> g_unloaded{false};

static bool ProcessExiting() {
    return pRtlDllShutdownInProgress && pRtlDllShutdownInProgress();
}

static bool ShuttingDown() {
    return g_unloaded || ProcessExiting();
}

static bool IsPreallocatedBrush(HGDIOBJ ho) {
    if (!ho)
        return false;
    for (int i = 0; i <= MAX_COLOR_INDEX; i++) {
        if (g_preallocatedBrushes[i] == (HBRUSH)ho)
            return true;
    }
    return false;
}

#pragma endregion Global variables



#pragma region Originals of hooked functions

using GetSysColor_t = decltype(&GetSysColor); 
GetSysColor_t pOriginalGetSysColor; 

using GetSysColorBrush_t = decltype(&GetSysColorBrush); 
GetSysColorBrush_t pOriginalGetSysColorBrush; 

using DeleteObject_t = decltype(&DeleteObject); 
DeleteObject_t pOriginalDeleteObject;

#pragma endregion Originals of hooked functions



#pragma region Reusable scope and reference counting functions

void IncrementHookRefCountA(LPCSTR tag) {

    g_hookRefCount++;
}

void DecrementHookRefCountA(LPCSTR tag) {

    g_hookRefCount--;
}

auto HookRefCountScopeA(LPCSTR tag) {

    IncrementHookRefCountA(tag);

    return std::unique_ptr<
        const CHAR,
        void(*)(LPCSTR)
    >{
        tag, [](LPCSTR tag) {
            DecrementHookRefCountA(tag);
        }
    };
}

#define AUTO_HOOK_COUNT_SCOPE           auto hookScope = HookRefCountScopeA(__func__);   //deny mod unload until this function exits

#pragma endregion Reusable scope and reference counting functions



#pragma region Caller module name getter

#ifdef _MSC_VER
#define ReturnAddress()     _ReturnAddress()
#else   //clang compiler
#define ReturnAddress()     __builtin_return_address(0)
#endif

HMODULE GetCallerModule(void *address) {

    if (!address)
        return NULL;

    SetLastError(0);    //some Windows API-s do not clear earlier errors in case of success, so lets clear it here manually just in case, so we can check for error after the call

    HMODULE hModule;
    if (!GetModuleHandleExW(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCTSTR)address, 
        &hModule
    )) {    //usually GetModuleHandleExW fails in case of .NET executables
        int errorCode = GetLastError();
        Wh_Log(L"Getting caller module failed for address 0x%llX error %i", (long long)address, errorCode);
        return NULL;
    }
    return hModule;
}

LPCWSTR GetModuleName(
    HMODULE hModule,
    LPWSTR  stackBuffer,
    int     stackBufferSize
) {
    if (!hModule)
        return NULL;

    SetLastError(0);    //some Windows API-s do not clear earlier errors in case of success, so lets clear it here manually just in case, so we can check for error after the call

    if (!GetModuleFileNameW(
        hModule,
        stackBuffer,
        stackBufferSize
    )) {
        Wh_Log(L"GetModuleFileNameW failed. Module 0x%llX", (long long)hModule);

        SetLastError(0);
        return NULL;
    }
    //If the buffer is too small to hold the module name, the string is truncated to nSize characters including the terminating null character, the function returns nSize, and the function sets the last error to ERROR_INSUFFICIENT_BUFFER.
    else if (GetLastError()) {
        Wh_Log(L"GetModuleFileNameW failed, probably the module path is too long. Module 0x%llX", (long long)hModule);

        SetLastError(0);
        return NULL;
    }
    else {
        return stackBuffer;
    }
}

bool IsCallerFilePicker(void* returnAddress) {

    bool result = false;

    if (!g_filePickerDetectionMap)
        return true;    // not set up yet: leave the colors alone

    AcquireSRWLockExclusive(&g_filePickerDetectionLock);
    auto it = g_filePickerDetectionMap->find(returnAddress);
    if (it != g_filePickerDetectionMap->end()) {
        result = it->second;
    }
    else {
        HMODULE callerModule = GetCallerModule(returnAddress);

        WCHAR stackBuffer[nMaxDllPathLength];
        PCWSTR callerDllPath = GetModuleName(
            callerModule,
            stackBuffer,
            nMaxDllPathLength
        );

        if (callerDllPath) {

            size_t callerDllPathLen = wcslen(callerDllPath);

            for (unsigned int i = 0; i < ARRAYSIZE(filePickerDlls); i++) {

                LPCWSTR checkPath = filePickerDlls[i];
                size_t checkPathLen = wcslen(checkPath);
                if (
                    callerDllPathLen >= checkPathLen
                    && wcsicmp(&callerDllPath[callerDllPathLen - checkPathLen], checkPath) == 0     //match end of path
                ) {
                    result = true;
                    break;
                }
            }
        }

        if (result) {
            Wh_Log(L"A file picker caller detected: %ls", callerDllPath ? callerDllPath : L"");
        }
        else {
            Wh_Log(L"A non file picker caller detected: %ls", callerDllPath ? callerDllPath : L"");
        }

        g_filePickerDetectionMap->insert({ 
            returnAddress, 
            result
        });
    }
    ReleaseSRWLockExclusive(&g_filePickerDetectionLock);

    return result;
}

#pragma endregion Caller module name getter



#pragma region Hooks

DWORD WINAPI GetSysColorHook(IN int nIndex) {

    AUTO_HOOK_COUNT_SCOPE;

    if (
        nIndex >= 0
        && nIndex <= MAX_COLOR_INDEX
        && !g_unloading
        && !ShuttingDown()
        && (!g_isNonTeamsWebView || g_applyToAllWebView)
        && !IsCallerFilePicker(ReturnAddress())    //file picker detection
    ) {
        return defaultWindowsColors[nIndex];
    }
    else {
        return pOriginalGetSysColor(nIndex);
    }
}

HBRUSH WINAPI GetSysColorBrushHook(IN int nIndex) {

    AUTO_HOOK_COUNT_SCOPE;

    if (
        nIndex >= 0 
        && nIndex <= MAX_COLOR_INDEX
        && !g_unloading
        && !ShuttingDown()
        && g_preallocatedBrushes[nIndex]
        && (!g_isNonTeamsWebView || g_applyToAllWebView)
        && !IsCallerFilePicker(ReturnAddress())    //file picker detection
    ) {
        //Need to use preallocated system color brushes since the program does not have to free them and allocating a new brush upon each CreateSolidBrushHook call would result in a resource leak.
        return g_preallocatedBrushes[nIndex];
    }
    else {
        return pOriginalGetSysColorBrush(nIndex);
    }
}

BOOL WINAPI DeleteObjectHook(IN HGDIOBJ ho) {

    AUTO_HOOK_COUNT_SCOPE;

    if (
        !g_unloaded
        && IsPreallocatedBrush(ho)
    ) {
        //While deleting system color brushes is not mandatory, it is still allowed. We need to catch these calls and ignore them so the custom brush continues to be available elsewhere.
        return TRUE;
    }
    else {
        return pOriginalDeleteObject(ho);
    }
}

#pragma endregion Hooks



#pragma region Mod entrypoints - Init, AfterInit, BeforeUninit, Uninit

bool DetectNonTeamsWebView() {

    bool hookAllMsEdgeWebView = Wh_GetIntSetting(L"hookAllMsEdgeWebView");
    if (hookAllMsEdgeWebView)
        return false;


    WCHAR programPath[nMaxPathLength];
    DWORD dwSize = ARRAYSIZE(programPath);
    if (!QueryFullProcessImageNameW(GetCurrentProcess(), 0, programPath, &dwSize)) {
        *programPath = L'\0';
    }

    //is the current process msedgewebview?
    PCWSTR msedgewebviewProcessName = L"\\msedgewebview";
    if (StrStrIW(programPath, msedgewebviewProcessName)) {

        //if the current process is msedgewebview then check whether it is serving ms-teams.exe, else do not hook
        LPCWSTR commandLine = GetCommandLineW();    //the lifetime of the returned value is managed by the system, applications should not free or modify this value
        if (!StrStrIW(commandLine, L"--webview-exe-name=ms-teams.exe")) {
            Wh_Log(L"Teams MsEdgeWebView process detected");
            return true;
        }
        else {
            Wh_Log(L"Non-Teams MsEdgeWebView process detected");
        }
    }

    return false;
}

// Returns true when this process is Helium on a build the settings don't list.
bool IsUnknownHeliumBuild() {

    WCHAR programPath[nMaxPathLength];
    DWORD dwSize = ARRAYSIZE(programPath);
    if (!QueryFullProcessImageNameW(GetCurrentProcess(), 0, programPath, &dwSize))
        return false;
    if (!StrStrIW(programPath, L"\\imput\\Helium\\"))
        return false;

    WCHAR version[64] = L"";
    DWORD handle = 0;
    DWORD size = GetFileVersionInfoSizeW(programPath, &handle);
    if (size) {
        void* data = HeapAlloc(GetProcessHeap(), 0, size);
        VS_FIXEDFILEINFO* info = nullptr;
        UINT infoLen = 0;
        if (data
            && GetFileVersionInfoW(programPath, 0, size, data)
            && VerQueryValueW(data, L"\\", (void**)&info, &infoLen)
            && info && infoLen >= sizeof(VS_FIXEDFILEINFO)) {
            wsprintfW(version, L"%u.%u.%u.%u",
                HIWORD(info->dwFileVersionMS), LOWORD(info->dwFileVersionMS),
                HIWORD(info->dwFileVersionLS), LOWORD(info->dwFileVersionLS));
        }
        if (data)
            HeapFree(GetProcessHeap(), 0, data);
    }

    PCWSTR list = Wh_GetStringSetting(L"heliumBuilds");
    bool known = false;
    if (list && *version) {
        WCHAR buf[512];
        lstrcpynW(buf, list, ARRAYSIZE(buf));
        WCHAR* ctx = nullptr;
        for (WCHAR* tok = wcstok_s(buf, L", ;", &ctx); tok; tok = wcstok_s(nullptr, L", ;", &ctx)) {
            if (wcscmp(tok, L"*") == 0 || _wcsicmp(tok, version) == 0) {
                known = true;
                break;
            }
        }
    }
    if (list)
        Wh_FreeStringSetting(list);

    if (!known)
        Wh_Log(L"Helium %ls is not in the builds list, skipping", *version ? version : L"(version unreadable)");
    return !known;
}

void LoadSettings() {

    g_applyToAllWebView = Wh_GetIntSetting(L"applyToAllMsEdgeWebView");
}

BOOL Wh_ModInit() {

    g_processId = GetCurrentProcessId();

    if (IsUnknownHeliumBuild())
        return FALSE;   // Windhawk unloads the mod from this process, nothing is hooked

    pRtlDllShutdownInProgress = (RtlDllShutdownInProgress_t)GetProcAddress(
        GetModuleHandleW(L"ntdll.dll"), "RtlDllShutdownInProgress");
    g_filePickerDetectionMap = new std::map<void*, bool>();

    LoadSettings();
    g_isNonTeamsWebView = DetectNonTeamsWebView();


    Wh_Log(L"Initialising hooks...");


    hGdi32 = LoadLibraryW(L"Gdi32.dll");
    if (!hGdi32) {
        Wh_Log(L"Error: Loading Gdi32.dll failed");
        return FALSE;
    }

    hUser32 = LoadLibraryW(L"User32.dll");
    if (!hUser32) {
        Wh_Log(L"Error: Loading User32.dll failed");
        return FALSE;
    }


    FARPROC pGetSysColor = GetProcAddress(hUser32, "GetSysColor"); 
    FARPROC pGetSysColorBrush = GetProcAddress(hUser32, "GetSysColorBrush");
    FARPROC pDeleteObject = GetProcAddress(hGdi32, "DeleteObject");

    if (!pGetSysColor) {
        Wh_Log(L"Finding hookable function GetSysColor from User32.dll failed");
        return FALSE;
    }     
    else if (!pGetSysColorBrush) {
        Wh_Log(L"Finding hookable function GetSysColorBrush from User32.dll failed");
        return FALSE;
    } 
    else if (!pDeleteObject) {
        Wh_Log(L"Finding hookable function DeleteObject from Gdi32.dll failed");
        return FALSE;
    }


    pOriginalGetSysColor = (GetSysColor_t)pGetSysColor;    
    for (int i = 0; i <= MAX_COLOR_INDEX; i++)
    {
        COLORREF color = pOriginalGetSysColor(i);
        HBRUSH brush = CreateSolidBrush(color);

        g_preallocatedBrushes[i] = brush;
    }


    Wh_SetFunctionHookT(pGetSysColor, GetSysColorHook, &pOriginalGetSysColor);
    Wh_SetFunctionHookT(pGetSysColorBrush, GetSysColorBrushHook, &pOriginalGetSysColorBrush);
    Wh_SetFunctionHookT(pDeleteObject, DeleteObjectHook, &pOriginalDeleteObject);


    return TRUE;
}

BOOL CALLBACK EnumBrowserWindowsFunc(HWND hWnd, LPARAM doNotWait) {

    DWORD dwProcessId = 0;
    DWORD dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);
    if (
        !dwThreadId 
        || dwProcessId != g_processId
    ) {
        return TRUE;
    }

    if (doNotWait) {
        //Sends the specified message to a window or windows. If the window was created by the calling thread, SendNotifyMessage calls the window procedure for the window and does not return until the window procedure has processed the message. If the window was created by a different thread, SendNotifyMessage passes the message to the window procedure and returns immediately; it does not wait for the window procedure to finish processing the message.
        SendNotifyMessageW(hWnd, WM_SYSCOLORCHANGE, NULL, NULL);
    }
    else {
        //Unfortunately, cannot use SendMessageCallbackW here since some windows never call the callback for some reason.

        //Calls the window procedure for the specified window and, if the specified window belongs to a different thread, does not return until the window procedure has processed the message or the specified time-out period has elapsed. If the window receiving the message belongs to the same queue as the current thread, the window procedure is called directly - the time-out value is ignored
        SendMessageTimeoutW(
            hWnd, 
            WM_SYSCOLORCHANGE, 
            NULL, 
            NULL, 
            SMTO_NOTIMEOUTIFNOTHUNG,    //The function does not enforce the time-out period as long as the receiving thread is processing messages. 
            1000,   //uTimeout
            NULL    //lpdwResult
        );
    }

    return TRUE;
}

void Wh_ModAfterInit(void) {

    Wh_Log(L"Initialising hooks done");

    //try to apply the updated colors to the previously running browser process immediately
    EnumWindows(EnumBrowserWindowsFunc, /*doNotWait*/true);
}

void Wh_ModSettingsChanged() {

    Wh_Log(L"SettingsChanged");

    LoadSettings();

    if (g_isNonTeamsWebView) {
        //try to apply the updated colors to the previously running MsEdgeWebView process immediately
        EnumWindows(EnumBrowserWindowsFunc, /*doNotWait*/true);
    }
}

void Wh_ModBeforeUninit() {

    Wh_Log(L"Restoring initial color scheme");

    g_unloading = true; //use original color scheme while processing WM_SYSCOLORCHANGE and onwards

    //try to apply the original colors
    EnumWindows(EnumBrowserWindowsFunc, /*doNotWait*/false);
}

void Wh_ModUninit() {

    Wh_Log(L"Uninit");

    g_unloaded = true;  //stop the hooks from treating our brushes specially

    //Wait for hooks to exit. I have seen programs crashing during mod unload without this.
    do {    //first sleep, then check g_hookRefCount since some hooked function might have a) entered, but not increased g_hookRefCount yet, or b) has decremented g_hookRefCount but not returned to the caller yet
        if (g_hookRefCount)
            Wh_Log(L"g_hookRefCount: %lli", (long long)g_hookRefCount);

        Sleep(1000);    //NB! Sleep always at least once. See the comment at the "do" keyword.

    } while (g_hookRefCount > 0 && !ProcessExiting());

    if (!ProcessExiting() && pOriginalDeleteObject) {
        for (int i = 0; i <= MAX_COLOR_INDEX; i++) {
            HBRUSH brush = g_preallocatedBrushes[i];
            g_preallocatedBrushes[i] = NULL;
            if (brush)
                pOriginalDeleteObject(brush);
        }
    }


    if (hGdi32) {
        FreeLibrary(hGdi32);
        hGdi32 = NULL;
    }

    if (hUser32) {
        FreeLibrary(hUser32);
        hUser32 = NULL;
    }
}

#pragma endregion Mod entrypoints - Init, AfterInit, SettingsChanged, Uninit
